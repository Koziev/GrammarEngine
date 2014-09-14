#include <lem/macro_parser.h>
#include <lem/solarix/TreeScorer.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/Thesaurus.h>

#if defined SOL_REPORT
#include <lem/solarix/sql_production.h>
#endif

#include <lem/solarix/WordAssociation.h>

using namespace Solarix;

WordAssociation::WordAssociation(): id(UNKNOWN), id_entry(UNKNOWN),id_entry1(UNKNOWN),id_metaentry1(UNKNOWN),id_entry2(UNKNOWN),id_metaentry2(UNKNOWN),
 ThesaurusCheck_Link(UNKNOWN),ThesaurusCheck_Entry(UNKNOWN),set_type(UNKNOWN), score(0), src_location(UNKNOWN)
{
}


WordAssociation::WordAssociation(
                                 int _id,
                                 int _id_src,
                                 int _id_entry,
                                 int _id_entry1, const lem::UCString & _word1, int _id_metaentry1,
                                 int _id_entry2, const lem::UCString & _word2, int _id_metaentry2,
                                 int _link_type, int _link_entry,
                                 const lem::UCString & _set_name,
                                 int _set_type,
                                 int _score
                                )
: id(_id), id_entry(_id_entry),id_entry1(_id_entry1),word1(_word1),id_metaentry1(_id_metaentry1),id_entry2(_id_entry2),word2(_word2),id_metaentry2(_id_metaentry2),
 ThesaurusCheck_Link(_link_type),ThesaurusCheck_Entry(_link_entry),set_type(_set_type), score(_score), src_location(_id_src)
{}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void WordAssociation::LoadTxt( Dictionary & dict, lem::Iridium::Macro_Parser & txtfile, WordEntrySet & sets )
{
 src_location = dict.GetDebugSymbols().RegisterLocation( txtfile, txtfile.tellp() );
 
 txtfile.read_it( B_LANGUAGE );
 // дальше идет наименование €зыка, в рамках которого действует правило.
 txtfile.read_it( B_EQUAL );
 lem::Iridium::BethToken t1 = txtfile.read();
 const int id_language = dict.GetSynGram().Find_Language(t1.string());
 if( id_language==UNKNOWN )
  {
   lem::Iridium::Print_Error(t1,txtfile);
   dict.GetIO().merr().printf( "Unknown language name %us\n", t1.c_str() );
   throw lem::E_BaseException();
  }

 txtfile.read_it( B_OFIGPAREN );

 LoadWordEntryPoint( dict, txtfile, id_language, &id_entry, NULL );

 txtfile.read_it(B_IFTHEN); // :-

 // “еперь один из вариантов селекторов.

 lem::Iridium::BethToken t0 = txtfile.read();
 if( sets.IsWordEntrySetName( t0.string() ) )
  {
   set_name = t0.string();
   set_type = 0;
  }
 else if( sets.IsWordSetName( t0.string() ) )
  {
   set_name = t0.string();
   set_type = 1;
  }
 else if( t0.string()==L'<' )
  {
   txtfile.seekp(t0.GetBegin());
   Solarix::Tree_Link link;
   link.LoadTxt( txtfile, dict.GetSynGram() );
   ThesaurusCheck_Link = link.GetState();
   LoadWordEntryPoint( dict, txtfile, id_language, &ThesaurusCheck_Entry, NULL );
  }
 else if( t0==B_OFIGPAREN )
  {
   // 2-грамма - пара словарных статей или лексем.

   lem::Iridium::BethToken t1 = txtfile.read();
   if( lem::in_apostrophes( t1.string() ) )
    {
     word1 = lem::strip_apostrophes( t1.string() );
    }
   else if( lem::in_quotes( t1.string() ) )
    {
     word1 = lem::strip_quotes( t1.string() );
    }
   else
    {
     LoadWordEntryPoint( dict, txtfile, id_language, &id_entry1, &id_metaentry1 );
    }

   lem::Iridium::BethToken t2 = txtfile.read();
   if( lem::in_apostrophes( t2.string() ) )
    {
     word2 = lem::strip_apostrophes( t2.string() );
    }
   else if( lem::in_quotes( t2.string() ) )
    {
     word2 = lem::strip_quotes( t2.string() );
    }
   else
    {
     LoadWordEntryPoint( dict, txtfile, id_language, &id_entry2, &id_metaentry2 );
    }
  }
 else if( lem::in_apostrophes( t0.string() ) )
  {
   Solarix::Lexem lex( lem::strip_apostrophes( t0.string() ) );
   dict.GetLexAuto().TranslateLexem( lex, true, id_language );
   word1 = lex;
  }
 else if( lem::in_quotes( t0.string() ) )
  {
   Solarix::Lexem lex( lem::strip_quotes( t0.string() ) );
   dict.GetLexAuto().TranslateLexem( lex, true, id_language );
   word1 = lex;
  }
 else
  {
   txtfile.seekp(t0.GetBegin());
   LoadWordEntryPoint( dict, txtfile, id_language, &id_entry1, &id_metaentry1 );

   // ... todo - может быть и дерево, тогда здесь пойдет точка....
  }

 // ÷елочисленна€ оценка силы обуславливани€.
 txtfile.read_it( B_EQUAL );
 score = txtfile.read_int();

 txtfile.read_it( B_CFIGPAREN );

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
// ≈сли metaentry=NULL, то не будем пытатьс€ загрузить метастатью.
void WordAssociation::LoadWordEntryPoint( Dictionary & dict, lem::Iridium::Macro_Parser & txtfile, int id_language, int * entry, int * metaentry )
{
 lem::Iridium::BethToken t1 = txtfile.read();
 lem::UCString class_name(t1.string());

 const int id_class = dict.GetSynGram().FindClass(class_name);
 if( id_class==UNKNOWN )
  {
   lem::Iridium::Print_Error(t1,txtfile);
   dict.GetIO().merr().printf( "Unknown part of speech %us\n", class_name.c_str() );
   throw lem::E_BaseException();
  }

 txtfile.read_it( B_COLON );
 lem::Iridium::BSourceState ebeg = txtfile.tellp();
 UCString ename=sol_read_multyname( dict.GetIO(), txtfile, B_OFIGPAREN );
 Solarix::Lexem lex_name(ename);
 dict.GetLexAuto().TranslateLexem(lex_name,true,id_language);

 ExactWordEntryLocator omonym_resolver;
 omonym_resolver.LoadTxt( txtfile, dict.GetSynGram() );

 int res = dict.GetSynGram().FindEntryOmonym( lex_name, id_class, omonym_resolver );

 if( res==UNKNOWN )
  {
   if( metaentry!=NULL )
    {
     *metaentry = dict.GetSynGram().FindMetaEntry(lex_name,id_class);
     if( *metaentry!=UNKNOWN )
      return;
    }
 
   lem::Iridium::Print_Error(t1,txtfile);
   dict.GetIO().merr().printf( "Can not find wordentry %us:%us\n", class_name.c_str(), ename.c_str() );
   throw lem::E_BaseException();
  }
 else
  {
   *entry = res;
   if( metaentry!=NULL )
    *metaentry = UNKNOWN;
  }
}
#endif



void WordAssociation::Save( LexiconStorage & storage )
{
 if( IsSingleLemma() )
  {
   id = storage.StoreWordAssoc_ByLemma( src_location, id_entry, id_entry1, score );
  }
 else if( IsSingleMetaEntry() )
  {
   id = storage.StoreWordAssoc_ByMetaentry( src_location, id_entry, id_metaentry1, score );
  }
 else if( IsSingleLexem() )
  {
   id = storage.StoreWordAssoc_ByLexem( src_location, id_entry, word1, score );
  }
 else if( IsThesaurusLink() )
  {
   id = storage.StoreWordAssoc_ByThesaurusLink( src_location, id_entry, ThesaurusCheck_Link, ThesaurusCheck_Entry, score );
  }
 else if( IsWordentrySet() || IsWordSet() )
  {
   id = storage.StoreWordAssoc_BySet( src_location, id_entry, set_name, set_type, score );
  }
 else
  {
   LEM_STOPIT;
   // ...
  }


 return;
}


#if defined SOL_CAA
bool WordAssociation::Match( const Word_Form & wordform, Dictionary & dict ) const
{
 if( IsSingleLemma() )
  {
   return wordform.GetEntryKey() == id_entry1;
  }
 else if( IsSingleMetaEntry() )
  {
   return dict.GetSynGram().GetStorage().DoesMetaEntryContains( id_metaentry1, wordform.GetEntryKey() );
  }
 else if( IsSingleLexem() )
  {
   return *wordform.GetNormalized() == word1;
  }
 else if( IsThesaurusLink() )
  {
   int id_link = dict.GetSynGram().Get_Net().Find_Linked_Entry( wordform.GetEntryKey(), ThesaurusCheck_Link, ThesaurusCheck_Entry );
   return id_link!=UNKNOWN;
  }
 else if( IsWordentrySet() )
  {
   return dict.GetLexAuto().GetWordEntrySet().FindWordEntrySet( set_name, wordform.GetEntryKey() );
  }
 else if( IsWordSet() )
  {
   return dict.GetLexAuto().GetWordEntrySet().FindWordSet( set_name, *wordform.GetNormalized() );
  }
 else
  {
   LEM_STOPIT;
   return false;
  }
}
#endif



#if defined SOL_REPORT
void WordAssociation::SaveSQL( OFormatter &out, const SQL_Production &sql_version ) const
{
 UFString word1_text = sql_version.SqlStr(word1);
 word1_text.re_clear();

 UFString word2_text = sql_version.SqlStr(word2);
 word2_text.re_clear();

 out.printf( "INSERT INTO word_assoc( id_src, id_entry, id_entry1, word1, id_metaentry1, id_entry2,"
             " word2, id_metaentry2, link_type, link_entry, set_name, set_type,"
             " score )"
             " VALUES ( %d, %d, %d, '%us', %d, %d,"
             "          '%us', %d, %d, %d, '%us', %d,"
             "          %d );\n",
             src_location, id_entry, id_entry1, word1_text.c_str(), id_metaentry1, id_entry2,
             word2_text.c_str(), id_metaentry2, ThesaurusCheck_Link, ThesaurusCheck_Entry, set_name.c_str(), set_type,
             score );

 return;
}
#endif
