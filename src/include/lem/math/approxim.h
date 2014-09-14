// -----------------------------------------------------------------------------
// File APPROXIM.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2005
//
// Content:
// Процедуры для решения проблем аппроксимации (интер- и экстраполяция).
// Двух- и трехмерные сплайны и другие замечательные кривые и поверхности.
// -----------------------------------------------------------------------------
//
// CD->01.03.1996
// LC->31.10.2005
// --------------

#ifndef LEM_APPROXIMATE__H
#define LEM_APPROXIMATE__H
#pragma once

 #include <lem/qarray.h>
 #include <lem/polynomial.h>
 #include <lem/qmatrix.h>
 #include <lem/render/3d.h>
 #include <lem/render/2d.h>

 namespace lem
 {
  namespace Math
  {
   void BuildPlaneMatrix(
                         RMatrix& A,
                         RArray& Y,
                         const RArray& xi,
                         const RArray& yi
                        );

   const RPolynome ApproxPoly(
                              const RArray& xi,
                              const RArray& yi,
                              int NPOLY
                             );

   // Квадратичная интерполяция по 3-м точкам.
   REAL SquareInterpol(
                       REAL x0, REAL y0,
                       REAL x1, REAL y1,
                       REAL x2, REAL y2,
                       REAL X
                      );


   const RPolynome Approx_Gauss(
                                const RArray& xi,
                                const RArray& yi,
                                int NPOLY,
                                REAL RELERR
                               );

   int FindLeftPoint( const RArray& xi, REAL X );

   REAL LinearInterpol(
                       const RArray& xi,
                       const RArray& yi,
                       REAL X
                      );

   REAL SquareInterpol(
                       const RArray& xi,
                       const RArray& yi,
                       REAL X
                      );

   REAL LagrangeInterpol(
                         const RArray& xi,
                         const RArray& yi,
                         REAL X
                        );

   REAL LagrangeInterpol(
                         const RArray& xi,
                         const RArray& yi,
                         REAL X,
                         int AP
                        );

   // --------------------------------------------------------
   // Частотная фильтрация, в том числе процедуры сглаживания.
   // --------------------------------------------------------
   extern RArray& smooth_curve(
                               const RArray &src,  // Вектор исходных данных.
                               RArray &dst,        // Вектор сглаженных данных.
                               int Order           // Порядок формулы сглаживания.
                              );

   extern RArray& smooth_curve( RArray &y, int Order );

   extern void GoThruX(
                       REAL X0,
                       REAL X1,
                       REAL DX,
                       const RPolynome p,
                       RArray &res_x,
                       RArray &res_y
                      );


  // GCURVES LIBRARY
  // (C) 1987,1988, 1989 Disk Software, Inc.
  // Richardson, Texas

  // Кубические B-сплайны.
  extern void CreateBSplineCurve(
                                 int n,
                                 const lem::Render::Point2di *p,
                                 int nt,
                                 lem::Render::Point2di **b,
                                 int &nn
                                );

  extern void CreateBSplineCurve(
                                 const RArray &px,
                                 const RArray &py,
                                 int nt,
                                 RArray &oX,
                                 RArray &oY
                                );

  // В пространстве.
  extern void CreateBSplineCurve(
                                 int n,
                                 const lem::Render::Point3d *p,
                                 int nt,
                                 lem::Render::Point3d **b,
                                 int &nn
                                );


  // Квадратичные B-сплайны.

  extern void CreateBSpline2Curve(
                                  int n,
                                  const lem::Render::Point2di *p,
                                  int nt,
                                  lem::Render::Point2di **b,
                                  int &nn
                                 );

  extern void CreateBSpline2Curve(
                                  const RArray &px,
                                  const RArray &py,
                                  int nt,
                                  RArray &oX,
                                  RArray &oY
                                 );

  extern void CreateBSpline2Curve(
                                  int n,
                                  const lem::Render::Point3d *p,
                                  int nt,
                                  lem::Render::Point3d **b,
                                  int &nn
                                 );

  // ------------------------------------------------------------

  extern void CreateBezierCurve(
                                int nrctrlpnts,
                                const lem::Render::Point2di *ctrlpnts,
                                int nrcurvepnts,
                                lem::Render::Point2di **curvepnts
                               );

  extern void CreateBezierCurve(
                                const RArray &px,
                                const RArray &py,
                                int nt,
                                RArray &oX,
                                RArray &oY
                               );

  extern void CreateBezierCurve(
                                int nrctrlpnts,
                                const lem::Render::Point3d *ctrlpnts,
                                int nrcurvepnts,
                                lem::Render::Point3d **curvepnts
                               );

  // ------------------------------------------------------------

  extern void CreateCatromCurve(
                                int nrctrlpnts,
                                const lem::Render::Point2di *ctrlpnts,
                                int subn,
                                REAL tension,
                                lem::Render::Point2di **curvepnts,
                                int &nrcurvepnts
                               );

  extern void CreateCatromCurve(
                                const RArray &px,
                                const RArray &py,
                                int nt,
                                REAL tension,
                                RArray &oX,
                                RArray &oY
                               );

  extern void CreateCatromCurve(
                                int nrctrlpnts,
                                const lem::Render::Point3d *ctrlpnts,
                                int sunb,
                                REAL tension,
                                lem::Render::Point3d **curvepnts,
                                int &nrcurvepnts
                               );

  } // namespace Math
 } // namespace 'lem'

#endif
// ------------------------- End Of File [APPROXIM.H] --------------------------
