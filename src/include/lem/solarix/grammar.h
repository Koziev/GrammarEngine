// -----------------------------------------------------------------------------
// File GRAMMAR.H
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// LEM C++ library  http://www.solarix.ru
// Классы поддержки Грамматик - разновидности Автоматов.
//
// 16.11.2010 - рефакторинг интерфейса доступа к списку классов.
// -----------------------------------------------------------------------------
//
// CD->29.05.1997
// LC->16.11.2010
// --------------

#ifndef SOL_GRAMMAR__H
#define SOL_GRAMMAR__H
#pragma once

 #include <lem/ptr_container.h>
 #include <lem/solarix/automaton.h>
 #include <lem/solarix/coordinate.h>
 #include <lem/solarix/gram_class.h>

 namespace Solarix
 {
  class ClassList;
  class CoordList;

  /**************************************************************
   Базовый класс для описания различных грамматик, основанный на
   некоторых обнаруженных теоретически общих моментах.
  **************************************************************/
  class Grammar : public Automaton
  {
   private:
    friend class Dictionary;

   protected:
    ClassList * aclass; // Список определений грамматических классов.
    CoordList * coord;  // справочник определений грамматических категорий
    int ilink_type;     // Индекс перечня имен связок (особого вида координаты)
    
   protected:
    #if defined SOL_LOADTXT && defined SOL_COMPILER

    /************************************************************************
     Этот метод переопределяется производным классом Грамматики и вызывается
     из метода ProcessLexem для загрузки словарной статьи из текстового
     файла. Курсор чтения находится на первом символе заголовка статьи.
    *************************************************************************/
    virtual void LoadEntry(
                           Macro_Parser& txtfile,
                           bool is_extern,
                           const Binarization_Options &options
                          ) {}

    virtual void LoadCoord( Macro_Parser& txtfile, bool is_extern );
    virtual void LoadClass( Macro_Parser& txtfile, bool is_extern );

    /***********************************************************************
     Перед началом первой загрузки Грамматики из текстового файла установим
     нумерацию ключей.
    ************************************************************************/
    virtual void PreLoad(
                         Macro_Parser &txtfile,
                         const Binarization_Options &options
                        ) {}

    virtual bool ProcessLexem(
                              const BethToken &t,
                              Macro_Parser& txt,
                              const Binarization_Options &options
                             );
    #endif

   public:
    Grammar( int Index );
    virtual ~Grammar(void);

    #if defined SOL_LOADBIN
    void LoadBin( lem::Stream& bin, const Load_Options &opt );
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void Prepare( const lem::Path &outdir, const Binarization_Options &opts );
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    GramCoordAdr LoadCoordIdTxt( lem::Iridium::Macro_Parser & txtfile, bool allow_quantors ) const;
    #endif

    const GramCoordAdr FindCoord( const UCString& coord_name ) const;
    const GramCoordPair FindCoordPair(
                                      Macro_Parser& txtfile,
                                      bool index_ref=false
                                     ) const;

    // Returns the index of class with name given
    int FindClass( const UCString& class_name ) const;

    // Access to the list of grammatical category declarations
    inline CoordList& coords(void) const { return *coord; }

    inline ClassList& classes(void) { return *aclass; }

    int GetnLink(void);
    int FindLink( const UCString& link_name );
    const UCString& GetLink( int i );

    #if defined SOL_REPORT
    virtual void Report( OFormatter &where_to );
    #endif
  };

 } // namespace 'Solarix'

#endif
