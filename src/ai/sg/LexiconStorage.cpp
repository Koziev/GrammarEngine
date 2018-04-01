#include <lem/conversions.h>
#include <lem/solarix/coord_pair.h>
#include <lem/solarix/LexiconStorage.h>

using namespace Solarix;

wchar_t LexiconStorage::CollocationDelimiter = L'\x1F';
wchar_t LexiconStorage::WORD_SET_DELIMITER = L'\x1F';


// Слова из списка words объединяем в одну строку таким образом, чтобы их можно было сохранить в БД, и
// потом снова разбить на слова.
void LexiconStorage::MergeCollocationWords( const lem::MCollect<lem::UCString> &words, lem::UFString &collocation )
{
 LEM_CHECKIT_Z( !words.empty() );

 collocation.clear();
 collocation += words.front().c_str();

 for( lem::Container::size_type i=1; i<words.size(); ++i )
  {
   collocation += CollocationDelimiter;
   collocation += words[i].c_str();
  }

 LEM_CHECKIT_Z( !collocation.empty() );

 return;
}


void LexiconStorage::SplitCollocationWords( const lem::UFString &collocation, lem::MCollect<lem::UCString> &words )
{
 LEM_CHECKIT_Z( !collocation.empty() );

 words.clear();
 lem::Collect<lem::UFString> w;
 const wchar_t delimiter[2] = { CollocationDelimiter, 0 };
 lem::parse( collocation, w, delimiter, false );
 for( lem::Container::size_type i=0; i<w.size(); ++i )
  words.push_back( lem::UCString( w[i].c_str() ) );

 LEM_CHECKIT_Z( !words.empty() );

 return;
}


namespace
{
 static bool cpa_sorter( const Solarix::GramCoordPair &a, const Solarix::GramCoordPair &b )
 { return a.GetCoord().GetIndex() > b.GetCoord().GetIndex(); }
}

void LexiconStorage::SortCoords( CP_Array & sorted_coords ) const
{
 std::sort( sorted_coords.begin(), sorted_coords.end(), cpa_sorter );
}


void LexiconStorage::SerializeCoords( const Solarix::CP_Array & sorted_coords, lem::FString & str_coords )
{
 for( lem::Container::size_type i=0; i<sorted_coords.size(); ++i )
  {
   str_coords += ' ';
   str_coords += lem::to_str( sorted_coords[i].GetCoord().GetIndex() ).c_str();
   str_coords += ':';
   str_coords += lem::to_str( sorted_coords[i].GetState() ).c_str();
  }

 str_coords += ' ';

 return;
}





