#if defined FAIND_DATAMINE && !defined DM_EMPIR__H
#define DM_EMPIR__H
#pragma once
 
// -----------------------------------------------------------------------------
// File DM_EMPIR.H
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// EMPIR program
// Всевозможная статистическая обработка текстов (морфология, синтаксис и т.д.).
//
// Заголовочный файл программы ЭМПИР - объявления классов.
//
// 17.11.2005 - в результате рефакторинга кода в обновленную программу EMPIR 
//              теперь входят ранее автономные модули SENTAN и CHARS. 
//
// 31.10.2006 - добавлен новый режим работы (команда -tonouns): слова из
//              обрабатываемых файлов приводятся к форме существительных и
//              результат записывается в выходной файл.
//
// 12.05.2007 - все перенесено в DitaMining блок поискового движка.
// -----------------------------------------------------------------------------
//
// CD->04.09.2002
// LC->13.06.2011
// --------------

#include <lem/config.h>

 #include <utility>
 #include <map>

 #include <lem/math/statkeep.h>
 #include <lem/math/histogram.h>
 #include <lem/qarray.h>
 #include <lem/mqueue.h>
 #include <lem/mset.h>
 #include <lem/stl.h>
 #include <lem/date_time.h>
 #include <lem/solarix/se_data_miner.h>
 #include <lem/solarix/search_engine.h>
 
 #include <lem/solarix/la_autom.h>
 #include <lem/solarix/sg_autom.h>
 #include <lem/solarix/lexem.h>
 #include <lem/solarix/dictionary.h>
 #include <lem/solarix/phrasema.h>
 //#include <lem/solarix/text_processor.h>
 //#include <lem/solarix/solarix.h>
 #include <lem/solarix/SG_CoordContext.h>

 #include <lem/solarix/se_data_miner.h>

namespace Solarix
{
namespace Search_Engine
{
namespace Empir
{ 

 const int W_QUEUE_LEN = 4; // Длина очереди истории обработанных слов.
// const int NCHAR     = 33;  // Число символов в алфавите

 const int NSUBLIST  = LEM_CSTRING_LEN; // Сколько делать подсписков слов для длин 1, 2,
                            // 3, ..., прочие.

 const int NCSL=256; // Кол-во подсписков для накопления контекстов

 // ****************************************************************
 // Следующие две функции выполняют вычисление двух составляющих в
 // ключе слова: номер подсписка и номер элемента в списке.
 // ****************************************************************
 inline int e_block( int key ) { return (key>>26) & 0x4fUL; }
 inline int e_hash( int key )  { return (key>>18) & 0xffUL; }
 inline int e_item( int key )  { return key & 0x4ffffUL; }

 // *****************************************************************
 // Собираем ключ из двух компонентов.
 // *****************************************************************
 inline int e_key( int iblock, lem::uint8_t hash_key )
 {  return hash_key | (iblock<<26); }

 inline int hash_to_key( lem::uint8_t hash, int item )
 {  return item | (hash<<18); }


 // ****************************
 // Список пар слово-частота
 // ****************************

 // ********************************************************
 // List of words that have equal hash code and length
 // ********************************************************
 class w_hash_list : public lem::MCollect< std::pair<UCString,int> >
 {
  public:
   w_hash_list(void):MCollect< std::pair<UCString,int> >() { reserve(256); }

   w_hash_list( const w_hash_list &x ) : lem::MCollect< std::pair<UCString,int> >(x) {}

   inline void operator=( const w_hash_list &x )
   {
    lem::MCollect< std::pair<UCString,int> >::operator=(x);
   }
 };


 // ************************************************************
 // Sectainer - the list of lists of words. All words in this
 // sectainer have equal length (but different hash codes).
 // ************************************************************
 class w_list : public Collect< w_hash_list >
 {
  public:
   w_list(void) : Collect< w_hash_list >(256)
   {}

   inline int add_lexem( const lem::UCString &Word )
   {
    int ifound=UNKNOWN;

    w_hash_list &words_n = operator[]( static_cast<unsigned>(Word.GetHash()) );

    // Попытаемся найти слово...
    for( lem::Container::size_type j=0; j<words_n.size(); j++ )
     if( words_n[j].first==Word )
      {
       words_n[ifound=j].second++;
       break;
      }

    // Слова нет в списке - добавляем.
    if( ifound==UNKNOWN )
     {
      ifound = words_n.size();
      words_n.push_back( std::make_pair( Word, 1 ) );
     }

    return hash_to_key( static_cast<unsigned>(Word.GetHash()), ifound );
   }
 };


