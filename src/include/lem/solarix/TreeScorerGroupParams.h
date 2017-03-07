#if !defined TreeScorerGroupParams__H
#define TreeScorerGroupParams__H

namespace Solarix
{
 struct TreeScorerGroupParams
 {
  bool allow_unmatched_children;
  int id_language; // целевой язык для поиска словарных статей в опорных точках

  TreeScorerGroupParams() : allow_unmatched_children(true), id_language(UNKNOWN)
  {}
 };
}

#endif
