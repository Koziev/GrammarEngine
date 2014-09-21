// -----------------------------------------------------------------------------
// File LEM_TIME.CPP
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
// LEM C++ library  http://www.solarix.ru
// Классы и процедуры работы со временем и датами. Преобразование между
// внутренним бинарным представлением и текстовым в разных форматах.
//
// 30.09.2005 - рефакторинг: используется Boost.Date_Time
// 27.11.2005 - добавлена функция timestamp() для удобства формирования отметок
//              о текущем времени в журналах  
// 29.03.2008 - переработан класс ElapsedTime для замера затраченного времени,
//              он теперь использует boost::posix_time::ptime 
// -----------------------------------------------------------------------------
//
// CD->13.09.1996
// LC->29.03.2008
// --------------

#include <lem/config.h>
#include <lem/user_interface.h>
#include <lem/conversions.h>
#include <lem/runtime_checks.h>
#include <lem/date_time.h>

using namespace std;
using namespace boost;
using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace lem;


namespace lem
{ 
 inline bool is_dat_delim( char ch )
 {
  return ch=='.' ||
         ch=='/' ||
         ch==' ' ||
         ch==':' ||
         ch=='-' ||
         ch==' ' ||
         ch=='\\';
 }
}



// ********************************************************************
// Returns the name of month given number MM. Language is also pointed
// by argument 'Language'.
// ********************************************************************
static const UFString get_month_name( int MM )
{
 return lem::UI::get_UI().GetMonthW(MM);
}


static const UFString get_month_name1( int MM )
{
 return lem::UI::get_UI().GetMonthFullW(MM);
}


const UCString lem::to_ustr(
                            const boost::posix_time::ptime& t,
                            const char *date_fmt,
                            const char *time_fmt
                           )
{
 return t.is_special() ? UCString() : (to_ustr( t.date(), date_fmt ) + L' ' + to_ustr( t.time_of_day(), time_fmt ));
}


// ************************************************************************
// Преобразование структуры "ДАТА" в строку по заданному формату.
// По умолчанию формат берется из текущей локали.
// ************************************************************************

