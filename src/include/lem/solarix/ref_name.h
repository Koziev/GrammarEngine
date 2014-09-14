// -----------------------------------------------------------------------------
// File REF_NAME.H
//
// (c) Koziev Elijah
//
// Content:
// Обслуживание ссылочных имен - маркировки точек в опорных контекстах.
// -----------------------------------------------------------------------------
//
// CD->31.05.1997
// LC->13.03.2009
// --------------

#ifndef SOL_REFNAME__H
#define SOL_REFNAME__H
#pragma once

 #include <lem/cstring.h>

 namespace lem
 {
  namespace Iridium {
                     class Macro_Parser;
                     class BethToken;
                    } 
  struct Sol_IO;
 }

 namespace Solarix
 {
 /***************************************************************************

                                  REMARKS

   В результатной части продукционных правил-beth (то есть в акторах), а
   иногда и в кондикторах приходится ссылаться на элементы входного опорного
   контекста. В некоторых случаях удобно указывать индекс опорной точки, а
   иногда проще (или нельзя иначе) указывать символическое имя маркированного
   фрагмента одного из деревьев в опорном контексте.

   После некоторых раздумий я решил ограничить символические имена одним
   латинским символом. Это не столь уж неприятное ограничение позволяет
   хранить ссылочные имена как поле int. Кроме того, одно поле int может
   хранить либо индекс, либо ссылочное имя без необходимости вводить
   дополнительное поле для типа. Действительно, достаточно заметить, что
   появление на входе Системы предложения с более чем 255 словами нереально,
   поэтому диапазон 0...255 отдан индексам, а 256 и далее - ссылочным именам.
   Для удобства работы вводится процедуры для УПАКОВКИ ссылочного имени в
   int поле и для обратного преобразования.

   After the lenghty consideration I decided to limit the reference names by
   the one character size. This limitation not being too bothering let me
   store any reference name as <int> field. Then, one <int> is able to
   contain either the index, or the reference name, and the type field is
   not necessary. As a matter of fact it is not a big secret that sentence
   with more than 255 words can never be entered to the System, so the
   range (0...255) of integer values represents the indeces as they are, and
   the range (255...) can represents any reference name. The handling of
   reference names is greately simplified by two routines. One of them
   PACKS the reference to integer, another UNPACK it back.
 ***************************************************************************/

 inline int sol_ref_name_to_index( int refname ) { return refname; }
 inline int sol_index_to_ref_name( int index )   { return index; }
 inline bool sol_is_index( int i )   { return i<L'A';  }
 inline bool sol_is_ref_name( int i ) { return i>=L'A'; }

 extern bool sol_is_it_ref_name( const lem::UCString &s );

 extern void sol_check_ref_name(
                                const lem::Sol_IO &io,
                                lem::Iridium::Macro_Parser& txtfile,
                                const lem::Iridium::BethToken& s
                               );

 extern int sol_check_index(
                            const lem::Sol_IO &io,
                            lem::Iridium::Macro_Parser& txtfile,
                            const lem::Iridium::BethToken& s
                           );

 extern int sol_str_to_ref_name( const lem::UCString &s );
 extern const lem::UCString sol_ref_name_to_str( int refname );

 } // namespace 'Solarix'

#endif
