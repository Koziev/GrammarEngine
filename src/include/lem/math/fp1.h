// -----------------------------------------------------------------------------
// File FP1.H
//
// (c) Koziev Elijah
//
// Contens:
// Специализированный класс для работы с действительными числами в диапазоне
// [-1.00,+1.00] (вероятностями). Имеет размер 1 байт, и реализован через
// целочисленную арифметику. Реально представимый диапазон немного больше,
// примерно (+/- 1.20)
//
// 16.07.2008 - небольшие правки декларация для компиляции в GCC 4.x
// -----------------------------------------------------------------------------
//
// CD->24.07.1996
// LC->02.02.2009
// --------------

#ifndef LEM_REAL1__H
#define LEM_REAL1__H
#pragma once

 #include <lem/cstring.h>
 #include <lem/runtime_checks.h>
 #include <lem/containers.h>

 namespace lem
 {
  class Real1
  {
   private:
    unsigned char a; // Числитель дроби, число получается как a/100.
                     // Все арифметические операции выполняются с предположением,
                     // что знаменатель равен именно 100.
                     // Допустимый диапазон числителя принят как 0...120

    friend Real1 to_fp1( const wchar_t* src );

    // ************************************************
    // Преобразование в строковый формат типа "0.85"
    // ************************************************
    friend const UCString to_ustr( Real1 x );
    friend const CString  to_str(  Real1 x );

   public:
    // Default constructor - для удобства неинициализированное число равно 0.
    Real1(void):a(0) {}

    explicit Real1( int iA )
    {
     // Контролируем поддерживаемый диапазон.
     LEM_CHECKIT_Z( iA>=0 && iA<=120 );
     a=static_cast<unsigned char>(iA);
    }

    explicit Real1( double rA )
    {
     LEM_CHECKIT_Z( rA>=0 && rA<=1.2 );
     a=static_cast<unsigned char>(100*rA);
    }

    inline Real1& operator=( int iA )
    {
     LEM_CHECKIT_Z( iA>=0 && iA<=120 );
     a=static_cast<unsigned char>(iA);
     return *this;
    }

    inline Real1& operator=( double rA )
    {
     LEM_CHECKIT_Z( rA>=0 && rA<=1.2 );
     a=static_cast<unsigned char>(100*rA);
     return *this;
    }

    inline bool operator==( int b )   const { return a==b; }
    inline bool operator!=( int b )   const { return a!=b; }
    inline bool operator==( Real1 b ) const { return a==b.a; }
    inline bool operator!=( Real1 b ) const { return a!=b.a; }

    friend Real1 operator+( Real1 x, Real1 y );
    friend Real1 operator-( Real1 x, Real1 y );
    friend Real1 operator*( Real1 x, Real1 y );
    friend Real1 operator/( Real1 x, Real1 y );

    friend bool operator<(  Real1 x, Real1 y );
    friend bool operator<=( Real1 x, Real1 y );
    friend bool operator>(  Real1 x, Real1 y );
    friend bool operator>=( Real1 x, Real1 y );

    inline int GetInt(void) const { return (int)a; }

    Real1& operator*=( Real1 y );

    inline float GetFloat(void) const { return float(a)/float(100.); }
  };

  // *************************************************
  //   *** РЕАЛИЗАЦИИ АРИФМЕТИЧЕСКИХ ОПЕРАТОРОВ ***
  // *************************************************

  inline Real1 operator*( Real1 x, Real1 y )
  {
   int res = (int(x.a)*int(y.a)) / 100;
   return Real1(res);
  }

  inline Real1& Real1::operator*=( Real1 y )
  {
   a = (int(a)*int(y.a)) / 100;
   LEM_CHECKIT_Z( a<=120 );
   return *this;
  }

  inline Real1 operator+( Real1 x, Real1 y )
  { return Real1(int(x.a)+int(y.a)); }


  inline Real1 operator-( Real1 x, Real1 y )
  { return Real1(int(x.a)-int(y.a)); }


  inline Real1 operator/( Real1 x, Real1 y )
  {
   const long res = ( (int(x.a)*100) * 100l / (int(y.a)*100) );
   return Real1((int)res);
  }

  inline bool operator<( Real1 x, Real1 y )
  { return x.a<y.a; }

  inline bool operator>( Real1 x, Real1 y )
  { return x.a>y.a; }

  inline bool operator<=( Real1 x, Real1 y )
  { return x.a<=y.a; }

  inline bool operator>=( Real1 x, Real1 y )
  { return x.a>=y.a; }


  inline Real1 lem_1max( Real1 x, Real1 y )
  { return x>y ? x : y; }

  inline Real1 lem_1min( Real1 x, Real1 y )
  { return x<y ? x : y; }


  extern Real1 to_fp1( const wchar_t* src );

  typedef MCollect<Real1> Real1Array;

 } // namespace 'lem'

#endif
