#if !defined(SOL_NO_NGRAMS)

#include <lem/solarix/_sg_api.h>
#include <lem/solarix/NGramsCollectors.h>
#include <lem/solarix/WordEntry.h>

using namespace std;
using namespace lem;
using namespace Solarix;



CovalentNGramsCollector::CovalentNGramsCollector( Solarix::NGramsCollectorFlags::Flags _correl )
 : RawNGramsCollector()
{
 correl = _correl;

 lemmatization = true;

 accum_1grams = false;
 accum_2grams = true;
 accum_3grams = false;

 needs_WORDS=false;
 needs_NGRAM1=false;
 needs_NGRAM2=true;
 needs_NGRAM3=false;

 return;
}


void CovalentNGramsCollector::PresetTablesSuffix(void)
{
 switch(correl)
 { 
  case NGramsCollectorFlags::Noun_Noun:   suffix0 = "_n_2_n";   break;
  case NGramsCollectorFlags::Adj_Noun:    suffix0 = "_a_2_n";   break;
  case NGramsCollectorFlags::Noun_Verb:   suffix0 = "_n_2_v";   break;
  case NGramsCollectorFlags::Adverb_Verb: suffix0 = "_adv_2_v"; break;
  case NGramsCollectorFlags::Adverb_Adj:  suffix0 = "_adv_2_a"; break;
  case NGramsCollectorFlags::Prepos_Noun: suffix0 = "_p_2_n";   break;
  case NGramsCollectorFlags::Verb_Object: suffix0 = "_obj_2_v"; break;
  default:
   LEM_STOPIT;  
 }

 suffix = suffix0;

 if( !segment_n.empty() )
  suffix += FString("_")+segment_n;

 suffix.re_clear();

 return;
}

void CovalentNGramsCollector::Prepare(
                                      lem::Ptr<Solarix::Dictionary> _dict,
                                      const lem::Path &_outdir,
                                      Language _language
                                     )
{
 RawNGramsCollector::Prepare(_dict,_outdir,_language);

 #if defined LEM_WINDOWS
 stopverbs_ru.push_back( sg->FindEntry( UCString(L"БЫТЬ"), INFINITIVE_ru, false ) );
 #endif

 const wchar_t *vl[] = 
                      {
                       #if defined LEM_WINDOWS
                       L"БЫТЬ",
                       L"НАЧАТЬ",
                       L"НАЧИНАТЬ",
                       L"ХОТЕТЬ",
                       L"ЗАХОТЕТЬ",
                       L"МОЧЬ",
                       L"ДОЛЖЕНСТВОВАТЬ",
                       L"ИМЕТЬ",
                       L"СМОЧЬ",
                       L"ПРИЙТИ_2",
                       L"ЕСТЬ_2",
                       #endif    
                       NULL
                      };  

 int i=0;
 while( vl[i]!=NULL )
  {
   Solarix::Lexem lex( vl[i++] );
   la->TranslateLexem(lex,true);
   const int ie = sg->FindEntry( lex, VERB_ru, false );
   if( ie!=UNKNOWN )
    stopverbs_ru.push_back( ie );
  }


 const wchar_t *al[] = 
                        {
                         #if defined LEM_WINDOWS  
                         L"ТОТ",
                         L"СВОЙ",
                         L"КАКОЙ",
                         L"ЕГО",
                         L"ЭТАКИЙ",
                         L"КОТОРЫЙ",
                         L"ИХ",
                         L"НАШ",
                         L"САМ",
                         L"МОЙ",
                         L"ЭТОТ",
                         L"ЕЕ",
                         L"ТАКОЙ",
                         L"ВАШ",
                         L"ЧЕЙ",
                         #endif 
                         NULL
                        };  

 i=0;
 while( al[i]!=NULL )
  {
   Lexem lex(al[i++]);
   la->TranslateLexem(lex,true);
   const int ie = sg->FindEntry( lex, ADJ_ru, false );
   if( ie!=UNKNOWN )
    stopadjs_ru.push_back( ie );
  }


 const wchar_t *advl[] = 
                        {
                         #if defined LEM_WINDOWS
                         L"НЕУЖЕЛИ", L"ХОТЬ", L"УЖЕ", L"НИЧЕГО", L"НИКАК",
                         L"ЕЩЕ", L"ВОКРУГ", L"ВОВСЕ", L"ПУСТЬ", L"СРАЗУ", 
                         L"ТАК", L"КАК", L"БУДЕТ", L"ЧЕРЕЗ", L"СТАЛО", 
                         L"ТАКИ", L"КУДА", L"ПОЧЕМУ", L"СЕЙЧАС", 
                         L"ЗАЧЕМ", L"ГДЕ", L"ТЕПЕРЬ", L"РАЗВЕ", L"ТОГДА", 
                         L"УЖ", L"ТУТ",
                         L"ВООБЩЕ", L"ТАМ", L"ХУЖЕ",
                         #endif
                         NULL
                        };  

 i=0;
 while( advl[i]!=NULL )
  {
   Lexem lex(advl[i++]);
   la->TranslateLexem(lex,true);
   const int ie = sg->FindEntry( lex, ADVERB_ru, false );
   if( ie!=UNKNOWN )
    stopadvs_ru.push_back( ie );
  }

 
 const wchar_t *en_modal[] =
 { 
  L"BE", L"HAVE", L"DO", L"GET", L"CAN", L"MUST", L"NEED", L"SHOULD",
  L"WOULD", L"MAY", L"OUGHT", L"WILL", L"SHALL",
  L"BE_NOT", L"HAVEN'T", L"DON'T", L"CANNOT",
  NULL
 };
 
 i=0;
 while( en_modal[i]!=NULL )
  {
   Lexem lex(en_modal[i++]);
   la->TranslateLexem(lex,true);
   const int ie = sg->FindEntry( lex, VERB_en, false );
   if( ie!=UNKNOWN )
    stopverbs_en.push_back( ie );
  }


 distance = 2;
 add_reverse_links = false;

 switch(correl)
 {
  case NGramsCollectorFlags::Noun_Noun:
  {
   distance = 5;
   add_reverse_links = true;
   break;
  }

  case NGramsCollectorFlags::Adj_Noun:
  {
   // Для ловли конструкций БОЛЬШАЯ БЕЛАЯ КОШКА
   distance = 2;
   break;
  }

  case NGramsCollectorFlags::Verb_Object:
  {
   distance = 2; // чтобы ловить именно конструкции управления 'кошка ВИДИТ МЫШКУ' и 'кошка ВИДИТ жирную КОШКУ'
   break;
  }

  case NGramsCollectorFlags::Noun_Verb:
  {
   distance = 3; // для ловли сложных глагольных времен типа КОШКА НАЧАЛА ТИХО СПАТЬ
   break;
  }

  case NGramsCollectorFlags::Adverb_Verb:
  {
   distance = 2;
   break;
  }

  case NGramsCollectorFlags::Adverb_Adj:
  {
   distance = 2;
   break;
  }

  case NGramsCollectorFlags::Prepos_Noun:
  {
   distance = 2;
   break;
  }

  default:
   LEM_STOPIT;
 } 

 return;
}


