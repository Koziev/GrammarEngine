// -----------------------------------------------------------------------------
// File SG_NET_LINK.CPP
//
// (c) Koziev Elijah
//
// Content:
// Класс SG_NetLink - организация одной связки Грамматической Сети, является
// элементом контейнера в классе SG_Entry.
// -----------------------------------------------------------------------------
//
// CD->20.11.1996
// LC->18.11.2010
// --------------

#include <lem/oformatter.h>
#include <lem/macro_parser.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/ThesaurusTagDefs.h>
#include <lem/solarix/TagSets.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/Thesaurus.h>

using namespace lem;
using namespace Solarix;


#if defined SOL_LOADTXT && defined SOL_COMPILER
SG_NetLink::SG_NetLink(
                       Macro_Parser &txtfile,
                       SynGram &gram,
                       bool realy,
                       int EntryKey0
                      )
{ LoadTxt(txtfile,gram,realy,EntryKey0); }
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
/*********************************************************************************
 Загрузка описания связки из текстового файла Словаря. Если realy=false, то
 поиска именованных полей в Грамматике и запоминания индексов производится
 не будет, то есть произойдет фактически пропуск описания связки. Данный прием
 используется при двухпроходном чтении описания статей Синтаксической Грамматики,
 а это необходимо из-за возможных ссылок вперед на неописанные словарные статьи.

 Формат:
        <имя_связки>класс:имя_статьи{}

**********************************************************************************/
void SG_NetLink::LoadTxt(
                         Macro_Parser &txtfile,
                         SynGram &gram,
                         bool realy,
                         int EntryKey0
                        )
{
 entry_key0 = EntryKey0;

 link.LoadTxt(txtfile,gram);

 BSourceState s = txtfile.tellp();
  
 entry_key1 = sol_load_omonym(txtfile,gram,false);

 if( realy && entry_key1==UNKNOWN )
  {
 
   BSourceState s1 = txtfile.tellp();
/*
   // Это не ошибка, но напечатать предупреждение следует: статья,
   // на которую отсылает связка, не найдена.

   // Распечатаем имя ненайденной статьи
//   Print_Error( s, txtfile, true );
   gram.GetIO().merr().printf( "Warning: link to undeclared entry " );
   txtfile.seekp(s);

   while( !txtfile.eof() )
    {
     BethToken t = txtfile.read();
     if( t.GetToken()==B_OFIGPAREN )
      break;

     gram.GetIO().merr().printf( "%us", t.c_str() );
    }

   gram.GetIO().merr().eol();
*/

   // Продолжаем трансляцию
   txtfile.seekp(s1);
  }

 return;
}
#endif


#if defined SOL_SAVETXT
void SG_NetLink::SaveTxt( OFormatter &txtfile, SynGram &gram ) const
{
 txtfile << "  ";
 sol_print_class_entry(txtfile,gram,entry_key0);
 link.SaveTxt(txtfile,gram);
 sol_print_class_entry(txtfile,gram,entry_key1);
 txtfile<<sol_get_token(B_OFIGPAREN)<<sol_get_token(B_CFIGPAREN);
 SaveTagsTxt(txtfile,gram);

 txtfile<<"\n";
 return;
}
#endif


#if defined SOL_SAVETXT
void SG_NetLink::SaveTagsTxt( OFormatter &txtfile, SynGram &gram ) const
{
 if( tags!=0 )
  {
   txtfile.printf( " tags { " );

   SG_TagsList tags_ptr = gram.Get_Net().tag_sets->operator [](tags);

   for( lem::Container::size_type i=0; i<tags_ptr->size(); ++i )
    {
     const int itag = (*tags_ptr)[i].first;
     const int ival = (*tags_ptr)[i].second;

     const ThesaurusTag &tag = gram.Get_Net().GetTagDefs()[itag];

     txtfile.printf( " \"%us\"", tag.GetName().c_str() );

     if( ival!=UNKNOWN )
      {
       const lem::UCString &val = tag[ival];
       txtfile.printf( "=\"%us\"", val.c_str() );        
      }

     txtfile.printf( " }" );     
    }
  }

 return;
}
#endif


void Solarix::PrintTags( SG_TagsList tags, lem::UFString &str, SynGram &sg )
{
 str.clear();

 if( tags!=NULL )
  {
   for( lem::Container::size_type i=0; i<tags->size(); ++i )
    {
     const int itag = (*tags)[i].first;
     const int ival = (*tags)[i].second;

     const ThesaurusTag &tag = sg.Get_Net().GetTagDefs()[itag];

     if( !str.empty() ) str += L' ';
     str += tag.GetName().c_str();

     if( ival!=UNKNOWN )
      {
       const lem::UCString &val = tag[ival];
       str += L'=';
       str += val.c_str();
      }
    }
  }

 return;
}


#if defined SOL_SAVETXT
void SG_NetLink::PrintTagsTxt( lem::UFString &res, SynGram &gram ) const
{
 if( tags!=0 )
  {
   SG_TagsList tags_ptr = (*gram.Get_Net().tag_sets)[tags];
   PrintTags( tags_ptr, res, gram );
  }

 return;
}
#endif

