// -----------------------------------------------------------------------------
// File SG_AUTOM_SQL_GENERATOR.CPP
//
// (c) by Elijah Koziev
//
// Content:
// Часть кода SynGram - генерация скрипта для заливки лексикона в SQL СУБД.
// 04.06.2009 - правка для компилябельности в gcc.Linux
// 13.06.2009 - для классов выгружаются привязки координат в таблицу
//              SG_CLASS_COORD с пометкой атрибут/измерение/тэг.
// 05.03.2010 - доработки экспорта в SQL для MS SQL Server
// 23.03.2010 - доработка экспорта в XML: добавлены узлы <entry_attrs> и
//              <form_dims> со строковым представлением координатных пар.
// 28.03.2010 - при экспорте в SQL создание таблицы SG_FORM_COORD управляется
//              параметром
// 27.05.2010 - поддержка BULK INSERT для MS SQL
// 27.08.2010 - убран столбец SG_ENTRY.I
// 06.01.2011 - добавление ограничений для SQL схемы лемматизатора в FireBird
// 11.08.2011 - добавлен экспорт таблиц окончаний
// -----------------------------------------------------------------------------
//
// CD->21.09.1996
// LC->08.04.2018
// --------------

#if defined SOL_EXPORT_SQL

#include <lem/fstring.h>
#include <lem/system_config.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/casing_coder.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/PhraseEntries.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/ClassList.h>
#include <lem/solarix/PartOfSpeechEnumerator.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntryEnumerator.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/LexemeEnumerator.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/CoordEnumerator.h>
#include <lem/solarix/Languages.h>
#include <lem/solarix/CriterionEnumerator.h>
#include <lem/solarix/LanguageEnumerator.h>
#include <lem/solarix/dsa_main.h>
#include <lem/solarix/Paradigma.h>
#include <lem/solarix/ParadigmaForm.h>
#include <lem/solarix/MetaEntry.h>
#include <lem/solarix/sg_autom.h>

using namespace lem;
using namespace Solarix;




static lem::UCString null_if_minus(int x)
{
    if (x == UNKNOWN)
        return UCString(L"null");
    else
        return lem::to_ustr(x);
}


static lem::CString null_if_minus8(int x)
{
    if (x == UNKNOWN)
        return lem::CString("null");
    else
        return to_str(x);
}






class CoordPairsList
{
private:
    lem::PtrCollect<lem::UFString> ints_list;
    lem::PtrCollect<lem::UFString> str_list;
    std::map< lem::UFString, int > ints2index;

public:
    CoordPairsList()
    {
        ints_list.push_back(new lem::UFString(L""));
        str_list.push_back(new lem::UFString(L""));
        ints2index.insert(std::make_pair(UFString(L""), 0));
        return;
    }

    int Register(const lem::UFString &ints, const lem::UFString &str)
    {
        if (str.empty() || str == L' ')
            return 0;

        auto it = ints2index.find(ints);
        if (it == ints2index.end())
        {
            int index = CastSizeToInt(ints_list.size());
            ints_list.push_back(new UFString(ints));
            str_list.push_back(new UFString(str));
            ints2index.insert(std::make_pair(ints, index));
            return index;
        }
        else
        {
            return it->second;
        }
    }

    void SaveSQL(OFormatter &out, const SQL_Production &sql_version)
    {
        const wchar_t* NPrefix = sql_version.GetNPrefix();

        if (sql_version.type == SQL_Production::MsSql)
        {
            out.printf("SET IDENTITY_INSERT coord_pairs ON\nGO\n");
        }

        int max__coord_pairs_id = 0;
        for (lem::Container::size_type i = 0; i < ints_list.size(); ++i)
        {
            out.printf("INSERT INTO coord_pairs( id, pairs, str_pairs )"
                " VALUES( %d, %us'%us', %us'%us' );\n",
                CastSizeToInt(i), NPrefix, ints_list[i]->c_str(), NPrefix, str_list[i]->c_str());
            max__coord_pairs_id = std::max(max__coord_pairs_id, CastSizeToInt(i));
        }


        if (sql_version.type == SQL_Production::FireBird)
        {
            out.printf(
                "CREATE SEQUENCE g_coord_pairs;\n"
                "ALTER SEQUENCE g_coord_pairs RESTART WITH %ud;\n",
                max__coord_pairs_id + 1
            );
        }
        else if (sql_version.type == SQL_Production::Oracle)
        {
            out.printf(
                "CREATE SEQUENCE g_coord_pairs START WITH %ud INCREMENT BY 1 NOCACHE NOCYCLE NOORDER;\n"
                , max__coord_pairs_id + 1
            );
        }
        else if (sql_version.type == SQL_Production::MsSql)
        {
            out.printf("SET IDENTITY_INSERT coord_pairs OFF\nGO\n");
        }

        return;
    }
};



