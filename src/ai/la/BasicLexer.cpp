#if defined SOL_CAA

#include <lem/solarix/word_form.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/TrMorphologyTracer.h>

#if defined SOL_DEBUGGING
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/PartOfSpeech.h>
#endif

#include <lem/solarix/BasicLexer.h>


using namespace Solarix;

BasicLexer::BasicLexer( Solarix::Dictionary * _dict, const TextRecognitionParameters & _params, TrTrace * _trace )
 : dict(_dict), params(_params), trace(_trace), wf_end(NULL)
{
 LEM_CHECKIT_Z( !params.language_ids.empty() );

 begin_token=NULL;

 use_recognition_cache=false;
 path_count=1;

 return;
}


BasicLexer::~BasicLexer()
{
 for( lem::Container::size_type i=0; i<wordforms.size(); ++i )
  delete wordforms[i];

 for( lem::Container::size_type i=0; i<positions.size(); ++i )
  delete positions[i];

 return;
}


// Начинается новая сессия распознавания. Производные классы должны
// очистить рабочие кэши.
void BasicLexer::ResetParams( const TextRecognitionParameters & _params )
{
 params = _params;
 recognitions.clear(); // так как может изменится степень нечеткости распознавания слов, то очистим этот кэш.
 edges.clear();
 end_tokens.clear();

 return;
}



const LexerTextPos * BasicLexer::GetBeginToken()
{
 if( begin_token==NULL )
  {
   // Для некоторых операций с графом может быть полезно, что справа от начального токена есть специальный токен "левее левой границы".
   // В частности, он позволяет работать функции @optional().

   Word_Form *wf_margin = new Word_Form( Solarix::Lexem(L"") );
   wordforms.push_back(wf_margin);

   LexerTextPos_BeyondLeft * margin = new LexerTextPos_BeyondLeft(wf_margin);
   positions.push_back(margin);

   Word_Form *wf = new Predef_Word_Form( dict->GetSynGram().I_BEGIN, dict->GetSynGram() );
   wordforms.push_back(wf);

   LexerTextPos_Begin * t = new LexerTextPos_Begin( margin, wf );
   positions.push_back(t);

   margin->SetNextChained( t );

   begin_token = t;
  }

 return begin_token;
}




const LexerTextPos * BasicLexer::GetEndToken( const LexerTextPos * last_token )
{
 CACHED_ENDS::const_iterator it = end_tokens.find(last_token);
 if( it!=end_tokens.end() )
  return it->second;

 if( wf_end==NULL )
  {
   wf_end = new Predef_Word_Form( dict->GetSynGram().I_END, dict->GetSynGram() );
   wordforms.push_back(wf_end);
  }

 LexerTextPos_End * t = new LexerTextPos_End( last_token, wf_end );
 positions.push_back(t);

 edges.insert( std::make_pair( last_token, t ) );
 end_tokens.insert( std::make_pair( last_token, t ) );
 
 return t;
}






void BasicLexer::FetchN( const LexerTextPos *current_token, int n, lem::MCollect<const LexerTextPos*> & final_tokens )
{
 if( n==0 )
  {
   if( current_token->GetWordform()!=NULL )
    final_tokens.push_back(current_token);
  }
 else
  {
   if( current_token->GetNextChained()!=NULL )
    {
     FetchN( current_token->GetNextChained(), n-1, final_tokens );
    }
   else if( current_token->IsEnd() )
    {
     final_tokens.push_back(current_token);
    }
   else if( current_token->IsTerminator() || current_token->IsBeyondRight() )
    {
     return;
    }
   else
    {
     lem::MCollect<const LexerTextPos*> next;
     Fetch( current_token, next );

     for( lem::Container::size_type i=0; i<next.size(); ++i )
      FetchN( next[i], n-1, final_tokens );
    }
  }

 return;
}

namespace
{
 static bool score_comparer( const LexerTextPos * a, const LexerTextPos * b )
 {
  const int sa = a->GetScore()+a->GetWordform()->GetMaxScore();
  const int sb = b->GetScore()+b->GetWordform()->GetMaxScore();
  return sa < sb;
 }
 
}


// сортирует список токенов так, что сначала идут самые большие оценки
void BasicLexer::SortTokensByScoreDesc( lem::MCollect<const LexerTextPos*> & tokens ) const
{
 if( tokens.size()>1 )
  std::sort( tokens.begin(), tokens.end(), score_comparer );

 return;
}


// Находим все листься, стартуя в токене current.
void BasicLexer::FetchEnds( const LexerTextPos * current, lem::MCollect<const LexerTextPos*> & right_ends, int max_right_leaves )
{
 if( current->IsEnd() )
  right_ends.push_back( current );
 else if( !current->IsTerminator() )
  {
   if( CastSizeToInt(right_ends.size()) < max_right_leaves )
    {
     lem::MCollect<const LexerTextPos*> next;
     Fetch( current, next );

     SortTokensByScoreDesc( next );

     for( lem::Container::size_type i=0; i<next.size() && CastSizeToInt(right_ends.size())<max_right_leaves; ++i )
      FetchEnds( next[i], right_ends, max_right_leaves );
    }
  }

 return;
}


