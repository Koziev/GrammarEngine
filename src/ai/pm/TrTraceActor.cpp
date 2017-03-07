#if defined SOL_CAA

#include <lem/solarix/translation.h>

using namespace Solarix;

int TrTraceActor::seq=0;


TrTraceActor::TrTraceActor( int Mark, int Location )
 : entering(false), seq_mark(Mark)
{
 src_locations.push_back(Location);
 return;
}

TrTraceActor::TrTraceActor( int Mark, const lem::MCollect<int> & Locations )
 : src_locations(Locations), entering(false), seq_mark(Mark)
{}


bool TrTraceActor::Match( const TrTraceActor * x ) const
{
 return seq_mark == x->seq_mark;
}

void TrTraceActor::PrintContext( Solarix::Dictionary &dict, lem::OFormatter &out ) const
{
}

int TrTraceActor::CountContextItems(void) const
{
 return 0;
}

lem::UFString TrTraceActor::GetContextItemName( int i ) const
{
 return UFString();
}

void TrTraceActor::PrintContextItem( Solarix::Dictionary &dict, int i, lem::OFormatter &out ) const
{
}

void TrTraceActor::PrintCurrentToken( Solarix::Dictionary &dict, lem::OFormatter &out ) const
{
}


#endif
