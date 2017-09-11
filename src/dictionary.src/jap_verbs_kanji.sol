// CD->01.03.2009
// LC->13.04.2013

automat sg
{
 #define KanjiVerb(x,Transitive=NULL) \
  #begin
   entry x : JAP_VERB
   {
    paradigm auto
    JAP_FORM:KANJI
    #if Transitive!=NULL
    JAP_TRANSITIVE
    #endif	
   }
  #end 

 #define KanjiVerb_5r(x,Transitive=NULL) \
  #begin
   entry x : JAP_VERB
   {
    paradigm JapVerb_9801
    JAP_FORM:KANJI
    #if Transitive!=NULL
    JAP_TRANSITIVE
    #endif	
   }
  #end 

 KanjiVerb( 購入する, JAP_TRANSITIVE ) // покупать
 KanjiVerb( 勉強する ) // учиться
 KanjiVerb( 接触する, JAP_TRANSITIVE ) // касаться
 KanjiVerb( 説明する, JAP_TRANSITIVE ) // объяснять
 KanjiVerb( 取り消しする, JAP_TRANSITIVE ) // отменять
 KanjiVerb( 生産する, JAP_TRANSITIVE ) // производить, выпускать


 KanjiVerb( 更新する ) // обновить, обновлять
 KanjiVerb( 管理する ) // управлять
 KanjiVerb( 点滅する ) // мигать, мигнуть
 KanjiVerb( 要求する ) // спрашивать, спросить
 KanjiVerb( 完売する ) // продавать, продать
 KanjiVerb( 報告する ) // сообщить, сообщать
 KanjiVerb( 付属する ) // поставляться
 KanjiVerb( 点灯する ) // светить, освещать, осветить
 KanjiVerb( 終了する ) // выйти, выходить
 KanjiVerb( はまる ) // относиться, отнестись
 KanjiVerb( 鑑賞する ) // ценить, оценить
 KanjiVerb( ショートする ) // замкнуть накоротко
 KanjiVerb( 始動する ) // пускать, пустить
 KanjiVerb( 落下する ) // падать, упасть
 KanjiVerb( 再現する ) // воспроизводить, воспроизвести
 KanjiVerb( 軽減する ) // смягчать, смягчить
 KanjiVerb( 節約する ) // экономить, сэкономить
 KanjiVerb( 活用する ) // воспользоваться
 KanjiVerb( 交換する ) // заменять
 KanjiVerb( 欠損する ) // отсутствовать
 KanjiVerb( 利用する ) // использовать
 KanjiVerb( 登録する ) // внести, вносить
 KanjiVerb( 梱包する ) // упаковывать
 KanjiVerb( 加工する ) // происходить
 KanjiVerb( 頂戴する ) // предоставлять
 KanjiVerb( 準備する ) // готовить
 KanjiVerb( 引っかかる ) // поймать
 KanjiVerb( 確認する ) // проверять
 KanjiVerb( 落札する ) // предлагать
 KanjiVerb( 防止する ) // предотвращать
 KanjiVerb( 開封する ) // открывать
 KanjiVerb( ロックする ) // запирать
 KanjiVerb( ドレスアップする ) // наряжаться
 KanjiVerb( 存在する ) // существовать
 KanjiVerb( 転送する ) // продвигаться
 KanjiVerb( 付着する ) // придерживаться
 KanjiVerb( 入力する ) // вводить
 KanjiVerb( 記録する ) // записывать
 KanjiVerb( 除去する ) // удалять
 KanjiVerb( 発生する ) // происходить
 KanjiVerb( 変更する ) // менять, изменить
 KanjiVerb( 装着する ) // прикрепить, прикреплять
 KanjiVerb( 削除する ) // удалить, удалять, удаление
 KanjiVerb( 惚れ惚れする ) // восхищаться, восхитительный
 KanjiVerb( 中止する ) // прервать, прерывать
 KanjiVerb( 塗装する ) // окрасить, окрашивать, окрашенный
 KanjiVerb( お断りする ) // отказывать, отказать
 KanjiVerb( 変化する ) // менять, изменить, изменять
 KanjiVerb( 劣化する ) // ухудшать, ухудшить
 KanjiVerb( 操作する ) // работать
 KanjiVerb( 発送する ) // грузить, загрузить
 KanjiVerb( 設定する ) // устанавлить, установить
 KanjiVerb( お願いする ) // благодарить
 KanjiVerb( キャンセルする ) // отменить, отменять
 KanjiVerb( 制限する ) // ограничивать, ограничть
 KanjiVerb( 省略する ) // пропускать, пропустить
 KanjiVerb( 使用する ) // использовать
 KanjiVerb( 表示する ) // отображать, отобразить


 KanjiVerb( あざ笑う, JAP_TRANSITIVE ) // (v5u,vt) (uk) to sneer at/to ridicule
 KanjiVerb( うつ伏せる, JAP_TRANSITIVE ) // (v1,vt) to lie face-down
 KanjiVerb( かき回す, JAP_TRANSITIVE ) // (v5s,vt) to stir up/to churn/to ransack/to disturb
 KanjiVerb( かき合せる, JAP_TRANSITIVE ) // (v1,vt) to adjust/to arrange
 KanjiVerb( かき集める, JAP_TRANSITIVE ) // (v1,vt) to gather up/to scrape up together
 KanjiVerb( かき消す, JAP_TRANSITIVE ) // (v5s,vt) to erase
 KanjiVerb( かき分ける, JAP_TRANSITIVE ) // (v1,vt) to push one's way through
 KanjiVerb( かき立てる, JAP_TRANSITIVE ) // (v1,vt) to stir up/to arouse
 KanjiVerb( かっ飛ばす, JAP_TRANSITIVE ) // (v5s,vt) to knock out (a homer)/to slam
 KanjiVerb( くり抜く, JAP_TRANSITIVE ) // (v5k,vt) to gouge out/to excavate/to bore/to drill
 KanjiVerb( こき使う, JAP_TRANSITIVE ) // (v5u,vt) to work someone hard
 KanjiVerb( こじ開ける, JAP_TRANSITIVE ) // (v1,vt) to wrench open/to prize open/to pick (lock)
 KanjiVerb( さらけ出す, JAP_TRANSITIVE ) // (v5s,vt) to expose/to disclose/to lay bare/to confess
 KanjiVerb( し損じる, JAP_TRANSITIVE ) // (v1,vt) to blunder/to fail/to make a mistake
 KanjiVerb( し損ずる, JAP_TRANSITIVE ) // (vz,vt) to blunder/to fail/to make a mistake
 KanjiVerb( たらし込む, JAP_TRANSITIVE ) // (v5m,vt) to cajole/to deceive/to seduce
 KanjiVerb( つけ加える, JAP_TRANSITIVE ) // (v1,vt) to add one thing to another
 KanjiVerb( つなぎ止める, JAP_TRANSITIVE ) // (v1,vt) to tie/to fasten/to hitch
 KanjiVerb( でっち上げる, JAP_TRANSITIVE ) // (v1,vt) (1) (uk) to fabricate/to invent/to make up (a story)/(2) to frame someone
 KanjiVerb( なぎ倒す, JAP_TRANSITIVE ) // (v5s,vt) to mow down/to beat/to cut a swath/to sweep off one's feet
 KanjiVerb( にらみ付ける, JAP_TRANSITIVE ) // (v1,vt) to glare at/to scowl at
 KanjiVerb( ねじ伏せる, JAP_TRANSITIVE ) // (v1,vt) to hold down/to twist one's arm
 KanjiVerb( はめ込む, JAP_TRANSITIVE ) // (v5m,vt) to inlay/to insert/to fix into a container
 KanjiVerb( ひき殺す, JAP_TRANSITIVE ) // (v5s,vt) to kill by running over
 KanjiVerb( ひっくり返す, JAP_TRANSITIVE ) // (v5s,vt) to turn over/to overturn/to knock over/to upset/to turn inside out
 KanjiVerb( ひん曲げる, JAP_TRANSITIVE ) // (v1,vt) (1) to bend (with great force)/to twist/to wrench/(2) to distort (the truth)
 KanjiVerb( ぶっ掛ける, JAP_TRANSITIVE ) // (v1,vt) to dash (slosh) water (or other liquid) on a person or in a person's face
 KanjiVerb( ぶっ殺す, JAP_TRANSITIVE ) // (v5s,vt) to beat to death
 KanjiVerb( ぶっ飛ばす, JAP_TRANSITIVE ) // (v5s,vt) to drive at full speed/to beat/to strike/to knock/to let go off/to not partake
 KanjiVerb( ぶら下げる, JAP_TRANSITIVE ) // (v1,vt) to hang/to suspend/to dangle/to swing/(P)
 KanjiVerb( まき散らす, JAP_TRANSITIVE ) // (v5s,vt) to scatter/to spread
 KanjiVerb( やっ付ける, JAP_TRANSITIVE ) // (v1,vt) to beat/to attack (an enemy)/to do away with/to finish off/(P)
 KanjiVerb( やり過ごす, JAP_TRANSITIVE ) // (v5s,vt) to do too much/to let something (or somebody) go past/(P)
 KanjiVerb( やり合う, JAP_TRANSITIVE ) // (v5u,vt) to compete with/to argue with/to quarrel
 KanjiVerb( やり遂げる, JAP_TRANSITIVE ) // (v1,vt) to accomplish
 KanjiVerb( やり直す, JAP_TRANSITIVE ) // (v5s,vt) to do over again/to redo/to start over/to remake/to resume/to recommence/(P)
 KanjiVerb( 哀しむ, JAP_TRANSITIVE ) // (v5m,vt) to be sad/to mourn for/to regret
 KanjiVerb( 哀れむ, JAP_TRANSITIVE ) // (v5m,vt) to commiserate/to pity/to have mercy on/to sympathize with/to sympathise with/(P)
 KanjiVerb( 愛でる, JAP_TRANSITIVE ) // (v1,vt) to love/to admire
 KanjiVerb( 握らす, JAP_TRANSITIVE ) // (v5s,vt) to let (someone) take hold of your hand/(P)
 KanjiVerb( 握りつぶす, JAP_TRANSITIVE ) // (v5s,vt) to crush (with one's hands)/to abandon
 KanjiVerb( 握り緊める, JAP_TRANSITIVE ) // (v1,vt) to grasp tightly
 KanjiVerb( 握り潰す, JAP_TRANSITIVE ) // (v5s,vt) to crush (with one's hands)/to abandon
 KanjiVerb( 握り締める, JAP_TRANSITIVE ) // (v1,vt) to grasp tightly/(P)
 KanjiVerb( 圧し込む, JAP_TRANSITIVE ) // (v5m,vt) to push into
 KanjiVerb( 圧し殺す, JAP_TRANSITIVE ) // (v5s,vt) to crush to death/to stifle to death/to squeeze to death
 KanjiVerb( 圧し潰す, JAP_TRANSITIVE ) // (v5s,vt) to squash/to crush/to flatten
 KanjiVerb( 圧す, JAP_TRANSITIVE ) // (v5s,vt) (arch) to dent/to press/to push
 KanjiVerb( 圧潰す, JAP_TRANSITIVE ) // (v5s,vt) to squash/to crush/to flatten
 KanjiVerb( 扱う, JAP_TRANSITIVE ) // (v5u,vt) to handle/to deal with/to treat/(P)
 KanjiVerb( 扱き下ろす, JAP_TRANSITIVE ) // (v5s,vt) to denounce/to disparage/to lambast/to abuse
 KanjiVerb( 扱き使う, JAP_TRANSITIVE ) // (v5u,vt) to work someone hard
 KanjiVerb( 扱く, JAP_TRANSITIVE ) // (v5k,vt) (uk) to draw through one's hand/to stroke (a beard)/to work someone hard
 KanjiVerb( 扱下ろす, JAP_TRANSITIVE ) // (v5s,vt) to denounce/to disparage/to lambast/to abuse
 KanjiVerb( 扱使う, JAP_TRANSITIVE ) // (v5u,vt) to work someone hard
 KanjiVerb( 宛がう, JAP_TRANSITIVE ) // (v5u,vt) (1) to allot/to allocate/(2) to supply with/to furnish/(3) to fit to/to fasten to/to apply to
 KanjiVerb( 宛てがう, JAP_TRANSITIVE ) // (v5u,vt) (1) to allot/to allocate/(2) to supply with/to furnish/(3) to fit to/to fasten to/to apply to
 KanjiVerb( 宛てる, JAP_TRANSITIVE ) // (v1,vt) to address
 KanjiVerb( 按ずる, JAP_TRANSITIVE ) // (vz,vt) (1) to be anxious or concerned about/to ponder (anxiously)/to fear/(2) to investigate/to consider/to plan
 KanjiVerb( 暗ます, JAP_TRANSITIVE ) // (v5s,vt) to abscond/to deceive
 KanjiVerb( 案じる, JAP_TRANSITIVE ) // (v1,vt) to be anxious/to ponder
 KanjiVerb( 案ずる, JAP_TRANSITIVE ) // (vz,vt) (1) to be anxious or concerned about/to ponder (anxiously)/to fear/(2) to investigate/to consider/to plan
 KanjiVerb( 位置づける, JAP_TRANSITIVE ) // (v1,vt) to place (in relation to the whole)/to rank/to position/to locate
 KanjiVerb( 位置付ける, JAP_TRANSITIVE ) // (v1,vt) to place (in relation to the whole)/to rank/to position/to locate/(P)
 KanjiVerb( 囲う, JAP_TRANSITIVE ) // (v5u,vt) to enclose/(P)
 KanjiVerb( 囲む, JAP_TRANSITIVE ) // (v5m,vt) to surround/to encircle/(P)
 KanjiVerb( 委ねる, JAP_TRANSITIVE ) // (v1,vt) to entrust to/to devote oneself to/(P)
 KanjiVerb( 意味付ける, JAP_TRANSITIVE ) // (v1,vt) to give meaning to
 KanjiVerb( 慰める, JAP_TRANSITIVE ) // (v1,vt) to comfort/to console/(P)
 KanjiVerb( 為さる, JAP_TRANSITIVE ) // (v5aru,vt) (hon) to do/(P)
 KanjiVerb( 為し終える, JAP_TRANSITIVE ) // (v1,vt) to accomplish/to finish
 KanjiVerb( 為し遂げる, JAP_TRANSITIVE ) // (v1,vt) to accomplish/to finish/to fulfill
 KanjiVerb( 為す, JAP_TRANSITIVE ) // (v5s,vt) to accomplish/to do/(P)
 KanjiVerb( 為果せる, JAP_TRANSITIVE ) // (v1,vt) to accomplish
 KanjiVerb( 為合う, JAP_TRANSITIVE ) // (v5u,vt) (uk) to do together
 KanjiVerb( 為残す, JAP_TRANSITIVE ) // (v5s,vt) to leave unfinished
 KanjiVerb( 為尽くす, JAP_TRANSITIVE ) // (v5s,vt) to do everything possible
 KanjiVerb( 為尽す, JAP_TRANSITIVE ) // (v5s,vt) to do everything possible
 KanjiVerb( 為遂げる, JAP_TRANSITIVE ) // (v1,vt) to accomplish/to finish/to fulfill
 KanjiVerb( 為損じる, JAP_TRANSITIVE ) // (v1,vt) to blunder/to fail/to make a mistake
 KanjiVerb( 為損ずる, JAP_TRANSITIVE ) // (vz,vt) to blunder/to fail/to make a mistake
 KanjiVerb( 為落す, JAP_TRANSITIVE ) // (v5s,vt) to fail to do/to make light of/to neglect
 KanjiVerb( 為落とす, JAP_TRANSITIVE ) // (v5s,vt) to fail to do/to make light of/to neglect
 KanjiVerb( 移す, JAP_TRANSITIVE ) // (v5s,vt) to remove/to transfer/to infect/(P)
 KanjiVerb( 謂う, JAP_TRANSITIVE ) // (v5u,vt) is referred to as ../is called ..
 KanjiVerb( 違える, JAP_TRANSITIVE ) // (v1,vt) to change
 KanjiVerb( 遺す, JAP_TRANSITIVE ) // (v5s,vt) to leave (behind, over)/to bequeath/to save/to reserve
 KanjiVerb( 育てる, JAP_TRANSITIVE ) // (v1,vt) to raise/to rear/to bring up/(P)
 KanjiVerb( 育て上げる, JAP_TRANSITIVE ) // (v1,vt) to raise (to maturity)/to rear/to train/to educate
 KanjiVerb( 育む, JAP_TRANSITIVE ) // (v5m,vt) to raise/to rear/to bring up/(P)
 KanjiVerb( 逸らす, JAP_TRANSITIVE ) // (v5s,vt) to turn away/to avert/(P)
 KanjiVerb( 印象づける, JAP_TRANSITIVE ) // (v1,vt) to impress (someone)
 KanjiVerb( 印象付ける, JAP_TRANSITIVE ) // (v1,vt) to impress (someone)/(P)
 KanjiVerb( 引かす, JAP_TRANSITIVE ) // (v5s,vt) to redeem debts (e.g., of a geisha)
 KanjiVerb( 引き延す, JAP_TRANSITIVE ) // (v5s,vt) to delay/to enlarge/(P)
 KanjiVerb( 引き延ばす, JAP_TRANSITIVE ) // (v5s,vt) to delay/to enlarge/(P)
 KanjiVerb( 引き下げる, JAP_TRANSITIVE ) // (v1,vt) to pull down/to lower/to reduce/to withdraw/(P)
 KanjiVerb( 引き下ろす, JAP_TRANSITIVE ) // (v5s,vt) to haul down/to drag down
 KanjiVerb( 引き回す, JAP_TRANSITIVE ) // (v5s,vt) to draw a curtain/to guide/to parade about
 KanjiVerb( 引き寄せる, JAP_TRANSITIVE ) // (v1,vt) to draw or pull something towards oneself (e.g., chair)
 KanjiVerb( 引き起こす, JAP_TRANSITIVE ) // (v5s,vt) to cause/(P)
 KanjiVerb( 引き起す, JAP_TRANSITIVE ) // (v5s,vt) to cause/(P)
 KanjiVerb( 引き継ぐ, JAP_TRANSITIVE ) // (v5g,vt) to take over/to hand over/(P)
 KanjiVerb( 引き合わせる, JAP_TRANSITIVE ) // (v1,vt) to introduce/to compare
 KanjiVerb( 引き込む, JAP_TRANSITIVE ) // (v5m,vt) to draw in/to win over
 KanjiVerb( 引き止める, JAP_TRANSITIVE ) // (v1,vt) to detain/to check/to restrain/(P)
 KanjiVerb( 引き受ける, JAP_TRANSITIVE ) // (v1,vt) to undertake/to take up/to take over/to be responsible for/to guarantee/to contract (disease)/(P)
 KanjiVerb( 引き出す, JAP_TRANSITIVE ) // (v5s,vt) to pull out/to take out/to draw out/to withdraw/(P)
 KanjiVerb( 引き上げる, JAP_TRANSITIVE ) // (v1,vt) to withdraw/to leave/to pull out/to retire/(P)
 KanjiVerb( 引き伸す, JAP_TRANSITIVE ) // (v5s,vt) to delay/to enlarge/(P)
 KanjiVerb( 引き伸ばす, JAP_TRANSITIVE ) // (v5s,vt) to delay/to enlarge/(P)
 KanjiVerb( 引き摺り回す, JAP_TRANSITIVE ) // (v5s,vt) to drag around
 KanjiVerb( 引き摺り込む, JAP_TRANSITIVE ) // (v5m,vt) to drag in
 KanjiVerb( 引き摺り出す, JAP_TRANSITIVE ) // (v5s,vt) to drag out
 KanjiVerb( 引き替える, JAP_TRANSITIVE ) // (v1,vt) to exchange (things)/to reverse
 KanjiVerb( 引き直す, JAP_TRANSITIVE ) // (v5s,vt) to redo
 KanjiVerb( 引き締める, JAP_TRANSITIVE ) // (v1,vt) to tighten/to stiffen/to brace/to strain/(P)
 KanjiVerb( 引き渡す, JAP_TRANSITIVE ) // (v5s,vt) to deliver/to extradite/to stretch across/to hand over/(P)
 KanjiVerb( 引き倒す, JAP_TRANSITIVE ) // (v5s,vt) to pull down
 KanjiVerb( 引き当てる, JAP_TRANSITIVE ) // (v1,vt) to apply/to compare
 KanjiVerb( 引き入れる, JAP_TRANSITIVE ) // (v1,vt) to drag into/to win over
 KanjiVerb( 引き剥がす, JAP_TRANSITIVE ) // (v5s,vt) to tear off
 KanjiVerb( 引き剥ぐ, JAP_TRANSITIVE ) // (v5g,vt) to tear off
 KanjiVerb( 引き抜く, JAP_TRANSITIVE ) // (v5k,vt) to extract/to uproot/to pull out/(P)
 KanjiVerb( 引き払う, JAP_TRANSITIVE ) // (v5u,vt) to vacate
 KanjiVerb( 引き分ける, JAP_TRANSITIVE ) // (v1,vt) to pull apart/to separate
 KanjiVerb( 引き返す, JAP_TRANSITIVE ) // (v5s,vt) to repeat/to send back/to bring back/to retrace one's steps/(P)
 KanjiVerb( 引き放つ, JAP_TRANSITIVE ) // (v5t,vt) to pull apart
 KanjiVerb( 引き戻す, JAP_TRANSITIVE ) // (v5s,vt) to bring back/to restore/(P)
 KanjiVerb( 引き揚げる, JAP_TRANSITIVE ) // (v1,vt) to withdraw/to leave/to pull out/to retire
 KanjiVerb( 引き落す, JAP_TRANSITIVE ) // (v5s,vt) to pull down/to automatically debit (from a bank account)
 KanjiVerb( 引き落とす, JAP_TRANSITIVE ) // (v5s,vt) to pull down/to automatically debit (from a bank account)
 KanjiVerb( 引き離す, JAP_TRANSITIVE ) // (v5s,vt) to pull apart/to separate/(P)
 KanjiVerb( 引き立てる, JAP_TRANSITIVE ) // (v1,vt) to favour/to favor/to promote/to march (a prisoner off)/to support
 KanjiVerb( 引き留める, JAP_TRANSITIVE ) // (v1,vt) to detain/to check/to restrain
 KanjiVerb( 引き裂く, JAP_TRANSITIVE ) // (v5k,vt) to tear up/to tear off/to split/(P)
 KanjiVerb( 引き連れる, JAP_TRANSITIVE ) // (v1,vt) to take along with
 KanjiVerb( 引く, JAP_TRANSITIVE ) // (v5k,vi,vt) (1) to pull/(2) to draw back/(3) to draw (a card)/(4) to draw (plan, line, etc.)/(5) to catch (cold)/(6) to play (string instr.)/(7) to look up (e.g., dictionary)/to consult/(P)
 KanjiVerb( 引っかける, JAP_TRANSITIVE ) // (v1,vt) (1) to hang (something) on (something)/to throw on (clothes)/(2) to hook/to catch/to trap/to ensnare/(3) to cheat/to evade payment/to jump a bill/(4) to drink (alcohol)/(5) to spit at (a person)/(6) to hit the ball off the end of the bat (baseball)
 KanjiVerb( 引っ掛ける, JAP_TRANSITIVE ) // (v1,vt) (1) to hang (something) on (something)/to throw on (clothes)/(2) to hook/to catch/to trap/to ensnare/(3) to cheat/to evade payment/to jump a bill/(4) to drink (alcohol)/(5) to spit at (a person)/(6) to hit the ball off the end of the bat (baseball)/(P)
 KanjiVerb( 引っ繰り返す, JAP_TRANSITIVE ) // (v5s,vt) to turn over/to overturn/to knock over/to upset/to turn inside out
 KanjiVerb( 引っ懸ける, JAP_TRANSITIVE ) // (v1,vt) (1) to hang (something) on (something)/to throw on (clothes)/(2) to hook/to catch/to trap/to ensnare/(3) to cheat/to evade payment/to jump a bill/(4) to drink (alcohol)/(5) to spit at (a person)/(6) to hit the ball off the end of the bat (baseball)
 KanjiVerb( 引っ込める, JAP_TRANSITIVE ) // (v1,vt) to draw in/to take in
 KanjiVerb( 引っ掻き回す, JAP_TRANSITIVE ) // (v5s,vt) to ransack (a drawer)/to rummage/to stir up (mud)/to throw into confusion/to tamper with
 KanjiVerb( 引っ掻く, JAP_TRANSITIVE ) // (v5k,vt) to scratch
 KanjiVerb( 引っ張り出す, JAP_TRANSITIVE ) // (v5s,vt) to take out/to drag out
 KanjiVerb( 引っ剥ぐ, JAP_TRANSITIVE ) // (v5g,vt) to tear off
 KanjiVerb( 引っ捕える, JAP_TRANSITIVE ) // (v1,vt) to seize
 KanjiVerb( 引延す, JAP_TRANSITIVE ) // (v5s,vt) to delay/to enlarge/(P)
 KanjiVerb( 引延ばす, JAP_TRANSITIVE ) // (v5s,vt) to delay/to enlarge/(P)
 KanjiVerb( 引下げる, JAP_TRANSITIVE ) // (v1,vt) to pull down/to lower/to reduce/to withdraw/(P)
 KanjiVerb( 引下ろす, JAP_TRANSITIVE ) // (v5s,vt) to haul down/to drag down
 KanjiVerb( 引回す, JAP_TRANSITIVE ) // (v5s,vt) to draw a curtain/to guide/to parade about
 KanjiVerb( 引換える, JAP_TRANSITIVE ) // (v1,vt) to exchange (things)/to reverse
 KanjiVerb( 引寄せる, JAP_TRANSITIVE ) // (v1,vt) to draw or pull something towards oneself (e.g., chair)
 KanjiVerb( 引継ぐ, JAP_TRANSITIVE ) // (v5g,vt) to take over/to hand over/(P)
 KanjiVerb( 引止める, JAP_TRANSITIVE ) // (v1,vt) to detain/to check/to restrain/(P)
 KanjiVerb( 引受ける, JAP_TRANSITIVE ) // (v1,vt) to undertake/to take up/to take over/to be responsible for/to guarantee/to contract (disease)/(P)
 KanjiVerb( 引受る, JAP_TRANSITIVE ) // (v1,vt) to undertake/to take up/to take over/to be responsible for/to guarantee/to contract (disease)
 KanjiVerb( 引出す, JAP_TRANSITIVE ) // (v5s,vt) to pull out/to take out/to draw out/to withdraw/(P)
 KanjiVerb( 引伸す, JAP_TRANSITIVE ) // (v5s,vt) to delay/to enlarge/(P)
 KanjiVerb( 引伸ばす, JAP_TRANSITIVE ) // (v5s,vt) to delay/to enlarge/(P)
 KanjiVerb( 引替る, JAP_TRANSITIVE ) // (v1,vt) to exchange (things)/to reverse
 KanjiVerb( 引直す, JAP_TRANSITIVE ) // (v5s,vt) to redo
 KanjiVerb( 引締める, JAP_TRANSITIVE ) // (v1,vt) to tighten/to stiffen/to brace/to strain/(P)
 KanjiVerb( 引渡す, JAP_TRANSITIVE ) // (v5s,vt) to deliver/to extradite/to stretch across/to hand over
 KanjiVerb( 引当てる, JAP_TRANSITIVE ) // (v1,vt) to apply/to compare
 KanjiVerb( 引当る, JAP_TRANSITIVE ) // (v1,vt) to apply/to compare
 KanjiVerb( 引抜く, JAP_TRANSITIVE ) // (v5k,vt) to extract/to uproot/to pull out/(P)
 KanjiVerb( 引返す, JAP_TRANSITIVE ) // (v5s,vt) to repeat/to send back/to bring back/to retrace one's steps/(P)
 KanjiVerb( 引戻す, JAP_TRANSITIVE ) // (v5s,vt) to bring back/to restore/(P)
 KanjiVerb( 引落す, JAP_TRANSITIVE ) // (v5s,vt) to pull down/to automatically debit (from a bank account)
 KanjiVerb( 引落とす, JAP_TRANSITIVE ) // (v5s,vt) to pull down/to automatically debit (from a bank account)
 KanjiVerb( 引離す, JAP_TRANSITIVE ) // (v5s,vt) to pull apart/to separate/(P)
 KanjiVerb( 引立てる, JAP_TRANSITIVE ) // (v1,vt) to favour/to favor/to promote/to march (a prisoner off)/to support
 KanjiVerb( 引裂く, JAP_TRANSITIVE ) // (v5k,vt) to tear up/to tear off/to split/(P)
 KanjiVerb( 引連れる, JAP_TRANSITIVE ) // (v1,vt) to take along with
 KanjiVerb( 飲ます, JAP_TRANSITIVE ) // (v5s,vt) to make somebody drink
 KanjiVerb( 飲み下す, JAP_TRANSITIVE ) // (v5s,vt) to swallow/to gulp down
 KanjiVerb( 飲み回す, JAP_TRANSITIVE ) // (v5s,vt) to pass the cup round
 KanjiVerb( 飲み乾す, JAP_TRANSITIVE ) // (v5s,vt) to drink up/to drain (cup)
 KanjiVerb( 飲み干す, JAP_TRANSITIVE ) // (v5s,vt) to drink up/to drain (cup)
 KanjiVerb( 飲み込む, JAP_TRANSITIVE ) // (v5m,vt) (1) to gulp down/to swallow deeply/(2) to understand/to take in/to catch on to/to learn/to digest/(P)
 KanjiVerb( 飲み潰す, JAP_TRANSITIVE ) // (v5s,vt) to drink away one's money
 KanjiVerb( 飲み倒す, JAP_TRANSITIVE ) // (v5s,vt) to skip out on one's bar bill
 KanjiVerb( 飲み明かす, JAP_TRANSITIVE ) // (v5s,vt) to drink the night away
 KanjiVerb( 飲む, JAP_TRANSITIVE ) // (v5m,vt) to drink/(P)
 KanjiVerb( 飲下す, JAP_TRANSITIVE ) // (v5s,vt) to swallow/to gulp down
 KanjiVerb( 飲乾す, JAP_TRANSITIVE ) // (v5s,vt) to drink up/to drain (cup)
 KanjiVerb( 飲干す, JAP_TRANSITIVE ) // (v5s,vt) to drink up/to drain (cup)
 KanjiVerb( 飲込む, JAP_TRANSITIVE ) // (v5m,vt) (1) to gulp down/to swallow deeply/(2) to understand/to take in/to catch on to/to learn/to digest
 KanjiVerb( 飲潰す, JAP_TRANSITIVE ) // (v5s,vt) to drink away one's money
 KanjiVerb( 飲倒す, JAP_TRANSITIVE ) // (v5s,vt) to skip out on one's bar bill
 KanjiVerb( 隠す, JAP_TRANSITIVE ) // (v5s,vt) to hide/to conceal/(P)
 KanjiVerb( 窺う, JAP_TRANSITIVE ) // (v5u,vt) to see the situation
 KanjiVerb( 唄う, JAP_TRANSITIVE ) // (v5u,vt) to sing
 KanjiVerb( 運び込む, JAP_TRANSITIVE ) // (v5m,vt) to carry in/to bring in
 KanjiVerb( 営む, JAP_TRANSITIVE ) // (v5m,vt) to carry on (e.g., in ceremony)/to run a business/(P)
 KanjiVerb( 映し出す, JAP_TRANSITIVE ) // (v5s,vt) to project/to reflect/(P)
 KanjiVerb( 映す, JAP_TRANSITIVE ) // (v5s,vt) to project/to reflect/to cast (shadow)/(P)
 KanjiVerb( 曳く, JAP_TRANSITIVE ) // (v5k,vi,vt) (1) to pull/(2) to draw back/(3) to draw (a card)/(4) to draw (plan, line, etc.)/(5) to catch (cold)/(6) to play (string instr.)/(7) to look up (e.g., dictionary)/to consult
 KanjiVerb( 洩らす, JAP_TRANSITIVE ) // (v5s,vt) to let leak/to reveal
 KanjiVerb( 詠む, JAP_TRANSITIVE ) // (v5m,vt) to recite/to chant/(P)
 KanjiVerb( 厭う, JAP_TRANSITIVE ) // (v5u,vt) to dislike/to hate/to grudge (doing)/to spare (oneself)/to be weary of/to take (good) care of
 KanjiVerb( 厭かす, JAP_TRANSITIVE ) // (v5s,vt) to glut/to satiate/to weary/to tire/to bore/to weary
 KanjiVerb( 延ばす, JAP_TRANSITIVE ) // (v5s,vt) to lengthen/to stretch/to reach out/to postpone/to prolong/to extend/to grow (beard)/(P)
 KanjiVerb( 延べる, JAP_TRANSITIVE ) // (v1,vt) to make (bed)/to stretch/to widen
 KanjiVerb( 怨む, JAP_TRANSITIVE ) // (v5m,vt) to curse/to feel bitter
 KanjiVerb( 掩う, JAP_TRANSITIVE ) // (v5u,vt) to cover/to hide/to conceal/to wrap/to disguise
 KanjiVerb( 演じる, JAP_TRANSITIVE ) // (v1,vt) to perform (a play)/to play (a part)/to act (a part)/to commit (a blunder)/(P)
 KanjiVerb( 演ずる, JAP_TRANSITIVE ) // (vz,vt) to perform/to play/(P)
 KanjiVerb( 縁付ける, JAP_TRANSITIVE ) // (v1,vt) to marry off/to give in marriage
 KanjiVerb( 遠ざける, JAP_TRANSITIVE ) // (v1,vt) to keep away/to keep at a distance
 KanjiVerb( 遠退ける, JAP_TRANSITIVE ) // (v1,vt) to keep (someone) at a distance
 KanjiVerb( 汚す, JAP_TRANSITIVE ) // (v5s,vt) (1) to disgrace/to dishonour/to dishonor/(2) to pollute/to contaminate/to soil/to make dirty/to stain/(P)
 KanjiVerb( 凹ます, JAP_TRANSITIVE ) // (v5s,vt) to dent/to indent/to depress/to humiliate
 KanjiVerb( 凹める, JAP_TRANSITIVE ) // (v1,vt) to hollow out
 KanjiVerb( 往なす, JAP_TRANSITIVE ) // (v5s,vt) to parry/to sidestep/to let go/to chase away
 KanjiVerb( 押えつける, JAP_TRANSITIVE ) // (v1,vt) to press down/to hold down/to pin down/to repress
 KanjiVerb( 押える, JAP_TRANSITIVE ) // (v1,vt) to stop/to restrain/to seize/to repress/to suppress/to press down
 KanjiVerb( 押え込む, JAP_TRANSITIVE ) // (v5m,vt) to pin down/to immobilize/to immobilise/to control/to suppress
 KanjiVerb( 押え付ける, JAP_TRANSITIVE ) // (v1,vt) to press down/to hold down/to pin down/to repress
 KanjiVerb( 押さえる, JAP_TRANSITIVE ) // (v1,vt) to stop/to restrain/to seize/to repress/to suppress/to press down/(P)
 KanjiVerb( 押さえ込む, JAP_TRANSITIVE ) // (v5m,vt) to pin down/to immobilize/to immobilise/to control/to suppress
 KanjiVerb( 押さえ付ける, JAP_TRANSITIVE ) // (v1,vt) to press down/to hold down/to pin down/to repress
 KanjiVerb( 押しつける, JAP_TRANSITIVE ) // (v1,vt) to press/to push/to force
 KanjiVerb( 押しつぶす, JAP_TRANSITIVE ) // (v5s,vt) to squash/to crush/to flatten
 KanjiVerb( 押し隠す, JAP_TRANSITIVE ) // (v5s,vt) to cover up/to conceal
 KanjiVerb( 押し下げる, JAP_TRANSITIVE ) // (v1,vt) to push or press or force down/to depress
 KanjiVerb( 押し広める, JAP_TRANSITIVE ) // (v1,vt) to extend by force/to aggrandize/to aggrandise
 KanjiVerb( 押し込める, JAP_TRANSITIVE ) // (v1,vt) to shut up/to imprison
 KanjiVerb( 押し殺す, JAP_TRANSITIVE ) // (v5s,vt) to crush to death/to stifle to death/to squeeze to death
 KanjiVerb( 押し止める, JAP_TRANSITIVE ) // (v1,vt) to check/to stop/to keep back
 KanjiVerb( 押し出す, JAP_TRANSITIVE ) // (v5s,vt) to crowd out/to push out/to squeeze out
 KanjiVerb( 押し上げる, JAP_TRANSITIVE ) // (v1,vt) to boost/to force up/to push up
 KanjiVerb( 押し進める, JAP_TRANSITIVE ) // (v1,vt) to press forward
 KanjiVerb( 押し戴く, JAP_TRANSITIVE ) // (v5k,vt) to accept an object and hold it reverently over one's head
 KanjiVerb( 押し退ける, JAP_TRANSITIVE ) // (v1,vt) to push aside/to brush aside
 KanjiVerb( 押し頂く, JAP_TRANSITIVE ) // (v5k,vt) to accept an object and hold it reverently over one's head
 KanjiVerb( 押し通す, JAP_TRANSITIVE ) // (v5s,vt) to persist in/to carry out/to have one's own way/to push through/to carry through
 KanjiVerb( 押し潰す, JAP_TRANSITIVE ) // (v5s,vt) to squash/to crush/to flatten
 KanjiVerb( 押し倒す, JAP_TRANSITIVE ) // (v5s,vt) to push down
 KanjiVerb( 押し当てる, JAP_TRANSITIVE ) // (v1,vt) to push (something) against
 KanjiVerb( 押し付ける, JAP_TRANSITIVE ) // (v1,vt) to press/to push/to force/(P)
 KanjiVerb( 押し分ける, JAP_TRANSITIVE ) // (v1,vt) to push aside
 KanjiVerb( 押し返す, JAP_TRANSITIVE ) // (v5s,vt) to force back/to jostle
 KanjiVerb( 押し戻す, JAP_TRANSITIVE ) // (v5s,vt) to push back
 KanjiVerb( 押し立てる, JAP_TRANSITIVE ) // (v1,vt) to set up/to support
 KanjiVerb( 押し流す, JAP_TRANSITIVE ) // (v5s,vt) to wash away
 KanjiVerb( 押し留める, JAP_TRANSITIVE ) // (v1,vt) to stop
 KanjiVerb( 押す, JAP_TRANSITIVE ) // (v5s,vt) to push/to press/to stamp (i.e. a passport)/(P)
 KanjiVerb( 押っ被せる, JAP_TRANSITIVE ) // (v1,vt) to put a thing on top of another/to cover/to lay something on
 KanjiVerb( 押っ立てる, JAP_TRANSITIVE ) // (v1,vt) to raise/to set up
 KanjiVerb( 押隠す, JAP_TRANSITIVE ) // (v5s,vt) to cover up/to conceal
 KanjiVerb( 押込める, JAP_TRANSITIVE ) // (v1,vt) to shut up/to imprison
 KanjiVerb( 押殺す, JAP_TRANSITIVE ) // (v5s,vt) to crush to death/to stifle to death/to squeeze to death
 KanjiVerb( 押出す, JAP_TRANSITIVE ) // (v5s,vt) to crowd out/to push out/to squeeze out
 KanjiVerb( 押上げる, JAP_TRANSITIVE ) // (v1,vt) to boost/to force up/to push up
 KanjiVerb( 押通す, JAP_TRANSITIVE ) // (v5s,vt) to persist in/to carry out/to have one's own way/to push through/to carry through
 KanjiVerb( 押潰す, JAP_TRANSITIVE ) // (v5s,vt) to squash/to crush/to flatten
 KanjiVerb( 押倒す, JAP_TRANSITIVE ) // (v5s,vt) to push down
 KanjiVerb( 押返す, JAP_TRANSITIVE ) // (v5s,vt) to force back/to jostle
 KanjiVerb( 押戻す, JAP_TRANSITIVE ) // (v5s,vt) to push back
 KanjiVerb( 押流す, JAP_TRANSITIVE ) // (v5s,vt) to wash away
 KanjiVerb( 横たえる, JAP_TRANSITIVE ) // (v1,vt) to lie down/to lay (oneself) down
 KanjiVerb( 殴りつける, JAP_TRANSITIVE ) // (v1,vt) to beat (someone in battle)
 KanjiVerb( 殴り飛ばす, JAP_TRANSITIVE ) // (v5s,vt) to knock a person off his feet
 KanjiVerb( 殴り付ける, JAP_TRANSITIVE ) // (v1,vt) to beat (someone in battle)
 KanjiVerb( 卸す, JAP_TRANSITIVE ) // (v5s,vt) to sell wholesale/grated (vegetables)/(P)
 KanjiVerb( 温める, JAP_TRANSITIVE ) // (v1,vt) to cool something down (e.g., by adding water)
 KanjiVerb( 下げる, JAP_TRANSITIVE ) // (v1,vt) to hang/to lower/to move back/to wear/to dismiss/to grant/(P)
 KanjiVerb( 下げ渡す, JAP_TRANSITIVE ) // (v5s,vt) to make a (government) grant/to release (a criminal)
 KanjiVerb( 下す, JAP_TRANSITIVE ) // (v5s,vt) to lower/to let go down/(P)
 KanjiVerb( 下ろす, JAP_TRANSITIVE ) // (v5s,vt) (1) to take down (e.g., flag)/to launch (e.g., boat)/to drop/to lower (e.g., ladder)/to let (a person) off/to unload/to discharge/(2) to withdraw money from an account/(3) to wear (clothing) for the first time/(P)
 KanjiVerb( 化かす, JAP_TRANSITIVE ) // (v5s,vt) to bewitch/to confuse/to enchant/to delude
 KanjiVerb( 加える, JAP_TRANSITIVE ) // (v1,vt) to append/to sum up/to add (up)/to include/to increase/to inflict/(P)
 KanjiVerb( 歌い上げる, JAP_TRANSITIVE ) // (v1,vt) to sing at the top of one's voice/to express one's feelings fully in a poem
 KanjiVerb( 歌う, JAP_TRANSITIVE ) // (v5u,vt) to sing/(P)
 KanjiVerb( 苛む, JAP_TRANSITIVE ) // (v5m,vt) to torment/to torture/to harass
 KanjiVerb( 苛める, JAP_TRANSITIVE ) // (v1,vt) to tease/to torment/to persecute/to chastise/(P)
 KanjiVerb( 苛立てる, JAP_TRANSITIVE ) // (v1,vt) to irritate/to exasperate
 KanjiVerb( 荷なう, JAP_TRANSITIVE ) // (v5u,vt) to carry on shoulder/to bear (burden)/to shoulder (gun)
 KanjiVerb( 課す, JAP_TRANSITIVE ) // (v5s,vt) to impose
 KanjiVerb( 過ごす, JAP_TRANSITIVE ) // (v5s,vt) to pass/to spend/to go through/to tide over/(P)
 KanjiVerb( 画く, JAP_TRANSITIVE ) // (v5k,vt) to draw/to paint/to sketch/to depict/to describe
 KanjiVerb( 会わせる, JAP_TRANSITIVE ) // (v1,vt) to make (someone) to meet/to expose to/to subject to
 KanjiVerb( 解かす, JAP_TRANSITIVE ) // (v5s,vt) (1) to comb out/(2) to melt/(P)
 KanjiVerb( 解きほぐす, JAP_TRANSITIVE ) // (v5s,vt) (1) to disentangle/to unravel/(2) to relax someone/(P)
 KanjiVerb( 解き解す, JAP_TRANSITIVE ) // (v5s,vt) (1) to disentangle/to unravel/(2) to relax someone
 KanjiVerb( 解き放す, JAP_TRANSITIVE ) // (v5s,vt) to liberate/to set free
 KanjiVerb( 解き放つ, JAP_TRANSITIVE ) // (v5t,vt) to release
 KanjiVerb( 解き明かす, JAP_TRANSITIVE ) // (v5s,vt) to explain/to dispel doubts
 KanjiVerb( 解く, JAP_TRANSITIVE ) // (v5k,vt) to unfasten/to untie/to unwrap (e.g. parcel)/(P)
 KanjiVerb( 解ぐす, JAP_TRANSITIVE ) // (v5s,vt) to unfasten
 KanjiVerb( 解す, JAP_TRANSITIVE ) // (v5s,vt) to unfasten
 KanjiVerb( 解せる, JAP_TRANSITIVE ) // (v1,vt) to understand/to comprehend
 KanjiVerb( 解解す, JAP_TRANSITIVE ) // (v5s,vt) (1) to disentangle/to unravel/(2) to relax someone
 KanjiVerb( 回す, JAP_TRANSITIVE ) // (v5s,vt) to turn/to revolve/(P)
 KanjiVerb( 壊す, JAP_TRANSITIVE ) // (v5s,vt) to break/to break down/(P)
 KanjiVerb( 怪しむ, JAP_TRANSITIVE ) // (v5m,vt) to suspect/(P)
 KanjiVerb( 悔いる, JAP_TRANSITIVE ) // (v1,vt) to regret/(P)
 KanjiVerb( 悔い改める, JAP_TRANSITIVE ) // (v1,vt) to repent/to be penitent
 KanjiVerb( 悔やむ, JAP_TRANSITIVE ) // (v5m,vt) to mourn/(P)
 KanjiVerb( 悔改める, JAP_TRANSITIVE ) // (v1,vt) to repent/to be penitent
 KanjiVerb( 懐かしむ, JAP_TRANSITIVE ) // (v5m,vt) to yearn for (miss) someone (thing)/(P)
 KanjiVerb( 懐く, JAP_TRANSITIVE ) // (v5k,vt) to become emotionally attached
 KanjiVerb( 懐ける, JAP_TRANSITIVE ) // (v1,vt) to win over/to win another's heart
 KanjiVerb( 戒める, JAP_TRANSITIVE ) // (v1,vt) to admonish/to remonstrate/(P)
 KanjiVerb( 拐う, JAP_TRANSITIVE ) // (v5u,vt) to carry off/to run away with/to kidnap/to abduct
 KanjiVerb( 拐かす, JAP_TRANSITIVE ) // (v5s,vt) to kidnap
 KanjiVerb( 改む, JAP_TRANSITIVE ) // (v5m,vt) (abbr) to revise/to change
 KanjiVerb( 改める, JAP_TRANSITIVE ) // (v1,vt) to change/to alter/to reform/to revise/(P)
 KanjiVerb( 開く, JAP_TRANSITIVE ) // (v5k,vt) to open (e.g., a bank-account, festival, etc.)/(P)
 KanjiVerb( 開ける, JAP_TRANSITIVE ) // (v1,vt) to become civilized/to become civilised/to become opened up/to be up-to-date/(P)
 KanjiVerb( 開け広げる, JAP_TRANSITIVE ) // (v1,vt) to open wide/to reveal hidden contents
 KanjiVerb( 開け払う, JAP_TRANSITIVE ) // (v5u,vt) to open/to vacate
 KanjiVerb( 開け放す, JAP_TRANSITIVE ) // (v5s,vt) to open wide (doors,windows, etc.)/to fling open
 KanjiVerb( 開け放つ, JAP_TRANSITIVE ) // (v5t,vt) to throw open/to leave open
 KanjiVerb( 外す, JAP_TRANSITIVE ) // (v5s,vt) (1) to unfasten/to undo/(2) to remove/to take off/to deinstall/(3) to bump off (sl)/(P)
 KanjiVerb( 垣間見る, JAP_TRANSITIVE ) // (v1,vt) to take a peep at/to catch a glimpse of/(P)
 KanjiVerb( 拡げる, JAP_TRANSITIVE ) // (v1,vt) to spread/to extend/to expand/to enlarge/to widen/to broaden/to unfold/to open/to unroll
 KanjiVerb( 確かめる, JAP_TRANSITIVE ) // (v1,vt) to ascertain/(P)
 KanjiVerb( 覚え込む, JAP_TRANSITIVE ) // (v5m,vt) to master
 KanjiVerb( 覚ます, JAP_TRANSITIVE ) // (v5s,vt) (1) to awaken/(2) to disabuse/(3) to sober up/(P)
 KanjiVerb( 覚込む, JAP_TRANSITIVE ) // (v5m,vt) to master
 KanjiVerb( 角立てる, JAP_TRANSITIVE ) // (v1,vt) to be sharp/to be pointed
 KanjiVerb( 較べる, JAP_TRANSITIVE ) // (v1,vt) (1) to compare/(2) to calibrate
 KanjiVerb( 隔てる, JAP_TRANSITIVE ) // (v1,vt) to be shut out/to separate/to isolate/(P)
 KanjiVerb( 掛け替える, JAP_TRANSITIVE ) // (v1,vt) to replace/to substitute
 KanjiVerb( 掛け渡す, JAP_TRANSITIVE ) // (v5s,vt) to build (a bridge) over a river
 KanjiVerb( 割く, JAP_TRANSITIVE ) // (v5k,vt) to cut up/to separate/to spare (e.g., time)/to cleave/to sever/to divide/to cede/to alienate/(P)
 KanjiVerb( 割りつける, JAP_TRANSITIVE ) // (v1,vt) to allot/to distribute/to lay out/to divide among/to assign
 KanjiVerb( 割り引く, JAP_TRANSITIVE ) // (v5k,vt) to discount/(P)
 KanjiVerb( 割り込む, JAP_TRANSITIVE ) // (v5m,vt) to cut in/to thrust oneself into/to wedge oneself in/to muscle in on/to interrupt/to disturb/(P)
 KanjiVerb( 割り出す, JAP_TRANSITIVE ) // (v5s,vt) to calculate/to compute/to infer/(P)
 KanjiVerb( 割り当てる, JAP_TRANSITIVE ) // (v1,vt) to assign/to allot/to allocate/to divide among/to distribute/to prorate/(P)
 KanjiVerb( 割り付ける, JAP_TRANSITIVE ) // (v1,vt) to allot/to distribute/to lay out/to divide among/to assign
 KanjiVerb( 割り戻す, JAP_TRANSITIVE ) // (v5s,vt) to rebate/kickback
 KanjiVerb( 割引く, JAP_TRANSITIVE ) // (v5k,vt) to discount/(P)
 KanjiVerb( 割込む, JAP_TRANSITIVE ) // (v5m,vt) to cut in/to thrust oneself into/to wedge oneself in/to muscle in on/to interrupt/to disturb
 KanjiVerb( 割出す, JAP_TRANSITIVE ) // (v5s,vt) to calculate/to compute/to infer/(P)
 KanjiVerb( 割当てる, JAP_TRANSITIVE ) // (v1,vt) to assign/to allot/to allocate/to divide among/to distribute/to prorate/(P)
 KanjiVerb( 割付ける, JAP_TRANSITIVE ) // (v1,vt) to allot/to distribute/to lay out/to divide among/to assign
 KanjiVerb( 割付る, JAP_TRANSITIVE ) // (v1,vt) to allot/to distribute/to lay out/to divide among/to assign
 KanjiVerb( 割戻す, JAP_TRANSITIVE ) // (v5s,vt) to rebate/kickback
 KanjiVerb( 括りつける, JAP_TRANSITIVE ) // (v1,vt) to fasten (a person) to
 KanjiVerb( 括り付ける, JAP_TRANSITIVE ) // (v1,vt) to fasten (a person) to
 KanjiVerb( 活かす, JAP_TRANSITIVE ) // (v5s,vt) to revive/to resuscitate/to make use of
 KanjiVerb( 活ける, JAP_TRANSITIVE ) // (v1,vt) to arrange (flowers)
 KanjiVerb( 滑らす, JAP_TRANSITIVE ) // (v5s,vt) to let something slip/to slide/to glide
 KanjiVerb( 叶える, JAP_TRANSITIVE ) // (v1,vt) to grant (request, wish)/(P)
 KanjiVerb( 噛みこなす, JAP_TRANSITIVE ) // (v5s,vt) to chew/to digest
 KanjiVerb( 噛み砕く, JAP_TRANSITIVE ) // (v5k,vt) (1) to crunch/to masticate/(2) to simplify/to explain plainly
 KanjiVerb( 噛み殺す, JAP_TRANSITIVE ) // (v5s,vt) (1) to stifle a smile, yawn, etc./(2) to bite to death
 KanjiVerb( 噛み熟す, JAP_TRANSITIVE ) // (v5s,vt) to chew/to digest
 KanjiVerb( 噛み潰す, JAP_TRANSITIVE ) // (v5s,vt) to chew up
 KanjiVerb( 噛み締める, JAP_TRANSITIVE ) // (v1,vt) (1) to chew thoroughly/(2) to reflect upon/to digest
 KanjiVerb( 噛み付く, JAP_TRANSITIVE ) // (v5k,vt) to bite (at)/to snap at/to snarl at/(P)
 KanjiVerb( 噛み分ける, JAP_TRANSITIVE ) // (v1,vt) to taste/to distinguish/to understand
 KanjiVerb( 噛む, JAP_TRANSITIVE ) // (v5m,vt) to bite/to chew/to gnaw/(P)
 KanjiVerb( 噛砕く, JAP_TRANSITIVE ) // (v5k,vt) (1) to crunch/to masticate/(2) to simplify/to explain plainly
 KanjiVerb( 噛殺す, JAP_TRANSITIVE ) // (v5s,vt) (1) to stifle a smile, yawn, etc./(2) to bite to death
 KanjiVerb( 噛熟す, JAP_TRANSITIVE ) // (v5s,vt) to chew/to digest
 KanjiVerb( 噛潰す, JAP_TRANSITIVE ) // (v5s,vt) to chew up
 KanjiVerb( 噛締める, JAP_TRANSITIVE ) // (v1,vt) (1) to chew thoroughly/(2) to reflect upon/to digest
 KanjiVerb( 噛付く, JAP_TRANSITIVE ) // (v5k,vt) to bite (at)/to snap at/to snarl at
 KanjiVerb( 噛分ける, JAP_TRANSITIVE ) // (v1,vt) to taste/to distinguish/to understand
 KanjiVerb( 刈り干す, JAP_TRANSITIVE ) // (v5s,vt) to cut and dry (in the sun)
 KanjiVerb( 刈り込む, JAP_TRANSITIVE ) // (v5m,vt) to cut/to dress/to prune/to trim/to clip/(P)
 KanjiVerb( 刈り上げる, JAP_TRANSITIVE ) // (v1,vt) to reap completely/to trim up (the hair)/to dress up
 KanjiVerb( 刈り入れる, JAP_TRANSITIVE ) // (v1,vt) to harvest/to reap
 KanjiVerb( 刈り葺く, JAP_TRANSITIVE ) // (v5k,vt) to thatch (a roof)
 KanjiVerb( 乾かす, JAP_TRANSITIVE ) // (v5s,vt) to dry (clothes, etc.)/to desiccate/(P)
 KanjiVerb( 乾す, JAP_TRANSITIVE ) // (v5s,vt) to air/to dry/to desiccate/to drain (off)/to drink up
 KanjiVerb( 勘える, JAP_TRANSITIVE ) // (v1,vt) to consider/to think about
 KanjiVerb( 勧める, JAP_TRANSITIVE ) // (v1,vt) to recommend/to advise/to encourage/to offer (wine)/(P)
 KanjiVerb( 巻きつける, JAP_TRANSITIVE ) // (v1,vt) to wreathe (e.g rope)
 KanjiVerb( 巻き込む, JAP_TRANSITIVE ) // (v5m,vt) to roll up/to involve/to enfold/to swallow up/to drag into/(P)
 KanjiVerb( 巻き上げる, JAP_TRANSITIVE ) // (v1,vt) (1) to roll up/to hoist/to heave up/(2) to take away/(3) to blow up (dust)
 KanjiVerb( 巻き付ける, JAP_TRANSITIVE ) // (v1,vt) to wreathe (e.g rope)
 KanjiVerb( 巻き戻す, JAP_TRANSITIVE ) // (v5s,vt) to rewind
 KanjiVerb( 巻き揚げる, JAP_TRANSITIVE ) // (v1,vt) (1) to roll up/to hoist/to heave up/(2) to take away/(3) to blow up (dust)
 KanjiVerb( 巻込む, JAP_TRANSITIVE ) // (v5m,vt) to roll up/to involve/to enfold/to swallow up/to drag into/(P)
 KanjiVerb( 巻戻す, JAP_TRANSITIVE ) // (v5s,vt) to rewind
 KanjiVerb( 喚び出す, JAP_TRANSITIVE ) // (v5s,vt) (1) to summon/to call (e.g., phone)/(2) to invoke
 KanjiVerb( 堪える, JAP_TRANSITIVE ) // (v1,vi,vt) (1) to bear/to stand/to endure/to put up with/(v1,vi) (2) to support/to withstand/to resist/to brave/(v1,vi) (3) to be fit for/to be equal to/(P)
 KanjiVerb( 堪え忍ぶ, JAP_TRANSITIVE ) // (v5b,vt) to put up with/to endure/to bear patiently
 KanjiVerb( 寛げる, JAP_TRANSITIVE ) // (v1,vt) to loose/to ease/to relax
 KanjiVerb( 干し固める, JAP_TRANSITIVE ) // (v1,vt) to dry until stiff
 KanjiVerb( 干す, JAP_TRANSITIVE ) // (v5s,vt) to air/to dry/to desiccate/to drain (off)/to drink up/(P)
 KanjiVerb( 慣らす, JAP_TRANSITIVE ) // (v5s,vt) to accustom/(P)
 KanjiVerb( 憾む, JAP_TRANSITIVE ) // (v5m,vt) to curse/to feel bitter
 KanjiVerb( 換える, JAP_TRANSITIVE ) // (v1,vt) to exchange/to interchange/to substitute/to replace/(P)
 KanjiVerb( 甘やかす, JAP_TRANSITIVE ) // (v5s,vt) to pamper/to spoil/(P)
 KanjiVerb( 看做す, JAP_TRANSITIVE ) // (v5s,vt) to consider as/to regard/to be deemed (as)
 KanjiVerb( 緩める, JAP_TRANSITIVE ) // (v1,vt) to loosen/to slow down/(P)
 KanjiVerb( 観ずる, JAP_TRANSITIVE ) // (vz,vt) to view/to contemplate
 KanjiVerb( 諌める, JAP_TRANSITIVE ) // (v1,vt) to remonstrate/to warn not to do something
 KanjiVerb( 貫き通す, JAP_TRANSITIVE ) // (v5s,vt) to enforce (one's) will/(P)
 KanjiVerb( 貫く, JAP_TRANSITIVE ) // (v5k,vt) to go through/(P)
 KanjiVerb( 還す, JAP_TRANSITIVE ) // (v5s,vt) to send back
 KanjiVerb( 鑑みる, JAP_TRANSITIVE ) // (v1,vt) to heed/to take into account/to learn from/to take warning from/in view of/in the light of
 KanjiVerb( 間違える, JAP_TRANSITIVE ) // (v1,vt) (1) to make a mistake (in)/to commit an error (e.g., in calculation)/(2) to confuse/to mistake something for something else/(P)
 KanjiVerb( 間引く, JAP_TRANSITIVE ) // (v5k,vt) to thin out/to cull/to run on a curtailed schedule
 KanjiVerb( 関係付ける, JAP_TRANSITIVE ) // (v1,vt) to relate to/to connect with
 KanjiVerb( 陥れる, JAP_TRANSITIVE ) // (v1,vt) to tempt/to ensnare
 KanjiVerb( 丸める, JAP_TRANSITIVE ) // (v1,vt) to make round/to round off/to roll up/to curl up/to seduce/to cajole/to explain away/(P)
 KanjiVerb( 丸め込む, JAP_TRANSITIVE ) // (v5m,vt) (1) to coax/to seduce/(2) to roll up and put in (to something)/to bundle up/(P)
 KanjiVerb( 含ませる, JAP_TRANSITIVE ) // (v1,vt) to soak/to saturate/to suckle/to make one hold something in the mouth/to include/to instruct/to make one understand
 KanjiVerb( 含める, JAP_TRANSITIVE ) // (v1,vt) to include/to instruct/to make one understand/to put in one's mouth/(P)
 KanjiVerb( 玩ぶ, JAP_TRANSITIVE ) // (v5b,vt) to play with/to trifle with
 KanjiVerb( 翫ぶ, JAP_TRANSITIVE ) // (v5b,vt) to play with/to trifle with
 KanjiVerb( 願い下げる, JAP_TRANSITIVE ) // (v1,vt) to withdraw a request
 KanjiVerb( 願い出る, JAP_TRANSITIVE ) // (v1,vt) to apply for
 KanjiVerb( 願う, JAP_TRANSITIVE ) // (v5u,vt) to desire/to wish/to request/to beg/to hope/to implore/(P)
 KanjiVerb( 企てる, JAP_TRANSITIVE ) // (v1,vt) to plan/to plot/to propose/to design/to intend/to contemplate/to attempt/to undertake/(P)
 KanjiVerb( 企む, JAP_TRANSITIVE ) // (v5m,vt) (uk) to scheme/to plan/to play a trick/to invent/to conspire/to frame up/(P)
 KanjiVerb( 危める, JAP_TRANSITIVE ) // (v1,vt) to wound/to murder
 KanjiVerb( 寄こす, JAP_TRANSITIVE ) // (v5s,vt) (1) to send/to forward/(2) to hand over (e.g., money)
 KanjiVerb( 寄せつける, JAP_TRANSITIVE ) // (v1,vt) to get close to
 KanjiVerb( 寄せる, JAP_TRANSITIVE ) // (v1,vt) (1) to come near/to let someone approach/(2) to collect/to gather/to add/to put aside/(P)
 KanjiVerb( 寄せ集める, JAP_TRANSITIVE ) // (v1,vt) to put together/to gather/to collect/to scrape together
 KanjiVerb( 寄せ付ける, JAP_TRANSITIVE ) // (v1,vt) to get close to
 KanjiVerb( 寄越す, JAP_TRANSITIVE ) // (v5s,vt) (1) to send/to forward/(2) to hand over (e.g., money)/(P)
 KanjiVerb( 忌み嫌う, JAP_TRANSITIVE ) // (v5u,vt) to detest/to abhor/to loathe
 KanjiVerb( 忌嫌う, JAP_TRANSITIVE ) // (v5u,vt) to detest/to abhor/to loathe
 KanjiVerb( 棄てる, JAP_TRANSITIVE ) // (v1,vt) to throw away/to cast aside/to abandon/to resign
 KanjiVerb( 帰す, JAP_TRANSITIVE ) // (v5s,vt) to send back/(P)
 KanjiVerb( 気にかける, JAP_TRANSITIVE ) // (v1,vt) to weigh on one's mind/to trouble one's heart/to be concerned about/to worry about
 KanjiVerb( 気に掛ける, JAP_TRANSITIVE ) // (v1,vt) to weigh on one's mind/to trouble one's heart/to be concerned about/to worry about
 KanjiVerb( 貴ぶ, JAP_TRANSITIVE ) // (v5b,vt) to value/to prize/to esteem/(P)
 KanjiVerb( 起こす, JAP_TRANSITIVE ) // (v5s,vt) to raise/to cause/to wake someone/(P)
 KanjiVerb( 輝かす, JAP_TRANSITIVE ) // (v5s,vt) to light up/to brighten
 KanjiVerb( 戯かす, JAP_TRANSITIVE ) // (v5s,vt) to call for jokes
 KanjiVerb( 擬える, JAP_TRANSITIVE ) // (v1,vt) to pattern after/to liken to/to imitate
 KanjiVerb( 欺く, JAP_TRANSITIVE ) // (v5k,vt) to deceive/(P)
 KanjiVerb( 疑う, JAP_TRANSITIVE ) // (v5u,vt) to doubt/to distrust/to be suspicious of/to suspect/(P)
 KanjiVerb( 義務付ける, JAP_TRANSITIVE ) // (v1,vt) to obligate
 KanjiVerb( 掬い上げる, JAP_TRANSITIVE ) // (v1,vt) to dip or scoop up
 KanjiVerb( 掬う, JAP_TRANSITIVE ) // (v5u,vt) to scoop/to ladle out/(P)
 KanjiVerb( 喫う, JAP_TRANSITIVE ) // (v5u,vt) to smoke/to breathe in/to suck
 KanjiVerb( 詰め合せる, JAP_TRANSITIVE ) // (v1,vt) to pack an assortment of goods, etc.
 KanjiVerb( 詰め合わせる, JAP_TRANSITIVE ) // (v1,vt) to pack an assortment of goods, etc.
 KanjiVerb( 詰め込む, JAP_TRANSITIVE ) // (v5m,vt) to cram/to stuff/to jam/to squeeze/to pack/to crowd/(P)
 KanjiVerb( 詰め替える, JAP_TRANSITIVE ) // (v1,vt) to repack/to refill
 KanjiVerb( 詰合せる, JAP_TRANSITIVE ) // (v1,vt) to pack an assortment of goods, etc.
 KanjiVerb( 詰合わせる, JAP_TRANSITIVE ) // (v1,vt) to pack an assortment of goods, etc.
 KanjiVerb( 詰込む, JAP_TRANSITIVE ) // (v5m,vt) to cram/to stuff/to jam/to squeeze/to pack/to crowd
 KanjiVerb( 詰替える, JAP_TRANSITIVE ) // (v1,vt) to repack/to refill
 KanjiVerb( 却ける, JAP_TRANSITIVE ) // (v1,vt) to repel/to drive away/to repulse/to reject
 KanjiVerb( 虐げる, JAP_TRANSITIVE ) // (v1,vt) to oppress/(P)
 KanjiVerb( 逆立てる, JAP_TRANSITIVE ) // (v1,vt) to ruffle (up)
 KanjiVerb( 休める, JAP_TRANSITIVE ) // (v1,vt) to rest/to suspend/to give relief/(P)
 KanjiVerb( 及ぼす, JAP_TRANSITIVE ) // (v5s,vt) to exert/to cause/to exercise/(P)
 KanjiVerb( 吸いこむ, JAP_TRANSITIVE ) // (v5m,vt) (1) to inhale/to breathe in/to suck up/to imbibe/(2) to absorb/to soak up
 KanjiVerb( 吸いつける, JAP_TRANSITIVE ) // (v1,vt) to attract/to be used to
 KanjiVerb( 吸い寄せる, JAP_TRANSITIVE ) // (v1,vt) to draw in/to attract
 KanjiVerb( 吸い込む, JAP_TRANSITIVE ) // (v5m,vt) (1) to inhale/to breathe in/to suck up/to imbibe/(2) to absorb/to soak up/(P)
 KanjiVerb( 吸い出す, JAP_TRANSITIVE ) // (v5s,vt) to suck (or draw) out/to aspirate
 KanjiVerb( 吸い上げる, JAP_TRANSITIVE ) // (v1,vt) (1) to pump off or out/to suck up or out/to siphon off (incl. wealth)/(2) to take up others' views and opinions
 KanjiVerb( 吸い付ける, JAP_TRANSITIVE ) // (v1,vt) to attract/to be used to
 KanjiVerb( 吸う, JAP_TRANSITIVE ) // (v5u,vt) to smoke/to breathe in/to suck/(P)
 KanjiVerb( 吸寄せる, JAP_TRANSITIVE ) // (v1,vt) to draw in/to attract
 KanjiVerb( 吸込む, JAP_TRANSITIVE ) // (v5m,vt) (1) to inhale/to breathe in/to suck up/to imbibe/(2) to absorb/to soak up
 KanjiVerb( 吸出す, JAP_TRANSITIVE ) // (v5s,vt) to suck (or draw) out/to aspirate
 KanjiVerb( 吸上げる, JAP_TRANSITIVE ) // (v1,vt) (1) to pump off or out/to suck up or out/to siphon off (incl. wealth)/(2) to take up others' views and opinions
 KanjiVerb( 吸付ける, JAP_TRANSITIVE ) // (v1,vt) to attract/to be used to
 KanjiVerb( 急き立てる, JAP_TRANSITIVE ) // (v1,vt) to hurry (up)/to press/to urge on
 KanjiVerb( 急立てる, JAP_TRANSITIVE ) // (v1,vt) to hurry (up)/to press/to urge on
 KanjiVerb( 救い出す, JAP_TRANSITIVE ) // (v5s,vt) to rescue/to free
 KanjiVerb( 救う, JAP_TRANSITIVE ) // (v5u,vt) to rescue from/to help out of/(P)
 KanjiVerb( 救ける, JAP_TRANSITIVE ) // (v1,vt) to help/to save/to rescue/to give relief to/to spare (life)/to reinforce/to promote/to abet
 KanjiVerb( 求む, JAP_TRANSITIVE ) // (v5m,vt) to want/to seek/to request
 KanjiVerb( 求める, JAP_TRANSITIVE ) // (v1,vt) to seek/to request/to demand/to want/to wish for/to search for/to pursue (pleasure)/to hunt (a job)/to buy/(P)
 KanjiVerb( 汲み干す, JAP_TRANSITIVE ) // (v5s,vt) to empty out/to drain out/to pump dry
 KanjiVerb( 汲み込む, JAP_TRANSITIVE ) // (v5m,vt) to fill with water
 KanjiVerb( 汲み出す, JAP_TRANSITIVE ) // (v5s,vt) to pump out/to bail (water)
 KanjiVerb( 汲み上げる, JAP_TRANSITIVE ) // (v1,vt) to draw
 KanjiVerb( 汲み分ける, JAP_TRANSITIVE ) // (v1,vt) to apportion drawn water/to show understanding
 KanjiVerb( 汲む, JAP_TRANSITIVE ) // (v5m,vt) (1) to draw (water)/to ladle/to dip/to scoop/to pump/(2) to have a drink together/(3) to consider/to sympathize with/to sympathise with/(P)
 KanjiVerb( 汲干す, JAP_TRANSITIVE ) // (v5s,vt) to empty out/to drain out/to pump dry
 KanjiVerb( 汲込む, JAP_TRANSITIVE ) // (v5m,vt) to fill with water
 KanjiVerb( 汲出す, JAP_TRANSITIVE ) // (v5s,vt) to pump out/to bail (water)
 KanjiVerb( 汲上げる, JAP_TRANSITIVE ) // (v1,vt) to draw
 KanjiVerb( 泣かせる, JAP_TRANSITIVE ) // (v1,vt) (1) to make someone cry/to move someone to tears/(2) to grieve
 KanjiVerb( 泣き腫らす, JAP_TRANSITIVE ) // (v5s,vt) to weep one's eyes out
 KanjiVerb( 泣き暮す, JAP_TRANSITIVE ) // (v5s,vt) to spend one's days in tears and sorrow
 KanjiVerb( 泣き暮らす, JAP_TRANSITIVE ) // (v5s,vt) to spend one's days in tears and sorrow
 KanjiVerb( 泣き明かす, JAP_TRANSITIVE ) // (v5s,vt) to weep the night out/to weep all night
 KanjiVerb( 泣き明す, JAP_TRANSITIVE ) // (v5s,vt) to weep the night out/to weep all night
 KanjiVerb( 泣腫らす, JAP_TRANSITIVE ) // (v5s,vt) to weep one's eyes out
 KanjiVerb( 泣暮す, JAP_TRANSITIVE ) // (v5s,vt) to spend one's days in tears and sorrow
 KanjiVerb( 泣明す, JAP_TRANSITIVE ) // (v5s,vt) to weep the night out/to weep all night
 KanjiVerb( 究める, JAP_TRANSITIVE ) // (v1,vt) (1) to carry to extremes/to go to the end of something/(2) to investigate thoroughly/to master
 KanjiVerb( 窮める, JAP_TRANSITIVE ) // (v1,vt) (1) to carry to extremes/to go to the end of something/(2) to investigate thoroughly/to master
 KanjiVerb( 去なす, JAP_TRANSITIVE ) // (v5s,vt) to parry/to sidestep/to let go/to chase away
 KanjiVerb( 拒む, JAP_TRANSITIVE ) // (v5m,vt) to refuse/to reject/to decline/(P)
 KanjiVerb( 挙げる, JAP_TRANSITIVE ) // (v1,vt) (1) to raise/to fly/(2) to give (an example)/(P)
 KanjiVerb( 許す, JAP_TRANSITIVE ) // (v5s,vt) (1) to permit/to allow/to approve/(2) to exempt (from fine)/to excuse (from)/to pardon/to release/to let off/(3) to confide in/(4) to give up/to yield/(P)
 KanjiVerb( 距てる, JAP_TRANSITIVE ) // (v1,vt) to be shut out/to separate/to isolate
 KanjiVerb( 供える, JAP_TRANSITIVE ) // (v1,vt) to offer/to sacrifice/to dedicate/(P)
 KanjiVerb( 競り上げる, JAP_TRANSITIVE ) // (v1,vt) to bid up the price of
 KanjiVerb( 強いる, JAP_TRANSITIVE ) // (v1,vt) to force/to compel/to coerce/(P)
 KanjiVerb( 強める, JAP_TRANSITIVE ) // (v1,vt) to strengthen/to emphasize/to emphasise/(P)
 KanjiVerb( 挟み込む, JAP_TRANSITIVE ) // (v5m,vt) to insert
 KanjiVerb( 挟み上げる, JAP_TRANSITIVE ) // (v1,vt) to pick up (with chopsticks)/to take
 KanjiVerb( 挟む, JAP_TRANSITIVE ) // (v5m,vt) to interpose/to hold between/to insert/(P)
 KanjiVerb( 教える, JAP_TRANSITIVE ) // (v1,vt) to teach/to inform/to instruct/(P)
 KanjiVerb( 教え込む, JAP_TRANSITIVE ) // (v5m,vt) to train to/to give an idea to
 KanjiVerb( 狭める, JAP_TRANSITIVE ) // (v1,vt) to narrow/to reduce/to contract/(P)
 KanjiVerb( 矯める, JAP_TRANSITIVE ) // (v1,vt) to straighten/to correct/to cure/to falsify
 KanjiVerb( 脅かす, JAP_TRANSITIVE ) // (v5s,vt) to threaten/to coerce/(P)
 KanjiVerb( 脅す, JAP_TRANSITIVE ) // (v5s,vt) to threaten/to menace/(P)
 KanjiVerb( 興す, JAP_TRANSITIVE ) // (v5s,vt) to revive/to retrieve (fortunes)/to raise up/(P)
 KanjiVerb( 驚かす, JAP_TRANSITIVE ) // (v5s,vt) to surprise/to frighten/to create a stir/(P)
 KanjiVerb( 仰ぎ見る, JAP_TRANSITIVE ) // (v1,vt) to look up
 KanjiVerb( 仰ぐ, JAP_TRANSITIVE ) // (v5g,vt) to look up (to)/to respect/to depend on/to ask for/to seek/to revere/to drink/to take/(P)
 KanjiVerb( 仰しゃる, JAP_TRANSITIVE ) // (v5aru,vt) (hon) (uk) to say/to speak/to tell/to talk
 KanjiVerb( 仰せつける, JAP_TRANSITIVE ) // (v1,vt) to command/to request/to appoint
 KanjiVerb( 仰せ付ける, JAP_TRANSITIVE ) // (v1,vt) to command/to request/to appoint
 KanjiVerb( 仰っしゃる, JAP_TRANSITIVE ) // (v5aru,vt) (hon) (uk) to say/to speak/to tell/to talk/(P)
 KanjiVerb( 仰のける, JAP_TRANSITIVE ) // (v1,vt) to turn up (one's face or a card)
 KanjiVerb( 仰る, JAP_TRANSITIVE ) // (v5aru,vt) (hon) (uk) to say/to speak/to tell/to talk
 KanjiVerb( 仰見る, JAP_TRANSITIVE ) // (v1,vt) to look up
 KanjiVerb( 仰向ける, JAP_TRANSITIVE ) // (v1,vt) to turn up (one's face)
 KanjiVerb( 仰有る, JAP_TRANSITIVE ) // (v5aru,vt) (hon) (uk) to say/to speak/to tell/to talk
 KanjiVerb( 凝らす, JAP_TRANSITIVE ) // (v5s,vt) to concentrate/to devote/to apply/to strain/to rack
 KanjiVerb( 凝らせる, JAP_TRANSITIVE ) // (v1,vt) to freeze/to congeal
 KanjiVerb( 曲げる, JAP_TRANSITIVE ) // (v1,vt) to bend/to crook/to lean/(P)
 KanjiVerb( 極める, JAP_TRANSITIVE ) // (v1,vt) (1) to carry to extremes/to go to the end of something/(2) to investigate thoroughly/to master/(P)
 KanjiVerb( 極め込む, JAP_TRANSITIVE ) // (v5m,vt) to take for granted/to assume/to pretend
 KanjiVerb( 勤める, JAP_TRANSITIVE ) // (v1,vt) (1) to serve/to fill a post/to serve under/to work (for)/(2) to exert oneself/to endeavor/to endeavour/to be diligent/(3) to play (the part of)/(P)
 KanjiVerb( 勤め上げる, JAP_TRANSITIVE ) // (v1,vt) to serve out one's apprenticeship/to serve out one's time
 KanjiVerb( 均す, JAP_TRANSITIVE ) // (v5s,vt) to make even/to make smooth/to make level
 KanjiVerb( 禁じる, JAP_TRANSITIVE ) // (v1,vt) to prohibit/(P)
 KanjiVerb( 禁ずる, JAP_TRANSITIVE ) // (vz,vt) to forbid/to suppress/(P)
 KanjiVerb( 禁める, JAP_TRANSITIVE ) // (v1,vt) to remonstrate/to warn not to do something
 KanjiVerb( 謹む, JAP_TRANSITIVE ) // (v5m,vt) to be careful/to be chaste or discreet/to abstain or refrain/(P)
 KanjiVerb( 近づける, JAP_TRANSITIVE ) // (v1,vt) to bring near/to put close/to let come near/to associate with
 KanjiVerb( 近寄せる, JAP_TRANSITIVE ) // (v1,vt) to bring close to/to associate with/(P)
 KanjiVerb( 近付ける, JAP_TRANSITIVE ) // (v1,vt) to bring near/to put close/to let come near/to associate with/(P)
 KanjiVerb( 苦しめる, JAP_TRANSITIVE ) // (v1,vt) to torment/to harass/to inflict pain/(P)
 KanjiVerb( 駆り集める, JAP_TRANSITIVE ) // (v1,vt) to round up/to gather/to muster/to mobilize/to mobilise
 KanjiVerb( 駆り立てる, JAP_TRANSITIVE ) // (v1,vt) to spur on
 KanjiVerb( 駆集める, JAP_TRANSITIVE ) // (v1,vt) to round up/to gather/to muster/to mobilize/to mobilise
 KanjiVerb( 具える, JAP_TRANSITIVE ) // (v1,vt) (1) to furnish/to provide for/to equip/to install/(2) to have ready/to prepare for/(3) to possess/to have/to be endowed with/to be armed with/(P)
 KanjiVerb( 喰う, JAP_TRANSITIVE ) // (v5u,vt) (male) (vulg) to eat
 KanjiVerb( 喰らう, JAP_TRANSITIVE ) // (v5u,vt) to eat/to drink/to receive (blow)
 KanjiVerb( 屈める, JAP_TRANSITIVE ) // (v1,vt) (uk) to stoop/to bend
 KanjiVerb( 掘り下げる, JAP_TRANSITIVE ) // (v1,vt) to dig down/to delve into/to get to the bottom of (a matter)/to investigate further
 KanjiVerb( 掘り起こす, JAP_TRANSITIVE ) // (v5s,vt) to reclaim/to dig up
 KanjiVerb( 掘り起す, JAP_TRANSITIVE ) // (v5s,vt) to reclaim/to dig up
 KanjiVerb( 掘り出す, JAP_TRANSITIVE ) // (v5s,vt) to dig out/to pick up
 KanjiVerb( 掘り当てる, JAP_TRANSITIVE ) // (v1,vt) to strike/to find/to dig up
 KanjiVerb( 掘り抜く, JAP_TRANSITIVE ) // (v5k,vt) to dig through/to drill into/to excavate
 KanjiVerb( 掘り返す, JAP_TRANSITIVE ) // (v5s,vt) to dig up/to turn up/to tear up
 KanjiVerb( 掘下げる, JAP_TRANSITIVE ) // (v1,vt) to dig down/to delve into/to get to the bottom of (a matter)/to investigate further
 KanjiVerb( 掘起す, JAP_TRANSITIVE ) // (v5s,vt) to reclaim/to dig up
 KanjiVerb( 掘出す, JAP_TRANSITIVE ) // (v5s,vt) to dig out/to pick up
 KanjiVerb( 掘当てる, JAP_TRANSITIVE ) // (v1,vt) to strike/to find/to dig up
 KanjiVerb( 掘抜く, JAP_TRANSITIVE ) // (v5k,vt) to dig through/to drill into/to excavate
 KanjiVerb( 掘返す, JAP_TRANSITIVE ) // (v5s,vt) to dig up/to turn up/to tear up
 KanjiVerb( 繰り越す, JAP_TRANSITIVE ) // (v5s,vt) to carry forward (i.e. on a balance sheet)/to transfer
 KanjiVerb( 繰り延べる, JAP_TRANSITIVE ) // (v1,vt) to postpone/to defer
 KanjiVerb( 繰り下げる, JAP_TRANSITIVE ) // (v1,vt) to defer/to postpone
 KanjiVerb( 繰り回す, JAP_TRANSITIVE ) // (v5s,vt) to roll over (debt)
 KanjiVerb( 繰り寄せる, JAP_TRANSITIVE ) // (v1,vt) to draw towards
 KanjiVerb( 繰り広げる, JAP_TRANSITIVE ) // (v1,vt) to unfold/to open
 KanjiVerb( 繰り込む, JAP_TRANSITIVE ) // (v5m,vt) to march in/to transfer/to send
 KanjiVerb( 繰り出す, JAP_TRANSITIVE ) // (v5s,vt) to draw (a thread)/to sally forth/to send out/(P)
 KanjiVerb( 繰り上げる, JAP_TRANSITIVE ) // (v1,vt) to move up/to advance/(P)
 KanjiVerb( 繰り替える, JAP_TRANSITIVE ) // (v1,vt) to exchange
 KanjiVerb( 繰り入れる, JAP_TRANSITIVE ) // (v1,vt) to transfer/to add
 KanjiVerb( 繰り戻す, JAP_TRANSITIVE ) // (v5s,vt) to put back
 KanjiVerb( 繰越す, JAP_TRANSITIVE ) // (v5s,vt) to carry forward (i.e. on a balance sheet)/to transfer
 KanjiVerb( 繰延べる, JAP_TRANSITIVE ) // (v1,vt) to postpone/to defer
 KanjiVerb( 繰下げる, JAP_TRANSITIVE ) // (v1,vt) to defer/to postpone
 KanjiVerb( 繰回す, JAP_TRANSITIVE ) // (v5s,vt) to roll over (debt)
 KanjiVerb( 繰寄せる, JAP_TRANSITIVE ) // (v1,vt) to draw towards
 KanjiVerb( 繰広げる, JAP_TRANSITIVE ) // (v1,vt) to unfold/to open
 KanjiVerb( 繰込む, JAP_TRANSITIVE ) // (v5m,vt) to march in/to transfer/to send
 KanjiVerb( 繰出す, JAP_TRANSITIVE ) // (v5s,vt) to draw (a thread)/to sally forth/to send out
 KanjiVerb( 繰上げる, JAP_TRANSITIVE ) // (v1,vt) to move up/to advance
 KanjiVerb( 繰替える, JAP_TRANSITIVE ) // (v1,vt) to exchange
 KanjiVerb( 繰入れる, JAP_TRANSITIVE ) // (v1,vt) to transfer/to add
 KanjiVerb( 繰戻す, JAP_TRANSITIVE ) // (v5s,vt) to put back
 KanjiVerb( 傾げる, JAP_TRANSITIVE ) // (v1,vt) to lean/to incline/to tilt/to slant
 KanjiVerb( 恵む, JAP_TRANSITIVE ) // (v5m,vt) to bless/to show mercy to/(P)
 KanjiVerb( 掲げる, JAP_TRANSITIVE ) // (v1,vt) (1) to publish/to print/to carry (an article)/(2) to put up/to hang out/to hoist/to fly (a sail)/to float (a flag)/(P)
 KanjiVerb( 携える, JAP_TRANSITIVE ) // (v1,vt) to carry in one's hand/(P)
 KanjiVerb( 敬う, JAP_TRANSITIVE ) // (v5u,vt) to show respect/to honour/to honor/(P)
 KanjiVerb( 稽える, JAP_TRANSITIVE ) // (v1,vt) to consider/to think about
 KanjiVerb( 継ぎ合せる, JAP_TRANSITIVE ) // (v1,vt) to join together/to patch together
 KanjiVerb( 継ぎ合わせる, JAP_TRANSITIVE ) // (v1,vt) to join together/to patch together
 KanjiVerb( 継ぎ足す, JAP_TRANSITIVE ) // (v5s,vt) to add (coals to a fire)
 KanjiVerb( 継ぐ, JAP_TRANSITIVE ) // (v5g,vt) to succeed (someone in a business or inheritance)/(P)
 KanjiVerb( 継合せる, JAP_TRANSITIVE ) // (v1,vt) to join together/to patch together
 KanjiVerb( 継足す, JAP_TRANSITIVE ) // (v5s,vt) to add (coals to a fire)
 KanjiVerb( 繋ぎ止める, JAP_TRANSITIVE ) // (v1,vt) to tie/to fasten/to hitch
 KanjiVerb( 繋ぐ, JAP_TRANSITIVE ) // (v5g,vt) (uk) to tie/to fasten/to connect/to transfer (phone call)/(P)
 KanjiVerb( 繋げる, JAP_TRANSITIVE ) // (v1,vt) to tie/to fasten/to connect/to transfer (phone call)
 KanjiVerb( 計らう, JAP_TRANSITIVE ) // (v5u,vt) to manage/to arrange/to talk over/to dispose of
 KanjiVerb( 軽んじる, JAP_TRANSITIVE ) // (v1,vt) to look down on/to make light of
 KanjiVerb( 軽んずる, JAP_TRANSITIVE ) // (vz,vt) to despise/to belittle/to look down on
 KanjiVerb( 迎える, JAP_TRANSITIVE ) // (v1,vt) to go out to meet/to accept as a member of a group or family/(P)
 KanjiVerb( 迎え撃つ, JAP_TRANSITIVE ) // (v5t,vt) to ambush/to attack/to meet the enemy/(P)
 KanjiVerb( 迎え入れる, JAP_TRANSITIVE ) // (v1,vt) to show in/to usher in
 KanjiVerb( 撃ち合う, JAP_TRANSITIVE ) // (v5u,vt) (1) to fight/to exchange blows/to rally/(2) to arrange a meeting
 KanjiVerb( 撃ち殺す, JAP_TRANSITIVE ) // (v5s,vt) to shoot to death
 KanjiVerb( 撃ち止める, JAP_TRANSITIVE ) // (v1,vt) to kill/to slay/to shoot to death/to bring down (bird)/(P)
 KanjiVerb( 撃ち落す, JAP_TRANSITIVE ) // (v5s,vt) to knock down/to shoot down/to lop off
 KanjiVerb( 撃ち落とす, JAP_TRANSITIVE ) // (v5s,vt) to knock down/to shoot down/to lop off
 KanjiVerb( 撃殺す, JAP_TRANSITIVE ) // (v5s,vt) to shoot to death
 KanjiVerb( 撃止める, JAP_TRANSITIVE ) // (v1,vt) to kill/to slay/to shoot to death/to bring down (bird)
 KanjiVerb( 撃落す, JAP_TRANSITIVE ) // (v5s,vt) to knock down/to shoot down/to lop off
 KanjiVerb( 欠かす, JAP_TRANSITIVE ) // (v5s,vt) to miss (doing)/to fail (to do)/(P)
 KanjiVerb( 欠く, JAP_TRANSITIVE ) // (v5k,vt) to lack/to break/to crack/to chip/(P)
 KanjiVerb( 決める, JAP_TRANSITIVE ) // (v1,vt) to decide/(P)
 KanjiVerb( 決め込む, JAP_TRANSITIVE ) // (v5m,vt) to take for granted/to assume/to pretend
 KanjiVerb( 決込む, JAP_TRANSITIVE ) // (v5m,vt) to take for granted/to assume/to pretend
 KanjiVerb( 結い上げる, JAP_TRANSITIVE ) // (v1,vt) to wear one's hair up/to arrange one's hair
 KanjiVerb( 結う, JAP_TRANSITIVE ) // (v5u,vt) to do up (hair)/to braid/(P)
 KanjiVerb( 結びつける, JAP_TRANSITIVE ) // (v1,vt) to combine/to join/to tie on/to attach with a knot/to bind (e.g., an address)
 KanjiVerb( 結び合せる, JAP_TRANSITIVE ) // (v1,vt) to tie/to correlate
 KanjiVerb( 結び付ける, JAP_TRANSITIVE ) // (v1,vt) to combine/to join/to tie on/to attach with a knot/to bind (e.g., an address)
 KanjiVerb( 結わえる, JAP_TRANSITIVE ) // (v1,vt) to bind/to fasten/to tie up
 KanjiVerb( 兼ね備える, JAP_TRANSITIVE ) // (v1,vt) to have both/to combine with/(P)
 KanjiVerb( 堅める, JAP_TRANSITIVE ) // (v1,vt) to harden/to freeze/to fortify
 KanjiVerb( 嫌う, JAP_TRANSITIVE ) // (v5u,vt) to hate/to dislike/to loathe/(P)
 KanjiVerb( 建てる, JAP_TRANSITIVE ) // (v1,vt) to build/to construct/(P)
 KanjiVerb( 建て増す, JAP_TRANSITIVE ) // (v5s,vt) to extend (building)/to build on
 KanjiVerb( 建て替える, JAP_TRANSITIVE ) // (v1,vt) to rebuild/to reconstruct
 KanjiVerb( 建て直す, JAP_TRANSITIVE ) // (v5s,vt) to rebuild/to reconstruct
 KanjiVerb( 建直す, JAP_TRANSITIVE ) // (v5s,vt) to rebuild/to reconstruct
 KanjiVerb( 懸ける, JAP_TRANSITIVE ) // (v1,vt) to hang/to construct/to sit/to offer (as a prize)/to put (one's life) on the line/(P)
 KanjiVerb( 懸け隔てる, JAP_TRANSITIVE ) // (v1,vt) to put distance between/to estrange
 KanjiVerb( 捲き上げる, JAP_TRANSITIVE ) // (v1,vt) (1) to roll up/to hoist/to heave up/(2) to take away/(3) to blow up (dust)
 KanjiVerb( 捲し立てる, JAP_TRANSITIVE ) // (v1,vt) to talk on and on
 KanjiVerb( 検める, JAP_TRANSITIVE ) // (v1,vt) to change/to alter/to reform/to revise
 KanjiVerb( 牽く, JAP_TRANSITIVE ) // (v5k,vi,vt) (1) to pull/(2) to draw back/(3) to draw (a card)/(4) to draw (plan, line, etc.)/(5) to catch (cold)/(6) to play (string instr.)/(7) to look up (e.g., dictionary)/to consult/(v5k,vt) (8) to pull (vehicles)
 KanjiVerb( 献げる, JAP_TRANSITIVE ) // (v1,vt) to lift up/to give/to offer/to consecrate/to devote/to sacrifice/to dedicate
 KanjiVerb( 研ぎ澄ます, JAP_TRANSITIVE ) // (v5s,vt) to sharpen/to grind/to whet/to hone/to make keen
 KanjiVerb( 研ぐ, JAP_TRANSITIVE ) // (v5g,vt) to sharpen/to grind/to scour/to hone/to polish/to wash (rice)/(P)
 KanjiVerb( 見い出す, JAP_TRANSITIVE ) // (v5s,vt) to find out/to discover/to notice/to select
 KanjiVerb( 見かける, JAP_TRANSITIVE ) // (v1,vt) to (happen to) see/to notice/to catch sight of
 KanjiVerb( 見せかける, JAP_TRANSITIVE ) // (v1,vt) to pretend/to feign
 KanjiVerb( 見せつける, JAP_TRANSITIVE ) // (v1,vt) to display/to show
 KanjiVerb( 見せびらかす, JAP_TRANSITIVE ) // (v5s,vt) to show off/to flaunt/(P)
 KanjiVerb( 見せる, JAP_TRANSITIVE ) // (v1,vt) to show/to display/(P)
 KanjiVerb( 見せ掛ける, JAP_TRANSITIVE ) // (v1,vt) to pretend/to feign
 KanjiVerb( 見せ付ける, JAP_TRANSITIVE ) // (v1,vt) to display/to show
 KanjiVerb( 見つけだす, JAP_TRANSITIVE ) // (v5s,vt) to find out/to discover/to locate
 KanjiVerb( 見つける, JAP_TRANSITIVE ) // (v1,vt) (1) to discover/to find (e.g., an error in a book)/to come across/to detect/(2) to locate/to find (e.g., something missing)/to find fault/(P)
 KanjiVerb( 見つめる, JAP_TRANSITIVE ) // (v1,vt) (uk) to stare at/to gaze at/to look hard at/to watch intently/to fix one's eyes on/(P)
 KanjiVerb( 見なす, JAP_TRANSITIVE ) // (v5s,vt) to consider as/to regard/to be deemed (as)/(P)
 KanjiVerb( 見る, JAP_TRANSITIVE ) // (v1,vt) (1) to see/to watch/(2) (as an auxiliary verb) to try/(P)
 KanjiVerb( 見違える, JAP_TRANSITIVE ) // (v1,vt) to be beyond recognition/to be quite a difference/(P)
 KanjiVerb( 見逸れる, JAP_TRANSITIVE ) // (v1,vt) to overlook/to fail to recognize/to fail to recognise
 KanjiVerb( 見越す, JAP_TRANSITIVE ) // (v5s,vt) to anticipate/to foresee
 KanjiVerb( 見下げる, JAP_TRANSITIVE ) // (v1,vt) to look down over/to look down on
 KanjiVerb( 見下げ果てる, JAP_TRANSITIVE ) // (v1,vt) to despise/to scorn/to look down on
 KanjiVerb( 見下す, JAP_TRANSITIVE ) // (v5s,vt) to despise/to look down on
 KanjiVerb( 見下ろす, JAP_TRANSITIVE ) // (v5s,vt) to overlook/to command a view of/to look down on something/(P)
 KanjiVerb( 見果てる, JAP_TRANSITIVE ) // (v1,vt) to see through to the finish/to be seen to the end
 KanjiVerb( 見過ごす, JAP_TRANSITIVE ) // (v5s,vt) to let go by/to let pass/to overlook/to miss/(P)
 KanjiVerb( 見過す, JAP_TRANSITIVE ) // (v5s,vt) to let go by/to let pass/to overlook/to miss
 KanjiVerb( 見回す, JAP_TRANSITIVE ) // (v5s,vt) to look around/to survey
 KanjiVerb( 見廻す, JAP_TRANSITIVE ) // (v5s,vt) to look around/to survey
 KanjiVerb( 見開く, JAP_TRANSITIVE ) // (v5k,vt) to open one's eyes
 KanjiVerb( 見覚える, JAP_TRANSITIVE ) // (v1,vt) to remember/to recollect/to recognize/to recognise
 KanjiVerb( 見較べる, JAP_TRANSITIVE ) // (v1,vt) to compare with the eye
 KanjiVerb( 見掛ける, JAP_TRANSITIVE ) // (v1,vt) to (happen to) see/to notice/to catch sight of
 KanjiVerb( 見間違える, JAP_TRANSITIVE ) // (v1,vt) to take A for B/to mistake A for B
 KanjiVerb( 見詰める, JAP_TRANSITIVE ) // (v1,vt) (uk) to stare at/to gaze at/to look hard at/to watch intently/to fix one's eyes on/(P)
 KanjiVerb( 見極める, JAP_TRANSITIVE ) // (v1,vt) to see through/to probe/to make sure of/(P)
 KanjiVerb( 見計らう, JAP_TRANSITIVE ) // (v5u,vt) to choose at one's own discretion
 KanjiVerb( 見兼ねる, JAP_TRANSITIVE ) // (v1,vt) to be unable to let pass unnoticed/to be unable to be indifferent
 KanjiVerb( 見込む, JAP_TRANSITIVE ) // (v5m,vt) to anticipate/to estimate/(P)
 KanjiVerb( 見残す, JAP_TRANSITIVE ) // (v5s,vt) to leave unseen or unread
 KanjiVerb( 見失う, JAP_TRANSITIVE ) // (v5u,vt) to lose sight of/to miss/(P)
 KanjiVerb( 見捨てる, JAP_TRANSITIVE ) // (v1,vt) to abandon/to fail/to desert/(P)
 KanjiVerb( 見受ける, JAP_TRANSITIVE ) // (v1,vt) to catch sight of/to see/to suppose/(P)
 KanjiVerb( 見習う, JAP_TRANSITIVE ) // (v5u,vt) to follow another's example/(P)
 KanjiVerb( 見出す, JAP_TRANSITIVE ) // (v5s,vt) to find out/to discover/to notice/to select
 KanjiVerb( 見出だす, JAP_TRANSITIVE ) // (v5s,vt) to find out/to discover/to notice/to select
 KanjiVerb( 見初める, JAP_TRANSITIVE ) // (v1,vt) to see for the first time/to fall in love at first sight
 KanjiVerb( 見上げる, JAP_TRANSITIVE ) // (v1,vt) to look up at/to raise one's eyes/to admire/(P)
 KanjiVerb( 見据える, JAP_TRANSITIVE ) // (v1,vt) to gaze at/to make sure of
 KanjiVerb( 見澄ます, JAP_TRANSITIVE ) // (v5s,vt) to observe carefully/to make sure
 KanjiVerb( 見晴らす, JAP_TRANSITIVE ) // (v5s,vt) to command a view/(P)
 KanjiVerb( 見繕う, JAP_TRANSITIVE ) // (v5u,vt) to choose (a thing) at one's own discretion
 KanjiVerb( 見損う, JAP_TRANSITIVE ) // (v5u,vt) to misjudge/to mistake/to miss seeing
 KanjiVerb( 見損なう, JAP_TRANSITIVE ) // (v5u,vt) to misjudge/to mistake/to miss seeing/(P)
 KanjiVerb( 見通す, JAP_TRANSITIVE ) // (v5s,vt) to see without obstruction/to forecast/to predict
 KanjiVerb( 見定める, JAP_TRANSITIVE ) // (v1,vt) to make sure of/to ascertain/to confirm/to grasp
 KanjiVerb( 見渡す, JAP_TRANSITIVE ) // (v5s,vt) to look out over/to survey (scene)/to take an extensive view of/(P)
 KanjiVerb( 見逃がす, JAP_TRANSITIVE ) // (v5s,vt) to miss/to overlook/to leave at large
 KanjiVerb( 見逃す, JAP_TRANSITIVE ) // (v5s,vt) to miss/to overlook/to leave at large/(P)
 KanjiVerb( 見透かす, JAP_TRANSITIVE ) // (v5s,vt) to see through
 KanjiVerb( 見届ける, JAP_TRANSITIVE ) // (v1,vt) to make sure of/to assure oneself of/to see with one's own eyes/to ascertain/(P)
 KanjiVerb( 見抜く, JAP_TRANSITIVE ) // (v5k,vt) to see through
 KanjiVerb( 見比べる, JAP_TRANSITIVE ) // (v1,vt) to compare with the eye/(P)
 KanjiVerb( 見付ける, JAP_TRANSITIVE ) // (v1,vt) (1) to discover/to find (e.g., an error in a book)/to come across/to detect/(2) to locate/to find (e.g., something missing)/to find fault/(P)
 KanjiVerb( 見付け出す, JAP_TRANSITIVE ) // (v5s,vt) to find out/to discover/to locate
 KanjiVerb( 見附る, JAP_TRANSITIVE ) // (v1,vt) (1) to discover/to find (e.g., an error in a book)/to come across/to detect/(2) to locate/to find (e.g., something missing)/to find fault
 KanjiVerb( 見舞う, JAP_TRANSITIVE ) // (v5u,vt) to ask after (health)/to visit/(P)
 KanjiVerb( 見分ける, JAP_TRANSITIVE ) // (v1,vt) (1) to distinguish/to recognize/to recognise/to tell apart/to differentiate (both figuratively and visually)/(2) to identify (whether an object is positive or negative in some aspect)/to know the difference between something of superior and inferior quality (on sight or figuratively)/(P)
 KanjiVerb( 見変える, JAP_TRANSITIVE ) // (v1,vt) to forsake one thing for another
 KanjiVerb( 見返す, JAP_TRANSITIVE ) // (v5s,vt) to look (stare) back at/to triumph over/(P)
 KanjiVerb( 見放す, JAP_TRANSITIVE ) // (v5s,vt) to desert/to abandon/to give up/(P)
 KanjiVerb( 見忘れる, JAP_TRANSITIVE ) // (v1,vt) to forget/to fail to recognize/to fail to recognise
 KanjiVerb( 見落す, JAP_TRANSITIVE ) // (v5s,vt) to overlook/to fail to notice/to miss (seeing)
 KanjiVerb( 見落とす, JAP_TRANSITIVE ) // (v5s,vt) to overlook/to fail to notice/to miss (seeing)/(P)
 KanjiVerb( 見離す, JAP_TRANSITIVE ) // (v5s,vt) to desert/to abandon/to give up
 KanjiVerb( 見立てる, JAP_TRANSITIVE ) // (v1,vt) to choose/to select
 KanjiVerb( 見做す, JAP_TRANSITIVE ) // (v5s,vt) to consider as/to regard/to be deemed (as)
 KanjiVerb( 見咎める, JAP_TRANSITIVE ) // (v1,vt) to find fault with/to question
 KanjiVerb( 見霽かす, JAP_TRANSITIVE ) // (v5s,vt) to enjoy a panoramic view
 KanjiVerb( 遣う, JAP_TRANSITIVE ) // (v5u,vt) to dispatch/to despatch/to send/to donate
 KanjiVerb( 遣す, JAP_TRANSITIVE ) // (v5s,vt) (1) to send/to forward/(2) to hand over (e.g., money)
 KanjiVerb( 遣っつける, JAP_TRANSITIVE ) // (v1,vt) to beat/to attack (an enemy)/to do away with/to finish off
 KanjiVerb( 遣って退ける, JAP_TRANSITIVE ) // (v1,vt) to succeed (in doing)/to pull something off/to manage (to do a job)
 KanjiVerb( 遣っ付ける, JAP_TRANSITIVE ) // (v1,vt) to beat/to attack (an enemy)/to do away with/to finish off
 KanjiVerb( 遣らかす, JAP_TRANSITIVE ) // (v5s,vt) to perpetrate/to do/to be guilty of
 KanjiVerb( 遣りつける, JAP_TRANSITIVE ) // (v1,vt) to be accustomed to/to be used to/to argue into silence/to talk down
 KanjiVerb( 遣り過す, JAP_TRANSITIVE ) // (v5s,vt) to do too much/to let something (or somebody) go past
 KanjiVerb( 遣り合う, JAP_TRANSITIVE ) // (v5u,vt) to compete with/to argue with/to quarrel
 KanjiVerb( 遣り込める, JAP_TRANSITIVE ) // (v1,vt) to talk down
 KanjiVerb( 遣り出す, JAP_TRANSITIVE ) // (v5s,vt) to begin
 KanjiVerb( 遣り遂げる, JAP_TRANSITIVE ) // (v1,vt) to accomplish
 KanjiVerb( 遣り直す, JAP_TRANSITIVE ) // (v5s,vt) to do over again/to redo/to start over/to remake/to resume/to recommence
 KanjiVerb( 遣り抜く, JAP_TRANSITIVE ) // (v5k,vt) to carry out to completion/to accomplish
 KanjiVerb( 遣り付ける, JAP_TRANSITIVE ) // (v1,vt) to be accustomed to/to be used to/to argue into silence/to talk down
 KanjiVerb( 遣り返す, JAP_TRANSITIVE ) // (v5s,vt) to do over/to answer or fire back/to retort
 KanjiVerb( 遣わす, JAP_TRANSITIVE ) // (v5s,vt) to send/to dispatch/to despatch
 KanjiVerb( 元気付ける, JAP_TRANSITIVE ) // (v1,vt) to pep up/to cheer up
 KanjiVerb( 減らす, JAP_TRANSITIVE ) // (v5s,vt) to abate/to decrease/to diminish/to shorten/(P)
 KanjiVerb( 現す, JAP_TRANSITIVE ) // (v5s,vt) to show/to indicate/to display/(P)
 KanjiVerb( 言いかえる, JAP_TRANSITIVE ) // (v1,vt) to say in other words/to put another way/to express in different words/to reword
 KanjiVerb( 言いかける, JAP_TRANSITIVE ) // (v1,vt) to begin speaking/to start to say/to stop in mid-sentence
 KanjiVerb( 言いきかせる, JAP_TRANSITIVE ) // (v1,vt) to tell someone to do something/to warn/to persuade/to instruct
 KanjiVerb( 言いそびれる, JAP_TRANSITIVE ) // (v1,vt) to fail to mention something or tell somebody something/to miss one's chance to tell somebody something
 KanjiVerb( 言いたす, JAP_TRANSITIVE ) // (v5s,vt) to say something additional/to add (to what was said before)
 KanjiVerb( 言いつける, JAP_TRANSITIVE ) // (v1,vt) to tell/to tell on (someone)/to order/to charge/to direct
 KanjiVerb( 言い違える, JAP_TRANSITIVE ) // (v1,vt) to say by mistake/to make a slip of the tongue
 KanjiVerb( 言い過ぎる, JAP_TRANSITIVE ) // (v1,vt) to talk or say too much/to go too far/to overstate/to exaggerate
 KanjiVerb( 言い開く, JAP_TRANSITIVE ) // (v5k,vt) to justify/to explain/to vindicate
 KanjiVerb( 言い掛ける, JAP_TRANSITIVE ) // (v1,vt) to begin speaking/to start to say/to stop in mid-sentence
 KanjiVerb( 言い換える, JAP_TRANSITIVE ) // (v1,vt) to say in other words/to put another way/to express in different words/to reword/(P)
 KanjiVerb( 言い含める, JAP_TRANSITIVE ) // (v1,vt) to give detailed instructions
 KanjiVerb( 言い継ぐ, JAP_TRANSITIVE ) // (v5g,vt) to transmit by word of mouth
 KanjiVerb( 言い兼ねる, JAP_TRANSITIVE ) // (v1,vt) to find it hard to say
 KanjiVerb( 言い現す, JAP_TRANSITIVE ) // (v5s,vt) to express (in words)
 KanjiVerb( 言い交す, JAP_TRANSITIVE ) // (v5s,vt) to have a chat with/to promise/to get engaged
 KanjiVerb( 言い合う, JAP_TRANSITIVE ) // (v5u,vt) to quarrel
 KanjiVerb( 言い込める, JAP_TRANSITIVE ) // (v1,vt) to talk down/to argue down
 KanjiVerb( 言い散らす, JAP_TRANSITIVE ) // (v5s,vt) to spread (a report)
 KanjiVerb( 言い残す, JAP_TRANSITIVE ) // (v5s,vt) to leave word with (a person)/to state in one's will/to leave (something) unsaid/to forget to mention
 KanjiVerb( 言い捨てる, JAP_TRANSITIVE ) // (v1,vt) to say (something) over one's shoulder
 KanjiVerb( 言い習わす, JAP_TRANSITIVE ) // (v5s,vt) to be handed down/to have a habit of saying
 KanjiVerb( 言い出す, JAP_TRANSITIVE ) // (v5s,vt) to start talking/to speak/to tell/to propose/to suggest/to break the ice/(P)
 KanjiVerb( 言い触らす, JAP_TRANSITIVE ) // (v5s,vt) to spread a rumor/to spread a rumour/to talk about
 KanjiVerb( 言い繕う, JAP_TRANSITIVE ) // (v5u,vt) to gloss over
 KanjiVerb( 言い争う, JAP_TRANSITIVE ) // (v5u,vt) to quarrel/to dispute
 KanjiVerb( 言い足す, JAP_TRANSITIVE ) // (v5s,vt) to say something additional/to add (to what was said before)
 KanjiVerb( 言い替える, JAP_TRANSITIVE ) // (v1,vt) to say in other words/to put another way/to express in different words/to reword
 KanjiVerb( 言い置く, JAP_TRANSITIVE ) // (v5k,vt) to leave word/to leave a message
 KanjiVerb( 言い直す, JAP_TRANSITIVE ) // (v5s,vt) to correct oneself/to restate
 KanjiVerb( 言い通す, JAP_TRANSITIVE ) // (v5s,vt) to persist in saying
 KanjiVerb( 言い添える, JAP_TRANSITIVE ) // (v1,vt) to add (to what was said before)/to say in addition
 KanjiVerb( 言い伝える, JAP_TRANSITIVE ) // (v1,vt) to send word
 KanjiVerb( 言い渡す, JAP_TRANSITIVE ) // (v5s,vt) to announce/to tell/to sentence/to order/(P)
 KanjiVerb( 言い当てる, JAP_TRANSITIVE ) // (v1,vt) to guess right
 KanjiVerb( 言い逃れる, JAP_TRANSITIVE ) // (v1,vt) to explain away/to talk one's way out of
 KanjiVerb( 言い抜ける, JAP_TRANSITIVE ) // (v1,vt) to explain away/to answer evasively
 KanjiVerb( 言い表す, JAP_TRANSITIVE ) // (v5s,vt) to express (in words)/(P)
 KanjiVerb( 言い表わす, JAP_TRANSITIVE ) // (v5s,vt) to express (in words)/(P)
 KanjiVerb( 言い付ける, JAP_TRANSITIVE ) // (v1,vt) to tell/to tell on (someone)/to order/to charge/to direct/(P)
 KanjiVerb( 言い負かす, JAP_TRANSITIVE ) // (v5s,vt) to talk (a person) down/to confute
 KanjiVerb( 言い伏せる, JAP_TRANSITIVE ) // (v1,vt) to argue down
 KanjiVerb( 言い紛らす, JAP_TRANSITIVE ) // (v5s,vt) to equivocate
 KanjiVerb( 言い聞かせる, JAP_TRANSITIVE ) // (v1,vt) to tell someone to do something/to warn/to persuade/to instruct
 KanjiVerb( 言い返す, JAP_TRANSITIVE ) // (v5s,vt) to repeat/to talk back/to answer back/(P)
 KanjiVerb( 言い包める, JAP_TRANSITIVE ) // (v1,vt) to explain away (e.g., unpleasant evidence)
 KanjiVerb( 言い放つ, JAP_TRANSITIVE ) // (v5t,vt) to declare
 KanjiVerb( 言い淀む, JAP_TRANSITIVE ) // (v5m,vt) to hesitate to say
 KanjiVerb( 言い落す, JAP_TRANSITIVE ) // (v5s,vt) to omit/to forget to mention/to leave unspoken
 KanjiVerb( 言い立てる, JAP_TRANSITIVE ) // (v1,vt) to state/to insist
 KanjiVerb( 言い漏らす, JAP_TRANSITIVE ) // (v5s,vt) to forget to mention/to leave unspoken/to let slip a secret
 KanjiVerb( 言い做す, JAP_TRANSITIVE ) // (v5s,vt) to speak as though something were actually the case/to smooth over/to describe
 KanjiVerb( 言い囃す, JAP_TRANSITIVE ) // (v5s,vt) to praise/to spread or circulate a rumor (rumour)
 KanjiVerb( 言い籠める, JAP_TRANSITIVE ) // (v1,vt) to talk down/to argue down
 KanjiVerb( 言づける, JAP_TRANSITIVE ) // (v1,vt) to send word/to send a message
 KanjiVerb( 言違える, JAP_TRANSITIVE ) // (v1,vt) to say by mistake/to make a slip of the tongue
 KanjiVerb( 言過ぎる, JAP_TRANSITIVE ) // (v1,vt) to talk or say too much/to go too far/to overstate/to exaggerate
 KanjiVerb( 言開く, JAP_TRANSITIVE ) // (v5k,vt) to justify/to explain/to vindicate
 KanjiVerb( 言掛ける, JAP_TRANSITIVE ) // (v1,vt) to begin speaking/to start to say/to stop in mid-sentence
 KanjiVerb( 言換える, JAP_TRANSITIVE ) // (v1,vt) to say in other words/to put another way/to express in different words/to reword
 KanjiVerb( 言含める, JAP_TRANSITIVE ) // (v1,vt) to give detailed instructions
 KanjiVerb( 言継ぐ, JAP_TRANSITIVE ) // (v5g,vt) to transmit by word of mouth
 KanjiVerb( 言兼ねる, JAP_TRANSITIVE ) // (v1,vt) to find it hard to say
 KanjiVerb( 言交す, JAP_TRANSITIVE ) // (v5s,vt) to have a chat with/to promise/to get engaged
 KanjiVerb( 言合う, JAP_TRANSITIVE ) // (v5u,vt) to quarrel
 KanjiVerb( 言込める, JAP_TRANSITIVE ) // (v1,vt) to talk down/to argue down
 KanjiVerb( 言散らす, JAP_TRANSITIVE ) // (v5s,vt) to spread (a report)
 KanjiVerb( 言残す, JAP_TRANSITIVE ) // (v5s,vt) to leave word with (a person)/to state in one's will/to leave (something) unsaid/to forget to mention
 KanjiVerb( 言捨てる, JAP_TRANSITIVE ) // (v1,vt) to say (something) over one's shoulder
 KanjiVerb( 言習わす, JAP_TRANSITIVE ) // (v5s,vt) to be handed down/to have a habit of saying
 KanjiVerb( 言祝ぐ, JAP_TRANSITIVE ) // (v5g,vt) to congratulate
 KanjiVerb( 言出す, JAP_TRANSITIVE ) // (v5s,vt) to start talking/to speak/to tell/to propose/to suggest/to break the ice
 KanjiVerb( 言触らす, JAP_TRANSITIVE ) // (v5s,vt) to spread a rumor/to spread a rumour/to talk about
 KanjiVerb( 言繕う, JAP_TRANSITIVE ) // (v5u,vt) to gloss over
 KanjiVerb( 言争う, JAP_TRANSITIVE ) // (v5u,vt) to quarrel/to dispute
 KanjiVerb( 言足す, JAP_TRANSITIVE ) // (v5s,vt) to say something additional/to add (to what was said before)
 KanjiVerb( 言替える, JAP_TRANSITIVE ) // (v1,vt) to say in other words/to put another way/to express in different words/to reword
 KanjiVerb( 言置く, JAP_TRANSITIVE ) // (v5k,vt) to leave word/to leave a message
 KanjiVerb( 言直す, JAP_TRANSITIVE ) // (v5s,vt) to correct oneself/to restate
 KanjiVerb( 言通す, JAP_TRANSITIVE ) // (v5s,vt) to persist in saying
 KanjiVerb( 言添える, JAP_TRANSITIVE ) // (v1,vt) to add (to what was said before)/to say in addition
 KanjiVerb( 言伝える, JAP_TRANSITIVE ) // (v1,vt) to send word
 KanjiVerb( 言渡す, JAP_TRANSITIVE ) // (v5s,vt) to announce/to tell/to sentence/to order
 KanjiVerb( 言当てる, JAP_TRANSITIVE ) // (v1,vt) to guess right
 KanjiVerb( 言逃れる, JAP_TRANSITIVE ) // (v1,vt) to explain away/to talk one's way out of
 KanjiVerb( 言抜ける, JAP_TRANSITIVE ) // (v1,vt) to explain away/to answer evasively
 KanjiVerb( 言表す, JAP_TRANSITIVE ) // (v5s,vt) to express (in words)
 KanjiVerb( 言付ける, JAP_TRANSITIVE ) // (v1,vt) to send word/to send a message/(P)
 KanjiVerb( 言負かす, JAP_TRANSITIVE ) // (v5s,vt) to talk (a person) down/to confute
 KanjiVerb( 言伏せる, JAP_TRANSITIVE ) // (v1,vt) to argue down
 KanjiVerb( 言紛らす, JAP_TRANSITIVE ) // (v5s,vt) to equivocate
 KanjiVerb( 言聞かせる, JAP_TRANSITIVE ) // (v1,vt) to tell someone to do something/to warn/to persuade/to instruct
 KanjiVerb( 言返す, JAP_TRANSITIVE ) // (v5s,vt) to repeat/to talk back/to answer back
 KanjiVerb( 言包める, JAP_TRANSITIVE ) // (v1,vt) to explain away (e.g., unpleasant evidence)
 KanjiVerb( 言放つ, JAP_TRANSITIVE ) // (v5t,vt) to declare
 KanjiVerb( 言淀む, JAP_TRANSITIVE ) // (v5m,vt) to hesitate to say
 KanjiVerb( 言落す, JAP_TRANSITIVE ) // (v5s,vt) to omit/to forget to mention/to leave unspoken
 KanjiVerb( 言立てる, JAP_TRANSITIVE ) // (v1,vt) to state/to insist
 KanjiVerb( 言漏らす, JAP_TRANSITIVE ) // (v5s,vt) to forget to mention/to leave unspoken/to let slip a secret
 KanjiVerb( 言做す, JAP_TRANSITIVE ) // (v5s,vt) to speak as though something were actually the case/to smooth over/to describe
 KanjiVerb( 言囃す, JAP_TRANSITIVE ) // (v5s,vt) to praise/to spread or circulate a rumor (rumour)
 KanjiVerb( 言籠める, JAP_TRANSITIVE ) // (v1,vt) to talk down/to argue down
 KanjiVerb( 古す, JAP_TRANSITIVE ) // (v5s,vt) to wear out
 KanjiVerb( 呼びかける, JAP_TRANSITIVE ) // (v1,vt) to call out to/to accost/to address (crowd)/to appeal
 KanjiVerb( 呼びつける, JAP_TRANSITIVE ) // (v1,vt) to summon/to get used to call
 KanjiVerb( 呼び覚ます, JAP_TRANSITIVE ) // (v5s,vt) to wake up
 KanjiVerb( 呼び掛ける, JAP_TRANSITIVE ) // (v1,vt) to call out to/to accost/to address (crowd)/to appeal/(P)
 KanjiVerb( 呼び寄せる, JAP_TRANSITIVE ) // (v1,vt) to call/to summon/to send for/to call together
 KanjiVerb( 呼び迎える, JAP_TRANSITIVE ) // (v1,vt) to send for
 KanjiVerb( 呼び止める, JAP_TRANSITIVE ) // (v1,vt) to challenge/to call somebody to halt
 KanjiVerb( 呼び集める, JAP_TRANSITIVE ) // (v1,vt) to call together/to convene
 KanjiVerb( 呼び出す, JAP_TRANSITIVE ) // (v5s,vt) (1) to summon/to call (e.g., phone)/(2) to invoke/(P)
 KanjiVerb( 呼び上げる, JAP_TRANSITIVE ) // (v1,vt) to call out
 KanjiVerb( 呼び入れる, JAP_TRANSITIVE ) // (v1,vt) to call in/to invite/to bring in
 KanjiVerb( 呼び付ける, JAP_TRANSITIVE ) // (v1,vt) to summon/to get used to call
 KanjiVerb( 呼び返す, JAP_TRANSITIVE ) // (v5s,vt) to call back/to recall
 KanjiVerb( 呼び戻す, JAP_TRANSITIVE ) // (v5s,vt) to call back/to call home/(P)
 KanjiVerb( 呼び立てる, JAP_TRANSITIVE ) // (v1,vt) to call out/to ask someone to come
 KanjiVerb( 呼び留める, JAP_TRANSITIVE ) // (v1,vt) to challenge/to call somebody to halt
 KanjiVerb( 呼ぶ, JAP_TRANSITIVE ) // (v5b,vt) to call out/to invite/(P)
 KanjiVerb( 固める, JAP_TRANSITIVE ) // (v1,vt) to harden/to freeze/to fortify/(P)
 KanjiVerb( 枯らす, JAP_TRANSITIVE ) // (v5s,vt) to let dry/to kill (vegetation) to season (lumber)
 KanjiVerb( 雇い入れる, JAP_TRANSITIVE ) // (v1,vt) to employ/to engage
 KanjiVerb( 雇う, JAP_TRANSITIVE ) // (v5u,vt) to employ/to hire/(P)
 KanjiVerb( 顧みる, JAP_TRANSITIVE ) // (v1,vt) to look back/to turn around/to review/(P)
 KanjiVerb( 呉れる, JAP_TRANSITIVE ) // (v1,vt) (uk) to give/to let one have/to do for one/to be given/(P)
 KanjiVerb( 後らせる, JAP_TRANSITIVE ) // (v1,vt) to put something off
 KanjiVerb( 語らう, JAP_TRANSITIVE ) // (v5u,vt) to talk/to tell/to recite/to pledge/to conspire with/(P)
 KanjiVerb( 語り継ぐ, JAP_TRANSITIVE ) // (v5g,vt) to transmit/to hand down
 KanjiVerb( 語り合う, JAP_TRANSITIVE ) // (v5u,vt) to talk together
 KanjiVerb( 語り伝える, JAP_TRANSITIVE ) // (v1,vt) to hand down/to pass on (story or tradition)
 KanjiVerb( 語り明かす, JAP_TRANSITIVE ) // (v5s,vt) to talk all the night
 KanjiVerb( 乞う, JAP_TRANSITIVE ) // (v5u-s,vt) to ask/to request/to invite
 KanjiVerb( 交える, JAP_TRANSITIVE ) // (v1,vt) (1) to mix/to converse with/(2) to cross (swords)/(P)
 KanjiVerb( 交す, JAP_TRANSITIVE ) // (v5s,vt) to exchange (messages)/to dodge/to parry/to avoid/to turn aside
 KanjiVerb( 交ぜる, JAP_TRANSITIVE ) // (v1,vt) to mix/to stir/to blend/(P)
 KanjiVerb( 交ぜ合せる, JAP_TRANSITIVE ) // (v1,vt) to mix
 KanjiVerb( 交わす, JAP_TRANSITIVE ) // (v5s,vt) to exchange (messages)/to dodge/to parry/to avoid/to turn aside/(P)
 KanjiVerb( 勾引す, JAP_TRANSITIVE ) // (v5s,vt) to kidnap
 KanjiVerb( 口号む, JAP_TRANSITIVE ) // (v5m,vt) to hum/to sing to oneself/to compose impromptu (poems)
 KanjiVerb( 口説く, JAP_TRANSITIVE ) // (v5k,vt) to seduce/to make a play
 KanjiVerb( 口遊む, JAP_TRANSITIVE ) // (v5m,vt) to hum/to sing to oneself/to compose impromptu (poems)
 KanjiVerb( 向ける, JAP_TRANSITIVE ) // (v1,vt) to turn towards/to point/(P)
 KanjiVerb( 向け直す, JAP_TRANSITIVE ) // (v5s,vt) to change direction
 KanjiVerb( 好き好む, JAP_TRANSITIVE ) // (v5m,vt) to do something by choice/to like/to be fond of
 KanjiVerb( 好く, JAP_TRANSITIVE ) // (v5k,vt) to like/to love/to be fond of
 KanjiVerb( 好む, JAP_TRANSITIVE ) // (v5m,vt) to like/to prefer/(P)
 KanjiVerb( 広げる, JAP_TRANSITIVE ) // (v1,vt) to spread/to extend/to expand/to enlarge/to widen/to broaden/to unfold/to open/to unroll/(P)
 KanjiVerb( 広める, JAP_TRANSITIVE ) // (v1,vt) to broaden/to propagate/(P)
 KanjiVerb( 攻める, JAP_TRANSITIVE ) // (v1,vt) to attack/to assault/(P)
 KanjiVerb( 攻め抜く, JAP_TRANSITIVE ) // (v5k,vt) persistent attacking
 KanjiVerb( 攻め滅ぼす, JAP_TRANSITIVE ) // (v5s,vt) to attack and overthrow/to utterly destroy
 KanjiVerb( 攻め立てる, JAP_TRANSITIVE ) // (v1,vt) to make an incessant onslaught/to attack incessantly
 KanjiVerb( 更かす, JAP_TRANSITIVE ) // (v5s,vt) to sit up late
 KanjiVerb( 構える, JAP_TRANSITIVE ) // (v1,vt) to set up/(P)
 KanjiVerb( 絞める, JAP_TRANSITIVE ) // (v1,vt) to strangle/to constrict/(P)
 KanjiVerb( 絞め殺す, JAP_TRANSITIVE ) // (v5s,vt) to strangle to death
 KanjiVerb( 絞り出す, JAP_TRANSITIVE ) // (v5s,vt) to squeeze or wring out
 KanjiVerb( 絞り上げる, JAP_TRANSITIVE ) // (v1,vt) (1) to squeeze (to the utmost)/to wring/(2) to strain one's voice/(3) to scold
 KanjiVerb( 耕す, JAP_TRANSITIVE ) // (v5s,vt) to till/to plow/to plough/to cultivate/(P)
 KanjiVerb( 考えつく, JAP_TRANSITIVE ) // (v5k,vt) to think of/to come up with
 KanjiVerb( 考える, JAP_TRANSITIVE ) // (v1,vt) to consider/to think about/(P)
 KanjiVerb( 考え直す, JAP_TRANSITIVE ) // (v5s,vt) to reconsider/to rethink
 KanjiVerb( 考え付く, JAP_TRANSITIVE ) // (v5k,vt) to think of/to come up with
 KanjiVerb( 荒げる, JAP_TRANSITIVE ) // (v1,vt) to raise (e.g., voice)
 KanjiVerb( 荒らげる, JAP_TRANSITIVE ) // (v1,vt) to raise (e.g., voice)/(P)
 KanjiVerb( 荒らす, JAP_TRANSITIVE ) // (v5s,vt) (1) to lay waste/to devastate/to damage/(2) to invade/to break into/(P)
 KanjiVerb( 荒立てる, JAP_TRANSITIVE ) // (v1,vt) to aggravate/to make serious
 KanjiVerb( 行ずる, JAP_TRANSITIVE ) // (vz,vt) (arch) (obsc) to perform/to do/to practice
 KanjiVerb( 講じる, JAP_TRANSITIVE ) // (v1,vt) (1) to take measures/to work out a plan/(2) to lecture/to read aloud/(3) to confer
 KanjiVerb( 講ずる, JAP_TRANSITIVE ) // (vz,vt) (1) to take measures/to work out a plan/(2) to lecture/to read aloud/(3) to confer/(P)
 KanjiVerb( 貢ぐ, JAP_TRANSITIVE ) // (v5g,vt) to support/to finance
 KanjiVerb( 購う, JAP_TRANSITIVE ) // (v5u,vt) to compensate/to make up for
 KanjiVerb( 降す, JAP_TRANSITIVE ) // (v5s,vt) to lower/to let go down
 KanjiVerb( 降らす, JAP_TRANSITIVE ) // (v5s,vt) to send (rain)/to shed
 KanjiVerb( 降り込める, JAP_TRANSITIVE ) // (v1,vt) to rain (or snow), keeping people indoors
 KanjiVerb( 降り籠める, JAP_TRANSITIVE ) // (v1,vt) to rain (or snow), keeping people indoors
 KanjiVerb( 降ろす, JAP_TRANSITIVE ) // (v5s,vt) (1) to take down (e.g., flag)/to launch (e.g., boat)/to drop/to lower (e.g., ladder)/to let (a person) off/to unload/to discharge/(2) to withdraw money from an account/(3) to wear (clothing) for the first time/(P)
 KanjiVerb( 高める, JAP_TRANSITIVE ) // (v1,vt) to raise/to lift/to boost/to enhance/(P)
 KanjiVerb( 劫かす, JAP_TRANSITIVE ) // (v5s,vt) to threaten/to coerce
 KanjiVerb( 合わせる, JAP_TRANSITIVE ) // (v1,vt) to join together/to be opposite/to face/to unite/to combine/to connect/to add up/to mix/to match/to overlap/to compare/to check with/(P)
 KanjiVerb( 刻みつける, JAP_TRANSITIVE ) // (v1,vt) to engrave/to carve out
 KanjiVerb( 刻み込む, JAP_TRANSITIVE ) // (v5m,vt) to etch (name, etc.)/to carve (design)
 KanjiVerb( 刻み付ける, JAP_TRANSITIVE ) // (v1,vt) to engrave/to carve out
 KanjiVerb( 刻む, JAP_TRANSITIVE ) // (v5m,vt) to mince/to carve/to engrave/to cut fine/to chop up/to hash/to chisel/to notch/(P)
 KanjiVerb( 告げる, JAP_TRANSITIVE ) // (v1,vt) to inform/(P)
 KanjiVerb( 黒める, JAP_TRANSITIVE ) // (v1,vt) to make something black/to talk wrong into right
 KanjiVerb( 漉す, JAP_TRANSITIVE ) // (v5s,vt) to filter/to strain
 KanjiVerb( 込める, JAP_TRANSITIVE ) // (v1,vt) to include/to put into/(P)
 KanjiVerb( 恨む, JAP_TRANSITIVE ) // (v5m,vt) to curse/to feel bitter/(P)
 KanjiVerb( 混ぜる, JAP_TRANSITIVE ) // (v1,vt) to mix/to stir/to blend/(P)
 KanjiVerb( 混ぜ合せる, JAP_TRANSITIVE ) // (v1,vt) to mix
 KanjiVerb( 唆す, JAP_TRANSITIVE ) // (v5s,vt) to instigate/to tempt/(P)
 KanjiVerb( 差しかける, JAP_TRANSITIVE ) // (v1,vt) to hold (umbrella) over
 KanjiVerb( 差しつける, JAP_TRANSITIVE ) // (v1,vt) to point (gun at)/to hold under one's nose
 KanjiVerb( 差し違える, JAP_TRANSITIVE ) // (v1,vi,vt) to misplace/to stab at each other
 KanjiVerb( 差し延べる, JAP_TRANSITIVE ) // (v1,vt) (1) to hold out/to extend (e.g., one's hands)/to stretch/to reach out for/(2) to thrust (javelin)
 KanjiVerb( 差し押える, JAP_TRANSITIVE ) // (v1,vt) to seize/to impound/to garnish/to attach goods
 KanjiVerb( 差し押さえる, JAP_TRANSITIVE ) // (v1,vt) to seize/to impound/to garnish/to attach goods
 KanjiVerb( 差し回す, JAP_TRANSITIVE ) // (v5s,vt) to send (a car) around
 KanjiVerb( 差し掛ける, JAP_TRANSITIVE ) // (v1,vt) to hold (umbrella) over
 KanjiVerb( 差し換える, JAP_TRANSITIVE ) // (v1,vt) to change/to replace
 KanjiVerb( 差し許す, JAP_TRANSITIVE ) // (v5s,vt) to allow/to forgive
 KanjiVerb( 差し挟む, JAP_TRANSITIVE ) // (v5m,vt) (1) to insert/(2) to interrupt/to slip in a word/(3) to harbor (e.g., doubts)/to harbour/to entertain (e.g., a theory)
 KanjiVerb( 差し固める, JAP_TRANSITIVE ) // (v1,vt) to close or shut tight/to warn sharply
 KanjiVerb( 差し交わす, JAP_TRANSITIVE ) // (v5s,vt) to cross
 KanjiVerb( 差し向ける, JAP_TRANSITIVE ) // (v1,vt) to send or direct a person to
 KanjiVerb( 差し控える, JAP_TRANSITIVE ) // (v1,vt) to be moderate/to not do too much/(P)
 KanjiVerb( 差し止める, JAP_TRANSITIVE ) // (v1,vt) to stop/to prohibit/to forbid someone to do something
 KanjiVerb( 差し出す, JAP_TRANSITIVE ) // (v5s,vt) to present/to submit/to tender/to hold out/(P)
 KanjiVerb( 差し招く, JAP_TRANSITIVE ) // (v5k,vt) to beckon (to)
 KanjiVerb( 差し上げる, JAP_TRANSITIVE ) // (v1,vt) (pol) to give/to hold up/to lift up/to offer/(P)
 KanjiVerb( 差し伸べる, JAP_TRANSITIVE ) // (v1,vt) (1) to hold out/to extend (e.g., one's hands)/to stretch/to reach out for/(2) to thrust (javelin)/(P)
 KanjiVerb( 差し替える, JAP_TRANSITIVE ) // (v1,vt) to change/to replace
 KanjiVerb( 差し置く, JAP_TRANSITIVE ) // (v5k,vt) to leave as is/to let alone/to disregard
 KanjiVerb( 差し入れる, JAP_TRANSITIVE ) // (v1,vt) to insert/to put in
 KanjiVerb( 差し付ける, JAP_TRANSITIVE ) // (v1,vt) to point (gun at)/to hold under one's nose
 KanjiVerb( 差し戻す, JAP_TRANSITIVE ) // (v5s,vt) to send back/to refer back/(P)
 KanjiVerb( 差し立てる, JAP_TRANSITIVE ) // (v1,vt) to stand/to send (off)
 KanjiVerb( 差延べる, JAP_TRANSITIVE ) // (v1,vt) (1) to hold out/to extend (e.g., one's hands)/to stretch/to reach out for/(2) to thrust (javelin)
 KanjiVerb( 差伸べる, JAP_TRANSITIVE ) // (v1,vt) (1) to hold out/to extend (e.g., one's hands)/to stretch/to reach out for/(2) to thrust (javelin)
 KanjiVerb( 催す, JAP_TRANSITIVE ) // (v5s,vt) to hold (a meeting)/to give (a dinner)/to feel/to show signs of/to develop symptoms of/to feel (sick)/(P)
 KanjiVerb( 塞き止める, JAP_TRANSITIVE ) // (v1,vt) to dam up/to hold back/to keep back/to intercept/to check
 KanjiVerb( 塞ぐ, JAP_TRANSITIVE ) // (v5g,vt) to stop up/to close up/to block (up)/to occupy/to fill up/to take up/to stand in another's way/to plug up/to shut up/(P)
 KanjiVerb( 採り入れる, JAP_TRANSITIVE ) // (v1,vt) (1) to harvest/to reap/(2) to take in/togather in/(3) to adopt
 KanjiVerb( 済ます, JAP_TRANSITIVE ) // (v5s,vt) (1) to finish/to get it over with/to conclude/(2) to settle/to pay back/(3) to get along (without something)/(P)
 KanjiVerb( 済ませる, JAP_TRANSITIVE ) // (v1,vt) to be finished/(P)
 KanjiVerb( 砕く, JAP_TRANSITIVE ) // (v5k,vt) to break/to smash/(P)
 KanjiVerb( 祭り込む, JAP_TRANSITIVE ) // (v5m,vt) to place an obnoxious person in an out-of-the-way post to be rid of him or her
 KanjiVerb( 祭り上げる, JAP_TRANSITIVE ) // (v1,vt) to set up (in high position)/to kick upstairs
 KanjiVerb( 祭上げる, JAP_TRANSITIVE ) // (v1,vt) to set up (in high position)/to kick upstairs
 KanjiVerb( 細める, JAP_TRANSITIVE ) // (v1,vt) to make narrow
 KanjiVerb( 裁く, JAP_TRANSITIVE ) // (v5k,vt) to judge/(P)
 KanjiVerb( 裁つ, JAP_TRANSITIVE ) // (v5t,vt) to cut (cloth)/(P)
 KanjiVerb( 載す, JAP_TRANSITIVE ) // (v5s,vt) to place on (something)/to take on board/to give a ride to
 KanjiVerb( 載せる, JAP_TRANSITIVE ) // (v1,vt) to place on (something)/to take on board/to give a ride/to let (one) take part/to impose on/to record/to mention/to load (luggage)/to publish/to run (an ad)
 KanjiVerb( 載っける, JAP_TRANSITIVE ) // (v1,vt) to place (something) on (something)
 KanjiVerb( 咲かせる, JAP_TRANSITIVE ) // (v1,vt) to make bloom
 KanjiVerb( 作り出す, JAP_TRANSITIVE ) // (v5s,vt) (1) to manufacture/to produce/to raise (crops)/(2) to invent/to dream up
 KanjiVerb( 作り上げる, JAP_TRANSITIVE ) // (v1,vt) to make up/to fabricate/to build up/to complete/to construct/(P)
 KanjiVerb( 作り替える, JAP_TRANSITIVE ) // (v1,vt) to remake/to remold/to remould/to convert/to reconstruct/to adapt/to parody
 KanjiVerb( 作り直す, JAP_TRANSITIVE ) // (v5s,vt) to remake/to rebuild
 KanjiVerb( 作り立てる, JAP_TRANSITIVE ) // (v1,vt) to adorn/to decorate/to dress up/to build up
 KanjiVerb( 搾り上げる, JAP_TRANSITIVE ) // (v1,vt) (1) to squeeze (to the utmost)/to wring/(2) to strain one's voice/(3) to scold
 KanjiVerb( 窄む, JAP_TRANSITIVE ) // (v5m,vt) to close/to shut
 KanjiVerb( 窄める, JAP_TRANSITIVE ) // (v1,vt) to make narrower/to shut (an umbrella)/to shrug (one's shoulders)/to purse (one's lips)
 KanjiVerb( 刷り込む, JAP_TRANSITIVE ) // (v5m,vt) to insert (an illustration)/to stencil (a pattern)
 KanjiVerb( 刷り上げる, JAP_TRANSITIVE ) // (v1,vt) to finish printing/to print off
 KanjiVerb( 撮み出す, JAP_TRANSITIVE ) // (v5s,vt) to pick out/to throw out
 KanjiVerb( 撮む, JAP_TRANSITIVE ) // (v5m,vt) to pinch/to hold/to pick up
 KanjiVerb( 撮り直す, JAP_TRANSITIVE ) // (v5s,vt) to retake (a photograph)
 KanjiVerb( 擦りつける, JAP_TRANSITIVE ) // (v1,vt) to blame another
 KanjiVerb( 擦り減らす, JAP_TRANSITIVE ) // (v5s,vt) to wear away/to rub down/to abrade
 KanjiVerb( 擦り付ける, JAP_TRANSITIVE ) // (v1,vt) to blame another
 KanjiVerb( 殺す, JAP_TRANSITIVE ) // (v5s,vt) to kill/(P)
 KanjiVerb( 雑える, JAP_TRANSITIVE ) // (v1,vt) (1) to mix/to converse with/(2) to cross (swords)
 KanjiVerb( 雑ぜる, JAP_TRANSITIVE ) // (v1,vt) to mix/to stir/to blend
 KanjiVerb( 晒す, JAP_TRANSITIVE ) // (v5s,vt) (1) to expose (to the air, to the public, to danger, etc.)/(2) to bleach/to refine/(P)
 KanjiVerb( 撒き散らす, JAP_TRANSITIVE ) // (v5s,vt) to scatter/to spread
 KanjiVerb( 撒く, JAP_TRANSITIVE ) // (v5k,vt) to scatter/to sprinkle/to sow (seeds)/(P)
 KanjiVerb( 散らかす, JAP_TRANSITIVE ) // (v5s,vt) to scatter around/to leave untidy/(P)
 KanjiVerb( 散らす, JAP_TRANSITIVE ) // (v5s,vt) to scatter/to disperse/to distribute/(P)
 KanjiVerb( 散りばめる, JAP_TRANSITIVE ) // (v1,vt) (uk) to inlay/to set/to stud/to enchase (a thing) with/to mount (gem)
 KanjiVerb( 散り嵌める, JAP_TRANSITIVE ) // (v1,vt) (uk) to inlay/to set/to stud/to enchase (a thing) with/to mount (gem)
 KanjiVerb( 散蒔く, JAP_TRANSITIVE ) // (v5k,vt) (uk) to disseminate/to scatter/to give money freely/(P)
 KanjiVerb( 散播く, JAP_TRANSITIVE ) // (v5k,vt) (uk) to disseminate/to scatter/to give money freely
 KanjiVerb( 産みつける, JAP_TRANSITIVE ) // (v1,vt) to lay/to spawn
 KanjiVerb( 産み出す, JAP_TRANSITIVE ) // (v5s,vt) (1) to bring forth/to bear/to give birth to/to produce/(2) to invent
 KanjiVerb( 産み付ける, JAP_TRANSITIVE ) // (v1,vt) to lay/to spawn
 KanjiVerb( 産み落とす, JAP_TRANSITIVE ) // (v5s,vt) to give birth to/to drop (calf or foal)
 KanjiVerb( 産む, JAP_TRANSITIVE ) // (v5m,vt) to give birth/to deliver/to produce/(P)
 KanjiVerb( 讃える, JAP_TRANSITIVE ) // (v1,vt) to extol/to give praise
 KanjiVerb( 斬りつける, JAP_TRANSITIVE ) // (v1,vt) to cut at/to slash at
 KanjiVerb( 斬り付ける, JAP_TRANSITIVE ) // (v1,vt) to cut at/to slash at
 KanjiVerb( 残す, JAP_TRANSITIVE ) // (v5s,vt) to leave (behind, over)/to bequeath/to save/to reserve/(P)
 KanjiVerb( 仕かける, JAP_TRANSITIVE ) // (v1,vt) to commence/to lay (mines)/to set (traps)/to wage (war)/to challenge
 KanjiVerb( 仕掛ける, JAP_TRANSITIVE ) // (v1,vt) to commence/to lay (mines)/to set (traps)/to wage (war)/to challenge/(P)
 KanjiVerb( 仕向ける, JAP_TRANSITIVE ) // (v1,vt) to induce/to tempt/to treat/to act toward/to handle (men)/to send/to forward to
 KanjiVerb( 仕向る, JAP_TRANSITIVE ) // (v1,vt) to induce/to tempt/to treat/to act toward/to handle (men)/to send/to forward to
 KanjiVerb( 仕出かす, JAP_TRANSITIVE ) // (v5s,vt) (uk) to perpetrate/to do/to finish up/to be guilty of
 KanjiVerb( 仕出す, JAP_TRANSITIVE ) // (v5s,vt) to begin to do/cater
 KanjiVerb( 仕出来す, JAP_TRANSITIVE ) // (v5s,vt) (uk) to perpetrate/to do/to finish up/to be guilty of
 KanjiVerb( 仕上げる, JAP_TRANSITIVE ) // (v1,vt) to finish up/to complete/(P)
 KanjiVerb( 仕遂げる, JAP_TRANSITIVE ) // (v1,vt) to accomplish/to finish/to fulfill
 KanjiVerb( 仕組む, JAP_TRANSITIVE ) // (v5m,vt) to devise/to arrange/to plan/to plot
 KanjiVerb( 仕損じる, JAP_TRANSITIVE ) // (v1,vt) to blunder/to fail/to make a mistake
 KanjiVerb( 仕損ずる, JAP_TRANSITIVE ) // (vz,vt) to blunder/to fail/to make a mistake
 KanjiVerb( 仕替える, JAP_TRANSITIVE ) // (v1,vt) to do over/to start anew
 KanjiVerb( 仕入れる, JAP_TRANSITIVE ) // (v1,vt) to lay in stock/to replenish stock/to procure/(P)
 KanjiVerb( 仕付ける, JAP_TRANSITIVE ) // (v1,vt) to be used to a job/to begin to do/to baste/to tack/to plant
 KanjiVerb( 仕舞い込む, JAP_TRANSITIVE ) // (v5m,vt) to put away/to stow away/to tuck away/to hoard
 KanjiVerb( 仕舞う, JAP_TRANSITIVE ) // (v5u,vt) (uk) to finish/to close/to do something completely/to put away/to put an end to/(P)
 KanjiVerb( 仕分ける, JAP_TRANSITIVE ) // (v1,vt) to assort/to classify/to journalize (in accounting)/to journalise
 KanjiVerb( 仕訳ける, JAP_TRANSITIVE ) // (v1,vt) to assort/to classify/to journalize (in accounting)/to journalise
 KanjiVerb( 仕立てる, JAP_TRANSITIVE ) // (v1,vt) to tailor/to make/to prepare/to train/to send (a messenger)/(P)
 KanjiVerb( 仕立て上げる, JAP_TRANSITIVE ) // (v1,vt) to be made out to be
 KanjiVerb( 仕留める, JAP_TRANSITIVE ) // (v1,vt) to bring down (a bird)/to kill
 KanjiVerb( 伺う, JAP_TRANSITIVE ) // (v5u,vt) (1) (hum) to visit/to ask/to inquire/to hear/to be told/(v5u,vi) (2) to implore (a god for an oracle)/to seek direction (from your superior)/(P)
 KanjiVerb( 使いこなす, JAP_TRANSITIVE ) // (v5s,vt) to handle (men)/to master (a tool)/to acquire a command of (a language)
 KanjiVerb( 使い古す, JAP_TRANSITIVE ) // (v5s,vt) to wear out (something)
 KanjiVerb( 使い込む, JAP_TRANSITIVE ) // (v5m,vt) to embezzle/to misappropriate/to peculate/to accustom oneself to using/to use for a long time
 KanjiVerb( 使い分ける, JAP_TRANSITIVE ) // (v1,vt) to use properly/to use (different things) for different purposes
 KanjiVerb( 使う, JAP_TRANSITIVE ) // (v5u,vt) to use/to handle/to manipulate/to employ/to need/to want/to spend/to consume/to speak (English)/to practise (fencing)/to practice (fencing)/to take (one's lunch)/to circulate (bad money)/(P)
 KanjiVerb( 使わす, JAP_TRANSITIVE ) // (v5s,vt) to send/to dispatch/to despatch/(P)
 KanjiVerb( 刺し違える, JAP_TRANSITIVE ) // (v1,vi,vt) to misplace/to stab at each other
 KanjiVerb( 刺し貫く, JAP_TRANSITIVE ) // (v5k,vt) to pierce
 KanjiVerb( 刺し殺す, JAP_TRANSITIVE ) // (v5s,vt) to stab to death/(P)
 KanjiVerb( 刺し通す, JAP_TRANSITIVE ) // (v5s,vt) to stab/to pierce/to run (a sword) through
 KanjiVerb( 刺す, JAP_TRANSITIVE ) // (v5s,vt) to pierce/to stab/to prick/to thrust/to bite/to sting/to pin down/to stitch/to put (a runner) out/to pole (a boat)/to catch (with a line)/to stick/(P)
 KanjiVerb( 始める, JAP_TRANSITIVE ) // (v1,vt) to start/to begin/(P)
 KanjiVerb( 思い過ごす, JAP_TRANSITIVE ) // (v5s,vt) to think too much of/to make too much of
 KanjiVerb( 思い過す, JAP_TRANSITIVE ) // (v5s,vt) to think too much of/to make too much of
 KanjiVerb( 思い回す, JAP_TRANSITIVE ) // (v5s,vt) to ponder/to recall
 KanjiVerb( 思い起こす, JAP_TRANSITIVE ) // (v5s,vt) to recall/to remember/(P)
 KanjiVerb( 思い起す, JAP_TRANSITIVE ) // (v5s,vt) to recall/to remember
 KanjiVerb( 思い詰める, JAP_TRANSITIVE ) // (v1,vt) to think hard/to brood over
 KanjiVerb( 思い残す, JAP_TRANSITIVE ) // (v5s,vt) to regret
 KanjiVerb( 思い出す, JAP_TRANSITIVE ) // (v5s,vt) to recall/to remember/(P)
 KanjiVerb( 思い巡らす, JAP_TRANSITIVE ) // (v5s,vt) to think over
 KanjiVerb( 思い設ける, JAP_TRANSITIVE ) // (v1,vt) to anticipate/to expect
 KanjiVerb( 思い知らせる, JAP_TRANSITIVE ) // (v1,vt) to have a revenge on/to get even with/to make someone realize/to make someone realise
 KanjiVerb( 思い直す, JAP_TRANSITIVE ) // (v5s,vt) to re-think/to think back upon/to change one's mind/(P)
 KanjiVerb( 思い定める, JAP_TRANSITIVE ) // (v1,vt) to make up one's mind/to be determined
 KanjiVerb( 思い悩む, JAP_TRANSITIVE ) // (v5m,vt) to worry
 KanjiVerb( 思い描く, JAP_TRANSITIVE ) // (v5k,vt) to imagine/to picture/to figure/to see
 KanjiVerb( 思い返す, JAP_TRANSITIVE ) // (v5s,vt) to re-think/to think back upon/to change one's mind
 KanjiVerb( 思い立つ, JAP_TRANSITIVE ) // (v5t,vt) to resolve
 KanjiVerb( 思う, JAP_TRANSITIVE ) // (v5u,vt) to think/to feel/(P)
 KanjiVerb( 思し召す, JAP_TRANSITIVE ) // (v5s,vt) to develop thoughts or feelings
 KanjiVerb( 思召す, JAP_TRANSITIVE ) // (v5s,vt) to develop thoughts or feelings
 KanjiVerb( 指し示す, JAP_TRANSITIVE ) // (v5s,vt) to indicate/to show/to point to/(P)
 KanjiVerb( 指す, JAP_TRANSITIVE ) // (v5s,vt) to point/to put up umbrella/to play/(P)
 KanjiVerb( 指差す, JAP_TRANSITIVE ) // (v5s,vt) to point at/(P)
 KanjiVerb( 支う, JAP_TRANSITIVE ) // (v5u,vt) to support or prop up
 KanjiVerb( 支払う, JAP_TRANSITIVE ) // (v5u,vt) to pay/(P)
 KanjiVerb( 施す, JAP_TRANSITIVE ) // (v5s,vt) to donate/to give/to conduct/to apply/to perform/(P)
 KanjiVerb( 止す, JAP_TRANSITIVE ) // (v5s,vt) to cease/to abolish/to resign/to give up/(P)
 KanjiVerb( 止める, JAP_TRANSITIVE ) // (v1,vt) to end/to stop/to cease/to resign/(P)
 KanjiVerb( 試す, JAP_TRANSITIVE ) // (v5s,vt) to attempt/to test/(P)
 KanjiVerb( 試みる, JAP_TRANSITIVE ) // (v1,vt) to try/to test/(P)
 KanjiVerb( 飼い慣らす, JAP_TRANSITIVE ) // (v5s,vt) to tame (e.g., animal)
 KanjiVerb( 飼う, JAP_TRANSITIVE ) // (v5u,vt) to keep/to raise/to feed/(P)
 KanjiVerb( 事寄す, JAP_TRANSITIVE ) // (v5s,vt) to find an excuse
 KanjiVerb( 事寄せる, JAP_TRANSITIVE ) // (v1,vt) to pretend
 KanjiVerb( 似せる, JAP_TRANSITIVE ) // (v1,vt) to copy/to imitate/to counterfeit/to forge/(P)
 KanjiVerb( 慈しむ, JAP_TRANSITIVE ) // (v5m,vt) to love/to be affectionate to/to pity
 KanjiVerb( 持たせる, JAP_TRANSITIVE ) // (v1,vt) to have someone hold something/to allow someone to keep something
 KanjiVerb( 持ちかける, JAP_TRANSITIVE ) // (v1,vt) to offer a suggestion/to propose an idea
 KanjiVerb( 持ち運ぶ, JAP_TRANSITIVE ) // (v5b,vt) to carry/to bring (to a place)
 KanjiVerb( 持ち越す, JAP_TRANSITIVE ) // (v5s,vt) to carry over/to carry forward/to keep (for later)/to defer/(P)
 KanjiVerb( 持ち掛ける, JAP_TRANSITIVE ) // (v1,vt) to offer a suggestion/to propose an idea
 KanjiVerb( 持ち堪える, JAP_TRANSITIVE ) // (v1,vt) to hold out/(P)
 KanjiVerb( 持ち古す, JAP_TRANSITIVE ) // (v5s,vt) to have long in use
 KanjiVerb( 持ち合せる, JAP_TRANSITIVE ) // (v1,vt) to happen to have on hand or in stock
 KanjiVerb( 持ち合わせる, JAP_TRANSITIVE ) // (v1,vt) to happen to have on hand or in stock
 KanjiVerb( 持ち込む, JAP_TRANSITIVE ) // (v5m,vt) to lodge/to take something into ../to bring in/(P)
 KanjiVerb( 持ち出す, JAP_TRANSITIVE ) // (v5s,vt) to take out/to carry out/to bring out from where it belongs/(P)
 KanjiVerb( 持ち上げる, JAP_TRANSITIVE ) // (v1,vt) to raise/to lift up/to flatter
 KanjiVerb( 持ち直す, JAP_TRANSITIVE ) // (v5s,vt) to recover/to rally/to improve/to pick up/(P)
 KanjiVerb( 持ち崩す, JAP_TRANSITIVE ) // (v5s,vt) to ruin (degrade) oneself
 KanjiVerb( 持て成す, JAP_TRANSITIVE ) // (v5s,vt) to entertain/to make welcome/(P)
 KanjiVerb( 持て余す, JAP_TRANSITIVE ) // (v5s,vt) to be too much for one/to find unmanageable/to be beyond one's control/to not know what to do with
 KanjiVerb( 持堪える, JAP_TRANSITIVE ) // (v1,vt) to hold out/(P)
 KanjiVerb( 持直す, JAP_TRANSITIVE ) // (v5s,vt) to recover/to rally/to improve/to pick up/(P)
 KanjiVerb( 時めかす, JAP_TRANSITIVE ) // (v5s,vt) (uk) to beat fast (e.g., the heart)
 KanjiVerb( 治す, JAP_TRANSITIVE ) // (v5s,vt) (1) to cure/to heal/(2) to fix/to correct/to repair/(P)
 KanjiVerb( 治める, JAP_TRANSITIVE ) // (v1,vt) (1) to govern/to manage/(2) to subdue/(P)
 KanjiVerb( 示し合せる, JAP_TRANSITIVE ) // (v1,vt) to arrange beforehand/to make a sign to each other/to conspire
 KanjiVerb( 示し合わせる, JAP_TRANSITIVE ) // (v1,vt) to arrange beforehand/to make a sign to each other/to conspire
 KanjiVerb( 示す, JAP_TRANSITIVE ) // (v5s,vt) to denote/to show/to point out/to indicate/(P)
 KanjiVerb( 蒔く, JAP_TRANSITIVE ) // (v5k,vt) to scatter/to sprinkle/to sow (seeds)/(P)
 KanjiVerb( 辞める, JAP_TRANSITIVE ) // (v1,vt) to retire/(P)
 KanjiVerb( 叱りつける, JAP_TRANSITIVE ) // (v1,vt) to rebuke/to scold harshly
 KanjiVerb( 叱り飛ばす, JAP_TRANSITIVE ) // (v5s,vt) to rebuke strongly/to tell off
 KanjiVerb( 叱り付ける, JAP_TRANSITIVE ) // (v1,vt) to rebuke/to scold harshly
 KanjiVerb( 執り行う, JAP_TRANSITIVE ) // (v5u,vt) to hold a ceremony
 KanjiVerb( 執り成す, JAP_TRANSITIVE ) // (v5s,vt) to mediate/to intervene/to smooth
 KanjiVerb( 執成す, JAP_TRANSITIVE ) // (v5s,vt) to mediate/to intervene/to smooth
 KanjiVerb( 失う, JAP_TRANSITIVE ) // (v5u,vt) to lose/to part with/(P)
 KanjiVerb( 湿す, JAP_TRANSITIVE ) // (v5s,vt) to wet/to moisten/to dampen
 KanjiVerb( 質す, JAP_TRANSITIVE ) // (v5s,vt) to ask a person about/to ascertain/to verify
 KanjiVerb( 偲ぶ, JAP_TRANSITIVE ) // (v5b,vt) to recollect/to remember
 KanjiVerb( 写し出す, JAP_TRANSITIVE ) // (v5s,vt) to reflect/to reveal/to show
 KanjiVerb( 写す, JAP_TRANSITIVE ) // (v5s,vt) (1) to transcribe/to duplicate/to reproduce/to imitate/to trace/(2) to describe/(3) to film/to picture/to photograph/(P)
 KanjiVerb( 射かける, JAP_TRANSITIVE ) // (v1,vt) to shoot or fire off an arrow
 KanjiVerb( 射る, JAP_TRANSITIVE ) // (v1,vt) to shoot/(P)
 KanjiVerb( 射掛ける, JAP_TRANSITIVE ) // (v1,vt) to shoot or fire off an arrow
 KanjiVerb( 射止める, JAP_TRANSITIVE ) // (v1,vt) to shoot dead/to make something one's own/(P)
 KanjiVerb( 射通す, JAP_TRANSITIVE ) // (v5s,vt) to pierce/to penetrate
 KanjiVerb( 射返す, JAP_TRANSITIVE ) // (v5s,vt) to return fire/to shoot back
 KanjiVerb( 射竦める, JAP_TRANSITIVE ) // (v1,vt) to pin the enemy down/to glare another down (and render impotent)
 KanjiVerb( 捨てる, JAP_TRANSITIVE ) // (v1,vt) to throw away/to cast aside/to abandon/to resign/(P)
 KanjiVerb( 捨て置く, JAP_TRANSITIVE ) // (v5k,vt) to leave as is/to ignore
 KanjiVerb( 赦す, JAP_TRANSITIVE ) // (v5s,vt) (1) to permit/to allow/to approve/(2) to exempt (from fine)/to excuse (from)/to pardon/to release/to let off/(3) to confide in/(4) to give up/to yield
 KanjiVerb( 煮つめる, JAP_TRANSITIVE ) // (v1,vt) to boil down/to concentrate
 KanjiVerb( 煮る, JAP_TRANSITIVE ) // (v1,vt) to boil/to cook/(P)
 KanjiVerb( 煮詰める, JAP_TRANSITIVE ) // (v1,vt) to boil down/to concentrate/(P)
 KanjiVerb( 煮出す, JAP_TRANSITIVE ) // (v5s,vt) to boil down/to extract
 KanjiVerb( 煮染める, JAP_TRANSITIVE ) // (v1,vt) to boil down
 KanjiVerb( 煮付ける, JAP_TRANSITIVE ) // (v1,vt) to cook hard
 KanjiVerb( 煮返す, JAP_TRANSITIVE ) // (v5s,vt) to warm over
 KanjiVerb( 煮立てる, JAP_TRANSITIVE ) // (v1,vt) to boil or simmer
 KanjiVerb( 借りる, JAP_TRANSITIVE ) // (v1,vt) to borrow/to have a loan/to hire/to rent/to buy on credit/(P)
 KanjiVerb( 借り換える, JAP_TRANSITIVE ) // (v1,vt) to convert (a loan)
 KanjiVerb( 借り受ける, JAP_TRANSITIVE ) // (v1,vt) to borrow/to have a loan/to hire/to rent/to buy on credit
 KanjiVerb( 借り出す, JAP_TRANSITIVE ) // (v5s,vt) to borrow/to take out
 KanjiVerb( 借り上げる, JAP_TRANSITIVE ) // (v1,vt) to hire/to lease/to requisition/to charter
 KanjiVerb( 借り倒す, JAP_TRANSITIVE ) // (v5s,vt) to evade payment
 KanjiVerb( 借り入れる, JAP_TRANSITIVE ) // (v1,vt) to borrow/to rent/to lease/to charter
 KanjiVerb( 借上げる, JAP_TRANSITIVE ) // (v1,vt) to hire/to lease/to requisition/to charter
 KanjiVerb( 酌む, JAP_TRANSITIVE ) // (v5m,vt) to serve sake
 KanjiVerb( 弱める, JAP_TRANSITIVE ) // (v1,vt) to weaken/(P)
 KanjiVerb( 取りかこむ, JAP_TRANSITIVE ) // (v5m,vt) to surround/to crowd around
 KanjiVerb( 取りつける, JAP_TRANSITIVE ) // (v1,vt) to furnish/to install/to get someone's agreement
 KanjiVerb( 取りまとめる, JAP_TRANSITIVE ) // (v1,vt) to collect/to arrange/to settle/(P)
 KanjiVerb( 取り扱う, JAP_TRANSITIVE ) // (v5u,vt) to treat/to handle/to deal in/(P)
 KanjiVerb( 取り囲む, JAP_TRANSITIVE ) // (v5m,vt) to surround/to crowd around/(P)
 KanjiVerb( 取り違える, JAP_TRANSITIVE ) // (v1,vt) to take by mistake
 KanjiVerb( 取り運ぶ, JAP_TRANSITIVE ) // (v5b,vt) to proceed smoothly
 KanjiVerb( 取り押える, JAP_TRANSITIVE ) // (v1,vt) (1) to seize/to capture/to arrest/(2) to hold down/to subdue
 KanjiVerb( 取り押さえる, JAP_TRANSITIVE ) // (v1,vt) (1) to seize/to capture/to arrest/(2) to hold down/to subdue
 KanjiVerb( 取り下げる, JAP_TRANSITIVE ) // (v1,vt) to withdraw/to abandon (e.g., a lawsuit)
 KanjiVerb( 取り回す, JAP_TRANSITIVE ) // (v5s,vt) to rotate in one's hands/to treat/to manage/to dispose of
 KanjiVerb( 取り壊す, JAP_TRANSITIVE ) // (v5s,vt) to demolish/to tear or pull down
 KanjiVerb( 取り外す, JAP_TRANSITIVE ) // (v5s,vt) to dismantle/to demount/to take something away/to detach/(P)
 KanjiVerb( 取り巻く, JAP_TRANSITIVE ) // (v5k,vt) to surround/to circle/to enclose/(P)
 KanjiVerb( 取り換える, JAP_TRANSITIVE ) // (v1,vt) to exchange/to replace
 KanjiVerb( 取り寄せる, JAP_TRANSITIVE ) // (v1,vt) to order/to send away for/(P)
 KanjiVerb( 取り極める, JAP_TRANSITIVE ) // (v1,vt) to agree/to decide upon/to enter into (a contract)
 KanjiVerb( 取り計らう, JAP_TRANSITIVE ) // (v5u,vt) to manage/to settle/to dispose of/to deal with/to arrange
 KanjiVerb( 取り決める, JAP_TRANSITIVE ) // (v1,vt) to agree/to decide upon/to enter into (a contract)/(P)
 KanjiVerb( 取り結ぶ, JAP_TRANSITIVE ) // (v5b,vt) to tie up/conclude
 KanjiVerb( 取り広げる, JAP_TRANSITIVE ) // (v1,vt) to enlarge/to widen/to spread out
 KanjiVerb( 取り混ぜる, JAP_TRANSITIVE ) // (v1,vt) to mix/to put together
 KanjiVerb( 取り殺す, JAP_TRANSITIVE ) // (v5s,vt) to haunt to death/to possess and kill
 KanjiVerb( 取り捌く, JAP_TRANSITIVE ) // (v5k,vt) to settle (a matter)
 KanjiVerb( 取り散らす, JAP_TRANSITIVE ) // (v5s,vt) to scatter about
 KanjiVerb( 取り残す, JAP_TRANSITIVE ) // (v5s,vt) to leave behind/(P)
 KanjiVerb( 取り止める, JAP_TRANSITIVE ) // (v1,vt) to cancel/to call off
 KanjiVerb( 取り持つ, JAP_TRANSITIVE ) // (v5t,vt) to mediate/to entertain/to serve
 KanjiVerb( 取り次ぐ, JAP_TRANSITIVE ) // (v5g,vt) to act as an agent for/to announce (someone)/to convey (a message)/(P)
 KanjiVerb( 取り捨てる, JAP_TRANSITIVE ) // (v1,vt) to throw away
 KanjiVerb( 取り集める, JAP_TRANSITIVE ) // (v1,vt) to gather/to collect
 KanjiVerb( 取り出す, JAP_TRANSITIVE ) // (v5s,vt) (1) to take out/to produce/to pick out/(2) to fetch/to retrieve/(P)
 KanjiVerb( 取り除く, JAP_TRANSITIVE ) // (v5k,vt) to remove/to deinstall/to take away/to set apart/(P)
 KanjiVerb( 取り消す, JAP_TRANSITIVE ) // (v5s,vt) to cancel/(P)
 KanjiVerb( 取り上げる, JAP_TRANSITIVE ) // (v1,vt) to take up/to pick up/to disqualify/to confiscate/to deprive/(P)
 KanjiVerb( 取り成す, JAP_TRANSITIVE ) // (v5s,vt) to mediate/to intervene/to smooth
 KanjiVerb( 取り繕う, JAP_TRANSITIVE ) // (v5u,vt) to temporize/to temporise/to smooth over
 KanjiVerb( 取り揃える, JAP_TRANSITIVE ) // (v1,vt) to assemble of goods (into a set)/to gather/to put together
 KanjiVerb( 取り損なう, JAP_TRANSITIVE ) // (v5u,vt) to miss/to fail to capitalize/to fail to capitalise
 KanjiVerb( 取り替える, JAP_TRANSITIVE ) // (v1,vt) to exchange/to replace/(P)
 KanjiVerb( 取り調べる, JAP_TRANSITIVE ) // (v1,vt) to investigate/to examine
 KanjiVerb( 取り直す, JAP_TRANSITIVE ) // (v5s,vt) (1) to re-grip/to re-wrestle (sumo)/(2) to regroup (after some adverse event)
 KanjiVerb( 取り鎮める, JAP_TRANSITIVE ) // (v1,vt) to quell/to quiet
 KanjiVerb( 取り纏める, JAP_TRANSITIVE ) // (v1,vt) to collect/to arrange/to settle
 KanjiVerb( 取り逃がす, JAP_TRANSITIVE ) // (v5s,vt) to miss (capturing)/to fail to catch/to let slip
 KanjiVerb( 取り逃す, JAP_TRANSITIVE ) // (v5s,vt) to miss (capturing)/to fail to catch/to let slip
 KanjiVerb( 取り入れる, JAP_TRANSITIVE ) // (v1,vt) (1) to harvest/to reap/(2) to take in/togather in/(3) to adopt/(P)
 KanjiVerb( 取り付ける, JAP_TRANSITIVE ) // (v1,vt) to furnish/to install/to get someone's agreement
 KanjiVerb( 取り払う, JAP_TRANSITIVE ) // (v5u,vt) to clear away/to remove/to demolish
 KanjiVerb( 取り分ける, JAP_TRANSITIVE ) // (v1,vt) to distribute/to apportion/to divide
 KanjiVerb( 取り片付ける, JAP_TRANSITIVE ) // (v1,vt) to clean up/to clear away/to put in order
 KanjiVerb( 取り返す, JAP_TRANSITIVE ) // (v5s,vt) to regain/to recover/to get back/(P)
 KanjiVerb( 取り崩す, JAP_TRANSITIVE ) // (v5s,vt) to demolish/to take away until nothing remains
 KanjiVerb( 取り戻す, JAP_TRANSITIVE ) // (v5s,vt) to take back/to regain/(P)
 KanjiVerb( 取り抑える, JAP_TRANSITIVE ) // (v1,vt) (1) to seize/to capture/to arrest/(2) to hold down/to subdue
 KanjiVerb( 取り離す, JAP_TRANSITIVE ) // (v5s,vt) to release/to let go (of)
 KanjiVerb( 取り立てる, JAP_TRANSITIVE ) // (v1,vt) to collect/to extort/to appoint/to promote
 KanjiVerb( 取り留める, JAP_TRANSITIVE ) // (v1,vt) to stop/to put a stop to/to check
 KanjiVerb( 取り毀す, JAP_TRANSITIVE ) // (v5s,vt) to demolish/to tear or pull down
 KanjiVerb( 取り拉ぐ, JAP_TRANSITIVE ) // (v5g,vt) to crush
 KanjiVerb( 取れる, JAP_TRANSITIVE ) // (v1,vi,vt) to come off/to be taken off/to be removed/to be obtained/to leave/to come out (e.g., photo)/to be interpreted/(P)
 KanjiVerb( 取囲む, JAP_TRANSITIVE ) // (v5m,vt) to surround/to crowd around
 KanjiVerb( 取違える, JAP_TRANSITIVE ) // (v1,vt) to take by mistake
 KanjiVerb( 取運ぶ, JAP_TRANSITIVE ) // (v5b,vt) to proceed smoothly
 KanjiVerb( 取押える, JAP_TRANSITIVE ) // (v1,vt) (1) to seize/to capture/to arrest/(2) to hold down/to subdue
 KanjiVerb( 取下げる, JAP_TRANSITIVE ) // (v1,vt) to withdraw/to abandon (e.g., a lawsuit)
 KanjiVerb( 取回す, JAP_TRANSITIVE ) // (v5s,vt) to rotate in one's hands/to treat/to manage/to dispose of
 KanjiVerb( 取壊す, JAP_TRANSITIVE ) // (v5s,vt) to demolish/to tear or pull down
 KanjiVerb( 取外す, JAP_TRANSITIVE ) // (v5s,vt) to dismantle/to demount/to take something away/to detach
 KanjiVerb( 取巻く, JAP_TRANSITIVE ) // (v5k,vt) to surround/to circle/to enclose
 KanjiVerb( 取換る, JAP_TRANSITIVE ) // (v1,vt) to exchange/to replace
 KanjiVerb( 取寄せる, JAP_TRANSITIVE ) // (v1,vt) to order/to send away for
 KanjiVerb( 取極める, JAP_TRANSITIVE ) // (v1,vt) to agree/to decide upon/to enter into (a contract)
 KanjiVerb( 取計らう, JAP_TRANSITIVE ) // (v5u,vt) to manage/to settle/to dispose of/to deal with/to arrange
 KanjiVerb( 取決める, JAP_TRANSITIVE ) // (v1,vt) to agree/to decide upon/to enter into (a contract)
 KanjiVerb( 取結ぶ, JAP_TRANSITIVE ) // (v5b,vt) to tie up/conclude
 KanjiVerb( 取広げる, JAP_TRANSITIVE ) // (v1,vt) to enlarge/to widen/to spread out
 KanjiVerb( 取混ぜる, JAP_TRANSITIVE ) // (v1,vt) to mix/to put together
 KanjiVerb( 取殺す, JAP_TRANSITIVE ) // (v5s,vt) to haunt to death/to possess and kill
 KanjiVerb( 取捌く, JAP_TRANSITIVE ) // (v5k,vt) to settle (a matter)
 KanjiVerb( 取散らす, JAP_TRANSITIVE ) // (v5s,vt) to scatter about
 KanjiVerb( 取残す, JAP_TRANSITIVE ) // (v5s,vt) to leave behind
 KanjiVerb( 取止める, JAP_TRANSITIVE ) // (v1,vt) to cancel/to call off
 KanjiVerb( 取持つ, JAP_TRANSITIVE ) // (v5t,vt) to mediate/to entertain/to serve
 KanjiVerb( 取次ぐ, JAP_TRANSITIVE ) // (v5g,vt) to act as an agent for/to announce (someone)/to convey (a message)
 KanjiVerb( 取捨てる, JAP_TRANSITIVE ) // (v1,vt) to throw away
 KanjiVerb( 取集める, JAP_TRANSITIVE ) // (v1,vt) to gather/to collect
 KanjiVerb( 取出す, JAP_TRANSITIVE ) // (v5s,vt) (1) to take out/to produce/to pick out/(2) to fetch/to retrieve
 KanjiVerb( 取除く, JAP_TRANSITIVE ) // (v5k,vt) to remove/to deinstall/to take away/to set apart
 KanjiVerb( 取消す, JAP_TRANSITIVE ) // (v5s,vt) to cancel
 KanjiVerb( 取上げる, JAP_TRANSITIVE ) // (v1,vt) to take up/to pick up/to disqualify/to confiscate/to deprive/(P)
 KanjiVerb( 取成す, JAP_TRANSITIVE ) // (v5s,vt) to mediate/to intervene/to smooth
 KanjiVerb( 取繕う, JAP_TRANSITIVE ) // (v5u,vt) to temporize/to temporise/to smooth over
 KanjiVerb( 取揃える, JAP_TRANSITIVE ) // (v1,vt) to assemble of goods (into a set)/to gather/to put together
 KanjiVerb( 取損なう, JAP_TRANSITIVE ) // (v5u,vt) to miss/to fail to capitalize/to fail to capitalise
 KanjiVerb( 取替える, JAP_TRANSITIVE ) // (v1,vt) to exchange/to replace
 KanjiVerb( 取調べる, JAP_TRANSITIVE ) // (v1,vt) to investigate/to examine
 KanjiVerb( 取直す, JAP_TRANSITIVE ) // (v5s,vt) (1) to re-grip/to re-wrestle (sumo)/(2) to regroup (after some adverse event)
 KanjiVerb( 取鎮める, JAP_TRANSITIVE ) // (v1,vt) to quell/to quiet
 KanjiVerb( 取纏める, JAP_TRANSITIVE ) // (v1,vt) to collect/to arrange/to settle
 KanjiVerb( 取逃す, JAP_TRANSITIVE ) // (v5s,vt) to miss (capturing)/to fail to catch/to let slip
 KanjiVerb( 取入れる, JAP_TRANSITIVE ) // (v1,vt) (1) to harvest/to reap/(2) to take in/togather in/(3) to adopt
 KanjiVerb( 取付ける, JAP_TRANSITIVE ) // (v1,vt) to furnish/to install/to get someone's agreement
 KanjiVerb( 取払う, JAP_TRANSITIVE ) // (v5u,vt) to clear away/to remove/to demolish
 KanjiVerb( 取分ける, JAP_TRANSITIVE ) // (v1,vt) to distribute/to apportion/to divide
 KanjiVerb( 取片付ける, JAP_TRANSITIVE ) // (v1,vt) to clean up/to clear away/to put in order
 KanjiVerb( 取返す, JAP_TRANSITIVE ) // (v5s,vt) to regain/to recover/to get back
 KanjiVerb( 取崩す, JAP_TRANSITIVE ) // (v5s,vt) to demolish/to take away until nothing remains
 KanjiVerb( 取戻す, JAP_TRANSITIVE ) // (v5s,vt) to take back/to regain
 KanjiVerb( 取抑える, JAP_TRANSITIVE ) // (v1,vt) (1) to seize/to capture/to arrest/(2) to hold down/to subdue
 KanjiVerb( 取離す, JAP_TRANSITIVE ) // (v5s,vt) to release/to let go (of)
 KanjiVerb( 取立てる, JAP_TRANSITIVE ) // (v1,vt) to collect/to extort/to appoint/to promote
 KanjiVerb( 取留める, JAP_TRANSITIVE ) // (v1,vt) to stop/to put a stop to/to check
 KanjiVerb( 取毀す, JAP_TRANSITIVE ) // (v5s,vt) to demolish/to tear or pull down
 KanjiVerb( 取拉ぐ, JAP_TRANSITIVE ) // (v5g,vt) to crush
 KanjiVerb( 守り抜く, JAP_TRANSITIVE ) // (v5k,vt) to hold fast/to protect to the end
 KanjiVerb( 守り立てる, JAP_TRANSITIVE ) // (v1,vt) to bring up/to support/to rally
 KanjiVerb( 手なずける, JAP_TRANSITIVE ) // (v1,vt) to tame/to win over
 KanjiVerb( 手懐ける, JAP_TRANSITIVE ) // (v1,vt) to tame/to win over
 KanjiVerb( 手掛ける, JAP_TRANSITIVE ) // (v1,vt) to handle/to manage/to work with/to rear/to look after/to have experience with
 KanjiVerb( 手繰り込む, JAP_TRANSITIVE ) // (v5m,vt) to reel in
 KanjiVerb( 手控える, JAP_TRANSITIVE ) // (v1,vt) (1) to hang (hold) back/to hold off/to refrain/to reduce or cut back on/(2) to jot down a note
 KanjiVerb( 手伝う, JAP_TRANSITIVE ) // (v5u,vt) to help/to assist/to take part in/(P)
 KanjiVerb( 手渡す, JAP_TRANSITIVE ) // (v5s,vt) to hand over/to surrender/(P)
 KanjiVerb( 手放す, JAP_TRANSITIVE ) // (v5s,vt) to release/to relinquish/to sell/to part with/to send away
 KanjiVerb( 狩り集める, JAP_TRANSITIVE ) // (v1,vt) to round up/to gather/to muster/to mobilize/to mobilise
 KanjiVerb( 狩り出す, JAP_TRANSITIVE ) // (v5s,vt) to hunt out/to round up
 KanjiVerb( 狩集める, JAP_TRANSITIVE ) // (v1,vt) to round up/to gather/to muster/to mobilize/to mobilise
 KanjiVerb( 腫らす, JAP_TRANSITIVE ) // (v5s,vt) to cause to swell/to inflame
 KanjiVerb( 受けつける, JAP_TRANSITIVE ) // (v1,vt) to be accepted/to receive (an application)
 KanjiVerb( 受ける, JAP_TRANSITIVE ) // (v1,vt) to undertake/to accept/to take (lesson, test, damage)/to undergo/to experience/to catch (e.g., a ball)/to become popular/(P)
 KanjiVerb( 受け継ぐ, JAP_TRANSITIVE ) // (v5g,vt) to inherit/to succeed/to take over/(P)
 KanjiVerb( 受け合う, JAP_TRANSITIVE ) // (v5u,vt) to take on a task and guarantee success
 KanjiVerb( 受け止める, JAP_TRANSITIVE ) // (v1,vt) to catch/to stop the blow/to react to/to take/(P)
 KanjiVerb( 受け持つ, JAP_TRANSITIVE ) // (v5t,vt) to take (be in) charge of/(P)
 KanjiVerb( 受け出す, JAP_TRANSITIVE ) // (v5s,vt) to redeem/to take out of pawn
 KanjiVerb( 受け入れる, JAP_TRANSITIVE ) // (v1,vt) to accept/to receive/(P)
 KanjiVerb( 受け付ける, JAP_TRANSITIVE ) // (v1,vt) to be accepted/to receive (an application)/(P)
 KanjiVerb( 受け流す, JAP_TRANSITIVE ) // (v5s,vt) to ward off/to elude/to turn aside (a joke)
 KanjiVerb( 受入れる, JAP_TRANSITIVE ) // (v1,vt) to accept/to receive
 KanjiVerb( 呪う, JAP_TRANSITIVE ) // (v5u,vt) to curse/to put a curse on/(P)
 KanjiVerb( 寿ぐ, JAP_TRANSITIVE ) // (v5g,vt) to congratulate/to wish one well
 KanjiVerb( 授ける, JAP_TRANSITIVE ) // (v1,vt) to grant/to award/to teach/(P)
 KanjiVerb( 収める, JAP_TRANSITIVE ) // (v1,vt) to obtain/to reap/to pay/to supply/to accept/to restore (something to its place)/(P)
 KanjiVerb( 就ける, JAP_TRANSITIVE ) // (v1,vt) to put/to place
 KanjiVerb( 修める, JAP_TRANSITIVE ) // (v1,vt) (1) to study/to complete (a course)/to cultivate/to master/(2) to order (one's life)/(3) to repair (a fault one has committed)/(P)
 KanjiVerb( 愁える, JAP_TRANSITIVE ) // (v1,vt) to grieve/to lament/to be anxious/to be distressed
 KanjiVerb( 拾い出す, JAP_TRANSITIVE ) // (v5s,vt) to single out/to select
 KanjiVerb( 拾う, JAP_TRANSITIVE ) // (v5u,vt) to pick up/to find/to gather/(P)
 KanjiVerb( 終う, JAP_TRANSITIVE ) // (v5u,vt) (uk) to finish/to close/to do something completely/to put away/to put an end to
 KanjiVerb( 終える, JAP_TRANSITIVE ) // (v1,vt) to finish/(P)
 KanjiVerb( 習う, JAP_TRANSITIVE ) // (v5u,vt) to learn/(P)
 KanjiVerb( 習わす, JAP_TRANSITIVE ) // (v5s,vt) to make (someone) learn
 KanjiVerb( 襲う, JAP_TRANSITIVE ) // (v5u,vt) to attack/(P)
 KanjiVerb( 蹴込む, JAP_TRANSITIVE ) // (v5m,vt) to kick in(to)/to sustain a loss
 KanjiVerb( 蹴散らす, JAP_TRANSITIVE ) // (v5s,vt) to kick about
 KanjiVerb( 蹴出す, JAP_TRANSITIVE ) // (v5s,vt) to kick out/to cut back (on spending)
 KanjiVerb( 蹴上げる, JAP_TRANSITIVE ) // (v1,vt) to kick up
 KanjiVerb( 蹴倒す, JAP_TRANSITIVE ) // (v5s,vt) to kick over or down
 KanjiVerb( 蹴飛ばす, JAP_TRANSITIVE ) // (v5s,vt) to kick away/to kick off/to kick (someone)/to refuse/to reject
 KanjiVerb( 蹴返す, JAP_TRANSITIVE ) // (v5s,vt) to kick back
 KanjiVerb( 蹴落す, JAP_TRANSITIVE ) // (v5s,vt) to kick down/to defeat
 KanjiVerb( 蹴立てる, JAP_TRANSITIVE ) // (v1,vt) to kick up
 KanjiVerb( 酬いる, JAP_TRANSITIVE ) // (v1,vt) to reward/to recompense/to repay
 KanjiVerb( 酬う, JAP_TRANSITIVE ) // (v5u,vt) to reward/to recompense/to repay
 KanjiVerb( 集める, JAP_TRANSITIVE ) // (v1,vt) to collect/to assemble/(P)
 KanjiVerb( 住み荒らす, JAP_TRANSITIVE ) // (v5s,vt) to leave a house in bad shape
 KanjiVerb( 住み替える, JAP_TRANSITIVE ) // (v1,vt) to change one's residence
 KanjiVerb( 充てがう, JAP_TRANSITIVE ) // (v5u,vt) (1) to allot/to allocate/(2) to supply with/to furnish/(3) to fit to/to fasten to/to apply to
 KanjiVerb( 充てる, JAP_TRANSITIVE ) // (v1,vt) to assign/to set aside/(P)
 KanjiVerb( 従える, JAP_TRANSITIVE ) // (v1,vt) (1) to be accompanied by/(2) to subdue/(P)
 KanjiVerb( 重ねる, JAP_TRANSITIVE ) // (v1,vt) to pile up/to put something on another/to heap up/to add/to repeat/(P)
 KanjiVerb( 重んじる, JAP_TRANSITIVE ) // (v1,vt) to respect/to honor/to honour/to esteem/to prize/(P)
 KanjiVerb( 重んずる, JAP_TRANSITIVE ) // (vz,vt) to honor/to honour/to respect/to esteem/to prize/(P)
 KanjiVerb( 祝う, JAP_TRANSITIVE ) // (v5u,vt) to congratulate/to celebrate/(P)
 KanjiVerb( 縮める, JAP_TRANSITIVE ) // (v1,vt) to shorten/to reduce/to boil down/to shrink/(P)
 KanjiVerb( 縮らす, JAP_TRANSITIVE ) // (v5s,vt) to curl/to crimp
 KanjiVerb( 熟す, JAP_TRANSITIVE ) // (v5s,vt) to ripen/to mature
 KanjiVerb( 出かす, JAP_TRANSITIVE ) // (v5s,vt) to do/to commit/to accomplish/to achieve
 KanjiVerb( 出し合う, JAP_TRANSITIVE ) // (v5u,vt) to contribute jointly
 KanjiVerb( 出し惜しむ, JAP_TRANSITIVE ) // (v5m,vt) to grudge/to be stingy/to be unwilling to pay
 KanjiVerb( 出し抜く, JAP_TRANSITIVE ) // (v5k,vt) to forestall/to anticipate/to jump the gun on/to outwit/to circumvent/to steal a march on
 KanjiVerb( 出す, JAP_TRANSITIVE ) // (v5s,vt) (1) to take out/to get out/(2) to put out/(3) to submit (e.g., thesis)/to turn in/(4) to publish/to make public/(5) to send (e.g., letter)/(6) to start (fire)/(P)
 KanjiVerb( 出迎える, JAP_TRANSITIVE ) // (v1,vt) to meet/to greet/(P)
 KanjiVerb( 出来す, JAP_TRANSITIVE ) // (v5s,vt) to do/to commit/to accomplish/to achieve
 KanjiVerb( 述べる, JAP_TRANSITIVE ) // (v1,vt) to state/to express/to mention/(P)
 KanjiVerb( 瞬く, JAP_TRANSITIVE ) // (v5k,vt) to wink/to blink
 KanjiVerb( 准える, JAP_TRANSITIVE ) // (v1,vt) to pattern after/to liken to/to imitate
 KanjiVerb( 準える, JAP_TRANSITIVE ) // (v1,vt) to pattern after/to liken to/to imitate/(P)
 KanjiVerb( 潤かす, JAP_TRANSITIVE ) // (v5s,vt) (uk) to soak/to steep/to macerate
 KanjiVerb( 潤す, JAP_TRANSITIVE ) // (v5s,vt) to moisten/to wet/profit/to enrich/to benefit/(P)
 KanjiVerb( 巡らす, JAP_TRANSITIVE ) // (v5s,vt) to enclose (with)/to surround (with)/to encircle/to think over/to work out
 KanjiVerb( 順序立てる, JAP_TRANSITIVE ) // (v1,vt) to put into order/to arrange (one's thoughts)
 KanjiVerb( 書きつける, JAP_TRANSITIVE ) // (v1,vt) to write down
 KanjiVerb( 書きとめる, JAP_TRANSITIVE ) // (v1,vt) to write down/to leave a note behind/to record/to chronicle
 KanjiVerb( 書き下す, JAP_TRANSITIVE ) // (v5s,vt) to write down
 KanjiVerb( 書き下ろす, JAP_TRANSITIVE ) // (v5s,vt) to write a play, book, filmscript, etc.
 KanjiVerb( 書き加える, JAP_TRANSITIVE ) // (v1,vt) to add (e.g., a postscript)
 KanjiVerb( 書き改める, JAP_TRANSITIVE ) // (v1,vt) to rewrite/to adapt (e.g., a novel)
 KanjiVerb( 書き換える, JAP_TRANSITIVE ) // (v1,vt) to rewrite/to overwrite/to renew/to transfer/(P)
 KanjiVerb( 書き記す, JAP_TRANSITIVE ) // (v5s,vt) to write down/to record/to register
 KanjiVerb( 書き込む, JAP_TRANSITIVE ) // (v5m,vt) (1) to fill in (writing)/(2) to post a message (e.g., on a bulletin-board)/to store/(P)
 KanjiVerb( 書き散らす, JAP_TRANSITIVE ) // (v5s,vt) to scribble/to scrawl
 KanjiVerb( 書き残す, JAP_TRANSITIVE ) // (v5s,vt) to leave a note or document behind/to leave half-written/to leave out
 KanjiVerb( 書き止める, JAP_TRANSITIVE ) // (v1,vt) to write down/to leave a note behind/to record/to chronicle
 KanjiVerb( 書き写す, JAP_TRANSITIVE ) // (v5s,vt) to transcribe
 KanjiVerb( 書き捨てる, JAP_TRANSITIVE ) // (v1,vt) to write and throw away/to write carelessly/to begin writing then stop part-way through
 KanjiVerb( 書き集める, JAP_TRANSITIVE ) // (v1,vt) to collect (writings)
 KanjiVerb( 書き出す, JAP_TRANSITIVE ) // (v5s,vt) to begin to write/to write out/to export (file)/to extract
 KanjiVerb( 書き上げる, JAP_TRANSITIVE ) // (v1,vt) to write out or down/to finish writing/(P)
 KanjiVerb( 書き足す, JAP_TRANSITIVE ) // (v5s,vt) to add to/to insert
 KanjiVerb( 書き続ける, JAP_TRANSITIVE ) // (v1,vt) to continue writing
 KanjiVerb( 書き替える, JAP_TRANSITIVE ) // (v1,vt) to rewrite/to overwrite/to renew/to transfer
 KanjiVerb( 書き直す, JAP_TRANSITIVE ) // (v5s,vt) to write out/to make a fair copy/(P)
 KanjiVerb( 書き添える, JAP_TRANSITIVE ) // (v1,vt) to add/to write a postscript
 KanjiVerb( 書き伝える, JAP_TRANSITIVE ) // (v1,vt) to record for transmission to posterity
 KanjiVerb( 書き入れる, JAP_TRANSITIVE ) // (v1,vt) to write in
 KanjiVerb( 書き抜く, JAP_TRANSITIVE ) // (v5k,vt) to extract
 KanjiVerb( 書き飛ばす, JAP_TRANSITIVE ) // (v5s,vt) to write (dash) off
 KanjiVerb( 書き表す, JAP_TRANSITIVE ) // (v5s,vt) (1) to write out/to express/to describe/(2) to publish
 KanjiVerb( 書き表わす, JAP_TRANSITIVE ) // (v5s,vt) (1) to write out/to express/to describe/(2) to publish
 KanjiVerb( 書き付ける, JAP_TRANSITIVE ) // (v1,vt) to write down
 KanjiVerb( 書き分ける, JAP_TRANSITIVE ) // (v1,vt) to classify and write up
 KanjiVerb( 書き並べる, JAP_TRANSITIVE ) // (v1,vt) to line up points in a speech
 KanjiVerb( 書き落す, JAP_TRANSITIVE ) // (v5s,vt) to leave out/to forget to write
 KanjiVerb( 書き立てる, JAP_TRANSITIVE ) // (v1,vt) to write up
 KanjiVerb( 書き流す, JAP_TRANSITIVE ) // (v5s,vt) to write off
 KanjiVerb( 書き留める, JAP_TRANSITIVE ) // (v1,vt) to write down/to leave a note behind/to record/to chronicle
 KanjiVerb( 書き連ねる, JAP_TRANSITIVE ) // (v1,vt) to make a list/to enumerate
 KanjiVerb( 書き漏らす, JAP_TRANSITIVE ) // (v5s,vt) leave out/forget to write
 KanjiVerb( 書く, JAP_TRANSITIVE ) // (v5k,vt) to write/(P)
 KanjiVerb( 書換える, JAP_TRANSITIVE ) // (v1,vt) to rewrite/to overwrite/to renew/to transfer
 KanjiVerb( 書散らす, JAP_TRANSITIVE ) // (v5s,vt) to scribble/to scrawl
 KanjiVerb( 書添える, JAP_TRANSITIVE ) // (v1,vt) to add/to write a postscript
 KanjiVerb( 助く, JAP_TRANSITIVE ) // (v5k,vt) to help/to save/to rescue
 KanjiVerb( 助ける, JAP_TRANSITIVE ) // (v1,vt) to help/to save/to rescue/to give relief to/to spare (life)/to reinforce/to promote/to abet/(P)
 KanjiVerb( 鋤返す, JAP_TRANSITIVE ) // (v5s,vt) to plow (up)/to plough (up)
 KanjiVerb( 除く, JAP_TRANSITIVE ) // (v5k,vt) to remove/to exclude/to except/(P)
 KanjiVerb( 除ける, JAP_TRANSITIVE ) // (v1,vt) to remove/to take away/to dislodge/to put something out of the way
 KanjiVerb( 傷める, JAP_TRANSITIVE ) // (v1,vt) to damage/to impair/to spoil/(P)
 KanjiVerb( 償う, JAP_TRANSITIVE ) // (v5u,vt) to make up for/to recompense/to redeem (one's faults)/to compensate for/to indemnify/to atone for/(P)
 KanjiVerb( 勝ち得る, JAP_TRANSITIVE ) // (v1,vt) to achieve/to win/to gain/to attain
 KanjiVerb( 召し寄せる, JAP_TRANSITIVE ) // (v1,vt) to call (someone) to you/to call together/to call to come
 KanjiVerb( 召し使う, JAP_TRANSITIVE ) // (v5u,vt) to employ
 KanjiVerb( 召し出す, JAP_TRANSITIVE ) // (v5s,vt) to call out/to summon
 KanjiVerb( 召し上げる, JAP_TRANSITIVE ) // (v1,vt) to forfeit/to confiscate/to call out
 KanjiVerb( 召し入れる, JAP_TRANSITIVE ) // (v1,vt) to call in
 KanjiVerb( 召し抱える, JAP_TRANSITIVE ) // (v1,vt) to employ/to engage
 KanjiVerb( 召し連れる, JAP_TRANSITIVE ) // (v1,vt) to bring along/to accompany
 KanjiVerb( 召す, JAP_TRANSITIVE ) // (v5s,vt) (1) to call/to send for/(2) to put on/to wear/to take (a bath)/to ride in/to buy/to eat/to drink/to catch (a cold)/(P)
 KanjiVerb( 召使う, JAP_TRANSITIVE ) // (v5u,vt) to hire a servant
 KanjiVerb( 商う, JAP_TRANSITIVE ) // (v5u,vt) (1) to sell/(2) to handle/to trade in
 KanjiVerb( 唱える, JAP_TRANSITIVE ) // (v1,vt) to recite/to chant/to call upon/(P)
 KanjiVerb( 嘗める, JAP_TRANSITIVE ) // (v1,vt) to lick/to taste/to experience/to make fun of/to make light of/to put down/to treat with contempt
 KanjiVerb( 小突く, JAP_TRANSITIVE ) // (v5k,vt) to poke/to push
 KanjiVerb( 招く, JAP_TRANSITIVE ) // (v5k,vt) to invite/(P)
 KanjiVerb( 招じ入れる, JAP_TRANSITIVE ) // (v1,vt) to invite or usher in
 KanjiVerb( 消し止める, JAP_TRANSITIVE ) // (v1,vt) to put out/to extinguish
 KanjiVerb( 消す, JAP_TRANSITIVE ) // (v5s,vt) (1) to erase/to delete/(2) to turn off power/(3) to bump off (sl)/(P)
 KanjiVerb( 焼きつける, JAP_TRANSITIVE ) // (v1,vt) to bake/to plate/to print/to burn or bake into/to burn into one's memory
 KanjiVerb( 焼き捨てる, JAP_TRANSITIVE ) // (v1,vt) to burn up
 KanjiVerb( 焼き上げる, JAP_TRANSITIVE ) // (v1,vt) to burn/to roast/to grill/to bake
 KanjiVerb( 焼き直す, JAP_TRANSITIVE ) // (v5s,vt) to grill again/to rehash
 KanjiVerb( 焼き付ける, JAP_TRANSITIVE ) // (v1,vt) to bake/to plate/to print/to burn or bake into/to burn into one's memory
 KanjiVerb( 焼き払う, JAP_TRANSITIVE ) // (v5u,vt) to clear away by burning/to reduce to ashes
 KanjiVerb( 焼く, JAP_TRANSITIVE ) // (v5k,vt) to bake/to grill/(P)
 KanjiVerb( 焼べる, JAP_TRANSITIVE ) // (v1,vt) to throw on the fire/to burn
 KanjiVerb( 焼付ける, JAP_TRANSITIVE ) // (v1,vt) to bake/to plate/to print/to burn or bake into/to burn into one's memory
 KanjiVerb( 焦がす, JAP_TRANSITIVE ) // (v5s,vt) to burn/to scorch/to singe/to char/(P)
 KanjiVerb( 焦らす, JAP_TRANSITIVE ) // (v5s,vt) (uk) to irritate
 KanjiVerb( 照らす, JAP_TRANSITIVE ) // (v5s,vt) to shine on/to illuminate/(P)
 KanjiVerb( 省く, JAP_TRANSITIVE ) // (v5k,vt) to omit/to eliminate/to curtail/to economize/to economise/(P)
 KanjiVerb( 省みる, JAP_TRANSITIVE ) // (v1,vt) to reflect/(P)
 KanjiVerb( 称える, JAP_TRANSITIVE ) // (v1,vt) to assume the name of
 KanjiVerb( 笑い飛ばす, JAP_TRANSITIVE ) // (v5s,vt) to laugh at
 KanjiVerb( 証拠立てる, JAP_TRANSITIVE ) // (v1,vt) to prove/to substantiate
 KanjiVerb( 上げる, JAP_TRANSITIVE ) // (v1,vt) to give/to raise/to elevate/to fly (kites)/to praise/to increase/to advance/to promote/to vomit/to usher in/to admit/to send (to school)/to offer/to present/to leave with/to finish/to arrange (expenses)/to observe/to perform/to quote/to mention/to bear (a child)/to improve (talents)/to do up (the hair)/to arrest/to engage/to fry/(rains) to stop/(P)
 KanjiVerb( 乗す, JAP_TRANSITIVE ) // (v5s,vt) to place on (something)/to take on board/to give a ride to
 KanjiVerb( 乗せる, JAP_TRANSITIVE ) // (v1,vt) to place on (something)/to take on board/to give a ride/to let (one) take part/to impose on/to record/to mention/to load (luggage)/to publish/to run (an ad)/(P)
 KanjiVerb( 乗っける, JAP_TRANSITIVE ) // (v1,vt) to place (something) on (something)
 KanjiVerb( 乗りかける, JAP_TRANSITIVE ) // (v1,vt) to be about to board/to be riding on/to get on top of/to lean over/to set about/to collide with
 KanjiVerb( 乗り越す, JAP_TRANSITIVE ) // (v5s,vt) to ride past/to pass/to outdistance/(P)
 KanjiVerb( 乗り回す, JAP_TRANSITIVE ) // (v5s,vt) to drive (a car) around/to ride (a bicycle) around/(P)
 KanjiVerb( 乗り掛ける, JAP_TRANSITIVE ) // (v1,vt) to be about to board/to be riding on/to get on top of/to lean over/to set about/to collide with
 KanjiVerb( 乗り換える, JAP_TRANSITIVE ) // (v1,vt) to transfer (trains)/to change (bus, train)/(P)
 KanjiVerb( 乗り継ぐ, JAP_TRANSITIVE ) // (v5g,vt) to change
 KanjiVerb( 乗り捨てる, JAP_TRANSITIVE ) // (v1,vt) to get off/to abandon (a ship or vehicle)
 KanjiVerb( 乗り出す, JAP_TRANSITIVE ) // (v5s,vt) (1) to set out/to set sail/(2) to embark on/to begin to ride/(3) to lean forward/(P)
 KanjiVerb( 乗り上げる, JAP_TRANSITIVE ) // (v1,vt) to run aground/to be stranded
 KanjiVerb( 乗り替える, JAP_TRANSITIVE ) // (v1,vt) to transfer (trains)/to change (bus, train)
 KanjiVerb( 乗り馴らす, JAP_TRANSITIVE ) // (v5s,vt) to break in (a horse)
 KanjiVerb( 乗り入れる, JAP_TRANSITIVE ) // (v1,vt) to ride into (a place)/to drive into (a place)/extend (a line into a city)
 KanjiVerb( 乗越す, JAP_TRANSITIVE ) // (v5s,vt) to ride past/to pass/to outdistance/(P)
 KanjiVerb( 乗回す, JAP_TRANSITIVE ) // (v5s,vt) to drive (a car) around/to ride (a bicycle) around/(P)
 KanjiVerb( 畳みかける, JAP_TRANSITIVE ) // (v1,vt) (uk) to press for an answer/to shower questions on someone
 KanjiVerb( 畳み掛ける, JAP_TRANSITIVE ) // (v1,vt) (uk) to press for an answer/to shower questions on someone
 KanjiVerb( 畳み込む, JAP_TRANSITIVE ) // (v5m,vt) to fold in/to bear deep in mind/to follow up
 KanjiVerb( 畳む, JAP_TRANSITIVE ) // (v5m,vt) to fold (clothes)/(P)
 KanjiVerb( 蒸かす, JAP_TRANSITIVE ) // (v5s,vt) to steam/(P)
 KanjiVerb( 蒸し返す, JAP_TRANSITIVE ) // (v5s,vt) to reheat/to steam over/to bring up again/to take up again a problem that has been dealt with/(P)
 KanjiVerb( 蒸す, JAP_TRANSITIVE ) // (v5s,vt) to steam/to poultice/to be sultry/(P)
 KanjiVerb( 蒸らす, JAP_TRANSITIVE ) // (v5s,vt) to cook by steam
 KanjiVerb( 譲り合う, JAP_TRANSITIVE ) // (v5u,vt) to give and take/to make mutual concessions/to compromise
 KanjiVerb( 譲り受ける, JAP_TRANSITIVE ) // (v1,vt) to inherit/to receive/to take over by transfer
 KanjiVerb( 譲り渡す, JAP_TRANSITIVE ) // (v5s,vt) to hand over/to turn over/to cede/(P)
 KanjiVerb( 醸し出す, JAP_TRANSITIVE ) // (v5s,vt) to engender/to bring about
 KanjiVerb( 醸す, JAP_TRANSITIVE ) // (v5s,vt) to brew/to cause/to give rise to/to distill
 KanjiVerb( 飾りつける, JAP_TRANSITIVE ) // (v1,vt) to decorate/to display
 KanjiVerb( 飾り付ける, JAP_TRANSITIVE ) // (v1,vt) to decorate/to display
 KanjiVerb( 飾り立てる, JAP_TRANSITIVE ) // (v1,vt) to decorate gaudily/to deck out
 KanjiVerb( 拭う, JAP_TRANSITIVE ) // (v5u,vt) to wipe/(P)
 KanjiVerb( 拭き込む, JAP_TRANSITIVE ) // (v5m,vt) to wipe thoroughly/to polish
 KanjiVerb( 拭く, JAP_TRANSITIVE ) // (v5k,vt) to wipe/to dry/(P)
 KanjiVerb( 植えつける, JAP_TRANSITIVE ) // (v1,vt) to plant
 KanjiVerb( 植える, JAP_TRANSITIVE ) // (v1,vt) to plant/to grow/(P)
 KanjiVerb( 植え込む, JAP_TRANSITIVE ) // (v5m,vt) to plant
 KanjiVerb( 植え付ける, JAP_TRANSITIVE ) // (v1,vt) to plant
 KanjiVerb( 植付ける, JAP_TRANSITIVE ) // (v1,vt) to plant
 KanjiVerb( 殖やす, JAP_TRANSITIVE ) // (v5s,vt) to increase/to add to/to augment/(P)
 KanjiVerb( 織りあげる, JAP_TRANSITIVE ) // (v1,vt) to weave up into fabric
 KanjiVerb( 織りなす, JAP_TRANSITIVE ) // (v5s,vt) to interweave
 KanjiVerb( 織り込む, JAP_TRANSITIVE ) // (v5m,vt) to be incorporated in
 KanjiVerb( 織り出す, JAP_TRANSITIVE ) // (v5s,vt) to weave a pattern/to begin to weave
 KanjiVerb( 織り上げる, JAP_TRANSITIVE ) // (v1,vt) to weave up into fabric
 KanjiVerb( 織り成す, JAP_TRANSITIVE ) // (v5s,vt) to interweave
 KanjiVerb( 触れ込む, JAP_TRANSITIVE ) // (v5m,vt) to announce/to pretend to be/to pass off for/to pose as/to herald
 KanjiVerb( 食い詰める, JAP_TRANSITIVE ) // (v1,vt) to go broke
 KanjiVerb( 食い荒らす, JAP_TRANSITIVE ) // (v5s,vt) to devour/to work at various things/to eat some of everything
 KanjiVerb( 食い殺す, JAP_TRANSITIVE ) // (v5s,vt) to devour/to bite to death
 KanjiVerb( 食い散らす, JAP_TRANSITIVE ) // (v5s,vt) to eat untidily/to eat a bit of everything
 KanjiVerb( 食い止める, JAP_TRANSITIVE ) // (v1,vt) to check/to hold back/(P)
 KanjiVerb( 食い潰す, JAP_TRANSITIVE ) // (v5s,vt) to run through one's fortune in idleness
 KanjiVerb( 食い倒す, JAP_TRANSITIVE ) // (v5s,vt) to bilk/to eat up one's fortune
 KanjiVerb( 食う, JAP_TRANSITIVE ) // (v5u,vt) (male) (vulg) to eat/(P)
 KanjiVerb( 食べつける, JAP_TRANSITIVE ) // (v1,vt) to be used to eating
 KanjiVerb( 食べる, JAP_TRANSITIVE ) // (v1,vt) to eat/(P)
 KanjiVerb( 食べ汚す, JAP_TRANSITIVE ) // (v5s,vt) to eat messily
 KanjiVerb( 食べ過ぎる, JAP_TRANSITIVE ) // (v1,vt) to overeat/(P)
 KanjiVerb( 食べ残す, JAP_TRANSITIVE ) // (v5s,vt) to leave a dish half-eaten
 KanjiVerb( 食べ付ける, JAP_TRANSITIVE ) // (v1,vt) to be used to eating
 KanjiVerb( 食らう, JAP_TRANSITIVE ) // (v5u,vt) to eat/to drink/to receive (blow)/(P)
 KanjiVerb( 食らわせる, JAP_TRANSITIVE ) // (v1,vt) (1) to make someone eat/(2) to deal (a blow)/to play (a trick)
 KanjiVerb( 食わせる, JAP_TRANSITIVE ) // (v1,vt) (1) to feed/(2) to provide/(3) to inflict/(4) to cheat
 KanjiVerb( 食止める, JAP_TRANSITIVE ) // (v1,vt) to check/to hold back/(P)
 KanjiVerb( 辱める, JAP_TRANSITIVE ) // (v1,vt) to put to shame
 KanjiVerb( 伸し上げる, JAP_TRANSITIVE ) // (v1,vt) to promote/to make richer
 KanjiVerb( 伸ばす, JAP_TRANSITIVE ) // (v5s,vt) to lengthen/to stretch/to reach out/to postpone/to prolong/to extend/to grow (beard)/(P)
 KanjiVerb( 伸べ広げる, JAP_TRANSITIVE ) // (v1,vt) to stretch out
 KanjiVerb( 信じる, JAP_TRANSITIVE ) // (v1,vt) to believe/to believe in/to place trust in/to confide in/to have faith in/(P)
 KanjiVerb( 信ずる, JAP_TRANSITIVE ) // (vz,vt) to believe/to believe in/to place trust in/to confide in/to have faith in/(P)
 KanjiVerb( 侵す, JAP_TRANSITIVE ) // (v5s,vt) to invade/to raid/to trespass/to violate/to intrude on/(P)
 KanjiVerb( 寝かしつける, JAP_TRANSITIVE ) // (v1,vt) to lull (a child) to sleep/to put a person to sleep
 KanjiVerb( 寝かし付ける, JAP_TRANSITIVE ) // (v1,vt) to lull (a child) to sleep/to put a person to sleep
 KanjiVerb( 寝かせる, JAP_TRANSITIVE ) // (v1,vt) to put to bed/to lay down/to ferment/(P)
 KanjiVerb( 心掛ける, JAP_TRANSITIVE ) // (v1,vt) to bear in mind/to aim to do/(P)
 KanjiVerb( 心得る, JAP_TRANSITIVE ) // (v1,vt) to be informed/to have thorough knowledge/(P)
 KanjiVerb( 慎む, JAP_TRANSITIVE ) // (v5m,vt) to be careful/to be chaste or discreet/to abstain or refrain/(P)
 KanjiVerb( 振りかける, JAP_TRANSITIVE ) // (v1,vt) to sprinkle (salt, pepper) over
 KanjiVerb( 振りかざす, JAP_TRANSITIVE ) // (v5s,vt) to brandish (sword) over one's head
 KanjiVerb( 振り解く, JAP_TRANSITIVE ) // (v5k,vt) to shake and untangle
 KanjiVerb( 振り回す, JAP_TRANSITIVE ) // (v5s,vt) to wield/to brandish/to flourish/to wave (about)/to swing/to display/to show off/to abuse/(P)
 KanjiVerb( 振り掛ける, JAP_TRANSITIVE ) // (v1,vt) to sprinkle (salt, pepper) over
 KanjiVerb( 振り向ける, JAP_TRANSITIVE ) // (v1,vt) to turn
 KanjiVerb( 振り撒く, JAP_TRANSITIVE ) // (v5k,vt) to scatter/to sprinkle/to lavish
 KanjiVerb( 振り捨てる, JAP_TRANSITIVE ) // (v1,vt) to shake off/forsake
 KanjiVerb( 振り出す, JAP_TRANSITIVE ) // (v5s,vt) to shake and give/to start shaking/to shake out/to write (draw on) a check (cheque)
 KanjiVerb( 振り上げる, JAP_TRANSITIVE ) // (v1,vt) to raise overhead
 KanjiVerb( 振り替える, JAP_TRANSITIVE ) // (v1,vt) to change/to make up for
 KanjiVerb( 振り当てる, JAP_TRANSITIVE ) // (v1,vt) to assign/to allot
 KanjiVerb( 振り払う, JAP_TRANSITIVE ) // (v5u,vt) to shake off
 KanjiVerb( 振り分ける, JAP_TRANSITIVE ) // (v1,vt) to partition out/to divide among
 KanjiVerb( 振り放す, JAP_TRANSITIVE ) // (v5s,vt) to break free of
 KanjiVerb( 振り落す, JAP_TRANSITIVE ) // (v5s,vt) to shake off/to throw off
 KanjiVerb( 振り落とす, JAP_TRANSITIVE ) // (v5s,vt) to shake off/to throw off
 KanjiVerb( 振り乱す, JAP_TRANSITIVE ) // (v5s,vt) to dishevel (hair)
 KanjiVerb( 振り立てる, JAP_TRANSITIVE ) // (v1,vt) to toss (i.e. one's head)/to wave (i.e. a flag)/to stand up energetically/to raise one's voice
 KanjiVerb( 振り翳ざす, JAP_TRANSITIVE ) // (v5s,vt) to brandish (sword) over one's head
 KanjiVerb( 振り翳す, JAP_TRANSITIVE ) // (v5s,vt) to brandish (sword) over one's head
 KanjiVerb( 振る舞う, JAP_TRANSITIVE ) // (v5u,vt) to behave/to conduct oneself/to entertain/(P)
 KanjiVerb( 振舞う, JAP_TRANSITIVE ) // (v5u,vt) to behave/to conduct oneself/to entertain
 KanjiVerb( 浸す, JAP_TRANSITIVE ) // (v5s,vt) to soak/to dip/to drench/(P)
 KanjiVerb( 深める, JAP_TRANSITIVE ) // (v1,vt) to deepen/to heighten/to intensify/(P)
 KanjiVerb( 申しつける, JAP_TRANSITIVE ) // (v1,vt) to order/to instruct
 KanjiVerb( 申し越す, JAP_TRANSITIVE ) // (v5s,vt) to send word to/to write to
 KanjiVerb( 申し込む, JAP_TRANSITIVE ) // (v5m,vt) to apply for/to make an application/to propose (marriage)/to offer (mediation)/to make an overture (of peace)/to challenge/to lodge (objections)/to request (an interview)/to subscribe for/to book/to reserve/(P)
 KanjiVerb( 申し受ける, JAP_TRANSITIVE ) // (v1,vt) to accept/to ask for/to charge (a price)
 KanjiVerb( 申し出る, JAP_TRANSITIVE ) // (v1,vt) to report to/to tell/to suggest/to submit/to request/to make an offer/to come forward with information/(P)
 KanjiVerb( 申し述べる, JAP_TRANSITIVE ) // (v1,vt) to say/to tell (somebody)/to state
 KanjiVerb( 申し上げる, JAP_TRANSITIVE ) // (v1,vt) to say/to tell/to state/(P)
 KanjiVerb( 申し添える, JAP_TRANSITIVE ) // (v1,vt) to add to what has been said
 KanjiVerb( 申し渡す, JAP_TRANSITIVE ) // (v5s,vt) to tell/to announce/to declare/to order
 KanjiVerb( 申し入れる, JAP_TRANSITIVE ) // (v1,vt) to propose/to suggest/(P)
 KanjiVerb( 申し付ける, JAP_TRANSITIVE ) // (v1,vt) to order/to instruct
 KanjiVerb( 申し聞かせる, JAP_TRANSITIVE ) // (v1,vt) to tell/to talk to
 KanjiVerb( 申し立てる, JAP_TRANSITIVE ) // (v1,vt) to declare/to plead
 KanjiVerb( 申す, JAP_TRANSITIVE ) // (v5s,vt) (hum) to be called/to say/(P)
 KanjiVerb( 申込む, JAP_TRANSITIVE ) // (v5m,vt) to apply for/to make an application/to propose (marriage)/to offer (mediation)/to make an overture (of peace)/to challenge/to lodge (objections)/to request (an interview)/to subscribe for/to book/to reserve
 KanjiVerb( 申述べる, JAP_TRANSITIVE ) // (v1,vt) to say/to tell (somebody)/to state
 KanjiVerb( 真似る, JAP_TRANSITIVE ) // (v1,vt) to mimic/to imitate/(P)
 KanjiVerb( 進ぜる, JAP_TRANSITIVE ) // (v1,vt) to offer/to present
 KanjiVerb( 進める, JAP_TRANSITIVE ) // (v1,vt) to advance/to promote/to hasten/(P)
 KanjiVerb( 震わせる, JAP_TRANSITIVE ) // (v1,vt) to be shaking/to be trembling
 KanjiVerb( 尋ねる, JAP_TRANSITIVE ) // (v1,vt) to ask/to enquire/to inquire/(P)
 KanjiVerb( 尽かす, JAP_TRANSITIVE ) // (v5s,vt) to be disgusted with/to give up on
 KanjiVerb( 訊き返す, JAP_TRANSITIVE ) // (v5s,vt) to ask in return/to ask again/to listen repeatedly
 KanjiVerb( 訊ねる, JAP_TRANSITIVE ) // (v1,vt) to ask
 KanjiVerb( 吹かす, JAP_TRANSITIVE ) // (v5s,vt) to smoke (a cigarette)/to behave as ../to accelerate/to rev up
 KanjiVerb( 吹きかける, JAP_TRANSITIVE ) // (v1,vt) to blow upon/to spur/to force/to overcharge
 KanjiVerb( 吹きつける, JAP_TRANSITIVE ) // (v1,vt) to blow against/to spray (paint, etc.) (onto a surface)
 KanjiVerb( 吹き掛ける, JAP_TRANSITIVE ) // (v1,vt) to blow upon/to spur/to force/to overcharge
 KanjiVerb( 吹き散らす, JAP_TRANSITIVE ) // (v5s,vt) to scatter/to blow about
 KanjiVerb( 吹き消す, JAP_TRANSITIVE ) // (v5s,vt) to blow out (a flame)
 KanjiVerb( 吹き上げる, JAP_TRANSITIVE ) // (v1,vt) to blow up (i.e. wind)
 KanjiVerb( 吹き着ける, JAP_TRANSITIVE ) // (v1,vt) to blow against/to spray (paint, etc.) (onto a surface)
 KanjiVerb( 吹き通す, JAP_TRANSITIVE ) // (v5s,vt) to blow through/to blow ceaselessly
 KanjiVerb( 吹き倒す, JAP_TRANSITIVE ) // (v5s,vt) to blow over
 KanjiVerb( 吹き飛ばす, JAP_TRANSITIVE ) // (v5s,vt) to blow off/to brush away/to talk big
 KanjiVerb( 吹き付ける, JAP_TRANSITIVE ) // (v1,vt) to blow against/to spray (paint, etc.) (onto a surface)
 KanjiVerb( 吹き払う, JAP_TRANSITIVE ) // (v5u,vt) to blow off
 KanjiVerb( 吹き分ける, JAP_TRANSITIVE ) // (v1,vt) to blow apart/to winnow/to smelt
 KanjiVerb( 吹っかける, JAP_TRANSITIVE ) // (v1,vt) to blow upon/to provoke/to overcharge
 KanjiVerb( 吹っ掛ける, JAP_TRANSITIVE ) // (v1,vt) to blow upon/to provoke/to overcharge
 KanjiVerb( 吹付ける, JAP_TRANSITIVE ) // (v1,vt) to blow against/to spray (paint, etc.) (onto a surface)
 KanjiVerb( 垂らす, JAP_TRANSITIVE ) // (v5s,vt) (1) to dribble/to spill/(2) to suspend/to hang down/to slouch/to dangle/(P)
 KanjiVerb( 垂れ下げる, JAP_TRANSITIVE ) // (v1,vt) to hang (a curtain)/to droop (a tail)/to lower (a blind)
 KanjiVerb( 推し進める, JAP_TRANSITIVE ) // (v1,vt) to press forward
 KanjiVerb( 推す, JAP_TRANSITIVE ) // (v5s,vt) to infer/to conclude/to support/(P)
 KanjiVerb( 炊き込む, JAP_TRANSITIVE ) // (v5m,vt) to cook (something) with rice
 KanjiVerb( 炊く, JAP_TRANSITIVE ) // (v5k,vt) to boil/to cook/(P)
 KanjiVerb( 遂げる, JAP_TRANSITIVE ) // (v1,vt) to accomplish/to achieve/to carry out/(P)
 KanjiVerb( 崇める, JAP_TRANSITIVE ) // (v1,vt) to revere/to respect/to worship
 KanjiVerb( 数える, JAP_TRANSITIVE ) // (v1,vt) to count/to enumerate/(P)
 KanjiVerb( 数え上げる, JAP_TRANSITIVE ) // (v1,vt) to count up/to enumerate
 KanjiVerb( 数え立てる, JAP_TRANSITIVE ) // (v1,vt) to enumerate/to count up
 KanjiVerb( 据えつける, JAP_TRANSITIVE ) // (v1,vt) to install/to equip/to mount
 KanjiVerb( 据える, JAP_TRANSITIVE ) // (v1,vt) to set (table)/to lay (foundation)/to place (gun)/to apply (moxa)/(P)
 KanjiVerb( 据え置く, JAP_TRANSITIVE ) // (v5k,vt) to leave as it is/to defer
 KanjiVerb( 据え付ける, JAP_TRANSITIVE ) // (v1,vt) to install/to equip/to mount/(P)
 KanjiVerb( 澄ます, JAP_TRANSITIVE ) // (v5s,vt) to clear/to make clear/to be unruffled/to look unconcerned/to look demure/to look prim/to put on airs/(P)
 KanjiVerb( 成し遂げる, JAP_TRANSITIVE ) // (v1,vt) to accomplish/to finish/to fulfill/(P)
 KanjiVerb( 成す, JAP_TRANSITIVE ) // (v5s,vt) to perform/to accomplish/(P)
 KanjiVerb( 成り立つ, JAP_TRANSITIVE ) // (v5t,vi,vt) (1) to consist of/(2) to be practical (logical, feasible, viable)/to be concluded/to hold true/(P)
 KanjiVerb( 成立つ, JAP_TRANSITIVE ) // (v5t,vi,vt) (1) to consist of/(2) to be practical (logical, feasible, viable)/to be concluded/to hold true
 KanjiVerb( 整える, JAP_TRANSITIVE ) // (v1,vt) (1) to put in order/to arrange/to adjust/(2) to get ready/to prepare/(3) to raise money/(P)
 KanjiVerb( 晴らす, JAP_TRANSITIVE ) // (v5s,vt) to dispel/to clear away/to refresh (oneself)/(P)
 KanjiVerb( 正す, JAP_TRANSITIVE ) // (v5s,vt) to correct/to adjust/to reform/to redress/to straighten/to amend/(P)
 KanjiVerb( 清ます, JAP_TRANSITIVE ) // (v5s,vt) to clear/to make clear/to be unruffled/to look unconcerned/to look demure/to look prim/to put on airs
 KanjiVerb( 清める, JAP_TRANSITIVE ) // (v1,vt) to purify/to cleanse/to exorcise
 KanjiVerb( 生かす, JAP_TRANSITIVE ) // (v5s,vt) to revive/to resuscitate/to make use of/(P)
 KanjiVerb( 生ける, JAP_TRANSITIVE ) // (v1,vt) to arrange (flowers)/(P)
 KanjiVerb( 生みつける, JAP_TRANSITIVE ) // (v1,vt) to lay/to spawn
 KanjiVerb( 生み出す, JAP_TRANSITIVE ) // (v5s,vt) (1) to bring forth/to bear/to give birth to/to produce/(2) to invent/(P)
 KanjiVerb( 生み付ける, JAP_TRANSITIVE ) // (v1,vt) to lay/to spawn
 KanjiVerb( 生み落す, JAP_TRANSITIVE ) // (v5s,vt) to give birth to/to drop (calf or foal)
 KanjiVerb( 生み落とす, JAP_TRANSITIVE ) // (v5s,vt) to give birth to/to drop (calf or foal)
 KanjiVerb( 生む, JAP_TRANSITIVE ) // (v5m,vt) to give birth/to deliver/to produce/(P)
 KanjiVerb( 生やす, JAP_TRANSITIVE ) // (v5s,vt) to grow/to cultivate/to wear beard/(P)
 KanjiVerb( 盛りつける, JAP_TRANSITIVE ) // (v1,vt) to dish up
 KanjiVerb( 盛り込む, JAP_TRANSITIVE ) // (v5m,vt) to incorporate/to include/(P)
 KanjiVerb( 盛り殺す, JAP_TRANSITIVE ) // (v5s,vt) to poison to death/to kill by a prescription error
 KanjiVerb( 盛り上げる, JAP_TRANSITIVE ) // (v1,vt) to pile up/to heap up/to stir up/to bring to a climax/to raise/(P)
 KanjiVerb( 盛り付ける, JAP_TRANSITIVE ) // (v1,vt) to dish up
 KanjiVerb( 盛り返す, JAP_TRANSITIVE ) // (v5s,vt) to rally/to make a comeback
 KanjiVerb( 精げる, JAP_TRANSITIVE ) // (v1,vt) to polish (rice)/to refine/to purify
 KanjiVerb( 誓う, JAP_TRANSITIVE ) // (v5u,vt) to swear/to vow/to take an oath/to pledge/(P)
 KanjiVerb( 請う, JAP_TRANSITIVE ) // (v5u-s,vt) to ask/to request/to invite/(P)
 KanjiVerb( 請ける, JAP_TRANSITIVE ) // (v1,vt) to receive/to accept/(P)
 KanjiVerb( 請け合う, JAP_TRANSITIVE ) // (v5u,vt) to assure/to guarantee/to undertake
 KanjiVerb( 請け出す, JAP_TRANSITIVE ) // (v5s,vt) to redeem/to take out of pawn
 KanjiVerb( 請け負う, JAP_TRANSITIVE ) // (v5u,vt) to contract/to undertake/(P)
 KanjiVerb( 請じ入れる, JAP_TRANSITIVE ) // (v1,vt) to invite or usher in
 KanjiVerb( 請合う, JAP_TRANSITIVE ) // (v5u,vt) to assure/to guarantee/to undertake
 KanjiVerb( 醒ます, JAP_TRANSITIVE ) // (v5s,vt) (1) to awaken/(2) to disabuse/(3) to sober up
 KanjiVerb( 静める, JAP_TRANSITIVE ) // (v1,vt) to appease/to suppress/to calm
 KanjiVerb( 斉える, JAP_TRANSITIVE ) // (v1,vt) (1) to put in order/to arrange/to adjust/(2) to get ready/to prepare/(3) to raise money
 KanjiVerb( 惜しむ, JAP_TRANSITIVE ) // (v5m,vt) (1) to be frugal/to be sparing/(2) to value/to hold dear/(3) to regret (e.g., a loss)/to feel sorry (for)/(4) to be unwilling/to be reluctant/(P)
 KanjiVerb( 斥ける, JAP_TRANSITIVE ) // (v1,vt) to repel/to drive away/to repulse/to reject
 KanjiVerb( 積み込む, JAP_TRANSITIVE ) // (v5m,vt) to load (with goods, cargo)/to put on board/to stow aboard/(P)
 KanjiVerb( 積み残す, JAP_TRANSITIVE ) // (v5s,vt) to leave off cargo
 KanjiVerb( 積み重ねる, JAP_TRANSITIVE ) // (v1,vt) to be piled up/to accumulate/(P)
 KanjiVerb( 積み出す, JAP_TRANSITIVE ) // (v5s,vt) to send off
 KanjiVerb( 積み上げる, JAP_TRANSITIVE ) // (v1,vt) to pile up/to make a heap/to lay bricks
 KanjiVerb( 積み替える, JAP_TRANSITIVE ) // (v1,vt) to transship
 KanjiVerb( 積み直す, JAP_TRANSITIVE ) // (v5s,vt) to reload
 KanjiVerb( 積み立てる, JAP_TRANSITIVE ) // (v1,vt) to accumulate/to save
 KanjiVerb( 責っ付く, JAP_TRANSITIVE ) // (v5k,vt) (uk) to pester someone (e.g., to buy something)
 KanjiVerb( 責めつける, JAP_TRANSITIVE ) // (v1,vt) to heap blame upon
 KanjiVerb( 責める, JAP_TRANSITIVE ) // (v1,vt) to condemn/to blame/to criticize/to criticise/(P)
 KanjiVerb( 責め付ける, JAP_TRANSITIVE ) // (v1,vt) to heap blame upon
 KanjiVerb( 責め立てる, JAP_TRANSITIVE ) // (v1,vt) to torture severely/to urge
 KanjiVerb( 責付く, JAP_TRANSITIVE ) // (v5k,vt) (uk) to pester someone (e.g., to buy something)
 KanjiVerb( 赤らめる, JAP_TRANSITIVE ) // (v1,vt) to blush/to redden
 KanjiVerb( 跡付ける, JAP_TRANSITIVE ) // (v1,vt) to trace/to inquire into
 KanjiVerb( 切らす, JAP_TRANSITIVE ) // (v5s,vt) to be out of/to run out of/to be short of/to be out of stock/(P)
 KanjiVerb( 切りつける, JAP_TRANSITIVE ) // (v1,vt) to cut at/to slash at
 KanjiVerb( 切り下げる, JAP_TRANSITIVE ) // (v1,vt) (1) to cut down/to prune/to reduce/to cut and hang down/to cut shorter/(2) to round down (e.g. fraction)
 KanjiVerb( 切り下ろす, JAP_TRANSITIVE ) // (v5s,vt) to slash downward
 KanjiVerb( 切り苛む, JAP_TRANSITIVE ) // (v5m,vt) to cut to pieces/to torment
 KanjiVerb( 切り解く, JAP_TRANSITIVE ) // (v5k,vt) to cut open a tied bundle/releasing prisoners
 KanjiVerb( 切り回す, JAP_TRANSITIVE ) // (v5s,vt) to run around killing/to manage everything/to control/to cut carelessly (a cook or surgeon)
 KanjiVerb( 切り開く, JAP_TRANSITIVE ) // (v5k,vt) to clear (land)/to open up/to cut through
 KanjiVerb( 切り外す, JAP_TRANSITIVE ) // (v5s,vt) to miss in attempting to kill
 KanjiVerb( 切り換える, JAP_TRANSITIVE ) // (v1,vt) to change/to exchange/to convert/to renew/to throw a switch/to replace/to switch over
 KanjiVerb( 切り詰める, JAP_TRANSITIVE ) // (v1,vt) to shorten/to reduce/to economize/to economise
 KanjiVerb( 切り刻む, JAP_TRANSITIVE ) // (v5m,vt) to hew/to chop up/to mangle/to mince
 KanjiVerb( 切り細裂く, JAP_TRANSITIVE ) // (v5k,vt) to cut up small
 KanjiVerb( 切り殺す, JAP_TRANSITIVE ) // (v5s,vt) to slay
 KanjiVerb( 切り散らす, JAP_TRANSITIVE ) // (v5s,vt) to cut down all/to slash promiscuously
 KanjiVerb( 切り捨てる, JAP_TRANSITIVE ) // (v1,vt) to truncate/to cut down/to omit/to discard/to slay/to cast away/(P)
 KanjiVerb( 切り出す, JAP_TRANSITIVE ) // (v5s,vt) to quarry/to cut (timber)/to cut and carry off/to begin to talk/to break the ice/to broach/to bring down
 KanjiVerb( 切り上げる, JAP_TRANSITIVE ) // (v1,vt) (1) to close/to finish/(2) to round up (a number)/(3) to revalue (a currency)
 KanjiVerb( 切り組む, JAP_TRANSITIVE ) // (v5m,vt) to piece together/to mortise/to miter/to dovetail
 KanjiVerb( 切り揃える, JAP_TRANSITIVE ) // (v1,vt) to cut and even up/to cut several pieces to the same size
 KanjiVerb( 切り替える, JAP_TRANSITIVE ) // (v1,vt) to change/to exchange/to convert/to renew/to throw a switch/to replace/to switch over
 KanjiVerb( 切り調える, JAP_TRANSITIVE ) // (v1,vt) to trim (hedges)
 KanjiVerb( 切り通す, JAP_TRANSITIVE ) // (v5s,vt) to cut through (with a road, tunnel, or canal)
 KanjiVerb( 切り倒す, JAP_TRANSITIVE ) // (v5s,vt) to cut down/to chop down/to fell
 KanjiVerb( 切り抜ける, JAP_TRANSITIVE ) // (v1,vt) to cut one's way through/to tide over/to struggle through/to get over
 KanjiVerb( 切り付ける, JAP_TRANSITIVE ) // (v1,vt) to cut at/to slash at
 KanjiVerb( 切り伏せる, JAP_TRANSITIVE ) // (v1,vt) to slay/to cut down (a foe)
 KanjiVerb( 切り払う, JAP_TRANSITIVE ) // (v5u,vt) to clear away/to clear land/to prune/to lop off
 KanjiVerb( 切り変える, JAP_TRANSITIVE ) // (v1,vt) to change/to exchange/to convert/to renew/to throw a switch/to replace/to switch over
 KanjiVerb( 切り返す, JAP_TRANSITIVE ) // (v5s,vt) to slash or strike back/to counterattack
 KanjiVerb( 切り崩す, JAP_TRANSITIVE ) // (v5s,vt) (1) to level (earth)/to cut through (a mountain)/(2) to split (the opposition)/to break (strike)/(P)
 KanjiVerb( 切り放す, JAP_TRANSITIVE ) // (v5s,vt) to cut loose/to let loose/to cut off/to detach/to dismember/to cut in two
 KanjiVerb( 切り放つ, JAP_TRANSITIVE ) // (v5t,vt) to cut loose/to let loose/to cut off/to detach/to dismember/to cut in two
 KanjiVerb( 切り落とす, JAP_TRANSITIVE ) // (v5s,vt) to cut down/to lop off/to prune
 KanjiVerb( 切り離す, JAP_TRANSITIVE ) // (v5s,vt) to detach/to decapitate/(P)
 KanjiVerb( 切り立てる, JAP_TRANSITIVE ) // (v1,vt) to cut/to slash/to slay all
 KanjiVerb( 切り裂く, JAP_TRANSITIVE ) // (v5k,vt) to cut off/to cut up/to tear to pieces
 KanjiVerb( 切換える, JAP_TRANSITIVE ) // (v1,vt) to change/to exchange/to convert/to renew/to throw a switch/to replace/to switch over
 KanjiVerb( 切上げる, JAP_TRANSITIVE ) // (v1,vt) (1) to close/to finish/(2) to round up (a number)/(3) to revalue (a currency)
 KanjiVerb( 切替える, JAP_TRANSITIVE ) // (v1,vt) to change/to exchange/to convert/to renew/to throw a switch/to replace/to switch over
 KanjiVerb( 接ぐ, JAP_TRANSITIVE ) // (v5g,vt) (1) to join/(2) to piece together/(3) to set (bones)/(4) to graft (trees)
 KanjiVerb( 折り曲げる, JAP_TRANSITIVE ) // (v1,vt) to bend/to turn up/to turn down/to double
 KanjiVerb( 折り込む, JAP_TRANSITIVE ) // (v5m,vt) to fold inside
 KanjiVerb( 折り重ねる, JAP_TRANSITIVE ) // (v1,vt) to fold back (up)
 KanjiVerb( 折り畳む, JAP_TRANSITIVE ) // (v5m,vt) to fold up/to fold into layers
 KanjiVerb( 折り返す, JAP_TRANSITIVE ) // (v5s,vt) to turn up/to fold back/(P)
 KanjiVerb( 折曲げる, JAP_TRANSITIVE ) // (v1,vt) to bend/to turn up/to turn down/to double
 KanjiVerb( 設える, JAP_TRANSITIVE ) // (v1,vt) to provide/to arrange/to install
 KanjiVerb( 設ける, JAP_TRANSITIVE ) // (v1,vt) to create/to establish/(P)
 KanjiVerb( 説きつける, JAP_TRANSITIVE ) // (v1,vt) to persuade
 KanjiVerb( 説き勧める, JAP_TRANSITIVE ) // (v1,vt) to persuade
 KanjiVerb( 説き付ける, JAP_TRANSITIVE ) // (v1,vt) to persuade
 KanjiVerb( 説き伏せる, JAP_TRANSITIVE ) // (v1,vt) to confute/to argue down
 KanjiVerb( 説き分ける, JAP_TRANSITIVE ) // (v1,vt) to explain carefully or by making distinctions
 KanjiVerb( 説き聞かせる, JAP_TRANSITIVE ) // (v1,vt) to explain/to reason
 KanjiVerb( 説き明かす, JAP_TRANSITIVE ) // (v5s,vt) to explain/to solve/to make clear
 KanjiVerb( 雪ぐ, JAP_TRANSITIVE ) // (v5g,vt) to rinse/to wash out
 KanjiVerb( 絶つ, JAP_TRANSITIVE ) // (v5t,vt) to sever/to cut off/to suppress/to abstain (from)/(P)
 KanjiVerb( 絶やす, JAP_TRANSITIVE ) // (v5s,vt) (1) to exterminate/to eradicate/(2) to let (fire) go out/(P)
 KanjiVerb( 先立てる, JAP_TRANSITIVE ) // (v1,vt) to have (someone) go ahead
 KanjiVerb( 占う, JAP_TRANSITIVE ) // (v5u,vt) to forecast/to predict/(P)
 KanjiVerb( 占む, JAP_TRANSITIVE ) // (v5m,vt) (arch) to occupy/to hold/to command/to account for
 KanjiVerb( 占める, JAP_TRANSITIVE ) // (v1,vt) (1) to comprise/to account for/to make up (of)/(2) to hold/to occupy/(P)
 KanjiVerb( 扇ぎ立てる, JAP_TRANSITIVE ) // (v1,vt) to fan incessantly/to agitate/to instigate
 KanjiVerb( 扇ぐ, JAP_TRANSITIVE ) // (v5g,vt) to fan/to flap/(P)
 KanjiVerb( 洗い出す, JAP_TRANSITIVE ) // (v5s,vt) to bring to light
 KanjiVerb( 洗い上げる, JAP_TRANSITIVE ) // (v1,vt) to finish washing/to wash well/to investigate thoroughly/(P)
 KanjiVerb( 洗い直す, JAP_TRANSITIVE ) // (v5s,vt) to wash again/to reconsider
 KanjiVerb( 洗い立てる, JAP_TRANSITIVE ) // (v1,vt) (1) to examine closely/to check up on/to ferret out/(2) to wash carefully
 KanjiVerb( 洗い流す, JAP_TRANSITIVE ) // (v5s,vt) to wash away
 KanjiVerb( 洗う, JAP_TRANSITIVE ) // (v5u,vt) to wash/(P)
 KanjiVerb( 染めつける, JAP_TRANSITIVE ) // (v1,vt) to dye (in patterns)
 KanjiVerb( 染める, JAP_TRANSITIVE ) // (v1,vt) to dye/to colour/to color/(P)
 KanjiVerb( 染め込む, JAP_TRANSITIVE ) // (v5m,vt) to dye
 KanjiVerb( 染め出す, JAP_TRANSITIVE ) // (v5s,vt) to dye
 KanjiVerb( 染め上げる, JAP_TRANSITIVE ) // (v1,vt) to finish dyeing
 KanjiVerb( 染め直す, JAP_TRANSITIVE ) // (v5s,vt) to dye again
 KanjiVerb( 染め抜く, JAP_TRANSITIVE ) // (v5k,vt) to dye fast/to leave undyed
 KanjiVerb( 染め付ける, JAP_TRANSITIVE ) // (v1,vt) to dye (in patterns)
 KanjiVerb( 染め分ける, JAP_TRANSITIVE ) // (v1,vt) to dye in different colors (colours)
 KanjiVerb( 染め返す, JAP_TRANSITIVE ) // (v5s,vt) to dye again
 KanjiVerb( 潜める, JAP_TRANSITIVE ) // (v1,vt) to hide/to conceal
 KanjiVerb( 煎じる, JAP_TRANSITIVE ) // (v1,vt) to boil/to decoct/to infuse
 KanjiVerb( 煎じ詰める, JAP_TRANSITIVE ) // (v1,vt) to boil down/to condense
 KanjiVerb( 煎じ出す, JAP_TRANSITIVE ) // (v5s,vt) to extract by broiling/to prepare an infusion of/to decoct
 KanjiVerb( 煎りつける, JAP_TRANSITIVE ) // (v1,vt) to parch/to roast/to broil/to scorch
 KanjiVerb( 煎り付ける, JAP_TRANSITIVE ) // (v1,vt) to parch/to roast/to broil/to scorch
 KanjiVerb( 煽ぎ立てる, JAP_TRANSITIVE ) // (v1,vt) to fan incessantly/to agitate/to instigate
 KanjiVerb( 煽ぐ, JAP_TRANSITIVE ) // (v5g,vt) to fan/to flap
 KanjiVerb( 煽てる, JAP_TRANSITIVE ) // (v1,vt) to stir up/to instigate/to flatter/(P)
 KanjiVerb( 穿く, JAP_TRANSITIVE ) // (v5k,vt) to wear/to put on (lower body, e.g., a sword)
 KanjiVerb( 穿つ, JAP_TRANSITIVE ) // (v5t,vt) to drill/to bore/to pierce/to put on/to wear/to be true to (nature)/to hit (the mark)
 KanjiVerb( 羨む, JAP_TRANSITIVE ) // (v5m,vt) to envy
 KanjiVerb( 薦める, JAP_TRANSITIVE ) // (v1,vt) to recommend/to advise/to encourage/to offer (wine)/(P)
 KanjiVerb( 選び出す, JAP_TRANSITIVE ) // (v5s,vt) to select/to pick out
 KanjiVerb( 選ぶ, JAP_TRANSITIVE ) // (v5b,vt) to choose/to select/(P)
 KanjiVerb( 選り出す, JAP_TRANSITIVE ) // (v5s,vt) to select/to pick out
 KanjiVerb( 選り抜く, JAP_TRANSITIVE ) // (v5k,vt) to select/to choose
 KanjiVerb( 選り分ける, JAP_TRANSITIVE ) // (v1,vt) to classify/to sort out/(P)
 KanjiVerb( 閃かす, JAP_TRANSITIVE ) // (v5s,vt) to brandish/to flash/to display
 KanjiVerb( 繕う, JAP_TRANSITIVE ) // (v5u,vt) to mend/to repair/to fix/to patch up/to darn/to tidy up/to adjust/to trim/(P)
 KanjiVerb( 狙い澄ます, JAP_TRANSITIVE ) // (v5s,vt) to take careful aim
 KanjiVerb( 狙う, JAP_TRANSITIVE ) // (v5u,vt) to aim at/(P)
 KanjiVerb( 疎む, JAP_TRANSITIVE ) // (v5m,vt) to neglect/to shun/to alienate
 KanjiVerb( 疎んじる, JAP_TRANSITIVE ) // (v1,vt) to neglect/to shun/to alienate/to distance oneself from
 KanjiVerb( 素っ破抜く, JAP_TRANSITIVE ) // (v5k,vt) to expose/to disclose/to unmask
 KanjiVerb( 素破抜く, JAP_TRANSITIVE ) // (v5k,vt) to expose/to disclose/to unmask
 KanjiVerb( 組み込む, JAP_TRANSITIVE ) // (v5m,vt) to insert/to include/to cut in (printing)/(P)
 KanjiVerb( 組み上げる, JAP_TRANSITIVE ) // (v1,vt) to compose/to put together
 KanjiVerb( 組み替える, JAP_TRANSITIVE ) // (v1,vt) to rearrange (classes)/to recompose/to reset/to recombine (genes)
 KanjiVerb( 組み入れる, JAP_TRANSITIVE ) // (v1,vt) to include/to insert/to ladle water into/to take into consideration
 KanjiVerb( 組み敷く, JAP_TRANSITIVE ) // (v5k,vt) to press down/to hold down/to pin down
 KanjiVerb( 組み伏せる, JAP_TRANSITIVE ) // (v1,vt) to hold down
 KanjiVerb( 組み立てる, JAP_TRANSITIVE ) // (v1,vt) to assemble/to set up/to construct/(P)
 KanjiVerb( 組入れる, JAP_TRANSITIVE ) // (v1,vt) to include/to insert/to ladle water into/to take into consideration
 KanjiVerb( 組敷く, JAP_TRANSITIVE ) // (v5k,vt) to press down/to hold down/to pin down
 KanjiVerb( 訴える, JAP_TRANSITIVE ) // (v1,vt) to sue (a person)/to resort to/to appeal to/(P)
 KanjiVerb( 創める, JAP_TRANSITIVE ) // (v1,vt) to start/to originate
 KanjiVerb( 奏する, JAP_TRANSITIVE ) // (vt,vs-s) to report to the Emperor/to play (musical instrument)/to accomplish
 KanjiVerb( 想う, JAP_TRANSITIVE ) // (v5u,vt) to think/to feel
 KanjiVerb( 捜し出す, JAP_TRANSITIVE ) // (v5s,vt) to locate/to discover
 KanjiVerb( 捜し当てる, JAP_TRANSITIVE ) // (v1,vt) to find out/to discover/to detect
 KanjiVerb( 捜す, JAP_TRANSITIVE ) // (v5s,vt) (1) to search (for something lost)/to seek (a suspect in a crime)/(2) to search (for something desired, needed)/to look for/(P)
 KanjiVerb( 掃き出す, JAP_TRANSITIVE ) // (v5s,vt) to release/to sweep out/to clean out
 KanjiVerb( 掃く, JAP_TRANSITIVE ) // (v5k,vt) to sweep/to brush/to gather up/(P)
 KanjiVerb( 挿げ替える, JAP_TRANSITIVE ) // (v1,vt) to exchange/to replace
 KanjiVerb( 挿し替える, JAP_TRANSITIVE ) // (v1,vt) to change/to replace
 KanjiVerb( 挿す, JAP_TRANSITIVE ) // (v5s,vt) to insert/to put in/to graft/to wear in belt
 KanjiVerb( 掻い込む, JAP_TRANSITIVE ) // (v5m,vt) to scoop into
 KanjiVerb( 掻い出す, JAP_TRANSITIVE ) // (v5s,vt) to bail out
 KanjiVerb( 掻い摘まむ, JAP_TRANSITIVE ) // (v5m,vt) (uk) to sum up/to summarize/to summarise
 KanjiVerb( 掻い摘む, JAP_TRANSITIVE ) // (v5m,vt) (uk) to sum up/to summarize/to summarise
 KanjiVerb( 掻き回す, JAP_TRANSITIVE ) // (v5s,vt) to stir up/to churn/to ransack/to disturb/(P)
 KanjiVerb( 掻き寄せる, JAP_TRANSITIVE ) // (v1,vt) to sweep/to rake up
 KanjiVerb( 掻き均す, JAP_TRANSITIVE ) // (v5s,vt) to smooth out
 KanjiVerb( 掻き合せる, JAP_TRANSITIVE ) // (v1,vt) to adjust/to arrange
 KanjiVerb( 掻き合わせる, JAP_TRANSITIVE ) // (v1,vt) to adjust/to arrange
 KanjiVerb( 掻き込む, JAP_TRANSITIVE ) // (v5m,vt) to carry under the arm/to rake in
 KanjiVerb( 掻き集める, JAP_TRANSITIVE ) // (v1,vt) to gather up/to scrape up together
 KanjiVerb( 掻き出す, JAP_TRANSITIVE ) // (v5s,vt) to scrape out
 KanjiVerb( 掻き消す, JAP_TRANSITIVE ) // (v5s,vt) to erase
 KanjiVerb( 掻き上げる, JAP_TRANSITIVE ) // (v1,vt) to comb upwards
 KanjiVerb( 掻き退ける, JAP_TRANSITIVE ) // (v1,vt) to push through
 KanjiVerb( 掻き分ける, JAP_TRANSITIVE ) // (v1,vt) to push one's way through
 KanjiVerb( 掻き抱く, JAP_TRANSITIVE ) // (v5k,vt) to hug/to clasp to one's breast
 KanjiVerb( 掻き鳴らす, JAP_TRANSITIVE ) // (v5s,vt) to thrum/to strum
 KanjiVerb( 掻き乱す, JAP_TRANSITIVE ) // (v5s,vt) to stir up/to disturb
 KanjiVerb( 掻き立てる, JAP_TRANSITIVE ) // (v1,vt) to stir up/to arouse
 KanjiVerb( 掻く, JAP_TRANSITIVE ) // (v5k,vt) (1) (uk) to scratch/(2) to perspire/(3) to shovel/to paddle/(P)
 KanjiVerb( 掻っ込む, JAP_TRANSITIVE ) // (v5m,vt) to bolt one's food/to gulp down
 KanjiVerb( 掻っ払う, JAP_TRANSITIVE ) // (v5u,vt) to swipe (as in steal)/to walk off with
 KanjiVerb( 掻っ攫う, JAP_TRANSITIVE ) // (v5u,vt) to nab/to snatch
 KanjiVerb( 掻攫う, JAP_TRANSITIVE ) // (v5u,vt) to nab/to snatch
 KanjiVerb( 早める, JAP_TRANSITIVE ) // (v1,vt) to hasten/to quicken/to expedite/to precipitate/to accelerate/(P)
 KanjiVerb( 漕ぎ出す, JAP_TRANSITIVE ) // (v5s,vt) to begin rowing
 KanjiVerb( 漕ぎ着ける, JAP_TRANSITIVE ) // (v1,vt) to row up to/to attain to
 KanjiVerb( 漕ぐ, JAP_TRANSITIVE ) // (v5g,vt) to row/to scull/to paddle/to pedal/(P)
 KanjiVerb( 装う, JAP_TRANSITIVE ) // (v5u,vt) (1) to dress/(2) to pretend/to feign/(P)
 KanjiVerb( 送りつける, JAP_TRANSITIVE ) // (v1,vt) to send
 KanjiVerb( 送り込む, JAP_TRANSITIVE ) // (v5m,vt) to send in/(P)
 KanjiVerb( 送り出す, JAP_TRANSITIVE ) // (v5s,vt) to send out/to forward/to show (a person) out
 KanjiVerb( 送り届ける, JAP_TRANSITIVE ) // (v1,vt) to send to/to deliver/to escort (a person) home
 KanjiVerb( 送り付ける, JAP_TRANSITIVE ) // (v1,vt) to send
 KanjiVerb( 騒がす, JAP_TRANSITIVE ) // (v5s,vt) to annoy/to cause trouble
 KanjiVerb( 増やす, JAP_TRANSITIVE ) // (v5s,vt) to increase/to add to/to augment/(P)
 KanjiVerb( 憎む, JAP_TRANSITIVE ) // (v5m,vt) to hate/to detest/(P)
 KanjiVerb( 造り出す, JAP_TRANSITIVE ) // (v5s,vt) (1) to manufacture/to produce/to raise (crops)/(2) to invent/to dream up
 KanjiVerb( 造り上げる, JAP_TRANSITIVE ) // (v1,vt) to make up/to fabricate/to build up/to complete/to construct
 KanjiVerb( 促す, JAP_TRANSITIVE ) // (v5s,vt) to urge/to press/to suggest/to demand/to stimulate/to quicken/to incite/to invite (attention to)/(P)
 KanjiVerb( 側める, JAP_TRANSITIVE ) // (v1,vt) to shove to one side/to look at out of the corner of one's eyes
 KanjiVerb( 捉える, JAP_TRANSITIVE ) // (v1,vt) to perceive/to catch sight of/to grasp
 KanjiVerb( 捉まえる, JAP_TRANSITIVE ) // (v1,vt) to catch/to arrest/to seize
 KanjiVerb( 束ねる, JAP_TRANSITIVE ) // (v1,vt) to tie up in a bundle/to govern/to manage/to control/to fold (one's arms)/to administer
 KanjiVerb( 足す, JAP_TRANSITIVE ) // (v5s,vt) (1) to add (numbers)/(2) to do (e.g., one's business)/(P)
 KanjiVerb( 速める, JAP_TRANSITIVE ) // (v1,vt) to hasten/to quicken/to expedite/to precipitate/to accelerate/(P)
 KanjiVerb( 続ける, JAP_TRANSITIVE ) // (v1,vt) to continue/to keep up/to keep on/(P)
 KanjiVerb( 揃える, JAP_TRANSITIVE ) // (v1,vt) to put things in order/to arrange/to make uniform/to get something ready/(P)
 KanjiVerb( 存じ上げる, JAP_TRANSITIVE ) // (v1,vt) (hum) to know
 KanjiVerb( 尊ぶ, JAP_TRANSITIVE ) // (v5b,vt) to value/to prize/to esteem/(P)
 KanjiVerb( 損ねる, JAP_TRANSITIVE ) // (v1,vt) to harm/to hurt/to injure/(P)
 KanjiVerb( 打ちのめす, JAP_TRANSITIVE ) // (v5s,vt) to knock down/to beat (someone) up
 KanjiVerb( 打ちまける, JAP_TRANSITIVE ) // (v1,vt) (1) to throw out (everything)/(2) to tell frankly/to confess
 KanjiVerb( 打ち下ろす, JAP_TRANSITIVE ) // (v5s,vt) to bring down
 KanjiVerb( 打ち果す, JAP_TRANSITIVE ) // (v5s,vt) to slay/to kill
 KanjiVerb( 打ち果たす, JAP_TRANSITIVE ) // (v5s,vt) to slay/to kill
 KanjiVerb( 打ち壊す, JAP_TRANSITIVE ) // (v5s,vt) to destroy/to spoil/to crush/to wreck
 KanjiVerb( 打ち開ける, JAP_TRANSITIVE ) // (v1,vt) to forcefully open up a hole (in a wall, etc)/to speak frankly, holding nothing back/to throw out everything inside
 KanjiVerb( 打ち貫く, JAP_TRANSITIVE ) // (v5k,vt) (1) to punch/to hit and hit/to stamp out/(2) to pierce/to bore into/to knock down walls
 KanjiVerb( 打ち合う, JAP_TRANSITIVE ) // (v5u,vt) (1) to fight/to exchange blows/to rally/(2) to arrange a meeting
 KanjiVerb( 打ち合せる, JAP_TRANSITIVE ) // (v1,vt) (1) to knock together/(2) to arrange (e.g., a meeting)
 KanjiVerb( 打ち合わせる, JAP_TRANSITIVE ) // (v1,vt) (1) to knock together/(2) to arrange (e.g., a meeting)/(P)
 KanjiVerb( 打ち砕く, JAP_TRANSITIVE ) // (v5k,vt) to smash/to crush
 KanjiVerb( 打ち殺す, JAP_TRANSITIVE ) // (v5s,vt) to shoot to death
 KanjiVerb( 打ち止める, JAP_TRANSITIVE ) // (v1,vt) to kill/to slay/to shoot to death/to bring down (bird)
 KanjiVerb( 打ち捨てる, JAP_TRANSITIVE ) // (v1,vt) to throw away/to abandon
 KanjiVerb( 打ち出す, JAP_TRANSITIVE ) // (v5s,vt) to begin/to beat/to end/to close/to set out (forth)/to work out/to hammer out/(P)
 KanjiVerb( 打ち消す, JAP_TRANSITIVE ) // (v5s,vt) to deny/to negate/to contradict/(P)
 KanjiVerb( 打ち上げる, JAP_TRANSITIVE ) // (v1,vt) to launch/to shoot up/(of waves) dash/to wash up (ashore)/to finish/to close/(P)
 KanjiVerb( 打ち据える, JAP_TRANSITIVE ) // (v1,vt) to place firmly/to hit very hard
 KanjiVerb( 打ち倒す, JAP_TRANSITIVE ) // (v5s,vt) to knock down/to defeat
 KanjiVerb( 打ち当てる, JAP_TRANSITIVE ) // (v1,vt) to hit against
 KanjiVerb( 打ち抜く, JAP_TRANSITIVE ) // (v5k,vt) (1) to punch/to hit and hit/to stamp out/(2) to pierce/to bore into/to knock down walls
 KanjiVerb( 打ち付ける, JAP_TRANSITIVE ) // (v1,vt) to knock/to run into/to nail on/to strike hard/to hit and attack/to try (an idea) on someone
 KanjiVerb( 打ち払う, JAP_TRANSITIVE ) // (v5u,vt) to brush away/to repel
 KanjiVerb( 打ち明ける, JAP_TRANSITIVE ) // (v1,vt) to forcefully open up a hole (in a wall, etc)/to speak frankly, holding nothing back/to throw out everything inside
 KanjiVerb( 打ち鳴らす, JAP_TRANSITIVE ) // (v5s,vt) to ring/to clang
 KanjiVerb( 打ち落す, JAP_TRANSITIVE ) // (v5s,vt) to knock down/to shoot down/to lop off
 KanjiVerb( 打ち落とす, JAP_TRANSITIVE ) // (v5s,vt) to knock down/to shoot down/to lop off
 KanjiVerb( 打ち立てる, JAP_TRANSITIVE ) // (v1,vt) to establish/to formulate
 KanjiVerb( 打ち留める, JAP_TRANSITIVE ) // (v1,vt) to kill/to slay/to shoot to death/to bring down (bird)
 KanjiVerb( 打ち拉ぐ, JAP_TRANSITIVE ) // (v5g,vt) to crush (with the weight of misfortune)
 KanjiVerb( 打っかける, JAP_TRANSITIVE ) // (v1,vt) to dash (slosh) water (or other liquid) on a person or in a person's face
 KanjiVerb( 打っ掛ける, JAP_TRANSITIVE ) // (v1,vt) to dash (slosh) water (or other liquid) on a person or in a person's face
 KanjiVerb( 打っ欠く, JAP_TRANSITIVE ) // (v5k,vt) to break into pieces/to chip off
 KanjiVerb( 打っ殺す, JAP_TRANSITIVE ) // (v5s,vt) to beat to death
 KanjiVerb( 打っ飛ばす, JAP_TRANSITIVE ) // (v5s,vt) to drive at full speed/to beat/to strike/to knock/to let go off/to not partake
 KanjiVerb( 打合せる, JAP_TRANSITIVE ) // (v1,vt) (1) to knock together/(2) to arrange (e.g., a meeting)
 KanjiVerb( 打殺す, JAP_TRANSITIVE ) // (v5s,vt) to shoot to death
 KanjiVerb( 打止める, JAP_TRANSITIVE ) // (v1,vt) to kill/to slay/to shoot to death/to bring down (bird)
 KanjiVerb( 打消す, JAP_TRANSITIVE ) // (v5s,vt) to deny/to negate/to contradict/(P)
 KanjiVerb( 打上げる, JAP_TRANSITIVE ) // (v1,vt) to launch/to shoot up/(of waves) dash/to wash up (ashore)/to finish/to close
 KanjiVerb( 打付ける, JAP_TRANSITIVE ) // (v1,vt) to knock/to run into/to nail on/to strike hard/to hit and attack/to try (an idea) on someone/(P)
 KanjiVerb( 打払う, JAP_TRANSITIVE ) // (v5u,vt) to brush away/to repel
 KanjiVerb( 打落す, JAP_TRANSITIVE ) // (v5s,vt) to knock down/to shoot down/to lop off
 KanjiVerb( 打留める, JAP_TRANSITIVE ) // (v1,vt) to kill/to slay/to shoot to death/to bring down (bird)
 KanjiVerb( 耐える, JAP_TRANSITIVE ) // (v1,vi,vt) (1) to bear/to stand/to endure/to put up with/(v1,vi) (2) to support/to withstand/to resist/to brave/(v1,vi) (3) to be fit for/to be equal to
 KanjiVerb( 耐え忍ぶ, JAP_TRANSITIVE ) // (v5b,vt) to put up with/to endure/to bear patiently
 KanjiVerb( 帯く, JAP_TRANSITIVE ) // (v5k,vt) to wear/to put on (lower body, e.g., a sword)
 KanjiVerb( 帯びる, JAP_TRANSITIVE ) // (v1,vt) (1) to wear (sword, decoration, etc.)/to carry/(2) to be entrusted (e.g., with a mission)/to take on/(3) to have a trace of/to be tinged with/(P)
 KanjiVerb( 待ちわびる, JAP_TRANSITIVE ) // (v1,vt) to be tired of waiting/to wait impatiently
 KanjiVerb( 待ち兼ねる, JAP_TRANSITIVE ) // (v1,vt) to wait impatiently for/(P)
 KanjiVerb( 待ち構える, JAP_TRANSITIVE ) // (v1,vt) to lie in wait/to be on the watch for/(P)
 KanjiVerb( 待ち受ける, JAP_TRANSITIVE ) // (v1,vt) to await/to expect/(P)
 KanjiVerb( 待ち焦がれる, JAP_TRANSITIVE ) // (v1,vt) to long for
 KanjiVerb( 待ち設ける, JAP_TRANSITIVE ) // (v1,vt) to expect/to look for/to look forward to/to anticipate/to wait for
 KanjiVerb( 待ち望む, JAP_TRANSITIVE ) // (v5m,vt) to look anxiously for/to wait eagerly for/(P)
 KanjiVerb( 待ち明かす, JAP_TRANSITIVE ) // (v5s,vt) to wait all night
 KanjiVerb( 待ち詫びる, JAP_TRANSITIVE ) // (v1,vt) to be tired of waiting/to wait impatiently
 KanjiVerb( 待ち侘びる, JAP_TRANSITIVE ) // (v1,vt) to be tired of waiting/to wait impatiently
 KanjiVerb( 待つ, JAP_TRANSITIVE ) // (v5t,vt) to wait/(P)
 KanjiVerb( 待設ける, JAP_TRANSITIVE ) // (v1,vt) to expect/to look for/to look forward to/to anticipate/to wait for
 KanjiVerb( 戴く, JAP_TRANSITIVE ) // (v5k,vt) (hum) to receive/to take food or drink/to be crowned with/to wear/to live under (a ruler)/to install (a president)/to accept/to buy/to take/(P)
 KanjiVerb( 替える, JAP_TRANSITIVE ) // (v1,vt) to exchange/to interchange/to substitute/to replace/(P)
 KanjiVerb( 貸しつける, JAP_TRANSITIVE ) // (v1,vt) to lend/to loan
 KanjiVerb( 貸し出す, JAP_TRANSITIVE ) // (v5s,vt) to lend/(P)
 KanjiVerb( 貸し付ける, JAP_TRANSITIVE ) // (v1,vt) to lend/to loan
 KanjiVerb( 貸す, JAP_TRANSITIVE ) // (v5s,vt) to lend/(P)
 KanjiVerb( 退かす, JAP_TRANSITIVE ) // (v5s,vt) to remove
 KanjiVerb( 退ける, JAP_TRANSITIVE ) // (v1,vt) to remove/to take away/to dislodge/to put something out of the way/(P)
 KanjiVerb( 代える, JAP_TRANSITIVE ) // (v1,vt) to exchange/to interchange/to substitute/to replace/(P)
 KanjiVerb( 啄む, JAP_TRANSITIVE ) // (v5m,vt) to pick at/to peck at
 KanjiVerb( 濯ぐ, JAP_TRANSITIVE ) // (v5g,vt) to rinse/to wash out
 KanjiVerb( 託ける, JAP_TRANSITIVE ) // (v1,vt) to make something the pretext (for)/to use something as an excuse
 KanjiVerb( 託つ, JAP_TRANSITIVE ) // (v5t,vt) to complain about/to grumble/to make an excuse for
 KanjiVerb( 濁す, JAP_TRANSITIVE ) // (v5s,vt) to make muddy/to prevaricate/(P)
 KanjiVerb( 叩きつける, JAP_TRANSITIVE ) // (v1,vt) to strike/to throw/to slap something onto
 KanjiVerb( 叩きのめす, JAP_TRANSITIVE ) // (v5s,vt) to knock down
 KanjiVerb( 叩き起こす, JAP_TRANSITIVE ) // (v5s,vt) to wake up/to rouse out of bed
 KanjiVerb( 叩き起す, JAP_TRANSITIVE ) // (v5s,vt) to wake up/to rouse out of bed
 KanjiVerb( 叩き込む, JAP_TRANSITIVE ) // (v5m,vt) to drive into/to throw into/to hit into
 KanjiVerb( 叩き殺す, JAP_TRANSITIVE ) // (v5s,vt) to beat to death
 KanjiVerb( 叩き出す, JAP_TRANSITIVE ) // (v5s,vt) to begin to strike/to kick out
 KanjiVerb( 叩き上げる, JAP_TRANSITIVE ) // (v1,vt) to work one's way up
 KanjiVerb( 叩き直す, JAP_TRANSITIVE ) // (v5s,vt) to beat into shape
 KanjiVerb( 叩き付ける, JAP_TRANSITIVE ) // (v1,vt) to strike/to throw/to slap something onto
 KanjiVerb( 叩き伏せる, JAP_TRANSITIVE ) // (v1,vt) to knock down/to utterly defeat
 KanjiVerb( 叩く, JAP_TRANSITIVE ) // (v5k,vt) (1) to strike/to clap/to dust/to beat/(v5k,vt) (2) to use up money
 KanjiVerb( 奪う, JAP_TRANSITIVE ) // (v5u,vt) to snatch away/to dispossess/(P)
 KanjiVerb( 脱ぎ捨てる, JAP_TRANSITIVE ) // (v1,vt) to fling/to throw off (clothes)/to kick off (boots)
 KanjiVerb( 脱ぐ, JAP_TRANSITIVE ) // (v5g,vt) to take off (clothes, shoes, etc.)/to undress/(P)
 KanjiVerb( 担う, JAP_TRANSITIVE ) // (v5u,vt) to carry on shoulder/to bear (burden)/to shoulder (gun)/(P)
 KanjiVerb( 担ぎ出す, JAP_TRANSITIVE ) // (v5s,vt) to carry something out of a place
 KanjiVerb( 担ぎ上げる, JAP_TRANSITIVE ) // (v1,vt) to put up/to flatter
 KanjiVerb( 担ぐ, JAP_TRANSITIVE ) // (v5g,vt) to shoulder/to carry on shoulder/(P)
 KanjiVerb( 探し出す, JAP_TRANSITIVE ) // (v5s,vt) to find out
 KanjiVerb( 探す, JAP_TRANSITIVE ) // (v5s,vt) (1) to search (for something lost)/to seek (a suspect in a crime)/(2) to search (for something desired, needed)/to look for/(P)
 KanjiVerb( 探り出す, JAP_TRANSITIVE ) // (v5s,vt) to spy out/to smell out
 KanjiVerb( 探り当てる, JAP_TRANSITIVE ) // (v1,vt) to find out
 KanjiVerb( 湛える, JAP_TRANSITIVE ) // (v1,vt) to fill (to the brim)
 KanjiVerb( 鍛える, JAP_TRANSITIVE ) // (v1,vt) to forge/to drill/to temper/to train/to discipline/(P)
 KanjiVerb( 鍛え上げる, JAP_TRANSITIVE ) // (v1,vt) to temper thoroughly/to train well
 KanjiVerb( 弾き出す, JAP_TRANSITIVE ) // (v5s,vt) to shoot (marbles)/to calculate/to spring out/to force out
 KanjiVerb( 断つ, JAP_TRANSITIVE ) // (v5t,vt) to sever/to cut off/to suppress/to abstain (from)/(P)
 KanjiVerb( 暖める, JAP_TRANSITIVE ) // (v1,vt) to warm/to heat/(P)
 KanjiVerb( 知らせる, JAP_TRANSITIVE ) // (v1,vt) to notify/to advise/(P)
 KanjiVerb( 知り抜く, JAP_TRANSITIVE ) // (v5k,vt) to know thoroughly
 KanjiVerb( 置き換える, JAP_TRANSITIVE ) // (v1,vt) to replace/to move/to change the position of
 KanjiVerb( 置き忘れる, JAP_TRANSITIVE ) // (v1,vt) to leave behind/to misplace/to forget
 KanjiVerb( 致す, JAP_TRANSITIVE ) // (v5s,vt) (hum) to do/(P)
 KanjiVerb( 遅らす, JAP_TRANSITIVE ) // (v5s,vt) to retard/to delay/(P)
 KanjiVerb( 遅らせる, JAP_TRANSITIVE ) // (v1,vt) to put something off
 KanjiVerb( 築き上げる, JAP_TRANSITIVE ) // (v1,vt) to build up/to establish (one's reputation)/(P)
 KanjiVerb( 築く, JAP_TRANSITIVE ) // (v5k,vt) to build/to pile up/to amass/(P)
 KanjiVerb( 蓄える, JAP_TRANSITIVE ) // (v1,vt) to store/to lay in stock/(P)
 KanjiVerb( 着く, JAP_TRANSITIVE ) // (v5k,vt) to wear/to put on (lower body, e.g., a sword)
 KanjiVerb( 着ける, JAP_TRANSITIVE ) // (v1,vt) (1) to attach/to join/to add/to append/to affix/to stick/to glue/to fasten/to sew on/to apply (ointment)/(2) to furnish (a house with)/(3) to wear/to put on/(4) to keep a diary/to make an entry/(5) to appraise/to set (a price)/(6) to bring alongside/(7) to place (under guard or doctor)/(8) to follow/to shadow/(9) to load/to give (courage to)/(10) to keep (an eye on)/(11) to establish (relations or understanding)/(P)
 KanjiVerb( 着こなす, JAP_TRANSITIVE ) // (v5s,vt) to wear (clothes) stylishly/to dress oneself stylishly
 KanjiVerb( 着せる, JAP_TRANSITIVE ) // (v1,vt) to put on clothes/(P)
 KanjiVerb( 着古す, JAP_TRANSITIVE ) // (v5s,vt) to wear out (clothing)
 KanjiVerb( 注ぎ込む, JAP_TRANSITIVE ) // (v5m,vt) to pour into/to put into/to invest in/to inject/to impregnate/to infuse/to instill/to implant/to imbue
 KanjiVerb( 注す, JAP_TRANSITIVE ) // (v5s,vt) to pour (drink)/to serve (drinks)/(P)
 KanjiVerb( 鋳る, JAP_TRANSITIVE ) // (v1,vt) to cast/to mint/to coin/(P)
 KanjiVerb( 鋳込む, JAP_TRANSITIVE ) // (v5m,vt) to cast in a mold (mould)
 KanjiVerb( 鋳潰す, JAP_TRANSITIVE ) // (v5s,vt) to melt down
 KanjiVerb( 著す, JAP_TRANSITIVE ) // (v5s,vt) to write/to publish/(P)
 KanjiVerb( 著わす, JAP_TRANSITIVE ) // (v5s,vt) to write/to publish/(P)
 KanjiVerb( 貯える, JAP_TRANSITIVE ) // (v1,vt) to store/to lay in stock
 KanjiVerb( 貯める, JAP_TRANSITIVE ) // (v1,vt) to save (i.e. in a bank)
 KanjiVerb( 弔う, JAP_TRANSITIVE ) // (v5u,vt) to mourn for/to hold a memorial service for/to condole/(P)
 KanjiVerb( 張りつける, JAP_TRANSITIVE ) // (v1,vt) to attach to a flat surface with glue/to paste/to stick/to affix
 KanjiVerb( 張り巡らす, JAP_TRANSITIVE ) // (v5s,vt) to stretch around
 KanjiVerb( 張り上げる, JAP_TRANSITIVE ) // (v1,vt) to raise
 KanjiVerb( 張り替える, JAP_TRANSITIVE ) // (v1,vt) to re-cover/to reupholster/to repaper
 KanjiVerb( 張り倒す, JAP_TRANSITIVE ) // (v5s,vt) to knock down
 KanjiVerb( 張り飛ばす, JAP_TRANSITIVE ) // (v5s,vt) to knock down/to send flying
 KanjiVerb( 張り付ける, JAP_TRANSITIVE ) // (v1,vt) to attach to a flat surface with glue/to paste/to stick/to affix
 KanjiVerb( 彫りつける, JAP_TRANSITIVE ) // (v1,vt) to carve (design)
 KanjiVerb( 彫り付ける, JAP_TRANSITIVE ) // (v1,vt) to carve (design)
 KanjiVerb( 懲らしめる, JAP_TRANSITIVE ) // (v1,vt) to chastise/to punish/to discipline
 KanjiVerb( 懲らす, JAP_TRANSITIVE ) // (v5s,vt) to chastise/to punish/to discipline
 KanjiVerb( 眺める, JAP_TRANSITIVE ) // (v1,vt) to view/to gaze at/(P)
 KanjiVerb( 聴く, JAP_TRANSITIVE ) // (v5k,vt) (1) to hear/to listen/(2) to ask
 KanjiVerb( 聴す, JAP_TRANSITIVE ) // (v5s,vt) (1) to permit/to allow/to approve/(2) to exempt (from fine)/to excuse (from)/to pardon/to release/to let off/(3) to confide in/(4) to give up/to yield
 KanjiVerb( 調える, JAP_TRANSITIVE ) // (v1,vt) (1) to put in order/to arrange/to adjust/(2) to get ready/to prepare/(3) to raise money
 KanjiVerb( 調べる, JAP_TRANSITIVE ) // (v1,vt) to investigate/to check up/(P)
 KanjiVerb( 跳ね除ける, JAP_TRANSITIVE ) // (v1,vt) to push aside/to brush or thrust aside/to remove/to get rid of
 KanjiVerb( 跳ね飛ばす, JAP_TRANSITIVE ) // (v5s,vt) (1) to send (something) flying/to splatter/(2) to drive (something) off
 KanjiVerb( 跳び越す, JAP_TRANSITIVE ) // (v5s,vt) to leap over
 KanjiVerb( 跳越す, JAP_TRANSITIVE ) // (v5s,vt) to leap over
 KanjiVerb( 頂く, JAP_TRANSITIVE ) // (v5k,vt) (hum) to receive/to take food or drink/to be crowned with/to wear/to live under (a ruler)/to install (a president)/to accept/to buy/to take/(P)
 KanjiVerb( 直す, JAP_TRANSITIVE ) // (v5s,vt) (1) to cure/to heal/(2) to fix/to correct/to repair/(P)
 KanjiVerb( 沈める, JAP_TRANSITIVE ) // (v1,vt) to sink/to submerge/(P)
 KanjiVerb( 鎮める, JAP_TRANSITIVE ) // (v1,vt) to appease/to suppress/to calm/(P)
 KanjiVerb( 追いかける, JAP_TRANSITIVE ) // (v1,vt) to chase or run after someone/to run down/to pursue
 KanjiVerb( 追い越す, JAP_TRANSITIVE ) // (v5s,vt) to pass (e.g., car)/to outdistance/to outstrip/(P)
 KanjiVerb( 追い回す, JAP_TRANSITIVE ) // (v5s,vt) to chase about/to hang on/to drive hard
 KanjiVerb( 追い掛ける, JAP_TRANSITIVE ) // (v1,vt) to chase or run after someone/to run down/to pursue
 KanjiVerb( 追い詰める, JAP_TRANSITIVE ) // (v1,vt) to corner/to drive to the wall/to run down/to track down
 KanjiVerb( 追い込む, JAP_TRANSITIVE ) // (v5m,vt) to herd/to corner/to drive/(P)
 KanjiVerb( 追い散らす, JAP_TRANSITIVE ) // (v5s,vt) to drive away/to scatter/to rout
 KanjiVerb( 追い出す, JAP_TRANSITIVE ) // (v5s,vt) to expel/to drive out/(P)
 KanjiVerb( 追い上げる, JAP_TRANSITIVE ) // (v1,vt) to gain on/to put pressure on/(P)
 KanjiVerb( 追い抜く, JAP_TRANSITIVE ) // (v5k,vt) to pass (a car)/to outdistance/to outsail/to outstrip/(P)
 KanjiVerb( 追い払う, JAP_TRANSITIVE ) // (v5u,vt) to drive away
 KanjiVerb( 追い返す, JAP_TRANSITIVE ) // (v5s,vt) to turn away/to send away
 KanjiVerb( 追い立てる, JAP_TRANSITIVE ) // (v1,vt) to drive away
 KanjiVerb( 追う, JAP_TRANSITIVE ) // (v5u,vt) to chase/to run after/(P)
 KanjiVerb( 追っ掛ける, JAP_TRANSITIVE ) // (v1,vt) to chase or run after someone/to run down/to pursue/(P)
 KanjiVerb( 追っ払う, JAP_TRANSITIVE ) // (v5u,vt) to drive away or out
 KanjiVerb( 痛めつける, JAP_TRANSITIVE ) // (v1,vt) to rebuke/to taunt/to give a good shaking/to knock about
 KanjiVerb( 痛める, JAP_TRANSITIVE ) // (v1,vt) to hurt/to injure/to cause pain/to worry/to bother/to afflict/to be grieved over
 KanjiVerb( 痛め付ける, JAP_TRANSITIVE ) // (v1,vt) to rebuke/to taunt/to give a good shaking/to knock about
 KanjiVerb( 通す, JAP_TRANSITIVE ) // (v5s,vt) to let pass/to overlook/to continue/to keep/to make way for/to persist in/(P)
 KanjiVerb( 掴まえる, JAP_TRANSITIVE ) // (v1,vt) to catch/to arrest/to seize
 KanjiVerb( 掴み出す, JAP_TRANSITIVE ) // (v5s,vt) to take out/to take a handful of/to grab and throw
 KanjiVerb( 掴む, JAP_TRANSITIVE ) // (v5m,vt) to seize/to catch/to grasp/to grip/to grab/to hold/to catch hold of/to lay one's hands on/(P)
 KanjiVerb( 漬ける, JAP_TRANSITIVE ) // (v1,vt) to soak/to moisten/to pickle/(P)
 KanjiVerb( 漬け込む, JAP_TRANSITIVE ) // (v5m,vt) to pickle a large amount
 KanjiVerb( 綴じる, JAP_TRANSITIVE ) // (v1,vt) to bind/to file/(P)
 KanjiVerb( 潰す, JAP_TRANSITIVE ) // (v5s,vt) to smash/to waste/(P)
 KanjiVerb( 吊し上げる, JAP_TRANSITIVE ) // (v1,vt) (1) to hang up/to hoist/(2) to denounce/to subject someone to a kangaroo court
 KanjiVerb( 吊す, JAP_TRANSITIVE ) // (v5s,vt) to hang
 KanjiVerb( 吊り下げる, JAP_TRANSITIVE ) // (v1,vt) to suspend from/to be suspended (from)
 KanjiVerb( 吊り出す, JAP_TRANSITIVE ) // (v5s,vt) to hold (the opponent) in the arms and carry him out of the ring
 KanjiVerb( 吊り上げる, JAP_TRANSITIVE ) // (v1,vt) to hang up/to suspend/to raise/to lift
 KanjiVerb( 吊るし上げる, JAP_TRANSITIVE ) // (v1,vt) (1) to hang up/to hoist/(2) to denounce/to subject someone to a kangaroo court
 KanjiVerb( 吊るす, JAP_TRANSITIVE ) // (v5s,vt) to hang/(P)
 KanjiVerb( 釣り下げる, JAP_TRANSITIVE ) // (v1,vt) to suspend from/to be suspended (from)
 KanjiVerb( 釣り込む, JAP_TRANSITIVE ) // (v5m,vt) to take in/to attract
 KanjiVerb( 釣り出す, JAP_TRANSITIVE ) // (v5s,vt) to pull out a fish/to lure
 KanjiVerb( 釣り上げる, JAP_TRANSITIVE ) // (v1,vt) to pull in (fish)/to boost (prices)/to raise (eyes)
 KanjiVerb( 低める, JAP_TRANSITIVE ) // (v1,vt) to lower/to be lowered/(P)
 KanjiVerb( 停める, JAP_TRANSITIVE ) // (v1,vt) to stop/to halt
 KanjiVerb( 定める, JAP_TRANSITIVE ) // (v1,vt) to decide/to establish/to determine/(P)
 KanjiVerb( 提げる, JAP_TRANSITIVE ) // (v1,vt) to take along/to hold in the hand/(P)
 KanjiVerb( 締めつける, JAP_TRANSITIVE ) // (v1,vt) to tighten/to press hard
 KanjiVerb( 締める, JAP_TRANSITIVE ) // (v1,vt) to tie/to fasten/(P)
 KanjiVerb( 締め固める, JAP_TRANSITIVE ) // (vt) to compact
 KanjiVerb( 締め込む, JAP_TRANSITIVE ) // (v5m,vt) to shut in/to lock in
 KanjiVerb( 締め殺す, JAP_TRANSITIVE ) // (v5s,vt) to strangle to death
 KanjiVerb( 締め出す, JAP_TRANSITIVE ) // (v5s,vt) to shut out/to bar/to lock out/(P)
 KanjiVerb( 締め上げる, JAP_TRANSITIVE ) // (v1,vt) to screw up/to put the screws on (a person)
 KanjiVerb( 締め付ける, JAP_TRANSITIVE ) // (v1,vt) to tighten/to press hard
 KanjiVerb( 諦める, JAP_TRANSITIVE ) // (v1,vt) to give up/to abandon/(P)
 KanjiVerb( 摘まみ出す, JAP_TRANSITIVE ) // (v5s,vt) to pick out/to throw out
 KanjiVerb( 摘まむ, JAP_TRANSITIVE ) // (v5m,vt) to pinch/to hold/to pick up
 KanjiVerb( 摘む, JAP_TRANSITIVE ) // (v5m,vt) to pluck/to pick/to trim/(P)
 KanjiVerb( 溺らす, JAP_TRANSITIVE ) // (v5s,vt) (1) to drown/(2) to cause to be indulged or addicted
 KanjiVerb( 徹す, JAP_TRANSITIVE ) // (v5s,vt) to let pass/to overlook/to continue/to keep/to make way for/to persist in/(P)
 KanjiVerb( 填める, JAP_TRANSITIVE ) // (v1,vt) to bury (e.g., one's face in hands)
 KanjiVerb( 添える, JAP_TRANSITIVE ) // (v1,vt) to add to/to attach/to append/to accompany/to garnish/to imitate/to annex/(P)
 KanjiVerb( 纏める, JAP_TRANSITIVE ) // (v1,vt) to put in order/to collect/to bring to a conclusion/(P)
 KanjiVerb( 貼りつける, JAP_TRANSITIVE ) // (v1,vt) to attach to a flat surface with glue/to paste/to stick/to affix
 KanjiVerb( 貼り付ける, JAP_TRANSITIVE ) // (v1,vt) to attach to a flat surface with glue/to paste/to stick/to affix
 KanjiVerb( 転がす, JAP_TRANSITIVE ) // (v5s,vt) to roll/(P)
 KanjiVerb( 点ける, JAP_TRANSITIVE ) // (v1,vt) (uk) to turn on/to switch on/to light up/(P)
 KanjiVerb( 点じる, JAP_TRANSITIVE ) // (v1,vt) to drop/to light/to kindle/to make tea
 KanjiVerb( 点す, JAP_TRANSITIVE ) // (v5s,vt) to light/to turn on/(P)
 KanjiVerb( 点ずる, JAP_TRANSITIVE ) // (vz,vt) to drop/to light/to kindle/to make tea
 KanjiVerb( 伝える, JAP_TRANSITIVE ) // (v1,vt) to convey/to report/to transmit/to communicate/to tell/to impart/to propagate/to teach/to bequeath/(P)
 KanjiVerb( 伝え聞く, JAP_TRANSITIVE ) // (v5k,vt) to learn by hearsay
 KanjiVerb( 吐き捨てる, JAP_TRANSITIVE ) // (v1,vt) to spit out
 KanjiVerb( 吐き出す, JAP_TRANSITIVE ) // (v5s,vt) to vomit/to spit out/(P)
 KanjiVerb( 吐く, JAP_TRANSITIVE ) // (v5k,vt) (1) to breathe/(2) to tell (lies)/(3) to vomit/to disgorge/(P)
 KanjiVerb( 塗す, JAP_TRANSITIVE ) // (v5s,vt) to cover (smear, sprinkle) (with)
 KanjiVerb( 塗りつける, JAP_TRANSITIVE ) // (v1,vt) to daub/to smear
 KanjiVerb( 塗り隠す, JAP_TRANSITIVE ) // (v5s,vt) to cover with paint/to hide with paint or make-up
 KanjiVerb( 塗り込める, JAP_TRANSITIVE ) // (v1,vt) to seal up
 KanjiVerb( 塗り替える, JAP_TRANSITIVE ) // (v1,vt) to repaint/(P)
 KanjiVerb( 塗り潰す, JAP_TRANSITIVE ) // (v5s,vt) to paint out
 KanjiVerb( 塗り付ける, JAP_TRANSITIVE ) // (v1,vt) to daub/to smear
 KanjiVerb( 塗り立てる, JAP_TRANSITIVE ) // (v1,vt) to paint beautifully/to paint thickly/to powder heavily
 KanjiVerb( 妬む, JAP_TRANSITIVE ) // (v5m,vt) to be jealous/to be envious/(P)
 KanjiVerb( 渡す, JAP_TRANSITIVE ) // (v5s,vt) to pass over/to hand over/(P)
 KanjiVerb( 賭ける, JAP_TRANSITIVE ) // (v1,vt) to wager/to bet/to risk/to stake/to gamble/(P)
 KanjiVerb( 努める, JAP_TRANSITIVE ) // (v1,vt) (1) to serve/to fill a post/to serve under/to work (for)/(2) to exert oneself/to endeavor/to endeavour/to be diligent/(3) to play (the part of)/(P)
 KanjiVerb( 怒らす, JAP_TRANSITIVE ) // (v5s,vt) to anger someone/to offend someone
 KanjiVerb( 怒鳴りつける, JAP_TRANSITIVE ) // (v1,vt) to shout at
 KanjiVerb( 怒鳴り付ける, JAP_TRANSITIVE ) // (v1,vt) to shout at
 KanjiVerb( 倒す, JAP_TRANSITIVE ) // (v5s,vt) to throw down/to beat/to bring down/to blow down/to fell/to knock down/to trip up/to defeat/to ruin/to overthrow/to kill/to leave unpaid/to cheat/(P)
 KanjiVerb( 凍らす, JAP_TRANSITIVE ) // (v5s,vt) to freeze/to refrigerate
 KanjiVerb( 投げかける, JAP_TRANSITIVE ) // (v1,vt) to throw at/to turn/to raise
 KanjiVerb( 投げつける, JAP_TRANSITIVE ) // (v1,vt) to throw at/to throw something at a person/to throw a person down
 KanjiVerb( 投げる, JAP_TRANSITIVE ) // (v1,vt) (1) to throw/to cast away/(2) to face defeat/to give up/(P)
 KanjiVerb( 投げ下ろす, JAP_TRANSITIVE ) // (v5s,vt) to dump (a load of something)
 KanjiVerb( 投げ掛ける, JAP_TRANSITIVE ) // (v1,vt) to throw at/to turn/to raise
 KanjiVerb( 投げ込む, JAP_TRANSITIVE ) // (v5m,vt) to throw into/(P)
 KanjiVerb( 投げ捨てる, JAP_TRANSITIVE ) // (v1,vt) to throw away
 KanjiVerb( 投げ出す, JAP_TRANSITIVE ) // (v5s,vt) to throw down/to abandon/to sacrifice/to throw out/(P)
 KanjiVerb( 投げ入れる, JAP_TRANSITIVE ) // (v1,vt) to throw into/to dump in together
 KanjiVerb( 投げ飛ばす, JAP_TRANSITIVE ) // (v5s,vt) to fling (away)/to hurl
 KanjiVerb( 投げ付ける, JAP_TRANSITIVE ) // (v1,vt) to throw at/to throw something at a person/to throw a person down
 KanjiVerb( 投下ろす, JAP_TRANSITIVE ) // (v5s,vt) to dump (a load of something)
 KanjiVerb( 投捨てる, JAP_TRANSITIVE ) // (v1,vt) to throw away
 KanjiVerb( 投付ける, JAP_TRANSITIVE ) // (v1,vt) to throw at/to throw something at a person/to throw a person down
 KanjiVerb( 盗む, JAP_TRANSITIVE ) // (v5m,vt) to steal/(P)
 KanjiVerb( 湯引く, JAP_TRANSITIVE ) // (v5k,vt) to parboil/to scald
 KanjiVerb( 湯掻く, JAP_TRANSITIVE ) // (v5k,vt) to parboil/to scald
 KanjiVerb( 灯す, JAP_TRANSITIVE ) // (v5s,vt) to light/to turn on/(P)
 KanjiVerb( 当てつける, JAP_TRANSITIVE ) // (v1,vt) to insinuate
 KanjiVerb( 当てはめる, JAP_TRANSITIVE ) // (v1,vt) to apply/to adapt/(P)
 KanjiVerb( 当てる, JAP_TRANSITIVE ) // (v1,vt) (1) to hit/(2) to expose/(3) to apply (e.g., patch)/(4) to allot/to call on someone (e.g., in class)/(5) to guess (an answer)/(6) to make a hit (e.g., in a lottery)/(P)
 KanjiVerb( 当て込む, JAP_TRANSITIVE ) // (v5m,vt) to count on
 KanjiVerb( 当て付ける, JAP_TRANSITIVE ) // (v1,vt) to insinuate
 KanjiVerb( 当て嵌める, JAP_TRANSITIVE ) // (v1,vt) to apply/to adapt
 KanjiVerb( 統べる, JAP_TRANSITIVE ) // (v1,vt) to control/to supervise
 KanjiVerb( 討ち果す, JAP_TRANSITIVE ) // (v5s,vt) to slay/to kill
 KanjiVerb( 討ち果たす, JAP_TRANSITIVE ) // (v5s,vt) to slay/to kill
 KanjiVerb( 討ち止める, JAP_TRANSITIVE ) // (v1,vt) to kill/to slay/to shoot to death/to bring down (bird)
 KanjiVerb( 討ち滅ぼす, JAP_TRANSITIVE ) // (v5s,vt) to destroy
 KanjiVerb( 討止める, JAP_TRANSITIVE ) // (v1,vt) to kill/to slay/to shoot to death/to bring down (bird)
 KanjiVerb( 踏まえる, JAP_TRANSITIVE ) // (v1,vt) to be based on/to have origin in/(P)
 KanjiVerb( 踏みつける, JAP_TRANSITIVE ) // (v1,vt) to trample down/to ignore/to tread on
 KanjiVerb( 踏みならす, JAP_TRANSITIVE ) // (v5s,vt) to stamp one's feet
 KanjiVerb( 踏み外す, JAP_TRANSITIVE ) // (v5s,vt) to miss one's footing
 KanjiVerb( 踏み均す, JAP_TRANSITIVE ) // (v5s,vt) to trample flat/to beat a path
 KanjiVerb( 踏み固める, JAP_TRANSITIVE ) // (v1,vt) to tread down
 KanjiVerb( 踏み荒す, JAP_TRANSITIVE ) // (v5s,vt) to trample down/to devastate
 KanjiVerb( 踏み荒らす, JAP_TRANSITIVE ) // (v5s,vt) to trample down/to devastate
 KanjiVerb( 踏み潰す, JAP_TRANSITIVE ) // (v5s,vt) to trample/to crush underfoot
 KanjiVerb( 踏み締める, JAP_TRANSITIVE ) // (v1,vt) to step firmly/to harden by treading
 KanjiVerb( 踏み倒す, JAP_TRANSITIVE ) // (v5s,vt) to trample down/to bilk/to shirk payment
 KanjiVerb( 踏み入れる, JAP_TRANSITIVE ) // (v1,vt) to walk in on/to tread upon
 KanjiVerb( 踏み抜く, JAP_TRANSITIVE ) // (v5k,vt) to tread (a nail) into the sole of one's foot/to tread through (the floor)
 KanjiVerb( 踏み付ける, JAP_TRANSITIVE ) // (v1,vt) to trample down/to ignore/to tread on
 KanjiVerb( 踏み分ける, JAP_TRANSITIVE ) // (v1,vt) to push through (i.e. a crowd, vegetation, etc.)
 KanjiVerb( 踏み鳴らす, JAP_TRANSITIVE ) // (v5s,vt) to stamp one's feet
 KanjiVerb( 踏む, JAP_TRANSITIVE ) // (v5m,vt) to step on/to tread on/(P)
 KanjiVerb( 踏荒らす, JAP_TRANSITIVE ) // (v5s,vt) to trample down/to devastate
 KanjiVerb( 逃がす, JAP_TRANSITIVE ) // (v5s,vt) to let loose/to set free/to let escape/(P)
 KanjiVerb( 逃す, JAP_TRANSITIVE ) // (v5s,vt) to let loose/to set free/to let escape/(P)
 KanjiVerb( 透かす, JAP_TRANSITIVE ) // (v5s,vt) to look through/to hold up to the light/to make an opening/to leave space/to space (lines)/to prune (trees)
 KanjiVerb( 透す, JAP_TRANSITIVE ) // (v5s,vt) to let pass/to overlook/to continue/to keep/to make way for/to persist in
 KanjiVerb( 働かす, JAP_TRANSITIVE ) // (v5s,vt) to put someone to work/to make someone work
 KanjiVerb( 働きかける, JAP_TRANSITIVE ) // (v1,vt) to work on someone/to influence/to appeal to/to begin to work
 KanjiVerb( 働き掛ける, JAP_TRANSITIVE ) // (v1,vt) to work on someone/to influence/to appeal to/to begin to work/(P)
 KanjiVerb( 動かす, JAP_TRANSITIVE ) // (v5s,vt) to move/to shift/to set in motion/to operate/to inspire/to rouse/to influence/to mobilize/to mobilise/to deny/to change/(P)
 KanjiVerb( 導く, JAP_TRANSITIVE ) // (v5k,vt) to guide/to lead/to show the way/to conduct/(P)
 KanjiVerb( 撞く, JAP_TRANSITIVE ) // (v5k,vt) to strike (e.g., a bell)
 KanjiVerb( 匿う, JAP_TRANSITIVE ) // (v5u,vt) to shelter/to shield/to hide
 KanjiVerb( 毒突く, JAP_TRANSITIVE ) // (v5k,vt) to curse (at someone)/to call someone names
 KanjiVerb( 読みかける, JAP_TRANSITIVE ) // (v1,vt) to begin to read/to leaf through a book
 KanjiVerb( 読み下す, JAP_TRANSITIVE ) // (v5s,vt) to transliterate classical Chinese into Japanese
 KanjiVerb( 読み掛ける, JAP_TRANSITIVE ) // (v1,vt) to begin to read/to leaf through a book
 KanjiVerb( 読み合せる, JAP_TRANSITIVE ) // (v1,vt) to read out and compare or collate
 KanjiVerb( 読み合わせる, JAP_TRANSITIVE ) // (v1,vt) to read out and compare or collate
 KanjiVerb( 読み込む, JAP_TRANSITIVE ) // (v5m,vt) (1) to express (e.g., emotion in poetry)/(2) to read (extra meaning) into (something)/(3) to fetch (e.g., CPU inst.)/to read (data into a system)
 KanjiVerb( 読み止す, JAP_TRANSITIVE ) // (v5s,vt) to leave half-read or unfinished
 KanjiVerb( 読み上げる, JAP_TRANSITIVE ) // (v1,vt) to read out loud (and clearly)/to call a roll/(P)
 KanjiVerb( 読み替える, JAP_TRANSITIVE ) // (v1,vt) to read a kanji with a different pronunciation
 KanjiVerb( 読み聞かせる, JAP_TRANSITIVE ) // (v1,vt) to read aloud to another
 KanjiVerb( 読み返す, JAP_TRANSITIVE ) // (v5s,vt) to reread/to read again/(P)
 KanjiVerb( 読み流す, JAP_TRANSITIVE ) // (v5s,vt) to read smoothly/to skim
 KanjiVerb( 読む, JAP_TRANSITIVE ) // (v5m,vt) to read/(P)
 KanjiVerb( 読掛ける, JAP_TRANSITIVE ) // (v1,vt) to begin to read/to leaf through a book
 KanjiVerb( 読替える, JAP_TRANSITIVE ) // (v1,vt) to be read as
 KanjiVerb( 突きっ返す, JAP_TRANSITIVE ) // (v5s,vt) to poke in return/to send back/to reject
 KanjiVerb( 突きつける, JAP_TRANSITIVE ) // (v1,vt) to thrust before/to thrust at
 KanjiVerb( 突き詰める, JAP_TRANSITIVE ) // (v1,vt) to investigate thoroughly/to probe into/to think something through/to follow an argument to its logical conclusion
 KanjiVerb( 突き合せる, JAP_TRANSITIVE ) // (v1,vt) to place persons opposite/to come face to face with/to compare
 KanjiVerb( 突き合わせる, JAP_TRANSITIVE ) // (v1,vt) to place persons opposite/to come face to face with/to compare
 KanjiVerb( 突き殺す, JAP_TRANSITIVE ) // (v5s,vt) to stab to death
 KanjiVerb( 突き刺す, JAP_TRANSITIVE ) // (v5s,vt) to stab/to pierce/to thrust/(P)
 KanjiVerb( 突き止める, JAP_TRANSITIVE ) // (v1,vt) to make sure/to locate/to find out/to ascertain
 KanjiVerb( 突き出す, JAP_TRANSITIVE ) // (v5s,vt) to push out/to project
 KanjiVerb( 突き除ける, JAP_TRANSITIVE ) // (v1,vt) to thrust aside
 KanjiVerb( 突き上げる, JAP_TRANSITIVE ) // (v1,vt) to push up/to toss/(P)
 KanjiVerb( 突き通す, JAP_TRANSITIVE ) // (v5s,vt) to pierce/to penetrate
 KanjiVerb( 突き転ばす, JAP_TRANSITIVE ) // (v5s,vt) to knock (a person) down
 KanjiVerb( 突き倒す, JAP_TRANSITIVE ) // (v5s,vt) to push down
 KanjiVerb( 突き動かす, JAP_TRANSITIVE ) // (v5s,vt) to stimulate/to stir up/to arouse
 KanjiVerb( 突き飛ばす, JAP_TRANSITIVE ) // (v5s,vt) to thrust away
 KanjiVerb( 突き付く, JAP_TRANSITIVE ) // (v5k,vt) to thrust in front of one's eyes
 KanjiVerb( 突き付ける, JAP_TRANSITIVE ) // (v1,vt) to thrust before/to thrust at
 KanjiVerb( 突き返す, JAP_TRANSITIVE ) // (v5s,vt) to poke in return/to send back/to reject
 KanjiVerb( 突き崩す, JAP_TRANSITIVE ) // (v5s,vt) to crush/to break through/to flatten
 KanjiVerb( 突き放す, JAP_TRANSITIVE ) // (v5s,vt) to thrust away/to refuse bluntly/to forsake
 KanjiVerb( 突き戻す, JAP_TRANSITIVE ) // (v5s,vt) to thrust back/to reject
 KanjiVerb( 突き落す, JAP_TRANSITIVE ) // (v5s,vt) to thrust down/to push off
 KanjiVerb( 突き落とす, JAP_TRANSITIVE ) // (v5s,vt) to thrust down/to push off
 KanjiVerb( 突き離す, JAP_TRANSITIVE ) // (v5s,vt) to thrust away/to refuse bluntly/to forsake
 KanjiVerb( 突き立てる, JAP_TRANSITIVE ) // (v1,vt) to pierce/to thrust violently
 KanjiVerb( 突く, JAP_TRANSITIVE ) // (v5k,vt) (1) to thrust/to strike/to attack/(2) to poke/to nudge/to pick at/(P)
 KanjiVerb( 突っかける, JAP_TRANSITIVE ) // (v1,vt) to slip on (slippers, sandals, etc)
 KanjiVerb( 突っぱねる, JAP_TRANSITIVE ) // (v1,vt) to reject/to spurn/to turn down/to refuse
 KanjiVerb( 突っ掛ける, JAP_TRANSITIVE ) // (v1,vt) to slip on (slippers, sandals, etc)/(P)
 KanjiVerb( 突っ突く, JAP_TRANSITIVE ) // (v5k,vt) to prompt someone
 KanjiVerb( 突っ放す, JAP_TRANSITIVE ) // (v5s,vt) to thrust or cast away/to look upon with detachment
 KanjiVerb( 突っ立てる, JAP_TRANSITIVE ) // (v1,vt) to stab/to plant one's feet
 KanjiVerb( 突っ撥ねる, JAP_TRANSITIVE ) // (v1,vt) to reject/to spurn/to turn down/to refuse
 KanjiVerb( 突ん出す, JAP_TRANSITIVE ) // (v5s,vt) to push out/to project
 KanjiVerb( 突出す, JAP_TRANSITIVE ) // (v5s,vt) to push out/to project
 KanjiVerb( 突付く, JAP_TRANSITIVE ) // (v5k,vt) to thrust in front of one's eyes
 KanjiVerb( 突崩す, JAP_TRANSITIVE ) // (v5s,vt) to crush/to break through/to flatten
 KanjiVerb( 届ける, JAP_TRANSITIVE ) // (v1,vt) to deliver/to forward/to send/to report/to file notice (to the authorities)/(P)
 KanjiVerb( 届け出る, JAP_TRANSITIVE ) // (v1,vt) to report/to notify
 KanjiVerb( 呑み込む, JAP_TRANSITIVE ) // (v5m,vt) (1) to gulp down/to swallow deeply/(2) to understand/to take in/to catch on to/to learn/to digest
 KanjiVerb( 呑む, JAP_TRANSITIVE ) // (v5m,vt) to drink/to gulp/to swallow
 KanjiVerb( 呑込む, JAP_TRANSITIVE ) // (v5m,vt) (1) to gulp down/to swallow deeply/(2) to understand/to take in/to catch on to/to learn/to digest
 KanjiVerb( 曇らす, JAP_TRANSITIVE ) // (v5s,vt) to encloud/to make dim or dull/to frown
 KanjiVerb( 鈍らす, JAP_TRANSITIVE ) // (v5s,vt) to blunt/to dull/to weaken
 KanjiVerb( 薙ぎ倒す, JAP_TRANSITIVE ) // (v5s,vt) to mow down/to beat/to cut a swath/to sweep off one's feet
 KanjiVerb( 薙ぎ払う, JAP_TRANSITIVE ) // (v5u,vt) to mow down
 KanjiVerb( 薙ぐ, JAP_TRANSITIVE ) // (v5k,vt) to mow down/to scythe down/to knock someone off their feet
 KanjiVerb( 馴らす, JAP_TRANSITIVE ) // (v5s,vt) to domesticate/to tame
 KanjiVerb( 匂わす, JAP_TRANSITIVE ) // (v5s,vt) to give out an odor, scent or perfume (odour)/to suggest/to insinuate
 KanjiVerb( 賑わす, JAP_TRANSITIVE ) // (v5s,vt) to make prosperous/to enliven
 KanjiVerb( 入り揚げる, JAP_TRANSITIVE ) // (v1,vt) to lavish money on
 KanjiVerb( 入れる, JAP_TRANSITIVE ) // (v1,vt) to put in/to take in/to bring in/to let in/to admit/to introduce/to commit (to prison)/to usher in/to insert/to set (jewels)/to employ/to listen to/to tolerate/to comprehend/to include/to pay (interest)/to cast (votes)/(P)
 KanjiVerb( 入れ違える, JAP_TRANSITIVE ) // (v1,vt) to misplace
 KanjiVerb( 入れ換える, JAP_TRANSITIVE ) // (v1,vt) to replace/to substitute/to shift/to change places
 KanjiVerb( 入れ交ぜる, JAP_TRANSITIVE ) // (v1,vt) to mix
 KanjiVerb( 入れ込む, JAP_TRANSITIVE ) // (v5m,vt) to put forth (effort)
 KanjiVerb( 入れ混ぜる, JAP_TRANSITIVE ) // (v1,vt) to mix
 KanjiVerb( 入れ替える, JAP_TRANSITIVE ) // (v1,vt) to replace/to substitute/to shift/to change places
 KanjiVerb( 入れ代える, JAP_TRANSITIVE ) // (v1,vt) to replace/to substitute/to shift/to change places
 KanjiVerb( 入れ揚げる, JAP_TRANSITIVE ) // (v1,vt) to lavish money on
 KanjiVerb( 任す, JAP_TRANSITIVE ) // (v5s,vt) to entrust/to leave to a person/(P)
 KanjiVerb( 任せる, JAP_TRANSITIVE ) // (v1,vt) (1) to entrust to another/to leave to/(2) to do something at one's leisure/(P)
 KanjiVerb( 忍ばせる, JAP_TRANSITIVE ) // (v1,vt) to conceal/to hide
 KanjiVerb( 忍ぶ, JAP_TRANSITIVE ) // (v5b,vt) (1) to conceal oneself/to hide/(2) to endure/(P)
 KanjiVerb( 認める, JAP_TRANSITIVE ) // (v1,vt) (1) to recognize/to recognise/to appreciate/(2) to observe/to notice/(3) to admit/to approve/(P)
 KanjiVerb( 濡らす, JAP_TRANSITIVE ) // (v5s,vt) to wet/to soak/to dip/(P)
 KanjiVerb( 念じる, JAP_TRANSITIVE ) // (v1,vt) to have in mind/to be anxious about/to pray silently
 KanjiVerb( 念ずる, JAP_TRANSITIVE ) // (vz,vt) to pray silently/to have in mind/to be anxious about
 KanjiVerb( 捻くり回す, JAP_TRANSITIVE ) // (v5s,vt) to twist/to twirl
 KanjiVerb( 捻じ伏せる, JAP_TRANSITIVE ) // (v1,vt) to hold down/to twist one's arm
 KanjiVerb( 捻り出す, JAP_TRANSITIVE ) // (v5s,vt) to work out/to raise money
 KanjiVerb( 捻り潰す, JAP_TRANSITIVE ) // (v5s,vt) to pinch and crush/to pinch out
 KanjiVerb( 燃す, JAP_TRANSITIVE ) // (v5s,vt) to burn/(P)
 KanjiVerb( 燃やす, JAP_TRANSITIVE ) // (v5s,vt) to burn/(P)
 KanjiVerb( 悩ます, JAP_TRANSITIVE ) // (v5s,vt) to afflict/to torment/to harass/to molest/(P)
 KanjiVerb( 納める, JAP_TRANSITIVE ) // (v1,vt) to obtain/to reap/to pay/to supply/to accept/to restore (something to its place)/(P)
 KanjiVerb( 覗き込む, JAP_TRANSITIVE ) // (v5m,vt) to look into/to peer in
 KanjiVerb( 播く, JAP_TRANSITIVE ) // (v5k,vt) to scatter/to sprinkle/to sow (seeds)
 KanjiVerb( 破く, JAP_TRANSITIVE ) // (v5k,vt) to tear/to violate/to defeat/to smash/to destroy
 KanjiVerb( 拝み倒す, JAP_TRANSITIVE ) // (v5s,vt) to persuade someone to consent/to entreat repeatedly/to beg/to implore
 KanjiVerb( 拝む, JAP_TRANSITIVE ) // (v5m,vt) to worship/to beg/to make a supplication/(P)
 KanjiVerb( 背ける, JAP_TRANSITIVE ) // (v1,vt) to turn one's face away/to avert one's eyes
 KanjiVerb( 背負う, JAP_TRANSITIVE ) // (v5u,vt) to be burdened with/to carry on back or shoulder/(P)
 KanjiVerb( 培う, JAP_TRANSITIVE ) // (v5u,vt) to cultivate/to foster/(P)
 KanjiVerb( 買い換える, JAP_TRANSITIVE ) // (v1,vt) to buy a replacement/to replace by buying something new
 KanjiVerb( 買い求める, JAP_TRANSITIVE ) // (v1,vt) to buy
 KanjiVerb( 買い込む, JAP_TRANSITIVE ) // (v5m,vt) to purchase/to buy up
 KanjiVerb( 買い受ける, JAP_TRANSITIVE ) // (v1,vt) to purchase
 KanjiVerb( 買い上げる, JAP_TRANSITIVE ) // (v1,vt) to buy/to buy up/to bid up
 KanjiVerb( 買い占める, JAP_TRANSITIVE ) // (v1,vt) to buy up/(P)
 KanjiVerb( 買い足す, JAP_TRANSITIVE ) // (v5s,vt) to make additional purchases
 KanjiVerb( 買い替える, JAP_TRANSITIVE ) // (v1,vt) to buy a replacement/to replace by buying something new
 KanjiVerb( 買い叩く, JAP_TRANSITIVE ) // (v5k,vt) to beat down prices/to strike a hard bargain
 KanjiVerb( 買い入れる, JAP_TRANSITIVE ) // (v1,vt) to purchase/to buy in/(P)
 KanjiVerb( 買い付ける, JAP_TRANSITIVE ) // (v1,vt) to buy in/to purchase
 KanjiVerb( 買い戻す, JAP_TRANSITIVE ) // (v5s,vt) to buy back/to redeem
 KanjiVerb( 買う, JAP_TRANSITIVE ) // (v5u,vt) to buy/(P)
 KanjiVerb( 買叩く, JAP_TRANSITIVE ) // (v5k,vt) to beat down prices/to strike a hard bargain
 KanjiVerb( 売りつける, JAP_TRANSITIVE ) // (v1,vt) to palm off/to force a sale
 KanjiVerb( 売り急ぐ, JAP_TRANSITIVE ) // (v5g,vt) to sell in haste
 KanjiVerb( 売り広める, JAP_TRANSITIVE ) // (v1,vt) to expand a market/to find a new market
 KanjiVerb( 売り込む, JAP_TRANSITIVE ) // (v5m,vt) to build a market for/to become well-known/to sell/(P)
 KanjiVerb( 売り捌く, JAP_TRANSITIVE ) // (v5k,vt) to sell out
 KanjiVerb( 売り出す, JAP_TRANSITIVE ) // (v5s,vt) to put on sale/to market/to become popular/(P)
 KanjiVerb( 売り尽くす, JAP_TRANSITIVE ) // (v5s,vt) to sell out/to exhaust one's stock
 KanjiVerb( 売り尽す, JAP_TRANSITIVE ) // (v5s,vt) to sell out/to exhaust one's stock
 KanjiVerb( 売り叩く, JAP_TRANSITIVE ) // (v5k,vt) to beat down prices
 KanjiVerb( 売り渡す, JAP_TRANSITIVE ) // (v5s,vt) to sell over to
 KanjiVerb( 売り飛ばす, JAP_TRANSITIVE ) // (v5s,vt) to dispose of/to sell off
 KanjiVerb( 売り付ける, JAP_TRANSITIVE ) // (v1,vt) to palm off/to force a sale
 KanjiVerb( 売り払う, JAP_TRANSITIVE ) // (v5u,vt) to dispose of
 KanjiVerb( 売り歩く, JAP_TRANSITIVE ) // (v5k,vt) to peddle
 KanjiVerb( 剥がす, JAP_TRANSITIVE ) // (v5s,vt) to tear off/to peel off/to rip off/to strip off/to skin/to flay/to disrobe/to deprive of/to detach/to disconnect/(P)
 KanjiVerb( 剥き出す, JAP_TRANSITIVE ) // (v5s,vt) to show/to bare (the teeth)
 KanjiVerb( 泊める, JAP_TRANSITIVE ) // (v1,vt) to give shelter to/to lodge/(P)
 KanjiVerb( 白げる, JAP_TRANSITIVE ) // (v1,vt) to polish (rice)/to refine/to purify
 KanjiVerb( 薄める, JAP_TRANSITIVE ) // (v1,vt) to dilute/to water down/(P)
 KanjiVerb( 迫り出す, JAP_TRANSITIVE ) // (v5s,vt) to push (a thing) out/to rise out the trap door (on stage)
 KanjiVerb( 迫出す, JAP_TRANSITIVE ) // (v5s,vt) to push (a thing) out/to rise out the trap door (on stage)
 KanjiVerb( 曝け出す, JAP_TRANSITIVE ) // (v5s,vt) to expose/to disclose/to lay bare/to confess
 KanjiVerb( 曝す, JAP_TRANSITIVE ) // (v5s,vt) (1) to expose (to the air, to the public, to danger, etc.)/(2) to bleach/to refine/(P)
 KanjiVerb( 縛りつける, JAP_TRANSITIVE ) // (v1,vt) to tie
 KanjiVerb( 縛り上げる, JAP_TRANSITIVE ) // (v1,vt) to bind (tie) up
 KanjiVerb( 縛り付ける, JAP_TRANSITIVE ) // (v1,vt) to tie
 KanjiVerb( 抜かす, JAP_TRANSITIVE ) // (v5s,vt) to omit/to leave out/(P)
 KanjiVerb( 抜き出す, JAP_TRANSITIVE ) // (v5s,vt) to start to pull out
 KanjiVerb( 抜き放す, JAP_TRANSITIVE ) // (v5s,vt) to unsheathe one's sword
 KanjiVerb( 抜き放つ, JAP_TRANSITIVE ) // (v5t,vt) to unsheathe
 KanjiVerb( 抜く, JAP_TRANSITIVE ) // (v5k,vt) (1) to extract/to omit/to surpass/to overtake/to draw out/to unplug/(2) (suf) to do something to the end/(P)
 KanjiVerb( 判じる, JAP_TRANSITIVE ) // (v1,vt) to judge/to decide/to guess/to solve/to decipher/to interpret/to divine
 KanjiVerb( 反す, JAP_TRANSITIVE ) // (v5s,vt) to change/to turn over/to turn upside down/(P)
 KanjiVerb( 反らす, JAP_TRANSITIVE ) // (v5s,vt) to bend/to warp/to curve
 KanjiVerb( 反らせる, JAP_TRANSITIVE ) // (v1,vt) to bend/to warp
 KanjiVerb( 犯す, JAP_TRANSITIVE ) // (v5s,vt) to commit/to perpetrate/to violate/to rape/(P)
 KanjiVerb( 挽く, JAP_TRANSITIVE ) // (v5k,vt) (1) to saw/(2) to grind (e.g. coffee beans)/to mill
 KanjiVerb( 卑しめる, JAP_TRANSITIVE ) // (v1,vt) to despise/to abase (oneself)
 KanjiVerb( 否む, JAP_TRANSITIVE ) // (v5m,vt) to detest/to dislike
 KanjiVerb( 庇う, JAP_TRANSITIVE ) // (v5u,vt) to protect someone/to take under one's wing/to plead for/to stick up for/to cover up for someone/(P)
 KanjiVerb( 悲しむ, JAP_TRANSITIVE ) // (v5m,vt) to be sad/to mourn for/to regret/(P)
 KanjiVerb( 比べる, JAP_TRANSITIVE ) // (v1,vt) (1) to compare/(2) to calibrate/(P)
 KanjiVerb( 疲らす, JAP_TRANSITIVE ) // (v5s,vt) to tire/to weary/to exhaust/to fatigue
 KanjiVerb( 秘める, JAP_TRANSITIVE ) // (v1,vt) to hide/to keep to oneself/(P)
 KanjiVerb( 肥やす, JAP_TRANSITIVE ) // (v5s,vt) to fertilize/to fertilise/to manure/to enrich/(P)
 KanjiVerb( 被う, JAP_TRANSITIVE ) // (v5u,vt) to cover/to hide/to conceal/to wrap/to disguise
 KanjiVerb( 被す, JAP_TRANSITIVE ) // (v5s,vt) to cover (with something)
 KanjiVerb( 被せる, JAP_TRANSITIVE ) // (v1,vt) to cover (with something)/to plate something (with a metal)/to pour or dash a liquid (on something)/to charge (a person with a guilt)/(P)
 KanjiVerb( 費やす, JAP_TRANSITIVE ) // (v5s,vt) to spend/to devote/to waste/(P)
 KanjiVerb( 避く, JAP_TRANSITIVE ) // (v5k,vt) to avoid
 KanjiVerb( 避ける, JAP_TRANSITIVE ) // (v1,vt) (1) to avoid (physical contact with)/(v1) (2) to ward off/to avert/(P)
 KanjiVerb( 飛ばす, JAP_TRANSITIVE ) // (v5s,vt) to skip over/to omit/(P)
 KanjiVerb( 飛び越える, JAP_TRANSITIVE ) // (v1,vt) to jump over/to clear/to walk over (someone)
 KanjiVerb( 飛び越す, JAP_TRANSITIVE ) // (v5s,vt) to leap over
 KanjiVerb( 飛越す, JAP_TRANSITIVE ) // (v5s,vt) to leap over
 KanjiVerb( 備えつける, JAP_TRANSITIVE ) // (v1,vt) to provide/to furnish/to equip/to install
 KanjiVerb( 備える, JAP_TRANSITIVE ) // (v1,vt) (1) to furnish/to provide for/to equip/to install/(2) to have ready/to prepare for/(3) to possess/to have/to be endowed with/to be armed with/(P)
 KanjiVerb( 備え付ける, JAP_TRANSITIVE ) // (v1,vt) to provide/to furnish/to equip/to install/(P)
 KanjiVerb( 微温める, JAP_TRANSITIVE ) // (v1,vt) to cool something down (e.g., by adding water)
 KanjiVerb( 紐解く, JAP_TRANSITIVE ) // (v5k,vi,vt) (1) to peruse (a book)/(2) to untie a scroll
 KanjiVerb( 表す, JAP_TRANSITIVE ) // (v5s,vt) to express/to show/to reveal/(P)
 KanjiVerb( 表わす, JAP_TRANSITIVE ) // (v5s,vt) to express/to show/to reveal/(P)
 KanjiVerb( 描き出す, JAP_TRANSITIVE ) // (v5s,vt) to delineate/to draw/to express/to imagine
 KanjiVerb( 描き上げる, JAP_TRANSITIVE ) // (v1,vt) to write out or down/to finish writing
 KanjiVerb( 描く, JAP_TRANSITIVE ) // (v5k,vt) to draw/to paint/to sketch/to depict/to describe
 KanjiVerb( 付ける, JAP_TRANSITIVE ) // (v1,vt) (1) to attach/to join/to add/to append/to affix/to stick/to glue/to fasten/to sew on/to apply (ointment)/(2) to furnish (a house with)/(3) to wear/to put on/(4) to keep a diary/to make an entry/(5) to appraise/to set (a price)/(6) to bring alongside/(7) to place (under guard or doctor)/(8) to follow/to shadow/(9) to load/to give (courage to)/(10) to keep (an eye on)/(11) to establish (relations or understanding)/(P)
 KanjiVerb( 付け加える, JAP_TRANSITIVE ) // (v1,vt) to add one thing to another/(P)
 KanjiVerb( 付け回す, JAP_TRANSITIVE ) // (v5s,vt) to follow/to shadow/to hanker after/to hover around
 KanjiVerb( 付け換える, JAP_TRANSITIVE ) // (v1,vt) to renew/to replace/to change for/to attach anew
 KanjiVerb( 付け出す, JAP_TRANSITIVE ) // (v5s,vt) to charge
 KanjiVerb( 付け狙う, JAP_TRANSITIVE ) // (v5u,vt) to prowl after/to keep watch on
 KanjiVerb( 付け足す, JAP_TRANSITIVE ) // (v5s,vt) to add to/(P)
 KanjiVerb( 付け替える, JAP_TRANSITIVE ) // (v1,vt) to renew/to replace/to change for/to attach anew
 KanjiVerb( 扶く, JAP_TRANSITIVE ) // (v5k,vt) to help/to save/to rescue
 KanjiVerb( 扶ける, JAP_TRANSITIVE ) // (v1,vt) to help/to save/to rescue/to give relief to/to spare (life)/to reinforce/to promote/to abet
 KanjiVerb( 敷き詰める, JAP_TRANSITIVE ) // (v1,vt) to lay/to spread all over
 KanjiVerb( 浮かす, JAP_TRANSITIVE ) // (v5s,vt) to raise/to rise
 KanjiVerb( 浮かべる, JAP_TRANSITIVE ) // (v1,vt) to float/to express/to look (sad, glad)/(P)
 KanjiVerb( 腐す, JAP_TRANSITIVE ) // (v5s,vt) to speak ill of
 KanjiVerb( 腐らす, JAP_TRANSITIVE ) // (v5s,vt) to spoil/to rot/to corrode
 KanjiVerb( 負う, JAP_TRANSITIVE ) // (v5u,vt) to bear/to owe/(P)
 KanjiVerb( 負かす, JAP_TRANSITIVE ) // (v5s,vt) to defeat/(P)
 KanjiVerb( 撫でつける, JAP_TRANSITIVE ) // (v1,vt) to comb down/to smooth down
 KanjiVerb( 撫でる, JAP_TRANSITIVE ) // (v1,vt) to brush gently/to stroke/(P)
 KanjiVerb( 撫で上げる, JAP_TRANSITIVE ) // (v1,vt) to comb back
 KanjiVerb( 撫で付ける, JAP_TRANSITIVE ) // (v1,vt) to comb down/to smooth down
 KanjiVerb( 舞い納める, JAP_TRANSITIVE ) // (v1,vt) to conclude a dance/to dance the last dance
 KanjiVerb( 封じ込める, JAP_TRANSITIVE ) // (v1,vt) to shut in/to confine/to contain
 KanjiVerb( 葺き替える, JAP_TRANSITIVE ) // (v1,vt) to reroof/to rethatch/to retile
 KanjiVerb( 伏し拝む, JAP_TRANSITIVE ) // (v5m,vt) to kneel and worship
 KanjiVerb( 伏せる, JAP_TRANSITIVE ) // (v1,vt) to lay something upside down/to turn something over/to cover/to lay (pipes)/to lay (an ambush)/to hide/(P)
 KanjiVerb( 副える, JAP_TRANSITIVE ) // (v1,vt) to add to/to attach/to append/to accompany/to garnish/to imitate/to annex
 KanjiVerb( 復習える, JAP_TRANSITIVE ) // (v1,vt) to review/to rehearse/to practise/to practice
 KanjiVerb( 覆いかぶせる, JAP_TRANSITIVE ) // (v1,vt) to cover up with something
 KanjiVerb( 覆い被せる, JAP_TRANSITIVE ) // (v1,vt) to cover up with something
 KanjiVerb( 覆う, JAP_TRANSITIVE ) // (v5u,vt) to cover/to hide/to conceal/to wrap/to disguise/(P)
 KanjiVerb( 覆す, JAP_TRANSITIVE ) // (v5s,vt) to overturn/to upset/to overthrow/to undermine/(P)
 KanjiVerb( 払い下げる, JAP_TRANSITIVE ) // (v1,vt) to make a sale of government property
 KanjiVerb( 払い込む, JAP_TRANSITIVE ) // (v5m,vt) to deposit/to pay in/(P)
 KanjiVerb( 払い出す, JAP_TRANSITIVE ) // (v5s,vt) to pay (out)/to drive away
 KanjiVerb( 払い除ける, JAP_TRANSITIVE ) // (v1,vt) to ward off/to brush away/to fling off/to drive away
 KanjiVerb( 払い清める, JAP_TRANSITIVE ) // (v1,vt) to purify/to exorcise
 KanjiVerb( 払い渡す, JAP_TRANSITIVE ) // (v5s,vt) to pay/to pay out/to pay over
 KanjiVerb( 払い戻す, JAP_TRANSITIVE ) // (v5s,vt) to repay/to pay back/(P)
 KanjiVerb( 払う, JAP_TRANSITIVE ) // (v5u,vt) (1) to pay/(2) to brush/to wipe/(P)
 KanjiVerb( 沸かす, JAP_TRANSITIVE ) // (v5s,vt) to boil/to heat/(P)
 KanjiVerb( 物言う, JAP_TRANSITIVE ) // (v5u,vt) to talk/to carry meaning
 KanjiVerb( 分かつ, JAP_TRANSITIVE ) // (v5t,vt) to divide/to separate/to distinguish/(P)
 KanjiVerb( 分ける, JAP_TRANSITIVE ) // (v1,vt) to divide/to separate/to make distinctions/to differentiate (between)/(P)
 KanjiVerb( 焚きつける, JAP_TRANSITIVE ) // (v1,vt) to kindle/to build a fire/to instigate/to stir up
 KanjiVerb( 焚き染める, JAP_TRANSITIVE ) // (v1,vt) to perfume clothes by burning incense
 KanjiVerb( 焚き付ける, JAP_TRANSITIVE ) // (v1,vt) to kindle/to build a fire/to instigate/to stir up
 KanjiVerb( 焚く, JAP_TRANSITIVE ) // (v5k,vt) to burn/to kindle/to build a fire/(P)
 KanjiVerb( 奮い起こす, JAP_TRANSITIVE ) // (v5s,vt) to muster (e.g., courage)/to gather/to collect/to pluck up
 KanjiVerb( 紛らす, JAP_TRANSITIVE ) // (v5s,vt) to divert/to distract/(P)
 KanjiVerb( 紛らわす, JAP_TRANSITIVE ) // (v5s,vt) to divert/to distract
 KanjiVerb( 聞かす, JAP_TRANSITIVE ) // (v5s,vt) to inform about/to read to/to sing for/(P)
 KanjiVerb( 聞かせる, JAP_TRANSITIVE ) // (v1,vt) to read to/to sing for/to inform/to tell
 KanjiVerb( 聞きつける, JAP_TRANSITIVE ) // (v1,vt) to hear/to catch (the sound)
 KanjiVerb( 聞き違える, JAP_TRANSITIVE ) // (v1,vt) to mishear
 KanjiVerb( 聞き外す, JAP_TRANSITIVE ) // (v5s,vt) to mishear
 KanjiVerb( 聞き覚える, JAP_TRANSITIVE ) // (v1,vt) to be familiar/to learn by ear/to pick up knowledge
 KanjiVerb( 聞き慣れる, JAP_TRANSITIVE ) // (v1,vt) to get used to hearing
 KanjiVerb( 聞き及ぶ, JAP_TRANSITIVE ) // (v5b,vt) to hear of/to learn of
 KanjiVerb( 聞き合せる, JAP_TRANSITIVE ) // (v1,vt) to make inquiries/to refer to
 KanjiVerb( 聞き込む, JAP_TRANSITIVE ) // (v5m,vt) to get information/to find out/to get wind of
 KanjiVerb( 聞き捨てる, JAP_TRANSITIVE ) // (v1,vt) to ignore/to overlook
 KanjiVerb( 聞き出す, JAP_TRANSITIVE ) // (v5s,vt) to get information out of a person/to begin listening
 KanjiVerb( 聞き澄ます, JAP_TRANSITIVE ) // (v5s,vt) to listen attentively
 KanjiVerb( 聞き置く, JAP_TRANSITIVE ) // (v5k,vt) to listen
 KanjiVerb( 聞き直す, JAP_TRANSITIVE ) // (v5s,vt) to listen again/to ask again
 KanjiVerb( 聞き伝える, JAP_TRANSITIVE ) // (v1,vt) to hear (secondhand)
 KanjiVerb( 聞き届ける, JAP_TRANSITIVE ) // (v1,vt) to grant
 KanjiVerb( 聞き馴れる, JAP_TRANSITIVE ) // (v1,vt) to get used to hearing
 KanjiVerb( 聞き入れる, JAP_TRANSITIVE ) // (v1,vt) to grant (a wish)/to accede/to comply with
 KanjiVerb( 聞き付ける, JAP_TRANSITIVE ) // (v1,vt) to hear/to catch (the sound)
 KanjiVerb( 聞き分ける, JAP_TRANSITIVE ) // (v1,vt) to recognize (identify) by sound/to recognise by sound
 KanjiVerb( 聞き返す, JAP_TRANSITIVE ) // (v5s,vt) to ask in return/to ask again/to listen repeatedly
 KanjiVerb( 聞き飽きる, JAP_TRANSITIVE ) // (v1,vt) to be tired of hearing
 KanjiVerb( 聞き忘れる, JAP_TRANSITIVE ) // (v1,vt) to forget to ask
 KanjiVerb( 聞き落す, JAP_TRANSITIVE ) // (v5s,vt) to fail to catch
 KanjiVerb( 聞き流す, JAP_TRANSITIVE ) // (v5s,vt) to ignore
 KanjiVerb( 聞き做す, JAP_TRANSITIVE ) // (v5s,vt) to consider
 KanjiVerb( 聞き咎める, JAP_TRANSITIVE ) // (v1,vt) to find fault with
 KanjiVerb( 聞く, JAP_TRANSITIVE ) // (v5k,vt) (1) to hear/to listen/(2) to ask/(P)
 KanjiVerb( 聞込む, JAP_TRANSITIVE ) // (v5m,vt) to get information/to find out/to get wind of
 KanjiVerb( 併せ持つ, JAP_TRANSITIVE ) // (v5t,vt) to own (something) as well
 KanjiVerb( 平らげる, JAP_TRANSITIVE ) // (v1,vt) to subjugate/to put down (trouble)/to consume (food)/to eat up
 KanjiVerb( 並べる, JAP_TRANSITIVE ) // (v1,vt) to line up/to set up/(P)
 KanjiVerb( 並べ立てる, JAP_TRANSITIVE ) // (v1,vt) to enumerate
 KanjiVerb( 閉ざす, JAP_TRANSITIVE ) // (v5s,vt) to shut/to close/to lock/to fasten/to plunge (in grief)/(P)
 KanjiVerb( 閉じ込む, JAP_TRANSITIVE ) // (v5m,vt) to (keep on) file
 KanjiVerb( 閉じ込める, JAP_TRANSITIVE ) // (v1,vt) to lock up/to shut up/to imprison
 KanjiVerb( 閉める, JAP_TRANSITIVE ) // (v1,vt) to close/to shut/(P)
 KanjiVerb( 閉め出す, JAP_TRANSITIVE ) // (v5s,vt) to shut out/to bar/to lock out
 KanjiVerb( 蔑む, JAP_TRANSITIVE ) // (v5m,vt) to scorn/to despise/(P)
 KanjiVerb( 変える, JAP_TRANSITIVE ) // (v1,vt) to change/to alter/to vary/to convert/to revise/to amend
 KanjiVerb( 片づける, JAP_TRANSITIVE ) // (v1,vt) (1) to tidy up/to put in order/to straighten up/to put away/(2) to settle (problem)/to clear (dispute)/(3) to finish/to bring something to an end/(4) to marry off (e.g., a daughter)/(5) to do away with someone/to bump someone off
 KanjiVerb( 片付ける, JAP_TRANSITIVE ) // (v1,vt) (1) to tidy up/to put in order/to straighten up/to put away/(2) to settle (problem)/to clear (dispute)/(3) to finish/to bring something to an end/(4) to marry off (e.g., a daughter)/(5) to do away with someone/to bump someone off/(P)
 KanjiVerb( 編み出す, JAP_TRANSITIVE ) // (v5s,vt) to work out/to think out
 KanjiVerb( 編む, JAP_TRANSITIVE ) // (v5m,vt) (1) to knit/to plait/to braid/(2) to compile (anthology, dictionary, etc.)/to edit/(P)
 KanjiVerb( 返す, JAP_TRANSITIVE ) // (v5s,vt) to return something/(P)
 KanjiVerb( 弁える, JAP_TRANSITIVE ) // (v1,vt) to know (right from wrong)/to discern/to discriminate/to understand/to bear in mind/(P)
 KanjiVerb( 鞭打つ, JAP_TRANSITIVE ) // (v5t,vt) to whip/to lash/to give the rod/to spur on/to encourage
 KanjiVerb( 保つ, JAP_TRANSITIVE ) // (v5t,vt) to keep/to preserve/to hold/to retain/to maintain/to support/to sustain/to last/to endure/to keep well (food)/to wear well/to be durable/(P)
 KanjiVerb( 捕える, JAP_TRANSITIVE ) // (v1,vt) to seize/to grasp/to capture/to arrest/(P)
 KanjiVerb( 捕まえる, JAP_TRANSITIVE ) // (v1,vt) to catch/to arrest/to seize/(P)
 KanjiVerb( 捕らえる, JAP_TRANSITIVE ) // (v1,vt) to seize/to grasp/to capture/to arrest/(P)
 KanjiVerb( 補う, JAP_TRANSITIVE ) // (v5u,vt) to compensate for/(P)
 KanjiVerb( 輔く, JAP_TRANSITIVE ) // (v5k,vt) to help/to save/to rescue
 KanjiVerb( 輔ける, JAP_TRANSITIVE ) // (v1,vt) to help/to save/to rescue/to give relief to/to spare (life)/to reinforce/to promote/to abet
 KanjiVerb( 慕う, JAP_TRANSITIVE ) // (v5u,vt) to yearn for/to miss/to adore/to love dearly/(P)
 KanjiVerb( 暮らす, JAP_TRANSITIVE ) // (v5s,vt) to live/to get along/(P)
 KanjiVerb( 包み隠す, JAP_TRANSITIVE ) // (v5s,vt) to conceal/to keep secret/to cover up
 KanjiVerb( 包み込む, JAP_TRANSITIVE ) // (v5m,vt) to wrap up
 KanjiVerb( 包む, JAP_TRANSITIVE ) // (v5m,vt) (1) to wrap up/to tuck in/to pack/to do up/to cover with/to dress in/(v5m) (2) to conceal/to hide/to be engulfed in/to be enveloped by/(P)
 KanjiVerb( 包める, JAP_TRANSITIVE ) // (v1,vt) to lump together/to include/to sum up/to quibble
 KanjiVerb( 報いる, JAP_TRANSITIVE ) // (v1,vt) to reward/to recompense/to repay/(P)
 KanjiVerb( 報う, JAP_TRANSITIVE ) // (v5u,vt) to reward/to recompense/to repay/(P)
 KanjiVerb( 報じる, JAP_TRANSITIVE ) // (v1,vt) to inform/to report/(P)
 KanjiVerb( 報ずる, JAP_TRANSITIVE ) // (vz,vt) to inform/to report/(P)
 KanjiVerb( 奉じる, JAP_TRANSITIVE ) // (v1,vt) to obey/to follow
 KanjiVerb( 崩す, JAP_TRANSITIVE ) // (v5s,vt) to destroy/to pull down/to make change (money)/(P)
 KanjiVerb( 抱える, JAP_TRANSITIVE ) // (v1,vt) (1) to hold or carry under or in the arms/(2) to have (esp. problems, debts, etc.)/(3) to employ/to engage/to hire/(P)
 KanjiVerb( 抱え込む, JAP_TRANSITIVE ) // (v5m,vt) to hold (carry) a thing in one's arm/to embrace (a baby)/to take upon oneself
 KanjiVerb( 抱きしめる, JAP_TRANSITIVE ) // (v1,vt) to hug someone close/to hold someone tight/to embrace closely
 KanjiVerb( 抱き起こす, JAP_TRANSITIVE ) // (v5s,vt) to lift (a person) in one's arms/to help (a person) sit up
 KanjiVerb( 抱き起す, JAP_TRANSITIVE ) // (v5s,vt) to lift (a person) in one's arms/to help (a person) sit up
 KanjiVerb( 抱き込む, JAP_TRANSITIVE ) // (v5m,vt) to hold in one's arms/to bring over a person to one's side/to involve
 KanjiVerb( 抱き上げる, JAP_TRANSITIVE ) // (v1,vt) to hold up in one's arms
 KanjiVerb( 抱き締める, JAP_TRANSITIVE ) // (v1,vt) to hug someone close/to hold someone tight/to embrace closely
 KanjiVerb( 抱き抱える, JAP_TRANSITIVE ) // (v1,vt) to hold/to carry/to embrace (in one's arms)
 KanjiVerb( 抱き留める, JAP_TRANSITIVE ) // (v1,vt) to catch in one's arms
 KanjiVerb( 抱き竦める, JAP_TRANSITIVE ) // (v1,vt) to hug tight
 KanjiVerb( 抱く, JAP_TRANSITIVE ) // (v5k,vt) (1) to embrace/to hold in the arms, e.g., a baby/to hug/(v5k) (2) to sleep with/(v5k) (3) to sit on eggs/(P)
 KanjiVerb( 捧げる, JAP_TRANSITIVE ) // (v1,vt) to lift up/to give/to offer/to consecrate/to devote/to sacrifice/to dedicate/(P)
 KanjiVerb( 放く, JAP_TRANSITIVE ) // (v5k,vt) (1) (uk) to let loose (e.g., a fart)/(2) to utter (e.g., a lie)
 KanjiVerb( 放す, JAP_TRANSITIVE ) // (v5s,vt) to separate/to set free/to turn loose/(P)
 KanjiVerb( 放つ, JAP_TRANSITIVE ) // (v5t,vt) to free/to release/to fire/(P)
 KanjiVerb( 放り込む, JAP_TRANSITIVE ) // (v5m,vt) to throw into
 KanjiVerb( 放り出す, JAP_TRANSITIVE ) // (v5s,vt) to throw out/to fire/to expel/to give up/to abandon/to neglect
 KanjiVerb( 泡立てる, JAP_TRANSITIVE ) // (v1,vt) to beat/to whip
 KanjiVerb( 縫いつける, JAP_TRANSITIVE ) // (v1,vt) to sew on
 KanjiVerb( 縫い込む, JAP_TRANSITIVE ) // (v5m,vt) to sew in
 KanjiVerb( 縫い上げる, JAP_TRANSITIVE ) // (v1,vt) to finish sewing
 KanjiVerb( 縫い直す, JAP_TRANSITIVE ) // (v5s,vt) to resew/to remake
 KanjiVerb( 縫い付ける, JAP_TRANSITIVE ) // (v1,vt) to sew on
 KanjiVerb( 縫い返す, JAP_TRANSITIVE ) // (v5s,vt) to resew
 KanjiVerb( 縫う, JAP_TRANSITIVE ) // (v5u,vt) to sew/(P)
 KanjiVerb( 褒める, JAP_TRANSITIVE ) // (v1,vt) to praise/to admire/to speak well/(P)
 KanjiVerb( 褒め称える, JAP_TRANSITIVE ) // (v1,vt) to admire/to praise/to applaud
 KanjiVerb( 訪う, JAP_TRANSITIVE ) // (v5u-s,vt) (1) to ask/to question/to inquire/(2) to charge (i.e. with a crime)/to accuse/(3) to care (about)/(4) without regard to (with negative verb)
 KanjiVerb( 訪ねる, JAP_TRANSITIVE ) // (v1,vt) to visit/(P)
 KanjiVerb( 飽かす, JAP_TRANSITIVE ) // (v5s,vt) to glut/to satiate/to weary/to tire/to bore/to weary
 KanjiVerb( 亡くす, JAP_TRANSITIVE ) // (v5s,vt) (1) to lose something/(v5s) (2) to get rid of/(v5s) (3) to lose someone (wife, child, etc.)/(P)
 KanjiVerb( 亡くなす, JAP_TRANSITIVE ) // (v5s,vt) to lose someone, wife, child, etc.
 KanjiVerb( 亡ぼす, JAP_TRANSITIVE ) // (v5s,vt) to destroy/to overthrow/to wreck/to ruin
 KanjiVerb( 妨げる, JAP_TRANSITIVE ) // (v1,vt) to disturb/to prevent/(P)
 KanjiVerb( 忘れる, JAP_TRANSITIVE ) // (v1,vt) to forget/to leave carelessly/to be forgetful of/to forget about/to forget (an article)/(P)
 KanjiVerb( 暴く, JAP_TRANSITIVE ) // (v5k,vt) to disclose/to divulge/to expose
 KanjiVerb( 望む, JAP_TRANSITIVE ) // (v5m,vt) to desire/to wish for/to see/to command (a view of)/(P)
 KanjiVerb( 冒す, JAP_TRANSITIVE ) // (v5s,vt) to brave/to risk/to face/to venture/to desecrate/to profane/(P)
 KanjiVerb( 紡ぐ, JAP_TRANSITIVE ) // (v5g,vt) to spin/to make yarn/(P)
 KanjiVerb( 膨らます, JAP_TRANSITIVE ) // (v5s,vt) to swell/to expand/to inflate/to bulge/(P)
 KanjiVerb( 防ぐ, JAP_TRANSITIVE ) // (v5g,vt) to defend (against)/to protect/to prevent/(P)
 KanjiVerb( 翻す, JAP_TRANSITIVE ) // (v5s,vt) to change (mind)/to reverse (decision)/to wave/to flutter/(P)
 KanjiVerb( 摩りつける, JAP_TRANSITIVE ) // (v1,vt) (1) to rub against/to nuzzle against, e.g., dog nosing a person/(2) to strike (a match)
 KanjiVerb( 摩り替える, JAP_TRANSITIVE ) // (v1,vt) to secretly substitute
 KanjiVerb( 摩り付ける, JAP_TRANSITIVE ) // (v1,vt) (1) to rub against/to nuzzle against, e.g., dog nosing a person/(2) to strike (a match)
 KanjiVerb( 磨き上げる, JAP_TRANSITIVE ) // (v1,vt) to polish up/to shine up
 KanjiVerb( 磨き立てる, JAP_TRANSITIVE ) // (v1,vt) to polish (up)/dress up
 KanjiVerb( 磨ぐ, JAP_TRANSITIVE ) // (v5g,vt) to sharpen/to grind/to scour/to hone/to polish/to wash (rice)
 KanjiVerb( 磨り減らす, JAP_TRANSITIVE ) // (v5s,vt) to wear away/to rub down/to abrade
 KanjiVerb( 磨り出す, JAP_TRANSITIVE ) // (v5s,vt) to polish
 KanjiVerb( 磨り潰す, JAP_TRANSITIVE ) // (v5s,vt) to pulverize/to pulverise/to mash/to deface/to lose a fortune
 KanjiVerb( 埋める, JAP_TRANSITIVE ) // (v1,vt) (1) to bury/(2) to fill up (e.g., audience fills a hall)/to fill (a seat, a vacant position)/(3) to plug gaps/to stop a gap/(4) to make amends/to cover up for something/(5) to put cold water in a bath/(P)
 KanjiVerb( 埋め合せる, JAP_TRANSITIVE ) // (v1,vt) to make amends/to compensate for/to make up for
 KanjiVerb( 埋め合わせる, JAP_TRANSITIVE ) // (v1,vt) to make amends/to compensate for/to make up for
 KanjiVerb( 埋め立てる, JAP_TRANSITIVE ) // (v1,vt) to reclaim/to fill up
 KanjiVerb( 満たす, JAP_TRANSITIVE ) // (v5s,vt) (1) to fill (e.g., a cup)/(2) to satisfy/to ingratiate/to fulfill/(P)
 KanjiVerb( 味わう, JAP_TRANSITIVE ) // (v5u,vt) to taste/to savor/to relish/(P)
 KanjiVerb( 未届ける, JAP_TRANSITIVE ) // (v1,vt) to make sure of/to assure oneself of/to see with one's own eyes/to ascertain
 KanjiVerb( 魅す, JAP_TRANSITIVE ) // (v5s,vt) to bewitch/to confuse/to enchant/to delude
 KanjiVerb( 務める, JAP_TRANSITIVE ) // (v1,vt) (1) to serve/to fill a post/to serve under/to work (for)/(2) to exert oneself/to endeavor/to endeavour/to be diligent/(3) to play (the part of)/(P)
 KanjiVerb( 無くす, JAP_TRANSITIVE ) // (v5s,vt) (1) to lose something/(v5s) (2) to get rid of/(P)
 KanjiVerb( 無くなす, JAP_TRANSITIVE ) // (v5s,vt) to lose/to miss
 KanjiVerb( 名づける, JAP_TRANSITIVE ) // (v1,vt) to name (someone)
 KanjiVerb( 名付ける, JAP_TRANSITIVE ) // (v1,vt) to name (someone)/(P)
 KanjiVerb( 命じる, JAP_TRANSITIVE ) // (v1,vt) to order/to command/to appoint/(P)
 KanjiVerb( 命ずる, JAP_TRANSITIVE ) // (vz,vt) to command/to appoint/(P)
 KanjiVerb( 明かす, JAP_TRANSITIVE ) // (v5s,vt) to pass/spend/to reveal/to divulge/(P)
 KanjiVerb( 明け渡す, JAP_TRANSITIVE ) // (v5s,vt) to vacate/to surrender
 KanjiVerb( 明け払う, JAP_TRANSITIVE ) // (v5u,vt) to open/to vacate
 KanjiVerb( 明け放す, JAP_TRANSITIVE ) // (v5s,vt) to open wide (doors,windows, etc.)/to fling open
 KanjiVerb( 盟う, JAP_TRANSITIVE ) // (v5u,vt) to swear/to vow/to take an oath/to pledge
 KanjiVerb( 迷わす, JAP_TRANSITIVE ) // (v5s,vt) to puzzle/perplex/bewilder/delude/mislead/fascinate
 KanjiVerb( 鳴らす, JAP_TRANSITIVE ) // (v5s,vt) to ring/to sound/to chime/to beat/to snort (nose)/(P)
 KanjiVerb( 滅ぼす, JAP_TRANSITIVE ) // (v5s,vt) to destroy/to overthrow/to wreck/to ruin/(P)
 KanjiVerb( 免じる, JAP_TRANSITIVE ) // (v1,vt) to dismiss/to exempt
 KanjiVerb( 免ずる, JAP_TRANSITIVE ) // (vz,vt) to dismiss/to exempt
 KanjiVerb( 儲ける, JAP_TRANSITIVE ) // (v1,vt) to get/to earn/to gain/to have (bear, beget) a child/(P)
 KanjiVerb( 目掛ける, JAP_TRANSITIVE ) // (v1,vt) to aim at
 KanjiVerb( 目差す, JAP_TRANSITIVE ) // (v5s,vt) to aim at/to have an eye on
 KanjiVerb( 目指す, JAP_TRANSITIVE ) // (v5s,vt) to aim at/to have an eye on/(P)
 KanjiVerb( 目論む, JAP_TRANSITIVE ) // (v5m,vt) to plan/to form a plan/to scheme/to envision/to intend to do
 KanjiVerb( 戻す, JAP_TRANSITIVE ) // (v5s,vt) to restore/to put back/to return/(P)
 KanjiVerb( 貰う, JAP_TRANSITIVE ) // (v5u,vt) (1) (uk) to receive/to take/to accept/(2) to get somebody to do something (follows a verb in te form)/(P)
 KanjiVerb( 問いかける, JAP_TRANSITIVE ) // (v1,vt) to ask a question
 KanjiVerb( 問い掛ける, JAP_TRANSITIVE ) // (v1,vt) to ask a question
 KanjiVerb( 問い詰める, JAP_TRANSITIVE ) // (v1,vt) to press a question/to cross-examine
 KanjiVerb( 問い質す, JAP_TRANSITIVE ) // (v5s,vt) to enquire of someone about something (inquire)/to question
 KanjiVerb( 問い返す, JAP_TRANSITIVE ) // (v5s,vt) to ask again/to ask back
 KanjiVerb( 問う, JAP_TRANSITIVE ) // (v5u-s,vt) (1) to ask/to question/to inquire/(2) to charge (i.e. with a crime)/to accuse/(3) to care (about)/(4) without regard to (with negative verb)/(P)
 KanjiVerb( 役立てる, JAP_TRANSITIVE ) // (v1,vt) to put to use/to make use of/to turn to account
 KanjiVerb( 約める, JAP_TRANSITIVE ) // (v1,vt) to abridge/to shorten/to economize
 KanjiVerb( 癒す, JAP_TRANSITIVE ) // (v5s,vt) to heal/to cure
 KanjiVerb( 癒やす, JAP_TRANSITIVE ) // (v5s,vt) to heal/to cure
 KanjiVerb( 諭す, JAP_TRANSITIVE ) // (v5s,vt) to admonish/to persuade/to warn/to remonstrate/(P)
 KanjiVerb( 勇気付ける, JAP_TRANSITIVE ) // (v1,vt) to encourage/to cheer
 KanjiVerb( 宥める, JAP_TRANSITIVE ) // (v1,vt) (uk) to soothe/to calm/to pacify/(P)
 KanjiVerb( 宥め賺す, JAP_TRANSITIVE ) // (v5s,vt) to soothe and humor (humour)/to coax
 KanjiVerb( 憂える, JAP_TRANSITIVE ) // (v1,vt) to grieve/to lament/to be anxious/to be distressed/(P)
 KanjiVerb( 誘い込む, JAP_TRANSITIVE ) // (v5m,vt) to entice/to tempt/to invite someone to join in
 KanjiVerb( 誘い出す, JAP_TRANSITIVE ) // (v5s,vt) to lure/to invite out
 KanjiVerb( 誘う, JAP_TRANSITIVE ) // (v5u,vt) (1) to invite/to ask/to call (for)/(2) to tempt/to lure/to induce
 KanjiVerb( 誘き寄せる, JAP_TRANSITIVE ) // (v1,vt) to lure someone/to entice someone
 KanjiVerb( 誘き出す, JAP_TRANSITIVE ) // (v5s,vt) to lure out of/to decoy out of/to entice out of
 KanjiVerb( 誘き入れる, JAP_TRANSITIVE ) // (v1,vt) to lure/to entice
 KanjiVerb( 遊ばす, JAP_TRANSITIVE ) // (v5s,vt) to let one play/to leave idle/to do (polite)
 KanjiVerb( 遊び暮す, JAP_TRANSITIVE ) // (v5s,vt) to idle away one's time
 KanjiVerb( 遊び暮らす, JAP_TRANSITIVE ) // (v5s,vt) to idle away one's time
 KanjiVerb( 融かす, JAP_TRANSITIVE ) // (v5s,vt) (1) to comb out/(2) to melt
 KanjiVerb( 余す, JAP_TRANSITIVE ) // (v5s,vt) to save/to leave over/to spare/(P)
 KanjiVerb( 与える, JAP_TRANSITIVE ) // (v1,vt) (1) (comp) to give/to present/to award/(2) to pass (a variable to a function)/(P)
 KanjiVerb( 誉める, JAP_TRANSITIVE ) // (v1,vt) to praise/to admire/to speak well
 KanjiVerb( 誉め称える, JAP_TRANSITIVE ) // (v1,vt) to admire/to praise/to applaud
 KanjiVerb( 預ける, JAP_TRANSITIVE ) // (v1,vt) (1) to give into custody/to leave (a child) in the care of/to entrust/to deposit/(2) to lean on/to put one's weight on/(P)
 KanjiVerb( 預け入れる, JAP_TRANSITIVE ) // (v1,vt) to make a deposit/(P)
 KanjiVerb( 傭う, JAP_TRANSITIVE ) // (v5u,vt) to employ/to hire
 KanjiVerb( 容れる, JAP_TRANSITIVE ) // (v1,vt) (1) to put something in (e.g., into a container)/(2) to let somebody in (e.g., into a room)
 KanjiVerb( 揚げる, JAP_TRANSITIVE ) // (v1,vt) (1) (gen) to lift/to fly/(2) (food) to deep fry in hot oil/(P)
 KanjiVerb( 揺する, JAP_TRANSITIVE ) // (vs-s,vt) to shake/to jolt/to rock (cradle)/to swing/(P)
 KanjiVerb( 揺らす, JAP_TRANSITIVE ) // (v5s,vt) to rock/to shake/to swing
 KanjiVerb( 揺り動かす, JAP_TRANSITIVE ) // (v5s,vt) to shake/to wave/to swing/to sway
 KanjiVerb( 揺るがす, JAP_TRANSITIVE ) // (v5s,vt) to shake/to swing/to sway/to shock/(P)
 KanjiVerb( 溶かす, JAP_TRANSITIVE ) // (v5s,vt) to melt/to dissolve/(P)
 KanjiVerb( 溶く, JAP_TRANSITIVE ) // (v5k,vt) to dissolve (paint)/(P)
 KanjiVerb( 用いる, JAP_TRANSITIVE ) // (v1,vt) to use/to make use of/(P)
 KanjiVerb( 用立てる, JAP_TRANSITIVE ) // (v1,vt) to make use of/to lend money
 KanjiVerb( 謡う, JAP_TRANSITIVE ) // (v5u,vt) to sing/(P)
 KanjiVerb( 踊らす, JAP_TRANSITIVE ) // (v5s,vt) (1) to manipulate/(2) to let one dance
 KanjiVerb( 養う, JAP_TRANSITIVE ) // (v5u,vt) to rear/to maintain/to cultivate/(P)
 KanjiVerb( 抑える, JAP_TRANSITIVE ) // (v1,vt) to check/to curb/to suppress/to control/to arrest/(P)
 KanjiVerb( 抑え付ける, JAP_TRANSITIVE ) // (v1,vt) to press down/to hold down/to pin down/to repress
 KanjiVerb( 浴びせかける, JAP_TRANSITIVE ) // (v1,vt) to hurl abuse/to level insults
 KanjiVerb( 浴びせる, JAP_TRANSITIVE ) // (v1,vt) to pour on/(P)
 KanjiVerb( 浴びせ掛ける, JAP_TRANSITIVE ) // (v1,vt) to hurl abuse/to level insults
 KanjiVerb( 浴びる, JAP_TRANSITIVE ) // (v1,vt) to bathe/to bask in the sun/to shower/(P)
 KanjiVerb( 来す, JAP_TRANSITIVE ) // (v5s,vt) to cause/to induce/to bring about a result or state/to produce
 KanjiVerb( 来たす, JAP_TRANSITIVE ) // (v5s,vt) to cause/to induce/to bring about a result or state/to produce
 KanjiVerb( 頼み込む, JAP_TRANSITIVE ) // (v5m,vt) to request earnestly
 KanjiVerb( 絡める, JAP_TRANSITIVE ) // (v1,vt) (1) to arrest/(2) to entwine/to twine around/(3) to coordinate (with)
 KanjiVerb( 落ち着ける, JAP_TRANSITIVE ) // (v1,vt) to quiet/to calm down/to compose oneself
 KanjiVerb( 落とす, JAP_TRANSITIVE ) // (v5s,vt) to drop/to lose/to let fall/(P)
 KanjiVerb( 落籍す, JAP_TRANSITIVE ) // (v5s,vt) to redeem debts (e.g., of a geisha)
 KanjiVerb( 乱す, JAP_TRANSITIVE ) // (v5s,vt) to throw out of order/to disarrange/to disturb/(P)
 KanjiVerb( 利かせる, JAP_TRANSITIVE ) // (v1,vt) to be seasoned/to be enlivened/(P)
 KanjiVerb( 履き違える, JAP_TRANSITIVE ) // (v1,vt) to put on anothers shoes/to be mistaken
 KanjiVerb( 履く, JAP_TRANSITIVE ) // (v5k,vt) to wear/to put on (lower body, e.g., a sword)/(P)
 KanjiVerb( 裏付ける, JAP_TRANSITIVE ) // (v1,vt) to support/to endorse/to substantiate
 KanjiVerb( 裏返す, JAP_TRANSITIVE ) // (v5s,vt) to turn inside out/to turn the other way/to turn (something) over/(P)
 KanjiVerb( 離す, JAP_TRANSITIVE ) // (v5s,vt) to part/to divide/to separate/(P)
 KanjiVerb( 率いる, JAP_TRANSITIVE ) // (v1,vt) to lead/to spearhead (a group)/to command (troops)/(P)
 KanjiVerb( 立てかける, JAP_TRANSITIVE ) // (v1,vt) to lean against/to set against
 KanjiVerb( 立てる, JAP_TRANSITIVE ) // (v1,vt) to stand (something) up/to erect (something)/(P)
 KanjiVerb( 立て掛ける, JAP_TRANSITIVE ) // (v1,vt) to lean against/to set against
 KanjiVerb( 立て込める, JAP_TRANSITIVE ) // (v1,vt) to be shut tight
 KanjiVerb( 立て替える, JAP_TRANSITIVE ) // (v1,vt) to pay in advance/to pay for another/to pay someone else's debt as a loan to him/(P)
 KanjiVerb( 立て直す, JAP_TRANSITIVE ) // (v5s,vt) to rally/to make over/to rearrange/to reorganize/to reorganise/(P)
 KanjiVerb( 立て通す, JAP_TRANSITIVE ) // (v5s,vt) to push through (an idea)
 KanjiVerb( 立直す, JAP_TRANSITIVE ) // (v5s,vt) to rally/to make over/to rearrange/to reorganize/to reorganise
 KanjiVerb( 掠める, JAP_TRANSITIVE ) // (v1,vt) to rob/to pillage/to skim/to sweep over/to graze (in passing)/to cheat/to hint
 KanjiVerb( 流し込む, JAP_TRANSITIVE ) // (v5m,vt) to pour into/to wash down
 KanjiVerb( 流す, JAP_TRANSITIVE ) // (v5s,vt) to drain/to float/to shed (blood, tears)/to cruise (e.g., taxi)/(P)
 KanjiVerb( 溜める, JAP_TRANSITIVE ) // (v1,vt) to amass/to accumulate/(P)
 KanjiVerb( 溜め込む, JAP_TRANSITIVE ) // (v5m,vt) to save up
 KanjiVerb( 留める, JAP_TRANSITIVE ) // (v1,vt) to fasten/to turn off/to detain
 KanjiVerb( 留め置く, JAP_TRANSITIVE ) // (v5k,vt) to detain/to keep/to lock up/to retain/to leave (letter) till called for
 KanjiVerb( 了う, JAP_TRANSITIVE ) // (v5u,vt) (uk) to finish/to close/to do something completely/to put away/to put an end to
 KanjiVerb( 凌ぐ, JAP_TRANSITIVE ) // (v5g,vt) to outdo/to surpass/to endure/to keep out (rain)/to stave off/to tide over/to pull through/to defy/to slight/to excel/to eclipse/(P)
 KanjiVerb( 量り込む, JAP_TRANSITIVE ) // (v5m,vt) to measure liberally
 KanjiVerb( 力む, JAP_TRANSITIVE ) // (v5m,vt) to strain/to bear up/to exert one's strength/to swagger/to bluff/to boast/(P)
 KanjiVerb( 力付ける, JAP_TRANSITIVE ) // (v1,vt) to encourage (someone)/to cheer (someone) up
 KanjiVerb( 例える, JAP_TRANSITIVE ) // (v1,vt) to compare/to liken/to speak figuratively/to illustrate/to use a simile/(P)
 KanjiVerb( 冷ます, JAP_TRANSITIVE ) // (v5s,vt) to cool/to dampen/to let cool/to throw a damper on/to spoil/(P)
 KanjiVerb( 冷やす, JAP_TRANSITIVE ) // (v5s,vt) to cool/to refrigerate/(P)
 KanjiVerb( 励ます, JAP_TRANSITIVE ) // (v5s,vt) to encourage/to cheer/to raise (the voice)/(P)
 KanjiVerb( 零す, JAP_TRANSITIVE ) // (v5s,vt) to spill/(P)
 KanjiVerb( 裂く, JAP_TRANSITIVE ) // (v5k,vt) to tear/to split/(P)
 KanjiVerb( 恋い慕う, JAP_TRANSITIVE ) // (v5u,vt) to miss/to yearn for
 KanjiVerb( 恋う, JAP_TRANSITIVE ) // (v5u,vt) to be in love
 KanjiVerb( 恋慕う, JAP_TRANSITIVE ) // (v5u,vt) to miss/to yearn for
 KanjiVerb( 憐れむ, JAP_TRANSITIVE ) // (v5m,vt) to pity
 KanjiVerb( 練り固める, JAP_TRANSITIVE ) // (v1,vt) to harden by kneading
 KanjiVerb( 練り上げる, JAP_TRANSITIVE ) // (v1,vt) to train up/to discipline
 KanjiVerb( 練り直す, JAP_TRANSITIVE ) // (v5s,vt) to knead again/to work over
 KanjiVerb( 連ねる, JAP_TRANSITIVE ) // (v1,vt) to link/to join/to put together/(P)
 KanjiVerb( 連れ込む, JAP_TRANSITIVE ) // (v5m,vt) to bring (somebody into a place)
 KanjiVerb( 連れ出す, JAP_TRANSITIVE ) // (v5s,vt) to take out
 KanjiVerb( 労う, JAP_TRANSITIVE ) // (v5u,vt) (uk) to thank for/for reward for
 KanjiVerb( 弄ぶ, JAP_TRANSITIVE ) // (v5b,vt) to play with/to trifle with
 KanjiVerb( 漏らす, JAP_TRANSITIVE ) // (v5s,vt) to let leak/to reveal/(P)
 KanjiVerb( 漏れ聞く, JAP_TRANSITIVE ) // (v5k,vt) to overhear
 KanjiVerb( 論う, JAP_TRANSITIVE ) // (v5u,vt) (1) to discuss/(2) to find fault with/to criticize/to criticise
 KanjiVerb( 論じる, JAP_TRANSITIVE ) // (v1,vt) to argue/to discuss/to debate/(P)
 KanjiVerb( 論ずる, JAP_TRANSITIVE ) // (vz,vt) to argue/to discuss/to debate/(P)
 KanjiVerb( 和える, JAP_TRANSITIVE ) // (v1,vt) to dress vegetables (salad)
 KanjiVerb( 和らげる, JAP_TRANSITIVE ) // (v1,vt) to soften/to moderate/to relieve/(P)
 KanjiVerb( 話しかける, JAP_TRANSITIVE ) // (v1,vt) to accost a person/to talk (to someone)
 KanjiVerb( 話し掛ける, JAP_TRANSITIVE ) // (v1,vt) to accost a person/to talk (to someone)/(P)
 KanjiVerb( 話し合う, JAP_TRANSITIVE ) // (v5u,vt) to discuss/to talk together/(P)
 KanjiVerb( 話し込む, JAP_TRANSITIVE ) // (v5m,vt) to be deep in talk/(P)
 KanjiVerb( 話す, JAP_TRANSITIVE ) // (v5s,vt) to speak/(P)
 KanjiVerb( 話込む, JAP_TRANSITIVE ) // (v5m,vt) to be deep in talk/(P)
 KanjiVerb( 歪める, JAP_TRANSITIVE ) // (v1,vt) to bend/to curve/to warp/to distort
 KanjiVerb( 賄う, JAP_TRANSITIVE ) // (v5u,vt) to give board to/to provide meals/to pay/(P)
 KanjiVerb( 惑わす, JAP_TRANSITIVE ) // (v5s,vt) to bewilder/to perplex/to puzzle/(P)
 KanjiVerb( 仄めかす, JAP_TRANSITIVE ) // (v5s,vt) to hint at/to intimate/to suggest/to allude to/(P)
 KanjiVerb( 佩く, JAP_TRANSITIVE ) // (v5k,vt) to wear/to put on (lower body, e.g., a sword)
 KanjiVerb( 俯ける, JAP_TRANSITIVE ) // (v1,vt) to turn upside down/to turn (face) downward
 KanjiVerb( 俯せる, JAP_TRANSITIVE ) // (v1,vt) to lie face-down
 KanjiVerb( 俯向ける, JAP_TRANSITIVE ) // (v1,vt) to turn upside down/to turn (face) downward
 KanjiVerb( 傅く, JAP_TRANSITIVE ) // (v5k,vt) to wait upon/to serve
 KanjiVerb( 凭せかける, JAP_TRANSITIVE ) // (v1,vt) to lean against/to set against
 KanjiVerb( 凭せ掛ける, JAP_TRANSITIVE ) // (v1,vt) to lean against/to set against
 KanjiVerb( 刎ねる, JAP_TRANSITIVE ) // (v1,vt) (1) to reject/to deny/to refuse/(2) to eliminate/to exclude/to leave out/(3) to flip/to splash/to splatter/(4) to decapitate/to behead/(5) to hit (e.g., to have a car hit something or someone)/to run into/(6) to jump up
 KanjiVerb( 刮げる, JAP_TRANSITIVE ) // (v1,vt) to scrape off
 KanjiVerb( 刳り貫く, JAP_TRANSITIVE ) // (v5k,vt) to gouge out/to excavate/to bore/to drill
 KanjiVerb( 刳り抜く, JAP_TRANSITIVE ) // (v5k,vt) to gouge out/to excavate/to bore/to drill
 KanjiVerb( 剪む, JAP_TRANSITIVE ) // (v5m,vt) to clip/to snip
 KanjiVerb( 劈く, JAP_TRANSITIVE ) // (v5k,vt) to break/to tear/to pierce/to split/to burst
 KanjiVerb( 咥える, JAP_TRANSITIVE ) // (v1,vt) (uk) to hold in one's mouth
 KanjiVerb( 咬む, JAP_TRANSITIVE ) // (v5m,vt) to bite/to chew/to gnaw/(P)
 KanjiVerb( 喩える, JAP_TRANSITIVE ) // (v1,vt) to compare/to liken/to speak figuratively/to illustrate/to use a simile
 KanjiVerb( 嗅ぎつける, JAP_TRANSITIVE ) // (v1,vt) to sniff out/to get wind of
 KanjiVerb( 嗅ぎ出す, JAP_TRANSITIVE ) // (v5s,vt) to scent out/to detect
 KanjiVerb( 嗅ぎ当てる, JAP_TRANSITIVE ) // (v1,vt) to sniff out/to catch the scent of
 KanjiVerb( 嗅ぎ付ける, JAP_TRANSITIVE ) // (v1,vt) to sniff out/to get wind of
 KanjiVerb( 嗅ぎ分ける, JAP_TRANSITIVE ) // (v1,vt) to scent out/to discern
 KanjiVerb( 嗅ぐ, JAP_TRANSITIVE ) // (v5g,vt) to sniff/to smell/(P)
 KanjiVerb( 嗜む, JAP_TRANSITIVE ) // (v5m,vt) to have a taste for/to be fond of
 KanjiVerb( 嗾ける, JAP_TRANSITIVE ) // (v1,vt) (uk) to instigate/to incite/to spur on
 KanjiVerb( 嘲笑う, JAP_TRANSITIVE ) // (v5u,vt) (uk) to sneer at/to ridicule
 KanjiVerb( 囃す, JAP_TRANSITIVE ) // (v5s,vt) to play accompaniment/to jeer at
 KanjiVerb( 毀つ, JAP_TRANSITIVE ) // (v5t,vt) to destroy/to break/to damage
 KanjiVerb( 壅ぐ, JAP_TRANSITIVE ) // (v5g,vt) to stop up/to close up/to block (up)/to occupy/to fill up/to take up/to stand in another's way/to plug up/to shut up
 KanjiVerb( 嵌める, JAP_TRANSITIVE ) // (v1,vt) (1) (col) to get in/to insert/to put on/(2) to make love/(P)
 KanjiVerb( 怺える, JAP_TRANSITIVE ) // (v1,vi,vt) (1) to bear/to stand/to endure/to put up with
 KanjiVerb( 戛飛ばす, JAP_TRANSITIVE ) // (v5s,vt) to knock out (a homer)/to slam
 KanjiVerb( 截つ, JAP_TRANSITIVE ) // (v5t,vt) to sever/to cut off/to suppress/to abstain (from)
 KanjiVerb( 抉じ開ける, JAP_TRANSITIVE ) // (v1,vt) to wrench open/to prize open/to pick (lock)
 KanjiVerb( 拗らせる, JAP_TRANSITIVE ) // (v1,vt) to aggravate/to complicate/to make worse
 KanjiVerb( 抛つ, JAP_TRANSITIVE ) // (v5t,vt) to abandon/to fling away
 KanjiVerb( 拉ぐ, JAP_TRANSITIVE ) // (v5g,vt) to crush
 KanjiVerb( 拱く, JAP_TRANSITIVE ) // (v5k,vt) (1) to fold (one's) arms/(2) to stand by and do nothing/to look on passively
 KanjiVerb( 拱ねく, JAP_TRANSITIVE ) // (v5k,vt) (1) to fold (one's) arms/(2) to stand by and do nothing/to look on passively
 KanjiVerb( 拵える, JAP_TRANSITIVE ) // (v1,vt) to make/to manufacture/(P)
 KanjiVerb( 挾む, JAP_TRANSITIVE ) // (v5m,vt) to interpose/to hold between/to insert/(P)
 KanjiVerb( 捏ち上げる, JAP_TRANSITIVE ) // (v1,vt) (1) (uk) to fabricate/to invent/to make up (a story)/(2) to frame someone
 KanjiVerb( 捏っち上げる, JAP_TRANSITIVE ) // (v1,vt) (1) (uk) to fabricate/to invent/to make up (a story)/(2) to frame someone
 KanjiVerb( 捏ねる, JAP_TRANSITIVE ) // (v1,vt) to knead/to mix with fingers
 KanjiVerb( 捏ね回す, JAP_TRANSITIVE ) // (v5s,vt) to knead/to mix/to complicate/to turn into a mess
 KanjiVerb( 捏ね返す, JAP_TRANSITIVE ) // (v5s,vt) to knead/to mix/to complicate/to turn into a mess
 KanjiVerb( 捩じ開ける, JAP_TRANSITIVE ) // (v1,vt) to wrench open
 KanjiVerb( 捩じ曲げる, JAP_TRANSITIVE ) // (v1,vt) to twist/to distort
 KanjiVerb( 捩じ向ける, JAP_TRANSITIVE ) // (v1,vt) to twist
 KanjiVerb( 捩じ込む, JAP_TRANSITIVE ) // (v5m,vt) to screw in/to thrust into a container/to protest against (and demand compensation)
 KanjiVerb( 捩じ上げる, JAP_TRANSITIVE ) // (v1,vt) to twist hard
 KanjiVerb( 捩じ伏せる, JAP_TRANSITIVE ) // (v1,vt) to hold down/to twist one's arm
 KanjiVerb( 揉み合う, JAP_TRANSITIVE ) // (v5u,vt) to jostle/to shove and push/to struggle with one another
 KanjiVerb( 揉み出す, JAP_TRANSITIVE ) // (v5s,vt) to squeeze out/to begin to squeeze
 KanjiVerb( 揉み消す, JAP_TRANSITIVE ) // (v5s,vt) to crush/to hush up
 KanjiVerb( 揉む, JAP_TRANSITIVE ) // (v5m,vt) to rub/to crumple (up)/to wrinkle/to massage/to be troubled about/to worry over/to train/to coach/(P)
 KanjiVerb( 搦める, JAP_TRANSITIVE ) // (v1,vt) (1) to arrest/(2) to entwine/to twine around/(3) to coordinate (with)
 KanjiVerb( 撓む, JAP_TRANSITIVE ) // (v5m,vt) to bend/to warp
 KanjiVerb( 撥ねかす, JAP_TRANSITIVE ) // (v5s,vt) to splash/to splatter
 KanjiVerb( 撥ねつける, JAP_TRANSITIVE ) // (v1,vt) to repel/to spurn
 KanjiVerb( 撥ねる, JAP_TRANSITIVE ) // (v1,vt) (1) to reject/to deny/to refuse/(2) to eliminate/to exclude/to leave out/(3) to flip/to splash/to splatter/(4) to decapitate/to behead/(5) to hit (e.g., to have a car hit something or someone)/to run into/(6) to jump up/(P)
 KanjiVerb( 撥ね除ける, JAP_TRANSITIVE ) // (v1,vt) to push aside/to brush or thrust aside/to remove/to get rid of
 KanjiVerb( 撥ね上げる, JAP_TRANSITIVE ) // (v1,vt) to splash/to raise
 KanjiVerb( 撥ね飛ばす, JAP_TRANSITIVE ) // (v5s,vt) (1) to send (something) flying/to splatter/(2) to drive (something) off
 KanjiVerb( 撥ね付ける, JAP_TRANSITIVE ) // (v1,vt) to repel/to spurn
 KanjiVerb( 擡げる, JAP_TRANSITIVE ) // (v1,vt) to lift/to raise
 KanjiVerb( 攫う, JAP_TRANSITIVE ) // (v5u,vt) to carry off/to run away with/to kidnap/to abduct
 KanjiVerb( 暈す, JAP_TRANSITIVE ) // (v5s,vt) to shade off/to obscure/(P)
 KanjiVerb( 梳かす, JAP_TRANSITIVE ) // (v5s,vt) (1) to comb out/(2) to melt
 KanjiVerb( 梳く, JAP_TRANSITIVE ) // (v5k,vt) to comb (out)/to card
 KanjiVerb( 淹れる, JAP_TRANSITIVE ) // (v1,vt) (1) to put something in (e.g., into a container)/(2) to let somebody in (e.g., into a room)
 KanjiVerb( 涸らす, JAP_TRANSITIVE ) // (v5s,vt) to dry up/to exhaust
 KanjiVerb( 漱ぐ, JAP_TRANSITIVE ) // (v5g,vt) to rinse/to wash out
 KanjiVerb( 濾す, JAP_TRANSITIVE ) // (v5s,vt) to filter/to strain
 KanjiVerb( 炒める, JAP_TRANSITIVE ) // (v1,vt) to stir-fry/(P)
 KanjiVerb( 燻す, JAP_TRANSITIVE ) // (v5s,vt) (1) to smoke (something)/to fumigate/(2) to oxidize/to oxidise
 KanjiVerb( 燻り出す, JAP_TRANSITIVE ) // (v5s,vt) to smoke animal out of its den
 KanjiVerb( 爛らかす, JAP_TRANSITIVE ) // (v5s,vt) to cause to be inflamed
 KanjiVerb( 眇める, JAP_TRANSITIVE ) // (v1,vt) to scrutinize/to scrutinise
 KanjiVerb( 睨みつける, JAP_TRANSITIVE ) // (v1,vt) to glare at/to scowl at
 KanjiVerb( 睨み合せる, JAP_TRANSITIVE ) // (v1,vt) to weigh one thing against the other/to act in consideration of/to compare and take into consideration
 KanjiVerb( 睨み合わせる, JAP_TRANSITIVE ) // (v1,vt) to weigh one thing against the other/to act in consideration of/to compare and take into consideration
 KanjiVerb( 睨み付ける, JAP_TRANSITIVE ) // (v1,vt) to glare at/to scowl at
 KanjiVerb( 睨む, JAP_TRANSITIVE ) // (v5m,vt) to glare at/to scowl at/to keep an eye on/(P)
 KanjiVerb( 睨めつける, JAP_TRANSITIVE ) // (v1,vt) to glare at/to scowl at
 KanjiVerb( 睨め付ける, JAP_TRANSITIVE ) // (v1,vt) to glare at/to scowl at
 KanjiVerb( 祓い清める, JAP_TRANSITIVE ) // (v1,vt) to purify/to exorcise
 KanjiVerb( 穢す, JAP_TRANSITIVE ) // (v5s,vt) (1) to disgrace/to dishonour/to dishonor/(2) to pollute/to contaminate/to soil/to make dirty/to stain
 KanjiVerb( 窘める, JAP_TRANSITIVE ) // (v1,vt) (uk) to chide/to rebuke/to reprove
 KanjiVerb( 窶す, JAP_TRANSITIVE ) // (v5s,vt) (1) to be absorbed in/to lose oneself to/(2) to disguise oneself as
 KanjiVerb( 竦める, JAP_TRANSITIVE ) // (v1,vt) (uk) to shrug (shoulders)/to duck (head)/to draw back (body)
 KanjiVerb( 篩い分ける, JAP_TRANSITIVE ) // (v1,vt) to sift/to screen
 KanjiVerb( 籠める, JAP_TRANSITIVE ) // (v1,vt) to include/to put into
 KanjiVerb( 糺す, JAP_TRANSITIVE ) // (v5s,vt) to query/(P)
 KanjiVerb( 絎ける, JAP_TRANSITIVE ) // (v1,vt) to blindstitch
 KanjiVerb( 綯い交ぜる, JAP_TRANSITIVE ) // (v1,vt) (1) to mix/to include/(2) to entwine threads of various colours (colors)
 KanjiVerb( 縊り殺す, JAP_TRANSITIVE ) // (v5s,vt) to strangle to death
 KanjiVerb( 繙く, JAP_TRANSITIVE ) // (v5k,vi,vt) (1) to peruse (a book)/(2) to untie a scroll
 KanjiVerb( 翳す, JAP_TRANSITIVE ) // (v5s,vt) (1) to hold up over one's head/to hold aloft/(2) to hold one's hands out (e.g., towards a fire)/(3) to shade one's eyes, face, etc.
 KanjiVerb( 舐める, JAP_TRANSITIVE ) // (v1,vt) to lick/to taste/to experience/to make fun of/to make light of/to put down/to treat with contempt/(P)
 KanjiVerb( 茹でる, JAP_TRANSITIVE ) // (v1,vt) to boil/(P)
 KanjiVerb( 蠢かす, JAP_TRANSITIVE ) // (v5s,vt) to wriggle
 KanjiVerb( 衒う, JAP_TRANSITIVE ) // (v5u,vt) to show off/to parade/to pretend
 KanjiVerb( 訝しむ, JAP_TRANSITIVE ) // (v5m,vt) to doubt
 KanjiVerb( 誂える, JAP_TRANSITIVE ) // (v1,vt) (uk) to give an order/to place an order
 KanjiVerb( 誑かす, JAP_TRANSITIVE ) // (v5s,vt) to trick/to cheat/to deceive
 KanjiVerb( 誑し込む, JAP_TRANSITIVE ) // (v5m,vt) to cajole/to deceive/to seduce
 KanjiVerb( 誣いる, JAP_TRANSITIVE ) // (v1,vt) to slander/to accuse falsely
 KanjiVerb( 諫める, JAP_TRANSITIVE ) // (v1,vt) to remonstrate/to warn not to do something
 KanjiVerb( 謳う, JAP_TRANSITIVE ) // (v5u,vt) to express/to state/to insist/to stipulate/(P)
 KanjiVerb( 譬える, JAP_TRANSITIVE ) // (v1,vt) to compare/to liken/to speak figuratively/to illustrate/to use a simile
 KanjiVerb( 貶す, JAP_TRANSITIVE ) // (v5s,vt) (uk) to speak ill of/(P)
 KanjiVerb( 貶なす, JAP_TRANSITIVE ) // (v5s,vt) (uk) to speak ill of
 KanjiVerb( 貶める, JAP_TRANSITIVE ) // (v1,vt) to show contempt for/to look down upon/to have a low opinion of
 KanjiVerb( 贖う, JAP_TRANSITIVE ) // (v5u,vt) to compensate/to make up for
 KanjiVerb( 躱す, JAP_TRANSITIVE ) // (v5s,vt) to dodge/to evade/to avoid/to sidestep
 KanjiVerb( 轢き殺す, JAP_TRANSITIVE ) // (v5s,vt) to kill by running over
 KanjiVerb( 轢く, JAP_TRANSITIVE ) // (v5k,vt) to run somebody over (with vehicle)/to knock someone down/(P)
 KanjiVerb( 辷らす, JAP_TRANSITIVE ) // (v5s,vt) to let something slip/to slide/to glide
 KanjiVerb( 鉗む, JAP_TRANSITIVE ) // (v5m,vt) to shut one's mouth
 KanjiVerb( 銜える, JAP_TRANSITIVE ) // (v1,vt) (uk) to hold in one's mouth/(P)
 KanjiVerb( 鋏む, JAP_TRANSITIVE ) // (v5m,vt) to cut off
 KanjiVerb( 鏤める, JAP_TRANSITIVE ) // (v1,vt) (uk) to inlay/to set/to stud/to enchase (a thing) with/to mount (gem)
 KanjiVerb( 韲える, JAP_TRANSITIVE ) // (v1,vt) to dress vegetables (salad)
 KanjiVerb( 顰める, JAP_TRANSITIVE ) // (v1,vt) (uk) to knit the brows/to raise eyebrows/to scowl/to grimace/to frown
 KanjiVerb( 騙し込む, JAP_TRANSITIVE ) // (v5m,vt) to deceive/to ensnare
 KanjiVerb( 騙す, JAP_TRANSITIVE ) // (v5s,vt) to trick/to cheat/to deceive/(P)
 KanjiVerb( 靡かす, JAP_TRANSITIVE ) // (v5s,vt) to seduce/to win over/to conquer
 KanjiVerb( あいた口も塞がらぬ ) // (v5n) to be surprising/to be shocking/to be jaw-dropping
 KanjiVerb( あか抜ける ) // (v1) to refine
 KanjiVerb( あっと言わせる ) // (v1) to startle
 KanjiVerb( あり得る ) // (v5uru,vi) to be possible/to be likely/to be probable
 KanjiVerb( いがみ合う ) // (v5u,vi) to snarl/to quarrel
 KanjiVerb( いきり立つ ) // (v5t,vi) to get angry/to lose one's temper
 KanjiVerb( いじり回す ) // (v5s) to tinker with/to twist up
 KanjiVerb( うまく行く ) // (v5k-s) to go smoothly/to turn out well/to do the trick/to have peaceful relations
 KanjiVerb( おぞけ立つ ) // (v5t,vi) to be horrified/to be filled with trepidation
 KanjiVerb( お聞きいただく ) // (v5k) to ask (politely)
 KanjiVerb( お聞き頂く ) // (v5k) to ask (politely)
 KanjiVerb( かき交ぜる ) // (v1) to mix/to stir/to scramble/to churn
 KanjiVerb( かき混ぜる ) // (v1) to mix/to stir/to scramble/to churn
 KanjiVerb( かけ直す ) // (v5s) to call again/to call someone back
 KanjiVerb( かけ離む ) // (v5m,vi) to rush in (at the last minute)/to stampede
 KanjiVerb( かけ離れる ) // (v1,vi) to be very far apart from/to be remote/to be quite different from
 KanjiVerb( かち合う ) // (v5u,vi) to clash/to be in conflict with
 KanjiVerb( かなぐり捨てる ) // (v1) to fling off/to throw off/to throw to the winds
 KanjiVerb( からみ合う ) // (v5u,vi) to be(come) intertwined/to be entangled
 KanjiVerb( くぐり抜ける ) // (v1,vi) to go through/to pass through/to escape (through the cordon)/to evade (the law)
 KanjiVerb( くっ付く ) // (v5k) (uk) to adhere to/to keep close to/(P)
 KanjiVerb( くっ付ける ) // (v1) to attach/(P)
 KanjiVerb( くんくん鳴く ) // (v5k) to whine (dog)
 KanjiVerb( けた上げる ) // (v1) (comp) to carry (of digit, bit, etc.)
 KanjiVerb( けり込む ) // (v5m) to kick in
 KanjiVerb( けり殺す ) // (v5s) to kick to death
 KanjiVerb( げらげら笑う ) // (v5u) to guffaw
 KanjiVerb( げんを担ぐ ) // (v5g) to be superstitious
 KanjiVerb( こぼれ落ちる ) // (v1,vi) to spill over and fall/to scatter (petals, leaves, etc.)
 KanjiVerb( こみ上げる ) // (v1,vi) (1) to feel nauseous/(2) to fill (one's heart)/to experience a welling up of feelings or sensations
 KanjiVerb( ごった返す ) // (v5s,vi) to be in confusion or commotion/to be in a turmoil/to be crowded or jammed with people
 KanjiVerb( ご座る ) // (v5aru,vi) (pol) to be
 KanjiVerb( ご座居る ) // (v1) to be (very pol.)
 KanjiVerb( さ迷う ) // (v5u,vi) to loiter/to putter/to prowl/to wander about/to roam about/to knock around
 KanjiVerb( しがみ付く ) // (v5k) (uk) to cling
 KanjiVerb( しくしく泣く ) // (v5k) to sob/to weep
 KanjiVerb( しゃがみ込む ) // (v5m,vi) (uk) to squat
 KanjiVerb( し吹く ) // (v5k,vi) to splash/to spray
 KanjiVerb( じっと見る ) // (v1) to watch steadily
 KanjiVerb( じろじろ見る ) // (v1) to stare at/to look hard at/to look up and down/to scrutinize/to scrutinise
 KanjiVerb( すすり泣く ) // (v5k) to sob
 KanjiVerb( すっ飛ぶ ) // (v5b,vi) to rush off/to rush away/to vanish
 KanjiVerb( すり抜ける ) // (v1,vi) to slip through/to make one's way through quickly
 KanjiVerb( すれ違う ) // (v5u,vi) to pass by one another/to disagree/to miss each other
 KanjiVerb( ずばずば言う ) // (v5u) to speak one's mind/to speak very frankly
 KanjiVerb( ずば抜ける ) // (v1,vi) to tower above the rest/to be by far the best/to be prominent
 KanjiVerb( ずれ込む ) // (v5m,vi) to drag on/to be delayed
 KanjiVerb( そっくり返る ) // (v1,vi) to throw one's chest out/to hold one's head high
 KanjiVerb( たくし上げる ) // (v1) to roll up or pull up (sleeves, skirt, etc)
 KanjiVerb( ちゅうちゅう吸う ) // (v5u) to suck
 KanjiVerb( ちゅうちゅう鳴く ) // (v5k) to squeak/to chirp/to twitter
 KanjiVerb( つけ始める ) // (v1) to begin to light (a cigarette)
 KanjiVerb( つなぎ合わせる ) // (v1) to connect/to join
 KanjiVerb( でご座る ) // (v5aru) (pol) to be
 KanjiVerb( で御座る ) // (v5aru) (pol) to be
 KanjiVerb( とやかく言う ) // (v5u) to say all kinds of things/to complain/to find fault (with)
 KanjiVerb( どなり立てる ) // (v1) to stand and shout
 KanjiVerb( にじみ出る ) // (v1,vi) to exude/to ooze/to seep out
 KanjiVerb( のめり込む ) // (v5m,vi) to be completely absorbed in/to fall for (something)
 KanjiVerb( はち切れる ) // (v1,vi) to be filled to bursting/to burst
 KanjiVerb( はまり込む ) // (v5m) (1) to get stuck in/to be mired in/(2) to be addicted to
 KanjiVerb( はみ出す ) // (v5s,vi) (1) to be forced out/be crowded out/(2) to jut out (of bounds)
 KanjiVerb( はみ出る ) // (v1,vi) (1) to jut out (of bounds)/(2) to be crowded out/to to be forced out
 KanjiVerb( はめ倒す ) // (v5s) (col) to make love
 KanjiVerb( はり合わせる ) // (v1) to paste together
 KanjiVerb( ひしめき合う ) // (v5u) to crowd together in a confined space/to gather and make a commotion
 KanjiVerb( ひれ伏す ) // (v5s,vi) to prostrate oneself before
 KanjiVerb( びんびん来る ) // (vk) to get an erection (US: hard-on)
 KanjiVerb( ぴくぴく動く ) // (v5k) to jerk/to wiggle/to twitch
 KanjiVerb( ぴよぴよ鳴く ) // (v5k) to peep/to cheep
 KanjiVerb( ぴんと来る ) // (vk) to get (a joke or explanation)/to strike home/to know intuitively
 KanjiVerb( ふさぎ込む ) // (v5m,vi) to mope
 KanjiVerb( ふて腐れる ) // (v1,vi) (uk) to become sulky/to become irresponsible
 KanjiVerb( ふるいに掛ける ) // (v1) (uk) to sieve/to sift
 KanjiVerb( ふるい落とす ) // (v5s) to sift out/to screen or eliminate (candidates)
 KanjiVerb( ぶり返す ) // (v5s,vi) to come back/to return/to recur
 KanjiVerb( へばり付く ) // (v5k) to cling to
 KanjiVerb( べた付く ) // (v5k,vi) to be sticky
 KanjiVerb( べろべろ嘗める ) // (v1) (uk) to lick up with one's tongue
 KanjiVerb( べろべろ舐める ) // (v1) (uk) to lick up with one's tongue
 KanjiVerb( ほくそ笑む ) // (v5k,vi) to chuckle/to snicker
 KanjiVerb( ほそぼそ話す ) // (v5s) to speak slowly and quietly
 KanjiVerb( ぼりぼり食べる ) // (v1) to eat with a munching or crunching sound
 KanjiVerb( ぽたぽた落ちる ) // (v1) to fall in drops/to drip down/to trickle down
 KanjiVerb( まくり上げる ) // (v1) to tuck (e.g., sleeves)
 KanjiVerb( まじまじと見る ) // (v1) to take a long hard look at something
 KanjiVerb( めり込む ) // (v5m,vi) to sink into/to cave in
 KanjiVerb( もんどり打つ ) // (v5t) to turn a somersault
 KanjiVerb( やって来る ) // (vk) to come along/to come around/to turn up/(P)
 KanjiVerb( ゆり落とす ) // (v5s) to shake down (e.g., nuts from a tree)
 KanjiVerb( チクチク痛む ) // (v5m) to prickle
 KanjiVerb( チューチュー鳴く ) // (v5k) to squeak/to chirp/to twitter
 KanjiVerb( ピントが外れる ) // (v1) to be out of focus/to be off the point/to be queer in the head
 KanjiVerb( ブチ壊す ) // (v5s) to break by striking/(P)
 KanjiVerb( ブチ殺す ) // (v5s) to kill by hitting
 KanjiVerb( 阿娜めく ) // (v5k) to be bewitching/to look coquettish
 KanjiVerb( 愛し合う ) // (v5u) to love one another
 KanjiVerb( 愛する ) // (vs-s) to love/(P)
 KanjiVerb( 愛に飢える ) // (v1) to hunger (starve) for love
 KanjiVerb( 逢う ) // (v5u,vi) to meet (with drama or pathos)/(P)
 KanjiVerb( 悪く言う ) // (v5u) to deprecate/to traduce
 KanjiVerb( 悪たれる ) // (v1,vi) to do mischief/to use abusive language
 KanjiVerb( 悪びれる ) // (v1,vi) to be timid/to be shy
 KanjiVerb( 悪怯れる ) // (v1,vi) to be timid/to be shy
 KanjiVerb( 悪擦る ) // (v1) to get worse and worse
 KanjiVerb( 圧し合う ) // (v5u,vi) to jostle/to push
 KanjiVerb( 圧する ) // (vs-s) to press/to oppress/to dominate/to overwhelm
 KanjiVerb( 扱き落とす ) // (v5s) to thresh
 KanjiVerb( 粟立つ ) // (v5t,vi) to have gooseflesh (cold or horror)
 KanjiVerb( 安く上げる ) // (v1) to make it less expensive
 KanjiVerb( 安く付く ) // (v5k) to come cheaper
 KanjiVerb( 安らう ) // (v5u) to rest/to relax
 KanjiVerb( 安らぐ ) // (v5g,vi) to feel at ease/(P)
 KanjiVerb( 安んじる ) // (v1,vi) to be contented/to be at ease
 KanjiVerb( 以てする ) // (vs-s) to do by the use of
 KanjiVerb( 位する ) // (vs-s) to rank/to be ranked/to be located
 KanjiVerb( 威張り散らす ) // (v5s) to domineer
 KanjiVerb( 意気込む ) // (v5m,vi) to be enthusiastic about/(P)
 KanjiVerb( 慰む ) // (v5m,vi) to be diverted/to forget one's worries/to comfort
 KanjiVerb( 易より難へ進む ) // (v5m) to proceed from the easy to the difficult
 KanjiVerb( 為過ぎる ) // (v1) to overdo/to do too much
 KanjiVerb( 為初める ) // (v1) to begin to do
 KanjiVerb( 為続ける ) // (v1) to continue to do/to persist in doing
 KanjiVerb( 為損なう ) // (v5u) to blunder/to fail/to make a mistake/to miss
 KanjiVerb( 畏れる ) // (v1,vi) to fear/to be afraid of
 KanjiVerb( 移し替える ) // (v1) to shift (move) (an object) to (into)
 KanjiVerb( 移り行く ) // (v5k-s,vi) to change/to shift/to come and go
 KanjiVerb( 移ろう ) // (v5u,vi) to change/to fade
 KanjiVerb( 萎える ) // (v1,vi) to wither/to droop/to be lame
 KanjiVerb( 萎びる ) // (v1,vi) to wilt/to fade
 KanjiVerb( 萎む ) // (v5m,vi) to wither/to fade (away)/to shrivel/to wilt/(P)
 KanjiVerb( 萎れる ) // (v1,vi) to wither/(P)
 KanjiVerb( 違う ) // (v5u,vi) to differ (from)/(P)
 KanjiVerb( 育ち過ぎる ) // (v1) to be overgrown
 KanjiVerb( 育ち行く ) // (v5k-s) to grow up
 KanjiVerb( 育つ ) // (v5t,vi) to be raised (e.g., child)/to be brought up/to grow (up)/(P)
 KanjiVerb( 一応聞いて置く ) // (v5k) to hear someone out anyway
 KanjiVerb( 一旗揚げる ) // (v1) to make a name for oneself
 KanjiVerb( 一気に飲む ) // (v5m) to drink in one gulp
 KanjiVerb( 一句詠む ) // (v5m) to make up a haiku poem
 KanjiVerb( 一口喰う ) // (v5u) to have a munch/to take a bite
 KanjiVerb( 一口食べる ) // (v1) to eat a mouthful
 KanjiVerb( 一札入れる ) // (v1) to give a signed statement or an IOU
 KanjiVerb( 一山当てる ) // (v1) to be right on target/to strike it rich
 KanjiVerb( 一字空ける ) // (v1) to leave a space (between words)
 KanjiVerb( 一節歌う ) // (v5u) to sing a tune
 KanjiVerb( 一段落付ける ) // (v1) to complete the first stage of/to settle for the time being
 KanjiVerb( 一杯食わされる ) // (v1) to be taken in/to be duped/to be deceived
 KanjiVerb( 一杯食わす ) // (v5s) to play a trick on
 KanjiVerb( 一肌脱ぐ ) // (v5g) to pitch in and help
 KanjiVerb( 一発かます ) // (v5s) (sl) to hit someone
 KanjiVerb( 一発抜く ) // (v5k) to ejaculate
 KanjiVerb( 一発放つ ) // (v5t) to break wind/to have a shot
 KanjiVerb( 一筆書く ) // (v5k) to drop a few lines
 KanjiVerb( 一服飲む ) // (v5m) to have a smoke
 KanjiVerb( 一歩退く ) // (v5k) to take a step backward
 KanjiVerb( 一泡吹かせる ) // (v1) to give a surprise (or blow)/to scare the hell out of
 KanjiVerb( 一目置く ) // (v5k) to take off one's hat to a person/to acknowledge anothers superiority/to give a piece or stone
 KanjiVerb( 一役買う ) // (v5u) to take on a role/to take part
 KanjiVerb( 溢れる ) // (v1,vi) to flood/to overflow/to brim over/(P)
 KanjiVerb( 溢れ出る ) // (v1) to overflow from something full
 KanjiVerb( 逸する ) // (vs-s) to lose (a chance)/to miss (a chance)/to deviate/to forget
 KanjiVerb( 逸れる ) // (v1,vi) to stray (turn) from subject/to get lost/to go astray/(P)
 KanjiVerb( 咽せる ) // (v1,vi) to choke over/to be choked by
 KanjiVerb( 咽び泣く ) // (v5k,vi) to sob/to be choked with tears
 KanjiVerb( 咽ぶ ) // (v5b,vi) to be choked/to be stifled/to be smothered
 KanjiVerb( 因む ) // (v5m,vi) to be associated (with)/to be connected (with)
 KanjiVerb( 引かれる ) // (v1) to be charmed by
 KanjiVerb( 引きつける ) // (v1) (1) to fascinate/to attract/to pull up (at a gate)/(2) to have a convulsion
 KanjiVerb( 引き越す ) // (v5s,vi) to move (house)/to change residence
 KanjiVerb( 引き換える ) // (v1) to exchange/to convert
 KanjiVerb( 引き合う ) // (v5u,vi) to pay/to be profitable
 KanjiVerb( 引き続く ) // (v5k,vi) to continue (for a long time)/to occur in succession
 KanjiVerb( 引き付ける ) // (v1) (1) to fascinate/to attract/to pull up (at a gate)/(2) to have a convulsion/(P)
 KanjiVerb( 引き立つ ) // (v5t) (1) to become active/(2) to look better
 KanjiVerb( 引ける ) // (v1,vi) to close/to be over/to break up (e.g., school)
 KanjiVerb( 引っ越す ) // (v5s,vi) to move (house)/to change residence/(P)
 KanjiVerb( 引っ括るめる ) // (v1) to lump together
 KanjiVerb( 引っ込む ) // (v5m,vi) to draw back/to sink/to cave in/(P)
 KanjiVerb( 引っ張たく ) // (v5k) to slap/to strike
 KanjiVerb( 引っ張り上げる ) // (v1) to pull up/to haul up
 KanjiVerb( 引っ付く ) // (v5k) to stick to/to flirt with/(P)
 KanjiVerb( 引っ捕らえる ) // (v1) to arrest/to capture/to seize
 KanjiVerb( 引ん剥く ) // (v5k) to strip/to peel
 KanjiVerb( 引越す ) // (v5s,vi) to move (house)/to change residence
 KanjiVerb( 引合う ) // (v5u,vi) to pay/to be profitable
 KanjiVerb( 引続く ) // (v5k,vi) to continue (for a long time)/to occur in succession
 KanjiVerb( 引付ける ) // (v1) (1) to fascinate/to attract/to pull up (at a gate)/(2) to have a convulsion/(P)
 KanjiVerb( 引付る ) // (v1) (1) to fascinate/to attract/to pull up (at a gate)/(2) to have a convulsion
 KanjiVerb( 引立つ ) // (v5t) (1) to become active/(2) to look better
 KanjiVerb( 飲ませる ) // (v1) to make somebody drink/to give someone a drink
 KanjiVerb( 飲み過ぎる ) // (v1) to drink too much
 KanjiVerb( 飲み潰れる ) // (v1,vi) to drink oneself drunk
 KanjiVerb( 飲める ) // (v1) to drink much/to be good to drink
 KanjiVerb( 飲んだくれる ) // (v1) to get dead drunk
 KanjiVerb( 陰で動く ) // (v5k) to act behind the scenes
 KanjiVerb( 隠し持つ ) // (v5t) to carry (something) under cover
 KanjiVerb( 隠れる ) // (v1,vi) to hide/to be hidden/to conceal oneself/to disappear/(P)
 KanjiVerb( 隠れ伏す ) // (v5s) to lie concealed
 KanjiVerb( 羽ばたく ) // (v5k,vi) to flap (wings)
 KanjiVerb( 羽撃く ) // (v5k,vi) to flap (wings)/(P)
 KanjiVerb( 渦巻く ) // (v5k,vi) to whirl/to eddy/to swirl/to curl (smoke)
 KanjiVerb( 嘘で固める ) // (v1) to fabricate a web of lies
 KanjiVerb( 云う ) // (v5u) to say
 KanjiVerb( 運び出す ) // (v5s) to carry out
 KanjiVerb( 運び上げる ) // (v1) to carry or bring (up)
 KanjiVerb( 運び入れる ) // (v1) to carry or bring in(to)
 KanjiVerb( 運ぶ ) // (v5b) to transport/(P)
 KanjiVerb( 運命づける ) // (v1) to preordain
 KanjiVerb( 運命付ける ) // (v1) to preordain
 KanjiVerb( 雲突く ) // (v5k) to tower
 KanjiVerb( 餌付く ) // (v5k,vi) to begin to eat or feed
 KanjiVerb( 映える ) // (v1,vi) to shine/to look attractive/to look pretty/(P)
 KanjiVerb( 栄える ) // (v1,vi) to shine/to look attractive/to look pretty/(P)
 KanjiVerb( 永らえる ) // (v1,vi) to have a long life/to live a long time
 KanjiVerb( 泳がせる ) // (v1) to let someone swim/to let someone go free
 KanjiVerb( 泳ぎ出す ) // (v5s) to strike out/to start swimming
 KanjiVerb( 泳ぐ ) // (v5g,vi) to swim/(P)
 KanjiVerb( 洩れる ) // (v1,vi) to leak out/to escape/to come through/to shine through/to filter out/to be omitted
 KanjiVerb( 駅迄歩く ) // (v5k) to walk to the station
 KanjiVerb( 悦ぶ ) // (v5b,vi) to be delighted/to be glad
 KanjiVerb( 謁する ) // (vs-s) to have an audience with
 KanjiVerb( 越える ) // (v1,vi) (1) to cross over/to cross/to pass through/to pass over (out of)/(2) to exceed/(P)
 KanjiVerb( 越す ) // (v5s) (1) to cross over (e.g., mountain)/to go across/(2) to go over (e.g., with audience)/(3) to pass (time, e.g., a winter)/(4) to surpass/to be better than/(5) to move house/(P)
 KanjiVerb( 厭きる ) // (v1,vi) to get tired of/to lose interest in/to have enough
 KanjiVerb( 厭む ) // (v5m,vi) to get tired of (doing)/to lose interest in
 KanjiVerb( 円で囲む ) // (v5m) to enclose (a word) with a circle
 KanjiVerb( 延びる ) // (v1,vi) (1) to stretch/to extend/to lengthen/to spread/(v1,vi) (2) to make progress/to grow (beard, body height)/(v1,vi) (3) to grow stale (soba)/(v1,vi) (4) to be straightened/to be flattened/to be smoothed/(v1,vi) (5) to be exhausted/(v1,vi) (6) to be postponed/to be prolonged/(P)
 KanjiVerb( 沿う ) // (v5u) to run along/to follow/(P)
 KanjiVerb( 演劇付く ) // (v5k) to be absorbed in a play
 KanjiVerb( 縁付く ) // (v5k,vi) to marry
 KanjiVerb( 艶めく ) // (v5k,vi) to be charming/to be beautiful
 KanjiVerb( 遠のく ) // (v5k,vi) to become distant/to recede
 KanjiVerb( 遠過ぎる ) // (v1) to be too far
 KanjiVerb( 遠退く ) // (v5k,vi) to become distant/to recede
 KanjiVerb( 汚れる ) // (v1,vi) to get dirty/to become dirty/(P)
 KanjiVerb( 凹ませる ) // (v1) to dent/to indent/to depress/to humiliate
 KanjiVerb( 凹む ) // (v5m) to be dented/to be indented/to yield to/to give/to sink/to collapse/to cave in/to be snubbed/(P)
 KanjiVerb( 応える ) // (v1,vi) to respond/to answer/to strike home/to take its toll/to reward/(P)
 KanjiVerb( 応じる ) // (v1,vi) to respond/to satisfy/to accept/to comply with/to apply for/(P)
 KanjiVerb( 応ずる ) // (vz,vi) to answer/to respond/to meet/to satisfy/to accept/(P)
 KanjiVerb( 押しかける ) // (v1,vi) to intrude on
 KanjiVerb( 押し開ける ) // (v1) to force open/to push open
 KanjiVerb( 押し掛ける ) // (v1,vi) to intrude on
 KanjiVerb( 押し寄せる ) // (v1,vi) to push aside/to advance on
 KanjiVerb( 押し詰める ) // (v1) to pack (in box)/to drive to wall
 KanjiVerb( 押し固める ) // (v1) to press together
 KanjiVerb( 押し広げる ) // (v1) to extend/to expand/to spread out
 KanjiVerb( 押し合う ) // (v5u,vi) to jostle/to crowd/to haggle
 KanjiVerb( 押し込む ) // (v5m) to push into/to crowd into/(P)
 KanjiVerb( 押っ始める ) // (v1) to begin
 KanjiVerb( 押開ける ) // (v1) to force open/to push open
 KanjiVerb( 押掛ける ) // (v1,vi) to intrude on
 KanjiVerb( 押寄せる ) // (v1,vi) to push aside/to advance on
 KanjiVerb( 押合う ) // (v5u,vi) to jostle/to crowd/to haggle
 KanjiVerb( 横向く ) // (v5k) to turn sideways
 KanjiVerb( 殴り合う ) // (v5u) to fight/to exchange blows
 KanjiVerb( 殴り殺す ) // (v5s) to strike dead/to beat to death
 KanjiVerb( 殴り倒す ) // (v5s) to knock down
 KanjiVerb( 黄ばむ ) // (v5m,vi) to turn yellow
 KanjiVerb( 臆する ) // (vs-s) to fear/to feel timid
 KanjiVerb( 温む ) // (v5m) to cool off/to become tepid
 KanjiVerb( 音を立てる ) // (v1) to make a sound
 KanjiVerb( 下さる ) // (v5aru) (hon) to give/to confer/(P)
 KanjiVerb( 下りる ) // (v1,vi) to alight (e.g., from bus)/to get off/to descend (e.g., a mountain)/(P)
 KanjiVerb( 下り立つ ) // (v5t,vi) (1) to go down and stand/(2) to alight/to get down
 KanjiVerb( 下押す ) // (v5s) to decline (stock market)
 KanjiVerb( 下駄を預ける ) // (v1) to leave everything to (someone)
 KanjiVerb( 下卑る ) // (v1) to become vulgar/to coarsen
 KanjiVerb( 化ける ) // (v1,vi) to change with age/to spoil from weathering
 KanjiVerb( 化す ) // (v5s,vi) to change into/to convert to/to transform/to be reduced/to influence/to improve (someone)
 KanjiVerb( 化する ) // (vs-s,suf) to change into/to convert into/to transform/to be reduced/to influence/to improve (someone)
 KanjiVerb( 価する ) // (vs-s) to be worth/to deserve/to merit
 KanjiVerb( 嫁ぐ ) // (v5g,vi) to marry/(P)
 KanjiVerb( 科する ) // (vs-s) to inflict/to impose (a fine, etc.)/(P)
 KanjiVerb( 果せる ) // (v1,vi) to succeed in doing
 KanjiVerb( 果たす ) // (v5s) to accomplish/to fulfill/to carry out/to achieve/(P)
 KanjiVerb( 果てる ) // (v1,vi) to end/to be finished/to be exhausted/to die/to perish/(P)
 KanjiVerb( 歌い合う ) // (v5u) to sing responsively
 KanjiVerb( 火が付く ) // (v5k) to catch fire/to provoke/to catch fire from/to be ignited
 KanjiVerb( 火で溶ける ) // (v1) to melt in the fire
 KanjiVerb( 稼ぐ ) // (v5g,vi) to earn income/to labor/to labour/(P)
 KanjiVerb( 稼げる ) // (v1) to work/to earn income
 KanjiVerb( 花やぐ ) // (v5g,vi) to become brilliant
 KanjiVerb( 花咲く ) // (v5k) to bloom
 KanjiVerb( 苛つく ) // (v5k,vi) (uk) to get irritated
 KanjiVerb( 苛立つ ) // (v5t) to be irritated
 KanjiVerb( 荷物を詰める ) // (v1) to pack one's things
 KanjiVerb( 華やぐ ) // (v5g,vi) to become brilliant
 KanjiVerb( 課する ) // (vs-s) to impose/(P)
 KanjiVerb( 過ぎる ) // (v1,vi) to pass/to go beyond/to elapse/to exceed/(P)
 KanjiVerb( 過ぎ行く ) // (v5k-s,vi) to pass/to go pass
 KanjiVerb( 過つ ) // (v5t,vi) to err
 KanjiVerb( 過行く ) // (v5k-s,vi) to pass/to go pass
 KanjiVerb( 霞む ) // (v5m,vi) to grow hazy/to be misty/(P)
 KanjiVerb( 我を立てる ) // (v1) to insist on one's own ideas
 KanjiVerb( 我意を得る ) // (v1) to approve of
 KanjiVerb( 画する ) // (vs-s) to draw/to demarcate/to mark/to divide/to map out/(P)
 KanjiVerb( 臥し転ぶ ) // (v5b,vi) to fall and roll over/wriggle about
 KanjiVerb( 臥す ) // (v5s,vi) to bend down/to bow down/to lie prostrate
 KanjiVerb( 芽ぐむ ) // (v5m,vi) to bud/to sprout
 KanjiVerb( 芽吹く ) // (v5k,vi) to bud
 KanjiVerb( 芽生える ) // (v1,vi) to bud/to sprout
 KanjiVerb( 餓える ) // (v1,vi) to be hungry/to starve/to thirst
 KanjiVerb( 介する ) // (vs-s) to worry/to mind/to care
 KanjiVerb( 会う ) // (v5u,vi) to meet/to interview/(P)
 KanjiVerb( 会する ) // (vs-s) (1) to meet/to assemble/(2) to mediate
 KanjiVerb( 解ける ) // (v1,vi) to come untied/to come apart/(P)
 KanjiVerb( 解け込む ) // (v5m,vi) to melt into
 KanjiVerb( 解ごす ) // (v5s) to unfasten
 KanjiVerb( 解する ) // (vs-s) (1) to interpret/(2) to understand/to appreciate
 KanjiVerb( 解れる ) // (v1,vi) to become frayed/to become loose
 KanjiVerb( 解合う ) // (v5u,vi) to come to a mutual understanding/to cancel mutually
 KanjiVerb( 回り出す ) // (v5s) to begin to turn
 KanjiVerb( 壊れる ) // (v1,vi) to be broken/to break/(P)
 KanjiVerb( 悔む ) // (v5m) to repent/to regret/to mourn
 KanjiVerb( 開けっ放す ) // (v5s) to leave open
 KanjiVerb( 外で遊ぶ ) // (v5b) to play outdoors
 KanjiVerb( 外れる ) // (v1,vi) to be disconnected/to get out of place/to be off/to be out (e.g., of gear)/(P)
 KanjiVerb( 咳き込む ) // (v5m,vi) to cough violently
 KanjiVerb( 咳き上げる ) // (v1,vi) to have a coughing fit/to sob convulsively
 KanjiVerb( 咳く ) // (v5k,vi) to cough
 KanjiVerb( 害する ) // (vs-s) to injure/to damage/to harm/to kill/to hinder/(P)
 KanjiVerb( 獲る ) // (v1) to get/to obtain/to gain/to acquire/to win/to catch
 KanjiVerb( 覚える ) // (v1,vi) (1) to remember/to recollect/to memorize/to memorise/(2) to feel/(P)
 KanjiVerb( 覚める ) // (v1,vi) to wake/to wake up/(P)
 KanjiVerb( 角目立つ ) // (v5t,vi) to be sharp/to be rough
 KanjiVerb( 角立つ ) // (v5t) to be sharp/to be rough
 KanjiVerb( 学ぶ ) // (v5b) to study (in depth)/to learn/to take lessons in/(P)
 KanjiVerb( 楽しむ ) // (v5m) to enjoy oneself/(P)
 KanjiVerb( 楽しめる ) // (v1) to be able to enjoy
 KanjiVerb( 額突く ) // (v5k) to make a deep bow
 KanjiVerb( 掛かり合う ) // (v5u) to have dealings with/to be involved in
 KanjiVerb( 掛け違う ) // (v5u) to cross paths/to conflict
 KanjiVerb( 掛け合う ) // (v5u,vi) to negotiate with/to talk over with
 KanjiVerb( 掛け合わす ) // (v5s) to multiply/to cross breed
 KanjiVerb( 掛け合わせる ) // (v1) to negotiate/to multiply/to cross breed
 KanjiVerb( 掛け直す ) // (v5s) to call again/to call someone back
 KanjiVerb( 掛け離れる ) // (v1,vi) to be very far apart from/to be remote/to be quite different from
 KanjiVerb( 掛合う ) // (v5u,vi) to negotiate with/to talk over with
 KanjiVerb( 掛離れる ) // (v1,vi) to be very far apart from/to be remote/to be quite different from
 KanjiVerb( 割ける ) // (v1) to be separated/to be divided
 KanjiVerb( 割りで払う ) // (v5u) to split the account
 KanjiVerb( 割り解す ) // (v5s) to beat (e.g., egg)/to whip (e.g., cream)
 KanjiVerb( 割り切れる ) // (v1,vi) to be divisible (by)/to be divided without residue
 KanjiVerb( 割れる ) // (v1,vi) to break/to split/to cleave/to fissure/to be smashed/to crack/to be torn/(P)
 KanjiVerb( 割解す ) // (v5s) to beat (e.g., egg)/to whip (e.g., cream)
 KanjiVerb( 恰好付ける ) // (v1) to affect a stylish air
 KanjiVerb( 括れる ) // (v1,vi) to be constricted
 KanjiVerb( 活きる ) // (v1,vi) to live/to exist
 KanjiVerb( 活気付く ) // (v5k) to become animated/to liven up/to become active
 KanjiVerb( 渇く ) // (v5k,vi) to be thirsty/(P)
 KanjiVerb( 渇する ) // (vs-s) to be thirsty/to be dry
 KanjiVerb( 滑り下りる ) // (v1) to slide down/to slip down
 KanjiVerb( 滑り降りる ) // (v1) to slide down (a hill) (e.g., ski, toboggan)
 KanjiVerb( 滑り込む ) // (v5m,vi) to slide into (base)/to slip into (ditch)
 KanjiVerb( 滑り出す ) // (v5s) to begin slipping or sliding/to make a start upon
 KanjiVerb( 滑り落ちる ) // (v1) to slip off
 KanjiVerb( 且つ飲み且つ歌う ) // (v5u) to drink and sing at the same time/to drink as well as sing
 KanjiVerb( 叶う ) // (v5u) to come true (wish)/(P)
 KanjiVerb( 噛み合う ) // (v5u,vi) (1) to gear (engage) with/to be in gear (mesh)/(2) to bite each other
 KanjiVerb( 噛み合わせる ) // (v1) (1) to clench (teeth)/to engage (gears)/(2) to set to fighting
 KanjiVerb( 噛り付く ) // (v5k,vi) to bite into/to stick to
 KanjiVerb( 噛合う ) // (v5u,vi) (1) to gear (engage) with/to be in gear (mesh)/(2) to bite each other
 KanjiVerb( 噛合わせる ) // (v1) (1) to clench (teeth)/to engage (gears)/(2) to set to fighting
 KanjiVerb( 乾く ) // (v5k,vi) to get dry/(P)
 KanjiVerb( 乾せる ) // (v1) to dry up/to scab/to slough/to be poisoned (with lacquer)
 KanjiVerb( 乾びる ) // (v1,vi) to dry up/to shrivel
 KanjiVerb( 乾枯らびる ) // (v1,vi) to dry up completely/to become stale
 KanjiVerb( 乾涸びる ) // (v1,vi) to dry up completely/to become stale
 KanjiVerb( 冠を曲げる ) // (v1) to become displeased/to get stubborn
 KanjiVerb( 勘づく ) // (v5k,vi) (uk) to suspect/to sense (danger)/to scent
 KanjiVerb( 勘付く ) // (v5k,vi) (uk) to suspect/to sense (danger)/to scent
 KanjiVerb( 巻き起こす ) // (v5s) to create (a sensation)/to give rise to (controversy)
 KanjiVerb( 巻き付く ) // (v5k) to twine around
 KanjiVerb( 巻く ) // (v5k) to wind/to coil/to roll/(P)
 KanjiVerb( 巻付く ) // (v5k) to twine around
 KanjiVerb( 喚き立てる ) // (v1) to yell/to bawl out
 KanjiVerb( 喚く ) // (v5k,vi) (uk) to shout/to cry/to scream/to clamour/(P)
 KanjiVerb( 堪えかねる ) // (v1,vi) to be unable to endure/to lose patience
 KanjiVerb( 堪え兼ねる ) // (v1,vi) to be unable to endure/to lose patience
 KanjiVerb( 堪り兼ねる ) // (v1,vi) be unable to bear (something) any longer/to be unable to put up with (something) any longer
 KanjiVerb( 姦する ) // (vs-s) to commit adultery/to rape
 KanjiVerb( 寛ぐ ) // (v5g) (uk) to relax/to feel at home/(P)
 KanjiVerb( 干からびる ) // (v1,vi) to dry up completely/to become stale
 KanjiVerb( 干る ) // (v1,vi) to dry/(P)
 KanjiVerb( 干涸びる ) // (v1,vi) to dry up completely/to become stale
 KanjiVerb( 患う ) // (v5u,vi) to fall ill/(P)
 KanjiVerb( 感じる ) // (v1,vi) to feel/to sense/to experience/(P)
 KanjiVerb( 感ずる ) // (vz,vi) to feel/to sense/(P)
 KanjiVerb( 感づく ) // (v5k,vi) (uk) to apprehend/to get an inkling (of something)/to smell (danger)
 KanjiVerb( 感付く ) // (v5k,vi) (uk) to apprehend/to get an inkling (of something)/to smell (danger)
 KanjiVerb( 慣れる ) // (v1,vi) to grow accustomed to/to become domesticated/to become tame/to get too familiar with/(P)
 KanjiVerb( 慣れ親しむ ) // (v5m) to become familiar with/to get used to
 KanjiVerb( 汗ばむ ) // (v5m,vi) to be sweaty
 KanjiVerb( 汗染みる ) // (v1,vi) to be sweat-stained
 KanjiVerb( 甘える ) // (v1,vi) (1) to behave like a spoiled child/to behave like a spoilt child/to fawn on/(2) to depend and presume upon another's benevolence/(P)
 KanjiVerb( 甘く見る ) // (v1) to not take seriously/to take lightly
 KanjiVerb( 甘んじる ) // (v1,vi) to content oneself with/to be resigned to (one's fate)/to be contented (satisfied) with (one's lot)
 KanjiVerb( 緩む ) // (v5m) to become loose/to slacken/(P)
 KanjiVerb( 肝胆相照らす ) // (v5s) to be profoundly compatible/to be inseparable
 KanjiVerb( 間に合う ) // (v5u) (1) to be in time for/(2) to serve (suit, meet) the purpose/to be good enough/to be enough/(P)
 KanjiVerb( 間に合わせる ) // (v1) to make do/to manage (with something)/to make shift/(P)
 KanjiVerb( 間違う ) // (v5u) to make a mistake/to be incorrect/to be mistaken/(P)
 KanjiVerb( 関する ) // (vs-s) to concern/to be related/(P)
 KanjiVerb( 関係つける ) // (v1) to relate
 KanjiVerb( 含ます ) // (v5s) to soak/to saturate/to suckle/to make one hold something in the mouth/to include/to instruct/to make one understand
 KanjiVerb( 含まれる ) // (v1,vi) to be included/to be comprised of
 KanjiVerb( 含む ) // (v5m) (1) to contain/to comprise/to have/to hold/to include/to embrace/(2) to hold in the mouth/(3) to bear in mind/to understand/(4) to harbor/to harbour/(P)
 KanjiVerb( 含羞む ) // (v5m) (uk) to be shy/to be bashful
 KanjiVerb( 眼をたれる ) // (v1) to stare menacingly
 KanjiVerb( 顔から火が出る ) // (v1) to be extremely embarrassed/to burn with shame
 KanjiVerb( 顔をしかめる ) // (v1) to grimace/to frown
 KanjiVerb( 顔を合わせる ) // (v1) to meet/to face someone
 KanjiVerb( 顔を立てる ) // (v1) to save face
 KanjiVerb( 願い求める ) // (v1) to entreat
 KanjiVerb( 危ぶむ ) // (v5m) to fear/to have misgivings/to be doubtful/to mistrust/(P)
 KanjiVerb( 喜ばす ) // (v5s) to delight/to give pleasure/(P)
 KanjiVerb( 喜び勇む ) // (v5m,vi) to be in high spirits
 KanjiVerb( 喜ぶ ) // (v5b,vi) to be delighted/to be glad/(P)
 KanjiVerb( 喜歌う ) // (v5u) to rejoice and sing
 KanjiVerb( 基づく ) // (v5k,vi) to be grounded on/to be based on/to be due to/to originate from/(P)
 KanjiVerb( 基付く ) // (v5k,vi) to be grounded on/to be based on/to be due to/to originate from
 KanjiVerb( 寄す ) // (v5s) (arch) to bring near/to put close/to let come near
 KanjiVerb( 寄せかける ) // (v1,vi) to rest or lean against
 KanjiVerb( 寄せ掛ける ) // (v1,vi) to rest or lean against
 KanjiVerb( 寄り合う ) // (v5u,vi) to gather/to meet
 KanjiVerb( 寄り添う ) // (v5u,vi) to get close/to cuddle close together/to nestle close to/to snuggle up to
 KanjiVerb( 寄り付く ) // (v5k,vi) to approach
 KanjiVerb( 寄合う ) // (v5u,vi) to gather/to meet
 KanjiVerb( 寄添う ) // (v5u,vi) to get close/to cuddle close together/to nestle close to/to snuggle up to
 KanjiVerb( 寄付く ) // (v5k,vi) to approach
 KanjiVerb( 忌む ) // (v5m,vi) to detest
 KanjiVerb( 揮う ) // (v5u) to exert
 KanjiVerb( 期す ) // (v5s) to expect/to look forward to
 KanjiVerb( 期する ) // (vs-s) to expect/to look forward to
 KanjiVerb( 帰する ) // (vs-s) to return to/to come to/to be attributed to
 KanjiVerb( 帰って来る ) // (vk) to return/to come back
 KanjiVerb( 帰り着く ) // (v5k,vi) to arrive home/to return
 KanjiVerb( 帰れる ) // (v1) to get out/to go home
 KanjiVerb( 気がつく ) // (v5k) (1) to notice/to become aware/to perceive/to realize/to realise/(2) to recover consciousness/to come to oneself
 KanjiVerb( 気が引ける ) // (v1) to feel awkward/to feel shy
 KanjiVerb( 気が付く ) // (v5k) (1) to notice/to become aware/to perceive/to realize/to realise/(2) to recover consciousness/to come to oneself
 KanjiVerb( 気づかう ) // (v5u,vi) to worry about/to feel anxious about/to have apprehensions of
 KanjiVerb( 気づく ) // (v5k) to notice/to recognize/to recognise/to become aware of/to perceive/to realize/to realise
 KanjiVerb( 気を取られる ) // (v1) to have one's attention attracted (caught)/to be preoccupied with
 KanjiVerb( 気圧される ) // (v1,vi) to be overawed (overpowered)
 KanjiVerb( 気違いじみる ) // (v1,vi) to go mad
 KanjiVerb( 気違い染みる ) // (v1,vi) to go mad
 KanjiVerb( 気狂いじみる ) // (v1,vi) to go mad
 KanjiVerb( 気狂い染みる ) // (v1,vi) to go mad
 KanjiVerb( 気遣う ) // (v5u,vi) to worry about/to feel anxious about/to have apprehensions of
 KanjiVerb( 気色ばむ ) // (v5m,vi) to grow angry/to display one's anger
 KanjiVerb( 気触れる ) // (v1,vi) to react to/to be influenced by/to go overboard for
 KanjiVerb( 気付く ) // (v5k) to notice/to recognize/to recognise/to become aware of/to perceive/to realize/to realise/(P)
 KanjiVerb( 気負い立つ ) // (v5t) to rouse oneself/to psyche oneself up
 KanjiVerb( 気負う ) // (v5u,vi) to get worked up/to be eager (enthusiastic)/to rouse oneself
 KanjiVerb( 記す ) // (v5s) to note/to write down/(P)
 KanjiVerb( 記号で表す ) // (v5s) to represent by signs
 KanjiVerb( 起きる ) // (v1,vi) (1) to get up/to rise/(2) to wake up/(3) to occur/to happen/to take place/(P)
 KanjiVerb( 起こりうる ) // (v5uru) to be possible to occur
 KanjiVerb( 起こり得る ) // (v5uru) to be possible to occur
 KanjiVerb( 起つ ) // (v5t,vi) to rise up/to initiate (political) action
 KanjiVerb( 輝く ) // (v5k) to shine/to glitter/to sparkle/(P)
 KanjiVerb( 飢える ) // (v1,vi) to be starved/to be hungry
 KanjiVerb( 偽り誓う ) // (v5u) to swear falsely
 KanjiVerb( 戯える ) // (v1,vi) to play pranks/to be spoiled/to be spoilt
 KanjiVerb( 戯ける ) // (v1,vi) to jest/to joke/to play the fool/to act indecently/to be silly over/to talk foolishly
 KanjiVerb( 戯れる ) // (v1,vi) (1) to be playful/to gambol/to be amused (with something)/to play/to sport/to frolic/to joke/(2) to flirt with/(P)
 KanjiVerb( 戯交わす ) // (v5s) to exchange jokes
 KanjiVerb( 欺き惑わす ) // (v5s) to deceive and lead astray
 KanjiVerb( 義務づける ) // (v1) to obligate
 KanjiVerb( 掬い出す ) // (v5s) to bail (water out of a boat)
 KanjiVerb( 喫する ) // (vs-s) to take/to drink/to suffer (e.g., defeat)/to receive a blow/(P)
 KanjiVerb( 詰まらせる ) // (v1) to make shorter/(P)
 KanjiVerb( 詰む ) // (v5m) to become fine/(P)
 KanjiVerb( 詰めかける ) // (v1,vi) to crowd (a house)/to throng to (a door)
 KanjiVerb( 詰める ) // (v1) (1) to pack/to fill/(2) to shorten/(3) to work out (details)/(P)
 KanjiVerb( 詰め掛ける ) // (v1,vi) to crowd (a house)/to throng to (a door)
 KanjiVerb( 詰掛ける ) // (v1,vi) to crowd (a house)/to throng to (a door)
 KanjiVerb( 逆らう ) // (v5u,vi) to go against/to oppose/to disobey/to defy/(P)
 KanjiVerb( 逆巻く ) // (v5k,vi) surging water or waves
 KanjiVerb( 逆上せる ) // (v1,vi) to feel dizzy/to have blood rush to one's head/to become conceited/(P)
 KanjiVerb( 逆立つ ) // (v5t) to stand up/to oppose
 KanjiVerb( 休ませる ) // (v1) to excuse (someone)/to give a holiday to/to make (someone) rest
 KanjiVerb( 休む ) // (v5m,vi) to rest/to have a break/to take a day off/to be finished/to be absent/to retire/to sleep/(P)
 KanjiVerb( 休らう ) // (v5u) to rest/to relax
 KanjiVerb( 及ぶ ) // (v5b,vi) to reach/to come up to/to amount to/to befall/to happen to/to extend/to match/to equal/(P)
 KanjiVerb( 吸い付く ) // (v5k) to stick to
 KanjiVerb( 吸付く ) // (v5k) to stick to
 KanjiVerb( 急かす ) // (v5s) to hurry/to urge on/(P)
 KanjiVerb( 急がせる ) // (v1) to hasten (the work)/to urge (a person) on
 KanjiVerb( 急きたてられる ) // (v1) to be hurried/to be hastened/to be hard pressed
 KanjiVerb( 急き込む ) // (v5m,vi) to sound agitated, hurried, flustered/to be impatient
 KanjiVerb( 急ぐ ) // (v5g,vi) to hurry/to rush/(P)
 KanjiVerb( 急込む ) // (v5m,vi) to sound agitated, hurried, flustered/to be impatient
 KanjiVerb( 救い上げる ) // (v1) to pick up and rescue
 KanjiVerb( 朽ちる ) // (v1,vi) to rot
 KanjiVerb( 朽ち果てる ) // (v1,vi) to rust away/to rot away/to decay/to fall to ruins/to die in obscurity
 KanjiVerb( 泣かす ) // (v5s) (1) to make someone cry/to move someone to tears/(2) to grieve
 KanjiVerb( 泣きつく ) // (v5k,vi) to cling to .. in tears/to beg .. in tears/to appeal/to throw oneself on someone's mercy
 KanjiVerb( 泣き喚く ) // (v5k) to cry/to scream
 KanjiVerb( 泣き叫ぶ ) // (v5b,vi) to cry and shout/to scream
 KanjiVerb( 泣き止む ) // (v5m) to stop crying/to cry oneself out
 KanjiVerb( 泣き出す ) // (v5s,vi) to burst into tears/to burst out crying/to begin to cry/to be moved to tears
 KanjiVerb( 泣き沈む ) // (v5m,vi) to abandon oneself to grief
 KanjiVerb( 泣き通す ) // (v5s) to keep crying
 KanjiVerb( 泣き潰す ) // (v5s) to cry one's eyes out/to weep oneself blind
 KanjiVerb( 泣き濡れる ) // (v1,vi) to be tear-stained
 KanjiVerb( 泣き付く ) // (v5k,vi) to cling to .. in tears/to beg .. in tears/to appeal/to throw oneself on someone's mercy
 KanjiVerb( 泣き伏す ) // (v5s,vi) to break down crying
 KanjiVerb( 泣き崩れる ) // (v1,vi) to break down crying
 KanjiVerb( 泣き落とす ) // (v5s) to persuade by tears/to use tears to get one's way
 KanjiVerb( 泣く ) // (v5k) to cry/to weep/to sob/to howl/(P)
 KanjiVerb( 泣ける ) // (v1,vi) to shed tears/to be moved to tears
 KanjiVerb( 泣喚く ) // (v5k) to cry/to scream
 KanjiVerb( 泣叫ぶ ) // (v5b,vi) to cry and shout/to scream
 KanjiVerb( 泣出す ) // (v5s,vi) to burst into tears/to burst out crying/to begin to cry/to be moved to tears
 KanjiVerb( 泣沈む ) // (v5m,vi) to abandon oneself to grief
 KanjiVerb( 泣潰す ) // (v5s) to cry one's eyes out/to weep oneself blind
 KanjiVerb( 泣付く ) // (v5k,vi) to cling to .. in tears/to beg .. in tears/to appeal/to throw oneself on someone's mercy
 KanjiVerb( 泣伏す ) // (v5s,vi) to break down crying
 KanjiVerb( 泣崩れる ) // (v1,vi) to break down crying
 KanjiVerb( 泣落とす ) // (v5s) to persuade by tears/to use tears to get one's way
 KanjiVerb( 窮する ) // (vs-s) (1) (arch) to be hard pressed/to be at a loss/(2) to become poor/to be reduced to poverty
 KanjiVerb( 糾う ) // (v5u) to twist (something)
 KanjiVerb( 給う ) // (v5u) to receive/to grant
 KanjiVerb( 居合わせる ) // (v1) to happen to be present/(P)
 KanjiVerb( 居続ける ) // (v1) to stay on (e.g., at one's friends house)/to remain in the same neighborhood
 KanjiVerb( 居着く ) // (v5k,vi) to settle down
 KanjiVerb( 居並ぶ ) // (v5b,vi) to sit in a row/to be arrayed
 KanjiVerb( 挙げられる ) // (v1) (comp) to be arrested/to be caught/to be captured (e.g. data)
 KanjiVerb( 虚ける ) // (v1,vi) (1) to become empty (hollow)/(2) to relax from a tense situation into a vacant or absent minded state
 KanjiVerb( 虚しく ) // (v5k) in vain/to no purpose/fruitlessly
 KanjiVerb( 競い合う ) // (v5u) to compete with/to vie for
 KanjiVerb( 競う ) // (v5u,vi) to emulate/to compete with/(P)
 KanjiVerb( 競り合う ) // (v5u,vi) to struggle for/to compete with/to vie with/(P)
 KanjiVerb( 競り勝つ ) // (v5t,vi) to win after tough bidding
 KanjiVerb( 競り落とす ) // (v5s) to knock down the price of
 KanjiVerb( 競勝つ ) // (v5t,vi) to win after tough bidding
 KanjiVerb( 叫く ) // (v5k,vi) (uk) to shout/to cry/to scream/to clamour
 KanjiVerb( 叫び出す ) // (v5s) to let out a cry/to break forth
 KanjiVerb( 叫ぶ ) // (v5b,vi) to shout/to cry/(P)
 KanjiVerb( 怯える ) // (v1,vi) to become frightened/to have a nightmare
 KanjiVerb( 怯む ) // (v5m,vi) (uk) to falter/to flinch (from)/to recoil (from)/to quail (at)
 KanjiVerb( 恐れる ) // (v1,vi) to fear/to be afraid of/(P)
 KanjiVerb( 恐れ戦く ) // (v5k) to tremble with fear
 KanjiVerb( 教え諭す ) // (v5s) to give guidance
 KanjiVerb( 狂い咲く ) // (v5k) to bloom out of season
 KanjiVerb( 狂う ) // (v5u,vi) to go mad/to get out of order/(P)
 KanjiVerb( 狂わす ) // (v5s) to drive mad/to put out of order/(P)
 KanjiVerb( 矯め直す ) // (v5s) to set up again/to correct/to cure
 KanjiVerb( 脅える ) // (v1,vi) to become frightened/to have a nightmare
 KanjiVerb( 脅しつける ) // (v1) to threaten/to terrify/to frighten
 KanjiVerb( 脅し付ける ) // (v1) to threaten/to terrify/to frighten
 KanjiVerb( 興じる ) // (v1,vi) to amuse oneself/to make merry
 KanjiVerb( 興ずる ) // (vz,vi) to amuse oneself/to make merry
 KanjiVerb( 興醒める ) // (v1,vi) to lose interest
 KanjiVerb( 響く ) // (v5k,vi) to resound/(P)
 KanjiVerb( 響めく ) // (v5k) to resound/to make a stir/(P)
 KanjiVerb( 饗する ) // (vs-s) to treat/to feast/to provide dinner for
 KanjiVerb( 驚かされる ) // (v1) to be surprised/(P)
 KanjiVerb( 驚く ) // (v5k,vi) to be surprised/to be astonished/(P)
 KanjiVerb( 仰せられる ) // (v1) (pol) to say/to state
 KanjiVerb( 仰のく ) // (v5k) to look up
 KanjiVerb( 仰むく ) // (v5k) to look upward
 KanjiVerb( 仰向く ) // (v5k) to look upward
 KanjiVerb( 極め尽くす ) // (v5s) to do thoroughly/to check through and through
 KanjiVerb( 極力努める ) // (v1) to do one's best
 KanjiVerb( 極力勉める ) // (v1) to do one's best
 KanjiVerb( 勤め行なう ) // (v5u) to carry on (work)
 KanjiVerb( 勤め働く ) // (v5k) to work diligently
 KanjiVerb( 近づく ) // (v5k) to approach/to get near/to get acquainted with/to get closer
 KanjiVerb( 近付く ) // (v5k) to approach/to get near/to get acquainted with/to get closer/(P)
 KanjiVerb( 苦しむ ) // (v5m,vi) to suffer/to groan/to be worried/(P)
 KanjiVerb( 苦労し抜く ) // (v5k) to go through all sorts of hardships
 KanjiVerb( 駆けつける ) // (v1,vi) to run to/to come running/to rush (someplace)/to hasten/(P)
 KanjiVerb( 駆ける ) // (v1,vi) to run (race, esp. horse)/to gallop/to canter/(P)
 KanjiVerb( 駆け下りる ) // (v1) to run down
 KanjiVerb( 駆け込む ) // (v5m,vi) to rush in (at the last minute)/to stampede
 KanjiVerb( 駆け出す ) // (v5s,vi) to run off/to break into a run/to start running
 KanjiVerb( 駆け抜ける ) // (v1,vi) to run past from behind/to run through (e.g., gate)
 KanjiVerb( 駆け付ける ) // (v1,vi) to run to/to come running/to rush (someplace)/to hasten
 KanjiVerb( 駆下りる ) // (v1) to run down
 KanjiVerb( 駆込む ) // (v5m,vi) to rush in (at the last minute)/to stampede
 KanjiVerb( 駆出す ) // (v5s,vi) to run off/to break into a run/to start running
 KanjiVerb( 駆抜ける ) // (v1,vi) to run past from behind/to run through (e.g., gate)
 KanjiVerb( 駆付ける ) // (v1,vi) to run to/to come running/to rush (someplace)/to hasten
 KanjiVerb( 駈ける ) // (v1,vi) to run/to gallop/to advance
 KanjiVerb( 駈け出す ) // (v5s,vi) to run off/to break into a run/to start running
 KanjiVerb( 駈出す ) // (v5s,vi) to run off/to break into a run/to start running
 KanjiVerb( 具する ) // (vs-s) to possess/to accompany
 KanjiVerb( 愚図つく ) // (v5k) to dawdle/to fret/to sulk/to complain/to waste time doing nothing in particular
 KanjiVerb( 愚図付く ) // (v5k) to dawdle/to fret/to sulk/to complain/to waste time doing nothing in particular
 KanjiVerb( 空く ) // (v5k,vi) (1) to open/to become open/to become empty/(v5k,vi) (2) to be less crowded/(P)
 KanjiVerb( 空ける ) // (v1,vi) (1) to become empty (hollow)/(2) to relax from a tense situation into a vacant or absent minded state
 KanjiVerb( 空惚ける ) // (v1,vi) to feign ignorance
 KanjiVerb( 空飛ぶ ) // (v5b) to fly in the sky
 KanjiVerb( 空嘯く ) // (v5k,vi) to feign ignorance or unconcern
 KanjiVerb( 遇う ) // (v5u,vi) to meet/to encounter
 KanjiVerb( 遇する ) // (vs-s) to entertain/to treat
 KanjiVerb( 屈する ) // (vs-s) to yield/to bend/to be daunted/to shrink
 KanjiVerb( 屈み込む ) // (v5m,vi) to lean over/to lean in
 KanjiVerb( 屈む ) // (v5m) to stoop/to lean over
 KanjiVerb( 窪む ) // (v5m) to cave in/to sink
 KanjiVerb( 繰り拡げる ) // (v1) to unfold/to roll out/to develop/to spread out
 KanjiVerb( 繰り合わす ) // (v5s) to make time/to arrange matters
 KanjiVerb( 繰り合わせる ) // (v1) to arrange/to manage (to find time)
 KanjiVerb( 繰り返す ) // (v5s,vi) to repeat/to do something over again/(P)
 KanjiVerb( 繰拡げる ) // (v1) to unfold/to roll out/to develop/to spread out
 KanjiVerb( 繰合わす ) // (v5s) to make time/to arrange matters
 KanjiVerb( 繰合わせる ) // (v1) to arrange/to manage (to find time)
 KanjiVerb( 繰返す ) // (v5s,vi) to repeat/to do something over again
 KanjiVerb( 群れる ) // (v1,vi) to crowd/to flock/to swarm/(P)
 KanjiVerb( 群れ遊ぶ ) // (v5b) to play in a group
 KanjiVerb( 群居る ) // (v1,vi) to crowd in/to come together
 KanjiVerb( 係う ) // (v5u) (1) (uk) to be mixed up with/to have a connection with (a troublesome matter)/(2) to be a stickler about/to be finicky about (some triviality)/(3) to take part (in some work)/to hang about/to bother (someone)
 KanjiVerb( 係わり合う ) // (v5u) to get involved or entangled in/to get mixed up in/to have something to do with/to have dealings with
 KanjiVerb( 傾ぐ ) // (v5g,vi) to lean/to incline/to tilt/to list/to tip/to careen/to lurch/to incline toward/to slant/to heed over/to be disposed to/to trend toward/to be prone to/to go down (sun)/to wane/to sink/to decline
 KanjiVerb( 傾け倒す ) // (v5s) to cast down/to lay low
 KanjiVerb( 傾れる ) // (v1,vi) to slope/to descend/to slide (snow, etc.)
 KanjiVerb( 傾れ込む ) // (v5m,vi) to rush or crowd into/to surge into
 KanjiVerb( 傾れ落ちる ) // (v1) to slide down (snow, etc.)
 KanjiVerb( 啓く ) // (v5k) (arch) to enlighten/to edify
 KanjiVerb( 型に嵌める ) // (v1) to stereotype/to squeeze into a pattern/to regiment
 KanjiVerb( 恵まれる ) // (v1,vi) to be blessed with/to be rich in/(P)
 KanjiVerb( 慶ぶ ) // (v5b,vi) to be delighted/to be glad
 KanjiVerb( 憩う ) // (v5u) to rest/to relax/to repose/(P)
 KanjiVerb( 敬する ) // (vs-s) to respect
 KanjiVerb( 経つ ) // (v5t,vi) to pass/to lapse/(P)
 KanjiVerb( 経る ) // (v1,vi) to pass/to elapse/to experience/(P)
 KanjiVerb( 繋ぎ合わせる ) // (v1) to join or tie or knot together
 KanjiVerb( 計られる ) // (v1) to be taken in
 KanjiVerb( 撃たれる ) // (v1,vi) to be struck/to be beaten
 KanjiVerb( 撃ち当てる ) // (v1) to hit (e.g., target)
 KanjiVerb( 撃ち抜く ) // (v5k) to shoot out (lights, window, etc.)
 KanjiVerb( 撃ち払う ) // (v5u) to drive someone off with gunfire
 KanjiVerb( 撃つ ) // (v5t) to attack/to defeat/to destroy/(P)
 KanjiVerb( 撃払う ) // (v5u) to drive someone off with gunfire
 KanjiVerb( 桁上げる ) // (v1) (comp) to carry (of digit, bit, etc.)
 KanjiVerb( 傑れる ) // (v1,vi) to surpass/to outstrip/to excel
 KanjiVerb( 欠ける ) // (v1,vi) to be lacking/(P)
 KanjiVerb( 決する ) // (vs-s) to decide/to determine/(P)
 KanjiVerb( 決めつける ) // (v1) to scold/to take (a person) to task
 KanjiVerb( 決め付ける ) // (v1) to scold/to take (a person) to task/(P)
 KanjiVerb( 穴を開ける ) // (v1) to cause a loss
 KanjiVerb( 結びつく ) // (v5k) to be connected or related/to join together/(P)
 KanjiVerb( 結び付く ) // (v5k) to be connected or related/to join together
 KanjiVerb( 結ぶ ) // (v5b) to tie/to bind/to link/(P)
 KanjiVerb( 結論づける ) // (v1) to reason/to sum up/to conclude
 KanjiVerb( 結論付ける ) // (v1) to reason/to sum up/to conclude
 KanjiVerb( 血迷う ) // (v5u,vi) to lose one's mind/to lose control of oneself
 KanjiVerb( 倹しく暮す ) // (v5s) to live frugally
 KanjiVerb( 倦きる ) // (v1,vi) to get tired of/to lose interest in/to have enough
 KanjiVerb( 倦ねる ) // (v1) (uk) to tire of/to lose interest in
 KanjiVerb( 倦み疲れる ) // (v1) to grow weary/to get tired of
 KanjiVerb( 倦む ) // (v5m,vi) to get tired of (doing)/to lose interest in
 KanjiVerb( 倦る ) // (v1,vi) to get tired of/to lose interest in/to have enough
 KanjiVerb( 兼ね仕える ) // (v1) to serve at the same time
 KanjiVerb( 建つ ) // (v5t,vi) to erect/to be erected/to be built/(P)
 KanjiVerb( 建て回す ) // (v5s) to build around
 KanjiVerb( 建て込む ) // (v5m) to be built up/to be crowded with houses
 KanjiVerb( 懸け離れる ) // (v1,vi) to be very far apart from/to be remote/to be quite different from
 KanjiVerb( 懸離れる ) // (v1,vi) to be very far apart from/to be remote/to be quite different from
 KanjiVerb( 捲れる ) // (v1,vi) to be (get) turned up (inside out)
 KanjiVerb( 肩をすくめる ) // (v1) to shrug one's shoulders
 KanjiVerb( 肩を怒らせる ) // (v1) to perk up (square) one's shoulders
 KanjiVerb( 肩寄せる ) // (v1) to be (standing) together, an arm across the other's shoulder
 KanjiVerb( 見える ) // (v1,vi) to be seen/to be in sight/to look/to seem/to appear/(P)
 KanjiVerb( 見え透く ) // (v5k,vi) to be transparent
 KanjiVerb( 見とれる ) // (v1,vi) to be fascinated (by)/to watch something in fascination/to be charmed
 KanjiVerb( 見慣れる ) // (v1,vi) to become used to seeing/to be familiar with/(P)
 KanjiVerb( 見交わす ) // (v5s) to exchange glances
 KanjiVerb( 見向く ) // (v5k,vi) to look around/to look towards (us)
 KanjiVerb( 見合う ) // (v5u) (1) to exchange glances/(2) to correspond/to counterbalance
 KanjiVerb( 見合わせる ) // (v1) to exchange glances/to postpone/to suspend operations/to refrain from performing an action/(P)
 KanjiVerb( 見惚れる ) // (v1,vi) to be fascinated (by)/to watch something in fascination/to be charmed
 KanjiVerb( 見尽くす ) // (v5s) to see everything
 KanjiVerb( 見続ける ) // (v1) to gaze away
 KanjiVerb( 見損ねる ) // (v1) to miss seeing
 KanjiVerb( 見直す ) // (v5s) to look again/to get a better opinion of/(P)
 KanjiVerb( 見蕩れる ) // (v1,vi) to be fascinated (by)/to watch something in fascination/to be charmed
 KanjiVerb( 見馴れる ) // (v1,vi) to become used to seeing/to be familiar with
 KanjiVerb( 見飽きる ) // (v1,vi) to be tired of looking at
 KanjiVerb( 遣って行く ) // (v5k-s) to live/to make a living/to get on with
 KanjiVerb( 遣られる ) // (v1) (uk) to suffer damage/to be deceived
 KanjiVerb( 遣り過ぎる ) // (v1) to overdo/to go too far/to go to excess
 KanjiVerb( 遣り損なう ) // (v5u) to fail
 KanjiVerb( 遣り通す ) // (v5s) to carry through/to achieve/to complete
 KanjiVerb( 顕われる ) // (v1,vi) (1) to appear/to come in sight/to become visible/to come out/to embody/to materialize/to materialise/(2) to express oneself
 KanjiVerb( 元気過ぎる ) // (v1) to be too energetic
 KanjiVerb( 元気付く ) // (v5k) to get encouraged/to become heightened in spirits/to recover one's strength
 KanjiVerb( 減ずる ) // (vz,vi) to decrease/to reduce/to subtract
 KanjiVerb( 減り込む ) // (v5m,vi) to sink into/to cave in
 KanjiVerb( 現ずる ) // (vz,vi) to appear/to reveal/to show
 KanjiVerb( 現れる ) // (v1,vi) (1) to appear/to come in sight/to become visible/to come out/to embody/to materialize/to materialise/(2) to express oneself/(P)
 KanjiVerb( 現われる ) // (v1,vi) (1) to appear/to come in sight/to become visible/to come out/to embody/to materialize/to materialise/(2) to express oneself/(P)
 KanjiVerb( 現われ出る ) // (v1) to appear
 KanjiVerb( 言い過ごす ) // (v5s) to talk or say too much/to go too far/to overstate/to exaggerate
 KanjiVerb( 言い改める ) // (v1) to correct oneself
 KanjiVerb( 言い掛けて止める ) // (v1) to stop in the middle of a sentence
 KanjiVerb( 言い丸める ) // (v1) to do sweet-talk
 KanjiVerb( 言い及ぶ ) // (v5b,vi) to refer to/to mention (e.g., theme)
 KanjiVerb( 言い古す ) // (v5s) to say repeatedly or proverbially
 KanjiVerb( 言い交わす ) // (v5s) to exchange words or promises/to promise
 KanjiVerb( 言い合わせる ) // (v1) to agree in advance
 KanjiVerb( 言い止す ) // (v5s) to break off (in middle of sentence)
 KanjiVerb( 言い尽くす ) // (v5s) to tell all/to give a full account
 KanjiVerb( 言い損なう ) // (v5u) to say by mistake/to make a slip of the tongue
 KanjiVerb( 言い聞かす ) // (v5s) to tell someone to do something/to warm/to persuade/to instruct
 KanjiVerb( 言い暮らす ) // (v5s) to pass the time talking
 KanjiVerb( 言い忘れる ) // (v1) to forget to mention or say
 KanjiVerb( 言う ) // (v5u) to say/(P)
 KanjiVerb( 言過ごす ) // (v5s) to talk or say too much/to go too far/to overstate/to exaggerate
 KanjiVerb( 言改める ) // (v1) to correct oneself
 KanjiVerb( 言掛けて止める ) // (v1) to stop in the middle of a sentence
 KanjiVerb( 言丸める ) // (v1) to do sweet-talk
 KanjiVerb( 言及ぶ ) // (v5b,vi) to refer to/to mention (e.g., theme)
 KanjiVerb( 言古す ) // (v5s) to say repeatedly or proverbially
 KanjiVerb( 言交わす ) // (v5s) to exchange words or promises/to promise
 KanjiVerb( 言合わせる ) // (v1) to agree in advance
 KanjiVerb( 言止す ) // (v5s) to break off (in middle of sentence)
 KanjiVerb( 言尽くす ) // (v5s) to tell all/to give a full account
 KanjiVerb( 言損なう ) // (v5u) to say by mistake/to make a slip of the tongue
 KanjiVerb( 言聞かす ) // (v5s) to tell someone to do something/to warm/to persuade/to instruct
 KanjiVerb( 言暮らす ) // (v5s) to pass the time talking
 KanjiVerb( 言忘れる ) // (v1) to forget to mention or say
 KanjiVerb( 古く見せる ) // (v1) to impart an ancient appearance
 KanjiVerb( 古びる ) // (v1,vi) to look old/to get old
 KanjiVerb( 古び衰える ) // (v1) to waste away
 KanjiVerb( 古ぼける ) // (v1,vi) (uk) to look old/to become musty/to wear out
 KanjiVerb( 古惚ける ) // (v1,vi) (uk) to look old/to become musty/to wear out
 KanjiVerb( 呼ばれる ) // (v1,vi) (1) to be treated to something/(2) to be called (a name)/to be referred to (as)
 KanjiVerb( 呼び慣れる ) // (v1) to be used to calling (someone by a certain name)
 KanjiVerb( 呼び起こす ) // (v5s) to call (to mind)/to wake
 KanjiVerb( 呼び交わす ) // (v5s) to call each other's names
 KanjiVerb( 呼び込む ) // (v5m) to call in/to restore a disowned son
 KanjiVerb( 固く戒める ) // (v1) to admonish sternly
 KanjiVerb( 戸惑う ) // (v5u,vi) to be bewildered/to be perplexed/(P)
 KanjiVerb( 枯れる ) // (v1,vi) to wither (plant)/to be blasted/to die/(P)
 KanjiVerb( 跨ぐ ) // (v5g) to straddle/(P)
 KanjiVerb( 伍する ) // (vs-s) to rank with (among)
 KanjiVerb( 後へ引く ) // (v5k) to retreat/to recede
 KanjiVerb( 後へ退く ) // (v5k) to retreat/to recede
 KanjiVerb( 後れる ) // (v1,vi) to be late/to be delayed/to fall behind schedule/to be overdue
 KanjiVerb( 御座る ) // (v5aru,vi) (pol) to be
 KanjiVerb( 御座居る ) // (v1) to be (very pol.)
 KanjiVerb( 語りかける ) // (v1) to make a speech/to address
 KanjiVerb( 語り掛ける ) // (v1) to make a speech/to address
 KanjiVerb( 誤魔化す ) // (v5s) to deceive/to falsify/to misrepresent/(P)
 KanjiVerb( 交う ) // (v5u) to take turns/to mingle together
 KanjiVerb( 交尾む ) // (v5m,vi) to copulate (animals)/to mate
 KanjiVerb( 光り輝く ) // (v5k,vi) to shine/to glitter/(P)
 KanjiVerb( 効く ) // (v5k,vi) to be effective/(P)
 KanjiVerb( 口ずさむ ) // (v5m) to hum something/to sing to oneself
 KanjiVerb( 口づける ) // (v1) to kiss
 KanjiVerb( 口をつける ) // (v1) to taste/to try (food or drink)
 KanjiVerb( 口を入れる ) // (v1) to throw in a suggestion
 KanjiVerb( 口を付ける ) // (v1) to taste/to try (food or drink)
 KanjiVerb( 口吟む ) // (v5m) to hum
 KanjiVerb( 口説き落とす ) // (v5s) to persuade/to prevail upon/to win a woman's heart/to win over/to talk someone into doing
 KanjiVerb( 口付ける ) // (v1) to kiss
 KanjiVerb( 向かい合う ) // (v5u,vi) to be opposite/to face each other
 KanjiVerb( 向かい合わせる ) // (v1) to face/to confront/to be opposite to
 KanjiVerb( 向かう ) // (v5u,vi) (1) to face/(2) to go towards/(P)
 KanjiVerb( 向き合う ) // (v5u,vi) to be opposite/to face each other
 KanjiVerb( 向く ) // (v5k) (1) to face/(2) to turn toward/(3) to be suited to/to be fit for/(P)
 KanjiVerb( 向け替える ) // (v1) to change direction
 KanjiVerb( 向こうから来る ) // (vk) to come from the opposite direction
 KanjiVerb( 向こうで暮らす ) // (v5s) to live overseas
 KanjiVerb( 垢抜ける ) // (v1) to refine
 KanjiVerb( 慌てふためく ) // (v5k,vi) to get into a panic/to be flustered/to panic/to get in a flap
 KanjiVerb( 慌てる ) // (v1,vi) to become confused (disconcerted, disorganized, disorganised)/(P)
 KanjiVerb( 抗う ) // (v5u,vi) (1) to dispute/to argue/to be at variance/(2) to compete/to contest/(3) to deny (e.g., evidence)
 KanjiVerb( 拘う ) // (v5u) (1) (uk) to be mixed up with/to have a connection with (a troublesome matter)/(2) to be a stickler about/to be finicky about (some triviality)/(3) to take part (in some work)/to hang about/to bother (someone)
 KanjiVerb( 拘らう ) // (v5u) (1) (uk) to be mixed up with/to have a connection with (a troublesome matter)/(2) to be a stickler about/to be finicky about (some triviality)/(3) to take part (in some work)/to hang about/to bother (someone)
 KanjiVerb( 控える ) // (v1) to draw in/to hold back/to make notes/to be temperate in/(P)
 KanjiVerb( 攻めあぐねる ) // (v1) to be at a loss how to continue/to become disheartened
 KanjiVerb( 攻め苛む ) // (v5m) to torture
 KanjiVerb( 攻め寄せる ) // (v1,vi) to make an onslaught (on)/to close in (on)
 KanjiVerb( 攻め倦ねる ) // (v1) to be at a loss how to continue/to become disheartened
 KanjiVerb( 攻め倦む ) // (v5m,vi) to lose the attacking initiative
 KanjiVerb( 攻め込む ) // (v5m,vi) to invade/to attack
 KanjiVerb( 攻め落とす ) // (v5s) to assault
 KanjiVerb( 更ける ) // (v1,vi) to get late/to advance/to wear on/(P)
 KanjiVerb( 構う ) // (v5u) to mind/to care about/to be concerned about/(P)
 KanjiVerb( 絞り込む ) // (v5m) (1) to squeeze/to wring out/(2) to narrow down/to refine
 KanjiVerb( 考えあぐねる ) // (v1) to be at a loss/to think and think but get nowhere/to fail to come up with a good idea
 KanjiVerb( 考え倦ねる ) // (v1) to be at a loss/to think and think but get nowhere/to fail to come up with a good idea
 KanjiVerb( 考え込む ) // (v5m,vi) to ponder/to brood
 KanjiVerb( 考え出す ) // (v5s) to think out/to devise/to invent/to begin to think/to come up with a plan
 KanjiVerb( 考え抜く ) // (v5k) to think thoroughly
 KanjiVerb( 肯く ) // (v5k,vi) (uk) to nod/to bow one's head in assent
 KanjiVerb( 荒む ) // (v5m) to grow wild/to run to waste
 KanjiVerb( 荒れる ) // (v1,vi) to be stormy/to be rough/to lose one's temper/(P)
 KanjiVerb( 荒れ果てる ) // (v1,vi) to fall into ruin/to be desolated
 KanjiVerb( 荒れ狂う ) // (v5u,vi) to rage/to get angry
 KanjiVerb( 荒果てる ) // (v1,vi) to fall into ruin/to be desolated
 KanjiVerb( 荒立つ ) // (v5t) to be(come) rough or aggravated or worse
 KanjiVerb( 行う ) // (v5u) to perform/to do/to conduct oneself/to carry out/(P)
 KanjiVerb( 行き違う ) // (v5u,vi) (1) to cross (each other)/to pass (each other)/(2) to misunderstand/to go amiss
 KanjiVerb( 行き過ぎる ) // (v1,vi) to go too far/to go to extremes/(P)
 KanjiVerb( 行き会う ) // (v5u) to meet somebody by chance
 KanjiVerb( 行き交う ) // (v5u,vi) to come and go/to go back and forth
 KanjiVerb( 行き合わせる ) // (v1) to happen to meet
 KanjiVerb( 行き始める ) // (v1) to get going/to start off
 KanjiVerb( 行き着く ) // (v5k,vi) to arrive at/to end up
 KanjiVerb( 行き届く ) // (v5k,vi) to be scrupulous/to be attentive/to be prudent/to be complete/to be thorough
 KanjiVerb( 行き悩む ) // (v5m,vi) to reach an impasse or deadlock
 KanjiVerb( 行き暮れる ) // (v1,vi) to be overtaken by darkness
// KanjiVerb( 行く ) // (v5k-s,vi) to go/(P)
 KanjiVerb( 行ける ) // (v1) to be good at
 KanjiVerb( 行なう ) // (v5u) to perform/to do/to conduct oneself/to carry out
 KanjiVerb( 行なわれる ) // (v1) to be done/to be practiced/to be practised/to take place/to be held/to prevail
 KanjiVerb( 行われる ) // (v1) to be done/to be practiced/to be practised/to take place/to be held/to prevail
 KanjiVerb( 降って湧く ) // (v5k) to happen suddenly/to take place unexpectedly
 KanjiVerb( 降りだす ) // (v5s,vi) to begin to rain
 KanjiVerb( 降りる ) // (v1,vi) to alight (e.g., from bus)/to get off/to descend (e.g., a mountain)/(P)
 KanjiVerb( 降り込む ) // (v5m,vi) to rain upon
 KanjiVerb( 降り始める ) // (v1) to begin to fall
 KanjiVerb( 降り止む ) // (v5m,vi) to stop raining or snowing
 KanjiVerb( 降り出す ) // (v5s,vi) to begin to rain
 KanjiVerb( 降り続く ) // (v5k,vi) to continue to rain or snow
 KanjiVerb( 降り注ぐ ) // (v5g,vi) to rain incessantly/to downpour
 KanjiVerb( 降り敷く ) // (v5k,vi) to be covered with
 KanjiVerb( 降り立つ ) // (v5t,vi) (1) to go down and stand/(2) to alight/to get down
 KanjiVerb( 項垂れる ) // (v1,vi) to hang one's head
 KanjiVerb( 合う ) // (v5u,vi) to fit/to suit/to agree with/to match/to be correct/to be profitable/(P)
 KanjiVerb( 合する ) // (vs-s,vi) to join together/to sum up/to combine/to unite/to mix/to agree with
 KanjiVerb( 合わす ) // (v5s) to join together/to face/to unite/to be opposite/to combine/to connect/to add up/to mix/to match/to overlap/to compare/to check with/(P)
 KanjiVerb( 合わせ行なう ) // (v5u) to carry on together/to do at the same time
 KanjiVerb( 轟く ) // (v5k,vi) to roar
 KanjiVerb( 克つ ) // (v5t,vi) to win/to gain victory
 KanjiVerb( 刻み出す ) // (v5s) to carve out
 KanjiVerb( 黒ずむ ) // (v5m,vi) to blacken/to darken
 KanjiVerb( 黒ばむ ) // (v5m,vi) to blacken/to become black
 KanjiVerb( 腰かける ) // (v1,vi) to sit (down)
 KanjiVerb( 腰掛ける ) // (v1,vi) to sit (down)/(P)
 KanjiVerb( 惚ける ) // (v1,vi) (1) to grow senile/(2) to fade (colour, color)/(P)
 KanjiVerb( 惚れる ) // (v1,vi) to fall in love/to be in love/to be charmed with/to lose one's heart to/(P)
 KanjiVerb( 惚れ込む ) // (v5m,vi) to be charmed by
 KanjiVerb( 惚気る ) // (v1,vi) to play up/to speak fondly of/to praise one's spouse
 KanjiVerb( 骨が折れる ) // (v1) to require much effort/to be hard to do/to have one's bones broken
 KanjiVerb( 骨を覚える ) // (v1) to learn the ropes/to get the knack
 KanjiVerb( 込み合う ) // (v5u,vi) to be crowded/to be packed/to be jammed
 KanjiVerb( 込み上げる ) // (v1,vi) (1) to feel nauseous/(2) to fill (one's heart)/to experience a welling up of feelings or sensations
 KanjiVerb( 込む ) // (v5m,vi) (1) to be crowded/(2) to go inside (usu. only when used in compound verbs)/(P)
 KanjiVerb( 込合う ) // (v5u,vi) to be crowded/to be packed/to be jammed
 KanjiVerb( 今めかす ) // (v5s) to modernize/to modernise
 KanjiVerb( 困らせる ) // (v1) to trouble with questions/to embarrass/to put out/to put on the spot/to inconvenience
 KanjiVerb( 困り果てる ) // (v1,vi) to be greatly perplexed/to be greatly embarrassed/(P)
 KanjiVerb( 困り抜く ) // (v5k,vi) to be at one's wit's end/to be in great trouble/to be at a loss
 KanjiVerb( 困難と闘う ) // (v5u) to contend with difficulties
 KanjiVerb( 根ざす ) // (v5s) to come from/to have roots in/(P)
 KanjiVerb( 根差す ) // (v5s,vi) to root in/to come from
 KanjiVerb( 根付く ) // (v5k,vi) to take root/to strike
 KanjiVerb( 混じり合う ) // (v5u) to be mixed together/to be blended
 KanjiVerb( 混ぜっ返す ) // (v5s) to mix in/to stir (up)/to interfere
 KanjiVerb( 混ぜ合わす ) // (v5s) mix together/blend/compound/(P)
 KanjiVerb( 混ぜ返す ) // (v5s) to banter/to make fun of (what a person says)/to stir up/to jeer at
 KanjiVerb( 混み合う ) // (v5u,vi) to be crowded/to be packed/to be jammed
 KanjiVerb( 混む ) // (v5m,vi) (1) to be crowded/(2) to go inside (usu. only when used in compound verbs)/(P)
 KanjiVerb( 混合う ) // (v5u,vi) to be crowded/to be packed/to be jammed
 KanjiVerb( 混沌としている ) // (v1) to be chaotic
 KanjiVerb( 魂消る ) // (v1,vi) to be astonished/to be startled/to be appalled
 KanjiVerb( 左に折れる ) // (v1) to turn to the left
 KanjiVerb( 差し引く ) // (v5k) to deduct
 KanjiVerb( 差し越える ) // (v1) to go out of turn/to butt in
 KanjiVerb( 差し越す ) // (v5s,vi) to go out of turn/to send
 KanjiVerb( 差し響く ) // (v5k,vi) to influence/to affect
 KanjiVerb( 差し向かう ) // (v5u,vi) (obsc) to be face to face
 KanjiVerb( 差し込む ) // (v5m) (1) to insert/to put in/to thrust in/to plug in/(2) to shine in/to flow in/(3) to jam a batter (with an inside pitch) (baseball)
 KanjiVerb( 差し支える ) // (v1,vi) to interfere/to hinder/to become impeded/(P)
 KanjiVerb( 差し出る ) // (v1,vi) to go forward/to stick one's nose into
 KanjiVerb( 差す ) // (v5s,vi) to raise (stretch out) hands/to raise umbrella/(P)
 KanjiVerb( 差込む ) // (v5m) (1) to insert/to put in/to thrust in/to plug in/(2) to shine in/to flow in/(3) to jam a batter (with an inside pitch) (baseball)
 KanjiVerb( 坐り込む ) // (v5m,vi) to sit down (and bask)/to sit-in (in protest)
 KanjiVerb( 座り込む ) // (v5m,vi) to sit down (and bask)/to sit-in (in protest)
 KanjiVerb( 挫く ) // (v5k) to crush/to break/to sprain
 KanjiVerb( 挫ける ) // (v1,vi) to be crushed/to be broken/to be sprained
 KanjiVerb( 催合う ) // (v5u) (arch) to co-operate (in enterprises)/to hold in common/to share
 KanjiVerb( 再び述べる ) // (v1) to restate
 KanjiVerb( 再び読む ) // (v5m) to reread/to read again
 KanjiVerb( 塞ぎ込む ) // (v5m,vi) to mope
 KanjiVerb( 才弾ける ) // (v1,vi) to be presumptuous/to be clever and forward
 KanjiVerb( 採り上げる ) // (v1) to accept/to adopt/to listen to
 KanjiVerb( 済む ) // (v5m,vi) to finish/to end/to be completed/(P)
 KanjiVerb( 砕ける ) // (v1,vi) to break/to be broken/(P)
 KanjiVerb( 斎く ) // (v5k,vi) to worship/enshrine
 KanjiVerb( 斎む ) // (v5m,vi) to avoid/to refrain from/to shun
 KanjiVerb( 裁ちかける ) // (v1) to begin to cut
 KanjiVerb( 裁ち掛ける ) // (v1) to begin to cut
 KanjiVerb( 裁ち出す ) // (v5s) to cut out (a dress) from cloth
 KanjiVerb( 裁ち縫う ) // (v5u) to cut and sew
 KanjiVerb( 際する ) // (vs-s) to arrive/to come to pass
 KanjiVerb( 際立つ ) // (v5t) to be prominent/to be conspicuous/(P)
 KanjiVerb( 在り付く ) // (v5k) to get/to obtain/to come by/to find
 KanjiVerb( 罪する ) // (vs-s) to charge/to sentence/to punish
 KanjiVerb( 冴える ) // (v1,vi) to be clear/to be serene/to be cold/to be skillful/(P)
 KanjiVerb( 冴え輝く ) // (v5k) to shine clearly
 KanjiVerb( 冴え行く ) // (v5k-s,vi) to clear gradually/to get cold gradually
 KanjiVerb( 咲う ) // (v5u,vi) to laugh/to smile
 KanjiVerb( 咲き溢れる ) // (v1,vi) to bloom all over
 KanjiVerb( 咲き出す ) // (v5s,vi) to begin to bloom/to come out
 KanjiVerb( 咲き初める ) // (v1,vi) to begin to blossom
 KanjiVerb( 咲き揃う ) // (v5u,vi) to be in full bloom
 KanjiVerb( 咲き匂う ) // (v5u,vi) to be in full bloom
 KanjiVerb( 咲き乱れる ) // (v1,vi) to bloom in profusion/(P)
 KanjiVerb( 咲く ) // (v5k,vi) to bloom/(P)
 KanjiVerb( 作り損じる ) // (v1) to fail in making
 KanjiVerb( 作り損なう ) // (v5u) to fail in making
 KanjiVerb( 作り返す ) // (v5s) to remake
 KanjiVerb( 作家として鳴らす ) // (v5s) to be very popular as a writer
 KanjiVerb( 削ぐ ) // (v5g) (1) to chip/to slice off/to sharpen/(2) to thin down/to reduce/to weaken
 KanjiVerb( 削げる ) // (v1,vi) to split/to be split/to splinter
 KanjiVerb( 削り落とす ) // (v5s) to scrape off/to plane off
 KanjiVerb( 削れる ) // (v1) to be shaved or planed
 KanjiVerb( 刷り出す ) // (v5s) to print/to publish/to begin to print
 KanjiVerb( 刷り損なう ) // (v5u) to misprint/to spoil in printing
 KanjiVerb( 刷り直す ) // (v5s) to reprint (book)
 KanjiVerb( 察する ) // (vs-s) to guess/to sense/to presume/to judge/to sympathize with/to sympathise with/(P)
 KanjiVerb( 擦り込む ) // (v5m) to rub in/to grind and mix
 KanjiVerb( 擦り切れる ) // (v1,vi) to wear out
 KanjiVerb( 擦り替える ) // (v1) to substitute/to sidestep (an issue)
 KanjiVerb( 擦り剥く ) // (v5k) to skin (one's knee)/to graze
 KanjiVerb( 擦り剥ける ) // (v1,vi) to abrade
 KanjiVerb( 擦り抜ける ) // (v1,vi) to slip through/to make one's way through quickly
 KanjiVerb( 擦り落とす ) // (v5s) to scrape off/to rub off
 KanjiVerb( 擦れる ) // (v1,vi) to rub/to chafe/to wear/to become sophisticated
 KanjiVerb( 擦れ違う ) // (v5u,vi) to pass by one another/to disagree/to miss each other
 KanjiVerb( 擦れ合う ) // (v5u,vi) to rub against/to chafe/to quarrel
 KanjiVerb( 殺ぐ ) // (v5g) (1) to chip/to slice off/to sharpen/(2) to thin down/to reduce/to weaken
 KanjiVerb( 殺げる ) // (v1,vi) to split/to be split/to splinter
 KanjiVerb( 殺気立つ ) // (v5t,vi) to be seething (with anger)/to be frenzied/to be menacing
 KanjiVerb( 捌く ) // (v5k) to handle/to sell
 KanjiVerb( 捌ける ) // (v1,vi) to be in order/to sell well/to be sociable/to flow smoothly
 KanjiVerb( 錆びる ) // (v1,vi) to rust/to become rusty/(P)
 KanjiVerb( 錆び付く ) // (v5k,vi) to rust together
 KanjiVerb( 錆付く ) // (v5k,vi) to rust together
 KanjiVerb( 三塁で刺される ) // (v1) to be put (thrown) out at third base
 KanjiVerb( 参らせる ) // (v1) to beat/to floor (someone)/to bring (someone) to his knees/to come
 KanjiVerb( 散ける ) // (v1,vi) to unravel
 KanjiVerb( 散り敷く ) // (v5k,vi) to lie scattered or strewn about
 KanjiVerb( 散り乱れる ) // (v1,vi) to be or lay scattered
 KanjiVerb( 産気付く ) // (v5k) to go into labor/to go into labour
 KanjiVerb( 斬り合う ) // (v5u,vi) to fight with swords/to cross swords
 KanjiVerb( 仕える ) // (v1,vi) to serve/to work for/(P)
 KanjiVerb( 仕兼ねる ) // (v1) to be unable to do/to hesitate/to be reluctant
 KanjiVerb( 仕込む ) // (v5m) to train/to teach/to educate/to stock/to prepare
 KanjiVerb( 仕済ます ) // (v5s) to succeed as planned
 KanjiVerb( 仕始める ) // (v1) to begin/to start
 KanjiVerb( 仕損なう ) // (v5u) to blunder/to fail/to make a mistake/to miss
 KanjiVerb( 仕直す ) // (v5s) to do over/to remake/to resume
 KanjiVerb( 仕馴れる ) // (v1) to be used to doing/to be experienced in
 KanjiVerb( 使い果たす ) // (v5s) to use up/to squander
 KanjiVerb( 使い過ぎる ) // (v1) to use excessively/to use too much/to spend too much/to overwork someone
 KanjiVerb( 使い慣らす ) // (v5s) to accustom oneself to using/to train/to break in (horses)
 KanjiVerb( 使い慣れる ) // (v1) to get accustomed to using
 KanjiVerb( 使い熟す ) // (v5s) to handle/to manage
 KanjiVerb( 使い出す ) // (v5s) to start using/to try out
 KanjiVerb( 使い尽くす ) // (v5s) to use up/to squander
 KanjiVerb( 使える ) // (v1) to be useful/to be serviceable
 KanjiVerb( 刺される ) // (v1) to be stabbed
 KanjiVerb( 師と仰ぐ ) // (v5g) to look up to (a person) as one's preceptor
 KanjiVerb( 志す ) // (v5s,vi) to plan/to intend/to aspire to/to set aims (sights on)/(P)
 KanjiVerb( 思いあぐねる ) // (v1) to think something over and over/to rack one's brains/to be at a loss
 KanjiVerb( 思いつく ) // (v5k) to think of/to hit upon/to come into one's mind/to be struck with an idea
 KanjiVerb( 思い及ぶ ) // (v5b,vi) to hit upon something
 KanjiVerb( 思い倦ねる ) // (v1) to think something over and over/to rack one's brains/to be at a loss
 KanjiVerb( 思い合う ) // (v5u,vi) to love one another
 KanjiVerb( 思い合わせる ) // (v1) to consider all the circumstances
 KanjiVerb( 思い込む ) // (v5m,vi) to be under impression that/to be convinced that/to imagine that/to set one's heart on/to be bent on/(P)
 KanjiVerb( 思い焦がれる ) // (v1,vi) to pine for
 KanjiVerb( 思い煩う ) // (v5u,vi) to worry about/to be vexed
 KanjiVerb( 思い付く ) // (v5k) to think of/to hit upon/to come into one's mind/to be struck with an idea/(P)
 KanjiVerb( 思い浮かぶ ) // (v5b) to occur to/to remind of
 KanjiVerb( 思い浮かべる ) // (v1) to be reminded of/to call to mind
 KanjiVerb( 思い乱れる ) // (v1,vi) to be worried about
 KanjiVerb( 思い惑う ) // (v5u,vi) to be at a loss
 KanjiVerb( 思える ) // (v1) to seem/to appear likely
 KanjiVerb( 思わせる ) // (v1) to make somebody believe (something)/to give somebody the impression
 KanjiVerb( 思われる ) // (v1) to seem/to appear
 KanjiVerb( 指折り数える ) // (v1) to count on one's fingers
 KanjiVerb( 指導者として頂く ) // (v5k) to have (a person) as one's leader
 KanjiVerb( 支える ) // (v1,vi) to be blocked/to choke/to be obstructed/to feel a pressure on one's chest
 KanjiVerb( 旨く行く ) // (v5k-s) to go smoothly/to turn out well/to do the trick/to have peaceful relations
 KanjiVerb( 止む ) // (v5m,vi) to cease/to stop/to be over/(P)
 KanjiVerb( 死して後已む ) // (v5m) to be determined to do or die
 KanjiVerb( 死にかける ) // (v1) to be dying/to be about to die/to be close to death
 KanjiVerb( 死に掛ける ) // (v1) to be dying/to be about to die/to be close to death
 KanjiVerb( 死に急ぐ ) // (v5g,vi) to hasten one's death
 KanjiVerb( 死に後れる ) // (v1,vi) to outlive
 KanjiVerb( 死に絶える ) // (v1,vi) to die out/to become extinct
 KanjiVerb( 死に損なう ) // (v5u) to fail to die/to survive/to outlive
 KanjiVerb( 死に別れる ) // (v1,vi) to be separated by death
 KanjiVerb( 死ぬ ) // (v5n,vi) to die/(P)
 KanjiVerb( 死ぬ迄戦う ) // (v5u) to fight to the last (death)
 KanjiVerb( 私する ) // (vs-s) to think only of oneself/to possess oneself
 KanjiVerb( 脂染みる ) // (v1,vi) to become greasy/to be oil-stained
 KanjiVerb( 試験で撥ねられる ) // (v1) to get flunked in an examination
 KanjiVerb( 資する ) // (vi,vs-s) to contribute/to finance/(P)
 KanjiVerb( 賜う ) // (v5u) to grant/to bestow/to award
 KanjiVerb( 飼い馴らす ) // (v5s) to tame/to domesticate
 KanjiVerb( 歯向う ) // (v5u,vi) to strike back at/to bite back/to turn on/to rise against/to oppose/to defy/(P)
 KanjiVerb( 歯向かう ) // (v5u,vi) to strike back at/to bite back/to turn on/to rise against/to oppose/to defy/(P)
 KanjiVerb( 事欠く ) // (v5k,vi) to lack
 KanjiVerb( 事切れる ) // (v1,vi) to expire/to die
 KanjiVerb( 事足りる ) // (v1,vi) to suffice/to serve the purpose/to be satisfied
 KanjiVerb( 事立てる ) // (v1) to do something different/to make a big thing of
 KanjiVerb( 似る ) // (v1,vi) to resemble/to be similar/(P)
 KanjiVerb( 似合う ) // (v5u,vi) to suit/to match/to become/to be like/(P)
 KanjiVerb( 似通う ) // (v5u,vi) to resemble closely/(P)
 KanjiVerb( 似付く ) // (v5k,vi) to become/to suit/to be like/to match well
 KanjiVerb( 侍する ) // (vs-s) to wait upon/to serve
 KanjiVerb( 持する ) // (vs-s) to hold/to maintain
 KanjiVerb( 持ち続ける ) // (v1) to persist in
 KanjiVerb( 持ち歩く ) // (v5k) to carry
 KanjiVerb( 持って来る ) // (vk) to bring/(P)
 KanjiVerb( 持つ ) // (v5t) (1) to hold/to carry/(2) to possess/(P)
 KanjiVerb( 持てる ) // (v1,vi) (1) to be well liked/to be popular/to be welcomed/(2) to possess riches/to be wealthy/(P)
 KanjiVerb( 持て囃す ) // (v5s) to praise extravagantly/to lionize/to lionise/to make much of
 KanjiVerb( 時めく ) // (v5k,vi) to be prosperous/to prosper/to flourish/to enjoy great prosperity
 KanjiVerb( 時化る ) // (v1) (uk) to be stormy or choppy (sea)/to go through hard times
 KanjiVerb( 時期に差しかける ) // (v1) to get close to the time
 KanjiVerb( 時期に差し掛ける ) // (v1) to get close to the time
 KanjiVerb( 次ぐ ) // (v5g,vi) to rank next to/to come after/(P)
 KanjiVerb( 示し合わす ) // (v5s) to conspire (with)/to prearrange
 KanjiVerb( 耳が肥えている ) // (v1) to have an ear for music
 KanjiVerb( 耳が肥ている ) // (v1) to have an ear for music
 KanjiVerb( 耳慣れる ) // (v1,vi) to be something familiar
 KanjiVerb( 自惚れる ) // (v1,vi) to be conceited/(P)
 KanjiVerb( 自分で決める ) // (v1) to decide by oneself
 KanjiVerb( 辞す ) // (v5s) to resign/to leave post/(P)
 KanjiVerb( 辞する ) // (vs-s) to resign (post)/to excuse oneself/to take one's leave
 KanjiVerb( 叱られる ) // (v1) to be scolded (reproved)
 KanjiVerb( 失する ) // (vs-s) to lose/to miss/to forget/to be excessive
 KanjiVerb( 失せる ) // (v1,vi) to disappear/to vanish
 KanjiVerb( 質に入れる ) // (v1) to pawn/to pledge
 KanjiVerb( 射し込む ) // (v5m,vi) to shine in (light)/to illuminate
 KanjiVerb( 射す ) // (v5s) to shine/to strike/(P)
 KanjiVerb( 射殺す ) // (v5s) to shoot a person to death
 KanjiVerb( 射損なう ) // (v5u) to shoot and miss
 KanjiVerb( 射抜く ) // (v5k) to shoot through
 KanjiVerb( 射落とす ) // (v5s) to shoot down/to win/to gain
 KanjiVerb( 捨てて置く ) // (v5k) to leave something as it is
 KanjiVerb( 煮える ) // (v1,vi) to boil/to cook/to be cooked/(P)
 KanjiVerb( 煮え立つ ) // (v5t,vi) to boil/to come to a boil
 KanjiVerb( 煮やす ) // (v5s) to cook inside/(P)
 KanjiVerb( 煮込む ) // (v5m,vi) to cook together/to boil well/(P)
 KanjiVerb( 煮立つ ) // (v5t,vi) to boil or simmer
 KanjiVerb( 煮零れる ) // (v1,vi) to boil over
 KanjiVerb( 謝する ) // (vs-s) (1) to thank/(2) to apologize/to apologise/(3) to say farewell/to retreat/to retire/(4) to refuse/(5) to pay back/to settle old scores
 KanjiVerb( 借り越す ) // (v5s) to overdraw
 KanjiVerb( 借り込む ) // (v5m) to borrow
 KanjiVerb( 借り集める ) // (v1) to borrow money/to call for loans
 KanjiVerb( 借金で苦しむ ) // (v5m) to be distressed with debts
 KanjiVerb( 借集める ) // (v1) to borrow money/to call for loans
 KanjiVerb( 灼ける ) // (v1,vi) to burn/to be roasted/to be sunburnt
 KanjiVerb( 酌み交わす ) // (v5s) to drink together
 KanjiVerb( 若く見える ) // (v1) to look (seem) young
 KanjiVerb( 寂れる ) // (v1,vi) to decline/to fall (down)
 KanjiVerb( 弱り果てる ) // (v1,vi) to be exhausted/to be at a loss/to be worn out/to be helpless
 KanjiVerb( 弱り込む ) // (v5m) to weaken/to be at wits' end
 KanjiVerb( 弱り衰える ) // (v1) to languish
 KanjiVerb( 惹きつける ) // (v1) to attract/to charm
 KanjiVerb( 惹き付ける ) // (v1) to attract/to charm
 KanjiVerb( 惹く ) // (v5k) to attract/to captivate
 KanjiVerb( 取って返す ) // (v5s,vi) to return
 KanjiVerb( 取って来る ) // (vk) to fetch/to go and get
 KanjiVerb( 取っ組む ) // (v5m,vi) to tackle/to wrestle with/to engage in a bout/to come to grips with/to make effort/to strive for
 KanjiVerb( 取っ組合う ) // (v5u,vi) to come to grips with/to fight
 KanjiVerb( 取っ付く ) // (v5k,vi) to cling to/to grapple with/to possess/to stick to
 KanjiVerb( 取りこぼす ) // (v5s,vi) (1) (comp) to lose an easy game/to suffer an unexpected defeat/(2) to lose information (computers)
 KanjiVerb( 取りつかれる ) // (v1) to become obsessed with/to be possessed (by spirits, etc.)
 KanjiVerb( 取り急ぐ ) // (v5g,vi) to hurry/to hasten
 KanjiVerb( 取り交わす ) // (v5s) to exchange/to interchange
 KanjiVerb( 取り合う ) // (v5u,vi) (1) to take each other's hands/to clasp (hands)/(2) to compete/to scramble for/(3) to respond
 KanjiVerb( 取り合わせる ) // (v1) to put together/to assemble
 KanjiVerb( 取り込む ) // (v5m) to take in/to capture (e.g. image)/to introduce/to be busy/to be confused/(P)
 KanjiVerb( 取り尽くす ) // (v5s) to deplete/to take all
 KanjiVerb( 取り澄ます ) // (v5s,vi) to look unconcerned/to assume a composed look
 KanjiVerb( 取り組む ) // (v5m,vi) to tackle/to wrestle with/to engage in a bout/to come to grips with/to make effort/to strive for
 KanjiVerb( 取り付かれる ) // (v1) to become obsessed with/to be possessed (by spirits, etc.)
 KanjiVerb( 取り付く ) // (v5k,vi) to cling to/to grapple with/to possess/to stick to
 KanjiVerb( 取り紛れる ) // (v1,vi) to be in confusion/to be busy
 KanjiVerb( 取り落とす ) // (v5s) to drop/to let fall/to omit
 KanjiVerb( 取り乱す ) // (v5s,vi) to scatter about/to be distracted
 KanjiVerb( 取り零す ) // (v5s,vi) (1) (comp) to lose an easy game/to suffer an unexpected defeat/(2) to lose information (computers)
 KanjiVerb( 取り憑かれる ) // (v1) to become obsessed with/to be possessed (by spirits, etc.)
 KanjiVerb( 取り憑く ) // (v5k,vi) to cling to/to grapple with/to possess/to stick to
 KanjiVerb( 取り籠める ) // (v1) to shut in/to confine/to surround
 KanjiVerb( 取急ぐ ) // (v5g,vi) to hurry/to hasten
 KanjiVerb( 取交わす ) // (v5s) to exchange/to interchange
 KanjiVerb( 取合う ) // (v5u,vi) (1) to take each other's hands/to clasp (hands)/(2) to compete/to scramble for/(3) to respond
 KanjiVerb( 取合わせる ) // (v1) to put together/to assemble
 KanjiVerb( 取込む ) // (v5m) to take in/to capture (e.g. image)/to introduce/to be busy/to be confused
 KanjiVerb( 取尽くす ) // (v5s) to deplete/to take all
 KanjiVerb( 取澄ます ) // (v5s,vi) to look unconcerned/to assume a composed look
 KanjiVerb( 取組む ) // (v5m,vi) to tackle/to wrestle with/to engage in a bout/to come to grips with/to make effort/to strive for
 KanjiVerb( 取付かれる ) // (v1) to become obsessed with/to be possessed (by spirits, etc.)
 KanjiVerb( 取付く ) // (v5k,vi) to cling to/to grapple with/to possess/to stick to
 KanjiVerb( 取紛れる ) // (v1,vi) to be in confusion/to be busy
 KanjiVerb( 取落とす ) // (v5s) to drop/to let fall/to omit
 KanjiVerb( 取乱す ) // (v5s,vi) to scatter about/to be distracted
 KanjiVerb( 取零す ) // (v5s,vi) (1) (comp) to lose an easy game/to suffer an unexpected defeat/(2) to lose information (computers)
 KanjiVerb( 取籠める ) // (v1) to shut in/to confine/to surround
 KanjiVerb( 手がける ) // (v1) to make/to do/to produce/to work on/(P)
 KanjiVerb( 手に入れる ) // (v1,vi) to obtain/to procure
 KanjiVerb( 手向かう ) // (v5u,vi) to resist
 KanjiVerb( 手招く ) // (v5k) to beckon
 KanjiVerb( 手伝って着せる ) // (v1) to help (a person) dress
 KanjiVerb( 朱筆を加える ) // (v1) to make corrections
 KanjiVerb( 狩り立てる ) // (v1) to hunt down
 KanjiVerb( 腫れる ) // (v1,vi) to swell (from inflammation)/to become swollen/(P)
 KanjiVerb( 首を縮める ) // (v1) to duck one's head
 KanjiVerb( 首肯く ) // (v5k,vi) (uk) to nod/to bow one's head in assent
 KanjiVerb( 受けて立つ ) // (v5t) to accept somebody's challenge/to take up the gauntlet
 KanjiVerb( 受け渡す ) // (v5s) to deliver/to hand over/to transfer
 KanjiVerb( 受渡す ) // (v5s) to deliver/to hand over/to transfer
 KanjiVerb( 授業を受ける ) // (v1) to take a class
 KanjiVerb( 囚われる ) // (v1,vi) to be captured/to be apprehended/to be seized with
 KanjiVerb( 就く ) // (v5k) to settle in (place)/to take (seat, position)/to study (under teacher)/(P)
 KanjiVerb( 拾い集める ) // (v1) to gather
 KanjiVerb( 拾い上げる ) // (v1) to pick up/to pick out
 KanjiVerb( 秀でる ) // (v1,vi) to excel/to surpass/(P)
 KanjiVerb( 秋めく ) // (v5k,vi) to become autumnal
 KanjiVerb( 臭う ) // (v5u,vi) to be fragrant/to smell/to stink/to glow/to be bright/(P)
 KanjiVerb( 襲い攻める ) // (v1) to array against
 KanjiVerb( 蹴り込む ) // (v5m) to kick in
 KanjiVerb( 蹴り殺す ) // (v5s) to kick to death
 KanjiVerb( 蹴り上げる ) // (v1) to kick up/to fling up
 KanjiVerb( 集う ) // (v5u) to meet/to assemble/to congregate/(P)
 KanjiVerb( 集め始める ) // (v1) to begin to catch (attention, etc.)
 KanjiVerb( 住する ) // (vs-s) to live/to reside/to inhabit
 KanjiVerb( 住まう ) // (v5u,vi) to live/to reside/to inhabit/(P)
 KanjiVerb( 住み慣れる ) // (v1) to get used to living in
 KanjiVerb( 住み込む ) // (v5m,vi) to be a live-in employee/to live in/to live with
 KanjiVerb( 住み着く ) // (v5k,vi) to settle down
 KanjiVerb( 住む ) // (v5m,vi) to abide/to reside/to live in/to inhabit/to dwell/(P)
 KanjiVerb( 充ちる ) // (v1,vi) to be full/to rise (tide)/to mature/to expire
 KanjiVerb( 充満ている ) // (v1) to be filled with/to be pregnant with/to teem with
 KanjiVerb( 従う ) // (v5u,vi) to abide (by the rules)/to obey/to follow/to accompany/(P)
 KanjiVerb( 重なり合う ) // (v5u) to lie on top of each other/to overlap/to pile up
 KanjiVerb( 重ねかける ) // (v1) to lap/to overlap
 KanjiVerb( 重ね掛ける ) // (v1) to lap/to overlap
 KanjiVerb( 重ね合わせる ) // (v1) to overlap
 KanjiVerb( 重過ぎる ) // (v1) to be too heavy
 KanjiVerb( 重立つ ) // (v5t,vi) main/principal/important/conspicuous/prominent
 KanjiVerb( 宿す ) // (v5s,vi) (1) to keep (guest)/(2) to conceive/(3) to carry (virus)/(P)
 KanjiVerb( 祝する ) // (vs-s) to congratulate/to celebrate
 KanjiVerb( 縮む ) // (v5m,vi) to shrink/to be contracted/(P)
 KanjiVerb( 縮れる ) // (v1,vi) to be wavy/to be curled/(P)
 KanjiVerb( 熟する ) // (vs-s) to ripen/to get ripe/to mature/to be in common use/to come to sound natural
 KanjiVerb( 熟れる ) // (v1,vi) to be digested/to be mellowed
 KanjiVerb( 出かける ) // (v1,vi) to depart/to go out (e.g., on an excursion or outing)/to set out/to start/to be going out
 KanjiVerb( 出くわす ) // (v5s) to happen to meet/to come across
 KanjiVerb( 出しっ放す ) // (v5s) to leave on/to leave running/to leave lying around/to leave (a faucet) open
 KanjiVerb( 出し違う ) // (v5u) to miss sending/to miss delivering
 KanjiVerb( 出し過ぎる ) // (v1) to overdo something (speed, exertion, etc.)
 KanjiVerb( 出し放す ) // (v5s) to leave on/to leave running/to leave lying around/to leave (a faucet) open
 KanjiVerb( 出そろう ) // (v5u,vi) to appear all together/to be all present
 KanjiVerb( 出で立つ ) // (v5t,vi) to start/to leave
 KanjiVerb( 出はじめる ) // (v1) to begin to appear/to begin to come in
 KanjiVerb( 出る ) // (v1,vi) (1) to appear/to come forth/(2) to leave/to exit/(P)
 KanjiVerb( 出逢う ) // (v5u,vi) to meet by chance/to come across/to happen to encounter/to hold a rendezvous/to have a date
 KanjiVerb( 出違う ) // (v5u,vi) to miss a visitor
 KanjiVerb( 出過ぎる ) // (v1,vi) to project or protrude too much/to be too forward/to obtrude
 KanjiVerb( 出会う ) // (v5u,vi) to meet by chance/to come across/to happen to encounter/to hold a rendezvous/to have a date/(P)
 KanjiVerb( 出外れる ) // (v1,vi) to be or lie just outside of
 KanjiVerb( 出掛ける ) // (v1,vi) to depart/to go out (e.g., on an excursion or outing)/to set out/to start/to be going out/(P)
 KanjiVerb( 出向く ) // (v5k,vi) to go to/to proceed to/to leave for/(P)
 KanjiVerb( 出合う ) // (v5u,vi) to meet by chance/to come across/to happen to encounter/to hold a rendezvous/to have a date/(P)
 KanjiVerb( 出始める ) // (v1) to begin to appear/to begin to come in
 KanjiVerb( 出尽くす ) // (v5s) to be all out/to exhaust
 KanjiVerb( 出尽す ) // (v5s) to be all out/to exhaust
 KanjiVerb( 出揃う ) // (v5u,vi) to appear all together/to be all present
 KanjiVerb( 出損なう ) // (v5u) to fail to go/to fail to come
 KanjiVerb( 出遅れる ) // (v1,vi) to get a late start/(P)
 KanjiVerb( 出直す ) // (v5s,vi) to come again/to call again/to make a fresh start
 KanjiVerb( 出払う ) // (v5u,vi) to be all out
 KanjiVerb( 出歩く ) // (v5k,vi) to go out/to take a stroll/to go about
 KanjiVerb( 出来る ) // (v1,vi) (1) (uk) to be able (in a position) to do/to be up to the task/(2) to be ready/to be completed/(3) to be made/to be built/(4) to be good at/to be permitted (to do)/(5) to become intimate/to take up (with somebody)/(6) to grow/to be raised/(P)
 KanjiVerb( 出来過ぎる ) // (v1,vi) to be too much/to be too good to be true
 KanjiVerb( 出来合う ) // (v5u,vi) to be ready-made/to become intimate with
 KanjiVerb( 出来損なう ) // (v5u) to be badly made/to fail
 KanjiVerb( 述べ立てる ) // (v1) to relate at great length/to dwell eloquently (on)
 KanjiVerb( 春めく ) // (v5k,vi) to become spring-like/to show signs of spring
 KanjiVerb( 楯つく ) // (v5k) to oppose
 KanjiVerb( 楯突く ) // (v5k,vi) to oppose/to resist/to defy/(P)
 KanjiVerb( 殉じる ) // (v1,vi) to sacrifice oneself
 KanjiVerb( 準じる ) // (v1,vi) to follow/to conform/to apply to/(P)
 KanjiVerb( 準ずる ) // (vz,vi) to apply correspondingly/to correspond to/to be proportionate to/to conform to/(P)
 KanjiVerb( 潤う ) // (v5u,vi) to be moist/to be damp/to get wet/to profit by/to be watered/to receive benefits/to favor/to favour/to charm/to steepen/(P)
 KanjiVerb( 潤ける ) // (v1,vi) (uk) to become sodden/to swell up
 KanjiVerb( 潤む ) // (v5m,vi) to be clouded/to be dimmed/to be bleared/to be wet/to get muddy/(P)
 KanjiVerb( 盾突く ) // (v5k,vi) to oppose/to resist/to defy
 KanjiVerb( 巡り会う ) // (v5u) to meet fortuitously (poet)/to meet by chance/to happen across/(P)
 KanjiVerb( 巡り合う ) // (v5u) to meet fortuitously (poet)/to meet by chance/to happen across
 KanjiVerb( 巡り歩く ) // (v5k) to walk around/to travel around
 KanjiVerb( 処する ) // (vs-s) to manage/to deal with/to cope with
 KanjiVerb( 書き違える ) // (v1) to miswrite
 KanjiVerb( 書き間違える ) // (v1) to write incorrectly (e.g. character)/to make a mistake in writing
 KanjiVerb( 書き起こす ) // (v5s) to begin (start) writing
 KanjiVerb( 書き尽くす ) // (v5s) to write down or convey in full
 KanjiVerb( 書き損なう ) // (v5u) to miswrite
 KanjiVerb( 書き著す ) // (v5s) to publish (a book)
 KanjiVerb( 書き落とす ) // (v5s) to forget to write something/to leave something out/to omit something
 KanjiVerb( 書間違える ) // (v1) to write incorrectly (e.g. character)/to make a mistake in writing
 KanjiVerb( 助け起こす ) // (v5s) to help up
 KanjiVerb( 助け合う ) // (v5u,vi) to help each other/to cooperate/(P)
 KanjiVerb( 助け出す ) // (v5s) to help out of (trouble)/to extricate
 KanjiVerb( 助け上げる ) // (v1) to help up/to pick up/to bring safely to land
 KanjiVerb( 鋤起こす ) // (v5s) to turn over soil/to dig or plow up (plough)
 KanjiVerb( 傷つく ) // (v5k) to be hurt/to be wounded/to get injured
 KanjiVerb( 傷む ) // (v5m,vi) to be damaged/to go bad/(P)
 KanjiVerb( 傷付く ) // (v5k) to be hurt/to be wounded/to get injured/(P)
 KanjiVerb( 傷付ける ) // (v1) to wound/to hurt someone's feelings/(P)
 KanjiVerb( 勝ちっ放す ) // (v5s) to win consecutive/to have a long winning streak
 KanjiVerb( 勝ち越す ) // (v5s,vi) to have more wins than losses/to lead (someone) by (three) matches/(P)
 KanjiVerb( 勝ち進む ) // (v5m,vi) to win and advance to the next round
 KanjiVerb( 勝ち通す ) // (v5s) to win straight victories
 KanjiVerb( 勝ち抜く ) // (v5k,vi) to win through
 KanjiVerb( 勝ち放す ) // (v5s,vi) to win continuously
 KanjiVerb( 勝つ ) // (v5t,vi) to win/to gain victory/(P)
 KanjiVerb( 召し集める ) // (v1) to call together
 KanjiVerb( 唱する ) // (vs-s) to recite/to chant/to read aloud
 KanjiVerb( 小戻す ) // (v5s) to rally a little (e.g., market)
 KanjiVerb( 少しの損で済む ) // (v5m) to get off with a little loss
 KanjiVerb( 承知尽く ) // (v5k) to act on mutual agreement
 KanjiVerb( 招き入れる ) // (v1) to invite in/to show someone in
 KanjiVerb( 消える ) // (v1,vi) to go out/to vanish/to disappear/(P)
 KanjiVerb( 消え果てる ) // (v1,vi) to vanish completely
 KanjiVerb( 消え失せる ) // (v1,vi) (X) (vulg) to disappear/to get out of sight/to die/(in imperative) to fuck off
 KanjiVerb( 消し飛ぶ ) // (v5b,vi) to scatter away
 KanjiVerb( 焼き殺す ) // (v5s) to kill by burning to death
 KanjiVerb( 焼き尽くす ) // (v5s) to thoroughly burn/to burn to nothing
 KanjiVerb( 焼き尽す ) // (v5s) to thoroughly burn/to burn to nothing
 KanjiVerb( 焼き付く ) // (v5k) to scorch
 KanjiVerb( 焼ける ) // (v1,vi) to burn/to be roasted/to be sunburnt/(P)
 KanjiVerb( 焼け死ぬ ) // (v5n,vi) to be burnt to death
 KanjiVerb( 焼け失せる ) // (v1,vi) to burn up completely
 KanjiVerb( 焼け出される ) // (v1,vi) to be burned out (of one's home)
 KanjiVerb( 焼け付く ) // (v5k,vi) to burn
 KanjiVerb( 焼け落ちる ) // (v1,vi) to be burned down
 KanjiVerb( 焼付く ) // (v5k) to scorch
 KanjiVerb( 焦がれる ) // (v1) to yearn for/to be in love with
 KanjiVerb( 焦げる ) // (v1,vi) to burn/to be burned/(P)
 KanjiVerb( 焦げ付く ) // (v5k,vi) to get burned and stuck on/to become uncollectable (and remain unpaid)
 KanjiVerb( 焦れる ) // (v1,vi) to get impatient/to become irritated/to fret/to chafe
 KanjiVerb( 照らし合わせる ) // (v1) to check/to compare
 KanjiVerb( 照りつける ) // (v1,vi) to blaze down on/to beat down on/to shine down upon
 KanjiVerb( 照り映える ) // (v1,vi) to shine/to glow
 KanjiVerb( 照り輝く ) // (v5k,vi) to shine brilliantly
 KanjiVerb( 照り込む ) // (v5m,vi) to shine into or upon
 KanjiVerb( 照り付ける ) // (v1,vi) to blaze down on/to beat down on/to shine down upon
 KanjiVerb( 照り返す ) // (v5s,vi) to reflect/to throw back light
 KanjiVerb( 照れる ) // (v1,vi) to be shy/to feel awkward/(P)
 KanjiVerb( 照付ける ) // (v1,vi) to blaze down on/to beat down on/to shine down upon
 KanjiVerb( 称する ) // (vs-s) (1) to take the name of/to call oneself/(2) to pretend/to feign/to purport/(P)
 KanjiVerb( 笑いかける ) // (v1) to smile/to grin
 KanjiVerb( 笑いこける ) // (v1,vi) to laugh heartily
 KanjiVerb( 笑い掛ける ) // (v1) to smile/to grin
 KanjiVerb( 笑い出す ) // (v5s) to burst into laughter
 KanjiVerb( 笑い転ける ) // (v1,vi) to laugh heartily
 KanjiVerb( 笑い倒ける ) // (v1,vi) to laugh heartily
 KanjiVerb( 笑う ) // (v5u,vi) to laugh/to smile/(P)
 KanjiVerb( 笑み割れる ) // (v1,vi) to crack
 KanjiVerb( 笑む ) // (v5m,vi) to smile
 KanjiVerb( 粧し込む ) // (v5m,vi) to dress oneself up/to deck oneself out
 KanjiVerb( 粧す ) // (v5s) (1) (uk) to adorn oneself/to dress oneself up/(aux-v) (2) to give an air of/to make oneself seem like
 KanjiVerb( 詳しく述べる ) // (v1) to expound
 KanjiVerb( 上がり込む ) // (v5m,vi) to enter/to step in
 KanjiVerb( 上げ離す ) // (v5s) to cut off (the head)
 KanjiVerb( 上り詰める ) // (v1,vi) to go to the top/to be engrossed in
 KanjiVerb( 上汲む ) // (v5m) to draw off the top liquid
 KanjiVerb( 上枯れる ) // (v1) to die at the top
 KanjiVerb( 上向く ) // (v5k,vi) to look upward/to turn upward/to rise
 KanjiVerb( 上手くいく ) // (v5k-s) to go smoothly/to turn out well/to do the trick/to have peaceful relations
 KanjiVerb( 上付く ) // (v5k) (uk) to be fickle/to be restless/to be flippant
 KanjiVerb( 乗じる ) // (v1) to take advantage of/to multiply (in math)/to follow blindly/(P)
 KanjiVerb( 乗ずる ) // (vz) to take advantage of/to multiply (in math)/to follow blindly/(P)
 KanjiVerb( 乗りこなす ) // (v5s) to manage (a horse)
 KanjiVerb( 乗りつける ) // (v1,vi) to ride up to/to get used to riding
 KanjiVerb( 乗り移す ) // (v5s) to transfer (a stowaway)
 KanjiVerb( 乗り越える ) // (v1,vi) to climb over/to ride across/to surmount/(P)
 KanjiVerb( 乗り過ごす ) // (v5s) to ride past
 KanjiVerb( 乗り合わす ) // (v5s,vi) to happen to ride together/to share a vehicle
 KanjiVerb( 乗り合わせる ) // (v1) to happen to ride together/to share a vehicle/to (operate a) carpool
 KanjiVerb( 乗り込む ) // (v5m,vi) (1) to board/to embark on/to get into (a car)/to ship (passengers)/to man (a ship)/to help (someone) into/(2) to march into/to enter/(P)
 KanjiVerb( 乗り進める ) // (v1) to ride forth
 KanjiVerb( 乗り組む ) // (v5m,vi) to get on aboard/to join a ship
 KanjiVerb( 乗り損なう ) // (v5u) to miss (a train)
 KanjiVerb( 乗り遅れる ) // (v1,vi) to miss (train, bus, etc)/(P)
 KanjiVerb( 乗り潰す ) // (v5s) to ride (a horse) to death
 KanjiVerb( 乗り飛ばす ) // (v5s) to tear along (a road)
 KanjiVerb( 乗り付ける ) // (v1,vi) to ride up to/to get used to riding
 KanjiVerb( 乗り戻す ) // (v5s) to ride (a horse) back/to drive (a car) back
 KanjiVerb( 蒸ける ) // (v1,vi) to become ready to eat (as a result of steaming)
 KanjiVerb( 蒸れる ) // (v1,vi) to be stuffy/to moulder/to molder
 KanjiVerb( 嘱する ) // (vs-s) to belong to/to come under/to be affiliated with/to be subject to
 KanjiVerb( 拭き消す ) // (v5s) to wipe out/to erase
 KanjiVerb( 植え替える ) // (v1) to transplant/to reset
 KanjiVerb( 殖える ) // (v1,vi) to increase/to multiply/(P)
 KanjiVerb( 色めき立つ ) // (v5t,vi) to become excited
 KanjiVerb( 色めく ) // (v5k,vi) to colour/to color/to be tinged/to brighten/to grow lively/to become excited/to be stirred
 KanjiVerb( 色眼鏡で見る ) // (v1) to look at things from a biased viewpoint (biassed)
 KanjiVerb( 色付く ) // (v5k,vi) to change color/to change colour
 KanjiVerb( 色褪せる ) // (v1,vi) to fade/to grow stale/to grow dull in color (colour)
 KanjiVerb( 色褪める ) // (v1) to fade in color/to fade in colour
 KanjiVerb( 触れる ) // (v1) to touch/to be touched/to touch on a subject/to feel/to violate (law, copyright, etc.)/to perceive/to be emotionally moved/(P)
 KanjiVerb( 触れ合う ) // (v5u) to come into contact with/to touch (each other)/(P)
 KanjiVerb( 食いっぱぐれる ) // (v1) to miss a meal/to lose the means to make one's livelihood
 KanjiVerb( 食いっ逸れる ) // (v1) to miss a meal/to lose the means to make one's livelihood
 KanjiVerb( 食いつく ) // (v5k,vi) (1) to bite at/to snap at/to nibble/(2) to hold with the teeth/to cling to
 KanjiVerb( 食いつなぐ ) // (v5g,vi) (1) to ration out and survive on (some food)/(2) to eke out a living
 KanjiVerb( 食い違う ) // (v5u,vi) to cross each other/to run counter to/to differ/to clash/to go awry/(P)
 KanjiVerb( 食い逸れる ) // (v1,vi) to miss a meal/to lose the means to make one's livelihood
 KanjiVerb( 食い延ばす ) // (v5s) to keep alive on/to stretch food to make ends meet
 KanjiVerb( 食い繋ぐ ) // (v5g,vi) (1) to ration out and survive on (some food)/(2) to eke out a living
 KanjiVerb( 食い荒す ) // (v5s) to wolf down
 KanjiVerb( 食い合う ) // (v5u) to fit together
 KanjiVerb( 食い合わす ) // (v5s) to clench
 KanjiVerb( 食い込む ) // (v5m,vi) to eat into/(P)
 KanjiVerb( 食い伸ばす ) // (v5s) to keep alive on/to stretch food to make ends meet
 KanjiVerb( 食い尽くす ) // (v5s) to consume
 KanjiVerb( 食い付く ) // (v5k,vi) (1) to bite at/to snap at/to nibble/(2) to hold with the teeth/to cling to
 KanjiVerb( 食する ) // (vs-s) to eat
 KanjiVerb( 食べ散らす ) // (v5s) to eat a bit of everything
 KanjiVerb( 食べ尽くす ) // (v5s) to eat up
 KanjiVerb( 食み出す ) // (v5s,vi) (1) to be forced out/be crowded out/(2) to jut out (of bounds)/(P)
 KanjiVerb( 食み出る ) // (v1,vi) (1) to jut out (of bounds)/(2) to be crowded out/to to be forced out/(P)
 KanjiVerb( 食らい込む ) // (v5m,vi) to be sent up/to be imprisoned/to be jailed/to be gaoled
 KanjiVerb( 食らい付く ) // (v5k,vi) (1) to bite at/to snap at/to nibble/(2) to hold with the teeth/to cling to
 KanjiVerb( 食らわす ) // (v5s) to make someone eat/to deal (a blow)/to play (a trick)
 KanjiVerb( 食わす ) // (v5s) (1) to feed/(2) to provide/(3) to inflict/(4) to cheat
 KanjiVerb( 食違う ) // (v5u,vi) to cross each other/to run counter to/to differ/to clash/to go awry/(P)
 KanjiVerb( 食付く ) // (v5k,vi) (1) to bite at/to snap at/to nibble/(2) to hold with the teeth/to cling to
 KanjiVerb( 蝕む ) // (v5m,vi) to eat into (e.g., by worms)/to spoil/to ruin/to undermine/(P)
 KanjiVerb( 伸し歩く ) // (v5k,vi) to swagger
 KanjiVerb( 伸す ) // (v5s) to stretch/to spread/to smooth out/to roll out/to iron/to extend/to gain influence/to knock out
 KanjiVerb( 伸びる ) // (v1,vi) (1) to stretch/to extend/to lengthen/to spread/(v1,vi) (2) to make progress/to grow (beard, body height)/(v1,vi) (3) to grow stale (soba)/(v1,vi) (4) to be straightened/to be flattened/to be smoothed/(v1,vi) (5) to be exhausted/(P)
 KanjiVerb( 伸び悩む ) // (v5m,vi) to be sluggish (business)/(P)
 KanjiVerb( 信じ込ます ) // (v5s) to lead to believe
 KanjiVerb( 信じ込む ) // (v5m) to believe implicitly/to believe firmly
 KanjiVerb( 寝かす ) // (v5s) to put to sleep/to lay (something) on its side/(P)
 KanjiVerb( 寝ころぶ ) // (v5b,vi) (uk) to lie down/to throw oneself down
 KanjiVerb( 寝つく ) // (v5k,vi) (1) to go to bed/to go to sleep/to fall asleep/(2) to be laid up (with a cold)/to be ill in bed
 KanjiVerb( 寝ぼける ) // (v1,vi) to be half asleep/to be still only half awake/(P)
 KanjiVerb( 寝る ) // (v1,vi) to go to bed/to lie down/to sleep/(P)
 KanjiVerb( 寝違える ) // (v1,vi) to sleep in an awkward position and wake with a crick in one's neck
 KanjiVerb( 寝過ぎる ) // (v1,vi) to oversleep
 KanjiVerb( 寝過ごす ) // (v5s) to oversleep/(P)
 KanjiVerb( 寝覚める ) // (v1) to wake up
 KanjiVerb( 寝惚ける ) // (v1,vi) to be half asleep/to be still only half awake
 KanjiVerb( 寝込む ) // (v5m,vi) to stay in bed/to sleep/to be laid up for a long time
 KanjiVerb( 寝損なう ) // (v5u) to miss a chance to sleep/to be wakeful
 KanjiVerb( 寝直す ) // (v5s) to go back to bed
 KanjiVerb( 寝転ぶ ) // (v5b,vi) (uk) to lie down/to throw oneself down/(P)
 KanjiVerb( 寝付く ) // (v5k,vi) (1) to go to bed/to go to sleep/to fall asleep/(2) to be laid up (with a cold)/to be ill in bed/(P)
 KanjiVerb( 寝付けす ) // (v5s) to put (someone) to bed
 KanjiVerb( 寝忘れる ) // (v1,vi) to oversleep
 KanjiVerb( 心する ) // (vs-s) to take care/to mind/to be attentive
 KanjiVerb( 心を捉える ) // (v1) to impress/to charm
 KanjiVerb( 心行く ) // (v5k-s,vi) to be completely satisfied or contented
 KanjiVerb( 振られる ) // (v1,vi) to give someone the cold shoulder/to be jilted/to be rejected
 KanjiVerb( 振り下ろす ) // (v5s) to swing downward
 KanjiVerb( 振り起こす ) // (v5s) to stir up/to stimulate
 KanjiVerb( 振り仰ぐ ) // (v5g,vi) to look up
 KanjiVerb( 振り向く ) // (v5k) to turn one's face/to turn around/(P)
 KanjiVerb( 振り込む ) // (v5m) to make a payment via bank deposit transfer/(P)
 KanjiVerb( 振り返す ) // (v5s) to relapse/to reassert
 KanjiVerb( 振るい落とす ) // (v5s) to shake off
 KanjiVerb( 振るう ) // (v5u) to flourish/to prosper/to thrive
 KanjiVerb( 振れる ) // (v1,vi) to lean towards/to deflect/to shake/to swing/to wave
 KanjiVerb( 浸ける ) // (v1) to dip in/to soak
 KanjiVerb( 浸みる ) // (v1,vi) (1) to pierce/to penetrate/to soak in/to permeate/(2) to be infected (with vice)/to be steeped (with prejudice)
 KanjiVerb( 申し開らく ) // (v5k) to explain/to justify
 KanjiVerb( 申し兼ねる ) // (v1) I'm sorry to trouble you
 KanjiVerb( 申し合わせる ) // (v1) to arrange/to make an appointment/to agree upon
 KanjiVerb( 申し遅れる ) // (v1) to be slow in saying
 KanjiVerb( 真で書く ) // (v5k) to write in the square style
 KanjiVerb( 親しむ ) // (v5m,vi) to be intimate with/to befriend/(P)
 KanjiVerb( 診る ) // (v1) to examine (medical)/(P)
 KanjiVerb( 身じろぐ ) // (v5g,vi) to stir/to move
 KanjiVerb( 身にしみる ) // (v1) to sink deeply into one's mind/to come home to/to go to one's heart
 KanjiVerb( 身に染みる ) // (v1) to sink deeply into one's mind/to come home to/to go to one's heart
 KanjiVerb( 身に沁みる ) // (v1) to sink deeply into one's mind/to come home to/to go to one's heart
 KanjiVerb( 身ぶりで示す ) // (v5s) to express by gestures
 KanjiVerb( 身をかがめる ) // (v1) to stoop/to bend over
 KanjiVerb( 身を寄せ合う ) // (v5u) to go into a huddle
 KanjiVerb( 身を投じる ) // (v1) to throw oneself (into an activity)
 KanjiVerb( 身構える ) // (v1,vi) to put oneself on guard/to stand ready/to square off
 KanjiVerb( 身振りで示す ) // (v5s) to express by gestures
 KanjiVerb( 進み出る ) // (v1,vi) to step forward/to volunteer
 KanjiVerb( 進む ) // (v5m,vi) to make progress/to advance/to improve/(P)
 KanjiVerb( 針で刺す ) // (v5s) to prick with a needle
 KanjiVerb( 震い付く ) // (v5k,vi) to hug
 KanjiVerb( 震う ) // (v5u) to shake/to tremble/to vibrate
 KanjiVerb( 震える ) // (v1,vi) to shiver/to shake/to quake/(P)
 KanjiVerb( 震え出す ) // (v5s) to begin to tremble
 KanjiVerb( 震撼させる ) // (v1) to shock/to shake
 KanjiVerb( 人一倍働く ) // (v5k) to work twice as hard as others
 KanjiVerb( 人慣れる ) // (v1,vi) to become accustomed to people
 KanjiVerb( 人馴れる ) // (v1,vi) to become accustomed to people
 KanjiVerb( 刃向かう ) // (v5u,vi) to strike back at/to bite back/to turn on/to rise against/to oppose/to defy
 KanjiVerb( 尽きる ) // (v1,vi) to be used up/to be run out/to be exhausted/to be consumed/to come to an end/(P)
 KanjiVerb( 尽き果てる ) // (v1,vi) to be exhausted
 KanjiVerb( 尽くす ) // (v5s) (1) to exhaust/to run out/(2) to devote/to serve (a person)/to befriend/(P)
 KanjiVerb( 訊く ) // (v5k) to ask
 KanjiVerb( 図抜ける ) // (v1,vi) to tower above/to stand out
 KanjiVerb( 吹きこぼれる ) // (v1,vi) to boil over
 KanjiVerb( 吹き下ろす ) // (v5s,vi) to blow down upon
 KanjiVerb( 吹き荒ぶ ) // (v5b,vi) to blow fiercely/to rage
 KanjiVerb( 吹き荒む ) // (v5m) to blow violently
 KanjiVerb( 吹き荒れる ) // (v1,vi) to blow violently/to sweep over/to devastate
 KanjiVerb( 吹き込む ) // (v5m) to blow into/to breathe into/to inspire/to lay down a recording (music, video, etc.)/to indoctrinate/(P)
 KanjiVerb( 吹き始める ) // (v1) to begin to blow
 KanjiVerb( 吹き出す ) // (v5s,vi) to spout/to spurt/to gush out/to burst into laughter/(P)
 KanjiVerb( 吹き出る ) // (v1,vi) to blow out/to spout out
 KanjiVerb( 吹き抜く ) // (v5k) to blow through/to blow over/to blow itself out
 KanjiVerb( 吹き抜ける ) // (v1) to blow through
 KanjiVerb( 吹き飛ぶ ) // (v5b,vi) to be blown off/to blow off/(P)
 KanjiVerb( 吹き返す ) // (v5s) to blow in the opposite direction/to revive
 KanjiVerb( 吹き落とす ) // (v5s) to blow down (fruit)
 KanjiVerb( 吹く ) // (v5k) (1) to blow (wind, etc)/(2) to emit/to spout/(P)
 KanjiVerb( 吹っ切れる ) // (v1,vi) to break through/to become unbound by/to ooze out
 KanjiVerb( 吹っ飛ぶ ) // (v5b,vi) to blow off/to be blown off
 KanjiVerb( 吹雪く ) // (v5k,vi) to blow snow violently
 KanjiVerb( 垂らし込む ) // (v5m) to drop into, drop-by-drop
 KanjiVerb( 垂れる ) // (v1,vi) (1) to hang/to droop/to dangle/to sag/to lower/to pull down/(2) to leave behind (at death)/to give/to confer/(3) to drip/to ooze/to trickle/to drop/(P)
 KanjiVerb( 垂れ流す ) // (v5s) to discharge (e.g., effluent)
 KanjiVerb( 垂れ篭める ) // (v1) to hang over (e.g., clouds)/to lie over
 KanjiVerb( 水で薄める ) // (v1) to water down/to dilute with water
 KanjiVerb( 水際立つ ) // (v5t,vi) to be splendid/to be superb
 KanjiVerb( 炊ける ) // (v1) to be boiled/to be cooked/to be done/to be ready
 KanjiVerb( 衰える ) // (v1,vi) to become weak/to decline/to wear/to abate/to decay/to wither/to waste away/(P)
 KanjiVerb( 衰え果てる ) // (v1,vi) to be utterly spent or crushed
 KanjiVerb( 酔いしれる ) // (v1,vi) to be befuddled (drunk, intoxicated) (with)
 KanjiVerb( 酔い痴れる ) // (v1,vi) to be befuddled (drunk, intoxicated) (with)
 KanjiVerb( 酔い潰れる ) // (v1,vi) to drink oneself dead drunk
 KanjiVerb( 酔う ) // (v5u,vi) to get drunk/to become intoxicated/(P)
 KanjiVerb( 酔っ払う ) // (v5u,vi) to get drunk/(P)
 KanjiVerb( 崇う ) // (v5u) to look up to/to respect
 KanjiVerb( 嵩む ) // (v5m,vi) to pile up/to increase
 KanjiVerb( 数え違える ) // (v1) to miscount/to count wrongly (e.g., pages)
 KanjiVerb( 数え込む ) // (v5m) to number among
 KanjiVerb( 数え直す ) // (v5s) to count again
 KanjiVerb( 数に入れる ) // (v1) to count/to include in the number
 KanjiVerb( 澄む ) // (v5m,vi) to clear (e.g., weather)/to become transparent/(P)
 KanjiVerb( 世に出る ) // (v1) to become famous
 KanjiVerb( 世に立つ ) // (v5t) to become famous
 KanjiVerb( 世慣れる ) // (v1,vi) to become used to the (ways of the) world/to become worldly or sophisticated
 KanjiVerb( 世馴れる ) // (v1,vi) to become used to the (ways of the) world/to become worldly or sophisticated
 KanjiVerb( 凄む ) // (v5m,vi) to threaten
 KanjiVerb( 制する ) // (vs-s) to control/to command/to get the better of/(P)
 KanjiVerb( 勢い込む ) // (v5m,vi) to brace oneself
 KanjiVerb( 勢い付く ) // (v5k,vi) to gather strength/to take heart
 KanjiVerb( 征く ) // (v5k) to conquer/to subjugate
 KanjiVerb( 成り果てる ) // (v1,vi) to be reduced to ..
 KanjiVerb( 成り込む ) // (v5m) to incorporate (shoji)
 KanjiVerb( 成り済ます ) // (v5s,vi) to pose as/to impersonate
 KanjiVerb( 成果てる ) // (v1,vi) to be reduced to ..
 KanjiVerb( 整う ) // (v5u,vi) to be prepared/to be in order/to be put in order/to be arranged/(P)
 KanjiVerb( 晴れる ) // (v1,vi) to be sunny/to clear away/to stop raining/(P)
 KanjiVerb( 棲む ) // (v5m,vi) to live/to (of animals) inhabit
 KanjiVerb( 正気づく ) // (v5k) to become conscious/to recover one's senses
 KanjiVerb( 清む ) // (v5m,vi) to clear (e.g., weather)/to become transparent
 KanjiVerb( 清濁併せ呑む ) // (v5m) to be broad-minded enough to associate with various types of people/to possess a capacious mind
 KanjiVerb( 生う ) // (v5u) (1) to grow/to spring up/(2) to cut (teeth)
 KanjiVerb( 生える ) // (v1,vi) (1) to grow/to spring up/(2) to cut (teeth)/(P)
 KanjiVerb( 生きて行く ) // (v5k-s) to subsist
 KanjiVerb( 生きる ) // (v1,vi) to live/to exist/(P)
 KanjiVerb( 生き延びる ) // (v1,vi) to survive/to live long
 KanjiVerb( 生き長らえる ) // (v1,vi) to live long/to survive
 KanjiVerb( 生き抜く ) // (v5k,vi) to live through/to survive
 KanjiVerb( 生き埋める ) // (v1) to bury (somebody) alive
 KanjiVerb( 生じる ) // (v1,vi) to produce/to yield/to result from/to arise/to be generated/(P)
 KanjiVerb( 生ずる ) // (vz,vi) to cause/to arise/to be generated/(P)
 KanjiVerb( 生で飲む ) // (v5m) to drink (whisky, whiskey) straight
 KanjiVerb( 生まれつく ) // (v5k,vi) (1) to be born/(2) to be destined
 KanjiVerb( 生まれる ) // (v1,vi) to be born/(P)
 KanjiVerb( 生まれ合わせる ) // (v1) to happen to be born
 KanjiVerb( 生まれ付く ) // (v5k,vi) (1) to be born/(2) to be destined
 KanjiVerb( 生まれ落ちる ) // (v1) to be born
 KanjiVerb( 生れる ) // (v1,vi) to be born
 KanjiVerb( 生れ付く ) // (v5k,vi) (1) to be born/(2) to be destined
 KanjiVerb( 盛り合わせる ) // (v1) to heap with/to assort
 KanjiVerb( 精出す ) // (v5s,vi) to exert oneself
 KanjiVerb( 声をかける ) // (v1) to greet/to call out to someone
 KanjiVerb( 声を掛ける ) // (v1) to greet/to call out to someone
 KanjiVerb( 声を立てる ) // (v1) to let out a cry/to shout
 KanjiVerb( 製する ) // (vs-s) to make (something)
 KanjiVerb( 誓い交わす ) // (v5s) to vow to each other
 KanjiVerb( 逝く ) // (v5k-s,vi) to die/to pass away
 KanjiVerb( 醒める ) // (v1,vi) to awake (wake up)/to come to one's senses/to get sober
 KanjiVerb( 青ざめる ) // (v1,vi) to become pale/to turn pale/(P)
 KanjiVerb( 青褪める ) // (v1,vi) to become pale/to turn pale
 KanjiVerb( 斥く ) // (v5k,vi) (1) to retreat/to recede/to withdraw/(v5k,vi) (2) to retire
 KanjiVerb( 昔を顧みる ) // (v1) to look back upon the past
 KanjiVerb( 積み下ろす ) // (v5s) to unload
 KanjiVerb( 積み過ぎる ) // (v1) to overload
 KanjiVerb( 積む ) // (v5m) to pile up/to stack/(P)
 KanjiVerb( 責め苛む ) // (v5m) to torture
 KanjiVerb( 赤らむ ) // (v5m,vi) to become red/to redden/to blush
 KanjiVerb( 赤茶ける ) // (v1,vi) to turn reddish-brown/to turn rufous/to become discolored/to become discoloured
 KanjiVerb( 跡切れる ) // (v1,vi) to pause/to be interrupted
 KanjiVerb( 跡絶える ) // (v1,vi) to stop/to cease/to come to an end
 KanjiVerb( 切り過ぎる ) // (v1) to overcut
 KanjiVerb( 切り拡げる ) // (v1) to cut and enlarge
 KanjiVerb( 切り起こす ) // (v5s) to open up waste land for cultivation
 KanjiVerb( 切り結ぶ ) // (v5b,vi) to cross swords with
 KanjiVerb( 切り枯らす ) // (v5s) to destroy/to kill off (trees)
 KanjiVerb( 切り合う ) // (v5u,vi) to fight with swords/to cross swords
 KanjiVerb( 切り込む ) // (v5m,vi) to cut into/to raid/to attack/to cut up
 KanjiVerb( 切り除ける ) // (v1) to cut off/to cut out
 KanjiVerb( 切り据える ) // (v1) to cut down an enemy
 KanjiVerb( 切り整える ) // (v1) to cut and prepare (stones)
 KanjiVerb( 切り拓く ) // (v5k) to open up
 KanjiVerb( 切り直す ) // (v5s) to correct cutting/to reshuffle (playing cards)
 KanjiVerb( 切り入れる ) // (v1) to cut and insert
 KanjiVerb( 切り抜く ) // (v5k) to cut out/to clip from/to extract
 KanjiVerb( 切り分かつ ) // (v5t) to cut up
 KanjiVerb( 切り分ける ) // (v1) to cut up/to cut and discard/to eliminate systematically (in fault-finding)
 KanjiVerb( 切り離れる ) // (v1) to cut off and separate
 KanjiVerb( 切り立つ ) // (v5t) to rise perpendicularly
 KanjiVerb( 切れる ) // (v1,vi) (1) to cut well/to be sharp/(2) to break (off)/to snap/to wear out/(3) to be injured/(4) to burst/to collapse/(5) to be disconnected/to be out of/to expire/to sever (connections) with/(6) to be shrewd/to have a sharp mind/(P)
 KanjiVerb( 切れ込む ) // (v5m,vi) to cut into
 KanjiVerb( 切欠く ) // (v5k) to (cut a) notch (in)
 KanjiVerb( 接ぎ合わせる ) // (v1) to join or patch together
 KanjiVerb( 接ぎ足す ) // (v5s) to extend/to add
 KanjiVerb( 接する ) // (vs-s) (1) to come in contact with/to touch/to connect (with)/(2) to attend (to)/(3) to receive (visitors)/(P)
 KanjiVerb( 折り合う ) // (v5u,vi) to compromise
 KanjiVerb( 折れる ) // (v1,vi) to break/to be folded/to give in/to turn (a corner)/(P)
 KanjiVerb( 折れ合う ) // (v5u,vi) to get along with/to compromise/to make concessions/to come to an agreement
 KanjiVerb( 折れ込む ) // (v5m,vi) to be folded under or inside
 KanjiVerb( 節する ) // (vs-s) to be moderate of/to save/to curtail
 KanjiVerb( 節榑立つ ) // (v5t,vi) to be knotty or gnarled
 KanjiVerb( 説き起こす ) // (v5s) to begin one's argument or story or lecture
 KanjiVerb( 説き及ぶ ) // (v5b,vi) to mention/to refer to/to touch upon
 KanjiVerb( 説き出す ) // (v5s,vi) to begin to speak/to begin to explain
 KanjiVerb( 説く ) // (v5k) to explain/to advocate/to preach/to persuade/(P)
 KanjiVerb( 雪で被われる ) // (v1) to be covered with snow
 KanjiVerb( 雪崩れ込む ) // (v5m,vi) to rush or crowd into/to surge into
 KanjiVerb( 絶える ) // (v1,vi) (1) to die out/to peter out/to become extinct/(2) to cease/to be stopped/to be discontinued/to be cut off/(P)
 KanjiVerb( 絶え果てる ) // (v1,vi) to be extinguished/to be exterminated/to cease completely
 KanjiVerb( 絶する ) // (vs-s) to be unspeakable/to be unimaginable
 KanjiVerb( 先んじる ) // (v1,vi) to precede/to forestall/to anticipate
 KanjiVerb( 先んずる ) // (vz,vi) to go before/to precede/to forestall/to anticipate
 KanjiVerb( 先駆ける ) // (v1,vi) to be the first/(P)
 KanjiVerb( 先立つ ) // (v5t,vi) to lead/to precede/to die before someone/to go before/to take precedence
 KanjiVerb( 千切れる ) // (v1) to be torn off/to be torn to pieces/(P)
 KanjiVerb( 占い当てる ) // (v1) to divine
 KanjiVerb( 宣う ) // (v5u) to say (polite)/to be pleased say (hint of sarcasm)
 KanjiVerb( 宣する ) // (vs-s) to announce/to declare
 KanjiVerb( 戦い抜く ) // (v5k) to fight to the bitter end
 KanjiVerb( 戦う ) // (v5u,vi) to fight/to battle/to combat/to struggle against/to wage war/to engage in contest/(P)
 KanjiVerb( 戦えば乃ち勝つ ) // (v5t) to win every battle (that is fought)
 KanjiVerb( 戦ぐ ) // (v5g,vi) to rustle/to stir/to flutter
 KanjiVerb( 戦慄く ) // (v5k,vi) to tremble/to shiver
 KanjiVerb( 洗い清める ) // (v1) to wash clean/to cleanse
 KanjiVerb( 洗い分ける ) // (v1) to separate by washing
 KanjiVerb( 洗い落とす ) // (v5s) to wash off/to wash out
 KanjiVerb( 染みる ) // (v1,vi) (1) to pierce/to penetrate/to soak in/to permeate/(2) to be infected (with vice)/to be steeped (with prejudice)/(P)
 KanjiVerb( 染み込む ) // (v5m,vi) to soak into/to permeate
 KanjiVerb( 染み出る ) // (v1,vi) to ooze/to exude/to percolate/to soak through
 KanjiVerb( 染み着く ) // (v5k,vi) to be indelibly stained or ingrained/to be dyed in deeply
 KanjiVerb( 染み付く ) // (v5k,vi) to be indelibly stained or ingrained/to be dyed in deeply
 KanjiVerb( 染着く ) // (v5k,vi) to be indelibly stained or ingrained/to be dyed in deeply
 KanjiVerb( 染付く ) // (v5k,vi) to be indelibly stained or ingrained/to be dyed in deeply
 KanjiVerb( 潜む ) // (v5m,vi) to lurk/to lie dormant/to be hidden/(P)
 KanjiVerb( 潜り込む ) // (v5m,vi) to slip into/to crawl into (under)/to conceal oneself (under)
 KanjiVerb( 潜り抜ける ) // (v1,vi) to go through/to pass through/to escape (through the cordon)/to evade (the law)
 KanjiVerb( 煎りつく ) // (v5k) to be scorched/to boil down
 KanjiVerb( 選ばれる ) // (v1) to be elected
 KanjiVerb( 閃く ) // (v5k,vi) flash (of thunder)/flicker (of lights)/(P)
 KanjiVerb( 全うする ) // (vs-s) to accomplish/to fulfill/to carry out
 KanjiVerb( 繕い立てる ) // (v1) to put up a good front
 KanjiVerb( 措く ) // (v5k) to give up/to except
 KanjiVerb( 素っ飛ぶ ) // (v5b,vi) to rush off/to rush away/to vanish
 KanjiVerb( 組み合う ) // (v5u,vi) to form a partnership or association/to join together/to grapple with
 KanjiVerb( 組み合す ) // (v5s) to combine/to dovetail together
 KanjiVerb( 組み合わせる ) // (v1) to join together/to combine/to join up/(P)
 KanjiVerb( 組み直す ) // (v5s) to reschedule
 KanjiVerb( 組み付く ) // (v5k) to grapple/to wrestle
 KanjiVerb( 組む ) // (v5m) to put together/(P)
 KanjiVerb( 組織立つ ) // (v5t,vi) to have orderly plans/to be systematic
 KanjiVerb( 組付く ) // (v5k) to grapple/to wrestle
 KanjiVerb( 訴え出る ) // (v1) to lodge a complaint
 KanjiVerb( 阻む ) // (v5m) to keep someone from doing/to stop/to prevent/to check/to hinder/to obstruct/to oppose/to thwart/(P)
 KanjiVerb( 創り出す ) // (v5s) to fashion/to create
 KanjiVerb( 倉庫に納める ) // (v1) to store in a warehouse
 KanjiVerb( 奏でる ) // (v1,vi) to play (an instrument)/(P)
 KanjiVerb( 捜し求める ) // (v1) to search for/to seek for/to look for
 KanjiVerb( 掃き寄せる ) // (v1) to sweep up
 KanjiVerb( 掃き集める ) // (v1) to sweep up together
 KanjiVerb( 掻き起こす ) // (v5s) to stir up
 KanjiVerb( 掻き交ぜる ) // (v1) to mix/to stir/to scramble/to churn
 KanjiVerb( 掻き口説く ) // (v5k,vi) to complain/to pester
 KanjiVerb( 掻き混ぜる ) // (v1) to mix/to stir/to scramble/to churn
 KanjiVerb( 掻き消える ) // (v1,vi) to disappear
 KanjiVerb( 掻き暮れる ) // (v1) to be sad
 KanjiVerb( 掻き落とす ) // (v5s) to scrape off
 KanjiVerb( 巣くう ) // (v5u,vi) to build (a nest)/to haunt (a place)/to hang out (somewhere)
 KanjiVerb( 巣食う ) // (v5u) (1) to nest/to build a nest/(2) to hang out/to haunt
 KanjiVerb( 巣立つ ) // (v5t) to leave the nest
 KanjiVerb( 槍玉に上げる ) // (v1) to be criticized/to be criticised/to be made an example of
 KanjiVerb( 燥ぐ ) // (v5g,vi) (uk) to make merry/to frolic/to be in high spirits/(P)
 KanjiVerb( 争い戦う ) // (v5u) to fight with/to contend with
 KanjiVerb( 争い訴える ) // (v1) to accuse/to rise up in judgment against (judgement)
 KanjiVerb( 争う ) // (v5u,vi) (1) to dispute/to argue/to be at variance/(2) to compete/to contest/(3) to deny (e.g., evidence)/(P)
 KanjiVerb( 痩せこける ) // (v1,vi) to get too skinny
 KanjiVerb( 痩せる ) // (v1,vi) to become thin/to lose weight/to reduce (one's) weight/to slim/(P)
 KanjiVerb( 痩せ衰える ) // (v1,vi) to become emaciated/to grow thin and worn out
 KanjiVerb( 相携える ) // (v1) to do something together
 KanjiVerb( 相次ぐ ) // (v5g) to follow in succession/(P)
 KanjiVerb( 相伴う ) // (v5u) to accompany
 KanjiVerb( 相和す ) // (v5s) to grow together/to join together (in doing something)
 KanjiVerb( 総毛立つ ) // (v5t,vi) to relate a hair-raising account or experience
 KanjiVerb( 草臥れる ) // (v1,vi) to get tired/to wear out/(P)
 KanjiVerb( 藻掻く ) // (v5k) (1) to struggle/to wriggle/to squirm/(2) to be impatient/(P)
 KanjiVerb( 走りかける ) // (v1) to start running
 KanjiVerb( 走り掛ける ) // (v1) to start running
 KanjiVerb( 走り込む ) // (v5m,vi) to run into (a building)
 KanjiVerb( 走り出す ) // (v5s) to begin to run/to start running/(P)
 KanjiVerb( 走り出る ) // (v1) to run out (e.g., of the room)
 KanjiVerb( 走り続ける ) // (v1) to keep running
 KanjiVerb( 走り抜く ) // (v5k) to outrun/to run through to the end
 KanjiVerb( 走り抜ける ) // (v1,vi) to run through
 KanjiVerb( 送り返す ) // (v5s) to send back/(P)
 KanjiVerb( 遭う ) // (v5u,vi) to meet/to encounter (undesirable nuance)/(P)
 KanjiVerb( 霜枯れる ) // (v1,vi) to be withered or nipped by frost
 KanjiVerb( 騒ぎ立てる ) // (v1,vi) to make a fuss (outcry, uproar)
 KanjiVerb( 騒ぐ ) // (v5g,vi) to make noise/to clamor/to be excited/to be alarmed/to kick up a fuss/to make merry/to be annoying/to be troublesome/to make a noise/(P)
 KanjiVerb( 騒めく ) // (v5k,vi) (uk) to be noisy/to be astir/to rustle/(P)
 KanjiVerb( 増える ) // (v1,vi) to increase/to multiply/(P)
 KanjiVerb( 増え続ける ) // (v1) to continue to increase/to continue to mount
 KanjiVerb( 増す ) // (v5s,vi) to increase/to grow/(P)
 KanjiVerb( 造りつける ) // (v1) to build in
 KanjiVerb( 造り付ける ) // (v1) to build in
 KanjiVerb( 側む ) // (v5m,vi) to lean to one side/to oppose/to look aside/to regret
 KanjiVerb( 即する ) // (vs-s) to conform to/to agree with/to be adapted to/to be based on/(P)
 KanjiVerb( 息づく ) // (v5k,vi) to breathe (heavily)/to pant/to gasp/to sigh
 KanjiVerb( 息む ) // (v5m,vi) (1) to strain (e.g., with constipation)/(2) to bear or push down (during childbirth)
 KanjiVerb( 息を弾ませる ) // (v1) to pant/to gasp/to be short of breath/to be excited
 KanjiVerb( 息巻く ) // (v5k,vi) to enrage/to infuriate
 KanjiVerb( 息衝く ) // (v5k,vi) to breathe (heavily)/to pant/to gasp/to sigh
 KanjiVerb( 束ね積む ) // (v5m) to shock (grain)
 KanjiVerb( 足が出る ) // (v1) to exceed the budget/to do not cover the expense
 KanjiVerb( 足りる ) // (v1,vi) to be sufficient/to be enough/(P)
 KanjiVerb( 足掻く ) // (v5k,vi) (1) to paw (at) the ground/(2) to flounder/to struggle
 KanjiVerb( 属する ) // (vs-s) to belong to/to come under/to be affiliated with/to be subject to/(P)
 KanjiVerb( 続く ) // (v5k,vi) to be continued/(P)
 KanjiVerb( 卒する ) // (vs-s) to die/to pass away
 KanjiVerb( 揃う ) // (v5u,vi) to become complete/to be equal/to be all present/to gather/(P)
 KanjiVerb( 存じる ) // (v1) (hum) to know/(P)
 KanjiVerb( 存ずる ) // (vz,vi) (hum) to think, feel, consider, know, etc.
 KanjiVerb( 損じる ) // (v1,vi) to harm/to hurt/to injure/to damage
 KanjiVerb( 損する ) // (vs-s) to lose/(P)
 KanjiVerb( 多すぎる ) // (v1) to be too numerous/to be too much
 KanjiVerb( 多過ぎる ) // (v1) to be too numerous/to be too much
 KanjiVerb( 堕する ) // (vs-s) to degenerate/to lapse into
 KanjiVerb( 堕ちる ) // (v1,vi) (1) to fall down/to drop/(2) to fail (e.g., exam)/(3) to crash/to degenerate/to degrade/(4) to fade/to come out (e.g., a stain)
 KanjiVerb( 堕つ ) // (v5t,vi) (1) to fall down/to drop/(2) to fail (e.g., exam)/(3) to crash/to degenerate/to degrade
 KanjiVerb( 堕ろす ) // (v5s) to abort (negative nuance)
 KanjiVerb( 打たれる ) // (v1,vi) to be struck/to be beaten
 KanjiVerb( 打ちひしがれる ) // (v1) to be stricken (e.g., with grief)/to be battered (e.g., by disasters)
 KanjiVerb( 打ち萎れる ) // (v1,vi) to droop/to be depressed
 KanjiVerb( 打ち過ぎる ) // (v1,vi) to pass by (time)/to hit too much
 KanjiVerb( 打ち解ける ) // (v1,vi) to open one's heart/to throw off reserve/to be frank
 KanjiVerb( 打ち噛ます ) // (v5s,vi) to strike the face (from sumo)/to punch hard
 KanjiVerb( 打ち寄せる ) // (v1) to break onto (shore)/to wash ashore/to attack
 KanjiVerb( 打ち克つ ) // (v5t,vi) to overcome
 KanjiVerb( 打ち込む ) // (v5m) to drive in (e.g., nail, stake)/to devote oneself to/to shoot into/to smash/to throw into/to cast into
 KanjiVerb( 打ち勝つ ) // (v5t,vi) to conquer/to overcome
 KanjiVerb( 打ち続く ) // (v5k,vi) to long-continuing
 KanjiVerb( 打ち続ける ) // (v1) to hit repeatedly
 KanjiVerb( 打ち損なう ) // (v5u) to fail to hit/to miss
 KanjiVerb( 打ち沈む ) // (v5m,vi) to be depressed
 KanjiVerb( 打ち負かす ) // (v5s) to defeat
 KanjiVerb( 打ち返す ) // (v5s) to return a blow repeat/to turn back/to rewhip/to plow up/to plough up/to come and retreat
 KanjiVerb( 打ち滅ぼす ) // (v5s) to destroy
 KanjiVerb( 打ち連れる ) // (v1,vi) to go along with
 KanjiVerb( 打ち拉がれる ) // (v1) to be stricken (e.g., with grief)/to be battered (e.g., by disasters)
 KanjiVerb( 打って出る ) // (v1) to launch oneself upon/to make one's debut
 KanjiVerb( 打つ ) // (v5t) to hit/to strike/(P)
 KanjiVerb( 打続く ) // (v5k,vi) to long-continuing
 KanjiVerb( 対する ) // (vs-s) to face/to confront/to oppose/(P)
 KanjiVerb( 耐兼ねる ) // (v1,vi) to be unable to endure/to lose patience
 KanjiVerb( 待たす ) // (v5s) to keep (a person) waiting/(P)
 KanjiVerb( 待たせる ) // (v1) to keep (a person) waiting/(P)
 KanjiVerb( 待ちくたびれる ) // (v1) to get tired of waiting
 KanjiVerb( 待ち倦む ) // (v5m) to tire of waiting
 KanjiVerb( 待ち合わせる ) // (v1) to rendezvous/to meet at a prearranged place and time/(P)
 KanjiVerb( 待ち惚ける ) // (v1) to wait in vain
 KanjiVerb( 待ち伏せる ) // (v1) to ambush
 KanjiVerb( 待ち暮らす ) // (v5s) to wait all day
 KanjiVerb( 怠ける ) // (v1,vi) to be idle/to neglect/(P)
 KanjiVerb( 戴ける ) // (v1,vi) (1) (uk) to receive (potential)/(2) to be pretty good/to be exquisite/to be approvable
 KanjiVerb( 苔むす ) // (v5s,vi) to become covered in moss/to become aged
 KanjiVerb( 苔生す ) // (v5s) to have moss growing on itself
 KanjiVerb( 貸してあげる ) // (v1) to lend (e.g., money)
 KanjiVerb( 貸して上げる ) // (v1) to lend (e.g., money)
 KanjiVerb( 貸し下げる ) // (v1) to lend/to loan
 KanjiVerb( 退く ) // (v5k,vi) (1) to retreat/to recede/to withdraw
 KanjiVerb( 逮捕される ) // (v1) to be arrested
 KanjiVerb( 代り合う ) // (v5u,vi) to relieve each other/to take turns
 KanjiVerb( 大詰を迎える ) // (v1) to approach the finale/to come to a close
 KanjiVerb( 大人びる ) // (v1,vi) to become grown-up/to age/to mature
 KanjiVerb( 托する ) // (vs-s) to entrust
 KanjiVerb( 拓く ) // (v5k) to open (e.g., path)/to clear (the way)/to break up (e.g., land)
 KanjiVerb( 託す ) // (v5s) to entrust with/to make an excuse of/(P)
 KanjiVerb( 託する ) // (vs-s) to entrust
 KanjiVerb( 託つける ) // (v1) to use as an excuse/to pretend that
 KanjiVerb( 叩き会う ) // (v5u) to come to blows/to fight (each other)
 KanjiVerb( 叩き壊す ) // (v5s) to tear down/to shatter
 KanjiVerb( 叩き消す ) // (v5s) to beat out (a fire)
 KanjiVerb( 叩き潰す ) // (v5s) to smash up/to defeat crushingly
 KanjiVerb( 叩き落とす ) // (v5s) to knock down/to knock off
 KanjiVerb( 達する ) // (vs-s) to reach/to get to/(P)
 KanjiVerb( 奪い合う ) // (v5u) to scramble for/to struggle for
 KanjiVerb( 奪い返す ) // (v5s) to take back/to recapture
 KanjiVerb( 脱がす ) // (v5s) to strip someone/to help someone remove (clothes)
 KanjiVerb( 脱げる ) // (v1,vi) to come off/to slip down/to slip off
 KanjiVerb( 脱する ) // (vs-s) to escape from/to get out/(P)
 KanjiVerb( 辿り着く ) // (v5k,vi) to grope along to/to struggle on to/to arrive somewhere after a struggle
 KanjiVerb( 棚引く ) // (v5k) to linger/to hover above/to trail/to hang (lie) over
 KanjiVerb( 嘆き悲しむ ) // (v5m) to grieve and moan
 KanjiVerb( 嘆く ) // (v5k,vi) to sigh/to lament/to grieve/(P)
 KanjiVerb( 担ぎ込む ) // (v5m) to carry something into a place
 KanjiVerb( 探し求める ) // (v1) to search for/to seek for/to look for
 KanjiVerb( 歎く ) // (v5k,vi) to sigh/to lament/to grieve
 KanjiVerb( 歎じる ) // (v1,vi) to grieve/to lament/to sigh in admiration
 KanjiVerb( 歎ずる ) // (vz,vi) to grieve/to lament/to sigh in admiration
 KanjiVerb( 綻びる ) // (v1,vi) to come apart at the seams/to begin to open/to smile broadly/(P)
 KanjiVerb( 弾き返す ) // (v5s) to reject/to repel
 KanjiVerb( 弾く ) // (v5k) to play (piano, guitar)/(P)
 KanjiVerb( 弾ける ) // (v1,vi) to burst open/to split open/to pop
 KanjiVerb( 弾む ) // (v5m,vi) to spring/to bound/to bounce/to be stimulated/to be encouraged/to get lively/to treat oneself to/to splurge on/(P)
 KanjiVerb( 断える ) // (v1,vi) (1) to die out/to peter out/to become extinct/(2) to cease/to be stopped/to be discontinued/to be cut off
 KanjiVerb( 談じ込む ) // (v5m,vi) to have a talk with
 KanjiVerb( 値する ) // (vs-s) to be worth/to deserve/to merit/(P)
 KanjiVerb( 知っている ) // (v1) to know
 KanjiVerb( 知らす ) // (v5s) (polite) to know/to understand/to be acquainted with/to feel
 KanjiVerb( 知り合う ) // (v5u,vi) to get to know (someone)/to make acquaintance/(P)
 KanjiVerb( 知り始める ) // (v1) to begin to know
 KanjiVerb( 知れる ) // (v1,vi) to become known/to come to light/to be discovered/(P)
 KanjiVerb( 知ろし召す ) // (v5s) to reign
 KanjiVerb( 知合う ) // (v5u,vi) to get to know (someone)/to make acquaintance/(P)
 KanjiVerb( 地が出る ) // (v1) to reveal one's true colors/to reveal one's true colours/to betray oneself
 KanjiVerb( 地でいく ) // (v5k-s) to do for real/to do in real life/to carry (a story) into actual practice (practise)
 KanjiVerb( 地でゆく ) // (v5k-s) to do for real/to do in real life/to carry (a story) into actual practice (practise)
 KanjiVerb( 地で行く ) // (v5k-s) to do for real/to do in real life/to carry (a story) into actual practice (practise)
 KanjiVerb( 地の底深く ) // (v5k) to be deep in the bowels of the earth
 KanjiVerb( 地団駄踏む ) // (v5m) to stamp one's feet
 KanjiVerb( 弛む ) // (v5m,vi) to slacken/to loosen/to relax/(P)
 KanjiVerb( 恥じらう ) // (v5u,vi) to feel shy/to be bashful/to blush/(P)
 KanjiVerb( 恥じる ) // (v1,vi) to feel ashamed/(P)
 KanjiVerb( 恥らう ) // (v5u,vi) to feel shy/to be bashful/to blush
 KanjiVerb( 置き違える ) // (v1) to put something in the wrong place/to misplace
 KanjiVerb( 置く ) // (v5k) (1) to put/to place/(2) to leave (behind)/(3) (uk) to do something in advance (us. following te-form verb)/(P)
 KanjiVerb( 遅れる ) // (v1,vi) to be late/to be delayed/to fall behind schedule/to be overdue/(P)
 KanjiVerb( 馳せる ) // (v1,vi) to drive (car)/to ride (horse)/to win (fame)
 KanjiVerb( 馳せ参じる ) // (v1,vi) to hasten to join
 KanjiVerb( 茶々を入れる ) // (v1) to tease/to make fun of
 KanjiVerb( 茶化す ) // (v5s) to poke fun at/to make fun of
 KanjiVerb( 茶茶を入れる ) // (v1) to tease/to make fun of
 KanjiVerb( 着る ) // (v1) to wear/to put on (from shoulders down)/(P)
 KanjiVerb( 着換える ) // (v1) to change one's clothes
 KanjiVerb( 着込む ) // (v5m) to wear extra clothes
 KanjiVerb( 着替える ) // (v1) to change one's clothes/(P)
 KanjiVerb( 着直す ) // (v5s) to change clothes
 KanjiVerb( 着膨れる ) // (v1) to be thickly clad
 KanjiVerb( 宙で読む ) // (v5m) to recite from memory
 KanjiVerb( 注ぎいれる ) // (v1) to pour into
 KanjiVerb( 注ぎ入れる ) // (v1) to pour into
 KanjiVerb( 注ぐ ) // (v5g) to pour (into)/to irrigate/to pay/to fill/to feed (e.g., a fire)/(P)
 KanjiVerb( 虫食む ) // (v5m,vi) to eat into (e.g., by worms)/to spoil/to ruin/to undermine
 KanjiVerb( 鋳直す ) // (v5s) to recast/to recoin
 KanjiVerb( 兆す ) // (v5s,vi) to show signs (symptoms)
 KanjiVerb( 凋む ) // (v5m,vi) to wither/to fade (away)/to shrivel/to wilt/(P)
 KanjiVerb( 張り詰める ) // (v1,vi) to strain/to stretch/to string up/to make tense/to cover over/to freeze over
 KanjiVerb( 張り合う ) // (v5u,vi) to rival/to compete with
 KanjiVerb( 張り合わせる ) // (v1) to paste together
 KanjiVerb( 張り込む ) // (v5m) to be on the lookout/to lie in wait
 KanjiVerb( 張り出す ) // (v5s,vi) to put up a notice/to project/to jut out/(P)
 KanjiVerb( 張り付く ) // (v5k) to cling (to)
 KanjiVerb( 張り裂ける ) // (v1,vi) to burst (open)/to break/to split
 KanjiVerb( 張付く ) // (v5k) to cling (to)
 KanjiVerb( 彫り刻む ) // (v5m) to engrave/to carve
 KanjiVerb( 彫り上げる ) // (v1) to emboss/to carve in relief/to finish carving of engraving
 KanjiVerb( 懲りる ) // (v1,vi) to learn by experience/to be disgusted with/(P)
 KanjiVerb( 挑む ) // (v5m,vi) to challenge/to contend for/to make love to/(P)
 KanjiVerb( 潮の如く押し寄せる ) // (v1) to rush like a flood/to surge
 KanjiVerb( 潮垂れる ) // (v1,vi) to weep copiously/to grieve/to be dejected
 KanjiVerb( 聴き込む ) // (v5m) to have heard
 KanjiVerb( 聴き頂く ) // (v5k) to receive a hearing
 KanjiVerb( 聴こえる ) // (v1,vi) (1) to be heard/to be audible/(2) to be said to be/to be reputed
 KanjiVerb( 脹れる ) // (v1,vi) to get cross/to get sulky/to swell (out)/to expand/to be inflated/to distend/to bulge
 KanjiVerb( 調う ) // (v5u,vi) to be prepared/to be in order/to be put in order/to be arranged/(P)
 KanjiVerb( 調べて置く ) // (v5k) to examine beforehand
 KanjiVerb( 調べ合わす ) // (v5s) to tune to/to check against
 KanjiVerb( 調べ直す ) // (v5s) to re-examine/to review/to recheck
 KanjiVerb( 調子付く ) // (v5k,vi) to warm up to/to become enthusiastic about/to be elated
 KanjiVerb( 超える ) // (v1,vi) (1) to cross over/to cross/to pass through/to pass over (out of)/(2) to exceed/(P)
 KanjiVerb( 超す ) // (v5s) (1) to cross over (e.g., mountain)/to go across/(2) to go over (e.g., with audience)/(3) to pass (time, e.g., a winter)/(4) to surpass/to be better than/(5) to move house/(P)
 KanjiVerb( 跳ねかける ) // (v1) to splash/to blame on
 KanjiVerb( 跳ねる ) // (v1,vi) (1) to jump/to leap/to prance/to spring up/to bound/to hop/(2) to break up/to close/to come to an end/(3) to hit (e.g., to have a car hit something or someone)/(P)
 KanjiVerb( 跳ね掛ける ) // (v1) to splash/to blame on
 KanjiVerb( 跳ね起きる ) // (v1,vi) to jump up/to spring up
 KanjiVerb( 跳ね出す ) // (v5s) to spring or rush out
 KanjiVerb( 跳ね出る ) // (v1) to spring or rush out
 KanjiVerb( 跳ね返す ) // (v5s) to reject/to bounce back
 KanjiVerb( 跳び出す ) // (v5s) to leap out/to take off
 KanjiVerb( 跳び出る ) // (v1) to spring or rush out
 KanjiVerb( 跳び跳ねる ) // (v1,vi) to jump up and down/to hop
 KanjiVerb( 跳び付く ) // (v5k,vi) to jump at/to be attracted by
 KanjiVerb( 跳ぶ ) // (v5b,vi) to jump/to fly/to leap/to spring/to bound/to hop/(P)
 KanjiVerb( 跳付く ) // (v5k,vi) to jump at/to be attracted by
 KanjiVerb( 長ける ) // (v1,vi) (1) to excel at/to be proficient at/(2) to grow old/(3) to ripen/(4) to rise high (e.g., the sun)
 KanjiVerb( 長らえる ) // (v1,vi) to have a long life/to live a long time
 KanjiVerb( 長引く ) // (v5k,vi) to be prolonged/to drag on/(P)
 KanjiVerb( 長過ぎる ) // (v1) to be too long
 KanjiVerb( 頂ける ) // (v1,vi) (1) (uk) to receive (potential)/(2) to be pretty good/to be exquisite/to be approvable
 KanjiVerb( 沈む ) // (v5m,vi) to sink/to feel depressed/(P)
 KanjiVerb( 陳こびる ) // (v1,vi) to look old/to appear mature (e.g., of children)
 KanjiVerb( 陳ねこびる ) // (v1,vi) to look old/to appear mature (e.g., of children)
 KanjiVerb( 墜ちる ) // (v1,vi) (1) to fall down/to drop/(2) to fail (e.g., exam)/(3) to crash/to degenerate/to degrade/(4) to fade/to come out (e.g., a stain)
 KanjiVerb( 墜つ ) // (v5t,vi) (1) to fall down/to drop/(2) to fail (e.g., exam)/(3) to crash/to degenerate/to degrade
 KanjiVerb( 追いつく ) // (v5k,vi) to overtake/to catch up (with)/(P)
 KanjiVerb( 追い求める ) // (v1) to pursue
 KanjiVerb( 追い着く ) // (v5k,vi) to overtake/to catch up (with)
 KanjiVerb( 追い付く ) // (v5k,vi) to overtake/to catch up (with)/(P)
 KanjiVerb( 追い落とす ) // (v5s) to disperse/to take a castle
 KanjiVerb( 追っぱらう ) // (v5u) to chase away
 KanjiVerb( 追着く ) // (v5k,vi) to overtake/to catch up (with)
 KanjiVerb( 追付く ) // (v5k,vi) to overtake/to catch up (with)
 KanjiVerb( 痛む ) // (v5m) to hurt/to feel a pain/to be injured/(P)
 KanjiVerb( 通い詰める ) // (v1,vi) to visit frequently
 KanjiVerb( 通う ) // (v5u,vi) (1) to go back and forth/to ply between/(2) to commute/to attend (school, church, etc.)/(P)
 KanjiVerb( 通じる ) // (v1,vi) to run to/to lead to/to communicate/to understand/to be well-informed/(P)
 KanjiVerb( 通じ合う ) // (v5u) to communicate with/to understand
 KanjiVerb( 通ずる ) // (vz) to run to/to lead to/to communicate/to understand/to be well-informed
 KanjiVerb( 通り越す ) // (v5s,vi) to go past (a place or thing)/to go beyond
 KanjiVerb( 通り過ぎる ) // (v1,vi) to pass/to pass through/(P)
 KanjiVerb( 通り合わせる ) // (v1) to come across/to happen upon
 KanjiVerb( 通り抜ける ) // (v1,vi) to cut through/to go through
 KanjiVerb( 掴み合う ) // (v5u,vi) to grapple
 KanjiVerb( 綴り合わせる ) // (v1) to bind together
 KanjiVerb( 潰える ) // (v1,vi) to collapse
 KanjiVerb( 潰れる ) // (v1,vi) to be smashed/to go bankrupt/(P)
 KanjiVerb( 爪先立つ ) // (v5t,vi) to stand on tiptoes
 KanjiVerb( 爪弾く ) // (v5k) to strum/to pluck the strings (of a guitar)
 KanjiVerb( 爪立つ ) // (v5t) to stand on tiptoe
 KanjiVerb( 釣られる ) // (v1,vi) to be lured/to be attracted
 KanjiVerb( 釣り合う ) // (v5u,vi) to balance/to be in harmony/to suit/(P)
 KanjiVerb( 釣り込まれる ) // (v1) to be carried away by/to be talked into
 KanjiVerb( 鶴首して待つ ) // (v5t) to wait expectantly/to wait with a craned (outstretched) neck
 KanjiVerb( 剃り捨てる ) // (v1) to cut off the hair/take the tonsure
 KanjiVerb( 剃り落とす ) // (v5s) to shave off the hair
 KanjiVerb( 呈する ) // (vs-s) to present/to offer/to show/to display/to exhibit
 KanjiVerb( 挺す ) // (v5s) to volunteer (bravely)
 KanjiVerb( 挺する ) // (vs-s) to volunteer (bravely)
 KanjiVerb( 締め括りをつける ) // (v1) to bring to a finish/to complete
 KanjiVerb( 泥の様に寝る ) // (v1) (col) to sleep like a log
 KanjiVerb( 泥濘む ) // (v5m,vi) to be muddy/to be slushy
 KanjiVerb( 摘まみ上げる ) // (v1) to take a pinch of something (e.g., salt)/to pick up in one's fingers
 KanjiVerb( 敵う ) // (v5u) to match
 KanjiVerb( 敵と戦う ) // (v5u) to fight one's enemy
 KanjiVerb( 適う ) // (v5u,vi) to be suited
 KanjiVerb( 適する ) // (vs-s) to fit/to suit/(P)
 KanjiVerb( 溺れる ) // (v1,vi) (1) to be drowned/(2) to indulge in/(P)
 KanjiVerb( 溺れ込む ) // (v5m) to drown/to get addicted/to become infatuated
 KanjiVerb( 溺れ死ぬ ) // (v5n) to die by drowning/to drown
 KanjiVerb( 溺れ損なう ) // (v5u) to come near being drowned
 KanjiVerb( 徹する ) // (vs-s) to sink in/to penetrate/to devote oneself/to believe in/to go through/to do intently and exclusively/(P)
 KanjiVerb( 填まり込む ) // (v5m) (1) to get stuck in/to be mired in/(2) to be addicted to
 KanjiVerb( 填り込む ) // (v5m) (1) to get stuck in/to be mired in/(2) to be addicted to
 KanjiVerb( 添い遂げる ) // (v1,vi) to remain married for life
 KanjiVerb( 添う ) // (v5u) to accompany/to become married/to comply with/(P)
 KanjiVerb( 纏い付く ) // (v5k,vi) to entwine/to follow about
 KanjiVerb( 纏う ) // (v5u) to put on/to wear/to be clad in
 KanjiVerb( 纏わり付く ) // (v5k,vi) to coil about/to follow about
 KanjiVerb( 貼り合わせる ) // (v1) to paste together
 KanjiVerb( 貼り出す ) // (v5s) to post (a notice on a board)/to display
 KanjiVerb( 貼り付く ) // (v5k) to cling (to)
 KanjiVerb( 貼付く ) // (v5k) to cling (to)
 KanjiVerb( 転がり込む ) // (v5m,vi) to roll in/to tumble into/to come to live with/to fall in one's way/to visit (esp. to stay overnight as an unwanted guest)
 KanjiVerb( 転がり落ちる ) // (v1) to tumble down/to roll down
 KanjiVerb( 転げる ) // (v1,vi) to roll over/to tumble/to roll about (with laughter)
 KanjiVerb( 転げ込む ) // (v5m,vi) to roll or tumble into
 KanjiVerb( 転げ落ちる ) // (v1,vi) to fall off/to tumble down
 KanjiVerb( 転じる ) // (v1,vi) to turn/to shift/to alter/to distract/(P)
 KanjiVerb( 転ずる ) // (vz,vi) to turn/to shift/to alter/to distract
 KanjiVerb( 転ぶ ) // (v5b,vi) to fall down/to fall over
 KanjiVerb( 点く ) // (v5k,vi) (1) to catch fire/(2) to be lit, e.g., electricity comes on/to be lighted/(P)
 KanjiVerb( 点て込む ) // (v5m) to be crowded/to be busy
 KanjiVerb( 伝う ) // (v5u) to go along/to walk along/to follow/(P)
 KanjiVerb( 澱む ) // (v5m,vi) to stagnate/to be stagnant/to settle/to deposit/to be sedimented/to be precipitated/to hesitate/to be sluggish/to stammer/to stumble/to falter/(P)
 KanjiVerb( 電気で動く ) // (v5k) to run by electricity
 KanjiVerb( 電源を入れる ) // (v1) to turn on power
 KanjiVerb( 兎や角言う ) // (v5u) to say all kinds of things/to complain/to find fault (with)
 KanjiVerb( 塗り込む ) // (v5m) to paint over heavily/to plaster up
 KanjiVerb( 塗り分ける ) // (v1) to paint in different colors (for different purposes) (colours)
 KanjiVerb( 塗れる ) // (v1,vi) to be smeared/to be covered
 KanjiVerb( 妬く ) // (v5k) to be jealous of/to be envious of
 KanjiVerb( 渡り合う ) // (v5u,vi) to argue
 KanjiVerb( 渡り歩く ) // (v5k,vi) to wander from place to place/to change jobs
 KanjiVerb( 登り詰める ) // (v1,vi) to go to the top/to be engrossed in
 KanjiVerb( 賭する ) // (vs-s) stake/risk/bet/wager
 KanjiVerb( 途切れる ) // (v1,vi) to pause/to be interrupted/(P)
 KanjiVerb( 途絶える ) // (v1,vi) to stop/to cease/to come to an end/(P)
 KanjiVerb( 度が過ぎる ) // (v1) to go too far/to go to excess/to carry too far
 KanjiVerb( 怒らせる ) // (v1) (1) to anger someone/to provoke/to offend someone/to make somebody's hackles rise
 KanjiVerb( 怒り狂う ) // (v5u) to be in a fit (of anger)/to rage
 KanjiVerb( 怒り出す ) // (v5s) to fly into a rage/to flare up
 KanjiVerb( 怒鳴り込む ) // (v5m,vi) to storm in with a yell/(P)
 KanjiVerb( 怒鳴り出す ) // (v5s) to start shouting/to break out
 KanjiVerb( 怒鳴り立てる ) // (v1) to stand and shout
 KanjiVerb( 倒れる ) // (v1,vi) to collapse/to break down/to go bankrupt/to fall/to drop/to die/to succumb to/to fall senseless/to be ruined/to have a bad debt/(P)
 KanjiVerb( 倒れ込む ) // (v5m) to collapse into/to flop onto
 KanjiVerb( 倒れ伏す ) // (v5s) to fall down
 KanjiVerb( 冬めく ) // (v5k,vi) to become wintry
 KanjiVerb( 凍える ) // (v1,vi) to freeze/to be chilled/to be frozen/(P)
 KanjiVerb( 凍え死ぬ ) // (v5n) to freeze to death/to die of cold
 KanjiVerb( 凍え付く ) // (v5k,vi) to freeze to/to be frozen to
 KanjiVerb( 凍てつく ) // (v5k,vi) to freeze
 KanjiVerb( 凍てる ) // (v1,vi) to freeze/to be frozen over/to congeal
 KanjiVerb( 凍て付く ) // (v5k,vi) to freeze
 KanjiVerb( 凍みる ) // (v1,vi) to freeze/to be frozen over/to congeal
 KanjiVerb( 凍み付く ) // (v5k,vi) to freeze to/to be frozen to
 KanjiVerb( 凍りつく ) // (v5k,vi) to freeze to/to be frozen to
 KanjiVerb( 凍り付く ) // (v5k,vi) to freeze to/to be frozen to
 KanjiVerb( 悼む ) // (v5m) to grieve over/to mourn/to lament/(P)
 KanjiVerb( 投げ上げる ) // (v1) to throw up (in the air)
 KanjiVerb( 投げ倒す ) // (v5s) to throw a person down
 KanjiVerb( 投げ返す ) // (v5s) to throw back
 KanjiVerb( 投げ与える ) // (v1) to give by tossing or throwing
 KanjiVerb( 投げ落とす ) // (v5s) to throw down
 KanjiVerb( 投じる ) // (v1,vi) to throw/to cast/to invest/(P)
 KanjiVerb( 盗み見る ) // (v1) to steal a glance
 KanjiVerb( 盗み出す ) // (v5s) to steal (from a person)
 KanjiVerb( 湯熨をかける ) // (v1) to iron with a wet cloth/to smooth by steaming and ironing
 KanjiVerb( 当たり散らす ) // (v5s) to find fault with everybody/to make oneself disagreeable
 KanjiVerb( 当てられる ) // (v1) (1) to be affected by (e.g., heat)/to suffer from/(2) to be embarrassed/to be annoyed
 KanjiVerb( 答える ) // (v1,vi) to answer/to reply
 KanjiVerb( 統べ合わせる ) // (v1) to bring together/to unite
 KanjiVerb( 蕩ける ) // (v1,vi) to be enchanted with
 KanjiVerb( 討つ ) // (v5t) to attack/to avenge/(P)
 KanjiVerb( 踏み違える ) // (v1) to misstep/to stray
 KanjiVerb( 踏み越える ) // (v1,vi) to step over or across/to overcome
 KanjiVerb( 踏み堪える ) // (v1,vi) to stand firm/to hold out
 KanjiVerb( 踏み込む ) // (v5m) to step into (someone else's territory)/to break into/to raid
 KanjiVerb( 踏み出す ) // (v5s,vi) to step forward/to advance
 KanjiVerb( 踏み消す ) // (v5s) to stamp out (a fire)
 KanjiVerb( 踏み迷う ) // (v5u,vi) to lose one's way/to go astray
 KanjiVerb( 踏み拉く ) // (v5k) to trample/to crush underfoot
 KanjiVerb( 逃げおおせる ) // (v1,vi) to escape
 KanjiVerb( 逃げる ) // (v1,vi) to escape/to run away/(P)
 KanjiVerb( 逃げ隠れる ) // (v1,vi) to run away and hide
 KanjiVerb( 逃げ延びる ) // (v1,vi) to make good one's escape
 KanjiVerb( 逃げ果せる ) // (v1,vi) to escape
 KanjiVerb( 逃げ後れる ) // (v1) to fail to escape
 KanjiVerb( 逃げ込む ) // (v5m,vi) to take refuge in/to succeed in running away
 KanjiVerb( 逃げ失せる ) // (v1,vi) to escape/to run away
 KanjiVerb( 逃げ出す ) // (v5s,vi) to run away/to escape from/(P)
 KanjiVerb( 逃げ落ちる ) // (v1,vi) to escape safely
 KanjiVerb( 逃げ惑う ) // (v5u,vi) to run about trying to escape
 KanjiVerb( 逃れる ) // (v1,vi) to escape/(P)
 KanjiVerb( 逃れ出る ) // (v1) to scuttle off/to take flight
 KanjiVerb( 透く ) // (v5k,vi) to be transparent/to leave a gap
 KanjiVerb( 透ける ) // (v1,vi) to be transparent/to show through
 KanjiVerb( 頭を痛める ) // (v1) to be concerned about
 KanjiVerb( 頭抜ける ) // (v1,vi) to tower above/to stand out
 KanjiVerb( 闘う ) // (v5u,vi) to fight/to battle/to combat/to struggle against/to wage war/to engage in contest/(P)
 KanjiVerb( 働かせる ) // (v1) to put someone to work/to make someone work/(P)
 KanjiVerb( 働き過ぎる ) // (v1) to overwork
 KanjiVerb( 働き出す ) // (v5s) to start working/to take action
 KanjiVerb( 働く ) // (v5k,vi) to work/to labor/to labour/to do/to act/to commit/to practise/to practice/to work on/to come into play/to be conjugated/to reduce the price/(P)
 KanjiVerb( 動きだす ) // (v5s) to start to move
 KanjiVerb( 動き出す ) // (v5s) to come alive/to get going/to start to move
 KanjiVerb( 動く ) // (v5k,vi) to move/to stir/to shift/to shake/to swing/to operate/to run/to go/to work/to be touched/to be influenced/to waver/to fluctuate/to vary/to change/to be transferred/(P)
 KanjiVerb( 動じる ) // (v1,vi) to be perturbed/to be agitated/(P)
 KanjiVerb( 動ずる ) // (vz,vi) to be perturbed/to be agitated
 KanjiVerb( 同じる ) // (v1,vi) to agree
 KanjiVerb( 同ずる ) // (vz,vi) to agree
 KanjiVerb( 導き出す ) // (v5s) to derive
 KanjiVerb( 憧れる ) // (v1,vi) to long for/to yearn after/to admire/to be attracted by/(P)
 KanjiVerb( 道化る ) // (v1,vi) to jest/to clown (around)
 KanjiVerb( 道行く ) // (v5k-s) to walk down the road
 KanjiVerb( 得する ) // (vs-s) to make a profit/(P)
 KanjiVerb( 得る ) // (v1) to get/to obtain/to gain/to acquire/to win/to catch/(P)
 KanjiVerb( 禿げる ) // (v1,vi) to lose hair/(P)
 KanjiVerb( 独りごちる ) // (v1) to talk to oneself/to mutter
 KanjiVerb( 独り言つ ) // (v5t,vi) to talk to oneself/to mutter
 KanjiVerb( 読み過ごす ) // (v5s) to skip over/to miss reading
 KanjiVerb( 読み出す ) // (v5s) to read out (e.g., data from a computer or process)
 KanjiVerb( 読み進む ) // (v5m) to go on reading
 KanjiVerb( 読み損う ) // (v5u) to misread/to mispronounce
 KanjiVerb( 読み損じる ) // (v1) to fail to read correctly
 KanjiVerb( 読み直す ) // (v5s) to read (a book, etc.) over again
 KanjiVerb( 読み聞かす ) // (v5s) to read to (for) someone
 KanjiVerb( 読み落とす ) // (v5s) to overlook in reading
 KanjiVerb( 突き出る ) // (v1,vi) to project/to stick out/to stand out
 KanjiVerb( 突き進む ) // (v5m,vi) to push on/to plunge forward/to push one's way to
 KanjiVerb( 突き抜く ) // (v5k) to pierce/to shoot through/to penetrate
 KanjiVerb( 突き抜ける ) // (v1,vi) to pierce through/to break through/(P)
 KanjiVerb( 突っ込む ) // (v5m) (1) to thrust something into something/(2) to plunge into/to go into deeply/(3) to meddle/to interfere/(P)
 KanjiVerb( 突っ伏す ) // (v5s,vi) to fall prostrate
 KanjiVerb( 突っ立つ ) // (v5t) to stand up
 KanjiVerb( 突抜く ) // (v5k) to pierce/to shoot through/to penetrate
 KanjiVerb( 突抜ける ) // (v1,vi) to pierce through/to break through
 KanjiVerb( 届く ) // (v5k,vi) to reach/(P)
 KanjiVerb( 届け出でる ) // (v1) to give notice/to submit notice
 KanjiVerb( 遁げ出す ) // (v5s,vi) to run away/to escape from
 KanjiVerb( 凪ぐ ) // (v5g,vi) to become calm/to die down
 KanjiVerb( 謎めく ) // (v5k,vi) to be enigmatic or puzzling/to be wrapped in mystery
 KanjiVerb( 馴れる ) // (v1,vi) to grow accustomed to/to become domesticated/to become tame/to get too familiar with
 KanjiVerb( 馴れ合う ) // (v5u,vi) to collude (with)/to conspire (with)/to establish a secret liaison (with)/to make friends with/to get along well with/to become intimate (with opposite sex)
 KanjiVerb( 馴染む ) // (v5m,vi) to become familiar with
 KanjiVerb( 軟らかく話す ) // (v5s) to speak gently
 KanjiVerb( 匂い立つ ) // (v5t) (1) to be enveloped in a smell/(2) to be radiant/to be attractive
 KanjiVerb( 匂う ) // (v5u,vi) to be fragrant/to smell/to stink/to glow/to be bright/(P)
 KanjiVerb( 匂わせる ) // (v1) to smell of/to give off a scent/to hint at/to intimate
 KanjiVerb( 賑わう ) // (v5u) to prosper/to flourish/to do thriving business/to be crowded with people/(P)
 KanjiVerb( 乳繰り合う ) // (v5u,vi) to flirt with one another/to caress amorously
 KanjiVerb( 入りかける ) // (v1) to be about to enter (a bath, etc.)
 KanjiVerb( 入り掛ける ) // (v1) to be about to enter (a bath, etc.)
 KanjiVerb( 入り込む ) // (v5m,vi) (1) to go into/to come into/to penetrate/to get in/to step in (a house)/(2) to become complicated/(P)
 KanjiVerb( 入り切れる ) // (v1) (all) are able to get in
 KanjiVerb( 入り組む ) // (v5m,vi) to be or become complicated
 KanjiVerb( 入り乱れる ) // (v1,vi) to be jumbled together
 KanjiVerb( 入れ違う ) // (v5u) to pass each other/to cross paths
 KanjiVerb( 入れ合わせる ) // (v1) to make up for
 KanjiVerb( 如く ) // (v5k,vi) to excel/to be equal to
 KanjiVerb( 任じる ) // (v1,vi) to appoint/to nominate/to assume (responsibility)/to pose as
 KanjiVerb( 任ずる ) // (vz) to appoint/to nominate/to assume (responsibility)/to pose as
 KanjiVerb( 妊む ) // (v5m,vi) to conceive/to become pregnant/to get filled with
 KanjiVerb( 忍び泣く ) // (v5k,vi) to shed silent tears
 KanjiVerb( 忍び込む ) // (v5m,vi) to creep in/to steal in
 KanjiVerb( 忍び出す ) // (v5s) to sneak out/to creep out
 KanjiVerb( 忍込む ) // (v5m,vi) to creep in/to steal in
 KanjiVerb( 濡れる ) // (v1,vi) to get wet/(P)
 KanjiVerb( 熱する ) // (vs-s) to heat/(P)
 KanjiVerb( 熱り立つ ) // (v5t,vi) to get angry/to lose one's temper
 KanjiVerb( 年長ける ) // (v1,vi) to grow old
 KanjiVerb( 年老いる ) // (v1) to grow old
 KanjiVerb( 捻くれる ) // (v1,vi) to be contrary/to be uncooperative/to be rebellious
 KanjiVerb( 捻じれる ) // (v1,vi) to twist/to wrench/to screw/(P)
 KanjiVerb( 捻れる ) // (v1,vi) to twist/to wrench/to screw
 KanjiVerb( 燃える ) // (v1,vi) to burn/(P)
 KanjiVerb( 燃え出す ) // (v5s,vi) to catch fire
 KanjiVerb( 燃え尽きる ) // (v1,vi) to burn out
 KanjiVerb( 燃え付く ) // (v5k,vi) to catch fire/to ignite
 KanjiVerb( 燃え立つ ) // (v5t,vi) to blaze up/to burn up
 KanjiVerb( 燃付く ) // (v5k,vi) to catch fire/to ignite
 KanjiVerb( 粘つく ) // (v5k) to be sticky/to be stringy/to be glutinous
 KanjiVerb( 粘り着く ) // (v5k,vi) to be sticky
 KanjiVerb( 粘り抜く ) // (v5k,vi) to stick it out/to see it to the end
 KanjiVerb( 粘付く ) // (v5k) to be sticky/to be stringy/to be glutinous
 KanjiVerb( 悩む ) // (v5m) to be worried/to be troubled/(P)
 KanjiVerb( 納まり返る ) // (v1,vi) to be satisfied with one's position/to be quite content
 KanjiVerb( 膿み爛れる ) // (v1) to fester
 KanjiVerb( 膿む ) // (v5m,vi) to fester/to form pus
 KanjiVerb( 覗く ) // (v5k) to peep in/to look in/to peek in/to stick out/(P)
 KanjiVerb( 波打つ ) // (v5t,vi) to dash against/to undulate/to wave/to heave/to beat fast (heart)
 KanjiVerb( 波立つ ) // (v5t,vi) to be choppy/to run high/to swell/to ripple/to billow/to be in discord
 KanjiVerb( 破ける ) // (v1,vi) to get torn/to wear out/to be frustrated/to break
 KanjiVerb( 破れる ) // (v1,vi) to get torn/to wear out/(P)
 KanjiVerb( 馬鹿げる ) // (v1,vi) to look foolish
 KanjiVerb( 廃する ) // (vs-s) (1) to abolish/to abandon/(2) to dethrone/(3) to repeal/to discontinue
 KanjiVerb( 廃れる ) // (v1,vi) to go out of use/to become obsolete/to die out/to go out of fashion
 KanjiVerb( 排する ) // (vs-s) to push aside/to overcome (e.g., difficulties)/to reject
 KanjiVerb( 敗れる ) // (v1,vi) to be defeated/to be unsuccessful/(P)
 KanjiVerb( 背く ) // (v5k,vi) to run counter to/to go against/to disobey/to infringe/(P)
 KanjiVerb( 煤ける ) // (v1,vi) to be sooty/to be stained
 KanjiVerb( 買い集める ) // (v1) to buy up
 KanjiVerb( 買い与える ) // (v1) to buy as a gift
 KanjiVerb( 売り広げる ) // (v1) to find a market for/to extend the sale of
 KanjiVerb( 売り惜しむ ) // (v5m) to hold back on or restrict sales of/to be reluctant to sell
 KanjiVerb( 売り切れる ) // (v1,vi) to be sold out/(P)
 KanjiVerb( 売れる ) // (v1,vi) to be sold/(P)
 KanjiVerb( 這い出す ) // (v5s,vi) to crawl or creep out of
 KanjiVerb( 這い出る ) // (v1,vi) to crawl or creep out of
 KanjiVerb( 這い蹲う ) // (v5u,vi) to grovel
 KanjiVerb( 這う ) // (v5u) to creep/to crawl/(P)
 KanjiVerb( 這入り込む ) // (v5m,vi) (1) to go into/to come into/to penetrate/to get in/to step in (a house)/(2) to become complicated
 KanjiVerb( 剥がれる ) // (v1,vi) to come unstuck from
 KanjiVerb( 剥ぐ ) // (v5g) to tear off/to peel off/to rip off/to strip off/to skin/to flay/to disrobe/to deprive of
 KanjiVerb( 剥げる ) // (v1,vi) to come off/to be worn off/to fade/to discolor/to discolour/(P)
 KanjiVerb( 剥げ落ちる ) // (v1) to peel off
 KanjiVerb( 剥れる ) // (v1,vi) (1) (uk) to become angry or sullen/to take offense/to be miffed/(2) to come unstuck from/to peel off/to come off/to be taken off
 KanjiVerb( 博す ) // (v5s) to win/to gain
 KanjiVerb( 博する ) // (vs-s) to win/to gain
 KanjiVerb( 泊り込む ) // (v5m,vi) to stay overnight
 KanjiVerb( 白む ) // (v5m,vi) to grow light/to become white/to turn grey (gray)
 KanjiVerb( 白茶ける ) // (v1,vi) to fade/to discolour/to discolor
 KanjiVerb( 薄らぐ ) // (v5g,vi) to become thin/to fade/to grow pale/(P)
 KanjiVerb( 薄れる ) // (v1,vi) to fade/to become dim/(P)
 KanjiVerb( 薄汚れる ) // (v1,vi) to get slightly dirty (all over)
 KanjiVerb( 爆ぜる ) // (v1,vi) to burst open/to pop/to split
 KanjiVerb( 縛に就く ) // (v5k) to be arrested/to be put in bonds
 KanjiVerb( 縛り込む ) // (v5m) to bind together
 KanjiVerb( 函れる ) // (v1) to put into
 KanjiVerb( 肌で感じる ) // (v1) to understand from experience
 KanjiVerb( 発する ) // (vs-s) to fire (a gun)/to emit/to give forth/(P)
 KanjiVerb( 発つ ) // (v5t,vi) to depart (on a plane, train, etc.)
 KanjiVerb( 伐つ ) // (v5t) to strike/to attack/to punish
 KanjiVerb( 罰する ) // (vs-s) to punish/to penalize/to penalise/(P)
 KanjiVerb( 抜きん出る ) // (v1) to excel/to be outstanding
 KanjiVerb( 抜き合わせる ) // (v1) to draw swords and face off
 KanjiVerb( 抜ける ) // (v1,vi) to come out/to fall out/to be omitted/to be missing/to escape/(P)
 KanjiVerb( 抜け出す ) // (v5s,vi) to slip out/to sneak away/to excel/(P)
 KanjiVerb( 抜け出る ) // (v1,vi) to excel/to steal out
 KanjiVerb( 抜け落ちる ) // (v1,vi) to shed hair
 KanjiVerb( 伴う ) // (v5u,vi) to accompany/to bring with/to be accompanied by/to be involved in/to be consequent upon/(P)
 KanjiVerb( 反する ) // (vs-s) to be inconsistent with/to oppose/to contradict/to transgress/to rebel/(P)
 KanjiVerb( 反っくり返る ) // (v1,vi) to throw one's chest out/to hold one's head high
 KanjiVerb( 反りくり返る ) // (v1,vi) to throw one's chest out/to hold one's head high
 KanjiVerb( 煩う ) // (v5u,vi) to worry about/to be concerned about/to be afflicted with/to suffer from/(P)
 KanjiVerb( 煩わす ) // (v5s) to trouble/to bother/to annoy/to give trouble
 KanjiVerb( 卑しむ ) // (v5m) to despise/to disdain/to scorn
 KanjiVerb( 比する ) // (vs-s) to compare
 KanjiVerb( 疲れる ) // (v1,vi) to get tired/to tire/(P)
 KanjiVerb( 疲れ果てる ) // (v1,vi) to get tired out/to be exhausted/(P)
 KanjiVerb( 罷む ) // (v5m,vi) to cease/to stop/to be over
 KanjiVerb( 罷めさせる ) // (v1) to fire (from job)/to discharge
 KanjiVerb( 罷り越す ) // (v5s,vi) to visit/to call on
 KanjiVerb( 罷り間違う ) // (v5u,vi) to go wrong/to turn for the worse
 KanjiVerb( 罷り出る ) // (v1,vi) to leave/to withdraw/to appear before
 KanjiVerb( 肥える ) // (v1,vi) (1) to grow fat/to grow fertile/(2) to have good taste/(P)
 KanjiVerb( 被害を受ける ) // (v1) to be damaged/to receive damage
 KanjiVerb( 費える ) // (v1,vi) to be wasted
 KanjiVerb( 非行に走らせる ) // (v1) to turn (child) to crime
 KanjiVerb( 飛び違う ) // (v5u,vi) to flit about
 KanjiVerb( 飛び下りる ) // (v1,vi) to jump down/to jump off/(P)
 KanjiVerb( 飛び起きる ) // (v1,vi) to jump up to one's feet
 KanjiVerb( 飛び交う ) // (v5u,vi) to fly about/to flutter about/to fly past each other/(P)
 KanjiVerb( 飛び降りる ) // (v1,vi) to jump down/to jump off/(P)
 KanjiVerb( 飛び込む ) // (v5m,vi) to jump in/to leap in/to plunge into/to dive/(P)
 KanjiVerb( 飛び出す ) // (v5s,vi) to jump out/to rush out/to fly out/to appear suddenly/to protrude/to project/(P)
 KanjiVerb( 飛び出る ) // (v1,vi) to be exorbitant (e.g., price)/to be ridiculously high
 KanjiVerb( 飛び退く ) // (v5k,vi) to jump back
 KanjiVerb( 飛び跳ねる ) // (v1,vi) to jump up and down/to hop
 KanjiVerb( 飛び抜ける ) // (v1) to be preeminent or outstanding
 KanjiVerb( 飛び付く ) // (v5k,vi) to jump at/to be attracted by
 KanjiVerb( 飛び歩く ) // (v5k,vi) to walk about
 KanjiVerb( 飛び離れる ) // (v1,vi) to fly apart/to tower over/to be out of the ordinary
 KanjiVerb( 飛び立つ ) // (v5t,vi) to jump up/to start up/to leap to one's feet/to fly away/to take off
 KanjiVerb( 飛ぶ ) // (v5b,vi) to jump/to fly/to leap/to spring/to bound/to hop/(P)
 KanjiVerb( 飛込む ) // (v5m,vi) to jump in/to leap in/to plunge into/to dive
 KanjiVerb( 飛付く ) // (v5k,vi) to jump at/to be attracted by
 KanjiVerb( 微かに見える ) // (v1) to be seen dimly
 KanjiVerb( 微笑みかける ) // (v1) to smile
 KanjiVerb( 微笑む ) // (v5m,vi) to smile/(P)
 KanjiVerb( 微睡む ) // (v5m,vi) (uk) to doze (off)
 KanjiVerb( 鼻歌混じりで働く ) // (v5k) to work while humming a tune
 KanjiVerb( 鼻白む ) // (v5m,vi) to look daunted
 KanjiVerb( 必要と認める ) // (v1) to judge as necessary
 KanjiVerb( 漂う ) // (v5u,vi) to drift about/to float/to hang in air/(P)
 KanjiVerb( 表する ) // (vs-s) to express/to show/(P)
 KanjiVerb( 表れる ) // (v1,vi) (1) to appear/to come in sight/to become visible/to come out/to embody/to materialize/to materialise/(2) to express oneself/(P)
 KanjiVerb( 表われる ) // (v1,vi) (1) to appear/to come in sight/to become visible/to come out/to embody/to materialize/to materialise/(2) to express oneself
 KanjiVerb( 表立つ ) // (v5t,vi) to become public/to be known/(P)
 KanjiVerb( 評する ) // (vs-s) to comment
 KanjiVerb( 描き下ろす ) // (v5s) to draw for a specific purpose/to draw for the occasion
 KanjiVerb( 病み付く ) // (v5k,vi) to be taken ill/to be addicted to/to become absorbed in/to give oneself up (to)
 KanjiVerb( 病み耄ける ) // (v1,vi) to become wasted by illness
 KanjiVerb( 病む ) // (v5m) to fall ill/to be ill/(P)
 KanjiVerb( 病気だと見える ) // (v1) to seem to be sick
 KanjiVerb( 瀕する ) // (vs-s) to draw near/to be on the verge of
 KanjiVerb( 貧しく暮らす ) // (v5s) to live in poverty
 KanjiVerb( 不貞腐れる ) // (v1,vi) (uk) to become sulky/to become irresponsible
 KanjiVerb( 付いて行く ) // (v5k-s) to follow
 KanjiVerb( 付いて来る ) // (vk) to follow/to come along with one/to accompany
 KanjiVerb( 付かせる ) // (v1) to direct someone toward ..
 KanjiVerb( 付き合う ) // (v5u,vi) to associate with/to keep company with/to get on with/(P)
 KanjiVerb( 付き従う ) // (v5u,vi) to follow/to accompany/to cleave to/to join up with/to obey implicitly/to flatter
 KanjiVerb( 付き随う ) // (v5u,vi) to follow/to accompany/to cleave to/to join up with/to obey implicitly/to flatter
 KanjiVerb( 付き添う ) // (v5u,vi) to attend on/to wait upon/to accompany/to escort and wait on/to chaperone
 KanjiVerb( 付き纏う ) // (v5u,vi) to dangle after
 KanjiVerb( 付く ) // (v5k,vi) to adjoin/to be attached/to adhere/to be connected with/to be dyed/to be stained/to be scarred/to be recorded/to start (fires)/to follow/to become allied to/to accompany/to study with/to increase/to be added to
 KanjiVerb( 付けで買う ) // (v5u) to buy on credit
 KanjiVerb( 付け合わせる ) // (v1) to add to
 KanjiVerb( 付け込む ) // (v5m,vi) to take advantage of/to impose on/to make an entry/(P)
 KanjiVerb( 付け直す ) // (v5s) to repair again/to join again
 KanjiVerb( 付け落とす ) // (v5s) to neglect to make an entry in a ledger
 KanjiVerb( 付合う ) // (v5u,vi) to associate with/to keep company with/to get on with
 KanjiVerb( 富ます ) // (v5s) to enrich/to make wealthy
 KanjiVerb( 富む ) // (v5m,vi) to be rich/to become rich/(P)
 KanjiVerb( 布く ) // (v5k) (1) to spread out/to lay out/(2) to take a position/(3) to impose widely (e.g., over a city)
 KanjiVerb( 怖じける ) // (v1) to be afraid (of)/to be frightened (of)
 KanjiVerb( 怖じる ) // (v1,vi) to be scared
 KanjiVerb( 怖じ気付く ) // (v5k,vi) to be seized with fear/to be intimidated/to lose one's nerve/to be frightened/to get cold feet/to have the wind up
 KanjiVerb( 怖気付く ) // (v5k,vi) to be seized with fear/to be intimidated/to lose one's nerve/to be frightened/to get cold feet/to have the wind up
 KanjiVerb( 怖気立つ ) // (v5t,vi) to be horrified/to be filled with trepidation
 KanjiVerb( 扶け起こす ) // (v5s) to help a person to his (her) feet
 KanjiVerb( 敷く ) // (v5k) (1) to spread out/to lay out/(2) to take a position/(3) to impose widely (e.g., over a city)/(P)
 KanjiVerb( 普く捜す ) // (v5s) to make a wide search
 KanjiVerb( 浮かされる ) // (v1,vi) to be carried away/to be delirious/to lapse into delirium
 KanjiVerb( 浮かぶ ) // (v5b) to float/to rise to surface/to come to mind/(P)
 KanjiVerb( 浮かれる ) // (v1,vi) to make merry/to be festive/(P)
 KanjiVerb( 浮き出す ) // (v5s,vi) to surface/to stand out
 KanjiVerb( 浮き出る ) // (v1,vi) to rise to the surface/to stand or break out
 KanjiVerb( 浮き足立つ ) // (v5t) to be prepared to flee
 KanjiVerb( 浮き立つ ) // (v5t,vi) to be enlivened/to be exhilarated
 KanjiVerb( 浮く ) // (v5k,vi) to float/to become merry/to become loose/(P)
 KanjiVerb( 浮れ歩く ) // (v5k) to gad around
 KanjiVerb( 浮わつく ) // (v5k) (uk) to be fickle/to be restless/to be flippant
 KanjiVerb( 浮腫む ) // (v5m,vi) to swell/to become swollen
 KanjiVerb( 浮付く ) // (v5k) (uk) to be fickle/to be restless/to be flippant
 KanjiVerb( 腐り果てる ) // (v1) to be corrupt
 KanjiVerb( 腐れる ) // (v1,vi) to spoil/to rot/to corrode
 KanjiVerb( 負える ) // (v1) to be able to bear/to be able to manage
 KanjiVerb( 負ける ) // (v1,vi) to lose/to be defeated/(P)
 KanjiVerb( 負ぶう ) // (v5u) to carry (child) on one's back
 KanjiVerb( 負わせる ) // (v1) (1) to put something on someone's back/to make someone carry something/(2) to lay responsibility on someone/to charge someone with a duty/(3) to inflict injury on someone
 KanjiVerb( 赴く ) // (v5k) to go/to proceed/to repair to/to become
 KanjiVerb( 撫で下ろす ) // (v5s) to stroke down
 KanjiVerb( 撫で回す ) // (v5s) to pat (e.g., dog)/to rub/to stroke
 KanjiVerb( 武者振り付く ) // (v5k) to jump into the fray
 KanjiVerb( 舞い降りる ) // (v1,vi) to swoop down upon/to fly down/to alight
 KanjiVerb( 舞い込む ) // (v5m,vi) to drop in/to happen to
 KanjiVerb( 舞う ) // (v5u,vi) to dance/to flutter about/to revolve/(P)
 KanjiVerb( 封じ込む ) // (v5m) to entrap
 KanjiVerb( 伏し倒れる ) // (v1) to fall down
 KanjiVerb( 伏す ) // (v5s) to bend down/to bow down/to prostrate oneself
 KanjiVerb( 副う ) // (v5u,vi) to suit/to meet/to satisfy/to marry/to accompany/to be added to/to be adjusted to
 KanjiVerb( 復す ) // (v5s) to return to normal/to recover/to restore
 KanjiVerb( 復する ) // (vs-s) to return to normal/to recover/to restore
 KanjiVerb( 復習う ) // (v5u) to review/to rehearse/to practise/to practice
 KanjiVerb( 服する ) // (vs-s) to be subject to/to submit to/to obey/to abide by/to serve, e.g., in the army, or a sentence in jail (gaol)/to observe, e.g., mourning
 KanjiVerb( 覆い隠す ) // (v5s) to mask/to cover
 KanjiVerb( 払い落とす ) // (v5s) to brush off/to shake off
 KanjiVerb( 沸き出す ) // (v5s) to cause to gush out
 KanjiVerb( 沸き出る ) // (v1,vi) to gush forth
 KanjiVerb( 沸き立つ ) // (v5t,vi) to boil up/to ferment/to seethe
 KanjiVerb( 沸く ) // (v5k,vi) to boil/to grow hot/to get excited/to gush forth/(P)
 KanjiVerb( 物申す ) // (v5s,vi) to speak/to object
 KanjiVerb( 分かちあたえる ) // (v1) to apportion to/to share
 KanjiVerb( 分かち合う ) // (v5u) to share
 KanjiVerb( 分かり合う ) // (v5u) to understand (each other)/to comprehend
 KanjiVerb( 分かり出す ) // (v5s) to take notice
 KanjiVerb( 分かれる ) // (v1,vi) to branch off/to diverge from/to fork/to split/to dispense/to scatter/to divide into/(P)
 KanjiVerb( 分かれ出る ) // (v1) to branch out/to diverge/to radiate
 KanjiVerb( 分かれ争う ) // (v5u) to quarrel and separate
 KanjiVerb( 分け合う ) // (v5u) to share
 KanjiVerb( 分け与える ) // (v1) to distribute/to hand out
 KanjiVerb( 分け離す ) // (v5s) to separate from/to detach
 KanjiVerb( 噴きこぼれる ) // (v1,vi) to boil over
 KanjiVerb( 噴き出す ) // (v5s,vi) to spout/to spurt/to gush out/to burst into laughter/(P)
 KanjiVerb( 噴き出る ) // (v1,vi) to blow out/to spout out
 KanjiVerb( 噴く ) // (v5k) (1) to blow (wind, etc)/(2) to emit/to spout
 KanjiVerb( 扮する ) // (vs-s) to disguise oneself/to be dressed (as someone else)
 KanjiVerb( 奮い立つ ) // (v5t,vi) to cheer up
 KanjiVerb( 奮う ) // (v5u) (1) to show (ability)/to wield (power)/(2) to screw up one's courage/(P)
 KanjiVerb( 紛う ) // (v5u) to be mistaken for/to be confused with
 KanjiVerb( 紛れる ) // (v1,vi) to be diverted/to slip into/(P)
 KanjiVerb( 紛れ込む ) // (v5m,vi) to disappear into/to slip into/to be lost in/to be mixed up with
 KanjiVerb( 聞きいただく ) // (v5k) to ask (politely)
 KanjiVerb( 聞きもらす ) // (v5s) to fail to hear/to miss
 KanjiVerb( 聞き違う ) // (v5u) to mishear
 KanjiVerb( 聞き過ごす ) // (v5s) to fail to catch/to ignore
 KanjiVerb( 聞き惚れる ) // (v1,vi) to listen to in an ecstasy
 KanjiVerb( 聞き尽くす ) // (v5s) to hear all about
 KanjiVerb( 聞き正す ) // (v5s) to draw (information from)
 KanjiVerb( 聞き損なう ) // (v5u) to mishear/to fail to catch
 KanjiVerb( 聞き頂く ) // (v5k) to ask (politely)
 KanjiVerb( 聞き漏らす ) // (v5s) to fail to hear/to miss
 KanjiVerb( 聞き糺す ) // (v5s) to ascertain/to confirm/to verify/to make sure of
 KanjiVerb( 聞こえる ) // (v1,vi) (1) to be heard/to be audible/(2) to be said to be/to be reputed/(P)
 KanjiVerb( 聞こし召す ) // (v5s) to hear/to drink
 KanjiVerb( 併せる ) // (v1) to unite/to put together/(P)
 KanjiVerb( 併せ考える ) // (v1) to consider together
 KanjiVerb( 併せ用いる ) // (v1) to use jointly/to use at the same time
 KanjiVerb( 平らぐ ) // (v5g) to be suppressed
 KanjiVerb( 平伏す ) // (v5s,vi) to prostrate oneself before
 KanjiVerb( 並ぶ ) // (v5b,vi) to line up/to stand in a line/(P)
 KanjiVerb( 並み外れる ) // (v1,vi) to be uncommon
 KanjiVerb( 並み居る ) // (v1,vi) to sit in a row/to be present (and lined up)
 KanjiVerb( 並居る ) // (v1,vi) to sit in a row/to be present (and lined up)
 KanjiVerb( 閉じる ) // (v1) to close (e.g., book, eyes, meeting, etc.)/to shut/(P)
 KanjiVerb( 僻む ) // (v5m) (1) to be prejudiced/to be soured/(2) to have an inferiority complex/(3) to be jealous/(P)
 KanjiVerb( 別ち与える ) // (v1) to divide and pass around
 KanjiVerb( 別れる ) // (v1,vi) to be divided/to part from/to separate/to bid farewell/(P)
 KanjiVerb( 別れ争う ) // (v5u) to quarrel and separate
 KanjiVerb( 偏り見る ) // (v1) to show partiality
 KanjiVerb( 変じる ) // (v1,vi) to change into/to be transformed/to be transfigured/to transform/to alter/to convert
 KanjiVerb( 変ずる ) // (vz,vi) to change into/to be transformed/to be transfigured/to transform/to alter/to convert
 KanjiVerb( 変わり果てる ) // (v1) to be completely changed
 KanjiVerb( 片づく ) // (v5k,vi) (1) to be put in order/to be put to rights/(2) to be disposed of/to be solved/(3) to be finished/(4) to be married (off)
 KanjiVerb( 片肌脱ぐ ) // (v5g) to lend a hand
 KanjiVerb( 片付く ) // (v5k,vi) (1) to be put in order/to be put to rights/(2) to be disposed of/to be solved/(3) to be finished/(4) to be married (off)/(P)
 KanjiVerb( 編み合わせる ) // (v1) to knit together/to intertwine
 KanjiVerb( 返り咲く ) // (v5k,vi) to come back/to bloom a second time
 KanjiVerb( 遍く捜す ) // (v5s) to make a wide search
 KanjiVerb( 便じる ) // (v1,vi) will do/to answer the purpose/to make convenient
 KanjiVerb( 便ずる ) // (vz,vi) will do/to answer the purpose/to make convenient
 KanjiVerb( 勉強し始める ) // (v1) to begin to study
 KanjiVerb( 勉強し出す ) // (v5s) to begin to study
 KanjiVerb( 弁じる ) // (v1,vi) to speak/to talk/to argue/to manage/to dispose of/to carry through/to distinguish/to discriminate
 KanjiVerb( 弁じ立てる ) // (v1) to speak eloquently/to talk volubly
 KanjiVerb( 弁ずる ) // (vz) to manage/to dispose of/to carry through/to distinguish/to discriminate
 KanjiVerb( 保ち合う ) // (v5u) to maintain equilibrium/to share expenses
 KanjiVerb( 捕らわれる ) // (v1,vi) to be captured/to be apprehended/to be seized with/(P)
 KanjiVerb( 捕われる ) // (v1,vi) to be captured/to be apprehended/to be seized with/(P)
 KanjiVerb( 歩き続ける ) // (v1) to keep walking
 KanjiVerb( 歩き疲れる ) // (v1) to be tired from walking
 KanjiVerb( 歩く ) // (v5k,vi) to walk/(P)
 KanjiVerb( 歩む ) // (v5m,vi) to walk/to go on foot/(P)
 KanjiVerb( 暮れる ) // (v1,vi) to get dark/to end/to come to an end/to close/to run out/(P)
 KanjiVerb( 暮れ果てる ) // (v1,vi) complete nightfall
 KanjiVerb( 暮れ行く ) // (v5k-s,vi) darkening/passing
 KanjiVerb( 暮れ泥む ) // (v5m,vi) to grow dark slowly
 KanjiVerb( 包み直す ) // (v5s) to re-wrap
 KanjiVerb( 呆ける ) // (v1,vi) (1) to grow senile/(2) to fade (colour, color)/(P)
 KanjiVerb( 呆れる ) // (v1,vi) to be amazed/to be shocked/(P)
 KanjiVerb( 呆れ果てる ) // (v1,vi) to be flabbergasted or dumbfounded
 KanjiVerb( 奉ずる ) // (vz) to present/to dedicate/to obey/to follow/to believe in/to serve
 KanjiVerb( 崩れる ) // (v1,vi) to collapse/to crumble/(P)
 KanjiVerb( 崩れ落ちる ) // (v1,vi) to crumble down/to tumble down/to fall in
 KanjiVerb( 崩折れる ) // (v1,vi) to collapse (physically or emotionally)/to fall down
 KanjiVerb( 抱きつく ) // (v5k) to cling to
 KanjiVerb( 抱きよせる ) // (v1) to embrace
 KanjiVerb( 抱き寄せる ) // (v1) to embrace
 KanjiVerb( 抱き合う ) // (v5u,vi) to embrace each other/(P)
 KanjiVerb( 抱き合わせる ) // (v1) to cause to embrace
 KanjiVerb( 抱き止める ) // (v1) to hold a person back/to restrain/to catch
 KanjiVerb( 抱き付く ) // (v5k) to cling to/to embrace
 KanjiVerb( 抱付く ) // (v5k) to cling to/to embrace
 KanjiVerb( 放ったらかす ) // (v5s) to let aside/to neglect
 KanjiVerb( 放っておく ) // (v5k) to leave alone/to leave as is/to ignore/to neglect
 KanjiVerb( 放って置く ) // (v5k) to leave alone/to leave as is/to ignore/to neglect
 KanjiVerb( 放っとく ) // (v5k) to leave someone alone
 KanjiVerb( 放り上げる ) // (v1) to hurl up
 KanjiVerb( 放れる ) // (v1,vi) to leave/to get free/to cut oneself off/(P)
 KanjiVerb( 泡立つ ) // (v5t) to bubble/to foam/to froth
 KanjiVerb( 縫い合わせる ) // (v1) to sew up (together)
 KanjiVerb( 萌える ) // (v1,vi) to burst into bud/to sprout
 KanjiVerb( 萌え出る ) // (v1,vi) to sprout/to bud
 KanjiVerb( 萌え立つ ) // (v5t) to burst into leaf/to sprout
 KanjiVerb( 褒めそやす ) // (v5s) to praise/to extol
 KanjiVerb( 褒め歌う ) // (v5u) to sing praises to
 KanjiVerb( 褒め殺す ) // (v5s) to compliment and criticize lavishly (criticise)
 KanjiVerb( 褒め上げる ) // (v1) to praise to the skies/extol
 KanjiVerb( 褒め立てる ) // (v1) to praise/to extol/to applaud
 KanjiVerb( 訪れる ) // (v1,vi) to visit/(P)
 KanjiVerb( 飽きる ) // (v1,vi) to get tired of/to lose interest in/to have enough/(P)
 KanjiVerb( 亡びる ) // (v1,vi) to be ruined/to go under/to perish/to be destroyed
 KanjiVerb( 亡ぶ ) // (v5b) to be ruined/to go under/to perish/to be destroyed
 KanjiVerb( 忘れかける ) // (v1) to start forgetting
 KanjiVerb( 忘れられる ) // (v1) to slip into obscurity/to be forgotten
 KanjiVerb( 忙殺される ) // (v1) to be worked to death/to be very busily occupied
 KanjiVerb( 暴き出す ) // (v5s) to dig up and expose a criminal matter
 KanjiVerb( 暴れる ) // (v1,vi) to act violently/to rage/to struggle/to be riotous/(P)
 KanjiVerb( 暴れ狂う ) // (v5u) to rage/to run amuck/to tear around
 KanjiVerb( 暴れ込む ) // (v5m) to enter someone's territory by force
 KanjiVerb( 暴れ出す ) // (v5s) to grow restive/to begin to act violently
 KanjiVerb( 膨らむ ) // (v5m) to expand/to swell (out)/to get big/to become inflated/(P)
 KanjiVerb( 膨れる ) // (v1,vi) to get cross/to get sulky/to swell (out)/to expand/to be inflated/to distend/to bulge/(P)
 KanjiVerb( 吠える ) // (v1,vi) to bark/to bay/to howl/to bellow/to roar/to cry/(P)
 KanjiVerb( 吠え出す ) // (v5s) to give mouth/to bark
 KanjiVerb( 吠え付く ) // (v5k,vi) to bark at and chase
 KanjiVerb( 吠る ) // (v1,vi) to bark/to bay/to howl/to bellow/to roar/to cry
 KanjiVerb( 頬染める ) // (v1) to blush
 KanjiVerb( 北叟笑む ) // (v5k,vi) to chuckle/to snicker
 KanjiVerb( 卜う ) // (v5u) to tell a fortune/to predict/to choose/to settle/to fix
 KanjiVerb( 卜する ) // (vs-s) to tell (a person's) fortune/to divine/to fix/to choose
 KanjiVerb( 睦ぶ ) // (v5b,vi) to be harmonious/to get on well/to be intimate or close
 KanjiVerb( 睦む ) // (v5m,vi) to be harmonious/to get on well/to be intimate or close
 KanjiVerb( 没する ) // (vs-s) (1) to sink/to go down/(2) to disappear/to vanish/(3) to pass away/to die
 KanjiVerb( 堀散らす ) // (v5s) to dig up messily
 KanjiVerb( 翻筋斗打つ ) // (v5t) to turn a somersault
 KanjiVerb( 摩する ) // (vs-s) (1) to rub/to scrub/(2) to draw near/to press
 KanjiVerb( 摩り込む ) // (v5m) to rub in/to grind and mix
 KanjiVerb( 摩り切れる ) // (v1,vi) to wear out
 KanjiVerb( 摩れる ) // (v1,vi) to rub/to chafe/to wear/to become sophisticated
 KanjiVerb( 磨り会わせる ) // (v1) to fit by rubbing together
 KanjiVerb( 磨り砕く ) // (v5k) to rub to pieces/to grind into powder
 KanjiVerb( 磨り消す ) // (v5s) to erase/to efface
 KanjiVerb( 磨り崩す ) // (v5s) to rub to pieces
 KanjiVerb( 麻酔をかける ) // (v1) to anesthetize/to anesthetise/to anaesthetize/to anaesthetise
 KanjiVerb( 埋ける ) // (v1) (1) to bury something in the ground/(2) to cover coals with ash/to bank a fire
 KanjiVerb( 埋め合わす ) // (v5s) to make up for/to compensate for
 KanjiVerb( 埋め込む ) // (v5m) to bury/to embed
 KanjiVerb( 埋もれる ) // (v1,vi) to be buried/to be covered/to be hidden/(P)
 KanjiVerb( 末枯れる ) // (v1,vi) to die (esp. foliage as winter approaches)
 KanjiVerb( 繭をかける ) // (v1) to spin a cocoon
 KanjiVerb( 繭を掛ける ) // (v1) to spin a cocoon
 KanjiVerb( 万一に備える ) // (v1) to provide against contingencies
 KanjiVerb( 満ちる ) // (v1,vi) to be full/to rise (tide)/to mature/to expire/(P)
 KanjiVerb( 満ち溢れる ) // (v1,vi) to be full of (e.g. adventure youth energy and such)/to be overflowing with
 KanjiVerb( 満ち足りる ) // (v1,vi) to be content/to have enough/to be happy/to be sufficient/to be satisfied
 KanjiVerb( 満ち満ちる ) // (v1) to be full to the brim
 KanjiVerb( 魅かれる ) // (v1) to be charmed by
 KanjiVerb( 魅せられる ) // (v1) to be enchanted/to be charmed
 KanjiVerb( 脈打つ ) // (v5t,vi) pounding heart/pulsing vein
 KanjiVerb( 眠りこむ ) // (v5m,vi) to fall asleep/to sleep deeply
 KanjiVerb( 眠り込む ) // (v5m,vi) to fall asleep/to sleep deeply
 KanjiVerb( 夢見る ) // (v1,vi) to dream (of)
 KanjiVerb( 名乗り出る ) // (v1,vi) to introduce oneself/(P)
 KanjiVerb( 名前を馳せる ) // (v1) to win fame/to make a name for oneself
 KanjiVerb( 明く ) // (v5k,vi) (1) to open/to become open/to become empty/(v5k,vi) (2) to dawn
 KanjiVerb( 明ける ) // (v1,vi) to dawn/to become daylight/(P)
 KanjiVerb( 明け初める ) // (v1) to dawn
 KanjiVerb( 明け暮れる ) // (v1,vi) to do nothing but/to spend all one's time doing
 KanjiVerb( 明け放れる ) // (v1) darkness giving way to the light of the morning
 KanjiVerb( 明らむ ) // (v5m,vi) to become luminous at dawn (esp. the sky)
 KanjiVerb( 明るむ ) // (v5m,vi) to brighten/to be refreshed
 KanjiVerb( 迷い込む ) // (v5m) to go astray/to lose one's way
 KanjiVerb( 迷う ) // (v5u,vi) to be puzzled/to be perplexed/to lose one's way/(P)
 KanjiVerb( 銘打つ ) // (v5t,vi) to engrave an inscription/to call (designate) itself/to mark/to label
 KanjiVerb( 鳴き交わす ) // (v5s) to exchange wooing cries/to cry (howl) to each other
 KanjiVerb( 鳴く ) // (v5k) (1) to sing (bird)/(2) to bark/to purr/to make sound (animal)/(P)
 KanjiVerb( 鳴り響く ) // (v5k,vi) to reverberate/to resound/to echo
 KanjiVerb( 鳴り出す ) // (v5s) to begin making a sound (ringing, singing, crying, etc.)
 KanjiVerb( 滅びる ) // (v1,vi) to be ruined/to go under/to perish/to be destroyed/(P)
 KanjiVerb( 滅ぶ ) // (v5b) to be ruined/to go under/to perish/to be destroyed
 KanjiVerb( 免れる ) // (v1,vi) to escape from/to be rescued from/to avoid/to evade/to avert/to elude/to be exempted/to be relieved from pain/to get rid of
 KanjiVerb( 面する ) // (vs-s) to face on/to look out on to/(P)
 KanjiVerb( 面喰らう ) // (v5u) to be confused (bewildered, taken aback)
 KanjiVerb( 面食らう ) // (v5u) to be confused (bewildered, taken aback)
 KanjiVerb( 毛羽立つ ) // (v5t) to become fluffy
 KanjiVerb( 黙り込む ) // (v5m,vi) to say no more/to sink into silence
 KanjiVerb( 目から火が出る ) // (v1) to see stars (i.e. after being hit in the head)
 KanjiVerb( 目する ) // (vs-s) to recognize/to recognise/to distinguish/to pay attention to
 KanjiVerb( 目につく ) // (v5k) to be noticeable
 KanjiVerb( 目に付く ) // (v5k) to be noticeable
 KanjiVerb( 目を止める ) // (v1) to take notice/to pay attention
 KanjiVerb( 目を伏せる ) // (v1) to cast down one's eyes
 KanjiVerb( 目覚ます ) // (v5s) to wake up
 KanjiVerb( 目覚める ) // (v1) to wake up/(P)
 KanjiVerb( 目立つ ) // (v5t,vi) to be conspicuous/to stand out/(P)
 KanjiVerb( 目眩く ) // (v5k,vi) to dazzle/to blind
 KanjiVerb( 問い合わせる ) // (v1) to enquire/to inquire/to seek information/(P)
 KanjiVerb( 問い正す ) // (v5s) to question
 KanjiVerb( 問い直す ) // (v5s) to question/to query
 KanjiVerb( 問題を取り上げる ) // (v1) to take up a problem
 KanjiVerb( 悶える ) // (v1,vi) to be in agony/to worry
 KanjiVerb( 弥増す ) // (v5s,vi) to increase (all the more)
 KanjiVerb( 役に立つ ) // (v5t) to be helpful/to be useful/(P)
 KanjiVerb( 役立つ ) // (v5t) to be useful/to be helpful/to serve the purpose/(P)
 KanjiVerb( 訳す ) // (v5s) to translate/(P)
 KanjiVerb( 躍り込む ) // (v5m,vi) to jump into/to rush into
 KanjiVerb( 躍り出る ) // (v1,vi) to jump (e.g., to first place)/to spring out
 KanjiVerb( 油染みる ) // (v1,vi) to become greasy/to be oil-stained
 KanjiVerb( 癒える ) // (v1,vi) to recover/to be healed
 KanjiVerb( 優れる ) // (v1,vi) to surpass/to outstrip/to excel/(P)
 KanjiVerb( 勇み立つ ) // (v5t,vi) to cheer up/to be encouraged (by)/to be in high spirits
 KanjiVerb( 勇む ) // (v5m) to be in high spirits/to be encouraged/to be lively/to cheer up/(P)
 KanjiVerb( 幽する ) // (vs-s) to confine to a room
 KanjiVerb( 幽明相隔てる ) // (v1) to die
 KanjiVerb( 憂い悩む ) // (v5m) to be grievously troubled
 KanjiVerb( 有する ) // (vs-s) to own/to be endowed with/(P)
 KanjiVerb( 有りうる ) // (v5uru,vi) to be possible/to be likely/to be probable
 KanjiVerb( 有りえる ) // (v1,vi) to be possible/to be likely
 KanjiVerb( 有り合う ) // (v5u,vi) to happen to be present
 KanjiVerb( 有り得る ) // (v1,vi) to be possible/to be likely
 KanjiVerb( 有り付く ) // (v5k) to get/to obtain/to come by/to find
 KanjiVerb( 有無相通じる ) // (v1) to help each other/to complement
 KanjiVerb( 湧く ) // (v5k,vi) to boil/to grow hot/to get excited/to gush forth/(P)
 KanjiVerb( 誘いかける ) // (v1) to invite
 KanjiVerb( 誘いをかける ) // (v1) to invite/to call out
 KanjiVerb( 誘い掛ける ) // (v1) to invite
 KanjiVerb( 誘い合う ) // (v5u) to ask each other
 KanjiVerb( 遊ばせる ) // (v1) to leave idle
 KanjiVerb( 遊び戯れる ) // (v1) to frolic
 KanjiVerb( 遊び歩く ) // (v5k) to visit one place after another without affect
 KanjiVerb( 遊ぶ ) // (v5b,vi) (1) to play/to make a visit (esp. for pleasure)/(2) to be idle/to do nothing/(P)
 KanjiVerb( 遊牝む ) // (v5m,vi) to copulate (animals)/to mate
 KanjiVerb( 融ける ) // (v1,vi) to melt/to thaw/to fuse/to dissolve
 KanjiVerb( 融け込む ) // (v5m,vi) to melt into
 KanjiVerb( 与する ) // (vs-s) to take part in/to be implicated in/to side with/to support
 KanjiVerb( 揺すり起こす ) // (v5s) to shake someone awake
 KanjiVerb( 揺らぐ ) // (v5g,vi) to swing/to sway/to shake/to tremble/(P)
 KanjiVerb( 揺らめく ) // (v5k,vi) to flicker/to quiver/to waver/to sway
 KanjiVerb( 揺り起こす ) // (v5s) to shake someone awake
 KanjiVerb( 揺り動く ) // (v5k,vi) to quake/to swing
 KanjiVerb( 揺り返す ) // (v5s,vi) to shake back
 KanjiVerb( 揺り落とす ) // (v5s) to shake down (e.g., nuts from a tree)
 KanjiVerb( 揺るぐ ) // (v5g,vi) to shake/to waver/to tremble/(P)
 KanjiVerb( 揺れる ) // (v1,vi) to shake/to sway/(P)
 KanjiVerb( 揺れ動く ) // (v5k) to tremble
 KanjiVerb( 揺蕩う ) // (v5u,vi) to drift from here to there/to float around
 KanjiVerb( 擁する ) // (vs-s) to have/to possess/(P)
 KanjiVerb( 溶きほぐす ) // (v5s) to whip an egg/to scramble (e.g., an egg)
 KanjiVerb( 溶ける ) // (v1,vi) to melt/to thaw/to fuse/to dissolve/(P)
 KanjiVerb( 溶け合う ) // (v5u,vi) to melt together
 KanjiVerb( 溶け込む ) // (v5m,vi) to melt into/(P)
 KanjiVerb( 熔ける ) // (v1,vi) to melt/to thaw/to fuse/to dissolve
 KanjiVerb( 要する ) // (vs-s) to demand/to require/to take/(P)
 KanjiVerb( 踊らされる ) // (v1) to be manipulated (lit: to be made to dance)
 KanjiVerb( 踊り狂う ) // (v5u) to dance in ecstasy
 KanjiVerb( 踊り出す ) // (v5s) to begin to dance/to break into a dance
 KanjiVerb( 踊り抜く ) // (v5k) to dance away
 KanjiVerb( 踊り明かす ) // (v5s) to dance all night/to dance until dawn
 KanjiVerb( 養い育てる ) // (v1) to bring up/to foster/to rear
 KanjiVerb( 抑え込む ) // (v5m) to shut out one's opponents/to stop the other side from scoring
 KanjiVerb( 欲する ) // (vs-s) to want/to desire/(P)
 KanjiVerb( 淀む ) // (v5m,vi) to stagnate/to be stagnant/to settle/to deposit/to be sedimented/to be precipitated/to hesitate/to be sluggish/to stammer/to stumble/to falter
 KanjiVerb( 来はじめる ) // (v1) to come for the first time/to become for the first time
// KanjiVerb( 来る ) // (vk) to come/to come to hand/to arrive/to approach/to call on/to come on (rain)/to set in/to be due/to become/to grow/to get/to come from/to be caused by/to derive from/(P)
 KanjiVerb( 来向かう ) // (v5u) to come facing (us)
 KanjiVerb( 来合わせる ) // (v1) to happen to come along
 KanjiVerb( 来付ける ) // (v1) to call frequently
 KanjiVerb( 頼む ) // (v5m) to request/to beg/to ask/(P)
 KanjiVerb( 絡み合う ) // (v5u,vi) to be(come) intertwined/to be entangled/(P)
 KanjiVerb( 絡み付く ) // (v5k) to twine oneself around/to coil around
 KanjiVerb( 絡む ) // (v5m,vi) (1) to entangle/to entwine/(2) to pick a quarrel/(3) to be involved with/(P)
 KanjiVerb( 落ちつく ) // (v5k) to calm down/to settle down/to be steady/to settle in/to take up one's residence/to harmonize with/to harmonise with/to match/to restore presence of mind
 KanjiVerb( 落ちぶれる ) // (v1) to be ruined/to fall low/to go under/to come to ruin
 KanjiVerb( 落ちる ) // (v1,vi) (1) to fall down/to drop/(2) to fail (e.g., exam)/(3) to crash/to degenerate/to degrade/(4) to fade/to come out (e.g., a stain)/(P)
 KanjiVerb( 落ち延びる ) // (v1,vi) to run away/to escape safely
 KanjiVerb( 落ち窪む ) // (v5m) to sink in/to cave in
 KanjiVerb( 落ち行く ) // (v5k-s,vi) to flee/to be ruined
 KanjiVerb( 落ち合う ) // (v5u,vi) to gather/to meet/to join/to flow together/to rendezvous/(P)
 KanjiVerb( 落ち込む ) // (v5m,vi) to fall into/to feel down (sad)/(P)
 KanjiVerb( 落ち着き払う ) // (v5u,vi) to keep cool
 KanjiVerb( 落ち着く ) // (v5k) to calm down/to settle down/to be steady/to settle in/to take up one's residence/to harmonize with/to harmonise with/to match/to restore presence of mind/(P)
 KanjiVerb( 落ち零れる ) // (v1) to fall behind/to fall short/to drop out
 KanjiVerb( 落っこちる ) // (v1,vi) to fall down/to drop
 KanjiVerb( 落つ ) // (v5t,vi) (1) to fall down/to drop/(2) to fail (e.g., exam)/(3) to crash/to degenerate/to degrade
 KanjiVerb( 落延びる ) // (v1,vi) to run away/to escape safely
 KanjiVerb( 落着く ) // (v5k) to calm down/to settle down/to be steady/to settle in/to take up one's residence/to harmonize with/to harmonise with/to match/to restore presence of mind
 KanjiVerb( 乱れる ) // (v1,vi) to get confused/to be disordered/to be disturbed/(P)
 KanjiVerb( 乱れ飛ぶ ) // (v5b,vi) to fly wildly about
 KanjiVerb( 乱吹く ) // (v5k,vi) to blow snow violently
 KanjiVerb( 利かす ) // (v5s) to season/to enliven
 KanjiVerb( 利く ) // (v5k,vi) to be effective/(P)
 KanjiVerb( 利する ) // (vs-s) (1) to profit/to benefit from/(2) to to take advantage of/to make good use of
 KanjiVerb( 履き替える ) // (v1) to change (clothes)
 KanjiVerb( 理解し合う ) // (v5u) to reach mutual understanding/to understand each other
 KanjiVerb( 裏問う ) // (v5u-s) to ascertain a person's innermost feelings
 KanjiVerb( 離れる ) // (v1,vi) to be separated from/to leave/to go away/to be a long way off/(P)
 KanjiVerb( 立たす ) // (v5s,vi) to help a person stand/to get someone to their feet/to raise/to rouse
 KanjiVerb( 立ち会う ) // (v5u,vi) to be present/to be witness to
 KanjiVerb( 立ち後れる ) // (v1,vi) to start slowly/to lag behind
 KanjiVerb( 立ち向かう ) // (v5u,vi) to fight against/to oppose/to face
 KanjiVerb( 立ち行く ) // (v5k-s,vi) to maintain itself/to last/to make itself pay/to make a living/to keep going
 KanjiVerb( 立ち合う ) // (v5u,vi) to be matched against
 KanjiVerb( 立ち込める ) // (v1,vi) to hang over/to shroud/to enshroud/to envelop/to screen
 KanjiVerb( 立ち上げる ) // (v1) (comp) to start (something)/to boot (a computer)
 KanjiVerb( 立ち振る舞う ) // (v5u) to act/to behave
 KanjiVerb( 立ち振舞う ) // (v5u) to act/to behave
 KanjiVerb( 立ち尽くす ) // (v5s) to stand stock still
 KanjiVerb( 立ち騒ぐ ) // (v5g,vi) to make a din
 KanjiVerb( 立ち続ける ) // (v1,vi) to keep standing
 KanjiVerb( 立ち退かせる ) // (v1) to evict/to eject
 KanjiVerb( 立ち退く ) // (v5k,vi) to evacuate/to clear out/to vacate/to withdraw/to take refuge/(P)
 KanjiVerb( 立ち遅れる ) // (v1,vi) to start slowly/to lag behind
 KanjiVerb( 立ち働く ) // (v5k,vi) to go about one's work
 KanjiVerb( 立ち並ぶ ) // (v5b) to stand up/to line in a row/to be equal to
 KanjiVerb( 立ち迷う ) // (v5u,vi) to drift along
 KanjiVerb( 立ち竦む ) // (v5m,vi) to be petrified/to be unable to move
 KanjiVerb( 立ち籠める ) // (v1,vi) to hang over/to shroud/to enshroud/to envelop/to screen
 KanjiVerb( 立つ ) // (v5t,vi) to stand/(P)
 KanjiVerb( 立て込む ) // (v5m) to be crowded/to be busy/(P)
 KanjiVerb( 立込める ) // (v1,vi) to hang over/to shroud/to enshroud/to envelop/to screen
 KanjiVerb( 立続ける ) // (v1,vi) to keep standing
 KanjiVerb( 掠め奪う ) // (v5u) to plunder
 KanjiVerb( 掠れる ) // (v1,vi) to be grazed/to touch/to chip
 KanjiVerb( 略す ) // (v5s) to abbreviate/(P)
 KanjiVerb( 流し出す ) // (v5s) to draw off/to run out/to flush out
 KanjiVerb( 流れる ) // (v1,vi) to stream/to flow (liquid, time, etc.)/to run (ink)/to be washed away/(P)
 KanjiVerb( 流れ込む ) // (v5m,vi) to flow/to pour/to stream/(P)
 KanjiVerb( 流れ出す ) // (v5s) to flow out/to stream out/to pour out/to gush forth/to leak/to ooze out/to drift away
 KanjiVerb( 流れ出る ) // (v1) to flow out/to stream out/to pour out/to gush forth/to leak/to ooze out/to drift away
 KanjiVerb( 流れ着く ) // (v5k) to drift to/to be washed ashore
 KanjiVerb( 流れ歩く ) // (v5k,vi) to wander about
 KanjiVerb( 流れ落ちる ) // (v1) to run off (fluid)/to run down/to flow down
 KanjiVerb( 流離う ) // (v5u,vi) to wander/to roam
 KanjiVerb( 粒立つ ) // (v5t,vi) to become grainy
 KanjiVerb( 旅慣れる ) // (v1,vi) to be accustomed to traveling (travelling)
 KanjiVerb( 旅立つ ) // (v5t,vi) to begin a trip/(P)
 KanjiVerb( 涼む ) // (v5m,vi) to cool oneself/to cool off/to enjoy evening cool/(P)
 KanjiVerb( 領する ) // (vs-s) to own/to receive/to understand
 KanjiVerb( 力づく ) // (v5k) to recover one's strength/to recover one's spirit/to revive/to be refreshed/to be invigorated/to be encouraged
 KanjiVerb( 力を入れる ) // (v1) to put forth effort
 KanjiVerb( 力んで見せる ) // (v1) to show a bold front
 KanjiVerb( 力付く ) // (v5k) to recover one's strength/to recover one's spirit/to revive/to be refreshed/to be invigorated/to be encouraged
 KanjiVerb( 力瘤を入れる ) // (v1) to work earnestly
 KanjiVerb( 臨む ) // (v5m,vi) to look out on/to face/to deal with/to attend (function)/(P)
 KanjiVerb( 隣り合う ) // (v5u,vi) to adjoin each other/to sit side by side/(P)
 KanjiVerb( 隣り合わせる ) // (v1) to adjoin
 KanjiVerb( 涙ぐむ ) // (v5m,vi) to be moved to tears
 KanjiVerb( 涙する ) // (vs-s) to shed tears/to bring tears to one's eyes
 KanjiVerb( 類する ) // (vs-s) to be similar to
 KanjiVerb( 冷える ) // (v1,vi) to grow cold/to get chilly/to cool down/(P)
 KanjiVerb( 冷え込む ) // (v5m,vi) to get colder/to get chilled/(P)
 KanjiVerb( 冷める ) // (v1,vi) to become cool/to wear off/to abate/to subside/to dampen/to cool down (interest)/to come down (fever)/(P)
 KanjiVerb( 冷やかす ) // (v5s) to banter/to make fun of/to jeer at/to cool/to refrigerate/(P)
 KanjiVerb( 励み合う ) // (v5u) to vie with another
 KanjiVerb( 励む ) // (v5m) to be zealous/to brace oneself/to endeavour/to endeavor/to strive/to make an effort/(P)
 KanjiVerb( 零れる ) // (v1,vi) to overflow/to spill/(P)
 KanjiVerb( 零れ落ちる ) // (v1,vi) to spill over and fall/to scatter (petals, leaves, etc.)
 KanjiVerb( 裂ける ) // (v1,vi) to split/to tear/to burst/(P)
 KanjiVerb( 恋い初める ) // (v1) to begin to love
 KanjiVerb( 恋い焦がれる ) // (v1) to yearn for/to be deeply in love with
 KanjiVerb( 恋い忍ぶ ) // (v5b) to live on love
 KanjiVerb( 恋い暮らす ) // (v5s) to live deeply in love
 KanjiVerb( 恋い佗びる ) // (v1) to be lovesick
 KanjiVerb( 恋する ) // (vs-s) to fall in love with/to love/(P)
 KanjiVerb( 恋焦がれる ) // (v1) to yearn for/to be deeply in love with
 KanjiVerb( 練り合せる ) // (v1) to knead together
 KanjiVerb( 練り合わせる ) // (v1) to knead together
 KanjiVerb( 練り歩く ) // (v5k,vi) to parade/to march
 KanjiVerb( 連む ) // (v5m,vi) to go with (a companion)
 KanjiVerb( 連れていく ) // (v5k-s) to take someone (of lower status) along
 KanjiVerb( 連れてくる ) // (vk) to bring someone along
 KanjiVerb( 連れて行く ) // (v5k-s) to take someone (of lower status) along/(P)
 KanjiVerb( 連れて来る ) // (vk) to bring someone along/(P)
 KanjiVerb( 連れる ) // (v1) to lead/to take (a person)/(P)
 KanjiVerb( 連れ添う ) // (v5u,vi) to be man and wife/to be married to
 KanjiVerb( 連れ戻す ) // (v5s) to bring back
 KanjiVerb( 連れ立つ ) // (v5t,vi) to accompany/to go with or together
 KanjiVerb( 弄する ) // (vs-s) to use/to talk/to play a trick
 KanjiVerb( 漏れる ) // (v1,vi) to leak out/to escape/to come through/to shine through/to filter out/to be omitted/(P)
 KanjiVerb( 狼狽える ) // (v1,vi) to be flustered/to loose one's presence of mind
 KanjiVerb( 老いさらばえる ) // (v1,vi) to become decrepit and ugly with age
 KanjiVerb( 老いぼれる ) // (v1,vi) to become decrepit/to become senile
 KanjiVerb( 老いる ) // (v1,vi) to age/to grow old/(P)
 KanjiVerb( 老い込む ) // (v5m,vi) to grow old/to weaken with age/to become senile
 KanjiVerb( 老い耄れる ) // (v1,vi) to become decrepit/to become senile
 KanjiVerb( 老ける ) // (v1,vi) to age/(P)
 KanjiVerb( 老け込む ) // (v5m,vi) to age/to become old
 KanjiVerb( 聾する ) // (vs-s) to deafen
 KanjiVerb( 論じ尽くす ) // (v5s) to deal exhaustively with/(P)
 KanjiVerb( 和む ) // (v5m) to be softened/to calm down/(P)
 KanjiVerb( 和らぐ ) // (v5g,vi) to soften/to calm down/to be mitigated/(P)
 KanjiVerb( 話が付く ) // (v5k) to come to an agreement
 KanjiVerb( 話し出す ) // (v5s) to tell the truth/to open up
 KanjiVerb( 話せる ) // (v1,vi) to be understanding/to be sensible
 KanjiVerb( 歪む ) // (v5m,vi) to warp/to swerve/to deflect/to be crooked/to be distorted/to be bent/to incline/to slant/to be perverted/to be gross-grained/to get bent/to be strained/(P)
 KanjiVerb( 惑う ) // (v5u,vi) to be puzzled
 KanjiVerb( 惑わせる ) // (v1) to lead astray
 KanjiVerb( 詫びる ) // (v1,vi) to apologize/to apologise/(P)
 KanjiVerb( 詫る ) // (v1,vi) to apologize/to apologise
 KanjiVerb( 腕尽く ) // (v5k) to do one's best/to do by force
 KanjiVerb( 仄めく ) // (v5k,vi) to be seen dimly/glimmer
 KanjiVerb( 佗びる ) // (v1,vi) to be worried/to be grieved/to pine for
 KanjiVerb( 佇む ) // (v5m,vi) (uk) to stand (still) a while/to loiter/to stop/(P)
 KanjiVerb( 侘びる ) // (v1,vi) to be worried/to be grieved/to pine for
 KanjiVerb( 佩びる ) // (v1) to wear/to put on (a sword)
 KanjiVerb( 俯く ) // (v5k) to hang one's head in shame/to look downward/to cast one's eyes down/(P)
 KanjiVerb( 俯す ) // (v5s) to bend down/to bow down/to prostrate oneself
 KanjiVerb( 俯向く ) // (v5k) to hang one's head in shame/to look downward/to cast one's eyes down
 KanjiVerb( 俯伏す ) // (v5s) to lie on one's face
 KanjiVerb( 做す ) // (v5s) to make
 KanjiVerb( 冱える ) // (v1,vi) to be clear/to be serene/to be cold/to be skillful
 KanjiVerb( 凭れる ) // (v1,vi) to lean against/to lean on/to recline on/to lie heavy (on the stomach)/(P)
 KanjiVerb( 刳れる ) // (v1,vi) to be gouged/to be hollowed/to become hollow
 KanjiVerb( 吼える ) // (v1,vi) to bark/to bay/to howl/to bellow/to roar/to cry
 KanjiVerb( 咎める ) // (v1) to blame/to find fault/to challenge/to threaten/to take someone to task/to aggravate (an injury)/(P)
 KanjiVerb( 呟く ) // (v5k,vi) to mutter/to murmur/(P)
 KanjiVerb( 呻く ) // (v5k,vi) to moan/to groan
 KanjiVerb( 啀み合う ) // (v5u,vi) to snarl/to quarrel
 KanjiVerb( 喘ぐ ) // (v5g,vi) to gasp/breathe hard
 KanjiVerb( 啼く ) // (v5k) (1) to sing (bird)/(2) to bark/to purr/to make sound (animal)
 KanjiVerb( 嗄れる ) // (v1,vi) (uk) to become hoarse
 KanjiVerb( 嗤う ) // (v5u,vi) to laugh/to smile
 KanjiVerb( 嘔吐く ) // (v5k,vi) to vomit
 KanjiVerb( 噎せる ) // (v1,vi) to choke over/to be choked by
 KanjiVerb( 噎ぶ ) // (v5b,vi) to be choked/to be stifled/to be smothered
 KanjiVerb( 嘶く ) // (v5k,vi) to neigh
 KanjiVerb( 嘲り笑う ) // (v5u) to laugh to scorn
 KanjiVerb( 嘯く ) // (v5k,vi) (uk) to exaggerate
 KanjiVerb( 囁く ) // (v5k,vi) to whisper/to murmur/(P)
 KanjiVerb( 媚びへつらう ) // (v5u,vi) to toady/to be obsequious
 KanjiVerb( 媚びる ) // (v1,vi) to flatter/to curry favor with/to curry favour with/to flirt with/to fawn on
 KanjiVerb( 媚び諂う ) // (v5u,vi) to toady/to be obsequious
 KanjiVerb( 孕む ) // (v5m,vi) to conceive/to become pregnant/to get filled with/(P)
 KanjiVerb( 孳尾む ) // (v5m,vi) to copulate (animals)/to mate
 KanjiVerb( 嵌まり込む ) // (v5m) (1) to get stuck in/to be mired in/(2) to be addicted to
 KanjiVerb( 嵌り込む ) // (v5m) (1) to get stuck in/to be mired in/(2) to be addicted to
 KanjiVerb( 巫山戯る ) // (v1) to romp/to gambol/to frolic/to joke/to make fun of/to flirt
 KanjiVerb( 已む ) // (v5m,vi) to cease/to stop/to be over
 KanjiVerb( 彗星のように現れる ) // (v1) to become famous overnight/to burst into fame
 KanjiVerb( 彷徨う ) // (v5u,vi) to loiter/to putter/to prowl/to wander about/to roam about/to knock around/(P)
 KanjiVerb( 彷徨く ) // (v5k,vi) (1) (uk) to loiter/to putter/to prowl/to wander aimlessly/to knock around/(2) to be confused from not knowing what to do/(P)
 KanjiVerb( 恍ける ) // (v1,vi) (1) to play dumb/to feign ignorance/to play innocent/to have a blank facial expression/(2) to play the fool/(3) to be in one's dotage
 KanjiVerb( 悄気る ) // (v1,vi) to be dispirited/to be dejected/to be disheartened/to lose heart
 KanjiVerb( 悄気込む ) // (v5m,vi) to be utterly disheartened
 KanjiVerb( 愕く ) // (v5k,vi) to be surprised/to be astonished
 KanjiVerb( 憬れる ) // (v1,vi) to long for/to yearn after/to admire/to be attracted by
 KanjiVerb( 憑く ) // (v5k) to possess/to haunt/to attach to
 KanjiVerb( 扠置く ) // (v5k) (uk) to set aside
 KanjiVerb( 抉れる ) // (v1,vi) to be gouged/to be hollowed/to become hollow
 KanjiVerb( 拗くれる ) // (v1,vi) to curve/to twist/to be rebellious
 KanjiVerb( 拗ける ) // (v1,vi) to curve/to twist/to be rebellious
 KanjiVerb( 拗ねる ) // (v1,vi) to be peevish/to sulk/to pout
 KanjiVerb( 拗れる ) // (v1,vi) to twist/to wrench/to screw
 KanjiVerb( 拈くれる ) // (v1,vi) to be contrary/to be uncooperative/to be rebellious
 KanjiVerb( 拉げる ) // (v1,vi) (1) to be crushed/to be squashed (flat)/(2) to be discouraged
 KanjiVerb( 捩れる ) // (v1,vi) to be twisted
 KanjiVerb( 揉める ) // (v1,vi) to disagree/to dispute/(P)
 KanjiVerb( 揶揄う ) // (v5u) (uk) to ridicule/to tease/to banter with/to make fun of/(P)
 KanjiVerb( 搦み合う ) // (v5u,vi) to be(come) intertwined/to be entangled
 KanjiVerb( 搗き交ぜる ) // (v1) to pound together/to mix together
 KanjiVerb( 搗ち合う ) // (v5u,vi) to clash/to be in conflict with
 KanjiVerb( 撓垂れる ) // (v1,vi) to droop
 KanjiVerb( 暈ける ) // (v1,vi) (1) to grow senile/(2) to fade (colour, color)/(P)
 KanjiVerb( 曰う ) // (v5u) to say (polite)/to be pleased say (hint of sarcasm)
 KanjiVerb( 鬱を散じる ) // (v1) to chase one's gloom away/to free one's thoughts from melancholy
 KanjiVerb( 欹てる ) // (v1) to strain to hear/to prick up one's ears
 KanjiVerb( 歿する ) // (vs-s) to die
 KanjiVerb( 沁みる ) // (v1,vi) (1) to pierce/to penetrate/to soak in/to permeate/(2) to be infected (with vice)/to be steeped (with prejudice)
 KanjiVerb( 沁み着く ) // (v5k,vi) to be indelibly stained or ingrained/to be dyed in deeply
 KanjiVerb( 洒落る ) // (v1,vi) to joke/to play on words/to dress stylishly/(P)
 KanjiVerb( 洒落込む ) // (v5m,vi) to get dressed up
 KanjiVerb( 浚う ) // (v5u) to sweep away/to wash away/to dredge/(P)
 KanjiVerb( 涸れる ) // (v1,vi) to dry up (spring, pond, etc.)/to run out
 KanjiVerb( 滲みる ) // (v1,vi) (1) to pierce/to penetrate/to soak in/to permeate/(2) to be infected (with vice)/to be steeped (with prejudice)
 KanjiVerb( 滲み込む ) // (v5m,vi) to soak into/to permeate
 KanjiVerb( 滲み出る ) // (v1,vi) to exude/to ooze/to seep out
 KanjiVerb( 滲む ) // (v5m) to run/to blur/to spread/to blot/to ooze/(P)
 KanjiVerb( 炙り出す ) // (v5s) to reveal invisible writing by applying heat
 KanjiVerb( 煌く ) // (v5k,vi) to glitter/to glisten/to sparkle/to twinkle/to glare/to gleam
 KanjiVerb( 煌めく ) // (v5k,vi) to glitter/to glisten/to sparkle/to twinkle/to glare/to gleam
 KanjiVerb( 燻らす ) // (v5s) to smoke (e.g., a pipe)/to puff (a cigarette)
 KanjiVerb( 熾す ) // (v5s) to light a fire
 KanjiVerb( 爛れる ) // (v1,vi) to be sore/to be inflamed/to be bleary/to fester
 KanjiVerb( 犇く ) // (v5k,vi) (uk) to clamour/to crowd/to jostle
 KanjiVerb( 犇めき合う ) // (v5u) to crowd together in a confined space/to gather and make a commotion
 KanjiVerb( 犇めく ) // (v5k,vi) (uk) to clamour/to crowd/to jostle
 KanjiVerb( 狎れる ) // (v1,vi) to grow accustomed to/to become domesticated/to become tame/to get too familiar with
 KanjiVerb( 疵付ける ) // (v1) to injure/to damage
 KanjiVerb( 疼く ) // (v5k,vi) (uk) to throb/to ache
 KanjiVerb( 痺れる ) // (v1,vi) to become numb/to go to sleep (e.g., a limb)/(P)
 KanjiVerb( 瘠せる ) // (v1,vi) to become thin/to lose weight/to reduce (one's) weight/to slim
 KanjiVerb( 瘠る ) // (v1,vi) to become thin/to lose weight/to reduce (one's) weight/to slim
 KanjiVerb( 皸が切れる ) // (v1) to be chapped (e.g., skin)
 KanjiVerb( 皹が切れる ) // (v1) to be chapped (e.g., skin)
 KanjiVerb( 盪ける ) // (v1,vi) to be enchanted with
 KanjiVerb( 眩む ) // (v5m) to become dizzy
 KanjiVerb( 睨み合う ) // (v5u,vi) to glare at each other
 KanjiVerb( 瞠若たらしめる ) // (v1) to strike someone dumb with astonishment
 KanjiVerb( 穢れる ) // (v1,vi) to get dirty/to become dirty
 KanjiVerb( 竦む ) // (v5m,vi) to cower/to be cramped
 KanjiVerb( 篩いにかける ) // (v1) (uk) to sieve/to sift
 KanjiVerb( 篩いに掛ける ) // (v1) (uk) to sieve/to sift
 KanjiVerb( 篩い落とす ) // (v5s) to sift out/to screen or eliminate (candidates)
 KanjiVerb( 絆される ) // (v1,vi) to be moved by affection/to be moved by kindness
 KanjiVerb( 縒れる ) // (v1,vi) to get twisted/to get kinked
 KanjiVerb( 縋り付く ) // (v5k,vi) to cling to
 KanjiVerb( 縺れる ) // (v1,vi) to tangle/to become complicated/to get twisted/(P)
 KanjiVerb( 縺れ込む ) // (v5m,vi) to proceed though deadlocked
 KanjiVerb( 罅ぜる ) // (v1,vi) to burst open/to pop/to split
 KanjiVerb( 羞じらう ) // (v5u,vi) to feel shy/to be bashful/to blush
 KanjiVerb( 聳える ) // (v1,vi) to rise/to tower/to soar/(P)
 KanjiVerb( 聳え立つ ) // (v5t) to stand towering over the surrounds
 KanjiVerb( 聳り立つ ) // (v5t) to rise (steeply)/to tower/to soar
 KanjiVerb( 舁き上げる ) // (v1) to shoulder (palanquin)
 KanjiVerb( 舁き入れる ) // (v1) to carry in
 KanjiVerb( 舫う ) // (v5u) to moor (a boat)
 KanjiVerb( 蠕く ) // (v5k,vi) to wriggle/to squirm/to crawl like a worm
 KanjiVerb( 蠢く ) // (v5k,vi) to wriggle/to squirm/to crawl like a worm
 KanjiVerb( 褪せる ) // (v1,vi) to fade/to discolor/to discolour/(P)
 KanjiVerb( 褪める ) // (v1,vi) to fade/to discolour/to discolor
 KanjiVerb( 誦する ) // (vs-s) to recite/to chant/to read aloud
 KanjiVerb( 諍う ) // (v5u,vi) to quarrel/to dispute
 KanjiVerb( 諂う ) // (v5u,vi) to flatter
 KanjiVerb( 諳んじる ) // (v1) to memorize/to memorise/to recite from memory
 KanjiVerb( 諷する ) // (vs-s) to hint/to insinuate/to satirize/to satirise
 KanjiVerb( 謳われる ) // (v1,vi) to be admired/to be stipulated/to be clearly expressed
 KanjiVerb( 貪り食う ) // (v5u) to devour greedily
 KanjiVerb( 貪り食らう ) // (v5u) to devour greedily
 KanjiVerb( 貪り読む ) // (v5m) to read a book avidly
 KanjiVerb( 齎らす ) // (v5s) (uk) to bring/to take/to bring about/(P)
 KanjiVerb( 跪く ) // (v5k,vi) (uk) to kneel/(P)
 KanjiVerb( 蹌踉ける ) // (v1,vi) to stagger/to stumble
 KanjiVerb( 蹌踉めく ) // (v5k,vi) (uk) to stagger/(P)
 KanjiVerb( 躊躇う ) // (v5u,vi) (uk) to hesitate/(P)
 KanjiVerb( 躓く ) // (v5k,vi) to stumble/to trip
 KanjiVerb( 躾ける ) // (v1) to train/to discipline/to teach manners
 KanjiVerb( 軋む ) // (v5m,vi) (uk) to jar/to creak/to grate
 KanjiVerb( 鄙びる ) // (v1,vi) to become rustic/to be countrified
 KanjiVerb( 鎔ける ) // (v1,vi) to melt/to thaw/to fuse/to dissolve
 KanjiVerb( 閊える ) // (v1,vi) to be blocked/to choke/to be obstructed/to feel a pressure on one's chest
 KanjiVerb( 闌ける ) // (v1,vi) (1) to excel at/to be proficient at/(2) to grow old/(3) to ripen/(4) to rise high (e.g., the sun)
 KanjiVerb( 靠れる ) // (v1,vi) to lean against/to lean on/to recline on/to lie heavy (on the stomach)
 KanjiVerb( 頷く ) // (v5k,vi) (uk) to nod/to bow one's head in assent/(P)
 KanjiVerb( 頽れる ) // (v1,vi) to collapse (physically or emotionally)/to fall down
 KanjiVerb( 顫える ) // (v1,vi) to shiver/to shake/to quake
 KanjiVerb( 饐える ) // (v1,vi) to go bad/to turn sour
 KanjiVerb( 饑える ) // (v1,vi) to be hungry/to starve/to thirst
 KanjiVerb( 駭く ) // (v5k,vi) to be surprised/to be astonished
 KanjiVerb( 騙し合う ) // (v5u) to cheat each other
 KanjiVerb( 魘される ) // (v1,vi) to have a nightmare
 KanjiVerb( 靡かせる ) // (v1) to fly/to flutter/to win over/to win one's heart/to subdue
 KanjiVerb( 靡く ) // (v5k,vi) to bend/to flutter/to wave/to bow to/to yield to/to obey/to be swayed by/(P)
 KanjiVerb( 黴びる ) // (v1,vi) to become moldy or musty (mouldy)
 KanjiVerb( 齧り散らす ) // (v5s) to gnaw at and scatter around/to start a lot of things without finishing any
 KanjiVerb( 齧り付く ) // (v5k,vi) to bite into/to stick to

 
 KanjiVerb_5r( くみ取る, JAP_TRANSITIVE ) // (v5r,vt) to scoop out/to pump out/to understand
 KanjiVerb_5r( ちょん切る, JAP_TRANSITIVE ) // (v5r,vt) to chop something off (e.g., head)/to snip off/to fire
 KanjiVerb_5r( ぬぐい取る, JAP_TRANSITIVE ) // (v5r,vt) to wipe off/to wipe out/to expunge
 KanjiVerb_5r( はぎ取る, JAP_TRANSITIVE ) // (v5r,vt) to tear off/to strip/to rob
 KanjiVerb_5r( ふき取る, JAP_TRANSITIVE ) // (v5r,vt) to wipe off/to wipe up
 KanjiVerb_5r( ぶん殴る, JAP_TRANSITIVE ) // (v5r,vt) to knock
 KanjiVerb_5r( へし折る, JAP_TRANSITIVE ) // (v5r,vt) to smash/to break
 KanjiVerb_5r( 愛しがる, JAP_TRANSITIVE ) // (v5r,vt) to treat with love/to pity/to cherish
 KanjiVerb_5r( 握る, JAP_TRANSITIVE ) // (v5r,vt) to grasp/to seize/to mould sushi/to mold sushi/(P)
 KanjiVerb_5r( 圧し折る, JAP_TRANSITIVE ) // (v5r,vt) to smash/to break
 KanjiVerb_5r( 為て遣る, JAP_TRANSITIVE ) // (v5r,vt) to do for (someone)/to deceive/to hoodwink
 KanjiVerb_5r( 引きずる, JAP_TRANSITIVE ) // (v5r,vt) to seduce/to drag along/to pull/to prolong/to support/(P)
 KanjiVerb_5r( 引きちぎる, JAP_TRANSITIVE ) // (v5r,vt) to tear off
 KanjiVerb_5r( 引き去る, JAP_TRANSITIVE ) // (v5r,vt) to retreat/to withdraw/to deduct
 KanjiVerb_5r( 引き絞る, JAP_TRANSITIVE ) // (v5r,vt) to draw bow to limit/to draw aside curt
 KanjiVerb_5r( 引き取る, JAP_TRANSITIVE ) // (v5r,vt) to take charge of/to take over/to retire to a private place/(P)
 KanjiVerb_5r( 引き摺る, JAP_TRANSITIVE ) // (v5r,vt) to seduce/to drag along/to pull/to prolong/to support
 KanjiVerb_5r( 引ずる, JAP_TRANSITIVE ) // (v5r,vt) to seduce/to drag along/to pull/to prolong/to support/(P)
 KanjiVerb_5r( 引っぱる, JAP_TRANSITIVE ) // (v5r,vt) (1) to pull/to draw/to stretch/to drag/(2) to pull the ball (baseball)
 KanjiVerb_5r( 引っ括る, JAP_TRANSITIVE ) // (v5r,vt) to bundle/to tie up
 KanjiVerb_5r( 引っ手繰る, JAP_TRANSITIVE ) // (v5r,vt) to snatch (steal) from
 KanjiVerb_5r( 引っ張る, JAP_TRANSITIVE ) // (v5r,vt) (1) to pull/to draw/to stretch/to drag/(2) to pull the ball (baseball)/(P)
 KanjiVerb_5r( 引っ被る, JAP_TRANSITIVE ) // (v5r,vt) to take upon oneself/to pull (a thing) over one's head
 KanjiVerb_5r( 引去る, JAP_TRANSITIVE ) // (v5r,vt) to retreat/to withdraw/to deduct
 KanjiVerb_5r( 引絞る, JAP_TRANSITIVE ) // (v5r,vt) to draw bow to limit/to draw aside curt
 KanjiVerb_5r( 引取る, JAP_TRANSITIVE ) // (v5r,vt) to take charge of/to take over/to retire to a private place/(P)
 KanjiVerb_5r( 引摺る, JAP_TRANSITIVE ) // (v5r,vt) to seduce/to drag along/to pull/to prolong/to support
 KanjiVerb_5r( 飲み回る, JAP_TRANSITIVE ) // (v5r,vt) to drink at a round of places
 KanjiVerb_5r( 羽織る, JAP_TRANSITIVE ) // (v5r,vt) to put on
 KanjiVerb_5r( 窺い知る, JAP_TRANSITIVE ) // (v5r,vt) to perceive/to understand
 KanjiVerb_5r( 詠じる, JAP_TRANSITIVE ) // (v5r,vt) to compose (e.g., poem)/to recite/to sing
 KanjiVerb_5r( 縁る, JAP_TRANSITIVE ) // (v5r,vt) to (add a) border or fringe
 KanjiVerb_5r( 縁取る, JAP_TRANSITIVE ) // (v5r,vt) to (add a) border or fringe
 KanjiVerb_5r( 押し遣る, JAP_TRANSITIVE ) // (v5r,vt) to push or thrust away
 KanjiVerb_5r( 押し切る, JAP_TRANSITIVE ) // (v5r,vt) (1) to have one's own way/(2) to press and cut/(P)
 KanjiVerb_5r( 押し破る, JAP_TRANSITIVE ) // (v5r,vt) to break through
 KanjiVerb_5r( 押切る, JAP_TRANSITIVE ) // (v5r,vt) (1) to have one's own way/(2) to press and cut
 KanjiVerb_5r( 横切る, JAP_TRANSITIVE ) // (v5r,vt) to cross (e.g., arms)/to traverse/(P)
 KanjiVerb_5r( 殴る, JAP_TRANSITIVE ) // (v5r,vt) to strike/to hit/(P)
 KanjiVerb_5r( 下回る, JAP_TRANSITIVE ) // (v5r,vt) to be less than/to be lower than
 KanjiVerb_5r( 嫁入る, JAP_TRANSITIVE ) // (v5r,vt) to wed/to marry a man
 KanjiVerb_5r( 臥せる, JAP_TRANSITIVE ) // (v5r,vt) to lie down/to retire/to go to bed
 KanjiVerb_5r( 賀する, JAP_TRANSITIVE ) // (v5r,vt) to congratulate
 KanjiVerb_5r( 割り振る, JAP_TRANSITIVE ) // (v5r,vt) to assign/to allot/to divide among/to distribute/to prorate/to assess
 KanjiVerb_5r( 割る, JAP_TRANSITIVE ) // (v5r,vt) to divide/to cut/to break/to halve/to separate/to split/to rip/to crack/to smash/to dilute/(P)
 KanjiVerb_5r( 括る, JAP_TRANSITIVE ) // (v5r,vt) to tie up/to tie together/to bundle/to fasten/to hang (oneself)/(P)
 KanjiVerb_5r( 噛み切る, JAP_TRANSITIVE ) // (v5r,vt) to bite off/to gnaw through
 KanjiVerb_5r( 噛る, JAP_TRANSITIVE ) // (v5r,vt) to chew/to bite (at)/to gnaw/to nibble/to munch/to crunch/to have a smattering of
 KanjiVerb_5r( 刈り取る, JAP_TRANSITIVE ) // (v5r,vt) to mow/to reap/to harvest/(P)
 KanjiVerb_5r( 刈る, JAP_TRANSITIVE ) // (v5r,vt) to cut (hair)/to mow (grass)/to harvest/to clip/to shear/to reap/to trim/to prune/(P)
 KanjiVerb_5r( 刈取る, JAP_TRANSITIVE ) // (v5r,vt) to mow/to reap/to harvest
 KanjiVerb_5r( 苅る, JAP_TRANSITIVE ) // (v5r,vt) to mow
 KanjiVerb_5r( 勘繰る, JAP_TRANSITIVE ) // (v5r,vt) to be suspicious of
 KanjiVerb_5r( 感じ取る, JAP_TRANSITIVE ) // (v5r,vt) to feel/(P)
 KanjiVerb_5r( 看破る, JAP_TRANSITIVE ) // (v5r,vt) to see through another's thoughts/to have a sharp eye/to penetrate/to fathom
 KanjiVerb_5r( 気どる, JAP_TRANSITIVE ) // (v5r,vt) to affect/to put on airs
 KanjiVerb_5r( 気取る, JAP_TRANSITIVE ) // (v5r,vt) to suspect/to sense
 KanjiVerb_5r( 疑る, JAP_TRANSITIVE ) // (v5r,vt) to doubt/to distrust/to be suspicious of/to suspect
 KanjiVerb_5r( 詰る, JAP_TRANSITIVE ) // (v5r,vt) to rebuke/to scold/to tell off
 KanjiVerb_5r( 吸い取る, JAP_TRANSITIVE ) // (v5r,vt) to suck up/to absorb/to squeeze (money)
 KanjiVerb_5r( 吸取る, JAP_TRANSITIVE ) // (v5r,vt) to suck up/to absorb/to squeeze (money)
 KanjiVerb_5r( 汲み取る, JAP_TRANSITIVE ) // (v5r,vt) to scoop out/to pump out/to understand/(P)
 KanjiVerb_5r( 汲取る, JAP_TRANSITIVE ) // (v5r,vt) to scoop out/to pump out/to understand
 KanjiVerb_5r( 牛耳る, JAP_TRANSITIVE ) // (v5r,vt) to control/to take the lead in/to have under one's thumb
 KanjiVerb_5r( 漁る, JAP_TRANSITIVE ) // (v5r,vt) to fish for/to look for/(P)
 KanjiVerb_5r( 競る, JAP_TRANSITIVE ) // (v5r,vt) to compete/to bid/to sell at auction/(P)
 KanjiVerb_5r( 強請る, JAP_TRANSITIVE ) // (v5r,vt) (1) to solicit/to demand/to extort
 KanjiVerb_5r( 挟み切る, JAP_TRANSITIVE ) // (v5r,vt) to nip off/to snip/to clip/to trim off
 KanjiVerb_5r( 教わる, JAP_TRANSITIVE ) // (v5r,vt) to be taught/(P)
 KanjiVerb_5r( 脅し取る, JAP_TRANSITIVE ) // (v5r,vt) to extort (money)/to blackmail
 KanjiVerb_5r( 仰せつかる, JAP_TRANSITIVE ) // (v5r,vt) to receive a command/to be appointed/to be ordered
 KanjiVerb_5r( 仰せ付かる, JAP_TRANSITIVE ) // (v5r,vt) to receive a command/to be appointed/to be ordered
 KanjiVerb_5r( 句切る, JAP_TRANSITIVE ) // (v5r,vt) to punctuate/to cut off/to mark off/to delimit/to stop/to put an end to
 KanjiVerb_5r( 区切る, JAP_TRANSITIVE ) // (v5r,vt) to punctuate/to cut off/to mark off/to delimit/to stop/to put an end to/(P)
 KanjiVerb_5r( 駆る, JAP_TRANSITIVE ) // (v5r,vt) to drive (car)/to spur on/to impel/(P)
 KanjiVerb_5r( 隈取る, JAP_TRANSITIVE ) // (v5r,vt) to make up/to shade
 KanjiVerb_5r( 繰る, JAP_TRANSITIVE ) // (v5r,vt) to reel/to wind/(P)
 KanjiVerb_5r( 契る, JAP_TRANSITIVE ) // (v5r,vt) to pledge/to promise/to swear
 KanjiVerb_5r( 計る, JAP_TRANSITIVE ) // (v5r,vt) to measure/to weigh/to survey/to time (sound, gauge, estimate)/(P)
 KanjiVerb_5r( 撃ちまくる, JAP_TRANSITIVE ) // (v5r,vt) to pound away
 KanjiVerb_5r( 嫌がる, JAP_TRANSITIVE ) // (v5r,vt) to hate/to dislike/(P)
 KanjiVerb_5r( 捲る, JAP_TRANSITIVE ) // (v5r,vt) to turn over/to turn pages of a book/to tear off/to strip off/(P)
 KanjiVerb_5r( 献じる, JAP_TRANSITIVE ) // (v5r,vt) to present/to offer/to dedicate
 KanjiVerb_5r( 見くびる, JAP_TRANSITIVE ) // (v5r,vt) to underrate/to belittle/to look down on/to despise
 KanjiVerb_5r( 見て取る, JAP_TRANSITIVE ) // (v5r,vt) to perceive/to grasp (the situation)
 KanjiVerb_5r( 見遣る, JAP_TRANSITIVE ) // (v5r,vt) to look at
 KanjiVerb_5r( 見限る, JAP_TRANSITIVE ) // (v5r,vt) to give up/to turn one's back/to abandon/(P)
 KanjiVerb_5r( 見誤る, JAP_TRANSITIVE ) // (v5r,vt) to mistake someone for someone else/to misread
 KanjiVerb_5r( 見取る, JAP_TRANSITIVE ) // (v5r,vt) to perceive/to understand
 KanjiVerb_5r( 見守る, JAP_TRANSITIVE ) // (v5r,vt) to watch over/to watch attentively/(P)
 KanjiVerb_5r( 見切る, JAP_TRANSITIVE ) // (v5r,vt) to see everything/to abandon/to sell at a loss
 KanjiVerb_5r( 見送る, JAP_TRANSITIVE ) // (v5r,vt) (1) to see off/to farewell/(2) to escort/(3) to let pass/to wait and see/(4) to let a pitch go by (baseball)/to watch a batted ball go into the stands/(P)
 KanjiVerb_5r( 見知る, JAP_TRANSITIVE ) // (v5r,vt) to recognise/to know by sight/to become acquainted with
 KanjiVerb_5r( 見張る, JAP_TRANSITIVE ) // (v5r,vt) to watch/to (stand) guard/to look out/to open one's eyes wide/(P)
 KanjiVerb_5r( 見破る, JAP_TRANSITIVE ) // (v5r,vt) to see through another's thoughts/to have a sharp eye/to penetrate/to fathom/(P)
 KanjiVerb_5r( 見縊る, JAP_TRANSITIVE ) // (v5r,vt) to underrate/to belittle/to look down on/to despise/(P)
 KanjiVerb_5r( 遣る, JAP_TRANSITIVE ) // (v5r,vt) (col) (uk) to do/to have sexual intercourse/to kill/to give (to inferiors, animals, etc.)/to dispatch (a letter)/to despatch/to send/to study/to perform/to play (sports, game)/to have (eat, drink, smoke)/to row (a boat)/to run or operate (a restaurant)
 KanjiVerb_5r( 言い捲る, JAP_TRANSITIVE ) // (v5r,vt) to talk volubly
 KanjiVerb_5r( 言い遣る, JAP_TRANSITIVE ) // (v5r,vt) to send word
 KanjiVerb_5r( 言い誤る, JAP_TRANSITIVE ) // (v5r,vt) to say by mistake/to make a slip of the tongue
 KanjiVerb_5r( 言い渋る, JAP_TRANSITIVE ) // (v5r,vt) to hesitate to say
 KanjiVerb_5r( 言い切る, JAP_TRANSITIVE ) // (v5r,vt) to declare/to assert/to state definitively/(P)
 KanjiVerb_5r( 言い送る, JAP_TRANSITIVE ) // (v5r,vt) to send a message/to write to
 KanjiVerb_5r( 言い張る, JAP_TRANSITIVE ) // (v5r,vt) to insist/to assert/to be obstinate in saying
 KanjiVerb_5r( 言い破る, JAP_TRANSITIVE ) // (v5r,vt) to argue down/to confute
 KanjiVerb_5r( 言い付かる, JAP_TRANSITIVE ) // (v5r,vt) to be ordered
 KanjiVerb_5r( 言捲る, JAP_TRANSITIVE ) // (v5r,vt) to talk volubly
 KanjiVerb_5r( 言遣る, JAP_TRANSITIVE ) // (v5r,vt) to send word
 KanjiVerb_5r( 言誤る, JAP_TRANSITIVE ) // (v5r,vt) to say by mistake/to make a slip of the tongue
 KanjiVerb_5r( 言渋る, JAP_TRANSITIVE ) // (v5r,vt) to hesitate to say
 KanjiVerb_5r( 言切る, JAP_TRANSITIVE ) // (v5r,vt) to declare/to assert/to state definitively
 KanjiVerb_5r( 言送る, JAP_TRANSITIVE ) // (v5r,vt) to send a message/to write to
 KanjiVerb_5r( 言張る, JAP_TRANSITIVE ) // (v5r,vt) to insist/to assert/to be obstinate in saying
 KanjiVerb_5r( 言破る, JAP_TRANSITIVE ) // (v5r,vt) to argue down/to confute
 KanjiVerb_5r( 言付かる, JAP_TRANSITIVE ) // (v5r,vt) to be entrusted with/to be asked to
 KanjiVerb_5r( 呼び回る, JAP_TRANSITIVE ) // (v5r,vt) to call out (for someone)
 KanjiVerb_5r( 悟る, JAP_TRANSITIVE ) // (v5r,vt) to attain enlightenment/to perceive/to understand/to discern/(P)
 KanjiVerb_5r( 語る, JAP_TRANSITIVE ) // (v5r,vt) to talk/to tell/to recite/(P)
 KanjiVerb_5r( 口走る, JAP_TRANSITIVE ) // (v5r,vt) to speak/to tell/to blurt out/(P)
 KanjiVerb_5r( 巧む, JAP_TRANSITIVE ) // (v5r,vt) to devise/to plot/to plan
 KanjiVerb_5r( 絞り取る, JAP_TRANSITIVE ) // (v5r,vt) to squeeze or wring out from
 KanjiVerb_5r( 絞る, JAP_TRANSITIVE ) // (v5r,vt) to press/to wring/to squeeze/(P)
 KanjiVerb_5r( 告る, JAP_TRANSITIVE ) // (v5r,vt) to confess (one's love)
 KanjiVerb_5r( 差し繰る, JAP_TRANSITIVE ) // (v5r,vt) to arrange/to manage
 KanjiVerb_5r( 彩る, JAP_TRANSITIVE ) // (v5r,vt) to colour/to color/to paint/to make up/(P)
 KanjiVerb_5r( 採る, JAP_TRANSITIVE ) // (v5r,vt) (1) to adopt (measure, proposal)/(2) to pick (fruit)/(3) to assume (attitude)/(P)
 KanjiVerb_5r( 祭る, JAP_TRANSITIVE ) // (v5r,vt) to deify/to enshrine/(P)
 KanjiVerb_5r( 裁ち割る, JAP_TRANSITIVE ) // (v5r,vt) to cut open/to cut apart/to divide
 KanjiVerb_5r( 作る, JAP_TRANSITIVE ) // (v5r,vt) to make/to create/to manufacture/to draw up/to write/to compose/to build/to coin/to cultivate/to organize/to organise/to establish/to make up (a face)/to trim (a tree)/to fabricate/to prepare (food)/to commit (sin)/to construct/(P)
 KanjiVerb_5r( 削る, JAP_TRANSITIVE ) // (v5r,vt) (1) to cut down little by little/(2) to take a percentage
 KanjiVerb_5r( 搾り取る, JAP_TRANSITIVE ) // (v5r,vt) to exploit
 KanjiVerb_5r( 搾る, JAP_TRANSITIVE ) // (v5r,vt) to press/to wring/to squeeze/(P)
 KanjiVerb_5r( 刷る, JAP_TRANSITIVE ) // (v5r,vt) to print/(P)
 KanjiVerb_5r( 撮る, JAP_TRANSITIVE ) // (v5r,vt) to take (a photo)/to make (a film)/(P)
 KanjiVerb_5r( 擦る, JAP_TRANSITIVE ) // (v5r,vt) to rub/to chafe/to file/to frost (glass)/to strike (match)/(P)
 KanjiVerb_5r( 仕掛かる, JAP_TRANSITIVE ) // (v5r,vt) (1) to start something/(2) to have started something, but not yet finished it
 KanjiVerb_5r( 仕掛る, JAP_TRANSITIVE ) // (v5r,vt) (1) to start something/(2) to have started something, but not yet finished it
 KanjiVerb_5r( 仕懸かる, JAP_TRANSITIVE ) // (v5r,vt) (1) to start something/(2) to have started something, but not yet finished it
 KanjiVerb_5r( 仕懸る, JAP_TRANSITIVE ) // (v5r,vt) (1) to start something/(2) to have started something, but not yet finished it
 KanjiVerb_5r( 仕切る, JAP_TRANSITIVE ) // (v5r,vt) to partition/to divide/to mark off/to settle accounts/to toe the mark
 KanjiVerb_5r( 使い切る, JAP_TRANSITIVE ) // (v5r,vt) to use up/to exhaust/to wear out
 KanjiVerb_5r( 司る, JAP_TRANSITIVE ) // (v5r,vt) to rule/to govern/to administer
 KanjiVerb_5r( 思いとどまる, JAP_TRANSITIVE ) // (v5r,vt) to give up (a plan or idea or idea)/to desist from (doing)/(P)
 KanjiVerb_5r( 思い止どまる, JAP_TRANSITIVE ) // (v5r,vt) to give up (a plan or idea or idea)/to desist from (doing)
 KanjiVerb_5r( 思い止まる, JAP_TRANSITIVE ) // (v5r,vt) to give up (a plan or idea or idea)/to desist from (doing)
 KanjiVerb_5r( 思い知る, JAP_TRANSITIVE ) // (v5r,vt) to realize/to realise
 KanjiVerb_5r( 諮る, JAP_TRANSITIVE ) // (v5r,vt) to consult with/to confer/(P)
 KanjiVerb_5r( 賜る, JAP_TRANSITIVE ) // (v5r,vt) to be given/to be granted/to be honored with/to be honoured with
 KanjiVerb_5r( 賜わる, JAP_TRANSITIVE ) // (v5r,vt) to be given/to be granted/to be honored with/to be honoured with
 KanjiVerb_5r( 持ち回る, JAP_TRANSITIVE ) // (v5r,vt) to carry about
 KanjiVerb_5r( 叱る, JAP_TRANSITIVE ) // (v5r,vt) to scold/(P)
 KanjiVerb_5r( 執る, JAP_TRANSITIVE ) // (v5r,vt) to take (trouble)/to attend (to business)/to command (army)/(P)
 KanjiVerb_5r( 捨て去る, JAP_TRANSITIVE ) // (v5r,vt) to abandon (ship)
 KanjiVerb_5r( 遮る, JAP_TRANSITIVE ) // (v5r,vt) to interrupt/to intercept/to obstruct/(P)
 KanjiVerb_5r( 借り切る, JAP_TRANSITIVE ) // (v5r,vt) to reserve
 KanjiVerb_5r( 借る, JAP_TRANSITIVE ) // (v5r,vt) to borrow/to have a loan/to hire/to rent/to buy on credit
 KanjiVerb_5r( 取り去る, JAP_TRANSITIVE ) // (v5r,vt) to remove/to eliminate
 KanjiVerb_5r( 取り仕切る, JAP_TRANSITIVE ) // (v5r,vt) to run or operate a business/to manage all by oneself
 KanjiVerb_5r( 取り締まる, JAP_TRANSITIVE ) // (v5r,vt) to manage/to control/to supervise/(P)
 KanjiVerb_5r( 取る, JAP_TRANSITIVE ) // (v5r,vt) to take/to pick up/to harvest/to earn/to choose/(P)
 KanjiVerb_5r( 取去る, JAP_TRANSITIVE ) // (v5r,vt) to remove/to eliminate
 KanjiVerb_5r( 取仕切る, JAP_TRANSITIVE ) // (v5r,vt) to run or operate a business/to manage all by oneself
 KanjiVerb_5r( 取締まる, JAP_TRANSITIVE ) // (v5r,vt) to manage/to control/to supervise
 KanjiVerb_5r( 守る, JAP_TRANSITIVE ) // (v5r,vt) to protect/to obey/to guard/to abide (by the rules)/(P)
 KanjiVerb_5r( 手繰る, JAP_TRANSITIVE ) // (v5r,vt) to pull in (rope)
 KanjiVerb_5r( 狩る, JAP_TRANSITIVE ) // (v5r,vt) to hunt
 KanjiVerb_5r( 受け取る, JAP_TRANSITIVE ) // (v5r,vt) to receive/to get/to accept/to take/to interpret/to understand/(P)
 KanjiVerb_5r( 受取る, JAP_TRANSITIVE ) // (v5r,vt) to receive/to get/to accept/to take/to interpret/to understand
 KanjiVerb_5r( 授かる, JAP_TRANSITIVE ) // (v5r,vt) to be gifted/to be awarded/(P)
 KanjiVerb_5r( 蹴る, JAP_TRANSITIVE ) // (v5r,vt) to kick/(P)
 KanjiVerb_5r( 蹴破る, JAP_TRANSITIVE ) // (v5r,vt) to kick in or open/to smash through
 KanjiVerb_5r( 出し渋る, JAP_TRANSITIVE ) // (v5r,vt) to grudge/to be stingy/to be unwilling to pay
 KanjiVerb_5r( 出し切る, JAP_TRANSITIVE ) // (v5r,vt) to use up/to do one's best
 KanjiVerb_5r( 出渋る, JAP_TRANSITIVE ) // (v5r,vt) to be unwilling to go out
 KanjiVerb_5r( 出切る, JAP_TRANSITIVE ) // (v5r,vt) to be out of/to have no more at hand
 KanjiVerb_5r( 書きなぐる, JAP_TRANSITIVE ) // (v5r,vt) to scribble (write quickly)/to dash off
 KanjiVerb_5r( 書き殴る, JAP_TRANSITIVE ) // (v5r,vt) to scribble (write quickly)/to dash off
 KanjiVerb_5r( 書き捲る, JAP_TRANSITIVE ) // (v5r,vt) to dash off/to write freely
 KanjiVerb_5r( 書き誤る, JAP_TRANSITIVE ) // (v5r,vt) to miswrite
 KanjiVerb_5r( 書き取る, JAP_TRANSITIVE ) // (v5r,vt) to write down/to take dictation/to take notes/(P)
 KanjiVerb_5r( 書き送る, JAP_TRANSITIVE ) // (v5r,vt) to write
 KanjiVerb_5r( 勝ちとる, JAP_TRANSITIVE ) // (v5r,vt) to exert oneself and win/to gain (victory)
 KanjiVerb_5r( 勝ち取る, JAP_TRANSITIVE ) // (v5r,vt) to exert oneself and win/to gain (victory)
 KanjiVerb_5r( 召し上がる, JAP_TRANSITIVE ) // (v5r,vt) (pol) to eat/(P)
 KanjiVerb_5r( 召し捕る, JAP_TRANSITIVE ) // (v5r,vt) to arrest/to apprehend
 KanjiVerb_5r( 承る, JAP_TRANSITIVE ) // (v5r,vt) (1) (hum) to hear/to be told/to know/(2) to receive (order)/(P)
 KanjiVerb_5r( 消し去る, JAP_TRANSITIVE ) // (v5r,vt) to get rid of/to erase
 KanjiVerb_5r( 焼き切る, JAP_TRANSITIVE ) // (v5r,vt) to burn off
 KanjiVerb_5r( 乗っ取る, JAP_TRANSITIVE ) // (v5r,vt) to capture/to occupy/to usurp/(P)
 KanjiVerb_5r( 乗り取る, JAP_TRANSITIVE ) // (v5r,vt) to capture/to occupy/to usurp
 KanjiVerb_5r( 譲る, JAP_TRANSITIVE ) // (v5r,vt) to turn over/to assign/to hand over/to transmit/to convey/to sell/to dispose of/to yield/to surrender/(P)
 KanjiVerb_5r( 飾る, JAP_TRANSITIVE ) // (v5r,vt) to decorate/to ornament/to adorn/(P)
 KanjiVerb_5r( 拭い取る, JAP_TRANSITIVE ) // (v5r,vt) to wipe off/to wipe out/to expunge
 KanjiVerb_5r( 拭き取る, JAP_TRANSITIVE ) // (v5r,vt) to wipe off/to wipe up
 KanjiVerb_5r( 織る, JAP_TRANSITIVE ) // (v5r,vt) to weave/(P)
 KanjiVerb_5r( 色取る, JAP_TRANSITIVE ) // (v5r,vt) to colour/to color/to paint/to make up
 KanjiVerb_5r( 食い切る, JAP_TRANSITIVE ) // (v5r,vt) to bite through/to eat up
 KanjiVerb_5r( 食い縛る, JAP_TRANSITIVE ) // (v5r,vt) to set one's teeth/to clench one's teeth
 KanjiVerb_5r( 食縛る, JAP_TRANSITIVE ) // (v5r,vt) to set one's teeth/to clench one's teeth
 KanjiVerb_5r( 寝取る, JAP_TRANSITIVE ) // (v5r,vt) to steal another's wife (husband, lover)
 KanjiVerb_5r( 振り絞る, JAP_TRANSITIVE ) // (v5r,vt) (1) to muster (one's strength)/(2) to strain (e.g., one's voice)
 KanjiVerb_5r( 振り切る, JAP_TRANSITIVE ) // (v5r,vt) to shake off/to shake free from/(P)
 KanjiVerb_5r( 振る, JAP_TRANSITIVE ) // (v5r,vt) (1) to wave/to shake/to swing/(2) to sprinkle/(3) to cast (actor)/to allocate (work)/(4) to turn down (somebody)/to reject/to jilt/(5) to abandon/to give up/to ruin/(P)
 KanjiVerb_5r( 申し送る, JAP_TRANSITIVE ) // (v5r,vt) to write to/to send word to/to hand over (official business)
 KanjiVerb_5r( 進ずる, JAP_TRANSITIVE ) // (v5r,vt) to offer/to present
 KanjiVerb_5r( 図る, JAP_TRANSITIVE ) // (v5r,vt) to plot/to attempt/to plan/to take in/to deceive/to devise/to design/to refer A to B/(P)
 KanjiVerb_5r( 推し計る, JAP_TRANSITIVE ) // (v5r,vt) to guess/to conjecture/to surmise
 KanjiVerb_5r( 推し測る, JAP_TRANSITIVE ) // (v5r,vt) to guess/to conjecture/to surmise
 KanjiVerb_5r( 推し量る, JAP_TRANSITIVE ) // (v5r,vt) to guess/to conjecture/to surmise
 KanjiVerb_5r( 生け捕る, JAP_TRANSITIVE ) // (v5r,vt) to capture alive/to take prisoner
 KanjiVerb_5r( 切り割る, JAP_TRANSITIVE ) // (v5r,vt) to cut in two
 KanjiVerb_5r( 切り捲る, JAP_TRANSITIVE ) // (v5r,vt) to attack and scatter/to argue vehemently
 KanjiVerb_5r( 切り取る, JAP_TRANSITIVE ) // (v5r,vt) to cut off/to excise/to tear off/to cut out/to whittle down/to tear out/to cut down/to amputate
 KanjiVerb_5r( 切り入る, JAP_TRANSITIVE ) // (v5r,vt) to cut into/to raid
 KanjiVerb_5r( 切り破る, JAP_TRANSITIVE ) // (v5r,vt) to cut to pieces
 KanjiVerb_5r( 折る, JAP_TRANSITIVE ) // (v5r,vt) to break/to fold/to pick flower/(P)
 KanjiVerb_5r( 煎る, JAP_TRANSITIVE ) // (v5r,vt) to parch/to fry/to fire/to broil/to roast/to boil down (in oil)
 KanjiVerb_5r( 穿る, JAP_TRANSITIVE ) // (v5r,vt) (uk) to dig up/to peck at
 KanjiVerb_5r( 選りすぐる, JAP_TRANSITIVE ) // (v5r,vt) to choose the best
 KanjiVerb_5r( 選る, JAP_TRANSITIVE ) // (v5r,vt) to choose/to select/(P)
 KanjiVerb_5r( 創る, JAP_TRANSITIVE ) // (v5r,vt) to make/to create/to manufacture/to draw up/to write/to compose/to build/to coin/to cultivate/to organize/to organise/to establish/to make up (a face)/to trim (a tree)/to fabricate/to prepare (food)/to commit (sin)/to construct
 KanjiVerb_5r( 掻い繰る, JAP_TRANSITIVE ) // (v5r,vt) to haul in hand over hand
 KanjiVerb_5r( 掻き切る, JAP_TRANSITIVE ) // (v5r,vt) to cut/to slit
 KanjiVerb_5r( 掻き毟る, JAP_TRANSITIVE ) // (v5r,vt) to tear off/to pluck/to scratch off
 KanjiVerb_5r( 操る, JAP_TRANSITIVE ) // (v5r,vt) to manipulate/to operate/to pull strings/(P)
 KanjiVerb_5r( 相手取る, JAP_TRANSITIVE ) // (v5r,vt) to take on an opponent/to challenge/(P)
 KanjiVerb_5r( 葬り去る, JAP_TRANSITIVE ) // (v5r,vt) to consign to oblivion
 KanjiVerb_5r( 葬る, JAP_TRANSITIVE ) // (v5r,vt) to bury/to inter/to entomb/to consign to oblivion/to shelve/(P)
 KanjiVerb_5r( 送る, JAP_TRANSITIVE ) // (v5r,vt) to send (a thing)/to dispatch/to despatch/to take or escort (a person somewhere)/to see off (a person)/to spend a period of time/to live a life/(P)
 KanjiVerb_5r( 贈る, JAP_TRANSITIVE ) // (v5r,vt) to send/to give to/to award to/to confer on/(P)
 KanjiVerb_5r( 造る, JAP_TRANSITIVE ) // (v5r,vt) to make/to create/to manufacture/to draw up/to write/to compose/to build/to coin/to cultivate/to organize/to organise/to establish/to make up (a face)/to trim (a tree)/to fabricate/to prepare (food)/to commit (sin)/to construct/(P)
 KanjiVerb_5r( 測る, JAP_TRANSITIVE ) // (v5r,vt) to measure/to weigh/to survey/to time (sound, gauge, estimate)/(P)
 KanjiVerb_5r( 打ちまくる, JAP_TRANSITIVE ) // (v5r,vt) to pound away
 KanjiVerb_5r( 打ち割る, JAP_TRANSITIVE ) // (v5r,vt) to split/to disclose
 KanjiVerb_5r( 打ち取る, JAP_TRANSITIVE ) // (v5r,vt) (1) to arrest/to take prisoner/(2) to kill/(3) to get someone out (in baseball)
 KanjiVerb_5r( 打ち切る, JAP_TRANSITIVE ) // (v5r,vt) to stop/to abort/to discontinue/to close/(P)
 KanjiVerb_5r( 打ち破る, JAP_TRANSITIVE ) // (v5r,vt) to hit
 KanjiVerb_5r( 打ん殴る, JAP_TRANSITIVE ) // (v5r,vt) to knock
 KanjiVerb_5r( 打取る, JAP_TRANSITIVE ) // (v5r,vt) (1) to arrest/to take prisoner/(2) to kill/(3) to get someone out (in baseball)
 KanjiVerb_5r( 貸し切る, JAP_TRANSITIVE ) // (v5r,vt) to reserve/to charter
 KanjiVerb_5r( 択る, JAP_TRANSITIVE ) // (v5r,vt) to choose/to select
 KanjiVerb_5r( 叩き割る, JAP_TRANSITIVE ) // (v5r,vt) to smash/to break into pieces
 KanjiVerb_5r( 奪い取る, JAP_TRANSITIVE ) // (v5r,vt) to plunder
 KanjiVerb_5r( 辿る, JAP_TRANSITIVE ) // (v5r,vt) to follow (road)/to pursue (course)/to follow up/(P)
 KanjiVerb_5r( 探る, JAP_TRANSITIVE ) // (v5r,vt) to search/to look for/to sound out/(P)
 KanjiVerb_5r( 端折る, JAP_TRANSITIVE ) // (v5r,vt) to tuck up/to abridge
 KanjiVerb_5r( 断ち切る, JAP_TRANSITIVE ) // (v5r,vt) to sever/to break off/to cut asunder/to cut off/to block/to disconnect
 KanjiVerb_5r( 断る, JAP_TRANSITIVE ) // (v5r,vt) (1) to refuse/to reject/to dismiss/to turn down/to decline/(2) to inform/to give notice/(3) to ask leave/to excuse oneself (from)/(P)
 KanjiVerb_5r( 断わる, JAP_TRANSITIVE ) // (v5r,vt) (1) to refuse/to reject/to dismiss/to turn down/to decline/(2) to inform/to give notice/(3) to ask leave/to excuse oneself (from)
 KanjiVerb_5r( 値切る, JAP_TRANSITIVE ) // (v5r,vt) to drive a bargain/to beat down the price/to haggle/(P)
 KanjiVerb_5r( 知る, JAP_TRANSITIVE ) // (v5r,vt) to know/to understand/to be acquainted with/to feel/(P)
 KanjiVerb_5r( 着飾る, JAP_TRANSITIVE ) // (v5r,vt) to dress up/(P)
 KanjiVerb_5r( 彫る, JAP_TRANSITIVE ) // (v5r,vt) (1) to carve/to engrave/to sculpture/to chisel/(2) to tattoo/(P)
 KanjiVerb_5r( 珍しがる, JAP_TRANSITIVE ) // (v5r,vt) to think (it) a curiosity
 KanjiVerb_5r( 追いやる, JAP_TRANSITIVE ) // (v5r,vt) (1) to drive away/to order off/to chase away/(2) to force into an unpleasant situation (bankruptcy, prostitution, suicide, etc.)
 KanjiVerb_5r( 追い遣る, JAP_TRANSITIVE ) // (v5r,vt) (1) to drive away/to order off/to chase away/(2) to force into an unpleasant situation (bankruptcy, prostitution, suicide, etc.)
 KanjiVerb_5r( 爪繰る, JAP_TRANSITIVE ) // (v5r,vt) to finger/to roll between the thumb and the fingers
 KanjiVerb_5r( 釣る, JAP_TRANSITIVE ) // (v5r,vt) to fish/(P)
 KanjiVerb_5r( 剃る, JAP_TRANSITIVE ) // (v5r,vt) to shave/(P)
 KanjiVerb_5r( 締めくくる, JAP_TRANSITIVE ) // (v5r,vt) to bind firmly/to superintend/to bring to a finish
 KanjiVerb_5r( 締め括る, JAP_TRANSITIVE ) // (v5r,vt) to bind firmly/to superintend/to bring to a finish
 KanjiVerb_5r( 締め切る, JAP_TRANSITIVE ) // (v5r,vt) to close up/to shut up (e.g., behind doors)/to cut off (e.g., because a deadline has expired)/(P)
 KanjiVerb_5r( 摘み取る, JAP_TRANSITIVE ) // (v5r,vt) to pluck/to pick/to nip off
 KanjiVerb_5r( 塗りたくる, JAP_TRANSITIVE ) // (v5r,vt) to bedaub (with paint)/to besmear/to paint heavily
 KanjiVerb_5r( 塗る, JAP_TRANSITIVE ) // (v5r,vt) to paint/to plaster/to lacquer/to varnish/(P)
 KanjiVerb_5r( 屠る, JAP_TRANSITIVE ) // (v5r,vt) to slaughter/to massacre/to defeat/to butcher
 KanjiVerb_5r( 盗み取る, JAP_TRANSITIVE ) // (v5r,vt) to steal
 KanjiVerb_5r( 討ち取る, JAP_TRANSITIVE ) // (v5r,vt) (1) to arrest/to take prisoner/(2) to kill/(3) to get someone out (in baseball)
 KanjiVerb_5r( 討取る, JAP_TRANSITIVE ) // (v5r,vt) (1) to arrest/to take prisoner/(2) to kill/(3) to get someone out (in baseball)
 KanjiVerb_5r( 踏みにじる, JAP_TRANSITIVE ) // (v5r,vt) to trample underfoot/to tread on/to crush with a foot
 KanjiVerb_5r( 踏み切る, JAP_TRANSITIVE ) // (v5r,vt) to make a bold start/to take a plunge/to take off/(P)
 KanjiVerb_5r( 踏み破る, JAP_TRANSITIVE ) // (v5r,vt) to walk across/to travel on foot
 KanjiVerb_5r( 踏み躙る, JAP_TRANSITIVE ) // (v5r,vt) to trample underfoot/to tread on/to crush with a foot
 KanjiVerb_5r( 読み誤る, JAP_TRANSITIVE ) // (v5r,vt) to misread/to mispronounce
 KanjiVerb_5r( 読み取る, JAP_TRANSITIVE ) // (v5r,vt) (1) to read (someone's) mind/to read between the lines/(2) to read (a calibration, a tape, etc.)
 KanjiVerb_5r( 読み切る, JAP_TRANSITIVE ) // (v5r,vt) to finish reading/to read through
 KanjiVerb_5r( 読み破る, JAP_TRANSITIVE ) // (v5r,vt) to read through (difficult passage or particularly long book)
 KanjiVerb_5r( 突き破る, JAP_TRANSITIVE ) // (v5r,vt) to break through/to penetrate/to pierce
 KanjiVerb_5r( 突っきる, JAP_TRANSITIVE ) // (v5r,vt) to cross/to go across/to go through/to cut across
 KanjiVerb_5r( 突っ切る, JAP_TRANSITIVE ) // (v5r,vt) to cross/to go across/to go through/to cut across
 KanjiVerb_5r( 捻くる, JAP_TRANSITIVE ) // (v5r,vt) to twirl/to spin/to fiddle with/to change wording
 KanjiVerb_5r( 捻じる, JAP_TRANSITIVE ) // (v5r,vt) (1) to screw/to twist/(2) to distort/(3) to torture/to wrest
 KanjiVerb_5r( 捻る, JAP_TRANSITIVE ) // (v5r,vt) to turn (a switch) on or off/to twist/to puzzle over/(P)
 KanjiVerb_5r( 撚る, JAP_TRANSITIVE ) // (v5r,vt) to twist (yarn)/to lay (rope)
 KanjiVerb_5r( 破る, JAP_TRANSITIVE ) // (v5r,vt) to tear/to violate/to defeat/to smash/to destroy/(P)
 KanjiVerb_5r( 敗る, JAP_TRANSITIVE ) // (v5r,vt) to tear/to violate/to defeat/to smash/to destroy
 KanjiVerb_5r( 配る, JAP_TRANSITIVE ) // (v5r,vt) to distribute/to deliver/(P)
 KanjiVerb_5r( 買いあおる, JAP_TRANSITIVE ) // (v5r,vt) to bid up/to corner the market
 KanjiVerb_5r( 買いかぶる, JAP_TRANSITIVE ) // (v5r,vt) to overestimate/to make too much of/(P)
 KanjiVerb_5r( 買い漁る, JAP_TRANSITIVE ) // (v5r,vt) to spend money freely
 KanjiVerb_5r( 買い取る, JAP_TRANSITIVE ) // (v5r,vt) to buy/to purchase
 KanjiVerb_5r( 買い切る, JAP_TRANSITIVE ) // (v5r,vt) to buy up
 KanjiVerb_5r( 買い煽る, JAP_TRANSITIVE ) // (v5r,vt) to bid up/to corner the market
 KanjiVerb_5r( 買い被る, JAP_TRANSITIVE ) // (v5r,vt) to overestimate/to make too much of
 KanjiVerb_5r( 売り渋る, JAP_TRANSITIVE ) // (v5r,vt) to be reluctant to sell
 KanjiVerb_5r( 売り切る, JAP_TRANSITIVE ) // (v5r,vt) to sell out/to sell off
 KanjiVerb_5r( 売る, JAP_TRANSITIVE ) // (v5r,vt) to sell/(P)
 KanjiVerb_5r( 剥ぎ取る, JAP_TRANSITIVE ) // (v5r,vt) to tear off/to strip/to rob
 KanjiVerb_5r( 剥る, JAP_TRANSITIVE ) // (v5r,vt) to pilfer/to steal a portion
 KanjiVerb_5r( 縛る, JAP_TRANSITIVE ) // (v5r,vt) to tie/to bind/(P)
 KanjiVerb_5r( 抜き取る, JAP_TRANSITIVE ) // (v5r,vt) to pull out/to draw out
 KanjiVerb_5r( 煩がる, JAP_TRANSITIVE ) // (v5r,vt) to feel annoyed at
 KanjiVerb_5r( 煩さがる, JAP_TRANSITIVE ) // (v5r,vt) to feel annoyed at
 KanjiVerb_5r( 被る, JAP_TRANSITIVE ) // (v5r,vt) to suffer/to receive/to sustain
 KanjiVerb_5r( 誹る, JAP_TRANSITIVE ) // (v5r,vt) to slander/to libel/to criticize/to criticise
 KanjiVerb_5r( 侮る, JAP_TRANSITIVE ) // (v5r,vt) to despise/to disdain/to make light of/(P)
 KanjiVerb_5r( 封じる, JAP_TRANSITIVE ) // (v5r,vt) (1) to seal (letter)/(2) to prevent/to forbid/(P)
 KanjiVerb_5r( 物語る, JAP_TRANSITIVE ) // (v5r,vt) to tell/to indicate/(P)
 KanjiVerb_5r( 分捕る, JAP_TRANSITIVE ) // (v5r,vt) to capture/to seize/to plunder
 KanjiVerb_5r( 聞き取る, JAP_TRANSITIVE ) // (v5r,vt) to catch (a person's words)/to follow/to understand/(P)
 KanjiVerb_5r( 聞き齧る, JAP_TRANSITIVE ) // (v5r,vt) to have a smattering knowledge of
 KanjiVerb_5r( 閉め切る, JAP_TRANSITIVE ) // (v5r,vt) to close up/to shut up (e.g., behind doors)/to cut off (e.g., because a deadline has expired)
 KanjiVerb_5r( 捕る, JAP_TRANSITIVE ) // (v5r,vt) to take/to catch (fish)/to capture/(P)
 KanjiVerb_5r( 奉る, JAP_TRANSITIVE ) // (v5r,vt) to offer/to present/to revere/to do respectfully
 KanjiVerb_5r( 放る, JAP_TRANSITIVE ) // (v5r,vt) (1) to let go/to abandon/to leave undone/(2) to throw/to toss/to fling/(P)
 KanjiVerb_5r( 褒めちぎる, JAP_TRANSITIVE ) // (v5r,vt) to praise (to the skies)/to sing the praises (of)/to extol
 KanjiVerb_5r( 忘れ去る, JAP_TRANSITIVE ) // (v5r,vt) to forget completely/to leave behind
 KanjiVerb_5r( 謀る, JAP_TRANSITIVE ) // (v5r,vt) to plot/to attempt/to plan/to take in/to deceive/to devise/to design/to refer A to B/(P)
 KanjiVerb_5r( 頬張る, JAP_TRANSITIVE ) // (v5r,vt) to stuff one's cheeks
 KanjiVerb_5r( 摩る, JAP_TRANSITIVE ) // (v5r,vt) to rub/to chafe/to file/to frost (glass)/to strike (match)
 KanjiVerb_5r( 磨る, JAP_TRANSITIVE ) // (v5r,vt) to rub/to chafe/to file/to frost (glass)/to strike (match)
 KanjiVerb_5r( 蒙る, JAP_TRANSITIVE ) // (v5r,vt) to suffer/to receive/to sustain
 KanjiVerb_5r( 野次る, JAP_TRANSITIVE ) // (v5r,vt) to jeer (at)/to hoot/to boo/to catcall/to heckle
 KanjiVerb_5r( 弥次る, JAP_TRANSITIVE ) // (v5r,vt) to jeer (at)/to hoot/to boo/to catcall/to heckle
 KanjiVerb_5r( 誉めちぎる, JAP_TRANSITIVE ) // (v5r,vt) to praise (to the skies)/to sing the praises (of)/to extol
 KanjiVerb_5r( 預かる, JAP_TRANSITIVE ) // (v5r,vt) to keep in custody/to receive on deposit/to take charge of/(P)
 KanjiVerb_5r( 揺る, JAP_TRANSITIVE ) // (v5r,vt) to shake/to jolt/to rock (cradle)/to swing/(P)
 KanjiVerb_5r( 欲しがる, JAP_TRANSITIVE ) // (v5r,vt) to desire/to want/to wish for/to covet/(P)
 KanjiVerb_5r( 頼み入る, JAP_TRANSITIVE ) // (v5r,vt) to entreat/to request earnestly
 KanjiVerb_5r( 裏切る, JAP_TRANSITIVE ) // (v5r,vt) to betray/to turn traitor to/to double-cross/(P)
 KanjiVerb_5r( 立て切る, JAP_TRANSITIVE ) // (v5r,vt) to close tight
 KanjiVerb_5r( 掠め取る, JAP_TRANSITIVE ) // (v5r,vt) to snatch/to steal
 KanjiVerb_5r( 慮る, JAP_TRANSITIVE ) // (v5r,vt) to consider
 KanjiVerb_5r( 量る, JAP_TRANSITIVE ) // (v5r,vt) to measure/to weigh/to survey/to time (sound, gauge, estimate)/(P)
 KanjiVerb_5r( 弄くる, JAP_TRANSITIVE ) // (v5r,vt) to finger/to tamper (with)
 KanjiVerb_5r( 弄る, JAP_TRANSITIVE ) // (v5r,vt) (1) to touch/to tamper with/(v5r,vt) (2) to grope about/to feel for something
 KanjiVerb_5r( 刳る, JAP_TRANSITIVE ) // (v5r,vt) to gouge/to hollow out/to bore/to excavate/to scoop out
 KanjiVerb_5r( 剔る, JAP_TRANSITIVE ) // (v5r,vt) to gouge/to hollow out/to bore/to excavate/to scoop out
 KanjiVerb_5r( 剪み切る, JAP_TRANSITIVE ) // (v5r,vt) to nip off/to snip/to clip/to trim off
 KanjiVerb_5r( 呷る, JAP_TRANSITIVE ) // (v5r,vt) to gulp down (a drink)/to slurp
 KanjiVerb_5r( 啜る, JAP_TRANSITIVE ) // (v5r,vt) (uk) to sip/to slurp
 KanjiVerb_5r( 嘲る, JAP_TRANSITIVE ) // (v5r,vt) (uk) to scoff/(P)
 KanjiVerb_5r( 娶る, JAP_TRANSITIVE ) // (v5r,vt) to marry (a woman) to take to wife
 KanjiVerb_5r( 嬲る, JAP_TRANSITIVE ) // (v5r,vt) to tease/to make sport of/to make fun of
 KanjiVerb_5r( 截ち切る, JAP_TRANSITIVE ) // (v5r,vt) to sever/to break off/to cut asunder/to cut off/to block/to disconnect
 KanjiVerb_5r( 抉る, JAP_TRANSITIVE ) // (v5r,vt) to gouge/to hollow out/to bore/to excavate/to scoop out
 KanjiVerb_5r( 抓る, JAP_TRANSITIVE ) // (v5r,vt) to pinch
 KanjiVerb_5r( 拗じる, JAP_TRANSITIVE ) // (v5r,vt) (1) to screw/to twist/(2) to distort/(3) to torture/to wrest
 KanjiVerb_5r( 拈くる, JAP_TRANSITIVE ) // (v5r,vt) to twirl/to spin/to fiddle with/to change wording
 KanjiVerb_5r( 抛る, JAP_TRANSITIVE ) // (v5r,vt) (1) to let go/to abandon/to leave undone/(2) to throw/to toss/to fling
 KanjiVerb_5r( 掏る, JAP_TRANSITIVE ) // (v5r,vt) to pick someone's pocket
 KanjiVerb_5r( 捩じる, JAP_TRANSITIVE ) // (v5r,vt) (1) to screw/to twist/(2) to distort/(3) to torture/to wrest/(P)
 KanjiVerb_5r( 捩じ取る, JAP_TRANSITIVE ) // (v5r,vt) to wring off/to wrest from
 KanjiVerb_5r( 捩じ切る, JAP_TRANSITIVE ) // (v5r,vt) to twist off
 KanjiVerb_5r( 捩る, JAP_TRANSITIVE ) // (v5r,vt) to twist
 KanjiVerb_5r( 搦め捕る, JAP_TRANSITIVE ) // (v5r,vt) to arrest
 KanjiVerb_5r( 擽る, JAP_TRANSITIVE ) // (v5r,vt) (uk) to tickle/(P)
 KanjiVerb_5r( 梳る, JAP_TRANSITIVE ) // (v5r,vt) (1) to shave (wood or leather)/to sharpen/to plane/to whittle/to pare/to scrape off/(2) to cross out/to reduce/to curtail/to remove/to erase
 KanjiVerb_5r( 毟り取る, JAP_TRANSITIVE ) // (v5r,vt) to tear off/to pluck off
 KanjiVerb_5r( 毟る, JAP_TRANSITIVE ) // (v5r,vt) to pluck/to pick/to tear
 KanjiVerb_5r( 炙る, JAP_TRANSITIVE ) // (v5r,vt) (uk) to scorch/to broil/to toast
 KanjiVerb_5r( 炒る, JAP_TRANSITIVE ) // (v5r,vt) to parch/to fry/to fire/to broil/to roast/to boil down (in oil)
 KanjiVerb_5r( 焙る, JAP_TRANSITIVE ) // (v5r,vt) (uk) to scorch/to broil/to toast
 KanjiVerb_5r( 熬る, JAP_TRANSITIVE ) // (v5r,vt) to parch/to fry/to fire/to broil/to roast/to boil down (in oil)
 KanjiVerb_5r( 瞑る, JAP_TRANSITIVE ) // (v5r,vt) to close the eyes/(P)
 KanjiVerb_5r( 祀る, JAP_TRANSITIVE ) // (v5r,vt) to deify/to enshrine
 KanjiVerb_5r( 縒る, JAP_TRANSITIVE ) // (v5r,vt) to twist (yarn)/to lay (rope)
 KanjiVerb_5r( 縢がる, JAP_TRANSITIVE ) // (v5r,vt) to cross-stitch/to hemstitch/to sew (up)/to darn
 KanjiVerb_5r( 縢る, JAP_TRANSITIVE ) // (v5r,vt) to cross-stitch/to hemstitch/to sew (up)/to darn
 KanjiVerb_5r( 舐る, JAP_TRANSITIVE ) // (v5r,vt) to lick
 KanjiVerb_5r( 謗る, JAP_TRANSITIVE ) // (v5r,vt) to slander/to libel/to criticize/to criticise
 KanjiVerb_5r( 譏る, JAP_TRANSITIVE ) // (v5r,vt) to slander/to libel/to criticize/to criticise
 KanjiVerb_5r( 貪る, JAP_TRANSITIVE ) // (v5r,vt) (uk) to covet/to indulge in/to deeply desire/to lust insatiably for/(P)
 KanjiVerb_5r( 騙る, JAP_TRANSITIVE ) // (v5r,vt) to swindle/to deceive/to cheat
 KanjiVerb_5r( 齧る, JAP_TRANSITIVE ) // (v5r,vt) to chew/to bite (at)/to gnaw/to nibble/to munch/to crunch/to have a smattering of
 KanjiVerb_5r( お高く止まる ) // (v5r) to assume an air of importance/to be self-important/to put on airs
 KanjiVerb_5r( お高く留まる ) // (v5r) to assume an air of importance/to be self-important/to put on airs
 KanjiVerb_5r( お出でになる ) // (v5r) (hon) (uk) to be
 KanjiVerb_5r( お婆はる ) // (v5r) (sl) to shamelessly demand one's rights
 KanjiVerb_5r( かさかさ鳴る ) // (v5r) to rustle/to make a rustling sound/to crinkle
 KanjiVerb_5r( かんかん怒る ) // (v5r) to get very mad
 KanjiVerb_5r( くすくす笑う ) // (v5r) to giggle
 KanjiVerb_5r( ご免被る ) // (v5r) to be excused from
 KanjiVerb_5r( じろりと見る ) // (v5r) to throw a glance
 KanjiVerb_5r( すり寄る ) // (v5r,vi) to draw close to/to edge up to/to snuggle up to/to nestle close to/to cuddle with/to draw closer to
 KanjiVerb_5r( だまし取る ) // (v5r) to take something away by deception
 KanjiVerb_5r( ちんちん鳴る ) // (v5r) to jingle/to tinkle
 KanjiVerb_5r( つかみ取る ) // (v5r) to grasp/to get
 KanjiVerb_5r( つれ帰る ) // (v5r) to bring (someone) back home/to take (someone) back home
 KanjiVerb_5r( でんぐり返る ) // (v5r,vi) to turn a somersault/to turn over (topsy-turvy)/to turn head over heels
 KanjiVerb_5r( のたうち回る ) // (v5r,vi) to writhe
 KanjiVerb_5r( のぼせ上がる ) // (v5r,vi) to be beside oneself/to lose one's head/to go mad with something
 KanjiVerb_5r( はい回る ) // (v5r,vi) to creep about
 KanjiVerb_5r( はげ上がる ) // (v5r) to become bald fom the forehead/to recede
 KanjiVerb_5r( はね上がる ) // (v5r,vi) to jump up/to spring up
 KanjiVerb_5r( ひっくり返る ) // (v5r,vi) to be overturned/to be upset/to topple over/to be reversed
 KanjiVerb_5r( ぴかぴか光る ) // (v5r) to sparkle/to glitter/to twinkle
 KanjiVerb_5r( ぶち当たる ) // (v5r) (1) to slam into (e.g. a wall, a limit) (figuratively)/to hit/(2) to face (e.g. trouble, a problem)/to confront
 KanjiVerb_5r( ぶら下がる ) // (v5r,vi) to hang from/to dangle/to swing/(P)
 KanjiVerb_5r( ぷりぷり怒る ) // (v5r) to be in a huff
 KanjiVerb_5r( もぎ取る ) // (v5r) (uk) to pluck off/to pick/to break or tear off
 KanjiVerb_5r( やり切る ) // (v5r) (uk) complete decisively/to do to completion
 KanjiVerb_5r( よじ登る ) // (v5r,vi) to climb/to clamber (over, up)/to scramble (up)/to scale/to claw one's way up
 KanjiVerb_5r( ロムる ) // (v5r) to read a forum/to chat without posting a message/to lurk (from Read-Only Member)
 KanjiVerb_5r( 阿ねる ) // (v5r,vi) to flatter
 KanjiVerb_5r( 阿る ) // (v5r,vi) to flatter
 KanjiVerb_5r( 安く譲る ) // (v5r) to sell (a thing) cheap
 KanjiVerb_5r( 位取る ) // (v5r) to scale
 KanjiVerb_5r( 依る ) // (v5r,vi) (1) (uk) to be due to/to be caused by/(2) to depend on/to turn on/(3) to be based on/to come from
 KanjiVerb_5r( 偉がる ) // (v5r,vi) to be conceited
 KanjiVerb_5r( 威張り腐る ) // (v5r) to throw one's weight around/to be puffed up
 KanjiVerb_5r( 威張る ) // (v5r,vi) to be proud/to swagger/(P)
 KanjiVerb_5r( 為し終わる ) // (v5r,vi) to finish
 KanjiVerb_5r( 為る ) // (v5r,vi) to change/to be of use/to reach to
 KanjiVerb_5r( 畏まる ) // (v5r,vi) to obey respectfully/to humble oneself/to sit straight (upright, respectfully, attentively)
 KanjiVerb_5r( 畏れ入る ) // (v5r,vi) to be filled with awe/to feel small/to be amazed/to be surprised/to be disconcerted/to be sorry/to be grateful/to be defeated/to confess guilt
 KanjiVerb_5r( 異なる ) // (v5r,vi) to differ/to vary/to disagree/(P)
 KanjiVerb_5r( 移り変わる ) // (v5r) to change
 KanjiVerb_5r( 移る ) // (v5r,vi) (1) to move (house)/to transfer (department)/(2) to be infected/to be contagious/(P)
 KanjiVerb_5r( 一字削る ) // (v5r) to delete a letter
 KanjiVerb_5r( 一服盛る ) // (v5r) to poison
 KanjiVerb_5r( 一歩下がる ) // (v5r) to take a step backward
 KanjiVerb_5r( 一本取る ) // (v5r) to beat/to gain a point/to upset
 KanjiVerb_5r( 一脈相通じる ) // (v5r) to have in common (with)
 KanjiVerb_5r( 一脈相通ずる ) // (v5r) to have in common (with)
 KanjiVerb_5r( 逸る ) // (v5r) to be in high spirits/to be impatient/to be hotblooded
 KanjiVerb_5r( 因る ) // (v5r,vi) (1) (uk) to be due to/to be caused by/(2) to depend on/to turn on/(3) to be based on/to come from/(P)
 KanjiVerb_5r( 引きつる ) // (v5r) to have a cramp (spasm, convulsion, twitch)/to become stiff/(P)
 KanjiVerb_5r( 引き下がる ) // (v5r,vi) to withdraw/to leave
 KanjiVerb_5r( 引き締まる ) // (v5r,vi) to become tense/to be tightened/(P)
 KanjiVerb_5r( 引き締る ) // (v5r,vi) to become tense/to be tightened/(P)
 KanjiVerb_5r( 引き攣る ) // (v5r) to have a cramp (spasm, convulsion, twitch)/to become stiff
 KanjiVerb_5r( 引き籠る ) // (v5r,vi) to stay (confined) indoors
 KanjiVerb_5r( 引っくり返る ) // (v5r,vi) to be overturned/to be upset/to topple over/to be reversed
 KanjiVerb_5r( 引っ掛かる ) // (v5r,vi) to be caught in/to be stuck in/to be cheated/(P)
 KanjiVerb_5r( 引っ掛る ) // (v5r,vi) to be caught in/to be stuck in/to be cheated/(P)
 KanjiVerb_5r( 引っ繰り返る ) // (v5r,vi) to be overturned/to be upset/to topple over/to be reversed/(P)
 KanjiVerb_5r( 引下がる ) // (v5r,vi) to withdraw/to leave
 KanjiVerb_5r( 引攣る ) // (v5r) to have a cramp (spasm, convulsion, twitch)/to become stiff
 KanjiVerb_5r( 引籠る ) // (v5r,vi) to stay (confined) indoors
 KanjiVerb_5r( 陰る ) // (v5r,vi) to darken/to get dark/to be clouded/to be obscured
 KanjiVerb_5r( 隠る ) // (v5r,vi) to hide/to be hidden/to conceal oneself/to disappear
 KanjiVerb_5r( 窺い探る ) // (v5r) to spy out
 KanjiVerb_5r( 運び去る ) // (v5r) to carry away
 KanjiVerb_5r( 映じる ) // (v5r,vi) (1) to be reflected (in)/to be mirrored (in)/(2) to impress (a person)
 KanjiVerb_5r( 映る ) // (v5r,vi) to be reflected/to harmonize with/to harmonise with/to come out (photo)/(P)
 KanjiVerb_5r( 悦に入る ) // (v5r) to be pleased/to gloat/to glow with self-satisfaction
 KanjiVerb_5r( 煙たがる ) // (v5r,vi) to be sensitive to smoke
 KanjiVerb_5r( 煙る ) // (v5r,vi) (1) to smoke (e.g., fire)/(2) to be hazy/(P)
 KanjiVerb_5r( 遠ざかる ) // (v5r,vi) to go far off/(P)
 KanjiVerb_5r( 凹まる ) // (v5r,vi) to be low (as a hollow)
 KanjiVerb_5r( 奥まる ) // (v5r,vi) to lie deep in/to extend far back
 KanjiVerb_5r( 押しまくる ) // (v5r) to push and push/to keep pushing to the end
 KanjiVerb_5r( 押し詰まる ) // (v5r) to approach the year end/to be jammed tight
 KanjiVerb_5r( 押し捲くる ) // (v5r) to push and push/to keep pushing to the end
 KanjiVerb_5r( 押し通る ) // (v5r) to force one's way through
 KanjiVerb_5r( 押し渡る ) // (v5r) to cross over/to wade
 KanjiVerb_5r( 押し入る ) // (v5r) to push in/(P)
 KanjiVerb_5r( 押し迫る ) // (v5r,vi) to draw near
 KanjiVerb_5r( 押し黙る ) // (v5r,vi) to keep silent
 KanjiVerb_5r( 押渡る ) // (v5r) to cross over/to wade
 KanjiVerb_5r( 押入る ) // (v5r) to push in
 KanjiVerb_5r( 押迫る ) // (v5r,vi) to draw near
 KanjiVerb_5r( 押黙る ) // (v5r,vi) to keep silent
 KanjiVerb_5r( 横たわる ) // (v5r,vi) to lie down/to stretch out/(P)
 KanjiVerb_5r( 殴られて伸びる ) // (v5r) to be knocked out cold
 KanjiVerb_5r( 恩がある ) // (v5r) to be in one's debt
 KanjiVerb_5r( 温まる ) // (v5r,vi) to warm oneself/to sun oneself/to warm up/to get warm
 KanjiVerb_5r( 温もる ) // (v5r,vi) to get warm/to become warm
 KanjiVerb_5r( 下がる ) // (v5r,vi) to hang down/to abate/to retire/to fall/to step back/(P)
 KanjiVerb_5r( 下る ) // (v5r,vi) to get down/to descend/(P)
 KanjiVerb_5r( 下掛かる ) // (v5r,vi) to talk about indecent things
 KanjiVerb_5r( 下掛る ) // (v5r,vi) to talk about indecent things
 KanjiVerb_5r( 下司ばる ) // (v5r) to be churlish/to be vulgar
 KanjiVerb_5r( 加わる ) // (v5r,vi) to join in/to accede to/to increase/to gain in (influence)/(P)
 KanjiVerb_5r( 可愛がる ) // (v5r) to love/to be affectionate/(P)
 KanjiVerb_5r( 可笑しがる ) // (v5r) to be amused (by, at)/to wonder at
 KanjiVerb_5r( 暇取る ) // (v5r) to take time
 KanjiVerb_5r( 架かる ) // (v5r,vi) to place on an easel/to hang
 KanjiVerb_5r( 歌いまくる ) // (v5r) to sing energetically/to sing with abandon
 KanjiVerb_5r( 歌い捲る ) // (v5r) to sing energetically/to sing with abandon
 KanjiVerb_5r( 火照る ) // (v5r,vi) to feel hot/to flush/to burn
 KanjiVerb_5r( 稼ぎ取る ) // (v5r) to earn by working
 KanjiVerb_5r( 過ぎ去る ) // (v5r,vi) to pass/to pass away
 KanjiVerb_5r( 過去る ) // (v5r,vi) to pass/to pass away
 KanjiVerb_5r( 解る ) // (v5r,vi) (1) to understand/to grasp/(2) to know/to realize/to realise
 KanjiVerb_5r( 回る ) // (v5r,vi) to wander around
 KanjiVerb_5r( 廻る ) // (v5r,vi) to wander around
 KanjiVerb_5r( 改まる ) // (v5r,vi) (1) to be renewed/(2) to stand on ceremony/to be formal/(3) to take a turn for the worse/(P)
 KanjiVerb_5r( 開き直る ) // (v5r,vi) to become defiant/to turn upon/to become serious/(P)
 KanjiVerb_5r( 拡がる ) // (v5r,vi) to spread (out)/to extend/to stretch/to reach to/to get around
 KanjiVerb_5r( 格式張る ) // (v5r,vi) to adhere to formalities
 KanjiVerb_5r( 角張る ) // (v5r,vi) to be angular/to be overly ceremonious
 KanjiVerb_5r( 隔たる ) // (v5r,vi) to be distant/(P)
 KanjiVerb_5r( 革まる ) // (v5r,vi) (1) to be renewed/(2) to stand on ceremony/to be formal/(3) to take a turn for the worse
 KanjiVerb_5r( 学が有る ) // (v5r) to have learning/to be educated
 KanjiVerb_5r( 学び取る ) // (v5r) to collect information/to gather knowledge
 KanjiVerb_5r( 掛かる ) // (v5r,vi) to take (e.g., time, money, etc)/to hang/(P)
 KanjiVerb_5r( 割って入る ) // (v5r) to force one's way through
 KanjiVerb_5r( 割り切る ) // (v5r) to divide/to give a clear explanation/(P)
 KanjiVerb_5r( 割れ返る ) // (v5r,vi) to break completely/to (figuratively) bring the house down
 KanjiVerb_5r( 割切る ) // (v5r) to divide/to give a clear explanation
 KanjiVerb_5r( 滑り寄る ) // (v5r,vi) to slide up to
 KanjiVerb_5r( 滑り入る ) // (v5r,vi) to slide into
 KanjiVerb_5r( 滑る ) // (v5r,vi) to be slippery/to be slimy/to behave charmingly/to walk merrily
 KanjiVerb_5r( 乾固まる ) // (v5r) to dry and harden
 KanjiVerb_5r( 乾上がる ) // (v5r,vi) to dry up/to parch/to ebb away
 KanjiVerb_5r( 寒がる ) // (v5r,vi) to be bothered by coldness/to complain about the cold
 KanjiVerb_5r( 巻き上がる ) // (v5r,vi) to roll up/to be rolled up
 KanjiVerb_5r( 干上がる ) // (v5r,vi) to dry up/to parch/to ebb away
 KanjiVerb_5r( 感じ入る ) // (v5r,vi) to be impressed/to greatly admire
 KanjiVerb_5r( 感極まる ) // (v5r) to be overcome with emotion
 KanjiVerb_5r( 換わる ) // (v5r,vi) to take the place of/to relieve/to be substituted for/to be exchanged/to change places with/to take turns/to be replaced
 KanjiVerb_5r( 甘やかして育てる ) // (v5r) to bring up indulgently
 KanjiVerb_5r( 看取る ) // (v5r) to care for the sick
 KanjiVerb_5r( 緩まる ) // (v5r,vi) to become loose/to slacken/to soften
 KanjiVerb_5r( 還る ) // (v5r,vi) to send back/to return
 KanjiVerb_5r( 間切る ) // (v5r,vi) to plow through (a wave) (plough)/to tack (against the wind)
 KanjiVerb_5r( 関る ) // (v5r,vi) to concern oneself in/to have to do with/to affect/to influence/to stick to (opinions)
 KanjiVerb_5r( 関わる ) // (v5r,vi) to concern oneself in/to have to do with/to affect/to influence/to stick to (opinions)/(P)
 KanjiVerb_5r( 陥る ) // (v5r,vi) to fall/to trap/to cave in/to collapse/(P)
 KanjiVerb_5r( 丸まる ) // (v5r,vi) to become rounded/to roll into a ball/(P)
 KanjiVerb_5r( 頑張る ) // (v5r,vi) to persist/to insist on/to stand firm/to try one's best/(P)
 KanjiVerb_5r( 危ながる ) // (v5r,vi) to be afraid of/to feel uneasy about/to shrink from
 KanjiVerb_5r( 危篤である ) // (v5r) to be in critical condition/to be dangerously ill
 KanjiVerb_5r( 喜がる ) // (v5r) to satisfy oneself/to feel satisfied/to be proud
 KanjiVerb_5r( 嬉しがる ) // (v5r) to be glad
 KanjiVerb_5r( 寄っかかる ) // (v5r) to lean against/to recline on
 KanjiVerb_5r( 寄っ掛る ) // (v5r) to lean against/to recline on
 KanjiVerb_5r( 寄りかかる ) // (v5r,vi) to lean against/to recline on/to lean on/to rely on
 KanjiVerb_5r( 寄り掛かる ) // (v5r,vi) to lean against/to recline on/to lean on/to rely on/(P)
 KanjiVerb_5r( 寄り集まる ) // (v5r,vi) to gather together/(P)
 KanjiVerb_5r( 寄り縋る ) // (v5r,vi) to cling to/to rely on
 KanjiVerb_5r( 寄る ) // (v5r,vi) to visit/to drop in/to approach/(P)
 KanjiVerb_5r( 寄縋る ) // (v5r,vi) to cling to/to rely on
 KanjiVerb_5r( 帰る ) // (v5r,vi) to go back/to go home/to come home/to return/(P)
 KanjiVerb_5r( 気にかかる ) // (v5r,vi) to weigh on one's mind/to be worried about (something)
 KanjiVerb_5r( 気に掛かる ) // (v5r,vi) to weigh on one's mind/to be worried about (something)
 KanjiVerb_5r( 気に入る ) // (v5r) to be pleased with/to suit/(P)
 KanjiVerb_5r( 気張る ) // (v5r) to strain or exert oneself/to go all out
 KanjiVerb_5r( 祈る ) // (v5r,vi) to pray/to wish/(P)
 KanjiVerb_5r( 規則で縛る ) // (v5r) to restrict (a person) by rule
 KanjiVerb_5r( 起きあがる ) // (v5r,vi) to rise/to erect/to get up
 KanjiVerb_5r( 起き上がる ) // (v5r,vi) to rise/to erect/to get up/(P)
 KanjiVerb_5r( 起き直る ) // (v5r,vi) to sit up
 KanjiVerb_5r( 起こる ) // (v5r,vi) to occur/to happen/(P)
 KanjiVerb_5r( 輝き渡る ) // (v5r,vi) to shine out far and wide
 KanjiVerb_5r( 偽り語る ) // (v5r) to speak falsely
 KanjiVerb_5r( 偽る ) // (v5r,vi) to lie/to cheat/to falsify/to deceive/to pretend/(P)
 KanjiVerb_5r( 儀式張る ) // (v5r,vi) to formalize/to formalise/to stick to formality/to be ceremonious/to punctilious
 KanjiVerb_5r( 宜しくやる ) // (v5r) to make cozy with (cosy)/to do at one's own discretion
 KanjiVerb_5r( 戯る ) // (v5r,vi) (arch) to be playful/to gambol/to be amused (with something)/to play/to sport/to frolic/to joke
 KanjiVerb_5r( 掬い取る ) // (v5r) to dip or scoop up/to ladle out
 KanjiVerb_5r( 吃る ) // (v5r,vi) to stammer/to stutter/(P)
 KanjiVerb_5r( 詰まる ) // (v5r,vi) (1) to be blocked/to be packed/(2) to hit the ball near the handle of the bat (baseball)/(P)
 KanjiVerb_5r( 詰め寄る ) // (v5r,vi) to draw near/to draw closer
 KanjiVerb_5r( 詰め切る ) // (v5r) to be or remain always on hand
 KanjiVerb_5r( 詰寄る ) // (v5r,vi) to draw near/to draw closer
 KanjiVerb_5r( 詰切る ) // (v5r) to be or remain always on hand
 KanjiVerb_5r( 逆上せ上がる ) // (v5r,vi) to be beside oneself/to lose one's head/to go mad with something
 KanjiVerb_5r( 休まる ) // (v5r,vi) to be rested/to feel at ease/to repose/to be relieved/(P)
 KanjiVerb_5r( 泣きじゃくる ) // (v5r) to sob
 KanjiVerb_5r( 泣き縋がる ) // (v5r) to cling tearfully to another person
 KanjiVerb_5r( 泣縋がる ) // (v5r) to cling tearfully to another person
 KanjiVerb_5r( 窮まる ) // (v5r,vi) to terminate/to reach an extreme/to be in a dilemma/to be at an end
 KanjiVerb_5r( 去る ) // (v5r,vi) (1) to leave/to go away/(2) to pass/to elapse/(3) to be distant/(P)
 KanjiVerb_5r( 居る ) // (v5r,vi) (uk) (hum) to be (animate)/to be/to exist/(P)
 KanjiVerb_5r( 居座る ) // (v5r,vi) to remain
 KanjiVerb_5r( 居残る ) // (v5r,vi) to stay behind/to remain/to work overtime
 KanjiVerb_5r( 居据わる ) // (v5r,vi) to remain
 KanjiVerb_5r( 居直る ) // (v5r,vi) (1) to sit up properly straight/(2) to become aggressive
 KanjiVerb_5r( 拠る ) // (v5r,vi) (1) (uk) to be due to/to be caused by/(2) to depend on/to turn on/(3) to be based on/to come from/(P)
 KanjiVerb_5r( 挙がる ) // (v5r,vi) to become prosperous/to be captured/(P)
 KanjiVerb_5r( 挙る ) // (v5r) (1) to assemble everything together/(2) to do something as a group
 KanjiVerb_5r( 虚しくなる ) // (v5r) to die/to expire
 KanjiVerb_5r( 距たる ) // (v5r,vi) to be distant
 KanjiVerb_5r( 強がる ) // (v5r,vi) to cry sour grapes/to bluff/to whistle in the dark
 KanjiVerb_5r( 強ばる ) // (v5r,vi) to stiffen
 KanjiVerb_5r( 強まる ) // (v5r,vi) to get strong/to gain strength/(P)
 KanjiVerb_5r( 強張る ) // (v5r,vi) to stiffen/(P)
 KanjiVerb_5r( 恐がる ) // (v5r,vi) to be afraid of/to fear/to dread/to be nervous (about)/to be shy (of)
 KanjiVerb_5r( 恐れ入る ) // (v5r,vi) to be filled with awe/to feel small/to be amazed/to be surprised/to be disconcerted/to be sorry/to be grateful/to be defeated/to confess guilt
 KanjiVerb_5r( 挟まる ) // (v5r,vi) to get between/to be caught in/(P)
 KanjiVerb_5r( 狂い回る ) // (v5r) to rave/to run amuck
 KanjiVerb_5r( 狭まる ) // (v5r,vi) to narrow/to contract/(P)
 KanjiVerb_5r( 興がる ) // (v5r,vi) to be amused or interested in
 KanjiVerb_5r( 興る ) // (v5r,vi) to rise/to flourish
 KanjiVerb_5r( 響き渡る ) // (v5r,vi) to resound
 KanjiVerb_5r( 驚き入る ) // (v5r,vi) to be astonished/to be amazed
 KanjiVerb_5r( 仰ぎ奉る ) // (v5r) (pol) to look up
 KanjiVerb_5r( 仰けぞる ) // (v5r) to bend (backward)
 KanjiVerb_5r( 仰反る ) // (v5r,vi) to bend back/to throw (the head) back
 KanjiVerb_5r( 仰奉る ) // (v5r) (pol) to look up
 KanjiVerb_5r( 凝り固まる ) // (v5r,vi) to coagulate/to curdle/to clot/to be fanatical
 KanjiVerb_5r( 凝る ) // (v5r,vi) to stiffen/to harden
 KanjiVerb_5r( 曲がりくねる ) // (v5r,vi) to bend many times/to turn and twist/to zigzag
 KanjiVerb_5r( 曲がる ) // (v5r,vi) to turn/to bend/(P)
 KanjiVerb_5r( 曲りくねる ) // (v5r,vi) to bend many times/to turn and twist/to zigzag
 KanjiVerb_5r( 極まる ) // (v5r,vi) to terminate/to reach an extreme/to be in a dilemma/to be at an end/(P)
 KanjiVerb_5r( 極る ) // (v5r,vi) (1) to be decided/to be settled/(2) to look good in (clothes)
 KanjiVerb_5r( 勤まる ) // (v5r,vi) to be fit for/to be equal to/to function properly
 KanjiVerb_5r( 筋張る ) // (v5r,vi) to become sinewy/to behave formally
 KanjiVerb_5r( 緊まる ) // (v5r,vi) (1) to be shut/to close/to be closed/(2) to be locked/(3) to tighten/to be tightened/(4) to become sober/to become tense
 KanjiVerb_5r( 近寄る ) // (v5r,vi) to approach/to draw near/(P)
 KanjiVerb_5r( 九州へ下る ) // (v5r) to go down to Kyushu
 KanjiVerb_5r( 苦しがる ) // (v5r) to suffer/to complain of a pain
 KanjiVerb_5r( 苦り切る ) // (v5r,vi) to look sour (disgusted)
 KanjiVerb_5r( 苦る ) // (v5r,vi) to feel bitter/to scowl
 KanjiVerb_5r( 苦手である ) // (v5r) to be weak in/to be poor at/to be bad at
 KanjiVerb_5r( 駆けずり回る ) // (v5r,vi) to run around/to bustle about/to busy oneself
 KanjiVerb_5r( 駆け下る ) // (v5r) to run down
 KanjiVerb_5r( 駆け回る ) // (v5r,vi) to run around/to bustle about/(P)
 KanjiVerb_5r( 駆け寄る ) // (v5r,vi) to rush over/to run up to
 KanjiVerb_5r( 駆け巡る ) // (v5r,vi) to run about
 KanjiVerb_5r( 駆け上がる ) // (v5r,vi) to run up
 KanjiVerb_5r( 駆け上る ) // (v5r,vi) to run up
 KanjiVerb_5r( 駆け登る ) // (v5r) to run (uphill)
 KanjiVerb_5r( 駆下る ) // (v5r) to run down
 KanjiVerb_5r( 駆回る ) // (v5r,vi) to run around/to bustle about
 KanjiVerb_5r( 駆寄る ) // (v5r,vi) to rush over/to run up to
 KanjiVerb_5r( 駆巡る ) // (v5r,vi) to run about
 KanjiVerb_5r( 駆上る ) // (v5r,vi) to run up
 KanjiVerb_5r( 駆登る ) // (v5r) to run (uphill)
 KanjiVerb_5r( 具わる ) // (v5r,vi) (1) to be furnished with/to be endowed with/(2) to be among/to be one of/to be possessed of/(P)
 KanjiVerb_5r( 愚図る ) // (v5r) to grumble/to be unsettled/to pick a quarrel
 KanjiVerb_5r( 愚痴る ) // (v5r,vi) to complain/to grumble
 KanjiVerb_5r( 空しくなる ) // (v5r) to die/to expire
 KanjiVerb_5r( 掘る ) // (v5r) to dig/to excavate/(P)
 KanjiVerb_5r( 繰り下がる ) // (v5r) to move back/to postpone/to borrow (in math)
 KanjiVerb_5r( 繰り取る ) // (v5r) to reel off
 KanjiVerb_5r( 繰り上がる ) // (v5r,vi) to move up (date or rank)
 KanjiVerb_5r( 繰下がる ) // (v5r) to move back/to postpone/to borrow (in math)
 KanjiVerb_5r( 繰取る ) // (v5r) to reel off
 KanjiVerb_5r( 繰上がる ) // (v5r,vi) to move up (date or rank)
 KanjiVerb_5r( 薫る ) // (v5r,vi) to smell sweet/to be fragrant
 KanjiVerb_5r( 群がる ) // (v5r,vi) to swarm/to gather/(P)
 KanjiVerb_5r( 群れ集まる ) // (v5r) to gather in large groups
 KanjiVerb_5r( 係る ) // (v5r,vi) to concern oneself in/to have to do with/to affect/to influence/to stick to (opinions)
 KanjiVerb_5r( 係わる ) // (v5r,vi) to concern oneself in/to have to do with/to affect/to influence/to stick to (opinions)/(P)
 KanjiVerb_5r( 形づくる ) // (v5r,vi) to form/to shape/to make/to mold/to mould/to build up/(P)
 KanjiVerb_5r( 形どる ) // (v5r,vi) (1) to model on/to make in the shape of/to represent/to pattern after/to imitate/(2) to symbolise
 KanjiVerb_5r( 形作る ) // (v5r,vi) to form/to shape/to make/to mold/to mould/to build up
 KanjiVerb_5r( 形式張る ) // (v5r,vi) to stand on ceremony
 KanjiVerb_5r( 形取る ) // (v5r,vi) (1) to model on/to make in the shape of/to represent/to pattern after/to imitate/(2) to symbolise
 KanjiVerb_5r( 形造る ) // (v5r,vi) to form/to shape/to make/to mold/to mould/to build up
 KanjiVerb_5r( 携わる ) // (v5r,vi) to participate/to take part/(P)
 KanjiVerb_5r( 経巡る ) // (v5r) to travel about
 KanjiVerb_5r( 経上がる ) // (v5r,vi) to rise
 KanjiVerb_5r( 繋がる ) // (v5r,vi) to be tied together/to be connected to/to be related to/(P)
 KanjiVerb_5r( 撃ち破る ) // (v5r) defeat/crush
 KanjiVerb_5r( 決まる ) // (v5r,vi) (1) to be decided/to be settled/(2) to look good in (clothes)/(P)
 KanjiVerb_5r( 血走る ) // (v5r,vi) bloodshot
 KanjiVerb_5r( 血塗る ) // (v5r,vi) to smear with blood/to kill
 KanjiVerb_5r( 懸かる ) // (v5r,vi) to be suspended from/to be trapped/(P)
 KanjiVerb_5r( 懸け隔たる ) // (v5r,vi) far apart/remote/quite different
 KanjiVerb_5r( 犬猿の仲である ) // (v5r) to be at enmity/to lead a cat and dog life
 KanjiVerb_5r( 肩肘張る ) // (v5r) to swagger/to stiffen
 KanjiVerb_5r( 見あたる ) // (v5r) to be found
 KanjiVerb_5r( 見つかる ) // (v5r,vi) (uk) to be found/to be discovered/(P)
 KanjiVerb_5r( 見やる ) // (v5r) to gaze/to stare at
 KanjiVerb_5r( 見回る ) // (v5r,vi) to make one's rounds/to patrol
 KanjiVerb_5r( 見識張る ) // (v5r,vi) to assume an air of importance/to stand on one's dignity
 KanjiVerb_5r( 見捨てて去る ) // (v5r) to leave behind
 KanjiVerb_5r( 見積もる ) // (v5r) to estimate
 KanjiVerb_5r( 見当たる ) // (v5r) to be found/(P)
 KanjiVerb_5r( 見入る ) // (v5r) to gaze at/to fix one's eyes upon/(P)
 KanjiVerb_5r( 見付かる ) // (v5r,vi) (uk) to be found/to be discovered/(P)
 KanjiVerb_5r( 見返る ) // (v5r,vi) to look back
 KanjiVerb_5r( 謙る ) // (v5r,vi) to deprecate oneself and praise the listener/to abase oneself
 KanjiVerb_5r( 減じる ) // (v5r,vi) to subtract/to deduct/to reduce/to decrease
 KanjiVerb_5r( 減る ) // (v5r,vi) to decrease (in size or number)/to diminish/to abate/(P)
 KanjiVerb_5r( 言い寄る ) // (v5r,vi) to court/to woo/to approach defiantly
 KanjiVerb_5r( 言い終わる ) // (v5r) to finish speaking
 KanjiVerb_5r( 言い募る ) // (v5r,vi) to argue vehemently
 KanjiVerb_5r( 言寄る ) // (v5r,vi) to court/to woo/to approach defiantly
 KanjiVerb_5r( 言終わる ) // (v5r) to finish speaking
 KanjiVerb_5r( 言募る ) // (v5r,vi) to argue vehemently
 KanjiVerb_5r( 言葉から実行に移る ) // (v5r) to change words into actions
 KanjiVerb_5r( 限る ) // (v5r,vi) to restrict/to limit/to confine/(P)
 KanjiVerb_5r( 呼びにやる ) // (v5r) to send for (doctor, etc.)
 KanjiVerb_5r( 呼びに遣る ) // (v5r) to send for (doctor, etc.)
 KanjiVerb_5r( 固くなる ) // (v5r) to become stiff/to tense
 KanjiVerb_5r( 固く固まる ) // (v5r) to form a hard mass
 KanjiVerb_5r( 固まる ) // (v5r,vi) to harden/to solidify/to become firm/to become certain/(P)
 KanjiVerb_5r( 誇る ) // (v5r,vi) to boast of/to be proud of/(P)
 KanjiVerb_5r( 跨がる ) // (v5r,vi) (1) to extend over or into/(2) to straddle/(P)
 KanjiVerb_5r( 跨る ) // (v5r,vi) (1) to extend over or into/(2) to straddle
 KanjiVerb_5r( 呉れて遣る ) // (v5r) (uk) to give/to do (something) for
 KanjiVerb_5r( 後ずさる ) // (v5r) to draw back/to step back/to shrink away
 KanjiVerb_5r( 後退る ) // (v5r) to retreat/to back off
 KanjiVerb_5r( 御出でになる ) // (v5r) (hon) (uk) to be
 KanjiVerb_5r( 御免被る ) // (v5r) to be excused from
 KanjiVerb_5r( 誤る ) // (v5r,vi) to make a mistake/(P)
 KanjiVerb_5r( 乞い取る ) // (v5r) to ask for and receive
 KanjiVerb_5r( 交ざる ) // (v5r,vi) to be mixed/to be blended with/to associate with/to mingle with/to join/(P)
 KanjiVerb_5r( 交じる ) // (v5r,vi) to be mixed/to be blended with/to associate with/to mingle with/to interest/to join/(P)
 KanjiVerb_5r( 交わる ) // (v5r,vi) to cross/to intersect/to associate with/to mingle with/to interest/to join/(P)
 KanjiVerb_5r( 光る ) // (v5r,vi) to shine/to glitter/to be bright/(P)
 KanjiVerb_5r( 口ごもる ) // (v5r,vi) to hesitate to say/to mumble/to hem and haw/to falter/(P)
 KanjiVerb_5r( 口篭る ) // (v5r,vi) to hesitate to say/to mumble/to hem and haw/to falter
 KanjiVerb_5r( 口籠る ) // (v5r,vi) to hesitate to say/to mumble/to hem and haw/to falter
 KanjiVerb_5r( 向き直る ) // (v5r,vi) to turn round/to face about/to turn about
 KanjiVerb_5r( 向け直る ) // (v5r,vi) to change direction
 KanjiVerb_5r( 垢染みる ) // (v5r,vi) to become grimy or dirty
 KanjiVerb_5r( 幸甚である ) // (v5r) to deem a favor/to deem a favour/to be very glad
 KanjiVerb_5r( 広がる ) // (v5r,vi) to spread (out)/to extend/to stretch/to reach to/to get around/(P)
 KanjiVerb_5r( 広まる ) // (v5r,vi) to spread/to be propagated/(P)
 KanjiVerb_5r( 拘る ) // (v5r,vi) to concern oneself in/to have to do with/to affect/to influence/to stick to (opinions)
 KanjiVerb_5r( 拘わる ) // (v5r,vi) to concern oneself in/to have to do with/to affect/to influence/to stick to (opinions)
 KanjiVerb_5r( 攻め上る ) // (v5r,vi) to march on the capital
 KanjiVerb_5r( 攻め入る ) // (v5r,vi) to invade
 KanjiVerb_5r( 江川る ) // (v5r) to (try to) act like a big-shot
 KanjiVerb_5r( 甲走る ) // (v5r,vi) to make a shrill sound
 KanjiVerb_5r( 絞まる ) // (v5r,vi) to be strangled/to be constricted
 KanjiVerb_5r( 考え過ぎる ) // (v5r) to think too much/to be over-concerned
 KanjiVerb_5r( 荒らし回る ) // (v5r) to break into (houses here and there)/to rampage
 KanjiVerb_5r( 行き詰まる ) // (v5r) to reach the limits/to come to the end of one's tether
 KanjiVerb_5r( 行き渡る ) // (v5r,vi) to diffuse/to spread through
 KanjiVerb_5r( 行き当たる ) // (v5r) to hit/to run into/to light on/to strike into/to come against/to deadlock
 KanjiVerb_5r( 行渡る ) // (v5r,vi) to diffuse/to spread through
 KanjiVerb_5r( 降りかかる ) // (v5r) (1) to fall onto/(2) to happen/to befall
 KanjiVerb_5r( 降りしきる ) // (v5r) to rain incessantly/to downpour
 KanjiVerb_5r( 降り掛かる ) // (v5r) (1) to fall onto/(2) to happen/to befall
 KanjiVerb_5r( 降り懸かる ) // (v5r) (1) to fall onto/(2) to happen/to befall
 KanjiVerb_5r( 降り積もる ) // (v5r) to lie thick
 KanjiVerb_5r( 降り募る ) // (v5r,vi) to rain harder
 KanjiVerb_5r( 降る ) // (v5r,vi) to precipitate/to fall (e.g., rain)/(P)
 KanjiVerb_5r( 香る ) // (v5r,vi) to smell sweet/to be fragrant/(P)
 KanjiVerb_5r( 高じる ) // (v5r,vi) to grow in intensity/to be aggravated/to get worse/to develop
 KanjiVerb_5r( 高ぶる ) // (v5r,vi) to be highly strung/to get excited/to be proud/to be haughty
 KanjiVerb_5r( 高まる ) // (v5r,vi) to rise/to swell/to be promoted/(P)
 KanjiVerb_5r( 高鳴る ) // (v5r,vi) to throb/to beat fast
 KanjiVerb_5r( 合わさる ) // (v5r,vi) to get together/to unite
 KanjiVerb_5r( 黒く染まる ) // (v5r) to be dyed black
 KanjiVerb_5r( 黒まる ) // (v5r,vi) to blacken/to become black
 KanjiVerb_5r( 骨ばる ) // (v5r,vi) to be bony/to be angular
 KanjiVerb_5r( 骨折る ) // (v5r,vi) to exert oneself greatly/to take pains
 KanjiVerb_5r( 骨張る ) // (v5r,vi) to be bony/to be angular
 KanjiVerb_5r( 込み入る ) // (v5r,vi) to push in/to be crowded/to be complicated
 KanjiVerb_5r( 困り切る ) // (v5r,vi) to be greatly perplexed/to be greatly embarrassed
 KanjiVerb_5r( 困る ) // (v5r,vi) to be worried/to be bothered/(P)
 KanjiVerb_5r( 混ざる ) // (v5r,vi) to be mixed/to be blended with/to associate with/to mingle with/to join/(P)
 KanjiVerb_5r( 混じる ) // (v5r,vi) to be mixed/to be blended with/to associate with/to mingle with/to interest/to join/(P)
 KanjiVerb_5r( 唆る ) // (v5r) (uk) to excite/to incite/to stimulate/to arouse/to tempt/to stir up
 KanjiVerb_5r( 左に曲がる ) // (v5r) to turn to the left
 KanjiVerb_5r( 差し掛かる ) // (v5r) to come near to/to approach/(P)
 KanjiVerb_5r( 差し障る ) // (v5r,vi) to hinder/to adversely affect
 KanjiVerb_5r( 差し当たる ) // (v5r,vi) to face the situation
 KanjiVerb_5r( 差し当る ) // (v5r,vi) to face the situation
 KanjiVerb_5r( 差し迫る ) // (v5r,vi) to be urgent or pressing
 KanjiVerb_5r( 坐る ) // (v5r,vi) to sit/to squat
 KanjiVerb_5r( 座る ) // (v5r,vi) to sit/to squat/(P)
 KanjiVerb_5r( 再び取る ) // (v5r) to reassume
 KanjiVerb_5r( 塞がる ) // (v5r,vi) to be plugged up/to be shut up/(P)
 KanjiVerb_5r( 才走る ) // (v5r,vi) to be clever/to be quick-witted/to be precocious
 KanjiVerb_5r( 災いする ) // (v5r,vi) to be the ruin of (a person)
 KanjiVerb_5r( 砕け散る ) // (v5r) to be smashed up
 KanjiVerb_5r( 細る ) // (v5r,vi) to get thin/to taper off/(P)
 KanjiVerb_5r( 裁ち切る ) // (v5r) to cut (cloth)
 KanjiVerb_5r( 載る ) // (v5r) (1) to spread (paints)/to be taken in/(v5r) (2) to share in/to join/to be found in (a dictionary)/to feel like doing/to be mentioned in/to be in harmony with/(v5r) (3) to appear (in print)/to be recorded/(P)
 KanjiVerb_5r( 在る ) // (v5r-i,vi) (1) (uk) to live/to be/to exist/(2) to have/(3) to be located/(4) to be equipped with/(5) to happen/to come about/(P)
 KanjiVerb_5r( 冴え渡る ) // (v5r,vi) to get cold/to freeze over
 KanjiVerb_5r( 冴え返る ) // (v5r,vi) to be very clear/to be keenly cold
 KanjiVerb_5r( 咲き誇る ) // (v5r,vi) to be in fullness of bloom
 KanjiVerb_5r( 咲き残る ) // (v5r,vi) to bloom late/to remain in bloom
 KanjiVerb_5r( 咲き渡る ) // (v5r,vi) to bloom over a wide area
 KanjiVerb_5r( 削り取る ) // (v5r) to shave off/to scrape off
 KanjiVerb_5r( 窄まる ) // (v5r,vi) to get narrower/to contract
 KanjiVerb_5r( 刷り上がる ) // (v5r) to be off the press
 KanjiVerb_5r( 擦り寄る ) // (v5r,vi) to draw close to/to edge up to/to snuggle up to/to nestle close to/to cuddle with/to draw closer to
 KanjiVerb_5r( 擦り減る ) // (v5r,vi) to be worn down/to be reduced
 KanjiVerb_5r( 擦り切る ) // (v5r) to cut by rubbing/to wear out/to spend all (one's money)
 KanjiVerb_5r( 擦れて薄くなる ) // (v5r) to wear thin
 KanjiVerb_5r( 殺る ) // (v5r) to do someone in/to bump someone off
 KanjiVerb_5r( 雑ざる ) // (v5r,vi) to be mixed/to be blended with/to associate with/to mingle with/to join
 KanjiVerb_5r( 雑じる ) // (v5r,vi) to be mixed/to be blended with/to associate with/to mingle with/to interest/to join
 KanjiVerb_5r( 参る ) // (v5r) (1) (hum) to go/to come/to call/(2) to be defeated/to collapse/to die/(3) to be annoyed/to be nonplussed/(4) to be madly in love/(5) to visit (shrine, grave)/(P)
 KanjiVerb_5r( 散らかる ) // (v5r,vi) to be in disorder/to lie scattered around/(P)
 KanjiVerb_5r( 散らばる ) // (v5r,vi) to be scattered about/(P)
 KanjiVerb_5r( 散り残る ) // (v5r,vi) to be left blooming/to remain on the stem
 KanjiVerb_5r( 散る ) // (v5r,vi) to fall/to scatter (e.g., blossoms)/(P)
 KanjiVerb_5r( 斬り掛かる ) // (v5r) to assault with a sword/to stab at
 KanjiVerb_5r( 残る ) // (v5r,vi) to remain/to be left/(P)
 KanjiVerb_5r( 残念である ) // (v5r) to be sorry/to regret
 KanjiVerb_5r( 仕え奉る ) // (v5r) (pol) to serve/to build as commanded
 KanjiVerb_5r( 仕る ) // (v5r,vi) (pol) to serve/to do
 KanjiVerb_5r( 仕上がる ) // (v5r,vi) to be finished
 KanjiVerb_5r( 刺さる ) // (v5r,vi) to stick/to be stuck/(P)
 KanjiVerb_5r( 四角張る ) // (v5r,vi) to be angular/to be formal
 KanjiVerb_5r( 始まる ) // (v5r,vi) to begin/(P)
 KanjiVerb_5r( 思い寄る ) // (v5r,vi) to recall
 KanjiVerb_5r( 思い遣る ) // (v5r) to be considerate/to sympathize with/to sympathise with
 KanjiVerb_5r( 思い至る ) // (v5r,vi) to realize/to realise
 KanjiVerb_5r( 思い上がる ) // (v5r,vi) to be conceited/(P)
 KanjiVerb_5r( 思い切る ) // (v5r,vi) to resign to fate/to despair/(P)
 KanjiVerb_5r( 思い当たる ) // (v5r,vi) to come to mind/to recall/to think of/(P)
 KanjiVerb_5r( 思い当る ) // (v5r,vi) to come to mind/to recall/to think of
 KanjiVerb_5r( 思い入る ) // (v5r) to ponder/to contemplate
 KanjiVerb_5r( 思い余る ) // (v5r,vi) to not know how to act or what to do/to be at a loss
 KanjiVerb_5r( 旨がる ) // (v5r) to relish/to show a liking for
 KanjiVerb_5r( 止まる ) // (v5r,vi) (1) to remain/to abide/to stay (in the one place)/(v5r) (2) to come to a halt/(v5r) (3) to stop/(P)
 KanjiVerb_5r( 死に掛かる ) // (v5r) to be dying
 KanjiVerb_5r( 脂下がる ) // (v5r,vi) to be complacent/to look self-satisfied
 KanjiVerb_5r( 至る ) // (v5r,vi) to come/to arrive/(P)
 KanjiVerb_5r( 事故る ) // (v5r) to have a road accident/to cause a traffic accident
 KanjiVerb_5r( 事足る ) // (v5r,vi) to suffice/to serve the purpose/to be satisfied
 KanjiVerb_5r( 似寄る ) // (v5r,vi) to resemble
 KanjiVerb_5r( 侍る ) // (v5r,vi) to wait upon/to serve
 KanjiVerb_5r( 持ち寄る ) // (v5r,vi) to gather (bringing something)/to gather (to exchange something)
 KanjiVerb_5r( 持ち帰る ) // (v5r) to carry back or home/to take out (e.g., food)/(P)
 KanjiVerb_5r( 持ち去る ) // (v5r) to take away/to carry away
 KanjiVerb_5r( 持ち上がる ) // (v5r,vi) to lift/to happen/to occur/to come up/to turn up
 KanjiVerb_5r( 持ち切る ) // (v5r,vi) to hold all the while/to talk about nothing but
 KanjiVerb_5r( 持って回る ) // (v5r) to carry around
 KanjiVerb_5r( 持上がる ) // (v5r,vi) to lift/to happen/to occur/to come up/to turn up
 KanjiVerb_5r( 治まる ) // (v5r,vi) to be at peace/to clamp down/to lessen (storm, terror, anger)/(P)
 KanjiVerb_5r( 治る ) // (v5r,vi) (1) to be cured/to get well/to be healed/(2) to get mended/to be repaired/to be fixed/(P)
 KanjiVerb_5r( 失せ去る ) // (v5r) to disappear/to be gone
 KanjiVerb_5r( 湿る ) // (v5r,vi) to be wet/to become wet/to be damp/(P)
 KanjiVerb_5r( 湿気る ) // (v5r,vi) to be damp/to be moist
 KanjiVerb_5r( 実る ) // (v5r,vi) to bear fruit/to ripen/(P)
 KanjiVerb_5r( 写る ) // (v5r,vi) to be photographed/to be projected/(P)
 KanjiVerb_5r( 煮え繰り返る ) // (v5r,vi) to boil/to seethe
 KanjiVerb_5r( 煮え返る ) // (v5r,vi) to seethe/to ferment/to boil over
 KanjiVerb_5r( 煮え滾る ) // (v5r,vi) to boil
 KanjiVerb_5r( 煮詰まる ) // (v5r) to be boiled down
 KanjiVerb_5r( 煮上がる ) // (v5r,vi) to boil up/to be thoroughly cooked
 KanjiVerb_5r( 謝る ) // (v5r,vi) to apologize/to apologise/(P)
 KanjiVerb_5r( 若返る ) // (v5r,vi) to be rejuvenated/to feel young again
 KanjiVerb_5r( 寂しがる ) // (v5r) to miss someone (or something)/to feel lonely
 KanjiVerb_5r( 弱まる ) // (v5r,vi) to abate/to weaken/to be emaciated/to be dejected/to be perplexed/(P)
 KanjiVerb_5r( 弱り切る ) // (v5r,vi) to faint/to be exhausted
 KanjiVerb_5r( 弱る ) // (v5r,vi) to weaken/to be troubled/to be downcast/to be emaciated/to be dejected/to be perplexed/to impair/(P)
 KanjiVerb_5r( 取って参る ) // (v5r) to fetch (something)
 KanjiVerb_5r( 取って代わる ) // (v5r) to supplant/to supersede
 KanjiVerb_5r( 取っ捕まる ) // (v5r,vi) to be caught
 KanjiVerb_5r( 取りかかる ) // (v5r,vi) to begin/to set about/to start
 KanjiVerb_5r( 取り掛かる ) // (v5r,vi) to begin/to set about/to start/(P)
 KanjiVerb_5r( 取り掛る ) // (v5r,vi) to begin/to set about/to start
 KanjiVerb_5r( 取り入る ) // (v5r) to make up to
 KanjiVerb_5r( 取り縋る ) // (v5r,vi) to cling to
 KanjiVerb_5r( 取掛る ) // (v5r,vi) to begin/to set about/to start
 KanjiVerb_5r( 取入る ) // (v5r) to make up to
 KanjiVerb_5r( 取縋る ) // (v5r,vi) to cling to
 KanjiVerb_5r( 手こずる ) // (v5r) (uk) to have much trouble/to have a hard time/to not know how to handle
 KanjiVerb_5r( 手間取る ) // (v5r,vi) to take time/to be delayed
 KanjiVerb_5r( 手古摺る ) // (v5r) (uk) to have much trouble/to have a hard time/to not know how to handle/(P)
 KanjiVerb_5r( 手子摺る ) // (v5r) (uk) to have much trouble/to have a hard time/to not know how to handle
 KanjiVerb_5r( 腫れ上がる ) // (v5r,vi) to swell up
 KanjiVerb_5r( 受かる ) // (v5r,vi) to pass (examination)/(P)
 KanjiVerb_5r( 収まる ) // (v5r,vi) (1) to be in one's place/to be installed/to settle into/(2) to be obtained/to be settled/to be paid/to be delivered/(P)
 KanjiVerb_5r( 修まる ) // (v5r,vi) to govern oneself/to conduct oneself well
 KanjiVerb_5r( 終わる ) // (v5r,vi) to finish/to close/(P)
 KanjiVerb_5r( 襲い掛かる ) // (v5r,vi) to rush on/to attack/to swoop down on
 KanjiVerb_5r( 集まる ) // (v5r,vi) to gather/to collect/to assemble/(P)
 KanjiVerb_5r( 集る ) // (v5r,vi) (1) to gather/to crowd round/to swarm/to flock/(2) to extort from/to sponge off/(P)
 KanjiVerb_5r( 渋る ) // (v5r) to hesitate/to be reluctant/to have loose painful bowel movement/(P)
 KanjiVerb_5r( 重なる ) // (v5r,vi) to be piled up/lie on top of one another/overlap each other/(P)
 KanjiVerb_5r( 重る ) // (v5r,vi) to get heavy/to grow serious/(P)
 KanjiVerb_5r( 重宝がる ) // (v5r) to find useful/to think highly of
 KanjiVerb_5r( 宿る ) // (v5r,vi) (1) to lodge/to dwell/(2) to be pregnant/(P)
 KanjiVerb_5r( 縮こまる ) // (v5r,vi) to curl oneself up/to squeeze oneself in/to be huddled
 KanjiVerb_5r( 縮まる ) // (v5r,vi) to be shortened/to be contracted/to shrink/(P)
 KanjiVerb_5r( 縮み上がる ) // (v5r,vi) to cringe/to wince/to flinch
 KanjiVerb_5r( 出しゃばる ) // (v5r,vi) to intrude/to butt in
 KanjiVerb_5r( 出っ張る ) // (v5r,vi) to project/to stand out/to jut out/to protrude
 KanjiVerb_5r( 出回る ) // (v5r,vi) to appear on the market/to be moving
 KanjiVerb_5r( 出盛る ) // (v5r,vi) to appear in profusion
 KanjiVerb_5r( 出替わる ) // (v5r,vi) to take someone's place
 KanjiVerb_5r( 出張る ) // (v5r,vi) to project/to stand out/to jut out/to protrude
 KanjiVerb_5r( 出直る ) // (v5r) to set out again
 KanjiVerb_5r( 出来上がる ) // (v5r,vi) (1) to be finished/to be ready/by definition/(2) to be very drunk/(P)
 KanjiVerb_5r( 巡る ) // (v5r,vi) (1) to go around/(2) to return/(3) to surround/(4) to dispute/(P)
 KanjiVerb_5r( 暑がる ) // (v5r,vi) to complain of the heat/to feel the heat
 KanjiVerb_5r( 書き終る ) // (v5r) to finish writing
 KanjiVerb_5r( 助かる ) // (v5r,vi) to be saved/to be rescued/to survive/to be helpful/(P)
 KanjiVerb_5r( 助け守る ) // (v5r) to protect/to preserve/to keep
 KanjiVerb_5r( 勝ち誇る ) // (v5r,vi) to triumph/to be elated with success
 KanjiVerb_5r( 勝ち残る ) // (v5r,vi) to win and advance to the next round
 KanjiVerb_5r( 勝る ) // (v5r,vi) to excel/to surpass/to outrival/(P)
 KanjiVerb_5r( 勝勢である ) // (v5r) to stand a good chance of winning the game
 KanjiVerb_5r( 昇る ) // (v5r,vi) (1) to rise/to ascend/to go up/to climb/(2) to go to (the capital)/(3) to be promoted/(4) to add up to/(5) to advance (in price)/(6) to sail up/(7) to come up (on the agenda)/(P)
 KanjiVerb_5r( 消え去る ) // (v5r) to disappear/to vanish
 KanjiVerb_5r( 消え残る ) // (v5r,vi) to remain unextinguished/to survive
 KanjiVerb_5r( 消え入る ) // (v5r,vi) to vanish
 KanjiVerb_5r( 渉る ) // (v5r,vi) to cross over/to go across
 KanjiVerb_5r( 焼きが回る ) // (v5r) to become decrepit/to be in one's dotage/to become dull/to lose one's astuteness
 KanjiVerb_5r( 焼け残る ) // (v5r,vi) to escape being burned
 KanjiVerb_5r( 焦る ) // (v5r,vi) to be in a hurry/to be impatient/(P)
 KanjiVerb_5r( 照り上がる ) // (v5r,vi) to become bright with sunlight following a shower
 KanjiVerb_5r( 照る ) // (v5r,vi) to shine/(P)
 KanjiVerb_5r( 笑って居る ) // (v5r) to be smiling (laughing)
 KanjiVerb_5r( 象る ) // (v5r,vi) (1) to model on/to make in the shape of/to represent/to pattern after/to imitate/(2) to symbolise
 KanjiVerb_5r( 障る ) // (v5r,vi) to hinder/to interfere with/to affect/to do one harm/to be harmful to/(P)
 KanjiVerb_5r( 上がる ) // (v5r,vi) (1) to enter/to go up/to rise/to climb up/to advance/to appreciate/to be promoted/to improve/to call on/to be offered/to accrue/(2) to be finished/to go bankrupt/to be caught/to let up (rain)/(3) to weaken (as a battery)/(4) to get ruffled/(P)
 KanjiVerb_5r( 上る ) // (v5r,vi) (1) to rise/to ascend/to go up/to climb/(2) to go to (the capital)/(3) to be promoted/(4) to add up to/(5) to advance (in price)/(6) to sail up/(7) to come up (on the agenda)/(P)
 KanjiVerb_5r( 上回る ) // (v5r,vi) to exceed/(P)
 KanjiVerb_5r( 上擦る ) // (v5r,vi) to be or get excited/to sound shallow/to sound hollow (a voice)/to ring false (a voice)/to sound shrill and nervous (a voice)/to be high-pitched and unstrung (a voice)
 KanjiVerb_5r( 上品振る ) // (v5r) to be prudish
 KanjiVerb_5r( 乗っかる ) // (v5r,vi) to get on
 KanjiVerb_5r( 乗っ切る ) // (v5r,vi) (arch) to overcome/to get through
 KanjiVerb_5r( 乗り移る ) // (v5r,vi) to change (cars or horses)/to transfer/to possess/to inspire
 KanjiVerb_5r( 乗り回る ) // (v5r,vi) to ride around
 KanjiVerb_5r( 乗り掛かる ) // (v5r) to be about to board/to be riding on/to get on top of/to lean over/to set about/to collide with
 KanjiVerb_5r( 乗り切る ) // (v5r,vi) to weather/to get over/to tide over/to overcome/to get through/to ride across/to sail across
 KanjiVerb_5r( 乗り通る ) // (v5r) to ride through/to ride along
 KanjiVerb_5r( 乗り入る ) // (v5r) to ride into (a place)/to drive into (a place)
 KanjiVerb_5r( 畳まる ) // (v5r,vi) to be folded (up)
 KanjiVerb_5r( 植わる ) // (v5r,vi) to be planted
 KanjiVerb_5r( 触る ) // (v5r,vi) to touch/to feel/(P)
 KanjiVerb_5r( 触れ回る ) // (v5r,vi) to cry about/to broadcast
 KanjiVerb_5r( 食い下がる ) // (v5r,vi) to hang on to/to doff/(P)
 KanjiVerb_5r( 食い入る ) // (v5r,vi) to eat into
 KanjiVerb_5r( 食い齧る ) // (v5r) to nibble at/to have a smattering of knowledge
 KanjiVerb_5r( 食って掛かる ) // (v5r) to flare up at
 KanjiVerb_5r( 食下がる ) // (v5r,vi) to hang on to/to doff
 KanjiVerb_5r( 伸し掛かる ) // (v5r,vi) (1) to lean on/to weigh on/(2) to bend over/to lean forward
 KanjiVerb_5r( 伸し掛る ) // (v5r,vi) (1) to lean on/to weigh on/(2) to bend over/to lean forward
 KanjiVerb_5r( 伸し上がる ) // (v5r,vi) to stand on tiptoe/to rise in the world/to become arrogant
 KanjiVerb_5r( 伸び広がる ) // (v5r) to stretch out
 KanjiVerb_5r( 伸び上がる ) // (v5r,vi) to stretch/to reach to/to stand on tiptoe
 KanjiVerb_5r( 寝そべる ) // (v5r,vi) to sprawl/to lie sprawled
 KanjiVerb_5r( 寝静まる ) // (v5r,vi) to fall asleep
 KanjiVerb_5r( 寝転がる ) // (v5r,vi) to lie down/to throw oneself down
 KanjiVerb_5r( 寝入る ) // (v5r,vi) to fall asleep
 KanjiVerb_5r( 寝返る ) // (v5r,vi) to change sides/to double-cross/to betray/(P)
 KanjiVerb_5r( 心温まる ) // (v5r,vi) to be heart-warming
 KanjiVerb_5r( 心暖まる ) // (v5r,vi) to be heart-warming
 KanjiVerb_5r( 振りかぶる ) // (v5r,vi) to hold aloft (e.g., a sword)/to brandish
 KanjiVerb_5r( 振り懸かる ) // (v5r) (1) to fall onto/(2) to happen/to befall
 KanjiVerb_5r( 振り振る ) // (v5r,vi) to hold aloft (e.g., a sword)/to brandish
 KanjiVerb_5r( 振り返る ) // (v5r,vi) to turn head/to look over one's shoulder/to turn around/to look back/(P)
 KanjiVerb_5r( 新しがる ) // (v5r,vi) to be fond of new things/to hunt after novelties
 KanjiVerb_5r( 浸かる ) // (v5r,vi) (1) to be pickled/to be well seasoned/(2) to be submerged/to be soaked
 KanjiVerb_5r( 浸る ) // (v5r,vi) to be soaked in/to be flooded/(P)
 KanjiVerb_5r( 深まる ) // (v5r,vi) to deepen/to heighten/to intensify/(P)
 KanjiVerb_5r( 申し遣わす ) // (v5r) to write to/to send word to/to hand over (official business)
 KanjiVerb_5r( 真面目腐る ) // (v5r,vi) to pretend to be earnest
 KanjiVerb_5r( 身罷る ) // (v5r,vi) to pass away/to die
 KanjiVerb_5r( 身籠る ) // (v5r,vi) to become pregnant
 KanjiVerb_5r( 辛くあたる ) // (v5r) to treat badly
 KanjiVerb_5r( 辛く当たる ) // (v5r) to treat badly
 KanjiVerb_5r( 進退窮まる ) // (v5r) to be at a loss
 KanjiVerb_5r( 震え上がる ) // (v5r,vi) to tremble violently/to shudder up
 KanjiVerb_5r( 人の好む所となる ) // (v5r) to be liked by people
 KanjiVerb_5r( 人妻と寝る ) // (v5r) to sleep with another person's wife
 KanjiVerb_5r( 甚振る ) // (v5r) (uk) to torment/to harass/to tease
 KanjiVerb_5r( 陣取る ) // (v5r,vi) to encamp/to take up positions
 KanjiVerb_5r( 吹き捲くる ) // (v5r,vi) to blow about/to blow along/to brag
 KanjiVerb_5r( 吹き捲る ) // (v5r,vi) to blow about/to blow along/to brag
 KanjiVerb_5r( 吹き送る ) // (v5r) to waft/to blow over
 KanjiVerb_5r( 吹き頻る ) // (v5r) to blow violently/to blow incessantly
 KanjiVerb_5r( 吹き募る ) // (v5r,vi) to blow harder and harder
 KanjiVerb_5r( 垂れ下がる ) // (v5r,vi) to hang/to dangle
 KanjiVerb_5r( 粋がる ) // (v5r,vi) to be stylish/to try to appear smart
 KanjiVerb_5r( 嵩じる ) // (v5r,vi) to grow in intensity/to be aggravated/to get worse/to develop
 KanjiVerb_5r( 嵩張る ) // (v5r,vi) to be bulky/to be unwieldy/to grow voluminous
 KanjiVerb_5r( 据る ) // (v5r,vi) to sit/to squat
 KanjiVerb_5r( 据わる ) // (v5r,vi) to sit/to squat
 KanjiVerb_5r( 澄み切る ) // (v5r,vi) to be serene/(P)
 KanjiVerb_5r( 澄み渡る ) // (v5r,vi) to be perfectly clear
 KanjiVerb_5r( 畝ねる ) // (v5r) to undulate/to meander/to surge/to swell/to roll/to wind/(P)
 KanjiVerb_5r( 成り下がる ) // (v5r,vi) to be degraded/to come down in the world
 KanjiVerb_5r( 成り上がる ) // (v5r,vi) to rise (suddenly) in the world (to a higher position)
 KanjiVerb_5r( 成り切る ) // (v5r,vi) to turn completely into/to become completely
 KanjiVerb_5r( 成り代わる ) // (v5r) to do in place of or on behalf of (someone)
 KanjiVerb_5r( 成り変わる ) // (v5r) to change/to change into/to become
 KanjiVerb_5r( 成る ) // (v5r,vi) (uk) to become/(P)
 KanjiVerb_5r( 成上がる ) // (v5r,vi) to rise (suddenly) in the world (to a higher position)
 KanjiVerb_5r( 晴れ上がる ) // (v5r,vi) to clear up
 KanjiVerb_5r( 晴れ渡る ) // (v5r,vi) to clear up/to be refreshed
 KanjiVerb_5r( 清まる ) // (v5r,vi) to be purified/to be cleansed
 KanjiVerb_5r( 生い茂る ) // (v5r,vi) to grow thickly/to be overgrown
 KanjiVerb_5r( 生え変わる ) // (v5r) to be replaced with new growth
 KanjiVerb_5r( 生き残る ) // (v5r,vi) to survive/(P)
 KanjiVerb_5r( 生き返る ) // (v5r,vi) to revive/to come to oneself/to be restored to life/(P)
 KanjiVerb_5r( 生まれ変わる ) // (v5r) to be born again/to make a fresh start in life
 KanjiVerb_5r( 生る ) // (v5r,vi) to bear fruit/(P)
 KanjiVerb_5r( 生返る ) // (v5r,vi) to revive/to come to oneself/to be restored to life/(P)
 KanjiVerb_5r( 盛り上がる ) // (v5r,vi) to rouse/to swell/to rise/(P)
 KanjiVerb_5r( 盛る ) // (v5r,vi) (1) to serve (food, etc.)/(2) to fill up/(3) to prescribe/(P)
 KanjiVerb_5r( 静まり返る ) // (v5r,vi) to fall silent/to become still as death
 KanjiVerb_5r( 静まる ) // (v5r,vi) to quieten down/to calm down/to subside/to die down/to abate/to be suppressed/(P)
 KanjiVerb_5r( 積み重なる ) // (v5r,vi) to accumulate
 KanjiVerb_5r( 積もる ) // (v5r) to pile up/(P)
 KanjiVerb_5r( 切り掛かる ) // (v5r) to begin to cut/to slash at
 KanjiVerb_5r( 切り去る ) // (v5r) to cut off
 KanjiVerb_5r( 切り替わる ) // (v5r) to change completely
 KanjiVerb_5r( 切羽詰まる ) // (v5r) to be at one's wit's end/to be cornered
 KanjiVerb_5r( 摂る ) // (v5r) to take something into the body/to absorb nourishment
 KanjiVerb_5r( 折り重なる ) // (v5r,vi) to lie on top of one another/to be in a heap
 KanjiVerb_5r( 折れ曲がる ) // (v5r) to bend back and forth
 KanjiVerb_5r( 折れ返る ) // (v5r,vi) to tell again and again/to repeat/to refrain/to turn up/to turn down
 KanjiVerb_5r( 折返る ) // (v5r,vi) to tell again and again/to repeat/to refrain/to turn up/to turn down
 KanjiVerb_5r( 絶え入る ) // (v5r,vi) to expire
 KanjiVerb_5r( 先細る ) // (v5r) to taper off
 KanjiVerb_5r( 先走る ) // (v5r,vi) to be forward/to be impertinent
 KanjiVerb_5r( 千切る ) // (v5r) to cut up fine/to pick (fruit)/(P)
 KanjiVerb_5r( 尖る ) // (v5r,vi) to taper to a point/to become sharp/to be sour/to look displeased
 KanjiVerb_5r( 尖んがる ) // (v5r) to get cross/to be displeased with/to get sharp
 KanjiVerb_5r( 洗い去る ) // (v5r) to wash away
 KanjiVerb_5r( 染まる ) // (v5r,vi) to dye/(P)
 KanjiVerb_5r( 染み通る ) // (v5r,vi) (1) to soak through/(2) to be deeply impressed
 KanjiVerb_5r( 染み渡る ) // (v5r,vi) to penetrate/to pervade/to spread
 KanjiVerb_5r( 染み透る ) // (v5r,vi) (1) to soak through/(2) to be deeply impressed
 KanjiVerb_5r( 染通る ) // (v5r,vi) (1) to soak through/(2) to be deeply impressed
 KanjiVerb_5r( 染透る ) // (v5r,vi) (1) to soak through/(2) to be deeply impressed
 KanjiVerb_5r( 潜る ) // (v5r,vi) (1) to drive/to pass through/(2) to evade/to hide/(3) to dive (into or under water)/to go underground
 KanjiVerb_5r( 煽る ) // (v5r) to fan/to agitate/to stir up/(P)
 KanjiVerb_5r( 選びとる ) // (v5r) to pick out item(s) from a group to keep
 KanjiVerb_5r( 選び取る ) // (v5r) to pick out item(s) from a group to keep
 KanjiVerb_5r( 蘇る ) // (v5r,vi) to be resurrected/to be revived/to be resuscitated/to be rehabilitated
 KanjiVerb_5r( 遡る ) // (v5r,vi) to go back/to go upstream/to make retroactive/(P)
 KanjiVerb_5r( 壮とする ) // (v5r) to admire (approve of) a person's courage
 KanjiVerb_5r( 捜し回る ) // (v5r) to hunt around/to search about for/(P)
 KanjiVerb_5r( 掻い潜る ) // (v5r,vi) to slip through
 KanjiVerb_5r( 掻き曇る ) // (v5r,vi) to become overcast
 KanjiVerb_5r( 掻っ穿じる ) // (v5r) (uk) to dig up/to peck at
 KanjiVerb_5r( 早まる ) // (v5r,vi) to be hasty/to be rash/to speed up/to gather speed/(P)
 KanjiVerb_5r( 巣籠る ) // (v5r,vi) to nest
 KanjiVerb_5r( 争い怒る ) // (v5r) to be angry and quarrelsome
 KanjiVerb_5r( 痩せ細る ) // (v5r,vi) to lose weight
 KanjiVerb_5r( 走りまわる ) // (v5r,vi) to run around
 KanjiVerb_5r( 走り回る ) // (v5r,vi) to run around/(P)
 KanjiVerb_5r( 走り去る ) // (v5r) to run away
 KanjiVerb_5r( 走る ) // (v5r,vi) to run/(P)
 KanjiVerb_5r( 則る ) // (v5r,vi) to conform to/to be in accordance with
 KanjiVerb_5r( 息せき切る ) // (v5r) to pant/to gasp
 KanjiVerb_5r( 息詰まる ) // (v5r) to be breathtaking/to be stifling
 KanjiVerb_5r( 息急き切る ) // (v5r) to pant/to gasp
 KanjiVerb_5r( 息張る ) // (v5r,vi) to strain/to bear down (in giving birth)
 KanjiVerb_5r( 捉まる ) // (v5r,vi) to hold on to/to grasp
 KanjiVerb_5r( 足る ) // (v5r,vi) to be sufficient/to be enough/(P)
 KanjiVerb_5r( 速まる ) // (v5r,vi) to be hasty/to be rash/to speed up/to gather speed
 KanjiVerb_5r( 遜る ) // (v5r,vi) to deprecate oneself and praise the listener/to abase oneself
 KanjiVerb_5r( 太る ) // (v5r,vi) to grow fat (stout, plump)/to become fat/(P)
 KanjiVerb_5r( 打ち掛かる ) // (v5r) to strike
 KanjiVerb_5r( 打ち当たる ) // (v5r) (1) to slam into (e.g. a wall, a limit) (figuratively)/to hit/(2) to face (e.g. trouble, a problem)/to confront
 KanjiVerb_5r( 打っちゃる ) // (v5r) (1) to discard/to abandon/(2) to neglect/to let be
 KanjiVerb_5r( 打って掛かる ) // (v5r) to attack/to strike/to take a swing at
 KanjiVerb_5r( 打って変わる ) // (v5r) to change suddenly
 KanjiVerb_5r( 打っ千切る ) // (v5r) (1) to win (a race) by a wide margin/(2) to slash though something/to tear (off)
 KanjiVerb_5r( 打つかる ) // (v5r) (uk) to strike/to collide with
 KanjiVerb_5r( 駄弁る ) // (v5r,vi) to jabber/to chatter/to chat with
 KanjiVerb_5r( 体裁振る ) // (v5r,vi) to put on airs
 KanjiVerb_5r( 怠る ) // (v5r,vi) to neglect/to be off guard/to be feeling better/(P)
 KanjiVerb_5r( 替わる ) // (v5r,vi) to take the place of/to relieve/to be substituted for/to be exchanged/to change places with/to take turns/to be replaced/(P)
 KanjiVerb_5r( 滞る ) // (v5r,vi) to stagnate/to be delayed
 KanjiVerb_5r( 代わる ) // (v5r,vi) to take the place of/to relieve/to be substituted for/to be exchanged/to change places with/to take turns/to be replaced/(P)
 KanjiVerb_5r( 代代伝わる ) // (v5r) to be transmitted (handed down) from generation to generation
 KanjiVerb_5r( 大磐石である ) // (v5r) to be as firm as rock
 KanjiVerb_5r( 濁る ) // (v5r,vi) to become muddy/to get impure/(P)
 KanjiVerb_5r( 叩き切る ) // (v5r) to mangle/to hack down/to chop down
 KanjiVerb_5r( 奪い去る ) // (v5r) to take away/to carry off
 KanjiVerb_5r( 担ぎ回る ) // (v5r) to carry something around
 KanjiVerb_5r( 探し回る ) // (v5r) to hunt around/to search about for/(P)
 KanjiVerb_5r( 探り回る ) // (v5r) to grope for/to fumble
 KanjiVerb_5r( 炭酸で割る ) // (v5r) to dilute with soda
 KanjiVerb_5r( 耽ける ) // (v5r,vi) (1) to indulge in/to give oneself up to/to be obsessed by/(2) to be engrossed in/to be lost in/to be absorbed in
 KanjiVerb_5r( 耽る ) // (v5r,vi) (1) to indulge in/to give oneself up to/to be obsessed by/(2) to be engrossed in/to be lost in/to be absorbed in/(P)
 KanjiVerb_5r( 断ち割る ) // (v5r) to split
 KanjiVerb_5r( 暖まる ) // (v5r,vi) to warm oneself/to sun oneself/to warm up/to get warm/(P)
 KanjiVerb_5r( 知れ渡る ) // (v5r,vi) to be well-known
 KanjiVerb_5r( 弛まる ) // (v5r,vi) to become loose/to slacken/to soften
 KanjiVerb_5r( 恥じ入る ) // (v5r,vi) to feel ashamed/to be abashed
 KanjiVerb_5r( 恥ずかしがる ) // (v5r) to be shy of/to be bashful/to be abashed/to blush
 KanjiVerb_5r( 置き換わる ) // (v5r) to be rearranged or transposed
 KanjiVerb_5r( 茶目る ) // (v5r) to play pranks
 KanjiVerb_5r( 中たる ) // (v5r,vi) to be hit/to be successful/to face (confront)/to lie (in the direction of)/to undertake/to treat/to be equivalent to/to apply to/to be applicable/to be assigned
 KanjiVerb_5r( 貯まる ) // (v5r) to be saved (e.g., money)
 KanjiVerb_5r( 喋る ) // (v5r,vi) to talk/to chat/to chatter/(P)
 KanjiVerb_5r( 張り切る ) // (v5r) to be in high spirits/to be full of vigor (vigour)/to be enthusiastic/to be eager/to stretch to breaking point/(P)
 KanjiVerb_5r( 張る ) // (v5r,vi) to stick/to paste/to put/to affix/to stretch/to spread/to strain/to stick out/to slap/to be expensive/to tighten/(P)
 KanjiVerb_5r( 聴き入る ) // (v5r) to listen attentively to/to be lost in
 KanjiVerb_5r( 脹れ上がる ) // (v5r) to swell up
 KanjiVerb_5r( 跳ね回る ) // (v5r,vi) to jump about
 KanjiVerb_5r( 跳ね上がる ) // (v5r,vi) to jump up/to spring up/(P)
 KanjiVerb_5r( 跳ね返る ) // (v5r) to rebound
 KanjiVerb_5r( 跳び過ぎる ) // (v5r) to overjump/to overleap
 KanjiVerb_5r( 跳び回る ) // (v5r,vi) to fly about/to skip about/to bustle about
 KanjiVerb_5r( 跳び上がる ) // (v5r,vi) to spring/to jump up/to fly up/to skip
 KanjiVerb_5r( 跳び乗る ) // (v5r) to jump upon (a moving object)
 KanjiVerb_5r( 跳回る ) // (v5r,vi) to fly about/to skip about/to bustle about
 KanjiVerb_5r( 跳上がる ) // (v5r,vi) to spring/to jump up/to fly up/to skip
 KanjiVerb_5r( 長じる ) // (v5r,vi) to grow/to grow up
 KanjiVerb_5r( 長老として奉る ) // (v5r) to kick (a person) upstairs/to revere (a person) as one's leader
 KanjiVerb_5r( 捗る ) // (v5r,vi) to make progress/to move right ahead (with the work)/to advance/(P)
 KanjiVerb_5r( 直る ) // (v5r,vi) (1) to be cured/to get well/to be healed/(2) to get mended/to be repaired/to be fixed/(P)
 KanjiVerb_5r( 直謝る ) // (v5r) to apologize earnestly/to apologise earnestly
 KanjiVerb_5r( 鎮まる ) // (v5r,vi) to quieten down/to calm down/to subside/to die down/to abate/to be suppressed/(P)
 KanjiVerb_5r( 追い捲くる ) // (v5r) to disperse/to chase away
 KanjiVerb_5r( 追い迫る ) // (v5r) to gain on someone/run somebody close
 KanjiVerb_5r( 追い縋る ) // (v5r,vi) to be hot on a person's heels
 KanjiVerb_5r( 痛がる ) // (v5r,vi) to complain of pain
 KanjiVerb_5r( 痛み入る ) // (v5r,vi) to be greatly obliged/to be very sorry
 KanjiVerb_5r( 通りかかる ) // (v5r,vi) to happen to pass by
 KanjiVerb_5r( 通り掛かる ) // (v5r,vi) to happen to pass by/(P)
 KanjiVerb_5r( 通る ) // (v5r,vi) to pass (by)/to go through/to walk along/to pass exams/to attend (e.g., school)/(P)
 KanjiVerb_5r( 掴まる ) // (v5r,vi) to hold on to/to grasp/(P)
 KanjiVerb_5r( 掴み掛かる ) // (v5r) to grab at
 KanjiVerb_5r( 漬かる ) // (v5r,vi) (1) to be pickled/to be well seasoned/(2) to be submerged/to be soaked/(P)
 KanjiVerb_5r( 綴る ) // (v5r) to spell/to compose
 KanjiVerb_5r( 吊り下がる ) // (v5r,vi) to hang down/to dangle
 KanjiVerb_5r( 吊る ) // (v5r) to hang/to suspend (something from something)/to be hanged (by the neck)/(P)
 KanjiVerb_5r( 釣り下がる ) // (v5r,vi) to hang down/to dangle
 KanjiVerb_5r( 釣り上がる ) // (v5r,vi) to be lifted up/to be hung up
 KanjiVerb_5r( 低まる ) // (v5r,vi) to lower/to be lowered
 KanjiVerb_5r( 停まる ) // (v5r,vi) to stop/to halt
 KanjiVerb_5r( 貞はる ) // (v5r) (sl) to harp too long on a subject
 KanjiVerb_5r( 定まる ) // (v5r,vi) to become settled/to be fixed/(P)
 KanjiVerb_5r( 締まる ) // (v5r,vi) (1) to be shut/to close/to be closed/(2) to be locked/(3) to tighten/to be tightened/(4) to become sober/to become tense/(P)
 KanjiVerb_5r( 泥濘る ) // (v5r,vi) to be muddy/to be slushy
 KanjiVerb_5r( 滴り落ちる ) // (v5r) to trickle down
 KanjiVerb_5r( 滴る ) // (v5r,vi) to drip/to drop/to trickle
 KanjiVerb_5r( 天下る ) // (v5r,vi) to descend from heaven
 KanjiVerb_5r( 天降る ) // (v5r,vi) to descend from heaven
 KanjiVerb_5r( 天翔る ) // (v5r,vi) to soar
 KanjiVerb_5r( 纏まる ) // (v5r,vi) to be collected/to be settled/to be in order/(P)
 KanjiVerb_5r( 纏わる ) // (v5r,vi) about/concerning/to be associated with
 KanjiVerb_5r( 貼る ) // (v5r) to stick/to paste/(P)
 KanjiVerb_5r( 転がる ) // (v5r,vi) to roll/to tumble/(P)
 KanjiVerb_5r( 転げ回る ) // (v5r) to roll about/to writhe about
 KanjiVerb_5r( 点る ) // (v5r,vi) to burn/to be lighted/to be lit
 KanjiVerb_5r( 伝って登る ) // (v5r) to shin up/to climb up
 KanjiVerb_5r( 伝わる ) // (v5r,vi) to be handed down/to be introduced/to be transmitted/to be circulated/to go along/to walk along/(P)
 KanjiVerb_5r( 渡る ) // (v5r,vi) to cross over/to go across/(P)
 KanjiVerb_5r( 登る ) // (v5r,vi) (1) to rise/to ascend/to go up/to climb/(2) to go to (the capital)/(3) to be promoted/(4) to add up to/(5) to advance (in price)/(6) to sail up/(7) to come up (on the agenda)/(P)
 KanjiVerb_5r( 度重なる ) // (v5r,vi) to repeat/to be frequent
 KanjiVerb_5r( 怒る ) // (v5r,vi) (1) to get angry/to get mad/(2) to be angry/(P)
 KanjiVerb_5r( 怒鳴る ) // (v5r,vi) to shout/to yell/(P)
 KanjiVerb_5r( 倒れ掛かる ) // (v5r,vi) to be weighed down by debt
 KanjiVerb_5r( 凍る ) // (v5r,vi) to freeze/to be frozen over/to congeal/(P)
 KanjiVerb_5r( 盗る ) // (v5r) to take (nuance of stealing)
 KanjiVerb_5r( 灯る ) // (v5r,vi) to burn/to be lighted/to be lit
 KanjiVerb_5r( 当たる ) // (v5r,vi) to be hit/to be successful/to face (confront)/to lie (in the direction of)/to undertake/to treat/to be equivalent to/to apply to/to be applicable/to be assigned/(P)
 KanjiVerb_5r( 当てはまる ) // (v5r) to apply (a rule)/to be applicable/to come under (a category)/to fulfill/(P)
 KanjiVerb_5r( 当て擦る ) // (v5r,vi) to insinuate/to satirize/to satirise/to take a dig at
 KanjiVerb_5r( 当て嵌まる ) // (v5r) to apply (a rule)/to be applicable/to come under (a category)/to fulfill
 KanjiVerb_5r( 当る ) // (v5r,vi) to be hit/to be successful/to face (confront)/to lie (in the direction of)/to undertake/to treat/to be equivalent to/to apply to/to be applicable/to be assigned
 KanjiVerb_5r( 到る ) // (v5r,vi) to attain
 KanjiVerb_5r( 討ち入る ) // (v5r,vi) to break into (a house to kill the master)/to raid
 KanjiVerb_5r( 踏み止まる ) // (v5r,vi) to stay on/to remain/to hold out/to stop (doing)/to give up/to hold one's ground
 KanjiVerb_5r( 踏ん張る ) // (v5r,vi) to brace one's legs/to straddle/to stand firm/to plant oneself (somewhere)/to hold out/to persist/(P)
 KanjiVerb_5r( 踏ん反り返る ) // (v5r,vi) to lie on one's back with legs outstretched/to recline/to get cocky/to be arrogant
 KanjiVerb_5r( 逃げ回る ) // (v5r,vi) to run from place to place
 KanjiVerb_5r( 逃げ帰る ) // (v5r,vi) to scurr or run home
 KanjiVerb_5r( 逃げ去る ) // (v5r) to take flight/to disappear
 KanjiVerb_5r( 逃げ切る ) // (v5r,vi) to get away/to manage to hold on/(P)
 KanjiVerb_5r( 逃げ走る ) // (v5r) to flee/to run away
 KanjiVerb_5r( 透き通る ) // (v5r,vi) to be(come) transparent/(P)
 KanjiVerb_5r( 透けて写る ) // (v5r) to be seen through
 KanjiVerb_5r( 動き回る ) // (v5r) to move around
 KanjiVerb_5r( 同工異曲である ) // (v5r) to be equally excellent in workmanship though difficult in style/to be practically the same
 KanjiVerb_5r( 得意がる ) // (v5r) to be inflated with pride
 KanjiVerb_5r( 禿げ上がる ) // (v5r) to recede
 KanjiVerb_5r( 禿上がる ) // (v5r) to become bald fom the forehead/to recede
 KanjiVerb_5r( 読み終る ) // (v5r) to finish reading/to read through
 KanjiVerb_5r( 読み終わる ) // (v5r) to finish reading/to read through
 KanjiVerb_5r( 読み耽ける ) // (v5r,vi) to be absorbed in reading
 KanjiVerb_5r( 読み耽る ) // (v5r,vi) to be absorbed in reading
 KanjiVerb_5r( 突き掛る ) // (v5r) to thrust at (with a knife)
 KanjiVerb_5r( 突き刺さる ) // (v5r,vi) to stick into/to pierce/to run into
 KanjiVerb_5r( 突き通る ) // (v5r,vi) to penetrate
 KanjiVerb_5r( 突き当たる ) // (v5r) to run into/to collide with/(P)
 KanjiVerb_5r( 突っかかる ) // (v5r,vi) to charge/to lunge/to rush
 KanjiVerb_5r( 突っ掛かる ) // (v5r,vi) to charge/to lunge/to rush
 KanjiVerb_5r( 突っ走る ) // (v5r,vi) to run swiftly
 KanjiVerb_5r( 突っ張る ) // (v5r) to support/to become stiff/to become taut/to thrust (one's opponent)/to stick to (one's opinion)/to insist on/(P)
 KanjiVerb_5r( 呑んで掛かる ) // (v5r) to make light of/to hold lightly
 KanjiVerb_5r( 曇る ) // (v5r,vi) to become cloudy/to become dim/(P)
 KanjiVerb_5r( 鈍る ) // (v5r,vi) to become less capable/to grow dull/to become blunt/to weaken/(P)
 KanjiVerb_5r( 乳繰る ) // (v5r,vi) to have secret or illicit sexual relations
 KanjiVerb_5r( 入り交じる ) // (v5r,vi) to mix with/to be mixed
 KanjiVerb_5r( 入り混じる ) // (v5r,vi) to mix with/to be mixed
 KanjiVerb_5r( 入り浸る ) // (v5r,vi) to seep in/to stay long
 KanjiVerb_5r( 入り替わる ) // (v5r,vi) to change places/to relieve (one another)
 KanjiVerb_5r( 入る ) // (v5r) to enter/to break into/to join/to enroll/to contain/to hold/to accommodate/to have (an income of)/(P)
 KanjiVerb_5r( 入れ替わる ) // (v5r,vi) to change places/to relieve one another
 KanjiVerb_5r( 入れ代わる ) // (v5r,vi) to change places/to relieve one another
 KanjiVerb_5r( 妊る ) // (v5r,vi) to become pregnant
 KanjiVerb_5r( 忍び寄る ) // (v5r,vi) to creep/to steal up/to draw near unnoticed
 KanjiVerb_5r( 忍び入る ) // (v5r,vi) to steal or sneak or slip into
 KanjiVerb_5r( 年寄る ) // (v5r,vi) to grow old
 KanjiVerb_5r( 年取る ) // (v5r,vi) to grow old/to age
 KanjiVerb_5r( 燃え移る ) // (v5r) (of fire) to spread/to extend itself
 KanjiVerb_5r( 燃え広がる ) // (v5r,vi) to spread (flames)
 KanjiVerb_5r( 燃え上がる ) // (v5r,vi) to flare up/to burst into flames/(P)
 KanjiVerb_5r( 燃え盛る ) // (v5r,vi) to blaze/to burn brightly
 KanjiVerb_5r( 粘る ) // (v5r,vi) to be sticky/to be adhesive/to persevere/to persist/to stick to/(P)
 KanjiVerb_5r( 濃い仲である ) // (v5r) to be thick (with)/to bound by love
 KanjiVerb_5r( 納まる ) // (v5r,vi) (1) to be in one's place/to be installed/to settle into/(2) to be obtained/to be settled/to be paid/to be delivered/(P)
 KanjiVerb_5r( 罵る ) // (v5r,vi) to speak ill of/to abuse/(P)
 KanjiVerb_5r( 廃る ) // (v5r) to go out of use/to become obsolete/to die out/to go out of fashion
 KanjiVerb_5r( 売れ残る ) // (v5r,vi) to remain unsold/to be left on the shelf
 KanjiVerb_5r( 這いずる ) // (v5r,vi) (uk) to creep/to crawl
 KanjiVerb_5r( 這い回る ) // (v5r,vi) to creep about
 KanjiVerb_5r( 這い上がる ) // (v5r,vi) to creep up/to crawl up
 KanjiVerb_5r( 這い蹲る ) // (v5r,vi) to grovel
 KanjiVerb_5r( 泊まる ) // (v5r,vi) to stay at (e.g., hotel)/(P)
 KanjiVerb_5r( 泊る ) // (v5r,vi) to stay at (e.g., hotel)
 KanjiVerb_5r( 白だと判る ) // (v5r) to be found innocent
 KanjiVerb_5r( 薄まる ) // (v5r,vi) to become weak/(P)
 KanjiVerb_5r( 迫り上がる ) // (v5r) (uk) to gradually rise
 KanjiVerb_5r( 迫る ) // (v5r,vi) to draw near/to press/(P)
 KanjiVerb_5r( 抜かる ) // (v5r,vi) to make a mistake/(P)
 KanjiVerb_5r( 抜き去る ) // (v5r) to (sur)pass/to overtake
 KanjiVerb_5r( 抜け上がる ) // (v5r,vi) to be balding in the front/to have a receding hairline
 KanjiVerb_5r( 抜け替わる ) // (v5r) to shed/to moult/to fall out
 KanjiVerb_5r( 判る ) // (v5r,vi) (1) to understand/to grasp/(2) to know/to realize/to realise
 KanjiVerb_5r( 反り返る ) // (v5r,vi) to warp/to bend backwards/to throw the head (or shoulders) back/to throw out the chest
 KanjiVerb_5r( 反る ) // (v5r,vi) (1) to warp/to be warped/to curve/to be curved/to be arched/(2) to bend (backward)/(P)
 KanjiVerb_5r( 繁忙である ) // (v5r) to be fully occupied/to be busy
 KanjiVerb_5r( 悲しがる ) // (v5r,vi) to feel sorrow/to be sad
 KanjiVerb_5r( 疲れ切る ) // (v5r) to be exhausted/to be tired out
 KanjiVerb_5r( 皮肉る ) // (v5r,vi) to speak cynically or with sarcasm
 KanjiVerb_5r( 罷り通る ) // (v5r,vi) to go by/to let pass/to get away with
 KanjiVerb_5r( 肥え太る ) // (v5r) to grow fat
 KanjiVerb_5r( 肥る ) // (v5r,vi) to grow fat (stout, plump)/to become fat
 KanjiVerb_5r( 飛びすさる ) // (v5r,vi) to leap back/to jump back
 KanjiVerb_5r( 飛び移る ) // (v5r) to jump from one thing to another
 KanjiVerb_5r( 飛び回る ) // (v5r,vi) to fly about/to skip about/to bustle about
 KanjiVerb_5r( 飛び掛かる ) // (v5r) to spring upon
 KanjiVerb_5r( 飛び去る ) // (v5r,vi) to flee away/to scatter
 KanjiVerb_5r( 飛び散る ) // (v5r,vi) to fly around/to scatter
 KanjiVerb_5r( 飛び上がる ) // (v5r,vi) to spring/to jump up/to fly up/to skip/(P)
 KanjiVerb_5r( 飛び乗る ) // (v5r,vi) to jump on
 KanjiVerb_5r( 飛び退る ) // (v5r,vi) to leap back/to jump back
 KanjiVerb_5r( 飛び翔る ) // (v5r,vi) to fly/to soar
 KanjiVerb_5r( 飛回る ) // (v5r,vi) to fly about/to skip about/to bustle about
 KanjiVerb_5r( 飛上がる ) // (v5r,vi) to spring/to jump up/to fly up/to skip
 KanjiVerb_5r( 備わる ) // (v5r,vi) (1) to be furnished with/to be endowed with/(2) to be among/to be one of/to be possessed of/(P)
 KanjiVerb_5r( 膝行る ) // (v5r,vi) to crawl/to shuffle along
 KanjiVerb_5r( 百歩譲る ) // (v5r) to be unwilling but to give in
 KanjiVerb_5r( 氷る ) // (v5r,vi) to freeze/to be frozen over/to congeal
 KanjiVerb_5r( 病気にかかる ) // (v5r) to contract a disease
 KanjiVerb_5r( 病気に罹る ) // (v5r) to contract a disease
 KanjiVerb_5r( 頻る ) // (v5r,vi) to repeat over and over again
 KanjiVerb_5r( 付き切る ) // (v5r) to be in constant attendance
 KanjiVerb_5r( 付け回る ) // (v5r,vi) to follow/to shadow/to hanker after/to hover around
 KanjiVerb_5r( 付け上がる ) // (v5r,vi) to be elated/to be spoiled/to be spoilt/to take advantage of
 KanjiVerb_5r( 付け入る ) // (v5r) to take advantage of/to impose on
 KanjiVerb_5r( 怖がる ) // (v5r,vi) to be afraid of/to fear/to dread/to be nervous (about)/to be shy (of)/(P)
 KanjiVerb_5r( 怖る ) // (v5r) to fear/to be afraid
 KanjiVerb_5r( 浮かび上がる ) // (v5r,vi) to rise to the surface/(P)
 KanjiVerb_5r( 浮き上がる ) // (v5r,vi) to float/to rise to the surface
 KanjiVerb_5r( 腐る ) // (v5r) to rot/to go bad/(P)
 KanjiVerb_5r( 負ぶさる ) // (v5r) to ride on a person's shoulders/to be carried on a person's back
 KanjiVerb_5r( 武張る ) // (v5r,vi) to be soldierly/to be martial
 KanjiVerb_5r( 舞い上がる ) // (v5r,vi) to soar/to fly high/to be whirled up
 KanjiVerb_5r( 舞い戻る ) // (v5r,vi) to come back
 KanjiVerb_5r( 舞い躍る ) // (v5r) to dance
 KanjiVerb_5r( 舞い踊る ) // (v5r) to dance
 KanjiVerb_5r( 封切る ) // (v5r) to release (a film)
 KanjiVerb_5r( 腹が下る ) // (v5r) to have loose bowels
 KanjiVerb_5r( 腹が減る ) // (v5r) to become hungry
 KanjiVerb_5r( 覆いかぶさる ) // (v5r,vi) to hang over/to cover
 KanjiVerb_5r( 覆い被さる ) // (v5r,vi) to hang over/to cover
 KanjiVerb_5r( 覆る ) // (v5r,vi) to topple over/to be overturned/to capsize/(P)
 KanjiVerb_5r( 沸き起こる ) // (v5r,vi) to burst/to arise
 KanjiVerb_5r( 沸き上がる ) // (v5r,vi) (1) to boil up/to break out/to arise/to seethe/(2) to get excited/to be in uproar
 KanjiVerb_5r( 沸き返る ) // (v5r,vi) (1) to boil up/to break out/to arise/to seethe/(2) to get excited/to be in uproar
 KanjiVerb_5r( 分かち取る ) // (v5r) to divide the spoils/to receive a share
 KanjiVerb_5r( 分かり切る ) // (v5r,vi) to be evident/to be obvious/to understand completely
 KanjiVerb_5r( 分かる ) // (v5r,vi) (1) to understand/to grasp/(2) to know/to realize/to realise/(P)
 KanjiVerb_5r( 分け取る ) // (v5r) to apportion/to share
 KanjiVerb_5r( 分け入る ) // (v5r) to force one's way/to push through
 KanjiVerb_5r( 分り切る ) // (v5r,vi) to be evident/to be obvious/to understand completely
 KanjiVerb_5r( 憤る ) // (v5r,vi) to fret/to be fretful/to be peevish
 KanjiVerb_5r( 聞き入る ) // (v5r) to listen attentively to/to be lost in
 KanjiVerb_5r( 併さる ) // (v5r,vi) to get together/to unite
 KanjiVerb_5r( 平つくばる ) // (v5r) to make a deep bow
 KanjiVerb_5r( 閉じこもる ) // (v5r,vi) to seclude oneself/to shut oneself away/(P)
 KanjiVerb_5r( 閉じ込もる ) // (v5r,vi) to seclude oneself/to shut oneself away
 KanjiVerb_5r( 閉じ篭る ) // (v5r,vi) to seclude oneself/to shut oneself away
 KanjiVerb_5r( 閉じ籠る ) // (v5r,vi) to seclude oneself/to shut oneself away
 KanjiVerb_5r( 閉まる ) // (v5r,vi) (1) to be shut/to close/to be closed/(2) to be locked/(3) to tighten/to be tightened/(4) to become sober/to become tense/(P)
 KanjiVerb_5r( 閉幕となる ) // (v5r) to come to a close (end)
 KanjiVerb_5r( 偏る ) // (v5r,vi) to be one-sided/to incline/to be partial/to be prejudiced/to lean/to be biased/to be biassed/(P)
 KanjiVerb_5r( 変わる ) // (v5r,vi) to change/to be transformed/to vary/to be revised/to be different/to move location/(P)
 KanjiVerb_5r( 片寄る ) // (v5r,vi) to be one-sided/to incline/to be partial/to be prejudiced/to lean/to be biased/to be biassed/(P)
 KanjiVerb_5r( 返る ) // (v5r,vi) to return/to come back/to go back/(P)
 KanjiVerb_5r( 便る ) // (v5r,vi) to rely on/to have recourse to/to depend on
 KanjiVerb_5r( 捕まる ) // (v5r,vi) to be caught/to be arrested/(P)
 KanjiVerb_5r( 歩き回る ) // (v5r) to walk about/to walk to and fro/to pace around/(P)
 KanjiVerb_5r( 歩み寄る ) // (v5r,vi) to step up/to compromise/to meet halfway/(P)
 KanjiVerb_5r( 募る ) // (v5r) to invite/to solicit help, participation, etc./(P)
 KanjiVerb_5r( 慕い寄る ) // (v5r,vi) to approach in adoration
 KanjiVerb_5r( 暮れ残る ) // (v5r,vi) lingering faint light of twilight
 KanjiVerb_5r( 包まる ) // (v5r,vi) to be wrapped up (e.g., in a blanket)/to cover oneself
 KanjiVerb_5r( 包み飾る ) // (v5r,vi) to cover up and make a show
 KanjiVerb_5r( 呆れ反る ) // (v5r,vi) to be utterly amazed
 KanjiVerb_5r( 呆れ返る ) // (v5r,vi) to be utterly amazed
 KanjiVerb_5r( 崩れ去る ) // (v5r) to crumble away/to collapse
 KanjiVerb_5r( 褒め奉る ) // (v5r) to praise/to render homage to
 KanjiVerb_5r( 乏しくなる ) // (v5r) to get scarce/to run short
 KanjiVerb_5r( 亡くなる ) // (v5r,vi) to die/(P)
 KanjiVerb_5r( 忘る ) // (v5r) (arch) to lose something
 KanjiVerb_5r( 暴れ回る ) // (v5r) to rampage/to run riot
 KanjiVerb_5r( 棒で殴る ) // (v5r) to hit with a club
 KanjiVerb_5r( 棒に振る ) // (v5r) to make a mess of/to sacrifice/to waste
 KanjiVerb_5r( 翻る ) // (v5r,vi) to turn over/to wave/to flutter/(P)
 KanjiVerb_5r( 摩り寄る ) // (v5r,vi) to draw close to/to edge up to/to snuggle up to/to nestle close to/to cuddle with/to draw closer to
 KanjiVerb_5r( 摩り切る ) // (v5r) to cut by rubbing/to wear out/to spend all (one's money)
 KanjiVerb_5r( 磨り減る ) // (v5r,vi) to be worn down/to be reduced
 KanjiVerb_5r( 埋まる ) // (v5r,vi) to be buried/to be surrounded/to overflow/to be filled/(P)
 KanjiVerb_5r( 蔓延る ) // (v5r,vi) to spread/to run rampant/to grow thick/to become powerful/(P)
 KanjiVerb_5r( 味わい知る ) // (v5r) to taste and know
 KanjiVerb_5r( 魅入る ) // (v5r) to be entranced or possessed
 KanjiVerb_5r( 眠る ) // (v5r,vi) to sleep/(P)
 KanjiVerb_5r( 務まる ) // (v5r,vi) to be fit for/to be equal to/to function properly
 KanjiVerb_5r( 無くなる ) // (v5r,vi) to disappear/to get lost/(P)
 KanjiVerb_5r( 名のる ) // (v5r,vi) to call oneself (name, label, etc)/to give one's name (as)
 KanjiVerb_5r( 名告る ) // (v5r,vi) to call oneself (name, label, etc)/to give one's name (as)
 KanjiVerb_5r( 名乗る ) // (v5r,vi) to call oneself (name, label, etc)/to give one's name (as)/(P)
 KanjiVerb_5r( 命じ終わる ) // (v5r) to finish giving orders
 KanjiVerb_5r( 明け残る ) // (v5r,vi) moon and stars remaining in the morning sky
 KanjiVerb_5r( 明け渡る ) // (v5r,vi) to become daylight
 KanjiVerb_5r( 明る ) // (v5r,vi) to become bright/to become clear
 KanjiVerb_5r( 鳴り渡る ) // (v5r,vi) to resound (echo) far and wide
 KanjiVerb_5r( 鳴る ) // (v5r,vi) to sound/to ring/to resound/to echo/to roar/to rumble/(P)
 KanjiVerb_5r( 滅入る ) // (v5r,vi) to feel depressed
 KanjiVerb_5r( 面白がる ) // (v5r,vi) to amuse oneself/to be amused/to enjoy/to think fun
 KanjiVerb_5r( 模る ) // (v5r,vi) (1) to model on/to make in the shape of/to represent/to pattern after/to imitate/(2) to symbolise
 KanjiVerb_5r( 茂る ) // (v5r,vi) to grow thick/to luxuriate/to be luxurious/(P)
 KanjiVerb_5r( 猛る ) // (v5r,vi) (1) to rage/to be fierce/(2) to be excited
 KanjiVerb_5r( 儲かる ) // (v5r,vi) to be profitable/to yield a profit/(P)
 KanjiVerb_5r( 黙りこくる ) // (v5r,vi) to keep silent
 KanjiVerb_5r( 黙る ) // (v5r,vi) to be silent/(P)
 KanjiVerb_5r( 目が回る ) // (v5r) to be dizzy/to feel faint
 KanjiVerb_5r( 目立ちたがる ) // (v5r) to show off
 KanjiVerb_5r( 勿体ぶる ) // (v5r,vi) to put on airs/to assume importance
 KanjiVerb_5r( 勿体振る ) // (v5r,vi) to put on airs/to assume importance
 KanjiVerb_5r( 戻る ) // (v5r,vi) to turn back/to return/(P)
 KanjiVerb_5r( 弥増さる ) // (v5r,vi) to become still greater
 KanjiVerb_5r( 躍り掛かる ) // (v5r) to spring at or upon
 KanjiVerb_5r( 躍り掛る ) // (v5r) to spring at or upon
 KanjiVerb_5r( 躍り懸かる ) // (v5r) to spring at or upon
 KanjiVerb_5r( 躍り上がる ) // (v5r,vi) to spring up/to leap to one's feet/to jump up and down
 KanjiVerb_5r( 躍る ) // (v5r,vi) (1) to dance/(2) to jump
 KanjiVerb_5r( 優る ) // (v5r,vi) to excel/to surpass/to outrival
 KanjiVerb_5r( 有り難がる ) // (v5r) to be thankful/to feel grateful/to show one's gratitude
 KanjiVerb_5r( 有り余る ) // (v5r,vi) to be superfluous/to be in excess/to be more than enough
 KanjiVerb_5r( 有る ) // (v5r-i,vi) (1) (uk) to live/to be/to exist/(2) to have/(3) to be located/(4) to be equipped with/(5) to happen/to come about
 KanjiVerb_5r( 有余る ) // (v5r,vi) to be superfluous/to be in excess/to be more than enough
 KanjiVerb_5r( 湧き起る ) // (v5r) to well up/to rise
 KanjiVerb_5r( 湧き上がる ) // (v5r,vi) (1) to boil up/to break out/to arise/to seethe/(2) to get excited/to be in uproar
 KanjiVerb_5r( 湧き上る ) // (v5r,vi) (1) to boil up/to break out/to arise/to seethe/(2) to get excited/to be in uproar
 KanjiVerb_5r( 由る ) // (v5r,vi) (1) (uk) to be due to/to be caused by/(2) to depend on/to turn on/(3) to be based on/to come from
 KanjiVerb_5r( 遊び回る ) // (v5r) to jaunt around/to play around/to visit one place after another without effect
 KanjiVerb_5r( 余る ) // (v5r,vi) to remain/to be left over/to be in excess/to be too many/(P)
 KanjiVerb_5r( 与る ) // (v5r,vi) to participate in
 KanjiVerb_5r( 与太る ) // (v5r,vi) to live a wicked life
 KanjiVerb_5r( 容体振る ) // (v5r,vi) to put on airs
 KanjiVerb_5r( 揚がる ) // (v5r,vi) to rise/(P)
 KanjiVerb_5r( 揺さぶる ) // (v5r) to shake/to jolt/to rock/to swing/(P)
 KanjiVerb_5r( 揺すぶる ) // (v5r) to shake/to jolt/to rock/to swing
 KanjiVerb_5r( 様変わる ) // (v5r) to change the state of things
 KanjiVerb_5r( 要る ) // (v5r,vi) to need/(P)
 KanjiVerb_5r( 踊り上がる ) // (v5r,vi) to spring up/to leap to one's feet/to jump up and down
 KanjiVerb_5r( 踊る ) // (v5r,vi) (1) to dance/(2) to jump/(P)
 KanjiVerb_5r( 欲張る ) // (v5r,vi) to covet/to lust for
 KanjiVerb_5r( 来たる ) // (v5r,vi) to come/to arrive/to be due to/to be next/to be forthcoming
 KanjiVerb_5r( 来掛かる ) // (v5r) to happen to come
 KanjiVerb_5r( 頼る ) // (v5r,vi) to rely on/to have recourse to/to depend on/(P)
 KanjiVerb_5r( 絡まる ) // (v5r,vi) to be entwined/to be involved
 KanjiVerb_5r( 落ち入る ) // (v5r,vi) to fall/to trap/to cave in/to collapse
 KanjiVerb_5r( 利口過ぎる ) // (v5r) to be too clever
 KanjiVerb_5r( 裏返る ) // (v5r,vi) to be turned inside out
 KanjiVerb_5r( 立ちなおる ) // (v5r,vi) to regain one's footing/to recover/(of the market) to improve/(P)
 KanjiVerb_5r( 立ちのぼる ) // (v5r,vi) to go up/to rise up
 KanjiVerb_5r( 立ちはだかる ) // (v5r,vi) to block one's way
 KanjiVerb_5r( 立ちふさがる ) // (v5r,vi) to stand in one's way
 KanjiVerb_5r( 立ち回る ) // (v5r,vi) to walk about/to turn up/to conduct oneself
 KanjiVerb_5r( 立ち寄る ) // (v5r,vi) to stop by/to drop in for a short visit/(P)
 KanjiVerb_5r( 立ち去る ) // (v5r,vi) to leave/to depart/to take one's leave/(P)
 KanjiVerb_5r( 立ち交じる ) // (v5r) to join
 KanjiVerb_5r( 立ち交る ) // (v5r,vi) to join
 KanjiVerb_5r( 立ち塞がる ) // (v5r,vi) to stand in one's way
 KanjiVerb_5r( 立ち止まる ) // (v5r) to stop/to halt/to stand still/(P)
 KanjiVerb_5r( 立ち至る ) // (v5r) to come to
 KanjiVerb_5r( 立ち勝る ) // (v5r) to surpass
 KanjiVerb_5r( 立ち上がる ) // (v5r,vi) to stand up/(P)
 KanjiVerb_5r( 立ち上る ) // (v5r,vi) to go up/to rise up
 KanjiVerb_5r( 立ち替わる ) // (v5r) to alternate/to take turns
 KanjiVerb_5r( 立ち直る ) // (v5r,vi) to regain one's footing/to recover/(of the market) to improve/(P)
 KanjiVerb_5r( 立ち通しである ) // (v5r) to keep standing (all the way)
 KanjiVerb_5r( 立ち入る ) // (v5r,vi) to enter/to interfere
 KanjiVerb_5r( 立ち返る ) // (v5r,vi) to turn back
 KanjiVerb_5r( 立ち戻る ) // (v5r,vi) to return/to come back
 KanjiVerb_5r( 立て直る ) // (v5r,vi) to recover/to rally/to pick up
 KanjiVerb_5r( 立て籠る ) // (v5r,vi) to barricade oneself in/to hold (a fort, etc.)/to shut oneself up/to be besieged/to dig in
 KanjiVerb_5r( 立寄る ) // (v5r,vi) to stop by/to drop in for a short visit
 KanjiVerb_5r( 立塞がる ) // (v5r,vi) to stand in one's way
 KanjiVerb_5r( 立入る ) // (v5r,vi) to enter/to interfere
 KanjiVerb_5r( 立籠る ) // (v5r,vi) to barricade oneself in/to hold (a fort, etc.)/to shut oneself up/to be besieged/to dig in
 KanjiVerb_5r( 掠る ) // (v5r) to graze/to squeeze/to become blurred/to exploit
 KanjiVerb_5r( 流行る ) // (v5r,vi) to flourish/to thrive/to be popular/to come into fashion/(P)
 KanjiVerb_5r( 溜まる ) // (v5r,vi) to collect/to gather/to save/(P)
 KanjiVerb_5r( 溜る ) // (v5r,vi) to collect/to gather/to save
 KanjiVerb_5r( 溜飲が下がる ) // (v5r) to feel gratified
 KanjiVerb_5r( 留まる ) // (v5r,vi) (1) to remain/to abide/to stay (in the one place)/(v5r) (2) to come to a halt/(v5r) (3) to be limited to/(v5r) (4) to stop
 KanjiVerb_5r( 留る ) // (v5r,vi) (1) to remain/to abide/to stay (in the one place)/(v5r) (2) to come to a halt/(v5r) (3) to stop
 KanjiVerb_5r( 旅する ) // (v5r) to travel/to take a trip
 KanjiVerb_5r( 良家の生まれである ) // (v5r) to be of good family
 KanjiVerb_5r( 淋しがる ) // (v5r) to miss someone (or something)/to feel lonely
 KanjiVerb_5r( 冷え上がる ) // (v5r,vi) to get completely chilled
 KanjiVerb_5r( 冷え切る ) // (v5r,vi) to become completely chilled
 KanjiVerb_5r( 冷え入る ) // (v5r,vi) to become completely chilled
 KanjiVerb_5r( 冷え募る ) // (v5r) to get colder/to get chilled
 KanjiVerb_5r( 列なる ) // (v5r,vi) to extend/to stretch out/to stand in a row
 KanjiVerb_5r( 劣る ) // (v5r,vi) to fall behind/to be inferior to/(P)
 KanjiVerb_5r( 恋い乱る ) // (v5r) to be lovesick
 KanjiVerb_5r( 恋い籠る ) // (v5r) to be deeply in love
 KanjiVerb_5r( 恋しがる ) // (v5r) to yearn for/to miss
 KanjiVerb_5r( 練る ) // (v5r,vi) to knead/to work over/to polish up/(P)
 KanjiVerb_5r( 連なる ) // (v5r,vi) to extend/to stretch out/to stand in a row/(P)
 KanjiVerb_5r( 連れ帰る ) // (v5r) to bring (someone) back home/to take (someone) back home
 KanjiVerb_5r( 連れ去る ) // (v5r) to take away/to kidnap/(P)
 KanjiVerb_5r( 労る ) // (v5r) to pity/to sympathize with/to sympathise with/to console/to care for/to be kind to/(P)
 KanjiVerb_5r( 漏る ) // (v5r) to leak/to run out/(P)
 KanjiVerb_5r( 篭る ) // (v5r,vi) to seclude oneself/to be confined in/to be implied/to be stuffy
 KanjiVerb_5r( 録る ) // (v5r) to record (video, audio, etc.)
 KanjiVerb_5r( 亙る ) // (v5r) to extend
 KanjiVerb_5r( 亘る ) // (v5r) to extend
 KanjiVerb_5r( 詫び入る ) // (v5r,vi) to apologize sincerely/to apologise sincerely
 KanjiVerb_5r( 椀ぎ取る ) // (v5r) (uk) to pluck off/to pick/to break or tear off
 KanjiVerb_5r( 倚り懸かる ) // (v5r,vi) to lean against/to recline on/to lean on/to rely on
 KanjiVerb_5r( 倚る ) // (v5r,vi) to lean on/to rest against
 KanjiVerb_5r( 傲る ) // (v5r,vi) (1) to be proud/to be haughty/(2) to be extravagant/to live luxuriously/(3) to give (someone) a treat
 KanjiVerb_5r( 凭り掛かる ) // (v5r,vi) to lean against/to recline on/to lean on/to rely on
 KanjiVerb_5r( 凭る ) // (v5r,vi) to lean on/to rest against
 KanjiVerb_5r( 凭れ掛かる ) // (v5r) to lean on/to recline on/to rely on
 KanjiVerb_5r( 刎ね上がる ) // (v5r,vi) to jump up/to spring up
 KanjiVerb_5r( 剪る ) // (v5r) to cut
 KanjiVerb_5r( 吝嗇る ) // (v5r) (uk) to be stingy/to scrimp
 KanjiVerb_5r( 唸る ) // (v5r,vi) to groan/to moan/to roar/to howl/to growl/to hum/to buzz/to sough/(P)
 KanjiVerb_5r( 噎せ返る ) // (v5r,vi) to choke/to sob convulsively
 KanjiVerb_5r( 囀る ) // (v5r,vi) (uk) to sing/to chirp/to twitter/(P)
 KanjiVerb_5r( 奢る ) // (v5r,vi) (1) to be proud/to be haughty/(2) to be extravagant/to live luxuriously/(3) to give (someone) a treat/(P)
 KanjiVerb_5r( 孕る ) // (v5r,vi) to become pregnant
 KanjiVerb_5r( 孵る ) // (v5r) to hatch out
 KanjiVerb_5r( 悖る ) // (v5r,vi) to go against/to deviate from/to oppose
 KanjiVerb_5r( 憚る ) // (v5r,vi) (1) to hesitate/to have scruples/(2) to lord it over/to have great influence
 KanjiVerb_5r( 罹る ) // (v5r) to suffer from/(P)
 KanjiVerb_5r( 撓垂れ掛かる ) // (v5r,vi) to lean coquettishly against/to snuggle into/to nestle into
 KanjiVerb_5r( 攀じ上る ) // (v5r,vi) to climb/to clamber (over, up)/to scramble (up)/to scale/to claw one's way up
 KanjiVerb_5r( 攀じ登る ) // (v5r,vi) to climb/to clamber (over, up)/to scramble (up)/to scale/to claw one's way up
 KanjiVerb_5r( 梃子摺る ) // (v5r) (uk) to have much trouble/to have a hard time/to not know how to handle
 KanjiVerb_5r( 沁み透る ) // (v5r,vi) (1) to soak through/(2) to be deeply impressed
 KanjiVerb_5r( 沁透る ) // (v5r,vi) (1) to soak through/(2) to be deeply impressed
 KanjiVerb_5r( 溯る ) // (v5r,vi) to go back/to go upstream/to make retroactive
 KanjiVerb_5r( 滾る ) // (v5r,vi) to boil/to seethe
 KanjiVerb_5r( 滲み渡る ) // (v5r,vi) to penetrate/to pervade/to spread
 KanjiVerb_5r( 漲る ) // (v5r,vi) (uk) to swell up/to rise/to be (brim) full of/to pervade
 KanjiVerb_5r( 炒まる ) // (v5r) to be sauteed in oil
 KanjiVerb_5r( 烟る ) // (v5r,vi) (1) to smoke (e.g., fire)/(2) to be hazy
 KanjiVerb_5r( 燻ぶる ) // (v5r,vi) to smoke/to smoulder/to smolder/to sputter
 KanjiVerb_5r( 熾きる ) // (v5r,vi) to be kindled (fire)/to be made
 KanjiVerb_5r( 狡ける ) // (v5r) (uk) to shirk one's duties/to be idle/to play truant
 KanjiVerb_5r( 甦る ) // (v5r,vi) to be resurrected/to be revived/to be resuscitated/to be rehabilitated/(P)
 KanjiVerb_5r( 痙る ) // (v5r) to cramp/to be cramped/to contract
 KanjiVerb_5r( 痼る ) // (v5r,vi) to stiffen/to harden
 KanjiVerb_5r( 祟る ) // (v5r,vi) to curse/to cast a spell
 KanjiVerb_5r( 籠もる ) // (v5r,vi) to seclude oneself/to be confined in/to be implied/to be stuffy/(P)
 KanjiVerb_5r( 籠る ) // (v5r,vi) to seclude oneself/to be confined in/to be implied/to be stuffy
 KanjiVerb_5r( 縋る ) // (v5r,vi) to cling to/to rely on/(P)
 KanjiVerb_5r( 翔る ) // (v5r,vi) to soar/to fly/(P)
 KanjiVerb_5r( 舐めずる ) // (v5r) to lick one's lips
 KanjiVerb_5r( 茹だる ) // (v5r,vi) (1) to boil/to seethe/(2) to be oppressed by heat
 KanjiVerb_5r( 蟠る ) // (v5r) (1) (uk) to lurk/to hover in the background/(2) to be coiled up/to stretch tortuously
 KanjiVerb_5r( 訛る ) // (v5r,vi) to speak with an accent/to be corrupted (of word)
 KanjiVerb_5r( 訝る ) // (v5r,vi) to suspect
 KanjiVerb_5r( 踞る ) // (v5r,vi) (uk) to crouch/to squat/to cower
 KanjiVerb_5r( 蹲る ) // (v5r,vi) (uk) to crouch/to squat/to cower/(P)
 KanjiVerb_5r( 躄る ) // (v5r,vi) to crawl/to shuffle along
 KanjiVerb_5r( 躙り寄る ) // (v5r,vi) to sidle up to
 KanjiVerb_5r( 軋る ) // (v5r) to creak/to squeak
 KanjiVerb_5r( 騙し取る ) // (v5r) to take something away by deception
 KanjiVerb_5r( 驕る ) // (v5r,vi) (1) to be proud/to be haughty/(2) to be extravagant/to live luxuriously/(3) to give (someone) a treat

 KanjiVerb_5r( 乗る ) // (v5r,vi) (1) to get on/to ride in/to board/to mount/to get up on/(v5r) (2) to spread (paints)/to be taken in/(v5r) (3) to share in/to join/to be found in (a dictionary)/to feel like doing/to be mentioned in/to be in harmony with/(P)
 
 KanjiVerb( 架ける )

 KanjiVerb( 受付ける )
 KanjiVerb( 見てとれる )
 KanjiVerb( ちがう )
 KanjiVerb( 申上げる )
 KanjiVerb( だす ) // спрашивать
 KanjiVerb( 差しあげる ) // связываться
 KanjiVerb( ばらつく ) // различаться
 KanjiVerb( 切り替る ) // переключиться
 KanjiVerb( 替る ) // переключиться
 KanjiVerb_5r( ビビる ) // ビビり ます --> болтать
 KanjiVerb_5r( びびる ) // びびり ます --> болтать



}
