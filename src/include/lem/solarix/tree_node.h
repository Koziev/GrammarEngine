// -----------------------------------------------------------------------------
// File TREE_NODE.H
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
//
// Content:
// Деревья-beth (грамматические деревья).
//
// PS: с этого заголовочного файла начиналась СОЛЯРИС в 1995 году...
// -----------------------------------------------------------------------------
//
// CD->06.10.1995
// LC->28.06.2012
// --------------

#if !defined( SOL_MATHLING__H )
#define SOL_MATHLING__H
#pragma once

 #include <lem/macros.h>
 #include <lem/ptr_container.h>
 #include <lem/oformatter.h>
 #include <lem/set.h>

 #include <lem/solarix/ref_name.h>
 #include <lem/solarix/gram_class.h>
 #include <lem/solarix/tree_link.h>
 #include <lem/solarix/word_form.h>
 #include <lem/solarix/form_table.h>

 namespace Solarix
 {
  using lem::PtrCollect;
  using lem::CloneCollect;
  using lem::Real1Array;
  using lem::Collect;
  using lem::MCollect;
  using lem::BaseSet;

  class Dictionary;
  class PM_Input;
  class SynGram;
  class Res_Pack;
  class PA_PrologSpace;
  class PA_Predicate;
  class PA_PrologSpace;
  class Result_Section;


  // ******************************
  // Слой связей.
  // ******************************
  class Tree_Node;
  class TreeDimension
  {
   private:
    lem::UCString name;
    lem::MCollect<Tree_Node*> nodes;

   public:
    TreeDimension(void);
    TreeDimension( const UCString &name );
    TreeDimension( const TreeDimension &x );
    ~TreeDimension(void);
    void operator=( const TreeDimension &x );

    void Clear(void);

    const UCString& GetName(void) const { return name; }
    const Tree_Node& operator[]( int i ) const { return *nodes[i]; }
          Tree_Node& operator[]( int i )       { return *nodes[i]; }

    void Add( Tree_Node *x );
    void Add( const TreeDimension &src );
    void Forget( int i ) { nodes[i]=NULL; }
    void Remove( int i );
    bool Empty(void) const { return nodes.empty(); }
    lem::Container::size_type size(void) const { return nodes.size(); }

    void SortByWordIndex();

    #if defined SOL_LOADBIN
    void LoadBin( lem::Stream &bin );
    #endif

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream &bin ) const;
    #endif

    void Print( const Solarix::Dictionary & dict, lem::OFormatter & out, bool detailed ) const;
    void PrintXML( lem::OFormatter & xml, const Solarix::Dictionary & dict ) const;
  };

  // ***********************************
  // Блок меток для узла.
  // ***********************************
  class TrValue;
  class TreeMarks
  {
   private:
    lem::UCString name; // имя блока
    lem::MCollect<TrValue*> values; // метки

   public:
    TreeMarks(void);
    TreeMarks( const UCString &Name );
    TreeMarks( const TreeMarks & x );
    ~TreeMarks(void);
 
    void operator=( const TreeMarks &x );

    const UCString & GetName(void) const { return name; }
    int Size(void) const { return CastSizeToInt(values.size()); } 
    const TrValue& operator[]( int i ) const { return * values[i]; }
          TrValue& operator[]( int i )       { return * values[i]; }

    void Add( TrValue *v );
    void Add( const TreeMarks &src );
    void Clear(void);

    #if defined SOL_LOADBIN
    void LoadBin( lem::Stream &bin );
    #endif

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream &bin ) const;
    #endif

    void Print( const Solarix::Dictionary &dict, lem::OFormatter &out ) const;
    void PrintXML( lem::OFormatter &out, const Solarix::Dictionary &dict ) const;
  };


 /*********************************************************************
  Универсальный класс для представления синтаксических (грамматических)
  деревьев в итерациях синтаксического анализа.
 **********************************************************************/
 class Tree_Node
 {
  protected:
   Tree_Link ilink;                     // Связка, которой наш узел подключен к вышестоящему
   lem::Ptr<Word_Form> node;            // Узловая синтаксема
   TreeDimension child;                 // Подсоединенные ветви - синтаксическое измерение графа
   lem::PtrCollect<TreeDimension> dims; // дополнительные измерения
   lem::PtrCollect<TreeMarks> marks;    // пометки

   void Init( const Tree_Node& tn );

  public:
   Tree_Node(void);
   Tree_Node( const Tree_Node& tn );
   explicit Tree_Node( const Word_Form& s );
   Tree_Node( Word_Form *s, bool dummy );
   explicit Tree_Node( lem::Stream &bin );

   void operator=( const Tree_Node& tn );

   void ForgetChild( int ichild );
   void ClearChildren(void);

   inline const Tree_Link& GetLinkIndex( int i ) const { return child[i].GetLink(); }
   inline const Tree_Link& GetLink(void) const { return ilink; }
   inline void SetLink( const Tree_Link& il ) { ilink=il; }
 
   // После этого вызова гарантировано будет измерение с именем name.
   TreeDimension& TouchDimension( const UCString &name );

   // Поиск измерения с указанным именем. Если не найдется, то возвращается NULL;
   TreeDimension* FindDimension( const UCString &name );
   const TreeDimension* FindDimension( const UCString &name ) const;

   const lem::PtrCollect<TreeDimension>& GetDimensions(void) const { return dims; }
         lem::PtrCollect<TreeDimension>& GetDimensions(void)       { return dims; }
   const TreeDimension& leafs(void) const { return child; }
         TreeDimension& leafs(void)       { return child; }
   const TreeDimension& leafs( const UCString &name ) const;
         TreeDimension& leafs( const UCString &name );

   TreeMarks& TouchMarks( const UCString &name );
   TreeMarks* FindMarks( const UCString &name );
   const TreeMarks* FindMarks( const UCString &name ) const;

         lem::PtrCollect<TreeMarks>& GetMarks(void)       { return marks; }
   const lem::PtrCollect<TreeMarks>& GetMarks(void) const { return marks; }

   inline const Word_Form& GetNode(void) const { return *node; }
   inline       Word_Form& GetNode(void)       { return *node; }
//   inline const Word_Form& GetOrgNode(void) const { return *org_node; }

   void SetNode( Solarix::Word_Form *new_node );

   // Проверяет полное владение указателем и если указатель разделяемый,
   // то создает свою копию.
   Word_Form& GetUnique(void);

//   inline int GetBethType( SynGram &sg ) const { return GetNode().GetBethType(sg); }
//   inline bool IsQuantor( SynGram &sg ) const { return node->IsQuantor(sg); }
//   inline bool IsAnyQuantor(void) const { return node->IsAnyQuantor(); }
//   inline bool IsUnknownQuantor(void) const { return node->IsUnknownQuantor(); }
//   inline bool IsMultyplicator( SynGram &sg ) const { return node->IsMultyplicator(sg); }

//   void Assemble_Entries_List( BaseSet<int> &entries ) const;

//   int CountClass( int iclass, SynGram &sg ) const;
//   int CountEntry( int ie ) const;

   int FindLinkedBy( const Tree_Link ilink ) const;

   bool DoesMatch( SynGram &sg, const Tree_Node& tn, bool strict_position=true ) const;
   bool operator==( const Tree_Node& tn ) const;
   bool operator!=( const Tree_Node& tn ) const;

   void Add( Tree_Node *to_add );
   void Add( const Tree_Node& to_add );

   #if defined SOL_CAA
   void Remove( int ichild );
   #endif

   void Print( lem::OFormatter &txtfile, SynGram &gram, int offset=-1, bool detailed=true ) const;
   void PrintPlain( lem::OFormatter &s, bool EntryKey ) const;
   void PrintXML( lem::OFormatter &xmlfile, SynGram &gram ) const;

   #if defined SOL_LOADBIN
   void LoadBin( lem::Stream &binfile );
   #endif

    #if defined SOL_SAVEBIN
   void SaveBin( lem::Stream &binfile ) const;
   #endif


   #if defined SOL_SAVETXT
   void SaveTxt(
                lem::OFormatter &txtfile,
                SynGram &gram,
                int Offset=0,
                bool detailed=true
               ) const;
   #endif

   #if defined SOL_CAA
//   inline int GetLabel(void) const { return label; }
//   inline void SetLabel( int l ) { label=l; }
//   void Label(void);
//   Tree_Node* CreateVersionedTree( const PM_Yield &yield ) const;
   #endif

//   bool Does_Contain_Class( int iClass, SynGram &sg ) const;

   Tree_Node* DeepCopy(void) const;
 };


 class Predef_Tree_Node : public Tree_Node
 {
  public:
   Predef_Tree_Node( int id_entry, SynGram &gram, int FakePosition=UNKNOWN );
 };

} // namespace 'Solarix'

#endif
