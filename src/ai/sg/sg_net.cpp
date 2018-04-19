// 15.03.2006 - исправлены ошибки с формированием списков связанных статей
//              (игнорировалась фильтрация по типу связок)
//
// 31.05.2006 - исправлена ошибка в Find_Linked_Entries, если задавался пустой
//              список допустимых связок, то поиск не работал. 
//
// 22.09.2006 - введены сложные связки с участием деревьев
//
// 12.11.2007 - оптимизация процедуры сборки тезауруса после его существенного
//              расширения
//
// 28.11.2007 - для временного накопления записей для тезауруса используется
//              дисковый файл.
// 30.12.2008 - уже во время загрузки описания каждой связки делается попытка
//              разрешить ее - это понадобилось для импорта тэгов (переходность
//              и падежная валентность в глаголах).
// 14.01.2009 - поправлено чтение complex link: убираем апострофы, чтобы можно
//              было задавать многолексемые статьи.
// 06.02.2009 - поправлена генерация SQL операторов INSERT
// 02.03.2009 - добавление возможности помечать связи в тезаурусе различными
//              тэгами (например - тематика для переводов)
// 28.12.2009 - добавлена выгрузка в SQL дамп комплексных связей с тэгами.
// 07.02.2010 - расширение поддержки сложных связей - для многословных левых
//              частей заполняется специальная служебная таблица, позволяющая
//              быстро подставлять многословные замены.
// 01.03.2010 - при компиляции тезауруса - предотвращаем появление
//              дубликатов сложных связей.  
// 27.05.2010 - добавлена поддержка выгрузки в SQL с MS SQL BULK INSERT
// 16.08.2010 - добавлена таблица TLINK_FLAG - дополнительные параметры сложных
//              связей.
//
// 11.09.2010 - улучшен контроль за возникновением ошибок при операциях с SQLite
// 11.09.2010 - из-за проблем с предельной длиной строкового %s поля в sprintf
//              под Linux переделываю все вызовы lem::format_str на использование
//              MemFormatter.
// 07.11.2010 - полный рефакторинг для версии 9 - перевод на взаимодействие с
//              хранилищем тезауруса в БД через промежуточный слой абстракции.
// -----------------------------------------------------------------------------
//
// CD->02.10.2005
// LC->16.04.2018
// --------------

#include <lem/sqlite_helpers.h>
#include <lem/logfile.h>
#include <lem/system_config.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/ThesaurusTagDefs.h>
#include <lem/solarix/TagSets.h>
#include <lem/solarix/ThesaurusStorage.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/PhraseEntries.h>
#include <lem/solarix/WordLinkEnumerator.h>
#include <lem/solarix/PhraseLinkEnumerator.h>
#include <lem/solarix/PhraseLink.h>
#include <lem/solarix/ClassList.h>
#include <lem/solarix/PartOfSpeechEnumerator.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/WordEntryEnumerator.h>
#include <lem/solarix/SG_TagFilter.h>
#include <lem/solarix/ExactWordEntryLocator.h>
#include <lem/solarix/Thesaurus.h>

using namespace lem;
using namespace Solarix;


SG_Net::SG_Net(const Dictionary_Config &cfg)
{
    sg = nullptr;
    db = nullptr;
    do_delete_storage = false;

#if defined SOL_COMPILER
    lem::Path raw_file = lem::Path::GetTmpFilename();
    raw.reset( new BinaryWriter(raw_file) );
    raw_count = 0;
#endif

    tag_sets = new TagSets();
    tag_defs = new ThesaurusTagDefs();

    return;
}



SG_Net::~SG_Net(void)
{
    lem_rub_off(tag_sets);
    lem_rub_off(tag_defs);

    if (do_delete_storage)
        delete db;

    return;
}


void SG_Net::SetStorage(ThesaurusStorage *_db, bool _do_delete)
{
    LEM_CHECKIT_Z(_db != nullptr);

    if (do_delete_storage)
        delete db;

    do_delete_storage = _do_delete;
    db = _db;

    tag_sets->Connect(db);
    tag_defs->Connect(db);
    return;
}


// ************************************************************
// Сколько связок заданного типа зарегистрировано в тезаурусе.
// В расчет берутся связи между словами и между фразами.
// ************************************************************
int SG_Net::CountLinks(Tree_Link x) const
{
    if (db == nullptr)
    {
        return 0;
    }
    else
    {
        int count1 = db->CountWordLinks(x.GetState());
        int count2 = db->CountPhraseLinks(x.GetState());
        return count1 + count2;
    }
}


// Общее кол-во связей любых типов
int SG_Net::CountAllLinks(void) const
{
    if (db == nullptr)
    {
        return 0;
    }
    else
    {
        int count1 = db->CountWordLinks(ANY_STATE);
        int count2 = db->CountPhraseLinks(ANY_STATE);
        return count1 + count2;
    }
}


int SG_Net::AddWordLink(const SG_NetLink &lnk)
{
    return db->AddWordLink(lnk.GetEntryKey0(), lnk.GetEntryKey1(), lnk.GetLink().GetState(), lnk.GetTags());
}



#if defined SOL_COMPILER
std::pair<int/*ientry1*/, int/*itags*/> SG_Net::FindSingleLinked(int EntryKey0, const Tree_Link &Link) const
{
    auto it = raw_links2.find(std::make_pair(EntryKey0, Link));

    if (it != raw_links2.end())
    {
        auto key1 = it->second;
        return key1;
    }

    return std::make_pair(UNKNOWN, UNKNOWN);
}
#endif




#if defined SOL_CAA
void SG_Net::Find_Linked_Entries(
    int EntryKey0,
    const Tree_Link& ilink,
    IntCollect &res_list,
    const SG_TagFilter *filter
)
{
    std::unique_ptr<LS_ResultSet> rs(db->ListWordLinks(EntryKey0, ilink.GetState()));
    while (rs->Fetch())
    {
        if (filter != nullptr)
        {
            const int id_link = rs->GetInt(0);
            const int id_tags = rs->GetInt(2);
            SG_TagsList tags = GetWordLinkTags(id_tags, id_link);

            if (!filter->Match(tags))
                continue;
        }

        res_list.push_back(rs->GetInt(1));
    }

    return;
}
#endif

void SG_Net::Find_Linked_Entries(
    int EntryKey0,
    float depth,
    std::set<int> &list,
    bool incoming,
    bool outgoing,
    const lem::MCollect< Tree_Link > *allowed,
    const SG_TagFilter *filter
)
{
    const float w_deminish = 0.4F;

    if (outgoing)
    {
        // Исходящие связи, быстрый алгоритм.

        lem::MCollect<int> types;
        if (allowed != nullptr)
            for (lem::Container::size_type i = 0; i < allowed->size(); ++i)
                types.push_back(allowed->get(i).GetState());

        std::unique_ptr<LS_ResultSet> rs(db->ListWordLinks(EntryKey0, types));

        while (rs->Fetch())
        {
            const int ekey2 = rs->GetInt(1);

            if (list.find(ekey2) == list.end())
            {
                if (filter != nullptr)
                {
                    const int id_link = rs->GetInt(0);
                    const int id_tags = rs->GetInt(4);
                    SG_TagsList tags = GetWordLinkTags(id_tags, id_link);

                    if (!filter->Match(tags))
                        continue;
                }

                list.insert(ekey2);

                const int link_type = rs->GetInt(3);
                const int link_w = sg->coords()[I_NET].states()[link_type].GetWeight();

                float w2 = depth - link_w;
                if (w2 > 0)
                    Find_Linked_Entries(ekey2, w2 - w_deminish, list, incoming, outgoing);
            }
        }
    }

    if (incoming)
    {
        lem::MCollect<int> types;
        if (allowed != nullptr)
        {
            for (lem::Container::size_type i = 0; i < allowed->size(); ++i)
                types.push_back(allowed->get(i).GetState());
        }

        std::unique_ptr<LS_ResultSet> rs(db->ListWordLinks2(EntryKey0, types));

        while (rs->Fetch())
        {
            const int ekey1 = rs->GetInt(1);

            if (list.find(ekey1) == list.end())
            {
                if (filter != nullptr)
                {
                    const int id_link = rs->GetInt(0);
                    const int id_tags = rs->GetInt(4);
                    SG_TagsList tags = GetWordLinkTags(id_tags, id_link);

                    if (!filter->Match(tags))
                        continue;
                }

                list.insert(ekey1);

                const int link_type = rs->GetInt(3);
                const int link_w = sg->coords()[I_NET].states()[link_type].GetWeight();

                if (depth > 0)
                    Find_Linked_Entries(ekey1, depth - link_w - w_deminish, list, incoming, outgoing);
            }
        }
    }

    return;
}



