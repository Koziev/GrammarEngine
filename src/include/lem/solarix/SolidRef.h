#if !defined SolidRef__H
 #define SolidRef__H

 #include <lem/noncopyable.h>
 #include <lem/containers.h>
 #include <lem/solarix/lexem.h>

 namespace Solarix
 {

  template < typename ITEM >
  class SolidRef : lem::NonCopyable
  {
   protected:
    const ITEM *old_first_item; // инициализируетс€ после загрузки из файла

    lem::MCollect<ITEM> list;

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    lem::MCollect<int> sublist[256];
    #endif

    ITEM null_item; // всегда существующий элемент, его адрес можно
                    // возвращать во внешний код в некоторых крайних случа€х.

   public:
    // “ак как мы отдаем указатели на хранимые в списке элементы, то придетс€
    // заранее выдел€ть пам€ть под список с запасом. ¬ случае переполнени€ будет
    // сгенерировано исключение.
    SolidRef( int Reserve )
    {
     LEM_CHECKIT_Z( Reserve>=0 );

     list.reserve(Reserve);
     old_first_item = NULL;

     #if defined SOL_LOADTXT && defined SOL_COMPILER
     for( int i=0; i<256; i++ )
      sublist[i].reserve( Reserve/256 );
     #endif
    }

    void Reserve( int n )
    {
     list.reserve(n);
     return;
    }

    #if defined SOL_LOADTXT

     #if defined SOL_COMPILER
     // Register new item and return the pointer to stored item.
     const ITEM* Add( const ITEM &x )
     {
      const int iSublist = unsigned( get_hash(x) ) & 0x00ffU;
      lem::MCollect<int> &sl = sublist[iSublist];

      for( lem::Container::size_type i=0; i<sl.size(); i++ )
       if( list[sl[i]] == x )
        // It is already stored.
        return &list[sl[i]];

      //   сожалению, из-за технологических особенностей хранени€
      // списка лексем приходитс€ заранее определ€ть его предельную
      // вместимость.
      if( list.size() == list.capacity() )
       throw lem::E_BaseException( L"Insufficient space in SolidRef list!\n" );

      sl.push_back( list.size() );
      list.push_back( x );
      return &list.back();
     }
     #else
     const ITEM* Add( const ITEM &x )
     {
      const ITEM *z = Find(x);
      if( z!=NULL )
       return z;
 
      //   сожалению, из-за технологических особенностей хранени€
      // списка лексем приходитс€ заранее определ€ть его предельную
      // вместимость.
      if( list.size() == list.capacity() )
       throw lem::E_BaseException( L"Insufficient space in SolidRef list!\n" );

      list.push_back( x );
      return &list.back();
     }
     #endif

    #endif

    const ITEM* Find( const ITEM &x ) const
    {
     for( lem::Container::size_type i=0; i<list.size(); i++ )
      if( list[i] == x )
       return &list[i];

     return NULL;
    }


    inline const lem::MCollect<ITEM>& get_list(void) const { return list; }

    lem::Container::size_type size(void) const { return list.size(); }
    const ITEM& operator[]( int i ) const { return list[i]; }

    const ITEM* reattach( const ITEM *Old_Ptr ) const
    {
     if( !Old_Ptr )
      return &null_item;

     // “ак как мы знаем адрес первого элемента в старом списке, и знаем
     // размер одного элемента, то получение нового адреса по старому - 
     // делаетс€ элементарно.
     LEM_CHECKIT_Z( Old_Ptr>=old_first_item );

     const lem::Container::size_type i_old = Old_Ptr - old_first_item;
     return &list[i_old];
    }
  };

 }
#endif
