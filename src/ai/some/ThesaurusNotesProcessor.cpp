// 28.08.2010 - добавлен подсценарий 'class' для выяснения грамматического класса фразы
//             
// CD->31.07.2010
// LC->29.06.2012

#include <lem/logfile.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/PhraseEntries.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/WrittenTextAnalysisSession.h>
#include <lem/solarix/ThesaurusNotesProcessor.h>

using namespace Solarix;


ThesaurusNotesProcessor::ThesaurusNotesProcessor( Solarix::Dictionary *dict )
{
 sol_id = dict;
 segmentation_delimiter=Solarix::SG_Net::DefaultSegmentationDelimiter;
 tn_type=UNKNOWN;
 id_lang=UNKNOWN;

 SynGram &sg = sol_id->GetSynGram();

 const wchar_t *pivot_class[]=
 {
  L"ENG_VERB", L"JAP_VERB",
  L"ENG_NOUN", L"JAP_NOUN",
  L"ENG_ADJECTIVE", L"JAP_ADJECTIVE",
  NULL
 };

 int i=0; 
 while( pivot_class[i]!=NULL )
  {
   UCString cn( pivot_class[i++] );
   const int id = sg.FindClass(cn);
   if( id==UNKNOWN )
    {
     lem::UFString msg( lem::format_str( L"Can not find class %ls", cn.c_str() ) );
     throw E_BaseException(msg);
    }

   pivot_iclass.push_back(id);
  }

 const char *PREPOSITIONS[]=
 {
  "ПРЕДЛОГ",
  "ENG_PREP",
  NULL,
 };

 i=0; 
 while( PREPOSITIONS[i]!=NULL )
  {
   UCString cn( lem::from_utf8(PREPOSITIONS[i++]).c_str() );
   const int id = sg.FindClass(cn);
   if( id==UNKNOWN )
    {
     lem::UFString msg( lem::format_str( L"Can not find class %ls", cn.c_str() ) );
     throw E_BaseException(msg);
    }

   prepositions.push_back(id);
  }



 const char *ADV[]=
 {
  "Russian", "НАРЕЧИЕ",
  "English", "ENG_ADVERB",
  "Japanese", "JAP_ADVERB",
  "French", "FR_ADVERB",
  "Chinese", "CN_ADVERB",
  NULL
 };

 i=0;
 while( ADV[i]!=NULL )
  {
   UCString lang( lem::from_utf8(ADV[i++]).c_str() );
   UCString cn( lem::from_utf8(ADV[i++]).c_str() );

   int id_lang = sg.Find_Language(lang);
   if( id_lang==UNKNOWN )
    {
     lem::UFString msg( lem::format_str( L"Can not find language %ls", lang.c_str() ) );
     throw E_BaseException(msg);
    }

   const int id_class = sg.FindClass(cn);
   if( id_class==UNKNOWN )
    {
     lem::UFString msg( lem::format_str( L"Can not find class %ls", cn.c_str() ) );
     throw E_BaseException(msg);
    }

   adverb_for_language.insert( std::make_pair(id_lang,id_class) );
  }




 NeutralLanguageId = sg.Find_Language(L"Neutral");

 ieu = sg.FindEntry( lem::UCString(L"UNKNOWNENTRY"), ANY_STATE, false );
 uekey = ieu==UNKNOWN ? UNKNOWN : sg.GetEntry(ieu).GetKey();

 id_JAP_VERB = sg.FindClass(L"JAP_VERB");
 id_JAP_VERB_BASE=sg.FindCoord(L"JAP_VERB_BASE").GetIndex();
 id_JAP_VB_PARTICIPLE=UNKNOWN;
 if( id_JAP_VERB_BASE!=UNKNOWN )
  {
   const Solarix::GramCoord &c = sg.coords()[id_JAP_VERB_BASE];
   id_JAP_VB_PARTICIPLE = c.FindState(L"PARTICIPLE");
  }

 

 return;
}



void ThesaurusNotesProcessor::SetSegmentationDelimiter( wchar_t c )
{
 if( c!=0 )
  segmentation_delimiter = c;

 return;
}

void ThesaurusNotesProcessor::SetLanguage( int id )
{
 id_lang = id;
 return;
}


