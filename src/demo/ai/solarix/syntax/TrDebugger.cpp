#if defined SOL_DEBUGGING

// CD->28.07.2009
// LC->05.09.2014

#include <lem/keyboard.h>
#include <lem/solarix/variator.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/TrMorphologyTracer.h>
#include <lem/solarix/LA_CropRule.h>
#include <lem/solarix/LA_RecognitionRule.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/LA_PhoneticRule.h>
#include <lem/solarix/LA_PreprocessorTokRule.h>
#include <lem/solarix/SourceFilenameEnumerator.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/SynPattern.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/LexerTextPos.h>
#include "syntax.h"

using namespace lem;
using namespace Solarix;

TrDebugger::TrDebugger( Solarix::Dictionary *d ) : dict(d)
{
 recognizer_trace = new LA_RecognitionTrace_Console(d);
 preprocessor_trace = new LA_PreprocessorTrace_Console(d);
 return;
}




TrDebugger::~TrDebugger(void)
{
 lem_rub_off(recognizer_trace);
 lem_rub_off(preprocessor_trace);
 return;
}




void TrDebugger::Enter( TrTraceActor *a )
{
 TrTrace::Enter(a);

 if( a->ExecuteBreakpoints() )
  ExecuteBreakpoints(a);

 if( callstack.size()>200 )
  {
   // зацикливание???
   lem::mout->printf( "\nPossible stack overflow, current_depth=%d!\n", CastSizeToInt(callstack.size()) );

   // Выведем меню для управления дальнейшим исполнением.
   while(true)
    {
     mout->printf( "%vf6Commands:%vn %vfER%vnun %vfES%vntop %vfEC%vnall_stack\n" );

     mout->printf( "\nEnter: " );

     int cmd = mkey->getch();
     mout->eol();

     if( cmd=='r' )
      break;

     if( cmd=='c' )
      {
       PrintStack(*mout);
       continue;
      }  

     if( cmd=='s' )
      {
       throw E_BaseException();
      }
    }
  }

 callstack.push_back(a);

 return;
}

void TrDebugger::Leave( TrTraceActor *a )
{
 TrTrace::Leave(a);

 if( !callstack.empty() && callstack.back()->Match(a) )
  {
   callstack.Remove( CastSizeToInt(callstack.size())-1 );
  }

 delete a;
}


void TrDebugger::DebugTrace( const lem::UCString &marker, const TrValue &arg )
{
 return;
}




void TrDebugger::RaisedExceptionLocation( const lem::MCollect<int> &src_locations )
{
 if( !src_locations.empty() )
  {
   lem::mout->printf( "\n\nAn exception has been raised in %d location(s):\n", CastSizeToInt(src_locations.size()) );

   for( lem::Container::size_type i=0; i<src_locations.size(); ++i )
    {
     lem::Path fname;
     int line=-1, column=-1;
     if( dict->GetDebugSymbols().GetLocation( src_locations[i], fname, line, column ) )
      {
       lem::mout->printf( "%us:%d,%d\n", fname.GetUnicode().c_str(), line, column );
      }
    }
 
   lem::mout->eol();
  }

 return;
}


void TrDebugger::RaisedExceptionLocation( int src_locations )
{
 lem::Path fname;
 int line=-1, column=-1;
 if( dict->GetDebugSymbols().GetLocation( src_locations, fname, line, column ) )
  {
   lem::mout->printf( "\n\nException has been raised in %us:%d,%d\n\n", fname.GetUnicode().c_str(), line, column );
  }

 return;
}



void TrDebugger::ExecuteBreakpoints( TrTraceActor *a )
{
 for( lem::Container::size_type i=0; i<breakpoints.size(); ++i )
  {
   TrBreakpoint &p = *breakpoints[i];

   if( p.once && p.on_call_stack_depth==UNKNOWN && p.ifile==UNKNOWN )
    {
     // Это точка, создаваемая отладчиком перед запуском процесса, срабатывает
     // на первом же операторе.
     ExecuteBreakpoint( i, a );
     break;
    }

   if( p.step && a->IsStatement() )
    {
     // Точка срабатывает на любой операторной строке - то есть, на шаге процедуры,
     // исполнении шага внутри функции { ... }, начале проверки кондиктора трансформанты.
     ExecuteBreakpoint( i, a );
    }

   if( p.ifile!=UNKNOWN && a->HasLocation() && a->IsStatement() )
    {
     for( lem::Container::size_type k=0; k<a->GetLocations().size(); ++k )
      {
       int file=UNKNOWN, line=UNKNOWN, column=UNKNOWN;
       dict->GetDebugSymbols().GetLocation( a->GetLocations()[k], file, line, column );
 
       if( file==p.ifile && line==p.iline )
        {
         ExecuteBreakpoint( i, a );
         break;
        }
      }
    }
  }

 return;
}


