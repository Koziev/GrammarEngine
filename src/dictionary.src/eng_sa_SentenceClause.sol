// Группа V_Clause объединяет паттерны с моделями S-V и S-V-O

pattern SentenceClause { V_Clause : export { node:root_node } }

			  
// ------------------------
// A is faster than B
// ------------------------

patterns SecondComparisonArg export { node:root_node }
pattern SecondComparisonArg { DirectObj:export { node:root_node } }
pattern SecondComparisonArg { eng_noun:*{ noun_form:basic }:export { node:root_node } }

patterns SecondComparisonArgPl export { node:root_node }
pattern SecondComparisonArgPl { eng_adjective:these{}:export { node:root_node } }
pattern SecondComparisonArgPl { eng_adjective:those{}:export { node:root_node } }

patterns SecondComparisonArgSg export { node:root_node }

// This book is cheaper than that one
pattern SecondComparisonArgSg
{
 a=eng_adjective:that{}
 n=eng_numeral:one{}:export { node:root_node }
} : links { n.<ATTRIBUTE>a }

// That book is cheaper that that one
pattern SecondComparisonArgSg
{
 a=eng_adjective:this{}
 n=eng_numeral:one{}:export { node:root_node }
} : links { n.<ATTRIBUTE>a }


/*
// I am faster than that boy
pattern SentenceClause
{
 sbj=Sbj_Singular
 v=Copula_Present_1st_Singular:export{ node:root_node }
 x=AdjComparative
 conj='than'
 y=SecondComparisonArg
} : links {
           v.{
              <SUBJECT>sbj
              <RHEMA>x.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>y
             }
          }

// This book is bigger than that one
pattern SentenceClause
{
 sbj=Sbj_Singular
 v=Copula_Present_1st_Singular:export{ node:root_node }
 x=AdjComparative
 conj='than'
 y=SecondComparisonArgSg
} : links {
           v.{
              <SUBJECT>sbj
              <RHEMA>x.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>y
             }
          }
          
// This student is smarter than that one           
pattern SentenceClause
{
 sbj=Sbj_3st_Singular
 v=Copula_Present_3st_Singular:export{ node:root_node }
 x=AdjComparative
 conj='than'
 y=SecondComparisonArg
} : links {
           v.{
              <SUBJECT>sbj
              <RHEMA>x.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>y
             }
          }

// These runners are much faster that those sportsmen
pattern SentenceClause
{
 sbj=Sbj_Plural
 v=Copula_Present_Plural:export{ node:root_node }
 x=AdjComparative
 conj='than'
 y=SecondComparisonArg
} : links {
           v.{
              <SUBJECT>sbj
              <RHEMA>x.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>y
             }
          }

// These runners are much faster that those
pattern SentenceClause
{
 sbj=Sbj_Plural
 v=Copula_Present_Plural:export{ node:root_node }
 x=AdjComparative
 conj='than'
 y=SecondComparisonArgPl
} : links {
           v.{
              <SUBJECT>sbj
              <RHEMA>x.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>y
             }
          }
*/


// It is possible for some type of arithmetic computations to produce an invalid result
pattern SentenceClause
{
 s1=eng_pronoun:I{ person:3 number:single case:nominative }
 v1='is':export{ node:root_node }
 a1=eng_adjective:possible{}
 prep=eng_prep:for{}
 n=SingularNounSbj //NounGroup
 inf=InfinitiveAction
} : links {
           v1.{
               <SUBJECT>s1
               <ATTRIBUTE>a1.<NEXT_COLLOCATION_ITEM>prep.<OBJECT>n.<ATTRIBUTE>inf
              }
          }


// It is possible for the computations to produce an invalid result that exceeds the range of the data type involved in the computation
pattern SentenceClause
{
 s1=eng_pronoun:I{ person:3 number:single case:nominative }
 v1='is':export{ node:root_node }
 a1=eng_adjective:possible{}
 prep=eng_prep:for{}
 n=PluralNounSbj
 inf=InfinitiveAction
} : links {
           v1.{
               <SUBJECT>s1
               <ATTRIBUTE>a1.<NEXT_COLLOCATION_ITEM>prep.<OBJECT>n.<ATTRIBUTE>inf
              }
          }


			  