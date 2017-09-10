// -----------------------------------------------------------------------------
// File WORD.CPP
//
// (c) Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project
// EMPIR program
//
// Часть программы EMPIR - обработка слов.
//
// 18.05.2006 - добавлено формирование бинарного файла с частотами словарных
//              статей для использования алгоритмом автореферирования поискового
//              движка (при автореферировании).
// 07.12.2008 - переделан алгоритм последней фазы сбора статистики - проекции
//              накопленных слов на словарь. Раньше происходило накопление
//              ненайденных слов в списке в памяти, что для большой обработанной
//              выборки давало очень большую нагрузку на память, иногда
//              достигая неприемлемых значений >1 Гб. 
// 20.08.2009 - переделка на int64 для полей, хранящих частоты, так как для
//              больших корпусов (>20 Гб) кол-во обработанных слов и частоты
//              самых популярных слов превышают 2 млрд.
// -----------------------------------------------------------------------------
//
// CD->07.01.2003
// LC->16.02.2012
// --------------

#include <utility>
#include <functional>
#include <algorithm>

#include <lem/solarix/dictionary.h>
#include <lem/solarix/version.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/ClassList.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/WordEntryEnumerator.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/PartOfSpeechEnumerator.h>

#include "empir.h"

using namespace std;



WordProcessor::WordProcessor( Solarix::LexicalAutomat *LA, bool tokenized_is_used, int language )
 : la(LA)
{
 id_language=language;
 nlex=0;
 total_wlen=0;
 merge_words = !tokenized_is_used;
 
 if( !tokenized_is_used )
  word_merger = new MultiwordMerger( LA );

 return;
}

void WordProcessor::EndDocument(void)
{
 PurgeMerger();
 return;
}


void WordProcessor::PurgeMerger(void)
{
 if( merge_words )
  {
   word_merger->ForceReady();

   while( word_merger->IsReady() )
    {
     ProcessInternal( word_merger->Pop() );
    }
  }

 return;
}




// *****************************************************************
// Регистрация слова Word, поступившего на обработку. Возвращается
// уникальный ключ в суперсписке.
// *****************************************************************
void WordProcessor::Process( const UCString &Word )
{
//mout->printf( "%us ", Word.c_str() );

 if(
    stopwords.find(Word)!=stopwords.end() ||
    //lem::is_udelim(Word) ||
    Word==L'.' || Word==L'!' || Word==L'?' ||
    lem::is_udigit(Word.front()) ||
    Word.front()==L'_'
   )
  {
   if( merge_words )
    PurgeMerger();

   return;
  }

 if( merge_words )
  {
   word_merger->Push(Word);
  
   while( word_merger->IsReady() )
    {
     ProcessInternal( word_merger->Pop() );
    }
  }
 else
  {
   ProcessInternal( Word );
  } 
 
 return;
}


void WordProcessor::ProcessInternal( const UCString &Word )
{
 if( Word.empty() )
  return;

 // В каком подсписке
 const int iblock = Word.length()<NSUBLIST ? Word.length()-1 : NSUBLIST-1;

 // Этот подсписок  - через ссылку для ускорения доступа
 w_list &words_n = words[iblock];

 total_wlen += Word.length();
 nlex ++; // Счетчик обработанных слов.

 UCString w(Word);
 //lem::CodeConverter::Strip_Diaktrices(w.ptr());
 //w.calc_hash();

 w.subst_all( 0x0401, 0x0415 ); // Ё->Е

 words_n.add_lexem(w);

 return;
}


int WordProcessor::GetWordFrequency( const lem::UCString &word ) const
{
 const int iblock = word.length()<NSUBLIST ? word.length()-1 : NSUBLIST-1;
 const w_list &words_n = words[iblock];
 return words_n.GetWordFrequency(word);
}




static bool sort_desc_pairs_predicate( const pair<int,lem::int64_t> &a, const pair<int,lem::int64_t> &b )
{
 return a.second>b.second;
}


