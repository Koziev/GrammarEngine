#ifndef PHRASE_GENERATOR__H
#define PHRASE_GENERATOR__H
#pragma once

 #if defined GM_PHRASE_GENERATOR

 #include <lem/config.h>
 #include <lem/process.h>
 #include <lem/solarix/_sg_api.h>
 #include <lem/solarix/SG_TagFilter.h>
 #include <lem/solarix/ml_projections.h>

namespace Solarix
{ 
 class Faind_Engine;
}

 #include <lem/math/random.h>
 #include <lem/solarix/dictionary.h>
 #include <lem/solarix/sg_autom.h>
 #include <lem/solarix/gg_autom.h>
 #include <lem/solarix/phrasema.h>


 struct ClearFlags
 {
  lem::zbool f_nouns, f_attribs, f_gerunds1, f_verbs, f_infs,
             f_gerunds2, f_prepos, f_adverbs;
 };


struct SynSubst : lem::NonCopyable
{
 lem::UFString old_word;
 lem::UFString new_word;
 lem::zbool complex;

 SynSubst( const lem::UFString &Old, const lem::UFString &New ) : old_word(Old), new_word(New) {}
};

struct WordSyn1 : lem::NonCopyable
{
 lem::UCString new_word; // подставляемый синоним
 lem::PtrCollect<SynSubst> substs; // все подстановки, которые придется выполнить для данной синонимизации,
                                   // включая пересогласование зависимых слов.
 bool simple; // вариант замены 1 на 1 слово
 int dependency_2gram_hits;

 WordSyn1(void) : simple(true), dependency_2gram_hits(0) {}
};


struct WordSyns : lem::NonCopyable
{
 lem::UCString org_word; // исходное синонимизируемое слово
 lem::MCollect<lem::UCString> alts; // варианты замены слова
 lem::PtrCollect<WordSyn1> syns; // варианты замены со всей дополнительной информацией - сопутствующими заменами
 bool all_are_simple; // все варианты синонимизации были простые, 1 слово на 1 слово

 lem::MCollect<float> hits; // частоты N-грамм, в которых поучаствовало слово
 lem::MCollect<float> rels; //  достоверности замены, без учета N-грамм

 bool HasSynonyms(void) const { return alts.size()>1; }
 int Count(void) const { return CastSizeToInt(alts.size()); }
 const lem::UCString& GetWord( int i ) const { return alts[i]; }
 void AddHit( int i, float freq ) { hits[i] += freq; }

 WordSyns( const lem::UCString &original_word );

 int SelectRandomSyn() const;

 void GetStat( float & max_hits, float & average_hits ) const;
 void RemoveUnmatchedSynonyms( float min_freq );
 void SortSynonymsByHits();
 void RemoveUnverified2();
 bool FindSyn( const lem::UCString &x ) const;
};


 class SynonymizerDebugger
 {
  protected:
   SynonymizerDebugger() {}

  public:
   virtual void PhrasalSynonyms( const lem::UCString & word, const lem::Collect<lem::UFString> & linked_phrases )=0;
   virtual void Synonyms( int id_entry, const lem::MCollect<int> id_entries )=0;
   virtual void FinalSubstitutions( const lem::MCollect<SynSubst*> & substs )=0;

   virtual void NGram( bool lemmatized, const lem::MCollect<lem::UCString> & words, bool found, int freq )=0;

   virtual void AfterDependencyFilter( const lem::MCollect<int> & syn_id_entry )=0;

   virtual void AvailableSubstitutions( const lem::MCollect<WordSyns*> & substs )=0;
   virtual void FilteredSubstitutions( const lem::MCollect<WordSyns*> & substs )=0;
 };



 // *************************************************************************
 // Контекст создания одного предложения - для учета уже использованных слов.
 // Инициализируется заново для каждого предложения.
 // *************************************************************************
 struct GeneratorContext : lem::NonCopyable
 {
  lem::MCollect<int> subject_noun_ie;

  lem::MCollect<int> used_nouns, used_adjs, used_verbs_perfect, used_verbs_imperfect,
                     used_infs_perfect, used_infs_imperfect, used_adverbs, used_gerunds2;

  lem::MCollect<int> boost_nouns, boost_adjs, boost_verbs_imperfect,
                     boost_verbs_perfect, boost_infs_perfect, boost_infs_imperfect,
                     boost_adverbs, boost_gerund1, boost_gerund2;

  int last_verb(void) const;
  int last_inf(void) const;
 };


