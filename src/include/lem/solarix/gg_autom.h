// -----------------------------------------------------------------------------
// File GG_AUTOM.H
//
// (c) Elijah Koziev
//
// Content:
// Описание Графической Грамматики, то есть Алфавита, для объектного языка
// Системы.
// -----------------------------------------------------------------------------
//
// CD->15.03.1996
// LC->05.06.2011
// --------------

#ifndef SOL_GRAPH_GRAMMAR__H
#define SOL_GRAPH_GRAMMAR__H
#pragma once

 #include <lem/qarray.h>
 #include <lem/solarix/grammar.h>

 #if defined AddForm
  #undef AddForm
 #endif

 namespace Solarix
 {
  class GraphGram;
  class GG_Entry;
  class Alphabet;
  class Alphabets;
  class Symbols;
  class AlphabetStorage;


  extern lem::UCString EncodeChar32ToWide( lem::uint32_t c );
  extern lem::CString EncodeChar32ToUtf8( lem::uint32_t c );

  class GG_CharOperations;
  class SyllabRules;
  class LA_RecognitionTrace;
  
  /*********************************************************************
   Описание Графической Грамматики, то есть Алфавит объектного языка.
  **********************************************************************/
  class GraphGram : public Grammar
  {
   private:
    AlphabetStorage * storage;
    bool do_delete_storage;

    Alphabets *alphabet;
    Symbols *symbols;
    GG_CharOperations *char_operations;
    SyllabRules *syllab_rules;

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void LoadEntry(
                           Macro_Parser& txtfile,
                           bool is_extern,
                           const Binarization_Options &options
                          );
    #endif

   protected:
    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual bool ProcessLexem(
                              const BethToken &t,
                              Macro_Parser& txt,
                              const Binarization_Options &options
                             );
    #endif

    #if defined SOL_REPORT
    virtual void Save_SQL( OFormatter &out, OFormatter &alters, const SQL_Production &sql_version ); 
    virtual void SaveRules_SQL( OFormatter &out, OFormatter &alters, const SQL_Production &sql_version ); 
    #endif

   public:
    GraphGram(void);
    ~GraphGram(void);

    void SetStorage( AlphabetStorage *_storage, bool _do_delete );
    AlphabetStorage& GetStorage(void) { return *storage; }

    const Word_Coord FindSymbol( wchar_t code ) const;
    const Word_Coord FindSymbol( wchar_t code, int AlphabetID ) const;
    const Word_Coord FindSymbol( wchar_t code, const lem::MCollect<int> &AlphabetID ) const;
    void FindSymbol( wchar_t code, MCollect<Word_Coord> &projs ) const;
    void FindSymbol( wchar_t code, MCollect<Word_Coord> &projs, int AlphabetID ) const;
    void FindSymbol( wchar_t code, MCollect<Word_Coord> &projs, const lem::MCollect<int> &AlphabetID ) const;

    Symbols& entries(void) const { return *symbols; }

    #if defined SOL_REPORT
    virtual void Report( OFormatter &where_to );
    virtual void PrintMap( OFormatter &txtfile );
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void Prepare( const lem::Path &outdir, const Binarization_Options &opts );
    #endif

    virtual const UCString GetName(void) const;

    inline Alphabets& alphabets(void) { return *alphabet; }
    inline GG_CharOperations& GetCharOperations(void) { return *char_operations; }

    // Возвращает индекс дескриптора алфавита по его имени.
    int Find_Alphabet( const UCString &Name ) const;

    void BeforeSyntaxRecompilation(void);

    void FindSyllabs(
                     const lem::UCString & word,
                     int id_language,
                     bool get_upper_case,
                     lem::MCollect<lem::UCString> &result_syllabs,
                     LA_RecognitionTrace *trace
                    );
  };

 } // namespace 'Solarix'

#endif
