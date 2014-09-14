// CD->07.03.2009
// LC->07.03.2009

#ifndef SOL_PREFIX_TREE__H
#define SOL_PREFIX_TREE__H
#pragma once

 #include <lem/noncopyable.h>
 #include <lem/containers.h>
 #include <map>

 namespace Solarix
 {
  class SG_Entry;

  struct CharNode : public lem::NonCopyable
  {
   lem::MCollect<const Solarix::SG_Entry*> entries; // на какие статьи приводит

   std::map< wchar_t, CharNode* > leafs;

   CharNode(void) {}

   ~CharNode(void);

   CharNode* find( wchar_t c, bool add );

   const CharNode* probe( wchar_t c ) const;

   bool match( const lem::UCString &str ) const;

   int match_len( const wchar_t * str ) const;
  };

 }
#endif