#if defined SOL_DEBUGGING
void BasicLexer::PrintRecognitions( lem::OFormatter & to ) const
{
 typedef std::multimap< lem::UCString, const Word_Form* > WORDS;
 WORDS words;

 std::set<lem::UCString> lexems;

 for( lem::Container::size_type i=0; i<wordforms.size(); ++i )
  {
   const lem::UCString & w = *wordforms[i]->GetName();
   words.insert( std::make_pair( w, wordforms[i] ) );
   lexems.insert( w );
  }

 for( std::set<lem::UCString>::const_iterator it=lexems.begin(); it!=lexems.end(); ++it )
  {
   to.printf( "Word %vfE%us%vn: ", it->c_str() );

   std::pair<WORDS::const_iterator,WORDS::const_iterator> p( words.equal_range(*it) );
   int n=0;
   for( WORDS::const_iterator it2=p.first; it2!=p.second; ++it2 )
    n++;

   to.printf( "%d %s:\n", n, n>1 ? "recognitions" : "recognition" );

   lem::MCollect<Solarix::Word_Form> unique;

   for( WORDS::const_iterator it2=p.first; it2!=p.second; ++it2 )
    {
     const Word_Form * wf = it2->second;

     int nver = wf->VersionCount();
     for( int iver=0; iver<nver; ++iver )
      {
       Word_Form wf1( *wf->GetVersion(iver), false );

       bool found=false;
       for( lem::Container::size_type k=0; k<unique.size(); ++k )
        {
         if( unique[k].GetEntryKey() == wf1.GetEntryKey() && *unique[k].GetName()==*wf1.GetName() && unique[k].GetPairs()==wf1.GetPairs() )
          {
           found=true;
           break;
          }
        }

       if( !found )
        {
         unique.push_back(wf1);
 
         to.printf( "ekey=%d ", wf1.GetEntryKey() );
      
         if( wf1.GetEntryKey()!=UNKNOWN )
          {
           const SG_Entry & e = dict->GetSynGram().GetEntry( wf1.GetEntryKey() );
           const SG_Class & c = dict->GetSynGram().GetClass( e.GetClass() );
           to.printf( "%us:%us{} --> ", c.GetName().c_str(), e.GetName().c_str() );
          } 
      
         wf1.Print( to, &dict->GetSynGram(), true );
         to.eol();
        }
      }

     to.eol();
    }

   to.printf( "%60h-\n" );
   to.eol();
  }
 

 return;
}
#endif



bool BasicLexer::Fetch( const LexerTextPos * current, lem::MCollect<const LexerTextPos*> & next )
{
 return Fetch( current, NULL, next );
}

void BasicLexer::FilterRecognitions( const LexerTextPos * token, const std::set<int> & selected_recognitions, bool remove_incorrect_alts )
{
 for( lem::Container::size_type i=0; i<positions.size(); ++i )
  {
   if( positions[i] == token )
    {
     if( remove_incorrect_alts )
      {
       Word_Form * new_wf = token->GetWordform()->CreateNewVersioned( selected_recognitions );
       wordforms.push_back(new_wf);
       positions[i]->ReplaceWordform( new_wf );
      }
     else
      {
       Word_Form * new_wf = token->GetWordform()->CreateNewVersionedSorted( selected_recognitions );
       wordforms.push_back(new_wf);
       positions[i]->ReplaceWordform( new_wf );
      }

     break;
    }
  }

 return;
}


bool BasicLexer::IsTooManyTokens( int new_branching ) const
{
 return (path_count * new_branching) >= 255;
}

void BasicLexer::AddBranching( int new_branching )
{
 if( new_branching>0 )
  path_count *= new_branching;
}

void BasicLexer::LimitBranching( lem::MCollect<const LexerTextPos*> & tokens ) const
{
 if( IsTooManyTokens(CastSizeToInt(tokens.size())) )
  {
   // ограничим ветвление - оставим только самый длинный токен
   int max_index=0, max_len=0;
   for( lem::Container::size_type i=0; i<tokens.size(); ++i )
    if( tokens[i]->GetWordLength() > max_len )
     {
      max_len = tokens[i]->GetWordLength();
      max_index = CastSizeToInt(i);
     }

   const LexerTextPos * best_token = tokens[max_index];
   tokens.clear();
   tokens.push_back( best_token );
  }
}


void BasicLexer::ReplaceTokenWordform( LexerTextPos * token, Word_Form * new_wordform )
{
 wordforms.push_back( new_wordform );
 token->ReplaceWordform( new_wordform );
 return;
}



#endif
