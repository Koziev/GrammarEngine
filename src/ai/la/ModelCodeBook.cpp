#include <lem/quantors.h>
#include <lem/solarix/MorphologyModels.h>
#include <lem/solarix/word_form.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/unicode.h>
#include <lem/quantors.h>

using namespace Solarix;


ModelCodeBook::ModelCodeBook()
{
 suffix_len=UNKNOWN;
 START_id=END_id=UNKNOWN;
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

 return;
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

