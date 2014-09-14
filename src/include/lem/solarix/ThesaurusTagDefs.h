#if !defined ThesaurusTagDefs__H
 #define ThesaurusTagDefs__H

 #include <lem/process.h>
 #include <lem/noncopyable.h>
 #include <lem/ucstring.h>
 #include <lem/containers.h>
 #include <lem/ptr_container.h>

 namespace lem
 {
  class OFormatter;
  struct Sol_IO;
  namespace Iridium
  {
   class Macro_Parser;
  }
 }

 namespace Solarix
 {
  class SG_Net;
  class SynGram;
  class SQL_Production;
  class ThesaurusStorage;
  struct Binarization_Options;

  // Описание одного тега - его имя и список возможных значений.
  class ThesaurusTag : lem::NonCopyable
  {
   private:
    int id;
    lem::UCString name; // имя тэга
    lem::MCollect<int> ivalues; // id значений
    lem::MCollect<lem::UCString> values; // допустимые значения

   public:
    ThesaurusTag(void);
    ThesaurusTag( int _id, ThesaurusStorage *db );

    void Store( ThesaurusStorage *db );

    const lem::UCString & GetName(void) const { return name; }
    int GetId(void) const { return id; }

    int operator[]( const lem::UCString &value_name ) const;
    const lem::UCString & operator[]( int ivalue ) const;

    int CountValues(void) const { return CastSizeToInt(values.size()); }

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt(
                 lem::Iridium::Macro_Parser & txtfile,
                 const lem::Sol_IO &io,
                 const Binarization_Options & options
                );
    #endif

    #if defined SOL_REPORT
    void Save_SQL( lem::OFormatter &out, const SQL_Production &sql_version ) const;
    #endif
  };

  class ThesaurusTagDefs;
  class LS_ResultSet; 
  class ThesaurusTagDefsEnumerator 
  {
   private:
    ThesaurusTagDefs *defs;
    LS_ResultSet *rs;

   public:
    ThesaurusTagDefsEnumerator( ThesaurusTagDefs *x );
    ~ThesaurusTagDefsEnumerator(void);
    bool Fetch(void);
    int GetId(void) const;
    lem::UCString GetName(void) const;
  };

  class ThesaurusTagDefs
  {
   private:
    friend class ThesaurusTagDefsEnumerator;
    ThesaurusStorage *db;
    lem::PtrCollect<ThesaurusTag> ptrs;
    std::map< int /*id*/, const ThesaurusTag* > id2tag;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs;
    #endif
    
   public:
    ThesaurusTagDefs(void);
    ~ThesaurusTagDefs(void);

    void Connect( ThesaurusStorage *_db );

    const ThesaurusTag& operator[]( int id_tag );
    int Find( const lem::UCString & tag_name );
    
    ThesaurusTagDefsEnumerator* Enumerate(void);

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt(
                 lem::Iridium::Macro_Parser & txtfile,
                 const lem::Sol_IO &io,
                 const Binarization_Options & options
                );
    #endif

    #if defined SOL_REPORT
    void Save_SQL( lem::OFormatter &out, const SQL_Production &sql_version );
    #endif
  };
 }
#endif
