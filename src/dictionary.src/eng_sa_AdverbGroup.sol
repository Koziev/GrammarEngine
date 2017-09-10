// Наречия, которые могут быть пост-модификаторами наречий
wordentry_set EngAdv4Adv2 =
{
 eng_adverb:enough{}
}

// --------------------------------------------------------------------------

#region CompoundAdv
patterns CompoundAdv { language=English } export { node:root_node ADJ_FORM MODIF_TYPE COMPARABILITY }

pattern CompoundAdv
{
 eng_adverb:*{} : export { node:root_node ADJ_FORM MODIF_TYPE COMPARABILITY }
}

pattern CompoundAdv
{
 p=eng_compound_preadv:*{}
 t='-'{ [-5]tokenizer_flag:word_conjunction }
 n=eng_adverb:*{} : export { node:root_node ADJ_FORM MODIF_TYPE COMPARABILITY }
} : links { n.<COMPOUND_PREFIX>t.p }
  

// наречие в кавычках etc.
pattern CompoundAdv
{
 q1=OpeningQuote
 n=CompoundAdv : export { node:root_node ADJ_FORM MODIF_TYPE COMPARABILITY }
 q2=ClosingQuote
} : links
{
 n.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}

#endregion CompoundAdv


// --------------------------------------------------------------------------

patterns Adv { language=English } export { node:root_node MODIF_TYPE  ADJ_FORM }

pattern Adv
{
 CompoundAdv{ADJ_FORM:BASIC} : export { node:root_node MODIF_TYPE  ADJ_FORM }
}


// Для наречных паттернов длинее 1 наречия
patterns Adv123 { language=English } export { node:root_node MODIF_TYPE ADJ_FORM }

pattern Adv
{
 Adv123 : export { node:root_node MODIF_TYPE ADJ_FORM }
}


// аналитические сравнительные и превосходные формы наречий 

pattern Adv123
{
 a1=eng_adverb:most{}
 a2=CompoundAdv{ COMPARABILITY:ANALYTIC ADJ_FORM:BASIC } : export{ node:root_node MODIF_TYPE ADJ_FORM }
} : links { a2.<ATTRIBUTE>a1 }
  : ngrams { 1 }


pattern Adv123
{
 a1=eng_adverb:little{adj_form:superlative}
 a2=CompoundAdv{ COMPARABILITY:ANALYTIC ADJ_FORM:BASIC } : export{ node:root_node MODIF_TYPE ADJ_FORM }
} : links { a2.<ATTRIBUTE>a1 }
  : ngrams { 1 }


// at least partially
pattern Adv123
{
 prep=eng_prep:at{}
 a1=eng_adverb:little{adj_form:superlative}
 a2=CompoundAdv{ ADJ_FORM:BASIC } : export{node:root_node MODIF_TYPE ADJ_FORM }
} : links { a2.<ATTRIBUTE>prep.<NEXT_COLLOCATION_ITEM>a1 }
  : ngrams { 1 }


// -----------------------------------------------------------------

word_set AuxComparAdverbs = 
{
 'less',
 'more'
}

patterns AdvComp { language=English } export { node:root_node  ADJ_FORM MODIF_TYPE }


// They work better
pattern AdvComp
{
 CompoundAdv{ ADJ_FORM:COMPARATIVE }:export{ node:root_node ADJ_FORM MODIF_TYPE }
}

// much better
pattern AdvComp
{
 a1=CompoundAdv{ [-5]MODIF_TYPE:COMPAR_ADV }
 a2=CompoundAdv{ ADJ_FORM:COMPARATIVE } : export{node:root_node ADJ_FORM MODIF_TYPE }
} : links { a2.<ATTRIBUTE>a1 }
  : ngrams { 1 }


// He works more accurately
pattern AdvComp
{
 a1=eng_adverb:more{}
 a2=CompoundAdv{ COMPARABILITY:ANALYTIC ADJ_FORM:BASIC }:export{node:root_node ADJ_FORM MODIF_TYPE }
} : links { a2.<ATTRIBUTE>a1 }
  : ngrams { 1 }


// He works less accurately
pattern AdvComp
{
 a1=eng_adverb:little{ ADJ_FORM:COMPARATIVE }
 a2=CompoundAdv{ COMPARABILITY:ANALYTIC ADJ_FORM:BASIC }:export{node:root_node ADJ_FORM MODIF_TYPE }
} : links { a2.<ATTRIBUTE>a1 }
  : ngrams { 1 }


  
patterns AdvComp2 { language=English } export { node:root_node MODIF_TYPE ADJ_FORM }

// Margaret sings better
pattern AdvComp2
{
 a=AdvComp : export { node:root_node MODIF_TYPE ADJ_FORM }
}

