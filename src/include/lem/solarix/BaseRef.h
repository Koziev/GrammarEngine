#if !defined BaseRef__H
 #define BaseRef__H

 #include <lem/ptr_container.h>

 namespace Solarix
 {

  // ******************************
  // Базовый класс для словарей БД.
  // ******************************
  template < typename ITEM >
  class BaseRef
  {
   protected:
    lem::Ptr_NC_Collect<ITEM> list;
    lem::MCollect<const ITEM*> old_list;

    #if defined SOL_LOADTXT
    lem::MCollect<ITEM*> sublist[256];
    #endif

    ITEM null_item; // всегда существующий элемент, его адрес можно
                    // возвращать во внешний код в некоторых крайних случаях.

    BaseRef( const BaseRef & );
    void operator=( const BaseRef & );

    void SortList(void)
    {
     // Отсортируем список old_list так, чтобы адреса в нем шли по возрастанию.
     const int N=CastSizeToInt(list.size());

     for( int gap=N/2; gap>0; gap/=2 )
      for( int i=gap; i<N; i++ )
       for( int j=i-gap; j>=0; j-=gap )
        {
         if( size_t(old_list[j+gap]) > size_t(old_list[j]) )
          break;

         std::swap( old_list[j], old_list[j+gap] );
         std::swap( list[j],     list[j+gap]     );
        }
     return;
    }

   public:
    BaseRef( int Delta=0 )
    {
     #if defined SOL_LOADTXT && defined SOL_COMPILER
     for( int i=0; i<256; i++ )
      sublist[i].reserve( (Delta/256) < 256 ? 256 : Delta/256 );
     #endif
    }

    // Register new item and return the pointer to stored Lexem.
    const ITEM* Add( const ITEM &x )
    {
     #if defined SOL_LOADTXT && defined SOL_COMPILER
     const int iSublist = unsigned( get_hash(x) ) & 0x00ffU;
     lem::MCollect<ITEM*> &sl = sublist[iSublist];

     for( lem::Container::size_type i=0; i<sl.size(); i++ )
      if( *(sl[i]) == x )
       // It is already stored.
       return sl[i];

     ITEM *to_add = new ITEM(x);
     list.push_back( to_add );
     sl.push_back( to_add );
     return to_add;
     #else

     const ITEM *stored = Find(x);
     if( stored!=NULL )
      return stored;

     ITEM *to_add = new ITEM(x);
     list.push_back( to_add );
     return to_add;
     #endif
    }
 

    const ITEM* Find( const ITEM &x ) const
    {
     for( lem::Container::size_type i=0; i<list.size(); ++i )
      if( *list[i] == x )
       return list[i];

     return NULL;
    }

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream &bin ) const
    {
     int n=CastSizeToInt(list.size());
     bin.write( &n, sizeof(n) );

     for( lem::Container::size_type i=0; i<list.size(); i++ )
      {
       const ITEM *ptr = list.get(i);
       bin.write( &ptr, sizeof(ptr) );
       list[i]->SaveBin(bin);
      }

     return;
    }
    #endif 


    #if defined SOL_LOADBIN
    void LoadBin( lem::Stream &bin )
    {
     int n=0;
     bin.read( &n, sizeof(n) );

     old_list.reserve( n );
     list.clear();
     list.reserve( n );

     for( int i=0; i<n; i++ )
      {
       const ITEM *ptr=NULL;
       bin.read( &ptr, sizeof(ptr) );
       old_list.push_back(ptr);

       ITEM *add = new ITEM;
       add->LoadBin(bin);
       list.push_back(add);
      }

     SortList();
     return;
    }
    #endif

    inline lem::Ptr_NC_Collect<ITEM>& get_list() { return list; }
    inline const lem::Ptr_NC_Collect<ITEM>& get_list() const
    { return list; }


    const ITEM* reattach( const ITEM *Old_Ptr ) const
    {
     if( !Old_Ptr )
      return &null_item;

     const int i_old = lem::find_bisection( old_list, Old_Ptr );
     LEM_CHECKIT_Z( i_old!=UNKNOWN );

     return list[i_old];
    }

    void AllAttached(void) { old_list.clear(); }
  };

 }
#endif
