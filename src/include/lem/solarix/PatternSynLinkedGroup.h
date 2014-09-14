#if !defined PatternSynLinkedGroup__H
 #define PatternSynLinkedGroup__H

 #include <lem/containers.h>

 namespace Solarix
 {
  class Word_Form;
  class LexerTextPos;

  struct PatternSynLinkedGroup
  {
   const LexerTextPos *begin, *end;
   const Word_Form * root_node;

   PatternSynLinkedGroup(void) : begin(NULL), end(NULL), root_node(NULL) {}
   PatternSynLinkedGroup( const LexerTextPos * _begin, const LexerTextPos * _end, const Word_Form * root )
     : begin(_begin), end(_end), root_node(root) {}

   bool operator==( const PatternSynLinkedGroup & y ) const
   {
    return begin==y.begin && end==y.end && root_node==y.root_node;
   }
  };  

  typedef lem::MCollect<PatternSynLinkedGroup> LINKAGE_GROUPS;
 }

#endif
