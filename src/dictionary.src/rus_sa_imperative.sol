﻿// #################################################
// Императивные конструкции для русской грамматики
// #################################################

patterns ГлИмпСДоп export { ЧИСЛО ЛИЦО node:root_node }

pattern ГлИмпСДоп
{
 v=ГлНастСказ_Нисх{ НАКЛОНЕНИЕ:ПОБУД } : export { node:root_node ЧИСЛО ЛИЦО }
}
: ngrams
{
 ВалентностьГлагола(v)
}