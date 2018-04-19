// -----------------------------------------------------------------------------
// File SG_FORM.CPP
//
// (c) Koziev Elijah
//
// Content:
// Класс SG_EntryForm. Грамматические формы описываются как комбинации лексема+
// список_состояний_координат. Класс SG_EntryForm хранит как текстовое
// представление словоформы статьи, так и вектор состояний. Парадигма слова -
// это список словарных статей.
// -----------------------------------------------------------------------------
//
// CD->12.10.1995
// LC->16.04.2018
// --------------

#include <lem/solarix/tokens.h>
#include <lem/solarix/ClassList.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/CoordList.h>

using namespace lem;
using namespace Solarix;


/*******************************************************************
 Если список измерений Dim содержит те же состояния координат, что
 и список словоформы, то возвращает true. При этом порядок координат
 в Dim роли не играет.
********************************************************************/
bool SG_EntryForm::is_equal_detailed(const CP_Array& Dim) const
{
    const int ndim = CastSizeToInt(Dim.size());

    for (int i = 0; i < ndim; i++)
    {
        const GramCoordPair Pair = Dim[i];
        const GramCoordAdr a1 = Pair.GetCoord();

        bool fixed = false;
        for (Container::size_type j = 0; j < dim->size(); j++)
        {
            const GramCoordPair pair = (*dim)[j];
            const GramCoordAdr a2 = pair.GetCoord();

            if (a1 == a2)
            {
                if (pair.GetState() == ANY_STATE || Pair.GetState() == ANY_STATE)
                {
                    fixed = true;
                    break;
                }

                if (pair.GetState() == Pair.GetState())
                {
                    fixed = true;
                    break;
                }
            }
        }

        if (!fixed)
            return false;
    }

    return true;
}



bool SG_EntryForm::does_match(const CP_Array& Dim) const
{
    const int ndim = CastSizeToInt(Dim.size());

    for (int i = 0; i < ndim; i++)
    {
        const GramCoordPair Pair = Dim[i];
        const GramCoordAdr a1 = Pair.GetCoord();

        bool fixed = false;
        for (Container::size_type j = 0; j < dim->size(); j++)
        {
            const GramCoordPair pair = (*dim)[j];
            const GramCoordAdr a2 = pair.GetCoord();

            if (a1 == a2)
            {
                if (pair.GetState() == ANY_STATE || Pair.GetState() == ANY_STATE)
                {
                    fixed = true;
                    break;
                }

                if (pair.GetState() == Pair.GetState())
                {
                    fixed = true;
                    break;
                }
            }
        }

        if (!fixed)
            return false;
    }

    return true;
}


int SG_EntryForm::count_matches(const CP_Array& Dim) const
{
    int count = 0;

    const int ndim = CastSizeToInt(Dim.size());

    for (int i = 0; i < ndim; i++)
    {
        const GramCoordPair Pair = Dim[i];
        const GramCoordAdr a1 = Pair.GetCoord();

        bool fixed = false;
        for (Container::size_type j = 0; j < dim->size(); j++)
        {
            const GramCoordPair pair = (*dim)[j];
            const GramCoordAdr a2 = pair.GetCoord();

            if (a1 == a2)
            {
                if (pair.GetState() == ANY_STATE || Pair.GetState() == ANY_STATE)
                {
                    fixed = true;
                    break;
                }

                if (pair.GetState() == Pair.GetState())
                {
                    fixed = true;
                    break;
                }
            }
        }

        if (fixed)
            count++;
    }

    return count;
}


