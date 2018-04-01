// -----------------------------------------------------------------------------
// File LEXEM.CPP
//
// (c) by Koziev Elijah
//
// Content:
// Класс Lexem - внутреннее представление ЛЕКСЕМЫ. Основное отличие лексемы
// от простого слова: слово - это просто конгломерат неких символов
// (не обязательно букв!), а лексема - это последовательность распознанных букв,
// с полной информацией об их местоположении в Алфавите Графической Грамматики.
// DO PAY ATTENTION: экономии памяти ради мы совмещаем хранение ЛЕКСЕМ и
// СПЕЦИАЛЬНЫХ КОМАНД для СубАвтомата Формообразования, так что в некоторых
// случаях лексемы могут содержать специальные символы, явно не
// зарегистрированные в Алфавите.
// -----------------------------------------------------------------------------
//
// CD->17.10.1995
// LC->06.05.2011
// --------------

#include <algorithm>

#include <lem/integer.h>
#include <lem/oformatter.h>
#include <lem/sol_io.h>

#include <lem/solarix/gg_autom.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/Symbols.h>
#include <lem/solarix/Symbol.h>
#include <lem/solarix/lexem.h>

#if LEM_DEBUGGING==1
 #include <lem/console_streams.h>
#endif

using namespace boost;
using namespace std;
using namespace lem;
using namespace Solarix;

wchar_t Lexem::DelimiterChar=L' ';
const wchar_t * Lexem::DelimiterStr=L" ";


Lexem::Lexem( const UCStringSet &list )
{
 for( lem::Container::size_type i=0; i<list.size(); i++ )
  Add( list[i] );

 return;
}


Lexem::Lexem( lem::Stream & bin )
{ LoadBin(bin); }

Lexem::Lexem( const wchar_t *str )
: UCString(str)
{}

Lexem::Lexem( const UCString &x ) : UCString(x)
{}



#if defined SOL_LOADTXT
/*******************************************************************************
               ***  ЧАСТЬ КОДА СУБАВТОМАТА ФОРМООБРАЗОВАНИЯ ***

 Преобразуем линейное описание лексемы в наше внутреннее представление.
 С помощью комбинаций специальных символов может быть определено положение
 ударения, задана безударность фонем, введено требования точного соответстви
 большие/малые буквы, а также описаны некоторые команды для Автомата Склонений.

 Если управляющий параметр mode==1 (случай по умолчанию), то подразумевается,
 что команды для Автомата Склонений отключены и должны вызвать печать диагностики
 ошибки. Если же mode==2, то требуется анализ и этих команд.

 Обращаю особое внимание, что any modifications в системе спецкоманд для DSA
 должны сопровождаться модификацией как нижеследующего метода, так и кода
 класса SG_DeclensionForm.
*********************************************************************************/

void Lexem::Translate( const GraphGram &gram, int mode )
{
 lem::MCollect<int> dummy;
 Translate( gram, mode, dummy );
 return;
}

void Lexem::Translate( const GraphGram &gram, int mode, const lem::MCollect<int>& id_alphabet )
{
 wchar_t buffer[LEM_CSTRING_LEN1]; // Временный буфер для размещения результата.
 memset( buffer, 0, sizeof(buffer) );
 int i_res=0;
 TranslateThis( i_res, str, buffer, gram, mode, id_alphabet );
 lem_strcpy( str, buffer );
 calc_hash();
 return;
}
#endif

