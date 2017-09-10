// Adjectives with prepositional+N.P. complementations

facts adj_prep language=English
{
 arity=2
 return=boolean
 generic
}

#define ap(a,p) fact adj_prep { if context { eng_adjective:a{} eng_prep:p{} } then return true }

ap( far, from ) // EISA's success was far from guaranteed.
ap( comparable, to ) // It is comparable in size to Ukraine.
ap( opposite, to ) // This is "opposite" to abelian.
ap( vulnerable, to ) // Children are especially vulnerable to atropine poisoning.
ap( prone, to ) // Mingus was prone to clinical depression.
ap( reminiscent, of ) // Some early works are reminiscent of Manet.
ap( passionate, about ) // Hofstadter is passionate about languages.
ap( unique, within ) // Numbers are unique only within one state.
ap( vital, to )
ap( responsible, for )
ap(undecided,on) // Einstein was still undecided on his future.
ap(identical,to)
ap(susceptible,to) // The mountain range will make the area susceptible to earthquakes.
ap(ablaze,with)
ap(absent,from)
ap(accustomed,to)
//--ap(ahead,of)
ap(amazed,at)
ap(amused,at)
ap(amused,with)
ap(angry,with)
ap(angry,about)
ap(annoyed,with)
ap(annoyed,about)
ap(answerable,to)
ap(answerable,for)
ap(anxious,about)
ap(ashamed,of)
ap(astonished,at)
ap(attentive,to)
ap(averse,to)
ap(aware,of)
ap(afraid,of) // The girls were afraid of the bull
ap(ambitious,for) // On the other hand, she is too ambitious for her own good.
ap(available,for) // There is also space available for campers.

//ap(big,for) // That hat is too big for you
ap(bad,at)
ap(bad,for)
ap(blind,to)
ap(bound,for)
ap(brilliant,at)
ap(busy,with)
ap(beneficial,for)


ap(capable,of)
ap(careful,of)
ap(careful,with)
ap(careless,of)
ap(careless,with)
ap(certain,of)
ap(certain,about)
ap(clear,about)
ap(clear,of)
ap(clever,at)
ap(clever,with)
ap(close,by)
ap(concerned,about)
ap(concerned,in)
ap(concerned,with)
ap(confident,of)
ap(confident,in)
ap(conscious,of)
ap(content,with)
ap(contented,with)
ap(contrary,to)
ap(convenient,for)
ap(crazy,about)
ap(critical,of)
ap(cruel,to)
ap(curious,about)
ap(close,to) // The house is close to the station.
ap(conscious,of) // She is conscious of his faults.
ap(crucial,to) // It is crucial to the case.

ap(dangerous,for) // A leeward tide is dangerous for small boats.
ap(difficult,for)
ap(different,from) // It was completely different from what we expected.
ap(deaf,to)
ap(dear,to)
ap(delighted,with)
ap(delighted,at)
ap(dependent,on)
ap(determined,on)
ap(disappointed,with)
ap(disgusted,with)
ap(doubtful,about)
ap(due,to)
ap(due,for)

ap(enough,for) // There isn't enough for all of us
ap(eager,for)
ap(easy,about)
ap(easy,on)
ap(envious,of)
ap(equal,to)
ap(essential,to)
ap(evident,to)
ap(excited,about)
ap(experienced,in)
ap(expert,at)

ap(furious,with) // Japan's prime minister was furious with executives at a power company
ap(fluent,in) // She was enviably fluent in French.
ap(full,of) // My pocket is full of apples
ap(faithful,to)
ap(familiar,with)
ap(familiar,to)
ap(famous,for)
ap(fit,for)
ap(fond,of)
ap(free,for)
ap(furious,about)
ap(fussy,about) // He was particularly fussy about spelling.

ap(generous,to)
ap(generous,with)
ap(gentle,with)
ap(glad,about)
ap(glad,of)
ap(good,at)
ap(good,to)
ap(good,for)

