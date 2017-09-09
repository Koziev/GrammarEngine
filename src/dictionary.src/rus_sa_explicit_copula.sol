
patterns ПодлежащееВСвязке export { node:root_node }
pattern ПодлежащееВСвязке
{
 Подлежащее : export { node:root_node }
}



// Попытка - не пытка
pattern ПредикатСвязка
{
 sbj=Подлежащее
 v=ДефисКакСвязка : export { node:root_node }
 n=частица:не{}
 r=ПодлежащееВСвязке
} : links
{
 v.{
    <NEGATION_PARTICLE>n
    <SUBJECT>sbj
    <RHEMA>r
   }
}


// отвлечься игрой света - плохой признак
pattern ПредикатСвязка
{
 thema=Инф2
 v=ДефисКакСвязка : export { node:root_node }
 rhema=ПодлежащееВСвязке
} : links
{
 v.{
    <THEMA>thema
    <RHEMA>rhema
   }
}


// ведь ты - мужчина
pattern ПредикатСвязка
{
 adv=ГруппаНареч2
 sbj=Подлежащее
 v=ДефисКакСвязка : export { node:root_node }
 r=ПодлежащееВСвязке
} : links
{
 v.{
    <ATTRIBUTE>adv
    <SUBJECT>sbj
    <RHEMA>r
   }
}
: ngrams
{
 -1
 ВалентностьГлагола(v)
}

// потом - про себя
pattern ПредикатСвязка
{
 t=ГруппаНареч2
 v=ДефисКакСвязка : export { node:root_node }
 r=ПредлогИСущ
} : links
{
 v.{
    <THEMA>t
    <RHEMA>r
   }
}


// а теперь - вперед
pattern ПредикатСвязка
{
 t=ГруппаНареч2
 v=ДефисКакСвязка : export { node:root_node }
 r=ГруппаНареч2
} : links
{
 v.{
    <THEMA>t
    <RHEMA>r
   }
}


// для нас - мгновенье
pattern ПредикатСвязка
{
 t=ПредлогИСущ
 v=ДефисКакСвязка : export { node:root_node }
 p=@optional('это'{ class:местоим_сущ падеж:им })
 r=ПодлежащееВСвязке
} : links
{
 v.{
    <THEMA>t
    ~<NEXT_COLLOCATION_ITEM>p
    <RHEMA>r
   }
}

// дед - за ним
// сила - это для слабых
pattern ПредикатСвязка
{
 t=Подлежащее
 v=ДефисКакСвязка : export { node:root_node }
 p=@optional('это'{ class:местоим_сущ падеж:им })
 r=ПредлогИСущ
} : links
{
 v.{
    <THEMA>t
    ~<NEXT_COLLOCATION_ITEM>p
    <RHEMA>r
   }
}

// служить тебе - великая честь
pattern ПредикатСвязка
{
 t=Инф2
 v=ДефисКакСвязка : export { node:root_node }
 r=ПодлежащееВСвязке
} : links
{
 v.{
    <THEMA>t
    <RHEMA>r
   }
}

// сзади - отряд лучников
pattern ПредикатСвязка
{
 t=ГруппаНареч2
 v=ДефисКакСвязка : export { node:root_node }
 r=ПодлежащееВСвязке
} : links
{
 v.{
    <THEMA>t
    <RHEMA>r
   }
}
: ngrams { -1 } // правда - осколок льда


// жить - значит чувствовать
pattern ПредикатСвязка
{
 t=Инф2
 v=ДефисКакСвязка : export { node:root_node }
 aux = 'значит'{ class:глагол }
 r=Инф2
} : links
{
 v.{
    <THEMA>t
    <RHEMA>aux.<INFINITIVE>r
   }
}



// а сейчас - спать
pattern ПредикатСвязка
{
 t=ГруппаНареч2
 v=ДефисКакСвязка : export { node:root_node }
 r=Инф2
} : links
{
 v.{
    <THEMA>t
    <RHEMA>r
   }
}


// точнее - у вас
pattern ПредикатСвязка
{
 t=ГруппаСрНареч2
 v=ДефисКакСвязка : export { node:root_node }
 r=ПредлогИСущ
} : links
{
 v.{
    <THEMA>t
    <RHEMA>r
   }
}

// во дворце - скучно
pattern ПредикатСвязка
{
 t=ПредлогИСущ
 v=ДефисКакСвязка : export { node:root_node }
 r=ГруппаНареч2
} : links
{
 v.{
    <THEMA>t
    <RHEMA>r
   }
}



// Для них создание рисунков - настоящий подвиг
pattern ПредикатСвязка
{
 pp=ПредлогИСущ
 sbj=Подлежащее
 v=ДефисКакСвязка : export { node:root_node }
 r=ПодлежащееВСвязке
} : links
{
 v.{
    <PREPOS_ADJUNCT>pp
    <SUBJECT>sbj
    <RHEMA>r
   }
}



// кот - хитрое и коварное животное
pattern ПредикатСвязка
{
 sbj=Подлежащее
 v=ДефисКакСвязка : export { node:root_node }
 r=ПодлежащееВСвязке
} : links
{
 v.{
    <SUBJECT>sbj
    <RHEMA>r
   }
}

// другое дело - мы
pattern ПредикатСвязка
{
 sbj=Подлежащее
 v=ДефисКакСвязка : export { node:root_node }
 r=ГруппаМест{ ПАДЕЖ:ИМ }
} : links
{
 v.{
    <SUBJECT>sbj
    <RHEMA>r
   }
}

// Россия для Абхазии – гарант нашей государственности и стабильности.
pattern ПредикатСвязка
{
 sbj=Подлежащее
 attr=ПредлогИСущ
 v=ДефисКакСвязка : export { node:root_node }
 r=ПодлежащееВСвязке
} : links
{
 v.{
    <SUBJECT>sbj.<ATTRIBUTE>attr
    <RHEMA>r
   }
}
: ngrams { -10 }



