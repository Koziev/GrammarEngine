#if !defined WordSplitResults__H
 #define WordSplitResults__H

namespace Solarix
{
 // Результаты применения правил замены цепочки токенов.
 struct WordSplitResults : lem::NonCopyable
 {
  bool greedy; // true, если исходное слово нужно забыть, false если исходное слово тоже является вариантом токенизации.
  lem::PtrCollect< lem::MCollect<lem::UCString> > words; // варианты цепочек слов, которые надо подставить вместо исходного.

  WordSplitResults() : greedy(false) {}
 };
}

#endif
