#include <lem/oformatter.h>
#include <lem/macro_parser.h>
#include <lem/solarix/gram_class.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/AlphabetStorage.h>
#include <lem/solarix/SymbolClasses.h>
#include <lem/solarix/SymbolClassEnumerator.h>

using namespace Solarix;


SymbolClasses::SymbolClasses(GraphGram *_gg)
    : gg(_gg), db(nullptr)
{
}


void SymbolClasses::Connect(AlphabetStorage *_db)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&cs);
#endif

    class_ptr.clear();
    class_id.clear();
    id2class.clear();
    name2id.clear();

    LEM_CHECKIT_Z(_db != nullptr);
    db = _db;
    return;
}


GramClass* SymbolClasses::Get(int id)
{
    auto it = id2class.find(id);
    if (it != id2class.end())
    {
        return class_ptr[it->second];
    }

    // в кэше класс с указанным id не найден, поищем в БД.
    GramClass *new_class = new GramClass();
    if (db->GetClass(id, *new_class))
    {
        const int index = CastSizeToInt(class_ptr.size());
        class_ptr.push_back(new_class);
        class_id.push_back(id);
        id2class.insert(std::make_pair(id, index));
        name2id.insert(std::make_pair(lem::to_upper(new_class->GetName()), id));
        for (lem::Container::size_type i = 0; i < new_class->GetAliases().size(); ++i)
            name2id.insert(std::make_pair(lem::to_upper(new_class->GetAliases()[i]), id));

        return new_class;
    }
    else
    {
        delete new_class;
        lem::UFString msg(lem::format_str(L"Can not find symbol class id=%d", id));
        throw lem::E_BaseException(msg);
    }
}


const GramClass& SymbolClasses::operator[](int id)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&cs);
#endif

    return *Get(id);
}

GramClass& SymbolClasses::GetClass(int id)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&cs);
#endif

    return *Get(id);
}


int SymbolClasses::Find(const UCString &name)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&cs);
#endif

    UCString uname(lem::to_upper(name));
    auto it = name2id.find(uname);
    if (it != name2id.end())
        return it->second;

    // поищем в БД
    const int id = db->FindClass(name);

    if (id != UNKNOWN)
        name2id.insert(std::make_pair(uname, id));

    return id;
}


int SymbolClasses::Count(void)
{
    return db->CountClasses();
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
GramClass* SymbolClasses::LoadTxt(
    lem::Iridium::Macro_Parser &txtfile,
    bool IsRealized
)
{
    LEM_CHECKIT_Z(db != nullptr);

#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&cs);
#endif

    const bool is_extern = !IsRealized;

    GramClass *new_class = new GramClass();
    new_class->LoadTxt(txtfile, *gg, IsRealized);

    const int id_class = Find(new_class->GetName());

    if (id_class == UNKNOWN)
    {
        AddNewClass(new_class, IsRealized);
        return new_class;
    }
    else
    {
        GramClass *old_class = Get(id_class);

        if (is_extern && !old_class->IsRealized())
        {
            // Фрагмент типа:
            //
            // extern class X
            //         :
            // extern class X

            if (*old_class != *new_class)
            {
                // Не совпадают объявления для класса.
                lem::Iridium::Print_Error(txtfile);
                gg->GetIO().merr().printf(
                    "%vfDTwo classes have got the same name [%us].%vn\n"
                    , new_class->GetName().c_str()
                );
                throw lem::E_ParserError();
            }
            else
            {
                // повторное определение идентично предыдущему.
                delete new_class;
            }

            return nullptr;
        }

        if (!is_extern && !old_class->IsRealized())
        {
            // Фрагмент типа:
            //
            // extern class X
            //         :
            // class X { ... }
            if (!old_class->IsEmpty() && *new_class != *old_class)
            {
                Print_Error(txtfile);
                gg->GetIO().merr().printf(
                    "%vfDTwo classes have got the same name [%us].%vn\n"
                    , new_class->GetName().c_str()
                );
                throw lem::E_ParserError();
            }
            else
            {
                // Запоминаем реализацию вместо объявления.
                for (lem::Container::size_type i = 0; i < class_ptr.size(); ++i)
                {
                    if (class_ptr[i] == old_class)
                    {
                        delete class_ptr[i];
                        class_ptr[i] = new_class;
                        break;
                    }
                }
            }

            return nullptr;
        }

        if (is_extern && old_class->IsRealized())
        {
            // Фрагмент:
            //
            //   class X { ... }
            //          :
            //   extern class X

            if (!new_class->IsEmpty() && *new_class != *old_class)
            {
                lem::Iridium::Print_Error(txtfile);
                gg->GetIO().merr().printf(
                    "%vfDTwo classes have got the same name [%us].%vn\n"
                    , new_class->GetName().c_str()
                );
                throw lem::E_ParserError();
            }

            delete new_class;
            return nullptr;
        }

        // Повторная реализация класса.
        if (!is_extern && old_class->IsRealized())
        {
            gg->GetIO().merr().printf(
                "%vfDTwo classes have got the same name [%us].%vn\n"
                , new_class->GetName().c_str()
            );
            lem::Iridium::Print_Error(txtfile);
            throw lem::E_ParserError();
        }
    }

    delete new_class;
    return nullptr;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SymbolClasses::AddNewClass(GramClass *new_class, bool IsRealized)
{
    const int index = CastSizeToInt(class_ptr.size());

    const int id = IsRealized ? db->AddClass(*new_class) : db->AddClass(new_class->GetName());

    class_ptr.push_back(new_class);
    class_id.push_back(id);
    id2class.insert(std::make_pair(id, index));

    name2id.insert(std::make_pair(lem::to_upper(new_class->GetName()), id));

    return;
}
#endif

ClassEnumerator* SymbolClasses::Enumerate(void)
{
    return new SymbolClassEnumerator(db, gg);
}
