#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/sql_production.h>
#include <lem/solarix/ThesaurusStorage.h>
#include <lem/solarix/ThesaurusTagDefs.h>

using namespace lem;
using namespace Solarix;

ThesaurusTag::ThesaurusTag(void)
{
 id=UNKNOWN;
}


ThesaurusTag::ThesaurusTag( int _id, ThesaurusStorage *db )
 : id(_id)
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 db->GetTagName( id, name );
 lem::Ptr<LS_ResultSet> rs = db->List_TagValues(id);
 while( rs->Fetch() )
  {
   ivalues.push_back( rs->GetInt(0) );
   values.push_back( rs->GetUCString(1) );
  }

 return;
}


void ThesaurusTag::Store( ThesaurusStorage *db )
{
 id = db->AddTag( name );

 for( lem::Container::size_type i=0; i<values.size(); ++i )
  {
   db->AddTagValue( id, ivalues[i], values[i] );
  }

 return;
}


int ThesaurusTag::operator[]( const lem::UCString &value_name ) const
{
 for( lem::Container::size_type i=0; i<values.size(); ++i )
  if( values[i].eqi(value_name) )
   return ivalues[i];

 return UNKNOWN;
}
   

const lem::UCString & ThesaurusTag::operator[]( int ivalue ) const
{
 const int i = ivalues.find(ivalue);
 if( i==UNKNOWN )
  throw lem::E_BaseException( "ThesaurusTag: value id is not found" );
 
 return values[i];
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
void ThesaurusTag::LoadTxt(
                           lem::Iridium::Macro_Parser & txtfile,
                           const lem::Sol_IO &sol_io,
                           const Binarization_Options & options
                          )
{
 lem::Iridium::BethToken t = txtfile.read();
 name = t.string();
 name.strip(L'"');

 int ivalue=0;
 if( txtfile.pick().GetToken()==B_EQUAL )
  {
   txtfile.read_it(B_EQUAL);
   txtfile.read_it(B_OFIGPAREN);

   while( !txtfile.eof() )
    {
     lem::Iridium::BethToken v = txtfile.read();
 
     if( v.GetToken()==B_CFIGPAREN )
      break;

     UCString vs=v.string();
     vs.strip(L'"');

     if( operator[](vs)!=UNKNOWN )
      {
       lem::Iridium::Print_Error( v, txtfile );
       sol_io.err->printf( "Thesaurus tag [%us] value [%us] is already declared", name.c_str(), vs.c_str() );
       throw E_ParserError();
      }

     values.push_back(vs);  
     ivalues.push_back(ivalue++);
    }
  }

 return;
}
#endif

#if defined SOL_REPORT
void ThesaurusTag::Save_SQL( OFormatter &out, const SQL_Production &sql_version ) const
{
 out.printf( "INSERT INTO sg_tag( id, name ) VALUES ( %d, %us'%us' );\n"
  , id, sql_version.GetNPrefix(), sql_version.SqlStr(name).c_str() );

 for( lem::Container::size_type i=0; i<values.size(); ++i )
  {
   out.printf( "INSERT INTO sg_tag_value( id_tag, ivalue, name ) VALUES ( %d, %d, %us'%us' );\n",
    id, ivalues[i], sql_version.GetNPrefix(), sql_version.SqlStr(values[i]).c_str() );
  }

 return;
}
#endif
