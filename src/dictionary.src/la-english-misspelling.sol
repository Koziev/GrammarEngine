// Правила распознавания опечаток для английского языка.
// CD->10.02.2012
// LC->25.05.2012
// --------------


automat la
{
 // Вместо двойной ll на конце делаем одиночную
 #define all2al(correct) misspelling language=English { if correct##l then correct }

 all2al(personal)
 all2al(continual)
 all2al(general)
 all2al(natural)
 all2al(anniversal)
 all2al(phantastical)
 all2al(casual)
 all2al(conditional)
 all2al(mystical)
 all2al(typical)
 all2al(magical)
 all2al(schismatical)
 all2al(principal)
 all2al(herbal)
 all2al(spyrytual)
 all2al(spiritual)
 all2al(spirytual)
 all2al(spyritual)
 all2al(effectual)
 all2al(gradual)
 all2al(habitual)
 all2al(poststal)
 all2al(individual)
 all2al(intellectual)
 all2al(journal)
 all2al(manual)
 all2al(menstrual)
 all2al(ineffectual)
 all2al(mutual)
 all2al(perpetual)
 all2al(punctual)
 all2al(ritual)
 all2al(sensual)
 all2al(tactual)
 all2al(polemical)
 all2al(textual)
 all2al(unusual)
 all2al(unequal)
 all2al(vertual)
 all2al(visual)
 all2al(virtual)
 all2al(ancestral)
 all2al(armorial)
 all2al(royal)
 all2al(roial)
 all2al(regal)
 all2al(rational)
 all2al(ecclesiastical)
 all2al(prejudical)
 all2al(political)
 all2al(mineral)
 all2al(hystorical)
 all2al(phylosophical)
 all2al(philosophical)
 all2al(especial)

 #define rule(incorrect,correct) misspelling language=English { if incorrect then correct }

 // travel (third-person singular simple present travels,
 //         present participle Commonwealth travelling, US traveling,
 //         simple past and past participle Commonwealth travelled, US traveled)
 rule( travell, travel )
 rule( travells, travels )
 rule( traveled, travelled )
 rule( traveling, travelling )
 rule( undestand, understand )
}
