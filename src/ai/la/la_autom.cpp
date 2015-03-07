// -----------------------------------------------------------------------------
// File LA_AUTOM.CPP
//
// (c) by Elijah Koziev     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
//                        --- МОРФОЛОГИЧЕСКИЙ АНАЛИЗАТОР ---
//
// 21.08.2006 - введена рекурсия в Translate_To_Nouns, чтобы было возможным
//              преобразовывать цепочки ПРИЧАСТИЕ->ИНФИНИТИВ->СУЩЕСТВИТЕЛЬНОЕ
// 29.07.2008 - добавлен метод Translate_To_Verbs для перехода от инфинитива к
//              глаголу. 
// 02.08.2008 - код sol_SeekThesaurus перенесен в LexiconAutomat, чтобы
//              был унифицированный способ получать связанные статьи и в
//              поисковой системе.
// 05.01.2009 - добавлена работа с фильтрами вариаторов.
// 04.03.2009 - в поиск по тезаурусу переводов добавлен учет японских (TO_JAPANESE_link)
// -----------------------------------------------------------------------------
//
// CD->02.12.1995
// LC->07.11.2014
// --------------

#if defined SOL_LOADTXT
#include <algorithm> // for sort(...)
#include <lem/conversions.h>
#include <lem/solarix/tokens.h>
#endif

#include <lem/logfile.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/version.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/casing_coder.h>
#include <lem/solarix/LA_WordProjectionBuffer.h>
#include <lem/solarix/KnowledgeBase.h>
#include <lem/solarix/TreeScorer.h>
#include <lem/solarix/LanguageEnumerator.h>


#if defined SOL_CAA
#include <lem/solarix/_sg_api.h>
#endif

#include <lem/solarix/aa_autom.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/CriteriaInStorage.h>
#include <lem/solarix/LA_Recognizer.h>
#include <lem/solarix/LA_Preprocessor.h>
#include <lem/solarix/LA_PhoneticRule.h>
#include <lem/solarix/LA_PhoneticMatcher.h>
#include <lem/solarix/LA_SynPatternTrees.h>
#include <lem/solarix/LA_UnbreakableRule.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/PM_FunctionLoader.h>
#include <lem/solarix/WordAssociation.h>
#include <lem/solarix/TreeScorers.h>
#include <lem/solarix/MorphologyModels.h>
#include <lem/solarix/la_autom.h>


using namespace std;
using namespace boost;
using namespace lem;
using namespace Solarix;

LexicalAutomat::LexicalAutomat(void) : PM_Automat(SOL_LA_INDEX)
{
 ROOT_NODE_NAME = L"ROOT_NODE";

 storage = NULL;

 #if defined SOL_CAA
 casing_coder = NULL;
 #endif

 unknown_entry_key = UNKNOWN;

 do_delete_storage = false;

 MIN_PROJ_R = Real1(0);
 minrel_loaded = false;

 param = new CriteriaInStorage();

 NWORDPROJMAX     = 0;
 NMISSMAX         = 3;

 #if defined SOL_CAA
 do_update_cache  = false;
 #else
 do_update_cache  = true;
 #endif

 wordentry_set = NULL;
 preprocessor = NULL;
 recognizer = NULL;
 phonetic_matcher = NULL;
 pattern_trees = NULL;

 word_proj = new LA_WordProjBuffer();
 knowledges = NULL;
 tree_scorers = new TreeScorers();
 models = NULL;

 #if defined SOL_CAA
 InitLinks();
 #endif


 return;
}


LexicalAutomat::~LexicalAutomat(void)
{
 lem_rub_off(wordentry_set);
 lem_rub_off(preprocessor);
 lem_rub_off(recognizer);
 lem_rub_off(phonetic_matcher);
 lem_rub_off(pattern_trees);
 lem_rub_off(knowledges);
 lem_rub_off(models);

 #if defined SOL_CAA
 lem_rub_off(casing_coder);
 #endif

 lem_rub_off(word_proj);
 lem_rub_off(tree_scorers);

 if( do_delete_storage )
  delete storage;

 return;
}


void LexicalAutomat::SetDictPtr( Dictionary *d )
{
 PM_Automat::SetDictPtr(d);

 GG = &dict->GetGraphGram();
 SG = &dict->GetSynGram();

 wordentry_set = new WordEntrySet();
 preprocessor = new LA_Preprocessor(&GetDict());
 recognizer = new LA_Recognizer(&GetDict());
 phonetic_matcher = new LA_PhoneticMatcher(&GetDict());
 pattern_trees = new LA_SynPatternTrees(&GetDict());
 knowledges = new KnowledgeBase( &GetDict() );
 models = new MorphologyModels();

 return;
}

