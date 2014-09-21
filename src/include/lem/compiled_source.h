// -----------------------------------------------------------------------------
// File COMPILED_SOURCE.H
//
// (c) by Koziev Elijah
//
// Content:
// Класс CompiledSource - надстройка для класса Text_Parser - осуществление
// предкомпиляции текста с сохранением лексем в оперативной памяти.
// -----------------------------------------------------------------------------
//
// CD->28.01.97
// LC->16.10.04
// ------------

#ifndef LEM_COMPILED__H
#define LEM_COMPILED__H
#pragma once

 #include <lem/lexers.h>
 #include <lem/containers.h>

 namespace lem
 {

 class CompiledSource : public Text_Parser
 {
  private:
   Collect<AToken> text;
   int next; // индекс следующего читаемого токена из списка.
   bool compiled; // Становится true после завершения загрузки всех токенов.

  public:
   CompiledSource( int NTOKEN=0, CString *TOKENS=NULL );

   void Open( const char *txtname );
   virtual const AToken read(void);
   virtual void ToLineBegin(void);
   virtual const SourceState ftell(void) const;
   virtual void fseek( const SourceState &ss );
   virtual bool eof(void);
 };

 } // namespace lem

#endif
// --------------------------- End Of File [COMPILED_SOURCE.H] ------------------------