const UCString lem::to_ustr( const boost::gregorian::date& d, const char *to_fmt )
{
 if( !to_fmt )
  throw ECheckFault( to_wstr( "Incorrect date format=NULL" ) );

 if( d.is_special() )
  // непредставимая дата.
  return L"";

 // Разбираем форматную строку на фрагменты
 int n_part=0;
 lem::FString part[5];
 bool zero_leading=false;

 int i=0;
 while( to_fmt[i] && n_part<5 )
  {
   if( is_dat_delim(to_fmt[i]) )
    {
     part[n_part++] = to_fmt[i++];
     continue;
    }

   if( to_fmt[i]=='0' )
    {
     if( zero_leading )
      throw ECheckFault( to_wstr("Date format error: ") + to_wstr(to_fmt) );

     zero_leading = true;
     i++;
     continue;
    }

   char c = toupper(to_fmt[i]);

   if(
      c=='D' ||
      c=='M' ||
      c=='Y'
     )
    {
     string s = zero_leading ? "0" : "";
     s += to_fmt[i++];

     while( to_fmt[i] && toupper(to_fmt[i])==c )
      {
       s += to_fmt[i++];
      } 
       
     part[n_part++] = s;
    }
  }



 // Теперь синтезируем строку даты

 // Form the yield boost::gregorian::date string according the given format.
 const UFString& Month = get_month_name( d.month()-1 );
 
 const boost::gregorian::date::ymd_type ymd = d.year_month_day();
 const int Year = ymd.year>=2000 ? ymd.year-2000 : ymd.year-1900;

 const int td = ymd.day;
 const int tm = ymd.month;
 const int ty = ymd.year;
 
 UCString sbuffer;
 

 for( int j=0; j<n_part; j++ )
  {
   if( part[j].eqi( "d" ) )
    {
     // lexical_cast<wstring> убран, так как BCB 6.0 дает ошибку компиляции
     // из-за отсутствующего метода stringstream << wstring  
     sbuffer += to_ustr(td);
    }
   else if( part[j].eqi("dd") || part[j].eqi("0d") )
    {
     if( td<10 )
      sbuffer += L"0";

     sbuffer += to_ustr(td);
    }   
   else if( part[j].eqi("m") )
    {
     sbuffer += to_ustr(tm);
    }   
   else if( part[j].eqi("mm") || part[j].eqi("0m") )
    {
     if( tm<10 )
      sbuffer += L"0";

     sbuffer += to_ustr(tm);
    }   
   else if( part[j].eqi("yy") )
    {
     sbuffer += to_ustr(Year);
    }   
   else if( part[j].eqi("yyyy") )
    {
     sbuffer += to_ustr(ty);
    }   
   else if( part[j].eqi("mmm") )
    {
     sbuffer += Month.c_str();
    }
   else if( part[j].eqi("month") )
    {
     const UFString& Month = get_month_name1( tm-1 );
     sbuffer += Month.c_str();
    }
   else
    {
     sbuffer += part[j].c_str();
    }
  } 
  

/* 
 #if defined LEM_WINDOWS 
 
 if( lem_eq_begin(to_fmt,"dd-mmm-yy") )
  swprintf( buffer, L"%02d-%ws-%02d", td, Month.c_str(), Year );
 if( lem_eq_begin(to_fmt,"dd.mmm.yy") )
  swprintf( buffer, L"%02d.%ws.%02d", td, Month.c_str(), Year );
 if( lem_eq_begin(to_fmt,"DDMMYYYY") )
  swprintf( buffer, L"%02d%02d%04d", td, tm, ty );
 else if( lem_eq_begin(to_fmt,"dd-mmm-yyyy") )
  swprintf( buffer, L"%02d-%ws-%04d", td, Month.c_str(), ty );
 else if( lem_eq_begin(to_fmt,"dd mmm yyyy") )
  swprintf( buffer, L"%02d %ws %04d", td, Month.c_str(), ty );
 else if( lem_eq_begin(to_fmt,"DD.MM.YYYY") || lem_eq_begin(to_fmt,"dd.mm.yyyy") )
  swprintf( buffer, L"%02d.%02d.%04d", td, tm, ty );
 else if( lem_eq_begin(to_fmt,"DD.MM.YY") || lem_eq_begin(to_fmt,"dd.mm.yy") )
  swprintf( buffer, L"%02d.%02d.%02d", td, tm, Year );
 else if( lem_eq_begin(to_fmt,"DD-MM-YYYY") || lem_eq_begin(to_fmt,"dd-mm-yyyy") )
  swprintf( buffer, L"%02d-%02d-%04d", td, tm, ty );
 else if( lem_eq_begin(to_fmt,"DD-MMM-YYYY") )
  {
   swprintf( buffer, L"%02d-%ws-%04d", td, Month.c_str(), ty );
   to_upper( buffer );
  }
 else if( lem_eq_begin(to_fmt,"DD-MMM-YY") )
  {
   swprintf( buffer, L"%02d-%ws-%02d", td, Month.c_str(), Year );
   to_upper( buffer );
  }
 else if( lem_eq_begin(to_fmt,"DD month YYYY") )
  {
   const UCString Month = get_month_name1( tm );
   swprintf( buffer, L"%02d %ws %04d", td, Month.c_str(), ty );
  }
 else
  throw ECheckFault( to_wstr("Unknown boost::gregorian::date format ") + to_wstr(to_fmt) );
 #endif
*/

 return sbuffer;
}


const lem::CString lem::to_str( const boost::gregorian::date& d, const char *to_fmt )
{
 return lem::to_ascii( to_ustr(d,to_fmt) );
}