void TrDebugger::ExecuteBreakpoint( int ipoint, TrTraceActor *a )
{
 // Отобразим контекст точки - фрагмент исходного файла, переменные и т.д.
 TrBreakpoint &p = *breakpoints[ipoint];
 p.pass_count++;

 if( p.on_pass_count==UNKNOWN || p.on_pass_count==p.pass_count )
  {
   if( a->HasLocation() )
    {
     lem::Path filename;
     int line=0, column=0;

     bool breakpoint_is_available=false;

     if( dict->GetDebugSymbols().GetLocation( a->GetLocations().front(), filename, line, column ) )
      {
       mout->printf( "\n%vf6pass=%vn%d %vf6file=%vn%us\n", p.pass_count, filename.GetFileName().c_str() );

       // Выведем строку в исходном тексте.
       UTextParser & txt = GetSourceText(filename);
       if( txt.SeekLine(line) )
        {
         mout->printf( "%vf6%78h-%vn\n" );
         mout->printf( "[%vf3%d%vn] ", line );
         txt.PrintLine(*mout); // Распечатываем строку
         mout->printf( "\n%vf6%78h-%vn\n" );
        }

       // В этой строке можно управлять точками прерывания.
       breakpoint_is_available = true;
      }

     // Выведем меню для управления дальнейшим исполнением.
     while(true)
      {
       mout->printf( "%vf6Commands:%vn %vfER%vnun %vfES%vntep %vfEV%vnariables %vfEC%vnall_stack" );

       if( breakpoint_is_available )
        mout->printf( " %vfET%vnoggle_breakpoint" );

       if( breakpoint_is_available )
        mout->printf( "  %vfEB%vnreakpoints" );

       mout->printf( "\nEnter: " );

       int cmd = mkey->getch();
       mout->eol();

       if( cmd=='r' )
        break;

       if( cmd=='c' )
        {
         PrintStack(*mout);
         continue;
        }  

       if( cmd=='v' )
        {
         a->PrintContext( *dict, *mout );
         continue; 
        }

       if( cmd=='s' )
        {
         // Установим точку останова на ближайшем
         TrBreakpoint *p = new TrBreakpoint;
         p->once = true;
         p->step = true; 
         breakpoints.push_back(p);
         break;
        }

       if( cmd=='b' )
        {
         ManageBreakpoints();
         continue;
        } 
      }
    }
  }

 if( breakpoints[ipoint]->once )
  breakpoints.Remove(ipoint);

 return;
}


void TrDebugger::Print( const UFString &str )
{
 mout->printf( "%vf6Debug output%vn: %vfF%us%vn\n", str.c_str() );
 return;
}







void TrDebugger::BeforePhrase(void)
{
 applied_colloc_filter.clear();

 // Выведем меню: манипуляции с точками останова, режим исполнения.

 while(true)
  {
   mout->printf( "%vf6Debugger commands:%vn %vfER%vnun %vfES%vntep %vfEB%vnreakpoints %vfET%vnriggers\nEnter: " );
   char cmd = mkey->getch();
   mout->eol();

   if( cmd=='r' )
    return;

   if( cmd=='s' )
    {
     // Установим точку останова на первом операторе.
     TrBreakpoint *p = new TrBreakpoint;
     p->once = true;
     p->step = true; 
     breakpoints.push_back(p);
     return;
    }

   if( cmd=='b' )
    {
     ManageBreakpoints();
    }

   if( cmd=='t' )
    {
     ManageTriggers();
    }
  }

 return;
}



void TrDebugger::ManageBreakpoints(void)
{
 try
  {
   while(true)
    {
     mout->printf( "%vf6Breakpoints:%vn %vfEL%vnist all  %vfEC%vnlear all  %vfES%vnet  %vfEE%vnxit\nEnter: " );
     char cmd = mkey->getch();
     mout->eol();

     if( cmd=='e' )
      break;

     if( cmd=='c' )
      {
       breakpoints.clear();
       continue;
      }

     if( cmd=='l' )
      {
       mout->printf( "\n" );
       for( lem::Container::size_type i=0; i<breakpoints.size(); ++i )
        {
         const TrBreakpoint &p = *breakpoints[i];
         if( p.ifile!=UNKNOWN && p.iline!=UNKNOWN )
          {
           const lem::Path &f = dict->GetDebugSymbols().GetFileName( p.ifile );
           mout->printf( "#%vfA%d%vn file=%vfE%us%vn line=%vfE%d%vn\n", i, f.GetFileName().c_str(), p.iline );

           // Отобразим строку
           UTextParser& txt = GetSourceText(f);
           if( txt.SeekLine(p.iline) )
            {
             mout->printf( "%vf6%78h-%vn\n" );
             mout->printf( "[%d] ", p.iline );
             txt.PrintLine(*mout); // Распечатываем строку
             mout->printf( "\n%vf6%78h-%vn\n" );
            }
          }
        }

       continue;
      }

     if( cmd=='s' )
      {
       while(true)
        {
         // Создание новой точки останова - запрашиваем у пользователя файл и строку.
         mout->printf( "Select a source file:\n" );
         lem::Collect<lem::UFString> file_names;
         lem::MCollect<int> file_ids;
         lem::Ptr<SourceFilenameEnumerator> sources( dict->GetDebugSymbols().ListFiles() );
         while( sources->Fetch() )
          {
           file_names.push_back( sources->GetFilename().GetLastLeaf() );
           file_ids.push_back(sources->GetId());
           mout->printf( "%d = %us\n", sources->GetId(), sources->GetFilename().GetLastLeaf().c_str() );
          }

         lem::UFString file_key = mkey->ask_ufstring( "Enter either file ID or file name (extension is optional): " );
         mout->eol();

         int ifile=-1;
         if( lem::is_int(file_key) )
          ifile=lem::to_int(file_key);
         else
          {
           for( lem::Container::size_type i=0; i<file_names.size(); ++i )
            if( file_names[i].eq_begi( file_key ) )
             {
              ifile = file_ids[i];
              break;
             }
          }

         if( ifile==-1 )
          break;

         const lem::Path &fn = dict->GetDebugSymbols().GetFileName(ifile);
         mout->printf( "Selected file: %vfE%us%vn\n", fn.GetUnicode().c_str() );

         int iline = mkey->ask_int( "Enter line number: " );
         mout->eol();
         if( iline==-1 )
          break;

         // Проверим, что такая точка действительно есть в исходниках.
         if( dict->GetDebugSymbols().Find(ifile,iline)==UNKNOWN )
          {
           mout->printf( "Sorry, breakpoint can not be set at this location.\n" );

           const int ibest = dict->GetDebugSymbols().Find(ifile,iline,true);
           if( ibest==UNKNOWN )
            {
             mout->printf( "It seems that file [%us] does not have source code lines.\n", dict->GetDebugSymbols().GetFileName(ifile).GetUnicode().c_str() );
             continue; 
            }

           int column;
           dict->GetDebugSymbols().GetLocation( ibest, ifile, iline, column );

           mout->printf( "Best available location is at line %vfE%d%vn. Set breakpoint?", iline );
           if( !mkey->ask_bool() )
            break;
          } 

         UTextParser& txt = GetSourceText(fn);
         if( txt.SeekLine(iline) )
          {
           mout->printf( "%vf6%78h-%vn\n" );
           mout->printf( "[%d] ", iline );
           txt.PrintLine(*mout); // Распечатываем строку
           mout->printf( "\n%vf6%78h-%vn\n" );
          }

         // Устанавливаем точку в этой позиции. Предварительно удалим имеющуюся точку.
         for( lem::Container::size_type i=0; i<breakpoints.size(); ++i )
          {
           const TrBreakpoint &p = *breakpoints[i];
           if( p.ifile==ifile && p.iline==iline )
            {
             breakpoints.Remove(i);
             break; 
            }
          }

         TrBreakpoint *p = new TrBreakpoint;
         p->ifile = ifile;
         p->iline = iline;
         breakpoints.push_back(p);
         break;
        }
      }
    }
  }
 catch(...)
  {
   merr->printf( "\nError\n" );
  }

 return;
}


