#if defined SOL_DEBUGGING

// CD->28.07.2009
// LC->06.09.2017

#include <lem/keyboard.h>
#include <lem/solarix/variator.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/TrMorphologyTracer.h>
#include <lem/solarix/LA_CropRule.h>
#include <lem/solarix/LA_RecognitionRule.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/LA_PhoneticRule.h>
#include <lem/solarix/LA_PreprocessorTokRule.h>
#include <lem/solarix/SourceFilenameEnumerator.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/SynPattern.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/LexerTextPos.h>

#include "LA_PreprocessorTrace_Console.h"

using namespace lem;
using namespace Solarix;

LA_PreprocessorTrace_Console::LA_PreprocessorTrace_Console(Solarix::Dictionary *d)
{
    dict = d;
}



void LA_PreprocessorTrace_Console::LanguageGuessed(const lem::UFString &phrase, int LanguageID)
{
    if (trace)
    {
        lem::mout->printf("Language guesser: phrase=%us id_language=%d", phrase.c_str(), LanguageID);
        if (LanguageID != UNKNOWN)
        {
            const SG_Language &lang = dict->GetSynGram().languages()[LanguageID];
            lem::mout->printf(" language=%us\n", lang.GetName().c_str());
        }
        else
        {
            lem::mout->eol();
        }
    }

    return;
}

#endif
