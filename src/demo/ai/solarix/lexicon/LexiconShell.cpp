// -----------------------------------------------------------------------------
// File LexiconShell.CPP
//
// (c) by Koziev Elijah --SOLARIX INTELLECTRONIX Project--
//
// Обработчик команд (консольный отладчик) для тестирования
// СОЛЯРИСа - грамматической машины. Данная утилита тестирует: лексикон (проекцию
// словоформ), тезаурус, базу N-грамм.
//
// 01.09.2007 - после старта выводим меню для запроса режима: морфологический
//              анализ, стемминг и др.  
//
// 02.10.2007 - выдается время загрузки словаря.
// 30.03.2008 - добавлена работа с БД N-грамм.
// 07.05.2008 - в версии Lite меню выбора режима не выводится, подразумевается
//              включение морфологического анализа.
// 12.05.2008 - для 64-битной версии словарь загружается из bin-windows64
// 23.07.2008 - исправлена ошибка в выводе результатов поиска N-грамм
// 27.07.2008 - после успешной загрузки словаря выдается краткая сводка по
//              его содержанию - кол-во статей, записей в тезаурусе и
//              базе n-грамм.
// 05.11.2008 - отдельно сделан поиск частоты для 2- и 3-грамм.
// 19.11.2008 - отдельно сделан поиск по разным видам согласованных 2-грамм
// 12.12.2008 - сделана декомпиляция найденной статьи
// 29.12.2008 - переделано меню работы с тезаурусом - добавлен пункт поиска
//              переводов. 
// 13.03.2009 - по умолчанию не создается файл unfound_entries.txt для записи
//              ненайденных слов, а также не открывается отладочный журнал. 
// 20.07.2009 - добавлена работа с 4- и 5-граммами
// 10.07.2010 - добавлен вывод парадигмы статей, найденных для введенного слова
// -----------------------------------------------------------------------------
//
// CD->25.02.2003
// LC->02.04.2018
// --------------

#include <lem/keyboard.h>
#include <lem/logfile.h>
#include <lem/shell.h>
#include <lem/process.h>
#include <lem/solarix/_sg_api.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/AuxFormTypes.h>
#include <lem/solarix/PhraseEntries.h>
#include <lem/solarix/PhraseNoteEnumerator.h>
#include <lem/solarix/ThesaurusTagDefs.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/WordLinkEnumerator.h>
#include <lem/solarix/PhraseLinkEnumerator.h>
#include <lem/solarix/ThesaurusStorage.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/PartsOfSpeech.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntryEnumerator.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/WordFormEnumerator.h>
#include <lem/solarix/NGramHandler.h>
#include <lem/solarix/MultiwordMerger.h>
#include <lem/solarix/casing_coder.h>

#include "NGramPrinter.h"
#include "LexiconShell.h"

using namespace std;
using namespace lem;
using namespace Solarix;



LexiconShell::LexiconShell(const lem::Path &dict_path, bool batch, bool write_unfound_entries)
    : first_turn(true)
{
    batch_mode = batch;

    LoadDictionary(dict_path);

    proj_words = true;
    do_print_proj_coords = true;

    if (write_unfound_entries)
        unfound_entry.Open(lem::Path("unfound_entries.txt"));

    return;
}



static bool lang_sorter(
    const lem::triple<int, UCString, int> &a,
    const lem::triple<int, UCString, int> &b
)
{
    return a.third > b.third;
}


// **********************************************
// Loading SOLARIX dictionary from binary file.
// **********************************************
void LexiconShell::LoadDictionary(const lem::Path &_dict_path)
{
    nul_tty.Open(lem::Path(NULL_DEVICE));
    sol_id.reset(new Dictionary(&nul_tty, merr));

    lem::Path folder;
    lem::Path dict_path;

    if (!_dict_path.empty())
    {
        dict_path = _dict_path;
    }
    else
    {
        // Сначала попробуем найти словарь в текущем каталоге, затем
        // в каталоге ..\bin-windows (или ..\bin-linux), а уже потом
        // спросим пользователя.
        int ivar = 0;

        while (true)
        {
            dict_path = folder;
            dict_path.ConcateLeaf(L"dictionary.xml");

            if (dict_path.DoesExist())
                break;

            ivar++;
            if (ivar == 1)
            {
#if defined LEM_WINDOWS
#if defined LEM_64
                folder = lem::Path(L"..\\bin-windows64");
#else
                folder = lem::Path(L"..\\bin-windows");
#endif
#else
#if defined LEM_64
                folder = lem::Path(L"../bin-linux64");
#else
                folder = lem::Path(L"../bin-linux");
#endif
#endif
            }
            else if (ivar == 2)
            {
#if defined LEM_WINDOWS
#if defined LEM_64
                folder = lem::Path(L"..\\..\\..\\..\\bin-windows64");
#else
                folder = lem::Path(L"..\\..\\..\\..\\bin-windows");
#endif
#elif defined LEM_MACOS
#if defined LEM_64
                folder = lem::Path(L"../../../../bin-mac64");
#else
                folder = lem::Path(L"../../../../bin-mac");
#endif
#else
#if defined LEM_64
                folder = lem::Path(L"../../../../bin-linux64");
#else
                folder = lem::Path(L"../../../../bin-linux");
#endif
#endif
            }
            else if (ivar == 3)
            {
#if defined LEM_WINDOWS
#if defined LEM_64
                folder = lem::Path(L".\\bin-windows64");
#else
                folder = lem::Path(L".\\bin-windows");
#endif
#elif defined LEM_MACOS
#if defined LEM_64
                folder = lem::Path(L"./bin-mac64");
#else
                folder = lem::Path(L"./bin-mac");
#endif
#else
#if defined LEM_64
                folder = lem::Path(L"./bin-linux64");
#else
                folder = lem::Path(L"./bin-linux");
#endif
#endif
            }
            else if (ivar == 4)
            {
#if defined LEM_WINDOWS
#if defined LEM_64
                folder.clear();
#else
                folder = lem::Path(L"..");
#endif
#else
#if defined LEM_64
                folder.clear();
#else
                folder = lem::Path(L"..");
#endif
#endif
            }
            else
            {
                folder = lem::Shell::AskFolder(L"Enter the name of folder containing dictionary files:");
            }
        }
    }

    mout->printf("Loading dictionary from %vfA%us%vn...", dict_path.GetUnicode().c_str()); mout->flush();

    Load_Options opt;
    opt.load_semnet = true;
    opt.affix_table = true;
    opt.seeker = true;
    opt.lexicon = false; // используем ленивую подгрузку словарных статей
    opt.ngrams = true;

    lem::ElapsedTime timer;
    bool ok = false;

    try
    {
        ok = sol_id->LoadModules(dict_path, opt);
    }
    catch( const lem::E_BaseException &ex )
    {
     mout->printf("%us\n", ex.what());
     ok = false;
    }
    catch (...)
    {
        ok = false;
    }

    if (!ok)
    {
        mout->printf("\n\nERROR!\nIncompatible dictionary version\n");
        lem::Process::Exit();
    }

    timer.stop();

    const int elapsed_msec = timer.msec();

    SG = &sol_id->GetSynGram();
    GG = &sol_id->GetGraphGram();

    mout->printf(" %vfAOK%vn %vfE%d%vn msec\nDictionary version=%us\n", elapsed_msec, sol_id->GetVersion().serialize().c_str());

    return;
}

LexiconShell::~LexiconShell(void)
{
    if (unfound_entry.IsOpened())
        unfound_entry.GetStream()->close();

    return;
}

const lem::UFString LexiconShell::enter_cmd(const char *Prompt) const
{
    UFString str;
    while (str.empty())
    {
        mout->printf("%vfF%s", Prompt); // Command prompt
        str = mkey->ask_ufstring();
        mout->printf("%vn");
        str.trim();
    }

    return str;
}

// ****************************************
// Entering the command processing loop.
// ****************************************
void LexiconShell::main_loop(bool show_menu, const lem::MCollect<int>& menu)
{
    if (first_turn)
    {
        // Выведем меню выбора режима.
        while (true)
        {
            int mode = 1;

            if (show_menu)
            {
                mout->printf(
                    "\n\n"
                    " %vfE1%vn - morphological analysis\n"
                    " %vfE2%vn - thesaurus\n"
                    " %vfE3%vn - N-grams\n"
                    " %vfE4%vn - search for entry by ID\n"
                    " %vfE5%vn - search for entry by name\n"
                    " %vfE6%vn - flexer\n"
                    " %vfE7%vn - syllabic breaks\n\n"
                    " %vfE8%vn - dictionary statistics\n\n"
                    " %vf90%vn - exit\n"
                    "\nChoose command: "
                );

                mode = menu.empty() ? mkey->ask_int() : menu[0];
            }

            ExecuteMenu(mode);

            show_menu = true;
        }
    }

    first_turn = false;

    return;
}


