#if !defined PhraseLink__H
 #define PhraseLink__H

 namespace Solarix
 {
  class PhraseLink
  {
   public:
    int id;
    int id_entry1, id_entry2;
    int link_type;
    int id_tags;

   public:
    PhraseLink(void) : id(UNKNOWN), id_entry1(UNKNOWN), id_entry2(UNKNOWN), link_type(UNKNOWN), id_tags(UNKNOWN) {}
  };
 }

#endif
