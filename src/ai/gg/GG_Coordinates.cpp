#include <lem/sol_io.h>
#include <lem/oformatter.h>
#include <lem/macro_parser.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/AlphabetStorage.h>
#include <lem/solarix/GG_CoordEnumerator.h>
#include <lem/solarix/GG_Coordinates.h>

using namespace Solarix;


GG_Coordinates::GG_Coordinates( GraphGram *_gg )
 : gg(_gg), db(NULL)
{
}


void GG_Coordinates::Connect( AlphabetStorage *_db )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs);
 #endif

 coord_ptr.clear();
 coord_id.clear();
 id2coord.clear();
 name2id.clear();

 LEM_CHECKIT_Z(_db!=NULL);
 db = _db;
 return;
}


GramCoord* GG_Coordinates::Get( int id )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 std::map< int, int >::const_iterator it = id2coord.find(id);
 if( it!=id2coord.end() )
  {
   return coord_ptr[it->second];
  }

 // в кэше класс с указанным id не найден, поищем в БД.
 GramCoord *new_coord = new GramCoord();
 if( db->GetCoord( id, *new_coord ) )
  { 
   const int index = CastSizeToInt(coord_ptr.size());
   coord_ptr.push_back(new_coord);
   coord_id.push_back(id);
   id2coord.insert( std::make_pair( id, index ) );
   name2id.insert( std::make_pair( lem::to_upper(new_coord->GetName().front()), id ) );

   return new_coord;
  }
 else
  {
   delete new_coord;
   lem::UFString msg( lem::format_str( L"Can not find the coordinate id=%d", id ) );
   throw lem::E_BaseException(msg);
  }
}


const GramCoord& GG_Coordinates::operator[]( int id )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs);
 #endif

 return *Get(id);
}

GramCoord& GG_Coordinates::GetCoord( int id )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs);
 #endif

 return *Get(id);
}


int GG_Coordinates::Find( const UCString &name )
{
 LEM_CHECKIT_Z( !name.empty() );

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs);
 #endif

 lem::UCString uname(lem::to_upper(name));
 std::map<lem::UCString,int>::const_iterator it = name2id.find( uname );
 if( it!=name2id.end() )
  return it->second;

 // поищем в БД
 const int id = db->FindCoord(name);

 if( id!=UNKNOWN )
  name2id.insert( std::make_pair(uname,id) );

 return id;
}


int GG_Coordinates::Count(void)
{
 return db->CountCoords();
}


int GG_Coordinates::Id2Index( int id )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 std::map< int, int >::const_iterator it = id2coord.find(id);
 if( it!=id2coord.end() )
  {
   return it->second;
  }

 GramCoord *dummy = Get(id);
 return id2coord.find(id)->second;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
GramCoord* GG_Coordinates::LoadTxt(
                                   lem::Iridium::Macro_Parser &txtfile,
                                   bool IsRealized
                                  )
{
 LEM_CHECKIT_Z( db!=NULL );

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs);
 #endif

 const bool is_extern = !IsRealized;

 // Загружаем реализацию или объявление координаты.
 GramCoord *cl = new GramCoord( txtfile, *gg, IsRealized );

 const int ic = Find(cl->GetName().front());

 if( ic==UNKNOWN )
  {
   AddNewCoord(cl,IsRealized);
   return cl;
  } 
 else
  {
   const int index = Id2Index(ic);
   GramCoord *old_coord = coord_ptr[index];
   if( is_extern && !old_coord->IsRealized() )
    {
     // Фрагмент типа:
     //
     // extern enum X
     //         :
     // extern enum X

     if( *old_coord != *cl )
      {
       // Не совпадают объявления для класса.
       gg->GetIO().merr().printf(
                                  "%vfDTwo coordinates have the same name [%us].%vn\n"
                                  , cl->GetName().front().c_str()
                                 );
       lem::Iridium::Print_Error(txtfile);
       throw lem::E_ParserError();
      }

     delete cl;
     return NULL;
    }

   if( !is_extern && !old_coord->IsRealized() )
    {
     // Фрагмент типа:
     //
     // extern enum X
     //         :
     // enum X { ... }
     if( old_coord->IsRealized() && *cl!=*old_coord )
      {
       gg->GetIO().merr().printf(
                                  "%vfDTwo coords have the same name [%us].%vn\n"
                                  , cl->GetName().front().c_str()
                                 );
       lem::Iridium::Print_Error(txtfile);
       throw lem::E_ParserError();
      }
     else
      {
       // Запоминаем реализацию вместо объявления.
       cl->id = old_coord->id;
       delete old_coord;
       coord_ptr[index] = cl;
       db->StoreCoord(cl->id,*cl);
      }

     return NULL;
    }

   if( is_extern && old_coord->IsRealized() )
    {
     // Фрагмент:
     //
     //   enum X { ... }
     //          :
     //   extern enum X

     if( cl->IsRealized() && *cl!=*old_coord )
      {
       gg->GetIO().merr().printf(
                                  "%vfDTwo coordinates have the same name [%us].%vn\n"
                                  , cl->GetName().front().c_str()
                                 );
       lem::Iridium::Print_Error(txtfile);
       throw lem::E_ParserError();
      }

     delete cl;
     return NULL;
    }

   // Если координата с таким именем уже была определена, то добавляем
   // к ней новые определения состояний.
   if( !is_extern && old_coord->IsRealized() )
    {
     // Проводим конкатенацию координат. Но сначала проверим, что
     // нет повтора состояний.
     const int nstates=cl->GetTotalStates();
     for( int is=0; is<nstates; is++ )
      if( old_coord->FindState( cl->GetStateName(is) ) != UNKNOWN )
       {
        gg->GetIO().merr().printf(
                              "%vfDState [%us] definition duplicated for a coordinate [%us]%vn\n",
                              cl->GetStateName(is).c_str(),
                              cl->GetName().string().c_str()
                             );

        Print_Error(txtfile);
        throw lem::E_ParserError();
       }

     lem::Ptr<GramCoordUpdator> updator = old_coord->updator;
     old_coord->updator.Delete();
     old_coord->Add(*cl);
     delete cl;
     db->StoreCoord( old_coord->id, *old_coord );
     old_coord->updator = updator;
     return NULL;
    }
  }

 delete cl;
 return NULL;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void GG_Coordinates::AddNewCoord( GramCoord *new_coord, bool IsRealized )
{
 const int index = CastSizeToInt(coord_ptr.size());

 const int id = db->AddCoord( *new_coord );
 new_coord->id = id;

 coord_ptr.push_back(new_coord);
 coord_id.push_back(id);
 id2coord.insert( std::make_pair( id, index ) );

 name2id.insert( std::make_pair( lem::to_upper(new_coord->GetName().front()), id ) );

 return;
}
#endif

CoordEnumerator* GG_Coordinates::Enumerate(void)
{
 return new GG_CoordEnumerator( db, this );
}