int LexiconShell::ShowMenu()
{
    mout->printf(
        "\n\n"
        " %vfE1%vn - morphological analysis\n"
        " %vfE2%vn - thesaurus\n"
        " %vfE3%vn - N-grams\n"
        " %vfE4%vn - search for entry by ID\n"
        " %vfE5%vn - search for entry by name\n"
        " %vfE6%vn - flexer\n"
        " %vfE7%vn - syllabic breaks\n\n"
        " %vfE8%vn - dictionary statistics\n\n"
        " %vf90%vn - exit\n"
        "\nChoose command: "
    );

    return mkey->ask_int();
}

void LexiconShell::ExecuteMenu(int choice)
{
    switch (choice)
    {
    case 1: TestLexiconLookUp();      break;
    case 2: TestThesaurus();  break;
    case 3: TestNGrams();     break;
    case 4: SearchByIE();     break;
    case 5: SearchByName();       break;
    case 6: ShowParadigma();      break;
    case 7: ShowSyllabicBreaks(); break;
    case 8: ShowStatistics();     break;
    case 0: exit(0);
    }

    return;
}


void LexiconShell::EnterMenuLoop()
{
    ExecuteMenu(ShowMenu());
    return;
}

void LexiconShell::TestLexiconLookUp(void)
{
    (*mout) << "Type #exit to exit, #menu to enter a control menu\n";

    for (;;)
    {
        UFString str = enter_cmd(": ");

        if (str == L"#exit")
            lem::Process::Exit(0);

        if (str == L"#help")
        {
            ShowHelp();
            continue;
        }

        if (str == "#menu")
        {
            EnterMenuLoop();
            return;
        }

        if (str.front() == L'#')
        {
            SetMode(str);
            continue;
        }

        if (
            str.search(L'*') == UNKNOWN &&
            str.search(L'?') == UNKNOWN &&
            str.search(L'~') == UNKNOWN
            )
        {
            // Точный поиск
            MorphologyAnalysis(str);
        }
        else
        {
            lem::Ptr<WordFormEnumerator> wenum;
            if (str.search(L'~') != UNKNOWN || str.search(L'/') != UNKNOWN)
            {
                // Нечеткий поиск
                str.subst(L"~", L"");

                UCString cword(str.c_str());

                wenum = SG->GetEntries().ListWordForms_Fuzzy(cword, 0.5);
            }
            else if (lem::regex_is_pattern(str.c_str()))
            {
                // Поиск по маске с ? и *
                wenum = SG->GetEntries().ListWordForms_Globbing(str);
            }


            mout->eol();

            while (wenum->Fetch())
            {
                const int ekey = wenum->GetEntryKey();
                const int iform = wenum->GetFormIndex();
                float val = wenum->GetValue();

                const SG_Entry &e = SG->GetEntry(ekey);
                const SG_EntryForm &f = e.forms()[iform];

                const SG_Class & cls = SG->GetClass(e.GetClass());

                const UCString &class_name = cls.GetName();

                mout->printf(
                    "%vfE%us%vn %35t %vfA%us%vn:%vfF%us%vn ekey=%d val=%4.2rf\n"
                    , f.name().c_str(), class_name.c_str(), e.GetName().c_str(), e.GetKey(), val
                );
            }

            mout->eol();
        }
    }

    return;
}


void LexiconShell::MorphologyAnalysis(const UFString &word)
{
    FullMorphologyAnalysis(word, true, false);
}


void LexiconShell::PrintPhrase(SynGram &sg, SG_Phrase & frz)
{
    UCString id_class(lem::to_ustr(frz.GetClass()));
    if (frz.GetClass() != -1)
    {
        const SG_Class &c = sg.GetClass(frz.GetClass());
        id_class = c.GetName();
    }

    UCString id_lang(lem::to_ustr(frz.GetLanguage()));
    if (frz.GetLanguage() != -1)
    {
        const SG_Language &l = sg.languages()[frz.GetLanguage()];
        id_lang = l.GetName();
    }

    mout->printf("Phrase [%vfE%us%vn] te_id=%d id_language=%us id_class=%us\n", frz.GetText().c_str(), frz.GetId(),
        id_lang.c_str(), id_class.c_str());

    // Выведем доп. информацию по этой фразе
    lem::Ptr<PhraseNoteEnumerator> notes(sg.EnumeratePhraseNotes(frz.GetId()));
    while (notes->Fetch())
    {
        SG_PhraseNote note;
        notes->GetNote(note);

        UCString note_type(lem::to_ustr(note.GetType()));
        switch (note.GetType())
        {
        case SynGram::SegmentationNote: note_type = L"segmentation"; break;
        case SynGram::SyntaxNote: note_type = L"syntax"; break;
        case SynGram::PivotNote: note_type = L"pivot"; break;
        }

        mout->printf("note tn_id=%d type=%us data=%us\n", note.GetId(), note_type.c_str(), note.GetData().c_str());
    }

    return;
}


void LexiconShell::FullMorphologyAnalysis(
    const UFString &word,
    bool print_projections,
    bool print_links
)
{
    LexicalAutomat &la = sol_id->GetLexAuto();

    Solarix::Lexem lword(word.c_str());
    la.TranslateLexem(lword, true);

    RC_Lexem ml(&lword, null_deleter());

    // MCollect<Word_Coord> res;
    // MCollect<Real1> val_list;
    // lem::PtrCollect<LA_ProjectInfo> prj_extra_inf;

     // Делаем запрос к Лексическому автомату, который делает проекцию...

    // if( fuzzy )
    //  la.ProjectWord( ml, res, val_list, prj_extra_inf, LexicalAutomat::Dynforms_Last_Chance, 2, UNKNOWN, GetDebugger() );
    // else
    //  la.ProjectWord( ml, res, val_list, prj_extra_inf, LexicalAutomat/*::DynformsMode*/::Wordforms, 0, UNKNOWN, GetDebugger() );

    MLProjList job(ml, lem::UCString(word.c_str()), 0, 1);
    job.set_Allow_Fuzzy(fuzzy);
    job.set_Dynforms(fuzzy);
    la.ProjectJob(job, UNKNOWN, false, GetDebugger());

    const MCollect<Word_Coord> &res = job.GetCoordList();
    const MCollect<ProjScore> &val_list = job.GetCoordValList();
    const lem::PtrCollect<LA_ProjectInfo> &prj_extra_inf = job.GetExtraInf();

    Display_Projects(res, val_list, prj_extra_inf, print_projections, print_links);

    // поищем соответствующие фразовые статьи
    lem::UFString phrase(word);
    phrase.trim();
    const int te_id = sol_id->GetSynGram().GetStorage().FindPhrase(phrase, true);
    if (te_id != UNKNOWN)
    {
        SG_Phrase frz;
        sol_id->GetSynGram().GetStorage().GetPhrase(te_id, frz);
        PrintPhrase(sol_id->GetSynGram(), frz);
    }

    return;
}


void LexiconShell::Display_Projects(
    const MCollect<Word_Coord> & res,
    const MCollect<ProjScore> & val_list,
    const lem::PtrCollect<LA_ProjectInfo> & prj_extra_inf,
    bool print_projections,
    bool print_links
)
{
    if (!res.empty())
    {
        CasingCoder& cc = sol_id->GetLexAuto().GetCasingCoder();

        mout->printf("\nThere are %vfE%d%vn projections:\n", CastSizeToInt(res.size()));

        std::set<int> ientry_set;

        // Перечисляем проекции
        for (lem::Container::size_type ipr = 0; ipr < res.size(); ipr++)
        {
            const int ientry = res[ipr].GetEntry();
            ientry_set.insert(ientry);

            const SG_Entry &e = SG->GetEntry(ientry);
            const UCString &e_name = e.GetName();
            lem::UFString word(e_name.c_str());
            cc.RestoreCasing(word, ientry);

            const int iclass = e.GetClass();
            const UCString &class_name = SG->classes()[iclass].GetName();

            mout->printf(
                "#%W2d %vfA%us%vn:%vfF%us%vn"
                , ipr + 1, class_name.c_str(), word.c_str()
            );

            if (val_list[ipr].score != 0)
                mout->printf(" score=%vfE%g%vn", val_list[ipr].score);

            if (print_projections)
            {
                const int iform = res[ipr].GetForm();
                const SG_EntryForm &frm = e.forms()[iform];
                const LA_ProjectInfo *inf = prj_extra_inf[ipr];

                mout->printf(" ientry=%d iform=%d", ientry, iform);

                if ((!frm.coords().empty() || inf != NULL) && do_print_proj_coords)
                {
                    if (!frm.coords().empty())
                    {
                        mout->printf("\n   { ");
                        for (Container::size_type i = 0; i < frm.coords().size(); i++)
                        {
                            frm.coords()[i].SaveTxt(*mout, *SG);
                            mout->printf(" ");
                        }
                        mout->printf("}");
                    }

                    if (inf != NULL)
                    {
                        mout->printf(' ');
                        inf->coords.SaveTxt(*mout, *SG);
                    }
                }

                lem::Ptr<LS_ResultSet> rs = SG->GetStorage().ListAuxForms(e.GetKey(), iform);
                int record_count = 0;
                while (rs->Fetch())
                {
                    int id_aux_type = rs->GetInt(1);
                    lem::UFString aux_data = rs->GetUFString(2);
                    lem::UCString aux_type = SG->GetAuxFormTypes()[id_aux_type];
                    mout->printf(" %vfD%us=%us%vn", aux_type.c_str(), aux_data.c_str());
                }
            }

            mout->eol();
        }

        if (print_links)
        {
            // Опционально отображаем все связки для найденных статей.
            if (!ientry_set.empty())
                for (std::set<int>::const_iterator l = ientry_set.begin(); l != ientry_set.end(); l++)
                {
                    // Связки
                    std::set<int> links;
                    SG->Get_Net().Find_Linked_Entries(SG->GetEntry(*l).GetKey(), 1, links);

                    for (std::set<int>::const_iterator k = links.begin(); k != links.end(); k++)
                    {
                        const SG_Entry &e = SG->GetEntry(*k);

                        mout->printf(
                            "link to %vfE%us%vn:%vfE%us%vn  %60t ekey=%d\n"
                            , SG->classes()[e.GetClass()].GetName().c_str()
                            , e.GetName().c_str()
                            , *k
                        );
                    }
                }
        }
    }

    return;
}



