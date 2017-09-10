wordentry_set MonthName=
{
 eng_noun:january{},
 eng_noun:february{},
 eng_noun:march{},
 eng_noun:april{},
 eng_noun:may{},
 eng_noun:june{},
 eng_noun:july{},
 eng_noun:august{},
 eng_noun:september{},
 eng_noun:october{},
 eng_noun:november{},
 eng_noun:december{}
}

wordentry_set SpecialVerbs = {
                              eng_beverb:be{},
                              eng_auxverb:will{},
                              eng_beverb:be_not{},
                              eng_auxverb:WILL_NOT{},
                              eng_auxverb:can{},
                              eng_auxverb:cannot{},
                              eng_auxverb:must{},
                              eng_auxverb:shall{},
                              eng_auxverb:would{},
                              eng_auxverb:would_not{},
                              eng_auxverb:should{},
                              eng_auxverb:should_not{},
                              eng_verb:"don't"{},
                              eng_verb:"haven't"{}
                             }


wordentry_set AdvMovement = {
                             eng_adverb:fastly{},
                             eng_adverb:quickly{}
                            }

wordentry_set AdvNotForVerb = {
                               eng_adverb:very{},
                               eng_adverb:too{}
                              }


wordentry_set CanBeAdverbsAfterDo=
{
 eng_adverb:like{}
}
                              
                              
wordentry_set PP_FollowedByInf=
{
 eng_verb:train{}, // I am trained to understand the risks
 eng_verb:force{} // He is forced to do it
}


wordentry_set OpeningQuote = ПУНКТУАТОР:{ '"', '«', '„', '“', '‹', '\'' }
wordentry_set ClosingQuote = ПУНКТУАТОР:{ '"', '«', '„', '“', '‹', '\'' }


wordentry_set EngModalVerb0=
{
 ENG_AUXVERB:must{},
 ENG_AUXVERB:can{},
 ENG_AUXVERB:shall{},
 ENG_AUXVERB:should{},
 ENG_AUXVERB:may{},
 ENG_AUXVERB:should_not{},
 ENG_AUXVERB:cannot{},
 ENG_AUXVERB:must_not{},
 ENG_AUXVERB:would{},
 ENG_AUXVERB:would_not{},
 ENG_AUXVERB:will{},
 ENG_AUXVERB:will_not{},
 ENG_AUXVERB:OUGHT{},
 ENG_AUXVERB:NEED{} // It need not be a primitive melt.
}


// ��������� ���������� ������� ���� ������������ ������� NOT ������, ��� ���������:
// Generated results need not exist as files.
//                   ^^^^^^^^
wordentry_set EngVerbNot0=
{
 eng_verb:need{},
 eng_verb:dare{}
}


wordentry_set TimeWord=eng_noun:{
 decade, // The Haitian Revolution lasted nearly a decade;
 century,
 year,
 month,
 day,
 night,
 time,
 morning,
 evening, week, hour, minute, second, summer, winter, autumn
} 

// Эти токены служат естественным ограничением клаузы слева,
wordentry_set LeftClauseBoundary=
{
 ПУНКТУАТОР:","{},
 ПУНКТУАТОР:"."{},
 ПУНКТУАТОР:":"{},
 ПУНКТУАТОР:!{},
 ПУНКТУАТОР:"?"{},
 ПУНКТУАТОР:"-"{},
 ПУНКТУАТОР:";"{},
 BETH:BEGIN{}
}

wordentry_set NumberNoun=
{
 eng_noun:hundred{},
 eng_noun:thousand{},
 eng_noun:million{},
 eng_noun:billion{},
 eng_noun:trillion{}
}