// Цена билета - 120 руб
pattern ПредикатСвязка
{
 sbj=Подлежащее
 v=ДефисКакСвязка : export { node:root_node }
 r=ЧислСущ
} : links
{
 v.{
    <SUBJECT>sbj
    <RHEMA>r
   }
}
: ngrams { -2 }



// она ведь - женщина
pattern ПредикатСвязка
{
 sbj=Подлежащее
 adv=ГруппаНареч2
 v=ДефисКакСвязка : export { node:root_node }
 r=ПодлежащееВСвязке
} : links
{
 v.{
    <SUBJECT>sbj
    <RHEMA>r
    <ATTRIBUTE>adv
   }
}

// знание - тоже оружие
pattern ПредикатСвязка
{
 sbj=Подлежащее
 v=ДефисКакСвязка : export { node:root_node }
 adv=ГруппаНареч2
 r=ПодлежащееВСвязке
} : links
{
 v.{
    <SUBJECT>sbj
    <RHEMA>r
    <ATTRIBUTE>adv
   }
} : ngrams { -1 } // чтобы не мешать прикрепляться наречию к прилагательным в реме

// любить - гораздо тяжелее
pattern ПредикатСвязка
{
 t=Инф2
 v=ДефисКакСвязка : export { node:root_node }
 r=ГруппаСрНареч2
} : links
{
 v.{
    <THEMA>t
    <RHEMA>r
   }
}

// потом - снова жужжание
pattern ПредикатСвязка
{
 t=ГруппаНареч2
 v=ДефисКакСвязка : export { node:root_node }
 adv=ГруппаНареч2
 r=ПодлежащееВСвязке
} : links
{
 v.{
    <THEMA>t
    <RHEMA>r
    <ATTRIBUTE>adv
   }
}
: ngrams
{
 ВалентностьПредиката(v)
}

// дальше - только темнота
pattern ПредикатСвязка
{
 t=ГруппаСрНареч2
 v=ДефисКакСвязка : export { node:root_node }
 adv=ГруппаНареч2
 r=ПодлежащееВСвязке
} : links
{
 v.{
    <THEMA>t
    <RHEMA>r
    <ATTRIBUTE>adv
   }
}



// без них - спокойнее
pattern ПредикатСвязка
{
 t=ПредлогИСущ
 v=ДефисКакСвязка : export { node:root_node }
 r=ГруппаСрНареч2
} : links
{
 v.{
    <THEMA>t
    <RHEMA>r
   }
}



// далее - тьма тишины
pattern ПредикатСвязка
{
 t=ГруппаСрНареч2
 v=ДефисКакСвязка : export { node:root_node }
 r=ПодлежащееВСвязке
} : links
{
 v.{
    <THEMA>t
    <RHEMA>r
   }
}




// когда - это вопрос
pattern ПредикатСвязка
{
 t=ГруппаНареч2
 v=ДефисКакСвязка : export { node:root_node }
 v2=местоим_сущ:это{ падеж:им }
 r=ПодлежащееВСвязке
} : links
{
 v.{
    <NEXT_COLLOCATION_ITEM>v2
    <THEMA>t
    <RHEMA>r
   }
}
: ngrams { 2 } // чтобы подавить распознавание ЭТО как атрибутивного прилагательного.


// неделя - это смешно
pattern ПредикатСвязка
{
 t=Подлежащее
 v=ДефисКакСвязка : export { node:root_node }
 v2=местоим_сущ:это{ падеж:им }
 r=ГруппаНареч2
} : links
{
 v.{
    <NEXT_COLLOCATION_ITEM>v2
    <THEMA>t
    <RHEMA>r
   }
}
: ngrams { 3 } // чтобы подавить распознавание ЭТО как атрибутивного прилагательного.


// кот - это хитрое и коварное животное
// а зло - это болезнь.
pattern ПредикатСвязка
{
 sbj=Подлежащее
 v=ДефисКакСвязка : export { node:root_node }
 v2=местоим_сущ:это{ падеж:им }
 r=ПодлежащееВСвязке
} : links
{
 v.{
    <NEXT_COLLOCATION_ITEM>v2
    <SUBJECT>sbj
    <RHEMA>r
   }
}
: ngrams { 12 } // чтобы подавить распознавание ЭТО как атрибутивного прилагательного.


// Мой кот - тут
pattern ПредикатСвязка
{
 sbj=Подлежащее
 v=ДефисКакСвязка : export { node:root_node }
 r=ГруппаНареч2
} : links
{
 v.{
    <SUBJECT>sbj
    <RHEMA>r
   }
}


patterns ГруппаПрилРема export { node:root_node РОД ЧИСЛО }

pattern ГруппаПрилРема
{
 ГруппаПрил2{ ПАДЕЖ:ИМ } : export { РОД ЧИСЛО node:root_node }
}

// Суперлатив в предикативной роли:
// мой кот - ленивейший из котов
//           ^^^^^^^^^^^^^^^^^^^
pattern ГруппаПрилРема
{
 Суперлатив0{ ПАДЕЖ:ИМ } : export { РОД ЧИСЛО node:root_node }
}



// мой кот - ленивейший
pattern ПредикатСвязка
{
 sbj=Подлежащее
 v=ДефисКакСвязка : export { node:root_node }
 r=ГруппаПрилРема{ =sbj:РОД =sbj:ЧИСЛО }
} : links
{
 v.{
    <SUBJECT>sbj
    <RHEMA>r
   }
}
: ngrams
{
 sbj_v_score( sbj, r )
}
