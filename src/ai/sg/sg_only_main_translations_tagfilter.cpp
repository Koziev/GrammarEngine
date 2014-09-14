#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/sg_only_main_translations_tagfilter.h>

using namespace lem;
using namespace Solarix;


TF_OnlyMainTransl::TF_OnlyMainTransl( const Dictionary &dict )
{
 transl_order_itag = dict.GetSynGram().Get_Net().FindTag(L"transl_order");
 return;
}

bool TF_OnlyMainTransl::Match( SG_TagsList x ) const
{
 // Среди тэгов в списке x либо не должно быть тэга transl_order, либо
 // его значение должно быть 0 или 1.

 if( x==NULL )
  return true;

 for( lem::Container::size_type i=0; i<x->size(); ++i )
  if( x->get(i).first == transl_order_itag )
   {
    if( x->get(i).second>1 )
     return false;
   }

 return true;
}

bool TF_OnlyMainTransl::Empty(void) const
{
 return transl_order_itag!=UNKNOWN;
}




TF_TranslOrderZero::TF_TranslOrderZero( const Dictionary &dict )
{
 transl_order_itag = dict.GetSynGram().Get_Net().FindTag(L"transl_order");
 return;
}

bool TF_TranslOrderZero::Match( SG_TagsList x ) const
{
 if( x==NULL )
  return true;

 // Обязательно должен быть тег с transl_order=0
 for( lem::Container::size_type i=0; i<x->size(); ++i )
  if( x->get(i).first == transl_order_itag )
   {
    if( x->get(i).second==0 )
     return true;
   }

 return false;
}

bool TF_TranslOrderZero::Empty(void) const
{
 return transl_order_itag!=UNKNOWN;
}
