#if !defined SOL_WORDENTRY_SET__H
 #define SOL_WORDENTRY_SET__H

 #include <lem/noncopyable.h>
 #include <lem/ptr_container.h>
 #include <lem/process.h>
 #include <lem/RWULock.h>
 #include <set>
 #include <map>

 namespace lem
 {
  namespace Iridium
  {
   class Macro_Parser;
  }
 }


 namespace Solarix
 {
  class Dictionary;
  class LexiconStorage;
  class WordEntrySetEnumerator;
  class WordSetEnumerator;
  struct WordEntrySetItem;
  struct WordSetItem;
  class LS_ResultSet;
  class CP_Array;
  class SynGram;
  class Word_Form;
  
  // Именованный набор словарных статей - используется в правилах при проверке
  // вхождения словоформы в заданное множество.
  //
  // Также существуют именованные наборы произвольных слов.
  class WordEntrySet : lem::NonCopyable
  {
   private:
    LexiconStorage *storage;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs_init;
    lem::Process::RWU_Lock cs;
    lem::Process::RWU_Lock cs_headword, cs_collocation, cs_wordform;
    #endif

    // именованные наборы словарных статей
    std::map< lem::UCString, const WordEntrySetItem* > wordentry_set_map;
    std::map< int, const WordEntrySetItem* > wordentry_id2set;
    lem::Collect< WordEntrySetItem* > wordentry_sets;

    // именованные наботы слов
    std::map< lem::UCString, const WordSetItem* > word_set_map;
    std::map< int, const WordSetItem* > word_id2set;
    lem::Collect< WordSetItem* > word_sets;

    // именованные наборы словосочетаний
    std::map< lem::UCString, int > collocation_set_map;
    volatile bool headwords_loaded;
    std::map< lem::UCString, std::pair<int,int> > headwords_map;
    int FindCollocationSet( const lem::UCString &collocation_name );


    // именованные наборы словоформ
    std::map< lem::UCString, int /*id_set*/ > wordform_set_map;
    std::map< int, const CP_Array* > wordform_set_coords_map;
    lem::MCollect< CP_Array* > wordform_set_coords;
    int FindWordformSet( const lem::UCString &set_name );
    const CP_Array & GetWordformSetCoords( int id_coords );


   public:
    WordEntrySet(void);
    ~WordEntrySet(void);

    void Connect( LexiconStorage *Storage );
    
    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt_WordEntrySet( lem::Iridium::Macro_Parser &txtfile, Dictionary &dict );
    void LoadTxt_WordSet( lem::Iridium::Macro_Parser &txtfile, Dictionary &dict );
    void LoadTxt_CollocationSet( lem::Iridium::Macro_Parser &txtfile, Dictionary &dict );
    void LoadTxt_WordformSet( lem::Iridium::Macro_Parser &txtfile, Dictionary &dict );
    #endif

    bool IsSetName( const lem::UCString &name );

    bool IsWordEntrySetName( const lem::UCString &name );
    bool FindWordEntrySet( const lem::UCString &name, int ekey );
    const WordEntrySetItem& GetWordEntrySet( int id );
    WordEntrySetEnumerator * ListWordEntrySets(void);

    bool IsWordSetName( const lem::UCString &name );
    bool FindWordSet( const lem::UCString &name, const lem::UCString &word );
    const WordSetItem& GetWordSet( int id );
    WordSetEnumerator * ListWordSets(void);

    bool IsCollocationSetName( const lem::UCString &colocation_name );
    bool IsCollocationHeadword( const lem::UCString & headword, int & min_len, int & max_len );
    bool FindCollocation( const lem::UCString &collocation_name, const lem::MCollect<lem::UCString> &words );

    bool IsWordformSetName( const lem::UCString &name );
    bool FindWordformSet( SynGram & sg, const lem::UCString &set_name, const Solarix::Word_Form &wordform );
  };
 }

#endif