ap(grateful,to)
ap(grateful,for)
ap(guilty,of)
ap(guilty,to) // Berkman pleaded not guilty to all charges.


ap(happy,about)
ap(hard,for)
ap(hard,on)
ap(harmful,to)
ap(harmful,for)
ap(hesitant,about)
ap(honest,about)
ap(hopeful,about)
ap(hopeful,of)
ap(hopeless,at)
ap(hungry,for)

ap(inconsistent,with) // It is inconsistent with the roadmap.
ap(ignorant,of)
ap(important,for)
ap(important,to) // Birds are often important to island ecology.
ap(independent,of)
ap(inferior,to)
ap(intent,on)
ap(interested,in)
ap(indifferent,to) // Their love left them indifferent to their surroundings.

ap(jealous,of)

ap(keen,on)
ap(kind,to)

ap(late,for) // He is often late for school
ap(level,with)
ap(loyal,to)

ap(mad,about)
ap(mad,at) // Mary was mad at him.
ap(married,to)
ap(mistaken,about)
ap(mistaken,in)
ap(mature,for) // She is mature for her age.

ap(necessary,for)
ap(necessary,to) // Presumably boron is necessary to other mammals.
ap(new,to)

ap(obedient,to)
ap(obvious,to) // His delight to see her was obvious to all.

ap(pessimistic,about) // She was unduly pessimistic about her future.
ap(proud,of) // She was fiercely proud of her children.
ap(proportional,to) // The punishment ought to be proportional to the crime.
ap(patient,with)
ap(peculiar,to)
ap(pleased,with)
ap(positive,of)
ap(positive,about)
ap(prejudiced,against)
ap(prepared,for)
ap(proud,of)
ap(puzzled,about)

ap(qualified,for)

ap(ready,for) // The children are not ready for school
ap(regretful,for)
ap(ripe,for)
ap(rude,to)

ap(anterior,to) // The trachea is anterior to the brain.
ap(successful,in) // She was outstandingly successful in her profession.
ap(skeptical,of) // She is unassumingly skeptical of her own work.
ap(sorry,for) //  We are truly sorry for the inconvenience.
ap(sacred,to)
ap(sad,about)
ap(safe,from)
ap(satisfied,with)
ap(selfish,about)
ap(sensible,about)
ap(sensitive,about)
ap( sensitive, to ) // Lamps are also sensitive to switching cycles.
ap(separate,from)
ap(serious,about)
ap(severe,on)
ap(several,of) // The enemy landed several of our aircraft.
ap(shocked,at)
ap(shocked,by)
ap(sick,of)
ap(sick,with) // She was sick with longing.
ap(silly,about)
ap(similar,to)
ap(sincere,about)
ap(skilful,at)
ap(slow,at)
ap(sorry,about)
ap(strong,in)
ap(stupid,about)
ap(sufficient,for)
ap(suitable,for)
ap(superior,to)
ap(sure,of)
ap(sure,about)
ap(surprised,at)
ap(suspicious,of)

ap(thankful,to)
ap(thrilled,about)
ap(tired,of)
ap(true,to)

ap(unaware,of) // He was blissfully unaware of the danger.
ap(uncertain,of)
ap(uncertain,about)
ap(uneasy,about)
ap(unaffected,by) // They are entirely unaffected by each other's writings.
//--ap(used,to)
ap(useful,for)
ap(unresponsive,to) // He was unresponsive to her passionate advances.

ap(visible,to) // This planet is visible to the naked eye

ap(wrong,about)
ap(weak,in)
ap(well,to)
ap(wide,of)
ap(worried,about)
ap(worthy,of)
ap(wrong,about)
ap(resistant,to)
ap(independent,of) // This step is entirely independent of microbes.
ap(unrelated,to) // Johnston was unrelated to Confederate general Joseph E. Johnston.



fact adj_prep
{
 if context { * * }
  then return false,-5
}

