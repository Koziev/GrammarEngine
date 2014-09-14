// -----------------------------------------------------------------------------
// File LEM_DU8.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// Òèï äëÿ ïðåäñòàâëåíèå äåéñòâèòåëüíûõ ÷èñåë ñ ó÷åòîì ïîãðåøíîñòåé ðàñ÷åòà,
// òî÷íîñòü REAL8.
// -----------------------------------------------------------------------------
//
// CD->26.07.96
// LC->28.10.04
// ------------

#if !defined LEM_DUPEL8__H && !defined LEM_NOREAL && !defined LEM_NODUP
#define LEM_DUPEL8__H
#pragma once

 #include <math.h>

 #include <lem/fp8.h>
 #include <lem/runtime_checks.h>

 #undef min
 #undef max

 namespace lem
 {
  namespace Math
  {

 extern REAL8 DOUBLEDIV8;

 #define MAXDUPEL8 MAXREAL8
 #define MINDUPEL8 MINREAL8

 class DUPEL8
 {
  private:
   REAL8 a;
   REAL8 b; // {a+/-b}

   inline const bool IsInside( const REAL8 v ) const
   { return v>=min() && v<=max(); }

  public:
   DUPEL8(void) { a=b=0.; }

   DUPEL8( const REAL8 A )
   {
    // Ñ÷èòàåì, ÷òî ðàçáðîñ - ïîëîâèíà ïîñëåäíåãî çíàêà
    b = Dabs(a=A)*DOUBLEDIV8;
   }

   DUPEL8( const REAL8 A, const REAL8 B ) { a=A; b=B; }

   inline const REAL8 real(void) const { return a; }
   inline const REAL8 diverg(void) const { return b; }
   inline const REAL8 min(void) const { return a-b; }
   inline const REAL8 max(void) const { return a+b; }
   inline const REAL8 error(void) const { return a==0. ? 0. : b/a; }

   friend const DUPEL8 operator+( const DUPEL8 &X,  const DUPEL8 &Y );
   DUPEL8& operator+=( const DUPEL8 &X );

   friend const DUPEL8 operator-( const DUPEL8 &X,  const DUPEL8 &Y );
   DUPEL8& operator-=( const DUPEL8 &X );

   friend const DUPEL8 operator*( const DUPEL8 &X,  const DUPEL8 &Y );
   DUPEL8& operator*=( const DUPEL8 &X );

   friend const DUPEL8 operator/( const DUPEL8 &X,  const DUPEL8 &Y );
   DUPEL8& operator/=( const DUPEL8 &X );

   const DUPEL8 operator-(void) const { return DUPEL8(-a,b); }

   const DUPEL8 operator++(int) { DUPEL8 r(a,b); a++; return r; }
   DUPEL8& operator++(void) { a++; return *this; }

   const DUPEL8 operator--(int) { DUPEL8 r(a,b); a--; return r; }
   DUPEL8& operator--(void) { a--; return *this; }

   friend bool operator==( const DUPEL8 &a, const DUPEL8 &b );
   friend bool operator!=( const DUPEL8 &a, const DUPEL8 &b );
   friend bool operator>(  const DUPEL8 &a, const DUPEL8 &b );
   friend bool operator>=( const DUPEL8 &a, const DUPEL8 &b );
   friend bool operator<(  const DUPEL8 &a, const DUPEL8 &b );
   friend bool operator<=( const DUPEL8 &a, const DUPEL8 &b );

   friend const DUPEL8 DDabs( const DUPEL8 &x );
   friend const DUPEL8 DDsqrt( const DUPEL8 &x );

   friend const DUPEL8 DDsin( const DUPEL8 &x );
   friend const DUPEL8 DDcos( const DUPEL8 &x );
   friend const DUPEL8 DDtan( const DUPEL8 &x );
   friend const DUPEL8 DDsec( const DUPEL8 &x );
   friend const DUPEL8 DDcosec( const DUPEL8 &x );
   friend const DUPEL8 DDcotan( const DUPEL8 &x );

   friend const DUPEL8 DDasin( const DUPEL8 &x );
   friend const DUPEL8 DDacos( const DUPEL8 &x );
   friend const DUPEL8 DDatan( const DUPEL8 &x );
   friend const DUPEL8 DDasec( const DUPEL8 &x );
   friend const DUPEL8 DDacosec( const DUPEL8 &x );
   friend const DUPEL8 DDacotan( const DUPEL8 &x );

   friend const DUPEL8 DDsinh( const DUPEL8 &x );
   friend const DUPEL8 DDcosh( const DUPEL8 &x );
   friend const DUPEL8 DDtanh( const DUPEL8 &x );
   friend const DUPEL8 DDsech( const DUPEL8 &x );
   friend const DUPEL8 DDcosech( const DUPEL8 &x );
   friend const DUPEL8 DDcotanh( const DUPEL8 &x );

   friend const DUPEL8 DDasinh( const DUPEL8 &x );
   friend const DUPEL8 DDacosh( const DUPEL8 &x );
   friend const DUPEL8 DDatanh( const DUPEL8 &x );
   friend const DUPEL8 DDasech( const DUPEL8 &x );
   friend const DUPEL8 DDacosech( const DUPEL8 &x );
   friend const DUPEL8 DDacotanh( const DUPEL8 &x );

   friend const DUPEL8 DDexp( const DUPEL8 &x );
   friend const DUPEL8 DDlog( const DUPEL8 &x );
   friend const DUPEL8 DDlog10( const DUPEL8 &x );

   friend const DUPEL8 DDfloor( const DUPEL8 &x );
   friend const DUPEL8 DDceil( const DUPEL8 &x );

   friend const DUPEL8 DDpow( const DUPEL8 &x, const DUPEL8 &y );
   friend const DUPEL8 DDpow2( const DUPEL8 &x );
   friend const DUPEL8 DDpow3( const DUPEL8 &x );
   friend const DUPEL8 DDpow10( const int n );
   friend const DUPEL8 DDatan2( const DUPEL8 &x, const DUPEL8 &y );

   friend const DUPEL8 DDmod( const DUPEL8 &x, const DUPEL8 &y );
   friend const DUPEL8 DDmodf( const DUPEL8 &x, DUPEL8 *y );
   friend const DUPEL8 DDrexp( const DUPEL8 &x );
   friend const DUPEL8 DDldexp( const DUPEL8 &x );

   friend const int DDroundi( const DUPEL8 &x );
   friend const long DDroundl( const DUPEL8 &x );

   friend const DUPEL8 DDmax( const DUPEL8 &x, const DUPEL8 &y );
   friend const DUPEL8 DDmin( const DUPEL8 &x, const DUPEL8 &y );
   friend const DUPEL8 DDmax( const DUPEL8 &x, const DUPEL8 &y, const DUPEL8 &z );
   friend const DUPEL8 DDmin( const DUPEL8 &x, const DUPEL8 &y, const DUPEL8 &z );
 };

 inline const DUPEL8 operator+( const DUPEL8 &X, const DUPEL8 &Y )
 {
  DUPEL8 Z;
  Z.a = X.a+Y.a;
  Z.b = X.b+Y.b;
  return Z;
 }

 inline DUPEL8& DUPEL8::operator+=( const DUPEL8 &X )
 {
  a += X.a;
  b += X.b;
  return *this;
 }

 inline const DUPEL8 operator-( const DUPEL8 &X, const DUPEL8 &Y )
 {
  DUPEL8 Z;
  Z.a = X.a-Y.a;
  Z.b = X.b+Y.b;
  return Z;
 }

 inline DUPEL8& DUPEL8::operator-=( const DUPEL8 &X )
 {
  a -= X.a;
  b += X.b;
  return *this;
 }

 inline const DUPEL8 operator*( const DUPEL8 &X, const DUPEL8 &Y )
 {
  DUPEL8 Z;

  Z.a=X.a*Y.a;
  Z.b = (Dabs(X.a*Y.b)+Dabs(Y.a*X.b));
  return Z;
 }

 inline DUPEL8& DUPEL8::operator*=( const DUPEL8 &Y )
 {
  a *= Y.a;
  b = Dabs(a*Y.b)+Dabs(Y.a*b);
  return *this;
 }

 inline const DUPEL8 operator/( const DUPEL8 &X,  const DUPEL8 &Y )
 {
  DUPEL8 Z;

  Z.a = X.a/Y.a;

  REAL8 den = Y.a*Y.a - Y.b*Y.b;
  Z.b = ( Dabs(X.a*Y.b)+Dabs(Y.a*X.b) ) /Dabs(den);

  return Z;
 }

 inline DUPEL8& DUPEL8::operator/=( const DUPEL8 &Y )
 {
  a /= Y.a;

  REAL8 den = Y.a*Y.a - Y.b*Y.b;
  b = ( Dabs(a*Y.b)+Dabs(Y.a*b) ) / Dabs(den);
  return *this;
 }

 //            ÎÏÅÐÀÒÎÐÛ ÑÐÀÂÍÅÍÈß

 inline bool operator==( const DUPEL8 &a, const DUPEL8 &b )
 { return a.a==b.a; }

 inline bool operator!=( const DUPEL8 &a, const DUPEL8 &b )
 { return a.a!=b.a; }

 inline bool operator>( const DUPEL8 &a, const DUPEL8 &b )
 { return a.a > b.a; }

 inline bool operator<( const DUPEL8 &a, const DUPEL8 &b )
 { return a.a < b.a; }

 inline bool operator>=( const DUPEL8 &a, const DUPEL8 &b )
 { return a.a >= b.a; }

 inline bool operator<=( const DUPEL8 &a, const DUPEL8 &b )
 { return a.a <= b.a; }

 //               ÒÐÈÃÎÍÎÌÅÒÐÈ×ÅÑÊÈÅ ÔÓÍÊÖÈÈ

 inline const DUPEL8 DDsin( const DUPEL8 &x )
 {
  const REAL8 res = Dsin(x.a);
  const REAL8 err = Dabs(Dcos(x.a)*x.b);
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDcos( const DUPEL8 &x )
 {
  const REAL8 res = Dcos(x.a);
  const REAL8 err = Dabs(Dsin(x.a)*x.b);
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDsec( const DUPEL8 &x )
 {
  const REAL8 res = Dsec(x.a);
  const REAL8 err = Dabs(x.b*Dsin(x.a)/Dpow2(Dcos(x.a)));
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDcosec( const DUPEL8 &x )
 {
  const REAL8 res = Dcosec(x.a);
  const REAL8 err = Dabs(x.b*Dcos(x.a)/Dpow2(Dsin(x.a)));
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDtan( const DUPEL8 &x )
 {
  const REAL8 res = Dtan(x.a);
  const REAL8 err = x.b/Dpow2(Dcos(x.a));
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDcotan( const DUPEL8 &x )
 {
  const REAL8 res = Dcotan(x.a);
  const REAL8 err = x.b/Dpow2(Dsin(x.a));
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 // ÎÁÐÀÒÍÛÅ ÒÐÈÃÎÍÎÌÅÒÐÈ×ÅÑÊÈÅ ÔÓÍÊÖÈÈ

 inline const DUPEL8 DDasin( const DUPEL8 &x )
 {
  const REAL8 res = Dasin(x.a);
  const REAL8 err = x.b/Dsqrt(1.-Dpow2(x.a));
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDacos( const DUPEL8 &x )
 {
  const REAL8 res = Dacos(x.a);
  const REAL8 err = x.b/Dsqrt(1.-Dpow2(x.a));
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDasec( const DUPEL8 &x )
 {
  const REAL8 res = Dasec(x.a);
  const REAL8 err = x.b / (x.a*Dsqrt(Dpow2(x.a)-1.) );
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDacosec( const DUPEL8 &x )
 {
  const REAL8 res = Dacosec(x.a);
  const REAL8 err = x.b / (x.a*Dsqrt(Dpow2(x.a)-1.) );
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDatan( const DUPEL8 &x )
 {
  const REAL8 res = Datan(x.a);
  const REAL8 err = x.b/(1.+Dpow2(x.a));
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDacotan( const DUPEL8 &x )
 {
  const REAL8 res = Dacotan(x.a);
  const REAL8 err = x.b/(1.+Dpow2(x.a));
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDatan2( const DUPEL8 &x, const DUPEL8 &y )
 {
  const REAL8 res = atan2(x.a,y.a);
  // ATT !!! Ñêîððåêòèðóé ïðîèçâîäíóþ.
  const REAL8 err = x.b /(1.+Dpow2(x.a)) + Dabs(x.a*y.b) + Dabs(y.a*x.b);
  return DUPEL8(res,res*(err+DOUBLEDIV8));
 }

 // ÃÈÏÅÐÁÎËÈ×ÅÑÊÈÅ ÔÓÍÊÖÈÈ

 inline const DUPEL8 DDsinh( const DUPEL8 &x )
 {
  const REAL8 res = Dsinh(x.a);
  const REAL8 err = Dcosh(x.a)*x.b;
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDcosh( const DUPEL8 &x )
 {
  const REAL8 res = Dcosh(x.a);
  const REAL8 err = Dsinh(x.a)*x.b;
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDsech( const DUPEL8 &x )
 {
  const REAL8 res = Dsech(x.a);
  const REAL8 err = Dabs(x.b*Dsinh(x.a)/Dpow2(Dcosh(x.a)));
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDcosech( const DUPEL8 &x )
 {
  const REAL8 res = Dcosech(x.a);
  const REAL8 err = Dabs(x.b*Dcosh(x.a)/Dpow2(Dsinh(x.a)));
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDtanh( const DUPEL8 &x )
 {
  const REAL8 res = Dtanh(x.a);
  const REAL8 err = x.b/Dpow2(Dcosh(x.a));
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDcotanh( const DUPEL8 &x )
 {
  const REAL8 res = Dcotanh(x.a);
  const REAL8 err = x.b/Dpow2(Dsinh(x.a));
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 // ÎÁÐÀÒÍÛÅ ÃÈÏÅÐÁÎËÈ×ÅÑÊÈÅ ÔÓÍÊÖÈÈ

 inline const DUPEL8 DDasinh( const DUPEL8 &x )
 {
  const REAL8 res = Dasinh(x.a);
  const REAL8 err = x.b / Dsqrt(Dpow2(x.a)+1.);
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDacosh( const DUPEL8 &x )
 {
  const REAL8 res = Dacosh(x.a);
  const REAL8 err = x.b / Dsqrt(Dpow2(x.a)-1.);
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDasech( const DUPEL8 &x )
 {
  const REAL8 res = Dasech(x.a);
  // ???
  const REAL8 err = x.b / (Dpow2(x.a)*Dsqrt(Dpow2(x.a)-1.) );
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDacosech( const DUPEL8 &x )
 {
  const REAL8 res = Dacosech(x.a);
  // ???
  const REAL8 err = x.b / (Dpow2(x.a)*Dsqrt(Dpow2(x.a)+1.) );
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDatanh( const DUPEL8 &x )
 {
  const REAL8 res = Datanh(x.a);
  const REAL8 err = x.b / (1.-Dpow2(x.a));
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDacotanh( const DUPEL8 &x )
 {
  const REAL8 res = Dcotanh(x.a);
  const REAL8 err = x.b / (1.-Dpow2(x.a));
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 //  ÑÒÅÏÅÍÍÛÅ, ÏÎÊÀÇÀÒÅËÜÍÛÅ È ËÎÃÀÐÈÔÌÈ×ÅÑÊÈÅ ÔÓÍÊÖÈÈ

 inline const DUPEL8 DDsqrt( const DUPEL8 &x )
 {
  const REAL8 res = Dsqrt(x.a);
  const REAL8 err = x.a==0. ? 0. : x.b / (2.*Dsqrt(x.a));
  return DUPEL8( res, err+res*DOUBLEDIV8 );
 }

 inline const DUPEL8 DDexp( const DUPEL8 &x )
 {
  const REAL8 res = Dexp(x.a);
  const REAL8 err = res*x.b;
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDlog( const DUPEL8 &x )
 {
  const REAL8 res = Dlog(x.a);
  const REAL8 err = Dabs(x.b / x.a);
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDlog10( const DUPEL8 &x )
 {
  const REAL8 res = Dlog(x.a);
  const REAL8 err = Dabs(x.b*0.43 / x.a);
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDpow2( const DUPEL8 &x )
 {
  const REAL8 res = Dpow2(x.a);
  const REAL8 err = Dabs(2.*x.b*x.a);
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDpow3( const DUPEL8 &x )
 {
  const REAL8 res = Dpow3(x.a);
  const REAL8 err = 3.*x.b*Dpow2(x.a);
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDpow( const DUPEL8 &x, const DUPEL8 &y )
 {
  const REAL8 res = Dpow(x.a,y.a);
  const REAL8 err = Dsqrt( Dpow2(Dlog(x.a)*y.b)+Dpow2(y.a/x.a*x.b) ) * res;
  return DUPEL8(res,err+res*DOUBLEDIV8);
 }

 inline const DUPEL8 DDpow10( const int n )
 { return DUPEL8(Dpow(10,n)); }

 //             ÏÐÎ×...

 inline const DUPEL8 DDfloor( const DUPEL8 &x )
 { return DUPEL8(Dfloor(x.a),0); }

 inline const DUPEL8 DDceil( const DUPEL8 &x )
 { return DUPEL8(Dceil(x.a),0); }

 // -------------------------------------------------------------------

 inline const DUPEL8 DDmod( const DUPEL8 &x, const DUPEL8 &y )
 {
  const REAL8 res = Dmod(x.a,y.a);
  const REAL8 err = 0;
  LEM_STOPIT;
  return DUPEL8(res,res*(err+DOUBLEDIV8));
 }

 inline const DUPEL8 DDmodf( const DUPEL8 &x, DUPEL8 *y )
 {
  LEM_STOPIT;
  return 0.;
 }

 inline const DUPEL8 DDrexp( const DUPEL8 &x )
 {
  LEM_STOPIT;
  return 0.;
 }

 inline const DUPEL8 DDldexp( const DUPEL8 &x )
 {
  LEM_STOPIT;
  return 0.;
 }

 inline const DUPEL8 DDabs( const DUPEL8 &x )
 { return DUPEL8( Dabs(x.a), x.b ); }

 inline const int DDroundi( const DUPEL8 &x )
 { return x.a>=0. ? int(x.a) : int(x.a-1.); }

 inline const long DDroundl( const DUPEL8 &x )
 { return x.a>=0. ? long(x.a) : long(x.a-1.); }

 inline const DUPEL8 DDmax( const DUPEL8 &x, const DUPEL8 &y )
 { return x>y ? x : y; }

 inline const DUPEL8 DDmin( const DUPEL8 &x, const DUPEL8 &y )
 { return x<y ? x : y; }

 inline const DUPEL8 DDmax( const DUPEL8 &x, const DUPEL8 &y, const DUPEL8 &z )
 { return DDmax( x, DDmax( y, z ) ); }

 inline const DUPEL8 DDmin( const DUPEL8 &x, const DUPEL8 &y, const DUPEL8 &z )
 { return DDmin( x, DDmin( y, z ) ); }

 extern const DUPEL8 DDmin( const DUPEL8 *x, const int n );
 extern const DUPEL8 DDmax( const DUPEL8 *x, const int n );
 extern void DDminmax( const DUPEL8 *x, const int n, DUPEL8 &MIN, DUPEL8 &MAX );
 extern void DDminmax( const DUPEL8 **Z, const int NX, int NY, DUPEL8 &zmin, DUPEL8 &zmax );

 inline const DUPEL8 DDRadToGrad( const DUPEL8 &rad )
 { return rad*57.295779513082320876798155; }

 inline const DUPEL8 DDGradToRad( const DUPEL8 &gr )
 { return gr*0.017453292519943295769237; }

 #if defined NOREAL10
  typedef DUPEL8 DUPEL10;
 #endif

 #if defined DEFREAL8 || defined DEFDUP8
  typedef DUPEL8 DUPEL;
 #endif

  } // namespace Math
 } // namespace lem
#endif
// --------------------------- End Of File [LEM_DU8.H] -------------------------
