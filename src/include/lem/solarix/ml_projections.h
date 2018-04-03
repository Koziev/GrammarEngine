#ifndef ML_PROJECTIONS__H
#define ML_PROJECTIONS__H
#pragma once

#include <lem/solarix/form_table.h>
#include <lem/solarix/word_form.h>
#include <lem/solarix/LA_ProjectInfo.h>
#include <lem/solarix/TokenizationTags.h>
#include <lem/solarix/ProjScore.h>

namespace Solarix
{
    using lem::Real1;
    using lem::IntCollect;
    using lem::MCollect;
    using lem::Collect;

    class Res_Pack;

#if defined SOL_CAA
    class ML_SliceItem
    {
    private:
        int job_index;  // Индекс задания на проекцию в списке фразоблока.
        Real1 val;      // Достоверность элемента.
        int ipos;       // Начальная позиция в исходном предложении.

    public:
        ML_SliceItem() { job_index = UNKNOWN; ipos = UNKNOWN; }

        ML_SliceItem(int iJob, Real1 Val, int Pos)
        {
            job_index = iJob; val = Val; ipos = Pos;
        }

        inline Real1 GetVal() const { return val; }
        inline int GetJobIndex() const { return job_index; }
        inline int GetOriginPos() const { return ipos; }
    };
#endif

    enum { SOL_DO_MIX_VARIATORS, SOL_DO_PACK_VARIATORS };

#if defined SOL_CAA
    struct Mixer_Config
    {
        lem::int64_t NTOT; // Общее число различных конфигураций.
        int iSCAN;         // Счетчик для перебора конфигураций.
        IntCollect TOP;    // Пределы изменения для субиндексов.
        IntCollect INDEX;  // Супериндекс.
        int Scheme;        // Схема генерации вариаторов: SOL_DO_xxx_VARIATORS

        Mixer_Config()
        {
            NTOT = iSCAN = 0;
            Scheme = UNKNOWN;
            return;
        }

        inline bool IsNotExhausted() const
        {
            return (Scheme == SOL_DO_MIX_VARIATORS) && iSCAN < NTOT;
        }
    };
#endif

#if defined SOL_CAA
    struct ML_Slice : public MCollect<ML_SliceItem>
    {
        Mixer_Config CONFIG;

        ML_Slice() :MCollect<ML_SliceItem>() {}
        ML_Slice(const ML_Slice &x) :MCollect<ML_SliceItem>(x), CONFIG(x.CONFIG) {}

        inline void operator=(const ML_Slice &x)
        {
            MCollect<ML_SliceItem>::operator=(x);
            CONFIG = x.CONFIG;
            return;
        }
    };
#endif



#if defined SOL_CAA
    class MLProjJob
    {
    private:
        Real1 val;        // Оценка достоверности мультилексемы.
        int ijob;         // Индекс задания на проекцию.
        int pos;          // Начальная позиция первой лексемы.

        // Самый частый случай - слово задано своим лексическим содержанием.
        RC_Lexem ml; // Собственно проецируемая мультилексема.
        UCString org_word; // исходный вид слова, в оригинальном регистре

    public:
        MLProjJob();

        MLProjJob(const MLProjJob &x);

        MLProjJob(
            int Pos,
            const RC_Lexem &Ml,
            const UCString &Org,
            Real1 Val,
            int Ijob
        );

        MLProjJob(
            int Pos,
            const RC_Lexem &Ml,
            Real1 Val,
            int Ijob
        );

        // Этот конструктор вызывается, когда формируется задание на проекцию
        // слова, описываемого через грамматические категории.
        MLProjJob(int Pos, int Ijob);

        void operator=(const MLProjJob &x);

        inline const RC_Lexem& GetContent() const { return ml; }
        inline Real1 GetVal() const { return val; }
        inline int GetiJob() const { return ijob; }
        inline int GetOriginPos() const { return pos; }

        // По возможности возвращается исходная лексема, без изменения регистра.
        const UCString & GetWord() const { return org_word.empty() ? (const UCString&)*ml : org_word; }

