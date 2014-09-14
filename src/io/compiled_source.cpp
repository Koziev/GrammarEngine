// -----------------------------------------------------------------------------
// File COMPILED_SOURCE.CPP
//
// (c) by Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// Надстройка над классом Source для работы с предкомпилированными текстами, то
// есть токены сначала загружаются в оперативную память, а потом можно быстро
// извлекать их из списка, возвращаться...
// -----------------------------------------------------------------------------
//
// CD->28.01.97
// LC->16.10.04
// ------------

#include <lem/compiled_source.h>

using namespace std;
using namespace lem;

CompiledSource::CompiledSource( int NTOKEN, CString *TOKENS )
:Text_Parser(),text(0,128)
{
 vector<CString> Tokens;
 Tokens.reserve(NTOKEN);
 for( int i=0; i<NTOKEN; i++ )
  Tokens.push_back(TOKENS[i]);

 SetTokens(Tokens);

 next=0;
 compiled=false;
 return;
}

// ********************************************************************
// Открываем текстовый файл-источник, читаем из него последовательно
// все токены и запоминаем их в списке в памяти. Только после отработки
// этой процедуры класс готов поставлять токены внешнему коду!
// ********************************************************************
void CompiledSource::Open( const char *TxtName )
{
 Text_Parser::Open(TxtName);

 // Читаем и сохраняем все токены в оперативной памяти.
 while( !Text_Parser::eof() )
  {
   AToken t = Text_Parser::read();

   // Токен с нулевой длиной - явный признак конца файла.
   if( !t.string().length() )
    break;
   else
    text.push_back(t);
  }

 compiled=true;
 return;
}

// ***********************************************************
// Возвращает очередной токен из списка в оперативной памяти.
// Продвигает указатель на следующий элемент в списке.
// ***********************************************************
const AToken CompiledSource::read(void)
{
 if( next>=text.size() )
  {
   // За пределами списка! Вернём пустой токен...
   AToken dummy;
   return dummy;
  }

 return text.get(next++);
}

/******************************************************************
 Возвращаемся к началу строки, в которой расположен токен, который
 будет возвращён при вызове read();
*******************************************************************/
void CompiledSource::ToLineBegin(void)
{
 const AToken &t = text.get(next);
 Text_Parser::seekp(t.GetBegin());
 Text_Parser::ToLineBegin();
 return;
}

// ********************************************************************
// Возвращает положение в исходном текстовом файле, если бы мы читали
// токены оттуда а не из списка в оперативной памяти.
// ********************************************************************
const SourceState CompiledSource::ftell(void) const
{
 return !compiled ?
         Text_Parser::tellp()
                  :
         ( text.get( next>=text.size() ? text.size()-1 : next).GetBegin() );
}

// ********************************************************************
// Возвращается к токену в оперативной памяти, который ходится в
// позиции в исходном текстовом файле, заданной как SourceState.
// Учитываем то факт, что обычно (99% случаев) производится откат
// на один токен назад.
// ********************************************************************
void CompiledSource::fseek( const SourceState &ss )
{
 if( !compiled )
  {
   Text_Parser::seekp(ss);
   return;
  }

 // Чаще всего возврат выполняется на один токен назад!
 if( next!=0 && text[next-1].GetBegin()==ss )
  {
   // Сделаем откат на один токен.
   next--;
   return;
  }

 // Ищем соответствующую позицию среди токенов перед предыдущим к текущему.
 // Предыдущий мы уже проверили, а чем откаты тем более редки, чем дальше
 // выполняется прыжок.
 bool found=false;
 int i,ifound;
 for( i=next-2; i>=0 && !found; i-- )
  found = text[ifound=i].GetBegin()==ss;

 if( found )
  {
   next=ifound;
   return;
  }

 // Производим поиск вперед.
 found=false;
 for( i=next-1; i<text.size() && !found; i++ )
  found = text[ifound=i].GetBegin()==ss;

 if( found )
  {
   next=ifound;
   return;
  }

 // Ошибка позиционирования файла!
 LEM_STOPIT;
}

/******************************************************
 Метод должен вернуть true, если все токены прочитаны.
*******************************************************/
bool CompiledSource::eof(void)
{
 if( !compiled )
  return Text_Parser::eof();

 return next>=text.size();
}

// -------------------------- End Of File [COMPILED_SOURCE.CPP] -----------------------
