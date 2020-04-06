automat sg
{
 link generator ГЛАГОЛ <в_инфинитив> ИНФИНИТИВ -> <в_предикат>
 link generator ПРИЛАГАТЕЛЬНОЕ <в_инфинитив> ИНФИНИТИВ -> <в_прил>
 link generator ДЕЕПРИЧАСТИЕ <в_инфинитив> ИНФИНИТИВ -> <в_деепричастие>
 link generator ПРИЛАГАТЕЛЬНОЕ <в_сущ> СУЩЕСТВИТЕЛЬНОЕ -> <в_прил>
 link generator НАРЕЧИЕ <в_инфинитив> ИНФИНИТИВ -> <в_наречие>

 // Считаем, что синонимические связи всегда обратимы
 link generator ИНФИНИТИВ <synonym> ИНФИНИТИВ -> <synonym>
 link generator СУЩЕСТВИТЕЛЬНОЕ <synonym> СУЩЕСТВИТЕЛЬНОЕ -> <synonym>
 link generator ПРИЛАГАТЕЛЬНОЕ <synonym> ПРИЛАГАТЕЛЬНОЕ -> <synonym>
 link generator НАРЕЧИЕ <synonym> НАРЕЧИЕ -> <synonym>
 link generator ДЕЕПРИЧАСТИЕ <synonym> ДЕЕПРИЧАСТИЕ -> <synonym>

 // Обратимы и "половые синонимы" КОТ-КОШКА
 link generator СУЩЕСТВИТЕЛЬНОЕ <sex_synonym> СУЩЕСТВИТЕЛЬНОЕ -> <sex_synonym>

 link generator НАРЕЧИЕ <в_прил> ПРИЛАГАТЕЛЬНОЕ -> <в_наречие>
 link generator НАРЕЧИЕ <в_сущ> СУЩЕСТВИТЕЛЬНОЕ -> <в_наречие>
 link generator СУЩЕСТВИТЕЛЬНОЕ <в_прил> ПРИЛАГАТЕЛЬНОЕ -> <в_сущ>
 link generator СУЩЕСТВИТЕЛЬНОЕ <в_наречие> НАРЕЧИЕ -> <в_сущ>

 
 link generator ПРИЛАГАТЕЛЬНОЕ <antonym> ПРИЛАГАТЕЛЬНОЕ -> <antonym>
 link generator СУЩЕСТВИТЕЛЬНОЕ <antonym> СУЩЕСТВИТЕЛЬНОЕ -> <antonym>
 link generator НАРЕЧИЕ <antonym> НАРЕЧИЕ -> <antonym>
 link generator ИНФИНИТИВ <antonym> ИНФИНИТИВ -> <antonym>
 link generator ГЛАГОЛ <antonym> ГЛАГОЛ -> <antonym>
 link generator ДЕЕПРИЧАСТИЕ <antonym> ДЕЕПРИЧАСТИЕ -> <antonym>


 link generator Существительное <в_класс> Существительное -> <член_класса>
 link generator Существительное <член_класса> Существительное -> <в_класс>
 
 link generator Существительное <уменьш_ласк> Существительное -> <нейтрал>
 link generator Прилагательное <уменьш_ласк> Прилагательное -> <нейтрал>
 link generator Наречие <уменьш_ласк> Наречие -> <нейтрал>

 link generator Существительное <груб> Существительное -> <нейтрал>
 link generator Прилагательное <груб> Прилагательное -> <нейтрал>
 link generator Наречие <груб> Наречие -> <нейтрал>
 
 link generator Существительное <увелич> Существительное -> <нейтрал>
 link generator Прилагательное <увелич> Прилагательное -> <нейтрал>
 link generator Наречие <увелич> Наречие -> <нейтрал>


 link generator СУЩЕСТВИТЕЛЬНОЕ <cognate> ИНФИНИТИВ -> <cognate>
 link generator СУЩЕСТВИТЕЛЬНОЕ <cognate> СУЩЕСТВИТЕЛЬНОЕ -> <cognate>
 link generator СУЩЕСТВИТЕЛЬНОЕ <cognate> ПРИЛАГАТЕЛЬНОЕ -> <cognate>
 link generator СУЩЕСТВИТЕЛЬНОЕ <cognate> НАРЕЧИЕ -> <cognate>
 link generator СУЩЕСТВИТЕЛЬНОЕ <cognate> ДЕЕПРИЧАСТИЕ -> <cognate>
 link generator СУЩЕСТВИТЕЛЬНОЕ <cognate> ПРЕФИКС_СОСТАВ_ПРИЛ -> <cognate>
 link generator СУЩЕСТВИТЕЛЬНОЕ <cognate> ГЛАГОЛ -> <cognate>

}

