#if !defined( IMB_G2D__H )
#define IMB_G2D__H

// -----------------------------------------------------------------------------
// File 2D.H
//
// (c) by Koziev Elijah
//
// Content:
// ќперации дл€ 2d машинной графики.
//
// 13.03.2008 - добавлены операторы сравнени€ дл€ примитивов.
// -----------------------------------------------------------------------------
//
// CD->22.08.1996
// LC->07.03.2010
// --------------


 #include <lem/render/imb_math.h>
 #include <lem/math/math.h>
 #include <lem/math/integer_math.h>
 #include <lem/stl.h>

 #if defined LEM_WINDOWS
  #if defined LEM_MFC
   #include <afxwin.h>
  #else 
   #include <windows.h>
  #endif
 #endif

 #undef min
 #undef max

 namespace lem
 {
  namespace Render
  {
   using lem::Math::REAL;
   using lem::Math::qsqrt;
   using lem::Math::qpow2;
   using lem::Math::imb_Zround;


 #if !defined LEM_NOREAL
 // ------------------------------------------
 // Ќормализаци€ 2d вектора.
 // ƒл€ нулевого вектора ничего не происходит.
 // ------------------------------------------
 inline void imb_Normalize( REAL &dx, REAL &dy )
 {
  const REAL n=qsqrt( qpow2(dx)+qpow2(dy) );
  if(imb_Zround(n)==0.)
   { dx=dy=0.; }
  else
   { dx/=n; dy/=n; }

  return;
 }
 #endif


 #if !defined LEM_NOREAL
 // -------------------
 // “очка на плоскости.
 // -------------------
 struct Point2d
 {
  REAL x,y;

  Point2d( REAL X, REAL Y ) { x=X; y=Y; }
  Point2d(void) { x=y=0.; }

  Point2d& operator*=( REAL k )
  { x*=k; y*=k; return *this; }

  Point2d& operator/=( REAL k )
  { x/=k; y/=k; return *this; }

  inline bool operator==( const Point2d &a ) const { return x==a.x && y==a.y; }
  inline bool operator!=( const Point2d &a ) const { return x!=a.x || y!=a.y; }
 };

 inline REAL imb_dist( const Point2d a, const Point2d b )
 { return qsqrt( qpow2(a.x-b.x) + qpow2(a.y-b.y) ); }
 #endif



 struct Point2di
 {
  int x,y;

  Point2di( int X, int Y ) { x=X; y=Y; }
  Point2di(void) { x=y=0; }

  inline bool operator==( const Point2di &a ) const { return x==a.x && y==a.y; }
  inline bool operator!=( const Point2di &a ) const { return x!=a.x || y!=a.y; }
 };

 inline int imb_dist( const Point2di a, const Point2di b )
 { return (int)lem::Math::isqrt( lem::Math::ipow2(a.x-b.x) + lem::Math::ipow2(a.y-b.y) ); }


 #if !defined LEM_NOREAL
 inline Point2d operator*( const Point2d &a, REAL k )
 { return Point2d(a.x*k,a.y*k); }

 inline Point2d operator/( const Point2d &a, REAL k )
 { return Point2d(a.x/k,a.y/k); }

 inline Point2d operator+( const Point2d& a, const Point2d& b )
 { return Point2d( a.x+b.x, a.y+b.y ); }
 #endif


 // ********************************************************************

 #if !defined LEM_NOREAL
 struct Vector2d
 {
  REAL dx, dy;

  Vector2d(void) { dx=dy=0; }
  Vector2d( REAL DX, REAL DY ) { dx=DX; dy=DY; Normalize(); }
  Vector2d( const Point2d& a, const Point2d& b )
  {
   dx=b.x-a.x;
   dy=b.y-a.y;
   Normalize();
  }

  inline REAL Length(void) const
  { return qsqrt( qpow2(dx) + qpow2(dy) ); }

  inline void Normalize(void)
  {
   const REAL l=Length();
   if( l!=0. )
    { dx/=l; dy/=l; }
   else
    { dx=dy=0.; }

   return;
  }

  inline Vector2d& operator+=( const Vector2d &a )
  { dx+=a.dx; dy+=a.dy; return *this; }

  inline Vector2d& operator-=( const Vector2d &a )
  { dx-=a.dx; dy-=a.dy; return *this; }

  inline Vector2d& operator*=( const REAL k )
  { dx*=k; dy*=k; return *this; }

  inline Vector2d& operator/=( const REAL k )
  { dx/=k; dy/=k; return *this; }

  inline bool operator==( const Vector2d &a ) const { return dx==a.dx && dy==a.dy; }
  inline bool operator!=( const Vector2d &a ) const { return dx!=a.dx || dy!=a.dy; }
 };

 extern REAL imb_atanxy( const Vector2d &v );

 inline REAL abs( const Vector2d& a )
 { return a.Length(); }

 inline Vector2d operator+(
                                 const Vector2d &a,
                                 const Vector2d &b
                                )
 { return Vector2d( a.dx+b.dx, a.dy+b.dy ); }

 inline Vector2d operator-(
                                 const Vector2d &a,
                                 const Vector2d &b
                                )
 { return Vector2d( a.dx-b.dx, a.dy-b.dy ); }

 inline Vector2d operator*( const Vector2d &v, REAL k )
 { return Vector2d( v.dx*k, v.dy*k ); }

 inline Vector2d operator/( const Vector2d &v, REAL k )
 { return Vector2d( v.dx/k, v.dy/k ); }

 inline REAL imb_Cross( const Vector2d &a, const Vector2d &b )
 { return a.dx*b.dy-a.dy*b.dx; }

 inline REAL operator*( const Vector2d &a, const Vector2d &b )
 { return a.dx*b.dx+a.dy*b.dy; }

 // ¬озвращаетс€ вектор, нормальный к v.
 inline Vector2d imb_GetRect( const Vector2d &v )
 { return Vector2d( v.dy, -v.dx ); }

 inline Point2d operator+( const Point2d &a, const Vector2d &d )
 { return Point2d( a.x+d.dx, a.y+d.dy ); }

 #endif



 // ********************************************************************

 struct Vector2di
 {
  int dx, dy;

  Vector2di(void) { dx=dy=0; }
  Vector2di( int DX, int DY ) { dx=DX; dy=DY; }
  Vector2di( const Point2di& a, const Point2di& b )
  {
   dx=b.x-a.x;
   dy=b.y-a.y;
   return;
  }

  inline long Length(void) const
  { return lem::Math::isqrt( long(dx*dx) + long(dy*dy) ); }

  inline Vector2di& operator+=( const Vector2di &a )
  { dx+=a.dx; dy+=a.dy; return *this; }

  inline Vector2di& operator-=( const Vector2di &a )
  { dx-=a.dx; dy-=a.dy; return *this; }

  #if !defined LEM_NOREAL
  inline Vector2di& operator*=( REAL k )
  { dx = lem::Math::qroundi(dx*k); dy = lem::Math::qroundi(dy*k); return *this; }

  inline Vector2di& operator/=( REAL k )
  { dx= lem::Math::qroundi(dx/k); dy=lem::Math::qroundi(dy/k); return *this; }
  #endif

  inline void Normalize(void)
  {
   const int l=(int)Length();
   if( l!=0 )
    { dx/=l; dy/=l; }
   else
    { dx=dy=0; }

   return;
  }

  inline bool operator==( const Vector2di &a ) const { return dx==a.dx && dy==a.dy; }
  inline bool operator!=( const Vector2di &a ) const { return dx!=a.dx || dy!=a.dy; }
 };

 #if !defined LEM_NOREAL
 inline REAL abs( const Vector2di& a )
 { return a.Length(); }
 #endif

 inline Vector2di operator+(
                                  const Vector2di &a,
                                  const Vector2di &b
                                 )
 { return Vector2di( a.dx+b.dx, a.dy+b.dy ); }

 inline Vector2di operator-(
                                  const Vector2di &a,
                                  const Vector2di &b
                                 )
 { return Vector2di( a.dx-b.dx, a.dy-b.dy ); }

 #if !defined LEM_NOREAL
 inline Vector2di operator*( const Vector2di &v, const REAL k )
 { return Vector2di( lem::Math::qroundi(v.dx*k), lem::Math::qroundi(v.dy*k) ); }

 inline Vector2di operator/( const Vector2di &v, const REAL k )
 { return Vector2di( lem::Math::qroundi(v.dx/k), lem::Math::qroundi(v.dy/k) ); }

 inline REAL imb_Cross( const Vector2di &a, const Vector2di &b )
 { return a.dx*b.dy-a.dy*b.dx; }

 inline REAL operator*( const Vector2di &a, const Vector2di &b )
 { return a.dx*b.dx+a.dy*b.dy; }
 #endif

 // ¬озвращаетс€ вектор, нормальный к v.
 inline Vector2di imb_GetRect( const Vector2di &v )
 { return Vector2di( v.dy, -v.dx ); }

 inline Point2di operator+(
                                 const Point2di &a,
                                 const Vector2di &d
                                )
 { return Point2di( a.x+d.dx, a.y+d.dy ); }

 // *******************************************************************

 #if !defined LEM_NOREAL
 inline void imb_Polar2Decart_cos(
                                  REAL rho,
                                  REAL cosphi,
                                  REAL &x,
                                  REAL &y
                                 )
 {
  x = rho*cosphi;
  y = rho*lem::Math::qsqrt(1-lem::Math::qpow2(cosphi));
 }

 inline void imb_Polar2Decart(
                              REAL rho,
                              REAL phi,
                              REAL &x,
                              REAL &y
                             )
 {
  const REAL cosphi=lem::Math::qcos(phi);
  x = rho*cosphi;
  y = rho*lem::Math::qsqrt(1-lem::Math::qpow2(cosphi));
 }

 inline Point2d imb_Polar2Decart( REAL rho, REAL phi )
 { return Point2d( rho*lem::Math::qcos(phi), rho*lem::Math::qsin(phi) ); }

 // --------------------------------------
 // ќпредел€ем, перекрывает ли треугольник
 // начало координат. Ёта функци€ активно
 // используетс€ трассировщиком лучей дл€
 // определени€, пересекаетс€ ли луч
 // каким-либо объектом.
 //
 // xA, yA, xB, yB, xC, yC - координаты вершин
 // треугольника на плоскости.
 // --------------------------------------
 inline bool imb_IsOrgInTriangle(
                                 REAL xA, REAL yA,
                                 REAL xB, REAL yB,
                                 REAL xC, REAL yC
                                )

 {
  // ќтсекаем заведомо проигрышные случаи.
  if( xA<0 && xB<0 && xC<0 ) return false;
  if( xA>0 && xB>0 && xC>0 ) return false;
  if( yA<0 && yB<0 && yC<0 ) return false;
  if( yA>0 && yB>0 && yC>0 ) return false;

  // «наки векторных произведений между
  // векторами сторон и векторами из
  // вершин в центр.
  const REAL s1 = lem::Math::lem_signum(imb_Zround(xA*yB-yA*xB));
  const REAL s2 = lem::Math::lem_signum(imb_Zround(xB*yC-yB*xC));
  const REAL s3 = lem::Math::lem_signum(imb_Zround(xC*yA-yC*xA));

  if( lem::Math::imb_is_Z(s1) || lem::Math::imb_is_Z(s2) || lem::Math::imb_is_Z(s3) )
   return true; // ќдна из сторон лежит на точке (0,0)

  return s1==s2 && s1==s3;
 }
 #endif



 // ********************************************************************

 struct Rect2di
 {
  int x,y,w,h;

  Rect2di(void) { x=y=w=h=0; }
  Rect2di( int X, int Y, int W, int H )
  { x=X; y=Y; w=W; h=H; }

  Rect2di( const Point2di a, const Point2di b )
  {
   x = a.x;
   y = a.y;
   w = b.x-a.x;
   h = b.y-a.y;
   return;
  }

  #if defined LEM_WINDOWS
  Rect2di( const RECT r )
  { x=r.left; y=r.top; w=r.right-r.left; h=r.bottom-r.top; }
  #endif

  inline int GetX0(void) const { return x;   }
  inline int GetY0(void) const { return y;   }
  inline int GetX1(void) const { return x+w; }
  inline int GetY1(void) const { return y+h; }

  inline int GetW(void) const { return w; }
  inline int GetH(void) const { return h; }

  // площадь фигуры
  inline int Area(void) const { return w*h; }

  inline bool IsNull(void) const { return !w && !h; }

  #if defined LEM_WINDOWS
  inline RECT GetRect(void) const
  {
   RECT r;
   r.left=x;    r.top=y;
   r.right=x+w; r.bottom=y+h;
   return r;
  }
  #endif

  inline bool operator==( const Rect2di &a ) const
  { return x==a.x && y==a.x && w==a.w && h==a.h; }

  inline bool operator!=( const Rect2di &a ) const
  { return x!=a.x || y!=a.x || w!=a.w || h!=a.h; }
 };

 // **********************************************************************
 // ¬озвращаем наименьший пр€моугольник, который охватывает оба аргумента.
 // **********************************************************************
 inline Rect2di imb_combine(
                                  const Rect2di a,
                                  const Rect2di b
                                 )
 {
  const int xmin = min( a.GetX0(), b.GetX0() );
  const int xmax = max( a.GetX1(), b.GetX1() );
  const int ymin = min( a.GetY0(), b.GetY0() );
  const int ymax = max( a.GetY1(), b.GetY1() );

  return Rect2di( xmin, ymin, xmax-xmin, ymax-ymin );
 }

 #if !defined LEM_NOREAL
 inline Point2di imb_get_point_on_line(
                                             const Point2di a,
                                             const Point2di b,
                                             REAL k
                                            )
 { return Point2di(
                   lem::Math::qroundi(a.x + (b.x-a.x)*k),
                   lem::Math::qroundi(a.y + (b.y-a.y)*k )); }

 inline Point2d imb_get_point_on_line(
                                                const Point2d a,
                                                const Point2d b,
                                                REAL k
                                               )
 { return Point2d( a.x + (b.x-a.x)*k, a.y + (b.y-a.y)*k ); }
 #endif

 // *************************************************************************
 // ѕолучаем координаты точки, котора€ находитс€ на рассто€нии dist от точки
 // from по вектору dir.
 // *************************************************************************
 inline Point2di imb_move_point(
                                      const Point2di from,
                                      const Vector2di dir,
                                      int dist
                                     )
 {
  Vector2di v = dir;
  v.Normalize();
  return Point2di( from.x + v.dx*dist, from.y + v.dy*dist );
 }


 // ********************************************
 // ќтрезок линии - задаетс€ координатами концов
 struct Line2di
 {
  Point2di a,b;
 
  Line2di(void) {}

  Line2di( int x0, int y0, int x1, int y1 )
   : a(x0,y0), b(x1,y1) {}

  inline int Dist(void) const { return imb_dist(a,b); }


  inline bool operator==( const Line2di &x ) const { return a==x.a && b==x.b; }
  inline bool operator!=( const Line2di &x ) const { return a!=x.a || b!=x.b; }
 };


  } // namespace Render
 } // namespace 'lem'

#endif
