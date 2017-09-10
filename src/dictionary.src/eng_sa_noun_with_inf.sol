pattern NounWithRightAdjunct
{
 n=NounGrpWithoutArticle0{ ENG_MODAL_NOUN }:export{ node:root_node NUMBER }
 inf=InfinitiveAction
} : links { n.<INFINITIVE>inf }
  : ngrams { 1 }


pattern NounWithRightAdjunct
{
 n1=NounGrpWithoutArticle0{ ENG_MODAL_NOUN }:export{ node:root_node NUMBER }
 prep=eng_prep:*{ noun_prep( n1.root_node, _ ) }
 n2=NounGroup
 inf=InfinitiveAction
} : links { n1.{
                <OBJECT>prep.<NEXT_COLLOCATION_ITEM>n2
                <INFINITIVE>inf
               } }
  : ngrams { 1 }

