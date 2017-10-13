// 14.04.2010 - первоначальная реализация
//
// API information: http://www.solarix.ru/for_developers/api/lemmatizator_api.shtml
//
// CD->14.04.2010
// LC->22.10.2012
// --------------

using System;
using System.Runtime.InteropServices;

namespace SolarixLemmatizatorEngineNET
{
 public class LemmatizatorEngine
 {
  #if( DEBUG )
  private const string lemmatizator_dll = "lemmatizatord.dll";
  #else
  private const string lemmatizator_dll = "lemmatizator.dll";
  #endif

  public const int LEME_DEFAULT = 0x00000000;
  public const int LEME_FASTER  = 0x00000001;
  public const int LEME_FASTEST = 0x00000002;

  // http://www.solarix.ru/api/en/sol_LoadLemmatizator.shtml
  [DllImport(lemmatizator_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern System.IntPtr sol_LoadLemmatizatorW( System.String DbPath, int Flags );

  // http://www.solarix.ru/api/en/sol_DeleteLemmatizator.shtml
  [DllImport(lemmatizator_dll, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_DeleteLemmatizator( System.IntPtr hEngine );

  // http://www.solarix.ru/api/en/sol_GetLemma.shtml
  [DllImport(lemmatizator_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_GetLemmaW( System.IntPtr hEngine, string Wordform, System.Text.StringBuilder LemmaBuffer, int BufferLen );

  // http://www.solarix.ru/api/en/sol_GetLemmas.shtml
  [DllImport(lemmatizator_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern System.IntPtr sol_GetLemmasW( System.IntPtr hEngine, string Wordform );

  [DllImport(lemmatizator_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern System.IntPtr sol_LemmatizePhraseW( System.IntPtr hEngine, string Sentence, int Flags, char WordSeparator );

  // http://www.solarix.ru/api/en/sol_CountLemmas.shtml
  [DllImport(lemmatizator_dll, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_CountLemmas( System.IntPtr hList );

  // http://www.solarix.ru/api/en/sol_GetLemmaString.shtml
  [DllImport(lemmatizator_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_GetLemmaStringW( System.IntPtr hList, int Index, System.Text.StringBuilder LemmaBuffer, int BufferLen );

  // http://www.solarix.ru/api/en/sol_DeleteLemmas.shtml
  [DllImport(lemmatizator_dll, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_DeleteLemmas( System.IntPtr hList );

  public LemmatizatorEngine() {}
 };

}
