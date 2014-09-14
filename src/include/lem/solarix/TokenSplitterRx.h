#if !defined TokenSplitterRx__H
#define TokenSplitterRx__H

#include <lem/noncopyable.h>
#include <lem/ucstring.h>
#include <lem/containers.h>
#include <boost/regex.hpp>

namespace Solarix
{
 class LA_PreprocessorTokRule;

 class TokenSplitterRx : lem::NonCopyable
 {
  private:
   bool greedy;
   const boost::wregex * rx_condition;
   const LA_PreprocessorTokRule * source_rule;

  public:
   TokenSplitterRx( const LA_PreprocessorTokRule * rule );

   const LA_PreprocessorTokRule* GetSourceRule() const { return source_rule; }
   bool IsGreedy() const { return greedy; }
   bool Apply( const lem::UCString & word, lem::MCollect<lem::UCString> & result ) const;
 };

}

#endif
