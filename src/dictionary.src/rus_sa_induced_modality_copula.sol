// Разбор нулевых связок с индуцированной модальностью:
// Жуткое дело смотреть.



// -------------------------------------------------------

patterns ИндуцМодСказуемоеВосх { bottomup } export { node:root_node }


wordentry_set ПодлежащееДляИндуцМод = существительное:{ дело, задача, цель }

pattern ИндуцМодСказуемоеВосх
{
 ГруппаСущ4{ ПАДЕЖ:ИМ ЧИСЛО:ЕД ПодлежащееДляИндуцМод } : export { node:root_node }
}


// ------------------------------------------

pattern ИндуцМодСказуемоеВосх
{
 v=ИндуцМодСказуемоеВосх : export { node:root_node }
 inf=Инф2
}
: links { v.<OBJECT>inf }


pattern ИндуцМодСказуемоеВосх
{
 v=ИндуцМодСказуемоеВосх : export { node:root_node }
 adv=Обст
}
: links { v.<ATTRIBUTE>adv }


// Она умница, конечно.
pattern ИндуцМодСказуемоеВосх
{
 v=ИндуцМодСказуемоеВосх : export { node:root_node }
 adv=ВводнАктант
} : links { v.<BEG_INTRO>adv }


// --------------------------------------------------------

patterns ИндуцМодСказуемоеНисх export { THEMA_VALENCY node:root_node }

pattern ИндуцМодСказуемоеНисх
{
 ИндуцМодСказуемоеВосх : export { THEMA_VALENCY:0 node:root_node }
}

pattern ИндуцМодСказуемоеНисх
{
 adv=Обст
 v=ИндуцМодСказуемоеНисх : export { THEMA_VALENCY node:root_node }
}
: links { v.<ATTRIBUTE>adv }
: ngrams { -1 }


pattern ИндуцМодСказуемоеНисх
{
 intro=ВводнАктант
 v=ИндуцМодСказуемоеНисх : export { THEMA_VALENCY node:root_node }
} 
: links { v.<BEG_INTRO>intro }


pattern ИндуцМодСказуемоеНисх
{
 intro=Детализатор
 v=ИндуцМодСказуемоеНисх : export { THEMA_VALENCY node:root_node }
} 
: links { v.<DETAILS>intro }


pattern ИндуцМодСказуемоеНисх
{
 pn=ПредлогИСущ
 v=ИндуцМодСказуемоеНисх : export { THEMA_VALENCY node:root_node }
} 
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams { -5 }

/*
pattern ИндуцМодСказуемоеНисх
{
 sbj=Подлежащее{ ПодлежащееДляИндуцМод }
 v=ИндуцМодСказуемоеНисх{ THEMA_VALENCY:1 } : export { THEMA_VALENCY:0 node:root_node }
}
: links { v.<SUBJECT>sbj }
*/


// ============================================================

pattern ПредикатСвязка
{
 t=ИндуцМодСказуемоеНисх{ THEMA_VALENCY:0 } : export { node:root_node }
}
: ngrams
{
 ВалентностьНульСвязки(t)
}
