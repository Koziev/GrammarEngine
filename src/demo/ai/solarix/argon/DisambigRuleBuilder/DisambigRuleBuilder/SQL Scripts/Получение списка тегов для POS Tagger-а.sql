select distinct (C.name + dbo.RemoveZeroCoords( dbo.GetEntryPairs(E.id) + PF.str_pairs ) ), LEN(dbo.RemoveZeroCoords( dbo.GetEntryPairs(E.id) + PF.str_pairs ))
 from sg_entry E, sg_form F, sg_class C, coord_pairs PF
 where C.id=E.id_class
  and F.id_entry=E.id
  and PF.id=F.id_dims
  and C.name in ( 'œ–»À¿√¿“≈À‹ÕŒ≈' )
 order by LEN(dbo.RemoveZeroCoords( dbo.GetEntryPairs(E.id) + PF.str_pairs )) desc
 

  