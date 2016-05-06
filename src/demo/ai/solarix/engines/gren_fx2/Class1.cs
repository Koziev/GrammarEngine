//
// CD->12.12.2011
// LC->12.01.2013
// --------------

using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using Microsoft.Win32.SafeHandles;


namespace SolarixGrammarEngineNET
{
 public struct CoordPair
 {
  public int CoordID, StateID;

  public override bool Equals( object obj )
  {
   CoordPair y = (CoordPair)obj;
   return CoordID == y.CoordID && StateID == y.StateID;
  }

  public override int GetHashCode()
  {
   return CoordID ^ ( StateID << 10 );
  }
 }


 // Обращаю внимание, что дескриптор hNode НЕ НАДО ОСВОБОЖДАТЬ, поэтому IDisposable не нужен
 public class SyntaxTreeNode
 {
  private readonly GrammarEngine2 gren;
  public readonly IntPtr hNode;

  // TODO: переделать на ленивую инициализацию в get, set сделать приватным.
  public List<SyntaxTreeNode> leafs;

  public SyntaxTreeNode( GrammarEngine2 _gren, IntPtr _hNode )
  {
   gren = _gren;
   hNode = _hNode;

   int nleaf = GrammarEngine.sol_CountLeafs( hNode );
   leafs = new List<SyntaxTreeNode>();
   for( int i = 0; i < nleaf; ++i )
    leafs.Add( new SyntaxTreeNode( gren, GrammarEngine.sol_GetLeaf( hNode, i ) ) );

   return;
  }

  public string GetWord()
  {
   return GrammarEngine.sol_GetNodeContentsFX( hNode );
  }

  public override string ToString()
  {
   return GetWord();
  }


  public int GetWordPosition()
  {
   return GrammarEngine.sol_GetNodePosition( hNode );
  }

  public int GetCoordState( int CoordID )
  {
   return GrammarEngine.sol_GetNodeCoordState( hNode, CoordID );
  }

  public int GetEntryID()
  {
   return GrammarEngine.sol_GetNodeIEntry( gren.GetEngineHandle(), hNode );
  }

  public int GetVersionEntryID( int version_index )
  {
   return GrammarEngine.sol_GetNodeVerIEntry( gren.GetEngineHandle(), hNode, version_index );
  }


  public int GetLinkType( int LeafIndex )
  {
   return GrammarEngine.sol_GetLeafLinkType( hNode, LeafIndex );
  }


  // Number of versions of morphological analysis
  public int VersionCount() { return GrammarEngine.sol_GetNodeVersionCount( gren.GetEngineHandle(), hNode ); }

  public List<CoordPair> GetPairs()
  {
   List<CoordPair> res = new List<CoordPair>();

   int n = GrammarEngine.sol_GetNodePairsCount( hNode );
   if( n > 0 )
   {
    for( int i = 0; i < n; ++i )
    {
     CoordPair p;
     p.CoordID = GrammarEngine.sol_GetNodePairCoord( hNode, i );
     p.StateID = GrammarEngine.sol_GetNodePairState( hNode, i );
     res.Add( p );
    }
   }

   return res;
  }

  public bool Contains( CoordPair p )
  {
   return SolarixGrammarEngineNET.GrammarEngine.sol_GetNodeCoordPair( hNode, p.CoordID, p.StateID ) == 1;
  }


  public bool VersionContains( int version_index, CoordPair p )
  {
   return SolarixGrammarEngineNET.GrammarEngine.sol_GetNodeVerCoordPair( hNode, version_index, p.CoordID, p.StateID ) == 1;
  }

  public override int GetHashCode()
  {
   return hNode.GetHashCode();
  }

  public override bool Equals( object obj )
  {
   if( obj == null )
    return false;

   return hNode.Equals( ( (SyntaxTreeNode)obj ).hNode );
  }
 }


 // [SecurityPermission(SecurityAction.InheritanceDemand, UnmanagedCode = true)]
 // [SecurityPermission(SecurityAction.Demand, UnmanagedCode = true)]
 internal class AnalysisResultsSafeHandle : SafeHandleZeroOrMinusOneIsInvalid
 {
  bool release_handle = true;
  public AnalysisResultsSafeHandle( IntPtr _handle )
   : base( true )
  {
   handle = _handle;
  }

