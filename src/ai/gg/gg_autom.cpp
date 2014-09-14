// -----------------------------------------------------------------------------
// File GG_AUTOM.CPP
//
// (c) by Elijah Koziev
//
// Content:
// SOLARIX Intellectronix Project      http://www.solarix.ru
//
// Класс GraphGram - контейнер для Графической Грамматики. Основной сервис,
// предоставляемый Графической Грамматикой - отождествление символа как буквы
// Алфавита объектного языка. Хранение информации об Алфавите стандартное для
// Системы - в виде набора буквостатей, хранящих альтернативные формы кодировок
// для ОДНОЙ БУКВЫ. Благодаря использованию Графической Грамматики мы уменьшаем
// зависимость Системы от кодового представления букв языка на машине.
// -----------------------------------------------------------------------------
//
// CD->02.03.1996
// LC->22.06.2014
// --------------

#if defined SOL_LOADTXT && defined SOL_COMPILER
#include <lem/conversions.h>
#include <lem/macro_parser.h>
#include <lem/solarix/exceptions.h>
#include <lem/logfile.h>
#endif

#include <lem/solarix/LS_ResultSet.h>
#include <lem/Ucs4ToWideString.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/automata_indeces.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/SymbolClasses.h>
#include <lem/solarix/GG_Coordinates.h>
#include <lem/solarix/CoordEnumerator.h>
#include <lem/solarix/Alphabet.h>
#include <lem/solarix/Alphabets.h>
#include <lem/solarix/AlphabetStorage.h>
#include <lem/solarix/Symbols.h>
#include <lem/solarix/Symbol.h>
#include <lem/solarix/ClassEnumerator.h>
#include <lem/solarix/SymbolEnumerator.h>
#include <lem/solarix/AlphabetEnumerator.h>
#include <lem/solarix/SymbolClassEnumerator.h>
#include <lem/solarix/CriteriaInStorage.h>
#include <lem/solarix/CriterionEnumerator.h>
#include <lem/solarix/GG_CharOperations.h>
#include <lem/solarix/GG_CharOperation.h>
#include <lem/solarix/CharOperationEnumerator.h>
#include <lem/solarix/SyllabRule.h>
#include <lem/solarix/gg_autom.h>

using namespace std;
using namespace lem;
using namespace Solarix;
using namespace lem::Iridium;


GraphGram::GraphGram(void):Grammar(SOL_GG_INDEX)
{
 storage = NULL;
 do_delete_storage=false;

 param = new CriteriaInStorage();
 alphabet = new Alphabets();
 symbols = new Symbols(this);
 coord = new GG_Coordinates(this);
 aclass = new SymbolClasses(this);
 char_operations = new GG_CharOperations(this);
 syllab_rules = new SyllabRules();

 return;
}


GraphGram::~GraphGram(void)
{
 delete alphabet;
 delete symbols;
 delete char_operations;
 delete syllab_rules;

 if( do_delete_storage )
  delete storage;

 return;
}


