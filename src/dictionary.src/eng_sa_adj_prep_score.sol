// Сочетаемость прилагательного и предлога (без учета объекта у предлога)
facts eng_adj_prep_score language=English
{
 arity=2
 return=integer
}

#define ap(a,p,w) \
#begin
fact eng_adj_prep_score
{
 if context { eng_adjective:a{} eng_prep:p{} }
  then return w
}
#end

ap(available,for,5)
ap(resistant,to,5) // Some of the insects survived and produced offspring that were also resistant to the insecticide.
ap(different,from,5)
ap(identical,to,5)
ap(important,to,5) // Birds are often important to island ecology.
ap(beneficial,to,2) // Traits associated with this gene are beneficial to the species.
ap(independent,of,2) // This step is entirely independent of microbes.