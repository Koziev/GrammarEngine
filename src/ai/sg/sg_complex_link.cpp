// -----------------------------------------------------------------------------
// File SG_COMPLEX_LINK.CPP
//
// (c) Koziev Elijah
//
// Content:
// Класс SG_ComplexLink - сложная связка в тезаурусе
//
// 06.12.2007 - архитектура сложных связок полностью переделана.
// 27.11.2009 - добавлена поддержка длинных токенов через BethToken::GetFullStr
// -----------------------------------------------------------------------------
//
// CD->22.09.2006
// LC->19.11.2010
// --------------

#include <lem/oformatter.h>
#include <lem/macro_parser.h>

#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/SG_ComplexLink.h>

using namespace lem;
using namespace Solarix;

SG_ComplexLink::SG_ComplexLink(void)
{
 tl_id=UNKNOWN;
 tags=NULL;
 return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER

void SG_ComplexLink::LoadPoint( Macro_Parser &txtfile, SynGram &gram, lem::UFString &entry )
{
 BethToken t = txtfile.read();

 if( t.GetToken()==B_ENTRY )
  {
   // Особый формат entry Класс:Статья { уточнение }
   // преобразуется в ключ статьи и возвращается в виде #ключ
   UCString class0 = txtfile.read().string();
   const int ic0 = class0==L"?" ? ANY_STATE : gram.FindClass(class0);
   if( ic0==UNKNOWN ) 
    {
     Print_Error( txtfile );
     gram.GetIO().merr().printf( "Unknown class %us\n", class0.c_str() );
     throw E_BaseException();
    }

   txtfile.read_it( B_COLON );
   UCString entry0 = sol_read_multyname( gram.GetIO(), txtfile, B_OFIGPAREN );
   entry0.strip(L'"');
   entry0.trim();

   // Может быть задана дополнительная фильтрующая координата
   Solarix::CP_Array coords0;
   coords0.LoadTxt( txtfile, gram );
   
   if( gram.IsOmonym(ic0,lem::to_upper(entry0)) && coords0.empty() )
    {
     Print_Error( txtfile );
     gram.GetIO().merr().printf( "Omonym %us:%us requires the coordinate array\n", class0.c_str(), entry0.c_str() );
     throw E_BaseException();
    }

   const int ie0 = coords0.empty() ? gram.FindEntry(entry0,ic0,false) : gram.FindEntryOmonym(entry0,ic0,coords0);
   if( ie0==UNKNOWN ) 
    {
     Print_Error( txtfile );
     gram.GetIO().merr().printf( "Unknown entry %us:%us\n", class0.c_str(), entry0.c_str() );
     throw E_BaseException();
    }

   const int ekey = gram.GetEntry(ie0).GetKey();
   entry = lem::format_str( L"#%d", ekey );

   return;
  }

 bool figparen = t.GetToken()==B_OFIGPAREN;

 if( !figparen )
  txtfile.seekp(t);
 
 entry.reserve(128);

 if( t.string()==L'@' )
  {
   entry = L'@';
   t = txtfile.read();
  }

 while( !txtfile.eof() )
  {
   BethToken t = txtfile.read();
   if( figparen && t.GetToken()==B_CFIGPAREN )
    break;
   
   if( !entry.empty() )
    entry += L' ';

   UFString ts( t.GetFullStr() );
   ts.strip(L'"');
   entry += ts;

   if( !figparen )
    break;
  }

 if( entry.front()==L'@' )
  {
   // Спецсимвол @ заставляет запомнить строку в виде "как есть"
   entry.remove(0);
   entry.trim();
  }
 else
  {
   entry.strip(L'"');
   gram.GetDict().GetLexAuto().TranslateLexem(entry,true);
  }

 return;
}




void SG_ComplexLink::LoadTxt( Macro_Parser &txtfile, SynGram &gram )
{
 LoadPoint(txtfile,gram,entry1); 
 link.LoadTxt(txtfile,gram);
 LoadPoint(txtfile,gram,entry2); 
 return;
}



bool SG_ComplexLink::operator<( const SG_ComplexLink &x ) const
{
 if( entry1 < x.entry1 )
  return true;

 if( entry1 > x.entry1 )
  return false;
 
 return entry2 < x.entry2;
}
#endif
