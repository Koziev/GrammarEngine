// Сочетаемость глагола и предлога (без учета объекта у предлога)
facts eng_v_prep_score language=English
{
 arity=2
 return=integer
}

#define vp(v,p,w) \
#begin
fact eng_v_prep_score
{
 if context { eng_verb:v{} eng_prep:p{} }
  then return w
}
#end

vp( fight, against, 5 ) // He fought against Charles Taylor's militia.
vp( convert, among, 1 ) // They cannot proselytize or convert among Muslims.
vp( care, for, 5 ) // Why should I care for that shield?
vp( broadcast, across, 5 )
vp( transfer, "out of", 5 )
vp( soar, into, 5 ) // The eagle beat its wings and soared high into the sky.
vp( speak, to, 5 ) // I have spoken to nobody about you
vp( fly, over, 2 ) // They flew out over Skegness and Cromer.
vp( form, from, 5 )
vp( travel, toward, 5 )
vp( shield, with, 5 )
vp( pull, over, 5 )
vp( explain, to, 5 )
vp( land, on, 5 )
vp( act, on, 5 )
vp( Look, into, 5 )
vp( erupt, from, 5 )
vp( Multiply, by, 5 )
vp( Subtract, from, 5 )
vp( compose, of, 5 )
vp( descend, from, 5 )
vp( react, to, 5 )
vp( spread, from, 5 )
vp( bind, to, 5 ) // Each antibody binds to a specific antigen;
vp( link, with, 5 ) // Cantor linked the Absolute Infinite with God.
vp( provide, with, 5 ) // Pakistan also provides Belarus with Military expertise.
vp( knock, "out of", 5 ) // Bermuda were knocked out of the World Cup.
vp( work, on, 5 ) // She also continued to work on sculpture.
vp( sacrifice, to, 2 ) // A goat was being sacrificed to her.
vp( fall, into, 5 ) // These names have now fallen into disuse.
vp( contaminate, with, 5 ) // The fish consumed by the birds are contaminated with pesticides.
vp( provide, with, 2 ) // 
vp( dedicate, to, 2 ) // The motion picture was dedicated to Dick.
vp( confine, to, 5 ) // His reputation was not confined to Europe
vp( sculpt, into, 5 ) // She is sculpting the block of marble into an image of her husband.
vp( write, on, 5 ) // The artist wrote Chinese characters on a big piece of white paper.
vp( suction, from, 5 ) // The doctors had to suction the water from the patient's lungs.
vp( travel, through, 5 )
vp( defend, against, 5 )
vp( cooperate, with, 5 ) // The organisms cooperate with each other.
vp( compete, with, 5 ) // The organisms compete with each other.
vp( prey, on, 5 ) // The organisms prey on each other.
vp( fall, from, 5 )
vp( pump, to, 5 ) // Water is pumped to the cabin from a distant reservoir.
vp( pick, from, 5 ) // Plants picked up the pesticides from the coastal soils.
vp( transport, to, 5 )
vp( package, into, 5 )
vp( divide, into, 5 )
vp( condense, into, 5 )
vp( prevent, from, 5 )
vp( bump, into, 5 )
vp( convert, to, 5 )
vp( pass, through, 5 )
vp( move, from, 5 )
vp( share, among, 5 )
vp( project, onto, 5 )
vp(protect,from,5) // Sunblock protects the skin from the sun's harmful Ultraviolet A and Ultraviolet B waves.
vp(learn,about,5)
vp(associate,with,5) // Which interaction is most likely associated with the formation of non-volcanic mountains?
vp(expose,to,5) // Lanthanum oxidizes rapidly when exposed to air.
vp(locate,near,2)
vp(occur,in,6)
vp(cut,into,5) // Cut words into pieces and scramble them.
vp(embed,in,5) // Sesamoid bones are bones embedded in tendons.
vp(drop,on,5) // The bombs are dropping on enemy targets.
vp(drop,below,3)
vp(drop,behind,3) // Temperature at night dropped behind a cold front.
vp(grant,to,5) // A privilege was granted only to him.
vp(release,to,5) // Sanitize a document before releasing it to the press.
vp(fall,on,5) // Her voice fell gratingly on our ears.
vp(spread,on,2) // Spread cheese on a piece of bread.
vp(look,on,5) // Look on the bright side of it.
vp(withdraw,from,5) // 85 was withdrawn from circulation
vp(play,on,5) // She sneered at her little sister's efforts to play the song on the piano
vp(collide,with,5)
vp(spray,with,5) // A farmer sprayed his orange trees with a pesticide
vp(separate,from,5)
vp(combine,into,2)
vp(look,for,5) // Let's look about for help.
vp(criticise,"in front of",5) // He humiliated his colleague by criticising him in front of the boss.
vp(pass,to,5) // He passed the ball to Paul.
vp(introduce,to,5) // He introduced his brother to Susan.
vp(compose,of,5) // Muscle cells are composed of tubular myofibrils.
vp(limit,to,5) // Selection was initially limited to military pilots.
vp(come,from,5) // Where do Morals Come From?
vp(relate,to,5) // Psychometry is related to clairsentience.
vp(respond,to,5) // Psychoacoustics explains how humans respond to sounds.
vp(name,after,5) // Scientific laws named after people.
vp(pay,in,3) // Workers were paid in grain;
vp(disagree,on,5) // Sources disagree on the meaning of the word.
vp(locate,at,5) // The Confederacy's capital was initially located at Montgomery.
vp(base,on,5) // He is based on Aristotle.
vp(record,on,5) // Some protestors record patients on camera.
vp(differ,from,5) // Autistic toddlers differ more strikingly from social norms;
vp(nominate,for,5) // Grant was nominated for president.
vp(bury,at,5) // He was buried at sea.
vp(move,toward,5) // The DNA moves towards anode.
vp(originate,in,5) // It originated in Northern Mesopotamia.
vp(prepare,for,2) // Beowulf prepares himself for battle.
vp(march,to,5) // Protagonists march to the Danube.
vp(break,into,5) // She breaks into the house
vp(settle,on,5) // Dust settled on the roofs.
vp(hang,on,2) // The dress hung formlessly on her body.
vp(focus,on,2) // Much of this focuses on ambiguity tolerance.
vp(depart,for,5) // Martin and Maltby then departed for home.

