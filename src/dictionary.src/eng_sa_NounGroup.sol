// ****************
// NOUNS
// LC->24.01.2016
// ****************

#region PersonName

patterns FAM_FirstName { language=English } export { node:root_node }
patterns FAM_MiddleName { language=English } export { node:root_node }
patterns FAM_LastName { language=English } export { node:root_node }
patterns FAM_Full { language=English } export { node:root_node }



// Проверяем, что слово является именем человека.
function int IsHumanName( tree w )
{
 // Запретим считать артикль THE именем при любых обстоятельствах
 // Georgia has an embassy in The Hague.
 //                           ^^^
 if( eq( wordform_entry(w), wordform_entry(ENG_ARTICLE:THE{}) ) )
  then return -100;


 // Предпочитаем существительные в единственном числе
 int id_pos =  wordform_class(w);
 if( eq( id_pos, ENG_NOUN ) )
  then
  {
   int numb_state = wordform_get_coord(w,NUMBER);
   if( eq( numb_state, NUMBER:SINGLE ) )
    then
    {
     tuple tx = thesaurus_collect( w, <в_класс> );

     if( gt( tuple_count(tx), 0 ) )
      then
      { 
       int n=tuple_count(tx);
       int i;
       for i=0 to arith_minus(n,1)
       {
        tree w2 = tuple_get( tx, i );
        int ie = wordform_entry(w2);
        string ename = entry_name(ie);
        if( eq( ie, wordform_entry( ThesaurusEntries:HypernymHumanName{} ) ) )
         then return 1;
       }
      }
 
     return 0;
    }
    else return -1;
  } 
  else return -2; 
}


// Личное имя
pattern FAM_FirstName
{
 @regex_strict("[\\@L][\\@l]+"){ IsHumanName(_) }:export{node:root_node}
}




function int IsEngName( tree w )
{
 // Предпочитаем существительные в единственном числе
 int id_pos =  wordform_class(w);
 if( eq( id_pos, ENG_NOUN ) )
  then
  {
   int numb_state = wordform_get_coord(w,NUMBER);
   if( eq( numb_state, NUMBER:SINGLE ) )
    then return 2;
    else return 1;
  } 
  else return 0; 
}


// Второе имя:
// They are named after Niels Henrik Abel.
//                            ^^^^^^
pattern FAM_MiddleName
{
 @regex_strict("[\\@L][\\@l]+"){ IsEngName(_) } : export { node:root_node }
}


// Фамилия:
// I know John Lamb.
//             ^^^^
pattern FAM_LastName
{
 @regex_strict("[\\@L][\\@l]+"){ IsEngName(_) } : export{node:root_node}
}





pattern FAM_Full
{
 n1=FAM_FirstName:export{node:root_node}
}

// I knew George Lamb.
//        ^^^^^^^^^^^
pattern FAM_Full
{
 n1=FAM_FirstName:export{node:root_node}
 n2=FAM_LastName
}
: links { n1.<RIGHT_NAME>n2 }
: ngrams { 1 }

// Alexander IX was chosen in his place.
//           ^^
pattern FAM_Full
{
 n1=FAM_FirstName:export{node:root_node}
 n2=@regex_strict("[IVXLM]+")
}
: links { n1.<RIGHT_NAME>n2 }
: ngrams { 1 }



// I knew George Martin Lamb.
pattern FAM_Full
{
 n1=FAM_FirstName:export{node:root_node}
 n2=FAM_MiddleName
 n3=FAM_LastName
}
: links { n1.<RIGHT_NAME>n2.<RIGHT_NAME>n3 }
: ngrams { 2 }


// Mr Lambert will return on Monday.
// ^^^^^^^^^^
pattern FAM_Full
{
 n1=@regex_strict("Mr"):export{node:root_node}
 n2=FAM_LastName
} : links { n1.<RIGHT_NAME>n2 }

// Barzaga, Jr. is the incumbent congressman.
// ^^^^^^^^^^^^
// TODO



#endregion PersonName

// ----------------------------------------------------------------------

// Составное существительное может включать в себя префиксы или части, отделенные дефисом.
#region CompoundNoun
patterns CompoundNoun { language=English }
 export
 {
  node:root_node
  NUMBER
  HAS_POSSESSIVE_FORM
  HAS_APPOSITIVE_SLOT
  ENG_PROPER_NOUN
  ENG_GENDER
  ENG_MASS_NOUN
  ENG_MODAL_NOUN
  CharCasing
 }

pattern CompoundNoun
{
 eng_noun:*{} : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT HAS_POSSESSIVE_FORM ENG_PROPER_NOUN ENG_GENDER ENG_MASS_NOUN ENG_MODAL_NOUN CharCasing }
}

// What are quasi-cash transactions?
//          ^^^^^^^^^^
pattern CompoundNoun
{
 p=eng_compound_prenoun:*{}
 t='-'{ [-5]tokenizer_flag:word_conjunction }
 n=eng_noun:*{} : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT HAS_POSSESSIVE_FORM ENG_PROPER_NOUN ENG_GENDER ENG_MASS_NOUN ENG_MODAL_NOUN CharCasing }
}
: links { n.<COMPOUND_PREFIX>t.<NEXT_COLLOCATION_ITEM>p }

  
// Префиксом составного может быть произвольная цепочка символов, которую мы тоже
// распознали как существительное:
// a 3'-end
// --^^----
pattern CompoundNoun
{
 p=eng_noun:*{}
 t='-'{ [-5]tokenizer_flag:word_conjunction }
 n=eng_noun:*{} : export { node:root_node NUMBER  HAS_APPOSITIVE_SLOT HAS_POSSESSIVE_FORM ENG_PROPER_NOUN ENG_GENDER ENG_MASS_NOUN ENG_MODAL_NOUN CharCasing }
}
: links { n.<COMPOUND_PREFIX>t.<NEXT_COLLOCATION_ITEM>p }
: ngrams { -5 }

// Asphalt/bitumen was used in early photographic technology.
// ^^^^^^^^^^^^^^^
// This diagram uses Q/total/width from the table.
//                   ^^^^^^^^^^^^^
pattern CompoundNoun
{
 p=eng_noun:*{}
 t='/'{}
 n=CompoundNoun : export { node:root_node NUMBER  HAS_APPOSITIVE_SLOT HAS_POSSESSIVE_FORM ENG_PROPER_NOUN ENG_GENDER ENG_MASS_NOUN ENG_MODAL_NOUN CharCasing }
}
: links { n.<RIGHT_LOGIC_ITEM>t.<NEXT_COLLOCATION_ITEM>p }




// No 19th-century candidate was elected.
//    ^^^^^^^^^^^^
pattern CompoundNoun
{
 p=ENG_NUMERAL:*{ NUMERAL_FORM:ORDINAL }
 t='-'{ [-5]tokenizer_flag:word_conjunction }
 n=eng_noun:*{} : export { node:root_node NUMBER  HAS_APPOSITIVE_SLOT HAS_POSSESSIVE_FORM ENG_PROPER_NOUN ENG_GENDER ENG_MASS_NOUN ENG_MODAL_NOUN CharCasing }
}
: links { n.<COMPOUND_PREFIX>t.<NEXT_COLLOCATION_ITEM>p }


// Their beak-like jaws are white.
//       ^^^^^^^^^
pattern CompoundNoun
{
 n=eng_noun:*{} : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT HAS_POSSESSIVE_FORM ENG_PROPER_NOUN ENG_GENDER ENG_MASS_NOUN ENG_MODAL_NOUN CharCasing }
 t='-'{ [-5]tokenizer_flag:word_conjunction }
 s=eng_adverb:like{}
}
: links { n.<NEXT_COLLOCATION_ITEM>t.<NEXT_COLLOCATION_ITEM>s }
: ngrams { 5 }


// Both these releases were full-frame.
//                          ^^^^^^^^^^
pattern CompoundNoun
{
 p=ENG_ADJECTIVE:*{ ADJ_FORM:BASIC }
 t='-'{ [-5]tokenizer_flag:word_conjunction }
 n=eng_noun:*{} : export { node:root_node NUMBER  HAS_APPOSITIVE_SLOT HAS_POSSESSIVE_FORM ENG_PROPER_NOUN ENG_GENDER ENG_MASS_NOUN ENG_MODAL_NOUN CharCasing }
}
: links { n.<COMPOUND_PREFIX>t.<NEXT_COLLOCATION_ITEM>p }
: ngrams { -1 }


// A tetrahedron is a 3-simplex.
//                    ^^^^^^^^^
pattern CompoundNoun
{
 p=num_word:*{}
 t='-'{ [-5]tokenizer_flag:word_conjunction }
 n=eng_noun:*{} : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT HAS_POSSESSIVE_FORM ENG_PROPER_NOUN ENG_GENDER ENG_MASS_NOUN ENG_MODAL_NOUN CharCasing }
}
: links { n.<COMPOUND_PREFIX>t.<NEXT_COLLOCATION_ITEM>p }


