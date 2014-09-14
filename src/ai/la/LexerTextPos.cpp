#include <lem/runtime_checks.h>
#include <lem/solarix/word_form.h>
#include <lem/solarix/LexerTextPos.h>

using namespace Solarix;

LexerTextPos::LexerTextPos(
                           const LexerTextPos * _previous,
                           const Word_Form * _wordform,
                           int _score,
                           int _start,
                           int _length,
                           int _wordindex
                          )
 : start_position(_start), token_length(_length), wordform(_wordform),
   score(_score), previous(_previous), next_chained(NULL), WordIndex(_wordindex), token_flags(0), creat_flags(0)
{
}

int LexerTextPos::GetWordLength() const
{
 LEM_CHECKIT_Z( wordform!=NULL );
 return wordform->GetName()->length();
}


void LexerTextPos::CollectPathToLeft( int count, lem::MCollect<const Word_Form*> & org ) const
{
 LEM_CHECKIT_Z( count>=0 );

 org.push_back( wordform );

 if( count>0 && previous!=NULL )
  previous->CollectPathToLeft( count-1, org );

 return;
}


void LexerTextPos::ReplaceWordform( const Word_Form * new_wordform )
{
 wordform=new_wordform;
// wordform_scores.resize( wordform->VersionCount() );
// wordform_scores.Nullify();
 return;
}


void LexerTextPos::Collect_Right2Left( const LexerTextPos *left_boundary, lem::MCollect<const LexerTextPos*> & inverted_path ) const
{
 LEM_CHECKIT_Z( left_boundary!=NULL );

 inverted_path.push_back(this);

 if( this != left_boundary && previous!=NULL )
  previous->Collect_Right2Left( left_boundary, inverted_path );
   
 return;  
}


void LexerTextPos::Collect_Right2Left( int count, lem::MCollect<const LexerTextPos*> & inverted_path ) const
{
 inverted_path.push_back(this);
 if( count>0 && !IsBegin() && previous!=NULL )
  GetPrev()->Collect_Right2Left( count-1, inverted_path );

 return;
}



LexerTextPos_Begin::LexerTextPos_Begin( const LexerTextPos_BeyondLeft * left_margin, const Word_Form * wf )
 : LexerTextPos( left_margin, wf, 0, 0, 0, -1 )
{
 token_flags = 4;
}



LexerTextPos_End::LexerTextPos_End( const LexerTextPos * previous, const Word_Form * wf )
 : LexerTextPos( previous, wf, 0, lem::int_max, 0, lem::int_max )
{
 token_flags = 1;
}


LexerTextPos_Terminator::LexerTextPos_Terminator()
 : LexerTextPos( NULL, NULL, 0, 0, 0, -1 )
{
 token_flags = 2;
}



LexerTextPos_BeyondRight::LexerTextPos_BeyondRight( const LexerTextPos * previous, const Word_Form * wf )
 : LexerTextPos( previous, wf, 0, lem::int_max, 0, lem::int_max )
{
 token_flags = 3;
}


LexerTextPos_BeyondLeft::LexerTextPos_BeyondLeft( const Word_Form * wf )
 : LexerTextPos( NULL, wf, 0, lem::int_min, 0, lem::int_min )
{
 token_flags = 5;
}

