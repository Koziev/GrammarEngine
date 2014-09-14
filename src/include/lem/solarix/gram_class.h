// -----------------------------------------------------------------------------
// File GRAM_CLASS.H
//
// (c) Koziev Elijah
//
// Content:
// Класс GramClass - грамматический класс для Грамматик. Хранит объявления
// имен тех координат, которые как-то важны для статей Грамматик, принадлежащих
// к данному классу.
// Примерами могут служить классы предлогов, существительных, глаголов.
//
// 07.08.2008 - добавлена возможность вводить алиасы имени класса для
//              безболезненного рефакторинга.
// 13.12.2008 - добавлена возможность задавать секцию импорта атрибутов.
// -----------------------------------------------------------------------------
//
// CD->06.10.1995
// LC->29.10.2010
// --------------

#ifndef SOL_CLASS__H
#define SOL_CLASS__H
#pragma once

 #include <lem/noncopyable.h>
 #include <lem/solarix/coord_pair.h>
 #include <lem/solarix/string_set.h>

 namespace lem
 {
  namespace Iridium
  {
   class BethToken;
  }
 }

 namespace Solarix
 {
  using lem::UCString;
  using lem::IntCollect;

  class Grammar;

  /******************************************************
   Грамматический класс предназначен для группирования
   описания подмножеств статей грамматики. В частности,
   здесь хранятся списки индексов координат, которые
   считаются для данного класса атрибутами и измерениями.
  *******************************************************/
  class GramClass : lem::NonCopyable
  {
   public:
    lem::UCString name; // Имя грамматического класса.
    Solarix::UCStringSet aliases; // Синонимы имени
    CA_Array dim_index;  // Индексы координат-измерений.
    CA_Array attr_index; // Информация о координатах-атрибутах.
    CA_Array tag_index; // Информация о координатах-тэгах.

    IntCollect parent; // Список индексов базовых (родительских) классов.
    bool is_parent;    // Является ли сам класс родительским.

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    bool is_realized; // false, если было extern объявление, true если была реализация.
    UCString c_name;  // имя константы для объявления в C/C++-коде
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadAttributesTxt( Macro_Parser &file, const Grammar& gram );
    void LoadDimentionsTxt( Macro_Parser &file, const Grammar& gram );
    void LoadTagsTxt( Macro_Parser &file, const Grammar& gram );
    #endif

    #if defined SOL_SAVETXT
    void SaveAttributesTxt( OFormatter& txtfile, const Grammar& gram ) const;
    void SaveDimentionsTxt( OFormatter& txtfile, const Grammar& gram ) const;
    void SaveTagsTxt( OFormatter& txtfile, const Grammar& gram ) const;
    #endif

   protected:
    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual bool Load_Private_Data( 
                                   const lem::Iridium::BethToken &t,
                                   lem::Iridium::Macro_Parser &txtfile,
                                   Grammar& gram
                                  );
    #endif

    #if defined SOL_SAVETXT
    virtual void Save_Private_Txt( OFormatter& txtfile, const Grammar& gram ) const;
    #endif

   public:
    lem::MCollect< std::pair<GramCoordAdr/*attr*/, int/*default_state*/> > attr_defaults; // значения состояний по умолчанию

   public:
    GramClass(void);

    #if defined SOL_LOADBIN
    GramClass( lem::Stream &bin );
    #endif

    virtual ~GramClass(void);

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void LoadTxt(
                         Macro_Parser &txtfile,
                         Grammar& gram,
                         bool IsRealized
                        );
    #endif

    virtual void LoadBin( lem::Stream &bin );

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream &bin ) const;
    #endif

    inline const UCString& GetName(void) const { return name; }
    const UCStringSet& GetAliases(void) const { return aliases; }
    bool MatchName( const lem::UCString &name ) const;

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    inline bool IsRealized(void) const { return is_realized; }

    inline bool IsEmpty(void) const
    { return dim_index.empty() && attr_index.empty(); }
    #endif

    inline bool IsParent(void) const { return is_parent; }

    inline const IntCollect& parents(void) const { return parent; }

    inline const CA_Array& attrs(void) const { return attr_index; }
    inline const CA_Array& dims(void)  const { return dim_index;  }
    inline const CA_Array& tags(void)  const { return tag_index;  }

    bool FindLocCoordIndex( const GramCoordAdr iglobal, bool strict=false ) const;

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    bool operator==( const GramClass & c ) const;
    bool operator!=( const GramClass & c ) const;

    inline const UCString& get_C_Name(void) const { return c_name; }
    #endif

    #if defined SOL_SAVETXT
    // Распечатка в указанный поток исходного кода определения класса.
    // Исходный код восстанавливается по имеющемуся бинарному описанию. 
    void SaveTxt( OFormatter& txtfile, Grammar& gram ) const;
    #endif
  };

  const int SOL_EQUIL_INDEX = -4; // Для пометки тех элементов контекста,
                                  // которые требуют совпадения с заданным
                                  // другим элементом контекста.


 } // namespace 'Solarix'

#endif
