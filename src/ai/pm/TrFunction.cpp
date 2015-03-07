#include <lem/solarix/tokens.h>
#include <lem/solarix/pm_autom.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/tr_funs.h>

using namespace lem;
using namespace Solarix;


#if defined SOL_LOADTXT && defined SOL_COMPILER
void TrFunction::CompileDeclaration(
                                    PM_Automat &pm,
                                    lem::Iridium::Macro_Parser &txtfile,
                                    TrFunctions &functions,
                                    const TrKnownVars *lambda_caller
                                   )
{
 const bool is_lambda = lambda_caller!=NULL;

 lem::Iridium::BSourceState fun_beg = txtfile.tellp();

 ret_type.LoadTxt( pm, txtfile, functions );

 lem::Iridium::BSourceState ss = txtfile.tellp();

 try
  {
   if( is_lambda )
    {
     // Формируем "невозможное" имя лямбда-функции, которое наверняка не будет
     // пересекаться с пользовательскими и встроенными функциями.
     static int lambda_number=0;
     name = L" $lambda";
     name += to_ustr(lambda_number++);
    }
   else
    {
     name = txtfile.read();
    }

   if( pm.GetDict().GetDebugLevel_ir()>=3 )
    {
     // Печатаем имя транслируемой статьи для контроля за процессом
     // парсинга Словаря.
     pm.GetDict().GetIO().mecho().printf( "function [%vfA%us%vn]->", name.c_str() );
    }

   if( !is_lambda && !CorrectName(name) )
    {
     lem::Iridium::Print_Error( ss, txtfile );
     pm.GetIO().merr().printf( "Invalid function name [%us]\n", name.c_str() );
     throw E_ParserError();
    }

   txtfile.read_it( B_OROUNDPAREN );

   TrKnownVars call_vars( lambda_caller==NULL ? &functions.global_known_vars : lambda_caller );

   // Список формальных аргументов
   while( !txtfile.eof() )
    {
     if( txtfile.pick().GetToken()==B_CROUNDPAREN )
      break;

     if( arg_name.size()>0 )
      txtfile.read_it(B_COMMA);

     TrType at;
     at.LoadTxt(pm,txtfile,functions);

     const lem::Iridium::BethToken &an = txtfile.read();

     if( arg_name.find(an)!=UNKNOWN )
      {
       lem::Iridium::Print_Error( an, txtfile );
       pm.GetIO().merr().printf( "Function [%us] call argument [%us] is already declared\n", name.c_str(), an.string().c_str() );
       throw E_ParserError();
      }
  
     arg_type.push_back(at);
     arg_name.push_back(an.string());

     call_vars.RegisterVar( at, an.string() );
    }

   txtfile.read_it( B_CROUNDPAREN );

   if( txtfile.pick().GetToken()==B_SEMICOLON )
    {
     txtfile.read();
     // Это форвардное объявление функции, без определения тела.
    }
   else
    {
     // Чтобы компилировать рекурсивные функции, мы сейчас добавим в список функций свое форвардное объявление.
     if( !is_lambda && !functions.IsFunction(name) )
      {
       TrFunction *forward = MakeForwardDeclaration();
       functions.AddForwardDeclaration(forward);
      }    

     // В фигурных скобочках - тело функции. Оно компилируется как вызов специальной функции-группы {}
     txtfile.read_it( B_OFIGPAREN );
     txtfile.backward();
     body = functions.CompileCall( pm, txtfile, call_vars );
    }

   if( pm.GetDict().GetDebugLevel_ir()>=3 )
    pm.GetIO().mecho().printf( "%vfAOK%vn\n" );
  }
 catch(...)
  {
   lem::Iridium::Print_Error( ss, txtfile );
   pm.GetIO().merr().printf( "Error in function [%us] definition\n", name.c_str() );
   throw;
  }

 return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
bool TrFunction::CorrectName( const UCString &x )
{
 return lem::is_name(x.c_str());
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
TrFunCall* TrFunction::CompileCall(
                                   PM_Automat &pm,
                                   lem::Iridium::Macro_Parser &txtfile, 
                                   TrFunctions &functions,
                                   TrKnownVars &known_vars
                                  )
{
 // Компилируем ВЫЗОВ функции;
 // Имя функции уже прочитано, нам надо загрузить список формальных аргументов в круглых скобочках
 // и оформить вызов.

 TrFun_User *fun = new TrFun_User;
 fun->name = name;
 fun->ret_type = ret_type;

 txtfile.read_it( B_OROUNDPAREN );

 int iarg=0;
 int narg=0;
 while( !txtfile.eof() )
  {
   if( txtfile.pick().GetToken()==B_CROUNDPAREN )
    {
     if( narg!=CastSizeToInt(arg_name.size()) )
      { 
       lem::Iridium::Print_Error( txtfile );
       pm.GetIO().merr().printf( "Invalid number of arguments in function [%us] call, got %d, must be %d\n", name.c_str(), narg, CastSizeToInt(arg_name.size()) );
       throw E_ParserError();  
      }

     break;
    }

   if( narg>=CastSizeToInt(arg_name.size()) )
    {
     lem::Iridium::Print_Error( txtfile );
     pm.GetIO().merr().printf( "Invalid number of arguments in function [%us] call, got %d, must be %d\n", name.c_str(), narg+1, CastSizeToInt(arg_name.size()) );
     throw E_ParserError();  
    }

   if( iarg>0 )
    txtfile.read_it( B_COMMA );

   TrFunCall *arg_expr = functions.CompileCall(pm,txtfile,known_vars);
   fun->arg_name.push_back( arg_name[iarg] );
   fun->arg_expr.push_back( arg_expr );
   iarg++;
   narg++;
  }
 
 txtfile.read_it( B_CROUNDPAREN );

 return fun;
}
#endif


#if defined SOL_SAVEBIN
void TrFunction::SaveBin( lem::Stream& bin ) const
{
 bin.write( &name, sizeof(name) );
 ret_type.SaveBin(bin);

 arg_name.SaveBin(bin);
 arg_type.SaveBin(bin);

 bin.write_bool( body.NotNull() );
 if( body.NotNull() )
  body->SaveBin(bin);
 return;
}
#endif

#if defined SOL_LOADBIN 
void TrFunction::LoadBin( lem::Stream& bin )
{
 bin.read( &name, sizeof(name) );
 ret_type.LoadBin(bin);

 arg_name.LoadBin(bin);
 arg_type.LoadBin(bin);

 if( bin.read_bool() )
  body = TrFunCall::load_bin(bin);

 return;
}

void TrFunction::Link( const TrFunctions &funs )
{
 if( body.NotNull() )
  body->Link(funs);

 return;
}
#endif



TrFunction* TrFunction::MakeForwardDeclaration(void) const
{
 TrFunction *f = new TrFunction;
 f->name = name;
 f->arg_name = arg_name;
 f->arg_type = arg_type;
 f->ret_type = ret_type;
 return f;
}


#if LEM_DEBUGGING==1
void TrFunction::PrintSignature( lem::OFormatter &out ) const
{
 out.printf( "function %vfE%us%vn( ", name.c_str() );

 for( lem::Container::size_type i=0; i<arg_name.size(); ++i )
  {
   if( i>0 )
    out.printf( ", " );
   out.printf( "%us %us", arg_type[i].GetName().c_str(), arg_name[i].c_str() );
  }

 out.printf( ")" );

 return;
}
#endif

#if defined SOL_COMPILER
void TrFunction::RefreshArgumentNames( const TrFunctions &declarations )
{
 body->RefreshArgumentNames(declarations);
 return;
}
#endif
