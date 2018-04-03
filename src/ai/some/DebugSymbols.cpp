#include <lem/math/integer_math.h>
#include <lem/macro_parser.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/SourceFilenameEnumerator.h>
#include <lem/solarix/debug_symbols.h>

using namespace lem;
using namespace Solarix;

DebugSymbols::DebugSymbols(void) : storage(nullptr)
{
}


DebugSymbols::~DebugSymbols()
{
}


void DebugSymbols::SetStorage(Solarix::LexiconStorage * _storage)
{
    storage = _storage;
    return;
}


#if defined SOL_COMPILER && defined SOL_LOADTXT
int DebugSymbols::RegisterLocation(
    const lem::Iridium::Macro_Parser &txt,
    const lem::Iridium::BSourceState &pos
)
{
    const int iline = txt.get(pos).GetLine();
    const int icolumn = txt.get(pos).GetSymbolPos();
    const int isrc = pos.GetFile();

    if (iline == UNKNOWN || isrc == UNKNOWN)
        return UNKNOWN;

    lem::Path p = txt.GetFileName(isrc).GetAbsolutePath();
    const int id_filename = storage->RegisterSourceFilename(p);
    const int id = storage->RegisterSourceLocation(id_filename, iline, icolumn);
    return id;
}
#endif



lem::Path DebugSymbols::GetFileName(int id_filename)
{
    lem::Path p;
    storage->GetSourceFilename(id_filename, p);
    return p;
}


bool DebugSymbols::GetLocation(int iloc, lem::Path &filename, int &line, int &column)
{
    int id_file = UNKNOWN;
    if (GetLocation(iloc, id_file, line, column))
    {
        if (id_file != UNKNOWN)
        {
            storage->GetSourceFilename(id_file, filename);
            return true;
        }
    }

    return false;
}



bool DebugSymbols::GetLocation(int iloc, int &ifile, int &line, int &column)
{
    if (iloc != UNKNOWN)
    {
        return storage->GetSourceLocation(iloc, ifile, line, column);
    }

    return false;
}



int DebugSymbols::Find(int id_file, int line, bool prox)
{
    // Сначала ищем самый левый токен в искомой строке.
    int id_loc = storage->FindSourceLineBeginning(id_file, line);
    if (id_loc != UNKNOWN)
        return id_loc;

    if (prox)
    {
        id_loc = storage->FindClosestSourceLocation(id_file, line);
        return id_loc;
    }

    return UNKNOWN;
}


SourceFilenameEnumerator * DebugSymbols::ListFiles()
{
    return new SourceFilenameEnumerator(storage->ListSourceFilenames());
}
