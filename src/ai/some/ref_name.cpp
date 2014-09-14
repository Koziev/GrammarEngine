// -----------------------------------------------------------------------------
// File REF_NAME.CPP
//
// (c) Koziev Elijah
//
// Content:
// ѕроцедуры дл€ работы со ссылочными именами.
// -----------------------------------------------------------------------------
//
// CD->07.10.1995
// LC->03.04.2009
// --------------

#include <lem/conversions.h>
#include <lem/macro_parser.h>

#include <lem/solarix/dictionary.h>
#include <lem/solarix/ref_name.h>

using namespace lem;
using namespace Solarix;

/****************************************************************
 Test if the lexem s can be a reference name.
*****************************************************************/
bool Solarix::sol_is_it_ref_name( const UCString &s )
{
 return is_ualpha(s[0]);
}

#if defined SOL_LOADTXT
// **********************************************************************
// ѕровер€ем правильность задани€ ссимени. ѕечатаем сообщение об ошибке
// с указанием места в файле в случае нарушени€ соглашени€ о ссылочных
// именах.
// **********************************************************************
void Solarix::sol_check_ref_name(
                                 const Sol_IO &io,
                                 Macro_Parser& txtfile,
                                 const BethToken& s
                                )
{
 if( !sol_is_it_ref_name(s.string()) )
  {
   lem::Iridium::Print_Error(s,txtfile);
   io.merr().printf("Incorrect reference name\n");
   LEM_STOPIT;
  }

 return;
}
#endif

#if defined SOL_LOADTXT
int Solarix::sol_check_index(
                             const Sol_IO &io,
                             Macro_Parser& txtfile,
                             const BethToken& s
                            )
{
 int dummy;

 if(
    !to_int( s.string().c_str(), &dummy ) ||
    dummy<0 ||
    dummy>=30
   )
  {
   lem::Iridium::Print_Error(s,txtfile);
   io.merr().printf("Incorrect index\n");
   LEM_STOPIT;
  }

 return dummy;
}
#endif

/***********************************************************************
 —троковое представление ссылочного имени s преобразуем в целое число,
 которое может хранить либо индекс, либо символическое им€.
************************************************************************/
int Solarix::sol_str_to_ref_name( const UCString &s )
{
 int dummy;

 if( to_int( s.c_str(), &dummy ) )
  return dummy;

 LEM_CHECKIT_Z( sol_is_it_ref_name(s) );
 return sol_ref_name_to_index(s[0]);
}

/************************************************************************
 —сылочное им€ (индекс или символич. им€) преобразует в текстовую строку
 дл€ печати.
*************************************************************************/
const UCString Solarix::sol_ref_name_to_str( int refname )
{
 if( sol_is_index(refname) )
  return to_ustr(refname);

 return UCString( sol_index_to_ref_name(refname) );
}

