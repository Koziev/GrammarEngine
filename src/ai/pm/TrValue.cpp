#if !defined SOL_NO_AA

// 11.10.2011 - добавлена сериализация в XML

#include <lem/solarix/dictionary.h>
#include <lem/solarix/variator.h>
#include <lem/solarix/translation.h>

using namespace lem;
using namespace Solarix;

TrValue::TrValue(void)
 : type(TrVoidType())
{
 v_fun = NULL;
 v_closure = NULL;
 v_fun_count = v_closure_count = NULL;
 return;
}




TrValue::TrValue( const TrValue &x )
 : type(x.type), v_bool(x.v_bool), v_int(x.v_int), v_string(x.v_string),
   v_tree(x.v_tree), v_trees(x.v_trees), v_tuple(x.v_tuple), v_fun(x.v_fun),
   v_fun_count(x.v_fun_count), v_closure(x.v_closure),
   v_closure_count(x.v_closure_count)
{
 if( v_fun!=NULL )
  (*v_fun_count)++;

 if( v_closure_count!=NULL )
  (*v_closure_count)++;

 return;
}


TrValue::TrValue( const lem::Ptr<TrValue> & x )
 : type(x->type), v_bool(x->v_bool), v_int(x->v_int), v_string(x->v_string),
   v_tree(x->v_tree), v_trees(x->v_trees), v_tuple( x->v_tuple ), v_fun(x->v_fun),
   v_fun_count(x->v_fun_count), v_closure(x->v_closure),
   v_closure_count(x->v_closure_count)
{
 if( v_fun!=NULL )
  (*v_fun_count)++;

 if( v_closure_count!=NULL )
  (*v_closure_count)++;

 return;
}



TrValue::TrValue( const Tree_Node &n )
 : type( TrType::Tree, true )
{
 v_fun = NULL;
 v_closure = NULL;
 v_fun_count = v_closure_count = NULL;
 v_tree = lem::Ptr<Tree_Node>( (Tree_Node*)&n, null_deleter() );
 return;
}

TrValue::TrValue( Tree_Node &n )
 : type( TrType::Tree )
{
 v_fun = NULL;
 v_closure = NULL;
 v_fun_count = v_closure_count = NULL;
 v_tree = lem::Ptr<Tree_Node>( &n, null_deleter() );
 return;
}

TrValue::TrValue( const Variator &v )
 : type( TrType::Trees )
{
 v_fun = NULL;
 v_closure = NULL;
 v_fun_count = v_closure_count = NULL;
 v_trees = lem::Ptr<Variator>( (Variator*)&v, null_deleter() );
 return;
}

TrValue::TrValue( Tree_Node *n, bool do_delete )
 : type( TrType::Tree )
{
 v_fun = NULL;
 v_closure = NULL;
 v_fun_count = v_closure_count = NULL;

 if( do_delete )
  v_tree = lem::Ptr<Tree_Node>( n );
 else
  v_tree = lem::Ptr<Tree_Node>( n, null_deleter() );

 return;
}

TrValue::TrValue( const Tree_Node *n, bool always_false_do_delete )
 : type( TrType::Tree, true )
{
 LEM_CHECKIT_Z( always_false_do_delete==false );
 v_fun = NULL;
 v_closure = NULL;
 v_fun_count = v_closure_count = NULL;
 v_tree = lem::Ptr<Tree_Node>( (Tree_Node*)n, null_deleter() );
 return;
}


TrValue::TrValue( Variator *v, bool do_delete )
 : type( TrType::Trees )
{
 v_fun = NULL;
 v_closure = NULL;
 v_fun_count = v_closure_count = NULL;
 if( do_delete )
  v_trees = lem::Ptr<Variator>( v );
 else
  v_trees = lem::Ptr<Variator>( v, null_deleter() );

 return;
}


TrValue::TrValue( TrTuple *v, bool do_delete )
 : type( TrType::Tuple )
{
 v_fun = NULL;
 v_closure = NULL;
 v_fun_count = v_closure_count = NULL;
 if( do_delete )
  v_tuple = lem::Ptr<TrTuple>( v );
 else
  v_tuple = lem::Ptr<TrTuple>( v, null_deleter() );

 return;
}





TrValue::TrValue( const lem::UCString & v )
 : type( TrType::String )
{
 v_fun = NULL;
 v_closure = NULL;
 v_fun_count = v_closure_count = NULL;
 v_string = new UCString(v);
 return;
}

