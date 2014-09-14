#if !defined ConnectionState__H && defined SOL_CAA
#define ConnectionState__H

#include <lem/noncopyable.h>
#include <lem/containers.h>

namespace Solarix
{
 class Connectors4Language;
 struct SynPatternResult;
 class BasicLexer;
 class PM_Automat;
 class SynGram;
 class LA_SynPatternTrees;
 class WordEntrySet;
 class TrWideContext;
 class TrTrace;
 class SynConnectorContext;
 class ConnectorApplication;

 class ConnectionState : lem::NonCopyable
 {
  private:
   SynPatternResult *empty_result;
   lem::MCollect<SynConnectorContext*> contexts;

   // ќбщее хранилище созданных контекстов - удалим их все по окончании жизни объекта.
   lem::MCollect<ConnectorApplication*> used_context;
   
   // “екущий список контекстов с примененными переписывани€ми.
   lem::MCollect<ConnectorApplication*> current_context;

   // ƒошедшие до конца контексты, уже не участвующие в итераци€х
   lem::MCollect<const ConnectorApplication*> final_context;

   lem::MCollect<SynPatternResult*> results; // промежуточные результаты применени€ правил; уни будут удалены уже после завершени€ итераций.

   void ApplyRules(
                   lem::MCollect<ConnectorApplication*> & current_contexts,
                   lem::MCollect<ConnectorApplication*> & new_contexts,
                   const Connectors4Language & rules,
                   PM_Automat &pm,
                   SynGram &sg,
                   LA_SynPatternTrees &named_filters,
                   WordEntrySet &wordentry_sets,
                   TrWideContext &env,
                   TrTrace *trace_log
                  );

  public:
   ConnectionState( const lem::MCollect<SynPatternResult*> & results, BasicLexer &lexer, Dictionary & dict, TrTrace * trace );
   ~ConnectionState();

   void ApplyRules(
                   const Connectors4Language & rules,
                   PM_Automat &pm,
                   SynGram &sg,
                   LA_SynPatternTrees &named_filters,
                   WordEntrySet &wordentry_sets,
                   TrWideContext &env,
                   TrTrace *trace_log
                  );
  
   bool HasFreshContext() const { return !current_context.empty(); }

   bool AddFinalContext( const ConnectorApplication * created );
   void ToDelete( ConnectorApplication * ctx ) { used_context.push_back(ctx); }

   void Add( SynPatternResult * r ) { results.push_back(r); }

   void GetResults( lem::MCollect<SynPatternResult*> & new_results );

   void PrintFinalContexts( lem::OFormatter & out, Dictionary & dict ) const;
 };
}

#endif
