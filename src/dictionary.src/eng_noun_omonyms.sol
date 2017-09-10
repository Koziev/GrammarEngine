// CD->26.05.2012
// LC->17.11.2015

automat sg
{
 omonym add eng_noun:bill{}

 entry Bill : eng_noun
 {
  ENG_PROPER_NOUN
  HAS_POSSESSIVE_FORM
  paradigm Noun_8000
  CharCasing:FirstCapitalized
 }

 link eng_noun:Bill{ ENG_PROPER_NOUN } <в_класс> ThesaurusEntries:HypernymHumanName{}

 
 entry bill : eng_noun
 {
  NUMBER:SINGLE { bill }
  NUMBER:PLURAL { bills }
 }

 omonym remove eng_noun:bill{}

 // ----------------------------

 omonym add eng_noun:fern{}

 entry "fern" : ENG_NOUN 
 {
  NUMBER:SINGLE { "fern" }
  NUMBER:PLURAL { "ferns" }
 }

 entry "Fern" : ENG_NOUN 
 {
  CHARCASING:FirstCapitalized
  ENG_GENDER:FEMININE
  ENG_PROPER_NOUN
  NUMBER:SINGLE { "Fern" }
 }

 omonym remove eng_noun:fern{}

 // ----------------------------

 omonym add eng_noun:aurora{}

 entry "aurora" : ENG_NOUN 
 {
  NUMBER:SINGLE { "aurora" }
  NUMBER:PLURAL { "auroras" }
 }

 entry "Aurora" : ENG_NOUN 
 {
  CHARCASING:FirstCapitalized
  ENG_GENDER:FEMININE
  ENG_PROPER_NOUN
  NUMBER:SINGLE { "Aurora" }
 }

 omonym remove eng_noun:aurora{}

 // --------------------------------------------

 omonym add eng_noun:Patty{}

 entry "patty" : ENG_NOUN 
 {
  NUMBER:SINGLE { "patty" }
  NUMBER:PLURAL { "patties" }
 }

entry "Patty" : ENG_NOUN 
{
 CHARCASING:FirstCapitalized
 ENG_GENDER:FEMININE
 ENG_PROPER_NOUN
 NUMBER:SINGLE { "Patty" }
}

 omonym remove eng_noun:patty{}

 // --------------------------------------------

 omonym add eng_noun:pattie{}

 entry "pattie" : ENG_NOUN 
 {
  NUMBER:SINGLE { "pattie" }
  NUMBER:PLURAL { "patties" }
 }

entry "Pattie" : ENG_NOUN 
{
 CHARCASING:FirstCapitalized
 ENG_GENDER:FEMININE
 ENG_PROPER_NOUN
 NUMBER:SINGLE { "Pattie" }
}

 omonym remove eng_noun:pattie{}

}