void LexicalAutomat::SetStorage( LexiconStorage *stg, bool _do_delete )
{
 if( do_delete_storage )
  delete storage;

 storage = stg;
 do_delete_storage = _do_delete;

 static_cast<CriteriaInStorage*>(param)->Connect( (CriteriaStorage*)stg );
 wordentry_set->Connect(stg);
 preprocessor->Connect(stg);
 recognizer->Connect(stg);
 phonetic_matcher->Connect(stg);
 pattern_trees->Connect(stg);
 knowledges->Connect(stg);
 tree_scorers->Connect(stg);

 PM_Automat::SetStorage( L"la", stg );

 return;
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
/***************************************************************************
 Метод вызывается из класса Automaton и должен распознать и загрузить
 очередной структурный элемент из текстового файла описания Словаря,
 относящийся к Лексическому Автомату. В случае, если это возможно, возвращаем
 true, иначе false. Входной параметр t - первая лексема из группы, так что к
 аргументу txtfile нужно обращаться только для считывания второй и
 последующих лексем.
****************************************************************************/
bool LexicalAutomat::ProcessLexem(
                                  const BethToken &t,
                                  Macro_Parser &txtfile,
                                  const Binarization_Options &options
                                 )
{
 if( ProcessLexem2( t, txtfile, options ) )
  return true;

 return PM_Automat::ProcessLexem(t,txtfile,options);
}

bool LexicalAutomat::ProcessLexem2(
                                  const BethToken &t,
                                  Macro_Parser &txtfile,
                                  const Binarization_Options &options
                                 )
{
 if(t.eqi(L"similarity"))
  {
   // Правило лексического искажения - для работы подсистемы нечеткой
   // проекции.
   LA_PhoneticRule r;
   r.LoadTxt(txtfile,GetGraphGram());

   if( storage->FindPhoneticRule( r.GetName() )!=UNKNOWN )
    {
     // Правило с таким именем уже загружено.
     lem::Iridium::Print_Error( t, txtfile );
     GetIO().merr().printf( "Rule [%us] redefinition\n", r.GetName().c_str() );
     throw E_ParserError();
    }
   else
    {
     storage->StorePhoneticRule(&r);
    }

   return true;
  }
 else if( t.string().eqi( L"unbreakable" ) )
  {
   LA_UnbreakableRule r;
   r.LoadTxt( txtfile, GetDict() );
   if( !r.GetName().empty() )
    {
     if( storage->FindUnbreakableRule(r.GetName())!=UNKNOWN )
      {
       lem::Iridium::Print_Error( t, txtfile );
       GetIO().merr().printf( "Rule [%us] redefinition\n", r.GetName().c_str() );
       throw E_ParserError();
      }
    }

   storage->StoreUnbreakableRule(&r);
   return true;
  }
 else if( t.string().eqi( L"recognition" ) )
  {
   recognizer->LoadTxt_Recognition( txtfile, GetDict() );
   return true;
  }
 else if( t.string().eqi( L"misspelling" ) )
  {
   recognizer->LoadTxt_Misspelling( txtfile, GetDict() );
   return true;
  }
 else if( t.string().eqi( L"crop" ) )
  {
   preprocessor->LoadTxt( t, txtfile, GetDict() );
   return true;
  }
 else if( t.string().eqi(L"wordentry_set") )
  {
   wordentry_set->LoadTxt_WordEntrySet( txtfile, GetDict() );
   return true;
  }
 else if( t.string().eqi(L"word_set") )
  {
   wordentry_set->LoadTxt_WordSet( txtfile, GetDict() );
   return true;
  }
 else if( t.string().eqi(L"collocation_set") )
  {
   wordentry_set->LoadTxt_CollocationSet( txtfile, GetDict() );
   return true;
  }
 else if( t.string().eqi(L"wordform_set") )
  {
   wordentry_set->LoadTxt_WordformSet( txtfile, GetDict() );
   return true;
  }
 else if( t.string().eqi( L"facts" ) )
  {
   knowledges->LoadFactsTxt(txtfile);
   return true;
  }
 else if( t.string().eqi( L"fact" ) )
  {
   knowledges->LoadFactTxt(txtfile);
   return true;
  }
 else if( t.string().eqi( L"patterns" ) )
  {
   pattern_declarations.LoadTxt( GetDict(), txtfile );
   return true;
  }
 else if( t==B_PATTERN )
  {
   SynPattern *p = new SynPattern();

   lem::Iridium::BSourceState beg = txtfile.tellp();

   p->LoadTxt(
              GetDict(),
              txtfile,
              pattern_declarations,
              GetWordEntrySet(),
              functions->Get()
             );

   if( p->Error() )
    {
     lem::Iridium::Print_Error( beg, txtfile );
     GetIO().merr().printf( "Error in pattern\n" );
     throw;
    }
   else
    {
     if( p->GetName().empty() )
      {
       if( p->IsIncomplete() )
        incomplete_patterns.push_back(p);
       else
        patterns.push_back(p);
      }
     else
      {
       named_patterns_list.push_back(p);
       pattern_declarations.NamedPatternLoaded( p->GetName() );
      }
    }

   return true;
  }
 else if( t.string().eqi( L"tree_scorers" ) )
  {
   tree_scorers->LoadGroup( GetDict(), txtfile );
   return true;
  }
 else if( t.string().eqi( L"tree_scorer" ) )
  {
   TreeScorer scorer;
   scorer.LoadTxt( GetDict(), txtfile, GetWordEntrySet(), *tree_scorers );
   scorer.Save( GetStorage() );
   return true;
  }
 else if( t.string().eqi( L"assoc_word" ) )
  {
   WordAssociation assoc;
   assoc.LoadTxt( GetDict(), txtfile, GetWordEntrySet() );
   assoc.Save( GetStorage() );
   return true;
  }
 else if( t.string().eqi( L"function" ) )
  {
   PM_Automat::ProcessLexem(t,txtfile,options);
   return true;
  }


 return false;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
 struct NameLang
 {
  lem::UCString name, uname;
  int id_language;

  NameLang(void) : id_language(UNKNOWN) {}
  NameLang( const lem::UCString & _name, const lem::UCString & _uname, int id_lang ) : name(_name), uname(_uname), id_language(id_lang) {}

  inline bool operator==( const NameLang &x ) const { return id_language==x.id_language && uname==x.uname; }
  inline bool operator!=( const NameLang &x ) const { return id_language!=x.id_language || uname!=x.uname; }

  inline bool operator<( const NameLang &x ) const
  {
   if( id_language < x.id_language )
    return true;

   if( id_language > x.id_language )
    return false;

   return uname < x.uname;
  }
 };

/************************************************************************
 Процедура подготавливает Автомат к работе после загрузки содержимого
 из текстового файла Словаря. Вызывается автоматически классом Словаря
 (class Dictionary).
*************************************************************************/
void LexicalAutomat::Prepare( const lem::Path & outdir, const Binarization_Options & opts )
{
 // Длительная операция: сообщаем пользователю.
 GetIO().mecho().printf( "%vfELA%vn: preparing..." );
 GetIO().mecho().flush();

 PM_Automat::Prepare(outdir,opts);

 NWORDPROJMAX = 256;

 word_proj->Adjust( GetGraphGram() );
 word_proj->SetMaxSize(NWORDPROJMAX);

 SynGram &sg = GetDict().GetSynGram();

 if( compilation_error_count )
  {
   GetIO().mecho().printf( "\n%vfALA: there were %d compilation errors. Details are available in journal.%vn\n", compilation_error_count.value );
   GetIO().mecho().flush();
   throw E_ParserError();
  }

 knowledges->AllFactsCompiled();

 // инициализируем все языки нулями.
 if( pattern_declarations.HasNamedPatterns() && !named_patterns_list.empty() )
  {
   std::map< NameLang, lem::MCollect<SynPattern*>* > x_patterns_map;

   // разбросаем паттерны в группы по именам с учетом языка
   for( lem::Container::size_type i=0; i<named_patterns_list.size(); ++i )
    {
     SynPattern *p = named_patterns_list[i];

     lem::UCString name( p->GetName() );
     lem::UCString uname( lem::to_upper(name) );
     NameLang name_lang(name,uname,p->GetLanguageId());

     std::map< NameLang, lem::MCollect<SynPattern*>* >::iterator it = x_patterns_map.find(name_lang);
     if( it==x_patterns_map.end() )
      {
       lem::MCollect<SynPattern*> *l = new lem::MCollect<SynPattern*>();
       l->push_back(p);
       x_patterns_map.insert( std::make_pair(name_lang,l) );
      }
     else
      {
       it->second->push_back( p );
      }
    }

   // из каждой группы паттернов делаем именованный фильтр
   for( std::map<NameLang, lem::MCollect<SynPattern*>* >::iterator it=x_patterns_map.begin(); 
        it!=x_patterns_map.end();
        ++it )
    {
     lem::UCString gname = it->first.name;
     const int id_tree = pattern_declarations.GetPatternID(gname);

     const lem::MCollect<SynPattern*> * x = it->second;

     // проверим, что в группе все паттерны имеют одинаковые наборы переменных
     for( lem::Container::size_type q=1; q<x->size(); ++q )
      {
       (*x)[q]->CheckBeforeMerge( *x->front(), sg );
      }

     // сливаем
     SynPatternTreeNode *tree = new SynPatternTreeNode(*x);

     if( pattern_declarations.GetOptions(gname).IsBottomUp() )
      tree->SetBottomUp();

     // сохраняем в БД
     pattern_trees->StoreFilterTree( id_tree, it->first.name, tree, it->first.id_language, LA_SynPatternTrees::NAMED_PATTERN );
    }

   // обработку паттернов завершили, удаляем временные списки.
   for( std::map< NameLang, lem::MCollect<SynPattern*>* >::iterator it=x_patterns_map.begin();
        it!=x_patterns_map.end();
        ++it )
    {
     delete it->second;
    }

   const int count_top_down_rules = CastSizeToInt(patterns.size()+named_patterns_list.size());
   GetIO().mecho().printf( " %d parser rules...", count_top_down_rules );
  }

 // Собираем префиксное дерево для проверки начальных вариаторов.
 // 2 прохода цикла - для полных паттернов и для incomplete
 for( int pat_type=0; pat_type<2; ++pat_type )
  {
   const lem::PtrCollect<SynPattern> & this_patterns = pat_type==0 ? patterns : incomplete_patterns;

   if( !this_patterns.empty() )
    {
     std::set<int> id_langs;
     typedef std::multimap< int, SynPattern* > LANG2PATTERN;
     LANG2PATTERN lang2pattern;

     for( lem::Container::size_type i=0; i<this_patterns.size(); ++i )
      {
       id_langs.insert( this_patterns[i]->GetLanguageId() );
       lang2pattern.insert( std::make_pair( this_patterns[i]->GetLanguageId(), (SynPattern*)this_patterns[i] ) );
      }

     for( std::set<int>::const_iterator it=id_langs.begin(); it!=id_langs.end(); ++it )
      {
       const int id_tree = pattern_declarations.GetNextTreeID();

       const int id_language = *it;
       std::pair< LANG2PATTERN::iterator, LANG2PATTERN::iterator > pit = lang2pattern.equal_range(id_language);
       lem::MCollect< SynPattern * > patterns_for_lang;
       for( LANG2PATTERN::iterator it2 = pit.first; it2!=pit.second; ++it2 )
        patterns_for_lang.push_back( it2->second );

       SynPatternTreeNode *filter_tree = new SynPatternTreeNode(patterns_for_lang);

       // сохраняем в БД
       const int pattern_type = pat_type==0 ? LA_SynPatternTrees::SOLID_PATTERN : LA_SynPatternTrees::INCOMPLETE_PATTERN;
       pattern_trees->StoreFilterTree( id_tree, L"", filter_tree, id_language, pattern_type );
      }
    }
  }


 lem::MCollect<lem::UCString> unresolved_patterns;
 pattern_declarations.GetUnresolvedForwardDeclarations( unresolved_patterns );
 if( !unresolved_patterns.empty() )
  {
   GetIO().merr().printf( "Unresolved forward pattern declarations - %d names:\n", CastSizeToInt(unresolved_patterns.size()) );
   for( int i=0; i<unresolved_patterns.size(); ++i )
    GetIO().merr().printf( "%us\n", unresolved_patterns[i].c_str() );

   GetIO().mecho().flush();
   throw E_ParserError();
  }

 GetIO().mecho().printf( "%vfAOK%vn\n" );
 GetIO().mecho().flush();

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void LexicalAutomat::Compile_Finder( const lem::Path &outdir )
{
 word_proj->Compile(outdir);
 return;
}
#endif




#if defined SOL_REPORT
/*************************************************
 Print status information onto specified stream.
**************************************************/
void LexicalAutomat::Report( OFormatter &s )
{
 PM_Automat::Report(s);

 word_proj->Report(s,*this);

 return;
}
#endif

/********************************************************************
 Возвращает условное имя Автомата. Это имя, состоящее из 2х букв,
 используется везде, где нужно как-то разделить по именам данные для
 разных автоматов.
*********************************************************************/
const UCString LexicalAutomat::GetName(void) const
{ return SOL_LEXAUTO_MARK; }


#if defined SOL_REPORT
void LexicalAutomat::PrintMap( OFormatter &txtfile )
{
 PM_Automat::PrintMap(txtfile);

 txtfile.eol();

 word_proj->PrintMap(txtfile,GetSynGram());

 // Конец листинга...
 txtfile.printf( "End of Lexical Automaton Content Map.\n\n" );

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void LexicalAutomat::Optimize(void)
{
 PM_Automat::Optimize();

 word_proj->Optimize();

 return;
}
#endif

#if defined SOL_CAA
bool LexicalAutomat::Translate_To_Nouns( int ientry_key, MCollect<int> &key_linked, int depth ) const
{
 static lem::MCollect<Tree_Link> filter_nouns;
 if( filter_nouns.empty() )
  {
   filter_nouns.push_back( Tree_Link(TO_NOUN_link) );
  }

 std::set<int> iek_list;
 GetDict().GetSynGram().Get_Net().Find_Linked_Entries( ientry_key, 0, iek_list, false, true, &filter_nouns );

 if( !iek_list.empty() )
  {
   for( std::set<int>::const_iterator i=iek_list.begin(); i!=iek_list.end(); i++ )
    {
     int ikey1 = *i;
     int ie1 = ikey1;//GetDict().GetSynGram().FindEntryIndexByKey(ikey1);

     const int iclass = GetDict().GetSynGram().GetEntry(ie1).GetClass(); 
     if( iclass==NOUN_ru || iclass==NOUN_fr || iclass==NOUN_en || iclass==NOUN_es )
      key_linked.push_back( ikey1 );
    }
  }

 if( depth>0 )
  {
   const int ic = GetDict().GetSynGram().GetEntry(ientry_key).GetClass();
   if( ic==GERUND_2_ru || ic==VERB_ru || ic==ADJ_ru )
    {
     // попробуем найти переход в инфинитив, а уже из него - в существительное
     if( !iek_list.empty() )
      {
       static lem::MCollect<Tree_Link> filter;
       if( filter.empty() )
        {
         filter.push_back( Tree_Link(TO_INF_link) );
        }

       // Отбираем только связки <в_инф>
       iek_list.clear();
       GetDict().GetSynGram().Get_Net().Find_Linked_Entries( ientry_key, 0, iek_list, false, true, &filter );

       for( std::set<int>::const_iterator i=iek_list.begin(); i!=iek_list.end(); i++ )
        {
         int ikey1 = *i;
         int ie1 = ikey1;//GetDict().GetSynGram().FindEntryIndexByKey(ikey1);

         const int iclass = GetDict().GetSynGram().GetEntry(ie1).GetClass(); 
         if( iclass==INFINITIVE_ru )
          Translate_To_Nouns( ikey1, key_linked, depth-1 );
        }
      }
    }
  }

 return !key_linked.empty();
} 
#endif



#if defined SOL_CAA
bool LexicalAutomat::Translate_To_Infinitives( int ientry_key, MCollect<int> &key_linked, int depth ) const
{
 const int iclass = GetDict().GetSynGram().GetEntry(ientry_key).GetClass(); 
 if( iclass==INFINITIVE_ru || iclass==VERB_fr || iclass==VERB_en )
  {
   // Уже нужная форма - просто возвращаем ее
   key_linked.push_back( ientry_key );
   return true;
  }

// if( iclass==VERB_ru || iclass==NOUN_ru )
  {
   static lem::MCollect<Tree_Link> filter_inf;
   if( filter_inf.empty() )
    {
     filter_inf.push_back( Tree_Link(TO_INF_link) );
    }

   std::set<int> iek_list;
   GetDict().GetSynGram().Get_Net().Find_Linked_Entries( ientry_key, 0, iek_list, false, true, &filter_inf );

   if( !iek_list.empty() )
    {
     for( std::set<int>::const_iterator i=iek_list.begin(); i!=iek_list.end(); i++ )
      {
       int ikey1 = *i;
       int ie1 = ikey1;//GetDict().GetSynGram().FindEntryIndexByKey(ikey1);
       key_linked.push_back( ikey1 );
      }
    }
  }

 return !key_linked.empty();
} 
#endif


#if defined SOL_CAA
bool LexicalAutomat::Translate_To_X( int link, int needed_class, int ientry_key, MCollect<int> &key_linked, int depth ) const
{
 const int iclass = GetDict().GetSynGram().GetEntry(ientry_key).GetClass(); 
 if( iclass==needed_class )
  {
   // Уже нужная статья - просто возвращаем ее
   key_linked.push_back( ientry_key );
   return true;
  }

 lem::MCollect<Tree_Link> filter_inf;
 if( filter_inf.empty() )
  {
   filter_inf.push_back( Tree_Link(link) );
  }

 std::set<int> iek_list;
 GetDict().GetSynGram().Get_Net().Find_Linked_Entries( ientry_key, 0, iek_list, false, true, &filter_inf );

 if( !iek_list.empty() )
  {
   for( std::set<int>::const_iterator i=iek_list.begin(); i!=iek_list.end(); i++ )
    {
     int ikey1 = *i;
//     int ie1 = GetDict().GetSynGram().FindEntryIndexByKey(ikey1);
     key_linked.push_back( ikey1 );
    }
  }

 return !key_linked.empty();
} 
#endif


#if defined SOL_CAA
bool LexicalAutomat::Translate_To_Verbs( int ientry_key, MCollect<int> &key_linked, int depth ) const
{
 const int iclass = GetDict().GetSynGram().GetEntry(ientry_key).GetClass();

 if( iclass==GERUND_2_ru || iclass==ADJ_ru )
  { 
   // Попробуем через инфинитив.
   lem::MCollect<int> keys,keys2;
   if( Translate_To_Infinitives(ientry_key,keys) )
    {
     for( lem::Container::size_type i=0; i<keys.size(); ++i )
      {
       const int keyi = keys[i];
       if( Translate_To_Verbs( keyi, keys2 ) )
        {
         for( lem::Container::size_type j=0; j<keys2.size(); ++j )
          {
           if( key_linked.find( keys2[j] )==UNKNOWN )
            key_linked.push_back(keys2[j]);
          }
        }
      }
    }

   return !key_linked.empty();
  }
 else
  return Translate_To_X( TO_VERB_link, VERB_ru, ientry_key, key_linked, depth );
} 
#endif

#if defined SOL_CAA
bool LexicalAutomat::Translate_To_Gerund( int ientry_key, MCollect<int> &key_linked, int depth ) const
{
 return Translate_To_X( TO_ADJ_link, ADJ_ru, ientry_key, key_linked, depth );
} 
#endif

#if defined SOL_CAA
bool LexicalAutomat::Translate_To_Gerund2( int ientry_key, MCollect<int> &key_linked, int depth ) const
{
 return Translate_To_X( TO_GERUND_2_link, GERUND_2_ru, ientry_key, key_linked, depth );
} 
#endif

#if defined SOL_CAA
int LexicalAutomat::SeekThesaurus0(
                                   int iEntryKey,
                                   bool Synonyms,
                                   bool Grammar_Links,
                                   bool Translations,
                                   bool Semantics,  
                                   int nJumps,
                                   lem::MCollect<int> &result_keys,
                                   const SG_TagFilter *tags
                                  )
{
 const bool all_links = Synonyms && Grammar_Links && Translations && Semantics;

 std::set<int> links;

 SynGram &sg = GetSynGram();

 // Связки
 if( all_links )
  {
   sg.Get_Net().Find_Linked_Entries( iEntryKey, nJumps, links, false, true, NULL, tags );
  }
 else
  {
   if( Synonyms && !Grammar_Links && !Translations && !Semantics )
    sg.Get_Net().Find_Linked_Entries( iEntryKey, nJumps, links, false, true, &allowed_links_synonyms, tags );
   else if( !Synonyms && Grammar_Links && !Translations && !Semantics )
    sg.Get_Net().Find_Linked_Entries( iEntryKey, nJumps, links, false, true, &allowed_links_grammar, tags );
   else if( !Synonyms && !Grammar_Links && Translations && !Semantics )
    sg.Get_Net().Find_Linked_Entries( iEntryKey, nJumps, links, false, true, &allowed_links_translations, tags );
   else if( !Synonyms && !Grammar_Links && !Translations && Semantics )
    sg.Get_Net().Find_Linked_Entries( iEntryKey, nJumps, links, false, true, &allowed_links_semantics, tags );
   else
    {
     // В данном случае не обойтись без оверхеда из-за формирования списка допускаемых
     // связок для указанного пользователем сочетания их категорий.
     lem::MCollect< Tree_Link > allowed_links;

     if( Synonyms )
      std::copy( allowed_links_synonyms.begin(), allowed_links_synonyms.end(), std::back_inserter(allowed_links) );

     if( Grammar_Links )
      std::copy( allowed_links_grammar.begin(), allowed_links_grammar.end(), std::back_inserter(allowed_links) );

     if( Translations )
      std::copy( allowed_links_translations.begin(), allowed_links_translations.end(), std::back_inserter(allowed_links) );

     if( Semantics )
      std::copy( allowed_links_semantics.begin(), allowed_links_semantics.end(), std::back_inserter(allowed_links) );

     sg.Get_Net().Find_Linked_Entries( iEntryKey, nJumps, links, true, true, &allowed_links, tags );
    }
  }

 for( std::set<int>::const_iterator i=links.begin(); i!=links.end(); i++ )
  result_keys.push_back( *i );

 return CastSizeToInt(result_keys.size());
}
#endif


#if defined SOL_CAA
void LexicalAutomat::InitLinks(void)
{
 allowed_links_synonyms.clear();
 allowed_links_synonyms.push_back( SYNONYM_link );
 allowed_links_synonyms.push_back( SEX_SYNONYM_link );

 allowed_links_grammar.push_back( TO_VERB_link );
 allowed_links_grammar.push_back( TO_INF_link );
 allowed_links_grammar.push_back( TO_PERFECT );
 allowed_links_grammar.push_back( TO_UNPERFECT );
 allowed_links_grammar.push_back( TO_NOUN_link );
 allowed_links_grammar.push_back( TO_ADJ_link );
 allowed_links_grammar.push_back( TO_ADV_link );
 allowed_links_grammar.push_back( TO_RETVERB );
 allowed_links_grammar.push_back( WOUT_RETVERB );

 allowed_links_translations.push_back( TO_ENGLISH_link );
 allowed_links_translations.push_back( TO_RUSSIAN_link );
 allowed_links_translations.push_back( TO_FRENCH_link );
 allowed_links_translations.push_back( TO_SPANISH_link );
 allowed_links_translations.push_back( TO_GERMAN_link );
 allowed_links_translations.push_back( TO_CHINESE_link );
 allowed_links_translations.push_back( TO_POLAND_link );
 allowed_links_translations.push_back( TO_ITALIAN_link );
 allowed_links_translations.push_back( TO_PORTUGUAL_link );
 allowed_links_translations.push_back( TO_JAPANESE_link );

 allowed_links_semantics.push_back( CLASS_link );
 allowed_links_semantics.push_back( MEMBER_link );
 allowed_links_semantics.push_back( ACTION_link );
 allowed_links_semantics.push_back( ACTOR_link );
 allowed_links_semantics.push_back( TOOL_link );
 allowed_links_semantics.push_back( RESULT_link );

 return;
}
#endif


#if defined SOL_CAA
void LexicalAutomat::SeekThesaurus(
                                   int iEntryKey,
                                   bool Synonyms,
                                   bool Grammar_Links,
                                   bool Translations,
                                   bool Semantics,
                                   int nJumps,
                                   lem::MCollect<int> &result_entry_keys,
                                   const SG_TagFilter *tags
                                  )
{
 const int iclass = GetSynGram().GetEntry(iEntryKey).GetClass();
 if( iclass==VERB_ru || /*iclass==ADJ_ru ||*/ iclass==GERUND_2_ru )
  {
   // Для глаголов и деепричастие надо искать также связки для инфинитивов

   //const SG_Entry &e = GetSynGram().GetEntry(iEntry);
   const int ikey0 = iEntryKey;
   lem::MCollect<int> iek_list; // список связанных инфинитивов
   if( Translate_To_Infinitives( ikey0, iek_list ) )
    {
     // Для каждого инфинитива (обычно он все-таки один) получаем связки нужного типа
     for( lem::Container::size_type i=0; i<iek_list.size(); ++i )
      {
       lem::MCollect<int> list2;
       int iek_inf = iek_list[i];
       SeekThesaurus0( iek_inf, Synonyms, Grammar_Links, Translations, Semantics, nJumps, list2, tags );
    
       // делаем по возможности обратный переход от неопределенной формы к глаголу.
       for( lem::Container::size_type j=0; j<list2.size(); ++j )
        {
         int iex = list2[j];
         bool verb_found=false;

         if( GetSynGram().GetEntry(iex).GetClass()==INFINITIVE_ru )
          {
           lem::MCollect<int> iek_list1; // список связанных глаголов
           const int ikey1 = iex; 
             
           bool translated=false;
           if( iclass==VERB_ru )
            translated = Translate_To_Verbs( ikey1, iek_list1 );
           else if( iclass==ADJ_ru )
            translated = Translate_To_Gerund( ikey1, iek_list1 );
           else if( iclass==GERUND_2_ru )
            translated = Translate_To_Gerund2( ikey1, iek_list1 );

           if( translated )
            {
             verb_found = true;

             for( lem::Container::size_type k=0; k<iek_list1.size(); ++k )
              {
               const int ie2 = iek_list1[k];
               if( result_entry_keys.find( ie2 )==UNKNOWN )
                result_entry_keys.push_back( ie2 );
              }
            }
          }
        }
      }  
    }
     
   // Добавляем связки для исходного глагола, причастия или деепричастия
   if( result_entry_keys.empty() ) 
    {
     SeekThesaurus0( iEntryKey, Synonyms, Grammar_Links, Translations, Semantics, nJumps, result_entry_keys, tags );
    }
   else
    {
     lem::MCollect<int> list2;
     SeekThesaurus0( iEntryKey, Synonyms, Grammar_Links, Translations, Semantics, nJumps, list2, tags );
     for( lem::Container::size_type i=0; i<list2.size(); ++i )
      if( result_entry_keys.find( list2[i] )==UNKNOWN )
       result_entry_keys.push_back( list2[i] );
    }
  }
 else
  {
   SeekThesaurus0( iEntryKey, Synonyms, Grammar_Links, Translations, Semantics, nJumps, result_entry_keys, tags );
  }

 return;
}
#endif


#if defined SOL_CAA
void LexicalAutomat::Synonymize( int iEntryKey, lem::MCollect<int> &result_entry_keys, const SG_TagFilter *tags )
{
 SeekThesaurus(iEntryKey,true,false,false,false,0,result_entry_keys,tags);
 return;
}

void LexicalAutomat::Translate( int iEntryKey, lem::MCollect<int> &result_entry_keys, const SG_TagFilter *tags )
{
 SeekThesaurus(iEntryKey,false,false,true,false,0,result_entry_keys,tags);
 return;
}
#endif


// Возвращается список алфавитов, которые соответствуют языкам по умолчанию.
// Этот список загружается при первом обращении из параметров SG.
const lem::MCollect<int> LexicalAutomat::GetDefaultAlphabets(void)
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker lock(&cs_default_alphabets);
 #endif

 if( !DefaultAlphabetsOk )
  {
   lem::MCollect<int> LanguageID;
   GetDict().GetLanguages( LanguageID );
   if( !LanguageID.empty() )
    {
     for( lem::Container::size_type i=0; i<LanguageID.size(); ++i )
      {
       const int id_lang = LanguageID[i];
       LEM_CHECKIT_Z( id_lang!=UNKNOWN );
       if( id_lang!=UNKNOWN )
        {
         const SG_Language &lang = GetSynGram().languages()[id_lang];

         for( lem::Container::size_type q=0; q<lang.GetAlphabets().size(); ++q )
          {
           const int id_alphabet = lang.GetAlphabets()[q];
           if( DefaultAlphabets.find(id_alphabet)==UNKNOWN )
            DefaultAlphabets.push_back(id_alphabet);
          } 
        }
      }

/*
#if LEM_DEBUGGING==1
lem::mout->printf( "Default alphabets:" );
for( int k=0; k<DefaultAlphabets.size(); ++k )
 lem::mout->printf( " %d", DefaultAlphabets[k] );
lem::mout->eol();
#endif
*/

     DefaultAlphabetsOk = true;
    }
  }

 return DefaultAlphabets;
}

// ****************************************
// Нужно вызвать перед пересборкой правил
// ****************************************
void LexicalAutomat::BeforeSyntaxRecompilation(void)
{
 PM_Automat::BeforeSyntaxRecompilation();

 storage->DeleteWordEntrySets();
 storage->DeleteWordSets();
 storage->DeleteWordformSets();
 storage->DeleteCollocationSets();
 storage->DeletePreprocessorRules();
 storage->DeleteRecognitionRules();
 storage->DeletePhoneticRules();
 storage->DeleteUnbreakableRules();
 storage->DeleteMorphologicalFilters();
 storage->DeleteSynPatternTrees();
 storage->DeleteMisspelling();

 return;
}

Real1 LexicalAutomat::GetMinProjectionRel(void)
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs_minrel);
 #endif
 if( !minrel_loaded )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif
   minrel_loaded = true;
   const int id = params().Find( L"MIN_PROJ_R" );
   if( id!=UNKNOWN )
    MIN_PROJ_R = lem::Real1(params()[id].GetInt());
  }
 
 return MIN_PROJ_R;
}





void LexicalAutomat::SetLazyLoad(void)
{
 lazy_load=true;
 return;
}


   
const lem::UCString * LexicalAutomat::GetRootNodeName(void) const
{
 return &ROOT_NODE_NAME;
}
