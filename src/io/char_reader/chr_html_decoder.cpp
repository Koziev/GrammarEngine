// -----------------------------------------------------------------------------
// File CHR_HTML_DECODER.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// Класс HTML_Decoder - извлекает из HTML файла контент, отбрасывая тэги и
// выполняя прочие необходимые перекодировки. 
//
// 25.02.2006 - добавлен поиск атрибута encoding=XXX для корректной работы с XML
//
// 02.06.2006 - при чтении символы \r, \n и \t заменяются пробелами
//
// 26.06.2006 - исправлена ошибка в чтении атрибута encoding (charset)
//
// 12.10.2006 - добавлена замена тэгов </p>, <hN>, </hN> и некоторых других на
//              пробелы. 
//
// 13.03.2007 - исправлена ошибка в парсере.
// -----------------------------------------------------------------------------
//
// CD->10.11.2004
// LC->01.04.2018
// --------------

#include <lem/unicode.h>
#include <lem/conversions.h>
#include <lem/ustreams.h>
#include <lem/char_buffer.h>

#undef min
#undef max

using namespace lem;
using namespace lem::Char_Stream;


HTML_Decoder::HTML_Decoder(void)
 : WideStream(SET_HTML)
{
 force_cp = NULL;
 missing_cp = NULL;
 cp = NULL;
 utf8 = false;

 #if defined LEM_ICU
 icu = false;
 #endif

 return;
}


HTML_Decoder::HTML_Decoder(
                           lem::Ptr<Stream> File,
                           const CodeConverter *Cp_IfMissing,
                           const CodeConverter *Force_cp,
                           bool do_open_stream
                          )
 : WideStream( SET_HTML, File )
{
 force_cp = Force_cp;
 missing_cp = Cp_IfMissing;
 cp = NULL;

 utf8 = false;

 #if defined LEM_ICU
 icu = false;
 #endif

 if( do_open_stream )
  Open_Stream();
 
 if( cp==NULL )
  cp = &lem::UI::get_UI().GetSessionCp();

 return;
}


void HTML_Decoder::Open_Stream(void)
{
 static FString UTF8_1("utf8");
 static FString UTF8_2("utf-8");

 if( force_cp!=NULL )
  {
   // Так как предпочитаемая кодовая таблица задана явно, то не будем
   // анализировать заголовок HTML.
   cp = force_cp;
   return;
  }

 // Попробуем определить кодовую страницу.
 // Для этого подгрузим первые 512 байтов страницы, и попробуем
 // в ней найти charset=xxx
 const int BLOCK_SIZE=512;
 boost::scoped_array<char> block( new char[BLOCK_SIZE+1] );
 Stream::pos_type rd = bin->read( block.get(), 511 );
 int z = std::max( std::min( int(rd), BLOCK_SIZE )-1, 0 );
 LEM_CHECKIT_Z( z>=0 );
 block[z]=0;

 if( lem_find( block.get(), "?xml" )!=UNKNOWN )
  {
   // По умолчанию предполагаем, что любой тэг разбивает слова.
   // Вообще говоря, надо искать в начальном блоке упоминание схемы и 
   // инициализировать список тэгов-пробелов в зависимости от схемы.
   all_tags_are_wordbreaker = true;
  }

 const char tag1[]="charset=";
 const char tag2[]="encoding=";

 int i0 = lem_find( block.get(), tag1 );
 int tag_len = 8;

 if( i0==UNKNOWN )
  {
   // В XML используется атрибут encoding=XXX
   i0 = lem_find( block.get(), tag2 );
   tag_len = 9;
  }

 if( i0!=UNKNOWN )
  {
   // выделяем название кодировки
   FString coding;

   int i=i0+tag_len;
  
   // В XML кодировка указывается так: encoding="windows-1251"
   //                                           ^------------^
   //
   // а в HTML обычно так:             charset=windows1251
  
   // пропускаем пробелы
   while( i<BLOCK_SIZE )
    if( lem::is_space(block[i]) )
     i++;
    else
     break;

   if( block[i]=='"' || block[i]=='\'' )
    i++;

   while( block[i] )
    {
     if( strchr( " \"'>\r\n", block[i] )!=NULL )
      break;
   
     coding += to_lower( block[i++] );
    } 

   coding.trim();

   if( !coding.empty() )
    format_buffer = string("text/html encoding=") + coding.c_str();

   if( coding==UTF8_1 || coding==UTF8_2 )
    // Следует использовать HTML_UTF8_Decoder,  см. метод Optimize()
    utf8=true;
   else
    {
     try
      {
       cp = lem::CodeConverter::getConverter( coding.c_str() );
      }
     catch(...)
      {
       // Возникновение ошибки однозначно вызывается отсутствием поддержки для 
       // кодировки. Поэтому подавляем исключение - чтобы попытаться организовать
       // обработку другими средствами.
      }
 
     if( !cp )
      {
       #if defined LEM_ICU
        // Будем использовать более универсальную, но менее эффективную схему
        // с перекодировкой средствами IBM ICU
        icu = true; 
       #else
        throw E_BaseException( wstring(L"Unknown encoding of HTML document: ")+to_wstr(coding.c_str()) );
       #endif  
      }
    } 
  }

 bin->seekp(0);

 if( !utf8 && cp==NULL && missing_cp!=NULL )
  cp = missing_cp;

 return; 
}


