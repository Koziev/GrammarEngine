// CD->28.12.2008
// LC->24.12.2015

automat sg
{
 #define Modal(Verb) tag ENG_VERB:Verb { VERB_SLOTS:ModalDirect }
 #define to(Verb) tag ENG_VERB:Verb { VERB_SLOTS:ModalTo }

 Modal(let)
 
 to(Need)
 Modal(need) // You need not do the work.
 Modal(help) // How did these new data help support the theory of plate tectonics?

 to(itch) // She is itching to start the project.
 to(aim) // The waiters around her aim to please.
 to(tend) // She tends to put down younger women colleagues.
 to( manage ) // she managed to live well.
 to(threaten) // Fundamental Islamicists threaten to perturb the social order in Algeria and Egypt.
 to(direct) // The dancers were directed to move upstage.
 to(offer) // He gallantly offered to take her home.
 to(Have)
 to(intend) // He roguishly intended to keep the money.
 to(learn) // We are learning to write English
 to(hope) // We hope to win the match
 to(forget)
 to(fail) // I failed to finish my homework
 to("Haven't")
 to(Want)
 to(Like)
 to(start)
 to(Get)
 to(Decide)
 to(Resolve)
 to(Begin)
 to(Help)
 to(propose)
 to(oblige)
 to(use)
 to(advise)
 to(promise)
 to(compel)
 to(ail)
 to(come) // e.g. come to help
 to(wish)
 to(allow)
 to(disallow)
 to(proceed) // proceed to steal things
 to(agree)
 to(accustom)
 to(desire)
 to(permit)
 to(endeavor)
 to(cease)
 to(forbid)
 to(refuse)
 to(invite)
 to(try)
 to(plan)
 to(teach) // Richard taught us to swim
 to(attempt) // They are presently attempting to gain a foothold in the Russian market.
 to(tough) // The horse was tough to break.
 to(contrive) // They contrived to murder their boss.

 Modal("Don't")
 Modal(dare)
 Modal(Pray)
 Modal(Do)
 Modal(make) // We make him do the work.
// Modal("be about to")

 // ‘ледующие 3 глагола фактически разворачиваются на полные конструкции
 // типа wanna->want to в начале синтаксического анализа
 Modal(Wanna)
 Modal(Gonna)
 Modal(Gotta)
}
