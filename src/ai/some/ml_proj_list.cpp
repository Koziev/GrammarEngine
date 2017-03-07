// -----------------------------------------------------------------------------
// File ML_PROJ_LIST.CPP
//
// (c) Koziev Elijah
//
// Content:
// Класс MLProjList - задание на прокцию мультилексемы Лексическим Автоматом,
// также хранит результаты успешных проекций.
// -----------------------------------------------------------------------------
//
// CD->10.08.1997
// LC->07.01.2012
// --------------

#if defined SOL_CAA

#include <lem/stl.h>
#include <lem/oformatter.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/tree_node.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/ml_projections.h>

using namespace std;
using namespace lem;
using namespace Solarix;


MLProjList::MLProjList( const RC_Lexem &Word, int WordIndex, int WordParts )
:word(Word), word_index(WordIndex), word_parts(WordParts)
{
 changed        = false;
 allow_fuzzy    = false;
 allow_dynforms = false;
 stadia         = 0;
 miss_parameter = 1;
 return;
}

MLProjList::MLProjList( const RC_Lexem &Word, const UCString &Org, int WordIndex, int WordParts )
:word(Word), org_word(Org), word_index(WordIndex), word_parts(WordParts)
{
 changed        = false;
 allow_fuzzy    = false;
 allow_dynforms = false;
 stadia         = 0;
 miss_parameter = 1;
 return;
}


MLProjList::MLProjList( const RC_Lexem &Word, const MCollect<UCString> &Group )
: word(Word), group(Group)
{
 word_index = UNKNOWN;
 word_parts = 1;
 changed        = false;
 allow_fuzzy    = false;
 allow_dynforms = false;
 stadia         = 0;
 miss_parameter = 1;
 return;
}


MLProjList::~MLProjList(void)
{
 ZAP_A(form);
 ZAP_A(extra_inf);
 return;
}


void MLProjList::Delete(void)
{
 ZAP_A(form);
 return;
}


void MLProjList::SetTokenizerFlag( const lem::UFString &flags )
{
 tokenizer_flags = flags;
 return;
}




bool MLProjList::CanAdd( const Word_Coord & Coord, const LA_ProjectInfo * info ) const
{
 if( info==NULL || info->empty() )
  return coord.find(Coord)==UNKNOWN;

 for( Container::size_type i=0; i<coord.size(); i++ )
  if( coord[i] == Coord )
   {
    // совпадает статья и форма. Если координатные пары, заданные в info, тоже совпадут - значит дубль.
    if( extra_inf[i]==NULL )
     {
      return info->empty();
     }
    else if( *extra_inf[i] == *info )
     {
      return false;
     }
   }

 return true;
}


bool MLProjList::Add( const Word_Coord & Coord, const ProjScore & scoring, const LA_ProjectInfo * info )
{
 if( info==NULL || info->empty() )
  {
   for( Container::size_type i=0; i<coord.size(); i++ )
    if( coord[i]==Coord && (extra_inf[i]==NULL || extra_inf[i]->empty()) )
     {
      // Такая проекция уже производилась. Если надежность новой
      // проекции выше, то запомним новую надежность.
      if( coord_val[i].score<scoring.score )
       {
        coord_val[i].score = scoring.score;
        changed=true;
       }

      return false;
     }
  }
 else
  {
   for( Container::size_type i=0; i<coord.size(); i++ )
    if( coord[i] == Coord )
     {
      if( extra_inf[i]==NULL || extra_inf[i]->empty() )
       break;

      if( *extra_inf[i] == *info )
       {
        // Такая проекция уже производилась. Если надежность новой
        // проекции выше, то запомним новую надежность.
        if( coord_val[i].score<scoring.score )
         {
          coord_val[i].score = scoring.score;
          changed=true;
         }

        return false;
       }
     }
  }   

 changed=true;
 coord.push_back(Coord);

 coord_val.push_back(scoring);
 if( info==NULL )
  extra_inf.push_back(NULL);
 else
  extra_inf.push_back( new LA_ProjectInfo(*info) );

 return true;
}


