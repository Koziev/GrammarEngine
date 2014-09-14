#if !defined RECO2_MatchContext__H
 #define RECO2_MatchContext__H

 #include <lem/ucstring.h>
 #include <lem/solarix/phrasema.h>
 #include <lem/solarix/R2Utils.h>

 namespace Solarix
 {
  class Tree_Node;
 }


 namespace Reco2
 {
  struct MatchContext : lem::NonCopyable
  {
   lem::MCollect<lem::UCString> words;
   lem::MCollect<const Solarix::Word_Form*> nodes;

   lem::PtrCollect<ints> word_ids;
   ints weights;
   lem::PtrCollect< floats > word_rels;

   lem::PtrCollect< std::set<int> > word_points;

   lem::PtrCollect< std::set<int> > word_patterns;
  };
 }

#endif
