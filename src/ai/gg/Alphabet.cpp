#include <lem/solarix/Alphabet.h>

using namespace Solarix;


Alphabet::Alphabet(void)
{}

Alphabet::Alphabet(int Id, const lem::UCString &Name)
    : id(Id), name(Name)
{}

#if defined SOL_LOADTXT && defined SOL_COMPILER
void Alphabet::LoadTxt(lem::Iridium::Macro_Parser &txtfile, Dictionary &dict)
{
    return;
}
#endif
