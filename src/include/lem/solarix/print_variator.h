#pragma once

#ifndef SOL_PRINT_VARIATOR__H
 #define SOL_PRINT_VARIATOR__H


 namespace lem
 {
  class OFormatter;
 } 

 namespace Solarix
 {
  class Res_Pack;
  class Dictionary;
  class Variator;

  extern void print_morphology(
                               const lem::UFString & str,
                               const Solarix::Res_Pack &fblo,
                               const Solarix::Dictionary &dict,
                               lem::OFormatter &out_file,
                               bool html
                              );

  extern void print_syntax_tree(
                                const lem::UFString & str,
                                const Solarix::Res_Pack & pack,
                                const Solarix::Dictionary & dict,
                                lem::OFormatter & out_file,
                                bool html,
                                bool detailed=false
                               );

  extern lem::UFString VarToStr(
                                const Solarix::Dictionary & dict,
                                const Solarix::Variator & var
                               );
 }

#endif