#if defined SOL_CAA
// *************************************************************
// Обращение к SQL базе тезауруса
// *************************************************************
void SG_Net::Find_Linked_DbEntries(
    const UCString &word,
    const lem::MCollect< Solarix::Tree_Link >& links,
    lem::Collect<lem::UFString> &linked,
    const SG_TagFilter *filter
)
{
    const int id_phrase1 = sg->GetStorage().FindPhrase(word.c_str(), true);

    if (id_phrase1 != UNKNOWN)
    {
        lem::MCollect<int> itypes;
        for (lem::Container::size_type i = 0; i < links.size(); ++i)
            itypes.push_back(links[i].GetState());

        std::unique_ptr<LS_ResultSet> rs(db->ListPhraseLinks(id_phrase1, itypes));
        while (rs->Fetch())
        {
            const int id_phrase2 = rs->GetInt(1);
            if (filter != nullptr)
            {
                const int id_link = rs->GetInt(0);
                const int id_tags = rs->GetInt(4);
                SG_TagsList tags = GetWordLinkTags(id_tags, id_link);

                if (!filter->Match(tags))
                    continue;
            }

            SG_Phrase frz;
            sg->GetStorage().GetPhrase(id_phrase2, frz);
            linked.push_back(frz.GetText());
        }
    }

    return;
}
#endif


#if defined SOL_CAA
void SG_Net::Find_Linked_DbEntries(
    const UCString &word,
    lem::Collect<lem::UFString> &linked,
    const SG_TagFilter *filter
)
{
    lem::MCollect< Solarix::Tree_Link > links;
    Find_Linked_DbEntries(word, links, linked, filter);
    return;
}
#endif




#if defined SOL_COMPILER
void SG_Net::SaveThesaurusDb(const lem::Path &p)
{
    db->CopyDatabase(p);
    return;
}
#endif


#if defined SOL_CAA
int SG_Net::Find_Linked_Entry(int id_entry1, const Tree_Link& ilink, int id_entry2)
{
    return db->FindWordLink(id_entry1, id_entry2, ilink.GetState());
}
#endif


#if defined SOL_CAA
bool SG_Net::Is_Any_Linked(
    int EntryKey0,
    const Tree_Link& ilink,
    bool outgoing,
    bool incoming,
    const SG_TagFilter *filter
)
{
    if (outgoing)
    {
        std::unique_ptr<LS_ResultSet> rs(db->ListWordLinks(EntryKey0, ilink.GetState()));

        while (rs->Fetch())
        {
            if (filter != nullptr)
            {
                const int id_link = rs->GetInt(0);
                const int id_tags = rs->GetInt(2);
                SG_TagsList tags = GetWordLinkTags(id_tags, id_link);

                if (!filter->Match(tags))
                    continue;
            }

            return true;
        }
    }

    if (incoming)
    {
        std::unique_ptr<LS_ResultSet> rs(db->ListWordLinks2(EntryKey0, ilink.GetState()));

        while (rs->Fetch())
        {
            if (filter != nullptr)
            {
                const int id_link = rs->GetInt(0);
                const int id_tags = rs->GetInt(2);
                SG_TagsList tags = GetWordLinkTags(id_tags, id_link);

                if (!filter->Match(tags))
                    continue;
            }

            return true;
        }
    }

    return false;
}
#endif



#if defined SOL_COMPILER
// Загружаем описание связи между словарными статьями для тезауруса
void SG_Net::Load_Declaration(
    Macro_Parser &txt,
    const Binarization_Options &options
)
{
    BSourceState beg = txt.tellp();

    if (txt.probe(B_COMPLEX))
    {
        Load_Complex(txt, options);
        return;
    }

    UCString class0 = txt.read().string();
    txt.read_it(B_COLON);
    UCString entry0 = sol_read_multyname(sg->GetIO(), txt, B_OFIGPAREN);
    entry0.strip(L'"');
    entry0.trim();

    // Может быть задана дополнительная фильтрующая координата или информация об ударении
    Solarix::ExactWordEntryLocator locator;
    locator.LoadTxt(txt, *sg);

    if (!Load_Declaration(txt, class0, entry0, locator, options))
    {
        txt.seekp(beg);
        return;
    }

    return;
}


bool SG_Net::Load_Declaration(
    Macro_Parser &txt,
    const UCString &class0,
    const UCString &_entry0,
    const Solarix::ExactWordEntryLocator & locator0,
    const Binarization_Options &options
)
{
    Tree_Link l;
    l.LoadTxt(txt, *sg);

    const BethToken class1 = txt.read();

    if (class1.GetToken() == B_TREE)
        return false;

    txt.read_it(B_COLON);
    UCString _entry1 = sol_read_multyname(sg->GetIO(), txt, B_OFIGPAREN);
    _entry1.strip(L'"');
    _entry1.trim();

    // Может быть задана дополнительная фильтрующая координата или информация об ударении
    Solarix::ExactWordEntryLocator locator1;
    locator1.LoadTxt(txt, *sg);

    // Опционально - тэги на эту связь.
    int itags = LoadTags(txt, options);

    Lexem entry0(_entry0);
    sg->GetDict().GetLexAuto().TranslateLexem(entry0, true);

    Lexem entry1(_entry1);
    sg->GetDict().GetLexAuto().TranslateLexem(entry1, true);

    if (options.allow_links)
    {
        RawRecord record = lem::make_foursome(
            std::make_pair(to_upper(class0), UCString(entry0)),
            l,
            std::make_pair(to_upper(class1.string()), UCString(entry1)),
            itags
        );

        lem::zbool resolved;

        // Попробуем прямо сейчас разрешить связь
        const int ic0 = record.first.first == L"?" ? ANY_STATE : sg->FindClass(record.first.first);
        if (ic0 != UNKNOWN)
        {
            if (sg->IsOmonym(ic0, lem::to_upper(entry0)) && locator0.Empty())
            {
                Print_Error(txt);
                sg->GetIO().merr().printf("Omonym %us:%us requires the coordinate array\n", class0.c_str(), entry0.c_str());
                throw E_BaseException();
            }

            const int ie0 = locator0.Empty() ? sg->FindEntry(entry0, ic0, false) : sg->FindEntryOmonym(entry0, ic0, locator0);

            if (ie0 != UNKNOWN)
            {
                const int key0 = sg->GetEntry(ie0).GetKey();

                const int ic1 = record.third.first == L"?" ? ANY_STATE : sg->FindClass(record.third.first);
                if (ic1 != UNKNOWN)
                {
                    if (sg->IsOmonym(ic1, lem::to_upper(entry1)) && locator1.Empty())
                    {
                        Print_Error(txt);
                        sg->GetIO().merr().printf("Omonym %us:%us requires the coordinate array\n", class1.c_str(), entry1.c_str());
                        throw E_BaseException();
                    }

                    const int ie1 = locator1.Empty() ? sg->FindEntry(entry1, ic1, false) : sg->FindEntryOmonym(entry1, ic1, locator1);

                    if (ie1 != UNKNOWN)
                    {
                        const int key1 = sg->GetEntry(ie1).GetKey();

                        resolved = true;

                        // Итак, связь полностью готова.
                        raw_links2.insert(std::make_pair(std::make_pair(key0, l), std::make_pair(key1, itags)));

                        if (GetStorage().FindWordLink(key0, key1, l.GetState()) == UNKNOWN)
                        {
                            const int id_link = db->AddWordLink(key0, key1, l.GetState(), itags);

                            if (!sg->GetDict().GetCurrentOriginator().empty() && lem::LogFile::IsOpen())
                            {
                                lem::LogFile::logfile->printf(
                                    "ORIGINATOR::UPDATE sg_link SET modifier='%us' WHERE id=%d;\n",
                                    sg->GetDict().GetCurrentOriginator().c_str(), id_link
                                );
                            }
                        }
                    }
                }
            }
        }

        if (!resolved)
        {
            // Запоминаем информацию и связке во временном файле, добавлять в БД будем потом.
            raw->write(&record, sizeof(record));
            locator0.SaveBin(*raw);
            locator1.SaveBin(*raw);
            raw_count++;

            //if( raw_count>=3669 )
             //LEM_STOPIT;
        }
    }

    return true;
}


