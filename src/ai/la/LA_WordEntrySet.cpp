#include <lem/macro_parser.h>
#include <lem/string_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/WordEntrySetItem.h>
#include <lem/solarix/WordEntrySetEnumerator.h>
#include <lem/solarix/WordSetItem.h>
#include <lem/solarix/WordSetEnumerator.h>
#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/ExactWordEntryLocator.h>
#include <lem/solarix/PartOfSpeech.h>

using namespace lem;
using namespace Solarix;


WordEntrySet::WordEntrySet(void)
{
 storage=NULL;
 headwords_loaded = false;
 return;
}


WordEntrySet::~WordEntrySet(void)
{
 for( lem::Container::size_type i=0; i<wordentry_sets.size(); ++i )
  delete wordentry_sets[i];

 for( lem::Container::size_type i=0; i<word_sets.size(); ++i )
  delete word_sets[i];

 return;
}



void WordEntrySet::Connect( LexiconStorage *Storage )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker lock(&cs_init); 
 #endif

 storage = Storage;
 headwords_loaded = false;

 for( lem::Container::size_type i=0; i<wordentry_sets.size(); ++i )
  delete wordentry_sets[i];

 for( lem::Container::size_type i=0; i<word_sets.size(); ++i )
  delete word_sets[i];
 
 wordentry_sets.clear();
 wordentry_set_map.clear();
 wordentry_id2set.clear();

 word_sets.clear();
 word_set_map.clear();
 word_id2set.clear();

 collocation_set_map.clear();
 headwords_map.clear();
 
 wordform_set_map.clear();
 wordform_set_coords_map.clear();


 for( lem::Container::size_type i=0; i<wordform_set_coords.size(); ++i )
  delete wordform_set_coords[i];

 wordform_set_coords.clear();

 return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void WordEntrySet::LoadTxt_WordEntrySet( lem::Iridium::Macro_Parser &txtfile, Dictionary &dict )
{
 lem::Iridium::BethToken t = txtfile.read();
 lem::UCString name = t.string();
 lem::UCString uname(to_upper(name));
 if( wordentry_set_map.find( uname )!=wordentry_set_map.end() )
  {
   lem::Iridium::Print_Error(t,txtfile);
   dict.GetIO().merr().printf( "WordEntry set redefinition: %vfC%us%vn\n", name.c_str() );
   throw lem::E_BaseException();   
  }

 if( IsSetName(name) )
  {
   lem::Iridium::Print_Error(t,txtfile);
   dict.GetIO().merr().printf( "%vfC%us%vn is already a set name\n", name.c_str() );
   throw lem::E_BaseException();   
  }

 const SynPatterns & patterns = dict.GetLexAuto().GetPatternDeclarations();
 if( patterns.IsPatternName(uname) )
  {
   lem::Iridium::Print_Error(t,txtfile);
   dict.GetIO().merr().printf( "%vfC%us%vn is already a patterns name\n", name.c_str() );
   throw lem::E_BaseException();   
  }


 WordEntrySetItem * ekeys = new WordEntrySetItem();
 ekeys->name = name;

 txtfile.read_it( B_EQUAL );


 // Немного сахара: вместо указания грамматического класса для каждого
 // элемента множества, разрешим указать его единожды перед всем списком.
 int common_class_id=UNKNOWN;
 int id_common_language=UNKNOWN;
 lem::UCString class_name;
 if( !txtfile.probe(B_OFIGPAREN) )
  {
   lem::Iridium::BethToken t1 = txtfile.read();
   class_name = t1.string();

   common_class_id=dict.GetSynGram().FindClass(class_name);
   if( common_class_id==UNKNOWN )
    {
     lem::Iridium::Print_Error(t1,txtfile);
     dict.GetIO().merr().printf( "Unknown class name %us\n", class_name.c_str() );
     throw lem::E_BaseException();   
    }

   id_common_language = dict.GetSynGram().GetClass( common_class_id ).GetLanguage();
   
   txtfile.read_it( B_COLON );
   txtfile.read_it( B_OFIGPAREN );
  }

 while( !txtfile.eof() )
  {
   if( txtfile.probe( B_CFIGPAREN ) )
    break;

   if( !ekeys->Empty() )
    txtfile.read_it( B_COMMA );

   lem::Iridium::BethToken t2;
   int id_class=common_class_id;
   int id_language=id_common_language;
   if( id_class==UNKNOWN )
    {
     // Считываем информацию, позволяющую идентифицировать слованную статью.
     t2 = txtfile.read();
     class_name = t2.string();
  
     // Если это имя коллекции, то добавим себе ее содержимое.
     std::map< lem::UCString, const WordEntrySetItem* >::const_iterator src = wordentry_set_map.find( to_upper(class_name) );
     if( src!=wordentry_set_map.end() )
      {
       for( std::set<int>::const_iterator i0=src->second->ies.begin(); i0!=src->second->ies.end(); ++i0 )
        {
         ekeys->InsertEntryKey(*i0);
        }
  
       continue;
      }
  
     id_class=dict.GetSynGram().FindClass(class_name);
     if( id_class==UNKNOWN )
      {
       lem::Iridium::Print_Error(t2,txtfile);
       dict.GetIO().merr().printf( "Unknown class name %us\n", class_name.c_str() );
       throw lem::E_BaseException();   
      }

     id_language = dict.GetSynGram().GetClass(id_class).GetLanguage();
  
     txtfile.read_it( B_COLON );
    }

   Solarix::Lexem ename;
   lem::Iridium::BSourceState item_begin = txtfile.tellp();

   // Может быть задана дополнительная фильтрующая координата или информация об ударении
   Solarix::ExactWordEntryLocator locator;

   if( common_class_id==UNKNOWN )
    {
     ename = sol_read_multyname( dict.GetIO(), txtfile, B_OFIGPAREN );
     locator.LoadTxt( txtfile, dict.GetSynGram() );
    }
   else
    {
     t2 = txtfile.read();
     ename = t2.string();
     if( ename.front()==L'\'' && ename.back()==L'\'' )
      ename.strip( L'\'' );
     else if( ename.front()==L'"' && ename.back()==L'"' )
      ename.strip( L'"' );
    }

   dict.GetLexAuto().TranslateLexem( ename, true, id_language );
 
   lem::MCollect<int> ies;

   if( dict.GetSynGram().IsOmonym( id_class, ename ) )
    {
     dict.GetSynGram().FindEntries( ename, ies );
     
     int icur=0;
     while( icur<CastSizeToInt(ies.size()) )
      {
       const int ekey = ies[icur];
       const SG_Entry &e = dict.GetSynGram().GetEntry(ekey);
       if( e.GetClass()!=id_class )
        {
         ies.Remove(icur);
         continue; 
        }
       else
        {
         bool match = locator.Check( e, dict.GetSynGram() );
     
         if( !match )
          {
           ies.Remove(icur);
           continue; 
          }
         else
          {
           icur++;
          } 
        }
      }
    }
   else
    {
     int ek = dict.GetSynGram().FindEntry2( ename, id_class );
     if( ek!=UNKNOWN )
      {
       if( locator.Empty() )
        ies.push_back(ek);
       else
        {
         const SG_Entry &e = dict.GetSynGram().GetEntry(ek);
         if( locator.Check( e, dict.GetSynGram() ) )
          ies.push_back(ek);
        }
      }
    }

   bool metaentry=false;
   if( ies.empty() )
    {
     // может это ссылка на метастатью?
     const int id_metaentry = dict.GetSynGram().GetStorage().FindMetaEntry( ename, id_class );
     if( id_metaentry!=UNKNOWN )
      {
       dict.GetSynGram().GetStorage().GetMetaEntryItems( id_metaentry, ies );
       metaentry=true;
      }
     else
      {
       lem::Iridium::Print_Error(item_begin,txtfile);
       dict.GetIO().merr().printf( "There is no entry matching the specification %us:%us\n", class_name.c_str(), ename.c_str() );
       throw lem::E_BaseException();
      }
    }
   else if( ies.size()>1 )
    {
     lem::Iridium::Print_Error(item_begin,txtfile);
     dict.GetIO().merr().printf( "There are %d alternatives for word entry %us:%us\n", CastSizeToInt(ies.size()), class_name.c_str(), ename.c_str() );
     throw lem::E_BaseException();
    }
   
   for( lem::Container::size_type k=0; k<ies.size(); ++k )
    {
     const int ekey = ies[k];
   
     if( ekeys->Contains(ekey) )
      {
       lem::Iridium::Print_Error(item_begin,txtfile);

       if( metaentry )
        {
         const SG_Entry & e = dict.GetSynGram().GetEntry(ekey);
         const SG_Class & c  = dict.GetSynGram().GetClass( e.GetClass() );
         dict.GetIO().merr().printf( "Entry %us:%us (declared as part of metaentry %us:%us) is already added to the set\n", c.GetName().c_str(), e.GetName().c_str(), class_name.c_str(), ename.c_str() );
        }
       else
        {
         dict.GetIO().merr().printf( "Entry %us:%us is already added to the set\n", class_name.c_str(), ename.c_str() );
        }

       throw lem::E_BaseException();
      }

     ekeys->ies.insert(ekey);
    }
  }

 wordentry_sets.push_back(ekeys);
 storage->StoreWordEntrySet( *ekeys );
 LEM_CHECKIT_Z( ekeys->GetId()!=UNKNOWN );

 wordentry_set_map.insert( std::make_pair( to_upper(name), ekeys ) );
 wordentry_id2set.insert( std::make_pair( ekeys->GetId(), ekeys ) );

 return;
}
#endif