// ************************************************************************
// Парсинг строки в дату согласно приведенному формату.
//
// org - строка с описанием даты.
// fmt - строка формата
// errf - индикатор ошибки (false - ошибка). Может быть NULL.
// check - генерировать ли исключение при возникновении ошибки.
// ************************************************************************
const boost::gregorian::date lem::parse_date_x(
                                               const char *org,
                                               const char *from_fmt,
                                               bool *errf,
                                               bool check
                                              )
{
 bool dummy;
 if( !errf ) errf = &dummy;

 // Сначала обнуляем индикатор ошибки.
 *errf = true;

 if(
    org==NULL ||
    *org=='\0' ||
    !strcmp(org,"(null)") // Строка (null) порождается printf'ами при печати строки 
                          // по NULL-указателю.
   )
  {
   // Пустая строка - порождает пустую дату.
   return boost::gregorian::date(not_a_date_time);
  }

 LEM_CHECKIT_AZ( from_fmt!=NULL, "Incorrect boost::gregorian::date format" );
 LEM_CHECKIT_AZ( from_fmt!='\0', "Incorrect boost::gregorian::date format" );

 int DD=1, MM=1, YY=2000;

 // ---------------------------------------------------------------
 // Parse the original date string according the specified format.
 // ---------------------------------------------------------------

 CString ms;
 CString ds;
 CString ys;

 if(
    !strlen(from_fmt)                   ||
    lem_eq_begin(from_fmt,"dd-mm-yy")   ||
    lem_eq_begin(from_fmt,"DD-MM-YYYY") ||
    lem_eq_begin(from_fmt,"dd.mm.yyyy") ||
    lem_eq_begin(from_fmt,"dd-mmm-yyyy")
   )
  {
   // ---------------------------
   // Retrieve the DAY number.
   // ---------------------------
   int icur=0;

   while( org[icur]!='\0' && !is_dat_delim(org[icur]) )
    ds += org[icur++];

   if( org[icur]!='\0' )
    icur++;

   // ---------------------------
   // Retrieve the MONTH.
   // ---------------------------

   while( org[icur]!='\0' && !is_dat_delim(org[icur]) )
    ms += org[icur++];

   if( org[icur]!='\0' )
    icur++;

   // ---------------------------
   // Finally, retrieve the YEAR.
   // ---------------------------
   while( org[icur]!='\0' && !is_dat_delim(org[icur]) )
    ys += org[icur++];

   // ---------------------------------------
  }
 else if (
          lem_eq_begin( from_fmt, "yyyy-mm-dd" ) ||
          lem_eq_begin( from_fmt, "YYYY-MM-DD" ) ||
          lem_eq_begin( from_fmt, "yyyy.mm.dd" ) ||
          lem_eq_begin( from_fmt, "YYYY.MM.DD" )
         )
  {
   int icur=0;

   while( org[icur]!='\0' && !is_dat_delim(org[icur]) )
    ys += org[icur++];

   if( org[icur]!='\0' )
    icur++;

   while( org[icur]!='\0' && !is_dat_delim(org[icur]) )
    ms += org[icur++];

   if( org[icur]!='\0' )
    icur++;

   while( org[icur]!='\0' && !is_dat_delim(org[icur]) )
    ds += org[icur++];
  }
 else
  {
   *errf = false;

   if( check )
    LEM_STOPIT_A2( "Data format unknown", from_fmt );
  }

 // --------------------------------------------------
 //  Convert DAY and check it.
 // --------------------------------------------------

 if( !to_int( ds.c_str(), &DD ) || DD<=0 || DD>31 )
  {
   *errf = false;

   if( check )
    {
     LEM_CHECKIT_A2Z( *errf, "Day incorrect in boost::gregorian::date", org );
    }
  }

 // -----------------------------------------------------------
 // Convert MONTH
 // It may be number (01 for example) or name (like 'JAN').
 // -----------------------------------------------------------
 if( !to_int( ms.c_str(), &MM ) )
  {
   ms.to_lower();
   MM = lem::UI::get_UI().FindMonth(ms.c_str());

   if( MM<=0 || MM>12 )
    {
     *errf = false;
     return boost::gregorian::date(not_a_date_time);

//     if( check )
//      {
//       LEM_CHECKIT_A2Z( *errf, "Month incorrect in boost::gregorian::date", org );
//      }
    }

   MM++;
  }
 else
  {
   if( MM<=0 || MM>12 )
    {
     *errf = false;

     if( check )
      LEM_CHECKIT_A2Z( *errf, "Month incorrect in boost::gregorian::date", org );
    }
  }

 // ************************************************
 // Количество дней по месяцам.
 // ************************************************
 int mdays[12]={
                31, 29, 31, 30, 31, 30,
                31, 31, 30, 31, 30, 31
               };

 if( DD>mdays[MM-1] )
  {
   *errf = false;

   if( check )
    LEM_CHECKIT_A2Z( *errf, "Day is out of range for this month", org );
  }

 // Convert YEAR.
 if( !to_int( ys.c_str(), &YY ) )
  {
   *errf = false;

   if( check )
    LEM_CHECKIT_A2Z( *errf, "Year incorrect in boost::gregorian::date", org );
  }

 // 98 -> 1998
 // 00 -> 2000
 if( ys.length()<=2 )
  {
   if( YY < 50 )
    YY += 2000;
   else
    YY += 1900;
  }

 if( YY<=0 )
  {
   *errf = false;
  
   if( check )
    LEM_CHECKIT_A2Z( *errf, "Year incorrect in boost::gregorian::date", org );
  }

 return boost::gregorian::date( YY, MM, DD );
}