// ***********************************************************
// Распечатываем только мультилексему, которая проецируется.
// Также можеи распечатать список фонетических инвариантов,
// созданных специальным модулем в составе LA.
// ***********************************************************
void MLProjList::PrintHeap( OFormatter &to ) const
{
 to.printf( "Original lexem: %vfE%us%vn\n", word->c_str() );

 if( !phon_inv.empty() )
  {
   // Есть фонетические инварианты, распечатываем ихю
   to.printf( "# of phonetic invariants: %d\n", phon_inv.size() );

   for( Container::size_type i=0; i<phon_inv.size(); i++ )
    to.printf(
              "#W6d [%us] val=%us\n"
              , phon_inv[i]->c_str()
              , to_ustr(pi_val[i]).c_str()
             );
  }

 return;
}


// ***********************************************************
// Печатем детальные результаты проекции (текущее состояние).
// ***********************************************************
void MLProjList::Print( OFormatter &to, bool detailed, const Dictionary *dict ) const
{
 to.printf( "# of projections: %d\n", CastSizeToInt(coord.size()) );

 if( detailed && dict!=NULL )
  {
   for( lem::Container::size_type i=0; i<coord.size(); ++i )
    {
     to.printf( "#%d: id_entry=%d iform=%d ", CastSizeToInt(i), coord[i].GetEntry(), coord[i].GetForm() );
     form[i]->Print( to, &dict->GetSynGram(), detailed );
     to.eol();
    }
  }

 return;
}


// ***************************************
// Сортируем список фонетических мутаций в
// порядке убывания достоверности.
// ***************************************
void MLProjList::SortPhonInv(void)
{
 const int N=CastSizeToInt(phon_inv.size());

 for( int gap=N/2; gap>0; gap/=2 )
  for( int i=gap; i<N; i++ )
   for( int j=i-gap; j>=0; j-=gap )
    {
     if( pi_val[j+gap] < pi_val[j] )
      break;

     std::swap( pi_val[j],   pi_val[j+gap]   );
     boost::swap( phon_inv[j], phon_inv[j+gap] );
    }

 return;
}

Word_Form* MLProjList::GetVersionedForm(void) const
{
 Word_Form *cluster = new Word_Form( *form.front() );
 cluster->SetOriginPos( word_index );
 for( lem::Container::size_type i=1; i<form.size(); ++i )
  {
   Word_Form * alt = new Word_Form( *form[i] );
   alt->SetOriginPos( word_index );
   cluster->AddAlt( alt );
  }

 return cluster;
}

RC_Lexem MLProjList::GetOrgWord(void) const
{
 if( org_word.empty() )
  return word;

 RC_Lexem rc( new Lexem(org_word) );
 return rc;
}




#if defined SOL_CAA
bool MLProjFreq::operator>( const MLProjFreq &x ) const
{
 if( known_entry>x.known_entry )
  return true;

 if( known_entry<x.known_entry )
  return false;

 if( score > x.score )
  return true;

 if( score < x.score )
  return false;

 if( local_freq>x.local_freq )
  return true;

 if( local_freq<x.local_freq )
  return false;

 if( wordform_freq>x.wordform_freq )
  return true;

 if( wordform_freq<x.wordform_freq )
  return false;

 return wordentry_freq > x.wordentry_freq;
}


bool MLProjFreq::operator<( const MLProjFreq &x ) const
{
 if( known_entry<x.known_entry )
  return true;

 if( known_entry>x.known_entry )
  return false;

 if( score < x.score )
  return true;

 if( score > x.score )
  return false;

 if( local_freq<x.local_freq )
  return true;

 if( local_freq>x.local_freq )
  return false;

 if( wordform_freq<x.wordform_freq )
  return true;

 if( wordform_freq>x.wordform_freq )
  return false;

 return wordentry_freq < x.wordentry_freq;
}
#endif


static bool word_freq_sorter( const std::pair<int,MLProjFreq> &x, const std::pair<int,MLProjFreq> &y )
{
 return x.second > y.second;
}

