#if !defined SG_TagsList__H
 #define SG_TagsList__H

 #include <lem/containers.h>

 namespace Solarix
 {
  typedef const lem::MCollect< std::pair<int/*id_tag*/,int/*ivalue*/> >* SG_TagsList;

  class SynGram;
  extern void PrintTags( SG_TagsList tags, lem::UFString &str, SynGram &sg );
 }
#endif

