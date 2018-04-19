#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/lexem.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/ExactWordEntryLocator.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/KnowledgeBase.h>

using namespace Solarix;


KB_Argument::KB_Argument(void) : id_entry(UNKNOWN), id_class(UNKNOWN), id_metaentry(UNKNOWN), is_regex(false), case_sensitive(false),
ThesaurusCheck_Link(UNKNOWN), ThesaurusCheck_Entry(UNKNOWN)
{
}



void KB_Argument::InitRegularExpression()
{
    if (case_sensitive)
    {
        // с точным учетом регистра
        rx = boost::wregex(regex_str.c_str());
    }
    else
    {
        // с игнорированием регистра
        rx = boost::wregex(regex_str.c_str(), boost::regex_constants::icase);
    }

    return;
}





#if defined SOL_LOADTXT && defined SOL_COMPILER
void KB_Argument::LoadTxt(const KB_Facts & facts, Solarix::Dictionary &dict, lem::Iridium::Macro_Parser &txtfile)
{
    lem::Iridium::BethToken t1 = txtfile.read();

    is_positive = true;

    if (t1.GetToken() == B_TILDA)
    {
        is_positive = false;
        t1 = txtfile.read();
    }

    if (t1.string() == L'@')
    {
        // Пока реализовано только задание регулярного выражения.

        t1 = txtfile.read();
        if (t1.string().eqi(L"regex"))
        {
            is_regex = true;
        }
        else if (t1.string().eqi(L"regex_strict"))
        {
            is_regex = case_sensitive = true;
        }
        else
        {
            lem::Iridium::Print_Error(t1, txtfile);
            dict.GetIO().merr().printf("Unknown function %us\n", t1.string().c_str());
            throw lem::E_BaseException();
        }

        txtfile.read_it(B_OROUNDPAREN);
        regex_str = txtfile.read().GetFullStr();

        if (regex_str.front() == L'"' && regex_str.back() == L'"')
        {
            regex_str.strip_quotes();
        }
        else if (regex_str.front() == L'\'' && regex_str.back() == L'\'')
        {
            regex_str.strip_apostrophes();
        }
        else
        {
            lem::Iridium::Print_Error(t1, txtfile);
            dict.GetIO().merr().printf("\" or ' are exected for argument %us\n", regex_str.c_str());
            throw lem::E_BaseException();
        }

        txtfile.read_it(B_CROUNDPAREN);

        if (txtfile.probe(B_OFIGPAREN))
        {
            Solarix::ExactWordEntryLocator omonym_resolver;
            LoadPreciser(dict, txtfile, omonym_resolver);
        }

        return;
    }

    WordEntrySet & sets = dict.GetLexAuto().GetWordEntrySet();

    if (lem::in_quotes(t1.string()))
    {
        Lexem lex(t1.string().strip_quotes());

        dict.GetLexAuto().TranslateLexem(lex, true, facts.GetLanguage());
        word = lex;

        if (txtfile.probe(B_OFIGPAREN))
        {
            Solarix::ExactWordEntryLocator omonym_resolver;
            LoadPreciser(dict, txtfile, omonym_resolver);
        }
    }
    else if (lem::in_apostrophes(t1.string()))
    {
        Lexem lex(t1.string().strip_apostrophes());

        dict.GetLexAuto().TranslateLexem(lex, true, facts.GetLanguage());
        word = lex;

        if (txtfile.probe(B_OFIGPAREN))
        {
            Solarix::ExactWordEntryLocator omonym_resolver;
            LoadPreciser(dict, txtfile, omonym_resolver);
        }
    }
    else if (t1.GetToken() == B_ANY)
    {
        id_entry = ANY_STATE;
        // может встретится конструкция *:*
        if (txtfile.probe(B_COLON))
        {
            txtfile.read_it(B_ANY);
            txtfile.read_it(B_OFIGPAREN);

            Solarix::ExactWordEntryLocator omonym_resolver;
            LoadPreciser(dict, txtfile, omonym_resolver);
        }
        else
        {
            if (txtfile.probe(B_OFIGPAREN))
            {
                Solarix::ExactWordEntryLocator omonym_resolver;
                LoadPreciser(dict, txtfile, omonym_resolver);
            }
        }
    }
    else
    {
        lem::UCString class_name(t1.string());

        if (sets.IsWordEntrySetName(class_name))
        {
            wordentryset_name = class_name;
            if (txtfile.probe(B_OFIGPAREN))
            {
                Solarix::ExactWordEntryLocator omonym_resolver;
                LoadPreciser(dict, txtfile, omonym_resolver);
            }
        }
        else if (sets.IsWordSetName(class_name))
        {
            wordset_name = class_name;
            if (txtfile.probe(B_OFIGPAREN))
            {
                Solarix::ExactWordEntryLocator omonym_resolver;
                LoadPreciser(dict, txtfile, omonym_resolver);
            }
        }
        else
        {
            id_class = dict.GetSynGram().FindClass(class_name);
            if (id_class == UNKNOWN)
            {
                lem::Iridium::Print_Error(t1, txtfile);
                dict.GetIO().merr().printf("Unknown class %us\n", class_name.c_str());
                throw lem::E_BaseException();
            }

            if (txtfile.probe(B_COLON))
            {
                lem::Iridium::BSourceState ebeg = txtfile.tellp();
                const UCString mname = sol_read_multyname(dict.GetIO(), txtfile, B_OFIGPAREN);

                Solarix::Lexem lex_name(mname);
                dict.GetLexAuto().TranslateLexem(lex_name, true, facts.GetLanguage());

                Solarix::ExactWordEntryLocator omonym_resolver;

                // Имеем пару класс:имя_статьи
                LoadPreciser(dict, txtfile, omonym_resolver);

                // Пытаемся найти статью.
                if (mname.front() != sol_get_token(B_ANY))
                {
                    // Считан НЕ квантор всеобщности, так что это должно
                    // быть имя статьи.
                    // Попытаемся найти статью среди уже загруженных, причем
                    // ищем с критерием принадлежности определенному синтаксическому
                    // классу.


                    if (dict.GetSynGram().IsOmonym(id_class, lex_name))
                    {
                        const SG_Class & pos = dict.GetSynGram().GetClass(id_class);
                        for (lem::Container::size_type i = 0; i < coords.size(); ++i)
                        {
                            if (pos.attrs().find(coords[i].GetCoord()) != UNKNOWN || pos.tags().find(coords[i].GetCoord()) != UNKNOWN)
                            {
                                omonym_resolver.pairs.push_back(coords[i]);
                                // вообще говоря, атрибут или тег можно убрать из списка coords...
                            }
                            else if (pos.dims().find(coords[i].GetCoord()) != UNKNOWN)
                            {
                            }
                            else
                            {
                                const GramCoord & c = dict.GetSynGram().coords()[coords[i].GetCoord().GetIndex()];
                                lem::Iridium::Print_Error(ebeg, txtfile);
                                dict.GetIO().merr().printf("Part of speech [%us] does not have coordinate [%us]\n", class_name.c_str(), c.GetName().string().c_str());
                                throw lem::E_BaseException();
                            }
                        }


                        lem::MCollect<int> ies;

                        dict.GetSynGram().FindEntries(lex_name, ies);

                        int icur = 0;
                        while (icur < CastSizeToInt(ies.size()))
                        {
                            const int ekey = ies[icur];
                            const SG_Entry &e = dict.GetSynGram().GetEntry(ekey);
                            if (e.GetClass() != id_class)
                            {
                                ies.Remove(icur);
                                continue;
                            }
                            else
                            {
                                bool match = omonym_resolver.Check(e, dict.GetSynGram());

                                if (!match)
                                {
                                    ies.Remove(icur);
                                    continue;
                                }
                                else
                                {
                                    icur++;
                                }
                            }
                        }

                        if (ies.size() == 1)
                            id_entry = ies.front();
                    }
                    else
                    {
                        const int found_id_entry = dict.GetSynGram().FindEntry2(lex_name, id_class);

                        if (found_id_entry != UNKNOWN)
                        {
                            if (omonym_resolver.Empty())
                                id_entry = found_id_entry;
                            else
                            {
                                const SG_Entry &e = dict.GetSynGram().GetEntry(found_id_entry);
                                if (omonym_resolver.Check(e, dict.GetSynGram()))
                                    id_entry = found_id_entry;
                            }
                        }
                    }

                    // Нашли ?
                    if (id_entry == UNKNOWN)
                    {
                        // сделаем попытку найти метастатью
                        id_metaentry = dict.GetSynGram().FindMetaEntry(mname, id_class);

                        if (id_metaentry == UNKNOWN)
                        {
                            // Нет! Выводим сообщение об неверном имени словарной статьи.
                            lem::Iridium::Print_Error(ebeg, txtfile);
                            dict.GetIO().merr().printf("The entry [%vfE%us%vn] is not previously declared in grammar\n", mname.c_str());
                            throw lem::E_BaseException();
                        }
                    }
                }
            }
        }
    }


    return;
}
#endif




