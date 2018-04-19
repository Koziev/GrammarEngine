#if !defined ThesaurusStorage_SQLITE__h
#define ThesaurusStorage_SQLITE__h

#include <lem/sqlite.h>
#include <lem/path.h>
#include <lem/solarix/ThesaurusStorage.h>

namespace Solarix
{
    class ThesaurusStorage_SQLITE : public ThesaurusStorage
    {
    private:
        lem::UFString sqlite_connection_string;
        struct sqlite3* hdb; // дескриптор БД тезауруса

        void Connect();
        void Disconnect();
        ThesaurusStorage_SQLITE();

        void CreateTable_SG_Tag();
        void CreateTable_SG_Tag_Value();
        void CreateTable_TagSets();
        void CreateTables_WordLinks();
        void CreateTables_PhraseLinks();

    public:
        ThesaurusStorage_SQLITE(const lem::UFString & connection_string);

        virtual ~ThesaurusStorage_SQLITE();

        virtual void CreateSchema() override;
        virtual void CopyDatabase(const lem::Path & thesaurus_db_path) override;

        virtual void BeginTx() override;
        virtual void CommitTx() override;
        virtual void RollBackTx() override;

        virtual TransactionGuard* GetTxGuard() override;

        virtual bool GetTagSet(int id_tagset, lem::UFString &str) override;
        virtual int AddTagSet(const lem::UFString &tags) override;
        virtual LS_ResultSet* List_TagSets() override;

        virtual LS_ResultSet* ListTagDefs() override;
        virtual void GetTagName(int id_tag, lem::UCString &name) override;
        virtual int GetTagId(const lem::UCString &tag_name) override;
        virtual LS_ResultSet* List_TagValues(int id_tag) override;
        virtual int AddTag(const lem::UCString & tag_name) override;
        virtual int AddTagValue(int id_tag, int ivalue, const lem::UCString & value_name) override;

        virtual void ReplaceEntryKey(int old_ekey, int new_ekey) override;

        virtual int CountWordLinks(int optional_link_type) override;
        virtual LS_ResultSet* ListWordLinks() override;
        virtual LS_ResultSet* ListWordLinks(int ekey1) override;
        virtual LS_ResultSet* ListWordLinks(int ekey1, int link_type) override;
        virtual LS_ResultSet* ListWordLinks(int ekey1, const lem::MCollect<int> & link_types) override;
        virtual LS_ResultSet* ListWordLinks2(int ekey2) override;
        virtual LS_ResultSet* ListWordLinks2(int ekey2, int link_type) override;
        virtual LS_ResultSet* ListWordLinks2(int ekey2, const lem::MCollect<int> & link_types) override;
        virtual int FindWordLink(int ekey1, int ekey2, int link_type) override;
        virtual bool GetWordLink(int id, WordLink &info) override;
        virtual int AddWordLink(int ekey1, int ekey2, int link_type, int id_tag_set) override;
        virtual void DeleteWordLink(int id) override;
        virtual int /*id_tag_set*/ GetWordLinkTags(int id, lem::MCollect< std::pair<int, int> > &atomized_tags) override;
        virtual void SetWordLinkTags(int id, int id_tag_set) override;
        virtual void ClearWordLinkTags(int id) override;

        virtual int CountPhraseLinks(int optional_link_type) override;
        virtual LS_ResultSet* ListPhraseLinks() override;
        virtual LS_ResultSet* ListPhraseLinks(int id_phrase1) override;
        virtual LS_ResultSet* ListPhraseLinks(int id_phrase1, int link_type) override;
        virtual LS_ResultSet* ListPhraseLinks(int id_phrase1, const lem::MCollect<int> & link_types) override;
        virtual int FindPhraseLink(int id_phrase1, int id_phrase2, int link_type) override;
        virtual bool GetPhraseLink(int id, PhraseLink &info) override;
        virtual int AddPhraseLink(int id_phrase1, int id_phrase2, int link_type, int id_tag_set) override;
        virtual void DeletePhraseLink(int id) override;
        virtual int /*id_tag_set*/ GetPhraseLinkTags(int id, lem::MCollect< std::pair<int, int> > &atomized_tags) override;
        virtual void SetPhraseLinkTags(int id, int id_tag_set) override;
        virtual void ClearPhraseLinkTags(int id) override;
        virtual void GetPhraseFlags(int id, lem::PtrCollect<SG_LinkFlag> &flags) override;
        virtual void ClearPhraseLinkFlags(int id_link) override;
        virtual int AddPhraseLinkFlag(int id_link, const lem::UCString &flag, const lem::UCString &value) override;
    };

}

#endif
