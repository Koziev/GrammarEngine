#if !defined PatternTemplate__H
#define PatternTemplate__H

#include <lem/noncopyable.h>
#include <lem/ptr_container.h>

namespace lem
{
    namespace Iridium
    {
        class Macro_Parser;
    }
}


namespace Solarix
{
    class Dictionary;
    class LexiconStorage;

    class PredicateTemplateParams : lem::NonCopyable
    {
    public:
        PredicateTemplateParams() {}
        virtual ~PredicateTemplateParams() {}
        virtual bool IsParam(const lem::UCString & probe) const = 0;
    };

    class PredicateTemplate
    {
    private:
        int id;
        lem::UFString src;
        lem::MCollect<lem::UCString> params;

    public:
        PredicateTemplate();
        PredicateTemplate(int id, const lem::UFString & _src, const lem::UFString & _params);

        PredicateTemplate(const PredicateTemplate & x);
        void operator=(const PredicateTemplate & x);

        bool operator==(const PredicateTemplate & x) const;
        bool operator!=(const PredicateTemplate & x) const;

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(Dictionary & dict, lem::Iridium::Macro_Parser & txtfile, const PredicateTemplateParams & param_list);
#endif

        const lem::UFString & GetSrc() const { return src; }
        const lem::MCollect<lem::UCString> & GetParams() { return params; }

        int Store(LexiconStorage * storage);
        void SaveBin(lem::Stream & bin) const;
        void LoadBin(lem::Stream & bin);
    };


    class PredicateTemplates
    {
    private:
        lem::PtrCollect<PredicateTemplate> predicates;

    public:
        PredicateTemplates() {}
        PredicateTemplates(const PredicateTemplates & x) : predicates(x.predicates) {}

        void operator=(const PredicateTemplates & x) { predicates = x.predicates; }

        bool operator==(const PredicateTemplates & x) const;
        bool operator!=(const PredicateTemplates & x) const;

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(Dictionary & dict, lem::Iridium::Macro_Parser & txtfile, const PredicateTemplateParams & param_list);
#endif

        void SaveBin(lem::Stream & bin) const;
        void LoadBin(lem::Stream & bin);
    };
}

#endif
