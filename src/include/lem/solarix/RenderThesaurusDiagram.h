#if !defined RenderThesaurusDiagram__H
 #define RenderThesaurusDiagram__H

 namespace Solarix
 {
  extern void RenderThesaurusDiagram(
                                     Solarix::Dictionary &dict,
                                     const int ientry,
                                     lem::Path &html_file,
                                     lem::PtrCollect<lem::Path> &aux_files
                                    );

  extern void RenderThesaurusDiagram(
                                     Solarix::Dictionary &dict,
                                     const lem::MCollect<int> &ies,
                                     lem::Path &html_file,
                                     lem::PtrCollect<lem::Path> &aux_files
                                    );

 }

#endif

