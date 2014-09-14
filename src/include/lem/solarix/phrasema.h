// -----------------------------------------------------------------------------
// File PHRASEMA.H
//
// (c) Koziev Elijah
//
// Content:
// Класс Phrasema - фразема, хранит звуковое и текстовое представления фразы,
// введенной пользователем или сгенерированной Системой для выдачи.
// -----------------------------------------------------------------------------
//
// CD->03.04.1998
// LC->08.07.2012
// --------------

#ifndef SOL_PHRASEMA__H
#define SOL_PHRASEMA__H
#pragma once

 #include <lem/ptr_container.h>
 #include <lem/solarix/lexem.h>
 //#include <lem/solarix/TokenizationTags.h>

 namespace lem
 {
  class OFormatter;
 }

 namespace Solarix
 {

 class Dictionary;
 class TrTrace;

 class SentenceWord
 {
  public:
   lem::UCString word;
   Solarix::Lexem normalized_word;
   //lem::Ptr<TokenizationTags> tags;
   //lem::Ptr<lem::UFString> tokenizer_flags;

  public:
   SentenceWord(void) {}

   SentenceWord( const SentenceWord &x );
   void operator=( const SentenceWord &x );

   //bool HasTokenizerFlag(void) const { return tokenizer_flags.NotNull(); }
 };


 #if defined SOL_CAA && !defined SOL_NO_AA
 // *****************************************************************
 // Результат сегментации и токенизации текста.
 // *****************************************************************
 class Sentence
 {
  private:
   lem::PtrCollect<SentenceWord> words;

  public:
   lem::UFString org_phrase; // исходный текст предложения
   int id_language; // определенный для фразы язык (UNKNOWN по умолчанию)

  public:
   Sentence(void);
   Sentence( const Sentence &x );
   
   virtual ~Sentence() {}

   void operator=( const Sentence &x );

   virtual void Parse(
                      const lem::UFString &buffer,
                      bool Pretokenized,
                      Solarix::Dictionary * dict,
                      int LanguageID,
                      TrTrace *trace
                     );

   const lem::UCString & GetWord( int word_index ) const { return words[word_index]->word; }
   const Solarix::Lexem & GetNormalizedWord( int word_index ) const { return words[word_index]->normalized_word; }
   //const TokenizationTags * GetTags( int word_index ) const { return words[word_index]->tags.IsNull() ? NULL : words[word_index]->tags.get(); }
   //const lem::UFString * GetFlags( int word_index ) const { return words[word_index]->tokenizer_flags.IsNull() ? NULL : words[word_index]->tokenizer_flags.get(); }
   //bool HasTokenizerFlag( int word_index ) const { return GetFlags(word_index)!=NULL; }

   void PrintOrg( OFormatter &s ) const;

   void AddWord( const lem::UCString & word );

   const lem::UFString string( wchar_t delimiter=L' ' ) const;
   void clear(void);
   bool empty(void) const { return words.empty(); }
   lem::Container::size_type size(void) const { return words.size(); }

   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );
 };
 #endif

 } // namespace 'Solarix'


#endif
