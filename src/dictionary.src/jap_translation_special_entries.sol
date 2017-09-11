automat sg
{
 // Несколько специальных словарных статей, которые облегчают перевод сложных конструкций.
 entry THEREIS : JAP_VERB { JAP_FORM:ROMAJI }
 entry j_POSSIBLE : JAP_ADVERB { JAP_FORM:ROMAJI }

 entry j_MUST : JAP_VERB { JAP_FORM:ROMAJI }

 entry j_CAN : JAP_VERB { JAP_FORM:ROMAJI }

 entry j_GOINGTO : JAP_VERB { JAP_FORM:ROMAJI }
 entry j_WANNA : JAP_VERB { JAP_FORM:ROMAJI }

 link JAP_VERB:j_GOINGTO{} <to_russian> ИНФИНИТИВ:собираться{}
 link JAP_VERB:j_WANNA{} <to_russian> ИНФИНИТИВ:хотеть{}

 entry j_ADJ : JAP_ADJECTIVE { JAP_FORM:ROMAJI }
 entry j_VERB: JAP_VERB { JAP_FORM:ROMAJI }
 entry j_ADVERB : JAP_ADVERB { JAP_FORM:ROMAJI }
 entry j_NOUN: JAP_NOUN { JAP_FORM:ROMAJI }

 entry j_in_language : JAP_NOUN { JAP_FORM:ROMAJI }

}