void SynGram::Save_SQL(
    OFormatter &out,
    OFormatter &alters,
    const SQL_Production &sql_version
)
{
    if (sql_version.type == SQL_Production::MsSql)
    {
        out.printf("!! @echo Loading the lexicon ...\n");
    }


    // парадигмы
    out.printf("%s\n", sql_version.BeginTx().c_str());
    DSA->Save_SQL(out, alters, sql_version);
    out.printf("%s\n", sql_version.CommitTx().c_str());


    const char DIEZ_PLACEHOLDER[] = "__diezplaceholder__";
    const char BACKSLASH_PLACEHOLDER[] = "__backslashplaceholder__";

    const int rows_per_insert = sql_version.bulk_inserts;
    const int rows_per_insert2 = sql_version.internal_commit_period;

    CasingCoder casing(*this);

    const wchar_t* NPrefix = sql_version.GetNPrefix();

    // -----------------------------
    // ПАРАМЕТРЫ -> SG_CRITERION
    // -----------------------------

    out.printf("%s\n", sql_version.BeginTx().c_str());

    lem::Ptr<CriterionEnumerator> crenum(param->Enumerate());
    while (crenum->Fetch())
    {
        const int id = crenum->GetId();
        const Criterion& x = crenum->GetItem();

        lem::UFString name(sql_version.SqlStr(x.GetName()));
        lem::UFString strval(sql_version.SqlStr(x.GetString()));

        out.printf(
            "INSERT INTO sg_criterion( id, name, strval ) VALUES( %d, %us'%us', %us'%us' );\n"
            , id
            , NPrefix
            , name.c_str()
            , NPrefix
            , strval.c_str()
        );
    }

    out.eol();
    out.printf("%s\n", sql_version.CommitTx().c_str());




    // ***************************
    // ЯЗЫКИ -> SG_LANGUAGE
    // ***************************

    out.printf("%s\n", sql_version.BeginTx().c_str());

    // язык с кодом -1 нужен для корректного создания Foreign Keys
    out.printf("INSERT INTO sg_language( id, name ) VALUES( -1, %us'((undefined))' );\n", NPrefix);

    int id_lang_alphabet = 1, id_lang_link = 1, id_lang_param = 1;
    lem::Ptr<LanguageEnumerator> lenum(languages().Enumerate());
    while (lenum->Fetch())
    {
        const SG_Language &lang = lenum->GetItem();
        const int id = lang.id;
        lem::UFString lname(sql_version.SqlStr(lang.GetName()));

        out.printf(
            "INSERT INTO sg_language( id, name ) VALUES( %d, %us'%us' );\n"
            , id
            , NPrefix
            , lname.c_str()
        );

        for (lem::Container::size_type i = 0; i < lang.alphabet.size(); ++i)
        {
            const int id_alphabet = lang.alphabet[i];

            out.printf("INSERT INTO lang_alphabet( id, id_language, id_alphabet, ordering ) VALUES ( %d, %d, %d, %d );\n"
                , id_lang_alphabet++, id, id_alphabet, CastSizeToInt(i));
        }

        for (lem::Container::size_type i = 0; i < lang.lang_links.size(); ++i)
        {
            const int id_state = lang.lang_links[i].first.GetState();
            const int id_lang2 = lang.lang_links[i].second;

            out.printf("INSERT INTO lang_link( id, id_language, id_state, id_language2 )"
                " VALUES ( %d, %d, %d, %d );\n", id_lang_link++, id, id_state, id_lang2);
        }

        for (lem::Container::size_type i = 0; i < lang.params.size(); ++i)
        {
            const SG_LanguageParam &p = *lang.params[i];
            lem::UFString pname(sql_version.SqlStr(p.name));

            for (lem::Container::size_type j = 0; j < p.values.size(); ++j)
            {
                lem::UFString pval(sql_version.SqlStr(sql_version.ClearInvalidChars(p.values[j])));

                if (sql_version.type == SQL_Production::Oracle)
                {
                    UFString s2 = SQL_Production::Oracle_UNISTR(pval);

                    out.printf("INSERT INTO lang_param( id, id_language, param_name, param_value, ordering )"
                        " VALUES ( %d, %d, %us'%us', %us, %d );\n"
                        , id_lang_param++, id, NPrefix, pname.c_str(), s2.c_str(), CastSizeToInt(j));
                }
                else
                {
                    out.printf("INSERT INTO lang_param( id, id_language, param_name, param_value, ordering )"
                        " VALUES ( %d, %d, %us'%us', %us'%us', %d );\n"
                        , id_lang_param++, id, NPrefix, pname.c_str(), NPrefix, pval.c_str(), CastSizeToInt(j));
                }
            }
        }
    }

    out.printf("%s\n", sql_version.CommitTx().c_str());
    out.eol();


    {
        // КООРДИНАТЫ И СОСТОЯНИЯ
        out.printf("%s\n", sql_version.BeginTx().c_str());

        lem::Ptr<CoordEnumerator> cenum(coords().Enumerate());
        while (cenum->Fetch())
        {
            const int id_coord = cenum->GetId();
            const GramCoord &c = cenum->GetItem();

            out.printf(
                "INSERT INTO sg_coord( id, name, bistable ) VALUES ( %d, %us'%us', %d );\n",
                id_coord,
                NPrefix,
                c.GetName().front().c_str(),
                c.IsBistable() ? 1 : 0
            );

            int istate = 0;

            if (c.IsBistable())
            {
                // Все-таки объявим в явном виде два состояния для бистабильных координат, чтобы
                // в реляционной схеме можно было создавать foreight key с таблиц SG_ENTRY_COORD и SG_FORM_COORD
                out.printf("INSERT INTO sg_state( id, id_coord, name, weight, id_parent ) VALUES ( 0, %d, '0', 1, 0 );\n", id_coord);
                out.printf("INSERT INTO sg_state( id, id_coord, name, weight, id_parent ) VALUES ( 1, %d, '1', 1, 1 );\n", id_coord);
            }
            else
            {
                for (lem::Container::size_type j = 0; j < c.states().size(); ++j)
                {
                    const GramCoordState & s = c.states()[j];
                    const int id_parent = istate;

                    for (lem::Container::size_type k = 0; k < s.size(); ++k, ++istate)
                    {
                        out.printf("INSERT INTO sg_state( id, id_coord, name, id_parent, weight ) VALUES ( %d, %d, %us'%us', %d, %d );\n",
                            istate, id_coord, NPrefix, s[k].c_str(), id_parent, s.GetWeight());
                    }
                }
            }
        }

        out.printf("%s\n", sql_version.CommitTx().c_str());
    }

    // ---------------------
    // КЛАССЫ -> SG_CLASS
    // ---------------------

    out.printf("%s\n", sql_version.BeginTx().c_str());

    int id_class_attr_def = 1;
    lem::Ptr<PartOfSpeechEnumerator> class_enum((PartOfSpeechEnumerator*)classes().Enumerate());
    while (class_enum->Fetch())
    {
        const int id = class_enum->GetId();
        const SG_Class & c = static_cast<const SG_Class&>(class_enum->GetItem());

        const int ilang = c.GetLanguage();

        LEM_CHECKIT_Z(c.GetAliases().size() < 2);
        UCString aliase = c.GetAliases().empty() ? UCString() : c.GetAliases().front();

        if (ilang == UNKNOWN)
            out.printf(
                "INSERT INTO sg_class( id, name, name_aliase, id_lang, weight, closed_class ) VALUES( %d, %us'%us', %us'%us', NULL, %d, %d );\n"
                , id
                , NPrefix
                , sql_version.SqlStr(c.GetName()).c_str()
                , NPrefix
                , sql_version.SqlStr(aliase).c_str()
                , c.GetValue()
                , c.IsClosed() ? 1 : 0
            );
        else
            out.printf(
                "INSERT INTO sg_class( id, name, name_aliase, id_lang, weight, closed_class ) VALUES( %d, %us'%us', %us'%us', %d, %d, %d );\n"
                , id
                , NPrefix
                , sql_version.SqlStr(c.GetName()).c_str()
                , NPrefix
                , sql_version.SqlStr(aliase).c_str()
                , ilang
                , c.GetValue()
                , c.IsClosed() ? 1 : 0
            );

        // Сохраним в базе информацию о привязке координат (атрибутов, измерений, тэгов) к классам.
        for (lem::Container::size_type k = 0; k < c.attrs().size(); ++k)
        {
            const GramCoordAdr &atr = c.attrs()[k];

            out.printf(
                "INSERT INTO sg_class_coord( id_class, id_coord, coord_type ) VALUES( %d, %d, 0 );\n"
                , id
                , atr.GetIndex()
            );
        }

        {
            for (lem::Container::size_type k = 0; k < c.dims().size(); ++k)
            {
                const GramCoordAdr &dim = c.dims()[k];

                out.printf(
                    "INSERT INTO sg_class_coord( id_class, id_coord, coord_type ) VALUES( %d, %d, 1 );\n"
                    , id
                    , dim.GetIndex()
                );
            }
        }

        {
            for (lem::Container::size_type k = 0; k < c.tags().size(); ++k)
            {
                const GramCoordAdr &tag = c.tags()[k];

                out.printf(
                    "INSERT INTO sg_class_coord( id_class, id_coord, coord_type ) VALUES( %d, %d, 2 );\n"
                    , id
                    , tag.GetIndex()
                );
            }
        }


        for (lem::Container::size_type k = 0; k < c.attr_defaults.size(); ++k)
        {
            const GramCoordAdr &attr = c.attr_defaults[k].first;
            const int def_state = c.attr_defaults[k].second;

            out.printf(
                "INSERT INTO class_attr_def( id, id_class, id_coord, default_state ) VALUES( %d, %d, %d, %d );\n"
                , id_class_attr_def++
                , id
                , attr.GetIndex()
                , def_state
            );
        }
    }


    // Специальные классы - они не объявлены явно, но на них могут быть ссылки.
    out.printf("INSERT INTO sg_class( id, name, id_lang, weight, closed_class ) VALUES( -4, '_ANY_CLASS', NULL, 0, 1 );\n");
    out.eol();
    out.printf("%s\n", sql_version.CommitTx().c_str());


    // **********************
    // СТАТЬИ -> SG_ENTRY
    // **********************


    out.printf("%s\n", sql_version.BeginTx().c_str());

    lem::Ptr<OFormatter> sg_entry16, sg_form16, sg_entry_coord16, sg_form_coord16, sg_lexem16, multilexem16;

    // в эти файлы будет записано содержимое некоторых таблиц, чтобы потом загрузить
    // их максимально быстро с помощью специфичных для каждой СУБД средств.
    lem::Path path_entries(sql_version.outdir);
    lem::Path path_forms(sql_version.outdir);
    lem::Path path_entry_coords(sql_version.outdir);
    lem::Path path_form_coords(sql_version.outdir);
    lem::Path path_lexem(sql_version.outdir);
    lem::Path path_multilexem(sql_version.outdir);

    if (sql_version.type == SQL_Production::Oracle)
    {
        path_entries.ConcateLeaf(L"sg_entry.ctl");
        path_forms.ConcateLeaf(L"sg_form.ctl");
        path_entry_coords.ConcateLeaf(L"sg_entry_coord.ctl");
        path_form_coords.ConcateLeaf(L"sg_form_coord.ctl");
        path_lexem.ConcateLeaf(L"sg_lexem.ctl");
        path_multilexem.ConcateLeaf(L"multilexem.ctl");
    }
    else
    {
        path_entries.ConcateLeaf(L"sg_entry.txt");
        path_forms.ConcateLeaf(L"sg_form.txt");
        path_entry_coords.ConcateLeaf(L"sg_entry_coord.txt");
        path_form_coords.ConcateLeaf(L"sg_form_coord.txt");
        path_lexem.ConcateLeaf(L"sg_lexem.txt");
        path_multilexem.ConcateLeaf(L"multilexem.txt");
    }

    bool external_data = false;

    CoordPairsList coords_ref;

    if (sql_version.mssql_bulk_insert)
    {
        external_data = true;
        sg_entry16 = new U16Formatter(path_entries, true);
        sg_form16 = new U16Formatter(path_forms, true);
        sg_entry_coord16 = new U16Formatter(path_entry_coords, true);
        sg_form_coord16 = new U16Formatter(path_form_coords, true);
        sg_lexem16 = new U16Formatter(path_lexem, true);
        multilexem16 = new U16Formatter(path_multilexem, true);
    }
    else if (sql_version.loader && sql_version.IsUtf8())
    {
        external_data = true;
        sg_entry16 = new OUFormatter(path_entries, false);
        sg_form16 = new OUFormatter(path_forms, false);
        sg_entry_coord16 = new OUFormatter(path_entry_coords, false);
        sg_form_coord16 = new OUFormatter(path_form_coords, false);
        sg_lexem16 = new OUFormatter(path_lexem, false);
        multilexem16 = new OUFormatter(path_multilexem, false);
    }
    else if (sql_version.loader && sql_version.IsAscii())
    {
        external_data = true;
        sg_entry16 = new OFormatter(path_entries);
        sg_form16 = new OFormatter(path_forms);
        sg_entry_coord16 = new OFormatter(path_entry_coords);
        sg_form_coord16 = new OFormatter(path_form_coords);
        sg_lexem16 = new OFormatter(path_lexem);
        multilexem16 = new OFormatter(path_multilexem);
    }

    if (sql_version.type == SQL_Production::Oracle)
    {
        sg_entry16->printf(
            "OPTIONS (ROWS=10000,BINDSIZE=10000000,STREAMSIZE=10000000,READSIZE=10000000)\n"
            "LOAD DATA\n"
            "INFILE *\n"
            "TRUNCATE\n"
            "INTO TABLE sg_entry\n"
            "FIELDS TERMINATED BY '#' ( id, name, uname, id_class, freq, exportable, flags )\n"
            "BEGINDATA\n"
        );


        sg_form16->printf(
            "OPTIONS (ROWS=10000,BINDSIZE=10000000,STREAMSIZE=10000000,READSIZE=10000000)\n"
            "LOAD DATA\n"
            "INFILE *\n"
            "TRUNCATE\n"
            "INTO TABLE sg_form\n"
            "FIELDS TERMINATED BY '#' ( id_entry, iform, name, id_lexem, id_dims )\n"
            "BEGINDATA\n"
        );

        sg_entry_coord16->printf(
            "OPTIONS (ROWS=10000,BINDSIZE=10000000,STREAMSIZE=10000000,READSIZE=10000000)\n"
            "LOAD DATA\n"
            "INFILE *\n"
            "TRUNCATE\n"
            "INTO TABLE sg_entry_coord\n"
            "FIELDS TERMINATED BY '#' ( id_entry, icoord, istate )\n"
            "BEGINDATA\n"
        );

        sg_form_coord16->printf(
            "OPTIONS (ROWS=10000,BINDSIZE=10000000,STREAMSIZE=10000000,READSIZE=10000000)\n"
            "LOAD DATA\n"
            "INFILE *\n"
            "TRUNCATE\n"
            "INTO TABLE sg_form_coord\n"
            "FIELDS TERMINATED BY '#' ( id_entry, iform, icoord, istate )\n"
            "BEGINDATA\n"
        );

        sg_lexem16->printf(
            "OPTIONS (ROWS=10000,BINDSIZE=10000000,STREAMSIZE=10000000,READSIZE=10000000)\n"
            "LOAD DATA\n"
            "INFILE *\n"
            "TRUNCATE\n"
            "INTO TABLE sg_lexem\n"
            "FIELDS TERMINATED BY '#' ( id, name )\n"
            "BEGINDATA\n"
        );

        multilexem16->printf(
            "OPTIONS (ROWS=10000,BINDSIZE=10000000,STREAMSIZE=10000000,READSIZE=10000000)\n"
            "LOAD DATA\n"
            "INFILE *\n"
            "TRUNCATE\n"
            "INTO TABLE multilexem\n"
            "FIELDS TERMINATED BY '#' ( id, txt, headword, n_lexem )\n"
            "BEGINDATA\n"
        );

    }


    int max__sg_entry_id = 0;
    int diez_ekey = UNKNOWN;
    int diez_ekey2 = UNKNOWN;
    int backslash_ekey = UNKNOWN;
    int backslash_ekey2 = UNKNOWN;
    int diez_iform = UNKNOWN;
    int backslash_iform = UNKNOWN;


    // Если будем выгружать не все sg_form, то полная таблица SG_LEXEM нам не нужна,
    // и в этом массиве мы накопим только нужные записи.
    const bool demo = sql_version.IsDemo();
    std::set<const Solarix::Lexem*> sg_form_lexems;

    // определим граничную частоту выгружаемых словарных статей, чтобы для демо-версии SQL словаря
    // можно было делать выгрузку только NNN самых частых статей.
    int min_entry_freq = 0; // по умолчанию выгружаем все, даже неиспользуемые в эталонном корпусе

    if (sql_version.top_freq != UNKNOWN)
    {
        lem::Ptr<WordEntryEnumerator> wenum(word_entries->ListEntries());
        int row = 0;
        int max_freq = 0;
        std::map<int, int> freq_histo;
        while (wenum->Fetch())
        {
            const SG_Entry &e = wenum->GetItem();
            const int efreq = e.GetFreq();
            max_freq = std::max(max_freq, efreq);

            std::map<int, int>::iterator it = freq_histo.find(efreq);
            if (it == freq_histo.end())
                freq_histo.insert(std::make_pair(efreq, 1));
            else
                it->second++;
        }


        lem::MCollect< std::pair<int, int> > freqs;
        freqs.reserve(freq_histo.size());
        for (auto it = freq_histo.begin(); it != freq_histo.end(); ++it)
            freqs.push_back(*it);

        // отсортируем в порядке возрастания частоты
        std::sort(freqs.begin(), freqs.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b)
        {
            return a.first > b.first;
        });


        // теперь идем по отсортированной гистограмме в порядке убывания частоты,
        // и останавливаемся в момент, когда сумма числа статей станет > NNN
        min_entry_freq = max_freq;
        int sum_n = 0;

        for (lem::Container::size_type i = 0; i < freqs.size(); ++i)
        {
            sum_n += freqs[i].second;
            min_entry_freq = freqs[i].first;
            if (sum_n >= sql_version.top_freq)
                break;
        }
    }


    // --- begin ---
    {
        int count_of_dumped_entries = 0;
        std::unique_ptr<WordEntryEnumerator> wenum(word_entries->ListEntries());
        int row = 0;
        while (wenum->Fetch())
        {
            const SG_Entry &e = wenum->GetItem();

            UFString s = e.GetName().c_str();

            if (!sql_version.MatchEntryName(e.GetName()) || e.GetFreq() < min_entry_freq)
                continue;

            if (s == L'#')
            {
                diez_ekey = e.GetKey();
                s = DIEZ_PLACEHOLDER;
            }
            else if (s == L'\\')
            {
                backslash_ekey = e.GetKey();
                s = BACKSLASH_PLACEHOLDER;
            }

            int e_flags = 0;

            if (e.IsNonterminal())
                e_flags = e_flags | SOL_SG_NONTERMINAL_ENTRY;

            if (e.IsSilent())
                e_flags = e_flags | SOL_SG_SILENT_ENTRY;

            if (e.IsQuantor())
                e_flags = e_flags | SOL_SG_QUANTOR_ENTRY;


            const int e_case = e.GetAttrState(Solarix::GramCoordAdr(casing.icoord_casing));
            casing.RestoreCasing(e_case, s);

            UFString us(e.GetName().c_str());
            if (us == L'#')
            {
                us = DIEZ_PLACEHOLDER;
            }
            else if (us == L'\\')
            {
                us = BACKSLASH_PLACEHOLDER;
            }

            count_of_dumped_entries++;

            if (external_data)
            {
                sg_entry16->printf(
                    "%d#%us#%us#%d#%d#1#%d#\n"
                    , e.GetKey()
                    , s.c_str()
                    , us.c_str()
                    , e.GetClass()
                    , e.GetFreq()
                    , e_flags
                );
            }
            else
            {
                s = encode_str_to_sql(s);
                us = encode_str_to_sql(us);

                out.printf(
                    "INSERT INTO sg_entry( id, name, uname, id_class, freq, exportable, flags ) VALUES( %d, '%us', '%us', %d, %d, 1, %d );\n"
                    , e.GetKey()
                    , s.c_str()
                    , us.c_str()
                    , e.GetClass()
                    , e.GetFreq()
                    , e_flags
                );
            }

            max__sg_entry_id = std::max(max__sg_entry_id, e.GetKey());

            for (Container::size_type j = 0; j < e.attrs().size(); ++j)
            {
                const int icoord = e.attrs()[j].GetCoord().GetIndex();
                const int istate = e.attrs()[j].GetState();

                if (istate != ANY_STATE)
                {
                    if (external_data)
                    {
                        sg_entry_coord16->printf("%d#%d#%d\n",
                            e.GetKey(), icoord, istate);
                    }
                    else
                    {
                        out.printf("INSERT INTO sg_entry_coord( id_entry, icoord, istate ) VALUES ( %d, %d, %d );\n",
                            e.GetKey(), icoord, istate);
                    }
                }
            }

            {
                UFString form_dims, str_form_dims;
                for (Container::size_type j = 0; j < e.forms().size(); j++, row++)
                {
                    const SG_EntryForm &form = e.forms()[j];
                    lem::UFString fs(form.name().c_str());

                    if (fs == L'\\')
                    {
                        backslash_ekey2 = e.GetKey();
                        backslash_iform = CastSizeToInt(j);
                        fs = BACKSLASH_PLACEHOLDER;
                    }

                    if (fs == L'#')
                    {
                        diez_ekey2 = e.GetKey();
                        diez_iform = CastSizeToInt(j);
                        fs = DIEZ_PLACEHOLDER;
                    }

                    casing.RestoreCasing(e_case, fs);

                    form_dims.clear();
                    ComposeFormDims(e, form, form_dims, true);
                    form_dims.re_clear();

                    str_form_dims.clear();
                    ComposeFormDims(e, form, str_form_dims, false);
                    str_form_dims.re_clear();

                    const int id_dims = coords_ref.Register(form_dims, str_form_dims);

                    if (demo) sg_form_lexems.insert(&form.name());

                    if (external_data)
                    {
                        sg_form16->printf(
                            "%ud#%d#%us#%uld#%d\n"
                            , e.GetKey()
                            , j
                            , fs.c_str()
                            , &form.name()
                            , id_dims
                        );
                    }
                    else
                    {
                        fs = encode_str_to_sql(fs);

                        if (!(row%rows_per_insert2))
                            out.printf("%s\n", sql_version.InternalCommit().c_str());

                        out.printf(
                            "INSERT INTO sg_form( id_entry, iform, id_lexem, name, id_dims ) VALUES( %ud, %d, %uld, %us'%us', %d );\n"
                            , e.GetKey()
                            , j
                            , &form.name()
                            , NPrefix
                            , fs.c_str()
                            , id_dims
                        );
                    }

                    if (!sql_version.noformcoords)
                    {
                        if (external_data)
                        {
                            if (!form.coords().empty())
                            {
                                for (Container::size_type k = 0; k < form.coords().size(); ++k)
                                {
                                    if (form.coords()[k].GetState() != ANY_STATE)
                                    {
                                        sg_form_coord16->printf("%d#%d#%d#%d\n",
                                            e.GetKey(), j, form.coords()[k].GetCoord().GetIndex(), form.coords()[k].GetState());
                                    }
                                }
                            }
                        }
                        else if (
                            rows_per_insert &&
                            sql_version.type == SQL_Production::MySql &&
                            CastSizeToInt(form.coords().size()) <= rows_per_insert
                            )
                        {
                            bool export_coords = false;

                            for (Container::size_type k = 0; k < form.coords().size(); ++k)
                            {
                                if (form.coords()[k].GetState() != ANY_STATE)
                                {
                                    export_coords = true;
                                    break;
                                }
                            }


                            if (export_coords)
                            {
                                out.printf("INSERT INTO sg_form_coord( id_entry, iform, icoord, istate ) VALUES");
                                for (Container::size_type k = 0; k < form.coords().size(); ++k)
                                {
                                    if (form.coords()[k].GetState() != ANY_STATE)
                                    {
                                        if (k > 0)
                                            out.printf(",");

                                        out.printf(" ( %d, %d, %d, %d )\n",
                                            e.GetKey(), j, form.coords()[k].GetCoord().GetIndex(), form.coords()[k].GetState());
                                    }
                                }

                                out.printf(";\n");
                            }
                        }
                        else
                        {
                            for (Container::size_type k = 0; k < form.coords().size(); ++k)
                            {
                                if (form.coords()[k].GetState() != ANY_STATE)
                                {
                                    out.printf("INSERT INTO sg_form_coord( id_entry, iform, icoord, istate ) "
                                        " VALUES ( %d, %d, %d, %d );\n", e.GetKey(), j, form.coords()[k].GetCoord().GetIndex(), form.coords()[k].GetState()
                                    );
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    out.printf("%s\n", sql_version.CommitTx().c_str());



    if (sql_version.type == SQL_Production::FireBird)
    {
        out.printf("%s\n", sql_version.BeginTx().c_str());
        out.printf(
            "CREATE SEQUENCE g_sg_entry;\n"
            "ALTER SEQUENCE g_sg_entry RESTART WITH %ud;\n",
            max__sg_entry_id + 1
        );
        out.printf("%s\n", sql_version.CommitTx().c_str());
    }
    else if (sql_version.type == SQL_Production::Oracle)
    {
        out.printf(
            "CREATE SEQUENCE g_sg_entry START WITH %ud INCREMENT BY 1 NOCACHE NOCYCLE NOORDER;\n"
            , max__sg_entry_id + 1
        );
    }


    out.printf("%s\n", sql_version.BeginTx().c_str());

    lem::FString line_terminator = lem::System_Config::GetLineTerminator(true).c_str();

    if (sql_version.mssql_bulk_insert)
    {
        out.printf("!! @echo Loading SG_ENTRY ...\n");

        out.printf(
            "SET IDENTITY_INSERT sg_entry ON\n"
            "GO\n"
            "BULK INSERT sg_entry FROM '%us' WITH ( FIELDTERMINATOR='#', DATAFILETYPE='widechar', KEEPIDENTITY )\n"
            "GO\n"
            "SET IDENTITY_INSERT sg_entry OFF\n"
            "GO\n"
            , path_entries.GetUnicode().c_str()
        );

        out.printf("!! @echo Loading SG_ENTRY_COORD ...\n");
        out.printf("BULK INSERT sg_entry_coord FROM '%us' WITH ( FIELDTERMINATOR='#', DATAFILETYPE='widechar' )\n"
            "GO\n", path_entry_coords.GetUnicode().c_str());

        out.printf("!! @echo Loading SG_FORM ...\n");
        out.printf("BULK INSERT sg_form FROM '%us' WITH ( FIELDTERMINATOR='#', DATAFILETYPE='widechar' )\n"
            "GO\n", path_forms.GetUnicode().c_str());

        if (!sql_version.noformcoords)
        {
            out.printf("!! @echo Loading SG_FORM_COORD ...\n");
            out.printf("BULK INSERT sg_form_coord FROM '%us' WITH ( FIELDTERMINATOR='#', DATAFILETYPE='widechar' )\n"
                "GO\n", path_form_coords.GetUnicode().c_str());
        }
    }
    else if (sql_version.loader && sql_version.type == SQL_Production::MySql)
    {
        out.printf("%us '%us' INTO TABLE sg_entry CHARACTER SET utf8 FIELDS TERMINATED BY '#' ESCAPED BY '\\\\' LINES TERMINATED BY '%s' (id,name,uname,id_class,freq,exportable,flags,dic_div);\n"
            , sql_version.GetLoadInfileText(), path_entries.GetAbsolutePath().GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());

        out.printf("%us '%us' INTO TABLE sg_entry_coord CHARACTER SET utf8 FIELDS TERMINATED BY '#' LINES TERMINATED BY '%s' (id_entry,icoord,istate);\n"
            , sql_version.GetLoadInfileText(), path_entry_coords.GetAbsolutePath().GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());

        out.printf("%us '%us' INTO TABLE sg_form CHARACTER SET utf8 FIELDS TERMINATED BY '#' ESCAPED BY '\\\\' LINES TERMINATED BY '%s' (id_entry,iform,name,id_lexem,id_dims);\n"
            , sql_version.GetLoadInfileText(), path_forms.GetAbsolutePath().GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());

        if (!sql_version.noformcoords)
        {
            out.printf("%us '%us' INTO TABLE sg_form_coord CHARACTER SET utf8 FIELDS TERMINATED BY '#' LINES TERMINATED BY '%s' (id_entry,iform,icoord,istate);\n"
                , sql_version.GetLoadInfileText(), path_form_coords.GetAbsolutePath().GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());
        }
    }
    else if (sql_version.loader && sql_version.type == SQL_Production::Postgres)
    {
        out.printf("%us sg_entry(id,name,uname,id_class,freq,exportable,flags,dic_div) FROM '%us' WITH DELIMITER '#' NULL ''\n"
            , sql_version.GetLoadInfileText(), path_entries.GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());

        out.printf("%us sg_entry_coord(id_entry,icoord,istate) FROM '%us' WITH DELIMITER '#' NULL ''\n"
            , sql_version.GetLoadInfileText(), path_entry_coords.GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());

        out.printf("%us sg_form(id_entry,iform,name,id_lexem,id_dims) FROM '%us' WITH DELIMITER '#' NULL ''\n"
            , sql_version.GetLoadInfileText(), path_forms.GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());

        if (!sql_version.noformcoords)
        {
            out.printf("%us sg_form_coord(id_entry,iform,icoord,istate) FROM '%us' WITH DELIMITER '#' NULL ''\n"
                , sql_version.GetLoadInfileText(), path_form_coords.GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());
        }
    }

    out.eol();
    out.printf("%s\n", sql_version.CommitTx().c_str());

    out.printf("%s\n", sql_version.BeginTx().c_str());

    if (diez_ekey != UNKNOWN)
    {
        out.printf("UPDATE sg_entry SET name='#', uname='#' WHERE id=%d;\n", diez_ekey);
        out.printf("%s\n", sql_version.CommitTx().c_str());
        out.printf("%s\n", sql_version.BeginTx().c_str());
    }

    if (backslash_ekey != UNKNOWN)
    {
        out.printf("UPDATE sg_entry SET name='\\\\', uname='\\\\' WHERE id=%d;\n", backslash_ekey);
        out.printf("%s\n", sql_version.CommitTx().c_str());
        out.printf("%s\n", sql_version.BeginTx().c_str());
    }

    if (backslash_ekey2 != UNKNOWN)
    {
        out.printf("UPDATE sg_form SET name='\\\\' WHERE id_entry=%d AND iform=%d;\n", backslash_ekey2, backslash_iform);
        out.printf("%s\n", sql_version.CommitTx().c_str());
        out.printf("%s\n", sql_version.BeginTx().c_str());
    }

    if (diez_ekey2 != UNKNOWN)
    {
        out.printf("UPDATE sg_form SET name='#' WHERE id_entry=%d AND iform=%d;\n", diez_ekey2, diez_iform);
        out.printf("%s\n", sql_version.CommitTx().c_str());
        out.printf("%s\n", sql_version.BeginTx().c_str());
    }

    coords_ref.SaveSQL(out, sql_version);

    out.eol();
    out.printf("%s\n", sql_version.CommitTx().c_str());
    out.printf("%s\n", sql_version.BeginTx().c_str());

    // заполним небольшие служебные таблички
    const IntCollect &uentries = GetUEntries();
    for (lem::Container::size_type i = 0; i < uentries.size(); ++i)
    {
        int ekey = uentries[i];
        out.printf("INSERT INTO unknown_entries(id) VALUES (%d);\n", ekey);
    }

    for (int ipredef = 0; ipredef < SOL_SG_NPREDEF_ENTRIES; ++ipredef)
    {
        int ekey = GetPredefinedEntryKey(ipredef);
        out.printf("INSERT INTO predef_entries(id,id_entry) VALUES (%d,%d);\n", ipredef, ekey);
    }

    out.printf("%s\n", sql_version.CommitTx().c_str());


    // ********************************
    // СПРАВОЧНИК ЛЕКСЕМ -> SG_LEXEM
    // ********************************

    out.printf("%s\n", sql_version.BeginTx().c_str());

    const Lexem * diez_id = NULL;
    if (external_data)
    {
        lem::uint64_t max__sg_lexem_id = 0;

        lem::Ptr<LexemeEnumerator> lenum(GetEntries().ListLexemes());
        while (lenum->Fetch())
        {
            Lexem lex;
            const Lexem *ptr = lenum->Get(lex);

            if (demo && sg_form_lexems.find(ptr) == sg_form_lexems.end())
                continue;

            lem::uint64_t id = (lem::uint64_t)ptr;
            max__sg_lexem_id = std::max(max__sg_lexem_id, id);

            if (!sql_version.MatchEntryName(lex))
                continue;

            if ((*ptr) == L'#')
            {
                diez_id = ptr;
                sg_lexem16->printf("%uld#%s\n", ptr, DIEZ_PLACEHOLDER);
            }
            else
            {
                if (sql_version.type == SQL_Production::MsSql)
                {
                    sg_lexem16->printf("%uld#%us\n", ptr, ptr->c_str());
                }
                else if (sql_version.type == SQL_Production::Postgres && (*ptr) == L'\\')
                {
                    sg_lexem16->printf("%uld#%us\n", ptr, L"\\\\");
                }
                else
                {
                    UFString s = sql_version.SqlStr(*ptr);
                    sg_lexem16->printf("%uld#%us\n", ptr, s.c_str());
                }
            }
        }

        if (sql_version.type == SQL_Production::Oracle)
        {
            out.printf(
                "CREATE SEQUENCE g_sg_lexem START WITH %ud INCREMENT BY 1 NOCACHE NOCYCLE NOORDER;\n"
                , max__sg_lexem_id + 1
            );
        }
    }
    else if (
        rows_per_insert > 0 && rows_per_insert < lem::int_max &&
        (sql_version.type == SQL_Production::Oracle ||
            sql_version.type == SQL_Production::FireBird ||
            sql_version.type == SQL_Production::MySql)
        && !sql_version.IsDemo()
        )
    {
        const int ni = GetEntries().CountLexemes();
        lem::Ptr<LexemeEnumerator> lenum(GetEntries().ListLexemes());

        const int nblock = ni / rows_per_insert + (ni%rows_per_insert ? 1 : 0);
        int n = ni, j = 0;

        lem::uint64_t max__sg_lexem_id = 0;
        Lexem lex;

        for (int iblock = 0; iblock < nblock; iblock++)
        {
            const int nrow = n > rows_per_insert ? rows_per_insert : n;

            if (sql_version.type == SQL_Production::MySql)
            {
                out.printf("INSERT INTO sg_lexem( id, name ) VALUES\n");

                for (int i = 0; i < nrow; i++, n--)
                {
                    if (i)
                        out.printf(", ");

                    lenum->Fetch();
                    const Lexem *ptr = lenum->Get(lex);

                    UFString s = sql_version.SqlStr(*ptr);

                    out.printf(
                        "( %uld, '%us' )\n"
                        , ptr
                        , s.c_str()
                    );
                }
            }
            else if (sql_version.type == SQL_Production::FireBird)
            {
                out.printf("INSERT INTO sg_lexem( id, name )\n");

                for (int i = 0; i < nrow; i++, n--)
                {
                    lenum->Fetch();
                    const Lexem *ptr = lenum->Get(lex);

                    UFString s = sql_version.SqlStr(*ptr);

                    max__sg_lexem_id = std::max(max__sg_lexem_id, (lem::uint64_t)ptr);

                    if (i)
                        out.printf("UNION ALL\n");

                    out.printf(
                        "SELECT %uld, '%us' FROM RDB$DATABASE\n"
                        , ptr
                        , s.c_str()
                    );

                }

                out.printf(";\n");

                out.printf("\n%s\n", sql_version.InternalCommit().c_str());
            }
            else
            {
                out.printf("INSERT INTO sg_lexem( id, name )\n");

                for (int i = 0; i < nrow; i++, n--)
                {
                    if (i)
                        out.printf("UNION\n");

                    lenum->Fetch();
                    const Lexem *ptr = lenum->Get(lex);

                    UFString s = sql_version.SqlStr(*ptr);

                    out.printf(
                        "SELECT %uld, %us'%us' FROM DUAL\n"
                        , ptr
                        , NPrefix
                        , s.c_str()
                    );

                }
            }

            out.printf(";\n\n");
        }

        if (sql_version.type == SQL_Production::FireBird)
        {
            out.printf(
                "CREATE SEQUENCE g_sg_lexem;\n"
                "ALTER SEQUENCE g_sg_lexem RESTART WITH %uld;\n", max__sg_lexem_id + 1
            );
        }
    }
    else
    {
        lem::Ptr<LexemeEnumerator> lenum(GetEntries().ListLexemes());

        int row_count = 0;
        const int internal_commit_period = sql_version.internal_commit_period;

        Lexem lex;
        while (lenum->Fetch())
        {
            if (row_count > 0 && !(row_count%internal_commit_period))
                out.printf("%s\n", sql_version.InternalCommit().c_str());

            const Lexem *ptr = lenum->Get(lex);

            if (!sql_version.MatchEntryName(lex))
                continue;

            if (demo && sg_form_lexems.find(ptr) == sg_form_lexems.end())
                continue;

            UFString s = sql_version.SqlStr(*ptr);

            out.printf(
                "INSERT INTO sg_lexem( id, name ) VALUES( %uld, %us'%us' );\n"
                , ptr
                , NPrefix
                , s.c_str()
            );

            row_count++;
        }
    }

    if (sql_version.mssql_bulk_insert)
    {
        out.printf("!! @echo Loading SG_LEXEM ...\n");

        out.printf(
            "SET IDENTITY_INSERT sg_lexem ON\n"
            "GO\n"
            "BULK INSERT sg_lexem FROM '%us' WITH ( FIELDTERMINATOR='#', DATAFILETYPE='widechar', KEEPIDENTITY )\n"
            "GO\n"
            "SET IDENTITY_INSERT sg_lexem OFF\n"
            "GO\n"
            , path_lexem.GetUnicode().c_str()
        );

        if (diez_id != NULL)
        {
            out.printf("UPDATE sg_lexem SET name='#' WHERE id=%uld;", diez_id);
        }
    }
    else if (sql_version.loader && sql_version.type == SQL_Production::MySql)
    {
        out.printf("%us '%us' INTO TABLE sg_lexem CHARACTER SET utf8 FIELDS TERMINATED BY '#' LINES TERMINATED BY '%s' (id,name);\n"
            , sql_version.GetLoadInfileText(), path_lexem.GetAbsolutePath().GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());

        if (diez_id != NULL)
        {
            out.printf("UPDATE sg_lexem SET name='#' WHERE id=%uld;", diez_id);
        }
    }
    else if (sql_version.loader && sql_version.type == SQL_Production::Postgres)
    {
        out.printf("%us sg_lexem(id,name) FROM '%us' WITH DELIMITER '#' NULL ''\n"
            , sql_version.GetLoadInfileText(), path_lexem.GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());

        if (diez_id != NULL)
        {
            out.printf("UPDATE sg_lexem SET name='#' WHERE id=%uld;", diez_id);
        }
    }

    diez_id = NULL;

    out.eol();
    out.printf("%s\n", sql_version.CommitTx().c_str());

    // --------------------------
    // *** MULTILEXEM ***
    // --------------------------

    out.printf("%s\n", sql_version.BeginTx().c_str());
    int max__multilexem_id = 0;

    lem::Ptr<LexemeEnumerator> mlenum(GetEntries().ListLexemes());
    while (mlenum->Fetch())
    {
        Lexem lex;
        const Lexem *ptr = mlenum->Get(lex);

        if (!sql_version.MatchEntryName(lex))
            continue;

        UFString s = sql_version.SqlStr(*ptr);

        if (s != L"#")
        {
            const int n_lexem = lex.Count_Lexems();
            if (n_lexem > 1)
            {
                max__multilexem_id++;

                UCStringSet toks;
                lex.Split(toks);

                if (external_data)
                {
                    UFString headword(toks.front().c_str());
                    multilexem16->printf("%d#%us#%us#%d\n", max__multilexem_id, lex.c_str(), headword.c_str(), n_lexem);
                }
                else
                {
                    UFString headword(sql_version.SqlStr(toks.front()));
                    if (sql_version.type == SQL_Production::FireBird ||
                        sql_version.type == SQL_Production::SQLite ||
                        sql_version.type == SQL_Production::Postgres ||
                        sql_version.type == SQL_Production::Oracle)
                    {
                        out.printf("INSERT INTO multilexem( id, txt, headword, n_lexem) VALUES (%d,'%us','%us',%d);\n"
                            , max__multilexem_id, s.c_str(), headword.c_str(), n_lexem);
                    }
                    else
                    {
                        out.printf("INSERT INTO multilexem( txt, headword, n_lexem) VALUES ( '%us', '%us', %d);\n"
                            , s.c_str(), headword.c_str(), n_lexem);
                    }
                }
            }
        }
    }

    multilexem16.Delete();

    if (sql_version.mssql_bulk_insert)
    {
        out.printf("!! @echo Loading MULTILEXEM ...\n");

        out.printf(
            "SET IDENTITY_INSERT multilexem ON\n"
            "GO\n"
            "BULK INSERT multilexem FROM '%us' WITH ( FIELDTERMINATOR='#', DATAFILETYPE='widechar', KEEPIDENTITY )\n"
            "GO\n"
            "SET IDENTITY_INSERT multilexem OFF\n"
            "GO\n"
            , path_multilexem.GetUnicode().c_str()
        );
    }
    else if (sql_version.loader && sql_version.type == SQL_Production::MySql)
    {
        out.printf("%us '%us' INTO TABLE multilexem CHARACTER SET utf8 FIELDS TERMINATED BY '#' LINES TERMINATED BY '%s' (id,txt,headword,n_lexem);\n"
            , sql_version.GetLoadInfileText(), path_multilexem.GetAbsolutePath().GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());
    }
    else if (sql_version.loader && sql_version.type == SQL_Production::Postgres)
    {
        out.printf("%us multilexem(id,txt,headword,n_lexem) FROM '%us' WITH DELIMITER '#' NULL ''\n"
            , sql_version.GetLoadInfileText(), path_multilexem.GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());
    }

    out.eol();
    out.printf("%s\n", sql_version.CommitTx().c_str());
    out.printf("%s\n", sql_version.BeginTx().c_str());

    if (sql_version.type == SQL_Production::FireBird)
    {
        out.printf(
            "CREATE SEQUENCE g_multilexem;\n"
            "ALTER SEQUENCE g_multilexem RESTART WITH %uld;\n", max__multilexem_id + 1
        );
    }
    else if (sql_version.type == SQL_Production::Oracle)
    {
        out.printf(
            "CREATE SEQUENCE g_multilexem START WITH %ud INCREMENT BY 1 NOCACHE NOCYCLE NOORDER;\n"
            , max__multilexem_id + 1
        );
    }

    out.eol();
    out.printf("%s\n", sql_version.CommitTx().c_str());


    // ----------------------
    // ФРАЗОВЫЕ СТАТЬИ
    // ----------------------

    out.printf("%s\n", sql_version.BeginTx().c_str());
    int max__g_tentry_id = 0;
    int max__tnotes_id = 0;

    const wchar_t* Nprefix = sql_version.GetNPrefix();

    // выгружаем фразовые статьи в 2 прохода.
    // первый проход - фразовые статьи
    // второй проход - доп. информация для них
    for (int sql_pass = 0; sql_pass < 2; sql_pass++)
    {
        if (sql_version.type == SQL_Production::MsSql && sql_version.mssql_bulk_insert)
        {
            switch (sql_pass)
            {
            case 0: out.printf("SET IDENTITY_INSERT sg_tentry ON\nGO\n"); break;
            case 1: out.printf("SET IDENTITY_INSERT tnotes ON\nGO\n"); break;
            }
        }

        lem::Ptr<LS_ResultSet> phrases(GetStorage().ListPhrases());

        int i = 0;
        while (phrases->Fetch())
        {
            i++;
            const int id_phrase = phrases->GetInt(0);

            if (i && !(i%rows_per_insert2))
                out.printf("%s\n", sql_version.InternalCommit().c_str());

            if (sql_pass == 0) // выгружаем SG_TENTRY
            {
                SG_Phrase te;
                GetStorage().GetPhrase(id_phrase, te);

                max__g_tentry_id = std::max(max__g_tentry_id, id_phrase);

                const lem::UFString &txt = te.GetText();
                lem::UFString utxt = sql_version.SqlStr(lem::to_upper(te.GetText()));
                lem::UFString ce(sql_version.SqlStr(txt));

                if (txt.length() <= 32)
                {
                    out.printf(
                        "INSERT INTO sg_tentry( te_id, te_text, te_utxt, te_text32, te_id_language, te_id_class, te_syntax_flags )"
                        " VALUES ( %d, %us'%us', %us'%us', %us'%us', %us, %us, %d );\n"
                        , id_phrase
                        , Nprefix
                        , ce.c_str()
                        , Nprefix
                        , utxt.c_str()
                        , Nprefix
                        , to_upper(ce).c_str()
                        , null_if_minus(te.GetLanguage()).c_str()
                        , null_if_minus(te.GetClass()).c_str()
                        , te.GetSyntaxFlags()
                    );
                }
                else
                {
                    out.printf(
                        "INSERT INTO sg_tentry( te_id, te_text, te_utxt, te_text32, te_id_language, te_id_class, te_syntax_flags )"
                        " VALUES ( %d, %us'%us', %us'%us', %us'%us', %us, %us, %d );\n"
                        , id_phrase
                        , Nprefix
                        , ce.c_str()
                        , Nprefix
                        , utxt.c_str()
                        , Nprefix
                        , to_upper(lem::left(ce, 32)).c_str()
                        , null_if_minus(te.id_language).c_str()
                        , null_if_minus(te.id_class).c_str()
                        , te.GetSyntaxFlags()
                    );
                }
            }
            else if (sql_pass == 1) // выгружаем TNOTES
            {
                lem::Ptr<LS_ResultSet> notes(GetStorage().ListPhraseNotes(id_phrase));

                SG_PhraseNote note;
                while (notes->Fetch())
                {
                    const int id_note = notes->GetInt(0);
                    GetStorage().GetPhraseNote(id_note, note);

                    if (
                        note.GetType() == Solarix::SynGram::PivotNote ||
                        note.GetType() == Solarix::SynGram::SegmentationNote ||
                        note.GetType() == Solarix::SynGram::SyntaxNote
                        )
                    {
                        lem::UFString t(sql_version.SqlStr(note.GetData()));

                        max__tnotes_id = std::max(max__tnotes_id, note.GetId());

                        out.printf("INSERT INTO tnotes( tn_id, tn_te_id, tn_type, tn_format, tn_data )"
                            " VALUES ( %d, %d, %d, 0, %us'%us' );\n"
                            , note.GetId()
                            , id_phrase
                            , note.GetType()
                            , Nprefix
                            , t.c_str());
                    }
                }
            }
        }

        if (sql_version.type == SQL_Production::MsSql && sql_version.mssql_bulk_insert)
        {
            switch (sql_pass)
            {
            case 0: out.printf("SET IDENTITY_INSERT sg_tentry OFF\nGO\n"); break;
            case 1: out.printf("SET IDENTITY_INSERT tnotes OFF\nGO\n"); break;
            }
        }
    }

    if (sql_version.type == SQL_Production::FireBird)
    {
        out.printf(
            "CREATE SEQUENCE g_sg_tentry;\n"
            "ALTER SEQUENCE g_sg_tentry RESTART WITH %ud;\n"
            , max__g_tentry_id + 1
        );

        out.printf(
            "CREATE SEQUENCE g_tnotes;\n"
            "ALTER SEQUENCE g_tnotes RESTART WITH %ud;\n"
            , max__tnotes_id + 1
        );
    }
    else if (sql_version.type == SQL_Production::Oracle)
    {
        out.printf(
            "CREATE SEQUENCE g_sg_tentry START WITH %ud INCREMENT BY 1 NOCACHE NOCYCLE NOORDER;\n"
            , max__g_tentry_id + 1
        );

        out.printf(
            "CREATE SEQUENCE g_tnotes START WITH %ud INCREMENT BY 1 NOCACHE NOCYCLE NOORDER;\n"
            , max__tnotes_id + 1
        );
    }

    out.printf("%s\n", sql_version.CommitTx().c_str());



    // Выгрузим служебную информацию о сложных связях с многословной левой частью.

    out.printf("%s\n", sql_version.BeginTx().c_str());

    lem::Ptr<LS_ResultSet> cplx_left(GetStorage().ListCplxLeft());

    if (sql_version.type == SQL_Production::MsSql && sql_version.mssql_bulk_insert)
    {
        out.printf("SET IDENTITY_INSERT cplx_left ON\nGO\n");
    }

    int max__cplx_left_id = 0;

    while (cplx_left->Fetch())
    {
        const int cl_id = cplx_left->GetInt(0);
        max__cplx_left_id = std::max(max__cplx_left_id, cl_id);

        lem::UFString cl_headword(cplx_left->GetUFString(1));

        const int cl_minlen = cplx_left->GetInt(2);
        const int cl_maxlen = cplx_left->GetInt(3);

        out.printf("INSERT INTO cplx_left( cl_id, cl_headword, cl_minlen, cl_maxlen ) "
            " VALUES ( %d, %us'%us', %d, %d );\n",
            cl_id,
            Nprefix,
            cl_headword.c_str(),
            cl_minlen,
            cl_maxlen);
    }

    if (sql_version.type == SQL_Production::MsSql && sql_version.mssql_bulk_insert)
    {
        out.printf("SET IDENTITY_INSERT cplx_left OFF\nGO\n");
    }

    if (sql_version.type == SQL_Production::FireBird)
    {
        out.printf(
            "CREATE SEQUENCE g_cplx_left;\n"
            "ALTER SEQUENCE g_cplx_left RESTART WITH %ud;\n"
            , max__cplx_left_id + 1
        );
    }
    else if (sql_version.type == SQL_Production::Oracle)
    {
        out.printf(
            "CREATE SEQUENCE g_cplx_left START WITH %ud INCREMENT BY 1 NOCACHE NOCYCLE NOORDER;\n"
            , max__cplx_left_id + 1
        );
    }

    out.printf("%s\n", sql_version.CommitTx().c_str());


    // ---------------------------------
    // справочник типов доп. сведений
    // ---------------------------------

    out.printf("%s\n", sql_version.BeginTx().c_str());

    lem::Ptr<LS_ResultSet> aux_form_types(GetStorage().ListAuxFormTypes());

    if (sql_version.type == SQL_Production::MsSql && sql_version.mssql_bulk_insert)
    {
        out.printf("SET IDENTITY_INSERT aux_form_types ON\nGO\n");
    }

    int max__aux_form_types_id = 0;

    while (aux_form_types->Fetch())
    {
        const int id = aux_form_types->GetInt(0);
        max__aux_form_types_id = std::max(max__aux_form_types_id, id);

        UFString aux_data = aux_form_types->GetUFString(1);

        out.printf("INSERT INTO aux_form_types( id, name ) "
            " VALUES ( %d, %us'%us' );\n",
            id,
            Nprefix,
            aux_data.c_str());
    }

    if (sql_version.type == SQL_Production::MsSql && sql_version.mssql_bulk_insert)
    {
        out.printf("SET IDENTITY_INSERT aux_form_types OFF\nGO\n");
    }
    else if (sql_version.type == SQL_Production::FireBird && !sql_version.IsDemo())
    {
        out.printf(
            "CREATE SEQUENCE g_aux_form_types;\n"
            "ALTER SEQUENCE g_aux_form_types RESTART WITH %ud;\n"
            , max__aux_form_types_id + 1
        );
    }
    else if (sql_version.type == SQL_Production::Oracle)
    {
        out.printf(
            "CREATE SEQUENCE g_aux_form_types START WITH %ud INCREMENT BY 1 NOCACHE NOCYCLE NOORDER;\n"
            , max__aux_form_types_id + 1
        );
    }

    aux_form_types.Delete();

    if (!sql_version.IsDemo())
    {
        // доп. данные для грамматических форм

        lem::Ptr<LS_ResultSet> aux_forms(GetStorage().ListAuxForms());

        if (sql_version.type == SQL_Production::MsSql && sql_version.mssql_bulk_insert)
        {
            out.printf("SET IDENTITY_INSERT aux_form ON\nGO\n");
        }

        int max__aux_form_id = 0;
        int insert_count = 0;
        while (aux_forms->Fetch())
        {
            insert_count++;
            if (insert_count > 1 && (insert_count % 1000) == 0)
            {
                out.printf("\n%s\n", sql_version.CommitTx().c_str());
                out.printf("%s\n\n", sql_version.BeginTx().c_str());
            }

            const int id = aux_forms->GetInt(0);
            max__aux_form_id = std::max(max__aux_form_id, id);

            const int id_entry = aux_forms->GetInt(1);
            const int iform = aux_forms->GetInt(2);
            const int data_type = aux_forms->GetInt(3);

            UFString aux_data = sql_version.SqlStr(aux_forms->GetUFString(4));

            out.printf("INSERT INTO aux_form( id, id_entry, iform, data_type, data_text ) "
                " VALUES ( %d, %d, %d, %d, %us'%us' );\n",
                id,
                id_entry,
                iform,
                data_type,
                Nprefix,
                aux_data.c_str());
        }

        if (sql_version.type == SQL_Production::MsSql && sql_version.mssql_bulk_insert)
        {
            out.printf("SET IDENTITY_INSERT aux_form OFF\nGO\n");
        }
        else if (sql_version.type == SQL_Production::FireBird)
        {
            out.printf(
                "CREATE SEQUENCE g_aux_form;\n"
                "ALTER SEQUENCE g_aux_form RESTART WITH %ud;\n"
                , max__aux_form_id + 1
            );
        }
        else if (sql_version.type == SQL_Production::Oracle)
        {
            out.printf(
                "CREATE SEQUENCE g_aux_form START WITH %ud INCREMENT BY 1 NOCACHE NOCYCLE NOORDER;\n"
                , max__aux_form_id + 1
            );
        }

        aux_forms.Delete();


        // доп. данные для словарных статей

        lem::Ptr<LS_ResultSet> aux_entry(GetStorage().ListAuxEntryData());

        if (sql_version.type == SQL_Production::MsSql && sql_version.mssql_bulk_insert)
        {
            out.printf("SET IDENTITY_INSERT aux_entry_data ON\nGO\n");
        }

        int max__aux_entry_data_id = 0;

        while (aux_entry->Fetch())
        {
            const int id = aux_entry->GetInt(0);
            max__aux_entry_data_id = std::max(max__aux_entry_data_id, id);

            const int id_entry = aux_entry->GetInt(1);
            const int data_type = aux_entry->GetInt(2);
            UFString aux_data = sql_version.SqlStr(aux_entry->GetUFString(3));

            out.printf("INSERT INTO aux_entry_data( id, id_entry, data_type, data_text ) "
                " VALUES ( %d, %d, %d, %us'%us' );\n",
                id,
                id_entry,
                data_type,
                Nprefix,
                aux_data.c_str());
        }

        if (sql_version.type == SQL_Production::MsSql && sql_version.mssql_bulk_insert)
        {
            out.printf("SET IDENTITY_INSERT aux_entry_data OFF\nGO\n");
        }

        if (sql_version.type == SQL_Production::FireBird)
        {
            out.printf(
                "CREATE SEQUENCE g_aux_entry_data;\n"
                "ALTER SEQUENCE g_aux_entry_data RESTART WITH %ud;\n"
                , max__aux_entry_data_id + 1
            );
        }
        else if (sql_version.type == SQL_Production::Oracle)
        {
            out.printf(
                "CREATE SEQUENCE g_aux_entry_data START WITH %ud INCREMENT BY 1 NOCACHE NOCYCLE NOORDER;\n"
                , max__aux_entry_data_id + 1
            );
        }

        aux_entry.Delete();
    }

    out.printf("%s\n", sql_version.CommitTx().c_str());


    // ********************************
    // информация об окончаниях
    // ********************************
    out.printf("\n%s\n", sql_version.BeginTx().c_str());

    if (sql_version.type == SQL_Production::MsSql)
    {
        out.printf("\n\nSET IDENTITY_INSERT endings ON\nGO\n");
    }

    lem::Ptr<LS_ResultSet> endings(GetStorage().ListEndings());
    while (endings->Fetch())
    {
        lem::UFString s(sql_version.SqlStr(endings->GetUCString(1)));

        out.printf("INSERT INTO endings( id, ending, id_language, nform, sumfreq ) VALUES ( %d, '%us', %d, %d, %d );\n"
            , endings->GetInt(0), s.c_str(), endings->GetInt(2), endings->GetInt(3), endings->GetInt(4));
    }

    if (sql_version.type == SQL_Production::MsSql)
    {
        out.printf("SET IDENTITY_INSERT endings OFF\nGO\n\n");
    }

    lem::Ptr<LS_ResultSet> ending_stat(GetStorage().ListEndingStat());
    while (ending_stat->Fetch())
    {
        out.printf("INSERT INTO ending_stat( id_language, max_len ) VALUES ( %d, %d );\n", ending_stat->GetInt(0), ending_stat->GetInt(1));
    }

    out.printf("%s\n", sql_version.CommitTx().c_str());


    // ------------------------------------------
    // ЧАСТОТЫ СЛОВОФОРМ
    // ------------------------------------------

    out.printf("%s\n", sql_version.BeginTx().c_str());

    if (sql_version.type == SQL_Production::MsSql)
    {
        out.printf("\n\nSET IDENTITY_INSERT wordform_frequency ON\nGO\n");
    }

    lem::Ptr<LS_ResultSet> wordform_freqs(GetStorage().ListWordformFrequency());
    while (wordform_freqs->Fetch())
    {
        out.printf("INSERT INTO wordform_frequency( id, id_entry, iform, freq ) VALUES ( %d, %d, %d, %d );\n"
            , wordform_freqs->GetInt(0), wordform_freqs->GetInt(1), wordform_freqs->GetInt(2), wordform_freqs->GetInt(3));
    }

    if (sql_version.type == SQL_Production::MsSql)
    {
        out.printf("SET IDENTITY_INSERT wordform_frequency OFF\nGO\n\n");
    }

    out.printf("%s\n", sql_version.CommitTx().c_str());

    if (!sql_version.IsDemo())
    {
        // ----- метастатьи -----
        out.printf("%s\n", sql_version.BeginTx().c_str());

        int metaentry_item_id = 1;

        lem::Ptr<LS_ResultSet> rs_metaentry(GetStorage().ListMetaEntries());
        while (rs_metaentry->Fetch())
        {
            const int id = rs_metaentry->GetInt(0);
            lem::Ptr<MetaEntry> m = GetStorage().LoadMetaEntry(id);

            m->SaveSQL(&metaentry_item_id, out, sql_version);
        }

        out.eol();

        out.printf("%s\n", sql_version.CommitTx().c_str());
    }

    // --- омонимичные леммы ---
    out.printf("%s\n", sql_version.BeginTx().c_str());

    if (sql_version.type == SQL_Production::MsSql)
    {
        out.printf("SET IDENTITY_INSERT omonym ON\nGO\n\n");
    }

    int id_omonym = 1;
    lem::Ptr<LS_ResultSet> rs_omonym(GetStorage().ListOmonyms());
    while (rs_omonym->Fetch())
    {
        lem::UFString s(sql_version.SqlStr(rs_omonym->GetUCString(0)));
        int id_class = rs_omonym->GetInt(1);
        out.printf("INSERT INTO omonym( id, entry_name, id_class ) VALUES ( %d, '%us', %d );\n",
            id_omonym++, s.c_str(), id_class);
    }
    rs_omonym.Delete();
    out.eol();

    if (sql_version.type == SQL_Production::MsSql)
    {
        out.printf("SET IDENTITY_INSERT omonym OFF\nGO\n\n");
    }

    out.printf("%s\n", sql_version.CommitTx().c_str());


    // -----

    // Тезаурус
    net->Save_SQL(out, sql_version, min_entry_freq);

    out.printf("%s The end of dictionary upload script\n", sql_version.Get_Comment().c_str());

    if (sql_version.type == SQL_Production::MsSql)
    {
        out.printf("!! @echo Lexicon has been loaded.\n");
    }


    return;
}



void SynGram::Dump_XML(OFormatter &xml, OFormatter &xsd, int max_entry_count)
{
    // Формируем файл схемы

    xsd.printf(
        "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
        "<xsd:schema xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" "
        "xmlns:od=\"urn:schemas-microsoft-com:officedata\">\n"
        " <xsd:element name=\"dataroot\">\n"
        "  <xsd:complexType>\n"
        "   <xsd:sequence>\n"
        "    <xsd:element ref=\"class\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n"
        "    <xsd:element ref=\"entry\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n"
        "    <xsd:element ref=\"entry_form\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n"
        "   </xsd:sequence>\n"
        "  </xsd:complexType>\n"
        " </xsd:element>\n\n"

        " <xsd:element name=\"class\">\n"
        "  <xsd:annotation>\n"
        "   <xsd:appinfo>\n"
        "    <od:index index-name=\"PrimaryKey\" index-key=\"id \" primary=\"yes\" unique=\"yes\" clustered=\"no\"/>\n"
        "   </xsd:appinfo>\n"
        "  </xsd:annotation>\n"
        "  <xsd:complexType>\n"
        "   <xsd:sequence>\n"
        "    <xsd:element name=\"id\" minOccurs=\"0\" od:jetType=\"longinteger\" od:sqlSType=\"int\">\n"
        "    </xsd:element>\n"
        "    <xsd:element name=\"name\" minOccurs=\"0\" od:jetType=\"text\" od:sqlSType=\"nvarchar\">\n"
        "     <xsd:simpleType>\n"
        "      <xsd:restriction base=\"xsd:string\">\n"
        "       <xsd:maxLength value=\"255\"/>\n"
        "      </xsd:restriction>\n"
        "     </xsd:simpleType>\n"
        "    </xsd:element>\n"
        "   </xsd:sequence>\n"
        "  </xsd:complexType>\n"
        " </xsd:element>\n\n"

        " <xsd:element name=\"entry\">\n"
        "  <xsd:annotation>\n"
        "   <xsd:appinfo>\n"
        "    <od:index index-name=\"PrimaryKey\" index-key=\"id \" primary=\"yes\" unique=\"yes\" clustered=\"no\"/>\n"
        "   </xsd:appinfo>\n"
        "  </xsd:annotation>\n"
        "  <xsd:complexType>\n"
        "   <xsd:sequence>\n"
        "    <xsd:element name=\"id\" minOccurs=\"0\" od:jetType=\"longinteger\" od:sqlSType=\"int\">\n"
        "    </xsd:element>\n"
        "    <xsd:element name=\"id_class\" minOccurs=\"0\" od:jetType=\"longinteger\" od:sqlSType=\"int\">\n"
        "    </xsd:element>\n"
        "    <xsd:element name=\"name\" minOccurs=\"0\" od:jetType=\"text\" od:sqlSType=\"nvarchar\">\n"
        "     <xsd:simpleType>\n"
        "      <xsd:restriction base=\"xsd:string\">\n"
        "       <xsd:maxLength value=\"255\"/>\n"
        "      </xsd:restriction>\n"
        "     </xsd:simpleType>\n"
        "    </xsd:element>\n"
        "    <xsd:element name=\"entry_attrs\" minOccurs=\"0\" od:jetType=\"text\" od:sqlSType=\"nvarchar\">\n"
        "     <xsd:simpleType>\n"
        "      <xsd:restriction base=\"xsd:string\">\n"
        "       <xsd:maxLength value=\"255\"/>\n"
        "      </xsd:restriction>\n"
        "     </xsd:simpleType>\n"
        "    </xsd:element>\n"
        "   </xsd:sequence>\n"
        "  </xsd:complexType>\n"
        " </xsd:element>\n\n"

        " <xsd:element name=\"entry_form\">\n"
        "  <xsd:complexType>\n"
        "   <xsd:sequence>\n"
        "    <xsd:element name=\"iform\" minOccurs=\"0\" od:jetType=\"longinteger\" od:sqlSType=\"int\">\n"
        "    </xsd:element>\n"
        "    <xsd:element name=\"id_entry\" minOccurs=\"0\" od:jetType=\"longinteger\" od:sqlSType=\"int\">\n"
        "    </xsd:element>\n"
        "    <xsd:element name=\"name\" minOccurs=\"0\" od:jetType=\"text\" od:sqlSType=\"nvarchar\">\n"
        "     <xsd:simpleType>\n"
        "      <xsd:restriction base=\"xsd:string\">\n"
        "       <xsd:maxLength value=\"255\"/>\n"
        "      </xsd:restriction>\n"
        "     </xsd:simpleType>\n"
        "    </xsd:element>\n"
        "    <xsd:element name=\"form_dims\" minOccurs=\"0\" od:jetType=\"text\" od:sqlSType=\"nvarchar\">\n"
        "     <xsd:simpleType>\n"
        "      <xsd:restriction base=\"xsd:string\">\n"
        "       <xsd:maxLength value=\"255\"/>\n"
        "      </xsd:restriction>\n"
        "     </xsd:simpleType>\n"
        "    </xsd:element>\n"
        "   </xsd:sequence>\n"
        "  </xsd:complexType>\n"
        " </xsd:element>\n\n"

        "</xsd:schema>\n"
    );

    // Файл с данными
    xml.printf(
        "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
        "<!-- More info at http://www.solarix.ru/for_developers/docs/xml_dictionary.shtml -->\n"
        "<dataroot xmlns:od=\"urn:schemas-solarix-intellectronix:officedata\""
        " xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\""
        " xsi:noNamespaceSchemaLocation=\"%us\">\n\n"
        , xsd.GetStream()->GetName().GetFileName().c_str()
    );

    // **************************************************************
    // Формируется таблица CLASS - справочник грамматических классов
    // **************************************************************
    lem::Ptr<PartOfSpeechEnumerator> cenum((PartOfSpeechEnumerator*)classes().Enumerate());
    while (cenum->Fetch())
    {
        xml.printf(
            "<class>\n"
            "<id>%d</id>\n"
            "<name>%us</name>\n"
            "</class>\n"
            , cenum->GetId()
            , cenum->GetItem().GetName().c_str()
        );
    }


    CasingCoder casing(*this);

    // **************************************************************
    // Формируется таблица ENTRY - названия словарных статей
    // **************************************************************
    lem::UFString entry_attrs;
    lem::Ptr<WordEntryEnumerator> wenum(word_entries->ListEntries());
    int entry_count = 0;
    std::set<int> exported_entry_ids;
    while (wenum->Fetch())
    {
        const SG_Entry &e = wenum->GetItem();

        // Специальные статьи не должны попасть в XML выгрузку
        if (e.IsNonterminal() || e.IsSilent() || e.IsQuantor() || e.IsNoExport())
            continue;

        exported_entry_ids.insert(e.GetKey());

        UFString s(e.GetName().c_str());
        const int e_case = e.GetAttrState(Solarix::GramCoordAdr(casing.icoord_casing));
        casing.RestoreCasing(e_case, s);
        s = to_html(s);

        entry_attrs.clear();
        ComposeEntryAttrs(e, entry_attrs, false);
        entry_attrs.re_clear();

        xml.printf(
            "<entry>\n"
            "<id>%d</id>\n"
            "<id_class>%d</id_class>\n"
            "<name>%us</name>\n"
            "<entry_attrs>%us</entry_attrs>\n"
            "</entry>\n"
            , e.GetKey()
            , e.GetClass()
            , s.c_str()
            , entry_attrs.c_str()
        );

        entry_count++;

        if (max_entry_count <= entry_count)
            break;
    }



    // **************************************************************
    // Теперь формируем таблицу ENTRY_FORM - формы словарных статей
    // **************************************************************
    lem::UFString form_dims;
    wenum = word_entries->ListEntries();
    while (wenum->Fetch())
    {
        const SG_Entry &e = wenum->GetItem();
        if (exported_entry_ids.find(e.GetKey()) == exported_entry_ids.end())
            continue;

        const int e_case = e.GetAttrState(Solarix::GramCoordAdr(casing.icoord_casing));

        // Специальные статьи не должны попасть в XML выгрузку
        if (e.IsNonterminal() || e.IsSilent() || e.IsQuantor() || e.IsNoExport())
            continue;

        for (lem::Container::size_type j = 0; j < e.forms().size(); j++)
        {
            const SG_EntryForm &f = e.forms()[j];

            UFString name(f.name().c_str());
            casing.RestoreCasing(e_case, name);
            name = to_html(name);

            form_dims.clear();
            ComposeFormDims(e, f, form_dims, false);
            form_dims.re_clear();

            xml.printf(
                "<entry_form>\n"
                "<iform>%d</iform>\n"
                "<id_entry>%d</id_entry>\n"
                "<name>%us</name>\n"
                "<form_dims>%us</form_dims>\n"
                "</entry_form>\n"
                , j
                , e.GetKey()
                , name.c_str()
                , form_dims.c_str()
            );
        }
    }


    xml.printf("</dataroot>\n");

    return;
}


void SynGram::SaveLemmatizatorSQL(OFormatter &txt, OFormatter &alters, const SQL_Production &sql_version) const
{
    if (sql_version.type == SQL_Production::MsSql)
    {
        txt.printf("SET NOCOUNT ON;\n");
        txt.printf("!! @echo Loading the lemmatizer ...\n");
    }
    else if (sql_version.type == SQL_Production::Oracle)
    {
        txt.printf("HOST echo Loading the lemmatizer ...\n");
    }

    const wchar_t * Nprefix = sql_version.GetNPrefix();

    if (!sql_version.noschema)
    {
        // Создаем таблицы
        if (sql_version.type == SQL_Production::Oracle)
        {
            txt.printf(
                "SET AUTOCOMMIT OFF;\n\n"
            );

            txt.printf(
                "drop table lexemes_1;\n"
                "drop table lexemes_n;\n"
                "drop table lemmas;\n"
            );

            txt.printf(
                "create table lexemes_1( id number NOT NULL, lexeme nvarchar2(64), id_lemma number, lemma_count number );\n"
                "create table lexemes_n( id number NOT NULL, lexeme nvarchar2(64), id_lemma number );\n"
                "create table lemmas( id number NOT NULL, lemma nvarchar2(64) );\n"
                "\n"
            );
        }
        else if (sql_version.type == SQL_Production::MySql)
        {
            txt.printf(
                "drop table if exists lexemes_1;\n"
                "drop table if exists lexemes_n;\n"
                "drop table if exists lemmas;\n"
                "create table lexemes_1( id integer NOT NULL, lexeme char(32), id_lemma integer, lemma_count integer );\n"
                "create table lexemes_n( id integer NOT NULL, lexeme char(32), id_lemma integer );\n"
                "create table lemmas( id integer NOT NULL, lemma char(32) );\n"
                "\n"
            );
        }
        else if (sql_version.type == SQL_Production::SQLite)
        {
            const int lexlen = lem::UCString::max_len;

            txt.printf(
                "begin;\n"
                "drop table if exists lexemes_1;\n"
                "drop table if exists lexemes_n;\n"
                "drop table if exists lemmas;\n"
                "create table lexemes_1( id integer, lexeme varchar(32), id_lemma integer, lemma_count integer );\n"
                "create table lexemes_n( id integer, lexeme varchar(32), id_lemma integer );\n"
                "create table lemmas( id integer, lemma varchar(32) );\n"
                "commit;"
                "\n"
            );
        }
        else if (sql_version.type == SQL_Production::FireBird)
        {
            const int lexlen = lem::UCString::max_len * 6 + 1; // for utf8 encoding

            txt.printf("%us\n", sql_version.DropTable("lexemes_1").c_str());
            txt.printf("%us\n", sql_version.DropTable("lexemes_n").c_str());
            txt.printf("%us\n", sql_version.DropTable("lemmas").c_str());

            txt.printf(
                "create table lexemes_1( id integer NOT NULL, lexeme varchar(%d), id_lemma integer, lemma_count integer );\n"
                "create table lexemes_n( id integer NOT NULL, lexeme varchar(%d), id_lemma integer );\n"
                "create table lemmas( id integer NOT NULL, lemma varchar(%d) );\n"
                "commit;\n"
                "\n",
                lexlen, lexlen, lexlen
            );
        }
        else if (sql_version.type == SQL_Production::MsSql)
        {
            txt.printf(
                "BEGIN TRANSACTION\n"
                "IF EXISTS(SELECT TABLE_NAME FROM solarix.INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'lexemes_1') drop table lexemes_1;\n"
                "IF EXISTS(SELECT TABLE_NAME FROM solarix.INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'lexemes_n') drop table lexemes_n;\n"
                "IF EXISTS(SELECT TABLE_NAME FROM solarix.INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'lemmas') drop table lemmas;\n"
                "CREATE TABLE lexemes_1( id INTEGER NOT NULL, lexeme nchar(32), id_lemma integer NOT NULL, lemma_count integer );\n"
                "CREATE TABLE lexemes_n( id INTEGER NOT NULL, lexeme nchar(32), id_lemma integer NOT NULL );\n"
                "CREATE TABLE lemmas( id integer NOT NULL, lemma nchar(32) );\n"
                "COMMIT\n"
                "GO\n"
                "\n"
            );
        }
    }

    // Выгружаем данные для лемматизатора

    const int rows_per_insert2 = sql_version.internal_commit_period;

    // Для ускорения процесса сначала составим обратный индекс

    std::map<Lexem, int> lemmas;
    int lemma_id = 0;

    std::map<Lexem, std::pair<int/*id*/, int/*count*/> > l2l;
    std::multimap<Lexem, int> l3l;
    typedef std::multimap<Lexem, int>::const_iterator IT3;

    lem::Ptr<WordEntryEnumerator> wenum(word_entries->ListEntries());
    while (wenum->Fetch())
    {
        const SG_Entry &e = wenum->GetItem();

        if (!sql_version.MatchEntryName(e.GetName()))
            continue;

        if (e.IsNonterminal() || e.IsQuantor())
            continue;

        const Lexem &lemma = e.GetName();

        const wchar_t c = lemma.front();
        if (lem::is_udelim(c) || c == L'_')
            continue;

        int id = UNKNOWN;
        std::map<Lexem, int>::const_iterator it1 = lemmas.find(lemma);
        if (it1 == lemmas.end())
        {
            id = lemma_id + 1;
            lemma_id++;
            lemmas.insert(std::make_pair(lemma, id));
        }
        else
        {
            id = it1->second;
        }


        for (lem::Container::size_type j = 0; j < e.forms().size(); ++j)
        {
            const Solarix::Lexem &lexeme = e.forms()[j].name();

            std::map< Lexem, std::pair<int, int> >::iterator it2 = l2l.find(lexeme);
            if (it2 == l2l.end())
            {
                // Эта форма еще не встречалась
                l2l.insert(std::make_pair(lexeme, std::make_pair(id, 1)));
            }
            else
            {
                // Эта форма уже встречалась ранее.
                // Посмотрим, какие лемматизации для нее зарегистрированы.
                std::pair<IT3, IT3> its3 = l3l.equal_range(lexeme);

                bool found = false;
                for (IT3 k = its3.first; k != its3.second; ++k)
                    if (k->second == id)
                    {
                        found = true;
                        break;
                    }

                if (!found)
                {
                    // Это новая лемматизация - инкремент счетчика альтернативных лемматизаций для формы
                    it2->second.second++;
                }
            }

            std::pair<IT3, IT3> its3 = l3l.equal_range(lexeme);
            if (its3.first == l3l.end())
            {
                l3l.insert(std::make_pair(lexeme, id));
            }
            else
            {
                bool found = false;
                for (IT3 k = its3.first; k != its3.second; ++k)
                    if (k->second == id)
                    {
                        found = true;
                        break;
                    }

                if (!found)
                {
                    l3l.insert(std::make_pair(lexeme, id));
                }
            }
        }
    }


    lem::Ptr<OFormatter> lemmas16, lexemes1_16, lexemesn_16;

    lem::Path path_lemmas(sql_version.outdir);
    lem::Path path_lexemes_1(sql_version.outdir);
    lem::Path path_lexemes_n(sql_version.outdir);

    if (sql_version.type == SQL_Production::Oracle)
    {
        path_lemmas.ConcateLeaf(L"lemmas.ctl");
        path_lexemes_1.ConcateLeaf(L"lexemes_1.ctl");
        path_lexemes_n.ConcateLeaf(L"lexemes_n.ctl");
    }
    else
    {
        path_lemmas.ConcateLeaf(L"lemmas.txt");
        path_lexemes_1.ConcateLeaf(L"lexemes_1.txt");
        path_lexemes_n.ConcateLeaf(L"lexemes_n.txt");
    }

    bool external_data = false;

    if (sql_version.mssql_bulk_insert)
    {
        external_data = true;
        lemmas16 = new U16Formatter(path_lemmas, true);
        lexemes1_16 = new U16Formatter(path_lexemes_1, true);
        lexemesn_16 = new U16Formatter(path_lexemes_n, true);
    }
    else if (sql_version.loader && sql_version.IsUtf8())
    {
        external_data = true;
        lemmas16 = new OUFormatter(path_lemmas, false);
        lexemes1_16 = new OUFormatter(path_lexemes_1, false);
        lexemesn_16 = new OUFormatter(path_lexemes_n, false);
    }
    else if (sql_version.loader && sql_version.IsAscii())
    {
        external_data = true;
        lemmas16 = new OFormatter(path_lemmas);
        lexemes1_16 = new OFormatter(path_lexemes_1);
        lexemesn_16 = new OFormatter(path_lexemes_n);
    }



    if (sql_version.type == SQL_Production::Oracle)
    {
        lemmas16->printf(
            "OPTIONS (ROWS=10000,BINDSIZE=10000000,STREAMSIZE=10000000,READSIZE=10000000)\n"
            "LOAD DATA\n"
            "INFILE *\n"
            "TRUNCATE\n"
            "INTO TABLE lemmas\n"
            "FIELDS TERMINATED BY '#' ( id, lemma )\n"
            "BEGINDATA\n"
        );

        lexemes1_16->printf(
            "OPTIONS (ROWS=10000,BINDSIZE=10000000,STREAMSIZE=10000000,READSIZE=10000000)\n"
            "LOAD DATA\n"
            "INFILE *\n"
            "TRUNCATE\n"
            "INTO TABLE lexemes_1\n"
            "FIELDS TERMINATED BY '#' ( id, lexeme, id_lemma, lemma_count )\n"
            "BEGINDATA\n"
        );

        lexemesn_16->printf(
            "OPTIONS (ROWS=10000,BINDSIZE=10000000,STREAMSIZE=10000000,READSIZE=10000000)\n"
            "LOAD DATA\n"
            "INFILE *\n"
            "TRUNCATE\n"
            "INTO TABLE lexemes_n\n"
            "FIELDS TERMINATED BY '#' ( id, lexeme, id_lemma )\n"
            "BEGINDATA\n"
        );
    }



    txt.printf("%s\n", sql_version.BeginTx().c_str());

    int irow = 0;

    for (std::map<Lexem, int>::const_iterator it = lemmas.begin(); it != lemmas.end(); ++it, ++irow)
    {
        const Solarix::Lexem & lemma = it->first;
        const int id = it->second;

        if (external_data)
        {
            if (lemma != L"#")
                lemmas16->printf("%d#%us\n", id, lemma.c_str());
        }
        else
        {
            if (!(irow%rows_per_insert2))
                txt.printf("%s\n", sql_version.InternalCommit().c_str());

            lem::UFString s_lemma = sql_version.SqlStr(lemma);
            txt.printf("INSERT INTO lemmas( id, lemma ) VALUES ( %d, %us'%us' );\n",
                id, Nprefix, s_lemma.c_str());
        }
    }

    int id_1 = 0, id_n = 0;
    for (std::map<Lexem, std::pair<int, int> >::const_iterator it = l2l.begin(); it != l2l.end(); ++it, irow++)
    {
        const Solarix::Lexem & lexeme = it->first;
        const int id_lemma = it->second.first;
        const int lemma_count = it->second.second;

        if (external_data)
        {
            if (lexeme != L"#")
                lexemes1_16->printf("%d#%us#%d#%d\n", id_1++, lexeme.c_str(), id_lemma, lemma_count);
        }
        else
        {
            if (!(irow%rows_per_insert2))
                txt.printf("%s\n", sql_version.InternalCommit().c_str());

            lem::UFString s_lexeme = sql_version.SqlStr(lexeme);

            txt.printf("INSERT INTO lexemes_1( id, lexeme, id_lemma, lemma_count ) VALUES ( %d, %us'%us', %d, %d );\n",
                id_1++, Nprefix, s_lexeme.c_str(), id_lemma, lemma_count);
        }
    }

    for (std::multimap<Lexem, int>::const_iterator it = l3l.begin(); it != l3l.end(); ++it, irow++)
    {
        const Solarix::Lexem & lexeme = it->first;
        const int id_lemma = it->second;

        if (external_data)
        {
            if (lexeme != L"#")
                lexemesn_16->printf("%d#%us#%d\n", id_n++, lexeme.c_str(), id_lemma);
        }
        else
        {
            if (!(irow%rows_per_insert2))
                txt.printf("%s\n", sql_version.InternalCommit().c_str());

            lem::UFString s_lexeme = sql_version.SqlStr(lexeme);

            txt.printf("INSERT INTO lexemes_n( id, lexeme, id_lemma ) VALUES ( %d, %us'%us', %d );\n",
                id_n++, Nprefix, s_lexeme.c_str(), id_lemma);
        }
    }

    lem::FString line_terminator = lem::System_Config::GetLineTerminator(true).c_str();

    if (sql_version.mssql_bulk_insert)
    {
        txt.printf("BULK INSERT lemmas FROM '%us' WITH ( FIELDTERMINATOR='#', DATAFILETYPE='widechar' )\n"
            "GO\n", path_lemmas.GetUnicode().c_str());

        txt.printf("BULK INSERT lexemes_1 FROM '%us' WITH ( FIELDTERMINATOR='#', DATAFILETYPE='widechar' )\n"
            "GO\n", path_lexemes_1.GetUnicode().c_str());

        txt.printf("BULK INSERT lexemes_n FROM '%us' WITH ( FIELDTERMINATOR='#', DATAFILETYPE='widechar' )\n"
            "GO\n", path_lexemes_n.GetUnicode().c_str());
    }
    else if (sql_version.loader && sql_version.type == SQL_Production::MySql)
    {
        txt.printf("%us '%us' INTO TABLE lemmas CHARACTER SET utf8 FIELDS TERMINATED BY '#' LINES TERMINATED BY '%s' (id,lemma);\n"
            , sql_version.GetLoadInfileText(), path_lemmas.GetAbsolutePath().GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());

        txt.printf("%us '%us' INTO TABLE lexemes_1 CHARACTER SET utf8 FIELDS TERMINATED BY '#' LINES TERMINATED BY '%s' (id,lexeme,id_lemma,lemma_count);\n"
            , sql_version.GetLoadInfileText(), path_lexemes_1.GetAbsolutePath().GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());

        txt.printf("%us '%us' INTO TABLE lexemes_n CHARACTER SET utf8 FIELDS TERMINATED BY '#' LINES TERMINATED BY '%s' (id,lexeme,id_lemma);\n"
            , sql_version.GetLoadInfileText(), path_lexemes_n.GetAbsolutePath().GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());
    }
    else if (sql_version.loader && sql_version.type == SQL_Production::Postgres)
    {
        txt.printf("%us lemmas(id,lemma) FROM '%us' WITH DELIMITER '#' NULL ''\n"
            , sql_version.GetLoadInfileText(), path_lemmas.GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());

        txt.printf("%us lexemes_1(id,lexeme,id_lemma,lemma_count) FROM '%us' WITH DELIMITER '#' NULL ''\n"
            , sql_version.GetLoadInfileText(), path_lexemes_1.GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());

        txt.printf("%us lexemes_n(id,lexeme,id_lemma) FROM '%us' WITH DELIMITER '#' NULL ''\n"
            , sql_version.GetLoadInfileText(), path_lexemes_n.GetUnicode().subst_all(L"\\", L"\\\\").c_str(), line_terminator.c_str());
    }



    txt.printf("%s\n", sql_version.CommitTx().c_str());


    // Создаем нужные индексы
    if (sql_version.type == SQL_Production::Oracle)
    {
        txt.printf("HOST echo Lemmatizer has been loaded.\n");
        txt.printf("EXIT\n\n");

        if (!sql_version.noschema)
        {
            alters.printf("create unique index lexemes1_idx1 on lexemes_1(lexeme);\n");
            alters.printf("create index lexemesn_idx1 on lexemes_n(lexeme);\n");
            alters.printf("create unique index lemmas_idx1 on lemmas(id);\n");

            alters.printf(
                "ALTER TABLE LEMMAS ADD PRIMARY KEY (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE LEXEMES_1 ADD FOREIGN KEY (ID_LEMMA) REFERENCES LEMMAS (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE LEXEMES_1 ADD CHECK (LEMMA_COUNT>0) ENABLE VALIDATE;\n"
                "ALTER TABLE LEXEMES_1 ADD PRIMARY KEY (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE LEXEMES_N ADD FOREIGN KEY (ID_LEMMA) REFERENCES LEMMAS (ID) ENABLE VALIDATE;\n"
                "COMMIT;\n"
            );
        }

        alters.printf("HOST echo Lemmatizer has been loaded.\n");
        alters.printf("EXIT\n\n");
    }
    else if (sql_version.type == SQL_Production::FireBird)
    {
        if (!sql_version.noschema)
        {
            txt.printf(
                "alter table LEMMAS add constraint PK_LEMMAS primary key (ID);\n"
                "alter table LEXEMES_1 add constraint PK_LEXEMES_1 primary key (ID);\n"
                "alter table LEXEMES_N add constraint PK_LEXEMES_N primary key (ID);\n"
                "COMMIT;\n"

                "alter table LEMMAS add constraint UNQ1_LEMMAS unique (LEMMA);\n"
                "alter table LEXEMES_1 add constraint FK_LEXEMES_1_1 foreign key (ID_LEMMA) references LEMMAS(ID);\n"
                "alter table LEXEMES_1 add constraint UNQ1_LEXEMES_1 unique (LEXEME);\n"
                "alter table LEXEMES_1 add constraint CHK1_LEXEMES_1 check (LEMMA_COUNT>0);\n"
                "alter table LEXEMES_N add constraint FK_LEXEMES_N_1 foreign key (ID_LEMMA) references LEMMAS(ID);\n"
                "CREATE INDEX LEXEMES_N_IDX1 ON LEXEMES_N (LEXEME);\n"

                "COMMIT;\n"

                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'LEXEME') and (RDB$RELATION_NAME = 'LEXEMES_N');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'LEMMA') and (RDB$RELATION_NAME = 'LEMMAS');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'LEXEME') and (RDB$RELATION_NAME = 'LEXEMES_1');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'ID_LEMMA') and (RDB$RELATION_NAME = 'LEXEMES_1');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'LEMMA_COUNT') and (RDB$RELATION_NAME = 'LEXEMES_1');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'ID_LEMMA') and (RDB$RELATION_NAME = 'LEXEMES_N');\n"
                "COMMIT;\n"
            );

        }
    }
    else if (sql_version.type == SQL_Production::MySql)
    {
        if (!sql_version.noschema)
        {
            txt.printf(
                "alter table lexemes_1 add unique index lexemes1_idx1(lexeme);\n"
                "alter table lexemes_n add index lexemes1_idx1(lexeme);\n"
                "alter table lemmas add unique index lemmas_idx1(id);\n"
                "\n"
            );
        }
    }
    else if (sql_version.type == SQL_Production::MsSql)
    {
        if (!sql_version.noschema)
        {
            txt.printf("BEGIN TRANSACTION\n");
            txt.printf("ALTER TABLE lemmas ADD CONSTRAINT pk_lemmas PRIMARY KEY (id);\n");
            txt.printf("ALTER TABLE lexemes_1 ADD CONSTRAINT pk_lexemes_1 PRIMARY KEY(id);\n");
            txt.printf("ALTER TABLE lexemes_n ADD CONSTRAINT pk_lexemes_n PRIMARY KEY(id);\n");

            txt.printf("ALTER TABLE lemmas ALTER COLUMN lemma nchar(32) NOT NULL;\n");
            txt.printf("create unique index lemmas_idx1 on lemmas(lemma);\n\n");

            txt.printf("ALTER TABLE lexemes_1 WITH CHECK ADD CONSTRAINT FK_lexemes_1_lemmas FOREIGN KEY(ID_LEMMA) REFERENCES lemmas(ID);\n");
            txt.printf("ALTER TABLE lexemes_1 CHECK CONSTRAINT FK_lexemes_1_lemmas;\n");
            txt.printf("ALTER TABLE lexemes_1 ALTER COLUMN lexeme nchar(32) NOT NULL;\n");
            txt.printf("ALTER TABLE lexemes_1 ALTER COLUMN lemma_count int NOT NULL;\n");
            txt.printf("create unique index lexemes1_idx1 on lexemes_1(lexeme);\n");

            txt.printf("ALTER TABLE lexemes_n ALTER COLUMN lexeme nchar(32) NOT NULL;\n");
            txt.printf("create index lexemesn_idx1 on lexemes_n(lexeme);\n");
            txt.printf("ALTER TABLE lexemes_n WITH CHECK ADD CONSTRAINT FK_lexemes_n_lemmas FOREIGN KEY(ID_LEMMA) REFERENCES lemmas(ID);\n");
            txt.printf("ALTER TABLE lexemes_n CHECK CONSTRAINT FK_lexemes_n_lemmas;\n");

            txt.printf("\n%s\n", sql_version.CommitTx().c_str());
        }

        txt.printf("!! @echo Lemmatizer has been loaded.\n");

        txt.printf(
            "EXIT\n"
            "\n"
        );
    }
    else if (sql_version.type == SQL_Production::SQLite)
    {
        if (!sql_version.noschema)
        {
            txt.printf("%s\n", sql_version.BeginTx().c_str());
            txt.printf("create unique index lexemes1_idx1 on lexemes_1(lexeme);\n");
            txt.printf("create index lexemesn_idx1 on lexemes_n(lexeme);\n");
            txt.printf("create unique index lemmas_idx1 on lemmas(id);\n\n");
            txt.printf("\n%s\n", sql_version.CommitTx().c_str());
        }

        txt.printf(
            ".exit\n"
            "\n"
        );
    }

    return;
}


void SynGram::ComposeEntryAttrs(
    const SG_Entry &e,
    UFString &entry_attrs,
    bool as_numbers
)
{
    entry_attrs.clear();

    if (e.GetClass() < 0)
        return;

    const SG_Class &cls = GetClass(e.GetClass());

    const CP_Array& coords = e.attrs();

    lem::MCollect< GramCoordPair > attrs;
    std::copy(coords.begin(), coords.end(), std::back_inserter(attrs));

    // Отсортируем список атрибутов по возрастанию кода координаты
    std::sort(attrs.begin(), attrs.end(), [](const GramCoordPair &x, const GramCoordPair &y)
    {
        return x.GetCoord().GetIndex() < y.GetCoord().GetIndex();
    });

    // Сериализация
    SerializeCoords(attrs, entry_attrs, as_numbers);

    return;
}




void SynGram::SaveRules_SQL(OFormatter &out, OFormatter &alters, const SQL_Production &sql_version)
{
    out.eol();

    std::unique_ptr<LS_ResultSet> rs(storage->ListLanguageUsage());
    while (rs->Fetch())
    {
        int id_language = rs->GetInt(0);
        bool is_input = rs->GetInt(1) == 1;
        bool is_output = rs->GetInt(2) == 1;
        bool is_default = rs->GetInt(3) == 1;

        out.printf("INSERT INTO lang_usage( id_language, is_input, is_output, is_default )"
            " VALUES ( %d, %d, %d, %d );\n", id_language, is_input ? 1 : 0, is_output ? 1 : 0, is_default ? 1 : 0);
    }

    out.eol();

    return;
}

#endif
