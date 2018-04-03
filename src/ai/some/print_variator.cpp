// CD->26.10.2009
// LC->27.06.2012

#include <lem/oformatter.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/print_variator.h>
#include <lem/solarix/casing_coder.h>

using namespace lem;
using namespace Solarix;

void Solarix::print_morphology(
                               const lem::UFString & str,
                               const Solarix::Res_Pack & pack,
                               const Solarix::Dictionary & dict,
                               OFormatter & out_file,
                               bool html
                              )
{
 if( html )
  {
   out_file.printf( "<p>" );
  }

 // Выведем результаты морфологического анализа.
 if( pack.vars().empty() )
  {
   if( html )
    {
     out_file.printf( "<p><span style=\"color: #FF0000;\"><span style=\"background-color: #FFFF99\">%us</span></span></p>\n", str.c_str() );
    }
   else
    {
     out_file.printf( "%vfCMorphology analyzer error:%vn %us\n", str.c_str() );
    }
  }
 else
  {
   const int iunknown_class = dict.GetSynGram().FindClass( L"UnknownEntries" );

   for( lem::Container::size_type v=0; v<pack.vars().size(); ++v )
    {
     const Variator &var = * pack.vars()[v];
     for( int i=1; i<var.size()-1; ++i )
      {
       const Tree_Node &node = *var[i];
   
       const UCString &wrd = * node.GetNode().GetName();
   
       bool is_unknown=false;
       bool many_classes=false;
   
       const int nalt = 1 + CastSizeToInt(node.GetNode().GetAlts().size());
       const int ekey0 = node.GetNode().GetEntryKey();
       if( !lem::is_quantor(ekey0) )
        {
         const SG_Entry &e0 = dict.GetSynGram().GetEntry(ekey0);
         const int iclass0 = e0.GetClass();
         if( iclass0==iunknown_class )
          is_unknown = true; 
         else
          {  
           // Посмотрим, сколько грамматических классов среди вариантов.
           for( int i=1; i<nalt; ++i )
            {
             const int ekeyi = node.GetNode().GetAlts()[i-1]->GetEntryKey();
             const SG_Entry &ei = dict.GetSynGram().GetEntry(ekeyi);
             const int iclassi = ei.GetClass();
             if( iclass0!=iclassi )
              {
               many_classes=true;
               break;
              }  
            } 
          }
        }
   
   
       // Сначала напечатаем слово.
   
       if( html )
        { 
         if( i>1 )
          out_file.printf( ' ' );
   
         if( is_unknown )
          out_file.printf( "<span style=\"color: #FF0000;\"><span style=\"background-color: #FFCCCC\">%us</span></span>", wrd.c_str() );
         else if( many_classes )
          out_file.printf( "<span style=\"color: #FF0000;\">%us</span>", wrd.c_str() );
         else    
          out_file.printf( "%us", wrd.c_str() );
        }
       else 
        {
         if( i>1 )
          out_file.printf( ' ' );
   
         if( is_unknown )
          out_file.printf( "%vfC%us%vn", wrd.c_str() );
         else if( many_classes )
          out_file.printf( "%vfB%us%vn", wrd.c_str() );
         else
          out_file.printf( "%vfE%us%vn", wrd.c_str() );
        }   
   
       if( !lem::is_udelim(wrd) && wrd!=L"\"" )
        {
         // Теперь выведем список альтернативных грамматических классов для этой словоформы
         lem::MCollect<int> printed;
   
         // число альтернатив для слова
         if( nalt>1 )
          {
           // если все альтернативы - одна и та же словарная статья, то используем один цвет,
           // а если разные - то надо выделить поярче.
           lem::MCollect<int> partsofspeech;
           if( !lem::is_quantor(ekey0) )
            {
             const SG_Entry &e0 = dict.GetSynGram().GetEntry(ekey0);
             const int iclass0 = e0.GetClass();
             partsofspeech.push_back(iclass0);
            }
          
           for( lem::Container::size_type t=0; t<node.GetNode().GetAlts().size(); ++t )
            {
             const int ekey1 = node.GetNode().GetAlts()[t]->GetEntryKey();
             if( !lem::is_quantor(ekey1) )
              {
               const SG_Entry &e1 = dict.GetSynGram().GetEntry(ekey1);
               const int iclass1 = e1.GetClass();
               if( partsofspeech.find(iclass1)==UNKNOWN )
                partsofspeech.push_back(iclass1);
              }
            } 
   
           if( html ) 
            {
             // Если есть альтернативы (nalt>1), то верхним индексов выводим их число.
             if( partsofspeech.size()>1 )
              {
               out_file.printf( "<small><sup><b><span style=\"color: #FF0000;\"><span style=\"background-color: #CCCCFF\">%d</span></span></b></sup></small>", nalt );
              }
             else
              {  
               out_file.printf( "<small><sup><span style=\"color: #3333FF;\"><span style=\"background-color: #CCCCFF\">%d</span></span></sup></small>", nalt );
              }
            }
           else
            {
             out_file.printf( " %vf3%d%vn", nalt );
            }
          }
   
         for( int i=0; i<nalt; ++i )
          {
           const Word_Form & wf = i==0 ? node.GetNode() : *node.GetNode().GetAlts()[i-1];
   
           const int ekey = wf.GetEntryKey();
           if( !lem::is_quantor(ekey) )
            {
             const SG_Entry &e = dict.GetSynGram().GetEntry(ekey);
             const int iclass = e.GetClass();
             if( printed.find(iclass)==UNKNOWN && !lem::is_quantor(iclass) && iclass!=iunknown_class )
              {
               printed.push_back(iclass);
               const SG_Class &cls = dict.GetSynGram().GetClass(iclass);
               if( i>0 )
                {
                 if( html )
                  {
                   out_file.printf( ' ' );
                  }
                }
   
               if( html )
                out_file.printf( "<small><sub><span style=\"color: rgb(153, 153, 153);\">" );
   
               if( !html )
                out_file.printf( ' ' );
   
               out_file.printf( "%vf6%us%vn", to_lower(cls.GetName()).c_str() );
   
               if( html )
                out_file.printf( "</small></sub></span>" );
              } 
            } 
          }  
        }
      }     
   
     if( html )
      out_file.printf( "</p>\n" );
     else
      out_file.eol();
    }
  }

 out_file.flush();

 return;
}