bool WordEntrySet::FindWordEntrySet( const lem::UCString &name, int ekey )
{
 LEM_CHECKIT_Z( !name.empty() );
 lem::UCString uname( to_upper(name) );

 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs);
 #endif

 std::map< lem::UCString, const WordEntrySetItem* >::const_iterator it = wordentry_set_map.find(uname);
 if( it==wordentry_set_map.end() )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif

   it = wordentry_set_map.find(uname);
   if( it==wordentry_set_map.end() )
    {
     // Попробуем загрузить из БД.
     const int id = storage->FindWordEntrySet(name);
     if( id==UNKNOWN )
      {
       lem::MemFormatter mem;
       mem.printf( "Can not find word entry set with name %us", name.c_str() );
       throw lem::E_BaseException( mem.string() );     
      }
     else
      {
       WordEntrySetItem *ies = storage->GetWordEntrySet( id );
       wordentry_sets.push_back(ies);
       wordentry_set_map.insert( std::make_pair( to_upper(ies->name), ies ) );
       wordentry_id2set.insert( std::make_pair( id, ies ) );
       return ies->Contains(ekey);
      }
    }
   else
    {
     return it->second->Contains(ekey);
    }
  }
 else
  {
   return it->second->Contains(ekey);
  }
}


const WordEntrySetItem& WordEntrySet::GetWordEntrySet( int id )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs);
 #endif

 std::map< int, const WordEntrySetItem* >::const_iterator it = wordentry_id2set.find(id);
 if( it==wordentry_id2set.end() )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif

   std::map< int, const WordEntrySetItem* >::const_iterator it = wordentry_id2set.find(id);
   if( it==wordentry_id2set.end() )
    {
     // Попробуем загрузить из БД.
     WordEntrySetItem *ies = storage->GetWordEntrySet(id);
     wordentry_sets.push_back(ies);
     wordentry_set_map.insert( std::make_pair( to_upper(ies->name), ies ) );
     wordentry_id2set.insert( std::make_pair( id, ies ) );
     return *ies;
    }
   else
    {
     return *it->second;
    }
  }
 else
  {
   return * it->second;
  }
}


