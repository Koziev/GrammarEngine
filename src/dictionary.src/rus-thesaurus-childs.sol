// CD->13.10.2010
// LC->08.10.2011

#define ParentOf( Parent, Child ) \
#begin
 extern entry Child : Существительное
 extern entry Parent : Существительное
 link СУЩЕСТВИТЕЛЬНОЕ:Child { одуш:одуш } <child_of> Существительное:Parent { одуш:одуш }
 link СУЩЕСТВИТЕЛЬНОЕ:Parent { одуш:одуш } <parent_of> Существительное:Child { одуш:одуш }
#end

automat sg
{
 link СУЩЕСТВИТЕЛЬНОЕ:лев{ CharCasing:Lower } <parent_of> Существительное:львёнок{}
 link СУЩЕСТВИТЕЛЬНОЕ:львёнок{} <child_of> Существительное:лев{ CharCasing:Lower }

 ParentOf( повар, поварёнок )
 ParentOf( повариха, поварёнок )
 ParentOf( олень, оленёнок )
 ParentOf( лягушка, лягушонок )
 ParentOf( крыса, крысёнок )
 ParentOf( белка, бельчонок )
 ParentOf( львица, львёнок )
 ParentOf( негр, негритёнок )
 ParentOf( негритянка, негритёнок )
 ParentOf( цыган, цыганёнок )
 ParentOf( цыганка, цыганёнок )
 ParentOf( китаец, китайчонок )
 ParentOf( китаянка, китайчонок )
 ParentOf( заяц, зайчонок )
 ParentOf( зайчиха, зайчонок )
 ParentOf( тигр, тигрёнок )
 ParentOf( тигрица, тигрёнок )
 ParentOf( лис, лисёнок )
 ParentOf( лиса, лисёнок )
 ParentOf( кот, котёнок )
 ParentOf( кошка, котёнок )
 ParentOf( лошадь, жеребёнок )
 ParentOf( собака, щенок )
 ParentOf( птица, птенец )
 ParentOf( змея, змееныш )
 ParentOf( крыса, крысёныш )
 ParentOf( паук, паучонок )
 ParentOf( слон, слонёнок )
 ParentOf( слониха, слонёнок )
 ParentOf( перепел, перепелёнок )
 ParentOf( перепелица, перепелёнок )
 ParentOf( перепелка, перепелёнок )
 ParentOf( галка, галчонок )
 ParentOf( дельфин, дельфинёнок )
 ParentOf( домовой, домовёнок )
 ParentOf( лось, лосёнок )
 ParentOf( рысь, рысёнок )
 ParentOf( сова, совёнок )
 ParentOf( татарин, татарчонок )
 ParentOf( чёрт, чертёнок )

 ParentOf( бобр, бобренок )
 ParentOf( аист, аистенок )
 ParentOf( буйвол, буйволенок )
 ParentOf( верблюд, верблюжонок )
 ParentOf( глухарь, глухаренок )
 ParentOf( голубь, голубенок )
 ParentOf( журавль, журавленок )
 ParentOf( зубр, зубренок )
 ParentOf( кабан, кабаненок )
 ParentOf( кенгуру, кенгуренок )
 ParentOf( крокодил, крокодиленок )
 ParentOf( лебедь, лебеденок )
 ParentOf( осел, осленок )
 ParentOf( скворец, скворчонок )
 ParentOf( соболь, соболенок )
 ParentOf( жид, жиденок )
 ParentOf( сокол, соколенок )
 ParentOf( морж, моржонок )

 ParentOf( кит, китёнок )
 ParentOf( пингвин, пингвинёнок )
 ParentOf( страус, страусёнок )
 ParentOf( турок, турчонок )
 ParentOf( тюлень, тюленёнок )
 ParentOf( фазан, фазанёнок )
 ParentOf( ястреб, ястребёнок )
 ParentOf( ящерица, ящерёнок )

/*
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
/**/
}
