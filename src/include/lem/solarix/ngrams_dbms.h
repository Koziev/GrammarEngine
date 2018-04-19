#if !defined(NGRAMS_DBMS__H) && !defined(SOL_NO_NGRAMS)
#define NGRAMS_DBMS__H
#pragma once

#include <lem/noncopyable.h>
#include <lem/path.h>
#include <lem/containers.h>

namespace Solarix
{
    class Ngrams;
    class NGramHandler;
    class LS_ResultSet;

    class NGramsDBMS : lem::NonCopyable
    {
    protected:
        NGramsDBMS() {}

    public:
        virtual ~NGramsDBMS();

        virtual bool IsRemote() const = 0;
        virtual NGramsDBMS* CreateDisconnectedClone() const = 0;

        virtual int MaxBulkInsert() const = 0;

        virtual void Connect(const lem::Path &dbfile) = 0;
        virtual void Disconnect() = 0;

        virtual bool Connected() const = 0;
        virtual void BeginTx() = 0;
        virtual void BeginReadTx() = 0;
        virtual void CommitTx() = 0;
        virtual void CommitReadTx() = 0;
        virtual void CommitRetaining() = 0;

        virtual LS_ResultSet* Select(const lem::FString &sql) = 0;

        virtual void ExecuteSql(const char *sql, bool check = true) = 0;
        virtual void ExecuteSql(const lem::FString &sql, bool check = true) = 0;
        virtual bool TableExists(const lem::FString &table) = 0;
        virtual bool IndexExists(const lem::FString &idx, const lem::FString &table_name) = 0;
        virtual void DropIndex(const lem::FString &idx, const lem::FString &table_name) = 0;
        virtual void SetDBCache(int cache_size) = 0;
        virtual void CommitCreatedIndeces() = 0;

        virtual int SelectInt(const lem::FString &Select, int def = -1) = 0;
        virtual int SelectInt(const char *Select, int def = -1) = 0;
        virtual std::pair<int, int> SelectIntPair(const lem::FString &Select) = 0;
        virtual void SelectInts(const lem::FString &Select, lem::MCollect<int> &list) = 0;
        virtual void SelectFStrings(const lem::FString &Select, lem::Collect<lem::FString> &list) = 0;

        virtual lem::UFString SelectStr(const char *Select) = 0;

        virtual void LoadSegments(const lem::FString &suffix, lem::Collect<lem::FString> &segments);
        virtual bool GetStat(
            int order,
            const lem::FString &suffix,
            const lem::FString &segment,
            float &min_w,
            float &max_w,
            lem::int64_t &n
        );


        virtual void FindLeftWords(
            const lem::FString &suffix,
            const lem::FString &segment,
            int ie_right,
            std::map< int, float > & reslist2,
            int min_w,
            int max_w,
            int min_freq
        );

        virtual void FindRightWords(
            const lem::FString &suffix,
            const lem::FString &segment,
            int ie_left,
            std::map< int, float > & reslist2,
            int min_w,
            int max_w,
            int min_freq
        );

        virtual std::pair<int, int> FindRawNGramsID(
            const lem::FString &suffix,
            const lem::FString &segment,
            const lem::UCString &w1
        );

        virtual std::pair<int, int> FindRawNGramsID(
            const lem::FString &suffix,
            const lem::FString &segment,
            const lem::UCString &w1,
            const lem::UCString &w2
        );

        virtual std::pair<int, int> FindRawNGramsID(
            const lem::FString &suffix,
            const lem::FString &segment,
            const lem::UCString &w1,
            const lem::UCString &w2,
            const lem::UCString &w3
        );

        virtual std::pair<int, int> FindRawNGramsID(
            const lem::FString &suffix,
            const lem::FString &segment,
            const lem::UCString &w1,
            const lem::UCString &w2,
            const lem::UCString &w3,
            const lem::UCString &w4
        );

        virtual std::pair<int, int> FindRawNGramsID(
            const lem::FString &suffix,
            const lem::FString &segment,
            const lem::UCString &w1,
            const lem::UCString &w2,
            const lem::UCString &w3,
            const lem::UCString &w4,
            const lem::UCString &w5
        );

        virtual int FindWord(
            const lem::FString &suffix,
            const lem::FString &segment,
            const lem::UCString &word
        );


        virtual void Find2GramsWithLeft(
            const lem::FString &suffix,
            const lem::FString &segment,
            float max_w2,
            const lem::UCString &left,
            int min_freq,
            std::map< lem::UCString, float > & reslist
        );

        virtual void Find2GramsWithRight(
            const lem::FString &suffix,
            const lem::FString &segment,
            float max_w2,
            const lem::UCString &right,
            int min_freq,
            std::map< lem::UCString, float > & reslist
        );

        virtual void FindRaw3GramsWithLeft(
            const lem::FString &suffix,
            const lem::FString &segment,
            float max_w3,
            const lem::UCString &left,
            int min_freq,
            std::map< std::pair<lem::UCString, lem::UCString>, float > & reslist
        );

        virtual void FindRaw3GramsWithCenter(
            const lem::FString &suffix,
            const lem::FString &segment,
            float max_w3,
            const lem::UCString &center,
            int min_freq,
            std::map< std::pair<lem::UCString, lem::UCString>, float > & reslist
        );

        virtual void FindRaw3GramsWithRight(
            const lem::FString &suffix,
            const lem::FString &segment,
            float max_w3,
            const lem::UCString &right,
            int min_freq,
            std::map< std::pair<lem::UCString, lem::UCString>, float > & reslist
        );