  public AnalysisResultsSafeHandle( IntPtr _handle, bool _release_handle )
   : base( true )
  {
   handle = _handle;
   release_handle = _release_handle;
  }

  public IntPtr GetHandle() { return handle; }

  //[ReliabilityContract(Consistency.WillNotCorruptState, Cer.MayFail)]
  override protected bool ReleaseHandle()
  {
   if( release_handle )
    SolarixGrammarEngineNET.GrammarEngine.sol_DeleteResPack( handle );

   handle = IntPtr.Zero;
   return true;
  }
 }


 public class AnalysisResults : IDisposable
 {
  private readonly AnalysisResultsSafeHandle hPack; // дескриптор с блоком результатов, его нужно освобождать
  private readonly List<SyntaxTreeNode> nodes;

  public AnalysisResults( GrammarEngine2 gren, IntPtr _hPack )
  {
   hPack = new AnalysisResultsSafeHandle( _hPack );
   nodes = new List<SyntaxTreeNode>();

   int n = SolarixGrammarEngineNET.GrammarEngine.sol_CountRoots( hPack.DangerousGetHandle(), 0 );
   for( int i = 0; i < n; ++i )
   {
    SyntaxTreeNode node = new SyntaxTreeNode( gren, SolarixGrammarEngineNET.GrammarEngine.sol_GetRoot( hPack.DangerousGetHandle(), 0, i ) );
    nodes.Add( node );
   }
  }

  public AnalysisResults( GrammarEngine2 gren, IntPtr _hPack, bool release_handle )
  {
   hPack = new AnalysisResultsSafeHandle( _hPack, release_handle );
   nodes = new List<SyntaxTreeNode>();

   int n = SolarixGrammarEngineNET.GrammarEngine.sol_CountRoots( hPack.DangerousGetHandle(), 0 );
   for( int i = 0; i < n; ++i )
   {
    SyntaxTreeNode node = new SyntaxTreeNode( gren, SolarixGrammarEngineNET.GrammarEngine.sol_GetRoot( hPack.DangerousGetHandle(), 0, i ) );
    nodes.Add( node );
   }
  }


  public int Count { get { return nodes.Count; } }

  public bool IsNull() { return hPack.GetHandle() == IntPtr.Zero; }
  public IntPtr GetHandle() { return hPack.GetHandle(); }

  public SyntaxTreeNode this[int index]
  { get { return nodes[index]; } }

  public void Dispose()
  {
   Dispose( true );
   GC.SuppressFinalize( this );
  }

  //[SecurityPermission(SecurityAction.Demand, UnmanagedCode = true)]
  protected virtual void Dispose( bool disposing )
  {
   if( hPack != null && !hPack.IsInvalid )
   {
    hPack.Dispose();
   }
  }
 }




 public class ThesaurusLinks : IDisposable
 {
  private readonly IntPtr hEngine;
  private IntPtr hList;

  public ThesaurusLinks( IntPtr _hEngine, IntPtr _hList ) { hEngine = _hEngine; hList = _hList; }

  public void Dispose()
  {
   Dispose( true );
   GC.SuppressFinalize( this );
  }

  //[SecurityPermission(SecurityAction.Demand, UnmanagedCode = true)]
  protected virtual void Dispose( bool disposing )
  {
   if( hList != IntPtr.Zero )
   {
    SolarixGrammarEngineNET.GrammarEngine.sol_DeleteLinksInfo( hEngine, hList );
    hList = IntPtr.Zero;
   }
  }

  public int Count()
  {
   return SolarixGrammarEngineNET.GrammarEngine.sol_LinksInfoCount( hEngine, hList );
  }

  public int GetEntry2( int index )
  {
   return SolarixGrammarEngineNET.GrammarEngine.sol_LinksInfoEKey2( hEngine, hList, index );
  }

  public int GetLinkID( int index )
  {
   return SolarixGrammarEngineNET.GrammarEngine.sol_LinksInfoID( hEngine, hList, index );
  }

  public string GetTags( int index )
  {
   return SolarixGrammarEngineNET.GrammarEngine.sol_LinksInfoTagsTxtFX( hEngine, hList, index );
  }
 }

 public class WordProjections : IDisposable
 {
  private IntPtr _hList;
  private readonly IntPtr _hEngine;

