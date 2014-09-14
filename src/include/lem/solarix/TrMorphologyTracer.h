#ifndef MORPHOLOGY_TRACER__H
#define MORPHOLOGY_TRACER__H
#pragma once

 // CD->06.03.2011
 // LC->28.06.2012

 #include <lem/noncopyable.h>
 #include <lem/containers.h>
 #include <lem/stack.h>
 #include <lem/ufstring.h>

 namespace Solarix
 {
  #if defined SOL_CAA
  class Word_Form;
  class SynPatternPoint;
  class TrMorphologyTracer;
  class Dictionary;

  class TrMorphologyTracerTx : lem::NonCopyable
  {
   private:
    int tx;
    TrMorphologyTracer *log;
 
    TrMorphologyTracerTx( TrMorphologyTracer *_log, int _tx );

    friend class TrMorphologyTracer;

   public:
    ~TrMorphologyTracerTx(void);
    void Rollback(void);
    void Commit(void);
  };

  class TrMorphologyTracer
  {
   private:
    lem::MCollect<const void*> wordform_src_ptr;
    lem::MCollect<Word_Form*> wordforms;
    lem::Collect<lem::UFString> str_wordforms;
    lem::MCollect<const SynPatternPoint*> points;
    lem::Collect<lem::UFString> str_points;
    lem::Collect<lem::UFString> tree_names;

    lem::Stack<lem::UFString> current_tree;
    lem::UFString GetCurrentTree(void);

   public:
    TrMorphologyTracer(void);
    ~TrMorphologyTracer(void);

    void Clear(void);

    TrMorphologyTracerTx* BeginTx(void);
    void RollbackTx( const TrMorphologyTracerTx * tx );

    void AddMatchingPoint(
                          const Solarix::Word_Form * head_wordform,
                          const lem::UFString & wordform_str,
                          const SynPatternPoint * point,
                          const lem::UFString & point_str
                         );

    void PushCurrentTree( const lem::UCString &tree_name );
    void PopCurrentTree(void);
    void PrintMatchingPoints( lem::OFormatter &to ) const;
  };
  #endif
 }

#endif
