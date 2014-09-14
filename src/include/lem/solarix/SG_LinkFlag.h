#if !defined SG_LinkFlag__H
 #define SG_LinkFlag__H

 #include <lem/ufstring.h>
 #include <lem/quantors.h>

 namespace Solarix
 {
  class SG_Net;
  class SG_LinkFlag
  {
   private:
    int tlf_id;
    lem::UFString flag, value;

    friend class SG_Net;

   public:
    SG_LinkFlag(void) : tlf_id(UNKNOWN) {}
    SG_LinkFlag( const SG_LinkFlag & x ) : tlf_id(x.tlf_id), flag(x.flag), value(x.value) {}

    SG_LinkFlag( int _tlf_id, const lem::UFString &_flag, const lem::UFString &_value )
     : tlf_id(_tlf_id), flag(_flag), value(_value) {}

    void operator=( const SG_LinkFlag & x )
    {
     tlf_id=x.tlf_id;
     flag = x.flag;
     value = x.value;
    }

    int GetId(void) const { return tlf_id; }
    const lem::UFString& GetFlag(void) const { return flag; }
    const lem::UFString& GetValue(void) const { return value; }
  };

 }

#endif
