// -----------------------------------------------------------------------------
// File SG_PREPARING.CPP
//
// (c) Koziev Elijah
//
// Content:
// Часть реализации Синтаксической Грамматики (класс SynGram): подготовка
// Лексикона к работе после загрузки из текстового файла Словаря.
// Используется компилятором Соляриса.
//
// 17.02.2008 - добавлена генерация констант для биндинга с CSharp
// 24.02.2009 - поправлена генерация текста Pascal-модуля с константами _sg_api.pas
// 03.02.2010 - генерация обратных связей отключается опцией в строке запуска
// 16.03.2010 - новый тип генераторов - многосвязные - для создания переводов
//              кана-русский из двух входных связей кандзи-русский и кандзи-кана
// 26.10.2011 - добавлена генерация экспортного модуля для PHP
// -----------------------------------------------------------------------------
//
// CD->02.09.1997
// LC->12.02.2012
// --------------

#include <lem/conversions.h>
#include <lem/logfile.h>
#include <lem/solarix/version.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/ThesaurusStorage.h>
#include <lem/solarix/TagSets.h>
#include <lem/solarix/WordLinkEnumerator.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/ClassList.h>
#include <lem/solarix/PartOfSpeechEnumerator.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/CoordEnumerator.h>
#include <lem/solarix/Languages.h>
#include <lem/solarix/LA_ProjectInfo.h>
#include <lem/solarix/LanguageEnumerator.h>
#include <lem/solarix/SG_Calibrator.h>
#include <lem/solarix/WordEntryEnumerator.h>


using namespace lem;
using namespace std;
using namespace Solarix;

const GraphGram& SynGram::GetGraphGram(void) const
{ return GetDict().GetGraphGram(); }