bool WordEntrySet::IsWordEntrySetName( const lem::UCString &name )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs);
 #endif

 LEM_CHECKIT_Z( !name.empty() );

 if( wordentry_set_map.find(to_upper(name))!=wordentry_set_map.end() )
  return true;

 return storage->FindWordEntrySet(name)!=UNKNOWN;
}


WordEntrySetEnumerator * WordEntrySet::ListWordEntrySets(void)
{
 return new WordEntrySetEnumerator( storage->ListWordEntrySet(), this );
}







#if defined SOL_LOADTXT && defined SOL_COMPILER
void WordEntrySet::LoadTxt_WordSet( lem::Iridium::Macro_Parser &txtfile, Dictionary &dict )
{
 lem::Iridium::BethToken t = txtfile.read();
 lem::UCString name = t.string();
 lem::UCString uname( to_upper(name) );

 if( word_set_map.find( uname )!=word_set_map.end() )
  {
   lem::Iridium::Print_Error(t,txtfile);
   dict.GetIO().merr().printf( "Word set redefinition %us\n", name.c_str() );
   throw lem::E_BaseException();   
  }

 if( IsSetName(name) )
  {
   lem::Iridium::Print_Error(t,txtfile);
   dict.GetIO().merr().printf( "%us is already a set name\n", name.c_str() );
   throw lem::E_BaseException();   
  }

 const SynPatterns & patterns = dict.GetLexAuto().GetPatternDeclarations();
 if( patterns.IsPatternName(uname) )
  {
   lem::Iridium::Print_Error(t,txtfile);
   dict.GetIO().merr().printf( "%vfC%us%vn is already a patterns name\n", name.c_str() );
   throw lem::E_BaseException();   
  }

 WordSetItem * words = new WordSetItem();
 words->name = name;

 txtfile.read_it( B_EQUAL );
 txtfile.read_it( B_OFIGPAREN );

 while( !txtfile.eof() )
  {
   if( txtfile.probe( B_CFIGPAREN ) )
    break;

   if( !words->Empty() )
    txtfile.read_it( B_COMMA );

   Solarix::Lexem word = txtfile.read().string();

   if( word.front()==L'"' )
    word.strip( L'"' );
   else if( word.front()==L'\'' )
    word.strip( L'\'' );

   dict.GetLexAuto().TranslateLexem( word, true, UNKNOWN );

   // Если это имя коллекции, то добавим себе ее содержимое.
   std::map< lem::UCString, const WordSetItem* >::const_iterator src = word_set_map.find(word);
   if( src!=word_set_map.end() )
    {
     for( std::set<lem::UCString>::const_iterator i0=src->second->words.begin(); i0!=src->second->words.end(); ++i0 )
      {
       words->InsertWord(*i0);
      }

     continue;
    }

   if( words->Contains(word) )
    {
     lem::Iridium::Print_Error(t,txtfile);
     dict.GetIO().merr().printf( "Word %us is already added to the set\n", word.c_str() );
     throw lem::E_BaseException();
    }

   words->words.insert(word);  
  }

 word_sets.push_back(words);
 storage->StoreWordSet( *words );
 LEM_CHECKIT_Z( words->GetId()!=UNKNOWN );

 word_set_map.insert( std::make_pair( to_upper(name), words ) );
 word_id2set.insert( std::make_pair( words->GetId(), words ) );

 return;
}
#endif





