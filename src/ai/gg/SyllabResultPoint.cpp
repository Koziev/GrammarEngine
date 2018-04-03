#include <lem/macro_parser.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/AlphabetStorage.h>
#include <lem/solarix/SyllabRule.h>

using namespace Solarix;


SyllabResultPoint::SyllabResultPoint()
{
 copy_index=merge_index0=merge_count=UNKNOWN;
}


SyllabResultPoint::SyllabResultPoint( int _copy_index, int _merge_index0, int _merge_count )
 : copy_index(_copy_index), merge_index0(_merge_index0), merge_count(_merge_count)
{
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
void SyllabResultPoint::LoadTxt(
                                lem::Iridium::Macro_Parser &txtfile,
                                Dictionary &dict,
                                const SyllabCondition &condition
                               )
{
 lem::Iridium::BethToken t = txtfile.read();

 const int max_index = condition.Count()-1;

 if( lem::is_int( t.string() ) )
  {
   copy_index = lem::to_int(t.string());
   if( copy_index>max_index )
    {
     lem::Iridium::Print_Error(t,txtfile);
     dict.GetIO().merr().printf( "Value %d exceeds the maximum possible index=%d\n", copy_index, max_index );
     throw lem::E_BaseException();
    }
  }
 else if( t.string().eqi(L"merge") )
  {
   txtfile.read_it( B_OFIGPAREN );
   merge_index0 = txtfile.read_int();
   merge_count = 1;
   int cur_index = merge_index0+1;
   while( !txtfile.eof() )
    {
     if( txtfile.probe(B_CFIGPAREN) )
      break;

     lem::Iridium::BethToken t_n = txtfile.read();

     int next_index = lem::to_int(t_n.string());
     if( next_index>max_index )
      {
       lem::Iridium::Print_Error(t_n,txtfile);
       dict.GetIO().merr().printf( "Value %d exceeds the maximum possible index=%d\n", copy_index, max_index );
       throw lem::E_BaseException();
      }

     if( next_index!=cur_index )
      {
       lem::Iridium::Print_Error(t_n,txtfile);
       dict.GetIO().merr().printf( "%d is expected instead of %d\n", cur_index, next_index );
       throw lem::E_BaseException();
      }
     
     cur_index++;
     merge_count++;
    }
  }
 else
  {
   lem::Iridium::Print_Error(t,txtfile);
   dict.GetIO().merr().printf( "Unknown statement %us\n", t.c_str() );
   throw lem::E_BaseException();
  }

 return;
}
#endif


void SyllabResultPoint::Store( AlphabetStorage * storage, int id_rule, int point_index ) const
{
 storage->StoreSyllabResultPoint(
                                 id_rule,
                                 point_index, 
                                 copy_index,
                                 merge_index0,
                                 merge_count
                                );

 return;
}

SyllabContextPoint* SyllabResultPoint::Produce( SyllabContext & ctx, int cursor_pos ) const
{
 if( copy_index!=UNKNOWN )
  {
   return ctx.ExtractPoint( cursor_pos + copy_index );
  }
 else
  {
   SyllabContextPoint * p = new SyllabContextGroup( ctx, cursor_pos+merge_index0, merge_count );
   return p;
  }
}

