#if !defined TreeScorerGroupParams__H
#define TreeScorerGroupParams__H

namespace Solarix
{
 struct TreeScorerGroupParams
 {
  bool allow_unmatched_children;

  TreeScorerGroupParams() { allow_unmatched_children=true; }
 };
}

#endif
