#if !defined MorphFiltersInfo__H
 #define MorphFiltersInfo__H

namespace Solarix
{
 struct MorphFiltersInfo
 {
  int min_len, max_len, left_filter_max_len, colloc_filter_max_len;
  MorphFiltersInfo() : min_len(lem::int_max), max_len(0), left_filter_max_len(0), colloc_filter_max_len(0) {}
 };
}
#endif
