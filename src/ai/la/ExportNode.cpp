#include <lem/solarix/ExportNodes.h>

using namespace Solarix;

void ExportNode::NormalizeCharCase()
{
    node_name.to_upper();
    as_name.to_upper();
}
