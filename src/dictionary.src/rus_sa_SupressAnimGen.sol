tree_scorers ОдушОбъектРод

tree_scorer ОдушОбъектРод language=Russian
{
 if context { местоим_сущ:кто{ падеж:род } }
  then 1
}

tree_scorer ОдушОбъектРод language=Russian
{
 if context { существительное:*{ одуш:одуш падеж:род } }
  then 1
}


#define SupressAnimGen(v) \
#begin
// Контрпример:
// Нагоняю двух связистов.
tree_scorer language=Russian
{
 if context { rus_verbs:v{}.{
                             <OBJECT>ОдушОбъектРод.[not]числительное:*{}
                             [not]частица:не{}
                            } }
  then -100
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:v{}.{
                             <OBJECT>ОдушОбъектРод.[not]числительное:*{}
                             [not]частица:не{}
                            } }
  then -100
}
#end

#define SupressAnimGen2(v) \
#begin
tree_scorer language=Russian
{
 if context { инфинитив:v{ вид:соверш }.{
                                         <OBJECT>ОдушОбъектРод.[not]числительное:*{}
                                         [not]частица:не{}
                                        } }
  then -100
}

tree_scorer language=Russian
{
 if context { инфинитив:v{ вид:несоверш }.{
                                           <OBJECT>ОдушОбъектРод.[not]числительное:*{}
                                           [not]частица:не{}
                                          } }
  then -100
}

tree_scorer language=Russian
{
 if context { глагол:v{ вид:соверш }.{
                                      <OBJECT>ОдушОбъектРод.[not]числительное:*{}
                                      [not]частица:не{}
                                     } }
  then -100
}

tree_scorer language=Russian
{
 if context { глагол:v{ вид:несоверш }.{
                                        <OBJECT>ОдушОбъектРод.[not]числительное:*{}
                                        [not]частица:не{}
                                       } }
  then -100
}




tree_scorer ВалентностьГлагола language=Russian
{
 if context { инфинитив:v{ вид:соверш }.{
                                         <OBJECT>ОдушОбъектРод.[not]числительное:*{}
                                         [not]частица:не{}
                                        } }
  then -100
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { инфинитив:v{ вид:несоверш }.{
                                           <OBJECT>ОдушОбъектРод.[not]числительное:*{}
                                           [not]частица:не{}
                                          } }
  then -100
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:v{ вид:соверш }.{
                                      <OBJECT>ОдушОбъектРод.[not]числительное:*{}
                                      [not]частица:не{}
                                     } }
  then -100
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:v{ вид:несоверш }.{
                                        <OBJECT>ОдушОбъектРод.[not]числительное:*{}
                                        [not]частица:не{}
                                       } }
  then -100
}

#end



