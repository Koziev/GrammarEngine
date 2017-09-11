// LC->18.07.2011

automat sg
{
 
 #define verb( inf, \
               je, tu, il, nous, vous, ils, \             // indicatif présent
               je_i, tu_i, il_i, nous_i, vous_i, ils_i, \ // indicatif imparfait
               je_f, tu_f, il_f, nous_f, vous_f, ils_f, \ // indicatif futur
               je_p, tu_p, il_p, nous_p, vous_p, ils_p, \ // indicatif passé simple 	
               present_participle, // participe présent
			   past_participle_1, past_participle_2, past_participle_3, past_participle_4, \  // participe passé
               imp1, imp21, imp22, // impératif présent
               subj_pres_1_s, subj_pres_1_p, subj_pres_2_s, subj_pres_2_p, subj_pres_3_s, subj_pres_3_p, // subjonctif présent
               subj_imp_1_s, subj_imp_1_p, subj_imp_2_s, subj_imp_2_p, subj_imp_3_s, subj_imp_3_p, // subjonctif 	imparfait
               cond_1_s, cond_1_p, cond_2_s, cond_2_p, cond_3_s, cond_3_p // conditionnel 	présent
			  ) \
 #begin
 entry inf : FR_VERB
 {
  FR_VERB_FORM:INFINITIVE { inf }

  FR_VERB_FORM:PRESENT |{
                         FR_PERSON:1 FR_NOMBRE:SINGULIER { je }
                         FR_PERSON:1 FR_NOMBRE:PLURIEL   { nous }
						 
                         FR_PERSON:2 FR_NOMBRE:SINGULIER { tu }
                         FR_PERSON:2 FR_NOMBRE:PLURIEL   { vous }
						 
                         FR_PERSON:3 FR_NOMBRE:SINGULIER { il }
                         FR_PERSON:3 FR_NOMBRE:PLURIEL   { ils }
                        }

  FR_VERB_FORM:IMPERFECT |{
                          FR_PERSON:1 FR_NOMBRE:SINGULIER { je_i }
                          FR_PERSON:1 FR_NOMBRE:PLURIEL   { nous_i }
						 
                          FR_PERSON:2 FR_NOMBRE:SINGULIER { tu_i }
                          FR_PERSON:2 FR_NOMBRE:PLURIEL   { vous_i }
						 
                          FR_PERSON:3 FR_NOMBRE:SINGULIER { il_i }
                          FR_PERSON:3 FR_NOMBRE:PLURIEL   { ils_i }
                         }
						
  FR_VERB_FORM:FUTURE |{
                         FR_PERSON:1 FR_NOMBRE:SINGULIER { je_f }
                         FR_PERSON:1 FR_NOMBRE:PLURIEL   { nous_f }
						 
                         FR_PERSON:2 FR_NOMBRE:SINGULIER { tu_f }
                         FR_PERSON:2 FR_NOMBRE:PLURIEL   { vous_f }
						 
                         FR_PERSON:3 FR_NOMBRE:SINGULIER { il_f }
                         FR_PERSON:3 FR_NOMBRE:PLURIEL   { ils_f }
                        }

  FR_VERB_FORM:SIMPLE_PAST |{
                             FR_PERSON:1 FR_NOMBRE:SINGULIER { je_p }
                             FR_PERSON:1 FR_NOMBRE:PLURIEL   { nous_p }
						    
                             FR_PERSON:2 FR_NOMBRE:SINGULIER { tu_p }
                             FR_PERSON:2 FR_NOMBRE:PLURIEL   { vous_p }
						     
                             FR_PERSON:3 FR_NOMBRE:SINGULIER { il_p }
                             FR_PERSON:3 FR_NOMBRE:PLURIEL   { ils_p }
                            }


  FR_VERB_FORM:IMPERATIVE |{
                            FR_PERSON:1 FR_NOMBRE:PLURIEL   { imp1 }
                            FR_PERSON:2 FR_NOMBRE:SINGULIER { imp21 }
                            FR_PERSON:2 FR_NOMBRE:PLURIEL   { imp22 }
                           }

  FR_VERB_FORM:SUBJUNCTIVE_PRESENT |{
                                     FR_PERSON:1 FR_NOMBRE:SINGULIER { subj_pres_1_s }
                                     FR_PERSON:1 FR_NOMBRE:PLURIEL   { subj_pres_1_p }
						 
                                     FR_PERSON:2 FR_NOMBRE:SINGULIER { subj_pres_2_s }
                                     FR_PERSON:2 FR_NOMBRE:PLURIEL   { subj_pres_2_p }
						 
                                     FR_PERSON:3 FR_NOMBRE:SINGULIER { subj_pres_3_s }
                                     FR_PERSON:3 FR_NOMBRE:PLURIEL   { subj_pres_3_p }
                                    }

  FR_VERB_FORM:SUBJUNCTIVE_IMPERFECT |{
                                       FR_PERSON:1 FR_NOMBRE:SINGULIER { subj_imp_1_s }
                                       FR_PERSON:1 FR_NOMBRE:PLURIEL   { subj_imp_1_p }
						           
                                       FR_PERSON:2 FR_NOMBRE:SINGULIER { subj_imp_2_s }
                                       FR_PERSON:2 FR_NOMBRE:PLURIEL   { subj_imp_2_p }
						           
                                       FR_PERSON:3 FR_NOMBRE:SINGULIER { subj_imp_3_s }
                                       FR_PERSON:3 FR_NOMBRE:PLURIEL   { subj_imp_3_p }
                                      }

  FR_VERB_FORM:CONDITIONAL |{
                             FR_PERSON:1 FR_NOMBRE:SINGULIER { cond_1_s }
                             FR_PERSON:1 FR_NOMBRE:PLURIEL   { cond_1_p }
						    
                             FR_PERSON:2 FR_NOMBRE:SINGULIER { cond_2_s }
                             FR_PERSON:2 FR_NOMBRE:PLURIEL   { cond_2_p }
						    
                             FR_PERSON:3 FR_NOMBRE:SINGULIER { cond_3_s }
                             FR_PERSON:3 FR_NOMBRE:PLURIEL   { cond_3_p }
                            }


  FR_VERB_FORM:PRESENT_PARTICIPLE { present_participle }

  FR_VERB_FORM:PAST_PARTICIPLE |{
                                 FR_NOMBRE:SINGULIER FR_GENRE:MASCULINE { past_participle_1 }
                                 FR_NOMBRE:PLURIEL   FR_GENRE:MASCULINE { past_participle_2 }
                                 FR_NOMBRE:SINGULIER FR_GENRE:FEMININE  { past_participle_3 }
                                 FR_NOMBRE:PLURIEL   FR_GENRE:FEMININE  { past_participle_4 }
                                }

 }
 #end 
 
 verb(
      avoir,
	  ai, avons, as, avez, a, ont,
	  avais, avions, avais, aviez, avait, avaient,
	  aurai, aurons, auras, aurez, aura, auront,
      eus, eûmes, eus, eûtes, eut, eurent,
      ayant,
      eu, eus, eue, eues,
      ayons, aie, ayez,
      aie, ayons, aies, ayez, ait, aient,
      eusse, eussions, eusses, eussiez, eût, eussent,
      aurais, aurions, aurais, auriez, aurait, auraient
	 )


 verb(
      être,
	  suis, sommes, es, êtes, est, sont,
	  étais, étions, étais, étiez, était, étaient,
	  serai, serons, seras, serez, sera, seront,
      fus, fûmes, fus, fûtes, fut, furent,
      étant,
      été, étés, étée, étées,
      soyons, sois, soyez,
      sois, soyons, sois, soyez, soit, soient,
      fusse, fussions, fusses, fussiez, fût, fussent,
      serais, serions, serais, seriez, serait, seraient
	 )

 
 verb(
      manger,
	  mange, manges, mange, mangeons, mangez, mangent,
	  mangeais, mangeais, mangeait, mangions, mangiez, mangeaient,
	  mangerai, mangeras, mangera, mangerons, mangerez, mangeront,
      mangeai, mangeas, mangea, mangeâmes, mangeâtes, mangèrent,
      mangeant,
      mangé, mangés, mangée, mangées,
      mangeons, mange, mangez,
      mange, mangions, manges, mangiez, mange, mangent,
      mangeasse, mangeassions, mangeasses, mangeassiez, mangeât, mangeassent, 
      mangerais, mangerions, mangerais, mangeriez, mangerait, mangeraient
	 )

 verb(
      commencer,
	  commence, commences, commence, commençons, commencez, commencent,
      commençais, commençais, commençait, commencions, commenciez, commençaient,
	  commencerai, commenceras, commencera, commencerons, commencerez, commenceront,
      commençai, commenças, commença, commençâmes, commençâtes, commencèrent,
      commençant,
	  commencé, commencés, commencés, commencées,
      commençons, commence, commencez,
      commence, commencions, commences, commenciez, commence, commencent,
      commençasse, commençassions, commençasses, commençassiez, commençât, commençassent,
      commencerais, commencerions, commencerais, commenceriez, commencerait, commenceraient
	 )

 verb(
      boire,
      bois, bois, boit, buvons, buvez, boivent,
      buvais, buvais, buvait, buvions, buviez, buvaient,
      boirai, boiras, boira, boirons, boirez, boiront,
      bus, bus, but, bûmes, bûtes, burent,
      buvant,
      bu, bus, bue, bues,
      buvons, bois, buvez,
      boive, buvions, boives, buviez, boive, boivent,
      busse, bussions, busses, bussiez, bût, bussent,
      boirais, boirions, boirais, boiriez, boirait, boiraient
     )

}
