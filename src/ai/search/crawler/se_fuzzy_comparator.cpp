// -----------------------------------------------------------------------------
// File SE_FUZZY_COMPARATOR.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// Fuzzy_Comparator - автомат для выполнения нечетких сравнений слов по
//                    задаваемым в словаре правилам.
//
// 30.11.2006 - изменен алгоритм сопоставления, улучшено вычисление "штрафных"
//              баллов при обнаружении отличия, добавлена работа с правилами 2->1
//
// 01.12.2006 - добавлена работа с правилами 3->1 и общий блок для правил N->1
// 10.09.2008 - поправлен баг в алгоритме - из-за двойного инкремента итератора
//              он вылетал за допустимый диапазон.
// -----------------------------------------------------------------------------
//
// CD->15.08.2005
// LC->30.05.2011
// --------------

#include <string.h>

#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/se_search_options.h>
#include <lem/solarix/LA_PhoneticMatcher.h>
#include <lem/solarix/LA_PhoneticRule.h>
#include <lem/solarix/LA_PhoneticRuleEnumerator.h>
//#include <lem/solarix/pm_rule.h>
#include <lem/solarix/se_fuzzy_comparator.h>

using namespace std;
using namespace lem;
using namespace Solarix;
using namespace Solarix::Search_Engine;


Fuzzy_Comparator::Fuzzy_Comparator(void)
{
 flags = NULL;
// affixes = NULL;

 // Предельные значения отличия сопоставляемых слов по умолчанию.
 max_miss  = 2;
 max_subst = 2;
 max_diff  = 2;

 wchar_t X[] = {
                L'\x0451', L'\x0415',
                L'\x0401', L'\x0415',
                L'\x0439', L'\x0418',
                L'\x0419', L'\x0418',
               };

 int n=DIM_A(X);
 for( int i=0; i<n; i+=2 )
  char_to_base.insert( std::make_pair( X[i], X[i+1] ) );
}


Fuzzy_Comparator::~Fuzzy_Comparator(void)
{
}


void Fuzzy_Comparator::ApplyDictionary( const Dictionary &dict )
{
 if( !!dict.affix_table )
  affixes = dict.affix_table;

 // Заполним таблицу пар символов, которые формально отличаются,
 // но в некоторых случаях могут считаться сопоставимыми
 const LA_PhoneticMatcherForLanguage &f = * dict.GetLexAuto().GetPhoneticMatcher().GetMatcherForLanguage(ANY_STATE);
 lem::Ptr<LA_PhoneticRuleEnumerator> rules = f.EnumerateRules();

 while( rules->Fetch() )
  {
   const LA_PhoneticRule &r = rules->Get();

   if( r.Is_1_to_1() )
    {
     const wchar_t c1 = To_Base( r.GetCondition().GetContext().front() );
     const wchar_t c2 = To_Base( r.GetResult().GetContext().front() );
     char_eq.insert( std::make_pair( pair_char(c1,c2), r.GetVal().GetFloat() ) );
     char_eq.insert( std::make_pair( pair_char(c2,c1), r.GetVal().GetFloat() ) );
    }
   else
    {
     const UCString &c1 = r.GetCondition().GetContext();
     const UCString &c2 = r.GetResult().GetContext();

     if( r.GetCondition().length()==2 && r.GetResult().length()==2 )
      {
       // Правила 2->2, например "ШИ-ШЫ"
       pair_char p1( To_Base(c1.front()), To_Base(c1[1]) );
       pair_char p2( To_Base(c2.front()), To_Base(c2[1]) );

       char22_eq.insert( std::make_pair( pair_str22(p1,p2), r.GetVal().GetFloat() ) );
       char22_eq.insert( std::make_pair( pair_str22(p2,p1), r.GetVal().GetFloat() ) );
      }
     else if( r.GetCondition().length()==2 && r.GetResult().length()==1 )
      {
       // Правила 2->1, например "ph-f"
       pair_char p1( To_Base(c1.front()), To_Base(c1[1]) );
       wchar_t p2( To_Base(c2.front()) );

       char21_eq.insert( std::make_pair( pair_str21(p1,p2), r.GetVal().GetFloat() ) );
      }
     else if( r.GetCondition().length()==1 && r.GetResult().length()==2 )
      {
       // Правила 1->2, например "x-cs"
       pair_char p1( To_Base(c2.front()), To_Base(c2[1]) );
       wchar_t p2( To_Base(c1.front()) );

       char21_eq.insert( std::make_pair( pair_str21(p1,p2), r.GetVal().GetFloat() ) );
      }
     else if( r.GetCondition().length()==3 && r.GetResult().length()==1 )
      {
       // Правила 3->1, например "ph-f"
       lem::triple<wchar_t,wchar_t,wchar_t> p1( To_Base(c1[0]), To_Base(c1[1]), To_Base(c1[2]) );
       wchar_t p2( c2.front() );

       char31_eq.insert( std::make_pair( pair_str31(p1,p2), r.GetVal().GetFloat() ) );
      }
     else if( r.GetCondition().length()==1 && r.GetResult().length()==3 )
      {
       // Правила 1->3, например "x-cs"
       lem::triple<wchar_t,wchar_t,wchar_t> p1( To_Base(c2[0]), To_Base(c2[1]), To_Base(c2[2]) );
       wchar_t p2( c1.front() );

       char31_eq.insert( std::make_pair( pair_str31(p1,p2), r.GetVal().GetFloat() ) );
      }
     else if( r.GetCondition().length()!=1 || r.GetResult().length()!=1 )
      {
       // Прочие правила, не относящиеся к двум предыдущим категориям.

       // первые буквы условия и следствия дают первичный ключ (неуникальный) для
       // быстрого применения нужных правил
       pair_char pk( To_Base(c1.front()), To_Base(c2.front()) );
       charN1_eq.insert( std::make_pair( pk, &r ) );

////mout->printf( "%us %us\n", c1.c_str(), c2.c_str() );
      }
    }
  }

 return;
}