// Существительное в кавычках etc.
// It is also called simply 'thunder-plant'.
//                          ^^^^^^^^^^^^^^^
pattern CompoundNoun
{
 q1=OpeningQuote
 n=CompoundNoun : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT HAS_POSSESSIVE_FORM ENG_PROPER_NOUN ENG_GENDER ENG_MASS_NOUN ENG_MODAL_NOUN CharCasing }
 q2=ClosingQuote
} : links
{
 n.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}



#endregion CompoundNoun


// ----------------------------------------------------------------------

wordentry_set Or_And={
 eng_conj:or{},
 eng_conj:and{},
 eng_conj:plus{},
 eng_conj:"vs."{},
 eng_conj:versus{}, // Frequency domain versus time domain.
 eng_conj:vs{}
} 

// -----------------------------------------------------------------------------------------

#region NounAdjunct

// Группа существительного в роли левого определения для существительного:
// It is a gentlemen's club in London.
//         ^^^^^^^^^
//
// У этих существительных могут быть свои определения-прилагательные.
// Чтобы не возникло бесконечно рекурсии слева, мы соберем эту группу особыми правилами.

patterns NounAdjunct0 { language=English } export { node:root_node NUMBER HAS_POSSESSIVE_FORM ENG_PROPER_NOUN }


// Ice hockey began with the women's competition;
//                           ^^^^^^^
pattern NounAdjunct0
{
 CompoundNoun : export { node:root_node NUMBER HAS_POSSESSIVE_FORM ENG_PROPER_NOUN }
}


// He is resentful of his brother's charity.
//                    ^^^^^^^^^^^
pattern NounAdjunct0
{
 adj=ENG_PRONOUN:*{ NOUN_FORM:POSSESSIVE PRONOUN_FORM:PRE }
 n=CompoundNoun : export { node:root_node NUMBER HAS_POSSESSIVE_FORM ENG_PROPER_NOUN }
} : links { n.<ATTRIBUTE>adj }


// Левая группа прилагательного атрибутирует существительное:
//
// The Invisible Man's Revenge
//     ^^^^^^^^^^^^^
// This is a professional women's tennis tournament.
//           ^^^^^^^^^^^^^^^^^^
// List of civil rights leaders.
//         ^^^^^^^^^^^^
pattern NounAdjunct0
{
 a=PrenominalAdjGroup
 n=CompoundNoun:export{node:root_node NUMBER HAS_POSSESSIVE_FORM ENG_PROPER_NOUN }
}
: links { n.<ATTRIBUTE>a }
: ngrams { eng_adj_noun_score(a,n) }


// Группа страдательного причастия в роли левого определения существительного:
// The broken windows theory is a criminological theory of the norm-setting and signaling effect of urban disorder and vandalism on additional crime
//     ^^^^^^^^^^^^^^
pattern NounAdjunct0
{
 a=ParticipleAsAdj0
 n=CompoundNoun:export{node:root_node NUMBER HAS_POSSESSIVE_FORM ENG_PROPER_NOUN }
}
: links { n.<ATTRIBUTE>a }
: ngrams { eng_adj_noun_score(a,n) }



// Группы существительного в роли левого определения могут образовывать союзные
// конструкции, поэтому вводим промежуточный нетерминал для единичного определения.
patterns NounAdjunct1 { language=English } export { node:root_node NOUN_FORM }

// Существительное, находящееся в основном падеже (то есть не притяжательном):
// the tennis tournament begins on the Monday
//     ^^^^^^
pattern NounAdjunct1
{
 NounAdjunct0{ /*[-3]~ENG_PROPER_NOUN*/ [-3]NUMBER:SINGLE ~CannotBeNounAdjunct }:export{ node:root_node NOUN_FORM:BASIC }
}


// Притяжательная форма существительного, с согласованием по числу:
// Man's formula
// ^^^^^
// cats'
// ^^^^^
// Допускаем также рассогласование по числу в случае неправильных существительных:
// It is a gentlemen's club in London.
//         ^^^^^^^^^^^
pattern NounAdjunct1
{
 n=NounAdjunct0{ HAS_POSSESSIVE_FORM } : export{ node:root_node NOUN_FORM:POSSESSIVE }
 x=ENG_POSSESSION:*{ [-1]=n:NUMBER }
}
: links { n.<POSSESSION_POSTFIX>x }
: ngrams { 1 }


pattern NounAdjunct1
{
 n=NounAdjunct0{ ~HAS_POSSESSIVE_FORM } : export{ node:root_node NOUN_FORM:POSSESSIVE }
 x=ENG_POSSESSION:*{ [-1]=n:NUMBER }
}
: links { n.<POSSESSION_POSTFIX>x }
: ngrams { -5 }

// Притяжательная форма ФИО:
// William Cobbett's social views influenced Chesterton.
// ^^^^^^^^^^^^^^^^^
pattern NounAdjunct1
{
 n=FAM_Full : export{ node:root_node NOUN_FORM:POSSESSIVE }
 x=ENG_POSSESSION:*{ NUMBER:SINGLE }
}
: links { n.<POSSESSION_POSTFIX>x }
: ngrams { 2 }


// ---------------------------------------------------------------------

// Некоторые существительные могут атрибутировать существительное, даже находясь в форме множественного числа
// The arms control must be provided
// I work in the sales division
// Weapons violations charges are very serious
wordform_set PluralNounAsModifier=
{
 'securities'{class:eng_noun number:plural }, // mystical theories about the securities market
 'sales'{class:eng_noun number:plural },
 'weapons'{class:eng_noun number:plural },
 'violations'{class:eng_noun number:plural }
}

pattern NounAdjunct1
{ NounAdjunct0 { PluralNounAsModifier } :export { node:root_node NOUN_FORM:BASIC } }




// Теперь собираем полную группу существительных в роли левого определения.
// Используем восходящую сборку, чтобы не ограничивать число компонентов в перечислении.
//
// признак KEYFEATURE_REQUIRED:0 - в группу вошло хотя бы одно существительное
// признак KEYFEATURE_DESIRABLE:1 - в группу вошел хотя бы один союз

patterns NounAdjunctUp { bottomup }
export
{
 KEYFEATURE_DETECTED // есть союзный паттерн или перечисление через запятую
 KEYFEATURE_REQUIRED // =0 присоединено хотя бы одно существительное
 KEYFEATURE_DESIRABLE // есть союз
 NOUN_FORM // будем связывать только существительные в одной форме - либо базовая, либо притяжательная.
 node:root_node
}

pattern NounAdjunctUp
{
 NounAdjunct1:export{ KEYFEATURE_DETECTED:0 KEYFEATURE_REQUIRED:1 KEYFEATURE_DESIRABLE:0 NOUN_FORM node:root_node }
}

// Присоединяем элемент через запятую:
// Children's, Men's and Women's Shirt
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern NounAdjunctUp
{
 n1=NounAdjunctUp:export{ KEYFEATURE_DESIRABLE:0 NOUN_FORM node:root_node }
 comma=',' : export { KEYFEATURE_DETECTED:1 }
 n2=NounAdjunct1{ =n1:NOUN_FORM }:export { KEYFEATURE_REQUIRED:0 }
}
: links { n1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>n2 }


// Присоединяем элемент через союз:
// It features men's and women's singles;
//             ^^^^^^^^^^^^^^^^^
pattern NounAdjunctUp
{
 n1=NounAdjunctUp:export { NOUN_FORM node:root_node }
 conj=Or_And : export{ KEYFEATURE_DETECTED:1 KEYFEATURE_DESIRABLE:1 }
 n2=NounAdjunct1{ =n1:NOUN_FORM }:export{ KEYFEATURE_REQUIRED:0 }
}
: links { n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2 }
: ngrams { 1 }


// Финальный нетерминал - группа существительного в роли левого определения
patterns NounAdjunct { language=English } export { node:root_node }

// Одиночное существительное (со своим определением):
// People in the women's movement used it.
//               ^^^^^^^
pattern NounAdjunct
{
 NounAdjunct1 : export { node:root_node }
}

// The voice, to be sure, is neither man's nor woman's
//                           ^^^^^^^^^^^^^^^^^^^^^^^^^
pattern NounAdjunct
{
 conj1=eng_conj:neither{}
 n1=NounAdjunct1 : export { node:root_node }
 conj2=eng_conj:nor{}
 n2=NounAdjunct1
}
: links { n1.{ <PREFIX_CONJUNCTION>conj1 <RIGHT_LOGIC_ITEM>conj2.n2 } }

// Nobody knows yet what is either man's or woman's proper sphere
//                          ^^^^^^^^^^^^^^^^^^^^^^^
pattern NounAdjunct
{
 conj1=eng_conj:either{}
 n1=NounAdjunct1 : export { node:root_node }
 conj2=eng_conj:or{}
 n2=NounAdjunct1
}
: links { n1.{ <PREFIX_CONJUNCTION>conj1 <RIGHT_LOGIC_ITEM>conj2.n2 } }


// Both Man's and Woman's Candidate In Republican Polls.
// ^^^^^^^^^^^^^^^^^^^^^^
// Both cat and dog fleas are carriers of the common tapeworm parasite
// ^^^^^^^^^^^^^^^^
pattern NounAdjunct
{
 conj1=eng_conj:both{}
 n1=NounAdjunct1 : export { node:root_node }
 conj2=eng_conj:and{}
 n2=NounAdjunct1
}
: links { n1.{ <PREFIX_CONJUNCTION>conj1 <RIGHT_LOGIC_ITEM>conj2.n2 } }



