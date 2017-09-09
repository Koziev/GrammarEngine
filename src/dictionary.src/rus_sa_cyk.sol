// ======================== НАЧАЛЬНЫЕ РАСПОЗНАВАТЕЛИ ==========================

// особый нетерминал, используемый для маркировки слов,
// которые не распознались другими распознавателями.
word_nonterm UNK { * }


word_nonterm COMMA { ',' }

word_nonterm STERM { '.' }
word_nonterm STERM { '!' }
word_nonterm STERM { '?' }


// -------------- СОЮЗЫ

wordentry_set ВОСХ_ЛогичСоюз = 
{
 союз:и{},
 союз:да{},
 союз:"и даже"{},
 союз:или{},
 союз:"да и"{},
 союз:либо{}
}

// Союзы для паттернов с глаголами:
// день укорачивается, а ночь удлинняется
wordentry_set ВОСХ_ГлСоюз = 
{
 ВОСХ_ЛогичСоюз,
 союз:а{},
 союз:зато{},
 союз:потому что{},
 союз:так как{}
}


patterns ВОСХ_ЛогичСоюз2 export { node:root_node }

// Кошка, но не собака
pattern ВОСХ_ЛогичСоюз2
{
 j=союз:но{} : export { node:root_node }
 n=частица:не{}
} : links { j.<NEGATION_PARTICLE>n }

word_nonterm J { ВОСХ_ЛогичСоюз }
word_nonterm J { ВОСХ_ЛогичСоюз2 }

// Союзные паттерны с двумя частями:
// Либо A, либо B

wordentry_set ВОСХ_СоюзВГруппе={
 союз:ни{},
 союз:и{},
 союз:или{},
 союз:либо{}
}

word_nonterm J2 { ВОСХ_СоюзВГруппе }

word_nonterm JV { ВОСХ_ГлСоюз }

// #####################################################
// -------------------- НАРЕЧИЯ ------------------------
// #####################################################

patterns ВОСХ_МодифНареч export { node:root_node }

pattern ВОСХ_МодифНареч
{
 МодифНареч : export { node:root_node }
}

pattern ВОСХ_МодифНареч
{
 n=частица:не{}
 a=МодифНареч : export { node:root_node }
} : links { a.<NEGATION_PARTICLE>n }


word_nonterm Ym { ВОСХ_МодифНареч }

// ------------------

patterns ВОСХ_Нареч export { node:root_node }

pattern ВОСХ_Нареч
{
 наречие:*{} : export { node:root_node }
}

pattern ВОСХ_Нареч
{
 n=частица:не{}
 a=наречие:*{} : export { node:root_node }
} : links { a.<NEGATION_PARTICLE>n }

word_nonterm Y { ВОСХ_Нареч }

// ---------------------


patterns ВОСХ_ИнфПерех export { node:root_node }
patterns ВОСХ_ИнфНеперех export { node:root_node }
patterns ВОСХ_ИнфМод export { node:root_node }

pattern ВОСХ_ИнфПерех
{
 инфинитив:*{ переходность:переходный } : export { node:root_node }
}

pattern ВОСХ_ИнфПерех
{
 n=частица:не{}
 v=инфинитив:*{ переходность:переходный } : export { node:root_node }
} : links { v.<NEGATION_PARTICLE>n }


pattern ВОСХ_ИнфНеперех
{
 инфинитив:*{ переходность:непереходный } : export { node:root_node }
}

pattern ВОСХ_ИнфНеперех
{
 n=частица:не{}
 v=инфинитив:*{ переходность:непереходный } : export { node:root_node }
} : links { v.<NEGATION_PARTICLE>n }



pattern ВОСХ_ИнфМод
{
 инфинитив:*{ модальный } : export { node:root_node }
}

pattern ВОСХ_ИнфМод
{
 n=частица:не{}
 v=инфинитив:*{ модальный } : export { node:root_node }
} : links { v.<NEGATION_PARTICLE>n }

word_nonterm It { ВОСХ_ИнфПерех }
word_nonterm Iit { ВОСХ_ИнфНеперех }
word_nonterm Im { ВОСХ_ИнфМод }

// ---------------------

patterns ВОСХ_ГлПерех export { node:root_node НАКЛОНЕНИЕ ВРЕМЯ ЛИЦО РОД ЧИСЛО }
patterns ВОСХ_ГлНеперех export { node:root_node НАКЛОНЕНИЕ ВРЕМЯ ЛИЦО РОД ЧИСЛО }
patterns ВОСХ_ГлМод export { node:root_node НАКЛОНЕНИЕ ВРЕМЯ ЛИЦО РОД ЧИСЛО }

pattern ВОСХ_ГлПерех
{
 глагол:*{ переходность:переходный } : export { node:root_node НАКЛОНЕНИЕ ЛИЦО ВРЕМЯ РОД ЧИСЛО }
}

pattern ВОСХ_ГлПерех
{
 n=частица:не{}
 v=глагол:*{ переходность:переходный } : export { node:root_node НАКЛОНЕНИЕ ЛИЦО ВРЕМЯ РОД ЧИСЛО }
} : links { v.<NEGATION_PARTICLE>n }


pattern ВОСХ_ГлНеперех
{
 глагол:*{ переходность:непереходный } : export { node:root_node НАКЛОНЕНИЕ ЛИЦО ВРЕМЯ РОД ЧИСЛО }
}

pattern ВОСХ_ГлНеперех
{
 n=частица:не{}
 v=глагол:*{ переходность:непереходный } : export { node:root_node НАКЛОНЕНИЕ ЛИЦО ВРЕМЯ РОД ЧИСЛО }
} : links { v.<NEGATION_PARTICLE>n }


pattern ВОСХ_ГлМод
{
 глагол:*{ модальный } : export { node:root_node НАКЛОНЕНИЕ ВРЕМЯ ЛИЦО РОД ЧИСЛО }
}

pattern ВОСХ_ГлМод
{
 n=частица:не{}
 v=глагол:*{ модальный } : export { node:root_node НАКЛОНЕНИЕ ВРЕМЯ ЛИЦО РОД ЧИСЛО }
} : links { v.<NEGATION_PARTICLE>n }

// переходные
word_nonterm Vt_f { ВОСХ_ГлПерех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm Vt_m { ВОСХ_ГлПерех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm Vt_n { ВОСХ_ГлПерех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ РОД:СР ЧИСЛО:ЕД } }
word_nonterm Vt_pl { ВОСХ_ГлПерех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:МН } }

word_nonterm Vt_1_sg { ВОСХ_ГлПерех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:1 ЧИСЛО:ЕД } }
word_nonterm Vt_2_sg { ВОСХ_ГлПерех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:2 ЧИСЛО:ЕД } }
word_nonterm Vt_3_sg { ВОСХ_ГлПерех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 ЧИСЛО:ЕД } }

word_nonterm Vt_1_pl { ВОСХ_ГлПерех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:1 ЧИСЛО:МН } }
word_nonterm Vt_2_pl { ВОСХ_ГлПерех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:2 ЧИСЛО:МН } }
word_nonterm Vt_3_pl { ВОСХ_ГлПерех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 ЧИСЛО:МН } }

word_nonterm Vt_1_sg { ВОСХ_ГлПерех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:1 ЧИСЛО:ЕД } }
word_nonterm Vt_2_sg { ВОСХ_ГлПерех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:2 ЧИСЛО:ЕД } }
word_nonterm Vt_3_sg { ВОСХ_ГлПерех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 ЧИСЛО:ЕД } }

word_nonterm Vt_1_pl { ВОСХ_ГлПерех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:1 ЧИСЛО:МН } }
word_nonterm Vt_2_pl { ВОСХ_ГлПерех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:2 ЧИСЛО:МН } }
word_nonterm Vt_3_pl { ВОСХ_ГлПерех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 ЧИСЛО:МН } }



// непереходные
word_nonterm Vit_1_sg { ВОСХ_ГлНеперех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:1 ЧИСЛО:ЕД } }
word_nonterm Vit_2_sg { ВОСХ_ГлНеперех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:2 ЧИСЛО:ЕД } }
word_nonterm Vit_3_sg { ВОСХ_ГлНеперех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 ЧИСЛО:ЕД } }

word_nonterm Vit_1_pl { ВОСХ_ГлНеперех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:1 ЧИСЛО:МН } }
word_nonterm Vit_2_pl { ВОСХ_ГлНеперех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:2 ЧИСЛО:МН } }
word_nonterm Vit_3_pl { ВОСХ_ГлНеперех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 ЧИСЛО:МН } }

word_nonterm Vit_1_sg { ВОСХ_ГлНеперех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:1 ЧИСЛО:ЕД } }
word_nonterm Vit_2_sg { ВОСХ_ГлНеперех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:2 ЧИСЛО:ЕД } }
word_nonterm Vit_3_sg { ВОСХ_ГлНеперех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 ЧИСЛО:ЕД } }

word_nonterm Vit_1_pl { ВОСХ_ГлНеперех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:1 ЧИСЛО:МН } }
word_nonterm Vit_2_pl { ВОСХ_ГлНеперех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:2 ЧИСЛО:МН } }
word_nonterm Vit_3_pl { ВОСХ_ГлНеперех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 ЧИСЛО:МН } }

