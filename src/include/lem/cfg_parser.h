// -----------------------------------------------------------------------------
// File CFG_PARSER.H
//
// (c) Koziev Elijah
//
// Content:
// Операции с файлами конфигурации (ini).
// -----------------------------------------------------------------------------
//
// CD->21.07.1995
// LC->07.09.2017
// --------------

#ifndef LEM_INI_FILE__H
#define LEM_INI_FILE__H
#pragma once

 #include <lem/lexers.h>
 #include <lem/smart_pointers.h>
 #include <string>
 #include <vector>
 #include <utility>

 using std::pair;
 using std::vector;

 namespace lem
 {
  namespace Cfg_Parser
  {
   struct SectionEntry
   {
    std::string name;

    typedef Text_Parser::pos_type pos_type;
    pos_type location;

    SectionEntry *prev; // Пред. в списке.
    SectionEntry *next; // След. в списке.
    SectionEntry *sub;  // На подсекцию.
    SectionEntry *supr; // Корневой.
    int level;          // Уровень вложенности.

    SectionEntry(void);
    SectionEntry(
                 const std::string &Name,
                 const pos_type& Loc,
                 int Lev
                );
    SectionEntry( const SectionEntry &se );

    ~SectionEntry(void);

    SectionEntry& operator=( const SectionEntry& se );

    void del(void);
   };


   struct SectionTree
   {
    typedef SectionEntry NODE;
    NODE *first;
    NODE *current;

    SectionTree(void);

    ~SectionTree(void);

    void Set_First( NODE *s ){ first->sub=s; }
    void To_Start(void) { current=first; }

    bool Next(void);
    bool Prev(void);
    bool Up(void);
    bool Down(void);
    bool Move_To( const string &loc );
    void Clear(void);
   };




   struct RootEntry : public SectionEntry
   {
    SectionTree *parent;

    RootEntry( SectionTree *p )
    {
     parent=p;
     name=string("_root_");
    }
   };



   extern int ParseSectionPath(
                               const string &sec_name,
                               string **name
                              );


  // ********************************************
  // Базовый парсер структурированных текстов.
  // ********************************************
  class Ini_Parser : public Text_Parser
  {
   protected:
    SectionTree tree;
    int bracket_level; // Для отслеживания текущей глубины секций

    // Указатель на поток, откуда берется текст.
    lem::Ptr<lem::Char_Stream::WideStream> stream;

    virtual void ReadDirectory(void);

    int status;
    Text_Parser::pos_type beginning;

    bool use_curled_brackets; // Используются фигурные скобочки для
                              // обозначения начала и конца тела секции.
                              // Если используются, то можно применять вложенные
                              // секции.

    inline SectionTree& GetTree(void) { return tree; }

   public:
    typedef SectionEntry section_type;

    inline lem::Char_Stream::WideStream& GetStream(void) { return *stream; }

   public:
    Ini_Parser(void);

    virtual void Open( lem::Ptr<lem::Char_Stream::WideStream> txt );
    virtual void Open( const lem::Path &filepath );

    virtual bool seek_section( const string& tosection );
    virtual const string NextFromSection(void);
    virtual bool write_to_config(
                                 const char *section_name,
                                 const char *var_name,
                                 const char *new_value
                                );

    int get_int( const string &path, const string &name, int def );
    bool get_bool( const string &path, const string &name, bool def );

    #if !defined LEM_NOREAL
    double get_real( const string &path, const string &name, double def );
    #endif

    const string get_string( const string &path, const string &name, const string &def );
    virtual bool seek_variable( const string& name );
    virtual const string GetNextVar(void);
    bool is_correct_var_name( const string& var );
   };

  } // namespace Cfg_Parser 

 } // namespace lem

#endif
