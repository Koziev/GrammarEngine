
#pragma floating off

#define _BEG beth:begin{}
#define _END beth:end{}

// =================================================
// ------- ПАТТЕРНЫ САМОГО ВЕРХНЕГО УРОВНЯ ---------
// =================================================

pattern language=Russian
{
 _BEG
 ПредложСТерм
 _END
}

pattern language=Russian
{
 _BEG
 НаучнНазв
 _END
}


pattern language=Russian
{
 _BEG
 КраткОтвет
 _END
}

pattern language=Russian
{
 ПредложСТерм
}



pattern incomplete language=Russian
{
 Предлож1
}

pattern incomplete language=Russian
{
 Сказуемое
}