bool WordEntrySet::FindWordSet( const lem::UCString &name, const lem::UCString &word )
{
 LEM_CHECKIT_Z( !name.empty() );
 lem::UCString uname( to_upper(name) );

 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs);
 #endif

 std::map< lem::UCString, const WordSetItem* >::const_iterator it = word_set_map.find(uname);
 if( it==word_set_map.end() )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif

   it = word_set_map.find(uname);
   if( it==word_set_map.end() )
    {
     // Попробуем загрузить из БД.
     const int id = storage->FindWordSet(name);
     if( id==UNKNOWN )
      {
       lem::MemFormatter mem;
       mem.printf( "Can not find word set with name [%us]", name.c_str() );
       throw lem::E_BaseException( mem.string() );     
      }
     else
      {
       WordSetItem *words = storage->GetWordSet( id );
       word_sets.push_back(words);
       word_set_map.insert( std::make_pair( to_upper(words->name), words ) );
       word_id2set.insert( std::make_pair( id, words ) );
       return words->Contains(word);
      }
    }
   else
    {
     return it->second->Contains(word);
    }
  }
 else
  {
   return it->second->Contains(word);
  }
}


const WordSetItem& WordEntrySet::GetWordSet( int id )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs);
 #endif

 std::map< int, const WordSetItem* >::const_iterator it = word_id2set.find(id);
 if( it==word_id2set.end() )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif

   it = word_id2set.find(id);
   if( it==word_id2set.end() )
    {
     // Попробуем загрузить из БД.
     WordSetItem *words = storage->GetWordSet(id);
     word_sets.push_back(words);
     word_set_map.insert( std::make_pair( to_upper(words->name), words ) );
     word_id2set.insert( std::make_pair( id, words ) );
     return *words;
    }
   else
    {
     return *it->second;
    }
  }
 else
  {
   return * it->second;
  }
}


bool WordEntrySet::IsWordSetName( const lem::UCString &name )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs);
 #endif

 LEM_CHECKIT_Z( !name.empty() );

 if( word_set_map.find(to_upper(name))!=word_set_map.end() )
  return true;

 return storage->FindWordSet(name)!=UNKNOWN;
}


WordSetEnumerator * WordEntrySet::ListWordSets(void)
{
 return new WordSetEnumerator( storage->ListWordSet(), this );
}


