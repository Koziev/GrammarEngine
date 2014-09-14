// CD->05.09.2014

#include <lem/solarix/pm_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/variator.h>
#include <lem/solarix/LA_SynPatternTrees.h>
#include <lem/solarix/BackTrace.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/TreeMatchingExperience.h>
#include <lem/solarix/SynPattern.h>
#include <lem/solarix/BasicLexer.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/ElapsedTimeConstraint.h>
#include <lem/solarix/SynPatternTreeNodeMatchingResults.h>


using namespace lem;
using namespace Solarix;


SynPatternTreeNode::SynPatternTreeNode(void) : bottomup(false)
{
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
SynPatternTreeNode::SynPatternTreeNode( const lem::MCollect<SynPatternPoint*> & points ) : bottomup(false)
{
 point.push_back( new SynPatternPoint( * points.front() ) );
 leaf.push_back( new SynPatternTreeNode( points, 0 ) );
 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
SynPatternTreeNode::SynPatternTreeNode( const lem::MCollect<SynPattern*> & patterns ) : bottomup(false)
{
 // Строим префиксное дерево для паттернов в заданном списке
 for( lem::Container::size_type i=0; i<patterns.size(); ++i )
  {
   const SynPattern &p = * patterns[i];

   const lem::PtrCollect<SynPatternPoint> & chain = p.GetPointChain();
   if( !chain.empty() )
    {
     // Для начальной точки уже есть ветка?
     bool found=false;
     for( lem::Container::size_type j=0; j<point.size(); ++j )
      if( point[j]->Equal( * chain.front() ) )
       {
        point[j]->Merge( * chain.front() );
        leaf[j]->Merge( p, 0 );
        found = true;
        break;
       }
   
     if( !found )
      {
       point.push_back( new SynPatternPoint( * chain.front() ) );
       leaf.push_back( new SynPatternTreeNode(p,0) );
      }
    }
  }

 // Отсортируем ветки так, чтобы сначала шли и проверялись самые детальные
 // точки - по принципу дерева исключений.
 
 const int N=CastSizeToInt(point.size());

 for( int gap=N/2; gap>0; gap/=2 )
  for( int i=gap; i<N; i++ )
   for( int j=i-gap; j>=0; j-=gap )
    {
     SynPatternPoint *a = point[j+gap];
     SynPatternPoint *b = point[j];

     if( *a < *b )
      break;
     else
      {
       point[j]     = a;
       point[j+gap] = b;

       SynPatternTreeNode *ta = leaf[j+gap];
       SynPatternTreeNode *tb = leaf[j];

       leaf[j] = ta;
       leaf[j+gap] = tb;
      }
    }


 LEM_CHECKIT_Z( point.size() == leaf.size() );

 #if LEM_DEBUGGING==1
 for( lem::Container::size_type i=0; i<leaf.size(); ++i )
  {
   LEM_CHECKIT_Z( leaf[i]!=NULL );
  }
 #endif

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
SynPatternTreeNode::SynPatternTreeNode( const lem::MCollect<SynPatternPoint*> & points, int ipoint ) : bottomup(false)
{
 if( ipoint+1 < CastSizeToInt(points.size()) )
  {
   const SynPatternPoint &p = * points[ipoint+1];
   point.push_back( new SynPatternPoint(p) );
   leaf.push_back( new SynPatternTreeNode( points, ipoint+1 ) );
  }

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
SynPatternTreeNode::SynPatternTreeNode( const SynPattern & pattern, int ipoint ) : bottomup(false)
{
 // Начиная с ipoint+1го узла в паттерне строим ветки
 if( ipoint+1 < CastSizeToInt(pattern.GetPointChain().size()) )
  {
   const SynPatternPoint &p = * pattern.GetPointChain()[ipoint+1];

   point.push_back( new SynPatternPoint(p) );
   leaf.push_back( new SynPatternTreeNode( pattern, ipoint+1 ) );
  }

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynPatternTreeNode::Merge( const SynPattern & pattern, int ipoint )
{
 if( ipoint+1 < CastSizeToInt(pattern.GetPointChain().size()) )
  {
   const SynPatternPoint &p = * pattern.GetPointChain()[ipoint+1];

   bool found=false;
   for( lem::Container::size_type i=0; i<point.size(); ++i )
    if( point[i]->Equal(p) )
     {
      found = true;
      point[i]->Merge(p);
      leaf[i]->Merge( pattern, ipoint+1 );     
      break;
     }

   if( !found )
    {
     point.push_back( new SynPatternPoint(p) );
     leaf.push_back( new SynPatternTreeNode(pattern,ipoint+1) );
    }
  }

 return;
}
#endif



#if defined SOL_SAVEBIN
void SynPatternTreeNode::SaveBin( lem::Stream& bin ) const
{
 bin.write_bool( bottomup );
 point.SaveBin(bin);
 leaf.SaveBin(bin);
 return;
}
#endif


#if defined SOL_LOADBIN 
void SynPatternTreeNode::LoadBin( lem::Stream& bin )
{
 bottomup = bin.read_bool();
 point.LoadBin(bin);
 leaf.LoadBin(bin);

 LEM_CHECKIT_Z( point.size()==leaf.size() );

 return;
}

void SynPatternTreeNode::Link( const TrFunctions &funs )
{
 for( lem::Container::size_type i=0; i<point.size(); ++i )
  point[i]->Link(funs);

 for( lem::Container::size_type j=0; j<leaf.size(); ++j )
  leaf[j]->Link(funs);

 return;
}
#endif




#if defined SOL_CAA && !defined SOL_NO_AA
static void Append(
                   std::multimap< const Word_Form*, int /*iversion*/ > &dst,
                   const std::multimap< const Word_Form*, int /*iversion*/ > &src
                  )
{
 for( std::multimap< const Word_Form*, int >::const_iterator it=src.begin(); it!=src.end(); ++it )
  dst.insert( *it );

 return;  
}

static void Append(
                   std::multimap< int, int > &dst,
                   const std::multimap< int, int > &src
                  )
{
 for( std::multimap< int, int >::const_iterator it=src.begin(); it!=src.end(); ++it )
  dst.insert( *it );

 return;  
}

static void Append(
                   lem::MCollect< std::pair<const Solarix::Word_Form *,const Solarix::Word_Form *> > &dst,
                   const lem::MCollect< std::pair<const Solarix::Word_Form *,const Solarix::Word_Form *> > &src
                  )
{
 std::copy( src.begin(), src.end(), std::back_inserter(dst) );
 return;
}


static void Append(
                   lem::MCollect< lem::triple<const Solarix::Word_Form *,int,const Solarix::Word_Form *> > &dst,
                   const lem::MCollect< lem::triple<const Solarix::Word_Form *,int,const Solarix::Word_Form *> > &src
                  )
{
 std::copy( src.begin(), src.end(), std::back_inserter(dst) );
 return;
}

static void Append(
                   lem::MCollect< std::pair<const lem::UCString*,const Word_Form*> > &dst,
                   const lem::MCollect< std::pair<const lem::UCString*,const Word_Form*> > & src
                  )
{
 std::copy( src.begin(), src.end(), std::back_inserter(dst) );
 return;
}


static void Append( LINKAGE_GROUPS & dst, const LINKAGE_GROUPS & src )
{
 std::copy( src.begin(), src.end(), std::back_inserter(dst) );
 return;
}

static void Append( LINKAGE_EDGES & dst, const LINKAGE_EDGES & src )
{
 std::copy( src.begin(), src.end(), std::back_inserter(dst) );
 return;
}



#if defined SOL_DEBUGGING
static void Append( SYNPATTERN_DEBUG_TRACE & dst, const SYNPATTERN_DEBUG_TRACE & src )
{
 std::copy( src.begin(), src.end(), std::back_inserter(dst) );
 return;
}
#endif





struct BestResults : lem::NonCopyable
{
 lem::PtrCollect<EXPORTED_COORDS> best_exported_coords;
 lem::PtrCollect<MATCHING_ALTS> best_matching_alts;
 lem::PtrCollect<EXPORTED_NODES> best_exported_nodes;
 lem::PtrCollect<LINKAGE_GROUPS> best_linkage_groups;
 lem::PtrCollect<LINKAGE_EDGES> best_linkage_edges;
 lem::PtrCollect<BackTrace> best_backtrace;
 lem::MCollect<int> matching_len;
 lem::MCollect<NGramScore> ngram_freqs;
 lem::MCollect<const LexerTextPos*> start_token;
 lem::MCollect<const LexerTextPos*> final_token;

 #if defined SOL_DEBUGGING
 lem::PtrCollect<SYNPATTERN_DEBUG_TRACE> best_debug_trace;
 #endif

 void Clear(void)
 {
  best_exported_coords.clear();
  best_matching_alts.clear();
  best_backtrace.clear();
  matching_len.clear();
  best_exported_nodes.clear();
  best_linkage_groups.clear();
  best_linkage_edges.clear();
  ngram_freqs.clear();
  start_token.clear();
  final_token.clear();

  #if defined SOL_DEBUGGING
  best_debug_trace.clear();
  #endif

  return;
 }
};


namespace {
/*
static bool result_sorter( const SynPatternResult * x, const SynPatternResult * y )
{
 if( x->res.Length() > y->res.Length() )
  return true;

 if( x->res.Length() < y->res.Length() )
  return false;

 return x->res.GetNGramFreq().Composite() > y->res.GetNGramFreq().Composite();
}
*/

static bool result_sorter_len_score( const SynPatternResult * x, const SynPatternResult * y )
{
 if( x->res.Length() > y->res.Length() )
  return true;

 if( x->res.Length() < y->res.Length() )
  return false;

 return x->res.GetNGramFreq().Composite() > y->res.GetNGramFreq().Composite();
}

static bool result_sorter_score( const SynPatternResult * x, const SynPatternResult * y )
{
 return x->res.GetNGramFreq().Composite() > y->res.GetNGramFreq().Composite();
}


static bool desc_len( int x, int y )
{
 return x > y;
}
}

void SynPatternTreeNode::Limit(
                               BasicLexer & lexer,
                               lem::PtrCollect<SynPatternResult> & results,
                               SynGram & sg
                              ) const
{
 const int MAX_COUNT = lexer.GetParams().timeout.max_alt;

 #if LEM_DEBUGGING==1
 if( MAX_COUNT>0 && results.size()==77 )
 #else
 if( MAX_COUNT>0 && results.size()>MAX_COUNT )
 #endif
  {
/*
   #if LEM_DEBUGGING==1
   lem::mout->printf( "n=%d\n", results.size() );
   #endif

   SynPatternResult::SelectUnique( results );

   #if LEM_DEBUGGING==1
   lem::mout->printf( "n=%d\n", results.size() );
   #endif
*/

   int max_len=-1;
   Solarix::NGramScore max_score;
   max_score.SetMinInfinite();

   lem::PtrCollect< lem::MCollect<const SynPatternResult*> > gc_res;
   typedef std::map<int,lem::MCollect<const SynPatternResult*>*> LEN2RES;
   LEN2RES len2res;
   lem::MCollect<int> lens;

   for( int k=0; k<results.size(); ++k )
    {
     const SynPatternResult * r = results[k];
     const int res_len = r->res.Length();
     max_len = std::max( max_len, res_len );

     if( r->res.GetNGramFreq() > max_score )
      max_score = r->res.GetNGramFreq();

     LEN2RES::iterator it = len2res.find(res_len);

     if( it==len2res.end() )
      {
       lem::MCollect<const SynPatternResult*> * l = new lem::MCollect<const SynPatternResult*>();
       gc_res.push_back( l );
       l->push_back( r );
       len2res.insert( std::make_pair( res_len, l ) );
       lens.push_back(res_len);
      }
     else
      {
       it->second->push_back(r);
      }
    }

   std::sort( lens.begin(), lens.end(), desc_len );

   // теперь список для каждой длины - отсортируем по убыванию достоверности
   for( lem::Container::size_type i=0; i<lens.size(); ++i )
    {
     const int res_len = lens[i];
     lem::MCollect<const SynPatternResult*> * rx = len2res.find(res_len)->second;

     #if LEM_DEBUGGING==1
//     lem::mout->printf( "results for len=%d, before selecting unique: count=%d ", res_len, rx->size() );
     #endif

     SynPatternResult::SelectUnique_WithoutRemoval( *rx );
     std::sort( rx->begin(), rx->end(), result_sorter_score );

/*
     #if LEM_DEBUGGING==1
     lem::mout->printf( ", after: count=%d\n", rx->size() );

     for( int k=0; k<rx->size(); ++k )
      {
       lem::mout->printf( "#%d: score=%d len=%d\n", k, rx->get(k)->res.GetNGramFreq().Composite(), rx->get(k)->res.Length() );
  
       const SynPatternResult * r = rx->get(k);
       r->Print( *lem::mout, sg );
       lem::mout->eol();
       r->PrintLinks( *lem::mout, sg ); 
       lem::mout->eol();
      }
  
     lem::mout->eol();
     #endif
*/
    }

   // теперь начинаем переносить в итоговый список
   std::set<const SynPatternResult*> final_results;

   int rest_count = MAX_COUNT;

   // если среди результатов есть такой, что он имеет максимальную достоверность - то сразу добавим его, по 1 из каждой длины.
   // по идее, это гарантирует, что даже короткий, но достоверный результат попадет в итоговый список.
   // при этом мы начинаем поиск таких коротких достоверных не с самой большой длины, а со второй в списке по убыванию.
   int count_for_maxscored=rest_count/2;
   for( lem::Container::size_type i=1; i<lens.size() && count_for_maxscored>0; ++i )
    {
     lem::MCollect<const SynPatternResult*> * len_res = len2res[ lens[i] ];
     if( !len_res->empty() && len_res->front()->res.GetNGramFreq() == max_score )
      {
       final_results.insert( len_res->front() );
       len_res->Remove(0);
       --count_for_maxscored;
       --rest_count;
      }
    }


   int ilen=0;
   while( rest_count>0 && ilen<lens.size() )
   {
    const int cur_len = lens[ilen];
    lem::MCollect<const SynPatternResult*> * len_res = len2res[cur_len];
    if( !len_res->empty() )
     {
      int len_count = rest_count/2 + rest_count%2; // из текущей длины берем столько элементов, чтобы они заполнили только половину оставшегося лимита
      lem::Container::size_type j=0;
      while( len_count>0 && j<len_res->size() )
       {
        if( len_res->get(j)!=NULL )
         {
          final_results.insert( len_res->get(j) );
          rest_count--;
          (*len_res)[j] = NULL;
          --len_count;
         }
        
        ++j;
       }
     }

    ++ilen;
   }

   // если лимит не вычерпан, но добавляем самые достоверные среди оставшихся
   if( rest_count>0 )
    {
     lem::MCollect<const SynPatternResult*> x;
     for( lem::Container::size_type i=0; i<gc_res.size(); ++i )
      {
       lem::MCollect<const SynPatternResult*> * rx = gc_res[i];
       for( lem::Container::size_type j=0; j<rx->size(); ++j )
        {
         if( rx->get(j)!=NULL )
          x.push_back( rx->get(j) );
        }
      }
     
     std::sort( x.begin(), x.end(), result_sorter_score );
     for( int i=0; i<rest_count && i<x.size(); ++i )
      {
       final_results.insert( x[i] );
      }
    }

   // оставляем в результатах только отобранные
   for( int i=CastSizeToInt(results.size())-1; i>=0; --i )
    if( final_results.find(results[i])==final_results.end() )
     results.Remove(i);

 
   // наконец, итоги отсортируем так, чтобы сначала шли самые длинные
   std::sort( results.begin(), results.end(), result_sorter_len_score );

   LEM_CHECKIT_Z( results.size()<=MAX_COUNT );

/*
   std::sort( results.begin(), results.end(), result_sorter );
   results.resize( MAX_COUNT );
*/

/*
   #if LEM_DEBUGGING==1
   for( int k=0; k<results.size(); ++k )
    {
     lem::mout->printf( "#%d: score=%d len=%d\n", k, results[k]->res.GetNGramFreq().Composite(), results[k]->res.Length() );

     const SynPatternResult * r = results[k];
     r->Print( *lem::mout, sg );
     lem::mout->eol();
    }

   lem::mout->eol();
   #endif
*/
  }

 return;
}


bool SynPatternTreeNode::MatchTree(
                                   int id_tree,
                                   PM_Automat &pm,
                                   SynGram &sg,
                                   TreeMatchingExperience & experience,
                                   const ElapsedTimeConstraint & constraints,
                                   LA_SynPatternTrees & named_filters,
                                   WordEntrySet & wordentry_sets,
                                   BasicLexer & lexer,
                                   const LexerTextPos * current_token,
                                   const BackTrace * parent_trace,
                                   const SynPatternResultBackTrace * x_result,
                                   bool greedy,
                                   bool can_skip_outer_tokens,
                                   lem::PtrCollect<SynPatternResult> & results,
                                   TrTrace * trace_log
                                  ) const
{
 if( bottomup )
  {
   int max_matched_len=0;

   std::set<int> CachedHashes;
   lem::MCollect<int> StoredResultHashes;
   lem::PtrCollect<SynPatternResult> StoredResults;

   // повторяем сопоставление, пока увеличивается максимальная длина сопоставленного участка.
   while( !constraints.Exceeded() )
   {
    int old_max_matched_len=max_matched_len;

    // TODO: не нужно ли на каждом проходе создавать новый BackTrace?
    lem::PtrCollect<SynPatternResult> pass_results;
    bool tree_matching = Match(
                               id_tree, // для предотвращения бесконечной левой рекурсии
                               pm,
                               sg,
                               experience,
                               constraints,
                               named_filters,
                               wordentry_sets,
                               lexer,
                               current_token,
                               parent_trace,
                               x_result,
                               greedy,
                               can_skip_outer_tokens,
                               pass_results,
                               trace_log
                              );

    bool changed=false;
    for( lem::Container::size_type q=0; q<pass_results.size(); ++q )
     if( pass_results[q]->res.Length() > max_matched_len )
      {
       changed=true;
       max_matched_len = pass_results[q]->res.Length();
       break;
      }

    if( !changed )
     {
      Limit( lexer, pass_results, sg );

      for( lem::Container::size_type q=0; q<pass_results.size(); ++q )
       {
        results.push_back( pass_results[q] );
        pass_results[q] = NULL;
       }
      
      break;
     }
    else
     {
      // обновляем кэш.
      if( old_max_matched_len==0 )
       {
        experience.Add(id_tree,current_token,true,pass_results);
       }
      else
       {
        for( lem::Container::size_type q=0; q<pass_results.size(); ++q )
         {
          bool stored=false;
          const int h = pass_results[q]->CalcHash();

          if( pass_results[q]->res.Length() > old_max_matched_len )
           {
            // без доп. проверок добавляем те, которые длинее ранее найденных.
            experience.Update(id_tree,current_token,true,*pass_results[q]);
            stored = true;
           }
          else
           {
            // остальные - проверяем на уникальность. 
            if( CachedHashes.find(h)==CachedHashes.end() )
             {
              // раз такого хеша нет, то гарантированно это новый результат.
              experience.Update(id_tree,current_token,true,*pass_results[q]);
              stored = true;
             }
            else
             {
              // есть совпадение хэша - придется проверять с каждым из сохраненных результатов
              bool found=false;
              for( lem::Container::size_type z=0; z<StoredResults.size(); ++z )
              {
               if( StoredResultHashes[z] == h && SynPatternResult::Equals( StoredResults[z], pass_results[q] ) )
                {
                 // нашли точное совпадение
                 found=true;
                 break;
                }
              }

              if( !found )
               {
                experience.Update(id_tree,current_token,true,*pass_results[q]);
                stored = true;
               }
             }
           }

          if( stored )
           {
            CachedHashes.insert(h);
            StoredResultHashes.push_back(h);
            StoredResults.push_back(pass_results[q]);
            pass_results[q] = NULL;
           }
         }
       }
     }
   }
 
   return max_matched_len>0;
  }
 else
  {
   return Match(
                UNKNOWN,
                pm,
                sg,
                experience,
                constraints,
                named_filters,
                wordentry_sets,
                lexer,
                current_token,
                parent_trace,
                x_result,
                greedy,
                can_skip_outer_tokens,
                results,
                trace_log
               );
  }
}


bool SynPatternTreeNode::Match(
                               int banned_id_tree,
                               PM_Automat &pm,
                               SynGram &sg,
                               TreeMatchingExperience &experience,
                               const ElapsedTimeConstraint & constraints,
                               LA_SynPatternTrees &named_filters,
                               WordEntrySet & wordentry_sets,
                               BasicLexer & lexer,
                               const LexerTextPos * current_token,
                               const BackTrace * parent_trace,
                               const SynPatternResultBackTrace * x_result,
                               bool greedy,
                               bool can_skip_outer_tokens,
                               lem::PtrCollect<SynPatternResult> &results,
                               TrTrace *trace_log
                              ) const
{
 bool point_matches=false;
 int max_len=0;
 NGramScore max_ngram_freq(0);

 BestResults *best_results=NULL;

 for( lem::Container::size_type i=0; i<point.size(); ++i )
  {
   // Ищем подходящую ветку для синтаксемы wf

   lem::PtrCollect<SynPatternResult> subresults;

   const SynPatternPoint * checking_point = point[i];

   const bool x=checking_point->Equal(
                                      banned_id_tree,
                                      pm,
                                      sg,
                                      experience,
                                      constraints,
                                      current_token,
                                      lexer,
                                      parent_trace,
                                      x_result,
                                      named_filters,
                                      wordentry_sets,
                                      greedy,
                                      false,
                                      can_skip_outer_tokens,
                                      subresults,
                                      trace_log
                                     );


   if( x )
    {
     // может быть несколько альтернативных вариантов сопоставления с разной
     // длиной совпавшего контекста.

     Limit( lexer, subresults, sg );

     bool any_y_matched=false;

     for( lem::Container::size_type q=0; q<subresults.size(); ++q )
      {
       lem::PtrCollect<SynPatternResult> subresults2;

       SynPatternResult & xres = * subresults[q];

       SynPatternResultBackTrace x2trace( x_result, &xres );

       if( !greedy && point[i]->IsTerminator() )
        {
         // Сопоставленная точка является в одном из вариантов паттерна терминатором,
         // там что мы можем оборвать сопоставление на ней и включить это как один из
         // вариантов сопоставления паттерна.
         point_matches=true;

         const int len2 = xres.res.Length();

         if( best_results==NULL )
          best_results = new BestResults();

         // добавляем новую альтернативу.

         #if defined SOL_DEBUGGING
         SYNPATTERN_DEBUG_TRACE * debug_trace = new SYNPATTERN_DEBUG_TRACE;
         Append( *debug_trace, xres.debug_trace );
         best_results->best_debug_trace.push_back( debug_trace );
         #endif

         MATCHING_ALTS *matching_alts = new MATCHING_ALTS();
         Append( *matching_alts, xres.matched_alts );
         best_results->best_matching_alts.push_back(matching_alts);

         EXPORTED_COORDS *exported_coords=NULL;
         if( !xres.exported_coords.empty() )
          {
           exported_coords = new EXPORTED_COORDS();
           Append( *exported_coords, xres.exported_coords );
          }
         best_results->best_exported_coords.push_back(exported_coords);

         EXPORTED_NODES *exported_nodes = NULL;
         if( !xres.exported_nodes.empty() )
          {
           exported_nodes = new EXPORTED_NODES( xres.exported_nodes );
          }
         best_results->best_exported_nodes.push_back(exported_nodes);

         LINKAGE_GROUPS * linkage_groups = NULL;
         if( !xres.linkage_groups.empty() )
          linkage_groups = new LINKAGE_GROUPS(xres.linkage_groups);
         best_results->best_linkage_groups.push_back( linkage_groups );

         LINKAGE_EDGES * linkage_edges = NULL;
         if( !xres.linkage_edges.empty() )
          linkage_edges = new LINKAGE_EDGES(xres.linkage_edges);
         best_results->best_linkage_edges.push_back( linkage_edges );


         BackTrace *backtrace = new BackTrace();
         xres.trace.CollectAll( backtrace );
         best_results->best_backtrace.push_back( backtrace );

         best_results->start_token.push_back( xres.res.GetStartToken() );
         best_results->final_token.push_back( xres.res.GetFinalToken() );
         best_results->matching_len.push_back(len2);
         best_results->ngram_freqs.push_back( xres.res.GetNGramFreq() );
        }

       lem::MCollect<const LexerTextPos*> next_tokens;

       if( xres.res.Length()==0 ) // сопоставление нулевой длины - функции @optional или @coalesce
        {
         const LexerTextPos * x_start = xres.res.GetStartToken(); // на этом токене закончено сопоставление x-точки.
         next_tokens.push_back( x_start );
        }
       else
        {
         const LexerTextPos * x_final = xres.res.GetFinalToken(); // на этом токене закончено сопоставление x-точки.
         // Получим токены справа от этого токена.
         lexer.Fetch( x_final, next_tokens );
        }

       for( lem::Container::size_type itoken=0; itoken<next_tokens.size(); ++itoken )
        {
         const LexerTextPos * y_token = next_tokens[itoken];

         bool y=false;

         if( !y_token->IsBeyondRight() && !y_token->IsTerminator() )
          y = leaf[i]->Match(
                             banned_id_tree,
                             pm,
                             sg,
                             experience,
                             constraints,
                             named_filters,
                             wordentry_sets,
                             lexer,
                             y_token,
                             & xres.trace,
                             & x2trace,
                             greedy,
                             true,
                             subresults2,
                             trace_log
                            );
   
         if( y )
          {
           for( lem::Container::size_type t=0; t<subresults2.size(); ++t )
            {
             SynPatternResult &yres = * subresults2[t];
        
             point_matches=true;
        
             const int len2 = xres.res.Length() + yres.res.Length();
             const NGramScore ngram_freq_sum( xres.res.GetNGramFreq(), yres.res.GetNGramFreq() );
        
             if( len2>=max_len || !greedy )
              {
               if( best_results==NULL )
                best_results = new BestResults();
        
               if( (len2>max_len || (len2==max_len && ngram_freq_sum>max_ngram_freq)) && greedy )
                {
                 // новый результат длинее предыдущих, забываем про старые.
                 best_results->Clear();
                }
        
               // добавляем новую альтернативу.
        
               #if defined SOL_DEBUGGING
               SYNPATTERN_DEBUG_TRACE * debug_trace = new SYNPATTERN_DEBUG_TRACE(xres.debug_trace);
               Append( *debug_trace, yres.debug_trace );
               best_results->best_debug_trace.push_back( debug_trace );
               #endif


               MATCHING_ALTS *matching_alts = new MATCHING_ALTS();
               Append( *matching_alts, xres.matched_alts );
               Append( *matching_alts, yres.matched_alts ); 
               best_results->best_matching_alts.push_back(matching_alts);


               EXPORTED_COORDS *exported_coords = NULL;
               if( !xres.exported_coords.empty() || !yres.exported_coords.empty() )
                {
                 exported_coords = new EXPORTED_COORDS();
                 Append( *exported_coords, xres.exported_coords );
                 Append( *exported_coords, yres.exported_coords );
                }
               best_results->best_exported_coords.push_back(exported_coords);
        
        
               EXPORTED_NODES *exported_nodes = NULL;
               if( !xres.exported_nodes.empty() || !yres.exported_nodes.empty() )
                {
                 exported_nodes = new EXPORTED_NODES( xres.exported_nodes );
                 Append( *exported_nodes, yres.exported_nodes );
                }
               best_results->best_exported_nodes.push_back( exported_nodes );
        
        
               LINKAGE_GROUPS * linkage_groups = NULL;
               if( !xres.linkage_groups.empty() || !yres.linkage_groups.empty() )
                {
                 linkage_groups = new LINKAGE_GROUPS( xres.linkage_groups );
                 Append( *linkage_groups, yres.linkage_groups );
                }
               best_results->best_linkage_groups.push_back( linkage_groups );
        
               LINKAGE_EDGES * linkage_edges = NULL;
               if( !xres.linkage_edges.empty() || !yres.linkage_edges.empty() )
                {
                 linkage_edges = new LINKAGE_EDGES( xres.linkage_edges );
                 Append( *linkage_edges, yres.linkage_edges );
                }
               best_results->best_linkage_edges.push_back( linkage_edges );
        
        
               BackTrace *backtrace = new BackTrace();
               yres.trace.CollectAll( backtrace );
               best_results->best_backtrace.push_back( backtrace );
        
               best_results->start_token.push_back( xres.res.GetStartToken() );

               //LEM_CHECKIT( yres.res.Length()>0 ) // непонятно, что делать - видимо, @optional или @coalesce в конце списка термов правила
               //best_results->final_token.push_back( yres.res.GetFinalToken() ); // ???
               if( yres.res.Length()==0 )
                {
                 if( xres.res.Length()==0 )
                  best_results->final_token.push_back( xres.res.GetStartToken()->GetPrev() );
                 else
                  best_results->final_token.push_back( xres.res.GetFinalToken() );
                }
               else
                {
                 best_results->final_token.push_back( yres.res.GetFinalToken() );
                }

               best_results->matching_len.push_back( len2 );
               best_results->ngram_freqs.push_back( ngram_freq_sum );
        
               max_len = std::max( max_len, len2 );
               max_ngram_freq = ngram_freq_sum;
        
               any_y_matched = true;
              }
            }
          }
         else if( point[i]->IsTerminator() && greedy )
          {
           // сопоставление дальше вправо не пошло, но наша точка является терминирующей
           // в одном из паттернов, так что можем считать, что нашли успешное сопоставление.
           point_matches=true;
      
           const int len2 = xres.res.Length();
      
           if( (len2 >= max_len) || !greedy )
            {
             if( best_results==NULL )
              best_results = new BestResults();
      
             if( (len2>max_len || (len2==max_len && xres.res.GetNGramFreq()>max_ngram_freq) ) && greedy )
              {
               // новый результат длинее предыдущих, забываем про старые.
               best_results->Clear();
              }
      
             // добавляем новую альтернативу.
      
             #if defined SOL_DEBUGGING
             SYNPATTERN_DEBUG_TRACE * debug_trace = new SYNPATTERN_DEBUG_TRACE(xres.debug_trace);
             best_results->best_debug_trace.push_back( debug_trace );
             #endif
      
             MATCHING_ALTS *matching_alts = new MATCHING_ALTS();
             Append( *matching_alts, xres.matched_alts );
             best_results->best_matching_alts.push_back(matching_alts);
      
             EXPORTED_COORDS *exported_coords = NULL;
             if( !xres.exported_coords.empty() )
              exported_coords = new EXPORTED_COORDS(xres.exported_coords);
             best_results->best_exported_coords.push_back(exported_coords);
      
             EXPORTED_NODES *exported_nodes = NULL;
             if( !xres.exported_nodes.empty() )
              exported_nodes = new EXPORTED_NODES(xres.exported_nodes);
             best_results->best_exported_nodes.push_back(exported_nodes);
      
             LINKAGE_GROUPS * linkage_groups = NULL;
             if( !xres.linkage_groups.empty() )
              linkage_groups = new LINKAGE_GROUPS( xres.linkage_groups );
             best_results->best_linkage_groups.push_back( linkage_groups );
      
             LINKAGE_EDGES * linkage_edges = NULL;
             if( !xres.linkage_edges.empty() )
              linkage_edges = new LINKAGE_EDGES( xres.linkage_edges );
             best_results->best_linkage_edges.push_back( linkage_edges );
      
             BackTrace *backtrace = new BackTrace();
             xres.trace.CollectAll( backtrace );
             best_results->best_backtrace.push_back( backtrace );
      
             best_results->start_token.push_back( xres.res.GetStartToken() );

             //LEM_CHECKIT( xres.res.Length()>0 ) // непонятно, что делать - видимо, @optional или @coalesce в конце списка термов правила
             //best_results->final_token.push_back( xres.res.GetFinalToken() ); // ???
             if( xres.res.Length()==0 )
              {
               best_results->final_token.push_back( xres.res.GetStartToken()->GetPrev() );
              }
             else
              {
               best_results->final_token.push_back( xres.res.GetFinalToken() );
              }


             best_results->matching_len.push_back(len2);
             best_results->ngram_freqs.push_back( xres.res.GetNGramFreq() );
      
             max_len = std::max( max_len, len2 );
             max_ngram_freq = std::max( max_ngram_freq, xres.res.GetNGramFreq() );
      
             any_y_matched = true;
            }
          }
        }
      }
    }
  }

 if( point_matches )
  {
   for( lem::Container::size_type i=0; i<best_results->best_matching_alts.size(); ++i )
    {
     const MATCHING_ALTS &a = *best_results->best_matching_alts[i];
     const EXPORTED_COORDS *c = best_results->best_exported_coords[i];
     const EXPORTED_NODES *n = best_results->best_exported_nodes[i];
     const LINKAGE_GROUPS * groups = best_results->best_linkage_groups[i];
     const LINKAGE_EDGES * edges = best_results->best_linkage_edges[i];

     SynPatternResult *r = new SynPatternResult(NULL);
     r->res = SynPatternMatchResult( true, best_results->matching_len[i], best_results->start_token[i], best_results->final_token[i], best_results->ngram_freqs[i] );

     if( c!=NULL ) r->exported_coords = *c;
     if( n!=NULL ) r->exported_nodes = *n;
     if( groups!=NULL ) r->linkage_groups = *groups;
     if( edges!=NULL ) r->linkage_edges = *edges;

     r->matched_alts = a;
     r->trace.Add( *best_results->best_backtrace[i] );

     #if defined SOL_DEBUGGING
     r->debug_trace = * best_results->best_debug_trace[i];
     #endif

     results.push_back(r);
    }

   Limit( lexer, results, sg );
  }

 if( best_results!=NULL )
  delete best_results;

 return point_matches;
}
#endif





#if defined SOL_CAA && !defined SOL_NO_AA
bool SynPatternTreeNode::Empty(void) const
{
 return point.empty();
}
#endif



#if defined SOL_CAA && !defined SOL_NO_AA
SynPatternTreeNodeMatchingResults* SynPatternTreeNode::CompleteAnalysis(
                                                                        PM_Automat &pm,
                                                                        SynGram &sg,
                                                                        LA_SynPatternTrees &named_filters,
                                                                        WordEntrySet &wordentry_sets,
                                                                        BasicLexer &lexer,
                                                                        int id_language,
                                                                        TreeMatchingExperience & experience,
                                                                        const ElapsedTimeConstraint & constraints,
                                                                        TrTrace *trace_log
                                                                       ) const
{
 SynPatternTreeNodeMatchingResults * result = new SynPatternTreeNodeMatchingResults();

 const bool x = MatchTree(
                          UNKNOWN,
                          pm,
                          sg,
                          experience,
                          constraints,
                          named_filters,
                          wordentry_sets,
                          lexer,
                          lexer.GetBeginToken(),
                          & result->null_trace,
                          NULL,
                          false,
                          false,
                          (PtrCollect<SynPatternResult>&)result->results, 
                          trace_log
                         );

/*
 #if LEM_DEBUGGING==1
 for( lem::Container::size_type k=0; k<result->results.size(); ++k )
  {
   const SynPatternResult * result_k = result->results[k];
   const LexerTextPos * final_token = result_k->res.GetFinalToken();
   lem::mout->printf( "RESULT #%d len=%d final_token=%us\n", CastSizeToInt(k),  result_k->res.Length(), final_token->GetWordform()->GetName()->c_str() );
  } 
 #endif
*/

 // Разрешен неполный анализ. Но если хотя бы одно решение достигло правой границы, то не будем запускать
 // сложный неполный анализ.
 bool complete_analysis_found=false;
 for( lem::Container::size_type k=0; k<result->results.size(); ++k )
  {
   const SynPatternResult * result_k = result->results[k];
   const LexerTextPos * final_token = result_k->res.GetFinalToken();
   if( final_token->IsEnd() )
    {
     complete_analysis_found=true;
     break;
    }
  } 

 if( !complete_analysis_found )
  {
   result->Clear();
  }

 return result;
}
#endif



static bool result_sorter( const SynPatternResult * x, const SynPatternResult * y )
{
 return x->res.GetNGramFreq().Greater( y->res.GetNGramFreq() );
}


#if defined SOL_CAA && !defined SOL_NO_AA
SynPatternTreeNodeMatchingResults* SynPatternTreeNode::IncompleteAnalysis(
                                                                          PM_Automat &pm,
                                                                          SynGram &sg,
                                                                          LA_SynPatternTrees &named_filters,
                                                                          WordEntrySet &wordentry_sets,
                                                                          BasicLexer &lexer,
                                                                          int id_language,
                                                                          TreeMatchingExperience & experience,
                                                                          const ElapsedTimeConstraint & constraints,
                                                                          TrTrace *trace_log
                                                                         ) const
{
 SynPatternTreeNodeMatchingResults * result = new SynPatternTreeNodeMatchingResults();

 SynPatternResult null_result;

 lem::PtrCollect<SynPatternResult> final_results;
 lem::MCollect<int> final_result_fragments;

 TryMatchIncomplete(
                    pm,
                    sg,
                    experience,
                    constraints,
                    named_filters,
                    wordentry_sets,
                    lexer,
                    lexer.GetBeginToken(),
                    & null_result,
                    0,
                    & result->null_trace,
                    final_results, 
                    final_result_fragments,
                    trace_log
                   );
 
 LEM_CHECKIT_Z( final_results.size() == final_result_fragments.size() );
 
 // Имеем набор решений в final_results и количество фрагментов для каждого решения в final_result_fragments.
  
 /*
 #if LEM_DEBUGGING==1
 for( lem::Container::size_type k=0; k<final_results.size(); ++k )
  {
   const SynPatternResult * result_k = final_results[k];
   const LexerTextPos * final_token = result_k->res.GetFinalToken();
   lem::mout->printf( "RESULT #%d len=%d final_token=%us flags=%d\n", CastSizeToInt(k),  result_k->res.Length(), final_token->GetWordform()->GetName()->c_str(), final_result_fragments[k] );
   result_k->Print( *lem::mout, sg );
   result_k->PrintLinks( *lem::mout, sg );
   lem::mout->printf( "%60h-\n" );
  }
 #endif
 */


 for( lem::Container::size_type k=0; k<final_results.size(); ++k )
  {
   SynPatternResult * result_k = final_results[k];
 
   int nfrag = final_result_fragments[k];
   result_k->res.AddNGramFreq( NGramScore( -nfrag ) );
 
   result->results.push_back( result_k );
   final_results[k] = NULL;
  }
 
 // Уберем из результатов те, которые не оканчиваются правым терминатором (???)
 for( int i=CastSizeToInt(result->results.size())-1; i>=0; --i )
  if( !result->results[i]->res.GetFinalToken()->IsEnd() )
   result->results.Remove(i);
 
 /*
 #if LEM_DEBUGGING==1
 for( lem::Container::size_type k=0; k<result->results.size(); ++k )
  {
   const SynPatternResult * result_k = result->results[k];
   const LexerTextPos * final_token = result_k->res.GetFinalToken();
   lem::mout->printf( "RESULT #%d len=%d final_token=%us\n", CastSizeToInt(k), result_k->res.Length(), final_token->GetWordform()->GetName()->c_str() );
   result_k->Print( *lem::mout, sg );
   result_k->PrintLinks( *lem::mout, sg );
   lem::mout->printf( "%60h-\n" );
  }
 lem::mout->eol();
 #endif
 */


 /*
 // Нам нужно выбрать решения с минимальной фрагментацией.
 int min_fragment_count = lem::int_max;
 for( lem::Container::size_type i=0; i<final_result_fragments.size(); ++i )
  min_fragment_count = std::min( min_fragment_count, final_result_fragments[i] );
 
 // Среди решений с минимальной фрагментацией нужно выбрать те, у которых наилучшая оценка.
 
 NGramScore best_score(lem::int_min);
 
 for( lem::Container::size_type i=0; i<final_result_fragments.size(); ++i )
  if( final_result_fragments[i] == min_fragment_count )
   {
    if( final_results[i]->res.GetNGramFreq().Greater( best_score ) )
     {
      best_score = final_results[i]->res.GetNGramFreq();
     }
   }
 
 result->results.clear();
 for( lem::Container::size_type i=0; i<final_result_fragments.size(); ++i )
  if(
     final_result_fragments[i] == min_fragment_count &&
     final_results[i]->res.GetNGramFreq().Equal( best_score )
    )
   {
    result->results.push_back( final_results[i] );
    final_results[i] = NULL;
   }
 */
 
 /*
 #if LEM_DEBUGGING==1
 for( lem::Container::size_type k=0; k<result->results.size(); ++k )
  {
   const SynPatternResult * result_k = result->results[k];
   const LexerTextPos * final_token = result_k->res.GetFinalToken();
   lem::mout->printf( "RESULT #%d len=%d final_token=%us\n", CastSizeToInt(k),  result_k->res.Length(), final_token->GetWordform()->GetName()->c_str() );
  }
 
 lem::mout->printf( "%40h-\n\n" );
 #endif
 */


 return result;
}
#endif





#if defined SOL_CAA && !defined SOL_NO_AA
void SynPatternTreeNode::TryMatchIncomplete(
                                            PM_Automat &pm,
                                            SynGram &sg,
                                            TreeMatchingExperience &experience,
                                            const ElapsedTimeConstraint & constraints,
                                            LA_SynPatternTrees &named_filters,
                                            WordEntrySet &wordentry_sets,
                                            BasicLexer & lexer,
                                            const LexerTextPos * current_token,
                                            const SynPatternResult * current_result,
                                            int fragment_no,
                                            const BackTrace * parent_trace,
                                            lem::PtrCollect<SynPatternResult> & final_results,
                                            lem::MCollect<int> & final_result_fragments,
                                            TrTrace *trace_log
                                           ) const
{
 lem::MCollect<const LexerTextPos* > current_tokens;

 if( current_token->IsRealWord() || current_token->IsBegin() )
  {
   if( lexer.Fetch( current_token, current_tokens ) )
    {
     for( lem::Container::size_type q=0; q<current_tokens.size(); ++q )
      {
       const LexerTextPos * t2 = current_tokens[q];

       #if LEM_DEBUGGING==1
//       lem::mout->printf( "TryMatchIncomplete AT %us\n", t2->GetWordform()->GetName()->c_str() );
       #endif

       if( t2->IsEnd() || constraints.Exceeded() )
        {
         // Мы на правой границе или закончилось отведенное на анализ время.

         SynPatternResult * result2 = new SynPatternResult();
         result2->res = SynPatternMatchResult( true, current_token->GetWordIndex()+2, current_result->res.GetStartToken(), t2, current_result->res.GetNGramFreq() );
         result2->Append( *current_result );

/*
         #if LEM_DEBUGGING==1
         lem::mout->eol();
         result2->Print( *lem::mout, sg );
         result2->PrintLinks( *lem::mout, sg );
         lem::mout->eol();
         #endif
*/

         final_results.push_back( result2 );
         final_result_fragments.push_back( fragment_no+1 );

         continue;
        }

       BackTrace unused_trace(NULL);

       PtrCollect<SynPatternResult> results2;

       bool matched2=false;
       if( !experience.GetMatchedFragmentAt( t2, results2, &matched2 ) )
        {
         // Пробуем найти сопоставления с этого токена.
         matched2 = MatchTree(
                              UNKNOWN,
                              pm,
                              sg,
                              experience,
                              constraints,
                              named_filters,
                              wordentry_sets,
                              lexer,
                              t2,
                              & unused_trace,
                              NULL,
                              false,
                              lexer.GetParams().SkipOuterToken,
                              results2,
                              trace_log
                             );

         SynPatternResult::SelectUnique_WithRemoval( results2 );


/*
         #if LEM_DEBUGGING==1
         lem::mout->printf( "%60h-\n" );
         for( int k=0; k<results2.size(); ++k )
          {
           SynPatternResult * result_k = results2[k];
           const LexerTextPos * final_token = result_k->res.GetFinalToken();
           lem::mout->printf( "RESULT #%d len=%d final_token=%us score=%d\n", CastSizeToInt(k),  result_k->res.Length(), final_token->GetWordform()->GetName()->c_str(), result_k->res.GetNGramFreq().Composite() );
          } 
         #endif
*/


         if( results2.size()>2 )
          {
           // Оставим только 2 результата: самый длинный и самый достоверный.

           int max_len=0;
           int n_max_len=0;
           lem::Container::size_type i_max_len=0;

           Solarix::NGramScore max_score(lem::int_min);
           int n_max_score=0;
           lem::Container::size_type i_max_score=0;

           for( lem::Container::size_type k=0; k<results2.size(); ++k )
            {
             const SynPatternResult * result_k = results2[k];
             if( result_k->res.Length()>max_len )
              {
               max_len = result_k->res.Length();
               n_max_len = 1;
               i_max_len = k;
              }
             else if( result_k->res.Length()==max_len )
              {
               n_max_len++;
              }

             if( result_k->res.GetNGramFreq().Greater( max_score ) )
              {
               max_score = result_k->res.GetNGramFreq();
               n_max_score = 1;
               i_max_score = k;
              }
             else if( result_k->res.GetNGramFreq().Equal( max_score ) )
              {
               n_max_score++;
              }
            }

           lem::MCollect<SynPatternResult*> selected_results;

           // Если с максимальной длиной несколько результатов, то среди них тоже выберем - максимально достоверный.
           if( n_max_len>1 )
            {
             Solarix::NGramScore max_score_4len(lem::int_min);
             lem::Container::size_type i_max_score_4len=0;
          
             for( lem::Container::size_type k=0; k<results2.size(); ++k )
              {
               const SynPatternResult * result_k = results2[k];
               if( result_k->res.Length()==max_len )
                {
                 if( result_k->res.GetNGramFreq().Greater( max_score_4len ) )
                  {
                   max_score_4len = result_k->res.GetNGramFreq();
                   i_max_score_4len = k;
                  }
                }
              }

             selected_results.push_back( results2[ i_max_score_4len ] );
             results2[i_max_score_4len] = NULL;
            }
           else
            {
             selected_results.push_back( results2[ i_max_len ] );
             results2[i_max_len] = NULL;
            }

           SynPatternResult * max_score_result = results2[ i_max_score ];
           if( max_score_result!=NULL )
            {
             selected_results.push_back( max_score_result );
             results2[i_max_score] = NULL;
            }

           results2.clear();
           for( lem::Container::size_type i=0; i<selected_results.size(); ++i )
            results2.push_back( selected_results[i] );

/*
           lem::MCollect<SynPatternResult*> & sorted = (lem::MCollect<SynPatternResult*>&)results2;
           std::sort( sorted.begin(), sorted.end(), result_sorter );
           if( results2.size()>2 )
            results2.ReduceTo(2);
*/

/*
           #if LEM_DEBUGGING==1
           lem::mout->printf( "%60h-\n" );
           for( int k=0; k<results2.size(); ++k )
            {
             SynPatternResult * result_k = results2[k];
             const LexerTextPos * final_token = result_k->res.GetFinalToken();
             lem::mout->printf( "RESULT #%d len=%d final_token=%us score=%d\n", CastSizeToInt(k),  result_k->res.Length(), final_token->GetWordform()->GetName()->c_str(), result_k->res.GetNGramFreq().Composite() );
            } 
           #endif
*/

          }

         experience.StoreMatchedFragment( t2, matched2, results2 );
        }

       if( !matched2 )
        {
         // Будем смещаться далее вправо на следующие токены.
         TryMatchIncomplete(
                            pm,
                            sg,
                            experience,
                            constraints,
                            named_filters,
                            wordentry_sets,
                            lexer,
                            t2,
                            current_result,
                            fragment_no+1,
                            & unused_trace,
                            final_results,
                            final_result_fragments,
                            trace_log
                           );
        }
       else
        {
         // Какую-то цепочку токенов удалось сопоставить.
         // Надо добавить к каждому из результатов родительские результаты из current_result.
    
         for( lem::Container::size_type j=0; j<results2.size(); ++j )
          {
           SynPatternResult * result2 = results2[j];

           if( result2->res.Length()==0 )
            {
             // результат имеет нулевую длину - СТРАННО!
             continue;
            }

           result2->Append( *current_result );

           // Если это сопоставление достигло правую границу, то можем добавлять в итоговые результаты.
           if( result2->res.GetFinalToken()->IsEnd() )
            {
             final_results.push_back( result2 );
             final_result_fragments.push_back( fragment_no );
             results2[j] = NULL;
            }
           else
            {
             // нет, справа еще есть токены.
             TryMatchIncomplete(
                                pm,
                                sg,
                                experience,
                                constraints,
                                named_filters,
                                wordentry_sets,
                                lexer,
                                result2->res.GetFinalToken(),
                                result2,
                                fragment_no+1,
                                & unused_trace,
                                final_results,
                                final_result_fragments,
                                trace_log
                               );
            }
          }
        }
      }
    }
  }

 return;
}
#endif