class Picker_RU
{
 private:
  lem::Process::CriticalSection cs_scan_entries;
  volatile bool entries_scanned;
  lem::Process::CriticalSection cs;

  lem::zbool filtered;
  lem::Ptr<Solarix::Dictionary> dict;
  Solarix::SynGram *sg;

  // Рабочие фильтрованные списки
  lem::MCollect<int> adverbs, attribs, gerunds1, gerunds2, nouns, verbs_perfect, verbs_imperfect,
                     infs_perfect, infs_imperfect, prepos;

  // Нефильтрованные списки
  lem::MCollect<int> adverbs0, attribs0, gerunds10, gerunds20, nouns0, verbs_perfect0, verbs_imperfect0,
                     infs_perfect0, infs_imperfect0, prepos0;

  // Копия отфильтрованных списков
  lem::MCollect<int> adverbs1, attribs1, gerunds11, gerunds21, nouns1, verbs_perfect1, verbs_imperfect1,
                     infs_perfect1, infs_imperfect1, prepos1;

  std::set<int> stop_words; // id статей, которые нельзя использовать. 

  lem::MCollect< lem::triple<int /*ientry*/,bool/*wants_imperfect*/,bool/*wants_perfect*/> > modverbs1, modverbs2; // модальные глаголы

  int to_be_ie; // глагол БЫТЬ
  int to_be_ie2; // инфинитив БЫТЬ

  lem::Collect< lem::UFString > intros1, intros2, intros3;

  void Init( const Picker_RU &x );

  void AddEntry( int ie, bool clear_previous, ClearFlags& flags );

  void AddStopWord( int ie );

  int GetEntry(
               GeneratorContext &context,
               int flags,
               lem::MCollect<int> &work_list,
               const lem::MCollect<int> &filtered_list,
               const lem::MCollect<int> &fulllexicon_list,
               bool *can_rollback=NULL
              );

 public:
  Picker_RU( const Picker_RU &x );
  Picker_RU( lem::Ptr<Solarix::Dictionary> Dict );

  void operator=( const Picker_RU &x );

  void ScanWordEntries(void);
  void ApplyFilter( const int *ies, int n, bool use_thesaurus );

  void NewPhrase(void);

  lem::UFString GetAdverb( GeneratorContext &context, int flags ); // наречия
  int GetAdverbIE( GeneratorContext &context, int flags );

  lem::UFString GetGerund2( GeneratorContext &context, int flags ); // деепричастия
  int GetGerund2IE( GeneratorContext &context, int flags );

  lem::UFString GetAttrib( GeneratorContext &context, int Gender, int Case, int Number, int flags ); // прилагательные
  lem::UFString GetGerund1( GeneratorContext &context, int Gender, int Case, int Number, int flags ); // причастия
  int GetAdjIE( GeneratorContext &context, int flags );

  lem::UFString GetNoun( GeneratorContext &context, int &Gender, int Case, int Number, int flags );   // существительное
  int GetNoun( GeneratorContext &context, int flags );

  lem::UFString GetVerb( GeneratorContext &context, int Tense, int Gender, int Number, int flags );
  int GetVerbIE( GeneratorContext &context, int flags );

  lem::UFString GetModalVerb(
                             GeneratorContext &context,
                             int Tense,
                             int Gender,
                             int Number,
                             int flags,
                             bool &wants_imperfect,
                             bool &wants_perfect
                            );

  lem::UFString GetIntro1(void); // пустая вводная конструкция для утверждений
  lem::UFString GetIntro2(void); // пустая вводная конструкция для вопросов
  lem::UFString GetIntro3(void); // пустая конструкция с выражением уверенности

  lem::UFString GetInf1( GeneratorContext &context, int flags ); // несовершенные инфинитивы
  int GetInf1IE( GeneratorContext &context, int flags );

  lem::UFString GetInf2( GeneratorContext &context, int flags ); // совершенные инфинитивы
  int GetInf2IE( GeneratorContext &context, int flags );

  lem::UFString GetPrepos( int &Case );
  int /*ientry*/ GetPrepos(void);

  lem::UFString SelectNoun( GeneratorContext &context, int Gender, int Animate, int Case, int Number, int flags );
};


