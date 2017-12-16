// CD->02.08.2011
// LC->02.08.2011

automat sg
{
 #define Member2Class( M, C ) link ИНФИНИТИВ:M{} <в_класс> ИНФИНИТИВ:C{}

 Member2Class( завтракать, кушать )
 Member2Class( полдничать, кушать )
 Member2Class( обедать, кушать )
 Member2Class( ужинать, кушать )
}

