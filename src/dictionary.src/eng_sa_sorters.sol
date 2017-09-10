// CD->05.06.2009
// LC->11.03.2012

#include "aa_rules.inc"

automat la
{
 // ------------ SORTERS ------------------
 
 // direct flight 
 pattern sorter language=English { ENG_ADJECTIVE:*{} ENG_NOUN:*{ NOUN_FORM:BASIC } }

 // the global economy
 pattern sorter language=English { eng_article:*{} ENG_ADJECTIVE:*{} ENG_NOUN:*{ NOUN_FORM:BASIC } }
 
 // the cat sleeps
 pattern sorter language=English { ENG_NOUN:*{ NOUN_FORM:BASIC NUMBER:SINGLE } ENG_VERB:*{ VERB_FORM:UNDEF NUMBER:SINGLE PERSON:3 } }

 // the cat silently sleeps
 pattern sorter language=English { ENG_NOUN:*{ NOUN_FORM:BASIC NUMBER:SINGLE } ENG_ADVERB:*{} ENG_VERB:*{ VERB_FORM:UNDEF NUMBER:SINGLE PERSON:3 } }
 
 // the cats sleep
 pattern sorter language=English { ENG_NOUN:*{ NOUN_FORM:BASIC NUMBER:PLURAL } ENG_VERB:*{ VERB_FORM:UNDEF NUMBER:PLURAL } }

 // the cats silently sleep
 pattern sorter language=English { ENG_NOUN:*{ NOUN_FORM:BASIC NUMBER:PLURAL } ENG_ADVERB:*{} ENG_VERB:*{ VERB_FORM:UNDEF NUMBER:PLURAL } }

 
}
