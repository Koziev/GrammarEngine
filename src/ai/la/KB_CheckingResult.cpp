#include <lem/solarix/KnowledgeBase.h>

using namespace Solarix;


KB_CheckingResult::KB_CheckingResult(void)
 : type(UNKNOWN), retbool(UNKNOWN), false_score(0), retint(UNKNOWN)
{
}

int KB_CheckingResult::GetBool(void) const
{
 if( type!=0 )
  throw lem::E_BaseException( "Can not convert KB_CheckingResult object to bool" );

 return retbool;
}



int KB_CheckingResult::GetInt(void) const
{
 if( type!=1 )
  throw lem::E_BaseException( "Can not convert KB_CheckingResult object to int" );

 return retint;
}


KB_BoolResult::KB_BoolResult( int bool_val, int false_fine )
 : KB_CheckingResult()
{
 type=0;
 retbool=bool_val;
 false_score = false_fine;
}


KB_IntResult::KB_IntResult( int int_val )
 : KB_CheckingResult()
{
 type=1;
 retint=int_val;
}


KB_NotMatchedResult::KB_NotMatchedResult(void)
 : KB_CheckingResult()
{
 type=UNKNOWN; 
}

