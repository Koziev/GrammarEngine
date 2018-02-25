select T.str
 from
 (
select DISTINCT(  C.name + ' ' + dbo.GetFormCoords( E.ID, F.IFORM ) ) as str
 from sg_language L
 join sg_class C on C.id_lang=L.id --OR C.id_lang=-1 OR C.id_lang is null
 join sg_entry E on E.id_class=C.id
 join sg_form F on F.id_entry=E.id
 where L.name='English' ) T
 order by LEN(T.str) DESC
 
 
 
 
select TOP 1000  C.name + ' ' + dbo.GetFormCoords( E.ID, F.IFORM )
 from sg_language L
 join sg_class C on C.id_lang=L.id-- OR C.id_lang=-1 OR C.id_lang is null
 join sg_entry E on E.id_class=C.id
 join sg_form F on F.id_entry=E.id
 where L.name='English'
 
    