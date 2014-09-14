#if !defined NGRAM_SCORE__H
 #define NGRAM_SCORE__H

 namespace Solarix
 {

  struct NGramScore
  {
   public:

   int positive;
   int negative;

   NGramScore() : positive(0), negative(0) {}

   explicit NGramScore( int x )
   {
    if( x<0 )
     { negative=x; positive=0; }
    else
     { positive=x; negative=0; }
   }

   NGramScore( const NGramScore & x, const NGramScore & y )
   {
    positive = x.positive+y.positive;
    negative = x.negative+y.negative;
   }

   bool IsZero() const { return positive==0 && negative==0; }

   void SetMinInfinite() { positive=0; negative=lem::int_min; }

   void operator+=( const NGramScore & x )
   {
    positive+=x.positive;
    negative+=x.negative;
   }

   inline bool Equal( const NGramScore & y ) const
   {
    return Composite()==y.Composite();
   }

   inline bool Greater( const NGramScore & y ) const
   {
    if( Composite()>y.Composite() )
     return true;
    else if( Composite()==y.Composite() )
     return positive>y.positive;
    else
     return false;
   }

   int Composite() const { return positive+negative; }
  };

 

   inline bool operator>( const NGramScore & x, const NGramScore & y )
   {
    if( x.negative>y.negative )
     return true;
    else if( x.negative==y.negative )
     return x.positive>y.positive;
    else
     return false;
   }

   inline bool operator<( const NGramScore & x, const NGramScore & y )
   {
    if( x.negative<y.negative )
     return true;
    else if( x.negative==y.negative )
     return x.positive<y.positive;
    else
     return false;
   }

   inline bool operator==( const NGramScore & x, const NGramScore & y )
   {
    return x.negative==y.negative && x.positive==y.positive;
   }

 }

#endif
