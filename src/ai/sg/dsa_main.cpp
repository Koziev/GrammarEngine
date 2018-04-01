// -----------------------------------------------------------------------------
// File DSA_MAIN.CPP
//
// (c) by Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
//
// Класс SG_DeclensionAutomat - СубАвтомат Формообразования. Содержит код
// для создания лексемы из некоторой базовой формы (обычно имени словарной
// статьи) и строки с командами модификации (обычно - элементом таблицы
// формообразования).
// -----------------------------------------------------------------------------
//
// CD->11.03.1997
// LC->16.09.2013
// --------------

#include <lem/conversions.h>
#include <lem/oformatter.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/Paradigma.h>
#include <lem/solarix/ParadigmaFinder.h>
#include <lem/solarix/ParadigmaForm.h>
#include <lem/solarix/dsa_main.h>

using namespace lem;
using namespace Solarix;

SG_DeclensionAutomat::SG_DeclensionAutomat( const SynGram *Gram )
{
 gram=Gram;
 storage=NULL;
 finder=NULL;
 store_auto_tables = false;
 return;
}



SG_DeclensionAutomat::~SG_DeclensionAutomat(void)
{
 for( lem::Container::size_type i=0; i<tables.size(); ++i )
  delete tables[i];

 lem_rub_off(finder);

 return;
}

void SG_DeclensionAutomat::Connect( LexiconStorage *_storage )
{
 storage = _storage;

 for( lem::Container::size_type i=0; i<tables.size(); ++i )
  delete tables[i];

 tables.clear();
 name2decl.clear();
 id2decl.clear();
 name2id.clear();

 delete finder;
 finder = new ParadigmaFinder(storage);

 return;
}



