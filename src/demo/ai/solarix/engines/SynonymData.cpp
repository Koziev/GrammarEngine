#if defined GM_PHRASE_GENERATOR

#include <lem/solarix/tree_node.h>
#include <lem/solarix/phrase_generator.h>
#include <lem/solarix/SynonymData.h>
#include <lem/solarix/synonymizer_engine.h>

using namespace lem;

SynonymData::SynonymData(void) : ie(UNKNOWN), w(1.0F), dependency_2gram_hits(0), i_center(0)
{}

SynonymData::SynonymData( const SynonymData &x )
: ie(x.ie), i_center(x.i_center), words(x.words), tree(x.tree), right(x.right),
  w(x.w), dependency_2gram_hits(x.dependency_2gram_hits)
{} 

SynonymData::SynonymData( int IE ) : ie(IE), w(1.0F), dependency_2gram_hits(0)
{ i_center=0; }


void SynonymData::operator=( const SynonymData &x )
{
 ie=x.ie;
 i_center=x.i_center;
 words=x.words;
 tree=x.tree;
 right=x.right;
 w = x.w;
 dependency_2gram_hits = x.dependency_2gram_hits;
 return;
}


UFString SynonymData::BuildSubstForNoun(
                                        Solarix::Dictionary & dict,
                                        const UCString & old_word,
                                        const UCString & new_word,
                                        const Solarix::CP_Array & dim0,
                                        const Solarix::SG_EntryForm & f
                                       ) const
{
 lem::MCollect< std::pair<UCString,UCString> > subst;
 subst.push_back( std::make_pair(words[i_center],new_word) );

 Solarix::SynGram &sg = dict.GetSynGram();

 // Кроме замены собственно существительного, надо пересогласовать связанные с ним прилагательные

 for( lem::Container::size_type i=0; i<tree->leafs().size(); ++i )
  {
   const Solarix::Tree_Node &l = tree->leafs()[i];
   const Solarix::Word_Form &wf = l.GetNode();

   int ekey = l.GetNode().GetEntryKey();
   if( !lem::is_quantor(ekey) )
    {
     const Solarix::SG_Entry &le = sg.GetEntry(ekey);
     if( le.GetClass()==ADJ_ru )
      {
       // Надо заменить форму прилагательного, взяв падеж и число у существительного
       
       Solarix::CP_Array dim;

       // У старой формы прилагательного возьмем все координаты, кроме падежа и числа.

       int case1 = UNKNOWN;
       for( lem::Container::size_type p=0; p<dim0.size(); ++p )
        {
         const Solarix::GramCoordPair &x = dim0[p];
         if( x.GetCoord().GetIndex()==CASE_ru )
          {
           dim.push_back(x);
           case1 = x.GetState();
          }
         else if( x.GetCoord().GetIndex()==NUMBER_ru )
          {
           dim.push_back(x);
          }
        }

       const int gender0 = wf.GetState( Solarix::GramCoordAdr(GENDER_ru) );
       const int form0 = wf.GetState( Solarix::GramCoordAdr(COMPAR_FORM_ru) );
       const int shortness0 = wf.GetState( Solarix::GramCoordAdr(SHORTNESS_ru) );

       dim.push_back( Solarix::GramCoordPair( GENDER_ru, gender0 ) );
       dim.push_back( Solarix::GramCoordPair( COMPAR_FORM_ru, form0 ) );
       dim.push_back( Solarix::GramCoordPair( SHORTNESS_ru, shortness0 ) );

       // Для винительного падежа надо обязательно брать туже одушевленность
       if( case1==ACCUSATIVE_CASE_ru )
        {
         const int anim0 = wf.GetState( Solarix::GramCoordAdr(FORM_ru) );
         if( anim0!=UNKNOWN )
          {
           dim.push_back( Solarix::GramCoordPair( FORM_ru, anim0 ) );
          }
        } 

       // Ищем такую форму 
       int iform = le.FindFormIndex(dim);

       // Нашли?
       if( iform!=UNKNOWN )
        { 
         const Solarix::SG_EntryForm& f = le.forms()[iform];
         const lem::UCString &form2 = f.name();
         subst.push_back( std::make_pair( *l.GetNode().GetName(), form2 ) );
        } 
      }
    }
  }

 UFString ret;
 SubstSynonyms( ret, subst );
 return ret;
}



UFString SynonymData::BuildSubstForAdj(
                                       Solarix::Dictionary & dict,
                                       const UCString & old_word,
                                       const UCString &new_word,
                                       const Solarix::CP_Array &dim,
                                       const Solarix::SG_EntryForm& f
                                      ) const
{
 lem::MCollect< std::pair<UCString,UCString> > subst;
 subst.push_back( std::make_pair(words[i_center],new_word) );

 // TODO: теоритически возможно, что синоним будет давать замену на И- или ИЛИ- конструкцию.
 // Поэтому тут надо бы немного проанализировать структуру синтаксического графа.
 // ...

 UFString ret;
 SubstSynonyms( ret, subst );
 return ret;
}


UFString SynonymData::BuildSubstForVerb(
                                        Solarix::Dictionary & dict,
                                        const UCString & old_word,
                                        const UCString &new_word,
                                        const Solarix::CP_Array &dim,
                                        const Solarix::SG_EntryForm& f
                                       ) const
{
 lem::MCollect< std::pair<UCString,UCString> > subst;
 subst.push_back( std::make_pair(words[i_center],new_word) );

 // TODO: теоретически возможно, что синоним будет давать замену на И- или ИЛИ- конструкцию.
 // Поэтому тут надо бы немного проанализировать структуру синтаксического графа.
 // ...

 UFString ret;
 SubstSynonyms( ret, subst );
 return ret;
}



UFString SynonymData::BuildSubstForOther(
                                         Solarix::Dictionary & dict,
                                         const UCString & old_word,
                                         const UCString &new_word
                                        ) const
{
 lem::MCollect< std::pair<UCString,UCString> > subst;
 subst.push_back( std::make_pair(words[i_center],new_word) );
 UFString ret;
 SubstSynonyms( ret, subst );
 return ret;
}



void SynonymData::SubstSynonyms(
                                lem::UFString &result,
                                const lem::MCollect< std::pair<lem::UCString,lem::UCString> >& subst
                               ) const
{
 result.clear();

 for( lem::Container::size_type i=0; i<words.size(); ++i )
  {
   if( !result.empty() )
    result += L' ';

   bool match=false;
   for( lem::Container::size_type j=0; j<subst.size(); ++j )
    {
     if( words[i].eqi( subst[j].first ) )
      {
       result += subst[j].second.c_str();
       match=true;
       break;
      }
    }

   if( !match )
    result += words[i].c_str();
  }

 result.to_lower();

 return; 
}

#endif
