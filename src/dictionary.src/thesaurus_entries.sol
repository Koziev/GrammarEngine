automat sg
{
 class ThesaurusEntries
 {
  language ThesaurusLanguage
 }

 // Для образования гипернимов 'ИМЯ ЧЕЛОВЕКА'
 entry HypernymHumanName : ThesaurusEntries { }

 // Для образования гипернимов "имеет длительность", e.g. ЧАС, ЛЕКЦИЯ
 entry HasDuration : ThesaurusEntries { }

}
