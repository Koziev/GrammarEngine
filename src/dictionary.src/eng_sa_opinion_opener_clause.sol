// Предложения с моделью I wish I could go home now.

/*
// Вводный клоз.
patterns OpinionOpeningSubclause { language=English } export { node:root_node }

// I hope
pattern OpinionOpeningSubclause
{
 Subject=Sbj_1st_Singular
 Predicate=V_Present_1st_Singular{OpinionVerbsWithoutThat VOICE:ACTIVE }:export{ node:root_node }
} : links { Predicate.<SUBJECT>Subject }


// She says she is nothing like that in reality.
// ^^^^^^^^
pattern OpinionOpeningSubclause
{
 Subject=Sbj_3st_Singular
 Predicate=V_Present_3st_Singular{OpinionVerbsWithoutThat VOICE:ACTIVE }:export{ node:root_node }
} : links { Predicate.<SUBJECT>Subject }


// We trust you will behave better from now on.
pattern OpinionOpeningSubclause
{
 Subject=Sbj_Plural
 Predicate=V_Present_Plural{OpinionVerbsWithoutThat VOICE:ACTIVE }:export{ node:root_node }
} : links { Predicate.<SUBJECT>Subject }


// Tom said Fred might borrow his bicycle
pattern OpinionOpeningSubclause
{
 Subject=Sbj_Singular
 Predicate=V_Past_Singular{OpinionVerbsWithoutThat VOICE:ACTIVE}:export{ node:root_node }
} : links { Predicate.<SUBJECT>Subject }


// We hoped it won't rain
pattern OpinionOpeningSubclause
{
 Subject=Sbj_Plural
 Predicate=V_Past_Plural{OpinionVerbsWithoutThat VOICE:ACTIVE}:export{ node:root_node }
} : links { Predicate.<SUBJECT>Subject }
*/

// ---------------------

/*
// I hope it won't rain.
pattern SentenceClause
{
 opener=OpinionOpeningSubclause
 clause=V_Clause : export { node:root_node }
} : links { clause.<BEG_INTRO>opener }
*/

/*
// I think it may rain.
pattern SentenceClause
{
 opener=OpinionOpeningSubclause
 clause=VModal_Clause : export { node:root_node }
} : links { clause.<BEG_INTRO>opener }
*/

/*
// I think he is very smart.
pattern SentenceClause
{
 opener=OpinionOpeningSubclause
 clause=CopulaClause : export { node:root_node }
} : links { clause.<BEG_INTRO>opener }
*/
