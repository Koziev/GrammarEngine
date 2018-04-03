#if !defined ALPHABET_STORAGE__H
#define ALPHABET_STORAGE__H

#include <lem/containers.h>
#include <lem/solarix/WordCoord.h>
#include <lem/solarix/coord_pair.h>
#include <lem/solarix/CriteriaStorage.h>

namespace Solarix
{
    class Alphabet;
    class AlphabetEnumerator;
    class LS_ResultSet;
    class GramCoord;
    class GramClass;
    class GG_Entry;
    class GG_CharOperation;
    class SyllabRule;

    class AlphabetStorage : public CriteriaStorage
    {
    protected:
        AlphabetStorage() {}

    public:
        virtual ~AlphabetStorage() {}

        virtual void CopyDatabase(const lem::Path & alphabet_db_path) = 0;

        virtual Alphabet* GetAlphabet(int id) = 0;
        virtual int FindAlphabet(const lem::UCString &name) = 0;
        virtual LS_ResultSet* ListAlphabets(void) = 0;
        virtual int AddAlphabet(const lem::UCString &name) = 0;
        virtual void StoreAlphabet(const Alphabet &a) = 0;
        virtual int CountAlphabets() = 0;

        virtual bool GetCoord(int id, GramCoord &coord) = 0;
        virtual LS_ResultSet* ListCoords(void) = 0;
        virtual int FindCoord(const lem::UCString &name) = 0;
        virtual int CountCoords() = 0;
        virtual int AddCoord(const lem::UCString &coord) = 0;
        virtual int AddCoord(Solarix::GramCoord &coord) = 0;
        virtual void StoreCoord(int id, Solarix::GramCoord &coord) = 0;

        virtual bool GetClass(int id, GramClass &cls) = 0;
        virtual LS_ResultSet* ListClasses() = 0;
        virtual int FindClass(const lem::UCString &name) = 0;
        virtual int CountClasses() = 0;
        virtual int AddClass(const lem::UCString &name) = 0;
        virtual int AddClass(const Solarix::GramClass &cls) = 0;
        virtual void StoreClass(int id, const GramClass &cls) = 0;

        virtual void FindSymbol(lem::uint32_t code, lem::MCollect<Word_Coord> &projs) = 0;
        virtual void FindSymbol(lem::uint32_t code, lem::MCollect<Solarix::Word_Coord> &projs, int AlphabetID) = 0;
        virtual void FindSymbol(lem::uint32_t code, lem::MCollect<Solarix::Word_Coord> &projs, const lem::MCollect<int> & AlphabetID) = 0;

        virtual int StorePairs(const lem::MCollect<GramCoordPair> & pairs) = 0;
        virtual void LoadPairs(int id_pairs, lem::MCollect<GramCoordPair> & pairs) = 0;

        virtual int StoreEntry(const GG_Entry &e) = 0;
        virtual GG_Entry* LoadEntry(int id) = 0;
        virtual LS_ResultSet* ListEntries(void) = 0;
        virtual int CountEntries() = 0;
        virtual int CountEntryForms() = 0;

        virtual LS_ResultSet* ListCharOperations(void) = 0;
        virtual GG_CharOperation* GetCharOperation(int id) = 0;
        virtual int StoreCharOperation(GG_CharOperation *operation) = 0;
        virtual int FindCharOperation(const lem::UCString &name) = 0;

        virtual void DeleteSyllabRules() = 0;
        virtual int StoreSyllabRule(const lem::UCString &rule_name, int id_language, int id_src, int cursor_shift) = 0;
        virtual void StoreSyllabConditionPoint(
            int id_rule,
            int point_index,
            const lem::MCollect<lem::uint32_t> &codes,
            int id_class,
            int id_entry,
            int id_coord0, int id_state0,
            bool is_left_boundary, bool is_right_boundary,
            bool is_positive
        ) = 0;
        virtual void StoreSyllabResultPoint(
            int id_rule,
            int point_index,
            int copy_index,
            int merge_index0,
            int merge_count
        ) = 0;
        virtual LS_ResultSet* ListSyllabRulesForLanguage(int id_language) = 0;
        virtual LS_ResultSet* ListSyllabRules() = 0;
        virtual LS_ResultSet* ListSyllabConditionPoints() = 0;
        virtual LS_ResultSet* ListSyllabResultPoints() = 0;
        virtual SyllabRule * LoadSyllabRule(int id_rule) = 0;
        virtual LS_ResultSet* ListSyllabConditionPointsForRule(int id_rule) = 0;
        virtual LS_ResultSet* ListSyllabResultPointsForRule(int id_rule) = 0;
    };
}

#endif
