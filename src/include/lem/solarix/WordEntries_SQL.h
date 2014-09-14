#if !defined WordEntries_SQL__H
 #define WordEntries_SQL__H

 #include <map>
 #include <lem/process.h>
 #include <lem/solarix/BaseRef.h>
 #include <lem/solarix/coord_pair.h>
 #include <lem/RWULock.h>

 #if defined SOL_LOADTXT
 #include <lem/solarix/LexemDictionary.h>
 #endif

 #include <lem/solarix/WordEntries.h>

 namespace Solarix
 {
  class SynGram;
  struct Dictionary_Config;

  class WordEntries_SQL : public WordEntries
  {
   private:
    #if defined LEM_THREADS
    lem::Process::CriticalSection cs0;
    #endif

    #if defined LEM_THREADS
    lem::Process::RWU_Lock cs_uentries;
    #endif
    lem::Process::InterlockedInt uentries_loaded;
    std::map< int /*index*/, int /*ekey*/ > predefined;
    std::map< int /*id_class*/, int /*ekey*/ > quantors;

    #if defined LEM_THREADS
    lem::Process::RWU_Lock cs_lexemes;
    #endif
    lem::PtrCollect<Solarix::Lexem> lexemes;
    std::map< Solarix::Lexem, int > lexemes_map;

    BaseRef<CP_Array> coord_ref;


    #if defined LEM_THREADS
    lem::Process::RWU_Lock cs_entry_lookup;
    #endif
    std::map< std::pair<lem::UCString/*ename*/,int>, int /*ekey*/ > entry_class_lookup;

   protected:
    SynGram &sg;

    lem::IntCollect uentries;
    #if defined SOL_LOADTXT
    LexemDictionary ml_ref;
    #endif

    #if defined LEM_THREADS
    lem::Process::RWU_Lock cs_multilexem;
    #endif

    int max_multilexem_len;
    std::map<lem::UCString,Solarix::MultiLexemInfo> multilexem_head;
    std::set<lem::UCString> not_multilexem_head;
    std::set<Solarix::Lexem> multilexems;

    #if defined LEM_THREADS
    lem::Process::RWU_Lock cs_entries;
    #endif

    std::map<int/*ekey*/,SG_Entry*> entries_map;
    lem::PtrCollect<SG_Entry> entries;

    lem::PtrCollect<Solarix::Lexem> enames;
    std::map< Solarix::Lexem, int > enames_map;

    const Solarix::Lexem* RegisterLexemeInCache( const Solarix::Lexem &lex );
    const CP_Array* RegisterCoordPairsInCache( const CP_Array & pairs );


    virtual int GetMaxMultilexemLen_Impl(void)=0;
    virtual bool IsMultilexemHead_Impl( const lem::UCString &word, MultiLexemInfo &info )=0;
    virtual bool IsMultilexemForm_Impl( const Solarix::Lexem &lex )=0;
    virtual int FindEntry_Impl( const lem::UCString &word_name, int id_class )=0;
    virtual SG_Entry* LoadEntryFromDb_Impl( int ekey )=0;
    virtual int RegisterLexemeInDatabase( const lem::UCString & lex )=0;
    virtual int RegisterCoordPairsInDatabase( const lem::UFString &int_pairs, const lem::UFString &str_pairs )=0;
    virtual void GetUEntries_Impl(void)=0;
    virtual int GetPredefinedEntryKey_Impl( int index )=0;
    virtual int FindQuantorEntry_Impl( int id_class )=0;

   public:
    WordEntries_SQL( SynGram &_sg, const Dictionary_Config &cfg );
    virtual ~WordEntries_SQL(void);

    virtual void CreateDefaultEntries(void);

    virtual bool PreferPrefixSearch(void);

    virtual int GetMaxMultilexemLen(void);

    virtual SG_Entry& LoadEntryFromDb( int ekey );

    virtual bool IsMultilexemHead( const lem::UCString &word, MultiLexemInfo &info );
    virtual bool IsMultilexemForm( const Solarix::Lexem &lex );

    virtual int FindEntry( const lem::UCString &word_name, int id_class );

    virtual const SG_Entry& GetEntry( int ekey );
    virtual SG_Entry& GetEntryForChange( int ekey );

    virtual int CreateEntry( const lem::UCString &ename, int id_class );
    virtual int GetPredefinedEntryKey( int index );
    virtual int FindQuantorEntry( int id_class );

    virtual int AddEntry( SG_Entry *new_entry );
    virtual const Lexem* AddLexeme( const Solarix::Lexem &lex );
    virtual const CP_Array* AddCoordPairs( const CP_Array &x );
    virtual const Lexem* ReattachLexeme( const Lexem *ptr );
    virtual const CP_Array* ReattachCoordPairs( const CP_Array *ptr );

    virtual void PrepareForMerging(void);
    virtual void CommitCompilation( lem::OFormatter &err );

    virtual CharNode* GetPrefixTreeForAllLanguages(void);
    virtual CharNode* GetPrefixTree( const std::set<int>& allowed_langs );

    virtual void ReplaceEntry( int ekey, SG_Entry *dummy );
    virtual void PostRead( lem::Iridium::Macro_Parser &txtfile, const Binarization_Options &options );

    virtual void LoadBin( lem::Stream &bin );
    virtual void SaveBin( lem::Stream &bin ) const;

    virtual void DetailedReport( lem::OFormatter &txtfile );

    virtual LD_Seeker* Get_Seeker(void);

    #if defined SOL_LOADBIN
    virtual LD_Seeker* Load_Seeker( lem::Stream &bin );
    #endif

    virtual const lem::IntCollect& GetUEntries(void);

    const Solarix::Lexem* RegisterLexem( const Solarix::Lexem &lex );

    virtual int GetUnknownEntryKey(void);
  };

 }

#endif
