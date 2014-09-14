#ifndef SOL_GG_ENTRY__H
#define SOL_GG_ENTRY__H
#pragma once

 #include <lem/ucstring.h>
 #include <lem/cstring.h>
 #include <lem/containers.h>
 #include <lem/solarix/coord_pair.h>
 #include <lem/solarix/form_table.h>

 #if defined AddForm
  #undef AddForm
 #endif

 namespace Solarix
 {
  class GraphGram;

  extern lem::CString EncodeChar32ToUtf8( lem::uint32_t c );
  extern lem::UCString EncodeChar32ToWide( lem::uint32_t c );

  /***************************************************
   Представление одного графического варианта символа.
  ****************************************************/
  class GG_EntryForm
  {
   private:
    // Координатые пары измерений, отличающие данную буквоформу.
    lem::MCollect<GramCoordPair> dim;

    // Код символа в UCS-4
    lem::uint32_t name;

   public:
    GG_EntryForm(void)
    { name = 0; }

    GG_EntryForm( const CP_Array& Dim, lem::uint32_t Name );

    inline lem::uint32_t GetName(void) const { return name; }
    lem::CString GetNameUtf8(void) const;
    lem::UCString GetNameWide(void) const;

    inline const lem::MCollect<GramCoordPair>& dims(void) const { return dim; }
    inline lem::MCollect<GramCoordPair>& dims(void) { return dim; }
  };

  /************************************************************
   Статья графической грамматики содержит определения вариантов
   написания и кодировки одного символа Алфавита.
  *************************************************************/
  class GG_Entry : public Base_Entry
  {
   private:
    lem::uint32_t name;         // Имя статьи в UCS-4.
    int id_alphabet;            // Индекс алфавита, к которому принадлежит буквостатья
    
    lem::Collect<GG_EntryForm> form; // Список словоформ.

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void LoadName( Macro_Parser &txtfile, Dictionary &dict );
    virtual void AddForm(
                         const CP_Array& dim,
                         const WordFormName& form_name,
                         Dictionary &dict
                        );
    virtual bool ProcessSection(
                                Macro_Parser &txtfile,
                                Grammar &gram,
                                const BethToken &t
                               );

    virtual int CountForms(void) const { return CastSizeToInt(form.size()); }
    #endif

    virtual const Grammar& GetGrammar( const Dictionary &dict );
    virtual       Grammar& GetGrammar( Dictionary &dict );

   public:
    GG_Entry(void);
    GG_Entry( const GG_Entry& e );
    GG_Entry( lem::uint32_t Ucs4Name, int id_class, int id_alphabet, const lem::MCollect<GramCoordPair> &_attrs );
    GG_Entry& operator=( const GG_Entry& e );


    virtual void PrintName( OFormatter &where_to ) const;

    inline lem::uint32_t GetName(void) const { return name; }

    lem::CString GetNameUtf8(void) const;
    lem::UCString GetNameWide(void) const;

    inline const lem::Collect<GG_EntryForm>& forms(void) const { return form; }
    void Add( const GG_EntryForm  &f );

    const GG_EntryForm GetForm( int Index ) const;

    inline int GetAlphabet(void) const { return id_alphabet; }
  };

 }
#endif