void CovalentNGramsCollector::ProcessSentence( const lem::MCollect<UCString> &sent )
{
 // Ищем в словаре каждое из слов.
 lem::MCollect<int> sentence_ie;
 lem::MCollect<int> sentence_iclass;

 for( lem::Container::size_type i=0; i<sent.size(); ++i )
  {
   const UCString &w = sent[i];
   Solarix::Lexem lex(w);
   la->TranslateLexem( lex, false );

   const int ie = FindIE(lex);
   sentence_ie.push_back(ie);

   int iclass = IE_2_IClass(ie);
   sentence_iclass.push_back(iclass);
  }

 // Обрабатываем пары.
 const int nlex_range = distance;

 if( !sentence_ie.empty() )
  {
   for( lem::Container::size_type i=0; i<sentence_ie.size(); ++i )
    {
     // Контролируем, чтобы расстояние между лексемами было не больше nlex_range
     int nlex=1;

     for( lem::Container::size_type j=i+1; j<sentence_ie.size() && nlex<=nlex_range; j++, nlex++ )
      {
       int ie1 = sentence_ie[i];
       int ie2 = sentence_ie[j];

       UCString word1 = sent[i];
       UCString word2 = sent[j];

       #if LEM_DEBUGGING==1
       //mout->printf( "word1=%us word2=%us\n", word1.c_str(), word2.c_str() );
       #endif

       int ic1 = sentence_iclass[i];
       int ic2 = sentence_iclass[j];

       if( ie1==ie2 || ie1==UNKNOWN || ie2==UNKNOWN )
        continue; 

       if( correl==NGramsCollectorFlags::Prepos_Noun && nlex==2 )
        {
         // Допускается только конструкция типа ПО БЕЛОМУ СНЕГУ
         // то есть между предлогом и существительным должно быть прилагательное
         if( sentence_iclass[i+1]!=ADJ_ru )
          continue;

         int ie05 = sentence_ie[i+1];
         UCString word05 = sent[i+1];
         int ic05 = sentence_iclass[i+1];

         Consider3Gram( ie1, ic1, word1, ie05, ic05, word05, ie2, ic2, word2 );
        }
       else if( correl==NGramsCollectorFlags::Verb_Object && nlex==2 )
        {
         // Допускается только конструкция типа ВИДИТ БЕЛУЮ КОШКУ
         // то есть между глаголом и существительным должно быть прилагательное
         if( sentence_iclass[i+1]!=ADJ_ru )
          continue;

         int ie05 = sentence_ie[i+1];
         UCString word05 = sent[i+1];
         int ic05 = sentence_iclass[i+1];
         Consider3Gram( ie1, ic1, word1, ie05, ic05, word05, ie2, ic2, word2 );
        }
       else
        {  
         Consider2Gram( ie1, ic1, word1, ie2, ic2, word2 );
         if( add_reverse_links )
          Consider2Gram( ie2, ic2, word2, ie1, ic1, word1 );
        }
      }
    }
  }

 return;
}



