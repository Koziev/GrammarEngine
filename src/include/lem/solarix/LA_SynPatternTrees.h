#if !defined LA_SynPatternTrees__H
 #define LA_SynPatternTrees__H

 #include <lem/process.h>
 #include <lem/RWULock.h>
 #include <lem/containers.h>
 
 
 namespace Solarix
 {
  class SynPatternTreeNode;
  class LexiconStorage;
  class Dictionary;

  class LA_SynPatternTrees
  {
   public:
    enum { SOLID_PATTERN, NAMED_PATTERN, INCOMPLETE_PATTERN };

   private:
    Solarix::Dictionary *dict;
    Solarix::LexiconStorage *storage;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs_init;
    lem::Process::RWU_Lock cs_default_filter, cs_default_sorter, cs_named, cs_sparse_patterns;
    #endif

    void Delete(void);

    // для каждого языка храним отдельное решающее дерево

    // префиксное дерево для выполнения полной и точной фильтрации паттернами
    lem::MCollect< std::pair<int,SynPatternTreeNode*> > pattern_tree;

    // деревья для неполного анализа
    lem::MCollect< std::pair<int,SynPatternTreeNode*> > incomplete_pattern_tree;

    lem::MCollect<SynPatternTreeNode*> named_filter_trees;
    std::map< int, const SynPatternTreeNode* > id2filter;
    std::map< int, lem::UCString > id2name;

   public:
    LA_SynPatternTrees( Solarix::Dictionary *Dict );
    ~LA_SynPatternTrees(void);

    void Connect( LexiconStorage *Storage );

    const SynPatternTreeNode& GetDefaultFilter( int id_language );
    const SynPatternTreeNode& GetIncompleteFilter( int id_language );
    const SynPatternTreeNode& GetNamedFilter( int id_tree );

    const lem::UCString & GetPatternName( int id_tree );

    void StoreFilterTree( int id, const lem::UCString &name, SynPatternTreeNode *tree, int id_language, int pattern_type );
  };
 }

#endif