#if defined SOL_LOADTXT && defined SOL_COMPILER
/***********************************************************************
   Подготовка к работе после загрузки содержимого из текстового
 файла Словаря. Процедура вызывается модулем Словаря автоматически.
 Выполняем некоторые операции, которые позволят реализовать быстрый
 алгоритм проецирования мультилексем на Лексикон. То есть, мы создадим и
 сохраним некоторые информационные структуры, чтобы при поиске словоформ
 не отвлекаться на создание этих структур снова и снова. Только после
 выполнения этой процедуры Лексикон готов к использованию другими
 автоматами.
***********************************************************************/
void SynGram::Prepare( const lem::Path &outdir, const Binarization_Options &opts )
{
 Grammar::Prepare(outdir,opts);

 word_entries->CommitCompilation( GetIO().merr() );
 storage->CommitCompilation();

 Generate_Links(opts);


 Write_Declarations(outdir);

 for( std::map<UCString,CplxLeft*>::iterator it=cplx_map.begin(); it!=cplx_map.end(); ++it )
  {
   const CplxLeft &x = * it->second;
   GetStorage().StoreCplxLeft(x.headword,x.minlen,x.maxlen);
  }


 // Инициализируем частоты словарных статей и словоформ.
 // Нам потребуется быстро найти словарные статьи по их леммам.

 std::multimap<lem::UCString,int> lemma2id;

 lem::Ptr<WordEntryEnumerator> wenum( word_entries->ListEntries() );
 while( wenum->Fetch() )
 {
  lem::UCString entry_name = lem::to_upper( GetEntry( wenum->GetId() ).GetName() );
  lemma2id.insert( std::make_pair( entry_name, wenum->GetId() ) );
 }



 if( wordfreq_filename.NotNull() )
  {
   wordfreq_file.Delete();

   lem::BinaryReader rdr( *wordfreq_filename );

   // Длительная операция: сообщаем пользователю.
   GetIO().mecho().printf( "%vfESG%vn: updating word frequencies..." );
   GetIO().mecho().flush();

   MCollect<Word_Coord> found_list;
   MCollect<ProjScore> val_list;
   PtrCollect<LA_ProjectInfo> inf_list;
   LexicalAutomat &la = GetDict().GetLexAuto();

   int counter=0;

   while( !rdr.eof() )
    {
     SG_calibrator c;
     c.LoadBin(rdr);
     
     if( rdr.eof() )
      break;

     counter++;

     if( counter>0 && (counter%10000)==0 )
     {
      lem::mout->printf( " %d", counter/10000 );
      lem::mout->flush();
     }

     Lexem uword( lem::to_upper( c.GetWord() ) );


     if( c.IsWordFormsScore() )
      {
       // Заданы оценки для всех форм слова
       lem::MCollect<int> ies;

       typedef std::multimap<lem::UCString,int>::const_iterator L2E_CIT;
       std::pair<L2E_CIT,L2E_CIT> r = lemma2id.equal_range( uword );
       for( L2E_CIT it=r.first; it!=r.second; ++it )
        {
         int id_entry = it->second;
         if( c.GetClass()==UNKNOWN || GetEntries().GetEntry( id_entry ).GetClass() == c.GetClass() )
          {
           SG_Entry& e = GetEntries().GetEntryForChange( id_entry );

           for( int iform=0; iform<e.forms().size(); ++iform )
            {
             const SG_EntryForm &f = e.forms()[iform];
             if( c.MatchCoords( f.coords() ) )
              {
               GetStorage().SetWordformFrequency( id_entry, iform, c.GetFreq() );
              }
            }
          }
        }
      }
     else if( c.GetClass()!=UNKNOWN && c.IsWordEntryFreq() )
      {
       lem::MCollect<int> ies;

       typedef std::multimap<lem::UCString,int>::const_iterator L2E_CIT;
       std::pair<L2E_CIT,L2E_CIT> r = lemma2id.equal_range( uword );
       for( L2E_CIT it=r.first; it!=r.second; ++it )
        {
         int id_entry = it->second;
         if( GetEntries().GetEntry( id_entry ).GetClass() == c.GetClass() )
          {
           SG_Entry& e = GetEntries().GetEntryForChange( id_entry );
           e.UpdateFreq( c.GetFreq() );
          }
        }
      }
     else if( c.IsWordFormScore() )
      {
       // задан скоринг для словоформы.

       int language_id=UNKNOWN;
       // если указан грамматический класс, то берем id языка оттуда.
       if( c.GetClass()!=UNKNOWN )
        {
         const Solarix::SG_Class & pos = GetClass( c.GetClass() );
         language_id = pos.GetLanguage();
        }
       
       la.TranslateLexem( uword, true, language_id );
       
       RC_Lexem rc_name( &uword, null_deleter() );

       found_list.clear();
       val_list.clear();
       inf_list.clear();

       la.ProjectWord( rc_name, found_list, val_list, inf_list, LexicalAutomat::Wordforms, 0, language_id, NULL );
    
       // задан скоринг для словоформы.
    
       if( found_list.empty() )
        {
         GetIO().mecho().printf( "\nUnknown word [%us] in word_frequency rule\n", c.GetWord().c_str() );
         throw lem::E_BaseException();
        }
    
       for( lem::Container::size_type j=0; j<found_list.size(); ++j )
        {
         const SG_Entry &e = GetEntry(found_list[j].GetEntry());
         
         if( c.GetClass()!=UNKNOWN && c.GetClass()!=e.GetClass() )
          {
           continue;
          } 
    
         const SG_EntryForm &f = e.forms()[found_list[j].GetForm()];
         if( c.MatchCoords( f.coords() ) )
          {
           GetStorage().SetWordformFrequency( found_list[j].GetEntry(), found_list[j].GetForm(), c.GetFreq() );
          }
        }
      }
     else
      {
       LEM_STOPIT;
      } 
    }


   rdr.close();
   wordfreq_filename->DoRemove();

   GetIO().mecho().printf( "%vfAOK%vn\n" );
  }

 return;
}
#endif


