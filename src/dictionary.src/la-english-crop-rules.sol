// -----------------------------------------------------------------------------
// File LA-ENGLISH-CROP-RULES.SOL
//
// (c) Koziev Elijah
//
// Content:
// Лексический Автомат, правила для управления работой Алгоритма Нечёткого
// сравнения мультилексем для АНГЛИЙСКОГО ЯЗЫКА.
// -----------------------------------------------------------------------------
//
// CD->13.07.2005
// LC->01.06.2011
// --------------

automat la
{
 crop "DE_militarization" language=English { if "$de" then  "" }
 crop "DES_interration"   language=English { if "$des" then  "" }
 crop "DIS_similar"       language=English { if "$dis" then  "" }
 crop "DI_atomic"         language=English { if "$di" then  "" }

 crop "GYGA-BYTE" language=English         { if "$gyga" then  "" }

 crop "IN-FORMAL" language=English { if "$in" then  "" }

 crop "IM-PERFECT" language=English { if "$im" then  "" }

 crop "IL-LEGAL" language=English { if "$il" then  "" }

 crop "IR-REGULAR" language=English { if "$ir" then  "" }

 crop "INTRA-VENOUS" language=English { if "$intra" then  "" }

 crop "INTER-NATIONAL" language=English { if "$inter" then  "" }

 crop "KILOHERZ" language=English { if "$kilo" then  "" }

 crop "THERMOSHIELD" language=English { if "$thermo" then  "" }

 crop "MISFORTUNE" language=English      { if "$mis" then  "" }

 crop "METALANGUAGE" language=English { if "$meta" then  "" }

 crop "MESOSTATE" language=English { if "$meso" then  "" }

 crop "MEGABYTE" language=English { if "$mega" then  "" }

 crop "MICROMETER" language=English { if "$micro" then  "" }

 crop "MULTIPOLAR" language=English { if "$multi" then  "" }

 crop "PSEUDOPODIA" language=English { if "$pseudo" then  "" }

 crop "PICOFARADE" language=English { if "$pico" then  "" }

 crop "PREVIEW" language=English { if "$pre" then  "" }

 crop "PHOTOMETER" language=English { if "$photo" then  "" }

 crop "REENTRY" language=English { if "$re" then  "" }

 crop "RADIOACTIVITY" language=English { if "$radio" then  "" }

 crop "SUPERPOWER" language=English { if "$super" then  "" }

 crop "TELECONTROL" language=English { if "$tele" then  "" }

 crop "UNDESIRABLE" language=English { if "$un" then  "" }

 crop "VIDEORECORDER" language=English { if "$video" then  "" }

 crop "TRANSCODER" language=English { if "$trans" then  "" }

 crop "COUNTERSTRIKE" language=English { if "$counter" then  "" }


  // Образование наречий
 crop "QUICK-LY" language=English { if "LY$" then  "" }
 crop "LUCKILY" language=English { if "ILY$" then  "Y" }

  // Формы глаголов
 crop "WILL-ING" language=English { if "ING$" then  "" }

 crop "ASK-ED" language=English { if "ED$" then  "" }
 crop "MARRIED" language=English { if "IED$" then  "Y" }

 crop "ASK-S" language=English { if "S$" then  "" }
 crop "FREQUENCIES" language=English { if "IESS$" then  "Y" }
 crop "BOXES" language=English { if "ES$" then  "" }

 crop "THINK-ER"  language=English { if "ER$" then  "" }
 crop "THINK-ERS" language=English { if "ERS$" then  "" }
 crop "STOPPER"   language=English { if "PPER$" then  "P" }
 crop "STOPPERS"  language=English { if "PPERS$" then  "P" }
 crop "CUTTER"    language=English { if "TTER$" then  "T" }
 crop "CUTTERS"   language=English { if "TTERS$" then  "T" }
 crop "PRINTER"   language=English { if "TER$" then  "T" }
 crop "PRINTERS"  language=English { if "TERS$" then  "T" }

 crop "ENVIRON-MENT" language=English { if "MENT$" then  "" }
 crop "ENVIRON-MENTS" language=English { if "MENTS$" then  "" }
 crop "ENVIRONMENTAL-IST" language=English { if "IST$" then  "" }
 crop "ENVIRONMENTAL-ISTS" language=English { if "ISTS$" then  "" }
 crop "PHYSIC-IAN" language=English { if "IAN$" then  "" }
 crop "PHYSIC-IANS" language=English { if "IANS$" then  "" }

 crop "DIRECT-ION" language=English { if "ION$" then  "" }
 crop "DIRECT-IONS" language=English { if "IONS$" then  "" }

 crop "DEMON-IZE" language=English { if "IZE$" then  "" }
  
 crop "MISTIFICATION"  language=English { if "ICATION$"  then  "Y" } // -> MISTIFY
 crop "MISTIFICATIONS" language=English { if "ICATIONS$" then  "Y" } // -> MISTIFY
 crop "MISTIFIER"      language=English { if "IER$"      then  "Y" } // -> MISTIFY
 crop "MISTIFIERS"     language=English { if "IERS$"     then  "Y" } // -> MISTIFY
 crop "MISTIFYING"     language=English { if "YING$"     then  "Y" } // -> MISTIFY
 crop "MISTIFIES"      language=English { if "IES$"      then  "Y" } // -> MISTIFY

 crop "RESPONSIBLE" language=English { if "IBLE$"     then  "E" } // -> response

 crop "ART-FUL"  language=English { if "FUL$"     then  "" } // -> art

  // разные образования существительных
 crop "SUN-NY"            language=English { if "NNY$"    then  "N" }
 crop "SUN-NIES"          language=English { if "NNIES$"  then  "N" }
 crop "DOG-GY"            language=English { if "GGY$"    then  "G" }
 crop "DOG-GIES"          language=English { if "GGIES$"  then  "G" }
 crop "GET-TY"            language=English { if "TTY$"    then  "T" }
 crop "GET-TIES"          language=English { if "TTIES$"  then  "T" }
 crop "WHEEL-IE"          language=English { if "IE$"     then  "" }
 crop "WHEEL-IES"         language=English { if "IES$"    then  "" }
 crop "NATION-AL"         language=English { if "AL$"     then  "" }
 crop "NATIONAL-IZATION"  language=English { if "IZATION$"     then  "IZE"  } // -> nationalize
 crop "NATIONAL-IZATIONS" language=English { if "IZATIONS$"     then  "IZE" } // -> nationalize
 crop "RESPONSIBILITY"    language=English { if "IBILITY$"     then  "E" } // -> response
 crop "RESPONSIBILITIES"  language=English { if "IBILITIES$"     then  "E" } // -> response
 
 crop "CONTRARINESS"  language=English { if "INESS$" then  "Y" } // -> response
 crop "ARTFULNESS"  language=English { if "NESS$" then  "" } // -> response

}