void ThesaurusNotesProcessor::SetScenario( const lem::UFString &scenario )
{
 LEM_CHECKIT_Z( !scenario.empty() );

 // Сценарий. Строка может содержать несколько токенов - распарсим ее.
 lem::MCollect<lem::UCString> sc_toks;
 lem::parse( scenario, sc_toks, false );

 syntax=sc_toks.find(L"syntax")!=UNKNOWN;
 cleanup=sc_toks.find(L"cleanup")!=UNKNOWN;
 segmentation=sc_toks.find(L"segmentation")!=UNKNOWN;
 lemmatization=sc_toks.find(L"lemmatization")!=UNKNOWN;
 pivot=sc_toks.find(L"pivot")!=UNKNOWN;
 detect_class=sc_toks.find(L"class")!=UNKNOWN;

 if( segmentation )
  tn_type=Solarix::SynGram::SegmentationNote;
 else if( syntax )
  tn_type=Solarix::SynGram::SyntaxNote;
 else if( pivot )
  tn_type=Solarix::SynGram::PivotNote;

 return;
}


void ThesaurusNotesProcessor::SetLanguage( const lem::UCString &_language )
{
 // Определим код языка
 language = _language;
 id_lang = language.empty() ? UNKNOWN : sol_id->GetSynGram().Find_Language(language);
 if( id_lang==UNKNOWN && !language.empty() )
  {
   lem::UFString msg( lem::format_str( L"Language %ls is not found", language.c_str() ) );
   throw E_BaseException(msg);
  }

 return;
}