#if defined SOL_LOADTXT
void Lexem::TranslateThis(
                          int &i_res,
                          const wchar_t src[],
                          wchar_t buffer[],
                          const GraphGram &gram,
                          int mode,
                          const lem::MCollect<int>& id_alphabet
                         ) const
{
 const int l=lem::lem_strlen(src);
 int i_src=0;

 bool precise_form=false;
 int8_t sflag=ANY_STATE;

 while(i_src<l)
  {
   wchar_t ch = src[i_src++];

   switch(ch)
    {
     case B_PRECISE_METACHAR:
      {
       // Для последующего символа следует точно запомнить им
       // формы, то есть есть различие, к примеру, для больших и малых букв.
       precise_form = true;
       break;
      }

     case B_STRESS_METACHAR:
      {
       // Ударный гласный звук.
       sflag = STRESSED_FLAG;
       break;
      }

     case B_UNSTRESS_METACHAR:
      {
       // Безударный гласный.
       sflag = UNSTRESSED_FLAG;
       break;
      }

     case B_COMMAND_METACHAR:
      {
       if( mode==2 )
        {
         // Только в этом режиме могут транслироваться команды для Автомата
         // склонений.
         buffer[i_res++]=ch;

         switch( ch=src[i_src++] )
          {
           case B_COMMAND_METACHAR:
            buffer[i_res++]=ch; // %% --> %
            break;
            

           case B_REDUCE_METACHAR:        // %-N
            buffer[i_res++]=ch;           // символ команды '-'
            buffer[i_res++]=str[i_src++]; // аргумент-цифра N
            break;

           case B_DOUBLE_METACHAR:        // %D
            buffer[i_res++]=ch;           // символ команды 'D'
            break;

           case B_STRESS_METACHAR:      // %+RRRR...R%
            {                           // %+RRR         - до конца строки
             buffer[i_res++]=ch;        // символ '+'

             if( src[i_src]==B_GROUP_BEGIN_METACHAR )
              {
               buffer[i_res++]=src[i_src++]; // символ '{'
               TranslateSubString(
                                  src,
                                  i_src,
                                  buffer,
                                  i_res,
                                  gram,
                                  mode,
                                  id_alphabet
                                 );
               buffer[i_res++]=src[i_src++]; // Символ '}'
              }
             else
              {
               ch = src[i_src++];

               do
                {
                 TranslateChar(
                               gram,
                               ch,
                               src,
                               buffer[i_res],
                               id_alphabet
                              );
                 i_res++;
                 ch=src[i_src++];
                }
               while( ch && ch!=B_COMMAND_METACHAR );
              }

             break;
            }

           case B_CUT_METACHAR:           // %cN
            buffer[i_res++]=ch;           // символ команды 'c'
            buffer[i_res++]=src[i_src++]; // аргумент-цифра N
            break;

           case B_PREFIX_INSERT_METACHAR: // %aNR
            {
             buffer[i_res++]=ch;           // символ команды 'a'
             buffer[i_res++]=src[i_src++]; // аргумент-цифра N

             if( src[i_src]==B_GROUP_BEGIN_METACHAR )
              {
               buffer[i_res++]=src[i_src++]; // символ '{'
               TranslateSubString(
                                  src,
                                  i_src,
                                  buffer,
                                  i_res,
                                  gram,
                                  mode,
                                  id_alphabet
                                 );
               buffer[i_res++]=src[i_src++]; // Символ '}'
              }
             else
              {
               TranslateChar(
                             gram,
                             src[i_src++], // аргумент-буква R
                             src,
                             buffer[i_res],
                             id_alphabet
                            );
               i_res++;
              }

             break;
            }

           default:
            {
             gram.GetIO().merr().printf(
                                        "Illegal control char in control sequence for Declenson SubAutomaton:\n"
                                        "[%us]\n"
                                        , src
                                       );

             gram.GetIO().merr().printf( "%H ^", i_src );
             throw E_ParserError();
            }
          }
        }
       else
        {
         buffer[i_res++]=ch;
        }

       break;
      }

     case B_PLAIN_METACHAR:
      {
       ch = src[i_src++];
       // Дальше идет символ, который не следует понимать как метасимвол.
       // Таким образом, можно использовать символы % и другие для
       // лексического наполнения имени лексемы, не опасаясь неожиданного
       // перевода таких символов в специальные действия.
       //
       // Мы не меняем текущие флаги ударности и точной статьи, так что есть
       // возможность употреблять спецсимволы внутри командных групп!
       if( !ch )
        {
         wchar_t b[2];
         b[0] = B_PLAIN_METACHAR;
         b[1] = 0;
         gram.GetIO().merr().printf(
                                    "Incorrect format of form generation template [%us]:"
                                    " must be a char after metachar '%us'.\n"
                                    , src, b
                                   );

         throw E_ParserError();
        }

       TranslateChar(
                     gram,
                     ch,
                     src,
                     buffer[i_res],
                     id_alphabet
                    );
       i_res++;
       break;
      }

     default:
      {
       TranslateChar(
                     gram,
                     ch,
                     src,
                     buffer[i_res],
                     id_alphabet
                    );
       i_res++;
       sflag        = ANY_STATE;
       precise_form = false;
       break;
      }
    }
  }

 return;
}
#endif

