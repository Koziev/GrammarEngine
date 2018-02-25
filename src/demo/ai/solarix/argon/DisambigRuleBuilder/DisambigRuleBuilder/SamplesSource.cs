using System;
using System.Collections.Generic;
using System.Text;



abstract class SampleSource
{
 public abstract IEnumerable<string> Samples();
 public abstract void Rewind();
}


// Вариант поставщика сэмплов - они вбиты хардкодом в теле класса.
class InlineSampleSource : SampleSource
{
 List<string> samples;

 public InlineSampleSource()
 {
  samples = new List<string>();

  samples.Add( "Я сплю." );
  //  samples.Add( "" );
 }

 public override IEnumerable<string> Samples() { return samples; }
 public override void Rewind() { }
}


// Вариант поставщика сэмплов - они читаются их файла с тестами для синтана.
class SyntanSamples : SampleSource
{
 string filepath;
 System.IO.StreamReader rdr;
 bool is_xml;

 public SyntanSamples( string _filepath )
 {
  filepath = _filepath;

  rdr = new System.IO.StreamReader( filepath );
  string header = rdr.ReadLine();
  is_xml = header.Contains( "?xml" );

  Rewind();
 }

 public override void Rewind()
 {
  rdr = new System.IO.StreamReader( filepath );
 }

 public override IEnumerable<string> Samples()
 {
  bool allow_fuzzy = false;
  bool allow_reco = false;
  bool allow_incomplete = false;

  while( !rdr.EndOfStream )
  {
   string line = rdr.ReadLine();
   if( line == null )
    break;

   if( line.Length == 0 )
    continue;

   if( is_xml )
   {
    if( line.StartsWith( "<text>" ) && line.EndsWith( "</text>" ) )
    {
     line = line.Substring( 6, line.Length - 13 );
     line = System.Web.HttpUtility.HtmlDecode( line );
     yield return line;
    }
   }
   else
   {
    if( line == "#fuzzyon" )
     allow_fuzzy = true;
    else if( line == "#fuzzyoff" )
     allow_fuzzy = false;
    else if( line == "#allow_reco" )
     allow_reco = true;
    else if( line == "#disallow_reco" )
     allow_reco = false;
    else if( line == "#allow_incomplete" )
     allow_incomplete = true;
    else if( line == "#disallow_incomplete" )
     allow_incomplete = false;
    else if( line == "$begin" )
    {
     line = rdr.ReadLine();

     if( !allow_fuzzy && !allow_reco && !allow_incomplete )
      yield return line;
    }
   }
  }

  rdr.Close();
 }

}



// Вариант поставщика сэмплов - они читаются их файла, одна строка=сэмпл
class PlainSamples : SampleSource
{
 string filepath;
 System.IO.StreamReader rdr;

 public PlainSamples( string _filepath )
 {
  filepath = _filepath;
  rdr = new System.IO.StreamReader( filepath );
 }

 public override void Rewind()
 {
  rdr = new System.IO.StreamReader( filepath );
 }

 public override IEnumerable<string> Samples()
 {
  while( !rdr.EndOfStream )
  {
   string line = rdr.ReadLine();
   if( line == null )
    break;

   yield return line;
  }

  rdr.Close();
 }
}

