// Дополнительная информация для английского токенизатора - исключения
// из общих правил деления строк на лексемы.
//
// Подробнее о токенизаторе:
// http://www.solarix.ru/for_developers/docs/tokenizer.shtml
//
// 19.10.2009 добавлено правило для won't
// 11.03.2012 добавлено правило для ain't
// 17.10.2015 добавлены и поправлены правила для токенизации ФИО
//
// CD->08.02.2009
// LC->04.12.2015



unbreakable language=English { "'s" }
unbreakable language=English { "’s" }
unbreakable language=English { "'ve" } // I've done it
unbreakable language=English { "'d" } // She'd asked
unbreakable language=English { "'ll" } // I'll be back
unbreakable language=English { "'re" } // We're happy now
unbreakable language=English { "'m" } // I'm here



unbreakable language=English { "shan't" }
unbreakable language=English { "shan’t" }
unbreakable language=English { "isn't" }
unbreakable language=English { "isn’t" }
unbreakable language=English { "ain't" }
unbreakable language=English { "ain’t" }
unbreakable language=English { "don't" }
unbreakable language=English { "don’t" }
unbreakable language=English { "didn't" }
unbreakable language=English { "didn’t" }
unbreakable language=English { "doesn't" }
unbreakable language=English { "doesn’t" } // Paul doesn’t question it in this epistle.
unbreakable language=English { "haven't" }
unbreakable language=English { "haven’t" }
unbreakable language=English { "hasn't" }
unbreakable language=English { "hasn’t" }
unbreakable language=English { "hadn't" }
unbreakable language=English { "hadn’t" }
unbreakable language=English { "won't" }
unbreakable language=English { "won’t" }
unbreakable language=English { "isn't" }
unbreakable language=English { "isn’t" }
unbreakable language=English { "aren't" }
unbreakable language=English { "wasn't" }
unbreakable language=English { "wasn’t" }
unbreakable language=English { "weren't" }
unbreakable language=English { "weren’t" }
unbreakable language=English { "can't" }
unbreakable language=English { "can’t" }
unbreakable language=English { "couldn't" }
unbreakable language=English { "couldn’t" }
unbreakable language=English { "mustn't" }
unbreakable language=English { "mustn’t" }
unbreakable language=English { "shouldn't" }
unbreakable language=English { "shouldn’t" }
unbreakable language=English { "wouldn't" }
unbreakable language=English { "wouldn’t" }

unbreakable language=English { "B.C." } // He was born 551 B.C.

unbreakable language=English { "i.e." }
unbreakable language=English { "e.g." }
unbreakable language=English { "mr." }
unbreakable language=English { "ms." }
unbreakable language=English { "dr." }
unbreakable language=English { "etc." }
unbreakable language=English { "D.C." } // Washington, D.C.
unbreakable language=English { "a.k.a." }
unbreakable language=English { ":lol:" }
unbreakable language=English { "U.K." }
unbreakable language=English { "U.S." }
//unbreakable language=English { "let's" } // считаем одной лексемой, чтобы не вводить вариант 's для us.

unbreakable language=English { "p.m." }
unbreakable language=English { "a.m." }

unbreakable language=English { "Mrs." }
unbreakable language=English { "Rev." }
unbreakable language=English { "Prof." }
unbreakable language=English { "Gov." }
unbreakable language=English { "Sen." }
unbreakable language=English { "Rep." }
unbreakable language=English { "Gen." }
unbreakable language=English { "Brig." }
unbreakable language=English { "Col." }
unbreakable language=English { "Capt." }
unbreakable language=English { "Lieut." }
unbreakable language=English { "Lt." }
unbreakable language=English { "Sgt." }
unbreakable language=English { "Pvt." }
unbreakable language=English { "Cmdr." }
unbreakable language=English { "Adm." }
unbreakable language=English { "Corp." }
unbreakable language=English { "St." }
unbreakable language=English { "Mt." }
unbreakable language=English { "Ft." }
unbreakable language=English { "jr." }
unbreakable language=English { "Sr." }

unbreakable language=English { "pre-exist" }
unbreakable language=English { "dilly-dally" }
unbreakable language=English { "ad-lib" }
unbreakable language=English { "o'clock" }


// He earned a Ph.D. in 1993 from Manchester University
//             ^^^^^
unbreakable language=English { "Ph.D." }

// It earned $4.7 billion in 2010.
//           ^^^^
unbreakable language=English { ~"\\$[0123456789]+\\.[0123456789]+" }



// J. Bush
unbreakable language=English
{ ~"[<\\@L>]\\. [<\\@L>][<\\@l>]+" }


// He partnered with Stephen T. Logan
//                   ^^^^^^^^^^^^^^^^
unbreakable language=English
{ ~"[<\\@L>][<\\@l>]* [<\\@L>]\\. [<\\@L>][<\\@l>]+" }



// orthodox Catholic writer G. K. Chesterton regularly employed paradox
//                          ^^^^^^^^^^^^^^^^
unbreakable language=English
{ ~"[<\\@L>]\\. [<\\@L>]\\. [<\\@L>][<\\@l>]+" }


// Robin W.G. Horton
// ^^^^^^^^^^^^^^^^^
// Louis J. M. Beel formed a new coalition cabinet.
// ^^^^^^^^^^^^^^^^
unbreakable language=English
{ ~"[<\\@L>][<\\@l>]* [<\\@L>]\\.[ ]*[<\\@L>]\\. [<\\@L>][<\\@l>]+" }


// A.H.J. Prins
unbreakable language=English
{ ~"[<\\@L>]\\.[<\\@L>]\\.[<\\@L>]\\. [<\\@L>][<\\@l>]+" }

// W. H. R. Rivers
unbreakable language=English
{ ~"[<\\@L>]\\. [<\\@L>]\\. [<\\@L>]\\. [<\\@L>][<\\@l>]+" }

// L. P. Vidyarthi
unbreakable language=English
{ ~"[<\\@L>]\\. [<\\@L>]\\. [<\\@L>][<\\@l>]+" }


// URLs: http://www.gutenberg.net
//       ^^^^^^^^^^^^^^^^^^^^^^^^
unbreakable language=English
{ ~"http://[abcdefghijklmnopqrstuvwxyz1234567890_-\\.]+" }



// The school serves 1,600 students.
//                   ^^^^^
unbreakable language=English
{ ~"[0123456789]+\\,[0123456789]+" }

// The first industries began in 1980's.
//                               ^^^^^^
unbreakable language=English
{ ~"[0123456789]+'s" }


