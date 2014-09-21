#if defined SOL_USE_SPEAKER

#include <lem/path.h>
#include <lem/solarix/speak_lib.h>
#include <lem/solarix/AuxFormTypes.h>
#include <lem/solarix/Languages.h>
#include <lem/solarix/Dictionary.h>
//#include <lem/solarix/phrasema.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/variator.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/WrittenTextAnalysisSession.h>
#include <lem/solarix/Speaker_eSpeak.h>

using namespace Solarix;



Speaker_eSpeak::Speaker_eSpeak( Solarix::Dictionary * _dict, const lem::Path & _data_folder )
 : Speaker(_dict), init_lib(true), data_folder(_data_folder)
{
}

Speaker_eSpeak::~Speaker_eSpeak()
{
 if( !init_lib )
  {
   espeak_Terminate();
  }
}


void Speaker_eSpeak::Init()
{
 if( init_lib )
 {
  lem::FString path;
  path = data_folder.GetAscii();

  int rc1 = espeak_Initialize( AUDIO_OUTPUT_SYNCH_PLAYBACK, 10000, path.c_str(), 0 );

  // espeak_SetSynthCallback(SynthCallback);
  init_lib=false;
 }

 return;
}


void Speaker_eSpeak::SelectVoice( int LanguageID )
{
 lem::UCString lang2("default");

 std::map<int,lem::UCString>::const_iterator it = id2lang.find( LanguageID );
 if( it==id2lang.end() )
  {
   const SG_Language & l = dict->GetSynGram().languages()[LanguageID];
   lang2 = l.GetParam( l.FindParam(L"Name2") ).GetValue().c_str();
   id2lang.insert( std::make_pair( LanguageID, lang2 ) );
  }
 else
  {
   lang2 = it->second;
  }

 if( current_voice_lang!=lang2 )
  {
/*
 const espeak_VOICE ** voices = espeak_ListVoices(NULL);

 if( voices!=NULL )
 {
  int i=0;
  while( voices[i]!=NULL )
  {
   printf( "%s\n", voices[i]->name );
   i++;
  }
 } 
*/

   current_voice_lang = lang2;
   int rc1 = espeak_SetVoiceByName( lem::to_ascii(lang2).c_str() );
   rc1 = espeak_SetParameter( espeakRATE, 100, 0 );
   rc1 = espeak_SetParameter( espeakRATE, 100, 0 );
  }

 return;
}

  
void Speaker_eSpeak::Say( const lem::UFString & phrase, int LanguageID )
{
 Init();

/*
 lem::MCollect<lem::UCString> words;

 Solarix::Sentence sent;
 sent.Parse( phrase, false, dict, LanguageID==UNKNOWN ? default_language : LanguageID, NULL );
 for( int i=0; i<CastSizeToInt(sent.size()); ++i )
  words.push_back( sent.GetWord(i) );
*/

 WrittenTextAnalysisSession current_analysis( dict, NULL );
 current_analysis.params.SetLanguageID( LanguageID==UNKNOWN ? default_language : LanguageID );
 current_analysis.params.CompleteAnalysisOnly = true;
 current_analysis.params.AllowPrimaryFuzzyWordRecog = false;
 current_analysis.params.UseTokenReconstruction = false;
 current_analysis.params.UseSparsePatterns = false;
 current_analysis.params.UseTopDownThenSparse = false;

 current_analysis.MorphologicalAnalysis(phrase);

 const Solarix::Res_Pack & pack = current_analysis.GetPack();
 const Solarix::Variator & var = * pack.vars()[ pack.GetShortestVar() ];

 const int aux_type = dict->GetSynGram().GetAuxFormTypes()[L"espeak"];

 lem::UFString phonemas;
 for( int i=1; i<var.size()-1; ++i )
  {
   bool generated = false;
   const Solarix::Word_Form & wf = var.get(i).GetNode();
   const int ekey = wf.GetEntryKey();
   if( ekey!=UNKNOWN )
    {
     const Solarix::SG_Entry & e = dict->GetSynGram().GetEntry(ekey);

     Solarix::CP_Array px;
     for( lem::Container::size_type j=0; j<wf.GetPairs().size(); ++j )
      px.push_back( wf.GetPairs()[j] );

     int id_form = e.FindFormIndex( px );
     if( id_form!=UNKNOWN )
      {
       lem::UFString word_transcr;
       int id_aux = dict->GetSynGram().GetStorage().GetAuxForm( ekey, id_form, aux_type, word_transcr );
       if( id_aux!=UNKNOWN )
        {
         // если у словоформы есть озвучка, то используем именно ее.
         phonemas += L" [[";
         phonemas += word_transcr.c_str();
         phonemas += L"]] ";
         generated=true;
        }
      }
    }

   if( !generated )
    {
     lem::UCString word = *wf.GetName();  //words[i];
     word.to_upper();
     lem::UFString word_transcr;
     int aux_id = dict->GetSynGram().GetStorage().GetAuxWord( word, aux_type, word_transcr );
     if( aux_id!=UNKNOWN )
      {
       phonemas += L" [[";
       phonemas += word_transcr.c_str();
       phonemas += L"]] ";
      }
     else
      {
       phonemas += L" ";
       phonemas += wf.GetName()->c_str();
      }
    }
  }

 SelectVoice( LanguageID==UNKNOWN ? default_language : LanguageID );

 // const char str[] = " [[sab'aka]] ";
 int rc2 = espeak_Synth( phonemas.c_str(), 0, 0, POS_CHARACTER, phonemas.length(), espeakCHARS_WCHAR | espeakPHONEMES,  0, NULL );

 return;
}

#endif
