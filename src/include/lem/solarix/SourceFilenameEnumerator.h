#if !defined SourceFilenameEnumerator__H
#define SourceFilenameEnumerator__H

#include <lem/noncopyable.h>
#include <lem/path.h>

namespace Solarix
{
    class LS_ResultSet;
    class SourceFilenameEnumerator : lem::NonCopyable
    {
    private:
        LS_ResultSet *rs;

    public:
        SourceFilenameEnumerator(LS_ResultSet * _rs);
        ~SourceFilenameEnumerator();

        bool Fetch();
        int GetId();
        lem::Path GetFilename();
    };
}

#endif