 // **************************************************************
 // Основной класс накопления статистики по словам.
 // **************************************************************
 class WordProcessor
 {
  private:
   // Накопленные списки пар слово-частота
   // Для ускорения отдельно ведутся списки слов длиной 1 символ,
   // 2 символа и далее, плюс последний список - для слов произвольной
   // длины больше заданной (NSUBLIST-1).
   w_list words[NSUBLIST]; // Длиной 1,2,3,4, и прочие
   lem::int64_t total_wlen; // Сумма длин слов - для вычисления средней длины
   int nlex; // Сколько слов обработано

  public:
   WordProcessor(void);

   int Process( const lem::UCString &w );
   void Report(
               lem::OFormatter &to,
               EmpirTextProcessor &Holder,
               lem::OFormatter *echo,
               const lem::Path &outdir
              );

   inline const std::pair<lem::UCString,int>& get_by_key( int key ) const
   { return words[ e_block(key) ] [ e_hash(key) ] [ e_item(key) ]; }
 };


 #if !defined SOL_NO_AA
 class SentanTextProcessor : public Solarix::Text_Processor
 {
  private:
   typedef enum { Scheme1, Scheme2, LexiconProbing } Scheme; // тип работающего алгоритма
   Scheme scheme;   

   lem::Math::Statis stat_sent; // Статистика длины предложения
   lem::Math::Statis aa_res;    // Статистика длины результата обработки в АА
   lem::Math::Statis aa_succ;
   lem::Histogramma start_vars; // Статистика по начальному числу вариаторов в пачке решений
   int n_success_sent; // Сколько предложений успешно подготовлено
   int n_sent_applied_aa;
   int n_success_aa; // Number of sents completely analysed by aa

   bool print_la_detailed; // Do print sentence preparation results
   bool print_aa_detailed; // Print results of AA performance for each sentence
   bool persentence_echo;  // При обработке каждого предложения выводить пояснения на терминал
   bool persentence_log;   //
   bool write_bin;         // Сохранять ли результаты анализа каждого предложения в бинарном файле

   Solarix::Sentence sent; // Буфер для накопления предложения.

   #if LEM_DEBUGGING==1
   Solarix::FB_StatInfo fb_stat_info; // для накопления статистики по фразоблокам
   #endif

   std::auto_ptr<lem::OUFormatter> ok_out;
   std::auto_ptr<lem::OUFormatter> bad_out;
   std::auto_ptr<lem::OUFormatter> skip_out;
   std::auto_ptr<lem::OUFormatter> log_out;

   std::auto_ptr<lem::BinaryFile> bin_out; // For resulting frasoblocks

   void process_sentence(void);

   virtual void Projected( Solarix::PhrasoBlock *fblo );
   virtual void Analysed( Solarix::PhrasoBlock *fblo );
   virtual void AA_Applied( Solarix::PhrasoBlock *fblo );
   virtual void LoopPassed( int n_pass );

  public:
   SentanTextProcessor( Solarix::Dictionary *Sol_id );

   virtual ~SentanTextProcessor(void);

   void Process( const lem::UCString &l );
   void Report( lem::OFormatter *echo );

   inline void SetScheme1(void) { scheme=Scheme1; do_perform_aa=true; }
   inline void SetScheme2(void) { scheme=Scheme2; do_perform_aa=false; }

   inline void Print_AA_Detailed(void)      { print_aa_detailed=true; }
   inline void Print_LA_Detailed(void)      { print_la_detailed=true; }
   inline void Print_PerSentence_Echo(void) { persentence_echo=true;  }
   inline void Log_PerSentence_Echo(void)   { persentence_log=true;   }

   void Do_Write_Bin(void);

   inline bool Echo_PerSentence(void) const
   { return persentence_echo; }
 };
 #endif


 // **************************************************************
 // Класс обработчика побуквенной статистики.
 // **************************************************************
 class CharProcessor
 {
  private:
   int nchar; // Сколько букв обработано
   int n_lim; // Сколько первых (или последних) букв обработано

   lem::IntCollect ch_freq;  // Частотная таблица для букв (256 элементов)
   lem::IntCollect org_freq; // Частотная таблица для первой буквы слова
   lem::IntCollect end_freq; // Частотная таблица для последней буквы слова

