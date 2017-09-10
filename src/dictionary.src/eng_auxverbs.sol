automat sg
{

entry "must" : ENG_AUXVERB 
{
 VERB_SLOTS:ModalDirect
 VERB_FORM:UNDEF { "must" }
}

entry "ought" : ENG_AUXVERB 
{
 VERB_SLOTS:ModalTo
 VERB_FORM:UNDEF { "ought" }
}


entry "must_not" : ENG_AUXVERB 
{
 VERB_SLOTS:ModalDirect
 VERB_FORM:UNDEF { "mustn't" }
}

entry "shall" : ENG_AUXVERB 
{
 VERB_SLOTS:ModalDirect
 VERB_FORM:UNDEF { "shall" }
}

entry "shall_not" : ENG_AUXVERB 
{
 VERB_SLOTS:ModalDirect
 VERB_FORM:UNDEF { "shan't" }
}


entry "should" : ENG_AUXVERB 
{
 VERB_SLOTS:ModalDirect
 VERB_FORM:UNDEF { "should" }
}

entry "should_not" : ENG_AUXVERB 
{
 VERB_SLOTS:ModalDirect
 VERB_FORM:UNDEF { "shouldn't" }
}

entry "may" : ENG_AUXVERB 
{
 VERB_SLOTS:ModalDirect
 VERB_FORM:UNDEF { "may" }
 VERB_FORM:ED { "might" }
}

entry "cannot" : ENG_AUXVERB 
{
 VERB_SLOTS:ModalDirect
 VERB_FORM:UNDEF { "cannot" }
 VERB_FORM:UNDEF { "can't" }
 VERB_FORM:ED { "couldn't" }
}

entry "can" : ENG_AUXVERB 
{
 VERB_SLOTS:ModalDirect
 VERB_FORM:UNDEF { "can" }
 VERB_FORM:ED { "could" }
}



entry "would" : ENG_AUXVERB 
{
 VERB_SLOTS:ModalDirect
 VERB_FORM:UNDEF { "would" }
 VERB_FORM:UNDEF { "'d" }
}

entry "would_not" : ENG_AUXVERB 
{
 VERB_SLOTS:ModalDirect
 VERB_FORM:UNDEF { "wouldn't" }
}


entry "will" : ENG_AUXVERB 
{
 VERB_SLOTS:ModalDirect
 VERB_FORM:UNDEF { "will" }
 VERB_FORM:UNDEF { "'ll" }
 VERB_FORM:ING { "willing" }
}

entry "will_not" : ENG_AUXVERB 
{
 VERB_SLOTS:ModalDirect
 VERB_FORM:UNDEF { "won't" }
}

// It need not be a primitive melt.
//    ^^^^
entry "need" : ENG_AUXVERB 
{
 VERB_SLOTS:ModalDirect
 VERB_FORM:UNDEF { "need" }
}
 
}