// ****************************************************************************
// С учетом весов координат, возвращается суммарный вес соответствующих пар
// ****************************************************************************
int SG_EntryForm::count_matches(const CP_Array& Dim, const lem::MCollect<int>& weight) const
{
    int count = 0;

    const int ndim = CastSizeToInt(Dim.size());

    for (int i = 0; i < ndim; i++)
    {
        const GramCoordPair Pair = Dim[i];
        const GramCoordAdr a1 = Pair.GetCoord();

        bool fixed = false;
        for (Container::size_type j = 0; j < dim->size(); j++)
        {
            const GramCoordPair pair = (*dim)[j];
            const GramCoordAdr a2 = pair.GetCoord();

            if (a1 == a2)
            {
                if (pair.GetState() == ANY_STATE || Pair.GetState() == ANY_STATE)
                {
                    fixed = true;
                    break;
                }

                if (pair.GetState() == Pair.GetState())
                {
                    fixed = true;
                    break;
                }
            }
        }

        if (fixed)
            count += weight[i];
    }

    return count;
}


// *****************************************************************************
// Возвращает число координатных пар, совпадающих у списка формы и Dim.
// Если у списков есть координаты с несовпадающими состояниями, то возвращается
// 0.
// *****************************************************************************
int SG_EntryForm::get_equal_coords(const CP_Array& Dim) const
{
    int n = 0;

    const Container::size_type ndim = Dim.size();

    for (Container::size_type i = 0; i < ndim; i++)
    {
        const GramCoordPair Pair = Dim[i];
        const GramCoordAdr a1 = Pair.GetCoord();

        for (Container::size_type j = 0; j < dim->size(); j++)
        {
            const GramCoordPair pair = (*dim)[j];
            const GramCoordAdr a2 = pair.GetCoord();

            if (a1 == a2)
            {
                if (pair.GetState() == ANY_STATE || Pair.GetState() == ANY_STATE)
                    break;

                /*
                       if( pair.GetState()!=Pair.GetState() )
                        // Первое же несовпадение портит весь результат...
                        return 0;
                       n++;
                */
                // 15.01.2009 - из-за наличия "многоохватных" координат типа падежа для
                // глаголов или предлогов, будем искать именно совпадения. Несовпадение еще
                // не означает провал поиска.
                if (pair.GetState() == Pair.GetState())
                    n++;
            }
        }
    }

    return n;
}




#if defined SOL_SAVETXT
void SG_EntryForm::SaveTxt(
    OFormatter& txtfile,
    Grammar &gram,
    const SG_Entry &entry
) const
{
    const GramClass &c = gram.classes()[entry.GetClass()];
    txtfile.printf("  ");

    for (Container::size_type i = 0; i < coords().size(); i++)
    {
        const GramCoordPair cp = coords()[i];

        if (find(c.attrs(), cp.GetCoord()) != UNKNOWN)
            continue;

        const GramCoord& c = gram.coords()[cp.GetCoord().GetIndex()];
        const UCString& dim_name = c.GetName()[cp.GetCoord().GetVar()];

        if (!c.states().empty())
        {
            const UCString &state_name = c.GetStateName(cp.GetState());

            if (c.IsDefState(cp.GetState()) && c.IsHeadState(cp.GetState()))
                txtfile.printf(
                    "%us%us%us%us%us ",
                    dim_name.c_str(),
                    sol_get_token(B_COLON).c_str(),
                    sol_get_token(B_OROUNDPAREN).c_str(),
                    state_name.c_str(),
                    sol_get_token(B_CROUNDPAREN).c_str()
                );
            else
                txtfile.printf(
                    "%us%us%us ",
                    dim_name.c_str(),
                    sol_get_token(B_COLON).c_str(),
                    state_name.c_str()
                );
        }
        else
        {
            UCString prefix;

            if (!cp.GetState())
                prefix = sol_get_token(B_NEGATIVE);

            txtfile.printf("%us%us ", prefix.c_str(), dim_name.c_str());
        }
    }

    txtfile.printf(
        " %us %us %us\n",
        sol_get_token(B_OFIGPAREN).c_str(),
        content->c_str(),
        sol_get_token(B_CFIGPAREN).c_str()
    );
    return;
}
#endif


void SG_EntryForm::Reattach_To_Refs(SynGram &sg)
{
    // Название формы.
    content = sg.GetEntries().ReattachLexeme(content);

    // Координаты
    dim = sg.GetEntries().ReattachCoordPairs(dim);

    return;
}
