﻿// CD->26.02.2011
// LC->07.05.2011

automat sg
{
 #define SexSynonym( A, B ) \
  #begin
   extern entry A:FR_NOUN
   extern entry B:FR_NOUN
   link FR_NOUN:A{} <sex_synonym> FR_NOUN:B{}
   link FR_NOUN:B{} <sex_synonym> FR_NOUN:A{}
  #end


 SexSynonym( chien, chienne )
 SexSynonym( roi, reine )

 SexSynonym( accompagnateur, accompagnatrice )
 SexSynonym( acteur, actrice )
 SexSynonym( adaptateur, adaptatrice )
 SexSynonym( administrateur, administratrice )
 SexSynonym( agitateur, agitatrice )
 SexSynonym( agriculteur, agricultrice )
 SexSynonym( animateur, animatrice )
 SexSynonym( bienfaiteur, bienfaitrice )
 SexSynonym( compétiteur, compétitrice )
 SexSynonym( cultivateur, cultivatrice )
 SexSynonym( curateur, curatrice )
 SexSynonym( désapprobateur, désapprobatrice )
 SexSynonym( dessinateur, dessinatrice )
 SexSynonym( dissipateur, dissipatrice )
 SexSynonym( électeur, électrice )
 SexSynonym( examinateur, examinatrice )
 SexSynonym( excavateur, excavatrice )
 SexSynonym( excréteur, excrétrice )
 SexSynonym( falsificateur, falsificatrice )
 SexSynonym( géniteur, génitrice )
 SexSynonym( illustrateur, illustratrice )
 SexSynonym( informateur, informatrice )
 SexSynonym( inspecteur, inspectrice )
 SexSynonym( inspirateur, inspiratrice )
 SexSynonym( instigateur, instigatrice )
 SexSynonym( instituteur, institutrice )
 SexSynonym( interlocuteur, interlocutrice )
 SexSynonym( intimidateur, intimidatrice )
 SexSynonym( introducteur, introductrice )
 SexSynonym( lecteur, lectrice )
 SexSynonym( locuteur, locutrice )
 SexSynonym( moniteur, monitrice )
 SexSynonym( opérateur, opératrice )
 SexSynonym( orateur, oratrice )
 SexSynonym( ostréiculteur, ostréicultrice )
 SexSynonym( pertrubateur, pertrubatrice )
 SexSynonym( prédicateur, prédicatrice )
 SexSynonym( profanateur, profanatrice )
 SexSynonym( réprobateur, réprobatrice )
 SexSynonym( reproducteur, reproductrice )
 SexSynonym( révélateur, révélatrice )
 SexSynonym( simulateur, simulatrice )
 SexSynonym( spectateur, spectatrice )
 SexSynonym( spéculateur, spéculatrice )
 SexSynonym( temporisateur, temporisatrice )
 SexSynonym( tuteur, tutrice )
 SexSynonym( versificateur, versificatrice )
 SexSynonym( sorcier, sorcière )
 SexSynonym( devin, devineresse )
 SexSynonym( trésorier, trésorière )
 SexSynonym( arbalétrier, arbalétrière )
 SexSynonym( aumônier, aumônière )
 SexSynonym( aventurier, aventurière )
 SexSynonym( batelier, batelière )
 SexSynonym( bijoutier, bijoutière )
 SexSynonym( buandier, buandière )
 SexSynonym( bélier, bélière )
 SexSynonym( cabaretier, cabaretière )
 SexSynonym( cafetier, cafetière )
 SexSynonym( caissier, caissière )
 SexSynonym( charnier, charnière )
 SexSynonym( conférencier, conférencière )
 SexSynonym( courtier, courtière )
 SexSynonym( coéquipier, coéquipière )
 SexSynonym( crémier, crémière )
 SexSynonym( cuisinier, cuisinière )
 SexSynonym( devancier, devancière )
 SexSynonym( fourmilier, fourmilière )
 SexSynonym( fourrier, fourrière )
 SexSynonym( fripier, fripière )
 SexSynonym( geôlier, geôlière )
 SexSynonym( giletier, giletière )
 SexSynonym( guichetier, guichetière )
 SexSynonym( guêpier, guêpière )
 SexSynonym( joaillier, joaillière )
 SexSynonym( lanier, lanière )
 SexSynonym( lisier, lisière )
 SexSynonym( meurtrier, meurtrière )
 SexSynonym( panier, panière )
 SexSynonym( placier, placière )
 SexSynonym( poivrier, poivrière )
 SexSynonym( rosier, rosière )
 SexSynonym( sablier, sablière )
 SexSynonym( tavernier, tavernière )
 SexSynonym( tenancier, tenancière )
 SexSynonym( trésorier, trésorière )
 SexSynonym( émeutier, émeutière )
 SexSynonym( épervier, épervière )
 SexSynonym( épicier, épicière )
 SexSynonym( équipier, équipière )

 /*
 SexSynonym( ,  )
 SexSynonym( ,  )
 SexSynonym( ,  )
 SexSynonym( ,  )
 SexSynonym( ,  )
 SexSynonym( ,  )
 SexSynonym( ,  )
*/ 
}