void LexiconShell::ShowHelp(void) const
{
    mout->printf(
        "Commands:\n"
        "%vfF#exit%vn       - quit the program\n"
        "%vfF#menu%vn       - enter additional commands\n"
        "%vfF#fuzzyon%vn    - allow fuzzy recognition\n"
        "%vfF#fuzzyoff%vn   - disallow fuzzy recognition\n"
        "%vfF#traceon%vn    - enable debugger and turn the tracer on\n"
        "%vfF#traceoff%vn   - turn the tracer off\n"
    );
}



void LexiconShell::SetMode(const UFString &str)
{
    if (str == L"#fuzzyon")
    {
        fuzzy = true;
        mout->printf("Fuzzy projection is now %vfAON%vn\n");
    }
    else if (str == L"#fuzzyoff")
    {
        fuzzy = false;
        mout->printf("Fuzzy projection is now %vfDOFF%vn\n");
    }
    else if (str == L"#debug")
    {
        debugger = new LexiconDebugger(&*sol_id);
        mout->printf("Debugger is now %vfAON%vn\n");
    }
    else if (str == L"#traceon")
    {
        if (debugger.IsNull())
            debugger = new LexiconDebugger(&*sol_id);

        debugger->Trace(true);

        mout->printf("Tracer is now %vfAON%vn\n");
    }
    else if (str == L"#traceoff")
    {
        if (debugger.NotNull())
            debugger->Trace(false);

        mout->printf("Tracer is now %vfAON%vn\n");
    }
    else if (str == L"#nodebug")
    {
        debugger.Delete();
        mout->printf("Debugger is now %vfDOFF%vn\n");
    }
    else
    {
        mout->printf("%vfCERROR:%vn unknown command %vfE%us%vn\n", str.c_str());
    }

    return;
}


void LexiconShell::Exiting(void)
{
    return;
}


// *******************************************
// Тестируем модуль склонения (без словаря)
// *******************************************
void LexiconShell::TestFlexer(void)
{
    while (true)
    {
        UFString cmd = enter_cmd("word> ");

        if (cmd == L"exit")
            break;

        UCString word(cmd.c_str());
        word.to_upper();

        lem::MCollect<UCString> list;
        lem::MCollect<lem::Real1> rels;

        if (sol_id->GetLexAuto().Produce_Dynforms(word, list, rels, UNKNOWN, GetDebugger()))
        {
            for (lem::Container::size_type i = 0; i < list.size(); i++)
            {
                mout->printf("%us (%4.2f)", list[i].c_str(), rels[i].GetFloat());
            }

            mout->eol();

            /*
                 sol_id->GetLexAuto().Generate_Forms_From_Normal(word,list);

                 for( lem::Container::size_type i=0; i<list.size(); i++ )
                  {
                   mout->printf( "%us ", list[i].c_str() );
                  }
            */
        }

        mout->eol();
    }
}


// *******************************************************
// Тестирование стеммера (без словаря) - поиск псевдокорня
// *******************************************************
void LexiconShell::TestStemmer(void)
{
    while (true)
    {
        UFString cmd = enter_cmd("word> ");

        if (cmd == L"exit")
            break;

        UCString word(cmd.c_str());
        word.to_upper();

        lem::MCollect<UCString> roots;
        lem::MCollect<float> str_val;

        sol_id->affix_table->GenerateRoots(word, 0.0, roots, str_val);
        mout->printf("Stems: ");

        for (lem::Container::size_type i = 0; i < roots.size(); i++)
        {
            mout->printf("%us ", roots[i].c_str());
        }

        mout->eol();
    }

    return;
}


void LexiconShell::TestThesaurus()
{
    lem::mout->printf(
        "\n-----------------------\n"
        " %vfE0%vn - exit\n"
        " %vfE1%vn - synonyms\n"
        " %vfE2%vn - translations\n"
        " %vfE3%vn - tagged links\n\n"
        " %vfE4%vn - all links\n\n"
        "Select mode: "
    );

    int k = mkey->ask_int();

    lem::zbool synonyms, translations, all_links;
    if (k == 0)
        return;

    lem::Ptr<Solarix::SG_TagFilter> tags_ptr;


    if (k == 1)
    {
        synonyms = true;
    }
    else if (k == 2)
    {
        translations = true;
    }
    else if (k == 3)
    {
        // Попросим ввести тэг
        lem::mout->printf("Choose a tag from the list:");

        lem::Ptr<ThesaurusTagDefsEnumerator> tags(sol_id->GetSynGram().Get_Net().GetTagDefs().Enumerate());

        while (tags->Fetch())
        {
            lem::mout->printf(" [%vfE%us%vn]", tags->GetName().c_str());
        }

        lem::mout->printf("\n>");
        lem::mout->flush();

        UCString tag_name = mkey->ask_ufstring().c_str();
        const int itag = sol_id->GetSynGram().Get_Net().FindTag(tag_name);
        if (itag == UNKNOWN)
        {
            lem::mout->printf("Tag [%vfE%us%vn] not found\n", tag_name.c_str());
            return;
        }

        const ThesaurusTag &tt = sol_id->GetSynGram().Get_Net().GetTagDefs()[itag];

        UCString tag_value;

        if (tt.CountValues() > 0)
        {
            int ivalue = UNKNOWN;
            lem::mout->printf("Choose a tag value from the list:");
            for (int i = 0; i < tt.CountValues(); ++i)
                lem::mout->printf(" [%vfE%us%vn]", tt[i].c_str());

            lem::mout->printf("\n>");
            lem::mout->flush();
            tag_value = mkey->ask_ufstring().c_str();
            ivalue = tt[tag_value];
            if (ivalue == UNKNOWN)
            {
                lem::mout->printf("Tag value [%vfE%us%vn] not found\n", tag_value.c_str());
                return;
            }
        }

        lem::Collect< std::pair<UCString /*tag*/, UCString /*value*/> > tags_list;
        tags_list.push_back(std::make_pair(tag_name, tag_value));
        tags_ptr = sol_id->GetSynGram().Get_Net().CompileTags(tags_list);
    }
    else
    {
        all_links = true;
    }


    while (true)
    {
        UFString str = enter_cmd("word or phrase> ");

        if (str.empty() || str == L"#exit" || str == L"#bye" || str == L".")
        {
            break;
        }

        if (str == "#menu")
        {
            EnterMenuLoop();
            return;
        }

        ThesaurusQuery(str, synonyms, translations, tags_ptr.IsNull() ? NULL : &*tags_ptr);
    }

    return;
}

void LexiconShell::ThesaurusQuery(
    const UFString &word,
    bool synonyms,
    bool translations,
    const Solarix::SG_TagFilter* tags
)
{
    Show_Semnet(word, synonyms, translations, tags);
    return;
}