#if defined SOL_LOADTXT && defined SOL_COMPILER
void KB_Argument::LoadPreciser(
    Dictionary & dict,
    lem::Iridium::Macro_Parser & txtfile,
    Solarix::ExactWordEntryLocator & locator
)
{
    SynGram &sg = dict.GetSynGram();

    while (!txtfile.eof())
    {
        if (txtfile.pick().GetToken() == B_CFIGPAREN)
        {
            txtfile.read();
            break;
        }

        if (txtfile.probe(L"aux"))
        {
            locator.LoadAuxSelector(txtfile, dict.GetSynGram());
            continue;
        }

        // может быть задание простой проверки на связь в тезаурусе
        if (txtfile.pick().GetToken() == B_OTRIPAREN)
        {
            if (ThesaurusCheck_Link != UNKNOWN)
            {
                dict.GetIO().merr().printf("Only one thesaurus check is allowed\n");
                lem::Iridium::Print_Error(txtfile);
                throw lem::E_BaseException();
            }

            Solarix::Tree_Link link(txtfile, sg);
            ThesaurusCheck_Link = link.GetState();

            // далее идет спецификация словарной статьи.
            lem::Iridium::BethToken class_name = txtfile.read();
            const int iclass = sg.FindClass(class_name.string());
            if (iclass == UNKNOWN)
            {
                sg.GetIO().merr().printf("Unknown class name [%us]\n", class_name.string().c_str());
                lem::Iridium::Print_Error(txtfile);
                throw lem::E_BaseException();
            }

            txtfile.read_it(B_COLON);

            lem::Iridium::BSourceState ebeg = txtfile.tellp();
            const UCString mname = sol_read_multyname(sg.GetIO(), txtfile, B_OFIGPAREN);
            txtfile.read_it(B_CFIGPAREN);

            // Имеем пару класс:имя_статьи
            ThesaurusCheck_Entry = sg.FindEntry(mname, iclass, false);

            // Нашли ?
            if (ThesaurusCheck_Entry == UNKNOWN)
            {
                // Нет! Выводим сообщение об неверном имени словарной статьи.
                lem::Iridium::Print_Error(ebeg, txtfile);
                sg.GetIO().merr().printf("The entry [%us:%vfE%us%vn] is not previously declared in grammar\n", class_name.string().c_str(), mname.c_str());
                throw lem::E_BaseException();
            }

            continue;
        }

        // для обычных: координата:состояние
        // для бистабильных: координата
        // для согласования с координатами в именованных точках слева =имя_точки:координата
        // расширенный формат описания согласования с именованными точками =имя_коорд->имя_точки:имя_коорд
        lem::Iridium::BethToken coord_name = txtfile.read();

        bool AFFIRM = true;

        if (coord_name.GetToken() == B_NEGATIVE)
        {
            // Оператор отрицания перед определением координаты!
            AFFIRM = false;
            coord_name = txtfile.read();
        }

        const GramCoordAdr iglob_coord = sg.FindCoord(coord_name.string());

        if (!iglob_coord.IsDefined())
        {
            sg.GetIO().merr().printf("Unknown coordinate %us\n", coord_name.c_str());
            lem::Iridium::Print_Error(coord_name, txtfile);
            throw lem::E_BaseException();
        }

        if (sg.coords()[iglob_coord.GetIndex()].IsBistable())
        {
            // Имя состояния не может быть указано.
            coords.push_back(GramCoordPair(iglob_coord, AFFIRM));
        }
        else
        {
            // После двоеточия должно идти имя состояния для координаты.
            txtfile.read_it(B_COLON);

            // Имя состояния.
            BethToken state_name = txtfile.read();

            // Получим индекс состояния для определенной координаты.
            const int istate = sg.coords()[iglob_coord.GetIndex()]
                .FindState(state_name.string());
            if (istate == UNKNOWN)
            {
                // Нет такого состояния для этого измерения.
                lem::Iridium::Print_Error(state_name, txtfile);
                sg.GetIO().merr().printf(
                    "State [%vfE%us%vn] is not declared for coordinate [%vfE%us%vn]\n"
                    , state_name.c_str(), coord_name.c_str()
                );
                throw E_ParserError();
            }

            coords.push_back(GramCoordEx(iglob_coord, istate, AFFIRM));
        }
    }

    return;
}
#endif



