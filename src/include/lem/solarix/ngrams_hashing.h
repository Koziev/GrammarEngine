#ifndef SOLARIX_NGRAMS_HASHING__H
#define SOLARIX_NGRAMS_HASHING__H
#pragma once

 namespace Solarix
 {

  inline lem::uint32_t ngram2hash( int i1, int i2 )
  { return (lem::uint32_t(i1)<<16) ^ (lem::uint32_t(i1)>>16) ^ lem::uint32_t(i2); }

  inline lem::uint32_t ngram3hash( int i1, int i2, int i3 )
  { return (lem::uint32_t(i1)<<16) ^ (lem::uint32_t(i1)>>16) ^ (lem::uint32_t(i2)<<12) ^ (lem::uint32_t(i2)>>18) ^ lem::uint32_t(i3); }

  inline lem::uint32_t ngram4hash( int i1, int i2, int i3, int i4 )
  { return (lem::uint32_t(i1)<<16) ^ (lem::uint32_t(i1)>>16) ^ (lem::uint32_t(i2)<<12) ^
         (lem::uint32_t(i2)>>18) ^ lem::uint32_t(i3) ^ (lem::uint32_t(i4)<<5); }

  inline lem::uint32_t ngram5hash( int i1, int i2, int i3, int i4, int i5 )
  { return (lem::uint32_t(i1)<<16) ^ (lem::uint32_t(i1)>>16) ^ (lem::uint32_t(i2)<<12) ^
         (lem::uint32_t(i2)>>18) ^ lem::uint32_t(i3) ^ (lem::uint32_t(i4)<<5) ^ (lem::uint32_t(i4)<<9) ^
         (lem::uint32_t(i5)>>4); }
 }

#endif

