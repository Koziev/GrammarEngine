#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntries_File.h>
#include <lem/solarix/WordFormEnumerator_File.h>

using namespace Solarix;


WordFormEnumeratorGlobbing_File::WordFormEnumeratorGlobbing_File(
                                                                 WordEntries_File * _entries,
                                                                 const lem::UFString &_mask
                                                                )
 : WordFormEnumeratorListing_File(_entries), mask(_mask)
{
 LEM_CHECKIT_Z( !_mask.empty() );
 return;
}


void WordFormEnumeratorGlobbing_File::Prefetch(void)
{
 const Solarix::LexemDictionary &lex0 = entries->ml_ref;
 const MCollect<Solarix::Lexem> &lex = lex0.get_list();

 std::set<const Solarix::Lexem*> ptr_lex;
 for( lem::Container::size_type i=0; i<lex.size(); ++i )
  {
   if( lem::regex_match( mask.c_str(), lex[i].c_str() ) )
    {
     ptr_lex.insert( &lex[i] );
    }
  }

 const int ne = entries->size();
 for( int i=ne-1; i>=0; --i )
  {
   const Solarix::SG_Entry &e = entries->GetWordEntry(i);

   for( lem::Container::size_type j=0; j<e.forms().size(); ++j )
    {
     const SG_EntryForm &f = e.forms()[j];
     const Solarix::Lexem *ptr = &f.name();

     std::set<const Solarix::Lexem*>::const_iterator it=ptr_lex.find(ptr);
     if( it!=ptr_lex.end() )
      {
       WordFormEnumeratorListing_File::Hit h;
       h.ekey = e.GetKey();
       h.iform = CastSizeToInt(j);
       h.val = 1.0F;
       hits.push_back( h );
      }
    }
  }

 // Отсортируем его так, чтобы сначала шли самые достоверные
 std::stable_sort( hits.begin(), hits.end(), WordFormEnumeratorListing_File::HitsComparator );

 return;
}
