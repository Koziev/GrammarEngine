#include <lem/macro_parser.h>
#include <lem/oformatter.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/TreeScorerGroupParams.h>
#include <lem/solarix/TreeScorers.h>

using namespace Solarix;

TreeScorers::TreeScorers() : storage(NULL)
{}

TreeScorers::~TreeScorers()
{
 Clear();
}

void TreeScorers::Connect( LexiconStorage * _storage )
{
 storage = _storage;
 return;
}

void TreeScorers::Clear()
{
 for( lem::Container::size_type i=0; i<params.size(); ++i )
  delete params[i];

 params.clear();
 id2params.clear();
 name2id.clear();
 return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void TreeScorers::LoadGroup( Dictionary & dict, lem::Iridium::Macro_Parser &txtfile )
{
 lem::Iridium::BethToken t_name = txtfile.read();
 lem::UCString gname = t_name.string();
 gname.to_upper();
 if( name2id.find(gname)!=name2id.end() )
  {
   lem::Iridium::Print_Error( t_name, txtfile );
   dict.GetIO().merr().printf( "Tree scorer group [%us] is already declared\n", t_name.string().c_str() );
   throw lem::E_ParserError();
  }

 TreeScorerGroupParams params;

 if( txtfile.probe( B_OFIGPAREN ) )
  {
   while( !txtfile.eof() )
   {
    if( txtfile.probe( B_CFIGPAREN ) )
     break;

    lem::Iridium::BethToken tparam = txtfile.read();
    if( tparam.string().eqi(L"allow_unmatched_children") )
     {
      txtfile.read_it( B_EQUAL );

      lem::Iridium::BethToken tbool = txtfile.read();
      if( tbool.string().eqi(L"true") )
       params.allow_unmatched_children = true;
      else if( tbool.string().eqi(L"false") )
       params.allow_unmatched_children = false;
      else
       {
        lem::Iridium::Print_Error( tbool, txtfile );
        dict.GetIO().merr().printf( "[%us] is not boolean value\n", tbool.string().c_str() );
        throw lem::E_ParserError();
       }
     }
    else if( tparam.string().eqi(L"language") )
     {
      txtfile.read_it( B_EQUAL );

      lem::Iridium::BethToken lang = txtfile.read();
      params.id_language = dict.GetSynGram().Find_Language(lang.string());
      if( params.id_language==UNKNOWN )
       {
        lem::Iridium::Print_Error(lang,txtfile);
        dict.GetIO().merr().printf( "Unknown language name %us\n", lang.c_str() );
        throw lem::E_BaseException();
       }

    }
    else
     {
      lem::Iridium::Print_Error( tparam, txtfile );
      dict.GetIO().merr().printf( "Unknown tree scorer group parameter [%us]\n", tparam.string().c_str() );
      throw lem::E_ParserError();
     }
   }
  }

 const int id = storage->StoreTreeScorerGroup( gname, params );
 name2id.insert( std::make_pair(gname,id) );

 return;
}
#endif


int TreeScorers::FindGroup( const lem::UCString & name, bool load_from_db )
{
 typedef std::map<lem::UCString,int>::const_iterator IT;
 lem::UCString uname(name);
 uname.to_upper();

 if( !load_from_db )
  {
   IT it = name2id.find( uname );
   if( it==name2id.end() )
    return UNKNOWN;
   else
    return it->second;
  }
 else
  {
   #if defined LEM_THREADS
   lem::Process::RWU_ReaderGuard rlock(cs_names);
   #endif

   IT it = name2id.find( uname );
   if( it==name2id.end() )
    {
     #if defined LEM_THREADS
     lem::Process::RWU_WriterGuard wlock(rlock);
     #endif

     it = name2id.find( uname );
     if( it==name2id.end() )
      {
       const int id = storage->FindTreeScorerGroup(uname);
       if( id!=UNKNOWN )
        name2id.insert( std::make_pair(uname,id) );

       return id;
      }
     else
      return it->second;
    }
   else
    return it->second;
  }
}

const TreeScorerGroupParams& TreeScorers::GetGroupParams( int id )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 typedef std::map<int,const TreeScorerGroupParams*>::const_iterator IT;

 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs_names);
 #endif

 IT it = id2params.find(id);
 if( it==id2params.end() )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif

   it = id2params.find(id);
   if( it==id2params.end() )
    {
     TreeScorerGroupParams * p = new TreeScorerGroupParams();
     storage->LoadTreeScorerGroupParams( id, *p );
     params.push_back(p);
     id2params.insert( std::make_pair(id,p) );
     return *p;
    }
   else
    {
     return * it->second;
    }
  }
 else
  {
   return * it->second;
  }
}

