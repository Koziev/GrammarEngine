// -----------------------------------------------------------------------------
// File IR_MACRO_HEAD.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// Класс IR_Macro_Head - хранение заголовка макроса: имя и формальные аргументы
// в круглых скобках.
// -----------------------------------------------------------------------------
//
// CD->30.07.1997
// LC->09.03.2010
// --------------

#include <lem/conversions.h>
#include <lem/ir_parser.h>
#include <lem/macro_parser.h>

using namespace lem;
using namespace lem::Iridium;


IR_Formal_Arg::IR_Formal_Arg(void)
{}

IR_Formal_Arg::IR_Formal_Arg( const UCString& x )
:UCString(x)
{}

IR_Formal_Arg::IR_Formal_Arg( const IR_Formal_Arg &x )
:UCString(x),def(x.def)
{}

IR_Formal_Arg::IR_Formal_Arg( const UCString& x, const lem::Collect<UFString> &Def )
:UCString(x), def(Def)
{}

void IR_Formal_Arg::operator=( const IR_Formal_Arg &x )
{  
 UCString::operator=(x);
 def=x.def;
 return;
}



// -------------------------------

IR_Macro_Head::IR_Macro_Head(void)
{}

IR_Macro_Head::IR_Macro_Head( Sol_IO &io, UTextParser &txtfile )
{
 LoadTxt(io,txtfile);
 return;
}

IR_Macro_Head::IR_Macro_Head( const IR_Macro_Head &h )
:name(h.name),arg(h.arg)
{}


void IR_Macro_Head::operator=( const IR_Macro_Head &h )
{ Init(h); }

void IR_Macro_Head::operator=( const UCString &Name )
{ name=Name; }


void IR_Macro_Head::Init( const IR_Macro_Head &h )
{
 name = h.name;
 arg  = h.arg;
}

/*******************************************************************
 Загружаем голову макроса из текстового файла. Считывание при этом
 не сопровождается какими-либо макроподстановками, то есть читаемые
 токены запоминаются "as is".
********************************************************************/
void IR_Macro_Head::LoadTxt( Sol_IO &io, UTextParser &txtfile )
{
 // Имя макроса - совершенно любая лексема, включая разнообразные
 // многосимвольные разделители, распознаваемые классом UTextSource<LEM_CSTRING_LEN>.
 const UToken n = txtfile.read();
 name=n.string();

 // Станет true после загрузки описания первого аргумента с default value,
 // так что можем контролировать обязательное наличие defaults для
 // остальных аргументов.
 bool first_def=false;

 // Пытаемся загрузить список аргументов в (...)
 const SourceState back = txtfile.tellp();
 if( txtfile.read() == Macro_Parser::t_OroundParen )
  while( !txtfile.eof() )
   {
    UToken Arg = txtfile.read();

    if( Arg == Macro_Parser::t_CroundParen )
     break;

    if( Arg==Macro_Parser::t_Backslash || Arg.eol() )
     continue;

    if( !arg.empty() )
     {
      txtfile.seekp(Arg.GetBegin());
      txtfile.read_it( Macro_Parser::t_Comma ); // Разделитель аргументов.
      Arg = txtfile.read();

      while( Arg==Macro_Parser::t_Backslash || Arg.eol() )
       Arg = txtfile.read();
     }

    if( !is_name( Arg.string().c_str() ) )
     {
      // Имя формального аргумента должно подчиняться правилам для имен.
      Print_Error( io, Arg, txtfile );
      io.merr().printf(
                       "Incorrect formal argument name [%vfE%us%vn] in macro [%vfE%us%vn]\n"
                       , Arg.string().c_str(), name.c_str()
                      );
      throw E_ParserError();
     }

    lem::Collect<UFString> def;
    // Конструкция arg_name=default задает значение аргумента по умолчанию.
    UToken t = txtfile.read();
    lem::UFString fstr;
    if( t==Macro_Parser::t_Equal )
     {
      txtfile.read(fstr);
      def.push_back(fstr);

      if( def.front()==Macro_Parser::t_OroundParen.c_str() )
       {
        def.clear(); 
        int n_open=1;

        while( !txtfile.eof() )
         {
          UFString tt;
          txtfile.read(tt);
          if( tt==Macro_Parser::t_CroundParen.c_str() )
           {
            n_open--;
            if( !n_open )
             break; 
           }
          else if( tt==Macro_Parser::t_OroundParen.c_str() )
           {
            n_open++;
           } 
          else if( !tt.empty() )
           def.push_back(tt);
         }  
       }

      first_def=true;
     }
    else
     {
      if( first_def )
       {
        Print_Error( io, Arg, txtfile );
        io.merr().printf(
                         "Formal argument [%vfE%us%vn] in macro [%vfE%us%vn] must "
                         "have a default value\n"
                         , Arg.string().c_str(), name.c_str()
                        );
        throw E_ParserError();
       }

      txtfile.seekp( t.GetBegin() );
     }

    arg.push_back( IR_Formal_Arg( Arg.string(), def ) );
   }
 else
  txtfile.seekp(back);

 return;
}