  public WordProjections( IntPtr hEngine, IntPtr hList ) { _hEngine = hEngine; _hList = hList; }

  public void Dispose()
  {
   Dispose( true );
   GC.SuppressFinalize( this );
  }

  protected virtual void Dispose( bool disposing )
  {
   if( _hList != IntPtr.Zero )
   {
    GrammarEngine.sol_DeleteProjections( _hList );
    _hList = IntPtr.Zero;
   }
  }

  public int Count
  {
   get
   {
    return _hList == IntPtr.Zero ? 0 : GrammarEngine.sol_CountProjections( _hList );
   }
  }

  public int GetEntryKey( int i )
  {
   return GrammarEngine.sol_GetIEntry( _hList, i );
  }

  public int GetCoordState( int Index, int CoordID )
  {
   return GrammarEngine.sol_GetProjCoordState( _hEngine, _hList, Index, CoordID );
  }
 }


 public class TextSegmenter : IDisposable
 {
  private readonly GrammarEngine2 gren;
  private IntPtr hObject;

  public TextSegmenter( GrammarEngine2 _gren, IntPtr _hObject )
  {
   gren = _gren;
   hObject = _hObject;
  }

  public void Dispose()
  {
   Dispose( true );
   GC.SuppressFinalize( this );
  }

  protected virtual void Dispose( bool disposing )
  {
   if( hObject != IntPtr.Zero )
   {
    GrammarEngine.sol_DeleteSentenceBroker( hObject );
    hObject = IntPtr.Zero;
   }
  }

  public string ReadSentence()
  {
   if( GrammarEngine.sol_FetchSentence( hObject ) >= 0 )
    return GrammarEngine.sol_GetFetchedSentenceFX( hObject );
   else
    return null;
  }
 }

 public class GrammarEngine2 : IDisposable
 {
  public GrammarEngine2() { }

  private IntPtr _hEngine = IntPtr.Zero;

  public GrammarEngine2( IntPtr hEngine ) { _hEngine = hEngine; }

  public IntPtr GetEngineHandle() { return _hEngine; }

  /// <summary>
  /// Connect to the dictionary database using the information in XML configuration file 
  /// </summary>
  /// <param name="DictionaryXmlPath">Configuration file path (read about it: http://www.solarix.ru/for_developers/docs/russian-grammatical-dictionary-configuration.shtml)</param>
  /// <param name="LazyLexicon">Word entries are loaded by demand if true</param>
  public void Load( string DictionaryXmlPath, bool LazyLexicon )
  {
   GrammarEngine.EngineInstanceFlags flags = GrammarEngine.EngineInstanceFlags.SOL_GREN_DEFAULT;
   if( LazyLexicon ) flags = GrammarEngine.EngineInstanceFlags.SOL_GREN_LAZY_LEXICON;

   _hEngine = GrammarEngine.sol_CreateGrammarEngineW( "" );
   int rc = GrammarEngine.sol_LoadDictionaryExW( _hEngine, DictionaryXmlPath, flags );

   if( rc!=1 )
   {
    string msg = GrammarEngine.sol_GetErrorFX( _hEngine );
    throw new ApplicationException( string.Format( "Error has occured when connecting the dictionary database by {0}: {1}", DictionaryXmlPath, msg ) );
   }

   return;
  }

  public void Dispose()
  {
   Dispose( true );
   GC.SuppressFinalize( this );
  }

  protected virtual void Dispose( bool disposing )
  {
   if( _hEngine != IntPtr.Zero )
   {
    GrammarEngine.sol_DeleteGrammarEngine( _hEngine );
    _hEngine = IntPtr.Zero;
   }
  }

  public WordProjections FindWordForm( string wordform )
  {
   return new WordProjections( _hEngine, GrammarEngine.sol_ProjectWord( _hEngine, wordform, 0 ) );
  }

  public int CountWordEntries()
  {
   return GrammarEngine.sol_CountEntries( _hEngine );
  }


  public int GetEntryClass( int id_entry )
  { return GrammarEngine.sol_GetEntryClass( _hEngine, id_entry ); }

  public string GetEntryName( int id_entry )
  { return GrammarEngine.sol_GetEntryNameFX( _hEngine, id_entry ); }


