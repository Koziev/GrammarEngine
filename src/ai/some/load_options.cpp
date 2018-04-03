#include <lem/solarix/load_options.h>

using namespace Solarix;

Load_Options::Load_Options()
{
 load_semnet = true;
 affix_table = false;
 seeker = false;
 stemmer = true;
 lexicon = true;

 lemmatizer = true;
 force_lemmatizer_fastest_mode = false;
}
