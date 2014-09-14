#if !defined SG_NetLink__H
 #define SG_NetLink__H

 namespace lem
 {
  class OFormatter;
 }

 namespace Solarix
 {

 class SG_NetLink
 {
  private:
   Tree_Link link; // тип связи
   int entry_key0; // какая статья 
   int entry_key1; // с какой статьей связка
   int tags; // список дополнительных тэгов для связи

  public:
   SG_NetLink(void) { entry_key0=entry_key1=tags=UNKNOWN; }
   SG_NetLink( int EntryKey0, int EntryKey1, Tree_Link Link, int iTags )
    : link(Link), tags(iTags)
   { entry_key0=EntryKey0; entry_key1=EntryKey1; }

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   SG_NetLink(
              Macro_Parser &txtfile,
              SynGram &gram,
              bool realy,
              int EntryKey0=UNKNOWN
             );
   #endif     

   inline Tree_Link GetLink(void) const { return link; }
   inline int GetEntryKey0(void) const { return entry_key0; }
   inline int GetEntryKey1(void) const { return entry_key1; }
   inline int GetTags(void) const { return tags; }

   inline bool operator==( const SG_NetLink &x ) const
   { return link==x.link && entry_key0==x.entry_key0 && entry_key1==x.entry_key1 && tags==x.tags; }

   // Оператор сравнения применяется для сортировки списка связок
   inline bool operator<( const SG_NetLink &x ) const
   {
    return entry_key0 < x.entry_key0 ||
           (entry_key0==x.entry_key0 && entry_key1<x.entry_key1);
   }

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void LoadTxt(
                Macro_Parser &txtfile,
                SynGram &gram,
                bool realy,
                int EntryKey0=UNKNOWN
               );
   #endif

   #if defined SOL_SAVETXT
   void SaveTxt( lem::OFormatter &txtfile, SynGram &gram ) const;
   void SaveTagsTxt( lem::OFormatter &txtfile, SynGram &gram ) const;
   void PrintTagsTxt( lem::UFString &res, SynGram &gram ) const;
   #endif
 };

}
#endif
