// -----------------------------------------------------------------------------
// File PM_AUTOM.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// SOLARIX Grammar engine
// -----------------------------------------------------------------------------
//
// CD->25.02.1997
// LC->23.08.2014
// --------------

#include <lem/set.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/CriteriaInFile.h>
#include <lem/solarix/PM_FunctionLoader.h>
#include <lem/solarix/LexiconStorage.h>
//#include <lem/solarix/PM_Rules.h>
//#include <lem/solarix/pm_rules_in_category.h>
//#include <lem/solarix/PM_ProcedureLoader.h>
//#include <lem/solarix/reconstructor_impl2.h>
//#include <lem/solarix/RuleCategoryEnumerator.h>
//#include <lem/solarix/ProcedureEnumerator.h>
//#include <lem/solarix/PatternMatcherEnumerator.h>
//#include <lem/solarix/tr_pattern_matchers.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/pm_autom.h>

using namespace std;
using namespace lem;
using namespace Solarix;

PM_Automat::PM_Automat( int Index ):Automaton(Index)
{
 sql_prefix = NULL;
 param = NULL;
 storage = NULL;
 functions = NULL;
 return;
}


PM_Automat::~PM_Automat(void)
{
 Delete();
 return;
}



void PM_Automat::Delete(void)
{
 lem_rub_off(functions);
 return;
}

void PM_Automat::SetDictPtr( Dictionary *d )
{
 Automaton::SetDictPtr(d);

 functions = new PM_FunctionLoader( d );

 return;
}



SynGram& PM_Automat::GetSynGram(void) const
{ return dict->GetSynGram(); }


