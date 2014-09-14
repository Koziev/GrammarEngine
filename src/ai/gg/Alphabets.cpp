#include <lem/macro_parser.h>
#include <lem/solarix/Alphabet.h>
#include <lem/solarix/AlphabetEnumerator.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/AlphabetStorage.h>
#include <lem/solarix/Alphabets.h>

using namespace Solarix;

Alphabets::Alphabets(void)
 : storage(NULL), a_count(UNKNOWN)
{
}

Alphabets::~Alphabets(void)
{
 for( lem::Container::size_type i=0; i<alphabets.size(); ++i )
  delete alphabets[i];

 return;
}


void Alphabets::Connect( AlphabetStorage *_storage )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker lock(&cs_init); 
 #endif

 storage = _storage;

 for( lem::Container::size_type i=0; i<alphabets.size(); ++i )
  delete alphabets[i];

 alphabets.clear();
 name2id.clear();
 id2alphabet.clear();
 a_count=UNKNOWN;

 return;
}

int Alphabets::Count(void)
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs_count);
 #endif

 if( a_count==UNKNOWN )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif
   
   if( a_count!=UNKNOWN )
    a_count = storage->CountAlphabets();
  }

 return a_count;
}


AlphabetEnumerator* Alphabets::List(void)
{
 LS_ResultSet * rs = storage->ListAlphabets();
 return new AlphabetEnumerator( this, rs );
}

const Alphabet& Alphabets::operator[]( int id )
{
 if( id==UNKNOWN )
  throw lem::E_BaseException( L"Can not retrieve alphabet with id=-1" );

 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs);
 #endif

 std::map< int, const Alphabet* >::const_iterator it = id2alphabet.find(id);
 if( it!=id2alphabet.end() )
  return * it->second;

 #if defined LEM_THREADS
 lem::Process::RWU_WriterGuard wlock(rlock);
 #endif

 it = id2alphabet.find(id);
 if( it!=id2alphabet.end() )
  return * it->second;

 Alphabet *a = storage->GetAlphabet(id);

 alphabets.push_back(a);
 id2alphabet.insert( std::make_pair( id, a ) );
 return *a;
}


int Alphabets::Find( const lem::UCString &name )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs);
 #endif

 lem::UCString uname(name);
 uname.to_upper();

 std::map<lem::UCString,int>::const_iterator it = name2id.find(uname);
 if( it!=name2id.end() )
  return it->second;

 #if defined LEM_THREADS
 lem::Process::RWU_WriterGuard wlock(rlock);
 #endif

 it = name2id.find(uname);
 if( it!=name2id.end() )
  return it->second;

 const int id = storage->FindAlphabet(name);
 if(id!=UNKNOWN)
  {
   name2id.insert( std::make_pair( uname, id ) );
  }

 return id;
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
void Alphabets::LoadTxt( lem::Iridium::Macro_Parser &txt, Dictionary &dict )
{
 lem::UCString name( txt.read().string() );

 if( Find( name ) != UNKNOWN )
  {
   dict.GetIO().merr().printf(
                         "Alphabet [%us] is already declared\n"
                         , name.c_str()
                        );
   throw E_ParserError();
  }
 

 const int id = storage->AddAlphabet(name);
 Alphabet *a = new Alphabet( id, name );

 a->LoadTxt( txt, dict );
 storage->StoreAlphabet(*a);

 name2id.insert( std::make_pair( name, id ) );
 id2alphabet.insert( std::make_pair( id, a ) );
 alphabets.push_back(a);
 
 return;
}
#endif
