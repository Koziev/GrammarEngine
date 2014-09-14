#include <lem/solarix/phrasema.h>

using namespace Solarix;

SentenceWord::SentenceWord( const SentenceWord &x )
 : word(x.word), normalized_word(x.normalized_word)//, tags(x.tags), tokenizer_flags(x.tokenizer_flags)
{
}


void SentenceWord::operator=( const SentenceWord &x )
{
 word = x.word;
 normalized_word = x.normalized_word;
// tags = x.tags;
// tokenizer_flags = x.tokenizer_flags;
 return;
}

