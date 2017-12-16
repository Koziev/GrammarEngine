// Правила перефразировки.
// Справка: http://www.solarix.ru/for_developers/docs/transformation.shtml

// CD->13.06.2009
// LC->14.02.2013

#include "aa_rules.inc"

#define _им ПАДЕЖ:ИМ
#define _вин ПАДЕЖ:ВИН


automat aa
{

 // Склоняем существительное, падеж и число опционально задаются кортежем.
 // Если есть связанные прилагательные - их тоже просклоняем.
 function tree п_ПросклонятьСущ( tree Сущ, tuple Коорд )
 {
  int i, nleft = link_count( Сущ, "left" );
  
  int noun_number = wordform_get_coord(Сущ,ЧИСЛО);
  int noun_gender = -1;
  if( eq( noun_number, ЧИСЛО:ЕД ) )
   then noun_gender = wordform_get_coord(Сущ,РОД);

  tuple КоордПрил = tuple_concat( tuple_create(), Коорд, ЧИСЛО, noun_number, РОД, noun_gender );

  // Признак одушевленности нужен для правильного склонения прилагательных только в винительном падеже и для мужского рода или множественного числа.
  // одушевленность: http://www.solarix.ru/grammar/anymacy.shtml
  // падеж:          http://www.solarix.ru/grammar/case.shtml
  // число:          http://www.solarix.ru/grammar/number.shtml
  bool clear_anim=true;
  int idx = tuple_find( Коорд, ПАДЕЖ );
  int ncase = tuple_get( Коорд, arith_plus(idx,1) );
  if( eq( ncase, ПАДЕЖ:ВИН ) )
   then if( log_or( eq( noun_number, ЧИСЛО:МН ), eq( noun_gender, РОД:МУЖ ) ) )
    then
     {
	  clear_anim = false;
	 }
   
  for i=0 to arith_minus(nleft,1)
   {
    tree ветка = link_get( Сущ, "left", i );
    if( eq( wordform_class(ветка), ПРИЛАГАТЕЛЬНОЕ ) )
     then
      {
       wordform_set_coord( ветка, КоордПрил );
	   
	   if( clear_anim )
	    then wordform_clear_coord( ветка, ОДУШ );
		
       wordform_refresh(ветка);
      } 
   }
  
  return wordform_refresh( wordform_set_coord( Сущ, Коорд ) );
 }

 
 function tree п_ПодцепСлева1( tree узел, variant слева1 )
 {
  return link_add( узел, "left", -1, слева1 );
 }

 function tree п_ПодцепСлева2( tree узел, variant слева1, variant слева2 )
 {
  return link_add( узел, "left", -1, слева1, слева2 );
 }
 
 function tree п_ПодцепСправа1( tree узел, variant справа1 )
 {
  return link_add( узел, "right", -1, справа1 );
 }
 
 function bool п_ЕстьВетки( variant x )
 {
  if( type_is_tree(x) )
   then return log_or( gt(link_count(x,"left"),0), gt(link_count(x,"right"),0) );
   else
   {
    trees xx = x;
    int i, n = var_count(x);
    for i=0 to arith_minus(n,1)
     {
      if( п_ЕстьВетки( var_get(xx,i) ) )
       then return true;      
     }
     
    return false;  
   }   
 } 

 function tree п_СкопироватьСлои( trees dst, trees src )
 {
  link_copy( dst, src, "left" );
  link_copy( dst, src, "leftmost" );
  link_copy( dst, src, "prefix" );
  link_copy( dst, src, "right" );
  return dst;
 }
 
 function trees п_УплощениеДерева( tree узел )
 {
  trees рез;
  int i;

  if( gt( link_count(узел,"prefix"), 0 ) )
   then 
    {
     for i=0 to arith_minus(link_count(узел,"prefix"),1)
      {
       var_prepend( рез, link_get(узел,"prefix",i) ) 
      }      
    }
  
  if( gt( link_count(узел,"leftmost"), 0 ) )
   then 
    {
     for i=arith_minus(link_count(узел,"leftmost"),1) to 0 step -1
      {
       var_prepend( рез, link_get(узел,"leftmost",i) ) 
      }      
    }
  
  if( gt( link_count(узел,"left"), 0 ) )
   then 
    {
     for i=arith_minus(link_count(узел,"left"),1) to 0 step -1
      {
       var_prepend( рез, link_get(узел,"left", i ) ) 
      }      
    }

  var_add( рез, wordform_root(узел) );
   
  if( gt( link_count(узел,"right"), 0 ) )
   then 
    {
     for i=0 to arith_minus(link_count(узел,"right"),1)
      {
       var_add( рез, link_get(узел,"right",i) ) 
      }      
    }
     
  return рез;     
 } 


 rulegroup ПодцепНареч_Z
 rulegroup ПодцепПрилаг_Z
 rulegroup ПерефразСтруктуры1
 rulegroup ПерефразСтруктуры
 rulegroup п_Уплощение
 rulegroup БуквЗамены

 procedure void paraphrase_ru( trees контекст )
 {
  replace( ПодцепНареч_Z, контекст )
  replace( ПодцепПрилаг_Z, контекст )
  replace( ПерефразСтруктуры1, контекст )
  replace( ПерефразСтруктуры, контекст )
  
  while( п_ЕстьВетки(контекст) )
   {
    transform п_Уплощение(контекст)
   }
  
  transform БуквЗамены(контекст)
 } 



 function variant НайтиВДереве( tree hay, tree needle )
 {
  int ipos1 = wordform_pos(needle);
  int ipos2 = wordform_pos(hay);

  if( eq( ipos1, ipos2 ) )
   then return hay;

  int i, n = link_count(hay,"");
  for i=0 to arith_minus(n,1)
   {
    tree leaf = link_get(hay,"",i);
    variant n2 = НайтиВДереве( leaf, needle );
    if( type_is_tree(n2) )
     then return n2;
   }

  return to_void();
 }

 function variant НайтиВДеревьях( trees ctx, tree node )
 {
  int i, n = var_count(ctx);
  for i=1 to arith_minus(n,2) // терминаторы игнорируем
   {
    tree n = var_get(ctx,i);
    variant found_n = НайтиВДереве( n, node );
    if( type_is_tree(found_n) )
     then return found_n;
   }

  return to_void();
 }

 function bool ЕстьВеткиСЧастьюРечи( tree root, int partofspeech )
 {
  int i, n = link_count(root,"");
  for i=0 to arith_minus(n,1)
   {
    tree leaf = link_get(root,"",i);
    if( eq( wordform_class(leaf), partofspeech ) )
     then return true;
   }

  return false;
 }


 function void MixIn( trees ctx )
 {
  trees graf = syntax_analysis( ctx );

  // ищем прилагательные в исходном предложении.
  int i, n = var_count(ctx);
  for i=1 to arith_minus(n,2)
   {
    tree n = var_getref(ctx,i);
    if( eq(wordform_class(n),ПРИЛАГАТЕЛЬНОЕ) )
     then
     {
      variant n2 = НайтиВДеревьях( graf, n );
      if( type_is_tree(n2) )
       then
        {
         // убедимся, что у этого прилагательного нет уже подсоединенных веток-наречий
         if( log_not( ЕстьВеткиСЧастьюРечи( n2, НАРЕЧИЕ ) ) )
          then
           {
            // прикрепляем слева наречие
            tree to_attach = НАРЕЧИЕ:ОЧЕНЬ{};
            п_ПодцепСлева1( n, to_attach );
//return;
           }
        }
     }
   }

  return;
 }


 procedure void mixin_ru( trees контекст )
 {
  MixIn(контекст);

  while( п_ЕстьВетки(контекст) )
   {
    transform п_Уплощение(контекст)
   }
 } 

 
 // ***************************************************************************************
 // Переносим наречия с корневого уровня, прикрепляем их как ветки к атрибутируемым словам.
 // ***************************************************************************************
 transformation(ПодцепНареч_Z) НаречиеКакАтрибут
 {
  declare adv, x;
  if context { @mark(НАРЕЧИЕ,adv) @mark( @or(ГЛАГОЛ,ДЕЕПРИЧАСТИЕ,ИНФИНИТИВ,ПРИЛАГАТЕЛЬНОЕ),x ) } 
   then context { п_ПодцепСлева1(x,adv) }
 }  

 // ***************************************************************************************
 // Прилагательные переносим в ветки существительных
 // ***************************************************************************************

 transformation(ПодцепПрилаг_Z) ПрилагКакАтрибут2
 {
  declare adj, n;
  if context { @mark(ПРИЛАГАТЕЛЬНОЕ,adj) @mark( СУЩЕСТВИТЕЛЬНОЕ, n ) } 
   then context
   {
    @lambda
    { 
     if( eq(wordform_get_coord(adj,СТЕПЕНЬ),СТЕПЕНЬ:АТРИБ) )
      then
      {
         int n_number = wordform_get_coord(n,ЧИСЛО);
       int n_case = wordform_get_coord(n,ПАДЕЖ);
       
         int a_number = wordform_get_coord(adj,ЧИСЛО);
       int a_case = wordform_get_coord(adj,ПАДЕЖ);
       
       if( log_and(eq(n_number,a_number),eq(n_case,a_case)) )
        then
         {
          int a_gender = -1;
          int n_gender = -1;

          if( eq( a_number, ЧИСЛО:ЕД) )
           then
            {
             // грамматический род согласуем только для единственного числа.
             a_gender = wordform_get_coord(adj,РОД);
             n_gender = wordform_get_coord(n,РОД);
            } 

          if( eq(a_gender,n_gender) )
           then
            {
             // Прилагательное и существительное согласованы, можем строить граф
             return п_ПодцепСлева1( n, adj );
            }
         }         
      }
    
     return tuple_create( adj, n );
    } 
   }
 } 


 transformation(ПодцепПрилаг_Z) ПрилагКакАтрибут3
 {
  declare adj1, adj2, n;
  if context { @mark(ПРИЛАГАТЕЛЬНОЕ,adj1) @mark(ПРИЛАГАТЕЛЬНОЕ,adj2) @mark( СУЩЕСТВИТЕЛЬНОЕ, n ) } 
   then context
   {
    @lambda
    { 
     if( log_and( eq(wordform_get_coord(adj1,СТЕПЕНЬ),СТЕПЕНЬ:АТРИБ), eq(wordform_get_coord(adj2,СТЕПЕНЬ),СТЕПЕНЬ:АТРИБ) ) )
      then
      {
       int n_number = wordform_get_coord(n,ЧИСЛО);
       int n_case = wordform_get_coord(n,ПАДЕЖ);
       
       int a1_number = wordform_get_coord(adj1,ЧИСЛО);
       int a1_case = wordform_get_coord(adj1,ПАДЕЖ);

       int a2_number = wordform_get_coord(adj2,ЧИСЛО);
       int a2_case = wordform_get_coord(adj2,ПАДЕЖ);
       
       if( log_and( log_and(eq(n_number,a1_number),eq(n_case,a1_case)), log_and(eq(n_number,a2_number),eq(n_case,a2_case)) ) )
        then
         {
          int a1_gender = -1;
          int n_gender = -1;
          int a2_gender = -1;

          if( eq( a1_number, ЧИСЛО:ЕД) )
           then
            {
             // грамматический род согласуем только для единственного числа.
             a1_gender = wordform_get_coord(adj1,РОД);
             a2_gender = wordform_get_coord(adj2,РОД);
             n_gender = wordform_get_coord(n,РОД);
            } 

          if( log_and( eq(a1_gender,n_gender), eq(a2_gender,n_gender) ) )
           then
            {
             // Прилагательное и существительное согласованы, можем строить граф
             return п_ПодцепСлева2( n, adj1, adj2 );
            }
         }         
      }
    
     return tuple_create( adj1, adj2, n );
    } 
   }
 } 
 
 
 // *********************************************************************
 // Возвращаем слова из синтаксического дерева на корневой уровень. 
 // *********************************************************************
 transformation(п_Уплощение) Уплощ1
 {
  if context { п_ЕстьВетки(_) }
   then context { п_УплощениеДерева( ctx_root(0) ) }
 }

 
 // ######################################################################################
 // Далее идут продукционные правила верхнего уровня - они срабатывают на определенные
 // паттерны в исходном предложении и порождают новое содержимое.
 // ######################################################################################

 
 // **************************************************
 // КАК КОШКА --> ПОДОБНО КОШКЕ
 // **************************************************
 transformation(ПерефразСтруктуры1) Как_Подобно
 {
  declare Сущ;
  if context { 'как' @mark( СУЩЕСТВИТЕЛЬНОЕ:*{ПАДЕЖ:ИМ}, Сущ ) } 
   then context
   {
    'подобно'
    п_ПросклонятьСущ( Сущ, tuple_create( ПАДЕЖ, ПАДЕЖ:ДАТ ) )
   }
 }  


 
 // **************************************************
 // Меняем местами фрагменты А и Б в паттерне
 // Если А, то Б.
 // **************************************************
 transformation(ПерефразСтруктуры) ПерестановкаЕслиТо
 {
  declare Условие, Следствие;
  if context { 'если' @mark(@until( ',' , 'то' ),Условие) ',' 'то' @mark(@until(@or('.','!','?',_КОН)),Следствие) } 
   then
    context { paraphrase_ru(Следствие) ',' 'если' paraphrase_ru(Условие) }
 }  

 // **************************************************
 // Меняем местами фрагменты А и Б в паттерне
 // Так как А, то Б.
 // **************************************************
 transformation(ПерефразСтруктуры) ПерестановкаТакКак
 {
  declare Условие, Следствие;
  if context { 'так как' @mark(@until( ',' , 'то' ),Условие) ',' 'то' @mark(@until(@or('.','!','?',_КОН)),Следствие) } 
   then
    context { paraphrase_ru(Следствие) ',' 'потому что' paraphrase_ru(Условие) }
 }  

 // *************************************************************
 // Спрягаем глагол гл по координатам, которые берем в образце.
 // *************************************************************
 function tree ПроспрягатьПоОбразцу( tree гл, tree образец )
 {
  wordform_clear_coord( гл, НАКЛОНЕНИЕ, ВРЕМЯ, ЧИСЛО, ЛИЦО, РОД );
 
  tree гл2 = wordform_set_coord( гл,
   ВРЕМЯ, wordform_get_coord(образец,ВРЕМЯ),
   НАКЛОНЕНИЕ, wordform_get_coord(образец,НАКЛОНЕНИЕ),
   ЧИСЛО, wordform_get_coord(образец,ЧИСЛО),
   ЛИЦО, wordform_get_coord(образец,ЛИЦО),
   РОД, wordform_get_coord(образец,РОД)
     );
     
  return wordform_refresh( гл2 );
 } 
 
 
 // **********************************************************************
 // Склоняем существительное сущ по координатам, которые берем в образце.
 // **********************************************************************
 function tree ПросклонятьСущПоОбразцу( tree сущ, tree образец )
 {
  wordform_clear_coord( ПАДЕЖ, ЧИСЛО );
  
  return wordform_refresh( wordform_set_coord( сущ,
   ПАДЕЖ, wordform_get_coord(образец,ПАДЕЖ),
   ЧИСЛО, wordform_get_coord(образец,ЧИСЛО)
     ) );
 } 


 // ************************************************************************************** 
 // Кошка такая хитрая, что ... --> Кошка столь хитра, что ...
 // ************************************************************************************** 
 transformation(ПерефразСтруктуры) ТакойЧто
 {
  declare Прил;
  if context { ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ{} @mark(ПРИЛАГАТЕЛЬНОЕ:*{},Прил) ',' 'что' } 
   then
    context
    {
	 @lambda
	 {
	  // попробуем получить краткую форму прилагательного.
	  tree short = copy(Прил);
	  wordform_set_coord( short, КРАТКИЙ, 1 );
	  wordform_clear_coord( short, ПАДЕЖ );
	  wordform_refresh(short);
	  
	  // если нашли...
	  if( eq( wordform_get_coord(short,КРАТКИЙ), 1 ) )
	   then
	    {
		 // ... то возвращаем СТОЛЬ ХИТРА, ЧТО
		 return tuple_create( НАРЕЧИЕ:СТОЛЬ{}, short, ctx_root(2), ctx_root(3) ); 
		}
       else
        {
		 // у прилагательного нет краткой формы, возвращаем исходный набор словоформ контекста.
		 return tuple_create( ctx_root(0), ctx_root(1), ctx_root(2), ctx_root(3) );
        }		
	 }
    }    
 }

 function tree УдалитьВеткуСлово( tree x, string dimension, string word )
 {
  int i, n = link_count(x,dimension);
  for i=0 to arith_minus(n,1)
   {
    string s = wordform_lexem(link_get( x, dimension, i ));
    if( eqi( s, word ) )
     then
      {
       link_remove( x, dimension, i );
       break;
      }
   }
 
  return x;
 }

 
 // ************************************************************************************** 
 // Кошка более хитрая ... -> Кошка хитрее
 // ************************************************************************************** 
 transformation(ПерефразСтруктуры) Более
 {
  declare Прил;
  if context { @tree( @mark(ПРИЛАГАТЕЛЬНОЕ:*{ СТЕПЕНЬ:АТРИБ },Прил), [left]НАРЕЧИЕ:БОЛЕЕ{} ) }
   then
    context
    {
	 @lambda
	 {
	  // попробуем получить сравнительную форму прилагательного.
	  tree compar = copy(Прил);
	  wordform_set_coord( compar, СТЕПЕНЬ, СТЕПЕНЬ:СРАВН );
	  wordform_clear_coord( compar, ПАДЕЖ, ЧИСЛО, РОД );
	  wordform_refresh(compar);
	  
	  // если нашли...
	  if( eq( wordform_get_coord(compar,СТЕПЕНЬ), СТЕПЕНЬ:СРАВН ) )
	   then
	    {
		 // ... то возвращаем ХИТРЕЕ
         // не забудем убрать ветку с БОЛЕЕ
		 return УдалитьВеткуСлово(compar,'left','более');
		}
       else
        {
		 // у прилагательного нет сравнительной формы, возвращаем исходный набор словоформ контекста.
		 return ctx_root(0);
        }		
	 }
    }    
 }
 
 
 // ************************************************************************************** 
 // Кошка самая хитрая -> Кошка хитрейшая
 // ************************************************************************************** 
 transformation(ПерефразСтруктуры) Самый
 {
  declare Прил;
  if context { ПРИЛАГАТЕЛЬНОЕ:САМЫЙ{} @mark(ПРИЛАГАТЕЛЬНОЕ:*{ СТЕПЕНЬ:АТРИБ },Прил) }
   then
    context
    {
	 @lambda
	 {
	  // попробуем получить превосходную форму прилагательного.
	  tree supr = copy(Прил);
	  wordform_set_coord( supr, СТЕПЕНЬ, СТЕПЕНЬ:ПРЕВОСХ );
	  wordform_refresh(supr);
	  
	  // если нашли...
	  if( eq( wordform_get_coord(supr,СТЕПЕНЬ), СТЕПЕНЬ:ПРЕВОСХ ) )
	   then
	    {
		 // ... то возвращаем ХИТРЕЙШИЙ
		 return supr; 
		}
       else
        {
		 // у прилагательного нет превосходной формы, возвращаем исходный набор словоформ контекста.
		 return tuple_create( ctx_root(0), ctx_root(1) );
        }		
	 }
    }    
 }
 
 
 
 
 // ************************************************************************************** 
 // Ночью каждая кошка уподобляется зверю. --> Ночью каждая кошка становится как зверь.
 // ************************************************************************************** 
 transformation(ПерефразСтруктуры) Уподобляться
 {
  declare Гл,Образец;
  if context { @mark(ГЛАГОЛ:УПОДОБЛЯТЬСЯ{},Гл) @mark(СУЩЕСТВИТЕЛЬНОЕ:*{ПАДЕЖ:ДАТ},Образец) } 
   then
    context
    {
     п_СкопироватьСлои( ПроспрягатьПоОбразцу( ГЛАГОЛ:СТАНОВИТЬСЯ{}, Гл ), Гл )
     'как'      
     п_ПросклонятьСущ( Образец, tuple_create(ПАДЕЖ,ПАДЕЖ:ИМ) )
    }    
 }  
 
 
 // **************************************************************************************
 // Посетить деревню --> Побывать в деревне.
 // ************************************************************************************** 
 transformation(ПерефразСтруктуры) ПосетитьПобывать1
 {
  declare Гл,Сущ;
  if context { @mark(ИНФИНИТИВ:ПОСЕТИТЬ{},Гл) @mark(СУЩЕСТВИТЕЛЬНОЕ:*{ПАДЕЖ:ВИН},Сущ) }
   then
    context
    {
     п_СкопироватьСлои( ИНФИНИТИВ:ПОБЫВАТЬ{}, Гл )
     ПРЕДЛОГ:В{}
     п_ПросклонятьСущ( Сущ, tuple_create(ПАДЕЖ,ПАДЕЖ:ПРЕДЛ) )
    }
 }  


 transformation(ПерефразСтруктуры) ПосетитьПобывать2
 {
  declare Гл,Сущ;
  if context { @mark(ГЛАГОЛ:ПОСЕТИТЬ{},Гл) @mark(СУЩЕСТВИТЕЛЬНОЕ:*{ПАДЕЖ:ВИН},Сущ) }
   then
    context
    {
     п_СкопироватьСлои( ПроспрягатьПоОбразцу( ГЛАГОЛ:ПОБЫВАТЬ{}, Гл ), Гл )
     ПРЕДЛОГ:В{}
     п_ПросклонятьСущ( Сущ, tuple_create(ПАДЕЖ,ПАДЕЖ:ПРЕДЛ) )
    }
 }  


/* 
 // **************************************************************************************
 // Побывать в деревне. --> Посетить деревню.
 // ************************************************************************************** 
 transformation(ПерефразСтруктуры) ПобыватьПосетить1
 {
  declare Гл,Сущ;
  if context { @mark(ИНФИНИТИВ:ПОБЫВАТЬ{},Гл) ПРЕДЛОГ:В{} @mark(СУЩЕСТВИТЕЛЬНОЕ:*{ПАДЕЖ:ПРЕДЛ},Сущ) } 
   then
    context
    {
     п_СкопироватьСлои( ИНФИНИТИВ:ПОСЕТИТЬ{}, Гл )
     п_ПросклонятьСущ( Сущ, tuple_create(ПАДЕЖ,ПАДЕЖ:ВИН) )
    }    
 }  
 
 transformation(ПерефразСтруктуры) ПобыватьПосетить2
 {
  declare Гл,Сущ;
  if context { @mark(ГЛАГОЛ:ПОБЫВАТЬ{},Гл) ПРЕДЛОГ:В{} @mark(СУЩЕСТВИТЕЛЬНОЕ:*{ПАДЕЖ:ПРЕДЛ},Сущ) } 
   then
    context
    {
     п_СкопироватьСлои( ПроспрягатьПоОбразцу( ГЛАГОЛ:ПОСЕТИТЬ{}, Гл ), Гл )
     п_ПросклонятьСущ( Сущ, tuple_create(ПАДЕЖ,ПАДЕЖ:ВИН) )
    }    
 }  
*/
 
 // ************************************************************************************** 
 // Рядом с деревом -> Недалеко от дерева
 // ************************************************************************************** 
 transformation(ПерефразСтруктуры) Рядом_Недалеко
 {
  declare Сущ;
  if context { ПРЕДЛОГ:рядом с{} @mark(СУЩЕСТВИТЕЛЬНОЕ:*{ПАДЕЖ:ТВОР},Сущ) }
   then
    context
    {
     ПРЕДЛОГ:недалеко от{}
     п_ПросклонятьСущ( Сущ, tuple_create(ПАДЕЖ,ПАДЕЖ:РОД) )
    }    
 }  
 
 
 
 
 // **************************************************************************************
 // С заходом солнца кот уподобился зверю. --> С заходом солнца кот стал как зверь.
 // ************************************************************************************** 
 transformation(ПерефразСтруктуры) Уподобиться
 {
  declare Гл,Образец;
  if context { @mark(ГЛАГОЛ:УПОДОБИТЬСЯ{},Гл) @mark(СУЩЕСТВИТЕЛЬНОЕ:*{ПАДЕЖ:ДАТ},Образец) } 
   then
    context
    {
     п_СкопироватьСлои( ПроспрягатьПоОбразцу( ГЛАГОЛ:СТАТЬ{}, Гл ), Гл )
     'как'
     п_ПросклонятьСущ( Образец, tuple_create(ПАДЕЖ,ПАДЕЖ:ИМ) )
    }    
 }  
 
 // **************************************************
 // Мне стало понятно, что ...
 // Я понял, что ...
 // **************************************************
 transformation(ПерефразСтруктуры) СталоПонятно
 {
  declare Кому;
  if context { @not(СОЮЗ) @mark( @or( СУЩЕСТВИТЕЛЬНОЕ, МЕСТОИМЕНИЕ ), Кому ) 'стало' 'понятно' ',' 'что' } 
   then context
   {
    0
    п_ПросклонятьСущ( Кому, tuple_create( ПАДЕЖ, ПАДЕЖ:ИМ ) )
    ','
    'что'
    }
 }  




 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРОГРАММИРУЕМЫЙ{_им} } then text { , который программируется }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { лег спать } then text { прикорнул }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { темное пиво } then text { портер }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { темное небо } then context { 'свинцовое' 1 }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { темная лошадка } then text { личность с туманными намерениями }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { темная комната } then context { 1 'без' 'освещения' }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { черный кофе } then context { 1 'без' 'молока' }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { черная магия } then text { ведьмовство }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { кот попил } then context { 0 'полакал' }
  }
  
 transformation(БуквЗамены) NoName
 {
  if text { в благодарность за } then text { в качестве благодарности за }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { крепло убеждение } then text { становилось более крепким убеждение }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { тем не менее } then text { все же }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { был не в ладах с самим собой } then text { с трудом находил согласие сам с собой }
 }
  
 transformation(БуквЗамены) NoName
 {
  if text { в не замеченных картографами } then text { в пропущенных составителями карт }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { давно вышедшего из моды } then text { ставшего немодным }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { никому не интересная } then text { полностью обойденная вниманием }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { примерно девяноста восьми } then text { приблизительно сотни }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { все еще очень похожи на } then text { до сих пор напоминают }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { достаточно сказать, что } then text { будет достаточным упомянуть, что }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { до сих пор считаются } then text { по сию пору признаются }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { большинство живущих на ней людей } then text { большая часть её обитателей }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { так как не находили в жизни счастья } then text { потому как их жизнь была несчастливой }
 }
 
 transformation(БуквЗамены) NoName
 {
  if text { рождалось множество решений } then text { возникало большое количество решений }
 }

 transformation(БуквЗамены) NoName
 {
  if text { почти все они } then text { большинство из них }
 }

 transformation(БуквЗамены) NoName
 {
  if text { никаких страданий не испытывали } then text { ничуть не страдали }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ибо счастья не искали } then text { потому что не нуждались в счастье }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ощущение несчастья было постоянным } then text { состояние несчастья было непрерывным }
 }

 transformation(БуквЗамены) NoName
 {
  if text { не скрашивали им жизнь. } then text { их жизнь ничуть не облегчали. }
 }

 transformation(БуквЗамены) NoName
 {
  if text { далеко-далеко } then text { очень далеко }
 }

 transformation(БуквЗамены) NoName
 {
  if text { не паникуй } then text { не поддавайся панике }
 }

 transformation(БуквЗамены) NoName
 {
  if text { предпринял попытку } then text { попытался }
 }

 transformation(БуквЗамены) NoName
 {
  if text { 'во-первых' } then text { прежде всего }
 
 }

 transformation(БуквЗамены) NoName
 {
  if text { Решение все никак  не  находилось, } then text { Решение не удавалось найти, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { кое-кто даже полагал, что } then text { отдельные личности были уверены в том, что }
 
 }

 transformation(БуквЗамены) NoName
 {
  if text { выпил } when { стилизация=груб } then text { выхлебал }
 }

 transformation(БуквЗамены) NoName
 {
  if text { съел } when { стилизация=груб } then text { сожрал }
 }

 transformation(БуквЗамены) NoName
 {
  if text { сильно напился } when { стилизация=груб } then text { налакался }
 }

 transformation(БуквЗамены) NoName
 {
  if text { кот } when { стилизация=груб } then text { котяра }
 }

 transformation(БуквЗамены) NoName
 {
  if text { думал } when { стилизация=груб } then text { шевелил мозгами }
 }

 transformation(БуквЗамены) NoName
 {
  if text { друг } when { стилизация=груб } then text { дружбан }

 }

 transformation(БуквЗамены) NoName
 {
  if text { съел } when { стилизация=изыск } then text { изволил искушать }
 }

 transformation(БуквЗамены) NoName
 {
  if text { выпил } when { стилизация=изыск } then text { соблаговолил испить }
 }

 transformation(БуквЗамены) NoName
 {
  if text { думал } when { стилизация=изыск } then text { размышлял }
 }

 transformation(БуквЗамены) NoName
 {
  if text { друг } when { стилизация=изыск } then text { верный товарищ }
 
 }

 transformation(БуквЗамены) NoName
 {
  if text { за ночь } then text { в течение ночи }
 }

 transformation(БуквЗамены) NoName
 {
  if text { за день } then text { в течение дня }
 }

 transformation(БуквЗамены) NoName
 {
  if text { целый день } then text { весь день }
 }

 transformation(БуквЗамены) NoName
 {
  if text { целую ночь } then text { всю ночь }
 }

 transformation(БуквЗамены) NoName
 {
  if text { целое утро } then text { все утро }
 }

 transformation(БуквЗамены) NoName
 {
  if text { все утро } then text { целое утро }
 }

 transformation(БуквЗамены) NoName
 {
  if text { в течение ночи } then text { за ночь }
 }

 transformation(БуквЗамены) NoName
 {
  if text { в течение дня } then text { за утро }
 }

 transformation(БуквЗамены) NoName
 {
  if text { весь день } then text { целый день }
 }

 transformation(БуквЗамены) NoName
 {
  if text { всю ночь } then text { целую ночь }
 }

 transformation(БуквЗамены) NoName
 {
  if text { с утра до ночи } then text { круглые сутки }
 }

 transformation(БуквЗамены) NoName
 {
  if text { круглые сутки } then text { день и ночь }
 }

 transformation(БуквЗамены) NoName
 {
  if text { день и ночь } then text { с утра до ночи }

 }

 transformation(БуквЗамены) NoName
 {
  if text { пошел ко дну } then text { утонул }
 }

 transformation(БуквЗамены) NoName
 {
  if text { утонул } then text { пошел ко дну }

 }

 transformation(БуквЗамены) NoName
 {
  if text { выщел сухим из воды } then text { избежал последствий }
 }

 transformation(БуквЗамены) NoName
 {
  if text { избежал последствий } then text { вышел сухим из воды }

 }

 transformation(БуквЗамены) NoName
 {
  if text { урановые месторождения } then text { месторождения урана }
 }

 transformation(БуквЗамены) NoName
 {
  if text { месторождения урана } then text { урановые месторождения }
 }

 transformation(БуквЗамены) NoName
 {
  if text { урановое месторождение } then text { месторождение урана }
 }

 transformation(БуквЗамены) NoName
 {
  if text { месторождение урана } then text { урановое месторождение }
 }

 transformation(БуквЗамены) NoName
 {
  if text { газовые месторождения } then text { месторождения газа }
 }

 transformation(БуквЗамены) NoName
 {
  if text { месторождения газа } then text { газовые месторождения }
 }

 transformation(БуквЗамены) NoName
 {
  if text { газовое месторождение } then text { месторождение газа }
 }

 transformation(БуквЗамены) NoName
 {
  if text { месторождение газа } then text { газовое месторождение }
 }

 transformation(БуквЗамены) NoName
 {
  if text { нефтяные месторождения } then text { месторождения нефти }
 }

 transformation(БуквЗамены) NoName
 {
  if text { месторождения нефти } then text { нефтяные месторождения }
 }

 transformation(БуквЗамены) NoName
 {
  if text { нефтяное месторождение } then text { месторождение нефти }
 }

 transformation(БуквЗамены) NoName
 {
  if text { месторождение нефти } then text { нефтяное месторождение }
  
 }

 transformation(БуквЗамены) NoName
 {
  if text { функций по надзору за } then text { функций надзора за }
 }

 transformation(БуквЗамены) NoName
 {
  if text { функций надзора за } then text { функций по надзору за }

 }

 transformation(БуквЗамены) NoName
 {
  if text { о возмещении вреда } then text { о компенсации вреда }
 }

 transformation(БуквЗамены) NoName
 {
  if text { о компенсации вреда } then text { о возмещении вреда }
 
 }

 transformation(БуквЗамены) NoName
 {
  if text { в Госдуму } then text { в Государственную Думу }
 }

 transformation(БуквЗамены) NoName
 {
  if text { в Государственную Думу } then text { в Госдуму }
 
 }

 transformation(БуквЗамены) NoName
 {
  if text { Премьер-министр Испании } then text { испанский премьер-министр }
 }

 transformation(БуквЗамены) NoName
 {
  if text { испанский премьер-министр } then text { Премьер-министр Испании }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Премьер-министр Японии } then text { японский премьер-министр }
 }

 transformation(БуквЗамены) NoName
 {
  if text { японский премьер-министр } then text { Премьер-министр Японии }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Премьер-министр Великобритании } then text { британский премьер-министр }
 }

 transformation(БуквЗамены) NoName
 {
  if text { британский премьер-министр } then text { Премьер-министр Великобритании }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Премьер-министр Франции } then text { французский премьер-министр }
 }

 transformation(БуквЗамены) NoName
 {
  if text { французский премьер-министр } then text { Премьер-министр Франции }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Премьер-министр Италии } then text { итальянский премьер-министр }
 }

 transformation(БуквЗамены) NoName
 {
  if text { итальянский премьер-министр } then text { Премьер-министр Италии }
 
 }

 transformation(БуквЗамены) NoName
 {
  if text { физлиц } then text { физических лиц }
 }

 transformation(БуквЗамены) NoName
 {
  if text { физических лиц } then text { физлиц }
 }

 transformation(БуквЗамены) NoName
 {
  if text { юриц } then text { юридических лиц }
 }

 transformation(БуквЗамены) NoName
 {
  if text { юридических лиц } then text { юрлиц }
 
 }

 transformation(БуквЗамены) NoName
 {
  if text { Налог на доходы } then text { подоходный налог }
 }

 transformation(БуквЗамены) NoName
 {
  if text { подоходный налог } then text { налог на доходы }

 }

 transformation(БуквЗамены) NoName
 {
  if text { министерство финансов } then text { Минфин }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Российской Федерации } then text { РФ }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Соединенных Штатов Америки } then text { США }

 }

 transformation(БуквЗамены) NoName
 {
  if text { подал прошение об отставке } then text { подал в отставку }
 }

 transformation(БуквЗамены) NoName
 {
  if text { подал в отставку } then text { ушел в отставку }

 }

 transformation(БуквЗамены) NoName
 {
  if text { имеет шансы } then text { может }
 }

 transformation(БуквЗамены) NoName
 {
  if text { кабинет министров } then text { Кабмин }
 }

 transformation(БуквЗамены) NoName
 {
  if text { не намерен } then text { не планирует }
 }

 transformation(БуквЗамены) NoName
 {
  if text { российско-китайский товарооборот } then text { товарооборот между Россией и Китаем } 

 }

 transformation(БуквЗамены) NoName
 {
  if text { с поставщиками из Китая . } then text { с китайскими поставщиками . } 
 }

 transformation(БуквЗамены) NoName
 {
  if text { с китайскими поставщиками . } then text { с поставщиками из Китая . } 
 
 }

 transformation(БуквЗамены) NoName
 {
  if text { заулыбался } then text { расплылся в улыбке }
 }

 transformation(БуквЗамены) NoName
 {
  if text { расплылся в улыбке } then text { заулыбался }
 }

 transformation(БуквЗамены) NoName
 {
  if text { дремлет } then text { предается неге }
 }

 transformation(БуквЗамены) NoName
 {
  if text { валяет дурака } then text { бездельничает }

 }

 transformation(БуквЗамены) NoName
 {
  if text { не питаю иллюзий по поводу } then text { не заблуждаюсь по поводу }

 }

 transformation(БуквЗамены) NoName
 {
  if text { вот как-то в четверг } then text { однажды в четверг }
 }

 transformation(БуквЗамены) NoName
 {
  if text { вот как-то в четверг, после дождя, } then text { однажды, после дождичка в четверг, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , спустя } then text { , по прошествии }
 }

 transformation(БуквЗамены) NoName
 {
  if text { почти две тысячи } then text { около двух тысяч }
 }

 transformation(БуквЗамены) NoName
 {
  if text { приколотили гвоздями } then text { гвоздями прибили }
 }

 transformation(БуквЗамены) NoName
 {
  if text { для разнообразия } then text { разнообразия ради }
 }

 transformation(БуквЗамены) NoName
 {
  if text { друг к  другу } then text { друг к дружке }
 }

 transformation(БуквЗамены) NoName
 {
  if text { некая девушка } then text { какая-то девушка }
 }

 transformation(БуквЗамены) NoName
 {
  if text { сидя в одиночестве } then text { одиноко сидя }
 }

 transformation(БуквЗамены) NoName
 {
  if text { На  сей  раз } then text { в этот раз }
 }

 transformation(БуквЗамены) NoName
 {
  if text { непременно получится } then text { непременно удастся }
 }

 transformation(БуквЗамены) NoName
 {
  if text { прочим предметам } then text { другим объектам }
 }

 transformation(БуквЗамены) NoName
 {
  if text { поделиться с кем-нибудь своим открытием, } then text { обсудить свое открытие с кем-нибудь, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { собираюсь вам поведать } then text { хочу вам рассказать }
 }

 transformation(БуквЗамены) NoName
 {
  if text { некоторых ее последствиях } then text { ряде ее последствий }
 }

 transformation(БуквЗамены) NoName
 {
  if text { в  обиходе } then text { в повседневном обиходе }
 }

 transformation(БуквЗамены) NoName
 {
  if text { не публиковавшейся } then text { не опубликованной }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Пожалуй,  это } then text { Можно сказать, что это }
 }

 transformation(БуквЗамены) NoName
 {
  if text { пользуется огромным спросом } then text { пользуется бешеной популярностью }
 }

 transformation(БуквЗамены) NoName
 {
  if text { оставив далеко  позади } then text { далеко обогнав }
 }

 transformation(БуквЗамены) NoName
 {
  if text { гораздо быстрее, чем } then text { намного быстрее, нежели }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Ибо, } then text { Потому как, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { несмотря на  } then text { невзирая на }
 }

 transformation(БуквЗамены) NoName
 {
  if text { крупными  буквами } then text { большими буквами }
 }

 transformation(БуквЗамены) NoName
 {
  if text { чудовищно  нелепом } then text { дурацком }
 }

 transformation(БуквЗамены) NoName
 {
  if text { о  роли,  которую  сыграла } then text { о той функции, которую выполнила }
 }

 transformation(БуквЗамены) NoName
 {
  if text { на  самом  краю } then text { у самого края }
 }

 transformation(БуквЗамены) NoName
 {
  if text { был ничем не примечателен } then text { был очень обыкновенен }
 }

 transformation(БуквЗамены) NoName
 {
  if text { лет  тридцать  назад } then text { три десятка лет тому назад }
 }

 transformation(БуквЗамены) NoName
 {
  if text { кирпичный } then text { кирпичный }
 }

 transformation(БуквЗамены) NoName
 {
  if text { невзрачный } then text { ничем не примечательный }
 }

 transformation(БуквЗамены) NoName
 {
  if text { человеком, полюбившим } then text { человеком, который полюбил }
 }

 transformation(БуквЗамены) NoName
 {
  if text { лишь  потому, что } then text { лишь постольку, поскольку }
 }

 transformation(БуквЗамены) NoName
 {
  if text { жил в нем } then text { обитал в нем }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , с тех пор как } then text { , с того момента как }

 }

 transformation(БуквЗамены) NoName
 {
  if text { яблоком раздора } then text { причиной разногласия }
 }

 transformation(БуквЗамены) NoName
 {
  if text { яблока раздора } then text { причины разногласия }
 }

 transformation(БуквЗамены) NoName
 {
  if text { причиной разногласия } then text { яблоком раздора  }
 }

 transformation(БуквЗамены) NoName
 {
  if text { заморить червячка } then text { поесть }
 }

 transformation(БуквЗамены) NoName
 {
  if text { поесть } then text { заморить червячка }
 }

 transformation(БуквЗамены) NoName
 {
  if text { заморил червячка } then text { перекусил }
 }

 transformation(БуквЗамены) NoName
 {
  if text { заморим червячка } then text { поедим }
 }

 transformation(БуквЗамены) NoName
 {
  if text { было невдомек, что } then text { было неизвестно, что }
 }

 transformation(БуквЗамены) NoName
 {
  if text { принял  решение } then text { решил }
 }

 transformation(БуквЗамены) NoName
 {
  if text { разлепил веки } then text { открыл глаза }
 }

 transformation(БуквЗамены) NoName
 {
  if text { На какой-то миг } then text { на одно мгновение }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , как принято говорить, } then text { , говоря без обиняков , }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , иными словами , } then text { , иначе говоря , }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , ведущей свое начало от } then text { , которая происходила от }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Выражаясь конкретнее, } then text { проще говоря, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { неоднократно битый жизнью } then text { множество раз терпевший поражения }
 }

 transformation(БуквЗамены) NoName
 {
  if text { домашний обед } then text { обед по-домашнему }
 }

 transformation(БуквЗамены) NoName
 {
  if text { собачий корм } then text { корм для собак }
 }

 transformation(БуквЗамены) NoName
 {
  if text { кошачий корм } then text { корм для кошек }
 }

 transformation(БуквЗамены) NoName
 {
  if text { американский президент } then text { президент США }
 }

 transformation(БуквЗамены) NoName
 {
  if text { американский конгресс } then text { Конгресс США }
 }

 transformation(БуквЗамены) NoName
 {
  if text { американский сенат } then text { Сенат США }
 }

 transformation(БуквЗамены) NoName
 {
  if text { немецкий парламент } then text { парламент ФРГ }
 }

 transformation(БуквЗамены) NoName
 {
  if text { британский парламент } then text { парламент Великобритании }
 }

 transformation(БуквЗамены) NoName
 {
  if text { английская королева } then text { королева Англии }
 }

 transformation(БуквЗамены) NoName
 {
  if text { испанский король } then text { король Испании }
 }

 transformation(БуквЗамены) NoName
 {
  if text { британское правительство } then text { правительство Великобритании }
 }

 transformation(БуквЗамены) NoName
 {
  if text { американское правительство } then text { правительство США }
 }

 transformation(БуквЗамены) NoName
 {
  if text { мексиканское правительство } then text { правительство Мексики }
 }

 transformation(БуквЗамены) NoName
 {
  if text { канадское правительство } then text { правительство Канады }
 }

 transformation(БуквЗамены) NoName
 {
  if text { французское правительство } then text { правительство Франции }
 }

 transformation(БуквЗамены) NoName
 {
  if text { американские власти } then text { власти США }
 }

 transformation(БуквЗамены) NoName
 {
  if text { немецкие власти } then text { власти ФРГ }
 }

 transformation(БуквЗамены) NoName
 {
  if text { правительство Великобритании } then text { британское правительство }
 }

 transformation(БуквЗамены) NoName
 {
  if text { правительство США } then text { американское правительство }
 }

 transformation(БуквЗамены) NoName
 {
  if text { правительство ФРГ } then text { немецкое правительство }
 }

 transformation(БуквЗамены) NoName
 {
  if text { правительство Мексики } then text { мексиканское правительство }
 }

 transformation(БуквЗамены) NoName
 {
  if text { правительство РФ } then text { российское правительство }
 }

 transformation(БуквЗамены) NoName
 {
  if text { правительство России } then text { российское правительство }
 }

 transformation(БуквЗамены) NoName
 {
  if text { американское консульство } then text { консульство США }
 }

 transformation(БуквЗамены) NoName
 {
  if text { российское консульство } then text { консульство России }
 }

 transformation(БуквЗамены) NoName
 {
  if text { консульство России } then text { консульство РФ }
 }

 transformation(БуквЗамены) NoName
 {
  if text { консульство США } then text { американское консульство }
 }

 transformation(БуквЗамены) NoName
 {
  if text { никоим образом не } then text { ни в коем случае не }
 }

 transformation(БуквЗамены) NoName
 {
  if text { был великим воином } then text { являлся выдающимся воителем }
 }

 transformation(БуквЗамены) NoName
 {
  if text { работа совсем не клеилась } then text { работа не удавалась }
 }

 transformation(БуквЗамены) NoName
 {
  if text { А заключалась его работа в том, чтобы } then text { В его обязанность входило, чтобы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { до конца дня } then text { до окончания дня }
 }

 transformation(БуквЗамены) NoName
 {
  if text { вы ничего не добьетесь. } then text { у Вас ничего не получится. }
 }

 transformation(БуквЗамены) NoName
 {
  if text { до бесконечности } then text { без конца }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Он многое  бы  дал,  чтобы } then text { Он был готов многим пожерствовать, лишь бы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { строил рожицы } then text { кривлялся }
 }

 transformation(БуквЗамены) NoName
 {
  if text { вам придется смириться } then text { Вы должны примириться }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Это почему же? } then text { С какой это стати? }
 }

 transformation(БуквЗамены) NoName
 {
  if text { замер в  нерешительности } then text { нерешительно замер }
 }

 transformation(БуквЗамены) NoName
 {
  if text { в то  время  как } then text { тогда как }
 }

 transformation(БуквЗамены) NoName
 {
  if text { сломя  голову  мчаться } then text { мчаться с безумной скоростью }
 }

 transformation(БуквЗамены) NoName
 {
  if text { задают себе  вопрос: } then text { спрашивают себя: }
 }

 transformation(БуквЗамены) NoName
 {
  if text { а всего лишь } then text { а только лишь }
 }

 transformation(БуквЗамены) NoName
 {
  if text { В   сложившейся   ситуации } then text { в таких условиях }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ,   безусловно, } then text { , без сомнения, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { проявлял вопиющую некомпетентность } then text { демонстрировал очевидную некомпетентность } 
 }

 transformation(БуквЗамены) NoName
 {
  if text { молил  Бога,  чтобы } then text { молил Всевышнего, дабы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Вы имели возможность } then text { у Вас была возможность }
 }

 transformation(БуквЗамены) NoName
 {
  if text { в надлежащее время } then text { в подобающее время }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Впервые } then text { в первый раз }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Я решил, что } then text { Я пришел к выводу, что }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Сперва он } then text { Он сначала }
 }

 transformation(БуквЗамены) NoName
 {
  if text { содрал с меня } then text { взял с меня }
 }

 transformation(БуквЗамены) NoName
 {
  if text { И только потом } then text { и лишь затем }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ни одной душе } then text { никому }
 }

 transformation(БуквЗамены) NoName
 {
  if text { В конце концов } then text { в итоге }
 }

 transformation(БуквЗамены) NoName
 {
  if text { мне пришлось } then text { я был вынужден }
 }

 transformation(БуквЗамены) NoName
 {
  if text { нельзя назвать особенно красивым } then text { не назовешь очень симпатичным }
 }

 transformation(БуквЗамены) NoName
 {
  if text { мне он нравится } then text { он мне симпатичен }
 }

 transformation(БуквЗамены) NoName
 {
  if text { чтоб духу вашего здесь не было } then text { убирайтесь отсюда }
 }

 transformation(БуквЗамены) NoName
 {
  if text { невнятно забормотал } then text { забубнил неразборчиво }
 }

 transformation(БуквЗамены) NoName
 {
  if text { взял себя в руки } then text { успокоился }
 }

 transformation(БуквЗамены) NoName
 {
  if text { для  вашего  сведения } then text { чтобы Вы знали }
 }

 transformation(БуквЗамены) NoName
 {
  if text {  Вы  представляете, } then text { Вам известно, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { бросился прочь } then text { рванул прочь }
 }

 transformation(БуквЗамены) NoName
 {
  if text { и помыслить о таком не мог } then text { ни в коем случае не мог такое себе представить }
 }

 transformation(БуквЗамены) NoName
 {
  if text { приложил немало усилий, чтобы } then text { добился ценой больших усилий, чтобы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { влиться в человеческое общество } then text { интегрироватся в человеческом обществе }
 }

 transformation(БуквЗамены) NoName
 {
  if text { не без успеха } then text { довольно успешно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { создавала  впечатление, что } then text { порождала иллюзию, что }
 }

 transformation(БуквЗамены) NoName
 {
  if text { К примеру,  } then text { В качестве примера, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { он взял за правило } then text { у него выработалась привычка }
 }

 transformation(БуквЗамены) NoName
 {
  if text { поднимал  взор  к  небу } then text { вглядывался ввысь }
 }

 transformation(БуквЗамены) NoName
 {
  if text { разражался диким  хохотом } then text { начинал безумно гоготать }
 }

 transformation(БуквЗамены) NoName
 {
  if text { до поросячьего визга } then text { до свинского состояния }
 }

 transformation(БуквЗамены) NoName
 {
  if text { какую-нибудь девицу } then text { первую попавшуюся девчонку }
 }

 transformation(БуквЗамены) NoName
 {
  if text { заплетающимся языком } then text { непослушным языком }
 }

 transformation(БуквЗамены) NoName
 {
  if text { не  имеет решающего значения } then text { не является существенным фактором }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ковыляя из последних сил } then text { переставляя конечности из последних сил }
 }

 transformation(БуквЗамены) NoName
 {
  if text { по  ночным  улицам } then text { по улицам, лишенным освещения, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , выспрашивая дорогу  } then text { , интересуясь, как добраться }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Не пора ли вам } then text { Не стоит ли Вам }
 }

 transformation(БуквЗамены) NoName
 {
  if text { отправиться домой } then text { пойти до дома }
 }

 transformation(БуквЗамены) NoName
 {
  if text { На самом же деле, } then text { в действительности же, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { вглядываясь в небо } then text { взирая ввысь }
 }

 transformation(БуквЗамены) NoName
 {
  if text { он  искал } then text { он пытался найти }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Тем  более } then text { тем паче }
 }

 transformation(БуквЗамены) NoName
 {
  if text { умел } then text { был способен }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Он знал, как  } then text { для него не было тайной, как }
 }

 transformation(БуквЗамены) NoName
 {
  if text { в день } then text { за день }
 }

 transformation(БуквЗамены) NoName
 {
  if text { день в день } then text { день в день }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Всем известна } then text { каждый знает }
 }

 transformation(БуквЗамены) NoName
 {
  if text { заключалось в том, чтобы } then text { состояло в том, чтобы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ,  дабы  извлечь } then text { , чтобы получить }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Как дела? } then text { Как жизнь? }
 }

 transformation(БуквЗамены) NoName
 {
  if text { в два счета } then text { на раз-два }
 }

 transformation(БуквЗамены) NoName
 {
  if text { напряженно всматривался в небо } then text { глядел в небеса с напряжением }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Это надо сделать сейчас же } then text { Это должно быть сделано прямо сейчас }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Потому что нам придется } then text { так как мы должны }
 }

 transformation(БуквЗамены) NoName
 {
  if text { помимо всего прочего } then text { не считая остального }
 }

 transformation(БуквЗамены) NoName
 {
  if text { все-таки не прочь } then text { не прочь все-таки }
 }

 transformation(БуквЗамены) NoName
 {
  if text { в голову пришла шальная мысль } then text { явилась безумная идея }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , погруженный  } then text { , который был погружен }
 }

 transformation(БуквЗамены) NoName
 {
  if text { являет  собой  угрозу } then text { является угрозой }
 }

 transformation(БуквЗамены) NoName
 {
  if text { и, следовательно,  } then text { , а значит }
 }

 transformation(БуквЗамены) NoName
 {
  if text { С  удивлением } then text { удивленно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { С  удивлением  и  тревогой } then text { удивленно и с тревогой }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Давайте предположим, что } then text { Представим на миг, будто }
 }

 transformation(БуквЗамены) NoName
 {
  if text { предположим также, что } then text { представим еще, будто }
 }

 transformation(БуквЗамены) NoName
 {
  if text { сваляет дурака } then text { опростоволосится }
 }

 transformation(БуквЗамены) NoName
 {
  if text { На ваш взгляд, } then text { Вы думаете, что }
 }

 transformation(БуквЗамены) NoName
 {
  if text { что победа за ним. } then text { что он одержал верх. }
 }

 transformation(БуквЗамены) NoName
 {
  if text { при том единственном условии, что } then text { если, и только если }
 }

 transformation(БуквЗамены) NoName
 {
  if text { проговорил  вслух } then text { пробормотал }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Некоторым образом да } then text { В некотором смысле правильно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { доказательства, что } then text { подтверждения, что }
 }

 transformation(БуквЗамены) NoName
 {
  if text { всякий раз, когда } then text { всегда, когда }
 }

 transformation(БуквЗамены) NoName
 {
  if text { он чувствовал себя } then text { он ощущал себя }
 }

 transformation(БуквЗамены) NoName
 {
  if text { подсказывает, как } then text { дает совет, как }
 }

 transformation(БуквЗамены) NoName
 {
  if text { отрешенно  уставился  в  окно } then text { уставился в окно с отрешенным взглядом }
 }

 transformation(БуквЗамены) NoName
 {
  if text { перевел взгляд на } then text { обратил взор на }
 }

 transformation(БуквЗамены) NoName
 {
  if text { недурная погодка } then text { неплохая погода }
 }

 transformation(БуквЗамены) NoName
 {
  if text { отвернулся к окну } then text { отвернулся в сторону окна }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , сидевший } then text { , который сидел }
 }

 transformation(БуквЗамены) NoName
 {
  if text { рядом  с } then text { по соседству с }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Не пялься } then text { не надо пялиться }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Сдачи не надо } then text { без сдачи }
 }

 transformation(БуквЗамены) NoName
 {
  if text { тихо удалиться } then text { уйти бесшумно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { черт побери } then text { в конце концов }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Как бы ты поступил,  если  бы } then text { чтобы ты сделал, если бы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ты способен } then text { ты в состоянии }
 }

 transformation(БуквЗамены) NoName
 {
  if text {  В сущности, } then text { по сути, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { сейчас это было } then text { это было сейчас }
 }

 transformation(БуквЗамены) NoName
 {
  if text { не  подозревал  об } then text { не догадывался об }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ,  известный } then text { , который известен }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Вообще-то } then text { На самом деле }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , которая полагает } then text { , полагающая }
 }

 transformation(БуквЗамены) NoName
 {
  if text { на редкость тупая } then text { чертовски дебильная }
 }

 transformation(БуквЗамены) NoName
 {
  if text { в конце концов } then text { в итоге }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , который исколесил } then text { , исколесивший }
 }

 transformation(БуквЗамены) NoName
 {
  if text { вдоль и поперек } then text { во всех направлениях }
 }

 transformation(БуквЗамены) NoName
 {
  if text { при тебе } then text { у тебя }
 }

 transformation(БуквЗамены) NoName
 {
  if text { не было смысла } then text { смысла не было }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , видимо, } then text { , наверное, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Он не понимал,  что } then text { ему было не понятно, что }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Что это такое } then text { Это что такое }
 }

 transformation(БуквЗамены) NoName
 {
  if text { с тех самых пор, как } then text { с того момента, как }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Благодарю за внимание } then text { Спасибо за внимание }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Заметив это, } then text { подметив данный факт, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { подать жалобу } then text { пожаловаться }
 }

 transformation(БуквЗамены) NoName
 {
  if text { рукой подать } then text { совсем недалеко }
 }

 transformation(БуквЗамены) NoName
 {
  if text { это ваше личное дело } then text { это ваши проблемы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Прямо не знаю, } then text { удивляюсь, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Ни капли не жаль } then text { не жалко ни чуточки }
 }

 transformation(БуквЗамены) NoName
 {
  if text { до  отвращения большими } then text { отвратительно огромными }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Из-за указанных недостатков } then text { по причине отмеченных недоработок }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Именно потому } then text { по этой причине }
 }

 transformation(БуквЗамены) NoName
 {
  if text { по случайному совпадению } then text { нечаянно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { не было случайностью } then text { не является простым совпадением }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Именно ради этого дня } then text { Исключительно для такого случая }
 }

 transformation(БуквЗамены) NoName
 {
  if text { знать не знаю } then text { совсем не знаю }
 }

 transformation(БуквЗамены) NoName
 {
  if text { выставить  свою  кандидатуру } then text { стать кандидатом }
 }

 transformation(БуквЗамены) NoName
 {
  if text {  Надо сказать, что } then text { Следует отметить тот факт, что }
 }

 transformation(БуквЗамены) NoName
 {
  if text { отдавали себе отчет в том, что } then text { осознавали, что }
 }

 transformation(БуквЗамены) NoName
 {
  if text { решенным делом } then text { свершившимся фактом }
 }

 transformation(БуквЗамены) NoName
 {
  if text {  Мало  кто  сознает,  что } then text { Немногие понимают, что }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Нет ничего более далекого от истины } then text { Это совершенно не соответствует правде }
 }

 transformation(БуквЗамены) NoName
 {
  if text { По правде говоря, } then text { Говоря честно, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { вообще незачем было } then text { было абсолютно не нужно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { как выглядит со стороны } then text { как смотрится }
 }

 transformation(БуквЗамены) NoName
 {
  if text { казался громадным } then text { выглядел огромным }
 }

 transformation(БуквЗамены) NoName
 {
  if text { в поте лица } then text { не покладая рук }
 }

 transformation(БуквЗамены) NoName
 {
  if text { мы давно с тобой знакомы } then text { мы с тобой давно знакомы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , черт побери, } then text { , в конце концов, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { подходил идеально. } then text { идеально подходил. }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Так продолжалось тысячелетиями, } then text { Это тянулось несколько тысяч лет, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { в одно прекрасное утро } then text { одним прекрасным утром }
 }

 transformation(БуквЗамены) NoName
 {
  if text { недалеко ушли от } then text { ушли недалеко от }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , но не увидел ничего, кроме } then text { , но не разглядел ничего, за исключением }
 }

 transformation(БуквЗамены) NoName
 {
  if text { питают отвращение } then text { испытывают сильную нелюбовь }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Только благодаря знанию } then text { Исключительно по причине понимания }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Мы в безопасности } then text { нам ничего не угрожает }
 }

 transformation(БуквЗамены) NoName
 {
  if text { как мы сюда попали } then text { каким образом мы очутились здесь }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Ему хотелось, чтобы } then text { Он хотел, чтобы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { со  всего  размаха } then text { изо всех сил }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Пошел вон "!" } then text { Убирайся прочь "!" }
 }

 transformation(БуквЗамены) NoName
 {
  if text { На этот раз } then text { В этот раз }
 }

 transformation(БуквЗамены) NoName
 {
  if text { как  правило, } then text { обыкновенно, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Что это? } then text { Это что такое? }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Тут есть  все,  что } then text { здесь имеется все, что }
 }

 transformation(БуквЗамены) NoName
 {
  if text { и  пальцем  не  пошевелят } then text { и палец о палец не ударят }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Ни в коем случае } then text { Ни при каких обстоятельствах }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Что же мне прикажешь делать? } then text { И что я по-твоему должен делать? }
 }

 transformation(БуквЗамены) NoName
 {
  if text { начал охать } then text { заохал }
 }

 transformation(БуквЗамены) NoName
 {
  if text { начал охать и причитать } then text { заохал и запричитал }
 }

 transformation(БуквЗамены) NoName
 {
  if text { начал смеяться } then text { засмеялся }
 }

 transformation(БуквЗамены) NoName
 {
  if text { начал улыбаться } then text { заулыбался }
 }

 transformation(БуквЗамены) NoName
 {
  if text { начал думать } then text { задумался }
 }

 transformation(БуквЗамены) NoName
 {
  if text { начал кричать } then text { закричал }
 }

 transformation(БуквЗамены) NoName
 {
  if text { начал стонать } then text { застонал }
 }

 transformation(БуквЗамены) NoName
 {
  if text { не  слишком } then text { достаточно слабо }
 }

 transformation(БуквЗамены) NoName
 {
  if text { умопомрачительно  красивый } then text { красивый до умопомрачения }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Толпа одобрительно взревела } then text { толпа взревела одобрительно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Как-то  здесь  неуютно } then text { тут не очень-то уютно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { могу понять } then text { понимаю }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Можешь понять } then text { понимаешь }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Если вам посчастливится, } then text { если вам повезет, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { представить  доказательства } then text { дать предоставить подтверждения }
 }

 transformation(БуквЗамены) NoName
 {
  if text { смириться  с мыслью, что } then text { примириться с тем, что }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Ноль эффекта } then text { Никакого эффекта }
 }

 transformation(БуквЗамены) NoName
 {
  if text { два дня назад } then text { пару дней назад }
 }

 transformation(БуквЗамены) NoName
 {
  if text { два года назад } then text { пару лет назад }
 }

 transformation(БуквЗамены) NoName
 {
  if text { сам он } then text { он сам }
 }

 transformation(БуквЗамены) NoName
 {
  if text { больше не существует } then text { не существует больше }
 }

 transformation(БуквЗамены) NoName
 {
  if text { смириться  можно } then text { можно свыкнуться }
 }

 transformation(БуквЗамены) NoName
 {
  if text { с  трудом } then text { трудно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { трудно разобраться } then text { с трудом удается разобраться }
 }

 transformation(БуквЗамены) NoName
 {
  if text { другую  попытку } then text { еще одну попытку }
 }

 transformation(БуквЗамены) NoName
 {
  if text { придя в себя } then text { вернувшись в чувство }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Ты ведь работал } then text { Ведь ты работал }
 }

 transformation(БуквЗамены) NoName
 {
  if text { мне удалось } then text { у меня получилось }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Дай взглянуть } then text { позволь посмотреть }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Я должен увидеть } then text { Мне надо увидеть }
 }

 transformation(БуквЗамены) NoName
 {
  if text { суть сохранится } then text { смысл останется }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Кто же это } then text { Это кто }
 }

 transformation(БуквЗамены) NoName
 {
  if text { центральный банк } then text { центробанк }
 }

 transformation(БуквЗамены) NoName
 {
  if text { председатель правительства } then text { премьер-министр }
 }

 transformation(БуквЗамены) NoName
 {
  if text { давать в долг } then text { одалживать }
 }

 transformation(БуквЗамены) NoName
 {
  if text { дать в долг } then text { одолжить }
 }

 transformation(БуквЗамены) NoName
 {
  if text { давал в долг } then text { одалживал }
 }

 transformation(БуквЗамены) NoName
 {
  if text { дал в долг } then text { одолжил }
 }

 transformation(БуквЗамены) NoName
 {
  if text { по истечению срока } then text { по окончании срока }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Он понятия не имел, что } then text { ему не было ясно, что }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Сквозь застилавший глаза туман } then text { сквозь туман, застилавший глаза, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Да-да } then text { безусловно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { в глубине души } then text { глубоко в душе }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Не надо  так  говорить } then text { не следует говорить так }
 }

 transformation(БуквЗамены) NoName
 {
  if text { что тебя привлекло } then text { что тебе нравилось }
 }

 transformation(БуквЗамены) NoName
 {
  if text { все равно } then text { так или иначе }
 }

 transformation(БуквЗамены) NoName
 {
  if text { так или иначе } then text { все равно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Через  несколько  секунд } then text { спустя считанные секунды }
 }

 transformation(БуквЗамены) NoName
 {
  if text { протянуть можно } then text { можно протянуть }
 }

 transformation(БуквЗамены) NoName
 {
  if text { в  высшей  степени } then text { исключительно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { факт остается  фактом } then text { с фактом не поспоришь }
 }

 transformation(БуквЗамены) NoName
 {
  if text { на  путешествие  в } then text { для путешествия }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ,  которую  называли } then text { , называемую }
 }

 transformation(БуквЗамены) NoName
 {
  if text { где мы } then text { мы где }
 }

 transformation(БуквЗамены) NoName
 {
  if text { я рад это слышать } then text { мне приятно это слышать }
 }

 transformation(БуквЗамены) NoName
 {
  if text { сошел с ума } then text { спятил }
 }

 transformation(БуквЗамены) NoName
 {
  if text { сошла с ума } then text { спятила }
 }

 transformation(БуквЗамены) NoName
 {
  if text { что-то с ним } then text { с ним что-то }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Кто это сказал } then text { кто сказал это }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Понятия не имею } then text { понятия не имею }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Где ты } then text { где ты }
 }

 transformation(БуквЗамены) NoName
 {
  if text { как это остановить } then text { как остановить это }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Успокойтесь, пожалуйста, } then text { пожалуйста, успокойтесь, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Не в этом дело } then text { это не важно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { с нами об этом } then text { об этом с нами }
 }

 transformation(БуквЗамены) NoName
 {
  if text { с этим они } then text { они с этим }

 }

 transformation(БуквЗамены) NoName
 {
  if text { белая кошка } then text { кошка белой окраски }
 }

 transformation(БуквЗамены) NoName
 {
  if text { черная кошка } then text { кошка черной окраски }
 }

 transformation(БуквЗамены) NoName
 {
  if text { белая кошка } then text { кошка белой окраски }
 }

 transformation(БуквЗамены) NoName
 {
  if text { дымчатая кошка } then text { кошка дымчатого окраса }
 }

 transformation(БуквЗамены) NoName
 {
  if text { маленькая кошка } then text { кошка небольшого размера }
 }

 transformation(БуквЗамены) NoName
 {
  if text { полосатая } then text { с полосками }
 }

 transformation(БуквЗамены) NoName
 {
  if text { полосатый } then text { с полосками }
 }

 transformation(БуквЗамены) NoName
 {
  if text { грустящий } then text { испытывающий грусть }
 }

 transformation(БуквЗамены) NoName
 {
  if text { грустящая } then text { испытывающая грусть }
 }

 transformation(БуквЗамены) NoName
 {
  if text { радующийся } then text { испытывающий радость }
 }

 transformation(БуквЗамены) NoName
 {
  if text { радующаяся } then text { испытывающая радость }
 }

 transformation(БуквЗамены) NoName
 {
  if text { бурно радоваться } then text { ликовать }
 }

 transformation(БуквЗамены) NoName
 {
  if text { помрачнел } then text { стал мрачным }
 }

 transformation(БуквЗамены) NoName
 {
  if text { позеленел } then text { стал зеленым }
 }

 transformation(БуквЗамены) NoName
 {
  if text { везде } then text { тут и там }
 }

 transformation(БуквЗамены) NoName
 {
  if text { футбольный мяч } then text { мяч для игры в футбол }
 }

 transformation(БуквЗамены) NoName
 {
  if text { теннисным мячик } then text { мячик для игры в пинг-понг }
 }

 transformation(БуквЗамены) NoName
 {
  if text { шерстяной шарф } then text { шарф из шерсти }
 }

 transformation(БуквЗамены) NoName
 {
  if text { кожаная куртка } then text { куртка из кожи }
 }

 transformation(БуквЗамены) NoName
 {
  if text { куриный бульон } then text { бульон из курицы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { овощное рагу } then text { рагу из овощей }
 }

 transformation(БуквЗамены) NoName
 {
  if text { мясной бульон } then text { бульон на мясе }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ватный тампон } then text { тампон из ваты }
 }

 transformation(БуквЗамены) NoName
 {
  if text { пеньковая веревка } then text { веревка из пеньки }
 }

 transformation(БуквЗамены) NoName
 {
  if text { наркотический бред } then text { бред от действия наркотиков }
 }

 transformation(БуквЗамены) NoName
 {
  if text { упал в обморок } then text { потерял сознание }
 }

 transformation(БуквЗамены) NoName
 {
  if text { упала в обморок } then text { потеряла сознание }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ненормативная лексика } then text { матершина }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ненормативной лексики } then text { матершины }
 }

 transformation(БуквЗамены) NoName
 {
  if text { американская армия } then text { армия США }
 }

 transformation(БуквЗамены) NoName
 {
  if text { американскими военными } then text { военнослужащими США }
 }

 transformation(БуквЗамены) NoName
 {
  if text { российская армия } then text { армия РФ }
 }

 transformation(БуквЗамены) NoName
 {
  if text { автомобильная парковка } then text { автопарковка }
 }

 transformation(БуквЗамены) NoName
 {
  if text { бумажный пакет } then text { пакет из бумаги }
 }

 transformation(БуквЗамены) NoName
 {
  if text { цейлонский чай } then text { чай с Цейлона }
 }

 transformation(БуквЗамены) NoName
 {
  if text { овощной салат } then text { салат из овощей }
 }

 transformation(БуквЗамены) NoName
 {
  if text { овощные салаты } then text { салаты из овощей }
 }

 transformation(БуквЗамены) NoName
 {
  if text { фруктовый мусс } then text { мусс из фруктов }
 }

 transformation(БуквЗамены) NoName
 {
  if text { овощное пюре } then text { пюре из овощей }
 }

 transformation(БуквЗамены) NoName
 {
  if text { деревянная ложка } then text { ложка из дерева }
 }

 transformation(БуквЗамены) NoName
 {
  if text { деревянной ложкой } then text { ложкой из дерева }
 }

 transformation(БуквЗамены) NoName
 {
  if text { бронзовая статуя } then text { статуя из бронзы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { стеклянные бусы } then text { бусы из стекла }
 
 }

 transformation(БуквЗамены) NoName
 {
  if text { о книге } then text { про книгу }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Заботило его  } then text { его волновало }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , чем все думают } then text { , чем думают люди }
 }

 transformation(БуквЗамены) NoName
 {
  if text { лил дождь } then text { шел проливной дождь }
 }

 transformation(БуквЗамены) NoName
 {
  if text { раскисла и потекла } then text { потекла и раскисла }
 }

 transformation(БуквЗамены) NoName
 {
  if text { - как выяснилось, в последний раз } then text { - в последний раз, как выяснилось }
 }

 transformation(БуквЗамены) NoName
 {
  if text { далеко не блестяще } then text { не очень хорошо }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Установленное правильно, } then text { правильно установленное, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { побрел в спальню одеваться } then text { пошел одеться в спальню }
 }

 transformation(БуквЗамены) NoName
 {
  if text { потом еще один } then text { затем другой }
 }

 transformation(БуквЗамены) NoName
 {
  if text { пришел к выводу  } then text { решил }
 }

 transformation(БуквЗамены) NoName
 {
  if text { долго и пространно } then text { пространно и долго }
 }

 transformation(БуквЗамены) NoName
 {
  if text { на дворе  } then text { во дворе }
 }

 transformation(БуквЗамены) NoName
 {
  if text { прямым потомком  } then text { непосредственным потомком }
 }

 transformation(БуквЗамены) NoName
 {
  if text { меховым шапочкам } then text { шапочкам из меха }
 }

 transformation(БуквЗамены) NoName
 {
  if text { задают себе вопрос } then text { задаются вопросом }
 }

 transformation(БуквЗамены) NoName
 {
  if text { маленький уютный  } then text { уютный маленький }
 }

 transformation(БуквЗамены) NoName
 {
  if text { над входной дверью  } then text { над входом }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ближайшей } then text { самой близкой }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ближайшая } then text { самая близкая }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ближайшее } then text { самое близкое }
 }

 transformation(БуквЗамены) NoName
 {
  if text { кратчайший } then text { самый короткий }
 }

 transformation(БуквЗамены) NoName
 {
  if text { крупнейший } then text { самый крупный }
 }

 transformation(БуквЗамены) NoName
 {
  if text { крупнейшего } then text { самого крупного }
 }

 transformation(БуквЗамены) NoName
 {
  if text { крупнейшую } then text { самую крупную }
 }

 transformation(БуквЗамены) NoName
 {
  if text { серьезнейшую } then text { самую серьезную }
 }

 transformation(БуквЗамены) NoName
 {
  if text { серьезнейшая } then text { самая серьезная }
 }

 transformation(БуквЗамены) NoName
 {
  if text { серьезнейший } then text { самый серьезный }
 }

 transformation(БуквЗамены) NoName
 {
  if text { крупнейшие } then text { самые крупные }
 }

 transformation(БуквЗамены) NoName
 {
  if text { сильнейший } then text { самый сильный }
 }

 transformation(БуквЗамены) NoName
 {
  if text { сильнейшие } then text { самые сильные }
 }

 transformation(БуквЗамены) NoName
 {
  if text { быстрейший } then text { самый быстрый }
 }

 transformation(БуквЗамены) NoName
 {
  if text { точнейший } then text { сам точный }
 }

 transformation(БуквЗамены) NoName
 {
  if text { точнейшая } then text { самая точная }
 }

 transformation(БуквЗамены) NoName
 {
  if text { мельчайший } then text { самый мелкий }
 }

 transformation(БуквЗамены) NoName
 {
  if text { мельчайшая } then text { самая мелкая  }
 }

 transformation(БуквЗамены) NoName
 {
  if text { мельчашие } then text { самые мелкие }
 }

 transformation(БуквЗамены) NoName
 {
  if text { отвратительнейший } then text { самый отвратительный }
 }

 transformation(БуквЗамены) NoName
 {
  if text { честнейший } then text { самый искренний }
 }

 transformation(БуквЗамены) NoName
 {
  if text { услышал об этом, когда  } then text { об этом услышал, когда }
 }

 transformation(БуквЗамены) NoName
 {
  if text { это было вчера } then text { это вчера было }
 }

 transformation(БуквЗамены) NoName
 {
  if text { обычно заканчивались плохо } then text { обычно плохо заканчивались }
 }

 transformation(БуквЗамены) NoName
 {
  if text { по рассеянности } then text { из-за невнимательности }
 }

 transformation(БуквЗамены) NoName
 {
  if text { где-нибудь поговорить } then text { поговорить где-то }
 }

 transformation(БуквЗамены) NoName
 {
  if text { должен затем  } then text { затем должен }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Раз проиграв, } then text { проиграв один раз, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { он хочет  } then text { ему хочется }
 }

 transformation(БуквЗамены) NoName
 {
  if text { я хочу } then text { мне хочется }
 }

 transformation(БуквЗамены) NoName
 {
  if text { она хочет } then text { ей хочется }
 }

 transformation(БуквЗамены) NoName
 {
  if text { мы хотим } then text { нам хочется }
 }

 transformation(БуквЗамены) NoName
 {
  if text { вы хотите } then text { вам хочется }
 }

 transformation(БуквЗамены) NoName
 {
  if text { бить баклуши } then text { бездельничать }
 }

 transformation(БуквЗамены) NoName
 {
  if text { валять дурака } then text { бездельничать }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Необходимости в этом нет } then text { В этом нет необходимости }
 }

 transformation(БуквЗамены) NoName
 {
  if text { был обеспокоен. } then text { испытывал беспокойство. }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Если честно - } then text { по правде говоря - }
 }

 transformation(БуквЗамены) NoName
 {
  if text { более чем достаточно } then text { вполне достаточно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Что это за  } then text { это что за }
 }

 transformation(БуквЗамены) NoName
 {
  if text {  с ума схожу } then text { лишаюсь рассудка }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Понятия не имею } then text { не знаю }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Что это значит } then text { Это что значит }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ума не приложу } then text { не понимаю }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Тебе не кажется, что  } then text { ты не думаешь, что }
 }

 transformation(БуквЗамены) NoName
 {
  if text { абрикосовое варенье } then text { варенье из абриковос }
 }

 transformation(БуквЗамены) NoName
 {
  if text { сливовое варенье } then text { варенье из сливы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { вишневый джем } then text { джем из вишни }
 }

 transformation(БуквЗамены) NoName
 {
  if text { клубничное варенье } then text { варенье из клубники }
 }

 transformation(БуквЗамены) NoName
 {
  if text { земляничное варенье } then text { варенье из земляники }
 }

 transformation(БуквЗамены) NoName
 {
  if text { проливной дождь } then text { ливень }
 }

 transformation(БуквЗамены) NoName
 {
  if text { шквалистый ветер } then text { ветер с порывами }

 }

 transformation(БуквЗамены) NoName
 {
  if text { тут и там } then text { повсюду }
 }

 transformation(БуквЗамены) NoName
 {
  if text { рынке акций } then text { фондовом рынке }
 }

 transformation(БуквЗамены) NoName
 {
  if text { президент России } then text { Российский Президент }
 }

 transformation(БуквЗамены) NoName
 {
  if text { российское правительство } then text { Правительство России }
 }

 transformation(БуквЗамены) NoName
 {
  if text { стать прибыльным } then text { получить прибыль }
 }

 transformation(БуквЗамены) NoName
 {
  if text { инвестиции в развитие производства } then text { производственные инвестиции }
 }

 transformation(БуквЗамены) NoName
 {
  if text { провести встречу } then text { встретиться }
 }

 transformation(БуквЗамены) NoName
 {
  if text { главой МИД } then text { министром иностранных дел }
 }

 transformation(БуквЗамены) NoName
 {
  if text { дело в отношении преступной группы } then text { дело преступной группы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { о признании недействительным } then text { об отмене }
 }

 transformation(БуквЗамены) NoName
 {
  if text { будут судить за } then text { предадут суду за }
 }

 transformation(БуквЗамены) NoName
 {
  if text { промышленного производства } then text { промпроизводства }
 }

 transformation(БуквЗамены) NoName
 {
  if text { промпроизводства } then text { промышленного производства }
 }

 transformation(БуквЗамены) NoName
 {
  if text { выборам в парламент } then text { парламентским выборам }
 }

 transformation(БуквЗамены) NoName
 {
  if text { на территории России } then text { на территории Российской Федерации }
 }

 transformation(БуквЗамены) NoName
 {
  if text { предположительно будут } then text { будут предположительно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { выросло дл } then text { достигло }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , обвиняемого в } then text { , которого обвиняют в }
 }

 transformation(БуквЗамены) NoName
 {
  if text { российской экономики } then text { экономики России }
 }

 transformation(БуквЗамены) NoName
 {
  if text { цен на нефть } then text { нефтяных цен }
 }

 transformation(БуквЗамены) NoName
 {
  if text { цен на нефть и газ } then text { нефтяных и газовых цен }
 }

 transformation(БуквЗамены) NoName
 {
  if text { спад в России } then text { спад в Российской Федерации }
 }

 transformation(БуквЗамены) NoName
 {
  if text { дал поручение } then text { поручил }
 }

 transformation(БуквЗамены) NoName
 {
  if text { поручил } then text { дал поручение }
 }

 transformation(БуквЗамены) NoName
 {
  if text { дал указание выплатить } then text { распорядился выплатить }
 }

 transformation(БуквЗамены) NoName
 {
  if text { дал указание начать } then text { распорядился начать }
 }

 transformation(БуквЗамены) NoName
 {
  if text { классика зарубежного кино } then text { зарубежная киноклассика }
 }

 transformation(БуквЗамены) NoName
 {
  if text { отечественные мультфильмы } then text { наши мультики }
 }

 transformation(БуквЗамены) NoName
 {
  if text { приколы и юмор } then text { юмор и приколы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { жестким диском } then text { винчестером }
 }

 transformation(БуквЗамены) NoName
 {
  if text { детская литература } then text { литература для детей }
 }

 transformation(БуквЗамены) NoName
 {
  if text { прогнозы и комментарии } then text { комментарии и прогнозы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { сохранить и приумножить } then text { приумножить и сохранить }
 }

 transformation(БуквЗамены) NoName
 {
  if text { объявления и анонсы } then text { анонсы и объявления }
 }

 transformation(БуквЗамены) NoName
 {
  if text { правила и инструкции } then text { инструкции и правила }
 }

 transformation(БуквЗамены) NoName
 {
  if text { сбережения и инвестиции } then text { инвестиции и сбережения }
 }

 transformation(БуквЗамены) NoName
 {
  if text { советы и рекомендации } then text { рекомендации и советы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { рынки и биржы } then text { биржы и рынки }
 }

 transformation(БуквЗамены) NoName
 {
  if text { по улучшению и развитию } then text { по развитию и улучшению }
 }

 transformation(БуквЗамены) NoName
 {
  if text { при всём при том, что } then text { хотя }
 }

 transformation(БуквЗамены) NoName
 {
  if text { хотя бы } then text { хотя бы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { хотя } then text { при всем при том, что }
 }

 transformation(БуквЗамены) NoName
 {
  if text { не смотря на то, что } then text { при все при том, что }
 }

 transformation(БуквЗамены) NoName
 {
  if text { латвийских проблем } then text { проблем Латвии }
 }

 transformation(БуквЗамены) NoName
 {
  if text { российских проблем } then text { проблем России }
 }

 transformation(БуквЗамены) NoName
 {
  if text { только народ, доведенный } then text { лишь население, доведенное }
 }

 transformation(БуквЗамены) NoName
 {
  if text { смертных грехах } then text { тяжких прегрешениях }
 }

 transformation(БуквЗамены) NoName
 {
  if text { идете по этому пути } then text { двигаетесь этим путем }
 }

 transformation(БуквЗамены) NoName
 {
  if text { никому ничего } then text { ничего никому }
 }

 transformation(БуквЗамены) NoName
 {
  if text { помощь больным детям } then text { помощь для больных детей }
 }

 transformation(БуквЗамены) NoName
 {
  if text { чью сторону ты примешь } then text { на чьей стороне ты окажешься }
 }

 transformation(БуквЗамены) NoName
 {
  if text { на чьей стороне ты окажешься } then text { чью сторону ты примешь }
 }

 transformation(БуквЗамены) NoName
 {
  if text { лелеет мечту } then text { мечтает }
 }

 transformation(БуквЗамены) NoName
 {
  if text { лелеет мечты } then text { мечтает }
 }

 transformation(БуквЗамены) NoName
 {
  if text { лелеял мечту } then text { мечтал }
 }

 transformation(БуквЗамены) NoName
 {
  if text { спасибо огромное } then text { огромное спасибо }
 }

 transformation(БуквЗамены) NoName
 {
  if text { огромное спасибо } then text { спасибо огромное }
 }

 transformation(БуквЗамены) NoName
 {
  if text { большое спасибо } then text { спасибо огромное }
 }

 transformation(БуквЗамены) NoName
 {
  if text { лично к Вам } then text { к Вам лично }
 }

 transformation(БуквЗамены) NoName
 {
  if text { пройти регистрацию } then text { зарегистрироваться }
 }

 transformation(БуквЗамены) NoName
 {
  if text { официально не перекрывали } then text { не перекрывали официально }
 }

 transformation(БуквЗамены) NoName
 {
  if text { не обязательно совпадает  } then text { не обязательно совпадает }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , опубликованных на } then text { , которые опубликованы на }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , сохраненных на } then text { , которые сохранены на }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , скопированных в } then text { , которые скопированы в }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , разработанных в } then text { , которые разработаны в }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , реализованных через } then text { , которые реализованы через }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , купленных в } then text { , которые куплены в }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , сброшенных по } then text { , которые сброшены в }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , скопированных на } then text { , которые скопированы на }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , взятый за основу } then text { , который взят в качестве основы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , принятый в } then text { , который принят в }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , принятые в } then text { , которые приняты в }
 }

 transformation(БуквЗамены) NoName
 {
  if text { отечественные фильмы } then text { российские фильмы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { отечественная классика } then text { российская классика }
 }

 transformation(БуквЗамены) NoName
 {
  if text { отечественные мультфильмы } then text { российские мультфильмы }
 }

 transformation(БуквЗамены) NoName
 {
  if text { в целях } then text { для }
 }

 transformation(БуквЗамены) NoName
 {
  if text { при наличии согласия } then text { при согласии }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ответные меры } then text { контрмеры }
 }

 transformation(БуквЗамены) NoName
 {
  if text { малой кровью } then text { без особых усилий }
 }

 transformation(БуквЗамены) NoName
 {
  if text { потом и кровью } then text { большими жертвами }
 }

 transformation(БуквЗамены) NoName
 {
  if text { больше никого не было видно } then text { никого больше не было видно }
 }
 

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им}, 'выставленные' } then text { , которые были выставленны }
 }

 transformation(БуквЗамены)
 { if context { существительное:*{число:ед падеж:им}, 'проданные' } then text { , которые были проданы }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'выпитый' } then text { , который был выпит }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'выпитый' } then text { , который был выпит }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'вывихнутый' } then text { , который был вывихнут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'вывихнутый' } then text { , который был вывихнут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'выводимый' } then text { , который выводится }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'выводимый' } then text { , который выводится }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'выгнутый' } then text { , который был выгнут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'выгнутый' } then text { , который был выгнут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'выкинутый' } then text { , который был выкинут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'выкинутый' } then text { , который был выкинут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'вымытый' } then text { , который был вымыт }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'вымытый' } then text { , который был вымыт }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'вытертый' } then text { , который был вытерт }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'вытертый' } then text { , который был вытерт }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'вычеркнутый' } then text { , который был вычеркнут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'вычеркнутый' } then text { , который был вычеркнут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'завернутый' } then text { , который был завернут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'завернутый' } then text { , который был завернут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'затронутый' } then text { , который был затронут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'затронутый' } then text { , который был затронут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'зашитый' } then text { , который был зашит }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'зашитый' } then text { , который был зашит }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'игнорируемый' } then text { , который игнорируется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'игнорируемый' } then text { , который игнорируется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'извергнутый' } then text { , который был извергнут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'извергнутый' } then text { , который был извергнут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'извлекаемый' } then text { , который извлекается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'извлекаемый' } then text { , который извлекается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'ИЗГОТОВЛЯЕМЫЙ' } then text { , который изготовляется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'ИЗГОТОВЛЯЕМЫЙ' } then text { , который изготовляется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'излучаемый' } then text { , который излучается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'излучаемый' } then text { , который излучается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'измятый' } then text { , который был измят }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'измятый' } then text { , который был измят }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'изучаемый' } then text { , который изучается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'изучаемый' } then text { , который изучается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'именуемый' } then text { , который именуется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'именуемый' } then text { , который именуется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'импортируемый' } then text { , который импортируется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'импортируемый' } then text { , который импортируется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'исчисляемый' } then text { , который исчисляется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'исчисляемый' } then text { , который исчисляется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'культивируемый' } then text { , который культивируется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'культивируемый' } then text { , который культивируется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, 'накапливаемый' } then text { , который накапливается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, 'накапливаемый' } then text { , который накапливается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НАНИМАЕМЫЙ{_им} } then text { , которого нанимают }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НАНИМАЕМЫЙ{_вин} } then text { , которого нанимают  }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НАСТИГНУТЫЙ{_им} } then text { , который был настигнут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НАСТИГНУТЫЙ{_вин} } then text { , который был настигнут }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НАСТРАИВАЕМЫЙ{_им} } then text { , который настраивается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НАСТРАИВАЕМЫЙ{_вин} } then text { , который настраивается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НАСЫЩАЕМЫЙ{_им} } then text { , который насыщается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НАСЫЩАЕМЫЙ{_вин} } then text { , который насыщается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕГОТОВЫЙ{_им} } then text { , который не готов }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕГОТОВЫЙ{_вин} } then text { , который не готов }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕЗАБИТЫЙ{_им} } then text { , который не был забит }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕЗАБИТЫЙ{_вин} } then text { , который не был забит }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕЗАБЫТЫЙ{_им} } then text { , который не был забыт }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕЗАБЫТЫЙ{_вин} } then text { , который не был забыт }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕЗАКРЫТЫЙ{_им} } then text { , который не был закрыт }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕЗАКРЫТЫЙ{_вин} } then text { , который не был закрыт }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕЗАПЕРТЫЙ{_им} } then text { , который не был заперт }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕЗАПЕРТЫЙ{_вин} } then text { , который не был заперт }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕЗАТРОНУТЫЙ{_им} } then text { , который не был затронут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕЗАТРОНУТЫЙ{_вин} } then text { , который не был затронут }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕИСПОЛЬЗУЕМЫЙ{_им} } then text { , который не используется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕИСПОЛЬЗУЕМЫЙ{_вин} } then text { , который не используется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕКОНВЕРТИРУЕМЫЙ{_им} } then text { , который не конвертируется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕКОНВЕРТИРУЕМЫЙ{_вин} } then text { , который не конвертируется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕКОНТРОЛИРУЕМЫЙ{_им} } then text { , который не контролируется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕКОНТРОЛИРУЕМЫЙ{_вин} } then text { , который не контролируется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕНАБЛЮДАЕМЫЙ{_им} } then text { , который не наблюдается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕНАБЛЮДАЕМЫЙ{_вин} } then text { , который не наблюдается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕНАГРЕТЫЙ{_им} } then text { , который не был нагрет }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕНАГРЕТЫЙ{_вин} } then text { , который не был нагрет }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕНАДУТЫЙ{_им} } then text { , который не был надут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕНАДУТЫЙ{_вин} } then text { , который не был надут }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕНАТЯНУТЫЙ{_им} } then text { , который не был натянут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕНАТЯНУТЫЙ{_вин} } then text { , который не был натянут }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕОБРАБАТЫВАЕМЫЙ{_им} } then text { , который не обрабатывается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕОБРАБАТЫВАЕМЫЙ{_вин} } then text { , который не обрабатывается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕОБУТЫЙ{_им} } then text { , который не был обут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕОБУТЫЙ{_вин} } then text { , который не был обут }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕОДЕТЫЙ{_им} } then text { , который не был одет }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕОДЕТЫЙ{_вин} } then text { , который не был одет }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕОПЛАЧИВАЕМЫЙ{_им} } then text { , который не оплачивается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕОПЛАЧИВАЕМЫЙ{_вин} } then text { , который не оплачивается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕОПРЕДЕЛИМЫЙ{_им} } then text { , который не определяется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕОПРЕДЕЛИМЫЙ{_вин} } then text { , который не определяется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕОСПАРИВАЕМЫЙ{_им} } then text { , который не оспаривается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕОСПАРИВАЕМЫЙ{_вин} } then text { , который не оспаривается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕОСЯЗАЕМЫЙ{_им} } then text { , который не осязается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕОСЯЗАЕМЫЙ{_вин} } then text { , который не осязается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕОТКРЫТЫЙ{_им} } then text { , который не был открыт }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕОТКРЫТЫЙ{_вин} } then text { , который не был открыт }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕОТЛИЧИМЫЙ{_им} } then text { , который нельзя отличить }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕОТЛИЧИМЫЙ{_вин} } then text { , который нельзя отличить }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕОТМЕНЯЕМЫЙ{_им} } then text { , который нельзя отменить }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕОТМЕНЯЕМЫЙ{_вин} } then text { , который нельзя отменить }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕОТЧУЖДАЕМЫЙ{_им} } then text { , который нельзя отчуждать }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕОТЧУЖДАЕМЫЙ{_вин} } then text { , который нельзя отчуждать }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕОЩУТИМЫЙ{_им} } then text { , который нельзя ощутить }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕОЩУТИМЫЙ{_вин} } then text { , который нельзя ощутить }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕПОДЧЕРКНУТЫЙ{_им} } then text { , который не был подчеркнут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕПОДЧЕРКНУТЫЙ{_вин} } then text { , который не был подчеркнут }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕПОНЯТЫЙ{_им} } then text { , который не был понят }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕПОНЯТЫЙ{_вин} } then text { , который не был понят }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕПОСЕЩАЕМЫЙ{_им} } then text { , который не посещается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕПОСЕЩАЕМЫЙ{_вин} } then text { , который не посещается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕПОТРЕБЛЯЕМЫЙ{_им} } then text { , который непотребляется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕПОТРЕБЛЯЕМЫЙ{_вин} } then text { , который непотребляется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕПРАЗДНУЕМЫЙ{_им} } then text { , который не празднуется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕПРАЗДНУЕМЫЙ{_вин} } then text { , который не празднуется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕПРЕРЫВАЕМЫЙ{_им} } then text { , который не прерывается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕПРЕРЫВАЕМЫЙ{_вин} } then text { , который не прерывается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕПРИМЕНИМЫЙ{_им} } then text { , который нельзя применять }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕПРИМЕНИМЫЙ{_вин} } then text { , который нельзя применять }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕПРИНЯТЫЙ{_им} } then text { , который не был принят }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕПРИНЯТЫЙ{_вин} } then text { , который не был принят }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕРАСКРЫТЫЙ{_им} } then text { , который не был раскрыт }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕРАСКРЫТЫЙ{_вин} } then text { , который не был раскрыт }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕРЕАЛИЗУЕМЫЙ{_им} } then text { , который невозможно реализовать }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕРЕАЛИЗУЕМЫЙ{_вин} } then text { , который невозможно реализовать }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕСДВИНУТЫЙ{_им} } then text { , который не был сдвинут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕСДВИНУТЫЙ{_вин} } then text { , который не был сдвинут }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕСМЫВАЕМЫЙ{_им} } then text { , который нельзя смыть }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕСМЫВАЕМЫЙ{_вин} } then text { , который нельзя смыть }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕСНЯТЫЙ{_им} } then text { , который не был снят }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕСНЯТЫЙ{_вин} } then text { , который не был снят }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕСПЕТЫЙ{_им} } then text { , который не был спет }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕСПЕТЫЙ{_вин} } then text { , который не был спет }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕСТРИЖЕНЫЙ{_им} } then text { , который не был стрижен }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕСТРИЖЕНЫЙ{_вин} } then text { , который не был стрижен }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕУПОМЯНУТЫЙ{_им} } then text { , который не был упомянут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕУПОМЯНУТЫЙ{_вин} } then text { , который не был упомянут }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, НЕУПРАВЛЯЕМЫЙ{_им} } then text { , который не управляется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, НЕУПРАВЛЯЕМЫЙ{_вин} } then text { , который не управляется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ОБВИНЯЕМЫЙ{_им} } then text { , который обвиняется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ОБВИНЯЕМЫЙ{_вин} } then text { , который обвиняется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ОБЕРНУТЫЙ{_им} } then text { , который был обернут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ОБЕРНУТЫЙ{_вин} } then text { , который был обернут }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ОБЛАГАЕМЫЙ{_им} } then text { , который облагается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ОБЛАГАЕМЫЙ{_вин} } then text { , который облагается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ОБНОВЛЯЕМЫЙ{_им} } then text { , который обновляется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ОБНОВЛЯЕМЫЙ{_вин} } then text { , который обновляется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ОБРАБАТЫВАЕМЫЙ{_им} } then text { , который обрабатывается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ОБРАБАТЫВАЕМЫЙ{_вин} } then text { , который обрабатывается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ОБРАЗУЕМЫЙ{_им} } then text { , который образуется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ОБРАЗУЕМЫЙ{_вин} } then text { , который образуется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ОБСУЖДАЕМЫЙ{_им} } then text { , который обсуждается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ОБСУЖДАЕМЫЙ{_вин} } then text { , который обсуждается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ОПЕКАЕМЫЙ{_им} } then text { , который опекается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ОПЕКАЕМЫЙ{_вин} } then text { , который опекается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ОПЛАЧИВАЕМЫЙ{_им} } then text { , который оплачивается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ОПЛАЧИВАЕМЫЙ{_вин} } then text { , который оплачивается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ОПРАШИВАЕМЫЙ{_им} } then text { , который опрашивается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ОПРАШИВАЕМЫЙ{_вин} } then text { , который опрашивается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ОПРЕДЕЛЯЕМЫЙ{_им} } then text { , который определяется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ОПРЕДЕЛЯЕМЫЙ{_вин} } then text { , который определяется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ОПРОВЕРГНУТЫЙ{_им} } then text { , который был опровергнут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ОПРОВЕРГНУТЫЙ{_вин} } then text { , который был опровергнут }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ОСПАРИВАЕМЫЙ{_им} } then text { , который оспаривается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ОСПАРИВАЕМЫЙ{_вин} } then text { , который оспаривается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ОТКИНУТЫЙ{_им} } then text { , который был откинут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ОТКИНУТЫЙ{_вин} } then text { , который был откинут }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ОЦЕНИВАЕМЫЙ{_им} } then text { , который оценивается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ОЦЕНИВАЕМЫЙ{_вин} } then text { , который оценивается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПАЛЬПИРУЕМЫЙ{_им} } then text { , который пальпируется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПАЛЬПИРУЕМЫЙ{_вин} } then text { , который пальпируется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПЕРЕВОДИМЫЙ{_им} } then text { , который переводится }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПЕРЕВОДИМЫЙ{_вин} } then text { , который переводится }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПЕРЕВОЗИМЫЙ{_им} } then text { , который перевозится }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПЕРЕВОЗИМЫЙ{_вин} } then text { , который перевозится }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПЕРЕЖИВАЕМЫЙ{_им} } then text { , который переживается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПЕРЕЖИВАЕМЫЙ{_вин} } then text { , который переживается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПЕРЕКРЫТЫЙ{_им} } then text { , который был перекрыт }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПЕРЕКРЫТЫЙ{_вин} } then text { , который был перекрыт }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПЕРЕНОСИМЫЙ{_им} } then text { , который переносится }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПЕРЕНОСИМЫЙ{_вин} } then text { , который переносится }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПЕРЕОДЕТЫЙ{_им} } then text { , который был переодет }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПЕРЕОДЕТЫЙ{_вин} } then text { , который был переодет }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПЕРЕСЕКАЕМЫЙ{_им} } then text { , который пересекается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПЕРЕСЕКАЕМЫЙ{_вин} } then text { , который пересекается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПИЛОТИРУЕМЫЙ{_им} } then text { , который пилотируется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПИЛОТИРУЕМЫЙ{_вин} } then text { , который пилотируется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПОДВИНУТЫЙ{_им} } then text { , который был подвинут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПОДВИНУТЫЙ{_вин} } then text { , который был подвинут }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПОДДЕРЖИВАЕМЫЙ{_им} } then text { , который поддерживается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПОДДЕРЖИВАЕМЫЙ{_вин} } then text { , который поддерживается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПОДОГРЕТЫЙ{_им} } then text { , который был подогрет }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПОДОГРЕТЫЙ{_вин} } then text { , который был подогрет }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПОДРАЗУМЕВАЕМЫЙ{_им} } then text { , который подразуемевается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПОДРАЗУМЕВАЕМЫЙ{_вин} } then text { , который подразумевается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПОЗНАВАЕМЫЙ{_им} } then text { , который познается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПОЗНАВАЕМЫЙ{_вин} } then text { , который познается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПОМЯНУТЫЙ{_им} } then text { , который был помянут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПОМЯНУТЫЙ{_вин} } then text { , который был помянут }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПОТРЕБЛЯЕМЫЙ{_им} } then text { , который потребляется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПОТРЕБЛЯЕМЫЙ{_вин} } then text { , который потребляется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, спетый{_им} } then text { , который был спет }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, спетый{_вин} } then text { , который был спет }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПОТРЕБЛЯЕМЫЙ{_им} } then text { , который потребляется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПОТРЕБЛЯЕМЫЙ{_вин} } then text { , который потребляется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПОЧИТАЕМЫЙ{_им} } then text { , который почитается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПОЧИТАЕМЫЙ{_вин} } then text { , который почитается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПОШИТЫЙ{_им} } then text { , который был пошит }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПОШИТЫЙ{_вин} } then text { , который был пошит }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРЕДНАЗНАЧАЕМЫЙ{_им} } then text { , который предназначается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРЕДНАЗНАЧАЕМЫЙ{_вин} } then text { , который предназначается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРЕДОПРЕДЕЛЯЕМЫЙ{_им} } then text { , который предопределяется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРЕДОПРЕДЕЛЯЕМЫЙ{_вин} } then text { , который предопределяется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРЕДОСТАВЛЯЕМЫЙ{_им} } then text { , который предоставляется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРЕДОСТАВЛЯЕМЫЙ{_вин} } then text { , который предоставляется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРЕДСТАВЛЯЕМЫЙ{_им} } then text { , который представляется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРЕДСТАВЛЯЕМЫЙ{_вин} } then text { , который представляется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРЕПОДНОСИМЫЙ{_им} } then text { , который преподносится }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРЕПОДНОСИМЫЙ{_вин} } then text { , который преподносится }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРИВОДИМЫЙ{_им} } then text { , который приводится }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРИВОДИМЫЙ{_вин} } then text { , который приводится }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, признаваемый{_им} } then text { , который признается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, признаваемый{_вин} } then text { , который признается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРИЛАГАЕМЫЙ{_им} } then text { , который прилагается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРИЛАГАЕМЫЙ{_вин} } then text { , который прилагается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРИНИМАЕМЫЙ{_им} } then text { , который принимается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРИНИМАЕМЫЙ{_вин} } then text { , который принимается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРИНОСИМЫЙ{_им} } then text { , который приносится }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРИНОСИМЫЙ{_вин} } then text { , который приносится }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРИПИСЫВАЕМЫЙ{_им} } then text { , который приписывается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРИПИСЫВАЕМЫЙ{_вин} } then text { , который приписывается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРИСОЕДИНЯЕМЫЙ{_им} } then text { , который присоединяется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРИСОЕДИНЯЕМЫЙ{_вин} } then text { , который присоединяется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРИШИТЫЙ{_им} } then text { , который был пришит }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРИШИТЫЙ{_вин} } then text { , который был пришит }

 }


 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРОГРАММИРУЕМЫЙ{_вин} } then text { , который программируется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРОИЗВОДИМЫЙ{_им} } then text { , который производится }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРОИЗВОДИМЫЙ{_вин} } then text { , который производится }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРОКОЛОТЫЙ{_им} } then text { , который был проколот }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРОКОЛОТЫЙ{_вин} } then text { , который был проколот }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРОПИСЫВАЕМЫЙ{_им} } then text { , который прописывается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРОПИСЫВАЕМЫЙ{_вин} } then text { , который прописывается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРОПОВЕДУЕМЫЙ{_им} } then text { , который проповедуется }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРОПОВЕДУЕМЫЙ{_вин} } then text { , который проповедуется }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, ПРОСЛЕЖИВАЕМЫЙ{_им} } then text { , который прослеживается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, ПРОСЛЕЖИВАЕМЫЙ{_вин} } then text { , который прослеживается }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, РАЗВЕРНУТЫЙ{_им} } then text { , который был развернут }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, РАЗВЕРНУТЫЙ{_вин} } then text { , который был развернут }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж}, РАЗДУВАЕМЫЙ{_им} } then text { , который раздувается }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж}, РАЗДУВАЕМЫЙ{_вин} } then text { , который раздувается }
 }

 
 
