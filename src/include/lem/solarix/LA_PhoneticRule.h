#if !defined LA_PHONETIC_RULE__H
#define LA_PHONETIC_RULE__H

#include <lem/noncopyable.h>
#include <lem/math/fp1.h>
#include <lem/ucstring.h>
#include <lem/solarix/lexem.h>

namespace Solarix
{

    /******************************************************************
     Часть продукционного/трансформационного правила для Лексического
     Алеф-Алгоритма: кондиктор, то есть условие применения правила.
    *******************************************************************/
    class GraphGram;
    class LA_PhoneticCondictor
    {
    public:
        typedef enum { PREFIX, AFFIX, UNLOCATED } LocType;

    private:
        LocType loc;
        lem::UCString context;

    public:
        LA_PhoneticCondictor();
        LA_PhoneticCondictor(const lem::UCString &str, bool IsPrefix, bool IsAffix);

#if defined SOL_LOADTXT && defined SOL_COMPILER
        LA_PhoneticCondictor(lem::Iridium::Macro_Parser &txtfile, GraphGram &gram);
#endif

#if defined SOL_CAA
        bool DoesMatch(const wchar_t *example) const;
        bool Can_Subst(const lem::UCString &lex) const;
#endif

        inline int length() const { return context.length(); }

        inline wchar_t single() const
        {
            LEM_CHECKIT_Z(context.length() == 1);
            return context.front();
        }

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(lem::Iridium::Macro_Parser &txtfile, GraphGram &gram);
        bool operator==(const LA_PhoneticCondictor& x) const;
#endif

        inline bool IsPrefix() const { return loc == PREFIX; }
        inline bool IsAffix() const { return loc == AFFIX; }
        inline bool IsUnlocated() const { return loc == UNLOCATED; }

        inline const lem::UCString& GetContext() const { return context; }
    };

    /******************************************************************
     Часть продукционного/трансформационного правила для Лесического
     Алеф-Алгоритма: актор, или результатная часть правила.
    *******************************************************************/
    class LA_PhoneticResult
    {
    private:
        Solarix::Lexem context;

    public:
        LA_PhoneticResult() {}
        LA_PhoneticResult(const lem::UCString &str);

#if defined SOL_LOADTXT && defined SOL_COMPILER
        LA_PhoneticResult(lem::Iridium::Macro_Parser &txtfile, Solarix::GraphGram &gram);
#endif

        inline const Solarix::Lexem& GetContext() const { return context; }
        inline int length() const { return context.length(); }

        inline wchar_t single() const
        {
            LEM_CHECKIT_Z(context.length() == 1);
            return context.front();
        }

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(lem::Iridium::Macro_Parser &txtfile, Solarix::GraphGram &gram);
        bool operator==(const LA_PhoneticResult& x) const;
#endif
    };



    /****************************************************************
     Правило продукции для программирования работы Фонетического
     Алеф-Алгоритма, являющегося частью Лексического Автомата.

     Для объектов класса действует соглашение о битовом копировании
     содержимого.
    *****************************************************************/
    class LA_PhoneticRule : lem::NonCopyable
    {
    private:
        int id;
        UCString name; // Имя правила - используется ТОЛЬКО для уведомления пользователя,
                       // сиречь программиста, о выполненных продукциях.
        int id_lang;   // целевой язык, для которого применимо правило

        lem::zbool is_prefix, is_affix;

        // Одно правило - одна продукция.
        LA_PhoneticCondictor head; // заголовок правила - в действительности это описание УСЛОВИЯ.
        LA_PhoneticResult    body; // тело правила - на самом деле это РЕЗУЛЬТАТНАЯ часть.
        lem::Real1 val;                 // Оценка достоверности преобразования

        int src_location;

    public:
        LA_PhoneticRule();
        LA_PhoneticRule(int Id, const lem::UCString &Name, int Id_Lang, bool IsPrefix,
            bool IsAffix, const lem::UCString &Condition, const lem::UCString &Result, lem::Real1 Rel, int SourceID);

        int GetId() const { return id; }
        void SetId(int _id) { id = _id; }

        int GetSourceLocation() const { return src_location; }

        inline const lem::UCString&        GetName() const { return name; }
        inline const LA_PhoneticCondictor& GetCondition() const { return head; }
        inline const LA_PhoneticResult&    GetResult() const { return body; }
        inline lem::Real1                  GetVal()  const { return val; }

        bool IsPrefix() const { return head.IsPrefix(); }
        bool IsAffix() const { return head.IsAffix(); }

        inline bool Is_1_to_1() const
        {
            return head.length() == 1 && body.length() == 1;
        }

        // Сколько опорных точек в условии правила.
        inline int GetnPoint() const { return head.length(); }

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(lem::Iridium::Macro_Parser &txtfile, GraphGram &gram);
#endif

#if defined SOL_CAA
        void Subst(const UCString &org, UCString &res) const;
#endif

        int GetHash() const;

        inline int GetLanguage() const { return id_lang; }
    };

}

#endif
