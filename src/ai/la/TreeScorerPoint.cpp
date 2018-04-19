#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/AuxFormTypes.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/TreeScorers.h>
#include <lem/solarix/TreeScorerApplicationContext.h>
#include <lem/solarix/TreeScorer.h>

using namespace Solarix;


TreeScorerPoint::TreeScorerPoint()
{
    id = UNKNOWN;
    id_src = UNKNOWN;
    id_group = UNKNOWN;
    link_type = UNKNOWN;
    id_metaentry = id_entry = id_class = UNKNOWN;
    ThesaurusCheck_Link = ThesaurusCheck_Entry = UNKNOWN;
    relative_position = UNKNOWN;
    is_positive = true;

    children_quantification.min_count = 0;
    children_quantification.max_count = 0;

    return;
}


TreeScorerPoint::~TreeScorerPoint()
{
    for (auto leaf : leafs)
    {
        delete leaf;
    }

    for (auto predicate : predicates)
    {
        delete predicate;
    }

    return;
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
void TreeScorerPoint::LoadTxt_Sequence(
    Dictionary & dict,
    lem::Iridium::Macro_Parser & txtfile,
    const TreeScorer & body,
    WordEntrySet &sets,
    TreeScorers & scorers,
    TreeScorerMarkers & markers
)
{
    LoadTxt_Point(dict, txtfile, body, sets, scorers, markers);

    if (!txtfile.probe(B_CFIGPAREN))
    {
        TreeScorerPoint * child = new TreeScorerPoint();
        child->LoadTxt_Sequence(dict, txtfile, body, sets, scorers, markers);
        leafs.push_back(child);

        children_quantification.min_count += child->quantification.GetMinCount();
        children_quantification.max_count += child->quantification.GetMaxCount();
    }

    return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void TreeScorerPoint::LoadTxt_Tree(
    Dictionary & dict,
    lem::Iridium::Macro_Parser & txtfile,
    const TreeScorer & body,
    WordEntrySet &sets,
    TreeScorers & scorers,
    TreeScorerMarkers & markers
)
{
    LoadTxt_Point(dict, txtfile, body, sets, scorers, markers);

    if (txtfile.probe(B_DOT))
    {
        if (txtfile.probe(B_OFIGPAREN))
        {
            // набор веток в фигурных скобках
            while (!txtfile.eof())
            {
                if (txtfile.probe(B_CFIGPAREN))
                    break;

                const lem::Iridium::BethToken & t = txtfile.pick();
                if (t.string() == L'@')
                {
                    TreeScorerPredicate * predicate = new TreeScorerPredicate();
                    predicate->LoadTxt(dict, txtfile);
                    predicates.push_back(predicate);
                }
                else
                {
                    TreeScorerPoint * child = new TreeScorerPoint();
                    child->LoadTxt_Tree(dict, txtfile, body, sets, scorers, markers);
                    leafs.push_back(child);

                    children_quantification.min_count += child->quantification.GetMinCount();
                    children_quantification.max_count += child->quantification.GetMaxCount();
                }
            }
        }
        else
        {
            // единственная ветка
            const lem::Iridium::BethToken & t = txtfile.pick();
            if (t.string() == L'@')
            {
                TreeScorerPredicate * predicate = new TreeScorerPredicate();
                predicate->LoadTxt(dict, txtfile);
                predicates.push_back(predicate);
            }
            else
            {
                TreeScorerPoint * child = new TreeScorerPoint();
                child->LoadTxt_Tree(dict, txtfile, body, sets, scorers, markers);
                leafs.push_back(child);

                children_quantification.min_count += child->quantification.GetMinCount();
                children_quantification.max_count += child->quantification.GetMaxCount();
            }
        }
    }

    if (!predicates.empty())
    {
        children_quantification.SetNoLimits();
    }

    return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
void TreeScorerPoint::LoadMarker(
    Dictionary & dict,
    lem::Iridium::Macro_Parser & txtfile,
    TreeScorerMarkers & markers
)
{
    const lem::Iridium::BethToken & t = txtfile.read();
    if (txtfile.probe(B_EQUAL))
    {
        marker = lem::to_upper(t.string());
        if (markers.IsAlreadyBound(marker))
        {
            lem::Iridium::Print_Error(t, txtfile);
            dict.GetIO().merr().printf("Variable %us already bound\n", marker.c_str());
            throw lem::E_BaseException();
        }

        markers.AddBoundMarker(marker);
    }
    else
    {
        txtfile.seekp(t);
    }

    return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void TreeScorerPoint::LoadTxt_Point(
    Dictionary & dict,
    lem::Iridium::Macro_Parser & txtfile,
    const TreeScorer & body,
    WordEntrySet &sets,
    TreeScorers & scorers,
    TreeScorerMarkers & markers
)
{
    id_src = dict.GetDebugSymbols().RegisterLocation(txtfile, txtfile.tellp());

    LoadMarker(dict, txtfile, markers);

    quantification.LoadTxt(txtfile);

    Tree_Link dummy_link;
    if (dummy_link.LoadTxt(txtfile, dict.GetSynGram()))
        link_type = dummy_link.GetState();
    else
        link_type = UNKNOWN;

    lem::Iridium::BethToken t1 = txtfile.read();

    is_positive = true;

    if (t1.GetToken() == B_TILDA)
    {
        is_positive = false;
        t1 = txtfile.read();
    }

    if (lem::in_quotes(t1.string()))
    {
        Lexem lex(t1.string().strip_quotes());

        dict.GetLexAuto().TranslateLexem(lex, true, body.GetLanguage());
        word = lex;

        if (txtfile.probe(B_OFIGPAREN))
            LoadPreciser(dict, txtfile, sets, markers);
    }
    else if (lem::in_apostrophes(t1.string()))
    {
        Lexem lex(t1.string().strip_apostrophes());

        dict.GetLexAuto().TranslateLexem(lex, true, body.GetLanguage());
        word = lex;

        if (txtfile.probe(B_OFIGPAREN))
            LoadPreciser(dict, txtfile, sets, markers);
    }
    else if (t1.GetToken() == B_ANY)
    {
        id_entry = ANY_STATE;
        // может встретится конструкция *:*
        if (txtfile.probe(B_COLON))
        {
            txtfile.read_it(B_ANY);
            txtfile.read_it(B_OFIGPAREN);
            LoadPreciser(dict, txtfile, sets, markers);
        }
        else
        {
            if (txtfile.probe(B_OFIGPAREN))
                LoadPreciser(dict, txtfile, sets, markers);
        }
    }
    else
    {
        lem::UCString class_name(t1.string());

        id_group = scorers.FindGroup(class_name, false);
        if (id_group != UNKNOWN)
        {
            // тут будет вызов решающего поддерева. 
            // разрешим также указать дополнительные условия на корневой узел
            if (txtfile.probe(B_OFIGPAREN))
                LoadPreciser(dict, txtfile, sets, markers);
        }
        else if (sets.IsWordEntrySetName(class_name))
        {
            wordentryset_name = class_name;
            if (txtfile.probe(B_OFIGPAREN))
                LoadPreciser(dict, txtfile, sets, markers);
        }
        else if (sets.IsWordformSetName(class_name))
        {
            wordformset_name = class_name;
            if (txtfile.probe(B_OFIGPAREN))
                LoadPreciser(dict, txtfile, sets, markers);
        }
        else if (sets.IsWordSetName(class_name))
        {
            wordset_name = class_name;
            if (txtfile.probe(B_OFIGPAREN))
                LoadPreciser(dict, txtfile, sets, markers);
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

                // Имеем пару класс:имя_статьи

                // Пытаемся найти словарную статью.
                if (mname.front() != sol_get_token(B_ANY))
                {
                    // Считан НЕ квантор всеобщности, так что это должно
                    // быть имя статьи.
                    // Попытаемся найти статью среди уже загруженных, причем
                    // ищем с критерием принадлежности определенному синтаксическому
                    // классу.
                    LoadPreciser(dict, txtfile, sets, markers);


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

                            lem::Iridium::Print_Error(t1, txtfile);
                            dict.GetIO().merr().printf("Part of speech [%us] does not have coordinate [%us]\n", class_name.c_str(), c.GetName().string().c_str());
                            throw lem::E_BaseException();
                        }
                    }

                    Solarix::Lexem lex_name(mname);
                    dict.GetLexAuto().TranslateLexem(lex_name, true, body.GetLanguage());
                    id_entry = dict.GetSynGram().FindEntryOmonym(lex_name, id_class, omonym_resolver);

                    // Нашли ?
                    if (id_entry == UNKNOWN)
                    {
                        // сделаем попытку найти метастатью
                        id_metaentry = dict.GetSynGram().FindMetaEntry(lex_name, id_class);

                        if (id_metaentry == UNKNOWN)
                        {
                            // Нет! Выводим сообщение об неверном имени словарной статьи.
                            lem::Iridium::Print_Error(ebeg, txtfile);
                            dict.GetIO().merr().printf("The entry [%vfE%us%vn] is not previously declared in grammar\n", mname.c_str());
                            throw lem::E_BaseException();
                        }
                    }
                }
                else
                {
                    LoadPreciser(dict, txtfile, sets, markers);
                }
            }
        }
    }

    return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void TreeScorerPoint::LoadPreciser(
    Dictionary & dict,
    lem::Iridium::Macro_Parser & txtfile,
    WordEntrySet &sets,
    TreeScorerMarkers & markers
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
            omonym_resolver.aux_type = txtfile.read().string();
            if (omonym_resolver.aux_type.front() == L'"')
                omonym_resolver.aux_type.strip(L'"');
            else
                omonym_resolver.aux_type.strip(L'\'');

            txtfile.read_it(B_EQUAL);

            lem::Iridium::BethToken t = txtfile.read();

            omonym_resolver.aux_value = t.string();

            if (omonym_resolver.aux_value.front() == L'"')
                omonym_resolver.aux_value.strip(L'"');
            else
                omonym_resolver.aux_value.strip(L'\'');

            if (sg.GetAuxFormTypes()[omonym_resolver.aux_type] == UNKNOWN)
            {
                lem::Iridium::Print_Error(t, txtfile);
                sg.GetIO().merr().printf("Unknown aux form type %us\n", omonym_resolver.aux_type.c_str());
                throw E_ParserError();
            }

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

        lem::Iridium::BethToken coord_name = txtfile.read();

        if (coord_name.GetToken() == B_EQUAL || coord_name.GetToken() == B_LOGNE)
        {
            lem::Iridium::BethToken t = txtfile.read();
            lem::UCString mark_name = t.string();
            mark_name = lem::to_upper(mark_name);

            bool same_coords = true;
            GramCoordAdr iglob_coord0, iglob_coord1;

            if (txtfile.probe(L"->"))
            {
                lem::Iridium::BethToken coord_name0 = t;

                t = txtfile.read();
                mark_name = t.string();
                mark_name = lem::to_upper(mark_name);

                iglob_coord0 = sg.FindCoord(coord_name0.string());

                if (!iglob_coord0.IsDefined())
                {
                    sg.GetIO().merr().printf("Unknown coordinate [%us]\n", coord_name0.c_str());
                    lem::Iridium::Print_Error(coord_name0, txtfile);
                    throw lem::E_BaseException();
                }

                same_coords = false;
            }

            if (!markers.IsAlreadyBound(mark_name))
            {
                sg.GetIO().merr().printf("Unknown marker %us\n", mark_name.c_str());
                lem::Iridium::Print_Error(t, txtfile);
                throw lem::E_BaseException();
            }

            txtfile.read_it(B_COLON);

            bool for_group = txtfile.probe(B_OSPAREN);
            lem::Iridium::BethToken coord_name1 = txtfile.read();
            if (for_group) txtfile.read_it(B_CSPAREN);

            iglob_coord1 = sg.FindCoord(coord_name1.string());

            if (!iglob_coord1.IsDefined())
            {
                sg.GetIO().merr().printf("Unknown coordinate %us\n", coord_name1.c_str());
                lem::Iridium::Print_Error(coord_name1, txtfile);
                throw lem::E_BaseException();
            }

            if (same_coords)
                iglob_coord0 = iglob_coord1;

            BackRefCorrel c;
            c.affirmative = coord_name.GetToken() == B_EQUAL;
            c.name = mark_name;
            c.id_coord0 = iglob_coord0.GetIndex();
            c.id_coord1 = iglob_coord1.GetIndex();
            c.for_group = for_group;
            //c.violation_handler = violation_handler;
            back_correls.push_back(c);
            continue;
        }



        // может быть число - задание относительной позиции сопоставленного слова
        if (lem::is_int(coord_name.string()))
        {
            relative_position = lem::to_int(coord_name.string());
            continue;
        }


        // для обычных: координата:состояние
        // для бистабильных: координата

        if (coord_name.GetToken() == B_CLASS)
        {
            txtfile.read_it(B_COLON);
            lem::Iridium::BethToken class_name2 = txtfile.read();
            id_class = sg.FindClass(class_name2.string());
            if (id_class == UNKNOWN)
            {
                lem::Iridium::Print_Error(class_name2, txtfile);
                sg.GetIO().merr().printf("Unknown class [%vfE%us%vn]\n", class_name2.string().c_str());
                throw E_ParserError();
            }

            continue;
        }

        bool AFFIRM = true;

        if (coord_name.GetToken() == B_NEGATIVE)
        {
            // Оператор отрицания перед определением координаты!
            AFFIRM = false;
            coord_name = txtfile.read();
        }


        // Может быть указание на именованное множество, для проверки что проверяемое слово входит или не входит в такое множество.
        if (sets.IsWordSetName(coord_name))
        {
            CollocFilterSetChecker set_checker;
            set_checker.SetWordSet();
            set_checker.set_name = coord_name;
            set_checker.affirm = AFFIRM;
            set_checkers.push_back(set_checker);

            if (set_checkers.size() > 3)
            {
                lem::Iridium::Print_Error(coord_name, txtfile);
                sg.GetIO().merr().printf("Too many named sets\n");
                throw E_ParserError();
            }

            continue;
        }
        else if (sets.IsWordEntrySetName(coord_name))
        {
            CollocFilterSetChecker set_checker;
            set_checker.SetWordEntrySet();
            set_checker.set_name = coord_name;
            set_checker.affirm = AFFIRM;
            set_checkers.push_back(set_checker);

            if (set_checkers.size() > 3)
            {
                lem::Iridium::Print_Error(coord_name, txtfile);
                sg.GetIO().merr().printf("Too many named sets\n");
                throw E_ParserError();
            }

            continue;
        }


        // может быть уточнение для выбора словарной статьи
        const int id_classX = dict.GetSynGram().FindClass(coord_name);
        if (id_classX != UNKNOWN)
        {
            lem::Iridium::BSourceState b = txtfile.tellp();

            txtfile.read_it(B_COLON);

            lem::Iridium::BSourceState ebeg = txtfile.tellp();
            const UCString mname = sol_read_multyname(dict.GetIO(), txtfile, B_OFIGPAREN);

            id_entry = dict.GetSynGram().FindEntry(mname, id_classX, false);

            // Нашли ?
            if (id_entry != UNKNOWN)
            {
                txtfile.read_it(B_CFIGPAREN);
                continue;
            }

            txtfile.seekp(b);
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





int TreeScorerPoint::Store(LexiconStorage & storage, int id_parent_point)
{
    id = storage.StoreTreeScorerPoint(
        id_parent_point,
        id_group,
        word, id_entry, id_metaentry, id_class, wordset_name, wordentryset_name, wordformset_name,
        coords,
        ThesaurusCheck_Link, ThesaurusCheck_Entry,
        set_checkers,
        is_positive,
        link_type,
        relative_position,
        id_src,
        quantification.min_count,
        quantification.max_count,
        children_quantification.min_count,
        children_quantification.max_count,
        marker,
        back_correls
    );

    for (lem::Container::size_type i = 0; i < leafs.size(); ++i)
    {
        leafs[i]->Store(storage, id);
    }

    for (lem::Container::size_type i = 0; i < predicates.size(); ++i)
    {
        predicates[i]->Store(storage, id);
    }

    return id;
}



bool TreeScorerPoint::Positive(bool f) const
{
    return is_positive ? f : !f;
}



#if defined SOL_CAA
bool TreeScorerPoint::DoesMatch(
    SynGram &sg,
    const Word_Form & version,
    const LinkEdgeContainer & edges,
    const TreeScorerApplicationContext & context,
    const TreeScorerBoundVariables & bound_variables
) const
{
    if (!predicates.empty())
    {
        for (lem::Container::size_type i = 0; i < predicates.size(); ++i)
        {
            if (!predicates[i]->DoesMatch(sg, version, edges, context))
                return Positive(false);
        }
    }

    if (!word.empty())
    {
        if (word != *version.GetNormalized())
            return Positive(false);
    }

    if (relative_position != UNKNOWN)
    {
        // проверим, что позиция словоформы version не вступает в противоречие с позициями ранее отмеченных токенов.
        if (!context.CheckPosition(version, relative_position))
            return Positive(false);
    }

    if (id_group != UNKNOWN)
    {
        // проверка через поддеревья будет выполняться снаружи, поэтому просто предположим успех.
    }
    else if (id_entry != UNKNOWN)
    {
        if (id_entry != ANY_STATE && id_entry != version.GetEntryKey())
            return Positive(false);
    }
    else if (id_metaentry != UNKNOWN)
    {
        return sg.GetStorage().DoesMetaEntryContains(id_metaentry, version.GetEntryKey());
    }
    else if (id_class != UNKNOWN && id_class != sg.GetEntry(version.GetEntryKey()).GetClass())
    {
        return Positive(false);
    }

    if (id_class != UNKNOWN)
    {
        if (lem::is_quantor(version.GetEntryKey()))
            return Positive(false);

        if (sg.GetEntry(version.GetEntryKey()).GetClass() != id_class)
            return Positive(false);
    }

    if (!wordentryset_name.empty())
    {
        LexicalAutomat &la = sg.GetDict().GetLexAuto();
        const bool set_contains = la.GetWordEntrySet().FindWordEntrySet(wordentryset_name, version.GetEntryKey());
        if (!set_contains)
            return Positive(false);
    }
    else if (!wordformset_name.empty())
    {
        LexicalAutomat &la = sg.GetDict().GetLexAuto();
        const bool set_contains = la.GetWordEntrySet().FindWordformSet(sg, wordformset_name, version);
        if (!set_contains)
            return Positive(false);
    }
    else if (!wordset_name.empty())
    {
        LexicalAutomat &la = sg.GetDict().GetLexAuto();
        const bool set_contains = la.GetWordEntrySet().FindWordSet(wordset_name, *version.GetName());
        if (!set_contains)
            return Positive(false);
    }




    for (lem::Container::size_type i = 0; i < coords.size(); ++i)
    {
        if (coords[i].GetAffirm())
        {
            if (version.GetPairs().FindOnce(coords[i]) == UNKNOWN)
            {
                return Positive(false);
            }
        }
        else
        {
            if (version.GetPairs().FindOnce(coords[i]) != UNKNOWN)
            {
                return Positive(false);
            }
            else
            {
                // такой координатной пары нет.
                // для бистабильных необходима дополнительная проверка, так как отсутствие и состояние 0 равносильны.
                if (sg.coords()[coords[i].GetCoord().GetIndex()].IsBistable())
                    if (coords[i].GetState() != 0)
                    {
                        return Positive(false);
                    }
            }
        }
    }



    if (ThesaurusCheck_Link != UNKNOWN)
    {
        // проверяем, что данная статья связана в тезаурусе в указанной статьей заданным типом связи
        int id_link = sg.Get_Net().Find_Linked_Entry(version.GetEntryKey(), ThesaurusCheck_Link, ThesaurusCheck_Entry);
        if (id_link == UNKNOWN)
            return Positive(false);
    }

    // Проверяем теоретико-множественные предикаты в уточняющем условии.
    for (lem::Container::size_type i = 0; i < set_checkers.size(); ++i)
    {
        const CollocFilterSetChecker & set_checker = set_checkers[i];

        bool set_passed = false;

        if (set_checker.IsWordEntrySet())
        {
            LexicalAutomat &la = sg.GetDict().GetLexAuto();
            const bool set_contains = la.GetWordEntrySet().FindWordEntrySet(set_checker.set_name, version.GetEntryKey());
            set_passed = set_checker.Positive(set_contains);
        }
        else if (set_checker.IsWordSet())
        {
            LexicalAutomat &la = sg.GetDict().GetLexAuto();
            const bool set_contains = la.GetWordEntrySet().FindWordSet(set_checker.set_name, *version.GetName());
            set_passed = set_checker.Positive(set_contains);
        }

        if (!set_passed)
            return Positive(false);
    }

    // Проверяем условия для ранее сопоставленных узлов
    for (lem::Container::size_type i = 0; i < back_correls.size(); ++i)
    {
        const BackRefCorrel & condition = back_correls[i];

        const Solarix::Word_Form * bound_wordform = bound_variables.GetVariable(condition.name);
        if (bound_wordform == nullptr)
        {
            lem::MemFormatter mem;
            mem.printf("Can not find bound variable [%us]", condition.name.c_str());
            throw lem::E_BaseException(mem.string());
        }

        const int id_coord0 = condition.id_coord0; // состояние этой координаты в текущей словоформе должно соответствовать
        const int id_coord1 = condition.id_coord1; // состоянию этой координаты в связанной словоформе (маркировке)

        if (condition.for_group)
        {
            // not implemented
            LEM_STOPIT;
        }
        else
        {
            lem::IntCollect this_states = version.GetStates(id_coord0);
            if (!this_states.empty())
            {
                lem::IntCollect bound_states = bound_wordform->GetStates(id_coord1);
                if (!bound_states.empty())
                {
                    bool all_matched = true;
                    for (lem::Container::size_type q = 0; q < this_states.size(); ++q)
                    {
                        if (bound_states.find(this_states[q]) == UNKNOWN)
                        {
                            all_matched = false;
                            break;
                        }
                    }

                    if (!all_matched)
                    {
                        if (condition.affirmative)
                            return Positive(false);
                    }
                    else
                    {
                        if (!condition.affirmative)
                            return Positive(false);
                    }
                }
            }
        }

    }

    return Positive(true);
}
#endif


const TreeScorerPoint * TreeScorerPoint::FindNonQuantorNode() const
{
    if (IsWord() || (IsEntry() && id_entry != ANY_STATE) || IsMetaEntry())
        return this;

    for (lem::Container::size_type i = 0; i < leafs.size(); ++i)
    {
        const TreeScorerPoint * node = leafs[i]->FindNonQuantorNode();
        if (node != nullptr)
            return node;
    }

    return nullptr;
}


bool TreeScorerPoint::HasConstraints() const
{
    return !wordset_name.empty() || !wordentryset_name.empty() || !wordformset_name.empty() ||
        !coords.empty() ||
        ThesaurusCheck_Link != UNKNOWN ||
        !set_checkers.empty();
}


const lem::UCString& TreeScorerPoint::GetSetName() const
{
    if (!wordset_name.empty()) return wordset_name;
    if (!wordentryset_name.empty()) return wordentryset_name;
    if (!wordformset_name.empty()) return wordformset_name;
    LEM_STOPIT;
}
