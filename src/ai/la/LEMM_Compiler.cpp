#if defined SOL_LOADTXT

#include <lem/oformatter.h>
#include <lem/macro_parser.h>
#include <lem/sol_io.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/ucstring_functions.h>
#include <lem/solarix/LEMM_Compiler.h>

using namespace Solarix;

LEMM_Compiler::LEMM_Compiler()
{
 suffix_len = 1;
}

LEMM_Compiler::~LEMM_Compiler()
{
}


void LEMM_Compiler::LoadNGram( lem::Iridium::Macro_Parser & txtfile, Dictionary & dict, lem::MCollect<int> & terms, int order ) const
{
 lem::Iridium::BSourceState beg = txtfile.tellp();

 while( !txtfile.eof() )
 {
  lem::Iridium::BethToken t = txtfile.read();
  if( lem::is_int(t.string()) )
   terms.push_back( lem::to_int(t.string()) );
  else
   {
    txtfile.seekp(t);
    break;
   }
 }

 if( terms.size() != order+1 )
  {
   dict.GetIO().merr().printf( "%vfDInvalid ngram%vn\n" );
   lem::Iridium::Print_Error( beg, txtfile );
   throw lem::E_ParserError();
  }

 return;
}

void LEMM_Compiler::LoadTxt( lem::Iridium::Macro_Parser & txtfile, Dictionary & dict )
{
 txtfile.read_it( B_OFIGPAREN );

 while( !txtfile.eof() )
 {
  lem::Iridium::BethToken t = txtfile.read();
  if( t.eqi( L"suffix" ) )
   {
    int id = txtfile.read_int();
    lem::UCString suffix = txtfile.read();
    if( suffix[0]==L'"' && suffix.back()==L'"' )
     suffix.strip_quotes();

    suffices.push_back( std::make_pair(id,suffix) );
   }
  else if( t.eqi( L"word" ) )
   {
    int id = txtfile.read_int();
    lem::UCString word = txtfile.read();
    if( word[0]==L'"' && word.back()==L'"' )
     word.strip_quotes();

    words.push_back( std::make_pair(id,word) );
   }
  else if( t.eqi(L"ngram2") )
   {
    lem::MCollect<int> terms;
    LoadNGram(txtfile,dict,terms,2);
    LEMM_Ngram2 n2;
    n2.tags.first = terms[0];
    n2.tags.second = terms[1];
    n2.freq = terms[2];
    ngram2.push_back(n2);
   }
  else if( t.eqi(L"ngram2_1") )
   {
    lem::MCollect<int> terms;
    LoadNGram(txtfile,dict,terms,2);
    LEMM_Ngram2 n2;
    n2.tags.first = terms[0];
    n2.tags.second = terms[1];
    n2.freq = terms[2];
    ngram2_1.push_back(n2);
   }
  else if( t.eqi(L"ngram3") )
   {
    lem::MCollect<int> terms;
    LoadNGram(txtfile,dict,terms,3);
    LEMM_Ngram3 n3;
    n3.tags.first = terms[0];
    n3.tags.second = terms[1];
    n3.tags.third = terms[2];
    n3.freq = terms[3];
    ngram3.push_back(n3);
   }
  else if( t.eqi(L"ngram3_1") )
   {
    lem::MCollect<int> terms;
    LoadNGram(txtfile,dict,terms,3);
    LEMM_Ngram3 n3;
    n3.tags.first = terms[0];
    n3.tags.second = terms[1];
    n3.tags.third = terms[2];
    n3.freq = terms[3];
    ngram3_1.push_back(n3);
   }
  else if( t.eqi(L"ngram3_2") )
   {
    lem::MCollect<int> terms;
    LoadNGram(txtfile,dict,terms,3);
    LEMM_Ngram3 n3;
    n3.tags.first = terms[0];
    n3.tags.second = terms[1];
    n3.tags.third = terms[2];
    n3.freq = terms[3];
    ngram3_2.push_back(n3);
   }
  else if( t.eqi(L"ngram4") )
   {
    lem::MCollect<int> terms;
    LoadNGram(txtfile,dict,terms,4);
    LEMM_Ngram4 n4;
    n4.tags.first = terms[0];
    n4.tags.second = terms[1];
    n4.tags.third = terms[2];
    n4.tags.fourth = terms[3];
    n4.freq = terms[4];
    ngram4.push_back(n4);
   }
  else if( t.eqi( L"suffix_len" ) )
   {
    suffix_len = txtfile.read_int();
   }

  else if( t.GetToken()==B_CFIGPAREN )
   break;
  else
   {
    dict.GetIO().merr().printf( "%vfDInvalid statement [%us]%vn\n", t.string().c_str() );
    lem::Iridium::Print_Error( t, txtfile );
    throw lem::E_ParserError();
   }
 }

 return;
}


