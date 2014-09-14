#if !defined PartOfSpeech__H
 #define PartOfSpeech__H

 #include <lem/ptr_container.h>
 #include <lem/solarix/gram_class.h>


 namespace Solarix
 {
  struct ImportFiltrerCoords : lem::NonCopyable
  {
   lem::MCollect<Solarix::GramCoordAdr> coords;
   int aux_type;
   lem::UCString aux_type_str;

   ImportFiltrerCoords() : aux_type(UNKNOWN) {}

   bool empty() const { return coords.empty() && aux_type==UNKNOWN; }
  };

  class Grammar;
  class SG_Class : public GramClass
  {
   public:
    int id_lang; // Language id for the word entries belonging for this class.
    int value; // Ценность класса, 0 - мусор, 1 - служебные частицы, 10 - знаменательные слова
    bool closed_class; // словарные статьи не участвуют в генерации правил распознавания по окончанию

   protected:
    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual bool Load_Private_Data( 
                                   const lem::Iridium::BethToken &t,
                                   lem::Iridium::Macro_Parser &txtfile,
                                   Solarix::Grammar& gram
                                  );
    void LoadImport( lem::Iridium::Macro_Parser &txtfile, Solarix::Grammar& gram );
    #endif

    #if defined SOL_SAVETXT
    virtual void Save_Private_Txt( lem::OFormatter& txtfile, const Solarix::Grammar& gram ) const;
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream &bin );
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream &bin ) const;
    #endif

   public:
    #if defined SOL_LOADTXT && defined SOL_COMPILER
    // Секция импорта атрибутов - используется только на стадии компиляции
    lem::MCollect<Solarix::GramCoordAdr> import_coord; // какие координаты импортируются
    lem::MCollect<int> import_class; // из какого грамматического класса каждая из координат импортируется
    lem::Ptr_NC_Collect<ImportFiltrerCoords> import_filters; // для омонимичных статей - по каким координатам идет отбор
    #endif

   public:
    SG_Class(void);

    int GetLanguage() const { return id_lang; }
    int GetValue() const { return value; }
    bool IsClosed() const { return closed_class; }

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    inline bool HasImport() const { return !import_coord.empty(); }
    bool IsImportableAttribute( const GramCoordAdr &coord ) const;
    #endif
  };  

 }
#endif
