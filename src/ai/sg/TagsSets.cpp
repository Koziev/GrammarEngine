#include <lem/conversions.h>
#include <lem/solarix/ThesaurusStorage.h>
#include <lem/solarix/TagSets.h>

using namespace Solarix;

TagSets::TagSets(void) :db(nullptr)
{}


void TagSets::Connect(ThesaurusStorage *_db)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs);
#endif

    tag_ptr.clear();
    id2tags.clear();

    lem::MCollect< std::pair<int, int> > * empty_set = new lem::MCollect< std::pair<int, int> >();
    tag_ptr.push_back(empty_set);
    tagset_id.push_back(0);
    id2tags.insert(std::make_pair(0, empty_set));

    db = _db;

    return;
}

int TagSets::operator[](SG_TagsList tags)
{
    if (tags == nullptr)
        return 0;

#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs);
#endif

    for (lem::Container::size_type i = 0; i < tag_ptr.size(); ++i)
    {
        if (tag_ptr[i] == tags)
            return tagset_id[i];
    }

    return UNKNOWN;
}


// Ищем в справочнике набор тегов, заданный списком tags. При необходимости
// вносим в БД новую запись. Возвращается ID найденной или созданной записи.
int TagSets::Register(const lem::MCollect< std::pair<int, int> > &tags)
{
    if (tags.empty())
    {
        return 0;
    }

#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs);
#endif

    // Для устранения вариантов записи одного и того же набора тегов отсортируем элементы по id_tag.
    lem::MCollect< std::pair<int, int> > *sorted_tags = new lem::MCollect< std::pair<int, int> >(tags);
    std::sort(sorted_tags->begin(), sorted_tags->end(), [](const std::pair<int,int> &a, const std::pair<int,int> &b)
    {
        return a.first > b.first;
    });

    // Такой кортеж есть?
    const int i = tag_ptr.find(*sorted_tags);

    if (i == UNKNOWN)
    {
        // Нет.
        // Поищем в БД.
        lem::UFString s;
        if (tags.size() == 1)
        {
            s = lem::format_str(L"%d %d", tags.front().first, tags.front().second);
        }
        else if (tags.size() == 2)
        {
            s = lem::format_str(L"%d %d %d %d", sorted_tags->get(0).first, sorted_tags->get(0).second, sorted_tags->get(1).first, sorted_tags->get(1).second);
        }
        else
        {
            for (lem::Container::size_type i = 0; i < sorted_tags->size(); ++i)
            {
                if (i > 0) s += L' ';
                s += lem::format_str(L"%d %d", sorted_tags->get(i).first, sorted_tags->get(i).second);
            }
        }

        const int id = db->AddTagSet(s);

        id2tags.insert(std::make_pair(id, sorted_tags));
        tag_ptr.push_back(sorted_tags);
        tagset_id.push_back(id);

        return id;
    }
    else
    {
        delete sorted_tags;
        return tagset_id[i];
    }
}




SG_TagsList TagSets::operator[](int id)
{
    if (id == 0)
        return nullptr;

#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs);
#endif

    std::map<int, SG_TagsList>::const_iterator it = id2tags.find(id);
    if (it == id2tags.end())
    {
        lem::UFString s;
        db->GetTagSet(id, s);

        lem::Collect<lem::UFString> vals;
        lem::parse(s, vals, L" ");
        lem::MCollect< std::pair<int, int> > *lst = new lem::MCollect< std::pair<int, int> >();
        for (lem::Container::size_type i = 0; i < vals.size(); i += 2)
        {
            const int id_tag = lem::to_int(vals[i]);
            const int ivalue = lem::to_int(vals[i + 1]);
            lst->push_back(std::make_pair(id_tag, ivalue));
        }

        tag_ptr.push_back(lst);
        tagset_id.push_back(id);
        id2tags.insert(std::make_pair(id, lst));
        return lst;
    }
    else
    {
        return it->second;
    }
}