void TrDebugger::ManageTriggers(void)
{
 mout->printf( "%vf6Triggers:%vn\n\n"
               "%vfE0%vn - cancel this menu\n"
               "%vfEc%vn - clear all triggers\n"
               "%vfE1%vn - stop before analysis\n"
               "%vfE2%vn - stop after model application\n"
               "%vfE5%vn - right boundary reached\n"
             );

 lem::FString cmd = mkey->ask_fstring();
 mout->eol();

 if( cmd=='0' )
  return;
 else if( cmd=='c' )
  {
   stop_on_right_boundary=false;
   stop_after_model=false;
   stop_before_analysis=false;
  }
 else if( cmd=='1' )
  {
   stop_before_analysis=true;
  }
 else if( cmd=='2' )
  {
   stop_after_model=true;
  }
 else if( cmd=='5' )
  stop_on_right_boundary=true;
 else
  {
   mout->printf( "%vfCInvalid menu choice\n" );
  }

 return;
}





void TrDebugger::AfterPhrase(void)
{
 callstack.clear();

 int n=CastSizeToInt(breakpoints.size())-1;
 for( int i=n; i>=0; --i )
  if( breakpoints[i]->once || breakpoints[i]->on_call_stack_depth!=UNKNOWN )
   breakpoints.Remove(i);

 return;
}


UTextParser& TrDebugger::GetSourceText( const lem::Path &filename )
{
 int i = source_filename.find(filename);
 if( i==UNKNOWN )
  {
   UTextParser *txtfile = new UTextParser();
   lem::StreamPtr file_x( new BinaryReader( filename ) );
   lem::Char_Stream::WideStreamPtr reader = lem::Char_Stream::WideStream::GetReader( file_x );
   txtfile->Open( reader );
   source_filename.push_back(filename);
   source_parser.push_back(txtfile);
   return *txtfile;
  }
 else
  {
   return *source_parser[i];
  } 
}

void TrDebugger::PrintStack( lem::OFormatter &out )
{
 for( int i=CastSizeToInt(callstack.size())-1; i>=0; --i )
  {
   TrTraceActor *a = callstack[i]; 

   if( a->IsStatement() )
    {
     if( a->HasLocation() )
      {
       lem::Path filename;
       int line=0, column=0;

       if( dict->GetDebugSymbols().GetLocation( a->GetLocations().front(), filename, line, column ) )
        {
         mout->printf( "%vf6file=%vn%us\n", filename.GetFileName().c_str() );

         // Выведем строку в исходном тексте.
         UTextParser & txt = GetSourceText(filename);
         if( txt.SeekLine(line) )
          {
           mout->printf( "[%d] ", line );
           txt.PrintLine(*mout); // Распечатываем строку
          }

         mout->printf( "\n%vf6%78h-%vn\n" );
        }
      }
    }
  }

 return;
}






// Через меню показываем различные результаты работы токенизатора, в том числе
// примененные префильтры и детальный граф токенизации.
void TrDebugger::ShowLexerPerformance( BasicLexer & lexer )
{
 while(true)
  {
   mout->printf( "\n%vf6Lexer performance command:%vn\n"
                 "%vfER%vnun\n"
                 "%vfEV%vniew tokenization graph\n" 
               );

   char cmd = mkey->getch();
   mout->eol();

   if( cmd=='r' )
    break;
   else if( cmd=='v' )
    {
     mout->eol();
     PrintTokenizationGraph( lexer, true );
     mout->eol();
    } 
  }

 lem::mout->eol();

 return;
}







