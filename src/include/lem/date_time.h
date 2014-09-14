// -----------------------------------------------------------------------------
// File DATE_TIME.H
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ library  http://www.solarix.ru
// –абота со временем и датами. ѕреобразование из/в текстовый формат.
//
// 30.09.2005 - после рефакторинга используетс€ библиотека Boost.Date_Time
// 06.12.2005 - исправлены функции перевода в даты .NET
// 19.01.2007 - реализована сво€ функци€ to_ptime( FILETIME ), так как имеюща€с€
//              в boost глючит.
// -----------------------------------------------------------------------------
//
// CD->13.09.1996
// LC->27.02.2009
// --------------

#ifndef LEM_TIME__H
#define LEM_TIME__H
#pragma once

 #include <lem/config.h>

 #if defined LEM_WINDOWS
  #if defined LEM_MFC
   #include <afxwin.h>
  #else 
   #include <windows.h>
  #endif

  #include <winbase.h>
 #endif

 #if defined LEM_MFC
  #include <atltime.h>
 #endif

 #include <boost/date_time/gregorian/gregorian_types.hpp>
 #include <boost/date_time/posix_time/posix_time_types.hpp>
 #include <boost/date_time/posix_time/conversion.hpp>

 #include <lem/user_interface.h>
 #include <lem/cstring.h>

 #if defined LEM_DOT_NET
  #using <mscorlib.dll>
  #using <system.dll>
 #endif
 
 namespace lem
 {
  extern const boost::gregorian::date parse_date_x(
                                                   const char *org,
                                                   const char *from_fmt,
                                                   bool *errf,
                                                   bool check
                                                  );

  // ѕреобразование строки в дату по заданному формату (либо по формату
  // текущей локали, если формат не задан).
  extern const boost::gregorian::date to_date(
                                              const char *org,
                                              const char *from_fmt=lem::UI::get_UI().GetDateFmt().c_str()
                                             );

  extern const boost::gregorian::date to_date(
                                              const wchar_t *org,
                                              const char *from_fmt=lem::UI::get_UI().GetDateFmt().c_str()
                                             );

  extern const boost::gregorian::date to_date(
                                              const lem::UFString& org,
                                              const char *from_fmt=lem::UI::get_UI().GetDateFmt().c_str()
                                             );

  // ѕроверка, €вл€етс€ ли строка org корректным представлением даты
  // по формату from_fmt (или по формату локали).
  extern bool check_date( const char *org, const char *from_fmt="" );

  // ѕреобразование даты в текстовую строку по заданному формату (либо по формату
  // текущей локали).
  extern const UCString to_ustr(
                                const boost::gregorian::date& d,
                                const char *to_fmt = lem::UI::get_UI().GetDateFmt().c_str()
                               );

  // ѕреобразование времени в строку (формат задаетс€ либо беретс€ из локали)
  extern const UCString to_ustr(
                                const boost::posix_time::time_duration& t,
                                const char *to_fmt = lem::UI::get_UI().GetTimeFmt().c_str()
                               );


  // ѕолучение строки с датой и временем
  extern const UCString to_ustr(
                                const boost::posix_time::ptime& t,
                                const char *date_fmt = lem::UI::get_UI().GetDateFmt().c_str(),
                                const char *time_fmt = lem::UI::get_UI().GetTimeFmt().c_str()
                               );



  extern const CString to_str(
                              const boost::gregorian::date& d,
                              const char *to_fmt = lem::UI::get_UI().GetDateFmt().c_str()
                             );


  extern const CString to_str(
                              const boost::posix_time::time_duration& t,
                              const char *to_fmt = lem::UI::get_UI().GetTimeFmt().c_str()
                             );


  // ѕроверка, €вл€етс€ ли строка корректным представлением времени по заданному
  // формату (либо по формату локали).
  extern bool check_time(
                         const char *str,
                         const char *to_fmt=lem::UI::get_UI().GetTimeFmt().c_str()
                        );


  // *******************************************************************************
  // ѕреобразование строки в бинарное врем€ - по заданному формату fmt, с возвратом
  // флага успешности преобразовани€.
  // *******************************************************************************
  extern bool to_time(
                      const char *str,
                      const char *fmt,
                      boost::posix_time::time_duration *t
                     );

  // *****************************************************************************
  // —окращенна€ верси€ процедуры парсинга строки времени с генерацией исключени€
  // при возникновении ошибок.
  // *****************************************************************************
  extern const boost::posix_time::time_duration to_time( const char *str, const char *fmt );
 
  extern const boost::posix_time::ptime to_ptime( const char *String, const char *Format );


  #if defined LEM_DOT_NET
 
  inline const boost::gregorian::date to_date( System::DateTime &dt )
  { return boost::gregorian::date( boost::gregorian::date( dt.get_Year(), dt.get_Month(), dt.get_Day() ) ); }

  inline const boost::posix_time::ptime to_time( System::DateTime &dt )
  { return boost::posix_time::ptime( 
                                    boost::gregorian::date(
                                                           dt.get_Year(),
                                                           dt.get_Month(),
                                                           dt.get_Day()
                                                          ),
                                    boost::posix_time::time_duration(
                                                         dt.get_Hour(),
                                                         dt.get_Minute(),
                                                         dt.get_Second()
                                                        )
                                   ); }

  inline ::System::DateTime to_dotnet_date( const boost::posix_time::ptime &x )
  {
   if( x.is_special() )
    return ::System::DateTime( 2999, 01, 01 );

   struct tm t = boost::posix_time::to_tm(x);   
   return ::System::DateTime( 1900+t.tm_year, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec );
  }

  inline ::System::DateTime to_dotnet_date( const boost::gregorian::date &x )
  {
   if( x.is_special() )
    return ::System::DateTime( 2999, 01, 01 );

   struct tm t = boost::gregorian::to_tm(x);   
   return ::System::DateTime( t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec );
  }

  #endif


  #if defined LEM_MFC

  inline const boost::gregorian::date to_date( CTime &dt )
  { return boost::gregorian::date( boost::gregorian::date( dt.GetYear(), dt.GetMonth(), dt.GetDay() ) ); }

  inline const boost::posix_time::ptime to_time( CTime &dt )
  { return boost::posix_time::ptime( 
                                    boost::gregorian::date(
                                                           dt.GetYear(),
                                                           dt.GetMonth(),
                                                           dt.GetDay()
                                                          ),
                                    boost::posix_time::time_duration(
                                                                     dt.GetHour(),
                                                                     dt.GetMinute(),
                                                                     dt.GetSecond()
                                                                    )
                                   ); }

  #endif


  extern const boost::posix_time::ptime get_time(void);
  extern const boost::gregorian::date get_date(void);


  // ***************************************************************
  //  ласс дл€ простых (без учета эффектов многозадачности и разных
  // приоритетов процессов) замеров интервалов времени.
  // ***************************************************************
  class ElapsedTime
  {
   private:
    boost::posix_time::ptime t0, t1;
    bool stopped;

    boost::posix_time::ptime GetStopTime() const;

   public:
    ElapsedTime(void);

    void start(void);
    void stop(void);

    boost::posix_time::time_duration elapsed(void) const;

    int msec(void) const;
    int sec(void) const;
  };


  // ***********************************************
  // ¬озвращаетс€ текстова€ строка с представлением
  // текущей даты и времени
  // ***********************************************
  extern UCString timestamp(void);

  #if defined LEM_WINDOWS  
  extern const boost::posix_time::ptime to_ptime( const FILETIME &ft );
  #endif
 } // namespace 'lem'

#endif
