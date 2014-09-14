// -----------------------------------------------------------------------------
// File SG_AUTOM.CPP
//
// (c) by Elijah Koziev
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
//
// Класс SynGram - контейнер для Синтаксической Грамматики (Лексикона и отчасти
// Семантикона). Прежде всего, это хранилище словарных статей. Отчасти -
// грамматическая сеть, определяющая связи грамматических форм.
//
// Дополнительная информация http://www.solarix.ru/for_developers/docs/sg.shtml
//
// 30.04.2006 - макс. емкость словаря увеличена до 700,000 лексем
// 10.05.2006 - макс. емкость словаря увеличена до 1,000,000 лексем
//
// 19.05.2006 - повторное задание калибратора теперь не считается ошибкой.
// 23.09.2006 - изменен бинарный формат словаря для версии Pro
// 26.05.2007 - в версии >= 3.2 тезаурус сохраняется в отдельном файле.
// 10.02.2009 - оптимизировано определение, что лексема может являться
//              первой частью мультилексемы: IsMultiLexemBegin
// 02.03.2009 - метод GetPrefixTree строит и возвращает префиксное дерево
//              для поиска словоформ по их начальным фрагментам.
// 15.02.2010 - добавлена загрузка фразовых статей
// 21.08.2010 - рефакторинг кода - убираем неиспользуемые классы
// 26.08.2010 - переопределение фразовой статьи не считается ошибкой,
//              если в опциях компиляции стоит -entry_redefinition=true
// 18.11.2010 - переработка хранилища словарных статей
// 03.11.2012 - добавлена загрузка определений word_aux из исходников.
// -----------------------------------------------------------------------------
//
// CD->06.03.1996
// LC->03.11.2012
// --------------

#include <lem/config.h>

#include <lem/conversions.h>
#include <lem/sol_io.h>
#include <lem/logfile.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/AuxFormTypes.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/ThesaurusStorage.h>
#include <lem/solarix/PhraseEntries.h>
#include <lem/solarix/sg_defs.h>
#include <lem/solarix/PhraseEnumerator.h>
#include <lem/solarix/PhraseNoteEnumerator.h>
#include <lem/solarix/WordLinkEnumerator.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/PartsOfSpeech.h>
#include <lem/solarix/SG_Coordinates.h>
#include <lem/solarix/PartOfSpeechEnumerator.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntryEnumerator.h>
#include <lem/solarix/WordFormEnumerator.h>
#include <lem/solarix/CoordEnumerator.h>
#include <lem/solarix/LanguageEnumerator.h>
#include <lem/solarix/CriteriaInStorage.h>
#include <lem/solarix/LanguageUsage.h>
#include <lem/solarix/prefix_tree.h>
#include <lem/solarix/dsa_main.h>
#include <lem/solarix/Paradigma.h>
#include <lem/solarix/SG_Calibrator.h>
#include <lem/solarix/MetaEntry.h>
#include <lem/solarix/ExactWordEntryLocator.h>
#include <lem/solarix/sg_autom.h>


using namespace std;
using namespace lem;
using namespace Solarix;

SynGram::SynGram( Dictionary & dict, const Dictionary_Config &cfg )
:Grammar(SOL_SG_INDEX)
, storage(NULL)
, word_entries(NULL)
{
 do_delete_storage = false;
 net = new SG_Net(cfg);
 net->StoreSG(this);

 DSA = new SG_DeclensionAutomat(this);

 param = new CriteriaInStorage();
 aux_form_types = new AuxFormTypes();
 aclass = new PartsOfSpeech(this);
 coord = new SG_Coordinates(this);
 langs = new Languages(this);
 lang_usage = new LanguageUsage(this);

 entries_beg_pos = 0;

 #if defined SOL_CAA
 prefix_tree = NULL;
 #endif

 internal_offset_buffer = cfg.internal_offset;

 return;
}

SynGram::~SynGram(void)
{
 lem_rub_off(DSA);
 lem_rub_off(langs);
 lem_rub_off(word_entries);
 lem_rub_off(net);
 lem_rub_off(aux_form_types);
 lem_rub_off(lang_usage);

 #if defined SOL_CAA
 lem_rub_off(prefix_tree);
 #endif

 if( do_delete_storage )
  delete storage;

 return;
}


void SynGram::SetEntries( WordEntries *x )
{
 lem_rub_off(word_entries);
 word_entries=x;
 word_entries->CreateDefaultEntries();
 return;
}


