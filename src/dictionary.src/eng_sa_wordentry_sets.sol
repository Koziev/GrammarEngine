word_set WhWords= {
                   'what', // What do you sing?
                   'why', // Why do you sing?
                   'where', // Where do you live?
                   'who', // Who is your friend?
                   'when', // When do you work?
                   'whom', // Whom do you love?
                   'how' // How do you sing?
                  }


// наречия, которые выступают в роли детерминантов для существительных.
wordentry_set SingDetAdverbs = {
                                eng_adverb:much{}, // Much money is spent for defence. There is much milk in the jug.
                                eng_adverb:"so much"{}, // I have so much work to do.
                                eng_adverb:"a little"{}, // We all need a little sugar!
                                eng_adverb:"how many"{}
                               }



wordentry_set AuxEngVerbs=
{
 eng_verb:do{},
 eng_auxverb:will{},
 eng_beverb:be{},
 eng_auxverb:can{},
 eng_verb:have{},
 eng_auxverb:must{},
 eng_auxverb:should{},
 eng_auxverb:may{},
 eng_verb:need{}
}

wordentry_set SpecialAuxVerbsED=
{
 eng_auxverb:may{},
 eng_beverb:be{},
 eng_verb:do{},
 eng_verb:have{},
 eng_verb:dare{},
 eng_verb:need{},
 eng_beverb:be_not{},
 eng_verb:"don't"{},
 eng_verb:"haven't"{},
 eng_auxverb:will{},
 eng_auxverb:can{},
 eng_auxverb:cannot{},
 eng_auxverb:would_not{},
 eng_auxverb:should_not{}
}

wordentry_set ModalCopulaVerbs =
{
 eng_auxverb:can{},
 eng_auxverb:must{},
 eng_auxverb:should{},
 eng_auxverb:may{},
 eng_auxverb:would{}
}

wordentry_set ModalCopulaVerbsNot =
{
 eng_auxverb:cannot{},
 eng_auxverb:would_not{},
 eng_auxverb:should_not{}
}



// некоторые наречия не могут стоять перед глаголом.
wordentry_set CannotBeBeforeVerb=
{
 eng_adverb:like{},
 eng_adverb:much{},
 eng_adverb:very{},
 eng_adverb:"a little"{},
 eng_adverb:"how many"{},
 eng_adverb:little{},
 eng_adjective:many{},
 eng_adverb:alone{},
 eng_adverb:soon{},
 eng_adverb:in{},
 eng_adverb:too{}
}