// Margaret sings better than Mary
//                ^^^^^^^^^^^^^^^^
pattern AdvComp2
{
 a=AdvComp : export { node:root_node MODIF_TYPE ADJ_FORM }
 conj=eng_conj:than{}
 obj=ComparativeObj
}
: links { a.<RIGHT_COMPARISON_Y>conj.<OBJECT>obj }
: ngrams { 1 }


// ***********************************
// цепочки наречий с модификаторами
// ***********************************

// ----------------------------------------------------------------------

#region AdvModifier
patterns AdvModifier export { node:root_node }

pattern AdvModifier
{
 CompoundAdv{ [-5]ADJ_FORM:BASIC [-5]MODIF_TYPE:ADV } : export { node:root_node }
}

// Neutrinos move very very fast
//                ^^^^^^^^^
pattern AdvModifier
{
 a11=eng_adverb:very{}
 a12=eng_adverb:very{} : export { node:root_node }
}
: links { a12.<ATTRIBUTE>a11 }
: ngrams { 1 }


// It moves very, very slowly
//          ^^^^^^^^^^
pattern AdvModifier
{
 a11=eng_adverb:very{} : export { node:root_node }
 comma=','
 a12=eng_adverb:very{}
} : links { a11.<PUNCTUATION>comma.<ATTRIBUTE>a12 }
  : ngrams { 1 } // предотвращаем разделение на два отдельных наречия very(very) + fast

// He works much more accurately
//          ^^^^^^^^^
pattern AdvModifier
{
 a0=eng_adverb:much{}
 a1=eng_adverb:more{} : export { node:root_node }
} : links { a1.<ATTRIBUTE>a0 }
  : ngrams { 2 }


// The east coast beaches are more often muddy.
//                            ^^^^
pattern AdvModifier
{
 eng_adverb:more{} : export { node:root_node }
}
  
  
pattern AdvModifier
{
 q1=OpeningQuote
 n=AdvModifier : export { node:root_node }
 q2=ClosingQuote
} : links
{
 n.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}
  
#endregion AdvModifier

// ----------------------------------------------------------------------


// He arrived too soon.
pattern Adv123
{
 a1=AdvModifier
 a2=CompoundAdv{adj_form:basic}:export{ node:root_node MODIF_TYPE ADJ_FORM }
}
: links { a2.<ATTRIBUTE>a1 }
: ngrams { 1 eng_adv_adv_score(a1,a2) }




// Постмодификатор.
// I cannot run fast enough.
pattern Adv123
{
 a2=CompoundAdv{ adj_form:basic AdvWithEnoughPostfix }:export{ node:root_node MODIF_TYPE ADJ_FORM }
 a1=EngAdv4Adv2
} : links { a2.<ATTRIBUTE>a1 }
  : ngrams { 1 }



// -----------------------------------------------------

// наречия, присоединяемые к глаголам справа. постфиксы (наречные частицы) сюда не включены.
patterns AdvPostfix { language=English } export { node:root_node }

// В этом списке должны быть наречные частицы-постфиксы, которые
// присоединяются к глаголу с дополнительными проверками отдельно.
wordentry_set AdvCannotBeVerbPostfix=
{
 eng_adverb:that{},
 eng_adverb:very{} // это наречие тоже не может быть использовано
}

pattern AdvPostfix
{
 CompoundAdv{ adj_form:basic ~AdvCannotBeVerbPostfix } : export { node:root_node }
}


// Многословные агрегаты (наречия со своими модификаторами)
pattern AdvPostfix
{
 Adv123{ ~AdvCannotBeVerbPostfix } : export { node:root_node }
}


// It ran faster
pattern AdvPostfix
{
 AdvComp2 : export { node:root_node }
}


// -----------------------------------------------------


patterns Adv0 { language=English } export { node:root_node MODIF_TYPE ADJ_FORM }
pattern Adv0 { Adv:export{ node:root_node MODIF_TYPE ADJ_FORM } }
pattern Adv0 { AdvComp:export{ node:root_node MODIF_TYPE ADJ_FORM } }





patterns NounGrpWithoutArticle export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }



// ------------------------------------- 
// Логические выражения с наречиями
// -------------------------------------

patterns AdvLogic { language=English } export { node:root_node ADJ_FORM MODIF_TYPE }

// once or twice, sooner or later
pattern AdvLogic
{
 a1=Adv0:export{node:root_node  ADJ_FORM MODIF_TYPE }
 conj=eng_conj:and{}
 a2=Adv0
} : links { a1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>a2 }

// Again and again. God is infinitely and unchangeably good.
pattern AdvLogic
{
 a1=Adv0 : export { node:root_node ADJ_FORM MODIF_TYPE }
 conj=eng_conj:or{}
 a2=Adv0
} : links { a1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>a2 }

