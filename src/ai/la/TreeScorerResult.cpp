#include <lem/macro_parser.h>
#include <lem/string_parser.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/TreeScorers.h>
#include <lem/solarix/KnowledgeBase.h>
#include <lem/solarix/TreeScorerApplicationContext.h>
#include <lem/solarix/TreeScorer.h>

using namespace Solarix;

TreeScorerResult::TreeScorerResult() : type(UNKNOWN), score(0), id_fact(UNKNOWN)
{
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
void TreeScorerResult::LoadTxt( Dictionary & dict, lem::Iridium::Macro_Parser & txtfile, const TreeScorerMarkers & markers )
{
 // ќценка может быть отрицательной.
 if( txtfile.probe( B_SUB ) )
  {
   type=0;
   score = -txtfile.read_int();
  }
 else
  {
   if( lem::is_int( txtfile.pick().string() ) )
    {
     type=0;
     score = txtfile.read_int();
    }
   else
    {
     const lem::Iridium::BethToken & t = txtfile.read();
     id_fact = dict.GetLexAuto().GetKnowledgeBase().FindFacts( t.string() );
     if( id_fact==UNKNOWN )
      {
       // todo - тут могут быть другие варианты вызываемых вычислений.
       lem::Iridium::Print_Error(t,txtfile);
       dict.GetIO().merr().printf( "Unknown scoring expression starts with %us\n", t.string().c_str() );
       throw lem::E_BaseException();
      }

     txtfile.read_it( B_OROUNDPAREN );
     while( !txtfile.eof() )
     {
      if( txtfile.probe( B_CROUNDPAREN ) )
       break;

      if( !args.empty() )
       txtfile.read_it( B_COMMA );

      const lem::Iridium::BethToken & var = txtfile.read();
      lem::UCString upper_var = lem::to_upper(var.string());
      if( !markers.IsAlreadyBound(upper_var) )
       {
        lem::Iridium::Print_Error(var,txtfile);
        dict.GetIO().merr().printf( "variable %us not bound\n", var.string().c_str() );
        throw lem::E_BaseException();
       }

      args.push_back( upper_var );
     }

     type=1;
    }
  }

 return;
}
#endif


lem::UFString TreeScorerResult::SerializeExpression() const
{
 lem::MemFormatter mem;

 if( type==0 )
  {
   return UFString(lem::to_ustr(score).c_str());
  }
 else if( type==1 )
  {
   mem.printf( "%d(", id_fact );

   for( lem::Container::size_type i=0; i<args.size(); ++i )
    {
     if( i>0 )
      mem.printf( "," );

     mem.printf( "%us", args[i].c_str() );
    }

   mem.printf( ")" );
  }
 else
  {
   LEM_STOPIT;
  }

 return mem.string();
}

void TreeScorerResult::DeserializeExpression( int expr_type, const lem::UFString & serialized )
{
 type=expr_type;

 if( type==0 )
  {
   score = lem::to_int( serialized);
  }
 else if( type==1 )
  {
   lem::StrParser<lem::UFString> txt(serialized);

   id_fact = lem::to_int( txt.read() );
   txt.read_it( L"(" );
   while( !txt.eof() )
   {
    if( txt.probe( L")" ) )
     break;

    if( !args.empty() )
     txt.read_it(L",");

    args.push_back( lem::UCString(txt.read().c_str()) );
   }
  }
 else
  {
   LEM_STOPIT;
  }

 return;
}


#if defined SOL_CAA
int TreeScorerResult::Calculate( Dictionary & dict, const TreeScorerBoundVariables & bound_variables ) const
{
 if( type==0 )
  return score;
 else
  {
   lem::MCollect<const Solarix::Word_Form*> vars;
   for( lem::Container::size_type i=0; i<args.size(); ++i )
   {
    const Solarix::Word_Form * wf = bound_variables.GetVariable( args[i] );
    if( wf==NULL )
     {
      lem::MemFormatter mem;
      mem.printf( "tree_scorer: can not find bound variable %us", args[i].c_str() );
      throw lem::E_BaseException( mem.string() );
     }

    vars.push_back(wf);
   }

   KB_CheckingResult res = dict.GetLexAuto().GetKnowledgeBase().Prove( id_fact, vars );
   if( res.IsMatched() )
    return res.GetInt();
   else
    return 0;
  }
}
#endif

