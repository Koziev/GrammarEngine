// -----------------------------------------------------------------------------
// File LEXICAL_CAST.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2005
//
// Content:
//
// -----------------------------------------------------------------------------
//
// CD->25.10.2005
// LC->13.08.2006
// --------------

#ifndef LEM_LEXICAL_CAST__H
#define LEM_LEXICAL_CAST__H
#pragma once

 #include <boost/lexical_cast.hpp>

 #include <lem/cstring.h>
 #include <lem/fstring.h>


  // Для использования lexical_cast<...> из библиотеки BOOST требуется
  // этот оператор.
  template < class charT, class traits, class Allocator, int LEN >
  inline std::basic_stringstream<charT,traits,Allocator>&
   operator << (
                std::basic_stringstream<charT,traits,Allocator>& stream,
                const lem::BaseCString<charT,LEN>& str
               )
  {
   stream << str.c_str();
   return stream;
  }

  template < class charT, class traits, class Allocator, int LEN >
  inline std::basic_stringstream<charT,traits,Allocator>&
   operator >> (
                std::basic_stringstream<charT,traits,Allocator>& stream,
                lem::BaseCString<charT,LEN>& str
               )
  {
   std::basic_string<charT> buf;
   stream >> buf;
   str = buf.c_str();
   return stream;
  }


  // Для использования lexical_cast<...> из библиотеки BOOST требуется
  // этот оператор.
  template < class charT, class traits, class Allocator >
  inline std::basic_stringstream<charT,traits,Allocator>&
   operator << (
                std::basic_stringstream<charT,traits,Allocator>& stream,
                const lem::BaseFString<charT>& str
               )
  {
   stream << str.c_str();
   return stream;
  }

  template < class charT, class traits, class Allocator >
  inline std::basic_stringstream<charT,traits,Allocator>&
   operator >> (
                std::basic_stringstream<charT,traits,Allocator>& stream,
                lem::BaseFString<charT>& str
               )
  {
   std::basic_string<charT> buf;
   stream >> buf;
   str = buf.c_str();
   return stream;
  }


  #if !defined LEM_WATCOM
  template < class CHAR >
  inline std::istream& operator >> ( std::istream& stream, lem::BaseFString<CHAR> &dst )
  {
   std::string buffer("");

   stream >> buffer;
   dst = buffer.c_str();

   return stream;
  }
  #endif 


#endif