/*****************************************************************
 Создаем лексическое содержимое грамматической формы из указанной
 базовой формы base согласно команде формообразования, заданной
 символами строки driver. Возвращает результат формообразования.
******************************************************************/
const Lexem SG_DeclensionAutomat::ProduceForm(
                                              const Lexem &base,
                                              int id_class,
                                              const SG_DeclensionForm &driver,
                                              const SynGram &gram
                                             ) const
{
 const Lexem &original = base;
 const Lexem &driver_lex = driver.GetContent();

 const wchar_t *org_lex  = original.c_str();
 const wchar_t *drv      = driver_lex.c_str();

 int i=0;
 wchar_t ch;

 wchar_t made_string[LEM_CSTRING_LEN1];

 int len=driver_lex.length();

 while( org_lex[i] )
  {
   made_string[i] = org_lex[i];
   i++;
  }

 int i_dest = i; // Длина original

 made_string[i] = 0;

 i=0;
 while( i<len && (ch=drv[i++]) )
  if( ch==B_COMMAND_METACHAR )
   {
    switch( ch=drv[i++] )
     {
      case B_REDUCE_METACHAR:
       {
        // %-N
        // Лексема урезается на несколько символов cправа.
        i_dest -= (wchar_t)uchar_to_digit(drv[i++]);
        if( i_dest<0 )
         {
          gram.GetIO().merr().printf( "Error in REDUCE command in [%us] with lexem [%us]\n", drv, org_lex );
          throw E_ParserError();
         }

        made_string[i_dest] = 0;
        break;
       }

      case B_STRESS_METACHAR:
       {
        // %+...%
        // Справа добавляются несколько символов, список добавляемых
        // символов обрывается символом '%' или концом строки. Может
        // встретится особый формат: добавляеые символы вместе с
        // особыми признаками (ударность etc.)  перечислены в скобочках
        // {RRR...R}.
        //
        // Контролируем, чтобы длина строки не превысила LEM_CSTRING_LEN,
        // в противном случае терминирующий 0 вылетит за пределы.

        wchar_t terminator = B_COMMAND_METACHAR;
        if( drv[i]==B_GROUP_BEGIN_METACHAR )
         {
          i++;
          terminator = B_GROUP_END_METACHAR;
         }

        while( i<len && (ch=drv[i++]) && ch!=terminator )
         {
//          made_form[i_dest]     = src_form[i];
//          made_stress[i_dest] = src_stress[i];
          made_string[i_dest++]   = ch;

          if( i_dest>=LEM_CSTRING_LEN )
           {
            gram.GetIO().merr().printf(
                "Incorrect result when applying declension command ADD in [%us] to [%us].\n"
                "Result too long.\n"
                                       , drv, org_lex
                                      );
            throw E_ParserError();
           }
         }

        made_string[i_dest]=0;
        break;
       }

      case B_CUT_METACHAR:
       {
        // %cN
        // Из лексемы вырезается символ, отстоящий на i_del от правого конца.
        // Если n=0, то отрезается самый последний символ, и так далее.
        const int i_del = uchar_to_digit(drv[i++]);
        const int ll = lem::lem_strlen(made_string);
        const int ip = ll - i_del - 1; // Символ в этой позиции исчезнет.
        const int rest=ll-ip; // Столько символов следует за вырезаемым + терминатор
        // Обращаю внимание, что буфера для строк made_form и made_stress
        // длинее на 1 элемент, чем это необходимо, поэтому можем работать в
        // них с 'терминаторами'!

        if( ip<0 )
         {
          // Вылетели за пределы строки!
          gram.GetIO().merr().printf(
                "Incorrect result of declension command %ucN in [%us], base form=[%us].\n"
                "Char to be cut off is out of string limits.\n"
                                     , drv, org_lex
                                    );
          throw E_ParserError();
         }

        // Сдвигаем строки на 1 символ.
        memmove( &made_string[ip], &made_string[ip+1], rest*sizeof(*made_string) );
        i_dest--;
        break;
       }

      case B_DOUBLE_METACHAR:
      {
       // %D
       // Дублируем последний символ

       if( i_dest>=LEM_CSTRING_LEN )
        {
         // Вылетели за пределы строки!
         gram.GetIO().merr().printf(
                "Incorrect result of declension command %D in [%us], base form=[%us].\n"
                "Result lexem is too long.\n"
                , drv, org_lex
                                    );
          throw E_ParserError();
         }

       made_string[i_dest] = made_string[i_dest-1];
       i_dest++;
       break;
      }  

      case B_PREFIX_INSERT_METACHAR:
       {
        // %aNR
        // В позицию результатной лексемы, начиная с N, вписывается
        // символ R, так что оригинальный символ из позиции N сдвигается
        // в позицию N+1, и так далее.
        // Особый вариант этой команды: %aN{RRR..R} позволяет добавить
        // в указанную позицию произвольное количество символов
        const int N = uchar_to_digit(drv[i++]);
        const int res_len = lem::lem_strlen(made_string);

        // Сколько символов вставляем...
        int n_char_to_add = 1;
        int i_char = i; // Из этой позиции берём добавляемые символы RRR
        if( drv[i]==B_GROUP_BEGIN_METACHAR )
         {
          int ii=i+1;
          i_char++;
          n_char_to_add=0;
          while( ii<len && drv[ii++]!=B_GROUP_END_METACHAR )
           n_char_to_add++;
         }

        // Нет ли переполнения буфера результата?
        if( (res_len+n_char_to_add)>LEM_CSTRING_LEN )
         {
          gram.GetIO().merr().printf(
                "Result is too long after application of declension command ADD in [%us] to [%us].\n"
                , drv, org_lex );
          throw E_ParserError();
         }

        // Исходная ситуация:
        //    AAAAABBBBBB
        //         ^
        //         N - позиция вставки символов
        //
        // После вставки символов:
        //    AAAAArrrBBBBBB
        //         ^^^

        // Длина хвоста справа от добавляемых символов, плюс терминатор.
        const int tail_len = len-N+1;

        // Хвост сдвигаем вправо.
        // Сдвигаем строки на n_char_to_add символов вправо!
        memmove( &made_string[N+n_char_to_add], &made_string[N], tail_len*sizeof(*made_string) );

        // Вписываем символы RRR
        memmove( &made_string[N], &drv[i_char], n_char_to_add*sizeof(*made_string) );

        if( n_char_to_add==1 )
         i++;
        else
         i+=(n_char_to_add+2);

        i_dest+=n_char_to_add;

//gram.GetIO().merr().printf( "DEBUG n_char_to_add=%d i=%d drv=%us made_string=%us\n", n_char_to_add, i, drv, made_string );

        break;
       }

      default:
       gram.GetIO().merr().printf(
                                  "Unrecognized wordform creation command %uc in string [%us], base form=[%us]\n"
                                  , ch, drv, org_lex
                                 );
      throw E_ParserError();
     }
   }
  else
   {
    // Неверная команда в строке...
    gram.GetIO().merr().printf(
                               "Unrecognized wordform creation command %uc in string [%us], base form=[%us]\n"
                               , ch, drv, org_lex
                              );
    throw E_ParserError();
   }

 made_string[i_dest] = 0;

 if( !i_dest )
  {
   // Result is empty lexem - this is invalid.
   gram.GetIO().merr().printf(
                              "\nInvalid result of aplying the forming "
                              "command [%us] on lexem [%us]: result empty.\n"
                              , drv, org_lex
                             );
   throw E_ParserError();
  }

 // Собираем лексему-результат...
 Lexem ret( made_string );

 int id_language=UNKNOWN;
 if( !lem::is_quantor(id_class) )
  {
   const SG_Class &c = gram.GetDict().GetSynGram().GetClass( id_class );
   id_language = c.GetLanguage();
  }
  
 gram.GetDict().GetLexAuto().TranslateLexem(ret,true,id_language);

 return ret;
}


