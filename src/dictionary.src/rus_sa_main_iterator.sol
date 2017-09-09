// -----------------------------------------------------------------------------
// File RUS_SA_MAIN_ITERATOR.SOL
//
// (c) Koziev Elijah
//
// Content:
// Syntax analyzer: main iterator for syntax analysis. It controls the process
// of grammatical trees creation while sentence analysis.
//
// Синтаксический анализатор: главный итератор для русского языка
//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml
// -----------------------------------------------------------------------------
//
// CD->05.10.1995
// LC->22.06.2011
// --------------

#include "pm_doac.h"
#include "aa_rules.inc"

automat aa
{
 #pragma floating off

 // ********************************************************************
 // Основной итератор Системы: вызывается Грамматическим Алеф-Автоматом
 // самостоятельно при поступлении на вход новой фразы.
 // Имя не менять!
 // ********************************************************************
 iterator MainIterator language=Russian
 {
  {
//print { beginning number of variators= $vars_count }
//print { $pack }

   // Сразу определяем тип предложения и убираем финальный пунктуатор.
   REPLACE AA_RULES_SENT

   // Особо обрабатываем апострофы и кавычки
   REPLACE AA_QUOTES

   REPLACE AA_RULES_IDIOM_1
   
   // после того как...
   REPLACE AA_RULES_AFTER0

   // до того, как
   REPLACE AA_RULES_BEFORE0

   // вместо того, чтобы... 
   REPLACE AA_RULES_INSTEAD_OF0
  
   // потому что....
   REPLACE AA_RULES_BECAUSE0
   
   // Кошка спит для того, чтобы отдыхать.
   REPLACE AA_RULES_IN_ORDER_TO0

/*
   // вводные слова и словосочетания
   REPLACE AA_RULES_INTRO
   REPLACE AA_RULES_INTRO_2
*/

   if count(НАРЕЧИЕ)>1 
    then
     {
	  // НАРЕЧИЕ + НАРЕЧИЕ
      // 'Очень быстро' 
      REPLACE LINK_ADVERB_NEXT_1
      REPLACE LINK_ADVERB_NEXT_2
      REPLACE LINK_ADVERB_PLUS_ADVERB
	 } 

   // Разные свертки типа 'НЕ ИГРАТЬ'
   REPLACE AA_RULES_CONV

   REPLACE LINK_ADVERB_BUT
   
   // По возможности сразу свернем сочетания наречия и некоторых частей речи
   REPLACE RusSA_Instant_Adverb
   
   // Повторим попытку свернуть конструкции типа БУДУ БЫСТРО СПАТЬ
   REPLACE AA_RULES_CONV

   // СВЕРТКИ - ПРЕДЛОГИ С СУЩЕСТВИТЕЛЬНЫМИ
   REPLACE LINK_PREPOSITIONS

   // По возможности сразу свернем сочетания прилагательного и существительного в случаях,
   // когда нет неоднозначности
   REPLACE RusSA_Instant_AdjNoun

   // СВЕРТКИ - ПРЕДЛОГИ С СУЩЕСТВИТЕЛЬНЫМИ
   REPLACE LINK_PREPOSITIONS


   // Цепочки существительных
   REPLACE RusSA_Instant_Noun


   // В некоторых случаях можно свернуть даже конструкции с инфинитивом.
   REPLACE RusSA_Instant_Infinitive


   // Привязка дополнения для деепричастий, инфинитивов, глаголов
   REPLACE RusSA_Instant_Object


   iterate needs1 3 /*** ITER_A ***/
    {
     // ПРЕОБРАЗОВАНИЕ "С УТРА ДО ВЕЧЕРА"
     PASS AA_RULES_TIME0

     // СВЕРТКИ - ПРЕДЛОГИ С СУЩЕСТВИТЕЛЬНЫМИ
     REPLACE LINK_PREPOSITIONS

     // НИ [С КЕМ]
     REPLACE LINK_NI
   
     // ************** НАРЕЧИЯ *******************

     if count(НАРЕЧИЕ)>0 
      then
       {
        REPLACE LINK_ADVERB_BUT
		
        // НАРЕЧИЕ + (ОБСТОЯТЕЛЬСТВО)
        //e.g. РЯДОМ С КОШКОЙ
        // 
        // NB: сложные случаи, типа
        //
        // РЯДОМ С БОЛЬШОЙ БЕЛОЙ КОШКОЙ
        //       
        // будут свернуты после одной или более полных итераций A.
        //
        REPLACE AA_LINK_5

        // НАРЕЧИЕ (ИЛИ) НАРЕЧИЕ (ИЛИ) НАРЕЧИЕ
        if match OrAdverb3
         then
          { 
           REPLACE OrAdverb3
           REPLACE OrAdverb3_2
           REPLACE OrAdverb3_3
          }      
   
        // НАРЕЧИЕ (И) НАРЕЧИЕ  
        if match AA_LINK_10
         then
          { 
           REPLACE AA_LINK_10
           REPLACE AA_LINK_10_2
           REPLACE AA_LINK_10_3
          }      
  
        // НАРЕЧИЕ (ИЛИ) НАРЕЧИЕ  
        if match AA_LINK_11
         then
          { 
           REPLACE AA_LINK_11
           REPLACE AA_LINK_11_2
           REPLACE AA_LINK_11_3
          }

        // ни быстро, ни медлено
        REPLACE LINK_ADVERB_NI_NI

        // то быстро, то медленно 
        REPLACE LINK_ADVERB_TO_TO

        // БОЛЕЕ ЯРКИЙ
        // МЕНЕЕ ЯРКИЙ
        REPLACE AA_LINK_25
     
        // НАРЕЧИЕ + ПРИЛАГАТЕЛЬНОЕ
        // НАРЕЧИЕ + ДЕЕПРИЧАСТИЕ   
        PASS LINK_ADVERB_2_ADJ
       } // end if count(НАРЕЧИЕ)>1

     REPLACE LINK_MULTIWORD_PARTICIPLE
 
     iterate 3 /****** ITER_K *****/
      {
       // Зацикливание на диапазоне от разбора прилагательных до присоединения подлежащего к сказуемому
       // необходимо для корректного распознавания конструкций типа "КОШКА, КОТОРАЯ СПИТ НА ТЕПЛОМ ПОЛУ",
       // в которых есть связь между глаголом и дополнением
 
 
       // **************** ПРИЛАГАТЕЛЬНЫЕ ************************

//       iterate 3 /*** ITER_M ***/
//        {

           if count(ПРИЛАГАТЕЛЬНОЕ)>1
            then
             {
              // ПРИЛАГАТЕЛЬНОЕ (ИЛИ) ПРИЛАГАТЕЛЬНОЕ (ИЛИ) ПРИЛАГАТЕЛЬНОЕ
              if match OrAdj3
               then
                { 
                 PASS OrAdj3
                 PASS OrAdj3_2
                 PASS OrAdj3_3
                }      
    
              // ПРИЛАГАТЕЛЬНОЕ (И) ПРИЛАГАТЕЛЬНОЕ   
              if match AA_LINK_106
               then
                { 
                 PASS AA_LINK_106
                 PASS AA_LINK_106_2
                 PASS AA_LINK_106_3
                }      
 
              // ПРИЛАГАТЕЛЬНОЕ (ИЛИ) ПРИЛАГАТЕЛЬНОЕ   
              if match AA_LINK_1062
               then
                { 
                 PASS AA_LINK_1062
                 PASS AA_LINK_1062_2
                 PASS AA_LINK_1062_3
                }  

              // ни быстрый, ни медленный
              PASS LINK_ADJ_NI_NI

              // то быстрый, то медленный
              PASS LINK_ADJ_TO_TO

              // белый, но грязный
              PASS LINK_ADJ_BUT

              // сначала белый, потом грязный 
              PASS LINK_ADJ_NEXT_1
              PASS LINK_ADJ_NEXT_2
             }
             

         if or( count(ЧИСЛИТЕЛЬНОЕ)>0 , count(num_word:NUMBER_{})>0 )
          then
           // ПРИЛАГАТЕЛЬНОЕ+ЧИСЛИТЕЛЬНОЕ (ЦЕЛЫХ ДВЕ КОШКИ)  
           PASS LINK_ADJ_2_NUMBER

  
         // ПРИЛАГАТЕЛЬНОЕ   +  ( СУЩ или МЕСТОИМЕНИЕ или МЕСТОИМ_СУЩ )
         PASS LINK_ADJ_2_NOUN

         if count(ПРИЛАГАТЕЛЬНОЕ)>1
          then
           // ПРИЛАГАТЕЛЬНОЕ + ПРИЛАГАТЕЛЬНОЕ
           // в конструкции "а другая синяя"
           PASS LINK_ADJ_2_ADJ


         // ПРИЧАСТИЕ+ДОПОЛНЕНИЕ
         // дополнений может быть несколько, типа
         // "идущий по ковру в туалет"
         PASS LINK_PARTICIPLE_PLUS_OBJECT

         // ПРИЧАСТНЫЙ ОБОРОТ
         PASS AA_PRICH // REPLACE
 
         // Для фразы "С ЖУТКОЙ РОЖЕЙ" необходимо повторить попытку
         // свертки предлога с существительным после прикрепления
         // прилагательного.
         REPLACE LINK_PREPOSITIONS

         // СУЩ + СУЩ                            
         PASS LINK_CONOUN      // ЧЕЛОВЕК-ПАУК               
         PASS LINK_NOUN_2_NOUN // "ПАРТИЯ ЛЮБИТЕЛЕЙ ПИВА"

         // ЯРЧЕ, ЧЕМ СОЛНЦЕ
         // ЯРЧЕ СОЛНЦА 
         PASS LINK_COMPARATIVE_ADJ_2_NOUN

//         fresh_up
//        } /*** ITER_M ***/


       if count(ДЕЕПРИЧАСТИЕ)>0
        then 
         {
          if count(НАРЕЧИЕ)>0
           then
            PASS LINK_COMPARATIVE_ADV_2_DEEPR

          // К этому моменту свернуты конструкции с наречиями, к примеру "быстро и резко начав играть",
          // конструкции из прилагательных "играя с белой и пушистой мышкой", а также с
          // особой конструкцией из существительных "играя с партией любителей пива"
          //
          // ДЕЕПРИЧАСТИЕ + (ОБСТОЯТЕЛЬСТВО)             "ИГРАЯ С КОШКОЙ"
          // Так как может быть целая цепочка дополнений:
          // "играя в углу с кошкой"
          // то делаем цикл итераций
          PASS LINK_DEEPR_PLUS_OBJECT
         }

 
       // *** СУЩЕСТВИТЕЛЬНЫЕ ***

       // СУЩ  (ИЛИ) СУЩ (ИЛИ) СУЩ
       if match OrNoun3
        then
         { 
          REPLACE OrNoun3
          REPLACE OrNoun3_2
          REPLACE OrNoun3_3
         }      
   

       // СУЩ  (И)  СУЩ
       if match AA_LINK_110
        then
         { 
          REPLACE AA_LINK_110
          REPLACE AA_LINK_110_2
          REPLACE AA_LINK_110_3
         }      

       // СУЩ  (ИЛИ)  СУЩ
       if match AA_LINK_111
        then
         { 
          REPLACE AA_LINK_111
          REPLACE AA_LINK_111_2
          REPLACE AA_LINK_111_3
         }      

       // ни кошка, ни собака
       REPLACE LINK_NOUN_NI_NI  // (*)

       // то кошка, то собака
       REPLACE LINK_NOUN_TO_TO  // (*)

       // кошка, но не собака
       REPLACE LINK_NOUN_BUT // (*)

       // сначала кошка, затем собака
       PASS LINK_NOUN_NEXT_1
       PASS LINK_NOUN_NEXT_2

       if count(МЕСТОИМЕНИЕ)>1
        then
         {  
         // НИ Я, НИ ТЫ 
         REPLACE LINK_PRONOUN_NI_NI

         // ТО Я, ТО ТЫ 
         REPLACE LINK_PRONOUN_TO_TO

         // Я, но не ты
         REPLACE LINK_PRONOUN_BUT  // (*)

         // сначала я, затем ты
         REPLACE LINK_PRONOUN_NEXT_1 // (*)
         REPLACE LINK_PRONOUN_NEXT_2 // (*)
        }

       if or(count(ЧИСЛИТЕЛЬНОЕ)>0, count(num_word:NUMBER_{})>0)
        then
         {
          // ни два, ни три
          REPLACE LINK_NUMBER_NI_NI

          // то два, то три
          REPLACE LINK_NUMBER_TO_TO

          // один, но не два
          REPLACE LINK_NUMBER_BUT

          // сначала один, затем два
          REPLACE LINK_NUMBER_NEXT_1
          REPLACE LINK_NUMBER_NEXT_2
         }  

       // После свертки логической связки можно попытаться свернуть предлог:
       // ДЛЯ КОШКИ И СОБАКИ
       REPLACE LINK_PREPOSITIONS
   
       if or(count(ЧИСЛИТЕЛЬНОЕ)>0, count(num_word:NUMBER_{})>0)
        then 
         {
          // цепочка числительных "сто двадцать шесть"
          REPLACE LINK_NUMBER_PLUS_NUMBER

          // ЧИСЛИТЕЛЬНОЕ + СУЩЕСТВИТЕЛЬНОЕ
          REPLACE LINK_NUMBER_PLUS_NOUN

          // один из нас
          REPLACE LINK_ONE_OF
         }


       // *************** ИНФИНИТИВ *********************

       if count(ИНФИНИТИВ)>0
        then
         {
          // Сначала прикрепляем дополнение
          // ИНФИНИТИВ  + СУЩ (не им.п.)
          //
          // дополнений может быть несколько:
          // "идти по ковру в туалет"
          PASS LINK_INF_PLUS_OBJECT

          // Особая связь с подлежащим:
          // Мне бы поесть
          // Котику бы поспать
          PASS LINK_INF_PLUS_SUBJECT

          if count(ИНФИНИТИВ)>2
           then
            { 
             // ИНФИНИТИВ (ИЛИ) ИНФИНИТИВ (ИЛИ) ИНФИНИТИВ
             if match OrInf3
              then
               { 
                REPLACE OrInf3
                REPLACE OrInf3_2
                REPLACE OrInf3_3
               }      
            } // count(ИНФИНИТИВ)>2
    
          if count(ИНФИНИТИВ)>1
           then
            { 
             // ИНФИНИТИВ (И)  ИНФИНИТИВ
             if match AA_LINK_130
              then
               { 
                REPLACE AA_LINK_130
                REPLACE AA_LINK_130_2
                REPLACE AA_LINK_130_3
               }      

             // ИНФИНИТИВ   (ИЛИ)  ИНФИНИТИВ
             if match AA_LINK_131
              then
               { 
                REPLACE AA_LINK_131
                REPLACE AA_LINK_131_2
                REPLACE AA_LINK_131_3
               }

             // ни спать, ни бодрствовать
             REPLACE LINK_INF_NI_NI

             // то спать, то бодрствовать
             REPLACE LINK_INF_TO_TO

             // спать, но не храпеть
             REPLACE LINK_INF_BUT // (*)

             // сначала спать, затем есть 
             PASS LINK_INF_NEXT_1
             PASS LINK_INF_NEXT_2
            } // count(ИНФИНИТИВ)>1

          PASS LINK_COMPARATIVE_ADV_2_INF
         } // count(ИНФИНИТИВ)>0

       // **************** КОНЕЦ ИНФИНИТИВОВ *****************

       PASS LINK_NOUN_2_INF // "ОН ОБЛАДАЕТ СПОСОБНОСТЬЮ ЛЕТАТЬ"
  
       PASS AA_LINK_70

       PASS LINK_ADJ_PLUS_INF // должен петь, способен летать, намерен купить
   
       // ***************** ДЕЕПРИЧАСТИЯ ********************
 
       if count(ДЕЕПРИЧАСТИЕ)>0
        then 
         { 
          // ДЕЕПРИЧАСТИЕ + (ОБСТОЯТЕЛЬСТВО)             "ИГРАЯ С (КОШКОЙ И СОБАКОЙ)"
          // может быть целая цепочка дополнений:
          // "играя в углу с кошкой"
          PASS LINK_DEEPR_PLUS_OBJECT

          if count(ИНФИНИТИВ)>0
           then
            // ДЕЕПРИЧАСТИЕ + ИНФИНИТИВ
            PASS LINK_DEEPR_PLUS_INF
   
          if count(ДЕЕПРИЧАСТИЕ)>2
           then 
            {
             // ДЕЕПРИЧАСТИЕ (ИЛИ) ДЕЕПРИЧАСТИЕ (ИЛИ) ДЕЕПРИЧАСТИЕ
             if match OrDeepr3
              then
               { 
                REPLACE OrDeepr3
                REPLACE OrDeepr3_2
                REPLACE OrDeepr3_3
               }      
            }

          if count(ДЕЕПРИЧАСТИЕ)>1
           then 
            {
             // ДЕЕПРИЧАСТИЕ (И) ДЕЕПРИЧАСТИЕ  
             if match AA_LINK_75
              then
               { 
                REPLACE AA_LINK_75
                REPLACE AA_LINK_75_2
                REPLACE AA_LINK_75_3
               }      

             // ДЕЕПРИЧАСТИЕ (ИЛИ) ДЕЕПРИЧАСТИЕ  
             if match AA_LINK_76
              then
               { 
                REPLACE AA_LINK_76
                REPLACE AA_LINK_76_2
                REPLACE AA_LINK_76_3
               }      
             }
   
          // ДЕЕПРИЧАСТНЫЙ ОБОРОТ                        "УШЛИ, ПОИГРАВ С КОШКОЙ" 
          REPLACE AA_DEEPR

          if count(ДЕЕПРИЧАСТИЕ)>1
           then 
            {
             // ни летая, ни ползая
             REPLACE LINK_DEEPR_NI_NI

             // то летая, то ползая
             REPLACE LINK_DEEPR_TO_TO

             // летая, но не падая
             REPLACE LINK_DEEPR_BUT // (*)

             // сначала летая, затем падая
             REPLACE LINK_DEEPR_NEXT_1 // (*)
             REPLACE LINK_DEEPR_NEXT_2 // (*)
            }

          PASS LINK_COMPARATIVE_ADV_2_DEEPR
         }

       // ************* КОНЕЦ БЛОКА РАБОТЫ С ДЕЕПРИЧАСТИЯМИ


       if count(ИНФИНИТИВ)>0
        then  
         // ПРИЧАСТИЕ+ИНФИНИТИВ
         PASS LINK_PARTICIPLE_PLUS_INF


       // ГЛАГОЛ + СУЩ (не им.п.)
       // дополнений может быть несколько
       // "идет по ковру в туалет"
       REPLACE LINK_VERB_PLUS_OBJECT // (*)

       if count(ИНФИНИТИВ)>0
        then  
         // ГЛАГОЛ + ИНФИНИТИВ
         PASS LINK_VERB_PLUS_INF

       iterate 3 /*** ITER_L ***/
        {
         // *************
         // Перед связыванием с субъектом, свернем логические союзы для глагола: КОШКА >>СПИТ И ВИДИТ<<
         // *************

         if count(ГЛАГОЛ)>2
          then 
           {
            // ГЛАГОЛ (ИЛИ) ГЛАГОЛ (ИЛИ) ГЛАГОЛ
            if match OrVerb3
             then
              {
               REPLACE OrVerb3
               REPLACE OrVerb3_2
               REPLACE OrVerb3_3
              }
           }
           
 
         if count(ГЛАГОЛ)>1
          then 
           {
            // ГЛАГОЛ (И) ГЛАГОЛ
            if match AA_LINK_160
             then
              { 
               REPLACE AA_LINK_160
               REPLACE AA_LINK_160_2
               REPLACE AA_LINK_160_3
              }
           }  

         // отдельно связки безличного глагола и личной формы типа
         // "котику надо спать, поэтому он уснул" 
         PASS LINK_VERB_AND

         if count(ГЛАГОЛ)>1
          then 
           {
            // ГЛАГОЛ (ИЛИ) ГЛАГОЛ
            if match AA_LINK_161
             then
              { 
               REPLACE AA_LINK_161
               REPLACE AA_LINK_161_2
               REPLACE AA_LINK_161_3
              }  

            // ни спит, ни бодрствует
            REPLACE LINK_VERB_NI_NI

            // то спит, то бодрствует
            REPLACE LINK_VERB_TO_TO

            // спит, но не храпит
            REPLACE LINK_VERB_BUT // (*)

            // сначала спит, затем ест  
            PASS LINK_VERB_NEXT_1
            PASS LINK_VERB_NEXT_2
           }

         // бегает быстрее, чем кошка
         PASS LINK_COMPARATIVE_ADV_2_VERB

         // псевдо-причастные обороты "КОШКА, КОТОРАЯ ПОЕТ"
         PASS LINK_NOUN_WHICH
 
    
         // ***** Связываем Подлежащее и Сказуемое ********
 
         // НЕКОТОРЫЕ СЛОЖНЫЕ КОНСТРУКЦИИ
         PASS AA_LINK_120

         // СУЩ (им.п.) + ГЛАГОЛ
         PASS LINK_SUBJECT_VERB

         // После связывания подлежащего со сказуемым оказывается возможным связать сказуемое
         // с депричастным оборотом
          
         if count(ДЕЕПРИЧАСТИЕ)>0
          then   
           // ДЕЕПРИЧАСТНЫЙ ОБОРОТ                        "УШЛИ, ПОИГРАВ С КОШКОЙ" 
           REPLACE AA_DEEPR

 
         // Свертка конструкций A, то есть B
         REPLACE LINK_THAT_IS_1
         PASS LINK_THAT_IS_2

         // Надо повторить цикл, так как в некоторых случаях только после связывания деепричастного оборота оказывается
         // возможным свернуть логические конструкции. А связать деепричастный оборот обычно невозможно без связывания
         // подлежащего со сказуемым...
         fresh_up
        } /*** ITER_L ***/

       fresh_up
      } /*** ITER_K ***/


     // группа должна отработать до ГЛАГОЛ + ГЛАГОЛ
     // КОГДА ...., ТОГДА ...
     PASS AA_WHEN_THEN

  
     // Сворачиваем далекую логическую связь двух групп подлежащее+сказуемое
 
     if count(ГЛАГОЛ)>2
      then   
       {
        // ГЛАГОЛ (ИЛИ) ГЛАГОЛ (ИЛИ) ГЛАГОЛ
        if match OrVerb3
         then
          { 
           REPLACE OrVerb3
           REPLACE OrVerb3_2
           REPLACE OrVerb3_3
          }      
       } 
  
     if count(ГЛАГОЛ)>1
      then   
       {
        // ГЛАГОЛ (И) ГЛАГОЛ
        if match AA_LINK_160
         then
          { 
           REPLACE AA_LINK_160
           REPLACE AA_LINK_160_2 
           REPLACE AA_LINK_160_3
          }      

        // ГЛАГОЛ (ИЛИ) ГЛАГОЛ
        if match AA_LINK_161
         then
          { 
           REPLACE AA_LINK_161
           REPLACE AA_LINK_161_2
           REPLACE AA_LINK_161_3
          }       
       }

     fresh_up
    } /*** ITER_A **/

   // Различные формы вопросов
   REPLACE AA_RULES_QUEST

   // КОШКА ДУМАЕТ, ЧТО ОНА СИЛЬНЕЕ СОБАКИ.
   REPLACE AA_RULES_THAT

   // КОШКА МНОГО ЕСТ, ПОЭТОМУ ОНА МНОГО СПИТ
   REPLACE AA_RULES_BECAUSE

   // Кошка спит вместо того, чтобы покушать 
   REPLACE AA_RULES_INSTEAD_OF

   // Кошка спит для того, чтобы отдыхать.
   REPLACE AA_RULES_IN_ORDER_TO
   
   // Кошка поест, прежде чем пойдет спать 
   REPLACE AA_RULES_BEFORE

   // Кошка поест, после того как поймает мышку
   REPLACE AA_RULES_AFTER

   // ЕСЛИ СВИНЬЯ ..., ТО ОНА ...
   REPLACE AA_RULES_CONDITION
 
   // СНАЧАЛА КОШКА СПИТ, А ЗАТЕМ ...
//   REPLACE AA_RULES_SEQUENCE

   // Я знаю, что любит кошка
   REPLACE RusSA_SubClause


   drop_parents 

   // Чистим лишние вариаторы
   iter_end
  }
 } // end of [MainIterator]

 #pragma floating on
}