void LEMM_Compiler::Prepare()
{
 std::sort( ngram2.begin(), ngram2.end() );
 std::sort( ngram2_1.begin(), ngram2_1.end() );

 std::sort( ngram3.begin(), ngram3.end() );
 std::sort( ngram3_1.begin(), ngram3_1.end() );
 std::sort( ngram3_2.begin(), ngram3_2.end() );

 std::sort( ngram4.begin(), ngram4.end() );

 return;
}



void LEMM_Compiler::SaveBin( lem::Stream & bin ) const
{
 bin.write_bool(true);

 const lem::uint32_t model_flags = 0x0000000E;
 bin.write( &model_flags, sizeof(model_flags) );
 bin.write_int( suffix_len );

 bin.write_int( CastSizeToInt(suffices.size()) );
 for( lem::Container::size_type i=0; i<suffices.size(); ++i )
  {
   bin.write( &suffices[i].first, sizeof(suffices[i].first) );
   lem::Save_Packed(suffices[i].second,bin);
  }

 bin.write_int( CastSizeToInt(words.size()) );
 for( lem::Container::size_type i=0; i<words.size(); ++i )
  {
   bin.write( &words[i].first, sizeof(words[i].first) );
   lem::Save_Packed(words[i].second,bin);
  }

 bin.write_int( CastSizeToInt(ngram2.size()) );
 for( lem::Container::size_type i=0; i<ngram2.size(); ++i )
  bin.write( &ngram2[i], sizeof(ngram2[i]) );

 bin.write_int( CastSizeToInt(ngram2_1.size()) );
 for( lem::Container::size_type i=0; i<ngram2_1.size(); ++i )
  bin.write( &ngram2_1[i], sizeof(ngram2_1[i]) );

 bin.write_int( CastSizeToInt(ngram3.size()) );
 for( lem::Container::size_type i=0; i<ngram3.size(); ++i )
  bin.write( &ngram3[i], sizeof(ngram3[i]) );

 bin.write_int( CastSizeToInt(ngram3_1.size()) );
 for( lem::Container::size_type i=0; i<ngram3_1.size(); ++i )
  bin.write( &ngram3_1[i], sizeof(ngram3_1[i]) );

 bin.write_int( CastSizeToInt(ngram3_2.size()) );
 for( lem::Container::size_type i=0; i<ngram3_2.size(); ++i )
  bin.write( &ngram3_2[i], sizeof(ngram3_2[i]) );


 bin.write_int( CastSizeToInt(ngram4.size()) );
 for( lem::Container::size_type i=0; i<ngram4.size(); ++i )
  bin.write( &ngram4[i], sizeof(ngram4[i]) );

 return;
}


void LEMM_Compiler::PrintModelInfo( lem::OFormatter & out ) const
{
 out.printf( " model: n_suffix=%d n_word=%d ngram2=%d ngram2_1=%d ngram3=%d ngram3_1=%d ngram3_2=%d ngram4=%d", 
  CastSizeToInt(suffices.size()), CastSizeToInt(words.size()), 
  CastSizeToInt(ngram2.size()), CastSizeToInt(ngram2_1.size()),
  CastSizeToInt(ngram3.size()), CastSizeToInt(ngram3_1.size()), CastSizeToInt(ngram3_2.size()),
  CastSizeToInt(ngram4.size()) );

 return;
}


#endif
