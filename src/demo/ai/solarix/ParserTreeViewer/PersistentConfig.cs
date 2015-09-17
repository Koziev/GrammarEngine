using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

public sealed class PersistentConfig
{
 public string ParsingPath;

 string path;
 public PersistentConfig()
 {
  path = System.IO.Path.Combine( Environment.GetFolderPath( Environment.SpecialFolder.ApplicationData ), "ParserTreeViewer.cfg" );
 }

 public void Load()
 {
  if( System.IO.File.Exists( path ) )
  {
   XmlDocument xml = new XmlDocument();
   xml.Load( path );

   XmlNode n = xml.SelectSingleNode( "/config/ParsingPath" );
   if( n != null )
    ParsingPath = n.InnerText;
  }

  return;
 }

 public void Save()
 {
  using( System.IO.StreamWriter wrt = new System.IO.StreamWriter( path ) )
  {
   wrt.WriteLine( "<?xml version=\"1.0\" encoding=\"utf-8\"?>" );
   wrt.WriteLine( "<config>" );
   wrt.WriteLine( "<ParsingPath><![CDATA[{0}]]></ParsingPath>", ParsingPath );
   wrt.WriteLine( "</config>" );
  }

  return;
 }
}
