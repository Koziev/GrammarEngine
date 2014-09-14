#if !defined SOL_NO_NGRAMS

#include <lem/conversions.h>
#include <lem/smart_pointers.h>
#include <lem/unicode.h>
#include <lem/oformatter.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/NGramHandler.h>
#include <lem/solarix/ngrams_dbms.h>

using namespace Solarix;
using namespace lem;

NGramsDBMS::~NGramsDBMS(void)
{}

void NGramsDBMS::LoadSegments( const lem::FString &suffix, lem::Collect<lem::FString> &segments )
{
 if( TableExists("NGRAM_SEGMENTS") )
  {
   lem::FString sql = lem::format_str("SELECT segment_n FROM NGRAM_SEGMENTS Where suffix='%s'", suffix.c_str() );
  
   lem::Collect<lem::FString> list;
   SelectFStrings(sql,list);

   for( lem::Container::size_type i=0; i<list.size(); ++i )
    {
     if( list[i].empty() )
      segments.push_back( list[i] );
     else
      segments.push_back( FString("_") + list[i] );
    }
  }

 if( segments.empty() )
  segments.push_back( lem::FString("") );

 return;
}


bool NGramsDBMS::GetStat(
                         int order, 
                         const lem::FString &suffix,
                         const lem::FString &segment,
                         float &min_w,
                         float &max_w,
                         lem::int64_t &n
                        )
{
 if( TableExists(lem::format_str("NGRAM_STATS%d%s%s", order, suffix.c_str(), segment.c_str() ) ) )
  {
   lem::FString sql( lem::format_str("SELECT max_w%d, count_n%d FROM NGRAM_STATS%d%s%s",
     order, order, order, suffix.c_str(), segment.c_str() ) );

   lem::Ptr<LS_ResultSet> rs( Select(sql) );
   if( rs->Fetch() )
    {
     const float _max_w = (float)rs->GetInt(0);
     const float _min_w = 0.F; 
     const int _n = rs->GetInt(1);

     max_w = max( max_w, _max_w );
     min_w = min( min_w, _min_w );
     n += _n;

     return true;
    }
  }

 return false;
}



void NGramsDBMS::FindLeftWords(
                               const lem::FString &suffix,
                               const lem::FString &segment,
                               int ie_right,
                               std::map< int, float > & reslist2,
                               int min_w,
                               int max_w,
                               int min_freq
                              )
{
 LEM_CHECKIT_Z( ie_right!=UNKNOWN );

 lem::FString sql( lem::format_str( "SELECT iword1, w FROM NGRAM2%s%s WHERE iword2=%d",
  suffix.c_str(), segment.c_str(), ie_right ) );

 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  {
   const int freq = rs->GetInt(1);
   if( freq>=min_freq )
    {
     const int ie1 = rs->GetInt(0);
     float w = max_w>0 ? (freq-min_w)/max_w : 0.0F;
     if( w<0.0F )
      w = 0.0F;

     std::map< int, float >::iterator it = reslist2.find(ie1);
     if( it==reslist2.end() )
      reslist2.insert( std::make_pair(ie1,w) );
     else
      it->second += w;
    }
  }

 return;
}



void NGramsDBMS::FindRightWords(
                               const lem::FString &suffix,
                               const lem::FString &segment,
                               int ie_left,
                               std::map< int, float > & reslist2,
                               int min_w,
                               int max_w,
                               int min_freq
                              )
{
 LEM_CHECKIT_Z( ie_left!=UNKNOWN );

 lem::FString sql( lem::format_str( "SELECT iword2, w FROM NGRAM2%s%s WHERE iword1=%d", suffix.c_str(), segment.c_str(), ie_left ) );

 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  {
   const int freq = rs->GetInt(1);
   if( freq>=min_freq )
    {
     const int ie2 = rs->GetInt(0);
     float w = max_w>0 ? (freq-min_w)/max_w : 0.0F;
     if( w<0.0F )
      w = 0.0F;

     std::map< int, float >::iterator it = reslist2.find(ie2);
     if( it==reslist2.end() )
      reslist2.insert( std::make_pair(ie2,w) );
     else
      it->second += w;
    }
  }

 return;
}



std::pair<int,int> NGramsDBMS::FindRawNGramsID(
                                               const lem::FString &suffix,
                                               const lem::FString &segment,
                                               const lem::UCString &left
                                              )
{
 FString sql = lem::format_str( "SELECT w, N.id"
                                " FROM NGRAM_WORDS%s%s wrd1, NGRAM1%s%s N"
                                " WHERE wrd1.word='%s'AND iword1=wrd1.id"
                                , suffix.c_str(), segment.c_str(), suffix.c_str(), segment.c_str()
                                , to_utf8(left.c_str()).c_str() );
 
 std::pair<int,int> r = SelectIntPair(sql);

 return r;
}


