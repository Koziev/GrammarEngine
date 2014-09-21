// -----------------------------------------------------------------------------
// File 3D.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2005
//
// Content:
// Операции для 3d машинной графики - геометрия.
// -----------------------------------------------------------------------------
//
// CD->15.07.1995
// LC->18.04.2007
// --------------

#if !defined( IMB_GEOM3D__H )
 #define IMB_GEOM3D__H

 #if !defined LEM_NOREAL

 #include <lem/config.h>
 #include <lem/math/math_constants.h>
 #include <lem/math/m4x4.h>
 #include <lem/render/imb_math.h>

 namespace lem
 {
  namespace Render
  {
   using lem::Math::Matrix4x4;
   using lem::Math::qpow2;
   using lem::Math::qsqrt;
   using lem::Math::imb_is_Z;
   using lem::Math::REAL;
   using lem::Math::qsin;
   using lem::Math::qcos;
   using lem::Math::qatan2;
   using lem::Math::qabs;
   using lem::Math::qacos;
   using lem::Math::qatan;
   using lem::Math::imb_minBound;
   using lem::Math::imb_eps_;
   using lem::Math::qroundi;

 /********************************************
  Элементы матрицы видового преобразования.
  Компоненты этой матрицы используются при
  преобразовании координат точек из мировой
  системы в видовую.
 *********************************************/
 extern REAL v11,v12,v13;
 extern REAL v21,v22,v23;
 extern REAL     v32,v33;
 extern REAL         v43;

 /*******************************************************************
  Нормализация вектора. Для нулевого вектора ничего не происходит.
 ********************************************************************/
 inline void imb_Normalize( REAL &dx, REAL &dy, REAL &dz )
 {
  const REAL n=qsqrt( qpow2(dx)+qpow2(dy)+qpow2(dz) );

  if( imb_is_Z(n) )
   { dx=dy=dz=0.; }
  else
   { dx/=n; dy/=n; dz/=n; }

  return;
 }

 /**********************************************
  Точка в 3D пространстве.
 ***********************************************/
 struct Vector3d;
 struct Point3d
 {
  REAL x,y,z;

  Point3d(void) { x=y=z=0.; }
  Point3d( REAL X, REAL Y, REAL Z ) { x=X; y=Y; z=Z; }

  friend REAL imb_dist( const Point3d &a, const Point3d &b );
  friend REAL imb_dist2( const Point3d &a, const Point3d &b );
  friend void imb_swap( Point3d &a, Point3d &b );

  friend const Point3d operator+( const Point3d &a, const Point3d &b );
  friend const Point3d operator*( const Point3d &a, REAL k );
  friend const Point3d operator/( const Point3d &a, REAL k );

  Point3d& operator+=( const Vector3d &v );

  Point3d& operator*=( const Matrix4x4& T );
 };

 inline const Point3d operator+( const Point3d &a, const Point3d &b )
 { return Point3d( a.x+b.x, a.y+b.y, a.z+b.z );  }

 inline const Point3d operator*( const Point3d &a, REAL k )
 { return Point3d( a.x*k, a.y*k, a.z*k );  }

 inline const Point3d operator/( const Point3d &a, REAL k )
 { return Point3d( a.x/k, a.y/k, a.z/k );  }

 extern const Point3d operator*(
                                      const Point3d &a,
                                      const Matrix4x4& T
                                     );

 inline REAL dist( const Point3d &a, const Point3d &b )
 { return qsqrt(qpow2(b.x-a.x)+qpow2(b.y-a.y)+qpow2(b.z-a.z)); }

 inline REAL dist2( const Point3d &a, const Point3d &b )
 { return qpow2(b.x-a.x)+qpow2(b.y-a.y)+qpow2(b.z-a.z); }

 // -----------------------------------------------------------
 // Тип ВЕКТОР и базовые математические операции над векторами.
 // -----------------------------------------------------------
 struct Vector3d
 {
  REAL dx,dy,dz;

  Vector3d(void) { dx=dy=dz=0.; }

  Vector3d( REAL dX, REAL dY, REAL dZ )
  { dx=dX; dy=dY; dz=dZ; Normalize(); }

  Vector3d( const Vector3d& v ) { dx=v.dx; dy=v.dy; dz=v.dz; }

  Vector3d( const Point3d& a, const Point3d& b )
  { dx=a.x-b.x; dy=a.y-b.y; dz=a.z-b.z; Normalize(); }

  inline Vector3d& operator+=( const Vector3d& v )
  { dx+=v.dx; dy+=v.dy; dz+=v.dz; return *this; }

  inline Vector3d& operator-=( const Vector3d& v )
  { dx-=v.dx; dy-=v.dy; dz-=v.dz; return *this; }

  inline Vector3d& operator*=( REAL k )
  { dx*=k; dy*=k; dz*=k; return *this; }

  inline Vector3d& operator/=( REAL k )
  { dx/=k; dy/=k; dz/=k; return *this; }

  inline REAL Length(void) const
  { return qsqrt(qpow2(dx)+qpow2(dy)+qpow2(dz)); }

  // normalize a vector to length 1
  inline void Normalize(void)
  {
   const REAL n=Length();

   if( imb_is_Z(n) )
    dx=dy=dz=0.;
   else
    { dx/=n; dy/=n; dz/=n; }

   return;
  }
 };

 /*
 inline void swap( Vector3d &a, Vector3d &b )
 {
  const Vector3d t=a;
  a=b;
  b=t;
 }
 */

 inline Point3d& Point3d::operator+=( const Vector3d &v )
 {
  x+=v.dx;
  y+=v.dy;
  z+=v.dz;
  return *this;
 }

 struct VectorOX3d : public Vector3d
 { VectorOX3d(void):Vector3d(1.,0.,0.){}; };

 struct IMB_VectorOY3d : public Vector3d
 { IMB_VectorOY3d(void):Vector3d(0.,1.,0.){}; };

 struct IMB_VectorOZ3d : public Vector3d
 { IMB_VectorOZ3d(void):Vector3d(0.,0.,1.){}; };

 // --------------------------------------
 // Векторное произведение (Cross Product)
 // --------------------------------------
 inline Vector3d Cross( const Vector3d &a, const Vector3d &b )
 {
  return Vector3d(
                      (a.dy*b.dz-a.dz*b.dy),
                      (b.dx*a.dz-a.dx*b.dz),
                      (a.dx*b.dy-a.dy*b.dx)
                     );
 }

 // ------------------------------------
 // Скалярное произведение (Dot Product)
 // ------------------------------------
 inline REAL operator*( const Vector3d &a, const Vector3d &b )
 { return (a.dx*b.dx+a.dy*b.dy+a.dz*b.dz); }

 inline const Vector3d operator+(
                                       const Vector3d &a,
                                       const Vector3d &b
                                      )
 { return Vector3d( a.dx+b.dx, a.dy+b.dy, a.dz+b.dz ); }

 inline const Vector3d operator-(
                                       const Vector3d &a,
                                       const Vector3d &b
                                      )
 { return Vector3d( a.dx-b.dx, a.dy-b.dy, a.dz-b.dz ); }

 // ------------------------------------------------
 // Создание вектора, проходящего через точки a и b.
 // ------------------------------------------------
 inline const Vector3d operator-(
                                       const Point3d &a,
                                       const Point3d &b
                                      )
 { return Vector3d( a.x-b.x, a.y-b.y, a.z-b.z ); }

 // Длина вектора
 inline REAL abs( const Vector3d& a ) { return a.Length(); }

 // -----------------------------------------------
 // Область 3d пространства в виде параллелепипеда.
 // -----------------------------------------------
 struct Box3d
 {
  REAL xmin, xmax, ymin, ymax, zmin, zmax;

  Box3d(void) { xmin=xmax=ymin=ymax=zmin=zmax=0.; }
  Box3d(
            REAL Xmin, REAL Xmax,
            REAL Ymin, REAL Ymax,
            REAL Zmin, REAL Zmax
           );

  inline REAL Volume(void) const
  { return (zmax-zmin)*(ymax-ymin)*(xmax-xmin); }
 };

 // ####################################################
 //  ВЗАИМНЫЕ ПРЕОБРАЗОВАНИЯ РАЗЛИЧНЫХ СИСТЕМ КООРДИНАТ
 // ####################################################

 // *****************************************************
 // Сферические в декартовы.
 // *****************************************************
 inline void Spher2Decart(
                           REAL Rho,
                           REAL Theta,
                           REAL Phi,
                           REAL &x, REAL &y, REAL &z
                          )
 {
  const REAL sinphi=Rho*qsin(Phi);
  x=sinphi*qcos(Theta);
  y=sinphi*qsin(Theta);
  z=Rho*qcos(Phi);
  return;
 }

 inline const Point3d Spher2Decart(
                                        REAL Rho,
                                        REAL Theta,
                                        REAL Phi
                                       )
 {
  const REAL sinphi=Rho*qsin(Phi);
  return Point3d(
                     sinphi*qcos(Theta),
                     sinphi*qsin(Theta),
                     Rho*qcos(Phi)
                    );
 }

 inline void Decart2Spher(
                           REAL x, REAL y, REAL z,
                           REAL &Rho, REAL &Theta, REAL &Phi
                          )
 {
  Rho=qsqrt(qpow2(x)+qpow2(y)+qpow2(z));

  if(x>0.)
   Theta=qatan2(y,x);
  else if(x<0.)
    Theta=PI+qatan2(y,qabs(x));
   else
    {
     if(y>=0.)
      Theta=PI_D_2;
     else
      Theta=PI*1.5;
    }

  if(Rho)
   Phi=qacos(z/Rho);
  else
   Phi=0.;

  return;
 }

 /************************************************************************
   Процедуры инициализации матрицы преобразования от
   мировых к видовым координатам.

   Параметр (Rho,Theta,Phi) определяют положение точки
   наблюдения E в сферических координатах:

                    z
                    |
                    |      * E
                    | phi /:
                    |   /  :
                    | /    :
                    * -----:--------- y
                   / \     :
                 /     \   :
               /  theta  \ :
             /             *
            x

 ************************************************************************/

 inline void InitViewMatrix(
                             REAL Rho,
                             REAL Theta,
                             REAL Phi,
                             REAL &V11, REAL &V12, REAL &V13,
                             REAL &V21, REAL &V22, REAL &V23,
                             REAL &V32, REAL &V33,
                             REAL &V43
                             )
 {
  const REAL costh=qcos(Theta);
  const REAL sinth=qsin(Theta);
  const REAL sinph=qsin(Phi);
  const REAL cosph=qcos(Phi);

  V11=-sinth; V12=-cosph*costh; V13=-sinph*costh;
  V21=costh;  V22=-cosph*sinth; V23=-sinph*sinth;
  V32=sinph;  V33=-cosph;
  V43=Rho;
 }

 inline void InitViewMatrix(
                             REAL Rho,
                             REAL Theta,
                             REAL Phi
                            )
 {
  InitViewMatrix(
                 Rho, Theta, Phi,
                 v11, v12, v13,
                 v21, v22, v23,
                 v32, v33,
                           v43
                );
 }


 // ---------------------------------------------------------------
 // Частичная инициализация матрицы видового преобразования для
 // целей трассировки луча ( используется геометическим модулем ).
 // ----------------------------------------------------------------
 inline void InitViewMatrix(
                             REAL Theta,
                             REAL Phi,
                             REAL &V11, REAL &V12,
                             REAL &V21, REAL &V22,
                                                  REAL &V32
                            )
 {
  const REAL costh=qcos(Theta);
  const REAL sinth=qsqrt(1.-qpow2(costh));
  const REAL cosph=qcos(Phi);
  const REAL sinph=qsqrt(1.-qpow2(cosph));

  V11=-sinth; V12=-cosph*costh;
  V21=costh;  V22=-cosph*sinth;
  V32=sinph;
  return;
 }

 /****************************************************************
  Преобразование мировых координат точки к видовым.
 *****************************************************************/
 inline void project(
                      REAL xx, REAL yy, REAL zz,
                      REAL &x, REAL &y, REAL &z
                     )
 {
  x = v11*xx + v21*yy;
  y = v12*xx + v22*yy + v32*zz;
  z = imb_minBound(v13*xx + v23*yy + v33*zz + v43);
  return;
 }

 inline const REAL projectz( REAL xx, REAL yy, REAL zz )
 {
  return imb_minBound( v13*xx + v23*yy + v33*zz + v43 );
 }

 inline void project( const Point3d &a, Point3d &ae )
 {
  ae.x = v11*a.x + v21*a.y;
  ae.y = v12*a.x + v22*a.y + v32*a.z;
  ae.z = imb_minBound(v13*a.x + v23*a.y + v33*a.z + v43);
  return;
 }

 inline const Point3d project(
                                   REAL xx,
                                   REAL yy,
                                   REAL zz
                                  )
 {
  return Point3d(
                     v11*xx + v21*yy,
                     v12*xx + v22*yy + v32*zz,
                     imb_minBound(v13*xx + v23*yy + v33*zz + v43)
                    );
 }

 inline const Point3d project( const Point3d& a )
 {
  return Point3d(
                     v11*a.x + v21*a.y,
                     v12*a.x + v22*a.y + v32*a.z,
                     imb_minBound(v13*a.x + v23*a.y + v33*a.z + v43)
                    );
 }


 // ------------------------------------------
 // Определение параметров уравнения плоскости
 // ax+by+cz-h=0, в которой лежит треугольник.
 // ------------------------------------------
 extern void GetTriPlane(
                          const Point3d &A,
                          const Point3d &B,
                          const Point3d &C,
                          REAL &a, REAL &b, REAL &c, REAL &d
                         );


 inline REAL GetTriPlaneH(
                           const Point3d &A,
                           const Point3d &B,
                           const Point3d &C
                          )
 {
  return A.x*(B.y*C.z-C.y*B.z) -
         B.x*(A.y*C.z-C.y*A.z) +
         C.x*(A.y*B.z-B.y*A.z);
 }

 inline bool IsBackTriPlane(
                             const Point3d &A,
                             const Point3d &B,
                             const Point3d &C
                            )
 {
  return ( A.x*(B.y*C.z-C.y*B.z) -
           B.x*(A.y*C.z-C.y*A.z) +
           C.x*(A.y*B.z-B.y*A.z) ) <=0.;
 }

 // ------------------------------------------------
 // Определение коэффициентов в уравнении плоскости,
 // в которой лежит треугольник, задаваемых мировыми
 // координатами вершин.
 // ------------------------------------------------
 extern void GetTriPlane(
                          REAL xA, REAL yA, REAL zA,
                          REAL xB, REAL yB, REAL zB,
                          REAL xC, REAL yC, REAL zC,
                          REAL &a, REAL &b, REAL &c, REAL &h
                         );

 inline REAL GetTriPlaneH(
                           REAL xA, REAL yA, REAL zA,
                           REAL xB, REAL yB, REAL zB,
                           REAL xC, REAL yC, REAL zC
                          )
 {
  return xA*(yB*zC-yC*zB) - xB*(yA*zC-yC*zA) +	xC*(yA*zB-yB*zA);
 }

 // -----------------------------
 //              Луч.
 // -----------------------------
 struct IMB_Ray3d
 {
  Point3d org; // Начальная точка луча.
  Vector3d dir; // Направляющий вектор луча.

  IMB_Ray3d(void) {};
  IMB_Ray3d( const Point3d& o, const Vector3d& v );
  IMB_Ray3d( const Point3d& a, const Point3d& b );

  inline void Normalize(void) { dir.Normalize(); }
 };

 // ----------------------------------------------------------
 // Координаты точки пересечения луча и плоскости.
 // ----------------------------------------------------------
 extern bool Intersect(
                        // Луч
                        const IMB_Ray3d &ray,
                        // Коэф. уравнения плоскости.
                        REAL a,
                        REAL b,
                        REAL c,
                        REAL h,
                        // Вычисляемая точка пересечения.
                        Point3d &p
                       );

 // ----------------------------------------------------
 // Определяем, находится ли точка p внутри треугольника
 // с вершинами в точках a,b,c.
 // ----------------------------------------------------
 extern bool IsPntInTri(
                         const Point3d &a,
                         const Point3d &b,
                         const Point3d &c,
                         const Point3d &p
                        );

 // --------------------------------------------------
 // Определение пересечения луча с параллелепипедом.
 // --------------------------------------------------
 extern bool HitBoundingBox(
                             const REAL *minB,   const REAL *maxB, // box
                             const REAL *origin, const REAL *dir,  // ray
                             REAL *coord                           // hit point
                            );

 // Площадь треугольника, заданного 3 вершинами.
 extern REAL AreaTri(
                      const Point3d& a,
                      const Point3d &b,
                      const Point3d &c
                     );

 // ------------------------------------------------------------
 // Преобразование координат из декартовой системы в полярную.
 // ------------------------------------------------------------
 inline void Decart2Polar(
                           REAL x, REAL y, REAL z,
                           REAL &Rho, REAL &Theta, REAL &Phi
                          )
 {
  const REAL pi=PI;
  Rho=imb_minBound(qsqrt(qpow2(x)+qpow2(y)+qpow2(z)));

  if(x>imb_eps_)
   Theta=qatan(y/x);
  else
   if(x<-imb_eps_)
    Theta=pi+qatan(y/x);
   else
    {
     if(y>=0.)
      Theta=pi*0.5;
     else
      Theta=1.5*pi;
    }

  Phi=qacos(z/Rho);
  return;
 }

 // **********************************************************
 // Быстрое преобразование полярных координат в декартовы.
 // Theta - угол между OX и вектором (ТОЧКА-ЦЕНТР).
 // Phi - угол между OY и вектором (ТОЧКА-ЦЕНТР).
 // **********************************************************
 inline const Point3d Polar2Decart(
                                        REAL Rho,
                                        REAL Theta,
                                        REAL Phi
                                       )
 {
  return Point3d(
                     Rho*qcos(Theta)*qsin(Phi),
                     Rho*qsin(Theta)*qsin(Phi),
                     Rho*qcos(Phi)
                    );
 }

 struct IMB_Segment3d
 {
  Point3d a,b;

  IMB_Segment3d(void) {};
  IMB_Segment3d( const Point3d &A, const Point3d &B ) { a=A; b=B; }
 };

 // ************************************************************************
 // Возвращается минимальный параллелепипед, который охватывает оба
 // данных параллелепипеда.
 // ************************************************************************
/*
 inline const Box3d combine( const Box3d &a, const Box3d &b )
 {
  return Box3d(
               std::min( (lem::Math::REAL)a.xmin, (lem::Math::REAL)b.xmin ),
               std::max( a.xmax, b.xmax ),
               std::min( a.ymin, b.ymin ),
               std::max( a.ymax, b.ymax ),
               std::min( a.zmin, b.zmin ),
               std::max( a.zmax, b.zmax )
              );
 }
*/

   } // namespace Render
 } // namespace lem

 #endif

#endif
