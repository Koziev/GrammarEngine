#if !defined MorphologyModels__H
#define MorphologyModels__H

#include <lem/noncopyable.h>
#include <lem/path.h>
#include <lem/ucstring.h>
#include <lem/containers.h>
#include <lem/ptr_container.h>
#include <lem/RWULock.h>
#include <lem/solarix/coord_pair.h>

#if defined SOL_CRF_MODEL
#include <crfsuite.h>
#endif

namespace Solarix
{
 class Word_Form;
 class Dictionary;
 class ModelTagMatcher : lem::NonCopyable
 {
  private:
   lem::int32_t id;
   lem::UCString lexeme;
   lem::MCollect<int> id_lemma;
   lem::MCollect<int> pos;
   lem::MCollect<Solarix::GramCoordPair> pairs;

  public:
   ModelTagMatcher();
   void LoadBin( lem::Stream & bin );

   bool Match( const Word_Form & wf, Dictionary & dict ) const;
   int GetId() const { return id; }

   void Print( lem::OFormatter & to, Dictionary & dict ) const;
 };


 class LexerTextPos;
 class ModelCodeBook : lem::NonCopyable
 {
  private:
   lem::int32_t suffix_len;
   lem::int32_t context_size; // полуразмер:  +/- слов от фокуса
   std::set<lem::UCString> undividable_words;
   lem::PtrCollect<ModelTagMatcher> matchers;
   std::map<int,const ModelTagMatcher*> id2matcher;

   std::map<lem::UCString,int> suffices;
   lem::int32_t START_id, END_id; // id тегов для границ

  public:
   static void LoadUtf8( lem::Stream & bin, lem::UCString & str );

  public:
   ModelCodeBook();
   void LoadBin( lem::Stream & bin );
   const ModelTagMatcher* GetTagMatcher( int id ) const;
   
   const ModelTagMatcher* Match( const Word_Form * version, Dictionary & dict ) const;

   int GetSuffixId( const LexerTextPos * token ) const;
   bool DetectAa( const LexerTextPos * token ) const;
   int GetSTART() const { return START_id; }
   int GetEND() const { return END_id; }

   int GetContextSize() const { return context_size; }
 };


 struct ModelTokenFeatures : lem::NonCopyable
 {
  int suffix_id;
  bool Aa;
  std::string POS_N; // сущ
  std::string POS_PRN ; // местоим
  std::string POS_PRN2; // местоим_сущ
  std::string POS_A; // прил
  std::string POS_V; // гл
  std::string POS_IMV; // безлич. гл.
  std::string POS_I; // инф
  std::string POS_Y; // нареч
  std::string POS_VY; // дееприч
  std::string POS_D; // числительное
  std::string POS_C; // число
  std::string POS_P; // предлог
  std::string POS_PX; // послелог
  std::string POS_PP; // притяж_частица

  lem::MCollect<lem::UCString> str_features;

  ModelTokenFeatures();
 };

 class BasicLexer;
 class ElapsedTimeConstraint;
 class SequenceLabelerModel;
 class ClassifierModel;

 class MorphologyModels : lem::NonCopyable
 {
  private:
   SequenceLabelerModel * sequence_labeler;
   ClassifierModel * classifier;

  public:
   MorphologyModels();
   ~MorphologyModels();

   SequenceLabelerModel & GetSequenceLabeler() const { return *sequence_labeler; }
   ClassifierModel & GetClassifier() const { return *classifier; }
 };



 class BasicModel : lem::NonCopyable
 {
  protected:
   #if defined LEM_THREADS
   lem::Process::RWU_Lock cs;
   #endif

   lem::Path folder;
   ModelCodeBook * codebook;
   bool loaded;
   volatile bool available;

   virtual bool Load()=0;

   ModelTokenFeatures* Get_START_Features() const;
   ModelTokenFeatures* Get_END_Features() const;
   ModelTokenFeatures* GetFeatures( const LexerTextPos * token, const Dictionary & dict ) const;

   void PullFeatures1( lem::MCollect<lem::CString> & b, const lem::PtrCollect<ModelTokenFeatures> & token_features, int ifocus, int offset, bool rich_set, bool emit_Aa_feature ) const;
   void PullFeatures2( lem::MCollect<lem::CString> & b, const lem::PtrCollect<ModelTokenFeatures> & token_features, int ifocus, int offset1, int offset2 ) const;
   void PullFeatures3( lem::MCollect<lem::CString> & b, const lem::PtrCollect<ModelTokenFeatures> & token_features, int ifocus, int offset1, int offset2, int offset3 ) const;

  public:
   BasicModel();
   virtual ~BasicModel();

   bool IsAvailable();
   void SetModelPath( const lem::Path & p ) { folder=p; }
 };



 class SequenceLabelerModel : public BasicModel
 {
  private:
   #if defined SOL_CRF_MODEL
   crfsuite_model_t *model;
   crfsuite_dictionary_t *attrs, *labels;
   crfsuite_tagger_t *tagger;
   #endif

   bool EMIT_PAIRWISE_FEATURE;
   bool EMIT_TRIPLE_FEATURE;
   bool EMIT_AA_FEATURE;
   bool EMIT_AA_FOR_CONTEXT;
   int CONTEXT_SIZE;

   virtual bool Load();

   void SelectRecognition(
                          BasicLexer & lexer,
                          const LexerTextPos * token,
                          const std::multimap< const LexerTextPos*, int > & token2selection,
                          bool remove_incorrect_alts
                         ) const;

  public:
   SequenceLabelerModel();
   ~SequenceLabelerModel();

   void Apply( BasicLexer & lexer, Dictionary & dict, const ElapsedTimeConstraint & constraints, bool remove_incorrect_alts );
 };


 class ClassifierModel : public BasicModel
 {
  protected:
   #if defined SOL_MAXENT_MODEL
   void * model_handle;
   #endif
   bool EMIT_AA_FEATURE;
   bool EMIT_AA_FOR_CONTEXT;
   bool EMIT_PAIRWISE_FEATURE;


   virtual bool Load();

  public:
   ClassifierModel();
   ~ClassifierModel();

   void Apply( BasicLexer & lexer, Dictionary & dict, const LexerTextPos * left, LexerTextPos * focus, const LexerTextPos * right );
 };

 
}

#endif