void CovalentNGramsCollector::EndDocument( bool echo )
{
 RawNGramsCollector::EndDocument(echo);
 return;
}


int CovalentNGramsCollector::ToVerb( int ie_inf )
{
 lem::MCollect<int> keys;
 if( la->Translate_To_Verbs( sg->GetEntry(ie_inf).GetKey(), keys ) )
  {
   if( !keys.empty() )
    return keys.front();//sg->FindEntryIndexByKey( keys.front() );
  }

 return UNKNOWN;
}

#define is_verbal(ic) (ic==VERB_ru || ic==INFINITIVE_ru || ic==GERUND_2_ru || ic==ADJ_ru)

void CovalentNGramsCollector::Consider2Gram(
                                            int ie_prev,
                                            int iclass_prev,
                                            const UCString &word_prev,
                                            int ie,
                                            int iclass,
                                            const UCString &word
                                           )
{
 LEM_CHECKIT_Z(ie!=NULL);
 LEM_CHECKIT_Z(ie_prev!=NULL);
 
 if( correl == Solarix::NGramsCollectorFlags::Noun_Noun )
  {   
   if( iclass==NOUN_ru && iclass_prev==NOUN_ru )
    {
     // берем ТОЛЬКО пары типа "ДОМ КОШКИ"
     // то есть второе существительное должно быть в родительном падеже
 
     Lexem ll(word);
     RC_Lexem ml( &ll, null_deleter() );

     MCollect<Word_Coord> res;
     MCollect<Solarix::ProjScore> val_list;
     PtrCollect<LA_ProjectInfo> inf_list;

     la->ProjectWord( ml, res, val_list, inf_list, LexicalAutomat/*::DynformsMode*/::Wordforms, 0, UNKNOWN, NULL );

     bool ignore=true;

     for( lem::Container::size_type j=0; j<res.size(); ++j )
      {
       const SG_Entry &e = sg->GetEntry(res[j].GetEntry());
       if( e.forms()[ res[j].GetForm() ].FindDimState( GramCoordAdr( CASE_ru ) )==GENITIVE_CASE_ru )
        {
         ignore = false;
         break;
        }
      } 

     if( !ignore )
      {
       Store2Gram( ie, ie_prev, 1 );
      }
    }
  }
 else if( correl == Solarix::NGramsCollectorFlags::Adj_Noun )
  {
   if( iclass==NOUN_ru && iclass_prev==ADJ_ru )
    {
     // Найдена пара ПРИЛАГАТЕЛЬНОЕ-СУЩЕСТВИТЕЛЬНОЕ
     int ie1 = ie;      // сущ 
     int ie2 = ie_prev; // прил

     // Уберем некоторые прилагательные
     bool ignore = false;
     switch( language )
     { 
      case Russian:
      {
       ignore = stopadjs_ru.find(ie2)!=UNKNOWN;
       break;
      }

      case English:
      {
       ignore = stopadjs_en.find(ie2)!=UNKNOWN;
       break;
      }
     } 

     // проверим согласование
     bool do_add = true;//!ignore && Solarix::Syntax_Analyzer::Check_Correlation( &*sol_id, word_prev, word )==true;

     if( do_add )
      { 
       Store2Gram( ie2, ie1, 1 );
      }
    }
  }
 else if( correl == Solarix::NGramsCollectorFlags::Prepos_Noun )
  {
   if( iclass==NOUN_ru && iclass_prev==PREPOS_ru )
    {
     // Найдена пара ПРЕДЛОГ-СУЩЕСТВИТЕЛЬНОЕ
     Store2Gram( ie_prev, ie, 1 );
    }
  }
 else if( correl == Solarix::NGramsCollectorFlags::Verb_Object )
  {
   if( iclass==NOUN_ru && iclass_prev==VERB_ru )
    {
     // глагол+управляемый_объект
     Store2Gram( ie, ie_prev, 1 );
    }
   else if( iclass==NOUN_ru && iclass_prev==INFINITIVE_ru )
    {
     // инфинитив преобразуем к глаголу
     MCollect<int> verbs;
     if( sol_id->GetLexAuto().Translate_To_Verbs( sol_id->GetSynGram().GetEntry(ie_prev).GetKey(), verbs ) )
      {
       ie_prev = verbs.front();//sol_id->GetSynGram().FindEntryIndexByKey( verbs.front() );
       Store2Gram( ie, ie_prev, 1 );
      } 
    }
   else if( iclass==NOUN_ru && is_verbal(iclass_prev) )
    {
     // глагол+управляемый_объект
     int ie_verb = ToVerb(ie_prev);
     if( ie_verb!=UNKNOWN )
      Store2Gram( ie, ie_verb, 1 );
    }
  }
 else if( correl == Solarix::NGramsCollectorFlags::Noun_Verb )
  {
   if( iclass==VERB_ru && iclass_prev==NOUN_ru )
    {
     if( ie!=UNKNOWN )
      { 
       // Найдена пара СУЩЕСТВИТЕЛЬНОЕ(ie_prev)-ГЛАГОЛ(ie)
       // Семантически это должны быть сочетания АКТОРА и его ДЕЙСТВИЯ, например 'кошка спит'
       bool ignore=true;

       // Берем только существительные в именительном падеже
       Lexem ll(word_prev);
       RC_Lexem ml( &ll, null_deleter() );

       MCollect<Word_Coord> res;
       MCollect<Solarix::ProjScore> val_list;
       PtrCollect<LA_ProjectInfo> inf_list;

       la->ProjectWord( ml, res, val_list, inf_list, LexicalAutomat/*::DynformsMode*/::Wordforms, 0, UNKNOWN, NULL );
  
       if( !res.empty() )
        {
         for( lem::Container::size_type j=0; j<res.size() && ignore; ++j )
          {
           const SG_Entry &e = sg->GetEntry(res[j].GetEntry());
           const int iform = res[j].GetForm();
           LEM_CHECKIT_Z( iform!=UNKNOWN );
           if( e.GetClass()==NOUN_ru && e.forms()[ iform ].FindDimState( GramCoordAdr( CASE_ru ) )==NOMINATIVE_CASE_ru )
            ignore = false;
          } 
        } 
       
       if( !ignore )
        {
         // Исключаем служебные глаголы
         switch( language )
         { 
          case Russian:
          {
           ignore = stopverbs_ru.find(ie)!=UNKNOWN;
           break;
          }

          case English:
          {
           ignore = stopverbs_en.find(ie)!=UNKNOWN;
           break;
          }
         } 

         // проверим согласование
//         if( !ignore && Solarix::Syntax_Analyzer::Check_Correlation( &*sol_id, word_prev, word )!=true )
//          ignore = true; 
        }

       if( !ignore )
        { 
         int ie_verb = ie;
         int ie_noun = ie_prev;
         Store2Gram( ie_verb, ie_noun, 1 );
        }
      }
    }
  }
 else if( correl == Solarix::NGramsCollectorFlags::Adverb_Adj )
  {
   if( iclass==ADJ_ru && iclass_prev==ADVERB_ru )
    {
     // Найдена пара НАРЕЧИЕ-ПРИЛАГАТЕЛЬНОЕ
     int ie1 = ie;        // прилагательное 
     int ie2 = ie_prev;   // наречие

     // Уберем некоторые наречия
     bool ignore = false;
     switch( language )
     { 
      case Russian:
      {
       ignore = stopadvs_ru.find(ie2)!=UNKNOWN || stopadjs_ru.find(ie1)!=UNKNOWN;
       break;
      }

      case English:
      {
       ignore = stopadvs_en.find(ie2)!=UNKNOWN || stopadjs_en.find(ie1)!=UNKNOWN;
       break;
      }
     } 

     if( !ignore )
      {
       Store2Gram(ie2,ie1,1);
      }
    }
  }
 else if( correl == Solarix::NGramsCollectorFlags::Adverb_Verb )
  {
   if(
      (is_verbal(iclass) && iclass_prev==ADVERB_ru) ||
      (iclass==ADVERB_ru && is_verbal(iclass_prev) )
     )
    {
     // Найдена пара НАРЕЧИЕ-ГЛАГОЛ

     int ie1 = ie;      // глагол
     int ie2 = ie_prev; // наречие

     if( iclass==ADVERB_ru )
      {
       std::swap( ie1, ie2 );

       if( iclass_prev!=VERB_ru )
        ie1 = ToVerb(ie1);
      }
     else
      {
       if( iclass!=VERB_ru )
        ie1 = ToVerb(ie1);
      } 

     if( ie1!=UNKNOWN )
      {
       // ie1 - глагол
       // ie2 - наречие
     
       bool ignore = false;

       // Исключаем служебные глаголы и наречия
       switch( language )
       { 
        case Russian:
        {
         ignore = stopverbs_ru.find(ie1)!=UNKNOWN || stopadvs_ru.find(ie2)!=UNKNOWN;
         break;
        }

        case English:
        {
         ignore = stopverbs_en.find(ie1)!=UNKNOWN || stopadvs_en.find(ie2)!=UNKNOWN;
         break;
        }
       } 

       // Уберем некоторые наречия
       if( !ignore )
        {
         switch( language )
         { 
          case Russian:
          {
           ignore = stopadvs_ru.find(ie2)!=UNKNOWN;
           break;
          }

          case English:
          {
           ignore = stopadvs_en.find(ie2)!=UNKNOWN;
           break;
          }
         } 
        }

       if( !ignore )
        {
         Store2Gram(ie2,ie1,1);
        }
      }
    }
  }

 return;
}





