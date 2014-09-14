// -----------------------------------------------------------------------------
// File QMATRIX.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2005
//
// Content:
// Класс-шаблон BaseMatrix - прямоугольная матрица из произвольных элементов.
// Используется для создания некоторых математических контейнеров для
// действительных, целых, комплексных чисел.
//
// Производные от этого шаблона классы QCMatrix и BaseMatrix вводят
// операции сравнения и арифметические операции дан элементами матриц.
// -----------------------------------------------------------------------------
//
// CD->20.05.1996
// LC->18.04.2008
// --------------

#ifndef LEM_QMATRIX__H
#define LEM_QMATRIX__H
#pragma once

 #include <lem/runtime_checks.h>
 #include <lem/math/real_functions.h>
 #include <lem/streams.h>

 namespace lem
 {

  #define BMT BaseMatrix<T>

  template < class T > class BaseMatrix;

  template < class T >
  class MatrixElement
  {
   private:
    BMT *m;
    int i,j;

    MatrixElement(void){};

   public:
    MatrixElement( BMT *matr, int I, int J )
    {
     m=matr;
     i=I;
     j=J;
     return;
    }

    inline operator T(void) const { return m->get(i,j); }

    inline const T operator=( const T v ) { m->set(i,j,v); return v; }
    inline const T operator+=( const T v ) { return m->add(i,j,v); }
    inline const T operator-=( const T v ) { return m->sub(i,j,v); }
    inline const T operator*=( const T v ) { return m->mul(i,j,v); }
    inline const T operator/=( const T v ) { return m->div(i,j,v); }

    inline const T operator-(void) { return -m->get(i,j); }
  };

  template < class T >
  class MatrixReference
  {
   private:
    BMT *m;
    int i;

    MatrixReference(void){};

   public:
    MatrixReference( BMT &matr, int I )
    {
     m=&matr;
     i=I;
     return;
    }

    inline MatrixElement<T> operator[]( int j )
    { return MatrixElement<T>(m,i,j); }
  };




  template <class T> class BaseMatrix
  {
   protected:
    T** field;  // Поле значений (список указателей на строки элементов).
    int i0,in,ni,j0,jn,nj; // Граничные значения для индексов и размерность.

    inline void Delete(void)
    {
     for( int i=0; i<ni; i++)
      delete[] field[i];

     lem_rub_off(field);
     return;
    }

    inline void Init(
                     int I0,
                     int iN,
                     int J0,
                     int JN,
                     const T *A=NULL
                    )
    {
     in=iN;
     i0=I0;
     ni = in-i0+1;
     nj = (jn=JN)-(j0=J0)+1;

     LEM_CHECKIT_Z(ni>=0 && nj>=0);

     if( !ni && !nj )
      {
       field=NULL;
      }
     else
      {
       field = new T*[ni];

       int ij=0;
       for( int i=0; i<ni; i++ )
        {
         field[i]=new T[nj];

         if( A!=NULL )
          {
           for( int j=0; j<nj; j++ )
            field[i][j] = A[ij++];
          }
         else
          memset( field[i], 0, sizeof(T)*nj );
         }
      }

     return;
    }

    inline void Init( const BMT& q )
    {
     Init( q.i0, q.in, q.j0, q.jn, NULL );

     for( int i=0; i<ni; i++ )
      memcpy( field[i], q.field[i], sizeof(T)*nj );

     return;
    }

   public:
    BaseMatrix()
    { field=NULL; i0=in=ni=j0=jn=nj=0; }

    BaseMatrix( int NI, int NJ, const T *A=NULL )
    { Init(0,NI-1,0,NJ-1,A); }

    BaseMatrix(
               // Обращаю внимание на имя аргумента iN - только после долгой
               // борьбы с компилятором Watcom удалось обнаружить, что имя аргумента
               // IN в данном случае воспринимается как-то не так.
               int I0, int iN,
               int J0, int JN,
               const T *A=NULL
              )
    { Init(I0,iN,J0,JN,A); }

    BaseMatrix( const BMT& q )
    { Init(q); }

    ~BaseMatrix() { Delete(); }

    inline BMT& operator=( const BMT& q )
    {
     if( &q!=this )
      {
       if( q.i0!=i0 || q.in!=in || q.j0!=j0 || q.jn!=jn )
        {
         // Размерность матрицы нужно менять, поэтому освобождаем память
         // и выделяем новый блок.
         Delete();
         Init(q);
        }
       else
        {
         // Бывают случаи, когда матрица может вместить новое содержимое
         // без проблем - тогда не будет освобождать память и тут же выделять ее.

         for( int i=0; i<ni; i++ )
          memcpy( field[i], q.field[i], sizeof(T)*nj );
        }
      }

     return *this;
    }

    // ****************************************************
    // Все элементы матрицы получают указанное значение A.
    // ****************************************************
    BMT& operator=( T A )
    {
     for( int i=0; i<ni; i++ )
      for( int j=0; j<nj; j++ )
       field[i][j] = A;

     return *this;
    }
 
    BMT& fill( const T& A )
    {
     for( int i=0; i<ni; i++ )
      for( int j=0; j<nj; j++ )
       field[i][j] = A;

     return *this;
    }
   

    // ******************************************************************
    // Инициализация элементов матрицы значениями из вектора A, который
    // можно считать развернутой построчно матрицей.
    // ******************************************************************
    BMT& operator=( const T *A )
    {
     LEM_CHECKIT_Z(A!=NULL);
     int ij=0;

     for( int i=0; i<ni; i++ )
      for( int j=0; j<nj; j++ )
       field[i][j] = A[ij++];

     return *this;
    }

    inline int GetFromI(void) const { return i0; }
    inline int GetFromJ(void) const { return j0; }
    inline int GetNI(void)    const { return ni; }
    inline int GetNJ(void)    const { return nj; }
    inline int GetToI(void)   const { return in; }
    inline int GetToJ(void)   const { return jn; }

    inline const T get( int i, int j ) const
    {
     LEM_CHECKIT_Z(i>=i0 && j>=j0 && i<=in && j<=jn );
     return field[i-i0][j-j0];
    }
/*
    inline const T operator()( int i, int j ) const
    {
     LEM_CHECKIT_Z(i>=i0 && j>=j0 && i<=in && j<=jn );
     return field[i-i0][j-j0];
    }
*/
    inline const T set( int i, int j, const T v )
    {
     LEM_CHECKIT_Z(i>=i0 && j>=j0 && i<=in && j<=jn );
     return field[i-i0][j-j0]=v;
    }

    BMT& operator+=( const T b );
    BMT& operator-=( const T b );
    BMT& operator*=( const T b );
    BMT& operator/=( const T b );

    BMT& operator+=( const BMT& b );
    BMT& operator-=( const BMT& b );
    BMT& operator*=( const BMT& b );
    BMT& operator/=( const BMT& b );

    bool operator==( const BaseMatrix<T>& q ) const;
    bool operator!=( const BaseMatrix<T>& q ) const;

    inline const T sub( int i, int j, const T v )
    {
     LEM_CHECKIT_Z(i>=i0 && j>=j0 && i<=in && j<=jn );
     return field[i-i0][j-j0]-=v;
    }

    inline const T add( int i, int j, const T v )
    {
     LEM_CHECKIT_Z(i>=i0 && j>=j0 && i<=in && j<=jn );
     return field[i-i0][j-j0]+=v;
    }

    inline const T div( int i, int j, const T v )
    {
     LEM_CHECKIT_Z(i>=i0 && j>=j0 && i<=in && j<=jn );
     return field[i-i0][j-j0]/=v;
    }

    inline const T mul( int i, int j, const T v )
    {
     LEM_CHECKIT_Z(i>=i0 && j>=j0 && i<=in && j<=jn );
     return field[i-i0][j-j0]*=v;
    }

    inline const T set_zero( int i, int j )
    {
     LEM_CHECKIT_Z(i>=i0 && j>=j0 && i<=in && j<=jn );
     return field[i-i0][j-j0]=0;
    }

    inline const T neg( int i, int j )
    {
     LEM_CHECKIT_Z(i>=i0 && j>=j0 && i<=in && j<=jn );
     return field[i-i0][j-j0]=-field[i-i0][j-j0];
    }

    inline void swap( int i1, int j1, int i2, int j2 )
    {
     LEM_CHECKIT_Z(i1>=i0 && j1>=j0 && i1<=in && j1<=jn );
     LEM_CHECKIT_Z(i2>=i0 && j2>=j0 && i2<=in && j2<=jn );

     const T t=field[i1-i0][j1-j0];
     field[i1-i0][j1-j0]=field[i2-i0][j2-j0];
     field[i2-i0][j2-j0]=t;
     return;
    }
/*
    BaseMatrix<T>& operator+=( const BaseMatrix<T>& x )
    {
     LEM_CHECKIT_Z( i0==x.i0 && in==x.in && j0==x.j0 && jn==x.jn );
     LEM_LOOP(i,ni)
      LEM_LOOP(j,nj)
       field[i][j]+=x.field[i][j];

     return *this;
    }
*/
/*
    BaseMatrix<T>& operator-=( const BaseMatrix<T>& x )
    {
     LEM_CHECKIT_Z( i0==x.i0 && in==x.in && j0==x.j0 && jn==x.jn );
     LEM_LOOP(i,ni)
      LEM_LOOP(j,nj)
       field[i][j]-=x.field[i][j];

     return *this;
    }
*/

/*
    BaseMatrix<T>& operator*=( const BaseMatrix<T>& x )
    {
     LEM_CHECKIT_Z( i0==x.i0 && in==x.in && j0==x.j0 && jn==x.jn );
     LEM_LOOP(i,ni)
      LEM_LOOP(j,nj)
       field[i][j]*=x.field[i][j];

     return *this;
    }
*/
/*
    BaseMatrix<T>& operator*=( const T x )
    {
     LEM_LOOP(i,ni)
      LEM_LOOP(j,nj)
       field[i][j]+=x;

     return *this;
    }
*/
/*
    BaseMatrix<T>& operator/=( const T x )
    {
     LEM_LOOP(i,ni)
      LEM_LOOP(j,nj)
       field[i][j]/=x;

     return *this;
    }
*/

   void SaveBin( lem::Stream &file ) const;
   void LoadBin( lem::Stream &file );
  };

  template <class T>
  inline bool BaseMatrix<T>::operator==( const BaseMatrix<T>& q ) const
  {
   if(
      i0!=q.i0 ||
      in!=q.in ||
      j0!=q.j0 ||
      jn!=q.jn
     ) return false;

   for(int i=0; i<ni; i++ )
    for( int j=0; j<nj; j++ )
     if( field[i][j]!=q.field[i][j] )
      return false;

   return true;
  }

 template <class T>
 inline bool BaseMatrix<T>::operator!=( const BaseMatrix<T>& q ) const
 {
  if(
     i0!=q.i0 ||
     in!=q.in ||
     j0!=q.j0 ||
     jn!=q.jn
    ) return true;

  for(int i=0; i<ni; i++ )
   for( int j=0; j<nj; j++ )
    if( field[i][j]!=q.field[i][j] )
     return true;

  return false;
 }

 // ============================================================

  template <class T>
  inline const BaseMatrix<T> operator+(
                                       const BaseMatrix<T> &a,
                                       const BaseMatrix<T> &b
                                      )
  {
   LEM_CHECKIT_Z( a.i0==b.i0 && a.j0==b.j0 && a.in==b.in && a.jn==b.jn );

   BaseMatrix<T> res(a);
   for( int i=0; i<a.GetNI(); i++ )
    for( int j=0; j<a.GetNJ(); j++ )
     res.set( i, j, a.get( i, j ) + b.get( i, j ) );

   return res;
  }


  template <class T>
  inline BMT& BMT::operator+=( const BMT& b )
  {
   const int i0 = GetFromI();
   const int j0 = GetFromJ();
   const int in = GetToI();
   const int jn = GetToJ();

   LEM_CHECKIT_Z( i0==b.GetFromI() );
   LEM_CHECKIT_Z( j0==b.GetFromJ() );
   LEM_CHECKIT_Z( in==b.GetToI()   );
   LEM_CHECKIT_Z( jn==b.GetToJ()   );

   for( int i=i0; i<=in; i++ )
    for( int j=j0; j<=jn; j++ )
     add( i, j, b.get(i,j) );

   return *this;
  }

 // ============================================================

  template <class T>
  inline const BaseMatrix<T> operator-(
                                       const BaseMatrix<T> &a,
                                       const BaseMatrix<T> &b
                                      )
  {
   LEM_CHECKIT_Z( a.i0==b.i0 && a.j0==b.j0 && a.in==b.in && a.jn==b.jn );
   BaseMatrix<T> res(a);
   for(int i=0; i<a.ni; i++ )
    for( int j=0; j<a.nj; j++ )
     res.sub( i, j, b.get(i,j) );

   return res;
  }

  template <class T>
  inline BMT& BMT::operator-=( const BMT& b )
  {
   const int i0 = GetFromI();
   const int j0 = GetFromJ();
   const int in = GetToI();
   const int jn = GetToJ();

   LEM_CHECKIT_Z( i0==b.GetFromI() );
   LEM_CHECKIT_Z( j0==b.GetFromJ() );
   LEM_CHECKIT_Z( in==b.GetToI()   );
   LEM_CHECKIT_Z( jn==b.GetToJ()   );

   for( int i=i0; i<=in; i++ )
    for( int j=j0; j<=jn; j++ )
     sub( i, j, get(i,j) );

   return *this;
  }

 // ============================================================

  template <class T>
  inline const BMT operator*( const BMT& a, const BMT& b )
  {
   LEM_CHECKIT_Z( a.GetFromI()==b.GetFromI() );
   LEM_CHECKIT_Z( a.GetFromJ()==b.GetFromJ() );
   LEM_CHECKIT_Z( a.GetNJ()==b.GetNI() );

   const int a_i0 = a.GetFromI();
   const int a_j0 = a.GetFromJ();
   const int a_jn = a.GetToJ();
   const int a_in = a.GetToI();
   const int b_jn = b.GetToJ();

   BMT res(a_i0,a_in,a_j0,b_jn);

   for( int i=a_i0; i<=a_in; i++ )
    for( int k=a_j0; k<=b_jn; k++ )
     {
      T dotpr = 0.;

      for( int j=a_j0; j<=a_jn; j++ )
       dotpr += a(i,j)*b(j,k);

      res.set( i, k, dotpr );
     }

   return res;
  }


  template <class T>
  inline BMT& BMT::operator*=( const BMT& b )
  {
   LEM_CHECKIT_Z( GetFromI()==b.GetFromI() );
   LEM_CHECKIT_Z( GetFromJ()==b.GetFromJ() );
   LEM_CHECKIT_Z( GetNJ()==b.GetNI() );

   const int a_i0 = GetFromI();
   const int a_j0 = GetFromJ();
   const int a_jn = GetToJ();
   const int a_in = GetToI();
   const int b_jn = b.GetToJ();

   BMT res(a_i0,a_in,a_j0,b_jn);
   int i,j,k;

   for( i=a_i0; i<=a_in; i++ )
    for( k=a_j0; k<=b_jn; k++ )
     {
      T dotpr = 0.;

      for( j=a_j0; j<=a_jn; j++ )
       dotpr += get(i,j)*b.get(j,k);

      res.set( i, k, dotpr );
     }

   for( i=a_i0; i<=a_in; i++ )
    for( k=a_j0; k<=b_jn; k++ )
      set( i, k, res.get(i,k) );

   return *this;
  }


  template <class T>
  inline const BaseMatrix<T> operator*(
                                       const BaseMatrix<T> &a,
                                       const T b
                                      )
  {
   BaseMatrix<T> res(a);

   for(int i=0; i<a.ni; i++ )
    for( int j=0; j<a.nj; j++ )
     res.mul( i, j, b );

   return res;
  }

  template <class T>
  inline const BaseMatrix<T> operator*(
                                       const T b,
                                       const BaseMatrix<T> &a
                                      )
  {
   BaseMatrix<T> res(a);
   for(int i=0; i<a.ni; i++ )
    for( int j=0; j<a.nj; j++ )
     res.mul( i, j, b );

   return res;
  }

  template <class T>
  inline BMT& BMT::operator*=( const T b )
  {
   const int i0 = GetFromI();
   const int j0 = GetFromJ();
   const int in = GetToI();
   const int jn = GetToJ();

   for( int i=i0; i<=in; i++ )
    for( int j=j0; j<=jn; j++ )
     mul( i, j, b );

   return *this;
  }


  // ============================================================


  template <class T>
  inline const BaseMatrix<T> operator/(
                                       const BaseMatrix<T> &a,
                                       const T b
                                      )
  {
   BaseMatrix<T> res(a);
   for( int i=0; i<a.ni; i++ )
    for( int j=0; j<a.nj; j++ )
     res.div( i, j, b );

   return res;
  }


  template <class T>
  inline void BMT::SaveBin( lem::Stream &file ) const
  {
   file.write( &i0, sizeof(i0) );
   file.write( &in, sizeof(in) );
   file.write( &ni, sizeof(ni) );
   file.write( &j0, sizeof(j0) );
   file.write( &jn, sizeof(jn) );
   file.write( &nj, sizeof(nj) );

   for( int i=0; i<ni; i++ )
    file.write( field[i], sizeof(T)*nj );
   
   return;
  }


  template <class T>
  inline void BMT::LoadBin( lem::Stream &file )
  {
   Delete();

   file.read( &i0, sizeof(i0) );
   file.read( &in, sizeof(in) );
   file.read( &ni, sizeof(ni) );
   file.read( &j0, sizeof(j0) );
   file.read( &jn, sizeof(jn) );
   file.read( &nj, sizeof(nj) );

   Init( i0, in, j0, jn );

   for( int i=0; i<ni; i++ )
    file.read( field[i], sizeof(T)*nj );

   return;
  }


  template <class T>
  inline BMT& BMT::operator/=( const T b )
  {
   const int i0 = GetFromI();
   const int j0 = GetFromJ();
   const int in = GetToI();
   const int jn = GetToJ();

   for( int i=i0; i<=in; i++ )
    for( int j=j0; j<=jn; j++ )
     div( i, j, b );

   return *this;
  }

  /*************************************************************************
   Вычисление шпура (или следа) матрицы, то есть суммы элементов
   на главной диагонали.


   Purpose of the routine is to determine the trace of an n*n matrix
   with real elements.

              n
             ---
             \
    Sp(A)  =  >  a(i,i)
             /
             ---
             i=1

  ***************************************************************************/
  template <class T>
  inline const T spur( const BMT& a )
  {
   T res(0);

   const int i0 = a.GetFromI();
   const int in = a.GetToI();

   LEM_CHECKIT_Z( i0==a.GetFromJ() );
   LEM_CHECKIT_Z( in==a.GetToI() );

   for( int i=i0; i<=in; i++ )
    res += a.get(i,i);

   return res;
  }

  template <class T>
  inline void minmax( const BMT& M, T& Min, T& Max )
  {
   Min = lem::Math::MAXREAL;
   Max = -lem::Math::MAXREAL;

   const int i0 = M.GetFromI();
   const int in = M.GetToI();
   const int j0 = M.GetFromJ();
   const int jn = M.GetToJ();

   for( int i=i0; i<=in; i++ )
    for( int j=j0; j<=jn; j++ )
     {
      T v = M.get(i,j);
      Max = qmax( Max, v );
      Min = qmin( Min, v );
     }

   return;
  }

/*
  template <class T>
  inline const BMT operator*( const BMT& a, const T b )
  {
   const int i0 = a.GetFromI();
   const int j0 = a.GetFromJ();
   const int in = a.GetNI();
   const int jn = a.GetNJ();
   BMT res(i0,in,j0,jn);

   for( int i=i0; i<=in; i++ )
    for( int j=j0; j<=jn; j++ )
     res.set( i, j, a(i,j)*b );

   return res;
  }
*/

/*
  template <class T>
  inline const BMT operator*( const T b, const BMT& a )
  {
   const int i0 = a.GetFromI();
   const int j0 = a.GetFromJ();
   const int in = a.GetToI();
   const int jn = a.GetToJ();
   BMT res(i0,in,j0,jn);

   for( int i=i0; i<=in; i++ )
    for( int j=j0; j<=jn; j++ )
     res.set( i, j, a.get(i,j)*b );

   return res;
  }
*/

/*
  template <class T>
  inline const BMT operator/( const BMT& a, const T b )
  {
   const int i0 = a.GetFromI();
   const int j0 = a.GetFromJ();
   const int in = a.GetToI();
   const int jn = a.GetToJ();
   BMT res(i0,in,j0,jn);

   for( int i=i0; i<=in; i++ )
    for( int j=j0; j<=jn; j++ )
     res.set( i, j, a(i,j)/b );

   return res;
  }
*/


/*
  template <class T>
  inline const BMT operator+( const BMT& a, const BMT& b )
  {
   const int i0 = a.GetFromI();
   const int j0 = a.GetFromJ();
   const int in = a.GetToI();
   const int jn = a.GetToJ();

   LEM_CHECKIT( i0==b.GetFromI() );
   LEM_CHECKIT( j0==b.GetFromJ() );
   LEM_CHECKIT( in==b.GetToI()   );
   LEM_CHECKIT( jn==b.GetToJ()   );

   BMT res(i0,in,j0,jn);

   for( int i=i0; i<=in; i++ )
    for( int j=j0; j<=jn; j++ )
     res.set( i, j, a(i,j)+b(i,j) );

   return res;
  }
*/


/*
  template <class T>
  inline const BMT operator-( const BMT& a, const BMT& b )
  {
   const int i0 = a.GetFromI();
   const int j0 = a.GetFromJ();
   const int in = a.GetToI();
   const int jn = a.GetToJ();

   LEM_CHECKIT_Z( i0==b.GetFromI() );
   LEM_CHECKIT_Z( j0==b.GetFromJ() );
   LEM_CHECKIT_Z( in==b.GetToI()   );
   LEM_CHECKIT_Z( jn==b.GetToJ()   );

   BMT res(i0,in,j0,jn);

   for( int i=i0; i<=in; i++ )
    for( int j=j0; j<=jn; j++ )
     res.set( i, j, a(i,j)-b(i,j) );

   return res;
  }
*/



  // **********************************************
  // This subroutine transposes an n by n matrix a.
  // **********************************************
  template <class T>
  inline const BMT transpose( const BMT& a )
  {
   const int i0 = a.GetFromI();
   const int j0 = a.GetFromJ();
   const int in = a.GetToI();
   const int jn = a.GetToJ();

   BMT res( j0, jn, i0, in );

   for( int i=j0; i<=jn; i++ )
    for( int j=i0; j<=in; j++ )
     res.set( i, j, a.get(j,i) );

   return res;
  }

  #if !defined LEM_NOREAL
  typedef BaseMatrix<lem::Math::REAL> RMatrix;
  typedef BaseMatrix<float> FMatrix;
  #endif


  class OFormatter;

  extern void print(
                    const RMatrix& A,
                    OFormatter& file,
                    int format,
                    const char *dformat
                   );

  extern void print_sym( const RMatrix &a, OFormatter &f );
  extern void print_matrix_info( const RMatrix &a, OFormatter &to );


  #undef BMT
 } // namespace 'lem'

#endif
