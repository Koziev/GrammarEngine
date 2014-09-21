// -----------------------------------------------------------------------------
// File MACRO_GENERATOR.H
//
// (c) Koziev Elijah
//
// Content:
// Классы для генератора отчетов БД.
// -----------------------------------------------------------------------------
//
// CD->01.02.2004
// LC->23.04.2007
// --------------

#pragma once
#ifndef LEM_MACRO_GENERATOR
#define LEM_MACRO_GENERATOR

 #include <set>

 #include <lem/config.h> 
 #include <lem/oformatter.h>
 #include <lem/fstring.h>
 #include <lem/sql_parser.h>
 #include <lem/string_parser.h>
 #include <lem/stl.h>
 #include <lem/db.h>

 #if defined LEM_DOT_NET
 #include <vcclr.h>
 using namespace System;
 #endif


 namespace lem
 {
  namespace Macro_Generator
  {
   class Macro_Formatter;
   class Macro_Frame;

   using lem::StrParser;
   using lem::FString;
   using std::vector;
   using lem::Database::SQL_Data_Source;

  // *************************************************
  // Специализированный лексер для парсинга скриптов.
  // Работает с 1-байтовыми символами, лексемы не
  // ограничены в длине.
  // *************************************************
  class A_Parser : public StrParser<FString>
  {
   public:
    A_Parser( const FString &Txt ) : StrParser<FString>(Txt)
   {
    // Часть символов не являются разделителями для данного парсера.
    delims = remove_chars( delims, "${}" );
   }
  };


   // *************************************************************************
   // Структура для контроля за порядком исполнения макрооператоров - например,
   // для реализации операторов BREAK и CONTINUE внутри цикла.
   // *************************************************************************
   struct Execution_Flow
   {
    typedef enum { NORMAL, BREAK_LOOP, CONTINUE_LOOP } STATUS;
    STATUS status;

    Execution_Flow(void) { status=NORMAL; }
   };


   // Специальное исключение - возникает, когда в тексте макропрограммы
   // встречается оператор чужого формата, хотя и похожий на свой.
   class E_MG_Alien_Command : public E_ParserError {};


   // ***********************************
   // Базовый класс для макрокоманды. Все
   // обработчики макрокоманд наследуются
   // от этого класса.
   // ***********************************
   class Base_Command
   {
    protected:
     FString name; // имя макрокоманды (без лидирующего символа-признака
                   // макрокоманды, например '$'). Это поле инициализируется
                   // в конструкторе производного класса, и затем используется
                   // парсером при поиске макрокоманд с тексте.

     Base_Command( const Base_Command& );
     void operator=( const Base_Command& );

    public:
     Base_Command( const char *Name ):name(Name) {};
     virtual ~Base_Command(void) {};

     inline bool operator==( const FString &Name ) const
     { return name==Name; }

     inline const FString& Get_Name(void) const { return name; }

     // *****************************************************************
     // Далее чистые виртуальные методы - переопределяются в наследниках
     // для выполнения работы конкретной макрокоманды.
     // *****************************************************************

     // **********************************************************************
     // Загружается вся конструкция макрокоманды - то есть ее тело (например,
     // для цикла - переменная цикла, граничные значения, тело цикла). При
     // непосредственном исполнении макрокоманды данные уже не загружаются
     // из текста скрипта, а используются загруженные в этом методе.
     // **********************************************************************
     virtual bool LoadHead( A_Parser &txt, int i_start )=0;

     // ***************************
     // Исполнение макрокоманды.
     // ***************************
     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      )=0;

     // ******************************************
     // Виртуальный конструктор - создает клон.
     // ******************************************
     virtual Base_Command* New(void) const =0;
   };


   // ***************************
   // Дескриптор для FOR-цикла
   // ***************************
   class For : public Base_Command
   {
    protected:
     FString var;      // имя переменной цикла
     FString iterator; // какой массив итерировать
     int begin;
     int body_pos;     // позиция первого символа тела цикла
     int n0;           // начальное значение итератора
     int n_pass;       // сколько проходов цикла
     int i_pass;       // текущее значение переменной цикла
     vector<FString> sn; // Список принимаемых переменной значений.

    public:
     For(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_start );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   // *************************************************************************

   class If : public Base_Command
   {
    private:
     FString condition; // условие

     int if_begin;      // Начало оператора
     int then_begin;    // Начало then-ветки

     int Get_Priority( const FString &com ) const;
     FString Parse_Expression( A_Parser &txt, int &i_cur );

    public:
     If(void);

     virtual Base_Command * New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   // *************************************************************************

   class Break : public Base_Command
   {
    public:
     Break(void);

     virtual Base_Command * New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   // *************************************************************************

   class Continue : public Base_Command
   {
    public:
     Continue(void);

     virtual Base_Command * New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   // ******************************************************************

   class Correlator : public Base_Command
   {
    private:
     FString word;   // склоняемое слово
     int    value;   // число, с которым согласуем
     int    l_case;  // грамматический падеж
     int beg, end;   // начало и конец оператораend - символ после ')'

    public:
     Correlator(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   // *****************************************************
   // Преобразователь числа в текстововое представление
   // *****************************************************
   class Convertor : public Base_Command
   {
    private:
     int    value; // число
     int beg, end; // начало и конец оператора end - символ после ')'

    public:
     Convertor(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   // **********************************************************************
   // Преобразователь арифметического выражения в текстововое представление
   // **********************************************************************
   class Calculator : public Base_Command
   {
    private:
     FString expr;
     int beg, end;

    public:
     Calculator(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   class Call : public Base_Command
   {
    private:
     FString proc;   // Имя вызываемой PL/SQL процедуры

     // аргументы вызова процедуры
     std::vector< std::pair< FString /*name*/, FString /*value*/ > > args; 
     int beg, end;

    public:
     Call(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   class Odbc : public Base_Command
   {
    private:
     FString alias, login, psw;

     int beg, end;

    public:
     Odbc(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   class Define : public Base_Command
   {
    private:
     FString var;   // имя создаваемого макроса
     FString value; // содержимое

     int beg, end;

    public:
     Define(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   class Ask : public Base_Command
   {
    private:
     FString var;      // имя создаваемого макроса
     FString question; // отображаемый вопрос

     int beg, end;

    public:
     Ask(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };



   class Subst : public Base_Command
   {
    private:
     FString str;     // преобразуемая строка
     FString pattern; // паттерн - что меняем
     FString new_str; // на что меняем
     int beg, end;    // начало и конец оператора - символ после ')'

    public:
     Subst(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };

   // ********************************************** 
   // Реализация команды переформатирования строки.
   // ********************************************** 
   class Format : public Base_Command
   {
    private:
     FString str; // преобразуемая строка
     FString fmt; // формат
     int beg, end;    

     FString i_fmt; // часть формата для целой части
     FString f_fmt; // часть формата для дробной части 
     int f_count;   // сколько знаков в дробной части надо вывести.
     char f_dot;    // отделитель дробной части

    public:
     Format(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   // ***************************************************************

   // ***************************************************************

   class Sql_Select : public Base_Command
   {
    private:
     string add_front, add_back; // Символы, добавляемые к имени макросов

     int beg, end;
     int body_beg, body_end;   // если есть тело оператора $BEGIN ... $END
     FString sql;              // исполняемый SELECT
     vector<FString> options;  // список опций форматирования
     lem::Sql_Parser::Sql_Select *parsed_sql;

    protected:
     void Prepare_Macro_Name( string &macro_name ) const;

    public:
     Sql_Select(void);

     Sql_Select( const Sql_Select &x );
     void operator=( const Sql_Select &x );

     virtual ~Sql_Select(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );

     void Add_Macro_Front( const char *s ) { add_front=s; }
     void Add_Macro_Back( const char *s ) { add_back=s; }
   };

   // *************************************************************************

   class Group : public Base_Command
   {
    private:
     int group_beg, body_beg, body_end, outside_beg;

    public:
     Group(void);

     virtual Base_Command * New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   class Print : public Base_Command
   {
    private:
     int beg, end;
     FString text; // текст для вывода на консоль

    public:
     Print(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   class Debug : public Base_Command
   {
    private:
     int beg, end;
     FString text; // текст для вывода в журнал

    public:
     Debug(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };

   class Reinterpret : public Base_Command
   {
    private:
     int beg, end;

    public:
     Reinterpret(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };



   // ***************************************************************
   // Фабрика объектов: хранит образцы всех команд и может по имени
   // команды построить C++-объект.
   // ***************************************************************
   class Cmd_Factory
   {
    protected:
     vector<Base_Command*> cmd_list; // список обработчиков команд
     bool case_sensitive; // учитывать регистр символов при поиске команд

    public:
     Cmd_Factory(void);
     virtual ~Cmd_Factory(void) { ZAP_A(cmd_list); }

     virtual Base_Command* Find( const FString &Txt ) const;

     inline void Case_Sensitive(void) { case_sensitive=true; }
   };


   // **************************************************************


   // *************************************************************************
   // Локальная таблица макросов. Макрос - это просто пара строк имя-значение.
   // *************************************************************************
   class Macro_Frame : public vector< std::pair<FString/*name*/,FString/*value*/> >
   {
    private:
     std::set<char> first_chars;
     Macro_Frame *prev;

     std::pair<FString,FString>* Find_Macro( const FString &name );

     Macro_Frame( const Macro_Frame& );
     void operator=( const Macro_Frame& );

     void push_back( const std::pair< FString, FString > & ); // blocked!

    public:
     Macro_Frame( Macro_Frame *Prev=NULL ) { prev = Prev; }

     // *********************************************************************
     // В списке макросов присваиваем макросу с именем name
     // новое значение. Если такого макроса нет, то добавляем его.
     // *********************************************************************
     bool Set_Macro( const FString &name, const FString &value );
     void Subst_Macros( FString &txt );

     void Rescan(void);
   };


   // *****************************
   // Общие флаги исполнения - как должен себя вести макрогенератор
   // в некоторых ситуациях.
   struct Exec_Options
   {
    bool show_alert; // в случае возникновения ошибок - показывать
                     // на экране MessageBox.
    FString error_stamp; // сообщение, вставляемое в отчет, при возникновении
                         // ошибок

    Exec_Options(void)
    {
     show_alert=false; 
     error_stamp = "#error#";
    }
   };


   // ************************************************************************

   class Macro_Formatter
   {
    private:
     FString *text; // Обрабатываемый скрипт (изменяется в ходе работы).
     OFormatter *console; // Форматтер для вывода текстовых сообщений из скрипта
     SQL_Data_Source* db;

    protected:
     Exec_Options exec_flags;
     Cmd_Factory *cmd_factory;

    public:
     inline void Set_DB( SQL_Data_Source* Db ) { db=Db; }
     inline SQL_Data_Source* Get_DB(void) { return db; }

     Macro_Formatter( FString *Text=NULL );

     virtual void Build_Commands(void);

     virtual void Set_Console( OFormatter *Console );
     inline OFormatter* Get_Console(void) { return console; }

     virtual ~Macro_Formatter(void);

     void Interpret(
                    FString &txt,
                    Macro_Frame &macros,
                    Execution_Flow &flow
                   );

     void Interpret( FString *Text=NULL );

     inline const Cmd_Factory& Get_Cmd_Factory(void) const { return *cmd_factory; }

     inline const Exec_Options& get_Exec_Flags(void) const { return exec_flags; }
   };

 } // namespace macro_generator

} // namespace lem


#endif
// ------------------------- End Of File [MACRO_GENERATOR.H] -------------------