#if defined SOL_LOADTXT && defined SOL_COMPILER
/************************************************************************
 Метод вызывается классом Automaton для загрузки специфических для
 Продукционной Машины структур данных. В случае успешного распознавания
 возвращаем true, иначе - false.
*************************************************************************/
bool PM_Automat::ProcessLexem(
                              const BethToken &t,
                              Macro_Parser &txtfile,
                              const Binarization_Options &options
                             )
{
 if( t.GetToken()==B_FUNCTION )
 {
  const TrFunction *fun = functions->Get().CompileDeclaration( *this, txtfile, procedure_declarations );
  return true;
 } 
 else if( t.string().eqi(L"static") )
 {
  // это должно быть объявление глобальной переменной:
  // static тип = значение;
  // Мы скомпилируем его как функцию, инициализирующую переменную в глобальном пространстве.
  functions->Get().CompileStatic( *this, txtfile, procedure_declarations );
  return true;
 }

 return false;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
/*************************************************************************
 Только что загрузили содержимое из текстового файла Словаря. Проделаем
 некоторые подготовительные операции для использования Машины, к примеру
 - сортировки, после чего PM сможет работать в режиме SOL_CAA.
*************************************************************************/
void PM_Automat::Prepare( const lem::Path &outdir, const Binarization_Options &opts )
{
 if( opts.lexicon_merging )
  return;

 const bool echo=true;

 functions->CompilationFinished();
 if(echo)
  {
   GetIO().mecho().printf( " 1 " );
   GetIO().mecho().flush();
  }

 return;
}
#endif






#if defined SOL_REPORT
/***************************************************************
 Краткий отчет о загрузке различных постоянных списков печатаем
 в указанный текстовый поток s.
****************************************************************/
void PM_Automat::Report( OFormatter &s )
{
 Automaton::Report(s);
 return;
}
#endif



#if defined SOL_REPORT
void PM_Automat::PrintMap( OFormatter &s )
{
 Report(s);

/*
 s.printf( "\n\n %10h- RULE GROUPS %10h-\n\n" );

 s.printf( "Total number of groups=%d\n\n", GetProductionRules().CountGroups() );

 const int ngroup = GetProductionRules().CountGroups();
 lem::Ptr<RuleCategoryEnumerator> e_cat = GetProductionRules().ListGroups();
 while( e_cat->Fetch() )
  {
   const int id = e_cat->GetId();
   const PM_RulesInCategory &g = e_cat->GetGroup();

   s.printf(
            "id=%d Category=%us rules=%d\n"
            , id
            , g.GetName().c_str()
            , g.list().size()
           );

   s.printf( "Rules list: " );
   for( Container::size_type j=0; j<g.list().size(); j++ )
    s.printf( "%us ", GetProductionRules().GetRule(g.list()[j])->GetName().c_str() );

   s.eol();

   s.printf( "LENS GROUPS (n=%d):\n", CastSizeToInt(g.len_groups().size()) );

   int n_rules=0;

   for( Container::size_type j2=0; j2<g.len_groups().size(); j2++ )
    {
     const PM_LenRuleGroup &lg = g.len_groups()[j2];

     s.printf(
              "group #%d len=%d items=%d ->"
              , j2
              , lg.Len()
              , lg.size()
             );

     n_rules += CastSizeToInt(lg.size());

     for( Container::size_type k=0; k<lg.size(); k++ )
      {
       s.printf( "%us", GetProductionRules().GetRule( lg[k].id_rule )->GetName().c_str() );

       if( lg[k].i_key_group!=UNKNOWN )
        {
         int ekey = g.key_groups()[ lg[k].i_key_group ].entry_key;

//         int ie = GetDict().GetSynGram().FindEntryByKey(ekey);
         const SG_Entry& e = GetDict().GetSynGram().GetEntry(ekey);

//         if( ie==UNKNOWN )
//          s.printf( ":(??%d) ", ekey );
//         else
          s.printf( ":(%us:%d) ", e.GetName().c_str(), ekey );
        }
       else
        s.printf( " " );
      }

     s.eol();
    }

   s.printf(
            "Total # of rules in all lens groups=%d (must be %d)\n%40h-\n\n"
            , n_rules, g.list().size()
           );
  }
*/

 return;
}
#endif



#if defined SOL_CAA
/************************************************************************
 Поиск правила с указанным ключем. Для ускорения поиска используем
 следующую особенность списка правил: хранимые операторы всегда
 располагаются в порядке возрастания ключей при использовании вектора
 индексации rule_k, а кроме того, весьма вероятно, что возрастание
 значений ключей будет монотонным с шагом 1 между соседями. Таким образом,
 для заданного ключа ikey сначала пробуем обратиться к правилу rule[ikey],
 если это допускается диапазоном. В случае неуспеха начинаем процедуру
 поиска методом дихотомии.
*************************************************************************/
/*
int PM_Automat::FindRuleByKey( int ikey ) const
{
 const int nrule=rule.size();

 if( ikey<nrule )
  if( rule( rule_k(ikey) )->GetKey() == ikey )
   return rule_k(ikey);

 int ileft=0, iright=nrule-1, imiddle;
 int imiddle_key;
 FOREVER
  {
   // ****************************************
   //
   //     x-------?-------x--------?------x
   //   ileft ( ikey)  imiddle (ikey)  iright
   //
   // ****************************************

   imiddle = (iright+ileft)/2;
   imiddle_key=rule( rule_k(imiddle) )->GetKey();

   if( imiddle_key==ikey )
    return imiddle;

   if( imiddle_key>ikey )
    iright=imiddle;
   else
    ileft=imiddle;

   if( (iright-ileft) < 3 )
    {
     for( int i=ileft; i<=iright; i++ )
      if( rule( rule_k(i) )->GetKey() == ikey )
       return i;

     break;
    }
  }

 return UNKNOWN;
}
*/


#endif

  
#if defined SOL_LOADTXT && defined SOL_COMPILER
void PM_Automat::Optimize(void)
{
 Automaton::Optimize();
 return;
}
#endif





#if defined SOL_LOADTXT && defined SOL_COMPILER
void PM_Automat::NeedsChainScenario( const UCString &s )
{
 if( needs_chain_scenarios.find(s)==UNKNOWN )
  needs_chain_scenarios.push_back(s);

 return;
}

void PM_Automat::NeedsReplaceScenario( const UCString &s )
{
 if( needs_replace_scenarios.find(s)==UNKNOWN )
  needs_replace_scenarios.push_back(s);

 return;
}
#endif



#if defined SOL_CAA
bool PM_Automat::CreateSequence( const UCString &name, int start_value ) const
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker locker(const_cast<lem::Process::CriticalSection*>(&cs_sequence));
 #endif

 if( sequence.find(to_lower(name))==sequence.end() )
  {
   std::map<UCString,int> &mutable_sequence = const_cast< std::map<UCString,int>& >(sequence);
   mutable_sequence.insert( std::make_pair(to_lower(name), start_value ) );
   return true;
  }
 else
  {
   return false;
  }
}


int PM_Automat::GetSequenceValue( const UCString &name, int step ) const
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker locker(const_cast<lem::Process::CriticalSection*>(&cs_sequence));
 #endif

 std::map<UCString,int> &mutable_sequence = const_cast< std::map<UCString,int>& >(sequence);

 std::map<UCString,int>::iterator it = mutable_sequence.find( to_lower(name) );
 if( it!=sequence.end() )
  {
   return it->second += step;
  }
 else
  {
   throw E_BaseException( lem::format_str( L"Can not find sequence [%us]", name.c_str() ) );
  }
}
#endif


#if defined SOL_LOADBIN 
void PM_Automat::DictionaryLoaded(void)
{
 Automaton::DictionaryLoaded();
 return;
}
#endif


void PM_Automat::SetStorage( const wchar_t *SqlPrefix, LexiconStorage *stg )
{
 sql_prefix = SqlPrefix;
 storage = stg;
 functions->Connect(storage,sql_prefix);
 return;
}

void PM_Automat::BeforeSyntaxRecompilation(void)
{
 storage->DeleteFunctions(sql_prefix);
 return;
}

/*
const PM_Rule* PM_Automat::GetRule( int id )
{
 return GetProductionRules().GetRule(id);
}
*/


