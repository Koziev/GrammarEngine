#if !defined AuxFormTypes__h
 #define AuxFormTypes__h

 #include <map>
 #include <lem/zeroed.h>
 #include <lem/process.h>
 #include <lem/ucstring.h>

 namespace lem
 {
  class OFormatter;
  namespace Iridium
  {
   class Macro_Parser;
  }
 }

 namespace Solarix
 {
  class LexiconStorage;

  class AuxFormTypes
  {
   private:
    LexiconStorage *db;
 
    int id_seq; // для создания новых ID при компиляции словаря

    std::map< int /*id*/, lem::UCString /**/ > id2name;

    // type names are stores in upper case in order to perform case insensitive lookup.
    std::map< lem::UCString /*name*/, int /*id*/> name2id;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs;
    #endif

    lem::tbool dirty;
    void Preload(void);

   public:
    AuxFormTypes(void);
    
    void Connect( LexiconStorage *_db );

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt( lem::Iridium::Macro_Parser &txtfile );
    #endif

    #if defined SOL_SAVETXT
    void SaveTxt( lem::OFormatter &txtfile ) const;
    #endif

    int operator[]( const lem::UCString &name );
    const lem::UCString& operator[]( int id );

    bool DoUpperCase( int id ) const { return true; } // заготовка на будущее - каждый тип может сам задавать нормализацию.
  };
 }

#endif