// --------------------------------------------------------------------------

#define v_at(v) \
#begin
fact eng_v_prep_score
{
 if context { eng_verb:v{} eng_prep:at{} }
  then return 2
}
#end

v_at( hold ) // Her concentrated passion held them at bay.
v_at( gnaw ) // Month by month, the betrayal gnawed at his heart.
v_at( zip ) // The runner zipped past us at breakneck speed.
v_at( incurvate ) // The body incurvates a little at the back.
v_at( see ) // I'll probably see you at the meeting.
v_at( sleep ) // At night the whole family slept in a rough shelter at the edge of the forest.
v_at( leave ) // The ship leaves at midnight.
v_at( turn ) // People turn to mysticism at the turn of a millennium.
v_at( ebb ) // The tides ebbed at noon.
v_at( suck ) //  Mud was sucking at her feet.
v_at( extemporize ) // He extemporized a speech at the wedding.
v_at( approach ) // The car pulled over when the ambulance approached at high speed.
v_at( plunge ) // She plunged at it eagerly.
v_at( thrill ) // The children were thrilled at the prospect of going to the movies.
v_at( horrify ) // I was horrified at the thought of being late for my interview.
v_at( roll ) // They rolled their eyes at his words.
v_at( pick ) // She picked nervously at the buttons of her blouse.
v_at( sneer ) // She sneered at her little sister's efforts to play the song on the piano
v_at( read ) // Read the manual at your leisure.
v_at( post ) // Post a warning at the dump.
v_at( scream ) // She screamed furiously at her tormentors.
v_at( bench ) // Bench the poodles at the dog show.
v_at( delight ) // They were secretly delighted at his embarrassment.
v_at( melt ) // The tree trunks are melting into the forest at dusk.
v_at( keep ) // Keep someone at arm's length.
v_at( total ) // The rock star totals his guitar at every concert.
v_at( put ) // Don't do anything that could put you at risk.
v_at( nibble ) // She nibbled daintily at her cake.
v_at( behave ) // He behaved boorishly at the party.
v_at( float ) // We were floating on air at the news.
v_at( fire ) // Guns fired witheringly at the railroad cars.
v_at( claw ) // He clawed insatiably at the traditional precepts.
v_at( smile ) // She smiled at him seductively.
v_at( glance ) // He glanced at her meaningfully.
v_at( stare ) // I stared at him numbly.
v_at( wink ) // He winked at her roguishly.
v_at( gaze ) // He gazed reverently at the handiwork.
v_at( represent ) // This voice is meagerly represented at the conference.
v_at( look ) // I look at you
v_at( expect ) // Don't expect a good meal at a cabaret.
v_at( drink ) // She drinks the tea at five o'clock
v_at( teach ) // I taught him at school
v_at( stay ) // Normally I stay at home in the evening
v_at( sing ) // Alice sang song at the concert
v_at( have ) // I have a copy of it at home but I haven't read it yet
v_at( stop ) // The train stops at the station
v_at( laugh ) // The babies laughed at the children
//v_at( be ) // These writers were in fashion at the beginning of the century.
v_at( learn ) // They learn English at school
v_at( work ) // The man works at a garage
v_at( meet )  // Let's meet at 11 A.M.
v_at( arrive ) // They had to consult before arriving at a decision.
v_at( study ) // Ultimately, I have been studying Greek at evening classes.