        virtual void Find1Grams(
            const lem::FString &suffix,
            const lem::FString &segment,
            int max_w1,
            int min_freq,
            std::map< lem::UCString, std::pair<int, float> > & reslist
        );

        virtual void Dump2Grams_1(
            const lem::FString &suffix,
            const lem::FString &segment,
            lem::OFormatter &to
        );

        virtual void Dump2Grams(
            const lem::FString &suffix,
            const lem::FString &segment,
            lem::OFormatter &to
        );

        virtual void Dump3Grams(
            const lem::FString &suffix,
            const lem::FString &segment,
            lem::OFormatter &to
        );

        virtual void ForEachRaw1(
            Ngrams &ngrams,
            const lem::FString &suffix,
            const lem::FString &segment,
            NGramHandler *handler,
            int sorting_type
        );

        virtual void ForEachRaw2(
            Ngrams &ngrams,
            const lem::FString &suffix,
            const lem::FString &segment,
            NGramHandler *handler,
            int sorting_type
        );

        virtual void ForEachRaw3(
            Ngrams &ngrams,
            const lem::FString &suffix,
            const lem::FString &segment,
            NGramHandler *handler,
            int sorting_type
        );

        virtual void ForEachRaw4(
            Ngrams &ngrams,
            const lem::FString &suffix,
            const lem::FString &segment,
            NGramHandler *handler,
            int sorting_type
        );

        virtual void ForEachRaw5(
            Ngrams &ngrams,
            const lem::FString &suffix,
            const lem::FString &segment,
            NGramHandler *handler,
            int sorting_type
        );

        virtual lem::int64_t SumFrequency(
            int order,
            const lem::FString &suffix,
            const lem::FString &segment
        );

        virtual void CreateTable_Words(const lem::FString &suffix) = 0;
        virtual void CreateTable_NGrams1(const lem::FString &suffix) = 0;
        virtual void CreateTable_NGrams2(const lem::FString &suffix) = 0;
        virtual void CreateTable_NGrams3(const lem::FString &suffix) = 0;
        virtual void CreateTable_NGrams4(const lem::FString &suffix) = 0;
        virtual void CreateTable_NGrams5(const lem::FString &suffix) = 0;
        virtual void CreateTable_Segments() = 0;

        virtual void CleanTables(const lem::FString &suffix, int order);
        virtual void CleanWordsTable(const lem::FString &suffix);

        virtual std::pair<int/*max(id)*/, int/*count(*)*/> GetMaxId(const lem::FString &suffix, int order);
        virtual std::pair<int/*max(id)*/, int/*count(*)*/> GetWordsMaxId(const lem::FString &suffix);
        virtual void RegisterSegment(const lem::FString &segment_n, const lem::FString &suffix0);

        virtual std::pair<int/*id*/, int/*w*/> Find1Gram(const lem::FString &suffix, int id_word);
        virtual std::pair<int/*id*/, int/*w*/> Find2Gram(const lem::FString &suffix, int id_word1, int id_word2);
        virtual std::pair<int/*id*/, int/*w*/> Find3Gram(const lem::FString &suffix, int id_word1, int id_word2, int id_word3);
        virtual std::pair<int/*id*/, int/*w*/> Find4Gram(const lem::FString &suffix, int id_word1, int id_word2, int id_word3, int id_word4);
        virtual std::pair<int/*id*/, int/*w*/> Find5Gram(const lem::FString &suffix, int id_word1, int id_word2, int id_word3, int id_word4, int id_word5);

        virtual lem::FString StartBulkInsert(const lem::FString &suffix, int order) = 0;

        virtual lem::FString AppendBulkInsert(
            const lem::FString &suffix,
            int counter,
            int id,
            int id_word1,
            int w
        ) = 0;

        virtual lem::FString AppendBulkInsert(
            const lem::FString &suffix,
            int counter,
            int id,
            int id_word1,
            int id_word2,
            int w
        ) = 0;

        virtual lem::FString AppendBulkInsert(
            const lem::FString &suffix,
            int counter,
            int id,
            int id_word1,
            int id_word2,
            int id_word3,
            int w
        ) = 0;

        virtual lem::FString AppendBulkInsert(
            const lem::FString &suffix,
            int counter,
            int id,
            int id_word1,
            int id_word2,
            int id_word3,
            int id_word4,
            int w
        ) = 0;

        virtual lem::FString AppendBulkInsert(
            const lem::FString &suffix,
            int counter,
            int id,
            int id_word1,
            int id_word2,
            int id_word3,
            int id_word4,
            int id_word5,
            int w
        ) = 0;

        void FinishBulkInsert(const lem::FString &sql);


        virtual void UpdateNGrams(
            const lem::FString &suffix,
            int order,
            const lem::MCollect< std::pair<int, int> > & list
        ) = 0;

        virtual void CreateIndeces1(const lem::FString &suffix, int order);
        virtual void CreateIndeces2(const lem::FString &suffix, int order);
        virtual void CreateIndecesWord2(const lem::FString &suffix);

        virtual int FindWord(
            const lem::FString &suffix,
            const lem::UCString &word
        );

        virtual lem::UCString GetWord(const lem::FString &suffix, const lem::FString &segment, int id_word);

        virtual void InsertWord(
            const lem::FString &suffix,
            int id_word,
            const lem::UCString &word
        );

        virtual void UpdateStatistics(const lem::FString &suffix, int order);
        virtual void EraseFreq1(const lem::FString &suffix, int order);
    };
}

#endif
