#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/AuxFormTypes.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/ExactWordEntryLocator.h>

using namespace lem;
using namespace Solarix;

#if defined SOL_LOADTXT
void ExactWordEntryLocator::LoadAuxSelector(Macro_Parser &txtfile, SynGram &sg)
{
    aux_type = txtfile.read().string();
    if (aux_type.front() == L'"')
        aux_type.strip(L'"');
    else
        aux_type.strip(L'\'');

    txtfile.read_it(B_EQUAL);

    lem::Iridium::BethToken t = txtfile.read();

    aux_value = t.string();

    if (aux_value.front() == L'"')
        aux_value.strip(L'"');
    else
        aux_value.strip(L'\'');

    if (sg.GetAuxFormTypes()[aux_type] == UNKNOWN)
    {
        lem::Iridium::Print_Error(t, txtfile);
        sg.GetIO().merr().printf("Unknown aux form type %us\n", aux_type.c_str());
        throw E_ParserError();
    }

    return;
}
#endif


#if defined SOL_LOADTXT
// ��������� ������ ������������ ��� �� ������ } (������ ����� ����� ����)
void ExactWordEntryLocator::LoadTxt(Macro_Parser &txtfile, SynGram &sg)
{
    while (!txtfile.eof())
    {
        if (txtfile.probe(B_CFIGPAREN))
            break;

        if (txtfile.probe(L"aux"))
        {
            LoadAuxSelector(txtfile, sg);
        }
        else
        {
            Solarix::GramCoordPair p;
            p.LoadTxt(txtfile, sg);
            pairs.push_back(p);
        }
    }

    return;
}
#endif


void ExactWordEntryLocator::SaveBin(lem::Stream &bin) const
{
    pairs.SaveBin(bin);
    bin.write(&aux_type, sizeof(aux_type));
    bin.write(&aux_value, sizeof(aux_value));
    return;
}

void ExactWordEntryLocator::LoadBin(lem::Stream &bin)
{
    pairs.LoadBin(bin);
    bin.read(&aux_type, sizeof(aux_type));
    bin.read(&aux_value, sizeof(aux_value));
    return;
}

bool ExactWordEntryLocator::Empty() const
{
    return pairs.empty() && aux_type.empty() && aux_value.empty();
}



bool ExactWordEntryLocator::Check(const SG_Entry & e, SynGram & sg) const
{
    bool all = true;

    for (auto& pair : pairs)
    {
        IntCollect e_states = e.GetAttrStates(pair.GetCoord());
        if (e_states.find(pair.GetState()) == UNKNOWN)
        {
            if (pair.GetState() == 0 && sg.coords()[pair.GetCoord().GetIndex()].IsBistable())
            {
                // ������ ��������� 0 ������������ ����������, ��� ����������� ��������, ��� ����� ���������� ������ ��� � ������ ��� ������.
                if (e_states.empty())
                    continue;
            }

            all = false;
            break;
        }
    }

    if (all && HasAuxSelector())
    {
        all = false;
        const int aux_type_id = sg.GetAuxFormTypes()[aux_type];
        if (aux_type_id == UNKNOWN)
        {
            lem::MemFormatter mem;
            mem.printf("Unknown aux type [%us]", aux_type.c_str());
            throw E_BaseException(mem.string());
        }

        lem::UFString aux_data;
        int aux_id = sg.GetStorage().GetAuxEntryData(e.GetKey(), aux_type_id, aux_data);
        if (aux_id != UNKNOWN && aux_data == aux_value.c_str())
        {
            all = true;
        }
    }

    return all;
}


void ExactWordEntryLocator::Print(lem::OFormatter & to, SynGram & sg) const
{
    for (auto &pair : pairs)
    {
        to.printf(" ");
        pair.SaveTxt(to, sg);
    }

    if (!aux_type.empty())
    {
        to.printf(" aux %us", aux_type.c_str());
    }

    return;
}
