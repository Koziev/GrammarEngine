// Некоторые модальные глаголы присоединяют только совершенный инфинитив:
//
// Командир остановился атаковать огневую точку.
// Зайчик остановился посмотреть по сторонам.

wordentry_set SupressImperfectInf=
{
 rus_verbs:остановиться{},
 rus_verbs:подойти{},
 rus_verbs:успеть{},
 rus_verbs:напомнить{},
 rus_verbs:повернуться{},
 rus_verbs:обернуться{},
 rus_verbs:угрожать{},
 rus_verbs:заехать{},
 rus_verbs:доверить{},
 rus_verbs:отчаиваться{}
}

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { инфинитив:*{ вид:несоверш }.<LEFT_AUX_VERB>SupressImperfectInf }
  then -97
}
