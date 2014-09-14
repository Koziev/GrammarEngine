#include <lem/solarix/word_form.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/TF_ClassFilter.h>

using namespace Solarix;

void TF_ClassFilter::AddClass( int iclass )
{
 if( iclass!=UNKNOWN )
  allowed_classes.push_back(iclass);

 return;
}

int TF_ClassFilter::Score( const Word_Form &wf, const Dictionary &dict ) const
{
 if( allowed_classes.empty() )
  return 0;

 const int ekey = wf.GetEntryKey();
 if( lem::is_quantor(ekey) )
  return 0;

 const int iclass = dict.GetSynGram().GetEntry(ekey).GetClass();

 return (iclass==UNKNOWN || allowed_classes.find(iclass)!=UNKNOWN) ? 0 : -100;
}

TokenizationTags* TF_ClassFilter::clone(void) const
{
 TF_ClassFilter *x = new TF_ClassFilter;
 x->allowed_classes = allowed_classes;
 return x;
}