void Fuzzy_Comparator::SetOptions( const Search_Options *Flags )
{
 flags=Flags;

 max_miss = max_subst = max_diff = flags->n_max_miss;

 return;
}


// *********************************************************************
// Интерфейсный метод для использования внешними процедурами - нечеткое
// сравнение двух лексем.
//
// Возвращается - проценты (0...100) сопоставимости лексем. 0 - лексемы
// несопоставимы, 100 - полное совпадение лексем.
// *********************************************************************
int Fuzzy_Comparator::Eq( const UCString &A, const UCString &B ) const
{
 const float miss = Compare( A.c_str(), B.c_str(), 0 );
 
 if( miss > max_diff )
  return 0;

 const int len = (A.length()+B.length())/2;

 return len ? int((len-miss)*100 / len) : 0;
}


// *********************************************************************
// Внутренняя процедура сопоставления
// *********************************************************************
float Fuzzy_Comparator::Compare( const wchar_t *A, const wchar_t *B, float cur_miss ) const
{
 int len=0;
 float n_miss=0;
 float val;

 int iA=0, iB=0;
 while( A[iA] && B[iB] && (n_miss+cur_miss)<=max_miss )
  {
   const wchar_t cA = To_Base(A[iA]);
   const wchar_t cB = To_Base(B[iB]);

   const wchar_t cA_1 = iA ? To_Base(A[iA-1]) : 0;
   const wchar_t cB_1 = iB ? To_Base(B[iB-1]) : 0;

   if( cA==cB )
    {
     // Символы в одинаковых позициях совпали.
     iA++; iB++;
     len++;
     continue;
    }

   // Несовпадение символов. 
   // Сравнимы ли символы? 
   if( Eq_Char( cA, cB, val ) )
    {
     // Да - продвигшаем позицию вперед на символ продолжаем.
     n_miss += (float)(1.-val);
     iA++; iB++;
     len++;
     continue;
    }

   // Не совпали символы, и эти символы не сопоставимы.

   // Возможен вариант с удвоением символа - удвоенный символ 
   // считается совпадающим с одинарным.

   if( iA>0 && cA_1==cA && cA==cB_1 ) // удвоение в A
    {
     return Compare( A+iA+1, B+iB, cur_miss+n_miss );
    }
   else if( iB>0 && cB_1==cB && cB==cA_1 ) // удвоение в B
    {
     return Compare( A+iA, B+iB+1, cur_miss+n_miss );
    }
   else
    {
     // Попробуем применить сложные морфологические правила, взятые из
     // словаря.

     // Сначала - быстрая проверка на правила 2->2
     
     if( iA>0 && iB>0)
      {
       pair_char pa1( cA_1, cA );
       pair_char pb1( cB_1, cB );

       C22E_ITER it1 = char22_eq.find( pair_str22(pa1,pb1) );
       if( it1 != char22_eq.end() )
        {
         iA++; iB++;
         len++;
         n_miss += (float)(1.-it1->second);
         continue; 
        }

       C22E_ITER it2 = char22_eq.find( pair_str22(pb1,pa1) );
       if( it2 != char22_eq.end() )
        {
         iA++; iB++;
         len++;
         n_miss += (float)(1.-it2->second);
         continue; 
        }
      }

     const wchar_t cA_2 = To_Base(A[iA+1]);
     const wchar_t cB_2 = To_Base(B[iB+1]);

     pair_char pa1( cA, cA_2 );
     pair_char pb1( cB, cB_2 );

     C22E_ITER it1 = char22_eq.find( pair_str22(pa1,pb1) );
     if( it1 != char22_eq.end() )
      {
       iA+=2; iB+=2;
       len+=2;
       n_miss += (float)(1.-it1->second);
       continue; 
      }


     C22E_ITER it2 = char22_eq.find( pair_str22(pb1,pa1) );
     if( it2 != char22_eq.end() )
      {
       iA+=2; iB+=2;
       len+=2;
       n_miss += (float)(1.0-it2->second);
       continue; 
      }

     // Правила 2->1 (типа PH->F)
    
     if( cA_2!=0 )
      {
       pair_char pa21( cA, cA_2 );
       C21E_ITER it3 = char21_eq.find( pair_str21(pa21,cB) );
       if( it3 != char21_eq.end() )
        {
         iA+=2; iB++;
         len++;
         n_miss += (float)(1.-it3->second);
         continue; 
        }
      }

     if( cB_2!=0 )
      {
       pair_char pb21( cB, cB_2 );
       C21E_ITER it3 = char21_eq.find( pair_str21(pb21,cA) );
       if( it3 != char21_eq.end() )
        {
         iA++; iB+=2;
         len++;
         n_miss += (float)(1.-it3->second);
         continue; 
        }
      }

     
     // Правила 3->1 (типа TCH->Ч)
    
     const wchar_t cA_3 = To_Base(A[iA+2]);
     if( cA_3!=0 )
      {
       lem::triple<wchar_t,wchar_t,wchar_t> pa31( cA, cA_2, cA_3 );
       C31E_ITER it4 = char31_eq.find( pair_str31(pa31,cB) );
       if( it4 != char31_eq.end() )
        {
         iA+=3; iB++;
         len++;
         n_miss += (float)(1.-it4->second);
         continue; 
        } 
      }

     const wchar_t cB_3 = To_Base(B[iB+2]);
     if( cB_3!=0 )
      {
       lem::triple<wchar_t,wchar_t,wchar_t> pb31( cB, cB_2, cB_3 );
       C31E_ITER it4 = char31_eq.find( pair_str31(pb31,cA) );
       if( it4 != char31_eq.end() )
        {
         iA++; iB+=3;
         len++;
         n_miss += (float)(1.-it4->second);
         continue; 
        }
      }

     // Пробуем остальные правила
     bool rule_applied=false;

     for( int iflip=0; iflip<2 && !rule_applied; iflip++ )
      {
       const wchar_t *Aflip = iflip==0 ? A : B;
       const wchar_t *Bflip = iflip==0 ? B : A;
       const wchar_t cAA = To_Base(Aflip[iA]);
       const wchar_t cBB = To_Base(Bflip[iB]);

       std::pair<CN1E_ITER,CN1E_ITER> range1 = charN1_eq.equal_range( pair_char( cAA, cBB ) );
       CN1E_ITER iend = charN1_eq.end();

       CN1E_ITER it1 = range1.first;
       if( it1!=charN1_eq.end() )
        {
         CN1E_ITER it2 = range1.second;

         for( CN1E_ITER it=it1; it!=it2; it++ )
          { 
           const UCString &ruleA = it->second->GetCondition().GetContext();
           const UCString &ruleB = it->second->GetResult().GetContext();
 
           // Условие сравниваем со строкой A, следствие - со строкой B.
           // Первые символы уже проверены (они дают первичный ключ для группы
           // правил).
           int iiA=1;
           bool match=true;

           while( iiA<ruleA.length() )
            {
             if( To_Base(A[iA+iiA])!=To_Base(ruleA[iiA]) )
              {
               match=false;
               break;
              }
             iiA++;
            }

           if( !match )
            {
             continue;
            }

           int iiB=1;

           while( iiB<ruleB.length() )
            {
             if( To_Base(B[iB+iiB])!=To_Base(ruleB[iiB]) )
              {
               match=false;
               break;
              }
             iiB++;
            }

           if( !match )
            {
             continue;
            }

           // Итак, правило подходит.
           rule_applied = true;

           iA+=ruleA.length();
           iB+=ruleB.length();
           n_miss += (float)(1.-it->second->GetVal().GetFloat());
           break;
          }   
        }
      }

     if( rule_applied )
      continue; 
    }

   if( (n_miss+cur_miss) > max_miss )
    return n_miss+cur_miss;

   const bool bA = A[iA+1]!=0;
   const bool bB = B[iB+1]!=0;

   if( !bA && !bB )
    {
     iA++; iB++;
     n_miss+=1.0;
     break;
    }

   float r3 = bA && bB ? Compare( A+iA+1, B+iB+1, cur_miss+n_miss+1 ) : UNCOMPARABLE;
   float r1 = bA       ? Compare( A+iA+1, B+iB,   cur_miss+n_miss+1 ) : UNCOMPARABLE;
   float r2 = bB       ? Compare( A+iA,   B+iB+1, cur_miss+n_miss+1 ) : UNCOMPARABLE;

   float r = std::min( r1, std::min( r2, r3 ) );
   return r;
  }

 if( A[iA]!=B[iB] )
  {
   // одно из слов закончилось раньше
   n_miss += ::wcslen( (const wchar_t*)(A+iA) ) + ::wcslen( B+iB );
  }

 return n_miss+cur_miss;
}




void Fuzzy_Comparator::LoadBin( Stream &bin )
{
 affixes = boost::shared_ptr<Solarix::Affix_Table>( new Affix_Table );
 affixes->LoadBin(bin);
 return;
}

