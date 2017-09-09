
// Понижаем достоверность варианта разбора, когда подлежащее стоит справа от инфинитива
// в модальном паттерне:
// учили их делать такие штуки.
// вам позволяли читать газеты?
#define SupressModalInfSbj(v) \
#begin
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:v{}.{
                             инфинитив:*{ 1 переходность:переходный падеж:вин }
                             <SUBJECT>*:*{ 2 } // может, только неодуш?
                            } }
  then -5
}
#end

SupressModalInfSbj(учить)
SupressModalInfSbj(научить)
SupressModalInfSbj(позволять)
SupressModalInfSbj(позволить)