static bool sort_unfound2( const pair<lem::UCString,lem::int64_t> &a, const pair<lem::UCString,lem::int64_t> &b )
{
 return a.second>b.second || (a.second==b.second && a.first<b.first);
}



// *************************************************************
// Распечатка статистики по накопленной информации в поток rep.
// *************************************************************
void WordProcessor::Report( OFormatter &rep, EmpirTextProcessor &Holder )
{
/*
// --- DEBUG
 lem::Ptr<Solarix::WordEntryEnumerator> wenum0( Holder.sol_id->GetSynGram().GetEntries().ListEntries() );

 mout->printf( "DEBUG-0\n" );
 mout->flush();

 int ientry0=0;
 while( wenum0->Fetch() )
  {
mout->printf( " %d", ientry0 );
mout->flush();
   const int ekey = wenum0->GetId();
mout->printf( " (key=%d name=%us)", ekey, Holder.sol_id->GetSynGram().GetEntry(ekey).GetName().c_str() );
mout->flush();
   ientry0++;
  }

 mout->printf( "DEBUG-0 END\n" );
 mout->flush();
wenum0.Delete();
 // --- DEBUG
*/


 // Here is the important sorting trick. As you can see the number of
 // collected words may be very big (more than 1 million). Sorting such list
 // takes so much time that i had to implement the new approach.

 w_hash_list sublist[10];
 IntCollect sort_indeces[10];

 for( int i=0; i<10; i++ )
  sort_indeces[i].reserve(8192);

 mout->printf( "Assembling the lists of words->" );
 mout->flush();
 lem::int64_t nword = 0;

 // ****************************************************************
 // Собираем общий список зарегистрированных слов из подсписков.
 // ****************************************************************

 for( int iwc=0; iwc<NSUBLIST; iwc++ )
  {
   for( lem::Container::size_type iw=0; iw<words[iwc].size(); iw++ )
     for( lem::Container::size_type jw=0; jw<words[iwc][iw].size(); jw++ )
      {
       const lem::int64_t n = words[iwc][iw][jw].second;

       if( !erase_freq1 || n>1 )
        {
         const int iList = int( ( n>0 && n<9 ) ? (n-1) : 9 );

         sort_indeces[ iList ].push_back( CastSizeToInt(sublist[iList].size()) );
         sublist[ iList ].push_back( words[iwc][iw][jw] );
         nword++;
        }
      }

   mout->dot();
  }

 mout->printf( "%qd words %vfAOK%vn\n", nword );

 // Now sort each sublist so most frequent words will be placed first.
 mout->printf( "Sort each words list..." );
 mout->flush();

 w_hash_list words_n; // The whole list of words.
 IntCollect sort_index;
 sort_index.reserve(16384);

 for( int ilist=9; ilist>=0; ilist-- )
  if( ilist<9 )
   {
    IntCollect &indeces = sort_indeces[ilist];

    transform(
              indeces.begin(),
              indeces.end(),
              indeces.begin(),
              bind2nd( plus<lem::int64_t>(), words_n.size() )
             );

    words_n.AddList( sublist[ilist] );
    sort_index.AddList( indeces );
   }
  else
   {
    sort_desc_pairs( sublist[ilist], sort_indeces[ilist] );

    IntCollect &indeces = sort_indeces[ilist];

    transform(
              indeces.begin(),
              indeces.end(),
              indeces.begin(),
              bind2nd( plus<lem::int64_t>(), words_n.size() )
             );

    words_n.AddList( sublist[ilist] );
    sort_index.AddList( indeces );
   }

 const int nw = CastSizeToInt(words_n.size()); // Всего слов
 mout->printf( "%vfE%d%vn words %vfAOK%vn\n", nw );

 mout->printf( "Search the words in dictionary..." );
 mout->flush();

 // Сколько грамматических классов определено в словаре
 const int nclass = CastSizeToInt(Holder.sol_id->GetSynGram().classes().Count());
 std::map<int,int> IndexToIclass, IclassToIndex;
 int ic=0;
 lem::Ptr<PartOfSpeechEnumerator> cenum( (PartOfSpeechEnumerator*) Holder.sol_id->GetSynGram().classes().Enumerate() );
 while( cenum->Fetch() )
  {
   const int id_class = cenum->GetId();
   IndexToIclass.insert( std::make_pair(ic, id_class) );
   IclassToIndex.insert( std::make_pair(id_class, ic) );
   ic++;
  }

 mout->printf( "1" );
 mout->flush();

 // Вектор для накопления частоты употребления классов.
 lem::MCollect<lem::int64_t> class_freq(nclass);
 class_freq.Nullify(); // предварительно обнуляем - по умолчанию
                       // в контейнере мусор

 // Вектор для накопления частот словарных статей
 const int nentry = Holder.sol_id->GetSynGram().GetnEntry();
 lem::MCollect<lem::int64_t> entry_freq(nentry);
 entry_freq.Nullify();

 std::map<int,int> EntryKeyToIndex;
 lem::MCollect<int> IndexToEkey;
 IndexToEkey.resize(nentry);
 IndexToEkey.Nullify();

 mout->printf( "2" );
 mout->flush();

 lem::Ptr<Solarix::WordEntryEnumerator> wenum( Holder.sol_id->GetSynGram().GetEntries().ListEntries() );

 mout->printf( "3" );
 mout->flush();

 int ientry=0;
 while( wenum->Fetch() )
  {
   const int ekey = wenum->GetId();
   EntryKeyToIndex.insert( std::make_pair(ekey,ientry) );
   IndexToEkey[ientry] = ekey;
   ientry++;
  }

 mout->printf( "4" );
 mout->flush();

 // Файл со статистикой по всем встретившимся словам: слово, частота, найдено
 // ли в Словаре.
 OUFormatter words_xml( GetOutPath(L"words.xml") );

 // Запишем схему - для того, чтобы задать правильные типы полей.
 OFormatter words_xsd( GetOutPath(L"words.xsd") );

 words_xsd.printf(
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<xsd:schema xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:od=\"urn:schemas-microsoft-com:officedata\">\n"
  "<xsd:element name=\"dataroot\">\n"
  "<xsd:complexType>\n"
  "<xsd:sequence>\n"
  "<xsd:element ref=\"word\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n"
  "</xsd:sequence>\n"
  "<xsd:attribute name=\"generated\" type=\"xsd:dateTime\"/>\n"
  "</xsd:complexType>\n"
  "</xsd:element>\n"
  "<xsd:element name=\"word\">\n"
  "<xsd:annotation>\n"
  "<xsd:appinfo/>\n"
  "</xsd:annotation>\n"
  "<xsd:complexType>\n"
  "<xsd:sequence>\n"
  "<xsd:element name=\"content\" minOccurs=\"0\" od:jetType=\"text\" od:sqlSType=\"nvarchar\">\n"
  "<xsd:simpleType>\n"
  "<xsd:restriction base=\"xsd:string\">\n"
  "<xsd:maxLength value=\"255\"/>\n"
  "</xsd:restriction>\n"
  "</xsd:simpleType>\n"
  "</xsd:element>\n"
  "<xsd:element name=\"freq\" minOccurs=\"0\" od:jetType=\"longinteger\" od:sqlSType=\"int\" type=\"xsd:int\"/>\n"
  "<xsd:element name=\"found\" minOccurs=\"0\" od:jetType=\"longinteger\" od:sqlSType=\"int\" type=\"xsd:int\"/>\n"
  "</xsd:sequence>\n"
  "</xsd:complexType>\n"
  "</xsd:element>\n"
  "</xsd:schema>\n"
 );

 words_xsd.GetStream()->close();

 OUFormatter uf_txt( GetOutPath(L"unfound.utf8") );

 OUFormatter misspelling_txt( GetOutPath(L"misspelling_corrections.utf8") );

 OUFormatter sg_calibr( GetOutPath(L"sg_calibrator.sol") );
 sg_calibr.printf(
                  "// This file was generated by EMPIR program %us\n"
                  "automat sg\n"
                  "{\n"
                  , to_ustr( boost::posix_time::second_clock::local_time() ).c_str()
                 );

 words_xml.printf(
                  "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                  "<dataroot xmlns:od=\"urn:schemas-microsoft-com:officedata\""
                  " xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\""
                  " xsi:noNamespaceSchemaLocation=\"words.xsd\" "
                  " generated=\"2004-11-04T12:57:19\">\n"
                 );

 lem::int64_t n_found=0, n_unfound=0;
 double unfound_sum=0; // Интеграл частоты ненайденных слов

 BinaryWriter unfound_words( GetOutPath(L"unfound.bin") ); // Для сбора списка ненайденных слов
 int count_unfound_words=0;
 unfound_words.write_int(0);

 LexicalAutomat &la = Holder.sol_id->GetLexAuto();

 // Гистограмма длины слов
 Histogramma word_len_histo( 1, UCString::max_len, UCString::max_len-1 );
 MCollect<Word_Coord> res; res.resize(1024); 
 MCollect<Solarix::ProjScore> val_list; val_list.resize(1024);
 PtrCollect<LA_ProjectInfo> inf_list;
 MCollect<lem::UCString> corrected_word;

 const LD_Seeker &seeker = *Holder.sol_id->seeker;

 lem::MCollect< std::pair<lem::UCString,lem::int64_t> > unfound_words2;


 for( lem::Container::size_type j=0; j<words_n.size(); j++ )
  {
   const UCString &Word = words_n[ sort_index[j] ].first;

   word_len_histo.Add( Word.length(), words_n[ sort_index[j] ].second );

   int n_proj=0;

   // Отображение прогресса в проецировании слов.
   if( !(j%4096) )
    mout->dot();

   if( seeker.Find(Word,false)!=UNKNOWN )
    {
     res.clear();
     val_list.clear();
     inf_list.clear();
     la.ProjectWord( Word, res, val_list, inf_list, LexicalAutomat::Wordforms, 0, id_language, NULL );
     n_proj = CastSizeToInt(res.size());
    }

   words_xml.printf(
                    "<word>\n"
                    "<content>%us</content>\n<freq>%d</freq>\n<found>%d</found>\n"
                    "</word>\n"
                    , lem::encode_chars_to_xml( UFString(Word.c_str()) ).c_str()
                    , words_n[sort_index[j]].second
                    , n_proj
                   );

   if( Holder.run_chars )
    {
     Holder.char_stat.Add( Word, words_n[sort_index[j]].second );
     #if defined EMPIR_SYLLAB
     Holder.syllab_stat.Add( Word, words_n[sort_index[j]].second );
     #endif
     Holder.word_stat.Add( Word, words_n[sort_index[j]].second );
    }

   double f = double(words_n[ sort_index[j] ].second) / double(words_n[ sort_index[0] ].second);
   if( /*f >= 0.000001 &&*/ n_proj )
    {
     if( Word==L"\"" || Word==L"\\" )
      sg_calibr.printf(
                       " calibrate \"\\%us\" = %qd\n"
                       , Word.c_str()
                       , words_n[ sort_index[j] ].second
                      );
     else
      sg_calibr.printf(
                       " calibrate \"%us\" = %qd\n"
                       , Word.c_str()
                       , words_n[ sort_index[j] ].second
                      );
    }

   if( !n_proj )
    {
     const double perc = 100.0*words_n[ sort_index[j] ].second/nlex;

     corrected_word.clear();
     if( la.FindMisspeltWord( Word, corrected_word, id_language ) )
      {
       for( lem::Container::size_type p=0; p<corrected_word.size(); ++p )
        {
         const lem::UCString & CorrectedWord = corrected_word[p];
         if( seeker.Find(CorrectedWord,false)!=UNKNOWN )
          {
           res.clear();
           val_list.clear();
           inf_list.clear();
           la.ProjectWord( CorrectedWord, res, val_list, inf_list, LexicalAutomat::Wordforms, 0, id_language, NULL );
           n_proj = CastSizeToInt(res.size()); 
           if( n_proj>0 )
            break;
          }
        }
      }

     if( n_proj>0 )
      {
       // В отдельном листинге выведем результаты коррекции.
       misspelling_txt.printf(
                              "[%W30us] %W6qd (%6.3rf %%)\n"
                              , words_n[sort_index[j]].first.c_str()
                              , words_n[sort_index[j]].second
                              , perc
                             );

       n_found += words_n[sort_index[j]].second;
      }
     else
      {
       unfound_sum += perc; // Интеграл частоты

       const lem::UCString & unfound_word = words_n[sort_index[j]].first;
       const lem::int64_t unfound_freq = words_n[sort_index[j]].second;

       unfound_words2.push_back( std::make_pair(unfound_word,unfound_freq) );
    
       uf_txt.printf(
                     "[%us]\n"
                    , unfound_word.c_str()
                   );
    
       n_unfound += words_n[sort_index[j]].second;
       count_unfound_words++;
       unfound_words.write( &words_n[sort_index[j]], sizeof(words_n[sort_index[j]]) );
      }
    }
   else
    {
     n_found += words_n[sort_index[j]].second;

     for( int iv=0; iv<n_proj; iv++ )
      {
       const int ekey = res[iv].GetEntry();
       class_freq[ IclassToIndex.find(Holder.sol_id->GetSynGram().GetEntry(ekey).GetClass())->second ]++;
       entry_freq[ EntryKeyToIndex.find(ekey)->second ]+=words_n[sort_index[j]].second;
      }
    }
  } // for( ...

 sg_calibr.printf( "}\n" );

 sg_calibr.GetStream()->close();

 words_xml.printf( "</dataroot>\n" );

 words_xml.GetStream()->close();

 // ---------------------------------------------------------------------------------
 OUFormatter uf_f( GetOutPath(L"unfound.res") );
 std::sort( unfound_words2.begin(), unfound_words2.end(), sort_unfound2 );

 for( lem::Container::size_type i=0; i<unfound_words2.size(); ++i )
 {
  uf_f.printf( "[%W30us] %W6qd\n", unfound_words2[i].first.c_str(), unfound_words2[i].second );
 }

 uf_f.close();
 // ---------------------------------------------------------------------------------



 mout->printf( "%vfAOK%vn\n" ); // завершили поиск слов в словаре

 rep.printf(
            "         --- Words Statistics ---\n"
            "Total # words processed       = %qd\n"
            "Number of accumulated words   = %d\n"
            "Average word length           = %4.1f\n\n"
            , nlex
            , nw
            , double(total_wlen)/double(nlex)
           );

 rep.printf(
            "\n\n%80h-\n"
            "Words length distribution (stored also in 'word_lengths.csv'):\n"
           );

 lem::report( word_len_histo, rep );
 lem::picture( word_len_histo, rep, 64, CString::max_len-1 );
 rep.printf( "\n%80h-\n" );

 OFormatter f1( GetOutPath(L"word_lengths.csv") );
 word_len_histo.Normalize();
 lem::save_data( word_len_histo, f1 );
 f1.GetStream()->close();


 // Процент обнаруженных слов среди всех прочитанных.
 nlex = n_unfound+n_found;
 const double perc_found = 100.0 * n_found / nlex;
 rep.printf(
            "No. of found words   = %qd (%6.3f %%)\n"
            "No. of unfound words = %qd\n"
            , n_found, perc_found, n_unfound
           );

 // Список частот грамматических классов.
 rep.printf(
            "Grammatic classes frequencies (total %d classes, also stored in "
            "'classes_freq.dat'):\n", nclass
           );

 OFormatter f3( GetOutPath(L"classes_freq.csv") );
 const lem::int64_t sum_class = sum_up( class_freq );

 MCollect< pair<int,lem::int64_t> > p_class;
 p_class.reserve(nentry);
 for( int ii=0; ii<nclass; ii++ )
  p_class.push_back( std::make_pair( IndexToIclass.find(ii)->second, class_freq[ii] ) );

 //sort_desc_pairs( p_class );
 std::sort( p_class.begin(), p_class.end(), sort_desc_pairs_predicate );

 for( int iclass=0; iclass<nclass; iclass++ )
  {
   const UCString &cn = Holder.sol_id->GetSynGram().classes()[ p_class[iclass].first ].GetName();
   rep.printf(
              "%W32us - %W10qd (%6.3f %%)\n"
              , cn.c_str()
              , p_class[iclass].second
              , (100.0*p_class[iclass].second)/sum_class
             );

   f3.printf( "\"%us\";%qd\n", cn.c_str(), p_class[iclass].second );
  }
 f3.GetStream()->close();

 // Отсортируем список частот статей
 mout->printf( "Sort the list of entry frequencies..." ); mout->flush();

 // Бывает, что (после обработки неповторяющегшося списка) все накопленные
 // слова имеют одинаковую частоту. Тогда сортировать не имеет смысла. Так
 // накладные расходы на просмотр списка частот практически отсутствуют (все
 // равно цикл нужен для других целей), то применим оптимизацию.
                                                                
 bool do_sort=false;
 lem::int64_t freq0 = entry_freq.front();

 const lem::int64_t sum_entry = sum_up( entry_freq ); // сумма частот
 SynGram &sg = Holder.sol_id->GetSynGram();

 MCollect< pair<int,lem::int64_t> > p_entry;
 p_entry.reserve(nentry);
 for( int ii=0; ii<nentry; ii++ )
  {
   p_entry.push_back( make_pair( IndexToEkey[ii], entry_freq[ii] ) );
   if( entry_freq[ii] != freq0 )
    {
     do_sort = true;
    }
  }

 if( do_sort )
  //sort_desc_pairs( p_entry );
  std::sort( p_entry.begin(), p_entry.end(), sort_desc_pairs_predicate );

 mout->printf( "%vfAOK%vn\n" );

 {
  rep.printf( "\n\nFrequencies of top 1024 entries (stored also in 'entry_freqs.csv'):\n" );

  OUFormatter f2( GetOutPath(L"entry_freqs.csv") );

  // Бинарный файл с частотами словарных статей
  BinaryWriter bin3( GetOutPath(L"entry_freqs.bin") );
  bin3.write_int(0); // сюда потом запишем сколько записей в векторе
  int nrec=0;

  for( int i3=0; i3<nentry; i3++ )
   {
    const SG_Entry &Entry = sg.GetEntry( p_entry[i3].first );
    const UCString& en = Entry.GetName();

    if( !p_entry[i3].second )
     // закончились хоть раз использованные словарные статьи.
     break;

    if( p_entry[i3].second>1 )
     {
      const int ekey = p_entry[i3].first;
      lem::int64_t freq = p_entry[i3].second;

      bin3.write_int(ekey);
      bin3.write(&freq,sizeof(freq));
      nrec++;
     }

    if( i3<1024 )
     // Чтобы общий файл журнала не стал слишком большим, в него пишем 
     // только часть статей. 
     rep.printf(
                "#%W5d %W32us - %W10qd (%6.3f%%)\n"
                , i3
                , en.c_str()
                , p_entry[i3].second
                , (100.0*p_entry[i3].second)/sum_entry
               );
     
     
    f2.printf( "%d;%us;%qd;", i3, en.c_str(), p_entry[i3].second );

    // Выясним, есть ли для статьи переводы на другие языки.
    int id_class = sg.GetEntry( p_entry[i3].first ).GetClass();
    if( !is_quantor(id_class) )
     {
      int id_lang = static_cast<const SG_Class&>(sg.classes()[id_class]).GetLanguage();

      if( !is_quantor(id_lang) )
       {
        const SG_Language &lang = sg.languages()[id_lang];
    
        for( lem::Container::size_type j=0; j<lang.links().size(); j++ )
         {
          const Tree_Link &Link = lang.links()[j].first;
        
          // У словарной статьи 'Entry' есть хоть одна такая связка (и входящие и исходящие)?
          if( sg.Get_Net().Is_Any_Linked( Entry.GetKey(), Link ) )
           {
            // да.
            f2.printf( ' ' );
            Link.SaveTxt( f2, sg );
           }
         }
       }
     }

    f2.eol();
   }

  lem::Stream::pos_type end = bin3.tellp();
  bin3.seekp(0);
  bin3.write_int(nrec);
  bin3.seekp(end); 
 }


 // Сохраним накопленные слова в бинарных файлах, так что другие программы
 // смогут загрузить эти списки и выполнять последующий анализ. Учитывая,
 // что накопление слов - весьма трудоемкая операция, разбиение анализа на
 // стадии накопления слов и последующего анализа пар СЛОВА-ЧАСТОТА помогает
 // сберечь нервы. Списки сохраняются НЕОТСОРТИРОВАННЫМИ.
 mout->printf( "Save the words list..." );
 mout->flush();

 BinaryWriter bin( GetOutPath(L"words.bin") );
 words_n.SaveBin(bin);

 // Вообще надо сохранить и sort_index ...
 bin.close();

 lem::Stream::pos_type unfound_end = unfound_words.tellp();
 unfound_words.seekp(0);
 unfound_words.write_int(count_unfound_words);
 unfound_words.seekp(unfound_end); 
 unfound_words.close();

 rep.eol();
 mout->printf( "%vfAOK%vn\n" );


 // **********************************
 // Build the list of LIVE WORDFORMS.
 // **********************************
/*
 mout->printf( "Search for dead wordforms..." ); mout->flush();
 OFormatter alive( lem::Path("sg_alive.sol") );

 // Count the wordforms in dictionary.
 int n_form=0;
 LEM_LOOP_A( i, sg.entries() )
  n_form += sg.entries().get(i)->forms().size();

 alive.printf(
              "// This file is created by EMPIR %s\n"
              "// It contains the list of ALIVE WORDSFORMS - which are used\n"
              "// at least one time when processing a set of text files.\n"
              "// Total number of wordforms = %d\n"
              , sol_get_version().c_str()
              , n_form
             );

 const Ptr_NC_Collect<MultyLexem>& word_ref = sg.Get_ML_ref().get_list();
 IntCollect used_flag( word_ref.size() );

 LEM_LOOP_A( i, word_ref )
  {
   used_flag[i] = 0;
   const MultyLexem& w = *word_ref[i];

   if( w.size()!=1 )
    {
     used_flag[i] = 1;
     continue;
    }

   LEM_LOOP_A( j, lexem_list )
    if( word_ref[i]->front() == lexem_list[j] )
     {
      used_flag[i] = 1;
      break;
     }
  }

 mout->printf( '.' ); mout->flush();

 int dead_count=0;
 LEM_LOOP_A( i, used_flag )
  if( !used_flag[i] )
   dead_count++;

 alive.printf(
              "// Number of dead forms = %d (%5.2f %%)\n\n"
              "automat sg\n"
              "{\n"
              " array alive={\n"
              , dead_count
              , double(dead_count*100)/n_form
             );

 int alive_count=0;
 const UCString APOSTROF( "\"" );
 LEM_LOOP_A( i, used_flag )
  if( used_flag[i] )
   {
    if( alive_count )
     alive.printf( ", " );

    if( !(alive_count%4) )
     alive.eol();

    alive_count++;
    if( word_ref[i]->front().string()==APOSTROF )
     alive.printf( " \"\\%W17us\"", word_ref[i]->front().string().c_str() );
    else
     alive.printf( " %W20us", word_ref[i]->front().string().c_str() );
   }

 alive.printf(
              " } //%d lexems \n"
              "\n}"
              "\n// %25h- End Of File [SG_ALIVE.SOL] %25h-\n"
              , alive_count
             );

 mout->printf( "%vfAOK%vn\n" );
*/
 // **************** End of dead wordforms list ***********************

 // Выгрузку результатов завершили.

 return;
}


lem::Path WordProcessor::GetOutPath( const wchar_t *filename ) const
{
 lem::Path p(outdir);
 p.ConcateLeaf(filename);
 return p;
}