// *******************************************
// Загружаем определение связи между фразами
// *******************************************
void SG_Net::Load_Complex(
    Macro_Parser &txt,
    const Binarization_Options &options
)
{
    BSourceState beg = txt.tellp();
    SG_ComplexLink link;
    link.LoadTxt(txt, *sg);

    // загружаем список тегов в формате
    // tags { тег=значение тег=значение ... }
    const int id_tags = LoadTags(txt, options);
    link.tags = (*tag_sets)[id_tags];


    // опциональный список дополнительных флагов
    lem::PtrCollect<SG_LinkFlag> flags;

    if (txt.probe(B_FLAG))
    {
        txt.read_it(B_OFIGPAREN);
        while (!txt.eof())
        {
            if (txt.probe(B_CFIGPAREN))
                break;

            lem::UCString flag = txt.read().string();
            txt.read_it(B_EQUAL);
            lem::UCString value = txt.read().string();

            SG_LinkFlag *rec = new SG_LinkFlag(UNKNOWN, flag.c_str(), value.c_str());
            flags.push_back(rec);
        }
    }

    int id1 = sg->GetStorage().FindPhrase(link.GetEntry1(), true);
    const bool left_present = id1 != UNKNOWN;

    try
    {
        if (id1 == UNKNOWN)
        {
            // запоминаем левую часть
            SG_Phrase frz(link.GetEntry1(), UNKNOWN, UNKNOWN, UNKNOWN);
            id1 = sg->GetStorage().AddPhrase(frz);
        }
    }
    catch (...)
    {
        Print_Error(beg, txt);
        sg->GetIO().merr().printf("Could not insert new record for '%us' in TWORDS table\n", link.GetEntry1().c_str());
        throw;
    }


    int id2 = sg->GetStorage().FindPhrase(link.GetEntry2(), true);
    const bool right_present = id2 != UNKNOWN;

    try
    {
        if (id2 == UNKNOWN)
        {
            // запоминаем левую часть
            SG_Phrase frz(link.GetEntry2(), UNKNOWN, UNKNOWN, UNKNOWN);
            id2 = sg->GetStorage().AddPhrase(frz);
        }
    }
    catch (...)
    {
        Print_Error(beg, txt);
        sg->GetIO().merr().printf("Could not insert new record for '%us' in sg_tentry table\n", link.GetEntry2().c_str());
        throw;
    }


    // проверим, что такой связи еще нет.
    if (left_present && right_present)
    {
        // И левая и правая части уже были в лексиконе, и поэтому могут участвоватьв связях.
        const int id_old = db->FindPhraseLink(id1, id2, link.GetLink().GetState());
        if (id_old != UNKNOWN)
            return;
    }

    const int tl_id = db->AddPhraseLink(id1, id2, link.GetLink().GetState(), id_tags);

    // Сохраняем список флагов.
    for (lem::Container::size_type i = 0; i < flags.size(); ++i)
    {
        db->AddPhraseLinkFlag(tl_id, flags[i]->GetFlag().c_str(), flags[i]->GetValue().c_str());
    }

    if (!sg->GetDict().GetCurrentOriginator().empty() && lem::LogFile::IsOpen())
    {
        lem::LogFile::logfile->printf(
            "ORIGINATOR::UPDATE sg_tlink SET tl_modifier='%us' WHERE tl_id=%d;\n",
            sg->GetDict().GetCurrentOriginator().c_str(), tl_id
        );
    }

    // обновляем информацию для быстрого поиска фразы в тексте
   // const lem::UFString &left = link.GetEntry1();
   // sg->StoreCplxLeft( left );

    return;
}






int SG_Net::LoadTags(
    Macro_Parser &txt,
    const Binarization_Options &options
)
{
    int itags = 0; // 0 означает пустой набор тегов.

    if (txt.pick().GetToken() == B_TAGS)
    {
        lem::MCollect< std::pair<int, int> > link_tags;

        txt.read();
        txt.read_it(B_OFIGPAREN);

        // Список пар тэг[=значение]

        while (!txt.eof())
        {
            BethToken t_tag = txt.read();

            if (t_tag == B_CFIGPAREN)
                break;

            UCString tag_name = t_tag.string();
            tag_name.strip(L'"');

            const int itag = FindTag(tag_name);
            if (itag == UNKNOWN)
            {
                lem::Iridium::Print_Error(t_tag, txt);
                sg->GetIO().err->printf("Unknown tag [%us] is used in link definition", tag_name.c_str());
                throw E_ParserError();
            }

            UCString tag_value;
            int ivalue = UNKNOWN;
            if (txt.pick().GetToken() == B_EQUAL)
            {
                txt.read_it(B_EQUAL);
                BethToken t_val = txt.read();
                tag_value = t_val.string();
                tag_value.strip(L'"');

                ivalue = GetTagDefs()[itag][tag_value];
                if (ivalue == UNKNOWN)
                {
                    lem::Iridium::Print_Error(t_val, txt);
                    sg->GetIO().err->printf("Unknown tag [%us] value [%us] is used in link definition", tag_name.c_str(), tag_value.c_str());
                    throw E_ParserError();
                }
            }

            std::pair<int, int> tv(itag, ivalue);
            if (link_tags.find(tv) == UNKNOWN)
                link_tags.push_back(tv);
        }

        itags = tag_sets->Register(link_tags);
    }

    return itags;
}