void TrDebugger::PrintTokenizationGraph( BasicLexer & lexer, bool detailed )
{
 lem::MCollect<const LexerTextPos*> final_tokens;
 lexer.FetchEnds( lexer.GetBeginToken(), final_tokens, lexer.GetParams().GetMaxRightLeaves() );

 if( final_tokens.size()==1 )
  lem::mout->printf( "There is %vfE1%vn path:\n" );
 else
  lem::mout->printf( "There are %vfE%d%vn paths:\n", CastSizeToInt(final_tokens.size()) );

 for( lem::Container::size_type i=0; i<final_tokens.size(); ++i )
  {
   const LexerTextPos * token = final_tokens[i];

   lem::mout->printf( "PATH #%vf9%d%vn:\n", CastSizeToInt(i) );

   // пройдем по цепочке назад и соберем список токенов в порядке от последнего к первому.
   lem::MCollect<const LexerTextPos*> chain;
   chain.push_back( token );
   const LexerTextPos * cur_token = token;
   while( !cur_token->IsBegin() )
    {
     chain.push_back( cur_token->GetPrev() );
     cur_token = cur_token->GetPrev();
    }

   // теперь напечатаем этот список в обратном порядке.
   if( detailed )
    {
     int word_index=0;
     for( int i=CastSizeToInt(chain.size())-1; i>=0; --i, ++word_index )
      {
       const Word_Form * wordform = chain[i]->GetWordform();
  
       lem::mout->printf( "%d: ", word_index );

       if( chain[i]->IsBegin() || chain[i]->IsEnd() )
        lem::mout->printf( "%vf4%us%vn\n", wordform->GetName()->c_str() );
       else if( wordform->GetEntryKey()==dict->GetLexAuto().GetUnknownEntryKey() )
        lem::mout->printf( "%vfC%us%vn\n", wordform->GetName()->c_str(), wordform->VersionCount() );
       else
        {
         wordform->Print( *lem::mout, &dict->GetSynGram(), true );
         lem::mout->eol();
        }
      }
    }
   else
    {
     for( int i=CastSizeToInt(chain.size())-1; i>=0; --i )
      {
       const Word_Form * wordform = chain[i]->GetWordform();
  
       if( chain[i]->IsBegin() || chain[i]->IsEnd() )
        lem::mout->printf( " %vf6[%vn%vf4%us%vf6]%vn", wordform->GetName()->c_str() );
       else if( wordform->GetEntryKey()==dict->GetLexAuto().GetUnknownEntryKey() )
        lem::mout->printf( " %vf6[%vn%vfC%us%vf6]%vn", wordform->GetName()->c_str(), wordform->VersionCount() );
       else if( wordform->VersionCount()>1 )
        lem::mout->printf( " %vf6[%vn%us/%vfF%d%vf6]%vn", wordform->GetName()->c_str(), wordform->VersionCount() );
       else
        lem::mout->printf( " %vf6[%vn%us%vf6]%vn", wordform->GetName()->c_str() );
      }
    }

   lem::mout->eol();
  }

 return;
}





void TrDebugger::MorphologicalAnalysisStarts( Solarix::BasicLexer & lexer )
{
 if( stop_before_analysis )
  {
   lem::mout->printf( "Analysis started - the tokenization tree is as follows:\n" );
   PrintTokenizationGraph( lexer, true );

   while(true)
    {
     mout->printf(
                  "\nCommands:\n"
                  "%vfER%vnun\n"
                 );

     char cmd = mkey->getch();
     mout->eol();

     if( cmd=='r' )
      break;
    }

   lem::mout->eol();
  }

 return;
}




void TrDebugger::AfterModelApplication( Solarix::BasicLexer & lexer )
{
 if( stop_after_model )
  {
   lem::mout->printf( "\nModel has been applied:\n" );
   PrintTokenizationGraph( lexer, true );
   lem::mout->printf( "\nPress any key to continue..." );
   char cmd = mkey->getch();
   mout->eol();
  }

 return;
}



void TrDebugger::MorphologicalAnalysisFinishes( const Res_Pack & pack )
{
/*
 if( stop_on_morphan_finish )
  {
   while(true)
    {
     mout->printf( "%vf6Morphology:%vn\n"
                   "%vfER%vnun\n"
                   "%vfEV%vniew current variator\n"
                   "%vfET%vnrace matching points\n"
                 );

     char cmd = mkey->getch();
     mout->eol();

     if( cmd=='r' )
      break;
     else if( cmd=='v' )
      {
       mout->eol();
       var.Print( *mout, dict->GetSynGram(), true );
       mout->eol();
      }
     else if( cmd=='t' )
      {
       mout->eol();
       GetMorphologyTracer().PrintMatchingPoints(*mout);
       mout->eol();
      }
    }
  }
*/

 return;
}

void TrDebugger::MorphologyAnalysisCompleted( const Solarix::TextAnalysisSession & fblo )
{
/*
 if( stop_on_morphan_finish )
  {
   const Solarix::Res_Pack &p = fblo.GetPack();
   mout->printf( "\nMorphological analysis has been completed. There are %vfE%d%vn variants:\n", CastSizeToInt(p.vars().size()) );

   for( lem::Container::size_type i=0; i<p.vars().size(); ++i )
    {
     p.vars()[i]->PrintV( *mout, dict->GetSynGram(), true );
     mout->printf( "%70h-\n" );
    }
  }
*/

 return;
}






