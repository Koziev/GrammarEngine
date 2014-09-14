#include <lem/solarix/BackTraceItem.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/SynPatternCompilation.h>
#include <lem/solarix/PatternConstraints.h>

using namespace Solarix;


PatternConstraint::PatternConstraint(void) : from_coord_id(UNKNOWN), to_coord_id(UNKNOWN)
{
 constraint_func = UnknownFunc;
}


bool PatternConstraint::operator!=( const PatternConstraint & x ) const
{
 return from_marker!=x.from_marker ||
        from_coord_id!=x.from_coord_id ||
        to_marker!=x.to_marker ||
        to_coord_id!=x.to_coord_id ||
        constraint_func!=x.constraint_func;
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
void PatternConstraint::LoadTxt( 
                                Dictionary &dict,
                                lem::Iridium::Macro_Parser & txtfile,
                                SynPatternCompilation & compilation_context
                               )
{
 lem::Iridium::BethToken marker_name = txtfile.read();

 if( compilation_context.Find(marker_name)==UNKNOWN )
  {
   dict.GetIO().merr().printf( "Marker [%us] is not declared in this pattern", marker_name.c_str() );
   lem::Iridium::Print_Error(marker_name,txtfile);
   throw lem::E_BaseException();
  }

 // ---------------------------

 from_marker = marker_name.string();
 from_marker.to_upper();

 // ---------------------------

 txtfile.read_it( B_COLON );

 lem::Iridium::BethToken coord_name1 = txtfile.read();
 //if( for_group ) txtfile.read_it( B_CSPAREN );

 Solarix::GramCoordAdr iglob_coord1 = dict.GetSynGram().FindCoord(coord_name1.string());

 if( !iglob_coord1.IsDefined() )
  {
   dict.GetSynGram().GetIO().merr().printf( "Unknown coordinate %us\n", coord_name1.c_str() );
   lem::Iridium::Print_Error(coord_name1,txtfile);
   throw lem::E_BaseException();
  }

 from_coord_id = iglob_coord1.GetIndex();

 // ---------------------------

 lem::Iridium::BethToken func = txtfile.read();

 if( func.GetToken()==B_EQUAL )
  constraint_func = EqualFunc;
 else if( func.GetToken()==B_LOGNE )
  constraint_func = NotEqualFunc;
 else
  {
   dict.GetIO().merr().printf( "Unknown constraint [%us]", func.string().c_str() );
   lem::Iridium::Print_Error(func,txtfile);
   throw lem::E_BaseException();
  }

 marker_name = txtfile.read();

 if( compilation_context.Find(marker_name)==UNKNOWN )
  {
   dict.GetIO().merr().printf( "Marker [%us] is not declared in this pattern", marker_name.c_str() );
   lem::Iridium::Print_Error(marker_name,txtfile);
   throw lem::E_BaseException();
  }

 to_marker = marker_name.string();
 to_marker.to_upper();

 // ---------------------------

 txtfile.read_it( B_COLON );

 lem::Iridium::BethToken coord_name2 = txtfile.read();
 //if( for_group ) txtfile.read_it( B_CSPAREN );

 Solarix::GramCoordAdr iglob_coord2 = dict.GetSynGram().FindCoord(coord_name2.string());

 if( !iglob_coord2.IsDefined() )
  {
   dict.GetSynGram().GetIO().merr().printf( "Unknown coordinate %us\n", coord_name2.c_str() );
   lem::Iridium::Print_Error(coord_name2,txtfile);
   throw lem::E_BaseException();
  }

 to_coord_id = iglob_coord2.GetIndex();

 return;
}
#endif    


void PatternConstraint::SaveBin( lem::Stream &bin ) const
{
 bin.write( &from_marker, sizeof(from_marker) );
 bin.write( &to_marker, sizeof(to_marker) );
 bin.write_int( from_coord_id );
 bin.write_int( to_coord_id );
 bin.write( &constraint_func, sizeof(constraint_func) );
 return;
}


void PatternConstraint::LoadBin( lem::Stream &bin )
{
 bin.read( &from_marker, sizeof(from_marker) );
 bin.read( &to_marker, sizeof(to_marker) );
 from_coord_id = bin.read_int();
 to_coord_id = bin.read_int();
 bin.read( &constraint_func, sizeof(constraint_func) );
 return;
}


#if defined SOL_CAA
PatternConstraintResult PatternConstraint::Check(
                                                 const LexicalAutomat & la,
                                                 const BackTrace * parent_trace,
                                                 const lem::MCollect<int> & PatternSequenceNumber,
                                                 const SynPatternResult * cur_result
                                                ) const
{ 
 PatternConstraintResult res;

 const BackTraceItem & mark_data1 = * cur_result->trace.Get(PatternSequenceNumber,from_marker);
 const BackTraceItem & mark_data2 = * cur_result->trace.Get(PatternSequenceNumber,to_marker);

 lem::MCollect<int> states1;
 mark_data1.GetCoordStates( from_coord_id, states1 );

 if( states1.empty() )
  {
   res.success=true;
   return res;
  }

 lem::MCollect<int> states2;
 mark_data2.GetCoordStates( to_coord_id, states2 );

 if( states2.empty() )
  {
   res.success=true;
   return res;
  }

 switch( constraint_func )
 {
  case EqualFunc:
  {
   for( lem::Container::size_type i=0; i<states1.size(); ++i )
    {
     const int state1_id = states1[i];
     if( states2.find( state1_id )!=UNKNOWN )
      {
       res.success=true;
       return res;
      }
    }

   break;
  }

  case NotEqualFunc:
  {
   res.success=true;
   for( lem::Container::size_type i=0; i<states1.size(); ++i )
    {
     const int state1_id = states1[i];
     if( states2.find( state1_id )!=UNKNOWN )
      {
       res.success=false;
       return res;
      }
    }

   return res;
  }

  default:
   LEM_STOPIT;
 }

 res.success = false;
 return res;
}
#endif
