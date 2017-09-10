#include "eng_sa_adv_macros.inc"

// ***************************************************

// Наречия и наречные группы, которые могут появляться сразу после
// глагола и быть единственными после него.

patterns AdvAfterVerb1 export { node:root_node }
pattern AdvAfterVerb1 { AdvPostfix:export {node:root_node} }
pattern AdvAfterVerb1 { AdvCompPhrase:export {node:root_node} }
pattern AdvAfterVerb1 { AdverbialPhrase:export {node:root_node} }
pattern AdvAfterVerb1 { GerundAdvPhrase:export {node:root_node} }




wordentry_set PeculiarModals=
{
 eng_verb:do{},
 eng_auxverb:will{},
 eng_auxverb:shall{},
 eng_beverb:be{},
 eng_auxverb:can{},
 eng_verb:have{},
 eng_auxverb:must{},
 eng_auxverb:should{},
 eng_auxverb:may{}
}


// Глаголы, которые могут выступать в роли модальных с присоединением голого инфинитива.
patterns VerbsWithBareInf export { node:root_node PERSON NUMBER }
pattern VerbsWithBareInf
{
 v=eng_verb:*{ VERB_FORM:UNDEF VERB_SLOTS:ModalDirect ~PeculiarModals } : export { node:root_node PERSON NUMBER }
 not=eng_particle:not{}
} : links { v.<NEGATION_PARTICLE>not }



// --------------
// PRESENT TENSE
// --------------

// **************************************************************************


