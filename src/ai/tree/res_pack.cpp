// -----------------------------------------------------------------------------
// File RES_PACK.CPP
//
// (c) Koziev Elijah
//
// Content:
// Класс Res_Pack - набор альтернативных вариаторов для обработки в Итерациях
// ЦАА Продукционной Машины. Используется Лексическим, Алеф-Автоматом, Речевым
// Автоматом и другими модулями Системы.
// -----------------------------------------------------------------------------
//
// CD->14.11.1995
// LC->18.08.2011
// --------------

#if !defined SOL_NO_AA

#include <lem/solarix/aa_autom.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/variator.h>
#include <lem/solarix/res_pack.h>

using namespace lem;
using namespace Solarix;

Res_Pack::Res_Pack(void)
{
// was_a_change=false;
 list.reserve(32);
}


Res_Pack::Res_Pack( const Res_Pack &rp )
{ Init(rp); }

Res_Pack::~Res_Pack(void)
{
 Delete();
 Clear();
 return;
}

void Res_Pack::Delete(void)
{
 for( lem::Container::size_type i=0; i<list.size(); ++i )
  delete list[i];

 return;
}

void Res_Pack::Init( const Res_Pack &rp )
{
 LEM_CHECKIT_Z( &rp != NULL );
// was_a_change = rp.was_a_change;

 const Container::size_type NI = rp.list.size();
 list.resize(NI);
 
 for( Container::size_type i=0; i<NI; i++ )
  list[i] = new Variator(*rp.list[i]);

 return;
}


void Res_Pack::operator=( const Res_Pack &rp )
{
 if( this==&rp )
  return;

 Delete();
 Clear();
 Init(rp);
 return;
}



/******************************************************************
 Попытаемся найти в нашем списке указанный вариатор. Процедура
 вызывается ЦАА, чтобы не допускать дублирования решения при
 продукции нового контекста (то есть при расщеплении решения на
 два новых потока). Используется буквальное сравнение вариаторов!
*******************************************************************/
/*
bool Res_Pack::Find(
                    SynGram &sg,
                    const Variator &variator,
                    bool strict_position
                   ) const
{
 for( Container::size_type i=0; i<list.size(); i++ )
  if( list[i] && list[i]->DoesMatch(sg,variator,strict_position) )
   return true;

 return false;
}
*/


/*
#if defined SOL_CAA
void Res_Pack::Doublicate( SynGram &sg, Variator *variator, bool strict_position )
{
 for( Container::size_type i=0; i<list.size(); i++ )
  if( list[i]->DoesMatch( sg, *variator, strict_position ) )
   {
    list[i]->SetCoolFlag( variator->GetCoolFlag() );
    break;
   }

 delete variator;
 return;
}
#endif
*/


#if defined SOL_CAA

/**********************************************************************
 Просматривает список вариаторов и те из них, которые были использованы
 для порождения новых вариаторов в итерации ЦАА, помечаются.
***********************************************************************/
/*
void Res_Pack::MarkUsed(void)
{
 for( Container::size_type i=0; i<list.size(); i++ )
  list[i]->MarkUsed();

 return;
}

void Res_Pack::OnIterEnd(void)
{
 for( Container::size_type i=0; i<list.size(); i++ )
  list[i]->OnIterEnd();

 return;
}
*/
#endif

/*
#if defined SOL_CAA
void Res_Pack::Unfroze(void)
{
 for( Container::size_type i=0; i<list.size(); i++ )
  list[i]->Unfroze();

 return;
}
#endif
*/


/*
#if defined SOL_CAA
void Res_Pack::DoRemark(void)
{
 for( Container::size_type i=0; i<list.size(); i++ )
  list[i]->DoRemark();

 return;
}
#endif

#if defined SOL_CAA
void Res_Pack::FreshVarsUp(void)
{
 for( Container::size_type i=0; i<list.size(); i++ )
  list[i]->FreshUp();

 return;
}
#endif
*/


#if defined SOL_CAA
/***********************************************************************
 Из списка вариаторов исключаем помеченные как породившие новые,
 добавляем их в корзину trash.
*************************************************************************/
/*
void Res_Pack::CutParents( MCollect<Variator*> &trash )
{
 int i=0;
 while( i<CastSizeToInt(list.size()) )
  if(
     list[i]->GetCoolFlag()==SOL_CAA_PARENT_ALT ||
     list[i]->GetCoolFlag()==SOL_CAA_USED_ALT
    )
   {
    trash.push_back( list[i] );
    list.Remove( i );
   }
  else
   i++;

 return;
}
*/
#endif


