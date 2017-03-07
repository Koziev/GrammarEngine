#if !defined SOL_PROJ_SCORE__H
#define SOL_PROJ_SCORE__H

#include <lem/math/fp1.h>

namespace Solarix
{
 struct ProjScore
 {
  float score;

  ProjScore() : score(0) {}
  ProjScore( float _score ) : score(_score) {}
 };
}

#endif