        void Print(OFormatter &to) const;
        void PrintLexem(lem::OFormatter &to) const;
    };
#endif

#if defined SOL_CAA
    struct MLProjFreq
    {
        float score;
        int known_entry; // 0 для кванторных статей, получающихся при нечеткой проекции
        int local_freq, wordform_freq, wordentry_freq;
        MLProjFreq(void) : score(0.0f), known_entry(0), local_freq(0), wordform_freq(0), wordentry_freq(0) {}

        bool operator>(const MLProjFreq &x) const;
        bool operator<(const MLProjFreq &x) const;
    };
#endif


#if defined SOL_CAA
    /************************************************************
     Задание на проекцию мультилексемы для Лексического Автомата.
     Хранит также результаты успешных проекций и поля для работы
     Карусели Распределения Времени.
    ************************************************************/
    // Все возможности по проецированию задания исчерпаны - такое значение
    // будет иметь поле stadia.
    const int SOL_LA_PROJECTING_EXHAUSTED = lem::int_max;

    class MLProjList : lem::NonCopyable
    {
    private:
        int stadia;                // Стадия обработки задания (0-начало).

        lem::zbool allow_dynforms; // Допускается ли генерация форм на основе правил (суффиксы и префиксы)
        lem::zbool allow_fuzzy;    // Допускается ли нечеткое проецирование
        int miss_parameter;        // Допустимое количество пропускаемых букв для нечеткого проецирования.
        lem::zbool autoinc_maxmiss; // можно ли увеличивать miss_parameter при невозможности выполнить проекцию

        // Самый частый случай - слово задано своим лексическим содержанием.
        int word_index; // индекс слова в исходном предложении
        int word_parts; // кол-во слов в мультилексеме
        RC_Lexem word;           // Проецируемая исходная мультилексема.
        UCString org_word;       // слово в исходном регистре

        lem::UFString tokenizer_flags;

        // Специальный случай - слово описывается через грамматические категории.
        MCollect<UCString> group; // Группа токенов описания

        Collect<RC_Lexem> broken;   // С отброшенными приставками и т.д.
        Collect<RC_Lexem> phon_inv; // Список фонетических инвариантов для проецируемой мультилексемы.
        MCollect<Real1> pi_val;     // Достоверности фонетических инвариантов.

        MCollect<Word_Coord> coord; // Найденные проекции на Лексикон.
        MCollect<ProjScore> coord_val;  // Достоверности найденых проекций.
        lem::PtrCollect<LA_ProjectInfo> extra_inf; // Явно заданные координаты для проекций
        MCollect<Word_Form*> form;  // Список форм для найденных проекций.
        bool changed;               // Флаг успешного проецирования, нужно миксировать вариаторы.

        lem::Ptr<TokenizationTags> tags; // дополнительные ограничения на результаты проекции

        MLProjList(const MLProjList&);
        void operator=(const MLProjList&);

    public:
        MLProjList(const RC_Lexem &Word, int WordIndex, int WordParts);
        MLProjList(const RC_Lexem &Word, const UCString &Org, int WordIndex, int WordParts);
        MLProjList(const RC_Lexem &Word, const MCollect<UCString> &Group);

        ~MLProjList();

        void Delete();

        int GetWordIndex() const { return word_index; }
        int GetWordParts() const { return word_parts; }

        void SetTokenizerFlag(const lem::UFString &flags);

        inline bool IsChanged() const { return changed; }
        inline void ClearChange() { changed = false; }
        inline bool IsProjected() const { return !coord.empty(); }

        inline int GetStadia() const { return stadia; }
        inline void SetStadia(int Stadia) { stadia = Stadia; }
        inline void NextStadia() { stadia++; }
        inline bool is_Exhausted() const
        {
            return stadia == SOL_LA_PROJECTING_EXHAUSTED;
        }

        inline void set_Allow_Fuzzy(bool f) { allow_fuzzy = f; }
        inline bool get_Allow_Fuzzy() const { return allow_fuzzy; }

        inline void set_Dynforms(bool f) { allow_dynforms = f; }
        inline bool get_Dynforms() const { return allow_dynforms; }

        void set_Tags(lem::Ptr<TokenizationTags> t) { tags = t; }
        const TokenizationTags* get_Tags() const { return tags.IsNull() ? NULL : &*tags; }

