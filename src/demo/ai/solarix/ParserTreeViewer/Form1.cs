using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;

namespace ParserTreeViewer
{
 public partial class Form1 : Form
 {
  public PersistentConfig config;

  public Form1()
  {
   InitializeComponent();
  }

  private void Form1_Load( object sender, EventArgs e )
  {
   config = new PersistentConfig();
   config.Load();

   openFileDialog1.Filter = "XML files (*.xml)|*.xml|All files (*.*)|*.*";
   openFileDialog1.CheckFileExists = true;

   if( !string.IsNullOrEmpty( config.ParsingPath ) )
   {
    openFileDialog1.FileName = config.ParsingPath;
    openFileDialog1.InitialDirectory = System.IO.Path.GetDirectoryName( config.ParsingPath );
   }

   if( openFileDialog1.ShowDialog() == DialogResult.OK )
   {
    LoadParsing( openFileDialog1.FileName );
   }
   else
   {
    Close();
   }
  }


  public ParsedCorpus parsed_corpus;


  private void LoadParsing( string filepath )
  {
   parsed_corpus = new ParsedCorpus();
   parsed_corpus.LoadParsing( filepath );

   config.ParsingPath = filepath;
   config.Save();

   listView1.VirtualListSize = parsed_corpus.Count;

   return;
  }

  private void listView1_RetrieveVirtualItem( object sender, RetrieveVirtualItemEventArgs e )
  {
   string sent = parsed_corpus.GetSentence( e.ItemIndex );
   e.Item = new ListViewItem( sent );
   return;
  }

  private void RenderTree( TreeNode tree_node, SNode sent_node )
  {
   foreach( SNode child in sent_node.children )
   {
    TreeNode child_node = tree_node.Nodes.Add( child.word.word );
    RenderTree( child_node, child );
   }

   return;
  }


  private void listView1_SelectedIndexChanged( object sender, EventArgs e )
  {
   if( listView1.SelectedIndices.Count==1 )
   {
    int index = listView1.SelectedIndices[0];

    // загружаем синтаксическое дерево внутри блока <sentence>, заполняем TreeView
    string xml_data = parsed_corpus.GetXMLData( index );

    XmlDocument xml = new XmlDocument();
    xml.LoadXml( xml_data );
    XmlNode n_sent = xml.DocumentElement.SelectSingleNode( "sentence" );
    Sentence sent = new Sentence( n_sent );

    treeView1.Nodes.Clear();

    TreeNode root_n = treeView1.Nodes.Add( sent.root.word.word );

    RenderTree( root_n, sent.root );    
    root_n.ExpandAll();
   }
  }


 }
}
