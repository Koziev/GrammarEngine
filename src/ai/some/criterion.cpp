// -----------------------------------------------------------------------------
// File CRITERION.CPP
//
// (c) Koziev Elijah
//
// Content:
// Класс Criterion - хранение числового именованного параметра. Параметры
// (или критерии) используются в автоматах для тонкого регулирования некоторых
// эвристических алгоритмов, когда априори не удается придумать однозначное
// значение некоторого фактора. Параметры считываются Автоматами из своих секций
// в текстовом файле Словаря.
// -----------------------------------------------------------------------------
//
// CD->24.03.1997
// LC->04.01.2011
// --------------

#include <lem/conversions.h>
#include <lem/macro_parser.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/criterion.h>

using namespace lem;
using namespace Solarix;
using namespace lem::Iridium;


Criterion::Criterion(void)
{}

Criterion::Criterion( const Criterion &c )
{
 rval = c.rval;
 name = c.name;
 str = c.str;
 return;
}

#if defined SOL_LOADTXT
Criterion::Criterion( const Sol_IO &dict, Macro_Parser &txtfile )
{ LoadTxt(dict,txtfile); }
#endif

void Criterion::operator=( const Criterion &c )
{
 rval = c.rval;
 name = c.name;
 str = c.str;
 return;
}

Criterion::Criterion( const lem::UCString &_name, const lem::UFString &_str )
 : name(_name), str(_str)
{
 if( lem::is_real(str.c_str()) )
  {
   lem::Math::REAL dval;
   to_real( str.c_str(), &dval );
   rval = dval;
  }
 
 return;
}


#if defined SOL_LOADTXT
/********************************************************************
 Считывание описания критерия из текстового файла. Возможные форматы:

 1. criterion имя = целое_число
 2. criterion имя = "дробное_число"

 Следует заметить, что допустимы дробные числа от +0.00 до +1.00.
*********************************************************************/
void Criterion::LoadTxt( const Sol_IO &io, Macro_Parser &txtfile )
{
 name = txtfile.read().string(); // Условное имя критерия.

 // После знака равенства идет численное значение.
 txtfile.read_it(B_EQUAL);
 const BethToken val = txtfile.read();
 str = val.GetFullStr();
 str.strip_quotes().strip_apostrophes();

 if( lem::is_real(str.c_str()) )
  {
   lem::Math::REAL dval;
   to_real( val.c_str(), &dval );
   rval = dval;
  }

 return;
}
#endif


int Criterion::GetInt(void) const
{
 if( rval.IsNull() )
  {
   lem::MemFormatter mem;
   mem.printf( "Can not convert the string %us to number when accessing the criterion [%us]", str.c_str(), name.c_str() );
   throw lem::E_BaseException(mem.string());
  }
 
 return int(rval.get());
}


double Criterion::GetDouble(void) const
{
 if( rval.IsNull() )
  {
   lem::MemFormatter mem;
   mem.printf( "Can not convert the string %us to number when accessing the criterion [%us]", str.c_str(), name.c_str() );
   throw lem::E_BaseException(mem.string());
  }
 
 return rval.get();  
}


void Criterion::SaveBin( lem::Stream &bin ) const
{
 str.SaveBin(bin);
 bin.write_bool( rval.NotNull() );
 if( rval.NotNull() )
  bin.write( &rval.get(), sizeof(rval.get()) );

 return;
}


void Criterion::LoadBin( lem::Stream &bin )
{
 str.LoadBin(bin);
 if( bin.read_bool() )
  {
   double x;
   bin.read( &x, sizeof(x) );
   rval = x; 
  }

 return;
}
