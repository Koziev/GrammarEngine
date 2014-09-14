#if !defined ConnectorApplication__H && defined SOL_CAA
#define ConnectorApplication__H

#include <set>
#include <lem/noncopyable.h>
#include <lem/containers.h>
#include <lem/solarix/PatternLinkEdge.h>

namespace Solarix
{
 class LexerTextPos;
 class SynConnectorContext;
 class SynConnector;
 class PreparedLexer;
 class Dictionary;
 class BasicLexer;
 class TrTrace;
 struct SynPatternResult;

 class ConnectorApplication : lem::NonCopyable
 {
  private:
   lem::uint32_t hash; // для ускорения сравнения

   const ConnectorApplication * previous; // из какой цепочки токенов была порождена данная
   const SynConnectorContext * org_context; // исходная цепочка токенов
   const SynConnector * applied_rule; // какое правило породило
   const SynPatternResult * result; // результаты применения правила

   lem::MCollect<const LexerTextPos*> current_roots;

   int score; // накопленные к этому моменту баллы.
   LINKAGE_EDGES linkage_edges; // накопленные к этому моменту связывания

   void StoreResult( SynPatternResult * dst ) const;

   PreparedLexer * lexer;


  public:
   bool used_in_matching; // если контекст участвовал хотя бы в одном сопоставлении с правилом.
   bool used_as_parent; // если из этого контекста было хоть одно порождение нового контекста.

  public:
   ConnectorApplication(
                        const SynConnectorContext * _org_context,
                        Dictionary & dict,
                        const BasicLexer & lexer0,
                        TrTrace * trace
                       );

   ConnectorApplication(
                        const ConnectorApplication * _previous,
                        const SynConnector * _applied_rule,
                        const SynPatternResult * _result,
                        Dictionary & dict,
                        const BasicLexer & lexer0,
                        TrTrace * trace
                       );

   ~ConnectorApplication();

   const lem::MCollect<const LexerTextPos*>& GetRoots() const;

   int Count() const { return CastSizeToInt(GetRoots().size()); }
   const LexerTextPos * GetRoot( int index ) const { return GetRoots()[index]; }

   int GetScore() const { return score; }

   bool operator==( const ConnectorApplication & x ) const;
   bool operator!=( const ConnectorApplication & x ) const;

   SynPatternResult* GetResult() const;

   void PrintRoots( SynGram & sg, lem::OFormatter & out, bool detailed=true ) const;
   void Print_HorizontalLayout( lem::OFormatter & to, Dictionary & dict, bool detailed=false ) const;

   PreparedLexer & GetLexer() { return *lexer; }
 };

 extern bool Find(
                  const ConnectorApplication * needle,
                  const lem::MCollect<const ConnectorApplication*> & hay
                 );

 extern bool Find(
                  const ConnectorApplication * needle,
                  const lem::MCollect<ConnectorApplication*> & hay
                 );

 extern void PrintContexts_HorizontalLayout( const lem::MCollect<const ConnectorApplication *> & contexts, lem::OFormatter & to, Dictionary & dict );  

}

#endif