word_nonterm Vit_f { ВОСХ_ГлНеперех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm Vit_m { ВОСХ_ГлНеперех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm Vit_n { ВОСХ_ГлНеперех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ РОД:СР ЧИСЛО:ЕД } }
word_nonterm Vit_pl { ВОСХ_ГлНеперех{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:МН } }

// модальные
word_nonterm Vm_1_sg { ВОСХ_ГлМод{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:1 ЧИСЛО:ЕД } }
word_nonterm Vm_2_sg { ВОСХ_ГлМод{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:2 ЧИСЛО:ЕД } }
word_nonterm Vm_3_sg { ВОСХ_ГлМод{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 ЧИСЛО:ЕД } }

word_nonterm Vm_1_pl { ВОСХ_ГлМод{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:1 ЧИСЛО:МН } }
word_nonterm Vm_2_pl { ВОСХ_ГлМод{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:2 ЧИСЛО:МН } }
word_nonterm Vm_3_pl { ВОСХ_ГлМод{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 ЧИСЛО:МН } }

word_nonterm Vm_1_sg { ВОСХ_ГлМод{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:1 ЧИСЛО:ЕД } }
word_nonterm Vm_2_sg { ВОСХ_ГлМод{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:2 ЧИСЛО:ЕД } }
word_nonterm Vm_3_sg { ВОСХ_ГлМод{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 ЧИСЛО:ЕД } }

word_nonterm Vm_1_pl { ВОСХ_ГлМод{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:1 ЧИСЛО:МН } }
word_nonterm Vm_2_pl { ВОСХ_ГлМод{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:2 ЧИСЛО:МН } }
word_nonterm Vm_3_pl { ВОСХ_ГлМод{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 ЧИСЛО:МН } }

word_nonterm Vm_f { ВОСХ_ГлМод{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm Vm_m { ВОСХ_ГлМод{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm Vm_n { ВОСХ_ГлМод{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ РОД:СР ЧИСЛО:ЕД } }
word_nonterm Vm_pl { ВОСХ_ГлМод{ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:МН } }


// #######################################################
// --------------------- ДЕЕПРИЧАСТИЕ --------------------
// #######################################################

patterns ВОСХ_ДеепрПерех export { node:root_node }
patterns ВОСХ_ДеепрНеперех export { node:root_node }
patterns ВОСХ_ДеепрМод export { node:root_node }

pattern ВОСХ_ДеепрПерех
{
 деепричастие:*{ переходность:переходный } : export { node:root_node }
}

pattern ВОСХ_ДеепрПерех
{
 n=частица:не{}
 v=деепричастие:*{ переходность:переходный } : export { node:root_node }
} : links { v.<NEGATION_PARTICLE>n }


pattern ВОСХ_ДеепрНеперех
{
 деепричастие:*{ переходность:непереходный } : export { node:root_node }
}

pattern ВОСХ_ДеепрНеперех
{
 n=частица:не{}
 v=деепричастие:*{ переходность:непереходный } : export { node:root_node }
} : links { v.<NEGATION_PARTICLE>n }


pattern ВОСХ_ДеепрМод
{
 деепричастие:*{ модальный } : export { node:root_node }
}

pattern ВОСХ_ДеепрМод
{
 n=частица:не{}
 v=деепричастие:*{ модальный } : export { node:root_node }
} : links { v.<NEGATION_PARTICLE>n }


word_nonterm YVt { ВОСХ_ДеепрПерех }
word_nonterm YVit { ВОСХ_ДеепрНеперех }
word_nonterm YVm { ВОСХ_ДеепрМод }




// ####################################################
// --------------------- ПРИЧАСТИЕ --------------------
// ####################################################

patterns ВОСХ_ПричПерех export { node:root_node РОД ЧИСЛО ПАДЕЖ }
patterns ВОСХ_ПричНеперех export { node:root_node РОД ЧИСЛО ПАДЕЖ }
patterns ВОСХ_ПричМод export { node:root_node РОД ЧИСЛО ПАДЕЖ }

pattern ВОСХ_ПричПерех
{
 прилагательное:*{ причастие переходность:переходный } : export { node:root_node РОД ЧИСЛО ПАДЕЖ }
}

pattern ВОСХ_ПричПерех
{
 n=частица:не{}
 v=прилагательное:*{ причастие переходность:переходный } : export { node:root_node РОД ЧИСЛО ПАДЕЖ }
} : links { v.<NEGATION_PARTICLE>n }


pattern ВОСХ_ПричНеперех
{
 прилагательное:*{ причастие переходность:непереходный } : export { node:root_node РОД ЧИСЛО ПАДЕЖ }
}

pattern ВОСХ_ПричНеперех
{
 n=частица:не{}
 v=прилагательное:*{ причастие переходность:непереходный } : export { node:root_node РОД ЧИСЛО ПАДЕЖ }
} : links { v.<NEGATION_PARTICLE>n }


pattern ВОСХ_ПричМод
{
 прилагательное:*{ причастие модальный } : export { node:root_node РОД ЧИСЛО ПАДЕЖ }
}

pattern ВОСХ_ПричМод
{
 n=частица:не{}
 v=прилагательное:*{ причастие модальный } : export { node:root_node РОД ЧИСЛО ПАДЕЖ }
} : links { v.<NEGATION_PARTICLE>n }

// переходные причастия

word_nonterm AVt_nom_f { ВОСХ_ПричПерех{ ПАДЕЖ:ИМ РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVt_nom_m { ВОСХ_ПричПерех{ ПАДЕЖ:ИМ РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVt_nom_n { ВОСХ_ПричПерех{ ПАДЕЖ:ИМ РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVt_nom_pl { ВОСХ_ПричПерех{ ПАДЕЖ:ИМ ЧИСЛО:МН } }

word_nonterm AVt_gen_f { ВОСХ_ПричПерех{ ПАДЕЖ:РОД РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVt_gen_m { ВОСХ_ПричПерех{ ПАДЕЖ:РОД РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVt_gen_n { ВОСХ_ПричПерех{ ПАДЕЖ:РОД РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVt_gen_pl { ВОСХ_ПричПерех{ ПАДЕЖ:РОД ЧИСЛО:МН } }

word_nonterm AVt_ins_f { ВОСХ_ПричПерех{ ПАДЕЖ:ТВОР РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVt_ins_m { ВОСХ_ПричПерех{ ПАДЕЖ:ТВОР РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVt_ins_n { ВОСХ_ПричПерех{ ПАДЕЖ:ТВОР РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVt_ins_pl { ВОСХ_ПричПерех{ ПАДЕЖ:ТВОР ЧИСЛО:МН } }

word_nonterm AVt_acc_f { ВОСХ_ПричПерех{ ПАДЕЖ:ВИН РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVt_acc_m { ВОСХ_ПричПерех{ ПАДЕЖ:ВИН РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVt_acc_n { ВОСХ_ПричПерех{ ПАДЕЖ:ВИН РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVt_acc_pl { ВОСХ_ПричПерех{ ПАДЕЖ:ВИН ЧИСЛО:МН } }

word_nonterm AVt_dat_f { ВОСХ_ПричПерех{ ПАДЕЖ:ДАТ РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVt_dat_m { ВОСХ_ПричПерех{ ПАДЕЖ:ДАТ РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVt_dat_n { ВОСХ_ПричПерех{ ПАДЕЖ:ДАТ РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVt_dat_pl { ВОСХ_ПричПерех{ ПАДЕЖ:ДАТ ЧИСЛО:МН } }

word_nonterm AVt_prep_f { ВОСХ_ПричПерех{ ПАДЕЖ:ПРЕДЛ РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVt_prep_m { ВОСХ_ПричПерех{ ПАДЕЖ:ПРЕДЛ РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVt_prep_n { ВОСХ_ПричПерех{ ПАДЕЖ:ПРЕДЛ РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVt_prep_pl { ВОСХ_ПричПерех{ ПАДЕЖ:ПРЕДЛ ЧИСЛО:МН } }


// непереходные причастия

word_nonterm AVit_nom_f { ВОСХ_ПричНеперех{ ПАДЕЖ:ИМ РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVit_nom_m { ВОСХ_ПричНеперех{ ПАДЕЖ:ИМ РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVit_nom_n { ВОСХ_ПричНеперех{ ПАДЕЖ:ИМ РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVit_nom_pl { ВОСХ_ПричНеперех{ ПАДЕЖ:ИМ ЧИСЛО:МН } }

word_nonterm AVit_gen_f { ВОСХ_ПричНеперех{ ПАДЕЖ:РОД РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVit_gen_m { ВОСХ_ПричНеперех{ ПАДЕЖ:РОД РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVit_gen_n { ВОСХ_ПричНеперех{ ПАДЕЖ:РОД РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVit_gen_pl { ВОСХ_ПричНеперех{ ПАДЕЖ:РОД ЧИСЛО:МН } }

word_nonterm AVit_ins_f { ВОСХ_ПричНеперех{ ПАДЕЖ:ТВОР РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVit_ins_m { ВОСХ_ПричНеперех{ ПАДЕЖ:ТВОР РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVit_ins_n { ВОСХ_ПричНеперех{ ПАДЕЖ:ТВОР РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVit_ins_pl { ВОСХ_ПричНеперех{ ПАДЕЖ:ТВОР ЧИСЛО:МН } }

word_nonterm AVit_acc_f { ВОСХ_ПричНеперех{ ПАДЕЖ:ВИН РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVit_acc_m { ВОСХ_ПричНеперех{ ПАДЕЖ:ВИН РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVit_acc_n { ВОСХ_ПричНеперех{ ПАДЕЖ:ВИН РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVit_acc_pl { ВОСХ_ПричНеперех{ ПАДЕЖ:ВИН ЧИСЛО:МН } }

word_nonterm AVit_dat_f { ВОСХ_ПричНеперех{ ПАДЕЖ:ДАТ РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVit_dat_m { ВОСХ_ПричНеперех{ ПАДЕЖ:ДАТ РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVit_dat_n { ВОСХ_ПричНеперех{ ПАДЕЖ:ДАТ РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVit_dat_pl { ВОСХ_ПричНеперех{ ПАДЕЖ:ДАТ ЧИСЛО:МН } }

word_nonterm AVit_prep_f { ВОСХ_ПричНеперех{ ПАДЕЖ:ПРЕДЛ РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVit_prep_m { ВОСХ_ПричНеперех{ ПАДЕЖ:ПРЕДЛ РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVit_prep_n { ВОСХ_ПричНеперех{ ПАДЕЖ:ПРЕДЛ РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVit_prep_pl { ВОСХ_ПричНеперех{ ПАДЕЖ:ПРЕДЛ ЧИСЛО:МН } }

// модальные

word_nonterm AVm_nom_f { ВОСХ_ПричМод{ ПАДЕЖ:ИМ РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVm_nom_m { ВОСХ_ПричМод{ ПАДЕЖ:ИМ РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVm_nom_n { ВОСХ_ПричМод{ ПАДЕЖ:ИМ РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVm_nom_pl { ВОСХ_ПричМод{ ПАДЕЖ:ИМ ЧИСЛО:МН } }

word_nonterm AVm_gen_f { ВОСХ_ПричМод{ ПАДЕЖ:РОД РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVm_gen_m { ВОСХ_ПричМод{ ПАДЕЖ:РОД РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVm_gen_n { ВОСХ_ПричМод{ ПАДЕЖ:РОД РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVm_gen_pl { ВОСХ_ПричМод{ ПАДЕЖ:РОД ЧИСЛО:МН } }

word_nonterm AVm_ins_f { ВОСХ_ПричМод{ ПАДЕЖ:ТВОР РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVm_ins_m { ВОСХ_ПричМод{ ПАДЕЖ:ТВОР РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVm_ins_n { ВОСХ_ПричМод{ ПАДЕЖ:ТВОР РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVm_ins_pl { ВОСХ_ПричМод{ ПАДЕЖ:ТВОР ЧИСЛО:МН } }

word_nonterm AVm_acc_f { ВОСХ_ПричМод{ ПАДЕЖ:ВИН РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVm_acc_m { ВОСХ_ПричМод{ ПАДЕЖ:ВИН РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVm_acc_n { ВОСХ_ПричМод{ ПАДЕЖ:ВИН РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVm_acc_pl { ВОСХ_ПричМод{ ПАДЕЖ:ВИН ЧИСЛО:МН } }

word_nonterm AVm_dat_f { ВОСХ_ПричМод{ ПАДЕЖ:ДАТ РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVm_dat_m { ВОСХ_ПричМод{ ПАДЕЖ:ДАТ РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVm_dat_n { ВОСХ_ПричМод{ ПАДЕЖ:ДАТ РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVm_dat_pl { ВОСХ_ПричМод{ ПАДЕЖ:ДАТ ЧИСЛО:МН } }

word_nonterm AVm_prep_f { ВОСХ_ПричМод{ ПАДЕЖ:ПРЕДЛ РОД:ЖЕН ЧИСЛО:ЕД } }
word_nonterm AVm_prep_m { ВОСХ_ПричМод{ ПАДЕЖ:ПРЕДЛ РОД:МУЖ ЧИСЛО:ЕД } }
word_nonterm AVm_prep_n { ВОСХ_ПричМод{ ПАДЕЖ:ПРЕДЛ РОД:СР ЧИСЛО:ЕД } }
word_nonterm AVm_prep_pl { ВОСХ_ПричМод{ ПАДЕЖ:ПРЕДЛ ЧИСЛО:МН } }





// ##########################################################
// --------------------- ПРИЛАГАТЕЛЬНОЕ --------------------
// ##########################################################

patterns ВОСХ_ПрилАтриб export { node:root_node РОД ПАДЕЖ ЧИСЛО }

pattern ВОСХ_ПрилАтриб
{
 прилагательное:*{ степень:атриб ~КРАТКИЙ } : export { node:root_node РОД ПАДЕЖ ЧИСЛО }
}

pattern ВОСХ_ПрилАтриб
{
 прилагательное:*{ степень:превосх } : export { node:root_node РОД ПАДЕЖ ЧИСЛО }
}

pattern ВОСХ_ПрилАтриб
{
 n=частица:не{}
 a=прилагательное:*{ степень:атриб ~КРАТКИЙ } : export { node:root_node РОД ПАДЕЖ ЧИСЛО }
} : links { a.<NEGATION_PARTICLE>n }

pattern ВОСХ_ПрилАтриб
{
 n=частица:не{}
 a=прилагательное:*{ степень:превосх } : export { node:root_node РОД ПАДЕЖ ЧИСЛО }
} : links { a.<NEGATION_PARTICLE>n }

// атрибутирующие прилагательные для подлежащего в именительном падеже
word_nonterm A_nom_f { ВОСХ_ПрилАтриб{ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:ЖЕН } }
word_nonterm A_nom_m { ВОСХ_ПрилАтриб{ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:МУЖ } }
word_nonterm A_nom_n { ВОСХ_ПрилАтриб{ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:СР } }
word_nonterm A_nom_pl { ВОСХ_ПрилАтриб{ ПАДЕЖ:ИМ ЧИСЛО:МН } }

// атрибутирующие прилагательные в родительном падеже
word_nonterm A_gen_f { ВОСХ_ПрилАтриб{ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:ЖЕН } }
word_nonterm A_gen_m { ВОСХ_ПрилАтриб{ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:МУЖ } }
word_nonterm A_gen_n { ВОСХ_ПрилАтриб{ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:СР } }
word_nonterm A_gen_pl { ВОСХ_ПрилАтриб{ ПАДЕЖ:РОД ЧИСЛО:МН } }

// атрибутирующие прилагательные в творительном падеже
word_nonterm A_ins_f { ВОСХ_ПрилАтриб{ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:ЖЕН } }
word_nonterm A_ins_m { ВОСХ_ПрилАтриб{ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:МУЖ } }
word_nonterm A_ins_n { ВОСХ_ПрилАтриб{ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:СР } }
word_nonterm A_ins_pl { ВОСХ_ПрилАтриб{ ПАДЕЖ:ТВОР ЧИСЛО:МН } }

// атрибутирующие прилагательные в винительном падеже
// TODO: для мужского рода надо делать различия для одушевленных и неодушевленных
word_nonterm A_acc_f { ВОСХ_ПрилАтриб{ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:ЖЕН } }
word_nonterm A_acc_m { ВОСХ_ПрилАтриб{ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:МУЖ } }
word_nonterm A_acc_n { ВОСХ_ПрилАтриб{ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:СР } }
word_nonterm A_acc_pl { ВОСХ_ПрилАтриб{ ПАДЕЖ:ВИН ЧИСЛО:МН } }

// атрибутирующие прилагательные в дательном падеже
word_nonterm A_dat_f { ВОСХ_ПрилАтриб{ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:ЖЕН } }
word_nonterm A_dat_m { ВОСХ_ПрилАтриб{ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:МУЖ } }
word_nonterm A_dat_n { ВОСХ_ПрилАтриб{ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:СР } }
word_nonterm A_dat_pl { ВОСХ_ПрилАтриб{ ПАДЕЖ:ДАТ ЧИСЛО:МН } }

// атрибутирующие прилагательные в предложном падеже
word_nonterm A_prep_f { ВОСХ_ПрилАтриб{ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:ЖЕН } }
word_nonterm A_prep_m { ВОСХ_ПрилАтриб{ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:МУЖ } }
word_nonterm A_prep_n { ВОСХ_ПрилАтриб{ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:СР } }
word_nonterm A_prep_pl { ВОСХ_ПрилАтриб{ ПАДЕЖ:ПРЕДЛ ЧИСЛО:МН } }



// Краткие прилагательные
patterns ВОСХ_КраткПрил export { node:root_node РОД ЧИСЛО }

pattern ВОСХ_КраткПрил
{
 прилагательное:*{ КРАТКИЙ } : export { node:root_node РОД ЧИСЛО }
}

word_nonterm AS_f { ВОСХ_КраткПрил{ ЧИСЛО:ЕД РОД:ЖЕН } }
word_nonterm AS_m { ВОСХ_КраткПрил{ ЧИСЛО:ЕД РОД:МУЖ } }
word_nonterm AS_n { ВОСХ_КраткПрил{ ЧИСЛО:ЕД РОД:СР } }
word_nonterm AS_pl { ВОСХ_КраткПрил{ ЧИСЛО:МН } }


// ------- ГЛАГОЛЫ-СВЯЗКИ

patterns ВОСХ_ГлСвязкаПрош export { node:root_node РОД ЧИСЛО }

pattern ВОСХ_ГлСвязкаПрош
{
 глагол:быть{ ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node РОД ЧИСЛО }
}

word_nonterm CV_f { ВОСХ_ГлСвязкаПрош{ ЧИСЛО:ЕД РОД:ЖЕН } }
word_nonterm CV_m { ВОСХ_ГлСвязкаПрош{ ЧИСЛО:ЕД РОД:МУЖ } }
word_nonterm CV_n { ВОСХ_ГлСвязкаПрош{ ЧИСЛО:ЕД РОД:СР } }
word_nonterm CV_pl { ВОСХ_ГлСвязкаПрош{ ЧИСЛО:МН } }



// ##########################################################
// --------------------- СУЩЕСТВИТЕЛЬНОЕ --------------------
// ##########################################################

// существительные в именительном падеже
word_nonterm N_nom_f { существительное:*{ падеж:им число:ед род:жен } }
word_nonterm N_nom_m { существительное:*{ падеж:им число:ед род:муж } }
word_nonterm N_nom_n { существительное:*{ падеж:им число:ед род:ср } }
word_nonterm N_nom_pl { существительное:*{ падеж:им число:мн } }

// существительные в родительном падеже (и в партитиве)
word_nonterm N_gen_f { существительное:*{ падеж:род число:ед род:жен } }
word_nonterm N_gen_f { существительное:*{ падеж:парт число:ед род:жен } }
word_nonterm N_gen_m { существительное:*{ падеж:род число:ед род:муж } }
word_nonterm N_gen_m { существительное:*{ падеж:парт число:ед род:муж } }
word_nonterm N_gen_n { существительное:*{ падеж:род число:ед род:ср } }
word_nonterm N_gen_pl { существительное:*{ падеж:род число:мн } }

// существительные в творительном падеже
word_nonterm N_ins_f { существительное:*{ падеж:твор число:ед род:жен } }
word_nonterm N_ins_m { существительное:*{ падеж:твор число:ед род:муж } }
word_nonterm N_ins_n { существительное:*{ падеж:твор число:ед род:ср } }
word_nonterm N_ins_pl { существительное:*{ падеж:твор число:мн } }

// существительные в винительном падеже (TODO: для правильного согласования с прилагательными
// необходимо учитывать отдельно одушевленные и неодушевленные).
word_nonterm N_acc_f { существительное:*{ падеж:вин число:ед род:жен } }
word_nonterm N_acc_m { существительное:*{ падеж:вин число:ед род:муж } }
word_nonterm N_acc_n { существительное:*{ падеж:вин число:ед род:ср } }
word_nonterm N_acc_pl { существительное:*{ падеж:вин число:мн } }

// существительные в дательном падеже
word_nonterm N_dat_f { существительное:*{ падеж:дат число:ед род:жен } }
word_nonterm N_dat_m { существительное:*{ падеж:дат число:ед род:муж } }
word_nonterm N_dat_n { существительное:*{ падеж:дат число:ед род:ср } }
word_nonterm N_dat_pl { существительное:*{ падеж:дат число:мн } }

// существительные в предложном и местном падеже
word_nonterm N_prep_f { существительное:*{ падеж:предл число:ед род:жен } }
word_nonterm N_prep_f { существительное:*{ падеж:мест число:ед род:жен } }
word_nonterm N_prep_m { существительное:*{ падеж:предл число:ед род:муж } }
word_nonterm N_prep_m { существительное:*{ падеж:мест число:ед род:муж } }
word_nonterm N_prep_n { существительное:*{ падеж:предл число:ед род:ср } }
word_nonterm N_prep_pl { существительное:*{ падеж:предл число:мн } }

// ФИО будем считать существительным в любом падеже
word_nonterm PERSON { ФИО }


// ##############################################################
// ---------------------- МЕСТОИМЕНИЕ -------------------------
// ##############################################################

// --- именительный

word_nonterm PRN_nom_1_sg { местоимение:*{ падеж:им лицо:1 число:ед } }
word_nonterm PRN_nom_1_sg { местоим_сущ:*{ падеж:им } } // кто работает
word_nonterm PRN_nom_2_sg { местоимение:*{ падеж:им лицо:2 число:ед } }
word_nonterm PRN_nom_3_sg { местоимение:*{ падеж:им лицо:3 число:ед } }

word_nonterm PRN_nom_1_pl { местоимение:*{ падеж:им лицо:1 число:мн } }
word_nonterm PRN_nom_2_pl { местоимение:*{ падеж:им лицо:2 число:мн } }
word_nonterm PRN_nom_3_pl { местоимение:*{ падеж:им лицо:3 число:мн } }

word_nonterm PRN_nom_f { местоимение:*{ падеж:им род:жен } }
word_nonterm PRN_nom_f { местоимение:*{ падеж:им лицо:1 число:ед } } // я устала
word_nonterm PRN_nom_f { местоимение:*{ падеж:им лицо:2 число:ед } } // ты устала

word_nonterm PRN_nom_m { местоимение:*{ падеж:им род:муж } }
word_nonterm PRN_nom_m { местоимение:*{ падеж:им лицо:1 число:ед } } // я устал
word_nonterm PRN_nom_m { местоимение:*{ падеж:им лицо:2 число:ед } } // ты устал
word_nonterm PRN_nom_m { местоим_сущ:кто{ падеж:им } } // кто устал
word_nonterm PRN_nom_m { местоим_сущ:кто-то{ падеж:им } } // кто-то пришел
word_nonterm PRN_nom_m { местоим_сущ:кто-нибудь{ падеж:им } } // кто-нибудь сделал
word_nonterm PRN_nom_m { местоим_сущ:кто-либо{ падеж:им } } // кто-либо справился
word_nonterm PRN_nom_m { местоим_сущ:некто{ падеж:им } } // некто пришел

word_nonterm PRN_nom_n { местоимение:*{ падеж:им род:ср } }
word_nonterm PRN_nom_n { местоимение:*{ падеж:им лицо:1 число:ед } } // я устало
word_nonterm PRN_nom_n { местоимение:*{ падеж:им лицо:2 число:ед } } // ты устало
word_nonterm PRN_nom_n { местоим_сущ:что{ падеж:им } } // что случилось
word_nonterm PRN_nom_n { местоим_сущ:что-то{ падеж:им } } // что-то случилось
word_nonterm PRN_nom_n { местоим_сущ:что-нибудь{ падеж:им } } // что-нибудь произошло
word_nonterm PRN_nom_n { местоим_сущ:что-либо{ падеж:им } } // что-либо случилось
word_nonterm PRN_nom_n { местоим_сущ:нечто{ падеж:им } } // нечто случилось

word_nonterm PRN_nom_pl { местоимение:*{ падеж:им число:мн } } // мы устали


word_nonterm PRN_nom { местоимение:*{ падеж:им } }
word_nonterm PRN_nom { местоим_сущ:*{ падеж:им } }

// --- родительный
word_nonterm PRN_gen { местоимение:*{ падеж:род } }
word_nonterm PRN_gen { местоим_сущ:*{ падеж:род } }

// --- творительный
word_nonterm PRN_ins { местоимение:*{ падеж:твор } }
word_nonterm PRN_ins { местоим_сущ:*{ падеж:твор } }

// --- винительный
word_nonterm PRN_acc { местоимение:*{ падеж:вин } }
word_nonterm PRN_acc { местоим_сущ:*{ падеж:вин } }

// --- дательный
word_nonterm PRN_dat { местоимение:*{ падеж:дат } }
word_nonterm PRN_dat { местоим_сущ:*{ падеж:дат } }

// --- предложный
word_nonterm PRN_prep { местоимение:*{ падеж:предл } }
word_nonterm PRN_prep { местоим_сущ:*{ падеж:предл } }



// ---------------------- ПРЕДЛОГ -------------------------

word_nonterm P_gen { предлог:*{ падеж:род } }
//word_nonterm P_gen { предлог:*{ падеж:парт } }
word_nonterm P_ins { предлог:*{ падеж:твор } }
word_nonterm P_acc { предлог:*{ падеж:вин } }
word_nonterm P_dat { предлог:*{ падеж:дат } }
word_nonterm P_prep { предлог:*{ падеж:предл } }
//word_nonterm P_prep { предлог:*{ падеж:мест } }



// --------------------- ЧИСЛА ----------------------

word_nonterm D { num_word:*{} }
word_nonterm D { числительное:*{} }



// ########################################################################
// ========================= ПРАВИЛА СВЯЗЫВАНИЯ ===========================
// ########################################################################



// JP - это соединитель, участвующий в союзных паттернах
// Кошка и собака
cyk_rule JP { J }
// Кошка, собака и мышка
cyk_rule JP { COMMA }
cyk_rule JP { COMMA J } : links { COMMA.<RIGHT_LOGIC_ITEM>J } : ngrams { -1 }

// союз для присоединения второй части в конструкциях типа
// И МАМА, И ПАПА
cyk_rule JP2 { COMMA J2 } : links { J2.<PUNCTUATION>COMMA } // обычно вторая часть союзного паттерна пишется через запятую
cyk_rule JP2 { J2 } : ngrams { -1 } // пропуск запятой в союзном паттерне: и кошка и собака


// JVP - союзы для глагольных паттернов
cyk_rule JVP { JV }
cyk_rule JVP { COMMA }
cyk_rule JVP { COMMA JV } : links { COMMA.<RIGHT_LOGIC_ITEM>JV } : ngrams { -1 }



// ====================
// наречная группа
// ====================

// Не очень много сделать
//    ^^^^^^^^^^^
cyk_rule Y { Ym Y } : links { Y.<ATTRIBUTE>Ym } : ngrams { ngram2(Ym,Y) }


// Союзные конструкции для наречий:
// быстро и дешево
cyk_rule YJ { JP Y } : links { JP.<OBJECT>Y }
cyk_rule Y { Y YJ } : links { Y.<RIGHT_LOGIC_ITEM>YJ }

cyk_rule YJ1 { J2 obj=Y } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule YJ2 { JP2 obj=Y } : links { JP2.<OBJECT>obj }

// и быстро, и дешево
cyk_rule Y  { y1=YJ1 y2=YJ2 } : links { y1.<RIGHT_LOGIC_ITEM>y2 }


// связывание по умолчанию
cyk_rule Y { z='*' Y } : links { Y.z } : ngrams { -2 }
cyk_rule Y { Y z='*' } : links { Y.z } : ngrams { -2 }


// --- разбор конструкций с наречием в корне
cyk_rule S { Y } : ngrams { -4 }



// ======================
// группа прилагательного
// ======================

// --- именительный падеж

cyk_rule AP_nom_f { A_nom_f }
cyk_rule AP_nom_f { Y A_nom_f } : links { A_nom_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,A_nom_f) }
cyk_rule AP_nom_f { a1=A_nom_f a2=A_nom_f } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_nom_m { A_nom_m }
cyk_rule AP_nom_m { Y A_nom_m } : links { A_nom_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,A_nom_m) }
cyk_rule AP_nom_m { a1=A_nom_m a2=A_nom_m } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_nom_n { A_nom_n }
cyk_rule AP_nom_n { Y A_nom_n } : links { A_nom_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,A_nom_n) }
cyk_rule AP_nom_n { a1=A_nom_n a2=A_nom_n } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_nom_pl { A_nom_pl }
cyk_rule AP_nom_pl { Y A_nom_pl } : links { A_nom_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,A_nom_pl) }
cyk_rule AP_nom_pl { a1=A_nom_pl a2=A_nom_pl } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }


// -----------------------------------------
// Союзные конструкции для прилагательного:

// быстрый и ловкий
//         ^^^^^^^^
cyk_rule APJ_nom_f { JP AP_nom_f } : links { JP.<OBJECT>AP_nom_f }
cyk_rule APJ_nom_m { JP AP_nom_m } : links { JP.<OBJECT>AP_nom_m }
cyk_rule APJ_nom_n { JP AP_nom_n } : links { JP.<OBJECT>AP_nom_n }
cyk_rule APJ_nom_pl { JP AP_nom_pl } : links { JP.<OBJECT>AP_nom_pl }

// прикрепляем справа союз и второе прилагательное:
// быстрый и ловкий
// ^^^^^^^^^^^^^^^^
cyk_rule AP_nom_f  { a1=AP_nom_f a2=APJ_nom_f } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_nom_m  { a1=AP_nom_m a2=APJ_nom_m } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_nom_n  { a1=AP_nom_n a2=APJ_nom_n } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_nom_pl { a1=AP_nom_pl a2=APJ_nom_pl } : links { a1.<RIGHT_LOGIC_ITEM>a2 }

cyk_rule APJ1_nom_f { J2 obj=AP_nom_f } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_nom_f { JP2 obj=AP_nom_f } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_nom_m { J2 obj=AP_nom_m } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_nom_m { JP2 obj=AP_nom_m } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_nom_n { J2 obj=AP_nom_n } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_nom_n { JP2 obj=AP_nom_n } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_nom_pl { J2 obj=AP_nom_pl } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_nom_pl { JP2 obj=AP_nom_pl } : links { JP2.<OBJECT>obj }


// и быстрый, и ловкий
cyk_rule AP_nom_f { a1=APJ1_nom_f a2=APJ2_nom_f } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_nom_n { a1=APJ1_nom_n a2=APJ2_nom_n } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_nom_m { a1=APJ1_nom_m a2=APJ2_nom_m } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_nom_pl { a1=APJ1_nom_pl a2=APJ2_nom_pl } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
// ---- конец правил для союзных паттернов




cyk_rule A_nom_f { z='*' A_nom_f } : links { A_nom_f.z } : ngrams { -2 }
cyk_rule A_nom_f { A_nom_f z='*' } : links { A_nom_f.z } : ngrams { -2 }
cyk_rule A_nom_m { z='*' A_nom_m } : links { A_nom_m.z } : ngrams { -2 }
cyk_rule A_nom_m { A_nom_m z='*' } : links { A_nom_m.z } : ngrams { -2 }
cyk_rule A_nom_n { z='*' A_nom_n } : links { A_nom_n.z } : ngrams { -2 }
cyk_rule A_nom_n { A_nom_n z='*' } : links { A_nom_n.z } : ngrams { -2 }
cyk_rule A_nom_pl { z='*' A_nom_pl } : links { A_nom_pl.z } : ngrams { -2 }
cyk_rule A_nom_pl { A_nom_pl z='*' } : links { A_nom_pl.z } : ngrams { -2 }

cyk_rule S { AP_nom_f } : ngrams { -4 }
cyk_rule S { AP_nom_m } : ngrams { -4 }
cyk_rule S { AP_nom_n } : ngrams { -4 }
cyk_rule S { AP_nom_pl } : ngrams { -4 }

// --- родительный падеж

cyk_rule AP_gen_f { A_gen_f }
cyk_rule AP_gen_f { Y A_gen_f } : links { A_gen_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,A_gen_f) }
cyk_rule AP_gen_f { a1=A_gen_f a2=A_gen_f } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_gen_m { A_gen_m }
cyk_rule AP_gen_m { Y AP_gen_m } : links { AP_gen_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AP_gen_m) }
cyk_rule AP_gen_m { a1=AP_gen_m a2=AP_gen_m } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_gen_n { A_gen_n }
cyk_rule AP_gen_n { Y AP_gen_n } : links { AP_gen_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AP_gen_n) }
cyk_rule AP_gen_n { a1=AP_gen_n a2=AP_gen_n } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_gen_pl { A_gen_pl }
cyk_rule AP_gen_pl { Y AP_gen_pl } : links { AP_gen_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AP_gen_pl) }
cyk_rule AP_gen_pl { a1=AP_gen_pl a2=AP_gen_pl } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }



// -----------------------------------------
// Союзные конструкции для прилагательного:

// от быстрой и ловкой собаки
//            ^^^^^^^^
cyk_rule APJ_gen_f { JP AP_gen_f } : links { JP.<OBJECT>AP_gen_f }
cyk_rule APJ_gen_m { JP AP_gen_m } : links { JP.<OBJECT>AP_gen_m }
cyk_rule APJ_gen_n { JP AP_gen_n } : links { JP.<OBJECT>AP_gen_n }
cyk_rule APJ_gen_pl { JP AP_gen_pl } : links { JP.<OBJECT>AP_gen_pl }

// прикрепляем справа союз и второе прилагательное:
// от быстрой и ловкой собаки
//    ^^^^^^^^^^^^^^^^
cyk_rule AP_gen_f  { a1=AP_gen_f a2=APJ_gen_f } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_gen_m  { a1=AP_gen_m a2=APJ_gen_m } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_gen_n  { a1=AP_gen_n a2=APJ_gen_n } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_gen_pl { a1=AP_gen_pl a2=APJ_gen_pl } : links { a1.<RIGHT_LOGIC_ITEM>a2 }

cyk_rule APJ1_gen_f { J2 obj=AP_gen_f } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_gen_f { JP2 obj=AP_gen_f } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_gen_m { J2 obj=AP_gen_m } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_gen_m { JP2 obj=AP_gen_m } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_gen_n { J2 obj=AP_gen_n } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_gen_n { JP2 obj=AP_gen_n } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_gen_pl { J2 obj=AP_gen_pl } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_gen_pl { JP2 obj=AP_gen_pl } : links { JP2.<OBJECT>obj }


// и быстрой, и ловкой
cyk_rule AP_gen_f { a1=APJ1_gen_f a2=APJ2_gen_f } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_gen_n { a1=APJ1_gen_n a2=APJ2_gen_n } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_gen_m { a1=APJ1_gen_m a2=APJ2_gen_m } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_gen_pl { a1=APJ1_gen_pl a2=APJ2_gen_pl } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
// ---- конец правил для союзных паттернов



cyk_rule A_gen_f { z='*' A_gen_f } : links { A_gen_f.z } : ngrams { -2 }
cyk_rule A_gen_f { A_gen_f z='*' } : links { A_gen_f.z } : ngrams { -2 }
cyk_rule A_gen_m { z='*' A_gen_m } : links { A_gen_m.z } : ngrams { -2 }
cyk_rule A_gen_m { A_gen_m z='*' } : links { A_gen_m.z } : ngrams { -2 }
cyk_rule A_gen_n { z='*' A_gen_n } : links { A_gen_n.z } : ngrams { -2 }
cyk_rule A_gen_n { A_gen_n z='*' } : links { A_gen_n.z } : ngrams { -2 }
cyk_rule A_gen_pl { z='*' A_gen_pl } : links { A_gen_pl.z } : ngrams { -2 }
cyk_rule A_gen_pl { A_gen_pl z='*' } : links { A_gen_pl.z } : ngrams { -2 }

cyk_rule S { AP_gen_f } : ngrams { -4 }
cyk_rule S { AP_gen_m } : ngrams { -4 }
cyk_rule S { AP_gen_n } : ngrams { -4 }
cyk_rule S { AP_gen_pl } : ngrams { -4 }


// --- творительный падеж

cyk_rule AP_ins_f { A_ins_f }
cyk_rule AP_ins_f { Y A_ins_f } : links { A_ins_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,A_ins_f) }
cyk_rule AP_ins_f { a1=A_ins_f a2=A_ins_f } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_ins_m { A_ins_m }
cyk_rule AP_ins_m { Y AP_ins_m } : links { AP_ins_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AP_ins_m) }
cyk_rule AP_ins_m { a1=AP_ins_m a2=AP_ins_m } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_ins_n { A_ins_n }
cyk_rule AP_ins_n { Y AP_ins_n } : links { AP_ins_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AP_ins_n) }
cyk_rule AP_ins_n { a1=AP_ins_n a2=AP_ins_n } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_ins_pl { A_ins_pl }
cyk_rule AP_ins_pl { Y AP_ins_pl } : links { AP_ins_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AP_ins_pl) }
cyk_rule AP_ins_pl { a1=AP_ins_pl a2=AP_ins_pl } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }



// -----------------------------------------
// Союзные конструкции для прилагательного:

// с быстрым и ловким
//           ^^^^^^^^
cyk_rule APJ_ins_f { JP AP_ins_f } : links { JP.<OBJECT>AP_ins_f }
cyk_rule APJ_ins_m { JP AP_ins_m } : links { JP.<OBJECT>AP_ins_m }
cyk_rule APJ_ins_n { JP AP_ins_n } : links { JP.<OBJECT>AP_ins_n }
cyk_rule APJ_ins_pl { JP AP_ins_pl } : links { JP.<OBJECT>AP_ins_pl }

// прикрепляем справа союз и второе прилагательное:
// с быстрым и ловким псом
// ^^^^^^^^^^^^^^^^^^
cyk_rule AP_ins_f  { a1=AP_ins_f a2=APJ_ins_f } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_ins_m  { a1=AP_ins_m a2=APJ_ins_m } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_ins_n  { a1=AP_ins_n a2=APJ_ins_n } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_ins_pl { a1=AP_ins_pl a2=APJ_ins_pl } : links { a1.<RIGHT_LOGIC_ITEM>a2 }

cyk_rule APJ1_ins_f { J2 obj=AP_ins_f } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_ins_f { JP2 obj=AP_ins_f } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_ins_m { J2 obj=AP_ins_m } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_ins_m { JP2 obj=AP_ins_m } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_ins_n { J2 obj=AP_ins_n } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_ins_n { JP2 obj=AP_ins_n } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_ins_pl { J2 obj=AP_ins_pl } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_ins_pl { JP2 obj=AP_ins_pl } : links { JP2.<OBJECT>obj }


// и быстрым, и ловким
cyk_rule AP_ins_f { a1=APJ1_ins_f a2=APJ2_ins_f } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_ins_n { a1=APJ1_ins_n a2=APJ2_ins_n } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_ins_m { a1=APJ1_ins_m a2=APJ2_ins_m } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_ins_pl { a1=APJ1_ins_pl a2=APJ2_ins_pl } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
// ---- конец правил для союзных паттернов




cyk_rule A_ins_f { z='*' A_ins_f } : links { A_ins_f.z } : ngrams { -2 }
cyk_rule A_ins_f { A_ins_f z='*' } : links { A_ins_f.z } : ngrams { -2 }
cyk_rule A_ins_m { z='*' A_ins_m } : links { A_ins_m.z } : ngrams { -2 }
cyk_rule A_ins_m { A_ins_m z='*' } : links { A_ins_m.z } : ngrams { -2 }
cyk_rule A_ins_n { z='*' A_ins_n } : links { A_ins_n.z } : ngrams { -2 }
cyk_rule A_ins_n { A_ins_n z='*' } : links { A_ins_n.z } : ngrams { -2 }
cyk_rule A_ins_pl { z='*' A_ins_pl } : links { A_ins_pl.z } : ngrams { -2 }
cyk_rule A_ins_pl { A_ins_pl z='*' } : links { A_ins_pl.z } : ngrams { -2 }

cyk_rule S { AP_ins_f } : ngrams { -4 }
cyk_rule S { AP_ins_m } : ngrams { -4 }
cyk_rule S { AP_ins_n } : ngrams { -4 }
cyk_rule S { AP_ins_pl } : ngrams { -4 }



// --- винительный падеж

cyk_rule AP_acc_f { A_acc_f }
cyk_rule AP_acc_f { Y A_acc_f } : links { A_acc_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,A_acc_f) }
cyk_rule AP_acc_f { a1=A_acc_f a2=A_acc_f } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_acc_m { A_acc_m }
cyk_rule AP_acc_m { Y AP_acc_m } : links { AP_acc_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AP_acc_m) }
cyk_rule AP_acc_m { a1=AP_acc_m a2=AP_acc_m } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_acc_n { A_acc_n }
cyk_rule AP_acc_n { Y AP_acc_n } : links { AP_acc_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AP_acc_n) }
cyk_rule AP_acc_n { a1=AP_acc_n a2=AP_acc_n } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_acc_pl { A_acc_pl }
cyk_rule AP_acc_pl { Y AP_acc_pl } : links { AP_acc_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AP_acc_pl) }
cyk_rule AP_acc_pl { a1=AP_acc_pl a2=AP_acc_pl } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }



// -----------------------------------------
// Союзные конструкции для прилагательного:

// быструю и ловкую собаку
//         ^^^^^^^^
cyk_rule APJ_acc_f { JP AP_acc_f } : links { JP.<OBJECT>AP_acc_f }
cyk_rule APJ_acc_m { JP AP_acc_m } : links { JP.<OBJECT>AP_acc_m }
cyk_rule APJ_acc_n { JP AP_acc_n } : links { JP.<OBJECT>AP_acc_n }
cyk_rule APJ_acc_pl { JP AP_acc_pl } : links { JP.<OBJECT>AP_acc_pl }

// прикрепляем справа союз и второе прилагательное:
// быструю и ловкую собаку
// ^^^^^^^^^^^^^^^^
cyk_rule AP_acc_f  { a1=AP_acc_f a2=APJ_acc_f } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_acc_m  { a1=AP_acc_m a2=APJ_acc_m } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_acc_n  { a1=AP_acc_n a2=APJ_acc_n } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_acc_pl { a1=AP_acc_pl a2=APJ_acc_pl } : links { a1.<RIGHT_LOGIC_ITEM>a2 }

cyk_rule APJ1_acc_f { J2 obj=AP_acc_f } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_acc_f { JP2 obj=AP_acc_f } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_acc_m { J2 obj=AP_acc_m } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_acc_m { JP2 obj=AP_acc_m } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_acc_n { J2 obj=AP_acc_n } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_acc_n { JP2 obj=AP_acc_n } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_acc_pl { J2 obj=AP_acc_pl } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_acc_pl { JP2 obj=AP_acc_pl } : links { JP2.<OBJECT>obj }


// и быструю, и ловкую
cyk_rule AP_acc_f { a1=APJ1_acc_f a2=APJ2_acc_f } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_acc_n { a1=APJ1_acc_n a2=APJ2_acc_n } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_acc_m { a1=APJ1_acc_m a2=APJ2_acc_m } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_acc_pl { a1=APJ1_acc_pl a2=APJ2_acc_pl } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
// ---- конец правил для союзных паттернов




cyk_rule A_acc_f { z='*' A_acc_f } : links { A_acc_f.z } : ngrams { -2 }
cyk_rule A_acc_f { A_acc_f z='*' } : links { A_acc_f.z } : ngrams { -2 }
cyk_rule A_acc_m { z='*' A_acc_m } : links { A_acc_m.z } : ngrams { -2 }
cyk_rule A_acc_m { A_acc_m z='*' } : links { A_acc_m.z } : ngrams { -2 }
cyk_rule A_acc_n { z='*' A_acc_n } : links { A_acc_n.z } : ngrams { -2 }
cyk_rule A_acc_n { A_acc_n z='*' } : links { A_acc_n.z } : ngrams { -2 }
cyk_rule A_acc_pl { z='*' A_acc_pl } : links { A_acc_pl.z } : ngrams { -2 }
cyk_rule A_acc_pl { A_acc_pl z='*' } : links { A_acc_pl.z } : ngrams { -2 }

cyk_rule S { AP_acc_f } : ngrams { -4 }
cyk_rule S { AP_acc_m } : ngrams { -4 }
cyk_rule S { AP_acc_n } : ngrams { -4 }
cyk_rule S { AP_acc_pl } : ngrams { -4 }

// --- дательный падеж

cyk_rule AP_dat_f { A_dat_f }
cyk_rule AP_dat_f { Y A_dat_f } : links { A_dat_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,A_dat_f) }
cyk_rule AP_dat_f { a1=A_dat_f a2=A_dat_f } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_dat_m { A_dat_m }
cyk_rule AP_dat_m { Y AP_dat_m } : links { AP_dat_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AP_dat_m) }
cyk_rule AP_dat_m { a1=AP_dat_m a2=AP_dat_m } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_dat_n { A_dat_n }
cyk_rule AP_dat_n { Y AP_dat_n } : links { AP_dat_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AP_dat_n) }
cyk_rule AP_dat_n { a1=AP_dat_n a2=AP_dat_n } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_dat_pl { A_dat_pl }
cyk_rule AP_dat_pl { Y AP_dat_pl } : links { AP_dat_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AP_dat_pl) }
cyk_rule AP_dat_pl { a1=AP_dat_pl a2=AP_dat_pl } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }


// -----------------------------------------
// Союзные конструкции для прилагательного:

// быстрой и ловкой
//         ^^^^^^^^
cyk_rule APJ_dat_f { JP AP_dat_f } : links { JP.<OBJECT>AP_dat_f }
cyk_rule APJ_dat_m { JP AP_dat_m } : links { JP.<OBJECT>AP_dat_m }
cyk_rule APJ_dat_n { JP AP_dat_n } : links { JP.<OBJECT>AP_dat_n }
cyk_rule APJ_dat_pl { JP AP_dat_pl } : links { JP.<OBJECT>AP_dat_pl }

// прикрепляем справа союз и второе прилагательное:
// быстрой и ловкой
// ^^^^^^^^^^^^^^^^
cyk_rule AP_dat_f  { a1=AP_dat_f a2=APJ_dat_f } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_dat_m  { a1=AP_dat_m a2=APJ_dat_m } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_dat_n  { a1=AP_dat_n a2=APJ_dat_n } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_dat_pl { a1=AP_dat_pl a2=APJ_dat_pl } : links { a1.<RIGHT_LOGIC_ITEM>a2 }

cyk_rule APJ1_dat_f { J2 obj=AP_dat_f } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_dat_f { JP2 obj=AP_dat_f } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_dat_m { J2 obj=AP_dat_m } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_dat_m { JP2 obj=AP_dat_m } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_dat_n { J2 obj=AP_dat_n } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_dat_n { JP2 obj=AP_dat_n } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_dat_pl { J2 obj=AP_dat_pl } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_dat_pl { JP2 obj=AP_dat_pl } : links { JP2.<OBJECT>obj }


// и быстрой, и ловкой
cyk_rule AP_dat_f { a1=APJ1_dat_f a2=APJ2_dat_f } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_dat_n { a1=APJ1_dat_n a2=APJ2_dat_n } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_dat_m { a1=APJ1_dat_m a2=APJ2_dat_m } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_dat_pl { a1=APJ1_dat_pl a2=APJ2_dat_pl } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
// ---- конец правил для союзных паттернов




cyk_rule A_dat_f { z='*' A_dat_f } : links { A_dat_f.z } : ngrams { -2 }
cyk_rule A_dat_f { A_dat_f z='*' } : links { A_dat_f.z } : ngrams { -2 }
cyk_rule A_dat_m { z='*' A_dat_m } : links { A_dat_m.z } : ngrams { -2 }
cyk_rule A_dat_m { A_dat_m z='*' } : links { A_dat_m.z } : ngrams { -2 }
cyk_rule A_dat_n { z='*' A_dat_n } : links { A_dat_n.z } : ngrams { -2 }
cyk_rule A_dat_n { A_dat_n z='*' } : links { A_dat_n.z } : ngrams { -2 }
cyk_rule A_dat_pl { z='*' A_dat_pl } : links { A_dat_pl.z } : ngrams { -2 }
cyk_rule A_dat_pl { A_dat_pl z='*' } : links { A_dat_pl.z } : ngrams { -2 }

cyk_rule S { AP_dat_f } : ngrams { -4 }
cyk_rule S { AP_dat_m } : ngrams { -4 }
cyk_rule S { AP_dat_n } : ngrams { -4 }
cyk_rule S { AP_dat_pl } : ngrams { -4 }

// --- предложный падеж

cyk_rule AP_prep_f { A_prep_f }
cyk_rule AP_prep_f { Y A_prep_f } : links { A_prep_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,A_prep_f) }
cyk_rule AP_prep_f { a1=A_prep_f a2=A_prep_f } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_prep_m { A_prep_m }
cyk_rule AP_prep_m { Y AP_prep_m } : links { AP_prep_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AP_prep_m) }
cyk_rule AP_prep_m { a1=AP_prep_m a2=AP_prep_m } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_prep_n { A_prep_n }
cyk_rule AP_prep_n { Y AP_prep_n } : links { AP_prep_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AP_prep_n) }
cyk_rule AP_prep_n { a1=AP_prep_n a2=AP_prep_n } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }

cyk_rule AP_prep_pl { A_prep_pl }
cyk_rule AP_prep_pl { Y AP_prep_pl } : links { AP_prep_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AP_prep_pl) }
cyk_rule AP_prep_pl { a1=AP_prep_pl a2=AP_prep_pl } : links { a1.<NEXT_ADJECTIVE>a2 } : ngrams { ngram2(a1,a2) }


// -----------------------------------------
// Союзные конструкции для прилагательного:

// о быстрой и ловкой
//           ^^^^^^^^
cyk_rule APJ_prep_f { JP AP_prep_f } : links { JP.<OBJECT>AP_prep_f }
cyk_rule APJ_prep_m { JP AP_prep_m } : links { JP.<OBJECT>AP_prep_m }
cyk_rule APJ_prep_n { JP AP_prep_n } : links { JP.<OBJECT>AP_prep_n }
cyk_rule APJ_prep_pl { JP AP_prep_pl } : links { JP.<OBJECT>AP_prep_pl }

// прикрепляем справа союз и второе прилагательное:
// о быстрой и ловкой
// ^^^^^^^^^^^^^^^^^^
cyk_rule AP_prep_f  { a1=AP_prep_f a2=APJ_prep_f } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_prep_m  { a1=AP_prep_m a2=APJ_prep_m } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_prep_n  { a1=AP_prep_n a2=APJ_prep_n } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_prep_pl { a1=AP_prep_pl a2=APJ_prep_pl } : links { a1.<RIGHT_LOGIC_ITEM>a2 }

cyk_rule APJ1_prep_f { J2 obj=AP_prep_f } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_prep_f { JP2 obj=AP_prep_f } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_prep_m { J2 obj=AP_prep_m } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_prep_m { JP2 obj=AP_prep_m } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_prep_n { J2 obj=AP_prep_n } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_prep_n { JP2 obj=AP_prep_n } : links { JP2.<OBJECT>obj }

cyk_rule APJ1_prep_pl { J2 obj=AP_prep_pl } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule APJ2_prep_pl { JP2 obj=AP_prep_pl } : links { JP2.<OBJECT>obj }


// и быстрой, и ловкой
cyk_rule AP_prep_f { a1=APJ1_prep_f a2=APJ2_prep_f } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_prep_n { a1=APJ1_prep_n a2=APJ2_prep_n } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_prep_m { a1=APJ1_prep_m a2=APJ2_prep_m } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
cyk_rule AP_prep_pl { a1=APJ1_prep_pl a2=APJ2_prep_pl } : links { a1.<RIGHT_LOGIC_ITEM>a2 }
// ---- конец правил для союзных паттернов


cyk_rule A_prep_f { z='*' A_prep_f } : links { A_prep_f.z } : ngrams { -2 }
cyk_rule A_prep_f { A_prep_f z='*' } : links { A_prep_f.z } : ngrams { -2 }
cyk_rule A_prep_m { z='*' A_prep_m } : links { A_prep_m.z } : ngrams { -2 }
cyk_rule A_prep_m { A_prep_m z='*' } : links { A_prep_m.z } : ngrams { -2 }
cyk_rule A_prep_n { z='*' A_prep_n } : links { A_prep_n.z } : ngrams { -2 }
cyk_rule A_prep_n { A_prep_n z='*' } : links { A_prep_n.z } : ngrams { -2 }
cyk_rule A_prep_pl { z='*' A_prep_pl } : links { A_prep_pl.z } : ngrams { -2 }
cyk_rule A_prep_pl { A_prep_pl z='*' } : links { A_prep_pl.z } : ngrams { -2 }

cyk_rule S { AP_prep_f } : ngrams { -4 }
cyk_rule S { AP_prep_m } : ngrams { -4 }
cyk_rule S { AP_prep_n } : ngrams { -4 }
cyk_rule S { AP_prep_pl } : ngrams { -4 }


// ###############################################
// ПРИЧАСТНЫЙ ОБОРОТ
// ###############################################


// -------------------------------------
// --- именительный падеж, жен.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_nom_f { AVt_nom_f }  : ngrams { -1 }
cyk_rule AAPit_nom_f { AVit_nom_f } : ngrams { -1 }
cyk_rule AAPm_nom_f { AVm_nom_f }  : ngrams { -1 }

// --- Левое наречие:
// неторопливо работавшая
cyk_rule AAPt_nom_f  { Y AVt_nom_f }  : links { AVt_nom_f.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_nom_f) }
cyk_rule AAPit_nom_f { Y AVit_nom_f } : links { AVit_nom_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_nom_f) }
cyk_rule AAPm_nom_f  { Y AVm_nom_f }  : links { AVm_nom_f.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_nom_f) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавшая неторопливо
cyk_rule AAPt_nom_f { AVt_nom_f Y } : links { AVt_nom_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_nom_f) }
cyk_rule AAPit_nom_f { AVit_nom_f Y } : links { AVit_nom_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_nom_f) }


// Обещающая нам дождь
cyk_rule AAPt_nom_f { v=AAPt_nom_f OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающая
cyk_rule AAPt_nom_f { OBJ v=AAPt_nom_f } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающая на заводе
cyk_rule AAPt_nom_f { AAPt_nom_f PN } : links { AAPt_nom_f.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_nom_f { AAPit_nom_f PN } : links { AAPit_nom_f.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшая
cyk_rule AAPt_nom_f { PN AAPt_nom_f } : links { AAPt_nom_f.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_nom_f { PN AAPit_nom_f } : links { AAPit_nom_f.<PREPOS_ADJUNCT>PN }

// студентка, начинающая выполнять задание
cyk_rule AAPm_nom_f { AAPm_nom_f IP } : links { AAPm_nom_f.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_nom_f,IP) }

cyk_rule AVP_nom_f { AAPt_nom_f  }
cyk_rule AVP_nom_f { AAPit_nom_f }
cyk_rule AVP_nom_f { AAPm_nom_f  }

cyk_rule AVt_nom_f { z='*' AVt_nom_f } : links { AVt_nom_f.z } : ngrams { -2 }
cyk_rule AVt_nom_f { AVt_nom_f z='*' } : links { AVt_nom_f.z } : ngrams { -2 }
cyk_rule AVit_nom_f { z='*' AVit_nom_f } : links { AVit_nom_f.z } : ngrams { -2 }
cyk_rule AVit_nom_f { AVit_nom_f z='*' } : links { AVit_nom_f.z } : ngrams { -2 }
cyk_rule AVm_nom_f { z='*' AVm_nom_f } : links { AVm_nom_f.z } : ngrams { -2 }
cyk_rule AVm_nom_f { AVm_nom_f z='*' } : links { AVm_nom_f.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_nom_f { AVP_nom_f }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_nom_f1 { AVP_nom_f COMMA } : links { AVP_nom_f.<PUNCTUATION>COMMA }

// Спит кошка, укравшая сметану.
cyk_rule AVPR_nom_f2 { COMMA AVP_nom_f } : links { AVP_nom_f.<PUNCTUATION>COMMA }

// Кошка, укравшая сметану, пошла спать.
cyk_rule AVPR_nom_f2 { COMMA AVPR_nom_f1 } : links { AVPR_nom_f1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_nom_f { AVPR_nom_f2 }
cyk_rule AVPR_nom_f { AVP_nom_f } : ngrams { -1 }

// Обожающая сметану кошка
cyk_rule NP_nom_f { AVP_nom_f NP_nom_f } : links { NP_nom_f.<ADJ_PARTICIPLE>AVP_nom_f }

// Кошка, обожающая сметану
cyk_rule NP_nom_f { NP_nom_f AVPR_nom_f } : links { NP_nom_f.<ADJ_PARTICIPLE>AVPR_nom_f}

//cyk_rule S { AVP_nom_f } : ngrams { -4 } AP_nom_f уже приводится к S






// -------------------------------------
// --- именительный падеж, муж.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_nom_m { AVt_nom_m }  : ngrams { -1 }
cyk_rule AAPit_nom_m { AVit_nom_m } : ngrams { -1 }
cyk_rule AAPm_nom_m { AVm_nom_m }  : ngrams { -1 }

// --- Левое наречие:
// Много работающий
cyk_rule AAPt_nom_m  { Y AVt_nom_m }  : links { AVt_nom_m.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_nom_m) }
cyk_rule AAPit_nom_m { Y AVit_nom_m } : links { AVit_nom_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_nom_m) }
cyk_rule AAPm_nom_m  { Y AVm_nom_m }  : links { AVm_nom_m.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_nom_m) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавший неторопливо
cyk_rule AAPt_nom_m { AVt_nom_m Y } : links { AVt_nom_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_nom_m) }
cyk_rule AAPit_nom_m { AVit_nom_m Y } : links { AVit_nom_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_nom_m) }


// Обещающий нам дождь
cyk_rule AAPt_nom_m { v=AAPt_nom_m OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающий
cyk_rule AAPt_nom_m { OBJ v=AAPt_nom_m } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающий на заводе
cyk_rule AAPt_nom_m { AAPt_nom_m PN } : links { AAPt_nom_m.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_nom_m { AAPit_nom_m PN } : links { AAPit_nom_m.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавший
cyk_rule AAPt_nom_m { PN AAPt_nom_m } : links { AAPt_nom_m.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_nom_m { PN AAPit_nom_m } : links { AAPit_nom_m.<PREPOS_ADJUNCT>PN }

// студент, начинающий выполнять задание
cyk_rule AAPm_nom_m { AAPm_nom_m IP } : links { AAPm_nom_m.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_nom_m,IP) }

cyk_rule AVP_nom_m { AAPt_nom_m  }
cyk_rule AVP_nom_m { AAPit_nom_m }
cyk_rule AVP_nom_m { AAPm_nom_m  }

cyk_rule AVt_nom_m { z='*' AVt_nom_m } : links { AVt_nom_m.z } : ngrams { -2 }
cyk_rule AVt_nom_m { AVt_nom_m z='*' } : links { AVt_nom_m.z } : ngrams { -2 }
cyk_rule AVit_nom_m { z='*' AVit_nom_m } : links { AVit_nom_m.z } : ngrams { -2 }
cyk_rule AVit_nom_m { AVit_nom_m z='*' } : links { AVit_nom_m.z } : ngrams { -2 }
cyk_rule AVm_nom_m { z='*' AVm_nom_m } : links { AVm_nom_m.z } : ngrams { -2 }
cyk_rule AVm_nom_m { AVm_nom_m z='*' } : links { AVm_nom_m.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_nom_m { AVP_nom_m }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_nom_m1 { AVP_nom_m COMMA } : links { AVP_nom_m.<PUNCTUATION>COMMA }

// Спит кот, укравший сметану.
cyk_rule AVPR_nom_m2 { COMMA AVP_nom_m } : links { AVP_nom_m.<PUNCTUATION>COMMA }

// Кот, укравший сметану, пошел спать.
cyk_rule AVPR_nom_m2 { COMMA AVPR_nom_m1 } : links { AVPR_nom_m1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_nom_m { AVPR_nom_m2 }
cyk_rule AVPR_nom_m { AVP_nom_m } : ngrams { -1 }

// Обожающий сметану кот
cyk_rule NP_nom_m { AVP_nom_m NP_nom_m } : links { NP_nom_m.<ADJ_PARTICIPLE>AVP_nom_m }

// Кот, обожающий сметану
cyk_rule NP_nom_m { NP_nom_m AVPR_nom_m } : links { NP_nom_m.<ADJ_PARTICIPLE>AVPR_nom_m}


// -------------------------------------
// --- именительный падеж, ср.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_nom_n { AVt_nom_n }  : ngrams { -2 }
cyk_rule AAPit_nom_n { AVit_nom_n } : ngrams { -2 }
cyk_rule AAPm_nom_n { AVm_nom_n }  : ngrams { -2 }

// --- Левое наречие:
// неторопливо работавшее
cyk_rule AAPt_nom_n  { Y AVt_nom_n }  : links { AVt_nom_n.<ATTRIBUTE>Y }  : ngrams { -1 ngram2(Y,AVt_nom_n) }
cyk_rule AAPit_nom_n { Y AVit_nom_n } : links { AVit_nom_n.<ATTRIBUTE>Y } : ngrams { -1 ngram2(Y,AVit_nom_n) }
cyk_rule AAPm_nom_n  { Y AVm_nom_n }  : links { AVm_nom_n.<ATTRIBUTE>Y }  : ngrams { -1 ngram2(Y,AVm_nom_n) }

// --- Правое наречие - используется реже, чем левое
// работавшее неторопливо
cyk_rule AAPt_nom_n { AVt_nom_n Y } : links { AVt_nom_n.<ATTRIBUTE>Y } : ngrams { -1 ngram2(Y,AVt_nom_n) }
cyk_rule AAPit_nom_n { AVit_nom_n Y } : links { AVit_nom_n.<ATTRIBUTE>Y } : ngrams { -1 ngram2(Y,AVit_nom_n) }


// Обещающее нам дождь
cyk_rule AAPt_nom_n { v=AAPt_nom_n OBJ } : links { v.<OBJECT>OBJ } : ngrams { 2 ngram2(v,obj) }

// Дождь нам обещающее
cyk_rule AAPt_nom_n { OBJ v=AAPt_nom_n } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающее на заводе
cyk_rule AAPt_nom_n { AAPt_nom_n PN } : links { AAPt_nom_n.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_nom_n { AAPit_nom_n PN } : links { AAPit_nom_n.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшее
cyk_rule AAPt_nom_n { PN AAPt_nom_n } : links { AAPt_nom_n.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_nom_n { PN AAPit_nom_n } : links { AAPit_nom_n.<PREPOS_ADJUNCT>PN }

// чадо, начинающее выполнять задание
cyk_rule AAPm_nom_n { AAPm_nom_n IP } : links { AAPm_nom_n.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_nom_n,IP) }

cyk_rule AVP_nom_n { AAPt_nom_n  }
cyk_rule AVP_nom_n { AAPit_nom_n }
cyk_rule AVP_nom_n { AAPm_nom_n  }

cyk_rule AVt_nom_n { z='*' AVt_nom_n } : links { AVt_nom_n.z } : ngrams { -2 }
cyk_rule AVt_nom_n { AVt_nom_n z='*' } : links { AVt_nom_n.z } : ngrams { -2 }
cyk_rule AVit_nom_n { z='*' AVit_nom_n } : links { AVit_nom_n.z } : ngrams { -2 }
cyk_rule AVit_nom_n { AVit_nom_n z='*' } : links { AVit_nom_n.z } : ngrams { -2 }
cyk_rule AVm_nom_n { z='*' AVm_nom_n } : links { AVm_nom_n.z } : ngrams { -2 }
cyk_rule AVm_nom_n { AVm_nom_n z='*' } : links { AVm_nom_n.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_nom_n { AVP_nom_n }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_nom_n1 { AVP_nom_n COMMA } : links { AVP_nom_n.<PUNCTUATION>COMMA }

// Спит животное, укравшее сметану.
cyk_rule AVPR_nom_n2 { COMMA AVP_nom_n } : links { AVP_nom_n.<PUNCTUATION>COMMA }

// Животное, укравшее сметану, пошло спать.
cyk_rule AVPR_nom_n2 { COMMA AVPR_nom_n1 } : links { AVPR_nom_n1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_nom_n { AVPR_nom_n2 }
cyk_rule AVPR_nom_n { AVP_nom_n } : ngrams { -1 }

// Обожающее сметану животное
cyk_rule NP_nom_n { AVP_nom_n NP_nom_n } : links { NP_nom_n.<ADJ_PARTICIPLE>AVP_nom_n }

// Животное, обожающее сметану
cyk_rule NP_nom_n { NP_nom_n AVPR_nom_n } : links { NP_nom_n.<ADJ_PARTICIPLE>AVPR_nom_n}

//cyk_rule S { AVP_nom_n } : ngrams { -4 } AP_nom_n уже приводится к S






// -------------------------------------
// --- именительный падеж, мн.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_nom_pl { AVt_nom_pl }  : ngrams { -1 }
cyk_rule AAPit_nom_pl { AVit_nom_pl } : ngrams { -1 }
cyk_rule AAPm_nom_pl { AVm_nom_pl }  : ngrams { -1 }

// --- Левое наречие:
// неторопливо работавшие
cyk_rule AAPt_nom_pl  { Y AVt_nom_pl }  : links { AVt_nom_pl.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_nom_pl) }
cyk_rule AAPit_nom_pl { Y AVit_nom_pl } : links { AVit_nom_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_nom_pl) }
cyk_rule AAPm_nom_pl  { Y AVm_nom_pl }  : links { AVm_nom_pl.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_nom_pl) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавшие неторопливо
cyk_rule AAPt_nom_pl { AVt_nom_pl Y } : links { AVt_nom_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_nom_pl) }
cyk_rule AAPit_nom_pl { AVit_nom_pl Y } : links { AVit_nom_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_nom_pl) }


// Обещающие нам дождь
cyk_rule AAPt_nom_pl { v=AAPt_nom_pl OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающие
cyk_rule AAPt_nom_pl { OBJ v=AAPt_nom_pl } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающие на заводе
cyk_rule AAPt_nom_pl { AAPt_nom_pl PN } : links { AAPt_nom_pl.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_nom_pl { AAPit_nom_pl PN } : links { AAPit_nom_pl.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшие
cyk_rule AAPt_nom_pl { PN AAPt_nom_pl } : links { AAPt_nom_pl.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_nom_pl { PN AAPit_nom_pl } : links { AAPit_nom_pl.<PREPOS_ADJUNCT>PN }

// студентки, начинающие выполнять задание
cyk_rule AAPm_nom_pl { AAPm_nom_pl IP } : links { AAPm_nom_pl.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_nom_pl,IP) }

cyk_rule AVP_nom_pl { AAPt_nom_pl  }
cyk_rule AVP_nom_pl { AAPit_nom_pl }
cyk_rule AVP_nom_pl { AAPm_nom_pl  }

cyk_rule AVt_nom_pl { z='*' AVt_nom_pl } : links { AVt_nom_pl.z } : ngrams { -2 }
cyk_rule AVt_nom_pl { AVt_nom_pl z='*' } : links { AVt_nom_pl.z } : ngrams { -2 }
cyk_rule AVit_nom_pl { z='*' AVit_nom_pl } : links { AVit_nom_pl.z } : ngrams { -2 }
cyk_rule AVit_nom_pl { AVit_nom_pl z='*' } : links { AVit_nom_pl.z } : ngrams { -2 }
cyk_rule AVm_nom_pl { z='*' AVm_nom_pl } : links { AVm_nom_pl.z } : ngrams { -2 }
cyk_rule AVm_nom_pl { AVm_nom_pl z='*' } : links { AVm_nom_pl.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_nom_pl { AVP_nom_pl }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_nom_pl1 { AVP_nom_pl COMMA } : links { AVP_nom_pl.<PUNCTUATION>COMMA }

// Спят кошки, укравшие сметану.
cyk_rule AVPR_nom_pl2 { COMMA AVP_nom_pl } : links { AVP_nom_pl.<PUNCTUATION>COMMA }

// Кошки, укравшие сметану, пошли спать.
cyk_rule AVPR_nom_pl2 { COMMA AVPR_nom_pl1 } : links { AVPR_nom_pl1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_nom_pl { AVPR_nom_pl2 }
cyk_rule AVPR_nom_pl { AVP_nom_pl } : ngrams { -1 }

// Обожающие сметану кошки
cyk_rule NP_nom_pl { AVP_nom_pl NP_nom_pl } : links { NP_nom_pl.<ADJ_PARTICIPLE>AVP_nom_pl }

// Кошки, обожающие сметану
cyk_rule NP_nom_pl { NP_nom_pl AVPR_nom_pl } : links { NP_nom_pl.<ADJ_PARTICIPLE>AVPR_nom_pl}

//cyk_rule S { AVP_nom_pl } : ngrams { -4 } AP_nom_pl уже приводится к S





// -------------------------------------
// --- родительный падеж, жен.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_gen_f { AVt_gen_f }  : ngrams { -1 }
cyk_rule AAPit_gen_f { AVit_gen_f } : ngrams { -1 }
cyk_rule AAPm_gen_f { AVm_gen_f }  : ngrams { -1 }

// --- Левое наречие:
// неторопливо работавшей
cyk_rule AAPt_gen_f  { Y AVt_gen_f }  : links { AVt_gen_f.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_gen_f) }
cyk_rule AAPit_gen_f { Y AVit_gen_f } : links { AVit_gen_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_gen_f) }
cyk_rule AAPm_gen_f  { Y AVm_gen_f }  : links { AVm_gen_f.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_gen_f) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавшей неторопливо
cyk_rule AAPt_gen_f { AVt_gen_f Y } : links { AVt_gen_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_gen_f) }
cyk_rule AAPit_gen_f { AVit_gen_f Y } : links { AVit_gen_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_gen_f) }


// Обещающая нам дождь
cyk_rule AAPt_gen_f { v=AAPt_gen_f OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающая
cyk_rule AAPt_gen_f { OBJ v=AAPt_gen_f } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающая на заводе
cyk_rule AAPt_gen_f { AAPt_gen_f PN } : links { AAPt_gen_f.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_gen_f { AAPit_gen_f PN } : links { AAPit_gen_f.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшая
cyk_rule AAPt_gen_f { PN AAPt_gen_f } : links { AAPt_gen_f.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_gen_f { PN AAPit_gen_f } : links { AAPit_gen_f.<PREPOS_ADJUNCT>PN }

// студентка, начинающая выполнять задание
cyk_rule AAPm_gen_f { AAPm_gen_f IP } : links { AAPm_gen_f.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_gen_f,IP) }

cyk_rule AVP_gen_f { AAPt_gen_f  }
cyk_rule AVP_gen_f { AAPit_gen_f }
cyk_rule AVP_gen_f { AAPm_gen_f  }

cyk_rule AVt_gen_f { z='*' AVt_gen_f } : links { AVt_gen_f.z } : ngrams { -2 }
cyk_rule AVt_gen_f { AVt_gen_f z='*' } : links { AVt_gen_f.z } : ngrams { -2 }
cyk_rule AVit_gen_f { z='*' AVit_gen_f } : links { AVit_gen_f.z } : ngrams { -2 }
cyk_rule AVit_gen_f { AVit_gen_f z='*' } : links { AVit_gen_f.z } : ngrams { -2 }
cyk_rule AVm_gen_f { z='*' AVm_gen_f } : links { AVm_gen_f.z } : ngrams { -2 }
cyk_rule AVm_gen_f { AVm_gen_f z='*' } : links { AVm_gen_f.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_gen_f { AVP_gen_f }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_gen_f1 { AVP_gen_f COMMA } : links { AVP_gen_f.<PUNCTUATION>COMMA }

// Спит кошка, укравшая сметану.
cyk_rule AVPR_gen_f2 { COMMA AVP_gen_f } : links { AVP_gen_f.<PUNCTUATION>COMMA }

// Кошка, укравшая сметану, пошла спать.
cyk_rule AVPR_gen_f2 { COMMA AVPR_gen_f1 } : links { AVPR_gen_f1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_gen_f { AVPR_gen_f2 }
cyk_rule AVPR_gen_f { AVP_gen_f } : ngrams { -1 }

// Обожающая сметану кошка
cyk_rule NP_gen_f { AVP_gen_f NP_gen_f } : links { NP_gen_f.<ADJ_PARTICIPLE>AVP_gen_f }

// Кошка, обожающая сметану
cyk_rule NP_gen_f { NP_gen_f AVPR_gen_f } : links { NP_gen_f.<ADJ_PARTICIPLE>AVPR_gen_f}

//cyk_rule S { AVP_gen_f } : ngrams { -4 } AP_gen_f уже приводится к S






// -------------------------------------
// --- родительный падеж, муж.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_gen_m { AVt_gen_m }  : ngrams { -1 }
cyk_rule AAPit_gen_m { AVit_gen_m } : ngrams { -1 }
cyk_rule AAPm_gen_m { AVm_gen_m }  : ngrams { -1 }

// --- Левое наречие:
// Много работающий
cyk_rule AAPt_gen_m  { Y AVt_gen_m }  : links { AVt_gen_m.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_gen_m) }
cyk_rule AAPit_gen_m { Y AVit_gen_m } : links { AVit_gen_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_gen_m) }
cyk_rule AAPm_gen_m  { Y AVm_gen_m }  : links { AVm_gen_m.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_gen_m) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавший неторопливо
cyk_rule AAPt_gen_m { AVt_gen_m Y } : links { AVt_gen_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_gen_m) }
cyk_rule AAPit_gen_m { AVit_gen_m Y } : links { AVit_gen_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_gen_m) }


// Обещающий нам дождь
cyk_rule AAPt_gen_m { v=AAPt_gen_m OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающий
cyk_rule AAPt_gen_m { OBJ v=AAPt_gen_m } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающий на заводе
cyk_rule AAPt_gen_m { AAPt_gen_m PN } : links { AAPt_gen_m.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_gen_m { AAPit_gen_m PN } : links { AAPit_gen_m.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавший
cyk_rule AAPt_gen_m { PN AAPt_gen_m } : links { AAPt_gen_m.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_gen_m { PN AAPit_gen_m } : links { AAPit_gen_m.<PREPOS_ADJUNCT>PN }

// студент, начинающий выполнять задание
cyk_rule AAPm_gen_m { AAPm_gen_m IP } : links { AAPm_gen_m.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_gen_m,IP) }

cyk_rule AVP_gen_m { AAPt_gen_m  }
cyk_rule AVP_gen_m { AAPit_gen_m }
cyk_rule AVP_gen_m { AAPm_gen_m  }

cyk_rule AVt_gen_m { z='*' AVt_gen_m } : links { AVt_gen_m.z } : ngrams { -2 }
cyk_rule AVt_gen_m { AVt_gen_m z='*' } : links { AVt_gen_m.z } : ngrams { -2 }
cyk_rule AVit_gen_m { z='*' AVit_gen_m } : links { AVit_gen_m.z } : ngrams { -2 }
cyk_rule AVit_gen_m { AVit_gen_m z='*' } : links { AVit_gen_m.z } : ngrams { -2 }
cyk_rule AVm_gen_m { z='*' AVm_gen_m } : links { AVm_gen_m.z } : ngrams { -2 }
cyk_rule AVm_gen_m { AVm_gen_m z='*' } : links { AVm_gen_m.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_gen_m { AVP_gen_m }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_gen_m1 { AVP_gen_m COMMA } : links { AVP_gen_m.<PUNCTUATION>COMMA }

// Спит кот, укравший сметану.
cyk_rule AVPR_gen_m2 { COMMA AVP_gen_m } : links { AVP_gen_m.<PUNCTUATION>COMMA }

// Кот, укравший сметану, пошел спать.
cyk_rule AVPR_gen_m2 { COMMA AVPR_gen_m1 } : links { AVPR_gen_m1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_gen_m { AVPR_gen_m2 }
cyk_rule AVPR_gen_m { AVP_gen_m } : ngrams { -1 }

// Обожающий сметану кот
cyk_rule NP_gen_m { AVP_gen_m NP_gen_m } : links { NP_gen_m.<ADJ_PARTICIPLE>AVP_gen_m }

// Кот, обожающий сметану
cyk_rule NP_gen_m { NP_gen_m AVPR_gen_m } : links { NP_gen_m.<ADJ_PARTICIPLE>AVPR_gen_m}


// -------------------------------------
// --- родительный падеж, ср.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_gen_n { AVt_gen_n }  : ngrams { -1 }
cyk_rule AAPit_gen_n { AVit_gen_n } : ngrams { -1 }
cyk_rule AAPm_gen_n { AVm_gen_n }  : ngrams { -1 }

// --- Левое наречие:
// неторопливо работавше
cyk_rule AAPt_gen_n  { Y AVt_gen_n }  : links { AVt_gen_n.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_gen_n) }
cyk_rule AAPit_gen_n { Y AVit_gen_n } : links { AVit_gen_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_gen_n) }
cyk_rule AAPm_gen_n  { Y AVm_gen_n }  : links { AVm_gen_n.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_gen_n) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавшее неторопливо
cyk_rule AAPt_gen_n { AVt_gen_n Y } : links { AVt_gen_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_gen_n) }
cyk_rule AAPit_gen_n { AVit_gen_n Y } : links { AVit_gen_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_gen_n) }


// Обещающее нам дождь
cyk_rule AAPt_gen_n { v=AAPt_gen_n OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающее
cyk_rule AAPt_gen_n { OBJ v=AAPt_gen_n } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающее на заводе
cyk_rule AAPt_gen_n { AAPt_gen_n PN } : links { AAPt_gen_n.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_gen_n { AAPit_gen_n PN } : links { AAPit_gen_n.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшее
cyk_rule AAPt_gen_n { PN AAPt_gen_n } : links { AAPt_gen_n.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_gen_n { PN AAPit_gen_n } : links { AAPit_gen_n.<PREPOS_ADJUNCT>PN }

// чадо, начинающее выполнять задание
cyk_rule AAPm_gen_n { AAPm_gen_n IP } : links { AAPm_gen_n.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_gen_n,IP) }

cyk_rule AVP_gen_n { AAPt_gen_n  }
cyk_rule AVP_gen_n { AAPit_gen_n }
cyk_rule AVP_gen_n { AAPm_gen_n  }

cyk_rule AVt_gen_n { z='*' AVt_gen_n } : links { AVt_gen_n.z } : ngrams { -2 }
cyk_rule AVt_gen_n { AVt_gen_n z='*' } : links { AVt_gen_n.z } : ngrams { -2 }
cyk_rule AVit_gen_n { z='*' AVit_gen_n } : links { AVit_gen_n.z } : ngrams { -2 }
cyk_rule AVit_gen_n { AVit_gen_n z='*' } : links { AVit_gen_n.z } : ngrams { -2 }
cyk_rule AVm_gen_n { z='*' AVm_gen_n } : links { AVm_gen_n.z } : ngrams { -2 }
cyk_rule AVm_gen_n { AVm_gen_n z='*' } : links { AVm_gen_n.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_gen_n { AVP_gen_n }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_gen_n1 { AVP_gen_n COMMA } : links { AVP_gen_n.<PUNCTUATION>COMMA }

// Спит животное, укравшее сметану.
cyk_rule AVPR_gen_n2 { COMMA AVP_gen_n } : links { AVP_gen_n.<PUNCTUATION>COMMA }

// Животное, укравшее сметану, пошло спать.
cyk_rule AVPR_gen_n2 { COMMA AVPR_gen_n1 } : links { AVPR_gen_n1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_gen_n { AVPR_gen_n2 }
cyk_rule AVPR_gen_n { AVP_gen_n } : ngrams { -1 }

// Обожающее сметану животное
cyk_rule NP_gen_n { AVP_gen_n NP_gen_n } : links { NP_gen_n.<ADJ_PARTICIPLE>AVP_gen_n }

// Животное, обожающее сметану
cyk_rule NP_gen_n { NP_gen_n AVPR_gen_n } : links { NP_gen_n.<ADJ_PARTICIPLE>AVPR_gen_n}

//cyk_rule S { AVP_gen_n } : ngrams { -4 } AP_gen_n уже приводится к S






// -------------------------------------
// --- родительный падеж, мн.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_gen_pl { AVt_gen_pl }  : ngrams { -1 }
cyk_rule AAPit_gen_pl { AVit_gen_pl } : ngrams { -1 }
cyk_rule AAPm_gen_pl { AVm_gen_pl }  : ngrams { -1 }

// --- Левое наречие:
// неторопливо работавшие
cyk_rule AAPt_gen_pl  { Y AVt_gen_pl }  : links { AVt_gen_pl.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_gen_pl) }
cyk_rule AAPit_gen_pl { Y AVit_gen_pl } : links { AVit_gen_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_gen_pl) }
cyk_rule AAPm_gen_pl  { Y AVm_gen_pl }  : links { AVm_gen_pl.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_gen_pl) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавшие неторопливо
cyk_rule AAPt_gen_pl { AVt_gen_pl Y } : links { AVt_gen_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_gen_pl) }
cyk_rule AAPit_gen_pl { AVit_gen_pl Y } : links { AVit_gen_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_gen_pl) }


// Обещающие нам дождь
cyk_rule AAPt_gen_pl { v=AAPt_gen_pl OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающие
cyk_rule AAPt_gen_pl { OBJ v=AAPt_gen_pl } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающие на заводе
cyk_rule AAPt_gen_pl { AAPt_gen_pl PN } : links { AAPt_gen_pl.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_gen_pl { AAPit_gen_pl PN } : links { AAPit_gen_pl.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшие
cyk_rule AAPt_gen_pl { PN AAPt_gen_pl } : links { AAPt_gen_pl.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_gen_pl { PN AAPit_gen_pl } : links { AAPit_gen_pl.<PREPOS_ADJUNCT>PN }

// студентки, начинающие выполнять задание
cyk_rule AAPm_gen_pl { AAPm_gen_pl IP } : links { AAPm_gen_pl.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_gen_pl,IP) }

cyk_rule AVP_gen_pl { AAPt_gen_pl  }
cyk_rule AVP_gen_pl { AAPit_gen_pl }
cyk_rule AVP_gen_pl { AAPm_gen_pl  }

cyk_rule AVt_gen_pl { z='*' AVt_gen_pl } : links { AVt_gen_pl.z } : ngrams { -2 }
cyk_rule AVt_gen_pl { AVt_gen_pl z='*' } : links { AVt_gen_pl.z } : ngrams { -2 }
cyk_rule AVit_gen_pl { z='*' AVit_gen_pl } : links { AVit_gen_pl.z } : ngrams { -2 }
cyk_rule AVit_gen_pl { AVit_gen_pl z='*' } : links { AVit_gen_pl.z } : ngrams { -2 }
cyk_rule AVm_gen_pl { z='*' AVm_gen_pl } : links { AVm_gen_pl.z } : ngrams { -2 }
cyk_rule AVm_gen_pl { AVm_gen_pl z='*' } : links { AVm_gen_pl.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_gen_pl { AVP_gen_pl }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_gen_pl1 { AVP_gen_pl COMMA } : links { AVP_gen_pl.<PUNCTUATION>COMMA }

// Спят кошки, укравшие сметану.
cyk_rule AVPR_gen_pl2 { COMMA AVP_gen_pl } : links { AVP_gen_pl.<PUNCTUATION>COMMA }

// Кошки, укравшие сметану, пошли спать.
cyk_rule AVPR_gen_pl2 { COMMA AVPR_gen_pl1 } : links { AVPR_gen_pl1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_gen_pl { AVPR_gen_pl2 }
cyk_rule AVPR_gen_pl { AVP_gen_pl } : ngrams { -1 }

// Обожающие сметану кошки
cyk_rule NP_gen_pl { AVP_gen_pl NP_gen_pl } : links { NP_gen_pl.<ADJ_PARTICIPLE>AVP_gen_pl }

// Кошки, обожающие сметану
cyk_rule NP_gen_pl { NP_gen_pl AVPR_gen_pl } : links { NP_gen_pl.<ADJ_PARTICIPLE>AVPR_gen_pl}

//cyk_rule S { AVP_gen_pl } : ngrams { -4 } AP_gen_pl уже приводится к S













// -------------------------------------
// --- творительный падеж, жен.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_ins_f { AVt_ins_f }  : ngrams { -1 }
cyk_rule AAPit_ins_f { AVit_ins_f } : ngrams { -1 }
cyk_rule AAPm_ins_f { AVm_ins_f }  : ngrams { -1 }

// --- Левое наречие:
// неторопливо работавшая
cyk_rule AAPt_ins_f  { Y AVt_ins_f }  : links { AVt_ins_f.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_ins_f) }
cyk_rule AAPit_ins_f { Y AVit_ins_f } : links { AVit_ins_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_ins_f) }
cyk_rule AAPm_ins_f  { Y AVm_ins_f }  : links { AVm_ins_f.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_ins_f) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавшая неторопливо
cyk_rule AAPt_ins_f { AVt_ins_f Y } : links { AVt_ins_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_ins_f) }
cyk_rule AAPit_ins_f { AVit_ins_f Y } : links { AVit_ins_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_ins_f) }


// Обещающая нам дождь
cyk_rule AAPt_ins_f { v=AAPt_ins_f OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающая
cyk_rule AAPt_ins_f { OBJ v=AAPt_ins_f } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающая на заводе
cyk_rule AAPt_ins_f { AAPt_ins_f PN } : links { AAPt_ins_f.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_ins_f { AAPit_ins_f PN } : links { AAPit_ins_f.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшая
cyk_rule AAPt_ins_f { PN AAPt_ins_f } : links { AAPt_ins_f.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_ins_f { PN AAPit_ins_f } : links { AAPit_ins_f.<PREPOS_ADJUNCT>PN }

// студентка, начинающая выполнять задание
cyk_rule AAPm_ins_f { AAPm_ins_f IP } : links { AAPm_ins_f.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_ins_f,IP) }

cyk_rule AVP_ins_f { AAPt_ins_f  }
cyk_rule AVP_ins_f { AAPit_ins_f }
cyk_rule AVP_ins_f { AAPm_ins_f  }

cyk_rule AVt_ins_f { z='*' AVt_ins_f } : links { AVt_ins_f.z } : ngrams { -2 }
cyk_rule AVt_ins_f { AVt_ins_f z='*' } : links { AVt_ins_f.z } : ngrams { -2 }
cyk_rule AVit_ins_f { z='*' AVit_ins_f } : links { AVit_ins_f.z } : ngrams { -2 }
cyk_rule AVit_ins_f { AVit_ins_f z='*' } : links { AVit_ins_f.z } : ngrams { -2 }
cyk_rule AVm_ins_f { z='*' AVm_ins_f } : links { AVm_ins_f.z } : ngrams { -2 }
cyk_rule AVm_ins_f { AVm_ins_f z='*' } : links { AVm_ins_f.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_ins_f { AVP_ins_f }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_ins_f1 { AVP_ins_f COMMA } : links { AVP_ins_f.<PUNCTUATION>COMMA }

// Спит кошка, укравшая сметану.
cyk_rule AVPR_ins_f2 { COMMA AVP_ins_f } : links { AVP_ins_f.<PUNCTUATION>COMMA }

// Кошка, укравшая сметану, пошла спать.
cyk_rule AVPR_ins_f2 { COMMA AVPR_ins_f1 } : links { AVPR_ins_f1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_ins_f { AVPR_ins_f2 }
cyk_rule AVPR_ins_f { AVP_ins_f } : ngrams { -1 }

// Обожающая сметану кошка
cyk_rule NP_ins_f { AVP_ins_f NP_ins_f } : links { NP_ins_f.<ADJ_PARTICIPLE>AVP_ins_f }

// Кошка, обожающая сметану
cyk_rule NP_ins_f { NP_ins_f AVPR_ins_f } : links { NP_ins_f.<ADJ_PARTICIPLE>AVPR_ins_f}

//cyk_rule S { AVP_ins_f } : ngrams { -4 } AP_ins_f уже приводится к S






// -------------------------------------
// --- творительный падеж, муж.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_ins_m { AVt_ins_m }  : ngrams { -1 }
cyk_rule AAPit_ins_m { AVit_ins_m } : ngrams { -1 }
cyk_rule AAPm_ins_m { AVm_ins_m }  : ngrams { -1 }

// --- Левое наречие:
// Много работающий
cyk_rule AAPt_ins_m  { Y AVt_ins_m }  : links { AVt_ins_m.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_ins_m) }
cyk_rule AAPit_ins_m { Y AVit_ins_m } : links { AVit_ins_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_ins_m) }
cyk_rule AAPm_ins_m  { Y AVm_ins_m }  : links { AVm_ins_m.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_ins_m) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавший неторопливо
cyk_rule AAPt_ins_m { AVt_ins_m Y } : links { AVt_ins_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_ins_m) }
cyk_rule AAPit_ins_m { AVit_ins_m Y } : links { AVit_ins_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_ins_m) }


// Обещающий нам дождь
cyk_rule AAPt_ins_m { v=AAPt_ins_m OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающий
cyk_rule AAPt_ins_m { OBJ v=AAPt_ins_m } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающий на заводе
cyk_rule AAPt_ins_m { AAPt_ins_m PN } : links { AAPt_ins_m.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_ins_m { AAPit_ins_m PN } : links { AAPit_ins_m.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавший
cyk_rule AAPt_ins_m { PN AAPt_ins_m } : links { AAPt_ins_m.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_ins_m { PN AAPit_ins_m } : links { AAPit_ins_m.<PREPOS_ADJUNCT>PN }

// студент, начинающий выполнять задание
cyk_rule AAPm_ins_m { AAPm_ins_m IP } : links { AAPm_ins_m.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_ins_m,IP) }

cyk_rule AVP_ins_m { AAPt_ins_m  }
cyk_rule AVP_ins_m { AAPit_ins_m }
cyk_rule AVP_ins_m { AAPm_ins_m  }

cyk_rule AVt_ins_m { z='*' AVt_ins_m } : links { AVt_ins_m.z } : ngrams { -2 }
cyk_rule AVt_ins_m { AVt_ins_m z='*' } : links { AVt_ins_m.z } : ngrams { -2 }
cyk_rule AVit_ins_m { z='*' AVit_ins_m } : links { AVit_ins_m.z } : ngrams { -2 }
cyk_rule AVit_ins_m { AVit_ins_m z='*' } : links { AVit_ins_m.z } : ngrams { -2 }
cyk_rule AVm_ins_m { z='*' AVm_ins_m } : links { AVm_ins_m.z } : ngrams { -2 }
cyk_rule AVm_ins_m { AVm_ins_m z='*' } : links { AVm_ins_m.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_ins_m { AVP_ins_m }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_ins_m1 { AVP_ins_m COMMA } : links { AVP_ins_m.<PUNCTUATION>COMMA }

// Спит кот, укравший сметану.
cyk_rule AVPR_ins_m2 { COMMA AVP_ins_m } : links { AVP_ins_m.<PUNCTUATION>COMMA }

// Кот, укравший сметану, пошел спать.
cyk_rule AVPR_ins_m2 { COMMA AVPR_ins_m1 } : links { AVPR_ins_m1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_ins_m { AVPR_ins_m2 }
cyk_rule AVPR_ins_m { AVP_ins_m } : ngrams { -1 }

// Обожающий сметану кот
cyk_rule NP_ins_m { AVP_ins_m NP_ins_m } : links { NP_ins_m.<ADJ_PARTICIPLE>AVP_ins_m }

// Кот, обожающий сметану
cyk_rule NP_ins_m { NP_ins_m AVPR_ins_m } : links { NP_ins_m.<ADJ_PARTICIPLE>AVPR_ins_m}


// -------------------------------------
// --- творительный падеж, ср.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_ins_n { AVt_ins_n }  : ngrams { -1 }
cyk_rule AAPit_ins_n { AVit_ins_n } : ngrams { -1 }
cyk_rule AAPm_ins_n { AVm_ins_n }  : ngrams { -1 }

// --- Левое наречие:
// неторопливо работавше
cyk_rule AAPt_ins_n  { Y AVt_ins_n }  : links { AVt_ins_n.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_ins_n) }
cyk_rule AAPit_ins_n { Y AVit_ins_n } : links { AVit_ins_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_ins_n) }
cyk_rule AAPm_ins_n  { Y AVm_ins_n }  : links { AVm_ins_n.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_ins_n) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавшее неторопливо
cyk_rule AAPt_ins_n { AVt_ins_n Y } : links { AVt_ins_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_ins_n) }
cyk_rule AAPit_ins_n { AVit_ins_n Y } : links { AVit_ins_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_ins_n) }


// Обещающее нам дождь
cyk_rule AAPt_ins_n { v=AAPt_ins_n OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающее
cyk_rule AAPt_ins_n { OBJ v=AAPt_ins_n } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающее на заводе
cyk_rule AAPt_ins_n { AAPt_ins_n PN } : links { AAPt_ins_n.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_ins_n { AAPit_ins_n PN } : links { AAPit_ins_n.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшее
cyk_rule AAPt_ins_n { PN AAPt_ins_n } : links { AAPt_ins_n.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_ins_n { PN AAPit_ins_n } : links { AAPit_ins_n.<PREPOS_ADJUNCT>PN }

// чадо, начинающее выполнять задание
cyk_rule AAPm_ins_n { AAPm_ins_n IP } : links { AAPm_ins_n.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_ins_n,IP) }

cyk_rule AVP_ins_n { AAPt_ins_n  }
cyk_rule AVP_ins_n { AAPit_ins_n }
cyk_rule AVP_ins_n { AAPm_ins_n  }

cyk_rule AVt_ins_n { z='*' AVt_ins_n } : links { AVt_ins_n.z } : ngrams { -2 }
cyk_rule AVt_ins_n { AVt_ins_n z='*' } : links { AVt_ins_n.z } : ngrams { -2 }
cyk_rule AVit_ins_n { z='*' AVit_ins_n } : links { AVit_ins_n.z } : ngrams { -2 }
cyk_rule AVit_ins_n { AVit_ins_n z='*' } : links { AVit_ins_n.z } : ngrams { -2 }
cyk_rule AVm_ins_n { z='*' AVm_ins_n } : links { AVm_ins_n.z } : ngrams { -2 }
cyk_rule AVm_ins_n { AVm_ins_n z='*' } : links { AVm_ins_n.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_ins_n { AVP_ins_n }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_ins_n1 { AVP_ins_n COMMA } : links { AVP_ins_n.<PUNCTUATION>COMMA }

// Спит животное, укравшее сметану.
cyk_rule AVPR_ins_n2 { COMMA AVP_ins_n } : links { AVP_ins_n.<PUNCTUATION>COMMA }

// Животное, укравшее сметану, пошло спать.
cyk_rule AVPR_ins_n2 { COMMA AVPR_ins_n1 } : links { AVPR_ins_n1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_ins_n { AVPR_ins_n2 }
cyk_rule AVPR_ins_n { AVP_ins_n } : ngrams { -1 }

// Обожающее сметану животное
cyk_rule NP_ins_n { AVP_ins_n NP_ins_n } : links { NP_ins_n.<ADJ_PARTICIPLE>AVP_ins_n }

// Животное, обожающее сметану
cyk_rule NP_ins_n { NP_ins_n AVPR_ins_n } : links { NP_ins_n.<ADJ_PARTICIPLE>AVPR_ins_n}

//cyk_rule S { AVP_ins_n } : ngrams { -4 } AP_ins_n уже приводится к S






// -------------------------------------
// --- творительный падеж, мн.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_ins_pl { AVt_ins_pl }  : ngrams { -1 }
cyk_rule AAPit_ins_pl { AVit_ins_pl } : ngrams { -1 }
cyk_rule AAPm_ins_pl { AVm_ins_pl }  : ngrams { -1 }

// --- Левое наречие:
// неторопливо работавшие
cyk_rule AAPt_ins_pl  { Y AVt_ins_pl }  : links { AVt_ins_pl.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_ins_pl) }
cyk_rule AAPit_ins_pl { Y AVit_ins_pl } : links { AVit_ins_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_ins_pl) }
cyk_rule AAPm_ins_pl  { Y AVm_ins_pl }  : links { AVm_ins_pl.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_ins_pl) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавшие неторопливо
cyk_rule AAPt_ins_pl { AVt_ins_pl Y } : links { AVt_ins_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_ins_pl) }
cyk_rule AAPit_ins_pl { AVit_ins_pl Y } : links { AVit_ins_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_ins_pl) }


// Обещающие нам дождь
cyk_rule AAPt_ins_pl { v=AAPt_ins_pl OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающие
cyk_rule AAPt_ins_pl { OBJ v=AAPt_ins_pl } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающие на заводе
cyk_rule AAPt_ins_pl { AAPt_ins_pl PN } : links { AAPt_ins_pl.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_ins_pl { AAPit_ins_pl PN } : links { AAPit_ins_pl.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшие
cyk_rule AAPt_ins_pl { PN AAPt_ins_pl } : links { AAPt_ins_pl.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_ins_pl { PN AAPit_ins_pl } : links { AAPit_ins_pl.<PREPOS_ADJUNCT>PN }

// студентки, начинающие выполнять задание
cyk_rule AAPm_ins_pl { AAPm_ins_pl IP } : links { AAPm_ins_pl.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_ins_pl,IP) }

cyk_rule AVP_ins_pl { AAPt_ins_pl  }
cyk_rule AVP_ins_pl { AAPit_ins_pl }
cyk_rule AVP_ins_pl { AAPm_ins_pl  }

cyk_rule AVt_ins_pl { z='*' AVt_ins_pl } : links { AVt_ins_pl.z } : ngrams { -2 }
cyk_rule AVt_ins_pl { AVt_ins_pl z='*' } : links { AVt_ins_pl.z } : ngrams { -2 }
cyk_rule AVit_ins_pl { z='*' AVit_ins_pl } : links { AVit_ins_pl.z } : ngrams { -2 }
cyk_rule AVit_ins_pl { AVit_ins_pl z='*' } : links { AVit_ins_pl.z } : ngrams { -2 }
cyk_rule AVm_ins_pl { z='*' AVm_ins_pl } : links { AVm_ins_pl.z } : ngrams { -2 }
cyk_rule AVm_ins_pl { AVm_ins_pl z='*' } : links { AVm_ins_pl.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_ins_pl { AVP_ins_pl }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_ins_pl1 { AVP_ins_pl COMMA } : links { AVP_ins_pl.<PUNCTUATION>COMMA }

// Спят кошки, укравшие сметану.
cyk_rule AVPR_ins_pl2 { COMMA AVP_ins_pl } : links { AVP_ins_pl.<PUNCTUATION>COMMA }

// Кошки, укравшие сметану, пошли спать.
cyk_rule AVPR_ins_pl2 { COMMA AVPR_ins_pl1 } : links { AVPR_ins_pl1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_ins_pl { AVPR_ins_pl2 }
cyk_rule AVPR_ins_pl { AVP_ins_pl } : ngrams { -1 }

// Обожающие сметану кошки
cyk_rule NP_ins_pl { AVP_ins_pl NP_ins_pl } : links { NP_ins_pl.<ADJ_PARTICIPLE>AVP_ins_pl }

// Кошки, обожающие сметану
cyk_rule NP_ins_pl { NP_ins_pl AVPR_ins_pl } : links { NP_ins_pl.<ADJ_PARTICIPLE>AVPR_ins_pl}

//cyk_rule S { AVP_ins_pl } : ngrams { -4 } AP_ins_pl уже приводится к S









// -------------------------------------
// --- винительный падеж, жен.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_acc_f { AVt_acc_f }  : ngrams { -1 }
cyk_rule AAPit_acc_f { AVit_acc_f } : ngrams { -1 }
cyk_rule AAPm_acc_f { AVm_acc_f }  : ngrams { -1 }

// --- Левое наречие:
// неторопливо работавшая
cyk_rule AAPt_acc_f  { Y AVt_acc_f }  : links { AVt_acc_f.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_acc_f) }
cyk_rule AAPit_acc_f { Y AVit_acc_f } : links { AVit_acc_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_acc_f) }
cyk_rule AAPm_acc_f  { Y AVm_acc_f }  : links { AVm_acc_f.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_acc_f) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавшая неторопливо
cyk_rule AAPt_acc_f { AVt_acc_f Y } : links { AVt_acc_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_acc_f) }
cyk_rule AAPit_acc_f { AVit_acc_f Y } : links { AVit_acc_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_acc_f) }


// Обещающая нам дождь
cyk_rule AAPt_acc_f { v=AAPt_acc_f OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающая
cyk_rule AAPt_acc_f { OBJ v=AAPt_acc_f } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающая на заводе
cyk_rule AAPt_acc_f { AAPt_acc_f PN } : links { AAPt_acc_f.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_acc_f { AAPit_acc_f PN } : links { AAPit_acc_f.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшая
cyk_rule AAPt_acc_f { PN AAPt_acc_f } : links { AAPt_acc_f.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_acc_f { PN AAPit_acc_f } : links { AAPit_acc_f.<PREPOS_ADJUNCT>PN }

// студентка, начинающая выполнять задание
cyk_rule AAPm_acc_f { AAPm_acc_f IP } : links { AAPm_acc_f.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_acc_f,IP) }

cyk_rule AVP_acc_f { AAPt_acc_f  }
cyk_rule AVP_acc_f { AAPit_acc_f }
cyk_rule AVP_acc_f { AAPm_acc_f  }

cyk_rule AVt_acc_f { z='*' AVt_acc_f } : links { AVt_acc_f.z } : ngrams { -2 }
cyk_rule AVt_acc_f { AVt_acc_f z='*' } : links { AVt_acc_f.z } : ngrams { -2 }
cyk_rule AVit_acc_f { z='*' AVit_acc_f } : links { AVit_acc_f.z } : ngrams { -2 }
cyk_rule AVit_acc_f { AVit_acc_f z='*' } : links { AVit_acc_f.z } : ngrams { -2 }
cyk_rule AVm_acc_f { z='*' AVm_acc_f } : links { AVm_acc_f.z } : ngrams { -2 }
cyk_rule AVm_acc_f { AVm_acc_f z='*' } : links { AVm_acc_f.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_acc_f { AVP_acc_f }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_acc_f1 { AVP_acc_f COMMA } : links { AVP_acc_f.<PUNCTUATION>COMMA }

// Спит кошка, укравшая сметану.
cyk_rule AVPR_acc_f2 { COMMA AVP_acc_f } : links { AVP_acc_f.<PUNCTUATION>COMMA }

// Кошка, укравшая сметану, пошла спать.
cyk_rule AVPR_acc_f2 { COMMA AVPR_acc_f1 } : links { AVPR_acc_f1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_acc_f { AVPR_acc_f2 }
cyk_rule AVPR_acc_f { AVP_acc_f } : ngrams { -1 }

// Обожающая сметану кошка
cyk_rule NP_acc_f { AVP_acc_f NP_acc_f } : links { NP_acc_f.<ADJ_PARTICIPLE>AVP_acc_f }

// Кошка, обожающая сметану
cyk_rule NP_acc_f { NP_acc_f AVPR_acc_f } : links { NP_acc_f.<ADJ_PARTICIPLE>AVPR_acc_f}

//cyk_rule S { AVP_acc_f } : ngrams { -4 } AP_acc_f уже приводится к S






// -------------------------------------
// --- винительный падеж, муж.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_acc_m { AVt_acc_m }  : ngrams { -1 }
cyk_rule AAPit_acc_m { AVit_acc_m } : ngrams { -1 }
cyk_rule AAPm_acc_m { AVm_acc_m }  : ngrams { -1 }

// --- Левое наречие:
// Много работающий
cyk_rule AAPt_acc_m  { Y AVt_acc_m }  : links { AVt_acc_m.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_acc_m) }
cyk_rule AAPit_acc_m { Y AVit_acc_m } : links { AVit_acc_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_acc_m) }
cyk_rule AAPm_acc_m  { Y AVm_acc_m }  : links { AVm_acc_m.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_acc_m) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавший неторопливо
cyk_rule AAPt_acc_m { AVt_acc_m Y } : links { AVt_acc_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_acc_m) }
cyk_rule AAPit_acc_m { AVit_acc_m Y } : links { AVit_acc_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_acc_m) }


// Обещающий нам дождь
cyk_rule AAPt_acc_m { v=AAPt_acc_m OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающий
cyk_rule AAPt_acc_m { OBJ v=AAPt_acc_m } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающий на заводе
cyk_rule AAPt_acc_m { AAPt_acc_m PN } : links { AAPt_acc_m.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_acc_m { AAPit_acc_m PN } : links { AAPit_acc_m.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавший
cyk_rule AAPt_acc_m { PN AAPt_acc_m } : links { AAPt_acc_m.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_acc_m { PN AAPit_acc_m } : links { AAPit_acc_m.<PREPOS_ADJUNCT>PN }

// студент, начинающий выполнять задание
cyk_rule AAPm_acc_m { AAPm_acc_m IP } : links { AAPm_acc_m.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_acc_m,IP) }

cyk_rule AVP_acc_m { AAPt_acc_m  }
cyk_rule AVP_acc_m { AAPit_acc_m }
cyk_rule AVP_acc_m { AAPm_acc_m  }

cyk_rule AVt_acc_m { z='*' AVt_acc_m } : links { AVt_acc_m.z } : ngrams { -2 }
cyk_rule AVt_acc_m { AVt_acc_m z='*' } : links { AVt_acc_m.z } : ngrams { -2 }
cyk_rule AVit_acc_m { z='*' AVit_acc_m } : links { AVit_acc_m.z } : ngrams { -2 }
cyk_rule AVit_acc_m { AVit_acc_m z='*' } : links { AVit_acc_m.z } : ngrams { -2 }
cyk_rule AVm_acc_m { z='*' AVm_acc_m } : links { AVm_acc_m.z } : ngrams { -2 }
cyk_rule AVm_acc_m { AVm_acc_m z='*' } : links { AVm_acc_m.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_acc_m { AVP_acc_m }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_acc_m1 { AVP_acc_m COMMA } : links { AVP_acc_m.<PUNCTUATION>COMMA }

// Спит кот, укравший сметану.
cyk_rule AVPR_acc_m2 { COMMA AVP_acc_m } : links { AVP_acc_m.<PUNCTUATION>COMMA }

// Кот, укравший сметану, пошел спать.
cyk_rule AVPR_acc_m2 { COMMA AVPR_acc_m1 } : links { AVPR_acc_m1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_acc_m { AVPR_acc_m2 }
cyk_rule AVPR_acc_m { AVP_acc_m } : ngrams { -1 }

// Обожающий сметану кот
cyk_rule NP_acc_m { AVP_acc_m NP_acc_m } : links { NP_acc_m.<ADJ_PARTICIPLE>AVP_acc_m }

// Кот, обожающий сметану
cyk_rule NP_acc_m { NP_acc_m AVPR_acc_m } : links { NP_acc_m.<ADJ_PARTICIPLE>AVPR_acc_m}


// -------------------------------------
// --- винительный падеж, ср.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_acc_n { AVt_acc_n }  : ngrams { -2 }
cyk_rule AAPit_acc_n { AVit_acc_n } : ngrams { -2 }
cyk_rule AAPm_acc_n { AVm_acc_n }  : ngrams { -2 }

// --- Левое наречие:
// неторопливо работавше
cyk_rule AAPt_acc_n  { Y AVt_acc_n }  : links { AVt_acc_n.<ATTRIBUTE>Y }  : ngrams { -1 ngram2(Y,AVt_acc_n) }
cyk_rule AAPit_acc_n { Y AVit_acc_n } : links { AVit_acc_n.<ATTRIBUTE>Y } : ngrams { -1 ngram2(Y,AVit_acc_n) }
cyk_rule AAPm_acc_n  { Y AVm_acc_n }  : links { AVm_acc_n.<ATTRIBUTE>Y }  : ngrams { -1 ngram2(Y,AVm_acc_n) }

// --- Правое наречие - используется реже, чем левое
// работавшее неторопливо
cyk_rule AAPt_acc_n { AVt_acc_n Y } : links { AVt_acc_n.<ATTRIBUTE>Y } : ngrams { -1 ngram2(Y,AVt_acc_n) }
cyk_rule AAPit_acc_n { AVit_acc_n Y } : links { AVit_acc_n.<ATTRIBUTE>Y } : ngrams { -1 ngram2(Y,AVit_acc_n) }


// Обещающее нам дождь
cyk_rule AAPt_acc_n { v=AAPt_acc_n OBJ } : links { v.<OBJECT>OBJ } : ngrams { 2 ngram2(v,obj) }

// Дождь нам обещающее
cyk_rule AAPt_acc_n { OBJ v=AAPt_acc_n } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// работающее на заводе
cyk_rule AAPt_acc_n { AAPt_acc_n PN } : links { AAPt_acc_n.<PREPOS_ADJUNCT>PN } : ngrams { 2 }
cyk_rule AAPit_acc_n { AAPit_acc_n PN } : links { AAPit_acc_n.<PREPOS_ADJUNCT>PN } : ngrams { 2 }

// на заводе работавшее
cyk_rule AAPt_acc_n { PN AAPt_acc_n } : links { AAPt_acc_n.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_acc_n { PN AAPit_acc_n } : links { AAPit_acc_n.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// чадо, начинающее выполнять задание
cyk_rule AAPm_acc_n { AAPm_acc_n IP } : links { AAPm_acc_n.<PREPOS_ADJUNCT>IP } : ngrams { 2 ngram2(AAPm_acc_n,IP) }

cyk_rule AVP_acc_n { AAPt_acc_n  }
cyk_rule AVP_acc_n { AAPit_acc_n }
cyk_rule AVP_acc_n { AAPm_acc_n  }

cyk_rule AVt_acc_n { z='*' AVt_acc_n } : links { AVt_acc_n.z } : ngrams { -2 }
cyk_rule AVt_acc_n { AVt_acc_n z='*' } : links { AVt_acc_n.z } : ngrams { -2 }
cyk_rule AVit_acc_n { z='*' AVit_acc_n } : links { AVit_acc_n.z } : ngrams { -2 }
cyk_rule AVit_acc_n { AVit_acc_n z='*' } : links { AVit_acc_n.z } : ngrams { -2 }
cyk_rule AVm_acc_n { z='*' AVm_acc_n } : links { AVm_acc_n.z } : ngrams { -2 }
cyk_rule AVm_acc_n { AVm_acc_n z='*' } : links { AVm_acc_n.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_acc_n { AVP_acc_n }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_acc_n1 { AVP_acc_n COMMA } : links { AVP_acc_n.<PUNCTUATION>COMMA }

// Спит животное, укравшее сметану.
cyk_rule AVPR_acc_n2 { COMMA AVP_acc_n } : links { AVP_acc_n.<PUNCTUATION>COMMA }

// Животное, укравшее сметану, пошло спать.
cyk_rule AVPR_acc_n2 { COMMA AVPR_acc_n1 } : links { AVPR_acc_n1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_acc_n { AVPR_acc_n2 }
cyk_rule AVPR_acc_n { AVP_acc_n } : ngrams { -1 }

// Обожающее сметану животное
cyk_rule NP_acc_n { AVP_acc_n NP_acc_n } : links { NP_acc_n.<ADJ_PARTICIPLE>AVP_acc_n }

// Животное, обожающее сметану
cyk_rule NP_acc_n { NP_acc_n AVPR_acc_n } : links { NP_acc_n.<ADJ_PARTICIPLE>AVPR_acc_n}

//cyk_rule S { AVP_acc_n } : ngrams { -4 } AP_acc_n уже приводится к S






// -------------------------------------
// --- винительный падеж, мн.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_acc_pl { AVt_acc_pl }  : ngrams { -1 }
cyk_rule AAPit_acc_pl { AVit_acc_pl } : ngrams { -1 }
cyk_rule AAPm_acc_pl { AVm_acc_pl }  : ngrams { -1 }

// --- Левое наречие:
// неторопливо работавшие
cyk_rule AAPt_acc_pl  { Y AVt_acc_pl }  : links { AVt_acc_pl.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_acc_pl) }
cyk_rule AAPit_acc_pl { Y AVit_acc_pl } : links { AVit_acc_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_acc_pl) }
cyk_rule AAPm_acc_pl  { Y AVm_acc_pl }  : links { AVm_acc_pl.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_acc_pl) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавшие неторопливо
cyk_rule AAPt_acc_pl { AVt_acc_pl Y } : links { AVt_acc_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_acc_pl) }
cyk_rule AAPit_acc_pl { AVit_acc_pl Y } : links { AVit_acc_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_acc_pl) }


// Обещающие нам дождь
cyk_rule AAPt_acc_pl { v=AAPt_acc_pl OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающие
cyk_rule AAPt_acc_pl { OBJ v=AAPt_acc_pl } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающие на заводе
cyk_rule AAPt_acc_pl { AAPt_acc_pl PN } : links { AAPt_acc_pl.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_acc_pl { AAPit_acc_pl PN } : links { AAPit_acc_pl.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшие
cyk_rule AAPt_acc_pl { PN AAPt_acc_pl } : links { AAPt_acc_pl.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_acc_pl { PN AAPit_acc_pl } : links { AAPit_acc_pl.<PREPOS_ADJUNCT>PN }

// студентки, начинающие выполнять задание
cyk_rule AAPm_acc_pl { AAPm_acc_pl IP } : links { AAPm_acc_pl.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_acc_pl,IP) }

cyk_rule AVP_acc_pl { AAPt_acc_pl  }
cyk_rule AVP_acc_pl { AAPit_acc_pl }
cyk_rule AVP_acc_pl { AAPm_acc_pl  }

cyk_rule AVt_acc_pl { z='*' AVt_acc_pl } : links { AVt_acc_pl.z } : ngrams { -2 }
cyk_rule AVt_acc_pl { AVt_acc_pl z='*' } : links { AVt_acc_pl.z } : ngrams { -2 }
cyk_rule AVit_acc_pl { z='*' AVit_acc_pl } : links { AVit_acc_pl.z } : ngrams { -2 }
cyk_rule AVit_acc_pl { AVit_acc_pl z='*' } : links { AVit_acc_pl.z } : ngrams { -2 }
cyk_rule AVm_acc_pl { z='*' AVm_acc_pl } : links { AVm_acc_pl.z } : ngrams { -2 }
cyk_rule AVm_acc_pl { AVm_acc_pl z='*' } : links { AVm_acc_pl.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_acc_pl { AVP_acc_pl }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_acc_pl1 { AVP_acc_pl COMMA } : links { AVP_acc_pl.<PUNCTUATION>COMMA }

// Спят кошки, укравшие сметану.
cyk_rule AVPR_acc_pl2 { COMMA AVP_acc_pl } : links { AVP_acc_pl.<PUNCTUATION>COMMA }

// Кошки, укравшие сметану, пошли спать.
cyk_rule AVPR_acc_pl2 { COMMA AVPR_acc_pl1 } : links { AVPR_acc_pl1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_acc_pl { AVPR_acc_pl2 }
cyk_rule AVPR_acc_pl { AVP_acc_pl } : ngrams { -1 }

// Обожающие сметану кошки
cyk_rule NP_acc_pl { AVP_acc_pl NP_acc_pl } : links { NP_acc_pl.<ADJ_PARTICIPLE>AVP_acc_pl }

// Кошки, обожающие сметану
cyk_rule NP_acc_pl { NP_acc_pl AVPR_acc_pl } : links { NP_acc_pl.<ADJ_PARTICIPLE>AVPR_acc_pl}

//cyk_rule S { AVP_acc_pl } : ngrams { -4 } AP_acc_pl уже приводится к S









// -------------------------------------
// --- дательный падеж, жен.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_dat_f { AVt_dat_f }  : ngrams { -1 }
cyk_rule AAPit_dat_f { AVit_dat_f } : ngrams { -1 }
cyk_rule AAPm_dat_f { AVm_dat_f }  : ngrams { -1 }

// --- Левое наречие:
// неторопливо работавшая
cyk_rule AAPt_dat_f  { Y AVt_dat_f }  : links { AVt_dat_f.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_dat_f) }
cyk_rule AAPit_dat_f { Y AVit_dat_f } : links { AVit_dat_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_dat_f) }
cyk_rule AAPm_dat_f  { Y AVm_dat_f }  : links { AVm_dat_f.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_dat_f) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавшая неторопливо
cyk_rule AAPt_dat_f { AVt_dat_f Y } : links { AVt_dat_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_dat_f) }
cyk_rule AAPit_dat_f { AVit_dat_f Y } : links { AVit_dat_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_dat_f) }


// Обещающая нам дождь
cyk_rule AAPt_dat_f { v=AAPt_dat_f OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающая
cyk_rule AAPt_dat_f { OBJ v=AAPt_dat_f } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающая на заводе
cyk_rule AAPt_dat_f { AAPt_dat_f PN } : links { AAPt_dat_f.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_dat_f { AAPit_dat_f PN } : links { AAPit_dat_f.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшая
cyk_rule AAPt_dat_f { PN AAPt_dat_f } : links { AAPt_dat_f.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_dat_f { PN AAPit_dat_f } : links { AAPit_dat_f.<PREPOS_ADJUNCT>PN }

// студентка, начинающая выполнять задание
cyk_rule AAPm_dat_f { AAPm_dat_f IP } : links { AAPm_dat_f.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_dat_f,IP) }

cyk_rule AVP_dat_f { AAPt_dat_f  }
cyk_rule AVP_dat_f { AAPit_dat_f }
cyk_rule AVP_dat_f { AAPm_dat_f  }

cyk_rule AVt_dat_f { z='*' AVt_dat_f } : links { AVt_dat_f.z } : ngrams { -2 }
cyk_rule AVt_dat_f { AVt_dat_f z='*' } : links { AVt_dat_f.z } : ngrams { -2 }
cyk_rule AVit_dat_f { z='*' AVit_dat_f } : links { AVit_dat_f.z } : ngrams { -2 }
cyk_rule AVit_dat_f { AVit_dat_f z='*' } : links { AVit_dat_f.z } : ngrams { -2 }
cyk_rule AVm_dat_f { z='*' AVm_dat_f } : links { AVm_dat_f.z } : ngrams { -2 }
cyk_rule AVm_dat_f { AVm_dat_f z='*' } : links { AVm_dat_f.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_dat_f { AVP_dat_f }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_dat_f1 { AVP_dat_f COMMA } : links { AVP_dat_f.<PUNCTUATION>COMMA }

// Спит кошка, укравшая сметану.
cyk_rule AVPR_dat_f2 { COMMA AVP_dat_f } : links { AVP_dat_f.<PUNCTUATION>COMMA }

// Кошка, укравшая сметану, пошла спать.
cyk_rule AVPR_dat_f2 { COMMA AVPR_dat_f1 } : links { AVPR_dat_f1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_dat_f { AVPR_dat_f2 }
cyk_rule AVPR_dat_f { AVP_dat_f } : ngrams { -1 }

// Обожающая сметану кошка
cyk_rule NP_dat_f { AVP_dat_f NP_dat_f } : links { NP_dat_f.<ADJ_PARTICIPLE>AVP_dat_f }

// Кошка, обожающая сметану
cyk_rule NP_dat_f { NP_dat_f AVPR_dat_f } : links { NP_dat_f.<ADJ_PARTICIPLE>AVPR_dat_f}

//cyk_rule S { AVP_dat_f } : ngrams { -4 } AP_dat_f уже приводится к S






// -------------------------------------
// --- дательный падеж, муж.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_dat_m { AVt_dat_m }  : ngrams { -1 }
cyk_rule AAPit_dat_m { AVit_dat_m } : ngrams { -1 }
cyk_rule AAPm_dat_m { AVm_dat_m }  : ngrams { -1 }

// --- Левое наречие:
// Много работающий
cyk_rule AAPt_dat_m  { Y AVt_dat_m }  : links { AVt_dat_m.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_dat_m) }
cyk_rule AAPit_dat_m { Y AVit_dat_m } : links { AVit_dat_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_dat_m) }
cyk_rule AAPm_dat_m  { Y AVm_dat_m }  : links { AVm_dat_m.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_dat_m) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавший неторопливо
cyk_rule AAPt_dat_m { AVt_dat_m Y } : links { AVt_dat_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_dat_m) }
cyk_rule AAPit_dat_m { AVit_dat_m Y } : links { AVit_dat_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_dat_m) }


// Обещающий нам дождь
cyk_rule AAPt_dat_m { v=AAPt_dat_m OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающий
cyk_rule AAPt_dat_m { OBJ v=AAPt_dat_m } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающий на заводе
cyk_rule AAPt_dat_m { AAPt_dat_m PN } : links { AAPt_dat_m.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_dat_m { AAPit_dat_m PN } : links { AAPit_dat_m.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавший
cyk_rule AAPt_dat_m { PN AAPt_dat_m } : links { AAPt_dat_m.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_dat_m { PN AAPit_dat_m } : links { AAPit_dat_m.<PREPOS_ADJUNCT>PN }

// студент, начинающий выполнять задание
cyk_rule AAPm_dat_m { AAPm_dat_m IP } : links { AAPm_dat_m.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_dat_m,IP) }

cyk_rule AVP_dat_m { AAPt_dat_m  }
cyk_rule AVP_dat_m { AAPit_dat_m }
cyk_rule AVP_dat_m { AAPm_dat_m  }

cyk_rule AVt_dat_m { z='*' AVt_dat_m } : links { AVt_dat_m.z } : ngrams { -2 }
cyk_rule AVt_dat_m { AVt_dat_m z='*' } : links { AVt_dat_m.z } : ngrams { -2 }
cyk_rule AVit_dat_m { z='*' AVit_dat_m } : links { AVit_dat_m.z } : ngrams { -2 }
cyk_rule AVit_dat_m { AVit_dat_m z='*' } : links { AVit_dat_m.z } : ngrams { -2 }
cyk_rule AVm_dat_m { z='*' AVm_dat_m } : links { AVm_dat_m.z } : ngrams { -2 }
cyk_rule AVm_dat_m { AVm_dat_m z='*' } : links { AVm_dat_m.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_dat_m { AVP_dat_m }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_dat_m1 { AVP_dat_m COMMA } : links { AVP_dat_m.<PUNCTUATION>COMMA }

// Спит кот, укравший сметану.
cyk_rule AVPR_dat_m2 { COMMA AVP_dat_m } : links { AVP_dat_m.<PUNCTUATION>COMMA }

// Кот, укравший сметану, пошел спать.
cyk_rule AVPR_dat_m2 { COMMA AVPR_dat_m1 } : links { AVPR_dat_m1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_dat_m { AVPR_dat_m2 }
cyk_rule AVPR_dat_m { AVP_dat_m } : ngrams { -1 }

// Обожающий сметану кот
cyk_rule NP_dat_m { AVP_dat_m NP_dat_m } : links { NP_dat_m.<ADJ_PARTICIPLE>AVP_dat_m }

// Кот, обожающий сметану
cyk_rule NP_dat_m { NP_dat_m AVPR_dat_m } : links { NP_dat_m.<ADJ_PARTICIPLE>AVPR_dat_m}


// -------------------------------------
// --- дательный падеж, ср.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_dat_n { AVt_dat_n }  : ngrams { -1 }
cyk_rule AAPit_dat_n { AVit_dat_n } : ngrams { -1 }
cyk_rule AAPm_dat_n { AVm_dat_n }  : ngrams { -1 }

// --- Левое наречие:
// неторопливо работавше
cyk_rule AAPt_dat_n  { Y AVt_dat_n }  : links { AVt_dat_n.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_dat_n) }
cyk_rule AAPit_dat_n { Y AVit_dat_n } : links { AVit_dat_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_dat_n) }
cyk_rule AAPm_dat_n  { Y AVm_dat_n }  : links { AVm_dat_n.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_dat_n) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавшее неторопливо
cyk_rule AAPt_dat_n { AVt_dat_n Y } : links { AVt_dat_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_dat_n) }
cyk_rule AAPit_dat_n { AVit_dat_n Y } : links { AVit_dat_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_dat_n) }


// Обещающее нам дождь
cyk_rule AAPt_dat_n { v=AAPt_dat_n OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающее
cyk_rule AAPt_dat_n { OBJ v=AAPt_dat_n } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающее на заводе
cyk_rule AAPt_dat_n { AAPt_dat_n PN } : links { AAPt_dat_n.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_dat_n { AAPit_dat_n PN } : links { AAPit_dat_n.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшее
cyk_rule AAPt_dat_n { PN AAPt_dat_n } : links { AAPt_dat_n.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_dat_n { PN AAPit_dat_n } : links { AAPit_dat_n.<PREPOS_ADJUNCT>PN }

// чадо, начинающее выполнять задание
cyk_rule AAPm_dat_n { AAPm_dat_n IP } : links { AAPm_dat_n.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_dat_n,IP) }

cyk_rule AVP_dat_n { AAPt_dat_n  }
cyk_rule AVP_dat_n { AAPit_dat_n }
cyk_rule AVP_dat_n { AAPm_dat_n  }

cyk_rule AVt_dat_n { z='*' AVt_dat_n } : links { AVt_dat_n.z } : ngrams { -2 }
cyk_rule AVt_dat_n { AVt_dat_n z='*' } : links { AVt_dat_n.z } : ngrams { -2 }
cyk_rule AVit_dat_n { z='*' AVit_dat_n } : links { AVit_dat_n.z } : ngrams { -2 }
cyk_rule AVit_dat_n { AVit_dat_n z='*' } : links { AVit_dat_n.z } : ngrams { -2 }
cyk_rule AVm_dat_n { z='*' AVm_dat_n } : links { AVm_dat_n.z } : ngrams { -2 }
cyk_rule AVm_dat_n { AVm_dat_n z='*' } : links { AVm_dat_n.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_dat_n { AVP_dat_n }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_dat_n1 { AVP_dat_n COMMA } : links { AVP_dat_n.<PUNCTUATION>COMMA }

// Спит животное, укравшее сметану.
cyk_rule AVPR_dat_n2 { COMMA AVP_dat_n } : links { AVP_dat_n.<PUNCTUATION>COMMA }

// Животное, укравшее сметану, пошло спать.
cyk_rule AVPR_dat_n2 { COMMA AVPR_dat_n1 } : links { AVPR_dat_n1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_dat_n { AVPR_dat_n2 }
cyk_rule AVPR_dat_n { AVP_dat_n } : ngrams { -1 }

// Обожающее сметану животное
cyk_rule NP_dat_n { AVP_dat_n NP_dat_n } : links { NP_dat_n.<ADJ_PARTICIPLE>AVP_dat_n }

// Животное, обожающее сметану
cyk_rule NP_dat_n { NP_dat_n AVPR_dat_n } : links { NP_dat_n.<ADJ_PARTICIPLE>AVPR_dat_n}

//cyk_rule S { AVP_dat_n } : ngrams { -4 } AP_dat_n уже приводится к S






// -------------------------------------
// --- дательный падеж, мн.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_dat_pl { AVt_dat_pl }  : ngrams { -1 }
cyk_rule AAPit_dat_pl { AVit_dat_pl } : ngrams { -1 }
cyk_rule AAPm_dat_pl { AVm_dat_pl }  : ngrams { -1 }

// --- Левое наречие:
// неторопливо работавшие
cyk_rule AAPt_dat_pl  { Y AVt_dat_pl }  : links { AVt_dat_pl.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_dat_pl) }
cyk_rule AAPit_dat_pl { Y AVit_dat_pl } : links { AVit_dat_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_dat_pl) }
cyk_rule AAPm_dat_pl  { Y AVm_dat_pl }  : links { AVm_dat_pl.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_dat_pl) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавшие неторопливо
cyk_rule AAPt_dat_pl { AVt_dat_pl Y } : links { AVt_dat_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_dat_pl) }
cyk_rule AAPit_dat_pl { AVit_dat_pl Y } : links { AVit_dat_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_dat_pl) }


// Обещающие нам дождь
cyk_rule AAPt_dat_pl { v=AAPt_dat_pl OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающие
cyk_rule AAPt_dat_pl { OBJ v=AAPt_dat_pl } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающие на заводе
cyk_rule AAPt_dat_pl { AAPt_dat_pl PN } : links { AAPt_dat_pl.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_dat_pl { AAPit_dat_pl PN } : links { AAPit_dat_pl.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшие
cyk_rule AAPt_dat_pl { PN AAPt_dat_pl } : links { AAPt_dat_pl.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_dat_pl { PN AAPit_dat_pl } : links { AAPit_dat_pl.<PREPOS_ADJUNCT>PN }

// студентки, начинающие выполнять задание
cyk_rule AAPm_dat_pl { AAPm_dat_pl IP } : links { AAPm_dat_pl.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_dat_pl,IP) }

cyk_rule AVP_dat_pl { AAPt_dat_pl  }
cyk_rule AVP_dat_pl { AAPit_dat_pl }
cyk_rule AVP_dat_pl { AAPm_dat_pl  }

cyk_rule AVt_dat_pl { z='*' AVt_dat_pl } : links { AVt_dat_pl.z } : ngrams { -2 }
cyk_rule AVt_dat_pl { AVt_dat_pl z='*' } : links { AVt_dat_pl.z } : ngrams { -2 }
cyk_rule AVit_dat_pl { z='*' AVit_dat_pl } : links { AVit_dat_pl.z } : ngrams { -2 }
cyk_rule AVit_dat_pl { AVit_dat_pl z='*' } : links { AVit_dat_pl.z } : ngrams { -2 }
cyk_rule AVm_dat_pl { z='*' AVm_dat_pl } : links { AVm_dat_pl.z } : ngrams { -2 }
cyk_rule AVm_dat_pl { AVm_dat_pl z='*' } : links { AVm_dat_pl.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_dat_pl { AVP_dat_pl }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_dat_pl1 { AVP_dat_pl COMMA } : links { AVP_dat_pl.<PUNCTUATION>COMMA }

// Спят кошки, укравшие сметану.
cyk_rule AVPR_dat_pl2 { COMMA AVP_dat_pl } : links { AVP_dat_pl.<PUNCTUATION>COMMA }

// Кошки, укравшие сметану, пошли спать.
cyk_rule AVPR_dat_pl2 { COMMA AVPR_dat_pl1 } : links { AVPR_dat_pl1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_dat_pl { AVPR_dat_pl2 }
cyk_rule AVPR_dat_pl { AVP_dat_pl } : ngrams { -1 }

// Обожающие сметану кошки
cyk_rule NP_dat_pl { AVP_dat_pl NP_dat_pl } : links { NP_dat_pl.<ADJ_PARTICIPLE>AVP_dat_pl }

// Кошки, обожающие сметану
cyk_rule NP_dat_pl { NP_dat_pl AVPR_dat_pl } : links { NP_dat_pl.<ADJ_PARTICIPLE>AVPR_dat_pl}

//cyk_rule S { AVP_dat_pl } : ngrams { -4 } AP_dat_pl уже приводится к S








// -------------------------------------
// --- предложный падеж, жен.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_prep_f { AVt_prep_f }  : ngrams { -1 }
cyk_rule AAPit_prep_f { AVit_prep_f } : ngrams { -1 }
cyk_rule AAPm_prep_f { AVm_prep_f }  : ngrams { -1 }

// --- Левое наречие:
// неторопливо работавшая
cyk_rule AAPt_prep_f  { Y AVt_prep_f }  : links { AVt_prep_f.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_prep_f) }
cyk_rule AAPit_prep_f { Y AVit_prep_f } : links { AVit_prep_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_prep_f) }
cyk_rule AAPm_prep_f  { Y AVm_prep_f }  : links { AVm_prep_f.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_prep_f) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавшая неторопливо
cyk_rule AAPt_prep_f { AVt_prep_f Y } : links { AVt_prep_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_prep_f) }
cyk_rule AAPit_prep_f { AVit_prep_f Y } : links { AVit_prep_f.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_prep_f) }


// Обещающая нам дождь
cyk_rule AAPt_prep_f { v=AAPt_prep_f OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающая
cyk_rule AAPt_prep_f { OBJ v=AAPt_prep_f } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающая на заводе
cyk_rule AAPt_prep_f { AAPt_prep_f PN } : links { AAPt_prep_f.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_prep_f { AAPit_prep_f PN } : links { AAPit_prep_f.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшая
cyk_rule AAPt_prep_f { PN AAPt_prep_f } : links { AAPt_prep_f.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_prep_f { PN AAPit_prep_f } : links { AAPit_prep_f.<PREPOS_ADJUNCT>PN }

// студентка, начинающая выполнять задание
cyk_rule AAPm_prep_f { AAPm_prep_f IP } : links { AAPm_prep_f.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_prep_f,IP) }

cyk_rule AVP_prep_f { AAPt_prep_f  }
cyk_rule AVP_prep_f { AAPit_prep_f }
cyk_rule AVP_prep_f { AAPm_prep_f  }

cyk_rule AVt_prep_f { z='*' AVt_prep_f } : links { AVt_prep_f.z } : ngrams { -2 }
cyk_rule AVt_prep_f { AVt_prep_f z='*' } : links { AVt_prep_f.z } : ngrams { -2 }
cyk_rule AVit_prep_f { z='*' AVit_prep_f } : links { AVit_prep_f.z } : ngrams { -2 }
cyk_rule AVit_prep_f { AVit_prep_f z='*' } : links { AVit_prep_f.z } : ngrams { -2 }
cyk_rule AVm_prep_f { z='*' AVm_prep_f } : links { AVm_prep_f.z } : ngrams { -2 }
cyk_rule AVm_prep_f { AVm_prep_f z='*' } : links { AVm_prep_f.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_prep_f { AVP_prep_f }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_prep_f1 { AVP_prep_f COMMA } : links { AVP_prep_f.<PUNCTUATION>COMMA }

// Спит кошка, укравшая сметану.
cyk_rule AVPR_prep_f2 { COMMA AVP_prep_f } : links { AVP_prep_f.<PUNCTUATION>COMMA }

// Кошка, укравшая сметану, пошла спать.
cyk_rule AVPR_prep_f2 { COMMA AVPR_prep_f1 } : links { AVPR_prep_f1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_prep_f { AVPR_prep_f2 }
cyk_rule AVPR_prep_f { AVP_prep_f } : ngrams { -1 }

// Обожающая сметану кошка
cyk_rule NP_prep_f { AVP_prep_f NP_prep_f } : links { NP_prep_f.<ADJ_PARTICIPLE>AVP_prep_f }

// Кошка, обожающая сметану
cyk_rule NP_prep_f { NP_prep_f AVPR_prep_f } : links { NP_prep_f.<ADJ_PARTICIPLE>AVPR_prep_f}

//cyk_rule S { AVP_prep_f } : ngrams { -4 } AP_prep_f уже приводится к S






// -------------------------------------
// --- предложный падеж, муж.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_prep_m { AVt_prep_m }  : ngrams { -1 }
cyk_rule AAPit_prep_m { AVit_prep_m } : ngrams { -1 }
cyk_rule AAPm_prep_m { AVm_prep_m }  : ngrams { -1 }

// --- Левое наречие:
// Много работающий
cyk_rule AAPt_prep_m  { Y AVt_prep_m }  : links { AVt_prep_m.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_prep_m) }
cyk_rule AAPit_prep_m { Y AVit_prep_m } : links { AVit_prep_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_prep_m) }
cyk_rule AAPm_prep_m  { Y AVm_prep_m }  : links { AVm_prep_m.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_prep_m) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавший неторопливо
cyk_rule AAPt_prep_m { AVt_prep_m Y } : links { AVt_prep_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_prep_m) }
cyk_rule AAPit_prep_m { AVit_prep_m Y } : links { AVit_prep_m.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_prep_m) }


// Обещающий нам дождь
cyk_rule AAPt_prep_m { v=AAPt_prep_m OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающий
cyk_rule AAPt_prep_m { OBJ v=AAPt_prep_m } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающий на заводе
cyk_rule AAPt_prep_m { AAPt_prep_m PN } : links { AAPt_prep_m.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_prep_m { AAPit_prep_m PN } : links { AAPit_prep_m.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавший
cyk_rule AAPt_prep_m { PN AAPt_prep_m } : links { AAPt_prep_m.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_prep_m { PN AAPit_prep_m } : links { AAPit_prep_m.<PREPOS_ADJUNCT>PN }

// студент, начинающий выполнять задание
cyk_rule AAPm_prep_m { AAPm_prep_m IP } : links { AAPm_prep_m.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_prep_m,IP) }

cyk_rule AVP_prep_m { AAPt_prep_m  }
cyk_rule AVP_prep_m { AAPit_prep_m }
cyk_rule AVP_prep_m { AAPm_prep_m  }

cyk_rule AVt_prep_m { z='*' AVt_prep_m } : links { AVt_prep_m.z } : ngrams { -2 }
cyk_rule AVt_prep_m { AVt_prep_m z='*' } : links { AVt_prep_m.z } : ngrams { -2 }
cyk_rule AVit_prep_m { z='*' AVit_prep_m } : links { AVit_prep_m.z } : ngrams { -2 }
cyk_rule AVit_prep_m { AVit_prep_m z='*' } : links { AVit_prep_m.z } : ngrams { -2 }
cyk_rule AVm_prep_m { z='*' AVm_prep_m } : links { AVm_prep_m.z } : ngrams { -2 }
cyk_rule AVm_prep_m { AVm_prep_m z='*' } : links { AVm_prep_m.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_prep_m { AVP_prep_m }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_prep_m1 { AVP_prep_m COMMA } : links { AVP_prep_m.<PUNCTUATION>COMMA }

// Спит кот, укравший сметану.
cyk_rule AVPR_prep_m2 { COMMA AVP_prep_m } : links { AVP_prep_m.<PUNCTUATION>COMMA }

// Кот, укравший сметану, пошел спать.
cyk_rule AVPR_prep_m2 { COMMA AVPR_prep_m1 } : links { AVPR_prep_m1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_prep_m { AVPR_prep_m2 }
cyk_rule AVPR_prep_m { AVP_prep_m } : ngrams { -1 }

// Обожающий сметану кот
cyk_rule NP_prep_m { AVP_prep_m NP_prep_m } : links { NP_prep_m.<ADJ_PARTICIPLE>AVP_prep_m }

// Кот, обожающий сметану
cyk_rule NP_prep_m { NP_prep_m AVPR_prep_m } : links { NP_prep_m.<ADJ_PARTICIPLE>AVPR_prep_m}


// -------------------------------------
// --- предложный падеж, ср.р. ед.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_prep_n { AVt_prep_n }  : ngrams { -1 }
cyk_rule AAPit_prep_n { AVit_prep_n } : ngrams { -1 }
cyk_rule AAPm_prep_n { AVm_prep_n }  : ngrams { -1 }

// --- Левое наречие:
// неторопливо работавше
cyk_rule AAPt_prep_n  { Y AVt_prep_n }  : links { AVt_prep_n.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_prep_n) }
cyk_rule AAPit_prep_n { Y AVit_prep_n } : links { AVit_prep_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_prep_n) }
cyk_rule AAPm_prep_n  { Y AVm_prep_n }  : links { AVm_prep_n.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_prep_n) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавшее неторопливо
cyk_rule AAPt_prep_n { AVt_prep_n Y } : links { AVt_prep_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_prep_n) }
cyk_rule AAPit_prep_n { AVit_prep_n Y } : links { AVit_prep_n.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_prep_n) }


// Обещающее нам дождь
cyk_rule AAPt_prep_n { v=AAPt_prep_n OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающее
cyk_rule AAPt_prep_n { OBJ v=AAPt_prep_n } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающее на заводе
cyk_rule AAPt_prep_n { AAPt_prep_n PN } : links { AAPt_prep_n.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_prep_n { AAPit_prep_n PN } : links { AAPit_prep_n.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшее
cyk_rule AAPt_prep_n { PN AAPt_prep_n } : links { AAPt_prep_n.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_prep_n { PN AAPit_prep_n } : links { AAPit_prep_n.<PREPOS_ADJUNCT>PN }

// чадо, начинающее выполнять задание
cyk_rule AAPm_prep_n { AAPm_prep_n IP } : links { AAPm_prep_n.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_prep_n,IP) }

cyk_rule AVP_prep_n { AAPt_prep_n  }
cyk_rule AVP_prep_n { AAPit_prep_n }
cyk_rule AVP_prep_n { AAPm_prep_n  }

cyk_rule AVt_prep_n { z='*' AVt_prep_n } : links { AVt_prep_n.z } : ngrams { -2 }
cyk_rule AVt_prep_n { AVt_prep_n z='*' } : links { AVt_prep_n.z } : ngrams { -2 }
cyk_rule AVit_prep_n { z='*' AVit_prep_n } : links { AVit_prep_n.z } : ngrams { -2 }
cyk_rule AVit_prep_n { AVit_prep_n z='*' } : links { AVit_prep_n.z } : ngrams { -2 }
cyk_rule AVm_prep_n { z='*' AVm_prep_n } : links { AVm_prep_n.z } : ngrams { -2 }
cyk_rule AVm_prep_n { AVm_prep_n z='*' } : links { AVm_prep_n.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_prep_n { AVP_prep_n }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_prep_n1 { AVP_prep_n COMMA } : links { AVP_prep_n.<PUNCTUATION>COMMA }

// Спит животное, укравшее сметану.
cyk_rule AVPR_prep_n2 { COMMA AVP_prep_n } : links { AVP_prep_n.<PUNCTUATION>COMMA }

// Животное, укравшее сметану, пошло спать.
cyk_rule AVPR_prep_n2 { COMMA AVPR_prep_n1 } : links { AVPR_prep_n1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_prep_n { AVPR_prep_n2 }
cyk_rule AVPR_prep_n { AVP_prep_n } : ngrams { -1 }

// Обожающее сметану животное
cyk_rule NP_prep_n { AVP_prep_n NP_prep_n } : links { NP_prep_n.<ADJ_PARTICIPLE>AVP_prep_n }

// Животное, обожающее сметану
cyk_rule NP_prep_n { NP_prep_n AVPR_prep_n } : links { NP_prep_n.<ADJ_PARTICIPLE>AVPR_prep_n}

//cyk_rule S { AVP_prep_n } : ngrams { -4 } AP_prep_n уже приводится к S






// -------------------------------------
// --- предложный падеж, мн.ч.
// -------------------------------------

// Постараемся учесть, что одиночное причастие обычно не формирует причастный оборот.
cyk_rule AAPt_prep_pl { AVt_prep_pl }  : ngrams { -1 }
cyk_rule AAPit_prep_pl { AVit_prep_pl } : ngrams { -1 }
cyk_rule AAPm_prep_pl { AVm_prep_pl }  : ngrams { -1 }

// --- Левое наречие:
// неторопливо работавшие
cyk_rule AAPt_prep_pl  { Y AVt_prep_pl }  : links { AVt_prep_pl.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVt_prep_pl) }
cyk_rule AAPit_prep_pl { Y AVit_prep_pl } : links { AVit_prep_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_prep_pl) }
cyk_rule AAPm_prep_pl  { Y AVm_prep_pl }  : links { AVm_prep_pl.<ATTRIBUTE>Y }  : ngrams { ngram2(Y,AVm_prep_pl) }

// --- Правое наречие - используется реже, чем левое, но штрафовать не будем.
// работавшие неторопливо
cyk_rule AAPt_prep_pl { AVt_prep_pl Y } : links { AVt_prep_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVt_prep_pl) }
cyk_rule AAPit_prep_pl { AVit_prep_pl Y } : links { AVit_prep_pl.<ATTRIBUTE>Y } : ngrams { ngram2(Y,AVit_prep_pl) }


// Обещающие нам дождь
cyk_rule AAPt_prep_pl { v=AAPt_prep_pl OBJ } : links { v.<OBJECT>OBJ } : ngrams { 1 ngram2(v,obj) }

// Дождь нам обещающие
cyk_rule AAPt_prep_pl { OBJ v=AAPt_prep_pl } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,obj) }

// работающие на заводе
cyk_rule AAPt_prep_pl { AAPt_prep_pl PN } : links { AAPt_prep_pl.<PREPOS_ADJUNCT>PN } : ngrams { 1 }
cyk_rule AAPit_prep_pl { AAPit_prep_pl PN } : links { AAPit_prep_pl.<PREPOS_ADJUNCT>PN } : ngrams { 1 }

// на заводе работавшие
cyk_rule AAPt_prep_pl { PN AAPt_prep_pl } : links { AAPt_prep_pl.<PREPOS_ADJUNCT>PN }
cyk_rule AAPit_prep_pl { PN AAPit_prep_pl } : links { AAPit_prep_pl.<PREPOS_ADJUNCT>PN }

// студентки, начинающие выполнять задание
cyk_rule AAPm_prep_pl { AAPm_prep_pl IP } : links { AAPm_prep_pl.<PREPOS_ADJUNCT>IP } : ngrams { 1 ngram2(AAPm_prep_pl,IP) }

cyk_rule AVP_prep_pl { AAPt_prep_pl  }
cyk_rule AVP_prep_pl { AAPit_prep_pl }
cyk_rule AVP_prep_pl { AAPm_prep_pl  }

cyk_rule AVt_prep_pl { z='*' AVt_prep_pl } : links { AVt_prep_pl.z } : ngrams { -2 }
cyk_rule AVt_prep_pl { AVt_prep_pl z='*' } : links { AVt_prep_pl.z } : ngrams { -2 }
cyk_rule AVit_prep_pl { z='*' AVit_prep_pl } : links { AVit_prep_pl.z } : ngrams { -2 }
cyk_rule AVit_prep_pl { AVit_prep_pl z='*' } : links { AVit_prep_pl.z } : ngrams { -2 }
cyk_rule AVm_prep_pl { z='*' AVm_prep_pl } : links { AVm_prep_pl.z } : ngrams { -2 }
cyk_rule AVm_prep_pl { AVm_prep_pl z='*' } : links { AVm_prep_pl.z } : ngrams { -2 }


// Причастный оборот без отбивки запятыми может выступать в роли левого определения
cyk_rule AP_prep_pl { AVP_prep_pl }

// Для использования в роли правого определения нужна отбивка запятыми:

cyk_rule AVPR_prep_pl1 { AVP_prep_pl COMMA } : links { AVP_prep_pl.<PUNCTUATION>COMMA }

// Спят кошки, укравшие сметану.
cyk_rule AVPR_prep_pl2 { COMMA AVP_prep_pl } : links { AVP_prep_pl.<PUNCTUATION>COMMA }

// Кошки, укравшие сметану, пошли спать.
cyk_rule AVPR_prep_pl2 { COMMA AVPR_prep_pl1 } : links { AVPR_prep_pl1.<PUNCTUATION>COMMA }

// Этот нетерминал присоединяется СПРАВА к атрибутируемому существительному
cyk_rule AVPR_prep_pl { AVPR_prep_pl2 }
cyk_rule AVPR_prep_pl { AVP_prep_pl } : ngrams { -1 }

// Обожающие сметану кошки
cyk_rule NP_prep_pl { AVP_prep_pl NP_prep_pl } : links { NP_prep_pl.<ADJ_PARTICIPLE>AVP_prep_pl }

// Кошки, обожающие сметану
cyk_rule NP_prep_pl { NP_prep_pl AVPR_prep_pl } : links { NP_prep_pl.<ADJ_PARTICIPLE>AVPR_prep_pl}

//cyk_rule S { AVP_prep_pl } : ngrams { -4 } AP_prep_pl уже приводится к S





// ############################
// группа существительного
// ############################

// ============ ГРУППА СУЩ. В ИМ. ПАДЕЖЕ =============

cyk_rule NP_nom_f { N_nom_f }
cyk_rule NP_nom_f { AP_nom_f N_nom_f } : links { N_nom_f.<ATTRIBUTE>AP_nom_f } : ngrams { ngram2(AP_nom_f,N_nom_f) }
cyk_rule NP_nom_f { n1=N_nom_f n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_nom_m { N_nom_m }
cyk_rule NP_nom_m { AP_nom_m N_nom_m } : links { N_nom_m.<ATTRIBUTE>AP_nom_m } : ngrams { ngram2(AP_nom_m,N_nom_m) }
cyk_rule NP_nom_m { n1=N_nom_m n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_nom_n { N_nom_n }
cyk_rule NP_nom_n { AP_nom_n N_nom_n } : links { N_nom_n.<ATTRIBUTE>AP_nom_n } : ngrams { ngram2(AP_nom_n,N_nom_n) }
cyk_rule NP_nom_n { n1=N_nom_n n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_nom_pl { N_nom_pl }
cyk_rule NP_nom_pl { AP_nom_pl N_nom_pl } : links { N_nom_pl.<ATTRIBUTE>AP_nom_pl } : ngrams { ngram2(AP_nom_pl,N_nom_pl) }
cyk_rule NP_nom_pl { n1=N_nom_pl n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

// --- число+сущ: ---
// 1 кошка спит
cyk_rule NP_nom_f { a=D n=NP_nom_f } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
// 1 человек спит
cyk_rule NP_nom_m { a=D n=NP_nom_m } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
// 1 животное спит
cyk_rule NP_nom_n { a=D n=NP_nom_n } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
// 5 человек спят
cyk_rule NP_nom_pl { a=D n='NP_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }


// --- ФИО в качестве существительного.
// А.Н.Гончарова писала стихи
cyk_rule NP_nom_f { PERSON } : ngrams { -1 }
// А.С.Пушкин писал стихи
cyk_rule NP_nom_m { PERSON } : ngrams { -1 }

// ---- Союзные конструкции для существительного ----

// NPJ_xxx_yyy это присоединяемая справа конструкция, начинающаяся с союза, запятой или (со штрафом) без оных
cyk_rule NPJ_nom { JP obj='NP_nom_*' } : links { JP.<OBJECT>obj }
cyk_rule NPJ_nom { 'NP_nom_*' } : ngrams { -1 }

// Кошка и собака
// Кошка, собака
cyk_rule NP_nom_f { n1=NP_nom_f n2=NPJ_nom } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_nom_m { n1=NP_nom_m n2=NPJ_nom } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_nom_n { n1=NP_nom_n n2=NPJ_nom } : links { n1.<RIGHT_LOGIC_ITEM>n2 }

// соединение двух существительных союзом И дает для подлежащего множественное число:
// Кошка и собака спят рядом
cyk_rule NP_nom_pl { n1='NP_nom_*' n2=NPJ_nom } : links { n1.<RIGHT_LOGIC_ITEM>n2 }


// Союзные паттерны с двумя союзами:
// И кошка, и собака
cyk_rule NPJ1_nom_f { J2 obj=NP_nom_f } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_nom_m { J2 obj=NP_nom_m } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_nom_n { J2 obj=NP_nom_n } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_nom_pl { J2 obj=NP_nom_pl } : links { obj.<PREFIX_CONJUNCTION>J2 }

cyk_rule NPJ2_nom { JP2 obj='NP_nom_*' } : links { JP2.<OBJECT>obj }

// и хитрая лисичка, и бесхитросный волк
cyk_rule NP_nom_f  { n1=NPJ1_nom_f n2=NPJ2_nom } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_nom_m  { n1=NPJ1_nom_m n2=NPJ2_nom } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_nom_n  { n1=NPJ1_nom_n n2=NPJ2_nom } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_nom_pl { n1=NPJ1_nom_pl n2=NPJ2_nom } : links { n1.<RIGHT_LOGIC_ITEM>n2 }

// ---- конец союзных паттернов для им. падежа



cyk_rule S { NP_nom_f } : ngrams { -3 }
cyk_rule S { NP_nom_m } : ngrams { -3 }
cyk_rule S { NP_nom_n } : ngrams { -3 }
cyk_rule S { NP_nom_pl } : ngrams { -3 }

// связывание по умолчанию

cyk_rule NP_nom_f { z='*' NP_nom_f } : links { NP_nom_f.z } : ngrams { -2 }
cyk_rule NP_nom_f { NP_nom_f z='*' } : links { NP_nom_f.z } : ngrams { -2 }
cyk_rule NP_nom_m { z='*' NP_nom_m } : links { NP_nom_m.z } : ngrams { -2 }
cyk_rule NP_nom_m { NP_nom_m z='*' } : links { NP_nom_m.z } : ngrams { -2 }
cyk_rule NP_nom_n { z='*' NP_nom_n } : links { NP_nom_n.z } : ngrams { -2 }
cyk_rule NP_nom_n { NP_nom_n z='*' } : links { NP_nom_n.z } : ngrams { -2 }
cyk_rule NP_nom_pl { z='*' NP_nom_pl } : links { NP_nom_pl.z } : ngrams { -2 }
cyk_rule NP_nom_pl { NP_nom_pl z='*' } : links { NP_nom_pl.z } : ngrams { -2 }


// ============ ГРУППА СУЩ. В РОД. ПАДЕЖЕ =============

cyk_rule NP_gen_f { N_gen_f }
cyk_rule NP_gen_f { AP_gen_f N_gen_f } : links { N_gen_f.<ATTRIBUTE>AP_gen_f } : ngrams { ngram2(AP_gen_f,N_gen_f) }
cyk_rule NP_gen_f { n1=N_gen_f n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_gen_m { N_gen_m }
cyk_rule NP_gen_m { AP_gen_m N_gen_m } : links { N_gen_m.<ATTRIBUTE>AP_gen_m } : ngrams { ngram2(AP_gen_m,N_gen_m) }
cyk_rule NP_gen_m { n1=N_gen_m n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_gen_n { N_gen_n }
cyk_rule NP_gen_n { AP_gen_n N_gen_n } : links { N_gen_n.<ATTRIBUTE>AP_gen_n } : ngrams { ngram2(AP_gen_n,N_gen_n) }
cyk_rule NP_gen_n { n1=N_gen_n n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_gen_pl { N_gen_pl }
cyk_rule NP_gen_pl { AP_gen_pl N_gen_pl } : links { N_gen_pl.<ATTRIBUTE>AP_gen_pl } : ngrams { ngram2(AP_gen_pl,N_gen_pl) }
cyk_rule NP_gen_pl { n1=N_gen_pl n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

// конец 3 попыток
cyk_rule NP_gen_f { a=D n='NP_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
cyk_rule NP_gen_m { a=D n='NP_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
cyk_rule NP_gen_n { a=D n='NP_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
cyk_rule NP_gen_pl { a=D n='NP_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }


// роман А.Н.Гончаровой
cyk_rule NP_gen_f { PERSON } : ngrams { -1 }
// стихи А.С.Пушкина
cyk_rule NP_gen_m { PERSON } : ngrams { -1 }


// ---- Союзные конструкции для существительного ----

// NPJ_xxx_yyy это присоединяемая справа конструкция, начинающаяся с союза, запятой или (со штрафом) без оных
cyk_rule NPJ_gen { JP obj='NP_gen_*' } : links { JP.<OBJECT>obj }
cyk_rule NPJ_gen { 'NP_gen_*' } : ngrams { -1 }

// у кошки и собаки
// у кошки, собаки
cyk_rule NP_gen_f { n1=NP_gen_f n2=NPJ_gen } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_gen_m { n1=NP_gen_m n2=NPJ_gen } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_gen_n { n1=NP_gen_n n2=NPJ_gen } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_gen_pl { n1=NP_gen_pl n2=NPJ_gen } : links { n1.<RIGHT_LOGIC_ITEM>n2 }

// Союзные паттерны с двумя союзами:
// ??? todo пример
cyk_rule NPJ1_gen_f { J2 obj=NP_gen_f } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_gen_m { J2 obj=NP_gen_m } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_gen_n { J2 obj=NP_gen_n } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_gen_pl { J2 obj=NP_gen_pl } : links { obj.<PREFIX_CONJUNCTION>J2 }

cyk_rule NPJ2_gen { JP2 obj='NP_gen_*' } : links { JP2.<OBJECT>obj }

// и хитрой лисички, и бесхитросного волка
cyk_rule NP_gen_f  { n1=NPJ1_gen_f n2=NPJ2_gen } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_gen_m  { n1=NPJ1_gen_m n2=NPJ2_gen } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_gen_n  { n1=NPJ1_gen_n n2=NPJ2_gen } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_gen_pl { n1=NPJ1_gen_pl n2=NPJ2_gen } : links { n1.<RIGHT_LOGIC_ITEM>n2 }

// ---- конец союзных паттернов для род. падежа



cyk_rule S { NP_gen_f } : ngrams { -3 }
cyk_rule S { NP_gen_m } : ngrams { -3 }
cyk_rule S { NP_gen_n } : ngrams { -3 }
cyk_rule S { NP_gen_pl } : ngrams { -3 }

// связывание по умолчанию

cyk_rule NP_gen_f { z='*' NP_gen_f } : links { NP_gen_f.z } : ngrams { -2 }
cyk_rule NP_gen_f { NP_gen_f z='*' } : links { NP_gen_f.z } : ngrams { -2 }
cyk_rule NP_gen_m { z='*' NP_gen_m } : links { NP_gen_m.z } : ngrams { -2 }
cyk_rule NP_gen_m { NP_gen_m z='*' } : links { NP_gen_m.z } : ngrams { -2 }
cyk_rule NP_gen_n { z='*' NP_gen_n } : links { NP_gen_n.z } : ngrams { -2 }
cyk_rule NP_gen_n { NP_gen_n z='*' } : links { NP_gen_n.z } : ngrams { -2 }
cyk_rule NP_gen_pl { z='*' NP_gen_pl } : links { NP_gen_pl.z } : ngrams { -2 }
cyk_rule NP_gen_pl { NP_gen_pl z='*' } : links { NP_gen_pl.z } : ngrams { -2 }



// ============ ГРУППА СУЩ. В ТВОР. ПАДЕЖЕ =============

cyk_rule NP_ins_f { N_ins_f }
cyk_rule NP_ins_f { AP_ins_f N_ins_f } : links { N_ins_f.<ATTRIBUTE>AP_ins_f } : ngrams { ngram2(AP_ins_f,N_ins_f) }
cyk_rule NP_ins_f { n1=N_ins_f n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_ins_m { N_ins_m }
cyk_rule NP_ins_m { AP_ins_m N_ins_m } : links { N_ins_m.<ATTRIBUTE>AP_ins_m } : ngrams { ngram2(AP_ins_m,N_ins_m) }
cyk_rule NP_ins_m { n1=N_ins_m n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_ins_n { N_ins_n }
cyk_rule NP_ins_n { AP_ins_n N_ins_n } : links { N_ins_n.<ATTRIBUTE>AP_ins_n } : ngrams { ngram2(AP_ins_n,N_ins_n) }
cyk_rule NP_ins_n { n1=N_ins_n n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_ins_pl { N_ins_pl }
cyk_rule NP_ins_pl { AP_ins_pl N_ins_pl } : links { N_ins_pl.<ATTRIBUTE>AP_ins_pl } : ngrams { ngram2(AP_ins_pl,N_ins_pl) }
cyk_rule NP_ins_pl { n1=N_ins_pl n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

// пользовался 2 двигателями
cyk_rule NP_ins_f { a=D n='NP_ins_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
cyk_rule NP_ins_m { a=D n='NP_ins_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
cyk_rule NP_ins_n { a=D n='NP_ins_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
cyk_rule NP_ins_pl { a=D n='NP_ins_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }


// восхищаюсь А.Н.Гончаровой
cyk_rule NP_ins_f { PERSON } : ngrams { -1 }
// наслаждаемся А.С.Пушкиным
cyk_rule NP_ins_m { PERSON } : ngrams { -1 }


// ---- Союзные конструкции для существительного ----

// NPJ_xxx_yyy это присоединяемая справа конструкция, начинающаяся с союза, запятой или (со штрафом) без оных
cyk_rule NPJ_ins { JP obj='NP_ins_*' } : links { JP.<OBJECT>obj }
cyk_rule NPJ_ins { 'NP_ins_*' } : ngrams { -1 }

// кошкой и собакой
// кошкой, собакой
cyk_rule NP_ins_f { n1=NP_ins_f n2=NPJ_ins } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_ins_m { n1=NP_ins_m n2=NPJ_ins } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_ins_n { n1=NP_ins_n n2=NPJ_ins } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_ins_pl { n1=NP_ins_pl n2=NPJ_ins } : links { n1.<RIGHT_LOGIC_ITEM>n2 }

// Союзные паттерны с двумя союзами:
// и кошкой, и собакой
cyk_rule NPJ1_ins_f { J2 obj=NP_ins_f } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_ins_m { J2 obj=NP_ins_m } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_ins_n { J2 obj=NP_ins_n } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_ins_pl { J2 obj=NP_ins_pl } : links { obj.<PREFIX_CONJUNCTION>J2 }

cyk_rule NPJ2_ins { JP2 obj='NP_ins_*' } : links { JP2.<OBJECT>obj }

// и хитрой лисичкой, и бесхитросным волком
cyk_rule NP_ins_f  { n1=NPJ1_ins_f n2=NPJ2_ins } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_ins_m  { n1=NPJ1_ins_m n2=NPJ2_ins } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_ins_n  { n1=NPJ1_ins_n n2=NPJ2_ins } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_ins_pl { n1=NPJ1_ins_pl n2=NPJ2_ins } : links { n1.<RIGHT_LOGIC_ITEM>n2 }

// ---- конец союзных паттернов для твор. падежа



cyk_rule S { NP_ins_f } : ngrams { -3 }
cyk_rule S { NP_ins_m } : ngrams { -3 }
cyk_rule S { NP_ins_n } : ngrams { -3 }
cyk_rule S { NP_ins_pl } : ngrams { -3 }

// связывание по умолчанию

cyk_rule NP_ins_f { z='*' NP_ins_f } : links { NP_ins_f.z } : ngrams { -2 }
cyk_rule NP_ins_f { NP_ins_f z='*' } : links { NP_ins_f.z } : ngrams { -2 }
cyk_rule NP_ins_m { z='*' NP_ins_m } : links { NP_ins_m.z } : ngrams { -2 }
cyk_rule NP_ins_m { NP_ins_m z='*' } : links { NP_ins_m.z } : ngrams { -2 }
cyk_rule NP_ins_n { z='*' NP_ins_n } : links { NP_ins_n.z } : ngrams { -2 }
cyk_rule NP_ins_n { NP_ins_n z='*' } : links { NP_ins_n.z } : ngrams { -2 }
cyk_rule NP_ins_pl { z='*' NP_ins_pl } : links { NP_ins_pl.z } : ngrams { -2 }
cyk_rule NP_ins_pl { NP_ins_pl z='*' } : links { NP_ins_pl.z } : ngrams { -2 }




// ============ ГРУППА СУЩ. В ВИН. ПАДЕЖЕ =============

cyk_rule NP_acc_f { N_acc_f }
cyk_rule NP_acc_f { AP_acc_f N_acc_f } : links { N_acc_f.<ATTRIBUTE>AP_acc_f } : ngrams { ngram2(AP_acc_f,N_acc_f) }
cyk_rule NP_acc_f { n1=N_acc_f n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_acc_m { N_acc_m }
cyk_rule NP_acc_m { AP_acc_m N_acc_m } : links { N_acc_m.<ATTRIBUTE>AP_acc_m } : ngrams { ngram2(AP_acc_m,N_acc_m) }
cyk_rule NP_acc_m { n1=N_acc_m n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_acc_n { N_acc_n }
cyk_rule NP_acc_n { AP_acc_n N_acc_n } : links { N_acc_n.<ATTRIBUTE>AP_acc_n } : ngrams { ngram2(AP_acc_n,N_acc_n) }
cyk_rule NP_acc_n { n1=N_acc_n n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_acc_pl { N_acc_pl }
cyk_rule NP_acc_pl { AP_acc_pl N_acc_pl } : links { N_acc_pl.<ATTRIBUTE>AP_acc_pl } : ngrams { ngram2(AP_acc_pl,N_acc_pl) }
cyk_rule NP_acc_pl { n1=N_acc_pl n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

// вижу 2 кошки
cyk_rule NP_acc_f { a=D n='NP_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
cyk_rule NP_acc_m { a=D n='NP_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
cyk_rule NP_acc_n { a=D n='NP_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
cyk_rule NP_acc_pl { a=D n='NP_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }

// знаю А.Н.Гончарову
cyk_rule NP_acc_f { PERSON } : ngrams { -1 }
// читаю А.С.Пушкина
cyk_rule NP_acc_m { PERSON } : ngrams { -1 }



// ---- Союзные конструкции для существительного ----

// NPJ_xxx_yyy это присоединяемая справа конструкция, начинающаяся с союза, запятой или (со штрафом) без оных
cyk_rule NPJ_acc { JP obj='NP_acc_*' } : links { JP.<OBJECT>obj }
cyk_rule NPJ_acc { 'NP_acc_*' } : ngrams { -1 }

// кошку и собаку
// кошку, собаку
cyk_rule NP_acc_f { n1=NP_acc_f n2=NPJ_acc } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_acc_m { n1=NP_acc_m n2=NPJ_acc } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_acc_n { n1=NP_acc_n n2=NPJ_acc } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_acc_pl { n1=NP_acc_pl n2=NPJ_acc } : links { n1.<RIGHT_LOGIC_ITEM>n2 }

// Союзные паттерны с двумя союзами:
// ???
cyk_rule NPJ1_acc_f { J2 obj=NP_acc_f } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_acc_m { J2 obj=NP_acc_m } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_acc_n { J2 obj=NP_acc_n } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_acc_pl { J2 obj=NP_acc_pl } : links { obj.<PREFIX_CONJUNCTION>J2 }

cyk_rule NPJ2_acc { JP2 obj='NP_acc_*' } : links { JP2.<OBJECT>obj }

// и хитрую лисичку, и бесхитросного волка
cyk_rule NP_acc_f  { n1=NPJ1_acc_f n2=NPJ2_acc } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_acc_m  { n1=NPJ1_acc_m n2=NPJ2_acc } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_acc_n  { n1=NPJ1_acc_n n2=NPJ2_acc } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_acc_pl { n1=NPJ1_acc_pl n2=NPJ2_acc } : links { n1.<RIGHT_LOGIC_ITEM>n2 }

// ---- конец союзных паттернов для вин. падежа





cyk_rule S { NP_acc_f } : ngrams { -3 }
cyk_rule S { NP_acc_m } : ngrams { -3 }
cyk_rule S { NP_acc_n } : ngrams { -3 }
cyk_rule S { NP_acc_pl } : ngrams { -3 }

// связывание по умолчанию

cyk_rule NP_acc_f { z='*' NP_acc_f } : links { NP_acc_f.z } : ngrams { -2 }
cyk_rule NP_acc_f { NP_acc_f z='*' } : links { NP_acc_f.z } : ngrams { -2 }
cyk_rule NP_acc_m { z='*' NP_acc_m } : links { NP_acc_m.z } : ngrams { -2 }
cyk_rule NP_acc_m { NP_acc_m z='*' } : links { NP_acc_m.z } : ngrams { -2 }
cyk_rule NP_acc_n { z='*' NP_acc_n } : links { NP_acc_n.z } : ngrams { -2 }
cyk_rule NP_acc_n { NP_acc_n z='*' } : links { NP_acc_n.z } : ngrams { -2 }
cyk_rule NP_acc_pl { z='*' NP_acc_pl } : links { NP_acc_pl.z } : ngrams { -2 }
cyk_rule NP_acc_pl { NP_acc_pl z='*' } : links { NP_acc_pl.z } : ngrams { -2 }



// ============ ГРУППА СУЩ. В ДАТ. ПАДЕЖЕ =============

cyk_rule NP_dat_f { N_dat_f }
cyk_rule NP_dat_f { AP_dat_f N_dat_f } : links { N_dat_f.<ATTRIBUTE>AP_dat_f } : ngrams { ngram2(AP_dat_f,N_dat_f) }
cyk_rule NP_dat_f { n1=N_dat_f n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_dat_m { N_dat_m }
cyk_rule NP_dat_m { AP_dat_m N_dat_m } : links { N_dat_m.<ATTRIBUTE>AP_dat_m } : ngrams { ngram2(AP_dat_m,N_dat_m) }
cyk_rule NP_dat_m { n1=N_dat_m n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_dat_n { N_dat_n }
cyk_rule NP_dat_n { AP_dat_n N_dat_n } : links { N_dat_n.<ATTRIBUTE>AP_dat_n } : ngrams { ngram2(AP_dat_n,N_dat_n) }
cyk_rule NP_dat_n { n1=N_dat_n n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_dat_pl { N_dat_pl }
cyk_rule NP_dat_pl { AP_dat_pl N_dat_pl } : links { N_dat_pl.<ATTRIBUTE>AP_dat_pl } : ngrams { ngram2(AP_dat_pl,N_dat_pl) }
cyk_rule NP_dat_pl { n1=N_dat_pl n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }


// отдаю 3 соседям
cyk_rule NP_dat_f { a=D n='NP_dat_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
cyk_rule NP_dat_m { a=D n='NP_dat_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
cyk_rule NP_dat_n { a=D n='NP_dat_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
cyk_rule NP_dat_pl { a=D n='NP_dat_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }


// передам А.Н.Гончаровой
cyk_rule NP_dat_f { PERSON } : ngrams { -1 }
// оставлю А.С.Пушкину
cyk_rule NP_dat_m { PERSON } : ngrams { -1 }



// ---- Союзные конструкции для существительного ----

// NPJ_xxx_yyy это присоединяемая справа конструкция, начинающаяся с союза, запятой или (со штрафом) без оных
cyk_rule NPJ_dat { JP obj='NP_dat_*' } : links { JP.<OBJECT>obj }
cyk_rule NPJ_dat { 'NP_dat_*' } : ngrams { -1 }

// к бабушке и дедушке
// к бабушке, дедушке
cyk_rule NP_dat_f { n1=NP_dat_f n2=NPJ_dat } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_dat_m { n1=NP_dat_m n2=NPJ_dat } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_dat_n { n1=NP_dat_n n2=NPJ_dat } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_dat_pl { n1=NP_dat_pl n2=NPJ_dat } : links { n1.<RIGHT_LOGIC_ITEM>n2 }

// Союзные паттерны с двумя союзами:
// ??? todo пример
cyk_rule NPJ1_dat_f { J2 obj=NP_dat_f } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_dat_m { J2 obj=NP_dat_m } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_dat_n { J2 obj=NP_dat_n } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_dat_pl { J2 obj=NP_dat_pl } : links { obj.<PREFIX_CONJUNCTION>J2 }

cyk_rule NPJ2_dat { JP2 obj='NP_dat_*' } : links { JP2.<OBJECT>obj }

cyk_rule NP_dat_f  { n1=NPJ1_dat_f n2=NPJ2_dat } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_dat_m  { n1=NPJ1_dat_m n2=NPJ2_dat } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_dat_n  { n1=NPJ1_dat_n n2=NPJ2_dat } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_dat_pl { n1=NPJ1_dat_pl n2=NPJ2_dat } : links { n1.<RIGHT_LOGIC_ITEM>n2 }

// ---- конец союзных паттернов для дат. падежа






cyk_rule S { NP_dat_f } : ngrams { -3 }
cyk_rule S { NP_dat_m } : ngrams { -3 }
cyk_rule S { NP_dat_n } : ngrams { -3 }
cyk_rule S { NP_dat_pl } : ngrams { -3 }

// связывание по умолчанию

cyk_rule NP_dat_f { z='*' NP_dat_f } : links { NP_dat_f.z } : ngrams { -2 }
cyk_rule NP_dat_f { NP_dat_f z='*' } : links { NP_dat_f.z } : ngrams { -2 }
cyk_rule NP_dat_m { z='*' NP_dat_m } : links { NP_dat_m.z } : ngrams { -2 }
cyk_rule NP_dat_m { NP_dat_m z='*' } : links { NP_dat_m.z } : ngrams { -2 }
cyk_rule NP_dat_n { z='*' NP_dat_n } : links { NP_dat_n.z } : ngrams { -2 }
cyk_rule NP_dat_n { NP_dat_n z='*' } : links { NP_dat_n.z } : ngrams { -2 }
cyk_rule NP_dat_pl { z='*' NP_dat_pl } : links { NP_dat_pl.z } : ngrams { -2 }
cyk_rule NP_dat_pl { NP_dat_pl z='*' } : links { NP_dat_pl.z } : ngrams { -2 }


// ============ ГРУППА СУЩ. В ПРЕДЛ. ПАДЕЖЕ =============

cyk_rule NP_prep_f { N_prep_f }
cyk_rule NP_prep_f { AP_prep_f N_prep_f } : links { N_prep_f.<ATTRIBUTE>AP_prep_f } : ngrams { ngram2(AP_prep_f,N_prep_f) }
cyk_rule NP_prep_f { n1=N_prep_f n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_prep_m { N_prep_m }
cyk_rule NP_prep_m { AP_prep_m N_prep_m } : links { N_prep_m.<ATTRIBUTE>AP_prep_m } : ngrams { ngram2(AP_prep_m,N_prep_m) }
cyk_rule NP_prep_m { n1=N_prep_m n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_prep_n { N_prep_n }
cyk_rule NP_prep_n { AP_prep_n N_prep_n } : links { N_prep_n.<ATTRIBUTE>AP_prep_n } : ngrams { ngram2(AP_prep_n,N_prep_n) }
cyk_rule NP_prep_n { n1=N_prep_n n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

cyk_rule NP_prep_pl { N_prep_pl }
cyk_rule NP_prep_pl { AP_prep_pl N_prep_pl } : links { N_prep_pl.<ATTRIBUTE>AP_prep_pl } : ngrams { ngram2(AP_prep_pl,N_prep_pl) }
cyk_rule NP_prep_pl { n1=N_prep_pl n2=GenOBJ } : links { n1.<RIGHT_GENITIVE_OBJECT>n2 } : ngrams { ngram2(n1,n2) }

// помню о 2 помощниках
cyk_rule NP_prep_f { a=D n='NP_prep_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
cyk_rule NP_prep_m { a=D n='NP_prep_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
cyk_rule NP_prep_n { a=D n='NP_prep_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }
cyk_rule NP_prep_pl { a=D n='NP_prep_*' } : links { n.<ATTRIBUTE>a } : ngrams { -1 }

// думаю о А.Н.Гончаровй
cyk_rule NP_prep_f { PERSON } : ngrams { -1 }
// знаю о А.С.Пушкине
cyk_rule NP_prep_m { PERSON } : ngrams { -1 }



// ---- Союзные конструкции для существительного ----

// NPJ_xxx_yyy это присоединяемая справа конструкция, начинающаяся с союза, запятой или (со штрафом) без оных
cyk_rule NPJ_prep { JP obj='NP_prep_*' } : links { JP.<OBJECT>obj }
cyk_rule NPJ_prep { 'NP_prep_*' } : ngrams { -1 }

// о кошке и собаке
// о кошке, собаке
cyk_rule NP_prep_f { n1=NP_prep_f n2=NPJ_prep } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_prep_m { n1=NP_prep_m n2=NPJ_prep } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_prep_n { n1=NP_prep_n n2=NPJ_prep } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_prep_pl { n1=NP_prep_pl n2=NPJ_prep } : links { n1.<RIGHT_LOGIC_ITEM>n2 }

// Союзные паттерны с двумя союзами:
// ??? todo пример
cyk_rule NPJ1_prep_f { J2 obj=NP_prep_f } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_prep_m { J2 obj=NP_prep_m } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_prep_n { J2 obj=NP_prep_n } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule NPJ1_prep_pl { J2 obj=NP_prep_pl } : links { obj.<PREFIX_CONJUNCTION>J2 }

cyk_rule NPJ2_prep { JP2 obj='NP_prep_*' } : links { JP2.<OBJECT>obj }

// о хитрой лисичке, и бесхитросном волке
cyk_rule NP_prep_f  { n1=NPJ1_prep_f n2=NPJ2_prep } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_prep_m  { n1=NPJ1_prep_m n2=NPJ2_prep } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_prep_n  { n1=NPJ1_prep_n n2=NPJ2_prep } : links { n1.<RIGHT_LOGIC_ITEM>n2 }
cyk_rule NP_prep_pl { n1=NPJ1_prep_pl n2=NPJ2_prep } : links { n1.<RIGHT_LOGIC_ITEM>n2 }

// ---- конец союзных паттернов для предл. падежа



cyk_rule S { NP_prep_f } : ngrams { -3 }
cyk_rule S { NP_prep_m } : ngrams { -3 }
cyk_rule S { NP_prep_n } : ngrams { -3 }
cyk_rule S { NP_prep_pl } : ngrams { -3 }

// связывание по умолчанию

cyk_rule NP_prep_f { z='*' NP_prep_f } : links { NP_prep_f.z } : ngrams { -2 }
cyk_rule NP_prep_f { NP_prep_f z='*' } : links { NP_prep_f.z } : ngrams { -2 }
cyk_rule NP_prep_m { z='*' NP_prep_m } : links { NP_prep_m.z } : ngrams { -2 }
cyk_rule NP_prep_m { NP_prep_m z='*' } : links { NP_prep_m.z } : ngrams { -2 }
cyk_rule NP_prep_n { z='*' NP_prep_n } : links { NP_prep_n.z } : ngrams { -2 }
cyk_rule NP_prep_n { NP_prep_n z='*' } : links { NP_prep_n.z } : ngrams { -2 }
cyk_rule NP_prep_pl { z='*' NP_prep_pl } : links { NP_prep_pl.z } : ngrams { -2 }
cyk_rule NP_prep_pl { NP_prep_pl z='*' } : links { NP_prep_pl.z } : ngrams { -2 }



// ############################
// ГРУППА МЕСТОИМЕНИЯ
// ############################

// TODO: тут надо обрабатывать паттерны типа "Я С ТОБОЙ"

// местоименная группа в именительном падеже
cyk_rule PRN_nom { z='*' PRN_nom } : links { PRN_nom.z } : ngrams { -2 }
cyk_rule PRN_nom { PRN_nom z='*' } : links { PRN_nom.z } : ngrams { -2 }

// местоименная группа в родительном падеже
cyk_rule PRN_gen { z='*' PRN_gen } : links { PRN_gen.z } : ngrams { -2 }
cyk_rule PRN_gen { PRN_gen z='*' } : links { PRN_gen.z } : ngrams { -2 }

// местоименная группа в творительном падеже
cyk_rule PRN_ins { z='*' PRN_ins } : links { PRN_ins.z } : ngrams { -2 }
cyk_rule PRN_ins { PRN_ins z='*' } : links { PRN_ins.z } : ngrams { -2 }

// местоименная группа в винительном падеже
cyk_rule PRN_acc { z='*' PRN_acc } : links { PRN_acc.z } : ngrams { -2 }
cyk_rule PRN_acc { PRN_acc z='*' } : links { PRN_acc.z } : ngrams { -2 }

// местоименная группа в дательном падеже
cyk_rule PRN_dat { z='*' PRN_dat } : links { PRN_dat.z } : ngrams { -2 }
cyk_rule PRN_dat { PRN_dat z='*' } : links { PRN_dat.z } : ngrams { -2 }

// местоименная группа в предложном падеже
cyk_rule PRN_prep { z='*' PRN_prep } : links { PRN_prep.z } : ngrams { -2 }
cyk_rule PRN_prep { PRN_prep z='*' } : links { PRN_prep.z } : ngrams { -2 }


// ####################################
// ПРЕДЛОЖНЫЙ ПАТТЕРН
// ####################################

cyk_rule PN { p=P_gen obj='NP_gen_*' } : links { p.<OBJECT>obj }
cyk_rule PN { p=P_ins obj='NP_ins_*' } : links { p.<OBJECT>obj }
cyk_rule PN { p=P_acc obj='NP_acc_*' } : links { p.<OBJECT>obj }
cyk_rule PN { p=P_dat obj='NP_dat_*' } : links { p.<OBJECT>obj }
cyk_rule PN { p=P_prep obj='NP_prep_*' } : links { p.<OBJECT>obj }


// Союзные конструкции:
// Для мамы и для папы
cyk_rule PNJ { JP PN } : links { JP.<OBJECT>PN }
cyk_rule PN { PN PNJ } : links { PN.<RIGHT_LOGIC_ITEM>PNJ }




cyk_rule S { PN } : ngrams { -5 }

// Существительные с предложным паттерном

cyk_rule NP_nom_f { n=NP_nom_f PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_nom_m { n=NP_nom_m PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_nom_n { n=NP_nom_n PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_nom_pl { n=NP_nom_pl PN } : links { n.<PREPOS_ADJUNCT>PN }

cyk_rule NP_gen_f { n=NP_gen_f PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_gen_m { n=NP_gen_m PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_gen_n { n=NP_gen_n PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_gen_pl { n=NP_gen_pl PN } : links { n.<PREPOS_ADJUNCT>PN }

cyk_rule NP_ins_f { n=NP_ins_f PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_ins_m { n=NP_ins_m PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_ins_n { n=NP_ins_n PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_ins_pl { n=NP_ins_pl PN } : links { n.<PREPOS_ADJUNCT>PN }

cyk_rule NP_acc_f { n=NP_acc_f PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_acc_m { n=NP_acc_m PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_acc_n { n=NP_acc_n PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_acc_pl { n=NP_acc_pl PN } : links { n.<PREPOS_ADJUNCT>PN }

cyk_rule NP_dat_f { n=NP_dat_f PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_dat_m { n=NP_dat_m PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_dat_n { n=NP_dat_n PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_dat_pl { n=NP_dat_pl PN } : links { n.<PREPOS_ADJUNCT>PN }

cyk_rule NP_prep_f { n=NP_prep_f PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_prep_m { n=NP_prep_m PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_prep_n { n=NP_prep_n PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule NP_prep_pl { n=NP_prep_pl PN } : links { n.<PREPOS_ADJUNCT>PN }

cyk_rule PRN_nom { n=PRN_nom PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule PRN_gen { n=PRN_gen PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule PRN_ins { n=PRN_ins PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule PRN_acc { n=PRN_acc PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule PRN_dat { n=PRN_dat PN } : links { n.<PREPOS_ADJUNCT>PN }
cyk_rule PRN_prep { n=PRN_prep PN } : links { n.<PREPOS_ADJUNCT>PN }



// ===================
// ПОДЛЕЖАЩЕЕ
// ===================

// существительные в им.п. в роли подлежащего
cyk_rule SBJ_f { NP_nom_f }
cyk_rule SBJ_m { NP_nom_m }
cyk_rule SBJ_n { NP_nom_n }
cyk_rule SBJ_pl { NP_nom_pl }

// местоимения в им.п. в роли подлежащего
cyk_rule SBJ_f { PRN_nom_f }
cyk_rule SBJ_m { PRN_nom_m }
cyk_rule SBJ_n { PRN_nom_n }
cyk_rule SBJ_pl { PRN_nom_pl }

// Иногда подлежащим может быть одно прилагательное:
// Первый оказался мальчиком.
cyk_rule SBJ_f { AP_nom_f } : ngrams { -1 }
cyk_rule SBJ_m { AP_nom_m } : ngrams { -1 }
cyk_rule SBJ_n { AP_nom_n } : ngrams { -1 }
cyk_rule SBJ_pl { AP_nom_pl } : ngrams { -1 }

cyk_rule SBJ_1_sg { PRN_nom_1_sg }
cyk_rule SBJ_2_sg { PRN_nom_2_sg }
cyk_rule SBJ_3_sg { PRN_nom_3_sg }

cyk_rule SBJ_1_pl { PRN_nom_1_pl }
cyk_rule SBJ_2_pl { PRN_nom_2_pl }
cyk_rule SBJ_3_pl { PRN_nom_3_pl }

cyk_rule SBJ_3_sg { NP_nom_f }
cyk_rule SBJ_3_sg { NP_nom_m }
cyk_rule SBJ_3_sg { NP_nom_n }
cyk_rule SBJ_3_pl { NP_nom_pl }

/*
// TODO: убрать недифференцированные подлежащие
cyk_rule SBJ { SBJ_f } : ngrams { -1 }
cyk_rule SBJ { SBJ_m } : ngrams { -1 }
cyk_rule SBJ { SBJ_n } : ngrams { -1 }
cyk_rule SBJ { SBJ_pl } : ngrams { -1 }

cyk_rule SBJ { SBJ_1_sg } : ngrams { -1 }
cyk_rule SBJ { SBJ_2_sg } : ngrams { -1 }
cyk_rule SBJ { SBJ_3_sg } : ngrams { -1 }

cyk_rule SBJ { SBJ_1_pl } : ngrams { -1 }
cyk_rule SBJ { SBJ_2_pl } : ngrams { -1 }
cyk_rule SBJ { SBJ_3_pl } : ngrams { -1 }
*/

// Число само себе может быть подлежащим:
cyk_rule SBJ_f { D } : ngrams { -3 }
cyk_rule SBJ_m { D } : ngrams { -3 }
cyk_rule SBJ_n { D } : ngrams { -3 }
cyk_rule SBJ_pl { D } : ngrams { -4 }




// ################################################################
// ПРЯМОЕ ДОПОЛНЕНИЕ
// существительное, местоимение, прилагательное в косвенных падежах
// ################################################################

cyk_rule OBJ { 'NP_gen_*' }
cyk_rule OBJ { 'NP_ins_*' }
cyk_rule OBJ { 'NP_acc_*' }
cyk_rule OBJ { 'NP_dat_*' }
cyk_rule OBJ { 'NP_prep_*' }

cyk_rule OBJ { PRN_gen }
cyk_rule OBJ { PRN_ins }
cyk_rule OBJ { PRN_acc }
cyk_rule OBJ { PRN_dat }
cyk_rule OBJ { PRN_prep }

cyk_rule OBJ { 'AP_gen_*' } : ngrams { -1 }
cyk_rule OBJ { 'AP_ins_*' } : ngrams { -1 }
cyk_rule OBJ { 'AP_acc_*' } : ngrams { -1 }
cyk_rule OBJ { 'AP_dat_*' } : ngrams { -1 }
cyk_rule OBJ { 'AP_prep_*' } : ngrams { -1 }


// Число само себе может быть прямым дополнение:
// "Вижу 15"
cyk_rule OBJ { D } : ngrams { -3 }


// ################################################################
// ДОПОЛНЕНИЕ В РОДИТЕЛЬНОМ ПАДЕЖЕ ДЛЯ СУЩЕСТВИТЕЛЬНОГО
// ################################################################

cyk_rule GenOBJ { 'NP_gen_*' }
cyk_rule GenOBJ { PRN_gen }
cyk_rule GenOBJ { 'AP_gen_*' } : ngrams { -1 }


// #################################
// Группа инфинитива
// #################################

// Не очень много пел
cyk_rule Iit { Y Iit } : links { Iit.<ATTRIBUTE>Y } : ngrams { ngram2(Y,Iit) }

// Пел слишком много
cyk_rule Iit { Iit Y } : links { Iit.<ATTRIBUTE>Y } : ngrams { ngram2(Y,Iit) }

// Не очень много сделал
cyk_rule It { Y It } : links { It.<ATTRIBUTE>Y } : ngrams { ngram2(Y,It) }

// делал слишком много
cyk_rule It { It Y } : links { It.<ATTRIBUTE>Y } : ngrams { ngram2(Y,It) }

// начать исправлять ошибки
cyk_rule Im { Y Im } : links { Im.<ATTRIBUTE>Y } : ngrams { ngram2(Y,Im) }

// Вижу сны
cyk_rule It { It OBJ } : links { It.<OBJECT>OBJ } : ngrams { ngram2(It,OBJ) }

// Сны вижу
cyk_rule It { OBJ It } : links { It.<OBJECT>OBJ } : ngrams { -1 ngram2(It,OBJ) }

// ---------------------------
// с косвенным дополнением:
// ---------------------------

// любоваться на луну
cyk_rule Iit { Iit PN } : links { Iit.<PREPOS_ADJUNCT>PN }

// на луну любоваться
cyk_rule Iit { PN Iit } : links { Iit.<PREPOS_ADJUNCT>PN } : ngrams { -1 }

// посмотреть на луну
cyk_rule It { It PN } : links { It.<PREPOS_ADJUNCT>PN }

// на луну посмотреть
cyk_rule It { PN It } : links { It.<PREPOS_ADJUNCT>PN } : ngrams { -1 }


// -----------------------------------------------------------
// Группа инфинитива для связывания с модальными нетерминалами
// -----------------------------------------------------------
cyk_rule IP { Iit }
cyk_rule IP { It }

// начинать работать
cyk_rule IP { Im IP } : links { Im.<INFINITIVE>IP }


// ---- Союзные конструкции для инфинитива ----

// IPJ это присоединяемая справа конструкция, начинающаяся с союза, запятой или (со штрафом) без оных
cyk_rule IPJ { JP IP } : links { JP.<OBJECT>IP }
cyk_rule IPJ { IP } : ngrams { -1 }

// прыгать и скакать
// прыгать, скакать
cyk_rule IP { i1=IP i2=IPJ } : links { i1.<RIGHT_LOGIC_ITEM>i2 }

// Союзные паттерны с двумя союзами:
// и петь, и плясать
cyk_rule IPJ1 { J2 IP } : links { IP.<PREFIX_CONJUNCTION>J2 }
cyk_rule IPJ2 { JP2 IP } : links { JP2.<OBJECT>IP }

// и петь песни, и читать стихи
cyk_rule IP  { i1=IPJ1 i2=IPJ2 } : links { i1.<RIGHT_LOGIC_ITEM>i2 }

// ---- конец союзных паттернов для инфинитива








// ----------------------------
// с деепричастным оборотом
// ----------------------------

// начал работать, включив приборы
cyk_rule IP { IP YVP } : links { IP.<ADV_PARTICIPLE>YVP }

// Выключив свет, уснуть
cyk_rule IP { YVP IP } : links { IP.<ADV_PARTICIPLE>YVP } : ngrams { -1 }

// --- связывание по умолчанию
cyk_rule Iit { Iit z='*' } : links { Iit.z } : ngrams { -2 }
cyk_rule Iit { z='*' Iit } : links { Iit.z } : ngrams { -2 }
cyk_rule It { It z='*' } : links { It.z } : ngrams { -2 }
cyk_rule It { z='*' It } : links { It.z } : ngrams { -2 }


// --- разбор конструкций с инфинитивом в корне
cyk_rule S { IP } : ngrams { -1 }


// ##################################
// Группа деепричастия
// ##################################

// Сильно обгорев
cyk_rule YVit { Y YVit } : links { YVit.<ATTRIBUTE>Y } : ngrams { ngram2(Y,YVit) }

// Обгорев очень сильно
cyk_rule YVit { YVit Y } : links { YVit.<ATTRIBUTE>Y } : ngrams { ngram2(Y,YVit) }

// Много работая
cyk_rule YVt { Y YVt } : links { YVt.<ATTRIBUTE>Y } : ngrams { ngram2(Y,YVt) }

// работая слишком много
cyk_rule YVt { YVt Y } : links { YVt.<ATTRIBUTE>Y } : ngrams { ngram2(Y,YVt) }

// Сразу начиная ворчать
cyk_rule YVm { Y YVm } : links { YVm.<ATTRIBUTE>Y } : ngrams { ngram2(Y,YVm) }


// работая дворником
cyk_rule YVt { YVt OBJ } : links { YVt.<OBJECT>OBJ } : ngrams { ngram2(YVt,OBJ) }

// дворником работая
cyk_rule YVt { OBJ YVt } : links { YVt.<OBJECT>OBJ } : ngrams { ngram2(YVt,OBJ) } : ngrams { -1 }



// с косвенным дополнением:
// обгорев на солнце
cyk_rule YVit { YVit PN } : links { YVit.<PREPOS_ADJUNCT>PN }

// обгорев на солнце
cyk_rule YVit { PN YVit } : links { YVit.<PREPOS_ADJUNCT>PN } : ngrams { -1 }

// работая с детьми
cyk_rule YVt { YVt PN } : links { YVt.<PREPOS_ADJUNCT>PN }

// с детьми работая
cyk_rule YVt { PN YVt } : links { YVt.<PREPOS_ADJUNCT>PN } : ngrams { -1 }

// ---------------------------------------------------------
// деепричастный оборот, преимущественно с отбивкой запятой
// ---------------------------------------------------------

// Съев сметану, кот уснул.
cyk_rule YVP1 { YVt COMMA } : links { YVt.<PUNCTUATION>COMMA } 

// Побегав за мышками, кот уснул
cyk_rule YVP1 { YVit COMMA } : links { YVit.<PUNCTUATION>COMMA } 

cyk_rule YVPm { YVm IP } : links { YVm.<INFINITIVE>IP } : ngrams { ngram2(YVm,IP) }

// Начав бегать, кот уснул
cyk_rule YVP1 { YVPm COMMA } : links { YVPm.<PUNCTUATION>COMMA } 

// Кот уснул, начав бегать
cyk_rule YVP2 { COMMA YVPm } : links { YVPm.<PUNCTUATION>COMMA }

// Кот уснул, съев сметану.
cyk_rule YVP2 { COMMA YVt } : links { YVt.<PUNCTUATION>COMMA } 

// Кот уснул, побегав за мышками
cyk_rule YVP2 { COMMA YVit } : links { YVit.<PUNCTUATION>COMMA } 

// Кот, съев сметану, уснул.
cyk_rule YVP2 { YVP2 COMMA } : links { YVP2.<PUNCTUATION>COMMA } 


cyk_rule YVP { YVit } : ngrams { -1 } // штрафуем за отсутствие запятой
cyk_rule YVP { YVt } : ngrams { -1 }
cyk_rule YVP { YVm } : ngrams { -1 }

cyk_rule YVP { YVP1 }
cyk_rule YVP { YVP2 }


// Союзные конструкции для деепричастий:
// дети радовались, смеясь и прыгая
cyk_rule YVPJ { JP YVP } : links { JP.<OBJECT>YVP }
cyk_rule YVP { YVP YVPJ } : links { YVP.<RIGHT_LOGIC_ITEM>YVPJ }

cyk_rule YVPJ1 { J2 obj=YVP } : links { obj.<PREFIX_CONJUNCTION>J2 }
cyk_rule YVPJ2 { JP2 obj=YVP } : links { JP2.<OBJECT>obj }

// и громко смеясь, и хлопая в ладоши
cyk_rule YVP { y1=YVPJ1 y2=YVPJ2 } : links { y1.<RIGHT_LOGIC_ITEM>y2 }


// --- связывание по умолчанию
cyk_rule YVit { YVit z='*' } : links { YVit.z } : ngrams { -2 }
cyk_rule YVit { z='*' YVit } : links { YVit.z } : ngrams { -2 }
cyk_rule YVt { YVt z='*' } : links { YVt.z } : ngrams { -2 }
cyk_rule YVt { z='*' YVt } : links { YVt.z } : ngrams { -2 }

// --- разбор конструкций с деепричастием в корне
cyk_rule S { YVP } : ngrams { -5 }




// ==============================
// --- Глагольная группа
// ==============================

// Не очень много пел
//          ^^^^^^^^^^
cyk_rule Vit_1_sg { Y v=Vit_1_sg } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vit_2_sg { Y v=Vit_2_sg } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vit_3_sg { Y v=Vit_3_sg } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }

cyk_rule Vit_1_pl { Y v=Vit_1_pl } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vit_2_pl { Y v=Vit_2_pl } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vit_3_pl { Y v=Vit_3_pl } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }

cyk_rule Vit_f { Y v=Vit_f } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vit_m { Y v=Vit_m } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vit_n { Y v=Vit_n } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vit_pl { Y v=Vit_pl } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }

// Не очень много сделал
//          ^^^^^^^^^^^^
cyk_rule Vt_1_sg { Y v=Vt_1_sg } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vt_2_sg { Y v=Vt_2_sg } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vt_3_sg { Y v=Vt_3_sg } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }

cyk_rule Vt_1_pl { Y v=Vt_1_pl } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vt_2_pl { Y v=Vt_2_pl } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vt_3_pl { Y v=Vt_3_pl } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }

cyk_rule Vt_f { Y v=Vt_f } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vt_m { Y v=Vt_m } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vt_n { Y v=Vt_n } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vt_pl { Y v=Vt_pl } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }


// наречие может быть в постфиксной позиции:
// Я спал слишком много
//   ^^^^^^^^^^^^^^^^^^
cyk_rule Vt_1_sg { v=Vt_1_sg Y } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vt_2_sg { v=Vt_2_sg Y } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vt_3_sg { v=Vt_3_sg Y } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }

cyk_rule Vt_1_pl { v=Vt_1_pl Y } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vt_2_pl { v=Vt_2_pl Y } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vt_3_pl { v=Vt_3_pl Y } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }

cyk_rule Vt_f { v=Vt_f Y } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vt_m { v=Vt_m Y } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vt_n { v=Vt_n Y } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }
cyk_rule Vt_pl { v=Vt_pl Y } : links { v.<ATTRIBUTE>Y } : ngrams { ngram2(Y,v) }

// с косвенным дополнением:

// Любуюсь на Луну
cyk_rule Vit_1_sg { v=Vit_1_sg PN } : links { v.<PREPOS_ADJUNCT>PN }
cyk_rule Vit_2_sg { v=Vit_2_sg PN } : links { v.<PREPOS_ADJUNCT>PN }
cyk_rule Vit_3_sg { v=Vit_3_sg PN } : links { v.<PREPOS_ADJUNCT>PN }

cyk_rule Vit_1_pl { v=Vit_1_pl PN } : links { v.<PREPOS_ADJUNCT>PN }
cyk_rule Vit_2_pl { v=Vit_2_pl PN } : links { v.<PREPOS_ADJUNCT>PN }
cyk_rule Vit_3_pl { v=Vit_3_pl PN } : links { v.<PREPOS_ADJUNCT>PN }

cyk_rule Vit_f { v=Vit_f PN } : links { v.<PREPOS_ADJUNCT>PN }
cyk_rule Vit_m { v=Vit_m PN } : links { v.<PREPOS_ADJUNCT>PN }
cyk_rule Vit_n { v=Vit_n PN } : links { v.<PREPOS_ADJUNCT>PN }
cyk_rule Vit_pl { v=Vit_pl PN } : links { v.<PREPOS_ADJUNCT>PN }

// На луну любуюсь
cyk_rule Vit_1_sg { PN v=Vit_1_sg } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }
cyk_rule Vit_2_sg { PN v=Vit_2_sg } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }
cyk_rule Vit_3_sg { PN v=Vit_3_sg } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }

cyk_rule Vit_1_pl { PN v=Vit_1_pl } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }
cyk_rule Vit_2_pl { PN v=Vit_2_pl } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }
cyk_rule Vit_3_pl { PN v=Vit_3_pl } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }

cyk_rule Vit_f { PN v=Vit_f } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }
cyk_rule Vit_m { PN v=Vit_m } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }
cyk_rule Vit_n { PN v=Vit_n } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }
cyk_rule Vit_pl { PN v=Vit_pl } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }

// Смотрю на Луну
cyk_rule Vt_1_sg { v=Vt_1_sg PN } : links { v.<PREPOS_ADJUNCT>PN }
cyk_rule Vt_2_sg { v=Vt_2_sg PN } : links { v.<PREPOS_ADJUNCT>PN }
cyk_rule Vt_3_sg { v=Vt_3_sg PN } : links { v.<PREPOS_ADJUNCT>PN }

cyk_rule Vt_1_pl { v=Vt_1_pl PN } : links { v.<PREPOS_ADJUNCT>PN }
cyk_rule Vt_2_pl { v=Vt_2_pl PN } : links { v.<PREPOS_ADJUNCT>PN }
cyk_rule Vt_3_pl { v=Vt_3_pl PN } : links { v.<PREPOS_ADJUNCT>PN }

cyk_rule Vt_f { v=Vt_f PN } : links { v.<PREPOS_ADJUNCT>PN }
cyk_rule Vt_m { v=Vt_m PN } : links { v.<PREPOS_ADJUNCT>PN }
cyk_rule Vt_n { v=Vt_n PN } : links { v.<PREPOS_ADJUNCT>PN }
cyk_rule Vt_pl { v=Vt_pl PN } : links { v.<PREPOS_ADJUNCT>PN }

// На Луну смотрю
cyk_rule Vt_1_sg { PN v=Vt_1_sg } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }
cyk_rule Vt_2_sg { PN v=Vt_2_sg } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }
cyk_rule Vt_3_sg { PN v=Vt_3_sg } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }

cyk_rule Vt_1_pl { PN v=Vt_1_pl } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }
cyk_rule Vt_2_pl { PN v=Vt_2_pl } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }
cyk_rule Vt_3_pl { PN v=Vt_3_pl } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }

cyk_rule Vt_f { PN v=Vt_f } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }
cyk_rule Vt_m { PN v=Vt_m } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }
cyk_rule Vt_n { PN v=Vt_n } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }
cyk_rule Vt_pl { PN v=Vt_pl } : links { v.<PREPOS_ADJUNCT>PN } : ngrams { -1 }


// --- связывание по умолчанию
cyk_rule Vit_1_sg { v=Vit_1_sg z='*' } : links { v.z } : ngrams { -2 }
cyk_rule Vit_2_sg { v=Vit_2_sg z='*' } : links { v.z } : ngrams { -2 }
cyk_rule Vit_3_sg { v=Vit_3_sg z='*' } : links { v.z } : ngrams { -2 }

cyk_rule Vit_1_pl { v=Vit_1_pl z='*' } : links { v.z } : ngrams { -2 }
cyk_rule Vit_2_pl { v=Vit_2_pl z='*' } : links { v.z } : ngrams { -2 }
cyk_rule Vit_3_pl { v=Vit_3_pl z='*' } : links { v.z } : ngrams { -2 }

cyk_rule Vit_f { v=Vit_f z='*' } : links { v.z } : ngrams { -2 }
cyk_rule Vit_m { v=Vit_m z='*' } : links { v.z } : ngrams { -2 }
cyk_rule Vit_n { v=Vit_n z='*' } : links { v.z } : ngrams { -2 }
cyk_rule Vit_pl { v=Vit_pl z='*' } : links { v.z } : ngrams { -2 }

cyk_rule Vit_1_sg { z='*' v=Vit_1_sg } : links { v.z } : ngrams { -2 }
cyk_rule Vit_2_sg { z='*' v=Vit_2_sg } : links { v.z } : ngrams { -2 }
cyk_rule Vit_3_sg { z='*' v=Vit_3_sg } : links { v.z } : ngrams { -2 }

cyk_rule Vit_1_pl { z='*' v=Vit_1_pl } : links { v.z } : ngrams { -2 }
cyk_rule Vit_2_pl { z='*' v=Vit_2_pl } : links { v.z } : ngrams { -2 }
cyk_rule Vit_3_pl { z='*' v=Vit_3_pl } : links { v.z } : ngrams { -2 }

cyk_rule Vit_f { z='*' v=Vit_f } : links { v.z } : ngrams { -2 }
cyk_rule Vit_m { z='*' v=Vit_m } : links { v.z } : ngrams { -2 }
cyk_rule Vit_n { z='*' v=Vit_n } : links { v.z } : ngrams { -2 }
cyk_rule Vit_pl { z='*' v=Vit_pl } : links { v.z } : ngrams { -2 }

cyk_rule Vt_1_sg { v=Vt_1_sg z='*' } : links { v.z } : ngrams { -2 }
cyk_rule Vt_2_sg { v=Vt_2_sg z='*' } : links { v.z } : ngrams { -2 }
cyk_rule Vt_3_sg { v=Vt_3_sg z='*' } : links { v.z } : ngrams { -2 }

cyk_rule Vt_1_pl { v=Vt_1_pl z='*' } : links { v.z } : ngrams { -2 }
cyk_rule Vt_2_pl { v=Vt_2_pl z='*' } : links { v.z } : ngrams { -2 }
cyk_rule Vt_3_pl { v=Vt_3_pl z='*' } : links { v.z } : ngrams { -2 }

cyk_rule Vt_f { v=Vt_f z='*' } : links { v.z } : ngrams { -2 }
cyk_rule Vt_m { v=Vt_m z='*' } : links { v.z } : ngrams { -2 }
cyk_rule Vt_n { v=Vt_n z='*' } : links { v.z } : ngrams { -2 }
cyk_rule Vt_pl { v=Vt_pl z='*' } : links { v.z } : ngrams { -2 }

cyk_rule Vt_1_sg { z='*' v=Vt_1_sg } : links { v.z } : ngrams { -2 }
cyk_rule Vt_2_sg { z='*' v=Vt_2_sg } : links { v.z } : ngrams { -2 }
cyk_rule Vt_3_sg { z='*' v=Vt_3_sg } : links { v.z } : ngrams { -2 }

cyk_rule Vt_1_pl { z='*' v=Vt_1_pl } : links { v.z } : ngrams { -2 }
cyk_rule Vt_2_pl { z='*' v=Vt_2_pl } : links { v.z } : ngrams { -2 }
cyk_rule Vt_3_pl { z='*' v=Vt_3_pl } : links { v.z } : ngrams { -2 }

cyk_rule Vt_f { z='*' v=Vt_f } : links { v.z } : ngrams { -2 }
cyk_rule Vt_m { z='*' v=Vt_m } : links { v.z } : ngrams { -2 }
cyk_rule Vt_n { z='*' v=Vt_n } : links { v.z } : ngrams { -2 }
cyk_rule Vt_pl { z='*' v=Vt_pl } : links { v.z } : ngrams { -2 }

// ----

cyk_rule VP_1_sg { Vit_1_sg }
cyk_rule VP_2_sg { Vit_2_sg }
cyk_rule VP_3_sg { Vit_3_sg }

cyk_rule VP_1_pl { Vit_1_pl }
cyk_rule VP_2_pl { Vit_2_pl }
cyk_rule VP_3_pl { Vit_3_pl }

cyk_rule VP_f { Vit_f }
cyk_rule VP_m { Vit_m }
cyk_rule VP_n { Vit_n }
cyk_rule VP_pl { Vit_pl }

cyk_rule VP_1_sg { Vt_1_sg }
cyk_rule VP_2_sg { Vt_2_sg }
cyk_rule VP_3_sg { Vt_3_sg }

cyk_rule VP_1_pl { Vt_1_pl }
cyk_rule VP_2_pl { Vt_2_pl }
cyk_rule VP_3_pl { Vt_3_pl }

cyk_rule VP_f { Vt_f }
cyk_rule VP_m { Vt_m }
cyk_rule VP_n { Vt_n }
cyk_rule VP_pl { Vt_pl }

// я начинаю заниматься
cyk_rule VP_1_sg { v=Vm_1_sg IP } : links { v.<INFINITIVE>IP } : ngrams { ngram2(v,IP) }
// ты начинаешь заниматься
cyk_rule VP_2_sg { v=Vm_2_sg IP } : links { v.<INFINITIVE>IP } : ngrams { ngram2(v,IP) }
// он начинает заниматься
cyk_rule VP_3_sg { v=Vm_3_sg IP } : links { v.<INFINITIVE>IP } : ngrams { ngram2(v,IP) }

// мы начинаем заниматься
cyk_rule VP_1_pl { v=Vm_1_pl IP } : links { v.<INFINITIVE>IP } : ngrams { ngram2(v,IP) }
// вы начинаете заниматься
cyk_rule VP_2_pl { v=Vm_2_pl IP } : links { v.<INFINITIVE>IP } : ngrams { ngram2(v,IP) }
// они начинают заниматься
cyk_rule VP_3_pl { v=Vm_3_pl IP } : links { v.<INFINITIVE>IP } : ngrams { ngram2(v,IP) }

// я начала заниматься
cyk_rule VP_f { v=Vm_f IP } : links { v.<INFINITIVE>IP } : ngrams { ngram2(v,IP) }
// я начал заниматься
cyk_rule VP_m { v=Vm_m IP } : links { v.<INFINITIVE>IP } : ngrams { ngram2(v,IP) }
// оно начало вылезать
cyk_rule VP_n { v=Vm_n IP } : links { v.<INFINITIVE>IP } : ngrams { ngram2(v,IP) }
// они начали заниматься
cyk_rule VP_pl { v=Vm_pl IP } : links { v.<INFINITIVE>IP } : ngrams { ngram2(v,IP) }


// ---------------------------
// с деепричастным оборотом:
// ---------------------------

// Сидя в кресле, делаю уроки
cyk_rule VP_1_sg { YVP v=VP_1_sg } : links { v.<ADV_PARTICIPLE>YVP }
cyk_rule VP_2_sg { YVP v=VP_2_sg } : links { v.<ADV_PARTICIPLE>YVP }
cyk_rule VP_3_sg { YVP v=VP_3_sg } : links { v.<ADV_PARTICIPLE>YVP }

cyk_rule VP_1_pl { YVP v=VP_1_pl } : links { v.<ADV_PARTICIPLE>YVP }
cyk_rule VP_2_pl { YVP v=VP_2_pl } : links { v.<ADV_PARTICIPLE>YVP }
cyk_rule VP_3_pl { YVP v=VP_3_pl } : links { v.<ADV_PARTICIPLE>YVP }

cyk_rule VP_f { YVP v=VP_f } : links { v.<ADV_PARTICIPLE>YVP }
cyk_rule VP_m { YVP v=VP_m } : links { v.<ADV_PARTICIPLE>YVP }
cyk_rule VP_n { YVP v=VP_n } : links { v.<ADV_PARTICIPLE>YVP }
cyk_rule VP_pl { YVP v=VP_pl } : links { v.<ADV_PARTICIPLE>YVP }

// Делаю уроки, сидя в кресле
cyk_rule VP_1_sg { v=VP_1_sg YVP } : links { v.<ADV_PARTICIPLE>YVP }
cyk_rule VP_2_sg { v=VP_2_sg YVP } : links { v.<ADV_PARTICIPLE>YVP }
cyk_rule VP_3_sg { v=VP_3_sg YVP } : links { v.<ADV_PARTICIPLE>YVP }

cyk_rule VP_1_pl { v=VP_1_pl YVP } : links { v.<ADV_PARTICIPLE>YVP }
cyk_rule VP_2_pl { v=VP_2_pl YVP } : links { v.<ADV_PARTICIPLE>YVP }
cyk_rule VP_3_pl { v=VP_3_pl YVP } : links { v.<ADV_PARTICIPLE>YVP }

cyk_rule VP_f { v=VP_f YVP } : links { v.<ADV_PARTICIPLE>YVP }
cyk_rule VP_m { v=VP_m YVP } : links { v.<ADV_PARTICIPLE>YVP }
cyk_rule VP_n { v=VP_n YVP } : links { v.<ADV_PARTICIPLE>YVP }
cyk_rule VP_pl { v=VP_pl YVP } : links { v.<ADV_PARTICIPLE>YVP }

// ------------------------
// С прямым дополнением:
// ------------------------

// Вижу Луну
cyk_rule VP_1_sg { v=Vt_1_sg OBJ } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,OBJ) }
cyk_rule VP_2_sg { v=Vt_2_sg OBJ } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,OBJ) }
cyk_rule VP_3_sg { v=Vt_3_sg OBJ } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,OBJ) }

cyk_rule VP_1_pl { v=Vt_1_pl OBJ } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,OBJ) }
cyk_rule VP_2_pl { v=Vt_2_pl OBJ } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,OBJ) }
cyk_rule VP_3_pl { v=Vt_3_pl OBJ } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,OBJ) }

cyk_rule VP_f { v=Vt_f OBJ } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,OBJ) }
cyk_rule VP_m { v=Vt_m OBJ } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,OBJ) }
cyk_rule VP_n { v=Vt_n OBJ } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,OBJ) }
cyk_rule VP_pl { v=Vt_pl OBJ } : links { v.<OBJECT>OBJ } : ngrams { ngram2(v,OBJ) }

// Луну вижу
cyk_rule VP_1_sg { OBJ v=Vt_1_sg } : links { v.<OBJECT>OBJ } : ngrams { -1 ngram2(v,OBJ) }
cyk_rule VP_2_sg { OBJ v=Vt_2_sg } : links { v.<OBJECT>OBJ } : ngrams { -1 ngram2(v,OBJ) }
cyk_rule VP_3_sg { OBJ v=Vt_3_sg } : links { v.<OBJECT>OBJ } : ngrams { -1 ngram2(v,OBJ) }

cyk_rule VP_1_pl { OBJ v=Vt_1_pl } : links { v.<OBJECT>OBJ } : ngrams { -1 ngram2(v,OBJ) }
cyk_rule VP_2_pl { OBJ v=Vt_2_pl } : links { v.<OBJECT>OBJ } : ngrams { -1 ngram2(v,OBJ) }
cyk_rule VP_3_pl { OBJ v=Vt_3_pl } : links { v.<OBJECT>OBJ } : ngrams { -1 ngram2(v,OBJ) }

cyk_rule VP_f { OBJ v=Vt_f } : links { v.<OBJECT>OBJ } : ngrams { -1 ngram2(v,OBJ) }
cyk_rule VP_m { OBJ v=Vt_m } : links { v.<OBJECT>OBJ } : ngrams { -1 ngram2(v,OBJ) }
cyk_rule VP_n { OBJ v=Vt_n } : links { v.<OBJECT>OBJ } : ngrams { -1 ngram2(v,OBJ) }
cyk_rule VP_pl { OBJ v=Vt_pl } : links { v.<OBJECT>OBJ } : ngrams { -1 ngram2(v,OBJ) }

// Кошка спит
cyk_rule VP_1_sg { s=SBJ_1_sg v=VP_1_sg } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }
cyk_rule VP_2_sg { s=SBJ_2_sg v=VP_2_sg } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }
cyk_rule VP_3_sg { s=SBJ_3_sg v=VP_3_sg } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }

cyk_rule VP_1_pl { s=SBJ_1_pl v=VP_1_pl } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }
cyk_rule VP_2_pl { s=SBJ_2_pl v=VP_2_pl } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }
cyk_rule VP_3_pl { s=SBJ_3_pl v=VP_3_pl } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }

cyk_rule VP_f { s=SBJ_f v=VP_f } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }
cyk_rule VP_m { s=SBJ_m v=VP_m } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }
cyk_rule VP_n { s=SBJ_n v=VP_n } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }
cyk_rule VP_pl { s=SBJ_pl v=VP_pl } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }


// Спит кошка
cyk_rule VP_1_sg { v=VP_1_sg s=SBJ_1_sg } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }
cyk_rule VP_2_sg { v=VP_2_sg s=SBJ_2_sg } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }
cyk_rule VP_3_sg { v=VP_3_sg s=SBJ_3_sg } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }

cyk_rule VP_1_pl { v=VP_1_pl s=SBJ_1_pl } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }
cyk_rule VP_2_pl { v=VP_2_pl s=SBJ_2_pl } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }
cyk_rule VP_3_pl { v=VP_3_pl s=SBJ_3_pl } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }

cyk_rule VP_f { v=VP_f s=SBJ_f } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }
cyk_rule VP_m { v=VP_m s=SBJ_m } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }
cyk_rule VP_n { v=VP_n s=SBJ_n } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }
cyk_rule VP_pl { v=VP_pl s=SBJ_pl } : links { v.<SUBJECT>s } : ngrams { ngram2(s,v) }


// Союзные конструкции для глаголов:
// кошки спали, а мышки рыскали на кухне
cyk_rule VPJ_1_sg { JVP v=VP_1_sg } : links { JVP.<OBJECT>v }
cyk_rule VPJ_2_sg { JVP v=VP_2_sg } : links { JVP.<OBJECT>v }
cyk_rule VPJ_3_sg { JVP v=VP_3_sg } : links { JVP.<OBJECT>v }

cyk_rule VPJ_1_pl { JVP v=VP_1_pl } : links { JVP.<OBJECT>v }
cyk_rule VPJ_2_pl { JVP v=VP_2_pl } : links { JVP.<OBJECT>v }
cyk_rule VPJ_3_pl { JVP v=VP_3_pl } : links { JVP.<OBJECT>v }

cyk_rule VPJ_f { JVP v=VP_f } : links { JVP.<OBJECT>v }
cyk_rule VPJ_m { JVP v=VP_m } : links { JVP.<OBJECT>v }
cyk_rule VPJ_n { JVP v=VP_n } : links { JVP.<OBJECT>v }
cyk_rule VPJ_pl { JVP v=VP_pl } : links { JVP.<OBJECT>v }


cyk_rule VP_1_sg { v=VP_1_sg j=VPJ_1_sg } : links { v.<RIGHT_LOGIC_ITEM>j }
cyk_rule VP_2_sg { v=VP_2_sg j=VPJ_2_sg } : links { v.<RIGHT_LOGIC_ITEM>j }
cyk_rule VP_3_sg { v=VP_3_sg j=VPJ_3_sg } : links { v.<RIGHT_LOGIC_ITEM>j }

cyk_rule VP_1_pl { v=VP_1_pl j=VPJ_1_pl } : links { v.<RIGHT_LOGIC_ITEM>j }
cyk_rule VP_2_pl { v=VP_2_pl j=VPJ_2_pl } : links { v.<RIGHT_LOGIC_ITEM>j }
cyk_rule VP_3_pl { v=VP_3_pl j=VPJ_3_pl } : links { v.<RIGHT_LOGIC_ITEM>j }

cyk_rule VP_f { v=VP_f j=VPJ_f } : links { v.<RIGHT_LOGIC_ITEM>j }
cyk_rule VP_m { v=VP_m j=VPJ_m } : links { v.<RIGHT_LOGIC_ITEM>j }
cyk_rule VP_n { v=VP_n j=VPJ_n } : links { v.<RIGHT_LOGIC_ITEM>j }
cyk_rule VP_pl { v=VP_pl j=VPJ_pl } : links { v.<RIGHT_LOGIC_ITEM>j }



// --- ГРУППА КРАТКОГО ПРИЛАГАТЕЛЬНОГО

// Она была очень довольна
cyk_rule AS_f { Y AS_f } : links { AS_f.<ATTRIBUTE>Y }

// Он был очень доволен
cyk_rule AS_m { Y AS_m } : links { AS_m.<ATTRIBUTE>Y }

// Оно было очень довольно
cyk_rule AS_n { Y AS_n } : links { AS_n.<ATTRIBUTE>Y }

// Они были очень довольны
cyk_rule AS_pl { Y AS_pl } : links { AS_pl.<ATTRIBUTE>Y }



// --- ГРУППА ГЛАГОЛА-СВЯЗКИ

// Она всегда была довольна
cyk_rule CV_f { Y CV_f } : links { CV_f.<ATTRIBUTE>Y }

// Он всегда был доволен
cyk_rule CV_m { Y CV_m } : links { CV_m.<ATTRIBUTE>Y }

// Оно всегда было довольно
cyk_rule CV_n { Y CV_n } : links { CV_n.<ATTRIBUTE>Y }

// Они всегда были довольны
cyk_rule CV_pl { Y CV_pl } : links { CV_pl.<ATTRIBUTE>Y }


// ------------------------------------------------------------------------
// Конструкции с глаголом-связкой и ремой в виде краткого прилагательного
// ------------------------------------------------------------------------

// был голоден
cyk_rule CV_m { CV_m AS_m } : links { CV_m.<RHEMA>AS_m }

// была голодна
cyk_rule CV_f { CV_f AS_f } : links { CV_f.<RHEMA>AS_f }

// было голодно
cyk_rule CV_n { CV_n AS_n } : links { CV_n.<RHEMA>AS_n }

// были голодны
cyk_rule CV_pl { CV_pl AS_pl } : links { CV_pl.<RHEMA>AS_pl }

cyk_rule CVP_f { s=SBJ_f v=CV_f } : links { v.<SUBJECT>s }
cyk_rule CVP_m { s=SBJ_m v=CV_m } : links { v.<SUBJECT>s }
cyk_rule CVP_n { s=SBJ_n v=CV_n } : links { v.<SUBJECT>s }
cyk_rule CVP_pl { s=SBJ_pl v=CV_pl } : links { v.<SUBJECT>s }

cyk_rule S { CVP_f }
cyk_rule S { CVP_m }
cyk_rule S { CVP_n }
cyk_rule S { CVP_pl }


// --------------------------------------------
// Полное предложение с глагольным сказуемым:
// --------------------------------------------

cyk_rule S { VP_1_sg }
cyk_rule S { VP_2_sg }
cyk_rule S { VP_3_sg }

cyk_rule S { VP_1_pl }
cyk_rule S { VP_2_pl }
cyk_rule S { VP_3_pl }

cyk_rule S { VP_f }
cyk_rule S { VP_m }
cyk_rule S { VP_n }
cyk_rule S { VP_pl }

// ------------------------------------------------------
// Финальные терминаторы - присоединяем их к предложению
// ------------------------------------------------------

cyk_rule S { S STERM } : links { S.<PUNCTUATION>STERM }