// *****************************************
// Компиляция всех накопленных связок
// *****************************************
void SG_Net::Compile(void)
{
    const int dbg = 1;

    if (dbg > 0)
    {
        const int n = GetStorage().CountWordLinks(ANY_STATE);

        // Длительная операция: сообщаем пользователю.
        sg->GetIO().mecho().printf("%vfEThesaurus%vn: %d stored, %d pending ...", n, raw_count);
        sg->GetIO().mecho().flush();
    }

    // Для ускорения поиска имен классов соберем их в std::map
    std::map< lem::UCString, int > fast_class;
    std::unique_ptr<Solarix::PartOfSpeechEnumerator> cenum((PartOfSpeechEnumerator*)sg->classes().Enumerate());
    while (cenum->Fetch())
    {
        const int id_class = cenum->GetId();
        const GramClass &cls = cenum->GetItem();

        fast_class.insert(std::make_pair(to_upper(cls.GetName()), id_class));

        for (lem::Container::size_type j = 0; j < cls.GetAliases().size(); ++j)
        {
            fast_class.insert(std::make_pair(to_upper(cls.GetAliases()[j]), id_class));
        }
    }

    fast_class.insert(std::make_pair(UCString(L"?"), ANY_STATE));

    // Аналогичную операцию - для имен словарных статей.
    std::multimap< lem::UCString, std::pair<int /*ientry*/, int/*iclass*/> > fast_entry;
    std::unique_ptr<WordEntryEnumerator> wenum(sg->GetEntries().ListEntries());
    while (wenum->Fetch())
    {
        const SG_Entry &entry = wenum->GetItem();
        fast_entry.insert(std::make_pair((const UCString&)entry.GetName(), std::make_pair(entry.GetKey(), entry.GetClass())));
    }
    wenum.reset();

    // Для ускорения проверки уникальности будем параллельно вести в памяти
    // список с быстрым поиском
    std::set<SG_NetLink> links_set;

    int added = 0, rejected = 0;

    raw->reopen(true, false);

    RawRecord r;

    for (int i2 = 0; i2 < raw_count; i2++)
    {
        raw->read(&r, sizeof(r));

        const UCString &class0 = r.first.first;
        const UCString &entry0 = r.first.second;

        const UCString &class1 = r.third.first;
        const UCString &entry1 = r.third.second;

        ExactWordEntryLocator locator0, locator1;
        locator0.LoadBin(*raw);
        locator1.LoadBin(*raw);

        const int tags = r.fourth;

        std::map< lem::UCString, int >::const_iterator itc = fast_class.find(class0);
        if (itc == fast_class.end())
        {
            sg->GetIO().merr().printf(
                "The class [%us] is not previously declared in grammar\n"
                , class0.c_str()
            );
            throw E_ParserError();
        }

        int iclass0 = itc->second;

        int ientry0 = UNKNOWN;

        if (locator0.Empty())
        {
            std::pair<std::multimap< lem::UCString, std::pair<int, int> >::const_iterator,
                std::multimap< lem::UCString, std::pair<int, int> >::const_iterator > ite = fast_entry.equal_range(entry0);

            for (std::multimap< lem::UCString, std::pair<int, int> >::const_iterator ii1 = ite.first; ii1 != ite.second; ii1++)
                if (iclass0 == ANY_STATE || ii1->second.second == iclass0)
                {
                    ientry0 = ii1->second.first;
                    break;
                }
        }
        else
        {
            ientry0 = sg->FindEntryOmonym(entry0, iclass0, locator0);
        }

        if (ientry0 == UNKNOWN)
        {
            if (lem::LogFile::IsOpen())
                lem::LogFile::logfile->printf("Warning: link from undeclared entry %us:%us", class0.c_str(), entry0.c_str());

            locator0.pairs.SaveTxt(*lem::LogFile::logfile, *sg);
            lem::LogFile::logfile->eol();

            rejected++;
            continue;
        }

        // ***********************

        itc = fast_class.find(class1);
        if (itc == fast_class.end())
        {
            sg->GetIO().merr().printf(
                "The class [%us] is not previously declared in grammar\n"
                , class1.c_str()
            );
            throw E_ParserError();
        }

        int iclass1 = itc->second;

        int ientry1 = UNKNOWN;

        if (locator1.Empty())
        {
            std::pair<std::multimap< lem::UCString, std::pair<int, int> >::const_iterator,
                std::multimap< lem::UCString, std::pair<int, int> >::const_iterator > ite = fast_entry.equal_range(entry1);

            for (std::multimap< lem::UCString, std::pair<int, int> >::const_iterator ii2 = ite.first; ii2 != ite.second; ii2++)
                if (iclass1 == ANY_STATE || ii2->second.second == iclass1)
                {
                    ientry1 = ii2->second.first;
                    break;
                }
        }
        else
        {
            ientry1 = sg->FindEntryOmonym(entry1, iclass1, locator1);
        }

        if (ientry1 == UNKNOWN)
        {
            if (lem::LogFile::IsOpen())
                lem::LogFile::logfile->printf("Warning: link to undeclared entry %us:%us", class1.c_str(), entry1.c_str());

            locator1.pairs.SaveTxt(*lem::LogFile::logfile, *sg);
            lem::LogFile::logfile->eol();

            rejected++;
            continue;
        }

        const int ekey0 = ientry0;
        const int ekey1 = ientry1;
        SG_NetLink new_link(ekey0, ekey1, r.second, tags);

        if (links_set.find(new_link) == links_set.end())
        {
            links_set.insert(new_link);

            if (GetStorage().FindWordLink(ekey0, ekey1, new_link.GetLink().GetState()) == UNKNOWN)
            {
                db->AddWordLink(new_link.GetEntryKey0(), new_link.GetEntryKey1(), new_link.GetLink().GetState(), tags);
                added++;
            }
            else
            {
                rejected++;
            }
        }
        else
        {
            rejected++;
        }
    }

    lem::Path tmp_filename(raw->GetName());
    raw.reset();
    tmp_filename.DoRemove();

    // Добавлены сложные связки?
    const int phrase_links = db->CountPhraseLinks(ANY_STATE);

    if (dbg > 0)
    {
        sg->GetIO().mecho().printf("%vfE%d%vn rejected, %vfE%d%vn added, %vfE%d%vn phrase links\n", rejected, added, phrase_links);
        sg->GetIO().mecho().flush();
    }

    return;
}

#endif


SG_TagsList SG_Net::GetWordLinkTags(int id_link)
{
    LEM_CHECKIT_Z(id_link != UNKNOWN);

    lem::MCollect< std::pair<int, int> > atomized_tags;
    const int id_tags = db->GetWordLinkTags(id_link, atomized_tags);
    if (id_tags != UNKNOWN)
    {
        return (*tag_sets)[id_tags];
    }

    if (atomized_tags.empty())
        return nullptr;

    int id_tags2 = tag_sets->Register(atomized_tags);
    return (*tag_sets)[id_tags];
}


SG_TagsList SG_Net::GetPhraseLinkTags(int id_link)
{
    LEM_CHECKIT_Z(id_link != UNKNOWN);

    lem::MCollect< std::pair<int, int> > atomized_tags;
    const int id_tags = db->GetPhraseLinkTags(id_link, atomized_tags);
    if (id_tags != UNKNOWN)
    {
        return (*tag_sets)[id_tags];
    }

    if (atomized_tags.empty())
        return nullptr;

    int id_tags2 = tag_sets->Register(atomized_tags);
    return (*tag_sets)[id_tags];
}




SG_TagsList SG_Net::GetWordLinkTags(int id_tags, int id_link)
{
    LEM_CHECKIT_Z(id_link != UNKNOWN);

    if (id_tags != UNKNOWN)
    {
        return (*tag_sets)[id_tags];
    }

    lem::MCollect< std::pair<int, int> > atomized_tags;
    db->GetWordLinkTags(id_link, atomized_tags);

    if (atomized_tags.empty())
        return nullptr;

    int id_tags2 = tag_sets->Register(atomized_tags);
    return (*tag_sets)[id_tags];
}


