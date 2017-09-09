function tree normalize_phrase_russian( tree root )
{
 tree nroot = wordform_root(root);

 int pos0 = wordform_class(root);

 if( eq( pos0, ПРИЛАГАТЕЛЬНОЕ ) )
 then
 {
  // Нормализация случаев типа "КОНДИЦИОНЕРЫ СТАРЕНЬКИЕ"
  // Прилагательное в дереве представляет именное сказуемое и располагается в корне.
  // Существительное является подлежащим.
  // Теперь атрибутирующее прилагательное.
  int nlink=link_count(root);
  int i;
  for i=0 to arith_minus(nlink,1)
  {
   if( eq( link_get_type2( root, "", i ), <SUBJECT> ) )
   then
   {
    tree sbj = link_get( root, "", i );
    if( eq( wordform_class( sbj ), СУЩЕСТВИТЕЛЬНОЕ ) )
    then
    {
     // нормализуем существительное
     if( neq( wordform_get_coord(sbj,ПАДЕЖ), ПАДЕЖ:ИМ ) )
     then
     {
      wordform_set_coord( sbj, ПАДЕЖ, ПАДЕЖ:ИМ );
     }
      
     if( neq( wordform_get_coord(sbj,ЧИСЛО), ЧИСЛО:ЕД ) )
     then
     {
      wordform_set_coord( sbj, ЧИСЛО, ЧИСЛО:ЕД );
     }
 
     // TODO: учесть случай существительных, у которых нет мн.ч.
     wordform_refresh( sbj );
     restore_case(sbj);

     // Теперь прилагательное     
     wordform_set_coord( root, ПАДЕЖ, ПАДЕЖ:ИМ );
     wordform_set_coord( root, ЧИСЛО, wordform_get_coord( sbj, ЧИСЛО ) );
     wordform_set_coord( root, РОД, wordform_get_coord( sbj, РОД ) );
     wordform_set_coord( root, СТЕПЕНЬ, СТЕПЕНЬ:АТРИБ );
     wordform_clear_coord( root, КРАТКИЙ );
     wordform_refresh( root );
     restore_case(root);

     // TODO: рекурсивно для прилагательных в союзной цепочке
     // ...
     
     return root;
    }
   }
  }
 }
 
 if( eq( pos0, СУЩЕСТВИТЕЛЬНОЕ ) )
 then
 {
  // нормализуем существительное и согласованное с ним прилагательное-атрибут.
  // TODO: особый случай, когда у существительного есть атрибут в виде счетного слова "много" etc

  if( neq( wordform_get_coord(nroot,ПАДЕЖ), ПАДЕЖ:ИМ ) )
  then
  {
   wordform_set_coord( nroot, ПАДЕЖ, ПАДЕЖ:ИМ );
  }
   
  if( neq( wordform_get_coord(nroot,ЧИСЛО), ЧИСЛО:ЕД ) )
  then
  {
   wordform_set_coord( nroot, ЧИСЛО, ЧИСЛО:ЕД );
  }

  // TODO: учесть случай существительных, у которых нет
  wordform_refresh( nroot );
  restore_case(nroot);

  wordform_replace( root, nroot );



  // Теперь атрибутирующее прилагательное.
  int nlink=link_count(root);
  int i;
  for i=0 to arith_minus(nlink,1)
  {
   if( eq( link_get_type2( root, "", i ), <ATTRIBUTE> ) )
   then
   {
    tree attr = link_getref( root, "", i );
    if( eq( wordform_class( attr ), ПРИЛАГАТЕЛЬНОЕ ) )
    then
    {
     wordform_set_coord( attr, ПАДЕЖ, ПАДЕЖ:ИМ );
     wordform_set_coord( attr, ЧИСЛО, wordform_get_coord( root, ЧИСЛО ) );
     wordform_set_coord( attr, РОД, wordform_get_coord( root, РОД ) );
     wordform_set_coord( attr, СТЕПЕНЬ, СТЕПЕНЬ:АТРИБ );
     wordform_clear_coord( attr, КРАТКИЙ );
     wordform_refresh( attr );
     restore_case(attr);
    }

    // TODO: рекурсивно для прилагательных в союзной цепочке
   }
  }
 }

 return root;
}