SupressAnimGen2( хлебануть )
SupressAnimGen2( согреть )
SupressAnimGen( огребать )
SupressAnimGen( огрести )
SupressAnimGen( накоплять )
SupressAnimGen( накопить )
SupressAnimGen( скапливать )
SupressAnimGen( скопить )
SupressAnimGen( срубить )
SupressAnimGen( наборматывать )
SupressAnimGen( набормотать )
SupressAnimGen( навоевывать )
SupressAnimGen( навоевать )
SupressAnimGen( нарывать )
SupressAnimGen( нарыть )
SupressAnimGen( насасывать )
SupressAnimGen( насосать )
SupressAnimGen( наскребывать )
SupressAnimGen( наскрести )
SupressAnimGen( насортировывать )
SupressAnimGen( насортировать )
SupressAnimGen( настирывать )
SupressAnimGen( настирать )
SupressAnimGen( откатывать )
SupressAnimGen( откатить )
SupressAnimGen( подзарабатывать )
SupressAnimGen( подзаработать )
SupressAnimGen( подпечатывать )
SupressAnimGen( подпечатать )
SupressAnimGen( пожевывать )
SupressAnimGen( пожевать )
SupressAnimGen( сбалтывать )
SupressAnimGen( сболтнуть )
SupressAnimGen( валять )
SupressAnimGen( провалять )
SupressAnimGen( допытываться )
SupressAnimGen( достигать )
SupressAnimGen( достичь )
SupressAnimGen( пожертвовать )
SupressAnimGen( заводить )
SupressAnimGen( завести )
SupressAnimGen( позаимствовать )
SupressAnimGen( запросить )
SupressAnimGen( заработать )
SupressAnimGen( поиметь )
SupressAnimGen( навещать )
SupressAnimGen( навестить )
SupressAnimGen( навьючивать )
SupressAnimGen( навьючить )
SupressAnimGen( нагонять )
SupressAnimGen( нагнать )
SupressAnimGen( надраться )
SupressAnimGen( напиться )
SupressAnimGen( напускать )
SupressAnimGen( напустить )
SupressAnimGen( отстегивать )
SupressAnimGen( отстегнуть )
SupressAnimGen( отхлебывать )
SupressAnimGen( отхлебнуть )
SupressAnimGen( плескать )
SupressAnimGen( плескануть )
SupressAnimGen( подливать )
SupressAnimGen( подлить )
SupressAnimGen( попить )
SupressAnimGen( набираться )
SupressAnimGen( набраться )
SupressAnimGen( налить )
SupressAnimGen( ожидать )
SupressAnimGen( опрашивать )
SupressAnimGen( опросить )
SupressAnimGen( позволять )
SupressAnimGen( позволить )
SupressAnimGen( спрашивать )
SupressAnimGen( спускать )
SupressAnimGen( спустить )
SupressAnimGen( стоить )
SupressAnimGen( считать )
SupressAnimGen( придерживаться )
SupressAnimGen( придержаться )
SupressAnimGen( посеять )
SupressAnimGen( вдохнуть )
SupressAnimGen( глотнуть )
SupressAnimGen( доискиваться )
SupressAnimGen( доискаться )
SupressAnimGen( наколоть )
SupressAnimGen( снести )
SupressAnimGen( поддавать )
SupressAnimGen( поддать )
SupressAnimGen( урывать )
SupressAnimGen( лишать )
SupressAnimGen( лишить )
SupressAnimGen( одалживать )
SupressAnimGen( одолжить )
SupressAnimGen( нажираться )
SupressAnimGen( нажраться )
SupressAnimGen( испрашивать )
SupressAnimGen( испросить )
SupressAnimGen( отгребать )
SupressAnimGen( отгрести )
SupressAnimGen( удостаивать )
SupressAnimGen( удостоить )
SupressAnimGen( страждать )
SupressAnimGen( снискивать )
SupressAnimGen( прихлебывать )
SupressAnimGen( прихлебнуть )
SupressAnimGen( удостаиваться )
SupressAnimGen( удостоиться )
SupressAnimGen( придать )
SupressAnimGen( придавать )
SupressAnimGen( осознать )
SupressAnimGen( осознавать )
SupressAnimGen( постесняться )
SupressAnimGen( найти )
SupressAnimGen( искать )
SupressAnimGen( узнать )
SupressAnimGen( знать )
SupressAnimGen( занять )
SupressAnimGen( занимать )
SupressAnimGen( пожелать )
SupressAnimGen( желать )
SupressAnimGen( ждать )
SupressAnimGen( выпить )
SupressAnimGen( выпивать )
SupressAnimGen( недоедать )
SupressAnimGen( недоесть )
SupressAnimGen( окуривать )
SupressAnimGen( окурить )
SupressAnimGen( ссуживать )
SupressAnimGen( насасываться )
SupressAnimGen( насосаться )
SupressAnimGen( отпивать )
SupressAnimGen( отпить )
SupressAnimGen( недобирать )
SupressAnimGen( недобрать )
SupressAnimGen( подбавлять )
SupressAnimGen( подбавить )
SupressAnimGen( согревать )
SupressAnimGen( добирать )
SupressAnimGen( добрать )
SupressAnimGen( напитываться )
SupressAnimGen( напитаться )
SupressAnimGen( нализываться )
SupressAnimGen( нализаться )
SupressAnimGen( преисполнять )
SupressAnimGen( преисполнить )
SupressAnimGen( напастись )
SupressAnimGen( поднабираться )
SupressAnimGen( поднабраться )
SupressAnimGen( нацеживать )
SupressAnimGen( накуриться )
SupressAnimGen( отбавлять )
SupressAnimGen( отбавить )
SupressAnimGen( пригубливать )
SupressAnimGen( сыскивать )
SupressAnimGen( недоливать )
SupressAnimGen( поназанимать )
SupressAnimGen( понакупить )
SupressAnimGen( понахватать )
SupressAnimGen( попотрошить )
SupressAnimGen( изволить )
SupressAnimGen( нагрести )
SupressAnimGen( напропускать )
SupressAnimGen( наскоблить )
SupressAnimGen( погодить )
SupressAnimGen( наделать )
SupressAnimGen( потерпеть )
SupressAnimGen( испить )
SupressAnimGen( наглотаться )
SupressAnimGen( надавать )
SupressAnimGen( наломать )
SupressAnimGen( наподдать )
SupressAnimGen( натворить )
SupressAnimGen( обождать )
SupressAnimGen( плеснуть )
SupressAnimGen( поискать )
SupressAnimGen( понюхать )
SupressAnimGen( продержаться )
SupressAnimGen( сыскать )
SupressAnimGen( накосить )
SupressAnimGen( насчитать )
SupressAnimGen( покушать )
SupressAnimGen( соснуть )
SupressAnimGen( довесить )
SupressAnimGen( прождать )
SupressAnimGen( свалять )
SupressAnimGen( дербалызнуть )
SupressAnimGen( дербануть )
SupressAnimGen( дерябнуть )
SupressAnimGen( клюкнуть )
SupressAnimGen( напугаться )
SupressAnimGen( налакаться )
SupressAnimGen( наклюкаться )
SupressAnimGen( пообождать )
SupressAnimGen( пождать )
SupressAnimGen( хватиться )
SupressAnimGen( востребовать )
SupressAnimGen( наболтать )
SupressAnimGen( стребовать )
SupressAnimGen( подвыпить )
SupressAnimGen( навалять )
SupressAnimGen( извалять )
SupressAnimGen( призанять )
SupressAnimGen( понаписать )
SupressAnimGen( перепить )
SupressAnimGen( нахлебаться )
SupressAnimGen( натерпеться )
SupressAnimGen( нанюхаться )
SupressAnimGen( заждаться )
SupressAnimGen( подзанять )
SupressAnimGen( поспрашать )
SupressAnimGen( надыбать )
SupressAnimGen( выкушать )
SupressAnimGen( застесняться )
SupressAnimGen( нахвататься )
SupressAnimGen( навидаться )
SupressAnimGen( назанимать )
SupressAnimGen( понастроить )
SupressAnimGen( понахвататься )
SupressAnimGen( перевидать )
SupressAnimGen( повалять )
SupressAnimGen( полакать )
SupressAnimGen( начеканить )
SupressAnimGen( позанимать )
SupressAnimGen( наплескать )
SupressAnimGen( перелопать )
SupressAnimGen( навялить )
SupressAnimGen( натрясти )
SupressAnimGen( налущить )
SupressAnimGen( приискать )

