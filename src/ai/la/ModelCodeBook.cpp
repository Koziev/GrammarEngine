#include <lem/quantors.h>
#include <lem/solarix/MorphologyModels.h>
#include <lem/solarix/word_form.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntry.h>
#include <lem/unicode.h>
#include <lem/oformatter.h>
#include <lem/quantors.h>

using namespace Solarix;


ModelCodeBook::ModelCodeBook()
{
 suffix_len=UNKNOWN;
 START_id=END_id=UNKNOWN;
 START_tag_id=END_tag_id=UNKNOWN;
}


void ModelCodeBook::LoadUtf8( lem::Stream & bin, lem::UCString & str )
{
 lem::uint32_t utf8_len=0;
 bin.read( &utf8_len, sizeof(utf8_len) );

 lem::uint8_t buffer[ lem::UCString::max_len*6+1 ];
 bin.read( buffer, utf8_len );
 buffer[utf8_len] = 0;
 lem::FString u( (const char*)buffer );
 str = lem::UCString(lem::from_utf8(u).c_str());

 return;
}


void ModelCodeBook::LoadBin( lem::Stream & bin )
{
 lem::uint32_t flags=0;
 bin.read( &flags, sizeof(flags) );

 bin.read( &suffix_len, sizeof(suffix_len) );
 bin.read( &context_size, sizeof(context_size) );

 lem::int32_t undiv_count=-1;
 bin.read( &undiv_count, sizeof(undiv_count) );

 for( int i=0; i<undiv_count; ++i )
  {
   lem::UCString w;
   LoadUtf8( bin, w );
   undividable_words.insert( w );
  }

 lem::uint32_t ntags;
 bin.read( &ntags, sizeof(ntags) );
 for( int i=0; i<ntags; ++i )
  {
   ModelTagMatcher * tag = new ModelTagMatcher();
   tag->LoadBin(bin);
   matchers.push_back(tag);
   id2matcher.insert( std::make_pair( tag->GetId(), tag) );
  }

 lem::int32_t n_suffix;
 bin.read( &n_suffix, sizeof(n_suffix) );
 for( int i=0; i<n_suffix; ++i )
  {
   lem::UCString sfx;
   LoadUtf8( bin, sfx );
   lem::int32_t id;
   bin.read( &id, sizeof(id) );
   suffices.insert( std::make_pair( sfx, id ) );
  }

 bin.read( &START_id, sizeof(START_id) );
 bin.read( &END_id, sizeof(END_id) );

 bin.read( &START_tag_id, sizeof(START_tag_id) );
 bin.read( &END_tag_id, sizeof(END_tag_id) );

 lem::int32_t n_param;
 bin.read( &n_param, sizeof(n_param) );
 for( int i=0; i<n_param; ++i )
 {
  lem::UCString param_name, param_value;
  LoadUtf8( bin, param_name );
  LoadUtf8( bin, param_value );
  model_params.push_back( std::make_pair( param_name, param_value ) );
 }

 // Списки семантических тегов для словоформ и для лемм
 lem::int32_t n_wordform_tag_items=0;
 bin.read( &n_wordform_tag_items, sizeof(n_wordform_tag_items) );
 lem::UCString wordform_1, tag_1;
 for( int i=0; i<n_wordform_tag_items; ++i )
 {
  LoadUtf8( bin, wordform_1 );
  lem::int16_t ntag;
  bin.read( &ntag, sizeof(ntag) );
  for( int j=0; j<ntag; ++j )
  {
   LoadUtf8( bin, tag_1 );
   wordform2semantic.insert( std::make_pair(wordform_1,tag_1) );
  } 
 }
 
 lem::int32_t n_lemma_tag_items=0;
 bin.read( &n_lemma_tag_items, sizeof(n_lemma_tag_items) );
 lem::UCString lemma_2, tag_2;
 for( int i=0; i<n_lemma_tag_items; ++i )
 {
  LoadUtf8( bin, lemma_2 );
  lem::int16_t ntag;
  bin.read( &ntag, sizeof(ntag) );
  for( int j=0; j<ntag; ++j )
  {
   LoadUtf8( bin, tag_2 );
   lemma2semantic.insert( std::make_pair(lemma_2,tag_2) );
  }
 }


 return;
}