  public List<int> GetLinks( int id_entry, int link_type )
  {
   List<int> res = new List<int>();

   IntPtr hList = GrammarEngine.sol_ListLinksTxt( _hEngine, id_entry, link_type, 0 );
   if( hList != IntPtr.Zero )
   {
    int n = GrammarEngine.sol_LinksInfoCount( _hEngine, hList );
    for( int i = 0; i < n; ++i )
    {
     int id_entry2 = GrammarEngine.sol_LinksInfoEKey2( _hEngine, hList, i );
     res.Add( id_entry2 );
    }

    GrammarEngine.sol_DeleteLinksInfo( _hEngine, hList );
   }

   return res;
  }

  public List<int> GetPhrasalLinks( int id_phrase, int link_type )
  {
   List<int> res = new List<int>();

   IntPtr hList = GrammarEngine.sol_ListLinksTxt( _hEngine, id_phrase, link_type, 1 );
   if( hList != IntPtr.Zero )
   {
    int n = GrammarEngine.sol_LinksInfoCount( _hEngine, hList );
    for( int i = 0; i < n; ++i )
    {
     int id_phrase2 = GrammarEngine.sol_LinksInfoEKey2( _hEngine, hList, i );
     res.Add( id_phrase2 );
    }

    GrammarEngine.sol_DeleteLinksInfo( _hEngine, hList );
   }

   return res;
  }


  public int FindEntry( string EntryName, int PartOfSpeech )
  {
   return GrammarEngine.sol_FindEntry( _hEngine, EntryName, PartOfSpeech, -1 );
  }

  public int FindPartOfSpeech( string PartOfSpeechName )
  {
   return GrammarEngine.sol_FindClass( _hEngine, PartOfSpeechName );
  }

  public int FindPhrase( string PhraseText, bool CaseSensitive )
  {
   return GrammarEngine.sol_FindPhrase( _hEngine, PhraseText, CaseSensitive ? 1 : 0 );
  }

  public string GetPhraseText( int PhraseID )
  {
   return GrammarEngine.sol_GetPhraseTextFX( _hEngine, PhraseID );
  }

  public int FindCoord( string CoordName )
  {
   return GrammarEngine.sol_FindEnum( _hEngine, CoordName );
  }

  public int FindState( int CoordID, string StateName )
  {
   return GrammarEngine.sol_FindEnumState( _hEngine, CoordID, StateName );
  }


  public int GetEntryAttrState( int EntryID, int CoordID )
  {
   return GrammarEngine.sol_GetEntryCoordState( _hEngine, EntryID, CoordID );
  }


  public System.Collections.Generic.List<string> GenerateWordforms( int EntryID, System.Collections.Generic.List<int> CoordID, System.Collections.Generic.List<int> StateID )
  {
   int npairs = CoordID.Count;
   int[] pairs = new int[npairs * 2];
   for( int i = 0, j = 0; i < npairs; ++i )
   {
    pairs[j++] = (int)CoordID[i];
    pairs[j++] = (int)StateID[i];
   }

   System.Collections.Generic.List<string> res = new System.Collections.Generic.List<string>();
   IntPtr hStr = GrammarEngine.sol_GenerateWordforms( _hEngine, EntryID, npairs, pairs );
   if( hStr != (IntPtr)0 )
   {
    int nstr = GrammarEngine.sol_CountStrings( hStr );
    for( int k = 0; k < nstr; ++k )
     res.Add( GrammarEngine.sol_GetStringFX( hStr, k ) );

    GrammarEngine.sol_DeleteStrings( hStr );
   }

   return res;
  }


  public string RestoreCasing( int EntryID, string word )
  {
   return GrammarEngine.sol_RestoreCasingFX( _hEngine, word, EntryID );
  }


  public AnalysisResults AnalyzeSyntax( string _phrase, int id_language )
  {
   IntPtr hPack = GrammarEngine.sol_SyntaxAnalysis( _hEngine, _phrase, 0, 0, 60000, id_language );
   AnalysisResults res = new AnalysisResults( this, hPack );
   return res;
  }