TrValue::TrValue( const wchar_t * v )
 : type( TrType::String )
{
 v_fun = NULL;
 v_closure = NULL;
 v_fun_count = v_closure_count = NULL;
 v_string = new UCString(v);
 return;
}



TrValue::TrValue( const TrFunCall *v, TrClosureVars *closure_vars )
 : type( TrType::Fun )
{
 v_fun = (TrFunCall*)v;
 v_closure = closure_vars;
 v_fun_count = new int(2);
 v_closure_count = new int(1);
 return;
}

void TrValue::operator=( const TrValue &x )
{
 type = x.type;
 v_bool = x.v_bool;
 v_int = x.v_int;
 v_string = x.v_string;
 v_tree = x.v_tree;
 v_trees = x.v_trees;
 v_tuple = x.v_tuple;

 v_fun = x.v_fun;
 v_fun_count = x.v_fun_count;
 v_closure = x.v_closure;


 if( v_fun!=NULL )
  (*v_fun_count)++;

 if( v_closure_count!=NULL )
  (*v_closure_count)++;

 return;
}


TrValue::~TrValue(void)
{
 if( v_fun!=NULL )
  {
   (*v_fun_count) --;
   if( (*v_fun_count)==0 )
    {
     delete v_fun_count;
     delete v_fun;
    }

   (*v_closure_count) --;
   if( (*v_closure_count)==0 )
    {
     delete v_closure_count;
     delete v_closure;
    }
  }

 v_fun_count = v_fun_count = NULL;
 v_closure = NULL;
 v_fun = NULL;

 return;
}

bool TrValue::IsNull(void) const
{
 switch(type.type)
 {
  case TrType::Bool: return v_bool.IsNull();
  case TrType::Int: return v_int.IsNull();
  case TrType::String: return v_string.IsNull();
  case TrType::Tree: return v_tree.IsNull();
  case TrType::Trees: return v_trees.IsNull();
  case TrType::Void: return false;
  case TrType::Fun:
   {
    /*v_fun->SaveBin(bin);*/
    LEM_STOPIT;
    break;
   }

  case TrType::Tuple: return v_tuple.IsNull();
  case TrType::Variant: LEM_STOPIT;
  default: LEM_STOPIT;
 }

 return false;
}



#if defined SOL_SAVEBIN
void TrValue::SaveBin( lem::Stream& bin ) const
{
 bin.write( &type, sizeof(type) );
 switch(type.type)
 {
  case TrType::Bool: bin.write( &*v_bool, sizeof(*v_bool) ); break;
  case TrType::Int: bin.write( &*v_int, sizeof(*v_int) ); break;
  case TrType::String: bin.write( &*v_string, sizeof(*v_string) ); break;
  case TrType::Tree: v_tree->SaveBin(bin); break;
  case TrType::Trees: v_trees->SaveBin(bin); break;
  case TrType::Void: break;
  case TrType::Fun:
   {
    /*v_fun->SaveBin(bin);*/
    LEM_STOPIT;
    break;
   }

  case TrType::Tuple: v_tuple->SaveBin(bin); break;
 }
 
 return;
}
#endif

#if defined SOL_LOADBIN 
void TrValue::LoadBin( lem::Stream& bin )
{
 bin.read( &type, sizeof(type) );
 switch(type.GetType())
 {
  case TrType::Bool: v_bool = new bool( bin.read_bool() ); break;
  case TrType::Int: v_int = new int( bin.read_int() ); break;
  case TrType::String:
   {
    UCString s;
    bin.read( &s, sizeof(s) );
    v_string = new UCString(s);
    break;
   }

  case TrType::Tree: v_tree = new Tree_Node(bin); break;
  case TrType::Trees: v_trees = new Variator(bin); break;
  case TrType::Void: break;
  case TrType::Tuple:
   {
    v_tuple = new TrTuple;
    v_tuple->LoadBin(bin);
    break;
   }

  case TrType::Fun:
   {
//    v_fun = TrFunCall::load_bin(bin);
//    v_fun_count = new int(1);
    LEM_STOPIT;
    break;
   }

  default: LEM_STOPIT;
 }
 
 return;
}