namespace {
static void Tokenize( const lem::UFString &str, lem::Collect<lem::UFString> & lwords )
{
 lem::StrParser<lem::UFString> parser(str);
 parser.set_Delims( L",.!'\":;?*()[]=-{}@#$%&<>" );

 while( !parser.eof() )
  {
   lem::UFString tok( parser.read() );
   lwords.push_back(tok);
  }

 return;
}
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void WordEntrySet::LoadTxt_CollocationSet( lem::Iridium::Macro_Parser &txtfile, Dictionary &dict )
{
 lem::Iridium::BethToken t = txtfile.read();
 lem::UCString name = t.string();
 lem::UCString uname = to_upper(name);
 if( collocation_set_map.find( uname )!=collocation_set_map.end() )
  {
   lem::Iridium::Print_Error(t,txtfile);
   dict.GetIO().merr().printf( "Collocation set redefinition %us\n", name.c_str() );
   throw lem::E_BaseException();   
  }

 if( IsSetName(name) )
  {
   lem::Iridium::Print_Error(t,txtfile);
   dict.GetIO().merr().printf( "%us is already a set name\n", name.c_str() );
   throw lem::E_BaseException();   
  }

 const SynPatterns & patterns = dict.GetLexAuto().GetPatternDeclarations();
 if( patterns.IsPatternName(uname) )
  {
   lem::Iridium::Print_Error(t,txtfile);
   dict.GetIO().merr().printf( "%vfC%us%vn is already a patterns name\n", name.c_str() );
   throw lem::E_BaseException();   
  }

 const int id_set = storage->RegisterCollocationSet( name, false );
 collocation_set_map.insert( std::make_pair(uname,id_set) );

 txtfile.read_it( B_EQUAL );
 txtfile.read_it( B_OFIGPAREN );

 while( !txtfile.eof() )
  {
   if( txtfile.probe( B_CFIGPAREN ) )
    break;

   lem::Iridium::BSourceState collocation_beginning = txtfile.tellp();

   lem::MCollect<lem::UCString> words;
   if( txtfile.probe( B_OFIGPAREN ) )
    {
     // список слов в фигурных скобочках, каждое слово явно описывается отдельно
     while( !txtfile.eof() )
      {
       if( txtfile.probe( B_CFIGPAREN ) )
        break;

       Solarix::Lexem word = txtfile.read().string();
       word.strip(L'"');
       dict.GetLexAuto().TranslateLexem( word, true, UNKNOWN );
       words.push_back( word );
      }
    }
   else
    {
     // словосочетание задано строкой в кавычках, слова отделены пробелами и другими обычными символами-разделителями
     lem::UFString str( txtfile.read().GetFullStr() );
     str.strip(L'"');
     lem::Collect<lem::UFString> lwords;
     Tokenize( str, lwords );
     for( lem::Container::size_type k=0; k<lwords.size(); ++k )
      {
       Solarix::Lexem word( lwords[k].c_str() );
       word.trim();
       if( !word.empty() )
        {
         dict.GetLexAuto().TranslateLexem( word, true, UNKNOWN );
         words.push_back( word );
        }
      }
    }

   if( words.empty() )
    {
     lem::Iridium::Print_Error(collocation_beginning,txtfile);
     dict.GetIO().merr().printf( "Empty word collocation is not allowed\n" );
     throw lem::E_BaseException();
    }

   if( storage->FindCollocationInSet( id_set, words )!=UNKNOWN )
    {
     lem::Iridium::Print_Error(collocation_beginning,txtfile);
     dict.GetIO().merr().printf( "Word collocation is already included in set %us\n", name.c_str() );
     throw lem::E_BaseException();
    }

   storage->AddCollocationToSet( id_set, words );

   if( !txtfile.probe( B_COMMA ) )
    {
     txtfile.read_it( B_CFIGPAREN );
     break;
    }
  }

 return;
}
#endif


bool WordEntrySet::IsCollocationSetName( const lem::UCString &collocation_name )
{
 // вызов этой функции нужен только при компиляции, поэтому не будем заморачиваться
 // с поддержкой многопоточности.
 lem::UCString uname( to_upper(collocation_name) );
 std::map< lem::UCString, int >::const_iterator it = collocation_set_map.find(uname);
 return it!=collocation_set_map.end();
}


bool WordEntrySet::IsCollocationHeadword( const lem::UCString & headword, int & min_len, int & max_len )
{
 LEM_CHECKIT_Z( !headword.empty() );
 lem::UCString uheadword( to_upper(headword) );

 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs_headword);
 #endif

