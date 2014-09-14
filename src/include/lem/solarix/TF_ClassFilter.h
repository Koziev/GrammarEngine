#if !defined TF_ClassFilter__H
#define TF_ClassFilter__H

#include <lem/containers.h>
#include <lem/solarix/TokenizationTags.h>

namespace Solarix
{

class TF_ClassFilter : public TokenizationTags
{
 public:
  lem::MCollect<int> allowed_classes;

 public:
  TF_ClassFilter(void) {}

  void AddClass( int iclass );
  virtual int Score( const Word_Form &wf, const Dictionary &dict ) const;
  virtual TokenizationTags* clone(void) const;
};

}
#endif
