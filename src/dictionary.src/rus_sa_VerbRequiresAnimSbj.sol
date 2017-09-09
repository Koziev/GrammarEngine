
wordentry_set НеодушКакОдушСущ=
{
 существительное:европарламент{},
 существительное:парламент{},
 существительное:комиссия{},
 существительное:комитет{},
 существительное:совет{},
 существительное:создание{},
 существительное:стая{},
 существительное:стайка{},
 существительное:группа{},
 существительное:бригада{},
 существительное:взвод{},
 существительное:банда{},
 существительное:коллектив{},
 существительное:сборище{},
 существительное:отряд{},
 существительное:стадо{}
}

// Некоторые глаголы употребляются обычно с одушевленным подлежащим.
#define VerbRequiresAnimSbj(v) \
#begin
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:v{}.<SUBJECT>*:*{ одуш:неодуш ~НеодушКакОдушСущ } }
  then -1
}
#end


VerbRequiresAnimSbj(есть)
//VerbRequiresAnimSbj(призвать) // призвал молодёжь ценить и помнить подвиг
//VerbRequiresAnimSbj(призывать)

// todo: заменить на полную выборку
VerbRequiresAnimSbj(кушать)
VerbRequiresAnimSbj(питаться)
VerbRequiresAnimSbj(жрать)
VerbRequiresAnimSbj(пожирать)
VerbRequiresAnimSbj(съедать)
VerbRequiresAnimSbj(родиться)
VerbRequiresAnimSbj(умирать)
VerbRequiresAnimSbj(говорить)
VerbRequiresAnimSbj(сказать)
VerbRequiresAnimSbj(сказануть)
VerbRequiresAnimSbj(болтать)
VerbRequiresAnimSbj(петь)
VerbRequiresAnimSbj(пропеть)
VerbRequiresAnimSbj(напеть)
VerbRequiresAnimSbj(напевать)
VerbRequiresAnimSbj(веселиться)
VerbRequiresAnimSbj(смеяться)
VerbRequiresAnimSbj(хохотать)