std::pair<int,int> NGramsDBMS::FindRawNGramsID(
                                               const lem::FString &suffix,
                                               const lem::FString &segment,
                                               const lem::UCString &left,
                                               const lem::UCString &right
                                              )
{
 FString sql = lem::format_str( "SELECT w, N.id"
                                " FROM NGRAM_WORDS%s%s wrd1, NGRAM_WORDS%s%s wrd2, NGRAM2%s%s N"
                                " WHERE wrd1.word='%s' AND wrd2.word='%s' AND iword1=wrd1.id AND iword2=wrd2.id"
                                , suffix.c_str(), segment.c_str()
                                , suffix.c_str(), segment.c_str()
                                , suffix.c_str(), segment.c_str()
                                , lem::to_utf8(left.c_str()).c_str(), to_utf8(right.c_str()).c_str() );
 
 std::pair<int,int> r = SelectIntPair(sql);

 return r;
}


std::pair<int,int> NGramsDBMS::FindRawNGramsID(
                                               const lem::FString &suffix,
                                               const lem::FString &segment,
                                               const lem::UCString &w1,
                                               const lem::UCString &w2,
                                               const lem::UCString &w3
                                              )
{
 FString sql = lem::format_str( "SELECT w, N.id"
                              " FROM NGRAM_WORDS%s%s wrd1, NGRAM_WORDS%s%s wrd2, NGRAM_WORDS%s%s wrd3, NGRAM3%s%s N"
                              " WHERE wrd1.word='%s' AND wrd2.word='%s' AND wrd3.word='%s' AND iword1=wrd1.id AND iword2=wrd2.id AND iword3=wrd3.id"
                              , suffix.c_str(), segment.c_str()
                              , suffix.c_str(), segment.c_str()
                              , suffix.c_str(), segment.c_str()
                              , suffix.c_str(), segment.c_str()
                              , to_utf8(w1.c_str()).c_str(), to_utf8(w2.c_str()).c_str(), to_utf8(w3.c_str()).c_str() );
 
 std::pair<int,int> r = SelectIntPair(sql);
 return r;
}


std::pair<int,int> NGramsDBMS::FindRawNGramsID(
                                               const lem::FString &suffix,
                                               const lem::FString &sgm,
                                               const lem::UCString &w1,
                                               const lem::UCString &w2,
                                               const lem::UCString &w3,
                                               const lem::UCString &w4
                                              )
{
 FString sql = lem::format_str( "SELECT w, N.id"
                              " FROM NGRAM_WORDS%s%s wrd1, NGRAM_WORDS%s%s wrd2, NGRAM_WORDS%s%s wrd3, NGRAM_WORDS%s%s wrd4, NGRAM4%s%s N"
                              " WHERE wrd1.word='%s' AND wrd2.word='%s' AND wrd3.word='%s' AND wrd4.word='%s' AND iword1=wrd1.id AND iword2=wrd2.id AND iword3=wrd3.id AND iword4=wrd4.id"
                              , suffix.c_str(), sgm.c_str()
                              , suffix.c_str(), sgm.c_str()
                              , suffix.c_str(), sgm.c_str()
                              , suffix.c_str(), sgm.c_str()
                              , suffix.c_str(), sgm.c_str()
                              , to_utf8(w1.c_str()).c_str(), to_utf8(w2.c_str()).c_str()
                              , to_utf8(w3.c_str()).c_str(), to_utf8(w4.c_str()).c_str() );
 
 std::pair<int,int> r = SelectIntPair(sql);
 return r;
}

std::pair<int,int> NGramsDBMS::FindRawNGramsID(
                                               const lem::FString &suffix,
                                               const lem::FString &sgm,
                                               const lem::UCString &w1,
                                               const lem::UCString &w2,
                                               const lem::UCString &w3,
                                               const lem::UCString &w4,
                                               const lem::UCString &w5
                                              )
{
 FString sql = lem::format_str( "SELECT w, N.id"
                              " FROM NGRAM_WORDS%s%s wrd1, NGRAM_WORDS%s%s wrd2, NGRAM_WORDS%s%s wrd3, NGRAM_WORDS%s%s wrd4, NGRAM_WORDS%s%s wrd5, NGRAM5%s%s N"
                              " WHERE wrd1.word='%s' AND wrd2.word='%s' AND wrd3.word='%s' AND wrd4.word='%s' AND wrd5.word='%s' AND iword1=wrd1.id AND iword2=wrd2.id AND iword3=wrd3.id AND iword4=wrd4.id AND iword5=wrd5.id"
                              , suffix.c_str(), sgm.c_str()
                              , suffix.c_str(), sgm.c_str()
                              , suffix.c_str(), sgm.c_str()
                              , suffix.c_str(), sgm.c_str()
                              , suffix.c_str(), sgm.c_str()
                              , suffix.c_str(), sgm.c_str()
                              , to_utf8(w1.c_str()).c_str(), to_utf8(w2.c_str()).c_str()
                              , to_utf8(w3.c_str()).c_str()
                              , to_utf8(w4.c_str()).c_str(), to_utf8(w5.c_str()).c_str() );

 std::pair<int,int> r = SelectIntPair(sql);
 return r;
}





int NGramsDBMS::FindWord( 
                         const lem::FString &suffix,
                         const lem::FString &sgm,
                         const lem::UCString &word
                        )
{ 
 FString sql = lem::format_str( "SELECT id FROM NGRAM_WORDS%s%s WHERE word='%s'"
                                 , suffix.c_str(), sgm.c_str(), to_utf8(word.c_str()).c_str()
                              );
 const int id = SelectInt( sql, -1 );
 return id;
}



