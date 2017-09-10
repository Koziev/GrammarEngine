facts eng_adv_adj_score language=English
{
 arity=2
 return=integer
}

#define aa(m,a,w) \
#begin
fact eng_adv_adj_score
{
 if context { eng_adverb:m{} eng_adjective:a{} }
  then return w
}
#end


aa( nearly, all, 5 ) // Quarter Horses come in nearly all colors.
aa( too, many, 5 ) // Our shop has too many goods on hand.
aa( some, long, 5 ) // However, the border is some long.
aa( so, foolish, 5 ) // Are you so foolish?
aa( totally, dark, 5 )
aa( quite, busy, 5 ) // Damascus has quite busy midnights.
aa( seriously,ill, 6 ) // In 1659, Pascal fell seriously ill.
aa( continuously, available, 5 )
aa( vastly, different, 5 )
aa( extremely, hot, 5 )
aa( extremely, cold, 5 )
aa(relatively,close,5)
aa(increasingly,violent,5) // It also became increasingly violent.
aa(almost,all,5) // Almost all U.S. bears live in Alaska.
aa(well,known,2) // She was well known as a hostess;
aa(quite,rich,5) // quite rich
aa(deadly,dull,5) // deadly dull
aa(very,successful,5) // This experiment proved very successful.
aa(increasingly,violent,5) // It also became increasingly violent.
aa(pretty,stupid,5) // He is pretty stupid
aa(very,stupid,5) // He is very stupid
aa(pretty,good,5) // She's pretty good.
