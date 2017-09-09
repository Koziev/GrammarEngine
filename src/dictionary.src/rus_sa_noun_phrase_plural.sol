// Восходяще-нисходящая сборка союзного именного паттерна,
// который выполеяет роль существительного в множественном
// числе

// +++++++++++++++++++++++++++++++++++++++++++++

patterns ГоловаГруппыСущ_МНОЖ export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }

pattern ГоловаГруппыСущ_МНОЖ
{
 ГоловаГруппыСущ : export{ РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }
}

pattern ГоловаГруппыСущ_МНОЖ export { РОД ПАДЕЖ ЧИСЛО (ОДУШ) node:root_node }
{
 ГруппаМест : export { РОД ПАДЕЖ ЧИСЛО node:root_node }
}



// +++++++++++++++++++++++++++++++++++++++++++++

patterns ХвостГруппыСущ_МНОЖ export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }

pattern ХвостГруппыСущ_МНОЖ
{
 ХвостГруппыСущ : export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }
}

pattern ХвостГруппыСущ_МНОЖ export { РОД ПАДЕЖ ЧИСЛО (ОДУШ) node:root_node }
{
 ГруппаМест : export { РОД ПАДЕЖ ЧИСЛО node:root_node }
}

// ---------------------------------------------------

// Признак KEYFEATURE_REQUIRED:0 => был присоединен второй и т.д. элемент
// Признак KEYFEATURE_DESIRABLE:1 => в состав фразы вошел союз
patterns МножСущВосх0 export { KEYFEATURE_DESIRABLE KEYFEATURE_REQUIRED РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }

pattern МножСущВосх0
{
 noun=ГоловаГруппыСущ_МНОЖ:export{ KEYFEATURE_DESIRABLE:0 KEYFEATURE_REQUIRED:1 РОД ПАДЕЖ ЧИСЛО:МН ОДУШ node:root_node }
}


// ---------------------------------------------------------

// Признак KEYFEATURE_DETECTED:1 есть перечисление или союзный паттерн

patterns МножСущВосх { bottomup } export { KEYFEATURE_DETECTED KEYFEATURE_REQUIRED KEYFEATURE_DESIRABLE РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }

pattern МножСущВосх
{
 МножСущВосх0:export{ KEYFEATURE_DETECTED:0 KEYFEATURE_REQUIRED:1 KEYFEATURE_DESIRABLE:0 РОД ПАДЕЖ ЧИСЛО:МН ОДУШ node:root_node }
}

// Кошка, собака, воробей жили на дереве
// ^^^^^^^^^^^^^
// Мама, папа, бабушка и дедушка будут ругаться
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern МножСущВосх
{
 n1=МножСущВосх:export{ РОД ПАДЕЖ ЧИСЛО:МН ОДУШ node:root_node KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:0 }
 comma=',' : export { KEYFEATURE_DETECTED:1 }
 n2=ХвостГруппыСущ_МНОЖ{ =n1:Падеж }
}
: links { n1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>n2 }



// Мама и папа будут ругаться
// ^^^^^^^^^^^
pattern МножСущВосх
{
 n1=МножСущВосх:export { РОД ПАДЕЖ ОДУШ ЧИСЛО:МН KEYFEATURE_REQUIRED:0 node:root_node }
 conj=ЛогичСоюз : export { KEYFEATURE_DETECTED:1 KEYFEATURE_DESIRABLE:1 }
 n2=ХвостГруппыСущ_МНОЖ{ =n1:ПАДЕЖ }
}
: links { n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2 }
: ngrams { 2 }

// ---------------------------------------------------

patterns МножСущФинал export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }


// В состав группы вошел хотя бы один союз:
//
// Кошка и собака, воробей и голубь жили в домике
// ^^^^^^^^^^^^^^
pattern МножСущФинал
{
 МножСущВосх{ ~НеЭлементСоюзнГруппы KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:1 } : export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }
}

// В состав группы не вошел ни один союз:
//
// Кошка, собака, воробей жили на дереве
// ^^^^^^^^^^^^^
pattern МножСущФинал
{
 МножСущВосх{ ~НеЭлементСоюзнГруппы KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:0 } : export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }
} : ngrams { -1 }



// ---------------------------------------------------

patterns ИменнаяГруппа_МНОЖ export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }

pattern ИменнаяГруппа_МНОЖ
{
 МножСущФинал:export{ РОД ПАДЕЖ ЧИСЛО:МН ОДУШ node:root_node }
}

