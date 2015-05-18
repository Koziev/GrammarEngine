#include <stdio.h>
#include <windows.h>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <boost/regex.hpp>

#include <lem/startup.h>
#include <lem/console_streams.h>
#include <lem/date_time.h>
#include <lem/xml_parser.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/sentencebroker.h>
#include <lem/solarix/WrittenTextAnalysisSession.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/MorphologyModels.h>
#include <lem/solarix/print_variator.h>
#include <lem/solarix/casing_coder.h>
#include <lem/solarix/la_autom.h>

#include <libdesr.h>


using namespace Solarix;






class SentenceEOL : public SentenceBroker
{
 public:
  SentenceEOL( lem::Char_Stream::WideStream &stream, Dictionary * dict, int language ) 
   : SentenceBroker( stream, dict, language ) {}

  SentenceEOL( lem::Ptr<lem::Char_Stream::WideStream> stream, Dictionary * dict, int language )
   : SentenceBroker( stream, dict, language ) {}

  virtual bool Fetch( lem::UFString & line, int & line_paragraph_id )
  {
   line.clear();
   line_paragraph_id = cur_paragraph_id;

   if( eof )
    return false;

   while( !eof )
   {
    wchar_t c = GetChar();
   
    if( SentenceBroker::IsEndOfParagraphMarker(c) )
     {
      cur_paragraph_id++;
      break;
     }
    else if( SentenceBroker::IsEndOfSentenceMarker(c) )
    {
     break;
    }
    else if( c==WEOF )
     {
      eof = true;
      return true;
     }
    else if( c=='\n' )
     {
      break;
     }
    else line.Add_Dirty(c);
   }

   line.calc_hash();
   line.trim();

   return true;
  }
};















void ShowHelp()
{
 lem::mout->printf( "\n\nUsage: parser -d dictionary_path input_text_file -o output_xml_file\n\n" );
 exit(0);
}


static lem::UFString EncodeStrXml( const wchar_t * src )
{
 lem::UFString res;

 if( res.find(L'&')!=-1 || res.find(L'<')!=-1 || res.find(L'>')!=-1 )
  {
   int i=0;
   while( src[i]!=0 )
   {
    if( src[i]==L'&' )
     res += L"&amp;";
    else if( src[i]==L'<' )
     res += L"&lt;";
    else if( src[i]==L'>' )
     res += L"&gt;";
    else
     res += src[i];

    i++;
   }
  }
 else
  {
   res = src;
  }

 return res;
}

static void AssembleEdges( const Solarix::Tree_Node & node, std::map<int, std::pair<int,int> > & child_to_parent, std::map<int,lem::UCString> & node2word )
{
 for( int j=0; j<node.leafs().size(); ++j )
  {
   const Solarix::Tree_Node & child = node.leafs()[j];
   node2word.insert( std::make_pair( child.GetNode().GetOriginPos(), *child.GetNode().GetName() ) );

   child_to_parent.insert( std::make_pair( child.GetNode().GetOriginPos(), std::make_pair( node.GetNode().GetOriginPos(), node.GetLinkIndex(j).GetState() ) ) );

   AssembleEdges( child, child_to_parent, node2word );
  }

 return;
}



