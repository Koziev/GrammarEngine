facts eng_adv_v_score language=English
{
 arity=2
 return=integer
}

#define av(m,a,w) \
#begin
fact eng_adv_v_score
{
 if context { eng_adverb:m{} eng_verb:a{} }
  then return w
}
#end

av( highly, specialize, 5 ) // Many contemporary composers specify highly specialized scordatura.
av( lukewarmly, receive, 5 ) // He was lukewarmly received by his relatives.
av( sedulously, forest, 5 ) // This illusion has been sedulously fostered.
av( temperately, state, 5 ) // These preferences are temperately stated.
av( unchangeably, fix, 5 ) // His views were unchangeably fixed.
av( asymmetrically, arrange, 5 ) // They were asymmetrically arranged.
av( empirically, test, 5 ) // This can be empirically tested.
av( barbarously, murder, 5 ) // They were barbarously murdered.
av( romantically, link, 5 ) // They were romantically linked.
av( maniacally, obsess, 5 ) // I am maniacally obsessed
av( Conically, shape, 5 )
av( sharply, define, 5 ) // The new style of Minoan pottery was sharply defined.
av( "no longer", use, 5 ) // Technically, the term is no longer used by experts.
av( unpleasantly, surprise, 5) // They had been unpleasantly surprised.
av( soon, begin, 2) // Soon things began looking up for Berkman.
av( almost, finish, 5 )
av( initially, locate, 5 ) // The Confederacy's capital was initially located at Montgomery.
av( greatly, appreciate, 5 ) // Feedback is greatly appreciated!
av( initially, limit, 5 )
av( well, know, 5 ) // She was well known as a hostess;
av( often, call, 5 ) // The latter is often called “field testing”.
av( badly, damage, 5 ) // They are badly damaged by souvenir seekers.
av( traditionally, write, 5 ) // It is traditionally written with embossed paper.
av( also, document, 5 ) // Bankruptcy is also documented in East Asia.
av( quickly, capture, 5 ) // The island was quickly captured.
av( never, solve, 5 ) // The crime was never solved.
av( never, compensate, 5 ) // The owners were never compensated.
av( partially, check, 5 ) // Simony had been partially checked.
av( weakly, attract, 5 )
av( properly, present, 5 )
av( quickly, become, 5 )
av( likely, take, 1 ) // His baptism likely took place at Canterbury.
av( severely,restrict,5) // Political freedoms are severely restricted in Burkina Faso.
av( extensively,quote,5) // He is extensively quoted on many topics.
av( sometimes, mention, 5 ) // English and American varieties are sometimes mentioned. 
av( well, describe, 5 ) // Which statement best describes a liquid sample?
av( unrecognizably, age, 5 ) // He had unrecognizably aged.
av( fully, understand, 5 ) // These effects are still not yet fully understood;
av( soon, emerge, 2 ) // A resistance movement soon emerged.
av( quickly, open,5) // She had quickly opened the door
av(totally,destroy,5) // The car was totally destroyed in the crash
av(far,outnumber,5) // The revolutionaries were far outnumbered.
av(elegantly,decorate,2) // The room was elegantly decorated.
av(sharply,question,2) // She was being sharply questioned.
av(fascinatingly,distort,2) // I become fascinatingly distorted.
av(obscurely,write,2) // This work is obscurely written.
av(visibly,display,2) // The sign was visibly displayed.
av(ornately,carve,2) // The cradle was ornately carved.
av(easily,recover,2) // Samples are also easily recovered.
av(electrically,power,2) // These are generally electrically powered.
av(commonly,use,2) // X-rays are most commonly used;
av(well,develop,2) // The ears are well developed in frogs.
av(explicitly,legislate,2) // Some conventions are explicitly legislated;
av(widely,share,2) // This sentiment was widely shared.
av(also,use,2) // Tamarind is also often used.
av(often,use,2) // Tamarind is also often used.
av(closely,mimic,5) // The resulting sound closely mimics numerous instruments.
av( well, receive, 5 ) // Its website has also been well received.



