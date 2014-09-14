#ifndef SOL_OPTIONS__H
#define SOL_OPTIONS__H
#pragma once

 namespace Solarix
 {
  class Compile_Options
  {
   public:
    bool decompile_rules; // ѕоказывать декомпилированный код в CPP-файле
                          // дл€ правил.

    bool explain_not_compiled; // ќбъ€сн€ть в CPP-файле причину отказа
                               // трансл€ции конкретного правила

    bool explain_correlation; // ƒетальные комментарии по трансл€ции точек
                              // коррелировани€

    bool explain_context;     // ƒетальные комментарии по трансл€ции точек
                              // проверки в эталонном контексте

    bool explain_predicates; // ƒетальные комментарии по проверке предикатов

    bool general_explanations; // ќбщие комментарии в генернируемые файлы

    Compile_Options(void)
    {
     decompile_rules      = false;
     explain_not_compiled = false;
     explain_correlation  = false;
     explain_context      = false;
     explain_predicates   = false;
     general_explanations = false;
    }

    
    inline void TurnOn(void)
    {
     decompile_rules      = true;
     explain_not_compiled = true;
     explain_correlation  = true;
     explain_predicates   = true;
     explain_context      = true;
     general_explanations = true;
    }
  };
 };

#endif
