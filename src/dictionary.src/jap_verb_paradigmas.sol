// -----------------------------------------------------------------------------
// File JAP_VERB_PARADIGMAS.SOL
//
// (c) Koziev Elijah
//
// Парадигмы спряжения японских глаголов.
// -----------------------------------------------------------------------------
//
// CD->08.03.2009
// LC->14.05.2011
// --------------

automat sg
{

 // Вежливая форма прошедшего времени образуется как IIя основа и постфикс ました.
 // См. группу правил "ФормаГлаголов"

 // Глаголы I спряжения, у которых основная форма заканчивается на -ру, например なる
 paradigm なる, JapVerb_9801 : JAP_VERB
 {
  JAP_VERB_BASE:I            { "%-1%+ら"  }
  JAP_VERB_BASE:II           { "%-1%+り"  }
  JAP_VERB_BASE:III          { ""       }
  JAP_VERB_BASE:IV           { "%-1%+れ"  }
  JAP_VERB_BASE:V            { "%-1%+ろう" } // 乗ろう
  JAP_VERB_BASE:PAST         { "%-1%+った" } // грубая форма
  JAP_VERB_BASE:PARTICIPLE   { "%-1%+って" } // て-форма
  JAP_VERB_BASE:POTENTIAL    { "%-1%+れる" } // 乗る　- скакать, 乗れる　могу скакать
  JAP_VERB_BASE:CONDITIONAL { "%-1%+れば" } // 乗れば - есть кто-либо скачет
 }

 
 paradigm 扱う : JAP_VERB for "(.+)う"
 {
  JAP_VERB_BASE:I            { "%-1%+わ"  }
  JAP_VERB_BASE:II           { "%-1%+い"  }
  JAP_VERB_BASE:III { "" }
  JAP_VERB_BASE:IV { "%-1%+え" }
  JAP_VERB_BASE:V { "%-1%+おう" } // 買おう
  JAP_VERB_BASE:PAST { "%-1%+った" } // грубая форма
  JAP_VERB_BASE:PARTICIPLE { "%-1%+って" }  // て-форма
  JAP_VERB_BASE:POTENTIAL    { "%-1%+える" } // 買う - купить, 買える　могу купить
  JAP_VERB_BASE:CONDITIONAL { "%-1%+えば" } // 買えば - есть кто-либо купит
 }

 
 paradigm 解き放つ : JAP_VERB for "(.+)つ"
 {
  JAP_VERB_BASE:I            { "%-1%+た"  }
  JAP_VERB_BASE:II           { "%-1%+ち"  }
  JAP_VERB_BASE:III { "" }
  JAP_VERB_BASE:IV { "%-1%+て" }
  JAP_VERB_BASE:V { "%-1%+とう" } // 待とう
  JAP_VERB_BASE:PAST { "%-1%+った" } // грубая форма
  JAP_VERB_BASE:PARTICIPLE { "%-1%+って" }  // て-форма
  JAP_VERB_BASE:POTENTIAL    { "%-1%+てる" } // 待つ - ждать, 待てる　могу подождать
  JAP_VERB_BASE:CONDITIONAL { "%-1%+てば" } // 待てば - есть кто-либо ждет
 }



 paradigm 死ぬ : JAP_VERB for "(.+)ぬ"
 {
  JAP_VERB_BASE:I            { "%-1%+な"  }
  JAP_VERB_BASE:II           { "%-1%+に"  }
  JAP_VERB_BASE:III { "" }
  JAP_VERB_BASE:IV { "%-1%+ね" }
  JAP_VERB_BASE:V { "%-1%+のう" } // 死のう
  JAP_VERB_BASE:PAST { "%-1%+んだ" } // грубая форма
  JAP_VERB_BASE:PARTICIPLE { "%-1%+んで" }  // て-форма
  JAP_VERB_BASE:POTENTIAL    { "%-1%+ねる" } //　死ぬ - умереть, 死ねる - могу умереть
  JAP_VERB_BASE:CONDITIONAL { "%-1%+ねば" } // 死ねば - есть кто-либо умрет
 }


 paradigm 貴ぶ : JAP_VERB for "(.+)ぶ"
 {
  JAP_VERB_BASE:I            { "%-1%+ば"  }
  JAP_VERB_BASE:II           { "%-1%+び"  }
  JAP_VERB_BASE:III { "" }
  JAP_VERB_BASE:IV { "%-1%+べ" }
  JAP_VERB_BASE:V { "%-1%+ぼう" } // 呼ぼう
  JAP_VERB_BASE:PAST { "%-1%+んだ" } // грубая форма
  JAP_VERB_BASE:PARTICIPLE { "%-1%+んで" } // て-форма
  JAP_VERB_BASE:POTENTIAL    { "%-1%+べる" } // 呼ぶ　- звать, 呼べる　- могу позвать
  JAP_VERB_BASE:CONDITIONAL { "%-1%+べば" } // 呼べば - есть кто-либо позовет
 }


 paradigm 囲む : JAP_VERB for "(.+)む"
 {
  JAP_VERB_BASE:I            { "%-1%+ま"  }
  JAP_VERB_BASE:II           { "%-1%+み"  }
  JAP_VERB_BASE:III { "" }
  JAP_VERB_BASE:IV { "%-1%+め" }
  JAP_VERB_BASE:V { "%-1%+もう" } // 読もう
  JAP_VERB_BASE:PAST { "%-1%+んだ" } // грубая форма
  JAP_VERB_BASE:PARTICIPLE { "%-1%+んで" } // て-форма
  JAP_VERB_BASE:POTENTIAL { "%-1%+める" } // 読む - читать, 読める　- могу читать
  JAP_VERB_BASE:CONDITIONAL { "%-1%+めば" } // 読めば - есть кто-либо прочитает
 }


 paradigm 引き抜く : JAP_VERB for "(.+)く"
 {
  JAP_VERB_BASE:I            { "%-1%+か"  }
  JAP_VERB_BASE:II           { "%-1%+き"  }
  JAP_VERB_BASE:III { "" }
  JAP_VERB_BASE:IV { "%-1%+け" }
  JAP_VERB_BASE:V { "%-1%+こう" } // 行こう
  JAP_VERB_BASE:PAST { "%-1%+いた" } // грубая форма
  JAP_VERB_BASE:PARTICIPLE { "%-1%+いて" }  // て-форма
  JAP_VERB_BASE:POTENTIAL { "%-1%+ける" }   // 書く - писать, 書ける　- могу писать
  JAP_VERB_BASE:CONDITIONAL { "%-1%+けば" } // 書けば - есть кто-либо пишет
 }

 paradigm 引継ぐ : JAP_VERB for "(.+)ぐ"
 {
  JAP_VERB_BASE:I            { "%-1%+が"  }
  JAP_VERB_BASE:II           { "%-1%+ぎ"  }
  JAP_VERB_BASE:III { "" }
  JAP_VERB_BASE:IV { "%-1%+げ" }
  JAP_VERB_BASE:V { "%-1%+ごう" } // 泳ごう
  JAP_VERB_BASE:PAST { "%-1%+いだ" } // грубая форма
  JAP_VERB_BASE:PARTICIPLE { "%-1%+いで" }  // て-форма
  JAP_VERB_BASE:POTENTIAL { "%-1%+げる" }   // 泳ぐ - плавать, 泳げる　- могу плавать
  JAP_VERB_BASE:CONDITIONAL { "%-1%+げば" } // 泳げば - есть кто-либо плавает
 }


 paradigm かき回す : JAP_VERB for "(.+)す"
 {
  JAP_VERB_BASE:I            { "%-1%+さ"  }
  JAP_VERB_BASE:II           { "%-1%+し"  }
  JAP_VERB_BASE:III { "" }
  JAP_VERB_BASE:IV { "%-1%+せ" }
  JAP_VERB_BASE:V { "%-1%+そう" } // 話そう
  JAP_VERB_BASE:PAST { "%-1%+した" }  // грубая форма
  JAP_VERB_BASE:PARTICIPLE { "%-1%+して" }   // て-форма
  JAP_VERB_BASE:POTENTIAL { "%-1%+せる" }   // 話す - говорить, 話せる　могу говорить
  JAP_VERB_BASE:CONDITIONAL { "%-1%+せば" } // 話せば - есть кто-либо говорит
 }


 paradigm 購入する : JAP_VERB for "(.+)する"
 {
  JAP_VERB_BASE:I            { "%-2%+し"    }
  JAP_VERB_BASE:II           { "%-2%+し"    }
  JAP_VERB_BASE:III          { ""       }
  JAP_VERB_BASE:IV           { "%-2%+すれ" }
  JAP_VERB_BASE:V            { "%-2%+しよう"} // 購入しよう
  JAP_VERB_BASE:PAST         { "%-2%+した" } // грубая форма
  JAP_VERB_BASE:PARTICIPLE   { "%-2%+して" }   // て-форма
  JAP_VERB_BASE:POTENTIAL { "%-2%+できる" }   // 購入できる
  JAP_VERB_BASE:CONDITIONAL { "%-2%+すれば" }   // 購入すれば
 }

 // Глаголы II спряжения
 paradigm Глаголы_Второго_Спряжения : JAP_VERB for "(.+)る"
 {
  JAP_VERB_BASE:I            { "%-1"    }
  JAP_VERB_BASE:II           { "%-1"    }
  JAP_VERB_BASE:III          { ""       }
  JAP_VERB_BASE:IV           { "%-1%+れ" }
  JAP_VERB_BASE:V            { "%-1%+よう"} // 見よう
  JAP_VERB_BASE:PAST         { "%-1%+た" } // грубая форма
  JAP_VERB_BASE:PARTICIPLE   { "%-1%+て" } // て-форма
  JAP_VERB_BASE:POTENTIAL { "%-1%+られる" }   // 見る　- видеть,　見られる - могу видеть
  JAP_VERB_BASE:CONDITIONAL { "%-1%+れば" }   // 見れば - если кто-то видит, 食べれば　если кто-то ест
 }
 
}