#if defined SOL_LOADTXT
void Lexem::TranslateChar(
                          const GraphGram &gram,
                          wchar_t ch,
                          const wchar_t *src,
                          wchar_t &res_char,
                          const lem::MCollect<int>& id_alphabet
                         ) const
{
 // Пробел используется как разделитель однолексем
 if( ch==DelimiterChar )
  {
   res_char = ch;
   return;
  }

 // Отыскиваем символ ch в Алфавите.
 const Word_Coord wc = gram.FindSymbol(ch,id_alphabet);

 if( wc.GetEntry()==UNKNOWN )
  {
/*
#if LEM_DEBUGGING==1
lem::mout->printf( "There are %d alphabets: ", gram.alphabets().size() );
for( lem::Container::size_type i=0; i<gram.alphabets().size(); ++i )
 {
  const GG_Alphabet &a = gram.alphabets()[i];
  lem::mout->printf( "[%d] %us ", a.get_Id(), a.get_Name().c_str() );
 }
lem::mout->eol();

{
lem::mout->printf( "There are %d symbols: ", gram.entries().size() );
for( int i=0; i<gram.entries().size(); ++i )
 {
  gram.entries()[i].PrintName(*mout);
  lem::mout->printf( ' ' );
 }
}

lem::mout->eol();

#endif
*/
   wchar_t dummy[2];
   dummy[0]=ch; dummy[1]=0;
   UFString err = lem::format_str(L"Symbol [%s] with hex code [%x] in lexem [%s] is not defined in Alphabet\n", dummy, int(ch), src );
   throw E_ParserError(err.c_str());
  }

 // Теперь это - не просто некий символ, а БУКВА.

 const GG_Entry &entry = gram.entries()[ wc.GetEntry() ];
 res_char   = entry.GetName();

 return;
}
#endif

#if defined SOL_LOADTXT
/****************************************************************
 Транслируем сложный аргумент метакоманды {RR...R} и добавляем
 соответствующие коды в буфер buffer и наши внутренние вектора
 form и stress. Предполагаем, что i_src указывает сейчас на
 символ после '{' в исходном буфере src. После работы процедуры
 i_src будет указывать на символ '}', закрывающей нашу подстроку.
*****************************************************************/
void Lexem::TranslateSubString(
                               const wchar_t src[],
                               int &i_src,
                               wchar_t buffer[],
                               int &i_res,
                               const GraphGram &gram,
                               int mode,
                               const lem::MCollect<int>& id_alphabet
                              ) const
{
 // Сначала извлечём символы RRR..RRR в скобках { } в отдельный буфер.
 wchar_t rrr[LEM_CSTRING_LEN1];
 memset( rrr, 0, sizeof(rrr) );
 int i_rrr=0;

 while( src[i_src]!=B_GROUP_END_METACHAR )
  {
   if( src[i_src]==0 )
    {
     gram.GetIO().merr().printf(
                                "Illegal control char in control sequence "
                                " for Declenson SubAutomaton:\n[%us]\n"
                                , src
                               );
     gram.GetIO().merr().printf( "%H ^", i_src );
     throw E_ParserError();
    }

   rrr[i_rrr++] = src[i_src++];
  }

 rrr[i_rrr]=0;

 TranslateThis( i_res, rrr, buffer, gram, mode, id_alphabet );
 return;
}
#endif

/*************************************************************************
 Преобразуем лексему в текстовую строку так, что сохраняются специальные
 управляющие признаки, поэтому можно будет по сохраненной строке точно
 восстановить лексему. Этот метод используется, в частности, при
 декомпиляции Словаря, когда нужно восстановить команды СубАвтомата
 Формообразования.
*************************************************************************/
const UCString Lexem::ToString(void) const
{
 wchar_t buffer[LEM_CSTRING_LEN1]; // Временный буфер для размещения результата.

 int ipos=0;
 const int l=length();
 bool plain_char=false;
 for( int i=0; i<l && ipos<LEM_CSTRING_LEN-1; /*...nothing...*/ )
  {
   if( plain_char )
    {
     ToString( &i, &ipos, buffer );
     plain_char=false;
     continue;
    }

   if( str[i]==B_PLAIN_METACHAR )
    {
     // Конструкция типа $x, например $%.
     buffer[ipos++] = str[i++];
     plain_char=true;
     continue;
    }

   if( str[i]==B_COMMAND_METACHAR )
    {
     // Директива %...
     buffer[ipos++] = str[i++]; // Сам символ директивы %
     buffer[ipos++] = str[i++]; // Спецификатор команды.
     // Далее будут идти параметры команды.
     continue;
    }

   // Обычный символ, возможно - с флагами контроля ударности и
   // точности формы.
   ToString( &i, &ipos, buffer );
  }

 buffer[ipos]=0;
 return UCString(buffer);
}