SG_TagsList SG_Net::GetPhraseLinkTags(int id_tags, int id_link)
{
    LEM_CHECKIT_Z(id_link != UNKNOWN);

    if (id_tags != UNKNOWN)
    {
        return (*tag_sets)[id_tags];
    }

    lem::MCollect< std::pair<int, int> > atomized_tags;
    db->GetPhraseLinkTags(id_link, atomized_tags);

    if (atomized_tags.empty())
        return nullptr;

    int id_tags2 = tag_sets->Register(atomized_tags);
    return (*tag_sets)[id_tags];
}



#if defined SOL_CAA
std::unique_ptr<SG_ComplexLink> SG_Net::GetComplexLink(int id_link)
{
    LEM_CHECKIT_Z(id_link >= 0);

    PhraseLink info;
    if (db->GetPhraseLink(id_link, info))
    {
        SG_Phrase frz1, frz2;
        sg->GetStorage().GetPhrase(info.id_entry1, frz1);
        sg->GetStorage().GetPhrase(info.id_entry2, frz2);

        SG_ComplexLink *lnk = new SG_ComplexLink;
        lnk->entry1 = frz1.GetText();
        lnk->entry2 = frz1.GetText();
        lnk->link = Tree_Link(info.link_type, I_NET);
        lnk->tags = GetPhraseLinkTags(info.id_tags, info.id);

        return std::unique_ptr<SG_ComplexLink>(lnk);
    }
    else
    {
        return std::unique_ptr<SG_ComplexLink>();
    }
}
#endif








#if defined SOL_COMPILER
void SG_Net::LoadTxt(
    Macro_Parser &txt,
    const Binarization_Options &options
)
{
    txt.read_it(B_OFIGPAREN);

    bool load = true;
    while (load && !txt.eof())
    {
        BethToken t = txt.read();
        switch (t.GetToken())
        {
        case B_TAG:
        {
            GetTagDefs().LoadTxt(txt, sg->GetIO(), options);
            break;
        }

        case B_CFIGPAREN:
        {
            load = false;
            break;
        }

        default:
        {
            lem::Iridium::Print_Error(t, txt);
            sg->GetDict().GetIO().err->printf("Invalid token [%vfC%us%vn] in thesaurus section\n", t.string().c_str());
            break;
        }
        }
    }

    return;
}
#endif


int SG_Net::FindTag(const lem::UCString &tag_name) const
{
    return tag_defs->Find(tag_name);
}


int SG_Net::FindTagValue(int TagID, const lem::UCString &tag_value) const
{
    LEM_CHECKIT_Z(!tag_value.empty());
    LEM_CHECKIT_Z(TagID != UNKNOWN);

    return (*tag_defs)[TagID][tag_value];
}


std::pair<int, int> SG_Net::FindTagValue(const lem::UCString &tag_name, const lem::UCString &tag_value) const
{
    LEM_CHECKIT_Z(!tag_name.empty());
    LEM_CHECKIT_Z(!tag_value.empty());

    std::pair<int, int> ret(-1, -1);

    const int id_tag = tag_defs->Find(tag_name);
    if (id_tag != UNKNOWN)
    {
        ret.first = id_tag;
        ret.second = (*tag_defs)[id_tag][tag_value];
    }

    return ret;
}



std::unique_ptr<SG_TagFilter> SG_Net::CompileTags(const lem::Collect< std::pair<UCString, UCString> > &stags) const
{
    lem::MCollect< std::pair<int, int> > itags; itags.reserve(stags.size());

    for (lem::Container::size_type i = 0; i < stags.size(); ++i)
    {
        const int itag = FindTag(stags[i].first);
        if (itag == UNKNOWN)
            throw E_BaseException(lem::format_str(L"Unknown tag '%s'", stags[i].first.c_str()).c_str());

        int ivalue = UNKNOWN;

        if ((*tag_defs)[itag].CountValues() > 0 || !stags[i].second.empty())
        {
            ivalue = (*tag_defs)[itag][stags[i].second];
            if (ivalue == UNKNOWN)
                throw E_BaseException(lem::format_str(L"Unknown value '%s' for tag '%s'", stags[i].second.c_str(), stags[i].first.c_str()).c_str());
        }

        itags.push_back(std::make_pair(itag, ivalue));
    }

    std::unique_ptr<SG_TagFilter> ret((SG_TagFilter*)new SG_RefTagFilter(itags, false));
    return ret;
}





void SG_Net::BeginTx(void)
{
    db->BeginTx();
    return;
}

void SG_Net::CommitTx(void)
{
    db->CommitTx();
    return;
}


#if defined SOL_CAA
// ********************************************************************************
// Ищем все фразовые статьи, связанные с левой tentry_id по связи типа link_type,
// с возможным учетом фильтра тегов.
// ********************************************************************************
void SG_Net::Find_Linked_DbEntries(
    int tentry_id,
    int link_type,
    lem::MCollect<int> & linked_te_id,
    const SG_TagFilter *filter
)
{
    std::unique_ptr<LS_ResultSet> rs(db->ListPhraseLinks(tentry_id, link_type));
    while (rs->Fetch())
    {
        const int id_link = rs->GetInt(0);
        const int id_tags = rs->GetInt(2);
        if (filter != nullptr)
        {
            SG_TagsList tags = GetPhraseLinkTags(id_tags, id_link);

            if (!filter->Match(tags))
                continue;
        }

        const int id_phrase2 = rs->GetInt(1);
        linked_te_id.push_back(id_phrase2);
    }

    return;
}
#endif



#if defined SOL_CAA
// ********************************************************************************
// Ищем все фразовые статьи, связанные с левой tentry_id по связи типа link_type.
// Заполняется список первичных ключей найденных записей самих связей, а также
// id правых фраз.
// ********************************************************************************
void SG_Net::FindComplexLinks(
    int tentry_id,
    int link_type,
    lem::MCollect<int> &tl_id,
    lem::MCollect<int> &te_id,
    const SG_TagFilter *filter
)
{
    tl_id.clear();
    te_id.clear();

    std::unique_ptr<LS_ResultSet> rs(db->ListPhraseLinks(tentry_id, link_type));
    while (rs->Fetch())
    {
        const int id_link = rs->GetInt(0);
        const int id_tags = rs->GetInt(2);
        if (filter != nullptr)
        {
            SG_TagsList tags = GetPhraseLinkTags(id_tags, id_link);

            if (!filter->Match(tags))
                continue;
        }

        tl_id.push_back(id_link);
        const int id_phrase2 = rs->GetInt(1);
        te_id.push_back(id_phrase2);
    }

    return;
}
#endif







void SG_Net::RemoveComplexLink(int LinkID)
{
    db->DeletePhraseLink(LinkID);
    return;
}


void SG_Net::RemoveWordsLink(int LinkID)
{
    db->DeleteWordLink(LinkID);
    return;
}


int SG_Net::AddWordsLink(int ie0, int link_type, int ie1, SG_TagsList tags)
{
    if (ie0 == UNKNOWN || link_type == UNKNOWN || ie1 == UNKNOWN)
        return UNKNOWN;

    const int ekey0 = sg->GetEntry(ie0).GetKey();
    const int ekey1 = sg->GetEntry(ie1).GetKey();
    const int id_tag_set = (*tag_sets)[tags];
    const int id = db->AddWordLink(ekey0, ekey1, link_type, id_tag_set);

    return id;
}


int SG_Net::AddWordsLink(int ie0, int link_type, int ie1, int tags)
{
    if (ie0 == UNKNOWN || link_type == UNKNOWN || ie1 == UNKNOWN)
        return UNKNOWN;

    const int ekey0 = sg->GetEntry(ie0).GetKey();
    const int ekey1 = sg->GetEntry(ie1).GetKey();
    const int id = db->AddWordLink(ekey0, ekey1, link_type, tags);

    return id;
}


