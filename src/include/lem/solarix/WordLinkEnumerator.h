#if !defined WordLinkEnumerator__H
 #define WordLinkEnumerator__H

 #include <lem/solarix/SG_TagsList.h>

 namespace Solarix
 {
  class SG_Net;
  class ThesaurusStorage;
  class LS_ResultSet;
  class WordLinkEnumerator
  {
   private:
    int ekey1;
    SG_Net *thesaurus;
    LS_ResultSet *rs;
    int link_type;
    int ekey1_field, ekey2_field, link_type_field, tags_field;

   public:
    WordLinkEnumerator( SG_Net *th );
    WordLinkEnumerator( SG_Net *th, int _ekey1 );
    WordLinkEnumerator( SG_Net *th, int _ekey1, int _link_type );
    ~WordLinkEnumerator(void);

    bool Fetch(void);
    int GetEntryKey1(void);
    int GetEntryKey2(void);
    int GetLinkType(void);
    int GetLinkId(void);
    int GetTagsId(void);
    SG_TagsList GetTags(void);
  };

 }

#endif
