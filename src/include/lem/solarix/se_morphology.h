// 27.05.2008 - добавлен тим морфологии Stems, то есть через генерацию стема

//
// CD->04.02.2006
// LC->27.05.2008
// --------------

#ifndef SE_MORPHOLOGY__H
#define SE_MORPHOLOGY__H
#pragma once

 namespace Solarix
 {
  namespace Search_Engine
  { 

   // Флаг управления морфологическим анализатором
   struct Morphology
   {
    typedef enum { None, Wordforms, Dynforms, Stems } Type;
    Type type;

    Morphology(void) { type=None; }
    Morphology( Type x ) : type(x) {}

    inline void clear(void) { type=None; }

    inline bool operator==( Morphology::Type x ) const { return type==x; }
    inline bool operator!=( Morphology::Type x ) const { return type!=x; }

    inline operator bool(void) const { return type!=Morphology::None; } 

    inline Morphology operator+( Morphology::Type x ) const
    {
     switch( type )
     {
      case None:      return x;
      case Wordforms: return x==Dynforms ? Dynforms : Wordforms;
      case Dynforms:  return Dynforms;
      case Stems:     return Stems; // ???
     }

     return None; 
    }
   };


   // Флаг управления синнтаксическим анализатором
   struct Syntax
   {
    typedef enum { None, Simple, Full } Type;
    Type type;

    Syntax(void) { type=None; }

    Syntax( Type x ) : type(x) {}

    inline void clear(void) { type=None; }

    inline bool operator==( Syntax::Type x ) const { return type==x; }
    inline bool operator!=( Syntax::Type x ) const { return type!=x; }
   };

  }
 }

#endif