void TrValue::Link( const TrFunctions &funs )
{
 #if defined SOL_CAA && !defined SOL_NO_AA
// if( v_fun!=NULL )
//  v_fun->Link(funs);

// if( v_closure!=NULL )
//  v_closure->Link(funs);

 if( v_tuple.NotNull() )
  v_tuple->Link(funs);
   
 #endif

 return;
}
#endif


#if defined SOL_COMPILER
void TrValue::RefreshArgumentNames( const TrFunctions &declarations )
{
 #if defined SOL_CAA && !defined SOL_NO_AA
 if( v_tuple.NotNull() )
  v_tuple->RefreshArgumentNames(funs);
 #endif
 return;
}

#endif


void TrValue::Assign( TrValue &v )
{
 if( type.type!=v.type.type && !type.IsVariant() )
  {
   UFString msg = format_str( L"Run-time error: can not assign to lvalue because of different types, left is '%s', right is '%s'",
    type.GetName().c_str(), v.type.GetName().c_str() );
   throw E_BaseException( msg );
  }

 type = v.type;

 switch(type.GetType())
 {
  case TrType::Bool: v_bool = v.v_bool; break;
  case TrType::Int: v_int = v.v_int; break;
  case TrType::String: v_string = v.v_string; break;
  case TrType::Tree: v_tree = v.v_tree; break;
  case TrType::Trees: v_trees = v.v_trees; break;
  case TrType::Void:
   {
    v_fun = v.v_fun;
    v_closure = v.v_closure;
    v_closure_count = v.v_closure_count;
    v_fun_count = v.v_fun_count;
    if( v_fun!=NULL )
     (*v_fun_count)++;

    if( v_closure_count!=NULL )
     (*v_closure_count)++;

    break;
   }

  case TrType::Tuple: v_tuple = v.v_tuple; break;

  default: LEM_STOPIT;
 }
 
 return;
}




void TrValue::Copy( const TrValue &v )
{
 if( type.type!=v.type.type && !type.IsVariant() )
  {
   throw E_BaseException( L"Run-time error: can not assign to lvalue because of different types" );
  }

 type = v.type;

 switch(type.GetType())
 {
  case TrType::Bool: v_bool = new bool( *v.v_bool ); break;
  case TrType::Int: v_int = new int( *v.v_int ); break;
  case TrType::String: v_string = new UCString(*v.v_string); break;

  case TrType::Tree:
  {
   v_tree = v.v_tree->DeepCopy();
   break;
  }

  case TrType::Trees:
  {
   v_trees = v.v_trees->DeepCopy();
   break;
  }

  case TrType::Fun:
   {
    v_fun = v.v_fun;
    v_closure = v.v_closure;
    v_closure_count = v.v_closure_count;
    v_fun_count = v.v_fun_count;
    if( v_fun!=NULL )
     (*v_fun_count)++;

    if( v_closure_count!=NULL )
     (*v_closure_count)++;

    break;
   }

  case TrType::Tuple: v_tuple = new TrTuple(*v.v_tuple); break;
  case TrType::Void: break;

  default: LEM_STOPIT;
 }
 
 return;
}

bool TrValue::eq( const lem::Ptr<TrValue> &x ) const
{
 return eq( *x );
}

bool TrValue::eq( const TrValue &x ) const
{
 if( type.type==x.type.type )
  {
   switch(type.GetType())
   {
    case TrType::Bool: return *v_bool == *x.v_bool;
    case TrType::Int: return *v_int == *x.v_int;
    case TrType::String: return *v_string == *x.v_string;

    case TrType::Tree:
     return &*v_tree == &*x.v_tree || *v_tree == *x.v_tree;

    case TrType::Trees:
     return &*v_trees==&*x.v_trees || *v_trees == *x.v_trees;

    case TrType::Void: return true;
    case TrType::Fun: return false;
    case TrType::Tuple:
     return &*v_tuple==&*x.v_tuple || *v_tuple == *x.v_tuple;

    default: LEM_STOPIT;
   }
  }
 else if( type.IsString() && x.type.IsTree() )
  {
   return *(x.v_tree->GetNode().GetName()) == *v_string;
  }
 else if( x.type.IsString() && type.IsTree() )
  {
   return *(v_tree->GetNode().GetName()) == *x.v_string;
  }
 else
  {
   UFString msg = format_str( L"Can not compare '%s' and '%s'", type.GetName().c_str(), x.type.GetName().c_str() ); 
   throw E_BaseException(msg);
  }

 return false;
}


