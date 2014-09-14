// -----------------------------------------------------------------------------
// File AA_AUTOM.CPP
//
// (c) by Elijah Koziev
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// SOLARIX Grammar engine
// Реализация класса AlephAutomat - грамматическая машина.
//
// 26.07.2006 - переделано формирование CPP файла с правилами, теперь
//              создается много файлов небольшого размера, чтобы не убивать
//              компилятор Borland C++ Builder
//
// 26.05.2007 - переделано формирование C++ кода правил для переноса
//              синтаксического анализатора во внешний файл DLL.
//
// 13.06.2009 - добавлены правила трансформации текста
// -----------------------------------------------------------------------------
//
// CD->25.02.1997
// LC->02.02.2013
// --------------

#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/version.h>
#include <lem/solarix/compile_options.h>
#include <lem/solarix/CriteriaInStorage.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/BasicLexer.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/TreeMatchingExperience.h>
#include <lem/solarix/aa_autom.h>


using namespace lem;
using namespace Solarix;

AlephAutomat::AlephAutomat():PM_Automat(SOL_AA_INDEX)
{
 do_delete_storage = false;
 storage = NULL;
 param = new CriteriaInStorage();
 return;
}

AlephAutomat::~AlephAutomat(void)
{
 if( do_delete_storage )
  lem_rub_off(storage);

 return;
}


SynGram& AlephAutomat::GetSynGram(void) const
{ return dict->GetSynGram(); }


#if defined SOL_LOADTXT && defined SOL_COMPILER
bool AlephAutomat::ProcessLexem(
                                const BethToken &t,
                                Macro_Parser &txtfile,
                                const Binarization_Options &options
                               )
{
 return PM_Automat::ProcessLexem( t, txtfile, options );
}

#endif


void AlephAutomat::SetStorage( LexiconStorage *stg, bool _do_delete )
{
 if( do_delete_storage )
  delete storage;

 storage = stg;
 do_delete_storage = _do_delete;

 PM_Automat::SetStorage( L"aa", stg );
 static_cast<CriteriaInStorage*>(param)->Connect( (CriteriaStorage*)stg );
 return;
}

#if defined SOL_REPORT
void AlephAutomat::SaveRules_SQL( OFormatter &out, OFormatter &alters, const SQL_Production &sql_version )
{
 if( sql_version.norules )
  return;

 PM_Automat::SaveRules_SQL( "aa", out, alters, sql_version );
 return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
void AlephAutomat::Prepare( const lem::Path &outdir, const Binarization_Options &opts )
{
 // Длительная операция: сообщаем пользователю.
 GetIO().mecho().printf( "%vfEAA%vn: preparing..." );
 GetIO().mecho().flush();

 PM_Automat::Prepare(outdir,opts);

 GetIO().mecho().printf( "%vfAOK%vn\n" );
 GetIO().mecho().flush();

 return;
}
#endif


#if defined SOL_CAA
const lem::UCString & AlephAutomat::GetSyntacticAnalyzerName( int id_language )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs_language2syntan);
 #endif

 std::map< int /*id_language*/, lem::UCString >::const_iterator it = language2syntan.find(id_language);
 if( it==language2syntan.end() )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif

   it = language2syntan.find(id_language);
   if( it==language2syntan.end() )
    {
     lem::UCString name;

     const SG_Language & lang = GetDict().GetSynGram().languages()[id_language];
     const int iparam = lang.FindParam(L"SyntacticAnalyzer");
    
     if( iparam!=UNKNOWN )
      {
       name = lang.GetParam(iparam).GetValue().c_str();
       name.strip_quotes();
      }

     language2syntan.insert( std::make_pair( id_language, name ) );
     return language2syntan.find(id_language)->second;
    }
   else
    {
     return it->second;
    }
  }
 else
  {
   return it->second;
  }
}
#endif



#if defined SOL_CAA
Res_Pack* AlephAutomat::Analyze(
                                BasicLexer & lexer,
                                TrWideContext & env,
                                const ElapsedTimeConstraint & constraints,
                                TrTrace * trace
                               )
{
 // Для каждого языка может быть задана отдельная процедура синтана. Ее имя указано в параметрах языка.
 const int language_id = lexer.GetParams().GetLanguageID(); 
 const lem::UCString & proc_name = GetSyntacticAnalyzerName( language_id );

 if( proc_name.empty() )
  {
   lem::MemFormatter mem;
   const SG_Language & lang = GetDict().GetSynGram().languages()[language_id];
   mem.printf( "There is no procedure for language %us (id=%d) to perform syntactic analysis", lang.GetName().c_str(), language_id );
  }


 Res_Pack * res = new Res_Pack();

 const LexerTextPos * begin = lexer.GetBeginToken();
 
 lem::MCollect<const LexerTextPos*> leafs;
 lexer.FetchEnds( begin, leafs, lexer.GetParams().GetMaxRightLeaves() );

 lem::MCollect<const LexerTextPos*> nodes;
 lem::MCollect<const LexerTextPos*> nodes2;

 lem::ElapsedTime timer;
 timer.start();

 for( lem::Container::size_type i=0; i<leafs.size(); ++i )
  {
   LINKAGE_EDGES * edges = NULL;

   const LexerTextPos * leaf = leafs[i];
   nodes.clear();
   leaf->Collect_Right2Left( begin, nodes ); // собираем все словоформы на этом пути

   const int src_token_count=CastSizeToInt(nodes.size()-2); // Сколько исходных токенов, не учитывая пропущенные, вошло в фрагменты в nodes2.

   Variator * var = new Variator();

   // словоформы собраны в обратном порядке, развернем его.
   for( int j=CastSizeToInt(nodes.size())-1; j>=0; --j )
    {
     const LexerTextPos * token = nodes[j];
     Tree_Node * node = new Tree_Node( new Word_Form(*token->GetWordform()), false );
     var->Add( node );
    }
  
   res->Add(var);

   if( lexer.GetParams().timeout.max_elapsed_millisecs>0 )
    {
     const int elapsed_millisec = timer.msec();
     if( elapsed_millisec>=lexer.GetParams().timeout.max_elapsed_millisecs )
      break;
    }

   if( lexer.GetParams().timeout.max_variators>0 )
    {
     if( CastSizeToInt(i) >= lexer.GetParams().timeout.max_variators )
      break;
    }   
  }

 #if LEM_DEBUGGING==1
 //res->Print( *lem::mout, GetDict().GetSynGram(), true );
 #endif

 return res;
}
#endif
