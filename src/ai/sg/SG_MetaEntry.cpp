#include <lem/macro_parser.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/MetaEntry.h>
#include <lem/solarix/sql_production.h>
#include <lem/solarix/LexiconStorage.h>

using namespace Solarix;

MetaEntry::MetaEntry() : id(UNKNOWN), id_class(UNKNOWN)
{}

MetaEntry::MetaEntry(int _id, int _id_class, const lem::UCString &_name, lem::MCollect<int> & _entries)
    : id(_id), id_class(_id_class), name(_name), entries(_entries)
{
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void MetaEntry::LoadTxt(SynGram & sg, lem::Iridium::Macro_Parser & txtfile)
{
    /* Общий формат объявления группы:

       entry_group имя_группы : класс
       {
        часть_речи:имя_статьи1{}
        часть_речи:имя_статьи2{}
        ...
       }
    */


    Solarix::Lexem lname = Solarix::sol_read_multyname(sg.GetIO(), txtfile, B_COLON);


    lem::Iridium::BethToken t_pos = txtfile.read();
    id_class = sg.FindClass(t_pos.string().c_str());
    if (id_class == UNKNOWN)
    {
        lem::Iridium::Print_Error(t_pos, txtfile);
        sg.GetIO().merr().printf(
            "Part of speech [%vfE%us%vn] is not previously declared in grammar\n"
            , t_pos.string().c_str()
        );
        throw lem::E_ParserError();
    }


    txtfile.read_it(B_OFIGPAREN);

    const int id_language = sg.GetClass(id_class).GetLanguage();
    sg.GetDict().GetLexAuto().TranslateLexem(lname, true, id_language);
    name = lname;

    while (!txtfile.eof())
    {
        if (txtfile.probe(B_CFIGPAREN))
            break;

        lem::Iridium::BethToken t_pos2 = txtfile.read();
        const int id_class2 = sg.FindClass(t_pos2.string());
        if ((id_class2) == UNKNOWN)
        {
            lem::Iridium::Print_Error(t_pos2, txtfile);

            sg.GetIO().merr().printf(
                "Part of speech [%vfE%us%vn] is not previously declared in grammar\n"
                , t_pos2.string().c_str()
            );

            throw lem::E_ParserError();
        }

        txtfile.read_it(B_COLON);
        lem::Iridium::BSourceState ebeg = txtfile.tellp();
        Solarix::Lexem ename = sol_read_multyname(sg.GetIO(), txtfile, B_OFIGPAREN);
        CP_Array coords;

        // Считываем список уточняющих координат
        while (!txtfile.eof())
        {
            if (txtfile.pick().GetToken() == B_CFIGPAREN)
            {
                txtfile.read();
                break;
            }

            // для обычных: координата:состояние
            // для бистабильных: координата
            // для согласования с координатами в именованных точках слева =имя_точки:координата
            lem::Iridium::BethToken coord_name = txtfile.read();

            const GramCoordAdr iglob_coord = sg.FindCoord(coord_name.string());

            if (!iglob_coord.IsDefined())
            {
                sg.GetIO().merr().printf("Unknown coordinate %us\n", coord_name.c_str());
                lem::Iridium::Print_Error(coord_name, txtfile);
                throw lem::E_BaseException();
            }

            if (sg.coords()[iglob_coord.GetIndex()].IsBistable())
            {
                // Имя состояния не может быть указано.
                coords.push_back(GramCoordPair(iglob_coord, 1));
            }
            else
            {
                // После двоеточия должно идти имя состояния для координаты.
                txtfile.read_it(B_COLON);

                // Имя состояния.
                BethToken state_name = txtfile.read();

                // Получим индекс состояния для определенной координаты.
                const int istate = sg.coords()[iglob_coord.GetIndex()]
                    .FindState(state_name.string());
                if (istate == UNKNOWN)
                {
                    // Нет такого состояния для этого измерения.
                    lem::Iridium::Print_Error(state_name, txtfile);
                    sg.GetIO().merr().printf(
                        "State [%vfE%us%vn] is not declared for coordinate [%vfE%us%vn]\n"
                        , state_name.c_str(), coord_name.c_str()
                    );
                    throw E_ParserError();
                }

                coords.push_back(GramCoordPair(iglob_coord, istate));
            }
        }


        sg.GetDict().GetLexAuto().TranslateLexem(ename, true, id_language);

        int ekey = UNKNOWN;

        if (sg.IsOmonym(id_class2, ename))
        {
            // есть омонимы, поэтому надо тщательно проверять.
            lem::MCollect<int> ies;
            sg.FindEntries(ename, ies);

            int icur = 0;
            while (icur < CastSizeToInt(ies.size()))
            {
                const int ekey = ies[icur];
                const SG_Entry &e = sg.GetEntry(ekey);
                if (e.GetClass() != id_class2)
                {
                    ies.Remove(icur);
                    continue;
                }
                else
                {
                    bool match = true;
                    for (lem::Container::size_type k = 0; k < coords.size(); ++k)
                    {
                        if (e.attrs().FindOnce(coords[k]) == UNKNOWN)
                        {
                            match = false;
                            break;
                        }
                    }

                    if (!match)
                    {
                        ies.Remove(icur);
                        continue;
                    }
                    else
                    {
                        icur++;
                    }
                }
            }

            if (ies.empty())
            {
                lem::Iridium::Print_Error(t_pos2, txtfile);
                sg.GetIO().merr().printf("There is no entry matching the specification %us:%us\n", t_pos2.string().c_str(), ename.c_str());
                throw lem::E_BaseException();
            }

            if (ies.size() > 1)
            {
                lem::Iridium::Print_Error(t_pos2, txtfile);
                sg.GetIO().merr().printf("There are %d alternatives for word entry %us:%us\n", CastSizeToInt(ies.size()), t_pos2.string().c_str(), ename.c_str());
                throw lem::E_BaseException();
            }

            ekey = ies.front();
        }
        else
        {
            // так как омонимов нет, то можем использовать быстрый поиск словарной статьи по имени и части речи.
            ekey = sg.FindEntry(ename, id_class2, false);

            if (lem::is_quantor(ekey))
            {
                lem::Iridium::Print_Error(t_pos2, txtfile);
                sg.GetIO().merr().printf("Word entry %us:%us is not found\n", t_pos2.string().c_str(), ename.c_str());
                throw lem::E_BaseException();
            }
        }

        if (entries.find(ekey) != UNKNOWN)
        {
            lem::Iridium::Print_Error(t_pos2, txtfile);
            sg.GetIO().merr().printf("Entry %us:%us (%d) is already added to metaentry [%us]:", t_pos2.string().c_str(), ename.c_str(), ekey, name.c_str());

            for (lem::Container::size_type i = 0; i < entries.size(); ++i)
            {
                const SG_Entry & e = sg.GetEntry(entries[i]);
                sg.GetIO().merr().printf(" [%us](%d)", e.GetName().c_str(), entries[i]);
            }

            sg.GetIO().merr().eol();

            throw lem::E_BaseException();
        }

        entries.push_back(ekey);
    }

    return;
}
#endif


void MetaEntry::Store(LexiconStorage * storage) const
{
    if (storage->FindMetaEntry(name, id_class) != UNKNOWN)
    {
        lem::MemFormatter msg;
        msg.printf("Meta entry %us is already added\n", name.c_str());
        throw lem::E_BaseException(msg.string());
    }

    storage->StoreMetaEntry(name, id_class, entries);
    return;
}


#if defined SOL_REPORT
void MetaEntry::SaveSQL(int * metaentry_item_id, lem::OFormatter & out, const SQL_Production &sql_version) const
{
    UFString name_str = sql_version.SqlStr(name);

    out.printf("INSERT INTO metaentry( id, id_class, name ) VALUES ( %d, %d, '%us' );\n",
        id, id_class, name_str.c_str());

    for (lem::Container::size_type i = 0; i < entries.size(); ++i)
    {
        out.printf("INSERT INTO metaentry_item( id, id_metaentry, id_entry ) VALUES (%d,%d,%d);\n", (*metaentry_item_id)++, id, entries[i]);
    }

    return;
}
#endif