void CovalentNGramsCollector::Consider3Gram(
                                            int ie_prev,
                                            int iclass_prev,
                                            const UCString &word_prev,
                                            int ie_0,
                                            int iclass_0,
                                            const UCString &word_0,
                                            int ie,
                                            int iclass,
                                            const UCString &word
                                           )
{
 LEM_CHECKIT_Z(ie!=NULL);
 LEM_CHECKIT_Z(ie_0!=NULL);
 LEM_CHECKIT_Z(ie_prev!=NULL);
 
 if( correl == Solarix::NGramsCollectorFlags::Adj_Noun )
  {
   if( iclass==NOUN_ru && iclass_prev==PREPOS_ru )
    {
     // Найдена пара ПРЕДЛОГ-СУЩЕСТВИТЕЛЬНОЕ

     // проверим согласование прилагательного и существительного
//     bool do_add = Solarix::Syntax_Analyzer::Check_Correlation( &*sol_id, word_0, word )==true;

//     if( do_add )
      { 
       Consider2Gram( ie_prev, iclass_prev, word_prev, ie, iclass, word );
      }
    }
  }
 else if( correl == Solarix::NGramsCollectorFlags::Verb_Object )
  {
   if( iclass==NOUN_ru && iclass_prev==VERB_ru )
    {
     // Найдена пара ГЛАГОЛ-УПРАВЛЯЕМЫЙ_ОБЪЕКТ

     // проверим согласование прилагательного и существительного
//     bool do_add = Solarix::Syntax_Analyzer::Check_Correlation( &*sol_id, word_0, word )==true;

//     if( do_add )
      { 
       Consider2Gram( ie_prev, iclass_prev, word_prev, ie, iclass, word );
      }
    }
  }

 return;
}



