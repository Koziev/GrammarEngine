// Сочетаемость глагола и прямого дополнения
facts eng_v_obj_score language=English
{
 arity=2
 return=integer
}

#define vo(v,o,w) \
#begin
fact eng_v_obj_score
{
 if context { eng_verb:v{} eng_noun:o{} }
  then return w
}
#end

vo( increase, control, 5 ) // He gradually increased his control over Valencia;
vo( provide, subsidy, 5 ) // The government plans to continue providing subsidies.
vo( speak, English, 2 ) // Can he speak English?
vo( read, chapter, 5 ) // He read a chapter every night before falling asleep.
vo( clean, floor, 5 ) // Is there a tool for cleaning the floor?
vo( beat, wing, 5 ) // The eagle beat its wings and soared high into the sky.
vo( save, money, 5 ) // I'm saving money toward retirement
vo( solve, equation, 5 ) // These texts deal with solving algebraic equations.
vo( feel, dislike, 5 ) // I felt a violent dislike.
vo( melt, rock, 5 )
vo( emulsify, fat, 5 )
vo( measure, temperature, 5 )
vo( propose, theory, 5 )
vo( sustain, agriculture, 5 )
vo( store, energy, 5 )
vo( reduce, loss, 5 )
vo( generate, energy, 5 )
vo( eat, food, 5 )
vo( generate, friction, 5 )
vo( undergo, mutation, 5 )
vo( gain, advantage, 5 )
vo( lack, water, 5 )
vo( contain, pollutant, 5 )
vo( dissolve, soil, 5 )
vo( find, evidence, 5 )
vo( pull, sweater, 5 )
vo( harm, environment, 5 )
vo( change, content, 5 )
vo( make, noise, 5 )
vo( Perform, trial, 5 )
vo( run, distance, 5 )
vo( measure, time, 5 )
vo( cause, difference, 5 )
vo( experience, increase, 5 )
vo( experience, decrease, 5 )
vo( reject, proposal, 5 ) // Flemish politicians have strongly rejected these proposals.
vo( interpret, dream, 5 ) // Daniel is summoned and interprets the dream.
vo( absorb, water, 5 ) // The sponge absorbs water well.
vo( complete, homework, 5 ) // Before bed-time Margaret will have completed her homework
vo( determine, role, 5 )
vo( make, observation, 5 )
vo( give, birth, 5 ) // A female opossum can give birth to 5-15 offspring.
vo( reverse, direction, 5 )
vo( change, speed, 5 )
vo( increase, energy, 2 )
vo( display, datum, 5 )
vo( provide, source, 5 )
vo( add, fertilizer, 5 )
vo( measure, humidity, 5 )
vo( replenish, nitrogen, 5 )
vo( slow, flow, 5 )
vo( transport, nutrient, 5 )
vo( remove, waste, 5 )
vo( relay, message, 5 )
vo( validate, claim, 5 )
vo( give, feedback, 5 )
vo( set, goal, 5 )
vo( generate, output, 5 )
vo( design, process, 5 )
vo(analyze,result,5)
vo(validate,result,5)
vo(increase,validity,5)
vo(gather,datum,5)
vo(organize,information,5)
vo(collect,information,5)
vo(lose,effectiveness,5)
vo(eliminate,insect,2)
vo(declare,law,2) // Banks posted guards and declared martial law.
vo(decrease,flow,2) // decrease blood flow to the skin.
vo(increase,flow,2) // increase blood flow to the skin.
vo(smell,air,5) // smelling the air for odors
vo(cut,string,5)
vo(take,turn,5) // Players take turns to cut a string.
vo(affect,trait,5)
vo(tense,rope,5) // Tense the rope manually before tensing the spring.
vo(wave,flag,5) // The guard blows his whistle and waves his flag
vo(undergo,fusion,6)
vo(do,job,5) // Please do your job properly!
vo(play,piano,5) // I heard Mary play the piano.
vo( win, game, 5 ) // I am going to win this game
vo( wipe, windscreen, 5 ) // Wipe the windscreen clear.
vo(find,job,2) // Illusive hopes of finding a better job.
vo(mature,fast,2) // He matured fast.
vo(list,eye,2) // Lift one's eyes.
vo(travel,far,2) // He traveled far.
vo(repair,shoe,2) // Repair my shoes
vo(share,idea,2)
vo(complete,work,5)
vo(describe,principle,5)
vo(coordinate,function,2)
vo(smell,air,2) // smelling the air for odors
vo(produce,offspring,2)
vo(describe,behaviour,2) // Which example describes a learned behavior in a dog?
vo(lose,sight,1) // The child strayed from the path and her parents lost sight of her.
vo(have,duty,1) // Do corporations have duties?
vo(reach,level,5) // Organization has reached global level.
vo(demand,money,5) // Aglaulus demands money in exchange.
vo(dig,salt,5) // Dig salt.
vo(dig,crystal,5) // How to Dig Crystals on the Oklahoma Salt Plains.
vo(commit,injury,5) // To commit a violent injury;
vo(need,help,5) // You need help
vo(need,rest,5) // I need a rest.
vo(make,sense,5) // It makes sense
vo(take,money,5) // Allen denied taking any money;
vo(receive,preference,5) // Boys receive preference in schooling;

