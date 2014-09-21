// Localized strings manager.
// This class returns a string by it's ID for the current session language.
// Strings are stored in text files (utf-8).
// 
// 05.07.2006 - добавлен разбор спецсимволов \r и \n в ресурсах
//
// 03.06.2007 - resource file can include other files, so it is possible to
//              save strings for each language in a separate file.
//
// LC->08.12.2009
// --------------

#include <lem/conversions.h>
#include <lem/ustreams.h>
#include <lem/user_interface.h>

using namespace std;
using namespace lem;
using namespace lem::UI;
using namespace lem::Char_Stream;

Resource_List::Resource_List(void)
{
 load_all_languages = true;
}


// Поиск представления строки ресурса для указанного языка
const lem::UFString& Resource::Get_String( int ilang, int default_lang ) const
{
 for( lem::Container::size_type i=0; i<list.size(); i++ )
  {
   //int il = list[i].first;
   if( list[i].first==ilang )
    return list[i].second;
  }

 if( default_lang!=UNKNOWN && ilang!=default_lang )
  {
   for( lem::Container::size_type i=0; i<list.size(); i++ )
    {
     //int il = list[i].first;
     if( list[i].first==default_lang )
      return list[i].second;
    }
  }

 // Точное соответствие не найдено, возвращаем
 // первый в списке (обычно английский).
 return list.front().second;
}



Resource_List::~Resource_List(void)
{
 for( lem::Container::size_type i=0; i<list.size(); i++ )
  delete list[i];

 list.clear();
 return;
}



void Resource_List::LoadTxt( const lem::Path &filename )
{
 BinaryFile bin_res( filename, true, false ); 
 lem::StreamPtr f(&bin_res,null_deleter());
 lem::Char_Stream::UTF8_Reader utf8_res(f);
 utf8_res.Read_Beginning();
 LoadTxt( static_cast<WideStream&>(utf8_res) );
 
 return;
}



