// -----------------------------------------------------------------------------
// File SPECIALS.SOL
//
// (c) by Koziev Elijah
//
// Content:
// Часть Лексикона: специальные символы пунктуации.
// -----------------------------------------------------------------------------
//
// CD->30.01.1997
// LC->26.01.2016
// --------------

automat gg
{
 class PUNCTUATOR
 class ORNAMENTOR



 entry  ,    : PUNCTUATOR { alphabet Neutral }
 entry  .    : PUNCTUATOR { alphabet Neutral }
 entry  !    : PUNCTUATOR { alphabet Neutral }
 entry  ?    : PUNCTUATOR { alphabet Neutral }
 entry  :    : PUNCTUATOR { alphabet Neutral }
 entry  — : PUNCTUATOR { alphabet Neutral }
 entry  – : PUNCTUATOR { alphabet Neutral }
 entry  ­ : PUNCTUATOR { alphabet Neutral }
 entry  ;    : PUNCTUATOR { alphabet Neutral }
        -    : PUNCTUATOR { alphabet Neutral }
        (    : PUNCTUATOR { alphabet Neutral }
        )    : PUNCTUATOR { alphabet Neutral }
        [    : PUNCTUATOR { alphabet Neutral }
        ]    : PUNCTUATOR { alphabet Neutral }
 entry "{"   : PUNCTUATOR { alphabet Neutral }
 entry "}"   : PUNCTUATOR { alphabet Neutral }
        <    : PUNCTUATOR { alphabet Neutral }
        >    : PUNCTUATOR { alphabet Neutral }
        +    : PUNCTUATOR { alphabet Neutral }
        =    : PUNCTUATOR { alphabet Neutral }
        *    : PUNCTUATOR { alphabet Neutral }
        &    : PUNCTUATOR { alphabet Neutral }
        %    : PUNCTUATOR { alphabet Neutral }
        $    : PUNCTUATOR { alphabet Neutral }
        #    : PUNCTUATOR { alphabet Neutral }
        @    : PUNCTUATOR { alphabet Neutral }
        ~    : PUNCTUATOR { alphabet Neutral }
        `    : PUNCTUATOR { alphabet Neutral }
        |    : PUNCTUATOR { alphabet Neutral }
        \    : PUNCTUATOR { alphabet Neutral }
        "\"" : PUNCTUATOR { alphabet Neutral }
        "'"  : PUNCTUATOR { alphabet Neutral }
        /    : PUNCTUATOR { alphabet Neutral }
        ^    : ORNAMENTOR { alphabet Neutral }

        _ : ORNAMENTOR { alphabet Neutral }

        "«" : PUNCTUATOR { alphabet Neutral }
        "»" : PUNCTUATOR { alphabet Neutral }
 "…" : PUNCTUATOR { alphabet Neutral }
 
 "“" : PUNCTUATOR { alphabet Neutral }
 "”" : PUNCTUATOR { alphabet Neutral }
 "„" : PUNCTUATOR { alphabet Neutral }
 "‹" : PUNCTUATOR { alphabet Neutral }
 "›" : PUNCTUATOR { alphabet Neutral }
 
}
