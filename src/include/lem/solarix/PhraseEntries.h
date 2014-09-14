#if !defined PhraseEntries__H
 #define PhraseEntries__H

 #include <lem/solarix/sg_defs.h>
 #include <lem/solarix/SG_LinkFlag.h>

 namespace Solarix
 {
  class SG_Phrase
  {
   public:
    int id;
    lem::UFString text;
    int id_language;
    int id_class;
    int syntax_flags;

   public:
    SG_Phrase(void) : id(UNKNOWN), id_language(UNKNOWN), id_class(UNKNOWN),
                      syntax_flags(frz_complete_syntax_analysis) {}

    SG_Phrase( int _id, const lem::UFString &_text, int _id_language, int _id_class, int _syntax_flags )
    : id(_id), text(_text), id_language(_id_language), id_class(_id_class), syntax_flags(_syntax_flags)
    {}

    SG_Phrase( const lem::UFString &_text, int _id_language, int _id_class, int _syntax_flags )
    : id(UNKNOWN), text(_text), id_language(_id_language), id_class(_id_class), syntax_flags(_syntax_flags)
    {}
    
    int GetId(void) const { return id; }
    int GetLanguage(void) const { return id_language; }
    int GetClass(void) const { return id_class; }
    int GetSyntaxFlags(void) const { return syntax_flags; }
    const lem::UFString& GetText(void) const { return text; }

    void SetClass( int _id_class ) { id_class=_id_class; }
  };



  class SG_PhraseNote
  {
   private:
    SG_PhraseNote( int _tn_id, int _type, const lem::UFString &_data )
     : tn_id(_tn_id), type(_type), data(_data) {}

   public:
    int tn_id;
    int type;
    lem::UFString data;

   public:
    SG_PhraseNote(void) : tn_id(UNKNOWN) {}
    SG_PhraseNote( const SG_PhraseNote & x ) : tn_id(x.tn_id), type(x.type), data(x.data) {}

    void operator=( const SG_PhraseNote & x )
    {
     tn_id=x.tn_id;
     type = x.type;
     data = x.data;
    }

    int GetId(void) const { return tn_id; }
    int GetType(void) const { return type; }
    const lem::UFString& GetData(void) const { return data; }
  };

 }
#endif
