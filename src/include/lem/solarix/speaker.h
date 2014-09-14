#if !defined SOL_SPEAKER__H && defined SOL_USE_SPEAKER
#define SOL_SPEAKER__H

#include <lem/noncopyable.h>
#include <lem/quantors.h>
#include <lem/ufstring.h>

namespace Solarix
{
 class Dictionary;

 class Speaker : lem::NonCopyable
 {
  protected:
   Solarix::Dictionary * dict;
   int default_language;

  public:
   Speaker( Solarix::Dictionary * _dict ) : dict(_dict), default_language(UNKNOWN) {}

   virtual ~Speaker() {}
   virtual void SetDefaultLanguage( int id ) { default_language=id; }
   virtual void Say( const lem::UFString & phrase, int LanguageID )=0;
 };
}

#endif