 std::map< lem::UCString, std::pair<int,int> >::const_iterator it = headwords_map.find(uheadword);
 if( it==headwords_map.end() )
  {
   if( headwords_loaded )
    return false; // список уже загружен из БД, и в нем слова нет - значит возвращает неуспех.

   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif

   it = headwords_map.find(uheadword);

   if( it==headwords_map.end() )
    {
     if( headwords_loaded )
      {
       return false;
      }
     
     // Попробуем загрузить из БД.
     // Так как поиск словосочетаний будет выполняться очень часто, то закешируем весь список.
     headwords_loaded = true;

     lem::Ptr<LS_ResultSet> rs( storage->ListCollocationSetHeadwords() );
     while( rs->Fetch() )
      {
       lem::UCString h( rs->GetUCString(1) );
       const int min_len0 = rs->GetInt(2);
       const int max_len0 = rs->GetInt(3);
       headwords_map.insert( std::make_pair( h, std::make_pair(min_len0,max_len0) ) );
      }
     
     // весь список загрузили, теперь ищем в нем.
     it = headwords_map.find(uheadword);
     if( it==headwords_map.end() )
      {
       return false;
      }
     else
      {
       min_len = it->second.first;
       max_len = it->second.second;
       return true;
      }
    }
   else
    {
     min_len = it->second.first;
     max_len = it->second.second;
     return true;
    }
  }
 else
  {
   min_len = it->second.first;
   max_len = it->second.second;
   return true;
  }
}


int WordEntrySet::FindCollocationSet( const lem::UCString &collocation_name )
{
 LEM_CHECKIT_Z( !collocation_name.empty() );

 lem::UCString uname( to_upper(collocation_name) );

 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs_collocation);
 #endif

 std::map< lem::UCString, int >::const_iterator it = collocation_set_map.find(uname);
 if( it==collocation_set_map.end() )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif

   it = collocation_set_map.find(uname);
   if( it==collocation_set_map.end() )
    {
     const int id = storage->FindCollocationSet( uname );
     if( id==UNKNOWN )
      {
       lem::MemFormatter mem;
       mem.printf( "Can not find collocation set with name %us", collocation_name.c_str() );
       throw lem::E_BaseException( mem.string() );     
      }

     collocation_set_map.insert( std::make_pair( uname, id ) );
     return id;
    }
   else
    {
     return it->second;
    }
  }
 else
  {
   return it->second;
  }  
}



bool WordEntrySet::FindCollocation( const lem::UCString &collocation_name, const lem::MCollect<lem::UCString> &words )
{
 LEM_CHECKIT_Z( !collocation_name.empty() );
 LEM_CHECKIT_Z( !words.empty() );

 const int id_set = FindCollocationSet( collocation_name );
 return storage->FindCollocationInSet( id_set, words )!=UNKNOWN;
}




bool WordEntrySet::IsSetName( const lem::UCString &name )
{
 LEM_CHECKIT_Z( !name.empty() );
 return IsWordEntrySetName(name) || IsWordSetName(name) || IsCollocationSetName(name) || IsWordformSetName(name);
}