// --------------------------------------------------------------------------

#define v_in(v) \
#begin
fact eng_v_prep_score
{
 if context { eng_verb:v{} eng_prep:in{} }
  then return 2
}
#end

v_in( welter ) // The shipwrecked survivors weltered in the sea for hours.
v_in( propagate ) // Sound and light propagate in this medium.
v_in( cover ) // Quantification in general is covered in the article on quantification.
v_in( freeze ) // The water froze in the pond last night
v_in( fidget ) // The child is always fidgeting in his seat.
v_in( swirl ) // The leaves swirled in the autumn wind.
v_in( whirl ) // Rising smoke whirled in the air.
v_in( tumble ) // The clothes tumbled in the dryer.
v_in( circulate ) // Blood circulates in my veins.
v_in( concentrate ) // These groups concentrate in the inner cities.
v_in( scatter ) // The children scattered in all directions when the teacher approached.
v_in( pullulate ) // Beggars pullulated in the plaza.
v_in( bunch ) // The frightened children bunched together in the corner of the classroom.
v_in( constellate ) // The poets constellate in this town every summer.
v_in( roll ) // He rolled up in a black Mercedes.
v_in( interpret ) // In reality these terms have been interpreted in a number of different ways.
v_in( continue ) // She continued in the direction of the hills.
v_in( rise ) // The dough rose slowly in the warm room.
v_in( land ) // The plane landed in Istanbul.
v_in( crash ) // The plane crashed in the sea.
v_in( galumph ) // The giant tortoises galumphed around in their pen.
v_in( prance ) // The young horse was prancing in the meadow.
v_in( recommit ) // The bill was recommitted three times in the House.
v_in( interfere ) // They had an agreement that they would not interfere in each other's business.
v_in( busk ) // Three young men were busking in the plaza.
v_in( cruise ) // We were cruising in the Caribbean.
v_in( kite ) // Kids were kiting in the park.
v_in( stomp ) // The men stomped through the snow in their heavy boots.
v_in( stagger ) // He staggered along in the heavy snow.
v_in( plod ) // Mules plodded in a circle around a grindstone.
v_in( hike ) // We were hiking in Colorado.
v_in( puddle ) // The ducks and geese puddled in the backyard.
v_in( blow ) // The leaves were blowing in the wind.
v_in( shift ) // He shifted in his seat.
v_in( whip ) // The tall grass whipped in the wind.
v_in( trash ) // The feverish patient thrashed around in his bed.
v_in( slip ) // The ship slipped away in the darkness.
v_in( churn ) // The sea was churning in the storm.
v_in( romp ) // The toddlers romped in the playroom.
v_in( frolick ) // The children frolicked in the garden.
v_in( flap ) // Flags flapped in the strong wind.
v_in( nod ) // The flowers were nodding in the breeze.
v_in( jostle ) // The passengers jostled each other in the overcrowded train.
v_in( skid ) // The car skidded in the curve on the wet road.
v_in( stall ) // The car stalled in the driveway.
v_in( bring ) // The noise brought her up in shock.
v_in( migrate ) // Birds migrate in the Winter.
v_in( crack ) // Ribs crack in your ears with sudden unaccustomed flexion.
v_in( inflate ) // The body inflates in painful increments
v_in( wallow ) // Pigs were wallowing in the mud.
v_in( bog ) // The car bogged down in the sand.
v_in( appear ) // A titillating story appeared in the usually conservative magazine.
v_in( draw ) // The deed was drawn in the lawyer's office.
v_in( paragraph ) //  All her friends were paragraphed in last Monday's paper.
v_in( set ) // The film is set in Africa.
v_in( criticise ) // He humiliated his colleague by criticising him in front of the boss.
v_in( fail ) // His children failed him in the crisis.
v_in( bob ) // The cork bobbed around in the pool.
v_in( writhe ) // The prisoner writhed in discomfort.
v_in( fictionalize ) // The writer fictionalized the lives of his parents in his latest novel.
v_in( clothe ) // The mountain was clothed in tropical trees.
v_in( close ) // They closed in the porch with a fence.
v_in( fence ) // We fenced in our yard.
v_in( clap ) // The judge clapped him in jail.
v_in( remain ) // She remained stubbornly in the same position.
v_in( bathe ) // The room was bathed in sunlight.
v_in( shroud ) // The origins of this civilization are shrouded in mystery.
v_in( soak ) // I soaked in the hot tub for an hour.
v_in( Immerse ) // Immerse yourself in hot water.
v_in( bask ) // The seals were basking in the sun.
v_in( live )
v_in( stay )
v_in( sleep )
v_in( rest )
v_in( perch ) // The birds perched high in the tree.
v_in( wash ) // Wash out your dirty shirt in the sink.
v_in( sandwich ) // She was sandwiched in her airplane seat between two fat men.
v_in( bury ) // He finally could free the legs of the earthquake victim who was buried in the rubble.
v_in( speak ) // She spoke in a calm voice.
v_in( rule ) // Order ruled in the streets.
v_in( leave ) // His brother's success left him in the shade.
v_in( trap ) // He was trapped in a medical swamp.
v_in( result ) // A continuous rearrangement of electrons in the solar atoms results in the emission of light.
v_in( behave ) // He behaved badly in school.
v_in( support ) // We support the armed services in the name of national security.
v_in( use ) // This type of border display is used repetitively in advertising.
v_in( survive ) // His works tenuously survive in the minds of a few scholars.
v_in( sum ) // The history is summed up concisely in this book.
v_in( interest ) // He is interested specifically in poisonous snakes.
v_in( engage ) // They were busily engaged in buying souvenirs.
v_in( display ) // The new car was prominently displayed in the driveway.
v_in( lock ) // Her jewels are locked away in a safe.
v_in( save ) // She was saved in the nick of time.
v_in( accumulate ) // Journals are accumulating in my office.
v_in( geminate ) // The consonants are geminated in these words.
v_in( emend ) // The text was emended in the second edition.
v_in( carry ) // The civil war carried into the neighboring province.
v_in( deepen ) // His dislike for raw fish only deepened in Japan.
v_in( dry ) // The laundry dries in the sun.
v_in( mold ) // The furniture molded in the old house.
v_in( decompose ) // The bodies decomposed in the heat.
v_in( ripen ) // The plums ripen in July.
v_in( grow ) // He grows vegetables in his backyard.
v_in( suffer ) // This author really suffers in translation.
v_in( bulk ) // The parcel bulked in the sack.
v_in( shrink ) // Proof the materials against shrinking in the dryer.
v_in( culminate ) // The helmet culminated in a crest.
v_in( disperse ) // Particles were colloidally dispersed in the medium.
v_in( walk ) // She walked briskly in the cold air.
v_in( act ) // The admiral intends to act offensively in the Mediterranean.
v_in( rustle ) // The leaves rustled tremulously in the wind.
v_in( indulge ) // He wishfully indulged in dreams of fame.
v_in( catch ) // His hair was caught aggravatingly in the branches of the tree.
v_in( go ) // Something has gone awry in our plans.
v_in( toss ) // Fretfully, the baby tossed in his crib.
v_in( fall ) // He fell headlong in love with his cousin.
v_in( believe ) // His followers slavishly believed in his new diet.
v_in( scratch ) // A single chicken was scratching forlornly in the yard.
v_in( involve ) // Don't involve me in your family affairs!
v_in( Dredge ) // Dredge the chicken in flour before frying it.
v_in( publish ) // It wasn't published in a refereed journal.
v_in( chase ) // I chased the rabbits in the field
v_in( see ) // I saw myself in the mirror
v_in( meddle ) // Don't meddle in my affairs!
v_in( drag ) // Don't drag me into this business.
v_in( get )
v_in( roar ) // The rushing wind roared in our ears
v_in( run ) // I am running in the field
v_in( find ) // One of the most toxic substances is found in this place
v_in( execute ) // all orders are executed in succession
v_in( assemble ) // At nine o'clock, we all assembled in the hall
v_in( place ) // George and I were placed in the same class.
v_in( gather ) // A large number of people gathered in the square.
v_in( sing ) // The bird is singing in the tree
v_in( work ) // Mary does not work in an office
v_in( sink ) // The ship sank in the great storm
v_in( destroy ) // The car was totally destroyed in the crash
//v_in( be ) // These writers were in fashion at the beginning of the century.
v_in( play ) // The boys are playing in the field
v_in( bake ) // It had been baked in a big oven
v_in( fix ) // This issue has been fixed in the source repository.
v_in( swim ) // Richard and Henry swam in the river
v_in( print ) // This book was printed in London
v_in( listen ) // The audience listened in breathless silence to the singer
v_in( stand ) // They stood in the rain for an hour
v_in( meet ) // Meet me in the same place
v_in( keep ) // The teacher knew how to keep the class in line.
v_in( outmaneuver ) // My new supervisor knows how to outmaneuver the boss in most situations.
v_in( hammer ) // Hammer the nails in well
v_in( dig ) // He's been digging in the garden all morning
v_in( teach ) // The teacher is teaching in this school now
v_in( hang ) // The astronaut hung weightlessly in the capsule
v_in( water ) // You should water them every day in dry weather
v_in( sit ) // She sat in the corner

