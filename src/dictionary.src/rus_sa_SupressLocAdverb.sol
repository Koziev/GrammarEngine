
// заключенные сами шьют куклы и иногда выезжают с представлениями в детский дом неподалеку
#define SupressLocAdverb(v) \
#begin
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { rus_verbs:выезжать{}.наречие:*{ ОБСТ_ВАЛ:МЕСТО } }
  then -10
}
#end


SupressLocAdverb(выезжать)