int CovalentNGramsCollector::IE_2_IClass( int ie ) const
{
 if( ie==UNKNOWN )
  return UNKNOWN;

 const int iclass = sg->GetEntry( ie ).GetClass();
 return iclass;
}



void CovalentNGramsCollector::Merge( const lem::Path &dbfolder, bool echo )
{
/*
 lem::Path dbfile( dbfolder );
 if( dbfile.IsFolder() )
  dbfile.ConcateLeaf( L"ngrams" );

 mout->printf( "Merging [%vfE%us%vn]...\n", dbfile.GetUnicode().c_str() );
 mout->flush(); 

 NGramsDBMS src;
 src.Connect(dbfile);

 BeginDocument(echo);

 FString sql2 = lem::format_str( "SELECT iword1, iword2, w FROM NGRAM2%s", suffix.c_str() );

 #if defined SOL_SQLITE_NGRAMS

 const int n2 = src.SelectInt( lem::format_str("SELECT count_n2 FROM STATS2%s", suffix.c_str() ), 0 );

 if( echo )
  {
   mout->printf( "Adding %vfE%d%vn records to NGRAM2%s ", n2, suffix.c_str() );
   mout->flush();
  }

 const int n100 = n2/100;
 int prev_p=0;
 int i=0; 

 sqlite3_stmt *stmt2=NULL;
 int res = sqlite3_prepare_v2( src.hdb, sql2.c_str(), -1, &stmt2, NULL );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt2 ) == SQLITE_ROW )
    {
     int iw1 = sqlite3_column_int(stmt2,0);
     int iw2 = sqlite3_column_int(stmt2,1);
     const int freq = sqlite3_column_int(stmt2,2);
     Store2Gram( iw1, iw2, freq );

     i++;
     if( echo && !(i%100000) )
      if( n100>0 )
       {
        int p = i/n100;
        if( p>prev_p )
         {
          mout->printf( "%d%% ", p ); mout->flush();
          prev_p=p;
         }  
       }  
    } 

   if( echo ) mout->printf( " %vfEDone%vn\n" );
   sqlite3_finalize(stmt2);
  }

 #elif defined SOL_FIREBIRD_NGRAMS

 src.BeginReadTx();

 const int n2 = src.SelectInt( lem::format_str("SELECT count_n2 FROM STATS2%s", suffix.c_str() ) );

 if( echo )
  {
   mout->printf( "Adding %vfE%d%vn records to %s ", n2, suffix.c_str() );
   mout->flush();
  }

 const int n100 = n2/100;
 int prev_p=0;
 int i=0; 

 isc_stmt_handle stmt = NULL;
 short flag0=0, flag1=1, flag2=2;

 int i1, i2, freq=0;

 XSQLDA *sqlda = (XSQLDA *)malloc(XSQLDA_LENGTH(3));
 sqlda->sqln = 3;
 sqlda->version = 1;

 sqlda->sqlvar[0].sqldata = (char *)&i1;
 sqlda->sqlvar[0].sqltype = SQL_LONG+1;
 sqlda->sqlvar[0].sqllen  = sizeof(i1);
 sqlda->sqlvar[0].sqlind  = &flag0;

 sqlda->sqlvar[1].sqldata = (char *)&i2;
 sqlda->sqlvar[1].sqltype = SQL_LONG+1;
 sqlda->sqlvar[1].sqllen  = sizeof(i2);
 sqlda->sqlvar[1].sqlind  = &flag1;

 sqlda->sqlvar[2].sqldata = (char *)&freq;
 sqlda->sqlvar[2].sqltype = SQL_LONG+1;
 sqlda->sqlvar[2].sqllen  = sizeof(freq);
 sqlda->sqlvar[2].sqlind  = &flag2;

 if( !isc_dsql_allocate_statement( src.status, &src.hdb, &stmt ) )
  {
   if( !isc_dsql_prepare( src.status, &src.htx, &stmt, 0, sql2.c_str(), 1, sqlda ) )
    {
     if( !isc_dsql_execute( src.status, &src.htx, &stmt, 1, NULL) )
      {
       while(true)
        {
         long fetch_stat = isc_dsql_fetch( src.status, &stmt, 1, sqlda );
         if( fetch_stat!=0 )
          {
           if( fetch_stat==100 )
            break;  

           #if LEM_DEBUGGING==1
           isc_print_status(src.status);
           #endif
           break; 
          }

         LEM_CHECKIT_Z( freq>0 );

         Store2Gram( i1, i2, freq );

         i++;
         if( echo && !(i%100000) )
          if( n100>0 )
           {
            int p = i/n100;
            if( p>prev_p )
             {
              mout->printf( "%d%% ", p ); mout->flush();
              prev_p=p;
             }  
           }  
        }

       if( echo ) mout->printf( " %vfEDone%vn\n" );
       isc_dsql_free_statement( src.status, &stmt, DSQL_drop);
      } 
    }
  }

 free(sqlda);
 src.Commit();

 #endif

 db->CommitRetaining();

 EndDocument(echo);

 mout->printf( "%vfEAll data merged.%vn\n" );
*/
 return;
}


void CovalentNGramsCollector::EndAll( bool echo )
{
 PurgeDocCache(echo);
 
 if( print_ngrams && print_file.NotNull() )
  {
   // ...
  }

 RawNGramsCollector::EndAll(echo);
 return;
}

#endif