/****************************************************************************
 Проверяем, нужно ли применять макроподстановку к последовательности
 токенов, начало которой (от 1 и более элементов) хранится в списке list.
 Если присутствующих в list токенов не хватит, то подгрузим необходимое
 число из исходного текстового файла txtfile посредством вызовов ::get_next.
 Через список 'subst' возвращаем описания конкретизаций формальных аргументов
 подставляемого макроса. Через параметр n_to_reduce возвращаем число
 элементов в list, которое необходимо удалить и подставить вместо них тело
 макроса с заменой формальных аргументов на найденные конкретизации.

 В список table добавляются переменные, то есть особым образом
 преобразованные конкретизации аргументов вызова макроса.
****************************************************************************/
bool IR_Macro_Head::DoesMatch(
                              Sol_IO &io,
                              Collect<UFString> &list,
                              int ifirst,
                              UTextParser &txtfile,
                              Collect<IR_Macro_Subst> &subst,
                              int *n_to_reduce,
                              IR_Var_Table *table
                             ) const
{
 if( list[ifirst] != name.c_str() )
  return false;

 *n_to_reduce=1;

 // Если описание макроса не содержит формальных аргументов, то можем
 // считать, что совпадения имени макроса и лексемы хватает для констатации
 // факта...
 if( !GetnArg() )
  return true;

 int icursor=ifirst+1;

 // Теперь должна быть открывающая скобка - за ней список значений формальных аргументов
 const UFString s( get_next( io, list, &icursor, txtfile ) );

 if( s != Macro_Parser::t_OroundParen.c_str() )
  {
   Print_Error( io, txtfile );
   io.merr().printf(
                    "[%vfE%us%vn] macro substitution : '(' expected, '%vfE%us%vn' is taken\n"
                    , name.c_str(), s.c_str()
                   );
   throw E_ParserError();
  }

 // Теперь загружаем конкретизацию для каждого формального аргумента.
 bool closed=false; // true, когда будет прочитана ')'
 for( int iarg=0; iarg<GetnArg(); iarg++ )
  {
   // Здесь будем накапливать конкретизирующие лексемы. Обращаю особое
   // внимание, что один формальный параметр может быть конкретизирован
   // целым списком лексем. Например, для макроса:
   //
   //               #define M(a,b)  a+b
   //
   // конструкция
   //
   //               M( 1 2, 3 )
   //
   // будет расшита в
   //
   //               1 2 + 3
   //
   //
   // Есть также особый синтаксис для списков, в которых есть запятые - например:
   //
   //               M( (1,2), 3 ) 
   //
   // будет расшит в 
   //
   //               1,2 + 3

   IR_Macro_Subst sub( GetArg(iarg) );

   if( closed )
    {
     // Формальный аргумент получает значение по умолчанию.
     std::copy( GetArg(iarg).def.begin(), GetArg(iarg).def.end(), std::back_inserter(sub) );
    }
   else
    {
     // Будем считывать лексемы для значения одного аргумента.
     bool first_tok=true;

     while( !txtfile.eof() )
      {
       const UFString s( get_next( io, list, &icursor, txtfile ) );

       if( s==Macro_Parser::t_OroundParen.c_str() )
        {
         if( first_tok )
          {
           // особый случай - список лексем в круглых скобках, запятые
           // включаются в определение аргумента.
 
           first_tok = false;

           int n_open=1; 
           
           while( !txtfile.eof() )
            { 
             const UFString s( get_next( io, list, &icursor, txtfile ) );

             if( s==Macro_Parser::t_OroundParen.c_str() )
              {
               n_open++;
              }
             else if( s==Macro_Parser::t_CroundParen.c_str() )
              {
               n_open--;
               if( !n_open )
                break;  
              }
             else if( s==L'\n' )
              continue; 

             sub.push_back( s );
            }                
  
           // Значение формального аргумента загрузили.
           break;
          }  
         else
          {
           Print_Error( io, txtfile );
           io.merr().printf(
                            "[%vfE%us%vn] macro substitution : opening parentess can not be used in this context\n"
                            , name.c_str()
                           );
           throw E_ParserError();
          }
        }  
 
       if( s==L'\n' )
        continue;

       first_tok = false;

       if( s == Macro_Parser::t_Comma.c_str() )
        {
         if( iarg == GetnArg()-1 )
          {
           Print_Error( io, txtfile );
           io.merr().printf(
                            "[%vfE%us%vn] macro substitution : too many arguments, macro definition requires only %d\n"
                            , name.c_str(), GetnArg()
                           );
           throw E_ParserError();
          }

         // Определение подстановки аргумента закончено.
         break;
        }

       if( s == Macro_Parser::t_CroundParen.c_str() )
        {
         if( iarg==GetnArg()-1 )
          {
           // Полностью закончено определение всех подстановок для аргументов.
           closed=true;

           // Если пропущен первый аргумент, и он имеет значение по умолчанию...
           if( iarg==0 && sub.empty() && !GetArg(iarg).def.empty() )
            {
             std::copy( GetArg(iarg).def.begin(), GetArg(iarg).def.end(), std::back_inserter(sub) );
            }

           break;
          }
         else
          {
           // Если оставшиеся аргументы могут иметь значения по умолчанию, то
           // всё нормально.
           bool have_def=true;
           for( int ii=iarg+1; ii<GetnArg() && have_def; ii++ )
           have_def = !GetArg(ii).def.empty();

           if( !have_def )
            {
             Print_Error( io, txtfile );
             io.merr().printf(
                              "[%vfE%us%vn] macro substitution : too few arguments, %d in macro definition\n"
                              , name.c_str(), GetnArg()
                             );
             throw E_ParserError();
            }

           closed=true;
           break;
          }
        }

       sub.push_back( s );
      }
    } 

   // Конкретизирован очередной формальный аргумент.
   subst.push_back( sub );

   // Сделаем еще одну полезную вещь - создадим временную переменную из
   // подстановки. Здесь есть одна хитрость со списочными подстановками...
   table->push_back( sub.CreateVar() );
  }

 if( !closed )
  {
   const UFString s( get_next( io, list, &icursor, txtfile ) );
   if( s != Macro_Parser::t_CroundParen.c_str() )
    {
     Print_Error( io, txtfile );
     io.merr().printf(
                      "[%vfE%us%vn] macro substitution : missing ')', got '%vfE%us%vn'\n"
                      , name.c_str(), s.c_str()
                     );
     throw E_ParserError();
    }
  }

 *n_to_reduce = icursor-ifirst;
 return true;
}

/***************************************************************************
 Пытается прочесть очередной элемент из списка list, и если этот список
 исчерпан, то подгружает токен из исходного файла. Вызывается из ::DoesMatch
****************************************************************************/
const UFString IR_Macro_Head::get_next(
                                       Sol_IO &io,
                                       lem::Collect<UFString> &list,
                                       int *icursor,
                                       UTextParser &txtfile
                                      ) const
{
 if( *icursor >= CastSizeToInt(list.size()) )
  {
   if( txtfile.eof() )
    {
     Print_Error( io, txtfile );
     io.merr().printf(
                      "[%vfE%us%vn] macro substitution : end of file reached\n"
                      , name.c_str()
                     );
     throw E_ParserError();
    }

   // В исходном списке не хватает лексем - подгрузим из исходного файла.
   lem::UFString fstr;
   txtfile.read(fstr);
   list.push_back(fstr);
  }

 return UFString( list[ (*icursor)++ ] );
}

