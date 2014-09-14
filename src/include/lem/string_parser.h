// -----------------------------------------------------------------------------
// File STRING_PARSER.H
//
// (c) Koziev Elijah
//
// Content:
// Класс-шаблон StrParser - простой лексемный парсер текстовых строк.
// -----------------------------------------------------------------------------
//
// CD->17.05.2004
// LC->02.03.2008
// --------------

#ifndef LEM_SPAR__H
#define LEM_SPAR__H
#pragma once

 #include <lem/conversions.h>
 #include <algorithm>

 #undef min
 #undef max

 namespace lem
 {

 template < class STR >
 class StrParser
 {
  public:
   typedef typename STR::value_type char_type;
   typedef int pos_type;

   bool parse_sign_as_part_of_float;
   bool parse_float; // Считывать ли числа с плавающей запятой
   int err_context_span; // число символов до и после места ошибки в печати диагностики

  protected:
   const STR &txt; // Строка текста, подвергаемая разбору.

   STR spaces; // Настроечная: символы-пробелы
   STR delims; // Настроечная: символы-разделители

   int i_read; // Внутренний курсор чтения
   int i_backpos; // Позиция для возврата на начало последней лексемы

   // *******************************************
   // Это пробельный символ?
   // *******************************************
   inline bool sp( char_type ch ) const
   { return std::find( spaces.begin(), spaces.end(), ch )!=spaces.end(); }

   // *******************************************
   // Это символ-разделитель?
   // *******************************************
   inline bool delim( char_type ch ) const
   { return std::find( delims.begin(), delims.end(), ch )!=delims.end(); }

   // ******************************************************************
   // Пытаемся считать лексему, которая представляет число с плавающей
   // запятой в формате +1111.2222e-444.
   // Если считать число не удается, то возвращается пустая строка.
   // ******************************************************************
   const STR read_floating( int &i_cur ) const
   {
    STR res;

    // Знак мантиссы
    #if defined LEM_GNUC
    const typename STR::value_type c = txt[i_cur];
    #else
    const STR::value_type c = txt[i_cur];
    #endif 

    if( c=='-' || c=='+' )
     {
      i_cur++;
      res = c;

      if( !parse_sign_as_part_of_float )
       {
        // Запрещено считывать знак перед числом, это может быть нужно для
        // всяких калькуляторов и т.д.
        return res;
       }
     }

    // Цифры до точки
    while( txt[i_cur] && is_udigit( txt[i_cur] ) )
     res += txt[i_cur++];

    if( txt[i_cur]!='.' && txt[i_cur] )
     {
      // Это не точка, значит число кончилось, либо начался порядок
      // Кстати, в Фортране символ порядка может быть 'd'
      if( txt[i_cur]!='e' && txt[i_cur]!='E' )
       {
        // должен быть разделитель.
        if( delim( txt[i_cur] ) )
         return res;
        else
         // некорректный формат числа
         return STR();
       }

      // идет порядок числа  - после 'e'
      res += txt[i_cur++];
     }
    else
     {
      res += txt[i_cur++];
    
      // Цифры после точки - до порядка
      while( txt[i_cur] && is_udigit( txt[i_cur] ) )
       res += txt[i_cur++];

      if( txt[i_cur]!='E' && txt[i_cur]!='e' )
       // Порядок не задан
       return res;
     }

    res += txt[i_cur++];
    
    // Знак порядка
    if( txt[i_cur] && ( txt[i_cur]!='+' && txt[i_cur]!='-' && !is_udigit(txt[i_cur]) ) )
     return STR();

    if( !is_udigit(txt[i_cur]) )
     res += txt[i_cur++];

    // Порядок.
    int n_exp=0;
    while( txt[i_cur] && is_udigit( txt[i_cur] ) )
     {
      res += txt[i_cur++];
      n_exp++;
     }
     
    if( !n_exp )
     {
      // Порядок не определен нормально.
      return STR();
     }

    return res;
   }


  public:   
   StrParser( const STR &Txt )
    : txt(Txt),
      spaces( " \t\r\n" ), 
      delims( "`~!@#$%^&*()-=+\\|[{]};:,<.>/?" )
   {
    i_read=0;
    parse_float=true;
    parse_sign_as_part_of_float=true;
    err_context_span=128;
    i_backpos = 0;
   }

   inline const STR& string(void) { return txt; }

   // Позволяют модифицировать настроечные списки.
   inline STR get_Spaces(void) { return spaces; }
   inline STR get_Delims(void) { return delims; }

   inline void set_Delims( const STR &s ) { delims=s; }
   inline void set_Spaces( const STR &s ) { spaces=s; }

   // *************************************************************************
   // Считывание одной лексемы. i_cur - курсор чтения (обновляется - при выходе
   // будет установлен на символ ПОСЛЕ прочитанной лексемы).
   // *************************************************************************
   inline const STR read(void) { i_backpos = i_read; return read(i_read); }

   inline bool probe( const STR & token )
   {
    if( read() == token )
     return true;

    back();
    return false;
   }

   // ******************************
   // Пропуск пробелов
   // ******************************
   void skip_whites( int &i_cur ) const
   {
    while( txt[i_cur] && sp( txt[i_cur] ) ) i_cur++;
   }

   // *************************************************
   // Считывание строки в двойных кавычках
   // Курсор в начале должен быть на начальной кавычке.
   // На выходе - на символе после закрывающей кавычки.
   // *************************************************
   const STR read_quoted( int &i_cur ) const
   {
    STR lex;
    lex = txt[i_cur++];

    while( txt[i_cur] && txt[i_cur]!='"' )
    {
     if( txt[i_cur]=='\\' )
      lex += txt[++i_cur]; 
     else
      lex += txt[i_cur];

     i_cur++;
    } 

    if( txt[i_cur]=='"' )
     {
      i_cur++;
      lex += '"';
     }

    return lex;
   }

   const STR read_apostrophed( int &i_cur ) const
   {
    STR lex;
    lex = txt[i_cur++];

    while( txt[i_cur] && txt[i_cur]!='\'' )
    {
     lex += txt[i_cur];

     if( txt[i_cur]=='\\' )
      lex += txt[++i_cur];

     i_cur++;
    } 

    if( txt[i_cur]=='\'' )
     {
      i_cur++;
      lex += '\'';
     }

    return lex;
   }
   

   const STR read( int &i_cur ) const
   {
    int l = txt.length();
    if( i_cur>=l )
     return STR(); // Попытка чтения за пределами строки - возвращаем пустую лексему

    // Начальные пробелы
    skip_whites( i_cur );

    STR lex;

    if( txt[i_cur]=='"' )
     return read_quoted( i_cur );

    if( txt[i_cur]=='\'' )
     return read_apostrophed( i_cur );

    if( parse_float )
     {
      // Попробуем загрузить как число с плавающей точкой.
      int i_back = i_cur;

      STR f = read_floating(i_cur);
      if( !f.empty() )
       // Да, получилось.
       return f;  

      // Неудача - снова загружаем уже как лексему.
      i_cur = i_back;
     }


    if( delim( txt[i_cur] ) )
     {
      lex = txt[i_cur++];
     }
    else
     while(
           txt[i_cur] &&
           !sp(txt[i_cur]) &&
           !delim( txt[i_cur] )
          )
    {
     lex += txt[i_cur];
     i_cur++;
    } 

   return lex;  
  }

  // ********************************************************
  // Читает указанный токен, если прочитана другая лексема - 
  // генерируется исключение.
  // ********************************************************
  inline void read_it( const char_type *token ) { i_backpos = i_read; read_it(i_read,token); }

  void read_it( int &i_cur, const char_type *token ) const
  {
   if( read( i_cur ) != token )
    {
     // Собираем строку 'контекста' ошибки
     int i_from = std::max( 0, i_cur-err_context_span );
     int i_to = std::min( txt.length(), i_cur+lem::lem_strlen(token)+err_context_span );
     STR context( txt.begin()+i_from, txt.begin()+i_to-1 );

     throw ECheckFault(
                       to_wstr("Missing token ")+to_wstr(token)+
                       to_wstr( " in context " ) + to_wstr(context.c_str())
                     );
    }
  }

  // Достигнут конец потока?
  inline bool eof(void) const { return i_read >= txt.length(); }
  inline bool eof( int icur ) const { return icur >= txt.length(); }

  // Возвращает текущую позицию курсора чтения
  inline pos_type tellp(void) const { return i_read; }

  // Устанавливает текущее значение курсора чтения
  inline void seekp( pos_type x ) { i_read=x; }

  inline void back(void) { i_read = i_backpos; }
 };

 } // namespace lem

#endif
