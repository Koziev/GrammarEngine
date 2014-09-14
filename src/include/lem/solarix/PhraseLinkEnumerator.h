#if !defined PhraseLinkEnumerator__H
 #define PhraseLinkEnumerator__H

 #include <lem/solarix/SG_TagsList.h>

 namespace Solarix
 {
  class SG_Net;
  class ThesaurusStorage;
  class LS_ResultSet;
  class PhraseLinkEnumerator
  {
   private:
    int id_phrase1;
    SG_Net *thesaurus;
    LS_ResultSet *rs;
    lem::MCollect<int> link_types;
    int id_phrase1_field, id_phrase2_field, link_type_field, tags_field;

   public:
    PhraseLinkEnumerator( SG_Net *th );
    PhraseLinkEnumerator( SG_Net *th, int _id_phrase1 );
    PhraseLinkEnumerator( SG_Net *th, int _id_phrase1, int _link_type );
    PhraseLinkEnumerator( SG_Net *th, int _id_phrase1, const lem::MCollect<int> _link_types );
    ~PhraseLinkEnumerator(void);

    bool Fetch(void);
    int GetIdPhrase1(void);
    int GetIdPhrase2(void);
    int GetLinkType(void);
    int GetLinkId(void);
    int GetTagsId(void);
    SG_TagsList GetTags(void);
  };

 }

#endif
