using System;
using SolarixLemmatizatorEngineNET;


namespace LemmatizatorTool
{
 class Class1
 {
  [STAThread]
  static void Main(string[] args)
  {
   // http://www.solarix.ru/api/en/sol_LoadLemmatizator.shtml
   IntPtr hEngine = LemmatizatorEngine.sol_LoadLemmatizatorW("..\\..\\..\\..\\..\\..\\..\\..\\bin-windows64\\lemmatizer.db",0);
//   IntPtr hEngine = LemmatizatorEngine.sol_LoadLemmatizatorW("lemmatizer.db",0);
   if( hEngine == IntPtr.Zero )
    {
     Console.WriteLine("Error");
     return;
    }

   System.Text.StringBuilder lemma = new System.Text.StringBuilder();
   lemma.EnsureCapacity(32);

   // http://www.solarix.ru/api/en/sol_GetLemma.shtml
   LemmatizatorEngine.sol_GetLemmaW( hEngine, "галактическими", lemma, 32 );

   String slemma = lemma.ToString();
   Console.WriteLine( "lemma={0}\n", slemma );

   // http://www.solarix.ru/api/en/sol_GetLemmas.shtml
   IntPtr lemmas = LemmatizatorEngine.sol_GetLemmasW( hEngine, "роем" );
   if( lemmas!=(IntPtr)0 )
    {
     // http://www.solarix.ru/api/en/sol_CountLemmas.shtml
     int n = LemmatizatorEngine.sol_CountLemmas( lemmas );

     for( int i=0; i<n; ++i )
      {
       lemma.Length = 0;
       // http://www.solarix.ru/api/en/sol_GetLemmaString.shtml
       LemmatizatorEngine.sol_GetLemmaStringW( lemmas, i, lemma, 32 );
       Console.WriteLine( "lemma[{0}]={1}", i, lemma.ToString() );
      }

     // http://www.solarix.ru/api/en/sol_DeleteLemmas.shtml
     LemmatizatorEngine.sol_DeleteLemmas(lemmas);
    }

   // http://www.solarix.ru/api/en/sol_DeleteLemmatizator.shtml
   LemmatizatorEngine.sol_DeleteLemmatizator(hEngine);

   return;
  }
 }
}