lem::UCString NGramsDBMS::GetWord( const lem::FString &suffix, const lem::FString &segment, int id_word )
{
 FString sql = lem::format_str( "SELECT word FROM NGRAM_WORDS%s%s WHERE id=%d"
                                 , suffix.c_str(), segment.c_str(), id_word
                              );

 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 if( rs->Fetch() )
  {
   UCString w( rs->GetUCString(0) );
   return w;
  }
 else
  {
   LEM_STOPIT;
   return lem::UCString();
  }
}




int NGramsDBMS::FindWord( 
                         const lem::FString &suffix,
                         const lem::UCString &word
                        )
{ 
 FString sql = lem::format_str( "SELECT id FROM NGRAM_WORDS%s WHERE word='%s'", suffix.c_str(), to_utf8(word.c_str()).c_str() );
 int id = SelectInt(sql);
 return id;
}


void NGramsDBMS::InsertWord(
                            const lem::FString &suffix,
                            int id,
                            const lem::UCString &word
                           )
{
 FString an( to_utf8(word.c_str()) );
 FString sql = lem::format_str( "INSERT INTO NGRAM_WORDS%s( id, word ) VALUES ( %d, '%s' )", suffix.c_str(), id, an.c_str() );
 ExecuteSql(sql);
 return;
}



void NGramsDBMS::Find2GramsWithLeft( 
                                    const lem::FString &suffix,
                                    const lem::FString &segment,
                                    float max_w2,
                                    const lem::UCString &left,
                                    int min_freq,
                                    std::map< lem::UCString, float > & reslist
                                   )
{
 FString sql = lem::format_str( "SELECT wrd2.word, w"
                                " FROM NGRAM_WORDS%s%s wrd1, NGRAM2%s%s, NGRAM_WORDS%s%s wrd2"
                                " WHERE wrd1.word='%s' AND iword1=wrd1.id AND wrd2.id=iword2"
                                , suffix.c_str(), segment.c_str()
                                , suffix.c_str(), segment.c_str()
                                , suffix.c_str(), segment.c_str()
                                , to_utf8(left.c_str()).c_str() );

 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  {
   const int f = rs->GetInt(1);
   if( f>=min_freq )
    {  
     UCString cs( rs->GetUCString(0) );
     const float ff=float(f)/max_w2;

     std::map<UCString,float>::iterator it=reslist.find(cs);
     if( it==reslist.end() )
      reslist.insert( std::make_pair(cs,ff) );
     else
      it->second += ff;  
    }
  }

 return;
}




void NGramsDBMS::Find2GramsWithRight( 
                                     const lem::FString &suffix,
                                     const lem::FString &sgm,
                                     float max_w2,
                                     const lem::UCString &right,
                                     int min_freq,
                                     std::map< lem::UCString, float > & reslist
                                    )
{
 FString sql = lem::format_str(
                               "SELECT wrd2.word, w"
                               " FROM NGRAM_WORDS%s%s wrd1, NGRAM2%s%s, NGRAM_WORDS%s%s wrd2"
                               " WHERE wrd1.word='%s' AND iword2=wrd1.id AND wrd2.id=iword1"
                               , suffix.c_str(), sgm.c_str()
                               , suffix.c_str(), sgm.c_str()
                               , suffix.c_str(), sgm.c_str()
                               , to_utf8(right.c_str()).c_str() );

 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  {
   const int f = rs->GetInt(1);
   if( f>=min_freq )
    {  
     UCString cs( rs->GetUCString(0) );
     const float ff=float(f)/max_w2;

     std::map<UCString,float>::iterator it=reslist.find(cs);
     if( it==reslist.end() )
      reslist.insert( std::make_pair(cs,ff) );
     else
      it->second += ff;  
    }
  }

 return;
}



void NGramsDBMS::FindRaw3GramsWithLeft(
                                       const lem::FString &suffix,
                                       const lem::FString &sgm,
                                       float max_w3,
                                       const lem::UCString &left,
                                       int min_freq,
                                       std::map< std::pair<lem::UCString,lem::UCString>, float > & reslist
                                      )
{
 FString sql = lem::format_str(
                               "SELECT wrd2.word, wrd3.word, w"
                               " FROM NGRAM_WORDS%s%s wrd1, NGRAM3%s%s, NGRAM_WORDS%s%s wrd2, NGRAM_WORDS%s%s wrd3"
                               " WHERE wrd1.word='%s' AND iword1=wrd1.id AND wrd2.id=iword2 AND wrd3.id=iword3"
                               , suffix.c_str(), sgm.c_str()
                               , suffix.c_str(), sgm.c_str()
                               , suffix.c_str(), sgm.c_str()
                               , suffix.c_str(), sgm.c_str()
                               , to_utf8(left.c_str()).c_str() );
 
 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  { 
   const int f = rs->GetInt(2);
   if( f>=min_freq )
    {
     UCString cw1( rs->GetUCString(0) );
     UCString cw2( rs->GetUCString(1) );
     const float ff = float(f)/max_w3;

     std::map< std::pair<UCString,UCString>, float >::iterator it = reslist.find( std::make_pair(cw1,cw2) );
     if( it==reslist.end() )
      reslist.insert( std::make_pair( std::make_pair(cw1,cw2), ff ) );
     else
      it->second+=ff;
    }
  } 

 return;
}



