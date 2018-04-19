// -----------------------------------------------------------------------------
// File SG_CLASS.CPP
//
// (c) by Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
//
// SG_Class - специализация грамматического класса для лексикона.
//
// 08.07.2009 - добавлено поле value=n для задания ценности класса
// 23.01.2013 - добавлено поле closed для пометки тех частей речи, которые не
//              должны создавать правила распознавания по окончанию.
// -----------------------------------------------------------------------------
//
// CD->06.03.1996
// LC->08.04.2018
// --------------

#include <lem/config.h>
#include <lem/conversions.h>
#include <lem/sol_io.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/AuxFormTypes.h>
#include <lem/solarix/PartOfSpeech.h>

using namespace std;
using namespace lem;
using namespace Solarix;


SG_Class::SG_Class()
    : GramClass()
{
    id_lang = UNKNOWN;
    value = 10;
    closed_class = false;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
// **********************************************************
// Для грамматических классов в лексиконе есть дополнительное
// поле language XXX
// **********************************************************
bool SG_Class::Load_Private_Data(
    const BethToken &t,
    Macro_Parser &txtfile,
    Grammar& gram
)
{
    if (t.GetToken() == B_LANGUAGE)
    {
        BethToken lang_name = txtfile.read();

        id_lang = static_cast<SynGram&>(gram).Find_Language(lang_name.string());

        if (id_lang == UNKNOWN)
        {
            lem::Iridium::Print_Error(lang_name, txtfile);
            gram.GetIO().merr().printf(
                "Unknown language [%us] is specified for class [%us]\n"
                , lang_name.string().c_str()
                , GetName().c_str()
            );
            throw E_ParserError();
        }

        return true;
    }

    if (t.GetToken() == B_IMPORT)
    {
        LoadImport(txtfile, gram);
        return true;
    }

    if (t.GetToken() == B_VALUE)
    {
        txtfile.read_it(B_EQUAL);
        BSourceState s = txtfile.tellp();
        value = txtfile.read_int();
        if (value < 0 || value>10)
        {
            lem::Iridium::Print_Error(s, txtfile);
            gram.GetIO().merr().printf(
                "Invalid value [%d] for class [%us], must be in range 0 to 10\n"
                , value
                , GetName().c_str()
            );
            throw E_ParserError();
        }

        return true;
    }

    if (t.string().eqi(L"closed"))
    {
        closed_class = true;
        return true;
    }

    return false;
}
#endif

#if defined SOL_SAVETXT
void SG_Class::Save_Private_Txt(
    OFormatter& txtfile,
    const Grammar& gram
) const
{
    if (id_lang != UNKNOWN)
        txtfile.printf(
            " %us %us\n"
            , sol_get_token(B_LANGUAGE).c_str()
            , static_cast<const SynGram&>(gram).languages()[id_lang].GetName().c_str()
        );
}
#endif


#if defined SOL_LOADBIN
void SG_Class::LoadBin(lem::Stream &bin)
{
    GramClass::LoadBin(bin);
    bin.rd(&id_lang);
    bin.read(&value, sizeof(value));
    closed_class = bin.read_bool();

#if LEM_DEBUGGING==1
    bin.Check();
#endif

    return;
}
#endif

#if defined SOL_SAVEBIN
void SG_Class::SaveBin(lem::Stream &bin) const
{
    GramClass::SaveBin(bin);
    bin.wr(&id_lang);
    bin.write(&value, sizeof(value));
    bin.write_bool(closed_class);

#if LEM_DEBUGGING==1
    bin.Check();
#endif

    return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SG_Class::LoadImport(Macro_Parser &txtfile, Grammar& gram)
{
    txtfile.read_it(B_OFIGPAREN);

    while (!txtfile.eof())
    {
        BethToken coord_name = txtfile.read();
        if (coord_name.GetToken() == B_CFIGPAREN)
            break;

        Solarix::GramCoordAdr icoord = gram.FindCoord(coord_name);

        if (!icoord.IsDefined())
        {
            Print_Error(coord_name, txtfile);
            gram.GetIO().merr().printf(
                "%vfDThe coordinate [%us] is not previously declared in grammar%vn\n"
                , coord_name.c_str()
            );
            throw E_ParserError();
        }

        txtfile.read_it(B_FROM);

        BethToken class_name = txtfile.read();

        int iclass = gram.FindClass(class_name);
        if (iclass == UNKNOWN)
        {
            Print_Error(class_name, txtfile);
            gram.GetIO().merr().printf(
                "%vfDThe class [%us] is not previously declared in grammar%vn\n"
                , class_name.c_str()
            );
            throw E_ParserError();
        }

        if (import_coord.find(icoord) != UNKNOWN)
        {
            Print_Error(coord_name, txtfile);
            gram.GetIO().merr().printf(
                "%vfDThe coordinate [%us] is already defined as importable%vn\n"
                , coord_name.c_str()
            );
            throw E_ParserError();
        }

        ImportFiltrerCoords * filt = new ImportFiltrerCoords();

        if (txtfile.probe(B_OFIGPAREN))
        {
            while (!txtfile.eof())
            {
                if (txtfile.probe(B_CFIGPAREN))
                    break;

                BethToken coord_name = txtfile.read();

                if (coord_name.eqi(L"aux"))
                {
                    if (filt->aux_type != UNKNOWN)
                    {
                        Print_Error(coord_name, txtfile);
                        gram.GetIO().merr().printf("%vfDOnly one AUX is allowed%vn\n");
                        throw E_ParserError();
                    }
                    else
                    {
                        lem::Iridium::BSourceState token_aux = txtfile.tellp();
                        lem::UCString aux_type = txtfile.read().string();
                        if (aux_type.front() == L'"')
                            aux_type.strip_quotes();
                        else if (aux_type.front() == L'\'')
                            aux_type.strip_apostrophes();

                        filt->aux_type_str = aux_type;
                        filt->aux_type = static_cast<SynGram&>(gram).GetAuxFormTypes()[aux_type];

                        if (filt->aux_type == UNKNOWN)
                        {
                            lem::Iridium::Print_Error(token_aux, txtfile);
                            gram.GetIO().merr().printf("Unknown aux form type %us\n", aux_type.c_str());
                            throw E_ParserError();
                        }
                    }
                }
                else
                {
                    Solarix::GramCoordAdr icoord = gram.FindCoord(coord_name);

                    if (!icoord.IsDefined())
                    {
                        Print_Error(coord_name, txtfile);
                        gram.GetIO().merr().printf(
                            "%vfDThe coordinate [%us] is not previously declared in grammar%vn\n"
                            , coord_name.c_str()
                        );
                        throw E_ParserError();
                    }

                    filt->coords.push_back(icoord);
                }
            }
        }

        import_coord.push_back(icoord);
        import_class.push_back(iclass);
        import_filters.push_back(filt);
    }

    return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
bool SG_Class::IsImportableAttribute(const GramCoordAdr &coord) const
{
    return import_coord.find(coord) != UNKNOWN;
}
#endif