class Picker_EN
{
 private:
  lem::Process::CriticalSection cs;

  lem::zbool filtered;
  lem::Ptr<Solarix::Dictionary> dict;
  Solarix::SynGram *sg;

  // Рабочие фильтрованные списки
  lem::MCollect<int> adverbs, attribs, gerunds1, gerunds2, nouns, verbs, prepos;

  // Нефильтрованные списки
  lem::MCollect<int> adverbs0, attribs0, gerunds10, gerunds20, nouns0, verbs0, prepos0;

  // Копия отфильтрованных списков
  lem::MCollect<int> adverbs1, attribs1, gerunds11, gerunds21, nouns1, verbs1, prepos1;

  std::set<int> stop_words; // id статей, которые нельзя использовать. 

  lem::MCollect<int> modverbs; // модальные глаголы

  int to_be_ie; // глагол TO BE
  int to_have_ie; // глагол TO HAVE
  int to_do_ie; // глагол TO DO

  lem::Collect< lem::UFString > intros1, intros2, intros3;

  void Init( const Picker_EN &x );

  void AddEntry( int ie, bool clear_previous, ClearFlags& flags );

  void AddStopWord( int ie );

  int GetEntry(
               GeneratorContext &context,
               lem::MCollect<int> &work_list,
               lem::MCollect<int> &filtered_list
              );

 public:
  Picker_EN( const Picker_EN &x );
  Picker_EN( lem::Ptr<Solarix::Dictionary> Dict );

  void operator=( const Picker_EN &x );
  
  void ApplyFilter( const int *ies, int n, bool use_thesaurus );

  void NewPhrase(void);

  lem::UFString GetAdverb( GeneratorContext &context ); // наречия

  lem::UFString GetAttrib( GeneratorContext &context ); // прилагательные

  lem::UFString GetNoun( GeneratorContext &context, int Number );   // существительное

  lem::UFString GetVerb( Solarix::Ngrams* ngrams, GeneratorContext &context, int Tense, int Tense2, int Number, int Voice, int Person );
  lem::UFString GetInf( Solarix::Ngrams* ngrams, GeneratorContext &context );

  lem::UFString GetModalVerb(
                             GeneratorContext &context,
                             int Tense,
                             int Number,
                             int Person
                            );

  lem::UFString GetIntro1(void); // пустая вводная конструкция для утверждений
  lem::UFString GetIntro2(void); // пустая вводная конструкция для вопросов
  lem::UFString GetIntro3(void); // пустая конструкция с выражением уверенности

  lem::UFString GetPrepos(void);