void NGramsDBMS::FindRaw3GramsWithRight(
                                        const lem::FString &suffix,
                                        const lem::FString &sgm,
                                        float max_w3,
                                        const lem::UCString &right,
                                        int min_freq,
                                        std::map< std::pair<lem::UCString,lem::UCString>, float > & reslist
                                       )
{
 FString sql = lem::format_str(
                               "SELECT wrd2.word, wrd3.word, w"
                               " FROM NGRAM3%s%s, NGRAM_WORDS%s%s wrd1, NGRAM_WORDS%s%s wrd2, NGRAM_WORDS%s%s wrd3"
                               " WHERE wrd1.word='%s' AND iword3=wrd1.id AND wrd2.id=iword1 AND wrd3.id=iword2"
                               , suffix.c_str(), sgm.c_str()
                               , suffix.c_str(), sgm.c_str()
                               , suffix.c_str(), sgm.c_str()
                               , suffix.c_str(), sgm.c_str()
                               , to_utf8(right.c_str()).c_str() );
 
 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  { 
   const int f = rs->GetInt(2);
   if( f>=min_freq )
    {
     UCString cw2( rs->GetUCString(0) );
     UCString cw3( rs->GetUCString(1) );
     const float ff = float(f)/max_w3;

     std::map< std::pair<UCString,UCString>, float >::iterator it = reslist.find( std::make_pair(cw2,cw3) );
     if( it==reslist.end() )
      reslist.insert( std::make_pair( std::make_pair(cw2,cw3), ff ) );
     else
      it->second+=ff;
    }
  } 

 return;
}




void NGramsDBMS::FindRaw3GramsWithCenter(
                                         const lem::FString &suffix,
                                         const lem::FString &sgm,
                                         float max_w3,
                                         const lem::UCString &center,
                                         int min_freq,
                                         std::map< std::pair<lem::UCString,lem::UCString>, float > & reslist
                                        )
{
 FString sql = lem::format_str(
                               "SELECT wrd1.word, wrd3.word, w"
                               " FROM NGRAM3%s%s, NGRAM_WORDS%s%s wrd1, NGRAM_WORDS%s%s wrd2, NGRAM_WORDS%s%s wrd3"
                               " WHERE wrd2.word='%s' AND iword2=wrd2.id AND wrd1.id=iword1 AND wrd3.id=iword3"
                               , suffix.c_str(), sgm.c_str()
                               , suffix.c_str(), sgm.c_str()
                               , suffix.c_str(), sgm.c_str()
                               , suffix.c_str(), sgm.c_str()
                               , to_utf8(center.c_str()).c_str() );
 
 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  { 
   const int f = rs->GetInt(2);
   if( f>=min_freq )
    {
     UCString cw1( rs->GetUCString(0) );
     UCString cw3( rs->GetUCString(1) );
     const float ff = float(f)/max_w3;

     std::map< std::pair<UCString,UCString>, float >::iterator it = reslist.find( std::make_pair(cw1,cw3) );
     if( it==reslist.end() )
      reslist.insert( std::make_pair( std::make_pair(cw1,cw3), ff ) );
     else
      it->second+=ff;
    }
  } 

 return;
}



void NGramsDBMS::Find1Grams(
                            const lem::FString &suffix,
                            const lem::FString &sgm,
                            int max_w1,
                            int min_freq,
                            std::map< UCString, std::pair<int,float> > & reslist
                           )
{
 FString sql = lem::format_str( "SELECT wrd.word, w"
                                " FROM NGRAM1%s%s, NGRAM_WORDS%s%s WRD"
                                " WHERE iword1=wrd.id ORDER BY w DESC"
                                , suffix.c_str(), sgm.c_str(), suffix.c_str(), sgm.c_str() );
 
 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  {
   const int f = rs->GetInt(1);
   if( f>=min_freq )
    {
     UCString cs( rs->GetUCString(0) );
     const int ciw = f;
     const float cw = float(f)/max_w1;

     std::map<UCString,std::pair<int,float> >::iterator it=reslist.find(cs);
     if( it==reslist.end() )
      reslist.insert( std::make_pair( cs, std::make_pair(ciw,cw) ) );
    }
  } 

 return;
}



void NGramsDBMS::Dump2Grams_1(
                              const lem::FString &suffix,
                              const lem::FString &sgm,
                              lem::OFormatter &to
                             )
{
 FString sql = lem::format_str( "SELECT iword1, iword2, w FROM NGRAM2%s%s"
  , suffix.c_str(), sgm.c_str() );

 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  {
   const int ie1 = rs->GetInt(0);
   const int ie2 = rs->GetInt(1);
   const int w = rs->GetInt(2);
   to.printf( "%6d %6d [%d]\n", ie1, ie2, w );
  } 

 return;
}


void NGramsDBMS::Dump2Grams(
                            const lem::FString &suffix,
                            const lem::FString &sgm,
                            lem::OFormatter &to
                           )
{
 FString sql = lem::format_str( "SELECT w1.word, w2.word"
                                " FROM NGRAM2%s%s, NGRAM_WORDS%s%s w1, NGRAM_WORDS%s%s w2"
                                " WHERE w1.id=iword1 AND w2.id=iword2"
                                , suffix.c_str(), sgm.c_str()
                                , suffix.c_str(), sgm.c_str()
                                , suffix.c_str(), sgm.c_str()
                               );

 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  {
   UCString s1( rs->GetUCString(0) );
   UCString s2( rs->GetUCString(1) );
   to.printf( "%us %us\n", s1.c_str(), s2.c_str() );
  }

 return;
}


