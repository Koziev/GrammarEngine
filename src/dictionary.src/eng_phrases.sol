// Forward declarations of English phrasal entries
//
// CD->13.01.2010
// CD->08.04.2010

#define Phrase(E,Pivot) phrase E { language:English pivot Pivot }

automat sg
{
 Phrase( "dirt road", "dirt|[road]" )
 Phrase( "direct current", "direct|[current]" )
 Phrase( "alternating current", "alternating|[current]" )
 Phrase( "public enemy", "public|[enemy]" )

 // ------------------------------------------------------------- 
 // Тестовая запись в тезаурусе - для проверки цепочки
 // КОМПИЛЯЦИЯ - ЭКСПОРТ В SQL - ЗАГРУЗКА В БД
 phrase @ TestPhrase0 { language:Neutral }
 phrase @ TestPhrase1 { language:Neutral }

 link complex @ TestPhrase0 <to_russian> { @ TestPhrase1 }
 // ------------------------------------------------------------- 
}
