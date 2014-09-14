#if !defined SOL_PROJ_SCORE__H
#define SOL_PROJ_SCORE__H

#include <lem/math/fp1.h>

namespace Solarix
{
 struct ProjScore
 {
  lem::Real1 val;
  int score;

  ProjScore() : val(100), score(0) {}
  ProjScore( lem::Real1 _val ) : val(_val), score(0) {}
 };
}

#endif
