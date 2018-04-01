// File SOLARIX_BINARIZATION_OPTIONS.H
//
// CD->10.07.2005
// LC->30.03.2018

#ifndef SOL_BIN_OPTIONS__H
#define SOL_BIN_OPTIONS__H
#pragma once

#include <set>
#include <lem/ptr_container.h>
#include <lem/regex.h> 

 namespace Solarix
 {
  struct Binarization_Options
  {
   lem::uint32_t parsing;   // Compilation (parsing) options

   bool allow_links;  // Store semantic net links in binary dictionary file (option -nolinks)
   bool allow_sounds; // Store sounde records in binary dictionary file (option -nosounds)
   lem::zbool produce_cpp_rules; // генерировать C++ код для исполнения итераторов и продукционных правил
   lem::zbool recompile_syntax; // перекомпиляция только синтаксических правил
   bool reverse_links; // автоматически генерировать обратные связи тезауруса
   lem::zbool entry_redefinition; // разрешать ли повторное определение словарных статей (игнорировать второе определение)
   lem::zbool lexicon_merging; // происходить объединение лексиконов, поэтому синтаксические правила из базового словаря не изменяются.

   std::set<lem::UCString> allowed_enames;
   lem::PtrCollect<lem::UFString> allowed_emasks;

   Binarization_Options(void)
   {
    parsing = 0;
    allow_links=true;
    allow_sounds=false;
    reverse_links=true;
   }

   bool CheckEntryName( const lem::UCString &x ) const
   {
    if( allowed_enames.empty() && allowed_emasks.empty() )
     return true;

    lem::UCString ename(x);
    ename.to_upper();
    if( allowed_enames.find(ename)!=allowed_enames.end() )
     return true;
     
    for( lem::Container::size_type i=0; i<allowed_emasks.size(); ++i )
     if( lem::regex_does_match( allowed_emasks[i]->c_str(), x.c_str() ) )
      return true;

    return false;
   }
  };

 } // namespace Solarix

#endif