void TrDebugger::Trace( bool f )
{
 trace = f;
 recognizer_trace->Trace(f);
 preprocessor_trace->Trace(f);
 return;
}






LA_RecognitionTrace* TrDebugger::RecognizerTrace(void)
{
 return recognizer_trace;
}

LA_PreprocessorTrace* TrDebugger::PreprocessorTrace(void)
{
 return preprocessor_trace;
}




LA_RecognitionTrace_Console::LA_RecognitionTrace_Console( Solarix::Dictionary *d )
{
 dict = d;
}

void LA_RecognitionTrace_Console::CropRuleApplied(
                                                  const lem::UCString &word_before,
                                                  const lem::UCString &word_after,
                                                  const LA_CropRule *rule
                                                 )
{
 if( trace )
  mout->printf( "Crop rule %vfA%us%vn has been applied: %vfE%us%vn -> %vfE%us%vn\n", rule->GetName().c_str(), word_before.c_str(), word_after.c_str() );

 return;
}

void LA_RecognitionTrace_Console::Matched( const lem::UCString &word, const LA_RecognitionRule *rule )
{
 if( trace )
  {
   mout->printf( "Recognition rule %vfA%us%vn has been applied for %vfE%us%vn rel=%vf9%4.2rf%vn", rule->GetName().c_str(), word.c_str(), rule->GetRel().GetFloat() );

   const Solarix::SG_Entry &e = dict->GetSynGram().GetEntry( rule->GetEntryKey() );
   const int id_class = e.GetClass();
   mout->printf( " %us:%us ", dict->GetSynGram().GetClass(id_class).GetName().c_str(), e.GetName().c_str() );
   rule->GetCoords().SaveTxt( *mout, dict->GetSynGram() );
   mout->printf( "\n" );
  }

 return;
}

void LA_RecognitionTrace_Console::MatchedSyllable( const lem::UCString &word, const lem::UCString &syllable, const LA_RecognitionRule *rule )
{
 if( trace )
  {
   mout->printf( "Recognition rule %vfA%us%vn has been applied for syllable %vfE%us%vn in word %vfE%us%vn rel=%vf9%4.2rf%vn"
    , rule->GetName().c_str(), syllable.c_str(), word.c_str(), rule->GetRel().GetFloat() );

   const Solarix::SG_Entry &e = dict->GetSynGram().GetEntry( rule->GetEntryKey() );
   const int id_class = e.GetClass();
   mout->printf( " %us:%us ", dict->GetSynGram().GetClass(id_class).GetName().c_str(), e.GetName().c_str() );
   rule->GetCoords().SaveTxt( *mout, dict->GetSynGram() );
   mout->printf( "\n" );
  }

 return;
}

void LA_RecognitionTrace_Console::PhoneticRuleProduction( const lem::UCString &source, const lem::UCString &result, lem::Real1 val, const LA_PhoneticRule *rule )
{
 if( trace )
  {
   mout->printf( "Phonetic rule %vfA%us%vn has been applied: %vfE%us%vn -> %vfE%us%vn  rel=%vf9%4.2rf%vn\n",
    rule->GetName().c_str(), source.c_str(), result.c_str(), val.GetFloat() );
  }

 return;
}


void LA_RecognitionTrace_Console::WordSyllabs( const lem::UCString &word, const lem::MCollect<lem::UCString> &slb_list )
{
 if( trace )
  {
   mout->printf( "Word %vfE%us%vn has been split to syllables:", word.c_str() );

   for( lem::Container::size_type i=0; i<slb_list.size(); i++ )
    lem::mout->printf( " %us", slb_list[i].c_str() );

   mout->eol();
  }

 return;
}







LA_PreprocessorTrace_Console::LA_PreprocessorTrace_Console( Solarix::Dictionary *d )
{
 dict = d;
}



void LA_PreprocessorTrace_Console::LanguageGuessed( const lem::UFString &phrase, int LanguageID )
{
 if( trace )
  {
   lem::mout->printf( "Language guesser: phrase=%us id_language=%d", phrase.c_str(), LanguageID );
   if( LanguageID!=UNKNOWN )
    {
     const SG_Language &lang = dict->GetSynGram().languages()[LanguageID];
     lem::mout->printf( " language=%us\n", lang.GetName().c_str() );
    }
   else
    {
     lem::mout->eol();
    }
  }

 return;
}



void TrDebugger::BreakOnRightBoundary( const lem::MCollect<SynPatternResult*> & results )
{
 if( stop_on_right_boundary )
  {
   while(true)
    {
     mout->printf(
                  "Select viewer command:\n"
                  "\n%vfER%vnun\n"
                  "%vfE1%vn show the best matching\n"
                  "%vfES%vnorted by scores\n"
                  "%vfEP%vnatterns\n"
                 );

     char cmd = mkey->getch();
     mout->eol();

     if( cmd=='r' )
      break;
     else if( cmd=='p' )
      {
       ShowSynPatternResults(results,false,4);
       lem::mout->eol();
      }
     else if( cmd=='s' )
      {
       ShowSynPatternResults(results,true,4);
       lem::mout->eol();
      }
     else if( cmd=='1' )
      {
       ShowSynPatternResults(results,true,1);
       lem::mout->eol();
      }
    }
  }

 return;
}


namespace {
static bool result_score_sorter( const SynPatternResult * x, const SynPatternResult * y )
{
 return x->res.GetNGramFreq().Composite() > y->res.GetNGramFreq().Composite();
}
}



