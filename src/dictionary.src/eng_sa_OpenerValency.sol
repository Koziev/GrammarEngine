
tree_scorers OpenerValency


// By definition, no specific cause can be determined.
// ^^^^^^^^^^^^^^
tree_scorer OpenerValency language=Russian
{
 if context { eng_prep:by{}.<OBJECT>eng_noun:definition{}.[not]*:*{} }
  then 1
}



