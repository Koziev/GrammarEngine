// -----------------------------------------------------------------------------
// File CriteriaInFile.CPP
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// Класс CriteriaInFile - список параметров, влияющих на работу Автоматов. Список
// загружается Автоматом из своей именной секции в текстовом файле Словаря.
// -----------------------------------------------------------------------------
//
// CD->22.08.1997
// LC->04.01.2011
// --------------

#include <lem/macro_parser.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/CriterionEnumeratorInFile.h>
#include <lem/solarix/criterion.h>
#include <lem/solarix/CriteriaInFile.h>

using namespace lem;
using namespace Solarix;
using namespace lem::Iridium;

#if defined SOL_LOADTXT
void CriteriaInFile::LoadTxt( const Sol_IO &io, Macro_Parser &txtfile )
{
 const BSourceState begin=txtfile.tellp();
 const Criterion to_add(io,txtfile);

 if( Find(to_add.GetName()) != UNKNOWN )
  {
   // Повторное определение параметра.
   io.merr().printf(
	                "Criterion [%us] is already defined\n"
					, to_add.GetName().c_str()
				   );
   Print_Error(begin,txtfile);
   throw E_ParserError();
  }

 list.push_back(to_add);
 return;
}
#endif

/**********************************************************************
 Поиск параметра с заданным именем name. Если поиск успешен, по
 возвращается внутренний индекс параметра в списке, иначе возвращается
 значение UNKNOWN.
***********************************************************************/
int CriteriaInFile::Find( const UCString &name )
{
 for( Container::size_type i=0; i<list.size(); i++ )
  if( list[i].GetName()==name )
   return CastSizeToInt(i);

 return UNKNOWN;
}

const Criterion& CriteriaInFile::operator[]( int id )
{
 if( id==-1 )
  throw lem::E_BaseException( L"Invalid parameter access" );

 return list[id];
}


const Criterion& CriteriaInFile::operator[]( const lem::UCString &name )
{
 int i = Find(name);
 if( i==UNKNOWN )
  { 
   lem::MemFormatter mem;
   mem.printf( "Can not find parameter [%us]", name.c_str() );
   throw lem::E_BaseException( mem.string() );
  }

 return list[i];
}


CriterionEnumerator* CriteriaInFile::Enumerate(void)
{
 return new CriterionEnumeratorInFile( this );
}

void CriteriaInFile::SaveBin( lem::Stream &bin ) const
{
 list.SaveBin(bin);
 return;
}

void CriteriaInFile::LoadBin( lem::Stream &bin )
{
 list.LoadBin(bin);
 return;
}
