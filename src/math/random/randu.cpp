// -----------------------------------------------------------------------------
// File RANDU.CPP
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// Прекрасный генератор псевдослучайных равномерно распределенных чисел с
// автоматической настройкой на процессор.
// -----------------------------------------------------------------------------
//
// CD->18.01.1996
// LC->16.08.2007
// --------------

#if !defined LEM_NOdouble

#include <lem/math/random.h>


using namespace boost;
using namespace lem;
using namespace lem::Math;

int RandU::Number=0;

//lem::Math::RandU::result_type lem::Math::RandU::min_value=0;
//lem::Math::RandU::result_type lem::Math::RandU::max_value=0xffffffffUL;

/*
  Идея самонастройки ГСЧ и пример программы можно найти в
  источнике:

   Дж.Форсайт, М.Малькольм, К.Моулер "Машинные методы математических
   вычислений", -М.:"Мир", 1980, стр.260 и далее.

*/

static double ABRAM[]=
                    {
                     5347981115.,
                     9803612217.,
                     5952640238.,
                     4057739351.,
                     4321169255.,
                     9734470328.,
                     5811691964.,
                     2624044643.,
                     8328797391.,
                     9282377578.,
                     6602338277.,
                     7452371118.,
                     8489213956.,
                     9889992315.,
                     6578359640.
                    };

RandU::RandU( int n )
{
// min_value=0;
 //max_value=0xffffffffUL;

 if( n>=0 ) Number=n-1;

 // Если мы действительно желаем иметь множество
 // независимых генераторов, то желательно для каждого
 // нового создаваемого немного модифицировать расчетные
 // формулы. Это достигается ведением учета генераторов с
 // помощью статического поля класса.
 Number++;

 // Начинаем настройку генератора.

 HALFM = uint32_max/2;

 // Вычисляем множитель и приращение линейного конгруэнтного
 // метода.

 IA  = 8*int( PI/8.0*HALFM) + 5;
 IC  = 2*int( ( 0.5-sqrt(3.0)/6.0 ) * HALFM) + 1;

 // Масштабирующий множитель для для преобразования в число с плавающей точкой.
 S = 0.5/HALFM;

 // Выбор способа формирования начальных значений
 // сильно влияет на взаимную корреляцию генераторов.
// LASTY = 314159257UL*(Number);

 LASTY = int( ABRAM[ Number%DIM_A(ABRAM) ] + 314159257.*Number );
 return;
}

void RandU::Generate( int NR, double *dest )
{
 for( int i=0; i<NR; i++ )
  dest[i] = aget();

 return;
}

void RandU::SaveBin( lem::Stream& bin ) const
{
 const int s=sizeof(RandU);
 bin.write( &s,     sizeof(s)     );
 bin.write( &HALFM, sizeof(HALFM) );
 bin.write( &IA,    sizeof(IA)    );
 bin.write( &IC,    sizeof(IC)    );
 bin.write( &S,     sizeof(S)     );
 bin.write( &LASTY, sizeof(LASTY) );
 return;
}

void RandU::LoadBin( lem::Stream& bin )
{
 int s;
 bin.read( &s,     sizeof(s)     );
 LEM_CHECKIT_Z(s==sizeof(RandU));

 bin.read( &HALFM, sizeof(HALFM) );
 bin.read( &IA,    sizeof(IA)    );
 bin.read( &IC,    sizeof(IC)    );
 bin.read( &S,     sizeof(S)     );
 bin.read( &LASTY, sizeof(LASTY) );
 return;
}

#endif

