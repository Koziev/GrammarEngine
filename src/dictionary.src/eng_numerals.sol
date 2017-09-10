// CD->01.01.2009
// LC->03.01.2009
// --------------

automat sg
{
 #define num(x,y,n=NULL) \
  #begin
   entry x : ENG_NUMERAL
   { 
    NUMERAL_FORM { x y }
    #if n!=NULL 
    NUMERAL_FORM:ORDINAL { n }
    #endif
   }
  #end
 

 num( ONE, FIRST, "1st" )
 num( TWO, SECOND, "2nd" )
 num( THREE, THIRD, "3rd" )
 num( FOUR, FOURTH, "4th" )
 num( FIVE, FIFTH, "5th" )
 num( SIX, SIXTH, "6th" )
 num( SEVEN, SEVENTH, "7th" )
 num( EIGHT, EIGHTH, "8th" )
 num( NINE, NINTH, "9th" )
 num( TEN, TENTH, "10th" )
 num( ELEVEN, ELEVENTH, "11th" )
 num( TWELVE, TWELFTH, "12th" )
 num( THIRTEEN, THIRTEENTH, "13th" )
 num( FOURTEEN, FOURTEENTH, "14th" )
 num( FIFTEEN, FIFTEENTH, "15th" )
 num( SIXTEEN, SIXTEENTH, "16th" )
 num( SEVENTEEN, SEVENTEENTH, "17th" )
 num( EIGHTEEN, EIGHTEENTH, "18th" )
 num( NINETEEN, NINETEENTH, "19th" )
 num( TWENTY, TWENTIETH, "20th" )
 num( THIRTY, THIRTIETH, "30th" )
 num( FORTY, FORTIETH, "40th" )
 num( FIFTY, FIFTIETH, "50th" )
 num( SIXTY, SIXTIETH, "60th" )
 num( SEVENTY, SEVENTIETH, "70th" )
 num( EIGHTY, EIGHTIETH, "80th" )
 num( NINETY, NINETIETH, "90th" )
 num( HUNDRED, HUNDREDTH, "100th" )
 num( thousand, thousandth )
 num( million, millionth )
}


