// +++++++++++++++++++++++++++++++++++++++++++

// Считаем вводные словосочетания таким же компонентом предиката, как
// подлежащее или обстоятельство.


pattern МодальнСловосочет
{
 МодальСловосочет0 : export { node:root_node }
}


// Должно быть, проверял себя.
// ^^^^^^^^^^^
pattern МодальнСловосочет
{
 @probe_left(ЛевыйОграничительОборота)
 w1='должно'{ class:прилагательное } : export { node:root_node }
 w2=инфинитив:быть{}
 @noshift(',')
}
: links { w1.<NEXT_COLLOCATION_ITEM>w2 }


// Цепочка ", что ли" в роли вводного:
//
// Голову, что ли, потерял со страху?
//         ^^^^^^
// Не понимаете, что ли?
//               ^^^^^^
pattern МодальнСловосочет
{
 @probe_left(',')
 adv=наречие:что{} : export { node:root_node }
 p=ЧастицаЛи
 @noshift(ПУНКТУАТОР:*{})
}
: links { adv.<POSTFIX_PARTICLE>p }
: ngrams { 13 }


// -------------------------------------------------------

patterns ГруппаВводныхСлов export { node:root_node }

// Насчет телефона она, конечно, сказала неправду.
//                      ^^^^^^^
pattern ГруппаВводныхСлов
{
 a=вводное:*{} : export { node:root_node }
}

// По-моему и по-твоему, получилось неплохо.
// ^^^^^^^^^^^^^^^^^^^^^
pattern ГруппаВводныхСлов
{
 a=вводное:*{} : export { node:root_node }
 conj=ЛогичСоюз
 b=вводное:*{}
} : links { a.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>b }

// -------------------------------------------------------

patterns ВводнАктант export { node:root_node }


// Получилось, по-моему, неплохо.
//           ^^^^^^^^^^^
pattern ВводнАктант
{
 comma1=','
 z=ГруппаВводныхСлов : export { node:root_node }
 @noshift(ПравыйОграничительОборота)
 comma2=@coalesce(',')
}
: links
{
 z.{
    <PUNCTUATION>comma1
    ~<PUNCTUATION>comma2
   }
}
: ngrams { 1 }


// Но Манцев, казалось, совсем сошел с ума...
//          ^^^^^^^^^^^
pattern ВводнАктант
{
 comma1=','
 z=МодальнСловосочет : export { node:root_node }
 @noshift(ПравыйОграничительОборота)
 comma2=@coalesce(',')
}
: links
{
 z.{
    <PUNCTUATION>comma1
    ~<PUNCTUATION>comma2
   }
}
: ngrams { -2 }

// Ты просто... не совсем обычный.
//          ^^^
pattern ВводнАктант
{
 '...' : export { node:root_node }
} : ngrams { -5 }


// Плавать не умею, боюсь - и все тут.
//                        ^^^^^^^^^^^
pattern ВводнАктант
{
 t='-' : export { node:root_node }
 w1=союз:и{}
 w2=местоим_сущ:все{}
 w3=наречие:тут{}
 @noshift(ПравыйОграничительОборота)
}
: links
{
 t.<NEXT_COLLOCATION_ITEM>w1.<NEXT_COLLOCATION_ITEM>w2.<NEXT_COLLOCATION_ITEM>w3
}
: ngrams { -5 }



// А ты небось домой сейчас пойдешь?
//      ^^^^^^
pattern ВводнАктант
{
 ВВОДНОЕ:*{} : export { node:root_node }
}
: ngrams { -5 }