void LexiconShell::Show_Semnet(
    const UFString &ua,
    bool synonyms,
    bool translations,
    const Solarix::SG_TagFilter* tags
)
{
    // Попробуем найти словоформы с таким лексическим содержимым.
    LexicalAutomat &la = sol_id->GetLexAuto();

    std::set<int> uresA;
    bool found_words = false;

    if (ua.front() == L'#' && lem::is_int(ua.c_str() + 1))
    {
        uresA.insert(lem::to_int(ua.c_str() + 1));
    }
    else if (ua.length() < lem::UCString::max_len)
    {
        MCollect<Word_Coord> resA;
        Lexem slA(ua.c_str());
        la.TranslateLexem(slA, true);
        RC_Lexem mlA(&slA, null_deleter());

        MCollect<ProjScore> val_list;
        lem::PtrCollect<LA_ProjectInfo> prj_extra_inf;

        // Делаем запрос к Лексическому автомату, который делает проекцию...
        la.ProjectWord(mlA, resA, val_list, prj_extra_inf, LexicalAutomat/*::DynformsMode*/::Wordforms, 0, UNKNOWN, GetDebugger());
        mout->eol();

        // Список без повторов.
        for (lem::Container::size_type ia = 0; ia < resA.size(); ia++)
        {
            const int iEntryA = resA[ia].GetEntry();
            uresA.insert(iEntryA);
            found_words = true;
        }
    }

    for (std::set<int>::const_iterator it = uresA.begin(); it != uresA.end(); ++it)
    {
        const int iEntryA = *it;

        const SG_Entry &eA = sol_id->GetSynGram().GetEntry(iEntryA);

        /*
             if( synonyms || translations )
              {
               // Для вывода синонимов - особый подход, так как есть специальная процедура,
               // которая учитывает особенности синонимизации причастий, глаголов и деепричастий.

               lem::MCollect<int> key_links;

               if( synonyms )
                la.Synonymize( eA.GetKey(), key_links );
               else if( translations )
                la.Translate( eA.GetKey(), key_links );

               for( lem::Container::size_type j=0; j<key_links.size(); ++j )
                {
                 const int iek = key_links[j];
                 const SG_Entry &e = sol_id->GetSynGram().GetEntry(iek);
                 const int iclass = e.GetClass();
                 const GramClass &cls = sol_id->GetSynGram().classes()[iclass];
                 mout->printf( " %vf9%us%vn : %vfE%us%vn\n", cls.GetName().c_str(), e.GetName().c_str() );
                }
              }
             else
        */

        // получаем диапазон индексов записей в главной таблице тезауруса
        lem::Ptr<WordLinkEnumerator> links(sol_id->GetSynGram().Get_Net().EnumerateWordLinks(eA.GetKey()));

        while (links->Fetch())
        {
            const int id_link = links->GetLinkId();

            const int id_tags = links->GetTagsId();
            SG_TagsList link_tags = links->GetTags();
            bool tags_ok = true;
            if (tags != NULL)
            {
                tags_ok = tags->Match(link_tags);
            }

            if (!tags_ok)
                continue;

            const int ek_C = links->GetEntryKey2();

            const SG_Entry &eC = sol_id->GetSynGram().GetEntry(ek_C);

            const GramCoord &c = sol_id->GetSynGram().coords()[I_NET];

            mout->printf(
                "%6d <%vfA%us%vn>%20Y %vfE%us%vn%35Y link_type=%vf9%d%vn key2=%d"
                , id_link
                , c.GetStateName(links->GetLinkType()).c_str()
                , eC.GetName().c_str()
                , links->GetLinkType()
                , eC.GetKey()
            );

            // Также выведем список тегов
            UFString tags_str;
            Solarix::PrintTags(link_tags, tags_str, sol_id->GetSynGram());
            mout->printf(" %vfD%us%vn", tags_str.c_str());

            mout->eol();
        }
    }

    lem::MCollect<int> cx_links;
    if (synonyms)
    {
        cx_links.push_back(SYNONYM_link);
        cx_links.push_back(SEX_SYNONYM_link);
    }
    else if (translations)
    {
        cx_links.push_back(TO_SPANISH_link);
        cx_links.push_back(TO_GERMAN_link);
        cx_links.push_back(TO_CHINESE_link);
        cx_links.push_back(TO_POLAND_link);
        cx_links.push_back(TO_ITALIAN_link);
        cx_links.push_back(TO_PORTUGUAL_link);
        cx_links.push_back(TO_ENGLISH_link);
        cx_links.push_back(TO_RUSSIAN_link);
        cx_links.push_back(TO_FRENCH_link);
        cx_links.push_back(TO_JAPANESE_link);
    }

    // Найдем и выведем сложные связки
    bool found_phrases = false;

    int id_phrase = sol_id->GetSynGram().GetStorage().FindPhrase(ua, true);
    if (id_phrase != UNKNOWN)
    {
        found_phrases = true;

        lem::Ptr<PhraseLinkEnumerator> links(sol_id->GetSynGram().Get_Net().EnumeratePhraseLinks(id_phrase, cx_links));
        const GramCoord &c = sol_id->GetSynGram().coords()[I_NET];

        while (links->Fetch())
        {
            const int id_link = links->GetLinkId();
            const int id_phrase2 = links->GetIdPhrase2();
            SG_TagsList tags = links->GetTags();

            SG_Phrase phrase2;
            sol_id->GetSynGram().GetStorage().GetPhrase(id_phrase2, phrase2);

            mout->printf("%6d <%vfA%us%vn> %vfE%us%vn id_phrase=%vfE%d%vn \n", id_link, c.GetStateName(links->GetLinkType()).c_str(),
                phrase2.GetText().c_str(), id_phrase2);
        }
    }

    mout->eol();
    if (!found_words && !found_phrases)
    {
        mout->printf("%vfDWord or phrase is not found in lexicon.%vn\n");
    }


    return;
}


void LexiconShell::ProcessFile(const lem::Path &filename)
{
    mout->printf("Start processing [%vfE%us%vn]...\n", filename.GetUnicode().c_str());

    /*
     lem::Ptr<Stream> file( new BinaryFile(filename,true,false) );
     lem::Ptr<lem::Char_Stream::WideStream> reader = lem::Char_Stream::WideStream::GetReader(file);

     UFString sentence;

     while( !reader->eof() )
      {
       wchar_t c = reader->wget();

       if( c==L'.' || c==L'?' || c==L'!' || c==WEOF )
        {
         if( c==WEOF )
          c = L'.';

         sentence.Add_Dirty(c);
         sentence.calc_hash();

         if( sentence.length()>3 )
          {
           // Выполняем анализ.
           mout->printf( "\n%70h-\n#%vfA%d%vn: %vfD%us%vn\n", n_total, sentence.c_str() );

           bool success = Perform_AA( sentence );

           if( success )
            n_success++;
           else
            n_faults++;

           n_total++;
          }

         sentence.clear();
        }
       else
        {
         sentence.Add_Dirty(c);
        }
      }
    */

    return;
}



void LexiconShell::SearchNGrams(const lem::Path &filename)
{
#if defined SOLARIX_PRO

    const lem::int64_t n = sol_id->ngrams.IsNull() ? 0 : sol_id->ngrams->TotalCount();

    if (n == 0)
    {
        lem::mout->printf("Sorry, N-grams database %vfCis not available%vn.\n");
        return;
    }

    mout->printf("There are %vfA%qd%vn Ngrams in database\n", n);

    mout->printf("Start processing [%vfE%us%vn]...\n", filename.GetUnicode().c_str());

    lem::Ptr<lem::Stream> file(new BinaryReader(filename));
    lem::Ptr<lem::Char_Stream::WideStream> reader = lem::Char_Stream::WideStream::GetReader(file);

    UFString line;

    int n_ngram = 0, n_found = 0;

    while (!reader->eof())
    {
        // Каждая N-грамма - на отдельной строке.
        reader->read_line(line);
        if (line.empty())
            return;

        n_ngram++;
        mout->printf("[%vfE%us%vn] ", line.c_str());
        mout->flush();

        lem::MCollect<lem::UCString> words;
        lem::parse(line, words, true);

        float w;
        int iw;

        ElapsedTime et; et.start();

        if (CastSizeToInt(words.size()) == 2)
        {
            if (sol_id->ngrams->FindRawNGrams(words[0], words[1], w, iw))
            {
                n_found++;
                mout->printf("%vfA%d%vn 2gram(s)", iw);
            }
            else
            {
                lem::mout->printf("%vfD2gram is missing%vn");
            }
        }
        else if (CastSizeToInt(words.size()) == 3)
        {
            if (sol_id->ngrams->FindRawNGrams(words[0], words[1], words[2], w, iw))
            {
                n_found++;
                mout->printf("%vfA%d%vn 3gram(s)", iw);
            }
            else
            {
                lem::mout->printf("%vfD3gram is missing%vn");
            }
        }

        et.stop();
        lem::mout->printf(" elapsed time=%vfE%d%vn msec", et.msec());

        mout->eol();
    }

    int perc = n_ngram > 0 ? (100 * n_found) / n_ngram : 0;
    mout->printf("\n\nAll done, %vfA%d%vn ngrams probed, %vfE%d%vn found (%d %%)\n", n_ngram, n_found, perc);

#endif

    return;
}