const UCString lem::to_ustr( const boost::posix_time::time_duration& t, const char *to_fmt )
{
 LEM_CHECKIT_AZ( to_fmt!=NULL, "Incorrect time format" );

 if( t.is_special() )
  // непредставимое время
  return L"";

 wchar_t buffer[32]=L"";
 
 #if defined LEM_WINDOWS 
 if( !strcmp(to_fmt,"hh:mm:ss") || !strcmp(to_fmt,"HH:MM:SS") )
  swprintf( buffer, L"%02d:%02d:%02d", t.hours(), t.minutes(), t.seconds() );
 else if( !strcmp(to_fmt,"hh-mm-ss") || !strcmp(to_fmt,"HH-MM-SS") )
  swprintf( buffer, L"%02d-%02d-%02d", t.hours(), t.minutes(), t.seconds() );
 else if( !strcmp(to_fmt,"hh/mm/ss") || !strcmp(to_fmt,"HH/MM/SS") )
  swprintf( buffer, L"%02d/%02d/%02d", t.hours(), t.minutes(), t.seconds() );
 else if( !strcmp(to_fmt,"hms") )
  swprintf( buffer, L"%02dh %02dm %02ds", t.hours(), t.minutes(), t.seconds() );
 else if( !strcmp(to_fmt,"hh:mm") )
  swprintf( buffer, L"%02dh:%02dm", t.hours(), t.minutes() );
 else
  LEM_STOPIT_A("Unknown time format");
 #endif  

 return UCString(buffer);
}

const lem::CString lem::to_str( const boost::posix_time::time_duration& t, const char *to_fmt )
{
 return lem::to_ascii( to_ustr( t, to_fmt ) );
}


// *************************************************
// Проверка валидности описания даты.
// Возвращает true, если с датой все нормально.
// *************************************************
bool lem::check_date( const char *org, const char *from_fmt )
{
 bool errf;
 parse_date_x( org, from_fmt, &errf, false );
 return errf;
}

// ******************************************************************
// Преобразование строки во внутренний формат даты с валидизацией и
// генерацией исключений при ошибках.
// ******************************************************************
const boost::gregorian::date lem::to_date( const char *org, const char *from_fmt )
{
 bool errf;
 return parse_date_x( org, from_fmt, &errf, true );
}

const boost::gregorian::date lem::to_date( const wchar_t *org, const char *from_fmt )
{
 bool errf;
 return parse_date_x( to_ascii( UFString(org) ).c_str(), from_fmt, &errf, true );
}

const boost::gregorian::date lem::to_date( const lem::UFString &org, const char *from_fmt )
{
 bool errf;
 return parse_date_x( to_ascii( org ).c_str(), from_fmt, &errf, true );
}

// **********************************
// Возвращает текущий год.
// **********************************
//int lem::cur_year(void)
//{ return get_boost::gregorian::date().year; }



bool lem::check_time( const char *str, const char *fmt )
{
 return to_time( str, fmt, NULL );
}



