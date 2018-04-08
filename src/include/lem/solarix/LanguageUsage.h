#if !defined LANGUAGE_USAGE__H
#define LANGUAGE_USAGE__H

#include <lem/process.h>
#include <lem/RWULock.h>
#include <lem/containers.h>

namespace Solarix
{
    class SynGram;
    class LexiconStorage;

    class LanguageUsage
    {
    private:
        SynGram *sg;
        LexiconStorage *storage;

#if defined LEM_THREADS
        lem::Process::CriticalSection cs_init;
        lem::Process::RWU_Lock cs;
#endif
        lem::zbool loaded;
        int id_default_input, id_default_output;
        lem::MCollect<int> id_langs, id_input_langs, id_output_langs;

        void Load();

    public:
        LanguageUsage(SynGram *SG);
        void Connect(LexiconStorage *Storage);

        int GetDefaultInputLanguage();
        int GetDefaultOutputLanguage();
        bool HasLanguage(int id_language);
        void GetLanguages(lem::MCollect<int> &ids);
        void GetInputLanguages(lem::MCollect<int> &ids);
        void GetOutputLanguages(lem::MCollect<int> &ids);
    };
}

#endif
