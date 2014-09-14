#ifndef SYNTAX_ANALYZER_TIMEOUT__H
#define SYNTAX_ANALYZER_TIMEOUT__H
#pragma once

 namespace Solarix
 {
  // Параметры, ограничивающие пределное потребление ресурсов
  // при выполнении грамматического анализа.
  struct SyntaxAnalyzerTimeout
  {
   enum { MAX_VARIATORS=4096 }; // значение максимального числа вариаторов в ходе
                                // грамматических итераций по умолчанию

   int max_tokenization_paths; // макс. число просматриваемых полных путей в графе токенизации
   int max_variators;
   int max_elapsed_millisecs;
   int max_alt; // макс. число параллельных путей разбора в нисходящем парсере
   int max_bottomup_trees; // макс. число просматриваемых вариантов построения графа в восходящем парсере

   SyntaxAnalyzerTimeout(void) : 
    max_variators(SyntaxAnalyzerTimeout::MAX_VARIATORS), max_elapsed_millisecs(3600000), max_alt(0), max_tokenization_paths(1000), max_bottomup_trees(1000) {}
  };

 }

#endif
