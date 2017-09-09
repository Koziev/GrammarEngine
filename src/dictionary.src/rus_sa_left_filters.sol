
colloc_filter Filter_Particle_TO language=Russian
{
 if context { "-" ["то"{ class:частица }] }
  then accept
}


colloc_filter Filter_To1 language=Russian
{
 if context { ',' [ЧАСТИЦА:ТО{}] }
   then reject
}

colloc_filter Filter_To2 language=Russian
{
 if context { ',' [МЕСТОИМ_СУЩ:ТО{}] }
  then reject
}


 
// СТАТЬ и ЗНАТЬ после модальных - только как инфинитивы
colloc_filter Filter_Modal_Inf2 language=Russian
{
 if context { *:*{ модальный } ['стать'{ class:инфинитив }] }
  then accept
}   

colloc_filter Filter_Modal_Inf3 language=Russian
{
 if context { *:*{ модальный } ['знать'{ class:инфинитив }] }
  then accept
}





colloc_filter Filter_Because1 language=Russian
{
 if context { СОЮЗ:ТАК{} [СОЮЗ:КАК{}] }
  then accept
}


colloc_filter Filter_Because2 language=Russian
{
 if context { СОЮЗ:ПОТОМУ{} [СОЮЗ:ЧТО{}] }
  then accept
}


colloc_filter Filter_So1 language=Russian
{
 if context { ',' [СОЮЗ:ТО{}] }
  then accept
}



// это были морозные, но солнечные дни
colloc_filter Были_1 language=Russian
{
 if context { 'это' ['были'{class:глагол}] }
  then accept
}


// за окном были уже сумерки
colloc_filter Были_1 language=Russian
{
 if context { существительное:*{} ['были'{class:существительное}] }
  then reject
}

// мы были неподвластны страху
colloc_filter Были_1 language=Russian
{
 if context { местоимение:*{} ['были'{class:существительное}] }
  then reject
}
