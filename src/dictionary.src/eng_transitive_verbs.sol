// CD->02.04.2010
// LC->05.02.2016

// глаголы с обязательной транзитивностью
#define vot(v) tag ENG_VERB:v { TRANSITIVITY:TRANSITIVE OBLIG_TRANSITIVITY:1 }

// глаголы с опциональной транзитивностью
#define vt(v) tag ENG_VERB:v { TRANSITIVITY:TRANSITIVE }

// непереходные глаголы
#define vi(v) tag ENG_VERB:v { TRANSITIVITY:INTRANSITIVE }

automat sg
{
 vt( gate )
 vt( contribute ) // There are a number of contributing factors.
 vt( cease ) // The cable station ceased operation in 1966.
 vt( discontinue ) // The national carrier discontinued operations in 2002.
 vt( cool ) // They are often cooled by liquid nitrogen.
 vt( energize ) // Its citizens energized us from the outset.
 vt( rank ) // This ranks a set of given possibilities.
 vt( retire ) // The Red Wings have retired seven numbers.
 vt( command ) // Gabre Heard commanded the forces in Somalia.
 vt( underutilize ) // Unfortunately, this resource remain terribly underutilized.
 vt( headquarter ) // It is headquartered in Copenhagen, Denmark.
 vt( speculate ) // Life on Mars has been long speculated.
 vt( approximate )  // In practice the ideal impedances are only approximated.
 vt( reuse ) // The desiccants can be dried and reused.
 vt( prompt ) // Identity of function prompts identity in name.
 vt( grasp ) // It can only be shown and grasped.
 vt( elect ) // It also elected him U.S. Senator again.
 vt( sport ) // He sported one-off helmet designs four times.
 vt( pan ) // The album was widely panned by critics;
 vt( Americanize ) // Immigrants to America often Americanized their names.
 vt( crumple )
 vt( license ) // No English-speaking country has licensed it to date.
 vt( colonise ) // Ants have colonised almost every landmass on Earth.
 vt( term ) // Most Protestants term these books as apocrypha.
 vt( terminate ) // Terminated crystals are relatively rare.
 vt( coach ) // Toney was later coached by Trevor Sherman.
 vt( practise ) // Islam is practised primarily by ethnic Malays.
 vt( border ) // It borders the London Borough of Bexley.
 vt( instruct ) // Gregory also instructed Augustine on other matters.
 vt( criminalise ) // The law does not criminalise spousal rape;
 vt( class ) // U.S. veterans class action lawsuit against manufacturers.
 vt( govern ) // Strict rules govern student life at BJU.
 vt( yield ) // 
 vt( emphasize )
 vt( acknowledge )
 vt( chip )
 vt( mate ) // 
 vt(note) // Note the unclear horizon near the center.
 vt(decrease) // decrease blood flow to the skin.
 vt(aid) // Which has the greatest effect on aiding the movement of blood through the human body?
 vt(necessitate) // This necessitates the satisfying of five equations;
 vt(characterize) // Their long thin legs also characterize them.
 vt(seize) // The sailors also seized molasses and wool.
 vt(rediscover) // The latter was recently rediscovered under water.
 vt(situate) // It is situated in the Ulus quarter.
 vt(weigh) // One California grizzly weighed pounds.
 vt(twin) // Yalta is twinned with the following cities:
 vt(permit) // It also permitted multiple protected mode clients.
 vt(generalise) // Newton's generalised binomial theorem.
 vt(vote) // The measure was voted down.
 vt(track) // Sixty commodities are tracked weekly.
 vt(expand) // He expanded the imperial palace.
 vt(incorporate) // Huxley also incorporated Bird into the novel.
 vt(gulp) // The subdued prey is gulped down whole.
 vt(operate) // This line is operated by the SNCF.
 vt(judge) // The contest was judged by the Muses.
 vt(tape) // The Show is taped there.
 vt(reconstitute) // Both parties have since reconstituted.
 vt(guarantee) // This guaranteed predictable annual income.
 vt(recognise) // Ten families are currently recognised.
 vt(withdraw) // 85 was withdrawn from circulation.
 vt(succeed) // Constantine succeeded him as king.
 vt(mine) // Nickel is mined at Bonao.
 vt(dispute) // Some historians dispute this estimate.
 vt(suffer) // In 1961 he suffered strokes.
 vt(resist) // The early Church resisted asceticism.
 vt(regret) // They appear Monday through Saturday;
 vt(join) // Seven countries have since joined.
 vt(settle) // The matter is not yet settled.
 vt(issue) // Pope Francis issues a challenge;
 vt(encourage) // Using alternative transportation is encouraged.
 vt(reveal) // Batgirl reveals herself as Barbara.
 vt(speed) // An index speeds the search.
 vt(boast) // Baku boasts a vibrant nightlife.
 vt(generalize) // Eyewitnesses reported a foul odor.
 vt(report) // Eyewitnesses reported a foul odor.
 vt(mentor) // She mentored the Teens category;
 vt(end) // The marriage ended in 1975.
 vt(appreciate) // Feedback is greatly appreciated!
 vt(power)
 vt(commit) // To commit a violent injury;
 vt(recover) // Samples are also easily recovered.
 vt(denature) //  enzymes denature invasive bacteria
 vot(beatify) // Albert was beatified in 1622.
 vot(refold)
 vot(reclassify)
 vot( use )
 vot( find )
 vot(nominate) // Grant was nominated for president
 vt( abate )
 vt( abound )
 vt( about-face )
 vt( abscond )
 vt( abstain )
 vt( accede )
 vt( account )
 vt( accrue )
 vt( ache )
 vt( acquiesce )
 vt( ad-lib )
 vt( adhere )
 vt( adjoin )
 vt( alight )
 vt( allude )
 vt( ally )
 vt( amount )
 vt( apologize )
 vt( appertain )
 vt( aquaplane )
 vt( arise )
// vt( arrive )
 vt( assent )
 vt( atone )
 vt( atrophy )
 vt( baa )
 vt( babble )
 vt( babysit )
 vt( backfire )
 vt( backpedal )
 vt( backslide )
 vt( backspace )
 vt( balk )
 vt( balloon )
 vt( banquet )
 vt( banter )
 vt( bark )
 vt( barnstorm )
 vt( bask )
 vt( bawl )
 vt( bay )
 vt( beetle )
 vt( behave )
 vt( belch )
 vt( bellyache )
 vt( belong )
 vt( bicker )
 vt( bicycle )
 vt( billow )
 vt( blabber )
 vt( blather )
 vt( blaze )
 vt( bleat )
 vt( bleed )
 vt( bleep )
 vt( bloom )
 vt( blossom )
 vt( blubber )
 vt( blunder )
 vt( blush )
 vt( bode )
 vt( boom )
 vt( brake )
 vt( brawl )
 vt( bray )
 vt( bristle )
 vt( brood )
 vt( browse )
 vt( bubble )
 vt( bud )
 vt( bullshit )
 vt( bunk )
 vt( burble )
 vt( burgeon )
 vt( burp )
 vt( bustle )
 vt( cackle )
 vt( campaign )
 vt( canoe )
 vt( canter )
 vt( caper )
 vt( capitulate )
 vt( careen )
 vt( carol )
 vt( carouse )
 vt( cascade )
 vt( castle )
 vt( cater )
 vt( caterwaul )
 vt( cavil )
 vt( cavort )
 vt( chafe )
 vt( chatter )
 vt( cheep )
 vt( chirp )
 vt( chirrup )
 vt( chortle )
 vt( chuckle )
 vt( chug )
 vt( chum )
 vt( clack )
 vt( clamber )
 vt( clamor )
 vt( clamour )
 vt( clank )
 vt( clash )
 vt( clatter )
 vt( clerk )
 vt( climax )
 vt( cling )
 vt( cluck )
 vt( clunk )
 vt( cluster )
 vt( co-operate )
 vt( coalesce )
 vt( coast )
 vt( coexist )
 vt( cohabit )
 vt( cohere )
 vt( coincide )
 vt( collaborate )
 vt( collide )
 vt( commentate )
 vt( commiserate )
 vt( commune )
 vt( compete )
 vt( comply )
 vt( compromise )
 vt( confab )
 vt( confabulate )
 vt( conflict )
 vt( conform )
 vt( congeal )
 vt( congregate )
 vt( connive )
 vt( consort )
 vt( conspire )
 vt( convalesce )
 vt( converge )
 vt( converse )
 vt( coo )
 vt( cooperate )
 vt( cope )
 vt( copulate )
 vt( correspond )
 vt( cower )
 vt( crackle )
 vt( crash-dive )
 vt( creak )
 vt( crest )
 vt( cringe )
 vt( croak )
 vt( crow )
 vt( crusade )
 vt( culminate )
 vt( curtsey )
 vt( curtsy )
 vt( cycle )
 vt( dabble )
 vt( dally )
 vt( dawdle )
 vt( dawn )
 vt( daydream )
 vt( decamp )
 vt( decay )
 vt( default )
 vt( defecate )
 vt( defect )
 vt( degenerate )
 vt( deliberate )
 vt( delve )
 vt( demur )
 vt( depart )
 vt( depend )
 vt( deplane )
 vt( depreciate )
 vt( deputize )
 vt( desist )
 vt( despair )
 vt( deteriorate )
 vt( detract )
 vt( deviate )
 vt( devolve )
 vt( diet )
 vt( differ )
 vt( digress )
 vt( dilly-dally )
 vt( disagree )
 vt( disappear )
 vt( discourse )
 vt( discriminate )
 vt( disembark )
 vt( disintegrate )
 vt( disrobe )
 vt( dissemble )
 vt( dissent )
 vt( dither )
 vt( diverge )
 vt( dodder )
 vt( domineer )
 vt( doodle )
 vt( dote )
 vt( double-park )
 vt( dovetail )
 vt( drawl )
 vt( drizzle )
 vt( drool )
 vt( duel )
 vt( dwell )
 vt( dwindle )
 vt( eavesdrop )
 vt( ebb )
 vt( economize )
 vt( eddy )
 vt( effervesce )
 vt( elapse )
 vt( elope )
 vt( emanate )
 vt( embark )
 vt( emerge )
 vt( emigrate )
 vt( encamp )
 vt( encroach )
 vt( enquire )
 vt( ensue )
 vt( err )
 vt( erupt )
 vt( evaporate )
 vt( excel )
 vt( exist )
 vt( exit )
 vt( expatiate )
 vt( experiment )
 vt( expire )
 vt( expostulate )
 vt( exult )
 vt( faint )
 vt( falter )
 vt( fare )
 vt( fart )
 vt( fast )
 vt( fawn )
 vt( feint )
 vt( fester )
 vt( fib )
 vt( fidget )
 vt( filibuster )
 vt( fizz )
 vt( flail )
 vt( flake )
 vt( flame )
 vt( flicker )
 vt( flinch )
 vt( flirt )
 vt( flit )
 vt( flop )
 vt( flounder )
 vt( flourish )
 vt( flower )
 vt( fluctuate )
 vt( flutter )
 vt( fly-fish )
 vt( forage )
 vt( foregather )
 vt( fornicate )
 vt( fossilize )
 vt( foxhunt )
 vt( fragment )
 vt( fraternize )
 vt( freelance )
 vt( freewheel )
 vt( fret )
 vt( froth )
 vt( frown )
 vt( fulminate )
 vt( fume )
 vt( function )
 vt( fuss )
 vt( gallivant )
 vt( galumph )
 vt( gambol )
 vt( gape )
 vt( garden )
 vt( gawp )
 vt( gaze )
 vt( gel )
 vt( genuflect )
 vt( gesticulate )
 vt( gesture )
 vt( gibe )
 vt( giggle )
 vt( glare )
 vt( gleam )
 vt( glide )
 vt( glimmer )
 vt( glint )
 vt( glisten )
 vt( glitter )
 vt( gloat )
 vt( globetrot )
 vt( glory )
 vt( glow )
 vt( glower )
 vt( goggle )
 vt( golf )
 vt( gossip )
 vt( graduate )
 vt( grapple )
 vt( gravitate )
 vt( gray )
 vt( graze )
 vt( grey )
 vt( grimace )
 vt( grin )
 vt( groove )
 vt( grouch )
 vt( grouse )
 vt( grovel )
 vt( guffaw )
 vt( gurgle )
 vt( gybe )
 vt( gyrate )
 vt( haggle )
 vt( hanker )
 vt( hark )
 vt( harp )
 vt( haw )
 vt( hearken )
 vt( heel )
 vt( hibernate )
 vt( hiccough )
 vt( hiccup )
 vt( hinge )
 vt( hiss )
 vt( hitchhike )
 vt( hobnob )
 vt( holler )
 vt( honeymoon )
 vt( hover )
 vt( huddle )
 vt( huff )
 vt( hunger )
 vt( hurtle )
 vt( ice-skate )
 vt( immigrate )
 vt( impend )
 vt( impinge )
 vt( inch )
 vt( innovate )
 vt( interact )
 vt( intercede )
 vt( intercommunicate )
 vt( interfere )
 vt( intermarry )
 vt( intermingle )
 vt( intervene )
 vt( introspect )
 vt( intrude )
 vt( inveigh )
 vt( itch )
 vt( jabber )
 vt( jack-knife )
 vt( jaunt )
 vt( jaw )
 vt( jaywalk )
 vt( jell )
 vt( jest )
 vt( jibe )
 vt( jive )
 vt( jockey )
 vt( joke )
 vt( journey )
 vt( joust )
 vt( kowtow )
 vt( lag )
 vt( languish )
 vt( lapse )
 vt( laugh )
 vt( leaf )
 vt( leer )
 vt( legislate )
 vt( liaise )
 vt( lip-read )
 vt( lisp )
 vt( live )
 vt( loaf )
 vt( loiter )
 vt( loll )
 vt( long )
 vt( lope )
 vt( lounge )
 vt( lumber )
 vt( lurk )
 vt( lust )
 vt( luxuriate )
 vt( major )
 vt( malfunction )
 vt( malinger )
 vt( marvel )
 vt( masquerade )
 vt( materialize )
 vt( matriculate )
 vt( maturate )
 vt( mature )
 vt( maunder )
 vt( meander )
 vt( meddle )
 vt( meditate )
 vt( menstruate )
 vt( metamorphose )
 vt( mew )
 vt( miaou )
 vt( miaow )
 vt( migrate )
 vt( militate )
 vt( mingle )
 vt( minister )
 vt( misbehave )
 vt( misfire )
 vt( molt )
 vt( monkey )
 vt( moo )
 vt( mooch )
 vt( mope )
 vt( moralize )
 vt( mosey )
 vt( motion )
 vt( motor )
 vt( mushroom )
 vt( mutiny )
 vt( name-drop )
 vt( nap )
 vt( natter )
 vt( neck )
 vt( neigh )
 vt( nest )
 vt( network )
 vt( niggle )
 vt( nosedive )
 vt( nosh )
 vt( object )
 vt( occur )
 vt( officiate )
 vt( orate )
 vt( oscillate )
 vt( outgo )
 vt( overact )
 vt( overbid )
 vt( overeat )
 vt( overlie )
 vt( overreact )
 vt( oversleep )
 vt( pale )
 vt( pall )
 vt( palpitate )
 vt( pander )
 vt( panhandle )
 vt( panic )
 vt( pant )
 vt( parachute )
 vt( parley )
 vt( partake )
 vt( participate )
 vt( patter )
 vt( pause )
 vt( peak )
 vt( pearl )
 vt( peep )
 vt( perambulate )
 vt( percolate )
 vt( perish )
 vt( persevere )
 vt( persist )
 vt( perspire )
 vt( pertain )
 vt( philander )
 vt( philosophize )
 vt( picnic )
 vt( piddle )
 vt( pimp )
 vt( ping )
 vt( pirouette )
 vt( pivot )
 vt( plod )
 vt( plummet )
 vt( politick )
 vt( pontificate )
 vt( pore )
 vt( posture )
 vt( potter )
 vt( pounce )
 vt( pout )
 vt( powwow )
 vt( prance )
 vt( prate )
 vt( prattle )
 vt( pre-exist )
 vt( predominate )
 vt( preside )
 vt( prevail )
 vt( prevaricate )
 vt( prey )
 vt( primp )
 vt( procrastinate )
 vt( procreate )
 vt( profit )
 vt( profiteer )
 vt( progress )
 vt( proliferate )
 vt( propagandize )
 vt( proselytize )
 vt( prosper )
 vt( protrude )
 vt( pub-crawl )
 vt( pulsate )
 vt( pulse )
 vt( pun )
 vt( purr )
 vt( pussyfoot )
 vt( putrefy )
 vt( putter )
 vt( quack )
 vt( quake )
 vt( quarrel )
 vt( quarry )
 vt( quaver )
 vt( quest )
 vt( queue )
 vt( quibble )
 vt( quip )
 vt( quiver )
 vt( racket )
 vt( raft )
 vt( rage )
 vt( rail )
 vt( rain )
 vt( ramble )
 vt( rampage )
 vt( range )
 vt( rankle )
 vt( rant )
 vt( rasp )
 vt( rat )
 vt( rave )
 vt( re-echo )
 vt( react )
 vt( reappear )
 vt( rebel )
 vt( rebound )
 vt( recede )
 vt( recline )
 vt( recoil )
 vt( reconnoitre )
 vt( recriminate )
 vt( recuperate )
 vt( recur )
 vt( redound )
 vt( refrain )
 vt( regress )
 vt( reign )
 vt( rejoice )
 vt( relapse )
 vt( relent )
 vt( rely )
 vt( reminisce )
 vt( remonstrate )
 vt( rendezvous )
 vt( renege )
 vt( reside )
 vt( resign )
 vt( resonate )
 vt( resort )
 vt( resound )
 vt( rest )
 vt( result )
 vt( resurface )
 vt( retaliate )
 vt( retch )
 vt( retreat )
 vt( retrench )
 vt( retrograde )
 vt( retrogress )
 vt( revel )
 vt( reverberate )
 vt( revert )
 vt( revolt )
 vt( revolve )
 vt( rhapsodize )
 vt( riot )
 vt( ripen )
 vt( riposte )
 vt( ripple )
 vt( rocket )
 vt( romance )
 vt( romp )
 vt( room )
 vt( roost )
 vt( rough-house )
 vt( rove )
 vt( rumble )
 vt( ruminate )
 vt( rummage )
 vt( rust )
 vt( sag )
 vt( salivate )
 vt( saunter )
 vt( scamper )
 vt( scavenge )
 vt( scheme )
 vt( scintillate )
 vt( scowl )
 vt( scram )
 vt( screech )
 vt( scrimp )
 vt( scrounge )
 vt( scuffle )
 vt( secede )
 vt( seesaw )
 vt( seethe )
 vt( sermonize )
 vt( shillyshally )
 vt( shimmer )
 vt( shit )
 vt( shiver )
 vt( shrimp )
 vt( shudder )
 vt( side )
 vt( sidle )
 vt( simmer )
 vt( simper )
 vt( sin )
 vt( sizzle )
 vt( skate )
 vt( skedaddle )
 vt( skimp )
 vt( skirmish )
 vt( skulk )
 vt( skylark )
 vt( skyrocket )
 vt( slacken )
 vt( slaver )
 vt( sleet )
 vt( slither )
 vt( slobber )
 vt( slog )
 vt( slouch )
 vt( slum )
 vt( slumber )
 vt( smart )
 vt( smile )
 vt( smirk )
 vt( smoulder )
 vt( snake )
 vt( sneer )
 vt( sneeze )
 vt( snicker )
 vt( sniffle )
 vt( snigger )
 vt( snipe )
 vt( snitch )
 vt( snivel )
 vt( snoop )
 vt( snooze )
 vt( snore )
 vt( snow )
 vt( snowball )
 vt( snuffle )
 vt( sob )
 vt( sojourn )
 vt( soliloquize )
 vt( somersault )
 vt( sour )
 vt( spar )
 vt( sparkle )
 vt( specialize )
 vt( speechify )
 vt( spiral )
 vt( splurge )
 vt( splutter )
 vt( sprawl )
 vt( sprint )
 vt( sputter )
 vt( squabble )
 vt( squall )
 vt( squawk )
 vt( squeak )
 vt( squeal )
 vt( squint )
 vt( squirm )
 vt( stagnate )
 vt( stem )
 vt( straggle )
 vt( stray )
 vt( strive )
 vt( struggle )
 vt( stutter )
 vt( sub )
 vt( subscribe )
 vt( subside )
 vt( subsist )
 vt( succumb )
 vt( sulk )
 vt( summer )
 vt( sunbathe )
 vt( sup )
 vt( supervene )
 vt( surface )
 vt( surge )
 vt( swagger )
 vt( swarm )
 vt( swelter )
 vt( swerve )
 vt( swirl )
 vt( swoon )
 vt( sympathize )
 vt( tamper )
 vt( tarry )
 vt( tattle )
 vt( taxi )
 vt( teem )
 vt( teeter )
 vt( teethe )
 vt( temporize )
 vt( thrive )
 vt( throb )
 vt( thud )
 vt( tingle )
 vt( tinker )
 vt( tinkle )
 vt( tiptoe )
 vt( titter )
 vt( tittle-tattle )
 vt( toady )
 vt( toboggan )
 vt( toil )
 vt( toll )
 vt( tolled )
 vt( ton )
 vt( tootle )
 vt( totter )
 vt( touch-type )
 vt( tower )
 vt( toy )
 vt( traipse )
 vt( transpire )
 vt( travel )
 vt( trek )
 vt( tremble )
 vt( trespass )
 vt( trifle )
 vt( triumph )
 vt( trundle )
 vt( tunnel )
 vt( tussle )
 vt( tweet )
 vt( twinkle )
 vt( twitch )
 vt( twitter )
 vt( ululate )
 vt( underact )
 vt( undulate )

 vt( urinate )
 vt( vacation )
 vt( vacillate )
 vt( vamoose )
 vt( vamp )
 vt( vanish )
 vt( vault )

 vt( vegetate )
 vt( verge )
 vt( vie )
 vt( vouch )
 vt( voyage )
 vt( waddle )
 vt( waffle )
 vt( wallow )

 vt( waltz )
 vt( wander )
 vt( wane )
 vt( wank )
 vt( warble )
 vt( waver )
 vt( weep )
 vt( welsh )

 vt( welter )
 vt( wheeze )
 vt( whimper )
 vt( whinny )
 vt( whir )
 vt( whirr )
 vt( wilt )
 vt( wince )
 vt( wink )
 vt( wiretap )
 vt( wisecrack )
 vt( wither )
 vt( wobble )
 vt( womanize )
 vt( wrangle )
 vt( wriggle )
 vt( writhe )
 vt( yacht )
 vt( yammer )
 vt( yap )
 vt( yawn )
 vt( yearn )
 vt( yelp )
 vt( yen )
 vt( zigzag )

 vt( abandon )
 vt( abase )
 vt( abbreviate )
 vt( abduct )
 vt( abet )
 vt( abhor )
 vt( abolish )

 vt( abridge )
 vt( abrogate )
 vt( absorb )
 vt( abstract )
 vt( abuse )
 vt( abut )
 vt( accent )

 vt( accentuate )
 vt( access )
 vt( acclaim )
 vt( accommodate )
 vt( accompany )
 vt( accomplish )

 vt( accost )
 vt( accredit )
 vt( accustom )
 vt( achieve )
 vt( acquaint )
 vt( acquire )

 vt( activate )
 vt( addict )
 vt( addle )
 vt( address )
 vt( adjudge )
 vt( administer )
 vt( admire )

 vt( admonish )
 vt( adopt )
 vt( adore )
 vt( adorn )
 vt( adulterate )
 vt( adumbrate )
 vt( aerate )

 vt( affect ) // Vehicle steering was adversely affected.
 vt( affix )
 vt( afflict )
 vt( aggrandize )
 vt( aggravate )
 vt( air )
 vt( alienate )

 vt( allay )
 vt( alleviate )
 vt( allocate )
 vt( allot )
 vt( amass )
 vt( ambush )
 vt( ameliorate )

 vt( amend )
 vt( amortize )
 vt( amplify )
 vt( amputate )
 vt( anaesthetize )
 vt( analyse )

 vt( analyze )
 vt( anathematize )
 vt( anesthetize )
 vt( anger )
 vt( anglicize )
 vt( animate )

 vt( annex )
 vt( annihilate )
 vt( annoint )
 vt( annotate )
 vt( annul )
 vt( anoint )

 vt( antagonize )
 vt( antedate )
 vt( ape )
 vt( appal )
 vt( appease )
 vt( append )
 vt( apportion )

 vt( appraise ) // He appraised the situation carefully before acting.
 vt( apprehend )
 vt( apprentice )
 vt( apprise )
 vt( appropriate )
 vt( arm )

 vt( arouse )
 vt( arraign )
 vt( array )
 vt( arrest )
 vt( arrogate )
 vt( ascribe )
 vt( asphalt )

 vt( asphyxiate )
 vt( aspirate )
 vt( assail )
 vt( assassinate )
 vt( assault )
 vt( assay )

 vt( assess )
 vt( assuage )
 vt( atomize )
 vt( attach )
 vt( attack )
 vt( attain )
 vt( attenuate )

 vt( attire )
 vt( attract )
 vt( attribute )
 vt( attune )
 vt( audit )
 vt( augment )

 vt( authenticate )
 vt( autograph )
 vt( automate )
 vt( avenge )
 vt( aver )
 vt( avert )
 vt( await )

 vt( awe )
 vt( ax )
 vt( axe )
 vt( backdate )
 vt( badger )
 vt( baffle )
 vt( bait )
 vt( bake )
 vt( balance )

 vt( bale )
 vt( bamboozle )
 vt( ban )
 vt( bandage )
 vt( banish )
 vt( bankrupt )
 vt( baptize )

 vt( barbarize )
 vt( barbecue )
 vt( bare )
 vt( barrel )
 vt( barricade )
 vt( base )
 vt( bash )

 vt( baste )
 vt( batter )
 vt( battle )
 vt( beatify )
 vt( beautify )
 vt( bedevil )
 vt( befall )

 vt( befit )
 vt( befoul )
 vt( befriend )
 vt( beget )
 vt( beggar )
 vt( beguile )
 vt( behead )

 vt( behold )
 vt( belabour )
 vt( belie )
 vt( belittle )
 vt( belt )
 vt( bemoan )
 vt( bequeath )

 vt( berate )
 vt( bereave )
 vt( beseech )
 vt( besiege )
 vt( besmirch )
 vt( bespeak )
 vt( bestir )

 vt( bestow )
 vt( bestrew )
 vt( bestride )
 vt( betoken )
 vt( betray )
 vt( bevel )
 vt( bewail )

 vt( bewilder )
 vt( bewitch )
 vt( bias )
 vt( bide )
 vt( biff )
 vt( bilk )
 vt( bill )
 vt( billet )

 vt( birch )
 vt( bisect )
 vt( blackball )
 vt( blacklist )
 vt( blackmail )
 vt( blame )
 vt( blanket )

 vt( blast )
 vt( blazon )
 vt( blemish )
 vt( bless )
 vt( blight )
 vt( blind )
 vt( blindfold )

 vt( blitz )
 vt( blockade )
 vt( blow-dry )
 vt( bludgeon )
 vt( blue-pencil )
 vt( blunt )

 vt( bolster )
 vt( bomb )
 vt( bombard )
 vt( boost ) // The singer had to be boosted onto the stage by a special contraption.
 vt( boss )
 vt( botch )
 vt( boycott )
 vt( brace )

 vt( bracket )
 vt( braid )
 vt( brainwash )
 vt( braise )
 vt( brand )
 vt( brandish )
 vt( brave )

 vt( breach )
 vt( bribe )
 vt( brick )
 vt( bridge )
 vt( brief )
 vt( broach )
 vt( brocade )
 vt( bronze )

 vt( brook )
 vt( browbeat )
 vt( brutalize )
 vt( budget )
 vt( buff )
 vt( bug )
 vt( bulldoze )
 vt( bung )

 vt( bungle )
 vt( buoy )
 vt( burden )
 vt( burlesque )
 vt( bury )
 vt( bus )
 vt( busy )
 vt( butcher )

 vt( buttonhole )
 vt( buttress )
 vt( by-pass )
 vt( bypass )
 vt( cajole )
 vt( calibrate )

 vt( camouflage )
 vt( cane )
 vt( cannibalize )
 vt( canonize )
 vt( cap )
 vt( captivate )

 vt( capture )
 vt( carbonize )
 vt( card )
 vt( caress )
 vt( caricature )
 vt( carpet )
 vt( case )

 vt( castigate )
 vt( castrate )
 vt( catalogue )
 vt( catapult )
 vt( categorize )
 vt( cede )

 vt( cement )
 vt( censor )
 vt( censure )
 vt( centralize )
 vt( chagrin )
 vt( chain )
 vt( chair )

 vt( champion )
 vt( channel )
 vt( chaperon )
 vt( charm )
 vt( chart )
 vt( charter )
 vt( chasten )

 vt( chastise )
 vt( cheapen )
 vt( checkmate )
 vt( cherish )
 vt( chide )
 vt( chisel )

 vt( chlorinate )
 vt( christen )
 vt( chronicle )
 vt( circularize )
 vt( circumcise )

 vt( circumnavigate )
 vt( circumscribe )
 vt( circumvent )
 vt( cite )
 vt( civilize )
 vt( clamp )

 vt( classify )
 vt( claw )
 vt( cleanse )
 vt( clench )
 vt( clip )
 vt( cloak )
 vt( clobber )

 vt( cloister )
 vt( clone )
 vt( closet )
 vt( clothe )
 vt( club )
 vt( co-author )
 vt( co-opt )

 vt( co-produce )
 vt( coat )
 vt( cobble )
 vt( cock )
 vt( coddle )
 vt( code )
 vt( codify )
 vt( coerce )

 vt( coin )
 vt( cold-shoulder )
 vt( collar )
 vt( collate )
 vt( collect )
 vt( collectivize )

 vt( colonize )
 vt( color )
 vt( colour )
 vt( combat )
 vt( comfort )
 vt( commandeer )

 vt( commemorate )
 vt( commend )
 vt( commercialize )
 vt( compact )
 vt( compartmentalize )

 vt( compile )
 vt( complement )
 vt( complete )
 vt( complicate )
 vt( compliment )
 vt( compost )

 vt( compound )
 vt( comprehend )
 vt( compress )
 vt( comprise )
 vt( computerize )
 vt( con )

 vt( conceal )
 vt( concern )
 vt( conciliate )
 vt( concoct )
 vt( condition ) // I condition my hair after washing it.
 vt( condone )

 vt( configure )
 vt( confine )
 vt( confiscate )
 vt( confound )
 vt( confront )
 vt( confuse )

 vt( confute )
 vt( congratulate )
 vt( conk )
 vt( connote )
 vt( conquer )
 vt( conscript )

 vt( consecrate )
 vt( conserve )
 vt( consign )
 vt( console )
 vt( constitute )
 vt( constrain )

 vt( constrict )
 vt( construct )
 vt( construe )
 vt( consume )
 vt( consummate )
 vt( contact )

 vt( contain )
 vt( contaminate )
 vt( content )
 vt( contort )
 vt( contour )
 vt( contradict )

 vt( contravene )
 vt( contrive )
 vt( control )
 vt( convey )
 vt( convoke )

 vt( convoy )
 vt( convulse )
 vt( coop )
 vt( coordinate )
 vt( copy )
 vt( copyright )
 vt( cord )

 vt( cordon )
 vt( core )
 vt( cork )
 vt( corner )
 vt( corral )
 vt( correct )
 vt( corroborate )

 vt( countenance )
 vt( counteract )
 vt( counterbalance )
 vt( counterfeit )

 vt( countermand )
 vt( countersign )
 vt( couple )
 vt( court )
 vt( court-martial )
 vt( covet )

 vt( cradle )
 vt( cramp )
 vt( crane )
 vt( crayon )
 vt( cream )
 vt( create )
 vt( credit )
 vt( cremate )

 vt( crimp )
 vt( cripple )
 vt( criticize )
 vt( cross-examine )
 vt( cross-fertilize )

 vt( cross-index )
 vt( cross-question )
 vt( crossbreed )
 vt( crown )
 vt( crucify )
 vt( crush )

 vt( cube )
 vt( cudgel )
 vt( cuff )
 vt( cull )
 vt( cultivate )
 vt( cup )
 vt( curb )
 vt( cure )
 vt( curry )

 vt( curtail )
 vt( cushion )
 vt( damage )
 vt( damn )
 vt( dampen )
 vt( dandle )
 vt( daub )
 vt( daunt )

 vt( daze )
 vt( dazzle )
 vt( de-escalate )
 vt( de-ice )
 vt( deaden )
 vt( deafen )
 vt( debar )

 vt( debase )
 vt( debauch )
 vt( debilitate )
 vt( debit )
 vt( debrief )
 vt( debug )
 vt( debunk )

 vt( decant )
 vt( decapitate )
 vt( decarbonize )
 vt( deceive )
 vt( decentralize )

 vt( decertify )
 vt( decimalize )
 vt( decimate )
 vt( decipher )
 vt( deck )
 vt( declaim )

 vt( declassify )
 vt( decode )
 vt( decolonize )
 vt( decompress )
 vt( decontaminate )

 vt( decorate )
 vt( decry )
 vt( dedicate )
 vt( deduct )
 vt( deep-freeze )
 vt( deface )
 vt( defame )

 vt( defeat )
 vt( defend )
 vt( defer )
 vt( defile )
 vt( define )
 vt( deflate )
 vt( deflower )

 vt( defoliate )
 vt( deforest )
 vt( deform )
 vt( defraud )
 vt( defray )
 vt( defrock )
 vt( defrost )

 vt( defuse )
 vt( defy )
 vt( degrade )
 vt( dehumanize )
 vt( dehydrate )
 vt( deify )
 vt( delegate )

 vt( delete )
 vt( delimit )
 vt( delineate )
 vt( delude )
 vt( deluge )
 vt( demagnetize )

 vt( demarcate )
 vt( demean )
 vt( demilitarize )
 vt( demist )
 vt( demobilize )
 vt( demolish )

 vt( demoralize )
 vt( demote )
 vt( denationalize )
 vt( denigrate )
 vt( denominate )

 vt( denote )
 vt( denounce )
 vt( dent )
 vt( denude )
 vt( deodorize )
 vt( deplete )
 vt( deplore )

 vt( deploy )
 vt( depopulate )
 vt( deport )
 vt( depose )
 vt( deposit )
 vt( deprecate )

 vt( deprogram )
 vt( derange )
 vt( deride )
 vt( desalinate )
 vt( desalinize )
 vt( desecrate )

 vt( desegregate )
 vt( desensitize )
 vt( desert )
 vt( desiccate )
 vt( designate )

 vt( despatch )
 vt( despise )
 vt( despoil )
 vt( destroy )
 vt( detach )
 vt( detain )
 vt( detect )

 vt( deter )
 vt( detest )
 vt( dethrone )
 vt( devaluate )
 vt( devalue )
 vt( devastate )
 vt( devise )

 vt( devote )
 vt( devour )
 vt( diagnose )
 vt( dice )
 vt( diddle )
 vt( diffract )
 vt( dignify )

 vt( dilute )
 vt( direct )
 vt( disable )
 vt( disallow )
 vt( disappoint )
 vt( disarrange )

 vt( disassociate )
 vt( disavow )
 vt( disburse )
 vt( discard )
 vt( discipline )
 vt( disclaim )

 vt( discomfit )
 vt( disconcert )
 vt( disconnect )
 vt( discontent )
 vt( discount )

 vt( discourage )
 vt( discredit )
 vt( disdain )
 vt( disembarrass )
 vt( disembowel )

 vt( disenchant )
 vt( disenfranchise )
 vt( disestablish )
 vt( disfavour )
 vt( disfigure )

 vt( disgorge )
 vt( disgrace )
 vt( disguise ) // We disguised our faces before robbing the bank.
 vt( dishearten )
 vt( dishonour )

 vt( disillusion )
 vt( disinfect )
 vt( disinherit )
 vt( disinter )
 vt( dislocate )

 vt( dislodge )
 vt( dismantle )
 vt( dismember )
 vt( dismiss )
 vt( disobey )
 vt( disorient )

 vt( disorientate )
 vt( disown )
 vt( disparage )
 vt( dispatch )
 vt( dispel )
 vt( displace )

 vt( display )
 vt( displease )
 vt( dispossess )
 vt( disprove )
 vt( disqualify )
 vt( disregard )

 vt( disrupt )
 vt( dissect )
 vt( disseminate )
 vt( dissociate )
 vt( dissuade )
 vt( distance )

 vt( distil )
 vt( distort )
 vt( distract )
 vt( distribute )
 vt( distrust )
 vt( disturb )

 vt( ditch )
 vt( divert )
 vt( divest )
 vt( divorce )
 vt( divulge )
 vt( dizzy )
 vt( doctor )

 vt( document )
 vt( doff )
 vt( domesticate )
 vt( dominate )
 vt( don )
 vt( donate )
 vt( doom )

 vt( dope )
 vt( dot )
 vt( double-check )
 vt( double-cross )
 vt( douse )
 vt( down )
 vt( downgrade )

 vt( download )
 vt( dragoon )
 vt( dramatize )
 vt( drape )
 vt( drench )
 vt( drip-dry )
 vt( drub )

 vt( drug )
 vt( dry-clean )
 vt( dumbfound )
 vt( dunk )
 vt( dupe )
 vt( duplicate )
 vt( dust )

 vt( dwarf )
 vt( dye )
 vt( dynamite )
 vt( earmark )
 vt( earn )
 vt( eclipse )
 vt( edify )
 vt( edit )

 vt( efface )
 vt( effect )
 vt( elbow )
 vt( electrify )
 vt( electrocute )
 vt( elevate )
 vt( elicit )

 vt( elide )
 vt( eliminate )
 vt( elucidate )
 vt( elude )
 vt( emancipate )
 vt( emasculate )

 vt( embalm )
 vt( embargo )
 vt( embed )
 vt( embellish )
 vt( embezzle )
 vt( embitter )

 vt( emblazon )
 vt( embody )
 vt( embolden )
 vt( emboss )
 vt( embrace )
 vt( embroil )
 vt( emend )

 vt( emit )
 vt( empanel )
 vt( empower )
 vt( emulate )
 vt( emulsify )
 vt( enact )
 vt( enamel )

 vt( encase )
 vt( enchant )
 vt( encircle )
 vt( enclose )
 vt( encode )
 vt( encompass )

 vt( encounter )
 vt( encrypt )
 vt( encumber )
 vt( endanger )
 vt( endear )
 vt( endorse )
 vt( endow )

 vt( enervate )
 vt( enfold )
 vt( enforce )
 vt( enfranchise )
 vt( engender )
 vt( engineer )

 vt( engrave )
 vt( engross )
 vt( engulf )
 vt( enhance )
 vt( enjoin )
 vt( enlarge )
 vt( enlighten )

 vt( enliven )
 vt( enmesh )
 vt( ennoble )
 vt( enrage )
 vt( enrich )
 vt( ensconce )
 vt( enshrine )

 vt( enshroud )
 vt( enslave )
 vt( ensnare )
 vt( entangle )
 vt( enthral )
 vt( enthrall )

 vt( enthrone )
 vt( entomb )
 vt( entrain )
 vt( entrance )
 vt( entrap )
 vt( entreat )
 vt( entrust )

 vt( entwine )
 vt( enumerate )
 vt( envelop )
 vt( envisage )
 vt( envy )
 vt( epitomize )
 vt( equal )

 vt( equalize )
 vt( equate )
 vt( equip )
 vt( eradicate )
 vt( erase )
 vt( erect )
 vt( eschew )

 vt( escort )
 vt( espouse )
 vt( espy )
 vt( establish )
 vt( esteem )
 vt( eulogize )
 vt( evade )

 vt( evaluate )
 vt( evict )
 vt( evince )
 vt( eviscerate )
 vt( evoke )
 vt( exacerbate )
 vt( exalt )

 vt( examine )
 vt( exasperate )
 vt( excavate )
 vt( exceed )
 vt( exchange )
 vt( excise )

 vt( exclude )
 vt( excommunicate )
 vt( excoriate )
 vt( excrete )
 vt( exculpate )
 vt( excuse )

 vt( execute )
 vt( exemplify )
 vt( exempt )
 vt( exert )
 vt( exhaust )
 vt( exhibit )

 vt( exhilarate )
 vt( exhume )
 vt( exile )
 vt( exorcize )
 vt( expedite )
 vt( expel )
 vt( expend )

 vt( experience )
 vt( expiate )
 vt( explicate )
 vt( exploit )
 vt( export )
 vt( expose )

 vt( express )
 vt( expropriate )
 vt( expunge )
 vt( expurgate )
 vt( extenuate )

 vt( exterminate )
 vt( externalize )
 vt( extinguish )
 vt( extirpate )
 vt( extol )
 vt( extort )

 vt( extract )
 vt( extradite )
 vt( extricate )
 vt( exude )
 vt( eye )
 vt( fabricate )

 vt( facilitate )
 vt( fag )
 vt( fake )
 vt( falsify )
 vt( familiarize )
 vt( fancy )
 vt( fascinate )

 vt( fashion )
 vt( fate )
 vt( fathom )
 vt( fatigue )
 vt( fault )
 vt( favour )
 vt( feather )

 vt( feature )
 vt( feed )
 vt( feign )
 vt( fence )
 vt( ferret )
 vt( fertilize )
 vt( festoon )

 vt( feteH )
 vt( fetter )
 vt( fillet )
 vt( finalize )
 vt( finance )
 vt( fine-tune )
 vt( finger )

 vt( flagellate )
 vt( flank )
 vt( flatter )
 vt( flaunt )
 vt( flavour )
 vt( flay )
 vt( fleece )

 vt( flex )
 vt( flick )
 vt( flog )
 vt( floodlight )
 vt( floor )
 vt( flout )
 vt( fluff )
 vt( flummox )

 vt( fluoridate )
 vt( flurry )
 vt( fluster )
 vt( foil )
 vt( foist )
 vt( foment )
 vt( fondle )

 vt( fool )
 vt( force-feed )
 vt( ford )
 vt( forecast )
 vt( forego )
 vt( foreordain )

 vt( foreshadow )
 vt( foreshorten )
 vt( forestall )
 vt( foreswear )
 vt( foretell )

 vt( forfeit )
 vt( forge )
 vt( forgo )
 vt( formalize )
 vt( formulate )
 vt( forsake )
 vt( forswear )

 vt( fortify )
 vt( forward )
 vt( foster )
 vt( frame )
 vt( frank )
 vt( free )
 vt( frequent )

 vt( fresco )
 vt( fricassee )
 vt( frighten )
 vt( frisk )
 vt( fritter )
 vt( frogmarch )

 vt( frustrate )
 vt( fry )
 vt( fulfil )
 vt( fulfill )
 vt( fumigate )
 vt( fund )
 vt( funnel )

 vt( furbish )
 vt( furnish )
 vt( furrow )
 vt( further )
 vt( gage )
 vt( gainsay )
 vt( gall )

 vt( galvanize )
 vt( gaol )
 vt( garb )
 vt( garble )
 vt( garner )
 vt( garnish )
 vt( garrison )

 vt( gash )
 vt( gatecrash )
 vt( gauge )
 vt( generate )
 vt( gerrymander )
 vt( gild )
 vt( gin )

 vt( gird )
 vt( gladden )
 vt( glamorize )
 vt( glean )
 vt( glimpse )
 vt( glorify )
 vt( glut )
 vt( goad )

 vt( gore )
 vt( gorge )
 vt( grab )
 vt( grace )
 vt( grade )
 vt( graft )
 vt( gratify )
 vt( gravel )

 vt( grease )
 vt( greet )
 vt( grill )
 vt( grip )
 vt( grit )
 vt( groin )
 vt( groom )
 vt( gross )

 vt( grudge )
 vt( guard )
 vt( guide )
 vt( guillotine )
 vt( gum )
 vt( gun )
 vt( gut )
 vt( guzzle )
 vt( gyp )

 vt( hallow )
 vt( halt )
 vt( halve )
 vt( hamper )
 vt( hamstring )
 vt( handcuff )
 vt( handicap )

 vt( handle )
 vt( harangue )
 vt( harass )
 vt( harbor )
 vt( harbour )
 vt( harm )
 vt( harness )

 vt( harpoon )
 vt( harrow )
 vt( harry )
 vt( harvest )
 vt( hassle )
 vt( haunt )
 vt( hawk )
 vt( hazard )

 vt( haze )
 vt( heap )
 vt( hearten )
 vt( heed )
 vt( herald )
 vt( highjack )
 vt( highlight )

 vt( hijack )
 vt( hinder )
 vt( hoax )
 vt( hobble )
 vt( hock )
 vt( hog )
 vt( hollow )
 vt( homogenize )

 vt( hone )
 vt( honor ) // An occasion arranged to honor the president.
 vt( honour )
 vt( hood )
 vt( hoodwink )
 vt( horrify )
 vt( horsewhip )
 vt( hose )

 vt( hospitalize )
 vt( host )
 vt( hotfoot )
 vt( hound )
 vt( house )
 vt( hull )
 vt( humble )

 vt( humbug )
 vt( humiliate )
 vt( humour )
 vt( hump )
 vt( hunch )
 vt( hurl )
 vt( husk )
 vt( hyphenate )

 vt( hypnotize )
 vt( idealize )
 vt( identify )
 vt( idolize )
 vt( ignore )
 vt( ill-treat )

 vt( illuminate )
 vt( illumine )
 vt( illustrate )
 vt( image )
 vt( imbibe )
 vt( imbue )

 vt( imitate )
 vt( immerse )
 vt( immobilize )
 vt( immolate )
 vt( immortalize )
 vt( immunize )

 vt( impact )
 vt( impair )
 vt( impale )
 vt( impanel )
 vt( impart )
 vt( impeach )
 vt( impede )

 vt( imperil )
 vt( impersonate )
 vt( implant )
 vt( implement )
 vt( implicate )
 vt( import )

 vt( impose )
 vt( impound )
 vt( impoverish )
 vt( impregnate )
 vt( impress )
 vt( imprint )

 vt( imprison ) // He was then imprisoned.
 vt( impugn )
 vt( impute )
 vt( inactivate )
 vt( inaugurate )
 vt( incapacitate )

 vt( incarcerate )
 vt( incense )
 vt( incinerate )
 vt( include )
 vt( inconvenience )

 vt( incriminate )
 vt( inculcate )
 vt( incur )
 vt( indemnify )
 vt( indenture )
 vt( index )

 vt( indict )
 vt( individuate )
 vt( indoctrinate )
 vt( induct ) // He was inducted in 1979.
 vt( infatuate )
 vt( infect )

 vt( infest )
 vt( infiltrate )
 vt( inflame )
 vt( inflate )
 vt( inflect )
 vt( inflict )

 vt( influence )
 vt( infuriate )
 vt( infuse )
 vt( ingest )
 vt( ingratiate )
 vt( inhabit )

 vt( inherit )
 vt( inhibit )
 vt( initial )
 vt( initiate )
 vt( inject )
 vt( injure )
 vt( ink )

 vt( inoculate )
 vt( inscribe )
 vt( inseminate )
 vt( insert )
 vt( inspect )
 vt( install )

 vt( instigate )
 vt( instil )
 vt( instill )
 vt( institute )
 vt( institutionalize )

 vt( insulate )
 vt( insult )
 vt( insure )
 vt( integrate )
 vt( inter )
 vt( intercept )

 vt( interchange )
 vt( interdict )
 vt( interest )
 vt( interject )
 vt( interleave )

 vt( internalize )
 vt( internationalize )
 vt( interpolate )
 vt( interrogate )

 vt( intersperse )
 vt( interweave )
 vt( intimidate )
 vt( intone )
 vt( intoxicate )

 vt( introduce )
 vt( intuit )
 vt( inundate )
 vt( invade )
 vt( invalidate )
 vt( inveigle )

 vt( invent )
 vt( invert )
 vt( invigorate )
 vt( invoke )
 vt( irk )
 vt( irradiate )
 vt( irrigate )

 vt( isolate )
 vt( italicize )
 vt( itemize )
 vt( iterate )
 vt( jail )
 vt( jar )
 vt( jeopardize )

 vt( jettison )
 vt( jilt )
 vt( jolly )
 vt( jug )
 vt( juxtapose )
 vt( ken )
 vt( kidnap )
 vt( kiss )

 vt( knead )
 vt( knife )
 vt( knight ) // Tom Davis is knighted.
 vt( label )
 vt( lace )
 vt( lacerate )
 vt( lack )
 vt( lacquer )

 vt( lambaste )
 vt( laminate )
 vt( lampoon ) // Reporters lampooned them as the Cleveland Crybabies.
 vt( lance )
 vt( landscape )
 vt( lasso )
 vt( laud )

 vt( launder )
 vt( lavish )
 vt( leach )
 vt( leapfrog )
 vt( lease )
 vt( leaven )
 vt( legalize )

 vt( legitimatize )
 vt( lever )
 vt( leverage )
 vt( levy )
 vt( libel )
 vt( liberalize )

 vt( liberate )
 vt( licence )
 vt( liken )
 vt( limit )
 vt( lionize )
 vt( liquidize )
 vt( list )
 vt( like )

 vt( loan )
 vt( loathe )
 vt( lob )
 vt( localize )
 vt( loft )
 vt( loot )
 vt( lubricate )
 vt( lug )

 vt( lull )
 vt( lump )
 vt( lure )
 vt( lynch )
 vt( madden )
 vt( magnetize )
 vt( magnify )
 vt( maim )

 vt( malign )
 vt( maltreat )
 vt( man )
 vt( manacle )
 vt( mandate )
 vt( mangle )
 vt( manhandle )

 vt( manicure )
 vt( manifest )
 vt( manipulate )
 vt( manufacture )
 vt( mar )
 vt( market )

 vt( maroon )
 vt( marshal )
 vt( martyr )
 vt( mash )
 vt( mask )
 vt( mass-produce )
 vt( massage )

 vt( master )
 vt( mastermind )
 vt( masticate )
 vt( maul )
 vt( maximize )
 vt( measure )

 vt( mechanize )
 vt( medicate )
 vt( memorialize )
 vt( memorize )
 vt( menace )
 vt( merit )

 vt( mesmerize )
 vt( microfilm )
 vt( milk )
 vt( mimeograph )
 vt( mimic ) // Declaration syntax mimics usage context.
 vt( mince )

 vt( miniaturize )
 vt( minimize )
 vt( mint )
 vt( mire )
 vt( mirror )
 vt( misapply )

 vt( misapprehend )
 vt( misappropriate )
 vt( miscast )
 vt( misconceive )
 vt( misconstrue )

 vt( misdate )
 vt( misdirect )
 vt( misgovern )
 vt( misguide )
 vt( mishandle )
 vt( mishear )

 vt( misinform )
 vt( misinterpret )
 vt( mislay )
 vt( mislead )
 vt( mismanage )
 vt( misname )

 vt( misplace )
 vt( mispronounce )
 vt( misquote )
 vt( misrepresent )
 vt( misspell )

 vt( misspend )
 vt( misstate )
 vt( mistake )
 vt( mistranslate )
 vt( mistreat )
 vt( mistrust )

 vt( misuse )
 vt( mitigate )
 vt( mob )
 vt( mock )
 vt( model )
 vt( modify )
 vt( modulate )
 vt( mold )

 vt( molest )
 vt( mollify )
 vt( mollycoddle )
 vt( monitor )
 vt( monopolize )
 vt( moor )

 vt( mortar )
 vt( mortgage )
 vt( mortify )
 vt( mothproof )
 vt( motorize )
 vt( muddy )
 vt( muff )

 vt( muffle )
 vt( mug )
 vt( mulch )
 vt( murder )
 vt( muster )
 vt( mute )
 vt( mutilate )
 vt( muzzle )

 vt( mystify )
 vt( nab )
 vt( nag )
 vt( narrate )
 vt( nationalize )
 vt( naturalize )
 vt( needle )

 vt( negate )
 vt( net )
 vt( nettle )
 vt( neuter )
 vt( neutralize )
 vt( nick )
 vt( nickname )

 vt( normalize )
 vt( nourish )
 vt( nudge )
 vt( nullify )
 vt( numb )
 vt( number )
 vt( nurse )

 vt( nurture )
 vt( obfuscate )
 vt( obligate )
 vt( obliterate )
 vt( obscure )
 vt( obstruct )

 vt( obtain )
 vt( obviate )
 vt( occasion )
 vt( occupy )
 vt( offend )
 vt( oil )
 vt( okay )
 vt( omen )

 vt( omit )
 vt( oppress )
 vt( orchestrate )
 vt( ordain )
 vt( organize )
 vt( orient )

 vt( orientate )
 vt( ornament )
 vt( ostracize )
 vt( oust )
 vt( outbalance )
 vt( outbid )

 vt( outclass )
 vt( outdistance )
 vt( outdo )
 vt( outfight )
 vt( outfit )
 vt( outflank )

 vt( outfox )
 vt( outgrow )
 vt( outlast )
 vt( outlaw )
 vt( outline )
 vt( outlive )

 vt( outmanoeuvre )
 vt( outnumber )
 vt( outplay )
 vt( outrage )
 vt( outrank )
 vt( outride )

 vt( outrun )
 vt( outshine )
 vt( outsmart )
 vt( outstay )
 vt( outvote )
 vt( outweigh )
 vt( outwit )

 vt( overawe )
 vt( overbear )
 vt( overburden )
 vt( overcook )
 vt( overcrowd )
 vt( overdo )

 vt( overemphasize )
 vt( overestimate )
 vt( overexert )
 vt( overexpose )
 vt( overhaul )

 vt( overhear )
 vt( overleap )
 vt( overload )
 vt( overlook )
 vt( overpay )
 vt( overplay )

 vt( overpower )
 vt( overpraise )
 vt( overprint )
 vt( overrate )
 vt( override )
 vt( overrule )

 vt( oversee )
 vt( overshadow )
 vt( overshoot )
 vt( oversimplify )
 vt( overstate )

 vt( overstay )
 vt( overstep )
 vt( overstock )
 vt( overstrain )
 vt( overtake )
 vt( overtax )

 vt( overvalue )
 vt( overwhelm )
 vt( own )
 vt( oxygenate )
 vt( pacify )
 vt( package )
 vt( pad )

 vt( padlock )
 vt( page )
 vt( pain )
 vt( pamper )
 vt( paper )
 vt( parallel )
 vt( paralyse )

 vt( paralyze )
 vt( paraphrase )
 vt( parch )
 vt( pardon )
 vt( pare )
 vt( parody )
 vt( parole )

 vt( parry )
 vt( parse )
 vt( partition )
 vt( partner )
 vt( paste )
 vt( pasteurize )
 vt( pat )

 vt( patent )
 vt( patrol )
 vt( patronize )
 vt( pattern )
 vt( pauperize )
 vt( paw )
 vt( pawn )
 vt( peg )

 vt( pelt )
 vt( penalize )
 vt( pencil )
 vt( pepper )
 vt( perfect )
 vt( perforate )
 vt( perfume )

 vt( perfuse )
 vt( perjure )
 vt( perm )
 vt( permeate )
 vt( permute )
 vt( perpetrate )

 vt( perpetuate )
 vt( perplex )
 vt( persecute )
 vt( personalize )
 vt( personify )
 vt( perturb )

 vt( peruse )
 vt( pervade )
 vt( pervert )
 vt( pester )
 vt( pet )
 vt( photocopy )
 vt( photograph )

 vt( photosensitize )
 vt( photostat )
 vt( phrase )
 vt( pickle )
 vt( picture )
 vt( pierce )

 vt( pigeonhole )
 vt( pilfer )
 vt( pilot )
 vt( pinch )
 vt( pinpoint )
 vt( pip )
 vt( pipe )
 vt( pique )

 vt( pirate )
 vt( pit )
 vt( pitchfork )
 vt( pity )
 vt( placate )
 vt( place )
 vt( plagiarize )

 vt( plague )
 vt( plant )
 vt( plaster )
 vt( please )
 vt( ply )
 vt( pocket )
 vt( poison )
 vt( polarize )

 vt( police )
 vt( polish )
 vt( politicize )
 vt( pollinate )
 vt( pollute )
 vt( ponder )

 vt( pooh-pooh )
 vt( pool )
 vt( popularize )
 vt( populate )
 vt( port )
 vt( portend )
 vt( position )

 vt( possess )
 vt( post )
 vt( postdate )
 vt( postmark )
 vt( postpone )
 vt( powder )
 vt( praise )

 vt( pre-empt )
 vt( prearrange )
 vt( precede )
 vt( precipitate )
 vt( preclude )

 vt( preconceive )
 vt( predestine )
 vt( predetermine )
 vt( predicate )
 vt( predispose )

 vt( preempt )
 vt( preen )
 vt( prefabricate )
 vt( preface )
 vt( prefigure )
 vt( preheat )

 vt( prejudge )
 vt( prejudice )
 vt( premeditate )
 vt( premise )
 vt( preoccupy )
 vt( preordain )

 vt( prepay )
 vt( prerecord )
 vt( presage )
 vt( prescribe )
 vt( present )
 vt( preserve )

 vt( presort )
 vt( pressurize )
 vt( prettify )
 vt( prevent )
 vt( price )
 vt( pride )
 vt( prime )

 vt( print )
 vt( privilege )
 vt( prize )
 vt( probe )
 vt( process )
 vt( procure )
 vt( prod )

 vt( produce )
 vt( proffer )
 vt( profile )
 vt( prognosticate )
 vt( prohibit )
 vt( prolong )

 vt( promote )
 vt( promulgate )
 vt( pronounce )
 vt( proof )
 vt( propel )
 vt( proportion )

 vt( proposition )
 vt( propound )
 vt( proscribe )
 vt( prosecute )
 vt( prostitute )

 vt( prostrate )
 vt( protect )
 vt( prune )
 vt( psychoanalyse )
 vt( psychoanalyze )

 vt( publicize )
 vt( publish )
 vt( pulverize )
 vt( pummel )
 vt( punctuate )
 vt( punish )

 vt( purchase )
 vt( purify )
 vt( purloin )
 vt( purse )
 vt( pursue )
 vt( purvey )
 vt( quaff )

 vt( quantify )
 vt( quarantine )
 vt( quarter )
 vt( quash )
 vt( quell )
 vt( quench )
 vt( query )

 vt( question )
 vt( quick-freeze )
 vt( quilt )
 vt( quote )
 vt( raffle )
 vt( raid )
 vt( railroad )

 vt( ram )
 vt( ramp )
 vt( ransack )
 vt( ransom )
 vt( rape )
 vt( ratify )
 vt( ration )
 vt( rationalize )

 vt( ravage )
 vt( ravish )
 vt( raze )
 vt( re-address )
 vt( re-educate )
 vt( re-establish )

 vt( readmit )
 vt( reap )
 vt( rearrange )
 vt( reassess )
 vt( reauthorize )
 vt( rebuff )

 vt( rebuke )
 vt( rebut )
 vt( recapture )
 vt( recast )
 vt( recess )
 vt( recite )
 vt( reclaim )

 vt( recommit )
 vt( recompense )
 vt( reconcile )
 vt( recondition )
 vt( reconsecrate )

 vt( reconsider )
 vt( reconstruct )
 vt( reconvict )
 vt( recoup )
 vt( recreate )
 vt( rectify )

 vt( recycle )
 vt( redecorate )
 vt( redeem )
 vt( redefine )
 vt( redeploy )
 vt( redesign )

 vt( redevelop )
 vt( rediscover )
 vt( redistribute )
 vt( redo )
 vt( redress )
 vt( reduce )

 vt( reduplicate )
 vt( reestablish )
 vt( refashion )
 vt( refill )
 vt( refinance )
 vt( refine )

 vt( reformulate )
 vt( refract )
 vt( refresh )
 vt( refrigerate )
 vt( refund )
 vt( refurbish )

 vt( refurnish )
 vt( refute )
 vt( regain )
 vt( regale )
 vt( regiment )
 vt( regularize )

 vt( regulate )
 vt( regurgitate )
 vt( rehabilitate )
 vt( rehash )
 vt( rehouse )
 vt( reimburse )

 vt( reinforce )
 vt( reinstate )
 vt( reinsure )
 vt( reintegrate )
 vt( reinterpret )

 vt( reinvent )
 vt( reissue )
 vt( reject )
 vt( rejoin )
 vt( rejuvenate )
 vt( relay )
 vt( release )

 vt( relegate )
 vt( relieve )
 vt( relinquish )
 vt( relish )
 vt( relist )
 vt( relive )
 vt( remand )

 vt( remedy )
 vt( remilitarize )
 vt( remould )
 vt( remove )
 vt( remunerate )

 vt( rend )
 vt( renew )
 vt( renounce )
 vt( renovate )
 vt( reorient )
 vt( reorientate )

 vt( repackage )
 vt( repaint )
 vt( repatriate )
 vt( repeal )
 vt( repel )
 vot( replace )

 vt( replant )
 vt( replay )
 vt( replenish )
 vt( replicate )
 vt( reprehend )
 vt( represent )

 vt( repress )
 vt( reprieve )
 vt( reprimand )
 vt( reprint )
 vt( reproach )
 vt( reproof )

 vt( reprove )
 vt( repudiate )
 vt( repulse )
 vt( repurchase )
 vt( repute )
 vt( requisition )

 vt( reread )
 vt( reroute )
 vt( reschedule )
 vt( rescind )
 vt( rescue )
 vt( research )
 vt( reseat )

 vt( resell )
 vt( resemble )
 vt( resent )
 vt( reserve )
 vt( reset )
 vt( reshape )
 vt( reshuffle )

 vt( resole )
 vt( respect )
 vt( restate )
 vt( restock )
 vt( restore )
 vt( restrain )
 vt( restrict )

 vt( restructure )
 vt( resurrect )
 vt( retain )
 vt( retake )
 vt( retard )
 vt( retell )

 vt( rethink )
 vt( retouch )
 vt( retrace )
 vt( retract )
 vt( retransmit )
 vt( retrieve )

 vt( revalue )
 vt( revamp )
 vt( revere )
 vt( review )
 vt( revile )
 vt( revise )
 vt( revisit )

 vt( revitalize )
 vt( revoke )
 vt( revolutionize )
 vt( reward )
 vt( rewire )
 vt( reword )

 vt( rewrite )
 vt( rib )
 vt( riddle )
 vt( ridicule )
 vt( rifle )
 vt( right )
 vt( rim )
 vt( rival )

 vt( rivet )
 vt( romanticize )
 vt( rope )
 vt( rout )
 vt( route )
 vt( rubber-stamp )
 vt( rubberize )

 vt( rue )
 vt( ruin )
 vt( rumple )
 vt( rusticate )
 vt( sabotage )
 vt( sack )
 vt( sadden )
 vt( saddle )

 vt( safeguard )
 vt( salt )
 vt( salvage )
 vt( sample )
 vt( sanctify )
 vt( sanction )
 vt( sand )

 vt( sandblast )
 vt( sandpaper )
 vt( sandwich )
 vt( sap )
 vt( satiate )
 vt( satirize )

 vt( satisfy )
 vt( saturate )
 vt( sauteH )
 vt( savage )
 vt( savour )
 vt( scald )
 vt( scalp )

 vt( scandalize )
 vt( scant )
 vt( scar )
 vt( scent )
 vt( schedule )
 vt( school )
 vt( scoop )

 vt( scorch )
 vt( scorn )
 vt( scotch )
 vt( scour )
 vt( scrap )
 vt( screen )
 vt( scrunch )

 vt( scrutinize )
 vt( sculpt )
 vt( scuttle )
 vt( sear )
 vt( season )
 vt( seat )
 vt( second )

 vt( secrete )
 vt( secularize )
 vt( secure )
 vt( sedate )
 vt( seduce )
 vt( seed )
 vt( segregate )

 vt( select )
 vt( sensitize )
 vt( sentimentalize )
 vt( sequester )
 vt( serenade )

 vt( serialize )
 vt( service )
 vt( shackle )
 vt( shadow )
 vt( shame )
 vt( shampoo )
 vt( share )

 vt( sharpen )
 vt( shear )
 vt( sheathe )
 vt( shelter )
 vt( shelve )
 vt( shepherd )
 vt( shield )

 vt( shingle )
 vt( shirk )
 vt( shock )
 vt( shoo )
 vt( short-change )
 vt( shortlist )
 vt( shoulder )

 vt( shovel )
 vt( shred )
 vt( shroud )
 vt( shuck )
 vt( shun )
 vt( shunt )
 vt( shutter )
 vt( sick )

 vt( sicken )
 vt( sideline )
 vt( sidestep )
 vt( sidetrack )
 vt( sieve )
 vt( sight )
 vt( signpost )

 vt( silence )
 vt( silhouette )
 vt( simplify )
 vt( simulate )
 vt( siphon )
 vt( sire )
 vt( skewer )

 vt( skin )
 vt( skipper )
 vt( skirt )
 vt( slake )
 vt( slander )
 vt( slap )
 vt( slash )
 vt( slate )

 vt( slaughter )
 vt( slay )
 vt( slice )
 vt( slight )
 vt( sling )
 vt( slot )
 vt( slug )
 vt( slur )

 vt( smelt )
 vt( smite )
 vt( smother )
 vt( snag )
 vt( snare )
 vt( snub )
 vt( sock )
 vt( soft-pedal )

 vt( soil )
 vt( solder )
 vt( solicit )
 vt( solve )
 vt( soothe )
 vt( soundproof )
 vt( soup )
 vt( souse )

 vt( spade )
 vt( span )
 vt( spank )
 vt( spare )
 vt( spay )
 vt( spear )
 vt( spearhead )
 vt( specify )

 vt( spew )
 vt( spike )
 vt( spin-dry )
 vt( spirit )
 vt( spite )
 vt( splice )
 vt( sponsor )

 vt( spoonfeed )
 vt( spot )
 vt( spotlight )
 vt( sprain )
 vt( spray )
 vt( sprinkle )
 vt( spurn )

 vt( squander )
 vt( squelch )
 vt( squire )
 vt( stab )
 vt( staff )
 vt( stage )
 vt( stalemate )

 vt( standardize )
 vt( staple )
 vt( starch )
 vt( startle )
 vt( stash )
 vt( station )
 vt( staunch )

 vt( steal )
 vt( steamroller )
 vt( steel )
 vt( stereotype )
 vt( sterilize )
 vt( stiff )

 vt( stigmatize )
 vt( still )
 vt( stimulate )
 vt( stitch )
 vt( stockade )
 vt( stoke )
 vt( stomach )

 vt( stone )
 vt( store )
 vt( stow )
 vt( straddle )
 vt( strafe )
 vt( straiten )
 vt( strangle )

 vt( strap )
 vt( streamline )
 vt( strew )
 vt( stroke )
 vt( structure )
 vt( stub )
 vt( stucco )

 vt( stud )
 vt( stun )
 vt( stunt )
 vt( style )
 vt( stylize )
 vt( stymie )
 vt( subdue )
 vt( subedit )

 vt( subject )
 vt( subjugate )
 vt( sublimate )
 vt( subordinate )
 vt( subpoena )
 vt( subserve )

 vt( subsidize )
 vt( substantiate )
 vt( subsume )
 vt( subtend )
 vt( subtract )
 vt( subvert )

 vt( succour )
 vt( suckle )
 vt( suffuse )
 vt( suit )
 vt( sully )
 vt( summarize )
 vt( summon )
 vt( sun )

 vt( sunder )
 vt( superimpose )
 vt( supersede )
 vt( supplant )
 vt( supplement )
 vt( supply )

 vt( support ) // 
 vt( suppress )
 vt( surmount )
 vt( surpass )
 vt( surround )
 vt( survey )

 vt( suspend )
 vt( sustain )
 vt( swamp )
 vt( swat )
 vt( swathe )
 vt( sweeten )
 vt( swig )
 vt( swindle )

 vt( swipe )
 vt( symbolize )
 vt( syncopate )
 vt( syndicate )
 vt( synthesize )
 vt( syphon )

 vt( systematize )
 vt( table )
 vt( tabulate )
 vt( tail )
 vt( tailor )
 vt( taint )
 vt( tame )
 vt( tamp )

 vt( tantalize )
 vt( tar )
 vt( target )
 vt( tattoo )
 vt( taunt )
 vt( tax )
 vt( tease )
 vt( telecast )

 vt( telescope )
 vt( televise )
 vt( tender )
 vt( terrace )
 vt( terrify )
 vt( terrorize )
 vt( test )

 vt( test-drive )
 vt( tether )
 vt( thank )
 vt( thatch )
 vt( thirst )
 vt( thread )
 vt( thumb )

 vt( thwart )
 vt( ticket )
 vt( tile )
 vt( till )
 vt( time )
 vt( tint )
 vt( titillate )
 vt( toe )

 vt( tolerate )
 vt( torment )
 vt( torpedo )
 vt( torture )
 vt( tote )
 vt( tour )
 vt( tousle )
 vt( tout )

 vt( tow )
 vt( towel )
 vt( trample )
 vt( tranquilize )
 vt( tranquillize )
 vt( transact )

 vt( transcend )
 vt( transcribe )
 vt( transfix )
 vt( transform )
 vt( transfuse )
 vt( transmit )

 vt( transmute )
 vt( transport )
 vt( transpose )
 vt( transship )
 vt( trap )
 vt( traverse )

 vt( treasure )
 vt( trick )
 vt( trigger )
 vt( trivialize )
 vt( trouble )
 vt( trounce )

 vt( truncate )
 vt( tutor )
 vt( tweak )
 vt( twiddle )
 vt( typecast )
 vt( typify )
 vt( tyrannize )

 vt( unbalance )
 vt( unban )
 vt( unblock )
 vt( unbolt )
 vt( unbuckle )
 vt( unburden )

 vt( unbutton )
 vt( uncork )
 vt( uncouple )
 vt( uncover )
 vt( uncross )
 vt( undercharge )

 vt( underestimate )
 vt( underexpose )
 vt( undergo )
 vt( underlie )
 vt( underline )

 vt( undermine )
 vt( underpay )
 vt( underpin )
 vt( underquote )
 vt( underrate )

 vt( underscore )
 vt( undersell )
 vt( undershoot )
 vt( undersign )
 vt( understate )

 vt( understock )
 vt( understudy )
 vt( undervalue )
 vt( underwrite )
 vt( undo )
 vt( unearth )

 vt( unfetter )
 vt( unfrock )
 vt( unfurl )
 vt( unhand )
 vt( unhinge )
 vt( unhook )
 vt( unlearn )

 vt( unleash )
 vt( unloose )
 vt( unmask )
 vt( unnerve )
 vt( unplug )
 vt( unsaddle )

 vt( unscramble )
 vt( scramble )
 vt( unsettle )
 vt( unsheathe )
 vt( unveil )
 vt( unzip )
 vt( upbraid )

 vt( update )
 vt( upgrade )
 vt( uphold )
 vt( upholster )
 vt( uplift )
 vt( uproot )
 vt( upstage )

 vt( usher )
 vt( usurp )
 vt( utilize )
 vt( utter )
 vt( vacate )
 vt( vaccinate )
 vt( valet )

 vt( validate )
 vt( value )
 vt( vanquish )
 vt( varnish )
 vt( veil )
 vt( vend )
 vt( venerate )

 vt( vent )
 vt( ventilate )
 vt( verbalize )
 vt( vet )
 vt( veto )
 vt( vex )
 vt( victimize )

 vt( videotape )
 vt( vilify )
 vt( vindicate )
 vt( violate )
 vt( visa )
 vt( visualize )

 vt( vitiate )
 vt( vivisect )
 vt( vocalize )
 vt( voice )
 vt( void )
 vt( vouchsafe )
 vt( vulgarize )

 vt( wage )
 vt( waive )
 vt( wall )
 vt( wallop )
 vt( wangle )
 vt( ward )
 vt( warrant )
 vt( waste )

 vt( waterproof )
 vt( waylay )
 vt( wean )
 vt( weather )
 vt( wedge )
 vt( weight )
 vt( welcome )
 vt( wend )
 vt( westernize )
 vt( wet )
 vt( whack )
 vt( wheedle )
 vt( whet )
 vt( whitewash )
 vt( wield )

 vt( wing )
 vt( winnow )
 vt( withhold )
 vt( withstand )
 vt( witness )
 vt( wolf )
 vt( woo )
 vt( word )

 vt( worm )
 vt( wound )
 vt( wreak )
 vt( wreck )
 vt( wrench )
 vt( wrest )
 vt( wrong )
 vt( zap )
 vt( zone )


 vt( see )
 vt( have )
 vt( get )
 vt( freeze )
 vt( wet )
 vt( cancel )
 vt( DISEMBOWEL )
 vt( marvel )
 vt( refuel )
 vt( fuel )
 vt( grovel )
 vt( unravel )
 vt( spell )
 vt( hang )
 vt( wed )
 vt( fit )
 vt( total )
 vt( broadcast )
 vt( level )
 vt( untie )
 vt( tie )
 vt( knit )
 vt( sow )
 vt( spoil )
 vt( bid )
 vt( learn )
 vt( relight )
 vt( do )
 vt( "haven't" )
// vt( "don't" )
 vt( eat )
 vt( awake )
 vt( beat )
 vt( begin )
 vt( bend )
 vt( beset )
 vt( bind )
 vt( bite )
 vt( blow )
 vt( buy )
 vt( break )
 vt( breed )
 vt( bring )
 vt( build )
 vt( rebuild )
 vt( burn )
 vt( cast )
 vt( catch )
 vt( cost )
 vt( cut )
 vt( undercut )
 vt( deal )
 vt( dig )
 vt( drink )
 vt( draw )
 vt( dream )
 vt( drive )
 vt( feel )
 vt( fight )
 vt( flee )
 vt( fly )
 vt( fling )
 vt( forbid )
 vt( forgive )
 vt( forget )
 vt( give )
 vt( grind )
 vt( hear )
 vt( hold )
 vt( hide )
 vt( hit )
 vt( hurt )
 vt( choose )
 vt( keep )
 vt( know )
 vt( lay )
 vt( underlay )
 vt( lead )


 vt( leave )
 vt( lend )
// vt( let )
 vt( light )
 vt( lose )
 vt( make )
 vt( mean )
 vt( meet )
 vt( mow )
 vt( overcome )
 vt( undertake )
 vt( overthrow )
 vt( owe )
 vt( pay )
 vt( repay )
 vt( prove )
 vot( put )
 vt( quit )
 vt( run )
 vt( read )
 vt( rid )
 vt( ride )
 vt( say )
 vt( sing )
 vt( sink )
 vt( saw )
 vt( seek )
 vt( sell )
 vot( send )
 vt( set )
 vt( offset )
 vt( sew )
 vt( shake )
 vt( shave )
 vt( shed )
 vt( shoe )
 vt( shoot )
 vot( show )
 vt( shut )
 vt( slide )
 vt( slit )
 vt( speak )
 vt( spend )
 vt( underspend )
 vt( spill )
 vt( spin )
 vt( split )
 vt( spread )
 vt( stand )
 vt( stick )
 vt( sting )
 vt( strike )
 vt( string )
 vt( swim )
 vt( sweep )
 vot( take )
 vt( teach )
 vt( tell )
 vt( throw )
 vt( thrust )
 vt( understand )
 vt( misunderstand )
 vt( upset )
 vt( wake )
 vt( wear )
 vt( weave )
 vt( win )
 vt( unwind )
 vt( wring )
 vt( write )
 vt( swing )

 vt( change )
 vt( reform )
 vt( form )
 vt( stop )
 vt( stop )
 vt( restart )
 vt( stabilize )
 vt( destabilize )
 vt( destabilize )
 vt( lift )
 vt( trade )


 vt( promise )
 vt( refuse )
 vt( pass )

 vt( addulce )
 vt( ameliorate )
 vt( asphyxiate )
 vt( assign )
 vt( backlog )
 vt( backport )
 vt( badmouth )
 vt( ban )
 vt( bedew )
 vt( behead )
 vt( belt )
 vt( benefit )
 vt( boycott )
 vt( butcher )
 vt( calibrate )
 vt( caricature )
 vt( charter )
 vt( clean )
 vt( clear )
 vt( click )
 vt( coerce )
 vt( commemorate )
 vt( compel )
 vt( contain )
 vt( create )
 vt( "cross-reference" )
 vt( cry )
 vt( debunk )
 vt( decorticate )
 vt( defraud )
 vt( demythologize )
 vt( depopulate )
 vt( detonate )
 vt( dice )
 vt( diffuse )
 vt( diminish )
 vt( disacknowledge )
 vt( disambiguate )
 vt( distribute )
 vt( domesticate )
 vt( drill )
 vt( drug )
 vt( dung )
 vt( electroplate )
 vt( embosom )
 vt( ensorcell )
 vt( envy )
 vt( exacerbate )
 vt( exaggerate )
 vt( excel )
 vt( exoculate )
 vt( exonerate )
 vt( expatriate )
 vt( extrapolate )
 vt( flatten )
 vt( flatter )
 vt( flog )
 vt( floor )
 vt( flourish )
 vt( foist )
 vt( foreshadow )
 vt( fulminate )
 vt( garland )
 vt( garrote )
 vt( garrotte )
 vt( glomp )
 vt( gouge )
 vt( gravel )
 vt( harpoon )
 vt( heist )
 vt( herald )
 vt( hijack )
 vt( hose )
 vt( imbosom )
 vt( impose )
 vt( impress )
 vt( inculcate )
 vt( install )
 vt( insufflate )
 vt( intercept )
 vt( irk )
 vt( irritate )
 vt( japan )
 vt( jit )
 vt( kidnap )
 vt( kipper )
 vt( liftshaft )
 vt( livery )
 vt( lock )
 vt( loop )
 vt( love )
 vt( macarize )
 vt( magnetize )
 vt( malign )
 vt( masticate )
 vt( meliorate )
 vt( microwave )
 vt( midwife )
 vt( miss )
 vt( mosh )
 vt( nab )
 vt( oblige )
 vt( obsess )
 vt( oppress )
 vt( orchestrate )
 vt( orientate )
 vt( outclass )
 vt( outlast )
 vt( outlay )
 vt( outmatch )
 vt( outnumber )
 vt( outrank )
 vt( outstrip )
 vt( oxygenate )
 vt( pacify )
 vt( pant )
 vt( peck )
 vt( peregrinate )
 vt( personate )
 vt( pester )
 vt( piss )
 vt( popularise )
 vt( pose )
 vt( powder )
 vt( prank )
 vt( precurse )
 vt( prejudice )
 vt( prescribe )
 vt( profane )
 vt( prohibit )
 vt( promote )
 vt( propitiate )
 vt( proscribe )
 vt( publish )
 vt( purchase )
 vt( quieten )
 vt( quitclaim )
 vt( quiz )
 vt( rebate )
 vt( recite )
 vt( reference )
 vt( refute )
 vt( regenerate )
 vt( relate )
 vt( replace )
 vt( resolve )
 vt( restore )
 vt( restrain )
 vt( rev )
 vt( roger )
 vt( satisfy )
 vt( scrape )
 vt( seduce )
 vt( shaft )
 vt( shoplift )
 vt( short )
 vt( skip )
 vt( slaughter )
 vt( slug )
 vt( snap )
 vt( sock )
 vt( soften )
 vt( spank )
 vt( stab )
 vt( state  )
 vt( steal )
 vt( steam )
 vt( stifle )
 vt( strangle )
 vt( suborn )
 vt( succor )
 vt( surfeit )
 vt( sustain )
 vt( swab )
 vt( thank )
 vt( traduce )
 vt( transcribe )
 vt( transduce )
 vt( transect )
 vt( transfigure )
 vt( transgress )
 vt( transistorize )
 vt( transliterate )
 vt( transmit )
 vt( transplace )
 vt( transubstantiate )
 vt( unblock )
 vt( unburden )
 vt( undelete )
 vt( underpin )
 vt( undervalue )
 vt( vamp )
 vt( ventilate )
 vt( verbify )
 vt( verify )
 vt( victimize )
 vt( videotape )
 vt( virtualize )
 vt( volley )
 vt( walk )
 vt( waterlog )
 vt( widow )
 vt( wish )
 vt( answer )
 vt( call )
 vt( ask )
 vt( warm )
 vt( chase )
 vt( arrange )
 vt( close )
 vt( open )
 vt( flood )
 vt( help )
 vt( move )
 vt( follow )
 vt( airlift )
 vt( raise ) // 
 vt( check )
 vot( want )
 vot( need )
 vt( fix )
 vt( believe )
 vt( play )
 vt( remember )
 vt( return )
 vt( invite )
 vt( recall )
 vt( zero )
 vt( notice ) // Is it noticed?
 vt( kill )
 vt( investigate )
 vt( finish )
 vt( explore )
 vt( save )
 vt( cross )
 vt( cause )
 vt( expect )
 vot( discover )
 vt( suspect )
 vt( study )
 vt( weaken )
 vt( repair )
 vt( alter )
 vt( climb )
 vt( paint )
 vt( conduct )
 vt( turn )
 vt( fail )
 vt( visit )
 vt( entertain )
 vt( hammer )
 vt( nail )
 vt( wave )
 vt( carry )
 vot( fill )
 vot( require )
 vot( receive )
 vot( push )
 vt( pull )
 vt( watch )
 vt( smoke )
 vt( cook )
 vt( kick )
 vt( thrill )
 vt( borrow )
 vot( water )
 vt( design )
 vot( involve )
 vt( announce )
 vt( drop ) // The numbers dropped even more in later decades.
 vot( wipe )
 vot( prefer )
 vt( dress )
 vt( wash )
 vt( chop )
 vot( mark )
 vot( hate )
 vot( attend )
 vt( ring )
 vot( brush ) // She brushed the suit before hanging it back into the closet.
 vt( plough )
 vot( consider )
 vt( accept )
 vt( troll )
 vt( interrupt )
 vot( reach ) // The climbers failed to reach the top of this mountain
 vt( listen ) // Is she listening the music?
 vot( hyperextend )
 vt( relax )
 vt( rush )
 vt( twist ) // Don't twist my words.
 vot( train ) // Don't train your camera on the women.
 vot( strain ) // Don't strain your mind too much.
 vt( bolt ) // Don't bolt your food!
 vt( force ) // Don't force it!
 vt( scratch ) // Don't scratch your insect bites!
 vt( excite ) // The political reforms excited unrest among to population.
 vt( outmaneuver ) // My new supervisor knows how to outmaneuver the boss in most situations.
 vt( explain )
 vt( think ) // Tell me what you think
 vt( discuss ) // Let's not discuss it.
 vt( dispense ) // Let's not purposelessly dispense the aid.
 vt( tone ) // Let's tone our muscles.
 vt( synchronize ) // Let's synchronize our efforts.
 vt( recapitulate ) // Let's recapitulate the main ideas.
 vt( unwrap ) // Let's unwrap the gifts!
 vt( crash ) // Let's crash the party!
 vt( rent ) // Let's rent a car.
 vot( avoid ) // Let's avoid a confrontation.
 vt( treat ) // Let's treat the prisoners of war humanely.
 vt( liven ) // Let's liven up this room a bit.
 vt( hoof ) // Let's hoof it to the disco.
 vt( perform ) // He performed a great feat.
 vot( provide ) // The agency provided placement services.
 vt( face ) // The proposal faces tough sledding.
 vt( gain ) // They are presently attempting to gain a foothold in the Russian market.
 vt( shower ) // He showered her with caresses.
 vt( afford ) // the transaction afforded him a good profit
 vt( try ) // Try this one more time
 vt( offer ) // I offer Mary some chocolate.
 vt( consult ) // He had to consult his associate before continuing.
 vt( start ) // I saw the instructions before starting the program
 vt( "re-check" ) // She wisely decided to re-check her homework before submitting it. 
 vt( cover ) // He covered the miter with glue before making the joint.
 vt( submit )
 vt( Bone ) // Bone the turkey before roasting it.
 vt( Parboil ) // Parboil the beans before freezing them.
 vt( Tense ) // Tense the rope manually before tensing the spring.
 vt( Sanitize ) // Sanitize a document before releasing it to the press.
 vt( format ) // Please format this disk before entering data!
 vt( Scaffold ) // Scaffold the building before painting it.
 vt( Dredge ) // Dredge the chicken in flour before frying it.
 vt( Flour ) // Flour fish or meat before frying it.
 vt( Score ) // Score the clay before firing it.
 vt( Wrap ) // Wrap the baby before taking her out.
 vt( Disjoint ) // Disjoint the chicken before cooking it.
 vt( Bread ) // Bread the pork chops before frying them.
 vt( "Rough-sand" ) // Rough-sand the door before painting it.
 vt( Crate ) // Crate the paintings before shipping them to the museum.
 vt( roast ) // Bone the turkey before roasting it.
 vt( enter ) // Please format this disk before entering data!
 vt( fire ) // Score the clay before firing it.
 vt( ship ) // Crate the paintings before shipping them to the museum.
 vt( rob ) // We disguised our faces before robbing the bank.
 vt( drag ) // Don't drag me into this business.
 vt( delay )
 vt( dislike ) // He disliked long farewells.
 vt( plan ) // The breakout was carefully planned.
 vt( sign ) // Don't sign a contract without reading the fine print.
 vt( stretch ) // The rope was tautly stretched.
 vt( appoint ) // This government building is sumptuously appointed.
 vt( circulate ) // This memo was circulated interdepartmentally.
 vt( gift ) // She is incomparably gifted.
 vt( prepare ) // He was adequately prepared.
 vt( bear ) // This child was born illegitimately.
 vt( seal ) // This bag is hermetically sealed.
 vt( match ) // Metrically, these poems are matched.
 vt( adjust ) // Prices are seasonally adjusted.
 vt( sniff ) // He sniffed the perfume voluptuously.
 vt( decline ) // I must regretfully decline your kind invitation.
 vt( apply ) // I applied my attention prosaically to my routine.
 vt( calculate ) // We can calculate the position of the particles probabilistically.
 vt( serve ) // He served his country meritoriously.
 vt( threat ) // This new leader meanly threatens the deepest values of our society.
 vt( dance ) // She danced the part of the Black Swan very lyrically.
 vt( pile ) // Garbage was piled sky-high.
 vt( link ) // They were romantically linked.
 vt( flavor ) // The soup was pungently flavored.
 vt( decide ) // He decided the case disinterestedly.
 vt( declare ) // Interfaces are declared by using the keyword
 vt( translate ) // The sentence is translated without regard to the context.
 vt( discharge ) // He was dishonorably discharged.
 vt( pack ) // The children were packed compactly into the car.
 vt( tire ) // Harry was tired after the game of football
 vt( propose ) // Domestically, the president proposes a more moderate economic policy.
 vt( trust ) // I implicitly trust him.
 vt( challenge ) // The young members challenged their leader impiously.
 vt( repeat ) // He repeated his position unrepentantly.
 vt( acquit ) // he was acquitted of murder
 vt( allow ) // An animal, but not a dog is allowed
 vt( regard ) // She regarded the food suspiciously.
 vt( whirle ) // Dust is whirled aloft.
 vt( convict ) // He was convicted circumstantially.
 vt( deny ) // He vehemently denied the accusations against him.
 vt( describe ) // He describes his adventures vivaciously.
 vt( recommend ) // I can unreservedly recommend this restaurant!
 vt( neglect ) // The garden was criminally neglected.
 vt( disorganize ) // The room was chaotically disorganized.
 vt( threaten ) // This new leader meanly threatens the deepest values of our society.
 vt( disperse ) // Particles were colloidally dispersed in the medium.
 vt( invest ) // He invested his fortune astutely.
 vt( annoy ) // His bureaucratic behavior annoyed his colleagues
 vt( rule )
 vt( enjoy ) // She enjoyed the wedding vicariously
 vt( assemble ) // He quickly assembled the fitted pieces
 vt( grant ) // A privilege was granted only to him.
 vt( accrete ) // The story accreted emotion.
 vt( prim ) // She primmed her lips after every bite of food.
 vt( crystallize ) // He tried to crystallize his thoughts.
 vt( fork ) // She forked her fingers.
 vt( reflect ) // His long face lugubriously reflects a hidden and unexpressed compassion.
 vt( slip ) // Obediently she slipped off her right shoe and stocking.
 vt( anticipate ) // He prophetically anticipated the disaster.
 vt( moderate ) // Moderate your speed.
 vt( round ) // Round the edges.
 vt( roll ) // Roll a cigarette.
 vt( shape ) // Shape the dough.
 vt( Scallop ) // Scallop the hem of the dress.
 vt( square ) // Square the wood with a file.
 vt( resuspend ) // Resuspend particles.
 vt( convert ) // Convert centimeters into inches.
 vt( Bulletproof ) // Bulletproof the car.
 vt( Childproof ) // Childproof the apartment.
 vt( Foolproof ) // Foolproof this appliance.
 vt( Consolidate ) // Consolidate fibers into boards.
 vt( Optimize ) // Optimize your resources.
 vt( choke ) // Choke a carburetor.
 vt( pick ) // Pick meat from a bone.
 vt( Crumb ) // Crumb the table.
 vt( add ) // Add insult to injury.
 vt( mix ) // Mix water into the drink.
 vt( Iodize ) // Iodize salt.
 vt( Mercerize ) // Mercerize cotton.
 vt( Fluoridize ) // Fluoridize the teeth of children.
 vt( plug ) // Plug the wall.
 vt( Concatenate ) // Concatenate terms.
 vt( pep ) // Pep up your paper.
 vt( juice ) // Juice up a party.
 vt( combine ) // Combine resources.
 vt( stump ) // Stump a field.
 vt( declaw ) // Declaw a cat.
 vt( Defang ) // Defang the poisonous snake.
 vt( shell ) // Shell the legumes.
 vt( tusk ) // Tusk an elephant.
 vt( Qualify ) // Qualify these remarks.
 vt( Bowdlerize ) // Bowdlerize a novel.
 vt( develop ) // He developed a new kind of apple.
 vt( mellow ) // The sun mellowed the fruit.
 vt( callus ) // The long march had callused his feet.
 vt( distend ) // The gas distended the animal's body.
 vt( swell ) // The water swells the wood.
 vt( leak ) // The container leaked gasoline.
 vt( bilge ) // The collision bilged the vessel.
 vt( bruise ) // The customer bruised the strawberries by squeezing them.
 vt( piece ) // She pieced the china cup.
 vt( point ) // Point a chimney.
 vt( patch ) // Patch a hole.
 vt( inflate ) // Inflate a balloons.
 vt( reflate ) // Reflate the balloon.
 vt( puff ) // The estimates were puffed up.
 vt( ossify ) // The disease ossified the tissue.
 vt( sensitize ) // He was not sensitized to her emotional needs.
 vt( corrode ) // The acid corroded the metal.
 vt( erode ) // Rain eroded the terraces.
 vt( tidy ) // Tidy up your room!
 vt( mess ) // He messed up his room.
 vt( order ) // Order the photos chronologically.
 vt( chronologize ) // The archivist chronologized the documents.
 vt( Hydrate ) // Hydrate your skin.
 vt( Strengthen ) // Strengthen the relations between the two countries.
 vt( Undergird ) // Undergird the ship.
 vt( Distill ) // Distill the essence of this compound.
 vt( Heighten ) // Heighten the tension.
 vt( Potentiate ) // Potentiate the drug.
 vt( Capsulize ) // Capsulize the news.
 vt( Condense ) // Condense the contents of a book into a summary.
 vt( Triple ) // Triple your income!
 vt( Multiply ) // Multiply a letter.
 vt( Elaborate ) // Elaborate a plan.
 vt( Straighten ) // Straighten this post.
 vt( "Rough-dry" ) // Rough-dry the laundry.
 vt( "Freeze-dry" ) // Freeze-dry the strawberries.
 vt( "Clear-cut" ) // Clear-cut an acre of forest.
 vt( correlate ) // Urbanization in Spain is correlated with a fall in reproductive rate.
 vt( improve ) // The editor improved the manuscript with his changes.
 vt( intensify ) // Her rudeness intensified his dislike for her.
 vt( deepen ) // This event only deepened my convictions.
 vt( squeeze ) // The customer bruised the strawberries by squeezing them.
 vt( grow ) // He grows vegetables in his backyard.
 vt( age ) // The death of his child aged him tremendously.
 vt( deactivate ) // They deactivated the file.
 vt( petrify ) // The horror petrified his feelings.
 vt( fracture ) // This writer really fractures the language.
 vt( humidify ) // We have a machine that humidifies the air in the house.
 vt( dehumidify ) // The air conditioner dehumidifies the air in the summer.
 vt( lave ) // The waves laved the shore.
 vt( moisten ) // The dew moistened the meadows.
 vt( moil ) // Her tears moiled the letter.
 vt( depress ) // The rising inflation depressed the economy.
 vt( stultify ) // Their behavior stultified the boss's hard work.
 vt( undergrow ) // The moss undergrew the stone patio.
 vt( overgrow ) // The ivy overgrew the patio.
 vt( shrink ) // Hot water will shrink the sweater.
 vt( merge ) // We merged our resources.
 vt( reverse ) // The trend was reversed.
 vt( convince ) // He was wholly convinced.
 vt( award ) // The scholarships will be awarded noncompetitively.
 vt( oppose ) // We are absolutely opposed to the idea.
 vt( vitalize ) // The eggs are vitalized.
 vt( knock ) // The windows were knocked out.
 vt( clog ) // The story was clogged with too many details.
 vt( deforest ) // The landscape was deforested by the enemy attacks.
 vt( scalp ) // The enemies were scalped.
 vt( black ) // Parts of the newspaper article were blacked out.
 vt( blank ) // Several line in the report were blanked out.
 vt( screw ) // Emotions were screwed up.
 vt( geminate ) // The consonants are geminated in these words.
 vt( marry ) // They were unlawfully married.
 vt( remodel ) // We are remodeling these rooms.
 vt( plum ) // The chimneys were pluming the sky.
 vt( locate ) // The theater is centrally located.
 vt( gather ) // We were gathered together.
 vt( line ) // His books were lined up unsystematically on the shelf.
 vt( connect ) // The two phenomena are intimately connected.
 vt( delight ) // They were secretly delighted at his embarrassment.
 vt( recognize ) // The club will be formally recognized.
 vt( narrow ) // The arteries were diffusely narrowed.
 vt( induce ) // Such effects can be induced reflexly.
 vt( demonstrate ) // This was strikingly demonstrated.
 vt( jumble ) // The papers were hopelessly jumbled.
 vt( depict ) // The flower had been correctly depicted by his son.
 vt( single ) // He was unjustly singled out for punishment.
 vt( engage ) // They were busily engaged in buying souvenirs.
 vt( carve ) // The cradle was ornately carved.
 vt( divide ) // It was divided half-and-half.
 vt( swear ) // He was ceremonially sworn in as President.
 vt( surprise ) // He had been unpleasantly surprised.
 vt( increase ) // The voltage was increased stepwise.
 vt( sum ) // The history is summed up concisely in this book.
 vt( condemn ) // This internationally known writer was foully condemned by the Muslim fundamentalists.
 vt( determine ) // This can be experimentally determined.
 vt( trim ) // The bush was trimmed pyramidically.
 vt( scatter ) // The houses were randomly scattered.
 vt( extend ) // The application of the law was extended farther.
 vt( lower ) // He humbly lowered his head.
 vt( approve ) // The Senate unanimously approved the bill.
 vt( interpret ) // He interprets the law broadly.
 vt( incline ) // He was negatively inclined.
 vt( confirm ) // He confirmed the wetness of the swimming trunks.
 vt( deserve ) // His display of foulness deserved severe punishment.
 vt( revive ) // A hot soup will revive me.
 vt( mousse ) // She mousses her hair.
 vt( exercise ) // This puzzle will exercise your mind.
 vt( alkalize ) // The oxide is alkalized.
 vt( allegorize ) // The story was allegorized over time.
 vt( readapt ) // He readapted himself.
 vt( Gentrify ) // Gentrify a row of old houses.
 vt( Catheterize ) // Catheterize the patient's bladder.
 vt( moon ) // Moon the audience.
 vt( occult ) // The lids were occulting her eyes.
 vt( block ) // The thick curtain blocked the action on the stage.
 vt( demo ) // We will demo the new software in Washington.
 vt( attaint ) // The man was attainted.
 vt( obey ) // The child is taught to obey her parents.
 vt( Alphabetize ) // Alphabetize the list.
 vt( Bleach ) // Bleach the laundry.
 vt( Randomize ) // Randomize the order of the numbers.
 vt( blacken ) // The smoke blackened the ceiling.
 vt( whiten ) // This detergent will whiten your laundry.
 vt( sallow ) // The illness has sallowed her face.
 vt( nod ) // She nodded her head dully.
 vt( Lighten ) // Lighten the burden of caring for her elderly parents.
 vt( View ) // View a show on television.
 vt( warn ) // I ought to warn you about that
 vt( escape ) // It is impossible to escape the dogging fears.
 vt( celebrate ) // They celebrated his election.
 vt( debate ) // They debated the truth of the proposition.
 vt( resume ) // We resumed the interrupted discussion.
 vt( manage )
 vt( employ ) // An open shop employs nonunion workers.
 vt( launch ) // Launch a ship.
 vt( Project ) // Project a missile.
 vt( Wreathe ) // Wreathe the grave site.
 vt( Frost ) // Frost a cake.
 vt( Upend ) // Upend the box and empty the contents.
 vt( empty )
 vt( Intertwine ) // Intertwine the ribbons.
 vt( Twine ) // Twine the threads into a rope.
 vt( Untwine ) // Untwine the strings.
 vt( Pleach ) // Pleach a hedge.
 vt( Unbraid ) // Unbraid my hair.
 vt( Vandalize ) // Vandalize the park.
 vt( key ) // His new Mercedes was keyed last night in the parking lot.
 vt( relace ) // She relaced her boots.
 vt( Wind ) // Wind your watch.
 vt( Cheese ) // Cheese the yarn.
 vt( unreel ) // Unreel the tape.
 vt( jampack ) // The theater was jampacked.
 vt( stuff ) // The child stuffed candy into his pockets.
 vt( overstuff ) // The pillow was overstuffed.
 vt( Lodge ) // Lodge a bullet in the table.
 vt( Puddle ) // Puddle young plants.
 vt( pot ) // He potted the palm.
 vt( grain ) // His hands were grained with dirt.
 vt( handwash ) // This delicate sweater must be handwashed.
 vt( Speckle ) // Speckle the wall with tiny yellow spots.
 vt( stipple ) // The sunlight stippled the trees.
 vt( spatter ) // The baby spattered the bib with food.
 vt( Anatomize ) // Anatomize the bodies of the victims of this strange disease.
 vt( Trisect ) // Trisect a line.
 vt( pockmark ) // Her face was pockmarked by the disease.
 vt( Whittle ) // Whittle a piece of wood.
 vt( Cleave ) // Cleave the bone.
 vt( part ) // Moses parted the Red Sea.
 vt( sever ) // His head was severed from his body.
 vt( Segment ) // Segment an orange.
 vt( Syllabify ) // Syllabify the words.
 vt( pound ) // The locks pound the water of the canal.
 vt( explode ) // The enemy exploded the bridge.
 vt( shipwreck ) // The vessel was shipwrecked.
 vt( Afforest ) // Afforest the mountains.
 vt( suffocate ) // The child suffocated herself with a plastic bag that the parents had left on the floor.
 vt( retrofit ) // The mansion was retrofitted with modern plumbing.
 vt( Tear ) // Tear the paper.
 vt( posit ) // She posited her hand on his shoulder.
 vt( redeposit ) // The water had redeposited minerals on the rocks.
 vt( Drift ) // Drift the cattle herds westwards.
 vt( Dip ) // Dip the garment into the cleaning solution.
 vt( Submerge ) // Submerge your head completely.
 vt( Ladle ) // Ladle the water out of the bowl.
 vt( Slop ) // Slop the food onto the plate.
 vt( Spoon ) // Spoon the sauce over the roast.
 vt( Divaricate ) // Divaricate one's fingers.
 vt( invaginate ) // The chrysalis is invaginated.
 vt( bathe ) // The room was bathed in sunlight.
 vt( swallow ) // The huge waves swallowed the small boat and it sank shortly thereafter.
 vt( Trace ) // Trace the outline of a figure in the sand.
 vt( Cone ) // Cone a tire.
 vt( separate ) // He separated the fighting children.
 vt( indicate ) // Amphoric breathing indicates a cavity in the lung.
 vt( perceive ) // We perceived the change only dimly.
 vt( crack ) // He cracked his knuckles restlessly.
 vt( snatch ) // He snatched the bills clumsily.
 vt( tackle ) // We must tackle these tasks boldly.
 vt( hire ) // We hired her on the spot.
 vt( scan ) // Hastily, he scanned the headlines.
 vt( bottleneck ) // His laziness has bottlenecked our efforts to reform the system.
 vt( Excogitate ) // Excogitate a way to measure the speed of light.
 vt( stipulate ) // Perennial efforts to stipulate the requirements
 vt( pry ) // They pried the information out of him.
 vt( schematize ) // The chemists schematized the various reactions in a coherent fashion.
 vt( render ) // The estate renders some revenue for the family.
 vt( conjure ) // He conjured wild birds in the air.
 vt( overproduce ) // The country overproduces cars.
 vt( perch ) // She perched her hat on her head.
 vt( hoist ) // They hoisted the patient onto the operating table.
 vt( trench ) // He trenched his military camp.
 vt( lean ) // He leaned his rifle against the wall.
 vt( clap ) // The judge clapped him in jail.
 vt( mantle ) // The ivy mantles the building.
 vt( grass ) // The owners decided to grass their property.
 vt( button ) // He cannot button his shirt with his slinged arm.
 vt( piggyback ) // He piggybacked her child so she could see the show.
 vt( juggle ) // The player juggled the ball.
 vt( eagle ) // She eagled the hole.
 vt( hitch ) // He hitched up his socks and pants.
 vt( jimmy ) // The burglar jimmied the lock.
 vt( continue ) // readiness to continue discussions
 vt( admit ) // Loath to admit a mistake
 vt( destruct ) // The engineers had to destruct the rocket for safety reasons.
 vt( tack ) // He tacked together some verses.
 vt( craft ) // The artisan crafted a complicated tool.
 vt( handcraft ) // We handcraft all our paper.
 vt( inspire ) // The article about the artist inspired the exhibition of his recent work.
 vt( provoke ) // Her behavior provoked a quarrel between the couple.
 vt( pioneer ) // She pioneered a graduate program for women students.
 vt( action ) // He actioned the operation.
 vt( envision ) // I cannot envision him as President.
 vt( fantasize ) // He is fantasizing the ideal wife.
 vt( fictionalize ) // The writer fictionalized the lives of his parents in his latest novel.
 vt( Spatchcock ) // Spatchcock a guinea hen.
 vt( work ) // Work the metal into a sword.
 vt( Press ) // Press a record.
 vt( Machinate ) // Machinate a plot.
 vt( Phase ) // Phase a withdrawal.
 vt( Mount ) // Mount a campaign against pornography.
 vt( Concord ) // Concord the conditions for the marriage of the Prince of Wales with a commoner.
 vt( Actuate ) // Actuate the circuits.
 vt( "Re-create" ) // Re-create the boom of the West on a small scale.
 vt( Hedge ) // Hedge the property.
 vt( Tap ) // Tap a maple tree for its syrup.
 vt( Dribble ) // Dribble oil into the mixture.
 vt( Load ) // Load the bags onto the trucks.
 vt( Cram ) // Cram books into the suitcase.
 vt( Girdle ) // Girdle the plant.
 vt( Macadam ) // Macadam the road.
 vt( Limber ) // Limber a cannon.
 vt( Lime ) // Lime the lawn.
 vt( Concrete ) // Concrete the walls.
 vt( Croquet ) // Croquet the opponent's ball.
 vt( Crape ) // Crape the mirror.
 vt( Comb ) // Comb your hair.
 vt( Jerk ) // Jerk his head.
 vt( Stake ) // Stake your goat.
 vt( Winch ) // Winch up the slack line.
 vt( Pluck ) // Pluck the flowers off the bush.
 vt( Tweeze ) // Tweeze facial hair.
 vt( conceive ) // This library was well conceived.
 vt( gradate ) // These lines are gradated.
 vt( coapt ) // The wounds were coapted.
 vt( wire ) // The columns were wired to the beams for support.
 vt( badge ) // The workers here must be badged.
 vt( plot ) // The writer is plotting a new novel.
 vt( remake ) // She is remaking her image.
 vt( overwork ) // This play has been overworked.
 vt( derive ) // Some of these drugs have been derived from opium
 vt( underperform ) // Her plays are underperformed, although they are very good.

 vt( demyelinate ) // The disease demyelinated the nerve fibers.
 vt( script ) // The playwright scripted the movie.
 vt( etch ) // He etched her image into the surface.
 vt( fringe ) // The weaver fringed the scarf.
 vt( mimick ) // The actor mimicked the President very accurately.
 vt( overcrop ) // The farmers overcropped the land.
 vt( reproduce ) // He reproduced the feeling of sadness in the portrait.
 vt( extemporize ) // He extemporized a speech at the wedding.
 vt( psalm ) // He psalms the works of God.
 vt( portray ) // The actor portrays an elderly, lonely man.
 vt( reenact ) // They reenacted the battle of Princeton.
 vt( versify ) // He versified the ancient saga.
 vt( metrify ) // The bard metrified his poems very precisely.
 vt( author ) // She authored this play.
 vt( compose ) // Beethoven composed nine symphonies.
 vt( recopy ) // The child had to recopy the homework.
 vt( crosshatch ) // The draftsman crosshatched the area.
 vt( stenograph ) // The students were able to stenograph and record the conversation.
 vt( tinsel ) // Snow flakes tinseled the trees.
 vt( knot ) // She knotted her fingers.
 vt( fagot ) // He fagotted the blouse for his wife.
 vt( brew ) // People have been brewing beer for thousands of years.
 vt( redeposit ) // The water had redeposited minerals on the rocks.
 vt( hoe ) // He is hoeing the flower beds.
 vt( rubricate ) // The manuscript is not rubricated.
 vt( honeycomb ) // The cliffs were honeycombed.
 vt( film ) // The coronation was filmed.
 vt( map ) // Sorrow was mapped on the mother's face.
 vt( tart ) // The small-town bar was all tarted up.
 vt( flag ) // The building was flagged for the holiday.
 vt( hem ) // The building was hemmed in by flowers.
 vt( badge ) // The workers here must be badged.
 vt( touch ) // The storyteller touched a chord.
 vt( Rekindle ) // Rekindle her love.
 vt( prick ) // The thought of her unhappiness pricked his conscience.
 vt( ignite ) // The ostentatious way of living of the rich ignites the hatred of the poor.
 vt( stir ) // The refugees' fate stirred up compassion around the world.
 vt( ferment ) // Islam is fermenting Africa.
 vt( jolt ) // The audience was jolted by the play.
 vt( cloud ) // Their faces were clouded with sadness.
 vt( wow ) // The speaker wowed the audience.
 vt( worship ) // Many Hindus worship Shiva.
 vt( fear ) // I fear the winters in Moscow.
 vt( bully ) // Her big brother always bullied her when she was young.
 vt( prepossess ) // The idea of his failure prepossesses him.
 vt( dissolve ) // The news dissolved her into tears.
 vt( miff ) // His behavior really miffed me.
 vt( Ruffle ) // Ruffle somebody's composure.
 vt( deflect ) // He deflected his competitors.
 vt( claim ) // The couple that wanted to adopt the child lost her when the biological parents claimed her.
 vt( mourn ) // She is mourning her dead child.
 vt( grieve ) // His behavior grieves his mother.
 vt( distress ) // The news of her child's illness distressed the mother.
 vt( Rack ) // Rack one's brains.
 vt( criticise ) // He humiliated his colleague by criticising him in front of the boss.
 vt( smash ) // The death of her son smashed her.
 vt( humanize ) // The mayor tried to humanize life in the big city.
 vt( lament ) // We lamented the death of the child.
 vt( tempt ) // The window displays tempted the shoppers.
 vt( intend ) // The advertisement is intended to tease the customers.
 vt( typeset ) // My book will be typeset nicely.
 vt( paragraph ) // 
 vt( inebriate ) // He was inebriated by his phenomenal success.
 vt( overjoy ) // The economic growth overjoyed the German industry.
 vt( ease ) // The news eased my conscience.
 vt( chill ) // The news of the city's surrender chilled the soldiers.
 vt( feast ) // She feasted her eyes on the Tuscan landscape.
 vt( condole ) // You must condole the widow.
 vt( disarm ) // Her charm disarmed the prosecution lawyer completely.
 vt( disgruntle ) // The employees were disgruntled by their bad working conditions.
 vt( spook ) // The noise spooked the horse.
 vt( hop ) // She hopped a train to Chicago.
 vt( sheer ) // She sheered her car around the obstacle.
 vt( affright ) // Ghosts could never affright her.
 vt( charge ) // The speaker charged up the crowd with his inflammatory remarks.
 vt( Channelize ) // Channelize the country for better transportation.
 vt( Indent ) // Indent the paragraphs of a letter.
 vt( Triplicate ) // Triplicate the letter for the committee.
 vt( Quadruplicate ) // Quadruplicate the bill.
 vt( Rag ) // Rag that old tune.
 vt( Reharmonize ) // Reharmonize the melody.
 vt( Re-write ) // Re-write a play for use in schools.
 vt( Draft ) // Draft a speech.
 vt( Sketch ) // Sketch the building.
 vt( Superscribe ) // Superscribe an envelope.
 vt( Panel ) // Panel the walls with wood.
 vt( Extrude ) // Extrude steel.
 vt( Crochet ) // Crochet a bedspread.
 vt( Caparison ) // Caparison the horses for the festive occasion.
 vt( Bead ) // Bead the wedding gown.
 vt( Macrame ) // Macrame a plant holder.
 vt( Retread ) // Retread an old plot.
 vt( Fledge ) // Fledge an arrow.
 vt( Precook ) // Precook the rice.
 vt( center ) // That vase in the picture is not centered.
 vt( "re-enter" ) // You cannot re-enter the country with this visa.
 vt( pump ) // The athlete pumps weights in the gym.
 vt( transit ) // The canal will transit hundreds of ships every day.
 vt( suction ) // The doctors had to suction the water from the patient's lungs.
 vt( evacuate ) // After the earthquake, residents were evacuated.
 vt( suggest ) // He suggested a better formulation.
 vt( rein ) // He reined in his horses in front of the post office
 vt( stall ) // I keep stalling the car.
 vt( jostle ) // The passengers jostled each other in the overcrowded train.
 vt( float ) // He floated the logs down the river.
 vt( refloat ) // Refloat a grounded boat.
 vt( reciprocate ) // The engine reciprocates the propeller.
 vt( rock ) // Rock the cradle.
 vt( sway ) // The wind swayed the trees gently.
 vt( lash ) // The lion lashed its tail.
 vt( roam ) // The gypsies roamed the woods.
 vt( tramp ) // We had to tramp the creeks.
 vt( Shift ) // Shift one's position.
 vt( Sparge ) // Sparge the water.
 vt( wag ) // The happy dog wagged his tail.
 vt( trip ) // The questions on the test tripped him up.
 vt( trot ) // She trotted the horse home.
 vt( Circle ) // Circle the globe.
 vt( compass ) // We compassed the earth.
 vt( decussate ) // This nerve decussates the other.
 vt( Wade ) // Wade the pond.
 vt( prowl ) // The suspicious stranger prowls the streets of the town.
 vt( remount ) // He remounted his horse.
 vt( buzz ) // Planes buzzed the crowds in the square.
 vt( parade ) // She parades her new husband around town.
 vt( cruise ) // She cruised the neighborhood in her new convertible.
 vt( Helm ) // Helm the ship.
 vt( navigate ) // He navigated his way to the altar.
 vt( Park ) // Park the car in front of the library.
 vt( head ) // We were headed for the mountains.
 vt( levitate ) // The magician levitated the woman.
 vt( Row ) // Row the boat across the lake.
 vt( Scull ) // Scull the boat.
 vt( fasten ) // They fastened various nicknames to each other.
 vt( Roughen ) // Roughen the surfaces so they will stick to each other.
 vt( republish ) // The scientist republished his results after he made some corrections.
 vt( reinstall ) // She reinstalled the washer after it had been repaired.
 vt( Solmizate ) // Solmizate a song before you learn the lyrics.
 vt( premiere ) // We premiered the opera of the young composer and it was a critical success.
 vt( Paddle ) // Paddle your own canoe.
 vt( Refer ) // Refer a patient to a specialist.
 vt( redirect ) // Redirect your attention to the danger from the fundamentalists.
 vt( Truck ) // Truck fresh vegetables across the mountains.
 vt( saltate ) // The sand grains are saltated by the wind.
 vt( ascend ) // We ascended the mountain.
 vt( Reef ) // Reef the sailboat's mast.
 vt( dump ) // The truck dumped the garbage in the street.
 vt( undershoot ) // The plane undershot the runway.
 vt( assume ) // He assumes the lotus position.
 vt( capsize )
 vt( space ) // Space the interviews so that you have some time between the different candidates.
 vt( nose ) // She nosed the car into the left lane.
 vt( advance ) // We have to advance clocks and watches when we travel eastward.
 vt( back ) // Back the car into the parking spot.
 vt( Hand ) // Hand the elderly lady into the taxi.
 vt( Stalk ) // Stalk the woods for deer.
 vt( hike ) // The landlord hiked up the rents.
 vt( land ) // The enemy landed several of our aircraft.
 vt( derail ) // They had planned to derail the trains that carried atomic waste.
 vt( penetrate ) // The hikers did not manage to penetrate the dense forest.
 vt( notify ) // In the meantime the police were notified.
 vt( breast ) // They breasted the mountain.
 vt( ground ) // The storm grounded the ship.
 vt( overrun ) // Marauding rebels overran the countryside.
 vt(  jam ) // The driver jammed the brake pedal to the floor.
 vt( crowd ) // Men in straw boaters and waxed mustaches crowded the verandah.
 vt( surcharge ) // The air raids had surcharged the emergency wards.
 vt( herd ) // We herded the children into a spare classroom.
 vt( disband ) // The principal disbanded the political student organization.
 vt( crook ) // He crooked his index finger.
 vt( overarch ) // Big rocks overarch the stream.
 vt( bank ) // The pilot had to bank the aircraft.
 vt( Tip ) // Tip the screen upward.
 vt( orbit ) // The planets are orbiting the sun.
 vt( angle ) // He angled his way into the room.
 vt( rotate ) // Ballet dancers can rotate their legs out by 90 degrees.
 vt( splay ) // He splayed his huge hands over the table.
 vt( wheel ) // They wheeled their horses around and left.
 vt( mill ) // Clean grain before milling it.
 vt( negotiate ) // The hiker negociated the high mountain pass.
 vt( Reeve ) // Reeve a rope.
 vt( approach ) // We were approaching our destination.
 vt( Unfold ) // Unfold the newspaper.
 vt( hunt ) // They hunted the unwanted immigrants out of the neighborhood.
 vt( race ) // The psychologist raced the rats through a long maze.
 vt( uncurl ) // He uncurled himself.
 vt( flow ) // The artist flowed the washes on the paper.
 vt( Pour ) // Pour water over the floor.
 vt( transfer ) // Transfer the packet from his trouser pockets to a pocket in his jacket.
 vt( hasten ) // In truth, moral decay hastened the decline of the Roman Empire.
 vt( count ) // He counted the ticks of the clock.
 vt( eject ) // The hose ejected a stream of water.
 vot( maintain ) // They maintained close relations with England even after independence.
 vt( Church ) // Church a woman after childbirth.
 vt( whisk ) // The President was whisked away in his limo.
 vt( march ) // They marched the mules into the desert.
 vt( stampede ) // Thunderbolts can stampede animals.
 vt( Evert ) // Evert the eyelid.
 vt( flap ) // The bird flapped its wings.
 vt( bench ) // Bench the poodles at the dog show.
 vt( transplant ) // Transplant the young rice plants.
 vt( record ) // Some protestors record patients on camera.
 vt( privatize ) // Alberta also privatized alcohol distribution.

 vt( educate )
 vt( coeducate )
 vt( miseducate )
 vt( estimate )
 vt( misestimate )
 vt( underrepresent ) // Urban interests were consistently underrepresented in the legislature.
 vt(found) // In 1956 the Uruguayan Anarchist Federation was founded.
 vt(tilt) // The rotor is tilted backward.
 vt(demand) // Aglaulus demands money in exchange.
 vt(name)
 vt(deemphasize) // Civil rights, however, were deemphasized.
 
 vot(confess) // I shudder to confess them.

 vot(predecease) // The two predeceased their father.
 
/*
 vt(  )
 vt(  )
 vt(  )
 vt(  )
 vt(  )
 vt(  )
 vt(  )
*/
}