// *******************************************
// Запросы разного рода к базе N-грамм
// *******************************************
void LexiconShell::TestNGrams()
{
    lem::mout->printf("\n%15h- N-GRAMS DB QUERY MODE %15h-\n\n");

    const lem::int64_t n = sol_id->ngrams.IsNull() ? 0 : sol_id->ngrams->TotalCount();

    if (n == 0)
    {
        lem::mout->printf("Sorry, N-grams database %vfCis not available%vn.\n");
        return;
    }

    lem::mout->printf(
        "There are %F$4vfE%11qd%vn records in N-grams database:\n\n"
        "          %vfA%11qd%vn covalent 2-grams\n\n"
        "          %F$4vfA%11qd%vn raw 1-grams %F$4vfA%11qd%vn literal 1-grams\n"
        "          %F$4vfA%11qd%vn raw 2-grams %F$4vfA%11qd%vn literal 2-grams\n"
        "          %F$4vfA%11qd%vn raw 3-grams %F$4vfA%11qd%vn literal 3-grams\n"
        "          %F$4vfA%11qd%vn raw 4-grams %F$4vfA%11qd%vn literal 4-grams\n"
        "          %F$4vfA%11qd%vn raw 5-grams %F$4vfA%11qd%vn literal 5-grams\n"
        , n
        , sol_id->ngrams->CountCovalent()
        , sol_id->ngrams->CountRaw1()
        , sol_id->ngrams->CountLiteral1()
        , sol_id->ngrams->CountRaw2()
        , sol_id->ngrams->CountLiteral2()
        , sol_id->ngrams->CountRaw3()
        , sol_id->ngrams->CountLiteral3()
        , sol_id->ngrams->CountRaw4()
        , sol_id->ngrams->CountLiteral4()
        , sol_id->ngrams->CountRaw5()
        , sol_id->ngrams->CountLiteral5()
    );

    lem::mout->printf(
        "\n-- Menu: --\n\n"
        "[%vfE0%vn] - %vfCexit%vn\n"
        "[%vfE1%vn] - raw and literal Ngrams query\n"
        "[%vfE2%vn] - covalent 2grams query\n"
        "[%vfE3%vn] - dump grams\n"
        "[%vfA4%vn] - search in WORDS table\n"
    );

    int mode = mkey->ask_int();

    if (mode == 0)
        return;

    if (mode == 1)
    {
        lem::mout->printf(
            "[%vfE0%vn] - %vfCexit%vn\n"
            "[%vfE1%vn]  - search for a %vfF1gram%vn frequency\n"
            "[%vfE2%vn]  - search for a %vfF2gram%vn frequency\n"
            "[%vfE3%vn]  - search for a %vfF3gram%vn frequency\n"
            "[%vfE4%vn]  - search for a %vfF4gram%vn frequency\n"
            "[%vfE5%vn]  - search for a %vfF5gram%vn frequency\n"
            "[%vfE10%vn] - search for the left counterparts in raw 2-grams\n"
            "[%vfE11%vn] - search for the right counterparts in raw 2-grams\n\n"
            "\n%vf8Select a mode:%vn "
        );

        mode = mkey->ask_int();

        if (mode == 0)
            return;

        mode += 1000;
    }
    else if (mode == 2)
    {
        lem::mout->printf(
            "[%vfE0%vn]  - %vfCexit%vn\n"
            "[%vfE1%vn]  - search for the Ngrams containing a word\n"
            "[%vfE2%vn]  - search for the adjectives for noun\n"
            "[%vfE3%vn]  - search for the nouns for adjective\n"
            "[%vfE4%vn]  - search for the adverbs for verb\n"
            "[%vfE5%vn]  - search for the verbs for adverb\n"
            "[%vfE6%vn]  - search for the adverbs for adjective\n"
            "[%vfE7%vn]  - search for the adjectives for adverb\n"
            "[%vfE8%vn]  - search for the nouns for preposition\n"
            "[%vfE9%vn]  - search for the prepositions for noun\n"
            "[%vfE10%vn] - search for the objects for verb\n"
            "[%vfE11%vn] - search for the verbs for actor (noun)\n"
            "\n%vf8Select a mode:%vn "
        );

        mode = mkey->ask_int();

        if (mode == 0)
            return;

        mode += 2000;
    }
    else if (mode == 3)
    {
        lem::mout->printf(
            "[%vfE0%vn] - %vfCexit%vn\n\n"

            "[%vfE1%vn]  - dump all raw %vfF1gram%vn\n"
            "[%vfE2%vn]  - dump all raw %vfF2gram%vn\n"
            "[%vfE3%vn]  - dump all raw %vfF3gram%vn\n"
            "[%vfE4%vn]  - dump all raw %vfF4gram%vn\n"
            "[%vfE5%vn]  - dump all raw %vfF5gram%vn\n\n"

            "[%vfE11%vn]  - dump all literal %vfF1gram%vn\n"
            "[%vfE12%vn]  - dump all literal %vfF2gram%vn\n"
            "[%vfE13%vn]  - dump all literal %vfF3gram%vn\n"
            "[%vfE14%vn]  - dump all literal %vfF4gram%vn\n"
            "[%vfE15%vn]  - dump all literal %vfF5gram%vn\n"

            "\n%vf8Select a mode:%vn "
        );

        mode = mkey->ask_int();

        if (mode == 0)
            return;

        mode += 3000;
    }


    lem::int64_t count = -1;
    switch (mode)
    {
    case 1001: count = sol_id->ngrams->CountRaw1() + sol_id->ngrams->CountLiteral1(); break;
    case 1002: count = sol_id->ngrams->CountRaw2() + sol_id->ngrams->CountLiteral2(); break;
    case 1003: count = sol_id->ngrams->CountRaw3() + sol_id->ngrams->CountLiteral3(); break;
    case 1004: count = sol_id->ngrams->CountRaw4() + sol_id->ngrams->CountLiteral4(); break;
    case 1005: count = sol_id->ngrams->CountRaw5() + sol_id->ngrams->CountLiteral5(); break;

    case 2002: count = sol_id->ngrams->CountAdjsForNoun(); break;
    case 2003: count = sol_id->ngrams->CountAdjsForNoun(); break;
    case 2004: count = sol_id->ngrams->CountAdvsForVerb(); break;
    case 2005: count = sol_id->ngrams->CountAdvsForVerb(); break;
    case 2006: count = sol_id->ngrams->CountAdvsForAdj(); break;
    case 2007: count = sol_id->ngrams->CountAdvsForAdj(); break;
    case 2008: count = sol_id->ngrams->CountPreposForNoun(); break;
    case 2009: count = sol_id->ngrams->CountPreposForNoun(); break;
    case 2010: count = sol_id->ngrams->CountObjsForVerb(); break;
    case 2011: count = sol_id->ngrams->CountVerbsForNoun(); break;
    }

    if (count > 0)
    {
        mout->printf("There are %vfE%qd%vn ngrams in the corresponding category\n", count);
    }

    if (mode >= 3000 && mode < 4000)
    {
        bool lemmatized = mode < 3011;
        int order = mode > 3010 ? mode - 3010 : mode - 3000;

        NGramPrinter handler;
        sol_id->ngrams->ForEachRaw(&handler, order, lemmatized, false);

        return;
    }


    lem::mout->printf("Attention: type %vfE#exit%vn or %vfE.%vn to exit\n\n");

    while (true)
    {
        UFString ustr = enter_cmd(": ");
        if (ustr.empty() || to_lower(ustr) == L"#exit" || ustr == L'.')
            break;

        if (ustr == L"#menu")
        {
            EnterMenuLoop();
            return;
        }

        lem::MCollect<lem::UCString> words0;
        lem::parse(ustr, words0, true);
        //sol_id->GetLexAuto().Segmentation(words);

        lem::MCollect<lem::UCString> words;
        MultiwordMerger merger(&sol_id->GetLexAuto());

        for (lem::Container::size_type i = 0; i < words0.size(); ++i)
        {
            merger.Push(lem::to_upper(words0[i]));

            while (merger.IsReady())
            {
                words.push_back(merger.Pop());
            }
        }

        merger.ForceReady();
        while (merger.IsReady())
        {
            words.push_back(merger.Pop());
        }



        if (mode == 1001)
        {
            if (words.size() != 1)
            {
                for (lem::Container::size_type i = 0; i < words.size(); ++i)
                    lem::mout->printf("[%vfE%us%vn] ", words[i].c_str());

                lem::mout->eol();

                lem::mout->printf("Enter 1gram please.\n");
                continue;
            }

            bool found = false;
            float w;
            int iw;

            if (sol_id->ngrams->FindRawNGrams(words[0], w, iw))
            {
                found = true;
                lem::mout->printf("RAW:     number of occurences=%vfE%8d%vn normalized weight=%vfE%f%vn\n", iw, w);
            }

            if (sol_id->ngrams->FindLiteralNGrams(words[0], w, iw))
            {
                found = true;
                lem::mout->printf("LITERAL: number of occurences=%vfE%8d%vn normalized weight=%vfE%f%vn\n", iw, w);
            }

            if (!found)
            {
                lem::mout->printf("%vfD1gram is missing%vn\n");
            }
        }
        else if (mode == 1002)
        {
            if (words.size() != 2)
            {
                for (lem::Container::size_type i = 0; i < words.size(); ++i)
                    lem::mout->printf("[%vfE%us%vn] ", words[i].c_str());

                lem::mout->eol();

                lem::mout->printf("Enter 2gram please.\n");
                continue;
            }

            bool found = false;
            float w;
            int iw;

            if (sol_id->ngrams->FindRawNGrams(words[0], words[1], w, iw))
            {
                found = true;
                lem::mout->printf("RAW:     number of occurences=%vfE%8d%vn normalized weight=%vfE%f%vn\n", iw, w);
            }

            if (sol_id->ngrams->FindLiteralNGrams(words[0], words[1], w, iw))
            {
                found = true;
                lem::mout->printf("LITERAL: number of occurences=%vfE%8d%vn normalized weight=%vfE%f%vn\n", iw, w);
            }

            if (!found)
            {
                lem::mout->printf("%vfD2gram is missing%vn\n");
            }
        }
        else if (mode == 1003)
        {
            if (words.size() != 3)
            {
                for (lem::Container::size_type i = 0; i < words.size(); ++i)
                    lem::mout->printf("[%vfE%us%vn] ", words[i].c_str());

                lem::mout->eol();

                lem::mout->printf("Enter 3gram please.\n");
                continue;
            }

            bool found = false;
            float w;
            int iw;

            if (sol_id->ngrams->FindRawNGrams(words[0], words[1], words[2], w, iw))
            {
                found = true;
                lem::mout->printf("RAW:     number of occurences=%vfE%8d%vn normalized weight=%vfE%f%vn\n", iw, w);
            }

            if (sol_id->ngrams->FindLiteralNGrams(words[0], words[1], words[2], w, iw))
            {
                found = true;
                lem::mout->printf("LITERAL: number of occurences=%vfE%8d%vn normalized weight=%vfE%f%vn\n", iw, w);
            }

            if (!found)
            {
                lem::mout->printf("%vfD3gram is missing%vn\n");
            }
        }
        else if (mode == 1004)
        {
            if (words.size() != 4)
            {
                for (lem::Container::size_type i = 0; i < words.size(); ++i)
                    lem::mout->printf("[%vfE%us%vn] ", words[i].c_str());

                lem::mout->eol();

                lem::mout->printf("Enter 4gram please.\n");
                continue;
            }

            bool found = false;
            float w;
            int iw;

            if (sol_id->ngrams->FindRawNGrams(words[0], words[1], words[2], words[3], w, iw))
            {
                found = true;
                lem::mout->printf("RAW:     number of occurences=%vfE%8d%vn normalized weight=%vfE%f%vn\n", iw, w);
            }

            if (sol_id->ngrams->FindLiteralNGrams(words[0], words[1], words[2], words[3], w, iw))
            {
                found = true;
                lem::mout->printf("LITERAL: number of occurences=%vfE%8d%vn normalized weight=%vfE%f%vn\n", iw, w);
            }

            if (!found)
            {
                lem::mout->printf("%vfD4gram is missing%vn\n");
            }
        }
        else if (mode == 1005)
        {
            if (words.size() != 5)
            {
                for (lem::Container::size_type i = 0; i < words.size(); ++i)
                    lem::mout->printf("[%vfE%us%vn] ", words[i].c_str());

                lem::mout->eol();

                lem::mout->printf("Enter 5gram please.\n");
                continue;
            }

            bool found = false;
            float w;
            int iw;

            if (sol_id->ngrams->FindRawNGrams(words[0], words[1], words[2], words[3], words[4], w, iw))
            {
                found = true;
                lem::mout->printf("RAW:     number of occurences=%vfE%8d%vn normalized weight=%vfE%f%vn\n", iw, w);
            }

            if (sol_id->ngrams->FindLiteralNGrams(words[0], words[1], words[2], words[3], words[4], w, iw))
            {
                found = true;
                lem::mout->printf("LITERAL: number of occurences=%vfE%8d%vn normalized weight=%vfE%f%vn\n", iw, w);
            }

            if (!found)
            {
                lem::mout->printf("%vfD5gram is missing%vn\n");
            }
        }
        else if (mode == 2001)
        {
            // поиск всех N-грамм для одного введенного слова

            if (words.size() != 1)
            {
                for (lem::Container::size_type i = 0; i < words.size(); ++i)
                    lem::mout->printf("[%vfE%us%vn] ", words[i].c_str());

                lem::mout->eol();

                lem::mout->printf("Enter a single word.\n");
                continue;
            }

            UCString word = words.front();
            word.to_upper();
            lem::MCollect<int> ies1;
            sol_id->GetLexAuto().GetAllProjections(word, false, ies1);

            lem::MCollect<std::pair<int/*ientry*/, float> > ies;

            for (lem::Container::size_type i = 0; i < ies1.size(); ++i)
            {
                const int ientry = ies1[i];
                sol_id->ngrams->FindLinkedWords(ientry, ies);
            }

            if (!ies.empty())
            {
                lem::mout->printf("There are %vfE%d%vn linked words:\n", CastSizeToInt(ies.size()));

                for (lem::Container::size_type i = 0; i < ies.size(); i++)
                {
                    const int ie = ies[i].first;
                    const float we = ies[i].second;
                    const lem::UCString& ename = SG->GetEntry(ie).GetName();
                    lem::mout->printf(" %vfE%us%vn(%5.2f)", ename.c_str(), we);
                }

                lem::mout->eol();
            }

#if defined SOLARIX_PREMIUM

            Solarix::Lexem lex(word);
            sol_id->GetLexAuto().TranslateLexem(lex, true);

            lem::MCollect<lem::UCString> lefts, rights;
            lem::MCollect<float> ws;
            sol_id->ngrams->FindRawNGrams(lefts, lex, ws);

            if (!lefts.empty())
            {
                lem::mout->printf("%vfALeft pairs:%vn");

                for (lem::Container::size_type j = 0; j < lefts.size(); ++j)
                {
                    lem::mout->printf(" %vfE%us%vn(%5.2f)", lefts[j].c_str(), ws[j]);
                }

                lem::mout->eol();
            }

            sol_id->ngrams->FindRawNGrams(lex, rights, ws);

            if (!rights.empty())
            {
                lem::mout->printf("%vfARight pairs:%vn");

                for (lem::Container::size_type j = 0; j < rights.size(); ++j)
                {
                    lem::mout->printf(" %vfE%us%vn(%5.2f)", rights[j].c_str(), ws[j]);
                }

                lem::mout->eol();
            }

#endif
        }
        else if (mode >= 2002 && mode <= 2011)
        {
            // поиск всех 2грамм определенного типа для одного введенного слова

            if (words.size() != 1)
            {
                for (lem::Container::size_type i = 0; i < words.size(); ++i)
                    lem::mout->printf("[%vfE%us%vn] ", words[i].c_str());

                lem::mout->eol();

                lem::mout->printf("Enter a single word.\n");
                continue;
            }

            UCString word = words.front();
            word.to_upper();
            lem::MCollect<int> ies2;
            sol_id->GetLexAuto().GetAllProjections(word, false, ies2);

            // Инфинитивы в глаголы.
            int n0 = CastSizeToInt(ies2.size());
            for (int i = 0; i < n0; i++)
            {
                int ie = ies2[i];
                if (sol_id->GetSynGram().GetEntry(ie).GetClass() == INFINITIVE_ru)
                {
                    lem::MCollect<int> ie_verbs;
                    sol_id->GetLexAuto().Translate_To_Verbs(sol_id->GetSynGram().GetEntry(ie).GetKey(), ie_verbs);
                    for (lem::Container::size_type j = 0; j < ie_verbs.size(); ++j)
                    {
                        int ie_verb = ie_verbs[j];

                        if (ies2.find(ie_verb) == UNKNOWN)
                            ies2.push_back(ie_verb);
                    }
                }
            }

            lem::MCollect<std::pair<int/*ientry*/, float> > ies;

            for (lem::Container::size_type i = 0; i < ies2.size(); ++i)
            {
                const int ientry = ies2[i];

                switch (mode)
                {
                case 4: sol_id->ngrams->FindAdjsForNoun(ientry, ies); break;
                case 5: sol_id->ngrams->FindNounsForAdj(ientry, ies); break;
                case 6: sol_id->ngrams->FindAdvsForVerb(ientry, ies); break;
                case 7: sol_id->ngrams->FindVerbsForAdv(ientry, ies); break;
                case 8: sol_id->ngrams->FindAdvsForAdj(ientry, ies); break;
                case 9: sol_id->ngrams->FindAdjsForAdv(ientry, ies); break;
                case 10: sol_id->ngrams->FindNounsForPrepos(ientry, ies); break;
                case 11: sol_id->ngrams->FindPreposForNoun(ientry, ies); break;
                case 12: sol_id->ngrams->FindObjsForVerb(ientry, ies); break;
                case 13: sol_id->ngrams->FindVerbsForNoun(ientry, ies); break;
                default: LEM_STOPIT;
                }
            }

            if (!ies.empty())
            {
                lem::mout->printf("There are %vfE%d%vn linked words:\n", CastSizeToInt(ies.size()));

                for (lem::Container::size_type i = 0; i < ies.size(); i++)
                {
                    const int ie = ies[i].first;
                    const float we = ies[i].second;
                    const lem::UCString& ename = SG->GetEntry(ie).GetName();
                    lem::mout->printf(" %vfE%us%vn(%5.2f)", ename.c_str(), we);
                }

                lem::mout->eol();
            }
        }
        else if (mode == 1010 || mode == 1011)
        {
            if (words.size() != 1)
            {
                for (lem::Container::size_type i = 0; i < words.size(); ++i)
                    lem::mout->printf("[%vfE%us%vn] ", words[i].c_str());

                lem::mout->eol();

                lem::mout->printf("Enter a single word.\n");
                continue;
            }


            Solarix::Lexem lex(words.front());
            sol_id->GetLexAuto().TranslateLexem(lex, true);

#if defined SOLARIX_PREMIUM

            for (int k = 0; k < 2; ++k)
            {
                lem::MCollect<lem::UCString> counterparts;
                lem::MCollect<float> ws;

                if (k == 0)
                {
                    if (mode == 1010)
                        sol_id->ngrams->FindRawNGrams(counterparts, lex, ws);
                    else
                        sol_id->ngrams->FindRawNGrams(lex, counterparts, ws);
                }
                else
                {
                    if (mode == 1010)
                        sol_id->ngrams->FindLiteralNGrams(counterparts, lex, ws);
                    else
                        sol_id->ngrams->FindLiteralNGrams(lex, counterparts, ws);
                }


                if (!counterparts.empty())
                {
                    lem::mout->printf("%vfA%s 2gram components:%vn", k == 0 ? "RAW" : "LITERAL");

                    for (lem::Container::size_type j = 0; j < counterparts.size(); ++j)
                    {
                        lem::mout->printf(" %vfE%us%vn(%5.2f)", counterparts[j].c_str(), ws[j]);
                    }

                    lem::mout->eol();
                }
            }

#endif
        }
        else if (mode == 5)
        {
            for (lem::Container::size_type i = 0; i < words.size(); ++i)
            {
                lem::mout->printf("%d [%us] --> ", CastSizeToInt(i), words[i].c_str());
                const int w_id1 = sol_id->ngrams->FindInWordTable(words[i], true);

                if (w_id1 != -1)
                    lem::mout->printf("words.id=%d ", w_id1);

                const int w_id2 = sol_id->ngrams->FindInWordTable(words[i], false);

                if (w_id2 != -1)
                    lem::mout->printf("words_literal.id=%d\n", w_id2);

                if (w_id1 == -1 && w_id2 == -1)
                    lem::mout->printf(" %vfCnull%vn\n");
                else
                    lem::mout->eol();
            }
        }
    }

    return;
}