int SG_Net::AddComplexLink(int id1, int link_type, int id2, SG_TagsList tags)
{
    if (id1 == UNKNOWN || link_type == UNKNOWN || id2 == UNKNOWN)
        return UNKNOWN;

    const int id_tag_set = (*tag_sets)[tags];
    const int id = db->AddPhraseLink(id1, id2, link_type, id_tag_set);

    return id;
}


int SG_Net::AddComplexLink(int id1, int link_type, int id2, int tags)
{
    if (id1 == UNKNOWN || link_type == UNKNOWN || id2 == UNKNOWN)
        return UNKNOWN;

    const int id = db->AddPhraseLink(id1, id2, link_type, tags);

    return id;
}


void SG_Net::SetLinkTags(int id_link, Solarix::SG_TagsList tags)
{
    const int id_tag_set = (*tag_sets)[tags];
    db->SetWordLinkTags(id_link, id_tag_set);
    return;
}


void SG_Net::SetLinkTags(int id_link, int id_tags)
{
    db->SetWordLinkTags(id_link, id_tags);
    return;
}


void SG_Net::SetComplexLinkTags(int id_link, Solarix::SG_TagsList tags)
{
    const int id_tag_set = (*tag_sets)[tags];
    db->SetPhraseLinkTags(id_link, id_tag_set);
    return;
}

void SG_Net::SetComplexLinkTags(int id_link, int id_tags)
{
    db->SetPhraseLinkTags(id_link, id_tags);
    return;
}


// Возвращается ID для записи в справочнике тегов.
int SG_Net::LoadTags(const lem::UFString &str_tags)
{
    lem::MCollect< std::pair<lem::UCString, UCString> > toks;

    lem::Collect<lem::UFString> toks2;
    lem::parse(str_tags, toks2, L" ");

    lem::Collect<UFString> toks1;

    lem::Collect< std::pair<UCString, UCString> > stags;

    for (lem::Container::size_type i = 0; i < toks2.size(); ++i)
    {
        const lem::UFString &tok2 = toks2[i];

        toks1.clear();
        lem::parse(tok2, toks1, L"=");

        LEM_CHECKIT_Z(toks1.size() == 2);

        if (toks1.size() == 2)
        {
            UCString tag_name(toks1[0].c_str());
            UCString tag_value(toks1[1].c_str());

            stags.push_back(std::make_pair(tag_name, tag_value));
        }
    }


    lem::MCollect< std::pair<int, int> > itags;
    itags.reserve(stags.size());

    for (lem::Container::size_type i = 0; i < stags.size(); ++i)
    {
        const int itag = FindTag(stags[i].first);
        if (itag == UNKNOWN)
            throw E_BaseException(lem::format_str(L"Unknown tag '%s'", stags[i].first.c_str()).c_str());

        int ivalue = UNKNOWN;

        if ((*tag_defs)[itag].CountValues() > 0 || !stags[i].second.empty())
        {
            ivalue = (*tag_defs)[itag][stags[i].second];
            if (ivalue == UNKNOWN)
                throw E_BaseException(lem::format_str(L"Unknown value '%s' for tag '%s'", stags[i].second.c_str(), stags[i].first.c_str()).c_str());
        }

        itags.push_back(std::make_pair(itag, ivalue));
    }

    int id_set = tag_sets->Register(itags);
    return id_set;
}



// ******************************************************************
// Extract the list of all flags associated with a complex link
// ******************************************************************
void SG_Net::GetLinkFlags(int tl_id, lem::PtrCollect<SG_LinkFlag> & list) const
{
    db->GetPhraseFlags(tl_id, list);
    return;
}


void SG_Net::StoreLinkFlag(int tl_id, SG_LinkFlag &flag)
{
    int tlf_id = db->AddPhraseLinkFlag(tl_id, flag.GetFlag().c_str(), flag.GetValue().c_str());
    flag.tlf_id = tlf_id;
    return;
}


void SG_Net::ClearLinkFlags(int tl_id)
{
    db->ClearPhraseLinkFlags(tl_id);
    return;
}