std::pair<bool/*processed*/,bool/*error*/> ThesaurusNotesProcessor::ProcessPhrase( int te_id )
{
 LEM_CHECKIT_Z( te_id!=UNKNOWN );

 bool err=false;
 bool processed=false;

 SynGram &sg = sol_id->GetSynGram();
 SG_Net &th = sg.Get_Net();

 SG_Phrase frz;
 sg.GetStorage().GetPhrase( te_id, frz );

 const lem::UFString & te_text = frz.GetText();
 
 LEM_CHECKIT_Z( !te_text.empty() );
   
 // Язык фразы может быть задан явно при объявлении.
 int is_language = frz.GetLanguage();

 lem::UFString txt;

 if( is_language==UNKNOWN )
  {
   // Попробуем определить язык фразы по статистическим критериям.
   is_language = id_lang==UNKNOWN ? UNKNOWN : sol_id->GetLexAuto().GuessLanguage(te_text);

   if( is_language==NeutralLanguageId )
    {
     // Побуквенная статистика не дала однозначного определения, придется
     // токенизировать без привязки к языку, делать проекцию.
     Solarix::Sentence sent0;
     sent0.Parse(te_text,false,NULL,UNKNOWN,NULL);
     is_language = sol_id->GetLexAuto().GuessLanguage(sent0);
    }   
  }

 lem::PtrCollect<UFString> classes;
 std::map<int,UFString> tokenizer_flags;

 if( cleanup && tn_type==UNKNOWN )
  {
   // удаляем все пометки для фразовой статьи
   sg.GetStorage().DeletePhraseNotes(te_id);
   processed=true;
   return std::make_pair(processed,err);
  }


 if( detect_class )
  {
   if(
      frz.GetClass()==UNKNOWN && // грамматический класс фразы еще не определен
      is_language==id_lang // Наш целевой язык
     )
    { 
     int id_class=UNKNOWN;
     int id_class0=UNKNOWN; 

     // нужно выполнить морфологический анализ фразы.
     WrittenTextAnalysisSession current_analysis( sol_id, NULL );
     current_analysis.params.SetLanguageID(id_lang);
     current_analysis.params.CompleteAnalysisOnly=true;
     current_analysis.MorphologicalAnalysis(te_text);

     lem::Ptr<Res_Pack> pack( current_analysis.PickPack() );
     pack->Save_Shortest_Vars();

     const int ivar = pack->GetShortestVar();
     if( ivar!=UNKNOWN )
      {
       const Variator &var = *pack->vars()[ivar];

       const Word_Form &wf0 = var.get(1).GetNode();  
       const int ekey0 = wf0.GetEntryKey();
       if( !lem::is_quantor(ekey0) )
        {
         const SG_Entry &e0 = sg.GetEntry(ekey0);
         id_class0 = e0.GetClass();
           
         // если есть альтернативы с другой частью речи, то сбрасываем.
         if( !wf0.GetAlts().empty())
          {
           for( lem::Container::size_type i=0; i<wf0.GetAlts().size(); ++i )
            {
             const int ekeyi = wf0.GetAlts()[i]->GetEntryKey();
             if( !lem::is_quantor(ekeyi) )
              {
               const SG_Entry &ei = sg.GetEntry(ekeyi);
               if( ei.GetClass()!=id_class0 )
                {
                 id_class0=UNKNOWN;
                 break;
                }
              }
            }
          }
        }

       if( id_class0!=UNKNOWN && IsPreposition(id_class0) )
        {
         // эвристика - если фраза начинается с предлога, то считаем ее наречием (это
         // скорее всего обстоятельство места ПОД КОВРОМ, В КИТАЕ).
         id_class=GetAdverbClassForLanguage(id_lang);
        } 
       else if( var.size()==3 )
        {
         // Если фраза содержит единственное слово, то дополнительный анализ не нужен.
         id_class = id_class0;
        }
       else
        {
         // Остальные случаи требуют запуска синтаксического анализатора. 
         WrittenTextAnalysisSession current_analysis( sol_id, NULL );
         current_analysis.params.SetLanguageID(id_lang);
         current_analysis.params.CompleteAnalysisOnly=true;
         current_analysis.SyntacticAnalysis(txt);

         lem::Ptr<Res_Pack> pack( current_analysis.PickPack() );

         pack->Save_Shortest_Vars();

         const int ivar = pack->GetShortestVar();
         if( ivar!=UNKNOWN )
          {
           const Variator &var = *pack->vars()[ivar];
           if( var.size()==3 )
            {
             const Solarix::Word_Form &root = var.get(1).GetNode();
             const int ekey0 = root.GetEntryKey();
             if( !lem::is_quantor(ekey0) )
              {
               const SG_Entry &e0 = sg.GetEntry(ekey0);
               id_class = e0.GetClass();
         
               // если есть альтернативы с другой частью речи, то сбрасываем.
               if( !root.GetAlts().empty())
                {
                 for( lem::Container::size_type i=0; i<root.GetAlts().size(); ++i )
                  {
                   const int ekeyi = root.GetAlts()[i]->GetEntryKey();
                   if( !lem::is_quantor(ekeyi) )
                    {
                     const SG_Entry &ei = sg.GetEntry(ekeyi);
                     if( ei.GetClass()!=id_class )
                      {
                       id_class=UNKNOWN;
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

     if( id_class!=UNKNOWN )
      {
       // надо обновить поле грамматического класса у фразы.

       if( lem::LogFile::IsOpen() )
        {
         lem::LogFile::logfile->printf( "Class detection for phrase '%us' class=%us\n", te_text.c_str(), sg.GetClass(id_class).GetName().c_str() );
        }

       frz.SetClass(id_class);  
       sg.GetStorage().UpdatePhrase( frz );
       processed=true;
      } 
    }

   return std::make_pair(processed,err);
  }



 SG_PhraseNote note;
 const int tn_id = sg.GetStorage().GetPhraseNote( te_id, tn_type, note );
 txt = note.GetData(); 

 if( cleanup && tn_id!=UNKNOWN )
  {
   // Запись в TNOTES нужного типа есть - удаляем ее.
   if( cleanup )
    {
     // особый случай - удаляем
     sg.GetStorage().DeletePhraseNote(tn_id);
     processed=true;
    }
     
   return std::make_pair(processed,err);
  }

 if( tn_id==UNKNOWN && !cleanup )
  {
   // Нужных данных нет, будем генерировать!
   if( segmentation )
    {
     if( tokenizer.IsNull() )
      { 
       tokenizer = sol_id->GetSentenceTokenizer(id_lang);
       if( tokenizer.IsNull() )
        {
         lem::UFString msg( lem::format_str( L"Can not create tokenizer for %ls", language.c_str() ) );
         throw E_BaseException(msg); 
        }
      }

     // Наш целевой язык?
     if( is_language==id_lang )
      {
       // Да.
       if( lemmatization )
        {
         WrittenTextAnalysisSession current_analysis( sol_id, NULL );
         current_analysis.params.SetLanguageID(id_lang);
         current_analysis.params.CompleteAnalysisOnly = true;
         current_analysis.MorphologicalAnalysis(te_text);
         lem::Ptr<Res_Pack> pack( current_analysis.PickPack() );
         
         pack->Save_Shortest_Vars();

         const int ivar = pack->GetShortestVar();
         const Variator &var = *pack->vars()[ivar];
         txt.clear();

         Solarix::CplxLeft cplx;
         cplx.headword = * var.get(1).GetNode().GetNormalized();
         cplx.minlen = cplx.maxlen = var.size()-2;

         for( int k=1; k<var.size()-1; ++k )
          {
           lem::UCString word;

           const int ekey = var.get(k).GetNode().GetEntryKey();
           
           if( ekey==UNKNOWN || ekey==uekey )
            {
             word = *var.get(k).GetNode().GetName(); 

             if( lem::LogFile::IsOpen() )
              {
               lem::LogFile::logfile->printf("Can not lemmatize word [%us] in phrase [%us]\n", word.c_str(), te_text.c_str() );
              }

             err=true;
            } 
           else
            {
             const SG_Entry &e = sol_id->GetSynGram().GetEntry( ekey );

             word = e.GetName();
             
             Lexem::CorrectFormSpaces(word); // ... убираем лишние пробелы ...
            }

           word.to_upper();

           if( !txt.empty() )
            txt.Add_Dirty(segmentation_delimiter);

           txt.Add_Dirty( word.c_str() );  
          }  

         // Запоминаем результат токенизации в TNOTES
         sg.GetStorage().AddPhraseNote( te_id, tn_type, txt );

         // И нужно обновить информацию в CPLX_LEFT
         sg.GetStorage().StoreCplxLeft( cplx.headword, cplx.minlen, cplx.maxlen );
         processed=true;
        }
       else
        {  
         // выполняем токенизацию.
         Sentence toks;
         toks.Parse(te_text,false,sol_id,id_lang,NULL);

         txt = toks.string(segmentation_delimiter); // токенизированная строка
         txt.to_upper(); 
 
         // Запоминаем результат токенизации в TNOTES
         sg.GetStorage().AddPhraseNote( te_id, tn_type, txt );

         // И нужно обновить информацию в CPLX_LEFT
         Solarix::CplxLeft cplx;
         cplx.headword = toks.GetNormalizedWord(0);
         cplx.minlen = cplx.maxlen = CastSizeToInt(toks.size());
         sg.GetStorage().StoreCplxLeft( cplx.headword, cplx.minlen, cplx.maxlen );
         processed=true;
        }
      }
    }
   else if( syntax )
    { 
     if( 
        is_language==id_lang // Наш целевой язык?
        && (frz.GetSyntaxFlags()&frz_no_syntax)!=frz_no_syntax // для фразы можно делать синт. анализ
       )
      {
       WrittenTextAnalysisSession current_analysis( sol_id, NULL );
       current_analysis.params.SetLanguageID(id_lang);
       current_analysis.params.CompleteAnalysisOnly = true;
       current_analysis.SyntacticAnalysis(te_text);
       lem::Ptr<Res_Pack> pack( current_analysis.PickPack() );

       bool syntax_ok=false;

       pack->Save_Shortest_Vars();

       const int ivar = pack->GetShortestVar();
       if( ivar!=UNKNOWN )
        {
         const Variator &var = *pack->vars()[ivar];

         lem::MemStream mem(true);
         var.SaveBin(mem);
         txt.clear();
  
         int sz = CastSizeToInt(mem.fsize());
         for( int q=0; q<sz; ++q )
          {
           const lem::uint8_t byte = mem.get_Block()[q];
           int hi4 = (byte>>4) & 0x0f;
           int lo4 = byte & 0x0f;
           txt.Add_Dirty( lem::get_unumerique(hi4) );
           txt.Add_Dirty( lem::get_unumerique(lo4) );
          }

         txt.calc_hash();
         sg.GetStorage().AddPhraseNote( te_id, tn_type, txt );
         processed=true;
         syntax_ok=true; 
        }

       if( !syntax_ok )
        {
         if( lem::LogFile::IsOpen() )
          {
           lem::LogFile::logfile->printf( "Unsuccessful syntax analysis for phrase [%us]\n", te_text.c_str() );
          }

         err=true; 
        }
      }
    }
   else if( pivot )
    {
     if( is_language==id_lang )
      {
       // Определяем ведущее слово.
       // Самый простой алгоритм - делаем морфологический анализ фразы и ищем слова
       // в таком порядке:
       //
       // 1. глагол (не те-форма)
       // 2. существительное
       // 3. прилагательное 
       //
       // Если соответствующая часть речи в единственном экземпляре - берем ее.
       // Иначе нужен более сложный анализ.
       bool pivot_found=false;
       int pivot_iword=UNKNOWN;

       Sentence sent;
       sent.Parse(te_text,false,sol_id,id_lang,NULL);

       // Если слева единственное слово - дополнительный анализ не нужен 
       if( sent.size()==1 )
        {
         pivot_found=true;
         pivot_iword=0;
        } 

       if( !pivot_found )
        {
         WrittenTextAnalysisSession current_analysis( sol_id, NULL );
         current_analysis.params.SetLanguageID(id_lang);
         current_analysis.params.CompleteAnalysisOnly = false;

         current_analysis.MorphologicalAnalysis(te_text);
         lem::Ptr<Res_Pack> pack( current_analysis.PickPack() );

         pack->Save_Shortest_Vars();

         const int ivar = pack->GetShortestVar();
         if( ivar!=UNKNOWN )
          {
           const Variator &var = *pack->vars()[ivar];

           pivot_iword=UNKNOWN;
           for( lem::Container::size_type ic=0; ic<pivot_iclass.size(); ++ic )
            {
             const int id_class = pivot_iclass[ic];

             // Сколько слов данного класса присутствует?
             int nword=0, iword=UNKNOWN;
           
             for( int k=1; k<var.size()-1; ++k )
              {
               const Solarix::Word_Form &wf = var.get(k).GetNode();
               const int n = 1+CastSizeToInt(wf.GetAlts().size());

               // соберем индексы (без повтора) классов для всех вариантов проекции слова.
               lem::MCollect<int> wf_classes;
               for( int j=0; j<n; ++j )
                {
                 const int ekey = j==0 ? wf.GetEntryKey() : wf.GetAlts().get(j-1)->GetEntryKey();
                 if( ekey!=UNKNOWN && ekey!=uekey )
                  {
                   const SG_Entry &e = sol_id->GetSynGram().GetEntry( ekey );
                   const int icls = e.GetClass();

                   if( icls==id_JAP_VERB )
                    {
                     if( j==0 )
                      {
                       const int ivform = wf.GetState( GramCoordAdr(id_JAP_VERB_BASE) );
                       if( ivform==id_JAP_VB_PARTICIPLE )
                        continue;
                      }
                     else
                      {
                       const int ivform = wf.GetAlts().get(j-1)->GetState( GramCoordAdr(id_JAP_VERB_BASE) );
                       if( ivform==id_JAP_VB_PARTICIPLE )
                        continue;
                      }  
                    }                     

                   if( wf_classes.find(icls)==UNKNOWN )
                    wf_classes.push_back(icls);
                  }
                }
 
               // Искомый класс присутствует?
               if( wf_classes.find(id_class)!=UNKNOWN )                
                {
                 nword++;
                 iword = k-1;
                 if( nword==2 )
                  break;
                }
              }
 
             if( nword==1 )
              {
               pivot_found = true;
               pivot_iword = iword;
               break; 
              }

             if( nword>1 )
              {
               // слов такого класса несколько, значит простой алгоритм не прошел.
               pivot_found=false;
               break;
              }
            }
          }
        }

       if( !pivot_found )
        {
         // Предыдущий алгоритм не дал результата.
         // Более сложный подход.
         // Выполняем синтаксический анализ, смотрим на корень получившегося графа,
         // его и считаем ведущим словом.
         WrittenTextAnalysisSession current_analysis( sol_id, NULL );
         current_analysis.params.SetLanguageID(id_lang);
         current_analysis.params.CompleteAnalysisOnly = false;

         current_analysis.SyntacticAnalysis(te_text);
         lem::Ptr<Res_Pack> pack( current_analysis.PickPack() );
         
         bool syntax_ok=false;
         pack->Save_Shortest_Vars();

         const int ivar = pack->GetShortestVar();
         if( ivar!=UNKNOWN )
          {
           const Variator &var = *pack->vars()[ivar];
           if( var.size()==3 )
            {
             const Solarix::Word_Form &root = var.get(1).GetNode();
             pivot_iword = root.GetOriginPos();
             pivot_found = pivot_iword!=UNKNOWN;
            }  
          }

         if( !pivot_found )
          {
           if( lem::LogFile::IsOpen() )
            {
             lem::LogFile::logfile->printf( "Unsuccessful syntax analysis for phrase [%us]\n", te_text.c_str() );
            }

           err=true;
          }
        }

       // Если нашли ведущее слово, то запоминаем его индекс.
       if( pivot_found && pivot_iword!=UNKNOWN )
        {
         lem::UFString txt = lem::to_ustr(pivot_iword).c_str();
         sg.GetStorage().AddPhraseNote( te_id, tn_type, txt );
         processed=true;
        }
       else
        {
         err=true;
         if( lem::LogFile::IsOpen() )
          {
           lem::LogFile::logfile->printf( "Can not find pivot word in phrase [%us]\n", te_text.c_str() );
          }
        }
      } 
    } 
  }

 return std::make_pair(processed,err);
}



int ThesaurusNotesProcessor::GetAdverbClassForLanguage( int id_language ) const
{
 std::map<int,int>::const_iterator it = adverb_for_language.find(id_language);
 if( it!=adverb_for_language.end() )
  {
   return it->second;
  }
 else
  {
   return UNKNOWN;
  } 
} 

