// Обычная концовка предложения - точка, хотя могут быть варианты, в том числе
// отсутствие явного терминатора.
word_set SentenceTerminators={'.','!','...',':',';','?'}

pattern SentenceEnd
{
 ПУНКТУАТОР:*{ [-5]SentenceTerminators } : export{node:root_node}
}

// I do agree!!
// Blocking is achieved by restricting randomization..
pattern SentenceEnd
{
 p1=ПУНКТУАТОР:*{}
 p2=ПУНКТУАТОР:*{} : export{node:root_node}
} : links { p2.<PUNCTUATION>p1 }



// You are ready, aren't you?
pattern SentenceEnd export { node:root_node }
{
 comma=','
 v=eng_beverb:be_not{}
 p=eng_pronoun:I{ CASE:NOMINATIVE }
 f='?':export{node:root_node}
} : links { f.<NEXT_COLLOCATION_ITEM>comma.<NEXT_COLLOCATION_ITEM>v.<SUBJECT>p }

// You sleep, don't you?
pattern SentenceEnd export { node:root_node }
{
 comma=','
 v=eng_verb:"don't"{}
 p=eng_pronoun:I{ CASE:NOMINATIVE }
 f='?':export{node:root_node}
} : links { f.<NEXT_COLLOCATION_ITEM>comma.<NEXT_COLLOCATION_ITEM>v.<SUBJECT>p }


// You can write, cannot you?
pattern SentenceEnd export { node:root_node }
{
 comma=','
 v=eng_auxverb:cannot{}
 p=eng_pronoun:I{ CASE:NOMINATIVE }
 f='?':export{node:root_node}
} : links { f.<NEXT_COLLOCATION_ITEM>comma.<NEXT_COLLOCATION_ITEM>v.<SUBJECT>p }

// You have answered the question, haven't you?
pattern SentenceEnd export { node:root_node }
{
 comma=','
 v=eng_verb:"haven't"{}
 p=eng_pronoun:I{ CASE:NOMINATIVE }
 f='?':export{node:root_node}
} : links { f.<NEXT_COLLOCATION_ITEM>comma.<NEXT_COLLOCATION_ITEM>v.<SUBJECT>p }


// You will return it, won't you?
pattern SentenceEnd export { node:root_node }
{
 comma=','
 v=Will_Shall_Not
 p=eng_pronoun:I{ CASE:NOMINATIVE }
 f='?':export{node:root_node}
} : links { f.<NEXT_COLLOCATION_ITEM>comma.<NEXT_COLLOCATION_ITEM>v.<SUBJECT>p }


// Наречия с отбивкой запятой в качестве концовки.
wordentry_set AdvFinalizer=
{
 eng_adverb:though{}, // It might be unpleasant, though.
 eng_adverb:defenselessly{}, // The child was standing in the middle of the crossfire, defenselessly.
 eng_adverb:too{} // He has a Mercedes, too.
}


pattern SentenceEnd export { node:root_node }
{
 comma=',' : export{node:root_node}
 adv=AdvFinalizer
 fin=@optional(SentenceTerminators)
} : links
{
 comma.{
        <OPINION>adv
        ~<PUNCTUATION>fin
       }
}
: ngrams { -5 }



// ---------------------------------------------------------
// Дополнительные виды концовки предложения, обычно в виде
// наречия или наречного оборота, с отбивкой запятой.
// ---------------------------------------------------------

// They are coming, for certain.
pattern SentenceEnd
{
 comma=',' : export{node:root_node}
 prep=eng_prep:for{}
 a=eng_adjective:certain{}
 fin=@optional(SentenceTerminators)
} : links
{
 comma.{
        <PREPOS_ADJUNCT>prep.<NEXT_COLLOCATION_ITEM>a
        ~<PUNCTUATION>fin
       }
}


// I love sailing, especially on the open sea.
pattern SentenceEnd
{
 comma=',' : export{node:root_node}
 adv1=eng_adverb:*{}
 adv2=PreposPhrase
 fin=@optional(SentenceTerminators)
} : links
{
 comma.{
        <ATTRIBUTE>adv1.<PREPOS_ADJUNCT>adv2
        ~<PUNCTUATION>fin
       }
}

// ------------------------------------------------------

patterns SentenceCloser export { node:root_node }

// Don't make a noise, please.
pattern SentenceCloser
{
 comma=',':export{node:root_node}
 closer=eng_particle:Please{}
} : links { comma.<NEXT_COLLOCATION_ITEM>closer }


// Repair my shoes please
pattern SentenceCloser
{
 eng_particle:Please{}:export{node:root_node}
}


// С обращением.
// Come closer, my dear!
pattern SentenceCloser
{
 comma=',' : export { node:root_node }
 a=eng_pronoun:I{ NOUN_FORM:POSSESSIVE PRONOUN_FORM:PRE }
 n=eng_adjective:dear{}
} : links { comma.<NEXT_COLLOCATION_ITEM>n.<ATTRIBUTE>a }



pattern SentenceEnd
{
 c=SentenceCloser
 e=SentenceEnd : export { node:root_node }
} : links { e.<NEXT_COLLOCATION_ITEM>c }






