#if !defined RECO2_TRANSFORM__H
 #define RECO2_TRANSFORM__H

 #include <lem/noncopyable.h>
 #include <lem/ucstring.h>
 #include <lem/containers.h>

 namespace Solarix
 {
  class Dictionary;
  class LemmatizatorStorage;
 }

 namespace Reco2
 {
  class RTransform : lem::NonCopyable
  {
   private: 
    int id;
    lem::UCString name;
    int distance;

   public:
    RTransform(void);

    RTransform( int _id, const wchar_t *_name, int _distance );

    int GetId(void) const { return id; }
    bool MatchName( const lem::UCString & x ) const { return x==name; }
    int GetDistance(void) const { return distance; }

    #if defined SOL_CAA
    bool Do(
            Solarix::Dictionary &dict,
            Solarix::LemmatizatorStorage &lemm,
            const lem::UCString &src,
            lem::MCollect<lem::UCString> &res
           ) const;
    #endif
  };

 }

#endif