#if defined SOL_CAA
/***********************************************************************
 Из списка вариаторов исключаем помеченные как породившие новые.
*************************************************************************/
/*
void Res_Pack::DropParents(void)
{
 lem::Container::size_type i=0;
 while( i<list.size() )
  if( list[i]->IsParent() )
   {
    delete list[i];
    list.Remove( i );
   }
  else
   i++;

 return;
}
*/
#endif


#if defined SOL_CAA
/***************************************************************************
 Пересортировываем вариаторы в порядке убывания достоверности и те из них,
 что имеют вероятность меньше k*Pmax, где Pmax - максимальная надежность
 среди вариаторв, убиваем. Используется во время итераций ЦАА для сокращени
 выполняемой информационной работы
****************************************************************************/
/*
void Res_Pack::Squeeze( Real1 k )
{
 // Сортируем вариаторы в порядке убывания их достоверности методом Шелла.
 int i,j,gap;
 const int N=list.size();
 Variator *dummy;

 for( gap=N/2; gap>0; gap/=2 )
  for( i=gap; i<N; i++ )
   for( j=i-gap; j>=0; j-=gap )
    {
     if( list[j+gap]->GetVal() < list[j]->GetVal() )
      break;

     dummy       = list[j];
     list[j]     = list[j+gap];
     list[j+gap] = dummy;
    }

 // Теперь вариаторы с надежностью<k*Pmax уничтожаем.
 // Определяем Pmax.
 Real1 Pmax(0);
 for( i=N-1; i>=0; i-- )
  Pmax = lem_1max( list[i]->GetVal(), list[i]->GetVal() );

 // Получаем нижнюю границу допуска.
 const Real1 Pbound = Pmax * k;

 for( i=0; i<N; i++ )
  if( list[i]->GetVal() < Pbound )
   {
    // Отседова и до конца списка - удаляем, учитывая, что список
    // отсортирован.
    for( j=i; j<N; j++ )
     delete list[j];

    // Уничтожаем хвост из удаленных вариаторов.
LEM_STOPIT;
    list.resize(i); // ???
    break;
   }

 return;
}
*/
#endif

/**********************************************************************
 Печатаем информацию о содержимом Пачки Решений в указанный текстовый
 поток s.
***********************************************************************/
void Res_Pack::Print(
                     OFormatter &s,
                     SynGram &gram,
                     bool detailed
                    ) const
{
 s.printf(
          "Result Pack contains %d variator(s)\n"
          , list.size()
         );

 for( Container::size_type i=0; i<list.size(); i++ )
  {
   s.printf( "variator #%d ", i );
   list[i]->Print(s,gram,detailed);
  }

 return;
}


#if defined SOL_CAA
/**************************************************************
 Достоверности всех вариаторов в нашей пачке домножаем на Val.
***************************************************************/
/*
void Res_Pack::MulVal( Real1 Val )
{
 if( Val!=Real1(100) )
  for( Container::size_type i=0; i<list.size(); i++ )
   list[i]->MulVal(Val);

 return;
}*/
#endif

#if defined SOL_CAA
/*
void Res_Pack::DoDestructVariatorByKey(
                                       int Var_Key,
                                       vector<PA_PrologSpace*> &pa_spaces,
                                       PrologAutomat &pa
                                      )
{
 for( Container::size_type i=0; i<list.size(); i++ )
  if( list[i]->GetKey() == Var_Key )
   {
    list[i]->CleanUp(pa_spaces,pa);
    delete list[i];
    ForgetPtr(i);
    return;
   }

 return;
}*/
#endif

/**********************************************************************
 Отыскиваем индекс вариатора в пачке по заданному его ключу. Будет
 возвращено значение UNKNOWN, если вариаторв с таким ключем в пачке
 не содержится.
***********************************************************************/
/*
int Res_Pack::FindVarByKey( int Key ) const
{
 if( Key==UNKNOWN )
  return UNKNOWN;

 for( Container::size_type i=0; i<list.size(); i++ )
  if( list[i]->GetKey()==Key )
   return i;

 return UNKNOWN;
}
*/

