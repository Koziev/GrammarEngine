// CD->17.04.2012
// LC->06.11.2015

patterns SVt_Clause export { node:root_node }

pattern SVt_Clause
{
 PredicateGroup0{ SUBJ_LINKED:1 WORD_ORDER:S_V ~TENSE:IMPERATIVE } : export{ node:root_node }
}


/*
// He likes the song that I sing
pattern SVt_Clause
{
 Subject=Sbj_1st_Singular
 Predicate=V_Present_1st_Singular{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
} : links { Predicate.<SUBJECT>Subject }


// This is the boy I see on Friday
pattern SVt_Clause
{
 Subject=Sbj_1st_Singular
 Predicate=V_Present_1st_Singular{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
 a=AdverbialPhrase
} : links { Predicate.{
                       <SUBJECT>Subject
                       <ATTRIBUTE>a
                      } }



// I give you the key I use today
pattern SVt_Clause
{
 Subject=Sbj_1st_Singular
 Predicate=V_Present_1st_Singular{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
 a=SVt_Clause_ADV
} : links { Predicate.{
                       <SUBJECT>Subject
                       <ATTRIBUTE>a
                      } }



// This is the boy I see on the picture
pattern SVt_Clause
{
 Subject=Sbj_1st_Singular
 Predicate=V_Present_1st_Singular{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
 a=PreposPhrase{ verb_prep( Predicate.root_node, _.prepos ) }
} : links { Predicate.{
                       <SUBJECT>Subject
                       <ATTRIBUTE>a
                      } }





// I like the song that Margaret sings
pattern SVt_Clause
{
 Subject=Sbj_3st_Singular
 Predicate=V_Present_3st_Singular{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
} : links { Predicate.<SUBJECT>Subject }


// This is the boy she sees on Friday
pattern SVt_Clause
{
 Subject=Sbj_3st_Singular
 Predicate=V_Present_3st_Singular{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
 a=AdverbialPhrase
} : links { Predicate.{
                       <SUBJECT>Subject
                       <ATTRIBUTE>a
                      } }

// I give you the key he uses today
pattern SVt_Clause
{
 Subject=Sbj_3st_Singular
 Predicate=V_Present_3st_Singular{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
 a=SVt_Clause_ADV
} : links { Predicate.{
                       <SUBJECT>Subject
                       <ATTRIBUTE>a
                      } }



// This is the boy she sees on the picture
pattern SVt_Clause
{
 Subject=Sbj_3st_Singular
 Predicate=V_Present_3st_Singular{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
 a=PreposPhrase{ verb_prep( Predicate.root_node, _.prepos ) }
} : links { Predicate.{
                       <SUBJECT>Subject
                       <ATTRIBUTE>a
                      } }


// I like the song that girls sing
pattern SVt_Clause
{
 Subject=Sbj_Plural
 Predicate=V_Present_Plural{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
} : links { Predicate.<SUBJECT>Subject }


// I like the song that girls sing on Friday
pattern SVt_Clause
{
 Subject=Sbj_Plural
 Predicate=V_Present_Plural{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
 a=AdverbialPhrase
} : links { Predicate.{
                       <SUBJECT>Subject
                       <ATTRIBUTE>a
                      } }


// I give you the key we use today
pattern SVt_Clause
{
 Subject=Sbj_Plural
 Predicate=V_Present_Plural{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
 a=SVt_Clause_ADV
} : links { Predicate.{
                       <SUBJECT>Subject
                       <ATTRIBUTE>a
                      } }



// This is the boy we see on the picture
pattern SVt_Clause
{
 Subject=Sbj_Plural
 Predicate=V_Present_Plural{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
 a=PreposPhrase{ verb_prep( Predicate.root_node, _.prepos ) }
} : links { Predicate.{
                       <SUBJECT>Subject
                       <ATTRIBUTE>a
                      } }





// I liked the song that Margaret sang
pattern SVt_Clause
{
 Subject=Sbj_Singular
 Predicate=V_Past_Singular{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
} : links { Predicate.<SUBJECT>Subject }


// This is the boy I met on Friday
pattern SVt_Clause
{
 Subject=Sbj_Singular
 Predicate=V_Past_Singular{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
 a=AdverbialPhrase
} : links { Predicate.{
                       <SUBJECT>Subject
                       <ATTRIBUTE>a
                      } }

// I give you the key I found yesterday
pattern SVt_Clause
{
 Subject=Sbj_Singular
 Predicate=V_Past_Singular{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
 a=SVt_Clause_ADV
} : links { Predicate.{
                       <SUBJECT>Subject
                       <ATTRIBUTE>a
                      } }



// This is the boy I met in the classroom
pattern SVt_Clause
{
 Subject=Sbj_Singular
 Predicate=V_Past_Singular{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
 a=PreposPhrase{ verb_prep( Predicate.root_node, _.prepos ) }
} : links { Predicate.{
                       <SUBJECT>Subject
                       <ATTRIBUTE>a
                      } }




// He likes the songs that we sang
//                         ^^^^^^^
pattern SVt_Clause
{
 Subject=Sbj_Plural
 Predicate=V_Past_Plural{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
} : links { Predicate.<SUBJECT>Subject }



// I like the song that girls sang on Friday
pattern SVt_Clause
{
 Subject=Sbj_Plural
 Predicate=V_Past_Plural{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
 a=AdverbialPhrase
} : links { Predicate.{
                       <SUBJECT>Subject
                       <ATTRIBUTE>a
                      } }

// I give you the key we found yesterday
pattern SVt_Clause
{
 Subject=Sbj_Plural
 Predicate=V_Past_Plural{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
 a=SVt_Clause_ADV
} : links { Predicate.{
                       <SUBJECT>Subject
                       <ATTRIBUTE>a
                      } }




// This is the boy we met in the classroom
pattern SVt_Clause
{
 Subject=Sbj_Plural
 Predicate=V_Past_Plural{TRANSITIVITY:TRANSITIVE}:export{ node:root_node }
 a=PreposPhrase{ verb_prep( Predicate.root_node, _.prepos ) }
} : links { Predicate.{
                       <SUBJECT>Subject
                       <ATTRIBUTE>a
                      } }
*/
