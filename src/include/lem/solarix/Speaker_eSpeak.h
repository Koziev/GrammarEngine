#if !defined SOL_SPEAKER_ESPEAK__H && defined SOL_USE_SPEAKER
#define SOL_SPEAKER_ESPEAK__H

#include <map>
#include <lem/ucstring.h>
#include <lem/solarix/speaker.h>

namespace Solarix
{
 class Speaker_eSpeak : public Speaker
 {
  private:
   lem::Path data_folder;

   bool init_lib;
   void Init();

   lem::UCString current_voice_lang; // 2х символьный код языка для текущего голоса
   std::map<int,lem::UCString> id2lang;
   void SelectVoice( int LanguageID );

  public:
   Speaker_eSpeak( Solarix::Dictionary * _dict, const lem::Path & data_folder );

   virtual ~Speaker_eSpeak();
   virtual void Say( const lem::UFString & phrase, int LanguageID );
 };
}

#endif