/***********************************************************************
 Отыскиваем таблицу формообразования по её коду (условному названию).
 Если найти не удалось, то возвращаем UNKNOWN - далее это скорее всего
 приведет к исключительной ситуации.
************************************************************************/
int SG_DeclensionAutomat::FindDecl( const lem::UCString &name )
{
 std::map<UCString,int>::const_iterator it = name2id.find( to_lower(name) );
 if( it!=name2id.end() )
  return it->second;
 else
  return UNKNOWN; 
}



const SG_DeclensionTable& SG_DeclensionAutomat::GetDecl(
                                                        const UCString &entry_name,
                                                        int iclass
                                                       )
{
 lem::MCollect<int> ids;
 finder->Find( iclass, entry_name, ids );
 if( !ids.empty() )
  {
   return GetDecl(ids.front());
  } 

 lem::MemFormatter mem;
 mem.printf( "Could not find declension table for entry %us", entry_name.c_str() );
 throw E_BaseException(mem.string());
}


// ************************************************
// Возвращает индексы всех подходящих автопарадигм
// ************************************************
void SG_DeclensionAutomat::FindDecl(
                                    const UCString &entry_name,
                                    lem::MCollect<int>& ids
                                   )
{
 finder->Find( ANY_STATE, entry_name, ids );
 return;
}

void SG_DeclensionAutomat::push_back( SG_DeclensionTable *p )
{
 LEM_CHECKIT_Z(p!=NULL);

 int id = -100-CastSizeToInt(tables.size());
 tables.push_back(p);

 for( lem::Container::size_type i=0; i<p->GetNames().size(); ++i )
  {
   lem::UCString xname = lem::to_lower(p->GetNames()[i]);

   if( name2decl.find(xname)!=name2decl.end() )
    {
     lem::MemFormatter mem;
     mem.printf( "Paradigma name %us is already in use", p->GetNames()[i].c_str() );
     throw lem::E_BaseException( mem.string() );
    }
  } 

 if( !p->GetCondition().Empty() && store_auto_tables )
  {
   id = storage->StoreParadigma(*p);
  }

 for( lem::Container::size_type i=0; i<p->GetNames().size(); ++i )
  {
   lem::UCString xname = lem::to_lower(p->GetNames()[i]);
   name2decl.insert( std::make_pair( xname, p ) );
   name2id.insert(  std::make_pair( xname, id ) );
  } 

 id2decl.insert( std::make_pair( id, p ) );

 if( !p->GetCondition().Empty() )
  {
   finder->Add( p->GetCondition(), p->GetClass(), id );
  }

 return;
}


