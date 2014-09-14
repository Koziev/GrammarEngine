#include <lem/solarix/sg_autom.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/ThesaurusStorage.h>
#include <lem/solarix/PhraseLinkEnumerator.h>

using namespace Solarix;

PhraseLinkEnumerator::PhraseLinkEnumerator( SG_Net *th )
 : id_phrase1(UNKNOWN), thesaurus(th)
{
 rs = NULL;
 id_phrase1_field=id_phrase2_field=link_type_field=tags_field=UNKNOWN;
 return;
}


PhraseLinkEnumerator::PhraseLinkEnumerator( SG_Net *th, int _id_phrase1 )
 : id_phrase1(_id_phrase1), thesaurus(th)
{
 LEM_CHECKIT_Z( id_phrase1!=UNKNOWN );
 rs = NULL;
 id_phrase1_field=id_phrase2_field=link_type_field=tags_field=UNKNOWN;
 return;
}

PhraseLinkEnumerator::PhraseLinkEnumerator( SG_Net *th, int _id_phrase1, int _link_type )
 : id_phrase1(_id_phrase1), thesaurus(th)
{
 LEM_CHECKIT_Z( id_phrase1!=UNKNOWN );
 LEM_CHECKIT_Z( _link_type!=UNKNOWN );

 link_types.push_back(_link_type);
 rs = NULL;
 id_phrase1_field=id_phrase2_field=link_type_field=tags_field=UNKNOWN;
 return;
}


PhraseLinkEnumerator::PhraseLinkEnumerator( SG_Net *th, int _id_phrase1, const lem::MCollect<int> _link_types )
 : id_phrase1(_id_phrase1), thesaurus(th), link_types(_link_types)
{
 LEM_CHECKIT_Z( id_phrase1!=UNKNOWN );

 rs = NULL;
 id_phrase1_field=id_phrase2_field=link_type_field=tags_field=UNKNOWN;
 return;
}


PhraseLinkEnumerator::~PhraseLinkEnumerator(void)
{
 lem_rub_off(rs);
 return;
}


bool PhraseLinkEnumerator::Fetch(void)
{
 if( rs==NULL )
  {
   if( id_phrase1==UNKNOWN )
    {
     rs = thesaurus->GetStorage().ListPhraseLinks();
     id_phrase1_field=1;
     id_phrase2_field=2;
     link_type_field=4;
     tags_field=5;
    }
   else if( id_phrase1!=UNKNOWN && link_types.empty() )
    {
     rs = thesaurus->GetStorage().ListPhraseLinks(id_phrase1);
     id_phrase2_field=1;
     link_type_field=3;
     tags_field=4;
    }
   else
    {
     rs = thesaurus->GetStorage().ListPhraseLinks(id_phrase1,link_types);
     id_phrase2_field=1;
     link_type_field=3;
     tags_field=4;
    }
  }

 return rs->Fetch();
}


int PhraseLinkEnumerator::GetLinkId(void)
{
 return rs->GetInt(0);
}

int PhraseLinkEnumerator::GetIdPhrase1(void)
{
 if( id_phrase1==UNKNOWN )
  return rs->GetInt( id_phrase1_field );
 else
  return id_phrase1;
}


int PhraseLinkEnumerator::GetIdPhrase2(void)
{
 return rs->GetInt(id_phrase2_field);
}


int PhraseLinkEnumerator::GetLinkType(void)
{
 if( link_types.size()==1 )
  return link_types.front();
 else
  return rs->GetInt(link_type_field);
}

int PhraseLinkEnumerator::GetTagsId(void)
{
 const int id_tags = rs->GetInt(tags_field);
 return id_tags;
}


SG_TagsList PhraseLinkEnumerator::GetTags(void)
{
 const int id_tags = rs->GetInt(tags_field);
 return thesaurus->GetPhraseLinkTags( id_tags, GetLinkId() );
}
