#if !defined LA_RECOGNITION_TRACE__H
 #define LA_RECOGNITION_TRACE__H

 #include <lem/noncopyable.h>
 #include <lem/math/fp1.h>


 namespace Solarix
 {
  class LA_RecognitionRule;
  class LA_CropRule;
  class LA_PhoneticRule;
  class SyllabContext;
  class SyllabRule;

  class LA_RecognitionTrace : lem::NonCopyable
  {
   public:
    LA_RecognitionTrace(void) {}
    virtual ~LA_RecognitionTrace(void) {}

    virtual void CropRuleApplied(
                                 const lem::UCString &word_before,
                                 const lem::UCString &word_after,
                                 const LA_CropRule *rule
                                )=0;

    virtual void Matched( const lem::UCString &word, const LA_RecognitionRule *rule )=0;
    virtual void MatchedSyllable( const lem::UCString &word, const lem::UCString &syllable, const LA_RecognitionRule *rule )=0;
    virtual void PhoneticRuleProduction( const lem::UCString &source, const lem::UCString &result, lem::Real1 val, const LA_PhoneticRule *rule )=0;
    virtual void WordSyllabs( const lem::UCString &word, const lem::MCollect<lem::UCString> &slb_list )=0;

    virtual void SyllabicBreakRuleHit(
                                      const SyllabContext & context,
                                      int cursor_pos,
                                      const SyllabRule & rule
                                     )=0;

    virtual void SyllabicBreakRuleApplied(
                                          const SyllabContext & context,
                                          int cursor_pos,
                                          const SyllabRule & rule
                                         )=0;
  };
 }

#endif
