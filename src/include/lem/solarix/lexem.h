// -----------------------------------------------------------------------------
// File LEXEM.H
//
// (c) Koziev Elijah
//
// Content:
// Лексемы: класс Lexem, расширение класса строк (UCString).
// -----------------------------------------------------------------------------
//
// CD->06.10.1995
// LC->07.05.2011
// --------------

#ifndef SOL_LEXEMS__H
#define SOL_LEXEMS__H
#pragma once

 #include <lem/integer.h>
 #include <lem/smart_pointers.h>
 #include <lem/quantors.h>
 #include <lem/containers.h>

 namespace lem
 {
  namespace Iridium { class Macro_Parser; }
  
  class OFormatter;
  class Stream;
 }

 namespace Solarix
 {
  using lem::uint8_t;
  using lem::int8_t;

  using lem::Iridium::Macro_Parser;
  using lem::OFormatter;
  using lem::Stream;
  using lem::UCString;

  // Спецсимволы для СубАвтомата Формообразования.
  const wchar_t B_STRESS_METACHAR        = L'+';
  const wchar_t B_UNSTRESS_METACHAR      = L'@';
  const wchar_t B_PRECISE_METACHAR       = L'^';
  const wchar_t B_COMMAND_METACHAR       = L'%';
  const wchar_t B_CUT_METACHAR           = L'c';
  const wchar_t B_REDUCE_METACHAR        = L'-';
  const wchar_t B_PREFIX_INSERT_METACHAR = L'a';
  const wchar_t B_GROUP_BEGIN_METACHAR   = L'{';
  const wchar_t B_GROUP_END_METACHAR     = L'}';
  const wchar_t B_ANY_METACHAR           = L'*';
  const wchar_t B_PLAIN_METACHAR         = L'$'; // След. символ не следует понимать
                                                // как метасимвол...
  const wchar_t B_DOUBLE_METACHAR        = L'D';
 

 inline bool sol_is_lex_metachar( wchar_t ch )
 {
  return ch==B_STRESS_METACHAR   ||
         ch==B_UNSTRESS_METACHAR ||
         ch==B_PRECISE_METACHAR  ||
         ch==B_COMMAND_METACHAR  ||
         ch==B_ANY_METACHAR      ||
         ch==B_PLAIN_METACHAR;
 }

 class GraphGram;
 class UCStringSet;

 const int STRESSED_FLAG   = 0;
 const int UNSTRESSED_FLAG = 1;

 // Константы для поля Lexem::compare_flags.
 const int8_t SOL_LEX_NOT_SOL_DETAILED = 0;
 const int8_t SOL_LEX_SOL_DETAILED     = 1;


 class Lexem : public UCString // Имена статей для символов.
 {
  private:
   void ToString( int *isrc, int *idst, wchar_t *buffer ) const;

   #if defined SOL_LOADTXT
   void TranslateChar(
                      const GraphGram &gram,
                      wchar_t ch,
                      const wchar_t *src,
                      wchar_t &res_char,
                      const lem::MCollect<int>& id_alphabet
                     ) const;

   void TranslateSubString(
                           const wchar_t src[],
                           int &i_src,
                           wchar_t buffer[],
                           int &i_res,
                           const GraphGram &gram,
                           int mode,
                           const lem::MCollect<int>& id_alphabet
                          ) const;

   void TranslateThis(
                      int &i_res,
                      const wchar_t src[],
                      wchar_t buffer[],
                      const GraphGram &gram,
                      int mode,
                      const lem::MCollect<int>& id_alphabet
                     ) const;
   #endif

   bool CompareAcsents( const Lexem &l ) const;

  public:
   static wchar_t DelimiterChar; // Символ для разделения лексем в мультилексеме
   static const wchar_t *DelimiterStr;

  public:
   Lexem(void) {}
   Lexem( const UCStringSet &list );
   Lexem( lem::Stream &bin );
   Lexem( const wchar_t *str );
   Lexem( const UCString &x );


   bool CompareAll_1( const Lexem &l ) const;

   #if defined SOL_LOADTXT
   void Translate( const GraphGram &gram, int Mode=1 );
   void Translate( const GraphGram &gram, int Mode, const lem::MCollect<int>& id_alphabet );
   #endif

   const UCString ToString(void) const;
   const UCString ToWord(void) const;

//   inline const UCString& string(void) const { return *this; }

/*
   wchar_t GetCharForm( int i ) const
   {
    LEM_CHECKIT_Z(i<LEM_CSTRING_LEN1);
    return form[i];
   }

   inline int8_t GetCharStress( int i ) const
   {
    LEM_CHECKIT_Z(i<LEM_CSTRING_LEN1);
    return stress[i];
   }

   inline const wchar_t* GetCharForms(void)     const { return form; }
   inline const int8_t* GetCharStresses(void)   const { return stress; }
*/

   /***************************************************************
    Вычисляем хэшы. В дополнении к CString'овским числам - длине
    строки 'len' и хэш-коду 'hash' получаем собственное число -
    'compare_flags'
   ****************************************************************/
/*
   inline void calc_hash(void)
   {
    UCString::calc_hash();
    calc_hash_2();
   }
*/

   // Возвращает число входящих в лексему частей, разделенных пробелом
   inline int Count_Lexems(void) const { return count(DelimiterChar)+1; }

   // Для мультилексемы возвращается список входящих в ее состав лексем.
   void Split( UCStringSet &list ) const;

   // Декоративная процедура - убирает из мультилексемы во внутреннем представлении
   // избыточные пробелы, например для "тяп-ляп", которая внутри хранится как "тяп - ляп"
   static void CorrectFormSpaces( UCString &f );

   void SaveBin( lem::Stream &bin ) const;
   bool Can_Be_Packed( const Lexem &base, uint8_t *pack_flags ) const;
   void SaveBin_Packed( lem::Stream &bin, const Lexem &base, uint8_t pack_flags ) const;
   void LoadBin( lem::Stream &bin );
   void LoadBin_Packed( lem::Stream &bin, const Lexem &base, uint8_t pack_flags );

   void Add( const UCString &str );
 };

 
  typedef boost::shared_ptr<Lexem> RC_Lexem;

  // Процедура меняет регистр символов в мультилексеме по шаблону Нью-Йорк - то есть
  // каждая лексема начинается с заглавной.
  extern void MakeEachLexemAa( lem::UCString &s );
  extern void MakeEachLexemAa( lem::UFString &s );


 } // namespace 'Solarix'

#endif
