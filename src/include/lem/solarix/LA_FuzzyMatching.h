#ifndef LA_FuzzyMatching__H
#define LA_FuzzyMatching__H
#pragma once

 #include <lem/math/fp1.h>

 namespace Solarix
 {
  #if defined SOL_CAA
  /**************************************************************
   Константы готовности вариатора порождать новые вариаторы,
   то есть участвовать в итерациях Фонетического Алеф-Алгоритма.
  ***************************************************************/
  enum { SOL_LA_FREE_VAR=0, SOL_LA_USED_VAR };

  class LA_Variator : public Lexem
  {
   private:
    int tran;  // Число изменений исходной лексемы, которые дали нашу.
    int flag;  // Признак использованности вариатора для порождений.
    lem::Real1 val; // Текущая оценка достоверности информации в вариаторе.

   public:
    LA_Variator(void):Lexem()
    {
     tran = 0;
     flag = SOL_LA_FREE_VAR;
     val  = 100;
    }

    LA_Variator( const Lexem &s ):Lexem(s)
    {
     tran = 0;
     flag = SOL_LA_FREE_VAR;
     val  = 100;
    }

    LA_Variator( const LA_Variator& lv ):Lexem(lv)
    {
     tran = lv.tran;
     flag = lv.flag;
     val  = lv.val;
    }

    inline void operator=( const LA_Variator& lv )
    {
     Lexem::operator=(lv);
     tran=lv.tran; flag=lv.flag; val=lv.val;
     return;
    }

    inline void set( const Lexem l ) { Lexem::operator=(l); }

    inline bool IsFrozen(void) const { return flag==SOL_LA_USED_VAR; }
    inline void Froze(void) { flag=SOL_LA_USED_VAR; }

    inline int get_Tran(void) const { return tran; }
    inline void IncTran(void) { tran++; }
    inline void set_Tran( int n ) { tran=n; }

    inline lem::Real1 get_Val(void) const { return val; }
    inline void set_Val( lem::Real1 factor ) { val = factor; }

    inline bool operator==( const LA_Variator &lv ) const
    { return Lexem::operator==(lv); }
  };

  /*************************************************
   Пачка Решений для Фонетического Алеф-Автомата.
  **************************************************/
  class LA_Pack : public lem::PtrCollect<LA_Variator>, boost::noncopyable
                         // Список вариантов этого слова, полученных
                         // применением заданных правил фонетической
                         // продукции
  {
   private:
    Lexem origin;               // Исходное слово

   public:
    LA_Pack(void) {}

    explicit LA_Pack( const Lexem &l )
    {
     origin=l;
     push_back( new LA_Variator(origin) );
    }

    inline const Lexem& GetOrigin(void) const { return origin; }
  };

  /****************************************************************
   Внутреннее представление фонетического инварианта предложения,
   используется при итерациях Фонетического Алеф-Алгоритма.
  *****************************************************************/
  class LA_Sentence : public lem::MCollect<LA_Variator>
  {
   private:
    lem::Real1 val;                 // Оценка достоверности распознания слов предложения
                               // как лексем.

   public:
    LA_Sentence(void):lem::MCollect<LA_Variator>() { val=100; }
    LA_Sentence( const LA_Sentence &x ):lem::MCollect<LA_Variator>(x)
    { val=x.val; }

    inline void operator=( const LA_Sentence &x )
    {
     lem::MCollect<LA_Variator>::operator=(x);
     val = x.val;
    }

    inline void Add( const LA_Variator &lv )
    {
     Add( lv );
     val = val*lv.get_Val();
     return;
    }

    inline lem::Real1 GetVal(void) const { return val; }
  };

 #endif

 } // namespace 'Solarix'

#endif