  lem::UFString GetCompoundAdverbForVerb( Solarix::Ngrams* ngrams, GeneratorContext &context, int ie_verb );
};



 typedef enum { NoneLogic, AndLogic, OrLogic, ButNotLogic } LogicType;

 inline bool FG_PROBE( int flags, int mask ) { return (flags&mask)==mask; }


 struct FG_Stats
 { 
  lem::zbool processed;
  lem::zbool changed;
  lem::zint n_subst;

  void Clear(void) { processed=changed=false; n_subst=0; }
 };

 

 struct SimpleSynSubst : public SynSubst
 {
  SimpleSynSubst( const lem::UFString &Old, const lem::UFString &New ) : SynSubst(Old,New) {}
 };


 struct ComplexSynSubst : public SynSubst
 {
  ComplexSynSubst( const lem::UFString &Old, const lem::UFString &New ) : SynSubst(Old,New) { complex=true; }
 };

 



 class PhraseGenerator
 {
  protected:
   lem::Process::CriticalSection cs;
   lem::Ptr<Solarix::Ngrams> ngrams;

   int paragraph_code; // в время генерации группы связанных предложений - ID шаблона группы
   int paragraph_isent; // и номер предложения в нем.

   std::set<int> stop_synonyms; // не-синонимизируемые слова /*ientry*/
   std::set<lem::UCString> stop_synonyms2; // не-синонимизируемые слова в виде явно заданных лексем

   int CHAIN_ORDER;
   typedef std::map< lem::UFString /*prefix*/, lem::MCollect< std::pair<lem::UCString,int> > > CHAINS_MAP;
   typedef CHAINS_MAP::iterator CHAINS_IT;
   CHAINS_MAP chains;

   lem::Collect< std::pair<int /*weight*/, lem::UFString > > startings; // стартовые цепочки с весами
   int startings_wsum; // суммарный вес стартовых цепочек

   virtual void BeforeAddingLexem( lem::UFString & buffer2, const lem::UFString & lexem ) {}

   virtual lem::UCString ConvertToBase( const lem::UCString &word );

   // Список лексем, которые являются разделителями для N-грамм
   std::set<lem::UCString> ngram_delims;
   bool IsNgramDelim( const lem::UCString &w ) const;

   virtual int SubstSynonyms(
                             const Solarix::Sentence &sent,
                             int PhraseTypeFlags,
                             int SyntaxAnalysisFlags,
                             int NGramFlags,
                             int ThesaurusFlags,  
                             int DebugFlags,  
                             int ResultsFormat,
                             lem::UFString &buffer2,
                             const lem::PtrCollect<SynSubst>& subst,
                             SynonymizerDebugger * trace
                            );

   // Вызывается языковыми модулями для коррекции эффектов токенизатора - удаления
   // лишних пробелов и т.д.
   virtual void CorrectTokenizationEffects( lem::UFString &str ) const;

   void StopSynonym( int ie );
   void StopSynonym( const lem::UCString &word );

  public:
   Solarix::Faind_Engine *gren;
   lem::Ptr<Solarix::Dictionary> dict;
   static lem::Math::RandU rnd;
   lem::Ptr<Solarix::SG_TagFilter> tags_ptr; // скомпилированные тэги для фильтрации синонимов

   PhraseGenerator( Solarix::Faind_Engine *Gren );

   virtual ~PhraseGenerator(void) {}

   inline Solarix::Ngrams* GetNgrams(void) { return ngrams.IsNull() ? NULL : &*ngrams; }
   inline Solarix::Dictionary* GetDict(void) { return &*dict; }
 
   virtual void Randomize(void);
   virtual void GeneratePhrase( int phrase_type, int DebugFlags, lem::UFString &result )=0;
   virtual void ApplyFilter( const int *ies, int n, bool use_thesaurus )=0;
   virtual void ApplyFilter2Grams( const int *ies, int npairs )=0;
   virtual void StopSynonyms( const int *ies, int n, bool use_thesaurus );
   virtual std::pair<int/*words*/,int/*entries*/> LoadStopSynonyms( const lem::Path &p );
   virtual bool Paraphrase(
                           int PhraseTypeFlags,
                           int SyntaxAnalysisFlags,
                           int NGramFlags,
                           int ThesaurusFlags,  
                           int DebugFlags,  
                           int ResultsFormat,
                           lem::UFString &result,
                           int max_subst,
                           FG_Stats *stats,
                           int max_elapsed_msec,
                           SynonymizerDebugger * trace
                          )=0;

   virtual void LoadNGrams(void);

   bool IsAcceptableSynonym( int ie ) const;
   bool IsAcceptableSynonym( const lem::UCString &word ) const;

   virtual int GetTargetLanguage(void)=0;

   virtual void BuildChains( const lem::Path &filename, int order );
   void GeneratePhraseByChains( lem::UFString &result, int max_size );

   void SetTags( const lem::UFString &tags );
 };

 extern lem::UFString alt( const lem::UFString &s );
 extern lem::UFString alt( const lem::UFString &s1, const lem::UFString &s2 );
 extern lem::UFString alt( const lem::UFString &s1, const lem::UFString &s2, const lem::UFString &s3 );

 extern const wchar_t* alt( const wchar_t *s );
 extern const wchar_t* alt( const wchar_t *s1, const wchar_t *s2 );
 extern const wchar_t* alt( const wchar_t *s0, const wchar_t *s1, const wchar_t *s2 );
 extern const wchar_t* alt( const wchar_t *s0, const wchar_t *s1, const wchar_t *s2,
                            const wchar_t *s3, const wchar_t *s4 );
 extern const wchar_t* alt( const wchar_t *s0, const wchar_t *s1, const wchar_t *s2, const wchar_t *s3 );
 extern const wchar_t* alt( const wchar_t *s0, const wchar_t *s1, const wchar_t *s2,
                            const wchar_t *s3, const wchar_t *s4, const wchar_t *s5,
                            const wchar_t *s6
                           );

 class PhraseGenerator_RU;

 class GroupGenerator
 {
  public:
   GroupGenerator(void) {}
   virtual ~GroupGenerator(void) {}

   virtual bool NextPhrase( PhraseGenerator_RU *fg, GeneratorContext &context, int phrase_type, int isent, lem::UFString &result )=0;
 };

 class GroupGenerator0 : public GroupGenerator
 {
  public:
   GroupGenerator0(void) {}

   virtual bool NextPhrase( PhraseGenerator_RU *fg, GeneratorContext &context, int phrase_type, int isent, lem::UFString &result );
 };


 struct WordPtr
 {
  int iclass; // грамматический класс
  int ie; // статья (семантический центр для сверток!)
  lem::UCString word; // лексическое представление слова
  const Solarix::Tree_Node* node; // узел в графе
  int iword; // порядковый номер в исходном предложении  

  WordPtr(void) { node=NULL; iword=iclass=ie=UNKNOWN; }
 };


 struct WordLinked : lem::NonCopyable
 {
  WordPtr head; // синонимизируемая часть речи

  lem::zbool conservative;
  lem::PtrCollect<Solarix::Word_Form> forms; // для особых случаев синонимизации существительных,
                                            // прилагательных и глаголов, когда надо соблюдать
                                            // условие грамматической консервативности замены.

  lem::MCollect<WordPtr> linked; // связанные с ним слова, нуждающиеся в согласовании

  lem::MCollect<WordPtr> dependencies_parent; // связь к родительскому узлу
  lem::MCollect<WordPtr> dependencies_children; // связи к подключенным веткам

  bool HasDependencies() const { return !dependencies_parent.empty() || !dependencies_children.empty(); }

  void AddDependency( const WordPtr & word, lem::MCollect<int> & dep_entries, lem::MCollect<int> & dep_on_left ) const;
  void GetDependencies( lem::MCollect<int> & dep_entries, lem::MCollect<int> & dep_on_left ) const;
 };


