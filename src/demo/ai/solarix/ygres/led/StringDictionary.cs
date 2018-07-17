using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using SolarixGrammarEngineNET;

namespace enter
{
 class StringDictionary : DictionaryBase
 {
   public String this[ String key ]  {
      get  {
         return( (String) Dictionary[key] );
      }
      set  {
         Dictionary[key] = value;
      }
   }

   public ICollection Keys  {
      get  {
         return( Dictionary.Keys );
      }
   }

   public ICollection Values  {
      get  {
         return( Dictionary.Values );
      }
   }

   public void Add( String key, String value )  {
      Dictionary.Add( key, value );
   }

   public bool Contains( String key )  {
      return( Dictionary.Contains( key ) );
   }

   public void Remove( String key )  {
      Dictionary.Remove( key );
   }
 }

}