// -----------------------------------------------------------------------------
// File VARIATOR.H
//
// (c) Koziev Elijah
//
// Content:
// Класс Variator - набор контекстных грамматических деревьев. Представляет
// собой контекст отдельного пути анализа входной фразы. Набор вариаторов
// хранится как Пачка Решений (класс Res_Pack).
// -----------------------------------------------------------------------------
//
// CD->07.09.1997
// LC->28.06.2012
// --------------

#if !defined( SOL_VARIATOR__H ) && !defined SOL_NO_AA
#define SOL_VARIATOR__H
#pragma once

#include <lem/containers.h>
#include <lem/set.h>
#include <lem/math/fp1.h>

#include <lem/solarix/tree_node.h>
#include <lem/solarix/PatternSynLinkedGroup.h>
#include <lem/solarix/PatternLinkEdge.h>

namespace Solarix
{
    using lem::MCollect;
    using lem::PtrCollect;
    using lem::OFormatter;
    using lem::Real1;

    class SynGram;
    class Tree_Node;
    class Word_Form;
    class SynGram;

    class Variator
    {
    private:
        int key;     // Уникальный ключ вариатора.
        int org_key; // Ключ исходного вариатора, то есть того начального
                     // вариатора, из которого данный клон получен серией грамматических
                     // преобразований. Сам исходный вариатор с данным ключем
                     // хранится в специальном контейнере (в пачке решений) в
                     // поле фразоблока.

        MCollect<Tree_Node*> roots; // Список деревьев.
        lem::PtrCollect<TreeMarks> marks; // пометки

        Real1 val; // Оценка достоверности, образуется как произведение достоверностей
                   // узлов.

        int freq;  // Аккумулятор частоты использования

        int score;

    public:
        void Init(const Variator& t);
        void Clear();

    public:
        Variator();
        Variator(const Variator& t);
        explicit Variator(const MCollect<Tree_Node*> &tree_list);

#if defined SOL_CAA
        Variator(const Word_Form *slist, int nsynt);
#endif

#if defined SOL_LOADBIN
        explicit Variator(lem::Stream &bin);
#endif

        Variator* DeepCopy() const;

        ~Variator();

        void Delete();

        void operator=(const Variator& t);

        inline int GetKey() const { return key; }
        inline int GetOrgKey() const { return org_key; }
        inline void SetOrgKey(int OrgKey) { org_key = OrgKey; }

        void Print(OFormatter &s, SynGram &gram, bool detailed) const;
        void PrintV(OFormatter &s, SynGram &gram, bool detailed) const;
        void PrintRoots(OFormatter &s, bool Decoration = true, bool EntryKeys = true) const;
        void PrintXML(OFormatter &xml, SynGram &gram) const;

        void Add(Tree_Node *to_add);

        inline const MCollect<Tree_Node*>& roots_list(void) const { return roots; }
        inline       MCollect<Tree_Node*>& roots_list(void) { return roots; }

        inline int size(void) const { return CastSizeToInt(roots.size()); }
        inline const Tree_Node& get(int i) const { return *roots[i]; }

        inline Tree_Node* operator[](int i) { return roots[i]; }
        inline const Tree_Node* operator[](int i) const { return roots[i]; }
        void DeleteTree(int index);

        void RemoveRoot(int ibunch);

        inline void ForgetTree(int index)
        {
            roots[index] = nullptr;
        }

#if defined SOL_CAA
        void SetPtr(int itree, Tree_Node *t);
        void Insert(int where_to, Tree_Node *to_add);
#endif

#if defined SOL_CAA
        inline int GetFreq(void) const { return freq; }
        inline void AddFreq(const int f) { freq += f; }
#endif

#if defined SOL_CAA
        inline void MulVal(Real1 f) { val = val * f; }
        inline void SetVal(Real1 v) { val = v; }
        inline Real1 GetVal() const { return val; }
#endif

        int GetScore() const { return score; }
        void AddScore(int delta) { score += delta; }

#if defined SOL_LOADBIN
        void LoadBin(lem::Stream &bin);
#endif

        void SaveBin(lem::Stream &bin) const;


#if defined SOL_CAA
        void DeleteRoots();
#endif

        bool operator==(const Variator &x) const;

        TreeMarks& TouchMarks(const UCString &name);
        TreeMarks* FindMarks(const UCString &name);
        const TreeMarks* FindMarks(const UCString &name) const;

        lem::PtrCollect<TreeMarks>& GetMarks() { return marks; }
        const lem::PtrCollect<TreeMarks>& GetMarks() const { return marks; }
    }; /* class Variator */

} // namespace 'Solarix'

#endif