#if defined SOL_LOADBIN
void Res_Pack::LoadBin( Stream &bin )
{
 #if defined SOL_CAA
// was_a_change = false;
 #endif

 int n;
 bin.read( &n, sizeof(n) );
 list.reserve(n);

 for( int i=0; i<n; i++ )
  Add( new Variator(bin) );

 return;
}
#endif

void Res_Pack::SaveBin( Stream &bin ) const
{
 int n=list.size();
 bin.write( &n, sizeof(n) );
 for( int i=0; i<n; i++ )
  list[i]->SaveBin(bin);

 return;
}

/*
bool Res_Pack::IsThereMultiplicator( SynGram &sg ) const
{
 for( Container::size_type ivar=0; ivar<list.size(); ivar++ )
  if( list[ivar]->IsThereMultiplicator(sg) )
   return true;

 return false;
}
*/



/***********************************************************************
 Переписываем себе указатели на вариаторы из списка src и очищаем
 src, чтобы вариаторы не были удалены при работе деструктора delete src.
************************************************************************/
void Res_Pack::Recevoire( Res_Pack *src )
{
 for( Container::size_type i=0; i<src->list.size(); i++ )
  list.push_back( src->list[i] );

 src->list.clear();
 return;
}


/*
void Res_Pack::DeleteByKey( int key )
{
 for( Container::size_type i=0; i<list.size(); i++ )
  if( list[i]->GetKey()==key )
   {
    delete list[i];
    list.Remove(i);
    break;
   }

 return;
}
*/


int Res_Pack::GetShortestVar(void) const
{
 int ires=UNKNOWN, min_len=INT_MAX;

 for( Container::size_type i=0; i<list.size(); i++ )
  if( list[i]->size()<min_len )
   // Запоминаем индекс и длину минимального вариатора
   if( (min_len=list[ ires=i ]->size())==1 )
    // Длины меньше чем 1 быть не может!
    break;

 return ires;
}

#if defined SOL_CAA
void Res_Pack::PrintRoots(
                           OFormatter &s,
                           bool Decoration,
                           bool EntryKeys
                          ) const
{
 if( Decoration )
  s.printf( "Res pack contains %d variator(s):\n", list.size() );

 for( Container::size_type i=0; i<list.size(); i++ )
  {
   if( Decoration )
    s.printf( "#%W2d ", i );

   list[i]->PrintRoots(s,Decoration,EntryKeys);
   s.eol();
  }

 return;
}
#endif


// Оставляет только вариаторы с минимальным числом корней.
void Res_Pack::Save_Shortest_Vars(void)
{
 if( list.empty() )
  return;

 int min_len=INT_MAX;

 for( Container::size_type i=0; i<list.size(); i++ )
  if( list[i]->size()<min_len )
   // Запоминаем индекс и длину минимального вариатора
   if( (min_len=list[ i ]->size())==1 )
    // Длины меньше чем 1 быть не может!
    break;

 for( int i2=list.size()-1; i2>=0; i2-- )
  if( list[i2]->size() > min_len )
   { 
    delete list[i2];
    list.Remove(i2);
   }

 return;
}

/*
void Res_Pack::DeleteVariator( int var_idx )
{
 delete list[var_idx];
 list.Remove(var_idx);
 return;
}
*/


static bool sorter_var_by_len_desc( const Variator *a, const Variator *b )
{
 return a->size() < b->size();
}

// пересортируем так, чтобы сначала шли самые короткие варианты
void Res_Pack::SortByLengthDescending(void)
{
 std::sort( list.begin(), list.end(), sorter_var_by_len_desc );
 #if LEM_DEBUGGING==1
 int l_begin = list.front()->size();
 int l_end = list.back()->size();
 #endif
 return;
}

/*
static bool sorter_var_by_coverage_len( const Variator *a, const Variator *b )
{
 #if defined SOL_CAA
 if( a->GetMorphologicalCoverage() < b->GetMorphologicalCoverage() )
  return true;

 if( a->GetMorphologicalCoverage() == b->GetMorphologicalCoverage() )
  return a->size() < b->size();
 #endif

 return false;
}
*/


void Res_Pack::SortByCoverageAscending(void)
{
// std::sort( list.begin(), list.end(), sorter_var_by_coverage_len );
 return;
}

#endif

