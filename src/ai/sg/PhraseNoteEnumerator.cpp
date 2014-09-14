#include <lem/solarix/PhraseEntries.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/PhraseNoteEnumerator.h>

using namespace Solarix;

PhraseNoteEnumerator::PhraseNoteEnumerator( SynGram *_sg, int _id_phrase )
 : sg(_sg), id_phrase(_id_phrase), rs(NULL)
{
 LEM_CHECKIT_Z( sg!=NULL );
 LEM_CHECKIT_Z( id_phrase!=UNKNOWN );
 return;
}


PhraseNoteEnumerator::~PhraseNoteEnumerator(void)
{
 lem_rub_off(rs);
 return;
}

bool PhraseNoteEnumerator::Fetch(void)
{
 if( rs==NULL )
  {
   rs = sg->GetStorage().ListPhraseNotes(id_phrase);
  }

 return rs->Fetch();
}

int PhraseNoteEnumerator::GetNoteId(void)
{
 return rs->GetInt(0);
}


void PhraseNoteEnumerator::GetNote( SG_PhraseNote &note )
{
 int id = GetNoteId();
 if( !sg->GetStorage().GetPhraseNote( id, note ) )
  {
   LEM_STOPIT;
  }

 return;
}