void NGramsDBMS::Dump3Grams(
                            const lem::FString &suffix,
                            const lem::FString &sgm,
                            lem::OFormatter &to
                           ) 
{
 FString sql = lem::format_str( 
  "SELECT w1.word, w2.word, w3.word, w"
  " FROM NGRAM3%s%s, NGRAM_WORDS%s%s w1, NGRAM_WORDS%s%s w2, NGRAM_WORDS%s%s w3" 
  " WHERE w1.id=iword1 AND w2.id=iword2 AND w3.id=iword3"
  , suffix.c_str(), sgm.c_str()
  , suffix.c_str(), sgm.c_str()
  , suffix.c_str(), sgm.c_str()
  , suffix.c_str(), sgm.c_str()
 );

 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  {
   UCString s1( rs->GetUCString(0) );
   UCString s2( rs->GetUCString(1) );
   UCString s3( rs->GetUCString(2) );
   const int w = rs->GetInt(3);
   to.printf( "%us %us %us [%d]\n", s1.c_str(), s2.c_str(), s3.c_str(), w );
  } 

 return;
}







void NGramsDBMS::ForEachRaw1(
                             Ngrams &ngrams,
                             const lem::FString &suffix,
                             const lem::FString &sgm,
                             NGramHandler *handler,
                             int sorting_type
                            )
{
 const char *sorting = "";
 switch(sorting_type)
 {
  case 1: sorting="ORDER BY id"; break;
  case 2: sorting="ORDER BY w"; break;
  case 3: sorting="ORDER BY w DESC"; break;
 }

 FString sql = lem::format_str( "SELECT NG.id, wrd.id, wrd.word, NG.w"
                                " FROM NGRAM1%s%s NG, NGRAM_WORDS%s%s wrd"
                                " WHERE iword1=wrd.id %s"
                                , suffix.c_str(), sgm.c_str(), suffix.c_str(), sgm.c_str(), sorting );
 
 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  {
   const int id_ngram = rs->GetInt(0);
   const int id_word1 = rs->GetInt(1);
   UCString word1( rs->GetUCString(2) );
   const int f = rs->GetInt(3);
   const int ciw = f;

   if( !handler->Do( ngrams, id_ngram, ciw, id_word1, word1 ) )
    break;
  } 

 return;
}



// Итерация по всем 2-граммам
void NGramsDBMS::ForEachRaw2(
                             Ngrams &ngrams,
                             const lem::FString &suffix,
                             const lem::FString &sgm,
                             NGramHandler *handler,
                             int sorting_type
                            )
{
 const char *sorting = "";
 switch(sorting_type)
 {
  case 1: sorting="ORDER BY id"; break;
  case 2: sorting="ORDER BY w"; break;
  case 3: sorting="ORDER BY w DESC"; break;
 }

 FString sql = lem::format_str( "SELECT NG.id, NG.iword1, NG.iword2, wrd1.word, wrd2.word, NG.w"
                                " FROM NGRAM2%s%s NG, NGRAM_WORDS%s%s wrd1, NGRAM_WORDS%s%s wrd2"
                                " WHERE wrd1.id=iword1 AND wrd2.id=iword2"
                                " %s"
                                , suffix.c_str(), sgm.c_str()
                                , suffix.c_str(), sgm.c_str()
                                , suffix.c_str(), sgm.c_str()
                                , sorting
                              );
 
 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  {
   const int id_ngram = rs->GetInt(0);
   const int id_word1 = rs->GetInt(1);
   const int id_word2 = rs->GetInt(2);
   UCString word1( rs->GetUCString(3) );
   UCString word2( rs->GetUCString(4) );
   const int f = rs->GetInt(5);
   const int ciw = f;

   if( !handler->Do( ngrams, id_ngram, ciw, id_word1, id_word2, word1, word2 ) )
    break;
  }

 return;
}



// Итератация по всем 3-граммам
void NGramsDBMS::ForEachRaw3(
                             Ngrams &ngrams,
                             const lem::FString &suffix,
                             const lem::FString &sgm,
                             NGramHandler *handler,
                             int sorting_type
                            )
{
 const char *sorting = "";
 switch(sorting_type)
 {
  case 1: sorting="ORDER BY id"; break;
  case 2: sorting="ORDER BY w"; break;
  case 3: sorting="ORDER BY w DESC"; break;
 }

 FString sql = lem::format_str( "SELECT NG.id, iword1, iword2, iword3, wrd1.word, wrd2.word, wrd3.word, NG.w"
                                " FROM NGRAM3%s%s NG, NGRAM_WORDS%s%s wrd1, NGRAM_WORDS%s%s wrd2, NGRAM_WORDS%s%s wrd3"
                                " WHERE wrd1.id=iword1 AND wrd2.id=iword2 AND wrd3.id=iword3"
                                " %s"
                                , suffix.c_str(), sgm.c_str()
                                , suffix.c_str(), sgm.c_str()
                                , suffix.c_str(), sgm.c_str()
                                , suffix.c_str(), sgm.c_str()
                                , sorting 
                              );
 
 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  {
   const int id_ngram = rs->GetInt(0);
   const int id_word1 = rs->GetInt(1);
   const int id_word2 = rs->GetInt(2);
   const int id_word3 = rs->GetInt(3);
   UCString word1( rs->GetUCString(4) );
   UCString word2( rs->GetUCString(5) );
   UCString word3( rs->GetUCString(6) );
   const int f = rs->GetInt(7);
   const int ciw = f;

   if( !handler->Do( ngrams, id_ngram, ciw, id_word1, id_word2, id_word3, word1, word2, word3 ) )
    break;
  }

 return;
}


