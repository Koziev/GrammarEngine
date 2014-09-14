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

    void Connect(void);
    void Disconnect(void);
    ThesaurusStorage_SQLITE(void);

    void CreateTable_SG_Tag(void);
    void CreateTable_SG_Tag_Value(void);
    void CreateTable_TagSets(void);
    void CreateTables_WordLinks(void);
    void CreateTables_PhraseLinks(void);

   public:
    ThesaurusStorage_SQLITE( const lem::UFString & connection_string );

    virtual ~ThesaurusStorage_SQLITE(void);

    virtual void CreateSchema(void);
    virtual void CopyDatabase( const lem::Path & thesaurus_db_path );

    virtual void BeginTx(void);
    virtual void CommitTx(void);
    virtual void RollBackTx(void);

    virtual TransactionGuard* GetTxGuard(void);

    virtual bool GetTagSet( int id_tagset, lem::UFString &str );
    virtual int AddTagSet( const lem::UFString &tags );
    virtual LS_ResultSet* List_TagSets(void);

    virtual LS_ResultSet* ListTagDefs(void);
    virtual void GetTagName( int id_tag, lem::UCString &name );
    virtual int GetTagId( const lem::UCString &tag_name );
    virtual LS_ResultSet* List_TagValues( int id_tag );
    virtual int AddTag( const lem::UCString & tag_name );
    virtual int AddTagValue( int id_tag, int ivalue, const lem::UCString & value_name );

    virtual void ReplaceEntryKey( int old_ekey, int new_ekey );

    virtual int CountWordLinks( int optional_link_type );
    virtual LS_ResultSet* ListWordLinks(void);
    virtual LS_ResultSet* ListWordLinks( int ekey1 );
    virtual LS_ResultSet* ListWordLinks( int ekey1, int link_type );
    virtual LS_ResultSet* ListWordLinks( int ekey1, const lem::MCollect<int> & link_types );
    virtual LS_ResultSet* ListWordLinks2( int ekey2 );
    virtual LS_ResultSet* ListWordLinks2( int ekey2, int link_type );
    virtual LS_ResultSet* ListWordLinks2( int ekey2, const lem::MCollect<int> & link_types );
    virtual int FindWordLink( int ekey1, int ekey2, int link_type );
    virtual bool GetWordLink( int id, WordLink &info );
    virtual int AddWordLink( int ekey1, int ekey2, int link_type, int id_tag_set );
    virtual void DeleteWordLink( int id );
    virtual int /*id_tag_set*/ GetWordLinkTags( int id, lem::MCollect< std::pair<int,int> > &atomized_tags );
    virtual void SetWordLinkTags( int id, int id_tag_set );
    virtual void ClearWordLinkTags( int id );

    virtual int CountPhraseLinks( int optional_link_type );
    virtual LS_ResultSet* ListPhraseLinks(void);
    virtual LS_ResultSet* ListPhraseLinks( int id_phrase1 );
    virtual LS_ResultSet* ListPhraseLinks( int id_phrase1, int link_type );
    virtual LS_ResultSet* ListPhraseLinks( int id_phrase1, const lem::MCollect<int> & link_types );
    virtual int FindPhraseLink( int id_phrase1, int id_phrase2, int link_type );
    virtual bool GetPhraseLink( int id, PhraseLink &info );
    virtual int AddPhraseLink( int id_phrase1, int id_phrase2, int link_type, int id_tag_set );
    virtual void DeletePhraseLink( int id );
    virtual int /*id_tag_set*/ GetPhraseLinkTags( int id, lem::MCollect< std::pair<int,int> > &atomized_tags );
    virtual void SetPhraseLinkTags( int id, int id_tag_set );
    virtual void ClearPhraseLinkTags( int id );
    virtual void GetPhraseFlags( int id, lem::PtrCollect<SG_LinkFlag> &flags );
    virtual void ClearPhraseLinkFlags( int id_link );
    virtual int AddPhraseLinkFlag( int id_link, const lem::UCString &flag, const lem::UCString &value );
  };

 }

#endif
