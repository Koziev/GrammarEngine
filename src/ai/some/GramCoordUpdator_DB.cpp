#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/coordinate.h>
#include <lem/solarix/GramCoordUpdator_DB.h>

using namespace Solarix;


GramCoordUpdator_DB::GramCoordUpdator_DB( LexiconStorage*_db )
 : db(_db)
{
}

void GramCoordUpdator_DB::Update( GramCoord &x )
{
 db->StoreCoord( x.id, x );
 return;
}