bool lem::to_time(
                  const char *str,
                  const char *fmt,
                  boost::posix_time::time_duration *t
                 )
{
 if( str==NULL || *str=='\0' )
  {
   *t = not_a_date_time;
   return true;
  }

 int ih=0, im=0, is=0;
 char h[4], m[4], s[4];

 int icur=0;

 // Пропустим пробелы.
 while( fmt[icur] && is_space(fmt[icur]) )
  icur++;

 while( fmt[icur]!='\0' && icur<32 ) // защита от зацикливания
  {
   switch(fmt[icur])
   {
    case 'h':
    case 'H':
     if( !is_digit(str[icur]) )
      return false;

     h[ih++] = str[icur++];
     break;

    case 'm':
    case 'M':
     if( !is_digit(str[icur]) )
      return false;

     m[im++] = str[icur++];
     break;

    case 's':
    case 'S':
     if( !is_digit(str[icur]) )
      return false;

     s[is++] = str[icur++];
     break;

    case ':':
    case '-':
    case '/':
    case '\\':
    case '$':
     if( str[icur]!=fmt[icur] )
      return false;

     icur++;
     break;

    default:
     throw ECheckFault( 
                       to_wstr("Invalid time conversion format string ")+
                       to_wstr(fmt)
                      );
   }
  }

 h[ih] = m[im] = s[is] = '\0';

 const int i_h = to_int(h);
 const int i_m = to_int(m);
 const int i_s = to_int(s);

 if( i_h<0 || i_h>23 )
  return false;

 if( i_m<0 || i_m>59 )
  return false;

 if( i_s<0 || i_s>59 )
  return false;

 if( t!=NULL )
  *t = time_duration(i_h,i_m,i_s);

 return true;
}

const boost::posix_time::time_duration lem::to_time( const char *str, const char *fmt )
{
 boost::posix_time::time_duration res;

 if( !lem::to_time( str, fmt, &res ) )
  throw ECheckFault(
                    to_wstr( "Can not convert string " ) +
                    to_wstr( str ) +
                    to_wstr( " to boost::posix_time::ptime by format " ) +
                    to_wstr( fmt )
                   ); 
 return res;
}


const boost::posix_time::ptime lem::to_ptime( const char *String, const char *Format )
{
 // Общий формат: DD-MM-YYYY HH:MM:SS
 // Отыскиваем пробел - разделитель формата даты и времени
 int i=0;
 while( Format[i] && Format[i]!=' ' )
  i++;

 if( Format[i]==' ' )
  {
   // Выделяем формат даты и времени
   FString fd( Format, Format+i );
   FString ft( Format+i );

   FString sd( String, String+i );
   FString st( String+i );

   boost::gregorian::date d = to_date( sd.c_str(), fd.c_str() );
   boost::posix_time::time_duration t = to_time( st.c_str(), ft.c_str() );

   return boost::posix_time::ptime( d, t );
  }
 else
  {
   // Есть только дата. 
   return boost::posix_time::ptime( to_date( String, Format ), time_duration() );
  }

 return boost::posix_time::ptime(not_a_date_time);
}

UCString lem::timestamp(void)
{
 return to_ustr( boost::posix_time::second_clock::local_time() );
}

const boost::posix_time::ptime lem::get_time(void)
{
 return boost::posix_time::second_clock::local_time();
}

const boost::gregorian::date lem::get_date(void)
{
 return boost::gregorian::day_clock::local_day();
}


#if defined LEM_WINDOWS  
const boost::posix_time::ptime lem::to_ptime( const FILETIME &ft )
{
 SYSTEMTIME st;
 memset( &st, 0, sizeof(st) );
 if( !FileTimeToSystemTime( &ft, &st ) )
  return boost::posix_time::ptime(not_a_date_time);

 boost::posix_time::time_duration t( st.wHour, st.wMinute, st.wSecond );
 boost::gregorian::date d( st.wYear, st.wMonth, st.wDay );

 return boost::posix_time::ptime( d, t );   
}
#endif



ElapsedTime::ElapsedTime(void)
{
 t1 = t0 = lem::get_time();
 stopped=false;
 return;
}

void ElapsedTime::start(void)
{
 t1 = t0 = lem::get_time();
 stopped=false;
 return;
}

void ElapsedTime::stop(void)
{
 t1 = lem::get_time();
 stopped=true;
}

boost::posix_time::ptime ElapsedTime::GetStopTime() const
{
 return stopped ? t1 : lem::get_time(); 
}



boost::posix_time::time_duration ElapsedTime::elapsed(void) const
{ return GetStopTime()-t0; }


int ElapsedTime::msec(void) const
{
 boost::posix_time::time_duration delta = elapsed();
 return delta.total_milliseconds();
}


int ElapsedTime::sec(void) const
{
  boost::posix_time::time_duration delta = elapsed();
 return delta.total_seconds();
}