void TrDebugger::ShowSynPatternResults( const lem::MCollect<SynPatternResult*> & results, bool sort_by_scores, int items_to_show )
{
 lem::mout->printf( "%20h= %d RIGHT BOUNDARY RESULTS %20h=\n", results.size() );

 lem::MCollect<SynPatternResult*> tmp_results = results;
 if( sort_by_scores )
  std::sort( tmp_results.begin(), tmp_results.end(), result_score_sorter );

 const int page_size=items_to_show;
 for( lem::Container::size_type k=0; k<tmp_results.size(); ++k )
  {
   if( k>0 && (k%page_size)==0 )
    {
     lem::mout->printf( "\nPress space to see the records #%d...%d, ESC to cancel: ", k, k+page_size-1 );
     int c = lem::mkey->getch();
     if( c==27 )
      {
       break;
      }

     lem::mout->eol();
    }

   const SynPatternResult & result_q = * tmp_results[k];

   lem::mout->printf( "Result #%vfE%d%vn   ngrams=(%vfA%d%vn,%vfC%d%vn):\n", k, result_q.res.GetNGramFreq().positive, result_q.res.GetNGramFreq().negative );

   // Трассировка по исходному тексту.

   lem::mout->printf( "Source code trace:\n" );

   for( lem::Container::size_type i=0; i<result_q.debug_trace.size(); ++i )
    {
     lem::mout->printf( "step %vfE%d%vn -->", CastSizeToInt(i)+1 );

     const SynPatternDebugTrace & dbg = result_q.debug_trace[i];
     const SynPatternPoint * point = dbg.point;

     if( point!=NULL )
      {
       lem::mout->printf( " source=" );

       for( lem::Container::size_type j=0; j<point->GetSources().size(); ++j )
        {
         const int src = point->GetSources()[j];
         lem::Path filename;
         int line=0, column=0;
    
         if( dict->GetDebugSymbols().GetLocation( src, filename, line, column ) )
          {
           lem::mout->printf( "%vfA%us%vn:%vfE%d%vn ", filename.GetFileName().c_str(), line );
          }
        }
      }

     const Word_Form * wordform = dbg.wordform;

     if( wordform!=NULL )
      {
       if( result_q.debug_trace[i].wordform_matching )
        {
         lem::mout->printf( "wordform=" );
         Solarix::Word_Form wf( *wordform, false );
         wf.Print( *lem::mout, & dict->GetSynGram(), true );
        }
       else
        {
         lem::mout->printf( "word=%vfE%us%vn", wordform->GetName()->c_str() );
        }
      }

     if( dbg.pattern_name!=NULL )
      {
       lem::mout->printf( " %vfD%us%vn", result_q.debug_trace[i].pattern_name->c_str() );
      }

     if( dbg.id_src_tree_scorer!=UNKNOWN )
      {
       lem::mout->printf( " source=" );
       const int src = dbg.id_src_tree_scorer;
       lem::Path filename;
       int line=0, column=0;
    
       if( dict->GetDebugSymbols().GetLocation( src, filename, line, column ) )
        {
         lem::mout->printf( "%vfA%us%vn:%vfE%d%vn", filename.GetFileName().c_str(), line );
        }

       lem::mout->printf( " %vfCtree scorer%vn" );
      }

     if( !dbg.ngram_freq.IsZero() )
      {
       lem::mout->printf( " score={%d,%d}", dbg.ngram_freq.positive, dbg.ngram_freq.negative );
       if( dbg.scoring_reason!=NULL )
        lem::mout->printf( " %s", dbg.scoring_reason );
      }

     lem::mout->eol();
    }

   const LINKAGE_GROUPS & groups = result_q.linkage_groups;
   const LINKAGE_EDGES & edges = result_q.linkage_edges;

/*
     if( !groups.empty() )
      {
       lem::mout->printf( "\nThere are %d linkage groups: ", CastSizeToInt(groups.size()) );
       for( int k=0; k<groups.size(); ++k )
        lem::mout->printf( " (%d,%d root=%us)", groups[k].index_begin, groups[k].index_end, groups[k].root_node->GetName()->c_str() );
       lem::mout->eol();
      }
*/

   if( !edges.empty() )
    {
     lem::mout->printf( "\nThere are %d edges:\n", CastSizeToInt(edges.size()) );
     for( lem::Container::size_type k=0; k<edges.size(); ++k )
      {
       const PatternLinkEdge & edge = edges[k];

       Solarix::Word_Form wf0( *edge.from, false );
       Solarix::Word_Form wf1( *edge.to, false );

       lem::UCString link_name;
       if( edge.link_type==UNKNOWN )
        link_name = L"((unknown))";
       else
        link_name = dict->GetSynGram().coords()[0].GetStateName(edge.link_type);

       wf0.Print( *lem::mout, &dict->GetSynGram(), true );
       lem::mout->printf( " --(%us)--> ", link_name.c_str() );
       wf1.Print( *lem::mout, &dict->GetSynGram(), true );
       lem::mout->eol();
      }
    }

   if( !result_q.scorer_id_src.empty() )
    {
     lem::mout->printf( "Scorers:\n" );

     for( lem::Container::size_type q=0; q<result_q.scorer_id_src.size(); ++q )
      {
       const int src = result_q.scorer_id_src[q];
       lem::Path filename;
       int line=0, column=0;
 
       if( dict->GetDebugSymbols().GetLocation( src, filename, line, column ) )
        {
         lem::mout->printf( "%vfA%us%vn:%vfE%d%vn\n", filename.GetFileName().c_str(), line );
        }
      }
    }

   lem::mout->printf( "%vf2%50h-%vn\n" );
  }

 lem::mout->printf( "%50h=\n\n" );

 return;
}



