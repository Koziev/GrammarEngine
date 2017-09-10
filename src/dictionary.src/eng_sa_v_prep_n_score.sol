// Сочетаемость глагола и предложного дополнения (3-граммы)
facts eng_v_prep_n_score language=English
{
 arity=3
 return=integer
}

#define x(v,p,n,w) \
#begin
fact eng_v_prep_n_score
{
 if context { eng_verb:v{} eng_prep:p{} eng_noun:n{} }
  then return w
}
#end

x( name, in, honor, 5 ) // The disease is named in his honor.
x( stay, at, home, 5 ) // He is going to stay at home
x( travel, by, bus, 5 ) // We travelled from Rome to Naples by bus.
x(write,in,script,5) // Breton is written in the Latin script.
x(evolve,over,time,5) // Production of these machines evolved over time.
x(expose,to,air,5) // Lanthanum oxidizes rapidly when exposed to air.
x(begin,in,batch,5) // The migration began in batches.
x(record,on,camera,5) // Some protestors record patients on camera.
x(resemble,in,appearance,5) // Salamanders resemble lizards in appearance;
x(enter,into,force,5) // Lisbon Treaty entered into force.
x(quibble,over,word,5) // Let's not quibble over words.
x(work,in,team,5) // Researchers work in teams to make cars more fuel efficient.
x(fall,in,love,5)
