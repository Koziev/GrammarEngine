// модальный НАЧАТЬ и подобные обычно присоединяют только
// несовершенный инфинитив:
// но сперва напомнить начало
//           ^^^^^^^^^ ~~~~~~

wordentry_set МодальныеТолькоНесоверш=
{
 rus_verbs:БЫТЬ{},
 rus_verbs:ПРИСПОСАБЛИВАТЬ{},
 rus_verbs:НАУЧАТЬ{},
 rus_verbs:НАУЧАТЬСЯ{},
 rus_verbs:ОБУЧАТЬСЯ{},
 rus_verbs:начать{},
 rus_verbs:начинать{},
 rus_verbs:уставать{},
 rus_verbs:устать{},
 rus_verbs:закончить{},
 rus_verbs:заканчивать{},
 rus_verbs:стать{},
 rus_verbs:забыть{},
 rus_verbs:продолжать{},
 rus_verbs:бросить{},
 rus_verbs:достать{},
 rus_verbs:учиться{},
 rus_verbs:прекратить{},
 rus_verbs:учить{},
 rus_verbs:опасаться{},
 rus_verbs:привыкнуть{},
 rus_verbs:бросать{},
 rus_verbs:избегать{},
 rus_verbs:приступить{},
 rus_verbs:научить{},
 rus_verbs:двинуться{},
 rus_verbs:полюбить{},
 rus_verbs:перестать{},
 rus_verbs:привыкать{},
 rus_verbs:кончить{},
 rus_verbs:кончать{},
 rus_verbs:запретить{},
 rus_verbs:пуститься{},
 rus_verbs:выучить{},
 rus_verbs:обучать{},
 rus_verbs:стыдиться{},
 rus_verbs:приступать{},
 rus_verbs:обучить{},
 rus_verbs:приняться{},
 rus_verbs:окончить{},
 rus_verbs:приниматься{},
 rus_verbs:тренироваться{},
 rus_verbs:приучить{},
 rus_verbs:прекращать{},
 rus_verbs:запрещать{},
 rus_verbs:выучиться{},
 rus_verbs:приучать{},
 rus_verbs:отучить{},
 rus_verbs:отвыкнуть{},
 rus_verbs:приноровиться{},
 rus_verbs:отвыкать{},
 rus_verbs:разучиться{},
 rus_verbs:отучиться{},
 rus_verbs:утомляться{},
 rus_verbs:приучаться{},
 rus_verbs:приучиться{},
 rus_verbs:приохотить{},
 rus_verbs:переставать{},
 rus_verbs:отучать{},
 rus_verbs:наловчиться{},
 rus_verbs:отучаться{},
 rus_verbs:натренироваться{},
 rus_verbs:приловчиться{},
 rus_verbs:замучиться{},
 rus_verbs:насобачиться{},
 rus_verbs:повадиться{},
 rus_verbs:заколебать{},
 rus_verbs:приохотиться{},
 rus_verbs:заебать{},
 rus_verbs:заебаться{},
 глагол:замучаться{},
 инфинитив:замучаться{},
 rus_verbs:приучиваться{}
}

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { инфинитив:*{ вид:соверш }.<LEFT_AUX_VERB>МодальныеТолькоНесоверш }
  then -100
}