void SynGram::SetStorage( LexiconStorage *stg, bool _do_delete )
{
 LEM_CHECKIT_Z(stg!=NULL);

 if( do_delete_storage )
  delete storage;

 storage = stg;
 do_delete_storage = _do_delete;

 static_cast<CriteriaInStorage*>(param)->Connect(storage);
 aux_form_types->Connect(storage);
 langs->Connect(storage);
 lang_usage->Connect(storage);
 static_cast<PartsOfSpeech*>(aclass)->Connect(storage);
 static_cast<SG_Coordinates*>(coord)->Connect(storage);

 DSA->Connect(stg);

 return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
/***********************************************************************
   Необходимо определить тип находящегося в файле Словаря структурного
 элемента и загрузить его в свои списки. Возвращаем true, если это
 удалось, false в противном случае. Метод вызывается классом Automaton
 через механизм перегрузки виртуальных функций.
************************************************************************/
bool SynGram::ProcessLexem(
                           const BethToken& t,
                           Macro_Parser& txtfile,
                           const Binarization_Options &options
                          )
{
 // Мы перегрузили также и парсер класса Grammar, поэтому дадим ему шанс
 // распознать конструкцию.
 if( Grammar::ProcessLexem(t,txtfile,options) )
  return true;

 if( ProcessLexem2( t, txtfile, options ) )
  return true;

 switch(t.GetToken())
  {
   case B_AUTOMAT:
   {
    BethToken t = txtfile.read();

    if( t.GetToken() == B_NET )
     {
      Get_Net().LoadTxt(txtfile,options);
     }
    
    return true;
   }
  }

 // Распознать не удалось.
 return false;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
bool SynGram::ProcessLexem2(
                            const BethToken& t,
                            Macro_Parser& txtfile,
                            const Binarization_Options &options
                           )
{
 if( t.string().eqi(L"wordform_score") )
  {
   LoadFrequency( txtfile, true );
   return true;
  }


 switch(t.GetToken())
  {
   case B_OMONYM:
    LoadOmonym( txtfile, options );
    return true;

   case B_LINK:
    Load_Link( txtfile, options );
    return true;

   case B_PHRASE:
    LoadPhrase( txtfile, options );
    return true;

   case B_CALIBRATE:
    LoadFrequency( txtfile, false );
    return true;

   case B_PARADIGMA:
    {
     // Таблица формообразования.
     SG_DeclensionTable *decl = new SG_DeclensionTable;

     decl->LoadTxt( txtfile, *this, false );

     if( !decl->IsAuto() )
      {
       // Проверим уникальность данной таблицы.
       for( lem::Container::size_type i=0; i<decl->GetNames().size(); ++i )
        {
         if( DSA->FindDecl( decl->GetNames()[i] ) != UNKNOWN )
          {
           GetIO().merr().printf(
                                 "\n%vfCDeclension table [%us] redefinition in Lexicon%vn\n"
                                 , decl->GetName().c_str()
                                );

           lem::Iridium::Print_Error( txtfile );
           throw E_ParserError();
          }
        }
      }

     decl->Translate( GetDict().GetGraphGram() );
     DSA->push_back( decl );
     return true;
    }

   case B_QUANTOR:
    {
     // особая словарная статья - определение грамматического квантора
     LoadQuantor( txtfile, false, options );
     return true;
    }

   case B_LANGUAGE:
    {
     // Load new language descriprion
     langs->LoadTxt( txtfile );
     return true;
    }

   case B_TAG:
    {
     LoadEntryTag(txtfile,options);
     return true;
    }
  }

 if( t.string().eqi( L"auxformtypes" ) )
  {
   aux_form_types->LoadTxt(txtfile);
   return true;
  }
 else if( t.string().eqi(L"aux_word") )
  {
   LoadAuxWord( txtfile );
   return true;
  }
 else if( t.string().eqi(L"metaentry") )
  {
   LoadEntryGroup( txtfile );
   return true;
  }

 bool lang_usage=false;
 bool is_input=false, is_output=false, is_default=false;
 if( t.string().eqi(L"default_input_language") )
  {
   lang_usage=is_input=is_default=true;
  }
 else if( t.string().eqi(L"default_output_language") )
  {
   lang_usage=is_output=is_default=true;
  }
 else if( t.string().eqi(L"input_language") )
  {
   lang_usage=is_input=true;
  }
 else if( t.string().eqi(L"output_language") )
  {
   lang_usage=is_output=true;
  }
 else if( t.string().eqi(L"additional_language") )
  {
   lang_usage=true;
  }
 
 if( lang_usage )
  {
   txtfile.read_it( B_EQUAL );

   lem::Iridium::BethToken lang_name = txtfile.read();
   const int id_lang = languages().Find(lang_name);
   if( id_lang==UNKNOWN )
    {
     GetIO().merr().printf( "\n%vfCUnknown language [%us]%vn\n", lang_name.string().c_str() );
     lem::Iridium::Print_Error( lang_name, txtfile );
     throw E_ParserError();
    }

   storage->StoreLanguageUsage( id_lang, is_input, is_output, is_default );
   return true;
  } 

 return false;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynGram::LoadEntryGroup( Macro_Parser& txtfile )
{
 MetaEntry e;
 e.LoadTxt( *this, txtfile );
 e.Store(storage);

 return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynGram::LoadAuxWord( Macro_Parser& txtfile )
{
 lem::Iridium::BethToken t_src = txtfile.read();
 lem::UCString src(t_src.string());

 // вообще говоря, не все типы доп. информации нуждаются в нормализации символов. для этого нужно
 // вписать доп. поля в таблицу aux_form_type. Но пока сделаем просто приведение к верхнему регистру,
 // если перед строкой нет символа @.
 bool normalize = src.front()==L'@';

 if( normalize )
  {
   src = src.c_str()+1;
   src.strip_quotes();
  }
 else
  {
   src.strip_quotes();
  }

 txtfile.read_it( B_OSPAREN );
 lem::Iridium::BethToken t_type = txtfile.read();
 txtfile.read_it( B_CSPAREN );

 const int type_id = (*aux_form_types)[t_type.string()];
 if( type_id==UNKNOWN )
  {
   GetIO().merr().printf( "\n%vfCUnknown aux type [%us]%vn\n", t_type.string().c_str() );
   lem::Iridium::Print_Error( t_type, txtfile );
   throw E_ParserError();
  }

 if( !normalize && aux_form_types->DoUpperCase(type_id) )
  {
   src.to_upper();
  }

 txtfile.read_it( B_EQUAL );
 
 lem::Iridium::BethToken t_res = txtfile.read();
 lem::UFString res(t_res.GetFullStr());
 res.strip_quotes();

 storage->AddAuxWord( src, type_id, res );

 return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynGram::LoadFrequency( Macro_Parser & txtfile, bool wordform )
{
 // Загружаем калибратор.
 SG_calibrator c(*this,GetIO(),txtfile,wordform);

 // Проверим уникальность.
 if( c.IsWordEntry() )
  {
   if( wordfreq_filename.IsNull() )
    {
     wordfreq_filename = new lem::Path(lem::Path::GetTmpFilename());
     wordfreq_file = new lem::BinaryWriter( *wordfreq_filename );
    }

   c.SaveBin( *wordfreq_file );
  }
 else if( c.IsWordForm() )
  {
   if( wordfreq_filename.IsNull() )
    {
     wordfreq_filename = new lem::Path(lem::Path::GetTmpFilename());
     wordfreq_file = new lem::BinaryWriter( *wordfreq_filename );
    }

   c.SaveBin( *wordfreq_file );
  }
 else
  {
   LEM_STOPIT;
  }
 
 return;
}
#endif




#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynGram::LoadEntryTag(
                           Macro_Parser &txtfile,
                           const Binarization_Options &options
                          )
{
 // Формат:
 // 1. Явное указание значения координаты
 //
 //    tag класс:статья { координатная_пара координатная_пара ... }
 //
 // 2. Импорт значения координаты из связанной по тезаурусу статьи
 //
 //    tag класс:статья { координата:<связка> координата:<связка> ... }
 // 
 // 3. Транскоординатный импорт состояний из связанной по тезаурусу статьи
 //
 //    tag класс:статья { координата:<связка>:координата_исх ... }


 BethToken class_name = txtfile.read();
 txtfile.read_it( B_COLON );
 UCString entry_name = Solarix::sol_read_multyname( GetIO(), txtfile, B_OFIGPAREN );
 
 const int id_class = FindClass(class_name.string());
 if( id_class==UNKNOWN )
  {
   lem::Iridium::Print_Error( class_name.GetBegin(), txtfile );
   GetIO().merr().printf( "Class [%vfE%us%vn] is not defined\n", entry_name.c_str() );
   throw E_ParserError();
  }  

 lem::MCollect<int> id_entries;

 // Для метастатей - особый подход.
 int id_metaentry = FindMetaEntry( entry_name, id_class );
 if( id_metaentry!=UNKNOWN )
  {
   GetStorage().GetMetaEntryItems( id_metaentry, id_entries );
  }
 else
  {
   // Найдем эту статью
   const int ie = FindEntry( entry_name, id_class, false );
   if( ie==UNKNOWN )
    {
     lem::Iridium::Print_Error( class_name.GetBegin(), txtfile );
     GetIO().merr().printf( "Entry [%vfE%us:%us%vn] is not defined\n", class_name.c_str(), entry_name.c_str() );
     throw E_ParserError();
    }

   id_entries.push_back(ie);
  }

 #if LEM_DEBUGGING==1
// if( entry_name==L"ПОВЕСТИ" )
//  lem::mout->printf("");
 #endif

 while( !txtfile.eof() )
  {
   BethToken coord_name = txtfile.read();

   lem::zbool replace;

   if( coord_name==B_CFIGPAREN )
    break;

   if( coord_name.eqi(L"replace") )
    {
     replace=true;
     txtfile.read_it( B_COLON );
     coord_name = txtfile.read();
    }

   GramCoordAdr icoord = FindCoord(coord_name.c_str()); 
   if( icoord.GetIndex()==UNKNOWN )
    {
     lem::Iridium::Print_Error( coord_name.GetBegin(), txtfile );
     GetIO().merr().printf( "Coordinate [%vfE%us%vn] is not defined\n", coord_name.c_str() );
     throw E_ParserError();
    } 

   lem::MCollect<int> istate;

   bool via_link=false;

   BethToken b1 = txtfile.read();
   if( b1==B_COLON )
    {
     if( txtfile.read()==B_OTRIPAREN )
      {
       via_link=true;
      }
    }

   for( lem::Container::size_type q=0; q<id_entries.size(); ++q )
    {
     txtfile.seekp(b1);

     int ie = id_entries[q];

     if( via_link )
      {
       // импорт состояния координаты из связанной по тезаурусу статьи
       txtfile.read_it(B_COLON);
       Tree_Link link( txtfile, *this );
   
       GramCoordAdr icoord_src = icoord; // по умолчанию берем туже координату
   
       // Дальше еще может идти явное указание координаты-источника
       if( txtfile.pick()==B_COLON )
        {
         txtfile.read_it( B_COLON );
         BethToken coord2_name = txtfile.read();
         icoord_src = FindCoord(coord2_name.c_str()); 
         if( icoord_src.GetIndex()==UNKNOWN )
          {
           lem::Iridium::Print_Error( coord2_name.GetBegin(), txtfile );
           GetIO().merr().printf( "Coordinate [%vfE%us%vn] is not defined\n", coord2_name.c_str() );
           throw E_ParserError();
          } 
   
         // Проверим, что координаты эквивалентны по набору состояний.
         if( coords()[icoord.GetIndex()]!=coords()[icoord_src.GetIndex()] )
          {
           lem::Iridium::Print_Error( coord2_name.GetBegin(), txtfile );
           GetIO().merr().printf( "Coordinates [%vfE%us%vn] and [%vfE%us%vn] are not compatible\n", coord_name.c_str(), coord2_name.c_str() );
           throw E_ParserError();
          }
        }
   
       const int key0 = ie;
       const int key1 = Get_Net().FindSingleLinked( key0, link ).first;
   
       if( key1==UNKNOWN )
        {
         GetIO().merr().printf( "Warning: can not resolve link " );
         link.SaveTxt( GetIO().merr(), *this );
         GetIO().merr().printf( " from %vfE%us%vn when importing the tag %vfE%us%vn\n", entry_name.c_str(), coord_name.c_str() );
        }
       else
        {
         const SG_Entry &e1 = GetEntry(key1);
        
         // Ищем значение тэга у статьи
         istate = e1.GetAttrStates( icoord_src );
        }
      }
     else
      {
       // Явное задание состояния
   
       // Для бистабильных координат сам факт упомянания координаты означает, что ее состояние равно true
       if( coords()[icoord.GetIndex()].IsBistable() )
        {
         istate.push_back(1);
        }   
       else
        {
         txtfile.read_it(B_COLON);
   
         BethToken state_name = txtfile.read();
   
         int iistate = coords()[icoord.GetIndex()].FindState(state_name.string());
     
         if( iistate==UNKNOWN )
          {
           lem::Iridium::Print_Error( state_name.GetBegin(), txtfile );
           GetIO().merr().printf( "State [%us] is not defined for coordinate [%us]\n", state_name.c_str(), coord_name.c_str() );
           throw E_ParserError();
          } 
   
         istate.push_back( iistate );  
        } 
      }

     if( !istate.empty() )
      {
       SG_Entry &e = word_entries->GetEntryForChange(ie);
   
       if( replace )
        {
         // Удалим все имеющиеся состояния этой координаты
         e.attrs().RemoveStates(icoord);
        }
   
       for( lem::Container::size_type j=0; j<istate.size(); ++j )
        {
         GramCoordPair tag_pair( icoord, istate[j] );
         e.SetAttr(tag_pair);
        }
   
       // Для всех форм статьи меняем координату - добавляем координатную пару для тэга
       for( lem::Container::size_type i=0; i<e.forms().size(); ++i )
        {
         SG_EntryForm & f = e.forms()[i];
   
         const CP_Array& old_coords = f.coords();
         CP_Array new_coords(old_coords);
   
         if( replace )
          {
           new_coords.RemoveStates( icoord );
          }
   
         for( lem::Container::size_type j=0; j<istate.size(); ++j )
          {
           GramCoordPair tag_pair( icoord, istate[j] );
   
           // На всякий случай проверим, что этот тэг не установлен уже для форм.
           if( new_coords.find(tag_pair)==UNKNOWN )
            {
             // Этого тэга еще нет.
             new_coords.push_back(tag_pair);
            }
          }
   
         if( new_coords!=old_coords )
          {
           const CP_Array *new_ptr = word_entries->AddCoordPairs(new_coords);
           f.ResetCoords(new_ptr);
          }
        }
      }
    }
  }

 return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
// **************************************************
// Загрузка определения фразовой статьи
// **************************************************
void SynGram::LoadPhrase(
                         Macro_Parser &txtfile,
                         const Binarization_Options &options
                        )
{
 // Общий формат:
 // phrase @ "произвольный текст"
 // { дополнительные данные }
 //
 // Опциональный символ @ запрещает какую-либо модификацию текста при сохранении,
 // например - приведение к верхнему регистру.

 // сначала - текстовое содержимое фразы
 lem::UFString phrase;
 phrase.reserve(128);

 while( !txtfile.eof() )
  {
   BethToken t = txtfile.read();
   if( t.GetToken()==B_OFIGPAREN )
    break;
   
   if( !phrase.empty() )
    phrase.Add_Dirty(L' ');

   UFString ts( t.GetFullStr() );
   ts.strip(L'"');
   phrase.Add_Dirty( ts );
  }

 phrase.calc_hash();

 if( phrase.front()==L'@' )
  {
   // Спецсимвол @ заставляет запомнить строку в виде "как есть"
   phrase.remove(0);
   phrase.trim();
  }
 else
  {
   phrase.strip(L'"');
   phrase.trim();
   phrase.to_upper();
  }


 // ищем имеющееся определение этой фразовой статьи
 int te_id = GetStorage().FindPhrase(phrase,true);

 bool skip=false;

 if( te_id!=UNKNOWN )
  {
   // Повторное определение фразовой статьи.
   if( options.entry_redefinition )
    {
     // разрешено - просто напишем предупреждение
     GetIO().merr().printf( "Acceptable phrase [%us] redefinition in Lexicon, found phrase id=%d\n", phrase.c_str(), te_id );
     lem::Iridium::Print_Error( txtfile, true );
     skip=true;
    }
   else
    {
     lem::Iridium::Print_Error(txtfile);
     GetIO().merr().printf( "Redefinition of phrase entry [%us], found phrase id=%d\n", phrase.c_str(), te_id );
     throw E_ParserError();
    }
  }


 // Читаем тело фразовой статьи.
 SG_Phrase te;
 te.id = te_id;
 te.text = phrase;

 if( te_id==UNKNOWN )
  {
   te_id = GetStorage().AddPhrase( te );
  }

 lem::zbool dirty;

 int syntax_flags=frz_complete_syntax_analysis;

 // В теле фразовой статьи может быть дополнительная информация, которую будем сохранять
 // в TNOTES.
 while( !txtfile.eof() )
  {
   BethToken t = txtfile.read();
   if( t.GetToken()==B_CFIGPAREN )
    break;
   
   if( t.GetToken()==B_LANGUAGE )
    {
     txtfile.read_it(B_COLON);
     BethToken lang_name = txtfile.read();

     int id_language = Find_Language( lang_name.string() );

     if( id_language==UNKNOWN )
      {
       lem::Iridium::Print_Error(lang_name,txtfile);
       GetIO().merr().printf(
                             "Unknown language [%us] is specified for class [%us]\n"
                             , lang_name.string().c_str()
                             , GetName().c_str() 
                            );
       throw E_ParserError();
      }
     
     te.id_language = id_language;
     dirty = true;
    }
   else if( t.GetToken()==B_CLASS )
    {
     txtfile.read_it(B_COLON);
     BethToken class_name = txtfile.read();
     int id_class = FindClass(class_name.string());
     if( id_class==UNKNOWN )
      { 
       lem::Iridium::Print_Error(class_name,txtfile);

       GetIO().merr()
               .printf(
                    "The class [%vfE%us%vn] is not previously declared in grammar\n"
                    , class_name.c_str()
                   );
  
       throw E_SG_NoClass(class_name.string());
      }

     te.id_class = id_class;

     if( te.id_language==UNKNOWN )
      {
       te.id_language = GetClass(id_class).GetLanguage();
      }

     dirty = true;
    }
   else if( t.GetToken()==B_FLAG )
    {
     // Считываем значение основного флагов, управляющих анализом фразы.
     // Это значение может быть образовано OR-слиянием множества чисел,
     // соединяемых токеном '|'.
     txtfile.read_it( B_COLON );

     while(!txtfile.eof())
      {
       syntax_flags |= txtfile.read_int();
       const BethToken& ttt = txtfile.read();
       if( ttt.GetToken() != B_ORSIGN )
        {
         txtfile.seekp(ttt);
         break;
        }
      }

     te.syntax_flags = syntax_flags;
     dirty=true;
    }
   else if( t.string()==L"pivot" )
    {
     BethToken t2 = txtfile.read();
     UFString str( t2.GetFullStr() );
     str.strip(L'"');

     // В этой строке символы | дают границы слов,
     // кроме того [ и ] определяют ведущее слово
     // Особый случай - если строка является целым числом, тогда это
     // явное задание номера ведущего слова, исползуемое в некоторых
     // случаях при автогенерации текста тезауруса.

     int pivot_iword=UNKNOWN;

     if( lem::is_int(str) )
      {
       pivot_iword = lem::to_int(str);
      }
     else
      { 
       lem::Collect<lem::UFString> toks;
       lem::parse( str, toks, L"|" );
       for( lem::Container::size_type j=0; j<toks.size(); ++j )
        {
         const lem::UFString &tok = toks[j];
         if( tok.front()==L'[' && tok.back()==L']' )
          {
           pivot_iword = CastSizeToInt(j);
           break;
          }  
        }
      }
     
     if( pivot_iword==UNKNOWN )
      {
       GetIO().merr().printf(
                             "Pivot word is not defined by [ and ] in phrasal entry body\n",
                             phrase.c_str()
                            );
       lem::Iridium::Print_Error( t2, txtfile );
       throw Solarix::E_Solarix(); 
      }

     if( !skip )
      {
       lem::UFString txt = to_ustr(pivot_iword).c_str();
       GetStorage().AddPhraseNote( te_id, Solarix::SynGram::PivotNote, txt );
      }
    }
   else
    {
     GetIO().merr().printf(
                           "Unknown token [%us] in phrasal entry body\n",
                           t.c_str()
                          );
     lem::Iridium::Print_Error( txtfile );
     throw Solarix::E_Solarix(); 
    } 
  }
  
 if( !skip && dirty )
  {
   // сохраним изменения в теле фразовой статьи
   GetStorage().UpdatePhrase( te );
  }

 if( !GetDict().GetCurrentOriginator().empty() && lem::LogFile::IsOpen() )
  {
   lem::LogFile::logfile->printf(
                                 "ORIGINATOR::UPDATE sg_tentry SET te_modifier='%us' WHERE te_id=%d;\n",
                                 GetDict().GetCurrentOriginator().c_str(), te_id
                                );
  } 

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynGram::LoadOmonym(
                         Macro_Parser &txtfile,
                         const Binarization_Options &options
                        )
{
 // Объявление омонима:
 // omonym add Класс:Статья{}
 //
 // Удаление объявления омонима
 // omonym remove Класс:Статья{}

 const BSourceState back = txtfile.tellp();

 lem::UCString oper = txtfile.read().string(); 

 const BethToken class_name = txtfile.read();
 int iclass=FindClass(class_name.string());
  if( iclass == UNKNOWN )
   {
    lem::Iridium::Print_Error( class_name, txtfile );
    GetIO().merr().printf(
                          "The class [%us] is not previously declared in grammar\n"
                          , class_name.c_str()
                         );
    throw E_ParserError();
   }

 txtfile.read_it( B_COLON );
 Solarix::Lexem entry_name = sol_read_multyname(GetIO(),txtfile,B_OFIGPAREN);
 GetDict().GetLexAuto().TranslateLexem( entry_name, true );

 std::pair<int,lem::UCString> p(iclass,entry_name);
 std::set< std::pair<int,lem::UCString> >::iterator it = omonyms.find(p);
 if( oper.eqi(L"add") )
  {
   // Во избежание накладок проверим, что объявляемый омоним еще ни разу
   // не был реализован статьями.
   if( FindEntry( entry_name, iclass, false )!=UNKNOWN )
    {
     lem::Iridium::Print_Error( back, txtfile );
     GetIO().merr().printf(
                           "Can not add omonym declaration for [%us] because of existing word entry declaration\n"
                           , entry_name.c_str()
                          );
     throw E_ParserError();
    }

   omonyms.insert(p);

   // также сохраняем информацию о известных омонимах в словарной БД, чтобы при пересборке
   // правил быстро проверять однозначность указания на словарные статьи.
   omonyms_history.insert(p);
   storage->StoreOmonym( entry_name, iclass );
  }
 else if( oper.eqi(L"remove") )
  {
   if( it!=omonyms.end() )
    {
     omonyms.erase(p);
    }
   else
    {
     lem::Iridium::Print_Error( back, txtfile );
     GetIO().merr().printf(
                           "Can not remove omonym declaration for [%us] because it was not added yet\n"
                           , entry_name.c_str()
                          );
     throw E_ParserError();
    } 
  }
 else
  {
   lem::Iridium::Print_Error( back, txtfile );
   GetIO().merr().printf(
                         "Omonym operation [%us] is unknown\n"
                         , oper.c_str()
                        );
   throw E_ParserError();
  }

 txtfile.read_it(B_CFIGPAREN);

 return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynGram::Load_Link(
                        Macro_Parser &txtfile,
                        const Binarization_Options &options
                       )
{
 const BSourceState back = txtfile.tellp();
 if( txtfile.read().GetToken() == B_GENERATOR )
  {
   // синтаксис
   // link generator ... 
   // определяет правило автогенерации связки
   Load_Link_Generator( txtfile, options );
  }
 else
  {
   // одна связь для тезауруса
   txtfile.seekp(back);
   net->Load_Declaration( txtfile, options );
  }

 return;
}

void SynGram::Load_Link_Generator(
                                  Macro_Parser &txtfile,
                                  const Binarization_Options &options
                                 )
{
 Link_Generator *g = new Link_Generator;
 g->LoadTxt(txtfile,*this,options);
 link_generators.push_back(g);
 return;
}

#endif



/*
#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynGram::RegisterHashes(
                             int iEntry,
                             const MSet<uint8_t> &hash_list
                            )
{
 for( lem::Container::size_type i=0; i<hash_list.size(); i++ )
  len_group[ hash_list[i] ].push_back( iEntry );

 return;
}
#endif
*/

#if defined SOL_LOADTXT && defined SOL_COMPILER

static bool EqualsFromPos( const lem::UCString& form_string, int ia, const lem::UCString & base_string, int ib )
{
 int lena = form_string.length();
 int lenb = base_string.length();

 while( ia<lena && ib<lenb )
  {
   if( form_string[ia]!=base_string[ib] )
    return false;

   ia++;
   ib++;
  }

 return true;
}

static bool DetectInternalFlexion( const lem::UCString& base_form, const lem::UCString& form )
{
 int len_base = base_form.length();
 int len_form = form.length();

 int ibase=0, iform=0;
 while( ibase<len_base && iform<len_form )
  {
   if( base_form[ibase]==form[iform] )
    {
     ibase++;
     iform++;
    }
   else
    {
     if( iform<len_form-1 && ibase<len_base-1 )
      return EqualsFromPos( form, iform, base_form, ibase+1 );
     else
      return false;
    }
  }

 return false;
}


void SynGram::Add_Entry( SG_Entry *e )
{
/*
#if LEM_DEBUGGING==1
bool x1= DetectInternalFlexion( L"ЛОБОК", L"ЛОБКАМИ" );
bool x2= DetectInternalFlexion( L"ЛОБОК", L"ЛОБКА" );
bool x3= DetectInternalFlexion( L"ЛОБОК", L"ЛОБ" );
bool x4= DetectInternalFlexion( L"ЛОБОК", L"ЛОБОКА" );
#endif
*/
 word_entries->AddEntry(e);

 // Получим список окончаний.
 lem::MCollect<lem::UCString> endings;

 const int id_class = e->GetClass();
 if( id_class!=UNKNOWN )
  {
   const int id_language = GetClass( id_class ).GetLanguage();

   if( id_language!=UNKNOWN )
    {
     const int MIN_STEM_LEN=3;
  
     const lem::UCString & ename = e->GetName();

#if LEM_DEBUGGING==1
//if( ename==L"ЛОБОК" )
// {
//  printf( "" );
// }
#endif

     lem::UCString stem;
     for( lem::Container::size_type i=0; i<e->forms().size(); ++i )
      {
       const lem::UCString &form = e->forms()[i].name();
  
       if( stem.empty() )
        stem = form;
       else
        {
         if( !DetectInternalFlexion( ename, form ) )
          {
           if( !form.eq_beg( stem ) )
            {
             int stem_len = stem.length()-1;
             while( stem_len>=MIN_STEM_LEN )
              {
               lem::UCString new_stem = lem::left( stem, stem_len );
               if( form.eq_begi( new_stem ) )
                {
                 stem = new_stem;
                 break;
                }
  
               stem_len--;
              }
            }
          }
        }
      }
  
     // нашли стем для статьи.
     // теперь еще один проход по формам и получаем окончания.
     if( stem.length()>=MIN_STEM_LEN )
      {
       for( lem::Container::size_type i=0; i<e->forms().size(); ++i )
        {
         const lem::UCString &form = e->forms()[i].name();
         if( form.eq_beg(stem) ) // учитываем только формы без внутренней флекции.
          {
           lem::UCString ending = lem::right( form, form.length()-stem.length() );
           if( !ending.empty() )
            {
/*
if( ending==L"S " )
 {
  lem::mout->printf( "DEBUG: entry=[%us] form=[%us]\n", e->GetName().c_str(), form.c_str() );
  exit(0);
 }
*/
             storage->AddEnding( ending, id_language, e->GetFreq() );
            }
          }
        }
      }
    }
  } 

 return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynGram::LoadEntry(
                        Macro_Parser& txtfile,
                        bool is_extern,
                        const Binarization_Options &options
                       )
{
 LoadEntry( txtfile, is_extern, new SG_Entry, options );
 return;
}

void SynGram::LoadQuantor(
                          Macro_Parser& txtfile,
                          bool is_extern,
                          const Binarization_Options &options
                         )
{ LoadEntry( txtfile, is_extern, new SG_Quantor, options ); }


/***************************************************************************
 Загружаем словарную статью. Метод вызывается классом Grammar при встрече
 с ключевым словом entry либо при распознании заголовка словарной статьи
 (см. класс Base_Entry).
****************************************************************************/
void SynGram::LoadEntry(
                        Macro_Parser& txtfile,
                        bool is_extern,
                        SG_Entry *dummy,
                        const Binarization_Options &options
                       )
{
 BSourceState eb = txtfile.tellp();

 try
  {
   if( is_extern )
    {
     // прочитаем класс:имя и проверим, не является ли это вариантом известного омонима.
     lem::Iridium::BSourceState on_name = txtfile.tellp();
     dummy->LoadName( txtfile, GetDict() );
     if( IsOmonym( dummy->GetClass(), dummy->GetName() ) )
      {
       delete dummy;
       return;
      }

     txtfile.seekp( on_name );
    }

   dummy->SetKey( GetDict().GetNextKey() );
   dummy->LoadTxt(txtfile,*this,!is_extern);
   dummy->AfterFirstRead();
   dummy->PrepareAfterLoad( GetDict().GetGraphGram(), *this );

   if( dummy->GetFlags2()==UNKNOWN && !options.CheckEntryName(dummy->GetName()) )
    {
     if( lem::LogFile::IsOpen() )
      {
       lem::LogFile::logfile->printf( "Entry %us does not pass the ename filter\n", dummy->GetName().c_str() );
      }

     delete dummy;
     return;
    }

   // Проверяем уникальность статьи! Мы не допускаем повтора пары имя_статьи +
   // имя_класса.
   const int ie = FindEntry( dummy->GetName(), dummy->GetClass(), false );

   if( ie==UNKNOWN )
    {
     Add_Entry( dummy );

     if( !GetDict().GetCurrentOriginator().empty() && lem::LogFile::IsOpen() )
      {
       lem::LogFile::logfile->printf(
                                     "ORIGINATOR::UPDATE sg_entry SET modifier='%us' WHERE id=%d;\n",
                                     GetDict().GetCurrentOriginator().c_str(), dummy->GetKey()
                                    );
      } 
    }
   else
    {
     if( is_extern )
      {
       // Просто ещё раз прочитано объявление статьи.
       //
       // extern entry A : B
       //         :
       // extern entry A : B
       delete dummy;
       return;
      }

     if( !is_extern && !GetEntry(ie).IsRealized() )
      {
       // Встречена РЕАЛИЗАЦИЯ статьи, нужно заменить ей предыдущее объявление.
       // Переносим себе ключ объявления, так как на него уже могли быть
       // ссылки...
       const int new_ekey = ie;
       GetStorage().ReplaceEntryKey( dummy->GetKey(), new_ekey );
       Get_Net().GetStorage().ReplaceEntryKey( dummy->GetKey(), new_ekey );
       dummy->SetKey( new_ekey );

       word_entries->ReplaceEntry( ie, dummy );

       if( !GetDict().GetCurrentOriginator().empty() && lem::LogFile::IsOpen() )
        {
         lem::LogFile::logfile->printf(
                                       "ORIGINATOR::UPDATE sg_entry SET modifier='%us' WHERE id=%d;\n",
                                       GetDict().GetCurrentOriginator().c_str(), dummy->GetKey()
                                      );
        }

       return;
      }

     if( !is_extern && GetEntry(ie).IsRealized() )
      {
       // Повторная реализация словарной статьи.
       if( options.entry_redefinition )
        {
         GetIO().merr().printf(
                               "Acceptable entry [%us:%us] redefinition in Lexicon\n"
                               , classes()[ dummy->GetClass() ].GetName().c_str()
                               , dummy->GetName().c_str()
                              );
         lem::Iridium::Print_Error( txtfile, true );
         delete dummy;
         dummy=NULL;  
        }
       else
        {
         std::pair<int,lem::UCString> p( dummy->GetClass(), dummy->GetName() );
         if( omonyms.find(p)==omonyms.end() )
          {
           GetIO().merr().printf(
                                 "Entry [%us:%us] redefinition in Lexicon\n"
                                 , classes()[ dummy->GetClass() ].GetName().c_str()
                                 , dummy->GetName().c_str()
                                );
           lem::Iridium::Print_Error( txtfile );
           throw E_ParserError();
          }
         else
          {
           Add_Entry( dummy );

           if( !GetDict().GetCurrentOriginator().empty() && lem::LogFile::IsOpen() )
            {
             lem::LogFile::logfile->printf(
                                           "ORIGINATOR::UPDATE sg_entry SET modifier='%us' WHERE id=%d;\n",
                                           GetDict().GetCurrentOriginator().c_str(), dummy->GetKey()
                                          );
            } 
          } 
        }
      }
    }
  }
 catch( ... )
  {
   lem::Iridium::Print_Error( eb, txtfile );

   if( dummy && &dummy->GetName()!=NULL )
    {
     GetIO().merr().printf(
                           "Error parsing entry [%us:%us] definition\n"
                           , dummy->GetClass()==UNKNOWN ? L"" : classes()[ dummy->GetClass() ].GetName().c_str()
                           , dummy->GetName().c_str()
                          );
    }
   else
    GetIO().merr().printf( "Error parsing entry definition\n" );

   throw;
  }

 return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
/**************************************************************************
   Дозагрузка Грамматической Сети после определения всех словарных статей.
 Связано с тем, что при определении связей в грамматической сети дл
 статьи могут потребоваться ссылки вперед на еще не определенные слова.
 Поэтому считывание определений для грамматической сети при первом
 проходе откладывается, и запоминается положение в текстовом файле
 соответствующих позиций. Теперь мы возвращаемся к запомненым позициям и
 загружаем связки в грамматической сети.
***************************************************************************/
void SynGram::PostRead(
                       Macro_Parser &txtfile,
                       const Binarization_Options &options
                      )
{
 // Запоминаем текущее положение курсора чтения - чтобы затем
 // нормально продолжить загрузку Словаря.
 const BSourceState back = txtfile.tellp();
 word_entries->PostRead( txtfile, options );
 txtfile.seekp(back);
 return;
}
#endif


#if defined SOL_SAVEBIN
// *******************************************************
// Store the content of grammar into binary stream <bin>.
// This content may be loaded by ::LoadBin
// *******************************************************
void SynGram::SaveBin( lem::Stream & bin ) const
{
 Grammar::SaveBin(bin);

 int dummy_flags = sizeof(*this);
 bin.write_int(dummy_flags);

 bin.write(&ilink_type,sizeof(ilink_type));

 lem::uint8_t c=0;
 bin.write_int( internal_offset_buffer );
 for( int i=0; i<internal_offset_buffer; ++i )
  bin.write( &c, 1 ); 

 bin.write_int(0);

 lem::Stream::pos_type entries_beg_pos = bin.tellp();
 bin.write( &entries_beg_pos, sizeof(entries_beg_pos) );
 word_entries->SaveBin(bin);

 return;
}
#endif



#if defined SOL_LOADBIN
void SynGram::LoadBin( lem::Stream& bin, const Load_Options &opt )
{
 Grammar::LoadBin(bin,opt);

 int dummy_flags = bin.read_int();

 bin.read(&ilink_type,sizeof(ilink_type));

 if( internal_offset_buffer==UNKNOWN )
  {
   internal_offset_buffer = bin.read_int();
  }
 else
  {
   int dummy = bin.read_int();
  } 

 bin.move( internal_offset_buffer );

 bin.read_int();

 bin.read( &entries_beg_pos, sizeof(entries_beg_pos) );

 word_entries->LoadBin(bin);

 return;
}
#endif




/*******************************************************************************
   Поиск статьи по имени и с учетом грамматического класса.

  ВХОДНЫЕ ПАРАМЕТРЫ:

   name   - имя статьи. Если имя статьи является квантором всеобщности '*',
            то возвращается ANY_STATE.

   iclass - индекс грамматического класса, к которому должна принадлежать
            статья. Если iclass==ANY_STATE, то поиск производится дл
            статей всех классов.

   do_account_quantors - следует рассматривать лексему '*' как имя специальной
            статьи-квантора ANY_STATE (==true), или это нормальная статья с
            таким именем (==false).

  ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ - индекс статьи в списке грамматики. Если возвращено
            UNKNOWN, то статья не найдена. Если возвращено значение ANY_STATE,
            то имя статьи задано как квантор всеобщности.
*******************************************************************************/
int SynGram::FindEntry(
                       const UCString& name,
                       int iclass,
                       bool do_account_quantors
                      )
{
 if( do_account_quantors && name==sol_get_token(B_ANY) )
  return ANY_STATE;

 Lexem lname(name);

 if( !lem::is_quantor(iclass) )
  {
   const SG_Class &cls = GetClass(iclass);
   const int id_language = cls.GetLanguage();
   GetDict().GetLexAuto().TranslateLexem(lname,true,id_language);
  }
 else
  {
   GetDict().GetLexAuto().TranslateLexem(lname);
  }

 return FindEntry2( lname, iclass );
}


int SynGram::FindMetaEntry( const UCString& name, int id_class )
{
 Lexem normalized_name(name);

 const SG_Class &cls = GetClass(id_class);
 const int id_language = cls.GetLanguage();
 GetDict().GetLexAuto().TranslateLexem(normalized_name,true,id_language);

 return GetStorage().FindMetaEntry( normalized_name, id_class );
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
int SynGram::FindEntryOmonym( const Lexem& lname, int iclass, const ExactWordEntryLocator & locator )
{
 if( IsOmonym(iclass,lname) )
  {
   if( locator.Empty() )
    {
/*
     // Если слово представляет имя известного омонима, и не задан атрибут для выбора одного из омонимов - ошибка.
     lem::MemFormatter msg;
     msg.printf( "Unresolved omonym %us", lname.c_str() );
     throw E_BaseException(msg.string());
*/

     return UNKNOWN;
    }

   // Представленный атрибут действительно снимает омонимию?
   lem::MCollect<int> ekeys;

   lem::Ptr<WordEntryEnumerator> wenum( word_entries->ListEntries(lname,iclass) );
   while( wenum->Fetch() )
   {
    if( locator.Check( wenum->GetItem(), *this ) )
     ekeys.push_back( wenum->GetId() );
   }

   if( ekeys.size()>1 )
    {
/*
     // Если слово представляет имя известного омонима, и не задан атрибут для выбора одного из омонимов - ошибка.
     lem::MemFormatter msg;
     msg.printf( "Unresolved omonym %us:%us", GetClass(iclass).GetName().c_str(), lname.c_str() );
     throw E_BaseException(msg.string());
*/

     return UNKNOWN;
    }

   if( ekeys.empty() )
    return UNKNOWN;

   return ekeys.front();
  }

 return word_entries->FindEntry(lname,iclass);
}


int SynGram::FindEntryOmonym( const Lexem& lname, int iclass, const Solarix::GramCoordPair &p ) const
{
 return word_entries->FindEntryOmonym(lname,iclass,p);
}


int SynGram::FindEntryOmonym( const Lexem & lname, int iclass, const lem::MCollect<Solarix::GramCoordPair> & p )
{
 ExactWordEntryLocator locator;
 locator.pairs = p;
 return FindEntryOmonym( lname, iclass, locator );
}

#endif


int SynGram::FindEntry2( const Lexem& lname, int iclass )
{
 return word_entries->FindEntry( lname, iclass );
}


int SynGram::Find_Quantor_Entry( int id_class )
{
 return word_entries->FindQuantorEntry(id_class);
}



#if defined SOL_LOADTXT
/*********************************************************************
 Процедура пытается найти словоформу с лексическим содержимым, равным
 входному аргументу name. В случае успеха возвращается пара
 индекс_статьи:индекс_формы. Отыскивается только первый вариант!
 Процедура используется классом Word_Form для парсинга описания
 в текстовом файле, а именно - когда используется сокращенный
 формат: ИМЯ_ФОРМЫ, вместо указания имени класса, имени статьи и
 списка координат.
**********************************************************************/
const Word_Coord SynGram::FindEntryForm( const UCString& name ) const
{
 Lexem Name(name);
 GetDict().GetLexAuto().TranslateLexem(Name);
 return word_entries->FindWordForm(Name);
}
#endif


#if defined SOL_LOADTXT
void SynGram::FindEntryForms( const UCString& name, lem::MCollect<Word_Coord> &wc ) const
{
 Lexem Name(name);
 GetDict().GetLexAuto().TranslateLexem(Name);

 lem::Ptr<WordFormEnumerator> fenum( word_entries->ListWordForms(Name,true) );
 while( fenum->Fetch() )
  {
   wc.push_back( Word_Coord( fenum->GetEntryKey(), fenum->GetFormIndex() ) );
  }

 return;
}
#endif


#if defined SOL_REPORT
/*****************************************************************
 Brief report on SG is printed into the stream 'to'. 
 Печатаем в указанный поток краткий отчет о состоянии Грамматики.
******************************************************************/
void SynGram::Report( OFormatter &to )
{
 Grammar::Report(to);

 to.printf( "%W7d language(s)\n", languages().Count() );

 lem::Ptr<LanguageEnumerator> lenum( languages().Enumerate() );
 while( lenum->Fetch() )
  {
   const int id = lenum->GetId();
   const SG_Language &l = lenum->GetItem();

   to.printf( "Language [%us] id=%d\n", l.GetName().c_str(), l.get_Id() );

   const int nentry=word_entries->CountEntries( ANY_STATE, id );
   const int nform=word_entries->CountForms( id );

   to.printf(
             "%15h %W7d entries in language\n"
             "%15h %W7d form(s) in language\n"
             , nentry
             , nform
            );
  }

 const int nword=GetnEntry();
 const int nform=word_entries->CountForms(ANY_STATE);

 to.printf(
           "%W7d entries total\n"
           "%W7d form(s)\n"
           , nword
           , nform
          );

 return;
}
#endif

/*******************************************************************
 Return automaton name (label), that occurs in automaton XX command
 in dictionary text file.
********************************************************************/
const UCString SynGram::GetName(void) const
{ return SOL_SYNAUTO_MARK; }


#if defined SOL_REPORT
void SynGram::DetailedReport( OFormatter &txtfile )
{
 word_entries->DetailedReport(txtfile);
 return;
}
#endif


#if defined SOL_REPORT
/***********************************************************************
 Печатается разнообразная, полезная и не очень, информация о состоянии
 Грамматики, в том числе - содержимое кэшей и ускорительных списков.
************************************************************************/
void SynGram::PrintMap( OFormatter &txtfile )
{
 Grammar::PrintMap(txtfile);

 Report( txtfile );

 MCollect< pair<int/*iclass*/,int/*nentry*/> > class_info;
 class_info.reserve(classes().Count());

 // Перечень классов (их имен).
 txtfile.printf( "\n%18h-List of classes:%18h-\n iclass        class name        number of entries\n" );
 int max_entries = 0;
 lem::Ptr<PartOfSpeechEnumerator> cenum( (PartOfSpeechEnumerator*)classes().Enumerate() );
 while( cenum->Fetch() )
  {
   const int id_class = cenum->GetId();
   const SG_Class &c = static_cast<const SG_Class&>(cenum->GetItem());

   // Сколько статей относится к данному классу
   const int nentry=word_entries->CountEntries(id_class,ANY_STATE);

   txtfile.printf(
                  "  %W3d        %W30us   %d\n"
                  , id_class
                  , c.GetName().c_str()
                  , nentry
                 );

   class_info.push_back( make_pair(id_class,nentry) );
   max_entries = std::max( max_entries, nentry );
  }

 txtfile.eol();

 // Going to make more impressing list of classes - ordered by number
 // of entries belong to each of them.
 sort_desc_pairs( class_info );

 if( !max_entries ) max_entries = 1;

 txtfile.printf( "Ordered list of classes (weighted by number of belonging entries\n" );
 for( lem::Container::size_type j=0; j<class_info.size(); j++ )
  {
   const int id_class = class_info[j].first;
   const SG_Class &c = static_cast<const SG_Class&>(classes()[id_class]);

   txtfile.printf(
                  "%W3d %W20us %W5d |%H#\n"
                  , id_class
                  , c.GetName().c_str()
                  , class_info[j].second
                  , int( 46*class_info[j].second/max_entries )
                 );
  }

 txtfile.eol();

 // Перечень имен координат
 txtfile.printf( "\nList of coordinates:\n" );
 lem::Ptr<CoordEnumerator> coenum( coords().Enumerate() );
 while( coenum->Fetch() )
  {
   const int id_coord = coenum->GetId();
   const GramCoord &c = coenum->GetItem();
   txtfile.printf(
                  " icoord=%W2d %W32us %W2d state(s)\n"
                  , id_coord
                  , c.GetName()[0].c_str()
                  , c.states().size()
                 );
  }

 txtfile.eol();


 DetailedReport( txtfile );

 // Теперь отдельные таблицы для каждого класса.
 cenum = (PartOfSpeechEnumerator*)classes().Enumerate();
 while( cenum->Fetch() )
  PrintMap_2( txtfile, cenum->GetId() );

 // Окончание распечатки...
 txtfile.printf( "\n%80h-\nThe end of Lexicon decompilation.\n%80h-\n\n\n" );

 return;
}
#endif





#if defined SOL_REPORT
/****************************************************************************
 Теперь для грамматического класса с индексом iclass в списке грамматики
 печатаем перечень входящих в него статей.
*****************************************************************************/
void SynGram::PrintMap_2( OFormatter &txtfile, int iclass )
{
 const GramClass &c = classes()[iclass];

 txtfile.printf( "\n\n%10tTABLE FOR CLASS [%us]", c.GetName().c_str() );

 const int nword=GetnEntry();

 // Сколько статей относится к классу.
 const int nentry = word_entries->CountEntries( iclass, ANY_STATE );

 txtfile.printf( " %W5d entry(s)\n\n", nentry );

 if( !nentry )
  return;

 lem::Ptr<WordEntryEnumerator> wenum( word_entries->ListEntries() );
 while( wenum->Fetch() )
  {
   const SG_Entry& e = wenum->GetItem();

   if( iclass!=e.GetClass() )
    continue;

   txtfile.printf(
                  "%6tkey=%W10d %16tname=[%us] %64t%W3d form(s)\n"
                  , e.GetKey()
                  , e.GetName().c_str()
                  , e.forms().size()
                 );
  }

 return;
}
#endif

/*
#if defined SOL_CAA
// *****************************************************************************
// Поиск имени грамматической связки для перевода статей из класса from_class
// в класс to_class (задаются ключи классов). Например - для перевода предиката
// в причастие.
// В случае неуспеха возвращается пустая строка.
// *****************************************************************************
const UCString SynGram::FindGramLink(
                                     const UCString &from_class,
                                     const UCString &to_class
                                    ) const
{
 for( lem::Container::size_type i=0; i<gram_links.size(); i++ )
  if(
     gram_links[i].from_class == from_class &&
     gram_links[i].to_class == to_class
    )
   return gram_links[i].link_name;

 return L"";
}
#endif
*/


/*
#if defined SOL_CAA
void SynGram::AddGramLink(
                          const UCString &from_class,
                          const UCString &to_class,
                          const UCString &link_name
                         )
{
 gram_links.push_back( SG_GramLink(from_class,to_class,link_name) );
 return;
}
#endif
*/


#if defined SOL_CAA
int SynGram::FindLinkedEntryKey(
                                int From_Entry_Key,
                                const UCString &link_name
                               )
{
 const SG_Entry &from_entry = GetEntry(From_Entry_Key);
 const int move_by_link = FindLink(link_name);

 // Поручаем словарной статье самой сделать перемещение по связке и
 // получаем список достигаемых статей ie_res_key.
 IntCollect ie_res_key;
 net->Find_Linked_Entries( From_Entry_Key, move_by_link, ie_res_key );

 return !ie_res_key.empty() ? ie_res_key.front() : UNKNOWN;
}
#endif








#if defined SOL_CAA
// ******************************************************
// Вычисление сетевого расстояния между статьями.
// Пока в целях упрощения реализован только простой
// алгоритм: делается попытка одного прыжка по сети
// от одной статья к другой.
// ******************************************************
int SynGram::Calc_Distance( int ientry1, int ientry2, int max_dist )
{
 if( ientry1==ientry2 )
  // Предельный случай - совпадение статей
  return 0;

 const SG_Entry &e1 = GetEntry(ientry1);
 const int key1 = e1.GetKey();

 const SG_Entry &e2 = GetEntry(ientry2);
 const int key2 = e2.GetKey();

 lem::Ptr<WordLinkEnumerator> links1( Get_Net().EnumerateWordLinks(key1) );
 while( links1->Fetch() )
  {
   const int ek_C = links1->GetEntryKey2();
   if( ek_C==key2 )
    return 1;
  }
 links1.Delete();

 lem::Ptr<WordLinkEnumerator> links2( Get_Net().EnumerateWordLinks(key2) );
 while( links2->Fetch() )
  {
   const int ek_C = links2->GetEntryKey2();
   if( ek_C==key1 )
    return 1;
  }
 links2.Delete();

 if( !max_dist )
  {
   // Углубляться более не можем. Возвращаем целочисленную бесконечность.
   return INT_MAX;
  }

 links1 = Get_Net().EnumerateWordLinks(key1);
 while( links1->Fetch() )
  {
   const int ek_C = links1->GetEntryKey2();
   int dist1 = Calc_Distance( ek_C, ientry2, max_dist-1 );
   if( dist1 != INT_MAX )
    return dist1+1;
  }
 links1.Delete();

 links2 = Get_Net().EnumerateWordLinks(key2);
 while( links2->Fetch() )
  {
   const int ek_C = links2->GetEntryKey2();
   int dist2 = Calc_Distance( ientry1, ek_C, max_dist-1 );
   if( dist2 != INT_MAX )
    return dist2+1;
  }

 return INT_MAX;
}
#endif




int SynGram::GetnEntry( int Id_Language )
{
 return word_entries->CountEntries( ANY_STATE, Id_Language );
}


// *************************************************
// Подсчитывает количество форм в оперативной памяти
// *************************************************
int SynGram::Count_Forms( int Id_Language )
{
 return word_entries->CountForms( Id_Language );
}



int SynGram::Find_Language( const UCString &Name )
{
 return langs->Find(Name);
}


GramClass* SynGram::Create_Class(void) const
{ return new SG_Class; }


int SynGram::Find_Link( const UCString &s ) const
{
 return coords()[I_NET].FindState(s);
}

Tree_Link SynGram::Find_Tree_Link( const UCString &s ) const
{
 int istate = coords()[I_NET].FindState(s);
 return Tree_Link( istate, I_NET );
}


#if defined SOL_SAVETXT
void SynGram::SaveTxt( OFormatter &txt )
{
 txt.printf( "automat sg\n{\n" );

 aux_form_types->SaveTxt(txt);

 lem::Ptr<CoordEnumerator> coenum( coords().Enumerate() );
 while( coenum->Fetch() )
  coenum->GetItem().SaveTxt(txt);

 txt.eol();

 lem::Ptr<Solarix::PartOfSpeechEnumerator> cenum( (PartOfSpeechEnumerator*)classes().Enumerate() );
 while( cenum->Fetch() )
  cenum->GetItem().SaveTxt(txt,*this);

 txt.eol();

 lem::Ptr<WordEntryEnumerator> wenum( word_entries->ListEntries() );
 while( wenum->Fetch() )
  wenum->GetItem().SaveTxt(txt,*this);

 txt.printf( "\n}\n" );

 return;
}
#endif



#if defined SOL_CAA
// ********************************************************
// Если лексема-аргумент может быть начальной лексемой для
// мультилексемы, то возвращается максимальная длина такой
// мультилексемы, иначе 0.
// ********************************************************
int SynGram::IsMultiLexemBegin( const Lexem &l ) const
{
 MultiLexemInfo info;
 if( word_entries->IsMultilexemHead( l, info ) )
  return info.maxlen;
 else
  return 0;
}

bool SynGram::IsMultiLexem( const Lexem &l ) const
{
 return word_entries->IsMultilexemForm( l );
}


// Если слово является известной грамматической формой
bool SynGram::IsWordForm( const Lexem &l ) const
{
 return word_entries->IsWordForm( l );
}

#endif


bool SynGram::FindMLEntryForm( const Lexem& ml_name )
{
 return word_entries->IsMultilexemForm(ml_name);
}


#if defined SOL_CAA
const CharNode& SynGram::GetPrefixTree(void)
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs_prefix_tree);
 #endif

 if( prefix_tree==NULL )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif

   // Сначала выясним, какие из реализованных языков нужно включать в построение.
   std::set<int> allowed_langs;
   lem::Ptr<LanguageEnumerator> lenum( langs->Enumerate() );
   while( lenum->Fetch() )
    {
     const SG_Language &l = lenum->GetItem();

     const int iseg = l.FindParam(L"Segmentation");

     if( iseg!=UNKNOWN && l.params[iseg]->values.size()==1 && l.params[iseg]->values.front()==L"dictionary_lookup" )
      allowed_langs.insert( l.GetId() );
    } 

   prefix_tree = GetPrefixTree( allowed_langs );
  }

 return *prefix_tree;
}


CharNode* SynGram::GetPrefixTreeForAllLanguages(void)
{
 return word_entries->GetPrefixTreeForAllLanguages();
}


CharNode* SynGram::GetPrefixTree( const std::set<int>& allowed_langs )
{
 return word_entries->GetPrefixTree(allowed_langs);
}

#endif


#if defined SOL_LOADBIN && defined SOL_COMPILER
void SynGram::PrepareForMerging(void)
{
 word_entries->PrepareForMerging();
 return;
}
#endif


// ************************************************
// Ищем все словарные статьи с указанным именем.
// ************************************************
bool SynGram::FindEntries( const Lexem& name, lem::MCollect<int>& ies ) const
{
 ies.clear();

 lem::Ptr<WordEntryEnumerator> wenum( word_entries->ListEntries(name,UNKNOWN) );
 while( wenum->Fetch() )
  {
   ies.push_back( wenum->GetId() );
  }

 return !ies.empty();
}


int SynGram::GetPredefinedEntryKey( int index )
{
 return word_entries->GetPredefinedEntryKey(index);
}




#if defined SOL_LOADTXT && defined SOL_COMPILER
// *****************************************************************
// Вернет true, если статья имеет омонимичные разновидности
// *****************************************************************
bool SynGram::IsOmonym( int iclass, const lem::UCString & ename ) const
{
 if( !omonyms_history.empty() )
  return omonyms_history.find( std::make_pair(iclass,ename) )!=omonyms_history.end();
 else
  return storage->IsOmonym( ename, iclass );
}
#endif


#if defined SOL_LOADTXT
int SynGram::LoadEntry( lem::StrParser<lem::UFString> &txt )
{
 return word_entries->LoadEntry(txt);
}
#endif


void SynGram::SaveLexiconDb( const lem::Path &lexicon_db_path )
{
 storage->CopyDatabase( lexicon_db_path ); 
 return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynGram::StoreCplxLeft( const lem::UFString &phrase )
{
 bool is_multiword=phrase.find(L' ')!=UNKNOWN; // чаще всего используется пробел, проверяем его быстро
 if( !is_multiword )
  {
   for( int i=0; i<phrase.length(); ++i )
    if( lem::is_udelim(phrase[i]) )
     {
      is_multiword=true;
      break;
     }
  }

 if( is_multiword )
  {
   // Разбиваем левую часть на слова, нам нужно оставить первое слово.
   lem::Collect<UFString> words;
   lem::parse( phrase, words, L" ,-&+" );
   const int len = CastSizeToInt(words.size());
   
   if( len>1 )
    {
     lem::UCString headword = lem::to_upper(words.front()).c_str();

     std::map<UCString,CplxLeft*>::iterator it = cplx_map.find(headword);
     if( it==cplx_map.end() )
      {
       CplxLeft *x = new CplxLeft;
       x->headword = headword;
       x->minlen=x->maxlen=len;
       cplx_map.insert( std::make_pair(headword,x) );
       cplx_list.push_back(x);
      }
     else
      {
       it->second->minlen = std::min( it->second->minlen, len );
       it->second->maxlen = std::max( it->second->maxlen, len );
      }
    }
  }

 return;
}
#endif


bool SynGram::IsComplexHeadword( const UCString &headword, int &minlen, int &maxlen )
{
 CplxLeft info;
 const int cl_id = GetStorage().GetCplxLeft( headword, info );
 if( cl_id!=UNKNOWN )
  {
   minlen = info.minlen;
   maxlen = info.maxlen;
  }

 return cl_id!=UNKNOWN;
}


int SynGram::FindComplexEntry( const UFString &phrase )
{
 return GetStorage().FindPhrase( phrase, true );
}


PhraseEnumerator* SynGram::GetComplexEntries( bool left, bool right )
{
 if( left && right )
  {
   LS_ResultSet *rs = GetStorage().ListPhrases();
   return new PhraseEnumerator( rs, 0, this );
  }
 else if( left )
  {
   LS_ResultSet *rs = Get_Net().GetStorage().ListPhraseLinks();
   return new PhraseEnumerator( rs, 1, this );
  }
 else if( right )
  {
   LS_ResultSet *rs = Get_Net().GetStorage().ListPhraseLinks();
   return new PhraseEnumerator( rs, 2, this );
  }
 else
  {
   LEM_STOPIT;
   return NULL;
  }
}

int SynGram::GetnPhrase(void)
{
 return GetStorage().CountPhrases();
}

PhraseNoteEnumerator* SynGram::EnumeratePhraseNotes( int id_phrase )
{
 return new PhraseNoteEnumerator(this,id_phrase);
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynGram::LoadClass( Macro_Parser& txtfile, bool is_extern )
{
 SG_Class *new_class = (SG_Class*)( aclass->LoadTxt(txtfile,!is_extern));
 
 if( new_class!=NULL )
  {
   const UCString &new_class_name = new_class->GetName();

   // Координата I_CLASSCOORD относится к предопределенным...
   // if( FindCoord(I_CLASSCOORD).GetIndex()!=UNKNOWN )
    {
     GramCoord &cc = coords().GetCoord(I_CLASSCOORD);
     cc.AddState( new_class_name );
    }

   // Также мы должны сгенерировать статью class_name:?, то есть с
   // особым лексическим содержимым - квантором '?'.
   word_entries->CreateEntry( SOL_UNKNOWN_ENTRY_NAME, classes().Find( new_class->GetName() ) );
  }

 return;
}
#endif


const SG_Class& SynGram::GetClass( int id )
{
 return (const SG_Class&)(classes()[id]);
}

int SynGram::GetMaxMLLen(void) const
{
 return word_entries->GetMaxMultilexemLen();
}

const SG_Entry& SynGram::GetEntry( int ekey )
{
 return word_entries->GetEntry(ekey);
}

const IntCollect& SynGram::GetUEntries(void)
{
 return word_entries->GetUEntries();
}

LanguageUsage& SynGram::GetLanguageUsage(void)
{
 return *lang_usage;
}


bool SynGram::GetAuxForm( int id_entry, int iform, int aux_type_id, lem::UFString &aux_form )
{
 return GetStorage().GetAuxForm( id_entry, iform, aux_type_id, aux_form )!=UNKNOWN;
}


static bool dims_sorter( const GramCoordPair &x, const GramCoordPair &y )
{
 return x.GetCoord().GetIndex()<y.GetCoord().GetIndex();
}

void SynGram::ComposeFormDims(
                              const SG_Entry &e,
                              const SG_EntryForm &form,
                              UFString &form_dims,
                              bool as_numbers
                             )
{
 // проверка на специальные классы
 if( e.GetClass()<0 )
  return;

 const SG_Class &cls = GetClass( e.GetClass() );

 const CP_Array& coords = form.coords();

 lem::MCollect< GramCoordPair > dims;

 for( lem::Container::size_type i=0; i<coords.size(); ++i )
  {
   const Solarix::GramCoordPair &p = coords[i];

   // Отбираем только измерения!
   const int icoord = p.GetCoord().GetIndex();

   if( cls.dims().find( GramCoordAdr(icoord) )!=UNKNOWN )
    dims.push_back(p);
  }

 // Отсортируем список измерений по возрастанию кода координаты
 std::sort( dims.begin(), dims.end(), dims_sorter );

 // Сериализация
 SerializeCoords( dims, form_dims, as_numbers );

 return;
}


void SynGram::SerializeCoords(
                              const lem::MCollect< GramCoordPair > & pairs,
                              UFString &str,
                              bool as_numbers
                             )
{
 // Сериализация
 for( lem::Container::size_type i=0; i<pairs.size(); ++i )
  {
   if( pairs[i].GetState()==ANY_STATE )
    continue;

   str.Add_Dirty( L' ' );

   if( as_numbers )
    {
     str.Add_Dirty( lem::to_ustr( pairs[i].GetCoord().GetIndex() ).c_str() );
     str.Add_Dirty( L':' );
     str.Add_Dirty( lem::to_ustr( pairs[i].GetState() ).c_str() );
    }
   else
    {
     const Solarix::GramCoord & c = coords()[ pairs[i].GetCoord().GetIndex() ];
     if( c.IsBistable() )
      {
       if( pairs[i].GetState()==0 )
        {
         str.Add_Dirty( L'~' );
         str.Add_Dirty( c.GetName()[0].c_str() );
        }
       else
        {
         str.Add_Dirty( c.GetName()[0].c_str() );
        }    
      }
     else
      {
       str.Add_Dirty( c.GetName()[0].c_str() );
       str.Add_Dirty( L':' );
       str.Add_Dirty( c.GetStateName(pairs[i].GetState()).c_str() );
      }  
    }
  }

 str.Add_Dirty( L' ' );
 str.calc_hash();

 return;
}


