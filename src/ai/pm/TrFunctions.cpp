// LC->24.11.2011

#include <lem/solarix/tokens.h>
#include <lem/solarix/pm_autom.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/PM_FunctionLoader.h>
#include <lem/solarix/tr_funs.h>

using namespace lem;
using namespace Solarix;

TrBuiltInFunSignature::TrBuiltInFunSignature( const wchar_t *str )
{
 sign = L'=';

 if( lem_strlen(str)>0 )
  {
   if( str[0]==L'>' )
    {
     sign = str[0];
     n_args.push_back( to_int(str+1) );
    }
   else   
    {
     if( lem::lem_find(str,L',')!=UNKNOWN )
      {
       lem::Collect<lem::UFString> toks;
       lem::parse( str, toks, L"," );
       for( lem::Container::size_type i=0; i<toks.size(); ++i )   
        n_args.push_back( to_int(toks[i]) );
      }
     else 
      {
       n_args.push_back( to_int(str) );
      }
    }
  }

 return;
}

TrBuiltInFunSignature::TrBuiltInFunSignature( const TrBuiltInFunSignature &x )
{
 sign = x.sign;
 n_args = x.n_args;
}

void TrBuiltInFunSignature::operator=( const TrBuiltInFunSignature &x )
{
 sign = x.sign;
 n_args = x.n_args;
}


bool TrBuiltInFunSignature::Check( int n ) const
{
 if( n_args.empty() )
  return true;

 if( sign==L'=' )
  {
   return n_args.find(n)!=UNKNOWN;
  }
 else if( sign==L'>' )
  {
   return n>n_args.front();
  }
 else if( sign==L'<' )
  {
   return n>n_args.front();
  }

 LEM_STOPIT;
 return false;
}