#if defined SOL_COMPILER
/*************************************************************************
*************************************************************************/
void SynGram::Generate_Links( const Binarization_Options &opts )
{
 net->Compile();

 if( opts.reverse_links )
  {
   const int dbg = 1;

   if( dbg>0 )
    {
     // Длительная операция: сообщаем пользователю.
     GetIO().mecho().printf( "%vfESG%vn: generating reverse links..." );
     GetIO().mecho().flush();
    }

   int n_total_links=0;

   // Накапливаем информацию о всех существующих связках.

   typedef lem::foursome<int,int,int,int> WordLinkInfo;

   std::set< WordLinkInfo > links;

   lem::Ptr<WordLinkEnumerator> rs( Get_Net().EnumerateWordLinks() );

   while( rs->Fetch() )
    {
     const int ekey1 = rs->GetEntryKey1();
     const int ekey2 = rs->GetEntryKey2();
     const int link_type = rs->GetLinkType();
     const int itags = rs->GetTagsId(); 
     links.insert( lem::make_foursome(ekey1,ekey2,link_type,itags) );
    }

   rs.Delete();

   //const int net_size_0 = CastSizeToInt(net.size()); // будет меняться по ходу добавления
   int n_generated_links=0;

   // Теперь можем генерировать ОБРАТНЫЕ связки по имеющимся.
   rs = Get_Net().EnumerateWordLinks();

   while( rs->Fetch() )
    {
     try
      {
       const int id_link = rs->GetLinkId();
       const int ek0 = rs->GetEntryKey1();
       const int ek1 = rs->GetEntryKey2();
       const int link_type = rs->GetLinkType();
       const int id_tags = rs->GetTagsId();
       SG_TagsList tags = (*Get_Net().tag_sets)[id_tags];

//lem::LogFile::logfile->printf( "DEBUG 1 id=%d, ek0=%d ek1=%d link_type=%d id_tags=%d\n", id_link, ek0, ek1, link_type, id_tags );

       Tree_Link t(link_type);

       int ie0 = ek0;//this->FindEntryIndexByKey(ek0);
       if( lem::is_quantor(ie0) )
        continue;
 
       int ic0 = this->GetEntry(ie0).GetClass();
       if( lem::is_quantor(ic0) )
        continue;

       int ie1 = ek1;//this->FindEntryIndexByKey(ek1);
       if( lem::is_quantor(ie1) )
        continue;

       int ic1 = GetEntry(ie1).GetClass();
       if( lem::is_quantor(ic1) ) 
        continue;

       WordLinkInfo new_link;
       lem::MCollect<WordLinkInfo> new_links;

       for( Container::size_type j=0; j<link_generators.size(); j++ ) 
        if( link_generators[j]->IsMultitier() )
         {
          // Многофакторные генераторы
          new_links.clear();
          if( link_generators[j]->Match2( *this, ek0, t, ek1, new_links ) )
           {
            for( lem::Container::size_type j=0; j<new_links.size(); ++j )
             {
              new_link = new_links[j];

//lem::LogFile::logfile->printf( "DEBUG 2 ek0=%d ek1=%d link_type=%d id_tags=%d\n", new_link.first, new_link.second, new_link.third, new_link.fourth );

              const bool pres = links.find(new_link)!=links.end();

              if( !pres )
               {
                Get_Net().GetStorage().AddWordLink( new_link.first, new_link.second, new_link.third, new_link.fourth );
                links.insert( new_link );

                n_generated_links++;

                if( dbg>=2 )
                 {
                  lem::LogFile::logfile->printf( "Link: %us", GetEntry(ie0).GetName().c_str() );
                  t.Print( *lem::LogFile::logfile, *this );
                  lem::LogFile::logfile->printf( " %us generates(2) new link: ", GetEntry(ie1).GetName().c_str() );
      
                  lem::LogFile::logfile->printf( "%us", GetEntry( new_link.first ).GetName().c_str() );
                  Tree_Link tl(new_link.third);  
                  tl.Print( *lem::LogFile::logfile, *this );
                  lem::LogFile::logfile->printf( " %us\n", GetEntry( new_link.second ).GetName().c_str() );
                  lem::LogFile::logfile->flush();
                 }
               }
             }
           }
         }
        else
         { 
          // Простые генераторы
          if( link_generators[j]->Match( ic0, t, ic1 ) )
           {
            new_link = lem::make_foursome( ek1, ek0, link_generators[j]->getReverseLink().GetState(), id_tags );

//lem::LogFile::logfile->printf( "DEBUG 3 ek0=%d ek1=%d link_type=%d id_tags=%d\n", new_link.first, new_link.second, new_link.third, new_link.fourth );

            const bool pres = links.find(new_link)!=links.end();

            if( !pres )
             {
              Get_Net().GetStorage().AddWordLink( ek1, ek0, link_generators[j]->getReverseLink().GetState(), id_tags );

              links.insert( new_link );

              n_generated_links++;

              if( dbg>=2 )
               {
                lem::LogFile::logfile->printf( "Link: %us", GetEntry(ie0).GetName().c_str() );
                t.Print( *lem::LogFile::logfile, *this );
                lem::LogFile::logfile->printf( " %us generates new link: ", GetEntry(ie1).GetName().c_str() );
      
                lem::LogFile::logfile->printf( "%us", GetEntry(ie1).GetName().c_str() );
                Tree_Link tl( new_link.third );
                tl.Print( *lem::LogFile::logfile, *this );
                lem::LogFile::logfile->printf( " %us\n", GetEntry(ie0).GetName().c_str() );
                lem::LogFile::logfile->flush();
               }
             }
           } 
         } 
       }
     catch( const E_RunTime& )
      {
      }
    }

   if( dbg>0 )
    {
     GetIO().mecho().printf( "%vfE%d%vn links generated %vfAOK%vn\n", n_generated_links );
     GetIO().mecho().flush();
    }
  }

 
 return;
}
#endif






