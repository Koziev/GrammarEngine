#include <lem/macro_parser.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/PredicateTemplate.h>

using namespace Solarix;

PredicateTemplate::PredicateTemplate() : id(UNKNOWN)
{
}

PredicateTemplate::PredicateTemplate(const PredicateTemplate & x) : id(x.id), src(x.src), params(x.params)
{}



PredicateTemplate::PredicateTemplate(int _id, const lem::UFString & _src, const lem::UFString & _params)
    : id(_id), src(_src)
{
    LEM_CHECKIT_Z(id != UNKNOWN);
    LEM_CHECKIT_Z(!src.empty());

    lem::parse(_params, params, false);

    return;
}



void PredicateTemplate::operator=(const PredicateTemplate & x)
{
    id = x.id;
    src = x.src;
    params = x.params;
}



bool PredicateTemplate::operator==(const PredicateTemplate & x) const
{
    return src == x.src && params == x.params;
}


bool PredicateTemplate::operator!=(const PredicateTemplate & x) const
{
    return src != x.src || params != x.params;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void PredicateTemplate::LoadTxt(Dictionary & dict, lem::Iridium::Macro_Parser & txtfile, const PredicateTemplateParams & param_list)
{
    int open_paren = 1; // инициализируем 1-цей, чтобы считать начало предиката вида xxx( ....

    while (!txtfile.eof())
    {
        lem::Iridium::BethToken t = txtfile.read();

        src += L' ';
        src += t.string().c_str();

        if (t == B_OROUNDPAREN)
            open_paren++;
        else if (t == B_CROUNDPAREN)
        {
            open_paren--;
            if (open_paren == 1)
                break;
        }
        else
        {
            if (param_list.IsParam(t.string()))
                params.push_back(t.string());
        }
    }

    return;
}
#endif



int PredicateTemplate::Store(LexiconStorage * storage)
{
    id = storage->StorePredicateTemplate(src, params);
    return id;
}


void PredicateTemplate::SaveBin(lem::Stream & bin) const
{
    src.SaveBin(bin);
    params.SaveBin(bin);
    return;
}


void PredicateTemplate::LoadBin(lem::Stream & bin)
{
    src.LoadBin(bin);
    params.LoadBin(bin);
    return;
}
