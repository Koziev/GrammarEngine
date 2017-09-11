// CD->01.03.2009
// LC->25.01.2013

automat sg
{
 // Для прилагательных, у которых словарная основа заканчивается на い
 #define KanjiAdj0(x) entry x : JAP_ADJECTIVE { JAP_FORM:KANJI paradigm JapAdj_9700 }

 // Для полупредикативных прилагательных, у которых основа заканчивается на -の или -な 
 #define KanjiAdj1(x) entry x : JAP_ADJECTIVE { JAP_FORM:KANJI paradigm JapAdj_9701 }

 // Для китайских прилагательных
 #define KanjiAdj2(x) entry x : JAP_ADJECTIVE { JAP_FORM:KANJI paradigm JapAdj_9702 }

 // Есть только словарная форма
 #define KanjiAdj3(x) entry x : JAP_ADJECTIVE { JAP_FORM:KANJI paradigm JapAdj_9703 }

 KanjiAdj1(安全な) // безопасный
 KanjiAdj1(不明な) // неясный
 KanjiAdj1(神経質な) // нервозный

 KanjiAdj0( 見にくい )
 KanjiAdj0( 見づらい )
 KanjiAdj0( いけ好かない ) // (adj) nasty/disgusting/disagreeable/creepy
 KanjiAdj0( うそ寒い ) // (adj) somewhat cold/a bit chilly
 KanjiAdj0( うら若い ) // (adj) young/youthful
 KanjiAdj0( うら寂しい ) // (adj) lonesome/lonely/forlorn
 KanjiAdj0( うら恥ずかしい ) // (adj) slightly ashamed/rather shy
 KanjiAdj0( うら悲しい ) // (adj) sad/mournful/melancholy/sorrowful
 KanjiAdj0( え辛っぽい ) // (adj) (uk) acrid/pungent
 KanjiAdj0( おそれ多い ) // (adj) awesome/awe-inspiring/august
 KanjiAdj0( お寒い ) // (adj) poor/unsatisfactory/inadequate
 KanjiAdj0( お高い ) // (adj) haughty
 KanjiAdj0( かび臭い ) // (adj) musty/putrid
 KanjiAdj0( かん高い ) // (adj) shrill
 KanjiAdj0( か弱い ) // (adj) frail/feeble/(P)
 KanjiAdj0( がまん強い ) // (adj) patient/persevering
 KanjiAdj0( きな臭い ) // (adj) (1) burning or scorched smell/(2) imminent military action/(3) suspicious
 KanjiAdj0( きまり悪い ) // (adj) feeling awkward/being ashamed/(P)
 KanjiAdj0( けったくそ悪い ) // (adj) (vulg) extremely vexing
 KanjiAdj0( こっ酷い ) // (adj) (uk) bad/harsh/severe
 KanjiAdj0( ご機嫌麗しい ) // (adj) be in good humor (humour)
 KanjiAdj0( ずる賢い ) // (adj-na) sly
 KanjiAdj0( だだっ広い ) // (adj) very (excessively) spacious/unduly wide/sprawling
 KanjiAdj0( どす黒い ) // (adj) darkish/dusky
 KanjiAdj0( ど偉い ) // (adj) immense/awesome/enormous/terrific
 KanjiAdj0( なじみ深い ) // (adj) extremely intimate/very well-acquainted
 KanjiAdj0( ひ弱い ) // (adj) weak/sickly
 KanjiAdj0( ほど遠い ) // (adj) far off or away
 KanjiAdj0( ほど近い ) // (adj) near/nearby/not far off
 KanjiAdj0( ほろ酔い ) // (adj) slightly drunk/tipsy
 KanjiAdj0( まんざら夢ではない ) // (adj) not altogether a dream
 KanjiAdj0( やり切れない ) // (adj) unbearable/too much/(P)
 KanjiAdj0( より良い ) // (adj) superior/better
 KanjiAdj0( ろれつが回らない ) // (adj) speaking inarticulately (slurring, lisping, etc)
 KanjiAdj0( バタ臭い ) // (adj) Western (lit: smelling of butter)/European/exotic/outlandish/alien
 KanjiAdj0( ホロ苦い ) // (adv,adj) bittersweet/slightly bitter/something that has a strong taste that adults favor
 KanjiAdj0( ボール扱いが巧い ) // (adj) being good at handling a ball
 KanjiAdj0( 阿呆らしい ) // (adj) ridiculous
 KanjiAdj0( 阿呆臭い ) // (adj) ridiculous
 KanjiAdj0( 阿娜っぽい ) // (adj) coquettish
 KanjiAdj0( 哀しい ) // (oK) (adj) sad/sorrowful
 KanjiAdj0( 哀れっぽい ) // (adj) plaintive/piteous/doleful
 KanjiAdj0( 愛おしい ) // (adj) lovely/sweet/precious/adorable
 KanjiAdj0( 愛くるしい ) // (adj) lovely/cute
 KanjiAdj0( 愛しい ) // (adj) lovely/dear/beloved/darling/(P)
 KanjiAdj0( 愛でたい ) // (adj) auspicious
 KanjiAdj0( 愛らしい ) // (adj) pretty/charming/lovely
 KanjiAdj0( 愛想のいい ) // (adj) affable/amiable/sociable/agreeable
 KanjiAdj0( 悪い ) // (adj) bad/inferior/(P)
 KanjiAdj0( 悪戯っぽい ) // (adj) (uk) roguish/impish
 KanjiAdj0( 悪賢い ) // (adj) cunning/crafty/wily/sly/(P)
 KanjiAdj0( 悪名高い ) // (adj) infamous/notorious
 KanjiAdj0( 扱い難い ) // (adj) hard to handle
 KanjiAdj0( 安い ) // (adj) cheap/inexpensive/peaceful/quiet/gossipy/thoughtless/(P)
 KanjiAdj0( 安っぽい ) // (adj) cheap-looking/tawdry/insignificant/(P)
 KanjiAdj0( 暗い ) // (adj) (uk) dark/gloomy/(P)
 KanjiAdj0( 偉い ) // (adj) great/celebrated/eminent/terrible/awful/famous/remarkable/excellent/(P)
 KanjiAdj0( 委しい ) // (iK) (adj) knowing very well/detailed/full/accurate
 KanjiAdj0( 意を得ない ) // (adj) fail to make sense (of)
 KanjiAdj0( 意気地のない ) // (adj) spineless/backboneless/timid/cowardly/weak-kneed
 KanjiAdj0( 意義深い ) // (adj) significant/important
 KanjiAdj0( 意地悪い ) // (adj) ill-natured
 KanjiAdj0( 意地汚い ) // (adj) gluttonous/greedy
 KanjiAdj0( 意地汚ない ) // (adj) gluttonous/greedy
 KanjiAdj0( 意地穢い ) // (adj) gluttonous/greedy
 KanjiAdj0( 意味が通らない ) // (adj) be incomprehensible/not make sense
 KanjiAdj0( 易い ) // (adj,suf) easy/(P)
 KanjiAdj0( 易しい ) // (adj) easy/plain/simple/(P)
 KanjiAdj0( 為悪い ) // (adj) hard to do
 KanjiAdj0( 畏れ多い ) // (adj) awesome/awe-inspiring/august
 KanjiAdj0( 異存がない ) // (adj) nothing to say/have no objection
 KanjiAdj0( 違いない ) // (adj,exp) (phrase) sure/no mistaking it/for certain/(P)
 KanjiAdj0( 違い無い ) // (adj,exp) (phrase) sure/no mistaking it/for certain
 KanjiAdj0( 遺憾に堪えない ) // (adj) be really regrettable
 KanjiAdj0( 育ちが良い ) // (adj) be well-bred
 KanjiAdj0( 一顧もしない ) // (adj) not give a damn/take no notice of
 KanjiAdj0( 一番多い ) // (adj) most numerous
 KanjiAdj0( 一溜まりもない ) // (adj) without difficulty
 KanjiAdj0( 一溜まりも無い ) // (adj) without difficulty
 KanjiAdj0( 飲みやすい ) // (adj) easy to drink/easy to swallow/quaffable
 KanjiAdj0( 飲み易い ) // (adj) easy to drink/easy to swallow/quaffable
 KanjiAdj0( 陰気臭い ) // (adj) dismal/gloomy
 KanjiAdj0( 烏滸がましい ) // (adj) (uk) presumptuous/impertinent/ridiculous/absurd
 KanjiAdj0( 運が悪い ) // (adj) is unlucky
 KanjiAdj0( 永い ) // (adj) long/lengthy
 KanjiAdj0( 鋭い ) // (adj) pointed/sharp/(P)
 KanjiAdj0( 悦ばしい ) // (adj) delightful/joyful/gratifying
 KanjiAdj0( 厭やらしい ) // (adj) unpleasant/disgusting/repulsive/detestable/disagreeable/indecent/lewd/dirty/lascivious/(P)
 KanjiAdj0( 厭わしい ) // (adj) detestable/disagreeable
 KanjiAdj0( 円い ) // (adj) round/circular/spherical/(P)
 KanjiAdj0( 怨めしい ) // (adj) reproachful/hateful/bitter
 KanjiAdj0( 煙い ) // (adj) smoky/(P)
 KanjiAdj0( 煙たい ) // (adj) smoky/feeling awkward/(P)
 KanjiAdj0( 縁がない ) // (adj) have no relation to
 KanjiAdj0( 縁が遠い ) // (adj) distantly related
 KanjiAdj0( 縁が無い ) // (adj) have no relation to
 KanjiAdj0( 縁遠い ) // (adj) (1) lately married/(2) having little prospect of marriage/(3) unconnected/weakly related
 KanjiAdj0( 艶かしい ) // (adj) charming/captivating
 KanjiAdj0( 艶っぽい ) // (adj) romantic/spicy/coquettish
 KanjiAdj0( 艶めかしい ) // (adj) charming/captivating
 KanjiAdj0( 遠い ) // (adj) far/distant/(P)
 KanjiAdj0( 遠く及ばない ) // (adj) fall far short of/be no equal (match) for
 KanjiAdj0( 遠慮のない ) // (adj) unreserved
 KanjiAdj0( 遠慮の無い ) // (adj) unreserved
 KanjiAdj0( 遠慮深い ) // (adj) reserved
 KanjiAdj0( 塩っぱい ) // (adj) (1) (sl) salty/(2) stingy/(3) hoarse/(4) wearisome
 KanjiAdj0( 塩辛い ) // (adj) salty (taste)/(P)
 KanjiAdj0( 汚い ) // (adj) dirty/unclean/filthy/(P)
 KanjiAdj0( 汚らしい ) // (adj) dirty-looking/squalid
 KanjiAdj0( 汚らわしい ) // (adj) filthy/unfair
 KanjiAdj0( 奥ゆかしい ) // (adj) humble/modest
 KanjiAdj0( 奥床しい ) // (adj) refined/graceful/modest
 KanjiAdj0( 奥深い ) // (adj) profound/deep
 KanjiAdj0( 押しつけがましい ) // (adj) pushy/pushing/self-assertive
 KanjiAdj0( 押しも押されもしない ) // (adj) of established reputation
 KanjiAdj0( 押し付けがましい ) // (adj) pushy/pushing/self-assertive
 KanjiAdj0( 黄色い ) // (adj) yellow/(P)
 KanjiAdj0( 臆面もない ) // (adj) bold/audacious/impudent/unashamed/unabashed
 KanjiAdj0( 恩着せがましい ) // (adj) condescending/patronizing
 KanjiAdj0( 温い ) // (adj) (uk) lukewarm/tepid/(P)
 KanjiAdj0( 温かい ) // (adj) warm/mild/genial
 KanjiAdj0( 下らない ) // (adj) good-for-nothing/stupid/trivial/worthless/(P)
 KanjiAdj0( 何でもない ) // (adj,exp) easy/trifling/harmless
 KanjiAdj0( 何でも無い ) // (adj,exp) easy/trifling/harmless
 KanjiAdj0( 何の変哲もない ) // (adj) ordinary/plain/commonplace
 KanjiAdj0( 何の変哲も無い ) // (adj) ordinary/plain/commonplace
 KanjiAdj0( 何気ない ) // (adj) casual/unconcerned/(P)
 KanjiAdj0( 何気無い ) // (adj) casual/unconcerned
 KanjiAdj0( 何時にない ) // (adj) unusual
 KanjiAdj0( 何時に無い ) // (adj) unusual
 KanjiAdj0( 価値高い ) // (adj) valuable
 KanjiAdj0( 可愛い ) // (adj) (sl) pretty/cute/lovely/charming/dear/darling/pet
 KanjiAdj0( 可愛らしい ) // (adj) lovely/sweet/(P)
 KanjiAdj0( 可笑しい ) // (adj) (uk) strange/funny/amusing/ridiculous/(P)
 KanjiAdj0( 家庭を顧みない ) // (adj) thinking little of one's family
 KanjiAdj0( 暇がない ) // (adj) be busy/have no (free) time
 KanjiAdj0( 暇が無い ) // (adj) be busy/have no (free) time
 KanjiAdj0( 果てしがない ) // (adj) endless/boundless/fathomless/eternal
 KanjiAdj0( 果てしが無い ) // (adj) endless/boundless/fathomless/eternal
 KanjiAdj0( 果てしない ) // (adj) endless/boundless/everlasting/(P)
 KanjiAdj0( 果てし無い ) // (adj) endless/boundless/everlasting
 KanjiAdj0( 果ない ) // (adj) fleeting/transient/short-lived/momentary/vain/fickle/miserable/empty/ephemeral
 KanjiAdj0( 果敢ない ) // (adj) fleeting/transient/short-lived/momentary/vain/fickle/miserable/empty/ephemeral
 KanjiAdj0( 果敢無い ) // (adj) fleeting/transient/short-lived/momentary/vain/fickle/miserable/empty/ephemeral
 KanjiAdj0( 果無い ) // (adj) fleeting/transient/short-lived/momentary/vain/fickle/miserable/empty/ephemeral
 KanjiAdj0( 火付きが悪い ) // (adj) be slow to kindle
 KanjiAdj0( 禍々しい ) // (adj) (1) (uk) ominous/sinister/unlucky/ill-omened/(2) annoying/(3) appearing to be true
 KanjiAdj0( 禍禍しい ) // (adj) (1) (uk) ominous/sinister/unlucky/ill-omened/(2) annoying/(3) appearing to be true
 KanjiAdj0( 花々しい ) // (adj) brilliant/magnificent/spectacular
 KanjiAdj0( 花花しい ) // (adj) brilliant/magnificent/spectacular
 KanjiAdj0( 花恥ずかしい ) // (adj) beauty such as to put a flower to shame
 KanjiAdj0( 苛立たしい ) // (adj) irritation
 KanjiAdj0( 華々しい ) // (adj) brilliant/magnificent/spectacular/(P)
 KanjiAdj0( 華華しい ) // (adj) brilliant/magnificent/spectacular
 KanjiAdj0( 我が強い ) // (adj) egoistic/selfish/self-willed
 KanjiAdj0( 我慢強い ) // (adj) patient/persevering
 KanjiAdj0( 芽出度い ) // (adj) happy/simple soul/propitious/joyous
 KanjiAdj0( 解せない ) // (adj,exp) inscrutable/incomprehensible
 KanjiAdj0( 解り悪い ) // (oK) (adj) hard to understand/incomprehensible/unintelligible
 KanjiAdj0( 解り難い ) // (adj) hard to understand/incomprehensible/unintelligible
 KanjiAdj0( 解難い ) // (adj) difficult to solve
 KanjiAdj0( 回りくどい ) // (adj) circuitous/roundabout/indirect
 KanjiAdj0( 壊れ易い ) // (adj) fragile/break easily
 KanjiAdj0( 快い ) // (adj) pleasant/agreeable/(P)
 KanjiAdj0( 怪しい ) // (adj) (1) suspicious/dubious/doubtful/(P)
 KanjiAdj0( 悔しい ) // (adj) regrettable/mortifying/vexing
 KanjiAdj0( 悔やしい ) // (io) (adj) regrettable/mortifying/vexing
 KanjiAdj0( 懐かしい ) // (adj) dear/desired/missed/(P)
 KanjiAdj0( 馨しい ) // (adj) (uk) sweet-smelling/scentful/fragrant
 KanjiAdj0( 格好いい ) // (ik) (adj) attractive/good-looking/stylish/cool
 KanjiAdj0( 格好のいい ) // (adj-na) attractive/good-looking/stylish/cool
 KanjiAdj0( 格好の悪い ) // (adj-na) unattractive/ugly/unstylish/uncool
 KanjiAdj0( 格好よい ) // (adj) attractive/good-looking/stylish/cool
 KanjiAdj0( 格好悪い ) // (adj-na) unattractive/ugly/unstylish/uncool
 KanjiAdj0( 覚え易い ) // (adj) be easy to learn
 KanjiAdj0( 覚束ない ) // (adj) uncertain/doubtful/unreliable
 KanjiAdj0( 角々しい ) // (adj) intractable/angular
 KanjiAdj0( 角角しい ) // (adj) intractable/angular
 KanjiAdj0( 楽しい ) // (adj) enjoyable/fun/(P)
 KanjiAdj0( 額が少ない ) // (adj) insufficient (money or things)
 KanjiAdj0( 掛け替えのない ) // (adj-pn) thing with no substitute/money can't buy
 KanjiAdj0( 割の良い ) // (adj) paying/remunerative/advantageous/profitable
 KanjiAdj0( 割り切れない ) // (adj) indivisible/unconvincing/incomprehensible/unaccounted for
 KanjiAdj0( 割れ易い ) // (adj) brittle/fragile/easily cracked/perishable
 KanjiAdj0( 滑り易い ) // (adj) greasy/slimy/slippery
 KanjiAdj0( 乾きの早い ) // (adj) fast drying (clothes)
 KanjiAdj0( 寒い ) // (adj) cold (e.g., weather)/(P)
 KanjiAdj0( 勘定高い ) // (adj) calculating/mercenary/closefisted
 KanjiAdj0( 堪え難い ) // (adj) unbearable/intolerable/unendurable
 KanjiAdj0( 堪らない ) // (adj,exp) (1) intolerable/unbearable/unendurable/(2) cannot help (doing)/cannot but do/anxious to do/(3) tremendous/out of this world/irresistible/(P)
 KanjiAdj0( 姦しい ) // (adj) (1) noisy/boisterous
 KanjiAdj0( 寛い ) // (adj) broadminded
 KanjiAdj0( 敢えない ) // (adj) tragic/tragically
 KanjiAdj0( 敢え無い ) // (adj) tragic/tragically
 KanjiAdj0( 汗臭い ) // (adj) smell(ing) of sweat
 KanjiAdj0( 甘い ) // (adj) (1) delicious/appetizing/appetising/(2) skillful/clever/expert/wise/successful/(3) fortunate/splendid/promising
 KanjiAdj0( 甘ずっぱい ) // (adj) sweet and sour/bittersweet
 KanjiAdj0( 甘ったるい ) // (adj) sentimental/mushy
 KanjiAdj0( 甘っちょろい ) // (adj) optimistic
 KanjiAdj0( 甘酸っぱい ) // (adj) sweet and sour/bittersweet
 KanjiAdj0( 甘辛い ) // (adj) salty-sweet/bittersweet
 KanjiAdj0( 緩い ) // (adj) loose/lenient/slow/(P)
 KanjiAdj0( 間が良い ) // (adj) be lucky
 KanjiAdj0( 間近い ) // (adj) near at hand
 KanjiAdj0( 間尺に合わない ) // (adj) does not pay/not worth (one's) while
 KanjiAdj0( 丸い ) // (adj) round/circular/spherical/(P)
 KanjiAdj0( 丸っこい ) // (adj) round/spherical/circular
 KanjiAdj0( 丸で成ってない ) // (adj) not good at all
 KanjiAdj0( 含まれない ) // (adj) not to be included
 KanjiAdj0( 眼中にない ) // (adj) think nothing of
 KanjiAdj0( 頑是ない ) // (adj) innocent/helpless
 KanjiAdj0( 頑是無い ) // (adj) innocent/helpless
 KanjiAdj0( 願わしい ) // (adj) desirable
 KanjiAdj0( 危うい ) // (adj) dangerous/critical/grave/uncertain/unreliable/limping/narrow/close/watch out!/(P)
 KanjiAdj0( 危ない ) // (adj) dangerous/critical/grave/uncertain/unreliable/limping/narrow/close/watch out!/(P)
 KanjiAdj0( 危なげない ) // (adj) safe/certain
 KanjiAdj0( 危なっかしい ) // (adj) dangerous/critical/grave/uncertain/unreliable/limping/narrow/close/watch out
 KanjiAdj0( 危険を厭わない ) // (adj) do not mind running a risk
 KanjiAdj0( 喜ばしい ) // (adj) delightful/joyous/happy/(P)
 KanjiAdj0( 嬉しい ) // (adj) happy/glad/pleasant/(P)
 KanjiAdj0( 寄せ付けない ) // (adj) keep away/keep off
 KanjiAdj0( 忌々しい ) // (adj) annoying/provoking
 KanjiAdj0( 忌まわしい ) // (adj) abominable/(P)
 KanjiAdj0( 忌ま忌ましい ) // (adj) annoying/provoking
 KanjiAdj0( 忌忌しい ) // (adj) annoying/provoking
 KanjiAdj0( 気がいい ) // (adj) good-natured
 KanjiAdj0( 気が向かない ) // (adj) be not inclined (to do)
 KanjiAdj0( 気が荒い ) // (adj) bad-tempered/quarrelsome
 KanjiAdj0( 気が若い ) // (adj) young at heart
 KanjiAdj0( 気が重い ) // (adj) depressed/bummed out/heavy-hearted/heavy-spirited
 KanjiAdj0( 気が小さい ) // (adj) timid/faint-hearted/wimpish
 KanjiAdj0( 気が早い ) // (adj) short-tempered/quick-tempered/hasty
 KanjiAdj0( 気が多い ) // (adj) fickle
 KanjiAdj0( 気が大きい ) // (adj) generous/big-hearted
 KanjiAdj0( 気が短い ) // (adj) quick-tempered/having little patience/impatient
 KanjiAdj0( 気が長い ) // (adj) patient/having a long fuse
 KanjiAdj0( 気だるい ) // (adj) languid/listless
 KanjiAdj0( 気に食わない ) // (adj) unable to stomach/sticking in one's throat
 KanjiAdj0( 気のない ) // (adj) indifferent/half-hearted/dispirited
 KanjiAdj0( 気まずい ) // (adj) (uk) unpleasant/awkward
 KanjiAdj0( 気安い ) // (adj) relaxed/familiar/easy to access/friendly
 KanjiAdj0( 気強い ) // (adj) reassuring/stouthearted
 KanjiAdj0( 気軽い ) // (adj) cheerful/buoyant/lighthearted
 KanjiAdj0( 気遣わしい ) // (adj) anxiously/with anxious looks/with anxiety
 KanjiAdj0( 気高い ) // (adj) sublime
 KanjiAdj0( 気持ちいい ) // (adj) good feeling/feeling good
 KanjiAdj0( 気持ちよい ) // (adj) good feeling/feeling good
 KanjiAdj0( 気持ち悪い ) // (adj) bad feeling/feeling bad
 KanjiAdj0( 気乗りしない ) // (adj) indisposed/halfhearted
 KanjiAdj0( 気怠い ) // (adj) languid/listless
 KanjiAdj0( 気恥しい ) // (adj) embarrassed/feeling ashamed or awkward
 KanjiAdj0( 気恥ずかしい ) // (adj) embarrassed/feeling ashamed or awkward
 KanjiAdj0( 気難しい ) // (adj) hard to please/moody/crusty/fastidious
 KanjiAdj0( 気不味い ) // (adj) (uk) unpleasant/awkward
 KanjiAdj0( 気分が良い ) // (adj) feel good (pleasant)
 KanjiAdj0( 気忙しい ) // (adj) restless/fidgety/fussy
 KanjiAdj0( 規則正い ) // (adj) regular/well-regulated/systematic
 KanjiAdj0( 規則正しい ) // (adj) regular/well-regulated/systematic
 KanjiAdj0( 貴い ) // (adj) precious/valuable/priceless/noble/exalted/sacred/(P)
 KanjiAdj0( 輝かしい ) // (adj) brilliant/glorious/glittering/(P)
 KanjiAdj0( 宜しい ) // (adj) (hon) good/OK/all right/fine/very well/will do/may/can/(P)
 KanjiAdj0( 疑い深い ) // (adj) doubting/distrustful/incredulous/suspicious
 KanjiAdj0( 疑わしい ) // (adj) doubtful/questionable/uncertain/disputable/suspicious/(P)
 KanjiAdj0( 義理堅い ) // (adj) possessed of a strong sense of duty
 KanjiAdj0( 詰まらない ) // (adj) (1) (uk) dull/uninteresting/boring/(2) insignificant/trifling
 KanjiAdj0( 詰らない ) // (adj) (1) (uk) dull/uninteresting/boring/(2) insignificant/trifling/(P)
 KanjiAdj0( 久しい ) // (adj) long/long-continued/old (story)/(P)
 KanjiAdj0( 及び難い ) // (adj) hard to attain to
 KanjiAdj0( 窮まりない ) // (adj) extremely/in the extreme/boundless/limitless
 KanjiAdj0( 窮まり無い ) // (adj) extremely/in the extreme/boundless/limitless
 KanjiAdj0( 居もしない ) // (adj) (1) (uk) invisible/unseen/(2) vague/mysterious/(3) imaginary
 KanjiAdj0( 居心地が悪い ) // (adj) uncomfortable/ill at ease/not feel at home
 KanjiAdj0( 巨い ) // (adj) big/large/great
 KanjiAdj0( 虚しい ) // (adj) vacant/futile/vain/void/empty/ineffective/lifeless
 KanjiAdj0( 強い ) // (adj) strong/powerful/mighty/potent/(P)
 KanjiAdj0( 恐い ) // (adj) scary/frightening/eerie/dreadful
 KanjiAdj0( 恐れ多い ) // (adj) awesome/awe-inspiring/august
 KanjiAdj0( 恐ろしい ) // (adj) terrible/dreadful/(P)
 KanjiAdj0( 恭しい ) // (adj) respectful/reverent
 KanjiAdj0( 狂おしい ) // (adj) crazy about/maddening
 KanjiAdj0( 狂しい ) // (adj) crazy about/maddening
 KanjiAdj0( 狭い ) // (adj) narrow/confined/small/(P)
 KanjiAdj0( 狭苦しい ) // (adj) cramped
 KanjiAdj0( 胸苦しい ) // (adj) (feeling of) tightness in the chest
 KanjiAdj0( 胸糞が悪い ) // (adj) annoying
 KanjiAdj0( 興味が薄い ) // (adj) uninteresting
 KanjiAdj0( 興味深い ) // (adj) very interesting/of great interest/(P)
 KanjiAdj0( 仰々しい ) // (adj) exaggerated/bombastic/highly colored/highly coloured
 KanjiAdj0( 仰仰しい ) // (adj) exaggerated/bombastic/highly colored/highly coloured
 KanjiAdj0( 業が深い ) // (adj) be past redemption/be sinful
 KanjiAdj0( 曲々しい ) // (adj) (1) (uk) ominous/sinister/unlucky/ill-omened/(2) annoying/(3) appearing to be true
 KanjiAdj0( 曲が曲がしい ) // (adj) (1) (uk) ominous/sinister/unlucky/ill-omened/(2) annoying/(3) appearing to be true
 KanjiAdj0( 曲げ易い ) // (adj) pliant/supple/flexible
 KanjiAdj0( 曲のない ) // (adj) uninteresting/dull
 KanjiAdj0( 曲の無い ) // (adj) uninteresting/dull
 KanjiAdj0( 曲曲しい ) // (adj) (1) (uk) ominous/sinister/unlucky/ill-omened/(2) annoying/(3) appearing to be true
 KanjiAdj0( 極まりない ) // (adj) extremely/in the extreme/boundless/limitless
 KanjiAdj0( 極まり悪い ) // (adj) bashful
 KanjiAdj0( 極まり無い ) // (adj) extremely/in the extreme/boundless/limitless
 KanjiAdj0( 勤まらない ) // (adj) unfit for/unequal to
 KanjiAdj0( 均しい ) // (adj) equal/similar/like/equivalent
 KanjiAdj0( 筋違い ) // (adj-na,n) cramp/sprain/illogical/intersection/(P)
 KanjiAdj0( 近い ) // (adj,suf) near/close by/short/(P)
 KanjiAdj0( 近しい ) // (adj) intimate/close
 KanjiAdj0( 金食い ) // (adj) money-eating/expensive/extravagant
 KanjiAdj0( 金銭に細かい ) // (adj) skimpy about money
 KanjiAdj0( 苦々しい ) // (adj) unpleasant/disgusting/loathsome/shameful/scandalous
 KanjiAdj0( 苦い ) // (adj) bitter/(P)
 KanjiAdj0( 苦しい ) // (adj) painful/difficult/(P)
 KanjiAdj0( 苦苦しい ) // (adj) unpleasant/disgusting/loathsome/shameful/scandalous
 KanjiAdj0( 愚かしい ) // (adj) foolish/stupid
 KanjiAdj0( 空々しい ) // (adj) false/hypocritical
 KanjiAdj0( 空しい ) // (adj) vacant/futile/vain/void/empty/ineffective/lifeless/(P)
 KanjiAdj0( 空恐ろしい ) // (adj) having vague fears
 KanjiAdj0( 空空しい ) // (adj) false/hypocritical
 KanjiAdj0( 空高い ) // (adj) high in the sky
 KanjiAdj0( 空恥ずかしい ) // (adj) feeling ashamed or embarrassed without knowing why
 KanjiAdj0( 隅に置けない ) // (adj) be witty and knowing
 KanjiAdj0( 屈託のない ) // (adj) carefree/free from worry
 KanjiAdj0( 屈託の無い ) // (adj) carefree/free from worry
 KanjiAdj0( 卦体糞悪い ) // (adj) (vulg) extremely vexing
 KanjiAdj0( 経験が浅い ) // (adj) having little experience
 KanjiAdj0( 計り知れない ) // (adj,exp) unfathomable/inestimable/immeasurable/(P)
 KanjiAdj0( 計算高い ) // (adj) calculating
 KanjiAdj0( 軽々しい ) // (adj) indiscreet/thoughtless/careless/frivolous
 KanjiAdj0( 軽い ) // (adj) light/non-serious/minor/(P)
 KanjiAdj0( 軽軽しい ) // (adj) indiscreet/thoughtless/careless/frivolous
 KanjiAdj0( 劇しい ) // (adj) violent/vehement/intense/furious/tempestuous
 KanjiAdj0( 激しい ) // (adj) violent/vehement/intense/furious/tempestuous/(P)
 KanjiAdj0( 桁違い ) // (adj-na,n) off by a digit/in a different league/incomparable
 KanjiAdj0( 決まり悪い ) // (adj) feeling awkward/being ashamed
 KanjiAdj0( 決意が固い ) // (adj) be firmly determined
 KanjiAdj0( 潔い ) // (adj) manly/sportsmanlike/pure/upright/(P)
 KanjiAdj0( 潔しとしない ) // (adj) find it against one's conscience (to do)/be too proud (to do)
 KanjiAdj0( 血なまぐさい ) // (adj) bloody/bloody stench
 KanjiAdj0( 血生臭い ) // (adj) bloody/bloody stench
 KanjiAdj0( 倹しい ) // (adj) thrifty/economical
 KanjiAdj0( 健康に良い ) // (adj) be good for the health
 KanjiAdj0( 喧しい ) // (adj) (1) noisy/boisterous/(adj) (2) strict/faultfinding/carping/fussy/(P)
 KanjiAdj0( 喧嘩早い ) // (adj) quarrelsome
 KanjiAdj0( 堅い ) // (adj) (1) hard (esp. wood)/solid/tough/(2) stiff/tight/(3) strong/firm (not viscous or easily moved)/(4) safe/steady/honest/steadfast/(5) obstinate/stubborn/(6) bookish/formal/stuffy/(P)
 KanjiAdj0( 堅苦しい ) // (adj) formal/strict/ceremonious/stiff
 KanjiAdj0( 嫌い ) // (adj-na,n) (1) dislike/hate/(2) (suff) suspicion/tendency/smack (of)/(P)
 KanjiAdj0( 嫌らしい ) // (adj) unpleasant/disgusting/repulsive/detestable/disagreeable/indecent/lewd/dirty/lascivious
 KanjiAdj0( 肩身が狭い ) // (adj) feeling ashamed
 KanjiAdj0( 見すぼらしい ) // (adj) shabby/seedy
 KanjiAdj0( 見っともない ) // (adj) (uk) shameful/indecent/(P)
 KanjiAdj0( 見悪い ) // (adj) hard to see
 KanjiAdj0( 見易い ) // (adj) easy to see
 KanjiAdj0( 見苦しい ) // (adj) unsightly/ugly/(P)
 KanjiAdj0( 見好い ) // (adj) pleasant to look at/easy to see
 KanjiAdj0( 見窄らしい ) // (adj) shabby/seedy/(P)
 KanjiAdj0( 見当たらない ) // (adj) not be found/(P)
 KanjiAdj0( 見当違い ) // (adj-na,n) wrong (guess or estimate)/misdirected
 KanjiAdj0( 見目良い ) // (adj) good-looking
 KanjiAdj0( 見目麗しい ) // (adj) good-looking/fair/beautiful
 KanjiAdj0( 賢い ) // (adj) wise/clever/smart/(P)
 KanjiAdj0( 遣り切れない ) // (adj) intolerable/unbearable
 KanjiAdj0( 遣る瀬ない ) // (adj) helpless/cheerless/miserable/disconsolate/dreary/downhearted
 KanjiAdj0( 遣る瀬無い ) // (adj) helpless/cheerless/miserable/disconsolate/dreary/downhearted
 KanjiAdj0( 険しい ) // (adj) inaccessible place/impregnable position/steep place/sharp eyes/(P)
 KanjiAdj0( 厳い ) // (adj) grim/stern
 KanjiAdj0( 厳しい ) // (adj) (1) severe/strict/rigid/unsparing/relentless/(2) stern/austere/grave/solemn/majestic/(3) intense (cold)
 KanjiAdj0( 厳つい ) // (adj) grim/stern
 KanjiAdj0( 厳めしい ) // (adj) (1) severe/strict/rigid/unsparing/relentless/(2) stern/austere/grave/solemn/majestic/(3) intense (cold)
 KanjiAdj0( 言いづらい ) // (adj) difficult to speak about
 KanjiAdj0( 言い辛い ) // (adj) difficult to speak about
 KanjiAdj0( 言い難い ) // (adj) hard to say/inexpressible/hesitant to say
 KanjiAdj0( 言い訳が立たない ) // (adj) admit no excuse
 KanjiAdj0( 言うまでもない ) // (adj,exp) it goes without saying/there is no need to say so, but of course/it is needless to say/it need scarcely be said/(P)
 KanjiAdj0( 言う迄もない ) // (adj,exp) it goes without saying/there is no need to say so, but of course/it is needless to say/it need scarcely be said
 KanjiAdj0( 言う迄も無い ) // (adj,exp) it goes without saying/there is no need to say so, but of course/it is needless to say/it need scarcely be said
 KanjiAdj0( 言辛い ) // (adj) difficult to speak about
 KanjiAdj0( 言難い ) // (adj) hard to say/inexpressible/hesitant to say
 KanjiAdj0( 言訳が立たない ) // (adj) admit no excuse
 KanjiAdj0( 言葉に表せない ) // (adj) ineffable/inexpressible
 KanjiAdj0( 限りない ) // (adj) eternal/unlimited/endless/(P)
 KanjiAdj0( 限り無い ) // (adj) eternal/unlimited/endless
 KanjiAdj0( 古い ) // (adj) old (not person)/aged/ancient/antiquated/stale/threadbare/outmoded/obsolete article/(P)
 KanjiAdj0( 古めかしい ) // (adj) old-fashioned
 KanjiAdj0( 古臭い ) // (adj) stale/old fashioned/hackneyed/trite/(P)
 KanjiAdj0( 固い ) // (adj) (1) hard (esp. wood)/solid/tough/(2) stiff/tight/(3) strong/firm (not viscous or easily moved)/(4) safe/steady/honest/steadfast/(5) obstinate/stubborn/(6) bookish/formal/stuffy/(P)
 KanjiAdj0( 固苦しい ) // (adj) formal/strict/ceremonious/stiff
 KanjiAdj0( 胡散臭い ) // (adj) suspicious looking/shady
 KanjiAdj0( 誇らしい ) // (adj) proud/haughty/arrogant/splendid/magnificent
 KanjiAdj0( 誇り高い ) // (adj) proud/lordly
 KanjiAdj0( 五月蝿い ) // (ateji) (adj) (1) noisy/loud/(2) fussy/(3) annoying/troublesome/tiresome/importunate/(4) bossy
 KanjiAdj0( 五月蠅い ) // (ateji) (adj) (1) noisy/loud/(2) fussy/(3) annoying/troublesome/tiresome/importunate/(4) bossy
 KanjiAdj0( 互い違い ) // (adj-na,n) alternate/alternation/(P)
 KanjiAdj0( 後ろめたい ) // (adj) guilty
 KanjiAdj0( 後ろ暗い ) // (adj) shady/back or underhanded
 KanjiAdj0( 御寒い ) // (adj) poor/unsatisfactory/inadequate
 KanjiAdj0( 御機嫌麗しい ) // (adj) be in good humor (humour)
 KanjiAdj0( 御高い ) // (adj) haughty
 KanjiAdj0( 交際嫌い ) // (adj) unsociable
 KanjiAdj0( 厚い ) // (adj) cordial/kind/warm(hearted)/thick/deep/(P)
 KanjiAdj0( 厚かましい ) // (adj) impudent/shameless/brazen/(P)
 KanjiAdj0( 厚ぼったい ) // (adj) very thick/heavy
 KanjiAdj0( 口うるさい ) // (adj) nagging/faultfinding/carping/captious
 KanjiAdj0( 口がうまい ) // (adj) honeymouthed/glib/fair-spoken/cajoling/talking glibly
 KanjiAdj0( 口がない ) // (adj) being unable to find a job
 KanjiAdj0( 口が悪い ) // (adj) sarcastic/having a sharp (nasty) tongue
 KanjiAdj0( 口が軽い ) // (adj) having a loose tongue/being talkative
 KanjiAdj0( 口が巧い ) // (adj) honeymouthed/glib/fair-spoken/cajoling/talking glibly
 KanjiAdj0( 口が重い ) // (adj) incommunicative/taciturn
 KanjiAdj0( 口が上手い ) // (adj) honeymouthed/glib/fair-spoken/cajoling/talking glibly
 KanjiAdj0( 口が多い ) // (adj) having a large family to support
 KanjiAdj0( 口が無い ) // (adj) being unable to find a job
 KanjiAdj0( 口さがない ) // (adj) gossipy/abusive/critical/jabbering
 KanjiAdj0( 口やかましい ) // (adj) nagging/talkative/gossipy
 KanjiAdj0( 口汚い ) // (adj) foul-mouthed/abusive
 KanjiAdj0( 口喧しい ) // (adj) nagging/talkative/gossipy
 KanjiAdj0( 口堅い ) // (adj) discreet/tight-lipped
 KanjiAdj0( 口寂しい ) // (adj) longing to have or put something in one's mouth
 KanjiAdj0( 口重い ) // (adj) slow of speech/prudent
 KanjiAdj0( 口性ない ) // (adj) gossipy/abusive/critical/jabbering
 KanjiAdj0( 口性無い ) // (adj) gossipy/abusive/critical/jabbering
 KanjiAdj0( 口惜しい ) // (adj) regrettable/mortifying/vexing
 KanjiAdj0( 口煩い ) // (adj) nagging/faultfinding/carping/captious
 KanjiAdj0( 口煩さい ) // (adj) nagging/faultfinding/carping/captious
 KanjiAdj0( 口幅ったい ) // (adj) bragging/impudence
 KanjiAdj0( 向い ) // (io) (n,adj-no) facing/opposite/across the street/other side/(P)
 KanjiAdj0( 向かい ) // (n,adj-no) facing/opposite/across the street/other side/(P)
 KanjiAdj0( 好い ) // (adj) (uk) good/nice/pleasant/fine/excellent/agreeable/ok
 KanjiAdj0( 好ましい ) // (adj) nice/likeable/desirable/(P)
 KanjiAdj0( 巧い ) // (adj) skillful
 KanjiAdj0( 幸い ) // (adj-na,adv,n) happiness/blessedness/(P)
 KanjiAdj0( 広い ) // (adj) spacious/vast/wide/(P)
 KanjiAdj0( 弘い ) // (adj) spacious/vast/wide
 KanjiAdj0( 慌しい ) // (adj) busy/hurried/confused/flurried
 KanjiAdj0( 慌ただしい ) // (adj) busy/hurried/confused/flurried/(P)
 KanjiAdj0( 更々ない ) // (adj) not in the least
 KanjiAdj0( 更更ない ) // (adj) not in the least
 KanjiAdj0( 構わない ) // (adj) be indifferent (to)/do not care (mind)
 KanjiAdj0( 甲高い ) // (adj) high-pitched/shrill/(P)
 KanjiAdj0( 甲斐がない ) // (adj) useless/in vain
 KanjiAdj0( 甲斐が無い ) // (adj) useless/in vain
 KanjiAdj0( 甲斐甲斐しい ) // (adj) gallant/heroic/brave
 KanjiAdj0( 硬い ) // (adj) (1) solid/hard (esp. metal, stone)/(2) unpolished (writing)/(P)
 KanjiAdj0( 糠味噌臭い ) // (adj) overly concerned with domestic affairs
 KanjiAdj0( 考えられない ) // (adj) unimaginable
 KanjiAdj0( 考え深い ) // (adj) thoughtful/deep-thinking
 KanjiAdj0( 荒々しい ) // (adj) desolate/rough/wild/rude/harsh/gruff/violent/(P)
 KanjiAdj0( 荒い ) // (adj) rough/rude/wild/(P)
 KanjiAdj0( 荒っぽい ) // (adj) rough/rude/(P)
 KanjiAdj0( 荒荒しい ) // (adj) desolate/rough/wild/rude/harsh/gruff/violent
 KanjiAdj0( 行きたくない ) // (adj) do not want to go
 KanjiAdj0( 行きたく無い ) // (adj) do not want to go
 KanjiAdj0( 香しい ) // (adj) (uk) sweet-smelling/scentful/fragrant
 KanjiAdj0( 香ばしい ) // (adj) sweet/fragrant/aromatic/savory/savoury/(P)
 KanjiAdj0( 高い ) // (adj) (1) high/tall/(2) expensive/(P)
 KanjiAdj0( 豪い ) // (adj) great/celebrated/eminent/terrible/awful/famous/remarkable/excellent
 KanjiAdj0( 酷い ) // (adj) (uk) cruel/awful/severe/very bad/serious/terrible/heavy/violent/(P)
 KanjiAdj0( 酷しい ) // (adj) (1) severe/strict/rigid/unsparing/relentless/(2) stern/austere/grave/solemn/majestic/(3) intense (cold)
 KanjiAdj0( 黒い ) // (adj) (1) black/(2) dark/(P)
 KanjiAdj0( 黒っぽい ) // (adj) dark/blackish/(P)
 KanjiAdj0( 骨っぽい ) // (adj) bony/tough/plucky/spirited/hard to deal with
 KanjiAdj0( 今めかしい ) // (adj) fashionable
 KanjiAdj0( 恨めしい ) // (adj) reproachful/hateful/bitter
 KanjiAdj0( 根拠のない ) // (adj) baseless/groundless
 KanjiAdj0( 根強い ) // (adj) firmly rooted/deep-seated/(P)
 KanjiAdj0( 根深い ) // (adj) deep-rooted/ingrained
 KanjiAdj0( 差し向かい ) // (adj) face to face
 KanjiAdj0( 差し出がましい ) // (adj) forward/officious/impertinent/intrusive
 KanjiAdj0( 差し障りのない ) // (adj) innocuous/inoffensive
 KanjiAdj0( 差向い ) // (adj) face to face
 KanjiAdj0( 差向かい ) // (adj) face to face
 KanjiAdj0( 済まない ) // (adj,exp) sorry (phrase)/(P)
 KanjiAdj0( 細い ) // (adj) thin/slender/fine/(P)
 KanjiAdj0( 細かい ) // (adj) (1) small/(2) fine/minute/(P)
 KanjiAdj0( 細長い ) // (adj) long and narrow/(P)
 KanjiAdj0( 際どい ) // (adj) dangerous/risky/hazardous/close/delicate/suggestive
 KanjiAdj0( 際疾い ) // (adj) dangerous/risky/hazardous/close/delicate/suggestive
 KanjiAdj0( 罪のない ) // (adj) guiltless/innocent
 KanjiAdj0( 罪の無い ) // (adj) guiltless/innocent
 KanjiAdj0( 罪深い ) // (adj) sinful
 KanjiAdj0( 惨い ) // (adj) cruel/atrocious/merciless/inhuman/brutal
 KanjiAdj0( 算盤高い ) // (adj) calculating/miserly
 KanjiAdj0( 酸い ) // (adj) sour/acid
 KanjiAdj0( 酸っぱい ) // (adj) sour/acid/(P)
 KanjiAdj0( 残り惜しい ) // (adj) regrettable/reluctant
 KanjiAdj0( 仕兼ねない ) // (adj) capable of anything
 KanjiAdj0( 仕切れない ) // (adj) impossible to do
 KanjiAdj0( 仕方がない ) // (adj,exp) it can't be helped/it's inevitable/it's no use/can't stand it/being impatient/being annoyed/(P)
 KanjiAdj0( 仕方が無い ) // (adj,exp) it can't be helped/it's inevitable/it's no use/can't stand it/being impatient/being annoyed
 KanjiAdj0( 仕方ない ) // (adj) it can't be helped/it's inevitable/it's no use/can't stand it/impatient/annoyed
 KanjiAdj0( 仕方無い ) // (adj) it can't be helped/it's inevitable/it's no use/can't stand it/impatient/annoyed
 KanjiAdj0( 仕様のない ) // (adj) hopeless/good-for-nothing/incorrigible
 KanjiAdj0( 仕様の無い ) // (adj) hopeless/good-for-nothing/incorrigible
 KanjiAdj0( 使いやすい ) // (adj) (uk) easy to use
 KanjiAdj0( 使い易い ) // (adj) (uk) easy to use
 KanjiAdj0( 使い物にならない ) // (adj) be no use
 KanjiAdj0( 刺々しい ) // (adj) sharp/harsh/stinging/thorny/snappy
 KanjiAdj0( 刺刺しい ) // (adj) sharp/harsh/stinging/thorny/snappy
 KanjiAdj0( 史上に例を見ない ) // (adj) be unparalleled in history (unparallelled)
 KanjiAdj0( 四角い ) // (adj) square/(P)
 KanjiAdj0( 思いがけない ) // (adj) unexpected/contrary to unexpectations/by chance/casual/(P)
 KanjiAdj0( 思いも寄らない ) // (adj) unexpected/unforeseen/inconceivable
 KanjiAdj0( 思い掛けない ) // (adj) unexpected/contrary to unexpectations/by chance/casual
 KanjiAdj0( 思い掛け無い ) // (adj) unexpected/contrary to unexpectations/by chance/casual
 KanjiAdj0( 思しい ) // (adj) apparently
 KanjiAdj0( 思わしい ) // (adj) suitable/satisfactory/desirable
 KanjiAdj0( 思わしくない ) // (adj) disappointing/unsatisfactory/unsuitable
 KanjiAdj0( 思想が固まっていない ) // (adj) have no fixed ideas
 KanjiAdj0( 旨い ) // (adj) (1) delicious/appetizing/appetising/(2) skillful/clever/expert/wise/successful/(3) fortunate/splendid/promising
 KanjiAdj0( 旨く行かない ) // (adj) be unsuccessful/go badly
 KanjiAdj0( 止み難い ) // (adj) irresistible
 KanjiAdj0( 止めどない ) // (adj) endless/ceaseless
 KanjiAdj0( 止め処無い ) // (adj) endless/ceaseless
 KanjiAdj0( 止ん事無い ) // (adj) (uk) high class/esteemed/cherished
 KanjiAdj0( 脂っこい ) // (adj) (uk) greasy/fatty/oily
 KanjiAdj0( 脂っ濃い ) // (adj) (uk) greasy/fatty/oily
 KanjiAdj0( 脂濃い ) // (adj) (uk) greasy/fatty/oily
 KanjiAdj0( 至らない ) // (adj) imperfect/incompetent
 KanjiAdj0( 歯がゆい ) // (adj) impatient/tantalized/tantalised/irritated/chagrined/chagrinned/vexed
 KanjiAdj0( 歯が立たない ) // (adj) hard to chew/unable to compete with
 KanjiAdj0( 歯に衣を着せない ) // (adj) not mince matters
 KanjiAdj0( 歯牙に掛けない ) // (adj) no argument necessary
 KanjiAdj0( 歯痒い ) // (adj) impatient/tantalized/tantalised/irritated/chagrined/chagrinned/vexed/(P)
 KanjiAdj0( 事々しい ) // (adj) bombastic/pretentious/exaggerated
 KanjiAdj0( 事欠かない ) // (adj) having an abundance
 KanjiAdj0( 事事しい ) // (adj) bombastic/pretentious/exaggerated
 KanjiAdj0( 事新しい ) // (adj) new
 KanjiAdj0( 似つかわしい ) // (adj) suitable/appropriate/becoming
 KanjiAdj0( 似気ない ) // (adj) unlike/unbecoming/unworthy of/out of keeping with
 KanjiAdj0( 似気無い ) // (adj) unlike/unbecoming/unworthy of/out of keeping with
 KanjiAdj0( 似合い ) // (n,adj-no) well-matched/becoming/suitable/(P)
 KanjiAdj0( 似合わしい ) // (adj) well-matched/suitable/becoming
 KanjiAdj0( 似付かわしい ) // (adj) suitable/appropriate/becoming
 KanjiAdj0( 持って来い ) // (adj-na,exp) just right/ideal/perfectly suitable
 KanjiAdj0( 耳遠い ) // (adj) (1) hard of hearing/(2) unfamiliar
 KanjiAdj0( 耳新しい ) // (adj) novel/new/unfamiliar/hear for the first time
 KanjiAdj0( 耳聡い ) // (adj) sharp-eared/have sharp ears/picks things up fast
 KanjiAdj0( 鹿爪らしい ) // (adj) formal/solemn
 KanjiAdj0( 執念深い ) // (adj) vindictive/tenacious/persistent/spiteful/vengeful
 KanjiAdj0( 嫉妬深い ) // (adj) deep jealousy
 KanjiAdj0( 湿っぽい ) // (adj) damp/gloomy/(P)
 KanjiAdj0( 実らしい ) // (adj) honest (appearance)/sincere (impression)
 KanjiAdj0( 煮え切らない ) // (adj,exp) half-cooked/vague/halfhearted/indecisive
 KanjiAdj0( 邪魔臭い ) // (adj,exp) troublesome/pain in the butt
 KanjiAdj0( 若々しい ) // (adj) youthful/young/(P)
 KanjiAdj0( 若い ) // (adj) young/(P)
 KanjiAdj0( 若若しい ) // (adj) youthful/young
 KanjiAdj0( 寂しい ) // (adj) lonely/lonesome/solitary/desolate
 KanjiAdj0( 弱々しい ) // (adj) frail/slender/feminine
 KanjiAdj0( 弱い ) // (adj) weak/frail/delicate/tender/unskilled/weak (wine)/(P)
 KanjiAdj0( 弱弱しい ) // (adj) frail/slender/feminine
 KanjiAdj0( 弱保合い ) // (adj) (stock market) barely holding steady
 KanjiAdj0( 取り止めのない ) // (adj) incoherent/wandering/vague/rambling/whimsical
 KanjiAdj0( 取り止めの無い ) // (adj) incoherent/wandering/vague/rambling/whimsical
 KanjiAdj0( 取り留めのない ) // (adj) incoherent/wandering/vague/rambling/whimsical
 KanjiAdj0( 取り留めの無い ) // (adj) incoherent/wandering/vague/rambling/whimsical
 KanjiAdj0( 手が足りない ) // (adj) be short of hands
 KanjiAdj0( 手ごわい ) // (adj) difficult/tough/stubborn/redoubtable/(P)
 KanjiAdj0( 手っ取り早い ) // (adj) quick (and easy)/finishing up in a hurry
 KanjiAdj0( 手づよい ) // (adj) strong/resolute/firm/strict
 KanjiAdj0( 手緩い ) // (adj) lax/lenient/slow
 KanjiAdj0( 手強い ) // (adj) strong/resolute/firm/strict
 KanjiAdj0( 手堅い ) // (adj) steady/firm/solid/secure/(P)
 KanjiAdj0( 手厳しい ) // (adj) severe/harsh
 KanjiAdj0( 手厚い ) // (adj) courteous
 KanjiAdj0( 手広い ) // (adj) spacious/roomy
 KanjiAdj0( 手酷い ) // (adj) severe/harsh
 KanjiAdj0( 手早い ) // (adj) nimble/(P)
 KanjiAdj0( 手短い ) // (adj) short/brief
 KanjiAdj0( 手痛い ) // (adj) severe/hard/(P)
 KanjiAdj0( 手縫い ) // (n,adj-no) hand-tailored/hand-sewn
 KanjiAdj0( 酒臭い ) // (adj) reek of liquor
 KanjiAdj0( 受けが悪い ) // (adj) unpopular (with)/in the bad books
 KanjiAdj0( 受けが良い ) // (adj) popular (with)
 KanjiAdj0( 臭い ) // (adj) stinking/(P)
 KanjiAdj0( 醜い ) // (adj) ugly/(P)
 KanjiAdj0( 柔らかい ) // (adj) soft/tender/limp/(P)
 KanjiAdj0( 渋い ) // (adj) (1) tasteful (clothing)/cool/an aura of refined masculinity/(2) astringent/sullen/bitter (taste)/(3) grim/quiet/(4) sober/stingy/(P)
 KanjiAdj0( 重々しい ) // (adj) frequently/sincerely/exceedingly/serious/grave/dignified
 KanjiAdj0( 重い ) // (adj) (1) heavy/massive/(2) serious/important/severe/oppressed/(P)
 KanjiAdj0( 重たい ) // (adj) heavy/massive/serious/important/severe/oppressed/(P)
 KanjiAdj0( 重苦しい ) // (adj) heavy/gloomy/awkward/cumbrous/oppressive/leaden/(P)
 KanjiAdj0( 重重しい ) // (adj) frequently/sincerely/exceedingly/serious/grave/dignified
 KanjiAdj0( 熟柿臭い ) // (adj) smelling of (stale) liquor
 KanjiAdj0( 初々しい ) // (adj) innocent/artless/unsophisticated
 KanjiAdj0( 初初しい ) // (adj) innocent/artless/unsophisticated
 KanjiAdj0( 所在ない ) // (adj) bored/having nothing to do/idle
 KanjiAdj0( 所在無い ) // (adj) bored/having nothing to do/idle
 KanjiAdj0( 暑い ) // (adj) hot/warm/(P)
 KanjiAdj0( 暑苦しい ) // (adj) sultry/sweltering
 KanjiAdj0( 書きにくい ) // (adj) be difficult to write or draw/does not write well (pen, brush, etc.)
 KanjiAdj0( 書き難い ) // (adj) be difficult to write or draw/does not write well (pen, brush, etc.)
 KanjiAdj0( 女々しい ) // (adj) effeminate
 KanjiAdj0( 女っぽい ) // (adj) womanly/feminine/womanish/effeminate
 KanjiAdj0( 女らしい ) // (adj) womanly/ladylike/feminine/(P)
 KanjiAdj0( 女王らしい ) // (adj) queen-like
 KanjiAdj0( 女女しい ) // (adj) effeminate
 KanjiAdj0( 傷々しい ) // (adj) pitiful/pathetic
 KanjiAdj0( 傷ましい ) // (adj) pitiful/heartbreaking
 KanjiAdj0( 傷傷しい ) // (adj) pitiful/pathetic
 KanjiAdj0( 小い ) // (adj) very small (slightly pejorative)
 KanjiAdj0( 小うるさい ) // (adj) particular/hard to please/fussy
 KanjiAdj0( 小ぎれい ) // (adj-na) neat/trim/tidy/pretty
 KanjiAdj0( 小さい ) // (adj) small/little/tiny/(P)
 KanjiAdj0( 小っちゃい ) // (adj) tiny/little/wee
 KanjiAdj0( 小っ恥ずかしい ) // (adj) feeling a little (i.e. very) embarrassed/(a little) shameful
 KanjiAdj0( 小暗い ) // (adj) dusky/dim/shady
 KanjiAdj0( 小気味よい ) // (adj) smart/clever/neat/gloating
 KanjiAdj0( 小喧しい ) // (adj) nagging/fault-finding
 KanjiAdj0( 小賢しい ) // (adj) clever/shrewd/crafty/cunning/pretentious
 KanjiAdj0( 小高い ) // (adj) slightly elevated
 KanjiAdj0( 小憎らしい ) // (adj-na) provoking/horrible
 KanjiAdj0( 小恥ずかしい ) // (adj) feeling a little (i.e. very) embarrassed/(a little) shameful
 KanjiAdj0( 小難しい ) // (adj) troublesome/fastidious/tortuous
 KanjiAdj0( 少々足りない ) // (adj) somewhat lacking/somewhat weak in the head
 KanjiAdj0( 少い ) // (io) (adj) few/a little/scarce/insufficient/seldom
 KanjiAdj0( 少ない ) // (adj) few/a little/scarce/insufficient/seldom/(P)
 KanjiAdj0( 少少足りない ) // (adj) somewhat lacking/somewhat weak in the head
 KanjiAdj0( 床しい ) // (adj) admirable/charming/refined
 KanjiAdj0( 捷い ) // (adj) (1) (uk) smart/clever/(2) agile/nimble/quick
 KanjiAdj0( 焼きの足りない ) // (adj) underfired
 KanjiAdj0( 焦げ臭い ) // (adj) smelling (or tasting) burnt
 KanjiAdj0( 焦れったい ) // (adj) (uk) vexing/irritating/impatient
 KanjiAdj0( 焦臭い ) // (adj) (1) burning or scorched smell/(2) imminent military action/(3) suspicious
 KanjiAdj0( 照れくさい ) // (adj) embarrassing/awkward
 KanjiAdj0( 照れ臭い ) // (adj) embarrassing/awkward
 KanjiAdj0( 詳しい ) // (adj) knowing very well/detailed/full/accurate/(P)
 KanjiAdj0( 詳らかでない ) // (adj) be unknown
 KanjiAdj0( 賞賛して措かない ) // (adj) applaud highly/extol
 KanjiAdj0( 上手い ) // (adj) skillful
 KanjiAdj0( 場違い ) // (adj-na,exp,n) out-of-place/inappropriate/sticking out like a sore thumb/(P)
 KanjiAdj0( 情けない ) // (adj) miserable/pitiable/shameful/deplorable/(P)
 KanjiAdj0( 情け深い ) // (adj) tender-hearted/compassionate/(P)
 KanjiAdj0( 情け無い ) // (adj) miserable/pitiable/shameful/deplorable
 KanjiAdj0( 情ない ) // (adj) miserable/pitiable/shameful/deplorable
 KanjiAdj0( 情深い ) // (adj) tender-hearted/compassionate
 KanjiAdj0( 情無い ) // (adj) miserable/pitiable/shameful/deplorable
 KanjiAdj0( 蒸し暑い ) // (adj) humid/sultry/(P)
 KanjiAdj0( 飾り気のない ) // (adj) plain/unaffected
 KanjiAdj0( 飾り気の無い ) // (adj) plain/unaffected
 KanjiAdj0( 色っぽい ) // (adj) amorous/sexy/voluptuous/erotic
 KanjiAdj0( 色好い ) // (adj-pn) favorable/favourable/friendly/encouraging
 KanjiAdj0( 色濃い ) // (adj) marked/pronounced/strongly tending to
 KanjiAdj0( 色良い ) // (adj-pn) favorable/favourable/friendly/encouraging
 KanjiAdj0( 食い足りない ) // (adj) not eating enough
 KanjiAdj0( 食えない ) // (adj,exp) shrewd/smart (and wide-awake)/cunning/crafty
 KanjiAdj0( 食べず嫌い ) // (adj-na,n) disliking without even tasting
 KanjiAdj0( 信心深い ) // (adj) deeply religious/devout/godly/faithful
 KanjiAdj0( 寝汚い ) // (adj) (1) sound asleep/fast asleep/(2) untidy/slovenly
 KanjiAdj0( 寝苦しい ) // (adj) unable to sleep well/(P)
 KanjiAdj0( 寝穢い ) // (adj) (1) sound asleep/fast asleep/(2) untidy/slovenly
 KanjiAdj0( 心ない ) // (adj) thoughtless/inconsiderate/tasteless/cruel
 KanjiAdj0( 心安い ) // (adj) intimate/carefree/familiar/friendly
 KanjiAdj0( 心許ない ) // (adj) uneasy/unsure/unreliable
 KanjiAdj0( 心強い ) // (adj) heartening/reassuring/(P)
 KanjiAdj0( 心苦しい ) // (adj) painful/be or feel sorry
 KanjiAdj0( 心細い ) // (adj) helpless/forlorn/hopeless/unpromising/lonely/discouraging/disheartening/(P)
 KanjiAdj0( 心寂しい ) // (adj) lonely/lonesome
 KanjiAdj0( 心憎い ) // (adj) refined/admirable/superb
 KanjiAdj0( 心地よい ) // (adj) comfortable/pleasant
 KanjiAdj0( 心地好い ) // (adj) comfortable/pleasant
 KanjiAdj0( 心地良い ) // (adj) comfortable/pleasant
 KanjiAdj0( 心恥かしい ) // (adj) slightly ashamed/rather shy
 KanjiAdj0( 心得難い ) // (adj) hard to understand or accept
 KanjiAdj0( 心悲しい ) // (adj) sad/mournful/melancholy/sorrowful
 KanjiAdj0( 心忙しい ) // (adj) restless
 KanjiAdj0( 心無い ) // (adj) thoughtless/inconsiderate/tasteless/cruel
 KanjiAdj0( 心淋しい ) // (adj) lonesome/lonely/forlorn
 KanjiAdj0( 慎ましい ) // (adj) modest/reserved/quiet/humble
 KanjiAdj0( 慎み深い ) // (adj) discreet/modest/cautious
 KanjiAdj0( 振るわない ) // (adj) be in a bad way/be dull
 KanjiAdj0( 新しい ) // (adj) new/(P)
 KanjiAdj0( 深い ) // (adj) deep/profound/thick/close/(P)
 KanjiAdj0( 申し分ない ) // (adj) no objection/nothing to criticize/nothing to criticise
 KanjiAdj0( 申し分のない ) // (adj) no objection/nothing to criticize/nothing to criticise/(P)
 KanjiAdj0( 申し分の無い ) // (adj) no objection/nothing to criticize/nothing to criticise
 KanjiAdj0( 申し分無い ) // (adj) no objection/nothing to criticize/nothing to criticise/(P)
 KanjiAdj0( 申し訳ない ) // (adj) inexcusable/(P)
 KanjiAdj0( 申し訳無い ) // (adj) inexcusable
 KanjiAdj0( 申分のない ) // (adj) no objection/nothing to criticize/nothing to criticise
 KanjiAdj0( 申分の無い ) // (adj) no objection/nothing to criticize/nothing to criticise
 KanjiAdj0( 真っ黒い ) // (adj) pitch black/deep black
 KanjiAdj0( 真っ白い ) // (adj) pure white
 KanjiAdj0( 真ん円い ) // (adj) perfectly round
 KanjiAdj0( 真ん丸い ) // (adj) perfectly circular
 KanjiAdj0( 真近い ) // (adj) near at hand
 KanjiAdj0( 真新しい ) // (adj) brand new/(P)
 KanjiAdj0( 真白い ) // (adj) pure white
 KanjiAdj0( 神々しい ) // (adj) divine/sublime/solemn
 KanjiAdj0( 神神しい ) // (adj) divine/sublime/solemn
 KanjiAdj0( 親しい ) // (adj) intimate/close
 KanjiAdj0( 親しみやすい ) // (adj) friendly
 KanjiAdj0( 親しみ易い ) // (adj) friendly
 KanjiAdj0( 身じろぎもしない ) // (adj) didn't stir an inch
 KanjiAdj0( 辛い ) // (adj) painful/heart-breaking/(P)
 KanjiAdj0( 辛気臭い ) // (adj) irritating/fretful/boring
 KanjiAdj0( 辛抱強い ) // (adj) patient
 KanjiAdj0( 人に訴える力がない ) // (adj) be of little appeal to people
 KanjiAdj0( 人に訴える力が無い ) // (adj) be of little appeal to people
 KanjiAdj0( 人懐かしい ) // (adj) lonesome for
 KanjiAdj0( 人懐こい ) // (adj) friendly/affable/amiable/sociable/loving company/(animals) taking kindly to men
 KanjiAdj0( 人懐っこい ) // (adj) friendly/affable/amiable/sociable/loving company/(animals) taking kindly to men
 KanjiAdj0( 人間らしい ) // (adj) human/humane
 KanjiAdj0( 人気がない ) // (adj) no sign of life
 KanjiAdj0( 人気が無い ) // (adj) no sign of life
 KanjiAdj0( 人恋しい ) // (adj) longing for others
 KanjiAdj0( 甚だしい ) // (adj) extreme/excessive/terrible/intense/severe/serious/tremendous/heavy (damage)/(P)
 KanjiAdj0( 尽きない ) // (adj) everlasting/inexhaustible
 KanjiAdj0( 図々しい ) // (adj) impudent/shameless/(P)
 KanjiAdj0( 図図しい ) // (adj) impudent/shameless
 KanjiAdj0( 図太い ) // (adj) bold/shameless/cheeky
 KanjiAdj0( 水っぽい ) // (adj) (1) watery/soggy/(2) racy/titillating/sexy/suggestive
 KanjiAdj0( 水を通さない ) // (adj) be impervious to water
 KanjiAdj0( 水臭い ) // (adj) stand-offish/distant/not frank/reserved/watery/(P)
 KanjiAdj0( 瑞々しい ) // (adj) young and vivacious/(P)
 KanjiAdj0( 瑞瑞しい ) // (adj) young and vivacious
 KanjiAdj0( 数え切れない ) // (adj) countless/incalculable
 KanjiAdj0( 数少ない ) // (adj) few in number
 KanjiAdj0( 数多い ) // (adj) many/a multiplicity of
 KanjiAdj0( 寸が足りない ) // (adj) be too short
 KanjiAdj0( 世知辛い ) // (adj) hard (life)/tough (world)
 KanjiAdj0( 凄い ) // (adj) terrible/dreadful/terrific/amazing/great/wonderful/to a great extent/(P)
 KanjiAdj0( 凄じい ) // (io) (adj) terrific/fierce/terrible/tremendous/dreadful/awful/amazing/absurd
 KanjiAdj0( 凄まじい ) // (adj) terrific/fierce/terrible/tremendous/dreadful/awful/amazing/absurd/(P)
 KanjiAdj0( 晴れがましい ) // (adj) formal/grand/gala
 KanjiAdj0( 晴れ晴れしい ) // (adj) clear/splendid
 KanjiAdj0( 正しい ) // (adj) right/just/correct/righteous/honest/truthful/proper/straightforward/perfect/(P)
 KanjiAdj0( 清々しい ) // (adj) (uk) fresh/refreshing/(P)
 KanjiAdj0( 清い ) // (adj) clear/pure/noble/(P)
 KanjiAdj0( 清清しい ) // (adj) (uk) fresh/refreshing
 KanjiAdj0( 生々しい ) // (adj) lively/green/fresh/raw/(P)
 KanjiAdj0( 生ぬるい ) // (adj) lukewarm/halfhearted/(P)
 KanjiAdj0( 生めかしい ) // (adj) charming/captivating
 KanjiAdj0( 生易しい ) // (adj) simple/easy
 KanjiAdj0( 生温い ) // (adj) lukewarm/halfhearted
 KanjiAdj0( 生臭い ) // (adj) smelling of fish or blood/fish or meat/(P)
 KanjiAdj0( 生新しい ) // (adj) very fresh
 KanjiAdj0( 生生しい ) // (adj) lively/green/fresh/raw
 KanjiAdj0( 生暖かい ) // (adj) lukewarm/tepid
 KanjiAdj0( 生白い ) // (adj) pale
 KanjiAdj0( 青い ) // (adj) blue/pale/green/unripe/inexperienced/(P)
 KanjiAdj0( 青黒い ) // (adj) dark blue/discolored/discoloured
 KanjiAdj0( 青臭い ) // (adj) inexperienced/immature/grassy-smelling
 KanjiAdj0( 青白い ) // (adj) (1) pale/pallid/(2) blue and white/(P)
 KanjiAdj0( 斉しい ) // (adj) equal/similar/like/equivalent
 KanjiAdj0( 脆い ) // (adj) brittle/fragile/tender-hearted/(P)
 KanjiAdj0( 惜しい ) // (adj) (1) regrettable/disappointing/(2) precious/dear/valuable/(3) too good for/deserving better/(4) almost but not quite/(P)
 KanjiAdj0( 惜しまない ) // (adj) without sparing (effort, funds, etc.)/(P)
 KanjiAdj0( 赤い ) // (adj) red/(P)
 KanjiAdj0( 赤黒い ) // (adj) dark red
 KanjiAdj0( 切ない ) // (adj) painful/trying/oppressive/suffocating/(P)
 KanjiAdj0( 切らない ) // (adj) not through/not finished
 KanjiAdj0( 切ら無い ) // (adj) not through/not finished
 KanjiAdj0( 切りのない ) // (adj) endless/boundless
 KanjiAdj0( 切りの無い ) // (adj) endless/boundless
 KanjiAdj0( 切れない ) // (adj,suf) being too many or much
 KanjiAdj0( 切れ無い ) // (adj,suf) being too many or much
 KanjiAdj0( 拙い ) // (adj) clumsy/unskillful/foolish/unlucky
 KanjiAdj0( 折り目正しい ) // (adj) good manners/courteous
 KanjiAdj0( 節を曲げない ) // (adj) remain firm/stick by one's principles
 KanjiAdj0( 浅い ) // (adj) shallow/superficial/(P)
 KanjiAdj0( 浅ましい ) // (adj) wretched/miserable/shameful/mean/despicable/abject
 KanjiAdj0( 浅黒い ) // (adj) darkish/swarthy/(P)
 KanjiAdj0( 羨ましい ) // (adj) envious/enviable/(P)
 KanjiAdj0( 詮ない ) // (adj) unavoidable/no help for
 KanjiAdj0( 詮無い ) // (adj) unavoidable/no help for
 KanjiAdj0( 善い ) // (adj) (uk) good/nice/pleasant/fine/excellent/agreeable/ok
 KanjiAdj0( 然り気ない ) // (adj) (uk) nonchalant/unconcerned/in a casual manner
 KanjiAdj0( 然り気無い ) // (adj) (uk) nonchalant/unconcerned/in a casual manner
 KanjiAdj0( 疎々しい ) // (adj) unfriendly
 KanjiAdj0( 疎い ) // (adj) distant/estranged/disinterested
 KanjiAdj0( 疎ましい ) // (adj) disagreeable/unpleasant/adverse/unsympathetic
 KanjiAdj0( 疎疎しい ) // (adj) unfriendly
 KanjiAdj0( 粗い ) // (adj) coarse/rough/(P)
 KanjiAdj0( 素っ気ない ) // (adj) cold/short/curt/blunt
 KanjiAdj0( 素っ気無い ) // (adj) cold/short/curt/blunt
 KanjiAdj0( 素気ない ) // (adj) cold/short/curt/blunt
 KanjiAdj0( 素気無い ) // (adj) cold/short/curt/blunt
 KanjiAdj0( 素行が修まらない ) // (adj) be dissolute/conduct oneself loosely
 KanjiAdj0( 素人臭い ) // (adj) amateurish
 KanjiAdj0( 素晴しい ) // (io) (adj) wonderful/splendid/magnificent
 KanjiAdj0( 素晴らしい ) // (adj) wonderful/splendid/magnificent/(P)
 KanjiAdj0( 素早い ) // (adj) (1) fast/quick/prompt/(2) nimble/agile/(P)
 KanjiAdj0( 素速い ) // (adj) (1) fast/quick/prompt/(2) nimble/agile
 KanjiAdj0( 想像し難い ) // (adj) hard to imagine
 KanjiAdj0( 早い ) // (adj) early/(P)
 KanjiAdj0( 相違ない ) // (adj) without doubt/certain/sure
 KanjiAdj0( 相応しい ) // (adj) appropriate/(P)
 KanjiAdj0( 相等しい ) // (adj) equal to each other
 KanjiAdj0( 相入れない ) // (adj,exp) in conflict/incompatible/out of harmony/running counter
 KanjiAdj0( 相容れない ) // (adj,exp) in conflict/incompatible/out of harmony/running counter
 KanjiAdj0( 草深い ) // (adj) grassy/weedy
 KanjiAdj0( 蒼い ) // (oK) (adj) blue/pale/green/unripe/inexperienced
 KanjiAdj0( 蒼白い ) // (adj) (1) pale/pallid/(2) blue and white
 KanjiAdj0( 騒々しい ) // (adj) noisy/boisterous/(P)
 KanjiAdj0( 騒がしい ) // (adj) noisy/(P)
 KanjiAdj0( 騒騒しい ) // (adj) noisy/boisterous
 KanjiAdj0( 憎々しい ) // (adj) hateful/detestable/loathsome
 KanjiAdj0( 憎い ) // (adj) (1) hateful/abominable/poor-looking/detestable/(2) (with irony) lovely, lovable, wonderful, etc./(P)
 KanjiAdj0( 憎たらしい ) // (adj) odious/hateful
 KanjiAdj0( 憎らしい ) // (adj) odious/hateful/(P)
 KanjiAdj0( 憎憎しい ) // (adj) hateful/detestable/loathsome
 KanjiAdj0( 造作ない ) // (adj) no trouble/easy
 KanjiAdj0( 造作無い ) // (adj) no trouble/easy
 KanjiAdj0( 息苦しい ) // (adj) choking/oppressive/suffocating
 KanjiAdj0( 捉え所のない ) // (adj) subtle/elusive/slippery
 KanjiAdj0( 捉え所の無い ) // (adj) subtle/elusive/slippery
 KanjiAdj0( 足手まとい ) // (adj-na,n) impediment/burden/encumbrance/hindrance/drag
 KanjiAdj0( 足手纏い ) // (adj-na,n) impediment/burden/encumbrance/hindrance/drag
 KanjiAdj0( 足手纒い ) // (adj-na,n) impediment/burden/encumbrance/hindrance/drag
 KanjiAdj0( 足速い ) // (adj) swift-footed/light-footed
 KanjiAdj0( 速い ) // (adj) quick/fast/swift/(P)
 KanjiAdj0( 俗っぽい ) // (adj) cheap (reading)/vulgar/worldly-minded
 KanjiAdj0( 揃わない ) // (adj) unequal/uneven/incomplete/odd
 KanjiAdj0( 尊い ) // (adj) precious/valuable/priceless/noble/exalted/sacred/(P)
 KanjiAdj0( 遜色がない ) // (adj) bears comparison with (something)/compares favorably with (something)/compares favourably with (something)/isn't inferior to (something)
 KanjiAdj0( 他愛ない ) // (adj) (uk) silly/foolish/absurd/childish/easy/trifling/guileless
 KanjiAdj0( 他愛もない ) // (adj) (uk) silly/foolish/absurd/childish/easy/trifling/guileless
 KanjiAdj0( 他愛も無い ) // (adj) (uk) silly/foolish/absurd/childish/easy/trifling/guileless
 KanjiAdj0( 他愛無い ) // (adj) (uk) silly/foolish/absurd/childish/easy/trifling/guileless
 KanjiAdj0( 多い ) // (adj) many/numerous/(P)
 KanjiAdj0( 太い ) // (adj) fat/thick/(P)
 KanjiAdj0( 太太しい ) // (adj) (uk) impudent/brazen/shameless/bold
 KanjiAdj0( 打つ手がない ) // (adj) no way to do/nothing can be done
 KanjiAdj0( 耐え難い ) // (adj) unbearable/intolerable/unendurable
 KanjiAdj0( 耐難い ) // (adj) unbearable/intolerable/unendurable
 KanjiAdj0( 待ち遠しい ) // (adj) looking forward to/(P)
 KanjiAdj0( 待ち切れない ) // (adj) waiting impatiently for
 KanjiAdj0( 怠い ) // (adj) (uk) sluggish/feel heavy/languid/dull/(P)
 KanjiAdj0( 態とらしい ) // (adj) unnatural/affected/studied/forced
 KanjiAdj0( 大きい ) // (adj) big/large/great/(P)
 KanjiAdj0( 大違い ) // (adj) (1) great difference/(2) major mistake
 KanjiAdj0( 大嫌い ) // (adj-na,n) very dislikeable/hate, loathe, abhor/(P)
 KanjiAdj0( 大笑い ) // (adj-na,n) great laughter/burst of laughter/(P)
 KanjiAdj0( 大食い ) // (adj-na,n) gluttony
 KanjiAdj0( 大食らい ) // (adj-na,n) glutton
 KanjiAdj0( 大人げない ) // (adj) immature/childish
 KanjiAdj0( 大人しい ) // (adj) obedient/docile/quiet/(P)
 KanjiAdj0( 大人っぽい ) // (adj) adult-like
 KanjiAdj0( 大人気ない ) // (adj) immature/childish
 KanjiAdj0( 大人気無い ) // (adj) immature/childish
 KanjiAdj0( 嘆かわしい ) // (adj) sad/wretched/deplorable/(P)
 KanjiAdj0( 淡い ) // (adj) light/faint/pale/fleeting/(P)
 KanjiAdj0( 短い ) // (adj) short/(P)
 KanjiAdj0( 短かい ) // (io) (adj) short
 KanjiAdj0( 端たない ) // (adj) immodest/unladylike/vulgar/(P)
 KanjiAdj0( 暖い ) // (io) (adj) warm/mild/genial
 KanjiAdj0( 暖かい ) // (adj) warm/mild/genial
 KanjiAdj0( 段違い ) // (adj-na,n) wide difference/remarkable difference
 KanjiAdj0( 男っぽい ) // (adj) manly/boyish
 KanjiAdj0( 男らしい ) // (adj) manly/(P)
 KanjiAdj0( 知らない ) // (adj) unknown/strange
 KanjiAdj0( 恥ずかしい ) // (adj) shy/ashamed/embarrassed/(P)
 KanjiAdj0( 稚い ) // (adj) very young/childish
 KanjiAdj0( 遅い ) // (adj) late/slow/(P)
 KanjiAdj0( 茶色い ) // (adj) light brown/tawny
 KanjiAdj0( 忠実忠実しい ) // (adj) (uk) hardworking/painstaking/diligent/conscientious/sincere
 KanjiAdj0( 注意深い ) // (adj-na) careful/(P)
 KanjiAdj0( 著しい ) // (adj) remarkable/considerable/(P)
 KanjiAdj0( 彫りの深い ) // (adj) finely chiseled (features)
 KanjiAdj0( 聴衆を飽かさない ) // (adj) hold the attention of the audience
 KanjiAdj0( 長い ) // (adj) long/lengthy/(P)
 KanjiAdj0( 長たらしい ) // (adj) tedious/lengthy/overlong/long-winded
 KanjiAdj0( 長ったらしい ) // (adj) tedious/lengthy/overlong/long-winded
 KanjiAdj0( 長長しい ) // (adj) long, drawn-out/tedious
 KanjiAdj0( 捗々しい ) // (adj) quick/rapid/swift/satisfactory
 KanjiAdj0( 捗捗しい ) // (adj) quick/rapid/swift/satisfactory
 KanjiAdj0( 直らない ) // (adj) beyond repair/irreparable
 KanjiAdj0( 珍しい ) // (adj) unusual/rare/(P)
 KanjiAdj0( 痛々しい ) // (adj) pitiful/pathetic
 KanjiAdj0( 痛い ) // (adj) painful/(P)
 KanjiAdj0( 痛ましい ) // (adj) pitiful/heartbreaking/(P)
 KanjiAdj0( 痛快極まりない ) // (adj) be extremely thrilling
 KanjiAdj0( 痛快極まり無い ) // (adj) be extremely thrilling
 KanjiAdj0( 痛痛しい ) // (adj) pitiful/pathetic
 KanjiAdj0( 辻褄の合わない ) // (adj) incoherent/inconsistent
 KanjiAdj0( 低い ) // (adj) short/low/humble/low (voice)/(P)
 KanjiAdj0( 底意地悪い ) // (adj) malicious/spiteful
 KanjiAdj0( 底気味悪い ) // (adj) strange/eerie/ominous
 KanjiAdj0( 底堅い ) // (adj) stable (market) after having bottomed out
 KanjiAdj0( 程遠い ) // (adj) far off or away
 KanjiAdj0( 程近い ) // (adj) near/nearby/not far off
 KanjiAdj0( 程好い ) // (adj) moderate/proper/just right
 KanjiAdj0( 程良い ) // (adj) moderate/proper/just right
 KanjiAdj0( 締まりのない ) // (adj) slack/loose/lax
 KanjiAdj0( 締まりの無い ) // (adj) slack/loose/lax
 KanjiAdj0( 泥臭い ) // (adj) smelling of mud or earth/unrefined/uncouth
 KanjiAdj0( 適わない ) // (adj) be beyond one's power/be unable
 KanjiAdj0( 点の打ち所がない ) // (adj) be above reproach
 KanjiAdj0( 点の打ち所が無い ) // (adj) be above reproach
 KanjiAdj0( 妬ましい ) // (adj) jealous/envious
 KanjiAdj0( 徒広い ) // (adj) very (excessively) spacious/unduly wide/sprawling
 KanjiAdj0( 途轍もない ) // (adj) (uk) extravagant/absurd/unbelievable/preposterous/unreasonable
 KanjiAdj0( 途轍も無い ) // (adj) (uk) extravagant/absurd/unbelievable/preposterous/unreasonable
 KanjiAdj0( 途方もない ) // (adj) extraordinary/preposterous/outrageous/absurd
 KanjiAdj0( 度し難い ) // (adj) beyond help/incorrigible
 KanjiAdj0( 土臭い ) // (adj) smelling of earth/rustic
 KanjiAdj0( 怒りっぽい ) // (adj) hot-tempered/quick to take offense/quick to take offence/irascible/touchy
 KanjiAdj0( 当たり障りのない ) // (adj) harmless and inoffensive
 KanjiAdj0( 当たり障りの無い ) // (adj) harmless and inoffensive
 KanjiAdj0( 当てのない ) // (adj) aimless
 KanjiAdj0( 等しい ) // (adj) equal/similar/like/equivalent/(P)
 KanjiAdj0( 得体の知れない ) // (adj-pn) strange/unfamiliar/mysterious/suspicious
 KanjiAdj0( 得難い ) // (adj) hard to get
 KanjiAdj0( 徳の高い ) // (adj) virtuous/respectable
 KanjiAdj0( 篤い ) // (adj) serious/cordial/faithful/kind/warm
 KanjiAdj0( 毒々しい ) // (adj) poisonous/venomous
 KanjiAdj0( 毒毒しい ) // (adj) poisonous/venomous
 KanjiAdj0( 読みづらい ) // (adj) hard to read
 KanjiAdj0( 読み辛い ) // (adj) hard to read
 KanjiAdj0( 突拍子もない ) // (adj) astounding/tremendous/crazy/exorbitant
 KanjiAdj0( 突拍子も無い ) // (adj) astounding/tremendous/crazy/exorbitant
 KanjiAdj0( 鈍い ) // (adj) dull (e.g., a knife)/thickheaded/slow (opposite of fast)/stupid/(P)
 KanjiAdj0( 鈍臭い ) // (adj) slow (opposite of fast)/stupid/irritating
 KanjiAdj0( 馴々しい ) // (adj) over-familiar
 KanjiAdj0( 馴れ馴れしい ) // (adj) over-familiar/(P)
 KanjiAdj0( 馴染み深い ) // (adj) extremely intimate/very well-acquainted
 KanjiAdj0( 軟らかい ) // (adj) soft/tender/limp/(P)
 KanjiAdj0( 難い ) // (adj,suf) difficult/hard/(P)
 KanjiAdj0( 難しい ) // (adj) difficult
 KanjiAdj0( 日の目を見ない ) // (adj) staying indoors/have no sunshine/remain obscure
 KanjiAdj0( 乳臭い ) // (adj) smelling of milk/green/wet behind the ears/immature
 KanjiAdj0( 如何わしい ) // (adj) (1) (uk) suspicious/dubious/unreliable/(2) indecent/unseemly
 KanjiAdj0( 如才ない ) // (adj) tactful/shrewd/cautious/clever/smart/adroit
 KanjiAdj0( 如才無い ) // (adj) tactful/shrewd/cautious/clever/smart/adroit
 KanjiAdj0( 如在無い ) // (adj) tactful/shrewd/cautious/clever/smart/adroit
 KanjiAdj0( 忍び難い ) // (adj) intolerable/unbearable
 KanjiAdj0( 忍耐強い ) // (adj) persevering/very patient
 KanjiAdj0( 認め難い ) // (adj) unapprovable
 KanjiAdj0( 猫の子一匹居ない ) // (adj) completely deserted
 KanjiAdj0( 熱い ) // (adj) hot (thing)/(P)
 KanjiAdj0( 熱し易い ) // (adj) excitable
 KanjiAdj0( 熱っぽい ) // (adj) (1) feverish/(2) enthusiastic
 KanjiAdj0( 年甲斐もない ) // (adj) unbecoming/unsuitable/disgraceful
 KanjiAdj0( 年甲斐も無い ) // (adj) unbecoming/unsuitable/disgraceful
 KanjiAdj0( 年若い ) // (adj) young/youthful
 KanjiAdj0( 年端もいかない ) // (adj) of tender years/very young
 KanjiAdj0( 年端も行かない ) // (adj) of tender years/very young
 KanjiAdj0( 粘い ) // (adj) sticky
 KanjiAdj0( 粘っこい ) // (adj) sticky/stiff/tenacious/persistent
 KanjiAdj0( 粘り強い ) // (adj) tenacious/persevering/persistent/(P)
 KanjiAdj0( 悩ましい ) // (adj) (1) seductive/carnal/enchanting/(2) troubling/difficult/thorny/hard/(3) anxious/uneasy
 KanjiAdj0( 濃い ) // (adj) thick (as of color, liquid) (colour)/dense/strong/(P)
 KanjiAdj0( 納まらない ) // (adj) feel grieved/be unsatisfied
 KanjiAdj0( 能がない ) // (adj) incompetent/have no merit
 KanjiAdj0( 能が無い ) // (adj) incompetent/have no merit
 KanjiAdj0( 馬鹿らしい ) // (adj) absurd/(P)
 KanjiAdj0( 馬鹿臭い ) // (adj) absurd
 KanjiAdj0( 馬鹿馬鹿しい ) // (adj) stupid
 KanjiAdj0( 白々しい ) // (adj) (1) barefaced (e.g., lie)/shameless/transparent/(2) pure white/very clear
 KanjiAdj0( 白い ) // (adj) white/(P)
 KanjiAdj0( 白っぽい ) // (adj) whitish
 KanjiAdj0( 白白しい ) // (adj) (1) barefaced (e.g., lie)/shameless/transparent/(2) pure white/very clear
 KanjiAdj0( 薄い ) // (adj) thin/weak/watery/diluted/(P)
 KanjiAdj0( 薄ら寒い ) // (adj) chilly/rather cold/somewhat cold
 KanjiAdj0( 薄暗い ) // (adj) dim/gloomy/(P)
 KanjiAdj0( 薄汚い ) // (adj) filthy/dirty (looking)/drab
 KanjiAdj0( 薄汚ない ) // (adj) filthy/dirty (looking)/drab
 KanjiAdj0( 薄気味悪い ) // (adj) weird/eerie/uncanny
 KanjiAdj0( 薄白い ) // (adj) whitish
 KanjiAdj0( 肌が合わない ) // (adj) cannot go together (with)
 KanjiAdj0( 肌寒い ) // (adj) chilly/unpleasantly cold
 KanjiAdj0( 抜け目ない ) // (adj) shrewd/astute/cunning
 KanjiAdj0( 判り難い ) // (adj) hard to understand/incomprehensible/unintelligible
 KanjiAdj0( 反りが合わない ) // (adj) unable to cooperate
 KanjiAdj0( 犯し難い ) // (adj) dignified
 KanjiAdj0( 煩い ) // (ateji) (adj) (1) noisy/loud/(2) fussy/(3) annoying/troublesome/tiresome/importunate/(4) bossy/(P)
 KanjiAdj0( 煩わしい ) // (adj) troublesome/annoying/complicated/(P)
 KanjiAdj0( 飯が食えない ) // (adj) cannot make a living
 KanjiAdj0( 卑しい ) // (adj) greedy/vulgar/shabby/humble/base/mean/vile/(P)
 KanjiAdj0( 悲しい ) // (adj) sad/sorrowful/(P)
 KanjiAdj0( 比べ物にならない ) // (adj) cannot be compared with/be no match for
 KanjiAdj0( 比を見ない ) // (adj) be unique (unrivaled, unrivalled)
 KanjiAdj0( 比類のない ) // (adj) peerless
 KanjiAdj0( 非道い ) // (adj) (uk) cruel/awful/severe/very bad/serious/terrible/heavy/violent
 KanjiAdj0( 微笑ましい ) // (adj) pleasant/charming
 KanjiAdj0( 微酔い ) // (adj) slightly drunk/tipsy
 KanjiAdj0( 美々しい ) // (adj) beautiful
 KanjiAdj0( 美しい ) // (adj) beautiful/lovely/(P)
 KanjiAdj0( 美美しい ) // (adj) beautiful
 KanjiAdj0( 美味い ) // (adj) (1) delicious/appetizing/appetising/(2) skillful/clever/expert/wise/successful/(3) fortunate/splendid/promising
 KanjiAdj0( 美味しい ) // (adj) delicious/tasty/(P)
 KanjiAdj0( 鼻持ちならない ) // (adj) stink/intolerable
 KanjiAdj0( 貧しい ) // (adj) poor/needy/(P)
 KanjiAdj0( 敏捷い ) // (adj) (1) (uk) smart/clever/(2) agile/nimble/quick
 KanjiAdj0( 不甲斐ない ) // (adj) disappointing/weak-minded/spiritless/cowardly/worthless
 KanjiAdj0( 不甲斐無い ) // (adj) disappointing/weak-minded/spiritless/cowardly/worthless
 KanjiAdj0( 不似合い ) // (adj-na,n) unbecoming/improper/unsuitable/ill-matched/unworthy of
 KanjiAdj0( 不揃い ) // (adj-na,n) unevenness/irregularity/lack of uniformity
 KanjiAdj0( 不釣り合い ) // (adj-na,n) unbalance/imbalance/asymmetry/disparity
 KanjiAdj0( 不釣合い ) // (adj-na,n) unbalance/imbalance/asymmetry/disparity
 KanjiAdj0( 不味い ) // (adj) (uk) unappetising/unappetizing/unpleasant (taste, appearance, situation)/ugly/unskilful/awkward/bungling/unwise/untimely/(P)
 KanjiAdj0( 怖い ) // (adj) scary/frightening/eerie/dreadful/(P)
 KanjiAdj0( 普通でない ) // (adj) abnormal
 KanjiAdj0( 浮かばれない ) // (adj) turning in one's grave/cannot rest in peace
 KanjiAdj0( 膚寒い ) // (adj) chilly/unpleasantly cold
 KanjiAdj0( 負けず嫌い ) // (adj-na,n) hating to lose/determined
 KanjiAdj0( 部厚い ) // (adj) bulky/massive/thick/heavy
 KanjiAdj0( 風采が揚がらない ) // (adj) make a poor appearance
 KanjiAdj0( 幅広い ) // (adj) extensive/wide/broad/(P)
 KanjiAdj0( 福福しい ) // (adj) (plump and) happy-looking
 KanjiAdj0( 腹が緩い ) // (adj) have loose bowels
 KanjiAdj0( 腹汚い ) // (adj) black-hearted/nasty
 KanjiAdj0( 腹黒い ) // (adj) mean/malicious/scheming
 KanjiAdj0( 腹立たしい ) // (adj) irritating
 KanjiAdj0( 腹穢い ) // (adj) black-hearted/nasty
 KanjiAdj0( 仏臭い ) // (adj) otherwordly/sanctimonious
 KanjiAdj0( 物々しい ) // (adj) imposing/showy/overdone
 KanjiAdj0( 物の数に入らない ) // (adj) be off the map/be insignificant
 KanjiAdj0( 物狂おしい ) // (adj) frantic/like mad
 KanjiAdj0( 物堅い ) // (adj) honest/upright/faithful/reliable
 KanjiAdj0( 物見高い ) // (adj) burning curiosity
 KanjiAdj0( 物寂しい ) // (adj) lonely
 KanjiAdj0( 物凄い ) // (adj) earth-shattering/staggering/to a very great extent/(P)
 KanjiAdj0( 物騒がしい ) // (adj) noisy/boisterous/turbulent
 KanjiAdj0( 物足りない ) // (adj) unsatisfied/unsatisfactory/(P)
 KanjiAdj0( 物体ない ) // (adj) (uk) too good/more than one deserves/wasteful/sacrilegious/unworthy of
 KanjiAdj0( 物体無い ) // (adj) (uk) too good/more than one deserves/wasteful/sacrilegious/unworthy of
 KanjiAdj0( 物珍しい ) // (adj) curious
 KanjiAdj0( 物悲しい ) // (adj) sad/melancholy
 KanjiAdj0( 物物しい ) // (adj) imposing/showy/overdone
 KanjiAdj0( 物憂い ) // (adj) languid/weary/listless/melancholy
 KanjiAdj0( 物淋しい ) // (adj) lonely
 KanjiAdj0( 分かち難い ) // (adj) inseparable
 KanjiAdj0( 分かりづらい ) // (adj) difficult to understand
 KanjiAdj0( 分かりにくい ) // (adj) hard to understand/incomprehensible/unintelligible
 KanjiAdj0( 分かりやすい ) // (adj) easy to understand
 KanjiAdj0( 分かり悪い ) // (adj) hard to understand/incomprehensible/unintelligible
 KanjiAdj0( 分かり易い ) // (adj) easy to understand
 KanjiAdj0( 分かり辛い ) // (adj) difficult to understand
 KanjiAdj0( 分かり難い ) // (oK) (adj) hard to understand/incomprehensible/unintelligible
 KanjiAdj0( 分かり良い ) // (adj) easy to understand
 KanjiAdj0( 分厚い ) // (adj) bulky/massive/thick/heavy
 KanjiAdj0( 紛らわしい ) // (adj) confusing/misleading/equivocal/ambiguous/(P)
 KanjiAdj0( 聞き悪い ) // (adj) difficult to hear/hesitating to ask
 KanjiAdj0( 聞き苦しい ) // (adj) poor sound quality/unpleasant to hear
 KanjiAdj0( 聞き辛い ) // (adj) difficult to hear/difficult to ask
 KanjiAdj0( 聞き分けの良い ) // (adj) reasonable
 KanjiAdj0( 聞き良い ) // (adj) pleasant to listen to
 KanjiAdj0( 平たい ) // (adj) flat/even/level/simple/plain/(P)
 KanjiAdj0( 柄にもない ) // (adj) out of character/unlike one
 KanjiAdj0( 柄にも無い ) // (adj) out of character/unlike one
 KanjiAdj0( 柄の悪い ) // (adj) ill-bred
 KanjiAdj0( 並びない ) // (adj) unparalleled/unparallelled/unequaled/unequalled/unique
 KanjiAdj0( 並び無い ) // (adj) unparalleled/unparallelled/unequaled/unequalled/unique
 KanjiAdj0( 碧い ) // (oK) (adj) blue/pale/green/unripe/inexperienced
 KanjiAdj0( 変わらない ) // (adj) constant/invariant/(P)
 KanjiAdj0( 変わり易い ) // (adj) changeable/unsettled/inconstant
 KanjiAdj0( 変哲もない ) // (adj) usual/mediocre/monotonous
 KanjiAdj0( 変哲も無い ) // (adj) usual/mediocre/monotonous
 KanjiAdj0( 片腹痛い ) // (adj) ridiculous/absurd
 KanjiAdj0( 弁えのない ) // (adj) indiscreet/undiscerning
 KanjiAdj0( 弁えの無い ) // (adj) indiscreet/undiscerning
 KanjiAdj0( 捕らえ所のない ) // (adj) subtle/elusive/slippery
 KanjiAdj0( 捕らえ所の無い ) // (adj) subtle/elusive/slippery
 KanjiAdj0( 慕わしい ) // (adj) dear/beloved
 KanjiAdj0( 呆気ない ) // (adj) not enough/too quick (short, long, etc.)
 KanjiAdj0( 芳しい ) // (adj) sweet/fragrant/aromatic/savory/savoury/(P)
 KanjiAdj0( 芳しくない ) // (adj) poor/unfavourable/unfavorable/disgraceful
 KanjiAdj0( 飽きっぽい ) // (adj) fickle/capricious/soon wearied of
 KanjiAdj0( 飽き易い ) // (adj) tired of/wearied/fickle
 KanjiAdj0( 飽き足らない ) // (adj) unsatisfactory/unsatisfying
 KanjiAdj0( 飽き足りない ) // (adj) unsatisfactory/unsatisfying
 KanjiAdj0( 飽くことを知らない ) // (adj) insatiable
 KanjiAdj0( 乏しい ) // (adj) meagre/meager/scarce/limited/destitute/hard up/scanty/poor
 KanjiAdj0( 亡い ) // (adj) dead
 KanjiAdj0( 忘れっぽい ) // (adj) forgetful
 KanjiAdj0( 忙しい ) // (adj) busy/irritated
 KanjiAdj0( 忙しない ) // (adj) restless/fidgety/in a hurry
 KanjiAdj0( 望ましい ) // (adj) desirable/hoped for/(P)
 KanjiAdj0( 睦まじい ) // (adj) harmonious
 KanjiAdj0( 又ない ) // (adj) unique/matchless/unparalleled/unparallelled/never again
 KanjiAdj0( 又無い ) // (adj) unique/matchless/unparalleled/unparallelled/never again
 KanjiAdj0( 抹香臭い ) // (adj) smelling of incense/overly pious
 KanjiAdj0( 末永い ) // (adj) very long/many years of
 KanjiAdj0( 末恐ろしい ) // (adj) ominous/likely to grow worse
 KanjiAdj0( 末若い ) // (adj) young/youthful
 KanjiAdj0( 末頼もしい ) // (adj) promising (future)
 KanjiAdj0( 満更でもない ) // (adj) not as dissatisfied (or annoyed) as (s)he would have us believe
 KanjiAdj0( 満更夢ではない ) // (adj) not altogether a dream
 KanjiAdj0( 味わい ) // (n,adj-no) (1) flavour/flavor/(2) meaning/significance/(P)
 KanjiAdj0( 味気ない ) // (adj) wearisome/insipid/irksome/wretched/vain
 KanjiAdj0( 味気無い ) // (adj) wearisome/insipid/irksome/wretched/vain
 KanjiAdj0( 未払い ) // (n,adj-no) unpaid/overdue/(P)
 KanjiAdj0( 未練がましい ) // (adj) (1) regretful/irresolute/(2) unmanly
 KanjiAdj0( 眠い ) // (adj) (1) sleepy/drowsy/(2) aestivation/estivation/(P)
 KanjiAdj0( 眠たい ) // (adj) sleepy/(P)
 KanjiAdj0( 無い ) // (adj) there isn't/doesn't have/(P)
 KanjiAdj0( 名もない ) // (adj) unknown/obscure/insignificant
 KanjiAdj0( 名も無い ) // (adj) unknown/obscure/insignificant
 KanjiAdj0( 名高い ) // (adj) famous/celebrated/well-known/(P)
 KanjiAdj0( 名残り惜しい ) // (adj) regret (at parting)/reluctance (to part)
 KanjiAdj0( 名残惜しい ) // (adj) regret (at parting)/reluctance (to part)/(P)
 KanjiAdj0( 明い ) // (io) (adj) bright/cheerful
 KanjiAdj0( 明るい ) // (adj) bright/cheerful/(P)
 KanjiAdj0( 滅多にない ) // (adj) (uk) rare
 KanjiAdj0( 滅多に無い ) // (adj) (uk) rare
 KanjiAdj0( 面映ゆい ) // (adj) embarrassed/self-conscious/bashful/abashed
 KanjiAdj0( 面憎い ) // (adj) provoking/offensive
 KanjiAdj0( 面倒い ) // (adj) troublesome/bothersome
 KanjiAdj0( 面倒臭い ) // (adj) bother to do/tiresome/(P)
 KanjiAdj0( 面白い ) // (adj) interesting/amusing/(P)
 KanjiAdj0( 面白可笑しい ) // (adj) humorous/humourous/funny
 KanjiAdj0( 面目ない ) // (adj) ashamed
 KanjiAdj0( 面目無い ) // (adj) ashamed
 KanjiAdj0( 妄りがましい ) // (oK) (adj) morally corrupt
 KanjiAdj0( 毛深い ) // (adj) hairy/thickly haired
 KanjiAdj0( 猛々しい ) // (adj) ferocious
 KanjiAdj0( 猛猛しい ) // (adj) ferocious
 KanjiAdj0( 木深い ) // (adj) deep in the woods
 KanjiAdj0( 目がない ) // (adj) extremely fond of/having a weakness for
 KanjiAdj0( 目ざとい ) // (adj) (1) sharp sighted/(2) easily awakened
 KanjiAdj0( 目ぼしい ) // (adj) main/chief/important/valuable
 KanjiAdj0( 目まぐるしい ) // (adj) hectic/bewildering/bustling/dizzy
 KanjiAdj0( 目もくれない ) // (adj) indifferent/paying no attention/taking no notice
 KanjiAdj0( 目映い ) // (adj) dazzling/glaring/dazzlingly beautiful
 KanjiAdj0( 目覚しい ) // (adj) (arch) brilliant/splendid/striking/remarkable
 KanjiAdj0( 目覚ましい ) // (adj) (arch) brilliant/splendid/striking/remarkable/(P)
 KanjiAdj0( 目出度い ) // (adj) happy/simple soul/propitious/joyous/(P)
 KanjiAdj0( 目新しい ) // (adj) original/novel/new
 KanjiAdj0( 目早い ) // (adj) sharp-eyed
 KanjiAdj0( 目敏い ) // (adj) (1) sharp sighted/(2) easily awakened
 KanjiAdj0( 勿体ない ) // (adj) (uk) too good/more than one deserves/wasteful/sacrilegious/unworthy of/(P)
 KanjiAdj0( 勿体無い ) // (adj) (uk) too good/more than one deserves/wasteful/sacrilegious/unworthy of
 KanjiAdj0( 尤もらしい ) // (adj) plausible/(P)
 KanjiAdj0( 夜深い ) // (adj) (staying) up late at night
 KanjiAdj0( 野太い ) // (adj) audacious/throaty (voice)
 KanjiAdj0( 野暮ったい ) // (adj) unfashionable (e.g., clothes)/uncouth/unpolished
 KanjiAdj0( 訳が分らない ) // (adj) incomprehensible
 KanjiAdj0( 訳ない ) // (adj) (1) easy/simple/(exp) (2) (there is) no reason
 KanjiAdj0( 訳無い ) // (adj) (1) easy/simple/(exp) (2) (there is) no reason
 KanjiAdj0( 愉しい ) // (adj) enjoyable/fun
 KanjiAdj0( 油っ濃い ) // (adj) (uk) greasy/fatty/oily
 KanjiAdj0( 優しい ) // (adj) tender/kind/gentle/graceful/affectionate/amiable/suave/(P)
 KanjiAdj0( 優るとも劣らない ) // (adj) not at all inferior to
 KanjiAdj0( 勇ましい ) // (adj) brave/valiant/gallant/courageous/(P)
 KanjiAdj0( 憂い ) // (adj) unhappy/sad/gloomy
 KanjiAdj0( 有りもしない ) // (adj) nonexistent/unreal/imaginary/spurious
 KanjiAdj0( 有り難い ) // (adj) grateful/thankful/welcome/appreciated/evoking gratitude/(P)
 KanjiAdj0( 有難い ) // (adj) grateful/thankful/welcome/appreciated/evoking gratitude/(P)
 KanjiAdj0( 由々しい ) // (adj) grave/serious/alarming
 KanjiAdj0( 由由しい ) // (adj) grave/serious/alarming
 KanjiAdj0( 雄雄しい ) // (adj) manly/brave/heroic
 KanjiAdj0( 余り面白くない ) // (adj) not very interesting
 KanjiAdj0( 余儀ない ) // (adj) unavoidable/inevitable/beyond one's control/(P)
 KanjiAdj0( 余儀無い ) // (adj) unavoidable/inevitable/beyond one's control
 KanjiAdj0( 余所余所しい ) // (adj) distant/cold/formal
 KanjiAdj0( 幼い ) // (adj) very young/childish/(P)
 KanjiAdj0( 幼気ない ) // (adj) (uk) innocent/helpless/tender
 KanjiAdj0( 妖しい ) // (adj) (1) suspicious/dubious/doubtful/(adj) (2) charming/bewitching
 KanjiAdj0( 容易い ) // (adj) (uk) easy/simple/light/(P)
 KanjiAdj0( 揺るぎない ) // (adj) solid/firm/steady
 KanjiAdj0( 揺るぎ無い ) // (adj) solid/firm/steady
 KanjiAdj0( 用に足りない ) // (adj) be of no use/be useless
 KanjiAdj0( 用心深い ) // (adj) wary/watchful/(P)
 KanjiAdj0( 抑え難い ) // (adj) uncontrollable/irrepressible
 KanjiAdj0( 欲しい ) // (adj) wanted/wished for/in need of/desired/(P)
 KanjiAdj0( 欲深い ) // (adj) greedy
 KanjiAdj0( 頼み少ない ) // (adj) helpless
 KanjiAdj0( 頼もしい ) // (adj) reliable/trustworthy/hopeful/promising/(P)
 KanjiAdj0( 頼りない ) // (adj) unreliable/undependable/flaky/vague/helpless/forlorn/(P)
 KanjiAdj0( 頼り無い ) // (adj) unreliable/undependable/flaky/vague/helpless/forlorn
 KanjiAdj0( 濫りがましい ) // (adj) morally corrupt
 KanjiAdj0( 濫りがわしい ) // (adj) morally corrupt/slovenly/obscene
 KanjiAdj0( 理屈っぽい ) // (adj) argumentative
 KanjiAdj0( 立錐の余地もない ) // (adj) tightly packed/full to capacity
 KanjiAdj0( 留処無い ) // (adj) endless/ceaseless
 KanjiAdj0( 涼しい ) // (adj) cool/refreshing/(P)
 KanjiAdj0( 良い ) // (adj) (uk) good/nice/pleasant/fine/excellent/agreeable/ok/(P)
 KanjiAdj0( 力ない ) // (adj) feeble
 KanjiAdj0( 力強い ) // (adj) reassuring/emboldened/(P)
 KanjiAdj0( 力無い ) // (adj) feeble
 KanjiAdj0( 淋しい ) // (adj) lonely/lonesome/solitary/desolate
 KanjiAdj0( 涙ぐましい ) // (adj) touching/moving/painful/(P)
 KanjiAdj0( 涙脆い ) // (adj) easily moved to tears
 KanjiAdj0( 類のない ) // (adj) unprecedented/unparalleled/unparallelled
 KanjiAdj0( 類の無い ) // (adj) unprecedented/unparalleled/unparallelled
 KanjiAdj0( 冷たい ) // (adj) cold (to the touch)/chilly/icy/freezing/coldhearted/(P)
 KanjiAdj0( 礼儀正しい ) // (adj) polite (person)
 KanjiAdj0( 麗々しい ) // (adj) ostentatious/gaudy/showy
 KanjiAdj0( 麗しい ) // (adj) beautiful/lovely
 KanjiAdj0( 麗麗しい ) // (adj) ostentatious/gaudy/showy
 KanjiAdj0( 烈しい ) // (adj) violent/vehement/intense/furious/tempestuous
 KanjiAdj0( 恋しい ) // (adj) (1) dear/beloved/darling/(2) yearned for/(P)
 KanjiAdj0( 呂律が回らない ) // (adj) speaking inarticulately (slurring, lisping, etc)
 KanjiAdj0( 労わしい ) // (adj) heartrending/pitiful
 KanjiAdj0( 和気あいあい ) // (adj-na,adj-t) (1) harmonious/(n) (2) peace and harmony
 KanjiAdj0( 腕が良い ) // (adj) be able/be skilled
 KanjiAdj0( 腕弛るい ) // (adj) (1) (uk) listless/languid/sluggish/(2) irritating/exasperating/tiresome
 KanjiAdj0( 仄暗い ) // (adj) gloomy/obscure
 KanjiAdj0( 仄白い ) // (adj) dimly white
 KanjiAdj0( 佗しい ) // (adj) miserable/wretched/lonely/dreary/shabby/comfortless
 KanjiAdj0( 侘しい ) // (adj) miserable/wretched/lonely/dreary/shabby/comfortless
 KanjiAdj0( 儘ならない ) // (adj) (uk) unable to have one's way with
 KanjiAdj0( 儚い ) // (adj) fleeting/transient/short-lived/momentary/vain/fickle/miserable/empty/ephemeral/(P)
 KanjiAdj0( 凛々しい ) // (adj) gallant/brave/imposing/awe-inspiring/severe/biting/chivalrous/manly/dignified
 KanjiAdj0( 凛凛しい ) // (adj) gallant/brave/imposing/awe-inspiring/severe/biting/chivalrous/manly/dignified
 KanjiAdj0( 吝かでない ) // (adj) be ready (to do)/willing
 KanjiAdj0( 囂しい ) // (adj) (1) noisy/boisterous
 KanjiAdj0( 埒が明かない ) // (adj) make no progress/remain unsettled
 KanjiAdj0( 夥しい ) // (adj) abundantly/innumerably/(P)
 KanjiAdj0( 婀娜っぽい ) // (adj) coquettish
 KanjiAdj0( 忝い ) // (adj) grateful/indebted
 KanjiAdj0( 恙ない ) // (adj) well/in good health/safe/free from accident
 KanjiAdj0( 恙無い ) // (adj) well/in good health/safe/free from accident
 KanjiAdj0( 悍ましい ) // (adj) (uk) disgusting/repulsive
 KanjiAdj0( 憖い ) // (adj-na) (uk) thoughtlessly/rashly
 KanjiAdj0( 擽ぐったい ) // (io) (adj) (uk) ticklish
 KanjiAdj0( 擽ったい ) // (adj) (uk) ticklish/(P)
 KanjiAdj0( 鬱陶しい ) // (oK) (adj) (uk) gloomy/depressing/(P)
 KanjiAdj0( 毳々しい ) // (adj) (uk) gaudy/showy/garish/loud
 KanjiAdj0( 毳毳しい ) // (adj) (uk) gaudy/showy/garish/loud
 KanjiAdj0( 洒落臭い ) // (adj) impertinent/impudent/cheeky
 KanjiAdj0( 狡い ) // (adj) (uk) sly/cunning/(P)
 KanjiAdj0( 狡賢い ) // (adj-na) sly/(P)
 KanjiAdj0( 猥りがましい ) // (adj) morally corrupt
 KanjiAdj0( 猥りがわしい ) // (adj) morally corrupt/slovenly/obscene
 KanjiAdj0( 疚しい ) // (adj) (feel) guilty/(having a) guilty conscience
 KanjiAdj0( 疳高い ) // (adj) high-pitched/shrill
 KanjiAdj0( 痒い ) // (adj) itchy/itching/(P)
 KanjiAdj0( 眩い ) // (io) (adj) (col) (uk) cute/pretty
 KanjiAdj0( 眩しい ) // (adj) dazzling/radiant/(P)
 KanjiAdj0( 腑甲斐ない ) // (adj) disappointing/weak-minded/spiritless/cowardly/worthless
 KanjiAdj0( 腑甲斐無い ) // (adj) disappointing/weak-minded/spiritless/cowardly/worthless
 KanjiAdj0( 腥い ) // (adj) smelling of fish or blood/fish or meat
 KanjiAdj0( 膠もない ) // (adj) (uk) curt/point-blank
 KanjiAdj0( 膠も無い ) // (adj) (uk) curt/point-blank
 KanjiAdj0( 訝しい ) // (adj) suspicious/doubtful
 KanjiAdj0( 諄い ) // (adj) (uk) verbose/importunate/heavy (taste)/(P)
 KanjiAdj0( 賤しい ) // (adj) greedy/vulgar/shabby/humble/base/mean/vile
 KanjiAdj0( 逞しい ) // (adj) (uk) burly/strong/sturdy/(P)
 KanjiAdj0( 遽しい ) // (adj) busy/hurried/confused/flurried
 KanjiAdj0( 饑い ) // (adj) (uk) hungry
 KanjiAdj0( 騙され易い ) // (adj) (uk) gullible/naive
 KanjiAdj0( 黴臭い ) // (adj) musty/putrid

 KanjiAdj1( 新鮮な ) // свежий
 KanjiAdj1( 穏やかな ) // спокойный
 KanjiAdj1( 静かな )
 KanjiAdj1( 永の ) // (adj) long/eternal
 KanjiAdj1( 押すな押すな ) // (adj-no) crowded (e.g. with people)/overflowing
 KanjiAdj1( 何の ) // (adj-pn) what kind/what sort
 KanjiAdj1( 可笑しな ) // (adj-pn) ridiculous/odd/(P)
 KanjiAdj1( 開かずの ) // (adj-no) (1) unopened/(2) forbidden
 KanjiAdj1( 頑な ) // (adj-na) (uk) obstinate/(P)
 KanjiAdj1( 此の ) // (adj-pn,int) (uk) this/(P)
 KanjiAdj1( 此れ等の ) // (adj-no) (uk) these
 KanjiAdj1( 色んな ) // (adj-pn) various/(P)
 KanjiAdj1( 真の ) // (adj-pn) true/real/genuine/utter/(P)
 KanjiAdj1( 其の ) // (adj-pn) (uk) the/that
 KanjiAdj1( 長の ) // (adj) long/eternal
 KanjiAdj1( 当の ) // (adj-pn,pref) the .. in question/(P)
 KanjiAdj1( 彼の ) // (adj-pn) (uk) that over there
 KanjiAdj1( 彼らの ) // (adj-no) their
 KanjiAdj1( 彼等の ) // (adj-no) their
// KanjiAdj1( 本の ) // (adj-pn) (uk) mere/only/just/(P)
 KanjiAdj1( 味な ) // (adj-pn) smart/clever/witty/strange
 KanjiAdj1( 有らずもがな ) // (adj-no) uncalled for/unnecessary/gratuitous


 KanjiAdj2( サロン的 ) // (adj-na) (1) social/(2) exclusive
 KanjiAdj2( 圧制的 ) // (adj-na) oppressive/despotic
 KanjiAdj2( 圧倒的 ) // (adj-na,n) overwhelming/(P)
 KanjiAdj2( 威圧的 ) // (adj-na) coercive/overbearing
 KanjiAdj2( 威嚇的 ) // (adj-na) threatening/menacing
 KanjiAdj2( 意志的 ) // (adj-na) strong-willed
 KanjiAdj2( 意識的 ) // (adj-na) consciously/deliberately/(P)
 KanjiAdj2( 意図的 ) // (adj-na) intentional/on purpose/(P)
 KanjiAdj2( 一義的 ) // (adj-na,n) unmistakable
 KanjiAdj2( 一元的 ) // (adj-na,n) monistic/unitary/unified/centralized/centralised
 KanjiAdj2( 一時的 ) // (adj-na,n) temporary/(P)
 KanjiAdj2( 一般的 ) // (adj-na) popular/typical/general/(P)
 KanjiAdj2( 一方的 ) // (adj-na) one-sided/unilateral/arbitrary/(P)
 KanjiAdj2( 印象的 ) // (adj-na) impressive/(P)
 KanjiAdj2( 運命的 ) // (adj-na) (pre)destined
 KanjiAdj2( 営利的 ) // (adj-na) commercial
 KanjiAdj2( 英雄的 ) // (adj-na) heroic
 KanjiAdj2( 衛生的 ) // (adj-na) hygienic/sanitary/(P)
 KanjiAdj2( 厭世的 ) // (adj-na) pessimistic
 KanjiAdj2( 演劇的 ) // (adj-na) dramatic/theatrical
 KanjiAdj2( 遠心的 ) // (adj-na) centrifugal
 KanjiAdj2( 化学的 ) // (adj-na) chemical
 KanjiAdj2( 仮言的 ) // (adj-na) hypothetical
 KanjiAdj2( 可及的 ) // (adj-na) as .. as possible
 KanjiAdj2( 家庭的 ) // (adj-na,n) family-oriented/familial
 KanjiAdj2( 科学的 ) // (adj-na) scientific
 KanjiAdj2( 過渡的 ) // (adj-na) transitional
 KanjiAdj2( 画一的 ) // (adj-na) uniform/standard
 KanjiAdj2( 画期的 ) // (adj-na,n) epoch-making/(P)
 KanjiAdj2( 画世的 ) // (adj-na) epoch-making
 KanjiAdj2( 回帰的 ) // (adj-na) recursive
 KanjiAdj2( 回顧的 ) // (adj-na) retrospective
 KanjiAdj2( 外形的 ) // (adj-na) external/outward
 KanjiAdj2( 外交的 ) // (adj-na) diplomatic
 KanjiAdj2( 外的 ) // (adj-na,n) external/outside
 KanjiAdj2( 概念的 ) // (adj-na,n) general/conceptual
 KanjiAdj2( 劃期的 ) // (adj-na,n) epoch-making
 KanjiAdj2( 劃時代的 ) // (adj-na,n) epoch-making
 KanjiAdj2( 確定的 ) // (adj-na) definitely
 KanjiAdj2( 革新的 ) // (adj-na) (1) innovative/(2) liberal/reformist
 KanjiAdj2( 革命的 ) // (adj-na) revolutionary (e.g., technology)
 KanjiAdj2( 学究的 ) // (adj-na) scholastic/academic
 KanjiAdj2( 学際的 ) // (adj-na) interdisciplinary
 KanjiAdj2( 学問的 ) // (adj-na) scholarly
 KanjiAdj2( 楽観的 ) // (adj-na) optimistic/hopeful/(P)
 KanjiAdj2( 楽天的 ) // (adj-na,n) optimistic/(P)
 KanjiAdj2( 活動的 ) // (adj-na) active/dynamic/energetic
 KanjiAdj2( 官能的 ) // (adj-na) sensual/voluptuous/sexy
 KanjiAdj2( 感覚的 ) // (adj-na) sensible/sensuous
 KanjiAdj2( 感傷的 ) // (adj-na) sentimental
 KanjiAdj2( 感情的 ) // (adj-na) emotional/sentimental/(P)
 KanjiAdj2( 慣例的 ) // (adj-na) typical/customary
 KanjiAdj2( 観念的 ) // (adj-na) ideal
 KanjiAdj2( 間接的 ) // (adj-na) indirectly/(P)
 KanjiAdj2( 器質的 ) // (adj-na) organic
 KanjiAdj2( 基礎的 ) // (adj-na) fundamental/basic
 KanjiAdj2( 基本的 ) // (adj-na) fundamental/standard/basic/(P)
 KanjiAdj2( 奇跡的 ) // (adj-na) miraculous
 KanjiAdj2( 希望的 ) // (adj-na) wishful
 KanjiAdj2( 機械的 ) // (adj-na) mechanical
 KanjiAdj2( 機能的 ) // (adj-na) functional/efficient
 KanjiAdj2( 帰納的 ) // (adj-na,n) inductive/recursive
 KanjiAdj2( 季節的 ) // (adj-na) seasonal
 KanjiAdj2( 規則的 ) // (adj-na) systematic/regular/routine
 KanjiAdj2( 規範的 ) // (adj-na) normative
 KanjiAdj2( 記録的 ) // (adj-na) record(-setting)/(P)
 KanjiAdj2( 貴族的 ) // (adj-na) aristocratic
 KanjiAdj2( 儀礼的 ) // (adj-na) formal/courteous
 KanjiAdj2( 技巧的 ) // (adj-na) polished
 KanjiAdj2( 技術的 ) // (adj-na) technical/practical/(P)
 KanjiAdj2( 擬古典的 ) // (adj-na) pseudoclassic
 KanjiAdj2( 欺瞞的 ) // (adj-na) deceptive/fraudulent
 KanjiAdj2( 犠牲的 ) // (adj-na) self-sacrificing
 KanjiAdj2( 義務的 ) // (adj-na) compulsory/obligatory
 KanjiAdj2( 客観的 ) // (adj-na) objectivity/(P)
 KanjiAdj2( 逆説的 ) // (adj-na) paradoxical
 KanjiAdj2( 急進的 ) // (adj-na) radical
 KanjiAdj2( 巨視的 ) // (adj-na,n) macroscopic/(P)
 KanjiAdj2( 虚無的 ) // (adj-na) nihilistic
 KanjiAdj2( 享楽的 ) // (adj-na) pleasure-seeking
 KanjiAdj2( 強制的 ) // (adj-na) forced/compulsory
 KanjiAdj2( 教育的 ) // (adj-na) educational/instructive/(P)
 KanjiAdj2( 教訓的 ) // (adj-na) instructive
 KanjiAdj2( 狂信的 ) // (adj-na) fanatic
 KanjiAdj2( 狂的 ) // (adj-na,n) insane/fanatic
 KanjiAdj2( 脅迫的 ) // (adj-na) menacing/threatening
 KanjiAdj2( 驚異的 ) // (adj-na) wonderful
 KanjiAdj2( 局地的 ) // (adj-na) local
 KanjiAdj2( 禁欲的 ) // (adj-na) abstemious/(P)
 KanjiAdj2( 近代的 ) // (adj-na) modern/(P)
 KanjiAdj2( 具象的 ) // (adj-na) concrete/material/definite
 KanjiAdj2( 具体的 ) // (adj-na) concrete/tangible/definite/(P)
 KanjiAdj2( 空想的 ) // (adj-na) imaginary
 KanjiAdj2( 偶像教徒的 ) // (adj-na) idolatrous
 KanjiAdj2( 偶発的 ) // (adj-na) accidental/incidental/occasional/casual
 KanjiAdj2( 寓意的 ) // (adj) allegorical/emblematic
 KanjiAdj2( 屈辱的 ) // (adj-na) humiliating
 KanjiAdj2( 軍事的 ) // (adj-na) military
 KanjiAdj2( 形式的 ) // (adj-na) formal/(P)
 KanjiAdj2( 系統的 ) // (adj-na,n) systematic
 KanjiAdj2( 経験的 ) // (adj-na) experiential
 KanjiAdj2( 経済的 ) // (adj-na) economic/economical/(P)
 KanjiAdj2( 継続的 ) // (adj-na) continuous/(P)
 KanjiAdj2( 計画的 ) // (adj-na) systematic/(P)
 KanjiAdj2( 芸術的 ) // (adj-na) artistic
 KanjiAdj2( 劇的 ) // (adj-na,n) dramatic/(P)
 KanjiAdj2( 決定的 ) // (adj-na,n) definite/final/decisive/conclusive/(P)
 KanjiAdj2( 健康的 ) // (adj-na) hygienic/healthful/sanitary
 KanjiAdj2( 建設的 ) // (adj-na) constructive/(P)
 KanjiAdj2( 権威的 ) // (adj-na) authoritarian
 KanjiAdj2( 献身的 ) // (adj-na) devoted
 KanjiAdj2( 原始的 ) // (adj-na) primitive/original
 KanjiAdj2( 原則的 ) // (adj-na) general
 KanjiAdj2( 現実的 ) // (adj-na) realism/pragmatic
 KanjiAdj2( 現代的 ) // (adj-na) modernistic/(P)
 KanjiAdj2( 限定的 ) // (adj-na) limiting/restrictive
 KanjiAdj2( 個人的 ) // (adj-na) individualistic/personal/self-centred/self-centered/(P)
 KanjiAdj2( 個性的 ) // (adj-na) personal/individual
 KanjiAdj2( 古典的 ) // (adj-na) classical/(P)
 KanjiAdj2( 互助的 ) // (adj-na) friendly
 KanjiAdj2( 互譲的 ) // (adj-na) conciliatory
 KanjiAdj2( 後天的 ) // (adj-na,n) a posteriori/(P)
 KanjiAdj2( 語彙的 ) // (adj-na) lexical
 KanjiAdj2( 公的 ) // (adj-na,n) public/official/(P)
 KanjiAdj2( 功利的 ) // (adj-na,n) utilitarian
 KanjiAdj2( 効果的 ) // (adj-na) effective/successful/(P)
 KanjiAdj2( 効率的 ) // (adj-na) efficient/(P)
 KanjiAdj2( 向米的 ) // (adj-na) pro-American
 KanjiAdj2( 好意的 ) // (adj-na) favorable/favourable
 KanjiAdj2( 好戦的 ) // (adj-na) belligerent
 KanjiAdj2( 恒久的 ) // (adj-na) permanent/perpetual/lasting
 KanjiAdj2( 恒常的 ) // (adj-na) constant
 KanjiAdj2( 攻撃的 ) // (adj-na) offensive/aggressive
 KanjiAdj2( 肯定的 ) // (adj-na) affirmative
 KanjiAdj2( 高圧的 ) // (adj-na) high-handed/oppressive
 KanjiAdj2( 高踏的 ) // (adj-na) transcendent
 KanjiAdj2( 合憲的 ) // (adj-na) constitutional
 KanjiAdj2( 合法的 ) // (adj-na) legal/lawful/legitimate/low-abiding/in order/(P)
 KanjiAdj2( 合目的 ) // (adj-na) purposive/appropriate
 KanjiAdj2( 合理的 ) // (adj-na) rational/reasonable/logical/(P)
 KanjiAdj2( 国家的 ) // (adj-na) national
 KanjiAdj2( 国際的 ) // (adj-na) international/(P)
 KanjiAdj2( 国民的 ) // (adj-na) national/(P)
 KanjiAdj2( 今日的 ) // (adj-na) modern/up-to-date/(P)
 KanjiAdj2( 根本的 ) // (adj-na) fundamental/basic/(P)
 KanjiAdj2( 最終的 ) // (adj-na) finally/(P)
 KanjiAdj2( 作為的 ) // (adj-na) intentional/contrived
 KanjiAdj2( 殺人的 ) // (adj-na) murderous (workload, etc)
 KanjiAdj2( 散発的 ) // (adj-na) sporadic
 KanjiAdj2( 散文的 ) // (adj-na) prosaic
 KanjiAdj2( 暫定的 ) // (adj-na) temporary/provisional
 KanjiAdj2( 刺戟的 ) // (adj-na) stimulating
 KanjiAdj2( 刺激的 ) // (adj-na) stimulating
 KanjiAdj2( 史的 ) // (adj-na,n) historic/historical
 KanjiAdj2( 思索的 ) // (adj-na) contemplative/meditative
 KanjiAdj2( 思想的 ) // (adj-na) ideological
 KanjiAdj2( 支配的 ) // (adj-na) dominant/ruling/(P)
 KanjiAdj2( 私的 ) // (adj-na,n) personal/private/proprietary/(P)
 KanjiAdj2( 詩的 ) // (adj-na,n) poetic
 KanjiAdj2( 試験的 ) // (adj-na) experimental/provisional/(P)
 KanjiAdj2( 事務的 ) // (adj-na) businesslike/practical/(P)
 KanjiAdj2( 持続的 ) // (adj-na) continuous/dynamic (as opposed to static)/(P)
 KanjiAdj2( 自虐的 ) // (adj-na) self-torturing
 KanjiAdj2( 自殺的 ) // (adj-na) suicidal
 KanjiAdj2( 自主的 ) // (adj-na) independent/autonomous/(P)
 KanjiAdj2( 自動的 ) // (adj-na) automatic/(P)
 KanjiAdj2( 自発的 ) // (adj-na) spontaneous/voluntary/(P)
 KanjiAdj2( 質的 ) // (adj-na,n) qualitative/(P)
 KanjiAdj2( 実験的 ) // (adj-na) experimental
 KanjiAdj2( 実際的 ) // (adj-na) practical
 KanjiAdj2( 実質的 ) // (adj-na) substantially/(P)
 KanjiAdj2( 実証的 ) // (adj-na) empirical/positive
 KanjiAdj2( 実践的 ) // (adj-na) practical
 KanjiAdj2( 実用的 ) // (adj-na) practical/(P)
 KanjiAdj2( 写実的 ) // (adj-na) realistic/graphic/true to life
 KanjiAdj2( 社会的 ) // (adj-na) social/(P)
 KanjiAdj2( 社交的 ) // (adj-na) sociable/(P)
 KanjiAdj2( 主観的 ) // (adj-na) subjectivity/subject/ego/(P)
 KanjiAdj2( 主情的 ) // (adj-na) emotional
 KanjiAdj2( 主体的 ) // (adj-na) subjective/(P)
 KanjiAdj2( 主知的 ) // (adj-na) intellectual
 KanjiAdj2( 主動的 ) // (adj-na) autonomous
 KanjiAdj2( 主目的 ) // (n,adj-na) main purpose/primary objective
 KanjiAdj2( 手続き的 ) // (adj-na) procedural
 KanjiAdj2( 儒教的 ) // (adj-na) Confucian
 KanjiAdj2( 受動的 ) // (adj-na) passive/(P)
 KanjiAdj2( 集合的 ) // (adj-na) collective
 KanjiAdj2( 集約的 ) // (adj-na) intensive
 KanjiAdj2( 従的 ) // (adj-na) subordinate/secondary
 KanjiAdj2( 重層的 ) // (adj-na) stratified/multilayered
 KanjiAdj2( 宿命的 ) // (adj-na) fateful/predestined
 KanjiAdj2( 出世間的 ) // (adj-na) unworldly/religious
 KanjiAdj2( 庶民的 ) // (adj-na) normal/natural/common/(P)
 KanjiAdj2( 女性的 ) // (adj-na) feminine/effeminate/(P)
 KanjiAdj2( 小乗的 ) // (adj-na) narrow-minded
 KanjiAdj2( 消極的 ) // (adj-na) passive/(P)
 KanjiAdj2( 消耗的 ) // (adj-na) exhaustive
 KanjiAdj2( 衝動的 ) // (adj-na) impulsive
 KanjiAdj2( 象徴的 ) // (adj-na) symbolic/(P)
 KanjiAdj2( 常識的 ) // (adj-na) ordinary/sensible/commonplace/(P)
 KanjiAdj2( 常習的 ) // (adj-na) habitual
 KanjiAdj2( 職業的 ) // (adj-na) professional
 KanjiAdj2( 信仰的 ) // (adj-na) religious/spiritual
 KanjiAdj2( 侵略的 ) // (adj-na) aggressive
 KanjiAdj2( 審美的 ) // (adj-na) aesthetic
 KanjiAdj2( 心的 ) // (adj-na,n) mental/psychological/physical
 KanjiAdj2( 心理学的 ) // (adj-na) psychological
 KanjiAdj2( 心理的 ) // (adj-na) psychological/mental
 KanjiAdj2( 神秘的 ) // (adj-na) mysterious
 KanjiAdj2( 紳士的 ) // (adj-na) gentlemanly
 KanjiAdj2( 進歩的 ) // (adj-na) progressive
 KanjiAdj2( 人為的 ) // (adj-na) artificial/unnatural/(P)
 KanjiAdj2( 人間的 ) // (adj-na) human/(P)
 KanjiAdj2( 人工的 ) // (adj-na) artificial/unnatural/(P)
 KanjiAdj2( 人種的 ) // (adj-na) racial
 KanjiAdj2( 人的 ) // (adj-na,n) human/personal/(P)
 KanjiAdj2( 人道的 ) // (adj-na,n) humane/(P)
 KanjiAdj2( 推移的 ) // (adj-na) transitive
 KanjiAdj2( 数学的 ) // (adj-na) mathematical
 KanjiAdj2( 世界的 ) // (adj-na) global/international/world-famous/(P)
 KanjiAdj2( 世俗的 ) // (adj-na) worldliness
 KanjiAdj2( 性的 ) // (adj-na,n) sex/sexual/sexy/(P)
 KanjiAdj2( 政治的 ) // (adj-na) political/(P)
 KanjiAdj2( 生得的 ) // (adj-na) innate/inherent/natural/inborn
 KanjiAdj2( 生理的 ) // (adj-na) physiological/physiologic/physiologically
 KanjiAdj2( 精神的 ) // (adj-na) mental/emotional/(P)
 KanjiAdj2( 静的 ) // (adj-na,n) static
 KanjiAdj2( 積極的 ) // (adj-na) positive/active/proactive/(P)
 KanjiAdj2( 絶対的 ) // (adj-na) absolute/(P)
 KanjiAdj2( 絶望的 ) // (adj-na) desperate/hopeless
 KanjiAdj2( 先験的 ) // (adj-na,n) transcendental
 KanjiAdj2( 先端的 ) // (adj-na) ultramodern/leading
 KanjiAdj2( 先天的 ) // (adj-na,n) a priori/inborn/innate/inherent/congenital/hereditary/(P)
 KanjiAdj2( 宣言的 ) // (adj-na) declarative
 KanjiAdj2( 専門的 ) // (adj-na) technical (e.g., discussion)/exclusive/professional/(P)
 KanjiAdj2( 戦闘的 ) // (adj-na) militant/aggressive
 KanjiAdj2( 扇情的 ) // (adj-na) inflammatory/lascivious/sensational
 KanjiAdj2( 潜在的 ) // (adj-na) latent/potential
 KanjiAdj2( 煽情的 ) // (adj-na) inflammatory/lascivious/sensational
 KanjiAdj2( 前時代的 ) // (adj-na) premodern/old-fashioned/outmoded/antiquated
 KanjiAdj2( 漸進的 ) // (adj-na) gradual
 KanjiAdj2( 全国的 ) // (adj-na) nation-wide
 KanjiAdj2( 全般的 ) // (adj-na) universal/general
 KanjiAdj2( 全幅的 ) // (adj-na) fully
 KanjiAdj2( 全面的 ) // (adj-na) all-out/general/over-all/complete/extensive/full-scale/(P)
 KanjiAdj2( 組織的 ) // (adj-na) systematic/(P)
 KanjiAdj2( 遡及的 ) // (adj-na) retroactive
 KanjiAdj2( 創作的 ) // (adj-na) creative
 KanjiAdj2( 創造的 ) // (adj-na) creative/(P)
 KanjiAdj2( 挿話的 ) // (adj-na) episodic
 KanjiAdj2( 相関的 ) // (adj-na) correlative
 KanjiAdj2( 相対的 ) // (adj-na) relative/(P)
 KanjiAdj2( 相反的 ) // (adj-na,adv) reciprocal/reciprocally
 KanjiAdj2( 総括的 ) // (adj-na) all-inclusive/all-embracing/overall
 KanjiAdj2( 総合的 ) // (adj-na) synthetic/comprehensive/(P)
 KanjiAdj2( 装飾的 ) // (adj-na) decorative
 KanjiAdj2( 即物的 ) // (adj-na,n) practical/matter-of-fact/realistic/utilitarian
 KanjiAdj2( 他覚的 ) // (adj-na) objective (symptoms)
 KanjiAdj2( 多角的 ) // (adj-na) multilateral/many-sided/diversified/(P)
 KanjiAdj2( 多元的 ) // (adj-na,n) pluralism/plurality/(P)
 KanjiAdj2( 多面的 ) // (adj-na) multifaceted/versatile
 KanjiAdj2( 多目的 ) // (adj-na,n) multipurpose/(P)
 KanjiAdj2( 打算的 ) // (adj-na) calculating/mercenary/(P)
 KanjiAdj2( 体系的 ) // (adj-na) systematic
 KanjiAdj2( 対照的 ) // (adj-na) contrastive/(P)
 KanjiAdj2( 対称的 ) // (adj-na) symmetrical
 KanjiAdj2( 対蹠的 ) // (adj-na) diametrically opposed/antipodal
 KanjiAdj2( 退嬰的 ) // (adj-na) conservative/unadventurous
 KanjiAdj2( 退廃的 ) // (adj-na) degenerate/decadent/(P)
 KanjiAdj2( 代表的 ) // (adj-na) representative/exemplary/model/(P)
 KanjiAdj2( 大々的 ) // (adj-na,n) great/grand/extensive/large-scale/(P)
 KanjiAdj2( 大乗的 ) // (adj-na,n) broad/great
 KanjiAdj2( 大大的 ) // (adj-na,n) great/grand/extensive/large-scale
 KanjiAdj2( 第一義的 ) // (n,adj-na) basic/primary/fundamental
 KanjiAdj2( 択一的 ) // (adj-na) alternative
 KanjiAdj2( 短絡的 ) // (adj-na) simplistic/hasty
 KanjiAdj2( 端的 ) // (adj-na) frank/direct/plain/straightforward/point-blank/(P)
 KanjiAdj2( 耽美的 ) // (adj-na) aesthetic/esthetic
 KanjiAdj2( 断続的 ) // (adj-na) intermittent
 KanjiAdj2( 断熱的 ) // (adj-na) adiabatic
 KanjiAdj2( 断片的 ) // (adj-na) fragmentary
 KanjiAdj2( 男性的 ) // (adj-na) manly/(P)
 KanjiAdj2( 知性的 ) // (adj-na) intellectual
 KanjiAdj2( 知的 ) // (adj-na,n) intellectual/(P)
 KanjiAdj2( 知能的 ) // (adj-na) intelligent
 KanjiAdj2( 地域的 ) // (adj-na) regional/local
 KanjiAdj2( 致命的 ) // (adj-na) fatal/lethal/(P)
 KanjiAdj2( 逐語的 ) // (adj-na) word-for-word
 KanjiAdj2( 茶番的 ) // (adj-na) farcical/comical
 KanjiAdj2( 中心的 ) // (adj-na) central
 KanjiAdj2( 抽象的 ) // (adj-na) abstract/(P)
 KanjiAdj2( 挑発的 ) // (adj-na) provocative/suggestive/lascivious/(P)
 KanjiAdj2( 超現実的 ) // (adj-na,n) surrealistic
 KanjiAdj2( 超国家的 ) // (adj-na) ultranationalistic
 KanjiAdj2( 超自然的 ) // (adj-na) supernatural
 KanjiAdj2( 超人的 ) // (adj-na) superhuman
 KanjiAdj2( 超世俗的 ) // (adj-na) unworldly/supermundane/free from worldly cares (concerns)
 KanjiAdj2( 長期的 ) // (adj-na) long term/(P)
 KanjiAdj2( 直感的 ) // (adj-na) intuitive
 KanjiAdj2( 直観的 ) // (adj-na) intuitive
 KanjiAdj2( 直接的 ) // (adj-na,n) direct/(P)
 KanjiAdj2( 通俗的 ) // (adj-na) plain and popular/(P)
 KanjiAdj2( 定期的 ) // (adj-na) periodic/(P)
 KanjiAdj2( 定量的 ) // (adj-na) quantitative
 KanjiAdj2( 帝国主義的 ) // (adj-na) imperialistic
 KanjiAdj2( 的 ) // (adj-na,suf) -like/typical/(P)
 KanjiAdj2( 哲学的 ) // (adj-na) philosophical
 KanjiAdj2( 徹底的 ) // (adj-na,n) thoroughness/(P)
 KanjiAdj2( 典型的 ) // (adj-na) typical/prototypical/representative/stereotypical/model/ideal/(P)
 KanjiAdj2( 天文学的 ) // (adj-na) astronomical
 KanjiAdj2( 伝奇的 ) // (adj-na) legendary
 KanjiAdj2( 伝統的 ) // (adj-na) traditional/conventional/(P)
 KanjiAdj2( 投機的 ) // (adj-na) speculative
 KanjiAdj2( 等方的 ) // (adj-na) isotropic
 KanjiAdj2( 統一的 ) // (adj-na) united/unified
 KanjiAdj2( 統計的 ) // (adj-na) statistical
 KanjiAdj2( 逃避的 ) // (adj-na) evasive
 KanjiAdj2( 動的 ) // (adj-na) dynamic/kinetic
 KanjiAdj2( 同志的 ) // (adj-na) companionable
 KanjiAdj2( 同質的 ) // (adj-na) homogeneous
 KanjiAdj2( 道徳的 ) // (adj-na,n) ethical/moral
 KanjiAdj2( 独裁的 ) // (adj-na) dictatorial
 KanjiAdj2( 独占的 ) // (adj-na) monopolistic
 KanjiAdj2( 独善的 ) // (adj-na) self-righteous
 KanjiAdj2( 独創的 ) // (adj-na) creative/original/(P)
 KanjiAdj2( 突発的 ) // (adj-na) sudden/unexpected
 KanjiAdj2( 内向的 ) // (adj-na) introvert/(P)
 KanjiAdj2( 内在的 ) // (adj-na) immanent/internal/intrinsic
 KanjiAdj2( 内的 ) // (adj-na,n) inner/intrinsic/mental/inherited
 KanjiAdj2( 内罰的 ) // (adj-na,n) (psychology) intropunitive
 KanjiAdj2( 内部的 ) // (adj-na) internal
 KanjiAdj2( 内面的 ) // (adj-na) inner/internal/inside
 KanjiAdj2( 二義的 ) // (adj-na,n) secondary
 KanjiAdj2( 二元的 ) // (adj-na) dual
 KanjiAdj2( 二次的 ) // (adj-na) secondary
 KanjiAdj2( 肉感的 ) // (adj-na,n) sensual
 KanjiAdj2( 肉体的 ) // (adj-na) corporeal/material/(P)
 KanjiAdj2( 肉的 ) // (adj-na,n) physical/fleshly
 KanjiAdj2( 日本的 ) // (adj-na) typically Japanese
 KanjiAdj2( 熱力学的 ) // (adj-na) thermodynamic
 KanjiAdj2( 能動的 ) // (adj-na) active/(P)
 KanjiAdj2( 能率的 ) // (adj-na) efficient
 KanjiAdj2( 派生的 ) // (adj-na) derivative/secondary
 KanjiAdj2( 破壊的 ) // (adj-na) destructive
 KanjiAdj2( 拝外的 ) // (adj-na) proforeign/xenophilous
 KanjiAdj2( 排外的 ) // (adj-na) exclusive/antiforeign
 KanjiAdj2( 排他的 ) // (adj-na) exclusive
 KanjiAdj2( 爆発的 ) // (adj-na) explosive/tremendous
 KanjiAdj2( 発作的 ) // (adj-na) spasmodic(ally)/fitful
 KanjiAdj2( 抜本的 ) // (adj-na) drastic/radical/(P)
 KanjiAdj2( 半永久的 ) // (adj-na) semipermanent
 KanjiAdj2( 半官的 ) // (adj-na) semiofficial
 KanjiAdj2( 反軍的 ) // (adj-na) antimilitary
 KanjiAdj2( 反抗的 ) // (adj-na) rebelliousness/defiance
 KanjiAdj2( 反射的 ) // (adj-na) reflective/reflecting/reflexive/(P)
 KanjiAdj2( 反社会的 ) // (adj-na) antisocial
 KanjiAdj2( 反対称的 ) // (adj-na) antisymmetric
 KanjiAdj2( 反動的 ) // (adj-na) reactionary
 KanjiAdj2( 蛮的 ) // (adj-na) savage/barbarous/rustic
 KanjiAdj2( 否定的 ) // (adj-na) negative/contradictory
 KanjiAdj2( 悲観的 ) // (adj-na) pessimistic/(P)
 KanjiAdj2( 悲劇的 ) // (adj-na) tragic
 KanjiAdj2( 批判的 ) // (adj-na,n) critical/(P)
 KanjiAdj2( 比較的 ) // (adj-na) comparatively/relatively/(P)
 KanjiAdj2( 比喩的 ) // (adj-na) figurative
 KanjiAdj2( 非営利的 ) // (adj-na) nonprofit
 KanjiAdj2( 非科学的 ) // (adj-na) unscientific
 KanjiAdj2( 非現実的 ) // (adj-na) unrealistic
 KanjiAdj2( 非合理的 ) // (adj-na) illogical
 KanjiAdj2( 非実際的 ) // (adj-na) impractical/unpractical
 KanjiAdj2( 非社交的 ) // (adj-na) unsociable/antisocial
 KanjiAdj2( 非循環的 ) // (adj-na) acyclic
 KanjiAdj2( 非生産的 ) // (adj-na) non-business related
 KanjiAdj2( 非良心的 ) // (adj-na) unscrupulous/dishonest/irresponsibly done (work, etc.)
 KanjiAdj2( 非論理的 ) // (adj-na,n) illogical
 KanjiAdj2( 飛躍的 ) // (adj-na) rapidly
 KanjiAdj2( 微視的 ) // (adj-na,n) microscopic
 KanjiAdj2( 美学的 ) // (adj-na) aesthetic
 KanjiAdj2( 美術的 ) // (adj-na) artistic
 KanjiAdj2( 美的 ) // (adj-na,n) esthetic/aesthetic
 KanjiAdj2( 必然的 ) // (adj-na) inevitable/necessary/(P)
 KanjiAdj2( 表面的 ) // (adj-na) on the surface
 KanjiAdj2( 病的 ) // (adj-na,n) abnormal
 KanjiAdj2( 不可知的 ) // (adj-na) agnostic
 KanjiAdj2( 不生産的 ) // (adj-na) unproductive/unfruitful
 KanjiAdj2( 付帯的 ) // (adj-na) incidental/secondary/accessory
 KanjiAdj2( 普遍的 ) // (adj-na) universal/omnipresent/ubiquitous/(P)
 KanjiAdj2( 武断的 ) // (adj-na) militaristic
 KanjiAdj2( 部分的 ) // (adj-na) partial(ly)/(P)
 KanjiAdj2( 封建的 ) // (adj-na) feudal/(P)
 KanjiAdj2( 副次的 ) // (adj-na,n) secondary
 KanjiAdj2( 物質的 ) // (adj-na) material/physical/(P)
 KanjiAdj2( 物的 ) // (adj-na,n) material/physical/(P)
 KanjiAdj2( 物理的 ) // (adj-na) physical
 KanjiAdj2( 分解的 ) // (adj-na) analytical
 KanjiAdj2( 文化的 ) // (adj-na) cultural/(P)
 KanjiAdj2( 文学的 ) // (adj-na) literary
 KanjiAdj2( 文法的 ) // (adj-na) grammatical
 KanjiAdj2( 平和的 ) // (adj-na) peaceful
 KanjiAdj2( 変態的 ) // (adj-na) abnormal
 KanjiAdj2( 弁証法的 ) // (adj-na) dialectic
 KanjiAdj2( 保守的 ) // (adj-na) conservative/(P)
 KanjiAdj2( 包括的 ) // (adj-na) comprehensive
 KanjiAdj2( 包含的 ) // (adj-na) inclusive
 KanjiAdj2( 法的 ) // (adj-na,n) legality/(P)
 KanjiAdj2( 泡沫的 ) // (adj-na) transient/passing/fleeting/ephemeral/like a bubble on liquid
 KanjiAdj2( 牧歌的 ) // (adj-na) pastoral/idyllic
 KanjiAdj2( 没我的 ) // (adj-na) self-effacing/selfless
 KanjiAdj2( 没個性的 ) // (adj-na) impersonal
 KanjiAdj2( 本格的 ) // (adj-na) full-blown/regular/genuine/earnest/normal/typical/fundamental/real/(P)
 KanjiAdj2( 本質的 ) // (adj-na) essentially
 KanjiAdj2( 魔法的 ) // (adj-na) magic
 KanjiAdj2( 末期的 ) // (adj-na) decadent/terminal/(P)
 KanjiAdj2( 末梢的 ) // (adj-na) trivial/minor/insignificant
 KanjiAdj2( 慢性的 ) // (adj-na) chronic/(P)
 KanjiAdj2( 魅力的 ) // (adj-na) charming/fascinating
 KanjiAdj2( 民事的 ) // (adj-na) civil
 KanjiAdj2( 民主的 ) // (adj-na) democratic/(P)
 KanjiAdj2( 民衆的 ) // (adj-na) popular
 KanjiAdj2( 民族的 ) // (adj-na) racial
 KanjiAdj2( 無意識的 ) // (adj-na) unconsciously
 KanjiAdj2( 明示的 ) // (adj-na) explicit
 KanjiAdj2( 模範的 ) // (adj-na) exemplary
 KanjiAdj2( 盲目的 ) // (adj-na,n) blind (devotion)
 KanjiAdj2( 優先的 ) // (adj-na) preferential/(P)
 KanjiAdj2( 友好的 ) // (adj-na) friendly/amicable
 KanjiAdj2( 有意的 ) // (adj-na) intentional/significant
 KanjiAdj2( 有機的 ) // (adj-na) organic
 KanjiAdj2( 遊戯的 ) // (adj-na) playful
 KanjiAdj2( 予備的 ) // (adj-na) preliminary/preparatory
 KanjiAdj2( 利己的 ) // (adj-na) selfish
 KanjiAdj2( 理性的 ) // (adj-na) rational
 KanjiAdj2( 理想的 ) // (adj-na) ideal/(P)
 KanjiAdj2( 理知的 ) // (adj-na,n) intellectual
 KanjiAdj2( 理念的 ) // (adj-na) conceptual
 KanjiAdj2( 理論的 ) // (adj-na) theoretical
 KanjiAdj2( 離散的 ) // (adj-na) discrete/separate
 KanjiAdj2( 立体的 ) // (adj-na) three-dimensional/(P)
 KanjiAdj2( 流動的 ) // (adj-na,n) fluid/unsettled/(P)
 KanjiAdj2( 両性的 ) // (adj-na) bisexual
 KanjiAdj2( 良心的 ) // (adj-na) upright/fair/honest
 KanjiAdj2( 量的 ) // (adj-na,n) substantively/(P)
 KanjiAdj2( 力学的 ) // (adj-na) mechanical
 KanjiAdj2( 力動的 ) // (adj-na) dynamic
 KanjiAdj2( 倫理的 ) // (adj-na) ethical/(P)
 KanjiAdj2( 類型的 ) // (adj-na) stereotyped/patterned/typical
 KanjiAdj2( 例外的 ) // (adj-na) exceptional/(P)
 KanjiAdj2( 冷笑的 ) // (adj-na) sarcastic/derisive
 KanjiAdj2( 霊的 ) // (adj-na,n) spiritual/incorporeal
 KanjiAdj2( 歴史的 ) // (adj-na) historic/historical/traditional/(P)
 KanjiAdj2( 浪花節的 ) // (adj-na) of the old feeling of naniwa-bushi/marked by the dual themes of obligation and compassion that distinguish the naniwa-bushi ballads
 KanjiAdj2( 浪漫的 ) // (adj-na) romantic (school)
 KanjiAdj2( 論理的 ) // (adj-na) logical/(P)
 KanjiAdj2( 刹那的 ) // (adj-na) ephemeral/transitory
 KanjiAdj2( 嗜虐的 ) // (adj-na) sadistic
 KanjiAdj2( 恣意的 ) // (adj-na) selfish
 KanjiAdj2( 蠱惑的 ) // (adj-na) fascinating/alluring
 KanjiAdj2( 衒学的 ) // (adj-na) pedantic


 KanjiAdj3(友好的な) // дружественный
 KanjiAdj3(厚くて) // толстый
 KanjiAdj3(綺麗) // Красивый
 KanjiAdj1( 簡単な )
 KanjiAdj1( 好きな ) // вкусный
 KanjiAdj0( 下手い ) // (adj) not skillful
 KanjiAdj1( 真っ白な ) // белоснежный ???
 KanjiAdj1( 元気な ) // активный
 KanjiAdj1( 賑やか ) // оживленный
 KanjiAdj1( 大変な ) // трудный
 KanjiAdj1( 親切な ) // добрый
 KanjiAdj1( 便利な ) // удобный
 KanjiAdj1( 不便な ) // неудобный
 KanjiAdj1( 有名な ) // известный
 KanjiAdj1( 奇麗な ) // чистый
 KanjiAdj1( 暇な ) // свободный

 KanjiAdj1( 丁寧な ) // вежливый
 KanjiAdj1( 上品な ) // чистый
 KanjiAdj1( マイルドな ) // мягкий
 
}