#if defined SOL_COMPILER
// **************************************************************
// В отдельный файл (*.h) записываются объявления констант,
// с помощью которых удобнее работать во внешних C-программах
// со словарем Проекта.
// **************************************************************
void SynGram::Write_Declarations( const lem::Path &outdir )
{
 lem::Path cpp_path(outdir);
 cpp_path.ConcateLeaf( lem::Path( "_sg_api.h" ) );
 OUFormatter cpp( cpp_path, false );
 cpp.printf(
            "// This file is generated %us by Ygres compiler ver. %s.\n" 
            , timestamp().c_str()
            , sol_get_version().c_str() 
           );  


 lem::Path cs_path(outdir);
 cs_path.ConcateLeaf( lem::Path( "_sg_api.cs" ) );
 OUFormatter cs( cs_path, false );
 cs.printf(
           "namespace SolarixGrammarEngineNET\n"
           "{\n"
           " public sealed class GrammarEngineAPI\n"
           " {\n"
           "  public const string VERSION_MARK=\"This file is generated %us by Ygres compiler ver. %s.\";\n"
           , timestamp().c_str()
           , sol_get_version().c_str() 
          );  


 // Для Pascal нельзя использовать utf-8 кодировку файла, поэтому - текущая локаль.
 lem::Path pas_path(outdir);
 pas_path.ConcateLeaf( lem::Path( "_sg_api.pas" ) );
 OFormatter pas( pas_path );
 pas.SetOutCP( &lem::UI::get_UI().GetSessionCp() );
 pas.printf(
            "{ This file is generated %us by Ygres compiler ver. %s. }\n" 
            , timestamp().c_str()
            , sol_get_version().c_str() 
           );  

 pas.printf(
            "unit _sg_api;\n"
            "interface\n"
           );

 lem::Path py_path(outdir);
 py_path.ConcateLeaf( lem::Path( "_sg_api.py" ) );
 OUFormatter py( py_path, false );
 py.printf(
           "# -*- coding: utf-8\n"
           "# This file is generated %us by Ygres compiler ver. %s.\n" 
           , timestamp().c_str()
           , sol_get_version().c_str() 
          );  

 lem::Path php_path(outdir);
 php_path.ConcateLeaf( lem::Path( "_sg_api.php" ) );
 OUFormatter php( php_path, false );
 php.printf(
            "<?php\n"
            "// This file is generated %us by Ygres compiler ver. %s.\n"
            "namespace Solarix;\n"
            , timestamp().c_str()
            , sol_get_version().c_str() 
           );

 cpp.printf( "// Languages\n" );
 cs.printf( "// Languages\n" );
 pas.printf( "{ Languages }\n" );
 py.printf( "# Languages\n" );
 php.printf( "// Languages\n" );


 lem::Ptr<LanguageEnumerator> lenum( languages().Enumerate() );
 while( lenum->Fetch() )
  {
   const SG_Language lang = lenum->GetItem();
   const int id = lang.GetId();

   if( !lang.get_C_Name().empty() ) 
    {
     cpp.printf(
                "const int %us = %d; %50t // language %us\n"
                , lang.get_C_Name().c_str()
                , id
                , lang.GetName().c_str()
               );

     cs.printf(
               " public const int %us = %d; %50t // language %us\n"
               , lang.get_C_Name().c_str()
               , id
               , lang.GetName().c_str()
              );

     pas.printf(
                " const %us: integer = %d; %50t { language %us }\n"
                , lang.get_C_Name().c_str()
                , id
                , lang.GetName().c_str()
               );

     py.printf(
                "%us = %d %50t # language %us\n"
                , lang.get_C_Name().c_str()
                , id
                , lang.GetName().c_str()
               );

     php.printf(
                "define( '%us', %d ); %50t // language %us\n"
                , lang.get_C_Name().c_str()
                , id
                , lang.GetName().c_str()
               );
    }
  }

 cpp.printf( "// %60h-\n\n\n" );
 cs.printf( "// %60h-\n\n\n" );
 pas.printf( "{ %60h- }\n\n\n" );
 py.printf( "# %60h-\n\n\n" );
 php.printf( "// %60h-\n\n\n" );

 lem::Ptr<PartOfSpeechEnumerator> cenum( (PartOfSpeechEnumerator*)classes().Enumerate() );
 while( cenum->Fetch() )
  {
   const int id_class = cenum->GetId();
   const SG_Class &c = (SG_Class&)cenum->GetItem();
   if( !c.get_C_Name().empty() ) 
    {
     cpp.printf(
                "const int %us = %d; %50t // class %us\n"
                , c.get_C_Name().c_str()
                , id_class
                , c.GetName().c_str()
               );

     cs.printf(
               " public const int %us = %d; %50t // class %us\n"
               , c.get_C_Name().c_str()
               , id_class
               , c.GetName().c_str()
              );

     pas.printf(
                " const %us: integer = %d; %50t { class %us }\n"
                , c.get_C_Name().c_str()
                , id_class
                , c.GetName().c_str()
               );

     py.printf(
               "%us = %d %50t # class %us\n"
               , c.get_C_Name().c_str()
               , id_class
               , c.GetName().c_str()
              );

     php.printf(
                "define( '%us', %d ); %50t // class %us\n"
                , c.get_C_Name().c_str()
                , id_class
                , c.GetName().c_str()
               );
    }
  }
 cpp.printf( "// %60h-\n\n\n" );
 cs.printf( "// %60h-\n\n\n" );
 pas.printf( "{ %60h- }\n\n\n" );
 py.printf( "# %60h-\n\n\n" );
 php.printf( "// %60h-\n\n\n" );

 lem::Ptr<CoordEnumerator> coenum( coords().Enumerate() );
 while( coenum->Fetch() )
  {
   const int id_coord = coenum->GetId();
   const GramCoord &c = coenum->GetItem();
   if( !c.get_C_Name().empty() ) 
    {
     cpp.eol();
     cs.eol();
 
     cpp.printf(
                "const int %us = %d; %50t // enum %us\n"
                , c.get_C_Name().c_str()
                , id_coord
                , c.GetName().front().c_str()
               );
 
     cs.printf(
               " public const int %us = %d; %50t // enum %us\n"
               , c.get_C_Name().c_str()
               , id_coord
               , c.GetName().front().c_str()
              );
 
     pas.printf(
                " const %us: integer = %d; %50t { enum %us }\n"
                , c.get_C_Name().c_str()
                , id_coord
                , c.GetName().front().c_str()
               );

     py.printf(
               "%us = %d %50t # enum %us\n"
               , c.get_C_Name().c_str()
               , id_coord
               , c.GetName().front().c_str()
              );
 
     php.printf(
                "define( '%us', %d ); %50t // enum %us\n"
                , c.get_C_Name().c_str()
                , id_coord
                , c.GetName().front().c_str()
               );

     c.Save_API( cpp, lem::Binding::CPP );
     c.Save_API( cs, lem::Binding::CSharp );
     c.Save_API( pas, lem::Binding::Pascal );
     c.Save_API( py, lem::Binding::Python );
     c.Save_API( php, lem::Binding::PHP );
    }
  }

 cpp.printf( "// %60h-\n\n\n" );
 cs.printf( "// %60h-\n\n\n" );
 pas.printf( "{ %60h- }\n\n\n" );
 py.printf( "# %60h-\n\n\n" );
 php.printf( "// %60h-\n\n\n" );
 

 const int n_link = coords()[I_NET].states().size();
 for( int i5=0; i5<n_link; i5++ )
  if( !coords()[I_NET].states()[i5].get_C_Name().empty() )
   {
    cpp.printf(
               "const int %us = %d;\n"
                , coords()[I_NET].states()[i5].get_C_Name().c_str()
                , i5
               );

    cs.printf(
              " public const int %us = %d;\n"
              , coords()[I_NET].states()[i5].get_C_Name().c_str()
              , i5
             );

    pas.printf(
              " const %us: integer = %d;\n"
              , coords()[I_NET].states()[i5].get_C_Name().c_str()
              , i5
             );

    py.printf(
              "%us = %d\n"
              , coords()[I_NET].states()[i5].get_C_Name().c_str()
              , i5
             );

    php.printf(
               "define( '%us', %d );\n"
               , coords()[I_NET].states()[i5].get_C_Name().c_str()
               , i5
              );
   }

 cs.printf( "\n  };\n }\n" );

 pas.printf(
            "implementation\n"
            "end.\n"
           );

 php.printf(
            "\n?>\n"
           );

 return;
}
#endif