void Resource_List::LoadTxt( WideStream &txt )
{
 // Формат ресурсов: NNN  LANG  string
 //
 // Допускаются директивы:
 // $include filename language                     

 int last_good_id=0;
 
 const lem::UCString INCLUDE(L"$include");

 const UFString cur_lang( lem::to_unicode( lem::UI::get_UI().GetCurrLang() ) );
 const UFString english(L"en");

 UCString nnn;
 std::string lang;
 UFString string;

 while( !txt.eof() )
  {
   txt.skip_white();

   nnn.clear();
   lang.clear();
   string.clear();

   // read the number identifier (primary key) of the string record.
   while( !txt.eof() )
    {
     const wchar_t u = txt.wget();
     if( u==WEOF )
      break;

     if( nnn.front()==L'#' ) 
      {
       // Commentary string - read until EOL.
       while( !txt.eof() )
        {
         const wchar_t u = txt.wget();
         if( u == L'\n' || u==L'\r' || u==WEOF )
          break;
        }

       break;
      }

     if( is_uspace(u) ) 
      {
       txt.unget(u);
       break; 
      }

     nnn += u;
    }
    
   if( nnn.empty() )
    continue;

   if( nnn == INCLUDE )
    {
     // Next fields are: 1) filename and 2) language
     UFString filename, language;
     filename.reserve(64);
     language.reserve(4);

     txt.skip_white();
     while( !txt.eof() )
      {
       const wchar_t u = txt.wget();
       if( u==WEOF )
        break;

       if( is_uspace(u) || u==L'\n' || u==L'\r' ) 
        {
         txt.unget(u);
         break; 
        }

       filename.Add_Dirty(u);
      }

     txt.skip_white();
     while( !txt.eof() )
      {
       const wchar_t u = txt.wget();
       if( u==WEOF )
        break;

       if( is_uspace(u) || u==L'\n' || u==L'\r' ) 
        {
         txt.unget(u);
         break; 
        }

       language.Add_Dirty(u);
      }

     language.calc_hash();
     filename.calc_hash();
     
     // Recursively load the file
     if( load_all_languages || language == cur_lang || language==english )
      {
       // Если задан файл без указания пути, то путь берем из исходного файла
       lem::Path inc(filename);  
       inc.RemoveLastLeaf();
       if( inc.empty() )
        {
         inc = txt.GetName();
         inc.RemoveLastLeaf();
         inc.ConcateLeaf(lem::Path(filename));
         LoadTxt( inc );
        } 
       else 
        {
         LoadTxt( lem::Path(filename) );
        } 
      }  

     continue;
    }

   int iname = 0;
   if( lem::to_int( nnn.c_str(), &iname )==false || iname<=0 )
    throw E_BaseException( lem::format_str( L"Incorrect format of string resource file: id is not a number [%ls]", nnn.c_str() ).c_str() );

   last_good_id = iname;

   // метка языка

   txt.skip_white();

   while( !txt.eof() )
    {
     wchar_t u = txt.wget();
     if( u==WEOF )
      break;

     if( is_uspace(u) ) 
      {
       txt.unget(u);
       break; 
      }

     lang += static_cast<char>(u);
    }
  
   // Ведем список языков, для которых есть локализация ресурсов.
   // ищем такой язык в справочнике
   int ilang = FindLang(lang,NULL);
   int il=0;
   for( std::vector<std::string>::const_iterator j=langs.begin(); j!=langs.end(); j++, il++ )
    if( *j == lang )
     {
      ilang = il;
      break;
     }

   if( ilang==UNKNOWN && !lang.empty() )
    {
     ilang = langs.size();
     langs.push_back( lang );
    }

   txt.skip_white();

   bool apostrophed=true;
   // теперь сама строка ресурсов 
   while( !txt.eof() )
    {
     wchar_t u = txt.wget();
     if( u==WEOF /*EOF fixed 17.09.2009 */ )
      break;

     if( u==L'\r' || u=='\n' ) 
      {
       break; 
      }

     if( u==L'"' && string.empty() )
      {
       // Начало строки в апострофах
       apostrophed = true;
       continue;
      }

     if( u==L'"' && !string.empty() )
      {
       // Конец строки в апострофах
       // Если далее идет символ +, то будет продолжение на следующей строке.
       wchar_t next = txt.wget();
       if( next==L'+' )
        {
         // Это продолжение.
         txt.skip_white();

         next = txt.wget();

         if( next==WEOF || next==0 )
          continue;

         LEM_CHECKIT_Z( next==L'"' );
         continue;
        }

       break;
      }

     if( u==L'\\' )
      {
       // спецсимволы
       wchar_t u2 = txt.wget();
       if( u2==WEOF )
        break;

       if( u2==L'\r' || u2=='\n' ) 
        break; 

       if( u2==L'r' || u2==L'n' )
        u = L'\n';
       else if( u2==L'"' )
        u = L'"';
       else
        u = u2;          
      }

     string.Add_Dirty(u);
    }

   string.calc_hash();

   if( !nnn.empty() && !string.empty() )
    {
     // Сохраняем ресурс. 
     // Ветка ресурса для этого nnn уже есть?
     string.trim();  
     string.strip_quotes();

     Resource *r = NULL;

     std::map<int,Resource*>::iterator it = iname_2_res.find(iname);
     if( it!=iname_2_res.end() )
      {
       r = it->second;
      }
     else
      { 
       r = new Resource;
       r->name = iname;
       list.push_back(r);  
       iname_2_res.insert( std::make_pair(iname,r) );
      }

     r->list.push_back( make_pair( ilang, string ) ); 
    }
  }

 return;
}

int Resource_List::FindLang( const std::string &lang, const char *default_lang ) const
{
 int il=0;
 for( std::vector<std::string>::const_iterator j=langs.begin(); j!=langs.end(); j++, il++ )
  {
   const std::string &s = *j;
   if( s == lang )
    return il;
  }

 // В качестве лингва франка пусть будет английский язык...
 if( default_lang!=NULL && lang!=default_lang )
  return FindLang(default_lang,NULL);

 return UNKNOWN;
}



const UFString& Resource_List::Find( int name ) const
{
 UCString Name(name);

 for( Container::size_type i=0; i<list.size(); i++ )
  if( list[i]->name == name ) 
   return list[i]->Get_String( FindLang( lem::UI::get_UI().GetCurrLang() ), FindLang( "en" ) );

 static UFString dummy( L"*** resource not found ***" );
 return dummy;
}


const FString Resource_List::FindA( int name ) const
{
 return to_ascii( Find(name) );
}