void MLProjList::SortByFrequency( Dictionary &dict )
{
 LexicalAutomat &la = dict.GetLexAuto();
 SynGram &sg = dict.GetSynGram();

 const int iue = la.GetUnknownEntryKey();

 // Отсортируем проекции согласно частотам.
 if( coord.size()>1 )
  {
   LEM_CHECKIT_Z( coord.size()==form.size() );

   lem::MCollect< std::pair<int,MLProjFreq> > freqs;
   for( lem::Container::size_type i=0; i<coord.size(); ++i )
    {
     std::pair<int,MLProjFreq> p;
     p.first = CastSizeToInt(i);
     p.second.score = coord_val[i].score;
     
     const int id_entry = coord[i].GetEntry();
     const int iform = coord[i].GetForm();

     p.second.known_entry = sg.GetUEntries().find( id_entry )==UNKNOWN ? 1 : 0;

     if( id_entry!=UNKNOWN && id_entry!=iue )
      {
       const SG_Entry &e = sg.GetEntry(id_entry);
       p.second.wordentry_freq = e.GetFreq();

       if( iform!=UNKNOWN )
        {
         p.second.wordform_freq = la.GetWordformFrequency( id_entry, iform );
         coord_val[i].score += p.second.wordform_freq;
         form[i]->SetScore( coord_val[i].score );
        }
      }

     freqs.push_back(p);
    }

   if( freqs.size()==2 )
    {
     if( freqs.back().second > freqs.front().second )
      {
       std::swap( coord.front(), coord.back() );
       std::swap( coord_val.front(), coord_val.back() );
       std::swap( extra_inf.front(), extra_inf.back() );
       std::swap( form.front(), form.back() );
      }
    }
   else
    {
     std::sort( freqs.begin(), freqs.end(), word_freq_sorter );

/*
     for( lem::Container::size_type k=0; k<freqs.size(); ++k )
      {
#if LEM_DEBUGGING==1
lem::mout->printf( "freq[%d] known=%d ie=%d\n", k, freqs[k].second.known_entry, coord[ freqs[k].first ].GetEntry() );
#endif
      }
*/
     LEM_CHECKIT_Z( !(freqs.front().second < freqs.back().second ) );

     MCollect<Word_Coord> coord2;
     MCollect<ProjScore> coord_val2;
     lem::MCollect<LA_ProjectInfo*> extra_inf2;
     lem::MCollect<Word_Form*> form2;

     for( lem::Container::size_type k=0; k<freqs.size(); ++k )
      {
       coord2.push_back( coord[ freqs[k].first ] );
       coord_val2.push_back( coord_val[ freqs[k].first ] );
       extra_inf2.push_back( extra_inf[ freqs[k].first ] );
       form2.push_back( form[ freqs[k].first ] );
      }

     for( lem::Container::size_type k=0; k<freqs.size(); ++k )
      {
       coord[k] = coord2[k];
       coord_val[k] = coord_val2[k];
       extra_inf[k] = extra_inf2[k];
       form[k] = form2[k];
      }
    }
  }
 else if( !coord.empty() )
  {
   // вариант распознавания только один, поэтому просто проинициализируем wordform_score, если такая информация есть.
   // Это необходимо в случаях, когда слово - мультилексема, допускающая распознавание также на отдельные слова. Поэтому
   // в графе токенизации мультилексема может быть в единственном варианте, но нам надо взвешивать также варианты разбора.
   const int id_entry = coord.front().GetEntry();
   const int iform = coord.front().GetForm();

   if( id_entry!=UNKNOWN && id_entry!=iue && iform!=UNKNOWN )
    {
     const SG_Entry &e = sg.GetEntry(id_entry);
     int wordform_score = la.GetWordformFrequency( id_entry, iform );
     coord_val.front().score += wordform_score;
     form.front()->SetScore(wordform_score);
    }
  }

 return;
}


void MLProjList::Projected(void)
{
 if( !tokenizer_flags.empty() )
  for( lem::Container::size_type i=0; i<form.size(); ++i )
   {
    form[i]->SetTokenizerFlag( tokenizer_flags );
    form[i]->SetScore( coord_val[i].score );
   }

 return;
}


#endif // defined SOL_CAA