HTML_Decoder* HTML_Decoder::Optimize(void)
{
 if( utf8 )
  {
   HTML_UTF8_Decoder *ret = new HTML_UTF8_Decoder( bin );
   ret->all_tags_are_wordbreaker = all_tags_are_wordbreaker;
   return ret;
  }
 #if defined LEM_ICU
 else if( icu )
  {
   HTML_ICU_Decoder *ret = new HTML_ICU_Decoder( bin );
   ret->all_tags_are_wordbreaker = all_tags_are_wordbreaker;
   return ret;
  }
 #endif

 return this;
}


wchar_t HTML_Decoder::get2(void)
{
 if( back_ch )
  {
   int ch=back_ch;
   back_ch=0;
   return ch;
  }

 int ch = bin->get();

 if( ch==-1 )//WEOF ) // fixed: 09.07.2007
  return ch;

 if( cp!=NULL && cp->IsSingleByte() )
  {
   return ((SBCodeConverter*)(cp))->to_unicode(ch);
  }
 else
  {
   LEM_STOPIT;
   return WEOF;
  }
}


// Читаем очередной символ из SGML-потока, попутно декодируя
// последовательности типа &#NNNN и &xxxx;
wchar_t HTML_Decoder::Read_Char(void)
{
 last_char_pos = bin->tellp();
 wchar_t ch = get2();

//static int count=0;
//count++;
//printf( "%d char=%d\n", count, ch );
 
parse_ampersand:;

 if( ch==L'&' )
  {
   // С символа & начинаются именованные символы (HTML ENTITY) типа &amp;
   // Считываем имя символа до ;
   string name;
   while( !eof() )
    {
     wchar_t ch2 = get2();

     if( ch2==WEOF )
      break;

     if( ch2==L'#' && name.empty() )
      {
       // Символ кодирован в UNICODE.
       int radix=10;
        
       while( !eof() )
        {
         wchar_t ch2 = get2();

         if( ch2==WEOF )
          break;

         // По стандарту числовое определение UNICODE символа
         // должно заканчиваться ';', но есть коряво сделанные файлы,
         // где цифры терминируются произвольным символом, который надо вернуть
         // для чтения.
         if( ch2==L';' || ch2==L'\r' || ch2==L'\n' || is_uspace(ch2) )
          break;

         if( (ch2==L'x' || ch2==L'X') && name.empty() )
          {
           radix=16;
           continue;  
          }

         if( !is_udigit(ch2) )
          {
           unget(ch2);
           break;
          }

         name += static_cast<char>(ch2);
        }

       lem::int32_t res=0;

       if( to_int( name.c_str(), &res, radix ) )
        return static_cast<wchar_t>(res);

       return L' ';
      }

     // бежим до конца имени
     if( ch2==L';' || ch2==L'\r' || ch2==L'\n' || is_uspace(ch2) )
      break;

     name += static_cast<char>(ch2);
    }

   // теперь преобразуем в одиночный символ.
   if( name.length()<2 )
    return L' ';

   wchar_t res = lem::CodeConverter::Sgml_2_Char( name.c_str() );

   if( !res )
    res = L' ';

   return res;
  }

 if( ch==L'<' && strip_decoration )
  {
   // начало тега. Тег полностью пропускаем.
   // Некоторые тэги <p>, </p>, <br>, <hN>, </hN>, <table>, <td>, <tr>,
   // <th>, <div> заменяются на пробелы, так как могут делить слова
   ch = 0;
   int count=0, itag=0;
   bool tag_extracted=false;
   lem::WCharBuffer tag(32);

   while( !ch && !eof() )
    {
     wchar_t ch_prev=0;
     wchar_t ch2=0;
     while( !eof() && itag<CastSizeToInt(tag.Size()) )
      {
       ch_prev = ch2; 
       ch2 = get2();

       if( ch2==WEOF )
        break;

       count++;

       if( count==1 && ch2==L'/' )
        continue;

       // бежим до конца тэга.
       // Нам нужно выделить имя тэга.
       if( !tag_extracted )
        {
         if( !is_ualpha(ch2) )
          {
           tag_extracted=true;
           tag[itag]=0;  
          }
         else
          {
           tag[itag++] = towlower(ch2);
           continue;
          }
        } 

       // Встречаются HTML файлы, сверстанные с разрывами строк ВНУТРИ тела тэгов,
       // поэтому прерывать извлечение тэга по символам \r и \b нежелательно.
       // Хотя встречаются уродливые файлы, в которых тэги остаются незакрытими, 
       // поэтому приходится контролировать длину тела тэга.
       if( ch2==L'>' /*|| ch2==L'\r' || ch2==L'\n'*/  || count>=1024 )
        break;
      }

     if( all_tags_are_wordbreaker )
      return L' ';
     else if( itag==1 )
      {
       if( tag[0]==L'p' )
        return L' ';
      }
     else if( itag==2 )
      {
       if(
          (tag[0]==L'h' && lem::is_udigit(tag[1]) ) ||
          !wcscmp( tag, L"br" ) ||
          !wcscmp( tag, L"td" ) ||
          !wcscmp( tag, L"tr" ) ||
          !wcscmp( tag, L"th" ) 
         )
        return L' ';
      } 
     else if( itag==3 )
      {
       if(
          !wcscmp( tag, L"div" )
         )
        return L' '; 
      } 
     else if( itag==4 )
      {
       if(
          !wcscmp( tag, L"body" ) ||
          !wcscmp( tag, L"head" )
         )
        return L' '; 
      } 
     else if( itag==5 )
      {
       if(
          !wcscmp( tag, L"table" ) ||
          !wcscmp( tag, L"frame" ) ||
          !wcscmp( tag, L"title" )
         )
        return L' '; 
      } 

     // Тут рекурсивный вызов... Тэги могут следовать один за другим.
//     ch = Read_Char();
     ch = get2();
     if( ch==L'<' )
      { count=0; itag=0; ch=0; tag_extracted=false; }
     else
      {
       if( ch==L'&' )
        { 
         // Значит здесь идет определение символа типа &nbsp;
//       unget(ch);
//       ch = Read_Char();
         goto parse_ampersand;
        } 
       else
        {
         // Нормальный символ, возвращаем его. 
         return ch;
        } 
      }
    }
  }
 else if( ch==L'\n' || ch=='\r' || ch=='\t' )
  return L' ';
  
 return ch;
}


