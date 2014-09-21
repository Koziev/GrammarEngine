// CD->10.11.2006
// LC->18.09.2009

#include <lem/config.h>

#if defined LEM_WINDOWS
 #if defined LEM_MFC
  #include <afxwin.h>
 #else 
  #include <windows.h>
 #endif
#endif

#include <lem/ustreams.h>
#include <lem/lexers.h>
#include <lem/unicode.h>
#include <lem/minmax.h>

using namespace lem;


Transliterator::Transliterator(void)
{
}

Transliterator::Transliterator( const lem::Path &filename )
{
 name = filename.GetUnicode();
 LoadTxt(filename);
 return;
}


void Transliterator::SaveBin( lem::Stream &bin ) const
{
 bin.wr( &name );
}


void Transliterator::LoadBin( lem::Stream &bin )
{
 bin.rd( &name );
}


wchar_t Transliterator::NextChar( lem::Stream &txt )
{
 if( !queue.empty() )
  {
   wchar_t r = queue.front();
   queue.Remove(0);
   return r;
  }

 int c = txt.get();
 if( c==EOF || c<' ' )
  return c;

 CITER it = table.find( static_cast<char>(c) );
 if( it==table.end() )
  return c;

 // Трансляция 1->N
 if( it->second.max_len==1 )
  {
   const UCString &res = it->second.alt.front().second; 

   if( res.length()==1 )
    return res.front();

   queue = res.begin()+1;
   return res.front();
  }

 const XLat& xlat = it->second;

 CString acc;
 int ilast_alt=UNKNOWN;
 while( !txt.eof() )
  {
   // Считываем следующий символ
   Stream::pos_type back = txt.tellp();
   int c2 = txt.get();

   if( c2==EOF )
    return c;

   acc += static_cast<char>(c2);

   // Есть такая группа?
   const int ialt = xlat.Find(acc);
   if( ialt!=UNKNOWN )
    {
     // Есть. Есть более длинные группы?
     if( acc.length()+1<xlat.max_len && !txt.eof() )
      {
       // Да - продолжим накопление символов
       ilast_alt = ialt;
       continue;
      }
 
     // Более длинных групп нету, значит прекращаем наращивание и возвращаем
     // результат для текущей группы.
     const UCString &res = xlat.alt[ialt].second;

     if( res.length()==1 )
      return res.front();

     queue = res.begin()+1;
     return res.front();
    }
   else
    {
     // Такой группы нет. Усекаем последний добавленный символ.
     txt.seekp(back);
     acc.Remove( acc.length()-1 );
     
     // Возвращаем результат для более короткой группы
     const UCString &res = xlat.alt[ilast_alt==UNKNOWN ? xlat.Find(acc) : ilast_alt].second;
     if( res.length()==1 )
      return res.front();

     queue = res.begin()+1;
     return res.front();
    }
  }

 return WEOF;
}



void Transliterator::Add( const char *org, const wchar_t *res )
{
 LEM_CHECKIT_Z(org!=NULL);
 LEM_CHECKIT_Z(*org!=0 );
 LEM_CHECKIT_Z(res!=0);

 ITER it = table.find( *org );
 if( it==table.end() )
  {
   XLat xlat;
   xlat.Add( org+1, res );
   table.insert( std::make_pair( *org, xlat ) );
  }
 else
  {
   it->second.Add( org+1, res );
  }

 if( wcslen(res)==1 )
  {
   table2.insert( std::make_pair( *res, CString(org) ) );
  }

 return;
}



void Transliterator::XLat::Add( const char *Tail, const wchar_t *Res )
{
 LEM_CHECKIT_Z(Tail!=NULL);
 LEM_CHECKIT_Z(Res!=NULL);

 for( lem::Container::size_type i=0; i<alt.size(); i++ )
  if( alt[i].first == Tail )
   throw E_BaseException( L"Incorrect transliteration table record" );

 max_len = lem::max( max_len, int(strlen(Tail)+1) );
 alt.push_back( std::make_pair( CString(Tail), UCString(Res) ) );

 return;
}



int Transliterator::XLat::Find( const lem::CString &Tail ) const
{
 for( lem::Container::size_type i=0; i<alt.size(); i++ )
  if( alt[i].first==Tail )
   return CastSizeToInt(i);

 return UNKNOWN;
}






// ***************************************************************
// Загрузка таблицы транслитерации из указанного текстового файла
// ***************************************************************
void Transliterator::LoadTxt( const lem::Path &filename )
{
 BinaryFile bin(filename,true,false);
 lem::Char_Stream::UTF8_Reader utf8( lem::StreamPtr(&bin,null_deleter()) );
 utf8.Read_Beginning();

 UTextParser txt;
 txt.Open( lem::Char_Stream::WideStreamPtr(&utf8,null_deleter()) );

 while( !txt.eof() )
  {
   CString from = to_ascii(txt.read().string()); // латиница - как представлен текст
   UCString to = txt.read().string();   // кириллица - каков был оригинальный русский текст

   if( from.empty() || to.empty() )
    break;

   if( to.length()!=1 )
    throw E_BaseException( L"Incorrect field 'TO' in transliteration table\n" );

   if( from.length()<1 )
    throw E_BaseException( L"Incorrect field 'FROM' in transliteration table\n" );

   Add( from.c_str(), to.c_str() );
  }

 return;
}