#if defined SOL_REPORT
void SG_Net::Save_SQL(OFormatter &out, const SQL_Production &sql_version, int min_entry_freq)
{
    if (sql_version.type == SQL_Production::MsSql)
    {
        out.printf("!! @echo Loading thesaurus ...\n");
    }

    const wchar_t* Nprefix = sql_version.GetNPrefix();

    out.printf("%s\n", sql_version.BeginTx().c_str());

    std::unique_ptr<ThesaurusTagDefsEnumerator> tags_enum(tag_defs->Enumerate());
    while (tags_enum->Fetch())
    {
        const int id_tag = tags_enum->GetId();
        const ThesaurusTag &t = (*tag_defs)[id_tag];
        t.Save_SQL(out, sql_version);
    }
    tags_enum.reset();
    out.printf("%s\n", sql_version.CommitTx().c_str());


    // -----------------------------------------------------------------

    out.printf("%s\n", sql_version.BeginTx().c_str());


    int seq = 1;

    const int rows_per_insert2 = sql_version.internal_commit_period;

    std::unique_ptr<OFormatter> sg_link16, sg_link_tag16;

    lem::Path path_links(sql_version.outdir);
    lem::Path path_link_tags(sql_version.outdir);

    if (sql_version.type == SQL_Production::Oracle)
    {
        path_links.ConcateLeaf(L"sg_link.ctl");
        path_link_tags.ConcateLeaf(L"sg_link_tag.ctl");
    }
    else
    {
        path_links.ConcateLeaf(L"sg_link.txt");
        path_link_tags.ConcateLeaf(L"sg_link_tag.txt");
    }

    bool external_data = false;

    if (sql_version.mssql_bulk_insert)
    {
        external_data = true;
        sg_link16.reset(new U16Formatter(path_links, true));
        sg_link_tag16.reset(new U16Formatter(path_link_tags, true));
    }
    else if (sql_version.loader && sql_version.IsUtf8())
    {
        external_data = true;
        sg_link16.reset(new OUFormatter(path_links, false));
        sg_link_tag16.reset(new OUFormatter(path_link_tags, false));
    }
    else if (sql_version.loader && sql_version.IsAscii())
    {
        external_data = true;
        sg_link16.reset(new OFormatter(path_links));
        sg_link_tag16.reset(new OFormatter(path_link_tags));
    }

    if (sql_version.type == SQL_Production::Oracle)
    {
        sg_link16->printf(
            "OPTIONS (ROWS=10000,BINDSIZE=10000000,STREAMSIZE=10000000,READSIZE=10000000)\n"
            "LOAD DATA\n"
            "INFILE *\n"
            "TRUNCATE\n"
            "INTO TABLE sg_link\n"
            "FIELDS TERMINATED BY '#' ( id, id_entry1, id_entry2, icoord, istate, tags )\n"
            "BEGINDATA\n"
        );

        sg_link_tag16->printf(
            "OPTIONS (ROWS=10000,BINDSIZE=10000000,STREAMSIZE=10000000,READSIZE=10000000)\n"
            "LOAD DATA\n"
            "INFILE *\n"
            "TRUNCATE\n"
            "INTO TABLE sg_link_tag\n"
            "FIELDS TERMINATED BY '#' ( id, id_link, id_tag, ivalue )\n"
            "BEGINDATA\n"
        );
    }

    out.printf("%s\n", sql_version.CommitTx().c_str());


    int max__sg_link_id = 0;
    int max__link_tag_id = 0;
    int max__sg_tlink_id = 0;
    int max__sg_tlink_tag_id = 0;
    int max__sg_tlink_flag_id = 0;
    int max__tag_set_id = 0;

    // --- TAG_SET ---

    out.printf("%s\n", sql_version.BeginTx().c_str());

    if (sql_version.type == SQL_Production::MsSql)
    {
        out.printf(
            "SET IDENTITY_INSERT tag_set ON\n"
            "GO\n"
        );
    }

    std::unique_ptr<LS_ResultSet> tsenum(GetStorage().List_TagSets());
    lem::UFString tags;
    while (tsenum->Fetch())
    {
        const int id = tsenum->GetInt(0);
        if (id != UNKNOWN)
        {
            tags.clear();
            GetStorage().GetTagSet(id, tags);

            out.printf("INSERT INTO tag_set( id, tags ) VALUES ( %d, '%us' );\n", id, tags.c_str());

            max__tag_set_id = std::max(id, max__tag_set_id);
        }
    }


    if (sql_version.type == SQL_Production::MsSql)
    {
        out.printf(
            "SET IDENTITY_INSERT tag_set OFF\n"
            "GO\n"
        );
    }

    out.printf("%s\n", sql_version.CommitTx().c_str());

    // ----------------------------------------------------------------

    std::unique_ptr<WordLinkEnumerator> word_links(EnumerateWordLinks());

    out.printf("%s\n", sql_version.BeginTx().c_str());

    int i = 0;
    while (word_links->Fetch())
    {
        i++;

        const int ekey1 = word_links->GetEntryKey1();
        const int ekey2 = word_links->GetEntryKey2();

        const Solarix::SG_Entry &e1 = sg->GetEntry(ekey1);
        const Solarix::SG_Entry &e2 = sg->GetEntry(ekey2);

        if (sql_version.IsDemo())
        {
            // При генерации демо-скрипта отфильтруем связи только между
            // выгружаемыми статьями, чтобы можно было корректно создать FK в таблице SG_LINK
            if (!sql_version.MatchEntryName(e1.GetName()))
                continue;

            if (!sql_version.MatchEntryName(e2.GetName()))
                continue;

            if (e1.GetFreq() < min_entry_freq || e2.GetFreq() < min_entry_freq)
                continue;
        }

        // Специальные статьи не должны попасть в SQL выгрузку
        if (e1.IsNonterminal() || e1.IsSilent() || e1.IsQuantor() || e1.IsNoExport())
            continue;

        if (e2.IsNonterminal() || e2.IsSilent() || e2.IsQuantor() || e2.IsNoExport())
            continue;

        const int id_link = word_links->GetLinkId();
        const int link_type = word_links->GetLinkType();
        const int id_tags = word_links->GetTagsId();

        max__sg_link_id = std::max(max__sg_link_id, id_link);

        if (external_data)
        {
            sg_link16->printf(
                "%d#%d#%d#%d#%d#%d\n"
                , id_link
                , ekey1
                , ekey2
                , 0
                , link_type
                , id_tags
            );
        }
        else
        {
            if (i && !(i%rows_per_insert2))
                out.printf("%s\n", sql_version.InternalCommit().c_str());

            out.printf(
                "INSERT INTO sg_link( id, id_entry1, id_entry2, icoord, istate, tags ) VALUES( %d, %d, %d, %d, %d, %d );\n"
                , id_link
                , ekey1
                , ekey2
                , 0
                , link_type
                , id_tags
            );
        }

        SG_TagsList t = GetWordLinkTags(id_tags, id_link);
        if (t != nullptr && !t->empty())
        {
            for (lem::Container::size_type k = 0; k < t->size(); ++k)
            {
                max__link_tag_id = std::max(max__link_tag_id, seq);

                if (external_data)
                {
                    sg_link_tag16->printf("%d#%d#%d#%d\n", seq++, id_link, t->get(k).first, t->get(k).second);
                }
                else
                {
                    out.printf("INSERT INTO sg_link_tag( id, id_link, id_tag, ivalue ) VALUES ( %d, %d, %d, %d );\n",
                        seq++, id_link, t->get(k).first, t->get(k).second);
                }
            }
        }
    }

    word_links.reset();
    out.printf("%s\n", sql_version.CommitTx().c_str());

    // ---------------------------------------------------------

    out.printf("%s\n", sql_version.BeginTx().c_str());


    lem::FString line_terminator = lem::System_Config::GetLineTerminator(true).c_str();

    if (sql_version.type == SQL_Production::MsSql && sql_version.mssql_bulk_insert)
    {
        out.printf("!! @echo Loading SG_LINK ...\n");

        out.printf(
            "SET IDENTITY_INSERT sg_link ON\n"
            "GO\n"
            "BULK INSERT sg_link FROM '%us' WITH ( FIELDTERMINATOR='#', DATAFILETYPE='widechar', KEEPIDENTITY )\n"
            "GO\n"
            "SET IDENTITY_INSERT sg_link OFF\n"
            "GO\n"
            , path_links.GetUnicode().c_str()
        );

        out.printf("%s\n", sql_version.CommitTx().c_str());

        out.printf("!! @echo Loading SG_LINK_TAG ...\n");
        out.printf("%s\n", sql_version.BeginTx().c_str());
        out.printf(
            "SET IDENTITY_INSERT sg_link_tag ON\n"
            "GO\n"
            "BULK INSERT sg_link_tag FROM '%us' WITH ( FIELDTERMINATOR='#', DATAFILETYPE='widechar', KEEPIDENTITY )\n"
            "GO\n"
            "SET IDENTITY_INSERT sg_link_tag OFF\n"
            "GO\n"
            , path_link_tags.GetUnicode().c_str());
    }
    else if (sql_version.loader && sql_version.type == SQL_Production::MySql)
    {
        out.printf("%us '%us' INTO TABLE sg_link CHARACTER SET utf8 FIELDS TERMINATED BY '#' LINES TERMINATED BY '%s' (id,id_entry1,id_entry2,icoord,istate,tags);\n"
            , sql_version.GetLoadInfileText(), path_links.GetAbsolutePath().GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());

        out.printf("%us '%us' INTO TABLE sg_link_tag CHARACTER SET utf8 FIELDS TERMINATED BY '#' LINES TERMINATED BY '%s' (id,id_link,id_tag,ivalue);\n"
            , sql_version.GetLoadInfileText(), path_link_tags.GetAbsolutePath().GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());
    }
    else if (sql_version.loader && sql_version.type == SQL_Production::Postgres)
    {
        //out.printf("%us sg_entry(id,name,uname,id_class,freq,exportable,flags,dic_div) FROM '%us' WITH DELIMITER '#' NULL ''\n"
            //, sql_version.GetLoadInfileText(), path_entries.GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());

        out.printf("%us sg_link(id,id_entry1,id_entry2,icoord,istate,tags) FROM '%us' WITH DELIMITER '#' NULL ''\n"
            , sql_version.GetLoadInfileText(), path_links.GetAbsolutePath().GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());

        out.printf("%us sg_link_tag(id,id_link,id_tag,ivalue) FROM '%us' WITH DELIMITER '#' NULL ''\n"
            , sql_version.GetLoadInfileText(), path_link_tags.GetAbsolutePath().GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());
    }


    out.printf("%s\n", sql_version.CommitTx().c_str());

    // ---------------------------------------------------------------

    out.printf("%s\n", sql_version.BeginTx().c_str());

    // Выгружаем сложные связи

    int seq2 = 1;

    for (int sql_pass = 0; sql_pass < 3; sql_pass++)
    {
        if (sql_version.type == SQL_Production::MsSql && sql_version.mssql_bulk_insert)
        {
            switch (sql_pass)
            {
            case 0: out.printf("SET IDENTITY_INSERT sg_tlink ON\nGO\n"); break;
            case 1: out.printf("SET IDENTITY_INSERT sg_tlink_tag ON\nGO\n"); break;
            case 2: out.printf("SET IDENTITY_INSERT sg_tlink_flag ON\nGO\n"); break;
            }
        }

        std::unique_ptr<LS_ResultSet> phrase_links(db->ListPhraseLinks());

        lem::PtrCollect<SG_LinkFlag> flags;
        while (phrase_links->Fetch())
        {
            int tl_id = phrase_links->GetInt(0);
            int id1 = phrase_links->GetInt(1);
            int id2 = phrase_links->GetInt(2);
            int link_id = phrase_links->GetInt(4);
            int itags = phrase_links->GetInt(5);

            SG_TagsList tags = GetPhraseLinkTags(itags, tl_id);

            if (i && !(i%rows_per_insert2))
                out.printf("%s\n", sql_version.InternalCommit().c_str());

            if (sql_pass == 0)
            {
                max__sg_tlink_id = std::max(max__sg_tlink_id, tl_id);
                out.printf("INSERT INTO sg_tlink( tl_id, tl_te_id1, tl_te_id2, tl_icoord, tl_istate, tl_tags ) VALUES ( %d, %d, %d, %d, %d, %d );\n",
                    tl_id, id1, id2, 0, link_id, itags);
            }

            if (sql_pass == 1)
            {
                if (tags != nullptr && !tags->empty())
                {
                    for (lem::Container::size_type k = 0; k < tags->size(); ++k)
                    {
                        max__sg_tlink_tag_id = std::max(max__sg_tlink_tag_id, seq2);
                        out.printf("INSERT INTO sg_tlink_tag( tlt_id, tlt_tl_id, tlt_id_tag, tlt_ivalue ) VALUES ( %d, %d, %d, %d );\n",
                            seq2++, tl_id, tags->get(k).first, tags->get(k).second);
                    }
                }
            }

            if (sql_pass == 2)
            {
                flags.clear();
                GetLinkFlags(tl_id, flags);

                for (lem::Container::size_type j = 0; j < flags.size(); ++j)
                {
                    max__sg_tlink_flag_id = std::max(max__sg_tlink_flag_id, flags[j]->GetId());
                    out.printf("INSERT INTO sg_tlink_flag( tlf_id, tlf_tl_id, tlf_flag, tlf_value ) VALUES ( %d, %d, %us'%us', %us'%us' );\n",
                        flags[j]->GetId(),
                        tl_id,
                        Nprefix,
                        flags[j]->GetFlag().c_str(),
                        Nprefix,
                        flags[j]->GetValue().c_str()
                    );
                }
            }
        }

        if (sql_version.type == SQL_Production::MsSql && sql_version.mssql_bulk_insert)
        {
            switch (sql_pass)
            {
            case 0: out.printf("SET IDENTITY_INSERT sg_tlink OFF\nGO\n"); break;
            case 1: out.printf("SET IDENTITY_INSERT sg_tlink_tag OFF\nGO\n"); break;
            case 2: out.printf("SET IDENTITY_INSERT sg_tlink_flag OFF\nGO\n"); break;
            }
        }
    }

    out.printf("%s\n", sql_version.CommitTx().c_str());

    // ----------------------------------------------------------------

    out.printf("%s\n", sql_version.BeginTx().c_str());

    if (sql_version.type == SQL_Production::FireBird)
    {
        out.printf(
            "CREATE SEQUENCE g_sg_link;\n"
            "ALTER SEQUENCE g_sg_link RESTART WITH %ud;\n"
            , max__sg_link_id + 1
        );

        out.printf(
            "CREATE SEQUENCE g_sg_link_tag;\n"
            "ALTER SEQUENCE g_sg_link_tag RESTART WITH %ud;\n"
            , max__link_tag_id + 1
        );


        out.printf(
            "CREATE SEQUENCE g_sg_tlink;\n"
            "ALTER SEQUENCE g_sg_tlink RESTART WITH %ud;\n"
            , max__sg_tlink_id + 1
        );

        out.printf(
            "CREATE SEQUENCE g_sg_tlink_tag;\n"
            "ALTER SEQUENCE g_sg_tlink_tag RESTART WITH %ud;\n"
            , max__sg_tlink_tag_id + 1
        );

        out.printf(
            "CREATE SEQUENCE g_sg_tlink_flag;\n"
            "ALTER SEQUENCE g_sg_tlink_flag RESTART WITH %ud;\n"
            , max__sg_tlink_flag_id + 1
        );

        out.printf(
            "CREATE SEQUENCE g_tag_set;\n"
            "ALTER SEQUENCE g_tag_set RESTART WITH %ud;\n"
            , max__tag_set_id + 1
        );
    }
    else if (sql_version.type == SQL_Production::Oracle)
    {
        out.printf("COMMIT;\n\n");
        out.printf(
            "CREATE SEQUENCE g_sg_link START WITH %ud INCREMENT BY 1 NOCACHE NOCYCLE NOORDER;\n"
            , max__sg_link_id + 1
        );

        out.printf(
            "CREATE SEQUENCE g_sg_link_tag START WITH %ud INCREMENT BY 1 NOCACHE NOCYCLE NOORDER;\n"
            , max__link_tag_id + 1
        );


        out.printf(
            "CREATE SEQUENCE g_sg_tlink START WITH %ud INCREMENT BY 1 NOCACHE NOCYCLE NOORDER;\n"
            , max__sg_tlink_id + 1
        );

        out.printf(
            "CREATE SEQUENCE g_sg_tlink_tag START WITH %ud INCREMENT BY 1 NOCACHE NOCYCLE NOORDER;\n"
            , max__sg_tlink_tag_id + 1
        );

        out.printf(
            "CREATE SEQUENCE g_sg_tlink_flag START WITH %ud INCREMENT BY 1 NOCACHE NOCYCLE NOORDER;\n"
            , max__sg_tlink_flag_id + 1
        );

        out.printf(
            "CREATE SEQUENCE g_tag_set START WITH %ud INCREMENT BY 1 NOCACHE NOCYCLE NOORDER;\n"
            , max__tag_set_id + 1
        );
    }

    out.printf("%s\n", sql_version.CommitTx().c_str());

    if (sql_version.type == SQL_Production::MsSql)
    {
        out.printf("!! @echo Thesaurus has been loaded.\n");
    }

    return;
}
#endif

WordLinkEnumerator* SG_Net::EnumerateWordLinks(void)
{
    return new WordLinkEnumerator(this);
}


WordLinkEnumerator* SG_Net::EnumerateWordLinks(int ekey0)
{
    return new WordLinkEnumerator(this, ekey0);
}


WordLinkEnumerator* SG_Net::EnumerateWordLinks(int ekey0, int link_type)
{
    return new WordLinkEnumerator(this, ekey0, link_type);
}


PhraseLinkEnumerator* SG_Net::EnumeratePhraseLinks(void)
{
    return new PhraseLinkEnumerator(this);
}


PhraseLinkEnumerator* SG_Net::EnumeratePhraseLinks(int id_phrase1)
{
    return new PhraseLinkEnumerator(this, id_phrase1);
}


PhraseLinkEnumerator* SG_Net::EnumeratePhraseLinks(int id_phrase1, int link_type)
{
    return new PhraseLinkEnumerator(this, id_phrase1, link_type);
}

PhraseLinkEnumerator* SG_Net::EnumeratePhraseLinks(int id_phrase1, const lem::MCollect<int> &link_types)
{
    return new PhraseLinkEnumerator(this, id_phrase1, link_types);
}