namespace
{
 struct NodePrintBlock : lem::NonCopyable
 {
  UFString empty_line;
  lem::Collect<UFString> lines;  

  lem::MCollect<NodePrintBlock*> child;
  int w, h;

  void PrintAttributes( OFormatter & out, Solarix::SynGram & sg, const Solarix::Word_Form & word ) const;

  NodePrintBlock( const Tree_Node & node, SynGram & sg, bool html, bool detailed );
  ~NodePrintBlock();

  void PushLine( const UFString & s );

  const UFString& GetLine( int iline ) const;
 };




 NodePrintBlock::NodePrintBlock( const Tree_Node & node, SynGram & sg, bool html, bool detailed )
 {
  w=h=0;
  lines.reserve(32);

  lem::Char_Stream::UTF16_MemWriter mem; 
  OUFormatter mf( &mem, false );

  // Первая строка - узловое слово
  node.GetNode().PrintPlain( mf, false );
  if( detailed )
   PrintAttributes( mf, sg, node.GetNode() );

  const UFString & line0 = mem.string();
  PushLine(line0);
  mem.clear();

  const int nleaf = CastSizeToInt(node.leafs().size());

  // Теперь дадим каждому узлу построить свой блок отображения
  for( lem::Container::size_type i=0; i<node.leafs().size(); ++i )
   {
    NodePrintBlock *nb = new NodePrintBlock( node.leafs()[i], sg, html, detailed );
    child.push_back(nb);
   }

  // Начинаем распечатку узлов с соединительными линиями к корню
  for( int i=nleaf-1; i>=0; --i )
   {
    // Разделительная строка содержит вертикальные штрихи - по числу оставшихся веток
    UFString hstrokes;

    if( html )
     hstrokes += L"<span style=\"color: rgb(153, 153, 153);\">";

    hstrokes += UFString( i+1, 0x2502 );
    if( i<(nleaf-1) )
     {
      UFString s( nleaf-1-i, L' ' );
      hstrokes += s;
     }

    hstrokes += L' ';

    if( html )
     hstrokes += L"</span>";

    PushLine(hstrokes);

    const NodePrintBlock &nb = *child[i];
    const int block_lines = nb.h;

    for( int iline=0; iline<block_lines; ++iline )
     {
      UFString str_prefix;

      if( html )
       str_prefix += L"<span style=\"color: rgb(153, 153, 153);\">";
    
      if( iline==0 )
       {
        // Первая строка для блока содержит ответвление вправо для крайне правой линии.
        const int n_down = i;
        str_prefix += UFString( n_down, 0x2502 );
        str_prefix += 0x2514;
        const int n_hor = 1 + (nleaf-1-i);
        str_prefix += UFString( n_hor, 0x2500 );
       }
      else
       {
        // остальные - только вертикальные линии слева и пробелы справа
        const int n_down = i;
        str_prefix += UFString( n_down, 0x2502 );
        const int n_hor = 3 + (nleaf-1-i);
        str_prefix += UFString( n_hor, L' ' );
       }

      if( html )
       str_prefix += L"</span>";

      // Справа добавляем строку блока
      const UFString &block_line = nb.GetLine(iline);
      str_prefix += block_line;

      // Строка полностью готова
      PushLine(str_prefix);
     }
   }

  return;
 }