bool WordEntrySet::IsWordformSetName( const lem::UCString &set_name )
{
 // вызов этой функции нужен только при компиляции, поэтому не будем заморачиваться
 // с поддержкой многопоточности.

 LEM_CHECKIT_Z( !set_name.empty() );

 lem::UCString uname( to_upper(set_name) );
 std::map< lem::UCString, int >::const_iterator it = wordform_set_map.find(uname);
 return it!=wordform_set_map.end();
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
void WordEntrySet::LoadTxt_WordformSet( lem::Iridium::Macro_Parser &txtfile, Dictionary &dict )
{
 // читаем имя множества и проверяем его уникальность.
 lem::Iridium::BethToken t = txtfile.read();
 lem::UCString name = t.string();
 lem::UCString uname(to_upper(name));
 if( wordform_set_map.find( uname )!=wordform_set_map.end() )
  {
   lem::Iridium::Print_Error(t,txtfile);
   dict.GetIO().merr().printf( "Wordform set redefinition: %vfC%us%vn\n", name.c_str() );
   throw lem::E_BaseException();   
  }

 if( IsSetName(name) )
  {
   lem::Iridium::Print_Error(t,txtfile);
   dict.GetIO().merr().printf( "%vfC%us%vn is already a set name\n", name.c_str() );
   throw lem::E_BaseException();   
  }


 const SynPatterns & patterns = dict.GetLexAuto().GetPatternDeclarations();
 if( patterns.IsPatternName(uname) )
  {
   lem::Iridium::Print_Error(t,txtfile);
   dict.GetIO().merr().printf( "%vfC%us%vn is already a patterns name\n", name.c_str() );
   throw lem::E_BaseException();   
  }

 // Регистрируем новое множество в хранилище.
 const int id_set = storage->RegisterWordformSet( uname );
 wordform_set_map.insert( std::make_pair( uname, id_set ) );

 // Теперь читаем список элементов.

 txtfile.read_it( B_EQUAL );
 txtfile.read_it( B_OFIGPAREN );
 bool first=true;

 // для контроля повторного добавления
 std::set< lem::triple<lem::UCString,int,int> > loaded_items;

 while( !txtfile.eof() )
  {
   if( txtfile.probe( B_CFIGPAREN ) )
    break;

   if( !first )
    txtfile.read_it( B_COMMA );

   first = false;

   // Считываем слово, возможно в апострофах или кавычках.
   lem::Iridium::BethToken t2 = txtfile.read();
   Solarix::Lexem lexeme = t2.string();

   if( lexeme.front()==L'\'' && lexeme.back()==L'\'' )
    lexeme.strip(L'\'');
   else if( lexeme.front()==L'"' && lexeme.back()==L'"' )
    lexeme.strip(L'"');

   dict.GetLexAuto().TranslateLexem( lexeme, true, UNKNOWN );

   // считываем список уточняющих признаков, которые должны идентифицировать словоформу.

   txtfile.read_it( B_OFIGPAREN );

   int id_class=UNKNOWN;
   CP_Array coords;

   while( !txtfile.eof() )
    {
     if( txtfile.probe( B_CFIGPAREN ) )
      break;

     if( txtfile.probe( B_CLASS ) )
      {
       txtfile.read_it( B_COLON );
       lem::Iridium::BethToken class_name = txtfile.read();
    
       id_class=dict.GetSynGram().FindClass(class_name);
       if( id_class==UNKNOWN )
        {
         lem::Iridium::Print_Error(class_name,txtfile);
         dict.GetIO().merr().printf( "Unknown class name %us\n", class_name.c_str() );
         throw lem::E_BaseException();   
        }
    
       continue;
      }
    
     // для обычных: координата:состояние
     // для бистабильных: координата
     // для согласования с координатами в именованных точках слева =имя_точки:координата
     lem::Iridium::BethToken coord_name = txtfile.read();
    
     const GramCoordAdr iglob_coord = dict.GetSynGram().FindCoord(coord_name.string());
    
     if( !iglob_coord.IsDefined() )
      {
       dict.GetIO().merr().printf( "Unknown coordinate %us\n", coord_name.c_str() );
       lem::Iridium::Print_Error(coord_name,txtfile);
       throw lem::E_BaseException();
      }
    
     if( dict.GetSynGram().coords()[iglob_coord.GetIndex()].IsBistable() )
      {
       // Имя состояния не может быть указано.
       coords.push_back(GramCoordPair(iglob_coord,1));
      }
     else
      {
       // После двоеточия должно идти имя состояния для координаты.
       txtfile.read_it(B_COLON);
    
       // Имя состояния.
       BethToken state_name = txtfile.read();
    
       // Получим индекс состояния для определенной координаты.
       const int istate = dict.GetSynGram().coords()[iglob_coord.GetIndex()]
                              .FindState(state_name.string());
       if( istate==UNKNOWN )
        {
         // Нет такого состояния для этого измерения.
         lem::Iridium::Print_Error(state_name,txtfile);
         dict.GetIO().merr().printf(
                                  "State [%vfE%us%vn] is not declared for coordinate [%vfE%us%vn]\n"
                                  , state_name.c_str(),coord_name.c_str()
                                 );
         throw E_ParserError();
        }
    
       coords.push_back( GramCoordPair(iglob_coord,istate) );
      }
    }

   // ищем подходящие словоформы
   lem::MCollect<Word_Coord> ies;
   dict.GetSynGram().FindEntryForms( lexeme, ies );

   // теперь среди них нужно отобрать те, которые соответствуют уточняющим атрибутам и части речи.

   int icur=0;
   while( icur<CastSizeToInt(ies.size()) )
    {
     const int ekey = ies[icur].GetEntry();
     const SG_Entry &e = dict.GetSynGram().GetEntry(ekey);
     if( id_class!=UNKNOWN && e.GetClass()!=id_class )
      {
       // другая часть речи, убираем из списка.
       ies.Remove(icur);
       continue; 
      }
     else
      {
       bool match=true;

       const SG_EntryForm & f = e.forms()[ ies[icur].GetForm() ];

       for( lem::Container::size_type k=0; k<coords.size(); ++k )
        {
         if( f.coords().FindOnce( coords[k] )==UNKNOWN )
          {
           match=false;
           break;
          }
        }

       if( !match )
        {
         // какая-то из координат не соответствует, убираем словоформу из списка.
         ies.Remove(icur);
         continue; 
        }
       else
        {
         icur++;
        } 
      }
    }

   if( ies.empty() )
    {
     lem::Iridium::Print_Error(t2,txtfile);
     dict.GetIO().merr().printf( "There is no word form matching the specification for '%us'\n", lexeme.c_str() );
     throw lem::E_BaseException();
    }

   const int ekey = ies.front().GetEntry();

   if( ies.size()>1 )
    {
     // проверим, что все оставшиеся варианты соответствуют одной и той же словарной статье.
     for( lem::Container::size_type i=1; i<ies.size(); ++i )
      if( ies[i].GetEntry()!=ekey )
       {
        lem::Iridium::Print_Error(t2,txtfile);
        dict.GetIO().merr().printf( "There are %d alternatives for wordform '%us'\n", CastSizeToInt(ies.size()), lexeme.c_str() );
        throw lem::E_BaseException();
       }
    }

   // сохраняем запись в справочник наборов координат
   const int id_coords = storage->StoreWordformSetCoords( coords );

   // Проверяем, что такой элемент уже не был добавлен.
   lem::triple<lem::UCString,int,int> new_item = lem::make_triple( lem::UCString(lexeme), ekey, id_coords );
   if( loaded_items.find(new_item)!=loaded_items.end() )
    {
     lem::Iridium::Print_Error(t2,txtfile);
     dict.GetIO().merr().printf( "Wordform '%us' is already added to the set\n", lexeme.c_str() );
     throw lem::E_BaseException();
    }

   loaded_items.insert( new_item );

   // Сохраняем сам элемент в множество.
   storage->StoreWordformSetItem( id_set, lexeme, ekey, id_coords );
  }

 return;
}
#endif




int WordEntrySet::FindWordformSet( const lem::UCString &set_name )
{
 LEM_CHECKIT_Z( !set_name.empty() );

 lem::UCString uname( to_upper(set_name) );

 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs_wordform);
 #endif

 std::map< lem::UCString, int >::const_iterator it = wordform_set_map.find(uname);
 if( it==wordform_set_map.end() )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif

   it = wordform_set_map.find(uname);
   if( it==wordform_set_map.end() )
    {
     const int id = storage->FindWordformSet( uname );
     if( id==UNKNOWN )
      {
       lem::MemFormatter mem;
       mem.printf( "Can not find wordform set with name %us", set_name.c_str() );
       throw lem::E_BaseException( mem.string() );     
      }

     wordform_set_map.insert( std::make_pair( uname, id ) );
     return id;
    }
   else
    {
     return it->second;
    }
  }
 else
  {
   return it->second;
  }  
}


