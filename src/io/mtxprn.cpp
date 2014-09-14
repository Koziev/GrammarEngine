// -----------------------------------------------------------------------------
// File MTXPRN.CPP
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// Печать матриц по различным форматам, в основном процедуры используются
// при отладке программ с численными схемами решения задач.
// -----------------------------------------------------------------------------
//
// CD->10.01.96
// LC->16.10.04
// ------------

#include <lem/oformatter.h>
#include <lem/qmatrix.h>

using namespace lem;
using namespace lem::Math;


// ***************************************************************************
// Действительная матрица A распечатывается в поток file. Способ печати
// задается полем format:
//
//     0: почти нулевые значения распечатываются как символ '.', остальные
//        распечатываются как символ '#'.
//
//     1: значения распечатывааются с помощью форматной строки (для
//        OFormatter), заданной dformat
//
//     2: нулевые значения печатаются как символ '.', положительные как '+',
//        отрицательные как '-'.
//
// С помощью этой процедуры удобно анализировать структуру матриц в численных
// методах.
// ***************************************************************************
void lem::print(
                const RMatrix& A,
                OFormatter& file,
                int format,
                const char *dformat
               )
{
 const int i0=A.GetFromI();
 const int j0=A.GetFromJ();
 const int in=A.GetToI();
 const int jn=A.GetToJ();

 switch( format )
  {
   case 0:
    {
     for( int i=i0; i<=in; i++ )
      {
       for( int j=j0; j<=jn; j++ )
        if( qabs(A.get(i,j))>1e-10 )
         file.printf('#');
        else
         file.printf('.');

       file.eol();
      }

     break;
    }

   case 1:
    {
     for( int i=i0; i<=in; i++ )
      {
       for( int j=j0; j<=jn; j++ )
        {
         REAL z = A.get(i,j);
         file.printf( dformat, z );
        }

       file.eol();
      }

     break;
    }

   case 2:
    {
     for( int i=i0; i<=in; i++ )
      {
       for( int j=j0; j<=jn; j++ )
        {
         REAL z = A.get(i,j);
         if( z<0. )
          file.printf( '-');
         else
          if( z>0. )
           file.printf('+');
          else
           file.printf('.');
        }

       file.eol();
      }
    break;
   }

  default:
   // Нереализованный формат
   LEM_STOPIT;
  }

 return;
}

// **************************************************************************
// Процедура выполняет проверку таких важных свойств действительной матрицы,
// как её симметричность и эрмитовость.
// **************************************************************************
void lem::print_sym( const RMatrix &a, OFormatter &f )
{
 // Доспустимые отклонения от симметричности и эрмитовости.
 REAL sym_criteria=1e-5;
 REAL hermit_criteria=1e-5;

 bool is_symmetric=true;
 bool is_hermitian=true;

 const int i0 = a.GetFromI();
 const int in = a.GetNI();

 LEM_CHECKIT_Z( i0==a.GetFromJ() );
 LEM_CHECKIT_Z( in==a.GetNJ() );

 bool flag=true;
 for( int i=i0; i<=in && flag; i++ )
  for( int j=i0; j<i; j++ )
   {
    REAL aij = a.get(i,j);
    REAL aji = a.get(j,i);

    // Симметрична?
    REAL devs = qabs(aij-aji);
    if( devs>sym_criteria )
     is_symmetric = false;

    // Эрмитова?
    REAL devh = qabs(aij+aji);
    if( devh>hermit_criteria )
     is_hermitian = false;

    if( !is_symmetric && !is_hermitian )
     {
      flag=false;
      break;
     }
   }

 #if defined LEM_RUSSIAN
  f.printf( "Симметричность матрицы с критерем %re: %b\n", sym_criteria, is_symmetric );
  f.printf( "Эрмитовость матрицы с критерем    %re: %b\n", hermit_criteria, is_hermitian );
 #else
  f.printf( "Matrix symmetry with criteria  %re: %b\n", sym_criteria, is_symmetric );
  f.printf( "Matrix hermitianity with criteria %re: %b\n", hermit_criteria, is_hermitian );
 #endif

 return;
}

// ------------------------ End Of File [MTXPRN.CPP] ---------------------------
