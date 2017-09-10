// -----------------------------------------------------------------------------
// File ENG_PRONOUNS.SOL
//
// (c) Koziev Elijah
// Solarix Intellectronix project   http://www.solarix.ru
//
// Content:
// Ћексикон - определени¤ форм местоимени¤ I дл¤ английского раздела —ловар¤.
//
// 31.05.2012 - добавил рефлексивную форму "ourself"
// -----------------------------------------------------------------------------
//
// CD->19.02.2005
// LC->31.05.2012
// --------------


#include "sg_defs.h"

automat sg
{

 entry I : ENG_PRONOUN
 {

  NOUN_FORM:BASIC |{
                    // —убъектные формы - выступают в роли подлежащего.
                    CASE:NOMINATIVE |{
                                      PERSON:1 NUMBER:SINGLE { I }
                                      PERSON:1 NUMBER:PLURAL { WE }   

                                      PERSON:2 NUMBER:PLURAL { YOU }

                                      PERSON:2 NUMBER:SINGLE { THOU }
                                      PERSON:2 NUMBER:PLURAL { YE }   
 
                                      PERSON:3 NUMBER:SINGLE GENDER { HE SHE IT }
                                      PERSON:3 NUMBER:PLURAL        { THEY      }   
                                     }

                    // ќбъектные формы - пр¤мое дополнение и именна¤ часть предложной фразы
                    CASE:PREPOSITIVE |{
                                       PERSON:1 NUMBER:SINGLE { ME }
                                       PERSON:1 NUMBER:PLURAL { US }   
 
                                       PERSON:2 NUMBER:PLURAL { YOU }
                                       
                                       PERSON:2 NUMBER:SINGLE { THEE }
 
                                       PERSON:3 NUMBER:SINGLE GENDER { HIM HER IT }
                                       PERSON:3 NUMBER:PLURAL        { THEM       }   
                                      }
                   }

  // јтрибутивные формы - выступают в роли правого определени¤ дл¤ существительного.
  NOUN_FORM:POSSESSIVE |{
                         PERSON:1 NUMBER:SINGLE PRONOUN_FORM { MY  MINE MYSELF }
                         PERSON:1 NUMBER:PLURAL PRONOUN_FORM { OUR OURS OURSELVES }
                         PERSON:1 NUMBER:PLURAL PRONOUN_FORM:REFLEXIVE { ourself }

                         PERSON:2 NUMBER:SINGLE PRONOUN_FORM { YOUR  YOURS YOURSELF }
                         PERSON:2 NUMBER:PLURAL PRONOUN_FORM { YOUR  YOURS YOURSELVES }
                         PERSON:2 NUMBER:SINGLE PRONOUN_FORM { THY Thine THYSELF }

                         PERSON:3 NUMBER:SINGLE GENDER:MASCULINE PRONOUN_FORM { HIS HIS HIMSELF }
                         PERSON:3 NUMBER:SINGLE GENDER:FEMININE  PRONOUN_FORM { HER HERS HERSELF }
                         PERSON:3 NUMBER:SINGLE GENDER:NEUTRAL   PRONOUN_FORM { ITS ITS ITSELF }

                         PERSON:3 NUMBER:PLURAL PRONOUN_FORM { THEIR THEIRS THEMSELVES }
                        }
 }

 entry WHO : ENG_PRONOUN
 {
  NOUN_FORM:BASIC CASE:NOMINATIVE PERSON:3 NUMBER:SINGLE { WHO }
  NOUN_FORM:BASIC CASE:PREPOSITIVE{ WHOM }
  NOUN_FORM:POSSESSIVE { WHOSE }
 }
}