bool TrValue::eqi( const lem::Ptr<TrValue> &x ) const
{
 return eqi( *x );
}

bool TrValue::eqi( const TrValue &x ) const
{
 LEM_CHECKIT_Z( type.type==x.type.type );

 if( type.type==x.type.type )
  {
   switch(type.GetType())
   {
    case TrType::String: return v_string->eqi(*x.v_string);
    default: LEM_STOPIT;
   }
  }
 else if( type.IsString() && x.type.IsTree() )
  {
   return (x.v_tree->GetNode().GetName())->eqi(*v_string);
  }
 else if( x.type.IsString() && type.IsTree() )
  {
   return (v_tree->GetNode().GetName())->eqi( *x.v_string );
  }
 else
  {
   UFString msg = format_str( L"Can not apply 'eqi' to '%s' and '%s'", type.GetName().c_str(), x.type.GetName().c_str() ); 
   throw E_BaseException(msg);
  }

 return false;
}


void TrValue::Print( const Solarix::Dictionary &dict, lem::OFormatter &out, const TrValuePrinterDecorator *decorator ) const
{
 #if defined SOL_CAA
 switch(type.GetType())
 {
  case TrType::Bool: out.printf( "%b", *v_bool ); break;
  case TrType::Int: out.printf( "%d", *v_int ); break;

  case TrType::String:
   {
    if( decorator==NULL )
     out.printf( "%us", v_string->c_str() );
    else
     decorator->PrintString( v_string->c_str(), out );

    break;
   }

  case TrType::Tree: v_tree->Print( out, dict.GetSynGram() ); break;
  case TrType::Trees:
   {
    if( v_trees->size()==1 )
     v_trees->PrintV( out, dict.GetSynGram(), true );
    else
     {
      // Вариатор слишком длинный и не влезет на 1 строку.
      out.printf( "%vf6...see below...%vn\n" );
      v_trees->PrintV( out, dict.GetSynGram(), true );
     }

    break;
   }
  case TrType::Void: out.printf( "%vf6void%vn" ); break;
  case TrType::Fun: out.printf( "%vf6fun*%vn" ); break;
  case TrType::Tuple: v_tuple->Print( dict, out, decorator ); break;
  case TrType::Variant: out.printf( "%vf6((undefined-variant))%vn" ); break;
  default: LEM_STOPIT;
 }
 #endif

 return;
}


void TrValue::PrintXML( lem::OFormatter &xml, const Solarix::Dictionary &dict ) const
{
 switch(type.GetType())
 {
  case TrType::Bool:
  {
   xml.printf( "<value type=\"bool\">%b</value>\n", *v_bool );
   break;
  }

  case TrType::Int:
  {
   xml.printf( "<value type=\"int\">%d</value>\n", *v_int );
   break;
  }

  case TrType::String:
  {
   xml.printf( "<value type=\"string\">" );
   xml.printf( "%us", lem::encode_chars_to_xml(v_string->c_str()).c_str() );
   xml.printf( "</value>\n" );
   break;
  }

  case TrType::Tree:
  {
   xml.printf( "<value type=\"tree\">" );
   v_tree->PrintXML( xml, dict.GetSynGram() );
   xml.printf( "</value>\n" );
   break;
  }

  case TrType::Trees:
  {
   xml.printf( "<value type=\"trees\">" );
   v_trees->PrintXML( xml, dict.GetSynGram() );
   xml.printf( "</value>\n" );
   break;
  }

  case TrType::Void:
  {
   xml.printf( "<value type=\"void\"/>" );
   break;
  }

  case TrType::Fun:
  {
   xml.printf( "<value type=\"fun\"/>" );
   break;
  }


  case TrType::Tuple:
  {
   xml.printf( "<value type=\"tuple\">" );
   v_tuple->PrintXML( xml, dict );
   xml.printf( "</value>\n" );
   break;
  }

  case TrType::Variant:
  {
   xml.printf( "<value type=\"variant\"/>" );
   break;
  }

  default: LEM_STOPIT;
 }

 return;
}




bool TrValue::GetBool(void) const
{
 if( !type.IsBool() )
  {
   UFString msg = format_str( L"Can not cast '%s' to 'bool'", type.GetName().c_str() );
   throw E_BaseException(msg);
  }

 return *v_bool;
}

