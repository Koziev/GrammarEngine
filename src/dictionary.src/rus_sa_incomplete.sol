
patterns НеполнПредлож0 export { node:root_node }


// по умолчанию предпочитаем существительное в именительном падеже:
// "простой техники" - тут будет сущ. простой, 
pattern НеполнПредлож0
{
 ГруппаСущ4{ падеж:им } : export { node:root_node }
} : ngrams { -2 }

// Для существительного есть важная эмпирика - предложный падеж без предлога
// обычно не употребляется.
pattern НеполнПредлож0
{
 ГруппаСущ4{ падеж:род } : export { node:root_node }
} : ngrams { -3 }


// чаю, греющего душу
pattern НеполнПредлож0
{
 ГруппаСущ4{ падеж:парт } : export { node:root_node }
} : ngrams { -3 }


pattern НеполнПредлож0
{
 ГруппаСущ4{ падеж:твор } : export { node:root_node }
} : ngrams { -3 }


pattern НеполнПредлож0
{
 ГруппаСущ4{ падеж:вин } : export { node:root_node }
} : ngrams { -3 }


pattern НеполнПредлож0
{
 ГруппаСущ4{ падеж:дат } : export { node:root_node }
} : ngrams { -3 }


// шведском столе
pattern НеполнПредлож0
{
 ГруппаСущ4{ падеж:предл } : export { node:root_node }
} : ngrams { -5 }


// - О  глупый  Петер,  сын угольщика! - воскликнул человечек
//   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern НеполнПредлож0
{
 частица:о{}
 ГруппаСущ4{ падеж:им одуш:одуш } : export { node:root_node }
} : ngrams { -3 }


// Однажды в Китае и Америке
pattern НеполнПредлож0
{
 adv=ГруппаНареч2
 p=Предлог_В_НА : export { node:root_node }
 n=ГруппаСущ4{ падеж:предл }
}
: links { p.{ <ATTRIBUTE>adv <OBJECT>n } }
: ngrams { -4 }



// ------------------------------------------------------

pattern НеполнПредлож0
{
 ГруппаНареч2 : export { node:root_node }
}
: ngrams { -4 }

pattern НеполнПредлож0
{
 ГруппаСрНареч2 : export { node:root_node }
}
: ngrams { -4 }

pattern НеполнПредлож0
{
 ГруппаПрил2 : export { node:root_node }
}
: ngrams { -3 }

pattern НеполнПредлож0
{
 КраткПрил1 : export { node:root_node }
}
: ngrams { -3 }

pattern НеполнПредлож0
{
 Обст : export { node:root_node }
}
: ngrams { -4 }

pattern НеполнПредлож0
{
 ПричОборот2 : export { node:root_node }
}
: ngrams { -3 }

pattern НеполнПредлож0
{
 ГруппаМест : export { node:root_node }
}
: ngrams { -4 }

// ------------------------------------------------------

tree_scorers ВалентностьНеполнИнфинитивн

// И всем окопаться!
tree_scorer ВалентностьНеполнИнфинитивн language=Russian generic
{
 if context { инфинитив:*.{ ~ПАДЕЖ:ТВОР }.<OBJECT>'всем'{ ПАДЕЖ:ДАТ } }
  then 8
}

pattern НеполнПредлож0
{
 v=Инф2 : export { node:root_node }
}
: ngrams
{
 -3
 ВалентностьНеполнИнфинитивн(v)
}




pattern НеполнПредлож0
{
 Деепр2 : export { node:root_node }
}
: ngrams { -4 }

pattern НеполнПредлож0
{
 ЧислСущ : export { node:root_node }
}
: ngrams { -3 }


pattern НеполнПредлож0
{
 v=Сказуемое : export { node:root_node }
}


// ЭТО в роли вводной частицы:
// это меня хотели убить!
pattern НеполнПредлож0
{
 x=ЭтоКакЧастица
 p=Сказуемое : export { node:root_node }
} : links { p.<PREFIX_PARTICLE>x }
  : ngrams { -2 }


// ну хватит об этом
pattern НеполнПредлож0
{
 x=частица:ну{}
 p=Сказуемое : export { node:root_node }
} : links { p.<BEG_INTRO>x }
  : ngrams { -2 }

// Союз ЗАТО и другие как вводная частица:
// зато хорошенько изучил местность.
pattern НеполнПредлож0
{
 conj=союз:*{}
 p=Сказуемое : export { node:root_node }
}
: links { p.<BEG_INTRO>conj }
: ngrams { -2 }

pattern НеполнПредлож0
{
 ПредлогИСущ : export { node:root_node }
}
: ngrams { -5 }


// ---------------------------------------------------------


pattern НеполнПредлож
{
 v=НеполнПредлож0 : export { node:root_node }
}

// - Приготовить чай, мамочка?
pattern НеполнПредлож
{
 v=Инф2 : export { node:root_node }
 x=ПрямоеОбращение
}
: links { v.<APPEAL>x }
: ngrams { -3 }


// Господа, немедленно покинуть помещение!
// Боже мой, какое счастье!
pattern НеполнПредлож
{
 x=ПрямоеОбращение
 v=НеполнПредлож0 : export { node:root_node }
}
: links { v.<APPEAL>x }
: ngrams { -3 }


// вот бы купить самолет!
pattern НеполнПредлож
{
 intro=ВводнаяФраза
 p=НеполнПредлож0 : export { node:root_node }
}
: links { p.<BEG_INTRO>intro }
: ngrams { -3 }


// - А по-моему, это очень нетрудно понять.
//   ^^^^^^^^^^
pattern НеполнПредлож
{
 intro0=ВводнСоюз
 intro=ВводнаяФраза
 p=НеполнПредлож0 : export { node:root_node }
}
: links
{
 p.{
    <BEG_INTRO>intro0
    <BEG_INTRO>intro
   }
}
: ngrams { -3 }




// однако поступать так глупо
pattern НеполнПредлож
{
 opener=вводное:*{}
 s=Инф2 : export { node:root_node }
} : links { s.<BEG_INTRO>opener }
  : ngrams { -2 }

// или же держать при себе.
// И получше изучить местность.
// Ах, хорошо бы сейчас искупаться в Черном море!
pattern НеполнПредлож
{
 opener=СоюзКакВводн
 s=НеполнПредлож0 : export { node:root_node }
} : links { s.<BEG_INTRO>opener }
//: ngrams { -3 }

// - А если откачать воду из минных труб?
//   ^^^^^^
pattern НеполнПредлож
{
 opener0=СоюзКакВводн0
 opener=СоюзКакВводн
 s=НеполнПредлож0 : export { node:root_node }
}
: links { s.{ <BEG_INTRO>opener0 <BEG_INTRO>opener } }
: ngrams { -3 }



// Да, но где же взять двенадцатый?
// ^^^^^^
pattern НеполнПредлож
{
 intro=ВводнаяФраза
 @probe_left(',')
 opener=СоюзКакВводн
 s=НеполнПредлож0 : export { node:root_node }
}
: links
{
 s.{
    <BEG_INTRO>intro
    <BEG_INTRO>opener
   }
}
: ngrams { -3 }



// был рад помочь
pattern НеполнПредлож
{
 НеполнСвязка : export { node:root_node }
}
: ngrams { -1 }

// ведь должны были сразу привести ее сюда.
pattern НеполнПредлож
{
 int=СоюзКакВводн0
 p=НеполнСвязка : export { node:root_node }
} : links
{
 p.<BEG_INTRO>int
}
: ngrams
{
 -1
}
