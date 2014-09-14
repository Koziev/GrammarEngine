#if defined SOL_EXPORT_SQL

#include <lem/solarix/LA_CropRule.h>
#include <lem/solarix/LA_PhoneticRule.h>
#include <lem/solarix/LA_RecognitionRule.h>
#include <lem/solarix/LA_UnbreakableRule.h>
#include <lem/solarix/WordSetEnumerator.h>
#include <lem/solarix/WordSetItem.h>
#include <lem/solarix/WordEntrySetItem.h>
#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/WordEntrySetEnumerator.h>
#include <lem/solarix/LanguageEnumerator.h>
#include <lem/solarix/WordAssociation.h>
#include <lem/solarix/PredicateTemplate.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>

using namespace lem;
using namespace Solarix;

void LexicalAutomat::SaveRules_SQL( OFormatter &out, OFormatter &alters, const SQL_Production &sql_version )
{
 if( sql_version.norules )
  return;

 PM_Automat::SaveRules_SQL( "la", out, alters, sql_version );


 lem::Ptr<LS_ResultSet> rs_predicates( GetStorage().ListPredicateTemplate() );
 while( rs_predicates->Fetch() )
 {
  int id = rs_predicates->GetInt(0);
  lem::Ptr<PredicateTemplate> t( GetStorage().LoadPredicateTemplate(id) );

  lem::UFString src( sql_version.SqlStr(t->GetSrc()) );
  
  lem::UFString params;
  for( lem::Container::size_type i=0; i<t->GetParams().size(); ++i )
   if( i>0 )
    {
     params.Add_Dirty( L"," );
     params.Add_Dirty( t->GetParams()[i].c_str() );
    }
   else
    {
     params.Add_Dirty( t->GetParams()[i].c_str() );
    }

  out.printf( "INSERT INTO predicate_template( src, params ) VALUES ( '%us', '%us' );\n", src.c_str(), params.c_str() );
 }
 rs_predicates.Delete();
 out.eol();
 out.flush();
 

 lem::Ptr<LS_ResultSet> rs_assocs( GetStorage().ListAssociatedEntries() );
 while( rs_assocs->Fetch() )
 {
  const int id = rs_assocs->GetInt(0);
  lem::Ptr<WordAssociation> assoc( GetStorage().LoadAssocitation(id) );
  assoc->SaveSQL( out, sql_version );
 }
 rs_assocs.Delete();
 out.flush();

 out.printf( "\n\n" );

 lem::Ptr<LS_ResultSet> misspelling( GetStorage().ListMisspelling() );
 while( misspelling->Fetch() )
  {
   int id_language = misspelling->GetInt(1);
   UFString old_word = sql_version.SqlStr(misspelling->GetUFString(2));
   UFString new_word = sql_version.SqlStr(misspelling->GetUFString(3));

   old_word = sql_version.SqlStr(old_word);
   new_word = sql_version.SqlStr(new_word);   

   out.printf( "INSERT INTO misspelling( id_language, original_word, substitution ) VALUES ( %d, '%us', '%us' );\n",
    id_language, old_word.c_str(), new_word.c_str() );
  }
 misspelling.Delete();
 out.eol();


 lem::Ptr<WordEntrySetEnumerator> wordentry_sets( wordentry_set->ListWordEntrySets() );
 while( wordentry_sets->Fetch() )
  {
   const WordEntrySetItem &wes = wordentry_sets->GetItem();

   lem::UFString s;
   for( std::set<int>::const_iterator it=wes.ies.begin(); it!=wes.ies.end(); ++it )
    {
     if( !s.empty() )
      s.Add_Dirty(L' ');

     s.Add_Dirty( lem::to_ustr(*it).c_str() );
    } 

   out.printf( "INSERT INTO word_entry_set( id, name, ies ) VALUES ( %d, '%us', '%us' );\n",
                 wes.GetId(), lem::to_upper(wes.GetName()).c_str(), s.c_str() );
  }
 wordentry_sets.Delete();
 out.eol();


 lem::Ptr<WordSetEnumerator> word_sets( wordentry_set->ListWordSets() );
 while( word_sets->Fetch() )
  {
   const WordSetItem &wes = word_sets->GetItem();

   lem::UFString s;
   for( std::set<lem::UCString>::const_iterator it=wes.words.begin(); it!=wes.words.end(); ++it )
    {
     if( !s.empty() )
      s.Add_Dirty(LexiconStorage::WORD_SET_DELIMITER);

     s.Add_Dirty( sql_version.SqlStr(*it) );
    } 

   out.printf( "INSERT INTO word_set( id, name, words, case_sensitive ) VALUES ( %d, '%us', '%us', %d );\n",
                 wes.GetId(), lem::to_upper(wes.GetName()).c_str(), s.c_str(), wes.case_sensitive ? 1 : 0 );
  }
 word_sets.Delete();
 out.eol();


 // именованные наборы словосочетаний
 lem::Ptr<LS_ResultSet> rs_collocation_sets( storage->ListCollocationSets() );
 while( rs_collocation_sets->Fetch() )
  {
   int id = rs_collocation_sets->GetInt(0);
   lem::UFString name = sql_version.SqlStr(rs_collocation_sets->GetUFString(1));
   int case_sensitive = rs_collocation_sets->GetInt(2);

   out.printf( "INSERT INTO collocation_set( id, name, case_sensitive ) VALUES ( %d, '%us', %d );\n",
                 id, name.c_str(), case_sensitive );
  }
 rs_collocation_sets.Delete();


 lem::Ptr<LS_ResultSet> rs_collocation_items( storage->ListCollocationSetItems() );
 while( rs_collocation_items->Fetch() )
  {
   int id = rs_collocation_items->GetInt(0);
   int id_set = rs_collocation_items->GetInt(1);
   lem::UFString words = sql_version.SqlStr(rs_collocation_items->GetUFString(2));
   int n_word = rs_collocation_items->GetInt(3);
   lem::UFString headword = sql_version.SqlStr(rs_collocation_items->GetUFString(4));

   out.printf( "INSERT INTO collocation_set_item( id, id_set, words, n_word, headword ) VALUES ( %d, %d, '%us', %d, '%us' );\n",
                 id, id_set, words.c_str(), n_word, headword.c_str() );
  }
 rs_collocation_items.Delete();


 lem::Ptr<LS_ResultSet> rs_collocation_headwords( storage->ListCollocationSetHeadwords() );
 while( rs_collocation_headwords->Fetch() )
  {
   int id = rs_collocation_headwords->GetInt(0);
   lem::UFString headword = sql_version.SqlStr(rs_collocation_headwords->GetUFString(1));
   int min_len = rs_collocation_headwords->GetInt(2);
   int max_len = rs_collocation_headwords->GetInt(3);

   out.printf( "INSERT INTO collocation_headword( id, headword, min_len, max_len ) VALUES ( %d, '%us', %d, %d );\n",
                 id, headword.c_str(), min_len, max_len );
  }
 rs_collocation_headwords.Delete();

 // --------------------------------------------

 lem::Ptr<LS_ResultSet> rs_wordform_sets( storage->ListWordformSets() );
 while( rs_wordform_sets->Fetch() )
  {
   int id = rs_wordform_sets->GetInt(0);
   lem::UFString name = sql_version.SqlStr(rs_wordform_sets->GetUFString(1));

   out.printf( "INSERT INTO wordform_set( id, name ) VALUES ( %d, '%us' );\n",
                 id, name.c_str() );
  }
 rs_wordform_sets.Delete();


 lem::Ptr<LS_ResultSet> rs_wordform_set_coords( storage->ListWordformSetCoords() );
 while( rs_wordform_set_coords->Fetch() )
  {
   int id = rs_wordform_set_coords->GetInt(0);
   lem::UFString coords = rs_wordform_set_coords->GetUFString(1);

   out.printf( "INSERT INTO wordform_set_coords( id, coords ) VALUES ( %d, '%us' );\n",
                 id, coords.c_str() );
  }
 rs_wordform_set_coords.Delete();


 lem::Ptr<LS_ResultSet> rs_wordform_set_items( storage->ListWordformSetItems() );
 while( rs_wordform_set_items->Fetch() )
  {
   const int id = rs_wordform_set_items->GetInt(0);
   const int id_set = rs_wordform_set_items->GetInt(1);
   lem::UFString word = sql_version.SqlStr( rs_wordform_set_items->GetUFString(2) );
   const int id_entry = rs_wordform_set_items->GetInt(3);
   const int id_coords = rs_wordform_set_items->GetInt(4);

   out.printf( "INSERT INTO wordform_set_item( id, id_set, word, id_entry, id_coords ) VALUES ( %d, %d, '%us', %d, %d );\n",
                 id, id_set, word.c_str(), id_entry, id_coords );
  }
 rs_wordform_set_items.Delete();


 // --------------------------------------------

 lem::Ptr<LS_ResultSet> rs_unb( storage->ListUnbreakableRules(ANY_STATE) );
 while( rs_unb->Fetch() )
  {
   const int id_rule = rs_unb->GetInt(0);
   lem::Ptr<LA_UnbreakableRule> rule( storage->GetUnbreakableRule(id_rule) );

   lem::UFString pattern(rule->GetPattern());
   pattern = sql_version.SqlStr(pattern);

   out.printf( "INSERT INTO unbreakable( id, name, id_language, is_regex,"
             " pattern, id_src ) VALUES ( %d, '%us', %d, %d, '%us', %d );\n",
             rule->GetId(), lem::to_upper(rule->GetName()).c_str(), rule->GetLanguage(),
             rule->IsRegex() ? 1 : 0,
             pattern.c_str(), rule->GetSourceLocation() );
  }

 out.eol();

 lem::Ptr<LS_ResultSet> rs_recog = storage->ListRecognitionRules(ANY_STATE,true);
 while( rs_recog->Fetch() )
  {
   const int id = rs_recog->GetInt(0);
   lem::Ptr<LA_RecognitionRule> rule = storage->GetRecognitionRule(id);
   
   lem::UFString condition(rule->GetCondition());
   condition = sql_version.SqlStr(condition);

   lem::UFString word;
   if( rule->IsWordMatcher() )
    {
     word = sql_version.SqlStr(condition);
     word.dress(L'\'');
    }
   else
    word = L"NULL";

   lem::UFString coords;
   coords.reserve(64);
   for( lem::Container::size_type i=0; i<rule->GetCoords().size(); ++i )
    {
     if( i>0 )
      coords.Add_Dirty(L' ');

     coords.Add_Dirty( to_ustr( rule->GetCoords()[i].GetCoord().GetIndex() ).c_str() );
     coords.Add_Dirty( L':' );
     coords.Add_Dirty( to_ustr( rule->GetCoords()[i].GetState() ).c_str() );
    }

   out.printf( "INSERT INTO recog_rule( id, name, id_language, is_syllab, is_regex, is_prefix, is_affix,"
               " r_condition, id_entry, rel, coords, id_src, word ) VALUES ( %d, '%us', %d, %d, %d, %d, %d, '%us', %d, %d, '%us', %d, %us );\n",
               rule->GetId(), lem::to_upper(rule->GetName()).c_str(), rule->GetLanguage(),
               rule->IsSyllab() ? 1 : 0,
               rule->IsRegex() ? 1 : 0,
               rule->IsPrefix() ? 1 : 0,
               rule->IsAffix() ? 1 : 0,
               condition.c_str(), rule->GetEntryKey(), rule->GetRel().GetInt(), coords.c_str(), rule->GetSourceLocation(), word.c_str() );
  }

 out.eol();

 lem::Ptr<LS_ResultSet> rs_ph( storage->ListPhoneticRules(ANY_STATE) );
 while( rs_ph->Fetch() )
  {
   int id = rs_ph->GetInt(0);
   lem::Ptr<LA_PhoneticRule> rule = storage->GetPhoneticRule(id);

   lem::UFString condition(rule->GetCondition().GetContext().c_str());
   condition = sql_version.SqlStr(condition);

   lem::UFString result(rule->GetResult().GetContext().c_str());
   result = sql_version.SqlStr(result);

   out.printf( "INSERT INTO ph_rule( id, name, id_language, is_prefix, is_affix,"
               " r_condition, r_result, rel, id_src ) VALUES ( %d, '%us', %d, %d, %d, '%us', '%us', %d, %d );\n",
               rule->GetId(), lem::to_upper(rule->GetName()).c_str(), rule->GetLanguage(),
               rule->IsPrefix() ? 1 : 0, rule->IsAffix() ? 1 : 0,
               condition.c_str(), result.c_str(), rule->GetVal().GetInt(), rule->GetSourceLocation() );
  }

 out.eol();

 lem::Ptr<LS_ResultSet> rs_syn = storage->ListSynPatternTrees();
 while( rs_syn->Fetch() )
  {
   const int id_tree = rs_syn->GetInt(0);
   const lem::UCString name = rs_syn->GetUCString(1);
   const lem::UCString uname = rs_syn->GetUCString(2);
   const int id_language = rs_syn->GetInt(3);
   const int pattern_type = rs_syn->GetInt(4);
   
   std::pair<SynPatternTreeNode*,lem::UCString> tree_name = storage->GetSynPatternTree(id_tree);
   lem::Ptr<SynPatternTreeNode> tree = tree_name.first;

   lem::MemStream mem(true);
   tree->SaveBin(mem);
   const int sz = mem.tellp();
   const char* bytes = mem.get_Block();
   lem::FString hex;
   Storage_Data2Hex( bytes, sz, hex );
   
   if( sql_version.type==SQL_Production::SQLite )
    {
     int id0=-1;
     int segment_no=0;

     out.printf( "INSERT INTO SynPatternTree( id_tree, id0, segment_no, name, uname, id_language, pattern_type, bin )"
                 " VALUES ( %d, %d, %d, '%us', '%us', %d, %d, X'%s' );\n", id_tree, id0, segment_no, name.c_str(), uname.c_str(), id_language, pattern_type, hex.c_str() );
 
    }
   else
    {
     out.printf( "INSERT INTO SynPatternTree( id_tree, name, uname, id_language, pattern_type, bin )"
                 " VALUES ( %d, '%us', '%us', %d, %d, 0x%s );\n", id_tree, name.c_str(), uname.c_str(), id_language, pattern_type, hex.c_str() );
    }
  }

 out.eol();

 lem::Ptr<LS_ResultSet> rs_c = storage->ListCropRules(ANY_STATE);
 while( rs_c->Fetch() )
  {
   const int id = rs_c->GetInt(0);
   lem::Ptr<LA_CropRule> rule = storage->GetPreprocessorCropRule(id);

   lem::UFString condition(rule->GetCondition());
   condition = sql_version.SqlStr(condition);

   lem::UFString result(rule->GetResult());
   result = sql_version.SqlStr(result);

   out.printf( "INSERT INTO crop_rule( id, name, id_language, is_prefix, is_affix,"
               " r_condition, r_result, is_regex, case_sensitive, id_src, rel )"
               " VALUES ( %d, '%us', %d, %d, %d, '%us', '%us', %d, %d, %d, %d );\n",
               id, lem::to_upper(rule->GetName()).c_str(), rule->GetLanguage(),
               rule->IsPrefix() ? 1 : 0, rule->IsAffix() ? 1 : 0,
               condition.c_str(), result.c_str(), rule->IsRegex() ? 1 : 0, rule->IsCaseSensitive() ? 1 : 0,
               rule->GetSourceLocation(), rule->GetRel().GetInt() );
  }

 out.eol();


 // ------------------
 // база знаний
 // ------------------
 
 lem::Ptr<LS_ResultSet> rs_kb1 = storage->ListFactGroups();
 while( rs_kb1->Fetch() )
  {
   const int id = rs_kb1->GetInt(0);
   const int id_language = rs_kb1->GetInt(1);
   lem::UCString name = rs_kb1->GetUCString(2);
   const int n_arg = rs_kb1->GetInt(3);
   const int n_ret = rs_kb1->GetInt(4);
   const int query_mode = rs_kb1->GetInt(5);
   const int ret_type = rs_kb1->GetInt(6);

   const int violation_score = rs_kb1->GetInt(7);
   const int violation_handler = rs_kb1->GetInt(8);

   out.printf( "INSERT INTO kb_facts( id, id_language, name, n_arg, n_ret, query_mode, ret_type, violation_score, violation_handler ) VALUES ( %d, %d, '%us', %d, %d, %d, %d, %d, %d );\n"
    , id, id_language, name.c_str(), n_arg, n_ret, query_mode, ret_type, violation_score, violation_handler );
  }
 rs_kb1.Delete();
 out.printf( "\n\n" );


 lem::Ptr<LS_ResultSet> rs_kb2 = storage->ListFacts();
 lem::UCString null_str(L"NULL");
 while( rs_kb2->Fetch() )
  {
   const int id = rs_kb2->GetInt(0);
   const int id_group = rs_kb2->GetInt(1);

   const int boolean_return = rs_kb2->GetInt(2);
   const int integer_return = rs_kb2->GetInt(3);

   lem::CString bool_ret, int_ret;
   if( boolean_return==-1 )
    bool_ret = "NULL";
   else
    bool_ret = lem::to_str(boolean_return);

   if( integer_return==-1 )
    int_ret = "NULL";
   else
    int_ret = lem::to_str(integer_return);

   const int false_score = rs_kb2->GetInt(14);

   out.printf( "INSERT INTO kb_fact( id, id_group, boolean_return, integer_return, false_score )"
               " VALUES ( %d, %d, %d, %d, %d );\n"
               , id, id_group, bool_ret.c_str(), int_ret.c_str(), false_score );
  }
 rs_kb2.Delete();
 out.printf( "\n\n" );


 lem::Ptr<LS_ResultSet> rs_kbi1 = storage->ListFactIndex1();
 while( rs_kbi1->Fetch() )
  {
   const int id = rs_kbi1->GetInt(0);
   const int id_group = rs_kbi1->GetInt(1);
   const int id_fact = rs_kbi1->GetInt(2);

   lem::UCString word1 = rs_kbi1->GetUCString(9);
   lem::UCString word2 = rs_kbi1->GetUCString(10);
   lem::UCString word3 = rs_kbi1->GetUCString(11);
   lem::UCString word4 = rs_kbi1->GetUCString(12);
   lem::UCString word5 = rs_kbi1->GetUCString(13);

   if( word1.empty() )
    word1 = null_str;
   else
    word1.dress_apostrophes();

   if( word2.empty() )
    word2 = null_str;
   else
    word2.dress_apostrophes();

   if( word3.empty() )
    word3 = null_str;
   else
    word3.dress_apostrophes();

   if( word4.empty() )
    word4 = null_str;
   else
    word4.dress_apostrophes();

   if( word5.empty() )
    word5 = null_str;
   else
    word5.dress_apostrophes();

   const int false_score = rs_kbi1->GetInt(14);

   out.printf( "INSERT INTO kb_fact_index1( id, id_group, id_fact,"
               " word1, word2, word3, word4, word5"
               " ) VALUES ( %d, %d, %d,"
               " %s, %s, %s, %s, %s );\n"
               , id, id_group, id_fact
               , word1.c_str(), word2.c_str(), word3.c_str(), word4.c_str(), word5.c_str()
             );
  }
 rs_kbi1.Delete();
 out.printf( "\n\n" );





 lem::Ptr<LS_ResultSet> rs_kbi2 = storage->ListFactIndex2();
 while( rs_kbi2->Fetch() )
  {
   const int id = rs_kbi2->GetInt(0);
   const int id_group = rs_kbi2->GetInt(1);
   const int id_fact = rs_kbi2->GetInt(2);

   const int id_entry1 = rs_kbi2->GetInt(4);
   const int id_entry2 = rs_kbi2->GetInt(5);
   const int id_entry3 = rs_kbi2->GetInt(6);
   const int id_entry4 = rs_kbi2->GetInt(7);
   const int id_entry5 = rs_kbi2->GetInt(8);

   CString entry1("NULL"), entry2("NULL"), entry3("NULL"), entry4("NULL"), entry5("NULL");

   if( id_entry1!=-1 ) entry1 = lem::to_str(id_entry1);
   if( id_entry2!=-1 ) entry2 = lem::to_str(id_entry2);
   if( id_entry3!=-1 ) entry3 = lem::to_str(id_entry3);
   if( id_entry4!=-1 ) entry4 = lem::to_str(id_entry4);
   if( id_entry5!=-1 ) entry5 = lem::to_str(id_entry5);

   out.printf( "INSERT INTO kb_fact_index2( id, id_group, id_fact,"
               " id_entry1, id_entry2, id_entry3, id_entry4, id_entry5"
               " ) VALUES ( %d, %d, %d,"
               " %s, %s, %s, %s, %s );\n"
               , id, id_group, id_fact
               , entry1.c_str(), entry2.c_str(), entry3.c_str(), entry4.c_str(), entry5.c_str()
             );
  }
 rs_kbi2.Delete();
 out.printf( "\n\n" );




 lem::Ptr<LS_ResultSet> rs_kb3 = storage->ListFactArguments();
 while( rs_kb3->Fetch() )
  {
   const int id = rs_kb3->GetInt(0);
   const int id_fact = rs_kb3->GetInt(1);
   const int argument_index = rs_kb3->GetInt(2);
   lem::UFString word_text( sql_version.SqlStr(rs_kb3->GetUFString(3)) );
   const int id_entry = rs_kb3->GetInt(4);

   const int id_class = rs_kb3->GetInt(5);
   lem::UFString wordentryset_name( sql_version.SqlStr(rs_kb3->GetUFString(6)) );
   lem::UFString wordset_name( sql_version.SqlStr(rs_kb3->GetUFString(7)) );
   const int n_coords = rs_kb3->GetInt(8);
   const int id_coord1 = rs_kb3->GetInt(9);

   const int id_state1 = rs_kb3->GetInt(10);
   const int affirm1 = rs_kb3->GetInt(11);
   const int id_coord2 = rs_kb3->GetInt(12);
   const int id_state2 = rs_kb3->GetInt(13);
   const int affirm2 = rs_kb3->GetInt(14);

   const int id_coord3 = rs_kb3->GetInt(15);
   const int id_state3 = rs_kb3->GetInt(16);
   const int affirm3 = rs_kb3->GetInt(17);
   const int id_coord4 = rs_kb3->GetInt(18);
   const int id_state4 = rs_kb3->GetInt(19);

   const int affirm4 = rs_kb3->GetInt(20);
   const int thesauruscheck_link = rs_kb3->GetInt(21);
   const int thesauruscheck_entry = rs_kb3->GetInt(22);
   const int is_positive = rs_kb3->GetInt(23);
   const int is_regex = rs_kb3->GetInt(24);
   const int case_sensitive = rs_kb3->GetInt(25);
   const int id_metaentry = rs_kb3->GetInt(26);

   out.printf( "INSERT INTO kb_argument_point("
               " id, id_fact, argument_index, word_text, id_entry,"
               " id_class, wordentryset_name, wordset_name, n_coords, id_coord1,"
               " id_state1, affirm1, id_coord2, id_state2, affirm2,"
               " id_coord3, id_state3, affirm3, id_coord4, id_state4,"
               " affirm4, thesauruscheck_link, thesauruscheck_entry, is_positive,"
               " is_regex, case_sensitive, id_metaentry"
               "  ) VALUES ("
               " %d, %d, %d, '%us', %d,"
               " %d, '%us', '%us', %d, %d,"
               " %d, %d, %d, %d, %d,"
               " %d, %d, %d, %d, %d,"
               " %d, %d, %d, %d,"
               " %d, %d, %d );\n",
               id, id_fact, argument_index, word_text.c_str(), id_entry,
               id_class, wordentryset_name.c_str(), wordset_name.c_str(), n_coords, id_coord1,
               id_state1, affirm1, id_coord2, id_state2, affirm2,
               id_coord3, id_state3, affirm3, id_coord4, id_state4,
               affirm4, thesauruscheck_link, thesauruscheck_entry, is_positive,
               is_regex, case_sensitive, id_metaentry );
  }
 rs_kb3.Delete();
 out.printf( "\n\n" );

 // ---- Выгружаем tree scorers

 lem::Ptr<LS_ResultSet> ts_head_lemma( GetStorage().ListTreeScorerLemmas() );
 while( ts_head_lemma->Fetch() )
  {
   int id_entry = ts_head_lemma->GetInt(0);
   int id_head_point = ts_head_lemma->GetInt(1);
   int score_type = ts_head_lemma->GetInt(2);
   UFString score_expr = ts_head_lemma->GetUFString(3);
   int root_node = ts_head_lemma->GetInt(4);
   int id_group = ts_head_lemma->GetInt(5);

   out.printf( "INSERT INTO ts_head_lemma( id_entry, id_head_point, score_type, score_expr, root_node, id_group ) VALUES ( %d, %d, %d, '%us', %d, %d );\n",
    id_entry, id_head_point, score_type, score_expr.c_str(), root_node, id_group );
  }
 ts_head_lemma.Delete();
 out.eol();


 lem::Ptr<LS_ResultSet> ts_head_word( GetStorage().ListTreeScorerWords() );
 while( ts_head_word->Fetch() )
  {
   lem::UFString word_text( sql_version.SqlStr(ts_head_word->GetUFString(0)) );
   int id_head_point = ts_head_word->GetInt(1);
   int score_type = ts_head_word->GetInt(2);
   UFString score_expr = ts_head_word->GetUFString(3);
   int root_node = ts_head_word->GetInt(4);
   int id_group = ts_head_word->GetInt(5);

   out.printf( "INSERT INTO ts_head_word( word, id_head_point, score_type, score_expr, root_node, id_group ) VALUES ( '%us', %d, %d, '%us', %d, %d );\n",
    word_text.c_str(), id_head_point, score_type, score_expr.c_str(), root_node, id_group );
  }
 ts_head_word.Delete();
 out.eol();



 lem::Ptr<LS_ResultSet> ts_point = storage->ListTreeScorerPoints();
 while( ts_point->Fetch() )
  {
   const int id = ts_point->GetInt(0);
   const int id_parent = ts_point->GetInt(1);
   lem::UFString word_text( sql_version.SqlStr(ts_point->GetUFString(2)) );
   const int id_entry = ts_point->GetInt(3);
   const int id_class = ts_point->GetInt(4);
   lem::UFString wordentryset_name( sql_version.SqlStr(ts_point->GetUFString(5)) );
   lem::UFString wordset_name( sql_version.SqlStr(ts_point->GetUFString(6)) );
   lem::UFString wordformset_name( sql_version.SqlStr(ts_point->GetUFString(7)) );

   const int n_coords = ts_point->GetInt(8);

   const int id_coord1 = ts_point->GetInt(9);
   const int id_state1 = ts_point->GetInt(10);
   const int affirm1 = ts_point->GetInt(11);

   const int id_coord2 = ts_point->GetInt(12);
   const int id_state2 = ts_point->GetInt(13);
   const int affirm2 = ts_point->GetInt(14);

   const int id_coord3 = ts_point->GetInt(15);
   const int id_state3 = ts_point->GetInt(16);
   const int affirm3 = ts_point->GetInt(17);

   const int id_coord4 = ts_point->GetInt(18);
   const int id_state4 = ts_point->GetInt(19);
   const int affirm4 = ts_point->GetInt(20);

   const int thesauruscheck_link = ts_point->GetInt(21);
   const int thesauruscheck_entry = ts_point->GetInt(22);
   const int is_positive = ts_point->GetInt(23);

   const int children_quantification_min_count = ts_point->GetInt(24);
   const int children_quantification_max_count = ts_point->GetInt(25);

   const int n_set_checkers = ts_point->GetInt(26);

   lem::UFString set_name1( sql_version.SqlStr(ts_point->GetUFString(27)) );
   const int set_type1 = ts_point->GetInt(28);
   const int set_affirm1 = ts_point->GetInt(29);

   lem::UFString set_name2( sql_version.SqlStr(ts_point->GetUFString(30)) );
   const int set_type2 = ts_point->GetInt(31);
   const int set_affirm2 = ts_point->GetInt(32);

   lem::UFString set_name3( sql_version.SqlStr(ts_point->GetUFString(33)) );
   const int set_type3 = ts_point->GetInt(34);
   const int set_affirm3 = ts_point->GetInt(35);

   const int link_type = ts_point->GetInt(36);
   const int id_metaentry = ts_point->GetInt(37);
   const int relative_position = ts_point->GetInt(38);
   const int id_src = ts_point->GetInt(39);
   const int id_group = ts_point->GetInt(40);

   const int quantification_min_count = ts_point->GetInt(41);
   const int quantification_max_count = ts_point->GetInt(42);

   lem::UFString marker( sql_version.SqlStr(ts_point->GetUFString(43)) );

   const int n_backref = ts_point->GetInt(44);

   int br_affirm_0 = -1;
   int br_coord0_0 = -1;
   lem::UFString br_marker_0;
   int br_coord1_0 = -1;
   int br_for_group_0 = -1;

   int br_affirm_1 = -1;
   int br_coord0_1 = -1;
   lem::UFString br_marker_1;
   int br_coord1_1 = -1;
   int br_for_group_1 = -1;

   int br_affirm_2 = -1;
   int br_coord0_2 = -1;
   lem::UFString br_marker_2;
   int br_coord1_2 = -1;
   int br_for_group_2 = -1;

   if( n_backref>0 )
    {
     br_affirm_0 = ts_point->GetInt(45);
     br_coord0_0 = ts_point->GetInt(46);
     br_marker_0 = sql_version.SqlStr(ts_point->GetUFString(47));
     br_coord1_0 = ts_point->GetInt(48);
     br_for_group_0 = ts_point->GetInt(49);
    }

   if( n_backref>1 )
    {
     br_affirm_1 = ts_point->GetInt(50);
     br_coord0_1 = ts_point->GetInt(51);
     br_marker_1 = sql_version.SqlStr(ts_point->GetUFString(52));
     br_coord1_1 = ts_point->GetInt(53);
     br_for_group_1 = ts_point->GetInt(54);
    }

   if( n_backref>2 )
    {
     br_affirm_2 = ts_point->GetInt(55);
     br_coord0_2 = ts_point->GetInt(56);
     br_marker_2 = sql_version.SqlStr(ts_point->GetUFString(57));
     br_coord1_2 = ts_point->GetInt(58);
     br_for_group_2 = ts_point->GetInt(59);
    }

   LEM_CHECKIT_Z( n_backref<=3 );

   out.printf( "INSERT INTO ts_point("
               " id, id_parent, word_text, id_entry,"
               " id_class, wordentryset_name, wordset_name, wordformset_name, "
               " n_coords, id_coord1, id_state1, affirm1,"
               " id_coord2, id_state2, affirm2, id_coord3, id_state3,"
               " affirm3, thesauruscheck_link, thesauruscheck_entry, is_positive, children_quantification_min_count, children_quantification_max_count,"
               " id_coord4, id_state4, affirm4,"
               " n_setcheckers, set_name1, set_type1, set_affirm1, set_name2,"
               " set_type2, set_affirm2, set_name3, set_type3, set_affirm3,"
               " link_type, id_metaentry, relative_position, id_src, id_group,"
               " quantification_min_count, quantification_max_count, marker,"
               "n_backref,"
               "br_affirm_0, br_coord0_0, br_marker_0, br_coord1_0, br_for_group_0,"
               "br_affirm_1, br_coord0_1, br_marker_1, br_coord1_1, br_for_group_1,"
               "br_affirm_2, br_coord0_2, br_marker_2, br_coord1_2, br_for_group_2"
               " ) VALUES ("
               " %d,  %d, '%us', %d,"
               " %d, '%us', '%us', '%us',"
               " %d, %d, %d, %d," 
               " %d, %d, %d, %d, %d,"
               " %d, %d, %d, %d, %d, %d,"
               " %d, %d, %d,"
               " %d, '%us', %d, %d, '%us',"
               " %d, %d, '%us', %d, %d,"
               " %d, %d, %d, %d, %d,"
               " %d, %d, '%us',"
               " %d,"
               " %d, %d, '%us', %d, %d,"
               " %d, %d, '%us', %d, %d,"
               " %d, %d, '%us', %d, %d"
               " );\n",
               id, id_parent, word_text.c_str(), id_entry,
               id_class, wordentryset_name.c_str(), wordset_name.c_str(), wordformset_name.c_str(),
               n_coords, id_coord1, id_state1, affirm1,
               id_coord2, id_state2, affirm2, id_coord3, id_state3,
               affirm3, thesauruscheck_link, thesauruscheck_entry, is_positive, children_quantification_min_count, children_quantification_max_count,
               id_coord4, id_state4, affirm4,
               n_set_checkers, set_name1.c_str(), set_type1, set_affirm1, set_name2.c_str(),
               set_type2, set_affirm2, set_name3.c_str(), set_type3, set_affirm3,
               link_type, id_metaentry, relative_position, id_src, id_group,
               quantification_min_count, quantification_max_count, marker.c_str(),
               n_backref,
               br_affirm_0, br_coord0_0, br_marker_0.c_str(), br_coord1_0, br_for_group_0,
               br_affirm_1, br_coord0_1, br_marker_1.c_str(), br_coord1_1, br_for_group_1,
               br_affirm_2, br_coord0_2, br_marker_2.c_str(), br_coord1_2, br_for_group_2
              );
  }
 ts_point.Delete();
 out.printf( "\n\n" );


 lem::Ptr<LS_ResultSet> ts_group = storage->ListTreeScorerGroups();
 while( ts_group->Fetch() )
  {
   const int id = ts_group->GetInt(0);
   lem::UFString name( sql_version.SqlStr(ts_group->GetUFString(1)) );
   const int allow_unmatched_children = ts_group->GetInt(2);
 
   out.printf( "INSERT INTO ts_group(id,name,allow_unmatched_children) VALUES (%d,'%us',%d);\n", id, name.c_str(), allow_unmatched_children );
  }
 ts_group.Delete();
 out.printf( "\n\n" );


 lem::Ptr<LS_ResultSet> ts_group2root = storage->ListTreeScoreGroupMembers();
 while( ts_group2root->Fetch() )
  {
   const int id_group = ts_group2root->GetInt(0);
   const int id_root = ts_group2root->GetInt(1);

   out.printf( "INSERT INTO ts_group2root(id_group,id_root) VALUES (%d,%d);\n", id_group, id_root );
  }
 ts_group2root.Delete();
 out.printf( "\n\n" );




 lem::Ptr<LS_ResultSet> ts_gts = storage->ListGenericTreeScorers();
 while( ts_gts->Fetch() )
  {
   const int id = ts_gts->GetInt(0);
   const int id_head_point = ts_gts->GetInt(1);
   const int id_group = ts_gts->GetInt(2);
   lem::UFString score_expr = sql_version.SqlStr(ts_gts->GetUFString(3));
   const int score_type = ts_gts->GetInt(4);

   out.printf( "INSERT INTO generic_tree_scorer(id,id_head_point,id_group,score_type,score_expr) VALUES (%d,%d,%d,%d,'%us');\n", id, id_head_point, id_group, score_type, score_expr.c_str() );
  }
 ts_gts.Delete();
 out.printf( "\n\n" );




 lem::Ptr<LS_ResultSet> ts_pr = storage->ListTreeScorerPredicates();
 while( ts_pr->Fetch() )
  {
   const int id = ts_pr->GetInt(0);
   const int id_point = ts_pr->GetInt(1);
   UCString func_name = ts_pr->GetUCString(2);
   const int narg = ts_pr->GetInt(3);
   const int id_class1 = ts_pr->GetInt(4);

   out.printf( "INSERT INTO ts_predicate(id,id_point,func_name,narg,id_class1) VALUES (%d,%d,'%us',%d,%d);\n", id, id_point, func_name.c_str(), narg, id_class1 );
  }
 ts_pr.Delete();
 out.printf( "\n\n" );


 out.printf( "\n\n" );

 return;
}

#endif
