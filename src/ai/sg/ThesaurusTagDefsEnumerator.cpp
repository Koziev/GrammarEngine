#include <lem/solarix/ThesaurusStorage.h>
#include <lem/solarix/ThesaurusTagDefs.h>

using namespace Solarix;

ThesaurusTagDefsEnumerator::ThesaurusTagDefsEnumerator( ThesaurusTagDefs *x ) : defs(x), rs(NULL)
{
}


ThesaurusTagDefsEnumerator::~ThesaurusTagDefsEnumerator(void)
{
 lem_rub_off(rs);
 return;
}


bool ThesaurusTagDefsEnumerator::Fetch(void)
{
 if( rs==NULL )
  {
   rs = defs->db->ListTagDefs();
  }

 return rs->Fetch();
}


int ThesaurusTagDefsEnumerator::GetId(void) const
{
 return rs->GetInt(0);
}

lem::UCString ThesaurusTagDefsEnumerator::GetName(void) const
{
 return rs->GetUCString(1);
}