// Итератация по всем 4-граммам
void NGramsDBMS::ForEachRaw4(
                             Ngrams &ngrams,
                             const lem::FString &suffix,
                             const lem::FString &sgm,
                             NGramHandler *handler,
                             int sorting_type
                            )
{
 const char *sorting = "";
 switch(sorting_type)
 {
  case 1: sorting="ORDER BY id"; break;
  case 2: sorting="ORDER BY w"; break;
  case 3: sorting="ORDER BY w DESC"; break;
 }

 FString sql = lem::format_str( "SELECT NG.id, iword1, iword2, iword3, iword4, wrd1.word, wrd2.word, wrd3.word, wrd4.word, NG.w"
                                " FROM NGRAM4%s%s NG, NGRAM_WORDS%s%s wrd1, NGRAM_WORDS%s%s wrd2, NGRAM_WORDS%s%s wrd3, NGRAM_WORDS%s%s wrd4"
                                " WHERE wrd1.id=iword1 AND wrd2.id=iword2 AND wrd3.id=iword3 AND wrd4.id=iword4"
                                " %s"
                                , suffix.c_str(), sgm.c_str()
                                , suffix.c_str(), sgm.c_str()
                                , suffix.c_str(), sgm.c_str()
                                , suffix.c_str(), sgm.c_str()
                                , suffix.c_str(), sgm.c_str()
                                , sorting
                              );
 
 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  {
   const int id_ngram = rs->GetInt(0);
   const int id_word1 = rs->GetInt(1);
   const int id_word2 = rs->GetInt(2);
   const int id_word3 = rs->GetInt(3);
   const int id_word4 = rs->GetInt(4);
   UCString word1( rs->GetUCString(5) );
   UCString word2( rs->GetUCString(6) );
   UCString word3( rs->GetUCString(7) );
   UCString word4( rs->GetUCString(8) );
   const int f = rs->GetInt(9);

   if( !handler->Do( ngrams, id_ngram, f, id_word1, id_word2, id_word3, id_word4, word1, word2, word3, word4 ) )
    break;
  }

 return;
}


// Итератация по всем 5-граммам
void NGramsDBMS::ForEachRaw5(
                             Ngrams &ngrams,
                             const lem::FString &suffix,
                             const lem::FString &sgm,
                             NGramHandler *handler,
                             int sorting_type
                            )
{
 const char *sorting = "";
 switch(sorting_type)
 {
  case 1: sorting="ORDER BY id"; break;
  case 2: sorting="ORDER BY w"; break;
  case 3: sorting="ORDER BY w DESC"; break;
 }
 
 FString sql = lem::format_str( "SELECT NG.id, iword1, iword2, iword3, iword4, iword5, wrd1.word, wrd2.word, wrd3.word, wrd4.word, wrd5.word, NG.w"
                                " FROM NGRAM5%s%s NG, NGRAM_WORDS%s%s wrd1, NGRAM_WORDS%s%s wrd2, NGRAM_WORDS%s%s wrd3, NGRAM_WORDS%s%s wrd4, NGRAM_WORDS%s%s wrd5"
                                " WHERE wrd1.id=iword1 AND wrd2.id=iword2 AND wrd3.id=iword3 AND wrd4.id=iword4 AND wrd5.id=iword5"
                                " %s"
                                , suffix.c_str(), sgm.c_str()
                                , suffix.c_str(), sgm.c_str()
                                , suffix.c_str(), sgm.c_str()
                                , suffix.c_str(), sgm.c_str()
                                , suffix.c_str(), sgm.c_str()
                                , suffix.c_str(), sgm.c_str()
                                , sorting
                              );
 
 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  {
   const int id_ngram = rs->GetInt(0);
   const int id_word1 = rs->GetInt(1);
   const int id_word2 = rs->GetInt(2);
   const int id_word3 = rs->GetInt(3);
   const int id_word4 = rs->GetInt(4);
   const int id_word5 = rs->GetInt(5);
   UCString word1( rs->GetUCString(6) );
   UCString word2( rs->GetUCString(7) );
   UCString word3( rs->GetUCString(8) );
   UCString word4( rs->GetUCString(9) );
   UCString word5( rs->GetUCString(10) );
   const int f = rs->GetInt(11);
   const int ciw = f;

   if( !handler->Do( ngrams, id_ngram, ciw, id_word1, id_word2, id_word3, id_word4, id_word5, word1, word2, word3, word4, word5 ) )
    break;
  }

 return;
}