        inline const RC_Lexem& GetContent() const { return word; }
        RC_Lexem GetOrgWord() const;

        inline const MCollect<Word_Coord>& GetCoordList(void) const { return coord; }
        inline const MCollect<ProjScore>& GetCoordValList(void) const { return coord_val; }
        inline const lem::PtrCollect<LA_ProjectInfo>& GetExtraInf(void) const { return extra_inf; }

        void SortByFrequency(Dictionary &dict);
        void Projected();

        inline const Word_Form& Get_Form(int i) const { return *form[i]; }
        Word_Form* GetVersionedForm() const;

        int CountForms() const { return CastSizeToInt(form.size()); }

        inline int GetnPhonInv() const { return CastSizeToInt(phon_inv.size()); }
        inline const RC_Lexem& GetPhonInv(int i) const { return phon_inv[i]; }
        inline Real1 GetPhonInvVal(int i) const { return pi_val[i]; }
        inline void AddPhonInv(const RC_Lexem &mlex, Real1 val)
        {
            phon_inv.push_back(mlex);
            pi_val.push_back(val);
            return;
        }

        inline void Add_Broken(const RC_Lexem &x) { broken.push_back(x); }
        inline const Collect<RC_Lexem>& get_Broken() const { return broken; }

        void SortPhonInv();
        //void SortProjs(void);

        bool Add(const Word_Coord & wc, const ProjScore & scoring, const LA_ProjectInfo * info);
        bool CanAdd(const Word_Coord& Coord, const LA_ProjectInfo *info) const;

        inline void Add(Word_Form *Form) { form.push_back(Form); }

        // Управление параметром - допустимое число несовпадающих букв
        inline void IncMissParameter() { miss_parameter++; }
        inline int get_Miss_Parameter() const { return miss_parameter; }
        inline void set_Miss_Parameter(int x) { miss_parameter = x; }
        inline bool CanIncrementMaxMiss() const { return autoinc_maxmiss; }

        void PrintHeap(OFormatter &to) const;
        void Print(OFormatter &to, bool detailed = false, const Dictionary *dict = NULL) const;

        inline const MCollect<UCString>& get_Group(void) const { return group; }
    };
#endif

#if defined SOL_CAA
    /***************************************************************************
    // Узел представления Сети Потока Распознования (для Лексического Автомата)
    ****************************************************************************/
    class MLNetNode
    {
    private:
        MCollect<MLNetNode*> child; // Список последующих узлов, которые прикреплены к нашему
        int from, n; // Индекс начального слова и число слов, входящих в мультилексему.
        int proj_job_i; // Индекс задания на проекцию в списке фразоблока.
        Real1 val; // Достоверность для узла (произв. задания и исходной мультилексемы).
        const MLNetNode *previous; // Предыдущий узел Сети, к которому прикреплен данный.

        MLNetNode(const MLNetNode&);
        void operator=(const MLNetNode&);

    public:
        MLNetNode(void)
        {
            from =
                n = 0;
            previous = NULL;
            val = Real1(100);
            proj_job_i = UNKNOWN;
        }

        MLNetNode(bool r);
        MLNetNode(
            const MLNetNode* prev,
            int ifrom,
            int nword,
            int ntotal,
            const MCollect<MLProjJob*> & job_list,
            const MCollect<MLProjList*> & proj_list,
            const MCollect<int> & word_job,
            const MCollect<Lexem> & words,
            Dictionary &dict
        );

        ~MLNetNode() { Delete(); }

        void Delete();

        inline int GetnChild() const { return CastSizeToInt(child.size()); }
        inline const MLNetNode& GetChild(int i) const
        {
            return *child[i];
        }
        inline MLNetNode* GetChildPtr(int i) { return child[i]; }

        inline const MLNetNode* GetPrevious() const { return previous; }
        inline int GetFrom() const { return from; }
        inline int GetN() const { return n; }
        inline int GetProjJobIndex() const { return proj_job_i; }
        inline Real1 GetVal() const { return val; }

        void FindFinitees(
            MCollect<const MLNetNode*> &finitees,
            int nword
        ) const;
    };
#endif

} // namespace Solarix

#endif
