#if !defined ExportNode__H
#define ExportNode__H

#include <lem/ucstring.h>

namespace Solarix
{
    struct ExportNode
    {
        lem::UCString node_name, as_name;

        bool operator==(const ExportNode & x) const { return node_name == x.node_name && as_name == x.as_name; }
        bool operator!=(const ExportNode & x) const { return node_name != x.node_name || as_name != x.as_name; }

        void NormalizeCharCase();
    };
}

#endif
