#if !defined VariableChecker__H
#define VariableChecker__H

namespace Solarix
{
 #if defined SOL_LOADTXT && defined SOL_COMPILER
 class VariableChecker : lem::NonCopyable
 {
  protected:
   VariableChecker() {}

  public:
   virtual int Find( const lem::UCString & var_name ) const=0;
 };
 #endif
}

#endif
