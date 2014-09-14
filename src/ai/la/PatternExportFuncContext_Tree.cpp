#include <lem/solarix/BackTrace.h>
#include <lem/solarix/SynPattern.h>

using namespace Solarix;


bool PatternExportFuncContext_Tree::ContainsCoordPair( const Solarix::GramCoordPair & pair ) const
{
 for( lem::Container::size_type i=0; i<pairs.size(); ++i )
  if( pairs[i].first==pair.GetCoord().GetIndex() && pairs[i].second==pair.GetState() )
   return true;

 return false;
}

void PatternExportFuncContext_Tree::GetCoordStates( int coord_id, lem::MCollect<int> & state_ids ) const
{
 for( lem::Container::size_type i=0; i<pairs.size(); ++i )
  if( pairs[i].first == coord_id )
   state_ids.push_back( pairs[i].second );

 return;
}


void PatternExportFuncContext_Tree::GetCoordStates( const lem::UCString & mark_name, int coord_id, lem::MCollect<int> & state_ids ) const
{
 const BackTraceItem & mark_data = *parent_trace->Get(PatternSequenceNumber,mark_name);
 mark_data.GetCoordStates( coord_id, state_ids );
 return;
}



void PatternExportFuncContext_Tree::SubtractMarkedNodeCoordStates( const lem::UCString & mark_name, int coord_id, lem::MCollect<int> & state_ids ) const
{
 LEM_CHECKIT_Z( coord_id!=UNKNOWN );

 if( !state_ids.empty() )
  {
   if( mark_name.empty() )
    {
     int state_id = UNKNOWN;
     for( lem::Container::size_type j=0; j<pairs.size(); ++j )
      if( pairs[j].first == coord_id )
       {
        state_id = pairs[j].second;
        break;
       }

     LEM_CHECKIT_Z( state_id!=UNKNOWN );
     
     int i=CastSizeToInt(state_ids.size())-1;
     while(i>=0)
      {
       if( state_ids[i]==state_id )
        {
         state_ids.Remove(i);
        }
  
       --i;
      }
    }
   else
    {
     const BackTraceItem & mark_data = *parent_trace->Get(PatternSequenceNumber,mark_name);
     
     const int state_id = mark_data.GetCoordState( coord_id );
     if( state_id!=UNKNOWN )
      {
       int i=CastSizeToInt(state_ids.size())-1;
       while(i>=0)
        {
         if( state_ids[i]==state_id )
          {
           state_ids.Remove(i);
          }
    
         --i;
        }
      }
    }
  }

 return;
}