  public AnalysisResults AnalyzeSyntax( string phrase, int id_language, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags morph_flags, SolarixGrammarEngineNET.GrammarEngine.SyntaxFlags syntax_flags )
  {
   IntPtr hPack = GrammarEngine.sol_SyntaxAnalysis( _hEngine, phrase, morph_flags, syntax_flags, 60000, id_language );
   AnalysisResults res = new AnalysisResults( this, hPack );
   return res;
  }

  public AnalysisResults AnalyzeSyntax( string phrase, int id_language, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags morph_flags, SolarixGrammarEngineNET.GrammarEngine.SyntaxFlags syntax_flags, int constraints )
  {
   IntPtr hPack = GrammarEngine.sol_SyntaxAnalysis( _hEngine, phrase, morph_flags, syntax_flags, constraints, id_language );
   AnalysisResults res = new AnalysisResults( this, hPack );
   return res;
  }


  public AnalysisResults AnalyzeMorphology( string phrase, int id_language )
  {
   IntPtr hPack = GrammarEngine.sol_MorphologyAnalysis( _hEngine, phrase, 0, 0, 0, id_language );
   AnalysisResults res = new AnalysisResults( this, hPack );
   return res;
  }

  public AnalysisResults AnalyzeMorphology( string phrase, int id_language, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags flags )
  {
   IntPtr hPack = GrammarEngine.sol_MorphologyAnalysis( _hEngine, phrase, flags, 0, 0, id_language );
   AnalysisResults res = new AnalysisResults( this, hPack );
   return res;
  }

  public AnalysisResults AnalyzeMorphology( string phrase, int id_language, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags flags, int constraints )
  {
   IntPtr hPack = GrammarEngine.sol_MorphologyAnalysis( _hEngine, phrase, flags, 0, constraints, id_language );
   AnalysisResults res = new AnalysisResults( this, hPack );
   return res;
  }

  public string NormalizePhrase( AnalysisResults linkages )
  {
   return SolarixGrammarEngineNET.GrammarEngine.NormalizePhraseFX( _hEngine, linkages.GetHandle() );
  }


  public ThesaurusLinks ListLinksTxt( int id_entry, int link_code, int flags )
  {
   IntPtr hList = SolarixGrammarEngineNET.GrammarEngine.sol_ListLinksTxt( GetEngineHandle(), id_entry, link_code, flags );
   return new ThesaurusLinks( GetEngineHandle(), hList );
  }

  public int FindTag( string TagName )
  {
   return SolarixGrammarEngineNET.GrammarEngine.sol_FindTagW( GetEngineHandle(), TagName );
  }

  public int FindTagValue( int TagID, string ValueName )
  {
   return SolarixGrammarEngineNET.GrammarEngine.sol_FindTagValueW( GetEngineHandle(), TagID, ValueName );
  }

  public string[] Tokenize( string Text, int LanguageID )
  {
   return SolarixGrammarEngineNET.GrammarEngine.sol_TokenizeFX( GetEngineHandle(), Text, LanguageID );
  }

  public int GetCoordType( int PartOfSpeechID, int CoordID )
  {
   return SolarixGrammarEngineNET.GrammarEngine.sol_GetCoordType( GetEngineHandle(), CoordID, PartOfSpeechID );
  }

  public string GetClassName( int PartOfSpeechID )
  {
   return SolarixGrammarEngineNET.GrammarEngine.sol_GetClassNameFX( GetEngineHandle(), PartOfSpeechID );
  }

  public string GetCoordName( int CoordID )
  {
   return SolarixGrammarEngineNET.GrammarEngine.sol_GetCoordNameFX( GetEngineHandle(), CoordID );
  }

  public int CountCoordStates( int CoordID )
  {
   return SolarixGrammarEngineNET.GrammarEngine.sol_CountCoordStates( GetEngineHandle(), CoordID );
  }

  public string GetCoordStateName( int CoordID, int StateID )
  {
   return SolarixGrammarEngineNET.GrammarEngine.sol_GetCoordStateNameFX( GetEngineHandle(), CoordID, StateID );
  }

  public TextSegmenter GetTextFileSegmenter( string FilePath, string Encoding, int LanguageID )
  {
   IntPtr h = SolarixGrammarEngineNET.GrammarEngine.sol_CreateSentenceBroker( GetEngineHandle(), FilePath, Encoding, LanguageID );
   return new TextSegmenter( this, h );
  }
 };

}