void Lexem::ToString( int *isrc, int *idst, wchar_t *buffer ) const
{
 // Возможно, следует вписать флаг точного задания имени буквоформы.
 buffer[(*idst)++] = str[*isrc];
 (*isrc)++;

 return;
}

/*********************************************************************
 Внутреннее представление лексемы преобразуется в символьную строку,
 не содержащую специальных команд, и пригодную для чтения человеком.
*********************************************************************/
const UCString Lexem::ToWord(void) const
{
 wchar_t buffer[LEM_CSTRING_LEN1]; // Временный буфер для результата.

 const int l=length();
 int ipos=0;
 for( int i=0; i<l; i++ )
  buffer[ipos++] = str[i];//form[i]==wchar_t(ANY_STATE) ? str[i] : form[i];

 buffer[l]=0;
 return UCString(buffer);
}

/***************************************************************************
 Сравниваем флаги ударности. Это вспомогательная процедура, является частью
 inline-метода CompareAll. Я вынес ее в outline, так как она содержит цикл.
****************************************************************************/
/*
bool Lexem::CompareAcsents( const Lexem &l ) const
{
 LEM_LOOP( i, length() )
  {
   if( stress[i]!=(int8_t)ANY_STATE && l.stress[i]!=(int8_t)ANY_STATE )
    if( stress[i] != l.stress[i] )
     return false;

   if( form[i]!=wchar_t(ANY_STATE) && l.form[i]!=wchar_t(ANY_STATE) )
    if( form[i]!=l.form[i] )
     return false;
  }

 return true;
}
*/

/*******************************************************************************
 Сравниваем содержимое лексем, но не требуем полного соответствия - необходимо,
 чтобы совпали начальные части: наша (вся) и аргумента l (часть). То есть,
 длина l может превышать длину нашей лексемы, но наша длина не может превышать
 длину l.
********************************************************************************/
bool Lexem::CompareAll_1( const Lexem &l ) const
{
 const int L=length();

 for( int j=0; j<L; j++ )
  if( str[j]!=l.str[j] )
   return false;

/*
 // Проверим флаги ударности.
 LEM_LOOP( i, L )
  {
   if( stress[i]!=(int8_t)ANY_STATE && l.stress[i]!=(int8_t)ANY_STATE )
    if( stress[i] != l.stress[i] )
     return false;

   if( form[i]!=wchar_t(ANY_STATE) && l.form[i]!=wchar_t(ANY_STATE) )
    if( form[i]!=l.form[i] )
     return false;
  }
*/

 return true;
}

namespace lem
{
 enum lex_store_flags {
                       f_entries_packed=0x80
//                       f_has_stress=1,
//                       f_has_forms=2,
//                       f_forms_equal_entries=4,
//                       f_forms_packed=16
                      };

 void write_packed( Stream &bin, const wchar_t *src, int len )
 {
  bin.write( src, sizeof(wchar_t) );

  for( int i=1; i<len; i++ )
   {
    int8_t delta = int8_t(src[i] - *src);
    bin.write( &delta, 1 );
   }

  return;
 }

 void read_packed( Stream &bin, wchar_t *src, int len )
 {
  bin.read( src, sizeof(wchar_t) );

  for( int i=1; i<len; i++ )
   {
    int8_t delta=0;
    bin.read( &delta, 1 );
    src[i] = int16_t(*src) + int16_t(delta);
   }

  return;
 }
}

void Lexem::SaveBin( Stream &bin ) const
{
 bool entries_packed=true;

 for( int i=1; i<len; i++ )
  {
   int e_delta = str[i] - *str;

   if( e_delta > 127 )
    entries_packed = false;
   else if( e_delta < -127 )
    entries_packed = false;
  }

 // Длину сохраняем вместе с флагами сжатия
 uint8_t flags = ( entries_packed ? f_entries_packed : 0 ) | len;
 bin.write( &flags, sizeof(flags) );

 if( entries_packed )
  write_packed( bin, str, len );
 else
  bin.write( str, sizeof(*str)*len );

 return;
}


