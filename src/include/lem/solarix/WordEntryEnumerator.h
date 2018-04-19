#if !defined WordEntryEnumerator__H
#define WordEntryEnumerator__H 

namespace Solarix
{
    class SG_Entry;
    class WordEntryEnumerator
    {
    public:
        WordEntryEnumerator() {}
        virtual ~WordEntryEnumerator() {}

        virtual bool Fetch() = 0;
        virtual int GetId() = 0;
        virtual const SG_Entry& GetItem() = 0;
    };

}

#endif
