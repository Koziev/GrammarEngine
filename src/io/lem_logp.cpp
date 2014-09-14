// -----------------------------------------------------------------------------
// File LEM_LOGP.CPP
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
// CD->22.06.1996
// LC->28.05.2006
// --------------

#include <lem/oformatter.h>
#include <lem/lexers.h>
#include <lem/conversions.h>
#include <lem/lem_logp.h>

using namespace lem;
using namespace std;

BoolTree::BoolTree( const string& s )
{
 affirmative=true;
 if( !to_bool(s.c_str(),&val) )
  {
   if( is_name(s.c_str()) )
    {
     type = VARNAME;
     varname = s;
    }
   else
    throw ECheckFault(
                      (
                       to_wstr( "Incorrect token in logical tree: " ) +
                       to_wstr( s.c_str() )
                      ).c_str()
                     );
  }
 else
  type = VALUE;

 return;
}

BoolTree::BoolTree( Text_Parser &txtfile )
{
 affirmative=true;
 vector<char>    operation;
 vector<BoolTree*> operand;

 AToken t;
 operation.push_back( ' ' );
 while(!txtfile.eof())
  {
   bool loading_var = true;
   bool affirmative=true;

   while( loading_var )
    {
     t=txtfile.read();
     switch( t.string()[0] )
      {
       case '(':
        {
         BoolTree *child = new BoolTree(txtfile);
         child->set(affirmative);
         operand.push_back(child);
         loading_var=false;
         break;
        }

       case '~':
        {
         affirmative = !affirmative;
         break;
        }

       default:
        {
         BoolTree *child = new BoolTree(t.c_str());
         child->set(affirmative);
         operand.push_back(child);
         loading_var=false;
         break;
        }
      }
    }

   // —читываем код операции
   t = txtfile.read();

   if( t.string()==')' )
    break;

   if( t.string()==';' ) //  онец выражени€
    break;

   operation.push_back(char(t.string()[0]));
  }

 // “еперь собираем подузлы. —начала соберем все AND-выражени€, так
 // как они имеют больший приоритет.
 type = OR;
 vector<BoolTree> resline;
 for( int i=0; i<operand.size(); )
  {
   BoolTree built;
   built.and.push_back( new BoolTree( *operand[i] ) );
   built.type=AND;

   int j=0;
   for( j=i+1; j<operand.size(); j++ )
    if( operation[j]=='&' )
     built.and.push_back( new BoolTree(*operand[j]) );
    else
     break;

   or.push_back( new BoolTree(built) );
   i=j;
  }

 ZAP_A(operand);

 return;
}


BoolTree::BoolTree( const BoolTree& lt )
{ Init(lt); }

BoolTree::~BoolTree(void)
{ Delete(); }

BoolTree& BoolTree::operator=( const BoolTree& lt )
{
 Delete();
 Init(lt);
 return *this;
}

void BoolTree::Delete()
{
 type = EMPTY;
 val = false;
 varname="";

 for( int i=0; i<or.size(); i++ )
  delete or[i];

 or.clear();

 for( int i=0; i<and.size(); i++ )
  delete and[i];

 and.clear();
 return;
}

void BoolTree::Init( const BoolTree& lt )
{
 type    = lt.type;
 varname = lt.varname;
 val     = lt.val;
 affirmative = lt.affirmative;

 for( int i=0; i<lt.or.size(); i++ )
  or.push_back(new BoolTree(*lt.or[i]));

 for( int i=0; i<lt.and.size(); i++ )
  and.push_back( new BoolTree(*lt.and[i]) );

 return;
}

bool BoolTree::compute( const vector<BoolVar>& vars ) const
{
 switch(type)
  {
   case VALUE: return affirmative ? val : !val;

   case VARNAME:
    {
     for( int i=0; i<vars.size(); i++ )
      if( vars[i].GetName()==varname )
       return affirmative ? vars[i].GetVal() : !vars[i].GetVal();

     throw ECheckFault(
                       (
                        to_wstr( "Variable noy found: " ) +
                        to_wstr( varname.c_str() )
                       ).c_str()
                      );
    }

   case OR:
    {
     for( int i=0; i<or.size(); i++ )
      if( or[i]->compute(vars) )
       return affirmative;

     return !affirmative;
    }

   case AND:
    {
     for( int i=0; i<and.size(); i++ )
      if( !and[i]->compute(vars) )
       return !affirmative;

     return affirmative;
    }

   default: LEM_STOPIT;
  }

 return false;
}

void BoolCompiler::Execute( Text_Parser& txtfile )
{
 while(!txtfile.eof())
  {
   AToken t = txtfile.read();

   if( t.string().empty() )
    break;

   if( t.string()=="bool" )
    {
     AToken varname = txtfile.read();
     txtfile.read_it("=");
     bool val = compute(txtfile);

     for( int i=0; i<var_list.size(); i++ )
      if( var_list[i].GetName() == varname.c_str() )
       {
        throw ECheckFault(
                          (
                           to_wstr( "Variable redefinition: " ) +
                           to_wstr( varname.c_str() )
                          ).c_str()
                         );
       }

     var_list.push_back( BoolVar(varname.c_str(),val) );
    }
  }

 return;
}

bool BoolCompiler::compute( Text_Parser& txtfile ) const
{
 BoolTree root(txtfile);
 return root.compute(var_list);
}

// -------------------------- End Of File [LEM_LOGP.CPP] -----------------------