vo(collect,stamp,5) // I am interested in collecting stamps
vo(disperse,light,5) // The prism disperses light.
vo(plaster,warning,5) // She plastered warnings all over the wall.
vo(play,football,5)
vo(declare,victory,5) // His principal opponent unblushingly declared victory before the ballots had been counted.
vo(diffract,electron,5 ) // Laser light diffracts electrons.
vo(pour,water,5) // Pour water over the floor.
vo(love,sailing,5) // I love sailing
vo(trot,horse,5) // She trotted the horse home.

vo( irrigate, crop, 5 )
vo( check, accuracy, 5 )
vo( provide, information, 5 )
vo( write, report, 5 )
vo( release, hormone, 5 )
vo( maintain, equilibrium, 5 )
vo( maintain, level, 5 )
vo(provide, energy, 5 )
vo(draw, conclusion, 5 )
vo( make, conclusion, 5 )
vo(absorb, moisture, 5 )
vo(release, energy, 5 )
vo(carry, message, 5 )
vo(assemble, protein, 5 )
vo(dissolve, nutrient, 5 )
vo(absorb, sunlight, 5 )
vo(face, extinction, 5 )
vo(make, contact, 5 )
vo(release, oxygen, 5 )
vo(support, body, 5 )
vo(publish, result, 5 )
vo(change, direction, 5 )
vo(collect, water, 5 )
vo(absorb, oxygen, 5 )
vo(give, access, 5 )
vo(absorb, radiation, 5 )
vo(divide, work, 5 )
vo(establish, territory, 5 )
vo(discover, law, 5 )
vo(leave, hive, 5 )
vo(collect, nectar, 5 )
vo(retain, volume, 5 )
vo(conduct, message, 5 )
vo(perform, function, 5 )
vo(add, pressure, 5 ) // Its volume can be greatly reduced by adding pressure.
vo(increase, temperature, 5 )
vo(play, role, 5 )
vo(prevent, weathering, 5 )
vo(prevent, erosion, 5 )
vo(pollinate, flower, 5 )
vo(demonstrate, professionalism, 5 )
vo(rack,brain,5) // Rack one's brain
vo( buy, food, 5 ) // I buy food wholesale.
vo( form, glucose, 5 )
vo( do, work, 5 )
vo( perform, function, 5 )
vo( produce, drug, 5 )
vo( conduct, investigation, 5 )
vo( improve, accuracy, 5 )
vo(take,priority,5) // National independence takes priority over class struggle.
vo(take,place,6) // But this need not always take place.
vo( produce, electricity, 5 )
vo( transpire, water, 5 )
