#if !defined ParadigmaForm__H
#define ParadigmaForm__H

#include <lem/config.h>

#if !defined FAIND_NO_BOOST_REGEX
#include <boost/regex.hpp>
#endif

namespace Solarix
{
    class SG_DeclensionTable;
    class SG_DeclensionForm
    {
    private:
        CP_Array dim; // Список координатных пар измерений.
        Lexem form;   // Строка-команда для Автомата Склонений.

        bool valid_condition, valid_flexer_flags; // к сожалению, wregex выдает исключение при вызове empty() для неинициализированного объекта.
        lem::UFString condition_str, flexer_flags_str;
        boost::wregex condition, flexer_flags;

        void Init(const SG_DeclensionForm &df);

        void Check() const;

    public:
        SG_DeclensionForm();
        SG_DeclensionForm(const SG_DeclensionForm &df);
        SG_DeclensionForm(const CP_Array &Dim, const lem::UCString &Command);
        SG_DeclensionForm(
            const lem::UFString & lexem_generator,
            const lem::UFString & rx_condition,
            const lem::UFString & flexer_flags,
            const CP_Array & dims
        );

        void operator=(const SG_DeclensionForm &df);

        void Translate(int id_class, const GraphGram &gram);

        inline const Lexem& GetContent() const { return form; }
        inline const CP_Array& GetDim() const { return dim; }
        const lem::UCString& GetLexemGenerator() const { return form; }
        const lem::UFString& GetConditionStr() const { return condition_str; }
        const lem::UFString& GetFlexerFlagsStr() const { return flexer_flags_str; }

        bool MatchCondition(const UCString &str, const UFString &flexer_flags) const;

        void ReadAdditionalInfo(Grammar &gram, const SG_DeclensionTable &table, Macro_Parser& txtfile);
    };

}
#endif

