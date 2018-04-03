// -----------------------------------------------------------------------------
// File SOL_IO.CPP
//
// (c) Koziev Elijah https://github.com/Koziev/GrammarEngine
//
// Content:
// Среда ввода-вывода: комплекс потоков для ввода-вывода информации прикладными
// программами.
// -----------------------------------------------------------------------------
//
// CD->14.10.2002
// LC->01.04.2018
// --------------

#include <lem/oformatter.h>
#include <lem/sol_io.h>

using namespace lem;

void Sol_IO::Flush(void)
{
    if (echo) echo->flush();
    if (err)  err->flush();
}