class NodeVisitor : lem::NonCopyable
{
 public:
  Solarix::SynGram &sg;
  lem::PtrCollect< WordLinked > words;
  lem::MCollect<int> aux_key, aux_ie;

 protected:
  std::set<int> classes; // индексы обрабатываемых классов

  virtual void ExtractSemanticCenter( const Solarix::Word_Form &wf, WordPtr &word );
  virtual void ExtractGrammarCenter( const Solarix::Word_Form &wf, WordPtr &word );

  void CollectDependencies( const Solarix::Tree_Node * parent, const Solarix::Tree_Node * node, WordLinked * word ) const;

 public:
  NodeVisitor( Solarix::SynGram &Sg );
  virtual ~NodeVisitor(void) {}

  virtual bool operator()( const Solarix::Tree_Node *parent, const Solarix::Tree_Node *node, int ic0 )=0;

  virtual bool operator()( const Solarix::Tree_Node *parent, const Solarix::Tree_Node *node );

  bool empty(void) const { return words.empty(); } 
 };


 class RawOtherCollector : public NodeVisitor
 {
  private:
   lem::PtrCollect<Solarix::Tree_Node> nodes;

  protected:
   lem::MCollect<int> classes;

   virtual bool CanBeSynonymized( const Solarix::MLProjList & job, int & use_iclass, int & ijob ) const;

  public:
   RawOtherCollector( Solarix::SynGram &Sg );

   virtual bool operator()( const Solarix::Tree_Node *parent, const Solarix::Tree_Node *node, int ic0 ) { LEM_STOPIT; return false; }

   virtual void Collect( const Solarix::Sentence &sent );
 };



 class OtherCollector : public NodeVisitor
 {
  protected:
   lem::MCollect<int> logics; // индексы статей логических конструкций
   std::set<int> stopwords; // индексы статей, которые нельзя пытаться менять 

  public:
   OtherCollector( Solarix::SynGram &Sg );

   virtual bool operator()( const Solarix::Tree_Node *parent, const Solarix::Tree_Node *node, int ic0 );
 };



 class PhraseGenerator_RU : public PhraseGenerator
 {
  public:
   lem::Ptr<Picker_RU> base_picker;
   lem::Ptr<Picker_RU> picker;

  private:

   struct FoundSynonymsStat
   {
    lem::zbool gender_changes; // были ли у существительных при синонимизации изменения рода
   };

   // Модули для генерирования различных связанных групп предложений
   lem::PtrCollect<GroupGenerator> group_gens;
   lem::MCollect<int> igens; // исчерпываемый список ожидающих генераторов групп.

   virtual int GetTargetLanguage(void) { return RUSSIAN_LANGUAGE; }

   virtual void BeforeAddingLexem( lem::UFString & buffer2, const lem::UFString & lexem );
 
   void BoostVerbs(
                   GeneratorContext& context,
                   lem::MCollect<std::pair<int/*ientry*/,float> >& verbs
                  );

   void PickPreposNoun(
                       GeneratorContext &context,
                       int phrase_type,
                       lem::UFString &prepos,
                       lem::UFString &noun
                      );

   void PickPreposNounForVerb( 
                              int ie_inf,
                              GeneratorContext &context,
                              int phrase_type,
                              lem::UFString &prepos,
                              lem::UFString &noun
                             );

   void GetRightAddForVerb(
                           int ie_inf,
                           GeneratorContext& context,
                           int phrase_type,
                           lem::UFString &right_add
                          );

   virtual void CorrectTokenizationEffects( lem::UFString &str ) const;
 
  protected:

   friend class GroupGenerator0;

   void AddPair( int ie1, int ie2 );

   void GetAtomicGerund1(
                         GeneratorContext &context,
                         int phrase_type,
                         lem::UFString &result,
                         int Gender = MASCULINE_GENDER_ru, // род
                         int Case = NOMINATIVE_CASE_ru, // падеж
                         int Number = SINGULAR_NUMBER_ru // число 
                        );

   void GetAtomicGerund2(
                         GeneratorContext& context,
                         int phrase_type,
                         lem::UFString &result
                        );

   void GetAtomicAttributeForNoun(
                                  GeneratorContext &context,
                                  int phrase_type,
                                  lem::UFString &result,
                                  int Gender = MASCULINE_GENDER_ru, // род
                                  int Case = NOMINATIVE_CASE_ru, // падеж
                                  int Number = SINGULAR_NUMBER_ru // число 
                                 );


   void GetCompoundAttributeForNoun(
                                    GeneratorContext &context,
                                    int phrase_type,
                                    lem::UFString &result,
                                    int Gender = MASCULINE_GENDER_ru, // род
                                    int Case = NOMINATIVE_CASE_ru,    // падеж
                                    int Number = SINGULAR_NUMBER_ru   // число
                                   );

   void GetAtomicSubject(
                         GeneratorContext &context,
                         int phrase_type,
                         lem::UFString &result,
                         int Case = NOMINATIVE_CASE_ru, // падеж
                         int Number = SINGULAR_NUMBER_ru, // число 
                         int *Gender=NULL  
                        );

   void GetCompoundSubject(
                           GeneratorContext &context,
                           int phrase_type,
                           lem::UFString &result,
                           int Case = NOMINATIVE_CASE_ru, // падеж
                           int Number = SINGULAR_NUMBER_ru // число 
                          );

   void GetAtomicPredicate(
                           GeneratorContext &context,
                           int phrase_type,
                           lem::UFString &result,
                           int Gender,
                           int Number,
                           int Tense
                          );

   // ФИОЛЕТОВЫЙ АЛЬТАИР ОСВЕЩАЕТ КОНОПЛЯНОЕ ПОЛЕ
   lem::UFString& GeneratePhrase0(
                                  GeneratorContext& context,
                                  int phrase_type,
                                  int DebugFlags, 
                                  lem::UFString &result
                                 );

   // ГАЛАКТИКА ЯВЛЯЕТСЯ ЗВЕЗДНЫМ ОСТРОВОМ.
   lem::UFString& GeneratePhrase1(
                                  GeneratorContext& context,
                                  int phrase_type,
                                  int DebugFlags, 
                                  lem::UFString &result
                                 );


   // ГАЛАКТИКА ЭТО ЗВЕЗДНЫЙ ОСТРОВ.
   lem::UFString& GeneratePhrase2(
                                  GeneratorContext& context,
                                  int phrase_type,
                                  int DebugFlags, 
                                  lem::UFString &result
                                 );


   // ОСВЕЩАЕТ ЛИ КОНОПЛЯНОЕ ПОЛЕ ФИОЛЕТОВЫЙ АЛЬТАИР?
   lem::UFString& GeneratePhrase3(
                                  GeneratorContext& context,
                                  int phrase_type,
                                  int DebugFlags, 
                                  lem::UFString &result
                                 );


   // А АЛЬТАИР-ТО ОСВЕЩАЕТ КОНОПЛЯНОЕ ПОЛЕ!
   lem::UFString& GeneratePhrase4(
                                  GeneratorContext& context,
                                  int phrase_type,
                                  int DebugFlags, 
                                  lem::UFString &result
                                 );


   void FindSynonyms(
                     int PhraseTypeFlags,
                     int SyntaxAnalysisFlags,
                     int NGramFlags,
                     int ThesaurusFlags,  
                     int DebugFlags,  
                     int ResultsFormat,
                     const Solarix::Sentence &sent,
                     NodeVisitor &x,
                     lem::PtrCollect<SynSubst>& subst,
                     FoundSynonymsStat & stat,
                     int max_subst,
                     bool ignore_wordform_errors,
                     SynonymizerDebugger * trace
                    );

  public:
   PhraseGenerator_RU( Solarix::Faind_Engine *Gren );

   virtual void ApplyFilter( const int *ies, int n, bool use_thesaurus );
   virtual void ApplyFilter2Grams( const int *ies, int npairs );
   virtual void GeneratePhrase( int phrase_type, int DebugFlags, lem::UFString &result );
   virtual bool Paraphrase(
                           int PhraseTypeFlags,
                           int SyntaxAnalysisFlags,
                           int NGramFlags,
                           int ThesaurusFlags,  
                           int DebugFlags,  
                           int ResultsFormat,
                           lem::UFString &result,
                           int max_subst,
                           FG_Stats *stats,
                           int max_elapsed_msec,
                           SynonymizerDebugger * trace
                          );
 };


 class PhraseGenerator_EN : public PhraseGenerator
 {
  private:
   lem::Ptr<Picker_EN> base_picker;
   lem::Ptr<Picker_EN> picker;

   virtual int GetTargetLanguage(void) { return ENGLISH_LANGUAGE; }

   virtual void CorrectTokenizationEffects( lem::UFString &str ) const;

   void FindSynonyms(
                     int PhraseTypeFlags,
                     int SyntaxAnalysisFlags,
                     int NGramFlags,
                     int ThesaurusFlags,  
                     int DebugFlags,  
                     int ResultsFormat,
                     const Solarix::Sentence &sent,
                     NodeVisitor &x,
                     lem::PtrCollect<SynSubst>& subst,
                     int max_subst,
                     bool ignore_wordform_errors
                    );

   void GetAtomicSubject(
                         GeneratorContext &context,
                         int phrase_type,
                         lem::UFString &result,
                         int Number,
                         bool AllowCompoundAdj
                        );

   void GetCompoundSubject(
                           GeneratorContext &context,
                           int phrase_type,
                           lem::UFString &result,
                           int Number
                          );

   void GetAtomicAttributeForNoun(
                                  GeneratorContext &context,
                                  int phrase_type,
                                  lem::UFString &result
                                 );

   void GetCompoundAttributeForNoun(
                                    GeneratorContext &context,
                                    int phrase_type,
                                    lem::UFString &result
                                   );

   void GetAtomicPredicate(
                           GeneratorContext &context,
                           int phrase_type,
                           lem::UFString &result,
                           int Number,
                           int Tense,
                           int Person
                          );

   lem::UFString& GeneratePhrase0( GeneratorContext& context, int phrase_type, lem::UFString &result );
   lem::UFString& GeneratePhrase1( GeneratorContext& context, int phrase_type, lem::UFString &result );

  public:
   PhraseGenerator_EN( Solarix::Faind_Engine *Gren );

   virtual void ApplyFilter( const int *ies, int n, bool use_thesaurus );
   virtual void ApplyFilter2Grams( const int *ies, int npairs );

   virtual void GeneratePhrase( int phrase_type, int DebugFlags, lem::UFString &result );
   virtual bool Paraphrase(
                           int PhraseTypeFlags,
                           int SyntaxAnalysisFlags,
                           int NGramFlags,
                           int ThesaurusFlags,  
                           int DebugFlags,  
                           int ResultsFormat,
                           lem::UFString &result,
                           int max_subst,
                           FG_Stats *stats,
                           int max_elapsed_msec,
                           SynonymizerDebugger * trace
                          );
 };

 #endif

#endif
