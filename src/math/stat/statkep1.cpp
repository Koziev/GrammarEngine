// -----------------------------------------------------------------------------
// File STATKEP1.CPP
//
// (c) Koziev Elijah
//
// Content:
// Класс StatKeeper - для простейшей статистической обработки последовательно
// вычисляемых значений. В частности, может использоваться в методе Монте-Карло
// для получения статистик параметров. Для каждого параметра можно создавать
// отдельный объект StatKeeper.
// -----------------------------------------------------------------------------
//
// CD->19.01.1996
// LC->19.09.2009
// --------------

#include <lem/minmax.h>
#include <lem/math/statkeep.h>
#include <lem/math/math.h>
#include <lem/streams.h>
#include <lem/oformatter.h>

#undef min
#undef max

using namespace lem;
using namespace lem::Math;

Statis::Statis(void)
{
 amin =  MAXREAL;
 amax = -MAXREAL;

 N = 0;
 SUM = SUM2 = SUM3 = SUM4 = 0.;

 return;
}

void Statis::add( REAL y )
{
 N++;

 REAL yy=qpow2(y);

 SUM  += y;
 SUM2 += yy;

 amin = lem::min( amin, y );
 amax = lem::max( amax, y );

 return;
}

void Statis::add_ex( REAL y )
{
 N++;

 REAL yy=qpow2(y);

 SUM  += y;
 SUM2 += yy;
 SUM3 += yy*=y;
 SUM4 += yy*=y;

 amin = lem::min( amin, y );
 amax = lem::max( amax, y );
 return;
}

/*******************************************
 Математическое ожидание M1, то есть первый
 центральный момент.
*******************************************/
REAL Statis::M1(void) const
{
 return N ? SUM/N : MAXREAL;
}

/***************************************************
  Центральный момент второго порядка - ДИСПЕРСИЯ M2.
****************************************************/
REAL Statis::M2(void) const
{
 REAL D2 = N ? (SUM2/N-qpow2(SUM/N)) : MAXREAL;
 if( D2<0. )
  D2=0.; // Быть такого не может!!!

 return D2;
}

/***********************************
 Среднеквадратическое отклонение.
***********************************/
REAL Statis::SIGMA(void) const
{
 return N ? qsqrt(M2()) : MAXREAL;
}

/*************************************
  Момент третьего порядка - асимметри
**************************************/
REAL Statis::m3(void) const
{
 return N ? (SUM3/N) : MAXREAL;
}

/****************************************
  Эксцесс - момент четвертого порядка m4
*****************************************/
REAL Statis::m4(void) const
{
 return N ? (SUM4/N) : MAXREAL;//(3.*(N-1)*pow2(M2())+SUM4)/pow3(N);
}

REAL Statis::M4(void) const
{
 return N ? (3.*(N-1)*qpow2(M2())+SUM4)/qpow3(N) : MAXREAL;
}

REAL Statis::Kv(void) const
{
 if( M1()!=0. )
  return N ? qsqrt(M2())/M1() : MAXREAL;
 else
  return MAXREAL;
}

/*****************************
 Коэффициент асимметрии
******************************/
REAL Statis::KA(void) const
{
 return N ? m3()/qpow(M2(),1.5) : MAXREAL;
}

/*************************
 Коэффициент эксцесса
**************************/
REAL Statis::KE(void) const
{
 return N ? m4()/qpow3(M2())-3. : MAXREAL;
}



/**************************************************************************
  Вывод статистической информации, накопленной объектом класса StatKeeper
  в указанный поток (по умолчанию - на консоль).
***************************************************************************/
void lem::Math::print( const Statis& sk, OFormatter& rep )
{
 #if defined RUSSIAN
  rep.printf( "Минимум %30Y. min = %10.4re\n", sk.min()   );
  rep.printf( "Максимум %30Y. max = %10.4re\n", sk.max()   );
  rep.printf( "Среднее %30Y. M1 = %10.4re\n", sk.M1()    );
  rep.printf( "Дисперсия %30Y. M2 = %10.4re\n", sk.M2()    );
  rep.printf( "Ср.-квадр. откл. %30Y. SIGMA = %10.4re\n", sk.SIGMA() );
  rep.printf( "Коэф. вариации %30Y. Kv = %10.4re\n", sk.Kv()    );
//  mout.printf( "Асимметрия m3    = %re\n", sk.m3()    );
//  mout.printf( "Эксцесс M4       = %re\n", sk.m4()    );
//  mout.printf( "Коэф. асимметрии = %re\n", sk.KA()    );
//  mout.printf( "Коэф. эксцесса   = %re\n", sk.KE()    );
 #else
  rep.printf( "Minimum %30Y. min = %10.4re\n", sk.min()   );
  rep.printf( "Maximum %30Y. max = %10.4re\n", sk.max()   );
  rep.printf( "Average %30Y. M1 = %10.4re\n", sk.M1()    );
  rep.printf( "Dispersion %30Y. M2 = %10.4re\n", sk.M2()    );
  rep.printf( "Av.-Squr. Div. %30Y. SIGMA = %10.4re\n", sk.SIGMA() );
  rep.printf( "Variation koeff. %30Y. KV = %10.4re\n", sk.Kv()    );
//  mout.printf( "Asymmetry m3     = %re\n", sk.m3()    );
//  mout.printf( "Excess    M4     = %re\n", sk.m4()    );
//  mout.printf( "Koef. of assym.  = %re\n", sk.KA()    );
//  mout.printf( "Koef. of excess  = %re\n", sk.KE()    );
 #endif
 return;
}

StatKeeper::StatKeeper(void)
:Statis()
{
 amin=MAXREAL;
 amax=-MAXREAL;
 SUM=SUM2=SUM3=SUM4=0.;
 N=0;
 return;
}

/*************************************************************
 Сохраняем состояние объекта и всю накопленную статистическую
 информацию в бинарном потоке.
**************************************************************/
void StatKeeper::SaveBin( lem::Stream& bin ) const
{
 bin.write( &amin, sizeof(amin) );
 bin.write( &amax, sizeof(amax) );
 bin.write( &SUM,  sizeof(SUM)  );
 bin.write( &SUM2, sizeof(SUM2) );
 bin.write( &SUM3, sizeof(SUM3) );
 bin.write( &SUM4, sizeof(SUM4) );
 bin.write( &N,    sizeof(N)    );
 return;
}

/***********************************************
 Восстанавливаем состояние из бинарного потока.
************************************************/
void StatKeeper::LoadBin( lem::Stream& bin )
{
 bin.read( &amin, sizeof(amin) );
 bin.read( &amax, sizeof(amax) );
 bin.read( &SUM,  sizeof(SUM)  );
 bin.read( &SUM2, sizeof(SUM2) );
 bin.read( &SUM3, sizeof(SUM3) );
 bin.read( &SUM4, sizeof(SUM4) );
 bin.read( &N,    sizeof(N)    );
 return;
}

