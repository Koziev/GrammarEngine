// CD->01.03.2009
// LC->18.08.2010

automat sg
{
 #define KanaVerb(x,Transitive=NULL) \
  #begin
   entry x : JAP_VERB
   {
    paradigm auto
    JAP_FORM:KANA
    #if Transitive!=NULL
    JAP_TRANSITIVE
    #endif	
   }
  #end 

 #define KanaVerb_5r(x,Transitive=NULL) \
  #begin
   entry x : JAP_VERB
   {
    paradigm JapVerb_9801
    JAP_FORM:KANA
    #if Transitive!=NULL
    JAP_TRANSITIVE
    #endif	
   }
  #end 


 
 KanaVerb( あやす, JAP_TRANSITIVE ) // (v5s,vt) to dandle
 KanaVerb( あしらう, JAP_TRANSITIVE ) // (v5u,vt) to arrange/to treat/to handle/to deal with
 KanaVerb( くすねる, JAP_TRANSITIVE ) // (v1,vt) to pilfer/to filch/to swipe
 KanaVerb( こじつける, JAP_TRANSITIVE ) // (v1,vt) to distort/to strain (interpretation)/to force (meaning)
 KanaVerb( させる, JAP_TRANSITIVE ) // (v1,vt) to make (someone) do
 KanaVerb( すっぽかす, JAP_TRANSITIVE ) // (v5s,vt) to stand (someone) up/to leave (something) undone/to neglect (a duty)
 KanaVerb( ずらす, JAP_TRANSITIVE ) // (v5s,vt) to shift/to slide (e.g., something away from something else)/to move (e.g., something out of the way)/to put off/to delay/(P)
 KanaVerb( せがむ, JAP_TRANSITIVE ) // (v5m,vt) to badger (pester) (a person to do)/(P)
 KanaVerb( せしめる, JAP_TRANSITIVE ) // (v1,vt) to cheat someone out of/to wangle
 KanaVerb( はぐらかす, JAP_TRANSITIVE ) // (v5s,vt) to dodge/to evade/to give the slip
 KanaVerb( はめこむ, JAP_TRANSITIVE ) // (v5m,vt) to inlay/to insert/to fix into a container
 KanaVerb( ひけらかす, JAP_TRANSITIVE ) // (v5s,vt) to show off/to make a display (e.g., of wealth)
 KanaVerb( ひんまげる, JAP_TRANSITIVE ) // (v1,vt) (1) to bend (with great force)/to twist/to wrench/(2) to distort (the truth)
 KanaVerb( ぶっちゃける, JAP_TRANSITIVE ) // (v1,vt) to be frank .../to put things bluntly ...
 KanaVerb( ぶらさげる, JAP_TRANSITIVE ) // (v1,vt) to hang/to suspend/to dangle/to swing/(P)
 KanaVerb( ほざく, JAP_TRANSITIVE ) // (v5k,vt) to spatter/to prate/to prattle/to babble/to grumble/to murmur/to brawl
 KanaVerb( まやかす, JAP_TRANSITIVE ) // (v5s,vt) to cheat/to swindle/to deceive
 KanaVerb( パクつく, JAP_TRANSITIVE ) // (v5k,vt) to open your mouth wide and eat heartily/to gulp down food
 KanaVerb( めでる, JAP_TRANSITIVE ) // (v1,vt) to love/to admire
 KanaVerb( にぎらす, JAP_TRANSITIVE ) // (v5s,vt) to let (someone) take hold of your hand/(P)
 KanaVerb( にぎりつぶす, JAP_TRANSITIVE ) // (v5s,vt) to crush (with one's hands)/to abandon
 KanaVerb( にぎりしめる, JAP_TRANSITIVE ) // (v1,vt) to grasp tightly/(P)
 KanaVerb( へしこむ, JAP_TRANSITIVE ) // (v5m,vt) to push into
 KanaVerb( へす, JAP_TRANSITIVE ) // (v5s,vt) (arch) to dent/to press/to push
 KanaVerb( あつかう, JAP_TRANSITIVE ) // (v5u,vt) to handle/to deal with/to treat/(P)
 KanaVerb( しごく, JAP_TRANSITIVE ) // (v5k,vt) (uk) to draw through one's hand/to stroke (a beard)/to work someone hard
 KanaVerb( こきおろす, JAP_TRANSITIVE ) // (v5s,vt) to denounce/to disparage/to lambast/to abuse
 KanaVerb( こきつかう, JAP_TRANSITIVE ) // (v5u,vt) to work someone hard
 KanaVerb( くらます, JAP_TRANSITIVE ) // (v5s,vt) to abscond/to deceive
 KanaVerb( あんじる, JAP_TRANSITIVE ) // (v1,vt) to be anxious/to ponder
 KanaVerb( あんずる, JAP_TRANSITIVE ) // (vz,vt) (1) to be anxious or concerned about/to ponder (anxiously)/to fear/(2) to investigate/to consider/to plan
 KanaVerb( いちづける, JAP_TRANSITIVE ) // (v1,vt) to place (in relation to the whole)/to rank/to position/to locate/(P)
 KanaVerb( かこう, JAP_TRANSITIVE ) // (v5u,vt) to enclose/(P)
 KanaVerb( かこむ, JAP_TRANSITIVE ) // (v5m,vt) to surround/to encircle/(P)
 KanaVerb( ゆだねる, JAP_TRANSITIVE ) // (v1,vt) to entrust to/to devote oneself to/(P)
 KanaVerb( いみづける, JAP_TRANSITIVE ) // (v1,vt) to give meaning to
 KanaVerb( なぐさめる, JAP_TRANSITIVE ) // (v1,vt) to comfort/to console/(P)
 KanaVerb( なさる, JAP_TRANSITIVE ) // (v5aru,vt) (hon) to do/(P)
 KanaVerb( なしおえる, JAP_TRANSITIVE ) // (v1,vt) to accomplish/to finish
 KanaVerb( しおおせる, JAP_TRANSITIVE ) // (v1,vt) to accomplish
 KanaVerb( しあう, JAP_TRANSITIVE ) // (v5u,vt) (uk) to do together
 KanaVerb( しのこす, JAP_TRANSITIVE ) // (v5s,vt) to leave unfinished
 KanaVerb( しつくす, JAP_TRANSITIVE ) // (v5s,vt) to do everything possible
 KanaVerb( しおとす, JAP_TRANSITIVE ) // (v5s,vt) to fail to do/to make light of/to neglect
 KanaVerb( たがえる, JAP_TRANSITIVE ) // (v1,vt) (1) to break one's word/(2) to be unpunctual
 KanaVerb( ちがえる, JAP_TRANSITIVE ) // (v1,vt) to change
 KanaVerb( そだてる, JAP_TRANSITIVE ) // (v1,vt) to raise/to rear/to bring up/(P)
 KanaVerb( そだてあげる, JAP_TRANSITIVE ) // (v1,vt) to raise (to maturity)/to rear/to train/to educate
 KanaVerb( はぐくむ, JAP_TRANSITIVE ) // (v5m,vt) to raise/to rear/to bring up/(P)
 KanaVerb( いんしょうづける, JAP_TRANSITIVE ) // (v1,vt) to impress (someone)/(P)
 KanaVerb( ひきおこす, JAP_TRANSITIVE ) // (v5s,vt) to cause/(P)
 KanaVerb( ひきあわせる, JAP_TRANSITIVE ) // (v1,vt) to introduce/to compare
 KanaVerb( ひきこむ, JAP_TRANSITIVE ) // (v5m,vt) to draw in/to win over
 KanaVerb( ひきずりまわす, JAP_TRANSITIVE ) // (v5s,vt) to drag around
 KanaVerb( ひきずりこむ, JAP_TRANSITIVE ) // (v5m,vt) to drag in
 KanaVerb( ひきずりだす, JAP_TRANSITIVE ) // (v5s,vt) to drag out
 KanaVerb( ひきたおす, JAP_TRANSITIVE ) // (v5s,vt) to pull down
 KanaVerb( ひきいれる, JAP_TRANSITIVE ) // (v1,vt) to drag into/to win over
 KanaVerb( ひきはがす, JAP_TRANSITIVE ) // (v5s,vt) to tear off
 KanaVerb( ひきはぐ, JAP_TRANSITIVE ) // (v5g,vt) to tear off
 KanaVerb( ひきはらう, JAP_TRANSITIVE ) // (v5u,vt) to vacate
 KanaVerb( ひきわける, JAP_TRANSITIVE ) // (v1,vt) to pull apart/to separate
 KanaVerb( ひきはなつ, JAP_TRANSITIVE ) // (v5t,vt) to pull apart
 KanaVerb( ひきあげる, JAP_TRANSITIVE ) // (v1,vt) to withdraw/to leave/to pull out/to retire
 KanaVerb( ひっくりかえす, JAP_TRANSITIVE ) // (v5s,vt) to turn over/to overturn/to knock over/to upset/to turn inside out
 KanaVerb( ひっかける, JAP_TRANSITIVE ) // (v1,vt) (1) to hang (something) on (something)/to throw on (clothes)/(2) to hook/to catch/to trap/to ensnare/(3) to cheat/to evade payment/to jump a bill/(4) to drink (alcohol)/(5) to spit at (a person)/(6) to hit the ball off the end of the bat (baseball)
 KanaVerb( ひっこめる, JAP_TRANSITIVE ) // (v1,vt) to draw in/to take in
 KanaVerb( ひっかきまわす, JAP_TRANSITIVE ) // (v5s,vt) to ransack (a drawer)/to rummage/to stir up (mud)/to throw into confusion/to tamper with
 KanaVerb( ひっかく, JAP_TRANSITIVE ) // (v5k,vt) to scratch
 KanaVerb( ひっぱりだす, JAP_TRANSITIVE ) // (v5s,vt) to take out/to drag out
 KanaVerb( ひっぱぐ, JAP_TRANSITIVE ) // (v5g,vt) to tear off
 KanaVerb( ひきさげる, JAP_TRANSITIVE ) // (v1,vt) to pull down/to lower/to reduce/to withdraw/(P)
 KanaVerb( ひきおろす, JAP_TRANSITIVE ) // (v5s,vt) to haul down/to drag down
 KanaVerb( ひきまわす, JAP_TRANSITIVE ) // (v5s,vt) to draw a curtain/to guide/to parade about
 KanaVerb( ひきよせる, JAP_TRANSITIVE ) // (v1,vt) to draw or pull something towards oneself (e.g., chair)
 KanaVerb( ひきつぐ, JAP_TRANSITIVE ) // (v5g,vt) to take over/to hand over/(P)
 KanaVerb( ひきとめる, JAP_TRANSITIVE ) // (v1,vt) to detain/to check/to restrain/(P)
 KanaVerb( ひきうける, JAP_TRANSITIVE ) // (v1,vt) to undertake/to take up/to take over/to be responsible for/to guarantee/to contract (disease)
 KanaVerb( ひきだす, JAP_TRANSITIVE ) // (v5s,vt) to pull out/to take out/to draw out/to withdraw/(P)
 KanaVerb( ひきのばす, JAP_TRANSITIVE ) // (v5s,vt) to delay/to enlarge/(P)
 KanaVerb( ひきかえる, JAP_TRANSITIVE ) // (v1,vt) to exchange (things)/to reverse
 KanaVerb( ひきなおす, JAP_TRANSITIVE ) // (v5s,vt) to redo
 KanaVerb( ひきしめる, JAP_TRANSITIVE ) // (v1,vt) to tighten/to stiffen/to brace/to strain/(P)
 KanaVerb( ひきわたす, JAP_TRANSITIVE ) // (v5s,vt) to deliver/to extradite/to stretch across/to hand over
 KanaVerb( ひきあてる, JAP_TRANSITIVE ) // (v1,vt) to apply/to compare
 KanaVerb( ひきぬく, JAP_TRANSITIVE ) // (v5k,vt) to extract/to uproot/to pull out/(P)
 KanaVerb( ひきかえす, JAP_TRANSITIVE ) // (v5s,vt) to repeat/to send back/to bring back/to retrace one's steps/(P)
 KanaVerb( ひきもどす, JAP_TRANSITIVE ) // (v5s,vt) to bring back/to restore/(P)
 KanaVerb( ひきおとす, JAP_TRANSITIVE ) // (v5s,vt) to pull down/to automatically debit (from a bank account)
 KanaVerb( ひきはなす, JAP_TRANSITIVE ) // (v5s,vt) to pull apart/to separate/(P)
 KanaVerb( ひきたてる, JAP_TRANSITIVE ) // (v1,vt) to favour/to favor/to promote/to march (a prisoner off)/to support
 KanaVerb( ひきさく, JAP_TRANSITIVE ) // (v5k,vt) to tear up/to tear off/to split/(P)
 KanaVerb( ひきつれる, JAP_TRANSITIVE ) // (v1,vt) to take along with
 KanaVerb( のます, JAP_TRANSITIVE ) // (v5s,vt) to make somebody drink
 KanaVerb( のみまわす, JAP_TRANSITIVE ) // (v5s,vt) to pass the cup round
 KanaVerb( のみあかす, JAP_TRANSITIVE ) // (v5s,vt) to drink the night away
 KanaVerb( のみくだす, JAP_TRANSITIVE ) // (v5s,vt) to swallow/to gulp down
 KanaVerb( のみほす, JAP_TRANSITIVE ) // (v5s,vt) to drink up/to drain (cup)
 KanaVerb( のみつぶす, JAP_TRANSITIVE ) // (v5s,vt) to drink away one's money
 KanaVerb( のみたおす, JAP_TRANSITIVE ) // (v5s,vt) to skip out on one's bar bill
 KanaVerb( かくす, JAP_TRANSITIVE ) // (v5s,vt) to hide/to conceal/(P)
 KanaVerb( はこびこむ, JAP_TRANSITIVE ) // (v5m,vt) to carry in/to bring in
 KanaVerb( いとなむ, JAP_TRANSITIVE ) // (v5m,vt) to carry on (e.g., in ceremony)/to run a business/(P)
 KanaVerb( いとう, JAP_TRANSITIVE ) // (v5u,vt) to dislike/to hate/to grudge (doing)/to spare (oneself)/to be weary of/to take (good) care of
 KanaVerb( えんじる, JAP_TRANSITIVE ) // (v1,vt) to perform (a play)/to play (a part)/to act (a part)/to commit (a blunder)/(P)
 KanaVerb( えんずる, JAP_TRANSITIVE ) // (vz,vt) to perform/to play/(P)
 KanaVerb( えんづける, JAP_TRANSITIVE ) // (v1,vt) to marry off/to give in marriage
 KanaVerb( とおざける, JAP_TRANSITIVE ) // (v1,vt) to keep away/to keep at a distance
 KanaVerb( とおのける, JAP_TRANSITIVE ) // (v1,vt) to keep (someone) at a distance
 KanaVerb( へこます, JAP_TRANSITIVE ) // (v5s,vt) to dent/to indent/to depress/to humiliate
 KanaVerb( くぼめる, JAP_TRANSITIVE ) // (v1,vt) to hollow out
 KanaVerb( おしさげる, JAP_TRANSITIVE ) // (v1,vt) to push or press or force down/to depress
 KanaVerb( おしひろめる, JAP_TRANSITIVE ) // (v1,vt) to extend by force/to aggrandize/to aggrandise
 KanaVerb( おしのける, JAP_TRANSITIVE ) // (v1,vt) to push aside/to brush aside
 KanaVerb( おしいただく, JAP_TRANSITIVE ) // (v5k,vt) to accept an object and hold it reverently over one's head
 KanaVerb( おしあてる, JAP_TRANSITIVE ) // (v1,vt) to push (something) against
 KanaVerb( おしつける, JAP_TRANSITIVE ) // (v1,vt) to press/to push/to force/(P)
 KanaVerb( おしわける, JAP_TRANSITIVE ) // (v1,vt) to push aside
 KanaVerb( おしたてる, JAP_TRANSITIVE ) // (v1,vt) to set up/to support
 KanaVerb( おしとどめる, JAP_TRANSITIVE ) // (v1,vt) to stop
 KanaVerb( おっかぶせる, JAP_TRANSITIVE ) // (v1,vt) to put a thing on top of another/to cover/to lay something on
 KanaVerb( おったてる, JAP_TRANSITIVE ) // (v1,vt) to raise/to set up
 KanaVerb( おしかくす, JAP_TRANSITIVE ) // (v5s,vt) to cover up/to conceal
 KanaVerb( おしこめる, JAP_TRANSITIVE ) // (v1,vt) to shut up/to imprison
 KanaVerb( おしころす, JAP_TRANSITIVE ) // (v5s,vt) to crush to death/to stifle to death/to squeeze to death
 KanaVerb( おしだす, JAP_TRANSITIVE ) // (v5s,vt) to crowd out/to push out/to squeeze out
 KanaVerb( おしあげる, JAP_TRANSITIVE ) // (v1,vt) to boost/to force up/to push up
 KanaVerb( おしとおす, JAP_TRANSITIVE ) // (v5s,vt) to persist in/to carry out/to have one's own way/to push through/to carry through
 KanaVerb( おしつぶす, JAP_TRANSITIVE ) // (v5s,vt) to squash/to crush/to flatten
 KanaVerb( おしたおす, JAP_TRANSITIVE ) // (v5s,vt) to push down
 KanaVerb( おしかえす, JAP_TRANSITIVE ) // (v5s,vt) to force back/to jostle
 KanaVerb( おしもどす, JAP_TRANSITIVE ) // (v5s,vt) to push back
 KanaVerb( おしながす, JAP_TRANSITIVE ) // (v5s,vt) to wash away
 KanaVerb( よこたえる, JAP_TRANSITIVE ) // (v1,vt) to lie down/to lay (oneself) down
 KanaVerb( なぐりとばす, JAP_TRANSITIVE ) // (v5s,vt) to knock a person off his feet
 KanaVerb( なぐりつける, JAP_TRANSITIVE ) // (v1,vt) to beat (someone in battle)
 KanaVerb( ぬくめる, JAP_TRANSITIVE ) // (v1,vt) to warm/to heat
 KanaVerb( さげわたす, JAP_TRANSITIVE ) // (v5s,vt) to make a (government) grant/to release (a criminal)
 KanaVerb( うたいあげる, JAP_TRANSITIVE ) // (v1,vt) to sing at the top of one's voice/to express one's feelings fully in a poem
 KanaVerb( さいなむ, JAP_TRANSITIVE ) // (v5m,vt) to torment/to torture/to harass
 KanaVerb( いじめる, JAP_TRANSITIVE ) // (v1,vt) to tease/to torment/to persecute/to chastise/(P)
 KanaVerb( いらだてる, JAP_TRANSITIVE ) // (v1,vt) to irritate/to exasperate
 KanaVerb( すごす, JAP_TRANSITIVE ) // (v5s,vt) to pass/to spend/to go through/to tide over/(P)
 KanaVerb( ときはなす, JAP_TRANSITIVE ) // (v5s,vt) to liberate/to set free
 KanaVerb( ときはなつ, JAP_TRANSITIVE ) // (v5t,vt) to release
 KanaVerb( ほどく, JAP_TRANSITIVE ) // (v5k,vt) to unfasten/to untie/to unwrap (e.g. parcel)/(P)
 KanaVerb( ほぐす, JAP_TRANSITIVE ) // (v5s,vt) to unfasten
 KanaVerb( げせる, JAP_TRANSITIVE ) // (v1,vt) to understand/to comprehend
 KanaVerb( まわす, JAP_TRANSITIVE ) // (v5s,vt) to turn/to revolve/(P)
 KanaVerb( こわす, JAP_TRANSITIVE ) // (v5s,vt) to break/to break down/(P)
 KanaVerb( あやしむ, JAP_TRANSITIVE ) // (v5m,vt) to suspect/(P)
 KanaVerb( くいる, JAP_TRANSITIVE ) // (v1,vt) to regret/(P)
 KanaVerb( くやむ, JAP_TRANSITIVE ) // (v5m,vt) to mourn/(P)
 KanaVerb( くいあらためる, JAP_TRANSITIVE ) // (v1,vt) to repent/to be penitent
 KanaVerb( なつかしむ, JAP_TRANSITIVE ) // (v5m,vt) to yearn for (miss) someone (thing)/(P)
 KanaVerb( なつく, JAP_TRANSITIVE ) // (v5k,vt) to become emotionally attached
 KanaVerb( いましめる, JAP_TRANSITIVE ) // (v1,vt) to admonish/to remonstrate/(P)
 KanaVerb( あらたむ, JAP_TRANSITIVE ) // (v5m,vt) (abbr) to revise/to change
 KanaVerb( ひらける, JAP_TRANSITIVE ) // (v1,vt) to become civilized/to become civilised/to become opened up/to be up-to-date/(P)
 KanaVerb( あけひろげる, JAP_TRANSITIVE ) // (v1,vt) to open wide/to reveal hidden contents
 KanaVerb( あけはなつ, JAP_TRANSITIVE ) // (v5t,vt) to throw open/to leave open
 KanaVerb( はずす, JAP_TRANSITIVE ) // (v5s,vt) (1) to unfasten/to undo/(2) to remove/to take off/to deinstall/(3) to bump off (sl)/(P)
 KanaVerb( かいまみる, JAP_TRANSITIVE ) // (v1,vt) to take a peep at/to catch a glimpse of/(P)
 KanaVerb( たしかめる, JAP_TRANSITIVE ) // (v1,vt) to ascertain/(P)
 KanaVerb( おぼえこむ, JAP_TRANSITIVE ) // (v5m,vt) to master
 KanaVerb( かどだてる, JAP_TRANSITIVE ) // (v1,vt) to be sharp/to be pointed
 KanaVerb( かけかえる, JAP_TRANSITIVE ) // (v1,vt) to replace/to substitute
 KanaVerb( かけわたす, JAP_TRANSITIVE ) // (v5s,vt) to build (a bridge) over a river
 KanaVerb( わりびく, JAP_TRANSITIVE ) // (v5k,vt) to discount/(P)
 KanaVerb( わりこむ, JAP_TRANSITIVE ) // (v5m,vt) to cut in/to thrust oneself into/to wedge oneself in/to muscle in on/to interrupt/to disturb
 KanaVerb( わりだす, JAP_TRANSITIVE ) // (v5s,vt) to calculate/to compute/to infer/(P)
 KanaVerb( わりあてる, JAP_TRANSITIVE ) // (v1,vt) to assign/to allot/to allocate/to divide among/to distribute/to prorate/(P)
 KanaVerb( わりつける, JAP_TRANSITIVE ) // (v1,vt) to allot/to distribute/to lay out/to divide among/to assign
 KanaVerb( わりもどす, JAP_TRANSITIVE ) // (v5s,vt) to rebate/kickback
 KanaVerb( くくりつける, JAP_TRANSITIVE ) // (v1,vt) to fasten (a person) to
 KanaVerb( かなえる, JAP_TRANSITIVE ) // (v1,vt) to grant (request, wish)/(P)
 KanaVerb( かみくだく, JAP_TRANSITIVE ) // (v5k,vt) (1) to crunch/to masticate/(2) to simplify/to explain plainly
 KanaVerb( かみころす, JAP_TRANSITIVE ) // (v5s,vt) (1) to stifle a smile, yawn, etc./(2) to bite to death
 KanaVerb( かみこなす, JAP_TRANSITIVE ) // (v5s,vt) to chew/to digest
 KanaVerb( かみつぶす, JAP_TRANSITIVE ) // (v5s,vt) to chew up
 KanaVerb( かみしめる, JAP_TRANSITIVE ) // (v1,vt) (1) to chew thoroughly/(2) to reflect upon/to digest
 KanaVerb( かみつく, JAP_TRANSITIVE ) // (v5k,vt) to bite (at)/to snap at/to snarl at
 KanaVerb( かみわける, JAP_TRANSITIVE ) // (v1,vt) to taste/to distinguish/to understand
 KanaVerb( かりほす, JAP_TRANSITIVE ) // (v5s,vt) to cut and dry (in the sun)
 KanaVerb( かりふく, JAP_TRANSITIVE ) // (v5k,vt) to thatch (a roof)
 KanaVerb( かわかす, JAP_TRANSITIVE ) // (v5s,vt) to dry (clothes, etc.)/to desiccate/(P)
 KanaVerb( まきつける, JAP_TRANSITIVE ) // (v1,vt) to wreathe (e.g rope)
 KanaVerb( まきこむ, JAP_TRANSITIVE ) // (v5m,vt) to roll up/to involve/to enfold/to swallow up/to drag into/(P)
 KanaVerb( まきもどす, JAP_TRANSITIVE ) // (v5s,vt) to rewind
 KanaVerb( くつろげる, JAP_TRANSITIVE ) // (v1,vt) to loose/to ease/to relax
 KanaVerb( ほしかためる, JAP_TRANSITIVE ) // (v1,vt) to dry until stiff
 KanaVerb( ほす, JAP_TRANSITIVE ) // (v5s,vt) to air/to dry/to desiccate/to drain (off)/to drink up/(P)
 KanaVerb( あまやかす, JAP_TRANSITIVE ) // (v5s,vt) to pamper/to spoil/(P)
 KanaVerb( ゆるめる, JAP_TRANSITIVE ) // (v1,vt) to loosen/to slow down/(P)
 KanaVerb( つらぬきとおす, JAP_TRANSITIVE ) // (v5s,vt) to enforce (one's) will/(P)
 KanaVerb( つらぬく, JAP_TRANSITIVE ) // (v5k,vt) to go through/(P)
 KanaVerb( かんがみる, JAP_TRANSITIVE ) // (v1,vt) to heed/to take into account/to learn from/to take warning from/in view of/in the light of
 KanaVerb( まちがえる, JAP_TRANSITIVE ) // (v1,vt) (1) to make a mistake (in)/to commit an error (e.g., in calculation)/(2) to confuse/to mistake something for something else/(P)
 KanaVerb( まびく, JAP_TRANSITIVE ) // (v5k,vt) to thin out/to cull/to run on a curtailed schedule
 KanaVerb( かんけいづける, JAP_TRANSITIVE ) // (v1,vt) to relate to/to connect with
 KanaVerb( おとしいれる, JAP_TRANSITIVE ) // (v1,vt) to tempt/to ensnare
 KanaVerb( まるめる, JAP_TRANSITIVE ) // (v1,vt) to make round/to round off/to roll up/to curl up/to seduce/to cajole/to explain away/(P)
 KanaVerb( まるめこむ, JAP_TRANSITIVE ) // (v5m,vt) (1) to coax/to seduce/(2) to roll up and put in (to something)/to bundle up/(P)
 KanaVerb( ふくませる, JAP_TRANSITIVE ) // (v1,vt) to soak/to saturate/to suckle/to make one hold something in the mouth/to include/to instruct/to make one understand
 KanaVerb( ふくめる, JAP_TRANSITIVE ) // (v1,vt) to include/to instruct/to make one understand/to put in one's mouth/(P)
 KanaVerb( ねがいさげる, JAP_TRANSITIVE ) // (v1,vt) to withdraw a request
 KanaVerb( ねがいでる, JAP_TRANSITIVE ) // (v1,vt) to apply for
 KanaVerb( ねがう, JAP_TRANSITIVE ) // (v5u,vt) to desire/to wish/to request/to beg/to hope/to implore/(P)
 KanaVerb( くわだてる, JAP_TRANSITIVE ) // (v1,vt) to plan/to plot/to propose/to design/to intend/to contemplate/to attempt/to undertake/(P)
 KanaVerb( たくらむ, JAP_TRANSITIVE ) // (v5m,vt) (uk) to scheme/to plan/to play a trick/to invent/to conspire/to frame up/(P)
 KanaVerb( あやめる, JAP_TRANSITIVE ) // (v1,vt) to wound/to murder
 KanaVerb( よせる, JAP_TRANSITIVE ) // (v1,vt) (1) to come near/to let someone approach/(2) to collect/to gather/to add/to put aside/(P)
 KanaVerb( よせあつめる, JAP_TRANSITIVE ) // (v1,vt) to put together/to gather/to collect/to scrape together
 KanaVerb( よせつける, JAP_TRANSITIVE ) // (v1,vt) to get close to
 KanaVerb( いみきらう, JAP_TRANSITIVE ) // (v5u,vt) to detest/to abhor/to loathe
 KanaVerb( きにかける, JAP_TRANSITIVE ) // (v1,vt) to weigh on one's mind/to trouble one's heart/to be concerned about/to worry about
 KanaVerb( かがやかす, JAP_TRANSITIVE ) // (v5s,vt) to light up/to brighten
 KanaVerb( じゃらかす, JAP_TRANSITIVE ) // (v5s,vt) to call for jokes
 KanaVerb( あざむく, JAP_TRANSITIVE ) // (v5k,vt) to deceive/(P)
 KanaVerb( うたがう, JAP_TRANSITIVE ) // (v5u,vt) to doubt/to distrust/to be suspicious of/to suspect/(P)
 KanaVerb( ぎむづける, JAP_TRANSITIVE ) // (v1,vt) to obligate
 KanaVerb( つめあわせる, JAP_TRANSITIVE ) // (v1,vt) to pack an assortment of goods, etc.
 KanaVerb( つめこむ, JAP_TRANSITIVE ) // (v5m,vt) to cram/to stuff/to jam/to squeeze/to pack/to crowd
 KanaVerb( つめかえる, JAP_TRANSITIVE ) // (v1,vt) to repack/to refill
 KanaVerb( しいたげる, JAP_TRANSITIVE ) // (v1,vt) to oppress/(P)
 KanaVerb( さかだてる, JAP_TRANSITIVE ) // (v1,vt) to ruffle (up)
 KanaVerb( やすめる, JAP_TRANSITIVE ) // (v1,vt) to rest/to suspend/to give relief/(P)
 KanaVerb( およぼす, JAP_TRANSITIVE ) // (v5s,vt) to exert/to cause/to exercise/(P)
 KanaVerb( すう, JAP_TRANSITIVE ) // (v5u,vt) to smoke/to breathe in/to suck/(P)
 KanaVerb( すいよせる, JAP_TRANSITIVE ) // (v1,vt) to draw in/to attract
 KanaVerb( すいこむ, JAP_TRANSITIVE ) // (v5m,vt) (1) to inhale/to breathe in/to suck up/to imbibe/(2) to absorb/to soak up
 KanaVerb( すいだす, JAP_TRANSITIVE ) // (v5s,vt) to suck (or draw) out/to aspirate
 KanaVerb( すいあげる, JAP_TRANSITIVE ) // (v1,vt) (1) to pump off or out/to suck up or out/to siphon off (incl. wealth)/(2) to take up others' views and opinions
 KanaVerb( すいつける, JAP_TRANSITIVE ) // (v1,vt) to attract/to be used to
 KanaVerb( せかせる, JAP_TRANSITIVE ) // (v1,vt) to hurry up
 KanaVerb( せきたてる, JAP_TRANSITIVE ) // (v1,vt) to hurry (up)/to press/to urge on
 KanaVerb( すくいだす, JAP_TRANSITIVE ) // (v5s,vt) to rescue/to free
 KanaVerb( もとむ, JAP_TRANSITIVE ) // (v5m,vt) to want/to seek/to request
 KanaVerb( もとめる, JAP_TRANSITIVE ) // (v1,vt) to seek/to request/to demand/to want/to wish for/to search for/to pursue (pleasure)/to hunt (a job)/to buy/(P)
 KanaVerb( くみわける, JAP_TRANSITIVE ) // (v1,vt) to apportion drawn water/to show understanding
 KanaVerb( くみほす, JAP_TRANSITIVE ) // (v5s,vt) to empty out/to drain out/to pump dry
 KanaVerb( くみだす, JAP_TRANSITIVE ) // (v5s,vt) to pump out/to bail (water)
 KanaVerb( なかせる, JAP_TRANSITIVE ) // (v1,vt) (1) to make someone cry/to move someone to tears/(2) to grieve
 KanaVerb( なきはらす, JAP_TRANSITIVE ) // (v5s,vt) to weep one's eyes out
 KanaVerb( なきくらす, JAP_TRANSITIVE ) // (v5s,vt) to spend one's days in tears and sorrow
 KanaVerb( なきあかす, JAP_TRANSITIVE ) // (v5s,vt) to weep the night out/to weep all night
 KanaVerb( いなす, JAP_TRANSITIVE ) // (v5s,vt) to parry/to sidestep/to let go/to chase away
 KanaVerb( こばむ, JAP_TRANSITIVE ) // (v5m,vt) to refuse/to reject/to decline/(P)
 KanaVerb( へだてる, JAP_TRANSITIVE ) // (v1,vt) to be shut out/to separate/to isolate
 KanaVerb( せりあげる, JAP_TRANSITIVE ) // (v1,vt) to bid up the price of
 KanaVerb( つよめる, JAP_TRANSITIVE ) // (v1,vt) to strengthen/to emphasize/to emphasise/(P)
 KanaVerb( はさみこむ, JAP_TRANSITIVE ) // (v5m,vt) to insert
 KanaVerb( はさみあげる, JAP_TRANSITIVE ) // (v1,vt) to pick up (with chopsticks)/to take
 KanaVerb( おしえる, JAP_TRANSITIVE ) // (v1,vt) to teach/to inform/to instruct/(P)
 KanaVerb( おしえこむ, JAP_TRANSITIVE ) // (v5m,vt) to train to/to give an idea to
 KanaVerb( せばめる, JAP_TRANSITIVE ) // (v1,vt) to narrow/to reduce/to contract/(P)
 KanaVerb( おどかす, JAP_TRANSITIVE ) // (v5s,vt) to threaten/to coerce/(P)
 KanaVerb( おどろかす, JAP_TRANSITIVE ) // (v5s,vt) to surprise/to frighten/to create a stir/(P)
 KanaVerb( おおせつける, JAP_TRANSITIVE ) // (v1,vt) to command/to request/to appoint
 KanaVerb( あおのける, JAP_TRANSITIVE ) // (v1,vt) to turn up (one's face or a card)
 KanaVerb( あおぎみる, JAP_TRANSITIVE ) // (v1,vt) to look up
 KanaVerb( あおむける, JAP_TRANSITIVE ) // (v1,vt) to turn up (one's face)
 KanaVerb( おっしゃる, JAP_TRANSITIVE ) // (v5aru,vt) (hon) (uk) to say/to speak/to tell/to talk
 KanaVerb( こごらす, JAP_TRANSITIVE ) // (v5s,vt) to freeze/to congeal
 KanaVerb( こごらせる, JAP_TRANSITIVE ) // (v1,vt) to freeze/to congeal
 KanaVerb( きわめる, JAP_TRANSITIVE ) // (v1,vt) (1) to carry to extremes/to go to the end of something/(2) to investigate thoroughly/to master/(P)
 KanaVerb( つとめあげる, JAP_TRANSITIVE ) // (v1,vt) to serve out one's apprenticeship/to serve out one's time
 KanaVerb( きんじる, JAP_TRANSITIVE ) // (v1,vt) to prohibit/(P)
 KanaVerb( きんずる, JAP_TRANSITIVE ) // (vz,vt) to forbid/to suppress/(P)
 KanaVerb( ちかよせる, JAP_TRANSITIVE ) // (v1,vt) to bring close to/to associate with/(P)
 KanaVerb( ちかづける, JAP_TRANSITIVE ) // (v1,vt) to bring near/to put close/to let come near/to associate with/(P)
 KanaVerb( くるしめる, JAP_TRANSITIVE ) // (v1,vt) to torment/to harass/to inflict pain/(P)
 KanaVerb( かがめる, JAP_TRANSITIVE ) // (v1,vt) (uk) to stoop/to bend
 KanaVerb( ほりさげる, JAP_TRANSITIVE ) // (v1,vt) to dig down/to delve into/to get to the bottom of (a matter)/to investigate further
 KanaVerb( ほりおこす, JAP_TRANSITIVE ) // (v5s,vt) to reclaim/to dig up
 KanaVerb( ほりだす, JAP_TRANSITIVE ) // (v5s,vt) to dig out/to pick up
 KanaVerb( ほりあてる, JAP_TRANSITIVE ) // (v1,vt) to strike/to find/to dig up
 KanaVerb( ほりぬく, JAP_TRANSITIVE ) // (v5k,vt) to dig through/to drill into/to excavate
 KanaVerb( ほりかえす, JAP_TRANSITIVE ) // (v5s,vt) to dig up/to turn up/to tear up
 KanaVerb( くりこす, JAP_TRANSITIVE ) // (v5s,vt) to carry forward (i.e. on a balance sheet)/to transfer
 KanaVerb( くりのべる, JAP_TRANSITIVE ) // (v1,vt) to postpone/to defer
 KanaVerb( くりさげる, JAP_TRANSITIVE ) // (v1,vt) to defer/to postpone
 KanaVerb( くりまわす, JAP_TRANSITIVE ) // (v5s,vt) to roll over (debt)
 KanaVerb( くりよせる, JAP_TRANSITIVE ) // (v1,vt) to draw towards
 KanaVerb( くりひろげる, JAP_TRANSITIVE ) // (v1,vt) to unfold/to open
 KanaVerb( くりこむ, JAP_TRANSITIVE ) // (v5m,vt) to march in/to transfer/to send
 KanaVerb( くりだす, JAP_TRANSITIVE ) // (v5s,vt) to draw (a thread)/to sally forth/to send out
 KanaVerb( くりあげる, JAP_TRANSITIVE ) // (v1,vt) to move up/to advance
 KanaVerb( くりかえる, JAP_TRANSITIVE ) // (v1,vt) to exchange
 KanaVerb( くりいれる, JAP_TRANSITIVE ) // (v1,vt) to transfer/to add
 KanaVerb( くりもどす, JAP_TRANSITIVE ) // (v5s,vt) to put back
 KanaVerb( かたむける, JAP_TRANSITIVE ) // (v1,vt) to incline/to list/to bend/to lean/to tip/to tilt/to slant/to concentrate on/to ruin (a country)/to squander/to empty/(P)
 KanaVerb( かしげる, JAP_TRANSITIVE ) // (v1,vt) to lean/to incline/to tilt/to slant/(P)
 KanaVerb( かたげる, JAP_TRANSITIVE ) // (v1,vt) to lean/to incline/to tilt/to slant
 KanaVerb( めぐむ, JAP_TRANSITIVE ) // (v5m,vt) to bless/to show mercy to/(P)
 KanaVerb( かかげる, JAP_TRANSITIVE ) // (v1,vt) (1) to publish/to print/to carry (an article)/(2) to put up/to hang out/to hoist/to fly (a sail)/to float (a flag)/(P)
 KanaVerb( たずさえる, JAP_TRANSITIVE ) // (v1,vt) to carry in one's hand/(P)
 KanaVerb( うやまう, JAP_TRANSITIVE ) // (v5u,vt) to show respect/to honour/to honor/(P)
 KanaVerb( つなぎとめる, JAP_TRANSITIVE ) // (v1,vt) to tie/to fasten/to hitch
 KanaVerb( つなぐ, JAP_TRANSITIVE ) // (v5g,vt) (uk) to tie/to fasten/to connect/to transfer (phone call)/(P)
 KanaVerb( つなげる, JAP_TRANSITIVE ) // (v1,vt) to tie/to fasten/to connect/to transfer (phone call)
 KanaVerb( はからう, JAP_TRANSITIVE ) // (v5u,vt) to manage/to arrange/to talk over/to dispose of
 KanaVerb( かろんじる, JAP_TRANSITIVE ) // (v1,vt) to look down on/to make light of
 KanaVerb( かろんずる, JAP_TRANSITIVE ) // (vz,vt) to despise/to belittle/to look down on
 KanaVerb( むかえる, JAP_TRANSITIVE ) // (v1,vt) to go out to meet/to accept as a member of a group or family/(P)
 KanaVerb( むかえうつ, JAP_TRANSITIVE ) // (v5t,vt) to ambush/to attack/to meet the enemy/(P)
 KanaVerb( むかえいれる, JAP_TRANSITIVE ) // (v1,vt) to show in/to usher in
 KanaVerb( かかす, JAP_TRANSITIVE ) // (v5s,vt) to miss (doing)/to fail (to do)/(P)
 KanaVerb( きめる, JAP_TRANSITIVE ) // (v1,vt) to decide/(P)
 KanaVerb( きめこむ, JAP_TRANSITIVE ) // (v5m,vt) to take for granted/to assume/to pretend
 KanaVerb( ゆいあげる, JAP_TRANSITIVE ) // (v1,vt) to wear one's hair up/to arrange one's hair
 KanaVerb( むすびあわせる, JAP_TRANSITIVE ) // (v1,vt) to tie/to correlate
 KanaVerb( むすびつける, JAP_TRANSITIVE ) // (v1,vt) to combine/to join/to tie on/to attach with a knot/to bind (e.g., an address)
 KanaVerb( ゆわえる, JAP_TRANSITIVE ) // (v1,vt) to bind/to fasten/to tie up
 KanaVerb( かねそなえる, JAP_TRANSITIVE ) // (v1,vt) to have both/to combine with/(P)
 KanaVerb( きらう, JAP_TRANSITIVE ) // (v5u,vt) to hate/to dislike/to loathe/(P)
 KanaVerb( たてます, JAP_TRANSITIVE ) // (v5s,vt) to extend (building)/to build on
 KanaVerb( かけへだてる, JAP_TRANSITIVE ) // (v1,vt) to put distance between/to estrange
 KanaVerb( まきあげる, JAP_TRANSITIVE ) // (v1,vt) (1) to roll up/to hoist/to heave up/(2) to take away/(3) to blow up (dust)
 KanaVerb( まくしたてる, JAP_TRANSITIVE ) // (v1,vt) to talk on and on
 KanaVerb( あらためる, JAP_TRANSITIVE ) // (v1,vt) to change/to alter/to reform/to revise
 KanaVerb( とぎすます, JAP_TRANSITIVE ) // (v5s,vt) to sharpen/to grind/to whet/to hone/to make keen
 KanaVerb( みせびらかす, JAP_TRANSITIVE ) // (v5s,vt) to show off/to flaunt/(P)
 KanaVerb( みせる, JAP_TRANSITIVE ) // (v1,vt) to show/to display/(P)
 KanaVerb( みせかける, JAP_TRANSITIVE ) // (v1,vt) to pretend/to feign
 KanaVerb( みせつける, JAP_TRANSITIVE ) // (v1,vt) to display/to show
 KanaVerb( みちがえる, JAP_TRANSITIVE ) // (v1,vt) to be beyond recognition/to be quite a difference/(P)
 KanaVerb( みそれる, JAP_TRANSITIVE ) // (v1,vt) to overlook/to fail to recognize/to fail to recognise
 KanaVerb( みこす, JAP_TRANSITIVE ) // (v5s,vt) to anticipate/to foresee
 KanaVerb( みさげる, JAP_TRANSITIVE ) // (v1,vt) to look down over/to look down on
 KanaVerb( みさげはてる, JAP_TRANSITIVE ) // (v1,vt) to despise/to scorn/to look down on
 KanaVerb( みくだす, JAP_TRANSITIVE ) // (v5s,vt) to despise/to look down on
 KanaVerb( みおろす, JAP_TRANSITIVE ) // (v5s,vt) to overlook/to command a view of/to look down on something/(P)
 KanaVerb( みはてる, JAP_TRANSITIVE ) // (v1,vt) to see through to the finish/to be seen to the end
 KanaVerb( みすごす, JAP_TRANSITIVE ) // (v5s,vt) to let go by/to let pass/to overlook/to miss
 KanaVerb( みまわす, JAP_TRANSITIVE ) // (v5s,vt) to look around/to survey
 KanaVerb( みひらく, JAP_TRANSITIVE ) // (v5k,vt) to open one's eyes
 KanaVerb( みおぼえる, JAP_TRANSITIVE ) // (v1,vt) to remember/to recollect/to recognize/to recognise
 KanaVerb( みかける, JAP_TRANSITIVE ) // (v1,vt) to (happen to) see/to notice/to catch sight of
 KanaVerb( みまちがえる, JAP_TRANSITIVE ) // (v1,vt) to take A for B/to mistake A for B
 KanaVerb( みつめる, JAP_TRANSITIVE ) // (v1,vt) (uk) to stare at/to gaze at/to look hard at/to watch intently/to fix one's eyes on/(P)
 KanaVerb( みきわめる, JAP_TRANSITIVE ) // (v1,vt) to see through/to probe/to make sure of/(P)
 KanaVerb( みはからう, JAP_TRANSITIVE ) // (v5u,vt) to choose at one's own discretion
 KanaVerb( みかねる, JAP_TRANSITIVE ) // (v1,vt) to be unable to let pass unnoticed/to be unable to be indifferent
 KanaVerb( みこむ, JAP_TRANSITIVE ) // (v5m,vt) to anticipate/to estimate/(P)
 KanaVerb( みのこす, JAP_TRANSITIVE ) // (v5s,vt) to leave unseen or unread
 KanaVerb( みうしなう, JAP_TRANSITIVE ) // (v5u,vt) to lose sight of/to miss/(P)
 KanaVerb( みすてる, JAP_TRANSITIVE ) // (v1,vt) to abandon/to fail/to desert/(P)
 KanaVerb( みうける, JAP_TRANSITIVE ) // (v1,vt) to catch sight of/to see/to suppose/(P)
 KanaVerb( みならう, JAP_TRANSITIVE ) // (v5u,vt) to follow another's example/(P)
 KanaVerb( みいだす, JAP_TRANSITIVE ) // (v5s,vt) to find out/to discover/to notice/to select
 KanaVerb( みそめる, JAP_TRANSITIVE ) // (v1,vt) to see for the first time/to fall in love at first sight
 KanaVerb( みあげる, JAP_TRANSITIVE ) // (v1,vt) to look up at/to raise one's eyes/to admire/(P)
 KanaVerb( みすえる, JAP_TRANSITIVE ) // (v1,vt) to gaze at/to make sure of
 KanaVerb( みすます, JAP_TRANSITIVE ) // (v5s,vt) to observe carefully/to make sure
 KanaVerb( みはらす, JAP_TRANSITIVE ) // (v5s,vt) to command a view/(P)
 KanaVerb( みつくろう, JAP_TRANSITIVE ) // (v5u,vt) to choose (a thing) at one's own discretion
 KanaVerb( みそこなう, JAP_TRANSITIVE ) // (v5u,vt) to misjudge/to mistake/to miss seeing/(P)
 KanaVerb( みとおす, JAP_TRANSITIVE ) // (v5s,vt) to see without obstruction/to forecast/to predict
 KanaVerb( みさだめる, JAP_TRANSITIVE ) // (v1,vt) to make sure of/to ascertain/to confirm/to grasp
 KanaVerb( みわたす, JAP_TRANSITIVE ) // (v5s,vt) to look out over/to survey (scene)/to take an extensive view of/(P)
 KanaVerb( みのがす, JAP_TRANSITIVE ) // (v5s,vt) to miss/to overlook/to leave at large/(P)
 KanaVerb( みすかす, JAP_TRANSITIVE ) // (v5s,vt) to see through
 KanaVerb( みぬく, JAP_TRANSITIVE ) // (v5k,vt) to see through
 KanaVerb( みくらべる, JAP_TRANSITIVE ) // (v1,vt) to compare with the eye/(P)
 KanaVerb( みつけだす, JAP_TRANSITIVE ) // (v5s,vt) to find out/to discover/to locate
 KanaVerb( みつける, JAP_TRANSITIVE ) // (v1,vt) (1) to discover/to find (e.g., an error in a book)/to come across/to detect/(2) to locate/to find (e.g., something missing)/to find fault
 KanaVerb( みまう, JAP_TRANSITIVE ) // (v5u,vt) to ask after (health)/to visit/(P)
 KanaVerb( みわける, JAP_TRANSITIVE ) // (v1,vt) (1) to distinguish/to recognize/to recognise/to tell apart/to differentiate (both figuratively and visually)/(2) to identify (whether an object is positive or negative in some aspect)/to know the difference between something of superior and inferior quality (on sight or figuratively)/(P)
 KanaVerb( みかえす, JAP_TRANSITIVE ) // (v5s,vt) to look (stare) back at/to triumph over/(P)
 KanaVerb( みわすれる, JAP_TRANSITIVE ) // (v1,vt) to forget/to fail to recognize/to fail to recognise
 KanaVerb( みおとす, JAP_TRANSITIVE ) // (v5s,vt) to overlook/to fail to notice/to miss (seeing)/(P)
 KanaVerb( みはなす, JAP_TRANSITIVE ) // (v5s,vt) to desert/to abandon/to give up
 KanaVerb( みたてる, JAP_TRANSITIVE ) // (v1,vt) to choose/to select
 KanaVerb( みなす, JAP_TRANSITIVE ) // (v5s,vt) to consider as/to regard/to be deemed (as)
 KanaVerb( みとがめる, JAP_TRANSITIVE ) // (v1,vt) to find fault with/to question
 KanaVerb( みはるかす, JAP_TRANSITIVE ) // (v5s,vt) to enjoy a panoramic view
 KanaVerb( よこす, JAP_TRANSITIVE ) // (v5s,vt) (1) to send/to forward/(2) to hand over (e.g., money)
 KanaVerb( やってのける, JAP_TRANSITIVE ) // (v1,vt) to succeed (in doing)/to pull something off/to manage (to do a job)
 KanaVerb( やっつける, JAP_TRANSITIVE ) // (v1,vt) to beat/to attack (an enemy)/to do away with/to finish off
 KanaVerb( やらかす, JAP_TRANSITIVE ) // (v5s,vt) to perpetrate/to do/to be guilty of
 KanaVerb( やりすごす, JAP_TRANSITIVE ) // (v5s,vt) to do too much/to let something (or somebody) go past
 KanaVerb( やりあう, JAP_TRANSITIVE ) // (v5u,vt) to compete with/to argue with/to quarrel
 KanaVerb( やりこめる, JAP_TRANSITIVE ) // (v1,vt) to talk down
 KanaVerb( やりだす, JAP_TRANSITIVE ) // (v5s,vt) to begin
 KanaVerb( やりとげる, JAP_TRANSITIVE ) // (v1,vt) to accomplish
 KanaVerb( やりなおす, JAP_TRANSITIVE ) // (v5s,vt) to do over again/to redo/to start over/to remake/to resume/to recommence
 KanaVerb( やりぬく, JAP_TRANSITIVE ) // (v5k,vt) to carry out to completion/to accomplish
 KanaVerb( やりつける, JAP_TRANSITIVE ) // (v1,vt) to be accustomed to/to be used to/to argue into silence/to talk down
 KanaVerb( やりかえす, JAP_TRANSITIVE ) // (v5s,vt) to do over/to answer or fire back/to retort
 KanaVerb( げんきづける, JAP_TRANSITIVE ) // (v1,vt) to pep up/to cheer up
 KanaVerb( へらす, JAP_TRANSITIVE ) // (v5s,vt) to abate/to decrease/to diminish/to shorten/(P)
 KanaVerb( いいそびれる, JAP_TRANSITIVE ) // (v1,vt) to fail to mention something or tell somebody something/to miss one's chance to tell somebody something
 KanaVerb( いいちがえる, JAP_TRANSITIVE ) // (v1,vt) to say by mistake/to make a slip of the tongue
 KanaVerb( いいすぎる, JAP_TRANSITIVE ) // (v1,vt) to talk or say too much/to go too far/to overstate/to exaggerate
 KanaVerb( いいひらく, JAP_TRANSITIVE ) // (v5k,vt) to justify/to explain/to vindicate
 KanaVerb( いいかける, JAP_TRANSITIVE ) // (v1,vt) to begin speaking/to start to say/to stop in mid-sentence
 KanaVerb( いいふくめる, JAP_TRANSITIVE ) // (v1,vt) to give detailed instructions
 KanaVerb( いいつぐ, JAP_TRANSITIVE ) // (v5g,vt) to transmit by word of mouth
 KanaVerb( いいかねる, JAP_TRANSITIVE ) // (v1,vt) to find it hard to say
 KanaVerb( いいあう, JAP_TRANSITIVE ) // (v5u,vt) to quarrel
 KanaVerb( いいちらす, JAP_TRANSITIVE ) // (v5s,vt) to spread (a report)
 KanaVerb( いいのこす, JAP_TRANSITIVE ) // (v5s,vt) to leave word with (a person)/to state in one's will/to leave (something) unsaid/to forget to mention
 KanaVerb( いいすてる, JAP_TRANSITIVE ) // (v1,vt) to say (something) over one's shoulder
 KanaVerb( いいならわす, JAP_TRANSITIVE ) // (v5s,vt) to be handed down/to have a habit of saying
 KanaVerb( いいふらす, JAP_TRANSITIVE ) // (v5s,vt) to spread a rumor/to spread a rumour/to talk about
 KanaVerb( いいつくろう, JAP_TRANSITIVE ) // (v5u,vt) to gloss over
 KanaVerb( いいあらそう, JAP_TRANSITIVE ) // (v5u,vt) to quarrel/to dispute
 KanaVerb( いいたす, JAP_TRANSITIVE ) // (v5s,vt) to say something additional/to add (to what was said before)
 KanaVerb( いいかえる, JAP_TRANSITIVE ) // (v1,vt) to say in other words/to put another way/to express in different words/to reword
 KanaVerb( いいおく, JAP_TRANSITIVE ) // (v5k,vt) to leave word/to leave a message
 KanaVerb( いいなおす, JAP_TRANSITIVE ) // (v5s,vt) to correct oneself/to restate
 KanaVerb( いいとおす, JAP_TRANSITIVE ) // (v5s,vt) to persist in saying
 KanaVerb( いいそえる, JAP_TRANSITIVE ) // (v1,vt) to add (to what was said before)/to say in addition
 KanaVerb( いいつたえる, JAP_TRANSITIVE ) // (v1,vt) to send word
 KanaVerb( いいわたす, JAP_TRANSITIVE ) // (v5s,vt) to announce/to tell/to sentence/to order
 KanaVerb( いいあてる, JAP_TRANSITIVE ) // (v1,vt) to guess right
 KanaVerb( いいのがれる, JAP_TRANSITIVE ) // (v1,vt) to explain away/to talk one's way out of
 KanaVerb( いいぬける, JAP_TRANSITIVE ) // (v1,vt) to explain away/to answer evasively
 KanaVerb( いいあらわす, JAP_TRANSITIVE ) // (v5s,vt) to express (in words)
 KanaVerb( いいつける, JAP_TRANSITIVE ) // (v1,vt) to tell/to tell on (someone)/to order/to charge/to direct
 KanaVerb( ことづける, JAP_TRANSITIVE ) // (v1,vt) to send word/to send a message/(P)
 KanaVerb( いいまかす, JAP_TRANSITIVE ) // (v5s,vt) to talk (a person) down/to confute
 KanaVerb( いいふせる, JAP_TRANSITIVE ) // (v1,vt) to argue down
 KanaVerb( いいまぎらす, JAP_TRANSITIVE ) // (v5s,vt) to equivocate
 KanaVerb( いいきかせる, JAP_TRANSITIVE ) // (v1,vt) to tell someone to do something/to warn/to persuade/to instruct
 KanaVerb( いいかえす, JAP_TRANSITIVE ) // (v5s,vt) to repeat/to talk back/to answer back
 KanaVerb( いいくるめる, JAP_TRANSITIVE ) // (v1,vt) to explain away (e.g., unpleasant evidence)
 KanaVerb( いいはなつ, JAP_TRANSITIVE ) // (v5t,vt) to declare
 KanaVerb( いいよどむ, JAP_TRANSITIVE ) // (v5m,vt) to hesitate to say
 KanaVerb( いいおとす, JAP_TRANSITIVE ) // (v5s,vt) to omit/to forget to mention/to leave unspoken
 KanaVerb( いいたてる, JAP_TRANSITIVE ) // (v1,vt) to state/to insist
 KanaVerb( いいもらす, JAP_TRANSITIVE ) // (v5s,vt) to forget to mention/to leave unspoken/to let slip a secret
 KanaVerb( いいなす, JAP_TRANSITIVE ) // (v5s,vt) to speak as though something were actually the case/to smooth over/to describe
 KanaVerb( いいはやす, JAP_TRANSITIVE ) // (v5s,vt) to praise/to spread or circulate a rumor (rumour)
 KanaVerb( いいこめる, JAP_TRANSITIVE ) // (v1,vt) to talk down/to argue down
 KanaVerb( ふるす, JAP_TRANSITIVE ) // (v5s,vt) to wear out
 KanaVerb( よびさます, JAP_TRANSITIVE ) // (v5s,vt) to wake up
 KanaVerb( よびかける, JAP_TRANSITIVE ) // (v1,vt) to call out to/to accost/to address (crowd)/to appeal/(P)
 KanaVerb( よびよせる, JAP_TRANSITIVE ) // (v1,vt) to call/to summon/to send for/to call together
 KanaVerb( よびむかえる, JAP_TRANSITIVE ) // (v1,vt) to send for
 KanaVerb( よびあつめる, JAP_TRANSITIVE ) // (v1,vt) to call together/to convene
 KanaVerb( よびだす, JAP_TRANSITIVE ) // (v5s,vt) (1) to summon/to call (e.g., phone)/(2) to invoke/(P)
 KanaVerb( よびあげる, JAP_TRANSITIVE ) // (v1,vt) to call out
 KanaVerb( よびいれる, JAP_TRANSITIVE ) // (v1,vt) to call in/to invite/to bring in
 KanaVerb( よびつける, JAP_TRANSITIVE ) // (v1,vt) to summon/to get used to call
 KanaVerb( よびかえす, JAP_TRANSITIVE ) // (v5s,vt) to call back/to recall
 KanaVerb( よびもどす, JAP_TRANSITIVE ) // (v5s,vt) to call back/to call home/(P)
 KanaVerb( よびたてる, JAP_TRANSITIVE ) // (v1,vt) to call out/to ask someone to come
 KanaVerb( よびとめる, JAP_TRANSITIVE ) // (v1,vt) to challenge/to call somebody to halt
 KanaVerb( よぶ, JAP_TRANSITIVE ) // (v5b,vt) to call out/to invite/(P)
 KanaVerb( かためる, JAP_TRANSITIVE ) // (v1,vt) to harden/to freeze/to fortify/(P)
 KanaVerb( やといいれる, JAP_TRANSITIVE ) // (v1,vt) to employ/to engage
 KanaVerb( かたらう, JAP_TRANSITIVE ) // (v5u,vt) to talk/to tell/to recite/to pledge/to conspire with/(P)
 KanaVerb( かたりつぐ, JAP_TRANSITIVE ) // (v5g,vt) to transmit/to hand down
 KanaVerb( かたりあう, JAP_TRANSITIVE ) // (v5u,vt) to talk together
 KanaVerb( かたりつたえる, JAP_TRANSITIVE ) // (v1,vt) to hand down/to pass on (story or tradition)
 KanaVerb( かたりあかす, JAP_TRANSITIVE ) // (v5s,vt) to talk all the night
 KanaVerb( かどわかす, JAP_TRANSITIVE ) // (v5s,vt) to kidnap
 KanaVerb( くどく, JAP_TRANSITIVE ) // (v5k,vt) to seduce/to make a play
 KanaVerb( くちずさむ, JAP_TRANSITIVE ) // (v5m,vt) to hum/to sing to oneself/to compose impromptu (poems)
 KanaVerb( むけなおす, JAP_TRANSITIVE ) // (v5s,vt) to change direction
 KanaVerb( すきこのむ, JAP_TRANSITIVE ) // (v5m,vt) to do something by choice/to like/to be fond of
 KanaVerb( このむ, JAP_TRANSITIVE ) // (v5m,vt) to like/to prefer/(P)
 KanaVerb( ひろげる, JAP_TRANSITIVE ) // (v1,vt) to spread/to extend/to expand/to enlarge/to widen/to broaden/to unfold/to open/to unroll/(P)
 KanaVerb( ひろめる, JAP_TRANSITIVE ) // (v1,vt) to broaden/to propagate/(P)
 KanaVerb( せめぬく, JAP_TRANSITIVE ) // (v5k,vt) persistent attacking
 KanaVerb( せめほろぼす, JAP_TRANSITIVE ) // (v5s,vt) to attack and overthrow/to utterly destroy
 KanaVerb( かまえる, JAP_TRANSITIVE ) // (v1,vt) to set up/(P)
 KanaVerb( しぼりだす, JAP_TRANSITIVE ) // (v5s,vt) to squeeze or wring out
 KanaVerb( たがやす, JAP_TRANSITIVE ) // (v5s,vt) to till/to plow/to plough/to cultivate/(P)
 KanaVerb( かんがえる, JAP_TRANSITIVE ) // (v1,vt) to consider/to think about/(P)
 KanaVerb( かんがえなおす, JAP_TRANSITIVE ) // (v5s,vt) to reconsider/to rethink
 KanaVerb( かんがえつく, JAP_TRANSITIVE ) // (v5k,vt) to think of/to come up with
 KanaVerb( あらげる, JAP_TRANSITIVE ) // (v1,vt) to raise (e.g., voice)
 KanaVerb( あららげる, JAP_TRANSITIVE ) // (v1,vt) to raise (e.g., voice)/(P)
 KanaVerb( あらす, JAP_TRANSITIVE ) // (v5s,vt) (1) to lay waste/to devastate/to damage/(2) to invade/to break into/(P)
 KanaVerb( あらだてる, JAP_TRANSITIVE ) // (v1,vt) to aggravate/to make serious
 KanaVerb( ぎょうずる, JAP_TRANSITIVE ) // (vz,vt) (arch) (obsc) to perform/to do/to practice
 KanaVerb( こうずる, JAP_TRANSITIVE ) // (vz,vt) (1) to take measures/to work out a plan/(2) to lecture/to read aloud/(3) to confer/(P)
 KanaVerb( みつぐ, JAP_TRANSITIVE ) // (v5g,vt) to support/to finance
 KanaVerb( くだす, JAP_TRANSITIVE ) // (v5s,vt) to lower/to let go down
 KanaVerb( ふらす, JAP_TRANSITIVE ) // (v5s,vt) to send (rain)/to shed
 KanaVerb( ふりこめる, JAP_TRANSITIVE ) // (v1,vt) to rain (or snow), keeping people indoors
 KanaVerb( たかめる, JAP_TRANSITIVE ) // (v1,vt) to raise/to lift/to boost/to enhance/(P)
 KanaVerb( おびやかす, JAP_TRANSITIVE ) // (v5s,vt) to threaten/to coerce
 KanaVerb( きざみこむ, JAP_TRANSITIVE ) // (v5m,vt) to etch (name, etc.)/to carve (design)
 KanaVerb( きざみつける, JAP_TRANSITIVE ) // (v1,vt) to engrave/to carve out
 KanaVerb( きざむ, JAP_TRANSITIVE ) // (v5m,vt) to mince/to carve/to engrave/to cut fine/to chop up/to hash/to chisel/to notch/(P)
 KanaVerb( くろめる, JAP_TRANSITIVE ) // (v1,vt) to make something black/to talk wrong into right
 KanaVerb( うらむ, JAP_TRANSITIVE ) // (v5m,vt) to curse/to feel bitter/(P)
 KanaVerb( まぜあわせる, JAP_TRANSITIVE ) // (v1,vt) to mix
 KanaVerb( そそのかす, JAP_TRANSITIVE ) // (v5s,vt) to instigate/to tempt/(P)
 KanaVerb( さしおさえる, JAP_TRANSITIVE ) // (v1,vt) to seize/to impound/to garnish/to attach goods
 KanaVerb( さしまわす, JAP_TRANSITIVE ) // (v5s,vt) to send (a car) around
 KanaVerb( さしかける, JAP_TRANSITIVE ) // (v1,vt) to hold (umbrella) over
 KanaVerb( さしゆるす, JAP_TRANSITIVE ) // (v5s,vt) to allow/to forgive
 KanaVerb( さしはさむ, JAP_TRANSITIVE ) // (v5m,vt) (1) to insert/(2) to interrupt/to slip in a word/(3) to harbor (e.g., doubts)/to harbour/to entertain (e.g., a theory)
 KanaVerb( さしかためる, JAP_TRANSITIVE ) // (v1,vt) to close or shut tight/to warn sharply
 KanaVerb( さしかわす, JAP_TRANSITIVE ) // (v5s,vt) to cross
 KanaVerb( さしむける, JAP_TRANSITIVE ) // (v1,vt) to send or direct a person to
 KanaVerb( さしひかえる, JAP_TRANSITIVE ) // (v1,vt) to be moderate/to not do too much/(P)
 KanaVerb( さしとめる, JAP_TRANSITIVE ) // (v1,vt) to stop/to prohibit/to forbid someone to do something
 KanaVerb( さしだす, JAP_TRANSITIVE ) // (v5s,vt) to present/to submit/to tender/to hold out/(P)
 KanaVerb( さしまねく, JAP_TRANSITIVE ) // (v5k,vt) to beckon (to)
 KanaVerb( さしあげる, JAP_TRANSITIVE ) // (v1,vt) (pol) to give/to hold up/to lift up/to offer/(P)
 KanaVerb( さしおく, JAP_TRANSITIVE ) // (v5k,vt) to leave as is/to let alone/to disregard
 KanaVerb( さしいれる, JAP_TRANSITIVE ) // (v1,vt) to insert/to put in
 KanaVerb( さしつける, JAP_TRANSITIVE ) // (v1,vt) to point (gun at)/to hold under one's nose
 KanaVerb( さしもどす, JAP_TRANSITIVE ) // (v5s,vt) to send back/to refer back/(P)
 KanaVerb( さしたてる, JAP_TRANSITIVE ) // (v1,vt) to stand/to send (off)
 KanaVerb( さしのべる, JAP_TRANSITIVE ) // (v1,vt) (1) to hold out/to extend (e.g., one's hands)/to stretch/to reach out for/(2) to thrust (javelin)
 KanaVerb( もよおす, JAP_TRANSITIVE ) // (v5s,vt) to hold (a meeting)/to give (a dinner)/to feel/to show signs of/to develop symptoms of/to feel (sick)/(P)
 KanaVerb( せきとめる, JAP_TRANSITIVE ) // (v1,vt) to dam up/to hold back/to keep back/to intercept/to check
 KanaVerb( せく, JAP_TRANSITIVE ) // (v5k,vt) to dam (up) (stream)
 KanaVerb( すませる, JAP_TRANSITIVE ) // (v1,vt) to be finished/(P)
 KanaVerb( くだく, JAP_TRANSITIVE ) // (v5k,vt) to break/to smash/(P)
 KanaVerb( まつりこむ, JAP_TRANSITIVE ) // (v5m,vt) to place an obnoxious person in an out-of-the-way post to be rid of him or her
 KanaVerb( まつりあげる, JAP_TRANSITIVE ) // (v1,vt) to set up (in high position)/to kick upstairs
 KanaVerb( ほそめる, JAP_TRANSITIVE ) // (v1,vt) to make narrow
 KanaVerb( さかせる, JAP_TRANSITIVE ) // (v1,vt) to make bloom
 KanaVerb( つくりかえる, JAP_TRANSITIVE ) // (v1,vt) to remake/to remold/to remould/to convert/to reconstruct/to adapt/to parody
 KanaVerb( つくりなおす, JAP_TRANSITIVE ) // (v5s,vt) to remake/to rebuild
 KanaVerb( つくりたてる, JAP_TRANSITIVE ) // (v1,vt) to adorn/to decorate/to dress up/to build up
 KanaVerb( しぼりあげる, JAP_TRANSITIVE ) // (v1,vt) (1) to squeeze (to the utmost)/to wring/(2) to strain one's voice/(3) to scold
 KanaVerb( つぼむ, JAP_TRANSITIVE ) // (v5m,vt) to close/to shut
 KanaVerb( すぼめる, JAP_TRANSITIVE ) // (v1,vt) to make narrower/to shut (an umbrella)/to shrug (one's shoulders)/to purse (one's lips)
 KanaVerb( つぼめる, JAP_TRANSITIVE ) // (v1,vt) to make narrower/to shut (an umbrella)/to shrug (one's shoulders)/to purse (one's lips)
 KanaVerb( すりあげる, JAP_TRANSITIVE ) // (v1,vt) to finish printing/to print off
 KanaVerb( こすりつける, JAP_TRANSITIVE ) // (v1,vt) (1) to rub against/to nuzzle against, e.g., dog nosing a person/(2) to strike (a match)
 KanaVerb( なすりつける, JAP_TRANSITIVE ) // (v1,vt) to blame another
 KanaVerb( ころす, JAP_TRANSITIVE ) // (v5s,vt) to kill/(P)
 KanaVerb( まじえる, JAP_TRANSITIVE ) // (v1,vt) (1) to mix/to converse with/(2) to cross (swords)
 KanaVerb( まぜる, JAP_TRANSITIVE ) // (v1,vt) to mix/to stir/to blend
 KanaVerb( まきちらす, JAP_TRANSITIVE ) // (v5s,vt) to scatter/to spread
 KanaVerb( ちらかす, JAP_TRANSITIVE ) // (v5s,vt) to scatter around/to leave untidy/(P)
 KanaVerb( ちらす, JAP_TRANSITIVE ) // (v5s,vt) to scatter/to disperse/to distribute/(P)
 KanaVerb( ばらまく, JAP_TRANSITIVE ) // (v5k,vt) (uk) to disseminate/to scatter/to give money freely
 KanaVerb( のこす, JAP_TRANSITIVE ) // (v5s,vt) to leave (behind, over)/to bequeath/to save/to reserve/(P)
 KanaVerb( しかける, JAP_TRANSITIVE ) // (v1,vt) to commence/to lay (mines)/to set (traps)/to wage (war)/to challenge/(P)
 KanaVerb( しむける, JAP_TRANSITIVE ) // (v1,vt) to induce/to tempt/to treat/to act toward/to handle (men)/to send/to forward to
 KanaVerb( しだす, JAP_TRANSITIVE ) // (v5s,vt) to begin to do/cater
 KanaVerb( しでかす, JAP_TRANSITIVE ) // (v5s,vt) (uk) to perpetrate/to do/to finish up/to be guilty of
 KanaVerb( しあげる, JAP_TRANSITIVE ) // (v1,vt) to finish up/to complete/(P)
 KanaVerb( しとげる, JAP_TRANSITIVE ) // (v1,vt) to accomplish/to finish/to fulfill
 KanaVerb( しくむ, JAP_TRANSITIVE ) // (v5m,vt) to devise/to arrange/to plan/to plot
 KanaVerb( しそんじる, JAP_TRANSITIVE ) // (v1,vt) to blunder/to fail/to make a mistake
 KanaVerb( しそんずる, JAP_TRANSITIVE ) // (vz,vt) to blunder/to fail/to make a mistake
 KanaVerb( しかえる, JAP_TRANSITIVE ) // (v1,vt) to do over/to start anew
 KanaVerb( しいれる, JAP_TRANSITIVE ) // (v1,vt) to lay in stock/to replenish stock/to procure/(P)
 KanaVerb( しまいこむ, JAP_TRANSITIVE ) // (v5m,vt) to put away/to stow away/to tuck away/to hoard
 KanaVerb( しわける, JAP_TRANSITIVE ) // (v1,vt) to assort/to classify/to journalize (in accounting)/to journalise
 KanaVerb( したてる, JAP_TRANSITIVE ) // (v1,vt) to tailor/to make/to prepare/to train/to send (a messenger)/(P)
 KanaVerb( したてあげる, JAP_TRANSITIVE ) // (v1,vt) to be made out to be
 KanaVerb( しとめる, JAP_TRANSITIVE ) // (v1,vt) to bring down (a bird)/to kill
 KanaVerb( うかがう, JAP_TRANSITIVE ) // (v5u,vt) (1) (hum) to visit/to ask/to inquire/to hear/to be told/(v5u,vi) (2) to implore (a god for an oracle)/to seek direction (from your superior)/(P)
 KanaVerb( つかいふるす, JAP_TRANSITIVE ) // (v5s,vt) to wear out (something)
 KanaVerb( つかいこむ, JAP_TRANSITIVE ) // (v5m,vt) to embezzle/to misappropriate/to peculate/to accustom oneself to using/to use for a long time
 KanaVerb( つかいわける, JAP_TRANSITIVE ) // (v1,vt) to use properly/to use (different things) for different purposes
 KanaVerb( つかう, JAP_TRANSITIVE ) // (v5u,vt) to use/to handle/to manipulate/to employ/to need/to want/to spend/to consume/to speak (English)/to practise (fencing)/to practice (fencing)/to take (one's lunch)/to circulate (bad money)/(P)
 KanaVerb( つかわす, JAP_TRANSITIVE ) // (v5s,vt) to send/to dispatch/to despatch/(P)
 KanaVerb( さしちがえる, JAP_TRANSITIVE ) // (v1,vi,vt) to misplace/to stab at each other
 KanaVerb( さしつらぬく, JAP_TRANSITIVE ) // (v5k,vt) to pierce
 KanaVerb( さしころす, JAP_TRANSITIVE ) // (v5s,vt) to stab to death/(P)
 KanaVerb( さしとおす, JAP_TRANSITIVE ) // (v5s,vt) to stab/to pierce/to run (a sword) through
 KanaVerb( おもいすごす, JAP_TRANSITIVE ) // (v5s,vt) to think too much of/to make too much of
 KanaVerb( おもいまわす, JAP_TRANSITIVE ) // (v5s,vt) to ponder/to recall
 KanaVerb( おもいおこす, JAP_TRANSITIVE ) // (v5s,vt) to recall/to remember
 KanaVerb( おもいつめる, JAP_TRANSITIVE ) // (v1,vt) to think hard/to brood over
 KanaVerb( おもいのこす, JAP_TRANSITIVE ) // (v5s,vt) to regret
 KanaVerb( おもいだす, JAP_TRANSITIVE ) // (v5s,vt) to recall/to remember/(P)
 KanaVerb( おもいめぐらす, JAP_TRANSITIVE ) // (v5s,vt) to think over
 KanaVerb( おもいもうける, JAP_TRANSITIVE ) // (v1,vt) to anticipate/to expect
 KanaVerb( おもいしらせる, JAP_TRANSITIVE ) // (v1,vt) to have a revenge on/to get even with/to make someone realize/to make someone realise
 KanaVerb( おもいなおす, JAP_TRANSITIVE ) // (v5s,vt) to re-think/to think back upon/to change one's mind/(P)
 KanaVerb( おもいさだめる, JAP_TRANSITIVE ) // (v1,vt) to make up one's mind/to be determined
 KanaVerb( おもいなやむ, JAP_TRANSITIVE ) // (v5m,vt) to worry
 KanaVerb( おもいえがく, JAP_TRANSITIVE ) // (v5k,vt) to imagine/to picture/to figure/to see
 KanaVerb( おもいかえす, JAP_TRANSITIVE ) // (v5s,vt) to re-think/to think back upon/to change one's mind
 KanaVerb( おもいたつ, JAP_TRANSITIVE ) // (v5t,vt) to resolve
 KanaVerb( おぼしめす, JAP_TRANSITIVE ) // (v5s,vt) to develop thoughts or feelings
 KanaVerb( さししめす, JAP_TRANSITIVE ) // (v5s,vt) to indicate/to show/to point to/(P)
 KanaVerb( ゆびさす, JAP_TRANSITIVE ) // (v5s,vt) to point at/(P)
 KanaVerb( ささえる, JAP_TRANSITIVE ) // (v1,vt) to support/to prop/(P)
 KanaVerb( しはらう, JAP_TRANSITIVE ) // (v5u,vt) to pay/(P)
 KanaVerb( ほどこす, JAP_TRANSITIVE ) // (v5s,vt) to donate/to give/to conduct/to apply/to perform/(P)
 KanaVerb( よす, JAP_TRANSITIVE ) // (v5s,vt) to cease/to abolish/to resign/to give up/(P)
 KanaVerb( ためす, JAP_TRANSITIVE ) // (v5s,vt) to attempt/to test/(P)
 KanaVerb( こころみる, JAP_TRANSITIVE ) // (v1,vt) to try/to test/(P)
 KanaVerb( ことよす, JAP_TRANSITIVE ) // (v5s,vt) to find an excuse
 KanaVerb( ことよせる, JAP_TRANSITIVE ) // (v1,vt) to pretend
 KanaVerb( にせる, JAP_TRANSITIVE ) // (v1,vt) to copy/to imitate/to counterfeit/to forge/(P)
 KanaVerb( いつくしむ, JAP_TRANSITIVE ) // (v5m,vt) to love/to be affectionate to/to pity
 KanaVerb( もたせる, JAP_TRANSITIVE ) // (v1,vt) to have someone hold something/to allow someone to keep something
 KanaVerb( もちはこぶ, JAP_TRANSITIVE ) // (v5b,vt) to carry/to bring (to a place)
 KanaVerb( もちこす, JAP_TRANSITIVE ) // (v5s,vt) to carry over/to carry forward/to keep (for later)/to defer/(P)
 KanaVerb( もちかける, JAP_TRANSITIVE ) // (v1,vt) to offer a suggestion/to propose an idea
 KanaVerb( もちふるす, JAP_TRANSITIVE ) // (v5s,vt) to have long in use
 KanaVerb( もちあわせる, JAP_TRANSITIVE ) // (v1,vt) to happen to have on hand or in stock
 KanaVerb( もちこむ, JAP_TRANSITIVE ) // (v5m,vt) to lodge/to take something into ../to bring in/(P)
 KanaVerb( もちだす, JAP_TRANSITIVE ) // (v5s,vt) to take out/to carry out/to bring out from where it belongs/(P)
 KanaVerb( もちあげる, JAP_TRANSITIVE ) // (v1,vt) to raise/to lift up/to flatter
 KanaVerb( もちくずす, JAP_TRANSITIVE ) // (v5s,vt) to ruin (degrade) oneself
 KanaVerb( もてなす, JAP_TRANSITIVE ) // (v5s,vt) to entertain/to make welcome/(P)
 KanaVerb( もてあます, JAP_TRANSITIVE ) // (v5s,vt) to be too much for one/to find unmanageable/to be beyond one's control/to not know what to do with
 KanaVerb( もちこたえる, JAP_TRANSITIVE ) // (v1,vt) to hold out/(P)
 KanaVerb( もちなおす, JAP_TRANSITIVE ) // (v5s,vt) to recover/to rally/to improve/to pick up/(P)
 KanaVerb( ときめかす, JAP_TRANSITIVE ) // (v5s,vt) (uk) to beat fast (e.g., the heart)
 KanaVerb( しめしあわせる, JAP_TRANSITIVE ) // (v1,vt) to arrange beforehand/to make a sign to each other/to conspire
 KanaVerb( やめる, JAP_TRANSITIVE ) // (v1,vt) to retire/(P)
 KanaVerb( しかりとばす, JAP_TRANSITIVE ) // (v5s,vt) to rebuke strongly/to tell off
 KanaVerb( しかりつける, JAP_TRANSITIVE ) // (v1,vt) to rebuke/to scold harshly
 KanaVerb( とりおこなう, JAP_TRANSITIVE ) // (v5u,vt) to hold a ceremony
 KanaVerb( うしなう, JAP_TRANSITIVE ) // (v5u,vt) to lose/to part with/(P)
 KanaVerb( しめす, JAP_TRANSITIVE ) // (v5s,vt) to wet/to moisten/to dampen
 KanaVerb( うつしだす, JAP_TRANSITIVE ) // (v5s,vt) to reflect/to reveal/to show
 KanaVerb( うつす, JAP_TRANSITIVE ) // (v5s,vt) (1) to transcribe/to duplicate/to reproduce/to imitate/to trace/(2) to describe/(3) to film/to picture/to photograph/(P)
 KanaVerb( いかける, JAP_TRANSITIVE ) // (v1,vt) to shoot or fire off an arrow
 KanaVerb( いとめる, JAP_TRANSITIVE ) // (v1,vt) to shoot dead/to make something one's own/(P)
 KanaVerb( いとおす, JAP_TRANSITIVE ) // (v5s,vt) to pierce/to penetrate
 KanaVerb( いかえす, JAP_TRANSITIVE ) // (v5s,vt) to return fire/to shoot back
 KanaVerb( いすくめる, JAP_TRANSITIVE ) // (v1,vt) to pin the enemy down/to glare another down (and render impotent)
 KanaVerb( すてる, JAP_TRANSITIVE ) // (v1,vt) to throw away/to cast aside/to abandon/to resign/(P)
 KanaVerb( すておく, JAP_TRANSITIVE ) // (v5k,vt) to leave as is/to ignore
 KanaVerb( にる, JAP_TRANSITIVE ) // (v1,vt) to boil/to cook/(P)
 KanaVerb( につめる, JAP_TRANSITIVE ) // (v1,vt) to boil down/to concentrate/(P)
 KanaVerb( にだす, JAP_TRANSITIVE ) // (v5s,vt) to boil down/to extract
 KanaVerb( にしめる, JAP_TRANSITIVE ) // (v1,vt) to boil down
 KanaVerb( につける, JAP_TRANSITIVE ) // (v1,vt) to cook hard
 KanaVerb( にかえす, JAP_TRANSITIVE ) // (v5s,vt) to warm over
 KanaVerb( にたてる, JAP_TRANSITIVE ) // (v1,vt) to boil or simmer
 KanaVerb( かりる, JAP_TRANSITIVE ) // (v1,vt) to borrow/to have a loan/to hire/to rent/to buy on credit/(P)
 KanaVerb( かりかえる, JAP_TRANSITIVE ) // (v1,vt) to convert (a loan)
 KanaVerb( かりうける, JAP_TRANSITIVE ) // (v1,vt) to borrow/to have a loan/to hire/to rent/to buy on credit
 KanaVerb( かりたおす, JAP_TRANSITIVE ) // (v5s,vt) to evade payment
 KanaVerb( かりいれる, JAP_TRANSITIVE ) // (v1,vt) to borrow/to rent/to lease/to charter
 KanaVerb( かりあげる, JAP_TRANSITIVE ) // (v1,vt) to hire/to lease/to requisition/to charter
 KanaVerb( よわめる, JAP_TRANSITIVE ) // (v1,vt) to weaken/(P)
 KanaVerb( とりあつかう, JAP_TRANSITIVE ) // (v5u,vt) to treat/to handle/to deal in/(P)
 KanaVerb( とれる, JAP_TRANSITIVE ) // (v1,vi,vt) to come off/to be taken off/to be removed/to be obtained/to leave/to come out (e.g., photo)/to be interpreted/(P)
 KanaVerb( とりかこむ, JAP_TRANSITIVE ) // (v5m,vt) to surround/to crowd around
 KanaVerb( とりちがえる, JAP_TRANSITIVE ) // (v1,vt) to take by mistake
 KanaVerb( とりはこぶ, JAP_TRANSITIVE ) // (v5b,vt) to proceed smoothly
 KanaVerb( とりさげる, JAP_TRANSITIVE ) // (v1,vt) to withdraw/to abandon (e.g., a lawsuit)
 KanaVerb( とりまわす, JAP_TRANSITIVE ) // (v5s,vt) to rotate in one's hands/to treat/to manage/to dispose of
 KanaVerb( とりはずす, JAP_TRANSITIVE ) // (v5s,vt) to dismantle/to demount/to take something away/to detach
 KanaVerb( とりまく, JAP_TRANSITIVE ) // (v5k,vt) to surround/to circle/to enclose
 KanaVerb( とりよせる, JAP_TRANSITIVE ) // (v1,vt) to order/to send away for
 KanaVerb( とりはからう, JAP_TRANSITIVE ) // (v5u,vt) to manage/to settle/to dispose of/to deal with/to arrange
 KanaVerb( とりきめる, JAP_TRANSITIVE ) // (v1,vt) to agree/to decide upon/to enter into (a contract)
 KanaVerb( とりむすぶ, JAP_TRANSITIVE ) // (v5b,vt) to tie up/conclude
 KanaVerb( とりひろげる, JAP_TRANSITIVE ) // (v1,vt) to enlarge/to widen/to spread out
 KanaVerb( とりまぜる, JAP_TRANSITIVE ) // (v1,vt) to mix/to put together
 KanaVerb( とりころす, JAP_TRANSITIVE ) // (v5s,vt) to haunt to death/to possess and kill
 KanaVerb( とりさばく, JAP_TRANSITIVE ) // (v5k,vt) to settle (a matter)
 KanaVerb( とりちらす, JAP_TRANSITIVE ) // (v5s,vt) to scatter about
 KanaVerb( とりのこす, JAP_TRANSITIVE ) // (v5s,vt) to leave behind
 KanaVerb( とりやめる, JAP_TRANSITIVE ) // (v1,vt) to cancel/to call off
 KanaVerb( とりもつ, JAP_TRANSITIVE ) // (v5t,vt) to mediate/to entertain/to serve
 KanaVerb( とりすてる, JAP_TRANSITIVE ) // (v1,vt) to throw away
 KanaVerb( とりあつめる, JAP_TRANSITIVE ) // (v1,vt) to gather/to collect
 KanaVerb( とりだす, JAP_TRANSITIVE ) // (v5s,vt) (1) to take out/to produce/to pick out/(2) to fetch/to retrieve
 KanaVerb( とりのぞく, JAP_TRANSITIVE ) // (v5k,vt) to remove/to deinstall/to take away/to set apart
 KanaVerb( とりけす, JAP_TRANSITIVE ) // (v5s,vt) to cancel
 KanaVerb( とりあげる, JAP_TRANSITIVE ) // (v1,vt) to take up/to pick up/to disqualify/to confiscate/to deprive/(P)
 KanaVerb( とりなす, JAP_TRANSITIVE ) // (v5s,vt) to mediate/to intervene/to smooth
 KanaVerb( とりつくろう, JAP_TRANSITIVE ) // (v5u,vt) to temporize/to temporise/to smooth over
 KanaVerb( とりそろえる, JAP_TRANSITIVE ) // (v1,vt) to assemble of goods (into a set)/to gather/to put together
 KanaVerb( とりそこなう, JAP_TRANSITIVE ) // (v5u,vt) to miss/to fail to capitalize/to fail to capitalise
 KanaVerb( とりかえる, JAP_TRANSITIVE ) // (v1,vt) to exchange/to replace
 KanaVerb( とりしらべる, JAP_TRANSITIVE ) // (v1,vt) to investigate/to examine
 KanaVerb( とりなおす, JAP_TRANSITIVE ) // (v5s,vt) (1) to re-grip/to re-wrestle (sumo)/(2) to regroup (after some adverse event)
 KanaVerb( とりしずめる, JAP_TRANSITIVE ) // (v1,vt) to quell/to quiet
 KanaVerb( とりまとめる, JAP_TRANSITIVE ) // (v1,vt) to collect/to arrange/to settle
 KanaVerb( とりにがす, JAP_TRANSITIVE ) // (v5s,vt) to miss (capturing)/to fail to catch/to let slip
 KanaVerb( とりいれる, JAP_TRANSITIVE ) // (v1,vt) (1) to harvest/to reap/(2) to take in/togather in/(3) to adopt
 KanaVerb( とりつける, JAP_TRANSITIVE ) // (v1,vt) to furnish/to install/to get someone's agreement
 KanaVerb( とりはらう, JAP_TRANSITIVE ) // (v5u,vt) to clear away/to remove/to demolish
 KanaVerb( とりわける, JAP_TRANSITIVE ) // (v1,vt) to distribute/to apportion/to divide
 KanaVerb( とりかたづける, JAP_TRANSITIVE ) // (v1,vt) to clean up/to clear away/to put in order
 KanaVerb( とりかえす, JAP_TRANSITIVE ) // (v5s,vt) to regain/to recover/to get back
 KanaVerb( とりくずす, JAP_TRANSITIVE ) // (v5s,vt) to demolish/to take away until nothing remains
 KanaVerb( とりもどす, JAP_TRANSITIVE ) // (v5s,vt) to take back/to regain
 KanaVerb( とりおさえる, JAP_TRANSITIVE ) // (v1,vt) (1) to seize/to capture/to arrest/(2) to hold down/to subdue
 KanaVerb( とりはなす, JAP_TRANSITIVE ) // (v5s,vt) to release/to let go (of)
 KanaVerb( とりたてる, JAP_TRANSITIVE ) // (v1,vt) to collect/to extort/to appoint/to promote
 KanaVerb( とりとめる, JAP_TRANSITIVE ) // (v1,vt) to stop/to put a stop to/to check
 KanaVerb( とりこわす, JAP_TRANSITIVE ) // (v5s,vt) to demolish/to tear or pull down
 KanaVerb( とりひしぐ, JAP_TRANSITIVE ) // (v5g,vt) to crush
 KanaVerb( まもりぬく, JAP_TRANSITIVE ) // (v5k,vt) to hold fast/to protect to the end
 KanaVerb( もりたてる, JAP_TRANSITIVE ) // (v1,vt) to bring up/to support/to rally
 KanaVerb( てなずける, JAP_TRANSITIVE ) // (v1,vt) to tame/to win over
 KanaVerb( たぐりこむ, JAP_TRANSITIVE ) // (v5m,vt) to reel in
 KanaVerb( てびかえる, JAP_TRANSITIVE ) // (v1,vt) (1) to hang (hold) back/to hold off/to refrain/to reduce or cut back on/(2) to jot down a note
 KanaVerb( てつだう, JAP_TRANSITIVE ) // (v5u,vt) to help/to assist/to take part in/(P)
 KanaVerb( てわたす, JAP_TRANSITIVE ) // (v5s,vt) to hand over/to surrender/(P)
 KanaVerb( てばなす, JAP_TRANSITIVE ) // (v5s,vt) to release/to relinquish/to sell/to part with/to send away
 KanaVerb( かりだす, JAP_TRANSITIVE ) // (v5s,vt) to hunt out/to round up
 KanaVerb( かりあつめる, JAP_TRANSITIVE ) // (v1,vt) to round up/to gather/to muster/to mobilize/to mobilise
 KanaVerb( うけつぐ, JAP_TRANSITIVE ) // (v5g,vt) to inherit/to succeed/to take over/(P)
 KanaVerb( うけとめる, JAP_TRANSITIVE ) // (v1,vt) to catch/to stop the blow/to react to/to take/(P)
 KanaVerb( うけもつ, JAP_TRANSITIVE ) // (v5t,vt) to take (be in) charge of/(P)
 KanaVerb( うけつける, JAP_TRANSITIVE ) // (v1,vt) to be accepted/to receive (an application)/(P)
 KanaVerb( うけながす, JAP_TRANSITIVE ) // (v5s,vt) to ward off/to elude/to turn aside (a joke)
 KanaVerb( うけいれる, JAP_TRANSITIVE ) // (v1,vt) to accept/to receive
 KanaVerb( のろう, JAP_TRANSITIVE ) // (v5u,vt) to curse/to put a curse on/(P)
 KanaVerb( ことぶく, JAP_TRANSITIVE ) // (v5k,vt) to congratulate/to wish one well
 KanaVerb( ことほぐ, JAP_TRANSITIVE ) // (v5g,vt) to congratulate/to wish one well
 KanaVerb( さずける, JAP_TRANSITIVE ) // (v1,vt) to grant/to award/to teach/(P)
 KanaVerb( ひろいだす, JAP_TRANSITIVE ) // (v5s,vt) to single out/to select
 KanaVerb( ひろう, JAP_TRANSITIVE ) // (v5u,vt) to pick up/to find/to gather/(P)
 KanaVerb( ならう, JAP_TRANSITIVE ) // (v5u,vt) to learn/(P)
 KanaVerb( ならわす, JAP_TRANSITIVE ) // (v5s,vt) to make (someone) learn
 KanaVerb( おそう, JAP_TRANSITIVE ) // (v5u,vt) to attack/(P)
 KanaVerb( けこむ, JAP_TRANSITIVE ) // (v5m,vt) to kick in(to)/to sustain a loss
 KanaVerb( けちらす, JAP_TRANSITIVE ) // (v5s,vt) to kick about
 KanaVerb( けだす, JAP_TRANSITIVE ) // (v5s,vt) to kick out/to cut back (on spending)
 KanaVerb( けあげる, JAP_TRANSITIVE ) // (v1,vt) to kick up
 KanaVerb( けたおす, JAP_TRANSITIVE ) // (v5s,vt) to kick over or down
 KanaVerb( けとばす, JAP_TRANSITIVE ) // (v5s,vt) to kick away/to kick off/to kick (someone)/to refuse/to reject
 KanaVerb( けかえす, JAP_TRANSITIVE ) // (v5s,vt) to kick back
 KanaVerb( けおとす, JAP_TRANSITIVE ) // (v5s,vt) to kick down/to defeat
 KanaVerb( けたてる, JAP_TRANSITIVE ) // (v1,vt) to kick up
 KanaVerb( あつめる, JAP_TRANSITIVE ) // (v1,vt) to collect/to assemble/(P)
 KanaVerb( すみあらす, JAP_TRANSITIVE ) // (v5s,vt) to leave a house in bad shape
 KanaVerb( すみかえる, JAP_TRANSITIVE ) // (v1,vt) to change one's residence
 KanaVerb( あてがう, JAP_TRANSITIVE ) // (v5u,vt) (1) to allot/to allocate/(2) to supply with/to furnish/(3) to fit to/to fasten to/to apply to
 KanaVerb( したがえる, JAP_TRANSITIVE ) // (v1,vt) (1) to be accompanied by/(2) to subdue/(P)
 KanaVerb( かさねる, JAP_TRANSITIVE ) // (v1,vt) to pile up/to put something on another/to heap up/to add/to repeat/(P)
 KanaVerb( おもんじる, JAP_TRANSITIVE ) // (v1,vt) to respect/to honor/to honour/to esteem/to prize/(P)
 KanaVerb( おもんずる, JAP_TRANSITIVE ) // (vz,vt) to honor/to honour/to respect/to esteem/to prize/(P)
 KanaVerb( いわう, JAP_TRANSITIVE ) // (v5u,vt) to congratulate/to celebrate/(P)
 KanaVerb( ちぢめる, JAP_TRANSITIVE ) // (v1,vt) to shorten/to reduce/to boil down/to shrink/(P)
 KanaVerb( ちぢらす, JAP_TRANSITIVE ) // (v5s,vt) to curl/to crimp
 KanaVerb( こなす, JAP_TRANSITIVE ) // (v5s,vt) to break to pieces/to digest/to handle easily/(P)
 KanaVerb( じゅくす, JAP_TRANSITIVE ) // (v5s,vt) to ripen/to mature
 KanaVerb( だしあう, JAP_TRANSITIVE ) // (v5u,vt) to contribute jointly
 KanaVerb( だしおしむ, JAP_TRANSITIVE ) // (v5m,vt) to grudge/to be stingy/to be unwilling to pay
 KanaVerb( だしぬく, JAP_TRANSITIVE ) // (v5k,vt) to forestall/to anticipate/to jump the gun on/to outwit/to circumvent/to steal a march on
 KanaVerb( でむかえる, JAP_TRANSITIVE ) // (v1,vt) to meet/to greet/(P)
 KanaVerb( でかす, JAP_TRANSITIVE ) // (v5s,vt) to do/to commit/to accomplish/to achieve
 KanaVerb( のべる, JAP_TRANSITIVE ) // (v1,vt) to state/to express/to mention/(P)
 KanaVerb( またたく, JAP_TRANSITIVE ) // (v5k,vt) to wink/to waver/to twinkle/(P)
 KanaVerb( まばたく, JAP_TRANSITIVE ) // (v5k,vt) to wink/to blink
 KanaVerb( なぞらえる, JAP_TRANSITIVE ) // (v1,vt) to pattern after/to liken to/to imitate/(P)
 KanaVerb( ふやかす, JAP_TRANSITIVE ) // (v5s,vt) (uk) to soak/to steep/to macerate
 KanaVerb( うるおす, JAP_TRANSITIVE ) // (v5s,vt) to moisten/to wet/profit/to enrich/to benefit/(P)
 KanaVerb( めぐらす, JAP_TRANSITIVE ) // (v5s,vt) to enclose (with)/to surround (with)/to encircle/to think over/to work out
 KanaVerb( じゅんじょたてる, JAP_TRANSITIVE ) // (v1,vt) to put into order/to arrange (one's thoughts)
 KanaVerb( かきくだす, JAP_TRANSITIVE ) // (v5s,vt) to write down
 KanaVerb( かきくわえる, JAP_TRANSITIVE ) // (v1,vt) to add (e.g., a postscript)
 KanaVerb( かきあらためる, JAP_TRANSITIVE ) // (v1,vt) to rewrite/to adapt (e.g., a novel)
 KanaVerb( かきしるす, JAP_TRANSITIVE ) // (v5s,vt) to write down/to record/to register
 KanaVerb( かきのこす, JAP_TRANSITIVE ) // (v5s,vt) to leave a note or document behind/to leave half-written/to leave out
 KanaVerb( かきうつす, JAP_TRANSITIVE ) // (v5s,vt) to transcribe
 KanaVerb( かきすてる, JAP_TRANSITIVE ) // (v1,vt) to write and throw away/to write carelessly/to begin writing then stop part-way through
 KanaVerb( かきつづける, JAP_TRANSITIVE ) // (v1,vt) to continue writing
 KanaVerb( かきなおす, JAP_TRANSITIVE ) // (v5s,vt) to write out/to make a fair copy/(P)
 KanaVerb( かきつたえる, JAP_TRANSITIVE ) // (v1,vt) to record for transmission to posterity
 KanaVerb( かきぬく, JAP_TRANSITIVE ) // (v5k,vt) to extract
 KanaVerb( かきとばす, JAP_TRANSITIVE ) // (v5s,vt) to write (dash) off
 KanaVerb( かきあらわす, JAP_TRANSITIVE ) // (v5s,vt) (1) to write out/to express/to describe/(2) to publish
 KanaVerb( かきならべる, JAP_TRANSITIVE ) // (v1,vt) to line up points in a speech
 KanaVerb( かきながす, JAP_TRANSITIVE ) // (v5s,vt) to write off
 KanaVerb( かきとどめる, JAP_TRANSITIVE ) // (v1,vt) to write down/to leave a note behind/to record/to chronicle
 KanaVerb( かきとめる, JAP_TRANSITIVE ) // (v1,vt) to write down/to leave a note behind/to record/to chronicle
 KanaVerb( かきつらねる, JAP_TRANSITIVE ) // (v1,vt) to make a list/to enumerate
 KanaVerb( かきもらす, JAP_TRANSITIVE ) // (v5s,vt) leave out/forget to write
 KanaVerb( かきかえる, JAP_TRANSITIVE ) // (v1,vt) to rewrite/to overwrite/to renew/to transfer
 KanaVerb( かきちらす, JAP_TRANSITIVE ) // (v5s,vt) to scribble/to scrawl
 KanaVerb( かきそえる, JAP_TRANSITIVE ) // (v1,vt) to add/to write a postscript
 KanaVerb( すきかえす, JAP_TRANSITIVE ) // (v5s,vt) to plow (up)/to plough (up)
 KanaVerb( つぐなう, JAP_TRANSITIVE ) // (v5u,vt) to make up for/to recompense/to redeem (one's faults)/to compensate for/to indemnify/to atone for/(P)
 KanaVerb( かちえる, JAP_TRANSITIVE ) // (v1,vt) to achieve/to win/to gain/to attain
 KanaVerb( めしよせる, JAP_TRANSITIVE ) // (v1,vt) to call (someone) to you/to call together/to call to come
 KanaVerb( めしだす, JAP_TRANSITIVE ) // (v5s,vt) to call out/to summon
 KanaVerb( めしあげる, JAP_TRANSITIVE ) // (v1,vt) to forfeit/to confiscate/to call out
 KanaVerb( めしいれる, JAP_TRANSITIVE ) // (v1,vt) to call in
 KanaVerb( めしかかえる, JAP_TRANSITIVE ) // (v1,vt) to employ/to engage
 KanaVerb( めしつれる, JAP_TRANSITIVE ) // (v1,vt) to bring along/to accompany
 KanaVerb( めす, JAP_TRANSITIVE ) // (v5s,vt) (1) to call/to send for/(2) to put on/to wear/to take (a bath)/to ride in/to buy/to eat/to drink/to catch (a cold)/(P)
 KanaVerb( めしつかう, JAP_TRANSITIVE ) // (v5u,vt) to hire a servant
 KanaVerb( あきなう, JAP_TRANSITIVE ) // (v5u,vt) (1) to sell/(2) to handle/to trade in
 KanaVerb( こづく, JAP_TRANSITIVE ) // (v5k,vt) to poke/to push
 KanaVerb( まねく, JAP_TRANSITIVE ) // (v5k,vt) to invite/(P)
 KanaVerb( けしとめる, JAP_TRANSITIVE ) // (v1,vt) to put out/to extinguish
 KanaVerb( けす, JAP_TRANSITIVE ) // (v5s,vt) (1) to erase/to delete/(2) to turn off power/(3) to bump off (sl)/(P)
 KanaVerb( やきすてる, JAP_TRANSITIVE ) // (v1,vt) to burn up
 KanaVerb( やきあげる, JAP_TRANSITIVE ) // (v1,vt) to burn/to roast/to grill/to bake
 KanaVerb( やきなおす, JAP_TRANSITIVE ) // (v5s,vt) to grill again/to rehash
 KanaVerb( やきはらう, JAP_TRANSITIVE ) // (v5u,vt) to clear away by burning/to reduce to ashes
 KanaVerb( くべる, JAP_TRANSITIVE ) // (v1,vt) to throw on the fire/to burn
 KanaVerb( やきつける, JAP_TRANSITIVE ) // (v1,vt) to bake/to plate/to print/to burn or bake into/to burn into one's memory
 KanaVerb( こがす, JAP_TRANSITIVE ) // (v5s,vt) to burn/to scorch/to singe/to char/(P)
 KanaVerb( てらす, JAP_TRANSITIVE ) // (v5s,vt) to shine on/to illuminate/(P)
 KanaVerb( はぶく, JAP_TRANSITIVE ) // (v5k,vt) to omit/to eliminate/to curtail/to economize/to economise/(P)
 KanaVerb( かえりみる, JAP_TRANSITIVE ) // (v1,vt) to reflect/(P)
 KanaVerb( となえる, JAP_TRANSITIVE ) // (v1,vt) to assume the name of
 KanaVerb( わらいとばす, JAP_TRANSITIVE ) // (v5s,vt) to laugh at
 KanaVerb( しょうこだてる, JAP_TRANSITIVE ) // (v1,vt) to prove/to substantiate
 KanaVerb( のせる, JAP_TRANSITIVE ) // (v1,vt) to place on (something)/to take on board/to give a ride/to let (one) take part/to impose on/to record/to mention/to load (luggage)/to publish/to run (an ad)/(P)
 KanaVerb( のっける, JAP_TRANSITIVE ) // (v1,vt) to place (something) on (something)
 KanaVerb( のりかける, JAP_TRANSITIVE ) // (v1,vt) to be about to board/to be riding on/to get on top of/to lean over/to set about/to collide with
 KanaVerb( のりつぐ, JAP_TRANSITIVE ) // (v5g,vt) to change
 KanaVerb( のりすてる, JAP_TRANSITIVE ) // (v1,vt) to get off/to abandon (a ship or vehicle)
 KanaVerb( のりだす, JAP_TRANSITIVE ) // (v5s,vt) (1) to set out/to set sail/(2) to embark on/to begin to ride/(3) to lean forward/(P)
 KanaVerb( のりあげる, JAP_TRANSITIVE ) // (v1,vt) to run aground/to be stranded
 KanaVerb( のりかえる, JAP_TRANSITIVE ) // (v1,vt) to transfer (trains)/to change (bus, train)
 KanaVerb( のりならす, JAP_TRANSITIVE ) // (v5s,vt) to break in (a horse)
 KanaVerb( のりいれる, JAP_TRANSITIVE ) // (v1,vt) to ride into (a place)/to drive into (a place)/extend (a line into a city)
 KanaVerb( のりこす, JAP_TRANSITIVE ) // (v5s,vt) to ride past/to pass/to outdistance/(P)
 KanaVerb( のりまわす, JAP_TRANSITIVE ) // (v5s,vt) to drive (a car) around/to ride (a bicycle) around/(P)
 KanaVerb( たたみかける, JAP_TRANSITIVE ) // (v1,vt) (uk) to press for an answer/to shower questions on someone
 KanaVerb( たたみこむ, JAP_TRANSITIVE ) // (v5m,vt) to fold in/to bear deep in mind/to follow up
 KanaVerb( たたむ, JAP_TRANSITIVE ) // (v5m,vt) to fold (clothes)/(P)
 KanaVerb( むしかえす, JAP_TRANSITIVE ) // (v5s,vt) to reheat/to steam over/to bring up again/to take up again a problem that has been dealt with/(P)
 KanaVerb( むす, JAP_TRANSITIVE ) // (v5s,vt) to steam/to poultice/to be sultry/(P)
 KanaVerb( むらす, JAP_TRANSITIVE ) // (v5s,vt) to cook by steam
 KanaVerb( ゆずりあう, JAP_TRANSITIVE ) // (v5u,vt) to give and take/to make mutual concessions/to compromise
 KanaVerb( ゆずりうける, JAP_TRANSITIVE ) // (v1,vt) to inherit/to receive/to take over by transfer
 KanaVerb( ゆずりわたす, JAP_TRANSITIVE ) // (v5s,vt) to hand over/to turn over/to cede/(P)
 KanaVerb( かもしだす, JAP_TRANSITIVE ) // (v5s,vt) to engender/to bring about
 KanaVerb( かもす, JAP_TRANSITIVE ) // (v5s,vt) to brew/to cause/to give rise to/to distill
 KanaVerb( かざりつける, JAP_TRANSITIVE ) // (v1,vt) to decorate/to display
 KanaVerb( かざりたてる, JAP_TRANSITIVE ) // (v1,vt) to decorate gaudily/to deck out
 KanaVerb( ぬぐう, JAP_TRANSITIVE ) // (v5u,vt) to wipe/(P)
 KanaVerb( うえこむ, JAP_TRANSITIVE ) // (v5m,vt) to plant
 KanaVerb( うえつける, JAP_TRANSITIVE ) // (v1,vt) to plant
 KanaVerb( おりだす, JAP_TRANSITIVE ) // (v5s,vt) to weave a pattern/to begin to weave
 KanaVerb( おりあげる, JAP_TRANSITIVE ) // (v1,vt) to weave up into fabric
 KanaVerb( おりなす, JAP_TRANSITIVE ) // (v5s,vt) to interweave
 KanaVerb( ふれこむ, JAP_TRANSITIVE ) // (v5m,vt) to announce/to pretend to be/to pass off for/to pose as/to herald
 KanaVerb( くいつめる, JAP_TRANSITIVE ) // (v1,vt) to go broke
 KanaVerb( くいあらす, JAP_TRANSITIVE ) // (v5s,vt) to devour/to work at various things/to eat some of everything
 KanaVerb( くいころす, JAP_TRANSITIVE ) // (v5s,vt) to devour/to bite to death
 KanaVerb( くいちらす, JAP_TRANSITIVE ) // (v5s,vt) to eat untidily/to eat a bit of everything
 KanaVerb( くいつぶす, JAP_TRANSITIVE ) // (v5s,vt) to run through one's fortune in idleness
 KanaVerb( くいたおす, JAP_TRANSITIVE ) // (v5s,vt) to bilk/to eat up one's fortune
 KanaVerb( くう, JAP_TRANSITIVE ) // (v5u,vt) (male) (vulg) to eat/(P)
 KanaVerb( たべよごす, JAP_TRANSITIVE ) // (v5s,vt) to eat messily
 KanaVerb( たべすぎる, JAP_TRANSITIVE ) // (v1,vt) to overeat/(P)
 KanaVerb( たべのこす, JAP_TRANSITIVE ) // (v5s,vt) to leave a dish half-eaten
 KanaVerb( たべつける, JAP_TRANSITIVE ) // (v1,vt) to be used to eating
 KanaVerb( くらう, JAP_TRANSITIVE ) // (v5u,vt) to eat/to drink/to receive (blow)/(P)
 KanaVerb( くらわせる, JAP_TRANSITIVE ) // (v1,vt) (1) to make someone eat/(2) to deal (a blow)/to play (a trick)
 KanaVerb( くわせる, JAP_TRANSITIVE ) // (v1,vt) (1) to feed/(2) to provide/(3) to inflict/(4) to cheat
 KanaVerb( くいとめる, JAP_TRANSITIVE ) // (v1,vt) to check/to hold back/(P)
 KanaVerb( はずかしめる, JAP_TRANSITIVE ) // (v1,vt) to put to shame
 KanaVerb( のしあげる, JAP_TRANSITIVE ) // (v1,vt) to promote/to make richer
 KanaVerb( のばす, JAP_TRANSITIVE ) // (v5s,vt) to lengthen/to stretch/to reach out/to postpone/to prolong/to extend/to grow (beard)/(P)
 KanaVerb( のべひろげる, JAP_TRANSITIVE ) // (v1,vt) to stretch out
 KanaVerb( しんじる, JAP_TRANSITIVE ) // (v1,vt) to believe/to believe in/to place trust in/to confide in/to have faith in/(P)
 KanaVerb( ねかしつける, JAP_TRANSITIVE ) // (v1,vt) to lull (a child) to sleep/to put a person to sleep
 KanaVerb( ねかせる, JAP_TRANSITIVE ) // (v1,vt) to put to bed/to lay down/to ferment/(P)
 KanaVerb( こころがける, JAP_TRANSITIVE ) // (v1,vt) to bear in mind/to aim to do/(P)
 KanaVerb( こころえる, JAP_TRANSITIVE ) // (v1,vt) to be informed/to have thorough knowledge/(P)
 KanaVerb( つつしむ, JAP_TRANSITIVE ) // (v5m,vt) to be careful/to be chaste or discreet/to abstain or refrain/(P)
 KanaVerb( ふりほどく, JAP_TRANSITIVE ) // (v5k,vt) to shake and untangle
 KanaVerb( ふりまわす, JAP_TRANSITIVE ) // (v5s,vt) to wield/to brandish/to flourish/to wave (about)/to swing/to display/to show off/to abuse/(P)
 KanaVerb( ふりかける, JAP_TRANSITIVE ) // (v1,vt) to sprinkle (salt, pepper) over
 KanaVerb( ふりむける, JAP_TRANSITIVE ) // (v1,vt) to turn
 KanaVerb( ふりまく, JAP_TRANSITIVE ) // (v5k,vt) to scatter/to sprinkle/to lavish
 KanaVerb( ふりすてる, JAP_TRANSITIVE ) // (v1,vt) to shake off/forsake
 KanaVerb( ふりだす, JAP_TRANSITIVE ) // (v5s,vt) to shake and give/to start shaking/to shake out/to write (draw on) a check (cheque)
 KanaVerb( ふりあげる, JAP_TRANSITIVE ) // (v1,vt) to raise overhead
 KanaVerb( ふりあてる, JAP_TRANSITIVE ) // (v1,vt) to assign/to allot
 KanaVerb( ふりはらう, JAP_TRANSITIVE ) // (v5u,vt) to shake off
 KanaVerb( ふりわける, JAP_TRANSITIVE ) // (v1,vt) to partition out/to divide among
 KanaVerb( ふりはなす, JAP_TRANSITIVE ) // (v5s,vt) to break free of
 KanaVerb( ふりおとす, JAP_TRANSITIVE ) // (v5s,vt) to shake off/to throw off
 KanaVerb( ふりみだす, JAP_TRANSITIVE ) // (v5s,vt) to dishevel (hair)
 KanaVerb( ふりたてる, JAP_TRANSITIVE ) // (v1,vt) to toss (i.e. one's head)/to wave (i.e. a flag)/to stand up energetically/to raise one's voice
 KanaVerb( ふりかざす, JAP_TRANSITIVE ) // (v5s,vt) to brandish (sword) over one's head
 KanaVerb( ふるまう, JAP_TRANSITIVE ) // (v5u,vt) to behave/to conduct oneself/to entertain
 KanaVerb( ひたす, JAP_TRANSITIVE ) // (v5s,vt) to soak/to dip/to drench/(P)
 KanaVerb( ふかめる, JAP_TRANSITIVE ) // (v1,vt) to deepen/to heighten/to intensify/(P)
 KanaVerb( もうしこす, JAP_TRANSITIVE ) // (v5s,vt) to send word to/to write to
 KanaVerb( もうしうける, JAP_TRANSITIVE ) // (v1,vt) to accept/to ask for/to charge (a price)
 KanaVerb( もうしでる, JAP_TRANSITIVE ) // (v1,vt) to report to/to tell/to suggest/to submit/to request/to make an offer/to come forward with information/(P)
 KanaVerb( もうしあげる, JAP_TRANSITIVE ) // (v1,vt) to say/to tell/to state/(P)
 KanaVerb( もうしそえる, JAP_TRANSITIVE ) // (v1,vt) to add to what has been said
 KanaVerb( もうしわたす, JAP_TRANSITIVE ) // (v5s,vt) to tell/to announce/to declare/to order
 KanaVerb( もうしいれる, JAP_TRANSITIVE ) // (v1,vt) to propose/to suggest/(P)
 KanaVerb( もうしつける, JAP_TRANSITIVE ) // (v1,vt) to order/to instruct
 KanaVerb( もうしきかせる, JAP_TRANSITIVE ) // (v1,vt) to tell/to talk to
 KanaVerb( もうしたてる, JAP_TRANSITIVE ) // (v1,vt) to declare/to plead
 KanaVerb( もうす, JAP_TRANSITIVE ) // (v5s,vt) (hum) to be called/to say/(P)
 KanaVerb( もうしこむ, JAP_TRANSITIVE ) // (v5m,vt) to apply for/to make an application/to propose (marriage)/to offer (mediation)/to make an overture (of peace)/to challenge/to lodge (objections)/to request (an interview)/to subscribe for/to book/to reserve
 KanaVerb( もうしのべる, JAP_TRANSITIVE ) // (v1,vt) to say/to tell (somebody)/to state
 KanaVerb( まねる, JAP_TRANSITIVE ) // (v1,vt) to mimic/to imitate/(P)
 KanaVerb( しんぜる, JAP_TRANSITIVE ) // (v1,vt) to offer/to present
 KanaVerb( ふるわせる, JAP_TRANSITIVE ) // (v1,vt) to be shaking/to be trembling
 KanaVerb( つかす, JAP_TRANSITIVE ) // (v5s,vt) to be disgusted with/to give up on
 KanaVerb( ふかす, JAP_TRANSITIVE ) // (v5s,vt) to smoke (a cigarette)/to behave as ../to accelerate/to rev up
 KanaVerb( ふきかける, JAP_TRANSITIVE ) // (v1,vt) to blow upon/to spur/to force/to overcharge
 KanaVerb( ふきちらす, JAP_TRANSITIVE ) // (v5s,vt) to scatter/to blow about
 KanaVerb( ふきけす, JAP_TRANSITIVE ) // (v5s,vt) to blow out (a flame)
 KanaVerb( ふきあげる, JAP_TRANSITIVE ) // (v1,vt) to blow up (i.e. wind)
 KanaVerb( ふきとおす, JAP_TRANSITIVE ) // (v5s,vt) to blow through/to blow ceaselessly
 KanaVerb( ふきたおす, JAP_TRANSITIVE ) // (v5s,vt) to blow over
 KanaVerb( ふきとばす, JAP_TRANSITIVE ) // (v5s,vt) to blow off/to brush away/to talk big
 KanaVerb( ふきはらう, JAP_TRANSITIVE ) // (v5u,vt) to blow off
 KanaVerb( ふきわける, JAP_TRANSITIVE ) // (v1,vt) to blow apart/to winnow/to smelt
 KanaVerb( ふきつける, JAP_TRANSITIVE ) // (v1,vt) to blow against/to spray (paint, etc.) (onto a surface)
 KanaVerb( たらす, JAP_TRANSITIVE ) // (v5s,vt) (1) to dribble/to spill/(2) to suspend/to hang down/to slouch/to dangle/(P)
 KanaVerb( たれさげる, JAP_TRANSITIVE ) // (v1,vt) to hang (a curtain)/to droop (a tail)/to lower (a blind)
 KanaVerb( おしすすめる, JAP_TRANSITIVE ) // (v1,vt) to press forward
 KanaVerb( おす, JAP_TRANSITIVE ) // (v5s,vt) to infer/to conclude/to support/(P)
 KanaVerb( あがめる, JAP_TRANSITIVE ) // (v1,vt) to revere/to respect/to worship
 KanaVerb( かぞえる, JAP_TRANSITIVE ) // (v1,vt) to count/to enumerate/(P)
 KanaVerb( かぞえあげる, JAP_TRANSITIVE ) // (v1,vt) to count up/to enumerate
 KanaVerb( かぞえたてる, JAP_TRANSITIVE ) // (v1,vt) to enumerate/to count up
 KanaVerb( すえおく, JAP_TRANSITIVE ) // (v5k,vt) to leave as it is/to defer
 KanaVerb( すえつける, JAP_TRANSITIVE ) // (v1,vt) to install/to equip/to mount/(P)
 KanaVerb( なしとげる, JAP_TRANSITIVE ) // (v1,vt) to accomplish/to finish/to fulfill/(P)
 KanaVerb( なりたつ, JAP_TRANSITIVE ) // (v5t,vi,vt) (1) to consist of/(2) to be practical (logical, feasible, viable)/to be concluded/to hold true
 KanaVerb( はらす, JAP_TRANSITIVE ) // (v5s,vt) to dispel/to clear away/to refresh (oneself)/(P)
 KanaVerb( すます, JAP_TRANSITIVE ) // (v5s,vt) to clear/to make clear/to be unruffled/to look unconcerned/to look demure/to look prim/to put on airs
 KanaVerb( きよめる, JAP_TRANSITIVE ) // (v1,vt) to purify/to cleanse/to exorcise
 KanaVerb( いかす, JAP_TRANSITIVE ) // (v5s,vt) to revive/to resuscitate/to make use of/(P)
 KanaVerb( うみだす, JAP_TRANSITIVE ) // (v5s,vt) (1) to bring forth/to bear/to give birth to/to produce/(2) to invent/(P)
 KanaVerb( うみつける, JAP_TRANSITIVE ) // (v1,vt) to lay/to spawn
 KanaVerb( うみおとす, JAP_TRANSITIVE ) // (v5s,vt) to give birth to/to drop (calf or foal)
 KanaVerb( もりこむ, JAP_TRANSITIVE ) // (v5m,vt) to incorporate/to include/(P)
 KanaVerb( もりころす, JAP_TRANSITIVE ) // (v5s,vt) to poison to death/to kill by a prescription error
 KanaVerb( もりあげる, JAP_TRANSITIVE ) // (v1,vt) to pile up/to heap up/to stir up/to bring to a climax/to raise/(P)
 KanaVerb( もりつける, JAP_TRANSITIVE ) // (v1,vt) to dish up
 KanaVerb( もりかえす, JAP_TRANSITIVE ) // (v5s,vt) to rally/to make a comeback
 KanaVerb( うける, JAP_TRANSITIVE ) // (v1,vt) to receive/to accept/(P)
 KanaVerb( うけだす, JAP_TRANSITIVE ) // (v5s,vt) to redeem/to take out of pawn
 KanaVerb( うけおう, JAP_TRANSITIVE ) // (v5u,vt) to contract/to undertake/(P)
 KanaVerb( しょうじいれる, JAP_TRANSITIVE ) // (v1,vt) to invite or usher in
 KanaVerb( うけあう, JAP_TRANSITIVE ) // (v5u,vt) to assure/to guarantee/to undertake
 KanaVerb( おしむ, JAP_TRANSITIVE ) // (v5m,vt) (1) to be frugal/to be sparing/(2) to value/to hold dear/(3) to regret (e.g., a loss)/to feel sorry (for)/(4) to be unwilling/to be reluctant/(P)
 KanaVerb( つみこむ, JAP_TRANSITIVE ) // (v5m,vt) to load (with goods, cargo)/to put on board/to stow aboard/(P)
 KanaVerb( つみのこす, JAP_TRANSITIVE ) // (v5s,vt) to leave off cargo
 KanaVerb( つみかさねる, JAP_TRANSITIVE ) // (v1,vt) to be piled up/to accumulate/(P)
 KanaVerb( つみだす, JAP_TRANSITIVE ) // (v5s,vt) to send off
 KanaVerb( つみあげる, JAP_TRANSITIVE ) // (v1,vt) to pile up/to make a heap/to lay bricks
 KanaVerb( つみかえる, JAP_TRANSITIVE ) // (v1,vt) to transship
 KanaVerb( つみなおす, JAP_TRANSITIVE ) // (v5s,vt) to reload
 KanaVerb( つみたてる, JAP_TRANSITIVE ) // (v1,vt) to accumulate/to save
 KanaVerb( せめる, JAP_TRANSITIVE ) // (v1,vt) to condemn/to blame/to criticize/to criticise/(P)
 KanaVerb( せめつける, JAP_TRANSITIVE ) // (v1,vt) to heap blame upon
 KanaVerb( せめたてる, JAP_TRANSITIVE ) // (v1,vt) to torture severely/to urge
 KanaVerb( せっつく, JAP_TRANSITIVE ) // (v5k,vt) (uk) to pester someone (e.g., to buy something)
 KanaVerb( あからめる, JAP_TRANSITIVE ) // (v1,vt) to blush/to redden
 KanaVerb( あとづける, JAP_TRANSITIVE ) // (v1,vt) to trace/to inquire into
 KanaVerb( きらす, JAP_TRANSITIVE ) // (v5s,vt) to be out of/to run out of/to be short of/to be out of stock/(P)
 KanaVerb( きりさげる, JAP_TRANSITIVE ) // (v1,vt) (1) to cut down/to prune/to reduce/to cut and hang down/to cut shorter/(2) to round down (e.g. fraction)
 KanaVerb( きりおろす, JAP_TRANSITIVE ) // (v5s,vt) to slash downward
 KanaVerb( きりさいなむ, JAP_TRANSITIVE ) // (v5m,vt) to cut to pieces/to torment
 KanaVerb( きりほどく, JAP_TRANSITIVE ) // (v5k,vt) to cut open a tied bundle/releasing prisoners
 KanaVerb( きりまわす, JAP_TRANSITIVE ) // (v5s,vt) to run around killing/to manage everything/to control/to cut carelessly (a cook or surgeon)
 KanaVerb( きりはずす, JAP_TRANSITIVE ) // (v5s,vt) to miss in attempting to kill
 KanaVerb( きりつめる, JAP_TRANSITIVE ) // (v1,vt) to shorten/to reduce/to economize/to economise
 KanaVerb( きりきざむ, JAP_TRANSITIVE ) // (v5m,vt) to hew/to chop up/to mangle/to mince
 KanaVerb( きりこまざく, JAP_TRANSITIVE ) // (v5k,vt) to cut up small
 KanaVerb( きりころす, JAP_TRANSITIVE ) // (v5s,vt) to slay
 KanaVerb( きりちらす, JAP_TRANSITIVE ) // (v5s,vt) to cut down all/to slash promiscuously
 KanaVerb( きりすてる, JAP_TRANSITIVE ) // (v1,vt) to truncate/to cut down/to omit/to discard/to slay/to cast away/(P)
 KanaVerb( きりいだす, JAP_TRANSITIVE ) // (v5s,vt) to quarry/to cut (timber)/to cut and carry off/to begin to talk/to break the ice/to broach/to bring down
 KanaVerb( きりだす, JAP_TRANSITIVE ) // (v5s,vt) to quarry/to cut (timber)/to cut and carry off/to begin to talk/to break the ice/to broach/to bring down
 KanaVerb( きりくむ, JAP_TRANSITIVE ) // (v5m,vt) to piece together/to mortise/to miter/to dovetail
 KanaVerb( きりそろえる, JAP_TRANSITIVE ) // (v1,vt) to cut and even up/to cut several pieces to the same size
 KanaVerb( きりととのえる, JAP_TRANSITIVE ) // (v1,vt) to trim (hedges)
 KanaVerb( きりとおす, JAP_TRANSITIVE ) // (v5s,vt) to cut through (with a road, tunnel, or canal)
 KanaVerb( きりたおす, JAP_TRANSITIVE ) // (v5s,vt) to cut down/to chop down/to fell
 KanaVerb( きりぬける, JAP_TRANSITIVE ) // (v1,vt) to cut one's way through/to tide over/to struggle through/to get over
 KanaVerb( きりつける, JAP_TRANSITIVE ) // (v1,vt) to cut at/to slash at
 KanaVerb( きりふせる, JAP_TRANSITIVE ) // (v1,vt) to slay/to cut down (a foe)
 KanaVerb( きりはらう, JAP_TRANSITIVE ) // (v5u,vt) to clear away/to clear land/to prune/to lop off
 KanaVerb( きりかえす, JAP_TRANSITIVE ) // (v5s,vt) to slash or strike back/to counterattack
 KanaVerb( きりくずす, JAP_TRANSITIVE ) // (v5s,vt) (1) to level (earth)/to cut through (a mountain)/(2) to split (the opposition)/to break (strike)/(P)
 KanaVerb( きりはなつ, JAP_TRANSITIVE ) // (v5t,vt) to cut loose/to let loose/to cut off/to detach/to dismember/to cut in two
 KanaVerb( きりおとす, JAP_TRANSITIVE ) // (v5s,vt) to cut down/to lop off/to prune
 KanaVerb( きりはなす, JAP_TRANSITIVE ) // (v5s,vt) to detach/to decapitate/(P)
 KanaVerb( きりたてる, JAP_TRANSITIVE ) // (v1,vt) to cut/to slash/to slay all
 KanaVerb( きりさく, JAP_TRANSITIVE ) // (v5k,vt) to cut off/to cut up/to tear to pieces
 KanaVerb( きりあげる, JAP_TRANSITIVE ) // (v1,vt) (1) to close/to finish/(2) to round up (a number)/(3) to revalue (a currency)
 KanaVerb( きりかえる, JAP_TRANSITIVE ) // (v1,vt) to change/to exchange/to convert/to renew/to throw a switch/to replace/to switch over
 KanaVerb( おりこむ, JAP_TRANSITIVE ) // (v5m,vt) to fold inside
 KanaVerb( おりかさねる, JAP_TRANSITIVE ) // (v1,vt) to fold back (up)
 KanaVerb( おりたたむ, JAP_TRANSITIVE ) // (v5m,vt) to fold up/to fold into layers
 KanaVerb( おりかえす, JAP_TRANSITIVE ) // (v5s,vt) to turn up/to fold back/(P)
 KanaVerb( おりまげる, JAP_TRANSITIVE ) // (v1,vt) to bend/to turn up/to turn down/to double
 KanaVerb( しつらえる, JAP_TRANSITIVE ) // (v1,vt) to provide/to arrange/to install
 KanaVerb( ときすすめる, JAP_TRANSITIVE ) // (v1,vt) to persuade
 KanaVerb( ときつける, JAP_TRANSITIVE ) // (v1,vt) to persuade
 KanaVerb( ときふせる, JAP_TRANSITIVE ) // (v1,vt) to confute/to argue down
 KanaVerb( ときわける, JAP_TRANSITIVE ) // (v1,vt) to explain carefully or by making distinctions
 KanaVerb( とききかせる, JAP_TRANSITIVE ) // (v1,vt) to explain/to reason
 KanaVerb( ときあかす, JAP_TRANSITIVE ) // (v5s,vt) to explain/to solve/to make clear
 KanaVerb( たやす, JAP_TRANSITIVE ) // (v5s,vt) (1) to exterminate/to eradicate/(2) to let (fire) go out/(P)
 KanaVerb( さきだてる, JAP_TRANSITIVE ) // (v1,vt) to have (someone) go ahead
 KanaVerb( しむ, JAP_TRANSITIVE ) // (v5m,vt) (arch) to occupy/to hold/to command/to account for
 KanaVerb( あらいだす, JAP_TRANSITIVE ) // (v5s,vt) to bring to light
 KanaVerb( あらいあげる, JAP_TRANSITIVE ) // (v1,vt) to finish washing/to wash well/to investigate thoroughly/(P)
 KanaVerb( あらいなおす, JAP_TRANSITIVE ) // (v5s,vt) to wash again/to reconsider
 KanaVerb( あらいたてる, JAP_TRANSITIVE ) // (v1,vt) (1) to examine closely/to check up on/to ferret out/(2) to wash carefully
 KanaVerb( あらいながす, JAP_TRANSITIVE ) // (v5s,vt) to wash away
 KanaVerb( あらう, JAP_TRANSITIVE ) // (v5u,vt) to wash/(P)
 KanaVerb( そめる, JAP_TRANSITIVE ) // (v1,vt) to dye/to colour/to color/(P)
 KanaVerb( そめこむ, JAP_TRANSITIVE ) // (v5m,vt) to dye
 KanaVerb( そめだす, JAP_TRANSITIVE ) // (v5s,vt) to dye
 KanaVerb( そめあげる, JAP_TRANSITIVE ) // (v1,vt) to finish dyeing
 KanaVerb( そめなおす, JAP_TRANSITIVE ) // (v5s,vt) to dye again
 KanaVerb( そめぬく, JAP_TRANSITIVE ) // (v5k,vt) to dye fast/to leave undyed
 KanaVerb( そめつける, JAP_TRANSITIVE ) // (v1,vt) to dye (in patterns)
 KanaVerb( そめわける, JAP_TRANSITIVE ) // (v1,vt) to dye in different colors (colours)
 KanaVerb( そめかえす, JAP_TRANSITIVE ) // (v5s,vt) to dye again
 KanaVerb( せんじる, JAP_TRANSITIVE ) // (v1,vt) to boil/to decoct/to infuse
 KanaVerb( せんじつめる, JAP_TRANSITIVE ) // (v1,vt) to boil down/to condense
 KanaVerb( せんじだす, JAP_TRANSITIVE ) // (v5s,vt) to extract by broiling/to prepare an infusion of/to decoct
 KanaVerb( いりつける, JAP_TRANSITIVE ) // (v1,vt) to parch/to roast/to broil/to scorch
 KanaVerb( あおぎたてる, JAP_TRANSITIVE ) // (v1,vt) to fan incessantly/to agitate/to instigate
 KanaVerb( あおぐ, JAP_TRANSITIVE ) // (v5g,vt) to fan/to flap
 KanaVerb( おだてる, JAP_TRANSITIVE ) // (v1,vt) to stir up/to instigate/to flatter/(P)
 KanaVerb( うがつ, JAP_TRANSITIVE ) // (v5t,vt) to drill/to bore/to pierce/to put on/to wear/to be true to (nature)/to hit (the mark)
 KanaVerb( うらやむ, JAP_TRANSITIVE ) // (v5m,vt) to envy
 KanaVerb( すすめる, JAP_TRANSITIVE ) // (v1,vt) to recommend/to advise/to encourage/to offer (wine)/(P)
 KanaVerb( えらびだす, JAP_TRANSITIVE ) // (v5s,vt) to select/to pick out
 KanaVerb( えらぶ, JAP_TRANSITIVE ) // (v5b,vt) to choose/to select/(P)
 KanaVerb( えりだす, JAP_TRANSITIVE ) // (v5s,vt) to select/to pick out
 KanaVerb( よりだす, JAP_TRANSITIVE ) // (v5s,vt) to select/to pick out
 KanaVerb( えりぬく, JAP_TRANSITIVE ) // (v5k,vt) to select/to choose
 KanaVerb( よりぬく, JAP_TRANSITIVE ) // (v5k,vt) to select/to choose
 KanaVerb( えりわける, JAP_TRANSITIVE ) // (v1,vt) to classify/to sort out
 KanaVerb( よりわける, JAP_TRANSITIVE ) // (v1,vt) to classify/to sort out/(P)
 KanaVerb( ひらめかす, JAP_TRANSITIVE ) // (v5s,vt) to brandish/to flash/to display
 KanaVerb( つくろう, JAP_TRANSITIVE ) // (v5u,vt) to mend/to repair/to fix/to patch up/to darn/to tidy up/to adjust/to trim/(P)
 KanaVerb( ねらいすます, JAP_TRANSITIVE ) // (v5s,vt) to take careful aim
 KanaVerb( ねらう, JAP_TRANSITIVE ) // (v5u,vt) to aim at/(P)
 KanaVerb( うとむ, JAP_TRANSITIVE ) // (v5m,vt) to neglect/to shun/to alienate
 KanaVerb( うとんじる, JAP_TRANSITIVE ) // (v1,vt) to neglect/to shun/to alienate/to distance oneself from
 KanaVerb( すっぱぬく, JAP_TRANSITIVE ) // (v5k,vt) to expose/to disclose/to unmask
 KanaVerb( くみこむ, JAP_TRANSITIVE ) // (v5m,vt) to insert/to include/to cut in (printing)/(P)
 KanaVerb( くみあげる, JAP_TRANSITIVE ) // (v1,vt) to compose/to put together
 KanaVerb( くみかえる, JAP_TRANSITIVE ) // (v1,vt) to rearrange (classes)/to recompose/to reset/to recombine (genes)
 KanaVerb( くみふせる, JAP_TRANSITIVE ) // (v1,vt) to hold down
 KanaVerb( くみたてる, JAP_TRANSITIVE ) // (v1,vt) to assemble/to set up/to construct/(P)
 KanaVerb( くみいれる, JAP_TRANSITIVE ) // (v1,vt) to include/to insert/to ladle water into/to take into consideration
 KanaVerb( くみしく, JAP_TRANSITIVE ) // (v5k,vt) to press down/to hold down/to pin down
 KanaVerb( うったえる, JAP_TRANSITIVE ) // (v1,vt) to sue (a person)/to resort to/to appeal to/(P)
 KanaVerb( はじめる, JAP_TRANSITIVE ) // (v1,vt) to start/to originate
 KanaVerb( そうする, JAP_TRANSITIVE ) // (vt,vs-s) to report to the Emperor/to play (musical instrument)/to accomplish
 KanaVerb( おもう, JAP_TRANSITIVE ) // (v5u,vt) to think/to feel
 KanaVerb( さがしあてる, JAP_TRANSITIVE ) // (v1,vt) to find out/to discover/to detect
 KanaVerb( すげかえる, JAP_TRANSITIVE ) // (v1,vt) to exchange/to replace
 KanaVerb( さしかえる, JAP_TRANSITIVE ) // (v1,vt) to change/to replace
 KanaVerb( かいつまむ, JAP_TRANSITIVE ) // (v5m,vt) (uk) to sum up/to summarize/to summarise
 KanaVerb( かきまわす, JAP_TRANSITIVE ) // (v5s,vt) to stir up/to churn/to ransack/to disturb/(P)
 KanaVerb( かきよせる, JAP_TRANSITIVE ) // (v1,vt) to sweep/to rake up
 KanaVerb( かきあわせる, JAP_TRANSITIVE ) // (v1,vt) to adjust/to arrange
 KanaVerb( かきこむ, JAP_TRANSITIVE ) // (v5m,vt) to carry under the arm/to rake in
 KanaVerb( かきあつめる, JAP_TRANSITIVE ) // (v1,vt) to gather up/to scrape up together
 KanaVerb( かきけす, JAP_TRANSITIVE ) // (v5s,vt) to erase
 KanaVerb( かきのける, JAP_TRANSITIVE ) // (v1,vt) to push through
 KanaVerb( かきいだく, JAP_TRANSITIVE ) // (v5k,vt) to hug/to clasp to one's breast
 KanaVerb( かきならす, JAP_TRANSITIVE ) // (v5s,vt) to thrum/to strum
 KanaVerb( かきみだす, JAP_TRANSITIVE ) // (v5s,vt) to stir up/to disturb
 KanaVerb( かきたてる, JAP_TRANSITIVE ) // (v1,vt) to stir up/to arouse
 KanaVerb( かっこむ, JAP_TRANSITIVE ) // (v5m,vt) to bolt one's food/to gulp down
 KanaVerb( かっぱらう, JAP_TRANSITIVE ) // (v5u,vt) to swipe (as in steal)/to walk off with
 KanaVerb( かっさらう, JAP_TRANSITIVE ) // (v5u,vt) to nab/to snatch
 KanaVerb( こぎだす, JAP_TRANSITIVE ) // (v5s,vt) to begin rowing
 KanaVerb( こぎつける, JAP_TRANSITIVE ) // (v1,vt) to row up to/to attain to
 KanaVerb( よそおう, JAP_TRANSITIVE ) // (v5u,vt) (1) to dress/(2) to pretend/to feign/(P)
 KanaVerb( おくりこむ, JAP_TRANSITIVE ) // (v5m,vt) to send in/(P)
 KanaVerb( おくりだす, JAP_TRANSITIVE ) // (v5s,vt) to send out/to forward/to show (a person) out
 KanaVerb( おくりとどける, JAP_TRANSITIVE ) // (v1,vt) to send to/to deliver/to escort (a person) home
 KanaVerb( おくりつける, JAP_TRANSITIVE ) // (v1,vt) to send
 KanaVerb( さわがす, JAP_TRANSITIVE ) // (v5s,vt) to annoy/to cause trouble
 KanaVerb( ふやす, JAP_TRANSITIVE ) // (v5s,vt) to increase/to add to/to augment/(P)
 KanaVerb( にくむ, JAP_TRANSITIVE ) // (v5m,vt) to hate/to detest/(P)
 KanaVerb( つくりだす, JAP_TRANSITIVE ) // (v5s,vt) (1) to manufacture/to produce/to raise (crops)/(2) to invent/to dream up
 KanaVerb( つくりあげる, JAP_TRANSITIVE ) // (v1,vt) to make up/to fabricate/to build up/to complete/to construct
 KanaVerb( うながす, JAP_TRANSITIVE ) // (v5s,vt) to urge/to press/to suggest/to demand/to stimulate/to quicken/to incite/to invite (attention to)/(P)
 KanaVerb( そばめる, JAP_TRANSITIVE ) // (v1,vt) to shove to one side/to look at out of the corner of one's eyes
 KanaVerb( たばねる, JAP_TRANSITIVE ) // (v1,vt) to tie up in a bundle/to govern/to manage/to control/to fold (one's arms)/to administer/(P)
 KanaVerb( つかねる, JAP_TRANSITIVE ) // (v1,vt) to tie up in a bundle/to govern/to manage/to control/to fold (one's arms)/to administer
 KanaVerb( たす, JAP_TRANSITIVE ) // (v5s,vt) (1) to add (numbers)/(2) to do (e.g., one's business)/(P)
 KanaVerb( はやめる, JAP_TRANSITIVE ) // (v1,vt) to hasten/to quicken/to expedite/to precipitate/to accelerate/(P)
 KanaVerb( つづける, JAP_TRANSITIVE ) // (v1,vt) to continue/to keep up/to keep on/(P)
 KanaVerb( そろえる, JAP_TRANSITIVE ) // (v1,vt) to put things in order/to arrange/to make uniform/to get something ready/(P)
 KanaVerb( ぞんじあげる, JAP_TRANSITIVE ) // (v1,vt) (hum) to know
 KanaVerb( たっとぶ, JAP_TRANSITIVE ) // (v5b,vt) to value/to prize/to esteem/(P)
 KanaVerb( とうとぶ, JAP_TRANSITIVE ) // (v5b,vt) to value/to prize/to esteem/(P)
 KanaVerb( そこねる, JAP_TRANSITIVE ) // (v1,vt) to harm/to hurt/to injure/(P)
 KanaVerb( うちのめす, JAP_TRANSITIVE ) // (v5s,vt) to knock down/to beat (someone) up
 KanaVerb( ぶちのめす, JAP_TRANSITIVE ) // (v5s,vt) to knock down/to beat (someone) up
 KanaVerb( ぶちまける, JAP_TRANSITIVE ) // (v1,vt) (1) to throw out (everything)/(2) to tell frankly/to confess
 KanaVerb( うちおろす, JAP_TRANSITIVE ) // (v5s,vt) to bring down
 KanaVerb( うちこわす, JAP_TRANSITIVE ) // (v5s,vt) to destroy/to spoil/to crush/to wreck
 KanaVerb( ぶちこわす, JAP_TRANSITIVE ) // (v5s,vt) to destroy/to spoil/to crush/to wreck
 KanaVerb( うちあう, JAP_TRANSITIVE ) // (v5u,vt) (1) to fight/to exchange blows/to rally/(2) to arrange a meeting
 KanaVerb( うちくだく, JAP_TRANSITIVE ) // (v5k,vt) to smash/to crush
 KanaVerb( うちすてる, JAP_TRANSITIVE ) // (v1,vt) to throw away/to abandon
 KanaVerb( うちだす, JAP_TRANSITIVE ) // (v5s,vt) to begin/to beat/to end/to close/to set out (forth)/to work out/to hammer out/(P)
 KanaVerb( うちすえる, JAP_TRANSITIVE ) // (v1,vt) to place firmly/to hit very hard
 KanaVerb( うちたおす, JAP_TRANSITIVE ) // (v5s,vt) to knock down/to defeat
 KanaVerb( うちあてる, JAP_TRANSITIVE ) // (v1,vt) to hit against
 KanaVerb( うちぬく, JAP_TRANSITIVE ) // (v5k,vt) (1) to punch/to hit and hit/to stamp out/(2) to pierce/to bore into/to knock down walls
 KanaVerb( ぶちあける, JAP_TRANSITIVE ) // (v1,vt) to forcefully open up a hole (in a wall, etc)/to speak frankly, holding nothing back/to throw out everything inside
 KanaVerb( うちならす, JAP_TRANSITIVE ) // (v5s,vt) to ring/to clang
 KanaVerb( うちたてる, JAP_TRANSITIVE ) // (v1,vt) to establish/to formulate
 KanaVerb( うちひしぐ, JAP_TRANSITIVE ) // (v5g,vt) to crush (with the weight of misfortune)
 KanaVerb( ぶっかける, JAP_TRANSITIVE ) // (v1,vt) to dash (slosh) water (or other liquid) on a person or in a person's face
 KanaVerb( ぶっかく, JAP_TRANSITIVE ) // (v5k,vt) to break into pieces/to chip off
 KanaVerb( ぶっころす, JAP_TRANSITIVE ) // (v5s,vt) to beat to death
 KanaVerb( ぶっとばす, JAP_TRANSITIVE ) // (v5s,vt) to drive at full speed/to beat/to strike/to knock/to let go off/to not partake
 KanaVerb( うちあわせる, JAP_TRANSITIVE ) // (v1,vt) (1) to knock together/(2) to arrange (e.g., a meeting)
 KanaVerb( うちころす, JAP_TRANSITIVE ) // (v5s,vt) to shoot to death
 KanaVerb( うちけす, JAP_TRANSITIVE ) // (v5s,vt) to deny/to negate/to contradict/(P)
 KanaVerb( うちあげる, JAP_TRANSITIVE ) // (v1,vt) to launch/to shoot up/(of waves) dash/to wash up (ashore)/to finish/to close
 KanaVerb( うちつける, JAP_TRANSITIVE ) // (v1,vt) to knock/to run into/to nail on/to strike hard/to hit and attack/to try (an idea) on someone
 KanaVerb( ぶつける, JAP_TRANSITIVE ) // (v1,vt) to knock/to run into/to nail on/to strike hard/to hit and attack/to try (an idea) on someone/(P)
 KanaVerb( うちはらう, JAP_TRANSITIVE ) // (v5u,vt) to brush away/to repel
 KanaVerb( うちおとす, JAP_TRANSITIVE ) // (v5s,vt) to knock down/to shoot down/to lop off
 KanaVerb( たえしのぶ, JAP_TRANSITIVE ) // (v5b,vt) to put up with/to endure/to bear patiently
 KanaVerb( まちかねる, JAP_TRANSITIVE ) // (v1,vt) to wait impatiently for/(P)
 KanaVerb( まちかまえる, JAP_TRANSITIVE ) // (v1,vt) to lie in wait/to be on the watch for/(P)
 KanaVerb( まちうける, JAP_TRANSITIVE ) // (v1,vt) to await/to expect/(P)
 KanaVerb( まちこがれる, JAP_TRANSITIVE ) // (v1,vt) to long for
 KanaVerb( まちのぞむ, JAP_TRANSITIVE ) // (v5m,vt) to look anxiously for/to wait eagerly for/(P)
 KanaVerb( まちあかす, JAP_TRANSITIVE ) // (v5s,vt) to wait all night
 KanaVerb( まちわびる, JAP_TRANSITIVE ) // (v1,vt) to be tired of waiting/to wait impatiently
 KanaVerb( まつ, JAP_TRANSITIVE ) // (v5t,vt) to wait/(P)
 KanaVerb( まちもうける, JAP_TRANSITIVE ) // (v1,vt) to expect/to look for/to look forward to/to anticipate/to wait for
 KanaVerb( かしだす, JAP_TRANSITIVE ) // (v5s,vt) to lend/(P)
 KanaVerb( かしつける, JAP_TRANSITIVE ) // (v1,vt) to lend/to loan
 KanaVerb( かす, JAP_TRANSITIVE ) // (v5s,vt) to lend/(P)
 KanaVerb( しりぞける, JAP_TRANSITIVE ) // (v1,vt) to repel/to drive away/to repulse/to reject
 KanaVerb( のける, JAP_TRANSITIVE ) // (v1,vt) to remove/to take away/to dislodge/to put something out of the way/(P)
 KanaVerb( ついばむ, JAP_TRANSITIVE ) // (v5m,vt) to pick at/to peck at
 KanaVerb( ゆすぐ, JAP_TRANSITIVE ) // (v5g,vt) to rinse/to wash out
 KanaVerb( かこつ, JAP_TRANSITIVE ) // (v5t,vt) to complain about/to grumble/to make an excuse for
 KanaVerb( にごす, JAP_TRANSITIVE ) // (v5s,vt) to make muddy/to prevaricate/(P)
 KanaVerb( たたきのめす, JAP_TRANSITIVE ) // (v5s,vt) to knock down
 KanaVerb( たたきおこす, JAP_TRANSITIVE ) // (v5s,vt) to wake up/to rouse out of bed
 KanaVerb( たたきこむ, JAP_TRANSITIVE ) // (v5m,vt) to drive into/to throw into/to hit into
 KanaVerb( たたきころす, JAP_TRANSITIVE ) // (v5s,vt) to beat to death
 KanaVerb( たたきだす, JAP_TRANSITIVE ) // (v5s,vt) to begin to strike/to kick out
 KanaVerb( たたきあげる, JAP_TRANSITIVE ) // (v1,vt) to work one's way up
 KanaVerb( たたきなおす, JAP_TRANSITIVE ) // (v5s,vt) to beat into shape
 KanaVerb( たたきつける, JAP_TRANSITIVE ) // (v1,vt) to strike/to throw/to slap something onto
 KanaVerb( たたきふせる, JAP_TRANSITIVE ) // (v1,vt) to knock down/to utterly defeat
 KanaVerb( たたく, JAP_TRANSITIVE ) // (v5k,vt) (1) to strike/to clap/to dust/to beat/(2) to abuse/to flame (e.g., on the Internet)/to insult/(P)
 KanaVerb( はたく, JAP_TRANSITIVE ) // (v5k,vt) (1) to strike/to clap/to dust/to beat/(v5k,vt) (2) to use up money
 KanaVerb( うばう, JAP_TRANSITIVE ) // (v5u,vt) to snatch away/to dispossess/(P)
 KanaVerb( ぬぎすてる, JAP_TRANSITIVE ) // (v1,vt) to fling/to throw off (clothes)/to kick off (boots)
 KanaVerb( になう, JAP_TRANSITIVE ) // (v5u,vt) to carry on shoulder/to bear (burden)/to shoulder (gun)/(P)
 KanaVerb( かつぎだす, JAP_TRANSITIVE ) // (v5s,vt) to carry something out of a place
 KanaVerb( かつぎあげる, JAP_TRANSITIVE ) // (v1,vt) to put up/to flatter
 KanaVerb( かつぐ, JAP_TRANSITIVE ) // (v5g,vt) to shoulder/to carry on shoulder/(P)
 KanaVerb( さがしだす, JAP_TRANSITIVE ) // (v5s,vt) to find out
 KanaVerb( さがす, JAP_TRANSITIVE ) // (v5s,vt) (1) to search (for something lost)/to seek (a suspect in a crime)/(2) to search (for something desired, needed)/to look for/(P)
 KanaVerb( さぐりだす, JAP_TRANSITIVE ) // (v5s,vt) to spy out/to smell out
 KanaVerb( さぐりあてる, JAP_TRANSITIVE ) // (v1,vt) to find out
 KanaVerb( たたえる, JAP_TRANSITIVE ) // (v1,vt) to fill (to the brim)
 KanaVerb( きたえる, JAP_TRANSITIVE ) // (v1,vt) to forge/to drill/to temper/to train/to discipline/(P)
 KanaVerb( きたえあげる, JAP_TRANSITIVE ) // (v1,vt) to temper thoroughly/to train well
 KanaVerb( はじきだす, JAP_TRANSITIVE ) // (v5s,vt) to shoot (marbles)/to calculate/to spring out/to force out
 KanaVerb( はじく, JAP_TRANSITIVE ) // (v5k,vt) to flip/to snap/(P)
 KanaVerb( あたためる, JAP_TRANSITIVE ) // (v1,vt) to warm/to heat/(P)
 KanaVerb( しらせる, JAP_TRANSITIVE ) // (v1,vt) to notify/to advise/(P)
 KanaVerb( しりぬく, JAP_TRANSITIVE ) // (v5k,vt) to know thoroughly
 KanaVerb( おきかえる, JAP_TRANSITIVE ) // (v1,vt) to replace/to move/to change the position of
 KanaVerb( おきわすれる, JAP_TRANSITIVE ) // (v1,vt) to leave behind/to misplace/to forget
 KanaVerb( いたす, JAP_TRANSITIVE ) // (v5s,vt) (hum) to do/(P)
 KanaVerb( おくらす, JAP_TRANSITIVE ) // (v5s,vt) to retard/to delay/(P)
 KanaVerb( おくらせる, JAP_TRANSITIVE ) // (v1,vt) to put something off
 KanaVerb( きずきあげる, JAP_TRANSITIVE ) // (v1,vt) to build up/to establish (one's reputation)/(P)
 KanaVerb( きずく, JAP_TRANSITIVE ) // (v5k,vt) to build/to pile up/to amass/(P)
 KanaVerb( きこなす, JAP_TRANSITIVE ) // (v5s,vt) to wear (clothes) stylishly/to dress oneself stylishly
 KanaVerb( きせる, JAP_TRANSITIVE ) // (v1,vt) to put on clothes/(P)
 KanaVerb( きふるす, JAP_TRANSITIVE ) // (v5s,vt) to wear out (clothing)
 KanaVerb( そそぎこむ, JAP_TRANSITIVE ) // (v5m,vt) to pour into/to put into/to invest in/to inject/to impregnate/to infuse/to instill/to implant/to imbue/(P)
 KanaVerb( つぎこむ, JAP_TRANSITIVE ) // (v5m,vt) to pour into/to put into/to invest in/to inject/to impregnate/to infuse/to instill/to implant/to imbue
 KanaVerb( いこむ, JAP_TRANSITIVE ) // (v5m,vt) to cast in a mold (mould)
 KanaVerb( いつぶす, JAP_TRANSITIVE ) // (v5s,vt) to melt down
 KanaVerb( たくわえる, JAP_TRANSITIVE ) // (v1,vt) to store/to lay in stock
 KanaVerb( とぶらう, JAP_TRANSITIVE ) // (v5u,vt) to mourn for/to hold a memorial service for/to condole
 KanaVerb( とむらう, JAP_TRANSITIVE ) // (v5u,vt) to mourn for/to hold a memorial service for/to condole/(P)
 KanaVerb( はりめぐらす, JAP_TRANSITIVE ) // (v5s,vt) to stretch around
 KanaVerb( はりあげる, JAP_TRANSITIVE ) // (v1,vt) to raise
 KanaVerb( はりかえる, JAP_TRANSITIVE ) // (v1,vt) to re-cover/to reupholster/to repaper
 KanaVerb( はりたおす, JAP_TRANSITIVE ) // (v5s,vt) to knock down
 KanaVerb( はりとばす, JAP_TRANSITIVE ) // (v5s,vt) to knock down/to send flying
 KanaVerb( ほりつける, JAP_TRANSITIVE ) // (v1,vt) to carve (design)
 KanaVerb( こらしめる, JAP_TRANSITIVE ) // (v1,vt) to chastise/to punish/to discipline
 KanaVerb( こらす, JAP_TRANSITIVE ) // (v5s,vt) to chastise/to punish/to discipline
 KanaVerb( ながめる, JAP_TRANSITIVE ) // (v1,vt) to view/to gaze at/(P)
 KanaVerb( ゆるす, JAP_TRANSITIVE ) // (v5s,vt) (1) to permit/to allow/to approve/(2) to exempt (from fine)/to excuse (from)/to pardon/to release/to let off/(3) to confide in/(4) to give up/to yield
 KanaVerb( ととのえる, JAP_TRANSITIVE ) // (v1,vt) (1) to put in order/to arrange/to adjust/(2) to get ready/to prepare/(3) to raise money
 KanaVerb( しらべる, JAP_TRANSITIVE ) // (v1,vt) to investigate/to check up/(P)
 KanaVerb( いただく, JAP_TRANSITIVE ) // (v5k,vt) (hum) to receive/to take food or drink/to be crowned with/to wear/to live under (a ruler)/to install (a president)/to accept/to buy/to take/(P)
 KanaVerb( なおす, JAP_TRANSITIVE ) // (v5s,vt) (1) to cure/to heal/(2) to fix/to correct/to repair/(P)
 KanaVerb( しずめる, JAP_TRANSITIVE ) // (v1,vt) to appease/to suppress/to calm/(P)
 KanaVerb( おいこす, JAP_TRANSITIVE ) // (v5s,vt) to pass (e.g., car)/to outdistance/to outstrip/(P)
 KanaVerb( おいまわす, JAP_TRANSITIVE ) // (v5s,vt) to chase about/to hang on/to drive hard
 KanaVerb( おいかける, JAP_TRANSITIVE ) // (v1,vt) to chase or run after someone/to run down/to pursue
 KanaVerb( おいつめる, JAP_TRANSITIVE ) // (v1,vt) to corner/to drive to the wall/to run down/to track down
 KanaVerb( おいちらす, JAP_TRANSITIVE ) // (v5s,vt) to drive away/to scatter/to rout
 KanaVerb( おいだす, JAP_TRANSITIVE ) // (v5s,vt) to expel/to drive out/(P)
 KanaVerb( おいあげる, JAP_TRANSITIVE ) // (v1,vt) to gain on/to put pressure on/(P)
 KanaVerb( おいぬく, JAP_TRANSITIVE ) // (v5k,vt) to pass (a car)/to outdistance/to outsail/to outstrip/(P)
 KanaVerb( おいはらう, JAP_TRANSITIVE ) // (v5u,vt) to drive away
 KanaVerb( おいかえす, JAP_TRANSITIVE ) // (v5s,vt) to turn away/to send away
 KanaVerb( おいたてる, JAP_TRANSITIVE ) // (v1,vt) to drive away
 KanaVerb( おっかける, JAP_TRANSITIVE ) // (v1,vt) to chase or run after someone/to run down/to pursue/(P)
 KanaVerb( おっぱらう, JAP_TRANSITIVE ) // (v5u,vt) to drive away or out
 KanaVerb( いためつける, JAP_TRANSITIVE ) // (v1,vt) to rebuke/to taunt/to give a good shaking/to knock about
 KanaVerb( つかみだす, JAP_TRANSITIVE ) // (v5s,vt) to take out/to take a handful of/to grab and throw
 KanaVerb( つかむ, JAP_TRANSITIVE ) // (v5m,vt) to seize/to catch/to grasp/to grip/to grab/to hold/to catch hold of/to lay one's hands on/(P)
 KanaVerb( つぶす, JAP_TRANSITIVE ) // (v5s,vt) to smash/to waste/(P)
 KanaVerb( つるしあげる, JAP_TRANSITIVE ) // (v1,vt) (1) to hang up/to hoist/(2) to denounce/to subject someone to a kangaroo court
 KanaVerb( つるす, JAP_TRANSITIVE ) // (v5s,vt) to hang/(P)
 KanaVerb( つりさげる, JAP_TRANSITIVE ) // (v1,vt) to suspend from/to be suspended (from)
 KanaVerb( つりこむ, JAP_TRANSITIVE ) // (v5m,vt) to take in/to attract
 KanaVerb( つりだす, JAP_TRANSITIVE ) // (v5s,vt) to pull out a fish/to lure
 KanaVerb( つりあげる, JAP_TRANSITIVE ) // (v1,vt) to pull in (fish)/to boost (prices)/to raise (eyes)
 KanaVerb( ひくめる, JAP_TRANSITIVE ) // (v1,vt) to lower/to be lowered/(P)
 KanaVerb( さだめる, JAP_TRANSITIVE ) // (v1,vt) to decide/to establish/to determine/(P)
 KanaVerb( しめかためる, JAP_TRANSITIVE ) // (vt) to compact
 KanaVerb( しめこむ, JAP_TRANSITIVE ) // (v5m,vt) to shut in/to lock in
 KanaVerb( しめころす, JAP_TRANSITIVE ) // (v5s,vt) to strangle to death
 KanaVerb( しめあげる, JAP_TRANSITIVE ) // (v1,vt) to screw up/to put the screws on (a person)
 KanaVerb( しめつける, JAP_TRANSITIVE ) // (v1,vt) to tighten/to press hard
 KanaVerb( あきらめる, JAP_TRANSITIVE ) // (v1,vt) to give up/to abandon/(P)
 KanaVerb( つまみだす, JAP_TRANSITIVE ) // (v5s,vt) to pick out/to throw out
 KanaVerb( つまむ, JAP_TRANSITIVE ) // (v5m,vt) to pinch/to hold/to pick up/(P)
 KanaVerb( つむ, JAP_TRANSITIVE ) // (v5m,vt) to pluck/to pick/to trim/(P)
 KanaVerb( おぼらす, JAP_TRANSITIVE ) // (v5s,vt) (1) to drown/(2) to cause to be indulged or addicted
 KanaVerb( まとめる, JAP_TRANSITIVE ) // (v1,vt) to put in order/to collect/to bring to a conclusion/(P)
 KanaVerb( はりつける, JAP_TRANSITIVE ) // (v1,vt) to attach to a flat surface with glue/to paste/to stick/to affix
 KanaVerb( ころがす, JAP_TRANSITIVE ) // (v5s,vt) to roll/(P)
 KanaVerb( てんじる, JAP_TRANSITIVE ) // (v1,vt) to drop/to light/to kindle/to make tea
 KanaVerb( とぼす, JAP_TRANSITIVE ) // (v5s,vt) to light/to turn on
 KanaVerb( てんずる, JAP_TRANSITIVE ) // (vz,vt) to drop/to light/to kindle/to make tea
 KanaVerb( つたえる, JAP_TRANSITIVE ) // (v1,vt) to convey/to report/to transmit/to communicate/to tell/to impart/to propagate/to teach/to bequeath/(P)
 KanaVerb( つたえきく, JAP_TRANSITIVE ) // (v5k,vt) to learn by hearsay
 KanaVerb( はきすてる, JAP_TRANSITIVE ) // (v1,vt) to spit out
 KanaVerb( はきだす, JAP_TRANSITIVE ) // (v5s,vt) to vomit/to spit out/(P)
 KanaVerb( まぶす, JAP_TRANSITIVE ) // (v5s,vt) to cover (smear, sprinkle) (with)
 KanaVerb( ぬりかくす, JAP_TRANSITIVE ) // (v5s,vt) to cover with paint/to hide with paint or make-up
 KanaVerb( ぬりこめる, JAP_TRANSITIVE ) // (v1,vt) to seal up
 KanaVerb( ぬりかえる, JAP_TRANSITIVE ) // (v1,vt) to repaint/(P)
 KanaVerb( ぬりつぶす, JAP_TRANSITIVE ) // (v5s,vt) to paint out
 KanaVerb( ぬりつける, JAP_TRANSITIVE ) // (v1,vt) to daub/to smear
 KanaVerb( ぬりたてる, JAP_TRANSITIVE ) // (v1,vt) to paint beautifully/to paint thickly/to powder heavily
 KanaVerb( ねたむ, JAP_TRANSITIVE ) // (v5m,vt) to be jealous/to be envious/(P)
 KanaVerb( わたす, JAP_TRANSITIVE ) // (v5s,vt) to pass over/to hand over/(P)
 KanaVerb( いからす, JAP_TRANSITIVE ) // (v5s,vt) to anger someone/to offend someone
 KanaVerb( どなりつける, JAP_TRANSITIVE ) // (v1,vt) to shout at
 KanaVerb( たおす, JAP_TRANSITIVE ) // (v5s,vt) to throw down/to beat/to bring down/to blow down/to fell/to knock down/to trip up/to defeat/to ruin/to overthrow/to kill/to leave unpaid/to cheat/(P)
 KanaVerb( こおらす, JAP_TRANSITIVE ) // (v5s,vt) to freeze/to refrigerate
 KanaVerb( なげる, JAP_TRANSITIVE ) // (v1,vt) (1) to throw/to cast away/(2) to face defeat/to give up/(P)
 KanaVerb( なげかける, JAP_TRANSITIVE ) // (v1,vt) to throw at/to turn/to raise
 KanaVerb( なげこむ, JAP_TRANSITIVE ) // (v5m,vt) to throw into/(P)
 KanaVerb( なげだす, JAP_TRANSITIVE ) // (v5s,vt) to throw down/to abandon/to sacrifice/to throw out/(P)
 KanaVerb( なげいれる, JAP_TRANSITIVE ) // (v1,vt) to throw into/to dump in together
 KanaVerb( なげとばす, JAP_TRANSITIVE ) // (v5s,vt) to fling (away)/to hurl
 KanaVerb( なげおろす, JAP_TRANSITIVE ) // (v5s,vt) to dump (a load of something)
 KanaVerb( なげすてる, JAP_TRANSITIVE ) // (v1,vt) to throw away
 KanaVerb( なげつける, JAP_TRANSITIVE ) // (v1,vt) to throw at/to throw something at a person/to throw a person down
 KanaVerb( ぬすむ, JAP_TRANSITIVE ) // (v5m,vt) to steal/(P)
 KanaVerb( ゆびく, JAP_TRANSITIVE ) // (v5k,vt) to parboil/to scald
 KanaVerb( ゆがく, JAP_TRANSITIVE ) // (v5k,vt) to parboil/to scald
 KanaVerb( さす, JAP_TRANSITIVE ) // (v5s,vt) to light (a fire)/to apply moxa cautery
 KanaVerb( ともす, JAP_TRANSITIVE ) // (v5s,vt) to light/to turn on/(P)
 KanaVerb( あてる, JAP_TRANSITIVE ) // (v1,vt) (1) to hit/(2) to expose/(3) to apply (e.g., patch)/(4) to allot/to call on someone (e.g., in class)/(5) to guess (an answer)/(6) to make a hit (e.g., in a lottery)/(P)
 KanaVerb( あてこむ, JAP_TRANSITIVE ) // (v5m,vt) to count on
 KanaVerb( あてつける, JAP_TRANSITIVE ) // (v1,vt) to insinuate
 KanaVerb( あてはめる, JAP_TRANSITIVE ) // (v1,vt) to apply/to adapt
 KanaVerb( すべる, JAP_TRANSITIVE ) // (v1,vt) to control/to supervise
 KanaVerb( うちはたす, JAP_TRANSITIVE ) // (v5s,vt) to slay/to kill
 KanaVerb( うちほろぼす, JAP_TRANSITIVE ) // (v5s,vt) to destroy
 KanaVerb( うちとめる, JAP_TRANSITIVE ) // (v1,vt) to kill/to slay/to shoot to death/to bring down (bird)
 KanaVerb( ふまえる, JAP_TRANSITIVE ) // (v1,vt) to be based on/to have origin in/(P)
 KanaVerb( ふみはずす, JAP_TRANSITIVE ) // (v5s,vt) to miss one's footing
 KanaVerb( ふみかためる, JAP_TRANSITIVE ) // (v1,vt) to tread down
 KanaVerb( ふみつぶす, JAP_TRANSITIVE ) // (v5s,vt) to trample/to crush underfoot
 KanaVerb( ふみしめる, JAP_TRANSITIVE ) // (v1,vt) to step firmly/to harden by treading
 KanaVerb( ふみたおす, JAP_TRANSITIVE ) // (v5s,vt) to trample down/to bilk/to shirk payment
 KanaVerb( ふみいれる, JAP_TRANSITIVE ) // (v1,vt) to walk in on/to tread upon
 KanaVerb( ふみぬく, JAP_TRANSITIVE ) // (v5k,vt) to tread (a nail) into the sole of one's foot/to tread through (the floor)
 KanaVerb( ふみつける, JAP_TRANSITIVE ) // (v1,vt) to trample down/to ignore/to tread on
 KanaVerb( ふみわける, JAP_TRANSITIVE ) // (v1,vt) to push through (i.e. a crowd, vegetation, etc.)
 KanaVerb( ふみならす, JAP_TRANSITIVE ) // (v5s,vt) to stamp one's feet
 KanaVerb( ふむ, JAP_TRANSITIVE ) // (v5m,vt) to step on/to tread on/(P)
 KanaVerb( ふみあらす, JAP_TRANSITIVE ) // (v5s,vt) to trample down/to devastate
 KanaVerb( にがす, JAP_TRANSITIVE ) // (v5s,vt) to let loose/to set free/to let escape/(P)
 KanaVerb( のがす, JAP_TRANSITIVE ) // (v5s,vt) to let loose/to set free/to let escape/(P)
 KanaVerb( すかす, JAP_TRANSITIVE ) // (v5s,vt) to look through/to hold up to the light/to make an opening/to leave space/to space (lines)/to prune (trees)
 KanaVerb( とおす, JAP_TRANSITIVE ) // (v5s,vt) to let pass/to overlook/to continue/to keep/to make way for/to persist in
 KanaVerb( はたらかす, JAP_TRANSITIVE ) // (v5s,vt) to put someone to work/to make someone work
 KanaVerb( はたらきかける, JAP_TRANSITIVE ) // (v1,vt) to work on someone/to influence/to appeal to/to begin to work/(P)
 KanaVerb( うごかす, JAP_TRANSITIVE ) // (v5s,vt) to move/to shift/to set in motion/to operate/to inspire/to rouse/to influence/to mobilize/to mobilise/to deny/to change/(P)
 KanaVerb( みちびく, JAP_TRANSITIVE ) // (v5k,vt) to guide/to lead/to show the way/to conduct/(P)
 KanaVerb( かくまう, JAP_TRANSITIVE ) // (v5u,vt) to shelter/to shield/to hide
 KanaVerb( どくづく, JAP_TRANSITIVE ) // (v5k,vt) to curse (at someone)/to call someone names
 KanaVerb( よみくだす, JAP_TRANSITIVE ) // (v5s,vt) to transliterate classical Chinese into Japanese
 KanaVerb( よみあわせる, JAP_TRANSITIVE ) // (v1,vt) to read out and compare or collate
 KanaVerb( よみこむ, JAP_TRANSITIVE ) // (v5m,vt) (1) to express (e.g., emotion in poetry)/(2) to read (extra meaning) into (something)/(3) to fetch (e.g., CPU inst.)/to read (data into a system)
 KanaVerb( よみさす, JAP_TRANSITIVE ) // (v5s,vt) to leave half-read or unfinished
 KanaVerb( よみあげる, JAP_TRANSITIVE ) // (v1,vt) to read out loud (and clearly)/to call a roll/(P)
 KanaVerb( よみきかせる, JAP_TRANSITIVE ) // (v1,vt) to read aloud to another
 KanaVerb( よみかえす, JAP_TRANSITIVE ) // (v5s,vt) to reread/to read again/(P)
 KanaVerb( よみながす, JAP_TRANSITIVE ) // (v5s,vt) to read smoothly/to skim
 KanaVerb( よむ, JAP_TRANSITIVE ) // (v5m,vt) to read/(P)
 KanaVerb( よみかける, JAP_TRANSITIVE ) // (v1,vt) to begin to read/to leaf through a book
 KanaVerb( つきっかえす, JAP_TRANSITIVE ) // (v5s,vt) to poke in return/to send back/to reject
 KanaVerb( つきつめる, JAP_TRANSITIVE ) // (v1,vt) to investigate thoroughly/to probe into/to think something through/to follow an argument to its logical conclusion
 KanaVerb( つきあわせる, JAP_TRANSITIVE ) // (v1,vt) to place persons opposite/to come face to face with/to compare
 KanaVerb( つきころす, JAP_TRANSITIVE ) // (v5s,vt) to stab to death
 KanaVerb( つきさす, JAP_TRANSITIVE ) // (v5s,vt) to stab/to pierce/to thrust/(P)
 KanaVerb( つきとめる, JAP_TRANSITIVE ) // (v1,vt) to make sure/to locate/to find out/to ascertain
 KanaVerb( つきだす, JAP_TRANSITIVE ) // (v5s,vt) to push out/to project
 KanaVerb( つきのける, JAP_TRANSITIVE ) // (v1,vt) to thrust aside
 KanaVerb( つきあげる, JAP_TRANSITIVE ) // (v1,vt) to push up/to toss/(P)
 KanaVerb( つきとおす, JAP_TRANSITIVE ) // (v5s,vt) to pierce/to penetrate
 KanaVerb( つきころばす, JAP_TRANSITIVE ) // (v5s,vt) to knock (a person) down
 KanaVerb( つきたおす, JAP_TRANSITIVE ) // (v5s,vt) to push down
 KanaVerb( つきうごかす, JAP_TRANSITIVE ) // (v5s,vt) to stimulate/to stir up/to arouse
 KanaVerb( つきとばす, JAP_TRANSITIVE ) // (v5s,vt) to thrust away
 KanaVerb( つきつける, JAP_TRANSITIVE ) // (v1,vt) to thrust before/to thrust at
 KanaVerb( つきかえす, JAP_TRANSITIVE ) // (v5s,vt) to poke in return/to send back/to reject
 KanaVerb( つきもどす, JAP_TRANSITIVE ) // (v5s,vt) to thrust back/to reject
 KanaVerb( つきおとす, JAP_TRANSITIVE ) // (v5s,vt) to thrust down/to push off
 KanaVerb( つきはなす, JAP_TRANSITIVE ) // (v5s,vt) to thrust away/to refuse bluntly/to forsake
 KanaVerb( つきたてる, JAP_TRANSITIVE ) // (v1,vt) to pierce/to thrust violently
 KanaVerb( つつく, JAP_TRANSITIVE ) // (v5k,vt) (1) to thrust/to strike/to attack/(2) to poke/to nudge/to pick at/(P)
 KanaVerb( つっかける, JAP_TRANSITIVE ) // (v1,vt) to slip on (slippers, sandals, etc)/(P)
 KanaVerb( つっつく, JAP_TRANSITIVE ) // (v5k,vt) to prompt someone
 KanaVerb( つっぱなす, JAP_TRANSITIVE ) // (v5s,vt) to thrust or cast away/to look upon with detachment
 KanaVerb( つったてる, JAP_TRANSITIVE ) // (v1,vt) to stab/to plant one's feet
 KanaVerb( つっぱねる, JAP_TRANSITIVE ) // (v1,vt) to reject/to spurn/to turn down/to refuse
 KanaVerb( つんだす, JAP_TRANSITIVE ) // (v5s,vt) to push out/to project
 KanaVerb( つきつく, JAP_TRANSITIVE ) // (v5k,vt) to thrust in front of one's eyes
 KanaVerb( つきくずす, JAP_TRANSITIVE ) // (v5s,vt) to crush/to break through/to flatten
 KanaVerb( とどける, JAP_TRANSITIVE ) // (v1,vt) to deliver/to forward/to send/to report/to file notice (to the authorities)/(P)
 KanaVerb( とどけでる, JAP_TRANSITIVE ) // (v1,vt) to report/to notify
 KanaVerb( のむ, JAP_TRANSITIVE ) // (v5m,vt) to drink/to gulp/to swallow
 KanaVerb( のみこむ, JAP_TRANSITIVE ) // (v5m,vt) (1) to gulp down/to swallow deeply/(2) to understand/to take in/to catch on to/to learn/to digest
 KanaVerb( くもらす, JAP_TRANSITIVE ) // (v5s,vt) to encloud/to make dim or dull/to frown
 KanaVerb( にぶらす, JAP_TRANSITIVE ) // (v5s,vt) to blunt/to dull/to weaken
 KanaVerb( なぎたおす, JAP_TRANSITIVE ) // (v5s,vt) to mow down/to beat/to cut a swath/to sweep off one's feet
 KanaVerb( なぎはらう, JAP_TRANSITIVE ) // (v5u,vt) to mow down
 KanaVerb( におわす, JAP_TRANSITIVE ) // (v5s,vt) to give out an odor, scent or perfume (odour)/to suggest/to insinuate
 KanaVerb( にぎわす, JAP_TRANSITIVE ) // (v5s,vt) to make prosperous/to enliven
 KanaVerb( いりあげる, JAP_TRANSITIVE ) // (v1,vt) to lavish money on
 KanaVerb( いれちがえる, JAP_TRANSITIVE ) // (v1,vt) to misplace
 KanaVerb( いれこむ, JAP_TRANSITIVE ) // (v5m,vt) to put forth (effort)
 KanaVerb( いれまぜる, JAP_TRANSITIVE ) // (v1,vt) to mix
 KanaVerb( いれかえる, JAP_TRANSITIVE ) // (v1,vt) to replace/to substitute/to shift/to change places
 KanaVerb( いれあげる, JAP_TRANSITIVE ) // (v1,vt) to lavish money on
 KanaVerb( まかせる, JAP_TRANSITIVE ) // (v1,vt) (1) to entrust to another/to leave to/(2) to do something at one's leisure/(P)
 KanaVerb( しのばせる, JAP_TRANSITIVE ) // (v1,vt) to conceal/to hide
 KanaVerb( しのぶ, JAP_TRANSITIVE ) // (v5b,vt) (1) to conceal oneself/to hide/(2) to endure/(P)
 KanaVerb( したためる, JAP_TRANSITIVE ) // (v1,vt) to write up
 KanaVerb( みとめる, JAP_TRANSITIVE ) // (v1,vt) (1) to recognize/to recognise/to appreciate/(2) to observe/to notice/(3) to admit/to approve/(P)
 KanaVerb( ぬらす, JAP_TRANSITIVE ) // (v5s,vt) to wet/to soak/to dip/(P)
 KanaVerb( ねんじる, JAP_TRANSITIVE ) // (v1,vt) to have in mind/to be anxious about/to pray silently
 KanaVerb( ねんずる, JAP_TRANSITIVE ) // (vz,vt) to pray silently/to have in mind/to be anxious about
 KanaVerb( ひねくりまわす, JAP_TRANSITIVE ) // (v5s,vt) to twist/to twirl
 KanaVerb( ひねりだす, JAP_TRANSITIVE ) // (v5s,vt) to work out/to raise money
 KanaVerb( ひねりつぶす, JAP_TRANSITIVE ) // (v5s,vt) to pinch and crush/to pinch out
 KanaVerb( もす, JAP_TRANSITIVE ) // (v5s,vt) to burn/(P)
 KanaVerb( もやす, JAP_TRANSITIVE ) // (v5s,vt) to burn/(P)
 KanaVerb( なやます, JAP_TRANSITIVE ) // (v5s,vt) to afflict/to torment/to harass/to molest/(P)
 KanaVerb( おさめる, JAP_TRANSITIVE ) // (v1,vt) to obtain/to reap/to pay/to supply/to accept/to restore (something to its place)/(P)
 KanaVerb( のぞきこむ, JAP_TRANSITIVE ) // (v5m,vt) to look into/to peer in
 KanaVerb( まく, JAP_TRANSITIVE ) // (v5k,vt) to scatter/to sprinkle/to sow (seeds)
 KanaVerb( やぶく, JAP_TRANSITIVE ) // (v5k,vt) to tear/to violate/to defeat/to smash/to destroy
 KanaVerb( おがみたおす, JAP_TRANSITIVE ) // (v5s,vt) to persuade someone to consent/to entreat repeatedly/to beg/to implore
 KanaVerb( おがむ, JAP_TRANSITIVE ) // (v5m,vt) to worship/to beg/to make a supplication/(P)
 KanaVerb( そむける, JAP_TRANSITIVE ) // (v1,vt) to turn one's face away/to avert one's eyes
 KanaVerb( しょう, JAP_TRANSITIVE ) // (v5u,vt) to be burdened with/to carry on back or shoulder
 KanaVerb( せおう, JAP_TRANSITIVE ) // (v5u,vt) to be burdened with/to carry on back or shoulder/(P)
 KanaVerb( つちかう, JAP_TRANSITIVE ) // (v5u,vt) to cultivate/to foster/(P)
 KanaVerb( かいもとめる, JAP_TRANSITIVE ) // (v1,vt) to buy
 KanaVerb( かいこむ, JAP_TRANSITIVE ) // (v5m,vt) to purchase/to buy up
 KanaVerb( かいうける, JAP_TRANSITIVE ) // (v1,vt) to purchase
 KanaVerb( かいあげる, JAP_TRANSITIVE ) // (v1,vt) to buy/to buy up/to bid up
 KanaVerb( かいしめる, JAP_TRANSITIVE ) // (v1,vt) to buy up/(P)
 KanaVerb( かいたす, JAP_TRANSITIVE ) // (v5s,vt) to make additional purchases
 KanaVerb( かいかえる, JAP_TRANSITIVE ) // (v1,vt) to buy a replacement/to replace by buying something new
 KanaVerb( かいいれる, JAP_TRANSITIVE ) // (v1,vt) to purchase/to buy in/(P)
 KanaVerb( かいつける, JAP_TRANSITIVE ) // (v1,vt) to buy in/to purchase
 KanaVerb( かいもどす, JAP_TRANSITIVE ) // (v5s,vt) to buy back/to redeem
 KanaVerb( かう, JAP_TRANSITIVE ) // (v5u,vt) to buy/(P)
 KanaVerb( かいたたく, JAP_TRANSITIVE ) // (v5k,vt) to beat down prices/to strike a hard bargain
 KanaVerb( うりいそぐ, JAP_TRANSITIVE ) // (v5g,vt) to sell in haste
 KanaVerb( うりひろめる, JAP_TRANSITIVE ) // (v1,vt) to expand a market/to find a new market
 KanaVerb( うりこむ, JAP_TRANSITIVE ) // (v5m,vt) to build a market for/to become well-known/to sell/(P)
 KanaVerb( うりさばく, JAP_TRANSITIVE ) // (v5k,vt) to sell out
 KanaVerb( うりだす, JAP_TRANSITIVE ) // (v5s,vt) to put on sale/to market/to become popular/(P)
 KanaVerb( うりつくす, JAP_TRANSITIVE ) // (v5s,vt) to sell out/to exhaust one's stock
 KanaVerb( うりたたく, JAP_TRANSITIVE ) // (v5k,vt) to beat down prices
 KanaVerb( うりわたす, JAP_TRANSITIVE ) // (v5s,vt) to sell over to
 KanaVerb( うりとばす, JAP_TRANSITIVE ) // (v5s,vt) to dispose of/to sell off
 KanaVerb( うりつける, JAP_TRANSITIVE ) // (v1,vt) to palm off/to force a sale
 KanaVerb( うりはらう, JAP_TRANSITIVE ) // (v5u,vt) to dispose of
 KanaVerb( うりあるく, JAP_TRANSITIVE ) // (v5k,vt) to peddle
 KanaVerb( むきだす, JAP_TRANSITIVE ) // (v5s,vt) to show/to bare (the teeth)
 KanaVerb( むく, JAP_TRANSITIVE ) // (v5k,vt) to peel/to skin/to pare/to hull/(P)
 KanaVerb( しらげる, JAP_TRANSITIVE ) // (v1,vt) to polish (rice)/to refine/to purify
 KanaVerb( せりだす, JAP_TRANSITIVE ) // (v5s,vt) to push (a thing) out/to rise out the trap door (on stage)
 KanaVerb( さらけだす, JAP_TRANSITIVE ) // (v5s,vt) to expose/to disclose/to lay bare/to confess
 KanaVerb( さらす, JAP_TRANSITIVE ) // (v5s,vt) (1) to expose (to the air, to the public, to danger, etc.)/(2) to bleach/to refine/(P)
 KanaVerb( しばりあげる, JAP_TRANSITIVE ) // (v1,vt) to bind (tie) up
 KanaVerb( しばりつける, JAP_TRANSITIVE ) // (v1,vt) to tie
 KanaVerb( ぬかす, JAP_TRANSITIVE ) // (v5s,vt) to omit/to leave out/(P)
 KanaVerb( ぬきだす, JAP_TRANSITIVE ) // (v5s,vt) to start to pull out
 KanaVerb( ぬきはなす, JAP_TRANSITIVE ) // (v5s,vt) to unsheathe one's sword
 KanaVerb( ぬきはなつ, JAP_TRANSITIVE ) // (v5t,vt) to unsheathe
 KanaVerb( ぬく, JAP_TRANSITIVE ) // (v5k,vt) (1) to extract/to omit/to surpass/to overtake/to draw out/to unplug/(2) (suf) to do something to the end/(P)
 KanaVerb( はんじる, JAP_TRANSITIVE ) // (v1,vt) to judge/to decide/to guess/to solve/to decipher/to interpret/to divine
 KanaVerb( そらす, JAP_TRANSITIVE ) // (v5s,vt) to bend/to warp/to curve
 KanaVerb( そらせる, JAP_TRANSITIVE ) // (v1,vt) to bend/to warp
 KanaVerb( いやしめる, JAP_TRANSITIVE ) // (v1,vt) to despise/to abase (oneself)
 KanaVerb( いなむ, JAP_TRANSITIVE ) // (v5m,vt) to refuse/to decline/to deny
 KanaVerb( いやむ, JAP_TRANSITIVE ) // (v5m,vt) to detest/to dislike
 KanaVerb( かばう, JAP_TRANSITIVE ) // (v5u,vt) to protect someone/to take under one's wing/to plead for/to stick up for/to cover up for someone/(P)
 KanaVerb( かなしむ, JAP_TRANSITIVE ) // (v5m,vt) to be sad/to mourn for/to regret/(P)
 KanaVerb( くらべる, JAP_TRANSITIVE ) // (v1,vt) (1) to compare/(2) to calibrate/(P)
 KanaVerb( つからす, JAP_TRANSITIVE ) // (v5s,vt) to tire/to weary/to exhaust/to fatigue
 KanaVerb( ひめる, JAP_TRANSITIVE ) // (v1,vt) to hide/to keep to oneself/(P)
 KanaVerb( こやす, JAP_TRANSITIVE ) // (v5s,vt) to fertilize/to fertilise/to manure/to enrich/(P)
 KanaVerb( かぶす, JAP_TRANSITIVE ) // (v5s,vt) to cover (with something)
 KanaVerb( かぶせる, JAP_TRANSITIVE ) // (v1,vt) to cover (with something)/to plate something (with a metal)/to pour or dash a liquid (on something)/to charge (a person with a guilt)/(P)
 KanaVerb( ついやす, JAP_TRANSITIVE ) // (v5s,vt) to spend/to devote/to waste/(P)
 KanaVerb( よける, JAP_TRANSITIVE ) // (v1,vt) (1) to avoid (physical contact with)/(v1) (2) to ward off/to avert/(P)
 KanaVerb( とばす, JAP_TRANSITIVE ) // (v5s,vt) to skip over/to omit/(P)
 KanaVerb( とびこえる, JAP_TRANSITIVE ) // (v1,vt) to jump over/to clear/to walk over (someone)
 KanaVerb( とびこす, JAP_TRANSITIVE ) // (v5s,vt) to leap over
 KanaVerb( そなえる, JAP_TRANSITIVE ) // (v1,vt) (1) to furnish/to provide for/to equip/to install/(2) to have ready/to prepare for/(3) to possess/to have/to be endowed with/to be armed with/(P)
 KanaVerb( そなえつける, JAP_TRANSITIVE ) // (v1,vt) to provide/to furnish/to equip/to install/(P)
 KanaVerb( ぬるめる, JAP_TRANSITIVE ) // (v1,vt) to cool something down (e.g., by adding water)
 KanaVerb( あらわす, JAP_TRANSITIVE ) // (v5s,vt) to express/to show/to reveal/(P)
 KanaVerb( えがきだす, JAP_TRANSITIVE ) // (v5s,vt) to delineate/to draw/to express/to imagine
 KanaVerb( えがく, JAP_TRANSITIVE ) // (v5k,vt) to draw/to paint/to sketch/to depict/to describe/(P)
 KanaVerb( つける, JAP_TRANSITIVE ) // (v1,vt) (1) to attach/to join/to add/to append/to affix/to stick/to glue/to fasten/to sew on/to apply (ointment)/(2) to furnish (a house with)/(3) to wear/to put on/(4) to keep a diary/to make an entry/(5) to appraise/to set (a price)/(6) to bring alongside/(7) to place (under guard or doctor)/(8) to follow/to shadow/(9) to load/to give (courage to)/(10) to keep (an eye on)/(11) to establish (relations or understanding)/(P)
 KanaVerb( つけくわえる, JAP_TRANSITIVE ) // (v1,vt) to add one thing to another/(P)
 KanaVerb( つけまわす, JAP_TRANSITIVE ) // (v5s,vt) to follow/to shadow/to hanker after/to hover around
 KanaVerb( つけねらう, JAP_TRANSITIVE ) // (v5u,vt) to prowl after/to keep watch on
 KanaVerb( つけたす, JAP_TRANSITIVE ) // (v5s,vt) to add to/(P)
 KanaVerb( つけかえる, JAP_TRANSITIVE ) // (v1,vt) to renew/to replace/to change for/to attach anew
 KanaVerb( しきつめる, JAP_TRANSITIVE ) // (v1,vt) to lay/to spread all over
 KanaVerb( うかす, JAP_TRANSITIVE ) // (v5s,vt) to raise/to rise
 KanaVerb( うかべる, JAP_TRANSITIVE ) // (v1,vt) to float/to express/to look (sad, glad)/(P)
 KanaVerb( くさす, JAP_TRANSITIVE ) // (v5s,vt) to speak ill of
 KanaVerb( くさらす, JAP_TRANSITIVE ) // (v5s,vt) to spoil/to rot/to corrode
 KanaVerb( おう, JAP_TRANSITIVE ) // (v5u,vt) to bear/to owe/(P)
 KanaVerb( まかす, JAP_TRANSITIVE ) // (v5s,vt) to defeat/(P)
 KanaVerb( なでる, JAP_TRANSITIVE ) // (v1,vt) to brush gently/to stroke/(P)
 KanaVerb( なであげる, JAP_TRANSITIVE ) // (v1,vt) to comb back
 KanaVerb( なでつける, JAP_TRANSITIVE ) // (v1,vt) to comb down/to smooth down
 KanaVerb( まいおさめる, JAP_TRANSITIVE ) // (v1,vt) to conclude a dance/to dance the last dance
 KanaVerb( ふうじこめる, JAP_TRANSITIVE ) // (v1,vt) to shut in/to confine/to contain
 KanaVerb( ふきかえる, JAP_TRANSITIVE ) // (v1,vt) to reroof/to rethatch/to retile
 KanaVerb( ふしおがむ, JAP_TRANSITIVE ) // (v5m,vt) to kneel and worship
 KanaVerb( ふせる, JAP_TRANSITIVE ) // (v1,vt) to lay something upside down/to turn something over/to cover/to lay (pipes)/to lay (an ambush)/to hide/(P)
 KanaVerb( そえる, JAP_TRANSITIVE ) // (v1,vt) to add to/to attach/to append/to accompany/to garnish/to imitate/to annex
 KanaVerb( さらえる, JAP_TRANSITIVE ) // (v1,vt) to review/to rehearse/to practise/to practice
 KanaVerb( おおいかぶせる, JAP_TRANSITIVE ) // (v1,vt) to cover up with something
 KanaVerb( おおう, JAP_TRANSITIVE ) // (v5u,vt) to cover/to hide/to conceal/to wrap/to disguise/(P)
 KanaVerb( くつがえす, JAP_TRANSITIVE ) // (v5s,vt) to overturn/to upset/to overthrow/to undermine/(P)
 KanaVerb( はらいさげる, JAP_TRANSITIVE ) // (v1,vt) to make a sale of government property
 KanaVerb( はらいこむ, JAP_TRANSITIVE ) // (v5m,vt) to deposit/to pay in/(P)
 KanaVerb( はらいだす, JAP_TRANSITIVE ) // (v5s,vt) to pay (out)/to drive away
 KanaVerb( はらいのける, JAP_TRANSITIVE ) // (v1,vt) to ward off/to brush away/to fling off/to drive away
 KanaVerb( はらいわたす, JAP_TRANSITIVE ) // (v5s,vt) to pay/to pay out/to pay over
 KanaVerb( はらいもどす, JAP_TRANSITIVE ) // (v5s,vt) to repay/to pay back/(P)
 KanaVerb( はらう, JAP_TRANSITIVE ) // (v5u,vt) (1) to pay/(2) to brush/to wipe/(P)
 KanaVerb( わかす, JAP_TRANSITIVE ) // (v5s,vt) to boil/to heat/(P)
 KanaVerb( ものいう, JAP_TRANSITIVE ) // (v5u,vt) to talk/to carry meaning
 KanaVerb( わかつ, JAP_TRANSITIVE ) // (v5t,vt) to divide/to separate/to distinguish/(P)
 KanaVerb( わける, JAP_TRANSITIVE ) // (v1,vt) to divide/to separate/to make distinctions/to differentiate (between)/(P)
 KanaVerb( たきつける, JAP_TRANSITIVE ) // (v1,vt) to kindle/to build a fire/to instigate/to stir up
 KanaVerb( ふるいおこす, JAP_TRANSITIVE ) // (v5s,vt) to muster (e.g., courage)/to gather/to collect/to pluck up
 KanaVerb( まぎらす, JAP_TRANSITIVE ) // (v5s,vt) to divert/to distract/(P)
 KanaVerb( まぎらわす, JAP_TRANSITIVE ) // (v5s,vt) to divert/to distract
 KanaVerb( ききちがえる, JAP_TRANSITIVE ) // (v1,vt) to mishear
 KanaVerb( ききはずす, JAP_TRANSITIVE ) // (v5s,vt) to mishear
 KanaVerb( ききおぼえる, JAP_TRANSITIVE ) // (v1,vt) to be familiar/to learn by ear/to pick up knowledge
 KanaVerb( ききおよぶ, JAP_TRANSITIVE ) // (v5b,vt) to hear of/to learn of
 KanaVerb( ききあわせる, JAP_TRANSITIVE ) // (v1,vt) to make inquiries/to refer to
 KanaVerb( ききすてる, JAP_TRANSITIVE ) // (v1,vt) to ignore/to overlook
 KanaVerb( ききだす, JAP_TRANSITIVE ) // (v5s,vt) to get information out of a person/to begin listening
 KanaVerb( ききすます, JAP_TRANSITIVE ) // (v5s,vt) to listen attentively
 KanaVerb( ききおく, JAP_TRANSITIVE ) // (v5k,vt) to listen
 KanaVerb( ききなおす, JAP_TRANSITIVE ) // (v5s,vt) to listen again/to ask again
 KanaVerb( ききつたえる, JAP_TRANSITIVE ) // (v1,vt) to hear (secondhand)
 KanaVerb( ききとどける, JAP_TRANSITIVE ) // (v1,vt) to grant
 KanaVerb( ききなれる, JAP_TRANSITIVE ) // (v1,vt) to get used to hearing
 KanaVerb( ききいれる, JAP_TRANSITIVE ) // (v1,vt) to grant (a wish)/to accede/to comply with
 KanaVerb( ききつける, JAP_TRANSITIVE ) // (v1,vt) to hear/to catch (the sound)
 KanaVerb( ききわける, JAP_TRANSITIVE ) // (v1,vt) to recognize (identify) by sound/to recognise by sound
 KanaVerb( ききかえす, JAP_TRANSITIVE ) // (v5s,vt) to ask in return/to ask again/to listen repeatedly
 KanaVerb( ききあきる, JAP_TRANSITIVE ) // (v1,vt) to be tired of hearing
 KanaVerb( ききわすれる, JAP_TRANSITIVE ) // (v1,vt) to forget to ask
 KanaVerb( ききおとす, JAP_TRANSITIVE ) // (v5s,vt) to fail to catch
 KanaVerb( ききながす, JAP_TRANSITIVE ) // (v5s,vt) to ignore
 KanaVerb( ききなす, JAP_TRANSITIVE ) // (v5s,vt) to consider
 KanaVerb( ききとがめる, JAP_TRANSITIVE ) // (v1,vt) to find fault with
 KanaVerb( ききこむ, JAP_TRANSITIVE ) // (v5m,vt) to get information/to find out/to get wind of
 KanaVerb( あわせもつ, JAP_TRANSITIVE ) // (v5t,vt) to own (something) as well
 KanaVerb( たいらげる, JAP_TRANSITIVE ) // (v1,vt) to subjugate/to put down (trouble)/to consume (food)/to eat up
 KanaVerb( ならべる, JAP_TRANSITIVE ) // (v1,vt) to line up/to set up/(P)
 KanaVerb( ならべたてる, JAP_TRANSITIVE ) // (v1,vt) to enumerate
 KanaVerb( とざす, JAP_TRANSITIVE ) // (v5s,vt) to shut/to close/to lock/to fasten/to plunge (in grief)/(P)
 KanaVerb( とじこむ, JAP_TRANSITIVE ) // (v5m,vt) to (keep on) file
 KanaVerb( とじこめる, JAP_TRANSITIVE ) // (v1,vt) to lock up/to shut up/to imprison
 KanaVerb( しめる, JAP_TRANSITIVE ) // (v1,vt) to close/to shut/(P)
 KanaVerb( しめだす, JAP_TRANSITIVE ) // (v5s,vt) to shut out/to bar/to lock out
 KanaVerb( さげすむ, JAP_TRANSITIVE ) // (v5m,vt) to scorn/to despise/(P)
 KanaVerb( かたづける, JAP_TRANSITIVE ) // (v1,vt) (1) to tidy up/to put in order/to straighten up/to put away/(2) to settle (problem)/to clear (dispute)/(3) to finish/to bring something to an end/(4) to marry off (e.g., a daughter)/(5) to do away with someone/to bump someone off/(P)
 KanaVerb( あみだす, JAP_TRANSITIVE ) // (v5s,vt) to work out/to think out
 KanaVerb( あむ, JAP_TRANSITIVE ) // (v5m,vt) (1) to knit/to plait/to braid/(2) to compile (anthology, dictionary, etc.)/to edit/(P)
 KanaVerb( かえす, JAP_TRANSITIVE ) // (v5s,vt) to return something/(P)
 KanaVerb( わきまえる, JAP_TRANSITIVE ) // (v1,vt) to know (right from wrong)/to discern/to discriminate/to understand/to bear in mind/(P)
 KanaVerb( むちうつ, JAP_TRANSITIVE ) // (v5t,vt) to whip/to lash/to give the rod/to spur on/to encourage
 KanaVerb( たもつ, JAP_TRANSITIVE ) // (v5t,vt) to keep/to preserve/to hold/to retain/to maintain/to support/to sustain/to last/to endure/to keep well (food)/to wear well/to be durable/(P)
 KanaVerb( つかまえる, JAP_TRANSITIVE ) // (v1,vt) to catch/to arrest/to seize/(P)
 KanaVerb( とらえる, JAP_TRANSITIVE ) // (v1,vt) to seize/to grasp/to capture/to arrest/(P)
 KanaVerb( おぎなう, JAP_TRANSITIVE ) // (v5u,vt) to compensate for/(P)
 KanaVerb( たすく, JAP_TRANSITIVE ) // (v5k,vt) to help/to save/to rescue
 KanaVerb( たすける, JAP_TRANSITIVE ) // (v1,vt) to help/to save/to rescue/to give relief to/to spare (life)/to reinforce/to promote/to abet
 KanaVerb( したう, JAP_TRANSITIVE ) // (v5u,vt) to yearn for/to miss/to adore/to love dearly/(P)
 KanaVerb( くらす, JAP_TRANSITIVE ) // (v5s,vt) to live/to get along/(P)
 KanaVerb( つつみかくす, JAP_TRANSITIVE ) // (v5s,vt) to conceal/to keep secret/to cover up
 KanaVerb( つつみこむ, JAP_TRANSITIVE ) // (v5m,vt) to wrap up
 KanaVerb( くるむ, JAP_TRANSITIVE ) // (v5m,vt) (1) to wrap up/to tuck in/to pack/to do up/to cover with/to dress in/(P)
 KanaVerb( つつむ, JAP_TRANSITIVE ) // (v5m,vt) (1) to wrap up/to tuck in/to pack/to do up/to cover with/to dress in/(v5m) (2) to conceal/to hide/to be engulfed in/to be enveloped by/(P)
 KanaVerb( くるめる, JAP_TRANSITIVE ) // (v1,vt) to lump together/to include/to sum up/to quibble
 KanaVerb( むくいる, JAP_TRANSITIVE ) // (v1,vt) to reward/to recompense/to repay/(P)
 KanaVerb( むくう, JAP_TRANSITIVE ) // (v5u,vt) to reward/to recompense/to repay/(P)
 KanaVerb( ほうじる, JAP_TRANSITIVE ) // (v1,vt) to obey/to follow
 KanaVerb( くずす, JAP_TRANSITIVE ) // (v5s,vt) to destroy/to pull down/to make change (money)/(P)
 KanaVerb( かかえる, JAP_TRANSITIVE ) // (v1,vt) (1) to hold or carry under or in the arms/(2) to have (esp. problems, debts, etc.)/(3) to employ/to engage/to hire/(P)
 KanaVerb( かかえこむ, JAP_TRANSITIVE ) // (v5m,vt) to hold (carry) a thing in one's arm/to embrace (a baby)/to take upon oneself
 KanaVerb( だきおこす, JAP_TRANSITIVE ) // (v5s,vt) to lift (a person) in one's arms/to help (a person) sit up
 KanaVerb( だきこむ, JAP_TRANSITIVE ) // (v5m,vt) to hold in one's arms/to bring over a person to one's side/to involve
 KanaVerb( だきあげる, JAP_TRANSITIVE ) // (v1,vt) to hold up in one's arms
 KanaVerb( だきしめる, JAP_TRANSITIVE ) // (v1,vt) to hug someone close/to hold someone tight/to embrace closely
 KanaVerb( だきかかえる, JAP_TRANSITIVE ) // (v1,vt) to hold/to carry/to embrace (in one's arms)
 KanaVerb( だきとめる, JAP_TRANSITIVE ) // (v1,vt) to catch in one's arms
 KanaVerb( だきすくめる, JAP_TRANSITIVE ) // (v1,vt) to hug tight
 KanaVerb( いだく, JAP_TRANSITIVE ) // (v5k,vt) (1) to embrace/to hold in the arms, e.g., a baby/to hug/(v5k,vt) (2) to harbour e.g., grudge/to harbor/to harbour/to entertain e.g., suspicion/(P)
 KanaVerb( だく, JAP_TRANSITIVE ) // (v5k,vt) (1) to embrace/to hold in the arms, e.g., a baby/to hug/(v5k) (2) to sleep with/(v5k) (3) to sit on eggs/(P)
 KanaVerb( ささげる, JAP_TRANSITIVE ) // (v1,vt) to lift up/to give/to offer/to consecrate/to devote/to sacrifice/to dedicate/(P)
 KanaVerb( こく, JAP_TRANSITIVE ) // (v5k,vt) (1) (uk) to let loose (e.g., a fart)/(2) to utter (e.g., a lie)
 KanaVerb( はなつ, JAP_TRANSITIVE ) // (v5t,vt) to free/to release/to fire/(P)
 KanaVerb( ほうりこむ, JAP_TRANSITIVE ) // (v5m,vt) to throw into
 KanaVerb( ほうりだす, JAP_TRANSITIVE ) // (v5s,vt) to throw out/to fire/to expel/to give up/to abandon/to neglect
 KanaVerb( あわだてる, JAP_TRANSITIVE ) // (v1,vt) to beat/to whip
 KanaVerb( ぬいこむ, JAP_TRANSITIVE ) // (v5m,vt) to sew in
 KanaVerb( ぬいあげる, JAP_TRANSITIVE ) // (v1,vt) to finish sewing
 KanaVerb( ぬいなおす, JAP_TRANSITIVE ) // (v5s,vt) to resew/to remake
 KanaVerb( ぬいつける, JAP_TRANSITIVE ) // (v1,vt) to sew on
 KanaVerb( ぬいかえす, JAP_TRANSITIVE ) // (v5s,vt) to resew
 KanaVerb( ぬう, JAP_TRANSITIVE ) // (v5u,vt) to sew/(P)
 KanaVerb( たずねる, JAP_TRANSITIVE ) // (v1,vt) to visit/(P)
 KanaVerb( さまたげる, JAP_TRANSITIVE ) // (v1,vt) to disturb/to prevent/(P)
 KanaVerb( わすれる, JAP_TRANSITIVE ) // (v1,vt) to forget/to leave carelessly/to be forgetful of/to forget about/to forget (an article)/(P)
 KanaVerb( あばく, JAP_TRANSITIVE ) // (v5k,vt) to disclose/to divulge/to expose
 KanaVerb( おかす, JAP_TRANSITIVE ) // (v5s,vt) to brave/to risk/to face/to venture/to desecrate/to profane/(P)
 KanaVerb( つむぐ, JAP_TRANSITIVE ) // (v5g,vt) to spin/to make yarn/(P)
 KanaVerb( ふくらます, JAP_TRANSITIVE ) // (v5s,vt) to swell/to expand/to inflate/to bulge/(P)
 KanaVerb( ふせぐ, JAP_TRANSITIVE ) // (v5g,vt) to defend (against)/to protect/to prevent/(P)
 KanaVerb( ひるがえす, JAP_TRANSITIVE ) // (v5s,vt) to change (mind)/to reverse (decision)/to wave/to flutter/(P)
 KanaVerb( すりかえる, JAP_TRANSITIVE ) // (v1,vt) to secretly substitute
 KanaVerb( すりつける, JAP_TRANSITIVE ) // (v1,vt) (1) to rub against/to nuzzle against, e.g., dog nosing a person/(2) to strike (a match)
 KanaVerb( みがきあげる, JAP_TRANSITIVE ) // (v1,vt) to polish up/to shine up
 KanaVerb( みがきたてる, JAP_TRANSITIVE ) // (v1,vt) to polish (up)/dress up
 KanaVerb( みがく, JAP_TRANSITIVE ) // (v5k,vt) to polish/to shine/to brush/to refine/to improve/(P)
 KanaVerb( すりへらす, JAP_TRANSITIVE ) // (v5s,vt) to wear away/to rub down/to abrade
 KanaVerb( すりだす, JAP_TRANSITIVE ) // (v5s,vt) to polish
 KanaVerb( すりつぶす, JAP_TRANSITIVE ) // (v5s,vt) to pulverize/to pulverise/to mash/to deface/to lose a fortune
 KanaVerb( うずめる, JAP_TRANSITIVE ) // (v1,vt) to bury (e.g., one's face in hands)/(P)
 KanaVerb( うめる, JAP_TRANSITIVE ) // (v1,vt) (1) to bury/(2) to fill up (e.g., audience fills a hall)/to fill (a seat, a vacant position)/(3) to plug gaps/to stop a gap/(4) to make amends/to cover up for something/(5) to put cold water in a bath/(P)
 KanaVerb( うめあわせる, JAP_TRANSITIVE ) // (v1,vt) to make amends/to compensate for/to make up for
 KanaVerb( うめたてる, JAP_TRANSITIVE ) // (v1,vt) to reclaim/to fill up
 KanaVerb( あじわう, JAP_TRANSITIVE ) // (v5u,vt) to taste/to savor/to relish/(P)
 KanaVerb( みとどける, JAP_TRANSITIVE ) // (v1,vt) to make sure of/to assure oneself of/to see with one's own eyes/to ascertain
 KanaVerb( ばかす, JAP_TRANSITIVE ) // (v5s,vt) to bewitch/to confuse/to enchant/to delude
 KanaVerb( つとめる, JAP_TRANSITIVE ) // (v1,vt) (1) to serve/to fill a post/to serve under/to work (for)/(2) to exert oneself/to endeavor/to endeavour/to be diligent/(3) to play (the part of)/(P)
 KanaVerb( なくす, JAP_TRANSITIVE ) // (v5s,vt) (1) to lose something/(v5s) (2) to get rid of/(P)
 KanaVerb( なくなす, JAP_TRANSITIVE ) // (v5s,vt) to lose/to miss
 KanaVerb( なづける, JAP_TRANSITIVE ) // (v1,vt) to name (someone)/(P)
 KanaVerb( めいじる, JAP_TRANSITIVE ) // (v1,vt) to order/to command/to appoint/(P)
 KanaVerb( めいずる, JAP_TRANSITIVE ) // (vz,vt) to command/to appoint/(P)
 KanaVerb( あかす, JAP_TRANSITIVE ) // (v5s,vt) to pass/spend/to reveal/to divulge/(P)
 KanaVerb( あけわたす, JAP_TRANSITIVE ) // (v5s,vt) to vacate/to surrender
 KanaVerb( あけはらう, JAP_TRANSITIVE ) // (v5u,vt) to open/to vacate
 KanaVerb( あけはなす, JAP_TRANSITIVE ) // (v5s,vt) to open wide (doors,windows, etc.)/to fling open
 KanaVerb( ちかう, JAP_TRANSITIVE ) // (v5u,vt) to swear/to vow/to take an oath/to pledge
 KanaVerb( まよわす, JAP_TRANSITIVE ) // (v5s,vt) to puzzle/perplex/bewilder/delude/mislead/fascinate
 KanaVerb( ならす, JAP_TRANSITIVE ) // (v5s,vt) to ring/to sound/to chime/to beat/to snort (nose)/(P)
 KanaVerb( ほろぼす, JAP_TRANSITIVE ) // (v5s,vt) to destroy/to overthrow/to wreck/to ruin/(P)
 KanaVerb( めんじる, JAP_TRANSITIVE ) // (v1,vt) to dismiss/to exempt
 KanaVerb( もうける, JAP_TRANSITIVE ) // (v1,vt) to get/to earn/to gain/to have (bear, beget) a child/(P)
 KanaVerb( めがける, JAP_TRANSITIVE ) // (v1,vt) to aim at
 KanaVerb( めざす, JAP_TRANSITIVE ) // (v5s,vt) to aim at/to have an eye on/(P)
 KanaVerb( もくろむ, JAP_TRANSITIVE ) // (v5m,vt) to plan/to form a plan/to scheme/to envision/to intend to do
 KanaVerb( もどす, JAP_TRANSITIVE ) // (v5s,vt) to restore/to put back/to return/(P)
 KanaVerb( もらう, JAP_TRANSITIVE ) // (v5u,vt) (1) (uk) to receive/to take/to accept/(2) to get somebody to do something (follows a verb in te form)/(P)
 KanaVerb( といかける, JAP_TRANSITIVE ) // (v1,vt) to ask a question
 KanaVerb( といつめる, JAP_TRANSITIVE ) // (v1,vt) to press a question/to cross-examine
 KanaVerb( といかえす, JAP_TRANSITIVE ) // (v5s,vt) to ask again/to ask back
 KanaVerb( とう, JAP_TRANSITIVE ) // (v5u-s,vt) (1) to ask/to question/to inquire/(2) to charge (i.e. with a crime)/to accuse/(3) to care (about)/(4) without regard to (with negative verb)/(P)
 KanaVerb( やくだてる, JAP_TRANSITIVE ) // (v1,vt) to put to use/to make use of/to turn to account
 KanaVerb( つづめる, JAP_TRANSITIVE ) // (v1,vt) to abridge/to shorten/to economize
 KanaVerb( いやす, JAP_TRANSITIVE ) // (v5s,vt) to heal/to cure
 KanaVerb( さとす, JAP_TRANSITIVE ) // (v5s,vt) to admonish/to persuade/to warn/to remonstrate/(P)
 KanaVerb( ゆうきづける, JAP_TRANSITIVE ) // (v1,vt) to encourage/to cheer
 KanaVerb( なだめる, JAP_TRANSITIVE ) // (v1,vt) (uk) to soothe/to calm/to pacify/(P)
 KanaVerb( なだめすかす, JAP_TRANSITIVE ) // (v5s,vt) to soothe and humor (humour)/to coax
 KanaVerb( うれえる, JAP_TRANSITIVE ) // (v1,vt) to grieve/to lament/to be anxious/to be distressed/(P)
 KanaVerb( さそいこむ, JAP_TRANSITIVE ) // (v5m,vt) to entice/to tempt/to invite someone to join in
 KanaVerb( さそいだす, JAP_TRANSITIVE ) // (v5s,vt) to lure/to invite out
 KanaVerb( いざなう, JAP_TRANSITIVE ) // (v5u,vt) (1) to invite/to ask/to call (for)/(2) to tempt/to lure/to induce
 KanaVerb( さそう, JAP_TRANSITIVE ) // (v5u,vt) to invite/to call out/(P)
 KanaVerb( そなう, JAP_TRANSITIVE ) // (v5u,vt) (1) to invite/to ask/to call (for)/(2) to tempt/to lure/to induce
 KanaVerb( おびきよせる, JAP_TRANSITIVE ) // (v1,vt) to lure someone/to entice someone
 KanaVerb( おびきだす, JAP_TRANSITIVE ) // (v5s,vt) to lure out of/to decoy out of/to entice out of
 KanaVerb( おびきいれる, JAP_TRANSITIVE ) // (v1,vt) to lure/to entice
 KanaVerb( あそばす, JAP_TRANSITIVE ) // (v5s,vt) to let one play/to leave idle/to do (polite)
 KanaVerb( あそびくらす, JAP_TRANSITIVE ) // (v5s,vt) to idle away one's time
 KanaVerb( あます, JAP_TRANSITIVE ) // (v5s,vt) to save/to leave over/to spare/(P)
 KanaVerb( あたえる, JAP_TRANSITIVE ) // (v1,vt) (1) (comp) to give/to present/to award/(2) to pass (a variable to a function)/(P)
 KanaVerb( ほめる, JAP_TRANSITIVE ) // (v1,vt) to praise/to admire/to speak well
 KanaVerb( ほめたたえる, JAP_TRANSITIVE ) // (v1,vt) to admire/to praise/to applaud
 KanaVerb( あずける, JAP_TRANSITIVE ) // (v1,vt) (1) to give into custody/to leave (a child) in the care of/to entrust/to deposit/(2) to lean on/to put one's weight on/(P)
 KanaVerb( あずけいれる, JAP_TRANSITIVE ) // (v1,vt) to make a deposit/(P)
 KanaVerb( やとう, JAP_TRANSITIVE ) // (v5u,vt) to employ/to hire
 KanaVerb( あげる, JAP_TRANSITIVE ) // (v1,vt) (1) (gen) to lift/to fly/(2) (food) to deep fry in hot oil/(P)
 KanaVerb( ゆする, JAP_TRANSITIVE ) // (vs-s,vt) to shake/to jolt/to rock (cradle)/to swing/(P)
 KanaVerb( ゆらす, JAP_TRANSITIVE ) // (v5s,vt) to rock/to shake/to swing
 KanaVerb( ゆりうごかす, JAP_TRANSITIVE ) // (v5s,vt) to shake/to wave/to swing/to sway
 KanaVerb( ゆるがす, JAP_TRANSITIVE ) // (v5s,vt) to shake/to swing/to sway/to shock/(P)
 KanaVerb( とく, JAP_TRANSITIVE ) // (v5k,vt) to dissolve (paint)/(P)
 KanaVerb( もちいる, JAP_TRANSITIVE ) // (v1,vt) to use/to make use of/(P)
 KanaVerb( ようだてる, JAP_TRANSITIVE ) // (v1,vt) to make use of/to lend money
 KanaVerb( おどらす, JAP_TRANSITIVE ) // (v5s,vt) (1) to manipulate/(2) to let one dance
 KanaVerb( やしなう, JAP_TRANSITIVE ) // (v5u,vt) to rear/to maintain/to cultivate/(P)
 KanaVerb( おさえる, JAP_TRANSITIVE ) // (v1,vt) to check/to curb/to suppress/to control/to arrest/(P)
 KanaVerb( おさえつける, JAP_TRANSITIVE ) // (v1,vt) to press down/to hold down/to pin down/to repress
 KanaVerb( あびせる, JAP_TRANSITIVE ) // (v1,vt) to pour on/(P)
 KanaVerb( あびせかける, JAP_TRANSITIVE ) // (v1,vt) to hurl abuse/to level insults
 KanaVerb( あびる, JAP_TRANSITIVE ) // (v1,vt) to bathe/to bask in the sun/to shower/(P)
 KanaVerb( きたす, JAP_TRANSITIVE ) // (v5s,vt) to cause/to induce/to bring about a result or state/to produce
 KanaVerb( たのみこむ, JAP_TRANSITIVE ) // (v5m,vt) to request earnestly
 KanaVerb( おちつける, JAP_TRANSITIVE ) // (v1,vt) to quiet/to calm down/to compose oneself
 KanaVerb( おとす, JAP_TRANSITIVE ) // (v5s,vt) to drop/to lose/to let fall/(P)
 KanaVerb( ひかす, JAP_TRANSITIVE ) // (v5s,vt) to redeem debts (e.g., of a geisha)
 KanaVerb( みだす, JAP_TRANSITIVE ) // (v5s,vt) to throw out of order/to disarrange/to disturb/(P)
 KanaVerb( きかせる, JAP_TRANSITIVE ) // (v1,vt) to be seasoned/to be enlivened/(P)
 KanaVerb( はきちがえる, JAP_TRANSITIVE ) // (v1,vt) to put on anothers shoes/to be mistaken
 KanaVerb( うらづける, JAP_TRANSITIVE ) // (v1,vt) to support/to endorse/to substantiate
 KanaVerb( うらがえす, JAP_TRANSITIVE ) // (v5s,vt) to turn inside out/to turn the other way/to turn (something) over/(P)
 KanaVerb( ひきいる, JAP_TRANSITIVE ) // (v1,vt) to lead/to spearhead (a group)/to command (troops)/(P)
 KanaVerb( たてる, JAP_TRANSITIVE ) // (v1,vt) to stand (something) up/to erect (something)/(P)
 KanaVerb( たてかける, JAP_TRANSITIVE ) // (v1,vt) to lean against/to set against
 KanaVerb( たてこめる, JAP_TRANSITIVE ) // (v1,vt) to be shut tight
 KanaVerb( たてかえる, JAP_TRANSITIVE ) // (v1,vt) to pay in advance/to pay for another/to pay someone else's debt as a loan to him/(P)
 KanaVerb( たてとおす, JAP_TRANSITIVE ) // (v5s,vt) to push through (an idea)
 KanaVerb( たてなおす, JAP_TRANSITIVE ) // (v5s,vt) to rally/to make over/to rearrange/to reorganize/to reorganise
 KanaVerb( かすめる, JAP_TRANSITIVE ) // (v1,vt) to rob/to pillage/to skim/to sweep over/to graze (in passing)/to cheat/to hint
 KanaVerb( ながしこむ, JAP_TRANSITIVE ) // (v5m,vt) to pour into/to wash down
 KanaVerb( ながす, JAP_TRANSITIVE ) // (v5s,vt) to drain/to float/to shed (blood, tears)/to cruise (e.g., taxi)/(P)
 KanaVerb( ためる, JAP_TRANSITIVE ) // (v1,vt) to amass/to accumulate/(P)
 KanaVerb( ためこむ, JAP_TRANSITIVE ) // (v5m,vt) to save up
 KanaVerb( とどめる, JAP_TRANSITIVE ) // (v1,vt) to stop/to cease/to put an end to/(P)
 KanaVerb( とめる, JAP_TRANSITIVE ) // (v1,vt) to fasten/to turn off/to detain
 KanaVerb( とめおく, JAP_TRANSITIVE ) // (v5k,vt) to detain/to keep/to lock up/to retain/to leave (letter) till called for
 KanaVerb( しまう, JAP_TRANSITIVE ) // (v5u,vt) (uk) to finish/to close/to do something completely/to put away/to put an end to
 KanaVerb( しのぐ, JAP_TRANSITIVE ) // (v5g,vt) to outdo/to surpass/to endure/to keep out (rain)/to stave off/to tide over/to pull through/to defy/to slight/to excel/to eclipse/(P)
 KanaVerb( はかりこむ, JAP_TRANSITIVE ) // (v5m,vt) to measure liberally
 KanaVerb( りきむ, JAP_TRANSITIVE ) // (v5m,vt) to strain/to bear up/to exert one's strength/to swagger/to bluff/to boast/(P)
 KanaVerb( ちからづける, JAP_TRANSITIVE ) // (v1,vt) to encourage (someone)/to cheer (someone) up
 KanaVerb( さます, JAP_TRANSITIVE ) // (v5s,vt) to cool/to dampen/to let cool/to throw a damper on/to spoil/(P)
 KanaVerb( ひやす, JAP_TRANSITIVE ) // (v5s,vt) to cool/to refrigerate/(P)
 KanaVerb( はげます, JAP_TRANSITIVE ) // (v5s,vt) to encourage/to cheer/to raise (the voice)/(P)
 KanaVerb( こぼす, JAP_TRANSITIVE ) // (v5s,vt) to spill/(P)
 KanaVerb( さく, JAP_TRANSITIVE ) // (v5k,vt) to tear/to split/(P)
 KanaVerb( こう, JAP_TRANSITIVE ) // (v5u,vt) to be in love
 KanaVerb( こいしたう, JAP_TRANSITIVE ) // (v5u,vt) to miss/to yearn for
 KanaVerb( あわれむ, JAP_TRANSITIVE ) // (v5m,vt) to pity
 KanaVerb( ねりかためる, JAP_TRANSITIVE ) // (v1,vt) to harden by kneading
 KanaVerb( ねりあげる, JAP_TRANSITIVE ) // (v1,vt) to train up/to discipline
 KanaVerb( ねりなおす, JAP_TRANSITIVE ) // (v5s,vt) to knead again/to work over
 KanaVerb( つらねる, JAP_TRANSITIVE ) // (v1,vt) to link/to join/to put together/(P)
 KanaVerb( つれこむ, JAP_TRANSITIVE ) // (v5m,vt) to bring (somebody into a place)
 KanaVerb( つれだす, JAP_TRANSITIVE ) // (v5s,vt) to take out
 KanaVerb( ねぎらう, JAP_TRANSITIVE ) // (v5u,vt) (uk) to thank for/for reward for
 KanaVerb( もてあそぶ, JAP_TRANSITIVE ) // (v5b,vt) to play with/to trifle with
 KanaVerb( もらす, JAP_TRANSITIVE ) // (v5s,vt) to let leak/to reveal/(P)
 KanaVerb( もれきく, JAP_TRANSITIVE ) // (v5k,vt) to overhear
 KanaVerb( あげつらう, JAP_TRANSITIVE ) // (v5u,vt) (1) to discuss/(2) to find fault with/to criticize/to criticise
 KanaVerb( ろんじる, JAP_TRANSITIVE ) // (v1,vt) to argue/to discuss/to debate/(P)
 KanaVerb( ろんずる, JAP_TRANSITIVE ) // (vz,vt) to argue/to discuss/to debate/(P)
 KanaVerb( やわらげる, JAP_TRANSITIVE ) // (v1,vt) to soften/to moderate/to relieve/(P)
 KanaVerb( はなしかける, JAP_TRANSITIVE ) // (v1,vt) to accost a person/to talk (to someone)/(P)
 KanaVerb( はなしあう, JAP_TRANSITIVE ) // (v5u,vt) to discuss/to talk together/(P)
 KanaVerb( はなす, JAP_TRANSITIVE ) // (v5s,vt) to speak/(P)
 KanaVerb( はなしこむ, JAP_TRANSITIVE ) // (v5m,vt) to be deep in talk/(P)
 KanaVerb( いがめる, JAP_TRANSITIVE ) // (v1,vt) to bend/to curve/to warp/to distort
 KanaVerb( ゆがめる, JAP_TRANSITIVE ) // (v1,vt) to bend/to curve/to warp/to distort
 KanaVerb( まかなう, JAP_TRANSITIVE ) // (v5u,vt) to give board to/to provide meals/to pay/(P)
 KanaVerb( まどわす, JAP_TRANSITIVE ) // (v5s,vt) to bewilder/to perplex/to puzzle/(P)
 KanaVerb( ほのめかす, JAP_TRANSITIVE ) // (v5s,vt) to hint at/to intimate/to suggest/to allude to/(P)
 KanaVerb( はく, JAP_TRANSITIVE ) // (v5k,vt) to wear/to put on (lower body, e.g., a sword)
 KanaVerb( うつぶせる, JAP_TRANSITIVE ) // (v1,vt) to lie face-down
 KanaVerb( うつむける, JAP_TRANSITIVE ) // (v1,vt) to turn upside down/to turn (face) downward
 KanaVerb( かしずく, JAP_TRANSITIVE ) // (v5k,vt) to wait upon/to serve
 KanaVerb( もたせかける, JAP_TRANSITIVE ) // (v1,vt) to lean against/to set against
 KanaVerb( こそげる, JAP_TRANSITIVE ) // (v1,vt) to scrape off
 KanaVerb( くりぬく, JAP_TRANSITIVE ) // (v5k,vt) to gouge out/to excavate/to bore/to drill
 KanaVerb( つんざく, JAP_TRANSITIVE ) // (v5k,vt) to break/to tear/to pierce/to split/to burst
 KanaVerb( かむ, JAP_TRANSITIVE ) // (v5m,vt) to bite/to chew/to gnaw/(P)
 KanaVerb( かぎだす, JAP_TRANSITIVE ) // (v5s,vt) to scent out/to detect
 KanaVerb( かぎあてる, JAP_TRANSITIVE ) // (v1,vt) to sniff out/to catch the scent of
 KanaVerb( かぎつける, JAP_TRANSITIVE ) // (v1,vt) to sniff out/to get wind of
 KanaVerb( かぎわける, JAP_TRANSITIVE ) // (v1,vt) to scent out/to discern
 KanaVerb( かぐ, JAP_TRANSITIVE ) // (v5g,vt) to sniff/to smell/(P)
 KanaVerb( たしなむ, JAP_TRANSITIVE ) // (v5m,vt) to have a taste for/to be fond of
 KanaVerb( けしかける, JAP_TRANSITIVE ) // (v1,vt) (uk) to instigate/to incite/to spur on
 KanaVerb( あざわらう, JAP_TRANSITIVE ) // (v5u,vt) (uk) to sneer at/to ridicule
 KanaVerb( はやす, JAP_TRANSITIVE ) // (v5s,vt) to play accompaniment/to jeer at
 KanaVerb( こぼつ, JAP_TRANSITIVE ) // (v5t,vt) to destroy/to break/to damage
 KanaVerb( ふさぐ, JAP_TRANSITIVE ) // (v5g,vt) to stop up/to close up/to block (up)/to occupy/to fill up/to take up/to stand in another's way/to plug up/to shut up
 KanaVerb( はめる, JAP_TRANSITIVE ) // (v1,vt) (1) (col) to get in/to insert/to put on/(2) to make love/(P)
 KanaVerb( こらえる, JAP_TRANSITIVE ) // (v1,vi,vt) (1) to bear/to stand/to endure/to put up with
 KanaVerb( かっとばす, JAP_TRANSITIVE ) // (v5s,vt) to knock out (a homer)/to slam
 KanaVerb( たつ, JAP_TRANSITIVE ) // (v5t,vt) to sever/to cut off/to suppress/to abstain (from)
 KanaVerb( こじあける, JAP_TRANSITIVE ) // (v1,vt) to wrench open/to prize open/to pick (lock)
 KanaVerb( こじらせる, JAP_TRANSITIVE ) // (v1,vt) to aggravate/to complicate/to make worse
 KanaVerb( なげうつ, JAP_TRANSITIVE ) // (v5t,vt) to abandon/to fling away
 KanaVerb( ひしぐ, JAP_TRANSITIVE ) // (v5g,vt) to crush
 KanaVerb( こまぬく, JAP_TRANSITIVE ) // (v5k,vt) (1) to fold (one's) arms/(2) to stand by and do nothing/to look on passively
 KanaVerb( こまねく, JAP_TRANSITIVE ) // (v5k,vt) (1) to fold (one's) arms/(2) to stand by and do nothing/to look on passively
 KanaVerb( こさえる, JAP_TRANSITIVE ) // (v1,vt) to make/to manufacture
 KanaVerb( こしらえる, JAP_TRANSITIVE ) // (v1,vt) to make/to manufacture/(P)
 KanaVerb( でっちあげる, JAP_TRANSITIVE ) // (v1,vt) (1) (uk) to fabricate/to invent/to make up (a story)/(2) to frame someone
 KanaVerb( こねる, JAP_TRANSITIVE ) // (v1,vt) to knead/to mix with fingers
 KanaVerb( こねまわす, JAP_TRANSITIVE ) // (v5s,vt) to knead/to mix/to complicate/to turn into a mess
 KanaVerb( こねかえす, JAP_TRANSITIVE ) // (v5s,vt) to knead/to mix/to complicate/to turn into a mess
 KanaVerb( ねじまげる, JAP_TRANSITIVE ) // (v1,vt) to twist/to distort
 KanaVerb( ねじむける, JAP_TRANSITIVE ) // (v1,vt) to twist
 KanaVerb( ねじこむ, JAP_TRANSITIVE ) // (v5m,vt) to screw in/to thrust into a container/to protest against (and demand compensation)
 KanaVerb( ねじあげる, JAP_TRANSITIVE ) // (v1,vt) to twist hard
 KanaVerb( ねじふせる, JAP_TRANSITIVE ) // (v1,vt) to hold down/to twist one's arm
 KanaVerb( もみあう, JAP_TRANSITIVE ) // (v5u,vt) to jostle/to shove and push/to struggle with one another
 KanaVerb( もみだす, JAP_TRANSITIVE ) // (v5s,vt) to squeeze out/to begin to squeeze
 KanaVerb( もみけす, JAP_TRANSITIVE ) // (v5s,vt) to crush/to hush up
 KanaVerb( もむ, JAP_TRANSITIVE ) // (v5m,vt) to rub/to crumple (up)/to wrinkle/to massage/to be troubled about/to worry over/to train/to coach/(P)
 KanaVerb( からめる, JAP_TRANSITIVE ) // (v1,vt) (1) to arrest/(2) to entwine/to twine around/(3) to coordinate (with)
 KanaVerb( たわむ, JAP_TRANSITIVE ) // (v5m,vt) to bend/to warp
 KanaVerb( はねかす, JAP_TRANSITIVE ) // (v5s,vt) to splash/to splatter
 KanaVerb( はねる, JAP_TRANSITIVE ) // (v1,vt) (1) to reject/to deny/to refuse/(2) to eliminate/to exclude/to leave out/(3) to flip/to splash/to splatter/(4) to decapitate/to behead/(5) to hit (e.g., to have a car hit something or someone)/to run into/(6) to jump up/(P)
 KanaVerb( はねのける, JAP_TRANSITIVE ) // (v1,vt) to push aside/to brush or thrust aside/to remove/to get rid of
 KanaVerb( はねあげる, JAP_TRANSITIVE ) // (v1,vt) to splash/to raise
 KanaVerb( はねとばす, JAP_TRANSITIVE ) // (v5s,vt) (1) to send (something) flying/to splatter/(2) to drive (something) off
 KanaVerb( はねつける, JAP_TRANSITIVE ) // (v1,vt) to repel/to spurn
 KanaVerb( もたげる, JAP_TRANSITIVE ) // (v1,vt) to lift/to raise
 KanaVerb( ぼかす, JAP_TRANSITIVE ) // (v5s,vt) to shade off/to obscure/(P)
 KanaVerb( とかす, JAP_TRANSITIVE ) // (v5s,vt) (1) to comb out/(2) to melt
 KanaVerb( すく, JAP_TRANSITIVE ) // (v5k,vt) to comb (out)/to card
 KanaVerb( いれる, JAP_TRANSITIVE ) // (v1,vt) (1) to put something in (e.g., into a container)/(2) to let somebody in (e.g., into a room)
 KanaVerb( からす, JAP_TRANSITIVE ) // (v5s,vt) to dry up/to exhaust
 KanaVerb( すすぐ, JAP_TRANSITIVE ) // (v5g,vt) to rinse/to wash out
 KanaVerb( こす, JAP_TRANSITIVE ) // (v5s,vt) to filter/to strain
 KanaVerb( いためる, JAP_TRANSITIVE ) // (v1,vt) to stir-fry/(P)
 KanaVerb( いぶす, JAP_TRANSITIVE ) // (v5s,vt) (1) to smoke (something)/to fumigate/(2) to oxidize/to oxidise
 KanaVerb( いぶりだす, JAP_TRANSITIVE ) // (v5s,vt) to smoke animal out of its den
 KanaVerb( ただらかす, JAP_TRANSITIVE ) // (v5s,vt) to cause to be inflamed
 KanaVerb( すがめる, JAP_TRANSITIVE ) // (v1,vt) to scrutinize/to scrutinise
 KanaVerb( にらみあわせる, JAP_TRANSITIVE ) // (v1,vt) to weigh one thing against the other/to act in consideration of/to compare and take into consideration
 KanaVerb( にらみつける, JAP_TRANSITIVE ) // (v1,vt) to glare at/to scowl at
 KanaVerb( にらむ, JAP_TRANSITIVE ) // (v5m,vt) to glare at/to scowl at/to keep an eye on/(P)
 KanaVerb( にらめつける, JAP_TRANSITIVE ) // (v1,vt) to glare at/to scowl at
 KanaVerb( ねめつける, JAP_TRANSITIVE ) // (v1,vt) to glare at/to scowl at
 KanaVerb( はらいきよめる, JAP_TRANSITIVE ) // (v1,vt) to purify/to exorcise
 KanaVerb( けがす, JAP_TRANSITIVE ) // (v5s,vt) (1) to disgrace/to dishonour/to dishonor/(2) to pollute/to contaminate/to soil/to make dirty/to stain
 KanaVerb( たしなめる, JAP_TRANSITIVE ) // (v1,vt) (uk) to chide/to rebuke/to reprove
 KanaVerb( やつす, JAP_TRANSITIVE ) // (v5s,vt) (1) to be absorbed in/to lose oneself to/(2) to disguise oneself as
 KanaVerb( すくめる, JAP_TRANSITIVE ) // (v1,vt) (uk) to shrug (shoulders)/to duck (head)/to draw back (body)
 KanaVerb( ふるいわける, JAP_TRANSITIVE ) // (v1,vt) to sift/to screen
 KanaVerb( こめる, JAP_TRANSITIVE ) // (v1,vt) to include/to put into
 KanaVerb( ただす, JAP_TRANSITIVE ) // (v5s,vt) to query/(P)
 KanaVerb( くける, JAP_TRANSITIVE ) // (v1,vt) to blindstitch
 KanaVerb( ないまぜる, JAP_TRANSITIVE ) // (v1,vt) (1) to mix/to include/(2) to entwine threads of various colours (colors)
 KanaVerb( くびりころす, JAP_TRANSITIVE ) // (v5s,vt) to strangle to death
 KanaVerb( ひもとく, JAP_TRANSITIVE ) // (v5k,vi,vt) (1) to peruse (a book)/(2) to untie a scroll
 KanaVerb( かざす, JAP_TRANSITIVE ) // (v5s,vt) (1) to hold up over one's head/to hold aloft/(2) to hold one's hands out (e.g., towards a fire)/(3) to shade one's eyes, face, etc.
 KanaVerb( なめる, JAP_TRANSITIVE ) // (v1,vt) to lick/to taste/to experience/to make fun of/to make light of/to put down/to treat with contempt/(P)
 KanaVerb( ゆでる, JAP_TRANSITIVE ) // (v1,vt) to boil/(P)
 KanaVerb( うごめかす, JAP_TRANSITIVE ) // (v5s,vt) to wriggle
 KanaVerb( てらう, JAP_TRANSITIVE ) // (v5u,vt) to show off/to parade/to pretend
 KanaVerb( いぶかしむ, JAP_TRANSITIVE ) // (v5m,vt) to doubt
 KanaVerb( あつらえる, JAP_TRANSITIVE ) // (v1,vt) (uk) to give an order/to place an order
 KanaVerb( たぶらかす, JAP_TRANSITIVE ) // (v5s,vt) to trick/to cheat/to deceive
 KanaVerb( たらしこむ, JAP_TRANSITIVE ) // (v5m,vt) to cajole/to deceive/to seduce
 KanaVerb( しいる, JAP_TRANSITIVE ) // (v1,vt) to slander/to accuse falsely
 KanaVerb( いさめる, JAP_TRANSITIVE ) // (v1,vt) to remonstrate/to warn not to do something
 KanaVerb( うたう, JAP_TRANSITIVE ) // (v5u,vt) to express/to state/to insist/to stipulate/(P)
 KanaVerb( たとえる, JAP_TRANSITIVE ) // (v1,vt) to compare/to liken/to speak figuratively/to illustrate/to use a simile
 KanaVerb( けなす, JAP_TRANSITIVE ) // (v5s,vt) (uk) to speak ill of
 KanaVerb( おとしめる, JAP_TRANSITIVE ) // (v1,vt) to show contempt for/to look down upon/to have a low opinion of
 KanaVerb( あがなう, JAP_TRANSITIVE ) // (v5u,vt) to compensate/to make up for
 KanaVerb( かわす, JAP_TRANSITIVE ) // (v5s,vt) to dodge/to evade/to avoid/to sidestep
 KanaVerb( ひきころす, JAP_TRANSITIVE ) // (v5s,vt) to kill by running over
 KanaVerb( ひく, JAP_TRANSITIVE ) // (v5k,vt) to run somebody over (with vehicle)/to knock someone down/(P)
 KanaVerb( すべらす, JAP_TRANSITIVE ) // (v5s,vt) to let something slip/to slide/to glide
 KanaVerb( つぐむ, JAP_TRANSITIVE ) // (v5m,vt) to shut one's mouth
 KanaVerb( くわえる, JAP_TRANSITIVE ) // (v1,vt) (uk) to hold in one's mouth/(P)
 KanaVerb( はさむ, JAP_TRANSITIVE ) // (v5m,vt) to cut off
 KanaVerb( ちりばめる, JAP_TRANSITIVE ) // (v1,vt) (uk) to inlay/to set/to stud/to enchase (a thing) with/to mount (gem)
 KanaVerb( あえる, JAP_TRANSITIVE ) // (v1,vt) to dress vegetables (salad)
 KanaVerb( しかめる, JAP_TRANSITIVE ) // (v1,vt) (uk) to knit the brows/to raise eyebrows/to scowl/to grimace/to frown
 KanaVerb( ひそめる, JAP_TRANSITIVE ) // (v1,vt) (uk) to knit the brows/to raise eyebrows/to scowl/to grimace/to frown
 KanaVerb( だましこむ, JAP_TRANSITIVE ) // (v5m,vt) to deceive/to ensnare
 KanaVerb( だます, JAP_TRANSITIVE ) // (v5s,vt) to trick/to cheat/to deceive/(P)
 KanaVerb( なびかす, JAP_TRANSITIVE ) // (v5s,vt) to seduce/to win over/to conquer
 KanaVerb( あいたくちもふさがらぬ ) // (v5n) to be surprising/to be shocking/to be jaw-dropping
 KanaVerb( あっといわせる ) // (v1) to startle
 KanaVerb( いかれる ) // (v1,vi) to be beaten/to break down
 KanaVerb( いじける ) // (v1,vi) (1) to grow timid (e.g., from an inferiority complex)/to lose one's nerve/(2) to become perverse/to become contrary
 KanaVerb( いじりまわす ) // (v5s) to tinker with/to twist up
 KanaVerb( いちゃつく ) // (v5k,vi) to flirt with/to dally
 KanaVerb( いらっしゃる ) // (v5aru,vi) (hon) to be/to come/to go/(P)
 KanaVerb( うっとりさせる ) // (v1) to enchant/to enthrall
 KanaVerb( うらぶれる ) // (v1,vi) to get shabby/to go downhill/to go to seed/to go to the dogs
 KanaVerb( おききいただく ) // (v5k) to ask (politely)
 KanaVerb( かじかむ ) // (v5m,vi) to grow numb with cold
 KanaVerb( かなぐりすてる ) // (v1) to fling off/to throw off/to throw to the winds
 KanaVerb( かまける ) // (v1,vi) to be too busy/to be occupied
 KanaVerb( がっつく ) // (v5k,vi) to be greedy/to devour greedily
 KanaVerb( くすむ ) // (v5m,vi) to be quiet/to be dull/to darken
 KanaVerb( くっつく ) // (v5k) (uk) to adhere to/to keep close to/(P)
 KanaVerb( くっつける ) // (v1) to attach/(P)
 KanaVerb( くんくんなく ) // (v5k) to whine (dog)
 KanaVerb( ぐらつく ) // (v5k,vi) to be unsteady/to reel/to shake
 KanaVerb( げらげらわらう ) // (v5u) to guffaw
 KanaVerb( げんをかつぐ ) // (v5g) to be superstitious
 KanaVerb( こっくりうなずく ) // (v5k) to nod in agreement/to nod in assent
 KanaVerb( こっくりとうなずく ) // (v5k) to nod in agreement/to nod in assent
 KanaVerb( ことができる ) // (v1) can (do)/to be able to (do)
 KanaVerb( こます ) // (v5s,vi) (1) to do/to have sexual intercourse/(2) to give/to present/to award
 KanaVerb( ごったがえす ) // (v5s,vi) to be in confusion or commotion/to be in a turmoil/to be crowded or jammed with people
 KanaVerb( ごろつく ) // (v5k,vi) to rumble/to thunder/to roll about (people, large objects)/to wander about without a fixed workplace, home, etc.
 KanaVerb( ささくれる ) // (v1,vi) (1) to split finely/to splinter/to get frayed/(2) to become irritable
 KanaVerb( しがみつく ) // (v5k) (uk) to cling
 KanaVerb( しくしくなく ) // (v5k) to sob/to weep
 KanaVerb( しみったれる ) // (v1,vi) to be stingy/to be tightfisted
 KanaVerb( しゃがみこむ ) // (v5m,vi) (uk) to squat
 KanaVerb( しゃがむ ) // (v5m,vi) to squat/(P)
 KanaVerb( しょぼくれる ) // (v1,vi) to be dispirited/to be dejected/to be disheartened/to lose heart
 KanaVerb( しらばくれる ) // (v1,vi) to play dumb/to feign ignorance/to act as innocent
 KanaVerb( しらばっくれる ) // (v1,vi) to play dumb/to feign ignorance/to act as innocent
 KanaVerb( しぶく ) // (v5k,vi) to splash/to spray
 KanaVerb( じっとみる ) // (v1) to watch steadily
 KanaVerb( じろじろみる ) // (v1) to stare at/to look hard at/to look up and down/to scrutinize/to scrutinise
 KanaVerb( すすりなく ) // (v5k) to sob
 KanaVerb( ずばずばいう ) // (v5u) to speak one's mind/to speak very frankly
 KanaVerb( ずばぬける ) // (v1,vi) to tower above the rest/to be by far the best/to be prominent
 KanaVerb( ずれこむ ) // (v5m,vi) to drag on/to be delayed
 KanaVerb( せせらぐ ) // (v5g) to babble (stream)
 KanaVerb( そびれる ) // (v1,vi) to miss a chance/to fail to do
 KanaVerb( たくしあげる ) // (v1) to roll up or pull up (sleeves, skirt, etc)
 KanaVerb( たじろぐ ) // (v5g,vi) to falter/to wince
 KanaVerb( だぶつく ) // (v5k,vi) (1) to be too large/to be baggy/to be flabby/(2) to have a glut
 KanaVerb( だらける ) // (v1,vi) to be lazy/to be slack/to feel dull/to feel languid/to feel listless
 KanaVerb( ちゅうちゅうすう ) // (v5u) to suck
 KanaVerb( ちゅうちゅうなく ) // (v5k) to squeak/to chirp/to twitter
 KanaVerb( ちらつく ) // (v5k,vi) to flicker/to flit/to litter/to be dazzled
 KanaVerb( つけはじめる ) // (v1) to begin to light (a cigarette)
 KanaVerb( でござる ) // (v5aru) (pol) to be
 KanaVerb( どんつく ) // (v5k) to make a drumming noise
 KanaVerb( にたつく ) // (v5k,vi) to have (break out into) a broad (suggestive) grin
 KanaVerb( にやける ) // (v1,vi) to be effeminate/to be a fop
 KanaVerb( ぬたうつ ) // (v5t,vi) to roll around in the grass or mud
 KanaVerb( のめりこむ ) // (v5m,vi) to be completely absorbed in/to fall for (something)
 KanaVerb( はためく ) // (v5k,vi) to flutter (e.g., a flag)
 KanaVerb( はちきれる ) // (v1,vi) to be filled to bursting/to burst
 KanaVerb( はめたおす ) // (v5s) (col) to make love
 KanaVerb( びんびんくる ) // (vk) to get an erection (US: hard-on)
 KanaVerb( ぴくぴくうごく ) // (v5k) to jerk/to wiggle/to twitch
 KanaVerb( ぴよぴよなく ) // (v5k) to peep/to cheep
 KanaVerb( ぴんとくる ) // (vk) to get (a joke or explanation)/to strike home/to know intuitively
 KanaVerb( ぶらつく ) // (v5k,vi) to dangle/to swing/to stroll about/to hang around/to linger
 KanaVerb( へこたれる ) // (v1,vi) to lose heart
 KanaVerb( へばりつく ) // (v5k) to cling to
 KanaVerb( べたつく ) // (v5k,vi) to be sticky
 KanaVerb( べろべろなめる ) // (v1) (uk) to lick up with one's tongue
 KanaVerb( ほそぼそはなす ) // (v5s) to speak slowly and quietly
 KanaVerb( ほっつく ) // (v5k,vi) (1) to loiter/(2) to waste money
 KanaVerb( ほつく ) // (v5k,vi) (1) to loiter/(2) to waste money
 KanaVerb( ぼやく ) // (v5k,vi) to grumble/to complain
 KanaVerb( ぼやける ) // (v1,vi) to become dim/to become blurred/(P)
 KanaVerb( ぼりぼりたべる ) // (v1) to eat with a munching or crunching sound
 KanaVerb( ぽたぽたおちる ) // (v1) to fall in drops/to drip down/to trickle down
 KanaVerb( まくりあげる ) // (v1) to tuck (e.g., sleeves)
 KanaVerb( まごつかせる ) // (v1) to abash
 KanaVerb( まごつく ) // (v5k,vi) to be confused/to be flustered/(P)
 KanaVerb( まじまじとみる ) // (v1) to take a long hard look at something
 KanaVerb( むかつく ) // (v5k,vi) to feel sick/to feel irritated/to feel offended/to feel angry
 KanaVerb( めげる ) // (v1,vi) to be discouraged/to shrink from
 KanaVerb( もぐ ) // (v5g) to pluck (usually from a tree)/to pick (e.g., apples)/(P)
 KanaVerb( もげる ) // (v1,vi) to be torn off/to come off
 KanaVerb( やっかむ ) // (v5m,vi) to be jealous/to be envious
 KanaVerb( やっちまう ) // (v5u) to do something the speaker regrets
 KanaVerb( やってくる ) // (vk) to come along/to come around/to turn up/(P)
 KanaVerb( らっしゃる ) // (v5aru,vi) (abbr) (hon) to be/to come/to go
 KanaVerb( ギラつく ) // (v5k,vi) (1) to glare/to dazzle/(2) to glitter
 KanaVerb( ゴワつく ) // (v5k,vi) to be stiff/to be starchy
 KanaVerb( ザラつく ) // (v5k,vi) to be rough feeling
 KanaVerb( ザワつく ) // (v5k,vi) to be noisy (e.g. from people talking)
 KanaVerb( チクチクいたむ ) // (v5m) to prickle
 KanaVerb( チューチューなく ) // (v5k) to squeak/to chirp/to twitter
 KanaVerb( ニヤつく ) // (v5k) to smirk/to grin broadly
 KanaVerb( バタつく ) // (v5k,vi) to clatter/to flap (noisily)/to rattle/to walk around being unable to settle down
 KanaVerb( パサつく ) // (v5k,vi) to be dried out/to be parched
 KanaVerb( パラつく ) // (v5k,vi) to sprinkle (e.g., with rain)
 KanaVerb( ヒクつく ) // (v5k,vi) to twitch
 KanaVerb( ヒリつく ) // (v5k,vi) to hurt/to smart/to sting
 KanaVerb( ピントがはずれる ) // (v1) to be out of focus/to be off the point/to be queer in the head
 KanaVerb( ブチころす ) // (v5s) to kill by hitting
 KanaVerb( ベトつく ) // (v5k,vi) to be sticky
 KanaVerb( モタつく ) // (v5k,vi) to be slow/to not make progress/to be inefficient
 KanaVerb( あだめく ) // (v5k) to be bewitching/to look coquettish
 KanaVerb( あいしあう ) // (v5u) to love one another
 KanaVerb( あいする ) // (vs-s) to love/(P)
 KanaVerb( あいにうえる ) // (v1) to hunger (starve) for love
 KanaVerb( わるくいう ) // (v5u) to deprecate/to traduce
 KanaVerb( あくたれる ) // (v1,vi) to do mischief/to use abusive language
 KanaVerb( わるびれる ) // (v1,vi) to be timid/to be shy
 KanaVerb( わるずれる ) // (v1) to get worse and worse
 KanaVerb( へしあう ) // (v5u,vi) to jostle/to push
 KanaVerb( あっする ) // (vs-s) to press/to oppress/to dominate/to overwhelm
 KanaVerb( こきおとす ) // (v5s) to thresh
 KanaVerb( やすくあげる ) // (v1) to make it less expensive
 KanaVerb( やすくつく ) // (v5k) to come cheaper
 KanaVerb( やすらぐ ) // (v5g,vi) to feel at ease/(P)
 KanaVerb( やすんじる ) // (v1,vi) to be contented/to be at ease
 KanaVerb( もってする ) // (vs-s) to do by the use of
 KanaVerb( くらいする ) // (vs-s) to rank/to be ranked/to be located
 KanaVerb( いばりちらす ) // (v5s) to domineer
 KanaVerb( いきごむ ) // (v5m,vi) to be enthusiastic about/(P)
 KanaVerb( なぐさむ ) // (v5m,vi) to be diverted/to forget one's worries/to comfort
 KanaVerb( いよりなんへすすむ ) // (v5m) to proceed from the easy to the difficult
 KanaVerb( しすぎる ) // (v1) to overdo/to do too much
 KanaVerb( しそめる ) // (v1) to begin to do
 KanaVerb( しつづける ) // (v1) to continue to do/to persist in doing
 KanaVerb( うつしかえる ) // (v1) to shift (move) (an object) to (into)
 KanaVerb( うつりゆく ) // (v5k-s,vi) to change/to shift/to come and go
 KanaVerb( うつろう ) // (v5u,vi) to change/to fade
 KanaVerb( なえる ) // (v1,vi) to wither/to droop/to be lame
 KanaVerb( しなびる ) // (v1,vi) to wilt/to fade
 KanaVerb( しおれる ) // (v1,vi) to wither/(P)
 KanaVerb( そだちすぎる ) // (v1) to be overgrown
 KanaVerb( そだちゆく ) // (v5k-s) to grow up
 KanaVerb( そだつ ) // (v5t,vi) to be raised (e.g., child)/to be brought up/to grow (up)/(P)
 KanaVerb( いちおうきいておく ) // (v5k) to hear someone out anyway
 KanaVerb( ひとはたあげる ) // (v1) to make a name for oneself
 KanaVerb( いっきにのむ ) // (v5m) to drink in one gulp
 KanaVerb( いっくよむ ) // (v5m) to make up a haiku poem
 KanaVerb( ひとくちくう ) // (v5u) to have a munch/to take a bite
 KanaVerb( ひとくちたべる ) // (v1) to eat a mouthful
 KanaVerb( いっさついれる ) // (v1) to give a signed statement or an IOU
 KanaVerb( ひとやまあてる ) // (v1) to be right on target/to strike it rich
 KanaVerb( いちじあける ) // (v1) to leave a space (between words)
 KanaVerb( ひとふしうたう ) // (v5u) to sing a tune
 KanaVerb( いちだんらくつける ) // (v1) to complete the first stage of/to settle for the time being
 KanaVerb( いっぱいくわされる ) // (v1) to be taken in/to be duped/to be deceived
 KanaVerb( いっぱいくわす ) // (v5s) to play a trick on
 KanaVerb( ひとはだぬぐ ) // (v5g) to pitch in and help
 KanaVerb( いっぱつかます ) // (v5s) (sl) to hit someone
 KanaVerb( いっぱつぬく ) // (v5k) to ejaculate
 KanaVerb( いっぱつはなつ ) // (v5t) to break wind/to have a shot
 KanaVerb( ひとふでかく ) // (v5k) to drop a few lines
 KanaVerb( いっぷくのむ ) // (v5m) to have a smoke
 KanaVerb( いっぽしりぞく ) // (v5k) to take a step backward
 KanaVerb( ひとあわふかせる ) // (v1) to give a surprise (or blow)/to scare the hell out of
 KanaVerb( いちもくおく ) // (v5k) to take off one's hat to a person/to acknowledge anothers superiority/to give a piece or stone
 KanaVerb( ひとやくかう ) // (v5u) to take on a role/to take part
 KanaVerb( あふれる ) // (v1,vi) to flood/to overflow/to brim over/(P)
 KanaVerb( あふれでる ) // (v1) to overflow from something full
 KanaVerb( いっする ) // (vs-s) to lose (a chance)/to miss (a chance)/to deviate/to forget
 KanaVerb( それる ) // (v1,vi) to stray (turn) from subject/to get lost/to go astray/(P)
 KanaVerb( はぐれる ) // (v1,vi) to stray (turn) from subject/to get lost/to go astray/(P)
 KanaVerb( むせびなく ) // (v5k,vi) to sob/to be choked with tears
 KanaVerb( ちなむ ) // (v5m,vi) to be associated (with)/to be connected (with)
 KanaVerb( ひける ) // (v1,vi) to close/to be over/to break up (e.g., school)
 KanaVerb( ひっこす ) // (v5s,vi) to move (house)/to change residence/(P)
 KanaVerb( ひっくるめる ) // (v1) to lump together
 KanaVerb( ひっこむ ) // (v5m,vi) to draw back/to sink/to cave in/(P)
 KanaVerb( ひっぱたく ) // (v5k) to slap/to strike
 KanaVerb( ひっぱりあげる ) // (v1) to pull up/to haul up
 KanaVerb( ひっつく ) // (v5k) to stick to/to flirt with/(P)
 KanaVerb( ひっとらえる ) // (v1) to arrest/to capture/to seize
 KanaVerb( ひんむく ) // (v5k) to strip/to peel
 KanaVerb( ひきこす ) // (v5s,vi) to move (house)/to change residence
 KanaVerb( ひきあう ) // (v5u,vi) to pay/to be profitable
 KanaVerb( ひきつづく ) // (v5k,vi) to continue (for a long time)/to occur in succession
 KanaVerb( ひきたつ ) // (v5t) (1) to become active/(2) to look better
 KanaVerb( のませる ) // (v1) to make somebody drink/to give someone a drink
 KanaVerb( のみすぎる ) // (v1) to drink too much
 KanaVerb( のみつぶれる ) // (v1,vi) to drink oneself drunk
 KanaVerb( のめる ) // (v1) to drink much/to be good to drink
 KanaVerb( のんだくれる ) // (v1) to get dead drunk
 KanaVerb( かげでうごく ) // (v5k) to act behind the scenes
 KanaVerb( かくしもつ ) // (v5t) to carry (something) under cover
 KanaVerb( かくれる ) // (v1,vi) to hide/to be hidden/to conceal oneself/to disappear/(P)
 KanaVerb( かくれふす ) // (v5s) to lie concealed
 KanaVerb( はばたく ) // (v5k,vi) to flap (wings)/(P)
 KanaVerb( うずまく ) // (v5k,vi) to whirl/to eddy/to swirl/to curl (smoke)
 KanaVerb( うそでかためる ) // (v1) to fabricate a web of lies
 KanaVerb( はこびだす ) // (v5s) to carry out
 KanaVerb( はこびあげる ) // (v1) to carry or bring (up)
 KanaVerb( はこびいれる ) // (v1) to carry or bring in(to)
 KanaVerb( はこぶ ) // (v5b) to transport/(P)
 KanaVerb( うんめいづける ) // (v1) to preordain
 KanaVerb( くもつく ) // (v5k) to tower
 KanaVerb( さかえる ) // (v1,vi) to prosper/to flourish/(P)
 KanaVerb( およがせる ) // (v1) to let someone swim/to let someone go free
 KanaVerb( およぎだす ) // (v5s) to strike out/to start swimming
 KanaVerb( およぐ ) // (v5g,vi) to swim/(P)
 KanaVerb( えきまであるく ) // (v5k) to walk to the station
 KanaVerb( えっする ) // (vs-s) to have an audience with
 KanaVerb( まるでかこむ ) // (v5m) to enclose (a word) with a circle
 KanaVerb( えんげきづく ) // (v5k) to be absorbed in a play
 KanaVerb( えんづく ) // (v5k,vi) to marry
 KanaVerb( つやめく ) // (v5k,vi) to be charming/to be beautiful
 KanaVerb( とおすぎる ) // (v1) to be too far
 KanaVerb( とおのく ) // (v5k,vi) to become distant/to recede
 KanaVerb( よごれる ) // (v1,vi) to get dirty/to become dirty/(P)
 KanaVerb( へこませる ) // (v1) to dent/to indent/to depress/to humiliate
 KanaVerb( へこむ ) // (v5m) to be dented/to be indented/to yield to/to give/to sink/to collapse/to cave in/to be snubbed/(P)
 KanaVerb( おうじる ) // (v1,vi) to respond/to satisfy/to accept/to comply with/to apply for/(P)
 KanaVerb( おうずる ) // (vz,vi) to answer/to respond/to meet/to satisfy/to accept/(P)
 KanaVerb( おしつめる ) // (v1) to pack (in box)/to drive to wall
 KanaVerb( おしかためる ) // (v1) to press together
 KanaVerb( おしひろげる ) // (v1) to extend/to expand/to spread out
 KanaVerb( おしこむ ) // (v5m) to push into/to crowd into/(P)
 KanaVerb( おっぱじめる ) // (v1) to begin
 KanaVerb( おしかける ) // (v1,vi) to intrude on
 KanaVerb( おしよせる ) // (v1,vi) to push aside/to advance on
 KanaVerb( おしあう ) // (v5u,vi) to jostle/to crowd/to haggle
 KanaVerb( よこむく ) // (v5k) to turn sideways
 KanaVerb( なぐりあう ) // (v5u) to fight/to exchange blows
 KanaVerb( なぐりころす ) // (v5s) to strike dead/to beat to death
 KanaVerb( なぐりたおす ) // (v5s) to knock down
 KanaVerb( きばむ ) // (v5m,vi) to turn yellow
 KanaVerb( おくする ) // (vs-s) to fear/to feel timid
 KanaVerb( ぬるむ ) // (v5m) to cool off/to become tepid
 KanaVerb( おとをたてる ) // (v1) to make a sound
 KanaVerb( くださる ) // (v5aru) (hon) to give/to confer/(P)
 KanaVerb( したおす ) // (v5s) to decline (stock market)
 KanaVerb( げたをあずける ) // (v1) to leave everything to (someone)
 KanaVerb( げびる ) // (v1) to become vulgar/to coarsen
 KanaVerb( とつぐ ) // (v5g,vi) to marry/(P)
 KanaVerb( おおせる ) // (v1,vi) to succeed in doing
 KanaVerb( はたす ) // (v5s) to accomplish/to fulfill/to carry out/to achieve/(P)
 KanaVerb( はてる ) // (v1,vi) to end/to be finished/to be exhausted/to die/to perish/(P)
 KanaVerb( うたいあう ) // (v5u) to sing responsively
 KanaVerb( ひがつく ) // (v5k) to catch fire/to provoke/to catch fire from/to be ignited
 KanaVerb( ひでとける ) // (v1) to melt in the fire
 KanaVerb( かせぐ ) // (v5g,vi) to earn income/to labor/to labour/(P)
 KanaVerb( かせげる ) // (v1) to work/to earn income
 KanaVerb( はなさく ) // (v5k) to bloom
 KanaVerb( いらつく ) // (v5k,vi) (uk) to get irritated
 KanaVerb( いらだつ ) // (v5t) to be irritated
 KanaVerb( にもつをつめる ) // (v1) to pack one's things
 KanaVerb( はなやぐ ) // (v5g,vi) to become brilliant
 KanaVerb( すぎる ) // (v1,vi) to pass/to go beyond/to elapse/to exceed/(P)
 KanaVerb( あやまつ ) // (v5t,vi) to err
 KanaVerb( すぎいく ) // (v5k-s,vi) to pass/to go pass
 KanaVerb( すぎゆく ) // (v5k-s,vi) to pass/to go pass
 KanaVerb( かすむ ) // (v5m,vi) to grow hazy/to be misty/(P)
 KanaVerb( がをたてる ) // (v1) to insist on one's own ideas
 KanaVerb( わがいをえる ) // (v1) to approve of
 KanaVerb( かくする ) // (vs-s) to draw/to demarcate/to mark/to divide/to map out/(P)
 KanaVerb( ふしまろぶ ) // (v5b,vi) to fall and roll over/wriggle about
 KanaVerb( めぶく ) // (v5k,vi) to bud
 KanaVerb( めばえる ) // (v1,vi) to bud/to sprout
 KanaVerb( ほどける ) // (v1,vi) to come untied/to come apart/(P)
 KanaVerb( ほごす ) // (v5s) to unfasten
 KanaVerb( ほぐれる ) // (v1,vi) to come untied/to come apart
 KanaVerb( ほつれる ) // (v1,vi) to become frayed/to become loose
 KanaVerb( まわりだす ) // (v5s) to begin to turn
 KanaVerb( こわれる ) // (v1,vi) to be broken/to break/(P)
 KanaVerb( あけっぱなす ) // (v5s) to leave open
 KanaVerb( そとであそぶ ) // (v5b) to play outdoors
 KanaVerb( はずれる ) // (v1,vi) to be disconnected/to get out of place/to be off/to be out (e.g., of gear)/(P)
 KanaVerb( せきあげる ) // (v1,vi) to have a coughing fit/to sob convulsively
 KanaVerb( しわぶく ) // (v5k,vi) to cough
 KanaVerb( がいする ) // (vs-s) to injure/to damage/to harm/to kill/to hinder/(P)
 KanaVerb( おぼえる ) // (v1,vi) (1) to remember/to recollect/to memorize/to memorise/(2) to feel/(P)
 KanaVerb( つのめだつ ) // (v5t,vi) to be sharp/to be rough
 KanaVerb( かどだつ ) // (v5t) to be sharp/to be rough
 KanaVerb( まなぶ ) // (v5b) to study (in depth)/to learn/to take lessons in/(P)
 KanaVerb( たのしむ ) // (v5m) to enjoy oneself/(P)
 KanaVerb( たのしめる ) // (v1) to be able to enjoy
 KanaVerb( ぬかずく ) // (v5k) to make a deep bow
 KanaVerb( かかりあう ) // (v5u) to have dealings with/to be involved in
 KanaVerb( かけちがう ) // (v5u) to cross paths/to conflict
 KanaVerb( かけあわす ) // (v5s) to multiply/to cross breed
 KanaVerb( かけあわせる ) // (v1) to negotiate/to multiply/to cross breed
 KanaVerb( かけなおす ) // (v5s) to call again/to call someone back
 KanaVerb( かけあう ) // (v5u,vi) to negotiate with/to talk over with
 KanaVerb( わりではらう ) // (v5u) to split the account
 KanaVerb( わりきれる ) // (v1,vi) to be divisible (by)/to be divided without residue
 KanaVerb( われる ) // (v1,vi) to break/to split/to cleave/to fissure/to be smashed/to crack/to be torn/(P)
 KanaVerb( わりほぐす ) // (v5s) to beat (e.g., egg)/to whip (e.g., cream)
 KanaVerb( かっこつける ) // (v1) to affect a stylish air
 KanaVerb( くびれる ) // (v1,vi) to be constricted
 KanaVerb( かっきづく ) // (v5k) to become animated/to liven up/to become active
 KanaVerb( すべりおりる ) // (v1) to slide down (a hill) (e.g., ski, toboggan)
 KanaVerb( すべりこむ ) // (v5m,vi) to slide into (base)/to slip into (ditch)
 KanaVerb( すべりだす ) // (v5s) to begin slipping or sliding/to make a start upon
 KanaVerb( すべりおちる ) // (v1) to slip off
 KanaVerb( かつのみかつうたう ) // (v5u) to drink and sing at the same time/to drink as well as sing
 KanaVerb( かみあう ) // (v5u,vi) (1) to gear (engage) with/to be in gear (mesh)/(2) to bite each other
 KanaVerb( かみあわせる ) // (v1) (1) to clench (teeth)/to engage (gears)/(2) to set to fighting
 KanaVerb( かわく ) // (v5k,vi) to get dry/(P)
 KanaVerb( かせる ) // (v1) to dry up/to scab/to slough/to be poisoned (with lacquer)
 KanaVerb( からびる ) // (v1,vi) to dry up/to shrivel
 KanaVerb( かんむりをまげる ) // (v1) to become displeased/to get stubborn
 KanaVerb( まきおこす ) // (v5s) to create (a sensation)/to give rise to (controversy)
 KanaVerb( まきつく ) // (v5k) to twine around
 KanaVerb( わめきたてる ) // (v1) to yell/to bawl out
 KanaVerb( たまりかねる ) // (v1,vi) be unable to bear (something) any longer/to be unable to put up with (something) any longer
 KanaVerb( くつろぐ ) // (v5g) (uk) to relax/to feel at home/(P)
 KanaVerb( ひる ) // (v1,vi) to dry/(P)
 KanaVerb( ひからびる ) // (v1,vi) to dry up completely/to become stale
 KanaVerb( かんじる ) // (v1,vi) to feel/to sense/to experience/(P)
 KanaVerb( かんづく ) // (v5k,vi) (uk) to apprehend/to get an inkling (of something)/to smell (danger)
 KanaVerb( なれしたしむ ) // (v5m) to become familiar with/to get used to
 KanaVerb( あせばむ ) // (v5m,vi) to be sweaty
 KanaVerb( あせじみる ) // (v1,vi) to be sweat-stained
 KanaVerb( あまえる ) // (v1,vi) (1) to behave like a spoiled child/to behave like a spoilt child/to fawn on/(2) to depend and presume upon another's benevolence/(P)
 KanaVerb( あまくみる ) // (v1) to not take seriously/to take lightly
 KanaVerb( あまんじる ) // (v1,vi) to content oneself with/to be resigned to (one's fate)/to be contented (satisfied) with (one's lot)
 KanaVerb( ゆるむ ) // (v5m) to become loose/to slacken/(P)
 KanaVerb( かんたんあいてらす ) // (v5s) to be profoundly compatible/to be inseparable
 KanaVerb( まにあう ) // (v5u) (1) to be in time for/(2) to serve (suit, meet) the purpose/to be good enough/to be enough/(P)
 KanaVerb( まにあわせる ) // (v1) to make do/to manage (with something)/to make shift/(P)
 KanaVerb( まちがう ) // (v5u) to make a mistake/to be incorrect/to be mistaken/(P)
 KanaVerb( かんする ) // (vs-s) to concern/to be related/(P)
 KanaVerb( ふくます ) // (v5s) to soak/to saturate/to suckle/to make one hold something in the mouth/to include/to instruct/to make one understand
 KanaVerb( ふくまれる ) // (v1,vi) to be included/to be comprised of
 KanaVerb( ふくむ ) // (v5m) (1) to contain/to comprise/to have/to hold/to include/to embrace/(2) to hold in the mouth/(3) to bear in mind/to understand/(4) to harbor/to harbour/(P)
 KanaVerb( はにかむ ) // (v5m) (uk) to be shy/to be bashful
 KanaVerb( がんをたれる ) // (v1) to stare menacingly
 KanaVerb( かおからひがでる ) // (v1) to be extremely embarrassed/to burn with shame
 KanaVerb( かおをしかめる ) // (v1) to grimace/to frown
 KanaVerb( かおをあわせる ) // (v1) to meet/to face someone
 KanaVerb( かおをたてる ) // (v1) to save face
 KanaVerb( ねがいもとめる ) // (v1) to entreat
 KanaVerb( あやぶむ ) // (v5m) to fear/to have misgivings/to be doubtful/to mistrust/(P)
 KanaVerb( よろこばす ) // (v5s) to delight/to give pleasure/(P)
 KanaVerb( よろこびいさむ ) // (v5m,vi) to be in high spirits
 KanaVerb( よろこびうたう ) // (v5u) to rejoice and sing
 KanaVerb( もとづく ) // (v5k,vi) to be grounded on/to be based on/to be due to/to originate from
 KanaVerb( よせかける ) // (v1,vi) to rest or lean against
 KanaVerb( よりあう ) // (v5u,vi) to gather/to meet
 KanaVerb( よりそう ) // (v5u,vi) to get close/to cuddle close together/to nestle close to/to snuggle up to
 KanaVerb( よりつく ) // (v5k,vi) to approach
 KanaVerb( きす ) // (v5s) to expect/to look forward to
 KanaVerb( きする ) // (vs-s) to return to/to come to/to be attributed to
 KanaVerb( かえってくる ) // (vk) to return/to come back
 KanaVerb( かえりつく ) // (v5k,vi) to arrive home/to return
 KanaVerb( かえれる ) // (v1) to get out/to go home
 KanaVerb( きがひける ) // (v1) to feel awkward/to feel shy
 KanaVerb( きがつく ) // (v5k) (1) to notice/to become aware/to perceive/to realize/to realise/(2) to recover consciousness/to come to oneself
 KanaVerb( きをとられる ) // (v1) to have one's attention attracted (caught)/to be preoccupied with
 KanaVerb( けおされる ) // (v1,vi) to be overawed (overpowered)
 KanaVerb( きちがいじみる ) // (v1,vi) to go mad
 KanaVerb( きづかう ) // (v5u,vi) to worry about/to feel anxious about/to have apprehensions of
 KanaVerb( けしきばむ ) // (v5m,vi) to grow angry/to display one's anger
 KanaVerb( かぶれる ) // (v1,vi) to react to/to be influenced by/to go overboard for
 KanaVerb( きづく ) // (v5k) to notice/to recognize/to recognise/to become aware of/to perceive/to realize/to realise/(P)
 KanaVerb( きおいたつ ) // (v5t) to rouse oneself/to psyche oneself up
 KanaVerb( きおう ) // (v5u,vi) to get worked up/to be eager (enthusiastic)/to rouse oneself
 KanaVerb( しるす ) // (v5s) to note/to write down/(P)
 KanaVerb( きごうであらわす ) // (v5s) to represent by signs
 KanaVerb( おこりうる ) // (v5uru) to be possible to occur
 KanaVerb( かがやく ) // (v5k) to shine/to glitter/to sparkle/(P)
 KanaVerb( かつえる ) // (v1,vi) to be starved/to be hungry
 KanaVerb( いつわりちかう ) // (v5u) to swear falsely
 KanaVerb( そばえる ) // (v1,vi) to play pranks/to be spoiled/to be spoilt
 KanaVerb( おどける ) // (v1,vi) to jest/to joke/to play the fool/to act indecently/to be silly over/to talk foolishly
 KanaVerb( たわける ) // (v1,vi) to jest/to joke/to play the fool/to act indecently/to be silly over/to talk foolishly
 KanaVerb( ざれる ) // (v1,vi) (1) to be playful/to gambol/to be amused (with something)/to play/to sport/to frolic/to joke/(2) to flirt with
 KanaVerb( たわむれる ) // (v1,vi) (1) to be playful/to gambol/to be amused (with something)/to play/to sport/to frolic/to joke/(2) to flirt with/(P)
 KanaVerb( ざれかわす ) // (v5s) to exchange jokes
 KanaVerb( あざむきまどわす ) // (v5s) to deceive and lead astray
 KanaVerb( きっする ) // (vs-s) to take/to drink/to suffer (e.g., defeat)/to receive a blow/(P)
 KanaVerb( つまらせる ) // (v1) to make shorter/(P)
 KanaVerb( つめる ) // (v1) (1) to pack/to fill/(2) to shorten/(3) to work out (details)/(P)
 KanaVerb( つめかける ) // (v1,vi) to crowd (a house)/to throng to (a door)
 KanaVerb( さからう ) // (v5u,vi) to go against/to oppose/to disobey/to defy/(P)
 KanaVerb( さかまく ) // (v5k,vi) surging water or waves
 KanaVerb( のぼせる ) // (v1,vi) to feel dizzy/to have blood rush to one's head/to become conceited/(P)
 KanaVerb( さかだつ ) // (v5t) to stand up/to oppose
 KanaVerb( やすませる ) // (v1) to excuse (someone)/to give a holiday to/to make (someone) rest
 KanaVerb( やすむ ) // (v5m,vi) to rest/to have a break/to take a day off/to be finished/to be absent/to retire/to sleep/(P)
 KanaVerb( やすらう ) // (v5u) to rest/to relax
 KanaVerb( およぶ ) // (v5b,vi) to reach/to come up to/to amount to/to befall/to happen to/to extend/to match/to equal/(P)
 KanaVerb( すいつく ) // (v5k) to stick to
 KanaVerb( せかす ) // (v5s) to hurry/to urge on/(P)
 KanaVerb( いそがせる ) // (v1) to hasten (the work)/to urge (a person) on
 KanaVerb( せきたてられる ) // (v1) to be hurried/to be hastened/to be hard pressed
 KanaVerb( いそぐ ) // (v5g,vi) to hurry/to rush/(P)
 KanaVerb( せきこむ ) // (v5m,vi) to sound agitated, hurried, flustered/to be impatient
 KanaVerb( すくいあげる ) // (v1) to pick up and rescue
 KanaVerb( くちはてる ) // (v1,vi) to rust away/to rot away/to decay/to fall to ruins/to die in obscurity
 KanaVerb( なきやむ ) // (v5m) to stop crying/to cry oneself out
 KanaVerb( なきとおす ) // (v5s) to keep crying
 KanaVerb( なきぬれる ) // (v1,vi) to be tear-stained
 KanaVerb( なきわめく ) // (v5k) to cry/to scream
 KanaVerb( なきさけぶ ) // (v5b,vi) to cry and shout/to scream
 KanaVerb( なきだす ) // (v5s,vi) to burst into tears/to burst out crying/to begin to cry/to be moved to tears
 KanaVerb( なきしずむ ) // (v5m,vi) to abandon oneself to grief
 KanaVerb( なきつぶす ) // (v5s) to cry one's eyes out/to weep oneself blind
 KanaVerb( なきつく ) // (v5k,vi) to cling to .. in tears/to beg .. in tears/to appeal/to throw oneself on someone's mercy
 KanaVerb( なきふす ) // (v5s,vi) to break down crying
 KanaVerb( なきくずれる ) // (v1,vi) to break down crying
 KanaVerb( なきおとす ) // (v5s) to persuade by tears/to use tears to get one's way
 KanaVerb( きゅうする ) // (vs-s) (1) (arch) to be hard pressed/to be at a loss/(2) to become poor/to be reduced to poverty
 KanaVerb( あざなう ) // (v5u) to twist (something)
 KanaVerb( いあわせる ) // (v1) to happen to be present/(P)
 KanaVerb( いつづける ) // (v1) to stay on (e.g., at one's friends house)/to remain in the same neighborhood
 KanaVerb( いならぶ ) // (v5b,vi) to sit in a row/to be arrayed
 KanaVerb( あげられる ) // (v1) (comp) to be arrested/to be caught/to be captured (e.g. data)
 KanaVerb( むなしく ) // (v5k) in vain/to no purpose/fruitlessly
 KanaVerb( きそいあう ) // (v5u) to compete with/to vie for
 KanaVerb( きそう ) // (v5u,vi) to emulate/to compete with/(P)
 KanaVerb( せりあう ) // (v5u,vi) to struggle for/to compete with/to vie with/(P)
 KanaVerb( せりおとす ) // (v5s) to knock down the price of
 KanaVerb( せりかつ ) // (v5t,vi) to win after tough bidding
 KanaVerb( わめく ) // (v5k,vi) (uk) to shout/to cry/to scream/to clamour
 KanaVerb( さけびだす ) // (v5s) to let out a cry/to break forth
 KanaVerb( さけぶ ) // (v5b,vi) to shout/to cry/(P)
 KanaVerb( ひるむ ) // (v5m,vi) (uk) to falter/to flinch (from)/to recoil (from)/to quail (at)
 KanaVerb( おそれる ) // (v1,vi) to fear/to be afraid of/(P)
 KanaVerb( おそれおののく ) // (v5k) to tremble with fear
 KanaVerb( おしえさとす ) // (v5s) to give guidance
 KanaVerb( くるいざく ) // (v5k) to bloom out of season
 KanaVerb( くるう ) // (v5u,vi) to go mad/to get out of order/(P)
 KanaVerb( くるわす ) // (v5s) to drive mad/to put out of order/(P)
 KanaVerb( ためなおす ) // (v5s) to set up again/to correct/to cure
 KanaVerb( おびえる ) // (v1,vi) to become frightened/to have a nightmare
 KanaVerb( おどしつける ) // (v1) to threaten/to terrify/to frighten
 KanaVerb( きょうじる ) // (v1,vi) to amuse oneself/to make merry
 KanaVerb( きょうざめる ) // (v1,vi) to lose interest
 KanaVerb( ひびく ) // (v5k,vi) to resound/(P)
 KanaVerb( どよめく ) // (v5k) to resound/to make a stir/(P)
 KanaVerb( おどろかされる ) // (v1) to be surprised/(P)
 KanaVerb( おおせられる ) // (v1) (pol) to say/to state
 KanaVerb( あおのく ) // (v5k) to look up
 KanaVerb( あおむく ) // (v5k) to look upward
 KanaVerb( きわめつくす ) // (v5s) to do thoroughly/to check through and through
 KanaVerb( きょくりょくつとめる ) // (v1) to do one's best
 KanaVerb( つとめおこなう ) // (v5u) to carry on (work)
 KanaVerb( つとめはたらく ) // (v5k) to work diligently
 KanaVerb( ちかづく ) // (v5k) to approach/to get near/to get acquainted with/to get closer/(P)
 KanaVerb( くるしむ ) // (v5m,vi) to suffer/to groan/to be worried/(P)
 KanaVerb( くろうしぬく ) // (v5k) to go through all sorts of hardships
 KanaVerb( かけおりる ) // (v1) to run down
 KanaVerb( かけこむ ) // (v5m,vi) to rush in (at the last minute)/to stampede
 KanaVerb( かけぬける ) // (v1,vi) to run past from behind/to run through (e.g., gate)
 KanaVerb( かけつける ) // (v1,vi) to run to/to come running/to rush (someplace)/to hasten
 KanaVerb( かけだす ) // (v5s,vi) to run off/to break into a run/to start running
 KanaVerb( ぐずつく ) // (v5k) to dawdle/to fret/to sulk/to complain/to waste time doing nothing in particular
 KanaVerb( うつける ) // (v1,vi) (1) to become empty (hollow)/(2) to relax from a tense situation into a vacant or absent minded state
 KanaVerb( そらとぼける ) // (v1,vi) to feign ignorance
 KanaVerb( そらとぶ ) // (v5b) to fly in the sky
 KanaVerb( そらうそぶく ) // (v5k,vi) to feign ignorance or unconcern
 KanaVerb( ぐうする ) // (vs-s) to entertain/to treat
 KanaVerb( くっする ) // (vs-s) to yield/to bend/to be daunted/to shrink
 KanaVerb( かがみこむ ) // (v5m,vi) to lean over/to lean in
 KanaVerb( かがむ ) // (v5m) to stoop/to lean over
 KanaVerb( くぼむ ) // (v5m) to cave in/to sink
 KanaVerb( くりあわす ) // (v5s) to make time/to arrange matters
 KanaVerb( くりあわせる ) // (v1) to arrange/to manage (to find time)
 KanaVerb( くりかえす ) // (v5s,vi) to repeat/to do something over again
 KanaVerb( むれあそぶ ) // (v5b) to play in a group
 KanaVerb( むれいる ) // (v1,vi) to crowd in/to come together
 KanaVerb( かかわりあう ) // (v5u) to get involved or entangled in/to get mixed up in/to have something to do with/to have dealings with
 KanaVerb( かたぶく ) // (v5k) to incline toward/to slant/to lurch/to heel over/to be disposed to/to trend toward/to be prone to/to go down (sun)/to wane/to sink/to decline
 KanaVerb( かたむく ) // (v5k) to incline toward/to slant/to lurch/to heel over/to be disposed to/to trend toward/to be prone to/to go down (sun)/to wane/to sink/to decline/(P)
 KanaVerb( かしぐ ) // (v5g,vi) to lean/to incline/to tilt/to list/to tip/to careen/to lurch/to incline toward/to slant/to heed over/to be disposed to/to trend toward/to be prone to/to go down (sun)/to wane/to sink/to decline
 KanaVerb( かたぐ ) // (v5g,vi) to lean/to incline/to tilt/to list/to tip/to careen/to lurch/to incline toward/to slant/to heed over/to be disposed to/to trend toward/to be prone to/to go down (sun)/to wane/to sink/to decline
 KanaVerb( かたむけたおす ) // (v5s) to cast down/to lay low
 KanaVerb( なだれる ) // (v1,vi) to slope/to descend/to slide (snow, etc.)
 KanaVerb( なだれおちる ) // (v1) to slide down (snow, etc.)
 KanaVerb( かたにはめる ) // (v1) to stereotype/to squeeze into a pattern/to regiment
 KanaVerb( めぐまれる ) // (v1,vi) to be blessed with/to be rich in/(P)
 KanaVerb( よろこぶ ) // (v5b,vi) to be delighted/to be glad
 KanaVerb( いこう ) // (v5u) to rest/to relax/to repose/(P)
 KanaVerb( けいする ) // (vs-s) to respect
 KanaVerb( つなぎあわせる ) // (v1) to join or tie or knot together
 KanaVerb( はかられる ) // (v1) to be taken in
 KanaVerb( けたあげる ) // (v1) (comp) to carry (of digit, bit, etc.)
 KanaVerb( けっする ) // (vs-s) to decide/to determine/(P)
 KanaVerb( きめつける ) // (v1) to scold/to take (a person) to task/(P)
 KanaVerb( あなをあける ) // (v1) to cause a loss
 KanaVerb( むすびつく ) // (v5k) to be connected or related/to join together
 KanaVerb( むすぶ ) // (v5b) to tie/to bind/to link/(P)
 KanaVerb( けつろんづける ) // (v1) to reason/to sum up/to conclude
 KanaVerb( ちまよう ) // (v5u,vi) to lose one's mind/to lose control of oneself
 KanaVerb( つましくくらす ) // (v5s) to live frugally
 KanaVerb( あぐねる ) // (v1) (uk) to tire of/to lose interest in
 KanaVerb( うみつかれる ) // (v1) to grow weary/to get tired of
 KanaVerb( あぐむ ) // (v5m,vi) to get tired of (doing)/to lose interest in
 KanaVerb( かねつかえる ) // (v1) to serve at the same time
 KanaVerb( たてまわす ) // (v5s) to build around
 KanaVerb( かけはなれる ) // (v1,vi) to be very far apart from/to be remote/to be quite different from
 KanaVerb( まくれる ) // (v1,vi) to be (get) turned up (inside out)
 KanaVerb( めくれる ) // (v1,vi) to be (get) turned up (inside out)
 KanaVerb( かたをすくめる ) // (v1) to shrug one's shoulders
 KanaVerb( かたをいからせる ) // (v1) to perk up (square) one's shoulders
 KanaVerb( かたよせる ) // (v1) to be (standing) together, an arm across the other's shoulder
 KanaVerb( まみえる ) // (v1,vi) (1) (arch) to have an audience/to meet (humble)/to face/(2) to act as a wife for
 KanaVerb( みえる ) // (v1,vi) to be seen/to be in sight/to look/to seem/to appear/(P)
 KanaVerb( みえすく ) // (v5k,vi) to be transparent
 KanaVerb( みかわす ) // (v5s) to exchange glances
 KanaVerb( みむく ) // (v5k,vi) to look around/to look towards (us)
 KanaVerb( みあう ) // (v5u) (1) to exchange glances/(2) to correspond/to counterbalance
 KanaVerb( みあわせる ) // (v1) to exchange glances/to postpone/to suspend operations/to refrain from performing an action/(P)
 KanaVerb( みほれる ) // (v1,vi) to be fascinated (by)/to watch something in fascination/to be charmed
 KanaVerb( みつくす ) // (v5s) to see everything
 KanaVerb( みつづける ) // (v1) to gaze away
 KanaVerb( みそこねる ) // (v1) to miss seeing
 KanaVerb( みなおす ) // (v5s) to look again/to get a better opinion of/(P)
 KanaVerb( みとれる ) // (v1,vi) to be fascinated (by)/to watch something in fascination/to be charmed
 KanaVerb( みなれる ) // (v1,vi) to become used to seeing/to be familiar with
 KanaVerb( みあきる ) // (v1,vi) to be tired of looking at
 KanaVerb( やっていく ) // (v5k-s) to live/to make a living/to get on with
 KanaVerb( やられる ) // (v1) (uk) to suffer damage/to be deceived
 KanaVerb( やりすぎる ) // (v1) to overdo/to go too far/to go to excess
 KanaVerb( やりそこなう ) // (v5u) to fail
 KanaVerb( やりとおす ) // (v5s) to carry through/to achieve/to complete
 KanaVerb( げんきすぎる ) // (v1) to be too energetic
 KanaVerb( げんきづく ) // (v5k) to get encouraged/to become heightened in spirits/to recover one's strength
 KanaVerb( めりこむ ) // (v5m,vi) to sink into/to cave in
 KanaVerb( げんずる ) // (vz,vi) to appear/to reveal/to show
 KanaVerb( あらわれでる ) // (v1) to appear
 KanaVerb( いう ) // (v5u) to say/(P)
 KanaVerb( ゆう ) // (v5u) to say/(P)
 KanaVerb( いいすごす ) // (v5s) to talk or say too much/to go too far/to overstate/to exaggerate
 KanaVerb( いいあらためる ) // (v1) to correct oneself
 KanaVerb( いいかけてやめる ) // (v1) to stop in the middle of a sentence
 KanaVerb( いいまるめる ) // (v1) to do sweet-talk
 KanaVerb( いいおよぶ ) // (v5b,vi) to refer to/to mention (e.g., theme)
 KanaVerb( いいふるす ) // (v5s) to say repeatedly or proverbially
 KanaVerb( いいかわす ) // (v5s) to exchange words or promises/to promise
 KanaVerb( いいあわせる ) // (v1) to agree in advance
 KanaVerb( いいさす ) // (v5s) to break off (in middle of sentence)
 KanaVerb( いいつくす ) // (v5s) to tell all/to give a full account
 KanaVerb( いいそこなう ) // (v5u) to say by mistake/to make a slip of the tongue
 KanaVerb( いいきかす ) // (v5s) to tell someone to do something/to warm/to persuade/to instruct
 KanaVerb( いいくらす ) // (v5s) to pass the time talking
 KanaVerb( いいわすれる ) // (v1) to forget to mention or say
 KanaVerb( ふるくみせる ) // (v1) to impart an ancient appearance
 KanaVerb( ふるびる ) // (v1,vi) to look old/to get old
 KanaVerb( ふるびおとろえる ) // (v1) to waste away
 KanaVerb( ふるぼける ) // (v1,vi) (uk) to look old/to become musty/to wear out
 KanaVerb( よばれる ) // (v1,vi) (1) to be treated to something/(2) to be called (a name)/to be referred to (as)
 KanaVerb( よびなれる ) // (v1) to be used to calling (someone by a certain name)
 KanaVerb( よびおこす ) // (v5s) to call (to mind)/to wake
 KanaVerb( よびかわす ) // (v5s) to call each other's names
 KanaVerb( よびこむ ) // (v5m) to call in/to restore a disowned son
 KanaVerb( かたくいましめる ) // (v1) to admonish sternly
 KanaVerb( とまどう ) // (v5u,vi) to be bewildered/to be perplexed/(P)
 KanaVerb( またぐ ) // (v5g) to straddle/(P)
 KanaVerb( あとへひく ) // (v5k) to retreat/to recede
 KanaVerb( ござる ) // (v5aru,vi) (pol) to be
 KanaVerb( ございる ) // (v1) to be (very pol.)
 KanaVerb( かたりかける ) // (v1) to make a speech/to address
 KanaVerb( ごまかす ) // (v5s) to deceive/to falsify/to misrepresent/(P)
 KanaVerb( ひかりかがやく ) // (v5k,vi) to shine/to glitter/(P)
 KanaVerb( くちをいれる ) // (v1) to throw in a suggestion
 KanaVerb( くちをつける ) // (v1) to taste/to try (food or drink)
 KanaVerb( くどきおとす ) // (v5s) to persuade/to prevail upon/to win a woman's heart/to win over/to talk someone into doing
 KanaVerb( くちづける ) // (v1) to kiss
 KanaVerb( むかいあう ) // (v5u,vi) to be opposite/to face each other
 KanaVerb( むかいあわせる ) // (v1) to face/to confront/to be opposite to
 KanaVerb( むかう ) // (v5u,vi) (1) to face/(2) to go towards/(P)
 KanaVerb( むきあう ) // (v5u,vi) to be opposite/to face each other
 KanaVerb( むけかえる ) // (v1) to change direction
 KanaVerb( むこうからくる ) // (vk) to come from the opposite direction
 KanaVerb( むこうでくらす ) // (v5s) to live overseas
 KanaVerb( あかぬける ) // (v1) to refine
 KanaVerb( あわてふためく ) // (v5k,vi) to get into a panic/to be flustered/to panic/to get in a flap
 KanaVerb( あわてる ) // (v1,vi) to become confused (disconcerted, disorganized, disorganised)/(P)
 KanaVerb( かかずらう ) // (v5u) (1) (uk) to be mixed up with/to have a connection with (a troublesome matter)/(2) to be a stickler about/to be finicky about (some triviality)/(3) to take part (in some work)/to hang about/to bother (someone)
 KanaVerb( ひかえる ) // (v1) to draw in/to hold back/to make notes/to be temperate in/(P)
 KanaVerb( せめよせる ) // (v1,vi) to make an onslaught (on)/to close in (on)
 KanaVerb( せめあぐねる ) // (v1) to be at a loss how to continue/to become disheartened
 KanaVerb( せめあぐむ ) // (v5m,vi) to lose the attacking initiative
 KanaVerb( せめこむ ) // (v5m,vi) to invade/to attack
 KanaVerb( せめおとす ) // (v5s) to assault
 KanaVerb( かまう ) // (v5u) to mind/to care about/to be concerned about/(P)
 KanaVerb( しぼりこむ ) // (v5m) (1) to squeeze/to wring out/(2) to narrow down/to refine
 KanaVerb( かんがえあぐねる ) // (v1) to be at a loss/to think and think but get nowhere/to fail to come up with a good idea
 KanaVerb( かんがえこむ ) // (v5m,vi) to ponder/to brood
 KanaVerb( かんがえだす ) // (v5s) to think out/to devise/to invent/to begin to think/to come up with a plan
 KanaVerb( かんがえぬく ) // (v5k) to think thoroughly
 KanaVerb( すさむ ) // (v5m) to grow wild/to run to waste
 KanaVerb( あれる ) // (v1,vi) to be stormy/to be rough/to lose one's temper/(P)
 KanaVerb( あれくるう ) // (v5u,vi) to rage/to get angry
 KanaVerb( あれはてる ) // (v1,vi) to fall into ruin/to be desolated
 KanaVerb( あらだつ ) // (v5t) to be(come) rough or aggravated or worse
 KanaVerb( いきちがう ) // (v5u,vi) (1) to cross (each other)/to pass (each other)/(2) to misunderstand/to go amiss
 KanaVerb( ゆきちがう ) // (v5u,vi) (1) to cross (each other)/to pass (each other)/(2) to misunderstand/to go amiss
 KanaVerb( いきすぎる ) // (v1,vi) to go too far/to go to extremes/(P)
 KanaVerb( いきあう ) // (v5u) to meet somebody by chance
 KanaVerb( いきかう ) // (v5u,vi) to come and go/to go back and forth
 KanaVerb( ゆきかう ) // (v5u,vi) to come and go/to go back and forth
 KanaVerb( いきあわせる ) // (v1) to happen to meet
 KanaVerb( いきはじめる ) // (v1) to get going/to start off
 KanaVerb( ゆきつく ) // (v5k,vi) to arrive at/to end up
 KanaVerb( いきとどく ) // (v5k,vi) to be scrupulous/to be attentive/to be prudent/to be complete/to be thorough/(P)
 KanaVerb( ゆきとどく ) // (v5k,vi) to be scrupulous/to be attentive/to be prudent/to be complete/to be thorough
 KanaVerb( ゆきなやむ ) // (v5m,vi) to reach an impasse or deadlock
 KanaVerb( ゆきくれる ) // (v1,vi) to be overtaken by darkness
 KanaVerb( おこなう ) // (v5u) to perform/to do/to conduct oneself/to carry out
 KanaVerb( おこなわれる ) // (v1) to be done/to be practiced/to be practised/to take place/to be held/to prevail
 KanaVerb( ふってわく ) // (v5k) to happen suddenly/to take place unexpectedly
 KanaVerb( おりる ) // (v1,vi) to alight (e.g., from bus)/to get off/to descend (e.g., a mountain)/(P)
 KanaVerb( ふりはじめる ) // (v1) to begin to fall
 KanaVerb( ふりやむ ) // (v5m,vi) to stop raining or snowing
 KanaVerb( ふりつづく ) // (v5k,vi) to continue to rain or snow
 KanaVerb( ふりそそぐ ) // (v5g,vi) to rain incessantly/to downpour
 KanaVerb( ふりしく ) // (v5k,vi) to be covered with
 KanaVerb( おりたつ ) // (v5t,vi) (1) to go down and stand/(2) to alight/to get down
 KanaVerb( うなだれる ) // (v1,vi) to hang one's head
 KanaVerb( がっする ) // (vs-s,vi) to join together/to sum up/to combine/to unite/to mix/to agree with
 KanaVerb( あわす ) // (v5s) to join together/to face/to unite/to be opposite/to combine/to connect/to add up/to mix/to match/to overlap/to compare/to check with/(P)
 KanaVerb( あわせおこなう ) // (v5u) to carry on together/to do at the same time
 KanaVerb( とどろく ) // (v5k,vi) to roar
 KanaVerb( きざみだす ) // (v5s) to carve out
 KanaVerb( くろずむ ) // (v5m,vi) to blacken/to darken
 KanaVerb( くろばむ ) // (v5m,vi) to blacken/to become black
 KanaVerb( こしかける ) // (v1,vi) to sit (down)/(P)
 KanaVerb( ほれる ) // (v1,vi) to fall in love/to be in love/to be charmed with/to lose one's heart to/(P)
 KanaVerb( ほれこむ ) // (v5m,vi) to be charmed by
 KanaVerb( のろける ) // (v1,vi) to play up/to speak fondly of/to praise one's spouse
 KanaVerb( ほねがおれる ) // (v1) to require much effort/to be hard to do/to have one's bones broken
 KanaVerb( こつをおぼえる ) // (v1) to learn the ropes/to get the knack
 KanaVerb( こみあげる ) // (v1,vi) (1) to feel nauseous/(2) to fill (one's heart)/to experience a welling up of feelings or sensations
 KanaVerb( いまめかす ) // (v5s) to modernize/to modernise
 KanaVerb( こまらせる ) // (v1) to trouble with questions/to embarrass/to put out/to put on the spot/to inconvenience
 KanaVerb( こまりはてる ) // (v1,vi) to be greatly perplexed/to be greatly embarrassed/(P)
 KanaVerb( こまりぬく ) // (v5k,vi) to be at one's wit's end/to be in great trouble/to be at a loss
 KanaVerb( こんなんとたたかう ) // (v5u) to contend with difficulties
 KanaVerb( ねざす ) // (v5s,vi) to root in/to come from
 KanaVerb( まじりあう ) // (v5u) to be mixed together/to be blended
 KanaVerb( まぜっかえす ) // (v5s) to mix in/to stir (up)/to interfere
 KanaVerb( まぜあわす ) // (v5s) mix together/blend/compound/(P)
 KanaVerb( まぜかえす ) // (v5s) to banter/to make fun of (what a person says)/to stir up/to jeer at
 KanaVerb( こむ ) // (v5m,vi) (1) to be crowded/(2) to go inside (usu. only when used in compound verbs)/(P)
 KanaVerb( こみあう ) // (v5u,vi) to be crowded/to be packed/to be jammed
 KanaVerb( こんとんとしている ) // (v1) to be chaotic
 KanaVerb( たまげる ) // (v1,vi) to be astonished/to be startled/to be appalled
 KanaVerb( ひだりにおれる ) // (v1) to turn to the left
 KanaVerb( さしひく ) // (v5k) to deduct
 KanaVerb( さしこえる ) // (v1) to go out of turn/to butt in
 KanaVerb( さしこす ) // (v5s,vi) to go out of turn/to send
 KanaVerb( さしひびく ) // (v5k,vi) to influence/to affect
 KanaVerb( さしむかう ) // (v5u,vi) (obsc) to be face to face
 KanaVerb( さしつかえる ) // (v1,vi) to interfere/to hinder/to become impeded/(P)
 KanaVerb( さしでる ) // (v1,vi) to go forward/to stick one's nose into
 KanaVerb( すわりこむ ) // (v5m,vi) to sit down (and bask)/to sit-in (in protest)
 KanaVerb( くじく ) // (v5k) to crush/to break/to sprain
 KanaVerb( くじける ) // (v1,vi) to be crushed/to be broken/to be sprained
 KanaVerb( ふたたびのべる ) // (v1) to restate
 KanaVerb( ふたたびよむ ) // (v5m) to reread/to read again
 KanaVerb( ふさぎこむ ) // (v5m,vi) to mope
 KanaVerb( さいはじける ) // (v1,vi) to be presumptuous/to be clever and forward
 KanaVerb( くだける ) // (v1,vi) to break/to be broken/(P)
 KanaVerb( いつく ) // (v5k,vi) to worship/enshrine
 KanaVerb( いむ ) // (v5m,vi) to avoid/to refrain from/to shun
 KanaVerb( たちかける ) // (v1) to begin to cut
 KanaVerb( たちだす ) // (v5s) to cut out (a dress) from cloth
 KanaVerb( たちぬう ) // (v5u) to cut and sew
 KanaVerb( さいする ) // (vs-s) to arrive/to come to pass
 KanaVerb( きわだつ ) // (v5t) to be prominent/to be conspicuous/(P)
 KanaVerb( つみする ) // (vs-s) to charge/to sentence/to punish
 KanaVerb( さえかがやく ) // (v5k) to shine clearly
 KanaVerb( さえゆく ) // (v5k-s,vi) to clear gradually/to get cold gradually
 KanaVerb( さきこぼれる ) // (v1,vi) to bloom all over
 KanaVerb( さきだす ) // (v5s,vi) to begin to bloom/to come out
 KanaVerb( さきそめる ) // (v1,vi) to begin to blossom
 KanaVerb( さきそろう ) // (v5u,vi) to be in full bloom
 KanaVerb( さきにおう ) // (v5u,vi) to be in full bloom
 KanaVerb( さきみだれる ) // (v1,vi) to bloom in profusion/(P)
 KanaVerb( つくりそんじる ) // (v1) to fail in making
 KanaVerb( つくりぞこなう ) // (v5u) to fail in making
 KanaVerb( つくりかえす ) // (v5s) to remake
 KanaVerb( さっかとしてならす ) // (v5s) to be very popular as a writer
 KanaVerb( けずりおとす ) // (v5s) to scrape off/to plane off
 KanaVerb( けずれる ) // (v1) to be shaved or planed
 KanaVerb( すぼむ ) // (v5m,vi) to get narrower/to contract
 KanaVerb( すりそこなう ) // (v5u) to misprint/to spoil in printing
 KanaVerb( すりなおす ) // (v5s) to reprint (book)
 KanaVerb( さっする ) // (vs-s) to guess/to sense/to presume/to judge/to sympathize with/to sympathise with/(P)
 KanaVerb( すりむく ) // (v5k) to skin (one's knee)/to graze
 KanaVerb( すりむける ) // (v1,vi) to abrade
 KanaVerb( すりぬける ) // (v1,vi) to slip through/to make one's way through quickly
 KanaVerb( こすりおとす ) // (v5s) to scrape off/to rub off
 KanaVerb( すれちがう ) // (v5u,vi) to pass by one another/to disagree/to miss each other
 KanaVerb( すれあう ) // (v5u,vi) to rub against/to chafe/to quarrel
 KanaVerb( そぐ ) // (v5g) (1) to chip/to slice off/to sharpen/(2) to thin down/to reduce/to weaken
 KanaVerb( そげる ) // (v1,vi) to split/to be split/to splinter
 KanaVerb( さっきだつ ) // (v5t,vi) to be seething (with anger)/to be frenzied/to be menacing
 KanaVerb( さばく ) // (v5k) to handle/to sell
 KanaVerb( さばける ) // (v1,vi) to be in order/to sell well/to be sociable/to flow smoothly
 KanaVerb( さびる ) // (v1,vi) to rust/to become rusty/(P)
 KanaVerb( さびつく ) // (v5k,vi) to rust together
 KanaVerb( さんるいでさされる ) // (v1) to be put (thrown) out at third base
 KanaVerb( まいらせる ) // (v1) to beat/to floor (someone)/to bring (someone) to his knees/to come
 KanaVerb( ばらける ) // (v1,vi) to unravel
 KanaVerb( ちりしく ) // (v5k,vi) to lie scattered or strewn about
 KanaVerb( ちりみだれる ) // (v1,vi) to be or lay scattered
 KanaVerb( さんけづく ) // (v5k) to go into labor/to go into labour
 KanaVerb( しかねる ) // (v1) to be unable to do/to hesitate/to be reluctant
 KanaVerb( しこむ ) // (v5m) to train/to teach/to educate/to stock/to prepare
 KanaVerb( しすます ) // (v5s) to succeed as planned
 KanaVerb( しはじめる ) // (v1) to begin/to start
 KanaVerb( しそこなう ) // (v5u) to blunder/to fail/to make a mistake/to miss
 KanaVerb( しなおす ) // (v5s) to do over/to remake/to resume
 KanaVerb( しなれる ) // (v1) to be used to doing/to be experienced in
 KanaVerb( つかいはたす ) // (v5s) to use up/to squander
 KanaVerb( つかいすぎる ) // (v1) to use excessively/to use too much/to spend too much/to overwork someone
 KanaVerb( つかいならす ) // (v5s) to accustom oneself to using/to train/to break in (horses)
 KanaVerb( つかいなれる ) // (v1) to get accustomed to using
 KanaVerb( つかいこなす ) // (v5s) to handle/to manage
 KanaVerb( つかいだす ) // (v5s) to start using/to try out
 KanaVerb( つかいつくす ) // (v5s) to use up/to squander
 KanaVerb( さされる ) // (v1) to be stabbed
 KanaVerb( しとあおぐ ) // (v5g) to look up to (a person) as one's preceptor
 KanaVerb( こころざす ) // (v5s,vi) to plan/to intend/to aspire to/to set aims (sights on)/(P)
 KanaVerb( おもいおよぶ ) // (v5b,vi) to hit upon something
 KanaVerb( おもいあぐねる ) // (v1) to think something over and over/to rack one's brains/to be at a loss
 KanaVerb( おもいあう ) // (v5u,vi) to love one another
 KanaVerb( おもいあわせる ) // (v1) to consider all the circumstances
 KanaVerb( おもいこむ ) // (v5m,vi) to be under impression that/to be convinced that/to imagine that/to set one's heart on/to be bent on/(P)
 KanaVerb( おもいこがれる ) // (v1,vi) to pine for
 KanaVerb( おもいわずらう ) // (v5u,vi) to worry about/to be vexed
 KanaVerb( おもいつく ) // (v5k) to think of/to hit upon/to come into one's mind/to be struck with an idea/(P)
 KanaVerb( おもいうかぶ ) // (v5b) to occur to/to remind of
 KanaVerb( おもいうかべる ) // (v1) to be reminded of/to call to mind
 KanaVerb( おもいみだれる ) // (v1,vi) to be worried about
 KanaVerb( おもいまどう ) // (v5u,vi) to be at a loss
 KanaVerb( おもえる ) // (v1) to seem/to appear likely
 KanaVerb( おもわせる ) // (v1) to make somebody believe (something)/to give somebody the impression
 KanaVerb( おもわれる ) // (v1) to seem/to appear
 KanaVerb( ゆびおりかぞえる ) // (v1) to count on one's fingers
 KanaVerb( しどうしゃとしていただく ) // (v5k) to have (a person) as one's leader
 KanaVerb( ししてのちやむ ) // (v5m) to be determined to do or die
 KanaVerb( しにかける ) // (v1) to be dying/to be about to die/to be close to death
 KanaVerb( しにいそぐ ) // (v5g,vi) to hasten one's death
 KanaVerb( しにおくれる ) // (v1,vi) to outlive
 KanaVerb( しにたえる ) // (v1,vi) to die out/to become extinct
 KanaVerb( しにそこなう ) // (v5u) to fail to die/to survive/to outlive
 KanaVerb( しにわかれる ) // (v1,vi) to be separated by death
 KanaVerb( しぬ ) // (v5n,vi) to die/(P)
 KanaVerb( しぬまでたたかう ) // (v5u) to fight to the last (death)
 KanaVerb( わたくしする ) // (vs-s) to think only of oneself/to possess oneself
 KanaVerb( しけんではねられる ) // (v1) to get flunked in an examination
 KanaVerb( たまう ) // (v5u) to grant/to bestow/to award
 KanaVerb( かいならす ) // (v5s) to tame/to domesticate
 KanaVerb( ことかく ) // (v5k,vi) to lack
 KanaVerb( こときれる ) // (v1,vi) to expire/to die
 KanaVerb( ことたりる ) // (v1,vi) to suffice/to serve the purpose/to be satisfied
 KanaVerb( ことだてる ) // (v1) to do something different/to make a big thing of
 KanaVerb( にあう ) // (v5u,vi) to suit/to match/to become/to be like/(P)
 KanaVerb( にかよう ) // (v5u,vi) to resemble closely/(P)
 KanaVerb( につく ) // (v5k,vi) to become/to suit/to be like/to match well
 KanaVerb( もちつづける ) // (v1) to persist in
 KanaVerb( もちあるく ) // (v5k) to carry
 KanaVerb( もってくる ) // (vk) to bring/(P)
 KanaVerb( もつ ) // (v5t) (1) to hold/to carry/(2) to possess/(P)
 KanaVerb( もてる ) // (v1,vi) (1) to be well liked/to be popular/to be welcomed/(2) to possess riches/to be wealthy/(P)
 KanaVerb( もてはやす ) // (v5s) to praise extravagantly/to lionize/to lionise/to make much of
 KanaVerb( ときめく ) // (v5k,vi) to be prosperous/to prosper/to flourish/to enjoy great prosperity
 KanaVerb( じきにさしかける ) // (v1) to get close to the time
 KanaVerb( しめしあわす ) // (v5s) to conspire (with)/to prearrange
 KanaVerb( みみがこえている ) // (v1) to have an ear for music
 KanaVerb( みみなれる ) // (v1,vi) to be something familiar
 KanaVerb( うぬぼれる ) // (v1,vi) to be conceited/(P)
 KanaVerb( じぶんできめる ) // (v1) to decide by oneself
 KanaVerb( じす ) // (v5s) to resign/to leave post/(P)
 KanaVerb( じする ) // (vs-s) to resign (post)/to excuse oneself/to take one's leave
 KanaVerb( しかられる ) // (v1) to be scolded (reproved)
 KanaVerb( しっする ) // (vs-s) to lose/to miss/to forget/to be excessive
 KanaVerb( うせる ) // (v1,vi) to disappear/to vanish
 KanaVerb( しちにいれる ) // (v1) to pawn/to pledge
 KanaVerb( さしこむ ) // (v5m,vi) to shine in (light)/to illuminate
 KanaVerb( いころす ) // (v5s) to shoot a person to death
 KanaVerb( いそこなう ) // (v5u) to shoot and miss
 KanaVerb( いぬく ) // (v5k) to shoot through
 KanaVerb( いおとす ) // (v5s) to shoot down/to win/to gain
 KanaVerb( すてておく ) // (v5k) to leave something as it is
 KanaVerb( にえる ) // (v1,vi) to boil/to cook/to be cooked/(P)
 KanaVerb( にえたつ ) // (v5t,vi) to boil/to come to a boil
 KanaVerb( にやす ) // (v5s) to cook inside/(P)
 KanaVerb( にこむ ) // (v5m,vi) to cook together/to boil well/(P)
 KanaVerb( にたつ ) // (v5t,vi) to boil or simmer
 KanaVerb( にこぼれる ) // (v1,vi) to boil over
 KanaVerb( しゃする ) // (vs-s) (1) to thank/(2) to apologize/to apologise/(3) to say farewell/to retreat/to retire/(4) to refuse/(5) to pay back/to settle old scores
 KanaVerb( かりこす ) // (v5s) to overdraw
 KanaVerb( かりこむ ) // (v5m) to borrow
 KanaVerb( しゃっきんでくるしむ ) // (v5m) to be distressed with debts
 KanaVerb( くみかわす ) // (v5s) to drink together
 KanaVerb( わかくみえる ) // (v1) to look (seem) young
 KanaVerb( さびれる ) // (v1,vi) to decline/to fall (down)
 KanaVerb( よわりはてる ) // (v1,vi) to be exhausted/to be at a loss/to be worn out/to be helpless
 KanaVerb( よわりこむ ) // (v5m) to weaken/to be at wits' end
 KanaVerb( よわりおとろえる ) // (v1) to languish
 KanaVerb( ひきつける ) // (v1) to attract/to charm
 KanaVerb( とってかえす ) // (v5s,vi) to return
 KanaVerb( とってくる ) // (vk) to fetch/to go and get
 KanaVerb( とっくみあう ) // (v5u,vi) to come to grips with/to fight
 KanaVerb( とりいそぐ ) // (v5g,vi) to hurry/to hasten
 KanaVerb( とりかわす ) // (v5s) to exchange/to interchange
 KanaVerb( とりあう ) // (v5u,vi) (1) to take each other's hands/to clasp (hands)/(2) to compete/to scramble for/(3) to respond
 KanaVerb( とりあわせる ) // (v1) to put together/to assemble
 KanaVerb( とりこむ ) // (v5m) to take in/to capture (e.g. image)/to introduce/to be busy/to be confused
 KanaVerb( とりつくす ) // (v5s) to deplete/to take all
 KanaVerb( とりすます ) // (v5s,vi) to look unconcerned/to assume a composed look
 KanaVerb( とっくむ ) // (v5m,vi) to tackle/to wrestle with/to engage in a bout/to come to grips with/to make effort/to strive for
 KanaVerb( とりくむ ) // (v5m,vi) to tackle/to wrestle with/to engage in a bout/to come to grips with/to make effort/to strive for
 KanaVerb( とりつかれる ) // (v1) to become obsessed with/to be possessed (by spirits, etc.)
 KanaVerb( とっつく ) // (v5k,vi) to cling to/to grapple with/to possess/to stick to
 KanaVerb( とりつく ) // (v5k,vi) to cling to/to grapple with/to possess/to stick to
 KanaVerb( とりまぎれる ) // (v1,vi) to be in confusion/to be busy
 KanaVerb( とりおとす ) // (v5s) to drop/to let fall/to omit
 KanaVerb( とりみだす ) // (v5s,vi) to scatter about/to be distracted
 KanaVerb( とりこぼす ) // (v5s,vi) (1) (comp) to lose an easy game/to suffer an unexpected defeat/(2) to lose information (computers)
 KanaVerb( とりこめる ) // (v1) to shut in/to confine/to surround
 KanaVerb( てにいれる ) // (v1,vi) to obtain/to procure
 KanaVerb( てむかう ) // (v5u,vi) to resist
 KanaVerb( てまねく ) // (v5k) to beckon
 KanaVerb( てつだってきせる ) // (v1) to help (a person) dress
 KanaVerb( しゅひつをくわえる ) // (v1) to make corrections
 KanaVerb( かりたてる ) // (v1) to hunt down
 KanaVerb( くびをちぢめる ) // (v1) to duck one's head
 KanaVerb( うけてたつ ) // (v5t) to accept somebody's challenge/to take up the gauntlet
 KanaVerb( うけわたす ) // (v5s) to deliver/to hand over/to transfer
 KanaVerb( じゅぎょうをうける ) // (v1) to take a class
 KanaVerb( ひろいあつめる ) // (v1) to gather
 KanaVerb( ひろいあげる ) // (v1) to pick up/to pick out
 KanaVerb( ひいでる ) // (v1,vi) to excel/to surpass/(P)
 KanaVerb( あきめく ) // (v5k,vi) to become autumnal
 KanaVerb( おそいせめる ) // (v1) to array against
 KanaVerb( けりこむ ) // (v5m) to kick in
 KanaVerb( けりころす ) // (v5s) to kick to death
 KanaVerb( けりあげる ) // (v1) to kick up/to fling up
 KanaVerb( つどう ) // (v5u) to meet/to assemble/to congregate/(P)
 KanaVerb( あつめはじめる ) // (v1) to begin to catch (attention, etc.)
 KanaVerb( じゅうする ) // (vs-s) to live/to reside/to inhabit
 KanaVerb( すまう ) // (v5u,vi) to live/to reside/to inhabit/(P)
 KanaVerb( すみなれる ) // (v1) to get used to living in
 KanaVerb( すみこむ ) // (v5m,vi) to be a live-in employee/to live in/to live with
 KanaVerb( すみつく ) // (v5k,vi) to settle down
 KanaVerb( みちみちている ) // (v1) to be filled with/to be pregnant with/to teem with
 KanaVerb( したがう ) // (v5u,vi) to abide (by the rules)/to obey/to follow/to accompany/(P)
 KanaVerb( かさなりあう ) // (v5u) to lie on top of each other/to overlap/to pile up
 KanaVerb( かさねかける ) // (v1) to lap/to overlap
 KanaVerb( かさねあわせる ) // (v1) to overlap
 KanaVerb( おもすぎる ) // (v1) to be too heavy
 KanaVerb( おもだつ ) // (v5t,vi) main/principal/important/conspicuous/prominent
 KanaVerb( やどす ) // (v5s,vi) (1) to keep (guest)/(2) to conceive/(3) to carry (virus)/(P)
 KanaVerb( ちぢむ ) // (v5m,vi) to shrink/to be contracted/(P)
 KanaVerb( ちぢれる ) // (v1,vi) to be wavy/to be curled/(P)
 KanaVerb( じゅくする ) // (vs-s) to ripen/to get ripe/to mature/to be in common use/to come to sound natural
 KanaVerb( こなれる ) // (v1,vi) to be digested/to be mellowed
 KanaVerb( でくわす ) // (v5s) to happen to meet/to come across
 KanaVerb( だしっぱなす ) // (v5s) to leave on/to leave running/to leave lying around/to leave (a faucet) open
 KanaVerb( だしちがう ) // (v5u) to miss sending/to miss delivering
 KanaVerb( だしすぎる ) // (v1) to overdo something (speed, exertion, etc.)
 KanaVerb( だしはなす ) // (v5s) to leave on/to leave running/to leave lying around/to leave (a faucet) open
 KanaVerb( いでたつ ) // (v5t,vi) to start/to leave
 KanaVerb( でちがう ) // (v5u,vi) to miss a visitor
 KanaVerb( ですぎる ) // (v1,vi) to project or protrude too much/to be too forward/to obtrude
 KanaVerb( ではずれる ) // (v1,vi) to be or lie just outside of
 KanaVerb( でかける ) // (v1,vi) to depart/to go out (e.g., on an excursion or outing)/to set out/to start/to be going out/(P)
 KanaVerb( でむく ) // (v5k,vi) to go to/to proceed to/to leave for/(P)
 KanaVerb( であう ) // (v5u,vi) to meet by chance/to come across/to happen to encounter/to hold a rendezvous/to have a date/(P)
 KanaVerb( ではじめる ) // (v1) to begin to appear/to begin to come in
 KanaVerb( でつくす ) // (v5s) to be all out/to exhaust
 KanaVerb( でそろう ) // (v5u,vi) to appear all together/to be all present
 KanaVerb( でそこなう ) // (v5u) to fail to go/to fail to come
 KanaVerb( でおくれる ) // (v1,vi) to get a late start/(P)
 KanaVerb( でなおす ) // (v5s,vi) to come again/to call again/to make a fresh start
 KanaVerb( ではらう ) // (v5u,vi) to be all out
 KanaVerb( であるく ) // (v5k,vi) to go out/to take a stroll/to go about
 KanaVerb( できる ) // (v1,vi) (1) (uk) to be able (in a position) to do/to be up to the task/(2) to be ready/to be completed/(3) to be made/to be built/(4) to be good at/to be permitted (to do)/(5) to become intimate/to take up (with somebody)/(6) to grow/to be raised/(P)
 KanaVerb( できすぎる ) // (v1,vi) to be too much/to be too good to be true
 KanaVerb( できあう ) // (v5u,vi) to be ready-made/to become intimate with
 KanaVerb( できそこなう ) // (v5u) to be badly made/to fail
 KanaVerb( のべたてる ) // (v1) to relate at great length/to dwell eloquently (on)
 KanaVerb( はるめく ) // (v5k,vi) to become spring-like/to show signs of spring
 KanaVerb( じゅんじる ) // (v1,vi) to follow/to conform/to apply to/(P)
 KanaVerb( じゅんずる ) // (vz,vi) to apply correspondingly/to correspond to/to be proportionate to/to conform to/(P)
 KanaVerb( うるおう ) // (v5u,vi) to be moist/to be damp/to get wet/to profit by/to be watered/to receive benefits/to favor/to favour/to charm/to steepen/(P)
 KanaVerb( ふやける ) // (v1,vi) (uk) to become sodden/to swell up
 KanaVerb( うるむ ) // (v5m,vi) to be clouded/to be dimmed/to be bleared/to be wet/to get muddy/(P)
 KanaVerb( たてつく ) // (v5k,vi) to oppose/to resist/to defy
 KanaVerb( めぐりあう ) // (v5u) to meet fortuitously (poet)/to meet by chance/to happen across
 KanaVerb( めぐりあるく ) // (v5k) to walk around/to travel around
 KanaVerb( しょする ) // (vs-s) to manage/to deal with/to cope with
 KanaVerb( かきちがえる ) // (v1) to miswrite
 KanaVerb( かきつくす ) // (v5s) to write down or convey in full
 KanaVerb( かきそこなう ) // (v5u) to miswrite
 KanaVerb( かきまちがえる ) // (v1) to write incorrectly (e.g. character)/to make a mistake in writing
 KanaVerb( たすけあう ) // (v5u,vi) to help each other/to cooperate/(P)
 KanaVerb( たすけだす ) // (v5s) to help out of (trouble)/to extricate
 KanaVerb( たすけあげる ) // (v1) to help up/to pick up/to bring safely to land
 KanaVerb( すきおこす ) // (v5s) to turn over soil/to dig or plow up (plough)
 KanaVerb( きずつく ) // (v5k) to be hurt/to be wounded/to get injured/(P)
 KanaVerb( かちっぱなす ) // (v5s) to win consecutive/to have a long winning streak
 KanaVerb( かちこす ) // (v5s,vi) to have more wins than losses/to lead (someone) by (three) matches/(P)
 KanaVerb( かちすすむ ) // (v5m,vi) to win and advance to the next round
 KanaVerb( かちとおす ) // (v5s) to win straight victories
 KanaVerb( かちぬく ) // (v5k,vi) to win through
 KanaVerb( かちはなす ) // (v5s,vi) to win continuously
 KanaVerb( かつ ) // (v5t,vi) to win/to gain victory/(P)
 KanaVerb( めしあつめる ) // (v1) to call together
 KanaVerb( こもどす ) // (v5s) to rally a little (e.g., market)
 KanaVerb( すこしのそんですむ ) // (v5m) to get off with a little loss
 KanaVerb( しょうちづく ) // (v5k) to act on mutual agreement
 KanaVerb( まねきいれる ) // (v1) to invite in/to show someone in
 KanaVerb( きえる ) // (v1,vi) to go out/to vanish/to disappear/(P)
 KanaVerb( きえはてる ) // (v1,vi) to vanish completely
 KanaVerb( きえうせる ) // (v1,vi) (X) (vulg) to disappear/to get out of sight/to die/(in imperative) to fuck off
 KanaVerb( けしとぶ ) // (v5b,vi) to scatter away
 KanaVerb( やきころす ) // (v5s) to kill by burning to death
 KanaVerb( やきつくす ) // (v5s) to thoroughly burn/to burn to nothing
 KanaVerb( やける ) // (v1,vi) to burn/to be roasted/to be sunburnt/(P)
 KanaVerb( やけしぬ ) // (v5n,vi) to be burnt to death
 KanaVerb( やけうせる ) // (v1,vi) to burn up completely
 KanaVerb( やけだされる ) // (v1,vi) to be burned out (of one's home)
 KanaVerb( やけつく ) // (v5k,vi) to burn
 KanaVerb( やけおちる ) // (v1,vi) to be burned down
 KanaVerb( やきつく ) // (v5k) to scorch
 KanaVerb( こがれる ) // (v1) to yearn for/to be in love with
 KanaVerb( こげつく ) // (v5k,vi) to get burned and stuck on/to become uncollectable (and remain unpaid)
 KanaVerb( てらしあわせる ) // (v1) to check/to compare
 KanaVerb( てりはえる ) // (v1,vi) to shine/to glow
 KanaVerb( てりかがやく ) // (v5k,vi) to shine brilliantly
 KanaVerb( てりこむ ) // (v5m,vi) to shine into or upon
 KanaVerb( てりかえす ) // (v5s,vi) to reflect/to throw back light
 KanaVerb( てれる ) // (v1,vi) to be shy/to feel awkward/(P)
 KanaVerb( てりつける ) // (v1,vi) to blaze down on/to beat down on/to shine down upon
 KanaVerb( わらいかける ) // (v1) to smile/to grin
 KanaVerb( わらいだす ) // (v5s) to burst into laughter
 KanaVerb( わらいこける ) // (v1,vi) to laugh heartily
 KanaVerb( えみわれる ) // (v1,vi) to crack
 KanaVerb( えむ ) // (v5m,vi) to smile
 KanaVerb( めかしこむ ) // (v5m,vi) to dress oneself up/to deck oneself out
 KanaVerb( めかす ) // (v5s) (1) (uk) to adorn oneself/to dress oneself up/(aux-v) (2) to give an air of/to make oneself seem like
 KanaVerb( くわしくのべる ) // (v1) to expound
 KanaVerb( あがりこむ ) // (v5m,vi) to enter/to step in
 KanaVerb( うわぐむ ) // (v5m) to draw off the top liquid
 KanaVerb( うわがれる ) // (v1) to die at the top
 KanaVerb( うえむく ) // (v5k,vi) to look upward/to turn upward/to rise
 KanaVerb( うわむく ) // (v5k,vi) to look upward/to turn upward/to rise
 KanaVerb( うまくいく ) // (v5k-s) to go smoothly/to turn out well/to do the trick/to have peaceful relations
 KanaVerb( のりこなす ) // (v5s) to manage (a horse)
 KanaVerb( のりうつす ) // (v5s) to transfer (a stowaway)
 KanaVerb( のりこえる ) // (v1,vi) to climb over/to ride across/to surmount/(P)
 KanaVerb( のりすごす ) // (v5s) to ride past
 KanaVerb( のりあわす ) // (v5s,vi) to happen to ride together/to share a vehicle
 KanaVerb( のりあわせる ) // (v1) to happen to ride together/to share a vehicle/to (operate a) carpool
 KanaVerb( のりこむ ) // (v5m,vi) (1) to board/to embark on/to get into (a car)/to ship (passengers)/to man (a ship)/to help (someone) into/(2) to march into/to enter/(P)
 KanaVerb( のりすすめる ) // (v1) to ride forth
 KanaVerb( のりくむ ) // (v5m,vi) to get on aboard/to join a ship
 KanaVerb( のりそこなう ) // (v5u) to miss (a train)
 KanaVerb( のりおくれる ) // (v1,vi) to miss (train, bus, etc)/(P)
 KanaVerb( のりつぶす ) // (v5s) to ride (a horse) to death
 KanaVerb( のりとばす ) // (v5s) to tear along (a road)
 KanaVerb( のりつける ) // (v1,vi) to ride up to/to get used to riding
 KanaVerb( のりもどす ) // (v5s) to ride (a horse) back/to drive (a car) back
 KanaVerb( むれる ) // (v1,vi) to be stuffy/to moulder/to molder
 KanaVerb( うえかえる ) // (v1) to transplant/to reset
 KanaVerb( いろめきたつ ) // (v5t,vi) to become excited
 KanaVerb( いろめく ) // (v5k,vi) to colour/to color/to be tinged/to brighten/to grow lively/to become excited/to be stirred
 KanaVerb( いろめがねでみる ) // (v1) to look at things from a biased viewpoint (biassed)
 KanaVerb( いろづく ) // (v5k,vi) to change color/to change colour
 KanaVerb( いろあせる ) // (v1,vi) to fade/to grow stale/to grow dull in color (colour)
 KanaVerb( いろざめる ) // (v1) to fade in color/to fade in colour
 KanaVerb( ふれあう ) // (v5u) to come into contact with/to touch (each other)/(P)
 KanaVerb( くいっぱぐれる ) // (v1) to miss a meal/to lose the means to make one's livelihood
 KanaVerb( くいはぐれる ) // (v1,vi) to miss a meal/to lose the means to make one's livelihood
 KanaVerb( くいつなぐ ) // (v5g,vi) (1) to ration out and survive on (some food)/(2) to eke out a living
 KanaVerb( くいあう ) // (v5u) to fit together
 KanaVerb( くいあわす ) // (v5s) to clench
 KanaVerb( くいこむ ) // (v5m,vi) to eat into/(P)
 KanaVerb( くいのばす ) // (v5s) to keep alive on/to stretch food to make ends meet
 KanaVerb( くいつくす ) // (v5s) to consume
 KanaVerb( しょくする ) // (vs-s) to eat
 KanaVerb( たべちらす ) // (v5s) to eat a bit of everything
 KanaVerb( たべつくす ) // (v5s) to eat up
 KanaVerb( はみだす ) // (v5s,vi) (1) to be forced out/be crowded out/(2) to jut out (of bounds)/(P)
 KanaVerb( はみでる ) // (v1,vi) (1) to jut out (of bounds)/(2) to be crowded out/to to be forced out/(P)
 KanaVerb( くらいこむ ) // (v5m,vi) to be sent up/to be imprisoned/to be jailed/to be gaoled
 KanaVerb( くらいつく ) // (v5k,vi) (1) to bite at/to snap at/to nibble/(2) to hold with the teeth/to cling to
 KanaVerb( くらわす ) // (v5s) to make someone eat/to deal (a blow)/to play (a trick)
 KanaVerb( くわす ) // (v5s) (1) to feed/(2) to provide/(3) to inflict/(4) to cheat
 KanaVerb( くいちがう ) // (v5u,vi) to cross each other/to run counter to/to differ/to clash/to go awry/(P)
 KanaVerb( くいつく ) // (v5k,vi) (1) to bite at/to snap at/to nibble/(2) to hold with the teeth/to cling to
 KanaVerb( のしあるく ) // (v5k,vi) to swagger
 KanaVerb( のす ) // (v5s) to stretch/to spread/to smooth out/to roll out/to iron/to extend/to gain influence/to knock out
 KanaVerb( のびる ) // (v1,vi) (1) to stretch/to extend/to lengthen/to spread/(v1,vi) (2) to make progress/to grow (beard, body height)/(v1,vi) (3) to grow stale (soba)/(v1,vi) (4) to be straightened/to be flattened/to be smoothed/(v1,vi) (5) to be exhausted/(P)
 KanaVerb( のびなやむ ) // (v5m,vi) to be sluggish (business)/(P)
 KanaVerb( しんじこます ) // (v5s) to lead to believe
 KanaVerb( しんじこむ ) // (v5m) to believe implicitly/to believe firmly
 KanaVerb( ねかす ) // (v5s) to put to sleep/to lay (something) on its side/(P)
 KanaVerb( ねちがえる ) // (v1,vi) to sleep in an awkward position and wake with a crick in one's neck
 KanaVerb( ねすぎる ) // (v1,vi) to oversleep
 KanaVerb( ねすごす ) // (v5s) to oversleep/(P)
 KanaVerb( ねざめる ) // (v1) to wake up
 KanaVerb( ねぼける ) // (v1,vi) to be half asleep/to be still only half awake
 KanaVerb( ねこむ ) // (v5m,vi) to stay in bed/to sleep/to be laid up for a long time
 KanaVerb( ねそこなう ) // (v5u) to miss a chance to sleep/to be wakeful
 KanaVerb( ねなおす ) // (v5s) to go back to bed
 KanaVerb( ねころぶ ) // (v5b,vi) (uk) to lie down/to throw oneself down/(P)
 KanaVerb( ねつく ) // (v5k,vi) (1) to go to bed/to go to sleep/to fall asleep/(2) to be laid up (with a cold)/to be ill in bed/(P)
 KanaVerb( ねつけす ) // (v5s) to put (someone) to bed
 KanaVerb( ねわすれる ) // (v1,vi) to oversleep
 KanaVerb( こころする ) // (vs-s) to take care/to mind/to be attentive
 KanaVerb( こころをとらえる ) // (v1) to impress/to charm
 KanaVerb( こころゆく ) // (v5k-s,vi) to be completely satisfied or contented
 KanaVerb( ふられる ) // (v1,vi) to give someone the cold shoulder/to be jilted/to be rejected
 KanaVerb( ふりおろす ) // (v5s) to swing downward
 KanaVerb( ふりおこす ) // (v5s) to stir up/to stimulate
 KanaVerb( ふりあおぐ ) // (v5g,vi) to look up
 KanaVerb( ふりむく ) // (v5k) to turn one's face/to turn around/(P)
 KanaVerb( ふりこむ ) // (v5m) to make a payment via bank deposit transfer/(P)
 KanaVerb( ふりかえす ) // (v5s) to relapse/to reassert
 KanaVerb( ふれる ) // (v1,vi) to lean towards/to deflect/to shake/to swing/to wave
 KanaVerb( もうしひらく ) // (v5k) to explain/to justify
 KanaVerb( もうしかねる ) // (v1) I'm sorry to trouble you
 KanaVerb( もうしあわせる ) // (v1) to arrange/to make an appointment/to agree upon
 KanaVerb( もうしおくれる ) // (v1) to be slow in saying
 KanaVerb( しんでかく ) // (v5k) to write in the square style
 KanaVerb( したしむ ) // (v5m,vi) to be intimate with/to befriend/(P)
 KanaVerb( みる ) // (v1) to examine (medical)/(P)
 KanaVerb( みじろぐ ) // (v5g,vi) to stir/to move
 KanaVerb( みにしみる ) // (v1) to sink deeply into one's mind/to come home to/to go to one's heart
 KanaVerb( みをかがめる ) // (v1) to stoop/to bend over
 KanaVerb( みをよせあう ) // (v5u) to go into a huddle
 KanaVerb( みをとうじる ) // (v1) to throw oneself (into an activity)
 KanaVerb( みがまえる ) // (v1,vi) to put oneself on guard/to stand ready/to square off
 KanaVerb( みぶりでしめす ) // (v5s) to express by gestures
 KanaVerb( すすみでる ) // (v1,vi) to step forward/to volunteer
 KanaVerb( はりでさす ) // (v5s) to prick with a needle
 KanaVerb( ふるいつく ) // (v5k,vi) to hug
 KanaVerb( ふるえだす ) // (v5s) to begin to tremble
 KanaVerb( しんかんさせる ) // (v1) to shock/to shake
 KanaVerb( ひといちばいはたらく ) // (v5k) to work twice as hard as others
 KanaVerb( ひとなれる ) // (v1,vi) to become accustomed to people
 KanaVerb( はむかう ) // (v5u,vi) to strike back at/to bite back/to turn on/to rise against/to oppose/to defy
 KanaVerb( つきる ) // (v1,vi) to be used up/to be run out/to be exhausted/to be consumed/to come to an end/(P)
 KanaVerb( つきはてる ) // (v1,vi) to be exhausted
 KanaVerb( つくす ) // (v5s) (1) to exhaust/to run out/(2) to devote/to serve (a person)/to befriend/(P)
 KanaVerb( ふきおろす ) // (v5s,vi) to blow down upon
 KanaVerb( ふきすさぶ ) // (v5b,vi) to blow fiercely/to rage
 KanaVerb( ふきすさむ ) // (v5m) to blow violently
 KanaVerb( ふきあれる ) // (v1,vi) to blow violently/to sweep over/to devastate
 KanaVerb( ふきこむ ) // (v5m) to blow into/to breathe into/to inspire/to lay down a recording (music, video, etc.)/to indoctrinate/(P)
 KanaVerb( ふきはじめる ) // (v1) to begin to blow
 KanaVerb( ふきぬく ) // (v5k) to blow through/to blow over/to blow itself out
 KanaVerb( ふきぬける ) // (v1) to blow through
 KanaVerb( ふきとぶ ) // (v5b,vi) to be blown off/to blow off/(P)
 KanaVerb( ふきかえす ) // (v5s) to blow in the opposite direction/to revive
 KanaVerb( ふきおとす ) // (v5s) to blow down (fruit)
 KanaVerb( ふっきれる ) // (v1,vi) to break through/to become unbound by/to ooze out
 KanaVerb( ふっとぶ ) // (v5b,vi) to blow off/to be blown off
 KanaVerb( たれる ) // (v1,vi) (1) to hang/to droop/to dangle/to sag/to lower/to pull down/(2) to leave behind (at death)/to give/to confer/(3) to drip/to ooze/to trickle/to drop/(P)
 KanaVerb( たれながす ) // (v5s) to discharge (e.g., effluent)
 KanaVerb( たれこめる ) // (v1) to hang over (e.g., clouds)/to lie over
 KanaVerb( みずでうすめる ) // (v1) to water down/to dilute with water
 KanaVerb( みずぎわだつ ) // (v5t,vi) to be splendid/to be superb
 KanaVerb( おとろえる ) // (v1,vi) to become weak/to decline/to wear/to abate/to decay/to wither/to waste away/(P)
 KanaVerb( おとろえはてる ) // (v1,vi) to be utterly spent or crushed
 KanaVerb( よいしれる ) // (v1,vi) to be befuddled (drunk, intoxicated) (with)
 KanaVerb( よいつぶれる ) // (v1,vi) to drink oneself dead drunk
 KanaVerb( よう ) // (v5u,vi) to get drunk/to become intoxicated/(P)
 KanaVerb( よっぱらう ) // (v5u,vi) to get drunk/(P)
 KanaVerb( あがまう ) // (v5u) to look up to/to respect
 KanaVerb( かさむ ) // (v5m,vi) to pile up/to increase
 KanaVerb( かぞえちがえる ) // (v1) to miscount/to count wrongly (e.g., pages)
 KanaVerb( かぞえこむ ) // (v5m) to number among
 KanaVerb( かぞえなおす ) // (v5s) to count again
 KanaVerb( かずにいれる ) // (v1) to count/to include in the number
 KanaVerb( よにでる ) // (v1) to become famous
 KanaVerb( よにたつ ) // (v5t) to become famous
 KanaVerb( よなれる ) // (v1,vi) to become used to the (ways of the) world/to become worldly or sophisticated
 KanaVerb( すごむ ) // (v5m,vi) to threaten
 KanaVerb( いきおいこむ ) // (v5m,vi) to brace oneself
 KanaVerb( いきおいづく ) // (v5k,vi) to gather strength/to take heart
 KanaVerb( なりこむ ) // (v5m) to incorporate (shoji)
 KanaVerb( なりすます ) // (v5s,vi) to pose as/to impersonate
 KanaVerb( なりはてる ) // (v1,vi) to be reduced to ..
 KanaVerb( しょうきづく ) // (v5k) to become conscious/to recover one's senses
 KanaVerb( すむ ) // (v5m,vi) to clear (e.g., weather)/to become transparent
 KanaVerb( せいだくあわせのむ ) // (v5m) to be broad-minded enough to associate with various types of people/to possess a capacious mind
 KanaVerb( はえる ) // (v1,vi) (1) to grow/to spring up/(2) to cut (teeth)/(P)
 KanaVerb( いきていく ) // (v5k-s) to subsist
 KanaVerb( いきる ) // (v1,vi) to live/to exist/(P)
 KanaVerb( いきのびる ) // (v1,vi) to survive/to live long
 KanaVerb( いきながらえる ) // (v1,vi) to live long/to survive
 KanaVerb( いきぬく ) // (v5k,vi) to live through/to survive
 KanaVerb( いきうめる ) // (v1) to bury (somebody) alive
 KanaVerb( しょうじる ) // (v1,vi) to produce/to yield/to result from/to arise/to be generated/(P)
 KanaVerb( きでのむ ) // (v5m) to drink (whisky, whiskey) straight
 KanaVerb( うまれあわせる ) // (v1) to happen to be born
 KanaVerb( うまれおちる ) // (v1) to be born
 KanaVerb( うまれる ) // (v1,vi) to be born
 KanaVerb( うまれつく ) // (v5k,vi) (1) to be born/(2) to be destined
 KanaVerb( もりあわせる ) // (v1) to heap with/to assort
 KanaVerb( せいだす ) // (v5s,vi) to exert oneself
 KanaVerb( こえをかける ) // (v1) to greet/to call out to someone
 KanaVerb( こえをたてる ) // (v1) to let out a cry/to shout
 KanaVerb( せいする ) // (vs-s) to make (something)
 KanaVerb( ちかいかわす ) // (v5s) to vow to each other
 KanaVerb( ゆく ) // (v5k-s,vi) to die/to pass away
 KanaVerb( あおざめる ) // (v1,vi) to become pale/to turn pale
 KanaVerb( むかしをかえりみる ) // (v1) to look back upon the past
 KanaVerb( つみおろす ) // (v5s) to unload
 KanaVerb( つみすぎる ) // (v1) to overload
 KanaVerb( せめさいなむ ) // (v5m) to torture
 KanaVerb( あかちゃける ) // (v1,vi) to turn reddish-brown/to turn rufous/to become discolored/to become discoloured
 KanaVerb( きりすぎる ) // (v1) to overcut
 KanaVerb( きりひろげる ) // (v1) to cut and enlarge
 KanaVerb( きりおこす ) // (v5s) to open up waste land for cultivation
 KanaVerb( きりむすぶ ) // (v5b,vi) to cross swords with
 KanaVerb( きりからす ) // (v5s) to destroy/to kill off (trees)
 KanaVerb( きりあう ) // (v5u,vi) to fight with swords/to cross swords
 KanaVerb( きりこむ ) // (v5m,vi) to cut into/to raid/to attack/to cut up
 KanaVerb( きりのける ) // (v1) to cut off/to cut out
 KanaVerb( きりすえる ) // (v1) to cut down an enemy
 KanaVerb( きりひらく ) // (v5k) to open up
 KanaVerb( きりなおす ) // (v5s) to correct cutting/to reshuffle (playing cards)
 KanaVerb( きりいれる ) // (v1) to cut and insert
 KanaVerb( きりぬく ) // (v5k) to cut out/to clip from/to extract
 KanaVerb( きりわかつ ) // (v5t) to cut up
 KanaVerb( きりわける ) // (v1) to cut up/to cut and discard/to eliminate systematically (in fault-finding)
 KanaVerb( きりはなれる ) // (v1) to cut off and separate
 KanaVerb( きりたつ ) // (v5t) to rise perpendicularly
 KanaVerb( きれる ) // (v1,vi) (1) to cut well/to be sharp/(2) to break (off)/to snap/to wear out/(3) to be injured/(4) to burst/to collapse/(5) to be disconnected/to be out of/to expire/to sever (connections) with/(6) to be shrewd/to have a sharp mind/(P)
 KanaVerb( きれこむ ) // (v5m,vi) to cut into
 KanaVerb( きりかく ) // (v5k) to (cut a) notch (in)
 KanaVerb( はぎあわせる ) // (v1) to join or patch together
 KanaVerb( おりあう ) // (v5u,vi) to compromise
 KanaVerb( おれる ) // (v1,vi) to break/to be folded/to give in/to turn (a corner)/(P)
 KanaVerb( おれあう ) // (v5u,vi) to get along with/to compromise/to make concessions/to come to an agreement
 KanaVerb( おれこむ ) // (v5m,vi) to be folded under or inside
 KanaVerb( ふしくれだつ ) // (v5t,vi) to be knotty or gnarled
 KanaVerb( ときおこす ) // (v5s) to begin one's argument or story or lecture
 KanaVerb( ときおよぶ ) // (v5b,vi) to mention/to refer to/to touch upon
 KanaVerb( ときいだす ) // (v5s,vi) to begin to speak/to begin to explain
 KanaVerb( ゆきでおおわれる ) // (v1) to be covered with snow
 KanaVerb( なだれこむ ) // (v5m,vi) to rush or crowd into/to surge into
 KanaVerb( たえはてる ) // (v1,vi) to be extinguished/to be exterminated/to cease completely
 KanaVerb( ぜっする ) // (vs-s) to be unspeakable/to be unimaginable
 KanaVerb( さきんじる ) // (v1,vi) to precede/to forestall/to anticipate
 KanaVerb( さきんずる ) // (vz,vi) to go before/to precede/to forestall/to anticipate
 KanaVerb( さきがける ) // (v1,vi) to be the first/(P)
 KanaVerb( さきだつ ) // (v5t,vi) to lead/to precede/to die before someone/to go before/to take precedence
 KanaVerb( ちぎれる ) // (v1) to be torn off/to be torn to pieces/(P)
 KanaVerb( うらないあてる ) // (v1) to divine
 KanaVerb( せんする ) // (vs-s) to announce/to declare
 KanaVerb( たたかいぬく ) // (v5k) to fight to the bitter end
 KanaVerb( たたかえばすなわちかつ ) // (v5t) to win every battle (that is fought)
 KanaVerb( おののく ) // (v5k,vi) to shake/to shudder
 KanaVerb( そよぐ ) // (v5g,vi) to rustle/to stir/to flutter
 KanaVerb( わななく ) // (v5k,vi) to tremble/to shiver
 KanaVerb( あらいきよめる ) // (v1) to wash clean/to cleanse
 KanaVerb( あらいわける ) // (v1) to separate by washing
 KanaVerb( あらいおとす ) // (v5s) to wash off/to wash out
 KanaVerb( しみでる ) // (v1,vi) to ooze/to exude/to percolate/to soak through
 KanaVerb( ひそむ ) // (v5m,vi) to lurk/to lie dormant/to be hidden/(P)
 KanaVerb( もぐりこむ ) // (v5m,vi) to slip into/to crawl into (under)/to conceal oneself (under)
 KanaVerb( くぐりぬける ) // (v1,vi) to go through/to pass through/to escape (through the cordon)/to evade (the law)
 KanaVerb( いりつく ) // (v5k) to be scorched/to boil down
 KanaVerb( えらばれる ) // (v1) to be elected
 KanaVerb( ひらめく ) // (v5k,vi) flash (of thunder)/flicker (of lights)/(P)
 KanaVerb( まっとうする ) // (vs-s) to accomplish/to fulfill/to carry out
 KanaVerb( つくろいたてる ) // (v1) to put up a good front
 KanaVerb( すっとぶ ) // (v5b,vi) to rush off/to rush away/to vanish
 KanaVerb( くみあう ) // (v5u,vi) to form a partnership or association/to join together/to grapple with
 KanaVerb( くみあわす ) // (v5s) to combine/to dovetail together
 KanaVerb( くみあわせる ) // (v1) to join together/to combine/to join up/(P)
 KanaVerb( くみなおす ) // (v5s) to reschedule
 KanaVerb( くむ ) // (v5m) to put together/(P)
 KanaVerb( そしきだつ ) // (v5t,vi) to have orderly plans/to be systematic
 KanaVerb( くみつく ) // (v5k) to grapple/to wrestle
 KanaVerb( うったえでる ) // (v1) to lodge a complaint
 KanaVerb( はばむ ) // (v5m) to keep someone from doing/to stop/to prevent/to check/to hinder/to obstruct/to oppose/to thwart/(P)
 KanaVerb( そうこにおさめる ) // (v1) to store in a warehouse
 KanaVerb( かなでる ) // (v1,vi) to play (an instrument)/(P)
 KanaVerb( はきよせる ) // (v1) to sweep up
 KanaVerb( はきあつめる ) // (v1) to sweep up together
 KanaVerb( かきおこす ) // (v5s) to stir up
 KanaVerb( かきくどく ) // (v5k,vi) to complain/to pester
 KanaVerb( かきまぜる ) // (v1) to mix/to stir/to scramble/to churn
 KanaVerb( かききえる ) // (v1,vi) to disappear
 KanaVerb( かきくれる ) // (v1) to be sad
 KanaVerb( かきおとす ) // (v5s) to scrape off
 KanaVerb( すくう ) // (v5u) (1) to nest/to build a nest/(2) to hang out/to haunt
 KanaVerb( すだつ ) // (v5t) to leave the nest
 KanaVerb( やりだまにあげる ) // (v1) to be criticized/to be criticised/to be made an example of
 KanaVerb( はしゃぐ ) // (v5g,vi) (uk) to make merry/to frolic/to be in high spirits/(P)
 KanaVerb( あらそいたたかう ) // (v5u) to fight with/to contend with
 KanaVerb( あらそいうったえる ) // (v1) to accuse/to rise up in judgment against (judgement)
 KanaVerb( あらそう ) // (v5u,vi) (1) to dispute/to argue/to be at variance/(2) to compete/to contest/(3) to deny (e.g., evidence)/(P)
 KanaVerb( やせこける ) // (v1,vi) to get too skinny
 KanaVerb( やせおとろえる ) // (v1,vi) to become emaciated/to grow thin and worn out
 KanaVerb( あいたずさえる ) // (v1) to do something together
 KanaVerb( あいつぐ ) // (v5g) to follow in succession/(P)
 KanaVerb( あいともなう ) // (v5u) to accompany
 KanaVerb( あいわす ) // (v5s) to grow together/to join together (in doing something)
 KanaVerb( そうけだつ ) // (v5t,vi) to relate a hair-raising account or experience
 KanaVerb( くたびれる ) // (v1,vi) to get tired/to wear out/(P)
 KanaVerb( もがく ) // (v5k) (1) to struggle/to wriggle/to squirm/(2) to be impatient/(P)
 KanaVerb( はしりかける ) // (v1) to start running
 KanaVerb( はしりこむ ) // (v5m,vi) to run into (a building)
 KanaVerb( はしりだす ) // (v5s) to begin to run/to start running/(P)
 KanaVerb( はしりでる ) // (v1) to run out (e.g., of the room)
 KanaVerb( はしりつづける ) // (v1) to keep running
 KanaVerb( はしりぬく ) // (v5k) to outrun/to run through to the end
 KanaVerb( はしりぬける ) // (v1,vi) to run through
 KanaVerb( おくりかえす ) // (v5s) to send back/(P)
 KanaVerb( あう ) // (v5u,vi) to meet/to encounter (undesirable nuance)/(P)
 KanaVerb( しもがれる ) // (v1,vi) to be withered or nipped by frost
 KanaVerb( さわぎたてる ) // (v1,vi) to make a fuss (outcry, uproar)
 KanaVerb( さわぐ ) // (v5g,vi) to make noise/to clamor/to be excited/to be alarmed/to kick up a fuss/to make merry/to be annoying/to be troublesome/to make a noise/(P)
 KanaVerb( ざわめく ) // (v5k,vi) (uk) to be noisy/to be astir/to rustle/(P)
 KanaVerb( ふえる ) // (v1,vi) to increase/to multiply/(P)
 KanaVerb( ふえつづける ) // (v1) to continue to increase/to continue to mount
 KanaVerb( ます ) // (v5s,vi) to increase/to grow/(P)
 KanaVerb( つくりつける ) // (v1) to build in
 KanaVerb( そばむ ) // (v5m,vi) to lean to one side/to oppose/to look aside/to regret
 KanaVerb( いきむ ) // (v5m,vi) (1) to strain (e.g., with constipation)/(2) to bear or push down (during childbirth)
 KanaVerb( いきをはずませる ) // (v1) to pant/to gasp/to be short of breath/to be excited
 KanaVerb( いきまく ) // (v5k,vi) to enrage/to infuriate
 KanaVerb( いきづく ) // (v5k,vi) to breathe (heavily)/to pant/to gasp/to sigh
 KanaVerb( たばねつむ ) // (v5m) to shock (grain)
 KanaVerb( あしがでる ) // (v1) to exceed the budget/to do not cover the expense
 KanaVerb( たりる ) // (v1,vi) to be sufficient/to be enough/(P)
 KanaVerb( あがく ) // (v5k,vi) (1) to paw (at) the ground/(2) to flounder/to struggle
 KanaVerb( ぞくする ) // (vs-s) to belong to/to come under/to be affiliated with/to be subject to/(P)
 KanaVerb( そっする ) // (vs-s) to die/to pass away
 KanaVerb( そろう ) // (v5u,vi) to become complete/to be equal/to be all present/to gather/(P)
 KanaVerb( そんじる ) // (v1,vi) to harm/to hurt/to injure/to damage
 KanaVerb( そんする ) // (vs-s) to lose/(P)
 KanaVerb( おおすぎる ) // (v1) to be too numerous/to be too much
 KanaVerb( だする ) // (vs-s) to degenerate/to lapse into
 KanaVerb( おろす ) // (v5s) to abort (negative nuance)
 KanaVerb( うたれる ) // (v1,vi) to be struck/to be beaten
 KanaVerb( うちしおれる ) // (v1,vi) to droop/to be depressed
 KanaVerb( うちすぎる ) // (v1,vi) to pass by (time)/to hit too much
 KanaVerb( うちとける ) // (v1,vi) to open one's heart/to throw off reserve/to be frank
 KanaVerb( ぶちかます ) // (v5s,vi) to strike the face (from sumo)/to punch hard
 KanaVerb( うちよせる ) // (v1) to break onto (shore)/to wash ashore/to attack
 KanaVerb( うちこむ ) // (v5m) to drive in (e.g., nail, stake)/to devote oneself to/to shoot into/to smash/to throw into/to cast into/(P)
 KanaVerb( ぶちこむ ) // (v5m) to drive in (e.g., nail, stake)/to devote oneself to/to shoot into/to smash/to throw into/to cast into
 KanaVerb( うちかつ ) // (v5t,vi) to conquer/to overcome
 KanaVerb( うちつづける ) // (v1) to hit repeatedly
 KanaVerb( うちそこなう ) // (v5u) to fail to hit/to miss
 KanaVerb( うちしずむ ) // (v5m,vi) to be depressed
 KanaVerb( うちまかす ) // (v5s) to defeat
 KanaVerb( うちかえす ) // (v5s) to return a blow repeat/to turn back/to rewhip/to plow up/to plough up/to come and retreat
 KanaVerb( うちつれる ) // (v1,vi) to go along with
 KanaVerb( うちひしがれる ) // (v1) to be stricken (e.g., with grief)/to be battered (e.g., by disasters)
 KanaVerb( うってでる ) // (v1) to launch oneself upon/to make one's debut
 KanaVerb( ぶつ ) // (v5t) to hit/to strike/(P)
 KanaVerb( うちつづく ) // (v5k,vi) to long-continuing
 KanaVerb( たいする ) // (vs-s) to face/to confront/to oppose/(P)
 KanaVerb( たえかねる ) // (v1,vi) to be unable to endure/to lose patience
 KanaVerb( またす ) // (v5s) to keep (a person) waiting/(P)
 KanaVerb( またせる ) // (v1) to keep (a person) waiting/(P)
 KanaVerb( まちくたびれる ) // (v1) to get tired of waiting
 KanaVerb( まちあぐむ ) // (v5m) to tire of waiting
 KanaVerb( まちあわせる ) // (v1) to rendezvous/to meet at a prearranged place and time/(P)
 KanaVerb( まちぼうける ) // (v1) to wait in vain
 KanaVerb( まちぼける ) // (v1) to wait in vain
 KanaVerb( まちぶせる ) // (v1) to ambush
 KanaVerb( まちくらす ) // (v5s) to wait all day
 KanaVerb( なまける ) // (v1,vi) to be idle/to neglect/(P)
 KanaVerb( こけむす ) // (v5s) to have moss growing on itself
 KanaVerb( かしてあげる ) // (v1) to lend (e.g., money)
 KanaVerb( かしさげる ) // (v1) to lend/to loan
 KanaVerb( しりぞく ) // (v5k,vi) (1) to retreat/to recede/to withdraw/(v5k,vi) (2) to retire
 KanaVerb( のく ) // (v5k,vi) (1) to retreat/to recede/to withdraw
 KanaVerb( たいほされる ) // (v1) to be arrested
 KanaVerb( かわりあう ) // (v5u,vi) to relieve each other/to take turns
 KanaVerb( おおづめをむかえる ) // (v1) to approach the finale/to come to a close
 KanaVerb( おとなびる ) // (v1,vi) to become grown-up/to age/to mature
 KanaVerb( ひらく ) // (v5k) to open (e.g., path)/to clear (the way)/to break up (e.g., land)
 KanaVerb( たくす ) // (v5s) to entrust with/to make an excuse of/(P)
 KanaVerb( たくする ) // (vs-s) to entrust
 KanaVerb( かこつける ) // (v1) to use as an excuse/to pretend that
 KanaVerb( たたきあう ) // (v5u) to come to blows/to fight (each other)
 KanaVerb( たたきこわす ) // (v5s) to tear down/to shatter
 KanaVerb( たたきけす ) // (v5s) to beat out (a fire)
 KanaVerb( たたきつぶす ) // (v5s) to smash up/to defeat crushingly
 KanaVerb( たたきおとす ) // (v5s) to knock down/to knock off
 KanaVerb( うばいあう ) // (v5u) to scramble for/to struggle for
 KanaVerb( うばいかえす ) // (v5s) to take back/to recapture
 KanaVerb( だっする ) // (vs-s) to escape from/to get out/(P)
 KanaVerb( たどりつく ) // (v5k,vi) to grope along to/to struggle on to/to arrive somewhere after a struggle
 KanaVerb( たなびく ) // (v5k) to linger/to hover above/to trail/to hang (lie) over
 KanaVerb( なげきかなしむ ) // (v5m) to grieve and moan
 KanaVerb( かつぎこむ ) // (v5m) to carry something into a place
 KanaVerb( さがしもとめる ) // (v1) to search for/to seek for/to look for
 KanaVerb( なげく ) // (v5k,vi) to sigh/to lament/to grieve
 KanaVerb( たんじる ) // (v1,vi) to grieve/to lament/to sigh in admiration
 KanaVerb( たんずる ) // (vz,vi) to grieve/to lament/to sigh in admiration
 KanaVerb( ほころびる ) // (v1,vi) to come apart at the seams/to begin to open/to smile broadly/(P)
 KanaVerb( はじきかえす ) // (v5s) to reject/to repel
 KanaVerb( はじける ) // (v1,vi) to burst open/to split open/to pop
 KanaVerb( はずむ ) // (v5m,vi) to spring/to bound/to bounce/to be stimulated/to be encouraged/to get lively/to treat oneself to/to splurge on/(P)
 KanaVerb( たえる ) // (v1,vi) (1) to die out/to peter out/to become extinct/(2) to cease/to be stopped/to be discontinued/to be cut off
 KanaVerb( だんじこむ ) // (v5m,vi) to have a talk with
 KanaVerb( あたいする ) // (vs-s) to be worth/to deserve/to merit/(P)
 KanaVerb( しっている ) // (v1) to know
 KanaVerb( しらす ) // (v5s) (polite) to know/to understand/to be acquainted with/to feel
 KanaVerb( しりはじめる ) // (v1) to begin to know
 KanaVerb( しれる ) // (v1,vi) to become known/to come to light/to be discovered/(P)
 KanaVerb( しろしめす ) // (v5s) to reign
 KanaVerb( しりあう ) // (v5u,vi) to get to know (someone)/to make acquaintance/(P)
 KanaVerb( じがでる ) // (v1) to reveal one's true colors/to reveal one's true colours/to betray oneself
 KanaVerb( じでいく ) // (v5k-s) to do for real/to do in real life/to carry (a story) into actual practice (practise)
 KanaVerb( じでゆく ) // (v5k-s) to do for real/to do in real life/to carry (a story) into actual practice (practise)
 KanaVerb( ちのそこふかく ) // (v5k) to be deep in the bowels of the earth
 KanaVerb( じだんだふむ ) // (v5m) to stamp one's feet
 KanaVerb( たゆむ ) // (v5m) to slacken/to relax
 KanaVerb( たるむ ) // (v5m,vi) to slacken/to loosen/to relax/(P)
 KanaVerb( はじる ) // (v1,vi) to feel ashamed/(P)
 KanaVerb( おきちがえる ) // (v1) to put something in the wrong place/to misplace
 KanaVerb( おく ) // (v5k) (1) to put/to place/(2) to leave (behind)/(3) (uk) to do something in advance (us. following te-form verb)/(P)
 KanaVerb( おくれる ) // (v1,vi) to be late/to be delayed/to fall behind schedule/to be overdue/(P)
 KanaVerb( はせさんじる ) // (v1,vi) to hasten to join
 KanaVerb( ちゃかす ) // (v5s) to poke fun at/to make fun of
 KanaVerb( ちゃちゃをいれる ) // (v1) to tease/to make fun of
 KanaVerb( きこむ ) // (v5m) to wear extra clothes
 KanaVerb( きがえる ) // (v1) to change one's clothes/(P)
 KanaVerb( きなおす ) // (v5s) to change clothes
 KanaVerb( きぶくれる ) // (v1) to be thickly clad
 KanaVerb( ちゅうでよむ ) // (v5m) to recite from memory
 KanaVerb( そそぎいれる ) // (v1) to pour into
 KanaVerb( そそぐ ) // (v5g) to pour (into)/to irrigate/to pay/to fill/to feed (e.g., a fire)/(P)
 KanaVerb( むしばむ ) // (v5m,vi) to eat into (e.g., by worms)/to spoil/to ruin/to undermine
 KanaVerb( いなおす ) // (v5s) to recast/to recoin
 KanaVerb( きざす ) // (v5s,vi) to show signs (symptoms)
 KanaVerb( しぼむ ) // (v5m,vi) to wither/to fade (away)/to shrivel/to wilt/(P)
 KanaVerb( はりつめる ) // (v1,vi) to strain/to stretch/to string up/to make tense/to cover over/to freeze over
 KanaVerb( はりあう ) // (v5u,vi) to rival/to compete with
 KanaVerb( はりこむ ) // (v5m) to be on the lookout/to lie in wait
 KanaVerb( はりさける ) // (v1,vi) to burst (open)/to break/to split
 KanaVerb( ほりきざむ ) // (v5m) to engrave/to carve
 KanaVerb( ほりあげる ) // (v1) to emboss/to carve in relief/to finish carving of engraving
 KanaVerb( こりる ) // (v1,vi) to learn by experience/to be disgusted with/(P)
 KanaVerb( いどむ ) // (v5m,vi) to challenge/to contend for/to make love to/(P)
 KanaVerb( うしおのごとくおしよせる ) // (v1) to rush like a flood/to surge
 KanaVerb( しおたれる ) // (v1,vi) to weep copiously/to grieve/to be dejected
 KanaVerb( はれる ) // (v1,vi) to swell (from inflammation)/to become swollen
 KanaVerb( ととのう ) // (v5u,vi) to be prepared/to be in order/to be put in order/to be arranged/(P)
 KanaVerb( しらべておく ) // (v5k) to examine beforehand
 KanaVerb( しらべあわす ) // (v5s) to tune to/to check against
 KanaVerb( しらべなおす ) // (v5s) to re-examine/to review/to recheck
 KanaVerb( ちょうしづく ) // (v5k,vi) to warm up to/to become enthusiastic about/to be elated
 KanaVerb( はねかける ) // (v1) to splash/to blame on
 KanaVerb( はねおきる ) // (v1,vi) to jump up/to spring up
 KanaVerb( はねだす ) // (v5s) to spring or rush out
 KanaVerb( はねでる ) // (v1) to spring or rush out
 KanaVerb( はねかえす ) // (v5s) to reject/to bounce back
 KanaVerb( ながらえる ) // (v1,vi) to have a long life/to live a long time
 KanaVerb( ながびく ) // (v5k,vi) to be prolonged/to drag on/(P)
 KanaVerb( ながすぎる ) // (v1) to be too long
 KanaVerb( いただける ) // (v1,vi) (1) (uk) to receive (potential)/(2) to be pretty good/to be exquisite/to be approvable
 KanaVerb( しずむ ) // (v5m,vi) to sink/to feel depressed/(P)
 KanaVerb( ひねこびる ) // (v1,vi) to look old/to appear mature (e.g., of children)
 KanaVerb( おいもとめる ) // (v1) to pursue
 KanaVerb( おいおとす ) // (v5s) to disperse/to take a castle
 KanaVerb( おいつく ) // (v5k,vi) to overtake/to catch up (with)
 KanaVerb( かよいつめる ) // (v1,vi) to visit frequently
 KanaVerb( かよう ) // (v5u,vi) (1) to go back and forth/to ply between/(2) to commute/to attend (school, church, etc.)/(P)
 KanaVerb( つうじる ) // (v1,vi) to run to/to lead to/to communicate/to understand/to be well-informed/(P)
 KanaVerb( つうじあう ) // (v5u) to communicate with/to understand
 KanaVerb( つうずる ) // (vz) to run to/to lead to/to communicate/to understand/to be well-informed
 KanaVerb( とおりこす ) // (v5s,vi) to go past (a place or thing)/to go beyond
 KanaVerb( とおりすぎる ) // (v1,vi) to pass/to pass through/(P)
 KanaVerb( とおりあわせる ) // (v1) to come across/to happen upon
 KanaVerb( とおりぬける ) // (v1,vi) to cut through/to go through
 KanaVerb( つかみあう ) // (v5u,vi) to grapple
 KanaVerb( つづりあわせる ) // (v1) to bind together
 KanaVerb( つぶれる ) // (v1,vi) to be smashed/to go bankrupt/(P)
 KanaVerb( つまさきだつ ) // (v5t,vi) to stand on tiptoes
 KanaVerb( つまびく ) // (v5k) to strum/to pluck the strings (of a guitar)
 KanaVerb( つまだつ ) // (v5t) to stand on tiptoe
 KanaVerb( つられる ) // (v1,vi) to be lured/to be attracted
 KanaVerb( つりあう ) // (v5u,vi) to balance/to be in harmony/to suit/(P)
 KanaVerb( つりこまれる ) // (v1) to be carried away by/to be talked into
 KanaVerb( かくしゅしてまつ ) // (v5t) to wait expectantly/to wait with a craned (outstretched) neck
 KanaVerb( そりすてる ) // (v1) to cut off the hair/take the tonsure
 KanaVerb( すりおとす ) // (v5s) to shave off the hair
 KanaVerb( そりおとす ) // (v5s) to shave off the hair
 KanaVerb( ていす ) // (v5s) to volunteer (bravely)
 KanaVerb( ていする ) // (vs-s) to volunteer (bravely)
 KanaVerb( しめくくりをつける ) // (v1) to bring to a finish/to complete
 KanaVerb( どろのようにねる ) // (v1) (col) to sleep like a log
 KanaVerb( ぬかるむ ) // (v5m,vi) to be muddy/to be slushy
 KanaVerb( つまみあげる ) // (v1) to take a pinch of something (e.g., salt)/to pick up in one's fingers
 KanaVerb( てきとたたかう ) // (v5u) to fight one's enemy
 KanaVerb( かなう ) // (v5u,vi) to be suited
 KanaVerb( てきする ) // (vs-s) to fit/to suit/(P)
 KanaVerb( おぼれる ) // (v1,vi) (1) to be drowned/(2) to indulge in/(P)
 KanaVerb( おぼれこむ ) // (v5m) to drown/to get addicted/to become infatuated
 KanaVerb( おぼれじぬ ) // (v5n) to die by drowning/to drown
 KanaVerb( おぼれそこなう ) // (v5u) to come near being drowned
 KanaVerb( てっする ) // (vs-s) to sink in/to penetrate/to devote oneself/to believe in/to go through/to do intently and exclusively/(P)
 KanaVerb( そいとげる ) // (v1,vi) to remain married for life
 KanaVerb( まといつく ) // (v5k,vi) to entwine/to follow about
 KanaVerb( まつわりつく ) // (v5k,vi) to coil about/to follow about
 KanaVerb( まとわりつく ) // (v5k,vi) to coil about/to follow about
 KanaVerb( はりあわせる ) // (v1) to paste together
 KanaVerb( はりだす ) // (v5s) to post (a notice on a board)/to display
 KanaVerb( はりつく ) // (v5k) to cling (to)
 KanaVerb( ころがりこむ ) // (v5m,vi) to roll in/to tumble into/to come to live with/to fall in one's way/to visit (esp. to stay overnight as an unwanted guest)
 KanaVerb( ころがりおちる ) // (v1) to tumble down/to roll down
 KanaVerb( こける ) // (v1,vi) to fall/to collapse/to drop/to break down/to die/to succumb to/to fall senseless/to be ruined/to have a bad debt
 KanaVerb( ころげる ) // (v1,vi) to roll over/to tumble/to roll about (with laughter)
 KanaVerb( ころげこむ ) // (v5m,vi) to roll or tumble into
 KanaVerb( ころげおちる ) // (v1,vi) to fall off/to tumble down
 KanaVerb( ころぶ ) // (v5b,vi) to fall down/to fall over/(P)
 KanaVerb( まろぶ ) // (v5b,vi) to fall down/to fall over
 KanaVerb( つたう ) // (v5u) to go along/to walk along/to follow/(P)
 KanaVerb( でんきでうごく ) // (v5k) to run by electricity
 KanaVerb( でんげんをいれる ) // (v1) to turn on power
 KanaVerb( とやかくいう ) // (v5u) to say all kinds of things/to complain/to find fault (with)
 KanaVerb( ぬりこむ ) // (v5m) to paint over heavily/to plaster up
 KanaVerb( ぬりわける ) // (v1) to paint in different colors (for different purposes) (colours)
 KanaVerb( まみれる ) // (v1,vi) to be smeared/to be covered
 KanaVerb( やく ) // (v5k) to be jealous of/to be envious of
 KanaVerb( わたりあう ) // (v5u,vi) to argue
 KanaVerb( わたりあるく ) // (v5k,vi) to wander from place to place/to change jobs
 KanaVerb( のぼりつめる ) // (v1,vi) to go to the top/to be engrossed in
 KanaVerb( とする ) // (vs-s) stake/risk/bet/wager
 KanaVerb( とぎれる ) // (v1,vi) to pause/to be interrupted/(P)
 KanaVerb( とだえる ) // (v1,vi) to stop/to cease/to come to an end/(P)
 KanaVerb( どがすぎる ) // (v1) to go too far/to go to excess/to carry too far
 KanaVerb( いからせる ) // (v1) (1) to anger someone/to provoke/to offend someone/to make somebody's hackles rise/(v1) (2) to square one's shoulders/(P)
 KanaVerb( おこらせる ) // (v1) (1) to anger someone/to provoke/to offend someone/to make somebody's hackles rise
 KanaVerb( いかりくるう ) // (v5u) to be in a fit (of anger)/to rage
 KanaVerb( いかりだす ) // (v5s) to break out/to fly into a rage/to lose one's temper
 KanaVerb( おこりだす ) // (v5s) to fly into a rage/to flare up
 KanaVerb( どなりこむ ) // (v5m,vi) to storm in with a yell/(P)
 KanaVerb( どなりだす ) // (v5s) to start shouting/to break out
 KanaVerb( どなりたてる ) // (v1) to stand and shout
 KanaVerb( たおれる ) // (v1,vi) to collapse/to break down/to go bankrupt/to fall/to drop/to die/to succumb to/to fall senseless/to be ruined/to have a bad debt/(P)
 KanaVerb( たおれこむ ) // (v5m) to collapse into/to flop onto
 KanaVerb( たおれふす ) // (v5s) to fall down
 KanaVerb( ふゆめく ) // (v5k,vi) to become wintry
 KanaVerb( こごえる ) // (v1,vi) to freeze/to be chilled/to be frozen/(P)
 KanaVerb( こごえじぬ ) // (v5n) to freeze to death/to die of cold
 KanaVerb( こごえつく ) // (v5k,vi) to freeze to/to be frozen to
 KanaVerb( いてる ) // (v1,vi) to freeze/to be frozen over/to congeal
 KanaVerb( いてつく ) // (v5k,vi) to freeze
 KanaVerb( こおりつく ) // (v5k,vi) to freeze to/to be frozen to
 KanaVerb( いたむ ) // (v5m) to grieve over/to mourn/to lament/(P)
 KanaVerb( なげあげる ) // (v1) to throw up (in the air)
 KanaVerb( なげたおす ) // (v5s) to throw a person down
 KanaVerb( なげかえす ) // (v5s) to throw back
 KanaVerb( なげあたえる ) // (v1) to give by tossing or throwing
 KanaVerb( なげおとす ) // (v5s) to throw down
 KanaVerb( ぬすみみる ) // (v1) to steal a glance
 KanaVerb( ぬすみだす ) // (v5s) to steal (from a person)
 KanaVerb( ゆのしをかける ) // (v1) to iron with a wet cloth/to smooth by steaming and ironing
 KanaVerb( あたりちらす ) // (v5s) to find fault with everybody/to make oneself disagreeable
 KanaVerb( あてられる ) // (v1) (1) to be affected by (e.g., heat)/to suffer from/(2) to be embarrassed/to be annoyed
 KanaVerb( こたえる ) // (v1,vi) to answer/to reply
 KanaVerb( すべあわせる ) // (v1) to bring together/to unite
 KanaVerb( ふみちがえる ) // (v1) to misstep/to stray
 KanaVerb( ふみこえる ) // (v1,vi) to step over or across/to overcome
 KanaVerb( ふみこたえる ) // (v1,vi) to stand firm/to hold out
 KanaVerb( ふみこむ ) // (v5m) to step into (someone else's territory)/to break into/to raid
 KanaVerb( ふみだす ) // (v5s,vi) to step forward/to advance
 KanaVerb( ふみけす ) // (v5s) to stamp out (a fire)
 KanaVerb( ふみまよう ) // (v5u,vi) to lose one's way/to go astray
 KanaVerb( ふみしだく ) // (v5k) to trample/to crush underfoot
 KanaVerb( にげる ) // (v1,vi) to escape/to run away/(P)
 KanaVerb( にげかくれる ) // (v1,vi) to run away and hide
 KanaVerb( にげのびる ) // (v1,vi) to make good one's escape
 KanaVerb( にげおおせる ) // (v1,vi) to escape
 KanaVerb( にげおくれる ) // (v1) to fail to escape
 KanaVerb( にげこむ ) // (v5m,vi) to take refuge in/to succeed in running away
 KanaVerb( にげうせる ) // (v1,vi) to escape/to run away
 KanaVerb( にげおちる ) // (v1,vi) to escape safely
 KanaVerb( にげまどう ) // (v5u,vi) to run about trying to escape
 KanaVerb( のがれる ) // (v1,vi) to escape/(P)
 KanaVerb( のがれでる ) // (v1) to scuttle off/to take flight
 KanaVerb( すける ) // (v1,vi) to be transparent/to show through
 KanaVerb( あたまをいためる ) // (v1) to be concerned about
 KanaVerb( ずぬける ) // (v1,vi) to tower above/to stand out
 KanaVerb( たたかう ) // (v5u,vi) to fight/to battle/to combat/to struggle against/to wage war/to engage in contest/(P)
 KanaVerb( はたらかせる ) // (v1) to put someone to work/to make someone work/(P)
 KanaVerb( はたらきすぎる ) // (v1) to overwork
 KanaVerb( はたらきだす ) // (v5s) to start working/to take action
 KanaVerb( はたらく ) // (v5k,vi) to work/to labor/to labour/to do/to act/to commit/to practise/to practice/to work on/to come into play/to be conjugated/to reduce the price/(P)
 KanaVerb( うごきだす ) // (v5s) to come alive/to get going/to start to move
 KanaVerb( うごく ) // (v5k,vi) to move/to stir/to shift/to shake/to swing/to operate/to run/to go/to work/to be touched/to be influenced/to waver/to fluctuate/to vary/to change/to be transferred/(P)
 KanaVerb( どうじる ) // (v1,vi) to agree
 KanaVerb( どうずる ) // (vz,vi) to agree
 KanaVerb( みちびきだす ) // (v5s) to derive
 KanaVerb( どうける ) // (v1,vi) to jest/to clown (around)
 KanaVerb( みちゆく ) // (v5k-s) to walk down the road
 KanaVerb( とくする ) // (vs-s) to make a profit/(P)
 KanaVerb( える ) // (v1) to get/to obtain/to gain/to acquire/to win/to catch/(P)
 KanaVerb( ひとりごちる ) // (v1) to talk to oneself/to mutter
 KanaVerb( ひとりごつ ) // (v5t,vi) to talk to oneself/to mutter
 KanaVerb( よみすごす ) // (v5s) to skip over/to miss reading
 KanaVerb( よみだす ) // (v5s) to read out (e.g., data from a computer or process)
 KanaVerb( よみすすむ ) // (v5m) to go on reading
 KanaVerb( よみそこなう ) // (v5u) to misread/to mispronounce
 KanaVerb( よみそんじる ) // (v1) to fail to read correctly
 KanaVerb( よみなおす ) // (v5s) to read (a book, etc.) over again
 KanaVerb( よみきかす ) // (v5s) to read to (for) someone
 KanaVerb( よみおとす ) // (v5s) to overlook in reading
 KanaVerb( つきでる ) // (v1,vi) to project/to stick out/to stand out
 KanaVerb( つきすすむ ) // (v5m,vi) to push on/to plunge forward/to push one's way to
 KanaVerb( つっこむ ) // (v5m) (1) to thrust something into something/(2) to plunge into/to go into deeply/(3) to meddle/to interfere/(P)
 KanaVerb( つっぷす ) // (v5s,vi) to fall prostrate
 KanaVerb( つったつ ) // (v5t) to stand up
 KanaVerb( つきぬく ) // (v5k) to pierce/to shoot through/to penetrate
 KanaVerb( つきぬける ) // (v1,vi) to pierce through/to break through
 KanaVerb( とどく ) // (v5k,vi) to reach/(P)
 KanaVerb( とどけいでる ) // (v1) to give notice/to submit notice
 KanaVerb( にげだす ) // (v5s,vi) to run away/to escape from
 KanaVerb( なぞめく ) // (v5k,vi) to be enigmatic or puzzling/to be wrapped in mystery
 KanaVerb( なれあう ) // (v5u,vi) to collude (with)/to conspire (with)/to establish a secret liaison (with)/to make friends with/to get along well with/to become intimate (with opposite sex)
 KanaVerb( なじむ ) // (v5m,vi) to become familiar with
 KanaVerb( やわらかくはなす ) // (v5s) to speak gently
 KanaVerb( においたつ ) // (v5t) (1) to be enveloped in a smell/(2) to be radiant/to be attractive
 KanaVerb( におう ) // (v5u,vi) to be fragrant/to smell/to stink/to glow/to be bright/(P)
 KanaVerb( におわせる ) // (v1) to smell of/to give off a scent/to hint at/to intimate
 KanaVerb( にぎわう ) // (v5u) to prosper/to flourish/to do thriving business/to be crowded with people/(P)
 KanaVerb( ちちくりあう ) // (v5u,vi) to flirt with one another/to caress amorously
 KanaVerb( いりかける ) // (v1) to be about to enter (a bath, etc.)
 KanaVerb( いりこむ ) // (v5m,vi) (1) to go into/to come into/to penetrate/to get in/to step in (a house)/(2) to become complicated
 KanaVerb( いりきれる ) // (v1) (all) are able to get in
 KanaVerb( いりくむ ) // (v5m,vi) to be or become complicated
 KanaVerb( いりみだれる ) // (v1,vi) to be jumbled together
 KanaVerb( いれちがう ) // (v5u) to pass each other/to cross paths
 KanaVerb( いれあわせる ) // (v1) to make up for
 KanaVerb( にんじる ) // (v1,vi) to appoint/to nominate/to assume (responsibility)/to pose as
 KanaVerb( にんずる ) // (vz) to appoint/to nominate/to assume (responsibility)/to pose as
 KanaVerb( しのびなく ) // (v5k,vi) to shed silent tears
 KanaVerb( しのびだす ) // (v5s) to sneak out/to creep out
 KanaVerb( しのびこむ ) // (v5m,vi) to creep in/to steal in
 KanaVerb( ぬれる ) // (v1,vi) to get wet/(P)
 KanaVerb( ねっする ) // (vs-s) to heat/(P)
 KanaVerb( いきりたつ ) // (v5t,vi) to get angry/to lose one's temper
 KanaVerb( としたける ) // (v1,vi) to grow old
 KanaVerb( としおいる ) // (v1) to grow old
 KanaVerb( もえだす ) // (v5s,vi) to catch fire
 KanaVerb( もえつきる ) // (v1,vi) to burn out
 KanaVerb( もえつく ) // (v5k,vi) to catch fire/to ignite
 KanaVerb( ねばりつく ) // (v5k,vi) to be sticky
 KanaVerb( ねばりぬく ) // (v5k,vi) to stick it out/to see it to the end
 KanaVerb( ねばつく ) // (v5k) to be sticky/to be stringy/to be glutinous
 KanaVerb( なやむ ) // (v5m) to be worried/to be troubled/(P)
 KanaVerb( おさまりかえる ) // (v1,vi) to be satisfied with one's position/to be quite content
 KanaVerb( うみただれる ) // (v1) to fester
 KanaVerb( うむ ) // (v5m,vi) to fester/to form pus
 KanaVerb( のぞく ) // (v5k) to peep in/to look in/to peek in/to stick out/(P)
 KanaVerb( なみうつ ) // (v5t,vi) to dash against/to undulate/to wave/to heave/to beat fast (heart)
 KanaVerb( なみだつ ) // (v5t,vi) to be choppy/to run high/to swell/to ripple/to billow/to be in discord
 KanaVerb( やぶける ) // (v1,vi) to get torn/to wear out/to be frustrated/to break
 KanaVerb( ばかげる ) // (v1,vi) to look foolish
 KanaVerb( すたれる ) // (v1,vi) to go out of use/to become obsolete/to die out/to go out of fashion
 KanaVerb( やぶれる ) // (v1,vi) to be defeated/to be unsuccessful/(P)
 KanaVerb( そむく ) // (v5k,vi) to run counter to/to go against/to disobey/to infringe/(P)
 KanaVerb( すすける ) // (v1,vi) to be sooty/to be stained
 KanaVerb( かいあつめる ) // (v1) to buy up
 KanaVerb( かいあたえる ) // (v1) to buy as a gift
 KanaVerb( うりひろげる ) // (v1) to find a market for/to extend the sale of
 KanaVerb( うりおしむ ) // (v5m) to hold back on or restrict sales of/to be reluctant to sell
 KanaVerb( うりきれる ) // (v1,vi) to be sold out/(P)
 KanaVerb( うれる ) // (v1,vi) to be sold/(P)
 KanaVerb( はいだす ) // (v5s,vi) to crawl or creep out of
 KanaVerb( はいでる ) // (v1,vi) to crawl or creep out of
 KanaVerb( はいつくばう ) // (v5u,vi) to grovel
 KanaVerb( はう ) // (v5u) to creep/to crawl/(P)
 KanaVerb( はいりこむ ) // (v5m,vi) (1) to go into/to come into/to penetrate/to get in/to step in (a house)/(2) to become complicated
 KanaVerb( はがれる ) // (v1,vi) to come unstuck from
 KanaVerb( へぐ ) // (v5g) to tear off/to peel off/to rip off/to strip off/to skin/to flay/to disrobe/to deprive of
 KanaVerb( むける ) // (v1,vi) to peel off/to come off/to be taken off/(P)
 KanaVerb( はげる ) // (v1,vi) to come off/to be worn off/to fade/to discolor/to discolour/(P)
 KanaVerb( はげおちる ) // (v1) to peel off
 KanaVerb( むくれる ) // (v1,vi) (1) (uk) to become angry or sullen/to take offense/to be miffed/(2) to come unstuck from/to peel off/to come off/to be taken off
 KanaVerb( はくす ) // (v5s) to win/to gain
 KanaVerb( はくする ) // (vs-s) to win/to gain
 KanaVerb( とまりこむ ) // (v5m,vi) to stay overnight
 KanaVerb( しらむ ) // (v5m,vi) to grow light/to become white/to turn grey (gray)
 KanaVerb( しろむ ) // (v5m,vi) to grow light/to become white/to turn grey (gray)
 KanaVerb( しらちゃける ) // (v1,vi) to fade/to discolour/to discolor
 KanaVerb( うすらぐ ) // (v5g,vi) to become thin/to fade/to grow pale/(P)
 KanaVerb( うすれる ) // (v1,vi) to fade/to become dim/(P)
 KanaVerb( うすよごれる ) // (v1,vi) to get slightly dirty (all over)
 KanaVerb( ばくにつく ) // (v5k) to be arrested/to be put in bonds
 KanaVerb( しばりこむ ) // (v5m) to bind together
 KanaVerb( はだでかんじる ) // (v1) to understand from experience
 KanaVerb( うつ ) // (v5t) to strike/to attack/to punish
 KanaVerb( ばっする ) // (vs-s) to punish/to penalize/to penalise/(P)
 KanaVerb( ぬきんでる ) // (v1) to excel/to be outstanding
 KanaVerb( ぬきあわせる ) // (v1) to draw swords and face off
 KanaVerb( ぬける ) // (v1,vi) to come out/to fall out/to be omitted/to be missing/to escape/(P)
 KanaVerb( ぬけだす ) // (v5s,vi) to slip out/to sneak away/to excel/(P)
 KanaVerb( ぬけでる ) // (v1,vi) to excel/to steal out
 KanaVerb( ぬけおちる ) // (v1,vi) to shed hair
 KanaVerb( ともなう ) // (v5u,vi) to accompany/to bring with/to be accompanied by/to be involved in/to be consequent upon/(P)
 KanaVerb( はんする ) // (vs-s) to be inconsistent with/to oppose/to contradict/to transgress/to rebel/(P)
 KanaVerb( そっくりかえる ) // (v1,vi) to throw one's chest out/to hold one's head high
 KanaVerb( そりくりかえる ) // (v1,vi) to throw one's chest out/to hold one's head high
 KanaVerb( わずらう ) // (v5u,vi) to worry about/to be concerned about/to be afflicted with/to suffer from/(P)
 KanaVerb( わずらわす ) // (v5s) to trouble/to bother/to annoy/to give trouble
 KanaVerb( いやしむ ) // (v5m) to despise/to disdain/to scorn
 KanaVerb( ひする ) // (vs-s) to compare
 KanaVerb( つかれる ) // (v1,vi) to get tired/to tire/(P)
 KanaVerb( つかれはてる ) // (v1,vi) to get tired out/to be exhausted/(P)
 KanaVerb( やめさせる ) // (v1) to fire (from job)/to discharge
 KanaVerb( まかりこす ) // (v5s,vi) to visit/to call on
 KanaVerb( まかりまちがう ) // (v5u,vi) to go wrong/to turn for the worse
 KanaVerb( まかりでる ) // (v1,vi) to leave/to withdraw/to appear before
 KanaVerb( こえる ) // (v1,vi) (1) to grow fat/to grow fertile/(2) to have good taste/(P)
 KanaVerb( ひがいをうける ) // (v1) to be damaged/to receive damage
 KanaVerb( ついえる ) // (v1,vi) to be wasted
 KanaVerb( ひこうにはしらせる ) // (v1) to turn (child) to crime
 KanaVerb( とびちがう ) // (v5u,vi) to flit about
 KanaVerb( とびおきる ) // (v1,vi) to jump up to one's feet
 KanaVerb( とびかう ) // (v5u,vi) to fly about/to flutter about/to fly past each other/(P)
 KanaVerb( とびおりる ) // (v1,vi) to jump down/to jump off/(P)
 KanaVerb( とびだす ) // (v5s,vi) to jump out/to rush out/to fly out/to appear suddenly/to protrude/to project/(P)
 KanaVerb( とびでる ) // (v1,vi) to be exorbitant (e.g., price)/to be ridiculously high
 KanaVerb( とびのく ) // (v5k,vi) to jump back
 KanaVerb( とびはねる ) // (v1,vi) to jump up and down/to hop
 KanaVerb( とびぬける ) // (v1) to be preeminent or outstanding
 KanaVerb( とびあるく ) // (v5k,vi) to walk about
 KanaVerb( とびはなれる ) // (v1,vi) to fly apart/to tower over/to be out of the ordinary
 KanaVerb( とびたつ ) // (v5t,vi) to jump up/to start up/to leap to one's feet/to fly away/to take off
 KanaVerb( とぶ ) // (v5b,vi) to jump/to fly/to leap/to spring/to bound/to hop/(P)
 KanaVerb( とびこむ ) // (v5m,vi) to jump in/to leap in/to plunge into/to dive
 KanaVerb( とびつく ) // (v5k,vi) to jump at/to be attracted by
 KanaVerb( かすかにみえる ) // (v1) to be seen dimly
 KanaVerb( ほほえみかける ) // (v1) to smile
 KanaVerb( ほほえむ ) // (v5m,vi) to smile/(P)
 KanaVerb( まどろむ ) // (v5m,vi) (uk) to doze (off)
 KanaVerb( はなうたまじりではたらく ) // (v5k) to work while humming a tune
 KanaVerb( はなじろむ ) // (v5m,vi) to look daunted
 KanaVerb( ひつようとみとめる ) // (v1) to judge as necessary
 KanaVerb( ただよう ) // (v5u,vi) to drift about/to float/to hang in air/(P)
 KanaVerb( あらわれる ) // (v1,vi) (1) to appear/to come in sight/to become visible/to come out/to embody/to materialize/to materialise/(2) to express oneself
 KanaVerb( おもてだつ ) // (v5t,vi) to become public/to be known/(P)
 KanaVerb( ひょうする ) // (vs-s) to comment
 KanaVerb( かきおろす ) // (v5s) to draw for a specific purpose/to draw for the occasion
 KanaVerb( やみつく ) // (v5k,vi) to be taken ill/to be addicted to/to become absorbed in/to give oneself up (to)
 KanaVerb( やみほおける ) // (v1,vi) to become wasted by illness
 KanaVerb( びょうきだとみえる ) // (v1) to seem to be sick
 KanaVerb( ひんする ) // (vs-s) to draw near/to be on the verge of
 KanaVerb( まずしくくらす ) // (v5s) to live in poverty
 KanaVerb( ふてくされる ) // (v1,vi) (uk) to become sulky/to become irresponsible
 KanaVerb( ついていく ) // (v5k-s) to follow
 KanaVerb( ついてゆく ) // (v5k-s) to follow
 KanaVerb( ついてくる ) // (vk) to follow/to come along with one/to accompany
 KanaVerb( つかせる ) // (v1) to direct someone toward ..
 KanaVerb( つきしたがう ) // (v5u,vi) to follow/to accompany/to cleave to/to join up with/to obey implicitly/to flatter
 KanaVerb( つきそう ) // (v5u,vi) to attend on/to wait upon/to accompany/to escort and wait on/to chaperone
 KanaVerb( つきまとう ) // (v5u,vi) to dangle after
 KanaVerb( つけでかう ) // (v5u) to buy on credit
 KanaVerb( つけあわせる ) // (v1) to add to
 KanaVerb( つけこむ ) // (v5m,vi) to take advantage of/to impose on/to make an entry/(P)
 KanaVerb( つけなおす ) // (v5s) to repair again/to join again
 KanaVerb( つけおとす ) // (v5s) to neglect to make an entry in a ledger
 KanaVerb( つきあう ) // (v5u,vi) to associate with/to keep company with/to get on with
 KanaVerb( とます ) // (v5s) to enrich/to make wealthy
 KanaVerb( とむ ) // (v5m,vi) to be rich/to become rich/(P)
 KanaVerb( おじける ) // (v1) to be afraid (of)/to be frightened (of)
 KanaVerb( おじる ) // (v1,vi) to be scared
 KanaVerb( おじけづく ) // (v5k,vi) to be seized with fear/to be intimidated/to lose one's nerve/to be frightened/to get cold feet/to have the wind up
 KanaVerb( おぞけたつ ) // (v5t,vi) to be horrified/to be filled with trepidation
 KanaVerb( たすけおこす ) // (v5s) to help a person to his (her) feet
 KanaVerb( しく ) // (v5k) (1) to spread out/to lay out/(2) to take a position/(3) to impose widely (e.g., over a city)/(P)
 KanaVerb( うかされる ) // (v1,vi) to be carried away/to be delirious/to lapse into delirium
 KanaVerb( うかぶ ) // (v5b) to float/to rise to surface/to come to mind/(P)
 KanaVerb( うかれる ) // (v1,vi) to make merry/to be festive/(P)
 KanaVerb( うきだす ) // (v5s,vi) to surface/to stand out
 KanaVerb( うきでる ) // (v1,vi) to rise to the surface/to stand or break out
 KanaVerb( うきあしだつ ) // (v5t) to be prepared to flee
 KanaVerb( うきたつ ) // (v5t,vi) to be enlivened/to be exhilarated
 KanaVerb( うく ) // (v5k,vi) to float/to become merry/to become loose/(P)
 KanaVerb( うかれあるく ) // (v5k) to gad around
 KanaVerb( むくむ ) // (v5m,vi) to swell/to become swollen
 KanaVerb( うわつく ) // (v5k) (uk) to be fickle/to be restless/to be flippant
 KanaVerb( くさりはてる ) // (v1) to be corrupt
 KanaVerb( くされる ) // (v1,vi) to spoil/to rot/to corrode
 KanaVerb( おえる ) // (v1) to be able to bear/to be able to manage
 KanaVerb( まける ) // (v1,vi) to lose/to be defeated/(P)
 KanaVerb( おぶう ) // (v5u) to carry (child) on one's back
 KanaVerb( おわせる ) // (v1) (1) to put something on someone's back/to make someone carry something/(2) to lay responsibility on someone/to charge someone with a duty/(3) to inflict injury on someone
 KanaVerb( おもむく ) // (v5k) to go/to proceed/to repair to/to become
 KanaVerb( なでおろす ) // (v5s) to stroke down
 KanaVerb( なでまわす ) // (v5s) to pat (e.g., dog)/to rub/to stroke
 KanaVerb( むしゃぶりつく ) // (v5k) to jump into the fray
 KanaVerb( まいおりる ) // (v1,vi) to swoop down upon/to fly down/to alight
 KanaVerb( まいこむ ) // (v5m,vi) to drop in/to happen to
 KanaVerb( まう ) // (v5u,vi) to dance/to flutter about/to revolve/(P)
 KanaVerb( ふうじこむ ) // (v5m) to entrap
 KanaVerb( ふしたおれる ) // (v1) to fall down
 KanaVerb( そう ) // (v5u,vi) to suit/to meet/to satisfy/to marry/to accompany/to be added to/to be adjusted to
 KanaVerb( ふくす ) // (v5s) to return to normal/to recover/to restore
 KanaVerb( ふくする ) // (vs-s) to be subject to/to submit to/to obey/to abide by/to serve, e.g., in the army, or a sentence in jail (gaol)/to observe, e.g., mourning
 KanaVerb( おおいかくす ) // (v5s) to mask/to cover
 KanaVerb( はらいおとす ) // (v5s) to brush off/to shake off
 KanaVerb( わきだす ) // (v5s) to cause to gush out
 KanaVerb( わきでる ) // (v1,vi) to gush forth
 KanaVerb( わきたつ ) // (v5t,vi) to boil up/to ferment/to seethe
 KanaVerb( ものもうす ) // (v5s,vi) to speak/to object
 KanaVerb( わかちあう ) // (v5u) to share
 KanaVerb( わかりあう ) // (v5u) to understand (each other)/to comprehend
 KanaVerb( わかりだす ) // (v5s) to take notice
 KanaVerb( わかれでる ) // (v1) to branch out/to diverge/to radiate
 KanaVerb( わけあう ) // (v5u) to share
 KanaVerb( わけあたえる ) // (v1) to distribute/to hand out
 KanaVerb( わけはなす ) // (v5s) to separate from/to detach
 KanaVerb( ふきこぼれる ) // (v1,vi) to boil over
 KanaVerb( ふきだす ) // (v5s,vi) to spout/to spurt/to gush out/to burst into laughter/(P)
 KanaVerb( ふきでる ) // (v1,vi) to blow out/to spout out
 KanaVerb( ふく ) // (v5k) (1) to blow (wind, etc)/(2) to emit/to spout
 KanaVerb( ふんする ) // (vs-s) to disguise oneself/to be dressed (as someone else)
 KanaVerb( ふるいたつ ) // (v5t,vi) to cheer up
 KanaVerb( ふるう ) // (v5u) (1) to show (ability)/to wield (power)/(2) to screw up one's courage/(P)
 KanaVerb( まがう ) // (v5u) to be mistaken for/to be confused with
 KanaVerb( まぎれる ) // (v1,vi) to be diverted/to slip into/(P)
 KanaVerb( まぎれこむ ) // (v5m,vi) to disappear into/to slip into/to be lost in/to be mixed up with
 KanaVerb( ききちがう ) // (v5u) to mishear
 KanaVerb( ききすごす ) // (v5s) to fail to catch/to ignore
 KanaVerb( ききほれる ) // (v1,vi) to listen to in an ecstasy
 KanaVerb( ききつくす ) // (v5s) to hear all about
 KanaVerb( ききそこなう ) // (v5u) to mishear/to fail to catch
 KanaVerb( ききいただく ) // (v5k) to ask (politely)
 KanaVerb( ききもらす ) // (v5s) to fail to hear/to miss
 KanaVerb( ききただす ) // (v5s) to ascertain/to confirm/to verify/to make sure of
 KanaVerb( きこえる ) // (v1,vi) (1) to be heard/to be audible/(2) to be said to be/to be reputed/(P)
 KanaVerb( きこしめす ) // (v5s) to hear/to drink
 KanaVerb( あわせる ) // (v1) to unite/to put together/(P)
 KanaVerb( あわせかんがえる ) // (v1) to consider together
 KanaVerb( あわせもちいる ) // (v1) to use jointly/to use at the same time
 KanaVerb( たいらぐ ) // (v5g) to be suppressed
 KanaVerb( ひれふす ) // (v5s,vi) to prostrate oneself before
 KanaVerb( ならぶ ) // (v5b,vi) to line up/to stand in a line/(P)
 KanaVerb( なみはずれる ) // (v1,vi) to be uncommon
 KanaVerb( なみいる ) // (v1,vi) to sit in a row/to be present (and lined up)
 KanaVerb( とじる ) // (v1) to close (e.g., book, eyes, meeting, etc.)/to shut/(P)
 KanaVerb( ひがむ ) // (v5m) (1) to be prejudiced/to be soured/(2) to have an inferiority complex/(3) to be jealous/(P)
 KanaVerb( わかちあたえる ) // (v1) to divide and pass around
 KanaVerb( わかれる ) // (v1,vi) to be divided/to part from/to separate/to bid farewell/(P)
 KanaVerb( わかれあらそう ) // (v5u) to quarrel and separate
 KanaVerb( かたよりみる ) // (v1) to show partiality
 KanaVerb( かわりはてる ) // (v1) to be completely changed
 KanaVerb( かたはだぬぐ ) // (v5g) to lend a hand
 KanaVerb( かたづく ) // (v5k,vi) (1) to be put in order/to be put to rights/(2) to be disposed of/to be solved/(3) to be finished/(4) to be married (off)/(P)
 KanaVerb( あみあわせる ) // (v1) to knit together/to intertwine
 KanaVerb( かえりざく ) // (v5k,vi) to come back/to bloom a second time
 KanaVerb( あまねくさがす ) // (v5s) to make a wide search
 KanaVerb( べんきょうしはじめる ) // (v1) to begin to study
 KanaVerb( べんきょうしだす ) // (v5s) to begin to study
 KanaVerb( べんじる ) // (v1,vi) to speak/to talk/to argue/to manage/to dispose of/to carry through/to distinguish/to discriminate
 KanaVerb( べんじたてる ) // (v1) to speak eloquently/to talk volubly
 KanaVerb( べんずる ) // (vz) to manage/to dispose of/to carry through/to distinguish/to discriminate
 KanaVerb( もちあう ) // (v5u) to maintain equilibrium/to share expenses
 KanaVerb( とらわれる ) // (v1,vi) to be captured/to be apprehended/to be seized with/(P)
 KanaVerb( あるきつづける ) // (v1) to keep walking
 KanaVerb( あるきつかれる ) // (v1) to be tired from walking
 KanaVerb( あるく ) // (v5k,vi) to walk/(P)
 KanaVerb( あゆむ ) // (v5m,vi) to walk/to go on foot/(P)
 KanaVerb( くれる ) // (v1,vi) to get dark/to end/to come to an end/to close/to run out/(P)
 KanaVerb( くれはてる ) // (v1,vi) complete nightfall
 KanaVerb( くれゆく ) // (v5k-s,vi) darkening/passing
 KanaVerb( くれなずむ ) // (v5m,vi) to grow dark slowly
 KanaVerb( つつみなおす ) // (v5s) to re-wrap
 KanaVerb( あきれる ) // (v1,vi) to be amazed/to be shocked/(P)
 KanaVerb( あきれはてる ) // (v1,vi) to be flabbergasted or dumbfounded
 KanaVerb( ほうずる ) // (vz) to present/to dedicate/to obey/to follow/to believe in/to serve
 KanaVerb( くずれる ) // (v1,vi) to collapse/to crumble/(P)
 KanaVerb( くずれおちる ) // (v1,vi) to crumble down/to tumble down/to fall in
 KanaVerb( だきよせる ) // (v1) to embrace
 KanaVerb( だきあう ) // (v5u,vi) to embrace each other/(P)
 KanaVerb( だきあわせる ) // (v1) to cause to embrace
 KanaVerb( だきつく ) // (v5k) to cling to/to embrace
 KanaVerb( ほったらかす ) // (v5s) to let aside/to neglect
 KanaVerb( ほうっておく ) // (v5k) to leave alone/to leave as is/to ignore/to neglect
 KanaVerb( ほっとく ) // (v5k) to leave someone alone
 KanaVerb( ほうりあげる ) // (v1) to hurl up
 KanaVerb( あわだつ ) // (v5t) to bubble/to foam/to froth
 KanaVerb( ぬいあわせる ) // (v1) to sew up (together)
 KanaVerb( もえる ) // (v1,vi) to burst into bud/to sprout
 KanaVerb( もえでる ) // (v1,vi) to sprout/to bud
 KanaVerb( もえたつ ) // (v5t) to burst into leaf/to sprout
 KanaVerb( ほめそやす ) // (v5s) to praise/to extol
 KanaVerb( ほめうたう ) // (v5u) to sing praises to
 KanaVerb( ほめごろす ) // (v5s) to compliment and criticize lavishly (criticise)
 KanaVerb( ほめあげる ) // (v1) to praise to the skies/extol
 KanaVerb( ほめたてる ) // (v1) to praise/to extol/to applaud
 KanaVerb( おとずれる ) // (v1,vi) to visit/(P)
 KanaVerb( あきる ) // (v1,vi) to get tired of/to lose interest in/to have enough/(P)
 KanaVerb( わすれかける ) // (v1) to start forgetting
 KanaVerb( わすれられる ) // (v1) to slip into obscurity/to be forgotten
 KanaVerb( ぼうさつされる ) // (v1) to be worked to death/to be very busily occupied
 KanaVerb( あばきだす ) // (v5s) to dig up and expose a criminal matter
 KanaVerb( あばれる ) // (v1,vi) to act violently/to rage/to struggle/to be riotous/(P)
 KanaVerb( あばれくるう ) // (v5u) to rage/to run amuck/to tear around
 KanaVerb( あばれこむ ) // (v5m) to enter someone's territory by force
 KanaVerb( あばれだす ) // (v5s) to grow restive/to begin to act violently
 KanaVerb( ふくらむ ) // (v5m) to expand/to swell (out)/to get big/to become inflated/(P)
 KanaVerb( ふくれる ) // (v1,vi) to get cross/to get sulky/to swell (out)/to expand/to be inflated/to distend/to bulge/(P)
 KanaVerb( ほえだす ) // (v5s) to give mouth/to bark
 KanaVerb( ほえつく ) // (v5k,vi) to bark at and chase
 KanaVerb( ほほそめる ) // (v1) to blush
 KanaVerb( ほくそえむ ) // (v5k,vi) to chuckle/to snicker
 KanaVerb( うらなう ) // (v5u) to tell a fortune/to predict/to choose/to settle/to fix
 KanaVerb( ぼくする ) // (vs-s) to tell (a person's) fortune/to divine/to fix/to choose
 KanaVerb( むつぶ ) // (v5b,vi) to be harmonious/to get on well/to be intimate or close
 KanaVerb( むつむ ) // (v5m,vi) to be harmonious/to get on well/to be intimate or close
 KanaVerb( ほりちらす ) // (v5s) to dig up messily
 KanaVerb( もんどりうつ ) // (v5t) to turn a somersault
 KanaVerb( まする ) // (vs-s) (1) to rub/to scrub/(2) to draw near/to press
 KanaVerb( すりこむ ) // (v5m) to rub in/to grind and mix
 KanaVerb( すりきれる ) // (v1,vi) to wear out
 KanaVerb( すれる ) // (v1,vi) to rub/to chafe/to wear/to become sophisticated
 KanaVerb( すりあわせる ) // (v1) to fit by rubbing together
 KanaVerb( すりくだく ) // (v5k) to rub to pieces/to grind into powder
 KanaVerb( すりけす ) // (v5s) to erase/to efface
 KanaVerb( すりくずす ) // (v5s) to rub to pieces
 KanaVerb( ますいをかける ) // (v1) to anesthetize/to anesthetise/to anaesthetize/to anaesthetise
 KanaVerb( いける ) // (v1) (1) to bury something in the ground/(2) to cover coals with ash/to bank a fire
 KanaVerb( うめあわす ) // (v5s) to make up for/to compensate for
 KanaVerb( うめこむ ) // (v5m) to bury/to embed
 KanaVerb( うずもれる ) // (v1,vi) to be buried/to be covered
 KanaVerb( うもれる ) // (v1,vi) to be buried/to be covered/to be hidden/(P)
 KanaVerb( うらがれる ) // (v1,vi) to die (esp. foliage as winter approaches)
 KanaVerb( まゆをかける ) // (v1) to spin a cocoon
 KanaVerb( まんいちにそなえる ) // (v1) to provide against contingencies
 KanaVerb( みちる ) // (v1,vi) to be full/to rise (tide)/to mature/to expire/(P)
 KanaVerb( みちあふれる ) // (v1,vi) to be full of (e.g. adventure youth energy and such)/to be overflowing with
 KanaVerb( みちたりる ) // (v1,vi) to be content/to have enough/to be happy/to be sufficient/to be satisfied
 KanaVerb( みちみちる ) // (v1) to be full to the brim
 KanaVerb( ひかれる ) // (v1) to be charmed by
 KanaVerb( みせられる ) // (v1) to be enchanted/to be charmed
 KanaVerb( みゃくうつ ) // (v5t,vi) pounding heart/pulsing vein
 KanaVerb( ねむりこむ ) // (v5m,vi) to fall asleep/to sleep deeply
 KanaVerb( ゆめみる ) // (v1,vi) to dream (of)
 KanaVerb( なのりでる ) // (v1,vi) to introduce oneself/(P)
 KanaVerb( なまえをはせる ) // (v1) to win fame/to make a name for oneself
 KanaVerb( あく ) // (v5k,vi) (1) to open/to become open/to become empty/(v5k,vi) (2) to dawn
 KanaVerb( あけそめる ) // (v1) to dawn
 KanaVerb( あけくれる ) // (v1,vi) to do nothing but/to spend all one's time doing
 KanaVerb( あけはなれる ) // (v1) darkness giving way to the light of the morning
 KanaVerb( あからむ ) // (v5m,vi) to become luminous at dawn (esp. the sky)
 KanaVerb( あかるむ ) // (v5m,vi) to brighten/to be refreshed
 KanaVerb( まよいこむ ) // (v5m) to go astray/to lose one's way
 KanaVerb( まよう ) // (v5u,vi) to be puzzled/to be perplexed/to lose one's way/(P)
 KanaVerb( めいうつ ) // (v5t,vi) to engrave an inscription/to call (designate) itself/to mark/to label
 KanaVerb( なきかわす ) // (v5s) to exchange wooing cries/to cry (howl) to each other
 KanaVerb( なりひびく ) // (v5k,vi) to reverberate/to resound/to echo
 KanaVerb( なりだす ) // (v5s) to begin making a sound (ringing, singing, crying, etc.)
 KanaVerb( ほろびる ) // (v1,vi) to be ruined/to go under/to perish/to be destroyed/(P)
 KanaVerb( ほろぶ ) // (v5b) to be ruined/to go under/to perish/to be destroyed
 KanaVerb( まぬがれる ) // (v1,vi) to escape from/to be rescued from/to avoid/to evade/to avert/to elude/to be exempted/to be relieved from pain/to get rid of
 KanaVerb( めんする ) // (vs-s) to face on/to look out on to/(P)
 KanaVerb( めんくらう ) // (v5u) to be confused (bewildered, taken aback)
 KanaVerb( けばだつ ) // (v5t) to become fluffy
 KanaVerb( だまりこむ ) // (v5m,vi) to say no more/to sink into silence
 KanaVerb( めからひがでる ) // (v1) to see stars (i.e. after being hit in the head)
 KanaVerb( もくする ) // (vs-s) to recognize/to recognise/to distinguish/to pay attention to
 KanaVerb( めにつく ) // (v5k) to be noticeable
 KanaVerb( めをとめる ) // (v1) to take notice/to pay attention
 KanaVerb( めをふせる ) // (v1) to cast down one's eyes
 KanaVerb( めざます ) // (v5s) to wake up
 KanaVerb( めざめる ) // (v1) to wake up/(P)
 KanaVerb( めだつ ) // (v5t,vi) to be conspicuous/to stand out/(P)
 KanaVerb( めくるめく ) // (v5k,vi) to dazzle/to blind
 KanaVerb( といあわせる ) // (v1) to enquire/to inquire/to seek information/(P)
 KanaVerb( といただす ) // (v5s) to question
 KanaVerb( といなおす ) // (v5s) to question/to query
 KanaVerb( もんだいをとりあげる ) // (v1) to take up a problem
 KanaVerb( もだえる ) // (v1,vi) to be in agony/to worry
 KanaVerb( いやます ) // (v5s,vi) to increase (all the more)
 KanaVerb( やくにたつ ) // (v5t) to be helpful/to be useful/(P)
 KanaVerb( やくだつ ) // (v5t) to be useful/to be helpful/to serve the purpose/(P)
 KanaVerb( やくす ) // (v5s) to translate/(P)
 KanaVerb( おどりこむ ) // (v5m,vi) to jump into/to rush into
 KanaVerb( おどりでる ) // (v1,vi) to jump (e.g., to first place)/to spring out
 KanaVerb( あぶらじみる ) // (v1,vi) to become greasy/to be oil-stained
 KanaVerb( いえる ) // (v1,vi) to recover/to be healed
 KanaVerb( すぐれる ) // (v1,vi) to surpass/to outstrip/to excel/(P)
 KanaVerb( いさみたつ ) // (v5t,vi) to cheer up/to be encouraged (by)/to be in high spirits
 KanaVerb( いさむ ) // (v5m) to be in high spirits/to be encouraged/to be lively/to cheer up/(P)
 KanaVerb( ゆうめいあいへだてる ) // (v1) to die
 KanaVerb( うれいなやむ ) // (v5m) to be grievously troubled
 KanaVerb( ゆうする ) // (vs-s) to own/to be endowed with/(P)
 KanaVerb( ありあう ) // (v5u,vi) to happen to be present
 KanaVerb( ありうる ) // (v5uru,vi) to be possible/to be likely/to be probable
 KanaVerb( ありえる ) // (v1,vi) to be possible/to be likely
 KanaVerb( ありつく ) // (v5k) to get/to obtain/to come by/to find
 KanaVerb( うむあいつうじる ) // (v1) to help each other/to complement
 KanaVerb( わく ) // (v5k,vi) to boil/to grow hot/to get excited/to gush forth/(P)
 KanaVerb( さそいをかける ) // (v1) to invite/to call out
 KanaVerb( さそいかける ) // (v1) to invite
 KanaVerb( さそいあう ) // (v5u) to ask each other
 KanaVerb( あそばせる ) // (v1) to leave idle
 KanaVerb( あそびたわむれる ) // (v1) to frolic
 KanaVerb( あそびあるく ) // (v5k) to visit one place after another without affect
 KanaVerb( あそぶ ) // (v5b,vi) (1) to play/to make a visit (esp. for pleasure)/(2) to be idle/to do nothing/(P)
 KanaVerb( くみする ) // (vs-s) to take part in/to be implicated in/to side with/to support
 KanaVerb( ゆすりおこす ) // (v5s) to shake someone awake
 KanaVerb( ゆらぐ ) // (v5g,vi) to swing/to sway/to shake/to tremble/(P)
 KanaVerb( ゆらめく ) // (v5k,vi) to flicker/to quiver/to waver/to sway
 KanaVerb( ゆりおこす ) // (v5s) to shake someone awake
 KanaVerb( ゆりうごく ) // (v5k,vi) to quake/to swing
 KanaVerb( ゆりかえす ) // (v5s,vi) to shake back
 KanaVerb( ゆりおとす ) // (v5s) to shake down (e.g., nuts from a tree)
 KanaVerb( ゆるぐ ) // (v5g,vi) to shake/to waver/to tremble/(P)
 KanaVerb( ゆれる ) // (v1,vi) to shake/to sway/(P)
 KanaVerb( ゆれうごく ) // (v5k) to tremble
 KanaVerb( たゆたう ) // (v5u,vi) to drift from here to there/to float around
 KanaVerb( ときほぐす ) // (v5s) to whip an egg/to scramble (e.g., an egg)
 KanaVerb( とけあう ) // (v5u,vi) to melt together
 KanaVerb( とけこむ ) // (v5m,vi) to melt into/(P)
 KanaVerb( ようする ) // (vs-s) to demand/to require/to take/(P)
 KanaVerb( おどらされる ) // (v1) to be manipulated (lit: to be made to dance)
 KanaVerb( おどりくるう ) // (v5u) to dance in ecstasy
 KanaVerb( おどりだす ) // (v5s) to begin to dance/to break into a dance
 KanaVerb( おどりぬく ) // (v5k) to dance away
 KanaVerb( おどりあかす ) // (v5s) to dance all night/to dance until dawn
 KanaVerb( やしないそだてる ) // (v1) to bring up/to foster/to rear
 KanaVerb( おさえこむ ) // (v5m) to shut out one's opponents/to stop the other side from scoring
 KanaVerb( よどむ ) // (v5m,vi) to stagnate/to be stagnant/to settle/to deposit/to be sedimented/to be precipitated/to hesitate/to be sluggish/to stammer/to stumble/to falter
 KanaVerb( らいはじめる ) // (v1) to come for the first time/to become for the first time
 KanaVerb( きむかう ) // (v5u) to come facing (us)
 KanaVerb( きあわせる ) // (v1) to happen to come along
 KanaVerb( きつける ) // (v1) to call frequently
 KanaVerb( たのむ ) // (v5m) to request/to beg/to ask/(P)
 KanaVerb( からみつく ) // (v5k) to twine oneself around/to coil around
 KanaVerb( からむ ) // (v5m,vi) (1) to entangle/to entwine/(2) to pick a quarrel/(3) to be involved with/(P)
 KanaVerb( おちぶれる ) // (v1) to be ruined/to fall low/to go under/to come to ruin
 KanaVerb( おちる ) // (v1,vi) (1) to fall down/to drop/(2) to fail (e.g., exam)/(3) to crash/to degenerate/to degrade/(4) to fade/to come out (e.g., a stain)/(P)
 KanaVerb( おちくぼむ ) // (v5m) to sink in/to cave in
 KanaVerb( おちゆく ) // (v5k-s,vi) to flee/to be ruined
 KanaVerb( おちあう ) // (v5u,vi) to gather/to meet/to join/to flow together/to rendezvous/(P)
 KanaVerb( おちこむ ) // (v5m,vi) to fall into/to feel down (sad)/(P)
 KanaVerb( おちつきはらう ) // (v5u,vi) to keep cool
 KanaVerb( おちこぼれる ) // (v1) to fall behind/to fall short/to drop out
 KanaVerb( おっこちる ) // (v1,vi) to fall down/to drop
 KanaVerb( おつ ) // (v5t,vi) (1) to fall down/to drop/(2) to fail (e.g., exam)/(3) to crash/to degenerate/to degrade
 KanaVerb( おちのびる ) // (v1,vi) to run away/to escape safely
 KanaVerb( おちつく ) // (v5k) to calm down/to settle down/to be steady/to settle in/to take up one's residence/to harmonize with/to harmonise with/to match/to restore presence of mind
 KanaVerb( みだれる ) // (v1,vi) to get confused/to be disordered/to be disturbed/(P)
 KanaVerb( みだれとぶ ) // (v5b,vi) to fly wildly about
 KanaVerb( ふぶく ) // (v5k,vi) to blow snow violently
 KanaVerb( きかす ) // (v5s) to season/to enliven
 KanaVerb( きく ) // (v5k,vi) to be effective/(P)
 KanaVerb( りする ) // (vs-s) (1) to profit/to benefit from/(2) to to take advantage of/to make good use of
 KanaVerb( はきかえる ) // (v1) to change (clothes)
 KanaVerb( りかいしあう ) // (v5u) to reach mutual understanding/to understand each other
 KanaVerb( うらどう ) // (v5u-s) to ascertain a person's innermost feelings
 KanaVerb( はなれる ) // (v1,vi) to be separated from/to leave/to go away/to be a long way off/(P)
 KanaVerb( たちむかう ) // (v5u,vi) to fight against/to oppose/to face
 KanaVerb( たちいく ) // (v5k-s,vi) to maintain itself/to last/to make itself pay/to make a living/to keep going
 KanaVerb( たちゆく ) // (v5k-s,vi) to maintain itself/to last/to make itself pay/to make a living/to keep going
 KanaVerb( たちあう ) // (v5u,vi) to be matched against
 KanaVerb( たちあげる ) // (v1) (comp) to start (something)/to boot (a computer)
 KanaVerb( たちふるまう ) // (v5u) to act/to behave
 KanaVerb( たちつくす ) // (v5s) to stand stock still
 KanaVerb( たちさわぐ ) // (v5g,vi) to make a din
 KanaVerb( たちのかせる ) // (v1) to evict/to eject
 KanaVerb( たちのく ) // (v5k,vi) to evacuate/to clear out/to vacate/to withdraw/to take refuge/(P)
 KanaVerb( たちおくれる ) // (v1,vi) to start slowly/to lag behind
 KanaVerb( たちはたらく ) // (v5k,vi) to go about one's work
 KanaVerb( たちならぶ ) // (v5b) to stand up/to line in a row/to be equal to
 KanaVerb( たちまよう ) // (v5u,vi) to drift along
 KanaVerb( たちすくむ ) // (v5m,vi) to be petrified/to be unable to move
 KanaVerb( たてこむ ) // (v5m) to be crowded/to be busy/(P)
 KanaVerb( たちこめる ) // (v1,vi) to hang over/to shroud/to enshroud/to envelop/to screen
 KanaVerb( たちつづける ) // (v1,vi) to keep standing
 KanaVerb( かすめうばう ) // (v5u) to plunder
 KanaVerb( かすれる ) // (v1,vi) to be grazed/to touch/to chip
 KanaVerb( りゃくす ) // (v5s) to abbreviate/(P)
 KanaVerb( ながしだす ) // (v5s) to draw off/to run out/to flush out
 KanaVerb( ながれる ) // (v1,vi) to stream/to flow (liquid, time, etc.)/to run (ink)/to be washed away/(P)
 KanaVerb( ながれこむ ) // (v5m,vi) to flow/to pour/to stream/(P)
 KanaVerb( ながれだす ) // (v5s) to flow out/to stream out/to pour out/to gush forth/to leak/to ooze out/to drift away
 KanaVerb( ながれでる ) // (v1) to flow out/to stream out/to pour out/to gush forth/to leak/to ooze out/to drift away
 KanaVerb( ながれつく ) // (v5k) to drift to/to be washed ashore
 KanaVerb( ながれあるく ) // (v5k,vi) to wander about
 KanaVerb( ながれおちる ) // (v1) to run off (fluid)/to run down/to flow down
 KanaVerb( さすらう ) // (v5u,vi) to wander/to roam
 KanaVerb( つぶだつ ) // (v5t,vi) to become grainy
 KanaVerb( たびなれる ) // (v1,vi) to be accustomed to traveling (travelling)
 KanaVerb( たびだつ ) // (v5t,vi) to begin a trip/(P)
 KanaVerb( すずむ ) // (v5m,vi) to cool oneself/to cool off/to enjoy evening cool/(P)
 KanaVerb( りょうする ) // (vs-s) to own/to receive/to understand
 KanaVerb( ちからをいれる ) // (v1) to put forth effort
 KanaVerb( りきんでみせる ) // (v1) to show a bold front
 KanaVerb( ちからづく ) // (v5k) to recover one's strength/to recover one's spirit/to revive/to be refreshed/to be invigorated/to be encouraged
 KanaVerb( ちからこぶをいれる ) // (v1) to work earnestly
 KanaVerb( のぞむ ) // (v5m,vi) to look out on/to face/to deal with/to attend (function)/(P)
 KanaVerb( となりあう ) // (v5u,vi) to adjoin each other/to sit side by side/(P)
 KanaVerb( となりあわせる ) // (v1) to adjoin
 KanaVerb( なみだぐむ ) // (v5m,vi) to be moved to tears
 KanaVerb( なみだする ) // (vs-s) to shed tears/to bring tears to one's eyes
 KanaVerb( るいする ) // (vs-s) to be similar to
 KanaVerb( ひえる ) // (v1,vi) to grow cold/to get chilly/to cool down/(P)
 KanaVerb( ひえこむ ) // (v5m,vi) to get colder/to get chilled/(P)
 KanaVerb( ひやかす ) // (v5s) to banter/to make fun of/to jeer at/to cool/to refrigerate/(P)
 KanaVerb( はげみあう ) // (v5u) to vie with another
 KanaVerb( はげむ ) // (v5m) to be zealous/to brace oneself/to endeavour/to endeavor/to strive/to make an effort/(P)
 KanaVerb( こぼれる ) // (v1,vi) to overflow/to spill/(P)
 KanaVerb( こぼれおちる ) // (v1,vi) to spill over and fall/to scatter (petals, leaves, etc.)
 KanaVerb( さける ) // (v1,vi) to split/to tear/to burst/(P)
 KanaVerb( こいそめる ) // (v1) to begin to love
 KanaVerb( こいしのぶ ) // (v5b) to live on love
 KanaVerb( こいくらす ) // (v5s) to live deeply in love
 KanaVerb( こいわびる ) // (v1) to be lovesick
 KanaVerb( こいする ) // (vs-s) to fall in love with/to love/(P)
 KanaVerb( こいこがれる ) // (v1) to yearn for/to be deeply in love with
 KanaVerb( ねりあわせる ) // (v1) to knead together
 KanaVerb( ねりあるく ) // (v5k,vi) to parade/to march
 KanaVerb( つれていく ) // (v5k-s) to take someone (of lower status) along/(P)
 KanaVerb( つれてくる ) // (vk) to bring someone along/(P)
 KanaVerb( つれる ) // (v1) to lead/to take (a person)/(P)
 KanaVerb( つれそう ) // (v5u,vi) to be man and wife/to be married to
 KanaVerb( つれもどす ) // (v5s) to bring back
 KanaVerb( つれだつ ) // (v5t,vi) to accompany/to go with or together
 KanaVerb( もれる ) // (v1,vi) to leak out/to escape/to come through/to shine through/to filter out/to be omitted/(P)
 KanaVerb( うろたえる ) // (v1,vi) to be flustered/to loose one's presence of mind
 KanaVerb( おいさらばえる ) // (v1,vi) to become decrepit and ugly with age
 KanaVerb( おいる ) // (v1,vi) to age/to grow old/(P)
 KanaVerb( おいこむ ) // (v5m,vi) to grow old/to weaken with age/to become senile
 KanaVerb( おいぼれる ) // (v1,vi) to become decrepit/to become senile
 KanaVerb( ふける ) // (v1,vi) to age/(P)
 KanaVerb( ふけこむ ) // (v5m,vi) to age/to become old
 KanaVerb( ろうする ) // (vs-s) to deafen
 KanaVerb( ろんじつくす ) // (v5s) to deal exhaustively with/(P)
 KanaVerb( なごむ ) // (v5m) to be softened/to calm down/(P)
 KanaVerb( やわらぐ ) // (v5g,vi) to soften/to calm down/to be mitigated/(P)
 KanaVerb( はなしがつく ) // (v5k) to come to an agreement
 KanaVerb( はなしだす ) // (v5s) to tell the truth/to open up
 KanaVerb( はなせる ) // (v1,vi) to be understanding/to be sensible
 KanaVerb( いがむ ) // (v5m,vi) to warp/to swerve/to deflect/to be crooked/to be distorted/to be bent/to incline/to slant/to be perverted/to be gross-grained/to get bent/to be strained
 KanaVerb( ひずむ ) // (v5m,vi) to warp/to swerve/to deflect/to be crooked/to be distorted/to be bent/to incline/to slant/to be perverted/to be gross-grained/to get bent/to be strained
 KanaVerb( ゆがむ ) // (v5m,vi) to warp/to swerve/to deflect/to be crooked/to be distorted/to be bent/to incline/to slant/to be perverted/to be gross-grained/to get bent/to be strained/(P)
 KanaVerb( まどう ) // (v5u,vi) to be puzzled
 KanaVerb( まどわせる ) // (v1) to lead astray
 KanaVerb( うでづく ) // (v5k) to do one's best/to do by force
 KanaVerb( ほのめく ) // (v5k,vi) to be seen dimly/glimmer
 KanaVerb( たたずむ ) // (v5m,vi) (uk) to stand (still) a while/to loiter/to stop/(P)
 KanaVerb( わびる ) // (v1,vi) to be worried/to be grieved/to pine for
 KanaVerb( おびる ) // (v1) to wear/to put on (a sword)
 KanaVerb( ふす ) // (v5s) to bend down/to bow down/to prostrate oneself
 KanaVerb( うつむく ) // (v5k) to hang one's head in shame/to look downward/to cast one's eyes down
 KanaVerb( うつぶす ) // (v5s) to lie on one's face
 KanaVerb( なす ) // (v5s) to make
 KanaVerb( さえる ) // (v1,vi) to be clear/to be serene/to be cold/to be skillful
 KanaVerb( ほえる ) // (v1,vi) to bark/to bay/to howl/to bellow/to roar/to cry
 KanaVerb( とがめる ) // (v1) to blame/to find fault/to challenge/to threaten/to take someone to task/to aggravate (an injury)/(P)
 KanaVerb( つぶやく ) // (v5k,vi) to mutter/to murmur/(P)
 KanaVerb( うめく ) // (v5k,vi) to moan/to groan
 KanaVerb( いがみあう ) // (v5u,vi) to snarl/to quarrel
 KanaVerb( あえぐ ) // (v5g,vi) to gasp/breathe hard
 KanaVerb( なく ) // (v5k) (1) to sing (bird)/(2) to bark/to purr/to make sound (animal)
 KanaVerb( しゃがれる ) // (v1,vi) (uk) to become hoarse
 KanaVerb( しわがれる ) // (v1,vi) (uk) to become hoarse
 KanaVerb( わらう ) // (v5u,vi) to laugh/to smile
 KanaVerb( えづく ) // (v5k,vi) to vomit
 KanaVerb( むせる ) // (v1,vi) to choke over/to be choked by
 KanaVerb( むせぶ ) // (v5b,vi) to be choked/to be stifled/to be smothered
 KanaVerb( いななく ) // (v5k,vi) to neigh
 KanaVerb( あざけりわらう ) // (v5u) to laugh to scorn
 KanaVerb( うそぶく ) // (v5k,vi) (uk) to exaggerate
 KanaVerb( ささやく ) // (v5k,vi) to whisper/to murmur/(P)
 KanaVerb( こびる ) // (v1,vi) to flatter/to curry favor with/to curry favour with/to flirt with/to fawn on
 KanaVerb( こびへつらう ) // (v5u,vi) to toady/to be obsequious
 KanaVerb( はらむ ) // (v5m,vi) to conceive/to become pregnant/to get filled with/(P)
 KanaVerb( つるむ ) // (v5m,vi) to copulate (animals)/to mate
 KanaVerb( はまりこむ ) // (v5m) (1) to get stuck in/to be mired in/(2) to be addicted to
 KanaVerb( ふざける ) // (v1) to romp/to gambol/to frolic/to joke/to make fun of/to flirt
 KanaVerb( やむ ) // (v5m,vi) to cease/to stop/to be over
 KanaVerb( すいせいのようにあらわれる ) // (v1) to become famous overnight/to burst into fame
 KanaVerb( さまよう ) // (v5u,vi) to loiter/to putter/to prowl/to wander about/to roam about/to knock around/(P)
 KanaVerb( うろつく ) // (v5k,vi) (1) (uk) to loiter/to putter/to prowl/to wander aimlessly/to knock around/(2) to be confused from not knowing what to do/(P)
 KanaVerb( とぼける ) // (v1,vi) (1) to play dumb/to feign ignorance/to play innocent/to have a blank facial expression/(2) to play the fool/(3) to be in one's dotage
 KanaVerb( しょげる ) // (v1,vi) to be dispirited/to be dejected/to be disheartened/to lose heart
 KanaVerb( しょげこむ ) // (v5m,vi) to be utterly disheartened
 KanaVerb( あこがれる ) // (v1,vi) to long for/to yearn after/to admire/to be attracted by
 KanaVerb( つく ) // (v5k) to possess/to haunt/to attach to
 KanaVerb( さておく ) // (v5k) (uk) to set aside
 KanaVerb( えぐれる ) // (v1,vi) to be gouged/to be hollowed/to become hollow
 KanaVerb( ねじくれる ) // (v1,vi) to curve/to twist/to be rebellious
 KanaVerb( ねじける ) // (v1,vi) to curve/to twist/to be rebellious
 KanaVerb( すねる ) // (v1,vi) to be peevish/to sulk/to pout
 KanaVerb( こじれる ) // (v1,vi) to get complicated/to grow worse
 KanaVerb( ひねくれる ) // (v1,vi) to be contrary/to be uncooperative/to be rebellious
 KanaVerb( ひしげる ) // (v1,vi) (1) to be crushed/to be squashed (flat)/(2) to be discouraged
 KanaVerb( ひしゃげる ) // (v1,vi) (1) to be crushed/to be squashed (flat)/(2) to be discouraged
 KanaVerb( へしゃげる ) // (v1,vi) (1) to be crushed/to be squashed (flat)/(2) to be discouraged
 KanaVerb( ねじれる ) // (v1,vi) to twist/to wrench/to screw
 KanaVerb( よじれる ) // (v1,vi) to be twisted
 KanaVerb( もめる ) // (v1,vi) to disagree/to dispute/(P)
 KanaVerb( からかう ) // (v5u) (uk) to ridicule/to tease/to banter with/to make fun of/(P)
 KanaVerb( からみあう ) // (v5u,vi) to be(come) intertwined/to be entangled
 KanaVerb( つきまぜる ) // (v1) to pound together/to mix together
 KanaVerb( かちあう ) // (v5u,vi) to clash/to be in conflict with
 KanaVerb( しなだれる ) // (v1,vi) to droop
 KanaVerb( ぼける ) // (v1,vi) (1) to grow senile/(2) to fade (colour, color)/(P)
 KanaVerb( のたまう ) // (v5u) to say (polite)/to be pleased say (hint of sarcasm)
 KanaVerb( うつをさんじる ) // (v1) to chase one's gloom away/to free one's thoughts from melancholy
 KanaVerb( そばだてる ) // (v1) to strain to hear/to prick up one's ears
 KanaVerb( ぼっする ) // (vs-s) to die
 KanaVerb( しみつく ) // (v5k,vi) to be indelibly stained or ingrained/to be dyed in deeply
 KanaVerb( しゃれる ) // (v1,vi) to joke/to play on words/to dress stylishly/(P)
 KanaVerb( しゃれこむ ) // (v5m,vi) to get dressed up
 KanaVerb( さらう ) // (v5u) to sweep away/to wash away/to dredge/(P)
 KanaVerb( かれる ) // (v1,vi) to dry up (spring, pond, etc.)/to run out
 KanaVerb( しみる ) // (v1,vi) (1) to pierce/to penetrate/to soak in/to permeate/(2) to be infected (with vice)/to be steeped (with prejudice)
 KanaVerb( しみこむ ) // (v5m,vi) to soak into/to permeate
 KanaVerb( にじみでる ) // (v1,vi) to exude/to ooze/to seep out
 KanaVerb( にじむ ) // (v5m) to run/to blur/to spread/to blot/to ooze/(P)
 KanaVerb( あぶりだす ) // (v5s) to reveal invisible writing by applying heat
 KanaVerb( きらめく ) // (v5k,vi) to glitter/to glisten/to sparkle/to twinkle/to glare/to gleam
 KanaVerb( くゆらす ) // (v5s) to smoke (e.g., a pipe)/to puff (a cigarette)
 KanaVerb( おこす ) // (v5s) to light a fire
 KanaVerb( ただれる ) // (v1,vi) to be sore/to be inflamed/to be bleary/to fester
 KanaVerb( ひしめきあう ) // (v5u) to crowd together in a confined space/to gather and make a commotion
 KanaVerb( ひしめく ) // (v5k,vi) (uk) to clamour/to crowd/to jostle
 KanaVerb( なれる ) // (v1,vi) to grow accustomed to/to become domesticated/to become tame/to get too familiar with
 KanaVerb( きずつける ) // (v1) to injure/to damage
 KanaVerb( うずく ) // (v5k,vi) (uk) to throb/to ache
 KanaVerb( しびれる ) // (v1,vi) to become numb/to go to sleep (e.g., a limb)/(P)
 KanaVerb( やせる ) // (v1,vi) to become thin/to lose weight/to reduce (one's) weight/to slim
 KanaVerb( ひびがきれる ) // (v1) to be chapped (e.g., skin)
 KanaVerb( とろける ) // (v1,vi) to be enchanted with
 KanaVerb( くらむ ) // (v5m) to become dizzy
 KanaVerb( にらみあう ) // (v5u,vi) to glare at each other
 KanaVerb( どうじゃくたらしめる ) // (v1) to strike someone dumb with astonishment
 KanaVerb( けがれる ) // (v1,vi) to get dirty/to become dirty
 KanaVerb( すくむ ) // (v5m,vi) to cower/to be cramped
 KanaVerb( ふるいにかける ) // (v1) (uk) to sieve/to sift
 KanaVerb( ふるいおとす ) // (v5s) to sift out/to screen or eliminate (candidates)
 KanaVerb( ほだされる ) // (v1,vi) to be moved by affection/to be moved by kindness
 KanaVerb( よれる ) // (v1,vi) to get twisted/to get kinked
 KanaVerb( すがりつく ) // (v5k,vi) to cling to
 KanaVerb( もつれる ) // (v1,vi) to tangle/to become complicated/to get twisted/(P)
 KanaVerb( もつれこむ ) // (v5m,vi) to proceed though deadlocked
 KanaVerb( はぜる ) // (v1,vi) to burst open/to pop/to split
 KanaVerb( はじらう ) // (v5u,vi) to feel shy/to be bashful/to blush
 KanaVerb( そびえる ) // (v1,vi) to rise/to tower/to soar/(P)
 KanaVerb( そびえたつ ) // (v5t) to stand towering over the surrounds
 KanaVerb( そそりたつ ) // (v5t) to rise (steeply)/to tower/to soar
 KanaVerb( かきあげる ) // (v1) to shoulder (palanquin)
 KanaVerb( かきいれる ) // (v1) to carry in
 KanaVerb( もやう ) // (v5u) to moor (a boat)
 KanaVerb( うごめく ) // (v5k,vi) to wriggle/to squirm/to crawl like a worm
 KanaVerb( あせる ) // (v1,vi) to fade/to discolor/to discolour/(P)
 KanaVerb( さめる ) // (v1,vi) to fade/to discolour/to discolor
 KanaVerb( しょうする ) // (vs-s) to recite/to chant/to read aloud
 KanaVerb( あらがう ) // (v5u,vi) (1) to dispute/to argue/to be at variance/(2) to compete/to contest/(3) to deny (e.g., evidence)
 KanaVerb( いさかう ) // (v5u,vi) to quarrel/to dispute
 KanaVerb( へつらう ) // (v5u,vi) to flatter
 KanaVerb( そらんじる ) // (v1) to memorize/to memorise/to recite from memory
 KanaVerb( ふうする ) // (vs-s) to hint/to insinuate/to satirize/to satirise
 KanaVerb( うたわれる ) // (v1,vi) to be admired/to be stipulated/to be clearly expressed
 KanaVerb( むさぼりくう ) // (v5u) to devour greedily
 KanaVerb( むさぼりくらう ) // (v5u) to devour greedily
 KanaVerb( むさぼりよむ ) // (v5m) to read a book avidly
 KanaVerb( もたらす ) // (v5s) (uk) to bring/to take/to bring about/(P)
 KanaVerb( ひざまずく ) // (v5k,vi) (uk) to kneel/(P)
 KanaVerb( よろける ) // (v1,vi) to stagger/to stumble
 KanaVerb( よろめく ) // (v5k,vi) (uk) to stagger/(P)
 KanaVerb( ためらう ) // (v5u,vi) (uk) to hesitate/(P)
 KanaVerb( つまずく ) // (v5k,vi) to stumble/to trip/(P)
 KanaVerb( つまづく ) // (v5k,vi) to stumble/to trip
 KanaVerb( しつける ) // (v1) to train/to discipline/to teach manners
 KanaVerb( きしむ ) // (v5m,vi) (uk) to jar/to creak/to grate
 KanaVerb( ひなびる ) // (v1,vi) to become rustic/to be countrified
 KanaVerb( とける ) // (v1,vi) to melt/to thaw/to fuse/to dissolve
 KanaVerb( つかえる ) // (v1,vi) to be blocked/to choke/to be obstructed/to feel a pressure on one's chest
 KanaVerb( つっかえる ) // (v1,vi) to be blocked/to choke/to be obstructed/to feel a pressure on one's chest
 KanaVerb( たける ) // (v1,vi) (1) to excel at/to be proficient at/(2) to grow old/(3) to ripen/(4) to rise high (e.g., the sun)
 KanaVerb( もたれる ) // (v1,vi) to lean against/to lean on/to recline on/to lie heavy (on the stomach)
 KanaVerb( うなずく ) // (v5k,vi) (uk) to nod/to bow one's head in assent/(P)
 KanaVerb( くずおれる ) // (v1,vi) to collapse (physically or emotionally)/to fall down
 KanaVerb( ふるえる ) // (v1,vi) to shiver/to shake/to quake
 KanaVerb( すえる ) // (v1,vi) to go bad/to turn sour
 KanaVerb( うえる ) // (v1,vi) to be hungry/to starve/to thirst
 KanaVerb( おどろく ) // (v5k,vi) to be surprised/to be astonished
 KanaVerb( だましあう ) // (v5u) to cheat each other
 KanaVerb( うなされる ) // (v1,vi) to have a nightmare
 KanaVerb( なびかせる ) // (v1) to fly/to flutter/to win over/to win one's heart/to subdue
 KanaVerb( なびく ) // (v5k,vi) to bend/to flutter/to wave/to bow to/to yield to/to obey/to be swayed by/(P)
 KanaVerb( かびる ) // (v1,vi) to become moldy or musty (mouldy)
 KanaVerb( かじりちらす ) // (v5s) to gnaw at and scatter around/to start a lot of things without finishing any
 KanaVerb( かじりつく ) // (v5k,vi) to bite into/to stick to
 KanaVerb( かぶりつく ) // (v5k,vi) to bite into/to stick to

 
 
 KanaVerb_5r( いびる, JAP_TRANSITIVE ) // (v5r,vt) to pick on/to tease
 KanaVerb_5r( おちょくる, JAP_TRANSITIVE ) // (v5r,vt) to tease/to banter/to make fun of somebody
 KanaVerb_5r( しゃぶる, JAP_TRANSITIVE ) // (v5r,vt) to suck/to chew
 KanaVerb_5r( せびる, JAP_TRANSITIVE ) // (v5r,vt) to demand money/to pester/to extort
 KanaVerb_5r( ちょくる, JAP_TRANSITIVE ) // (v5r,vt) to tease/to banter/to make fun of somebody
 KanaVerb_5r( ちょんぎる, JAP_TRANSITIVE ) // (v5r,vt) to chop something off (e.g., head)/to snip off/to fire
 KanaVerb_5r( なぞる, JAP_TRANSITIVE ) // (v5r,vt) to trace (drawing)/to follow
 KanaVerb_5r( アジる, JAP_TRANSITIVE ) // (v5r,vt) to stir up/to instigate (somebody to do something)
 KanaVerb_5r( ネグる, JAP_TRANSITIVE ) // (v5r,vt) to neglect
 KanaVerb_5r( ミスる, JAP_TRANSITIVE ) // (v5r,vt) to make a mistake/to mess up
 KanaVerb_5r( メモる, JAP_TRANSITIVE ) // (v5r,vt) to take notes
 KanaVerb_5r( いとしがる, JAP_TRANSITIVE ) // (v5r,vt) to treat with love/to pity/to cherish
 KanaVerb_5r( にぎる, JAP_TRANSITIVE ) // (v5r,vt) to grasp/to seize/to mould sushi/to mold sushi/(P)
 KanaVerb_5r( へしおる, JAP_TRANSITIVE ) // (v5r,vt) to smash/to break
 KanaVerb_5r( してやる, JAP_TRANSITIVE ) // (v5r,vt) to do for (someone)/to deceive/to hoodwink
 KanaVerb_5r( ひきちぎる, JAP_TRANSITIVE ) // (v5r,vt) to tear off
 KanaVerb_5r( ひっくくる, JAP_TRANSITIVE ) // (v5r,vt) to bundle/to tie up
 KanaVerb_5r( ひったくる, JAP_TRANSITIVE ) // (v5r,vt) to snatch (steal) from
 KanaVerb_5r( ひっぱる, JAP_TRANSITIVE ) // (v5r,vt) (1) to pull/to draw/to stretch/to drag/(2) to pull the ball (baseball)/(P)
 KanaVerb_5r( ひっかぶる, JAP_TRANSITIVE ) // (v5r,vt) to take upon oneself/to pull (a thing) over one's head
 KanaVerb_5r( ひきさる, JAP_TRANSITIVE ) // (v5r,vt) to retreat/to withdraw/to deduct
 KanaVerb_5r( ひきしぼる, JAP_TRANSITIVE ) // (v5r,vt) to draw bow to limit/to draw aside curt
 KanaVerb_5r( ひきとる, JAP_TRANSITIVE ) // (v5r,vt) to take charge of/to take over/to retire to a private place/(P)
 KanaVerb_5r( ひきずる, JAP_TRANSITIVE ) // (v5r,vt) to seduce/to drag along/to pull/to prolong/to support
 KanaVerb_5r( のみまわる, JAP_TRANSITIVE ) // (v5r,vt) to drink at a round of places
 KanaVerb_5r( はおる, JAP_TRANSITIVE ) // (v5r,vt) to put on
 KanaVerb_5r( うかがいしる, JAP_TRANSITIVE ) // (v5r,vt) to perceive/to understand
 KanaVerb_5r( えいじる, JAP_TRANSITIVE ) // (v5r,vt) to compose (e.g., poem)/to recite/to sing
 KanaVerb_5r( ふちどる, JAP_TRANSITIVE ) // (v5r,vt) to (add a) border or fringe
 KanaVerb_5r( おしやる, JAP_TRANSITIVE ) // (v5r,vt) to push or thrust away
 KanaVerb_5r( おしやぶる, JAP_TRANSITIVE ) // (v5r,vt) to break through
 KanaVerb_5r( おしきる, JAP_TRANSITIVE ) // (v5r,vt) (1) to have one's own way/(2) to press and cut
 KanaVerb_5r( よこぎる, JAP_TRANSITIVE ) // (v5r,vt) to cross (e.g., arms)/to traverse/(P)
 KanaVerb_5r( なぐる, JAP_TRANSITIVE ) // (v5r,vt) to strike/to hit/(P)
 KanaVerb_5r( したまわる, JAP_TRANSITIVE ) // (v5r,vt) to be less than/to be lower than
 KanaVerb_5r( よめいる, JAP_TRANSITIVE ) // (v5r,vt) to wed/to marry a man
 KanaVerb_5r( わりふる, JAP_TRANSITIVE ) // (v5r,vt) to assign/to allot/to divide among/to distribute/to prorate/to assess
 KanaVerb_5r( わる, JAP_TRANSITIVE ) // (v5r,vt) to divide/to cut/to break/to halve/to separate/to split/to rip/to crack/to smash/to dilute/(P)
 KanaVerb_5r( かみきる, JAP_TRANSITIVE ) // (v5r,vt) to bite off/to gnaw through
 KanaVerb_5r( かりとる, JAP_TRANSITIVE ) // (v5r,vt) to mow/to reap/to harvest
 KanaVerb_5r( かんぐる, JAP_TRANSITIVE ) // (v5r,vt) to be suspicious of
 KanaVerb_5r( かんじとる, JAP_TRANSITIVE ) // (v5r,vt) to feel/(P)
 KanaVerb_5r( きどる, JAP_TRANSITIVE ) // (v5r,vt) to affect/to put on airs/(P)
 KanaVerb_5r( けどる, JAP_TRANSITIVE ) // (v5r,vt) to suspect/to sense
 KanaVerb_5r( うたぐる, JAP_TRANSITIVE ) // (v5r,vt) to doubt/to distrust/to be suspicious of/to suspect
 KanaVerb_5r( なじる, JAP_TRANSITIVE ) // (v5r,vt) to rebuke/to scold/to tell off
 KanaVerb_5r( すいとる, JAP_TRANSITIVE ) // (v5r,vt) to suck up/to absorb/to squeeze (money)
 KanaVerb_5r( くみとる, JAP_TRANSITIVE ) // (v5r,vt) to scoop out/to pump out/to understand
 KanaVerb_5r( ぎゅうじる, JAP_TRANSITIVE ) // (v5r,vt) to control/to take the lead in/to have under one's thumb
 KanaVerb_5r( あさる, JAP_TRANSITIVE ) // (v5r,vt) to fish for/to look for/(P)
 KanaVerb_5r( せる, JAP_TRANSITIVE ) // (v5r,vt) to compete/to bid/to sell at auction/(P)
 KanaVerb_5r( ねだる, JAP_TRANSITIVE ) // (v5r,vt) (1) to solicit/to demand/to extort/(v5r,vt) (2) to tease/to coax/(P)
 KanaVerb_5r( おそわる, JAP_TRANSITIVE ) // (v5r,vt) to be taught/(P)
 KanaVerb_5r( おどしとる, JAP_TRANSITIVE ) // (v5r,vt) to extort (money)/to blackmail
 KanaVerb_5r( おおせつかる, JAP_TRANSITIVE ) // (v5r,vt) to receive a command/to be appointed/to be ordered
 KanaVerb_5r( くぎる, JAP_TRANSITIVE ) // (v5r,vt) to punctuate/to cut off/to mark off/to delimit/to stop/to put an end to/(P)
 KanaVerb_5r( くまどる, JAP_TRANSITIVE ) // (v5r,vt) to make up/to shade
 KanaVerb_5r( いやがる, JAP_TRANSITIVE ) // (v5r,vt) to hate/to dislike/(P)
 KanaVerb_5r( みてとる, JAP_TRANSITIVE ) // (v5r,vt) to perceive/to grasp (the situation)
 KanaVerb_5r( みやる, JAP_TRANSITIVE ) // (v5r,vt) to look at
 KanaVerb_5r( みかぎる, JAP_TRANSITIVE ) // (v5r,vt) to give up/to turn one's back/to abandon/(P)
 KanaVerb_5r( みあやまる, JAP_TRANSITIVE ) // (v5r,vt) to mistake someone for someone else/to misread
 KanaVerb_5r( みとる, JAP_TRANSITIVE ) // (v5r,vt) to perceive/to understand
 KanaVerb_5r( みまもる, JAP_TRANSITIVE ) // (v5r,vt) to watch over/to watch attentively/(P)
 KanaVerb_5r( みきる, JAP_TRANSITIVE ) // (v5r,vt) to see everything/to abandon/to sell at a loss
 KanaVerb_5r( みおくる, JAP_TRANSITIVE ) // (v5r,vt) (1) to see off/to farewell/(2) to escort/(3) to let pass/to wait and see/(4) to let a pitch go by (baseball)/to watch a batted ball go into the stands/(P)
 KanaVerb_5r( みしる, JAP_TRANSITIVE ) // (v5r,vt) to recognise/to know by sight/to become acquainted with
 KanaVerb_5r( みはる, JAP_TRANSITIVE ) // (v5r,vt) to watch/to (stand) guard/to look out/to open one's eyes wide/(P)
 KanaVerb_5r( みやぶる, JAP_TRANSITIVE ) // (v5r,vt) to see through another's thoughts/to have a sharp eye/to penetrate/to fathom/(P)
 KanaVerb_5r( みくびる, JAP_TRANSITIVE ) // (v5r,vt) to underrate/to belittle/to look down on/to despise/(P)
 KanaVerb_5r( いいまくる, JAP_TRANSITIVE ) // (v5r,vt) to talk volubly
 KanaVerb_5r( いいやる, JAP_TRANSITIVE ) // (v5r,vt) to send word
 KanaVerb_5r( いいあやまる, JAP_TRANSITIVE ) // (v5r,vt) to say by mistake/to make a slip of the tongue
 KanaVerb_5r( いいしぶる, JAP_TRANSITIVE ) // (v5r,vt) to hesitate to say
 KanaVerb_5r( いいきる, JAP_TRANSITIVE ) // (v5r,vt) to declare/to assert/to state definitively
 KanaVerb_5r( いいおくる, JAP_TRANSITIVE ) // (v5r,vt) to send a message/to write to
 KanaVerb_5r( いいはる, JAP_TRANSITIVE ) // (v5r,vt) to insist/to assert/to be obstinate in saying
 KanaVerb_5r( いいやぶる, JAP_TRANSITIVE ) // (v5r,vt) to argue down/to confute
 KanaVerb_5r( いいつかる, JAP_TRANSITIVE ) // (v5r,vt) to be ordered
 KanaVerb_5r( ことづかる, JAP_TRANSITIVE ) // (v5r,vt) to be entrusted with/to be asked to
 KanaVerb_5r( よびまわる, JAP_TRANSITIVE ) // (v5r,vt) to call out (for someone)
 KanaVerb_5r( さとる, JAP_TRANSITIVE ) // (v5r,vt) to attain enlightenment/to perceive/to understand/to discern/(P)
 KanaVerb_5r( くちばしる, JAP_TRANSITIVE ) // (v5r,vt) to speak/to tell/to blurt out/(P)
 KanaVerb_5r( たくむ, JAP_TRANSITIVE ) // (v5r,vt) to devise/to plot/to plan
 KanaVerb_5r( こくる, JAP_TRANSITIVE ) // (v5r,vt) to confess (one's love)
 KanaVerb_5r( さしくる, JAP_TRANSITIVE ) // (v5r,vt) to arrange/to manage
 KanaVerb_5r( はつる, JAP_TRANSITIVE ) // (v5r,vt) (1) to cut down little by little/(2) to take a percentage
 KanaVerb_5r( しぼりとる, JAP_TRANSITIVE ) // (v5r,vt) to exploit
 KanaVerb_5r( しぼる, JAP_TRANSITIVE ) // (v5r,vt) to press/to wring/to squeeze/(P)
 KanaVerb_5r( しかかる, JAP_TRANSITIVE ) // (v5r,vt) (1) to start something/(2) to have started something, but not yet finished it
 KanaVerb_5r( つかいきる, JAP_TRANSITIVE ) // (v5r,vt) to use up/to exhaust/to wear out
 KanaVerb_5r( つかさどる, JAP_TRANSITIVE ) // (v5r,vt) to rule/to govern/to administer
 KanaVerb_5r( おもいとどまる, JAP_TRANSITIVE ) // (v5r,vt) to give up (a plan or idea or idea)/to desist from (doing)
 KanaVerb_5r( おもいしる, JAP_TRANSITIVE ) // (v5r,vt) to realize/to realise
 KanaVerb_5r( たまわる, JAP_TRANSITIVE ) // (v5r,vt) to be given/to be granted/to be honored with/to be honoured with
 KanaVerb_5r( もちまわる, JAP_TRANSITIVE ) // (v5r,vt) to carry about
 KanaVerb_5r( しかる, JAP_TRANSITIVE ) // (v5r,vt) to scold/(P)
 KanaVerb_5r( すてさる, JAP_TRANSITIVE ) // (v5r,vt) to abandon (ship)
 KanaVerb_5r( さえぎる, JAP_TRANSITIVE ) // (v5r,vt) to interrupt/to intercept/to obstruct/(P)
 KanaVerb_5r( かりきる, JAP_TRANSITIVE ) // (v5r,vt) to reserve
 KanaVerb_5r( とりさる, JAP_TRANSITIVE ) // (v5r,vt) to remove/to eliminate
 KanaVerb_5r( とりしきる, JAP_TRANSITIVE ) // (v5r,vt) to run or operate a business/to manage all by oneself
 KanaVerb_5r( とりしまる, JAP_TRANSITIVE ) // (v5r,vt) to manage/to control/to supervise
 KanaVerb_5r( まもる, JAP_TRANSITIVE ) // (v5r,vt) to protect/to obey/to guard/to abide (by the rules)/(P)
 KanaVerb_5r( たぐる, JAP_TRANSITIVE ) // (v5r,vt) to pull in (rope)
 KanaVerb_5r( かる, JAP_TRANSITIVE ) // (v5r,vt) to hunt
 KanaVerb_5r( うけとる, JAP_TRANSITIVE ) // (v5r,vt) to receive/to get/to accept/to take/to interpret/to understand
 KanaVerb_5r( さずかる, JAP_TRANSITIVE ) // (v5r,vt) to be gifted/to be awarded/(P)
 KanaVerb_5r( ける, JAP_TRANSITIVE ) // (v5r,vt) to kick/(P)
 KanaVerb_5r( けやぶる, JAP_TRANSITIVE ) // (v5r,vt) to kick in or open/to smash through
 KanaVerb_5r( だししぶる, JAP_TRANSITIVE ) // (v5r,vt) to grudge/to be stingy/to be unwilling to pay
 KanaVerb_5r( だしきる, JAP_TRANSITIVE ) // (v5r,vt) to use up/to do one's best
 KanaVerb_5r( でしぶる, JAP_TRANSITIVE ) // (v5r,vt) to be unwilling to go out
 KanaVerb_5r( かきなぐる, JAP_TRANSITIVE ) // (v5r,vt) to scribble (write quickly)/to dash off
 KanaVerb_5r( かきまくる, JAP_TRANSITIVE ) // (v5r,vt) to dash off/to write freely
 KanaVerb_5r( かきあやまる, JAP_TRANSITIVE ) // (v5r,vt) to miswrite
 KanaVerb_5r( かきとる, JAP_TRANSITIVE ) // (v5r,vt) to write down/to take dictation/to take notes/(P)
 KanaVerb_5r( かきおくる, JAP_TRANSITIVE ) // (v5r,vt) to write
 KanaVerb_5r( かちとる, JAP_TRANSITIVE ) // (v5r,vt) to exert oneself and win/to gain (victory)
 KanaVerb_5r( めしあがる, JAP_TRANSITIVE ) // (v5r,vt) (pol) to eat/(P)
 KanaVerb_5r( めしとる, JAP_TRANSITIVE ) // (v5r,vt) to arrest/to apprehend
 KanaVerb_5r( うけたまわる, JAP_TRANSITIVE ) // (v5r,vt) (1) (hum) to hear/to be told/to know/(2) to receive (order)/(P)
 KanaVerb_5r( けしさる, JAP_TRANSITIVE ) // (v5r,vt) to get rid of/to erase
 KanaVerb_5r( やききる, JAP_TRANSITIVE ) // (v5r,vt) to burn off
 KanaVerb_5r( のりとる, JAP_TRANSITIVE ) // (v5r,vt) to capture/to occupy/to usurp
 KanaVerb_5r( かざる, JAP_TRANSITIVE ) // (v5r,vt) to decorate/to ornament/to adorn/(P)
 KanaVerb_5r( ぬぐいとる, JAP_TRANSITIVE ) // (v5r,vt) to wipe off/to wipe out/to expunge
 KanaVerb_5r( ふきとる, JAP_TRANSITIVE ) // (v5r,vt) to wipe off/to wipe up
 KanaVerb_5r( いろどる, JAP_TRANSITIVE ) // (v5r,vt) to colour/to color/to paint/to make up
 KanaVerb_5r( くいきる, JAP_TRANSITIVE ) // (v5r,vt) to bite through/to eat up
 KanaVerb_5r( くいしばる, JAP_TRANSITIVE ) // (v5r,vt) to set one's teeth/to clench one's teeth
 KanaVerb_5r( ねとる, JAP_TRANSITIVE ) // (v5r,vt) to steal another's wife (husband, lover)
 KanaVerb_5r( ふりしぼる, JAP_TRANSITIVE ) // (v5r,vt) (1) to muster (one's strength)/(2) to strain (e.g., one's voice)
 KanaVerb_5r( ふりきる, JAP_TRANSITIVE ) // (v5r,vt) to shake off/to shake free from/(P)
 KanaVerb_5r( ふる, JAP_TRANSITIVE ) // (v5r,vt) (1) to wave/to shake/to swing/(2) to sprinkle/(3) to cast (actor)/to allocate (work)/(4) to turn down (somebody)/to reject/to jilt/(5) to abandon/to give up/to ruin/(P)
 KanaVerb_5r( もうしおくる, JAP_TRANSITIVE ) // (v5r,vt) to write to/to send word to/to hand over (official business)
 KanaVerb_5r( しんずる, JAP_TRANSITIVE ) // (v5r,vt) to offer/to present
 KanaVerb_5r( おしはかる, JAP_TRANSITIVE ) // (v5r,vt) to guess/to conjecture/to surmise
 KanaVerb_5r( いけどる, JAP_TRANSITIVE ) // (v5r,vt) to capture alive/to take prisoner
 KanaVerb_5r( きりわる, JAP_TRANSITIVE ) // (v5r,vt) to cut in two
 KanaVerb_5r( きりまくる, JAP_TRANSITIVE ) // (v5r,vt) to attack and scatter/to argue vehemently
 KanaVerb_5r( きりとる, JAP_TRANSITIVE ) // (v5r,vt) to cut off/to excise/to tear off/to cut out/to whittle down/to tear out/to cut down/to amputate
 KanaVerb_5r( きりいる, JAP_TRANSITIVE ) // (v5r,vt) to cut into/to raid
 KanaVerb_5r( きりやぶる, JAP_TRANSITIVE ) // (v5r,vt) to cut to pieces
 KanaVerb_5r( おる, JAP_TRANSITIVE ) // (v5r,vt) to break/to fold/to pick flower/(P)
 KanaVerb_5r( ほじくる, JAP_TRANSITIVE ) // (v5r,vt) (uk) to dig up/to peck at
 KanaVerb_5r( ほじる, JAP_TRANSITIVE ) // (v5r,vt) (uk) to dig up/to peck at
 KanaVerb_5r( えりすぐる, JAP_TRANSITIVE ) // (v5r,vt) to choose the best
 KanaVerb_5r( かいぐる, JAP_TRANSITIVE ) // (v5r,vt) to haul in hand over hand
 KanaVerb_5r( かききる, JAP_TRANSITIVE ) // (v5r,vt) to cut/to slit
 KanaVerb_5r( かきむしる, JAP_TRANSITIVE ) // (v5r,vt) to tear off/to pluck/to scratch off
 KanaVerb_5r( あやつる, JAP_TRANSITIVE ) // (v5r,vt) to manipulate/to operate/to pull strings/(P)
 KanaVerb_5r( あいてどる, JAP_TRANSITIVE ) // (v5r,vt) to take on an opponent/to challenge/(P)
 KanaVerb_5r( ほうむりさる, JAP_TRANSITIVE ) // (v5r,vt) to consign to oblivion
 KanaVerb_5r( ほうむる, JAP_TRANSITIVE ) // (v5r,vt) to bury/to inter/to entomb/to consign to oblivion/to shelve/(P)
 KanaVerb_5r( おくる, JAP_TRANSITIVE ) // (v5r,vt) to send/to give to/to award to/to confer on/(P)
 KanaVerb_5r( つくる, JAP_TRANSITIVE ) // (v5r,vt) to make/to create/to manufacture/to draw up/to write/to compose/to build/to coin/to cultivate/to organize/to organise/to establish/to make up (a face)/to trim (a tree)/to fabricate/to prepare (food)/to commit (sin)/to construct/(P)
 KanaVerb_5r( うちまくる, JAP_TRANSITIVE ) // (v5r,vt) to pound away
 KanaVerb_5r( うちわる, JAP_TRANSITIVE ) // (v5r,vt) to split/to disclose
 KanaVerb_5r( うちきる, JAP_TRANSITIVE ) // (v5r,vt) to stop/to abort/to discontinue/to close/(P)
 KanaVerb_5r( うちやぶる, JAP_TRANSITIVE ) // (v5r,vt) to hit
 KanaVerb_5r( ぶんなぐる, JAP_TRANSITIVE ) // (v5r,vt) to knock
 KanaVerb_5r( かしきる, JAP_TRANSITIVE ) // (v5r,vt) to reserve/to charter
 KanaVerb_5r( たたきわる, JAP_TRANSITIVE ) // (v5r,vt) to smash/to break into pieces
 KanaVerb_5r( うばいとる, JAP_TRANSITIVE ) // (v5r,vt) to plunder
 KanaVerb_5r( たどる, JAP_TRANSITIVE ) // (v5r,vt) to follow (road)/to pursue (course)/to follow up/(P)
 KanaVerb_5r( さぐる, JAP_TRANSITIVE ) // (v5r,vt) to search/to look for/to sound out/(P)
 KanaVerb_5r( はしおる, JAP_TRANSITIVE ) // (v5r,vt) to tuck up/to abridge
 KanaVerb_5r( はしょる, JAP_TRANSITIVE ) // (v5r,vt) to tuck up/to abridge
 KanaVerb_5r( ことわる, JAP_TRANSITIVE ) // (v5r,vt) (1) to refuse/to reject/to dismiss/to turn down/to decline/(2) to inform/to give notice/(3) to ask leave/to excuse oneself (from)
 KanaVerb_5r( ねぎる, JAP_TRANSITIVE ) // (v5r,vt) to drive a bargain/to beat down the price/to haggle/(P)
 KanaVerb_5r( しる, JAP_TRANSITIVE ) // (v5r,vt) to know/to understand/to be acquainted with/to feel/(P)
 KanaVerb_5r( きかざる, JAP_TRANSITIVE ) // (v5r,vt) to dress up/(P)
 KanaVerb_5r( ほる, JAP_TRANSITIVE ) // (v5r,vt) (1) to carve/to engrave/to sculpture/to chisel/(2) to tattoo/(P)
 KanaVerb_5r( めずらしがる, JAP_TRANSITIVE ) // (v5r,vt) to think (it) a curiosity
 KanaVerb_5r( おいやる, JAP_TRANSITIVE ) // (v5r,vt) (1) to drive away/to order off/to chase away/(2) to force into an unpleasant situation (bankruptcy, prostitution, suicide, etc.)
 KanaVerb_5r( つまぐる, JAP_TRANSITIVE ) // (v5r,vt) to finger/to roll between the thumb and the fingers
 KanaVerb_5r( しめくくる, JAP_TRANSITIVE ) // (v5r,vt) to bind firmly/to superintend/to bring to a finish
 KanaVerb_5r( つまみとる, JAP_TRANSITIVE ) // (v5r,vt) to pluck/to pick/to nip off
 KanaVerb_5r( つみとる, JAP_TRANSITIVE ) // (v5r,vt) to pluck/to pick/to nip off
 KanaVerb_5r( ぬりたくる, JAP_TRANSITIVE ) // (v5r,vt) to bedaub (with paint)/to besmear/to paint heavily
 KanaVerb_5r( ぬる, JAP_TRANSITIVE ) // (v5r,vt) to paint/to plaster/to lacquer/to varnish/(P)
 KanaVerb_5r( ほふる, JAP_TRANSITIVE ) // (v5r,vt) to slaughter/to massacre/to defeat/to butcher
 KanaVerb_5r( ぬすみとる, JAP_TRANSITIVE ) // (v5r,vt) to steal
 KanaVerb_5r( うちとる, JAP_TRANSITIVE ) // (v5r,vt) (1) to arrest/to take prisoner/(2) to kill/(3) to get someone out (in baseball)
 KanaVerb_5r( ふみきる, JAP_TRANSITIVE ) // (v5r,vt) to make a bold start/to take a plunge/to take off/(P)
 KanaVerb_5r( ふみやぶる, JAP_TRANSITIVE ) // (v5r,vt) to walk across/to travel on foot
 KanaVerb_5r( ふみにじる, JAP_TRANSITIVE ) // (v5r,vt) to trample underfoot/to tread on/to crush with a foot
 KanaVerb_5r( よみあやまる, JAP_TRANSITIVE ) // (v5r,vt) to misread/to mispronounce
 KanaVerb_5r( よみとる, JAP_TRANSITIVE ) // (v5r,vt) (1) to read (someone's) mind/to read between the lines/(2) to read (a calibration, a tape, etc.)
 KanaVerb_5r( よみきる, JAP_TRANSITIVE ) // (v5r,vt) to finish reading/to read through
 KanaVerb_5r( よみやぶる, JAP_TRANSITIVE ) // (v5r,vt) to read through (difficult passage or particularly long book)
 KanaVerb_5r( つきやぶる, JAP_TRANSITIVE ) // (v5r,vt) to break through/to penetrate/to pierce
 KanaVerb_5r( つっきる, JAP_TRANSITIVE ) // (v5r,vt) to cross/to go across/to go through/to cut across
 KanaVerb_5r( ひねる, JAP_TRANSITIVE ) // (v5r,vt) to turn (a switch) on or off/to twist/to puzzle over/(P)
 KanaVerb_5r( やぶる, JAP_TRANSITIVE ) // (v5r,vt) to tear/to violate/to defeat/to smash/to destroy
 KanaVerb_5r( くばる, JAP_TRANSITIVE ) // (v5r,vt) to distribute/to deliver/(P)
 KanaVerb_5r( かいあさる, JAP_TRANSITIVE ) // (v5r,vt) to spend money freely
 KanaVerb_5r( かいとる, JAP_TRANSITIVE ) // (v5r,vt) to buy/to purchase
 KanaVerb_5r( かいきる, JAP_TRANSITIVE ) // (v5r,vt) to buy up
 KanaVerb_5r( かいあおる, JAP_TRANSITIVE ) // (v5r,vt) to bid up/to corner the market
 KanaVerb_5r( かいかぶる, JAP_TRANSITIVE ) // (v5r,vt) to overestimate/to make too much of
 KanaVerb_5r( うりしぶる, JAP_TRANSITIVE ) // (v5r,vt) to be reluctant to sell
 KanaVerb_5r( うりきる, JAP_TRANSITIVE ) // (v5r,vt) to sell out/to sell off
 KanaVerb_5r( うる, JAP_TRANSITIVE ) // (v5r,vt) to sell/(P)
 KanaVerb_5r( はぎとる, JAP_TRANSITIVE ) // (v5r,vt) to tear off/to strip/to rob
 KanaVerb_5r( へずる, JAP_TRANSITIVE ) // (v5r,vt) to pilfer/to steal a portion
 KanaVerb_5r( しばる, JAP_TRANSITIVE ) // (v5r,vt) to tie/to bind/(P)
 KanaVerb_5r( ぬきとる, JAP_TRANSITIVE ) // (v5r,vt) to pull out/to draw out
 KanaVerb_5r( うるさがる, JAP_TRANSITIVE ) // (v5r,vt) to feel annoyed at
 KanaVerb_5r( かぶる, JAP_TRANSITIVE ) // (v5r,vt) (1) to wear (on head)/to put on (over head)/(2) to pour or dash water, dust, etc. (on oneself)/(3) to bear (e.g., someone's debts, faults, etc.)/(4) to overlap/(P)
 KanaVerb_5r( あなずる, JAP_TRANSITIVE ) // (v5r,vt) to despise/to disdain/to make light of
 KanaVerb_5r( あなどる, JAP_TRANSITIVE ) // (v5r,vt) to despise/to disdain/to make light of/(P)
 KanaVerb_5r( ふうじる, JAP_TRANSITIVE ) // (v5r,vt) (1) to seal (letter)/(2) to prevent/to forbid/(P)
 KanaVerb_5r( ものがたる, JAP_TRANSITIVE ) // (v5r,vt) to tell/to indicate/(P)
 KanaVerb_5r( ぶんどる, JAP_TRANSITIVE ) // (v5r,vt) to capture/to seize/to plunder
 KanaVerb_5r( ききとる, JAP_TRANSITIVE ) // (v5r,vt) to catch (a person's words)/to follow/to understand/(P)
 KanaVerb_5r( ききかじる, JAP_TRANSITIVE ) // (v5r,vt) to have a smattering knowledge of
 KanaVerb_5r( しめきる, JAP_TRANSITIVE ) // (v5r,vt) to close up/to shut up (e.g., behind doors)/to cut off (e.g., because a deadline has expired)
 KanaVerb_5r( たてまつる, JAP_TRANSITIVE ) // (v5r,vt) to offer/to present/to revere/to do respectfully
 KanaVerb_5r( わすれさる, JAP_TRANSITIVE ) // (v5r,vt) to forget completely/to leave behind
 KanaVerb_5r( たばかる, JAP_TRANSITIVE ) // (v5r,vt) to plot/to attempt/to plan/to take in/to deceive/to devise/to design/to refer A to B
 KanaVerb_5r( ほおばる, JAP_TRANSITIVE ) // (v5r,vt) to stuff one's cheeks
 KanaVerb_5r( さする, JAP_TRANSITIVE ) // (v5r,vt) (1) to pat/to stroke/(2) to rub off/to polish/to grind/to graze/to scrape/(3) to be equal to/(4) to be about to reach/(P)
 KanaVerb_5r( こうむる, JAP_TRANSITIVE ) // (v5r,vt) to suffer/to receive/to sustain
 KanaVerb_5r( やじる, JAP_TRANSITIVE ) // (v5r,vt) to jeer (at)/to hoot/to boo/to catcall/to heckle
 KanaVerb_5r( ほめちぎる, JAP_TRANSITIVE ) // (v5r,vt) to praise (to the skies)/to sing the praises (of)/to extol
 KanaVerb_5r( あずかる, JAP_TRANSITIVE ) // (v5r,vt) to keep in custody/to receive on deposit/to take charge of/(P)
 KanaVerb_5r( ゆる, JAP_TRANSITIVE ) // (v5r,vt) to shake/to jolt/to rock (cradle)/to swing/(P)
 KanaVerb_5r( ほしがる, JAP_TRANSITIVE ) // (v5r,vt) to desire/to want/to wish for/to covet/(P)
 KanaVerb_5r( たのみいる, JAP_TRANSITIVE ) // (v5r,vt) to entreat/to request earnestly
 KanaVerb_5r( うらぎる, JAP_TRANSITIVE ) // (v5r,vt) to betray/to turn traitor to/to double-cross/(P)
 KanaVerb_5r( たてきる, JAP_TRANSITIVE ) // (v5r,vt) to close tight
 KanaVerb_5r( かすめとる, JAP_TRANSITIVE ) // (v5r,vt) to snatch/to steal
 KanaVerb_5r( おもんぱかる, JAP_TRANSITIVE ) // (v5r,vt) to consider
 KanaVerb_5r( はかる, JAP_TRANSITIVE ) // (v5r,vt) to measure/to weigh/to survey/to time (sound, gauge, estimate)/(P)
 KanaVerb_5r( いじくる, JAP_TRANSITIVE ) // (v5r,vt) to finger/to tamper (with)
 KanaVerb_5r( いじる, JAP_TRANSITIVE ) // (v5r,vt) (1) to touch/to tamper with/(P)
 KanaVerb_5r( まさぐる, JAP_TRANSITIVE ) // (v5r,vt) (1) to touch/to tamper with/(v5r,vt) (2) to grope about/to feel for something
 KanaVerb_5r( はさみきる, JAP_TRANSITIVE ) // (v5r,vt) to nip off/to snip/to clip/to trim off
 KanaVerb_5r( あおる, JAP_TRANSITIVE ) // (v5r,vt) to gulp down (a drink)/to slurp
 KanaVerb_5r( すする, JAP_TRANSITIVE ) // (v5r,vt) (uk) to sip/to slurp
 KanaVerb_5r( あざける, JAP_TRANSITIVE ) // (v5r,vt) (uk) to scoff/(P)
 KanaVerb_5r( めとる, JAP_TRANSITIVE ) // (v5r,vt) to marry (a woman) to take to wife
 KanaVerb_5r( なぶる, JAP_TRANSITIVE ) // (v5r,vt) to tease/to make sport of/to make fun of
 KanaVerb_5r( たちきる, JAP_TRANSITIVE ) // (v5r,vt) to sever/to break off/to cut asunder/to cut off/to block/to disconnect
 KanaVerb_5r( えぐる, JAP_TRANSITIVE ) // (v5r,vt) to gouge/to hollow out/to bore/to excavate/to scoop out
 KanaVerb_5r( つねる, JAP_TRANSITIVE ) // (v5r,vt) to pinch
 KanaVerb_5r( ひねくる, JAP_TRANSITIVE ) // (v5r,vt) to twirl/to spin/to fiddle with/to change wording
 KanaVerb_5r( ほうる, JAP_TRANSITIVE ) // (v5r,vt) (1) to let go/to abandon/to leave undone/(2) to throw/to toss/to fling
 KanaVerb_5r( ねじる, JAP_TRANSITIVE ) // (v5r,vt) (1) to screw/to twist/(2) to distort/(3) to torture/to wrest/(P)
 KanaVerb_5r( ねじとる, JAP_TRANSITIVE ) // (v5r,vt) to wring off/to wrest from
 KanaVerb_5r( ねじきる, JAP_TRANSITIVE ) // (v5r,vt) to twist off
 KanaVerb_5r( もじる, JAP_TRANSITIVE ) // (v5r,vt) to parody/to wrench/to twist
 KanaVerb_5r( よじる, JAP_TRANSITIVE ) // (v5r,vt) to twist
 KanaVerb_5r( からめとる, JAP_TRANSITIVE ) // (v5r,vt) to arrest
 KanaVerb_5r( くすぐる, JAP_TRANSITIVE ) // (v5r,vt) (uk) to tickle/(P)
 KanaVerb_5r( くしけずる, JAP_TRANSITIVE ) // (v5r,vt) to comb)
 KanaVerb_5r( けずる, JAP_TRANSITIVE ) // (v5r,vt) (1) to shave (wood or leather)/to sharpen/to plane/to whittle/to pare/to scrape off/(2) to cross out/to reduce/to curtail/to remove/to erase
 KanaVerb_5r( むしりとる, JAP_TRANSITIVE ) // (v5r,vt) to tear off/to pluck off
 KanaVerb_5r( むしる, JAP_TRANSITIVE ) // (v5r,vt) to pluck/to pick/to tear
 KanaVerb_5r( あぶる, JAP_TRANSITIVE ) // (v5r,vt) (uk) to scorch/to broil/to toast
// KanaVerb_5r( いる, JAP_TRANSITIVE ) // (v5r,vt) to parch/to fry/to fire/to broil/to roast/to boil down (in oil)
 KanaVerb_5r( つぶる, JAP_TRANSITIVE ) // (v5r,vt) to close the eyes/(P)
 KanaVerb_5r( つむる, JAP_TRANSITIVE ) // (v5r,vt) to close the eyes/(P)
 KanaVerb_5r( まつる, JAP_TRANSITIVE ) // (v5r,vt) to deify/to enshrine
 KanaVerb_5r( よる, JAP_TRANSITIVE ) // (v5r,vt) to twist (yarn)/to lay (rope)
 KanaVerb_5r( かがる, JAP_TRANSITIVE ) // (v5r,vt) to cross-stitch/to hemstitch/to sew (up)/to darn
 KanaVerb_5r( ねぶる, JAP_TRANSITIVE ) // (v5r,vt) to lick
 KanaVerb_5r( そしる, JAP_TRANSITIVE ) // (v5r,vt) to slander/to libel/to criticize/to criticise
 KanaVerb_5r( むさぼる, JAP_TRANSITIVE ) // (v5r,vt) (uk) to covet/to indulge in/to deeply desire/to lust insatiably for/(P)
 KanaVerb_5r( かたる, JAP_TRANSITIVE ) // (v5r,vt) to swindle/to deceive/to cheat
 KanaVerb_5r( かじる, JAP_TRANSITIVE ) // (v5r,vt) to chew/to bite (at)/to gnaw/to nibble/to munch/to crunch/to have a smattering of
 KanaVerb_5r( おたかくとまる ) // (v5r) to assume an air of importance/to be self-important/to put on airs
 KanaVerb_5r( おばはる ) // (v5r) (sl) to shamelessly demand one's rights
 KanaVerb_5r( かさかさなる ) // (v5r) to rustle/to make a rustling sound/to crinkle
 KanaVerb_5r( かんかんおこる ) // (v5r) to get very mad
 KanaVerb_5r( くすくすわらう ) // (v5r) to giggle
 KanaVerb_5r( くたばる ) // (v5r,vi) (col) to die/to be exhausted/(P)
 KanaVerb_5r( くっちゃべる ) // (v5r) to talk/to chatter/to tell (e.g., secrets)
 KanaVerb_5r( くねる ) // (v5r,vi) to bend loosely back and forth
 KanaVerb_5r( こだわる ) // (v5r,vi) to fuss over/to be particular about/to be concerned about/(P)
 KanaVerb_5r( しくじる ) // (v5r,vi) to fail/to fall through/to blunder/(P)
 KanaVerb_5r( じろりとみる ) // (v5r) to throw a glance
 KanaVerb_5r( ちんちんなる ) // (v5r) to jingle/to tinkle
 KanaVerb_5r( つかみとる ) // (v5r) to grasp/to get
 KanaVerb_5r( つんのめる ) // (v5r,vi) to pitch (fall) forward
 KanaVerb_5r( である ) // (v5r) to be (formal, literary)
 KanaVerb_5r( でんぐりがえる ) // (v5r,vi) to turn a somersault/to turn over (topsy-turvy)/to turn head over heels
 KanaVerb_5r( ぬたくる ) // (v5r,vi) to scrawl/to daub
 KanaVerb_5r( のたうちまわる ) // (v5r,vi) to writhe
 KanaVerb_5r( のたくる ) // (v5r,vi) to wriggle/to writhe/to squirm
 KanaVerb_5r( ぴかぴかひかる ) // (v5r) to sparkle/to glitter/to twinkle
 KanaVerb_5r( ぶらさがる ) // (v5r,vi) to hang from/to dangle/to swing/(P)
 KanaVerb_5r( ぷりぷりおこる ) // (v5r) to be in a huff
 KanaVerb_5r( へたばる ) // (v5r,vi) to be exhausted/to be worn out
 KanaVerb_5r( へばる ) // (v5r,vi) to be exhausted/to be worn out
 KanaVerb_5r( ぼったくる ) // (v5r) to rip someone off
 KanaVerb_5r( やりきる ) // (v5r) (uk) complete decisively/to do to completion
 KanaVerb_5r( イレブる ) // (v5r) to go to a Seven-Eleven
 KanaVerb_5r( キョドる ) // (v5r) to act suspiciously
 KanaVerb_5r( サボる ) // (v5r,vi) to be truant/to be idle/to sabotage by slowness/(P)
 KanaVerb_5r( シクる ) // (v5r) (sl) to fail/to stuff up
 KanaVerb_5r( ダブる ) // (v5r,vi) to coincide (fall on the same day)/to have two of something/to repeat a school year after failing
 KanaVerb_5r( チェキる ) // (v5r) to take a picture with a cheki camera
 KanaVerb_5r( チクる ) // (v5r) (sl) to tattle/to inform a superior of someone's actions
 KanaVerb_5r( テロる ) // (v5r) to commit acts of terrorism
 KanaVerb_5r( テンパる ) // (v5r) to be about to blow one's fuse
 KanaVerb_5r( デニる ) // (v5r) to eat at Denny's
 KanaVerb_5r( デモる ) // (v5r,vi) to demonstrate (e.g., in the streets)
 KanaVerb_5r( トラブる ) // (v5r,vi) to make trouble
 KanaVerb_5r( ドタバタやる ) // (v5r) to be noisy/to make noise
 KanaVerb_5r( ハモる ) // (v5r) to harmonize/to harmonise/to be in harmony
 KanaVerb_5r( ポシャる ) // (v5r,vi) to break down/to fail
 KanaVerb_5r( ヤニる ) // (v5r) to smoke (cigarettes, tobacco)
 KanaVerb_5r( ラリる ) // (v5r) (sl) to become intoxicated (e.g., with drugs)
 KanaVerb_5r( レズる ) // (v5r) to engage in lesbian sexual activity
 KanaVerb_5r( ろむる ) // (v5r) to read a forum/to chat without posting a message/to lurk (from Read-Only Member)
 KanaVerb_5r( おもねる ) // (v5r,vi) to flatter
 KanaVerb_5r( やすくゆずる ) // (v5r) to sell (a thing) cheap
 KanaVerb_5r( くらいどる ) // (v5r) to scale
 KanaVerb_5r( えらがる ) // (v5r,vi) to be conceited
 KanaVerb_5r( いばりくさる ) // (v5r) to throw one's weight around/to be puffed up
 KanaVerb_5r( いばる ) // (v5r,vi) to be proud/to swagger/(P)
 KanaVerb_5r( なしおわる ) // (v5r,vi) to finish
 KanaVerb_5r( かしこまる ) // (v5r,vi) to obey respectfully/to humble oneself/to sit straight (upright, respectfully, attentively)
 KanaVerb_5r( ことなる ) // (v5r,vi) to differ/to vary/to disagree/(P)
 KanaVerb_5r( うつりかわる ) // (v5r) to change
 KanaVerb_5r( いちじけずる ) // (v5r) to delete a letter
 KanaVerb_5r( いっぷくもる ) // (v5r) to poison
 KanaVerb_5r( いっぽさがる ) // (v5r) to take a step backward
 KanaVerb_5r( いっぽんとる ) // (v5r) to beat/to gain a point/to upset
 KanaVerb_5r( いちみゃくあいつうじる ) // (v5r) to have in common (with)
 KanaVerb_5r( いちみゃくあいつうずる ) // (v5r) to have in common (with)
 KanaVerb_5r( はぐる ) // (v5r,vi) (uk) to stray from/to get lost
 KanaVerb_5r( ひきしまる ) // (v5r,vi) to become tense/to be tightened/(P)
 KanaVerb_5r( ひっかかる ) // (v5r,vi) to be caught in/to be stuck in/to be cheated/(P)
 KanaVerb_5r( ひっくりかえる ) // (v5r,vi) to be overturned/to be upset/to topple over/to be reversed/(P)
 KanaVerb_5r( ひきさがる ) // (v5r,vi) to withdraw/to leave
 KanaVerb_5r( ひきつる ) // (v5r) to have a cramp (spasm, convulsion, twitch)/to become stiff
 KanaVerb_5r( ひきこもる ) // (v5r,vi) to stay (confined) indoors
 KanaVerb_5r( うかがいさぐる ) // (v5r) to spy out
 KanaVerb_5r( はこびさる ) // (v5r) to carry away
 KanaVerb_5r( えつにいる ) // (v5r) to be pleased/to gloat/to glow with self-satisfaction
 KanaVerb_5r( けむたがる ) // (v5r,vi) to be sensitive to smoke
 KanaVerb_5r( とおざかる ) // (v5r,vi) to go far off/(P)
 KanaVerb_5r( くぼまる ) // (v5r,vi) to be low (as a hollow)
 KanaVerb_5r( おくまる ) // (v5r,vi) to lie deep in/to extend far back
 KanaVerb_5r( おしつまる ) // (v5r) to approach the year end/to be jammed tight
 KanaVerb_5r( おしまくる ) // (v5r) to push and push/to keep pushing to the end
 KanaVerb_5r( おしとおる ) // (v5r) to force one's way through
 KanaVerb_5r( おしわたる ) // (v5r) to cross over/to wade
 KanaVerb_5r( おしいる ) // (v5r) to push in
 KanaVerb_5r( おしせまる ) // (v5r,vi) to draw near
 KanaVerb_5r( おしだまる ) // (v5r,vi) to keep silent
 KanaVerb_5r( よこたわる ) // (v5r,vi) to lie down/to stretch out/(P)
 KanaVerb_5r( なぐられてのびる ) // (v5r) to be knocked out cold
 KanaVerb_5r( おんがある ) // (v5r) to be in one's debt
 KanaVerb_5r( ぬくまる ) // (v5r,vi) to warm oneself/to sun oneself/to warm up/to get warm
 KanaVerb_5r( ぬくもる ) // (v5r,vi) to get warm/to become warm
 KanaVerb_5r( しもがかる ) // (v5r,vi) to talk about indecent things
 KanaVerb_5r( げすばる ) // (v5r) to be churlish/to be vulgar
 KanaVerb_5r( くわわる ) // (v5r,vi) to join in/to accede to/to increase/to gain in (influence)/(P)
 KanaVerb_5r( かわいがる ) // (v5r) to love/to be affectionate/(P)
 KanaVerb_5r( おかしがる ) // (v5r) to be amused (by, at)/to wonder at
 KanaVerb_5r( ひまどる ) // (v5r) to take time
 KanaVerb_5r( うたいまくる ) // (v5r) to sing energetically/to sing with abandon
 KanaVerb_5r( ほてる ) // (v5r,vi) to feel hot/to flush/to burn
 KanaVerb_5r( かせぎとる ) // (v5r) to earn by working
 KanaVerb_5r( すぎさる ) // (v5r,vi) to pass/to pass away
 KanaVerb_5r( まわる ) // (v5r,vi) (1) to turn/to revolve/(2) to visit several places
 KanaVerb_5r( もとおる ) // (v5r,vi) to wander around
 KanaVerb_5r( ひらきなおる ) // (v5r,vi) to become defiant/to turn upon/to become serious/(P)
 KanaVerb_5r( かくしきばる ) // (v5r,vi) to adhere to formalities
 KanaVerb_5r( かどばる ) // (v5r,vi) to be angular/to be overly ceremonious
 KanaVerb_5r( あらたまる ) // (v5r,vi) (1) to be renewed/(2) to stand on ceremony/to be formal/(3) to take a turn for the worse
 KanaVerb_5r( がくがある ) // (v5r) to have learning/to be educated
 KanaVerb_5r( まなびとる ) // (v5r) to collect information/to gather knowledge
 KanaVerb_5r( わってはいる ) // (v5r) to force one's way through
 KanaVerb_5r( われかえる ) // (v5r,vi) to break completely/to (figuratively) bring the house down
 KanaVerb_5r( わりきる ) // (v5r) to divide/to give a clear explanation
 KanaVerb_5r( すべりよる ) // (v5r,vi) to slide up to
 KanaVerb_5r( すべりいる ) // (v5r,vi) to slide into
 KanaVerb_5r( ぬめる ) // (v5r,vi) to be slippery/to be slimy/to behave charmingly/to walk merrily
 KanaVerb_5r( ひかたまる ) // (v5r) to dry and harden
 KanaVerb_5r( さむがる ) // (v5r,vi) to be bothered by coldness/to complain about the cold
 KanaVerb_5r( まきあがる ) // (v5r,vi) to roll up/to be rolled up
 KanaVerb_5r( ひあがる ) // (v5r,vi) to dry up/to parch/to ebb away
 KanaVerb_5r( かんじいる ) // (v5r,vi) to be impressed/to greatly admire
 KanaVerb_5r( かんきわまる ) // (v5r) to be overcome with emotion
 KanaVerb_5r( あまやかしてそだてる ) // (v5r) to bring up indulgently
 KanaVerb_5r( まぎる ) // (v5r,vi) to plow through (a wave) (plough)/to tack (against the wind)
 KanaVerb_5r( まるまる ) // (v5r,vi) to become rounded/to roll into a ball/(P)
 KanaVerb_5r( がんばる ) // (v5r,vi) to persist/to insist on/to stand firm/to try one's best/(P)
 KanaVerb_5r( あぶながる ) // (v5r,vi) to be afraid of/to feel uneasy about/to shrink from
 KanaVerb_5r( きとくである ) // (v5r) to be in critical condition/to be dangerously ill
 KanaVerb_5r( よがる ) // (v5r) to satisfy oneself/to feel satisfied/to be proud
 KanaVerb_5r( うれしがる ) // (v5r) to be glad
 KanaVerb_5r( よっかかる ) // (v5r) to lean against/to recline on
 KanaVerb_5r( よりあつまる ) // (v5r,vi) to gather together/(P)
 KanaVerb_5r( よりすがる ) // (v5r,vi) to cling to/to rely on
 KanaVerb_5r( きにかかる ) // (v5r,vi) to weigh on one's mind/to be worried about (something)
 KanaVerb_5r( きにいる ) // (v5r) to be pleased with/to suit/(P)
 KanaVerb_5r( きばる ) // (v5r) to strain or exert oneself/to go all out
 KanaVerb_5r( いのる ) // (v5r,vi) to pray/to wish/(P)
 KanaVerb_5r( きそくでしばる ) // (v5r) to restrict (a person) by rule
 KanaVerb_5r( おきあがる ) // (v5r,vi) to rise/to erect/to get up/(P)
 KanaVerb_5r( おきなおる ) // (v5r,vi) to sit up
 KanaVerb_5r( かがやきわたる ) // (v5r,vi) to shine out far and wide
 KanaVerb_5r( いつわりかたる ) // (v5r) to speak falsely
 KanaVerb_5r( いつわる ) // (v5r,vi) to lie/to cheat/to falsify/to deceive/to pretend/(P)
 KanaVerb_5r( ぎしきばる ) // (v5r,vi) to formalize/to formalise/to stick to formality/to be ceremonious/to punctilious
 KanaVerb_5r( よろしくやる ) // (v5r) to make cozy with (cosy)/to do at one's own discretion
 KanaVerb_5r( たわむる ) // (v5r,vi) (arch) to be playful/to gambol/to be amused (with something)/to play/to sport/to frolic/to joke
 KanaVerb_5r( すくいとる ) // (v5r) to dip or scoop up/to ladle out
 KanaVerb_5r( つまる ) // (v5r,vi) (1) to be blocked/to be packed/(2) to hit the ball near the handle of the bat (baseball)/(P)
 KanaVerb_5r( つめよる ) // (v5r,vi) to draw near/to draw closer
 KanaVerb_5r( つめきる ) // (v5r) to be or remain always on hand
 KanaVerb_5r( のぼせあがる ) // (v5r,vi) to be beside oneself/to lose one's head/to go mad with something
 KanaVerb_5r( やすまる ) // (v5r,vi) to be rested/to feel at ease/to repose/to be relieved/(P)
 KanaVerb_5r( なきじゃくる ) // (v5r) to sob
 KanaVerb_5r( なきすがる ) // (v5r) to cling tearfully to another person
 KanaVerb_5r( さる ) // (v5r,vi) (1) to leave/to go away/(2) to pass/to elapse/(3) to be distant/(P)
 KanaVerb_5r( いのこる ) // (v5r,vi) to stay behind/to remain/to work overtime
 KanaVerb_5r( いすわる ) // (v5r,vi) to remain
 KanaVerb_5r( いなおる ) // (v5r,vi) (1) to sit up properly straight/(2) to become aggressive
 KanaVerb_5r( こぞる ) // (v5r) (1) to assemble everything together/(2) to do something as a group
 KanaVerb_5r( へだたる ) // (v5r,vi) to be distant
 KanaVerb_5r( つよがる ) // (v5r,vi) to cry sour grapes/to bluff/to whistle in the dark
 KanaVerb_5r( つよまる ) // (v5r,vi) to get strong/to gain strength/(P)
 KanaVerb_5r( こわばる ) // (v5r,vi) to stiffen/(P)
 KanaVerb_5r( おそれいる ) // (v5r,vi) to be filled with awe/to feel small/to be amazed/to be surprised/to be disconcerted/to be sorry/to be grateful/to be defeated/to confess guilt
 KanaVerb_5r( はさまる ) // (v5r,vi) to get between/to be caught in/(P)
 KanaVerb_5r( くるいまわる ) // (v5r) to rave/to run amuck
 KanaVerb_5r( せばまる ) // (v5r,vi) to narrow/to contract/(P)
 KanaVerb_5r( きょうがる ) // (v5r,vi) to be amused or interested in
 KanaVerb_5r( ひびきわたる ) // (v5r,vi) to resound
 KanaVerb_5r( おどろきいる ) // (v5r,vi) to be astonished/to be amazed
 KanaVerb_5r( のけぞる ) // (v5r,vi) to bend back/to throw (the head) back
 KanaVerb_5r( あおぎたてまつる ) // (v5r) (pol) to look up
 KanaVerb_5r( こりかたまる ) // (v5r,vi) to coagulate/to curdle/to clot/to be fanatical
 KanaVerb_5r( こごる ) // (v5r,vi) to congeal/to freeze
 KanaVerb_5r( こる ) // (v5r,vi) (1) to grow stiff/(2) to be absorbed in/to be devoted to/to be a fanatic/to elaborate/(P)
 KanaVerb_5r( まがる ) // (v5r,vi) to turn/to bend/(P)
 KanaVerb_5r( まがりくねる ) // (v5r,vi) to bend many times/to turn and twist/to zigzag
 KanaVerb_5r( きわまる ) // (v5r,vi) to terminate/to reach an extreme/to be in a dilemma/to be at an end/(P)
 KanaVerb_5r( すじばる ) // (v5r,vi) to become sinewy/to behave formally
 KanaVerb_5r( ちかよる ) // (v5r,vi) to approach/to draw near/(P)
 KanaVerb_5r( きゅうしゅうへくだる ) // (v5r) to go down to Kyushu
 KanaVerb_5r( くるしがる ) // (v5r) to suffer/to complain of a pain
 KanaVerb_5r( にがりきる ) // (v5r,vi) to look sour (disgusted)
 KanaVerb_5r( にがる ) // (v5r,vi) to feel bitter/to scowl
 KanaVerb_5r( にがてである ) // (v5r) to be weak in/to be poor at/to be bad at
 KanaVerb_5r( かけずりまわる ) // (v5r,vi) to run around/to bustle about/to busy oneself
 KanaVerb_5r( かけくだる ) // (v5r) to run down
 KanaVerb_5r( かけまわる ) // (v5r,vi) to run around/to bustle about
 KanaVerb_5r( かけよる ) // (v5r,vi) to rush over/to run up to
 KanaVerb_5r( かけめぐる ) // (v5r,vi) to run about
 KanaVerb_5r( かけあがる ) // (v5r,vi) to run up
 KanaVerb_5r( かけのぼる ) // (v5r) to run (uphill)
 KanaVerb_5r( ぐずる ) // (v5r) to grumble/to be unsettled/to pick a quarrel
 KanaVerb_5r( ぐちる ) // (v5r,vi) to complain/to grumble
 KanaVerb_5r( むなしくなる ) // (v5r) to die/to expire
 KanaVerb_5r( くりさがる ) // (v5r) to move back/to postpone/to borrow (in math)
 KanaVerb_5r( くりとる ) // (v5r) to reel off
 KanaVerb_5r( くりあがる ) // (v5r,vi) to move up (date or rank)
 KanaVerb_5r( むらがる ) // (v5r,vi) to swarm/to gather/(P)
 KanaVerb_5r( むれあつまる ) // (v5r) to gather in large groups
 KanaVerb_5r( けいしきばる ) // (v5r,vi) to stand on ceremony
 KanaVerb_5r( かたちづくる ) // (v5r,vi) to form/to shape/to make/to mold/to mould/to build up
 KanaVerb_5r( たずさわる ) // (v5r,vi) to participate/to take part/(P)
 KanaVerb_5r( へめぐる ) // (v5r) to travel about
 KanaVerb_5r( へあがる ) // (v5r,vi) to rise
 KanaVerb_5r( つながる ) // (v5r,vi) to be tied together/to be connected to/to be related to/(P)
 KanaVerb_5r( きまる ) // (v5r,vi) (1) to be decided/to be settled/(2) to look good in (clothes)/(P)
 KanaVerb_5r( ちばしる ) // (v5r,vi) bloodshot
 KanaVerb_5r( ちぬる ) // (v5r,vi) to smear with blood/to kill
 KanaVerb_5r( かけへだたる ) // (v5r,vi) far apart/remote/quite different
 KanaVerb_5r( けんえんのなかである ) // (v5r) to be at enmity/to lead a cat and dog life
 KanaVerb_5r( かたひじはる ) // (v5r) to swagger/to stiffen
 KanaVerb_5r( みまわる ) // (v5r,vi) to make one's rounds/to patrol
 KanaVerb_5r( けんしきばる ) // (v5r,vi) to assume an air of importance/to stand on one's dignity
 KanaVerb_5r( みすててさる ) // (v5r) to leave behind
 KanaVerb_5r( みつもる ) // (v5r) to estimate
 KanaVerb_5r( みあたる ) // (v5r) to be found/(P)
 KanaVerb_5r( みつかる ) // (v5r,vi) (uk) to be found/to be discovered/(P)
 KanaVerb_5r( みかえる ) // (v5r,vi) to look back
 KanaVerb_5r( げんじる ) // (v5r,vi) to subtract/to deduct/to reduce/to decrease
 KanaVerb_5r( へる ) // (v5r,vi) to decrease (in size or number)/to diminish/to abate/(P)
 KanaVerb_5r( いいよる ) // (v5r,vi) to court/to woo/to approach defiantly
 KanaVerb_5r( いいおわる ) // (v5r) to finish speaking
 KanaVerb_5r( いいつのる ) // (v5r,vi) to argue vehemently
 KanaVerb_5r( ことばからじっこうにうつる ) // (v5r) to change words into actions
 KanaVerb_5r( かぎる ) // (v5r,vi) to restrict/to limit/to confine/(P)
 KanaVerb_5r( よびにやる ) // (v5r) to send for (doctor, etc.)
 KanaVerb_5r( かたくなる ) // (v5r) to become stiff/to tense
 KanaVerb_5r( かたくかたまる ) // (v5r) to form a hard mass
 KanaVerb_5r( かたまる ) // (v5r,vi) to harden/to solidify/to become firm/to become certain/(P)
 KanaVerb_5r( ほこる ) // (v5r,vi) to boast of/to be proud of/(P)
 KanaVerb_5r( またがる ) // (v5r,vi) (1) to extend over or into/(2) to straddle
 KanaVerb_5r( くれてやる ) // (v5r) (uk) to give/to do (something) for
 KanaVerb_5r( あとじさる ) // (v5r) to retreat/to back off
 KanaVerb_5r( あとずさる ) // (v5r) to retreat/to back off
 KanaVerb_5r( おいでになる ) // (v5r) (hon) (uk) to be
 KanaVerb_5r( ごめんこうむる ) // (v5r) to be excused from
 KanaVerb_5r( こいとる ) // (v5r) to ask for and receive
 KanaVerb_5r( まじわる ) // (v5r,vi) to cross/to intersect/to associate with/to mingle with/to interest/to join/(P)
 KanaVerb_5r( ひかる ) // (v5r,vi) to shine/to glitter/to be bright/(P)
 KanaVerb_5r( くちごもる ) // (v5r,vi) to hesitate to say/to mumble/to hem and haw/to falter
 KanaVerb_5r( むきなおる ) // (v5r,vi) to turn round/to face about/to turn about
 KanaVerb_5r( むけなおる ) // (v5r,vi) to change direction
 KanaVerb_5r( あかじみる ) // (v5r,vi) to become grimy or dirty
 KanaVerb_5r( こうじんである ) // (v5r) to deem a favor/to deem a favour/to be very glad
 KanaVerb_5r( ひろがる ) // (v5r,vi) to spread (out)/to extend/to stretch/to reach to/to get around/(P)
 KanaVerb_5r( ひろまる ) // (v5r,vi) to spread/to be propagated/(P)
 KanaVerb_5r( かかわる ) // (v5r,vi) to concern oneself in/to have to do with/to affect/to influence/to stick to (opinions)
 KanaVerb_5r( せめのぼる ) // (v5r,vi) to march on the capital
 KanaVerb_5r( せめいる ) // (v5r,vi) to invade
 KanaVerb_5r( えがわる ) // (v5r) to (try to) act like a big-shot
 KanaVerb_5r( かんばしる ) // (v5r,vi) to make a shrill sound
 KanaVerb_5r( かんがえすぎる ) // (v5r) to think too much/to be over-concerned
 KanaVerb_5r( あらしまわる ) // (v5r) to break into (houses here and there)/to rampage
 KanaVerb_5r( いきあたる ) // (v5r) to hit/to run into/to light on/to strike into/to come against/to deadlock
 KanaVerb_5r( ゆきあたる ) // (v5r) to hit/to run into/to light on/to strike into/to come against/to deadlock
 KanaVerb_5r( いきわたる ) // (v5r,vi) to diffuse/to spread through/(P)
 KanaVerb_5r( ゆきわたる ) // (v5r,vi) to diffuse/to spread through
 KanaVerb_5r( ふりしきる ) // (v5r) to rain incessantly/to downpour
 KanaVerb_5r( ふりつもる ) // (v5r) to lie thick
 KanaVerb_5r( ふりつのる ) // (v5r,vi) to rain harder
 KanaVerb_5r( くだる ) // (v5r,vi) to get down/to descend
 KanaVerb_5r( かおる ) // (v5r,vi) to smell sweet/to be fragrant/(P)
 KanaVerb_5r( たかぶる ) // (v5r,vi) to be highly strung/to get excited/to be proud/to be haughty
 KanaVerb_5r( たかまる ) // (v5r,vi) to rise/to swell/to be promoted/(P)
 KanaVerb_5r( たかなる ) // (v5r,vi) to throb/to beat fast
 KanaVerb_5r( くろくそまる ) // (v5r) to be dyed black
 KanaVerb_5r( くろまる ) // (v5r,vi) to blacken/to become black
 KanaVerb_5r( ほねおる ) // (v5r,vi) to exert oneself greatly/to take pains
 KanaVerb_5r( ほねばる ) // (v5r,vi) to be bony/to be angular
 KanaVerb_5r( こみいる ) // (v5r,vi) to push in/to be crowded/to be complicated
 KanaVerb_5r( こまりきる ) // (v5r,vi) to be greatly perplexed/to be greatly embarrassed
 KanaVerb_5r( こまる ) // (v5r,vi) to be worried/to be bothered/(P)
 KanaVerb_5r( そそる ) // (v5r) (uk) to excite/to incite/to stimulate/to arouse/to tempt/to stir up
 KanaVerb_5r( ひだりにまがる ) // (v5r) to turn to the left
 KanaVerb_5r( さしかかる ) // (v5r) to come near to/to approach/(P)
 KanaVerb_5r( さしさわる ) // (v5r,vi) to hinder/to adversely affect
 KanaVerb_5r( さしあたる ) // (v5r,vi) to face the situation
 KanaVerb_5r( さしせまる ) // (v5r,vi) to be urgent or pressing
 KanaVerb_5r( ふたたびとる ) // (v5r) to reassume
 KanaVerb_5r( ふさがる ) // (v5r,vi) to be plugged up/to be shut up/(P)
 KanaVerb_5r( さいばしる ) // (v5r,vi) to be clever/to be quick-witted/to be precocious
 KanaVerb_5r( わざわいする ) // (v5r,vi) to be the ruin of (a person)
 KanaVerb_5r( くだけちる ) // (v5r) to be smashed up
 KanaVerb_5r( ほそる ) // (v5r,vi) to get thin/to taper off/(P)
 KanaVerb_5r( さえわたる ) // (v5r,vi) to get cold/to freeze over
 KanaVerb_5r( さえかえる ) // (v5r,vi) to be very clear/to be keenly cold
 KanaVerb_5r( さきほこる ) // (v5r,vi) to be in fullness of bloom
 KanaVerb_5r( さきのこる ) // (v5r,vi) to bloom late/to remain in bloom
 KanaVerb_5r( さきわたる ) // (v5r,vi) to bloom over a wide area
 KanaVerb_5r( けずりとる ) // (v5r) to shave off/to scrape off
 KanaVerb_5r( すぼまる ) // (v5r,vi) to get narrower/to contract
 KanaVerb_5r( すりあがる ) // (v5r) to be off the press
 KanaVerb_5r( こする ) // (v5r) to rub/to scrub/(P)
 KanaVerb_5r( すれてうすくなる ) // (v5r) to wear thin
 KanaVerb_5r( やる ) // (v5r) to do someone in/to bump someone off
 KanaVerb_5r( まじる ) // (v5r,vi) to be mixed/to be blended with/to associate with/to mingle with/to interest/to join
 KanaVerb_5r( まいる ) // (v5r) (1) (hum) to go/to come/to call/(2) to be defeated/to collapse/to die/(3) to be annoyed/to be nonplussed/(4) to be madly in love/(5) to visit (shrine, grave)/(P)
 KanaVerb_5r( ちらかる ) // (v5r,vi) to be in disorder/to lie scattered around/(P)
 KanaVerb_5r( ちらばる ) // (v5r,vi) to be scattered about/(P)
 KanaVerb_5r( ちりのこる ) // (v5r,vi) to be left blooming/to remain on the stem
 KanaVerb_5r( ちる ) // (v5r,vi) to fall/to scatter (e.g., blossoms)/(P)
 KanaVerb_5r( のこる ) // (v5r,vi) to remain/to be left/(P)
 KanaVerb_5r( ざんねんである ) // (v5r) to be sorry/to regret
 KanaVerb_5r( つかえまつる ) // (v5r) (pol) to serve/to build as commanded
 KanaVerb_5r( つかまつる ) // (v5r,vi) (pol) to serve/to do
 KanaVerb_5r( しあがる ) // (v5r,vi) to be finished
 KanaVerb_5r( ささる ) // (v5r,vi) to stick/to be stuck/(P)
 KanaVerb_5r( しかくばる ) // (v5r,vi) to be angular/to be formal
 KanaVerb_5r( はじまる ) // (v5r,vi) to begin/(P)
 KanaVerb_5r( おもいよる ) // (v5r,vi) to recall
 KanaVerb_5r( おもいやる ) // (v5r) to be considerate/to sympathize with/to sympathise with
 KanaVerb_5r( おもいいたる ) // (v5r,vi) to realize/to realise
 KanaVerb_5r( おもいあがる ) // (v5r,vi) to be conceited/(P)
 KanaVerb_5r( おもいきる ) // (v5r,vi) to resign to fate/to despair/(P)
 KanaVerb_5r( おもいあたる ) // (v5r,vi) to come to mind/to recall/to think of
 KanaVerb_5r( おもいいる ) // (v5r) to ponder/to contemplate
 KanaVerb_5r( おもいあまる ) // (v5r,vi) to not know how to act or what to do/to be at a loss
 KanaVerb_5r( うまがる ) // (v5r) to relish/to show a liking for
 KanaVerb_5r( しにかかる ) // (v5r) to be dying
 KanaVerb_5r( やにさがる ) // (v5r,vi) to be complacent/to look self-satisfied
 KanaVerb_5r( ことたる ) // (v5r,vi) to suffice/to serve the purpose/to be satisfied
 KanaVerb_5r( による ) // (v5r,vi) to resemble
 KanaVerb_5r( はべる ) // (v5r,vi) to wait upon/to serve
 KanaVerb_5r( もちよる ) // (v5r,vi) to gather (bringing something)/to gather (to exchange something)
 KanaVerb_5r( もちかえる ) // (v5r) to carry back or home/to take out (e.g., food)/(P)
 KanaVerb_5r( もちさる ) // (v5r) to take away/to carry away
 KanaVerb_5r( もちきる ) // (v5r,vi) to hold all the while/to talk about nothing but
 KanaVerb_5r( もってまわる ) // (v5r) to carry around
 KanaVerb_5r( もちあがる ) // (v5r,vi) to lift/to happen/to occur/to come up/to turn up
 KanaVerb_5r( うせさる ) // (v5r) to disappear/to be gone
 KanaVerb_5r( みのる ) // (v5r,vi) to bear fruit/to ripen/(P)
 KanaVerb_5r( うつる ) // (v5r,vi) to be photographed/to be projected/(P)
 KanaVerb_5r( にえくりかえる ) // (v5r,vi) to boil/to seethe
 KanaVerb_5r( にえかえる ) // (v5r,vi) to seethe/to ferment/to boil over
 KanaVerb_5r( にえたぎる ) // (v5r,vi) to boil
 KanaVerb_5r( につまる ) // (v5r) to be boiled down
 KanaVerb_5r( にあがる ) // (v5r,vi) to boil up/to be thoroughly cooked
 KanaVerb_5r( あやまる ) // (v5r,vi) to apologize/to apologise/(P)
 KanaVerb_5r( わかがえる ) // (v5r,vi) to be rejuvenated/to feel young again
 KanaVerb_5r( よわまる ) // (v5r,vi) to abate/to weaken/to be emaciated/to be dejected/to be perplexed/(P)
 KanaVerb_5r( よわりきる ) // (v5r,vi) to faint/to be exhausted
 KanaVerb_5r( よわる ) // (v5r,vi) to weaken/to be troubled/to be downcast/to be emaciated/to be dejected/to be perplexed/to impair/(P)
 KanaVerb_5r( とってまいる ) // (v5r) to fetch (something)
 KanaVerb_5r( とってかわる ) // (v5r) to supplant/to supersede
 KanaVerb_5r( とっつかまる ) // (v5r,vi) to be caught
 KanaVerb_5r( とりかかる ) // (v5r,vi) to begin/to set about/to start
 KanaVerb_5r( とりいる ) // (v5r) to make up to
 KanaVerb_5r( とりすがる ) // (v5r,vi) to cling to
 KanaVerb_5r( てまどる ) // (v5r,vi) to take time/to be delayed
 KanaVerb_5r( うかる ) // (v5r,vi) to pass (examination)/(P)
 KanaVerb_5r( おわる ) // (v5r,vi) to finish/to close/(P)
 KanaVerb_5r( おそいかかる ) // (v5r,vi) to rush on/to attack/to swoop down on
 KanaVerb_5r( あつまる ) // (v5r,vi) to gather/to collect/to assemble/(P)
 KanaVerb_5r( たかる ) // (v5r,vi) (1) to gather/to crowd round/to swarm/to flock/(2) to extort from/to sponge off/(P)
 KanaVerb_5r( しぶる ) // (v5r) to hesitate/to be reluctant/to have loose painful bowel movement/(P)
 KanaVerb_5r( かさなる ) // (v5r,vi) to be piled up/lie on top of one another/overlap each other/(P)
 KanaVerb_5r( おもる ) // (v5r,vi) to get heavy/to grow serious/(P)
 KanaVerb_5r( ちょうほうがる ) // (v5r) to find useful/to think highly of
 KanaVerb_5r( やどる ) // (v5r,vi) (1) to lodge/to dwell/(2) to be pregnant/(P)
 KanaVerb_5r( ちぢこまる ) // (v5r,vi) to curl oneself up/to squeeze oneself in/to be huddled
 KanaVerb_5r( ちぢまる ) // (v5r,vi) to be shortened/to be contracted/to shrink/(P)
 KanaVerb_5r( ちぢみあがる ) // (v5r,vi) to cringe/to wince/to flinch
 KanaVerb_5r( でしゃばる ) // (v5r,vi) to intrude/to butt in
 KanaVerb_5r( でっぱる ) // (v5r,vi) to project/to stand out/to jut out/to protrude
 KanaVerb_5r( でまわる ) // (v5r,vi) to appear on the market/to be moving
 KanaVerb_5r( でさかる ) // (v5r,vi) to appear in profusion
 KanaVerb_5r( でかわる ) // (v5r,vi) to take someone's place
 KanaVerb_5r( でばる ) // (v5r,vi) to project/to stand out/to jut out/to protrude
 KanaVerb_5r( でなおる ) // (v5r) to set out again
 KanaVerb_5r( できあがる ) // (v5r,vi) (1) to be finished/to be ready/by definition/(2) to be very drunk/(P)
 KanaVerb_5r( めぐる ) // (v5r,vi) (1) to go around/(2) to return/(3) to surround/(4) to dispute/(P)
 KanaVerb_5r( あつがる ) // (v5r,vi) to complain of the heat/to feel the heat
 KanaVerb_5r( かきおわる ) // (v5r) to finish writing
 KanaVerb_5r( たすかる ) // (v5r,vi) to be saved/to be rescued/to survive/to be helpful/(P)
 KanaVerb_5r( たすけまもる ) // (v5r) to protect/to preserve/to keep
 KanaVerb_5r( かちほこる ) // (v5r,vi) to triumph/to be elated with success
 KanaVerb_5r( かちのこる ) // (v5r,vi) to win and advance to the next round
 KanaVerb_5r( しょうせいである ) // (v5r) to stand a good chance of winning the game
 KanaVerb_5r( きえさる ) // (v5r) to disappear/to vanish
 KanaVerb_5r( きえのこる ) // (v5r,vi) to remain unextinguished/to survive
 KanaVerb_5r( きえいる ) // (v5r,vi) to vanish
 KanaVerb_5r( やきがまわる ) // (v5r) to become decrepit/to be in one's dotage/to become dull/to lose one's astuteness
 KanaVerb_5r( やけのこる ) // (v5r,vi) to escape being burned
 KanaVerb_5r( てりあがる ) // (v5r,vi) to become bright with sunlight following a shower
 KanaVerb_5r( てる ) // (v5r,vi) to shine/(P)
 KanaVerb_5r( わらっている ) // (v5r) to be smiling (laughing)
 KanaVerb_5r( うわまわる ) // (v5r,vi) to exceed/(P)
 KanaVerb_5r( うわずる ) // (v5r,vi) to be or get excited/to sound shallow/to sound hollow (a voice)/to ring false (a voice)/to sound shrill and nervous (a voice)/to be high-pitched and unstrung (a voice)
 KanaVerb_5r( じょうひんぶる ) // (v5r) to be prudish
 KanaVerb_5r( のっかる ) // (v5r,vi) to get on
 KanaVerb_5r( のっきる ) // (v5r,vi) (arch) to overcome/to get through
 KanaVerb_5r( のりうつる ) // (v5r,vi) to change (cars or horses)/to transfer/to possess/to inspire
 KanaVerb_5r( のりまわる ) // (v5r,vi) to ride around
 KanaVerb_5r( のりかかる ) // (v5r) to be about to board/to be riding on/to get on top of/to lean over/to set about/to collide with
 KanaVerb_5r( のりきる ) // (v5r,vi) to weather/to get over/to tide over/to overcome/to get through/to ride across/to sail across
 KanaVerb_5r( のりとおる ) // (v5r) to ride through/to ride along
 KanaVerb_5r( のりいる ) // (v5r) to ride into (a place)/to drive into (a place)
 KanaVerb_5r( のる ) // (v5r,vi) (1) to get on/to ride in/to board/to mount/to get up on/(v5r) (2) to spread (paints)/to be taken in/(v5r) (3) to share in/to join/to be found in (a dictionary)/to feel like doing/to be mentioned in/to be in harmony with/(P)
 KanaVerb_5r( たたまる ) // (v5r,vi) to be folded (up)
 KanaVerb_5r( うわる ) // (v5r,vi) to be planted
 KanaVerb_5r( さわる ) // (v5r,vi) to touch/to feel/(P)
 KanaVerb_5r( ふれまわる ) // (v5r,vi) to cry about/to broadcast
 KanaVerb_5r( くいいる ) // (v5r,vi) to eat into
 KanaVerb_5r( くいかじる ) // (v5r) to nibble at/to have a smattering of knowledge
 KanaVerb_5r( くってかかる ) // (v5r) to flare up at
 KanaVerb_5r( くいさがる ) // (v5r,vi) to hang on to/to doff
 KanaVerb_5r( のしかかる ) // (v5r,vi) (1) to lean on/to weigh on/(2) to bend over/to lean forward
 KanaVerb_5r( のしあがる ) // (v5r,vi) to stand on tiptoe/to rise in the world/to become arrogant
 KanaVerb_5r( のびひろがる ) // (v5r) to stretch out
 KanaVerb_5r( のびあがる ) // (v5r,vi) to stretch/to reach to/to stand on tiptoe
 KanaVerb_5r( ねそべる ) // (v5r,vi) to sprawl/to lie sprawled
 KanaVerb_5r( ねしずまる ) // (v5r,vi) to fall asleep
 KanaVerb_5r( ねころがる ) // (v5r,vi) to lie down/to throw oneself down
 KanaVerb_5r( ねいる ) // (v5r,vi) to fall asleep
 KanaVerb_5r( ねがえる ) // (v5r,vi) to change sides/to double-cross/to betray/(P)
 KanaVerb_5r( こころあたたまる ) // (v5r,vi) to be heart-warming
 KanaVerb_5r( ふりかかる ) // (v5r) (1) to fall onto/(2) to happen/to befall
 KanaVerb_5r( ふりかぶる ) // (v5r,vi) to hold aloft (e.g., a sword)/to brandish
 KanaVerb_5r( ふりかえる ) // (v5r,vi) to turn head/to look over one's shoulder/to turn around/to look back/(P)
 KanaVerb_5r( あたらしがる ) // (v5r,vi) to be fond of new things/to hunt after novelties
 KanaVerb_5r( ひたる ) // (v5r,vi) to be soaked in/to be flooded/(P)
 KanaVerb_5r( ふかまる ) // (v5r,vi) to deepen/to heighten/to intensify/(P)
 KanaVerb_5r( もうしつかわす ) // (v5r) to write to/to send word to/to hand over (official business)
 KanaVerb_5r( まじめくさる ) // (v5r,vi) to pretend to be earnest
 KanaVerb_5r( みまかる ) // (v5r,vi) to pass away/to die
 KanaVerb_5r( つらくあたる ) // (v5r) to treat badly
 KanaVerb_5r( しんたいきわまる ) // (v5r) to be at a loss
 KanaVerb_5r( ふるえあがる ) // (v5r,vi) to tremble violently/to shudder up
 KanaVerb_5r( ひとのこのむところとなる ) // (v5r) to be liked by people
 KanaVerb_5r( ひとずまとねる ) // (v5r) to sleep with another person's wife
 KanaVerb_5r( いたぶる ) // (v5r) (uk) to torment/to harass/to tease
 KanaVerb_5r( じんどる ) // (v5r,vi) to encamp/to take up positions
 KanaVerb_5r( ふきまくる ) // (v5r,vi) to blow about/to blow along/to brag
 KanaVerb_5r( ふきおくる ) // (v5r) to waft/to blow over
 KanaVerb_5r( ふきしきる ) // (v5r) to blow violently/to blow incessantly
 KanaVerb_5r( ふきつのる ) // (v5r,vi) to blow harder and harder
 KanaVerb_5r( たれさがる ) // (v5r,vi) to hang/to dangle
 KanaVerb_5r( いきがる ) // (v5r,vi) to be stylish/to try to appear smart
 KanaVerb_5r( こうじる ) // (v5r,vi) to grow in intensity/to be aggravated/to get worse/to develop
 KanaVerb_5r( かさばる ) // (v5r,vi) to be bulky/to be unwieldy/to grow voluminous
 KanaVerb_5r( すわる ) // (v5r,vi) to sit/to squat
 KanaVerb_5r( すみきる ) // (v5r,vi) to be serene/(P)
 KanaVerb_5r( すみわたる ) // (v5r,vi) to be perfectly clear
 KanaVerb_5r( うねる ) // (v5r) to undulate/to meander/to surge/to swell/to roll/to wind/(P)
 KanaVerb_5r( なりさがる ) // (v5r,vi) to be degraded/to come down in the world
 KanaVerb_5r( なりきる ) // (v5r,vi) to turn completely into/to become completely
 KanaVerb_5r( なりかわる ) // (v5r) to change/to change into/to become
 KanaVerb_5r( なりあがる ) // (v5r,vi) to rise (suddenly) in the world (to a higher position)
 KanaVerb_5r( はれあがる ) // (v5r,vi) to clear up
 KanaVerb_5r( はれわたる ) // (v5r,vi) to clear up/to be refreshed
 KanaVerb_5r( きよまる ) // (v5r,vi) to be purified/to be cleansed
 KanaVerb_5r( おいしげる ) // (v5r,vi) to grow thickly/to be overgrown
 KanaVerb_5r( はえかわる ) // (v5r) to be replaced with new growth
 KanaVerb_5r( いきのこる ) // (v5r,vi) to survive/(P)
 KanaVerb_5r( うまれかわる ) // (v5r) to be born again/to make a fresh start in life
 KanaVerb_5r( いきかえる ) // (v5r,vi) to revive/to come to oneself/to be restored to life/(P)
 KanaVerb_5r( もりあがる ) // (v5r,vi) to rouse/to swell/to rise/(P)
 KanaVerb_5r( さかる ) // (v5r,vi) (1) to prosper/to flourish/(2) to copulate (animals)
 KanaVerb_5r( しずまりかえる ) // (v5r,vi) to fall silent/to become still as death
 KanaVerb_5r( つみかさなる ) // (v5r,vi) to accumulate
 KanaVerb_5r( つもる ) // (v5r) to pile up/(P)
 KanaVerb_5r( きりかかる ) // (v5r) to begin to cut/to slash at
 KanaVerb_5r( きりさる ) // (v5r) to cut off
 KanaVerb_5r( きりかわる ) // (v5r) to change completely
 KanaVerb_5r( せっぱつまる ) // (v5r) to be at one's wit's end/to be cornered
 KanaVerb_5r( おりかさなる ) // (v5r,vi) to lie on top of one another/to be in a heap
 KanaVerb_5r( おれまがる ) // (v5r) to bend back and forth
 KanaVerb_5r( おれかえる ) // (v5r,vi) to tell again and again/to repeat/to refrain/to turn up/to turn down
 KanaVerb_5r( たえいる ) // (v5r,vi) to expire
 KanaVerb_5r( さきぼそる ) // (v5r) to taper off
 KanaVerb_5r( さきばしる ) // (v5r,vi) to be forward/to be impertinent
 KanaVerb_5r( ちぎる ) // (v5r) to cut up fine/to pick (fruit)/(P)
 KanaVerb_5r( とがる ) // (v5r,vi) to taper to a point/to become sharp/to be sour/to look displeased/(P)
 KanaVerb_5r( とんがる ) // (v5r) to get cross/to be displeased with/to get sharp
 KanaVerb_5r( あらいさる ) // (v5r) to wash away
 KanaVerb_5r( そまる ) // (v5r,vi) to dye/(P)
 KanaVerb_5r( くぐる ) // (v5r,vi) (1) to drive/to pass through/(2) to evade/to hide/(3) to dive (into or under water)/to go underground/(P)
 KanaVerb_5r( もぐる ) // (v5r,vi) (1) to drive/to pass through/(2) to evade/to hide/(3) to dive (into or under water)/to go underground
 KanaVerb_5r( えらびとる ) // (v5r) to pick out item(s) from a group to keep
 KanaVerb_5r( そうとする ) // (v5r) to admire (approve of) a person's courage
 KanaVerb_5r( かいくぐる ) // (v5r,vi) to slip through
 KanaVerb_5r( かきくもる ) // (v5r,vi) to become overcast
 KanaVerb_5r( かっぽじる ) // (v5r) (uk) to dig up/to peck at
 KanaVerb_5r( すごもる ) // (v5r,vi) to nest
 KanaVerb_5r( あらそいいかる ) // (v5r) to be angry and quarrelsome
 KanaVerb_5r( やせほそる ) // (v5r,vi) to lose weight
 KanaVerb_5r( はしりまわる ) // (v5r,vi) to run around/(P)
 KanaVerb_5r( はしりさる ) // (v5r) to run away
 KanaVerb_5r( のっとる ) // (v5r,vi) to conform to/to be in accordance with
 KanaVerb_5r( いきづまる ) // (v5r) to be breathtaking/to be stifling
 KanaVerb_5r( いきせききる ) // (v5r) to pant/to gasp
 KanaVerb_5r( いきばる ) // (v5r,vi) to strain/to bear down (in giving birth)
 KanaVerb_5r( たる ) // (v5r,vi) to be sufficient/to be enough/(P)
 KanaVerb_5r( はやまる ) // (v5r,vi) to be hasty/to be rash/to speed up/to gather speed
 KanaVerb_5r( へりくだる ) // (v5r,vi) to deprecate oneself and praise the listener/to abase oneself
 KanaVerb_5r( うちかかる ) // (v5r) to strike
 KanaVerb_5r( ぶちあたる ) // (v5r) (1) to slam into (e.g. a wall, a limit) (figuratively)/to hit/(2) to face (e.g. trouble, a problem)/to confront
 KanaVerb_5r( うっちゃる ) // (v5r) (1) to discard/to abandon/(2) to neglect/to let be
 KanaVerb_5r( うってかかる ) // (v5r) to attack/to strike/to take a swing at
 KanaVerb_5r( うってかわる ) // (v5r) to change suddenly
 KanaVerb_5r( ぶっちぎる ) // (v5r) (1) to win (a race) by a wide margin/(2) to slash though something/to tear (off)
 KanaVerb_5r( ぶつかる ) // (v5r) (uk) to strike/to collide with
 KanaVerb_5r( だべる ) // (v5r,vi) to jabber/to chatter/to chat with
 KanaVerb_5r( ていさいぶる ) // (v5r,vi) to put on airs
 KanaVerb_5r( おこたる ) // (v5r,vi) to neglect/to be off guard/to be feeling better/(P)
 KanaVerb_5r( とどこおる ) // (v5r,vi) to stagnate/to be delayed
 KanaVerb_5r( だいだいつたわる ) // (v5r) to be transmitted (handed down) from generation to generation
 KanaVerb_5r( だいばんじゃくである ) // (v5r) to be as firm as rock
 KanaVerb_5r( にごる ) // (v5r,vi) to become muddy/to get impure/(P)
 KanaVerb_5r( たたききる ) // (v5r) to mangle/to hack down/to chop down
 KanaVerb_5r( うばいさる ) // (v5r) to take away/to carry off
 KanaVerb_5r( かつぎまわる ) // (v5r) to carry something around
 KanaVerb_5r( さがしまわる ) // (v5r) to hunt around/to search about for/(P)
 KanaVerb_5r( さぐりまわる ) // (v5r) to grope for/to fumble
 KanaVerb_5r( たんさんでわる ) // (v5r) to dilute with soda
 KanaVerb_5r( たちわる ) // (v5r) to split
 KanaVerb_5r( あたたまる ) // (v5r,vi) to warm oneself/to sun oneself/to warm up/to get warm/(P)
 KanaVerb_5r( しれわたる ) // (v5r,vi) to be well-known
 KanaVerb_5r( ゆるまる ) // (v5r,vi) to become loose/to slacken/to soften
 KanaVerb_5r( はじいる ) // (v5r,vi) to feel ashamed/to be abashed
 KanaVerb_5r( はずかしがる ) // (v5r) to be shy of/to be bashful/to be abashed/to blush
 KanaVerb_5r( おきかわる ) // (v5r) to be rearranged or transposed
 KanaVerb_5r( ちゃめる ) // (v5r) to play pranks
 KanaVerb_5r( しゃべる ) // (v5r,vi) to talk/to chat/to chatter/(P)
 KanaVerb_5r( はりきる ) // (v5r) to be in high spirits/to be full of vigor (vigour)/to be enthusiastic/to be eager/to stretch to breaking point/(P)
 KanaVerb_5r( ふくれあがる ) // (v5r) to swell up
 KanaVerb_5r( はねまわる ) // (v5r,vi) to jump about
 KanaVerb_5r( はねかえる ) // (v5r) to rebound
 KanaVerb_5r( とびすぎる ) // (v5r) to overjump/to overleap
 KanaVerb_5r( ちょうじる ) // (v5r,vi) to grow/to grow up
 KanaVerb_5r( ちょうろうとしてたてまつる ) // (v5r) to kick (a person) upstairs/to revere (a person) as one's leader
 KanaVerb_5r( はかどる ) // (v5r,vi) to make progress/to move right ahead (with the work)/to advance/(P)
 KanaVerb_5r( なおる ) // (v5r,vi) (1) to be cured/to get well/to be healed/(2) to get mended/to be repaired/to be fixed/(P)
 KanaVerb_5r( ひたあやまる ) // (v5r) to apologize earnestly/to apologise earnestly
 KanaVerb_5r( しずまる ) // (v5r,vi) to quieten down/to calm down/to subside/to die down/to abate/to be suppressed/(P)
 KanaVerb_5r( おいまくる ) // (v5r) to disperse/to chase away
 KanaVerb_5r( おいせまる ) // (v5r) to gain on someone/run somebody close
 KanaVerb_5r( おいすがる ) // (v5r,vi) to be hot on a person's heels
 KanaVerb_5r( いたがる ) // (v5r,vi) to complain of pain
 KanaVerb_5r( いたみいる ) // (v5r,vi) to be greatly obliged/to be very sorry
 KanaVerb_5r( とおりかかる ) // (v5r,vi) to happen to pass by/(P)
 KanaVerb_5r( とおる ) // (v5r,vi) to pass (by)/to go through/to walk along/to pass exams/to attend (e.g., school)/(P)
 KanaVerb_5r( つかみかかる ) // (v5r) to grab at
 KanaVerb_5r( つかる ) // (v5r,vi) (1) to be pickled/to be well seasoned/(2) to be submerged/to be soaked/(P)
 KanaVerb_5r( つづる ) // (v5r) to spell/to compose
 KanaVerb_5r( つりさがる ) // (v5r,vi) to hang down/to dangle
 KanaVerb_5r( つりあがる ) // (v5r,vi) to be lifted up/to be hung up
 KanaVerb_5r( ひくまる ) // (v5r,vi) to lower/to be lowered
 KanaVerb_5r( さだはる ) // (v5r) (sl) to harp too long on a subject
 KanaVerb_5r( さだまる ) // (v5r,vi) to become settled/to be fixed/(P)
 KanaVerb_5r( したたりおちる ) // (v5r) to trickle down
 KanaVerb_5r( したたる ) // (v5r,vi) to drip/to drop/to trickle
 KanaVerb_5r( あまくだる ) // (v5r,vi) to descend from heaven
 KanaVerb_5r( あまがける ) // (v5r,vi) to soar
 KanaVerb_5r( まとまる ) // (v5r,vi) to be collected/to be settled/to be in order/(P)
 KanaVerb_5r( まつわる ) // (v5r,vi) about/concerning/to be associated with
 KanaVerb_5r( はる ) // (v5r) to stick/to paste/(P)
 KanaVerb_5r( ころがる ) // (v5r,vi) to roll/to tumble/(P)
 KanaVerb_5r( ころげまわる ) // (v5r) to roll about/to writhe about
 KanaVerb_5r( とぼる ) // (v5r,vi) to burn/to be lighted/to be lit
 KanaVerb_5r( つたってのぼる ) // (v5r) to shin up/to climb up
 KanaVerb_5r( つたわる ) // (v5r,vi) to be handed down/to be introduced/to be transmitted/to be circulated/to go along/to walk along/(P)
 KanaVerb_5r( のぼる ) // (v5r,vi) (1) to rise/to ascend/to go up/to climb/(2) to go to (the capital)/(3) to be promoted/(4) to add up to/(5) to advance (in price)/(6) to sail up/(7) to come up (on the agenda)/(P)
 KanaVerb_5r( たびかさなる ) // (v5r,vi) to repeat/to be frequent
 KanaVerb_5r( いかる ) // (v5r,vi) (1) to get angry/to get mad/(2) to be angry
 KanaVerb_5r( どなる ) // (v5r,vi) to shout/to yell/(P)
 KanaVerb_5r( たおれかかる ) // (v5r,vi) to be weighed down by debt
 KanaVerb_5r( ともる ) // (v5r,vi) to burn/to be lighted/to be lit
 KanaVerb_5r( あてこする ) // (v5r,vi) to insinuate/to satirize/to satirise/to take a dig at
 KanaVerb_5r( あてはまる ) // (v5r) to apply (a rule)/to be applicable/to come under (a category)/to fulfill
 KanaVerb_5r( あたる ) // (v5r,vi) to be hit/to be successful/to face (confront)/to lie (in the direction of)/to undertake/to treat/to be equivalent to/to apply to/to be applicable/to be assigned
 KanaVerb_5r( いたる ) // (v5r,vi) to attain
 KanaVerb_5r( うちいる ) // (v5r,vi) to break into (a house to kill the master)/to raid
 KanaVerb_5r( ふみとどまる ) // (v5r,vi) to stay on/to remain/to hold out/to stop (doing)/to give up/to hold one's ground
 KanaVerb_5r( ふんばる ) // (v5r,vi) to brace one's legs/to straddle/to stand firm/to plant oneself (somewhere)/to hold out/to persist/(P)
 KanaVerb_5r( ふんぞりかえる ) // (v5r,vi) to lie on one's back with legs outstretched/to recline/to get cocky/to be arrogant
 KanaVerb_5r( にげまわる ) // (v5r,vi) to run from place to place
 KanaVerb_5r( にげかえる ) // (v5r,vi) to scurr or run home
 KanaVerb_5r( にげさる ) // (v5r) to take flight/to disappear
 KanaVerb_5r( にげきる ) // (v5r,vi) to get away/to manage to hold on/(P)
 KanaVerb_5r( にげはしる ) // (v5r) to flee/to run away
 KanaVerb_5r( すきとおる ) // (v5r,vi) to be(come) transparent/(P)
 KanaVerb_5r( すけてうつる ) // (v5r) to be seen through
 KanaVerb_5r( うごきまわる ) // (v5r) to move around
 KanaVerb_5r( どうこういきょくである ) // (v5r) to be equally excellent in workmanship though difficult in style/to be practically the same
 KanaVerb_5r( とくいがる ) // (v5r) to be inflated with pride
 KanaVerb_5r( はげあがる ) // (v5r) to become bald fom the forehead/to recede
 KanaVerb_5r( よみおわる ) // (v5r) to finish reading/to read through
 KanaVerb_5r( よみふける ) // (v5r,vi) to be absorbed in reading
 KanaVerb_5r( つきかかる ) // (v5r) to thrust at (with a knife)
 KanaVerb_5r( つきささる ) // (v5r,vi) to stick into/to pierce/to run into
 KanaVerb_5r( つきとおる ) // (v5r,vi) to penetrate
 KanaVerb_5r( つきあたる ) // (v5r) to run into/to collide with/(P)
 KanaVerb_5r( つっかかる ) // (v5r,vi) to charge/to lunge/to rush
 KanaVerb_5r( つっぱしる ) // (v5r,vi) to run swiftly
 KanaVerb_5r( つっぱる ) // (v5r) to support/to become stiff/to become taut/to thrust (one's opponent)/to stick to (one's opinion)/to insist on/(P)
 KanaVerb_5r( のんでかかる ) // (v5r) to make light of/to hold lightly
 KanaVerb_5r( くぐもる ) // (v5r,vi) (uk) to mumble/to mutter
 KanaVerb_5r( くもる ) // (v5r,vi) to become cloudy/to become dim/(P)
 KanaVerb_5r( にぶる ) // (v5r,vi) to become less capable/to grow dull/to become blunt/to weaken/(P)
 KanaVerb_5r( ちちくる ) // (v5r,vi) to have secret or illicit sexual relations
 KanaVerb_5r( いりまじる ) // (v5r,vi) to mix with/to be mixed
 KanaVerb_5r( いりびたる ) // (v5r,vi) to seep in/to stay long
 KanaVerb_5r( いりかわる ) // (v5r,vi) to change places/to relieve (one another)
 KanaVerb_5r( はいる ) // (v5r) to enter/to break into/to join/to enroll/to contain/to hold/to accommodate/to have (an income of)/(P)
 KanaVerb_5r( いれかわる ) // (v5r,vi) to change places/to relieve one another
 KanaVerb_5r( しのびよる ) // (v5r,vi) to creep/to steal up/to draw near unnoticed
 KanaVerb_5r( しのびいる ) // (v5r,vi) to steal or sneak or slip into
 KanaVerb_5r( としよる ) // (v5r,vi) to grow old
 KanaVerb_5r( としとる ) // (v5r,vi) to grow old/to age
 KanaVerb_5r( もえうつる ) // (v5r) (of fire) to spread/to extend itself
 KanaVerb_5r( もえひろがる ) // (v5r,vi) to spread (flames)
 KanaVerb_5r( もえあがる ) // (v5r,vi) to flare up/to burst into flames/(P)
 KanaVerb_5r( もえさかる ) // (v5r,vi) to blaze/to burn brightly
 KanaVerb_5r( ねばる ) // (v5r,vi) to be sticky/to be adhesive/to persevere/to persist/to stick to/(P)
 KanaVerb_5r( こいなかである ) // (v5r) to be thick (with)/to bound by love
 KanaVerb_5r( おさまる ) // (v5r,vi) (1) to be in one's place/to be installed/to settle into/(2) to be obtained/to be settled/to be paid/to be delivered/(P)
 KanaVerb_5r( ののしる ) // (v5r,vi) to speak ill of/to abuse/(P)
 KanaVerb_5r( すたる ) // (v5r) to go out of use/to become obsolete/to die out/to go out of fashion
 KanaVerb_5r( うれのこる ) // (v5r,vi) to remain unsold/to be left on the shelf
 KanaVerb_5r( はいずる ) // (v5r,vi) (uk) to creep/to crawl
 KanaVerb_5r( はいまわる ) // (v5r,vi) to creep about
 KanaVerb_5r( はいあがる ) // (v5r,vi) to creep up/to crawl up
 KanaVerb_5r( はいつくばる ) // (v5r,vi) to grovel
 KanaVerb_5r( しろだとわかる ) // (v5r) to be found innocent
 KanaVerb_5r( せりあがる ) // (v5r) (uk) to gradually rise
 KanaVerb_5r( せまる ) // (v5r,vi) to draw near/to press/(P)
 KanaVerb_5r( ぬかる ) // (v5r,vi) to make a mistake/(P)
 KanaVerb_5r( ぬきさる ) // (v5r) to (sur)pass/to overtake
 KanaVerb_5r( ぬけあがる ) // (v5r,vi) to be balding in the front/to have a receding hairline
 KanaVerb_5r( ぬけかわる ) // (v5r) to shed/to moult/to fall out
 KanaVerb_5r( そりかえる ) // (v5r,vi) to warp/to bend backwards/to throw the head (or shoulders) back/to throw out the chest
 KanaVerb_5r( そる ) // (v5r,vi) (1) to warp/to be warped/to curve/to be curved/to be arched/(2) to bend (backward)/(P)
 KanaVerb_5r( はんぼうである ) // (v5r) to be fully occupied/to be busy
 KanaVerb_5r( かなしがる ) // (v5r,vi) to feel sorrow/to be sad
 KanaVerb_5r( つかれきる ) // (v5r) to be exhausted/to be tired out
 KanaVerb_5r( ひにくる ) // (v5r,vi) to speak cynically or with sarcasm
 KanaVerb_5r( まかりとおる ) // (v5r,vi) to go by/to let pass/to get away with
 KanaVerb_5r( こえふとる ) // (v5r) to grow fat
 KanaVerb_5r( ふとる ) // (v5r,vi) to grow fat (stout, plump)/to become fat
 KanaVerb_5r( とびうつる ) // (v5r) to jump from one thing to another
 KanaVerb_5r( とびかかる ) // (v5r) to spring upon
 KanaVerb_5r( とびさる ) // (v5r,vi) to flee away/to scatter
 KanaVerb_5r( とびちる ) // (v5r,vi) to fly around/to scatter
 KanaVerb_5r( とびのる ) // (v5r,vi) to jump on
 KanaVerb_5r( とびすさる ) // (v5r,vi) to leap back/to jump back
 KanaVerb_5r( とびかける ) // (v5r,vi) to fly/to soar
 KanaVerb_5r( とびまわる ) // (v5r,vi) to fly about/to skip about/to bustle about
 KanaVerb_5r( とびあがる ) // (v5r,vi) to spring/to jump up/to fly up/to skip
 KanaVerb_5r( そなわる ) // (v5r,vi) (1) to be furnished with/to be endowed with/(2) to be among/to be one of/to be possessed of/(P)
 KanaVerb_5r( ひゃっぽゆずる ) // (v5r) to be unwilling but to give in
 KanaVerb_5r( こおる ) // (v5r,vi) to freeze/to be frozen over/to congeal
 KanaVerb_5r( びょうきにかかる ) // (v5r) to contract a disease
 KanaVerb_5r( しきる ) // (v5r,vi) to repeat over and over again
 KanaVerb_5r( つききる ) // (v5r) to be in constant attendance
 KanaVerb_5r( つけまわる ) // (v5r,vi) to follow/to shadow/to hanker after/to hover around
 KanaVerb_5r( つけあがる ) // (v5r,vi) to be elated/to be spoiled/to be spoilt/to take advantage of
 KanaVerb_5r( つけいる ) // (v5r) to take advantage of/to impose on
 KanaVerb_5r( こわがる ) // (v5r,vi) to be afraid of/to fear/to dread/to be nervous (about)/to be shy (of)/(P)
 KanaVerb_5r( おそる ) // (v5r) to fear/to be afraid
 KanaVerb_5r( うかびあがる ) // (v5r,vi) to rise to the surface/(P)
 KanaVerb_5r( うきあがる ) // (v5r,vi) to float/to rise to the surface
 KanaVerb_5r( くさる ) // (v5r) to rot/to go bad/(P)
 KanaVerb_5r( おぶさる ) // (v5r) to ride on a person's shoulders/to be carried on a person's back
 KanaVerb_5r( ぶばる ) // (v5r,vi) to be soldierly/to be martial
 KanaVerb_5r( まいあがる ) // (v5r,vi) to soar/to fly high/to be whirled up
 KanaVerb_5r( まいもどる ) // (v5r,vi) to come back
 KanaVerb_5r( まいおどる ) // (v5r) to dance
 KanaVerb_5r( ふうきる ) // (v5r) to release (a film)
 KanaVerb_5r( はらがくだる ) // (v5r) to have loose bowels
 KanaVerb_5r( はらがへる ) // (v5r) to become hungry
 KanaVerb_5r( おおいかぶさる ) // (v5r,vi) to hang over/to cover
 KanaVerb_5r( くつがえる ) // (v5r,vi) to topple over/to be overturned/to capsize/(P)
 KanaVerb_5r( わきかえる ) // (v5r,vi) (1) to boil up/to break out/to arise/to seethe/(2) to get excited/to be in uproar
 KanaVerb_5r( わかちとる ) // (v5r) to divide the spoils/to receive a share
 KanaVerb_5r( わかる ) // (v5r,vi) (1) to understand/to grasp/(2) to know/to realize/to realise/(P)
 KanaVerb_5r( わけとる ) // (v5r) to apportion/to share
 KanaVerb_5r( わけいる ) // (v5r) to force one's way/to push through
 KanaVerb_5r( わかりきる ) // (v5r,vi) to be evident/to be obvious/to understand completely
 KanaVerb_5r( いきどおる ) // (v5r,vi) to be angry/to resent/to be enraged/to be indignant
 KanaVerb_5r( むずかる ) // (v5r,vi) to fret/to be fretful/to be peevish
 KanaVerb_5r( ききいる ) // (v5r) to listen attentively to/to be lost in
 KanaVerb_5r( あわさる ) // (v5r,vi) to get together/to unite
 KanaVerb_5r( へいつくばる ) // (v5r) to make a deep bow
 KanaVerb_5r( とじこもる ) // (v5r,vi) to seclude oneself/to shut oneself away
 KanaVerb_5r( しまる ) // (v5r,vi) (1) to be shut/to close/to be closed/(2) to be locked/(3) to tighten/to be tightened/(4) to become sober/to become tense/(P)
 KanaVerb_5r( へいまくとなる ) // (v5r) to come to a close (end)
 KanaVerb_5r( かわる ) // (v5r,vi) to change/to be transformed/to vary/to be revised/to be different/to move location/(P)
 KanaVerb_5r( かたよる ) // (v5r,vi) to be one-sided/to incline/to be partial/to be prejudiced/to lean/to be biased/to be biassed/(P)
 KanaVerb_5r( つかまる ) // (v5r,vi) to be caught/to be arrested/(P)
 KanaVerb_5r( あるきまわる ) // (v5r) to walk about/to walk to and fro/to pace around/(P)
 KanaVerb_5r( あゆみよる ) // (v5r,vi) to step up/to compromise/to meet halfway/(P)
 KanaVerb_5r( つのる ) // (v5r) to invite/to solicit help, participation, etc./(P)
 KanaVerb_5r( したいよる ) // (v5r,vi) to approach in adoration
 KanaVerb_5r( くれのこる ) // (v5r,vi) lingering faint light of twilight
 KanaVerb_5r( くるまる ) // (v5r,vi) to be wrapped up (e.g., in a blanket)/to cover oneself
 KanaVerb_5r( つつみかざる ) // (v5r,vi) to cover up and make a show
 KanaVerb_5r( あきれかえる ) // (v5r,vi) to be utterly amazed
 KanaVerb_5r( くずれさる ) // (v5r) to crumble away/to collapse
 KanaVerb_5r( ほめまつる ) // (v5r) to praise/to render homage to
 KanaVerb_5r( とぼしくなる ) // (v5r) to get scarce/to run short
 KanaVerb_5r( わする ) // (v5r) (arch) to lose something
 KanaVerb_5r( あばれまわる ) // (v5r) to rampage/to run riot
 KanaVerb_5r( ぼうでなぐる ) // (v5r) to hit with a club
 KanaVerb_5r( ぼうにふる ) // (v5r) to make a mess of/to sacrifice/to waste
 KanaVerb_5r( ひるがえる ) // (v5r,vi) to turn over/to wave/to flutter/(P)
 KanaVerb_5r( すりよる ) // (v5r,vi) to draw close to/to edge up to/to snuggle up to/to nestle close to/to cuddle with/to draw closer to
 KanaVerb_5r( すりきる ) // (v5r) to cut by rubbing/to wear out/to spend all (one's money)
 KanaVerb_5r( すりへる ) // (v5r,vi) to be worn down/to be reduced
 KanaVerb_5r( うずまる ) // (v5r,vi) to be buried/to be surrounded/to overflow/to be filled/(P)
 KanaVerb_5r( うまる ) // (v5r,vi) to be buried/to be surrounded/to overflow/to be filled/(P)
 KanaVerb_5r( はびこる ) // (v5r,vi) to spread/to run rampant/to grow thick/to become powerful/(P)
 KanaVerb_5r( あじわいしる ) // (v5r) to taste and know
 KanaVerb_5r( みいる ) // (v5r) to be entranced or possessed
 KanaVerb_5r( ねむる ) // (v5r,vi) to sleep/(P)
 KanaVerb_5r( つとまる ) // (v5r,vi) to be fit for/to be equal to/to function properly
 KanaVerb_5r( なくなる ) // (v5r,vi) to disappear/to get lost/(P)
 KanaVerb_5r( なのる ) // (v5r,vi) to call oneself (name, label, etc)/to give one's name (as)/(P)
 KanaVerb_5r( めいじおわる ) // (v5r) to finish giving orders
 KanaVerb_5r( あけのこる ) // (v5r,vi) moon and stars remaining in the morning sky
 KanaVerb_5r( あけわたる ) // (v5r,vi) to become daylight
 KanaVerb_5r( なりわたる ) // (v5r,vi) to resound (echo) far and wide
 KanaVerb_5r( なる ) // (v5r,vi) to sound/to ring/to resound/to echo/to roar/to rumble/(P)
 KanaVerb_5r( めいる ) // (v5r,vi) to feel depressed
 KanaVerb_5r( おもしろがる ) // (v5r,vi) to amuse oneself/to be amused/to enjoy/to think fun
 KanaVerb_5r( かたどる ) // (v5r,vi) (1) to model on/to make in the shape of/to represent/to pattern after/to imitate/(2) to symbolise
 KanaVerb_5r( しげる ) // (v5r,vi) to grow thick/to luxuriate/to be luxurious/(P)
 KanaVerb_5r( もうかる ) // (v5r,vi) to be profitable/to yield a profit/(P)
 KanaVerb_5r( だまりこくる ) // (v5r,vi) to keep silent
 KanaVerb_5r( めがまわる ) // (v5r) to be dizzy/to feel faint
 KanaVerb_5r( めだちたがる ) // (v5r) to show off
 KanaVerb_5r( もったいぶる ) // (v5r,vi) to put on airs/to assume importance
 KanaVerb_5r( いやまさる ) // (v5r,vi) to become still greater
 KanaVerb_5r( おどりかかる ) // (v5r) to spring at or upon
 KanaVerb_5r( まさる ) // (v5r,vi) to excel/to surpass/to outrival
 KanaVerb_5r( ありがたがる ) // (v5r) to be thankful/to feel grateful/to show one's gratitude
 KanaVerb_5r( ある ) // (v5r-i,vi) (1) (uk) to live/to be/to exist/(2) to have/(3) to be located/(4) to be equipped with/(5) to happen/to come about
 KanaVerb_5r( ありあまる ) // (v5r,vi) to be superfluous/to be in excess/to be more than enough
 KanaVerb_5r( わきおこる ) // (v5r) to well up/to rise
 KanaVerb_5r( わきあがる ) // (v5r,vi) (1) to boil up/to break out/to arise/to seethe/(2) to get excited/to be in uproar
 KanaVerb_5r( あそびまわる ) // (v5r) to jaunt around/to play around/to visit one place after another without effect
 KanaVerb_5r( あまる ) // (v5r,vi) to remain/to be left over/to be in excess/to be too many/(P)
 KanaVerb_5r( よたる ) // (v5r,vi) to live a wicked life
 KanaVerb_5r( ようだいぶる ) // (v5r,vi) to put on airs
 KanaVerb_5r( あがる ) // (v5r,vi) to rise/(P)
 KanaVerb_5r( ゆさぶる ) // (v5r) to shake/to jolt/to rock/to swing/(P)
 KanaVerb_5r( ゆすぶる ) // (v5r) to shake/to jolt/to rock/to swing
 KanaVerb_5r( さまがわる ) // (v5r) to change the state of things
 KanaVerb_5r( おどりあがる ) // (v5r,vi) to spring up/to leap to one's feet/to jump up and down
 KanaVerb_5r( よくばる ) // (v5r,vi) to covet/to lust for
 KanaVerb_5r( きたる ) // (v5r,vi) to come/to arrive/to be due to/to be next/to be forthcoming/(P)
 KanaVerb_5r( きかかる ) // (v5r) to happen to come
 KanaVerb_5r( たよる ) // (v5r,vi) to rely on/to have recourse to/to depend on/(P)
 KanaVerb_5r( からまる ) // (v5r,vi) to be entwined/to be involved
 KanaVerb_5r( おちいる ) // (v5r,vi) to fall/to trap/to cave in/to collapse
 KanaVerb_5r( りこうすぎる ) // (v5r) to be too clever
 KanaVerb_5r( うらがえる ) // (v5r,vi) to be turned inside out
 KanaVerb_5r( たちはだかる ) // (v5r,vi) to block one's way
 KanaVerb_5r( たちまわる ) // (v5r,vi) to walk about/to turn up/to conduct oneself
 KanaVerb_5r( たちさる ) // (v5r,vi) to leave/to depart/to take one's leave/(P)
 KanaVerb_5r( たちまじる ) // (v5r,vi) to join
 KanaVerb_5r( たちどまる ) // (v5r) to stop/to halt/to stand still/(P)
 KanaVerb_5r( たちいたる ) // (v5r) to come to
 KanaVerb_5r( たちまさる ) // (v5r) to surpass
 KanaVerb_5r( たちあがる ) // (v5r,vi) to stand up/(P)
 KanaVerb_5r( たちのぼる ) // (v5r,vi) to go up/to rise up
 KanaVerb_5r( たちかわる ) // (v5r) to alternate/to take turns
 KanaVerb_5r( たちなおる ) // (v5r,vi) to regain one's footing/to recover/(of the market) to improve/(P)
 KanaVerb_5r( たちどおしである ) // (v5r) to keep standing (all the way)
 KanaVerb_5r( たちかえる ) // (v5r,vi) to turn back
 KanaVerb_5r( たちもどる ) // (v5r,vi) to return/to come back
 KanaVerb_5r( たてなおる ) // (v5r,vi) to recover/to rally/to pick up
 KanaVerb_5r( たちよる ) // (v5r,vi) to stop by/to drop in for a short visit
 KanaVerb_5r( たちふさがる ) // (v5r,vi) to stand in one's way
 KanaVerb_5r( たちいる ) // (v5r,vi) to enter/to interfere
 KanaVerb_5r( たてこもる ) // (v5r,vi) to barricade oneself in/to hold (a fort, etc.)/to shut oneself up/to be besieged/to dig in
 KanaVerb_5r( かする ) // (v5r) to graze/to squeeze/to become blurred/to exploit
 KanaVerb_5r( はやる ) // (v5r,vi) to flourish/to thrive/to be popular/to come into fashion/(P)
 KanaVerb_5r( たまる ) // (v5r,vi) to collect/to gather/to save
 KanaVerb_5r( りゅういんがさがる ) // (v5r) to feel gratified
 KanaVerb_5r( とどまる ) // (v5r,vi) (1) to remain/to abide/to stay (in the one place)/(v5r) (2) to come to a halt/(v5r) (3) to stop
 KanaVerb_5r( とまる ) // (v5r,vi) (1) to remain/to abide/to stay (in the one place)/(v5r) (2) to come to a halt/(v5r) (3) to stop
 KanaVerb_5r( たびする ) // (v5r) to travel/to take a trip
 KanaVerb_5r( りょうけのうまれである ) // (v5r) to be of good family
 KanaVerb_5r( さびしがる ) // (v5r) to miss someone (or something)/to feel lonely
 KanaVerb_5r( ひえあがる ) // (v5r,vi) to get completely chilled
 KanaVerb_5r( ひえきる ) // (v5r,vi) to become completely chilled
 KanaVerb_5r( ひえいる ) // (v5r,vi) to become completely chilled
 KanaVerb_5r( ひえつのる ) // (v5r) to get colder/to get chilled
 KanaVerb_5r( おとる ) // (v5r,vi) to fall behind/to be inferior to/(P)
 KanaVerb_5r( こいみだる ) // (v5r) to be lovesick
 KanaVerb_5r( こいこもる ) // (v5r) to be deeply in love
 KanaVerb_5r( こいしがる ) // (v5r) to yearn for/to miss
 KanaVerb_5r( ねる ) // (v5r,vi) to knead/to work over/to polish up/(P)
 KanaVerb_5r( つらなる ) // (v5r,vi) to extend/to stretch out/to stand in a row/(P)
 KanaVerb_5r( つれかえる ) // (v5r) to bring (someone) back home/to take (someone) back home
 KanaVerb_5r( つれさる ) // (v5r) to take away/to kidnap/(P)
 KanaVerb_5r( いたわる ) // (v5r) to pity/to sympathize with/to sympathise with/to console/to care for/to be kind to/(P)
 KanaVerb_5r( もる ) // (v5r) to leak/to run out/(P)
 KanaVerb_5r( とる ) // (v5r) to record (video, audio, etc.)
 KanaVerb_5r( わたる ) // (v5r) to extend
 KanaVerb_5r( わびいる ) // (v5r,vi) to apologize sincerely/to apologise sincerely
 KanaVerb_5r( もぎとる ) // (v5r) (uk) to pluck off/to pick/to break or tear off
 KanaVerb_5r( よりかかる ) // (v5r,vi) to lean against/to recline on/to lean on/to rely on
 KanaVerb_5r( もたれかかる ) // (v5r) to lean on/to recline on/to rely on
 KanaVerb_5r( はねあがる ) // (v5r,vi) to jump up/to spring up
 KanaVerb_5r( きる ) // (v5r) to cut
 KanaVerb_5r( けちる ) // (v5r) (uk) to be stingy/to scrimp
 KanaVerb_5r( うなる ) // (v5r,vi) to groan/to moan/to roar/to howl/to growl/to hum/to buzz/to sough/(P)
 KanaVerb_5r( むせかえる ) // (v5r,vi) to choke/to sob convulsively
 KanaVerb_5r( さえずる ) // (v5r,vi) (uk) to sing/to chirp/to twitter/(P)
 KanaVerb_5r( みごもる ) // (v5r,vi) to become pregnant
 KanaVerb_5r( かえる ) // (v5r) to hatch out
 KanaVerb_5r( もとる ) // (v5r,vi) to go against/to deviate from/to oppose
 KanaVerb_5r( はばかる ) // (v5r,vi) (1) to hesitate/to have scruples/(2) to lord it over/to have great influence
 KanaVerb_5r( しなだれかかる ) // (v5r,vi) to lean coquettishly against/to snuggle into/to nestle into
 KanaVerb_5r( よじのぼる ) // (v5r,vi) to climb/to clamber (over, up)/to scramble (up)/to scale/to claw one's way up
 KanaVerb_5r( てこずる ) // (v5r) (uk) to have much trouble/to have a hard time/to not know how to handle
 KanaVerb_5r( しみとおる ) // (v5r,vi) (1) to soak through/(2) to be deeply impressed
 KanaVerb_5r( さかのぼる ) // (v5r,vi) to go back/to go upstream/to make retroactive
 KanaVerb_5r( たぎる ) // (v5r,vi) to boil/to seethe
 KanaVerb_5r( しみわたる ) // (v5r,vi) to penetrate/to pervade/to spread
 KanaVerb_5r( みなぎる ) // (v5r,vi) (uk) to swell up/to rise/to be (brim) full of/to pervade
 KanaVerb_5r( いたまる ) // (v5r) to be sauteed in oil
 KanaVerb_5r( けぶる ) // (v5r,vi) (1) to smoke (e.g., fire)/(2) to be hazy
 KanaVerb_5r( けむる ) // (v5r,vi) (1) to smoke (e.g., fire)/(2) to be hazy
 KanaVerb_5r( いぶる ) // (v5r,vi) to smoke/to smoulder/to smolder/to sputter
 KanaVerb_5r( くすぶる ) // (v5r,vi) to smoke/to smoulder/to smolder/to sputter
 KanaVerb_5r( おきる ) // (v5r,vi) to be kindled (fire)/to be made
 KanaVerb_5r( ずるける ) // (v5r) (uk) to shirk one's duties/to be idle/to play truant
 KanaVerb_5r( よみがえる ) // (v5r,vi) to be resurrected/to be revived/to be resuscitated/to be rehabilitated/(P)
 KanaVerb_5r( つる ) // (v5r) to cramp/to be cramped/to contract
 KanaVerb_5r( しこる ) // (v5r,vi) to stiffen/to harden
 KanaVerb_5r( たたる ) // (v5r,vi) to curse/to cast a spell
 KanaVerb_5r( こもる ) // (v5r,vi) to seclude oneself/to be confined in/to be implied/to be stuffy
 KanaVerb_5r( すがる ) // (v5r,vi) to cling to/to rely on/(P)
 KanaVerb_5r( なめずる ) // (v5r) to lick one's lips
 KanaVerb_5r( うだる ) // (v5r,vi) (1) to boil/to seethe/(2) to be oppressed by heat
 KanaVerb_5r( ゆだる ) // (v5r,vi) (1) to boil/to seethe/(2) to be oppressed by heat
 KanaVerb_5r( わだかまる ) // (v5r) (1) (uk) to lurk/to hover in the background/(2) to be coiled up/to stretch tortuously
 KanaVerb_5r( なまる ) // (v5r,vi) to speak with an accent/to be corrupted (of word)
 KanaVerb_5r( いぶかる ) // (v5r,vi) to suspect
 KanaVerb_5r( うずくまる ) // (v5r,vi) (uk) to crouch/to squat/to cower/(P)
 KanaVerb_5r( いざる ) // (v5r,vi) to crawl/to shuffle along
 KanaVerb_5r( にじりよる ) // (v5r,vi) to sidle up to
 KanaVerb_5r( きしる ) // (v5r) to creak/to squeak
 KanaVerb_5r( だましとる ) // (v5r) to take something away by deception
 KanaVerb_5r( おごる ) // (v5r,vi) (1) to be proud/to be haughty/(2) to be extravagant/to live luxuriously/(3) to give (someone) a treat
  
 KanaVerb_5r( かかる ) // to take
 
 KanaVerb( かける ) // (v5r,vi) to soar/to fly/(P)

 
 entry いる : JAP_VERB
 {
  JAP_TRANSITIVE
  JAP_FORM:KANA
  
  JAP_VERB_BASE:I            { "い" }
  JAP_VERB_BASE:II           { "い" }
  JAP_VERB_BASE:III          { "いる" }
  JAP_VERB_BASE:IV           { "いれ" }
  JAP_VERB_BASE:V            { "いよう"}
  JAP_VERB_BASE:PAST         { "いた" }
  JAP_VERB_BASE:PARTICIPLE   { "いて" }
 }
 
 
 
}
