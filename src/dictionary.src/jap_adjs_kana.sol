// CD->01.03.2009
// LC->22.10.2013

automat sg
{
 // Для прилагательных, у которых словарная основа заканчивается на い
 #define KanaAdj0(x) entry x : JAP_ADJECTIVE { JAP_FORM:KANA paradigm JapAdj_9700 }

 // Для полупредикативных прилагательных, у которых основа заканчивается на -の или -な 
 #define KanaAdj1(x) entry x : JAP_ADJECTIVE { JAP_FORM:KANA paradigm JapAdj_9701 }

 #define KanaAdj3(x) entry x : JAP_ADJECTIVE { JAP_FORM:KANA paradigm JapAdj_9703 }

 entry いい : JAP_ADJECTIVE
 {
  JAP_FORM:KANA 
  JAP_ADJ_BASE:I    { いい   } // словарная форма
  JAP_ADJ_BASE:II   { よ    } // словообразовательная
  JAP_ADJ_BASE:III  { よく   } // наречно-соединительная
  JAP_ADJ_BASE:IV   { よけれ  } // условная
  JAP_ADJ_BASE:V    { よかろう } // вероятностная
  JAP_ADJ_BASE:T    { よくて  } // серединная
  JAP_ADJ_BASE:PAST { よかった } // прошедшее время
 }

 KanaAdj0( まじめい ) // серьезный (??? проверить)
 KanaAdj0( あくどい ) // (adj) (1) gaudy/showy/excessive/(2) vicious
 KanaAdj0( あざとい ) // (adj) clever/sly/cunning/pushy
 KanaAdj0( あどけない ) // (adj) innocent/cherubic
 KanaAdj0( あられもない ) // (adj) unladylike/unbecoming/immodest
 KanaAdj0( いがらっぽい ) // (adj) irritating
 KanaAdj0( いけない ) // (adj,exp) must not do/bad/wrong/not good/(P)
 KanaAdj0( いけすかない ) // (adj) nasty/disgusting/disagreeable/creepy
 KanaAdj0( いじましい ) // (adj) piddling/paltry
 KanaAdj0( いじらしい ) // (adj) innocent/lovable/sweet/pitiful/pathetic
 KanaAdj0( うざい ) // (ksb:) (adj) (1) annoying/(2) strict
 KanaAdj0( うざったい ) // (ksb:) (adj) (1) annoying/(2) strict
 KanaAdj0( うそさむい ) // (adj) somewhat cold/a bit chilly
 KanaAdj0( えぐい ) // (adj) (1) harsh/acrid/pungent/(2) sharp/biting
 KanaAdj0( えげつない ) // (adj) dirty/vulgar/nasty
 KanaAdj0( えがらっぽい ) // (adj) (uk) acrid/pungent
 KanaAdj0( おっかない ) // (adj) frightening/huge
 KanaAdj0( おっちょこちょい ) // (adj-na,n) careless person/scatterbrain/birdbrain
 KanaAdj0( おもろい ) // (adj) interesting/amusing
 KanaAdj0( かよわい ) // (adj) frail/feeble/(P)
 KanaAdj0( がめつい ) // (adj) greedy/grasping/predatory/calculating/avaricious
 KanaAdj0( きつい ) // (adj) (1) intense/severe/hard/(2) brave/(3) strong/(4) tight/close/(P)
 KanaAdj0( ぎごちない ) // (adj) stiff/awkward/stiff-mannered/crude/unrefined
 KanaAdj0( くだくだしい ) // (adj) tedious/lengthy/wordy/long-winded
 KanaAdj0( けたたましい ) // (adj) piercing/shrill/noisy/loud/clamorous/wild
 KanaAdj0( けったい ) // (adj-na) queer/weird/bizarre
 KanaAdj0( けばい ) // (adj) gawdy/glitzy
 KanaAdj0( こそばゆい ) // (adj) ticklish
 KanaAdj0( こっぴどい ) // (adj) (uk) bad/harsh/severe
 KanaAdj0( このるい ) // (adj-no) this kind
 KanaAdj0( こよない ) // (adj) best/perfect/superb
 KanaAdj0( ごっつい ) // (adj) rough/tough/hard
 KanaAdj0( ごつい ) // (adj) rough/tough/hard
 KanaAdj0( さもしい ) // (adj) selfish/self-seeking/self-interested/mean
 KanaAdj0( しおらしい ) // (adj) meek/gentle/modest/sweet
 KanaAdj0( しがない ) // (adj) poor/humble/wretched
 KanaAdj0( しつこい ) // (adj) insistent/obstinate/(P)
 KanaAdj0( しぶとい ) // (adj) tenacious/stubborn
 KanaAdj0( しょぼい ) // (adj) (1) shabby/dull/(2) gloomy
 KanaAdj0( しんどい ) // (adj) (1) tired/frazzled/(2) tiresome/worrisome/bothersome
 KanaAdj0( すげい ) // (ksb:) (adj) incredible/terrific/impressive
 KanaAdj0( すっとこどっこい ) // (n,adj-na) idiot/fool/idiocy/stupidity
 KanaAdj0( すばしこい ) // (adj) nimble/smart/quick
 KanaAdj0( すばしっこい ) // (adj) nimble/smart/quick
 KanaAdj0( せこい ) // (adj) petty/small-minded/stingy
 KanaAdj0( せせこましい ) // (adj) (1) narrow/limited/(2) fussy
 KanaAdj0( そぐわない ) // (adj) unsuitable/do not match/out of character
 KanaAdj0( そそっかしい ) // (adj) careless/thoughtless/(P)
 KanaAdj0( ぞんざい ) // (adj-na,n) rude/careless/slovenly/(P)
 KanaAdj0( たい ) // (adj) want or would like to do something (suffix on masu stem of verbs)
 KanaAdj0( たどたどしい ) // (adj) with difficulty
 KanaAdj0( たゆまない ) // (adj) untiring/steady/persistent
 KanaAdj0( だらしない ) // (adj) slovenly/loose/sluttish/slatternly/(P)
 KanaAdj0( ちょろい ) // (adj) easy/simple
 KanaAdj0( つれない ) // (adj) cold/indifferent/unfriendly/unsympathetic/unkind
 KanaAdj0( でかい ) // (adj) huge/gargantuan/(P)
 KanaAdj0( でっかい ) // (adj) huge/gargantuan/(P)
 KanaAdj0( とろい ) // (adj) slow (slightly pejorative)/dull/stupid
 KanaAdj0( とんでもない ) // (adj,exp) unexpected/offensive/outrageous/what a thing to say!/no way!/bullshit/(P)
 KanaAdj0( どぎつい ) // (adj) gaudy/loud/garish/violent/harsh
 KanaAdj0( どすぐろい ) // (adj) darkish/dusky
 KanaAdj0( どっこいどっこい ) // (adj) about the same/about equal to/close match
 KanaAdj0( どでかい ) // (adj) huge/gargantuan
 KanaAdj0( どえらい ) // (adj) immense/awesome/enormous/terrific
 KanaAdj0( ねちこい ) // (adj) persistent/obstinate/stubborn/pigheaded
 KanaAdj0( ねちっこい ) // (adj) persistent/obstinate/stubborn/pigheaded
 KanaAdj0( ばっちい ) // (adj) (sl) dirty (word used by kids)/unclean
 KanaAdj0( ひもじい ) // (adj) hungry
 KanaAdj0( ひよわい ) // (adj) weak/sickly
 KanaAdj0( びくともしない ) // (adj) (1) unperturbed/undaunted/retaining composure/(2) unyielding/not giving an inch
 KanaAdj0( ぶっとい ) // (adj) fat/thick
 KanaAdj0( まどろっこしい ) // (adj) dull (e.g. of movement or reaction)/sluggish
 KanaAdj0( みたい ) // (suf,adj-na) -like/sort of/similar to/resembling
 KanaAdj0( みみっちい ) // (adj) tightfisted/stingy/miserly/small-minded
 KanaAdj0( むだにしない ) // (adj) make good use of/make the most of
 KanaAdj0( めんこい ) // (thb:) (adj) lovely/sweet/cute
 KanaAdj0( もどかしい ) // (adj) irritating/not quick enough/tantalizing/tantalising/feel impatient/tardy
 KanaAdj0( やばい ) // (adj) (1) (sl) dangerous/risky/(2) awful (young persons' slang)/terrible/crap/(3) terrific (young persons' slang)/amazing/cool
 KanaAdj0( ややこしい ) // (adj) puzzling/tangled/complicated/complex/(P)
 KanaAdj0( やらしい ) // (adj) unpleasant/disgusting/repulsive/detestable/disagreeable/indecent/lewd/dirty/lascivious
 KanaAdj0( やりこい ) // (tsb:) (adj) soft/tender/limp
 KanaAdj0( よりよい ) // (adj) superior/better
 KanaAdj0( らしい ) // (adj,suf) appears like/seems/(P)
 KanaAdj0( アルカリせい ) // (n,adj-no) alkaline/(P)
 KanaAdj0( アンニュイ ) // (fr:) (n,adj-na) boredom (fr: ennui)/listlessness/languor
 KanaAdj0( エクイティ ) // (n,adj-no) equity
 KanaAdj0( エロい ) // (adj) erotic/pornographic/risque
 KanaAdj0( キショイ ) // (adj) (sl) (col) feel sick/(something is) weird
 KanaAdj0( キモイ ) // (adj) (sl) (abbr) gross/disgusting
 KanaAdj0( グレイ ) // (adj-na,n) grey/gray/(P)
 KanaAdj0( シャイ ) // (adj-na,n) shy/(P)
 KanaAdj0( スタンバイ ) // (n,adj-no) standby
 KanaAdj0( スピーディ ) // (adj-na,n) speedy
 KanaAdj0( セクスィ ) // (adj-na,n) sexy
 KanaAdj0( ドライ ) // (adj-na,n) dry (esp. as in not wet or as in dry humour)/(P)
 KanaAdj0( ナウい ) // (adj) up-to-date (trans: nowy) (slang from the 1980s)
 KanaAdj0( ハイ ) // (adj-na,n) high/(P)
 KanaAdj0( ハンディ ) // (adj-na,n) (1) handy/(2) (abbr) handicap/(P)
 KanaAdj0( バタくさい ) // (adj) Western (lit: smelling of butter)/European/exotic/outlandish/alien
 KanaAdj0( ヘヴィ ) // (adj-na) heavy
 KanaAdj0( ホロにがい ) // (adv,adj) bittersweet/slightly bitter/something that has a strong taste that adults favor
 KanaAdj0( ボールあつかいがうまい ) // (adj) being good at handling a ball
 KanaAdj0( ボロい ) // (adj) (1) profitable/(2) worn-out/crumbling
 KanaAdj0( マレイ ) // (n,adj) Malay
 KanaAdj0( あきゅうせい ) // (adj-no) subacute
 KanaAdj0( あませい ) // (adj-no) flaxen/linen
 KanaAdj0( あほらしい ) // (adj) ridiculous
 KanaAdj0( あほくさい ) // (adj) ridiculous
 KanaAdj0( あゆべんねい ) // (n,adj-no) flattery/adulation/sycophancy
 KanaAdj0( あわれっぽい ) // (adj) plaintive/piteous/doleful
 KanaAdj0( いとおしい ) // (adj) lovely/sweet/precious/adorable
 KanaAdj0( あいくるしい ) // (adj) lovely/cute
 KanaAdj0( いとしい ) // (adj) lovely/dear/beloved/darling/(P)
 KanaAdj0( あいらしい ) // (adj) pretty/charming/lovely
 KanaAdj0( あいそのいい ) // (adj) affable/amiable/sociable/agreeable
 KanaAdj0( わるい ) // (adj) bad/inferior/(P)
 KanaAdj0( いたずらっぽい ) // (adj) (uk) roguish/impish
 KanaAdj0( わるがしこい ) // (adj) cunning/crafty/wily/sly/(P)
 KanaAdj0( あくせい ) // (adj-na,n) malignancy/virulence/malignant (cancer)/pernicious (anemia, anaemia)/(P)
 KanaAdj0( あくみょうだかい ) // (adj) infamous/notorious
 KanaAdj0( あつかいにくい ) // (adj) hard to handle
 KanaAdj0( けんらんかれい ) // (n,adj-na) luxurious and gorgeous/splendid/dazzling/magnificent
 KanaAdj0( やすっぽい ) // (adj) cheap-looking/tawdry/insignificant/(P)
 KanaAdj0( あんい ) // (adj-na,n) easy-going/(P)
 KanaAdj0( あんせい ) // (adj-na,n) rest/(P)
 KanaAdj0( あんたい ) // (adj-na,n) peace/security/tranquility/tranquillity/(P)
 KanaAdj0( あんてい ) // (adj-na,n,vs) stability/equilibrium/(P)
 KanaAdj0( あんねい ) // (adj-na,n) public peace
 KanaAdj0( くらい ) // (adj) (uk) dark/gloomy/(P)
 KanaAdj0( あんがい ) // (adj-na,n-adv) unexpectedly/(P)
 KanaAdj0( あんばい ) // (n,vs) arrangement/assignment/adjustment
 KanaAdj0( いをえない ) // (adj) fail to make sense (of)
 KanaAdj0( いがい ) // (adj-na,adv-to,n) unexpected/surprising/(P)
 KanaAdj0( いくじのない ) // (adj) spineless/backboneless/timid/cowardly/weak-kneed
 KanaAdj0( いぎぶかい ) // (adj) significant/important
 KanaAdj0( いそうがい ) // (adj-na,n,adj-no) unexpected/unsuspected
 KanaAdj0( いじわるい ) // (adj) ill-natured
 KanaAdj0( いじきたない ) // (adj) gluttonous/greedy
 KanaAdj0( いみがとおらない ) // (adj) be incomprehensible/not make sense
 KanaAdj0( やすい ) // (adj,suf) easy/(P)
 KanaAdj0( いかんせんせい ) // (adj-na) compromised
 KanaAdj0( しにくい ) // (adj) hard to do
 KanaAdj0( いせいたい ) // (adj-na,n) isomer/isomeric
 KanaAdj0( いぞんがない ) // (adj) nothing to say/have no objection
 KanaAdj0( いほうせい ) // (adj-na,n) anisotropy
 KanaAdj0( いれい ) // (adj-na,n,adj-no) exception/illness/singular/exceptional/unprecedented/(P)
 KanaAdj0( いこうせい ) // (n,adj-na) (1) portability/upgradability/upwards compatibility/(2) transitional
 KanaAdj0( ちがいない ) // (adj,exp) (phrase) sure/no mistaking it/for certain
 KanaAdj0( いかんにたえない ) // (adj) be really regrettable
 KanaAdj0( いでんせい ) // (adj-na,n) inheritable character/inheritable/hereditary/inherited
 KanaAdj0( そだちがよい ) // (adj) be well-bred
 KanaAdj0( いちい ) // (adj-na,adv,n) unique/earnestness
 KanaAdj0( いっかい ) // (n,adj-no) mere/only a ../(P)
 KanaAdj0( いっこもしない ) // (adj) not give a damn/take no notice of
 KanaAdj0( いっしょけんめい ) // (adj-na,n-adv,n) (1) very hard/with utmost effort/with all one's might/desperately/frantically/for dear life/all-out effort/sticking at living in and defending one place/(2) sticking at living in one place
 KanaAdj0( いっしょうけんめい ) // (adj-na,n-adv,n) very hard/with utmost effort/with all one's might/for dear life/(P)
 KanaAdj0( いっちはんかい ) // (adj-na,n) superficial knowledge/half knowledge
 KanaAdj0( いってい ) // (n,adj-no,vs) fixed/settled/constant/definite/uniform/regularized/regularised/defined/standardized/standardised/certain/prescribed/(P)
 KanaAdj0( いっぱい ) // (adj-na,adv,n) (1) cup of ../drink/(2) full/(3) to the utmost/up to (one's income)/(a) lot of/much/(P)
 KanaAdj0( いっぱいいっぱい ) // (adj-na,n-adv,n) (1) one cup after another/cup by cup/(2) to the limit/to the fullest extent/absolutely the limit/the best one can do/be breaking even
 KanaAdj0( いちばんおおい ) // (adj) most numerous
 KanaAdj0( ひとたまりもない ) // (adj) without difficulty
 KanaAdj0( のみやすい ) // (adj) easy to drink/easy to swallow/quaffable
 KanaAdj0( いんわい ) // (adj-na,n) obscenity/obscene
 KanaAdj0( いんい ) // (n,adj-no) impotence
 KanaAdj0( いんきくさい ) // (adj) dismal/gloomy
 KanaAdj0( おこがましい ) // (adj) (uk) presumptuous/impertinent/ridiculous/absurd
 KanaAdj0( うんがわるい ) // (adj) is unlucky
 KanaAdj0( えいえい ) // (adj-na,adv,n) hard/unceasing
 KanaAdj0( えいめい ) // (adj-na,n) intelligent/wise/bright/brilliant/clear-sighted/(P)
 KanaAdj0( えいまい ) // (adj-na,n) wise and great
 KanaAdj0( するどい ) // (adj) pointed/sharp/(P)
 KanaAdj0( えきせい ) // (adj-na) pH/humoral
 KanaAdj0( いとわしい ) // (adj) detestable/disagreeable
 KanaAdj0( えんすいけい ) // (n,adj-no) cone/cone-shaped
 KanaAdj0( えんすいたい ) // (n,adj-na) cone
 KanaAdj0( えんかい ) // (n) postponement (adjournment) of meeting
 KanaAdj0( けむい ) // (adj) smoky/(P)
 KanaAdj0( けむたい ) // (adj) smoky/feeling awkward/(P)
 KanaAdj0( えんがとおい ) // (adj) distantly related
 KanaAdj0( えんがない ) // (adj) have no relation to
 KanaAdj0( えんどおい ) // (adj) (1) lately married/(2) having little prospect of marriage/(3) unconnected/weakly related
 KanaAdj0( つやっぽい ) // (adj) romantic/spicy/coquettish
 KanaAdj0( えんれい ) // (adj-na,n) dazzling (beauty)
 KanaAdj0( とおい ) // (adj) far/distant/(P)
 KanaAdj0( とおくおよばない ) // (adj) fall far short of/be no equal (match) for
 KanaAdj0( えんかくせい ) // (adj-na) remote
 KanaAdj0( えんせきがい ) // (adj-na,n) far infrared
 KanaAdj0( えんだい ) // (adj-na,n) grand/far-reaching
 KanaAdj0( えんりょのない ) // (adj) unreserved
 KanaAdj0( えんりょぶかい ) // (adj) reserved
 KanaAdj0( しょっぱい ) // (adj) (1) (sl) salty/(2) stingy/(3) hoarse/(4) wearisome
 KanaAdj0( しおからい ) // (adj) salty (taste)/(P)
 KanaAdj0( えんせい ) // (adj-na) saline/halophytic
 KanaAdj0( きたない ) // (adj) dirty/unclean/filthy/(P)
 KanaAdj0( きたならしい ) // (adj) dirty-looking/squalid
 KanaAdj0( けがらわしい ) // (adj) filthy/unfair
 KanaAdj0( おあい ) // (adj-na,n) night soil
 KanaAdj0( おわい ) // (adj-na,n) night soil
 KanaAdj0( おくゆかしい ) // (adj) refined/graceful/modest
 KanaAdj0( おくぶかい ) // (adj) profound/deep
 KanaAdj0( おしもおされもしない ) // (adj) of established reputation
 KanaAdj0( おしつけがましい ) // (adj) pushy/pushing/self-assertive
 KanaAdj0( おうせい ) // (adj-na,n) with vitality
 KanaAdj0( おうへい ) // (adj-na,n) arrogance/haughtiness/insolence/(P)
 KanaAdj0( きいろい ) // (adj) yellow/(P)
 KanaAdj0( おくめんもない ) // (adj) bold/audacious/impudent/unashamed/unabashed
 KanaAdj0( おんきせがましい ) // (adj) condescending/patronizing
 KanaAdj0( ぬるい ) // (adj) (uk) lukewarm/tepid/(P)
 KanaAdj0( おんねつせい ) // (adj-na) thermal
 KanaAdj0( くだらない ) // (adj) good-for-nothing/stupid/trivial/worthless/(P)
 KanaAdj0( かい ) // (n,adj-no) low rank/subordinate/lower order (e.g., byte)/low-end/(P)
 KanaAdj0( かほうしゅうせい ) // (n,vs) downward adjustment/downward revision
 KanaAdj0( なんでもない ) // (adj,exp) easy/trifling/harmless
 KanaAdj0( なんのへんてつもない ) // (adj) ordinary/plain/commonplace
 KanaAdj0( なにげない ) // (adj) casual/unconcerned
 KanaAdj0( いつにない ) // (adj) unusual
 KanaAdj0( かちたかい ) // (adj) valuable
 KanaAdj0( かわいい ) // (adj) (sl) pretty/cute/lovely/charming/dear/darling/pet/(P)
 KanaAdj0( かわゆい ) // (adj) (sl) pretty/cute/lovely/charming/dear/darling/pet
 KanaAdj0( かわいらしい ) // (adj) lovely/sweet/(P)
 KanaAdj0( おかしい ) // (adj) (uk) strange/funny/amusing/ridiculous/(P)
 KanaAdj0( かへんせい ) // (adj-na) versatile
 KanaAdj0( かていをかえりみない ) // (adj) thinking little of one's family
 KanaAdj0( ひまがない ) // (adj) be busy/have no (free) time
 KanaAdj0( はてしがない ) // (adj) endless/boundless/fathomless/eternal
 KanaAdj0( はてしない ) // (adj) endless/boundless/everlasting
 KanaAdj0( ひつきがわるい ) // (adj) be slow to kindle
 KanaAdj0( はなはずかしい ) // (adj) beauty such as to put a flower to shame
 KanaAdj0( かせい ) // (n,adj-no) caustic
 KanaAdj0( いらだたしい ) // (adj) irritation
 KanaAdj0( にやっかい ) // (adj-na,n) encumbrance
 KanaAdj0( はなばなしい ) // (adj) brilliant/magnificent/spectacular
 KanaAdj0( かれい ) // (adj-na,n) splendor/splendour/magnificence/(P)
 KanaAdj0( ががつよい ) // (adj) egoistic/selfish/self-willed
 KanaAdj0( がまんつよい ) // (adj) patient/persevering
 KanaAdj0( げせない ) // (adj,exp) inscrutable/incomprehensible
 KanaAdj0( ときがたい ) // (adj) difficult to solve
 KanaAdj0( まわりくどい ) // (adj) circuitous/roundabout/indirect
 KanaAdj0( かいせつげんかい ) // (n,adj-no) diffraction limit
 KanaAdj0( こわれやすい ) // (adj) fragile/break easily
 KanaAdj0( こころよい ) // (adj) pleasant/agreeable/(P)
 KanaAdj0( なつかしい ) // (adj) dear/desired/missed/(P)
 KanaAdj0( かいい ) // (adj-na,n) brawny/muscular/impressive/gigantic
 KanaAdj0( がいこうせい ) // (n,adj-no) extroversion
 KanaAdj0( がいしけい ) // (n,adj-no) foreign capital group/foreign company
 KanaAdj0( かくがい ) // (adj-na,n,adj-no) nonstandard/extraordinary/special
 KanaAdj0( かっこいい ) // (adj) attractive/good-looking/stylish/cool
 KanaAdj0( かっこういい ) // (ik) (adj) attractive/good-looking/stylish/cool
 KanaAdj0( かっこうのいい ) // (adj-na) attractive/good-looking/stylish/cool
 KanaAdj0( かっこうのわるい ) // (adj-na) unattractive/ugly/unstylish/uncool
 KanaAdj0( かっこうよい ) // (adj) attractive/good-looking/stylish/cool
 KanaAdj0( かっこよい ) // (adj) attractive/good-looking/stylish/cool
 KanaAdj0( かっこうわるい ) // (adj-na) unattractive/ugly/unstylish/uncool
 KanaAdj0( おぼえやすい ) // (adj) be easy to learn
 KanaAdj0( おぼつかない ) // (adj) uncertain/doubtful/unreliable
 KanaAdj0( かどかどしい ) // (adj) intractable/angular
 KanaAdj0( がくがすくない ) // (adj) insufficient (money or things)
 KanaAdj0( かけがえのない ) // (adj-pn) thing with no substitute/money can't buy
 KanaAdj0( わりのいい ) // (adj) paying/remunerative/advantageous/profitable
 KanaAdj0( わりきれない ) // (adj) indivisible/unconvincing/incomprehensible/unaccounted for
 KanaAdj0( われやすい ) // (adj) brittle/fragile/easily cracked/perishable
 KanaAdj0( すべりやすい ) // (adj) greasy/slimy/slippery
 KanaAdj0( こっけい ) // (adj-na,n) funny/humorous/humourous/comical/laughable/ridiculous/joking/(P)
 KanaAdj0( かわきのはやい ) // (adj) fast drying (clothes)
 KanaAdj0( さむい ) // (adj) cold (e.g., weather)/(P)
 KanaAdj0( かんじょうだかい ) // (adj) calculating/mercenary/closefisted
 KanaAdj0( たまらない ) // (adj,exp) (1) intolerable/unbearable/unendurable/(2) cannot help (doing)/cannot but do/anxious to do/(3) tremendous/out of this world/irresistible/(P)
 KanaAdj0( かんれい ) // (n,adj-no) custom/precedent/of convention/(P)
 KanaAdj0( あえない ) // (adj) tragic/tragically
 KanaAdj0( あせくさい ) // (adj) smell(ing) of sweat
 KanaAdj0( あまい ) // (adj,exp) (uk) generous/indulgent/easy-going/sweet/fond of/soft on/overly optimistic/naive/(P)
 KanaAdj0( あまったるい ) // (adj) sentimental/mushy
 KanaAdj0( あまっちょろい ) // (adj) optimistic
 KanaAdj0( あまずっぱい ) // (adj) sweet and sour/bittersweet
 KanaAdj0( あまからい ) // (adj) salty-sweet/bittersweet
 KanaAdj0( かんい ) // (adj-na,n) simplicity/convenience/easiness/quasi-/(P)
 KanaAdj0( ゆるい ) // (adj) loose/lenient/slow/(P)
 KanaAdj0( かんきゅうじざい ) // (n,adj-na) varying the tempo or speed (of something) at will
 KanaAdj0( かんたい ) // (adj-na,n) laxity/negligence
 KanaAdj0( まがいい ) // (adj) be lucky
 KanaAdj0( かんしつせい ) // (adj-no) interstitial
 KanaAdj0( ましゃくにあわない ) // (adj) does not pay/not worth (one's) while
 KanaAdj0( かんせい ) // (adj-na,n) quiet (e.g., neighbourhood, neighborhood)/(P)
 KanaAdj0( まるい ) // (adj) round/circular/spherical/(P)
 KanaAdj0( まるっこい ) // (adj) round/spherical/circular
 KanaAdj0( まるでなってない ) // (adj) not good at all
 KanaAdj0( ふくまれない ) // (adj) not to be included
 KanaAdj0( がんすい ) // (adj-no) hydrated/hydrous
 KanaAdj0( がんこうけいけい ) // (adj-t,adv-to) having piercing eyes/eagle-eyed/having a penetrating insight (into)
 KanaAdj0( がんちゅうにない ) // (adj) think nothing of
 KanaAdj0( がんぜない ) // (adj) innocent/helpless
 KanaAdj0( がんめい ) // (adj-na,n) stubbornness/obstinacy
 KanaAdj0( ねがわしい ) // (adj) desirable
 KanaAdj0( あやうい ) // (adj) dangerous/critical/grave/uncertain/unreliable/limping/narrow/close/watch out!/(P)
 KanaAdj0( あぶない ) // (adj) dangerous/critical/grave/uncertain/unreliable/limping/narrow/close/watch out!/(P)
 KanaAdj0( あぶなげない ) // (adj) safe/certain
 KanaAdj0( あぶなっかしい ) // (adj) dangerous/critical/grave/uncertain/unreliable/limping/narrow/close/watch out
 KanaAdj0( きけんをいとわない ) // (adj) do not mind running a risk
 KanaAdj0( よろこばしい ) // (adj) delightful/joyous/happy/(P)
 KanaAdj0( きい ) // (adj-na,n) odd/strange/wonderful/(P)
 KanaAdj0( きかい ) // (adj-na,n) strange/wonderful/weird/outrageous/mysterious/(P)
 KanaAdj0( きっかい ) // (adj-na,n) strange/wonderful/weird/outrageous/mysterious
 KanaAdj0( ききかいかい ) // (adj-na,n) very strange/bizarre/weird/mysterious
 KanaAdj0( きそうてんがい ) // (adj-na,n) fantastic idea/bizarre
 KanaAdj0( うれしい ) // (adj) happy/glad/pleasant/(P)
 KanaAdj0( よせつけない ) // (adj) keep away/keep off
 KanaAdj0( いまわしい ) // (adj) abominable/(P)
 KanaAdj0( いまいましい ) // (adj) annoying/provoking
 KanaAdj0( きさい ) // (n,adj-no) paid up/already settled
 KanaAdj0( きがいい ) // (adj) good-natured
 KanaAdj0( きがむかない ) // (adj) be not inclined (to do)
 KanaAdj0( きがあらい ) // (adj) bad-tempered/quarrelsome
 KanaAdj0( きがわかい ) // (adj) young at heart
 KanaAdj0( きがおもい ) // (adj) depressed/bummed out/heavy-hearted/heavy-spirited
 KanaAdj0( きがちいさい ) // (adj) timid/faint-hearted/wimpish
 KanaAdj0( きがはやい ) // (adj) short-tempered/quick-tempered/hasty
 KanaAdj0( きがおおい ) // (adj) fickle
 KanaAdj0( きがおおきい ) // (adj) generous/big-hearted
 KanaAdj0( きがみじかい ) // (adj) quick-tempered/having little patience/impatient
 KanaAdj0( きがながい ) // (adj) patient/having a long fuse
 KanaAdj0( きにくわない ) // (adj) unable to stomach/sticking in one's throat
 KanaAdj0( きのない ) // (adj) indifferent/half-hearted/dispirited
 KanaAdj0( きやすい ) // (adj) relaxed/familiar/easy to access/friendly
 KanaAdj0( きうそうだい ) // (n,adj-na) magnanimous in one's attitude of mind/grand in one's idea or mind-set
 KanaAdj0( きえい ) // (adj-na,n,adj-no) spirited/energetic/(P)
 KanaAdj0( きづよい ) // (adj) reassuring/stouthearted
 KanaAdj0( きがるい ) // (adj) cheerful/buoyant/lighthearted
 KanaAdj0( きづかわしい ) // (adj) anxiously/with anxious looks/with anxiety
 KanaAdj0( けだかい ) // (adj) sublime
 KanaAdj0( きもちいい ) // (adj) good feeling/feeling good
 KanaAdj0( きもちよい ) // (adj) good feeling/feeling good
 KanaAdj0( きもちわるい ) // (adj) bad feeling/feeling bad
 KanaAdj0( きのりしない ) // (adj) indisposed/halfhearted
 KanaAdj0( きずい ) // (adj-na,n) willful/wilful/as one pleases
 KanaAdj0( けだるい ) // (adj) languid/listless
 KanaAdj0( きはずかしい ) // (adj) embarrassed/feeling ashamed or awkward
 KanaAdj0( きむずかしい ) // (adj) hard to please/moody/crusty/fastidious/(P)
 KanaAdj0( きむづかしい ) // (adj) hard to please/moody/crusty/fastidious
 KanaAdj0( きまずい ) // (adj) (uk) unpleasant/awkward
 KanaAdj0( きぶんがよい ) // (adj) feel good (pleasant)
 KanaAdj0( きぜわしい ) // (adj) restless/fidgety/fussy
 KanaAdj0( きりょくおうせい ) // (n,adj-na) being full of energy (drive, motivation, vitality)
 KanaAdj0( きままほうだい ) // (n,adj-na) as selfishly (willfully) as one pleases
 KanaAdj0( きせつちょうせい ) // (n) seasonal adjustment
 KanaAdj0( きだい ) // (adj-no) uncommon/rare
 KanaAdj0( きそくただしい ) // (adj) regular/well-regulated/systematic
 KanaAdj0( きてい ) // (n,adj-no,vs) regulation/provisions/(P)
 KanaAdj0( きどうしゅうせい ) // (n) orbital adjustment
 KanaAdj0( かがやかしい ) // (adj) brilliant/glorious/glittering/(P)
 KanaAdj0( ぎせい ) // (adj-na) pseudo
 KanaAdj0( よろしい ) // (adj) (hon) good/OK/all right/fine/very well/will do/may/can/(P)
 KanaAdj0( うたがいぶかい ) // (adj) doubting/distrustful/incredulous/suspicious
 KanaAdj0( うたがわしい ) // (adj) doubtful/questionable/uncertain/disputable/suspicious/(P)
 KanaAdj0( ぎりがたい ) // (adj) possessed of a strong sense of duty
 KanaAdj0( つまらない ) // (adj) (1) (uk) dull/uninteresting/boring/(2) insignificant/trifling/(P)
 KanaAdj0( ひさしい ) // (adj) long/long-continued/old (story)/(P)
 KanaAdj0( きゅうかい ) // (n,vs) adjournment/recess
 KanaAdj0( およびがたい ) // (adj) hard to attain to
 KanaAdj0( きゅうけい ) // (n,adj-no) globular or spherical shape
 KanaAdj0( きゅうへい ) // (adj-na,n) old-fashioned/conservatism/standing evil/the old school/antiquated
 KanaAdj0( きゅうらい ) // (adj-no,n-adv,n-t) traditional/from ancient times/formerly/(P)
 KanaAdj0( いもしない ) // (adj) (1) (uk) invisible/unseen/(2) vague/mysterious/(3) imaginary
 KanaAdj0( いごこちがわるい ) // (adj) uncomfortable/ill at ease/not feel at home
 KanaAdj0( きょさい ) // (adj-na,n) large and small matters/particulars/details/greatness and smallness/circumstances
 KanaAdj0( こさい ) // (adj-na,n) large and small matters/particulars/details/greatness and smallness/circumstances
 KanaAdj0( きょだい ) // (adj-na,n) huge/gigantic/enormous/(P)
 KanaAdj0( きょけつせい ) // (adj-no) ischemic
 KanaAdj0( きょうけい ) // (adj-pn) conformal (mathematics, physics)
 KanaAdj0( つよい ) // (adj) strong/powerful/mighty/potent/(P)
 KanaAdj0( きょうせい ) // (adj-na,n) splendid/great/magnificent
 KanaAdj0( きょうだい ) // (adj-na,n) mighty/powerful/(P)
 KanaAdj0( おそれおおい ) // (adj) awesome/awe-inspiring/august
 KanaAdj0( おそろしい ) // (adj) terrible/dreadful/(P)
 KanaAdj0( うやうやしい ) // (adj) respectful/reverent
 KanaAdj0( くるおしい ) // (adj) crazy about/maddening
 KanaAdj0( せまい ) // (adj) narrow/confined/small/(P)
 KanaAdj0( せまくるしい ) // (adj) cramped
 KanaAdj0( きょうあい ) // (adj-na,n) narrow
 KanaAdj0( むなぐるしい ) // (adj) (feeling of) tightness in the chest
 KanaAdj0( むなくそがわるい ) // (adj) annoying
 KanaAdj0( きょうみがうすい ) // (adj) uninteresting
 KanaAdj0( きょうみぶかい ) // (adj) very interesting/of great interest/(P)
 KanaAdj0( きょうみほんい ) // (adj-na,n,adj-no) popular (literature, etc.)
 KanaAdj0( ぎょうぎょうしい ) // (adj) exaggerated/bombastic/highly colored/highly coloured
 KanaAdj0( ごうがふかい ) // (adj) be past redemption/be sinful
 KanaAdj0( まげやすい ) // (adj) pliant/supple/flexible
 KanaAdj0( きょくのない ) // (adj) uninteresting/dull
 KanaAdj0( まがまがしい ) // (adj) (1) (uk) ominous/sinister/unlucky/ill-omened/(2) annoying/(3) appearing to be true
 KanaAdj0( きわまりない ) // (adj) extremely/in the extreme/boundless/limitless
 KanaAdj0( きょくだい ) // (adj-na,n) maximum
 KanaAdj0( つとまらない ) // (adj) unfit for/unequal to
 KanaAdj0( すじちがい ) // (adj-na,n) cramp/sprain/illogical/intersection/(P)
 KanaAdj0( ちかい ) // (adj,suf) near/close by/short/(P)
 KanaAdj0( きんかい ) // (n) coastal waters/adjacent seas/(P)
 KanaAdj0( かねくい ) // (adj) money-eating/expensive/extravagant
 KanaAdj0( きんせんにこまかい ) // (adj) skimpy about money
 KanaAdj0( きんぞくせい ) // (n,adj-no) made of metal
 KanaAdj0( ぎんがけい ) // (n,adj-no) galaxy/galactic system
 KanaAdj0( にがい ) // (adj) bitter/(P)
 KanaAdj0( くるしい ) // (adj) painful/difficult/(P)
 KanaAdj0( にがにがしい ) // (adj) unpleasant/disgusting/loathsome/shameful/scandalous
 KanaAdj0( くたい ) // (n,adj-no) (1) body/skeleton/framework/(2) reinforced concrete skeletal soundness
 KanaAdj0( おろかしい ) // (adj) foolish/stupid
 KanaAdj0( ぐまい ) // (adj-na,n) stupid
 KanaAdj0( むなしい ) // (adj) vacant/futile/vain/void/empty/ineffective/lifeless/(P)
 KanaAdj0( そらおそろしい ) // (adj) having vague fears
 KanaAdj0( そらぞらしい ) // (adj) false/hypocritical
 KanaAdj0( そらたかい ) // (adj) high in the sky
 KanaAdj0( そらはずかしい ) // (adj) feeling ashamed or embarrassed without knowing why
 KanaAdj0( ぐうせい ) // (n,adj-no) impromptu
 KanaAdj0( すみにおけない ) // (adj) be witty and knowing
 KanaAdj0( くったくのない ) // (adj) carefree/free from worry
 KanaAdj0( けったくそわるい ) // (adj) (vulg) extremely vexing
 KanaAdj0( けいけんがあさい ) // (adj) having little experience
 KanaAdj0( はかりしれない ) // (adj,exp) unfathomable/inestimable/immeasurable/(P)
 KanaAdj0( けいかくせい ) // (n,adj-no) planning/planning ability/deliberateness
 KanaAdj0( けいさんだかい ) // (adj) calculating
 KanaAdj0( かるい ) // (adj) light/non-serious/minor/(P)
 KanaAdj0( けいい ) // (adj-na,n) easy/light/simple
 KanaAdj0( けいかい ) // (adj-na,n) rhythmical (e.g., melody)/casual (e.g., dress)/light/nimble/(P)
 KanaAdj0( かるがるしい ) // (adj) indiscreet/thoughtless/careless/frivolous
 KanaAdj0( けたちがい ) // (adj-na,n) off by a digit/in a different league/incomparable
 KanaAdj0( きまりわるい ) // (adj) feeling awkward/being ashamed
 KanaAdj0( けついがかたい ) // (adj) be firmly determined
 KanaAdj0( いさぎよい ) // (adj) manly/sportsmanlike/pure/upright/(P)
 KanaAdj0( いさぎよしとしない ) // (adj) find it against one's conscience (to do)/be too proud (to do)
 KanaAdj0( けっしょうせい ) // (adj-pn) crystalline
 KanaAdj0( ちなまぐさい ) // (adj) bloody/bloody stench
 KanaAdj0( つましい ) // (adj) thrifty/economical
 KanaAdj0( けんこうによい ) // (adj) be good for the health
 KanaAdj0( けんざい ) // (adj-na,n) in good health/well/(P)
 KanaAdj0( やかましい ) // (adj) (1) noisy/boisterous/(adj) (2) strict/faultfinding/carping/fussy/(P)
 KanaAdj0( けんかばやい ) // (adj) quarrelsome
 KanaAdj0( きらい ) // (adj-na,n) (1) dislike/hate/(2) (suff) suspicion/tendency/smack (of)/(P)
 KanaAdj0( いやらしい ) // (adj) unpleasant/disgusting/repulsive/detestable/disagreeable/indecent/lewd/dirty/lascivious
 KanaAdj0( けんきょうふかい ) // (n,adj-no) farfetched (argument, opinion)/forced (sense, view)/strained (interpretation)/distorted
 KanaAdj0( かたみがせまい ) // (adj) feeling ashamed
 KanaAdj0( みっともない ) // (adj) (uk) shameful/indecent/(P)
 KanaAdj0( みやすい ) // (adj) easy to see
 KanaAdj0( みぐるしい ) // (adj) unsightly/ugly/(P)
 KanaAdj0( みよい ) // (adj) pleasant to look at/easy to see
 KanaAdj0( みすぼらしい ) // (adj) shabby/seedy/(P)
 KanaAdj0( みあたらない ) // (adj) not be found/(P)
 KanaAdj0( けんとうちがい ) // (adj-na,n) wrong (guess or estimate)/misdirected
 KanaAdj0( みめよい ) // (adj) good-looking
 KanaAdj0( みめうるわしい ) // (adj) good-looking/fair/beautiful
 KanaAdj0( かしこい ) // (adj) wise/clever/smart/(P)
 KanaAdj0( けんめい ) // (adj-na,n) wisdom/intelligence/prudence/(P)
 KanaAdj0( やりきれない ) // (adj) intolerable/unbearable
 KanaAdj0( やるせない ) // (adj) helpless/cheerless/miserable/disconsolate/dreary/downhearted
 KanaAdj0( けわしい ) // (adj) inaccessible place/impregnable position/steep place/sharp eyes/(P)
 KanaAdj0( げんきいっぱい ) // (adj-na,adv,n) be brimming with health (vigor)/be full of pep
 KanaAdj0( げんきおうせい ) // (n,adj-na) be brimming with vitality/be full of vigor (life)
 KanaAdj0( げんけい ) // (n,adj-no) prototype/model/pattern/archetypal/(P)
 KanaAdj0( いかつい ) // (adj) grim/stern
 KanaAdj0( いかめしい ) // (adj) (1) severe/strict/rigid/unsparing/relentless/(2) stern/austere/grave/solemn/majestic/(3) intense (cold)
 KanaAdj0( げんせい ) // (adj-na,n) strictness/impartiality/exactness/rigidness
 KanaAdj0( げんだい ) // (adj-no,n-adv,n) nowadays/modern times/present-day/(P)
 KanaAdj0( いいなりほうだい ) // (adj-na) completely submissive to another person
 KanaAdj0( いうまでもない ) // (adj,exp) it goes without saying/there is no need to say so, but of course/it is needless to say/it need scarcely be said
 KanaAdj0( いいづらい ) // (adj) difficult to speak about
 KanaAdj0( いいがたい ) // (adj) hard to say/inexpressible/hesitant to say
 KanaAdj0( いいにくい ) // (adj) hard to say/inexpressible/hesitant to say
 KanaAdj0( いいわけがたたない ) // (adj) admit no excuse
 KanaAdj0( ことばにあらわせない ) // (adj) ineffable/inexpressible
 KanaAdj0( かぎりない ) // (adj) eternal/unlimited/endless
 KanaAdj0( ふるい ) // (adj) old (not person)/aged/ancient/antiquated/stale/threadbare/outmoded/obsolete article/(P)
 KanaAdj0( ふるめかしい ) // (adj) old-fashioned
 KanaAdj0( ふるくさい ) // (adj) stale/old fashioned/hackneyed/trite/(P)
 KanaAdj0( こらい ) // (adj-no,adv,n) from time immemorial/ancient/time-honoured/time-honored/(P)
 KanaAdj0( かたぐるしい ) // (adj) formal/strict/ceremonious/stiff
 KanaAdj0( ころうがんめい ) // (n,adj-na) obstinate/stubborn/hard-headed/being incapable of making sound judgments because of a narrow, inflexible and obstinate mentality
 KanaAdj0( こがい ) // (n,adj-no) open-air/outdoors/(P)
 KanaAdj0( うさんくさい ) // (adj) suspicious looking/shady
 KanaAdj0( ほこらしい ) // (adj) proud/haughty/arrogant/splendid/magnificent
 KanaAdj0( ほこりたかい ) // (adj) proud/lordly
 KanaAdj0( こだい ) // (adj-na,n) exaggeration/hyperbole/(P)
 KanaAdj0( こようちょうせい ) // (n) employment adjustment
 KanaAdj0( ごめんたい ) // (n,adj-no) pentahedron
 KanaAdj0( たがいちがい ) // (adj-na,n) alternate/alternation/(P)
 KanaAdj0( うしろめたい ) // (adj) guilty
 KanaAdj0( うしろぐらい ) // (adj) shady/back or underhanded
 KanaAdj0( おさむい ) // (adj) poor/unsatisfactory/inadequate
 KanaAdj0( ごきげんうるわしい ) // (adj) be in good humor (humour)
 KanaAdj0( おたかい ) // (adj) haughty
 KanaAdj0( おせっかい ) // (adj-na,n) meddling/nosy
 KanaAdj0( おなみだちょうだい ) // (n,adj-no) tearjerker/sob story/maudlin tale
 KanaAdj0( こうさいぎらい ) // (adj) unsociable
 KanaAdj0( こうえい ) // (adj-na,n) honour/honor/glory/privilege/(P)
 KanaAdj0( こうへい ) // (adj-na,n) fairness/impartial/justice/(P)
 KanaAdj0( こうめいせいだい ) // (adj-na,n) fairness/just and upright/aboveboard
 KanaAdj0( あつかましい ) // (adj) impudent/shameless/brazen/(P)
 KanaAdj0( あつぼったい ) // (adj) very thick/heavy
 KanaAdj0( くちがわるい ) // (adj) sarcastic/having a sharp (nasty) tongue
 KanaAdj0( くちがかるい ) // (adj) having a loose tongue/being talkative
 KanaAdj0( くちがおもい ) // (adj) incommunicative/taciturn
 KanaAdj0( くちがうまい ) // (adj) honeymouthed/glib/fair-spoken/cajoling/talking glibly
 KanaAdj0( くちがおおい ) // (adj) having a large family to support
 KanaAdj0( くちがない ) // (adj) being unable to find a job
 KanaAdj0( くちぎたない ) // (adj) foul-mouthed/abusive
 KanaAdj0( くちぎれい ) // (adj-na,n) speaking elegantly/speaking clearly/not coveting food/speaking like an innocent person
 KanaAdj0( くちやかましい ) // (adj) nagging/talkative/gossipy
 KanaAdj0( くちがたい ) // (adj) discreet/tight-lipped
 KanaAdj0( こうさい ) // (adj-na,n) clever speech
 KanaAdj0( くちさびしい ) // (adj) longing to have or put something in one's mouth
 KanaAdj0( くちおもい ) // (adj) slow of speech/prudent
 KanaAdj0( くちさがない ) // (adj) gossipy/abusive/critical/jabbering
 KanaAdj0( くちおしい ) // (adj) regrettable/mortifying/vexing
 KanaAdj0( くやしい ) // (adj) regrettable/mortifying/vexing
 KanaAdj0( くちうるさい ) // (adj) nagging/faultfinding/carping/captious
 KanaAdj0( くちはばったい ) // (adj) bragging/impudence
 KanaAdj0( すきほうだい ) // (adj-na,n) doing as one pleases
 KanaAdj0( このましい ) // (adj) nice/likeable/desirable/(P)
 KanaAdj0( こういっつい ) // (adj-na,n) well-matched
 KanaAdj0( さいわい ) // (adj-na,adv,n) happiness/blessedness/(P)
 KanaAdj0( こうはんい ) // (adj-na,n) extensive/vast range/wide scope/(P)
 KanaAdj0( ひろい ) // (adj) spacious/vast/wide
 KanaAdj0( さらさらない ) // (adj) not in the least
 KanaAdj0( かまわない ) // (adj) be indifferent (to)/do not care (mind)
 KanaAdj0( こうない ) // (n,adj-no) premises/grounds/campus/in-house/(P)
 KanaAdj0( たよりがない ) // (adj) useless/in vain
 KanaAdj0( かいがいしい ) // (adj) gallant/heroic/brave
 KanaAdj0( ぬかみそくさい ) // (adj) overly concerned with domestic affairs
 KanaAdj0( かんがえられない ) // (adj) unimaginable
 KanaAdj0( かんがえぶかい ) // (adj) thoughtful/deep-thinking
 KanaAdj0( あらっぽい ) // (adj) rough/rude/(P)
 KanaAdj0( あれほうだい ) // (adj-na,n) gone to ruin
 KanaAdj0( あらあらしい ) // (adj) desolate/rough/wild/rude/harsh/gruff/violent
 KanaAdj0( こうとうむけい ) // (adj-na,n) absurdity/nonsense/preposterous
 KanaAdj0( いきたくない ) // (adj) do not want to go
 KanaAdj0( こうばしい ) // (adj) sweet/fragrant/aromatic/savory/savoury/(P)
 KanaAdj0( たかい ) // (adj) (1) high/tall/(2) expensive/(P)
 KanaAdj0( こうい ) // (adj-na,n) (1) dignity/eminent/high ranking/(2) high-order (digit, bit, etc.)/(P)
 KanaAdj0( こうしせい ) // (adj-na,n) high profile/aggressive attitude
 KanaAdj0( こうだい ) // (adj-na) lofty/grand/impressive
 KanaAdj0( こうでんい ) // (adj-na) high-voltage
 KanaAdj0( こうめい ) // (adj-na,n) fame/renown/(P)
 KanaAdj0( えらい ) // (adj) great/celebrated/eminent/terrible/awful/famous/remarkable/excellent
 KanaAdj0( ごうかい ) // (adj-na,n) hearty/exciting/stirring/lively/heroic/largehearted/splendid/(P)
 KanaAdj0( ごうまい ) // (adj-na,n) intrepidity/indomitableness
 KanaAdj0( こくめい ) // (adj-na,n) detailed/elaborate/faithfulness/diligence/conscientiousness/(P)
 KanaAdj0( きびしい ) // (adj) (1) severe/strict/rigid/unsparing/relentless/(2) stern/austere/grave/solemn/majestic/(3) intense (cold)
 KanaAdj0( くろい ) // (adj) (1) black/(2) dark/(P)
 KanaAdj0( くろっぽい ) // (adj) dark/blackish/(P)
 KanaAdj0( ほねっぽい ) // (adj) bony/tough/plucky/spirited/hard to deal with
 KanaAdj0( いまめかしい ) // (adj) fashionable
 KanaAdj0( うらめしい ) // (adj) reproachful/hateful/bitter
 KanaAdj0( こんい ) // (adj-na,n) kindness/intimacy/friendship/(P)
 KanaAdj0( こんせつていねい ) // (n,adj-na) (an explanation, advice, etc. being) kind, careful, and thorough
 KanaAdj0( こんきょのない ) // (adj) baseless/groundless
 KanaAdj0( ねづよい ) // (adj) firmly rooted/deep-seated/(P)
 KanaAdj0( ねぶかい ) // (adj) deep-rooted/ingrained
 KanaAdj0( ささい ) // (adj-na,n) trivial/slight
 KanaAdj0( さしでがましい ) // (adj) forward/officious/impertinent/intrusive
 KanaAdj0( さしさわりのない ) // (adj) innocuous/inoffensive
 KanaAdj0( さしむかい ) // (adj) face to face
 KanaAdj0( さいちょうせい ) // (n) readjustment/realignment
 KanaAdj0( さいてい ) // (adj-na,adv,n) (1) least/lowest/worst/(2) nasty/disgusting/horrible/yuck!/(P)
 KanaAdj0( すまない ) // (adj,exp) sorry (phrase)/(P)
 KanaAdj0( ほそい ) // (adj) thin/slender/fine/(P)
 KanaAdj0( こまかい ) // (adj) (1) small/(2) fine/minute/(P)
 KanaAdj0( ほそながい ) // (adj) long and narrow/(P)
 KanaAdj0( きわどい ) // (adj) dangerous/risky/hazardous/close/delicate/suggestive
 KanaAdj0( ざいこちょうせい ) // (n) inventory (stock) adjustment
 KanaAdj0( ざいらい ) // (n,adj-no) pre-existing/already there/conventional/(P)
 KanaAdj0( つみのない ) // (adj) guiltless/innocent
 KanaAdj0( つみぶかい ) // (adj) sinful
 KanaAdj0( さっぷうけい ) // (adj-na,n) tasteless/dreary/tastelessness
 KanaAdj0( さんかくけい ) // (n,adj-no) triangle/three-cornered polygon/(P)
 KanaAdj0( さんかっけい ) // (n,adj-no) triangle/three-cornered polygon
 KanaAdj0( みかづきけい ) // (adj-no) crescent shape
 KanaAdj0( むごい ) // (adj) cruel/atrocious/merciless/inhuman/brutal
 KanaAdj0( さんかい ) // (n,vs) adjournment/(P)
 KanaAdj0( そろばんだかい ) // (adj) calculating/miserly
 KanaAdj0( すっぱい ) // (adj) sour/acid/(P)
 KanaAdj0( のこりおしい ) // (adj) regrettable/reluctant
 KanaAdj0( しかねない ) // (adj) capable of anything
 KanaAdj0( しきれない ) // (adj) impossible to do
 KanaAdj0( しほうだい ) // (adj-na,n) having one's own way
 KanaAdj0( しかたがない ) // (adj,exp) it can't be helped/it's inevitable/it's no use/can't stand it/being impatient/being annoyed
 KanaAdj0( しかたない ) // (adj) it can't be helped/it's inevitable/it's no use/can't stand it/impatient/annoyed
 KanaAdj0( しようのない ) // (adj) hopeless/good-for-nothing/incorrigible
 KanaAdj0( つかいやすい ) // (adj) (uk) easy to use
 KanaAdj0( つかいものにならない ) // (adj) be no use
 KanaAdj0( とげとげしい ) // (adj) sharp/harsh/stinging/thorny/snappy
 KanaAdj0( しじょうにれいをみない ) // (adj) be unparalleled in history (unparallelled)
 KanaAdj0( しかくい ) // (adj) square/(P)
 KanaAdj0( しぶんい ) // (n,adj-no) quartile
 KanaAdj0( しきおうせい ) // (n,adj-na) morale being very high/heightened fighting spirit
 KanaAdj0( しせいぶらい ) // (n,adj-no) urban villain/street hoodlum
 KanaAdj0( しない ) // (n,adj-no) (within a) city/local/(P)
 KanaAdj0( おもいもよらない ) // (adj) unexpected/unforeseen/inconceivable
 KanaAdj0( おもいがけない ) // (adj) unexpected/contrary to unexpectations/by chance/casual
 KanaAdj0( おぼしい ) // (adj) apparently
 KanaAdj0( おもわしい ) // (adj) suitable/satisfactory/desirable
 KanaAdj0( おもわしくない ) // (adj) disappointing/unsatisfactory/unsuitable
 KanaAdj0( しそうがかたまっていない ) // (adj) have no fixed ideas
 KanaAdj0( うまくいかない ) // (adj) be unsuccessful/go badly
 KanaAdj0( やみがたい ) // (adj) irresistible
 KanaAdj0( やんごとない ) // (adj) (uk) high class/esteemed/cherished
 KanaAdj0( ししるいるい ) // (n,adj-t,adv-to) heaps of corpses all around
 KanaAdj0( いたらない ) // (adj) imperfect/incompetent
 KanaAdj0( しじゅんしせい ) // (n,adj-na,adj-no) utmost purity
 KanaAdj0( しだい ) // (adj-na,n) immense/enormous
 KanaAdj0( ししつえいめい ) // (n,adj-na) wise and clear-sighted/intelligent and astute by nature/blessed with talents
 KanaAdj0( しせいえいめい ) // (n,adj-na) wise and clear-sighted/intelligent and astute by nature/blessed with talents
 KanaAdj0( しせいたんせい ) // (n,adj-na) being of an upright character/being of a noble nature
 KanaAdj0( しせい ) // (adj-na,n) female
 KanaAdj0( はがたたない ) // (adj) hard to chew/unable to compete with
 KanaAdj0( はにきぬをきせない ) // (adj) not mince matters
 KanaAdj0( しがにかけない ) // (adj) no argument necessary
 KanaAdj0( はがゆい ) // (adj) impatient/tantalized/tantalised/irritated/chagrined/chagrinned/vexed/(P)
 KanaAdj0( ことかかない ) // (adj) having an abundance
 KanaAdj0( ことごとしい ) // (adj) bombastic/pretentious/exaggerated
 KanaAdj0( ことあたらしい ) // (adj) new
 KanaAdj0( にげない ) // (adj) unlike/unbecoming/unworthy of/out of keeping with
 KanaAdj0( にあい ) // (n,adj-no) well-matched/becoming/suitable/(P)
 KanaAdj0( にあわしい ) // (adj) well-matched/suitable/becoming
 KanaAdj0( につかわしい ) // (adj) suitable/appropriate/becoming
 KanaAdj0( もってこい ) // (adj-na,exp) just right/ideal/perfectly suitable
 KanaAdj0( みみどおい ) // (adj) (1) hard of hearing/(2) unfamiliar
 KanaAdj0( みみあたらしい ) // (adj) novel/new/unfamiliar/hear for the first time
 KanaAdj0( みみざとい ) // (adj) sharp-eared/have sharp ears/picks things up fast
 KanaAdj0( じざい ) // (adj-na,n) freely/at will/(P)
 KanaAdj0( じめい ) // (adj-na,n,adj-no) obvious/self-evident/axiomatic/self-explanatory/(P)
 KanaAdj0( じゆうざんまい ) // (n,adj-na) free/unfettered/according to one's own whims/doing as one likes
 KanaAdj0( じゆうじざい ) // (adj-na,n) freely
 KanaAdj0( しかつめらしい ) // (adj) formal/solemn
 KanaAdj0( しゅうねんぶかい ) // (adj) vindictive/tenacious/persistent/spiteful/vengeful
 KanaAdj0( しっけい ) // (adj-na,int,n,vs) rudeness/saying good-bye/acting impolitely/stealing/impoliteness/disrespect/impertinence/(P)
 KanaAdj0( しっぱい ) // (n,adj-no,vs) failure/mistake/blunder/(P)
 KanaAdj0( しつれい ) // (n,vs,adj-na,exp) (1) discourtesy/impoliteness/(2) Excuse me/Goodbye/(P)
 KanaAdj0( しっとぶかい ) // (adj) deep jealousy
 KanaAdj0( しつない ) // (n,adj-no) indoor/inside the room/(P)
 KanaAdj0( しめっぽい ) // (adj) damp/gloomy/(P)
 KanaAdj0( じちらしい ) // (adj) honest (appearance)/sincere (impression)
 KanaAdj0( じつげんかのうせい ) // (n,adj-no) feasibility
 KanaAdj0( じっさい ) // (adj-no,adv,n) practical/actual condition/status quo/(P)
 KanaAdj0( じっせい ) // (n,adj-no) actual/real/true/(P)
 KanaAdj0( じつようほんい ) // (n,adj-no) pragmatism/functionalism/practicality/being intended for practical purposes
 KanaAdj0( じつりょくほんい ) // (n,adj-no) the precedence of merit/performance orientation/ability- (merit-) based (promotion, pay scale, etc.)
 KanaAdj0( にえきらない ) // (adj,exp) half-cooked/vague/halfhearted/indecisive
 KanaAdj0( しゃせい ) // (adj-na) company manufactured
 KanaAdj0( しゃない ) // (n,adj-no) within a company/in-house/(P)
 KanaAdj0( しゃさい ) // (n,adj-no) in-vehicle/on-board
 KanaAdj0( じゃまくさい ) // (adj,exp) troublesome/pain in the butt
 KanaAdj0( わかい ) // (adj) young/(P)
 KanaAdj0( わかわかしい ) // (adj) youthful/young
 KanaAdj0( よわい ) // (adj) weak/frail/delicate/tender/unskilled/weak (wine)/(P)
 KanaAdj0( よわよわしい ) // (adj) frail/slender/feminine
 KanaAdj0( じゃくたい ) // (adj-na,n) weak (organization, organisation)/(P)
 KanaAdj0( よわもちあい ) // (adj) (stock market) barely holding steady
 KanaAdj0( とりとめのない ) // (adj) incoherent/wandering/vague/rambling/whimsical
 KanaAdj0( てがたりない ) // (adj) be short of hands
 KanaAdj0( てっとりばやい ) // (adj) quick (and easy)/finishing up in a hurry
 KanaAdj0( ていっぱい ) // (adj-na,n) having one's hands full
 KanaAdj0( てぬるい ) // (adj) lax/lenient/slow
 KanaAdj0( てごわい ) // (adj) difficult/tough/stubborn/redoubtable
 KanaAdj0( てづよい ) // (adj) strong/resolute/firm/strict
 KanaAdj0( てがたい ) // (adj) steady/firm/solid/secure/(P)
 KanaAdj0( てきびしい ) // (adj) severe/harsh
 KanaAdj0( てあつい ) // (adj) courteous
 KanaAdj0( てびろい ) // (adj) spacious/roomy
 KanaAdj0( てひどい ) // (adj) severe/harsh
 KanaAdj0( てばやい ) // (adj) nimble/(P)
 KanaAdj0( てみじかい ) // (adj) short/brief
 KanaAdj0( ていたい ) // (adj) severe/hard/(P)
 KanaAdj0( てぬい ) // (n,adj-no) hand-tailored/hand-sewn
 KanaAdj0( てぎれい ) // (adj-na) neatly or cleverly made
 KanaAdj0( しゅだい ) // (adj-na,n) swelling
 KanaAdj0( さけくさい ) // (adj) reek of liquor
 KanaAdj0( うけがわるい ) // (adj) unpopular (with)/in the bad books
 KanaAdj0( うけがよい ) // (adj) popular (with)
 KanaAdj0( しゅうない ) // (adj-no) intrastate
 KanaAdj0( しゅうせい ) // (n,vs) adjustment/retouching (in photography)
 KanaAdj0( しゅうれい ) // (adj-na,n) graceful/beautiful
 KanaAdj0( くさい ) // (adj) stinking/(P)
 KanaAdj0( みにくい ) // (adj) ugly/(P)
 KanaAdj0( しゅうかい ) // (adj-na) monstrous/hideous/ugly/bizarre
 KanaAdj0( じゅうじけい ) // (adj-na) cross/cruciform
 KanaAdj0( しぶい ) // (adj) (1) tasteful (clothing)/cool/an aura of refined masculinity/(2) astringent/sullen/bitter (taste)/(3) grim/quiet/(4) sober/stingy/(P)
 KanaAdj0( じゅうおうじざい ) // (n,adj-na) freely/right and left/active without any restraint/with unrestricted energy in all directions
 KanaAdj0( おもい ) // (adj) (1) heavy/massive/(2) serious/important/severe/oppressed/(P)
 KanaAdj0( おもたい ) // (adj) heavy/massive/serious/important/severe/oppressed/(P)
 KanaAdj0( おもくるしい ) // (adj) heavy/gloomy/awkward/cumbrous/oppressive/leaden/(P)
 KanaAdj0( じゅうこうちょうだい ) // (n,adj-na) heavy, thick, long, and big (products)/massive and heavy (products)/heavy (manufacturing)
 KanaAdj0( おもおもしい ) // (adj) frequently/sincerely/exceedingly/serious/grave/dignified
 KanaAdj0( じゅうだい ) // (adj-na,n) serious/important/grave/weighty/(P)
 KanaAdj0( じゅくしくさい ) // (adj) smelling of (stale) liquor
 KanaAdj0( でほうだい ) // (adj-na,n) free flow (of water)/random talk/nonsense
 KanaAdj0( しゅつぼつじざい ) // (n,adj-na) appearing and disappearing at will/elusive/phantom-like
 KanaAdj0( じゅんすい ) // (adj-na,n) pure/true/genuine/unmixed/(P)
 KanaAdj0( じゅんせい ) // (adj-na) genuine/pure/perfect
 KanaAdj0( ういういしい ) // (adj) innocent/artless/unsophisticated
 KanaAdj0( あつくるしい ) // (adj) sultry/sweltering
 KanaAdj0( かきにくい ) // (adj) be difficult to write or draw/does not write well (pen, brush, etc.)
 KanaAdj0( すけべい ) // (adj-na,n) lewdness/lewd person/lecher
 KanaAdj0( おんなっぽい ) // (adj) womanly/feminine/womanish/effeminate
 KanaAdj0( おんならしい ) // (adj) womanly/ladylike/feminine/(P)
 KanaAdj0( じょおうらしい ) // (adj) queen-like
 KanaAdj0( めめしい ) // (adj) effeminate
 KanaAdj0( かってしだい ) // (adj-na,n) acting according to one's inclinations
 KanaAdj0( かってほうだい ) // (n,adj-na,adj-no) at one's sweet will/doing whatever one pleases/however one pleases
 KanaAdj0( ちっこい ) // (adj) very small (slightly pejorative)
 KanaAdj0( こうるさい ) // (adj) particular/hard to please/fussy
 KanaAdj0( ちいさい ) // (adj) small/little/tiny/(P)
 KanaAdj0( ちっちゃい ) // (adj) tiny/little/wee
 KanaAdj0( こっぱずかしい ) // (adj) feeling a little (i.e. very) embarrassed/(a little) shameful
 KanaAdj0( おぐらい ) // (adj) dusky/dim/shady
 KanaAdj0( こぐらい ) // (adj) dusky/dim/shady
 KanaAdj0( こぎれい ) // (adj-na) neat/trim/tidy/pretty
 KanaAdj0( こきみよい ) // (adj) smart/clever/neat/gloating
 KanaAdj0( こやかましい ) // (adj) nagging/fault-finding
 KanaAdj0( こざかしい ) // (adj) clever/shrewd/crafty/cunning/pretentious
 KanaAdj0( こだかい ) // (adj) slightly elevated
 KanaAdj0( こにくらしい ) // (adj-na) provoking/horrible
 KanaAdj0( こはずかしい ) // (adj) feeling a little (i.e. very) embarrassed/(a little) shameful
 KanaAdj0( こむずかしい ) // (adj) troublesome/fastidious/tortuous
 KanaAdj0( すくない ) // (adj) few/a little/scarce/insufficient/seldom/(P)
 KanaAdj0( しょうしょうたりない ) // (adj) somewhat lacking/somewhat weak in the head
 KanaAdj0( しょうそうゆうい ) // (adj-no) energetic
 KanaAdj0( ゆかしい ) // (adj) admirable/charming/refined
 KanaAdj0( やきのたりない ) // (adj) underfired
 KanaAdj0( こげくさい ) // (adj) smelling (or tasting) burnt
 KanaAdj0( じれったい ) // (adj) (uk) vexing/irritating/impatient
 KanaAdj0( きなくさい ) // (adj) (1) burning or scorched smell/(2) imminent military action/(3) suspicious
 KanaAdj0( てれくさい ) // (adj) embarrassing/awkward
 KanaAdj0( くわしい ) // (adj) knowing very well/detailed/full/accurate/(P)
 KanaAdj0( つまびらかでない ) // (adj) be unknown
 KanaAdj0( しょうさい ) // (adj-na,n) detail/particulars/(P)
 KanaAdj0( しょうさんしておかない ) // (adj) applaud highly/extol
 KanaAdj0( じょうけい ) // (adj-na,n) the above-mentioned
 KanaAdj0( じょうだい ) // (n,adj-no) (1) ancient times/(2) (nominal) retail price
 KanaAdj0( じょうほうしゅうせい ) // (n,vs) upward adjustment/upward revision
 KanaAdj0( ばちがい ) // (adj-na,exp,n) out-of-place/inappropriate/sticking out like a sore thumb/(P)
 KanaAdj0( なさけぶかい ) // (adj) tender-hearted/compassionate
 KanaAdj0( なさけない ) // (adj) miserable/pitiable/shameful/deplorable
 KanaAdj0( むしあつい ) // (adj) humid/sultry/(P)
 KanaAdj0( かざりけのない ) // (adj) plain/unaffected
 KanaAdj0( いろっぽい ) // (adj) amorous/sexy/voluptuous/erotic
 KanaAdj0( いろこい ) // (adj) marked/pronounced/strongly tending to
 KanaAdj0( いろよい ) // (adj-pn) favorable/favourable/friendly/encouraging
 KanaAdj0( くいたりない ) // (adj) not eating enough
 KanaAdj0( くえない ) // (adj,exp) shrewd/smart (and wide-awake)/cunning/crafty
 KanaAdj0( たべずぎらい ) // (adj-na,n) disliking without even tasting
 KanaAdj0( しんしくじざい ) // (adj-na) elastic/flexible/telescoping/expandable
 KanaAdj0( しんしゅくじざい ) // (adj-na) elastic/flexible/telescoping/expandable
 KanaAdj0( しんじんぶかい ) // (adj) deeply religious/devout/godly/faithful
 KanaAdj0( ねぐるしい ) // (adj) unable to sleep well/(P)
 KanaAdj0( いぎたない ) // (adj) (1) sound asleep/fast asleep/(2) untidy/slovenly
 KanaAdj0( こころやすい ) // (adj) intimate/carefree/familiar/friendly
 KanaAdj0( しんがい ) // (adj-na,n) wholly unexpected/regrettable/unthinkable/(P)
 KanaAdj0( こころもとない ) // (adj) uneasy/unsure/unreliable
 KanaAdj0( こころづよい ) // (adj) heartening/reassuring/(P)
 KanaAdj0( こころぐるしい ) // (adj) painful/be or feel sorry
 KanaAdj0( こころぼそい ) // (adj) helpless/forlorn/hopeless/unpromising/lonely/discouraging/disheartening/(P)
 KanaAdj0( こころさびしい ) // (adj) lonely/lonesome
 KanaAdj0( こころにくい ) // (adj) refined/admirable/superb
 KanaAdj0( ここちよい ) // (adj) comfortable/pleasant
 KanaAdj0( うらはずかしい ) // (adj) slightly ashamed/rather shy
 KanaAdj0( こころえがたい ) // (adj) hard to understand or accept
 KanaAdj0( しんぱい ) // (adj-na,n,vs) worry/concern/anxiety/care/(P)
 KanaAdj0( うらがなしい ) // (adj) sad/mournful/melancholy/sorrowful
 KanaAdj0( こころぜわしい ) // (adj) restless
 KanaAdj0( こころない ) // (adj) thoughtless/inconsiderate/tasteless/cruel
 KanaAdj0( うらさびしい ) // (adj) lonesome/lonely/forlorn
 KanaAdj0( つつましい ) // (adj) modest/reserved/quiet/humble
 KanaAdj0( つつしみぶかい ) // (adj) discreet/modest/cautious
 KanaAdj0( ふるわない ) // (adj) be in a bad way/be dull
 KanaAdj0( あたらしい ) // (adj) new/(P)
 KanaAdj0( しんえい ) // (adj-na,n) freshly picked/newly produced/(P)
 KanaAdj0( もうしぶんない ) // (adj) no objection/nothing to criticize/nothing to criticise/(P)
 KanaAdj0( もうしわけない ) // (adj) inexcusable
 KanaAdj0( もうしぶんのない ) // (adj) no objection/nothing to criticize/nothing to criticise
 KanaAdj0( まっくろい ) // (adj) pitch black/deep black
 KanaAdj0( まんまるい ) // (adj) perfectly circular
 KanaAdj0( まぢかい ) // (adj) near at hand
 KanaAdj0( まあたらしい ) // (adj) brand new/(P)
 KanaAdj0( まっしろい ) // (adj) pure white
 KanaAdj0( こうごうしい ) // (adj) divine/sublime/solemn
 KanaAdj0( しんせい ) // (adj-na,n) holiness/sacredness/dignity/(P)
 KanaAdj0( じんむいらい ) // (adj-no,n-adv,n-t) since the era of the Emperor Jinmu/(first ever) since the dawn of Japan's history/unprecedented
 KanaAdj0( したしい ) // (adj) intimate/close (e.g., friend)/(P)
 KanaAdj0( ちかしい ) // (adj) intimate/close
 KanaAdj0( したしみやすい ) // (adj) friendly
 KanaAdj0( しんあい ) // (n,adj-na) (1) deep affection/(2) dear (often used as the opening greeting of a letter)/beloved/(P)
 KanaAdj0( しんすい ) // (adj-no) hydrophilic/hydro-
 KanaAdj0( みじろぎもしない ) // (adj) didn't stir an inch
 KanaAdj0( みもとふめい ) // (n,adj-no) (a person or body being) unidentifiable (unidentified)
 KanaAdj0( みぎれい ) // (oK) (adj-na) neat personal appearance
 KanaAdj0( からい ) // (adj) (1) hot (spicy)/salty/(2) tough (on someone)/adverse/harsh/(P)
 KanaAdj0( つらい ) // (adj) painful/heart-breaking/(P)
 KanaAdj0( しんきくさい ) // (adj) irritating/fretful/boring
 KanaAdj0( しんぼうづよい ) // (adj) patient
 KanaAdj0( しんしょうぼうだい ) // (adj-na,n) exaggeration/making a mountain out of a molehill
 KanaAdj0( ひとにうったえるちからがない ) // (adj) be of little appeal to people
 KanaAdj0( ひとなつかしい ) // (adj) lonesome for
 KanaAdj0( ひとなつこい ) // (adj) friendly/affable/amiable/sociable/loving company/(animals) taking kindly to men
 KanaAdj0( ひとなつっこい ) // (adj) friendly/affable/amiable/sociable/loving company/(animals) taking kindly to men
 KanaAdj0( にんげんらしい ) // (adj) human/humane
 KanaAdj0( ひとけがない ) // (adj) no sign of life
 KanaAdj0( じんちくむがい ) // (adj-na) harmless to man and beast
 KanaAdj0( じんぶつほんい ) // (n,adj-no) chiefly on the basis of someone's personal character
 KanaAdj0( ひとこいしい ) // (adj) longing for others
 KanaAdj0( はなはだしい ) // (adj) extreme/excessive/terrible/intense/severe/serious/tremendous/heavy (damage)/(P)
 KanaAdj0( じんだい ) // (adj-na,n) very great/enormous/serious/(P)
 KanaAdj0( つきない ) // (adj) everlasting/inexhaustible
 KanaAdj0( ずうずうしい ) // (adj) impudent/shameless
 KanaAdj0( ずぶとい ) // (adj) bold/shameless/cheeky
 KanaAdj0( みずっぽい ) // (adj) (1) watery/soggy/(2) racy/titillating/sexy/suggestive
 KanaAdj0( みずをとおさない ) // (adj) be impervious to water
 KanaAdj0( みずくさい ) // (adj) stand-offish/distant/not frank/reserved/watery/(P)
 KanaAdj0( すいせい ) // (n,adj-no) aquatic (life)/living in the water
 KanaAdj0( すいへい ) // (adj-na,adj-no) level/horizontality/(P)
 KanaAdj0( すい ) // (adj-na,n) chic/style/purity/essence
 KanaAdj0( ずいい ) // (adj-na,n) voluntary/optional/(P)
 KanaAdj0( みずみずしい ) // (adj) young and vivacious
 KanaAdj0( かぞえきれない ) // (adj) countless/incalculable
 KanaAdj0( かずすくない ) // (adj) few in number
 KanaAdj0( あまたい ) // (adj) many/a multiplicity of
 KanaAdj0( すんがたりない ) // (adj) be too short
 KanaAdj0( せちがらい ) // (adj) hard (life)/tough (world)
 KanaAdj0( すごい ) // (adj) terrible/dreadful/terrific/amazing/great/wonderful/to a great extent/(P)
 KanaAdj0( すさまじい ) // (adj) terrific/fierce/terrible/tremendous/dreadful/awful/amazing/absurd/(P)
 KanaAdj0( はれがましい ) // (adj) formal/grand/gala
 KanaAdj0( はればれしい ) // (adj) clear/splendid
 KanaAdj0( ただしい ) // (adj) right/just/correct/righteous/honest/truthful/proper/straightforward/perfect/(P)
 KanaAdj0( しょうたいふめい ) // (n,adj-no) unidentifiable/unidentified
 KanaAdj0( せいはんたい ) // (adj-na,n) bipolar/polar/polarity/exactly opposite/(P)
 KanaAdj0( きよい ) // (adj) clear/pure/noble/(P)
 KanaAdj0( すがすがしい ) // (adj) (uk) fresh/refreshing
 KanaAdj0( なまめかしい ) // (adj) charming/captivating
 KanaAdj0( なまやさしい ) // (adj) simple/easy
 KanaAdj0( なまぬるい ) // (adj) lukewarm/halfhearted
 KanaAdj0( なまあたらしい ) // (adj) very fresh
 KanaAdj0( きっすい ) // (n,adj-no) pure/genuine/natural-born
 KanaAdj0( せいせい ) // (adj-na,n) lively/growing up
 KanaAdj0( なまなましい ) // (adj) lively/green/fresh/raw
 KanaAdj0( なまあたたかい ) // (adj) lukewarm/tepid
 KanaAdj0( なまじろい ) // (adj) pale
 KanaAdj0( なまっちろい ) // (adj) pale
 KanaAdj0( せいだい ) // (adj-na,n) grand/prosperous/magnificent/(P)
 KanaAdj0( せいえい ) // (adj-na,n) elite/picked/powerful/efficient/(P)
 KanaAdj0( せいさい ) // (adj-na,n) detail
 KanaAdj0( あおぐろい ) // (adj) dark blue/discolored/discoloured
 KanaAdj0( あおくさい ) // (adj) inexperienced/immature/grassy-smelling
 KanaAdj0( もろい ) // (adj) brittle/fragile/tender-hearted/(P)
 KanaAdj0( おしい ) // (adj) (1) regrettable/disappointing/(2) precious/dear/valuable/(3) too good for/deserving better/(4) almost but not quite/(P)
 KanaAdj0( おしまない ) // (adj) without sparing (effort, funds, etc.)/(P)
 KanaAdj0( あかい ) // (adj) red/(P)
 KanaAdj0( せきがい ) // (adj-na) infrared
 KanaAdj0( あかぐろい ) // (adj) dark red
 KanaAdj0( せつない ) // (adj) painful/trying/oppressive/suffocating/(P)
 KanaAdj0( きらない ) // (adj) not through/not finished
 KanaAdj0( きりのない ) // (adj) endless/boundless
 KanaAdj0( きれない ) // (adj,suf) being too many or much
 KanaAdj0( つたない ) // (adj) clumsy/unskillful/foolish/unlucky
 KanaAdj0( おりめただしい ) // (adj) good manners/courteous
 KanaAdj0( せつをまげない ) // (adj) remain firm/stick by one's principles
 KanaAdj0( せっかい ) // (adj-na,n) untimely interference
 KanaAdj0( ぜっせい ) // (n,adj-no) peerless/unequaled/unequalled/matchless
 KanaAdj0( ぜったいぜつめい ) // (adj-na,n) desperate situation/being driven into a corner/stalemate
 KanaAdj0( ぜつだい ) // (adj-na,n) tremendous/immense/(P)
 KanaAdj0( せんぞだいだい ) // (n,adj-no) ancestral/hereditary/generation after generation/passing from father to son
 KanaAdj0( せんぞでんらい ) // (adj-no) inherited
 KanaAdj0( せんばい ) // (adj-na,n) thousand-fold
 KanaAdj0( あさい ) // (adj) shallow/superficial/(P)
 KanaAdj0( あさましい ) // (adj) wretched/miserable/shameful/mean/despicable/abject
 KanaAdj0( あさぐろい ) // (adj) darkish/swarthy/(P)
 KanaAdj0( せんいせい ) // (adj-na) fibrous
 KanaAdj0( せんさい ) // (adj-na,n) fine/nice/delicate/subtle/(P)
 KanaAdj0( うらやましい ) // (adj) envious/enviable/(P)
 KanaAdj0( せんがい ) // (adj-no) outboard/extra-vehicular
 KanaAdj0( せんない ) // (adj) unavoidable/no help for
 KanaAdj0( せんえい ) // (adj-na,n) sharp/clear
 KanaAdj0( せんめい ) // (adj-na,n) vivid/clear/distinct/(P)
 KanaAdj0( せんれい ) // (adj-na,n) vivid/gorgeous/resplendent beauty/bright
 KanaAdj0( ぜんけい ) // (n,adj-no) above-named
 KanaAdj0( ぜんとゆうい ) // (n,adj-na,adj-no) having a very promising future/offering promising prospects
 KanaAdj0( さりげない ) // (adj) (uk) nonchalant/unconcerned/in a casual manner
 KanaAdj0( うとい ) // (adj) distant/estranged/disinterested
 KanaAdj0( うとましい ) // (adj) disagreeable/unpleasant/adverse/unsympathetic
 KanaAdj0( そすいせい ) // (adj-no) hydrophobic
 KanaAdj0( うとうとしい ) // (adj) unfriendly
 KanaAdj0( あらい ) // (adj) coarse/rough/(P)
 KanaAdj0( そだい ) // (adj-na,n) coarse or rough/(P)
 KanaAdj0( そっけない ) // (adj) cold/short/curt/blunt
 KanaAdj0( そこうがおさまらない ) // (adj) be dissolute/conduct oneself loosely
 KanaAdj0( しろうとくさい ) // (adj) amateurish
 KanaAdj0( すばらしい ) // (adj) wonderful/splendid/magnificent/(P)
 KanaAdj0( すばやい ) // (adj) (1) fast/quick/prompt/(2) nimble/agile
 KanaAdj0( そうだい ) // (adj-na,n) magnificent/grand/majestic/splendid/(P)
 KanaAdj0( そうだいかれい ) // (n,adj-na) grandiose and splendid
 KanaAdj0( そうれい ) // (adj-na,n) splendour/splendor/pompousness/magnificence
 KanaAdj0( そうかい ) // (adj-na,n) refreshing/exhilarating
 KanaAdj0( そうぞうしにくい ) // (adj) hard to imagine
 KanaAdj0( そうけい ) // (adj-na,n) over hasty/rash
 KanaAdj0( そういない ) // (adj) without doubt/certain/sure
 KanaAdj0( ふさわしい ) // (adj) appropriate/(P)
 KanaAdj0( あいひとしい ) // (adj) equal to each other
 KanaAdj0( そうはんせい ) // (adj-na) reciprocal
 KanaAdj0( あいいれない ) // (adj,exp) in conflict/incompatible/out of harmony/running counter
 KanaAdj0( くさぶかい ) // (adj) grassy/weedy
 KanaAdj0( そうごんかれい ) // (n,adj-na) majestic and splendid
 KanaAdj0( あおじろい ) // (adj) (1) pale/pallid/(2) blue and white
 KanaAdj0( さわがしい ) // (adj) noisy/(P)
 KanaAdj0( そうぞうしい ) // (adj) noisy/boisterous
 KanaAdj0( にくたらしい ) // (adj) odious/hateful
 KanaAdj0( にくらしい ) // (adj) odious/hateful/(P)
 KanaAdj0( にくにくしい ) // (adj) hateful/detestable/loathsome
 KanaAdj0( ぞうさない ) // (adj) no trouble/easy
 KanaAdj0( いきぐるしい ) // (adj) choking/oppressive/suffocating
 KanaAdj0( そくさい ) // (adj-na,n) good health
 KanaAdj0( あしでまとい ) // (adj-na,n) impediment/burden/encumbrance/hindrance/drag
 KanaAdj0( あしばやい ) // (adj) swift-footed/light-footed
 KanaAdj0( はやい ) // (adj) quick/fast/swift/(P)
 KanaAdj0( ぞくっぽい ) // (adj) cheap (reading)/vulgar/worldly-minded
 KanaAdj0( そろわない ) // (adj) unequal/uneven/incomplete/odd
 KanaAdj0( ぞんがい ) // (adj-na,adv,n) beyond or contrary to expectations
 KanaAdj0( たっとい ) // (adj) precious/valuable/priceless/noble/exalted/sacred/(P)
 KanaAdj0( とうとい ) // (adj) precious/valuable/priceless/noble/exalted/sacred/(P)
 KanaAdj0( そんだい ) // (adj-na,n) haughtiness/pomposity/self-sufficiency
 KanaAdj0( そんしょくがない ) // (adj) bears comparison with (something)/compares favorably with (something)/compares favourably with (something)/isn't inferior to (something)
 KanaAdj0( たわいもない ) // (adj) (uk) silly/foolish/absurd/childish/easy/trifling/guileless
 KanaAdj0( たわいない ) // (adj) (uk) silly/foolish/absurd/childish/easy/trifling/guileless
 KanaAdj0( おおい ) // (adj) many/numerous/(P)
 KanaAdj0( たげい ) // (adj-na,n) versatility
 KanaAdj0( たげいたさい ) // (n,adj-na) versatile/multi-talented
 KanaAdj0( たけっしょうせい ) // (adj-pn) polycrystalline
 KanaAdj0( たさい ) // (adj-na,n) talented/(P)
 KanaAdj0( ただい ) // (adj-na,n) heavy/much/(P)
 KanaAdj0( ふとい ) // (adj) fat/thick/(P)
 KanaAdj0( ふてぶてしい ) // (adj) (uk) impudent/brazen/shameless/bold
 KanaAdj0( うつてがない ) // (adj) no way to do/nothing can be done
 KanaAdj0( たいしんせい ) // (adj-no) earthquake-proof
 KanaAdj0( たえがたい ) // (adj) unbearable/intolerable/unendurable
 KanaAdj0( まちどおしい ) // (adj) looking forward to/(P)
 KanaAdj0( まちきれない ) // (adj) waiting impatiently for
 KanaAdj0( だるい ) // (adj) (uk) sluggish/feel heavy/languid/dull/(P)
 KanaAdj0( わざとらしい ) // (adj) unnatural/affected/studied/forced
 KanaAdj0( たいへい ) // (adj-na,n) peace/tranquility/tranquillity
 KanaAdj0( たいけいせいせい ) // (adj-no) anaplastic
 KanaAdj0( おおきい ) // (adj) big/large/great/(P)
 KanaAdj0( おおちがい ) // (adj) (1) great difference/(2) major mistake
 KanaAdj0( たいがい ) // (n-adv,n-t,adj-no) (1) in general/almost all/(2) mainly/mostly/most likely/(3) moderately/suitably/(P)
 KanaAdj0( だいきらい ) // (adj-na,n) very dislikeable/hate, loathe, abhor/(P)
 KanaAdj0( おおじだい ) // (adj-na,n) old-fashioned/antiquated/anachronistic/(P)
 KanaAdj0( おおわらい ) // (adj-na,n) great laughter/burst of laughter/(P)
 KanaAdj0( おおぐい ) // (adj-na,n) gluttony
 KanaAdj0( おおぐらい ) // (adj-na,n) glutton
 KanaAdj0( おとなしい ) // (adj) obedient/docile/quiet/(P)
 KanaAdj0( おとなっぽい ) // (adj) adult-like
 KanaAdj0( おとなげない ) // (adj) immature/childish
 KanaAdj0( たいてい ) // (adj-na,adv,n) usually/generally/(P)
 KanaAdj0( だいどうしょうい ) // (adj-na,n) essentially the same with only minor differences
 KanaAdj0( おおへい ) // (adj-na,n) large build/large pattern
 KanaAdj0( たつい ) // (adj-na,n) lucidity/intelligibility/perspicuity
 KanaAdj0( なげかわしい ) // (adj) sad/wretched/deplorable/(P)
 KanaAdj0( あわい ) // (adj) light/faint/pale/fleeting/(P)
 KanaAdj0( みじかい ) // (io) (adj) short
 KanaAdj0( たんめい ) // (adj-na,n) short life/(P)
 KanaAdj0( はしたない ) // (adj) immodest/unladylike/vulgar/(P)
 KanaAdj0( たんせい ) // (adj-na,n) handsome/noble
 KanaAdj0( たんれい ) // (adj-na,n) grace/beauty/elegance
 KanaAdj0( だんがい ) // (n,vs,adj-no) impeachment/accusation/censure/denunciation/(P)
 KanaAdj0( あたたかい ) // (adj) warm/mild/genial/(P)
 KanaAdj0( あったかい ) // (adj) warm/mild/genial
 KanaAdj0( だんちがい ) // (adj-na,n) wide difference/remarkable difference
 KanaAdj0( おとこっぽい ) // (adj) manly/boyish
 KanaAdj0( おとこらしい ) // (adj) manly/(P)
 KanaAdj0( あたい ) // (n,adj-no,vs) (1) (comp) value/price/cost/worth/merit/(2) variable (computer programming, programing)
 KanaAdj0( しらない ) // (adj) unknown/strange
 KanaAdj0( ちめい ) // (adj-na,n) well-known/(P)
 KanaAdj0( はずかしい ) // (adj) shy/ashamed/embarrassed/(P)
 KanaAdj0( おそい ) // (adj) late/slow/(P)
 KanaAdj0( ちゃいろい ) // (adj) light brown/tawny
 KanaAdj0( ちゅうぐらい ) // (adj-na,n) about medium
 KanaAdj0( ちゅうかんたい ) // (adj-na) intermediate (chem)
 KanaAdj0( ちゅうごくでんらい ) // (adj-no) imported (transmitted) from China
 KanaAdj0( まめまめしい ) // (adj) (uk) hardworking/painstaking/diligent/conscientious/sincere
 KanaAdj0( ちゅうせい ) // (adj-na,n) loyalty/sincerity/(P)
 KanaAdj0( ちゅういぶかい ) // (adj-na) careful/(P)
 KanaAdj0( ちょこざい ) // (adj-na,n) impertinence
 KanaAdj0( いちじるしい ) // (adj) remarkable/considerable/(P)
 KanaAdj0( ちょだい ) // (adj-na,n) exceptionally large
 KanaAdj0( ちょめい ) // (adj-na,n) clarity
 KanaAdj0( ぼりのふかい ) // (adj) finely chiseled (features)
 KanaAdj0( ちょうしゅうをあかさない ) // (adj) hold the attention of the audience
 KanaAdj0( ちょうせい ) // (n,vs) regulation/adjustment/tuning/(P)
 KanaAdj0( ちょうてい ) // (adj-no,pref) very low (deep, cold, etc.)/ultra-/infra-/hyper-
 KanaAdj0( ながい ) // (adj) long/lengthy/(P)
 KanaAdj0( ながたらしい ) // (adj) tedious/lengthy/overlong/long-winded
 KanaAdj0( ながったらしい ) // (adj) tedious/lengthy/overlong/long-winded
 KanaAdj0( ちょうだい ) // (adj-na,n) very long/great length/(P)
 KanaAdj0( ながながしい ) // (adj) long, drawn-out/tedious
 KanaAdj0( ちょうめい ) // (adj-na,n) long life
 KanaAdj0( なおらない ) // (adj) beyond repair/irreparable
 KanaAdj0( ちょくさい ) // (adj-na,n) frank/straightforward/prompt/directness/decisiveness
 KanaAdj0( ちんせい ) // (adj-na,n) stillness/tranquility/tranquillity/dullness/(P)
 KanaAdj0( ちんちゃくれいせい ) // (n,adj-na) calm, cool, and collected/level and calm
 KanaAdj0( めずらしい ) // (adj) unusual/rare/(P)
 KanaAdj0( ちんむるい ) // (adj-na,n) extraordinary/singular/incredible
 KanaAdj0( ちんつうせい ) // (adj-na) analgesic
 KanaAdj0( いたい ) // (adj) painful/(P)
 KanaAdj0( いたましい ) // (adj) pitiful/heartbreaking/(P)
 KanaAdj0( つうかい ) // (adj-na,n) intense pleasure/thrilling
 KanaAdj0( つうかいきわまりない ) // (adj) be extremely thrilling
 KanaAdj0( いたいたしい ) // (adj) pitiful/pathetic
 KanaAdj0( つじつまのあわない ) // (adj) incoherent/inconsistent
 KanaAdj0( ていてい ) // (adj-na,n) lofty
 KanaAdj0( ひくい ) // (adj) short/low/humble/low (voice)/(P)
 KanaAdj0( ていかい ) // (n) adjournment/suspension of a meeting/recess of legislature
 KanaAdj0( そこいじわるい ) // (adj) malicious/spiteful
 KanaAdj0( そこきみわるい ) // (adj) strange/eerie/ominous
 KanaAdj0( そこがたい ) // (adj) stable (market) after having bottomed out
 KanaAdj0( ほどとおい ) // (adj) far off or away
 KanaAdj0( ほどちかい ) // (adj) near/nearby/not far off
 KanaAdj0( ほどよい ) // (adj) moderate/proper/just right
 KanaAdj0( しまりのない ) // (adj) slack/loose/lax
 KanaAdj0( どろくさい ) // (adj) smelling of mud or earth/unrefined/uncouth
 KanaAdj0( かなわない ) // (adj) be beyond one's power/be unable
 KanaAdj0( てきおうしょうがい ) // (n) maladjustment
 KanaAdj0( てきせい ) // (adj-na,n) reasonable/suitable/(P)
 KanaAdj0( てんけい ) // (n,adj-no) type/pattern/archetypal/(P)
 KanaAdj0( てんれい ) // (adj-na,n) graceful
 KanaAdj0( てんかむるい ) // (n,adj-no) peerless (unparalleled, matchless, unequaled) in the country
 KanaAdj0( てんのうちどころがない ) // (adj) be above reproach
 KanaAdj0( でんらい ) // (n,adj-no) ancestral/hereditary/imported/transmitted/handed down
 KanaAdj0( でんかい ) // (adj-na,n,vs) electrolysis/electrolytic
 KanaAdj0( ねたましい ) // (adj) jealous/envious
 KanaAdj0( だだっぴろい ) // (adj) very (excessively) spacious/unduly wide/sprawling
 KanaAdj0( とてつもない ) // (adj) (uk) extravagant/absurd/unbelievable/preposterous/unreasonable
 KanaAdj0( とほうもない ) // (adj) extraordinary/preposterous/outrageous/absurd
 KanaAdj0( どしがたい ) // (adj) beyond help/incorrigible
 KanaAdj0( つちくさい ) // (adj) smelling of earth/rustic
 KanaAdj0( おこりっぽい ) // (adj) hot-tempered/quick to take offense/quick to take offence/irascible/touchy
 KanaAdj0( あたりさわりのない ) // (adj) harmless and inoffensive
 KanaAdj0( あてのない ) // (adj) aimless
 KanaAdj0( とうがい ) // (adj-pn,n) appropriate (authorities)/concern/applicability/correlation
 KanaAdj0( ひとしい ) // (adj) equal/similar/like/equivalent/(P)
 KanaAdj0( とうめい ) // (adj-na,n) transparency/cleanness/(P)
 KanaAdj0( どうねんだい ) // (n,adj-no) the same generation/coeval
 KanaAdj0( えたいのしれない ) // (adj-pn) strange/unfamiliar/mysterious/suspicious
 KanaAdj0( えがたい ) // (adj) hard to get
 KanaAdj0( とくのたかい ) // (adj) virtuous/respectable
 KanaAdj0( とくい ) // (adj-na,n) unique/singular/(P)
 KanaAdj0( とくてい ) // (adj-na,n,vs) specific/special/particular/(P)
 KanaAdj0( どくせい ) // (adj-na,n) toxicity/toxic/virulence/virulent/(P)
 KanaAdj0( どくどくしい ) // (adj) poisonous/venomous
 KanaAdj0( よみづらい ) // (adj) hard to read
 KanaAdj0( とっぴょうしもない ) // (adj) astounding/tremendous/crazy/exorbitant
 KanaAdj0( にぶい ) // (adj) dull (e.g., a knife)/thickheaded/slow (opposite of fast)/stupid/(P)
 KanaAdj0( のろい ) // (adj) dull (e.g., a knife)/thickheaded/slow (opposite of fast)/stupid/(P)
 KanaAdj0( どんくさい ) // (adj) slow (opposite of fast)/stupid/irritating
 KanaAdj0( のろくさい ) // (adj) slow (opposite of fast)/stupid/irritating
 KanaAdj0( ないない ) // (adj-no,adv,n) family circle/the inside/private/informal/secret/confidential
 KanaAdj0( なれなれしい ) // (adj) over-familiar/(P)
 KanaAdj0( なじみぶかい ) // (adj) extremely intimate/very well-acquainted
 KanaAdj0( やわらかい ) // (adj) soft/tender/limp/(P)
 KanaAdj0( がたい ) // (adj,suf) difficult/hard
 KanaAdj0( にくい ) // (adj,suf) difficult/hard/(P)
 KanaAdj0( むずかしい ) // (adj) difficult/(P)
 KanaAdj0( むつかしい ) // (adj) difficult
 KanaAdj0( なんかい ) // (adj-na,n) difficult/(P)
 KanaAdj0( ひのめをみない ) // (adj) staying indoors/have no sunshine/remain obscure
 KanaAdj0( ちちくさい ) // (adj) smelling of milk/green/wet behind the ears/immature
 KanaAdj0( にょいじざい ) // (n,adj-na,adj-no) freely/in complete control of/with complete freedom/at will/as one pleases
 KanaAdj0( いかがわしい ) // (adj) (1) (uk) suspicious/dubious/unreliable/(2) indecent/unseemly
 KanaAdj0( じょさいない ) // (adj) tactful/shrewd/cautious/clever/smart/adroit
 KanaAdj0( にんい ) // (adj-na,n,adj-no) any/arbitrary/optional/pleasure/discretion/free will/(P)
 KanaAdj0( しのびがたい ) // (adj) intolerable/unbearable
 KanaAdj0( にんたいづよい ) // (adj) persevering/very patient
 KanaAdj0( みとめがたい ) // (adj) unapprovable
 KanaAdj0( ねこのこいっぴきいない ) // (adj) completely deserted
 KanaAdj0( あつい ) // (adj) hot (thing)/(P)
 KanaAdj0( ねっしやすい ) // (adj) excitable
 KanaAdj0( ねつっぽい ) // (adj) (1) feverish/(2) enthusiastic
 KanaAdj0( ねっせい ) // (adj-na,n) earnestness
 KanaAdj0( としがいもない ) // (adj) unbecoming/unsuitable/disgraceful
 KanaAdj0( としわかい ) // (adj) young/youthful
 KanaAdj0( ねんしょうきえい ) // (n,adj-no) being young and spirited/being young and full of go
 KanaAdj0( としはもいかない ) // (adj) of tender years/very young
 KanaAdj0( ねんぱい ) // (n,adj-no) elderly/age/years/(P)
 KanaAdj0( ねんまつちょうせい ) // (n) year-end tax adjustment
 KanaAdj0( ねばい ) // (adj) sticky
 KanaAdj0( ねばっこい ) // (adj) sticky/stiff/tenacious/persistent
 KanaAdj0( ねばりづよい ) // (adj) tenacious/persevering/persistent/(P)
 KanaAdj0( ねんちゃくざい ) // (n,adj-na) adhesive/agglutinant/pressure sensitive adhesive
 KanaAdj0( なやましい ) // (adj) (1) seductive/carnal/enchanting/(2) troubling/difficult/thorny/hard/(3) anxious/uneasy
 KanaAdj0( こい ) // (adj) thick (as of color, liquid) (colour)/dense/strong/(P)
 KanaAdj0( おさまらない ) // (adj) feel grieved/be unsatisfied
 KanaAdj0( のうがない ) // (adj) incompetent/have no merit
 KanaAdj0( のうせい ) // (adj-na,n) cerebral
 KanaAdj0( ばからしい ) // (adj) absurd/(P)
 KanaAdj0( ばかくさい ) // (adj) absurd
 KanaAdj0( ばかていねい ) // (adj-na,n) overly polite
 KanaAdj0( ばかばかしい ) // (adj) stupid
 KanaAdj0( はくしきたさい ) // (n,adj-na) wide knowledge and versatile talents/profound learning and varied attainments
 KanaAdj0( しろい ) // (adj) white/(P)
 KanaAdj0( しろっぽい ) // (adj) whitish
 KanaAdj0( しらじらしい ) // (adj) (1) barefaced (e.g., lie)/shameless/transparent/(2) pure white/very clear
 KanaAdj0( はくらい ) // (n,adj-no) imported/foreign-made/(P)
 KanaAdj0( うすい ) // (adj) thin/weak/watery/diluted/(P)
 KanaAdj0( うすらさむい ) // (adj) chilly/rather cold/somewhat cold
 KanaAdj0( うすぐらい ) // (adj) dim/gloomy/(P)
 KanaAdj0( うすぎたない ) // (adj) filthy/dirty (looking)/drab
 KanaAdj0( うすきみわるい ) // (adj) weird/eerie/uncanny
 KanaAdj0( うすじろい ) // (adj) whitish
 KanaAdj0( ばくすい ) // (adj-na) fast asleep/bombed/crashed
 KanaAdj0( ばくだい ) // (adj-na,n) enormous/vast/(P)
 KanaAdj0( はだがあわない ) // (adj) cannot go together (with)
 KanaAdj0( ぬけめない ) // (adj) shrewd/astute/cunning
 KanaAdj0( はんえんけい ) // (adj-no) semicircular
 KanaAdj0( はんおんかい ) // (n,adj-no) chromatic (scale) (music)
 KanaAdj0( はんげつけい ) // (adj-no) semicircular/crescent-shaped/half-moon
 KanaAdj0( はんとうめい ) // (adj-na,n,adj-no) semi-transparent/translucent
 KanaAdj0( そりがあわない ) // (adj) unable to cooperate
 KanaAdj0( はんたい ) // (adj-na,n,vs) opposition/resistance/antagonism/hostility/contrast/objection/dissension/reverse/opposite/vice versa/(P)
 KanaAdj0( おかしがたい ) // (adj) dignified
 KanaAdj0( うるさい ) // (ateji) (adj) (1) noisy/loud/(2) fussy/(3) annoying/troublesome/tiresome/importunate/(4) bossy/(P)
 KanaAdj0( わずらわしい ) // (adj) troublesome/annoying/complicated/(P)
 KanaAdj0( めしがくえない ) // (adj) cannot make a living
 KanaAdj0( かなしい ) // (adj) sad/sorrowful/(P)
 KanaAdj0( くらべものにならない ) // (adj) cannot be compared with/be no match for
 KanaAdj0( ひをみない ) // (adj) be unique (unrivaled, unrivalled)
 KanaAdj0( ひるいのない ) // (adj) peerless
 KanaAdj0( ひえいせい ) // (adj-na,n) unsanitary/unhygenic
 KanaAdj0( ひけっしょうせい ) // (adj-pn) amorphous
 KanaAdj0( ひどい ) // (adj) (uk) cruel/awful/severe/very bad/serious/terrible/heavy/violent
 KanaAdj0( ひはかい ) // (adj) non-destructive
 KanaAdj0( びさい ) // (adj-na,n) minute/micro/detailed/delicate/subtle/(P)
 KanaAdj0( ほほえましい ) // (adj) pleasant/charming
 KanaAdj0( ほろよい ) // (adj) slightly drunk/tipsy
 KanaAdj0( びちょうせい ) // (n,vs) minute adjustment/fine tuning
 KanaAdj0( うつくしい ) // (adj) beautiful/lovely/(P)
 KanaAdj0( びびしい ) // (adj) beautiful
 KanaAdj0( うまい ) // (adj) (1) delicious/appetizing/appetising/(2) skillful/clever/expert/wise/successful/(3) fortunate/splendid/promising
 KanaAdj0( おいしい ) // (adj) delicious/tasty/(P)
 KanaAdj0( びれい ) // (adj-na,n) beauty/gorgeous(ness)
 KanaAdj0( はなもちならない ) // (adj) stink/intolerable
 KanaAdj0( ひょうがい ) // (adj-no) (1) outside a table or list/(2) not a common kanji
 KanaAdj0( ひょうざい ) // (adj-na) superficial
 KanaAdj0( ひょうそうせい ) // (adj-na) superficial
 KanaAdj0( ひょうない ) // (adj-no) inside a table or list
 KanaAdj0( ひんこうほうせい ) // (adj-na,n) irreproachable conduct
 KanaAdj0( まずしい ) // (adj) poor/needy/(P)
 KanaAdj0( はしこい ) // (adj) (1) (uk) smart/clever/(2) agile/nimble/quick
 KanaAdj0( はしっこい ) // (adj) (1) (uk) smart/clever/(2) agile/nimble/quick
 KanaAdj0( ふあんてい ) // (adj-na,n) instability/insecurity/crankiness/(P)
 KanaAdj0( ふあんない ) // (adj-na,n) ignorance/inexperience/unfamiliarity
 KanaAdj0( ふい ) // (adj-na,n,adj-no) sudden/abrupt/unexpected/unforeseen/(P)
 KanaAdj0( ふえいせい ) // (adj-na,n) unsanitary condition
 KanaAdj0( ふかかい ) // (adj-na,n) mystery/baffling/inexplicable/incomprehensible/(P)
 KanaAdj0( ふかい ) // (adj-na,n) unpleasant/displeasure/discomfort/(P)
 KanaAdj0( ふかくてい ) // (adj-na,n) uncertain/indefinite
 KanaAdj0( ふかっせい ) // (adj-no) (chemically) inert
 KanaAdj0( ふぐあい ) // (adj-na,n) (1) flaw/defect/failure/discrepancy/(2) inconvenient
 KanaAdj0( ふけい ) // (adj-na,n) disrespect/irreverence/impiety/blasphemy/profanity
 KanaAdj0( ふけいざい ) // (adj-na,n) poor economy/waste
 KanaAdj0( ふこうへい ) // (adj-na,n) unfairness/injustice/partiality/(P)
 KanaAdj0( ふにあい ) // (adj-na,n) unbecoming/improper/unsuitable/ill-matched/unworthy of
 KanaAdj0( ふせい ) // (adj-na,n) injustice/unfairness/iniquity/impropriety/irregularity/dishonesty/illegality/(P)
 KanaAdj0( ふせっせい ) // (adj-na,n) neglect of health/intemperance
 KanaAdj0( ふせんめい ) // (adj-na,n) blur
 KanaAdj0( ふぞろい ) // (adj-na,n) unevenness/irregularity/lack of uniformity
 KanaAdj0( ふていさい ) // (adj-na,n) bad form or manners/indecency/impropriety
 KanaAdj0( ふちゅうい ) // (adj-na,n) carelessness/inattention/thoughtlessness/(P)
 KanaAdj0( ふつりあい ) // (adj-na,n) unbalance/imbalance/asymmetry/disparity
 KanaAdj0( ふてってい ) // (adj-na,n) inconsistent/illogical/unconvincing/not thorough/indefinite/half-way
 KanaAdj0( ふとうめい ) // (adj-na,n) opacity/(P)
 KanaAdj0( ふとくい ) // (adj-na,n) one's weak point/(P)
 KanaAdj0( ふとくてい ) // (adj-na,n) unspecified/random/indefinite
 KanaAdj0( ふにょい ) // (adj-na,n) contrary to one's wishes/short of money
 KanaAdj0( ふねんせい ) // (n,adj-no) non-inflammability/incombustibility
 KanaAdj0( ふぶんめい ) // (adj-na) obscure/vague
 KanaAdj0( ふへい ) // (adj-na,n) complaint/discontent/dissatisfaction/(P)
 KanaAdj0( ふほんい ) // (adj-na,n) reluctance/unwilling/(P)
 KanaAdj0( まずい ) // (adj) (uk) unappetising/unappetizing/unpleasant (taste, appearance, situation)/ugly/unskilful/awkward/bungling/unwise/untimely/(P)
 KanaAdj0( ふめい ) // (adj-na,n) unknown/obscure/indistinct/uncertain/ambiguous/ignorant/lack of wisdom/anonymous/unidentified/(P)
 KanaAdj0( ふゆかい ) // (adj-na,n) discomfort/unpleasantness/disagreeableness/unhappiness/(P)
 KanaAdj0( ふようい ) // (adj-na,n) unpreparedness/carelessness/(P)
 KanaAdj0( ふてい ) // (adj-na,n) insubordination/outlawry
 KanaAdj0( こわい ) // (adj) scary/frightening/eerie/dreadful/(P)
 KanaAdj0( ふつうでない ) // (adj) abnormal
 KanaAdj0( うかばれない ) // (adj) turning in one's grave/cannot rest in peace
 KanaAdj0( ふそでんらい ) // (n,adj-no) hereditary/patrimonial/handed down from generation to generation
 KanaAdj0( はだざむい ) // (adj) chilly/unpleasantly cold
 KanaAdj0( まけずぎらい ) // (adj-na,n) hating to lose/determined
 KanaAdj0( ぶたんい ) // (n,adj-na) collating (printing)
 KanaAdj0( ふうさいがあがらない ) // (adj) make a poor appearance
 KanaAdj0( はばひろい ) // (adj) extensive/wide/broad/(P)
 KanaAdj0( ふくぶくしい ) // (adj) (plump and) happy-looking
 KanaAdj0( はらがゆるい ) // (adj) have loose bowels
 KanaAdj0( はらぐろい ) // (adj) mean/malicious/scheming
 KanaAdj0( はらだたしい ) // (adj) irritating
 KanaAdj0( はらぎたない ) // (adj) black-hearted/nasty
 KanaAdj0( ふくざつきかい ) // (n,adj-na) complex and mysterious (bizarre)/complicated and inscrutable
 KanaAdj0( ほとけくさい ) // (adj) otherwordly/sanctimonious
 KanaAdj0( もののかずにはいらない ) // (adj) be off the map/be insignificant
 KanaAdj0( ものぐるおしい ) // (adj) frantic/like mad
 KanaAdj0( ものがたい ) // (adj) honest/upright/faithful/reliable
 KanaAdj0( ものみだかい ) // (adj) burning curiosity
 KanaAdj0( ものすごい ) // (adj) earth-shattering/staggering/to a very great extent/(P)
 KanaAdj0( ものさわがしい ) // (adj) noisy/boisterous/turbulent
 KanaAdj0( ものたりない ) // (adj) unsatisfied/unsatisfactory/(P)
 KanaAdj0( ものめずらしい ) // (adj) curious
 KanaAdj0( ものがなしい ) // (adj) sad/melancholy
 KanaAdj0( ものものしい ) // (adj) imposing/showy/overdone
 KanaAdj0( ものうい ) // (adj) languid/weary/listless/melancholy
 KanaAdj0( ものさびしい ) // (adj) lonely
 KanaAdj0( わかちがたい ) // (adj) inseparable
 KanaAdj0( わかりやすい ) // (adj) easy to understand
 KanaAdj0( わかりづらい ) // (adj) difficult to understand
 KanaAdj0( わかりにくい ) // (oK) (adj) hard to understand/incomprehensible/unintelligible
 KanaAdj0( わかりよい ) // (adj) easy to understand
 KanaAdj0( ぶんがい ) // (adj-na,n) not within proper limits/excessive/unmerited/special
 KanaAdj0( ぶあつい ) // (adj) bulky/massive/thick/heavy
 KanaAdj0( ぶんめい ) // (adj-na,n) clearness/clear understanding
 KanaAdj0( まぎらわしい ) // (adj) confusing/misleading/equivocal/ambiguous/(P)
 KanaAdj0( ききにくい ) // (adj) difficult to hear/hesitating to ask
 KanaAdj0( ききぐるしい ) // (adj) poor sound quality/unpleasant to hear
 KanaAdj0( ききづらい ) // (adj) difficult to hear/difficult to ask
 KanaAdj0( ききわけのいい ) // (adj) reasonable
 KanaAdj0( ききよい ) // (adj) pleasant to listen to
 KanaAdj0( へいさい ) // (adj) (abbr) combining a pair of events/joint
 KanaAdj0( ひらたい ) // (adj) flat/even/level/simple/plain/(P)
 KanaAdj0( へいい ) // (adj-na,n) easy/simple/plain
 KanaAdj0( へいいめいかい ) // (n,adj-na) simple and clear/plain and lucid
 KanaAdj0( へいせい ) // (adj-na,n) calm/serenity/tranquillity/tranquility/(P)
 KanaAdj0( へいめい ) // (adj-na,n) clear/simple
 KanaAdj0( がらにもない ) // (adj) out of character/unlike one
 KanaAdj0( がらのわるい ) // (adj) ill-bred
 KanaAdj0( ならびない ) // (adj) unparalleled/unparallelled/unequaled/unequalled/unique
 KanaAdj0( なみたいてい ) // (adj-na,n) ordinary
 KanaAdj0( へいてい ) // (n,vs) adjourning court
 KanaAdj0( あおい ) // (oK) (adj) blue/pale/green/unripe/inexperienced
 KanaAdj0( へんぺい ) // (adj-na,n) flat
 KanaAdj0( かわらない ) // (adj) constant/invariant/(P)
 KanaAdj0( かわりやすい ) // (adj) changeable/unsettled/inconstant
 KanaAdj0( へんげんじざい ) // (adj-na,n) phantasmagoric/capable of ever-changing appearance
 KanaAdj0( へんつうじざい ) // (n,adj-na,adj-no) freely adaptable, very flexible, nimble in adaptation
 KanaAdj0( へんてつもない ) // (adj) usual/mediocre/monotonous
 KanaAdj0( かたはらいたい ) // (adj) ridiculous/absurd
 KanaAdj0( べんねい ) // (adj-na,n) flattery/adulation
 KanaAdj0( わきまえのない ) // (adj) indiscreet/undiscerning
 KanaAdj0( とらえどころのない ) // (adj) subtle/elusive/slippery
 KanaAdj0( ほせい ) // (n,vs) adjust (by supplementing)
 KanaAdj0( ほてい ) // (adj-na,n,vs) replenishment/prosthetic
 KanaAdj0( したわしい ) // (adj) dear/beloved
 KanaAdj0( あっけない ) // (adj) not enough/too quick (short, long, etc.)
 KanaAdj0( ほうとうぶらい ) // (n,adj-no) being dissolute and unruly/ruining oneself by leading a fast life
 KanaAdj0( ほうせい ) // (adj-na,n) rectitude
 KanaAdj0( かぐわしい ) // (adj) (uk) sweet-smelling/scentful/fragrant
 KanaAdj0( かんばしい ) // (adj) sweet/fragrant/aromatic/savory/savoury/(P)
 KanaAdj0( かんばしくない ) // (adj) poor/unfavourable/unfavorable/disgraceful
 KanaAdj0( あきっぽい ) // (adj) fickle/capricious/soon wearied of
 KanaAdj0( あきやすい ) // (adj) tired of/wearied/fickle
 KanaAdj0( あきたらない ) // (adj) unsatisfactory/unsatisfying
 KanaAdj0( あきたりない ) // (adj) unsatisfactory/unsatisfying
 KanaAdj0( あくことをしらない ) // (adj) insatiable
 KanaAdj0( とぼしい ) // (adj) meagre/meager/scarce/limited/destitute/hard up/scanty/poor/(P)
 KanaAdj0( ともしい ) // (adj) meagre/meager/scarce/limited/destitute/hard up/scanty/poor
 KanaAdj0( わすれっぽい ) // (adj) forgetful
 KanaAdj0( いそがしい ) // (adj) busy/irritated/(P)
 KanaAdj0( せわしい ) // (adj) busy/irritated
 KanaAdj0( せわしない ) // (adj) restless/fidgety/in a hurry
 KanaAdj0( ぼうあくむるい ) // (n,adj-no) incomparably ruthless/diabolical
 KanaAdj0( ぼうれい ) // (adj-na,n) tyranny/atrocity
 KanaAdj0( のぞましい ) // (adj) desirable/hoped for/(P)
 KanaAdj0( ぼうがい ) // (adj-na,n,adj-no) unexpected/unanticipated
 KanaAdj0( むつまじい ) // (adj) harmonious
 KanaAdj0( ほんぽうじざい ) // (n,adj-na) free and uncontrolled/behaving with abandon/freewheeling/totally uninhibited
 KanaAdj0( ほんらい ) // (n-adv,n-t,adj-no) essentially/naturally/by nature/in (and of) itself/originally/(P)
 KanaAdj0( ぼんようぐまい ) // (n,adj-na,adj-no) ordinary and ignorant/mediocre and stupid
 KanaAdj0( またない ) // (adj) unique/matchless/unparalleled/unparallelled/never again
 KanaAdj0( まっこうくさい ) // (adj) smelling of incense/overly pious
 KanaAdj0( すえながい ) // (adj) very long/many years of
 KanaAdj0( すえおそろしい ) // (adj) ominous/likely to grow worse
 KanaAdj0( うらわかい ) // (adj) young/youthful
 KanaAdj0( すえたのもしい ) // (adj) promising (future)
 KanaAdj0( まんざらでもない ) // (adj) not as dissatisfied (or annoyed) as (s)he would have us believe
 KanaAdj0( まんざらゆめではない ) // (adj) not altogether a dream
 KanaAdj0( あじわい ) // (n,adj-no) (1) flavour/flavor/(2) meaning/significance/(P)
 KanaAdj0( あじきない ) // (adj) wearisome/insipid/irksome/wretched/vain
 KanaAdj0( あじけない ) // (adj) wearisome/insipid/irksome/wretched/vain
 KanaAdj0( みかい ) // (adj-na,n,adj-no) savage land/backward region/uncivilized/uncivilised/(P)
 KanaAdj0( みかんせい ) // (adj-na,n,adj-no) incompletion/incomplete/unfinished/(P)
 KanaAdj0( みさい ) // (n,adj-no) executory/unpaid
 KanaAdj0( みてい ) // (adj-na,n) not yet fixed/undecided/pending/(P)
 KanaAdj0( みはらい ) // (n,adj-no) unpaid/overdue/(P)
 KanaAdj0( みれんがましい ) // (adj) (1) regretful/irresolute/(2) unmanly
 KanaAdj0( みょうれい ) // (n,adj-no) young/blooming (age)
 KanaAdj0( ねむい ) // (adj) (1) sleepy/drowsy/(2) aestivation/estivation/(P)
 KanaAdj0( ねむたい ) // (adj) sleepy/(P)
 KanaAdj0( ない ) // (adj) there isn't/doesn't have/(P)
 KanaAdj0( むい ) // (adj-na,n) idleness/inactivity/(P)
 KanaAdj0( むえきゆうがい ) // (n,adj-na) useless and harmful
 KanaAdj0( むがい ) // (adj-na,n) harmlessness/(P)
 KanaAdj0( むかんけい ) // (adj-na,n,adj-no) unrelated/(P)
 KanaAdj0( むきょうかい ) // (adj-no) non-denominational/churchless
 KanaAdj0( むげい ) // (adj-na,n) lacking talent or accomplishments
 KanaAdj0( むげんだい ) // (adj-na,n) infinity
 KanaAdj0( むさい ) // (adj-na,n) lacking talent or ability
 KanaAdj0( むさくい ) // (adj-na,n) at random/unintentional
 KanaAdj0( ぶじたいへい ) // (n,adj-na) peace and quiet/safe and peaceful/tranquil and uneventful
 KanaAdj0( むしょくとうめい ) // (n,adj-na,adj-no) colorless and transparent
 KanaAdj0( むしんけい ) // (adj-na,n) insensibility/thick-skinned/(P)
 KanaAdj0( ぶすい ) // (adj-na,n) no sense of refinement/inelegant/lacking in polish/unromantic/boorish
 KanaAdj0( むたい ) // (adj-na,n) by force/intangible
 KanaAdj0( むちぐまい ) // (n,adj-na) unenlightened/in the darkest ignorance/not knowing from A to B
 KanaAdj0( むちもうまい ) // (adj-na,n) unenlightened/in the darkest ignorance
 KanaAdj0( むていけい ) // (adj-na,n) amorphous/shapeless
 KanaAdj0( むとうせい ) // (adj-na,n) uncontrolled
 KanaAdj0( むはい ) // (n,adj-no) without dividend/(P)
 KanaAdj0( むへんざい ) // (adj-na,n) infinite/boundless
 KanaAdj0( むめい ) // (n,adj-no) unsigned/nameless/anonymous/anonymity/(P)
 KanaAdj0( ぶらい ) // (adj-na,n) villainy
 KanaAdj0( むりかい ) // (adj-na,n) lack of understanding or sympathy
 KanaAdj0( むりむたい ) // (adj-na,n) by force
 KanaAdj0( むるい ) // (adj-na,n) matchless/unequalled/unequaled
 KanaAdj0( ぶれい ) // (adj-na,n) impolite/rude/(P)
 KanaAdj0( めいめい ) // (adj-na,n,adj-no) dark/invisible/divine
 KanaAdj0( なもない ) // (adj) unknown/obscure/insignificant
 KanaAdj0( なだかい ) // (adj) famous/celebrated/well-known/(P)
 KanaAdj0( なごりおしい ) // (adj) regret (at parting)/reluctance (to part)/(P)
 KanaAdj0( あかるい ) // (adj) bright/cheerful/(P)
 KanaAdj0( めいかい ) // (adj-na,n) clarion/clarity/(P)
 KanaAdj0( めいさい ) // (adj-na,n) details/obvious/(P)
 KanaAdj0( めったにない ) // (adj) (uk) rare
 KanaAdj0( おもはゆい ) // (adj) embarrassed/self-conscious/bashful/abashed
 KanaAdj0( つらにくい ) // (adj) provoking/offensive
 KanaAdj0( めんどい ) // (adj) troublesome/bothersome
 KanaAdj0( めんどうくさい ) // (adj) bother to do/tiresome/(P)
 KanaAdj0( おもしろい ) // (adj) interesting/amusing/(P)
 KanaAdj0( おもしろおかしい ) // (adj) humorous/humourous/funny
 KanaAdj0( めんぼくない ) // (adj) ashamed
 KanaAdj0( けぶかい ) // (adj) hairy/thickly haired
 KanaAdj0( たけだけしい ) // (adj) ferocious
 KanaAdj0( こぶかい ) // (adj) deep in the woods
 KanaAdj0( もくせい ) // (n,adj-no) wooden/made of wood/(P)
 KanaAdj0( めがない ) // (adj) extremely fond of/having a weakness for
 KanaAdj0( めぼしい ) // (adj) main/chief/important/valuable
 KanaAdj0( めまぐるしい ) // (adj) hectic/bewildering/bustling/dizzy
 KanaAdj0( めもくれない ) // (adj) indifferent/paying no attention/taking no notice
 KanaAdj0( めいっぱい ) // (adj-na,adv,n) with all one's might
 KanaAdj0( めざましい ) // (adj) (arch) brilliant/splendid/striking/remarkable/(P)
 KanaAdj0( めでたい ) // (adj) happy/simple soul/propitious/joyous/(P)
 KanaAdj0( めあたらしい ) // (adj) original/novel/new
 KanaAdj0( めばやい ) // (adj) sharp-eyed
 KanaAdj0( めざとい ) // (adj) (1) sharp sighted/(2) easily awakened
 KanaAdj0( もったいない ) // (adj) (uk) too good/more than one deserves/wasteful/sacrilegious/unworthy of
 KanaAdj0( もっともらしい ) // (adj) plausible/(P)
 KanaAdj0( よぶかい ) // (adj) (staying) up late at night
 KanaAdj0( やろうじだい ) // (adj-na,n) throwing one's weight around in a small group without knowing one's real worth in a larger world outside
 KanaAdj0( やがい ) // (n,adj-no) fields/outskirts/open air/suburbs/(P)
 KanaAdj0( やせい ) // (n,adj-no) wild (nature)/uncouth/rough/unpolished/(P)
 KanaAdj0( のぶとい ) // (adj) audacious/throaty (voice)
 KanaAdj0( やぼったい ) // (adj) unfashionable (e.g., clothes)/uncouth/unpolished
 KanaAdj0( やっかい ) // (adj-na,n) trouble/burden/care/bother/worry/dependence/support/kindness/obligation/(P)
 KanaAdj0( わけがわからない ) // (adj) incomprehensible
 KanaAdj0( わけない ) // (adj) (1) easy/simple/(exp) (2) (there is) no reason
 KanaAdj0( たのしい ) // (adj) enjoyable/fun
 KanaAdj0( ゆかい ) // (adj-na,n) pleasant/happy/(P)
 KanaAdj0( あぶらっこい ) // (adj) (uk) greasy/fatty/oily
 KanaAdj0( いやしけい ) // (n,adj-no) healing (system)/rejeuvenating/refreshing/soothing
 KanaAdj0( やさしい ) // (adj) tender/kind/gentle/graceful/affectionate/amiable/suave/(P)
 KanaAdj0( まさるともおとらない ) // (adj) not at all inferior to
 KanaAdj0( ゆうせい ) // (adj-na,n) superiority/superior power/predominance/preponderance/(P)
 KanaAdj0( いさましい ) // (adj) brave/valiant/gallant/courageous/(P)
 KanaAdj0( ゆうまい ) // (adj-na) heroic/courageous
 KanaAdj0( ゆうすい ) // (adj-na,n) retired and quiet
 KanaAdj0( うい ) // (adj) unhappy/sad/gloomy
 KanaAdj0( ありもしない ) // (adj) nonexistent/unreal/imaginary/spurious
 KanaAdj0( ありてい ) // (adj-na,n) the unvarnished truth
 KanaAdj0( ゆうえきむがい ) // (n,adj-na) beneficial and harmless
 KanaAdj0( ゆうがい ) // (adj-na,n) harmfulness/(P)
 KanaAdj0( ありがたい ) // (adj) grateful/thankful/welcome/appreciated/evoking gratitude/(P)
 KanaAdj0( ゆうめい ) // (adj-na,n) fame/(P)
 KanaAdj0( ゆうめいむめい ) // (n,adj-no) well-known and unknown/somebodies and nobodies/both famous and humble
 KanaAdj0( ゆゆしい ) // (adj) grave/serious/alarming
 KanaAdj0( ゆうい ) // (adj-na,n) magnificent
 KanaAdj0( ゆうだい ) // (adj-na,n) grandeur/magnificence/splendour/splendor/(P)
 KanaAdj0( おおしい ) // (adj) manly/brave/heroic
 KanaAdj0( ゆうけい ) // (adj-na,n) vigorous/powerful
 KanaAdj0( よそうがい ) // (adj-na,n) unexpected/unforeseen/strange/(P)
 KanaAdj0( あまりおもしろくない ) // (adj) not very interesting
 KanaAdj0( よぎない ) // (adj) unavoidable/inevitable/beyond one's control
 KanaAdj0( よけい ) // (adj-na,adv,n) too much/unnecessary/abundance/surplus/excess/superfluity/(P)
 KanaAdj0( よそよそしい ) // (adj) distant/cold/formal
 KanaAdj0( いとけない ) // (adj) very young/childish
 KanaAdj0( おさない ) // (adj) very young/childish/(P)
 KanaAdj0( いたいけない ) // (adj) (uk) innocent/helpless/tender
 KanaAdj0( ようせい ) // (adj-na,n) larva/larvae
 KanaAdj0( あやしい ) // (adj) (1) suspicious/dubious/doubtful/(adj) (2) charming/bewitching
 KanaAdj0( ようい ) // (adj-na,n) easy/simple/plain/(P)
 KanaAdj0( たやすい ) // (adj) (uk) easy/simple/light/(P)
 KanaAdj0( ようがんびれい ) // (n,adj-na) beautiful face/attractive features
 KanaAdj0( ようぼうかいい ) // (n,adj-na) (a man) having a commanding face and a powerful physique
 KanaAdj0( ようぼうたんせい ) // (n,adj-na) having handsome and clean-cut features
 KanaAdj0( ゆるぎない ) // (adj) solid/firm/steady
 KanaAdj0( ようにたりない ) // (adj) be of no use/be useless
 KanaAdj0( ようじんぶかい ) // (adj) wary/watchful/(P)
 KanaAdj0( おさえがたい ) // (adj) uncontrollable/irrepressible
 KanaAdj0( ほしい ) // (adj) wanted/wished for/in need of/desired/(P)
 KanaAdj0( よくふかい ) // (adj) greedy
 KanaAdj0( たのみすくない ) // (adj) helpless
 KanaAdj0( たのもしい ) // (adj) reliable/trustworthy/hopeful/promising/(P)
 KanaAdj0( たよりがい ) // (n,adj-no) reliability/trustworthiness/dependability
 KanaAdj0( たよりない ) // (adj) unreliable/undependable/flaky/vague/helpless/forlorn
 KanaAdj0( らんけい ) // (n,adj-no) oval/egg-shaped/(P)
 KanaAdj0( たまごだい ) // (adj-no) egg-sized
 KanaAdj0( りくつっぽい ) // (adj) argumentative
 KanaAdj0( りっすいのよちもない ) // (adj) tightly packed/full to capacity
 KanaAdj0( りゅうかい ) // (n,vs) cancelling a meeting/adjournment of a meeting (due to lack of attendance)
 KanaAdj0( りゅうこうせい ) // (n,adj-no) epidemic
 KanaAdj0( りゅうれい ) // (adj-na,n) fluent/flowing/elegant
 KanaAdj0( とめどない ) // (adj) endless/ceaseless
 KanaAdj0( りゅうせい ) // (adj-na,n) prosperity/(P)
 KanaAdj0( りょがい ) // (adj-na,n,adj-no) unexpected
 KanaAdj0( りょうせい ) // (adj-na,n) amphibian
 KanaAdj0( すずしい ) // (adj) cool/refreshing/(P)
 KanaAdj0( よい ) // (adj) (uk) good/nice/pleasant/fine/excellent/agreeable/ok/(P)
 KanaAdj0( ちからづよい ) // (adj) reassuring/emboldened/(P)
 KanaAdj0( ちからない ) // (adj) feeble
 KanaAdj0( さびしい ) // (adj) lonely/lonesome/solitary/desolate
 KanaAdj0( さみしい ) // (adj) lonely/lonesome/solitary/desolate
 KanaAdj0( りんけい ) // (n,adj-no) ring-shaped/circular
 KanaAdj0( りんせつぶたい ) // (n) adjacent units
 KanaAdj0( なみだぐましい ) // (adj) touching/moving/painful/(P)
 KanaAdj0( なみだもろい ) // (adj) easily moved to tears
 KanaAdj0( るいるい ) // (adj-t,adv-to) in heaps
 KanaAdj0( るいのない ) // (adj) unprecedented/unparalleled/unparallelled
 KanaAdj0( れいがい ) // (n,adj-no) exception/(P)
 KanaAdj0( つめたい ) // (adj) cold (to the touch)/chilly/icy/freezing/coldhearted/(P)
 KanaAdj0( れいせい ) // (adj-na,n) calm/composure/coolness/serenity/(P)
 KanaAdj0( れいぎただしい ) // (adj) polite (person)
 KanaAdj0( れいさい ) // (adj-na,n) insignificant/trifling/paltry/(P)
 KanaAdj0( うるわしい ) // (adj) beautiful/lovely
 KanaAdj0( れいれいしい ) // (adj) ostentatious/gaudy/showy
 KanaAdj0( れっせい ) // (adj-na,n) numerical inferiority/(P)
 KanaAdj0( はげしい ) // (adj) violent/vehement/intense/furious/tempestuous
 KanaAdj0( こいしい ) // (adj) (1) dear/beloved/darling/(2) yearned for/(P)
 KanaAdj0( れんたいけい ) // (n) (ling) participle adjective/attributive form
 KanaAdj0( ろれつがまわらない ) // (adj) speaking inarticulately (slurring, lisping, etc)
 KanaAdj0( いたわしい ) // (adj) heartrending/pitiful
 KanaAdj0( ろうじんせい ) // (adj-na) senile/(P)
 KanaAdj0( ろうせい ) // (adj-na,n,vs) mature/becoming precocious
 KanaAdj0( ろうかい ) // (adj-na,n) cunning/crafty
 KanaAdj0( ろんがい ) // (adj-na,n) out of the question/(P)
 KanaAdj0( ろんしふめい ) // (n,adj-na) the point of an argument being unclear/the tenor of an argument being poorly reasoned
 KanaAdj0( ろんしめいかい ) // (n,adj-na) the point of an argument being clearly stated/the tenor of an argument being well-reasoned
 KanaAdj0( わきあいあい ) // (adj-na,adj-t) (1) harmonious/(n) (2) peace and harmony
 KanaAdj0( うでがいい ) // (adj) be able/be skilled
 KanaAdj0( かったるい ) // (adj) (1) (uk) listless/languid/sluggish/(2) irritating/exasperating/tiresome
 KanaAdj0( ほのぐらい ) // (adj) gloomy/obscure
 KanaAdj0( ほのじろい ) // (adj) dimly white
 KanaAdj0( わびしい ) // (adj) miserable/wretched/lonely/dreary/shabby/comfortless
 KanaAdj0( ままならない ) // (adj) (uk) unable to have one's way with
 KanaAdj0( はかない ) // (adj) fleeting/transient/short-lived/momentary/vain/fickle/miserable/empty/ephemeral/(P)
 KanaAdj0( べきれい ) // (adj-no) (math) nilpotent
 KanaAdj0( りりしい ) // (adj) gallant/brave/imposing/awe-inspiring/severe/biting/chivalrous/manly/dignified
 KanaAdj0( ていねい ) // (adj-na,n) polite/courteous/careful/care/kind/close/thorough/conscientious
 KanaAdj0( やぶさかでない ) // (adj) be ready (to do)/willing
 KanaAdj0( かしがましい ) // (adj) (1) noisy/boisterous
 KanaAdj0( かしましい ) // (adj) (1) noisy/boisterous
 KanaAdj0( かまびすしい ) // (adj) (1) noisy/boisterous
 KanaAdj0( らちがあかない ) // (adj) make no progress/remain unsettled
 KanaAdj0( おびただしい ) // (adj) abundantly/innumerably/(P)
 KanaAdj0( あだっぽい ) // (adj) coquettish
 KanaAdj0( ぼうだい ) // (adj-na,n) huge/bulky/enormous/extensive/swelling/expansion
 KanaAdj0( かたじけない ) // (adj) grateful/indebted
 KanaAdj0( つつがない ) // (adj) well/in good health/safe/free from accident
 KanaAdj0( おぞましい ) // (adj) (uk) disgusting/repulsive
 KanaAdj0( いんぎんぶれい ) // (adj-na,n) hypocritical courtesy/superficially polite but rude in intent
 KanaAdj0( なまじい ) // (adj-na) (uk) thoughtlessly/rashly
 KanaAdj0( くすぐったい ) // (adj) (uk) ticklish/(P)
 KanaAdj0( あいまい ) // (adj-na,n) vague/ambiguous/unclear/(P)
 KanaAdj0( こうせい ) // (n,adj-no) unparalleled/unparallelled/matchless
 KanaAdj0( うったい ) // (n,adj-no,vs) (uk) congestion/pent-up feelings
 KanaAdj0( うっとうしい ) // (oK) (adj) (uk) gloomy/depressing/(P)
 KanaAdj0( いんせい ) // (adj-na,n) prosperity
 KanaAdj0( けばけばしい ) // (adj) (uk) gaudy/showy/garish/loud
 KanaAdj0( しゃらくくさい ) // (adj) impertinent/impudent/cheeky
 KanaAdj0( しゃらくさい ) // (adj) impertinent/impudent/cheeky
 KanaAdj0( けいけい ) // (adj-na,n) glaring
 KanaAdj0( ずるい ) // (adj) (uk) sly/cunning/(P)
 KanaAdj0( ずるがしこい ) // (adj-na) sly/(P)
 KanaAdj0( こうかつろうかい ) // (n,adj-na) sly and crafty
 KanaAdj0( けんかい ) // (adj-na) obstinate/stubborn/headstrong
 KanaAdj0( みだりがましい ) // (adj) morally corrupt
 KanaAdj0( みだりがわしい ) // (adj) morally corrupt/slovenly/obscene
 KanaAdj0( きけい ) // (adj-na,n) deformity/abnormality
 KanaAdj0( やましい ) // (adj) (feel) guilty/(having a) guilty conscience
 KanaAdj0( かんだかい ) // (adj) high-pitched/shrill
 KanaAdj0( かゆい ) // (adj) itchy/itching/(P)
 KanaAdj0( まばゆい ) // (adj) dazzling/glaring/dazzlingly beautiful
 KanaAdj0( まぶい ) // (io) (adj) (col) (uk) cute/pretty
 KanaAdj0( まぶしい ) // (adj) dazzling/radiant/(P)
 KanaAdj0( もうまい ) // (oK) (adj-na,n) ignorance/(lack of) enlightenment or civilization (civilisation)/unenlightened/uncivilized/uncivilised
 KanaAdj0( きれい ) // (oK) (adj-na) (uk) pretty/clean/nice/tidy/beautiful/fair
 KanaAdj0( そうめい ) // (adj-na,n) wisdom/sagacity
 KanaAdj0( はいせい ) // (adj-na) embryonic/embryonal
 KanaAdj0( ふがいない ) // (adj) disappointing/weak-minded/spiritless/cowardly/worthless
 KanaAdj0( なまぐさい ) // (adj) smelling of fish or blood/fish or meat
 KanaAdj0( にべもない ) // (adj) (uk) curt/point-blank
 KanaAdj0( いぶかしい ) // (adj) suspicious/doubtful
 KanaAdj0( くどい ) // (adj) (uk) verbose/importunate/heavy (taste)/(P)
 KanaAdj0( いやしい ) // (adj) greedy/vulgar/shabby/humble/base/mean/vile
 KanaAdj0( そううつやまい ) // (n,adj-no) manic depression/manic-depressive psychosis/bipolar disorder
 KanaAdj0( たくましい ) // (adj) (uk) burly/strong/sturdy/(P)
 KanaAdj0( あわただしい ) // (adj) busy/hurried/confused/flurried
 KanaAdj0( ひわい ) // (adj-na,n) (uk) indecent/obscene
 KanaAdj0( かったつじざい ) // (n,adj-na) broad-minded and free in disposition/large-hearted and not scrupulous about trifles
 KanaAdj0( あいたい ) // (adj-t,adv-to) trailing clouds
 KanaAdj0( たいはい ) // (n,vs,adj-no) degeneration/decadence/deterioration/laxness/corruption
 KanaAdj0( ひだるい ) // (adj) (uk) hungry
 KanaAdj0( だまされやすい ) // (adj) (uk) gullible/naive
 KanaAdj0( かびくさい ) // (adj) musty/putrid

// KanaAdj1( い ) // (adj-na,n) greatness
 KanaAdj1( あんな ) // (adj-na,adj-pn) such/so/that/sort of/(P)
 KanaAdj1( いくつもの ) // (adj-no) many/great number of
 KanaAdj1( こんな ) // (adj-na,adj-pn,adv,n) such/like this/(P)
 KanaAdj1( そんな ) // (adj-na,adj-pn,adv,n) such/like that/that sort of/(P)
 KanaAdj1( どんな ) // (adj-na,adj-pn,n) what/what kind of/(P)
 KanaAdj1( ひょんな ) // (adj-pn) strange/unexpected/curious
 KanaAdj1( へなへな ) // (adj-na,adv,n,vs) bending/loss of strength
 KanaAdj1( おすなおすな ) // (adj-no) crowded (e.g. with people)/overflowing
 KanaAdj1( どの ) // (adj-pn) (uk) which/what (way)/(P)
 KanaAdj1( なんの ) // (adj-pn) what kind/what sort
 KanaAdj1( おかしな ) // (adj-pn) ridiculous/odd/(P)
 KanaAdj1( あかずの ) // (adj-no) (1) unopened/(2) forbidden
 KanaAdj1( かたくな ) // (adj-na) (uk) obstinate/(P)
 KanaAdj1( この ) // (adj-pn,int) (uk) this/(P)
 KanaAdj1( これらの ) // (adj-no) (uk) these
 KanaAdj1( いろんな ) // (adj-pn) various/(P)
 KanaAdj1( しんの ) // (adj-pn) true/real/genuine/utter/(P)
 KanaAdj1( さな ) // (adj-na,adv,n) truth/reality
 KanaAdj1( その ) // (adj-pn) (uk) the/that
 KanaAdj1( ながの ) // (adj) long/eternal
 KanaAdj1( とうの ) // (adj-pn,pref) the .. in question/(P)
// KanaAdj1( の ) // (prt) (1) (uk) indicates possessive/(2) verb and adjective nominalizer (nominaliser)/(3) indicates question (sentence end)
 KanaAdj1( あの ) // (adj-pn) (uk) that over there/(P)
 KanaAdj1( かの ) // (adj-pn) (uk) that over there
 KanaAdj1( あれらの ) // (adj-no) their
 KanaAdj1( かれらの ) // (adj-no) their
 KanaAdj1( ぶしょうもの ) // (adj-na,n) slouch/lazybones
 KanaAdj1( こなごな ) // (adj-na,n) in very small pieces
 KanaAdj1( ほんの ) // (adj-pn) (uk) mere/only/just/(P)
 KanaAdj1( あじな ) // (adj-pn) smart/clever/witty/strange
 KanaAdj1( あらずもがな ) // (adj-no) uncalled for/unnecessary/gratuitous
 KanaAdj1( こしらえもの ) // (adj-na,n) fake/imitation
 
 KanaAdj1( にぎやか ) // оживленный 
 KanaAdj1( ハンサムな ) // привлекательный
 KanaAdj1( きれいな ) // чистый
 KanaAdj1( フレッシュな ) // свежий, молодой
 KanaAdj1( モダンな ) // современный
 KanaAdj1( ぜいたくな ) // богатый, обеспеченный
 KanaAdj1( 大きな ) // большой
 KanaAdj1( 小さな ) // небольшой

}
