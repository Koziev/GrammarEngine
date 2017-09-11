// CD->17.05.2009
// LC->27.04.2010

automat sg
{
 #define RomajiNoun(x) entry x : JAP_NOUN { JAP_FORM:ROMAJI }

 RomajiNoun( Kolya )
 RomajiNoun( Rosa )

}
