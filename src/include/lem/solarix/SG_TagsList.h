#if !defined SG_TagsList__H
 #define SG_TagsList__H

 #include <lem/containers.h>

 namespace Solarix
 {
  using SG_TagsList = const lem::MCollect< std::pair<int/*id_tag*/,int/*ivalue*/> >*;

  class SynGram;
  extern void PrintTags( SG_TagsList tags, lem::UFString &str, SynGram &sg );
 }
#endif

