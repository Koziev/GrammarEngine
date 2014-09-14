// -----------------------------------------------------------------------------
// File LEM_LOGP.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// CONTENS:
// ѕример ***компил€тора*** логических выражений. ¬ файле приведен работающий
// пример простейшего разборщика выражений. Ёто действительно компил€тор, ибо
// дл€ вычислени€ логического выражени€ сначала строитьс€ дерево вывода,
// соответсвующее всему выражению, а затем в него подставл€ютс€ значени€
// переменных и констант.
// -----------------------------------------------------------------------------
//
// CD->22.06.96
// LC->11.06.04
// ------------

#ifndef LEM_LOG_PARSER
#define LEM_LOG_PARSER
#pragma once

  #include <string>
  #include <vector>
  #include <lem/lexers.h>

  namespace lem
  {

 //  ласс дл€ описани€ логической переменной.
 class BoolVar
 {
  private:
   std::string name; // »м€ переменной.
   bool val; // Ћогическое значение.

  public:
   BoolVar(void) { val=false; }
   BoolVar( const BoolVar &x ) : name(x.name) { val=x.val; }
   BoolVar( const std::string& Name, bool Val=false ) : name(Name) { val=Val; }

   inline void operator=( const BoolVar &x )
   {
    val = x.val;
    name = x.name;
   }

   inline const std::string& GetName(void) const { return name; }
   inline bool GetVal(void) const { return val; }
 };

 class BoolCompiler
 {
  private:
   std::vector<BoolVar> var_list; // “аблица переменных.

  public:
   BoolCompiler(void){};

   void Execute( lem::Text_Parser& txtfile );
   bool compute( lem::Text_Parser& txtfile ) const;

   inline const std::vector<BoolVar>& vars() const { return var_list; }
 };

 enum type { EMPTY, VALUE, VARNAME, OR, AND };

 class BoolTree
 {
  private:
   int type;
   bool val;
   bool affirmative;
   std::string varname;
   std::vector<BoolTree*> or;
   std::vector<BoolTree*> and;

   void Delete(void);
   void Init( const BoolTree& lt );

  public:
   BoolTree(void)
   {
    type=EMPTY;
    affirmative=true;
   }

   BoolTree( const std::string& i );
   BoolTree( lem::Text_Parser &txtfile );
   BoolTree( const BoolTree& lt );
   ~BoolTree(void);

   BoolTree& operator=( const BoolTree& lt );
   void set( bool aff ) { affirmative=aff; }
   bool compute( const std::vector<BoolVar>& vars ) const;
  };

 } // namespace 'lem'

#endif
// --------------------------- End Of File [LEM_LOGP.H] ------------------------
