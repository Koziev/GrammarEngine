#include <lem/macro_parser.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/PredicateTemplate.h>
#include <lem/solarix/KnowledgeBase.h>

using namespace Solarix;

KB_Facts::KB_Facts(void)
 : id(UNKNOWN), id_language(UNKNOWN), n_arg(UNKNOWN), n_ret(UNKNOWN), query_mode(UNKNOWN), check_features(0), ret_type(UNKNOWN),
   violation_handler(NULL), violation_score(0)
{
 #if defined SOL_LOADTXT && defined SOL_COMPILER
 allow_generic=false;
 #endif
}

KB_Facts::~KB_Facts()
{
 delete violation_handler;
}

namespace {
 class PredicateTemplateParams_KB : public PredicateTemplateParams
 {
  private:
   int arity;

   inline int ascii2int( wchar_t c ) const { return c-L'0'; }

  public:
   PredicateTemplateParams_KB( int _arity ) : arity(_arity)
   { LEM_CHECKIT_Z(arity<10); }

   bool IsParam( const lem::UCString & probe ) const
   {
    return probe.length()==2 && probe.front()==L'_' && lem::is_udigit(probe[1]) && ascii2int(probe[1])<=arity;
   }
 };
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void KB_Facts::LoadTxt( Solarix::Dictionary &dict, lem::Iridium::Macro_Parser &txtfile )
{
 name = txtfile.read().string();

 txtfile.read_it( B_LANGUAGE );
 txtfile.read_it( B_EQUAL );

 lem::Iridium::BethToken lang = txtfile.read();
 id_language = dict.GetSynGram().Find_Language(lang.string());
 if( id_language==UNKNOWN )
  {
   lem::Iridium::Print_Error(lang,txtfile);
   dict.GetIO().merr().printf( "Unknown language name %us\n", lang.c_str() );
   throw lem::E_BaseException();
  }

 txtfile.read_it( B_OFIGPAREN );

 n_ret=0;

 while( !txtfile.eof() )
  {
   if( txtfile.probe( B_CFIGPAREN ) )
    break;

   lem::Iridium::BethToken t = txtfile.read();
   if( t.string().eqi( L"arity" ) )
    {
     txtfile.read_it(B_EQUAL);
     n_arg = txtfile.read_int();
    }
   else if( t.string().eqi( L"return" ) )
    {
     txtfile.read_it(B_EQUAL);

     lem::Iridium::BethToken t_ret = txtfile.read();
     if( t_ret.eqi( L"boolean" ) )
      {
       n_ret=1;
       ret_type=0;
      }
     else if( t_ret.eqi( L"integer" ) )
      {
       n_ret=1;
       ret_type=1;
      }
     else
      {
       lem::Iridium::Print_Error(t_ret,txtfile);
       dict.GetIO().merr().printf( "Unknown return type %us\n", t_ret.c_str() );
       throw lem::E_BaseException();
      }
    }
   else if( t.string().eqi( L"violation_score" ) )
    {
     txtfile.read_it( B_EQUAL );

     if( txtfile.probe(B_SUB) )
      violation_score = -txtfile.read_int();
     else
      violation_score = txtfile.read_int();
    }
   else if( t.string().eqi( L"violation_handler" ) )
    {
     txtfile.read_it( B_EQUAL );

     violation_handler = new PredicateTemplate();
     PredicateTemplateParams_KB params(n_arg);
     violation_handler->LoadTxt( dict, txtfile, params );
    }
   else if( t.string().eqi( L"generic" ) )
    {
     allow_generic=true;
    }
   else
    {
     lem::Iridium::Print_Error(t,txtfile);
     dict.GetIO().merr().printf( "Unknown property %us\n", t.c_str() );
     throw lem::E_BaseException();
    }
  }

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void KB_Facts::UpdateQueryMode( const KB_Fact & x )
{
 if( query_mode==UNKNOWN )
  {
   if( x.CountArgs() > KB_Fact::MAX_ARG_FOR_QUERY )
    query_mode=0;
   else if( x.IsQueryableByEntries() )
    query_mode=2;
   else if( x.IsQueryableByWords() )
    query_mode=1;
   else
    query_mode=0;
  }
 else if( query_mode==2 )
  {
   if( x.CountArgs() > KB_Fact::MAX_ARG_FOR_QUERY || !x.IsQueryableByEntries() )
    {
     query_mode=0;
    }
  }
 else if( query_mode==1 )
  {
   if( x.CountArgs() > KB_Fact::MAX_ARG_FOR_QUERY || !x.IsQueryableByWords() )
    {
     query_mode=0;
    }
  }

 if( (query_mode==1 || query_mode==2) && !check_features )
  {
   if( x.NeedsFeatureCheck() )
    check_features = true;
  }
 
 if( query_mode==0 && !allow_generic )
  {
   throw E_BaseException( "This [facts] requires all records to be indexable" );
  }

 if( x.CountArgs()> KB_Fact::MAX_ARG_FOR_QUERY )
  {
   throw E_BaseException( "Argument limit exceeded for the fact" );
  }

 return;
}
#endif
