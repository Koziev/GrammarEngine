#if !defined WordEntryEnumerator_File__H
#define WordEntryEnumerator_File__H 

#include <lem/ucstring.h>
#include <lem/solarix/WordEntryEnumerator.h> 

namespace Solarix
{
    class WordEntries_File;
    class WordEntryEnumerator_File : public WordEntryEnumerator
    {
    private:
        WordEntries_File *entries;
        bool started, finished;
        int ifound;

        lem::UCString name;
        int id_class;

    public:
        WordEntryEnumerator_File(WordEntries_File *_entries);
        WordEntryEnumerator_File(WordEntries_File *_entries, const lem::UCString &_name, int id_class);

        virtual ~WordEntryEnumerator_File() {}

        virtual bool Fetch() override;
        virtual int GetId() override;
        virtual const SG_Entry& GetItem() override;
    };


    class SG_EntryGroup;
    class WordEntryEnumerator_File_ByGroup : public WordEntryEnumerator
    {
    private:
        WordEntries_File *entries;
        const SG_EntryGroup *group;
        int icur;
        bool finished;
        int N;

    public:
        WordEntryEnumerator_File_ByGroup(WordEntries_File *_entries, const SG_EntryGroup *_group);

        virtual ~WordEntryEnumerator_File_ByGroup() {}

        virtual bool Fetch() override;
        virtual int GetId() override;
        virtual const SG_Entry& GetItem() override;
    };
}

#endif