const lem::UCString ModelCodeBook::FindModelParam( const wchar_t * param_name, const wchar_t * default_value ) const
{
 for( lem::Container::size_type i=0; i<model_params.size(); ++i )
 {
  if( model_params[i].first.eqi( param_name ) )
   return model_params[i].second;
 }

 return lem::UCString( default_value );
}



const ModelTagMatcher* ModelCodeBook::GetTagMatcher( int id ) const
{
 std::map<int,const ModelTagMatcher*>::const_iterator it = id2matcher.find(id);
 if( it==id2matcher.end() )
  return NULL;
 else
  return it->second;
}


int ModelCodeBook::GetSuffixId( const LexerTextPos * token ) const
{
 const lem::UCString & word = * token->GetWordform()->GetName();
 const lem::UCString & uword = * token->GetWordform()->GetNormalized();

 // получаем суффикс.
 lem::UCString sfx;

 if( uword.length()<=suffix_len )
  {
   sfx = uword;
  }
 else
  {
   if( undividable_words.find(uword)!=undividable_words.end() )
    sfx = uword;
   else
    {
     // для чисел оставляем последнюю цифру
     if( lem::is_int(uword) )
      {
       sfx = uword.back();
      }
     else
      {
       sfx = L"~";
       sfx += lem::right( uword, suffix_len );
      }
    }
  }

 int id=UNKNOWN; 
 std::map<lem::UCString,int>::const_iterator it = suffices.find(sfx);
 if( it!=suffices.end() )
  id = it->second;

 return id;
}





void ModelCodeBook::GetSemanticTags( Dictionary & dict, const LexerTextPos * token, lem::MCollect<const wchar_t*> & tags ) const
{
 // теги для словоформы
 lem::UCString wordform = lem::to_upper( * token->GetWordform()->GetName() );
 typedef std::multimap<lem::UCString,lem::UCString>::const_iterator IT;
 std::pair<IT,IT> tags_range = wordform2semantic.equal_range( wordform );
 for( IT it=tags_range.first; it!=tags_range.second; ++it )
 {
  tags.push_back( it->second.c_str() );
 }
 
 // теги для лемм
 const Word_Form * wf = token->GetWordform();
 if( wf->VersionCount()==1 )
 {
  int id_entry = wf->GetEntryKey();
  if( id_entry!=UNKNOWN )
  {
   lem::UCString lemma = lem::to_upper( dict.GetSynGram().GetEntry( id_entry ).GetName() );

   std::pair<IT,IT> tags_range = lemma2semantic.equal_range( lemma );
   for( IT it=tags_range.first; it!=tags_range.second; ++it )
   {
    tags.push_back( it->second.c_str() );
   }
  }
 }
 else
 {
  lem::MCollect<int> entries;
  lem::MCollect<lem::UCString> lemmas;
  for( int i=0; i<wf->VersionCount(); ++i )
  {
   int id_entry = wf->GetVersion(i)->GetEntryKey();
   if( entries.find(id_entry)==UNKNOWN )
    {
     entries.push_back(id_entry);
    
     lem::UCString lemma = lem::to_upper(dict.GetSynGram().GetEntry( id_entry ).GetName());
     if( lemmas.find(lemma)==UNKNOWN )
     {
      lemmas.push_back( lemma );
      std::pair<IT,IT> tags_range = lemma2semantic.equal_range( lemma );
      for( IT it=tags_range.first; it!=tags_range.second; ++it )
      {
       tags.push_back( it->second.c_str() );
      }
     }
    }
  }
 }
 

 return;
}


bool ModelCodeBook::DetectAa( const LexerTextPos * token ) const
{
 const lem::UCString & word = * token->GetWordform()->GetName();
 const lem::UCString & uword = * token->GetWordform()->GetNormalized();

 return word.length()>1 && word[0]==uword[0] && word[1]!=uword[1];
}


const ModelTagMatcher* ModelCodeBook::Match( const Word_Form * version, Dictionary & dict ) const
{
 for( lem::Container::size_type i=0; i<matchers.size(); ++i )
  if( matchers[i]->Match( * version, dict ) )
   return matchers[i];

 return NULL;
}


void ModelCodeBook::PrintTags( lem::OFormatter & out, Dictionary & dict ) const
{
 for( lem::Container::size_type i=0; i<matchers.size(); ++i )
  {
   out.printf( "matcher[%d] ==> ", i );
   matchers[i]->Print(out,dict);
   out.eol();
  } 

 return;
}