/* 
 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж},  } then text { , который  }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж},  } then text { , который  }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж},  } then text { , который  }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж},  } then text { , который  }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж},  } then text { , который  }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж},  } then text { , который  }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж},  } then text { , который  }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж},  } then text { , который  }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж},  } then text { , который  }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж},  } then text { , который  }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж},  } then text { , который  }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж},  } then text { , который  }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж},  } then text { , который  }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж},  } then text { , который  }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж},  } then text { , который  }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж},  } then text { , который  }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж},  } then text { , который  }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж},  } then text { , который  }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж},  } then text { , который  }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж},  } then text { , который  }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж},  } then text { , который  }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж},  } then text { , который  }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж},  } then text { , который  }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж},  } then text { , который  }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж},  } then text { , который  }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж},  } then text { , который  }

 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:им род:муж},  } then text { , который  }
 }

 transformation(БуквЗамены)
 {
  if context { существительное:*{число:ед падеж:вин род:муж},  } then text { , который  }
 }
*/
 

 
 
 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { еще не одумался } then text { не одумался еще }
 }

 transformation(БуквЗамены) NoName
 {
  if text { попытался сделать  } then text { предпринял попытку выполнить }
 }

 transformation(БуквЗамены) NoName
 {
  if text { так ведь? } then text { правильно? }
 }

 transformation(БуквЗамены) NoName
 {
  if text { предельно ясно } then text { совершенно очевидно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { заикнулся было  } then text { хотел сказать }
 }

 transformation(БуквЗамены) NoName
 {
  if text { твердо сказал  } then text { произнес с уверенностью }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Дай человеку лечь. } then text { Пусть человек приляжет. }
 }

 transformation(БуквЗамены) NoName
 {
  if text { нам ничего не известно } then text { мы ничего не знаем }
 }

 transformation(БуквЗамены) NoName
 {
  if text { не покидала тревога } then text { не оставляли сомнения }
 }

 transformation(БуквЗамены) NoName
 {
  if text { через двенадцать  } then text { через дюжину }
 }

 transformation(БуквЗамены) NoName
 {
  if text { лучший на свете  } then text { лучший в мире }
 }

 transformation(БуквЗамены) NoName
 {
  if text { следует заплатить } then text { должно быть заплачено }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Тебе надо принять  } then text { ты должен принять }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Нам жизненно необходимо } then text { Нам позарез надо }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Неужели ты не понимаешь } then text { Неужто тебе не понятно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { мне нужно сообщить } then text { я должен сообщить }
 }

 transformation(БуквЗамены) NoName
 {
  if text { нам придется } then text { мы должны }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Двое соперников } then text { Два соперника }
 }

 transformation(БуквЗамены) NoName
 {
  if text { ни капли больше } then text { ни капли больше }
 }

 transformation(БуквЗамены) NoName
 {
  if text { он, пожалуй, все-таки не прочь зайти } then text { он не отказался бы заглянуть }
 }

 transformation(БуквЗамены) NoName
 {
  if text { А как же мой дом? } then text { Так что насчет моего дома? }
 }

 transformation(БуквЗамены) NoName
 {
  if text { терпеливо повторил } then text { повторил терпеливо }
 }

 transformation(БуквЗамены) NoName
 {
  if text { мы вас прикроем } then text { прекрытие мы вам обеспечим }
 }

 transformation(БуквЗамены) NoName
 {
  if text { с чувством проговорил } then text { произнес с чувством }
 }

 transformation(БуквЗамены) NoName
 {
  if text { , пожалуйста, } then text { , будьте добры, }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Я, наверное, } then text { Видимо, я }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Кто-то должен } then text { Кому-то следует }
 }

 transformation(БуквЗамены) NoName
 {
  if text { предельно ясно } then text { понятно совершенно ясно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { О чем ты } then text { Ты о чем }
 }

 transformation(БуквЗамены) NoName
 {
  if text { заикнулся было } then text { попытался сказать }
 }

 transformation(БуквЗамены) NoName
 {
  if text { с его плеч будто свалилась огромная тяжесть } then text { будто гигантский камень свалился с его плеч }
 }

 transformation(БуквЗамены) NoName
 {
  if text { На этом условии } then text { при таком условии }
 }


 transformation(БуквЗамены) NoName
 {
  if text { сам он не являет собой  } then text { он сам не представляет }
 }

 transformation(БуквЗамены) NoName
 {
  if text { о котором нам ничего не известно } then text { которое нам совершенно не известно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { Он не подведет } then text { На него можно положиться }
 }

 transformation(БуквЗамены) NoName
 {
  if text { не стоит выеденного яйца } then text { не имеет никакого значения }
 }

 transformation(БуквЗамены) NoName
 {
  declare x_min;
  if context { 'Примерно' 'через' @mark(*,x_min) 'минут' } then text { через x_min минут приблизительно }
 }

 transformation(БуквЗамены) NoName
 {
  if text { преисполненный достоинства  } then text { полный достоинства }
 }

 transformation(БуквЗамены) NoName
 {
  if text { попробовал он снова } then text { попытался он еще раз }
 }

 transformation(БуквЗамены) NoName
 {
  if text { коротко ответил } then text { ответил немногословно }
 } 


 transformation(БуквЗамены) NoName
 {
  if text { Тебе надо принять } then text { Ты должен принять }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { Для расслабления мышц } then text { чтобы мышцы расслабились }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { я прежде этого не замечал } then text { я этого раньше не замечал }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { отхлебнув изрядный глоток } then text { изрядно хлебнув }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { просто приказал } then text { приказал без затей }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { , должно быть, } then text { , наверное, }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { вечно все наперекосяк } then text { обычно все шиворот на выворот }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { тихо попискивал } then text { попискивал тихонько }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { , выпущенная } then text { , которую была выпущена }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { Она выпускалась в } then text { Ее выпускали в }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { в конце концов } then text { наконец }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { По необъяснимым причинам, } then text { В силу неизвестных обстоятельств, }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { с радостью } then text { радостно }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { внезапно спросил } then text { спросил внезапно }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { вскочил на ноги } then text { резко поднялся }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Слава Богу } then text { Хвала Всевышнему }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Пелена спала с его глаз } then text { С его глаз спала пелена }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Несколько секунд } then text { Несколько мгновений }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Пусть забавляются } then text { Пускай веселятся }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { еще раз выглянул в окно, } then text { посмотрел в окно еще раз }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { чтобы убедиться, что } then text { дабы убедиться в том, что }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { под воздействием стресса } then text { под влиянием стресса }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { в данный момент } then text { сейчас }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Вы серьезно, сэр } then text { Вы не шутите, мистер }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { скоро наступит конец света } then text { конец света близок }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Прямо вот так } then text { Нужто вот так }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { овладев собой } then text { взяв себя в руки }
 } 

 transformation(БуквЗамены) NoName
 {
  declare x;
  if context { 'меньше' @mark(*,x) 'минут' } then text { менее x минут }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { не поверил своим ушам } then text { отказался верить своим ушам }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { небрежно бросил } then text { бросил небрежно }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { с ума посходили } then text { чокнулись }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Вдрызг пьяный } then text { Пьяный до поросячьего визга }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { А я думал, } then text { Я полагал, }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { обаятельно улыбаясь } then text { сияя обаятельной улыбкой }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Прошу простить, } then text { Прошу прощения, }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { на секунду } then text { на одно мгновение }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { ненавидела его всеми фибрами своей души } then text { отчаяно ненавидела его }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { при мысли о том, что } then text { от осознания того факта, что }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { обращать внимание } then text { уделять внимание }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { в этот счастливый миг } then text { в это волшебное мгновение }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { нервно кашлянул } then text { кашлянул нервно }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { не заметил, как } then text { не обратил внимание, как }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { похолодало } then text { стало холодно }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { вообще ничего } then text { абсолютно ничего }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { По судам затаскаю } then text { по судам затаскаю }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { высекут хорошенько } then text { устроят хорошую порку }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { со всех ног бежал } then text { бежал что было сил }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { не замечал, что } then text { не обращал внимание, что }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { наконец заметил } then text { в этот момент заметил }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { долгие годы } then text { несколько долгих лет }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { что почем } then text { что к чему }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { едва уловимый } then text { почти неуловимый }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { еще один раз } then text { снова }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if context { Существительное:*{РОД:ЖЕН} 'подлежит' 'ликвидации' } then text { должна быть ликвидирована }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { завладел сердцами } then text { проник в сердца }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { от человека к человеку } then text { от одного человека к другому }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { возникла паника } then text { началась паника }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Сейчас бесполезно } then text { теперь бессмысленно }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { с обманчивой легкостью } then text { обманчиво легко }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { , вероятно, } then text { , судя по всему, }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Из-за указанных недостатков } then text { вследствие таких недостатков }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { чрезвычайно мало населен } then text { населен очень мало }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { свидетельство всеобщего безумия } then text { подтверждение массового помешательства }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { они отдавали себе отчет в том, что } then text { они понимали то, что }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { во многом } then text { главным образом }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { им предстояло узнать } then text { они должны узнать }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { На самом деле } then text { в действительности }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { сверкая на ярком солнце } then text { сверкая в лучах яркого солнца }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { лучился от удовольствия } then text { светился от радости }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { , разумеется,  } then text { , конечно же, }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { в этот момент } then text { в эту секунду }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { прекратившие свое существование вместе } then text { исчезнувшие вместе }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { говорила ему в лоб, что } then text { высказывала ему без обиняков, что }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { , потому что готовился } then text { , так как собирался }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { , скрытая от непрошеных глаз } then text { , недоступная постороннему взгляду, }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { замерли в ожидании. } then text { ожидающе замерли. }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { дикий вопль } then text { отчаянный крик }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { позволяла } then text { делала возможным }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Каждый год } then text { ежегодно }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { был типичным } then text { являлся обыкновенным }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { терпеть не мог } then text { не выносил }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { держать ухо востро } then text { быть начеку }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { прошептал он } then text { произнес он шопотом }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { с условием, чтобы } then text { при условии, чтобы }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Бери, бери } then text { давай бери }
 } 


 transformation(БуквЗамены) NoName
 {
  if text { никак не мог } then text { все еще не был способен }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { болтать } then text { трепать языком }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { впадал в ярость } then text { бесился }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { не придется об этом пожалеть } then text { не придется пожалеть об этом }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Это как } then text { как это }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { жалобно заскрипело } then text { заскрипело жалобно и тоскливо }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Пошел вон } then text { убирайся }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { тотчас исчез } then text { немедленно пропал }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { чрезвычайно обрадовался: } then text { ощутил чертовскую радость: }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Как-то здесь неуютно } then text { здесь слегка неуютно }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Они нас и впустили } then text { именно они впустили нас }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Отличные парни } then text { замечательные ребята }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Как я здесь оказался } then text { каким образом я очутился тут }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { и тем самым  } then text { и таким образом }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Отдыхай } then text { предавайся неге }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { он ее не видел. } then text { он не видел ее. }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Тсс-с! } then text { Тихо! }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { все увольнительные отменяются. } then text { отменяются все увольнительные. }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { в моем ухе } then text { у меня в ухе }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Короче говоря } then text { другими словами }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { окончательный довод в споре } then text { неопровержимый аргумент в дискуссии }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Что и требовалось доказать } then text { Что и следовало доказать. }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { О Боже, } then text { Господи, }
 } 
 

 transformation(БуквЗамены) NoName
 {
  if text { Картины былого } then text { воспоминания }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Ноль реакции } then text { никакой реакции }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { бесследно } then text { без следа }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { до него не дошло, } then text { он не понял, }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { мы влипли } then text { мы попали в переплет }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { толкало стремление } then text { подталкивало стремление }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { судорожно вздохнул, } then text { вздохнул судорожно, }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { и тихонько замычал } then text { и забубнил тихонько }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { тоскливо } then text { с тоской }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { присутствие духа } then text { бодрость духа }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { я не прочь подкрепиться } then text { я бы не отказался покушать }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { первая из них } then text { из них первая }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { Он покончил самоубийством } then text { Он совершил суицид }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { поплелся к } then text { медленно пошел по направлению к }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { И что случилось } then text { что произошло }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { возбужденно воскликнул } then text { вскричал с возбуждением }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { я с ним заговорил } then text { я начал с ним беседовать }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { Бросьте меня здесь } then text { оставьте меня тут }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { ненавидят меня. } then text { испытывают ко мне ненависть }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { С чего ты взял? } then text { Почему ты так решил? }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { что случилось } then text { что произошло }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { едва не упал } then text { с трудом удержался от падения }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { до крайности } then text { крайне }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { погиб от удушья } then text { задохнулся }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { рассветом } then text { восходом Солнца }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { и даром не надо } then text { не нужно даром }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { испытывал сильное удивление } then text { был сильно удивлен }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { , судя по всему,  } then text { , видимо, }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { немного подождали } then text { немного подождали }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { не сможете } then text { не способны }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { Снова наступила тишина } then text { опять стало тихо. }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { Наступила тишина. } then text { Стало тихо. }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Сзади и спереди } then text { спереди и сзади }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Мы не хотим } then text { Нам не хочется }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Теперь куда } then text { Куда теперь }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { наугад решил } then text { решил наугад }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { , растерянно озираясь, } then text { , озираясь в растеренности, }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Что получится, если } then text { Что будет, если }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { злорадно ухмыльнулся } then text { ухмыльнулся злорадно }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { время от времени } then text { от случая к случаю }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Самый простенький. } then text { максимально простой. }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Раз уж } then text { Если }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { В конце концов } then text { В итоге }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { бешеные деньги } then text { очень большие деньги }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { Иными словами } then text { иначе говоря }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { органическая часть } then text { неотъемлемая компонента }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { разжевывать очевидные факты } then text { растолковывать само собой разумеющиеся вещи }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { рано или поздно } then text { в один прекрасный момент }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Сам посуди } then text { Подумай сам }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { в той или иной форме } then text { в том или ином виде }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { вот оно что. } then text { значит так. }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { зачем вы ищете } then text { зачем вам нужно найти }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { в конце концов } then text { в итоге }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { я подумал, что } then text { мне показалось, что }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { не понадобятся } then text { не нужны }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { слегка удивившись } then text { удивившись чуть-чуть }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { уплетал за обе щеки } then text { ел с завидным аппетитом }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { удивленно переспросил } then text { переспросил с удивлением }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { в ту же секунду } then text { тотчас }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { войну на истребление. } then text { истребительную войну. }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { подобные вещи } then text { подобные явления }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Жизнь есть жизн } then text { Такова жизнь }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { уплетал за обе щеки } then text { ел с большим аппетитом }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Какое это имеет значение? } then text { Разве это важно? }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { В том-то и беда } then text { Именно в этом заключается проблема }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { есть в этом смысл? } then text { имеется ли в этом смысл? }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { требуется немного больше } then text { нужно чуть больше }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { вот только вам вряд ли удастся } then text { маловероятно, что у вас получится }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Набрав полную грудь воздуха, } then text { вздохнув полной грудью, }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { около тридцати секунд } then text { примерно тридцать секунд }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { однажды познакомился } then text { познакомился однажды }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { О да } then text { Конечно }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Боже всемогущий } then text { Господи }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if context { _НАЧ 'Почему' '?' } then context { 0 'С' 'какой' 'стати' '?' }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { сходим с ума } then text { лишаемся рассудка }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { И я так думаю } then text { И я того же мнения }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { спятили } then text { сошли с ума }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Кто это такой } then text { Это кто такой }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Прохожий какой-то } then text { Какой-то прохожий }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { с некоторым беспокойством } then text { беспокойно }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Ты намекаешь на тот факт, что } then text { Ты хочешь сказать, что }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Ты о чем, } then text { О чем ты, }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { По-моему,  } then text { Мне кажется, }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { , осмелюсь заметить, } then text { , хотелось бы сказать, }
 }
 
 
 transformation(БуквЗамены) NoName
 {
  if text { ему в голову пришла страшная мысль } then text { страшная мысль пришла в его голову }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { Вы в полной безопасности } then text { Вам ничего не угрожает }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { 'что-нибудь' более } then text { нечто более }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { не принимать близко к сердцу } then text { не воспринимать слишком серьёзно }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Обалдеть можно } then text { Можно с ума сойти }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { отчаянно } then text { в отчаянии }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { благодаря счастливой случайности } then text { совершенно случайно }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { реализовала на практике } then text { практически осуществила }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { например, чтобы } then text { чтобы, к примеру, }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { возможно, потому, что } then text { может быть из-за того, что }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { в конце концов } then text { в итоге }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { как-то раз } then text { однажды }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { убираться } then text { делать уборку }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Стало быть, } then text { Следовательно, }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Каково же было его удивление, когда } then text { Он был крайне удивлен, когда }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { понуро склонилась } then text { склонилась бессильно }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { На самом деле } then text { В действительности }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { возбужденно } then text { в возбуждении }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { мимолетно } then text { едва уловимо }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { вы не в состоянии справиться } then text { вы не можете совладать }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { Вас пригласят } then text { Вы будете приглашены }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { раздраженно } then text { с раздражением }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Откуда мне знать, } then text { Откуда я могу знать, }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { не кажется ли тебе, что } then text { не думаешь ли ты, что }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Не самое подходящее } then text { Не лучшее }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { спокойно } then text { со спокойствием }
 } 


 transformation(БуквЗамены) NoName
 {
  if text { сам того не желая } then text { без явного на то намерения }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { редко  } then text { не часто }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { были бы мертвы } then text { погибли бы }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { очень-очень } then text { крайне }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { почти неуловимо } then text { едва уловимо }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { устремил взгляд } then text { уставился }
 } 
 

 transformation(БуквЗамены) NoName
 {
  if text { слабый и безжизненный } then text { безжизненный и слабый }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { Всего лишь } then text { Только лишь }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { твердо } then text { без колебаний }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { с надрывом } then text { надрывно }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { медленно } then text { не торопясь }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { случайно } then text { по случаю }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { поспешно } then text { с поспешностью }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { не беспокойся } then text { не надо беспокоиться }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Все просто чудесно } then text { Все замечательно }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { По-моему } then text { мне кажется }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Откуда ты знаешь? } then text { Ты откуда это знаешь? }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { одновременно } then text { в одно и то же мгновение }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { восхищенно } then text { в восхищении }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { бесцельно } then text { без цели }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { слабым и безжизненным } then text { безжизненным и слабым }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Мне приказано } then text { У меня есть приказ }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { вещаем круглосуточно} then text { круглосуточно вещаем }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { немедленно } then text { без промедления }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { растерянно } then text { в растерянности }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { можете не сомневаться } then text { не сомневайтесь }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { одновременно } then text { в то же самое время }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { обиженно } then text { с обидой }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { страдальчески } then text { со страданием }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { спятите } then text { сойдете с ума }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { напряженно } then text { с напряжением }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { предостерегающе } then text { с предостережением }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { нетерпеливо } then text { с нетерпением }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { язвительно } then text { с язвительностью }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { , следовательно,  } then text { , таким образом, }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Медленно } then text { без спешки }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { еще омерзительнее } then text { еще более омерзительно }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Нерешительно } then text { в нерешительности }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { с самым беззаботным видом } then text { совершенно беззаботно }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Как мило, что } then text { здорово, что }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { не дал себя перещеголять } then text { не позволил переплюнуть себя }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { небрежно } then text { с небрежностью }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { вздрогнув от удивления } then text { удивленно вздрогнув }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { возмущенно } then text { с возмущением }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { холодно отрезал } then text { с холодностью отрезал }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { действительно } then text { без сомнений }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { беззвучно } then text { без единого звука }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Ей очень хотелось знать } then text { Она хотела бы знать }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { в этом мире ему не место } then text { ему не место в этом мире }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { страшно вымотался } then text { крайне устал }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { не сомкнув глаз } then text { не вздремнув }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Сейчас я тебе подскажу } then text { Сейчас я подскажу тебе }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { восторженно } then text { с энтузиазмом }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { торжественно } then text { с торжеством }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { сказочно разбогатели } then text { обогатились сказочно }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { в конце концов } then text { в итоге }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { впала в крайнюю нищету. } then text { стала нищей. }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Сгинула в небытие } then text { исчезла }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { отчаянно } then text { в отчаянии }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { вполголоса } then text { полушепотом }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { я не возьмусь отличить } then text { я не могу отличить }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Между прочим, } then text { кстати говоря, }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { во внезапно } then text { в неожиданно }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { от возбуждения дрожал } then text { возбужденно дрожал }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { перед сказочно красивой } then text { перед красивейшей }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { самый бывалый } then text { опытнейший }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { иронично } then text { с иронией }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { почувствовал волнение } then text { заволновался }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { , потребовалось } then text { , было нужно }
 } 
 

 transformation(БуквЗамены) NoName
 {
  if text { на полушаге застыла в воздухе } then text { застыла в воздухе на полушаге }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { "что-нибудь" не то сказал } then text { сказал что-то не то }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { В таком случае } then text { Тогда }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Даже если предположить, что } then text { Даже при условии, что }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { ни капли не верю } then text { совсем не верю }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { чего ради } then text { зачем }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { понятия не имеет } then text { не понимает }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Чушь собачья } then text { Чепуха }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { приносит свои извинения. } then text { просит извинить. }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { при первой возможности } then text { как только это станет возможно }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { Время от времени } then text { иногда }
 } 
 transformation(БуквЗамены) NoName
 {
  if text { что эти странные символы значат } then text { что означают эти странные символы }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { свихнулся } then text { сошел с ума }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Такую возможность я не исключаю } then text { Я не исключаю такую возможность }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { с тревогой и состраданием } then text { с состраданием и тревогой }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { дай объяснить } then text { позволь объяснить }
 } 
 transformation(БуквЗамены) NoName
 {
  if text { Тогда стал я } then text { Тогда я начал }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { надоело до чертиков } then text { полностью надоело }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { В эту секунду } then text { В это мгновение }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { наугад ткнул } then text { ткнул наугад }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Надо заметить, что } then text { Следует сказать, что }
 } 
 transformation(БуквЗамены) NoName
 {
  if text { в конце концов } then text { в итоге }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { делал вид, что } then text { притворялся, что }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { твердил как заведенный, что } then text { упрямо твердил, что }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { ежегодно } then text { каждый год }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { ежедневно } then text { каждый день }
 } 
 transformation(БуквЗамены) NoName
 {
  if text { еженощно } then text { каждую ночь }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { ежемесячно } then text { каждый месяц }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { еженедельно } then text { каждую неделю }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { отправился прогуляться } then text { пошел проветриться }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Это все ерунда } then text { Все это чепуха }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Терпеть не могу } then text { Не терплю }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Скажи-ка } then text { Ну-ка скажи }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { вы напугали меня } then text { вы меня испугали }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Не тревожься } then text { Не беспокойся }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { бросает несколько замечаний } then text { делает пару замечаний }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { недоверчиво } then text { с недоверием }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Увлекательнейшее } then text { Крайне увлекательное }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { с тоской } then text { грустно }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { горько бормоча } then text { бормоча с огорчением }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { неоднократно } then text { много раз }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { ошибочно } then text { по ошибке }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { совершенно ошибочно } then text { абсолютно неправильно }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { В действительности же } then text { на самом же деле }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { испуганно } then text { в испуге }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { стремительно } then text { крайне быстро }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { в ужасе } then text { от ужаса }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { стала уменьшаться } then text { начала падать }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { скучно и заурядно } then text { заурядно и скучно }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { с до боли знакомыми } then text { со знакомыми до боли }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { Лишившись дара речи, } then text { Не в силах промолвить ни слова, }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { сойду с ума } then text { свихнусь }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text { тихо проронил } then text { чуть слышно произнес }
 } 

 transformation(БуквЗамены) NoName
 {
  if text { ничего не произошло } then text { ничего не случилось }
 } 
 
 
 transformation(БуквЗамены) NoName
 {
  if text { которые нужно  } then text { которые требуется }
 } 

 
 transformation(БуквЗамены) NoName
 {
  if text { Почему я должен слушать } then text { почему мне следует слушать }
 } 

/* 
 transformation(БуквЗамены) NoName
 {
  if text {  } then text {  }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text {  } then text {  }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text {  } then text {  }
 } 
 
 transformation(БуквЗамены) NoName
 {
  if text {  } then text {  }
 } 
 
 
 /* */ 
 
}
