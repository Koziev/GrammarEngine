using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

class String2Vector
{
 string vectors_path;
 System.IO.StreamReader rdr;

 int vector_len;
 int n_key;
 Dictionary<string, string> key2vector;

 public String2Vector( string _vectors_path )
 {
  vectors_path = _vectors_path;
  key2vector = new Dictionary<string, string>();

  rdr = new System.IO.StreamReader( vectors_path );

  string line0 = rdr.ReadLine().Trim();
  n_key = int.Parse( line0.Split( ' ' )[0] );
  vector_len = int.Parse( line0.Split( ' ' )[1] );

  for( int i = 0; i < n_key; ++i )
  {
   string line = rdr.ReadLine().Trim();
   int space_pos = line.IndexOf( ' ' );
   string key = line.Substring( 0, space_pos );
   string vec = line.Substring( space_pos + 1 );
   key2vector.Add( key, vec );
  }

 }

 public int GetVectorLength()
 {
  return vector_len;
 }

 public double[] GetVector( string key )
 {
  double[] v = new double[GetVectorLength()];

  string str_vector = null;
  if( !key2vector.TryGetValue( key, out str_vector ) )
  {
   Array.Clear( v, 0, v.Length );
  }
  else
  {
   string[] toks = str_vector.Split( ' ' );
   for( int j = 0; j < toks.Length; ++j )
    v[j] = double.Parse( toks[j], System.Globalization.CultureInfo.InvariantCulture );
  }

  return v;
 }
}
