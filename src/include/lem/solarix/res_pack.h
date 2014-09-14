// -----------------------------------------------------------------------------
// File RES_PACK.H
//
// (c) Koziev Elijah
//
// Content:
// Класс Res_Pack - пачка решений, список вариаторов (клонов класса
// Variator), используется в Итерациях SOL_CAA. Пачки решений хранятьс
// в списке внутри клона класса SolPhrasoBlock.
// -----------------------------------------------------------------------------
//
// CD->07.09.1997
// LC->11.02.2012
// --------------

#if !defined( SOL_RESPACK__H ) && !defined SOL_NO_AA
#define SOL_RESPACK__H
#pragma once

 #include <lem/math/fp1.h>
 #include <lem/stl.h>

 #include <lem/solarix/variator.h>

 namespace Solarix
 {
  using lem::MCollect;
 /***********************************************************************
  Пачка Решений - набор вариаторов для Синтаксических Итераций ЦАА.
  По своему смыслу эти вариаторы являются альтернативными путями анализа
  входной фразы. Объединять вариаторы в обном списке заставляет их общий
  генезис - из одной исходной фразы, и удобство поддержки параллельной
  обработки вариаторов - можно легко избегать дублирования вариаторов
  при слиянии путей анализа.
 ************************************************************************/
 class SynGram;

 class Res_Pack
 {
  private:
   MCollect<Variator*> list; // Список вариаторов.

   void Init( const Res_Pack &rp );

  public:
   Res_Pack(void);
   Res_Pack( const Res_Pack &rp );
   ~Res_Pack(void);

   void Delete(void);

   void Clear(void);

   inline void reserve( int n ) { list.reserve(n); }

   void operator=( const Res_Pack &rp );

   inline       MCollect<Variator*>& vars(void)       { return list; }
   inline const MCollect<Variator*>& vars(void) const { return list; }

/*
   int FindVarByKey( int Key ) const;
   void DeleteByKey( int Key );
   void DeleteVariator( int var_idx );
   bool IsThereMultiplicator( SynGram &sg ) const;

   bool Find( SynGram &sg, const Variator& t, bool strict_position ) const;
*/

/*
   #if defined SOL_CAA
   void Doublicate( SynGram &sg, Variator *variator, bool strict_position );
   void CutParents( MCollect<Variator*> &trash );
   void OnIterEnd(void);
   void MarkUsed(void);
   void DoRemark(void);
   void Unfroze(void);
   void Squeeze( Real1 k );
   bool HasBeenChanged(void);
   inline void WasChange(void) { was_a_change=true; }
   void MulVal( Real1 Val );
   void FreshVarsUp(void);
   void DropParents(void);
   #endif
*/

   #if defined SOL_LOADBIN
   void LoadBin( lem::Stream &binfile );
   #endif

   void SaveBin( lem::Stream &binfile ) const;

   void Add( Variator *to_add );
   void AddFirst( Variator *to_add );

   inline Res_Pack& operator<<( Variator *to_add )
   { Add(to_add); return *this; }

   void ForgetPtr( int i );
   inline void SetPtr( int i, Variator *Var ) { list[i]=Var; }

   void Print(
              OFormatter &s,
              SynGram &s_gram,
              bool detailed=false
             ) const;

   void PrintRoots(
                   OFormatter &s,
                   bool Decoration=true,
                   bool EntryKeys=true
                  ) const;

/*
   #if defined SOL_CAA
   void DoDestructVariatorByKey(
                                int Var_Key,
                                std::vector<PA_PrologSpace*> &pa_spaces,
                                PrologAutomat &pa
                               );
   #endif
*/

   // Копирует содержимое (вариаторы) из пачки решения - забирает указатели.
   void Recevoire( Res_Pack *src );

   // Возвращает число корневых узлов в самом компактном вариаторе
   int GetShortestVar(void) const;

   // Оставляет только вариаторы с минимальным числом корней.
   void Save_Shortest_Vars(void);

   // пересортируем так, чтобы сначала шли самые короткие варианты
   void SortByLengthDescending(void);

   void SortByCoverageAscending(void);
 };


/*
 #if defined SOL_CAA
 inline bool Res_Pack::HasBeenChanged(void)
 {
  const bool ret = was_a_change;
  was_a_change=false;
  return ret;
 }
 #endif
*/

 inline void Res_Pack::Add( Variator *to_add )
 {
  list.push_back( to_add );
  #if defined SOL_CAA
//  was_a_change=true;
  #endif
  return;
 }

 inline void Res_Pack::AddFirst( Variator *to_add )
 {
  list.Insert( 0, to_add );
  #if defined SOL_CAA
//  was_a_change=true;
  #endif
  return;
 }

 inline void Res_Pack::Clear(void)
 {
  list.clear();

  #if defined SOL_CAA
//  was_a_change=false;
  #endif

  return;
 }

 /*****************************************************************
  Модификация списка указателей на вариаторы: указатель с индексом
  iVar заменяется на NULL, устанавливается флаг измененности пачки.
  Удаления старого указателя по индексу iVar не происходит.
 ******************************************************************/
 inline void Res_Pack::ForgetPtr( int iVar )
 {
  list[iVar]=NULL;
  #if defined SOL_CAA
//  was_a_change=true;
  #endif
  return;
 }

 } // namespace 'Solarix'

#endif