#if defined SOL_CAA
bool KB_Argument::Match(Solarix::Dictionary *dict, const Solarix::Word_Form &val) const
{
    if (is_regex)
    {
        const lem::UCString & word = *val.GetName();
        bool r = boost::regex_match(word.c_str(), rx);
        if (!r)
            return Positive(false);
    }
    else if (!word.empty())
    {
        if (word != *val.GetNormalized())
            return Positive(false);
    }

    if (id_metaentry != UNKNOWN)
    {
        return dict->GetSynGram().GetStorage().DoesMetaEntryContains(id_metaentry, val.GetEntryKey());
    }
    else if (id_entry != UNKNOWN)
    {
        if (id_entry != ANY_STATE && id_entry != val.GetEntryKey())
            return Positive(false);
    }
    else if (id_class != UNKNOWN && id_class != dict->GetSynGram().GetEntry(val.GetEntryKey()).GetClass())
        return Positive(false);

    if (!wordentryset_name.empty())
    {
        LexicalAutomat &la = dict->GetLexAuto();
        const bool set_contains = la.GetWordEntrySet().FindWordEntrySet(wordentryset_name, val.GetEntryKey());
        if (!set_contains)
            return Positive(false);
    }
    else if (!wordset_name.empty())
    {
        LexicalAutomat &la = dict->GetLexAuto();
        const bool set_contains = la.GetWordEntrySet().FindWordSet(wordset_name, *val.GetName());
        if (!set_contains)
            return Positive(false);
    }


    for (lem::Container::size_type i = 0; i < coords.size(); ++i)
    {
        if (coords[i].GetAffirm())
        {
            if (val.GetPairs().FindOnce(coords[i]) == UNKNOWN)
            {
                return Positive(false);
            }
        }
        else
        {
            if (val.GetPairs().FindOnce(coords[i]) != UNKNOWN)
            {
                return Positive(false);
            }
            else
            {
                // такой координатной пары нет.
                // для бистабильных необходима дополнительная проверка, так как отсутствие и состояние 0 равносильны.
                if (dict->GetSynGram().coords()[coords[i].GetCoord().GetIndex()].IsBistable())
                {
                    if (coords[i].GetState() != 0)
                    {
                        return Positive(false);
                    }
                }
            }
        }
    }

    if (ThesaurusCheck_Link != UNKNOWN)
    {
        // проверяем, что данная статья связана в тезаурусе в указанной статьей заданным типом связи
        int id_link = dict->GetSynGram().Get_Net().Find_Linked_Entry(val.GetEntryKey(), ThesaurusCheck_Link, ThesaurusCheck_Entry);
        if (id_link == UNKNOWN)
            return Positive(false);
    }

    return Positive(true);
}
#endif


#if defined SOL_CAA
bool KB_Argument::Positive(bool f) const
{
    return is_positive ? f : !f;
}
#endif


bool KB_Argument::IsQueryableByEntry() const
{
    return (!lem::is_quantor(id_entry) || id_metaentry != UNKNOWN) && is_positive;
}


bool KB_Argument::IsQueryableByWord() const
{
    return !word.empty() && is_positive;
}


bool KB_Argument::NeedsFeatureCheck() const
{
    return !coords.empty();
}


bool KB_Argument::IsMetaEntry() const
{
    return id_metaentry != UNKNOWN;
}
