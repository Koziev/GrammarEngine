#include <lem/smart_pointers.h>
#include <lem/oformatter.h>
#include <lem/sol_io.h>
#include <lem/solarix/Languages.h>
#include <lem/solarix/LanguageEnumerator.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/LA_CropRule.h>
#include <lem/solarix/LA_PreprocessorTrace.h>
#include <lem/solarix/LA_RecognitionTrace.h>
//#include <lem/solarix/WordSplitResults.h>
//#include <lem/solarix/TokenSplitterRx.h>
#include <lem/solarix/LA_Preprocessor.h>

using namespace Solarix;


LA_Preprocessor::LA_Preprocessor( Solarix::Dictionary *Dict )
{
 dict = Dict;
 storage = NULL;
 return;
}

void LA_Preprocessor::Connect( LexiconStorage *Storage )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker lock(&cs_init); 
 #endif

 storage = Storage;
 DeleteRules();
 return;
}

LA_Preprocessor::~LA_Preprocessor(void)
{
 DeleteRules();
 return;
}


void LA_Preprocessor::DeleteRules(void)
{
 for( lem::Container::size_type i=0; i<rules.size(); ++i )
  {
   delete rules[i];
  }

 rules.clear();
 id_langs.clear();
 all_langs.clear();

 return;
}


void LA_Preprocessor::LoadRulesFromStorage( int id_language )
{
 LA_PreprocessorRules *lang_rules = new LA_PreprocessorRules();
 
 // Для ускорения применения правил усечения мы их разделим на 2 группы - префиксы и аффиксы,
 // и выстроим индекс по коду символа, первого для префиксов и последнего для аффиксов.
 lem::Ptr<LS_ResultSet> rs3 = storage->ListCropRules(id_language);
 while( rs3->Fetch() )
  {
   const int id = rs3->GetInt(0);
   LA_CropRule *rule = storage->GetPreprocessorCropRule(id);
   if( rule->IsPrefix() )
    {
     lang_rules->prefix_crop_rules.insert( std::make_pair( rule->GetHash(), rule ) );
    }
   else if( rule->IsAffix() )
    {
     lang_rules->affix_crop_rules.insert( std::make_pair( rule->GetHash(), rule ) );
    }
   else
    LEM_STOPIT;

   lang_rules->crop_rules.push_back(rule);
  }

 
 id_langs.push_back(id_language);
 rules.push_back(lang_rules);

 return;
}


void LA_Preprocessor::LoadRules( int id_language )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs);
 #endif

 const int idx = id_langs.find(id_language);
 if( idx==UNKNOWN )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif

   LoadRulesFromStorage(id_language);

   // Правила для языка с кодом -1 применяются всегда, поэтому проверим и их в рамках текущей блокировки
   const int idxu = id_langs.find(UNKNOWN);
   if( idxu==UNKNOWN )
    {
     LoadRulesFromStorage(UNKNOWN);
    }
  }

 return;
}


const LA_PreprocessorRules* LA_Preprocessor::GetRules( int id_language ) const
{
 const int idx = id_langs.find(id_language);
 if( idx==UNKNOWN )
  {
   lem::MemFormatter mem;
   mem.printf( "Could not find the preprocessor rules for id_language=%d", id_language );
   throw lem::E_BaseException(mem.string());
  }

 return rules[idx]; 
}


// **************************************************************
// Загрузим ID всех языков и правила для этих языков.
// Это необходимо в случае, когда выполняется обработка текста
// с указанием ID языка=-1.
// **************************************************************
void LA_Preprocessor::LoadAllLangs(void)
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs_langs);
 #endif
 if( all_langs.empty() )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif
   
   Solarix::Languages &langs = dict->GetSynGram().languages();
   lem::Ptr<LanguageEnumerator> e( langs.Enumerate() );
   while( e->Fetch() )
    {
     all_langs.push_back( e->GetId() );
     LoadRules( e->GetId() );
    }
  }

 return;
}


bool LA_Preprocessor::Crop(
                           const lem::UCString &word,
                           lem::MCollect<lem::UCString> &results,
                           lem::MCollect<lem::Real1> &rels,
                           int id_language,
                           LA_RecognitionTrace *trace
                          )
{
 bool res=false;

 if( lem::is_quantor(id_language) )
  {
   LoadAllLangs();

   // Apply all rules.
   for( lem::Container::size_type j=0; j<rules.size(); ++j )
    {
     const LA_PreprocessorRules *r = rules[j];
     if( r->Crop(word,results,rels,trace) )
      {
       res=true;
       break;
      }
    }
  }
 else
  {
   LoadRules(id_language);

   #if defined LEM_THREADS
   lem::Process::RWU_ReaderGuard rlock(cs);
   #endif

   const LA_PreprocessorRules *rules1 = GetRules(id_language);
   if( !rules1->Crop(word,results,rels,trace) )
    {
     const LA_PreprocessorRules *rules2 = GetRules(UNKNOWN);
     if( rules2->Crop(word,results,rels,trace) )
      {
       res=true;
      }
    }
   else
    {
     res=true;
    }
  }

 return res;
}





#if defined SOL_LOADTXT && defined SOL_COMPILER
void LA_Preprocessor::LoadTxt(
                              const lem::Iridium::BethToken &head_token,
                              lem::Iridium::Macro_Parser &txtfile,
                              Dictionary &dict
                             )
{
 if( head_token.string().eqi(L"crop") )
  {
   LA_CropRule* r = new LA_CropRule();
   r->LoadTxt( txtfile, dict );

   if( !r->GetName().empty() && storage->FindCropRule(r->GetName())!=UNKNOWN )
    {
     lem::Iridium::Print_Error( head_token, txtfile );
     dict.GetIO().merr().printf( "Rule [%us] redefinition\n", r->GetName().c_str() );
     throw E_ParserError();
    }

   storage->StorePreprocessorCropRule(r);
  }
 
 return;
}
#endif
