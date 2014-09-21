// -----------------------------------------------------------------------------
// File LEM_DOTC.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// Класс WidgetCollect - универсальный контейнер (НЕ ШАБЛОН - managed-код не
// позволяет этого) для оконных элементов среды .NET.
// -----------------------------------------------------------------------------
//
// CD->28.04.2004
// LC->05.09.2005
// --------------

#ifndef LEM_DOT_COLLECT__H
#define LEM_DOT_COLLECT__H
#pragma once

 #if defined LEM_DOT_NET
 #using <System.DLL>

 namespace lem
 {
  typedef System::Windows::Forms::Control __gc* pWidget;
  typedef System::Object __gc* pDotObject;

  private __gc class DotCollect
  {
   private:
    int upperbound;
    int delta;
    int n;
    pDotObject container __gc[];

    inline void realloc()
    {
     container = new pDotObject __gc[ upperbound+=delta ];
     upperbound += delta;
    }

   public:
    DotCollect()
    {
     n=0;
     upperbound=-1;
     delta=128;
    }

    ~DotCollect()
    {
     for( int i=0; i<n; i++ )
      container[i] = NULL;

     delete[] container;
     container=NULL;
    }
 
    inline void Add( pDotObject Ptr )
    {
     if( n>upperbound )
      realloc();  

     container[n++] = Ptr;
    }

    inline pDotObject get( int i ) { return container[i]; }
    inline int size() { return n; }
  };

  private __gc class WidgetCollect
  {
   private:
    int upperbound;
    int delta;
    int n;
    pWidget container __gc[];

    inline void realloc()
    {
     container = new pWidget __gc[ upperbound+=delta ];
     upperbound += delta;
    }

   public:
    WidgetCollect()
    {
     n=0;
     upperbound=-1;
     delta=128;
    }

    ~WidgetCollect()
    {
     for( int i=0; i<n; i++ )
      {
       if( container[i] )
        { 
         container[i]->Dispose();
         container[i] = NULL;
        } 
      }

     delete[] container;
     container=NULL;
    }
 
    inline void Add( pWidget Ptr )
    {
     if( n>upperbound )
      realloc();  

     container[n++] = Ptr;
    }

    inline pWidget get( int i ) { return container[i]; }
    inline int size() { return n; }
  };
  #endif

 } // namespace lem


#endif
// ----------------------------- End Of File [LEM_DOTC.H] ----------------------