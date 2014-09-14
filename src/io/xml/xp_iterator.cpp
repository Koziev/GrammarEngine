// -----------------------------------------------------------------------------
// File XP_ITERATOR.CPP
//
// (c) 2005 by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// Классы Iterator и ConstIterator - удобный перебор узлов
//
// 24.08.2007 - первая реализация ConstIterator
// -----------------------------------------------------------------------------
//
// CD->24.08.2007
// LC->24.08.2007
// --------------

#include <lem/config.h>
#include <lem/xml_parser.h>

using namespace std;
using namespace lem;
using namespace lem::Xml;

Iterator::Iterator( Node *Root, const UFString &Name ) : name(Name)
{
 LEM_CHECKIT_Z(Root!=NULL);
 LEM_CHECKIT_Z(!Name.empty());

 root=Root;
 icur=UNKNOWN;

 for( Container::size_type i=0; i<root->GetNodes().size(); i++ )
  if( root->GetNodes()[i]->GetName() == Name )
   {
    icur=i;
    break;
   }

 return;
}


// **********************************************************
// Передвигаемся на следующий элемент с заданным именем.
// **********************************************************
Iterator& Iterator::operator++(void)
{
 if( icur!=UNKNOWN )
  {
   bool found=false;
   for( Container::size_type i=icur+1; i<root->GetNodes().size(); i++ )
    if( root->GetNodes()[i]->GetName() == name )
     {
      icur=i;
      found=true;
      break;
     }

   if( !found )
    icur=UNKNOWN;
  }

 return *this;
}

Iterator& Iterator::operator++(int)
{
 return operator++();
}





ConstIterator::ConstIterator( const Node *Root, const UFString &Name ) : name(Name)
{
 LEM_CHECKIT_Z(Root!=NULL);
 LEM_CHECKIT_Z(!Name.empty());

 root=Root;
 icur=UNKNOWN;

 for( Container::size_type i=0; i<root->GetNodes().size(); i++ )
  if( root->GetNodes()[i]->GetName() == Name )
   {
    icur=i;
    break;
   }

 return;
}


ConstIterator& ConstIterator::operator++(void)
{
 if( icur!=UNKNOWN )
  {
   bool found=false;
   for( Container::size_type i=icur+1; i<root->GetNodes().size(); i++ )
    if( root->GetNodes()[i]->GetName() == name )
     {
      icur=i;
      found=true;
      break;
     }

   if( !found )
    icur=UNKNOWN;
  }

 return *this;
}

ConstIterator& ConstIterator::operator++(int)
{
 return operator++();
}