// И радость, и печаль смешались в одно целое...
// ^^^^^^^^^^^^^^^^^^^
pattern ИменнаяГруппа_МНОЖ
{
 conj1=ЛогичСоюз2
 n1=МножСущВосх:export{ РОД ПАДЕЖ ЧИСЛО:МН ОДУШ node:root_node }
 comma=','
 conj2=ЛогичСоюз2
 n2=МножСущВосх{ =n1:Падеж }
} : links
{
 n1.{
     <PREFIX_CONJUNCTION>conj1
     <RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj2.<NEXT_COLLOCATION_ITEM>n2
    }
} 



// -----------------------------------------------------


// Так рыцарь, так и слуга стояли в грязи
// ^^^^^^^^^^^^^^^^^^^^^^^
pattern ИменнаяГруппа_МНОЖ
{ 
 w1=союз:как{}
 noun=МножСущВосх:export{ РОД ПАДЕЖ ЧИСЛО:МН ОДУШ node:root_node }
 comma=','
 w2=союз:так{}
 w3=союз:и{}
 n2=ИменнаяГруппа_МНОЖ{ =Noun:Падеж }
} : links
{
 noun.{
       <PREFIX_CONJUNCTION>w1
       <RIGHT_LOGIC_ITEM>comma.
       <NEXT_COLLOCATION_ITEM>w2.
        <NEXT_COLLOCATION_ITEM>w3.
         <NEXT_COLLOCATION_ITEM>n2
      }
}
: ngrams { 4 }



// Это сделал не он, а его помощник
pattern ИменнаяГруппа_МНОЖ
{ 
 n=частица:не{}
 noun=МножСущВосх:export{ РОД ПАДЕЖ ЧИСЛО:МН ОДУШ node:root_node }
 comma=','
 w2=СоединДляПрилаг
 n2=ИменнаяГруппа_МНОЖ{ =Noun:Падеж }
} : links
{
 noun.{
       <NEGATION_PARTICLE>n
       <RIGHT_LOGIC_ITEM>comma.
        <NEXT_COLLOCATION_ITEM>w2.
         <NEXT_COLLOCATION_ITEM>n2
      }
}
: ngrams { 4 }


// И воробей, и синица, и снегирь прилетали сюда
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ИменнаяГруппа_МНОЖ
{ 
 conj1=ЛогичСоюз2
 noun=МножСущВосх:export{ РОД ПАДЕЖ ЧИСЛО:МН ОДУШ node:root_node }
 comma=','
 conj2=ЛогичСоюз2
 n2=ИменнаяГруппа_МНОЖ{ =Noun:Падеж }
} : links
{
 noun.{
       <PREFIX_CONJUNCTION>conj1
       <RIGHT_LOGIC_ITEM>comma.
        <NEXT_COLLOCATION_ITEM>conj2.
         <NEXT_COLLOCATION_ITEM>n2
      }
}
: ngrams { 1 }




pattern ГруппаСущ4
{
 n=ИменнаяГруппа_МНОЖ : export { РОД ПАДЕЖ ЧИСЛО:МН ОДУШ node:root_node }
} 
: ngrams { ВалентностьСущ(n) }


// отдай это усталым дяде и тете
//           ^^^^^^^^^^^^^^^^^^^
pattern ГруппаСущ4
{
 a=ГруппаПрил2{ ЧИСЛО:МН }
 n=ИменнаяГруппа_МНОЖ{ =a:ПАДЕЖ =a:ОДУШ } : export { РОД ПАДЕЖ ЧИСЛО:МН ОДУШ node:root_node }
}
: links { n.<ATTRIBUTE>a }
: ngrams
{
 -1
 ВалентностьСущ(n)
}


// назвать поименно мастеров и гроссмейстера, участвовавших в том матче
//                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ГруппаСущ4
{
 n=ИменнаяГруппа_МНОЖ:export{ РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }
 p=ПравПричОборот{ =n:ПАДЕЖ ЧИСЛО:МН }
}
: links
{
 n.<ADJ_PARTICIPLE>p
}
: ngrams
{
 -1
 ВалентностьСущ(n)
}

// ------------------------------------------------

pattern СущСПредложДоп
{
 n1=ГруппаСущ1:export{ РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }
 n2=ИменнаяГруппа_МНОЖ{ ПАДЕЖ:РОД }
} : links
{
 n1.<RIGHT_GENITIVE_OBJECT>n2
}




/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// -------------------------------