// --------------------------------------------------------------------------------

// Очень немногие глаголы допускают связывание с предлогом of, в частности
// распространенный оборот make of smth.

#define v_of(v) \
#begin
fact eng_v_prep_score
{
 if context { eng_verb:v{} eng_prep:of{} }
  then return 2
}
#end

v_of( make )
v_of( dream ) // He never dreamed of such beauty.
v_of( tire ) // He never tires of playing that video.
v_of( apprise ) // She was duly apprised of the raise.
v_of( acquit ) // he was acquitted of murder

// ----------------------------------------------------------------------------------

#define v_to(v) \
#begin
fact eng_v_prep_score
{
 if context { eng_verb:v{} eng_prep:to{} }
  then return 2
}
#end

v_to(march) // Protagonists march to the Danube.
v_to( slide ) // He slid the money over to the other gambler.
v_to( step ) // Young people should step to the fore and help their peers.
v_to( remove ) // He removed his children to the countryside.
v_to( bring ) // This brings me to the main point.
v_to( adjust ) // We must adjust to the bad economic situation.
v_to( supply ) // Solutions to many of the other exercises will be supplied to instructors.
v_to( redirect ) // Redirect your attention to the danger from the fundamentalists.
v_to( warm ) // He warmed to the idea of a trip to Antarctica.
v_to( give )
v_to( move ) // After moving back to America
v_to( run )
v_to( express ) // Finally I would like to express my debt to my personal heroes.
v_to( incline ) // She inclined her head to the student.
v_to( pull ) // Pull one's horse to a stand.
v_to( climb ) // The path climbed all the way to the top of the hill.
v_to( veer ) // The motorbike veered to the right.
v_to( flock ) // Tourists flocked to the shrine where the statue was said to have shed tears.
v_to( transfer ) // Transfer the packet from his trouser pockets to a pocket in his jacket.
v_to( show ) // The usher showed us to our seats.
v_to( conduct ) // He conducted us to the palace.
v_to( lead ) // We lead him to our chief.
v_to( jam ) // The driver jammed the brake pedal to the floor.
v_to( sink ) // He sank to his knees.
v_to( plunge ) // It plunged to the bottom of the well.
v_to( ascend ) // She ascended from a life of poverty to one of great.
v_to( bubble ) // Bubble to the surface.
v_to( bounce ) // He bounced to his feet.
v_to( divert ) // Divert the low voltage to the engine cylinders.
v_to( stick ) // Roughen the surfaces so they will stick to each other.
v_to( fasten ) // They fastened various nicknames to each other.
v_to( play ) // She is playing up to the chairman.
v_to( bus ) // The children were bussed to school.
v_to( train ) // She trained to Hamburg.
v_to( drive ) // We drove to the university every morning.
v_to( totter ) // The drunk man tottered over to our table.
v_to( beat ) // She beat the dealer down to a much better price.
v_to( lurch ) // The ship suddenly lurched to the left.
v_to( repair ) // He repaired to his cabin in the woods.
v_to( read ) // I must read to the end of the story because I want to see who gets the treasure
v_to( appeal ) // The idea of a vacation appeals to me.
v_to( endear ) // This behavior endeared her to me.
v_to( commend ) // His paintings commend him to the artistic world.
v_to( wire ) // The columns were wired to the beams for support.
v_to( hitch ) // Hitch the trailer to the car.
v_to( mean ) // Stardom meant nothing to her.
v_to( attract ) // He was magnetically attracted to her.
v_to( explain ) // This cannot be airily explained to your children.
v_to( translate ) //  He was translated bodily to heaven.
v_to( oppose ) // We are absolutely opposed to the idea.
v_to( tie ) // These big jets are tied to large airports.
v_to( sensitize ) // He was not sensitized to her emotional needs.
v_to( reduce ) // Reduce a problem to a single question.
v_to( peg ) // The weak currency was pegged to the US Dollar.
v_to( redound ) // Everything redounded to his glory.
v_to( fall ) // His voice fell to a whisper.
v_to( cling ) // The child clung desperately to her mother.
v_to( flow ) // The river flows northeastward to the gulf.
v_to( submit ) // He submitted impassively to his arrest.
v_to( migrate ) // They migrated eastward to Sweden.
v_to( apply ) // I applied my attention prosaically to my routine.
v_to( reply ) // He had replied insolently to his superiors.
v_to( refer ) // He referred opaquely to her recent past.
v_to( ship ) // Crate the paintings before shipping them to the museum.
v_to( help ) // (???) Richard helped himself to the cakes
v_to( take ) // We can't take animals to school
v_to( write ) // He writes to you often
v_to( speed ) // We are speeding on our way to Paris
v_to( say ) // I have not said anything to anybody about you.
v_to( go ) // I am going to the store.
v_to( send ) // A battleship is being sent to the war area
v_to( walk ) // I shan't be walking to school
v_to( come ) // A car came to our door
v_to( travel ) // We travel to London
v_to( listen ) // We listen to the music
v_to( turn ) // He turned to the right.
v_to( talk ) // You don't even talk to me
v_to( return ) // Therefore, they return to the classroom
v_to( belong ) //  The boy thought that all toys belong to him
v_to( invite ) // Mary has invited us to tea
v_to( fly ) // This plane does not fly to London
v_to( ride ) // We rode to school on our bicycles
v_to( fix ) // Let's fix the picture to the frame.
v_to( add ) // Let's add on to this.
v_to( get ) // Let's get down to basics.
v_to( attribute ) //  These statements were faultily attributed to me.

