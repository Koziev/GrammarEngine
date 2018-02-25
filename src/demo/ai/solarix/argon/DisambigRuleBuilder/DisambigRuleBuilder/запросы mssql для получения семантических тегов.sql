-- 10k самых частотных статей - в семантические теги для pos tagger'а
select TT.w + '#' + cast( TT.t as varchar )
 from 
(
 select T.word as w, MAX(T.tag) as t
 from
 (
select top 10000 E.name as word, E.id as tag
 from sg_entry E, sg_class C, sg_language L
 where LEN(E.name)>1
       and C.id=E.id_class
       and L.id=C.id_lang
       and L.name='Russian'
 order by freq desc
) T
group by T.word
) TT
 


-- получение тегов для POS Tagger'а из тезауруса
select E1.name + '#' + E2.name
 from sg_entry E1, sg_link L, sg_entry E2, sg_state S, sg_class C, sg_language LANG
 where 
  L.id_entry2=E2.id
  and S.id=L.istate
  and S.id_coord=0
  and S.name='в_класс'
  and E1.id=L.id_entry1
  and C.id=E1.id_class
  and LANG.id=C.id_lang
  and LANG.name='Russian'
 
