#ifndef SE_SEARCH_OPTIONS__H
#define SE_SEARCH_OPTIONS__H
#pragma once

 #include <lem/zeroed.h>
 #include <lem/solarix/tree_link.h>
 #include <lem/solarix/se_morphology.h>

 namespace Solarix
 {
  class Dictionary;

  namespace Search_Engine
  {

   // ********************************************************
   // General search and match options. They describe how to
   // compare the pattern and text.
   // ќбщие флаги поиска - описывают, как сравниваетс€ паттерн
   // и текст.
   // ********************************************************
   struct Search_Options
   {
    /// “ипы запроса, соответствуют командам -regex, -sample, -logic, -multiword
    enum Query_Type { REGEX, SAMPLE, MULTIWORD };
    Query_Type query_type;

    /// separated lexems are regular expressions
    /// отдельные слова €вл€ютс€ регул€рными выражени€ми (команда -rx)
    lem::zbool regex;

    // частный случай регул€рного выражени€ - вместо команд регэкспов
    // примен€ютс€ метасимволы * и ?, которые перед использованием паттерна
    // преобразуютс€ в нормальный регэксп.
    lem::zbool wildcards;

    lem::zbool rx_suffix; // ƒл€ паттернов типа -rx -sample если терм не содержит
                    // метасимволов регекспа, то добавл€ть .+ в конце дл€
                    // имитации работы грамматического движка

    lem::zbool case_sensitive; /* Do not ignore case
                            строго следовать регистру букв паттерна */

    lem::zbool soundex;          // нечеткий поиск
    Morphology morphology; // приводить к базовым словоформам или учитывать динамические словоформы
    Syntax syntax;         // выполн€ть синтаксический анализ при фиксации контекста
    lem::zbool strip_accents;    // убирать диактрические символы у букв (акценты)
    lem::zbool try_translit;     // пробовать искать в транслите

    lem::zbool ordered;       // строго придерживатьс€ пор€дка слов паттерна
    int distance;       // рассто€ние между фиксируемыми словами (в лексемах)
    lem::zbool same_sentence; // слова должны быть в пределах одного предложени€
    lem::zbool same_line;     // слова должны находитьс€ в пределах одной строки в файле

    int semnet;         // работа с тезаурусом - макс. кол-во шагов по сети
    std::set<UCString> t_links; // имена допустимых по тезаурусу св€зок
    lem::MCollect< Solarix::Tree_Link > t_ilinks; // индексы этих св€зок по словарю
    lem::zbool l_synonyms, l_grammars, l_translations, l_semantics; // если заданы группы св€зок

    float minbound;     // минимальна€ достоверность фиксации
    int n_max_miss;     // максимальное отличие лексем при нечетком сравнении слов
    lem::zbool rooting;       // разрешать приведение к корню дл€ нечеткого сравнени€

    lem::zbool once_per_file; // искать паттерн один раз в файле
    lem::zbool allow_partial; // разрешать частичное сопоставление фраз (не все слова)

    lem::zbool target_content; // искать в текстовом контенте документа
    lem::zbool target_filename; // искать в имени файла

    void Init( const Search_Options &x );
 
    Search_Options(void);
    Search_Options( const Search_Options &x );

    void operator=( const Search_Options &x );

    void Clear(void);

    void AllowSynonyms(void);
    void AllowGrammar(void);
    void AllowSemantics(void);
    void AllowTranslations(void);

    void UnrollAllowedLinks( const Solarix::Dictionary *sol_id );

    bool SpecifiedLinkGroupsOnly(void) const;
   };

  } // namespace Search_Engine
 } // namespace Solarix

#endif