//v_to( lie{ OMONYM_RESOLUTION:1 }, //  The Sudan lies to the south of Egypt
//v_to( lie{ OMONYM_RESOLUTION:2 }, //  She found that he had lied to her.

// ---------------------------------------------------------------------------


#define v_with(v) \
#begin
fact eng_v_prep_score
{
 if context { eng_verb:v{} eng_prep:with{} }
  then return 2
}
#end
v_with(eat) // It is often eaten with pork crackling.
v_with(bind) // Thymine binds only with adenine;
v_with( toy ) // Toy with an idea.
v_with( run ) // I run with my dog
v_with( come ) // He came with them
v_with( fight ) // The soldiers fought with great courage
v_with( sympathise ) // We sympathise with you.
v_with( well ) // Her eyes welled with tears.
v_with( swim ) // These fish swim with a saltating motion.
v_with( commute ) // These operators commute with each other.
v_with( pelt ) // They pelted each other with snowballs.
v_with( grapple ) // The two men grappled with each other for several minutes.
v_with( draw ) // John is drawing with a pencil.
v_with( meet ) // I can't meet with you today.
v_with( pulsate ) // The city pulsated with music and excitement.
v_with( wobble ) // His voice wobbled with restrained emotion.
v_with( re-enter ) // You cannot re-enter the country with this visa.
v_with( panel ) // Panel the walls with wood.
v_with( color ) // Color the walls with paint in warm tones.
v_with( radiate ) // Her face radiated with happiness.
v_with( beam ) // She was beaming with joy.
v_with( die ) // I was dying with embarrassment when my little lie was discovered.
v_with( cloud ) // Their faces were clouded with sadness.
v_with( zap ) // This show zaps the viewers with some shocking scenes.
v_with( sizzle ) // She was sizzling with anger.
v_with( seethe ) // The customer was seething with anger.
v_with( charge ) // The speaker charged up the crowd with his inflammatory remarks.
v_with( strike ) // This writer strikes a chord with young women.
v_with( render ) // The face of the child is rendered with much tenderness in this painting.
v_with( write ) // Russian is written with the Cyrillic alphabet.
v_with( interlude ) // The guitar player interluded with a beautiful improvisation.
v_with( lace ) // The halo itself is laced with faint, narrow structures.
v_with( button ) // He cannot button his shirt with his slinged arm.
v_with( tamper ) // The machine will self-destruct if you tamper with it.
v_with( suffocate ) // The child suffocated herself with a plastic bag that the parents had left on the floor.
v_with( retrofit ) // The mansion was retrofitted with modern plumbing.
v_with( spatter ) // The baby spattered the bib with food.
v_with( speckle ) // Speckle the wall with tiny yellow spots.
v_with( grain ) // His hands were grained with dirt.
v_with( speak ) // He spoke with blithe ignorance of the true situation.
v_with( fill ) // The airport was filled with stormbound passengers.
v_with( discontent ) // He was discontented with his position.
v_with( dust ) // Everything was dusted over with a fine layer of soot.
v_with( cover ) // The wallpaper was covered all over with flowers.
v_with( supply ) // They were abundantly supplied with food.
v_with( please ) // His father was well pleased with his grades.
v_with( clog ) // The story was clogged with too many details.
v_with( satisfy ) // We are entirely satisfied with the meal.
v_with( overgrow ) // The patio overgrew with ivy.
v_with( improve ) // The editor improved the manuscript with his changes.
v_with( correlate ) // Urbanization in Spain is distinctly correlated with a fall in reproductive rate.
v_with( visit ) // He was visited with a terrible illness that killed him quickly.
v_with( defoliate ) // Defoliate the trees with pesticides.
v_with( act ) // He acted with the best of motives.
v_with( talk ) // He talked short with everyone.
v_with( bend ) // He was bent double with pain.
v_with( bore ) // The housewife bored us with her domestically limited conversation.
v_with( deal ) // He dealt proficiently with the problem.
v_with( decorate ) // The temple was garishly decorated with bright plastic flowers.
v_with( obsess ) // I am maniacally obsessed with jealousy.
v_with( endow ) // The area is slenderly endowed with natural resources.
v_with( flood ) // The reactor meltdown was avoided by flooding it with water and boric acid
v_with( play ) // I will play the games with you
v_with( shower ) // He showered her with caresses.
v_with( teem ) // The oceans are teeming with life.
v_with( help ) // He helped us with this exercise
v_with( hold ) // He held the book with this 
v_with( burn ) // I have burnt myself with the fireworks
v_with( fiddle ) // Don't fiddle with the screws.
v_with( dance ) // I do not dance with her
v_with( go ) // Those bolts go with these parts.
v_with( walk ) // They are walking with their son
v_with( work ) // He is currently working with new data
v_with( stay ) // The children are staying with their uncle and aunt
v_with( start ) // They started with us last year
v_with( live ) // I live with animals in a house
v_with( avoid ) // The reactor meltdown was avoided by flooding it with water and boric acid
v_with( sit ) // I sit with book in a chair
v_with( cut )   // He cut the string with his penknife.

