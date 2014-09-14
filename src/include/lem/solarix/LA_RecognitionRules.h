#if !defined LA_RECOGNITION_RULES__H
 #define LA_RECOGNITION_RULES__H

 #include <lem/ptr_container.h>
 #include <lem/solarix/WordCoord.h>
 #include <lem/solarix/LA_RecognitionRule.h>
 #include <lem/solarix/LA_ProjectInfo.h>
 #include <lem/solarix/ProjScore.h>

 namespace Solarix
 {
  class LA_RecognitionTrace;
  class LexiconStorage;

  // Набор правил распознавания грамматических атрибутов
  // для единственного языка. Использование - см. LA_Recognizer
  struct LA_RecognitionRules : lem::NonCopyable
  {
   int id_language;
   LexiconStorage *storage;

   lem::MCollect<LA_RecognitionRule*> rules; // общий список правил

   lem::MCollect<const LA_RecognitionRule*> rx_rules; // правила, проверка которых связана с 
                                                      // использованием регулярного выражения

   typedef std::multimap<LA_RecognitionRule::HashType,const LA_RecognitionRule*> RULES;
   RULES prefix_rules, affix_rules, syllab_prefix_rules, syllab_affix_rules;

   void AddResult(
                  const Solarix::Word_Coord &wc,
                  lem::Real1 val,
                  Solarix::LA_ProjectInfo *inf,
                  lem::MCollect<Solarix::Word_Coord> &found_list,
                  lem::MCollect<ProjScore> &val_list,
                  lem::PtrCollect<Solarix::LA_ProjectInfo> &inf_list
                 ) const;


   LA_RecognitionRules( int _id_language, LexiconStorage *_storage );
   ~LA_RecognitionRules(void);

   void Add( LA_RecognitionRule * rule );

   bool Apply(
              const lem::UCString &word,
              lem::Real1 word_rel,
              lem::MCollect<Solarix::Word_Coord> &found_list,
              lem::MCollect<ProjScore> &val_list,
              lem::PtrCollect<Solarix::LA_ProjectInfo> &inf_list,
              LA_RecognitionTrace *trace
             ) const;

   bool ApplyForSyllabs(
                        const lem::UCString &word,
                        lem::Real1 word_rel,
                        const lem::MCollect<lem::UCString> &syllabs,
                        lem::MCollect<Solarix::Word_Coord> &found_list,
                        lem::MCollect<ProjScore> &val_list,
                        lem::PtrCollect<Solarix::LA_ProjectInfo> &inf_list,
                        LA_RecognitionTrace *trace
                       ) const;
  };
 }

#endif