void GraphGram::SetStorage( AlphabetStorage *_storage, bool _do_delete )
{
 if( do_delete_storage )
  delete storage;

 storage = _storage;
 do_delete_storage = _do_delete;

 static_cast<CriteriaInStorage*>(param)->Connect(storage);
 alphabet->Connect(storage);
 symbols->Connect(storage);
 static_cast<GG_Coordinates*>(coord)->Connect(storage);
 static_cast<SymbolClasses*>(aclass)->Connect(storage);
 char_operations->Connect(storage);
 syllab_rules->Connect(storage);

 return;
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
/*********************************************************************
   Этот метод вызывается объектом класса Automaton при чтении секции
 automat gg {...} из текстового файла Словаря.

   Нас просят определить, должен ли структурный элемент в исходном
 текстовом файле Словаря, с начальным токеном t, загружаться нашим
 классом. В этом случае мы загружаем и возвращаем true, в противном
 случае возвращаем false. Так как мы перегрузили этот метод у
 родительского класса Grammar, "вручную" вызываем и его метод, чтобы
 Grammar мог загрузить общие для любой грамматики элементы Словаря.

   Графическая Грамматика - самая простая из всех автоматов Системы.
 В текстовом файле Словаря она описывается как набор статей, кажда
 статья есть множество представлений (отличающихся кодом) одной буквы
 Алфавита, например: большие и малые. Кроме того, Грамматика загружает
 Калибраторы. Каждый Калибратор определяет относительную частоту
 использования буквы в реальных текстах. С помошью калибраторов можно
 оптимизировать поиск символа в Алфавите, так как наиболее часто
 используемые символы будут размещены в просмотровой таблице сзади,
 и будут быстрее отыскиваться, без лишнего просмотра редких букв (поиск
 всегда будет идти с конца).
**********************************************************************/
bool GraphGram::ProcessLexem(
                             const BethToken &t,
                             Macro_Parser& txt,
                             const Binarization_Options &options
                            )
{
 if( t.GetToken() == B_ALPHABET )
  {
   alphabet->LoadTxt( txt, GetDict() );
   return true;
  }
 else if( t.string().eqi(L"syllab_rule") )
  {
   SyllabRule *rule = new SyllabRule();
   rule->LoadTxt( txt, GetDict() );
   rule->Store( storage );
   return true;
  }
 else if( t.string().eqi(L"operation") )
  {
   GG_CharOperation *x = new GG_CharOperation();
   x->LoadTxt( txt, GetDict() );
   const int id = storage->FindCharOperation(x->GetName());
   if( id!=UNKNOWN )
    {
     lem::Iridium::Print_Error(t,txt);
     dict->GetIO().merr().printf( "Character operation %us is already declared\n", x->GetName().c_str() );
     throw lem::E_BaseException();
    }

   storage->StoreCharOperation(x);
   delete x;
   return true;
  }

 // С остальными элементами пусть разбирается базовый класс Грамматики.
 return Grammar::ProcessLexem(t,txt,options);
}
#endif


int GraphGram::Find_Alphabet( const UCString &Name ) const
{
 return alphabet->Find(Name);
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
/**************************************************************************
 It is necessary to load an entry from Dictionary text file. This method
 is called by Grammar::ProcessLexem(...), and the invocation means that
 Grammar class recognizes the entry description in Dictionary file (see
 SolBaseEntry class for more information about rules of entry patterns
 recognition).
***************************************************************************/
void GraphGram::LoadEntry(
                          Macro_Parser& txtfile,
                          bool is_extern,
                          const Binarization_Options &options
                         )
{
 symbols->LoadEntry( txtfile, is_extern, options );
 return;
}
#endif



#if defined SOL_REPORT
/***********************************************************
 Печатаем краткий отчет о состоянии Графической Грамматики.
************************************************************/
void GraphGram::Report( OFormatter &s )
{
 Grammar::Report(s);

 // Подсчитываем общее число хранимых буквоформ.
 s.printf(
          "%W7d alphabet(s)\n" 
          "%W7d entry(s)\n"
          "%W7d form(s)\n"
          , alphabet->Count()
          , symbols->Count()
          , symbols->CountForms()
         );

 return;
}
#endif


#if defined SOL_REPORT
// ******************************************************
// Распечатка КАРТЫ - служебной информации об автомате в
// указанный текстовый поток.
// ******************************************************
void GraphGram::PrintMap( OFormatter &txtfile )
{
 Grammar::PrintMap(txtfile);
 Report( txtfile );

 // The simple list of classes (not ordered - listed as they are in container)
 txtfile.printf(
                "\n%14h-List of classes:%14h-\nid  class name    number of entries\n"
               );

 MCollect< pair<int/*id_class*/,int/*nentry*/> > class_info;
 class_info.reserve(classes().Count());

 int max_entries = 0;

 lem::Ptr<ClassEnumerator> cenum( classes().Enumerate() );
 while( cenum->Fetch() )
  {
   const int id_class = cenum->GetId();   

   // Сколько статей относится к данному классу
   int nentry=0;

   lem::Ptr<SymbolEnumerator> senum( symbols->Enumerate() );
   while( senum->Fetch() )
    {
     if( senum->GetItem().GetClass()==id_class )
      nentry++;
    }

   txtfile.printf(
                  "%W3d %W20us %d\n"
                  , id_class
                  , classes()[id_class].GetName().c_str()
                  , nentry
                 );

   class_info.push_back( make_pair(id_class,nentry) );
   max_entries = std::max( max_entries, nentry );
  }

 txtfile.eol();


 // Going to make more impressing list of classes - ordered by number
 // of entries belong to each of them.
 sort_desc_pairs( class_info );

 if( !max_entries )
  max_entries = 1;

 txtfile.printf( "Ordered list of classes (weighted by number of belonging entries\n" );

 for( int j=0; j<classes().Count(); j++ )
  {
   txtfile.printf(
                  "%W3d %W20us %W4d |%H#\n"
                  , class_info[j].first
                  , classes()[ class_info[j].first ].GetName().c_str()
                  , class_info[j].second
                  , int( 36*class_info[j].second/max_entries )
                 );
  }

 txtfile.flush();
 
 // Перечень имен координат
 txtfile.printf( "\nList of coordinates:" );
 lem::Ptr<CoordEnumerator> coenum( coords().Enumerate() );
 while( coenum->Fetch() )
  {
   const GramCoord &c = coenum->GetItem();
   txtfile.printf(
                  " %us (# of states: %d)"
                  , c.GetName().front().c_str()
                  , c.states().size()
                 );
  }

 txtfile.eol();
 txtfile.flush();

 txtfile.printf( "%10h- END OF <GG> SECTION %10h-\n\n\n" );

 GetIO().mecho().printf( "Ok\n" );

 txtfile.flush();

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
/****************************************************************************
 Подготавливаем Графическую Грамматику к работе в составе Вербальной Машины.
 После подготовки сбрасываем таблицу calibr, так как калибраторы больше не
 понадобятся. Обратите внимание, что формируемая таблица быстрого поиска
 символов содержит индексы статей, а не их ключи, поэтому после изменени
 порядка хранимых буквостатей таблица будет содержать некорректную информацию.
 Данный метод вызывается автоматически классом Dictionary. После полной
 загрузки всех текстовых файлов Словаря.
******************************************************************************/
void GraphGram::Prepare( const lem::Path &outdir, const Binarization_Options &opts )
{
 Grammar::Prepare(outdir,opts);
 symbols->FinishCompilation();
 return;
}
#endif


/*****************************************************************
 Возвращаем условное имя Автомата, которое используется в команде
 automat XX в текстовом файле Словаря для объявления секции
 Графической Грамматики.
******************************************************************/
const UCString GraphGram::GetName(void) const
{ return SOL_GRAPHAUTO_MARK; }



const Word_Coord GraphGram::FindSymbol( wchar_t code ) const
{
 return symbols->FindSymbol(code);
}

const Word_Coord GraphGram::FindSymbol( wchar_t code, int AlphabetID ) const
{
 return symbols->FindSymbol(code,AlphabetID);
}

const Word_Coord GraphGram::FindSymbol( wchar_t code, const lem::MCollect<int> &AlphabetID ) const
{
 return symbols->FindSymbol(code,AlphabetID);
}


void GraphGram::FindSymbol( wchar_t code, MCollect<Word_Coord> &projs ) const
{
 symbols->FindSymbol(code,projs);
 return;
}

void GraphGram::FindSymbol( wchar_t code, MCollect<Word_Coord> &projs, int AlphabetID ) const
{
 symbols->FindSymbol(code,projs,AlphabetID);
 return;
}


void GraphGram::FindSymbol( wchar_t code, MCollect<Word_Coord> &projs, const lem::MCollect<int> &AlphabetID ) const
{
 symbols->FindSymbol(code,projs,AlphabetID);
 return;
}


lem::CString Solarix::EncodeChar32ToUtf8( lem::uint32_t c )
{
 lem::CString res;

 uint8_t utf8[8];
 int len = lem::UCS4_to_UTF8( c, utf8 );
 for( int i=0; i<len; ++i )
  res += utf8[i+1];
 return res;
}


lem::UCString Solarix::EncodeChar32ToWide( lem::uint32_t c )
{
 if( sizeof(wchar_t)==4 )
  return lem::UCString( (wchar_t)c );
 else
  {
   Ucs4ToUCString res;
   res.Add(c);
   return res.ToString();
  }
}



#if defined SOL_REPORT

static bool dims_sorter( const GramCoordPair &x, const GramCoordPair &y )
{
 return x.GetCoord().GetIndex()<y.GetCoord().GetIndex();
}




class ABC_CoordPairsList
{
 private:
  lem::PtrCollect<lem::UFString> ints_list;
  lem::PtrCollect<CP_Array> pairs_list; 
  std::map< lem::UFString, int > ints2index;

 public:
  ABC_CoordPairsList(void)
  {
   pairs_list.push_back( new CP_Array );
   ints_list.push_back( new lem::UFString(L" ") );
   ints2index.insert( std::make_pair( UFString(L" "), 0 ) );
   return;
  }

  int Register( const CP_Array &pairs )
  {
   if( pairs.empty() )
    return 0;

   lem::UFString ints;
   for( lem::Container::size_type i=0; i<pairs.size(); ++i )
    {
     ints += lem::format_str( L" %d:%d", pairs[i].GetCoord().GetIndex(), pairs[i].GetState() );
    }

   ints += L' ';

   std::map< lem::UFString, int >::const_iterator it = ints2index.find(ints);
   if( it==ints2index.end() )
    {
     const int index = CastSizeToInt(ints_list.size());
     ints_list.push_back( new UFString(ints) );
     pairs_list.push_back( new CP_Array(pairs) );
     ints2index.insert( std::make_pair(ints,index) );
     return index;
    }
   else
    {
     return it->second;
    } 
  }


  void SaveSQL( OFormatter &out, const SQL_Production &sql_version )
  {
   const wchar_t* NPrefix = sql_version.GetNPrefix();

   int id_pair=0;
   for( lem::Container::size_type i=0; i<ints_list.size(); ++i )
    {
     int id_pairs = CastSizeToInt(i);

     out.printf( "INSERT INTO abc_pairs( id, str_pairs )"
                 " VALUES( %d, %us'%us' );\n", 
                  id_pairs, NPrefix, ints_list[i]->c_str() );

     const CP_Array &p = * pairs_list[i];
     for( lem::Container::size_type j=0; j<p.size(); ++j )
      {
       out.printf( "INSERT INTO abc_pair( id, id_pairs, id_coord, id_state )"
        " VALUES ( %d, %d, %d, %d );\n",
         id_pair++, id_pairs, p[j].GetCoord().GetIndex(), p[j].GetState() ); 
      }
    }

   return;
  }
};




void GraphGram::Save_SQL(
                         OFormatter &out,
                         OFormatter &alters,
                         const SQL_Production &sql_version
                        ) 
{
 if( sql_version.type==SQL_Production::MsSql )
  {
   out.printf( "!! @echo Creating alphabets...\n" );
  }
 else if( sql_version.type==SQL_Production::Oracle )
  {
   out.printf( "HOST echo Creating alphabets...\n" );
  }

 out.printf( "%s\n", sql_version.BeginTx().c_str() );

 const wchar_t* NPrefix = sql_version.GetNPrefix();

 // ПАРАМЕТРЫ -> SG_CRITERION
 lem::Ptr<CriterionEnumerator> crenum( param->Enumerate() );
 while( crenum->Fetch() )
  {
   const int id = crenum->GetId();
   const Criterion& x = crenum->GetItem();

   lem::UFString name( sql_version.SqlStr(x.GetName()) );   
   lem::UFString strval( sql_version.SqlStr(x.GetString()) );   

   out.printf( 
              "INSERT INTO sg_criterion( id, name, strval ) VALUES( %d, %us'%us', %us'%us' );\n"
              , id
              , NPrefix
              , name.c_str()
              , NPrefix
              , strval.c_str() 
             );
  }

 out.eol();

 // АЛФАВИТЫ
 lem::Ptr<AlphabetEnumerator> aenum( alphabets().List() );
 while( aenum->Fetch() )
  {
   const Alphabet &alphabet = aenum->GetItem();
   const int id = aenum->GetId();

   lem::UFString aname( sql_version.SqlStr(alphabet.get_Name()) );

   out.printf( 
              "INSERT INTO abc_alphabet( id, name ) VALUES( %d, %us'%us' );\n"
              , id
              , NPrefix
              , aname.c_str()
             );
  }

 out.eol();

 // КООРДИНАТЫ И СОСТОЯНИЯ
 lem::Ptr<CoordEnumerator> cenum( coords().Enumerate() );
 while( cenum->Fetch() )
  {
   const int id_coord = cenum->GetId();
   const GramCoord &c = cenum->GetItem();

   out.printf(
              "INSERT INTO abc_coord( id, name, bistable ) VALUES ( %d, %us'%us', %d );\n",
              id_coord,
              NPrefix,
              c.GetName().front().c_str(),
              c.IsBistable() ? 1 : 0
             );

   int istate=0;

   if( c.IsBistable() ) 
    {
     // Все-таки объявим в явном виде два состояния для бистабильных координат, чтобы
     // в реляционной схеме можно было создавать foreight key с таблиц SG_ENTRY_COORD и SG_FORM_COORD
     out.printf( "INSERT INTO abc_state( id, id_coord, name ) VALUES ( 0, %d, '0' );\n", id_coord );
     out.printf( "INSERT INTO abc_state( id, id_coord, name ) VALUES ( 1, %d, '1' );\n", id_coord );
    }
   else
    {
     for( lem::Container::size_type j=0; j<c.states().size(); ++j )
      {
       const GramCoordState & s = c.states()[j];
       const int id_parent = istate;

       for( lem::Container::size_type k=0; k<s.size(); ++k, ++istate )
        {
         out.printf( "INSERT INTO abc_state( id, id_coord, name ) VALUES ( %d, %d, %us'%us' );\n",
         istate, id_coord, NPrefix, s[k].c_str() );
        }
      }
    }
  }

 // КЛАССЫ -> ABC_CLASS
 lem::Ptr<SymbolClassEnumerator> class_enum( (SymbolClassEnumerator*)classes().Enumerate() );
 while( class_enum->Fetch() )
  {
   const int id = class_enum->GetId();
   const GramClass & c = class_enum->GetItem();

   out.printf(
              "INSERT INTO abc_class( id, name ) VALUES( %d, %us'%us' );\n"
              , id
              , NPrefix
              , sql_version.SqlStr(c.GetName()).c_str()
            );

   // Сохраним в базе информацию о привязке координат (атрибутов, измерений, тэгов) к классам.
   for( lem::Container::size_type k=0; k<c.attrs().size(); ++k )
    {
     const GramCoordAdr &atr = c.attrs()[k];

     out.printf(
                "INSERT INTO abc_class_coord( id_class, id_coord, coord_type ) VALUES( %d, %d, 0 );\n"
                , id
                , atr.GetIndex()
              );
    }

   for( lem::Container::size_type k=0; k<c.dims().size(); ++k )   
    {
     const GramCoordAdr &dim = c.dims()[k];

     out.printf(
                "INSERT INTO abc_class_coord( id_class, id_coord, coord_type ) VALUES( %d, %d, 1 );\n"
                , id
                , dim.GetIndex()
              );
    }
  }


 out.eol();


 // **********************
 // СТАТЬИ -> ABC_ENTRY
 // **********************

 ABC_CoordPairsList coords_ref;

 lem::Ptr<SymbolEnumerator> senum( entries().Enumerate() );
 int id_form=0;
 while( senum->Fetch() )
  {
   const GG_Entry &e = senum->GetItem();

   // некоторые версии MSSQL ругаются на unicode-символы с кодами более 2^16.
   // поэтому для этой СУБД не будем их реально загружать, но чтобы отсутствие этих
   // символов не вызывало удивления - впечатаем закомментированные операторы DML.
   bool wrap_in_comment=false;
   if( e.GetName()>0x0000ffffU )
   {
    if( sql_version.type==SQL_Production::MsSql || sql_version.type==SQL_Production::Oracle || sql_version.type==SQL_Production::Postgres )
     {
      wrap_in_comment=true;
     }
   }

   const int id_pairs = coords_ref.Register( e.attrs() );
   const int id_entry = senum->GetId();

   UFString s = lem::UFString(e.GetNameWide().c_str());

   if( wrap_in_comment )
    out.printf( "%s", sql_version.Get_Comment().c_str() );

   if( sql_version.type==SQL_Production::Oracle )
    {
     UFString s2=SQL_Production::Oracle_UNISTR(s);

     out.printf(
                "INSERT INTO abc_entry( id, name, code, id_class, id_alphabet, id_pairs ) VALUES( %d, %us, %d, %d, %d, %d );\n"
                , id_entry
                , s2.c_str()
                , e.GetName()
                , e.GetClass()
                , e.GetAlphabet()
                , id_pairs
               );
    }
   else
    {
     s = sql_version.ClearInvalidChars(s);
     s = sql_version.SqlStr(s);

     out.printf(
                "INSERT INTO abc_entry( id, name, code, id_class, id_alphabet, id_pairs ) VALUES( %d, %us'%us', %d, %d, %d, %d );\n"
                , id_entry
                , NPrefix
                , s.c_str()
                , e.GetName()
                , e.GetClass()
                , e.GetAlphabet()
                , id_pairs
               );
    }

   for( Container::size_type j=0; j<e.forms().size(); j++ )
    {
     const GG_EntryForm &form = e.forms()[j];
     lem::UFString fs( form.GetNameWide().c_str() );

     const int id_dims = coords_ref.Register( form.dims() );

     if( wrap_in_comment )
      out.printf( "%s", sql_version.Get_Comment().c_str() );

     if( sql_version.type==SQL_Production::Oracle )
      {
       UFString s2=SQL_Production::Oracle_UNISTR(fs);

       out.printf( 
                  "INSERT INTO abc_form( id, id_entry, ordnum, name, code, id_pairs )"
                  " VALUES( %d, %d, %d, %us, %d, %d );\n"
                  , id_form++
                  , id_entry
                  , CastSizeToInt(j)
                  , s2.c_str()
                  , form.GetName()
                  , id_dims
                 );
      }
     else
      {
       fs = sql_version.ClearInvalidChars(fs);
       fs = sql_version.SqlStr(fs);
  
       out.printf( 
                  "INSERT INTO abc_form( id, id_entry, ordnum, name, code, id_pairs )"
                  " VALUES( %d, %d, %d, %us'%us', %d, %d );\n"
                  , id_form++
                  , id_entry
                  , CastSizeToInt(j)
                  , NPrefix
                  , fs.c_str()
                  , form.GetName()
                  , id_dims
                 );
      }
    }  
  }


 if( !sql_version.norules )
  {
   // Правила слогоделителя
   lem::Ptr<LS_ResultSet> rs_slb1( storage->ListSyllabRules() );
   while( rs_slb1->Fetch() )
    {
     const int id = rs_slb1->GetInt(0);
     lem::UCString name = rs_slb1->GetUCString(1);
     const int id_src = rs_slb1->GetInt(2);
     const int id_language = rs_slb1->GetInt(3);
     const int cursor_shift = rs_slb1->GetInt(4);

     out.printf( "INSERT INTO slb_rule( id, name, id_src, id_language, cursor_shift ) VALUES ( %d, '%us', %d, %d, %d );\n", id, name.c_str(), id_src, id_language, cursor_shift );
    }
   rs_slb1.Delete();
   out.eol();


   lem::Ptr<LS_ResultSet> rs_slb2( storage->ListSyllabConditionPoints() );
   while( rs_slb2->Fetch() )
    {
     const int id = rs_slb2->GetInt(0);
     const int id_rule = rs_slb2->GetInt(1);
     const int point_index = rs_slb2->GetInt(2);
     const int n_char = rs_slb2->GetInt(3);
     lem::UFString char_text = rs_slb2->GetUFString(4);
     lem::UFString char_ucs4 = rs_slb2->GetUFString(5);
     const int id_class = rs_slb2->GetInt(6);
     const int id_entry = rs_slb2->GetInt(7);
     const int n_coord = rs_slb2->GetInt(8);
     const int id_coord0 = rs_slb2->GetInt(9);
     const int id_state0 = rs_slb2->GetInt(10);
     const int is_left_boundary = rs_slb2->GetInt(11);
     const int is_right_boundary = rs_slb2->GetInt(12);
     const int is_positive = rs_slb2->GetInt(13);

     out.printf( "INSERT INTO slb_condition_point( id, id_rule, point_index, n_char, char_text, char_ucs4,"
                 " id_class, id_entry, id_coord0, id_state0, is_left_boundary,"
                 " is_right_boundary, n_coord, is_positive ) VALUES ("
                 " %d, %d, %d, %d, '%us', '%us',"
                 " %d, %d, %d, %d, %d,"
                 " %d, %d, %d );\n",
                 id, id_rule, point_index, n_char, char_text.empty() ? L"" : char_text.c_str(), char_ucs4.empty() ? L"" : char_ucs4.c_str(),
                 id_class, id_entry, id_coord0, id_state0, is_left_boundary,
                 is_right_boundary, n_coord, is_positive
                );
    }

   rs_slb2.Delete();
   out.eol();

   lem::Ptr<LS_ResultSet> rs_slb3( storage->ListSyllabResultPoints() );
   while( rs_slb3->Fetch() )
    {
     const int id = rs_slb3->GetInt(0);
     const int id_rule = rs_slb3->GetInt(1);
     const int point_index = rs_slb3->GetInt(2);
     const int copy_index = rs_slb3->GetInt(3);
     const int merge_index0 = rs_slb3->GetInt(4);
     const int merge_count = rs_slb3->GetInt(5);

     out.printf( "INSERT INTO slb_result_point( id, id_rule, point_index, copy_index, merge_index0, merge_count )"
               " VALUES ( %d, %d, %d, %d, %d, %d );\n", id, id_rule, point_index, copy_index, merge_index0, merge_count );
    }

   rs_slb3.Delete();
   out.eol();


   out.eol();
   out.printf( "%s\n", sql_version.CommitTx().c_str() );
   out.printf( "%s\n", sql_version.BeginTx().c_str() );
  }

 coords_ref.SaveSQL(out,sql_version);

 out.eol();
 out.printf( "%s\n", sql_version.CommitTx().c_str() );

 if( sql_version.type==SQL_Production::MsSql )
  {
   out.printf( "!! @echo Alphabets have been loaded.\n" );
  }
 else if( sql_version.type==SQL_Production::Oracle )
  {
   out.printf( "HOST echo Alphabets have been loaded.\n" );
  }

 return;
}
#endif


#if defined SOL_REPORT
void GraphGram::SaveRules_SQL( OFormatter &out, OFormatter &alters, const SQL_Production &sql_version )
{
 lem::Ptr<CharOperationEnumerator> opers( GetCharOperations().ListOperations() );

 int id_seq=1;
 while( opers->Fetch() )
  {
   const GG_CharOperation &op = opers->GetOperation();

   out.printf( "\n\nINSERT INTO abc_operation( id, name ) VALUES ( %d, '%us' );\n", op.GetId(), op.GetName().c_str() );
  
   for( std::map< lem::uint32_t, lem::uint32_t >::const_iterator it=op.Items().begin(); it!=op.Items().end(); ++it )
    {
     out.printf( "INSERT INTO abc_operation_item( id, id_operation, src_char_ucs4, res_char_ucs4, src_char, res_char )"
                 " VALUES( %d, %d, %d, %d, '%uc', '%uc' );\n", id_seq++, op.GetId(), it->first, it->second, it->first, it->second );
    }
  }

 return;
}
#endif


void GraphGram::BeforeSyntaxRecompilation(void)
{
 storage->DeleteSyllabRules();
 return;
}



void GraphGram::FindSyllabs(
                            const lem::UCString & word,
                            int id_language,
                            bool get_upper_case,
                            lem::MCollect<lem::UCString> &result_syllabs,
                            LA_RecognitionTrace *trace
                           )
{
 SyllabContext ctx( *this, word, id_language );

 const SyllabRulesForLanguage & rules = syllab_rules->GetRules(id_language);
 ctx.Apply(rules,trace);

 ctx.GetResultSyllabs( result_syllabs, get_upper_case );
 return;
}
