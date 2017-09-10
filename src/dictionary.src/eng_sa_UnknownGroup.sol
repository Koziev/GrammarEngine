// для разбора неграмматических конструкций или конструкций с неизвестным нам синтаксисом
// будем брать цепочки слов в запятых и присоединять их к глаголам с большим штрафом.

// -----------------------------------------------------

wordentry_set WallMarkers = { beth:begin{}, beth:end{} }
pattern AnyWord
{
 *:*{ ~WallMarkers } : export { node:root_node }
}

// -----------------------------------------------------

patterns V_Clause export { node:root_node }
 
// вспомогательные нетерминалы

// Затравки
patterns UnknownGroupHead { language=English bottomup } export { node:root_node }

/*
pattern UnknownGroupHead
{
 AnyWord : export { node:root_node }
} : ngrams { -10 }
*/

pattern UnknownGroupHead
{
 unknownentries:*{} : export { node:root_node }
} : ngrams { -15 }

/*
pattern UnknownGroupHead
{
 PreposPhrase : export { node:root_node }
} : ngrams { -8 }

pattern UnknownGroupHead
{
 AdjGroup : export { node:root_node }
} : ngrams { -7 }

pattern UnknownGroupHead
{
 NounGroup : export { node:root_node }
} : ngrams { -6 }

pattern UnknownGroupHead
{
 V_Clause : export { node:root_node }
} : ngrams { -5 }


// Предпочитаем цепочки, начинающиеся с запятой.
pattern UnknownGroupHead
{
 comma=',' : export { node:root_node }
 t=UnknownGroupHead
}
: links { comma.<NEXT_COLLOCATION_ITEM>t }
: ngrams { 1 }
*/

// восходящая сборка
patterns UnknownGroupUp { language=English bottomup } export { node:root_node }

pattern UnknownGroupUp
{
 UnknownGroupHead : export { node:root_node }
}

/*
pattern UnknownGroupUp
{
 h=UnknownGroupUp : export { node:root_node }
 t=UnknownGroupHead
} : links { h.<NEXT_COLLOCATION_ITEM>t }
*/

// -----------------------------------------------------

pattern UnknownRightGroup
{
 h=UnknownGroupUp : export { node:root_node }
 t=пунктуатор:,{}
} : links { h.<PUNCTUATION>t }

pattern UnknownRightGroup
{
 h=UnknownGroupUp : export { node:root_node }
 t=пунктуатор:*{}
}
: links { h.<PUNCTUATION>t }
: ngrams { -5 }

pattern UnknownRightGroup
{
 UnknownGroupUp : export { node:root_node }
 @noshift(BETH:END{})
}


// Freebase aimed to create a global resource that allowed people (and machines) to access common information more effectively.
//                                                                ^^^^^^^^^^^^^^
pattern UnknownRightGroup
{
 o='('
 h=UnknownGroupUp : export { node:root_node }
 c=')'
}
: links { h.{ <PUNCTUATION>o <PUNCTUATION>c } }



// -----------------------------------------------------------

patterns UnknownLeftGroup export { node:root_node }

pattern UnknownLeftGroup
{
 unknownentries:*{} /*AnyWord*/ : export { node:root_node }
} : ngrams { -15 }


pattern UnknownLeftGroup
{
 o='('
 h=UnknownGroupUp : export { node:root_node }
 c=')'
}
: links { h.{ <PUNCTUATION>o <PUNCTUATION>c } }


