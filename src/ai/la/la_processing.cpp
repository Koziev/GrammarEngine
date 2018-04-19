// -----------------------------------------------------------------------------
// File LA_PROCESSING.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//
// Content:
//
// Часть кода Лексического Автомата, то есть реализация части методов класса
// LexicalAutomat. Здесь - все, что касается подготовки фразоблока к работе в
// AA и PA. В частности - проекция мультилексем на Лексикон и микширование
// вариаторов.
//
// 04.09.2009 - доработан алгоритм догадки языка предложения - после проекции
//              делается вторая попытка, что позволяет воспользоваться
//              результатами нечеткой проекции.
// -----------------------------------------------------------------------------
//
// CD->01.09.1997
// LC->17.04.2018
// --------------

#include <lem/math/integer_math.h>
#include <lem/conversions.h>
#include <lem/logfile.h>

#include <lem/solarix/dictionary.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/variator.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/tree_node.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/WordEntryEnumerator.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/Symbols.h>
#include <lem/solarix/Symbol.h>
#include <lem/solarix/LanguageEnumerator.h>
#include <lem/solarix/WordFormEnumerator.h>
#include <lem/solarix/LA_Recognizer.h>
#include <lem/solarix/LA_RecognitionTrace.h>
#include <lem/solarix/LA_Preprocessor.h>
#include <lem/solarix/casing_coder.h>
#include <lem/solarix/LA_WordProjectionBuffer.h>
#include <lem/solarix/dsa_main.h>
#include <lem/solarix/Paradigma.h>
#include <lem/solarix/EndingStat.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/WideStringUcs4.h>
#include <lem/Ucs4ToWideString.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/SG_EntryGroup.h>
#include <lem/solarix/AuxFormTypes.h>
#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/TextRecognitionParameters.h>
#include <lem/solarix/la_autom.h>


using namespace lem;
using namespace Solarix;

// Константы для указания стратегии проецирования заданий - комментарии ниже.
namespace Solarix
{
    enum {
        SOL_LA_MAKE_DEEPER,
        SOL_LA_JUST_PROJECT
    };
}

static const wchar_t UNKNOWN_ENTRY_NAME[] = L"UNKNOWNENTRY";





#if defined SOL_CAA
Solarix::Word_Form* LexicalAutomat::ProjectWord(
    const lem::UCString &word,
    int WordIndex,
    int WordParts,
    const TokenizationTags * tags,
    const TextRecognitionParameters & params,
    LA_RecognitionTrace *trace
)
{
    RC_Lexem normalized(new Lexem(word));
    TranslateLexem(*normalized, true, params.language_ids.front());

    MLProjList proj(normalized, word, WordIndex, WordParts);

    if (params.AllowPrimaryFuzzyWordRecog)
    {
        proj.set_Allow_Fuzzy(true);
    }

    proj.set_Dynforms(params.AllowDynform);

    if (tags != nullptr)
    {
        lem::Ptr<TokenizationTags> t(const_cast<TokenizationTags*>(tags), null_deleter());
        proj.set_Tags(t);
    }

    ProjectJob(proj, params.language_ids.front(), true, trace);

    Word_Form * wordform = proj.GetVersionedForm();

    return wordform;
}
#endif




#if defined SOL_CAA
void LexicalAutomat::FindParameters()
{
    // Параметр определяет, на сколько букв может отличаться проецируемое
    // слово и лексема в Лексиконе, чтобы признать несовпадение случайной
    // ошибкой.
    if (NMISSMAX == -1)
    {
        NMISSMAX = 1;
        const int icr = params().Find(L"NMISSMAX");
        if (icr != UNKNOWN)
            NMISSMAX = params()[icr].GetInt();
    }

    if (MIN_PROJ_SCORE == 0)
    {
        MIN_PROJ_SCORE = -50.0f;
        const int icr = params().Find(L"MIN_PROJ_SCORE");
        if (icr != UNKNOWN)
            MIN_PROJ_SCORE = params()[icr].GetInt();
    }

    return;
}
#endif // endif defined SOL_CAA



static inline float Real1ToScore(lem::Real1 fp1)
{
    if (fp1.GetInt() == 100)
        return 0.0f;

    return -(1.0f - fp1.GetFloat())*10.0f;
}



#if defined SOL_CAA
bool LexicalAutomat::ProjectJob(MLProjList &proj, int id_lang, bool allow_unknown_entries, LA_RecognitionTrace *trace)
{
    // Нам нужно засечь факт изменения задания...
    proj.ClearChange();

    lem::MCollect<Word_Coord> prj_found_list;
    lem::MCollect<ProjScore> prj_val_list;
    lem::PtrCollect<LA_ProjectInfo> prj_extra_inf;

    const RC_Lexem &word = proj.GetContent();

    if (!proj.get_Group().empty())
    {
        // Слово описано через грамматические категории, поэтому как таковая проекция
        // сводится к поиску по описанию. Причем возможна только одна проекция.
        Project_1(
            word,
            *proj.GetOrgWord(),
            0.0f,
            prj_found_list,
            prj_val_list,
            prj_extra_inf,
            false,
            proj.get_Allow_Fuzzy(),
            true,
            id_lang,
            trace
        );

        LEM_CHECKIT_Z(prj_found_list.size() == prj_val_list.size());
        LEM_CHECKIT_Z(prj_found_list.size() == prj_extra_inf.size());
        LEM_CHECKIT_Z(!prj_found_list.empty());
        AddResults(proj, prj_found_list, prj_val_list, prj_extra_inf);
    }
    else
    {
        bool added = false;

        /*
           // 1. Через кэш
           if( word_proj->Project(
                                  word,
                                  prj_found_list,
                                  prj_val_list,
                                  prj_extra_inf,
                                  id_lang,
                                  trace
                                 ) )
            {
             LEM_CHECKIT_Z( prj_found_list.size()==prj_val_list.size() );
             LEM_CHECKIT_Z( prj_found_list.size()==prj_extra_inf.size() );
             added = AddResults( proj, prj_found_list, prj_val_list, prj_extra_inf );
            }
           else*/

        {
            // проекция исходного слова как оно пришло на вход.

            if (Project_1(
                word,
                *proj.GetOrgWord(),
                0.0f,
                prj_found_list,
                prj_val_list,
                prj_extra_inf,
                do_update_cache,
                proj.get_Allow_Fuzzy(),
                true,
                id_lang,
                trace
            ))
            {
                LEM_CHECKIT_Z(prj_found_list.size() == prj_val_list.size());
                LEM_CHECKIT_Z(prj_found_list.size() == prj_extra_inf.size());
                added = AddResults(proj, prj_found_list, prj_val_list, prj_extra_inf);
            }
            else
            {
                bool all_dynforms_are_precise = true;

                if (proj.get_Allow_Fuzzy())
                {
                    // может это известная опечатка?
                    lem::MCollect<lem::UCString> corrected_word;
                    if (FindMisspeltWord(*word, corrected_word, id_lang))
                    {
                        // да, пробуем теперь проекцию скорректированного слова
                        for (lem::Container::size_type i2 = 0; i2 < corrected_word.size(); ++i2)
                        {
                            RC_Lexem word2(new Lexem(corrected_word[i2]));

                            if (Project_1(
                                word2,
                                *proj.GetOrgWord(),
                                0.0f,
                                prj_found_list,
                                prj_val_list,
                                prj_extra_inf,
                                do_update_cache,
                                false,
                                true,
                                id_lang,
                                trace
                            ))
                            {
                                added = AddResults(proj, prj_found_list, prj_val_list, prj_extra_inf);
                            }
                        }
                    }
                }

                if (!added && proj.get_Dynforms())
                {
                    // отсекаем продуктивные приставки и окончания, пытаемся найти слово после усечения.
                    lem::MCollect<UCString> dynforms;
                    lem::MCollect<lem::Real1> dynform_rels;
                    dynforms.reserve(16);
                    if (Produce_Dynforms(*word, dynforms, dynform_rels, id_lang, trace))
                    {
                        /*
                                 #if LEM_DEBUGGING==1
                                 mout->printf( "n_pi=%d\n", dynforms.size() );
                                 for( int i=0; i<dynforms.size(); i++ )
                                  {
                                   mout->printf( "[%vfE%us%vn]", dynforms[i].c_str() );
                                  }
                                 #endif
                        */

                        for (Container::size_type i = 0; i < dynforms.size(); i++)
                        {
                            Lexem *dynform_str = new Lexem(dynforms[i]);
                            TranslateLexem(*dynform_str, true, id_lang);
                            RC_Lexem dynform(dynform_str);
                            if (Project_1(
                                dynform,
                                *dynform_str,
                                Real1ToScore(dynform_rels[i]),
                                prj_found_list,
                                prj_val_list,
                                prj_extra_inf,
                                do_update_cache,
                                proj.get_Allow_Fuzzy(),
                                false,
                                id_lang,
                                trace
                            ))
                            {
                                added = added || AddResults(proj, prj_found_list, prj_val_list, prj_extra_inf);
                                if (dynform_rels[i] != Real1(100))
                                    all_dynforms_are_precise = false;
                            }
                        }

                        LEM_CHECKIT_Z(prj_found_list.size() == prj_val_list.size());
                        LEM_CHECKIT_Z(prj_found_list.size() == prj_extra_inf.size());
                    }
                }

                if ((!added || !all_dynforms_are_precise) && proj.get_Allow_Fuzzy())
                {
                    // нечеткая проекция.
                    if (Project_3(
                        word,
                        *proj.GetOrgWord(),
                        0.0f,
                        prj_found_list,
                        prj_val_list,
                        prj_extra_inf,
                        id_lang,
                        trace
                    ))
                    {
                        LEM_CHECKIT_Z(prj_found_list.size() == prj_val_list.size());
                        LEM_CHECKIT_Z(prj_found_list.size() == prj_extra_inf.size());
                        added = AddResults(proj, prj_found_list, prj_val_list, prj_extra_inf);
                    }
                }
            }
        }

        if (!added && allow_unknown_entries)
        {
            const int iue = GetUnknownEntryKey();

            if (iue != UNKNOWN)
            {
                prj_found_list.push_back(Word_Coord(iue, 0));
                prj_val_list.push_back(ProjScore(0.0f));
                prj_extra_inf.push_back(nullptr);
                AddResults(proj, prj_found_list, prj_val_list, prj_extra_inf);
            }
        }
    }

    LEM_CHECKIT_Z(prj_found_list.size() == prj_val_list.size());
    LEM_CHECKIT_Z(prj_found_list.size() == prj_extra_inf.size());

    // Отсортируем проекции согласно частотам.
    proj.SortByFrequency(GetDict());
    proj.Projected();

    return proj.IsChanged();
}
#endif // defined SOL_CAA


int LexicalAutomat::GetUnknownEntryKey()
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_unknown_entry_key);
#endif

    if (unknown_entry_key == UNKNOWN)
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        if (unknown_entry_key == UNKNOWN)
        {
            unknown_entry_key = GetDict().GetSynGram().GetEntries().GetUnknownEntryKey(); // GetDict().GetSynGram().FindEntry( UNKNOWN_ENTRY_NAME, ANY_STATE, true );
        }
    }

    return unknown_entry_key;
}



int LexicalAutomat::GetWordformFrequency(int id_entry, int iform)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_wordform_frequency);
#endif

    std::pair<int, int> key(id_entry, iform);
    auto it = wordform_frequency.find(key);
    if (it == wordform_frequency.end())
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        it = wordform_frequency.find(key);
        if (it == wordform_frequency.end())
        {
            std::pair<bool, int> freq = GetStorage().GetWordformFrequency(id_entry, iform);
            wordform_frequency.insert(std::make_pair(key, freq.second));
            return freq.second;
        }
        else
        {
            return it->second;
        }
    }
    else
    {
        return it->second;
    }
}




