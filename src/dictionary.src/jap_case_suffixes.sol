// CD->07.03.2009
// LC->07.03.2009
// --------------

automat sg
{
 #define JapCaseSuffix(x,case) entry x : JAP_CASE_SUFFIX { JAP_CASE:case }


 JapCaseSuffix( は, NOMINATIVE_THEM ) // Именной падеж тематического подлежащего
 JapCaseSuffix( が, NOMINATIVE_RHEM ) // Именной падеж рематического подлежащего
 JapCaseSuffix( を, ACCUSATIVE ) // винительный
 JapCaseSuffix( の, GENITIVE ) // родительный
 JapCaseSuffix( に, DATIVE ) // дательный, места при глаголе состояния, цели, предварительный
 JapCaseSuffix( へ, ALLATIVE ) // направления
 JapCaseSuffix( で, INSTRUMENTATIVE ) // орудия, места действия
 JapCaseSuffix( から, ELATIVE ) // исходный
 JapCaseSuffix( まで, LIMITIVE ) // предельный
 JapCaseSuffix( より, COMPARATIVE ) // сравнения
 JapCaseSuffix( と, COMITATIVE ) // совместный
 JapCaseSuffix( も, SOCIATIVE ) // присоединительный

}
