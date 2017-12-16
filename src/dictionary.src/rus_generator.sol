facts ngram2 language=Russian
{
 arity=2
 return=integer
}

// Кошка ловит мышь
//       ^^^^^^^^^^
fact ngram2
{
 if context { rus_verbs:ловить{} существительное:мышь{ падеж:вин } }
  then return 1
}


patterns G_AdjPhrase_acc_sg_f { language=Russian } export { node:root_node ОДУШ }
patterns G_AdjPhrase_nom_sg_f { language=Russian } export { node:root_node }

patterns G_NounPhrase_acc { language=Russian } export { node:root_node }
patterns G_NounPhrase_nom_sg_f { language=Russian } export { node:root_node }

patterns G_DirectObj_acc { language=Russian } export { node:root_node }

patterns G_Predicate_3_sg { language=Russian } export { node:root_node }

patterns G_Subject_3_sg { language=Russian } export { node:root_node }

patterns G_Clause { language=Russian } export { node:root_node }


// -------------------------------------


pattern G_AdjPhrase_acc_sg_f
{
 прилагательное:*{ падеж:вин число:ед род:жен ~краткий } : export { node:root_node ОДУШ }
}


pattern G_AdjPhrase_nom_sg_f
{
 прилагательное:*{ падеж:им род:жен число:ед ~краткий } : export { node:root_node }
}

// -------------------------------------


// Одиночное существительное как простейший вариант группы.
pattern G_NounPhrase_acc
{
 существительное:*{ ПАДЕЖ:ВИН }:export { node:root_node }
}

// Существительное может атрибутироваться прилагательным.
// При этом мы должны проверить согласование по роду, падежу, числу и одушевленности для
// винительного падежа.
pattern G_NounPhrase_acc
{
 adj=G_AdjPhrase_acc_sg_f
 n=существительное:*{ ПАДЕЖ:ВИН РОД:ЖЕН ЧИСЛО:ЕД /*=adj:ОДУШ*/ } : export { node:root_node }
} : ngrams { ngram2(adj,n) }


pattern G_NounPhrase_nom_sg_f
{
 существительное:*{ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:ЖЕН }:export { node:root_node }
}

/*
pattern G_NounPhrase_nom_sg_f
{
 adj=G_AdjPhrase_nom_sg_f
 n=существительное:*{ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:ЖЕН }:export { node:root_node }
} : ngrams { ngram2(adj,n) }
*/

// -------------------------------------

pattern G_DirectObj_acc
{
 G_NounPhrase_acc:export { node:root_node }
}

// -------------------------------------

pattern G_Subject_3_sg
{
 G_NounPhrase_nom_sg_f : export { node:root_node }
}


// -------------------------------------

pattern G_Predicate_3_sg
{
 v=глагол:*{
            наклонение:изъяв время:настоящее лицо:3 число:ед переходность:переходный
           } : export { node:root_node }
}



pattern G_Predicate_3_sg
{
 v=глагол:*{ наклонение:изъяв время:настоящее лицо:3 число:ед переходность:переходный падеж:вин } : export { node:root_node }
 obj=G_DirectObj_acc
} : links { v.<OBJECT>obj }
  : ngrams { ngram2(v,obj.root_node) }


// -------------------------------------


pattern G_Clause
{
 sbj=G_Subject_3_sg
 p=G_Predicate_3_sg : export { node:root_node }
} : links { p.<SUBJECT>sbj }
  : ngrams { ngram2(sbj.root_node,p.root_node) }


patterns _Generator { language=Russian }
pattern _Generator { beth:begin{} G_Clause beth:end{} }

