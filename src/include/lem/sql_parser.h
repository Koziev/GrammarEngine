#ifndef LEM_SQL_PARSER
#define LEM_SQL_PARSER
#pragma once

 #include <vector>
 #include <string>

namespace lem
{
 namespace Sql_Parser
 {
  using std::vector;
  using std::string;

  // ***************************************************************

  // ******************************************************
  // Базовый класс для любых разобранных SQL-команд.
  // ******************************************************
  class Sql_Command
  {
   private:
    Sql_Command( const Sql_Command& );
    void operator=( const Sql_Command& );

   public:
    Sql_Command(void) {};
    virtual ~Sql_Command(void) {};
  };


  // ***************************************************************

  class Sql_Select : public Sql_Command
  {
   public:
    string sql_genuine;      // Оператор без нестандартных элементов
    vector<string> col_name; // Отображаемые имена столбцов
    vector<string> extract_cols; // Извлекаемые столбцы (имена полей или более
                             // сложные конструкции).
    vector<string> vars;     // список принимающих переменных из INTO ...
    int n_col;               // Число извлекаемых столбцов (инициализируется,
                             // даже если столбцы не именованные).

    vector<string> from;     // Элементы, перечисленные в FROM                           

    string xml_source_file; // Из этого файла должны читаться данных XML

   public:
    Sql_Select( const char *text ) { n_col=0; Parse(text); }
    virtual void Parse( const char *text );
  };

  // ***************************************************************

  class Parser
  {
   public:
    Parser(void) {};

    virtual Sql_Command* Parse( const char *text );
  };

 } // namespace Sql_Parser
} // namespace lem

#endif
