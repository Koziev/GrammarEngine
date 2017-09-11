// CD->28.03.2009
// LC->19.07.2009

automat sg
{

 entry ます  : JAP_VERB_POSTFIX { JAP_VERB_KIND:PRESENT_FUTURE } // II основа ます --> настоящее-будущее время
 entry ません : JAP_VERB_POSTFIX { JAP_VERB_KIND:NEGATIVE_PRESENT_FUTURE } // Постфикс ません (-масэн) образует отрицательную форму глагола в настоящем-будущем времени
 entry ない : JAP_VERB_POSTFIX { JAP_VERB_KIND:NEGATIVE_PRESENT_FUTURE } // грубая форма отрицания для настоящего времени
 entry ませんか : JAP_VERB_POSTFIX { JAP_VERB_KIND:IMPERATIVE } // Постфикс ませんか образует побудительную форму 
 entry ませんでした : JAP_VERB_POSTFIX { JAP_VERB_KIND:NEGATIVE_PAST } // Вежливая форма отрицания прошедшего времени   
 entry ました : JAP_VERB_POSTFIX { JAP_VERB_KIND:Undefined } // стандартная форма прошедшего времени
}