#if defined SOL_CAA
// ********************************************************************
// Генерируем динамические формы - убираем и добавляем к оригинальной
// мультилексеме приставки и суффиксы на основе правил словаря. Обычно
// генерируются нормальные формы слов.
// ********************************************************************
bool LexicalAutomat::Produce_Dynforms(
    const UCString &lex, // оригинальное слово
    lem::MCollect<UCString> &list,
    lem::MCollect<lem::Real1> &dynform_rels,
    int id_language,
    LA_RecognitionTrace *trace
)
{
    return preprocessor->Crop(lex, list, dynform_rels, id_language, trace);
}




// **************************************************************************************
// Пробует формировать динамические формы и проецировать их на справочник лексем. Если
// будет успех, то вернет ientry проекции.
// **************************************************************************************
int LexicalAutomat::Project_Dynforms(
    const UCString &lex,  // оригинальное слово
    int id_language,
    const LD_Seeker &seeker
) const
{
    lem::MCollect<UCString> list;
    lem::MCollect<lem::Real1> rels;
    if (preprocessor->Crop(lex, list, rels, id_language, nullptr))
    {
        int ientry = UNKNOWN;
        for (lem::Container::size_type i = 0; i < list.size(); ++i)
        {
            if ((ientry = seeker.Find(list[i], false)) != UNKNOWN)
            {
                return ientry;
            }
        }
    }

    return UNKNOWN;
}





// *************************************************************************
// По заданной нормальной (базовой) форме генерируем всевозможные
// производные (склонение, спряжение) на основе специальных правил-парадигм.
// *************************************************************************
bool LexicalAutomat::Generate_Forms_From_Normal(
    const UCString &word,
    lem::MCollect<UCString> &list
)
{
    SG_DeclensionAutomat& dsa = GetSynGram().Get_DSA();

    // Попробуем найти парадигму.
    lem::MCollect<int> idecl;
    dsa.FindDecl(word, idecl);

    if (!idecl.empty())
    {
        Lexem lex(word);
        TranslateLexem(lex, false);

        MCollect<Lexem> res;

        for (lem::Container::size_type i = 0; i < idecl.size(); i++)
        {
            res.clear();
            dsa.GetDecl(idecl[i]).GenerateForms(lex, res, GetSynGram(), dsa);

            for (lem::Container::size_type j = 0; j < res.size(); j++)
            {
                list.push_back(res[j]);
            }
        }

        return true;
    }

    return false;
}

#endif



#if defined SOL_CAA
/*****************************************************************
 Делаем попытку спроецировать мультилексему из задания proj на
 Лексикон методом типа method. Входной параметр use_original
 равен true, если проецируем ИСХОДНОЕ представление мультилексемы,
 иначе - проецируем фонетические инварианты.
******************************************************************/
void LexicalAutomat::Project(
    MLProjList &proj,
    int method,
    bool use_original,
    int id_lang,
    LA_RecognitionTrace *trace
)
{
    lem::MCollect<Word_Coord> prj_found_list;
    lem::MCollect<ProjScore> prj_val_list;
    lem::PtrCollect<LA_ProjectInfo> prj_extra_inf;

    if (!proj.get_Group().empty())
    {
        // Слово описано через грамматические категории, поэтому как таковая проекция
        // сводится к поиску по описанию. Причем возможна только одна проекция.
        if (proj.GetStadia() > 0)
            return;

        proj.NextStadia();

        const RC_Lexem &word = proj.GetContent();

        Project_1(
            word,
            *proj.GetOrgWord(),
            0.0f,
            prj_found_list,
            prj_val_list,
            prj_extra_inf,
            false,
            false,
            true,
            id_lang,
            trace
        );

        LEM_CHECKIT_Z(prj_found_list.size() == prj_val_list.size());
        LEM_CHECKIT_Z(prj_found_list.size() == prj_extra_inf.size());
        LEM_CHECKIT_Z(!prj_found_list.empty());
    }
    else if (use_original)
    {
        // В число оригиналов входят и "ломанные"
        int n_org = 1 + CastSizeToInt(proj.get_Broken().size());

        for (int iorg = 0; iorg < n_org; iorg++)
        {
            // Для исходной мультилексемы.
            const RC_Lexem &word = !iorg ?
                proj.GetContent() :
                proj.get_Broken()[iorg - 1];

            switch (method)
            {
            case 0:
            {
                word_proj->Project(
                    word,
                    prj_found_list,
                    prj_val_list,
                    prj_extra_inf,
                    id_lang,
                    trace
                );

                LEM_CHECKIT_Z(prj_found_list.size() == prj_val_list.size());
                LEM_CHECKIT_Z(prj_found_list.size() == prj_extra_inf.size());

                break;
            }

            case 1:
                Project_1(
                    word,
                    *proj.GetOrgWord(),
                    0.0f,
                    prj_found_list,
                    prj_val_list,
                    prj_extra_inf,
                    do_update_cache,
                    proj.get_Allow_Fuzzy(),
                    true,
                    id_lang,
                    trace
                );
                LEM_CHECKIT_Z(prj_found_list.size() == prj_val_list.size());
                LEM_CHECKIT_Z(prj_found_list.size() == prj_extra_inf.size());
                break;

                /*
                      case 2:
                       Project_2(
                                 word,
                                 proj.get_Miss_Parameter(),
                                 prj_found_list,
                                 prj_val_list,
                                 prj_extra_inf,
                                 id_lang,
                                 trace
                                );
                       LEM_CHECKIT_Z( prj_found_list.size()==prj_val_list.size() );
                       LEM_CHECKIT_Z( prj_found_list.size()==prj_extra_inf.size() );
                       break;
                */

#if defined SOL_CAA
            case 3:
                Project_3(
                    word,
                    *proj.GetOrgWord(),
                    0.0f,
                    prj_found_list,
                    prj_val_list,
                    prj_extra_inf,
                    id_lang,
                    trace
                );
                LEM_CHECKIT_Z(prj_found_list.size() == prj_val_list.size());
                LEM_CHECKIT_Z(prj_found_list.size() == prj_extra_inf.size());
                break;
#else
            case 3:
                break;
#endif

            default: LEM_STOPIT;
            }
        }
    }
    else
    {
        /*
           // Для фонетических инвариантов.

           const int nfi = proj.GetnPhonInv();
           for( int pi=0; pi<nfi; pi++ )
            {
             // Каждый фонетический инвариант имеет свою степень недостоверности,
             // возникающую во время его получения. Поэтому возвращаемый список
             // достоверностей проекций мы домножаем на достоверность самого ф.и.
             const RC_Lexem &word = proj.GetPhonInv(pi);

             LEM_CHECKIT_Z( prj_found_list.size()==prj_val_list.size() );
             LEM_CHECKIT_Z( prj_found_list.size()==prj_extra_inf.size() );
             const lem::Container::size_type ibegin = prj_found_list.size();

             switch(method)
             {
              case 0:
               {
                word_proj->Project(
                                   word,
                                   prj_found_list,
                                   prj_val_list,
                                   prj_extra_inf,
                                   id_lang,
                                   trace
                                  );

                LEM_CHECKIT_Z( prj_found_list.size()==prj_val_list.size() );
                LEM_CHECKIT_Z( prj_found_list.size()==prj_extra_inf.size() );

                break;
               }

              case 1:
               {
                Project_1(
                          word,
                          prj_found_list,
                          prj_val_list,
                          prj_extra_inf,
                          do_update_cache,
                          id_lang,
                          trace
                         );

                LEM_CHECKIT_Z( prj_found_list.size()==prj_val_list.size() );
                LEM_CHECKIT_Z( prj_found_list.size()==prj_extra_inf.size() );

                break;
               }

              case 2:
               {
                Project_2(
                          word,
                          proj.get_Miss_Parameter(),
                          prj_found_list,
                          prj_val_list,
                          prj_extra_inf,
                          id_lang,
                          trace
                         );

                LEM_CHECKIT_Z( prj_found_list.size()==prj_val_list.size() );
                LEM_CHECKIT_Z( prj_found_list.size()==prj_extra_inf.size() );

                break;
               }

              default: LEM_STOPIT;
             }

             const Real1 pi_val = proj.GetPhonInvVal(pi);
             if( pi_val!=lem::Real1(100) )
              {
               for( Container::size_type i=ibegin; i<prj_val_list.size(); i++ )
                prj_val_list[i] = prj_val_list[i]*pi_val;
              }
            }
        */
    }

    AddResults(proj, prj_found_list, prj_val_list, prj_extra_inf);

    LEM_CHECKIT_Z(prj_found_list.size() == prj_val_list.size());
    LEM_CHECKIT_Z(prj_found_list.size() == prj_extra_inf.size());

    return;
}
#endif // defined SOL_CAA



bool LexicalAutomat::IsLanguageWithOptionalDiaktiriks(int id_language)
{
    if (id_language != UNKNOWN)
    {
#if defined LEM_THREADS
        lem::Process::RWU_ReaderGuard rlock(cs_lang_optional_diacritics);
#endif

        auto it = id_language_with_optional_diacritics.find(id_language);

        if (it == id_language_with_optional_diacritics.end())
        {
#if defined LEM_THREADS
            lem::Process::RWU_WriterGuard wlock(rlock);
#endif

            it = id_language_with_optional_diacritics.find(id_language);

            if (it == id_language_with_optional_diacritics.end())
            {
                SynGram &sg = GetSynGram();

                const SG_Language &lang = sg.languages()[id_language];
                const int iparam = lang.FindParam(L"HasOptionalDiacritics");
                if (iparam != UNKNOWN)
                {
                    const SG_LanguageParam & param = lang.GetParam(iparam);
                    const bool x = param.GetValue().eqi(L"true");
                    id_language_with_optional_diacritics.insert(std::make_pair(id_language, x ? 1 : 0));
                    if (x)
                    {
                        const int iparam2 = lang.FindParam(L"CharsWithOptionalDiacritics");
                        lem::UFString chars = lang.GetParam(iparam2).GetValue();
                        chars.strip_quotes();
                        optional_diacritics_for_languages.insert(std::make_pair(id_language, chars));

                        const int iparam3 = lang.FindParam(L"AuxTypeForDiacritics");
                        lem::UCString aux_type_name = lang.GetParam(iparam3).GetValue().c_str();
                        aux_type_name.strip_quotes();
                        const int aux_type_id = sg.GetAuxFormTypes()[aux_type_name];

                        optional_diacritics_aux_type.insert(std::make_pair(id_language, aux_type_id));
                    }

                    return x;
                }
                else
                {
                    id_language_with_optional_diacritics.insert(std::make_pair(id_language, 0));
                    return false;
                }
            }
            else
            {
                return it->second == 1;
            }
        }
        else
        {
            return it->second == 1;
        }
    }

    return false;
}


static bool MatchWithoutSpaces(const wchar_t * str1, const wchar_t * str2)
{
    while ((*str1) != 0 && (*str2) != 0)
    {
        if (*str1 == L' ') { str1++; continue; }
        if (*str2 == L' ') { str2++; continue; }
        if (*str1 == *str2)
        {
            str1++;
            str2++;
            continue;
        }

        return false;
    }

    return *str1 == *str2;
}