// Имитация отдельных нейронов, выполняющих эти элементарные функции, объединение их в единую работающую систему составляет сверхзадачу построения искусственного интеллекта.
pattern ИменнаяГруппа_МНОЖ
{
 noun=ЛогичЭлементСущ:export{ РОД ПАДЕЖ ЧИСЛО:МН ОДУШ node:root_node }
 comma=','
 n2=ЛогичЭлементСущ{ =Noun:Падеж }
}
: ngrams { -1 }
: links { noun.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>n2 }

// История математических терминов, понятий, обозначений.
pattern ИменнаяГруппа_МНОЖ
{
 noun=ЛогичЭлементСущ:export{ РОД ПАДЕЖ ЧИСЛО:МН ОДУШ node:root_node }
 comma1=','
 n2=ЛогичЭлементСущ{ =Noun:Падеж }
 comma2=','
 n3=ЛогичЭлементСущ{ =Noun:Падеж }
}
: ngrams { -1 }
: links
{
 noun.<RIGHT_LOGIC_ITEM>comma1.
       <NEXT_COLLOCATION_ITEM>n2.
        <RIGHT_LOGIC_ITEM>comma2.
         <NEXT_COLLOCATION_ITEM>n3
}






// Антонио и Мэри
pattern ИменнаяГруппа_МНОЖ
{
 n1=ЛогичЭлементСущ_МНОЖ:export { РОД ПАДЕЖ ОДУШ ЧИСЛО:МН node:root_node }
 conj=ЛогичСоюз
 n2=ЛогичЭлементСущ_МНОЖ{ =n1:ПАДЕЖ }
} : links
{ n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2 }


// Лиса, зайчишка и косолапый мишка жили в избушке
pattern ИменнаяГруппа_МНОЖ
{
 n1=ЛогичЭлементСущ_МНОЖ:export { РОД ПАДЕЖ ОДУШ ЧИСЛО:МН node:root_node }
 comma=','
 n2=ЛогичЭлементСущ_МНОЖ{ =n1:ПАДЕЖ }
 conj=союз:и{}
 n3=ЛогичЭлементСущ_МНОЖ{ =n1:ПАДЕЖ }
} : links
{
 n1.<RIGHT_LOGIC_ITEM>comma.
     <NEXT_COLLOCATION_ITEM>n2.
      <RIGHT_LOGIC_ITEM>conj.
       <NEXT_COLLOCATION_ITEM>n3
}

// папа, мама, брат и я любим петь
pattern ИменнаяГруппа_МНОЖ
{
 n1=ЛогичЭлементСущ_МНОЖ:export { РОД ПАДЕЖ ОДУШ ЧИСЛО:МН node:root_node }
 comma=','
 n2=ЛогичЭлементСущ_МНОЖ{ =n1:ПАДЕЖ }
 comma2=','
 n3=ЛогичЭлементСущ_МНОЖ{ =n1:ПАДЕЖ }
 conj=союз:и{}
 n4=ЛогичЭлементСущ_МНОЖ{ =n1:ПАДЕЖ }
} : links
{
 n1.<RIGHT_LOGIC_ITEM>comma.
     <NEXT_COLLOCATION_ITEM>n2.
      <RIGHT_LOGIC_ITEM>comma2.
       <NEXT_COLLOCATION_ITEM>n3.
        <RIGHT_LOGIC_ITEM>conj.
         <NEXT_COLLOCATION_ITEM>n4
}

// Канарейка и попугай, кошка и собака живут в квартире
pattern ИменнаяГруппа_МНОЖ
{
 n1=ЛогичЭлементСущ_МНОЖ:export { РОД ПАДЕЖ ОДУШ ЧИСЛО:МН node:root_node }
 conj1=союз:и{}
 n2=ЛогичЭлементСущ_МНОЖ{ =n1:ПАДЕЖ }
 comma=','
 n3=ЛогичЭлементСущ_МНОЖ{ =n1:ПАДЕЖ }
 conj2=союз:и{}
 n4=ЛогичЭлементСущ_МНОЖ{ =n1:ПАДЕЖ }
} : links
{
 n1.<RIGHT_LOGIC_ITEM>conj1.
     <NEXT_COLLOCATION_ITEM>n2.
      <RIGHT_LOGIC_ITEM>comma.
       <NEXT_COLLOCATION_ITEM>n3.
        <RIGHT_LOGIC_ITEM>conj2.
         <NEXT_COLLOCATION_ITEM>n4
}
*/