const CP_Array & WordEntrySet::GetWordformSetCoords( int id_coords )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs_wordform);
 #endif

 std::map< int, const CP_Array* >::const_iterator it = wordform_set_coords_map.find(id_coords);
 if( it==wordform_set_coords_map.end() )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif

   it = wordform_set_coords_map.find(id_coords);
   if( it==wordform_set_coords_map.end() )
    {
     CP_Array * a = new CP_Array();
     storage->LoadWordformSetCoords( id_coords, *a );
     wordform_set_coords.push_back(a);
     wordform_set_coords_map.insert( std::make_pair( id_coords, a ) );
     return *a;
    }
   else
    {
     return *it->second;
    }
  }
 else
  {
   return *it->second;
  }  
}



bool WordEntrySet::FindWordformSet( SynGram & sg, const lem::UCString &set_name, const Solarix::Word_Form &wordform )
{
 LEM_CHECKIT_Z( !set_name.empty() );

 const int id_set = FindWordformSet( set_name );
 int id_coords=UNKNOWN;
 if( storage->FindWordformSetItem( id_set, * wordform.GetNormalized(), wordform.GetEntryKey(), &id_coords )!=UNKNOWN )
  {
   const CP_Array & required_coords = GetWordformSetCoords( id_coords );
   
   for( lem::Container::size_type i=0; i<required_coords.size(); ++i )
    {
     const GramCoordPair & p = required_coords[i];

     if( wordform.GetPairs().FindOnce(p)==UNKNOWN )
      {
       // для бистабильной координаты состояние 0 равносильно ее отсутствию.
       if( p.GetState()==0 && sg.coords()[ p.GetCoord().GetIndex() ].IsBistable() )
        continue;

       return false;
      }
    }

   return true;
  }
 else
  return false;
}
