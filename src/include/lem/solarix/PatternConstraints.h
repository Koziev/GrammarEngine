#if !defined PatternConstraints__H
 #define PatternConstraints__H

 namespace lem
 {
  namespace Iridium
  {
   class Macro_Parser;
  }
 }

 namespace Solarix
 {
  struct SynPatternResult;
  class LexicalAutomat;
  class BackTrace;

  struct PatternConstraintResult
  {
   bool success;
   int score;

   PatternConstraintResult() : success(false), score(0) {}

   void Union( const PatternConstraintResult & x )
   {
    success = success && x.success;
    score += x.score;
   }
  };

  class PatternConstraint
  {
   public:
    typedef enum { UnknownFunc, EqualFunc, NotEqualFunc } ConstraintFunc;
    ConstraintFunc constraint_func;
    lem::UCString from_marker;
    int from_coord_id;
    lem::UCString to_marker;
    int to_coord_id;

   public:
    PatternConstraint(void);

    bool operator!=( const PatternConstraint & x ) const;

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt( 
                 Dictionary &dict,
                 lem::Iridium::Macro_Parser & txtfile,
                 SynPatternCompilation & compilation_context
                );
    #endif    

    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );

    #if defined SOL_CAA
    PatternConstraintResult Check(
                                  const LexicalAutomat & la,
                                  const BackTrace * parent_trace,
                                  const lem::MCollect<int> & PatternSequenceNumber,
                                  const SynPatternResult * cur_result
                                 ) const;
    #endif
  };




  class Dictionary;
  class SynPatternCompilation;
  class PatternConstraints
  {
   private:
    lem::PtrCollect<PatternConstraint> constraints;

   public:
    PatternConstraints(void);
    PatternConstraints( const PatternConstraints &x );

    void operator=( const PatternConstraints &x );

    bool operator!=( const PatternConstraints &x ) const;

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt( 
                 Dictionary &dict,
                 lem::Iridium::Macro_Parser & txtfile,
                 SynPatternCompilation & compilation_context
                );

    #endif    

    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );

    #if defined SOL_CAA
    PatternConstraintResult Check(
                                  const LexicalAutomat & la,
                                  const BackTrace * parent_trace,
                                  const lem::MCollect<int> & PatternSequenceNumber,
                                  const SynPatternResult * cur_result
                                 ) const;
    #endif
  };

 }

#endif
