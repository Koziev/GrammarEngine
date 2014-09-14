#include <lem/solarix/PhraseEntries.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/PhraseEnumerator.h>

using namespace Solarix;

PhraseEnumerator::PhraseEnumerator( LS_ResultSet *_rs, int _pk_field, SynGram *_sg )
 : rs(_rs), sg(_sg), pk_field(_pk_field)
{
}


PhraseEnumerator::~PhraseEnumerator(void)
{
 lem_rub_off(rs);
 return;
}

bool PhraseEnumerator::Fetch(void)
{
 return rs->Fetch();
}

int PhraseEnumerator::GetPhraseId(void)
{
 return rs->GetInt(pk_field);
}


void PhraseEnumerator::GetText( lem::UFString &text )
{
 int id = GetPhraseId();
 SG_Phrase frz;
 sg->GetStorage().GetPhrase( id, frz );
 text = frz.GetText();
 return;
}
