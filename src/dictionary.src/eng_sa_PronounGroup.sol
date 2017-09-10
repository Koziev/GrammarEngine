// Группа местоимения
// Кроме одиночного местоимения также может быть союзный паттерн.


patterns PronounItem export { node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER }

pattern PronounItem
{
 eng_pronoun:*{} : export { node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER }
}


pattern PronounItem
{
 n=eng_particle:not{}
 p=eng_pronoun:*{} : export { node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER }
} : links { p.<NEGATION_PARTICLE>n }


// We all needed some rest
// ^^^^^^
pattern PronounItem
{
 p=ENG_PRONOUN:I{}:export { node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER }
 a=eng_adjective:all{}
} : links { p.<ATTRIBUTE>a }


// He himself wrote that novel
// ^^^^^^^^^^
// They themselves wrote that novel
// ^^^^^^^^^^^^^^^
pattern PronounItem
{
 n=eng_pronoun:*{ NOUN_FORM:BASIC CASE:NOMINATIVE } : export { node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER }
 p=eng_pronoun:*{ =n:NUMBER pronoun_form:reflexive }
} : links { n.<ATTRIBUTE>p }


// -------------------------------------------------------

patterns PronounUp { bottomup language=English }
export
{
 KEYFEATURE_DETECTED // есть союзный паттерн или перечисление через запятую
 KEYFEATURE_REQUIRED // =0 присоединено хотя бы одно местоимение
 KEYFEATURE_DESIRABLE // есть союз
 PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER
 node:root_node
}

pattern PronounUp
{
 PronounItem : export { KEYFEATURE_DETECTED:0 KEYFEATURE_REQUIRED:1 KEYFEATURE_DESIRABLE:0 node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER }
}


wordentry_set PronounConj=
{
 eng_conj:or{},
 eng_conj:and{},
 eng_conj:rather than{}
}


// Присоединяем элемент через запятую, причем присоединяемое местоимение часто бывает в слабой форме
// George, Robert and I were always together.
pattern PronounUp
{
 n1=PronounUp : export{ KEYFEATURE_DESIRABLE:0 node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER }
 comma=',' : export { KEYFEATURE_DETECTED:1 }
 n2=PronounItem{ [-1]=n1:NOUN_FORM [-1]=n1:PRONOUN_FORM } : export { KEYFEATURE_REQUIRED:0 }
}
: links { n1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>n2 }



// Присоединяем элемент через союз. Грамматическое число берем из головы группы.
// You and I are very good friend.
// George and I are friends
// George and I are very good friends.
// George and I were placed in the same class.
pattern PronounUp
{
 n1=PronounUp:export { node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER }
 conj=PronounConj : export{ KEYFEATURE_DETECTED:1 KEYFEATURE_DESIRABLE:1 }
 n2=PronounItem{ [-1]=n1:NOUN_FORM [-1]=n1:PRONOUN_FORM } : export{ KEYFEATURE_REQUIRED:0 }
}
: links { n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2 }
: ngrams { 1 }



patterns NounWithRightAdjunct { language=English } export { node:root_node NUMBER }

// He and others were executed.
// ^^^^^^^^^^^^^
pattern PronounUp
{
 n1=PronounUp:export { node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER }
 conj=PronounConj : export{ KEYFEATURE_DETECTED:1 KEYFEATURE_DESIRABLE:1 }
 n2=NounWithRightAdjunct : export{ KEYFEATURE_REQUIRED:0 }
}
: links { n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2 }




// AUTOMATIC ESTIMATION OF ONE'S AGE WITH HIS/HER SPEECH.
//                                        ^^^^^^^
// How is Your Child Developing in His/Her Speech
//                                 ^^^^^^^
pattern PronounUp
{
 n1=PronounUp:export { node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER }
 conj=Пунктуатор:"/"{} : export{ KEYFEATURE_DETECTED:1 KEYFEATURE_DESIRABLE:1 }
 n2=PronounItem{ [-1]=n1:NOUN_FORM [-1]=n1:PRONOUN_FORM } : export{ KEYFEATURE_REQUIRED:0 }
}
: links { n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2 }
: ngrams { 1 }



// You and me
pattern PronounUp
{
 n1=PronounUp{ NOUN_FORM:BASIC CASE:NOMINATIVE }:export { node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER }
 conj=eng_conj:and{} : export{ KEYFEATURE_DETECTED:1 KEYFEATURE_DESIRABLE:1 }
 n2=PronounItem{ NOUN_FORM:BASIC CASE:PREPOSITIVE }:export{ KEYFEATURE_REQUIRED:0 }
}
: links { n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2 }


// -------------------------------------------------------

patterns PronounGroup export { node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER }


// Одиночное местоимение:
pattern PronounGroup
{
 PronounItem : export { node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER }
}

// В группу входит минимум одно местоимение и есть союзы.
// Считаем, что группа имеет множественное число.
pattern PronounGroup
{
 n=PronounUp{ KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:1 }:export{ node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER:PLURAL }
}

// Считаем, что группы имеет единственное число, хотя в него входит более одного
// местоимения, и все входящие местоимения в единственном числе
pattern PronounGroup
{
 n=PronounUp{ NUMBER:SINGLE KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:1 }:export{ node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER }
} : ngrams { -1 }



// Особо рассматриваем группу из нескольких местоимений, связанных
// без использования союза. Небольшой штраф дает преимущество союзным конструкциям.
pattern PronounGroup
{
 n=PronounUp{ KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:0 }:export{ node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER }
} : ngrams { -1 }


patterns PastParticipleLeftGroup export { node:root_node }

// Левый причастный оборот:
// When ordered to strip, he hesitated.
// ^^^^^^^^^^^^^^^^^^^^^^^^^
pattern PronounGroup
{
 a=PastParticipleLeftGroup
 comma=','
 n=PronounGroup : export{ node:root_node PRONOUN_FORM PERSON CASE NOUN_FORM NUMBER }
}
: links { n.{ <ATTRIBUTE>a <PUNCTUATION>comma } }