 void NodePrintBlock::PrintAttributes( OFormatter & out, Solarix::SynGram & sg, const Solarix::Word_Form & word ) const
 {
  out.printf( " (" );

  int id_entry = word.GetEntryKey();
  if( !lem::is_quantor(id_entry) )
   {
    out.printf( " %us", sg.GetClass( sg.GetEntry(id_entry).GetClass() ).GetName().c_str() );
   }

  for( lem::Container::size_type i=0; i<word.pairs().size(); ++i )
   {
    const int id_coord = word.pairs()[i].GetCoord().GetIndex();
    const int id_state = word.pairs()[i].GetState();
    
    const Solarix::GramCoord & coord = sg.coords()[id_coord];
    if( coord.IsBistable() )
     {
      out.printf( " " );
      if( id_state==0 )
       out.printf( "~" );

      out.printf( "%us", coord.GetName().string().c_str() );
     }
    else
     {
      out.printf( " %us:%us", coord.GetName().string().c_str(), coord.GetStateName( id_state ).c_str() );
     }
   }

  out.printf( " )" );

  return;
 }

 NodePrintBlock::~NodePrintBlock(void)
 {
  for( lem::Container::size_type i=0; i<child.size(); ++i )
   delete child[i];

  return;
 }

 void NodePrintBlock::PushLine( const UFString& s )
 {
  lines.push_back(s);
  h++;
  w = lem::_max( w, (int)s.length() );
  return;
 }

 const UFString& NodePrintBlock::GetLine( int iline ) const
 {
  return iline<CastSizeToInt(lines.size()) ? lines[iline] : empty_line;
 }

}

void Solarix::print_syntax_tree(
                                const lem::UFString & str,
                                const Solarix::Res_Pack & pack,
                                const Solarix::Dictionary & dict,
                                lem::OFormatter & out_file,
                                bool html,
                                bool detailed
                               )
{
 // Выведем синтаксический граф
 const int ivar = pack.GetShortestVar();
 if( ivar!=UNKNOWN )
  {
   if( html )
    {
     out_file.printf( "<pre>" );
    } 

   const Variator &var = *pack.vars()[ivar];
   lem::PtrCollect<NodePrintBlock> blocks;
   int nlines=0, npos=0;

   for( int i=1; i<var.size()-1; ++i )
    {
     const Tree_Node &node = *var[i];

     NodePrintBlock *block = new NodePrintBlock(node,dict.GetSynGram(),html,detailed);
     blocks.push_back(block);

     if( block->h > nlines )
      nlines = block->h;

     npos += block->w;
    }

   for( int iline=0; iline<nlines; ++iline )
    {
     UFString line; line.reserve(npos+64);

     for( lem::Container::size_type i=0; i<blocks.size(); ++i )
      {
       if( i>0 )
        line += L' ';

       const UFString &bl = blocks[i]->GetLine(iline);
       line += bl;
       if( bl.length()<blocks[i]->w )
        line += UFString( blocks[i]->w-bl.length(), L' ' );
      }

     if( html )
      {
       out_file.printf( "%us\n", line.c_str() );
      } 
     else
      {
       out_file.printf( "%us\n", line.c_str() );
      }
    }

   if( html )
    {
     out_file.printf( "</pre>\n" );
    } 
  }
 else
  {
   if( html )
    {
     out_file.printf( "<p><span style=\"color: #FF0000;\"><span style=\"background-color: #FFFF99\">%us</span></span></p>\n", str.c_str() );
    }
   else
    {
     out_file.printf( "%vfCMorphology analyzer error:%vn %us\n", str.c_str() );
    }
  }

 out_file.flush();

 return;
}


lem::UFString Solarix::VarToStr( const Solarix::Dictionary &dict, const Solarix::Variator &var )
{
 lem::UFString res;

 CasingCoder & casing = dict.GetLexAuto().GetCasingCoder();

 for( int i=0; i<var.size(); ++i )
  {
   const Tree_Node &tn = var.get(i);

   if( tn.GetNode().GetEntryKey()!=dict.GetSynGram().I_END &&
       tn.GetNode().GetEntryKey()!=dict.GetSynGram().I_BEGIN )
    {
     #if LEM_DEBUGGING==1
     const Word_Form &wf = tn.GetNode();
     const RC_Lexem &rc = wf.GetName();
     #endif

     UCString w = *tn.GetNode().GetName();
     if( w==L',' || w==L'.' || w==L'!' || w==L'?' || w==L';' || w==L':' )
      {
       res += w.c_str();
      }
     else
      {
       if( tn.GetNode().GetEntryKey()==UNKNOWN )
        {
         if( !res.empty() )
          res += L' ';   
 
         res += w.c_str();
        }
       else
        {
         // Выставим правильный регистр.
         const Word_Form &wf = tn.GetNode();
         const int ekey = wf.GetEntryKey();
         const Solarix::SG_Entry &e = dict.GetSynGram().GetEntry(ekey);

         bool use_casing=true;
         const int iclass=e.GetClass();
         if( !lem::is_quantor(iclass) )
          {
           if( dict.GetSynGram().GetClass(iclass).GetName().eqi(L"UnknownEntries") )
            use_casing=false; 
          }

         if( use_casing )
          {
           lem::UFString wstr( w.c_str() );
           casing.RestoreCasing( ekey, wstr );
           w = wstr.c_str();
          }

         if( !res.empty() )
          res += L' ';   
 
         res += w.c_str();
        } 
      }
    }
  }

 if( !res.empty() )
  {
   const wchar_t c = res.front();
   res.set(0,lem::to_uupper(c));
  }

 return res;
}
