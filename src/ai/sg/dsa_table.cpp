// -----------------------------------------------------------------------------
// File DSA_TABL.CPP
//
// (c) by Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
//
// Класс SG_DeclensionTable - описание Таблицы Формообразования для
// Синтаксической грамматики. Одна такая таблица содержит команды для Автомата
// Формообразования и позволяет построить полный набор словоформ из некоторой
// базовой формы для словарной статьи.
//
// 07.05.2006 - для регекспа образца включена опция "игнорировать регистр"
// 08.07.2009 - название парадигм теперь могут быть не только числами, но и
//              произвольными строками.
// 19.03.2010 - для автопарадигм теперь также можно задавать имена, чтобы
//              выдавать их пользователю в программе SQLex для автозаполнения
//              форм создаваемой словарной статьи.
// -----------------------------------------------------------------------------
//
// CD->10.03.1997
// LC->27.06.2011
// --------------

#include <lem/conversions.h>
#include <lem/macro_parser.h>

#undef AddForm

#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/ClassList.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/dsa_main.h>
#include <lem/solarix/ParadigmaForm.h>
#include <lem/solarix/Paradigma.h>

using namespace boost;
using namespace lem;
using namespace Solarix;

#if !defined FAIND_NO_BOOST_REGEX
using boost::wregex;
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
SG_DeclensionTable::SG_DeclensionTable(
                                       Macro_Parser& txtfile,
                                       Grammar& gram
                                      )
:Form_Table()
{ LoadTxt(txtfile,gram,false); }
#endif


SG_DeclensionTable::SG_DeclensionTable(
                                       const lem::MCollect<lem::UCString> & Names,
                                       const lem::UFString & matcher_str,
                                       int PartOfSpeech,
                                       const CP_Array & Attrs,
                                       const lem::MCollect<SG_DeclensionForm*> &Forms
                                      )
:Form_Table(), names(Names), condition(matcher_str)
{
 if( !names.empty() ) name=names.front();
 iclass = PartOfSpeech;
 attr = Attrs;
 form = Forms;
 return;
}




SG_DeclensionTable::~SG_DeclensionTable(void)
{
 for( lem::Container::size_type i=0; i<form.size(); ++i )
  delete form[i];

 return;
}


const Grammar& SG_DeclensionTable::GetGrammar( const Dictionary &dict )
{
 return dict.GetSynGram();
}

Grammar& SG_DeclensionTable::GetGrammar( Dictionary &dict )
{
 return dict.GetSynGram();
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
/*******************************************************************
 Именем таблицы в данном случае является целое неотрицательное число
 в десятеричной системе счисления.
********************************************************************/
void SG_DeclensionTable::LoadName(
                                  Macro_Parser &txtfile,
                                  Dictionary &dict
                                 )
{
 const BethToken& t = txtfile.read();
 key = ANY_STATE;

 // Формат:
 // paradigma Условное_Имя, Алиас1, ... :
 name = t.string();
 names.push_back(name);

 key = ANY_STATE;

 while( !txtfile.eof() && txtfile.pick().GetToken()==B_COMMA )
  {
   txtfile.read_it(B_COMMA);  
   names.push_back( txtfile.read().string() );
  } 

 txtfile.read_it(B_COLON);

 if( dict.GetDebugLevel_ir()>=3 )
  {
   dict.GetIO().mecho().printf(
                               "%us [%vfE%us%vn]->",
                               sol_get_token(B_PARADIGMA).c_str(),
                               GetName().c_str()
                              );
  }

 return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
// Синтаксис реализации таблицы склонения может быть более сложным,
// чем для обычных таблиц форм:
//
// declension auto : NOUN for "(.+)S"
// {                      ^^^^^^^^^^^
//  :    
//
//
// Курсор считывания стоит на первой после имени класса (NOUN в примере)
// лексеме.
void SG_DeclensionTable::LoadBody( Macro_Parser &txtfile, Grammar& gram )
{
 if( txtfile.probe(B_FOR) )
  {
   condition.LoadTxt( txtfile, GetClass(), (SynGram&)gram );
  }

 Form_Table::LoadBody( txtfile, gram );

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SG_DeclensionTable::Loaded( const Dictionary &dict )
{
 if( dict.GetDebugLevel_ir()>=3 )
  dict.GetIO().merr().printf( "%vfAOK%vn\n" );

 return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
void SG_DeclensionTable::AddForm(
                                 const CP_Array &dim,
                                 const WordFormName &form_name,
                                 Dictionary &dict
                                )
{
 try
  {
   form.push_back( new SG_DeclensionForm(dim,form_name.form_name) );
  }
 catch( ... )
  {
   dict.GetIO().merr().printf( "Error in paradigma [%us] syntax\n", GetName().c_str() ); 
   throw E_BaseException();
  }
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
/****************************************************************************
 Заканчиваем преобразование описаний мультилексем в корректные мультилексемы.
 Вызывается непосредственно после загрузки описания таблицы из текстового
 файла Словаря.
*****************************************************************************/
void SG_DeclensionTable::Translate( const GraphGram &gram )
{
 for( lem::Container::size_type i=0; i<form.size(); i++ )
  form[i]->Translate(GetClass(),gram);

 return;
}
#endif


// *********************************************************************
// Можно ли использовать таблицу для генерации форм у статьи с заданным
// именем.
// *********************************************************************
bool SG_DeclensionTable::CanApply( const UCString &entry_name ) const
{
 return condition.Match(entry_name);
}

bool SG_DeclensionTable::IsAuto(void) const
{
 return !condition.Empty();
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SG_DeclensionTable::ReadAdditionalInfo( Grammar &gram, int iForm, Macro_Parser& txtfile )
{
 form[iForm]->ReadAdditionalInfo(gram,*this,txtfile);
 return;
}
#endif


int SG_DeclensionTable::CountForms(void) const
{
 return CastSizeToInt(form.size());
}


void SG_DeclensionTable::GenerateForms(
                                       const Lexem &entry_name,
                                       lem::MCollect<Lexem> &res,
                                       const SynGram &sg,
                                       const SG_DeclensionAutomat &dsa 
                                      ) const
{
 res.reserve(form.size());

 for( lem::Container::size_type i=0; i<form.size(); i++ )
  {
   UCString frm( dsa.ProduceForm( entry_name, GetClass(), *form[i], sg ) );

   // Без повторов
   if( std::find( res.begin(), res.end(), frm )==res.end() )
    res.push_back( frm );
  }

 return;
}


void SG_DeclensionTable::GenerateForms(
                                       const Lexem &entry_name,
                                       lem::MCollect<Lexem> & res,
                                       lem::PtrCollect<CP_Array> & form_dims, 
                                       const SynGram &sg,
                                       const SG_DeclensionAutomat &dsa 
                                      ) const
{
 res.reserve(form.size());

 for( lem::Container::size_type i=0; i<form.size(); i++ )
  {
   UCString frm( dsa.ProduceForm( entry_name, GetClass(), *form[i], sg ) );

   res.push_back( frm);
   form_dims.push_back( new CP_Array( form[i]->GetDim() ) );
  }

 return;
}



bool SG_DeclensionTable::MatchName( const lem::UCString &s ) const
{
 for( lem::Container::size_type j=0; j<names.size(); j++ )
  {
   if( names[j].eqi(s) )
    return true;
  }

 return false;
}
