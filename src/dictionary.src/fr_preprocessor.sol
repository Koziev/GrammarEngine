
// d'où
unbreakable language=French { "d'où" }


// l'Italie
// c'est
// J'achète
// n'aime pas
// t'appelles
// s'intéressent
// d'Europe
token_rewriter L_article greedy language=French
{
 if { ~"([lcjntsd]')(.+)" } then { "?1" "?2" }
}


//Qu'est-ce
token_rewriter qu_prefix greedy language=French
{
 if { ~"(qu')(.+)" } then { "?1" "?2" }
}
