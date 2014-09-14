#if !defined WordSetChecker__H
 #define WordSetChecker__H

 namespace Solarix
 {
  class WordEntrySet;
  class Word_Form;

  class WordSetChecker
  {
   private:
    lem::uint8_t set_type; // 0 word_set, 1 wordentry_set, 2 wordform_set
    bool positive;
    lem::UCString set_name;
    lem::UCString export_node_name; // если проверяется именованное дерево и не узел ROOT_NODE

   public:
    WordSetChecker(void);
    WordSetChecker( int type, const lem::UCString &Setname, bool Positive, const lem::UCString & ExportNodeName );
    WordSetChecker( const WordSetChecker & x );
    void operator=( const WordSetChecker & x );

    bool operator!=( const WordSetChecker & x ) const;

    #if defined SOL_CAA
    bool Check( SynGram &sg, const Solarix::Word_Form &wf, WordEntrySet & sets ) const;
    #endif

    bool RequiresNamedNode() const { return !export_node_name.empty(); }
    const lem::UCString & GetNodeName() const { return export_node_name; }
    const lem::UCString & GetSetName() const { return set_name; }
    bool Affirmate( bool x ) const { return positive ? x : !x; }

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADBIN 
    void LoadBin( lem::Stream& binfile );
    #endif
  };

 }

#endif
