// 21.06.2011 добавлены теги СтильРечи и РазмерСила
// 28.05.2012 - добавлен атрибут OMONYM_RESOLUTION для разрешения омонимии в тезаурусе в случаях, когда другие способы неприменимы.

automat sg
{
 // Омонимы типа lie(лежать) - lie(глать), в тезаурусе
 // при задании связей можно отличать с помощью такой пометки.
 enum OMONYM_RESOLUTION { 1 2 3 }

 enum PERSON as PERSON_xx      { 1 as PERSON_1_xx 2 as PERSON_2_xx 3 as PERSON_3_xx }
 enum NUMBER as NUMBER_xx      { SINGLE as SINGLE_xx PLURAL as PLURAL_xx }
 enum GENDER as GENDER_xx      { MASCULINE as MASCULINE_xx FEMININE as FEMININE_xx NEUTRAL as NEUTRAL_xx }

 AuxFormTypes = { stress yo transcription espeak }
 
 enum СтильРечи as SPEECH_STYLE_xx
 { Нейтр /*собака*/ Груб /*шавка*/ Разговорн /*псина*/ }

 enum РазмерСила as STRENGTH_xx
 {
  Нейтр   // рука
  Уменьш  // ручка
  Усил    // ручища
  Частичн // полуоглохший
 }

 
 // ---------------------------
 // Рабочие флаги для парсеров
 // ---------------------------

 enum AUX_VERB_REQUIRED { 0 1 }
 enum THEMA_VALENCY { 0 1 }
 enum RHEMA_VALENCY { 0 1 }
 
 
 enum SUBJ_LINKED { 0 1 } // прикреплено подлежащее
 enum OBJ_LINKED { 0 1 } // прикреплено прямое дополнение
 enum OBJ2_LINKED { 0 1 } // прикреплен дательный (второй) объект для дитранзитивных глаголов
 enum GERUND_LINKED { 0 1 } // прикреплен герундий к глаголу: to keep doing ...
 enum SECONDVERB_LINKED { 0 1 } // прикреплен второй глагол в английском предложении с обратным порядком слов
 enum RHEMA_LINKED { 0 1 } // прикреплена рема: You are busy

 enum SUBJ_LOC { None Left Right }
 enum OBJ_LOC { None Left Right }
 enum RHEMA_LOC { None Left Right }


 // Порядок подлежащего и сказуемого в предикате
 enum WORD_ORDER
 {
  UNKNOWN
  S_V
  V_S
 }

 // обязательное условие, которое должно найтись в ходе восходящего или нисходящего разбора
 enum KEYFEATURE_REQUIRED { 0 1 }

 // дополнительное условие, которое делает результаты разбора более достоверными
 enum KEYFEATURE_DESIRABLE { 0 1 }

 // Особое условие, которое было обнаружено в ходе синтаксического разбора,
 // например: союзная конструкция.
 enum KEYFEATURE_DETECTED { 0 1 }

 
}