void Lexem::LoadBin( Stream &bin )
{
 // Length & flags
 uint8_t flags=0;
 bin.read( &flags, sizeof(flags) );
 len = flags & 0x7f;

// flags &= 0xf0;

 // Chars
 if( (flags & f_entries_packed) == f_entries_packed )
  read_packed( bin, str, len );
 else
  bin.read( str, sizeof(*str)*len );

 // Terminate them because zero is not stored in stream.
 str[len]  = 0;
 calc_hash();

 return;
}


// ************************************************************
// Вернет true, если можно сжимать относительно лексемы base.
// У данной лексемы и у base должна быть общая часть.
//
// Через pack_flags возвращается дополнительная информация об
// упаковке.
// ************************************************************
bool Lexem::Can_Be_Packed( const Lexem &base, lem::uint8_t *pack_flags ) const
{
 int l = std::min( length(), base.length() );
 if( l )
  {
   int common_len=0;
   for( int i=0; i<l; i++ )
    if( str[i] == base.str[i] )
     common_len++;
    else
     break;

   // Общая часть достаточно длинна, чтобы покрыть расходы на хранение
   // дополнительных флагов?  
   if( common_len>3 )
    {
     *pack_flags = common_len;
     return true;
    }
  }

 return false;
}


// ***************************************************************************
// Сохраняем лексему в сжатом виде - как добавку к базовой части
// другой лексемы base. Обе лексемы имеют общую часть длиной pack_flags,
// причем - с самого начала.
//
// Для сохранения аффикса в опять-таки упакованном виде конструируем
// временную лексему.
// ***************************************************************************
void Lexem::SaveBin_Packed(
                           Stream &bin,
                           const Lexem &base,
                           lem::uint8_t pack_flags
                          ) const
{
 Lexem( str+pack_flags ).SaveBin(bin);
 return;
}

void Lexem::LoadBin_Packed(
                           Stream &bin,
                           const Lexem &base,
                           lem::uint8_t pack_flags
                          )
{
 Lexem affix;
 affix.LoadBin(bin);

 // Копируем себе содержимое base
 copy( base.str,    base.str+pack_flags,    str    );

 // добавляем аффикс
 copy( affix.str,    affix.str+affix.len+1,  str+pack_flags );

 calc_hash();
}


void Lexem::Split( UCStringSet &list ) const
{
 const int n = Count_Lexems();

 if( n==1 )
  {
   list.push_back(*this);
   return;
  }

 list.reserve(n);
 for( int i=0; i<length(); ) 
  { 
   UCString part;
   
   while( str[i] && str[i]!=DelimiterChar )
    part += str[i++];

   list.push_back(part);
     
   i++;
  }

 return;
}

void Lexem::Add( const UCString &str )
{
 if( !empty() )
  (*this) += DelimiterChar;

 (*this) += str;
 return;
}

void Lexem::CorrectFormSpaces( UCString &f )
{
 if( f.count(L' ')>1 )
  {
   // Для мультилексем уберем лишние пробелы между составными частями
   UFString us(f.c_str());
   us.subst_all( L" ,", L"," );
   us.subst_all( L" - ", L"-" );
   f = us.c_str();
  } 

 return;
}


// Процедура меняет регистр символов в мультилексеме по шаблону Нью-Йорк - то есть
// каждая лексема начинается с заглавной.
void Solarix::MakeEachLexemAa( lem::UCString &s )
{
 s.to_Aa();
 const int l = s.length();
 for( int i=1; i<l-1; ++i )
  {
   const wchar_t c = s[i];
   if( c==Lexem::DelimiterChar || lem::is_udelim(c) )
    s.set( i+1, lem::to_uupper(s[i+1]) );
  }

 s.calc_hash();

 return;
}

void Solarix::MakeEachLexemAa( lem::UFString &s )
{
 s.to_Aa();
 const int l = s.length();
 for( int i=1; i<l-1; ++i )
  {
   const wchar_t c = s[i];
   if( c==Lexem::DelimiterChar || c==L'-' )
    s.set( i+1, lem::to_uupper(s[i+1]) );
  }

 return;
}