// В группу входит минимум одно существительное и есть союзы:
// It features men's and women's singles;
//             ^^^^^^^^^^^^^^^^^
pattern NounAdjunct
{
 n=NounAdjunctUp{ KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:1 }:export{ node:root_node }
}


// Особо рассматриваем группу из нескольких существительных, связанных
// без использования союза. Небольшой штраф дает преимущество союзным конструкциям.
pattern NounAdjunct
{
 n=NounAdjunctUp{ KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:0 }:export{ node:root_node }
} : ngrams { -1 }

#endregion NounAdjunct

// ----------------------------------------------------------------------------------------

// Элементарное существительное со своими левыми определениями, но без детерминаторов (артиклей и т.д.)
#region NounGrpWithoutArticle

// Вспомогательный нетерминал для рекурсии по левым определениям и дополнениям.
patterns NounGrpWithoutArticle0 export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }

// В качестве затравки берем голое существительное.
pattern NounGrpWithoutArticle0
{
 CompoundNoun : export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }
}

// Vehicle steering was adversely affected.
//         ^^^^^^^^
pattern NounGrpWithoutArticle0
{
 eng_verb:*{ verb_form:ing } : export { NUMBER:SINGLE HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }
} : ngrams { -2 }


// Делаем левую рекурсию для присоединения определений,
// чтобы разбирать такие паровозы:
// As students at the United States Navy's elite fighter weapons school compete to be best in the class, one daring young pilot learns a few things from a civilian
//                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


// Oil extraction facilities were nationalized.
// ^^^^^^^^^^^^^^...
pattern NounGrpWithoutArticle0
{
 a=NounAdjunct
 n=NounGrpWithoutArticle0 : export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }
}
: links { n.<ATTRIBUTE>a }
: ngrams { eng_noun_noun_score(a,n) }

// Modern amphibians are all Lissamphibia.
// ^^^^^^...
pattern NounGrpWithoutArticle0
{
 a=PrenominalAdjGroup
 n=NounGrpWithoutArticle0 : export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }
}
: links { n.<ATTRIBUTE>a }
: ngrams { eng_adj_noun_score(a,n) }


// Examples of potentially confusing ambiguous mathematical expressions.
//             ^^^^^^^^^^^^^^^^^^^^^...
pattern NounGrpWithoutArticle0
{
 a=ParticipleAsAdj0
 n=NounGrpWithoutArticle0 : export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }
}
: links { n.<ATTRIBUTE>a }
: ngrams { eng_adj_noun_score(a,n) }



// Spinoza’s second knowledge involves reasoning plus emotions.
//           ^^^^^^
pattern NounGrpWithoutArticle0
{
 a=OrdinalNumber
 n=NounGrpWithoutArticle0 : export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }
}
: links { n.<ATTRIBUTE>a }
: ngrams { eng_adj_noun_score(a,n) }



// The last two volumes were published posthumously.
//          ^^^
// Three main areas of interest rapidly developed.
// ^^^^^...
// There are 95 printable characters in total.
//           ^^...
pattern NounGrpWithoutArticle0
{
 c=NounEnumerator
 n=NounGrpWithoutArticle0{ [-5]=c:NUMBER } : export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }
} : links { n.<ATTRIBUTE>c }


// Левый причастный оборот:
pattern NounGrpWithoutArticle0
{
 a=PastParticipleLeftGroup
 comma=','
 n=NounGrpWithoutArticle0 : export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }
}
: links { n.{ <ATTRIBUTE>a <PUNCTUATION>comma } }
: ngrams { eng_adj_noun_score(a,n) }


// ---------------------------------------------------



pattern NounGrpWithoutArticle
{
 NounGrpWithoutArticle0 : export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }
}



// Прилагательное в компаративе и суперлативе должно быть первым элементом в цепочке определений
// It is the best work
//           ^^^^
// He is my best friend
//          ^^^^
pattern NounGrpWithoutArticle
{
 a=AdjSuperlative2
 n=NounGrpWithoutArticle0 : export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }
}
: links { n.<ATTRIBUTE>a }
: ngrams { eng_adj_noun_score( a, n ) }





// A better chance of success.
//   ^^^^^^
// It's an inherently better method
//         ^^^^^^^^^^^^^^^^^
pattern NounGrpWithoutArticle
{
 a=AdjComparative2
 n=NounGrpWithoutArticle0 : export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }
}
: links { n.<ATTRIBUTE>a }
: ngrams { eng_adj_noun_score( a, n ) }


// the more curious fox
//     ^^^^^^^^^^^^
pattern NounGrpWithoutArticle
{
 d=eng_adverb:more{}
 a=eng_adjective:*{ adj_form:basic COMPARABILITY:ANALYTIC }
 n=NounGrpWithoutArticle0 : export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }
}
: links { n.<ATTRIBUTE>a.<ATTRIBUTE>d }
: ngrams { eng_adj_noun_score( a, n ) }


// It is the less curious fox
//           ^^^^^^^^^^^^
pattern NounGrpWithoutArticle
{
 d=eng_adverb:little{ adj_form:comparative }
 a=eng_adjective:*{ adj_form:basic COMPARABILITY:ANALYTIC }
 n=NounGrpWithoutArticle0 : export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }
}
: links { n.<ATTRIBUTE>a.<ATTRIBUTE>d }
: ngrams { eng_adj_noun_score( a, n ) }


// It is the most curious fox
//           ^^^^^^^^^^^^
pattern NounGrpWithoutArticle
{
 d=eng_adverb:most{}
 a=eng_adjective:*{ adj_form:basic COMPARABILITY:ANALYTIC }
 n=NounGrpWithoutArticle0 : export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }
}
: links { n.<ATTRIBUTE>a.<ATTRIBUTE>d }
: ngrams { eng_adj_noun_score( a, n ) }


// It is the least curious fox
//           ^^^^^^^^^^^^^
pattern NounGrpWithoutArticle
{
 d=eng_adverb:little{ adj_form:superlative }
 a=eng_adjective:*{ adj_form:basic COMPARABILITY:ANALYTIC }
 n=NounGrpWithoutArticle0 : export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }
}
: links { n.<ATTRIBUTE>a.<ATTRIBUTE>d }
: ngrams { eng_adj_noun_score( a, n ) }


// An 'edge dislocation' is shown.
//    ^^^^^^^^^^^^^^^^^^
pattern NounGrpWithoutArticle
{
 q1=OpeningQuote
 n=NounGrpWithoutArticle : export { NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN ENG_PROPER_NOUN ENG_MASS_NOUN node:root_node }
 q2=ClosingQuote
} : links
{
 n.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}



// -----------------------------------------------------------



patterns PluralNounWithoutArticle { language=English } export { node:root_node }
patterns SingularNounWithoutArticle { language=English } export { node:root_node }

// personal verb endings
pattern PluralNounWithoutArticle
{
 NounGrpWithoutArticle{ NUMBER:PLURAL } : export { node:root_node }
}

// Ambulance drivers are paramedical personnel.
//                       ^^^^^^^^^^^^^^^^^^^^^
pattern SingularNounWithoutArticle
{
 NounGrpWithoutArticle{ NUMBER:SINGLE } : export { node:root_node }
}

#endregion NounGrpWithoutArticle

// ----------------------------------------------------------------------------------------


#region Determiners                 

wordentry_set SingularIdentifier = {
                                    eng_article:a{}, // I am in a bad mood
                                    eng_article:the{},
                                    eng_adjective:this{},
                                    eng_adjective:that{},
                                    eng_numeral:one{},
                                    eng_adjective:another{}, // She gets another pet
                                    eng_adjective:some{}, // Drink some water! We all need some rest.
                                    eng_adjective:such{}, // I do such work
                                    eng_adjective:every{},
                                    eng_adjective:each{},
                                    eng_particle:no{} // We did no work today. I have no time.
                                   }


wordentry_set PluralIdentifier = {
                                  eng_article:the{},
                                  eng_adjective:these{}, // these men are called musicians
                                  eng_adjective:those{}, // We killed those men in their flying machines.
                                  eng_adjective:many{}, // We saw many dogs throughout Athens. I've lived here for many years. There were many people at the party. 
                                  eng_adjective:several{}, // I noticed several men
                                  eng_adjective:all{}, // all men are brothers
                                  eng_adjective:other{},
                                  eng_adjective:both{}, // I know both sides of the story
                                  eng_adjective:some{},
                                  eng_adjective:few{}, // few products are really original
                                  eng_particle:no{} // Spiders have no wings and no antennae.
                                 }

patterns DetAnySingular { language=English } export { node:root_node }



function bool IsUpperCased( tree w )
{
 return str_regex( to_string(w), "[A-Z][a-z]+" );
}



pattern DetAnySingular
{ SingularIdentifier:export{ node:root_node } }

// Much money is spent for defence. There is much milk in the jug.
pattern DetAnySingular
{ SingDetAdverbs:export{ node:root_node } }

