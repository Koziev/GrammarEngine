#include <lem/oformatter.h>
#include <lem/solarix/ThesaurusStorage.h>
#include <lem/solarix/ThesaurusTagDefs.h>

using namespace Solarix;


ThesaurusTagDefs::ThesaurusTagDefs() :db(nullptr)
{
}


ThesaurusTagDefs::~ThesaurusTagDefs()
{
}


void ThesaurusTagDefs::Connect(ThesaurusStorage *_db)
{
    LEM_CHECKIT_Z(_db != NULL);

#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs);
#endif

    id2tag.clear();
    ptrs.clear();
    db = _db;
    return;
}


ThesaurusTagDefsEnumerator* ThesaurusTagDefs::Enumerate()
{
    return new ThesaurusTagDefsEnumerator(this);
}


const ThesaurusTag& ThesaurusTagDefs::operator[](int id_tag)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs);
#endif

    LEM_CHECKIT_Z(id_tag != UNKNOWN);
    auto it = id2tag.find(id_tag);
    if (it == id2tag.end())
    {
        // загрузим определение тега с заданным id из БД.
        ThesaurusTag *tag = new ThesaurusTag(id_tag, db);
        ptrs.push_back(tag);
        id2tag.insert(std::make_pair(id_tag, tag));
        return *tag;
    }
    else
    {
        return *it->second;
    }
}

int ThesaurusTagDefs::Find(const lem::UCString & tag_name)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs);
#endif

    for (lem::Container::size_type i = 0; i < ptrs.size(); ++i)
    {
        if (ptrs[i]->GetName().eqi(tag_name))
            return ptrs[i]->GetId();
    }

    if (db == nullptr)
        throw lem::E_BaseException("thesaurus is not available");

    int id_tag = db->GetTagId(tag_name);
    return id_tag;
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
void ThesaurusTagDefs::LoadTxt(
    lem::Iridium::Macro_Parser & txtfile,
    const lem::Sol_IO &io,
    const Binarization_Options & options
)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs);
#endif

    ThesaurusTag *tag = new ThesaurusTag();
    tag->LoadTxt(txtfile, io, options);
    tag->Store(db);
    ptrs.push_back(tag);
    id2tag.insert(std::make_pair(tag->GetId(), tag));
    return;
}
#endif

#if defined SOL_REPORT
void ThesaurusTagDefs::Save_SQL(lem::OFormatter &out, const SQL_Production &sql_version)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs);
#endif

    for (lem::Container::size_type i = 0; i < ptrs.size(); ++i)
    {
        ptrs[i]->Save_SQL(out, sql_version);
        out.eol();
    }

    return;
}
#endif
