#ifndef LEM_NULLABLE__H
#define LEM_NULLABLE__H
#pragma once

 #include <lem/runtime_checks.h>
 #include <lem/ufstring.h>
 #include <lem/fstring.h>
 #include <lem/ucstring.h>
 #include <lem/cstring.h>
 #include <lem/date_time.h>

 namespace lem
 {
  template < class T >
  struct Nullable
  {
   /*typename*/ T value; 
   bool nil;
   
   Nullable() : value(), nil(true) {}
   Nullable( T t ) : value(t), nil(false) {}
   Nullable( const Nullable<T>& x ) : value(x.value), nil(x.nil) {}
   
   const Nullable<T>& operator=( T t ) { value=t; nil=false; return *this; }
   const Nullable<T>& operator=( const Nullable<T>& x ) { value=x.value; nil=x.nil; return *this; }

   inline bool IsNull(void) const { return nil; } 
   inline bool NotNull(void) const { return !nil; }
   inline void SetNull(void) { nil=true; }

   inline bool operator==( T t ) const
   { return !nil && value==t; }

   inline bool operator!=( T t ) const
   { return !nil && value!=t; }

   inline bool operator==( const Nullable<T>& x ) const
   { return !nil && !x.nil && value==x.value; }

   inline bool operator!=( const Nullable<T>& x ) const
   { return !nil && !x.nil && value!=x.value; }

   inline operator T(void) const { LEM_CHECKIT_Z(!nil); return value; }
   inline const T& get(void) const { LEM_CHECKIT_Z(!nil); return value; }
  };

  extern lem::UFString to_ustr( const Nullable<lem::UFString> &x );
  extern lem::FString to_str( const Nullable<lem::FString> &x );
  extern lem::UCString to_ustr( const Nullable<int> &x, int radix=10 );
  extern lem::CString to_str( const Nullable<int> &x, int radix=10 );
  extern lem::CString to_str( const lem::Nullable<double> &x, const char *Format="%g" );
  extern lem::UCString to_ustr( const lem::Nullable<double> &x, const char *Format="%g" );
  extern lem::UCString to_ustr( const Nullable<bool> &x );
  extern lem::CString to_str( const Nullable<bool> &x );

  extern lem::UCString to_ustr( const Nullable<boost::gregorian::date>& d,
                                const char *to_fmt = lem::UI::get_UI().GetDateFmt().c_str()
                               );

  extern lem::UCString to_ustr(
                               const Nullable<boost::posix_time::time_duration>& t,
                               const char *to_fmt = lem::UI::get_UI().GetTimeFmt().c_str()
                              );


  extern lem::UCString to_ustr(
                               const Nullable<boost::posix_time::ptime>& t,
                               const char *date_fmt = lem::UI::get_UI().GetDateFmt().c_str(),
                               const char *time_fmt = lem::UI::get_UI().GetTimeFmt().c_str()
                              );



  extern lem::CString to_str(
                             const Nullable<boost::gregorian::date>& d,
                             const char *to_fmt = lem::UI::get_UI().GetDateFmt().c_str()
                            );


  extern lem::CString to_str(
                             const Nullable<boost::posix_time::time_duration>& t,
                             const char *to_fmt = lem::UI::get_UI().GetTimeFmt().c_str()
                            );

 }

#endif
