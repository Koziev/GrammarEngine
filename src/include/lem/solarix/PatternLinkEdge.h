#if !defined PatternLinkEdge__H
 #define PatternLinkEdge__H

 #include <lem/quantors.h>
 #include <lem/containers.h> 

 namespace Solarix
 {
  class Word_Form;
  struct PatternLinkEdge
  {
   const Solarix::Word_Form *from, *to;
   int link_type;

   PatternLinkEdge(void) : from(NULL), to(NULL), link_type(UNKNOWN) {}
   PatternLinkEdge( const Solarix::Word_Form * f, int l, const Solarix::Word_Form * t ) : from(f), to(t), link_type(l) {}

   bool operator==( const PatternLinkEdge & x ) const
   { return from==x.from && to==x.to && link_type==x.link_type; }
  };

  typedef lem::MCollect<PatternLinkEdge> LINKAGE_EDGES;
 }

#endif
