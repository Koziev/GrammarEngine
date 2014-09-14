#include <lem/solarix/SynPattern.h>

using namespace lem;
using namespace Solarix;

bool PatternExportFuncContext_Wordform::ContainsCoordPair( const Solarix::GramCoordPair & pair ) const
{
 return wf->Find(pair); 
}

