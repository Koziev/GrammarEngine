// -----------------------------------------------------------------------------
// File Multiwordmerger.cpp
//
// (c) Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project
// -----------------------------------------------------------------------------
//
// CD->15.05.2011
// LC->15.05.2011
// --------------

#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/MultiwordMerger.h>

using namespace Solarix;

MultiwordMerger::MultiwordMerger( Solarix::LexicalAutomat *_la )
 : la(_la)
{
 n_max_expecting = 0;
 return;
}



// ****************************************************************************************
// ѕринудительно проталкиваем слова из входной очереди в выходную, объедин€ем что сможем,
// что не удастьс€ - передаем как одиночные слова.
// ****************************************************************************************
void MultiwordMerger::ForceReady(void)
{
 while( !words.empty() )
  {
   const lem::UCString &w0 = words.front();
 
   MultiLexemInfo info;
   if( la->GetDict().GetSynGram().GetEntries().IsMultilexemHead( w0, info ) )
    {
     int ml = info.maxlen; // с этого слова может начинатьс€ мультилексема такой длиной.

     int max_len=0;
     for( int len=std::min(CastSizeToInt(words.size()),ml); len>1; --len )
      {
       Solarix::Lexem lex;
       for( int i=0; i<len; ++i )
        lex.Add( words[i] );

       if( la->GetDict().GetSynGram().GetEntries().IsMultilexemForm(lex) )
        {
         max_len=len;
         ready_words.push_back(lex);
       
         for( int k=0; k<max_len; ++k )
          words.Remove(0);

         break;
        }
      }

     if( max_len==0 )
      {
       // ≈сли построить мультилексему не удалось, передаем одиночное первое слово в
       // выходную очередь и начнем обработку следующего слова.
       ready_words.push_back( words.front() );
       words.Remove(0);
      }
    }
   else
    {
     // слово не €вл€етс€ началом мультилексемы, проталкиваем его в одиночку.
     ready_words.push_back(w0);
     words.Remove(0);
    }
  }

 // ¬ходна€ очередь должна быть пуста. 
 LEM_CHECKIT_Z( words.empty() ); 

 return;
}

// ******************************************
// ¬талкиваем слово во входной накопитель.
// ******************************************
void MultiwordMerger::Push( const lem::UCString &word )
{
 if( words.empty() )
  {
   // — этой лексемы начинаетс€ хоть одна мультилексема?
   MultiLexemInfo info;
   if( la->GetDict().GetSynGram().GetEntries().IsMultilexemHead( word, info ) )
    {
     words.push_back(word);
     n_max_expecting = info.maxlen;
    }
   else
    {
     // нет, это слово употребл€етс€ только отдельно.
     ready_words.push_back(word);
     n_max_expecting=0;
    }
  }
 else
  {
   words.push_back(word);

   if( CastSizeToInt(words.size())>=n_max_expecting )
    {
     Purge();
    }
  }

 return;
}



void MultiwordMerger::Purge(void)
{
 // накоплен максимально длинный набор лексем, из которых с первым словом
 // можно составить мультилексему.

 // »щем самую длинную из возможных.
 int max_len=0;
 for( int len=CastSizeToInt(words.size()); len>1; --len )
  {
   Solarix::Lexem lex;
   for( int i=0; i<len; ++i )
    lex.Add( words[i] );

   if( la->GetDict().GetSynGram().GetEntries().IsMultilexemForm(lex) )
    {
     max_len=len;
     ready_words.push_back(lex);
     
     for( int k=0; k<max_len; ++k )
      words.Remove(0);

     break;
    }
  }

 if( max_len==0 )
  {
   // Ќайти мультилексему не удалось, поэтому проталкиваем в выходной контейнер единственное первое слово.
   ready_words.push_back( words.front() );
   words.Remove(0);
  }

 n_max_expecting=0;

 // ≈сли во входном буфере остались слова, то проверим дл€ первого из них, не
 // может ли оно образовывать мультилексему.
 while( !words.empty() )
  {
   const lem::UCString &w0 = words.front();
   MultiLexemInfo info;
   if( la->GetDict().GetSynGram().GetEntries().IsMultilexemHead( w0, info ) )
    {
     n_max_expecting = info.maxlen;
     break;
    }
   else
    {
     ready_words.push_back( w0 );
     words.Remove(0);
    }
  }

 return;
}


bool MultiwordMerger::IsReady(void) const
{
 return !ready_words.empty();
}


lem::UCString MultiwordMerger::Pop(void)
{
 lem::UCString w = ready_words.front();
 ready_words.Remove(0);
 return w;
}
