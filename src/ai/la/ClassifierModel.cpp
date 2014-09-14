#include <lem/streams.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/word_form.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/BasicLexer.h>
#include <lem/solarix/ElapsedTimeConstraint.h>
#include <lem/solarix/MorphologyModels.h>

#if defined SOL_MAXENT_MODEL
#include "MaxentTaggerLib.h"
#endif


using namespace Solarix;


ClassifierModel::ClassifierModel() : BasicModel()
{
 #if defined SOL_MAXENT_MODEL
 model_handle=NULL;
 #endif
 EMIT_AA_FEATURE = false;
 EMIT_AA_FOR_CONTEXT = false;
 EMIT_PAIRWISE_FEATURE = true;
}

ClassifierModel::~ClassifierModel()
{
}


bool ClassifierModel::Load()
{
 #if defined SOL_MAXENT_MODEL
 if( !folder.empty() )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_ReaderGuard rlock(cs);
   #endif

   if( !loaded )
    {
     #if defined LEM_THREADS
     lem::Process::RWU_WriterGuard wlock(rlock);
     #endif

     lem::Path codebook_path( folder );
     codebook_path.ConcateLeaf( L"classifier.codebook" );
     if( codebook_path.DoesExist() )
      {
       codebook = new ModelCodeBook();
       lem::BinaryReader rdr(codebook_path);
       codebook->LoadBin(rdr);

       lem::Path model_path( folder );
       model_path.ConcateLeaf( L"classifier.model" );

       #if defined SOL_MAXENT_MODEL
       model_handle = MaxEntLibCreate();
       MaxEntLibLoad( model_handle, model_path.GetAscii().c_str() );
       #endif
      }

     available = codebook!=NULL;
     loaded = true;
    }
  }
 #else
 available = false;
 loaded = false;
 #endif

 return loaded;
}


namespace
{
 static bool desc_score_sorter( const std::pair<const Word_Form*, std::pair<int,double> > & a, const std::pair<const Word_Form*, std::pair<int,double> > & b )
 {
  return a.second.second > b.second.second;
 }
}

void ClassifierModel::Apply( BasicLexer & lexer, Dictionary & dict, const LexerTextPos * left, LexerTextPos * focus, const LexerTextPos * right )
{
 #if defined SOL_MAXENT_MODEL && defined SOL_CAA
 if( focus->GetWordform()->VersionCount()<2 )
  return;

 lem::PtrCollect<ModelTokenFeatures> token_features;
 for( lem::Container::size_type j=0; j<3; ++j )
  {
   const LexerTextPos * token;
   if( j==0 )
    token = left;
   else if( j==1 )
    token = focus;
   else if( j==2 )
    token = right;

   ModelTokenFeatures * f;
   if( token->IsBegin() )
    f = Get_START_Features();
   else if( token->IsEnd() )
    f = Get_END_Features();
   else
    f = GetFeatures( token, dict );

   token_features.push_back(f);
  }

 lem::MCollect<lem::CString> str_features;
 for( int iword=0; iword<CastSizeToInt(token_features.size()); ++iword )
  {
   // -----------------------------
   // признаки для текущего слова
   // -----------------------------
   PullFeatures1( str_features, token_features, iword, 0, true, EMIT_AA_FEATURE );
   
   // и соседние слова
   PullFeatures1( str_features, token_features, iword, -1, false, EMIT_AA_FOR_CONTEXT );
   PullFeatures1( str_features, token_features, iword, 1, false, EMIT_AA_FOR_CONTEXT );
   
   if( EMIT_PAIRWISE_FEATURE )
    {
     PullFeatures2( str_features, token_features, iword, -1, 0 );
     PullFeatures2( str_features, token_features, iword, 0, 1 );
    }
  }

 char const ** maxent_features = new const char*[ str_features.size() ];

 for( lem::Container::size_type i=0; i<str_features.size(); ++i )
  maxent_features[i] = str_features[i].c_str();

 lem::MCollect<const ModelTagMatcher *> matchers;
 std::multimap< const ModelTagMatcher *, int > matcher2wordform;

 lem::MCollect< std::pair<const Word_Form*, std::pair<int,double> > > src_versions;

 for( int iversion=0; iversion<focus->GetWordform()->VersionCount(); ++iversion )
  {
   const Word_Form * version = focus->GetWordform()->GetVersion(iversion);
   const ModelTagMatcher * tag_matcher = codebook->Match( version, dict );

   src_versions.push_back( std::make_pair(version, std::make_pair(version->GetScore(),1.0)) );

   if( tag_matcher!=NULL )
    {
     if( matchers.find(tag_matcher)==UNKNOWN )
       matchers.push_back( tag_matcher );

     matcher2wordform.insert( std::make_pair( tag_matcher, CastSizeToInt(src_versions.size())-1 ) );
    }
  }

 for( lem::Container::size_type i=0; i<matchers.size(); ++i )
  {
   const ModelTagMatcher * matcher = matchers[i];
   const int tag_id = matcher->GetId();
   lem::CString str_tag = lem::to_str(tag_id);

   double p = MaxEntLibEval( model_handle, maxent_features, str_features.size(), str_tag.c_str() );

   typedef std::multimap< const ModelTagMatcher *, int >::iterator IT;
   std::pair<IT,IT> pit = matcher2wordform.equal_range(matcher);
   for( IT it=pit.first; it!=pit.second; ++it )
    {
     const int iver = it->second;
     src_versions[iver].second.second = p;
    }
  }

 std::stable_sort( src_versions.begin(), src_versions.end(), desc_score_sorter );

 lem::MCollect<const Word_Form*> sorted_versions;
 for( lem::Container::size_type i=0; i<src_versions.size(); ++i )
  sorted_versions.push_back( src_versions[i].first );

 Word_Form * new_token_wordform = new Word_Form( sorted_versions );

 #if defined SOL_DEBUGGING
 if( lexer.GetTrace()!=NULL )
  {
   lexer.GetTrace()->ClassifierModelApplied( focus->GetWordform(), new_token_wordform );
  }
 #endif

 lexer.ReplaceTokenWordform( focus, new_token_wordform );

 delete[] maxent_features;

 #endif

 return;
}