// *************************************************************************


HTML_UTF8_Decoder::HTML_UTF8_Decoder( lem::Ptr<Stream> File )
: HTML_Decoder(File,NULL,NULL,false)
{
}

HTML_UTF8_Decoder::HTML_UTF8_Decoder(void)
: HTML_Decoder()
{
}


/*
   ------ UCS-4 ------   ------------------- UTF-8 ---------------------------  
   0000 0000-0000 007F   0xxxxxxx
   0000 0080-0000 07FF   110xxxxx 10xxxxxx
   0000 0800-0000 FFFF   1110xxxx 10xxxxxx 10xxxxxx
   0001 0000-001F FFFF   11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
   0020 0000-03FF FFFF   111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
   0400 0000-7FFF FFFF   1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
*/

/* Based on RFC2279 */

inline bool BYTE6( unsigned char code ) { return (code & 0xfe) == 0xfc; }
inline bool BYTE5( unsigned char code ) { return (code & 0xfc) == 0xf8; }
inline bool BYTE4( unsigned char code ) { return (code & 0xf8) == 0xf0; }
inline bool BYTE3( unsigned char code ) { return (code & 0xf0) == 0xe0; }
inline bool BYTE2( unsigned char code ) { return (code & 0xe0) == 0xc0; }
inline bool BYTE1( unsigned char code ) { return code <= 0x7f; }

