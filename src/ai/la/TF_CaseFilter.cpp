#include <lem/solarix/dictionary.h>
#include <lem/solarix/word_form.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/TokenizationTags.h>

using namespace Solarix;


int TF_CaseFilter::Score( const Word_Form &wf, const Dictionary &dict ) const
{
 if( required_casing==UNKNOWN )
  return 0;

 const int ekey = wf.GetEntryKey();
 if( lem::is_quantor(ekey) )
  return 0;

 const SG_Entry & e = dict.GetSynGram().GetEntry(ekey);
 const int id_state = e.GetAttrState(id_CharCasing);
 if( id_state==UNKNOWN )
  {
   // по умолчанию считаем, что слово должно быть в нижнем регистре.
   // нарушение условия - небольшой штраф.
   // Важный тестовый пример с омонимией имени "Ида" и императивом "идти":
   // - Иди!
   return required_casing==id_state_lower ? 0 : -1;
  }

 return id_state==required_casing ? 0 : -1;
}


TokenizationTags* TF_CaseFilter::clone(void) const
{
 TF_CaseFilter *x = new TF_CaseFilter( id_CharCasing, required_casing, id_state_lower );
 return x;
}