TrFunctions::TrFunctions(void)
{
 #if defined SOL_CAA
 stat_vars_initialized=0;
 #endif

 // Список встроенных функций с данными об их сигнатуре, точнее о количестве необходимых
 // аргументов при вызове. Так как встроенные функции могут иметь плавающее кол-во аргументов,
 // то применется специальный микроформат описания сигнатуры.
 const wchar_t* b[]=
 {
  L"copy", L"1",
  L"neq", L"2",
  L"eq", L">1",
  L"eqi", L">1",
  L"one_of", L">1",
  L"gt", L"2",
  L"ge", L"2",
  L"lt", L"2",
  L"log_or", L">1",
  L"log_and", L">1",
  L"log_not", L"1",
  L"wordform_class", L"1",
  L"wordform_language", L"1",
  L"wordform_entry", L"1",
  L"wordform_lexem", L"1",
  L"wordform_set_coord", L">1",
  L"wordform_setadd_coord", L">1",
  L"wordform_clear_coord", L">1",
  L"wordform_get_coord", L"2",
  L"wordform_dims", L"1",
  L"wordform_copy_coord", L">2",
  L"wordform_refresh", L"1",
  L"wordform_create", L">1",
  L"wordform_root", L"1",
  L"wordform_pack", L"1",
  L"wordform_replace", L"2",
  L"wordform_decompose", L"1",
  L"wordform_pos", L"1",
  L"entry_name", L"1",
  L"entry_count_forms", L"1",
  L"entry_get_form", L"2",
  L"entry_forms", L"1",
  L"entry_find", L"2",
  L"phrase_find", L"1",
  L"mark_get", L"3",
  L"mark_add", L"",
  L"mark_clear", L"",
  L"mark_count", L">1",
  L"mark_copy", L">1",
  L"link_count", L"",
  L"link_get", L"3",
  L"link_getref", L"3",
  L"link_get_type2", L"3",
  L"link_add", L">3",
  L"link_remove", L">1",
  L"link_copy", L">1",
  L"var_count", L"1",
  L"var_get", L"2",
  L"var_getref", L"2",
  L"var_set", L"3",
  L"var_back", L">0",
  L"var_add", L">1",
  L"var_prepend", L"2",
  L"var_remove", L"2",
  L"var_create", L">0",
  L"thesaurus_find", L">1",
  L"thesaurus_collect", L">1",
  L"seq_create", L">0",
  L"seq_get", L">0",
  L"fun_create", L"1",
  L"fun_call", L">0",
  L"type_is_void", L"1",
  L"type_is_bool", L"1",
  L"type_is_int", L"1",
  L"type_is_string", L"1",
  L"type_is_tree", L"1",
  L"type_is_trees", L"1",
  L"type_is_fun", L"1",
  L"type_is_tuple", L"1",
  L"to_void", L"",
  L"to_int", L"1",
  L"is_int", L"1",
  L"to_string", L"1",
  L"to_wordform", L"1",
  L"ctx_var", L"0",
  L"ctx_root", L"1",
  L"ctx_cursor", L"0",
  L"arith_minus", L"2",
  L"arith_plus", L"2",
  L"arith_mul", L"2",
  L"arith_div", L"2",
  L"arith_mod", L"2",
  L"str_icmp", L"2",
  L"str_eq_beg", L"2",
  L"str_eq_end", L"2",
  L"str_eq_begi", L"2",
  L"str_eq_endi", L"2",
  L"str_len", L"1",
  L"str_left", L"2",
  L"str_right", L"2",
  L"str_mid", L"3",
  L"str_index_of", L"2",
  L"str_rindex_of", L"2",
  L"str_regex", L"2",
  L"str_charset", L"3", 
  L"str_cat", L">1",
  L"env_find", L"2",
  L"env_get", L"2",
  L"env_set", L"3",
  L"env_remove", L">0",
  L"tuple_create", L"",
  L"tuple_get", L"2",
  L"tuple_set", L"3",
  L"tuple_count", L"1",
  L"tuple_add", L"2",
  L"tuple_concat", L">1",
  L"tuple_remove", L"2",
  L"tuple_insert", L"1",
  L"tuple_foreash", L"2", 
  L"tuple_clear", L"1",
  L"tuple_find", L"2",
  L"ngrams_status", L"2",
  L"ngrams_find", L">1",
  L"ngrams_filter", L"4",
  L"transform_module", L"3",
  L"subst_cplx", L"3,4",
  L"replace_cplx", L"3,4",
  L"restore_case", L"1",
  L"is_null", L"1",
  L"syntax_analysis", L"1,2",
  L"replace", L"2,3,4",
  L"debug_print", L"2",
  L"export_get_coord", L"2",
  L"export_copy_coords", L"2",
  L"raise" ,L"1",

  // ...
  NULL
 };

 int i=0;
 while( b[i]!=NULL )
  {
   builtin.insert( std::make_pair(UCString(b[i]), TrBuiltInFunSignature(b[i+1])) );
   i+=2;
  }

 statements.insert( L"if" );
 statements.insert( L"for" );
 statements.insert( L"while" );
 statements.insert( L"scan" );


 const wchar_t *cpf[]=
 {
  L"not",
  L"or",
  L"and",
  L"noshift",
  L"if",
  L"until",
  L"repeat",
  L"repeat0",
  L"group",
  L"mark",
  L"tree",
  L"contains",
  L"lambda",
  L"lambda0",
  L"optional",
  L"regex",
  L"regex_strict",
  L"in_wordentry_set",
  L"in_word_set",
  L"in_collocation_set",
  L"pattern",
  NULL
 };

 i=0;
 while( cpf[i]!=NULL )
  condictor_point_funs.insert( UCString(cpf[i++]) );

 return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void TrFunctions::AddForwardDeclaration( TrFunction *fun )
{
 lem::UCString uname( lem::to_upper(fun->GetName()) );
 NAME2FUN::iterator it = name2fun.find( uname );
 if( it!=name2fun.end() )
  {
   for( lem::Container::size_type i=0; i<funs.size(); ++i )
    if( funs[i] == it->second )
     {
      delete funs[i];
      funs[i] = fun;
      name2fun.erase(uname);
      name2fun.insert( std::make_pair( uname, fun ) );
      break;
     }
  }
 else
  {
   funs.push_back(fun);
   name2fun.insert( std::make_pair( uname, fun ) );
  }

 return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
const TrFunction* TrFunctions::CompileDeclaration(
                                                  PM_Automat &pm,
                                                  lem::Iridium::Macro_Parser &txtfile,
                                                  const TrProcedureDeclaration &procs
                                                 )
{
 // Синтаксис определения функции:

 // function возвр_тип имя( тип имя_аргумента, тип имя_аргумента, ... )
 // {
 //  тело фукции
 // }
 //
 // Особый синтаксис:
 // function возвр_тип имя( тип имя_аргумента, тип имя_аргумента, ... );
 //
 // позволяет сделать forward объявление функции
 
 const lem::Iridium::BSourceState &beg = txtfile.tellp();

 TrFunction *fun = new TrFunction;
 fun->CompileDeclaration( pm, txtfile, *this, procs );

 lem::UCString uname( lem::to_upper(fun->GetName()) );
 NAME2FUN::iterator it = name2fun.find( uname );
 if( it!=name2fun.end() )
  {
   for( lem::Container::size_type i=0; i<funs.size(); ++i )
    if( funs[i] == it->second )
     {
      if( funs[i]->IsForwardDeclaration() )
       {
        // заменяем объявление функции на ее нормальное определение.
        delete funs[i];
        funs[i] = fun;
        name2fun.erase(uname);
        name2fun.insert( std::make_pair(uname,fun) );
        break;
       }
      else
       {
        lem::Iridium::Print_Error( beg, txtfile );
        pm.GetIO().merr().printf( "Function [%us] is already defined\n", fun->GetName().c_str() );
        throw E_ParserError();
       }
     }
  }
 else
  {
   funs.push_back(fun);
   name2fun.insert( std::make_pair(uname,fun) );
  }

 return fun;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
TrFun_Lambda* TrFunctions::CompileLambdaDeclaration(
                                                    PM_Automat &pm,
                                                    lem::Iridium::Macro_Parser &txtfile,
                                                    const TrProcedureDeclaration &procs,
                                                    const TrKnownVars &lambda_caller
                                                   )
{
 // Синтаксис определения лямбда-функции:

 // lambda[(связываемые_локальные_переменные)] тип( тип имя_аргумента, тип имя_аргумента, ... )
 // {
 //  тело фукции
 // }
 
 lem::MCollect<UCString> locals;
 if( txtfile.pick().GetToken()==B_OROUNDPAREN )
  {
   txtfile.read();
 
   while( !txtfile.eof() )
    {
     if( txtfile.pick().GetToken()==B_CROUNDPAREN )
      break;
     
     if( !locals.empty() )
      txtfile.read_it(B_COMMA);
 
     locals.push_back( txtfile.read() );
    }

   txtfile.read_it( B_CROUNDPAREN );
  }


 TrFunction *fun = new TrFunction;
 fun->CompileDeclaration( pm, txtfile, *this, procs, &lambda_caller );
 funs.push_back(fun);
 if( !fun->GetName().empty() )
  name2fun.insert( std::make_pair( lem::to_upper(fun->GetName()), fun ) );

 // Теперь надо скомпилировать ее вызов как обычной пользовательской функции
 TrFun_Lambda *call = new TrFun_Lambda(fun,locals);
 TrKnownVars kvars( &pm.GetFunctions().Get().global_known_vars );

 // В теле лямбда-функции видны только те переменные из тела внешней функции, которые явно перечислены.
 for( lem::Container::size_type i=0; i<locals.size(); ++i )
  {
   TrType local_type = lambda_caller.GetVarType(locals[i]);
   kvars.RegisterVar( local_type, locals[i] );
  }  
 
 call->CompileDeclaration( pm, txtfile, *this, procs, kvars, NULL );

 return call;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
TrFunCall* TrFunctions::CompileCall(
                                    PM_Automat &pm,
                                    lem::Iridium::Macro_Parser &txtfile,
                                    const TrProcedureDeclaration &procs,
                                    TrKnownVars &known_vars
                                   )
{
 const lem::Iridium::BethToken &t = txtfile.read();

 const int src_location = pm.GetDict().GetDebugSymbols().RegisterLocation( txtfile, t.GetBegin() );

 if( known_vars.IsVariable(t) )
  {
   // Особо обрабатываем синтаксис "a = выражение"
   if( txtfile.pick().GetToken()==B_EQUAL )
    {
     // Левая часть должна быть lvalue
     const TrType &vt = known_vars.GetVarType(t);
     if( vt.IsConst() )
      {
       lem::Iridium::Print_Error( t, txtfile );
       pm.GetIO().merr().printf( "[%us] is constant, lvalue is required\n", t.string().c_str() );
       throw E_ParserError();
      }

     txtfile.read();
     TrFunCall *right = CompileCall( pm, txtfile, procs, known_vars );
     txtfile.read_it( B_SEMICOLON );

     TrFun_Assign *f = new TrFun_Assign(t.string(),right);
     f->src_location = src_location;
     return f;
    }
   else
    {
     // В этом контексте имя переменной компилируется как функция, возвращающая ее значение.
     TrFun_Var *f = new TrFun_Var(t);
     f->src_location = src_location;
     return f;
    }
  }

 if( lem::is_int(t) )
  {
   TrIntValue v( lem::to_int(t) );
   TrFun_Constant *f = new TrFun_Constant(v);
   f->src_location = src_location;
   return f;
  }
 
 if( t.length()>2 && t[0]==L'0' && t[1]==L'x' )
  {
   int ival=0;
   if( lem::to_int( t.c_str()+2, &ival, 16 ) )
    {
     TrIntValue v( ival );
     TrFun_Constant *f = new TrFun_Constant(v);
     f->src_location = src_location;
     return f;
    }
  }

 if( t.string()==L'-' && lem::is_int(txtfile.pick()) )
  {
   TrIntValue v( -lem::to_int(txtfile.read().string()) );
   TrFun_Constant *f = new TrFun_Constant(v);
   f->src_location=src_location;
   return f;
  }

 if( t.string().eqi(L"true") || t.string().eqi(L"false") )
  {
   TrBoolValue v( lem::to_bool(t) );
   TrFun_Constant *f = new TrFun_Constant(v);
   f->src_location = src_location;
   return f;
  }

 if( lem::in_apostrophes(t) || lem::in_quotes(t) )
  {
   UCString s=t.string();
   s.strip_quotes();
   s.strip_apostrophes();
   TrValue v( s );
   TrFun_Constant *f = new TrFun_Constant(v);
   f->src_location = src_location;
   return f;
  }

 if( t.GetToken()==B_OSPAREN )
  {
   // Кортеж-константа [ элемент, элемент, ... ]
   // На самом деле мы скомпилируем тут вызов функции tuple_create(...)
   TrFun_BuiltIn *f = new TrFun_BuiltIn;
   f->name = L"tuple_create";

   while( !txtfile.eof() )
    {
     if( txtfile.pick().GetToken()==B_CSPAREN )
      break;

     if( !f->args.empty() )
      txtfile.read_it( B_COMMA );

     TrFunCall *expr = CompileCall( pm, txtfile, procs, known_vars );
     f->args.push_back(expr);
    }

   txtfile.read_it( B_CSPAREN );

   f->src_location = src_location;
   return f;
  }

 SynGram &sg = pm.GetDict().GetSynGram();
 const int icoord = sg.FindCoord(t.string()).GetIndex();
 if( icoord!=UNKNOWN )
  {
   // Комбинацию КООРДИНАТА:СОСТОЯНИЕ компилируем как целочисленный индекс состояния.
   if( txtfile.pick().GetToken()==B_COLON )
    {
     txtfile.read();
     const lem::Iridium::BethToken &state = txtfile.read();
     const int istate = sg.coords()[icoord].FindState(state.string());
     if( istate==UNKNOWN )
      {
       lem::Iridium::Print_Error( state, txtfile );
       pm.GetIO().merr().printf( "Unknown state [%us:%us]\n", t.string().c_str(), state.string().c_str() );
       throw E_ParserError();
      }

     TrIntValue v( istate );
     TrFun_Constant *f = new TrFun_Constant(v);
     f->src_location = src_location;
     return f;
    }
   else
    {
     TrIntValue v( icoord );
     TrFun_Constant *f = new TrFun_Constant(v);
     f->src_location = src_location;
     return f;
    }
  }

 // Имена грамматических классов, координат и состояний компилируются как целочисленные константы.
 const int iclass = sg.FindClass(t.string());
 if( iclass!=UNKNOWN )
  {
   // Особый синтаксис:
   //  класс:статья { координаты }
   // транслируется в вызов функции построения словоформы
   if( txtfile.pick().GetToken()==B_COLON )
    {
     txtfile.seekp(t);
     TrFun_CreateWordform *f = new TrFun_CreateWordform();
     f->CompileDeclaration( pm, txtfile, *this, procs, known_vars, NULL );
     return f; 
    }
   else
    {
     TrIntValue v( iclass );
     TrFun_Constant *f = new TrFun_Constant(v);
     f->src_location = src_location;
     return f;
    } 
  }


 const int ilang = sg.Find_Language(t.string());
 if( ilang!=UNKNOWN )
  {
   TrIntValue v( ilang );
   TrFun_Constant *f = new TrFun_Constant(v);
   f->src_location = src_location;
   return f;
  }

 // Компилируем связки тезауруса в формате:
 // <имя_связки>
 // как целочисленные константы.
 if( t.GetToken()==B_OTRIPAREN )
  {
   txtfile.seekp(t);
   Tree_Link link( txtfile, sg );
   if( !link.Is_Undefined() )
    {
     TrIntValue v( link.GetState() );
     TrFun_Constant *f = new TrFun_Constant(v);
     f->src_location = src_location;
     return f;
    }
   else
    txtfile.seekp(t);
  }

 // Тут мы должны проверить встроенные функции и известные пользовательские функции.
 for( lem::Container::size_type i=0; i<funs.size(); ++i )
  if( funs[i]->GetName().eqi(t.string()) )
   {
    TrFunCall *f = funs[i]->CompileCall( pm, txtfile, *this, procs, known_vars );
    return f;  
   }

 // тут - обработка встроенных функций с особенным синтаксисом вызова.

 if( t.GetToken()==B_OFIGPAREN )
  {
   // Группа функций в {...}
   TrFun_Group *f = new TrFun_Group();
   txtfile.seekp(t);
   f->CompileDeclaration(pm,txtfile,*this,procs,known_vars,NULL);
   return f;
  }

 if( t.eqi( L"return" ) )
  {
   TrFun_Return *f = NULL;
   // Возврат значения функции - транслируем в функцию присваивания значения
   // особой "скрытой" переменной с именем "return"
   if( txtfile.pick().GetToken()==B_SEMICOLON )
    {
     // Возвращаем void.
     TrValue v;
     f = new TrFun_Return( new TrFun_Constant(v) );
     f->src_location = src_location;
    }
   else
    { 
     TrFunCall *right = CompileCall( pm, txtfile, procs, known_vars );
     txtfile.read_it(B_SEMICOLON);
     f = new TrFun_Return(right);
     f->src_location = src_location;
    }

   return f;
  }

 if( t.eqi( L"break" ) )
  {
   // Выход из {} блока
   TrFun_Break *f = new TrFun_Break();
   f->src_location = src_location;
   return f;
  }


 if( t.eqi(L"if") )
  {
   // Условный оператор if(условие) then операторы else операторы
   TrFun_If *f = new TrFun_If();
   f->CompileDeclaration( pm, txtfile, *this, procs, known_vars, NULL );
   return f;
  }

 if( t.eqi(L"while") )
  {
   // Цикл while(условие) оператор
   TrFun_While *f = new TrFun_While();
   f->CompileDeclaration( pm, txtfile, *this, procs, known_vars, NULL );
   return f;
  }

 if( t.eqi(L"for") )
  {
   // Цикл for переменная=нач_значение to кон_значение step шаг оператор
   TrFun_For *f = new TrFun_For();
   f->CompileDeclaration( pm, txtfile, *this, procs, known_vars, NULL );
   return f;
  }

 if( t.eqi(L"lambda" ) )
  {
   // Определение и вызов безымянной функции
   // 
   // lambda тип( формальные_аргументы )
   //
   // lambda(связываемые_локальные_переменные) тип( формальные_аргументы )

   // Сначала загружаем определение функции
   TrFun_Lambda *lambda = CompileLambdaDeclaration( pm, txtfile, procs, known_vars );
   return lambda;
  }

 if( IsType(t) )
  {
   // Функция объявления локальных переменных:
   // тип имя=инициализация, имя, имя ....;
   txtfile.backward();
   TrFun_Declare *f = new TrFun_Declare();
   f->CompileDeclaration( pm, txtfile, *this, procs, known_vars, NULL );
   return f;
  }

 std::map<UCString,TrBuiltInFunSignature>::const_iterator it = builtin.find( to_lower(t.string()) );
 if( it!=builtin.end() )
  {
   txtfile.backward();
   TrFun_BuiltIn *f = new TrFun_BuiltIn();
   f->CompileDeclaration( pm, txtfile, *this, procs, known_vars, &it->second );

   if( t.string().eqi(L"replace") )
    {
     // особенность данной встроенной функции - 2й аргумент должен быть строковой константной,
     // чтобы мы могли сейчас запомнить требование на создание решающего дерева.
     const TrFun_Constant *solver_name = dynamic_cast<const TrFun_Constant*>( f->GetArg(1) );

     if( solver_name==NULL )
      {
       throw E_BaseException( "Invalid invokation of 'replace': second argument must be a constant string" );
      }

     const TrValue &v = solver_name->GetValue();

     const UCString &scenario = v.GetString();
     pm.NeedsReplaceScenario(scenario);
    }

   return f;
  }

 lem::Iridium::Print_Error( t, txtfile );
 pm.GetIO().merr().printf( "Unknown token [%vfE%us%vn]\n", t.c_str() );
 throw E_ParserError();

 return NULL;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
bool TrFunctions::IsType( const UCString &t ) const
{
 return t.eqi(L"const") ||
        t.eqi(L"bool") ||
        t.eqi(L"int") ||
        t.eqi(L"string") ||
        t.eqi(L"tree") ||
        t.eqi(L"trees") ||
        t.eqi(L"variant") ||
        t.eqi(L"fun") ||
        t.eqi(L"tuple");
}
#endif

#if defined SOL_SAVEBIN
void TrFunctions::SaveBin( lem::Stream& bin ) const
{
 funs.SaveBin(bin);
 static_functions.SaveBin(bin);
 return;
}
#endif

#if defined SOL_LOADBIN 
void TrFunctions::LoadBin( lem::Stream& bin )
{
 funs.LoadBin(bin);

 for( lem::Container::size_type i=0; i<funs.size(); ++i )
  {
   TrFunction *fun = funs[i];

   if( !fun->GetName().empty() )
    name2fun.insert( std::make_pair( lem::to_upper(fun->GetName()), fun ) );
  }

 for( lem::Container::size_type i=0; i<funs.size(); ++i )
  {
   TrFunction *fun = funs[i];
   fun->Link( *this );
  }

 static_functions.LoadBin(bin);

 for( lem::Container::size_type i=0; i<static_functions.size(); ++i )
  static_functions[i]->Link( *this );

 return;
}
#endif


const TrFunction* TrFunctions::Find( const lem::UCString &name ) const
{
 lem::UCString uname( lem::to_upper(name) );
 NAME2FUN::const_iterator it = name2fun.find( uname );
 if( it!=name2fun.end() )
  return it->second;

 lem::MemFormatter mem;
 mem.printf( "Can not link to function [%us]", name.c_str() );
 throw lem::E_BaseException(mem.string().c_str());
 return NULL; 
}


bool TrFunctions::IsFunction( const lem::UCString &fun_name ) const
{
 if( builtin.find( to_lower(fun_name) )!=builtin.end() )
  return true;

 if( statements.find( to_lower(fun_name) )!=statements.end() )
  return true;

 lem::UCString uname( lem::to_upper(fun_name) );
 NAME2FUN::const_iterator it = name2fun.find( uname );
 return it!=name2fun.end();
}

int TrFunctions::CountUserFuns(void) const
{
 return CastSizeToInt(funs.size());
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
bool TrFunctions::IsCondictorPointFunction( const lem::UCString &fun ) const
{
 return condictor_point_funs.find( to_lower(fun) )!=condictor_point_funs.end();
}
#endif


#if defined SOL_CAA
void TrFunctions::InitializeStatics(
                                    const ElapsedTimeConstraint & constraints,
                                    PM_Automat &pm,
                                    TrTrace *trace_log
                                   )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs);
 #endif

 if( stat_vars_initialized==0 )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif

   if( stat_vars_initialized==0 )
    {
     stat_vars_initialized = 1;

     // Один раз нужно инициализировать глобальные переменные.
     static_vars = new TrContextInvokation(NULL);
     
     // Инициализация происходит при выполнении инициализаторов
     for( lem::Container::size_type i=0; i<static_functions.size(); ++i )
      {
       static_functions[i]->Run( constraints, pm, *static_vars, trace_log );
      }
    }
  }

 return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
void TrFunctions::CompileStatic(
                                PM_Automat &pm, 
                                lem::Iridium::Macro_Parser &txtfile,
                                const TrProcedureDeclaration &procs
                               )  
{
 static_functions.push_back( CompileCall( pm, txtfile, procs, global_known_vars ) );
 return;
}
#endif


#if defined SOL_COMPILER
void TrFunctions::CompilationFinished(void)
{
 for( lem::Container::size_type i=0; i<funs.size(); ++i )
  funs[i]->RefreshArgumentNames( *this );
 
 return;
}
#endif