const SG_DeclensionTable& SG_DeclensionAutomat::GetDecl( int id )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs_id2decl);
 #endif
 
 std::map<int, const SG_DeclensionTable*>::const_iterator it = id2decl.find(id);
 if( it==id2decl.end() )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif
   
   SG_DeclensionTable *p = storage->GetParadigma(id);
   tables.push_back(p);
   id2decl.insert( std::make_pair(id,p) );

   for( lem::Container::size_type i=0; i<p->GetNames().size(); ++i )
    {
     name2decl.insert( std::make_pair( lem::to_lower(p->GetNames()[i]), p ) );
     name2id.insert(  std::make_pair( lem::to_lower(p->GetNames()[i]), id ) );
    }

   return *p;
  }
 else
  {
   return *it->second;
  }
}


void SG_DeclensionAutomat::Save_SQL( lem::OFormatter &out, lem::OFormatter &alters, const SQL_Production &sql_version ) const
{
 int id_form=1, id_name=1;

 lem::Ptr<LS_ResultSet> rs_paradigmas( storage->ListParadigmas() );
 while( rs_paradigmas->Fetch() )
  {
   int id = rs_paradigmas->GetInt(0);
   lem::Ptr<SG_DeclensionTable> p( storage->GetParadigma(id) );

   lem::UFString matcher = sql_version.SqlStr(p->GetCondition().ToString());

   lem::UFString attrs;
   for( lem::Container::size_type i=0; i<p->attrs().size(); ++i )
    {
     if( i>0 )
      attrs += L' ';

     attrs += lem::format_str( L"%d:%d", p->attrs()[i].GetCoord().GetIndex(), p->attrs()[i].GetState() ).c_str();
    }

   out.printf( "INSERT INTO paradigma( id, front_name, r_condition, id_class, attrs ) VALUES ( %d, '%us', '%us', %d, '%us' );\n",
    id, lem::to_upper(p->GetName()).c_str(), matcher.c_str(), p->GetClass(), attrs.c_str() );

   for( lem::Container::size_type i=0; i<p->GetNames().size(); ++i, ++id_name )
    {
     out.printf( "INSERT INTO paradigma_name( id, id_paradigma, name, uname ) VALUES ( %d, %d, '%us', '%us' );\n",
      id_name, id, p->GetNames()[i].c_str(), lem::to_upper(p->GetNames()[i]).c_str() );
    }

   for( lem::Container::size_type i=0; i<p->GetForms().size(); ++i, ++id_form )
    {
     const SG_DeclensionForm & f = * p->GetForms()[i];
     
     lem::UFString dims;
     for( lem::Container::size_type i=0; i<f.GetDim().size(); ++i )
      {
       if( i>0 )
        dims += L' ';

       dims += lem::format_str( L"%d:%d", f.GetDim()[i].GetCoord().GetIndex(), f.GetDim()[i].GetState() ).c_str();
      }

     lem::UFString generator( sql_version.SqlStr( lem::UFString(f.GetLexemGenerator().c_str()) ) );
     lem::UFString condition_str( sql_version.SqlStr(f.GetConditionStr()) );
     lem::UFString flexer_flags( sql_version.SqlStr(f.GetFlexerFlagsStr()) );

     out.printf( "INSERT INTO paradigma_form( id, id_paradigma, lexem_generator, rx_condition, flexer_flags, dims ) VALUES ( %d, %d, '%us', '%us', '%us', '%us' );\n",
      id_form, id, generator.c_str(), condition_str.c_str(), flexer_flags.c_str(), dims.c_str() );
    }

   out.eol();
  }

 return;
}
