#include <lem/sol_io.h>
#include <lem/oformatter.h>
#include <lem/macro_parser.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/PartOfSpeechEnumerator.h>
#include <lem/solarix/PartsOfSpeech.h>

using namespace Solarix;


PartsOfSpeech::PartsOfSpeech(SynGram *_sg)
    : sg(_sg), db(nullptr)
{
}


void PartsOfSpeech::Connect(LexiconStorage *_db)
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


SG_Class* PartsOfSpeech::Get(int id)
{
    auto it = id2class.find(id);
    if (it != id2class.end())
    {
        return class_ptr[it->second];
    }

    // � ���� ����� � ��������� id �� ������, ������ � ��.
    SG_Class *new_class = new SG_Class();
    if (db->GetPartOfSpeech(id, *new_class))
    {
        const int index = CastSizeToInt(class_ptr.size());
        class_ptr.push_back(new_class);
        class_id.push_back(id);
        id2class.insert(std::make_pair(id, index));
        name2id.insert(std::make_pair(lem::to_upper(new_class->GetName()), id));
        for (lem::Container::size_type i = 0; i < new_class->GetAliases().size(); ++i)
        {
            name2id.insert(std::make_pair(lem::to_upper(new_class->GetAliases()[i]), id));
        }

        return new_class;
    }
    else
    {
        delete new_class;
        lem::UFString msg(lem::format_str(L"Can not find part of speech id=%d", id));
        throw lem::E_BaseException(msg);
    }
}


const GramClass& PartsOfSpeech::operator[](int id)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&cs);
#endif

    return *Get(id);
}

GramClass& PartsOfSpeech::GetClass(int id)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&cs);
#endif

    return *Get(id);
}


int PartsOfSpeech::Find(const UCString &name)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&cs);
#endif

    UCString uname(lem::to_upper(name));
    auto it = name2id.find(uname);
    if (it != name2id.end())
        return it->second;

    // ������ � ��
    const int id = db->FindPartOfSpeech(name);

    if (id != UNKNOWN)
        name2id.insert(std::make_pair(uname, id));

    return id;
}


int PartsOfSpeech::Count()
{
    return db->CountPartsOfSpeech();
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
GramClass* PartsOfSpeech::LoadTxt(
    lem::Iridium::Macro_Parser &txtfile,
    bool IsRealized
)
{
    LEM_CHECKIT_Z(db != nullptr);

#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&cs);
#endif

    const bool is_extern = !IsRealized;

    SG_Class *new_class = new SG_Class();
    new_class->LoadTxt(txtfile, *sg, IsRealized);

    const int id_class = Find(new_class->GetName());

    if (id_class == UNKNOWN)
    {
        AddNewClass(new_class, IsRealized);
        return new_class;
    }
    else
    {
        SG_Class *old_class = Get(id_class);

        if (is_extern && !old_class->IsRealized())
        {
            // �������� ����:
            //
            // extern class X
            //         :
            // extern class X

            if (*old_class != *new_class)
            {
                // �� ��������� ���������� ��� ������.
                lem::Iridium::Print_Error(txtfile);
                sg->GetIO().merr().printf(
                    "%vfDTwo classes have got the same name [%us].%vn\n"
                    , new_class->GetName().c_str()
                );
                throw lem::E_ParserError();
            }
            else
            {
                // ��������� ����������� ��������� �����������.
                delete new_class;
            }

            return nullptr;
        }

        if (!is_extern && !old_class->IsRealized())
        {
            // �������� ����:
            //
            // extern class X
            //         :
            // class X { ... }
            if (!old_class->IsEmpty() && *new_class != *old_class)
            {
                Print_Error(txtfile);
                sg->GetIO().merr().printf(
                    "%vfDTwo classes have got the same name [%us].%vn\n"
                    , new_class->GetName().c_str()
                );
                throw lem::E_ParserError();
            }
            else
            {
                // ���������� ���������� ������ ����������.
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
            // ��������:
            //
            //   class X { ... }
            //          :
            //   extern class X

            if (!new_class->IsEmpty() && *new_class != *old_class)
            {
                lem::Iridium::Print_Error(txtfile);
                sg->GetIO().merr().printf(
                    "%vfDTwo classes have got the same name [%us].%vn\n"
                    , new_class->GetName().c_str()
                );
                throw lem::E_ParserError();
            }

            delete new_class;
            return nullptr;
        }

        // ��������� ���������� ������.
        if (!is_extern && old_class->IsRealized())
        {
            sg->GetIO().merr().printf(
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
void PartsOfSpeech::AddNewClass(SG_Class *new_class, bool IsRealized)
{
    const int index = CastSizeToInt(class_ptr.size());

    const int id = IsRealized ? db->AddPartOfSpeech(*new_class) : db->AddPartOfSpeech(new_class->GetName());

    class_ptr.push_back(new_class);
    class_id.push_back(id);
    id2class.insert(std::make_pair(id, index));

    name2id.insert(std::make_pair(lem::to_upper(new_class->GetName()), id));
    for (lem::Container::size_type i = 0; i < new_class->GetAliases().size(); ++i)
    {
        name2id.insert(std::make_pair(lem::to_upper(new_class->GetAliases()[i]), id));
    }

    return;
}
#endif

ClassEnumerator* PartsOfSpeech::Enumerate()
{
    return new PartOfSpeechEnumerator(db, this);
}