   Solarix::Dictionary* sol_id;

   int unique_chars;
   std::map<wchar_t,int> chars; // список распознаваемых символов

   inline int get_ichar( wchar_t Ch ) const
   {
    std::map<wchar_t,int>::const_iterator wh = chars.find(Ch);
    return wh==chars.end() ? UNKNOWN : wh->second;
   }

  public:
   CharProcessor(void);

   void Add( const lem::UCString &s, int word_freq );

   void Report( lem::OFormatter &to, lem::OFormatter *echo ) const;

   lem::Math::REAL Calc_Val( const lem::UCString &s, int wFreq ) const;

   void SetSol( Solarix::Dictionary* SolId );

   inline int Total_Chars(void) const { return unique_chars; }
 };


 class ws_list : public lem::MCollect< std::pair<UCString,int> >
 {
  public:
   ws_list(void) { reserve(1024); }
 };


 class Syllab_Ctx
 {
  private:
   Syllab_Ctx( const Syllab_Ctx& );
   void operator=( const Syllab_Ctx& );

  public:
   lem::UCString syllab;
   int freq; // Syllab frequency
   lem::Collect< std::pair<SG_CoordContext,int> > gram_contx;

   Syllab_Ctx( const lem::UCString &Syllab, int nOrgFreq )
    : syllab(Syllab), freq(nOrgFreq) {}

   void Add( int iClass, const CP_Array& dims );
 };


 // **************************************************************
 // Класс обработчика послоговой информации.
 // **************************************************************
 class SyllabProcessor
 {
  private:
   int words_count; // Счетчик обработанных слов

   ws_list syllabs_2; // Накопленный список пар слог - частота
                     // для слогов длиной 2 буквы

   ws_list syllabs_3; // Накопленный список пар слог - частота
                     // для слогов длиной 3 буквы

   ws_list endings_2; // Накопленный список пар слог - частота для окончаний
                     // длиной 2 символа

   ws_list endings_3; // Накопленный список пар слог - частота для окончаний
                     // длиной 3 символа


   ws_list real_org_slb;
   ws_list real_mid_slb;
   ws_list real_end_slb;

   lem::Ptr_NC_Collect<Syllab_Ctx> real_ctx;

   Solarix::Dictionary* sol_id;

   void process_syllab_2( const lem::UCString &e, int word_freq );
   void process_syllab_3( const lem::UCString &e, int word_freq );

   void process_ending_2( const lem::UCString &e, int word_freq );
   void process_ending_3( const lem::UCString &e, int word_freq );

   void process_real_mid( const lem::UCString &e, int word_freq );
   void process_real_end( const lem::UCString &e, int word_freq );
   void process_real_org( const lem::UCString &e, int word_freq );

   void Dump_Syllabs( lem::OFormatter &out, const ws_list &slb ) const;

  public:
   SyllabProcessor(void);

   inline void SetSol( Solarix::Dictionary* SolId ) { sol_id=SolId; }

   void Add( const lem::UCString &l, int word_freq );
   void Report( lem::OFormatter &to, const CharProcessor &CH, lem::OFormatter *echo ) const;
   void Post_Process( lem::OFormatter *echo );
 };


 class WordStatProcessor
 {
  private:
   Solarix::Dictionary* sol_id;
   lem::MCollect<lem::Math::REAL> P_char, P_syllab;
   int words_count;

   lem::IntCollect  Nfreq;
   lem::Math::REAL tot_freq;

   lem::Math::Statis S_char, S_syllab;

   lem::Histogramma H_char, H_syllab;

   lem::MCollect<lem::Math::REAL> X_char, W_char, X_syllab, W_syllab;

   void Report_Chars( lem::OFormatter &to, lem::OFormatter *echo ) const;
   void Report_Syllabs( lem::OFormatter &to, lem::OFormatter *echo ) const;

  public:
   WordStatProcessor(void);

   inline void SetSol( Solarix::Dictionary* SolId ) { sol_id=SolId; }

   void Add( const lem::UCString &u, int word_freq );

   void Report( lem::OFormatter &to, lem::OFormatter *echo ) const;
   void Post_Process( lem::OFormatter *echo );
 };

} // namespace Empir
} // namespace Search_Engine
} // namespace Solarix

#endif