void TrDebugger::BeforeSynPatternTreeProve(
                                           const SynPatternPoint &point,
                                           const lem::MCollect<int> &id_src,
                                           const BasicLexer & lexer,
                                           const LexerTextPos * current_token,
                                           const BackTrace * parent_trace
                                          )
{
 // посмотрим, есть ли точки останова на этой опорной точке.
 for( lem::Container::size_type i=0; i<breakpoints.size(); ++i )
  {
   TrBreakpoint &p = *breakpoints[i];

   if( p.ifile!=UNKNOWN )
    {
     for( lem::Container::size_type k=0; k<id_src.size(); ++k )
      {
       int file=UNKNOWN, line=UNKNOWN, column=UNKNOWN;
       dict->GetDebugSymbols().GetLocation( id_src[k], file, line, column );
 
       if( file==p.ifile && line==p.iline )
        {
         // Да, покажем положение

         lem::Path filename;
         int line=0, column=0;

         bool breakpoint_is_available=false;

         if( dict->GetDebugSymbols().GetLocation( id_src.front(), filename, line, column ) )
          {
           lem::mout->printf( "\nBEFORE %vf6pass=%vn%d %vf6file=%vn%us", p.pass_count, filename.GetFileName().c_str() );
           lem::mout->printf( " current_token: pos=%d word=%us\n", current_token->GetWordIndex(), current_token->GetWordform()->GetName()->c_str() );

           // Выведем строку в исходном тексте.
           UTextParser & txt = GetSourceText(filename);
           if( txt.SeekLine(line) )
            {
             mout->printf( "%vf6%78h-%vn\n" );
             mout->printf( "[%vf3%d%vn] ", line );
             txt.PrintLine(*mout); // Распечатываем строку
             mout->printf( "\n%vf6%78h-%vn\n" );
            }

           // В этой строке можно управлять точками прерывания.
           breakpoint_is_available = true;
          }

         // Выведем меню для управления дальнейшим исполнением.
         while(true)
          {
           mout->printf( "%vf6Commands:%vn %vfER%vnun %vfEV%vnariables %vfEC%vnall_stack" );
        
           if( breakpoint_is_available )
            mout->printf( " %vfET%vnoggle_breakpoint" );
        
           if( breakpoint_is_available )
            mout->printf( "  %vfEB%vnreakpoints" );
        
           mout->printf( "\nEnter: " );
        
           int cmd = mkey->getch();
           mout->eol();
        
           if( cmd=='r' )
            break;
        
           if( cmd=='c' )
            {
             PrintStack(*mout);
             continue;
            }  
        
           if( cmd=='v' )
            {
             lem::mout->printf( "\n%vf6Trace:%vn\n" );
             parent_trace->Print( *lem::mout, dict->GetSynGram(), true );
             lem::mout->eol();
             continue;
            }
        
           if( cmd=='b' )
            {
             ManageBreakpoints();
             continue;
            } 
          }

         return;
        }
      }
    }
  }
 

 return;
}


void TrDebugger::SynPatternTreeProved(
                                      const SynPatternPoint &point,
                                      const lem::MCollect<int> &id_src,
                                      const BasicLexer & lexer,
                                      const LexerTextPos *current_token,
                                      const lem::PtrCollect<SynPatternResult> & subresults
                                     )
{
 // посмотрим, есть ли точки останова на этой опорной точке.
 for( lem::Container::size_type i=0; i<breakpoints.size(); ++i )
  {
   TrBreakpoint &p = *breakpoints[i];

   if( p.ifile!=UNKNOWN )
    {
     for( lem::Container::size_type k=0; k<id_src.size(); ++k )
      {
       int file=UNKNOWN, line=UNKNOWN, column=UNKNOWN;
       dict->GetDebugSymbols().GetLocation( id_src[k], file, line, column );
 
       if( file==p.ifile && line==p.iline )
        {
         // Да, покажем положение и меню с возможностью вывода результатов вызова именованного дерева.

         lem::Path filename;
         int line=0, column=0;

         bool breakpoint_is_available=false;

         if( dict->GetDebugSymbols().GetLocation( id_src.front(), filename, line, column ) )
          {
           lem::mout->printf( "\nAFTER %vf6pass=%vn%d %vf6file=%vn%us", p.pass_count, filename.GetFileName().c_str() );
           lem::mout->printf( " current_token: pos=%d word=%us\n", current_token->GetWordIndex(), current_token->GetWordform()->GetName()->c_str() );

           // Выведем строку в исходном тексте.
           UTextParser & txt = GetSourceText(filename);
           if( txt.SeekLine(line) )
            {
             mout->printf( "%vf6%78h-%vn\n" );
             mout->printf( "[%vf3%d%vn] ", line );
             txt.PrintLine(*mout); // Распечатываем строку
             mout->printf( "\n%vf6%78h-%vn\n" );
            }

           // В этой строке можно управлять точками прерывания.
           breakpoint_is_available = true;
          }

         lem::mout->printf( "Term matching count=%d\n", CastSizeToInt(subresults.size()) );


         // Выведем меню для управления дальнейшим исполнением.
         while(true)
          {
           mout->printf( "%vf6Commands:%vn %vfER%vnun %vfEV%vnariables %vfEC%vnall_stack" );
        
           if( breakpoint_is_available )
            mout->printf( " %vfET%vnoggle_breakpoint" );
        
           if( breakpoint_is_available )
            mout->printf( "  %vfEB%vnreakpoints" );
        
           mout->printf( "\nEnter: " );
        
           int cmd = mkey->getch();
           mout->eol();
        
           if( cmd=='r' )
            break;
        
           if( cmd=='c' )
            {
             PrintStack(*mout);
             continue;
            }  
        
           if( cmd=='v' )
            {
             lem::mout->printf( "\n%vf6Matchings:%vn\n" );
             point.Print( *lem::mout, dict->GetSynGram() );
             lem::mout->printf( "\n%40h-\n\n" );
             lem::mout->printf( "Results (n=%vfE%d%vn):\n", CastSizeToInt(subresults.size()) );

             for( lem::Container::size_type q=0; q<subresults.size(); ++q )
              {
               lem::mout->printf( "Result #%d ", CastSizeToInt(q) );
               const SynPatternResult * subresult_q = subresults[q];
               subresult_q->Print( *lem::mout, dict->GetSynGram() );
               lem::mout->eol();

               if( !subresult_q->linkage_edges.empty() )
                {
                 lem::mout->eol();
                 subresult_q->PrintLinks( *lem::mout, dict->GetSynGram() );
                 lem::mout->eol();
                }
              }
             
             continue;
            }
        
           if( cmd=='b' )
            {
             ManageBreakpoints();
             continue;
            } 
          }

         return;
        }
      }
    }
  }

 return;
}