void LexiconShell::SearchByIE()
{
    lem::zbool show_forms, decompile;

    mout->printf(
        "[%vfE0%vn] - exit\n"

        "[%vfE1%vn] - search by key, print entry name only\n"
        "[%vfE2%vn] - search by key, print all wordforms\n"
        "[%vfE3%vn] - search by key, decompile entry\n"
        "[%vfE4%vn] - search for the phrase by ID\n"

        "---------------------------\n"
        "Enter your choise:"
    );

    const int k = mkey->ask_int();

    if (k == 0)
        return;

    show_forms = k == 2;
    decompile = k == 3;

    for (;;)
    {
        UFString str = enter_cmd(": ");

        if (str == L"#exit")
        {
            break;
        }

        if (str == "#menu")
        {
            EnterMenuLoop();
            return;
        }

        if (str == L"#help")
        {
            ShowHelp();
            continue;
        }

        try
        {
            int ie = UNKNOWN;

            if (str == L".")
                break;

            if (lem::to_int(str.c_str(), &ie))
            {
                if (k == 4)
                {
                    SG_Phrase frz;
                    if (SG->GetStorage().GetPhrase(ie, frz))
                    {
                        PrintPhrase(sol_id->GetSynGram(), frz);
                    }

                    continue;
                }

                const SG_Entry &e = SG->GetEntry(ie);
                const lem::UCString& ename = e.GetName();
                int iclass = e.GetClass();
                lem::UCString class_name = lem::is_quantor(iclass) ? L"" : SG->classes()[iclass].GetName();
                lem::mout->printf("%vfA%us%vn : %vfE%us%vn\n", class_name.c_str(), ename.c_str());

                if (show_forms)
                {
                    mout->printf("Forms:\n");
                    for (lem::Container::size_type i = 0; i < e.forms().size(); ++i)
                    {
                        mout->printf("%d: %vfE%us%vn\n", i, e.forms()[i].name().c_str());
                    }
                }

                if (decompile)
                {
                    e.SaveTxt(*mout, *SG);
                }
            }
            else
            {
                lem::mout->printf("Integer is expected.\n");
            }
        }
        catch (...)
        {
            lem::mout->printf("Error - it's possible that this IE is not valid\n");
        }
    }

    return;
}