// **************************************************************************
// Заданный символ кодируется латиницей, либо возвращается NULL - кодирование
// невозможно.
// **************************************************************************
const char* Transliterator::ToLatin( wchar_t c ) const
{
 CITER2 it=table2.find( lem::to_ulower(c) );
 return it==table2.end() ? NULL : it->second.c_str();
}


// ****************************************
// Преобразование строки в транслит.
// ****************************************
void Transliterator::ToLatin( const wchar_t *src, FString &res ) const
{
 int i=0;
 while( src[i]!=0 )
  {
   CITER2 it=table2.find( lem::to_ulower(src[i]) );
   if( it!=table2.end() )
    res.Add_Dirty( it->second.c_str() );

   i++;
  }

 res.calc_hash();

 return;
}



Translit_Gost_16876_71::Translit_Gost_16876_71(void)
{
 Add( "a",   L"\x0430" );
 Add( "b",   L"\x0431" );
 Add( "v",   L"\x0432" );
 Add( "g",   L"\x0433" );
 Add( "d",   L"\x0434" );
 Add( "e",   L"\x0435" );
 Add( "jo",  L"\x0451" );
 Add( "zh",  L"\x0436" );
 Add( "z",   L"\x0437" );
 Add( "i",   L"\x0438" );
 Add( "jj",  L"\x0439" );
 Add( "k",   L"\x043A" );
 Add( "l",   L"\x043B" );
 Add( "m",   L"\x043C" );
 Add( "n",   L"\x043D" );
 Add( "o",   L"\x043E" );
 Add( "p",   L"\x043F" );
 Add( "r",   L"\x0440" );
 Add( "s",   L"\x0441" );
 Add( "t",   L"\x0442" );
 Add( "u",   L"\x0443" );
 Add( "f",   L"\x0444" );
 Add( "kh",  L"\x0445" );
 Add( "c",   L"\x0446" );
 Add( "ch",  L"\x0447" );
 Add( "sh",  L"\x0448" );
 Add( "shh", L"\x0449" );
 Add( "\"",  L"\x044A" );
 Add( "y",   L"\x044B" );
 Add( "'",   L"\x044C" );
 Add( "eh",  L"\x044D" );
 Add( "yu",  L"\x044E" );
 Add( "ya",  L"\x044F" );

 return;
}



static Translit_Gost_16876_71 *translit_gost=NULL;
const Translit_Gost_16876_71* Translit_Gost_16876_71::GetInstance(void)
{ 
 if( translit_gost==NULL )
  translit_gost = new Translit_Gost_16876_71();

 return translit_gost;
}






Translit_EngPhonetics::Translit_EngPhonetics(void)
{
 Add( "a",   L"\x0430" );
 Add( "b",   L"\x0431" );
 Add( "d",   L"\x0434" );
 Add( "e",   L"\x0435" );
 Add( "f",   L"\x0444" );
 Add( "g",   L"\x0433" );
 Add( "h",   L"\x0445" );
 Add( "i",   L"\x0438" );
 Add( "j",   L"\x0439" );
 Add( "k",   L"\x043A" );
 Add( "l",   L"\x043B" );
 Add( "m",   L"\x043C" );
 Add( "n",   L"\x043D" );
 Add( "o",   L"\x043E" );
 Add( "p",   L"\x043F" );
 Add( "q",   L"\x043A" );
 Add( "r",   L"\x0440" );
 Add( "s",   L"\x0441" );
 Add( "t",   L"\x0442" );
 Add( "u",   L"\x0443" );
 Add( "v",   L"\x0432" );
 Add( "w",   L"\x0432" );
 Add( "x",   L"\x043A\x0441" );
 Add( "y",   L"\x044B" );
 Add( "z",   L"\x0437" );

 Add( "tcsh", L"\x0449" );
 Add( "sh",   L"\x0448" );
 Add( "ch",   L"\x0447" );
 Add( "tz",   L"\x0446" );
// Add( "",    L"ъ" );
// Add( "",    L"ь" );
 Add( "e",   L"\x0451" );
 Add( "e",   L"\x044D" );
 Add( "a",   L"\x044F" );
 Add( "u",   L"\x044E" );
 Add( "c",   L"\x0441" );

 return;
}


void Translit_EngPhonetics::Add( const char *org, const wchar_t *res )
{
 LEM_CHECKIT_Z(org!=NULL);
 LEM_CHECKIT_Z(res!=NULL);

 if( wcslen(res)==1 )
  table2.insert( std::make_pair( *res, CString(org) ) );

 return;
}



static Translit_EngPhonetics *translit_engphon=NULL;
const Translit_EngPhonetics* Translit_EngPhonetics::GetInstance(void)
{ 
 if( translit_engphon==NULL )
  translit_engphon = new Translit_EngPhonetics();

 return translit_engphon;
}




void Transliterator::DeleteInstances(void)
{ 
 lem_rub_off(translit_gost);
}