int TrValue::GetInt(void) const
{
 if( !type.IsInt() )
  {
   UFString msg = format_str( L"Can not cast '%s' to 'int'", type.GetName().c_str() );
   throw E_BaseException(msg);
  }

 return *v_int;
}

const lem::UCString& TrValue::GetString(void) const
{
 if( !type.IsString() )
  {
   UFString msg = format_str( L"Can not cast '%s' to 'string'", type.GetName().c_str() );
   throw E_BaseException(msg);
  }

 return *v_string;
}

const Solarix::Tree_Node& TrValue::GetTree(void) const
{
 if( !type.IsTree() )
  {
   UFString msg = format_str( L"Can not cast '%s' to 'tree'", type.GetName().c_str() );
   throw E_BaseException(msg);
  }

 return *v_tree;
}

Solarix::Tree_Node& TrValue::GetTree(void)
{
 if( !type.IsTree() )
  {
   UFString msg = format_str( L"Can not cast '%s' to 'tree'", type.GetName().c_str() );
   throw E_BaseException(msg);
  }

 return *v_tree;
}

const Solarix::Variator& TrValue::GetTrees(void) const
{
 if( !type.IsTrees() )
  {
   UFString msg = format_str( L"Can not cast '%s' to 'trees'", type.GetName().c_str() );
   throw E_BaseException(msg);
  }

 return *v_trees;
}

Solarix::Variator& TrValue::GetTrees(void)
{
 if( !type.IsTrees() )
  {
   UFString msg = format_str( L"Can not cast '%s' to 'trees'", type.GetName().c_str() );
   throw E_BaseException(msg);
  }

 return *v_trees;
}

const TrTuple& TrValue::GetTuple(void) const
{
 if( !type.IsTuple() )
  {
   UFString msg = format_str( L"Can not cast '%s' to 'tuple'", type.GetName().c_str() );
   throw E_BaseException(msg);
  }

 return *v_tuple;
}

TrTuple& TrValue::GetTuple(void)
{
 if( !type.IsTuple() )
  {
   UFString msg = format_str( L"Can not cast '%s' to 'tuple'", type.GetName().c_str() );
   throw E_BaseException(msg);
  }

 return *v_tuple;
}

const TrFunCall & TrValue::GetFun(void) const
{
 if( !type.IsFun() )
  {
   UFString msg = format_str( L"Can not cast '%s' to 'fun'", type.GetName().c_str() );
   throw E_BaseException(msg);
  }

 return *v_fun;
}

const TrClosureVars * TrValue::GetClosureVars(void) const
{
 if( !type.IsFun() )
  {
   UFString msg = format_str( L"Can not cast '%s' to 'fun'", type.GetName().c_str() );
   throw E_BaseException(msg);
  }

 return v_closure;
} 



TrBoolValue::TrBoolValue( bool v )
{
 type = TrType(TrType::Bool);
 v_fun = NULL;
 v_closure = NULL;
 v_fun_count = v_closure_count = NULL;
 v_bool = new bool(v);
 return;
}

TrIntValue::TrIntValue( int v )
{
 type = TrType(TrType::Int);
 v_fun = NULL;
 v_closure = NULL;
 v_fun_count = v_closure_count = NULL;
 v_int = new int(v);
 return;
}


TrTypeValue::TrTypeValue( const TrType &t )
{
 type = t;
 v_fun = NULL;
 v_closure = NULL;
 v_fun_count = v_closure_count = NULL;

 switch(type.GetType())
 {
  case TrType::Bool: v_bool = new bool(false); break;
  case TrType::Int: v_int = new int(0); break;
  case TrType::String:
   {
    v_string = new UCString();
    break;
   }

  case TrType::Tree: v_tree = new Tree_Node; break;
  case TrType::Trees: v_trees = new Variator; break;
  case TrType::Void: break;

  #if defined SOL_CAA && !defined SOL_NO_AA
  case TrType::Fun: 
   {
    v_fun = NULL;
    v_closure = NULL;
    v_fun_count = new int(0);
    v_closure_count = new int(0);
    break;
   }
  #endif

  case TrType::Tuple: v_tuple = new TrTuple; break; 

  case TrType::Variant: break;

  default: LEM_STOPIT;
 }

 return; 
}


#endif