lem::int64_t NGramsDBMS::SumFrequency(
                                      int order,
                                      const lem::FString &suffix,
                                      const lem::FString &sgm
                                     ) 
{
 FString sql = lem::format_str( "SELECT sum(w)"
                                " FROM NGRAM%d%s%s"
                                , order, suffix.c_str(), sgm.c_str()
                               );
 
 const int f = SelectInt(sql,0);
 return f;
}


std::pair<int/*max(id)*/,int/*count(*)*/> NGramsDBMS::GetMaxId( const lem::FString &suffix, int order )
{
 FString sql = lem::format_str( "SELECT Coalesce(max(id),0), count(*) FROM NGRAM%d%s", order, suffix.c_str() );
 std::pair<int,int> r = SelectIntPair(sql); 
 return r;
}


std::pair<int/*max(id)*/,int/*count(*)*/> NGramsDBMS::GetWordsMaxId( const lem::FString &suffix )
{
 FString sql = lem::format_str( "SELECT Coalesce(max(id),0), count(*) FROM NGRAM_WORDS%s", suffix.c_str() );
 std::pair<int,int> r = SelectIntPair(sql); 
 return r;
}

void NGramsDBMS::RegisterSegment( const lem::FString &segment_n, const lem::FString &suffix0 )
{
 if( SelectInt( lem::format_str("SELECT Count(*) FROM NGRAM_SEGMENTS WHERE segment_n='%s' AND suffix='%s'", segment_n.c_str(), suffix0.c_str() ), -1 )==0 )
  {
   ExecuteSql( lem::format_str("INSERT INTO NGRAM_SEGMENTS( segment_n, suffix ) VALUES ( '%s', '%s' )", segment_n.c_str(), suffix0.c_str() ) );
  }

 return;
}


std::pair<int/*id*/,int/*w*/> NGramsDBMS::Find1Gram( const lem::FString &suffix, int id_word )
{
 lem::FString sql( format_str( "SELECT id, w FROM NGRAM1%s WHERE iword1=%d", suffix.c_str(), id_word ) );
 return SelectIntPair(sql);
}


std::pair<int/*id*/,int/*w*/> NGramsDBMS::Find2Gram( const lem::FString &suffix, int id_word1, int id_word2 )
{
 lem::FString sql( format_str( "SELECT id, w FROM NGRAM2%s WHERE iword1=%d AND iword2=%d", suffix.c_str(), id_word1, id_word2 ) );
 return SelectIntPair(sql);
}

std::pair<int/*id*/,int/*w*/> NGramsDBMS::Find3Gram( const lem::FString &suffix, int id_word1, int id_word2, int id_word3 )
{
 lem::FString sql( format_str( "SELECT id, w FROM NGRAM3%s WHERE iword1=%d AND iword2=%d AND iword3=%d", suffix.c_str(), id_word1, id_word2, id_word3 ) );
 return SelectIntPair(sql);
}

std::pair<int/*id*/,int/*w*/> NGramsDBMS::Find4Gram( const lem::FString &suffix, int id_word1, int id_word2, int id_word3, int id_word4 )
{
 lem::FString sql( format_str( "SELECT id, w FROM NGRAM4%s WHERE iword1=%d AND iword2=%d AND iword3=%d AND iword4=%d", suffix.c_str(), id_word1, id_word2, id_word3, id_word4 ) );
 return SelectIntPair(sql);
}

std::pair<int/*id*/,int/*w*/> NGramsDBMS::Find5Gram( const lem::FString &suffix, int id_word1, int id_word2, int id_word3, int id_word4, int id_word5 )
{
 lem::FString sql( format_str( "SELECT id, w FROM NGRAM5%s WHERE iword1=%d AND iword2=%d AND iword3=%d AND iword4=%d AND iword5=%d", suffix.c_str(), id_word1, id_word2, id_word3, id_word4, id_word5 ) );
 return SelectIntPair(sql);
}




void NGramsDBMS::FinishBulkInsert( const lem::FString &sql )
{
 ExecuteSql(sql);
 return;
}


void NGramsDBMS::CreateIndeces2( const lem::FString &suffix, int order )
{
 for( int k=0; k<order; ++k )
  {
   if( !IndexExists( format_str( "ngrams_idx%d%d%s", order, 3+k, suffix.c_str() ),lem::format_str("NGRAM%d%s", order, suffix.c_str()) ) )
    {
     ExecuteSql( lem::format_str( "CREATE INDEX ngrams_idx%d%d%s ON NGRAM%d%s(iword%d)",
                  order, k+3, suffix.c_str(), order, suffix.c_str(), k+1 ) );
    }
  }

 return;
}

void NGramsDBMS::CreateIndecesWord2( const lem::FString &suffix )
{
 if( !IndexExists( format_str( "ngrams_idxw1%s", suffix.c_str() ),lem::format_str("NGRAM_WORDS%s", suffix.c_str()) ) )
  ExecuteSql( lem::format_str( "CREATE INDEX ngrams_idxw1%s ON NGRAM_WORDS%s(id)", suffix.c_str(), suffix.c_str() ) );
 return;
}





