#ifndef LEM_MINMAX__H
#define LEM_MINMAX__H
#pragma once

#undef min
#undef max

namespace lem
{
 template < class T >
 inline T min( T a, T b )
 { return a<b ? a : b; }

 template < class T >
 inline T max( T a, T b )
 { return a>b ? a : b; }

 template < class T >
 inline T max( T a, T b, T c )
 { return lem::max( a, lem::max(b,c) ); }


 template < class T >
 inline T _min( T a, T b )
 { return a<b ? a : b; }

 template < class T >
 inline T _max( T a, T b )
 { return a>b ? a : b; }
}

#endif
