// CD->02.04.2011
// LC->01.06.2011

automat la
{
 recognition OrdinalNumbers language=French
 {
  if "[[:digit:]]*e" then FR_NUMERAL:"???" { FR_NUMERAL_FORM:ORDINAL FR_GENRE:MASCULINE }  // le 9e étage
 } 
 
 
 recognition OrdinalNumbers language=French
 {
  if "[[:digit:]]*e" then FR_NUMERAL:"???" { FR_NUMERAL_FORM:ORDINAL FR_GENRE:FEMININE }  // la 8e armée britannique; la 2e brigade
 } 
 
}