void NGramsDBMS::CreateIndeces1( const lem::FString &suffix, int order )
{
 if( order==1 )
  {
   const char* ci1[] = {
                        "ngrams_idx12%s", "CREATE UNIQUE INDEX ngrams_idx12%s ON NGRAM1%s(id)",
                        "ngrams_idx11%s", "CREATE UNIQUE INDEX ngrams_idx11%s ON NGRAM1%s(iword1)",
                        NULL
                       };

   int i=0;
   while( ci1[i]!=NULL )
    {
     if( !IndexExists( lem::format_str( ci1[i], suffix.c_str() ),lem::format_str("NGRAM1%s",suffix.c_str()) ) )
      {
       FString sql( lem::format_str( ci1[i+1], suffix.c_str(), suffix.c_str() ) );
       ExecuteSql(sql);
      }

     i+=2;
    }
  }
 else if( order==2 )
  {
   const char* ci2[] = {
                        "ngrams_idx21%s", "CREATE UNIQUE INDEX ngrams_idx21%s ON NGRAM2%s(id)",
                        "ngrams_idx22%s", "CREATE UNIQUE INDEX ngrams_idx22%s ON NGRAM2%s(iword1,iword2)",
                        NULL
                       };

   int i=0;
   while( ci2[i]!=NULL )
    {
     if( !IndexExists( lem::format_str( ci2[i], suffix.c_str() ),lem::format_str("NGRAM2%s",suffix.c_str()) ) )
      {
       FString sql( lem::format_str( ci2[i+1], suffix.c_str(), suffix.c_str() ) );
       ExecuteSql(sql);
      }

     i+=2;
    }
  }
 else if( order==3 )
  {
   const char* ci3[] = {
                        "ngrams_idx31%s", "CREATE UNIQUE INDEX ngrams_idx31%s ON NGRAM3%s(id)",
                        "ngrams_idx32%s", "CREATE UNIQUE INDEX ngrams_idx32%s ON NGRAM3%s(iword1,iword2,iword3)",
                        NULL
                       };

   int i=0;
   while( ci3[i]!=NULL )
    {
     if( !IndexExists( lem::format_str( ci3[i], suffix.c_str() ),lem::format_str("NGRAM3%s",suffix.c_str()) ) )
      {
       FString sql( lem::format_str( ci3[i+1], suffix.c_str(), suffix.c_str() ) );
       ExecuteSql(sql);
      }

     i+=2;
    }
  }
 else if( order==4 )
  {
   const char* ci4[] = {
                        "ngrams_idx41%s", "CREATE UNIQUE INDEX ngrams_idx41%s ON NGRAM4%s(id)",
                        "ngrams_idx42%s", "CREATE UNIQUE INDEX ngrams_idx42%s ON NGRAM4%s(iword1,iword2,iword3,iword4)",
                        NULL
                       };

   int i=0;
   while( ci4[i]!=NULL )
    {
     if( !IndexExists( lem::format_str( ci4[i], suffix.c_str() ),lem::format_str("NGRAM4%s",suffix.c_str()) ) )
      {
       FString sql( lem::format_str( ci4[i+1], suffix.c_str(), suffix.c_str() ) );
       ExecuteSql(sql);
      }

     i+=2;
    }
  }
 else if( order==5 )
  {
   const char* ci5[] = {
                        "ngrams_idx51%s", "CREATE UNIQUE INDEX ngrams_idx51%s ON NGRAM5%s(id)",
                        "ngrams_idx52%s", "CREATE UNIQUE INDEX ngrams_idx52%s ON NGRAM5%s(iword1,iword2,iword3,iword4,iword5)",
                        NULL
                       };

   int i=0;
   while( ci5[i]!=NULL )
    {
     if( !IndexExists( lem::format_str( ci5[i], suffix.c_str() ),lem::format_str("NGRAM5%s",suffix.c_str()) ) )
      {
       FString sql( lem::format_str( ci5[i+1], suffix.c_str(), suffix.c_str() ) );
       ExecuteSql(sql);
      }

     i+=2;
    }
  }

 return;
}




void NGramsDBMS::UpdateStatistics( const lem::FString &suffix, int order )
{
 ExecuteSql( lem::format_str( "DELETE FROM NGRAM_STATS%d%s", order, suffix.c_str() ).c_str() );
 std::pair<int,int> p1(0,0);
 p1 = SelectIntPair( lem::format_str( "SELECT Coalesce(max(w),0), count(*) FROM NGRAM%d%s", order, suffix.c_str() ).c_str() );
 FString sql = format_str(
         "INSERT INTO NGRAM_STATS%d%s( max_w%d, count_n%d ) VALUES ( %d, %d )",
         order, suffix.c_str(), order, order, p1.first, p1.second
        );

 ExecuteSql( sql );

 return;
}


void NGramsDBMS::EraseFreq1( const lem::FString &suffix, int order )
{
 FString sql = format_str( "DELETE FROM NGRAM%d%s WHERE w=1", order, suffix.c_str() );
 ExecuteSql(sql);
 return;
}

void NGramsDBMS::CleanTables( const lem::FString &suffix, int order )
{
 ExecuteSql( format_str( "DELETE FROM NGRAM%d%s", order, suffix.c_str() ) );
 ExecuteSql( format_str( "DELETE FROM NGRAM_STATS%d%s", order, suffix.c_str() ) );
 return;
}

void NGramsDBMS::CleanWordsTable( const lem::FString &suffix )
{
 ExecuteSql( format_str( "DELETE FROM NGRAM_WORDS%s", suffix.c_str() ) );
 return;
}

#endif
