// Различные конструкции, выступающие в роли вводной фразы с отбивкой запятой.

patterns ClauseOpener0 export { node:root_node }


// Please, stop this insanity.
// ^^^^^^^
pattern ClauseOpener0
{
 intro=eng_particle:please{}:export{node:root_node}
}




// Наречие с отбивкой запятой:
// Statistically, the study was almost worthless.
// ^^^^^^^^^^^^^
// More recently, synthetic materials were added.
// ^^^^^^^^^^^^^
pattern ClauseOpener0
{
 Adv0{ [-1]AdvAsOpener }:export{node:root_node}
}

// Произвольный союз:
// And all the rest is merely accidental.
// ^^^
pattern ClauseOpener0
{
 eng_conj:*{}:export{node:root_node}
} : ngrams { -1 }




// Yes, she learned all by herself
pattern ClauseOpener0
{
 eng_particle:yes{}:export{node:root_node}
}


// No, she did learn all by herself
pattern ClauseOpener0
{
 eng_particle:no{}:export{node:root_node}
}


// ---------------

collocation_set ClauseOpenerCollocation =
{
 { First },
 { Of course },
 { But , in general },
 { Thus },
 { As shown here },
 { Also },
// { Therefore },
 { As you known },
// { Futhermore },
 { Should this be the case }, // Should this be the case, I will let you know soon.
 { Best of all }, // Best of all, we don't have any homework!
 { Last }, // Last, I'll discuss family values.
 { Second }, // Second, we must consider the economy.
 { Sure enough }, // Sure enough, he asked her for money again.
 { All joking aside }, // All joking aside, I think you're crazy.
 { Month by month }, // Month by month, the betrayal gnawed at his heart.
 { Week by week }, // Week by week, the betrayal gnawed at his heart.
 { All at once }, // All at once, he started shouting.
 { All in all }, // All in all, it's not so bad.
 { To be sure }, // To be sure, he is no Einstein.
 { Then again }, // Then again, she might not go.
 { First of all }, // First of all, be sure of one thing.
 { Fortunately for you }, // Fortunately for you, I have it right here.
 { This time yesterday } // This time yesterday, we were having an English lesson
}


pattern ClauseOpener0
{
 ClauseOpenerCollocation:export{node:root_node}
}


// Alas, I cannot stay.
// ^^^^
pattern ClauseOpener0
{
 eng_interjection:*{}:export{node:root_node}
}

// As usual, she arrived late.
// ^^^^^^^^
pattern ClauseOpener0
{
 c=eng_conj:as{}:export{node:root_node}
 a=eng_adjective:*{} 
} : links { c.<NEXT_COLLOCATION_ITEM>a }


// As a matter of fact, he is several inches taller than his father.
// ^^^^^^^^^^^^^^^^^^^
pattern ClauseOpener0
{
 c=eng_conj:as{}:export{node:root_node}
 n=NounGroup
} : links { c.<NEXT_COLLOCATION_ITEM>n }



// Для вводных конструкций с отбивкой запятой.
patterns ClauseOpener export { node:root_node }

pattern ClauseOpener
{
 @probe_left(LeftClauseBoundary)
 intro=ClauseOpener0 : export{node:root_node}
 comma=','
} : links { intro.<PUNCTUATION>comma }


// "Please" часто употребляется без отбивки запятой:
// Please don't forget to write to me
// ^^^^^^
pattern ClauseOpener
{
 eng_particle:please{}:export{node:root_node}
}


pattern ClauseOpener
{
 @probe_left(LeftClauseBoundary)
 intro=ClauseOpener0 : export{node:root_node}
} : ngrams { -10 }


