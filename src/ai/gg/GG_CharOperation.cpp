#include <lem/macro_parser.h>
#include <lem/WideStringUcs4.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/GG_CharOperation.h>

using namespace Solarix;
using namespace lem;

GG_CharOperation::GG_CharOperation(void)
{
}

GG_CharOperation::GG_CharOperation( int Id, const lem::UCString &Name, const std::map< lem::uint32_t, lem::uint32_t > &Items )
 : id(Id), name(Name), items(Items)
{
 for( std::map< lem::uint32_t, lem::uint32_t >::const_iterator it=Items.begin(); it!=Items.end(); ++it )
  result_items.insert( it->second );
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
void GG_CharOperation::LoadTxt( lem::Iridium::Macro_Parser &txtfile, Dictionary &dict )
{
 name = txtfile.read().string();
 name.strip(L'"');
 txtfile.read_it( B_OFIGPAREN );

 while( !txtfile.eof() )
  {
   if( txtfile.probe(B_CFIGPAREN) )
    break;

   UCString src_char = txtfile.read().string();
   src_char.strip_apostrophes();

   txtfile.read_it( B_ARROW_R );

   UCString res_char = txtfile.read().string();
   res_char.strip_apostrophes();
  
   WideStringUcs4 src_enum( src_char.c_str() );
   const lem::uint32_t src_ucs4 = src_enum.Fetch();

   WideStringUcs4 res_enum( res_char.c_str() );
   const lem::uint32_t res_ucs4 = res_enum.Fetch();

   if( items.find(src_ucs4)!=items.end() )
    {
     lem::Iridium::Print_Error(txtfile);
     dict.GetIO().merr().printf( "Character operation %us is already declared for symbol %us\n", name.c_str(), src_char.c_str() );
     throw lem::E_BaseException();
    }

   items.insert( std::make_pair( src_ucs4, res_ucs4 ) );
  }

 return;
}
#endif

lem::uint32_t GG_CharOperation::Apply( lem::uint32_t src ) const
{
 std::map< lem::uint32_t, lem::uint32_t >::const_iterator it = items.find(src);
 if( it==items.end() )
  return src;

 return it->second;
}