/****************************************************************************
    Алгоритм быстрого точного проецирования мультилексемы на Лексикон.

 Так как большинство словарных статей не хранят в развернутом виде свои
 словоформы, а только указывают на индекс таблицы склонения, то мы не можем
 просто просмотреть все словоформы всех статей: потребуется распаковка,
 огромное засорение динамической памяти при выделении и освобождении большого
 числа блочков и так далее. Впрочем, нам и не нужно этим заниматься, так как
 значительная часть сравнений словоформ и мультилексемы исключается благодаря
 нескольким эффективным критериям (хешам): по диапазону символьной длины, по
 сигнатуре присутствия букв, по хеш-функции H(x), по обязательной сигнатуре,
 по числу лексем в мультилексеме. Таким образом, большинство проверок
 заключается лишь в извлечении из словарных статей ряда хеш-полей и сравнении
 их со значениями параметров для проецируемой мультилексемы. Только если все
 критерии дают положительный результат, необходимо распаковать словоформы
 (когда это нужно) и сравнивать мультилексему с каждой из них.

   Эта процедура отлично приспособлена и для автономного использования (в случае
 необходимости) "извне Системы". Итак, если требуется спроецировать
 мультилексему A, и получить список (в общем случае) проекций, то есть индексов
 словарных статей и словоформ, то вызывается данная процедура. Чтобы отключить
 обновление кэша проекций (но не его использование!), достаточно установить
 do_register=false. Это снимет проблему побочных эффектов, хотя отключит
 механизм динамического обучения. Если же не отключать обновление кэша проекций
 (как это происходит при внутреннем использовании процедуры), то возможно
 переполнение кэша, что потребует проведения операции сборки мусора - лишняя
 головная боль для вызвавшей программы.
*********************************************************************************/
bool LexicalAutomat::Project_1(
    const RC_Lexem &A,
    const lem::UCString &original_word,
    float scoreA,
    MCollect<Word_Coord> &found_list,
    MCollect<ProjScore> &val_list,
    PtrCollect<LA_ProjectInfo> &inf_list,
    bool refresh_cache,
    bool allow_fuzzy,
    bool use_recognition_rules,
    int id_lang,
    LA_RecognitionTrace *trace
)
{
    SynGram &s_gram = GetSynGram();

    const wchar_t *As = A->c_str();

    // Пробуем распознать как число.
    lem::zbool it_is_number;

    if (A->Count_Lexems() == 1)
    {
        LEM_CHECKIT_Z(!A->empty());

        double dummy;

        if (As[A->length() - 1] == L'%' || As[A->length() - 1] == L'$')
        {
            UCString b;
            for (int i = 0; i < A->length() - 1; ++i)
                b += As[i];

            it_is_number = to_real(b.c_str(), &dummy);
        }
        else if (to_real(As, &dummy))
        {
            it_is_number = true;
        }

        if (it_is_number)
        {
            static int i_number = UNKNOWN;

            if (i_number == UNKNOWN)
                i_number = GetDict().GetSynGram().FindEntry(UCString(L"number_"), ANY_STATE, false);

            found_list.push_back(Word_Coord(i_number, 0));
            val_list.push_back(scoreA);
            inf_list.push_back(nullptr);
            return true;
        }
    }

    bool ret_hit = false;
    bool precise_search_succeeded = false;

    /*
     if( s_gram.GetEntries().PreferPrefixSearch() )
      {
       const int A_len = A->length();

       bool prefix_lookup_used=false;

       if( lazy_load && GetDict().IsPrefixEntrySearcherAvailable() )
        {
         bool chars_ok=true;
         for( int k=A->length()-1; k>=0; --k )
          {
           wchar_t c = (*A)[k];
           if( c==L' ' )
            {
             chars_ok=false;
             break;
            }
          }

         if( chars_ok )
          {
           prefix_lookup_used=true;
           lem::Ptr<PrefixEntrySearcher> prefix_searcher( GetDict().GetPrefixEntrySearcher( lem::int_max ) );

           lem::MCollect<int> ies;
           prefix_searcher->Search( A->c_str(), ies );

           for( lem::Container::size_type i=0; i<ies.size(); ++i )
            {
             const int id_entry = ies[i];
             const SG_Entry &E = s_gram.GetEntry(id_entry);

             if( A_len<E.GetMinLen() || A_len>E.GetMaxLen() )
              continue;

             if( !E.GetRoot().empty() && lem_find( As, E.GetRoot().c_str() )==UNKNOWN )
              continue;

             // Сравниваем A с лексическим содержимым словоформ.
             const int nform = CastSizeToInt(E.forms().size());

             for( int iform=0; iform<nform; iform++ )
              {
               if( *A==E.forms()[iform].name() )
                {
                 found_list.push_back( Word_Coord(id_entry,iform) );
                 val_list.push_back( relA );
                 inf_list.push_back(NULL);
                 ret_hit=true;
                 precise_search_succeeded=true;
                }
              }
            }
          }
        }

       if( !prefix_lookup_used )
        {
         // Берем первый символ A и отыскиваем в Таблице Быстрого Поиска соответствующий
         // элемент, который содержит список индексов статей, лексическое содержимое
         // словоформ которых начинается с той же буквы.
         lem::Ptr<WordEntryEnumerator> wenum( s_gram.GetEntries().ListEntries( SG_EntryGroup::BuildKey(*A) ) );

         while( wenum->Fetch() )
          {
           const int ientry = wenum->GetId();

           const SG_Entry &E = wenum->GetItem();

           // Проверяем второй критерий: длина мультилексемы A должна попасть
           // в диапазон для словоформ статьи.
           if( A_len<E.GetMinLen() || A_len>E.GetMaxLen() )
            continue;

           // Если корень статьи есть, то он должен присутствовать в лексеме.
           if( !E.GetRoot().empty() && lem_find( As, E.GetRoot().c_str() )==UNKNOWN )
            continue;

           // Сравниваем A с лексическим содержимым словоформ.
           const int nform = CastSizeToInt(E.forms().size());

           for( int iform=0; iform<nform; iform++ )
            {
             if( *A==E.forms()[iform].name() )
              {
               found_list.push_back( Word_Coord(ientry,iform) );
               val_list.push_back( relA );
               inf_list.push_back(NULL);
               ret_hit=true;
               precise_search_succeeded=true;
              }
            }
          }
        }
      }
     else*/
    {
        std::unique_ptr<WordFormEnumerator> fenum(s_gram.GetEntries().ListWordForms(*A, false));

        while (fenum->Fetch())
        {
            const int ientry = fenum->GetEntryKey();
            const int iform = fenum->GetFormIndex();

            found_list.push_back(Word_Coord(ientry, iform));
            val_list.push_back(scoreA);
            inf_list.push_back(nullptr);
            ret_hit = true;
            precise_search_succeeded = true;
        }
    }


    if (ret_hit && use_recognition_rules)
    {
        // применим только особую группу ОБЯЗАТЕЛЬНЫХ правил.
        recognizer->Apply(*A, original_word, scoreA, 0.0f, found_list, val_list, inf_list, id_lang, true, trace);
    }

    if (!ret_hit && use_recognition_rules)
    {
        // найти ничего не удалось.

#if defined SOL_CAA
// может это известная опечатка?
        lem::MCollect<lem::UCString> corrected_word;
        if (FindMisspeltWord(*A, corrected_word, id_lang))
        {
            // да, пробуем теперь проекцию скорректированного слова
            for (lem::Container::size_type i2 = 0; i2 < corrected_word.size(); ++i2)
            {
                RC_Lexem word2(new Lexem(corrected_word[i2]));

                if (Project_1(
                    word2,
                    original_word,
                    0.0f,
                    found_list,
                    val_list,
                    inf_list,
                    do_update_cache,
                    false,
                    false,
                    id_lang,
                    trace
                ))
                {
                    ret_hit = true;
                    precise_search_succeeded = true;
                }
            }
        }
#endif

        bool recognizer_applied = false;
        if (!ret_hit)
        {
            // пробуем применить точные правила распознавания, например для слов типа "123-е"
            ret_hit = recognizer_applied = recognizer->Apply(*A, original_word, scoreA, 0.0f, found_list, val_list, inf_list, id_lang, false, trace);
            LEM_CHECKIT_Z(found_list.size() == val_list.size());
            LEM_CHECKIT_Z(found_list.size() == inf_list.size());
        }

#if defined SOL_CAA
        if ((recognizer_applied || !ret_hit) && allow_fuzzy)
        {
            // нечеткая проекция разрешена, можем попробовать найти слова с опечатками, взяв суперпозицию.

            MCollect<Word_Coord> found_list2;
            MCollect<ProjScore> val_list2;
            PtrCollect<LA_ProjectInfo> inf_list2;

            if (Project_3(A, original_word, scoreA, found_list2, val_list2, inf_list2, id_lang, trace))
            {
#if LEM_DEBUGGING==1
                for (int q = 0; q < found_list2.size(); ++q)
                {
                    const SG_Entry & eq = s_gram.GetEntry(found_list2[q].GetEntry());
                    lem::mout->printf("#%d --> %us\n", q, eq.GetName().c_str());
                }
#endif

                lem::MCollect<int> quantor_deletion_flag;
                quantor_deletion_flag.resize(found_list.size());
                quantor_deletion_flag.Nullify();
                bool delete_quantors = false;

                for (lem::Container::size_type k = 0; k < found_list.size(); ++k)
                {
                    if (inf_list[k] != nullptr)
                    {
                        const int ekey1 = found_list[k].GetEntry();
                        const SG_Entry &e1 = s_gram.GetEntry(ekey1);
                        const int id_class1 = e1.GetClass();

                        const CP_Array & coords1 = inf_list[k]->coords;

                        for (lem::Container::size_type l = 0; l < found_list2.size(); ++l)
                        {
                            const int ekey2 = found_list2[l].GetEntry();
                            if (ekey1 != ekey2)
                            {
                                if (inf_list2[l] == nullptr)
                                {
                                    const SG_Entry &e2 = s_gram.GetEntry(ekey2);
                                    const int id_class2 = e2.GetClass();

                                    if (id_class1 == id_class2)
                                    {
                                        // сопоставим грамматические координатные пары.
                                        const SG_EntryForm &f2 = e2.forms()[found_list2[l].GetForm()];

                                        if (f2.coords().size() == coords1.size())
                                        {
                                            if (f2.does_match(coords1))
                                            {
                                                // если кванторный результат распознавания полностью соответствует по координатным парам
                                                // найденному реальному слову, то квантор можем выкинуть.
                                                quantor_deletion_flag[k] = 1;
                                                delete_quantors = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                if (delete_quantors)
                {
                    for (int k = CastSizeToInt(found_list.size()) - 1; k >= 0; --k)
                        if (quantor_deletion_flag[k] == 1)
                        {
                            quantor_deletion_flag.Remove(k);
                            found_list.Remove(k);
                            val_list.Remove(k);
                            inf_list.Remove(k);
                        }
                }

                for (lem::Container::size_type k = 0; k < found_list2.size(); ++k)
                {
                    if (found_list.empty())
                    {
                        found_list.push_back(found_list2[k]);
                        val_list.push_back(val_list2[k]);
                        inf_list.push_back(inf_list2[k]);
                        inf_list2[k] = nullptr;
                    }
                    else
                    {
                        found_list.Insert(0, found_list2[k]);
                        val_list.Insert(0, val_list2[k]);
                        inf_list.Insert(0, inf_list2[k]);
                        inf_list2[k] = nullptr;
                    }
                }
            }
        }
#endif
    }


    if (ret_hit)
    {
        if (precise_search_succeeded && found_list.size() > 1)
        {
            int id_language_found = id_lang;
            int n_lang = 0;

            if (id_language_found == UNKNOWN)
            {
                SynGram &sg = GetSynGram();

                for (lem::Container::size_type i = 0; i < found_list.size(); ++i)
                {
                    const SG_Entry &e = sg.GetEntry(found_list[i].GetEntry());
                    const int id_class = e.GetClass();
                    const int class_lang = sg.GetClass(id_class).GetLanguage();
                    if (class_lang != UNKNOWN)
                    {
                        if (id_language_found == UNKNOWN)
                        {
                            n_lang = 1;
                            id_language_found = class_lang;
                        }
                        else
                        {
                            if (id_language_found != class_lang)
                            {
                                n_lang++;
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                n_lang = 1;
            }

            if (n_lang == 1 && IsLanguageWithOptionalDiaktiriks(id_language_found))
            {
                // просмотрим ёфикацию и попробуем отфильтровать

#if defined LEM_THREADS
                lem::Process::RWU_ReaderGuard rlock(cs_lang_optional_diacritics);
#endif

                const lem::UFString & chars = optional_diacritics_for_languages.find(id_language_found)->second;
                const int aux_type_id = optional_diacritics_aux_type.find(id_language_found)->second;

                // хоть один из перечисленных в chars символов есть в исходном слове?
                bool has_trigger_chars = false;
                for (int i = 0; i < chars.size(); ++i)
                    if (original_word.find(chars[i]))
                    {
                        has_trigger_chars = true;
                        break;
                    }

                if (has_trigger_chars)
                {
                    int n_diacritic_hits = 0;
                    lem::MCollect<int> form_matching;

                    lem::UFString aux_form;
                    SynGram &sg = GetSynGram();
                    for (lem::Container::size_type i = 0; i < found_list.size(); ++i)
                    {
                        form_matching.push_back(0);

                        if (sg.GetAuxForm(found_list[i].GetEntry(), found_list[i].GetForm(), aux_type_id, aux_form))
                        {
                            const bool match = MatchWithoutSpaces(aux_form.c_str(), original_word.c_str());
                            if (match)
                            {
                                n_diacritic_hits++;
                                form_matching.back() = 1;
                            }
                        }
                    }

                    // если есть хотя бы одно совпадение с aux-формой, то оставляем только совпадающие формы.
                    if (n_diacritic_hits > 0)
                    {
                        for (int k = CastSizeToInt(found_list.size()) - 1; k >= 0; --k)
                        {
                            if (form_matching[k] == 0)
                            {
                                found_list.Remove(k);
                                val_list.Remove(k);
                                inf_list.Remove(k);
                            }
                        }
                    }
                }
            }
        }

        if (refresh_cache)
        {
            // Обновляем кэш осуществленных проекций.
#if defined LEM_THREADS
            lem::Process::CritSecLocker locker(&cs);
#endif

            if (!found_list.empty())
                word_proj->Add(LA_WordProjection(A, found_list, val_list, 1));
        }
    }

    LEM_CHECKIT_Z(found_list.size() == val_list.size());
    LEM_CHECKIT_Z(found_list.size() == inf_list.size());


    /*
    #if LEM_DEBUGGING==1
    for( int i=0; i<inf_list.size(); ++i )
     {
      lem::mout->printf( "proj #%d :-> val=%s coords=", i, lem::to_str(val_list[i].val).c_str() );
      if( inf_list[i]!=NULL )
       {
        for( int j=0; j<inf_list[i]->coords.size(); ++j )
        {
         lem::mout->printf( " %d:%d", inf_list[i]->coords[j].GetCoord().GetIndex(), inf_list[i]->coords[j].GetState() );
        }
       }

      lem::mout->printf("\n");
     }
    #endif
    */

    return ret_hit;
}





#if defined SOL_CAA
/************************************************************************

             Нечеткая проекция мультилексемы A на Лексикон.

 В этой процедуре мы, к сожалению, не имеем возможности использовать
 Таблицу Быстрого Поиска, так как и первая буква может быть пропущена или
 искажена. Однако продолжают быть полезными некоторые критерии алгоритма
 быстрого проецирования.

 A - проецируемая мультилексема.

 nmissmax - Параметр определяет, на сколько букв может отличаться
            проецируемое слово и лексема в Лексиконе, чтобы признать
            несовпадение случайной ошибкой.

 Списки found_list и val_list являются результатом работы и содержат
 соответственно координаты словоформ в Лексиконе и оценки достоверности
 проекции.
**************************************************************************/
void LexicalAutomat::Project_2(
    const RC_Lexem &A,
    int nmissmax,
    MCollect<Word_Coord> &found_list,
    MCollect<ProjScore> &val_list,
    PtrCollect<LA_ProjectInfo> &inf_list,
    int id_lang,
    LA_RecognitionTrace *trace
)
{
    /*
    MultyLexem a,b;
    a.push_back( L"САБАКА" );
    b.push_back( L"СКЛАДА" );
    int rtm = CompareThem( a, b, 1 );
    */

    LEM_CHECKIT_Z(found_list.size() == val_list.size());
    LEM_CHECKIT_Z(found_list.size() == inf_list.size());

    SynGram& s_gram = GetSynGram();
    // GraphGram& g_gram = GetGraphGram();

    bool was_projection = false;

    const int A_len = A->length();

    const wchar_t A_first = A->front(); // Первый символ первой лексемы
    const wchar_t A_last = A->back(); // Последний символ последней лексемы

    std::set<wchar_t> Achars;
    for (int j = 0; j < A->length(); j++)
        Achars.insert((*A)[j]);

    // Просматриваем все словарные статьи синтаксической грамматики в поиске
    // тех словоформ, длина лексического значения которых отличается от A_len
    // не более чем на NMISSMAX символов.
    std::unique_ptr<WordEntryEnumerator> wenum(s_gram.GetEntries().ListEntries());
    while (wenum->Fetch())
    {
        const int ientry = wenum->GetId();
        const SG_Entry &e = wenum->GetItem();

        // Второй критерий: общая длина A не должна выходить за границы диапазона
        // длин словоформ статьи более чем на nmissmax.
        if (A_len<e.GetMinLen() && lem::Math::iabs(e.GetMinLen() - A_len) > nmissmax)
            continue;

        if (A_len > e.GetMaxLen() && lem::Math::iabs(e.GetMaxLen() - A_len) > nmissmax)
            continue;

        // Все буквы корня должны быть в искомой лексеме
        const UCString &rt = e.GetRoot();
        int nmiss1 = 0;
        for (int j = 0; j < rt.length() && nmiss1 <= nmissmax; j++)
            if (Achars.find(rt[j]) == Achars.end())
                nmiss1++;

        if (nmiss1 > nmissmax)
            continue;

        //mout.printf( "Entry: %us root=%us nmiss=%d\n", e.GetName().c_str(), e.GetRoot().c_str(), nmiss1 );

        const int nform = CastSizeToInt(e.forms().size());

        for (int iform = 0; iform < nform; iform++)
        {
            const Lexem &B = e.forms()[iform].name();
            const int B_len = B.length();

            if (lem::Math::iabs(A_len - B_len) > nmissmax)
                continue;

            bool does_match = false;
            Real1 value(0);

            int ntotmiss = 0;
            Real1 equality(0);

            // Проверяем особый случай: как известно, при чтении текста человеком
            // он прежде всего распознает слова по первой и последней букве, а срединка
            // может быть полностью перемешана (но при этом все буквы присутствуют).
            // Так что и мы проверяем, совпадают ли граничные буквы, и если да -
            // проверяем серединку.
            // Для упрощения работы - только для однолексем.
       /*
            if(
               A.size()==1 && B.size()==1   &&
               A_first == B.front().front() &&
               A_last  == B.back().back()
              )
             {
              bool go_compare=true;

              // Все буквы из A должны присутствовать в B.
              // первую и последнюю мы уже проверили, они совпадают. Проверим
              // серединку.

              const Lexem& LA = A->front();

              // Если есть разница в длинах...
              ntotmiss = lem_iabs(LA.length()-B.front().length());

              for( int i=1; i<LA.length()-1 && go_compare; i++ )
               {
                const wchar_t ch_A = LA[i];
                bool ch_found=false;

                const Lexem& LB = B.front();

                for( int j=1; j<LB.length()-1; j++ )
                 if( LB[j] == ch_A )
                  {
                   ch_found=true;
                   break;
                  }

                if( !ch_found )
                 {
                  // еще один символ из A не найден. Вообще говоря, тут надо бы
                  // учитывать частоты символов - редкие символы более заметны,
                  // так что их отсутствие более весомо. Но пока ограничимся
                  // простоым алгоритмом.
                  ntotmiss++;

                  if( ntotmiss>nmissmax )
                   {
                    does_match = false;
                    go_compare = false;
                    break;
                   }
                 }
               }

              if( ntotmiss<=nmissmax )
               {
                // Отличие слов в пределах допустимого
                does_match = true;
               }
             }
            else
       */
            {
                // Умная проверка не прошла. Выполняем механическую проверку, не имеющую
                // психологического соответствия, но корректную в формально-математическом
                // смысле.
                ntotmiss = CompareThem(*A, B, id_lang, nmissmax, &equality);
                does_match = ntotmiss <= nmissmax;
            }

            // Добавляем словоформу к списку найденных.
            if (does_match)
            {

                //mout.printf( "[%us] -> [%us] miss=%d\n", A->string().c_str(), B.string().c_str(), ntotmiss );
                // --------------------------------------------------------------------------
                // Расчитываем оценку достоверности нечеткой проекции:
                //
                //          длина_слова - число_отличий   min(длина_слова,длина_словоформы)
                // оценка=  --------------------------- * -----------------------------------
                //                  длина_слова           max(длина_слова,длина_словоформы)
                //
                // --------------------------------------------------------------------------
                const Real1 value1 = ntotmiss > A_len ?
                    Real1(0) :
                    (
                        equality != 0 ?
                        equality :
                        Real1((A_len - ntotmiss) * 100 / A_len)
                        );

                const Real1 value2(lem::min(A_len, B_len) * 100 / lem::max(A_len, B_len));

                value = value1*value2; // достоверность проекции

                // отсев вариантов проекции по граничному значению достоверности.
                //if( value < MIN_PROJ_R )
                // continue;

                const Word_Coord WC(ientry, iform);

                bool already = false;
                const int nfl = CastSizeToInt(found_list.size());
                for (int ii = 0; ii < nfl && !already; ii++)
                    already = found_list[ii] == WC;

                if (already)
                    continue;

                /*
                       if( GetDebugLevel()>=3 )
                       {
                        if( !found_list.size() )
                         lem::LogFile::logfile->eol();

                        lem::LogFile::logfile->printf(
                                                 "Fuzzy projection [%us] as [%us] value=%us int=%d ientry=%d\n"
                                                 , A->c_str()
                                                 , B.c_str()
                                                 , to_ustr( value ).c_str()
                                                 , ientry
                                                 , iform
                                                );
                       }
                */

                found_list.push_back(WC);
                val_list.push_back(Real1ToScore(value));
                inf_list.push_back(nullptr);
                was_projection = true;
            } // end if
        } // end for( iform ...
    } // end for( ientry ...


    if (was_projection)
    {
#if defined LEM_THREADS
        lem::Process::CritSecLocker locker(&cs);
#endif

        word_proj->Add(LA_WordProjection(A, found_list, val_list, 1));
    }

    LEM_CHECKIT_Z(found_list.size() == val_list.size());
    LEM_CHECKIT_Z(found_list.size() == inf_list.size());

    return;
}
#endif

#if defined SOL_CAA
const EndingStat & LexicalAutomat::GetEndingStat(int id_lang)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_endings);
#endif

    int i = ending_stat_lang.find(id_lang);
    if (i == UNKNOWN)
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        i = ending_stat_lang.find(id_lang);
        if (i == UNKNOWN)
        {
            EndingStat stat;
            SynGram &sg = GetDict().GetSynGram();
            sg.GetStorage().GetEndingStat(id_lang, stat);
            ending_stat_lang.push_back(id_lang);
            ending_stat_data.push_back(stat);
            return ending_stat_data.back();
        }
        else
        {
            return ending_stat_data[i];
        }
    }
    else
    {
        return ending_stat_data[i];
    }
}
#endif



#if defined SOL_CAA
bool LexicalAutomat::GetEnding(int id_lang, const lem::UCString &ending, int &nform, int &sumfreq)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_endings);
#endif

    EndingKey key(ending, id_lang);
    const std::map< EndingKey, EndingInfo >::const_iterator it = ending_info.find(key);
    if (it == ending_info.end())
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        EndingInfo info;

        SynGram &sg = GetSynGram();
        info.found = sg.GetStorage().FindEnding(id_lang, ending, info.nform, info.sumfreq);
        ending_info.insert(std::make_pair(key, info));

        nform = info.nform;
        sumfreq = info.sumfreq;

        return info.found;
    }
    else
    {
        nform = it->second.nform;
        sumfreq = it->second.sumfreq;
        return it->second.found;
    }
}
#endif



#if defined SOL_CAA
// *******************************************************************
// Проекция неизвестного слова на основе "правил догадки" по аффиксу
// *******************************************************************
bool LexicalAutomat::Project_3(
    const RC_Lexem &A,
    const lem::UCString & original_word,
    float scoreA,
    MCollect<Word_Coord> &found_list,
    MCollect<ProjScore> &val_list,
    PtrCollect<LA_ProjectInfo> &inf_list,
    int _id_lang,
    LA_RecognitionTrace *trace
)
{
    const lem::UCString & word = *A;
    int id_lang = _id_lang;
    if (id_lang == UNKNOWN)
    {
        id_lang = GuessLanguage(word.c_str());
    }

    SynGram &sg = GetSynGram();

    bool ret_hit = false;

    // 1. Ищем среди известных опечаток
    lem::MCollect<lem::UCString> rewritten_words;
    if (recognizer->RewriteMisspeltWord(id_lang, word, rewritten_words))
    {
        for (lem::Container::size_type i = 0; i < rewritten_words.size(); ++i)
        {
            const lem::UCString & rewritten_word = rewritten_words[i];
            RC_Lexem lex(new Lexem(rewritten_word));

            bool hit = Project_1(
                lex,
                rewritten_word,
                scoreA,
                found_list,
                val_list,
                inf_list,
                false,
                false,
                false,
                id_lang,
                trace
            );

            if (hit)
                ret_hit = true;
        }
    }

    if (ret_hit)
        return true;


    // 2. попробуем нечеткую проекцию для корня слова, с сохранением окончания.
    bool found_by_root = false;

    // определяем максимальную длину окончания для языка
    if (id_lang != UNKNOWN)
    {
        bool ending_found = false;
        UCString stem;
        UCString ending;

        const EndingStat & info = GetEndingStat(id_lang);
        if (info.max_len > 0)
        {
            int MIN_STEM_LEN = 3;
            const SG_Language & lang = sg.languages()[id_lang];
            int iparam = lang.FindParam(L"MIN_STEM_LEN");
            if (iparam != UNKNOWN)
                MIN_STEM_LEN = lem::to_int(lang.GetParam(iparam).GetValue());

            lem::MCollect<lem::UCString> stems2;
            lem::MCollect<lem::Real1> rels2;

            for (int end_len = std::min(info.max_len, word.length() - MIN_STEM_LEN); end_len >= 1; --end_len)
            {
                if (end_len + MIN_STEM_LEN <= word.length())
                {
                    ending = lem::right(word, end_len);
                    ending.to_upper();

                    int nform = 0, sumfreq = 0;
                    if (GetEnding(id_lang, ending, nform, sumfreq))
                    {
                        // нашли такое окончание.
                        if (nform > 10 || sumfreq > 1000)
                        {
                            ending_found = true;

                            stem = lem::left(word, word.length() - end_len);

                            // теперь из основы генерируем фонетические инварианты.
                            stems2.clear();
                            rels2.clear();
                            ProducePhonInv(stem, id_lang, stems2, rels2, trace);
                            if (!stems2.empty())
                            {
                                /*
                                #if LEM_DEBUGGING==1
                                for( int k=0; k<stems2.size(); ++k )
                                 {
                                  lem::mout->printf( "stem=%us\n", stems2[k].c_str() );
                                 }
                                #endif
                                /**/
                                // теперь к каждой искаженной основе прикрепляем обратно окончание и пытаемся найти такое слово.
                                for (lem::Container::size_type j = 0; j < stems2.size(); ++j)
                                {
                                    lem::UCString word2 = stems2[j] + ending;

                                    if (word2 == word)
                                        continue;

                                    RC_Lexem lex2(new Lexem(word2));

                                    bool hit = Project_1(
                                        lex2,
                                        word2,
                                        Real1ToScore(rels2[j]) + scoreA,
                                        found_list,
                                        val_list,
                                        inf_list,
                                        false,
                                        false,
                                        false,
                                        id_lang,
                                        trace
                                    );

                                    if (hit)
                                    {
                                        found_by_root = true;
                                    }
                                }
                            }

                            break;
                        }
                    }
                }
            }
        }




        if (!ending_found && !found_by_root)
        {
            // Окончание не нашли. Поэтому работаем с полным словом.

            lem::MCollect<lem::UCString> words2;
            lem::MCollect<lem::Real1> rels2;

            ProducePhonInv(word, id_lang, words2, rels2, trace);
            if (!words2.empty())
            {
                /*
                #if LEM_DEBUGGING==1
                for( int k=0; k<stems2.size(); ++k )
                 {
                  lem::mout->printf( "stem=%us\n", stems2[k].c_str() );
                 }
                #endif
                /**/
                // теперь к каждой искаженной основе прикрепляем обратно окончание и пытаемся найти такое слово.
                for (lem::Container::size_type j = 0; j < words2.size(); ++j)
                {
                    if (words2[j] == word)
                        continue;

                    RC_Lexem lex2(new Lexem(words2[j]));

                    bool hit = Project_1(
                        lex2,
                        words2[j],
                        Real1ToScore(rels2[j]) + scoreA,
                        found_list,
                        val_list,
                        inf_list,
                        false,
                        false,
                        false,
                        id_lang,
                        trace
                    );

                    if (hit)
                    {
                        found_by_root = true;
                    }
                }
            }
        }




        if (!found_by_root)
        {
            // попробуем считать, что в слове пропущена, искажена или ошибочно добавлена буква.
            // для эффективной работы потребуется префиксное поисковое дерево.
            lem::Ptr<PrefixEntrySearcher> ps = GetDict().GetPrefixEntrySearcher(lem::int_max);
            if (ps.NotNull())
            {
                // префиксное дерево есть.
                lem::MCollect< lem::uint32_t > chars;

                // локальный кэш.
                typedef std::map< std::pair<int, lem::uint32_t>, const std::set<int>* > CHARPOS2ENTRIES;
                CHARPOS2ENTRIES charpos2entries;
                lem::PtrCollect< std::set<int> > id_entries;

                // Попробуем с перестановками соседних букв, не считая границы
                // XY -> YZ
                // XYZ -> ZYX

                WideStringUcs4 cenum_word_core(word.c_str());
                lem::uint32_t c;
                while ((c = cenum_word_core.Fetch()) != 0)
                {
                    chars.push_back(c);
                }

                const int c4_len = CastSizeToInt(chars.size());
                lem::MCollect<lem::uint32_t> probe_ch4;

                for (int swap_strategy = 0; swap_strategy < 2; ++swap_strategy)
                {
                    // swap_strategy==0 перестановка соседних букв  XY  --> YX
                    // swap_strategy==1 перестановка букв через 1   XYZ --> ZYX

                    const float rel = float(c4_len - 0.5F*(1 + swap_strategy)) / float(c4_len);
                    Real1 miss_rel(rel);

                    for (int ipos = 1; ipos < c4_len - 2 - swap_strategy; ++ipos)
                    {
                        lem::Ucs4ToUCString trial_form;
                        probe_ch4.clear();

                        if (swap_strategy == 0)
                        {
                            for (int jpos = 0; jpos < c4_len; ++jpos)
                            {
                                if (jpos<ipos || jpos>ipos + 1)
                                {
                                    probe_ch4.push_back(chars[jpos]);
                                    trial_form.Add(chars[jpos]);
                                }
                                else
                                {
                                    probe_ch4.push_back(chars[jpos + 1]);
                                    probe_ch4.push_back(chars[jpos]);

                                    trial_form.Add(chars[jpos + 1]);
                                    trial_form.Add(chars[jpos]);

                                    jpos++;
                                }
                            }
                        }
                        else if (swap_strategy == 1)
                        {
                            for (int jpos = 0; jpos < c4_len; ++jpos)
                            {
                                if (jpos<ipos || jpos>ipos + 2)
                                {
                                    probe_ch4.push_back(chars[jpos]);
                                    trial_form.Add(chars[jpos]);
                                }
                                else
                                {
                                    probe_ch4.push_back(chars[jpos + 2]);
                                    probe_ch4.push_back(chars[jpos + 1]);
                                    probe_ch4.push_back(chars[jpos]);

                                    trial_form.Add(chars[jpos + 2]);
                                    trial_form.Add(chars[jpos + 1]);
                                    trial_form.Add(chars[jpos]);

                                    jpos += 2;
                                }
                            }
                        }

                        std::set<int> * tot_ids = nullptr;
                        int first = true;

                        for (int iprobe = 0; iprobe < probe_ch4.size(); ++iprobe)
                        {
                            lem::uint32_t ucs4 = probe_ch4[iprobe];

                            const std::set<int> * ids = nullptr;

                            std::pair<int, lem::uint32_t> charpos(iprobe, ucs4);
                            CHARPOS2ENTRIES::const_iterator it = charpos2entries.find(charpos);
                            if (it == charpos2entries.end())
                            {
                                std::set<int> *ids2 = new std::set<int>();
                                ps->GetEntriesForCharPos(iprobe, ucs4, *ids2);

                                id_entries.push_back(ids2);
                                charpos2entries.insert(std::make_pair(charpos, ids2));

                                ids = ids2;
                            }
                            else
                            {
                                ids = it->second;
                            }

                            if (ids->empty())
                            {
                                if (tot_ids != nullptr)
                                    tot_ids->clear();
                            }

                            if (first)
                            {
                                first = false;
                                tot_ids = new std::set<int>(*ids);
                            }
                            else
                            {
                                // делаем суперпозицию
                                std::set<int> * res_ids = new std::set<int>();

                                for (std::set<int>::const_iterator it2 = tot_ids->begin(); it2 != tot_ids->end(); ++it2)
                                    if (ids->find(*it2) != ids->end())
                                        res_ids->insert(*it2);

                                delete tot_ids;
                                tot_ids = res_ids;

                                if (tot_ids->empty())
                                    break;
                            }
                        }

                        if (tot_ids != nullptr && !tot_ids->empty())
                        {
                            // нашли подходящие словарные статьи.

                            // ищем в них формы и добавляем в результаты
                            lem::UCString form_to_find(trial_form.ToString().c_str());

                            for (std::set<int>::const_iterator it3 = tot_ids->begin(); it3 != tot_ids->end(); ++it3)
                            {
                                const int id_entry = *it3;
                                const SG_Entry &e = sg.GetEntry(id_entry);

                                for (lem::Container::size_type iform = 0; iform < e.forms().size(); ++iform)
                                {
                                    const lem::UCString &eform = e.forms()[iform].name();

                                    if (eform == form_to_find)
                                    {
                                        // нашли.

                                        found_list.push_back(Word_Coord(id_entry, CastSizeToInt(iform)));
                                        val_list.push_back(scoreA + Real1ToScore(miss_rel));
                                        inf_list.push_back(nullptr);

                                        found_by_root = true;
                                    }
                                }
                            }
                        }

                        lem_rub_off(tot_ids);
                    }
                }

                // -------

                chars.clear();
                WideStringUcs4 cenum_stem(stem.empty() ? word.c_str() : stem.c_str());
                while ((c = cenum_stem.Fetch()) != 0)
                {
                    chars.push_back(c);
                }

                const int stem_len_ucs4 = CastSizeToInt(chars.size());

                WideStringUcs4 cenum_ending(ending.c_str());
                while ((c = cenum_ending.Fetch()) != 0)
                {
                    chars.push_back(c);
                }

                const int word_len_ucs4 = CastSizeToInt(chars.size());

                for (int imisspos = 1; imisspos <= stem_len_ucs4; ++imisspos)
                {
                    // в этом заходе считаем, что пропущен символ в позиции imisspos.

                    for (int strategy = 0; strategy < 3; ++strategy)
                    {
                        // strategy==0 считаем, что пропущена буква
                        // strategy==1 считаем, что буква искажена
                        // strategy==2 считаем, что добавлена лишняя буква

                        float rel = float(word_len_ucs4 - 1) / float(word_len_ucs4);
                        Real1 miss_rel(rel);

                        lem::Ucs4ToUCString trial_form;

                        std::set<int> * tot_ids = nullptr;
                        int first = true;
                        lem::uint32_t ucs4 = 0;

                        for (int ipos0 = 0; ipos0 < word_len_ucs4; ++ipos0)
                        {
                            int ipos1 = -1;
                            bool do_char = true;

                            if (strategy == 0)
                            {
                                ipos1 = ipos0 >= imisspos ? ipos0 + 1 : ipos0; // символы после проверочной позиции сдвигаем на 1 вправо

                                if (ipos0 == imisspos)
                                    trial_form.Add(L'#');

                                ucs4 = chars[ipos0];
                                trial_form.Add(ucs4);
                            }
                            else if (strategy == 1)
                            {
                                // неверная буква, пропускаем ее
                                if (ipos0 == imisspos)
                                {
                                    do_char = false;
                                    trial_form.Add(L'#');
                                }
                                else
                                {
                                    ipos1 = ipos0;
                                    ucs4 = chars[ipos0];
                                    trial_form.Add(ucs4);
                                }
                            }
                            else if (strategy == 2)
                            {
                                // лишняя буква
                                if (ipos0 == imisspos)
                                    do_char = false;
                                else
                                {
                                    if (ipos0 > imisspos)
                                        ipos1 = ipos0 - 1;
                                    else
                                        ipos1 = ipos0;

                                    ucs4 = chars[ipos0];
                                    trial_form.Add(ucs4);
                                }
                            }

                            if (do_char)
                            {
                                const std::set<int> * ids = nullptr;

                                std::pair<int, lem::uint32_t> charpos(ipos1, ucs4);
                                CHARPOS2ENTRIES::const_iterator it = charpos2entries.find(charpos);
                                if (it == charpos2entries.end())
                                {
                                    std::set<int> *ids2 = new std::set<int>();
                                    ps->GetEntriesForCharPos(ipos1, ucs4, *ids2);

                                    id_entries.push_back(ids2);
                                    charpos2entries.insert(std::make_pair(charpos, ids2));

                                    ids = ids2;
                                }
                                else
                                {
                                    ids = it->second;
                                }

                                if (ids->empty())
                                {
                                    if (tot_ids != nullptr)
                                        tot_ids->clear();
                                }

                                if (first)
                                {
                                    first = false;
                                    tot_ids = new std::set<int>(*ids);
                                }
                                else
                                {
                                    // делаем суперпозицию
                                    std::set<int> * res_ids = new std::set<int>();

                                    for (std::set<int>::const_iterator it2 = tot_ids->begin(); it2 != tot_ids->end(); ++it2)
                                        if (ids->find(*it2) != ids->end())
                                            res_ids->insert(*it2);

                                    delete tot_ids;
                                    tot_ids = res_ids;

                                    if (tot_ids->empty())
                                        break;
                                }
                            }
                        }

                        if (tot_ids != nullptr && !tot_ids->empty())
                        {
                            // нашли подходящие статьи
                            // ищем в них формы с учетом пропуска и добавляем в результаты
                            lem::UCString form_to_find(trial_form.ToString().c_str());

                            for (std::set<int>::const_iterator it3 = tot_ids->begin(); it3 != tot_ids->end(); ++it3)
                            {
                                const int id_entry = *it3;
                                const SG_Entry &e = sg.GetEntry(id_entry);

                                // нам известны макс. и мин. длины форм в этой статье
                                if (e.GetMinLen() <= form_to_find.length() && e.GetMaxLen() >= form_to_find.length())
                                {
                                    for (lem::Container::size_type iform = 0; iform < e.forms().size(); ++iform)
                                    {
                                        const lem::UCString &eform = e.forms()[iform].name();
                                        if (eform.length() == form_to_find.length())
                                        {
                                            bool matches = true;

                                            if (strategy == 0)
                                            {
                                                // вариант с пропущенной буквой
                                                for (int k = 0; k < eform.length(); ++k)
                                                    if (k != imisspos && eform[k] != form_to_find[k])
                                                    {
                                                        matches = false;
                                                        break;
                                                    }
                                            }
                                            else if (strategy == 1)
                                            {
                                                // вариант с искаженной буквой
                                                for (int k = 0; k < eform.length(); ++k)
                                                    if (k != imisspos && eform[k] != form_to_find[k])
                                                    {
                                                        matches = false;
                                                        break;
                                                    }
                                            }
                                            else if (strategy == 2)
                                            {
                                                // вариант с добавленной буквой
                                                matches = eform == form_to_find;
                                            }

                                            if (matches)
                                            {
                                                // нашли.

                                                found_list.push_back(Word_Coord(id_entry, CastSizeToInt(iform)));
                                                val_list.push_back(scoreA + Real1ToScore(miss_rel));
                                                inf_list.push_back(nullptr);

                                                found_by_root = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        delete tot_ids;
                    }
                }
            }
        }


        ret_hit = found_by_root;
    }


    if (!found_by_root)
    {
        // 3. попробуем проекцию на основе только окончания
        // Делаем разбивку на слоги
        lem::MCollect<lem::UCString> slb_list;
        GetDict().GetGraphGram().FindSyllabs(*A, id_lang, false, slb_list, trace);

        if (trace != nullptr)
        {
            trace->WordSyllabs(*A, slb_list);
        }

        if (slb_list.size() > 1)
        {
            ret_hit = recognizer->ApplyForSyllabs(*A, scoreA, slb_list, GetMinProjectionScore(), found_list, val_list, inf_list, id_lang, trace);
        }

        if (!ret_hit)
        {
            ret_hit = recognizer->Apply(*A, original_word, scoreA, GetMinProjectionScore(), found_list, val_list, inf_list, id_lang, false, trace);
        }

        LEM_CHECKIT_Z(found_list.size() == val_list.size());
        LEM_CHECKIT_Z(found_list.size() == inf_list.size());
    }

    return ret_hit;
}
#endif



#if defined SOL_CAA
/************************************************************************
 Для мультилексемы из задания proj была успешно осуществлена проекция на
 Лексикон и теперь необходимо результаты проекции запомнить во внутренних
 списках proj.
*************************************************************************/
bool LexicalAutomat::AddResults(
    MLProjList &proj,
    const MCollect<Word_Coord> &coords,
    const MCollect<ProjScore> &vals,
    const PtrCollect<LA_ProjectInfo> &inf_list
)
{
    bool added = false;

    LEM_CHECKIT_Z(coords.size() == vals.size());
    LEM_CHECKIT_Z(inf_list.size() == coords.size());

    SynGram& s_gram = GetSynGram();
    const int n = CastSizeToInt(coords.size()); // Число проекций (0 - нет).

    const TokenizationTags *tags = proj.get_Tags();

    const int id_unknown_entry = GetUnknownEntryKey();

    Word_Form *wf = nullptr;

    for (int i = 0; i < n; i++)
        if (proj.CanAdd(coords[i], inf_list[i]))
        {
            const Word_Coord& wc = coords[i];
            const SG_Entry &e = s_gram.GetEntry(wc.GetEntry());
            const int entry_key = e.GetKey();

            if (wc.GetEntry() == I_NUMWORD)
            {
                // Статья для представления чисел в действительности не имеет форм,
                // хотя поле индекса формы в wc проинициализировано.
                wf = new Word_Form(
                    proj.GetContent(),
                    proj.GetContent(),
                    entry_key,
                    vals[i].score
                );
            }
            else
            {
                const SG_EntryForm form = s_gram.GetEntry(wc.GetEntry()).forms()[wc.GetForm()];
                wf = new Word_Form(
                    proj.GetOrgWord(),
                    proj.GetContent(),
                    entry_key,
                    form.coords(),
                    vals[i].score
                );
            }

            if (inf_list[i] != nullptr)
            {
                // Явно указан список координатных пар, которые надо установить
                // для проекции.
                const LA_ProjectInfo &inf = *inf_list[i];

                // Чтобы не было помех, удаляем возможные координатные пары
                // для добавляемой координаты.
                for (Container::size_type ie = 0; ie < inf.coords.size(); ie++)
                {
                    wf->Remove_Coord_States(inf.coords[ie].GetCoord());
                }

                // Добавляем координатную пару.
                for (Container::size_type ie = 0; ie < inf.coords.size(); ie++)
                {
                    wf->pairs().push_back(inf.coords[ie]);
                }
            }

            int filter_score = 0;
            if (tags != nullptr)
            {
                filter_score = tags->Score(*wf, GetDict());

                ProjScore v = ProjScore(vals[i].score + filter_score);

                if (proj.Add(coords[i], v, inf_list[i]))
                {
                    proj.Add(wf);
                    added = true;
                    wf = nullptr;
                }
            }
            else
            {
                if (proj.Add(coords[i], vals[i].score, inf_list[i]))
                {
                    proj.Add(wf);
                    added = true;
                    wf = nullptr;
                }
            }
        }

    return added;
}
#endif // defined SOL_CAA


/******************************************************************
 Вспомогательная процедура проекции мультилексемы на Лексикон без
 навороченных методов (с реискажениями и так далее). Используется
 внешними программами типа Argon.
*******************************************************************/
void LexicalAutomat::ProjectWord(
    const UCString &A,
    MCollect<Word_Coord> &found_list,
    MCollect<ProjScore> &val_list,
    lem::PtrCollect<LA_ProjectInfo> &prj_extra_inf,
    DynformsMode allow_dynforms,
    int nmissmax,
    int id_lang,
    LA_RecognitionTrace *trace
)
{
    Lexem lex(A);
    TranslateLexem(lex, true);
    RC_Lexem rc(&lex, null_deleter());
    ProjectWord(rc, found_list, val_list, prj_extra_inf, allow_dynforms, nmissmax, id_lang, trace);
    return;
}

void LexicalAutomat::ProjectWord(
    const RC_Lexem &A,
    MCollect<Word_Coord> &found_list,
    MCollect<ProjScore> &val_list,
    lem::PtrCollect<LA_ProjectInfo> &prj_extra_inf,
    DynformsMode allow_dynforms,
    int nmissmax,
    int id_lang,
    LA_RecognitionTrace *trace
)
{
    if (allow_dynforms ==/*DynformsMode::*/Wordforms && !nmissmax)
    {
#if defined SOL_CAA
        word_proj->Project(A, found_list, val_list, prj_extra_inf, id_lang, trace);

        if (found_list.empty())
#endif
        {
            Project_1(A, *A, 0.0f, found_list, val_list, prj_extra_inf, false, false, false, id_lang, trace);
        }
    }
    else
    {
#if defined SOL_CAA
        // Создаем задание на проекцию
        MLProjList ml_job(A, UNKNOWN, UNKNOWN);
        ml_job.set_Miss_Parameter(nmissmax);
        ml_job.set_Allow_Fuzzy(nmissmax > 0);
        ml_job.set_Dynforms(allow_dynforms !=/*DynformsMode::*/Wordforms);

        ProjectJob(ml_job, id_lang, true, trace);

        found_list = ml_job.GetCoordList();
        val_list = ml_job.GetCoordValList();
        prj_extra_inf = ml_job.GetExtraInf();

#else
        LEM_STOPIT;
#endif
    }

    return;
}



#if defined SOL_CAA
void LexicalAutomat::ProjectUnknown(
    const RC_Lexem &A,
    const lem::UCString & original_word,
    MCollect<Word_Coord> &found_list,
    MCollect<ProjScore> &val_list,
    PtrCollect<LA_ProjectInfo> &inf_list,
    int id_language,
    bool refresh_cache
)
{
    SynGram &sg = GetDict().GetSynGram();

    recognizer->Apply(*A, original_word, 0.0f, GetMinProjectionScore(), found_list, val_list, inf_list, id_language, false, nullptr);

    // Обновляем кэш осуществленных проекций.
#if defined LEM_THREADS
    lem::Process::CritSecLocker locker(&cs);
#endif

    if (!found_list.empty() && refresh_cache)
        word_proj->Add(LA_WordProjection(A, found_list, val_list, 1));

    return;
}
#endif



#if defined SOL_CAA
int LexicalAutomat::GuessLanguage(const Sentence & phrase)
{
    const int nlang = CastSizeToInt(GetDict().GetSynGram().languages().Count());

    lem::MCollect<float> lang_points;
    lang_points.resize(nlang);
    lang_points.fill(0.F);

    MCollect<Word_Coord> res;
    MCollect<ProjScore> val_list;
    lem::PtrCollect<LA_ProjectInfo> prj_extra_inf;

    for (lem::Container::size_type i = 0; i < phrase.size(); ++i)
    {
        const UCString &word = phrase.GetWord(CastSizeToInt(i));

        if (word.length() < 2)
            // пропускаем всякие пунктуаторы и даже односложные слова типа 'I', 'у'
            continue;

        const Lexem & sl = phrase.GetNormalizedWord(CastSizeToInt(i));

        RC_Lexem ml((Lexem*)&sl, null_deleter());
        res.clear();
        val_list.clear();
        prj_extra_inf.clear();

        ProjectWord(ml, res, val_list, prj_extra_inf, LexicalAutomat::Wordforms, 0, UNKNOWN, nullptr);

        for (lem::Container::size_type j = 0; j < res.size(); ++j)
        {
            const int ientry = res[j].GetEntry();
            if (ientry != UNKNOWN)
            {
                const SG_Entry &e = GetDict().GetSynGram().GetEntry(ientry);
                const int iclass = e.GetClass();
                const int id_lang = GetDict().GetSynGram().GetClass(iclass).GetLanguage();

                if (id_lang != UNKNOWN)
                {
                    lang_points[id_lang] += val_list[j].score;
                }
            }
        }
    }

    // Выбираем язык с максимальными баллами
    int imaxlang = UNKNOWN;
    float maxpoint = 0.F;

    for (int i = 0; i < nlang; i++)
    {
        if (lang_points[i] > maxpoint)
        {
            maxpoint = lang_points[i];
            imaxlang = i;
        }
    }

    return imaxlang;
}


/*
int LexicalAutomat::GuessLanguage( const lem::MCollect<UCString> &phrase )
{
 const int nlang = CastSizeToInt(GetDict().GetSynGram().languages().Count());

 lem::MCollect<float> lang_points;
 lang_points.resize(nlang);
 lang_points.fill(0.F);

 MCollect<Word_Coord> res;
 MCollect<Real1> val_list;
 lem::PtrCollect<LA_ProjectInfo> prj_extra_inf;

 for( lem::Container::size_type i=0; i<phrase.size(); ++i )
  {
   const UCString &word = phrase[i];

   if( word.length()<2 )
    // пропускаем всякие пунктуаторы и даже односложные слова типа 'I', 'у'
    continue;

   Lexem sl(word);
   TranslateLexem( sl, true );

   RC_Lexem ml( &sl, null_deleter() );
   res.clear();
   val_list.clear();
   prj_extra_inf.clear();

   ProjectWord( ml, res, val_list, prj_extra_inf, LexicalAutomat::Wordforms, 0, UNKNOWN, nullptr );

   for( lem::Container::size_type j=0; j<res.size(); ++j )
    {
     const int ientry = res[j].GetEntry();
     if( ientry!=UNKNOWN )
      {
       const SG_Entry &e = GetDict().GetSynGram().GetEntry(ientry);
       const int iclass = e.GetClass();
       const int id_lang = GetDict().GetSynGram().GetClass(iclass).GetLanguage();

       if( id_lang!=UNKNOWN )
        {
         lang_points[ id_lang ] += val_list[j].GetFloat();
        }
      }
    }
  }

 // Выбираем язык с максимальными баллами
 int imaxlang=UNKNOWN;
 float maxpoint=0.F;

 {
 for( int i=0; i<nlang; i++ )
  {
   if( lang_points[i]>maxpoint )
    {
     maxpoint = lang_points[i];
     imaxlang = i;
    }
  }
 }

 return imaxlang;
}
*/


// ****************************************************************
// Определение языка на основе выполненных проекций слов.
// В отличие от предыдущего метода, данный может опереться
// на сложные методы нечеткой проекции.
// ****************************************************************
/*
int LexicalAutomat::GuessLanguage( const Solarix::PhrasoBlock &phrase ) const
{
 const int nlang = CastSizeToInt(GetDict().GetSynGram().languages().Count());

 lem::MCollect<float> lang_points;
 lang_points.resize(nlang);
 lang_points.fill(0.F);

 MCollect<Word_Coord> res;
 MCollect<Real1> val_list;

 int nproj = phrase.GetnProj();

 for( int i=0; i<nproj; ++i )
  {
   const MLProjList& proj = phrase.GetProj(i);

   const int nalt = CastSizeToInt(proj.GetCoordList().size());

   for( int j=0; j<nalt; ++j )
    {
     const int ientry = proj.GetCoordList()[j].GetEntry();

     if( ientry!=UNKNOWN )
      {
       const SG_Entry &e = GetDict().GetSynGram().GetEntry(ientry);
       const int iclass = e.GetClass();
       const int id_lang = GetDict().GetSynGram().GetClass(iclass).GetLanguage();

       if( id_lang!=UNKNOWN )
        {
         const float ef = proj.GetCoordValList()[j].GetFloat();
         lang_points[ id_lang ] += ef;
        }
      }
    }
  }

 // Выбираем язык с максимальными баллами
 int imaxlang=UNKNOWN;
 float maxpoint=0.F;

 {
 for( int i=0; i<nlang; i++ )
  {
   if( lang_points[i]>maxpoint )
    {
     maxpoint = lang_points[i];
     imaxlang = i;
    }
  }
 }

 return imaxlang;
}
*/


// *************************************************************************
// Данный метод пытается определить язык на основе буквенной статистики.
// *************************************************************************
int LexicalAutomat::GuessLanguage(const lem::UFString &str) const
{
    const SynGram &sg = GetDict().GetSynGram();
    const GraphGram &gg = GetDict().GetGraphGram();

    lem::MCollect<int> lang_scores;
    lem::MCollect<int> lang_id;

    // Если список языков, для которых в лексиконе есть слова, известен,
    // то будем анализировать только эти языки.
    GetDict().GetLanguages(lang_id);

    if (lang_id.size() == 1)
    {
        return lang_id.front();
    }
    else if (lang_id.empty())
    {
        // Иначе - статанализ по всем языкам.
        std::unique_ptr<LanguageEnumerator> lenum(sg.languages().Enumerate());
        while (lenum->Fetch())
        {
            const int id_lang = lenum->GetId();
            lang_id.push_back(id_lang);
        }
        lenum.reset();
    }

    lang_scores.resize(lang_id.size());
    lang_scores.fill(0);

    const int nlang = CastSizeToInt(lang_id.size());

    MCollect<Word_Coord> projs;
    for (int i = 0; i < str.length(); ++i)
    {
        const wchar_t c = str[i];
        if (!lem::is_uspace(c) && !lem::is_udigit(c) && !lem::is_upunct(c))
        {
            projs.clear();
            gg.FindSymbol(c, projs);

            for (lem::Container::size_type j = 0; j < projs.size(); ++j)
            {
                const int isymbol = projs[j].GetEntry();
                const GG_Entry &symbol = gg.entries()[isymbol];
                const int id_alphabet = symbol.GetAlphabet();
                if (id_alphabet != UNKNOWN)
                {
                    std::unique_ptr<LanguageEnumerator> lenum(sg.languages().Enumerate());
                    while (lenum->Fetch())
                    {
                        const int id_lang = lenum->GetId();
                        const SG_Language &lang = lenum->GetItem();
                        if (lang.IsMainAlphabet(id_alphabet)) // проверяем только главные алфавиты, так как латиница может быть вторичным алфавитом для нескольких языков.
                        {
                            const int ilang = lang_id.find(id_lang);
                            if (ilang != UNKNOWN)
                                lang_scores[ilang] += 2;
                        }
                    }
                }
            }
        }
    }

    // Выбираем язык с максимальными баллами
    int imaxlang = UNKNOWN;
    int maxpoint = 0;

    for (int i = 0; i < nlang; i++)
    {
        if (lang_scores[i] > maxpoint)
        {
            maxpoint = lang_scores[i];
            imaxlang = i;
        }
    }

    if (maxpoint > 10)
    {
        // Проверим, что другие варианты распознавания достаточно малодостоверны.
        int min_dw = lem::int_max;
        for (int i = 0; i < nlang; i++)
        {
            if (i != imaxlang)
            {
                const int dw = maxpoint - lang_scores[i];
                if (dw < min_dw)
                {
                    min_dw = dw;
                    if (min_dw == 0)
                        break;
                }
            }
        }

        if (float(min_dw) / float(maxpoint) < 0.1)
        {
            // Разница выбранного победителя и серебрянного призера слишком
            // мала для достоверного выбора.
            // Применим более сложный алгоритм - с проекцией слов.
            if (GetDict().seeker.NotNull())
            {
                lem::Collect<UFString> words;
                lem::parse(str, words, L" \r\n\t,.:;'\"?!()*&-+=[{]}|<>", false);

                lang_scores.Nullify();

                for (lem::Container::size_type i = 0; i < words.size(); ++i)
                {
                    UCString word(words[i].c_str());
                    word.to_upper();

                    const int ie = GetDict().seeker->Find(word, true);
                    if (ie != UNKNOWN)
                    {
                        const SG_Entry &e = GetDict().GetSynGram().GetEntry(ie);
                        const int iclass = e.GetClass();
                        if (!lem::is_quantor(iclass))
                        {
                            const SG_Class &cls = GetDict().GetSynGram().GetClass(iclass);
                            const int id_lang = cls.GetLanguage();
                            if (id_lang != UNKNOWN)
                            {
                                const int ilang = lang_id.find(id_lang);
                                if (ilang != UNKNOWN)
                                    lang_scores[ilang]++;
                            }
                        }
                    }
                }
            }

            imaxlang = UNKNOWN;
            maxpoint = 0;

            for (int i = 0; i < nlang; i++)
            {
                if (lang_scores[i] > maxpoint)
                {
                    maxpoint = lang_scores[i];
                    imaxlang = i;
                }
            }
        }
    }

    return imaxlang == UNKNOWN ? UNKNOWN : lang_id[imaxlang];
}



int LexicalAutomat::GuessLanguage(const Solarix::Variator &phrase) const
{
    const int nlang = CastSizeToInt(GetDict().GetSynGram().languages().Count());

    lem::MCollect<float> lang_points;
    lang_points.resize(nlang);
    lang_points.fill(0.F);

    SynGram &sg = GetDict().GetSynGram();

    lem::MCollect<int> lang_id;
    std::unique_ptr<LanguageEnumerator> lenum(sg.languages().Enumerate());
    while (lenum->Fetch())
    {
        const int id_lang = lenum->GetId();
        lang_id.push_back(id_lang);
    }
    lenum.reset();


    MCollect<Word_Coord> res;
    MCollect<Real1> val_list;

    int nprojected = 0;

    for (int i = 1; i < phrase.size() - 1; ++i)
    {
        const Tree_Node & root = *phrase[i];

        const int nalt = 1 + CastSizeToInt(root.GetNode().GetAlts().size());

        for (int ialt = 0; ialt < nalt; ++ialt)
        {
            const Solarix::Word_Form &wf = ialt == 0 ? root.GetNode() : *root.GetNode().GetAlts()[ialt - 1];

            const int ekey = wf.GetEntryKey();

            if (ekey != UNKNOWN)
            {
                const SG_Entry &e = sg.GetEntry(ekey);
                const int iclass = e.GetClass();
                const int id_lang = GetDict().GetSynGram().GetClass(iclass).GetLanguage();

                if (id_lang != UNKNOWN)
                {
                    nprojected++;
                    const int ilang = lang_id.find(id_lang);
                    lang_points[ilang] += 1.F / float(nalt);
                }
            }
        }
    }

    if (!nprojected)
    {
        // по результатам проекции определить язык невозможно, будем использовать статистику по буквам
        UFString str;
        for (int i = 1; i < phrase.size() - 1; ++i)
        {
            const Tree_Node & root = *phrase[i];
            const Word_Form & wf = root.GetNode();

            if (!str.empty())
                str += L' ';

            str += wf.GetName()->c_str();
        }

        return GuessLanguage(str);
    }

    // Выбираем язык с максимальными баллами
    int imaxlang = UNKNOWN;
    float maxpoint = 0.F;

    {
        for (int i = 0; i < nlang; i++)
        {
            if (lang_points[i] > maxpoint)
            {
                maxpoint = lang_points[i];
                imaxlang = i;
            }
        }
    }

    return lang_id[imaxlang];
}



#if defined SOL_CAA
void LexicalAutomat::GetBaseForm(lem::UCString &word, bool allow_dynforms) const
{
    word.to_upper();

    if (GetDict().seeker.NotNull())
    {
        const int ie = GetDict().seeker->Find(word, allow_dynforms);

        if (ie != UNKNOWN)
            word = GetDict().GetSynGram().GetEntry(ie).GetName();
    }

    return;
}
#endif


#if defined SOL_CAA
void LexicalAutomat::GetAllProjections(
    const lem::UCString &word,
    bool allow_dynforms,
    lem::MCollect<int> &ies
)
{
    Lexem sl(word);
    TranslateLexem(sl, true);

    RC_Lexem ml(&sl, null_deleter());

    MCollect<Word_Coord> res;
    MCollect<ProjScore> val_list;
    lem::PtrCollect<LA_ProjectInfo> prj_extra_inf;

    ProjectWord(ml, res, val_list, prj_extra_inf, allow_dynforms ? LexicalAutomat::Dynforms_Last_Chance : LexicalAutomat::Wordforms, 0, UNKNOWN, nullptr);

    for (lem::Container::size_type j = 0; j < res.size(); ++j)
    {
        const int ientry = res[j].GetEntry();
        if (ientry != UNKNOWN && ies.find(ientry) == UNKNOWN)
            ies.push_back(ientry);
    }

    return;
}
#endif


#if defined SOL_CAA

/*
void LexicalAutomat::Segmentation( lem::PtrCollect<SentenceWord> & words, int LanguageID )
{
 const SynGram &sg = GetDict().GetSynGram();

 lem::zbool any_ml;


 for( lem::Container::size_type i=0; i<words.size(); ++i )
  {
   const Lexem & wl = words[i]->normalized_word;

   const int ml_len = sg.IsMultiLexemBegin(wl);

   if( ml_len>1 )
    {
     // если первая лексема также может быть самостоятельной формой какого-либо
     // слова, то выбор - сливать или не сливать мультилексему - сейчас не может быть
     // сделан.
     // С другой стороны, если для 2-лексемы второе слово не может являться
     // самостоятельной грамматической формой, то можно смело сливать.

     if( CastSizeToInt(i)<CastSizeToInt(words.size())-1 )
      {
       if( !sg.IsWordForm(wl) )
        {
         any_ml = true;
         break;
        }

       const int tail_size = CastSizeToInt(words.size())-CastSizeToInt(i);

       if( ml_len>=2 )
        {
         if( tail_size>=2 )
          {
           const Lexem & l2 = words[i+1]->normalized_word;

           if( !sg.IsWordForm(l2) )
            {
             // второе слово не может быть отдельной грамматической формой.
             any_ml = true;
             break;
            }

           if( ml_len>=3 )
            {
             // третье слово не может быть отдельной формой
             if( tail_size>=3 )
              {
               const Lexem & l3 = words[i+2]->normalized_word;

               if( !sg.IsWordForm(l3) )
                {
                 // убедимся, что второе и третье слово не образуют форму...
                 Lexem l23 = words[i+1]->normalized_word;
                 l23.Add(l3);

                 if( !sg.IsWordForm(l23) )
                  {
                   any_ml = true;
                   break;
                  }
                }
              }
            }
          }
        }
      }
    }
  }

 // Нужно проводить более тщательный анализ и слияние?
 if( any_ml )
  {
   // Да

   lem::zbool changed;
   lem::PtrCollect< SentenceWord > merged_words;

   int icur=0;
   while( icur<CastSizeToInt(words.size()) )
    {
     SentenceWord * cur_word = words[icur];

     const Lexem & wl = cur_word->normalized_word;
     const int ml_len =  sg.IsMultiLexemBegin(wl);

     if( ml_len<2 )
      {
       merged_words.push_back(cur_word);
       words[icur] = NULL;
       icur++;
      }
     else
      {
       bool headword_is_wordform=false;

       if( sg.IsWordForm(wl) )
        {
         headword_is_wordform=true;
        }

       bool found=false;

       // Попытаемся собрать максимально длинную мультилексему.
       for( int j=ml_len; j>1; j-- )
        {
         if( (icur+j) > CastSizeToInt(words.size()) )
          // У нас столько слов уже нету в правой части.
          continue;

         Lexem probe_lex(wl);

         bool do_probe=true;
         for( int k=1; k<j; ++k )
          {
           const Lexem & wl2 = words[icur+k]->normalized_word;

           if( headword_is_wordform )
            {
             // Если хоть одна лексема может быть отдельным словом, то сливать нельзя.

             if( sg.IsWordForm(wl2) )
              {
               do_probe=false;
               break;
              }

             const int ml2 = sg.IsMultiLexemBegin(wl2);
             if( ml2>1 && ml2<=j )
              {
               do_probe=false;
               break;
              }
            }

           if( !do_probe )
            break;

           probe_lex.Add(wl2);
          }

         if( !do_probe )
          continue;

         // Проецируем эту мультилексему...
         const bool is_ml = sg.IsMultiLexem( probe_lex );

         // Получилось?
         if( is_ml )
          {
           // Да.
           // Таким образом, собрали мультилексему.
           UCString ml_word( cur_word->word );

           for( int k=1; k<j; k++ )
            {
             #if LEM_DEBUGGING==1
             UCString wx(words[icur+k]->word);
             #endif

             if( words[icur+k]->word==L'-' || words[icur+k-1]->word==L'-' )
              {
               // Дефис не нуждается в пробелах слева и справа.
               // "КТО-ТО"
              }
             else if( words[icur+k]->word==L',' )
              {
               // Перед запятой пробел не нужен!
               // ПОСТОЛЬКУ, ПОСКОЛЬКУ
              }
             else
              {
               ml_word += Lexem::DelimiterChar;
              }

             ml_word += words[icur+k]->word;
            }

           SentenceWord * merged_word = new SentenceWord();
           merged_word->word = ml_word;
           merged_word->normalized_word = probe_lex;
           merged_words.push_back( merged_word );

           changed=true;
           icur+=j;
           found=true;
           break;
          }
        }

       if( !found )
        {
         merged_words.push_back( cur_word );
         words[icur] = NULL;
         icur++;
        }
      }
    }

   if( changed )
    {
     words = merged_words;
    }
   else
    {
     for( lem::Container::size_type i=0; i<merged_words.size(); ++i )
      {
       words[i] = merged_words[i];
       merged_words[i] = NULL;
      }
    }
  }

 return;
}
*/


/*
void LexicalAutomat::ConservativeSegmentation( Solarix::Phrasema &f )
{

 const SynGram &sg = GetDict().GetSynGram();

 lem::zbool any_ml;

 for( lem::Container::size_type i=0; i<words.size(); ++i )
  {
   const UCString &w = words[i];
   Lexem wl(w);
   TranslateLexem(wl,true);
   int ml_len = sg.IsMultiLexemBegin(wl);
   if( ml_len>1 )
    {
     any_ml = true;
     break;
    }
  }

 if( any_ml )
  {

  }

 return;
}
*/

#endif


int LexicalAutomat::Find_Quantor_Entry(int iclass)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker locker(&cs);
#endif

    auto it = unknown_entries.find(iclass);
    if (it == unknown_entries.end())
    {
        int res = GetDict().GetSynGram().Find_Quantor_Entry(iclass);
        unknown_entries.insert(std::make_pair(iclass, res));
        return res;
    }
    else
    {
        return it->second;
    }
}

#endif



#if defined SOL_CAA
CasingCoder& LexicalAutomat::GetCasingCoder()
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_casing_coder);
#endif

    if (casing_coder == nullptr)
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        casing_coder = new CasingCoder(GetSynGram());
        return *casing_coder;
    }
    else
    {
        return *casing_coder;
    }
}
#endif


#if defined SOL_CAA
Solarix::Word_Form* LexicalAutomat::ProjectWord2Wordform(const lem::UCString &word, int LanguageID)
{
    Solarix::Lexem *word2 = new Solarix::Lexem(word);
    this->TranslateLexem(*word2, true, LanguageID);
    RC_Lexem lex(word2);

    MCollect<Word_Coord> found_list;
    MCollect<ProjScore> val_list;
    lem::PtrCollect<LA_ProjectInfo> prj_extra_inf;

    this->ProjectWord(lex, found_list, val_list, prj_extra_inf, /*DynformsMode::*/Wordforms, 0, LanguageID, nullptr);

    Solarix::Word_Form *wf = nullptr;

    for (lem::Container::size_type i = 0; i < found_list.size(); ++i)
    {
        const int ekey = found_list[i].GetEntry();
        const Solarix::SG_Entry &e = GetDict().GetSynGram().GetEntry(ekey);
        CP_Array coords(e.forms()[found_list[i].GetForm()].coords());
        if (prj_extra_inf[i] != nullptr)
        {
            std::copy(prj_extra_inf[i]->coords.begin(), prj_extra_inf[i]->coords.end(), std::back_inserter(coords));
        }

        if (i == 0)
        {
            wf = new Solarix::Word_Form(lex, lex, ekey, coords, 0 /*Real1(100)*/);
        }
        else
        {
            Solarix::Word_Form *alt = new Solarix::Word_Form(lex, lex, ekey, coords, 0 /*Real1(100)*/);
            wf->AddAlt(alt);
        }
    }

    return wf;
}
#endif


void LexicalAutomat::ProjectWord(
    const lem::UCString &word,
    MCollect<Word_Coord> &found_list,
    int LanguageID
)
{
    Solarix::Lexem *word2 = new Solarix::Lexem(word);
    this->TranslateLexem(*word2, true, LanguageID);
    RC_Lexem lex(word2);

    MCollect<ProjScore> val_list;
    lem::PtrCollect<LA_ProjectInfo> prj_extra_inf;

    ProjectWord(lex, found_list, val_list, prj_extra_inf, /*DynformsMode::*/Wordforms, 0, LanguageID, nullptr);
    return;
}






#if defined SOL_CAA
bool LexicalAutomat::FindMisspeltWord(
    const lem::UCString &word,
    MCollect<lem::UCString> &corrected_word,
    int id_lang
)
{
    return recognizer->RewriteMisspeltWord(id_lang, word, corrected_word);
}
#endif


#if defined SOL_CAA
void LexicalAutomat::ListAssociationsForEntry(int id_entry, lem::MCollect<int> & ids)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_word_assoc);
#endif

    auto it = unassociated_words.find(id_entry);
    if (it == unassociated_words.end())
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        ids.clear();

        std::unique_ptr<LS_ResultSet> rs(GetStorage().ListAssociationsForEntry(id_entry));
        while (rs->Fetch())
        {
            ids.push_back(rs->GetInt(0));
        }
        rs.reset();

        if (ids.empty())
            unassociated_words.insert(id_entry);
    }

    return;
}
#endif
