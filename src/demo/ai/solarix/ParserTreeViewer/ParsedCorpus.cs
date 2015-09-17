using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ParserTreeViewer
{
 public class ParsedCorpus
 {
  private string corpus_path;
  private string index_path;
  private List<long> sent2pos;

  private System.IO.FileStream corpus_rdr;

  public ParsedCorpus() { }



  static byte[] read_buffer;

  static string ReadLine( System.IO.FileStream rdr )
  {
   if( read_buffer == null )
   {
    read_buffer = new byte[65000];
   }

   read_buffer[0] = 0;
   int line_len = 0;
   int bufpos = 0;
   while( true )
   {
    int b = rdr.ReadByte();
    if( b == -1 )
    {
     break;
    }
    else if( b == '\r' )
    {
     b = rdr.ReadByte();
     break;
    }
    else if( b == '\n' )
    {
     break;
    }
    else
    {
     read_buffer[bufpos++] = (byte)b;
     line_len++;
    }
   }

   return System.Text.Encoding.UTF8.GetString( read_buffer, 0, line_len );
  }



  public void LoadParsing( string _corpus_path )
  {
   corpus_path = _corpus_path;
   sent2pos = new List<long>();

   // Читаем файл filepath построчно, запоминая позиции узлов <sentence ...> в особом
   // индексном файле

   index_path = System.IO.Path.Combine( System.IO.Path.GetTempPath(), System.IO.Path.GetFileNameWithoutExtension( corpus_path ) + ".XMLINDEX" );

   // проверить, если такой файл уже существует и создан после файла парсинга, то можно просто загрузить его содержимое.
   if( System.IO.File.Exists( index_path ) && System.IO.File.GetLastWriteTime( corpus_path ) < System.IO.File.GetLastWriteTime( index_path ) )
   {
    using( System.IO.BinaryReader rdr = new System.IO.BinaryReader( System.IO.File.Open( index_path, System.IO.FileMode.Open ) ) )
    {
     long filesize = rdr.BaseStream.Length;
     long nrec = filesize / sizeof( long );
     long[] recs = new long[nrec];

     for( long i = 0; i < nrec; ++i )
     {
      sent2pos.Add( rdr.ReadInt64() );
     }
    }
   }
   else
   {
    using( System.IO.BinaryWriter index_wrt = new System.IO.BinaryWriter( System.IO.File.Open( index_path, System.IO.FileMode.Create ) ) )
    {
     using( System.IO.FileStream rdr = new System.IO.FileStream( corpus_path, System.IO.FileMode.Open ) )
     {
      while( true )
      {
       long pos = rdr.Position;
       string line = ReadLine( rdr );
       if( string.IsNullOrEmpty( line ) )
       {
        continue;
       }

       if( line == "</parsing>" )
        break;

       if( line.StartsWith( "<sentence" ) )
       {
        index_wrt.Write( pos );
        sent2pos.Add( pos );
       }
      }
     }
    }
   }

   return;
  }

  public int Count { get { return sent2pos.Count; } }

  public string GetSentence( int index )
  {
   if( corpus_rdr == null )
    corpus_rdr = new System.IO.FileStream( corpus_path, System.IO.FileMode.Open );

   corpus_rdr.Position = sent2pos[index];

   // Загружаем текст предложения внутри узла <text>...</text>

   ReadLine( corpus_rdr ); // пропускаем тег <sentence...>
   string text_xml = ReadLine( corpus_rdr );

   if( text_xml.StartsWith( "<text>" ) && text_xml.EndsWith( "</text>" ) )
   {
    return text_xml.Substring( 6, text_xml.Length - 6 - 7 );
   }
   else
   {
    return "";
   }

  }

  public string GetXMLData( int index )
  {
   if( corpus_rdr == null )
    corpus_rdr = new System.IO.FileStream( corpus_path, System.IO.FileMode.Open );

   corpus_rdr.Position = sent2pos[index];

   System.Text.StringBuilder b = new StringBuilder();

   b.Append( "<?xml version='1.0' encoding='utf-8' ?>" );
   b.Append( "<dataroot>" );

   while( true )
   {
    string str = ReadLine( corpus_rdr );
    b.AppendLine( str );
    if( str.StartsWith( "</sentence" ) )
     break;
   }

   b.Append( "</dataroot>" );

   return b.ToString();
  }
 }
}
