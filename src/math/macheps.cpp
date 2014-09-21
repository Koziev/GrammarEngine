// -----------------------------------------------------------------------------
// File MACHEPS.CPP
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2006
//
// Content:
// Вычисление относительной машинной погрешности для текущей арифметики REAL.
// Инициализируются некоторые глобальные переменные, используемые матпакетом
// для самонастройки.
// -----------------------------------------------------------------------------
//
// CD->01.01.1996
// LC->07.04.2007
// --------------

#if !defined LEM_NOREAL

#include <lem/math/math.h>

using namespace lem;
using namespace lem::Math;

const REAL lem::Math::MACHEPS=lem::Math::compute_mach_eps();

static int MACHBITS; // Число бит в мантиссе.

int lem::Math::get_mach_bits(void) { return MACHBITS; }

lem::Math::REAL lem::Math::compute_mach_eps(void)
{
 static bool first=true;

 const REAL HALF = TOREAL(.5);
 const REAL ONE  = TOREAL(1.);
 const REAL TWO  = TOREAL(2.);

 if(first)
  {
   REAL eps=ONE;
   REAL eps1=ONE+eps;

   MACHBITS=0;
   REAL twon=ONE;

   // Определяем машинную ошибку - минимальное
   // число, представимое в виде eps*e+1. Одновременно
   // определяем число бит в машинной мантиссе.

   while( eps1 != ONE )
    {
     MACHBITS++;
     twon *= TWO;
     eps  *= HALF;
     eps1 = ONE+eps;
    }

   eps   = TWO/twon;
   first = false;
   return eps;
  }

 return MACHEPS;
}


/*************************************************************************
 Estimate unit roundoff in quantities of size x.

 This program should function properly on all systems satisfying
 the following two assumptions,

   1. the base used in representing dfloating point numbers is not a power
      of three.

   2. the quantity a in statement 10 is represented to the accuracy used
      in dfloating point variables that are stored in memory.

 Under these assumptions, it should be true that,

   a  is not exactly equal to four-thirds,
   b  has a zero for its last bit or digit,
   c  is not exactly equal to one,

 eps measures the separation of 1.0 from the next larger dfloating point
 number. The developers of eispack would appreciate being informed
 about any systems where these assumptions do not hold.

 *****************************************************************
 this routine is one of the auxiliary routines used by eispack iii
 to avoid machine dependencies.
 *****************************************************************

 this version dated 4/6/83.
**************************************************************************/
REAL lem::Math::get_epsilon( REAL x )
{
 const REAL ZERO = TOREAL(0.0);
 const REAL ONE  = TOREAL(1.0);

 REAL a,b,c,eps;

 a = 4.0e0/3.0e0;
 eps = ZERO;

 while( eps == ZERO )
 {
  b = a - ONE;
  c = b + b + b;
  eps = qabs(c-ONE);
 }

 return eps*qabs(x);
}

#endif


