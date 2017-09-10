/*
// I'll be back
token_rewriter ll_postfix greedy language=English
{
 if { ~"(.+)('ll)" } then { "?1" "?2" }
}

// We're happy now
token_rewriter re_postfix greedy language=English
{
 if { ~"(.+)('re)" } then { "?1" "?2" }
}

// I've done it
token_rewriter ve_postfix greedy language=English
{
 if { ~"(.+)('ve)" } then { "?1" "?2" }
}

// She'd asked
token_rewriter d_postfix greedy language=English
{
 if { ~"(.+)('d)" } then { "?1" "?2" }
}

// I'm here
token_rewriter m_postfix greedy language=English
{
 if { ~"(.+)('m)" } then { "?1" "?2" }
}


// Greenspan's -> [Greenspan's]
// Man's -> [Man] ['s]
token_rewriter s_postfix nongreedy language=English
{
 if { ~"(.+)('s)" } then { "?1" "?2" }
}
*/