static void DumpMorphTokens( Solarix::Dictionary & dict, Solarix::CasingCoder & cc, const Solarix::Variator & tagging, bool emit_morph, lem::OUFormatter & out_stream )
{
 out_stream.printf( "<tokens>\n" );
 for( lem::Container::size_type i=1; i<tagging.roots_list().size()-1; ++i )
 {
  out_stream.printf( "<token>\n" );
 
  const Solarix::Word_Form & wf = tagging.roots_list()[i]->GetNode();
  lem::UFString sword( EncodeStrXml( wf.GetName()->c_str()) );

  lem::UFString slemma;
  bool is_unknown=false;    
  int id_entry = wf.GetEntryKey();
  const SG_Entry & e = dict.GetSynGram().GetEntry( id_entry );
  const SG_Class & e_class = dict.GetSynGram().GetClass( e.GetClass() );

  if( dict.GetSynGram().GetUEntries().find( id_entry )==UNKNOWN )
   {
    lem::UFString w(e.GetName().c_str());
    cc.RestoreCasing(w,id_entry);
    w.subst_all( L" - ", L"-" );
    w.subst_all( L" ' ", L"'" );

    slemma = EncodeStrXml(w.c_str());
   }
  else
   {
    is_unknown = true;
    slemma = EncodeStrXml(wf.GetName()->c_str());
   }


  out_stream.printf( "<word%s>%us</word>\n", (is_unknown ? " is_unknown='true'" : ""), sword.c_str() );
  out_stream.printf( "<position>%d</position>\n", wf.GetOriginPos() );
  out_stream.printf( "<lemma>%us</lemma>\n", slemma.c_str() );
  out_stream.printf( "<part_of_speech>%us</part_of_speech>\n", e_class.GetName().c_str() );

  if( emit_morph )
   {
    out_stream.printf( "<tags>" );
    for( int itag=0; itag<wf.GetnPair(); ++itag )
     {
      int id_coord = wf.GetPair(itag).GetCoord().GetIndex();
      int id_state = wf.GetPair(itag).GetState();
 
      if( itag>0 )
       out_stream.printf( "|" );
 
      if( dict.GetSynGram().coords().GetCoord( id_coord ).IsBistable() )
      {
       out_stream.printf( "%us:%d", 
        dict.GetSynGram().coords().GetCoord( id_coord ).GetName().string().c_str(), id_state );
      }
      else
      {
       out_stream.printf( "%us:%us",
        dict.GetSynGram().coords().GetCoord( id_coord ).GetName().string().c_str(),
        dict.GetSynGram().coords().GetCoord( id_coord ).GetStateName( id_state ).c_str() );
      }
     }
 
    out_stream.printf( "</tags>\n" );
   }

  out_stream.printf( "</token>\n" );
 }
 
 out_stream.printf( "</tokens>\n" );

 return;
}