void LexiconShell::ShowParadigma(void)
{
    LexicalAutomat &la = sol_id->GetLexAuto();

    (*mout) << "Enter basic word forms.\n";

    for (;;)
    {
        UFString str = enter_cmd(": ");

        if (str == "." || str == "#exit")
            break;

        if (str == L"#help" || str == L"?")
        {
            ShowHelp();
            continue;
        }

        if (str == "#menu")
        {
            EnterMenuLoop();
            return;
        }

        if (str.front() == L'#')
        {
            SetMode(str);
            continue;
        }


        Solarix::Lexem lword(str.c_str());
        la.TranslateLexem(lword, true);
        RC_Lexem ml(&lword, null_deleter());

        MCollect<int> shown_ie;

        MCollect<Word_Coord> ies;
        MCollect<ProjScore> val_list;
        lem::PtrCollect<LA_ProjectInfo> prj_extra_inf;

        la.ProjectWord(ml, ies, val_list, prj_extra_inf, LexicalAutomat/*::DynformsMode*/::Wordforms, 0, UNKNOWN, GetDebugger());

        for (lem::Container::size_type i = 0; i < ies.size(); ++i)
        {
            const int ie = ies[i].GetEntry();
            if (!lem::is_quantor(ie) && shown_ie.find(ie) == UNKNOWN)
            {
                shown_ie.push_back(ie);

                const SG_Entry &e = sol_id->GetSynGram().GetEntry(ie);
                const SG_Class &c = sol_id->GetSynGram().GetClass(e.GetClass());

                lem::mout->printf("%us:%us ie=%d\n", e.GetName().c_str(), c.GetName().c_str(), ie);

                for (lem::Container::size_type j = 0; j < e.forms().size(); ++j)
                {
                    const SG_EntryForm &f = e.forms()[j];
                    lem::mout->printf("%vfE%us%vn ", f.name().c_str());

                    if (!f.coords().empty() && do_print_proj_coords)
                    {
                        mout->printf("\n   { ");
                        for (Container::size_type i = 0; i < f.coords().size(); i++)
                        {
                            f.coords()[i].SaveTxt(*mout, *SG);
                            mout->printf(" ");
                        }
                        mout->printf("}");
                    }

                    lem::Ptr<LS_ResultSet> rs = SG->GetStorage().ListAuxForms(e.GetKey(), CastSizeToInt(j));
                    int record_count = 0;
                    while (rs->Fetch())
                    {
                        int id_aux_type = rs->GetInt(1);
                        lem::UFString aux_data = rs->GetUFString(2);
                        lem::UCString aux_type = SG->GetAuxFormTypes()[id_aux_type];
                        mout->printf(" %vfD%us=%us%vn", aux_type.c_str(), aux_data.c_str());
                    }

                    mout->eol();
                }
            }
        }
    }

    return;
}


void LexiconShell::ShowLexiconStatistics(void)
{
    const int nentry = SG->GetnEntry();
    const int nphrase = SG->GetnPhrase();
    const int nlinks = SG->Get_Net().CountAllLinks();
    const int nsynonyms = SG->Get_Net().CountLinks(Tree_Link(SYNONYM_link));
    const lem::int64_t ngrams = sol_id->GetNgrams() == NULL ? 0 : sol_id->GetNgrams()->TotalCount();

    const int ntransl = SG->Get_Net().CountLinks(Tree_Link(TO_RUSSIAN_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_ENGLISH_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_JAPANESE_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_FRENCH_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_CHINESE_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_SPANISH_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_GERMAN_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_PORTUGUAL_link));

    int nforms = 0;
    std::set<lem::UCString> lexems;

    // подсчитаем распределение статей по языкам

    lem::MCollect< lem::triple<int/*language id*/, UCString/*language name*/, int /*# of entries*/> > entry_counts;

    lem::Ptr<WordEntryEnumerator> wenum(SG->GetEntries().ListEntries());
    while (wenum->Fetch())
    {
        const int ekey = wenum->GetId();
        const SG_Entry &e = wenum->GetItem();

        nforms += CastSizeToInt(e.forms().size());

        for (lem::Container::size_type p = 0; p < e.forms().size(); ++p)
            lexems.insert(e.forms()[p].name());

        if (e.GetName() != Solarix::SOL_UNKNOWN_ENTRY_NAME)
        {
            const int id_class = e.GetClass();
            if (!lem::is_quantor(id_class))
            {
                int id_lang = SG->GetClass(id_class).GetLanguage();
                if (!lem::is_quantor(id_lang))
                {
                    bool found = false;
                    for (lem::Container::size_type j = 0; j < entry_counts.size(); ++j)
                        if (entry_counts[j].first == id_lang)
                        {
                            entry_counts[j].third++;
                            found = true;
                            break;
                        }

                    if (!found)
                        entry_counts.push_back(lem::make_triple(id_lang, SG->languages()[id_lang].GetName(), 1));
                }
            }
        }
    }

    mout->printf("Dictionary status:\n"
        "%4h %vfE%8d%vn entries, %vfE%d%vn wordforms, %vfE%d%vn unique lexemes\n"
        , nentry, nforms, CastSizeToInt(lexems.size()));

    mout->printf("%4h %vfE%8d%vn phrases\n", nphrase);

    std::sort(entry_counts.begin(), entry_counts.end(), lang_sorter);

    for (lem::Container::size_type i = 0; i < entry_counts.size(); ++i)
        if (entry_counts[i].third > 0)
        {
            lem::mout->printf("%4h %vfA%8d%vn %us entries\n", entry_counts[i].third, entry_counts[i].second.c_str());
        }

    mout->printf(
        "%4h %vfE%8d%vn thesaurus records (%vfE%d%vn synonyms, %vfE%d%vn translations)\n"
        "%4h %vfE%8qd%vn n-grams\n\n"
        , nlinks, nsynonyms, ntransl, ngrams);

    return;
}


