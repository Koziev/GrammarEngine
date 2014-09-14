#ifndef SE_TEXT__H
#define SE_TEXT__H
#pragma once

 #include <lem/math/fp1.h>
 #include <lem/solarix/file_factory.h>
 #include <lem/solarix/form_table.h> 
// #include <lem/solarix/phrasoblock.h> 

 namespace Solarix
 {
  namespace Search_Engine
  {
   using lem::MCollect;
   using lem::Real1;
   using lem::UFString;

  // ******************************
  // Результаты проекции лексемы
  // ******************************
  struct Lexem_Projs
  {
   private:
    Lexem_Projs( const Lexem_Projs& );
    void operator=( const Lexem_Projs& );

   public:
    MCollect<Word_Coord> found_list;
    MCollect<Real1> val_list;

    Lexem_Projs(void) {};
  };

 // ***********************************
 // Для каждого слова нужно знать, где
 // в файле оно было расположено.
 // ***********************************
 struct File_Lexem : public Solarix::Search_Engine::Base_File_Lexem
 {
  int sent_number;       // номер предложения, к которому принадлежит слово
//  UCString uppered_word; // слово в верхнем регистре
  Lexem_Projs *projs;    // проекции лексемы на лексикон (NULL, если проекции не сделано)

  File_Lexem(void)
  {
   sent_number=UNKNOWN;
   projs = NULL;
  } 
 };



  // *************************************************************
  // Одно предложение текста. Храним не сами слова, а индексы слов
  // в постороннем списке.
  // *************************************************************
  struct Sentence
  {
   int number;     // порядковый номер в тексте
   int from, upto; // лексемы, входящие в предложение.

   #if !defined SOL_NO_AA
//   Solarix::PhrasoBlock *fblo; // Результат синтаксического анализа. Удаляем не мы.
   #endif

   Sentence(void)
   {
    number=UNKNOWN;
    from=upto=UNKNOWN;

    #if !defined SOL_NO_AA
//    fblo=NULL;
    #endif
   }

   // Возвращает число слов в предложении
   inline int length(void) const { return upto-from+1; }
  };


  // ***********************************
  // Весь загруженный текст документа.
  // ***********************************
  class Text
  {
   private:
    Text( const Text& );
    void operator=( const Text& );

   public:
    UFString whole_text; // Текст в виде одной строки
    MCollect<File_Lexem> lexems; // Разбитый на лексемы текст
    MCollect<Sentence> sent; // предложения

    MCollect<Lexem_Projs*> projs; // проекции для лексем

    #if !defined SOL_NO_AA
//    MCollect<Solarix::PhrasoBlock*> fblos; // фразоблоки - результаты синтаксического
                                           // анализа предложений. 
    #endif

    bool loaded; // Была ли реальная попытка загрузить текст

    Text(void)
    {
     loaded=false;

     projs.reserve(1024);

     #if !defined SOL_NO_AA
     //fblos.reserve(1024);
     #endif

     lexems.reserve(1024);
     sent.reserve(128);
    }

    ~Text(void)
    {
     ZAP_A(projs);
     #if !defined SOL_NO_AA
//     ZAP_A(fblos);
     #endif
    }
  };

 } // namespace Search_Engine
 } // namespace Solarix

#endif