#if defined SOL_REPORT
void PM_Automat::SaveRules_SQL( const char *marker, OFormatter &out, OFormatter &alters, const SQL_Production &sql_version )
{
 TrFunctions & funs = GetFunctions().Get();

 lem::MemStream mem(true);
 funs.SaveBin(mem);
 const int sz = mem.tellp();
 const char* bytes = mem.get_Block();
 lem::FString hex;
 Solarix::Storage_Data2Hex( bytes, sz, hex );

 if( sql_version.type==SQL_Production::SQLite )
  {
   out.printf( "%s\n\n", sql_version.BeginTx().c_str() );
  }
 
 if( sql_version.type==SQL_Production::SQLite )
  {
   int segment_no=0;
   out.printf( "INSERT INTO tr_functions( segment_no, marker, bin ) VALUES ( %d, '%us', '%s' );\n\n", segment_no, sql_prefix, hex.c_str() );
  }
 else
  {
   out.printf( "INSERT INTO tr_functions( marker, bin ) VALUES ( '%us', '%s' );\n\n", sql_prefix, hex.c_str() );
  }

/*
 lem::Ptr<ProcedureEnumerator> procs( procedures->ListProcedures() );
 while( procs->Fetch() )
  {
   const TrProcedure & p = procs->GetProcedure();

   lem::MemStream mem(true);
   p.SaveBin(mem);
   const int sz = mem.tellp();
   const char* bytes = mem.get_Block();
   lem::FString hex;
   Storage_Data2Hex( bytes, sz, hex );
   
   out.printf( "INSERT INTO tr_procedure( id, marker, name, bin, id_src ) VALUES ( %d, '%us', '%us', '%s', %d );\n"
    , procs->GetId(), sql_prefix, lem::to_upper(p.GetName()).c_str(), hex.c_str(), p.GetSourceLocation() );
  }
 procs.Delete();

 lem::Ptr<PatternMatcherEnumerator> matchers( procedures->ListMatchers() );
 while( matchers->Fetch() )
  {
   const int id = matchers->GetId();
   const TrPatternMatcher & m = matchers->GetMatcher();
   const int type = m.GetTypeForStorage();

   lem::MemStream mem(true);
   m.SaveBin(mem);
   const int sz = mem.tellp();
   const char* bytes = mem.get_Block();
   lem::FString hex;
   Storage_Data2Hex( bytes, sz, hex );
   
   if( sql_version.type==SQL_Production::SQLite )
    {
     int id0=-1;
     int segment_no=-1;
     out.printf( "INSERT INTO pattern_matcher( id, id0, segment_no, type, marker, name, bin )"
               " VALUES ( %d, %d, %d, %d, '%us', '%us', '%s' );\n", id, id0, segment_no, type, sql_prefix, lem::to_upper(m.GetName()).c_str(), hex.c_str() );
    }
   else
    {
     out.printf( "INSERT INTO pattern_matcher( id, type, marker, name, bin )"
               " VALUES ( %d, %d, '%us', '%us', '%s' );\n", id, type, sql_prefix, lem::to_upper(m.GetName()).c_str(), hex.c_str() );
    }
  } 
 matchers.Delete();
*/

/*
 lem::Ptr<ProductionRuleEnumerator> rulz( production_rules->ListRules() );
 while( rulz->Fetch() )
  {
   const int id = rulz->GetId();
   const PM_Rule & r = rulz->GetRule();

   lem::MemStream mem(true);
   r.SaveBin(mem);
   const int sz = mem.tellp();
   const char* bytes = mem.get_Block();
   lem::FString hex;
   Storage_Data2Hex( bytes, sz, hex );

   if( sql_version.type==SQL_Production::SQLite )
    {
     int id0=-1;
     int segment_no=0;

     out.printf( "INSERT INTO production_rule( id, id0, segment_no, marker, name, id_language, bin, id_src )"
               " VALUES ( %d, %d, %d, '%us', '%us', %d, '%s', %d );\n"
               , id, id0, segment_no, sql_prefix, to_upper(r.GetName()).c_str(), r.GetLanguage(), hex.c_str(), r.GetSourceLocation() );
    }
   else
    {
     out.printf( "INSERT INTO production_rule( id, marker, name, id_language, bin, id_src )"
               " VALUES ( %d, '%us', '%us', %d, '%s', %d );\n"
               , id, sql_prefix, to_upper(r.GetName()).c_str(), r.GetLanguage(), hex.c_str(), r.GetSourceLocation() );
    }
  }
 rulz.Delete();

 lem::Ptr<RuleCategoryEnumerator> groups( production_rules->ListGroups() );
 while( groups->Fetch() )
  {
   const int id = groups->GetId();
   const PM_RulesInCategory & g = groups-> GetGroup();

   lem::MemStream mem(true);
   g.SaveBin(mem);
   const int sz = mem.tellp();
   const char* bytes = mem.get_Block();
   lem::FString hex;
   Storage_Data2Hex( bytes, sz, hex );

   out.printf( "INSERT INTO rules_in_category( id, marker, name, bin )"
               " VALUES ( %d, '%us', '%us', '%s' );\n", id, sql_prefix, lem::to_upper(g.GetName()).c_str(), hex.c_str() );

  }
 groups.Delete();
*/

 if( sql_version.type==SQL_Production::SQLite )
  {
   out.printf( "\n%s\n", sql_version.CommitTx().c_str() );
  }


 return;
}
#endif
