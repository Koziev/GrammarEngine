#if !defined ThesaurusStorage__h
 #define ThesaurusStorage__h

 #include <lem/containers.h>
 #include <lem/ptr_container.h>
 #include <lem/solarix/LS_ResultSet.h>
 #include <lem/solarix/SG_LinkFlag.h>
 #include <lem/solarix/WordLink.h>
 #include <lem/solarix/DictionaryStorage.h>

 namespace Solarix
 {
  class PhraseLink;

  class ThesaurusStorage : public DictionaryStorage
  {
   protected:
    ThesaurusStorage(void) {}

   public:
    virtual ~ThesaurusStorage(void) {}

    virtual bool GetTagSet( int id_tagset, lem::UFString &str )=0;
    virtual LS_ResultSet* List_TagSets(void)=0;
    virtual int AddTagSet( const lem::UFString &tags )=0;

    virtual LS_ResultSet* ListTagDefs(void)=0;
    virtual void GetTagName( int id_tag, lem::UCString &name )=0;
    virtual int GetTagId( const lem::UCString &tag_name )=0;
    virtual LS_ResultSet* List_TagValues( int id_tag )=0;
    virtual int AddTag( const lem::UCString & tag_name )=0;
    virtual int AddTagValue( int id_tag, int ivalue, const lem::UCString & value_name )=0;

    virtual void ReplaceEntryKey( int old_ekey, int new_ekey )=0;
    virtual int CountWordLinks( int optional_link_type )=0;
    virtual LS_ResultSet* ListWordLinks(void)=0;
    virtual LS_ResultSet* ListWordLinks( int ekey1 )=0;
    virtual LS_ResultSet* ListWordLinks( int ekey1, int link_type )=0;
    virtual LS_ResultSet* ListWordLinks( int ekey1, const lem::MCollect<int> & link_types )=0;
    virtual LS_ResultSet* ListWordLinks2( int ekey2 )=0;
    virtual LS_ResultSet* ListWordLinks2( int ekey2, int link_type )=0;
    virtual LS_ResultSet* ListWordLinks2( int ekey2, const lem::MCollect<int> & link_types )=0;
    virtual int FindWordLink( int ekey1, int ekey2, int type )=0;
    virtual bool GetWordLink( int id, WordLink &info )=0;
    virtual int AddWordLink( int ekey1, int ekey2, int link_type, int id_tag_set )=0;
    virtual void DeleteWordLink( int id )=0;
    virtual int /*id_tag_set*/ GetWordLinkTags( int id, lem::MCollect< std::pair<int,int> > &atomized_tags )=0;
    virtual void SetWordLinkTags( int id, int id_tag_set )=0;
    virtual void ClearWordLinkTags( int id )=0;


    virtual int CountPhraseLinks( int optional_link_type )=0;
    virtual LS_ResultSet* ListPhraseLinks(void)=0;
    virtual LS_ResultSet* ListPhraseLinks( int id_phrase1 )=0;
    virtual LS_ResultSet* ListPhraseLinks( int id_phrase1, int link_type )=0;
    virtual LS_ResultSet* ListPhraseLinks( int id_phrase1, const lem::MCollect<int> & link_types )=0;
    virtual int FindPhraseLink( int id_phrase1, int id_phrase2, int link_type )=0;
    virtual bool GetPhraseLink( int id, PhraseLink &info )=0;
    virtual int AddPhraseLink( int id_phrase1, int id_phrase2, int link_type, int id_tag_set )=0;
    virtual void DeletePhraseLink( int id )=0;
    virtual int /*id_tag_set*/ GetPhraseLinkTags( int id, lem::MCollect< std::pair<int,int> > &atomized_tags )=0;
    virtual void SetPhraseLinkTags( int id, int id_tag_set )=0;
    virtual void ClearPhraseLinkTags( int id )=0;
    virtual void GetPhraseFlags( int id, lem::PtrCollect<SG_LinkFlag> &flags )=0;
    virtual void ClearPhraseLinkFlags( int id_link )=0;
    virtual int AddPhraseLinkFlag( int id_link, const lem::UCString &flag, const lem::UCString &value )=0;
  };

 }

#endif
