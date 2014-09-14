#include <lem/runtime_checks.h>
#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/AuxFormTypes.h>

using namespace Solarix;

AuxFormTypes::AuxFormTypes(void):db(NULL), id_seq(0)
{
}

    
void AuxFormTypes::Connect( LexiconStorage *_db )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs);
 #endif

 LEM_CHECKIT_Z( _db!=NULL );
 db = _db;
 id2name.clear();
 name2id.clear();
 return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void AuxFormTypes::LoadTxt( lem::Iridium::Macro_Parser &txt )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs);
 #endif

 LEM_CHECKIT_Z( db!=NULL );

 txt.read_it( B_EQUAL );
 txt.read_it( B_OFIGPAREN );

 lem::UCString type_name, uname;
 while( !txt.eof() )
  {
   if( txt.probe(B_CFIGPAREN) )
    break;
 
   int id=id_seq+1;
   type_name = txt.read();
   if( txt.probe(B_EQUAL) )
    {
     id = txt.read_int();
     if( id<0 )
      {
       lem::MemFormatter mem;
       mem.printf( "Invalid ID=%d for auxiluary form type", id, type_name.c_str() );
       throw lem::E_BaseException( mem.string() );
      }
    }

   id_seq = id;

   uname = lem::to_upper(type_name);

   if( id2name.find(id)!=id2name.end() || name2id.find(uname)!=name2id.end() )
    {
     lem::MemFormatter mem;
     mem.printf( "Auxiluary form type id=%d name=%us redefinition", id, type_name.c_str() );
     throw lem::E_BaseException( mem.string() );
    }

   db->AddAuxFormType( id, type_name );
   id2name.insert( std::make_pair( id, type_name ) );
   name2id.insert( std::make_pair( uname, id ) );
  }

 return;
}
#endif

#if defined SOL_SAVETXT
void AuxFormTypes::SaveTxt( lem::OFormatter &txtfile ) const
{
 LEM_CHECKIT_Z( db!=NULL );

 lem::Ptr<LS_ResultSet> rs = db->ListAuxFormTypes();

 txtfile.printf( "aux_forms = {" );
 while( rs->Fetch() )
  {
   int id = rs->GetInt(0);
   lem::UCString name = rs->GetUCString(1);
   txtfile.printf( " %us=%d", name.c_str(), id );
  }

 return;
}
#endif


int AuxFormTypes::operator[]( const lem::UCString &name )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs);
 #endif

 Preload();
 std::map<lem::UCString,int>::const_iterator it = name2id.find(lem::to_upper(name));
 return it==name2id.end() ? UNKNOWN : it->second;
}

const lem::UCString& AuxFormTypes::operator[]( int id )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs);
 #endif

 Preload();
 std::map<int,lem::UCString>::const_iterator it = id2name.find(id);
 if( it==id2name.end() )
  {
   lem::MemFormatter mem;
   mem.printf( "AuxFormTypes error: cannot find id=%d", id );
   throw lem::E_BaseException(mem.string());
  }

 return it->second;
}

void AuxFormTypes::Preload(void)
{
 if( dirty )
  {
   dirty=false;
   id2name.clear();
   name2id.clear(); 
   
   LEM_CHECKIT_Z( db!=NULL );

   lem::Ptr<LS_ResultSet> rs = db->ListAuxFormTypes();

   while( rs->Fetch() )
    {
     int id = rs->GetInt(0);
     lem::UCString name = rs->GetUCString(1);
     lem::UCString uname = lem::to_upper(name);
     id2name.insert( std::make_pair(id,name) );
     name2id.insert( std::make_pair(uname,id) );
    }
  }

 return;
}