int main( int argc, char *argv[] )
{
 lem::LemInit initer;

 lem::Path dict_path("dictionary.xml");
 lem::Path input_path;
 lem::Path out_path;
 int beam_size=20;
 bool verbose=false;
 bool eol=false;
 bool render_tree=false;
 bool emit_morph=true;
 int start_index=0;
 int max_count=lem::int_max;

 int tagger_type=-1; // -1 - none, 0 - CRF POS tagger
 int parser_type=-1; // -1 - none, 0 - DeSR, 1 - top-down

 lem::UCString language_name(L"Russian");

 for( int i=1; i<argc; ++i )
 {
  if( strlen(argv[i])>1 && argv[i][0]=='-' )
  {
   const char * opt = argv[i]+1;
   if( opt[0]=='-' )
    opt = opt+1;

   try
   { 
    if( strcmp( opt, "dict" )==0 )
     dict_path = lem::Path(argv[++i]);
    else if( strcmp( opt, "start_index" )==0 )
     start_index = lem::to_int(argv[++i]);
    else if( strcmp( opt, "max_count" )==0 )
     max_count = lem::to_int(argv[++i]);
    else if( strcmp( opt, "output" )==0 )
     out_path = lem::Path(argv[++i]);
    else if( strcmp( opt, "input" )==0 )
     input_path = lem::Path(argv[++i]);
    else if( strcmp( opt, "beam" )==0 )
     beam_size = lem::to_int(argv[++i]);
    else if( strcmp( opt, "parser" )==0 )
     parser_type = lem::to_int(argv[++i]);
    else if( strcmp( opt, "tagger" )==0 )
     tagger_type = lem::to_int(argv[++i]);
    else if( strcmp( opt, "render_tree" )==0 )
     render_tree = lem::to_int(argv[++i])==1;
    else if( strcmp( opt, "verbose" )==0 )
     verbose = true;
    else if( strcmp( opt, "eol" )==0 )
     eol = true;
    else if( strcmp( opt, "emit_morph" )==0 )
     emit_morph = lem::to_int(argv[++i])==1;
    else if( strcmp( opt, "d" )==0 )
     dict_path = lem::Path(argv[++i]);
    else if( strcmp( opt, "o" )==0 )
     out_path = lem::Path(argv[++i]);
    else if( strcmp( opt, "i" )==0 )
     input_path = lem::Path(argv[++i]);
    else if( strcmp( opt, "v" )==0 )
     verbose = true;
    else if( strcmp( opt, "h" )==0 || strcmp( opt, "?" )==0 )
     ShowHelp();
    else
    {
     printf( "Unknown option [%s]\n", argv[i] );
     exit(1);
    }
   }
   catch( const E_BaseException & e )
   {
    lem::mout->printf( "Command line option %s parsing error: %us", e.what() );
    exit(1);
   }
   catch( std::exception & e )
   {
    lem::mout->printf( "Command line option %s parsing error: %s", e.what() );
    exit(1);
   }
   catch(...)
   {
    lem::mout->printf( "Command line option %s parsing error" );
    exit(1);
   }
  }
  else if( input_path.empty() )
  {
   input_path = lem::Path( argv[i] );
  }
  else
  {
   printf( "Unknown option [%s]\n", argv[i] );
   exit(1);
  }
 }


 Dictionary dict;

 Load_Options opt;

 opt.load_semnet = true;
 opt.ngrams = true;
 opt.lexicon = true;

 bool ok=false;

 try
  {
   dict_path = dict_path.GetAbsolutePath();

   if( verbose )
    lem::mout->printf( "Loading dictionary from [%us]...\n", dict_path.GetUnicode().c_str() );

   ok = dict.LoadModules( dict_path, opt );
  }
 catch(...)
  {
   ok = false;
  }

 if( !ok )
  {
   lem::mout->printf( "\nCould not load the dictionary using [%us]\n", dict_path.GetUnicode().c_str() );
   lem::Process::Exit();
  }


 // -------------------------------------------------------------------------

 ModelCodeBook desr_codebook;
 void * hDESR = NULL;

 if( parser_type==0 )
  {
   // Загрузим модель для синт. парсера DeSR
   lem::Xml::Parser xml_dict;
   xml_dict.Load( dict_path );
   lem::UFString desr_path = xml_dict.Get_By_Path( L"dataroot.models.desr" );

   lem::Path desr_folder( dict_path );
   desr_folder.RemoveLastLeaf();
   desr_folder.ConcateLeaf( desr_path );
   desr_folder = desr_folder.GetAbsolutePath();

   lem::Path desr_codebook_path( desr_folder );
   desr_codebook_path.ConcateLeaf( L"syntax.codebook" );

   lem::Path desr_model( desr_folder );
   desr_model.ConcateLeaf( L"syntax.model" );

   if( verbose )
    lem::mout->printf( "syntax parser model file=%s\n", desr_model.GetAscii().c_str() );

   if( !desr_model.DoesExist() )
    {
     lem::mout->printf( "File [%s] does not exist", desr_model.GetAscii().c_str() );
     exit(1);
    }

   lem::Path desr_conf( desr_folder );
   desr_conf.ConcateLeaf( L"desr.conf" );

   lem::BinaryReader desr_codebook_stream( desr_codebook_path );
   desr_codebook.LoadBin( desr_codebook_stream );

   hDESR = DesrInit( 10, desr_conf.GetAscii().c_str(), desr_model.GetAscii().c_str() );
  }


 // -------------------------------------------------------------------------

 int language_id = UNKNOWN;
 language_id = dict.GetSynGram().Find_Language( language_name );
 if( language_id==UNKNOWN )
  {
   lem::mout->printf( "Unknown language [%us]\n", language_name );
   exit(1);
  }


 Solarix::WrittenTextAnalysisSession current_analysis( &dict, NULL );
 current_analysis.params.SetLanguageID(language_id);
 current_analysis.params.AllowPrimaryFuzzyWordRecog = false;
 current_analysis.params.AllowDynform = true;
 current_analysis.params.ApplyModel = true;

 // Ограничение на суммарное затраченное время в миллисекундах
 const int MaxMillisecTimeout = 180000;
 current_analysis.params.timeout.max_elapsed_millisecs = MaxMillisecTimeout>0 ? MaxMillisecTimeout : lem::int_max;

 // Ограничение на макс. число параллельно проверяемых альтернативных путей построения синтаксического дерева
 current_analysis.params.timeout.max_alt = beam_size;

 current_analysis.params.CompleteAnalysisOnly = false;
 current_analysis.params.ConfigureSkipToken();

 Solarix::CasingCoder& cc = dict.GetLexAuto().GetCasingCoder();

 // ------------------------------------
 std::vector<lem::Path> filenames;
 if( input_path.IsFolder() )
  {
   input_path.ListFiles( filenames, true );
  }
 else
  {
   filenames.push_back( input_path );
  }

 lem::OUFormatter out_stream( out_path );
 out_stream.printf( "<?xml version='1.0' encoding='utf-8' ?>\n<parsing>\n" );

 lem::ElapsedTime elapsed_time;
 elapsed_time.start();
 int word_count=0;
 int counter=0;

 int sent_count=0;

 try
 {
  for( int ifile=0; ifile<filenames.size() && sent_count<max_count; ++ifile )
  {
   const lem::Path & input_file = filenames[ifile];

   if( filenames.size()>1 )
    lem::mout->printf( "Parsing %d/%d [%us]...\n", ifile+1, CastSizeToInt(filenames.size()), input_file.GetUnicode().c_str() );

   // Считаем, что входные файлы всегда в utf-8
   lem::Ptr<lem::Char_Stream::WideStream> reader = new lem::Char_Stream::UTF8_Reader(input_file); //lem::Char_Stream::WideStream::GetReader(input_path);
   SentenceBroker * segmenter = NULL;

   if( eol )
    segmenter = new SentenceEOL( reader, &dict, language_id );
   else
    segmenter = new SentenceBroker( reader, &dict, language_id );

   while( segmenter->Fetch() )
   {
    try
    {
     UFString sentence( segmenter->GetFetchedSentence() );
     sent_count++;
     if( sent_count<start_index )
      continue;
   
     if( sent_count>max_count )
      break;
   
     if( !sentence.empty() )
     {
      sentence.trim();
      lem::UFString xml_str = EncodeStrXml(sentence.c_str());
      int paragraph_id = segmenter->GetFetchedParagraphID();
      out_stream.printf( "\n\n<sentence paragraph_id='%d'>\n<text>%us</text>\n", paragraph_id, xml_str.c_str() );
   
      if( verbose )
       lem::mout->printf( "%d: %us\n", counter, sentence.c_str() );
   
      counter++;
   
      if( parser_type==-1 )
       {
        if( tagger_type==0 )
         {
          // применяем вероятностную модель морфологии для снятия неоднозначностей, но правила не применяем.
          current_analysis.ApplyFilters(sentence);
         }
        else
         {
          // точный и медленный POS Tagger...
          current_analysis.MorphologicalAnalysis(sentence);
         }
   
        const Res_Pack & pack0 = current_analysis.GetPack();
        const Solarix::Variator & tagging = * pack0.vars().front();
        DumpMorphTokens( dict, cc, tagging, emit_morph, out_stream );
     
        const int n_token = CastSizeToInt(tagging.roots_list().size()-2);
        word_count += n_token;
       }
      else if( parser_type==0 )
       {
        // DESR вероятностный парсер
   
        // применяем вероятностную модель морфологии для снятия неоднозначностей, но правила не применяем.
        current_analysis.ApplyFilters(sentence);
   
        const Res_Pack & pack0 = current_analysis.GetPack();
        const Solarix::Variator & tagging = * pack0.vars().front();
   
        if( tagger_type!=-1 )
         DumpMorphTokens( dict, cc, tagging, emit_morph, out_stream );
     
        const int n_token = CastSizeToInt(tagging.roots_list().size()-2);
        word_count += n_token;
   
        
        // выполним парсинг, используя результаты POS Tagger'а
        out_stream.printf( "\n<syntax_tree>\n" );
     
        lem::FString desr_input;
     
        for( lem::Container::size_type i=1; i<tagging.roots_list().size()-1; ++i )
        {
         const Solarix::Word_Form & wf = tagging.roots_list()[i]->GetNode();
     
         const ModelTagMatcher * tm = desr_codebook.Match( &wf, dict );
         int id_tag = tm==NULL ? -1 : tm->GetId();
   
         #if LEM_DEBUGGING==1
         lem::mout->printf( "token #%d word=%us tag=%d ", i, wf.GetName()->c_str(), id_tag );
         tm->Print( *lem::mout, dict );
         lem::mout->eol();
         tm->Match( wf, dict );
         #endif
         
         desr_input.Add_Dirty( lem::format_str( "%d\t_\t_\t_\t%d\t_\t?\t?\t_\t_\n", CastSizeToInt(i), id_tag ) );
        }
     
        // lem::mout->printf( "DEBUG: Before syntax...\n" );
        char * desr_res_str = DesrTag( hDESR, desr_input.c_str() );
        // lem::mout->printf( "DEBUG: After syntax...\n" );
     
        std::string s_res( desr_res_str );
     
        // разбиваем выдачу на строки
        boost::regex rx_line( "^(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)$", boost::regex_constants::icase );
     
        boost::sregex_iterator m2;
        int itoken=1;
        for( boost::sregex_iterator it( s_res.begin(), s_res.end(), rx_line ); it!=m2; ++it, ++itoken )
        {
         const boost::match_results<std::string::const_iterator> & mx = *it;
         const std::string & parent_id = mx[7].str();
         lem::UFString link_name = lem::from_utf8( mx[8].str().c_str() );
     
         int word_index = itoken-1;
         int parent_index = lem::to_int(parent_id)-1;
     
         const Solarix::Word_Form & node_wf = tagging.roots_list()[itoken]->GetNode();
         lem::UFString node_word( EncodeStrXml( node_wf.GetName()->c_str()) );
     
         if( parent_index==-1 )
          {
           out_stream.printf( "<node is_root='true'>" );
           out_stream.printf( "<token>%d</token><word>%us</word><parent>-1</parent><parent_word></parent_word><link_type></link_type></node>\n", word_index, node_word.c_str() );
          }
         else
          {
           const Solarix::Word_Form & parent_wf = tagging.roots_list()[parent_index+1]->GetNode();
           lem::UFString parent_word( EncodeStrXml( parent_wf.GetName()->c_str()) );
           out_stream.printf( "<node><token>%d</token><word>%us</word><parent>%d</parent><parent_word>%us</parent_word><link_type>%us</link_type></node>\n", word_index, node_word.c_str(), parent_index, parent_word.c_str(), link_name.c_str() );
          }
     
        }
     
        DesrFreeResult( hDESR, desr_res_str );
     
        out_stream.printf( "</syntax_tree>\n" );
       }
      else if( parser_type==1 )
       {
        // Медленный top-down парсер
        // Отдельный POS Tagger не запускаем.
   
        current_analysis.SyntacticAnalysis(sentence);
        const Res_Pack & linkage = current_analysis.GetPack();
   
        const Solarix::Variator & var = * linkage.vars().front();
        int nroot = var.roots_list().size();
   
        Solarix::Variator tagging;
        for( lem::Container::size_type i=0; i<var.roots_list().size(); ++i )
         {
          Solarix::Tree_Node * node = var.roots_list()[i];
          tagging.Add( node );
         }
   
        const int n_token = tagging.roots_list().size()-2;
   
        if( tagger_type!=-1 )
         {
          DumpMorphTokens( dict, cc, tagging, emit_morph, out_stream );
          
          for( lem::Container::size_type i=0; i<var.roots_list().size(); ++i )
          {
           tagging.ForgetTree(i);
          }
         }
   
        std::set<int> roots;
        std::map<int, std::pair<int,int> > child_to_parent;
        std::map<int,lem::UCString> node2word;
   
        out_stream.printf( "\n<syntax_tree>\n" );
        for( lem::Container::size_type i=1; i<var.roots_list().size()-1; ++i )
        {
         const Solarix::Tree_Node & node = * var.roots_list()[i];
     
         roots.insert( node.GetNode().GetOriginPos() );
         node2word.insert( std::make_pair( node.GetNode().GetOriginPos(), *node.GetNode().GetName() ) );
     
         AssembleEdges( node, child_to_parent, node2word );
        }
        
        for( int word_pos=0; word_pos<n_token; ++word_pos )
        {
         lem::UFString node_word( EncodeStrXml( node2word[word_pos].c_str()) );
     
         if( roots.find(word_pos)!=roots.end() )
          out_stream.printf( "<node is_root='true'><token>%d</token><word>%us</word><parent>-1</parent><link_type>ROOT</link_type></node>\n", word_pos, node_word.c_str() );
         else if( child_to_parent.find(word_pos)==child_to_parent.end() )
          out_stream.printf( "<node is_orphant='true'><token>%d</token><word>%us</word><parent>-1</parent><link_type>UNKNOWN</link_type></node>\n", word_pos, node_word.c_str() );
         else
          {
           const std::pair<int,int> & parent_and_link = child_to_parent[ word_pos ];
           const UCString & link_name = dict.GetSynGram().coords()[0].GetStateName( parent_and_link.second );
           lem::UFString parent_word( EncodeStrXml( node2word[parent_and_link.first].c_str()) );
           out_stream.printf( "<node><token>%d</token><word>%us</word><parent>%d</parent><parent_word>%us</parent_word><link_type>%us</link_type></node>\n", word_pos, node_word.c_str(), parent_and_link.first, parent_word.c_str(), link_name.c_str() );
          }
        }
     
        out_stream.printf( "</syntax_tree>\n" );
     
        if( render_tree )
         {
          lem::MemFormatter mem;
          Solarix::print_syntax_tree( L"", linkage, dict, mem, false, false );
          lem::UFString str = mem.string();
          lem::UFString encoded_tree = EncodeStrXml(str.c_str()).subst_all( '\r', ' ' );
   
          out_stream.printf( "<syntax_tree_rendering>\n<![CDATA[\n%us\n]]>\n</syntax_tree_rendering>\n", encoded_tree.c_str() );
         }
       }


      out_stream.printf( "</sentence>\n" );
     }
    }
    catch( const lem::E_BaseException & ex )
    {
     lem::mout->printf( "\nInternal parser error: %us\n", ex.what() );
     exit(1);
    }
    catch( const std::exception &ex )
    {
     lem::mout->printf( "\nInternal parser error: %s\n", ex.what() );
     exit(1);
    }
    catch(...)
    {
     lem::mout->printf( "\nUnknown internal parser error\n" );
     exit(1);
    }
   }

   delete segmenter;
  }
 }
 catch( const E_BaseException & e )
 {
  lem::mout->printf( "Command line option %s parsing error: %us", e.what() );
  exit(1);
 }
 catch( std::exception & e )
 {
  lem::mout->printf( "Command line option %s parsing error: %s", e.what() );
  exit(1);
 }
 catch(...)
 {
  lem::mout->printf( "Unknown error" );
  exit(1);
 }


 out_stream.printf( "\n</parsing>" );
 out_stream.close();

 elapsed_time.stop();
 boost::posix_time::time_duration dt = elapsed_time.elapsed();

 lem::mout->printf( "Done, sentence_count=%d, elapsed_time=%d sec, rate=%g words/sec\n", counter, dt.total_seconds(), (word_count*1000.0/dt.total_milliseconds()) );

 if( parser_type==0 )
  {
   DesrDeleteEngine(hDESR);
  }
 
 return 0;
}
