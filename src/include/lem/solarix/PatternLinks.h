#if !defined PatternLinks__H
 #define PatternLinks__H

 #include <lem/ucstring.h>
 #include <lem/ptr_container.h>
 
 namespace lem
 {
  namespace Iridium
  {
   class Macro_Parser;
  }
 }


 namespace Solarix
 {
  struct SynPatternResult;
  class LexicalAutomat;

  class PatternLink
  {
   public:
    lem::UCString from_marker, from_node;
    lem::UCString to_marker, to_node;
    bool optional_to_node;
    int link_type;

   private:
    #if defined SOL_CAA
    const Solarix::Word_Form* GetNode(
                                      const LexicalAutomat & la,
                                      const lem::MCollect<int> & PatternSequenceNumber,
                                      SynPatternResult * cur_result,
                                      const lem::UCString & marker_name,
                                      const lem::UCString & node_name,
                                      bool optional_to
                                     ) const;
    #endif

   public:
    PatternLink(void);

    bool operator!=( const PatternLink & x ) const;

    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );

    #if defined SOL_CAA
    void Generate( const LexicalAutomat & la, const lem::MCollect<int> & PatternSequenceNumber, SynPatternResult * cur_result ) const;
    #endif

    #if defined SOL_CAA
    void GenerateConnections( const std::multimap<lem::UCString,const Word_Form*> & points, SynPatternResult * cur_result ) const;
    #endif
  };


  class PatternDefaultLinkage
  {
   private:
    bool optional_node;
    lem::UCString marker_name, node_name;

   public:
    PatternDefaultLinkage(void);
    PatternDefaultLinkage( const lem::UCString & marker, const lem::UCString & node, bool optional );

    bool IsOptional(void) const { return optional_node; }
    const lem::UCString& GetMarker(void) const { return marker_name; }
    const lem::UCString& GetNode(void) const { return node_name; }

    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );

    #if defined SOL_CAA
    void Generate( const LexicalAutomat & la, const lem::MCollect<int> & PatternSequenceNumber, SynPatternResult * cur_result ) const;
    #endif
  };


  class Dictionary;
  class SynPatternCompilation;
  class PatternLinks
  {
   private:
    lem::PtrCollect<PatternLink> links;
    lem::PtrCollect<PatternDefaultLinkage> groups;

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void AddGroup(
                  const lem::UCString &marker_name,
                  const lem::UCString & node_name,
                  bool optional_node
                 );

    void AddLink(
                 const lem::UCString & from_marker,
                 const lem::UCString & from_node,
                 int link_type,
                 const lem::UCString & to_marker,
                 const lem::UCString & to_node,
                 bool optional_to_node
                );

    void LoadNode( 
                  Dictionary &dict,
                  lem::Iridium::Macro_Parser & txtfile,
                  SynPatternCompilation & compilation_context,
                  lem::UCString & marker_name,
                  lem::UCString & node_name,
                  std::set<lem::UCString> & linked_markers // для контроля повторного использования маркировки
                 ) const;

    void LoadNodeAndChildren(
                             int to_root_link,
                             bool optional_node,
                             const lem::UCString &root_marker_name,
                             const lem::UCString &root_node_name,
                             Dictionary &dict,
                             lem::Iridium::Macro_Parser & txtfile,
                             SynPatternCompilation & compilation_context,
                             std::set<lem::UCString> & linked_markers // для контроля повторного использования маркировки
                            );
    #endif


   public:
    PatternLinks(void);
    PatternLinks( const PatternLinks &x );

    void operator=( const PatternLinks &x );

    bool operator!=( const PatternLinks &x ) const;

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt( 
                 Dictionary &dict,
                 lem::Iridium::Macro_Parser & txtfile,
                 SynPatternCompilation & compilation_context
                );

    #endif    

    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );

    #if defined SOL_CAA
    void Generate( const LexicalAutomat & la, const lem::MCollect<int> & PatternSequenceNumber, SynPatternResult * cur_result ) const;
    #endif

    #if defined SOL_CAA
    const lem::UCString& GetRootNodeMarker() const;
    #endif

    #if defined SOL_CAA
    void GenerateConnections( const std::multimap<lem::UCString,const Word_Form*> & points, SynPatternResult * cur_result ) const;
    #endif
  };

 }

#endif
