using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using SolarixGrammarEngineNET;

namespace enter
{
 public class AuxData
 {
  public string base_form;
  public string yo;
  public string stress;

  public AuxData( string str )
  {
   char[] c = { '-', ' ', '\'', '=', '/', '$', '&', '+', '*' };
   string s = str.Trim();

   if( s.IndexOfAny( "¸¨".ToCharArray() )!=-1 )
    { 
     yo = "\""+s.Replace("^","")+"\"";
    }

   if( s.IndexOf( '^' )!=-1 )
    { 
     stress = "\""+s+"\"";
     s = s.Replace( "^", "" );
    }

   base_form=s; 
   if( s.IndexOfAny( c )!=-1 )
    base_form = "\"" + s.Replace("^", "") + "\"";

   return;
  }

  public string Form()
  {
   System.Text.StringBuilder b = new System.Text.StringBuilder();
   
   if( yo!=null || stress!=null )
    {
     b.AppendFormat( "[{0}", base_form );

     if( yo!=null )
      b.AppendFormat( " yo={0}", yo );

     if( stress!=null )
      b.AppendFormat( " stress={0}", stress );

     b.Append( "]" );
    }
   else
    {
     b.Append( base_form );
    }

   return b.ToString();
  }

  public void WriteAuxEntry( System.IO.StreamWriter file )
  {
   if( yo!=null )
    file.WriteLine( "  aux yo={0}", yo );

   if( stress!=null )
    file.WriteLine( "  aux stress={0}", stress );

   return;
  }

 }
}