void TrDebugger::BeforeMatchingTheWord(
                                       const SynPatternPoint &point,
                                       const lem::MCollect<int> &id_src,
                                       const BasicLexer & lexer,
                                       const LexerTextPos *current_token
                                      )
{
 // посмотрим, есть ли точки остановка на этой опорной точке.
 for( lem::Container::size_type i=0; i<breakpoints.size(); ++i )
  {
   TrBreakpoint &p = *breakpoints[i];

   if( p.ifile!=UNKNOWN )
    {
     for( lem::Container::size_type k=0; k<id_src.size(); ++k )
      {
       int file=UNKNOWN, line=UNKNOWN, column=UNKNOWN;
       dict->GetDebugSymbols().GetLocation( id_src[k], file, line, column );
 
       if( file==p.ifile && line==p.iline )
        {
         lem::Path filename;
         int line=0, column=0;

         bool breakpoint_is_available=false;

         if( dict->GetDebugSymbols().GetLocation( id_src.front(), filename, line, column ) )
          {
           mout->printf( "\n%vf6pass=%vn%d %vf6file=%vn%us\n", p.pass_count, filename.GetFileName().c_str() );

           // Выведем строку в исходном тексте.
           UTextParser & txt = GetSourceText(filename);
           if( txt.SeekLine(line) )
            {
             mout->printf( "%vf6%78h-%vn\n" );
             mout->printf( "[%vf3%d%vn] ", line );
             txt.PrintLine(*mout); // Распечатываем строку
             mout->printf( "\n%vf6%78h-%vn\n" );
            }

           // В этой строке можно управлять точками прерывания.
           breakpoint_is_available = true;
          }

         // Выведем меню для управления дальнейшим исполнением.
         while(true)
          {
           mout->printf( "%vf6Commands:%vn %vfER%vnun %vfET%vnoken %vfEC%vnall_stack" );
        
           if( breakpoint_is_available )
            mout->printf( " %vfET%vnoggle_breakpoint" );
        
           if( breakpoint_is_available )
            mout->printf( "  %vfEB%vnreakpoints" );
        
           mout->printf( "\nEnter: " );
        
           int cmd = mkey->getch();
           mout->eol();
        
           if( cmd=='r' )
            break;
        
           if( cmd=='c' )
            {
             PrintStack(*mout);
             continue;
            }  
        
           if( cmd=='t' )
            {
             lem::mout->printf( "Token start_position=%d word_index=%d score=%d\n", current_token->GetStartPosition(), current_token->GetWordIndex(), current_token->GetScore() );
             current_token->GetWordform()->Print( *lem::mout, &dict->GetSynGram(), true );
             lem::mout->eol();
             continue; 
            }
        
           if( cmd=='b' )
            {
             ManageBreakpoints();
             continue;
            } 
          }

         return;
        }
      }
    }
  }

 return;
}




void TrDebugger::LanguageGuessed( const lem::UFString & str, int id_language )
{
 if( trace )
  {
   lem::mout->printf( "Language guesser: %us --> %d ", str.c_str(), id_language );

   if( id_language!=UNKNOWN )
    {
     const SG_Language & lang = dict->GetSynGram().languages()[id_language];
     lem::mout->printf( "%us", lang.GetName().c_str() );
    }

   lem::mout->eol();
  }

 return;
}


void TrDebugger::ClassifierModelApplied( const Word_Form * focus, const Word_Form * new_token_wordform )
{
 if( trace )
  {
   lem::mout->printf( "\n\nClassifier model has been applied:\n\n" );

   lem::mout->printf( "OLD TOKEN: " );
   focus->Print( *lem::mout, &dict->GetSynGram(), true );
   lem::mout->printf( "\n\n" );
   lem::mout->printf( "NEW TOKEN: " ); 
   new_token_wordform->Print( *lem::mout, &dict->GetSynGram(), true );
   lem::mout->printf( "\n\n" );
  }

 return;
}
#endif
