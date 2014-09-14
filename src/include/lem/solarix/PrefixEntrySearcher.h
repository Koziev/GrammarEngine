#ifndef SOL_PREFIX_SEARCHER__H
#define SOL_PREFIX_SEARCHER__H
#pragma once

// CD->12.11.2009
// LC->24.06.2012

#include <lem/ucstring.h>
#include <lem/noncopyable.h> 
#include <lem/ptr_container.h> 
#include <map>

namespace Solarix
{
 class SG_Entry;
 class SynGram;

 class Charpos2EntryStorage;
 class PrefixEntrySearcher : lem::NonCopyable
 {
  private:
   Charpos2EntryStorage *storage;

   lem::uint32_t CharPos2Int( lem::uint32_t ucs4, int pos ) const
   {
    LEM_CHECKIT_Z( (ucs4&0xff000000)==0 );
    return (pos<<24) | ucs4;
   }

   lem::PtrCollect< std::set<int> > keys;
   std::map< lem::uint32_t, std::set<int>* > charpos2keys;

   void Add( const lem::UCString &prefix, int ie );

   int max_ie_count;
   
  public:
   PrefixEntrySearcher( Charpos2EntryStorage *_storage, int max_ies );
   ~PrefixEntrySearcher(void);

   void AddEntry( int ie, const Solarix::SG_Entry &e );
   void Commit(void);

   int FindMaxPrefixLen( const wchar_t * text ) const;

   void Search( const wchar_t *prefix, lem::MCollect<int> &ies ) const;
   void PreciseSearch( const wchar_t *prefix, Solarix::SynGram &sg, lem::MCollect<int> &ies ) const;

   void GetEntriesForCharPos( int ipos, lem::uint32_t ucs4, std::set<int> &result );

   void Save_SQL( const lem::Path &filename, const SQL_Production &sql_version );
 };

} // namespace Solarix 

#endif
