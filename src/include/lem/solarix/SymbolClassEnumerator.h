#if !defined SymbolClassEnumerator__H
 #define SymbolClassEnumerator__H


 #include <lem/solarix/ClassEnumerator.h>

 namespace Solarix
 {
  class GraphGram;
  class LS_ResultSet;

  class SymbolClassEnumerator : public ClassEnumerator
  {
   private:
    AlphabetStorage *db;
    GraphGram *gg;
    LS_ResultSet *rs;
   
   public:
    SymbolClassEnumerator( AlphabetStorage *_db, GraphGram *_gg );
    virtual ~SymbolClassEnumerator(void);
 
    virtual bool Fetch(void);
    virtual int GetId(void);
    virtual const GramClass& GetItem(void);
  };
 }

#endif
