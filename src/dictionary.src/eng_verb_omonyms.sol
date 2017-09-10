automat sg
{
 omonym add eng_verb:lie{}

 // лежать горизонтально
 entry lie : ENG_VERB
 {
  OMONYM_RESOLUTION:1

  VERB_FORM:INF { lie   }
  VERB_FORM:S   { lies  }
  VERB_FORM:ED  { lay   }
  VERB_FORM:PP  { lain  }
  VERB_FORM:ING { lying }
 }

 // Лгать
 entry lie : ENG_VERB
 {
  OMONYM_RESOLUTION:2

  VERB_FORM:INF { lie   }
  VERB_FORM:S   { lies  }
  VERB_FORM:ED  { lied  }
  VERB_FORM:PP  { lied  }
  VERB_FORM:ING { lying }
 }

 omonym remove eng_verb:lie{}
}