// slowly but surely
pattern AdvLogic
{
 a1=Adv0:export{node:root_node  ADJ_FORM MODIF_TYPE }
 conj=eng_conj:but{}
 a2=Adv0
} : links { a1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>a2 }

// I solved the problem theoretically rather than practically.
pattern AdvLogic
{
 a1=Adv0:export{node:root_node ADJ_FORM MODIF_TYPE }
 conj1=eng_adverb:rather{}
 conj2=eng_conj:than{}
 a2=Adv0
} : links { a1.<RIGHT_LOGIC_ITEM>conj1.<NEXT_COLLOCATION_ITEM>conj2.<NEXT_COLLOCATION_ITEM>a2 }

// His chapters are arranged thematically, not chronologically.
pattern AdvLogic
{
 a1=Adv0:export{node:root_node ADJ_FORM MODIF_TYPE }
 comma=','
 conj=eng_particle:not{}
 a2=Adv0
} : links { a1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>a2 }


pattern AdvPostfix { AdvLogic : export { node:root_node } }

// -------------------------

patterns AdvGroup { language=English } export { node:root_node MODIF_TYPE ADJ_FORM }

pattern AdvGroup { Adv0:export{ node:root_node MODIF_TYPE ADJ_FORM } }
pattern AdvGroup { AdvLogic:export{node:root_node MODIF_TYPE ADJ_FORM } }

// He never even fails
// This dictionary will never even be virtually complete.
pattern AdvGroup
{
 a1=eng_adverb:never{}:export{node:root_node MODIF_TYPE ADJ_FORM }
 a2=eng_adverb:even{}
} : links { a1.<ATTRIBUTE>a2 }

// The city never ever sleeps
pattern AdvGroup
{
 a1=eng_adverb:never{}:export{node:root_node MODIF_TYPE ADJ_FORM }
 a2=eng_adverb:ever{} 
} : links { a1.<ATTRIBUTE>a2 }


// It ran faster
pattern AdvGroup
{
 AdvComp2 : export { node:root_node MODIF_TYPE ADJ_FORM }
}



pattern AdvGroup
{
 q1=OpeningQuote
 n=AdvGroup : export { node:root_node MODIF_TYPE ADJ_FORM }
 q2=ClosingQuote
} : links
{
 n.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}



// ---------------------------------------------------------------

// Простое наречие (возможно с модификатором), присоединяемое справа к глаголу.
patterns SimplePostfixAdverb4Verb { language=English } export { node:root_node }


wordentry_set CantBePostfixVerbModifier=
{
 eng_adverb:that{},
 eng_adverb:so{},
 eng_adverb:rather{},
 eng_adverb:very{}
}


pattern SimplePostfixAdverb4Verb
{
 Adv0{ ~CantBePostfixVerbModifier }:export { node:root_node }
}

// ------------------------------------------------------------------------
// Наречие внутри группы составной связки или сложного глагольного времени:
// He has already gone home.
//        ^^^^^^^
patterns V_ADV_BETWEEN export { node:root_node }
pattern V_ADV_BETWEEN
{
 AdvGroup{ ~CanBeAdverbsAfterDo ~CannotBeBeforeVerb } : export { node:root_node }
} 

pattern V_ADV_BETWEEN
{
 CompoundAdv : export { node:root_node }
} : ngrams { -5 }

// -------------------------------------------------------------------------

// Группа наречий в роли левого модификатора глагола:
// The Confederacy's capital was initially located at Montgomery.
//                               ^^^^^^^^^

patterns AdvLeftModifier4Verb export { node:root_node }

wordentry_set NotLeftVerbModif = { eng_adverb:to{} }

pattern AdvLeftModifier4Verb
{
 AdvGroup{ /*[-1]ADJ_FORM:BASIC*/ [-2]MODIF_TYPE:VERB ~NotLeftVerbModif } : export { node:root_node }
}

// ---------------------------------------------------------


patterns AdvRightModifier4Verb export { node:root_node }

pattern AdvRightModifier4Verb
{
 AdvGroup{ [-1]MODIF_TYPE:VERB } : export { node:root_node }
}




// --------------------------------------------------------------------------

// Группа наречий в роли модификатора прилагательного

patterns AdvModifier4Adj export { node:root_node }

// He is slightly mad
//       ^^^^^^^^
// Organically certified berries are becoming more widely available.
//                                            ^^^^^^^^^^^
pattern AdvModifier4Adj
{
 AdvGroup { adj_form:basic [-2]MODIF_TYPE:ADJ /*EngAdv4Adj*/ } : export { node:root_node }
}