void LexiconShell::ShowThesaurusStatistics(void)
{
    const int nlinks = SG->Get_Net().CountAllLinks();
    const int nwrd = SG->Get_Net().GetStorage().CountWordLinks(ANY_STATE);
    const int nfrz = SG->Get_Net().GetStorage().CountPhraseLinks(ANY_STATE);

    const int n_synonyms = SG->Get_Net().CountLinks(Tree_Link(SYNONYM_link));
    const int n_antonyms = SG->Get_Net().CountLinks(Tree_Link(ANTONYM_link));
    const int n_hyperonyms = SG->Get_Net().CountLinks(Tree_Link(CLASS_link));
    const int n_hyponyms = SG->Get_Net().CountLinks(Tree_Link(MEMBER_link));

    const int n_deriv = SG->Get_Net().CountLinks(Tree_Link(TO_VERB_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_INF_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_PERFECT)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_UNPERFECT)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_NOUN_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_ADJ_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_ADV_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_RETVERB)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_GERUND_2_link)) +
        SG->Get_Net().CountLinks(Tree_Link(WOUT_RETVERB));

    const int n_translations = SG->Get_Net().CountLinks(Tree_Link(TO_ENGLISH_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_RUSSIAN_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_FRENCH_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_SPANISH_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_GERMAN_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_CHINESE_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_POLAND_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_ITALIAN_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_PORTUGUAL_link)) +
        SG->Get_Net().CountLinks(Tree_Link(TO_JAPANESE_link));

    lem::mout->printf("\n ------- Thesaurus status ------\n"
        "Total number of links ... %vfE%W8ArF$3d%vn\n"
        "Word links .............. %vfE%W8ArF$3d%vn\n"
        "Phrase links ............ %vfE%W8ArF$3d%vn\n"
        "Synonyms ................ %vfE%W8ArF$3d%vn\n"
        "Antonyms ................ %vfE%W8ArF$3d%vn\n"
        "Hypernyms ............... %vfE%W8ArF$3d%vn\n"
        "Hyponyms ................ %vfE%W8ArF$3d%vn\n"
        "Translations ............ %vfE%W8ArF$3d%vn\n"
        "Derivatives ............. %vfE%W8ArF$3d%vn\n"
        , nlinks, nwrd, nfrz, n_synonyms, n_antonyms, n_hyperonyms, n_hyponyms, n_translations, n_deriv
    );

    const int nentry = SG->GetnEntry();

    // подсчитаем кол-во синонимизированных слов
    int nsynword = 0;
    std::set<int> dummy;
    lem::MCollect<Tree_Link> syn_links;
    syn_links.push_back(Tree_Link(SYNONYM_link));

    // Для анализа кол-ва переводов
    int ntranslated = 0;
    lem::MCollect<Tree_Link> tr_links;
    tr_links.push_back(Tree_Link(TO_RUSSIAN_link));
    tr_links.push_back(Tree_Link(TO_ENGLISH_link));
    tr_links.push_back(Tree_Link(TO_JAPANESE_link));
    tr_links.push_back(Tree_Link(TO_FRENCH_link));
    tr_links.push_back(Tree_Link(TO_CHINESE_link));
    tr_links.push_back(Tree_Link(TO_SPANISH_link));
    tr_links.push_back(Tree_Link(TO_GERMAN_link));
    tr_links.push_back(Tree_Link(TO_PORTUGUAL_link));

    lem::Ptr<WordEntryEnumerator> wenum(SG->GetEntries().ListEntries());
    while (wenum->Fetch())
    {
        const int ekey = wenum->GetId();
        dummy.clear();
        SG->Get_Net().Find_Linked_Entries(ekey, 0, dummy, false, true, &syn_links);
        if (!dummy.empty())
            nsynword++;

        dummy.clear();
        SG->Get_Net().Find_Linked_Entries(ekey, 0, dummy, false, true, &tr_links);
        if (!dummy.empty())
            ntranslated++;
    }

    const float perc_synonymized = nsynword*100.0F / nentry;
    const float perc_translated = ntranslated*100.0F / nentry;

    mout->printf("Lexicon: %vfE%8d%vn entries, %3.0rf%% synonymized, %3.0rf%% translated\n"
        , nentry, perc_synonymized, perc_translated);

    return;
}

void LexiconShell::ShowStatistics(void)
{
    ShowThesaurusStatistics();
    ShowLexiconStatistics();
    return;
}



void LexiconShell::SearchByName(void)
{
    LexicalAutomat &la = sol_id->GetLexAuto();

    for (;;)
    {
        UFString str = enter_cmd(": ");

        if (str == "." || str == L"#exit")
        {
            break;
        }

        if (str == L"#help" || str == L"?")
        {
            ShowHelp();
            continue;
        }

        if (str == "#menu")
        {
            EnterMenuLoop();
            return;
        }

        lem::MCollect<int> ientries;

        // Префиксный поиск задается так КОШ*
        if (str.back() == L'*')
        {
            lem::Ptr<PrefixEntrySearcher> pes = sol_id->GetPrefixEntrySearcher();
            if (pes.IsNull())
            {
                lem::mout->printf("Prefix entry searcher is not available\n");
            }
            else
            {
                str.to_upper();
                pes->Search(lem::left(str, str.length() - 1).c_str(), ientries);
            }
        }
        else
        {
            Solarix::Lexem lword(str.c_str());
            la.TranslateLexem(lword, true);

            // Пробуем найти словарную статью с таким именем.
            SG->FindEntries(lword, ientries);
        }

        mout->eol();

        if (!ientries.empty())
        {
            for (lem::Container::size_type k = 0; k < ientries.size(); ++k)
            {
                const int ientry = ientries[k];

                // Статья найдена, ientry - порядковый индекс статьи.

                const SG_Entry &e = SG->GetEntry(ientry);
                const int iclass = e.GetClass();
                const UCString &class_name = SG->classes()[iclass].GetName();

                mout->printf(
                    "Entry [%vfA%us%vn:%vfF%us%vn]: key=%vfE%d%vn iclass=%vfE%d%vn\n"
                    , class_name.c_str(), e.GetName().c_str(), e.GetKey(), iclass
                );

                // выведем дополнительные данные для статьи, если они есть.
                lem::Ptr<LS_ResultSet> aux = SG->GetStorage().ListAuxEntryData(e.GetKey());
                while (aux->Fetch())
                {
                    int id_aux_type = aux->GetInt(1);
                    lem::UFString aux_data = aux->GetUFString(2);
                    UCString aux_type = SG->GetAuxFormTypes()[id_aux_type];
                    mout->printf("%vfD%us=%us%vn\n", aux_type.c_str(), aux_data.c_str());
                }
            }
        }
    }

    return;
}


LexiconDebugger* LexiconShell::GetDebugger(void)
{
    if (debugger.IsNull())
        return nullptr;
    else
        return &*debugger;
}





void LexiconShell::ShowSyllabicBreaks(void)
{
    LexicalAutomat &la = sol_id->GetLexAuto();
    GraphGram &gg = sol_id->GetGraphGram();

    mout->printf("Enter '#exit' to quit\n\n");

    for (;;)
    {
        UFString str = enter_cmd(": ");

        if (str == L"#exit")
            break;

        if (str == "#menu")
        {
            EnterMenuLoop();
            return;
        }

        if (str.front() == L'#')
        {
            SetMode(str);
            continue;
        }

        UCString word(str.c_str());

        const int id_language = la.GuessLanguage(str);

        lem::MCollect<lem::UCString> syllabs;

        gg.FindSyllabs(word, id_language, false, syllabs, GetDebugger());

        for (auto& syllab : syllabs)
        {
            lem::mout->printf("%us\n", syllab.c_str());
        }

        lem::mout->eol();
    }

    return;
}
