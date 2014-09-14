// 15.11.007 - стем не создается для слов короче 3 символов

#if defined SOL_CAA

#include <lem/xml_parser.h>
#include <lem/unicode.h>
#include <lem/solarix/sg_autom.h>

using namespace lem;
using namespace Solarix;

SG_Stemmer::SG_Stemmer(void)
{
 hStemmer = NULL;
 return;
}


void SG_Stemmer::Load( const lem::Path &dllpath )
{
 if( dll.Load(dllpath) )
  {
   // Импортируем функции API стеммера
   sol_CreateStemmerForLanguage = (sol_CreateStemmerForLanguage_fun)dll.Import("sol_CreateStemmerForLanguage");
   sol_DeleteStemmer = (sol_DeleteStemmer_fun)dll.Import("sol_DeleteStemmer");
   sol_Stem = (sol_Stem_fun)dll.Import("sol_Stem");

   if( sol_CreateStemmerForLanguage!=NULL &&
       sol_DeleteStemmer!=NULL &&
       sol_Stem!=NULL )
    {
     // Создадим стеммер для языка текущей сессии или для указанного в конфиге
     
     lem::Path cfg(dllpath);
     cfg.AddExtension( "xml" ); 
     
     if( cfg.DoesExist() )
      {
       // Конфиг-файл существует, читаем имя языка оттуда.
       try
        { 
         lem::Xml::Parser p;
         p.Load(cfg);

         const lem::Xml::Node* nod = p.Find_By_Path( L"dataroot.lang2" );
         if( nod==NULL )
          throw E_BaseException( lem::format_str( L"Incorrect format of stemmer XML file '%ls'", cfg.GetUnicode().c_str() ).c_str() );
 
         const UFString &lang2 = nod->GetBody();
         hStemmer = (void*)sol_CreateStemmerForLanguage( lem::to_ascii(lang2).c_str() );
        }
       catch(...)
        {
         throw E_BaseException( lem::format_str( L"Incorrect format of stemmer XML file '%ls'", cfg.GetUnicode().c_str() ).c_str() );
        }   
      }
     else
      {     
       // Используем имя языка текущей пользовательской сессии.
       hStemmer = (void*)sol_CreateStemmerForLanguage( lem::UI::get_UI().GetCurrLang().c_str() );
      } 
    }
  }
 
 return;
}

bool SG_Stemmer::Stem( const UCString &org, UCString &stem ) const
{
 if( hStemmer==NULL || org.length()<3 )
  return false;

 stem = org;
 if( sol_Stem( hStemmer, (wchar_t*)stem.c_str() )==0 )
  {
   stem.calc_hash(); 
   return true;
  }

 return false;
}

#endif