patterns DetAnyPlural { language=English } export { node:root_node }

pattern DetAnyPlural
{ PluralIdentifier:export{ node:root_node } }

#endregion Determiners                 

// Существительное с артиклем, детерминатором (или без него, но со штрафом)
#region NounGroup0

patterns NounGroup0 export { node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }

// Имена собственные употребляются без артикля:
// Costa Rica has an embassy in Moscow.
//                              ^^^^^^
pattern NounGroup0
{
 NounGrpWithoutArticle{ ENG_PROPER_NOUN } : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
}


pattern NounGroup0
{
 NounGrpWithoutArticle{ ~ENG_PROPER_NOUN } : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
}
: ngrams { -1 } // штраф за отсутствие артикля и т.п.

// ------------------ ЕДИНСТВЕННОЕ ЧИСЛО ----------------

pattern NounGroup0
{
 d=DetAnySingular
 n=NounGrpWithoutArticle{ NUMBER:SINGLE } : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
}
: links { n.<ATTRIBUTE>d }


// I've got plenty of time.
//          ^^^^^^^^^^^^^^
pattern NounGroup0
{
 q=eng_noun:plenty{}:export{ node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
 p=eng_prep:of{}
 n=NounGrpWithoutArticle{ NUMBER:SINGLE }
}
: links { q.<PREPOS_ADJUNCT>p.<OBJECT>n }


// I have too much work to do.
//        ^^^^^^^^^^^^^
pattern NounGroup0
{
 x=eng_adverb:too{}
 y=eng_adverb:much{}
 n=NounGrpWithoutArticle{ NUMBER:SINGLE } : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
}
: links { n.<ATTRIBUTE>y.<ATTRIBUTE>x }

// England imports a great deal of oil.
//                 ^^^^^^^^^^^^^^^^^^^
pattern NounGroup0
{
 a=eng_adjective:great{}
 n=eng_noun:deal{}:export{ node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
 p=eng_prep:of{}
 n2=NounGrpWithoutArticle{ NUMBER:SINGLE }
} : links { n.{ <ATTRIBUTE>a <PREPOS_ADJUNCT>p.<OBJECT>n2 } }

// I have so much work to do.
//        ^^^^^^^^^^^^
pattern NounGroup0
{
 x=eng_adverb:so{}
 y=eng_adverb:much{}
 n=NounGrpWithoutArticle{ NUMBER:SINGLE } : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
} : links { n.<ATTRIBUTE>y.<ATTRIBUTE>x }

// We all need a little sugar!
//             ^^^^^^^^^^^^^^
pattern NounGroup0
{
 x=eng_article:a{}
 y=eng_adverb:little{}
 n=NounGrpWithoutArticle{ NUMBER:SINGLE } : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
} : links { n.{ <ATTRIBUTE>y <ATTRIBUTE>x } }


// It was such a beautiful day
//        ^^^^^^^^^^^^^^^^^^^^
pattern NounGroup0
{
 x=eng_adjective:such{}
 y=eng_article:a{}
 n=NounGrpWithoutArticle{ NUMBER:SINGLE } : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
} : links { n.{ <ATTRIBUTE>y <ATTRIBUTE>x } }

// ------------ МНОЖЕСТВЕННОЕ ЧИСЛО -----------------------

pattern NounGroup0
{
 d=DetAnyPlural
 n=NounGrpWithoutArticle{ NUMBER:PLURAL } : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
}
: links { n.<ATTRIBUTE>d }


// All the people are here.
// ^^^^^^^^^^^^^^
// I love all the girls.
//        ^^^^^^^^^^^^^
// All the dogs died.
// ^^^^^^^^^^^^
pattern NounGroup0
{
 a=eng_adjective:all{}
 d=eng_article:the{}
 n=NounGrpWithoutArticle{ NUMBER:PLURAL } : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
}
: links { n.{ <ATTRIBUTE>a <ATTRIBUTE>d } }
: ngrams { 4 }

// All the rest had fled.
// ^^^^^^^^^^^^
pattern NounGroup0
{
 a=eng_adjective:all{}
 d=eng_article:the{}
 n=NounGrpWithoutArticle{ NUMBER:SINGLE } : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
}
: links { n.{ <ATTRIBUTE>a <ATTRIBUTE>d } }
: ngrams { 4 }


// Not all fractures are painful.
// ^^^^^^^^^^^^^^^^^
pattern NounGroup0
{
 neg=eng_particle:not{}
 a=eng_adjective:all{}
 n=NounGrpWithoutArticle{ NUMBER:PLURAL } : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
} : links { n.<ATTRIBUTE>a.<NEGATION_PARTICLE>neg }


// I bought both the books for my class.
//          ^^^^^^^^^^^^^^
pattern NounGroup0
{
 x=eng_adjective:both{}
 y=eng_article:the{}
 n=NounGrpWithoutArticle{ NUMBER:PLURAL } : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
} : links { n.{ <ATTRIBUTE>x <ATTRIBUTE>y } }

// I saw so many dogs on my walk back home that I lost count
//       ^^^^^^^^^^^^
pattern NounGroup0
{
 x=eng_adverb:so{}
 y=eng_adjective:many{}
 n=NounGrpWithoutArticle{ NUMBER:PLURAL } : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
} : links { n.<ATTRIBUTE>y.<ATTRIBUTE>x }
: ngrams { 2 }

// Very many old people live alone.
// ^^^^^^^^^^^^^^^^^^^^
pattern NounGroup0
{
 x=eng_adverb:very{}
 y=eng_adjective:many{}
 n=NounGrpWithoutArticle{ NUMBER:PLURAL } : export { node:root_node NUMBER:PLURAL HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
} : links { n.<ATTRIBUTE>y.<ATTRIBUTE>x }

// There are too many mistakes in your exercises.
//           ^^^^^^^^^^^^^^^^^
pattern NounGroup0
{
 x=eng_adverb:too{}
 y=eng_adjective:many{}
 n=NounGrpWithoutArticle{ NUMBER:PLURAL } : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
}
: links { n.<ATTRIBUTE>y.<ATTRIBUTE>x }
: ngrams { 4 }


// I make a lot of mistakes. I've got a lot of questions. There were a lot of people at the party.
// A lot of people speak English.
// ^^^^^^^^^^^^^^^
pattern NounGroup0
{
 x=eng_article:a{}
 n=eng_noun:lot{} : export { node:root_node NUMBER:PLURAL HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
 p=eng_prep:of{}
 n2=NounGrpWithoutArticle{ NUMBER:PLURAL }
} : links { n.{
               <ATTRIBUTE>x
               <PREPOS_ADJUNCT>p.<OBJECT>n2
              } }


// There are a number of contributing factors.
//           ^^^^^^^^^^^^^^^...
// A large number of people gathered in the square.
// ^^^^^^^^^^^^^^^^^^^^^^^^
wordentry_set NumberOfNoun = { eng_noun:number{} }
pattern NounGroup0
{
 x=eng_article:a{}
 n=NounGrpWithoutArticle0{ NumberOfNoun } : export { node:root_node NUMBER:PLURAL HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
 p=eng_prep:of{}
 n2=NounGrpWithoutArticle{ NUMBER:PLURAL }
} : links { n.{
               <ATTRIBUTE>x
               <PREPOS_ADJUNCT>p.<OBJECT>n2
              } }
: ngrams { 1 }


// There are plenty of vacant seats here.
//           ^^^^^^^^^^^^^^^^^^^^^^
pattern NounGroup0
{
 n=eng_noun:plenty{} : export { node:root_node NUMBER:PLURAL HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
 p=eng_prep:of{}
 n2=NounGrpWithoutArticle{ NUMBER:PLURAL }
} : links { n.<PREPOS_ADJUNCT>p.<OBJECT>n2 }


// Only few products are really original
// ^^^^^^^^^^^^^^^^^
pattern NounGroup0
{
 x=eng_adverb:only{}
 y=eng_adjective:few{}
 n=NounGrpWithoutArticle{ NUMBER:PLURAL } : export { node:root_node NUMBER:PLURAL HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
} : links { n.<ATTRIBUTE>y.<ATTRIBUTE>x }


// A few people came to the party. A few golden coins.
pattern NounGroup0
{
 x=eng_article:a{}
 y=eng_adjective:few{}
 n=NounGrpWithoutArticle{ NUMBER:PLURAL } : export { node:root_node NUMBER:PLURAL HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
} : links { n.{ <ATTRIBUTE>y <ATTRIBUTE>x } }

// I see most other dogs
//       ^^^^^^^^^^^^^^^
pattern NounGroup0
{
 x=eng_adverb:most{}
 y=eng_adjective:other{}
 n=NounGrpWithoutArticle{ NUMBER:PLURAL } : export { node:root_node NUMBER:PLURAL HAS_APPOSITIVE_SLOT ENG_MODAL_NOUN }
} : links { n.{ <ATTRIBUTE>y <ATTRIBUTE>x } }



// --------------------------------------------------------



patterns AnyWord export { node:root_node }


// Разрешаем любые слова в роли именной группы при наличии артикля и т.д.
pattern NounGroup0
{
 d=DetAnySingular
 n=AnyWord : export { node:root_node NUMBER HAS_APPOSITIVE_SLOT:0 ENG_MODAL_NOUN }
}
: links { n.<ATTRIBUTE>d }
: ngrams { -10 }


#region Elective
// ЭЛЕКТИВНЫЕ КОНСТРУКЦИИ

// Конструкция с "most of xxx" имеет особенность формирования
// грамматического числа: оно берется из объекта.

wordentry_set HeadOfNumerative0=
{
 eng_noun:most{},
 eng_adjective:some{}, // Some of these drugs have been derived from opium
 eng_adjective:which{}, // Which of these elements is likely to be found in an organic compound?
 eng_adjective:both{}, // Both of these elastomers undergo strain crystallization.
 eng_adjective:all{}, // Samuel Weaver oversaw all of these reburials.
 eng_noun:number{} // A number of theories have been published.
}

patterns ElectiveHead export { node:root_node }

pattern ElectiveHead
{
 HeadOfNumerative0 : export { node:root_node }
}

// I bought some more of these deliciously sweet peaches
//          ^^^^^^^^^
pattern ElectiveHead
{
 mod=eng_adverb:some{}
 n=eng_adjective:many{} : export { node:root_node }
} : links { n.<ATTRIBUTE>mod }


// Элективная конструкция:
// One of the replaced frames was tilted;
// ^^^^^^^^...
pattern ElectiveHead
{
 eng_noun:one{} : export { node:root_node }
}
: ngrams { 1 }


// Much of this focuses on ambiguity tolerance.
// ^^^^^^^^^^^^
pattern ElectiveHead
{
 eng_adverb:much{} : export { node:root_node }
}
: ngrams { 1 }


// 600 of these were Parchamites
// ^^^
pattern ElectiveHead
{
 NumberGroup : export { node:root_node }
}
: ngrams { 1 }



patterns ElectiveTail export { NUMBER node:root_node }

// Вариант с группой местоимения:
// Most of us will agree with this view.
// ^^^^^^^^^^
pattern ElectiveTail
{
 PronounGroup : export { NUMBER node:root_node }
}

// Вариант с группой существительного:
// Most of the population lives along the coast.
// ^^^^^^^^^^^^^^^^^^^^^^
pattern ElectiveTail
{
 NounGroup : export { NUMBER node:root_node }
}



pattern NounGroup0 export { node:root_node NUMBER HAS_APPOSITIVE_SLOT (ENG_MODAL_NOUN) }
{
 d=ElectiveHead : export { node:root_node HAS_APPOSITIVE_SLOT:0 }
 p=eng_prep:of{}
 n=ElectiveTail : export { NUMBER }
}
: links { d.<PREPOS_ADJUNCT>p.<OBJECT>n }



// Единственное число для WHICH и ONE:
// Which of these elements is likely to be found in an organic compound?
// ^^^^^^^^....
// One of two subsets is commonly chosen.
// ^^^^^^^...
wordentry_set ElectiveHeadSing0=
{
 eng_adjective:which{},
 eng_numeral:one{}
}

pattern NounGroup0 export { node:root_node NUMBER HAS_APPOSITIVE_SLOT (ENG_MODAL_NOUN) }
{
 d=ElectiveHeadSing0 : export { node:root_node NUMBER:SINGLE HAS_APPOSITIVE_SLOT:0 }
 p=eng_prep:of{}
 n=ElectiveTail
}
: links { d.<PREPOS_ADJUNCT>p.<OBJECT>n }
: ngrams { 1 }



#endregion Elective


// Most are accessible by cyclists.
// ^^^^
pattern NounGroup0 export { node:root_node NUMBER HAS_APPOSITIVE_SLOT (ENG_MODAL_NOUN) }
{
 eng_noun:most{}: export { node:root_node NUMBER HAS_APPOSITIVE_SLOT:0 }
}

/*
// Одиночное числительное в роли именной группы:
// 141 were caught and executed.
// ^^^
pattern NounGroup0
{
 num_word:*{} : export { node:root_node NUMBER:PLURAL HAS_APPOSITIVE_SLOT:0 }
}
*/

// She died on February 1.
//             ^^^^^^^^^^
// German armed forces surrendered unconditionally on May 7.
//                                                    ^^^^^
pattern NounGroup0 export { node:root_node NUMBER HAS_APPOSITIVE_SLOT (ENG_MODAL_NOUN) }
{
 n = MonthName : export { node:root_node NUMBER:PLURAL HAS_APPOSITIVE_SLOT:0 }
 num = num_word:*{}
} : links { n.<ATTRIBUTE>num }

// Quarrying finally ceased in 1971.
// ^^^^^^^^^
pattern NounGroup0 export { node:root_node NUMBER HAS_APPOSITIVE_SLOT (ENG_MODAL_NOUN) }
{
 eng_verb:*{ VERB_FORM:ING } : export { node:root_node NUMBER:SINGLE HAS_APPOSITIVE_SLOT:0 }
} : ngrams { -2 }




// What Is an Arminian?
// ^^^^
pattern NounGroup0 export { node:root_node NUMBER HAS_APPOSITIVE_SLOT (ENG_MODAL_NOUN) }
{
 eng_noun:what{} : export { node:root_node NUMBER:SINGLE HAS_APPOSITIVE_SLOT:0 }
}


// Tom Davis becomes Premier.
// ^^^^^^^^^
pattern NounGroup0 export { node:root_node NUMBER HAS_APPOSITIVE_SLOT (ENG_MODAL_NOUN) }
{
 FAM_Full : export { node:root_node NUMBER:SINGLE HAS_APPOSITIVE_SLOT:0 } 
}




// All but Santa Luzia are inhabited.
// ^^^^^^^^^^^^^^^^^^^
pattern NounGroup0 export { node:root_node NUMBER HAS_APPOSITIVE_SLOT (ENG_MODAL_NOUN) }
{
 a=eng_adjective:all{} : export { node:root_node NUMBER:PLURAL HAS_APPOSITIVE_SLOT:0 }
 c=eng_conj:but{}
 obj=DirectObj
} : links { a.<RIGHT_LOGIC_ITEM>c.<NEXT_COLLOCATION_ITEM>obj }


// Некоторые прилагательные сочетаются с определенным артиклем в именную группу:
// The same applies for Macedonian.
// ^^^^^^^^
// The same applied to Anabaptists and Jews.
// ^^^^^^^^
// Ultimately, she would do the same.
//                          ^^^^^^^^
// The latter is often called “field testing”.
//     ^^^^^^

wordentry_set AdjWithArticle=eng_adjective:{ same, latter }

pattern NounGroup0 export { node:root_node NUMBER HAS_APPOSITIVE_SLOT (ENG_MODAL_NOUN) }
{
 d=eng_article:the{}
 a=eng_adjective:*{ [-5]AdjWithArticle } : export { node:root_node NUMBER:SINGLE HAS_APPOSITIVE_SLOT:0 }
}
: links { a.<ATTRIBUTE>d }
: ngrams { -1 }



#endregion NounGroup0
// --------------------------------------------------------------------

// Существительное с правым дополнение (предложная группа, подчиненная клауза и так далее).
#region NounWithRightAdjunct

pattern NounWithRightAdjunct
{
 n=NounGroup0: export { node:root_node NUMBER }
} 
: ngrams { NounValency(n) }


patterns InfinitiveGroup export { node:root_node }

// An ability to interest casual students.
pattern NounWithRightAdjunct
{
 n=NounGroup0{ ENG_MODAL_NOUN } : export { node:root_node NUMBER }
 inf=InfinitiveGroup
} : links { n.<INFINITIVE>inf }

// The aptness of iron to rust
pattern NounWithRightAdjunct
{
 n=NounGroup0{ ENG_MODAL_NOUN } : export { node:root_node NUMBER }
 p=eng_prep:of{}
 obj=PreposObject
 inf=InfinitiveGroup
} : links { n.{ <PREPOS_ADJUNCT>p.<OBJECT>obj <INFINITIVE>inf } }


patterns PreposPhrase export{ node:root_node node:n2 }

// Which is a distinction between an epidemic and a pandemic?
//            ^^^^^^^^^^^^^^^^^^^ ...
pattern NounWithRightAdjunct
{
 n=NounGroup0: export { node:root_node NUMBER }
 p_obj=PreposPhrase{ noun_prep(n,_) }
}
: links { n.<PREPOS_ADJUNCT>p_obj }
: ngrams
{
 eng_n_prep_score(n,p_obj)
 eng_n_prep_n_score(n,p_obj.root_node,p_obj.n2)
 NounValency(n)
}

// the movement of blood through the human body?
//     ^^^^^^^^ ^^       ^^^^^^^
pattern NounWithRightAdjunct
{
 n=NounGroup0: export { node:root_node NUMBER }
 p_obj=PreposPhrase{ noun_prep(n,_) }
 p_obj2=PreposPhrase{ noun_prep(n,_) }
}
: links { n.{ <PREPOS_ADJUNCT>p_obj <PREPOS_ADJUNCT>p_obj2 } }
: ngrams
{
 eng_n_prep_score(n,p_obj)
 eng_n_prep_n_score(n,p_obj.root_node,p_obj.n2)
 eng_n_prep_score(n,p_obj2)
 eng_n_prep_n_score(n,p_obj2.root_node,p_obj2.n2)
 NounValency(n)
}




// Одиночный предлог:
// Coptic has a letter for.
//                     ^^^
pattern NounWithRightAdjunct
{
 n=NounGroup0: export { node:root_node NUMBER }
 p=PreposItem
}
: links { n.<PREPOS_ADJUNCT>p }
: ngrams
{
 -11
}


// Experience as a test pilot is desirable.
// ^^^^^^^^^^^^^...
pattern NounWithRightAdjunct
{
 n=NounGroup0: export { node:root_node NUMBER }
 c=eng_conj:as{}
 n2=NounGroup
}
: links { n.<ATTRIBUTE>c.<NEXT_COLLOCATION_ITEM>n2 }
: ngrams { 1 }



patterns TimeOClock export{ node:root_node }

pattern TimeOClock
{
 num=NounEnumerator
 n=eng_noun:"o'clock"{} : export{ node:root_node }
} : links { n.<ATTRIBUTE>num }


// The tea at five o'clock is necessary
//     ^^^^^^^^^^^^^^^^^^^
pattern NounWithRightAdjunct
{
 n=NounGroup0:export{node:root_node NUMBER }
 t=TimeOClock
} : links { (n.root_node).<OBJECT>(t.root_node) }



// The good friend of mine comes today
//     ^^^^^^^^^^^^^^^^^^^
// The good friends of mine come today
//     ^^^^^^^^^^^^^^^^^^^^
pattern NounWithRightAdjunct
{
 n1=NounGroup0:export{node:root_node NUMBER }
 prep=eng_prep:of{}
 n2=eng_pronoun:I{ NOUN_FORM:POSSESSIVE PRONOUN_FORM:POST }
}
: links { n1.<PREPOS_ADJUNCT>prep.<OBJECT>n2 }
: ngrams
{
 -1
 eng_n_prep_n_score(n1,prep,n2)
}



// The numbers 1 through 9 are written here
//     ^^^^^^^^^^^^^^^^^^^
pattern NounWithRightAdjunct
{
 n=NounGroup0{ NUMBER:PLURAL }:export{ node:root_node NUMBER }
 c1=num_word
 prep=eng_prep:through{}
 c2=num_word
} : links { n.<ATTRIBUTE>c1.<NEXT_COLLOCATION_ITEM>prep.<NEXT_COLLOCATION_ITEM>c2 }



// The numbers one through nine are written here
//     ^^^^^^^^^^^^^^^^^^^^^^^^
pattern NounWithRightAdjunct
{
 n=NounGroup0{ NUMBER:PLURAL }:export{ node:root_node NUMBER }
 c1=eng_numeral:*{NUMERAL_FORM:CARDINAL}
 prep=eng_prep:through{}
 c2=eng_numeral:*{NUMERAL_FORM:CARDINAL}
} : links { n.<ATTRIBUTE>c1.<NEXT_COLLOCATION_ITEM>prep.<NEXT_COLLOCATION_ITEM>c2 }




// С возвратным местоимением:
// The Prince himself danced with Cinderella
//     ^^^^^^^^^^^^^^
pattern NounWithRightAdjunct
{
 n=NounGroup0 : export { node:root_node NUMBER }
 p=eng_pronoun:*{ =n:number pronoun_form:reflexive }
} : links { n.<ATTRIBUTE>p }





patterns AdvNounAdjunct { language=English } export { node:root_node }

// A man, apparently in  a bad mood, was there.
pattern AdvNounAdjunct
{
 comma1=',' : export { node:root_node }
 adv1=CopulaBeAdvModifier
 prep=eng_prep:*{ /*~EngPrepNot4NounAdjunct*/ }
 n=NounGroup
 comma2=','
} : links { comma1.<NEXT_COLLOCATION_ITEM>adv1.<NEXT_COLLOCATION_ITEM>prep.<NEXT_COLLOCATION_ITEM>n.<NEXT_COLLOCATION_ITEM>comma2 }
 


// A man, apparently in a bad mood, was here.
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern NounWithRightAdjunct
{
 n1=NounGroup0:export{ node:root_node NUMBER }
 adjunct=AdvNounAdjunct
}
: links { n1.<ATTRIBUTE>adjunct }
: ngrams { -1 }




// She is nothing like that
//        ^^^^^^^^^^^^^^^^^
pattern NounWithRightAdjunct
{
 n=eng_noun:nothing{} : export { node:root_node NUMBER }
 like=eng_adverb:like{}
 obj=DirectObj
} : links { n.<ATTRIBUTE>like.<OBJECT>obj }



// ---------------------------------------------------------------
// Правое определение в виде подчиненного клоза с моделью S-V(t)
// ---------------------------------------------------------------
tree_scorers VerbValency

patterns RAttrSV_Clause export { node:root_node }
patterns PredicateGroup0 export { node:root_node SUBJ_LINKED TENSE VOICE PERSON NUMBER TRANSITIVITY OBJ_LINKED WORD_ORDER }


// I didn't like the girl we met
//               ^^^^^^^^^^^^^^^^^
// I didn't like the people we met
//               ^^^^^^^^^^^^^^^^^
pattern NounWithRightAdjunct
{
 n=NounGroup0:export{ node:root_node NUMBER }
 a=RAttrSV_Clause
}
: links { n.<ATTRIBUTE>a }
: ngrams { -1 }


wordentry_set RightAttrHeadword0=
{
 eng_adjective:that{},
 eng_adjective:which{}
}

patterns RightAttrHeadword export { node:root_node }

pattern RightAttrHeadword
{
 RightAttrHeadword0 : export { node:root_node }
} 

// Achromatopsia is a genetic disorder in which sufferers have no color vision.
//                    ................^^^^^^^^^^^...
pattern NounWithRightAdjunct
{
 n=NounGroup0:export{ node:root_node NUMBER }
 prep=eng_prep:*{}
 obj=eng_adjective:which{}
 a=PredicateGroup0{ SUBJ_LINKED:1 WORD_ORDER:S_V ~TENSE:IMPERATIVE }
}
: links { n.<ATTRIBUTE>a.<PREPOS_ADJUNCT>prep.<OBJECT>obj }
: ngrams
{
 eng_sbj_verb_score( n, a )
 eng_v_prep_score( a, prep )
 VerbValency( a )
}



// Robots can perform tasks that are dangerous for humans.
//                    ^^^^^^^^^^^^^^^...
pattern NounWithRightAdjunct
{
 n=NounGroup0:export{ node:root_node NUMBER }
 @noshift( RightAttrHeadword )
 a=PredicateGroup0{ SUBJ_LINKED:1 WORD_ORDER:S_V ~TENSE:IMPERATIVE }
}
: links { n.<ATTRIBUTE>a }
: ngrams
{
 eng_sbj_verb_score( n, a )
 VerbValency( a )
}




// Некоторые прилагательные часто выступают в роли именной группы множественного числа:
// Others were probably invented.
// ^^^^^^
// Both cover same topic.
// ^^^^
// These are my books
// ^^^^^
// Those are stars
// ^^^^^

wordentry_set AdjAsPluralNoun=eng_adjective:{ all, both, others, these, those, that }

pattern NounWithRightAdjunct
{
 AdjAsPluralNoun : export { node:root_node NUMBER:PLURAL }
}

// A few have been manufactured
// ^^^^^
pattern NounWithRightAdjunct
{
 d=eng_article:a{}
 a=eng_adjective:few{} : export { node:root_node NUMBER:PLURAL }
} : links { a.<ATTRIBUTE>d }





wordentry_set AdjAsSingleNoun = eng_adjective:{ this, that, which, all }

// Which is a distinction between an epidemic and a pandemic?
// ^^^^^
// This remains the current record.
// ^^^^
// But that was not all;
//     ^^^^
pattern NounWithRightAdjunct
{
 AdjGroup{ AdjAsSingleNoun } : export { node:root_node NUMBER:SINGLE }
} : ngrams { -1 }

// ***************************************************************
// Расширенный правый атрибут существительного, присоединяемый
// через WHO и содержащий подчиненный клоз.
// ***************************************************************

patterns WHO_RAttr export { node:root_node }
patterns PredicateGroup export { node:root_node PERSON NUMBER VOICE SUBJ_LINKED }

// The burglar who steals the jewels must be caught
//             ^^^^^^^^^^^^^^^^^^^^^
pattern WHO_RAttr
{
 who=eng_pronoun:who{}
 p=PredicateGroup{ SUBJ_LINKED:0 /*[-2]TENSE:PRESENT*/ PERSON:3 NUMBER:SINGLE } : export { node:root_node }
} : links { p.<SUBJECT>who }


// Those who adopt it are called Thomists.
//       ^^^^^^^^^^^^
pattern WHO_RAttr
{
 who=eng_pronoun:who{}
 p=PredicateGroup{ SUBJ_LINKED:0 /*[-2]TENSE:PAST*/ NUMBER:SINGLE } : export { node:root_node }
} : links { p.<SUBJECT>who }

// I'll find somebody who will substitute you.
//                    ^^^^^^^^^^^^^^^^^^^^^^^
// A 'mangonto' is someone who will eat.
//                         ^^^^^^^^^^^^
pattern WHO_RAttr
{
 who=eng_pronoun:who{}
 p=PredicateGroup{ SUBJ_LINKED:0 /*[-2]TENSE:FUTURE*/ } : export { node:root_node }
} : links { p.<SUBJECT>who }


pattern NounWithRightAdjunct
{
 n=NounGroup0:export{ node:root_node NUMBER }
 a=WHO_RAttr
} : links { n.<ATTRIBUTE>a }

// С отбивкой запятой:
// Abram married Sarai, who was barren.
//                    ^^^^^^^^^^^^^^^^
pattern NounWithRightAdjunct
{
 n=NounGroup0:export{ node:root_node NUMBER }
 comma=','
 a=WHO_RAttr
 comma2=@coalesce(',')
}
: links
{
 n.{ <PUNCTUATION>comma <ATTRIBUTE>a ~<PUNCTUATION>comma2 }
}

// Those who adopt it are called Thomists.
// ^^^^^
pattern NounWithRightAdjunct
{
 n=eng_adjective:those{} : export{ node:root_node NUMBER:PLURAL }
 a=WHO_RAttr
} : links { n.<ATTRIBUTE>a }






// He used the term Hamitic.
//             ^^^^^^^^^^^^
// She is played by actress Christina Grosse.
//                  ^^^^^^^^^^^^^^^^^^^^^^^^
pattern NounWithRightAdjunct
{
 n=NounGroup0 { HAS_APPOSITIVE_SLOT:1 } : export{ node:root_node NUMBER }
 n2=FAM_Full
}
: links { n.<RIGHT_NAME>n2 }
: ngrams { 2 }


patterns RightName { language=English } export { node:root_node }

pattern RightName
{
 @regex_strict("[\\@L][\\@l]+"):export{node:root_node}
}

/*
// Lake Tanganyika remains an important trading point.
// ^^^^^^^^^^^^^^^
pattern NounWithRightAdjunct
{
 n=NounGroup0 { HAS_APPOSITIVE_SLOT:1 } : export{ node:root_node NUMBER }
 n2=RightName
}
: links { n.<RIGHT_NAME>n2 }
: ngrams { 2 }
*/


pattern NounWithRightAdjunct
{
 n=NounGroup0 { HAS_APPOSITIVE_SLOT:1 } : export{ node:root_node NUMBER }
 q1=OpeningQuote
 n2=*:*{}
 q2=ClosingQuote
}
: links { n.<RIGHT_NAME>n2.{ <PREPEND_QUOTE>q1 <APPEND_QUOTE>q2 } }
: ngrams { 2 }

pattern NounWithRightAdjunct
{
 n=NounGroup0 { HAS_APPOSITIVE_SLOT:1 } : export{ node:root_node NUMBER }
 n2=*:*{}
}
: links { n.<RIGHT_NAME>n2 }
: ngrams { -10 }
 

// Cable select is controlled by pin 28.
//                               ^^^^^^
pattern NounWithRightAdjunct
{
 n=NounGroup0 : export{ node:root_node NUMBER }
 n2=NounEnumerator
}
: links { n.<RIGHT_NAME>n2 }
: ngrams { -2 }

 
 

// Even novelty tools such as 'SEUCK' were available.
//                    ^^^^^^^
// TODO ...


// What John did was run.
// ^^^^^^^^^^^^^
// TODO ...


// Группа прилагательного в роли правого определения:
// There is also space available for campers.
//               ^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern NounWithRightAdjunct
{
 n=NounGroup0 : export{node:root_node NUMBER }
 a=Adj_WithPreposAdjunct
}
: links { n.<ATTRIBUTE>a }
: ngrams
{
 -2
 eng_adj_noun_score(a,n)
}



patterns PastParticipleGroup export { node:root_node OBJ_LINKED }

// Правый причастный оборот:
// All the articles merged should be specified.
// ^^^^^^^^^^^^^^^^^^^^^^^
pattern NounWithRightAdjunct
{
 n=NounGroup0 : export{node:root_node NUMBER }
 a=PastParticipleGroup
}
: links { n.<ATTRIBUTE>a }
: ngrams
{
 -2
 eng_adj_noun_score(a,n)
}


// Правое определение в виде причастия настоящего времени:
// Current laws pertaining to abortion are diverse.
// ^^^^^^^^^^^^^^^^^^^^^^^^...
pattern NounWithRightAdjunct
{
 n=NounGroup0 : export{ node:root_node NUMBER }
 a=Gerund
}
: links { n.<ATTRIBUTE>a }
: ngrams
{
 -2
 eng_adj_noun_score(a,n)
}




#endregion NounWithRightAdjunct



// -----------------------------------------------------------------------------------

// сборка группы существительного с использованием восходящих правил для союзных конструкций.
#region NounGroup


// Используем восходящую сборку, чтобы не ограничивать число компонентов в перечислении.
//
// признак KEYFEATURE_REQUIRED:0 - в группу вошло хотя бы одно существительное
// признак KEYFEATURE_DESIRABLE:1 - в группу вошел хотя бы один союз

patterns NounGroupUp { bottomup }
export
{
 KEYFEATURE_DETECTED // есть союзный паттерн или перечисление через запятую
 KEYFEATURE_REQUIRED // =0 присоединено хотя бы одно существительное
 KEYFEATURE_DESIRABLE // есть союз
 NUMBER
 node:root_node
}

pattern NounGroupUp
{
 NounWithRightAdjunct : export{ KEYFEATURE_DETECTED:0 KEYFEATURE_REQUIRED:1 KEYFEATURE_DESIRABLE:0 NUMBER node:root_node }
}

patterns NounGroupUp_Tail export { node:root_node NUMBER }


pattern NounGroupUp_Tail
{
 NounWithRightAdjunct : export { node:root_node NUMBER }
}

// The gene is controlled by environment and not heredity.
//                                           ^^^^^^^^^^^^
pattern NounGroupUp_Tail
{
 P=ENG_PARTICLe:NOT{}
 n=NounGroupUp_Tail : export { node:root_node NUMBER }
} : links { n.<NEGATION_PARTICLE>p }


// Присоединяем элемент через запятую. Если голова и хвост в единственном числе,
// то оставляем единственное число у результата, с небольшим штрафом.
pattern NounGroupUp
{
 n1=NounGroupUp{ NUMBER:SINGLE } :export{ KEYFEATURE_DESIRABLE:0 NUMBER node:root_node }
 comma=',' : export { KEYFEATURE_DETECTED:1 }
 n2=NounGroupUp_Tail{ NUMBER:SINGLE } :export { KEYFEATURE_REQUIRED:0 }
}
: links { n1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>n2 }
: ngrams { -1 }


// Присоединяем элемент через запятую. Результат считаем множественным числом.
// Use in mathematics, logic and science.
//        ^^^^^^^^^^^^^^^^^^...
pattern NounGroupUp
{
 n1=NounGroupUp :export{ KEYFEATURE_DESIRABLE:0 NUMBER:PLURAL node:root_node }
 comma=',' : export { KEYFEATURE_DETECTED:1 }
 n2=NounGroupUp_Tail :export { KEYFEATURE_REQUIRED:0 }
}
: links { n1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>n2 }


// Присоединяем элемент через союз. Голова и хвост в единственном числе, поэтому
// считаем, что результат тоже имеет признак единственного числа.
pattern NounGroupUp
{
 n1=NounGroupUp{ NUMBER:SINGLE } :export { NUMBER node:root_node }
 conj=Or_And : export{ KEYFEATURE_DETECTED:1 KEYFEATURE_DESIRABLE:1 }
 n2=NounGroupUp_Tail{ NUMBER:SINGLE } : export{ KEYFEATURE_REQUIRED:0 }
}
: links { n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2 }


// Присоединяем хвост через союз. Считаем, что результат имеет множественное число.
// Pine woods and fir woods are widespread.
// ^^^^^^^^^^^^^^^^^^^^^^^^
// They often donated land and labor as well.
//                    ^^^^^^^^^^^^^^
pattern NounGroupUp
{
 n1=NounGroupUp :export { NUMBER:PLURAL node:root_node }
 conj=Or_And : export{ KEYFEATURE_DETECTED:1 KEYFEATURE_DESIRABLE:1 KEYFEATURE_REQUIRED:0 }
 n2=NounGroupUp_Tail
}
: links { n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2 }
: ngrams { 1 }



// The adrenal cortex comprises three zones, or layers.
//                                      ...^^^^...
// Donkeys, mules, and horses are also useful.
//          .....^^^^^...
pattern NounGroupUp
{
 n1=NounGroupUp :export { NUMBER:PLURAL node:root_node }
 comma=','
 conj=Or_And : export{ KEYFEATURE_DETECTED:1 KEYFEATURE_DESIRABLE:1 }
 n2=NounGroupUp_Tail : export{ KEYFEATURE_REQUIRED:0 }
}
: links { n1.{ <PUNCTUATION>comma <RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2 } }
: ngrams { 1 }


// ----------------------------------------------------------


// Финальный нетерминал - группа существительного
// Одиночное существительное (со своим определением):
pattern NounGroup
{
 NounWithRightAdjunct : export { node:root_node NUMBER }
}


// Neither France nor China signed the PTBT.
// ^^^^^^^^^^^^^^^^^^^^^^^^
pattern NounGroup
{
 conj1=eng_conj:neither{}
 n1=NounGroup : export { node:root_node NUMBER }
 conj2=eng_conj:nor{}
 n2=NounGroup
}
: links { n1.{ <PREFIX_CONJUNCTION>conj1 <RIGHT_LOGIC_ITEM>conj2.<NEXT_COLLOCATION_ITEM>n2 } }

// Feed either cat or mice
//      ^^^^^^^^^^^^^^^^^^
pattern NounGroup
{
 conj1=eng_conj:either{}
 n1=NounGroup : export { node:root_node NUMBER }
 conj2=eng_conj:or{}
 n2=NounGroup
}
: links { n1.{ <PREFIX_CONJUNCTION>conj1 <RIGHT_LOGIC_ITEM>conj2.<NEXT_COLLOCATION_ITEM>n2 } }

// Both cat people and dog people have good qualities
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern NounGroup
{
 conj1=eng_conj:both{}
 n1=NounGroup : export { node:root_node NUMBER }
 conj2=eng_conj:and{}
 n2=NounGroup
}
: links { n1.{ <PREFIX_CONJUNCTION>conj1 <RIGHT_LOGIC_ITEM>conj2.<NEXT_COLLOCATION_ITEM>n2 } }


// An animal, but not a dog is allowed
// ^^^^^^^^^^^^^^^^^^^^^^^^
pattern NounGroup
{
 n1=NounGroupUp:export{node:root_node NUMBER }
 comma=','
 conj=eng_conj:but{}
 ne=eng_particle:not{}
 n2=NounGroup
} : links { n1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>ne.<NEXT_COLLOCATION_ITEM>n2 }



pattern NounGroup
{
 n=NounGroupUp{ [-1]KEYFEATURE_DESIRABLE:1 }:export{ node:root_node NUMBER }
}

/*
// В группу входит минимум одно существительное и есть союзы:
pattern NounGroup
{
 n=NounGroupUp{ KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:1 }:export{ node:root_node NUMBER }
}


// Особо рассматриваем группу из нескольких существительных, связанных
// без использования союза. Небольшой штраф дает преимущество союзным конструкциям.
pattern NounGroup
{
 n=NounGroupUp{ KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:0 }:export{ node:root_node NUMBER }
} : ngrams { -1 }
*/

// Группа в апострофах:
// I've only written genuine articles about 'genuinely notable people'.
//                                          ^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern NounGroup
{
 q1=OpeningQuote
 n=NounGroup : export{ node:root_node NUMBER }
 q2=ClosingQuote
} : links
{
 n.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}

// Незакрытая кавычка:
// He called it "my mortality."
//              ^
pattern NounGroup
{
 q1=OpeningQuote
 n=NounGroup : export{ node:root_node NUMBER }
}
: links { n.<PREPEND_QUOTE>q1 }
: ngrams { -1 }




// What Is an Arminian?
// ^^^^
pattern NounGroup
{
 eng_noun:what{} : export{ node:root_node NUMBER:SINGLE }
} : ngrams { 1 }




// The two predeceased their father.
// ^^^^^^^
pattern NounGroup
{
 a=eng_article:the{}
 n=eng_numeral:*{} : export{ node:root_node NUMBER:PLURAL }
}



wordentry_set X_thing=
{
 eng_noun:anything{},
 eng_noun:nothing{},
 eng_noun:something{}
}

// Nothing else is an ancestor.
// ^^^^^^^^^^^^
pattern NounGroup
{
 n=X_thing : export{ node:root_node NUMBER:SINGLE }
 a=eng_adjective:else{}
} : links { n.<ATTRIBUTE>a }


// Числительное может выступать в роли именной группы:
// 85 was withdrawn from circulation
// ^^
pattern NounGroup
{
 n=NumberGroup : export{ node:root_node NUMBER:SINGLE }
}// : ngrams { -1 }

pattern NounGroup
{
 n=NumberGroup : export{ node:root_node NUMBER:PLURAL }
} : ngrams { -1 }


#endregion NounGroup



#region PredicateAsNounPhrase

// ------------------------------------------------------------

// Полный предикат может выступать в роли именной группы:
// They easily forget what they've learned...
//                    ^^^^^^^^^^^^^^^^^^^^


// WH-обстоятельство:
// Perhaps you ask why I do this.
//                 ^^^^^^^^^^^^^
// This explains why no bodies were found.
//               ^^^^^^^^^^^^^^^^^^^^^^^^
// We don't know why it was rejected.
//               ^^^^^^^^^^^^^^^^^^^

wordentry_set WH_adv_opens_NP =
{
 eng_adverb:where{}, // Pauperdom is where one might end up.
 eng_adverb:how{}, // Psychoacoustics explains how humans respond to sounds.
 eng_adverb:why{}
}

patterns NounPhrase_Predicate export { node:root_node }

pattern NounPhrase_Predicate
{
 adv=WH_adv_opens_NP
 p=PredicateGroup : export { node:root_node }
} : links { p.<ATTRIBUTE>adv }



// I knew how to fix the problem
//        ^^^^^^^^^^^^^^^^^^^^^^
pattern NounPhrase_Predicate
{
 adv=eng_adverb:how{}
 v=InfinitiveGroup : export { node:root_node }
} : links { v.<ATTRIBUTE>adv }




// WH-подлежащее

patterns PredicateConjTail export { node:root_node SUBJ_LINKED TENSE VOICE PERSON NUMBER TRANSITIVITY OBJ_LINKED WORD_ORDER }

patterns WH_SubclauseSubject export { node:root_node }

// What happened at the meeting remains unclear.
// ^^^^
pattern WH_SubclauseSubject
{
 eng_noun:what{} : export { node:root_node }
} 

pattern WH_SubclauseSubject
{
 eng_pronoun:who{ CASE:NOMINATIVE } : export { node:root_node }
} 

// What happens next is not completely clear.
// ^^^^^^^^^^^^^^^^^
pattern NounPhrase_Predicate
{
 sbj=WH_SubclauseSubject
 p=PredicateConjTail{ SUBJ_LINKED:0 TENSE:PRESENT PERSON:3 NUMBER:SINGLE } : export { node:root_node }
} : links { p.<SUBJECT>sbj }


// I'll see what can be done.
//          ^^^^^^^^^^^^^^^^
pattern NounPhrase_Predicate
{
 sbj=WH_SubclauseSubject
 p=PredicateConjTail{ EngModalVerb0 SUBJ_LINKED:0 } : export { node:root_node }
} : links { p.<SUBJECT>sbj }


// What happened at the meeting remains unclear.
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// There are conflicting reports of what happened.
//                                  ^^^^^^^^^^^^^
pattern NounPhrase_Predicate
{
 sbj=WH_SubclauseSubject
 p=PredicateConjTail{ SUBJ_LINKED:0 TENSE:PAST NUMBER:SINGLE } : export { node:root_node }
} : links { p.<SUBJECT>sbj }


// Well, let's see what will happen.
//                 ^^^^^^^^^^^^^^^^
pattern NounPhrase_Predicate
{
 sbj=WH_SubclauseSubject
 p=PredicateConjTail{ SUBJ_LINKED:0 TENSE:FUTURE } : export { node:root_node }
} : links { p.<SUBJECT>sbj }

// WH-дополнение

patterns WH_SubclauseObject export { node:root_node }

// Everyone knows what the third word means.
//                ^^^^^^^^^^^^^^^^^^^^^^^^^
// This identification is what Lacan called alienation.
//                        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern WH_SubclauseObject
{
 eng_noun:what{} : export { node:root_node }
} 

// This is obviously not what we want.
//                   ^^^^^^^^
pattern WH_SubclauseObject
{
 n=eng_particle:not{}
 s=WH_SubclauseSubject : export { node:root_node }
} : links { s.<NEGATION_PARTICLE>n }


pattern NounPhrase_Predicate
{
 obj=WH_SubclauseObject
 p=PredicateConjTail{ TRANSITIVITY:TRANSITIVE OBJ_LINKED:0 SUBJ_LINKED:1 } : export { node:root_node }
} : links { p.<OBJECT>obj }


// It is unknown from whom he descended;
//                    ^^^^^^^^^^^^^^^^^
pattern NounPhrase_Predicate
{
 obj=eng_pronoun:who{ CASE:PREPOSITIVE }
 p=PredicateConjTail{ TRANSITIVITY:TRANSITIVE OBJ_LINKED:0 SUBJ_LINKED:1 } : export { node:root_node }
} : links { p.<OBJECT>obj }



pattern NounGroup
{
 NounPhrase_Predicate : export { node:root_node NUMBER:SINGLE }
}


#endregion PredicateAsNounPhrase

