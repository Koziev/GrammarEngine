#if !defined SG_Calibrator__H
 #define SG_Calibrator__H

 #include <lem/solarix/lexem.h>
 #include <lem/sol_io.h>
 #include <lem/solarix/coord_pair.h>

 namespace lem
 {
  namespace Iridium
  {
   class Macro_Parser;
  }
 }

 namespace Solarix
 {
  class SynGram;

  #if defined SOL_LOADTXT && defined SOL_COMPILER
  /***************************************************************************
   Калибратор: насколько часто используется словоформа. Набор таких структур
   позволяет предварительно настроить кэш Лексического Автомата, не дожидаясь,
   пока он накопит достаточную статистическую информацию о языке.
  ****************************************************************************/
  struct SG_calibrator
  {
   enum { UnknownType=-1, WordEntryFreq, WordFormScore, WordFormsScore };
   int freq_type;
   
   Solarix::Lexem word; // Лексическое содержимое
   int id_class;
   Solarix::CPE_Array coords; 
   int freq;  // Абсолютная частота использования.

   SG_calibrator() : id_class(UNKNOWN), freq(0), freq_type(UnknownType) {}
   SG_calibrator( const SG_calibrator &x );
   SG_calibrator( const lem::UCString & keyword, const Solarix::SynGram &sg, const lem::Sol_IO &io, lem::Iridium::Macro_Parser &txtfile );

   void operator=( const SG_calibrator &x );

   inline const Lexem& GetWord() const { return word; }
   inline int GetFreq() const { return freq; }
   int GetClass() const { return id_class; }

   bool MatchCoords( const CP_Array &form_coords ) const;

   bool IsWordEntryFreq() const { return freq_type==WordEntryFreq; }
   bool IsWordFormScore() const { return freq_type==WordFormScore; }
   bool IsWordFormsScore() const { return freq_type==WordFormsScore; }

   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );
  };
  #endif

 }
#endif
