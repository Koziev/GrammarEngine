// Для оценки левого дополнения существительного:
// 

facts eng_noun_noun_score language=English
{
 arity=2
 return=integer
}

#define nn(n1,n2,w) \
#begin
fact eng_noun_noun_score
{
 if context { eng_noun:n1{} eng_noun:n2{} }
  then return w
}
#end

nn( water, droplet, 6 )
nn( jet, stream, 6 )
nn( weather, pattern, 6 )
nn( surface, wind, 6 )
nn( life, cycle, 6 )
nn( saltwater, lake, 6 )
nn( body, system, 6 )
nn( Gas, bubble, 6 )
nn( water, vapor, 6 )
nn( control, group, 6 )
nn( phone, call, 5 ) // Make a phone call.
nn( night, air, 6 ) // The raw and fresh damp of night air.
nn( blood, vessel, 5 )
nn( Sound, wave, 5 )
nn( asteroid, belt, 5 )
nn( metal, spoon, 5 )
nn( feedback, mechanism, 5 )
nn( star, cluster, 5 )
nn( sand, dune, 5 )
nn( vitamin, deficiency, 5 )
nn( oak, tree, 5 )
nn( bone, tissue, 5 )
nn( water, depth, 5 )
nn( water, clarity, 5 )
nn( water, salinity, 5 )
nn( water, temperature, 5 )
nn( ground, tissue, 5 )
nn( forest, ecosystem, 5 )
nn( Soil, erosion, 5 )
nn( forest, fire, 5 )
nn( convection, current, 5 )
nn( soil, erosion, 5 )
nn( water, pollution, 5 )
nn( wildlife, extinction, 5 )
nn( air, pollution, 5 )
nn( wolf, pack, 5 ) // A wolf pack howls to warn other wolves to stay away.
nn( light, year, 5 )
nn( South, Pole, 5 )
nn(mass, extinction, 5 )
nn(fault, zone, 5 )
nn(strep, throat, 5 )
nn( pivot, joint, 5 )
nn( gene, expression, 5 )
nn( pie, chart, 5 )
nn( line, graph, 5 )
nn( hinge, joint, 5 )
nn( human, diet, 5 )
nn( gas, state, 5 )
nn( bone, cell, 5 )
nn( skin, cell, 5 )
nn( blood, cell, 5 )
nn( nerve, cell, 5 )
nn( water, droplet, 5 )
nn( cell, membrane, 5 )
nn( model, rocket, 5 )
nn( gas, state, 5 )
nn( copper, sphere, 5 )
nn( Temperature, inversion, 5 )
nn( water, vapor, 5 )
nn( evaporation, rate, 5 )
nn(acceleration, force,5)
nn( mountain, range, 5 )
nn( sea,level, 5 )
nn( tennis, ball, 5 )
nn( reflection, image, 5 )
nn( refraction, image, 5 )
nn( gas, emission, 5 )
nn( gas, mileage, 5 )
nn( water, bottle, 5 )
nn( hay, fever, 5 )
nn( human, eye, 5 )
nn( dance, partner, 5 )
nn( dress, code, 5 ) // The requirement for such dress codes differ.
nn( mutation, rate, 5 )
nn( research, topic, 5 )
nn( Asteroid, Explosion, 5 )
nn( asteroid, impact, 5 )
nn( stimulation, feedback, 5 )
nn(Vietnam,War,5) // The song lampoons the Vietnam War draft.
nn(oil,extraction,5) // Oil extraction facilities were nationalized.
nn(alcohol,distribution,5) // Alberta also privatized alcohol distribution.
nn(heart,rate,5)
nn(respiration,rate,5)
nn(human,body,2)
nn(tissue,level,2)
nn(organ,level,2)
nn(system,level,2)
nn(cellular,level,2)
nn(golf,ball,2)
nn(water,cycle,2)
nn(sugar,level,2)
nn(blood,flow,2) // increase blood flow to the skin.
nn(pesticide,resistance,2)
nn(color,vision,2)
nn(Battle,dress,5)
nn(Prime,number,5)
nn(Greenhouse,gas,5)
nn(Bermudan,beach,5)
nn(Bahraini,beach,5)
nn(Antiguan,island,5)
nn(Mineral,deposit,5)
nn(Digestive,juice,5)
nn("New York",City,5)
nn(surface,water,3)
nn(silk,tie,6)




// В паттерне "the animal types" поощряем трактовку "types" как существительного, модифицируемого словом "data"
nn( animal, type, 1 )

nn( datum, type, 5 )
nn(radio,station,2) // ASU has two radio stations.
nn(battle,dress,5) // Battle dress
nn(industry,standard,5) // This became the industry standard.
nn(mission,control,5) //  On Earth, Mission Control continued to wait.
nn(space,travel,5) // The thrills of space travel
nn(child,character,5) // the young child's character

nn(control,group,6)
nn(climate,condition,6)
nn(river,sediment,6)
nn(carbonate,mineral,6)
nn(vapor,pressure,6)
nn(land,feature,6)
nn(weather,observation,6)
nn( weather, report, 5 )
nn( ocean, salinity, 5 )
nn(school,building,6)
nn(glass,window,6)
nn(bronze,statue,6)
nn(aluminum,can,6)
nn(fiberglass,bumper,6)
nn(school,district,6)
nn(hand,sanitizer,6)
nn(aluminum, foil,6)
nn(moon, gravity,6)
nn(research, lab,6)
nn(drug, company,6)
nn(selection, pressure,6)
nn(copper, wire,6)
nn(steel, tubing,6)
nn(food, supply,6)
nn(carbon, dioxide,6)
nn(lever, system,6)
nn(human, stomach,6)
nn(life, function,6)
nn(pastor,call,6) // The pastor's calls on his parishioners
nn(heat, transfer,6)
nn(fossil, record,6)
nn(science, teacher,6)
nn(air, resistance,6)
nn(harm, environment,6)
nn(time, period,6)
nn(animal, life,6)
nn(class,struggle,6) // National independence takes priority over class struggle.
nn( Doppler, effect, 5 )
nn( tomato, plant, 5 )
nn( corn, plant, 5 )
nn( safety, equipment, 5 )
nn( Coal, combustion, 5 )
nn( electron, microscope, 5 )
nn( body, structure, 5 )
nn( Earth, core, 5 )
nn( Earth, crust, 5 )
nn( space, object, 5 )
nn( pole, reversal, 5 )
nn( ceiling, fan, 5 )
nn( radio, telescope, 5 )
nn( wind, turbine, 5 )
nn( heat, transfer, 5 )
nn( time, period, 5 )
nn( galaxy, shape, 5 )
nn( tissue, decomposition, 5 )
