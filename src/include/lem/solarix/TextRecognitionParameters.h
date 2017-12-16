#if !defined TextRecognitionParameters__H
#define TextRecognitionParameters__H

#include <lem/containers.h>
#include <lem/solarix/syntax_analyzer_timeout.h>

namespace Solarix
{

 struct TextRecognitionParameters
 {
  lem::MCollect<int> language_ids; // список языков, первый в списке - основной.
  bool Pretokenized; // предложение уже разбито на слова специальным символом
  bool RecognizeWordforms; // по умолчанию true - выполнять морфологическое распознавание лексем
  bool AllowPrimaryFuzzyWordRecog; // разрешено нечеткое распознавание слов, которые не найдены в лексиконе.
  bool AllowFuzzyRecogMixin; // Даже для словарных токенов делаем нечеткий поиск и добавляем менее достоверные проекции к основной.
  bool AllowDynform; // пробовать отсекать приставки и продуктивные суффиксы при нечетком распознавании
  bool CompleteAnalysisOnly; // Допускается только анализ всего предложения, а не фрагментов.
  bool UseTokenReconstruction; // Восстанавливать пропущенные токены и исправлять формы слов

  // минимальное (обычно в отрицательной области) значение оценки для применения действия, включая нечеткое распознавание.
  int min_score_bound; 

  // максимальная длина применяемых фильтров и, следовательно, перебираемых контекстов.
  // Если поставить это значение в 0, то фильтры вообще не будут использованы.
  // Чем больше значение, тем тщательнее будет префильтрация (в пределах длины имеющихся префидьтров), то
  // тем тяжелее будет перебор.
  //int max_filter_len;

  //bool ApplyCollocFilters; // применять ли финальные фильтры словосочетаний

  int LookAheadTokens; // на сколько токенов вправо может заглядывать алгоритм применения префильтров.

  bool UseSparsePatterns; // неполный анализ, начинающийся с фиксации ключевых элементов
  bool SkipInnerTokens; // если разрешено пропускать слова внутри паттернов
  bool SkipOuterToken; // если разрешено пропускать слова перед или после паттернов
  int MaxSkipToken; // сколько токенов максимум можно пропускать при неполном анализе
  bool UseTopDownThenSparse; // сложная схема работы - сначала пробуем top down анализ, если неудача - то пробуем приблизительный.

  bool ReorderTree; // сортировать ветки в порядке возрастания позиции слов.
  bool ApplyModel; // применять статистическую модель для снятия морф. неоднозначности

  SyntaxAnalyzerTimeout timeout;

  TextRecognitionParameters();

  int GetLanguageID() const { return language_ids.front(); }
  void SetLanguageID( int id ) { language_ids.clear(); language_ids.push_back(id); }
  bool LanguageUnknown() const { return language_ids.empty() || language_ids.front()==UNKNOWN; }
  bool CanSkipInnerTokens() const { return SkipInnerTokens && !CompleteAnalysisOnly; }
  bool CanSkipOuterTokens() const { return SkipOuterToken && !CompleteAnalysisOnly; }

  // максимальное просматриваемое число правых листьев в графе токенизации.
  int GetMaxRightLeaves() const { return timeout.max_tokenization_paths>0 ? timeout.max_tokenization_paths : lem::int_max; }

  // инициализация параметра MaxSkipToken в зависимости от других установленных параметров.
  void ConfigureSkipToken();
 };

}

#endif
