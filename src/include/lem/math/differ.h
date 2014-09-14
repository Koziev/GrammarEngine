// -----------------------------------------------------------------------------
// File DIFFER.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// Различные инструменты для численного дифференцирования и смежных вопросов.
// -----------------------------------------------------------------------------
//
// CD->21.01.96
// LC->23.10.04
// ------------

#ifndef LEM_DIFFER__H
#define LEM_DIFFER__H
#pragma once

 #if !defined LEM_NOREAL

 #include <lem/qmatrix.h>
 #include <lem/qarray.h>

 namespace lem
 {
  namespace Math
  {
   extern void BuildFiniteDiffer( int nnode, int nprime, RMatrix &w );
   extern const RArray BuildFiniteDiffer( int nnode, int nprime, int node );
   extern const RMatrix BuildFiniteDiffer( int nnode, int nprime );
   extern const RArray Differ( const RArray& y, int prime, int nnode, REAL dx=1 );
   extern void Differ( RArray *y, int prime, int nnode, REAL dx=1 );

   typedef REAL(*differ_func)( REAL x, REAL y );
   typedef REAL(*differ_func2)( REAL x, REAL y, REAL yp );
   typedef REAL(*differ_func3)(
                               REAL x,
                               REAL y,
                               REAL yp,
                               REAL ypp
                              );

    typedef REAL(*differ_func4)(
                                REAL x,
                                REAL y,
                                REAL yp,
                                REAL ypp,
                                REAL yppp
                               );

    typedef REAL(*sdiffer_func)(
                                int n,
                                REAL x,
                                const RArray& y
                               );

    extern REAL RungeCutta2_1(
                              differ_func F,
                              REAL a,
                              REAL b,
                              REAL dx,
                              REAL y0,
                              RArray *store
                             );

     extern REAL RungeCutta2_2(
                               differ_func F,
                               REAL a,
                               REAL b,
                               REAL dx,
                               REAL y0,
                               RArray *store
                              );

      extern REAL RungeCutta4(
                              differ_func F,
                              REAL a,
                              REAL b,
                              REAL dx,
                              REAL y0,
                              RArray *store
                             );

      extern REAL RungeCutta6(
                              differ_func F,
                              REAL a,
                              REAL b,
                              REAL dx,
                              REAL y0,
                              RArray *store
                             );

      extern void RungeCutta4(
                              sdiffer_func FF,
                              REAL a,
                              REAL b,
                              REAL dx,
                              RArray& y0,
                              int isave,
                              RArray& Y
                             );

      extern REAL RungeCuttaVar4(
                                 differ_func F,
                                 REAL a,
                                 REAL b,
                                 REAL dx,
                                 REAL y0,
                                 REAL ROUPH   = 1e-3,
                                 REAL PRECISE = 1e-4,
                                 RArray *X = NULL,
                                 RArray *Y = NULL
                                );


      extern REAL Miln(
                       differ_func F,
                       REAL a,
                       REAL b,
                       REAL dx,
                       REAL y0,
                       RArray *store
                      );

      extern REAL RungeCutta3(
                              differ_func F,
                              REAL a,
                              REAL b,
                              REAL dx,
                              REAL y0,
                              RArray *store
                             );


      extern REAL Miln1(
                        differ_func F,
                        REAL x0,
                        REAL y0,
                        REAL dx,
                        REAL xn,
                        RArray *Y=NULL
                       );

      extern REAL Butcher3(
                           differ_func F,
                           REAL x0,
                           REAL y0,
                           REAL dx,
                           REAL xn,
                           RArray *Y
                          );


      extern int RungeCutta4_upto(
                                  sdiffer_func FF,
                                  REAL a,
                                  REAL limit,
                                  int MAXNX,
                                  int ilimit,
                                  REAL dx,
                                  RArray& y0,
                                  int isave,
                                  RArray& Y
                                 );



       extern REAL RungeCutta24(
                                differ_func2 F,
                                REAL a,
                                REAL b,
                                REAL dx,
                                REAL ya,
                                REAL ypa,
                                RArray *store=NULL
                               );

       extern REAL RungeCutta34(
                                differ_func3 F,
                                REAL a,
                                REAL b,
                                REAL dx,
                                REAL ya,
                                REAL ypa,
                                REAL yppa,
                                RArray *store=NULL
                               );

       extern REAL EulerPreCorr(
                                differ_func F,
                                REAL a,
                                REAL b,
                                REAL dx,
                                REAL y0,
                                REAL eps,
                                RArray *store=NULL
                               );

       // ********************************************************************

       class ODE1_Solver
       {
        protected:
         sdiffer_func ff; // pointer to function calculating the primes

         virtual void FCN(
                          REAL X,
                          const RArray &Y,
                          RArray &Y_prime
                         );

         virtual void solous(
                             int i,
                             REAL X,
                             RArray &Y
                            );

         virtual REAL CalcPrime(
                                int i,
                                REAL X,
                                const RArray &Y
                               );

        public:
         ODE1_Solver(void);

         virtual ~ODE1_Solver(void);
       };

      class ODE1_RK6_Solver : public ODE1_Solver
      {
       public:
        ODE1_RK6_Solver(void);

        virtual bool solve(
                           sdiffer_func FF,
                           REAL X,
                           REAL XEND,
                           RArray &Y,
                           REAL dx
                          );

        virtual bool solve(
                           REAL X,
                           REAL XEND,
                           RArray &Y,
                           REAL dx0
                          );
      };

      // ******************************************************************
      // Классы-решатели для систем обыкновенных дифференциальных уравнений
      // первого порядка. Адаптивный шаг, постоянный порядок.
      // ******************************************************************

      class Dopri5Solver : public ODE1_Solver
      {
       private:
        int NMAX; // Maximal number of steps.

       protected:
        virtual void fail( REAL X );
        bool change_step; // Можно ли менять шаг решения? По умолчанию true, но
                          // если установить как false, то получим простую неадаптивную
                          // схему с фиксированным шагом.

       public:
        int NFCN;   // Number of function evaluations.
        int NSTEP;  // Number of computed steps.
        int NACCPT; // Number of accepted steps.
        int NREJCT; // Number of rejected steps.

        Dopri5Solver(void);

        virtual bool solve(
                           sdiffer_func FF,
                           REAL X,
                           REAL XEND,
                           RArray &Y,
                           REAL EPS,
                           REAL HMAX,
                           REAL dx0
                          );

        virtual bool solve(
                           REAL X,
                           REAL XEND,
                           RArray &Y,
                           REAL EPS,
                           REAL HMAX,
                           REAL dx0
                          );
      };

      typedef REAL(*boundary_func)( REAL t );
      typedef REAL(*begin_func)( REAL x );
      typedef REAL(*prime_coef_func)( REAL x, REAL t );
      typedef REAL(*prime_coef_func1)( REAL x );

      extern const RArray SolveBC1d(
                                    REAL a,
                                    REAL b,
                                    int NX,
                                    REAL tend,
                                    int NT,
                                    boundary_func YA,
                                    boundary_func YB,
                                    begin_func Y0,
                                    prime_coef_func Uxx,
                                    prime_coef_func Ux,
                                    prime_coef_func U,
                                    prime_coef_func Fxt
                                   );


      extern const RArray SolveBC1d(
                                    REAL a,
                                    REAL b,
                                    int NX,
                                    REAL tend,
                                    int NT,
                                    REAL YA,
                                    REAL YB,
                                    REAL Y0,
                                    REAL Uxx,
                                    REAL Ux,
                                    REAL U
                                   );



      extern const RArray SolveBC1d_5(
                                      REAL a,
                                      REAL b,
                                      int NX,
                                      REAL tend,
                                      int NT,
                                      boundary_func YA,
                                      boundary_func YB,
                                      begin_func Y0,
                                      prime_coef_func Uxx,
                                      prime_coef_func Ux,
                                      prime_coef_func U,
                                      prime_coef_func Fxt,
                                      int nt_levels=3
                                     );


      extern const RArray SolveBC1d_5(
                                      REAL a,
                                      REAL b,
                                      int NX,
                                      REAL tend,
                                      int NT,
                                      REAL YA,
                                      REAL YB,
                                      REAL Y0,
                                      REAL Uxx,
                                      REAL Ux,
                                      REAL U,
                                      int nt_levels=3
                                     );


      extern const RArray SolveBC1d(
                                    REAL a,
                                    REAL b,
                                    int NX,
                                    REAL YA,
                                    REAL YB,
                                    prime_coef_func1 Uxx,
                                    prime_coef_func1 Ux,
                                    prime_coef_func1 U,
                                    prime_coef_func1 Fx
                                   );


      extern const RArray SolveBC1d(
                                    REAL a,
                                    REAL b,
                                    int NX,
                                    REAL YA,
                                    REAL YB,
                                    REAL Uxx,
                                    REAL Ux,
                                    REAL U
                                   );

      extern const RArray SolveBC1d_5(
                                      REAL a,
                                      REAL b,
                                      int NX,
                                      REAL YA,
                                      REAL YB,
                                      prime_coef_func1 Uxx,
                                      prime_coef_func1 Ux,
                                      prime_coef_func1 U,
                                      prime_coef_func1 Fx
                                     );


      extern const RArray SolveBC1d_5(
                                      REAL a,
                                      REAL b,
                                      int NX,
                                      REAL YA,
                                      REAL YB,
                                      REAL Uxx,
                                      REAL Ux,
                                      REAL U
                                     );
  } // namespace 'Math'
 } // namespace 'lem'

 #endif
#endif
// -------------------------- End Of File [DIFFER.H] ---------------------------