#define CLEAR_MSB(code)	 (code & (~0x80))

wchar_t HTML_UTF8_Decoder::get2(void)
{
 lem::uint8_t u4 = bin->get();

 lem::uint32_t uni = 0;

 if( BYTE4(u4) )
  {
   lem::uint8_t u3 = bin->get();
   lem::uint8_t u2 = bin->get();
   lem::uint8_t u1 = bin->get();

   uni = ((u4 & 0x7) << 2) | ((u3 >> 4) & 0x3);
   uni = (uni << 8) | ((u3 & 0xf) << 4 | ((u2 >> 2) & 0xf));
   uni = (uni << 8) | ((u2 & 0x3) << 6 | (u1 & 0x3f));
  }
 else if (BYTE3(u4) )
  {
   lem::uint8_t u3 = u4;
   lem::uint8_t u2 = bin->get();
   lem::uint8_t u1 = bin->get();

   uni = (u3 & 0xf);
   uni = (uni << 4) | ((u2 >> 2) & 0xf);
   uni = (uni << 8) | ((u2 & 0x3) << 6 | (u1 & 0x3f));
  }
 else if (BYTE2(u4) )
  {
   /* Ok, First six bit of the 1st byte goes to the first six bits in the
    * first byte. Then bits # 0, 1 in the 2nd byte goes to bits # 6, 7 in
    * the first byte. So we're done with the first byte.
    * Then bits # 2-4 from the 2nd byte goes to the bits # 0-2 in the 2nd
    * byte. So we're done!
    */
   lem::uint8_t u2 = u4;
   lem::uint8_t u1 = bin->get();

   uni = (u2 >> 2) & 0x7;
   uni = (uni << 8) | ((u2 & 0x3) << 6 | (u1 & 0x3f));
  }
 else if (BYTE1(u4) )
  uni = u4;

 return static_cast<wchar_t>(uni);
}


// **************************************************************************

#if defined LEM_ICU

HTML_ICU_Decoder::HTML_ICU_Decoder( lem::Ptr<Stream> File )
: HTML_Decoder(File,NULL,false)
{
 icu_reader = new ICU_Reader( cp, File );
}


HTML_ICU_Decoder::~HTML_ICU_Decoder(void)
{
 LEM_CHECKIT_Z(icu_reader);
 lem_rub_off(icu_reader);
}

Stream::pos_type HTML_ICU_Decoder::seekp( off_type pos, int whereto )
{
 return icu_reader->seekp(pos,whereto);
}


wchar_t HTML_ICU_Decoder::get2(void)
{
 return icu_reader->Read_Char();
}

#endif
