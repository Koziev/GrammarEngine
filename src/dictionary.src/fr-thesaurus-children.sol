// CD->24.07.2011
// LC->24.07.2011

#define ParentOf( Parent, Child ) \
#begin
 extern entry Child : FR_NOUN
 extern entry Parent : FR_NOUN
 link FR_NOUN:Child {} <child_of> FR_NOUN:Parent {}
 link FR_NOUN:Parent {} <parent_of> FR_NOUN:Child {}
#end

automat sg
{
 ParentOf( aigle, aiglon )

/*
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
 ParentOf( ,  )
/**/
}
