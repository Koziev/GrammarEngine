// LC->23.08.2014

#include <lem/solarix/pm_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/aa_autom.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/variator.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/tr_funs.h>
#include <lem/solarix/tr_trace_actors.h>
#include <lem/solarix/sg_notag_filter.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/ThesaurusTagDefs.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/PhraseEntries.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/ThesaurusLinkFlags.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/TextRecognitionParameters.h>
#include <lem/solarix/ElapsedTimeConstraint.h>
#include <lem/solarix/PreparedLexer.h>
#include <lem/solarix/WrittenTextAnalysisSession.h>
#include <lem/solarix/casing_coder.h>

using namespace lem;
using namespace Solarix;


static bool wfa_sorter( const std::pair<const Word_Form*,int> &x, const std::pair<const Word_Form*,int> &y )
{
 return y.second < x.second;
}


static void ValueToTreeList( const TrValue &val, MCollect<Tree_Node*> &list )
{
 if( val.GetType().IsTree() )
  { 
   const Tree_Node &tn = val.GetTree();
   Tree_Node *add_tn = new Tree_Node(tn);
   list.push_back(add_tn); 
  }
 else if( val.GetType().IsTrees() )
  {
   const Variator &v = val.GetTrees();
   for( int k=0; k<v.size(); ++k )
    {
     Tree_Node *add_tn = new Tree_Node( v.get(k) );
     list.push_back(add_tn); 
    }
  }
 else if( val.GetType().IsString() )
  {
   const UCString &s = val.GetString();
   Word_Form *wf = new Word_Form(s);
   Tree_Node *add_tn = new Tree_Node(wf,true);
   list.push_back(add_tn); 
  }
 else if( val.GetType().IsTuple() )
  {
   const TrTuple &t = val.GetTuple();
   for( int i=0; i<t.Count(); ++i )
    ValueToTreeList( t[i], list );
  }
 else
  {
   UFString msg = format_str( L"Can not cast '%s' to tree", val.GetType().GetName().c_str() );
   throw E_BaseException(msg);
  } 

 return;
}


TrFun_BuiltIn::TrFun_BuiltIn(void)
 : TrFunCall( TrFunCall::BuiltIn )
{
}


TrFun_BuiltIn::TrFun_BuiltIn( const TrFun_BuiltIn & x )
 : TrFunCall(x), name(x.name), args(x.args)
{
 return;
}



void TrFun_BuiltIn::operator=( const TrFunCall & x )
{
 TrFunCall::operator =(x);
 name = ((const TrFun_BuiltIn&)x).name;
 args = ((const TrFun_BuiltIn&)x).args;
 return;
}
   


#if defined SOL_CAA
static void Add2Var( const PM_Automat &pm, Variator &var, const TrValue &v )
{
 bool has_end=false;
 if( var.size()>1 && var.get(var.size()-1).GetNode().GetEntryKey()==pm.GetDict().GetSynGram().I_END )
  has_end = true;

 if( v.GetType().IsTree() )
  {
   const Tree_Node &tn = v.GetTree();
  
   if( has_end )
    var.Insert( var.size()-1, new Tree_Node(tn) );
   else
    var.Add( new Tree_Node(tn) );
  }
 else if( v.GetType().IsTrees() )
  {
   const Variator &add_var = v.GetTrees();
   for( int i=0; i<add_var.size(); ++i )
    { 
     if( add_var.get(i).GetNode().GetEntryKey()==pm.GetDict().GetSynGram().I_END ||
         add_var.get(i).GetNode().GetEntryKey()==pm.GetDict().GetSynGram().I_BEGIN )
      continue;  

     if( has_end )
      var.Insert( var.size()-1, new Tree_Node( *add_var[i] ) );
     else
      var.Add( new Tree_Node( *add_var[i] ) );
    } 
  } 
 else if( v.GetType().IsTuple() )
  {
   // Отдельно добавляем каждый элемент кортежа
   const TrTuple &tu = v.GetTuple();
   for( lem::Container::size_type i=0; i<tu.values.size(); ++i )
    {
     const TrValue &v = *tu.values[i];
     Add2Var( pm, var, v );
    }
  }
 else if( v.GetType().IsVoid() )
  {
   // пропускаем
  } 
 else if( v.GetType().IsString() )
  {
   const UCString &s = v.GetString();
   if( !s.empty() )
    {
     Word_Form *wf = new Word_Form( s );
     var.Add( new Tree_Node( wf, true ) );
    }
  }
 else
  {
   UFString msg = format_str( L"Error in variator creation function: inacceptable argument type" ); 
   throw E_BaseException(msg);
  }

 return;
}
#endif



#if defined SOL_CAA
static void Prepend2Var( const PM_Automat &pm, Variator &var, const TrValue &v )
{
 int idx=0;
 if( var.size()>1 && var.get(0).GetNode().GetEntryKey()==pm.GetDict().GetSynGram().I_BEGIN )
  idx=1;

 if( v.GetType().IsTree() )
  {
   const Tree_Node &tn = v.GetTree();
   var.Insert( idx, new Tree_Node(tn) );
  }
 else if( v.GetType().IsTrees() )
  {
   const Variator &add_var = v.GetTrees();
   for( int i=0; i<add_var.size(); ++i )
    { 
     if( add_var.get(i).GetNode().GetEntryKey()==pm.GetDict().GetSynGram().I_END ||
         add_var.get(i).GetNode().GetEntryKey()==pm.GetDict().GetSynGram().I_BEGIN )
      continue;  

     var.Insert( idx+i, new Tree_Node( *add_var[i] ) );
    } 
  } 
 else if( v.GetType().IsTuple() )
  {
   // Отдельно добавляем каждый элемент кортежа
   const TrTuple &tu = v.GetTuple();
   for( lem::Container::size_type i=0; i<tu.values.size(); ++i )
    {
     const TrValue &v = *tu.values[i];

     if( v.GetType().IsTree() )
      {
       var.Insert( idx+i, new Tree_Node( v.GetTree() ) );
      }
     else
      {
       LEM_STOPIT;
      }
    }
  }
 else if( v.GetType().IsVoid() )
  {
   // пропускаем
  } 
 else if( v.GetType().IsString() )
  {
   const UCString &s = v.GetString();
   if( !s.empty() )
    {
     Word_Form *wf = new Word_Form( s );
     var.Insert( idx, new Tree_Node( wf, true ) );
    }
  }
 else
  {
   UFString msg = format_str( L"Error in variator creation function: inacceptable argument type" ); 
   throw E_BaseException(msg);
  }

 return;
}
#endif


#if defined SOL_CAA

struct AltIndex
{
 int iroot;
 int ialt;
 AltIndex(void) : iroot(UNKNOWN), ialt(UNKNOWN) {}
 AltIndex( int r, int a ) : iroot(r), ialt(a) {}

 bool operator==( const AltIndex &x ) const { return iroot==x.iroot && ialt==x.ialt; }
 bool operator<( const AltIndex &x ) const
 {
  return iroot<x.iroot ||
         (iroot==x.iroot && ialt<x.ialt);
 }
};

lem::Ptr<TrValue> TrFun_BuiltIn::Run(
                                     const ElapsedTimeConstraint & constraints,
                                     PM_Automat &pm,
                                     TrFunContext &ctx,
                                     TrTrace *trace_log
                                    ) const
{
 const int mark = TrTraceActor::seq++;
 if( trace_log!=NULL )
  trace_log->Enter( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 #if LEM_DEBUGGING==1 && defined LEM_MSC
// _ASSERTE( _CrtCheckMemory( ) );
 #endif

/*
#if LEM_DEBUGGING==1
// --- debug
if( lem::LogFile::IsOpen() )
 {
  lem::Path fname;
  int line=-1, column=-1;
  if( pm.GetDict().GetDebugSymbols().GetLocation( src_location, fname, line, column ) )
   {
    lem::MemFormatter mem;
    mem.printf( "DEBUG TrFun_BuiltIn::Run fun=%us file=%us line=%d column=%d", name.c_str(), fname.GetUnicode().c_str(), line, column );
    lem::LogFile::Print( mem.string() );
   }
 }
// --- 
#endif
*/

 lem::Ptr<TrValue> ret;

 if( name.eqi(L"eq") )
  {
   bool r=true;

   lem::Ptr<TrValue> x = args.front()->Run(constraints,pm,ctx,trace_log);

   for( lem::Container::size_type i=1; i<args.size(); ++i )
    {
     lem::Ptr<TrValue> y = args[i]->Run(constraints,pm,ctx,trace_log);

     if( !x->eq(y) )
      {
       r = false;
       break;  
      }
    }

   ret = new TrBoolValue(r);
  }
 else if( name.eqi(L"eqi") )
  {
   bool r=true;

   lem::Ptr<TrValue> x = args.front()->Run(constraints,pm,ctx,trace_log);
   for( lem::Container::size_type i=1; i<args.size(); ++i )
    {
     lem::Ptr<TrValue> y = args[i]->Run(constraints,pm,ctx,trace_log);
     if( !x->eqi(y) )
      {
       r = false;
       break;  
      }
    }

   ret = new TrBoolValue(r);
  }
 else if( name.eqi(L"one_of") )
  {
   bool r=false;

   lem::Ptr<TrValue> x = args.front()->Run(constraints,pm,ctx,trace_log);
   for( lem::Container::size_type i=1; i<args.size(); ++i )
    {
     lem::Ptr<TrValue> y = args[i]->Run(constraints,pm,ctx,trace_log);
     if( x->eq(y) )
      {
       r = true;
       break;  
      }
    }

   ret = new TrBoolValue(r);
  }
 else if( name.eqi(L"log_or") )
  {
   bool r=false;

   for( lem::Container::size_type i=0; i<args.size(); ++i )
    {
     lem::Ptr<TrValue> a = args[i]->Run(constraints,pm,ctx,trace_log);
     if( a->GetBool() )
      {
       r = true;
       break;  
      }
    }

   ret = new TrBoolValue(r);
  }
 else if( name.eqi(L"log_and") )
  {
   bool r=true;

   for( lem::Container::size_type i=0; i<args.size(); ++i )
    {
     lem::Ptr<TrValue> a = args[i]->Run(constraints,pm,ctx,trace_log);
     if( !a->GetBool() )
      {
       r = false;
       break;  
      }
    }

   ret = new TrBoolValue(r);
  }
 else if( name.eqi(L"log_not") )
  {
   lem::Ptr<TrValue> a = args.front()->Run(constraints,pm,ctx,trace_log);
   ret = new TrBoolValue(!a->GetBool());
  }
 else if( name.eqi(L"neq") )
  {
   lem::Ptr<TrValue> x = args[0]->Run(constraints,pm,ctx,trace_log);
   lem::Ptr<TrValue> y = args[1]->Run(constraints,pm,ctx,trace_log);
   ret = new TrBoolValue( !(x->eq(y)) );
  }
 else if( name.eqi(L"gt") )
  {
   lem::Ptr<TrValue> x = args[0]->Run(constraints,pm,ctx,trace_log);
   lem::Ptr<TrValue> y = args[1]->Run(constraints,pm,ctx,trace_log);
   ret = new TrBoolValue( x->GetInt() > y->GetInt() );
  }
 else if( name.eqi(L"ge") )
  {
   lem::Ptr<TrValue> x = args[0]->Run(constraints,pm,ctx,trace_log);
   lem::Ptr<TrValue> y = args[1]->Run(constraints,pm,ctx,trace_log);
   ret = new TrBoolValue( x->GetInt() >= y->GetInt() );
  }
 else if( name.eqi(L"lt") )
  {
   lem::Ptr<TrValue> x = args[0]->Run(constraints,pm,ctx,trace_log);
   lem::Ptr<TrValue> y = args[1]->Run(constraints,pm,ctx,trace_log);
   ret = new TrBoolValue( x->GetInt() < y->GetInt() );
  }
 else if( name.eqi( L"link_copy" ) )
  {
   // Копирование связей в указанных измерениях с заданным типом связки
   // link_copy( приемник, источник [, имя_измерения [, тип_связи ] ] )

   // Первый аргумент - всегда одиночное дерево.
   lem::Ptr<TrValue> a0 = args.front()->Run(constraints,pm,ctx,trace_log);
   Tree_Node & tn = a0->GetTree();

   // источник связей
   lem::Ptr<TrValue> a1 = args[1]->Run(constraints,pm,ctx,trace_log);
   Tree_Node & src = a1->GetTree();
     
   if( &tn != &src )
    {
     if( args.size()==2 )
      {
       // Копируем все связи во всех измерениях.
       // Сначала - нулевое измерения, синтаксические связи.

       const TreeDimension& d0 = src.leafs();
       for( lem::Container::size_type i=0; i<d0.size(); ++i )
        {
         tn.leafs().Add( new Tree_Node( d0[i] ) );
        }

       {
       // Теперь копируем остальные измерения
       for( lem::Container::size_type i=0; i<src.GetDimensions().size(); ++i )
        {
         const TreeDimension &d = *src.GetDimensions()[i];
         TreeDimension & dst_d = tn.TouchDimension( d.GetName() );
         dst_d.Add( d );
        }
       }
      } 
     else if( args.size()>=3 )
      {
       // Задано имя копируемого измерения.
       lem::Ptr<TrValue> dim_name = args[2]->Run(constraints,pm,ctx,trace_log);

       const TreeDimension * src_dim = src.FindDimension(dim_name->GetString());
       if( src_dim!=NULL )
        {  
         TreeDimension & dim = tn.TouchDimension(dim_name->GetString());

         if( args.size()==3 )
          {
           dim.Add( *src_dim ); 
          }
         else if( args.size()==4 )
          {
           // Задан фильтр связки
           lem::MCollect<int> links;
   
           lem::Ptr<TrValue> link = args[3]->Run(constraints,pm,ctx,trace_log);
           if( link->GetType().IsInt() )
            {
             const int ilink = link->GetInt();
             if( ilink!=UNKNOWN )
              links.push_back(ilink);
            }
           else if( link->GetType().IsTuple() )
            {
             const TrTuple &t = link->GetTuple();
             for( int j=0; j<t.Count(); ++j )
              {
               const TrValue &v = t[j];
               if( v.GetType().IsInt() )
                {
                 const int ilink = v.GetInt();
                 if( ilink!=UNKNOWN )
                  links.push_back(ilink);
                }
               else
                {
                 LEM_STOPIT;
                }  
              }
            }
           else
            {
             LEM_STOPIT;
            }
        
           for( lem::Container::size_type k=0; k<src_dim->size(); ++k )
            {
             const Tree_Node &src_tn = (*src_dim)[k];
             if( links.empty() || links.find( src_tn.GetLink().GetState() )!=UNKNOWN )
              {
               dim.Add( new Tree_Node( src_tn ) );
              }
            }
          }
         else
          {
           LEM_STOPIT;
          }
        }
      }
    }

   ret = a0;
  } 
 else if( name.eq_begi( L"link_" ) )
  {
   // Первый аргумент - всегда одиночное дерево.
   lem::Ptr<TrValue> a0 = args.front()->Run(constraints,pm,ctx,trace_log);
   Tree_Node & tn = a0->GetTree();

   // Второй аргумент - имя измерения.
   lem::UCString dim_name;
   if( args.size()>1 )
    {
     lem::Ptr<TrValue> a1 = args[1]->Run(constraints,pm,ctx,trace_log);
     dim_name = a1->GetString();
    }

   if( name.eqi( L"link_count" ) )
    {
     // link_count( корень, имя_измерения [, тип_связи [, проверяльщик_ветки ] ] )

     // Подсчет кол-ва веток в заданном измерении, удовлетворяющих указанным
     // требованиям на тип связи и - содержимое подключенного узла.

     // Далее могут идти еще 2 аргумента (опционально) - тип связки и требование на ветку.
     // Требование на ветку реализуется через механизм лямбда-функций.    

     int link=ANY_STATE;
     const TrFunCall *visitor = NULL;
     if( args.size()>2 )
      {
       lem::Ptr<TrValue> a2 = args[2]->Run(constraints,pm,ctx,trace_log);
       link = a2->GetInt();

       if( args.size()>3 )
        {
         visitor = & args[3]->Run(constraints,pm,ctx,trace_log)->GetFun();
        }
      }

     int res_count=0;

     const TreeDimension *dim = tn.FindDimension(dim_name);
 
     if( dim!=NULL )
      {
       if( link==ANY_STATE && visitor==NULL )
        {
         res_count = CastSizeToInt( dim->size() );
        }
       else
        {  
         // Запускаем цикл просмотра веток у первого аргумента.
         for( lem::Container::size_type ileaf=0; ileaf<dim->size(); ++ileaf )
          {
           const Tree_Node &leaf = (*dim)[ileaf];

           if( link!=ANY_STATE )
            {
             // проверям тип связи
             if( leaf.GetLink()!=link )
              continue;
            }

           // Проверяем ветку вызовом лямбда-функции.
           if( visitor!=NULL )
            {
             // Аргумент вызова - проверяемый узел.
             lem::Ptr<TrValue> rleaf( new TrValue( &leaf, false ) );
             TrContextInvokation ctx2(&ctx);
             ctx2.AddVar( L"_", rleaf );
             lem::Ptr<TrValue> rok = visitor->Run( constraints, pm, ctx2, trace_log );
             if( rok->GetBool()==false )
              continue;
            }

           res_count++;
          }
        }
      } 

     ret = new TrIntValue(res_count);
    } 
   else if( name.eqi( L"link_get" ) ||  name.eqi( L"link_getref" ) )
    {
     // Возвращает i-й узел, связанный с корнем в указанном измерении
     // link_get( корень, имя_измерения, индекс_ветки )

     TreeDimension *dim = tn.FindDimension(dim_name);

     if( dim==NULL )
      {
       lem::UFString msg( lem::format_str( L"Can not access dimension [%s] in function 'link_get'", dim_name.c_str() ) );
       throw E_BaseException(msg.c_str());
      } 
 
     // Третий аргумент - индекс требуемой ветки.
     lem::Ptr<TrValue> a3 = args[2]->Run(constraints,pm,ctx,trace_log);
     const int ileaf = a3->GetInt();
     if( ileaf<0 || ileaf>=CastSizeToInt(dim->size()) )
      {
       lem::UFString msg( lem::format_str( L"Index %d is out of range [0,%d) in link_get", ileaf, CastSizeToInt(dim->size()) ) );
       throw E_BaseException(msg.c_str());
      }

     Tree_Node &leaf = (*dim)[ileaf];

     if( name.eqi( L"link_get" ) )
      { 
       // Делаем глубокую копию дерева, так как в TreeDimension храняться обычные указатели,
       // и при очистке слоя внешние указатели станут некорректными.
       ret = new TrValue( new Tree_Node(leaf), true );
      }
     else
      {
       ret = new TrValue( &leaf, false );
      }
    } 
   else if( name.eqi( L"link_get_type2" ) )
    {
     // Возвращает тип связи для i-го узла, связанного с корнем в указанном измерении 
     // link_get_type2( корень, имя_измерения, индекс_ветки )

     TreeDimension *dim = tn.FindDimension(dim_name);

     if( dim==NULL )
      {
       lem::UFString msg( lem::format_str( L"Can not access dimension [%s] in function 'link_get_type2'", dim_name.c_str() ) );
       throw E_BaseException(msg.c_str());
      } 
 
     // Третий аргумент - индекс требуемой ветки.
     lem::Ptr<TrValue> a3 = args[2]->Run(constraints,pm,ctx,trace_log);
     const int ileaf = a3->GetInt();
     Tree_Node &leaf = (*dim)[ileaf];
     const Tree_Link& l = leaf.GetLink();

     ret = new TrIntValue( l.GetState() );
    } 
   else if( name.eqi( L"link_add" ) )
    {
     // link_add( корень, имя_измерения, тип_связи, добавляемый_узел1 [, добавляемый_узел2 [, ...] ] )
     // Возвращает: корень

     TreeDimension & dim = tn.TouchDimension(dim_name);

     lem::Ptr<TrValue> a2 = args[2]->Run(constraints,pm,ctx,trace_log);
     const int link = a2->GetInt();

     MCollect<Tree_Node*> nodes;
     for( lem::Container::size_type k=3; k<args.size(); ++k )
      {
       lem::Ptr<TrValue> a3 = args[k]->Run(constraints,pm,ctx,trace_log);
       nodes.clear();
       ValueToTreeList( *a3, nodes );
       for( lem::Container::size_type i=0; i<nodes.size(); ++i )
        {
         nodes[i]->SetLink(link);
         dim.Add(nodes[i]); 
        }
      } 

     ret = a0;
    } 
   else if( name.eqi( L"link_remove" ) )
    {
     // link_remove( корень, имя_измерения [, индекс_ветки] )

     TreeDimension & dim = tn.TouchDimension(dim_name);

     if( args.size()>2 )
      {
       lem::Ptr<TrValue> a3 = args[2]->Run(constraints,pm,ctx,trace_log);
       const int ileaf = a3->GetInt();
       dim.Remove(ileaf);
      }
     else
      {
       dim.Clear();
      }
 
     ret = a0;
    } 
  }
 else if( name.eqi( L"debug_print" ) )
  {
   if( trace_log!=NULL )
    {
     lem::Ptr<TrValue> a1 = args[0]->Run(constraints,pm,ctx,trace_log);
     lem::Ptr<TrValue> a2 = args[1]->Run(constraints,pm,ctx,trace_log);
     const lem::UCString &name = a1->GetString();
     trace_log->DebugTrace( name, *a2 );
    }
  }
 else if( name.eq_begi( L"var_" ) )
  {
   // ФУНКЦИИ ДЛЯ РАБОТЫ С ВАРИАТОРАМИ

   if( name.eqi( L"var_create" ) )
    {
     // Создание вариатора
     Variator *v = new Variator;
     
     for( lem::Container::size_type i=0; i<args.size(); ++i )
      {
       lem::Ptr<TrValue> point = args[i]->Run(constraints,pm,ctx,trace_log);
       Add2Var( pm, *v, *point ); 
      }

//     v->InitHash();
     ret = new TrValue( v, true );
    }
   else
    {
     // Первый аргумент всегда - вариатор.
     lem::Ptr<TrValue> a1 = args[0]->Run(constraints,pm,ctx,trace_log);
     Variator &var = a1->GetTrees();

     if( name.eqi( L"var_get" ) )
      {
       // Извлекаем дерево по его индексу в вариаторе:
       // var_get( вариатор, индекс_корня )
       lem::Ptr<TrValue> a2 = args[1]->Run(constraints,pm,ctx,trace_log);
       const int iroot = a2->GetInt();

       if( iroot>= var.size() )
        {
         lem::MemFormatter mem;
         mem.printf( "var_get error: index %d is out of boundary, var size=%d", iroot, var.size() );
         throw E_BaseException( mem.string() );
        }

       const Tree_Node &root = * var[iroot];

       ret = new TrValue( new Tree_Node(root), true );
      }
     else if( name.eqi( L"var_getref" ) )
      {
       // Извлекаем дерево по его индексу в вариаторе, возвращаем ССЫЛКУ:
       // var_getref( вариатор, индекс_корня )
       lem::Ptr<TrValue> a2 = args[1]->Run(constraints,pm,ctx,trace_log);
       const int iroot = a2->GetInt();

       if( iroot>= var.size() )
        {
         lem::MemFormatter mem;
         mem.printf( "var_get error: index %d is out of boundary, var size=%d", iroot, var.size() );
         throw E_BaseException( mem.string() );
        }

       Tree_Node &root = * var[iroot];
       ret = new TrValue( &root, false );
      }
     else if( name.eqi( L"var_set" ) )
      {
       // Замена дерева в вариаторе в указанной позиции
       // var_set( вариатор, индекс_корня, новый_корень )
       lem::Ptr<TrValue> a2 = args[1]->Run(constraints,pm,ctx,trace_log);
       const int iroot = a2->GetInt();

       if( iroot>= var.size() )
        {
         lem::MemFormatter mem;
         mem.printf( "var_get error: index %d is out of boundary, var size=%d", iroot, var.size() );
         throw E_BaseException( mem.string() );
        }

       lem::Ptr<TrValue> a3 = args[2]->Run(constraints,pm,ctx,trace_log);

       var.DeleteTree(iroot);
       var.SetPtr( iroot, new Tree_Node( a3->GetTree() ) );
//       var.InitHash();

       ret = a1;
      }
     else if( name.eqi( L"var_back" ) )
      {
       // Извлекаем дерево на конце вариатора ДО метки $END
       // var_back( вариатор [, доп_смещение ] )
       int d = 0;
       if( args.size()>1 )
        {
         lem::Ptr<TrValue> a2 = args[1]->Run(constraints,pm,ctx,trace_log);
         d = a2->GetInt();
        }

       const int iroot = CastSizeToInt(var.size())-2-d;
  
       const Tree_Node &root = * var[iroot];

       ret = new TrValue( new Tree_Node(root), true );
      }
     else if( name.eqi( L"var_add" ) )
      {
       // var_add( вариатор, добавляемый_узел1 [, добавляемый_узел2 [, ... ] ] )
       //
       // ATTENTION: чтобы упростить программирование, мы сами отслеживаем ситуацию, когда на конце
       // вариатора стоит метка END (а это обычное состояние вариатора), и тогда вставляем добавляемый
       // узел ДО этой метки.

       for( lem::Container::size_type i=1; i<args.size(); ++i )
        {  
         lem::Ptr<TrValue> a2 = args[i]->Run(constraints,pm,ctx,trace_log);
         Add2Var( pm, var, *a2 );
        }
  
//       var.InitHash();

       ret = a1;
      }
     else if( name.eqi( L"var_prepend" ) )
      {
       // var_prepend( вариатор, добавляемый_узел )
       //
       // ATTENTION: чтобы упростить программирование, мы сами отслеживаем ситуацию, когда в начале
       // вариатора стоит метка BEGIN, и тогда вставляем добавляемый узел ПОСЛЕ этой метки.

       lem::Ptr<TrValue> a2 = args[1]->Run(constraints,pm,ctx,trace_log);
       Prepend2Var( pm, var, *a2 );
//       var.InitHash();
       ret = a1;
      }
     else if( name.eqi( L"var_count" ) )
      {
       // Возвращает кол-во корней в вариаторе (с учетом границ)
       // var_count(вариатор)
       const int n = var.size();
       ret = new TrIntValue(n);
      }
     else if( name.eqi( L"var_remove" ) )
      {
       // Удаляет указанный индексом корень из вариатора.
       // var_remove( вариатор, индекс_корня )
       lem::Ptr<TrValue> a2 = args[1]->Run(constraints,pm,ctx,trace_log);
       const int iroot = a2->GetInt();

       if( iroot>= var.size() )
        {
         lem::MemFormatter mem;
         mem.printf( "var_get error: index %d is out of boundary, var size=%d", iroot, var.size() );
         throw E_BaseException( mem.string() );
        }

       var.RemoveRoot(iroot);
//       var.InitHash();
       ret = a1;
      }
    }
  }
 else if( name.eqi( L"restore_case" ) )
  {
   // Для корня дерева или корней деревьев надо восстановить правильный регистр,
   // основываясь на атрибутах словарных статей
   lem::Ptr<TrValue> x = args[0]->Run(constraints,pm,ctx,trace_log);

   // Нам будет нужен объект-восстановитель.
   CasingCoder & cc = pm.GetDict().GetLexAuto().GetCasingCoder();

   if( x->GetType().IsTree() )
    {
     // Единственное дерево - обрабатываем его корень.
     Solarix::Tree_Node & tn = x->GetTree();

     Solarix::Word_Form & wf = tn.GetNode();
  
     const RC_Lexem & rc = wf.GetName();
     UFString w = rc->c_str();

/*
     if( wf.IsConvolved() )
      {
       w.to_lower();
      }
     else*/
      {
       const int ekey = wf.GetEntryKey();
       if( !lem::is_quantor(ekey) )
        {
         const Solarix::SG_Entry &e = pm.GetDict().GetSynGram().GetEntry(ekey);
         const int icasing = e.GetAttrState( Solarix::GramCoordAdr(cc.icoord_casing) );
         cc.RestoreCasing(icasing,w,ekey);
        }  
      }

     if( w!=rc->c_str() )
      wf.SetName( UCString(w.c_str()) );
    }
   else if( x->GetType().IsTrees() )
    {
     // Вариатор - обрабатываем корни всех деревьев.
     Solarix::Variator & var = x->GetTrees();

     for( int i=0; i<var.size(); ++i )
      {
       Solarix::Tree_Node & tn = * var[i];

       Solarix::Word_Form & wf = tn.GetNode();
  
       const RC_Lexem & rc = wf.GetName();
       UFString w = rc->c_str();

/*
       if( wf.IsConvolved() )
        {
         w.to_lower();
        }
       else*/
        {
         const int ekey = wf.GetEntryKey();

         if(
            !lem::is_quantor(ekey) &&
            ekey!=pm.GetDict().GetSynGram().I_BEGIN &&
            ekey!=pm.GetDict().GetSynGram().I_END
           )
          {
           const Solarix::SG_Entry &e = pm.GetDict().GetSynGram().GetEntry(ekey);
           const int icasing = e.GetAttrState( Solarix::GramCoordAdr(cc.icoord_casing) );
           cc.RestoreCasing(icasing,w,ekey);
          }  
        }

       if( w!=rc->c_str() )
        wf.SetName( UCString(w.c_str()) );
      }
    }
   else
    {
     UFString msg = format_str( L"Invalid argument type %us in function 'restore_casing'", x->GetType().GetName().c_str() );
     throw E_BaseException( msg );
    }
  }
 else if( name.eq_begi( L"thesaurus_find" ) || name.eq_begi( L"thesaurus_collect" ) )
  {
   // Поиск связей по тезаурусу
   // thesaurus_find( узел, связь1[, флаг_фильтра] )
   // thesaurus_collect( узел, связь1[, флаг_фильтра] )
   // Возвращается узел, созданный по результатам перехода в сети.
   // Грамматические атрибуты - сброшены.
   //
   // Если в глобальном контексте заданы тэги и значение аргумента флаг_фильтра=true,
   // то они используются для фильтрации находимых связей.
   //
   // Функция thesaurus_find упаковывает найденные слова как альтернативы одной словоформы и поэтому
   // возвращает tree.
   //
   // Функция thesaurus_collect возвращает список связанных статей через tuple, элементы которого - tree. 
   //
   // Вместо одной связи может быть задан путь - кортеж с несколькими связями, тогда
   // будет выполнен последовательный переход в семантической сети по указанным связям.

   lem::Ptr<TrValue> start = args[0]->Run(constraints,pm,ctx,trace_log);

   lem::Ptr<TrValue> rlink = args[1]->Run(constraints,pm,ctx,trace_log);

   lem::Ptr<Solarix::SG_TagFilter> tags0_ptr;
   lem::Ptr<Solarix::SG_TagFilter> tags_ptr;   

   if( args.size()==3 )
    {
     lem::Ptr<TrValue> atags = args[2]->Run(constraints,pm,ctx,trace_log);

     if( atags->GetType().IsTuple() )
      {
       // Список тэгов задан через вектор пар { имя_тэга, значение, ... }
       const TrTuple &t = atags->GetTuple(); 

       if( t.Count()==0 )
        {
         // особый случай - задан пустой список тегов, это означает, что ищем
         // связи БЕЗ тегов.
         tags_ptr = new Solarix::NoTagFilter();
        }
       else
        {
         UCString tag_name = t[0].GetString();
         UCString tag_value = t[1].GetString();

         const int itag = pm.GetDict().GetSynGram().Get_Net().FindTag(tag_name);
         if( itag==UNKNOWN )
          {
           UFString msg = format_str( L"Tag '%s' not found\n", tag_name.c_str() );
           throw E_BaseException(msg);
          }

         const ThesaurusTag &tt = pm.GetDict().GetSynGram().Get_Net().GetTagDefs()[itag];

         if( tt.CountValues()>0 )
          { 
           int ivalue=UNKNOWN;
           ivalue = tt[tag_value];
           if( ivalue==UNKNOWN )
            {
             UFString msg = format_str( L"Tag value '%s' not found\n", tag_value.c_str() );
             throw E_BaseException(msg);
            }
          }

         lem::Collect< std::pair<UCString /*tag*/, UCString /*value*/> > tags;
         tags.push_back( std::make_pair(tag_name,tag_value) );
         tags_ptr = pm.GetDict().GetSynGram().Get_Net().CompileTags( tags );
        }
      }
    }

   lem::MCollect<int> links;

   if( rlink->GetType().IsInt() )
    {
     links.push_back( rlink->GetInt() );
    }
   else if( rlink->GetType().IsString() )
    {
     int link = pm.GetDict().GetSynGram().Find_Link( rlink->GetString() );
     if( link==UNKNOWN )
      throw E_BaseException( format_str( L"Unknown link name '%s' in 'thesaurus_find'", rlink->GetString().c_str() ) );

     links.push_back(link);
    }
   else if( rlink->GetType().IsTuple() )
    {
     const TrTuple &tu = rlink->GetTuple();
     for( int q=0; q<tu.Count(); ++q )
      {
       const TrValue &vq = tu[q];
        
       if( vq.GetType().IsInt() )
        {
         links.push_back( vq.GetInt() );
        }
       else if( rlink->GetType().IsString() )
        {
         int link = pm.GetDict().GetSynGram().Find_Link( vq.GetString() );
         if( link==UNKNOWN )
          throw E_BaseException( format_str( L"Unknown link name '%s' in 'thesaurus_find'", rlink->GetString().c_str() ) );

         links.push_back(link);
        }
       else
        {
         UFString msg = format_str( L"Invalid item #%d in link type tuple argument(1) in function 'thesaurus_find' must be integer or string, got '%s'", q, vq.GetType().GetName().c_str() );
         throw E_BaseException( msg );
        }
      }
    }
   else
    {
     UFString msg = format_str( L"Second argument in function 'thesaurus_find' must be integer or string, got '%s'", rlink->GetType().GetName().c_str() );
     throw E_BaseException( msg );
    }

   SynGram &sg = pm.GetDict().GetSynGram();
   SG_Net &net = sg.Get_Net();
  
   bool collecting = false;
   if( name.eqi(L"thesaurus_collect") )
    {
     ret = new TrValue( new TrTuple(), true );
     collecting = true;
    }

   lem::MCollect<int> ekeys;

   if( start->GetType().IsTree() )
    {
     // Исходная точка - словоформа, возможно с альтернативными версиями.
     // Берем ключи всех версий.
     const Tree_Node &tn = start->GetTree();
     const Word_Form &wf = tn.GetNode();

     Word_Form *new_wf = NULL;

     const int nver = 1 + CastSizeToInt(wf.GetAlts().size());
     for( int iver=0; iver<nver; ++iver )
      {
       const Word_Form &ver = iver==0 ? wf : *wf.GetAlts()[iver-1];
       const int ek = ver.GetEntryKey();
       ekeys.push_back(ek);
      }
    }
   else if( start->GetType().IsInt() )
    {
     // Задан ключ статьи...
     const int ek = start->GetInt();
     ekeys.push_back(ek);  
    }
   else
    {
     lem::UFString msg( lem::format_str( L"Invalid first argument in 'thesaurus_find' call: tree or integer is expected, got '%s'", start->GetType().GetName().c_str() ) );
     throw E_BaseException(msg);
    }

   lem::MCollect<int> ekeys2;

   for( lem::Container::size_type li=0; li<links.size(); ++li )
    {
     const int link = links[li];
     lem::MCollect< Tree_Link > allowed_links;
     allowed_links.push_back( link );

     std::set<int> linked;
     ekeys2.clear();

     #if LEM_DEBUGGING==1
     int nekeys = CastSizeToInt( ekeys.size() );
     #endif

     for( lem::Container::size_type ki=0; ki<ekeys.size(); ++ki )
      {
       const int ek = ekeys[ki];

       if( ek==UNKNOWN )
        continue; 

       if( tags0_ptr.NotNull() )
        {
         net.Find_Linked_Entries( ek, 0, linked, false, true, &allowed_links, tags0_ptr.IsNull() ? NULL : &*tags0_ptr );
        }

       if( linked.empty() )
        {
         net.Find_Linked_Entries( ek, 0, linked, false, true, &allowed_links, tags_ptr.IsNull() ? NULL : &*tags_ptr );
        }
         
       for( std::set<int>::const_iterator it=linked.begin(); it!=linked.end(); it++ )
        {
         const int k = *it;
         ekeys2.push_back(k);
        }
      }

     ekeys = ekeys2; 
    }

   #if LEM_DEBUGGING==1
   int nekeys = CastSizeToInt( ekeys.size() );
   #endif

   Word_Form *new_wf = NULL;

   for( lem::Container::size_type iek=0; iek<ekeys.size(); ++iek )
    {
     const int ek = ekeys[iek];

     const SG_Entry &e = sg.GetEntry(ek);

     // атрибуты словарной статьи сразу скопируем как состояния словоформы.
     const CP_Array& attrs = e.attrs();

     Word_Form *new_ver = new Word_Form( e.GetName(), ek, attrs );

     if( collecting )
      {
       Tree_Node *new_tn = new Tree_Node( new_ver, true );
       ret->GetTuple().Add( new TrValue(new_tn,true) );
      }
     else
      {  
       if( new_wf==NULL )
        new_wf = new_ver;
       else
        new_wf->AddAlt(new_ver);
      }
    }

   if( !collecting )
    {  
     if( new_wf!=NULL )
      {
       Tree_Node *new_tn = new Tree_Node( new_wf, true );
       ret = new TrValue( new_tn, true );
      }
     else
      {
       // В тезаурусе ничего не найдено.
       // Возвращаем void
       ret = new TrValue;
      } 
    } 
  }
 else if( name.eq_begi( L"wordform_" ) )
  {
   if( name.eqi( L"wordform_class" ) )
    {
     lem::Ptr<TrValue> tn = args[0]->Run(constraints,pm,ctx,trace_log);
     
     Tree_Node &t = tn->GetTree();
     Word_Form &wf = t.GetNode(); 
     const int ek = wf.GetEntryKey();

     int iclass=UNKNOWN;
     if( ek!=UNKNOWN )
      iclass = pm.GetDict().GetSynGram().GetEntry(ek).GetClass();

     ret = new TrIntValue(iclass);
    }
   else if( name.eqi( L"wordform_decompose" ) )
    {
     // Декомпозиция - разбираем результат свертки на составные словоформы
     // tuple wordform_decompose( tree x )

     lem::Ptr<TrValue> tn = args[0]->Run(constraints,pm,ctx,trace_log);
     
     const Tree_Node &t = tn->GetTree();
     const Word_Form &wf = t.GetNode(); 

     TrTuple *tuple = new TrTuple;
/*
     if( wf.IsConvolved() )
      {
       for( int i=0; i<wf.GetnConvolved(); ++i )
        {
         const int ie = wf.GetEList()[i];

         // собираем wname
         Lexem wname = wf.GetPartName(i);

         if( wf.GetiCenter()==i )
          {
           // имеем дело с грамматическим центром, поэтому сюда надо скопировать
           // весь список координатных пар и подцепить ветки разлагаемого узла
           Word_Form *wfx = new Word_Form( wname, ie, wf.GetPairs() );

           Tree_Node *ntn = new Tree_Node(t);
           ntn->SetNode(wfx);

           TrValue *elem = new TrValue(ntn,true);
           tuple->Add(elem);
          } 
         else
          {
           Word_Form *wfx = new Word_Form( wname, ie );
           Tree_Node *ntn = new Tree_Node(wfx,true);
           TrValue *elem = new TrValue(ntn,true);
           tuple->Add(elem);
          } 

        } 
      }
     else*/
      {
       // Декомпозиция свертки не требуется - вернем копию аргумента.
       Tree_Node *ntn = new Tree_Node(t);
       TrValue *elem = new TrValue(ntn,true);
       tuple->Add(elem);
      }

     ret = new TrValue(tuple,true);
    }
   else if( name.eqi( L"wordform_pack" ) )
    {
     // Упаковка словоформ из заданного списка (tuple) в одну словоформу с образованием
     // альтернативных форм.
     lem::Ptr<TrValue> tn = args[0]->Run(constraints,pm,ctx,trace_log);
     const TrTuple &t = tn->GetTuple();
 
     Word_Form *wf = NULL;

     for( int i=0; i<t.Count(); ++i )
      {
       const Tree_Node &tree_i = t[i].GetTree();
       if( wf==NULL )
        wf = new Word_Form(tree_i.GetNode());
       else
        wf->AddAlt( new Word_Form(tree_i.GetNode()) );
      }

     if( wf!=NULL )
      ret = new TrValue( new Tree_Node(wf,true), true );
     else
      ret = new TrValue;
    }
   else if( name.eqi( L"wordform_root" ) )
    {
     // Возвращается корневой узел дерева, без веток.
     lem::Ptr<TrValue> tn = args[0]->Run(constraints,pm,ctx,trace_log);
     
     Tree_Node &t = tn->GetTree();
     Word_Form &wf = t.GetNode(); 

     Tree_Node *ntn = new Tree_Node(wf);

     // Скопируем все маркировки
     for( lem::Container::size_type i=0; i<t.GetMarks().size(); ++i )
      {
       const TreeMarks &src_marks = *t.GetMarks()[i];
       TreeMarks & dst_marks = ntn->TouchMarks( src_marks.GetName() );
       dst_marks.Add( src_marks );
      }

     ret = new TrValue(ntn,true);
    }
   else if( name.eqi( L"wordform_replace" ) )
    {
     // Заменяем корень дерева на указанную словоформу
     lem::Ptr<TrValue> tn = args[0]->Run(constraints,pm,ctx,trace_log); // изменяемый корень
     lem::Ptr<TrValue> wf = args[1]->Run(constraints,pm,ctx,trace_log); // подставляемая словоформа
     
     Tree_Node &t = tn->GetTree();
     t.SetNode( new Word_Form( wf->GetTree().GetNode() ) );

     //ret = new TrValue(&t,false);
    }
   else if( name.eqi( L"wordform_create" ) )
    {
     // wordform_create( класс, имя_статьи [, форма [, координата1, состояние1 [, ... ] ] ] )
     
     const int iclass = args[0]->Run( constraints,pm, ctx, trace_log )->GetInt();
     Lexem ename = args[1]->Run( constraints,pm, ctx, trace_log )->GetString();

     Lexem fname = ename;
     if( args.size()>2 )
      fname = args[2]->Run( constraints,pm, ctx, trace_log )->GetString();
 
     pm.GetDict().GetLexAuto().TranslateLexem( ename );
     pm.GetDict().GetLexAuto().TranslateLexem( fname );

     const int ie = pm.GetDict().GetSynGram().FindEntry(ename,iclass,false);
     if( ie==UNKNOWN )
      {
       UFString msg = format_str( L"Can not create entry: class=%d name=%s", iclass, ename.c_str() );
       throw E_BaseException(msg);
      }

     const int ekey = pm.GetDict().GetSynGram().GetEntry(ie).GetKey();
     Word_Form *wf = new Word_Form( fname, ekey );

     for( lem::Container::size_type i=3; i<args.size(); i+=2 )
      {
       const int icoord = args[i]->Run( constraints,pm, ctx, trace_log )->GetInt();
       const int istate = args[i+1]->Run( constraints,pm, ctx, trace_log )->GetInt();
       wf->SetState( GramCoordPair( icoord, istate ), false );
      } 
      
     Tree_Node *tn = new Tree_Node(wf,true);
     ret = new TrValue( tn, true );
    }
   else if( name.eqi( L"wordform_get_coord" ) )
    {
     // Определение состояния координаты
     // wordform_get_coord( узел, координата )
     lem::Ptr<TrValue> tn = args[0]->Run(constraints,pm,ctx,trace_log);
     lem::Ptr<TrValue> coord = args[1]->Run(constraints,pm,ctx,trace_log);
     const Solarix::Word_Form &wf = tn->GetTree().GetNode();
     const int icoord = coord->GetInt();

     const int istate = wf.GetState( GramCoordAdr(icoord) );
     ret = new TrIntValue(istate);
    }
   else if( name.eqi( L"wordform_get_dims" ) )
    {
     // Список измерений в виде цепочки [измерение,состояние,измерение,состояние,...]
     // wordform_get_dims( узел )
     lem::Ptr<TrValue> tn = args[0]->Run(constraints,pm,ctx,trace_log);
     lem::Ptr<TrValue> coord = args[1]->Run(constraints,pm,ctx,trace_log);
     const Solarix::Word_Form &wf = tn->GetTree().GetNode();

     TrTuple *tu = new TrTuple();
     const int ekey = wf.GetEntryKey();
     if( !lem::is_quantor(ekey) )
      {
       const Solarix::SG_Entry &e = pm.GetDict().GetSynGram().GetEntry(ekey);
       const int iclass = e.GetClass();
       if( !lem::is_quantor(iclass) )
        {
         const Solarix::SG_Class &cls = pm.GetDict().GetSynGram().GetClass(iclass);
         for( lem::Container::size_type i=0; i<cls.dims().size(); ++i )
          {
           const int icoord = cls.dims()[i].GetIndex();
           const int istate = wf.GetState( GramCoordAdr(icoord) );
           tu->Add( new TrIntValue(icoord) ); 
           tu->Add( new TrIntValue(istate) ); 
          } 
        }
      }

     ret = new TrValue(tu,true);
    }
   else if( name.eqi( L"wordform_language" ) )
    {
     lem::Ptr<TrValue> tn = args[0]->Run(constraints,pm,ctx,trace_log);
     Tree_Node &t = tn->GetTree();
     Word_Form &wf = t.GetNode(); 
     const int ek = wf.GetEntryKey();

     int ilang=UNKNOWN;
     if( ek!=UNKNOWN )
      {
       const int iclass = pm.GetDict().GetSynGram().GetEntry(ek).GetClass();
       if( !lem::is_quantor(iclass) )
        {
         ilang = pm.GetDict().GetSynGram().GetClass(iclass).GetLanguage();
        }
      } 

     ret = new TrIntValue(ilang);
    }
   else if( name.eqi( L"wordform_entry" ) )
    {
     lem::Ptr<TrValue> tn = args[0]->Run(constraints,pm,ctx,trace_log);
     Tree_Node &t = tn->GetTree();
     Word_Form &wf = t.GetNode(); 
     const int ek = wf.GetEntryKey();

     ret = new TrIntValue(ek);
    }
   else if( name.eqi( L"wordform_pos" ) )
    {
     lem::Ptr<TrValue> tn = args[0]->Run(constraints,pm,ctx,trace_log);
     Tree_Node &t = tn->GetTree();
     Word_Form &wf = t.GetNode(); 
     const int pos = wf.GetOriginPos();
     ret = new TrIntValue(pos);
    }
   else if( name.eqi( L"wordform_lexem" ) )
    {
     lem::Ptr<TrValue> tn = args[0]->Run(constraints,pm,ctx,trace_log);
     Tree_Node &t = tn->GetTree();
     Word_Form &wf = t.GetNode(); 
     //const int ek = wf.GetEntryKey();

     ret = new TrValue( *wf.GetName() );
    }
   else if( name.eqi( L"wordform_set_coord" ) ||
            name.eqi( L"wordform_setadd_coord" ) )
    {
     lem::Ptr<TrValue> tn = args[0]->Run(constraints,pm,ctx,trace_log);
     Tree_Node &t = tn->GetTree();
     Word_Form &wf = t.GetNode(); 
     const int ek = wf.GetEntryKey();

     // Изменение грамматических атрибутов у словоформы
     // wordform_set_coord( узел, координата0, состояние0 [, координата1, состояние1, ... ] )
     // если координатаi - кортеж, то берем список пар из кортежа.
     const bool add = name.eqi( L"wordform_setadd_coord" );

     for( lem::Container::size_type i=1; i<args.size(); )
      {
       lem::Ptr<TrValue> rcoord = args[i]->Run(constraints,pm,ctx,trace_log);

       if( rcoord->GetType().IsTuple() )
        {
         const TrTuple &tu = rcoord->GetTuple();
         for( int j=0; j<tu.Count(); j+=2 )
          {
           const int icoord = tu.values[j]->GetInt(); 
           const int istate = tu.values[j+1]->GetInt(); 
           if( icoord!=UNKNOWN && istate!=UNKNOWN )
            {
             Word_Form &wf2 = tn->GetTree().GetNode();
             wf2.SetState( GramCoordPair( icoord, istate ), add, true );
            }
          }

         i++;
        }
       else
        {
         lem::Ptr<TrValue> rstate = args[i+1]->Run(constraints,pm,ctx,trace_log);

         i+=2; 

         const int icoord = rcoord->GetInt(); 
         const int istate = rstate->GetInt(); 
         if( icoord!=UNKNOWN && istate!=UNKNOWN )
          {
           Word_Form &wf2 = tn->GetTree().GetNode();
           wf2.SetState( GramCoordPair( icoord, istate ), add, true );
          }
        }
      } 

     ret = tn;
    }
   else if( name.eqi( L"wordform_clear_coord" ) )
    {
     // Удаляем все координатные пары с указанной координатой у словоформы
     // wordform_clear_coord( узел [, координата0 [, координата1, ... ] ] )
     lem::Ptr<TrValue> tn = args[0]->Run(constraints,pm,ctx,trace_log);
     Tree_Node &t = tn->GetTree();
     Word_Form &wf = t.GetNode(); 

     for( lem::Container::size_type i=1; i<args.size(); i++ )
      {
       lem::Ptr<TrValue> rcoord = args[i]->Run(constraints,pm,ctx,trace_log);
       const int icoord = rcoord->GetInt(); 
       if( icoord!=UNKNOWN )
        {
         wf.Remove_Coord_States( GramCoordAdr(icoord) );
        }
      }

     ret = tn;
    }
   else if( name.eqi( L"wordform_refresh" ) )
    {
     lem::Ptr<TrValue> tn = args[0]->Run(constraints,pm,ctx,trace_log);

     // Приведение лексического состояния в соответствии с установленными ранее координатами. 
     // wordform_refresh( узел )
     tn->GetTree().GetNode().Rename_By_States( pm.GetDict().GetSynGram(), true );
     ret = tn;
    }
   else if( name.eqi( L"wordform_copy_coord" ) )
    {
     lem::Ptr<TrValue> tn = args[0]->Run(constraints,pm,ctx,trace_log);
     Tree_Node &t = tn->GetTree();
     Word_Form &wf = t.GetNode(); 
     const int ek = wf.GetEntryKey();

     // Копирование указанных координат из другого узла
     // wordform_copy_coord( узел, узел_источник, координата0 [, координата1, ... ] )

     lem::Ptr<TrValue> rsrc = args[1]->Run(constraints,pm,ctx,trace_log);
     const Word_Form &src_wf = rsrc->GetTree().GetNode();

     for( lem::Container::size_type i=2; i<args.size(); i+=2 )
      {
       lem::Ptr<TrValue> rcoord = args[i]->Run(constraints,pm,ctx,trace_log);

       const int icoord = rcoord->GetInt(); 

       IntCollect istate = src_wf.GetStates( GramCoordAdr(icoord) );

       for( lem::Container::size_type j=0; j<istate.size(); ++j )
        tn->GetTree().GetNode().SetState( GramCoordPair( icoord, istate[j] ), false );
      } 

     ret = tn;
    }
  }
 else if( name.eqi( L"entry_name" ) )
  {
   // Аргумент - entry key
   const int ekey = args[0]->Run(constraints,pm,ctx,trace_log)->GetInt();
   if( ekey==UNKNOWN )
    {
     ret = new TrValue( lem::UCString(L"") );
    }
   else 
    {
     const SG_Entry &e = pm.GetDict().GetSynGram().GetEntry(ekey);
     ret = new TrValue( e.GetName() );
    }
  }
 else if( name.eqi( L"entry_count_forms" ) )
  {
   // Вернет кол-во грамматических форм в статье
   // Аргумент - entry key
   const int ekey = args[0]->Run(constraints,pm,ctx,trace_log)->GetInt();
   if( ekey==UNKNOWN )
    {
     ret = new TrIntValue(0);
    }
   else 
    {
     const SG_Entry &e = pm.GetDict().GetSynGram().GetEntry(ekey);
     ret = new TrIntValue( CastSizeToInt(e.forms().size()) );
    }
  }
 else if( name.eqi( L"entry_find" ) )
  {
   // Поиск ключа статьи по её классу и имени
   const int id_class = args[0]->Run(constraints,pm,ctx,trace_log)->GetInt();
   UCString ename = args[1]->Run(constraints,pm,ctx,trace_log)->GetString();

   const int ie = pm.GetDict().GetSynGram().FindEntry( ename, id_class, false );

   ret = new TrIntValue( ie );
  }
 else if( name.eqi( L"phrase_find" ) )
  {
   int id_phrase=UNKNOWN;

   lem::UFString text;

   lem::Ptr<TrValue> a0 = args[0]->Run(constraints,pm,ctx,trace_log);
   if( a0->GetType().IsString() )
    {
     text = a0->GetString().c_str();
    }
   else if( a0->GetType().IsTuple() )
    {
     // из списка строк сформируем одну строку
     const TrTuple &t = a0->GetTuple();
     for( int i=0; i<t.Count(); ++i )
      {
       const TrValue &v = t[i];
       if( v.GetType().IsString() )
        {
         text.Add_Dirty( v.GetString().c_str() );
        }
       else
        {
         lem::MemFormatter mem;
         mem.printf( "Tuple in phrase_find must contain strings, not %us", v.GetType().GetName().c_str() );
         throw lem::E_BaseException(mem.string());
        }
      }

     text.calc_hash(); 
    }
   else
    {
     lem::MemFormatter mem;
     mem.printf( "phrase_find expects string or tuple as first argument, not %us", a0->GetType().GetName().c_str() );
     throw lem::E_BaseException(mem.string());
    }

   id_phrase = pm.GetDict().GetSynGram().FindComplexEntry(text);

   ret = new TrIntValue( id_phrase );
  }
 else if( name.eqi( L"entry_get_form" ) )
  {
   // Вернет грамматическую форму с заданным порядковым номером в статье
   // первый аргумент - entry key
   const int ekey = args[0]->Run(constraints,pm,ctx,trace_log)->GetInt();
   // второй аргумент - индекс формы
   const int iform = args[1]->Run(constraints,pm,ctx,trace_log)->GetInt();
   if( ekey==UNKNOWN )
    {
     throw E_BaseException( L"Invalid argument ie=-1 in entry_get_form" );
    }
   else 
    {
     const SG_Entry &e = pm.GetDict().GetSynGram().GetEntry(ekey);
     const SG_EntryForm &f = e.forms()[iform];

     Word_Form *wf = new Word_Form( f.name(), e.GetKey(), f.coords() );
     Tree_Node *tn = new Tree_Node( wf, true );
     ret = new TrValue(tn,true);
    }
  }
 else if( name.eqi( L"entry_forms" ) )
  {
   // Проекция слова - получаем кортеж словоформ-проекций для этой лексемы
   UCString form = args[0]->Run(constraints,pm,ctx,trace_log)->GetString();

   Lexem *ml = new Lexem(form);
   pm.GetDict().GetLexAuto().TranslateLexem(*ml,true);

   RC_Lexem rc(ml);
   lem::MCollect<Solarix::Word_Coord> list;
   MCollect<ProjScore> val_list;
   lem::PtrCollect<LA_ProjectInfo> prj_extra_inf;


   pm.GetDict().GetLexAuto().ProjectWord(
                                         rc,
                                         list,
                                         val_list,
                                         prj_extra_inf,
                                         LexicalAutomat::Wordforms,
                                         0,
                                         UNKNOWN,
                                         NULL
                                        );
   
   TrTuple *ret_tuple = new TrTuple;
   
   for( lem::Container::size_type i=0; i<list.size(); ++i )
    {
     const Word_Coord & wc = list[i];

     if( !wc.IsUnknown() )
      {
       const int ie = wc.GetEntry();
       const SG_Entry &e = pm.GetDict().GetSynGram().GetEntry(ie);
       const SG_EntryForm &f = e.forms()[wc.GetForm()];

       Word_Form *wf = new Word_Form( rc, rc, e.GetKey(), f.coords(), val_list[i].val );
       Tree_Node *tn = new Tree_Node( wf, true );
       TrValue *tr = new TrValue(tn,true);
       ret_tuple->Add(tr);
      }
    }

   ret = new TrValue( ret_tuple, true );
  }
 else if( name.eq_begi( L"seq_" ) )
  {
   lem::Ptr<TrValue> rname = args[0]->Run(constraints,pm,ctx,trace_log);
   const UCString & seq_name = rname->GetString();

   if( name.eqi( L"seq_create" ) )
    {
     // Создание генератора
     // seq_create( имя_генератора [, нач_значение] )

     int i0=0;

     if( args.size()>1 )
      {
       lem::Ptr<TrValue> ri0 = args[1]->Run(constraints,pm,ctx,trace_log);
       i0 = ri0->GetInt();
      }
    
     bool rc = pm.CreateSequence( seq_name, i0 );

     ret = new TrIntValue(rc);
    }
   else if( name.eqi( L"seq_get" ) )
    {
     // Генерация очередного числа
     // seq_get( имя_генератора [, смещение ] )
     int step=1;

     if( args.size()>1 )
      {
       lem::Ptr<TrValue> rstep = args[1]->Run(constraints,pm,ctx,trace_log);
       step = rstep->GetInt();
      }
    
     const int v = pm.GetSequenceValue( seq_name, step );
     ret = new TrIntValue(v);
    }
  }
 else if( name.eq_begi( L"fun_" ) )
  { 
   if( name.eqi( L"fun_create" ) )
    { 
     // Похоже на лямбда-функцию, но тут мы работаем с именованной функцией.
     const TrFunCall* fun_ptr = args[0];
     ret = new TrValue( fun_ptr );
    }
   else if( name.eqi( L"fun_call" ) )
    {
     TrContextInvokation ctx2(NULL); // Вызываемая функция не видит наших локальных аргументов!

     lem::Ptr<TrValue> rfun = args[0]->Run(constraints,pm,ctx,trace_log);
     const TrFunCall *f = & rfun->GetFun();
     const TrClosureVars *cv = rfun->GetClosureVars();

     if( cv!=NULL )
      {
       // Значения переменных, связанных с контекстом создания лямбда-функции.
       for( lem::Container::size_type j=0; j<cv->local_name.size(); ++j )
        {
         lem::Ptr<TrValue> local_val( (TrValue*)cv->local_value[j], null_deleter() );
         ctx2.AddVar( cv->local_name[j], local_val );
        }
  
       if( dynamic_cast<const TrFun_User*>(f)!=NULL )
        {
         // Также зададим аргументы вызова функции, их количество должно соответствовать
         // сигнатуре функции.
         int iarg=0, narg=0;
         for( lem::Container::size_type i=1; i<args.size(); ++i, ++iarg )
          {
           lem::Ptr<TrValue> rarg = args[i]->Run(constraints,pm,ctx,trace_log);
           ctx2.AddVar( cv->arg_name[iarg], rarg );
           narg++;
          }

         if( narg!=CastSizeToInt(cv->arg_name.size()) )
          {
           UFString msg = format_str( L"Number of arguments in lambda function call does not match its declaration: must be %d, got %d", CastSizeToInt(cv->arg_name.size()), narg );
           throw E_BaseException(msg);
          }
        }
       else
        {
         LEM_STOPIT; 
        }
      } 

     ret = f->Run( constraints,pm, ctx2, trace_log );
    }
  }
 else if( name.eq_begi( L"mark_" ) )
  {
   lem::Ptr<TrValue> a0 = args[0]->Run(constraints,pm,ctx, trace_log);

   if( name.eqi( L"mark_get" ) )
    {
     // Получение параметра из именованного контейнера маркировок в узле
     // mark_get( узел, имя_блока, индекс_параметра )
     lem::Ptr<TrValue> rname = args[1]->Run(constraints,pm,ctx,trace_log);
     const UCString &val_name = rname->GetString();
  
     lem::Ptr<TrValue> ri = args[2]->Run(constraints,pm,ctx, trace_log);
     const int ivalue = ri->GetInt();

     if( a0->GetType().IsTree() )
      {
       Tree_Node &tn = a0->GetTree();
     
       TreeMarks *marks = tn.FindMarks( val_name );
       if( marks!=NULL )
        {
         TrValue & v = (*marks)[ivalue];
         ret = new TrValue(v);
        }
       else
        {
         throw E_BaseException( format_str(L"Mark block [%us] does not exist in tree node", val_name.c_str() ) );
        }
      }
     else if( a0->GetType().IsTrees() )
      {
       Variator &var = a0->GetTrees();
     
       TreeMarks *marks = var.FindMarks( val_name );
       if( marks!=NULL )
        {
         TrValue & v = (*marks)[ivalue];
         ret = new TrValue(v);
        }
       else
        {
         throw E_BaseException( format_str(L"Mark block [%us] does not exist in variator", val_name.c_str() ) );
        }
      }
    }
   else if( name.eqi( L"mark_count" ) )
    {
     // Количество параметров в блоке маркировок.
     // Вернет 0, если блока не существует.
     // mark_count( узел, имя_блока [, имя_параметра] )

     lem::Ptr<TrValue> rname = args[1]->Run(constraints,pm,ctx,trace_log);
     const UCString &val_name = rname->GetString();

     lem::Ptr<TrValue> pname;
     if( args.size()==3 )
      {
       pname = args[2]->Run(constraints,pm,ctx,trace_log);
      } 
  
     if( a0->GetType().IsTree() )
      {
       const Tree_Node &tn = a0->GetTree();

       const TreeMarks *marks = tn.FindMarks( val_name );
       if( marks!=NULL )
        {
         if( pname.IsNull() )
          ret = new TrIntValue( marks->Size() );
         else
          {
           int c=0;
           for( int j=0; j<marks->Size(); ++j )
            if( (*marks)[j].eq( *pname ) )
             c++;

           ret = new TrIntValue(c);
          }
        }
       else
        {
         ret = new TrIntValue(0);
        }
      }
     else if( a0->GetType().IsTrees() )
      {
       const Variator &var = a0->GetTrees();
       const TreeMarks *marks = var.FindMarks( val_name );

       if( marks!=NULL )
        {
         if( pname.IsNull() )
          ret = new TrIntValue( marks->Size() );
         else
          {
           int c=0;
           for( int j=0; j<marks->Size(); ++j )
            if( (*marks)[j].eq( *pname ) )
             c++;

           ret = new TrIntValue(c);
          }
        }
       else
        {
         ret = new TrIntValue(0);
        }
      }
    }
   else if( name.eqi( L"mark_clear" ) )
    {
     // Очистка блока маркировок
     // mark_clear( узел, имя_блока1 [, имя_блока2 ... ] ] )

     for( lem::Container::size_type k=1; k<args.size(); ++k )
      { 
       lem::Ptr<TrValue> rname = args[k]->Run(constraints,pm,ctx,trace_log);
       const UCString &val_name = rname->GetString();
  
       if( a0->GetType().IsTree() )
        {
         Tree_Node &tn = a0->GetTree();
   
         TreeMarks *marks = tn.FindMarks( val_name );
         if( marks!=NULL )
          {
           marks->Clear();
          }
        }
       else if( a0->GetType().IsTrees() )
        {
         Variator &var = a0->GetTrees();

         TreeMarks *marks = var.FindMarks( val_name );
         if( marks!=NULL )
          {
           marks->Clear();
          }
        }
      } 

     ret = a0;
    }
   else if( name.eqi( L"mark_add" ) )
    {
     // Добавление параметра в именованный контейнер маркировок в узле
     // mark_add( узел, имя_блока, параметр1 [, параметр2 ... ] )
     lem::Ptr<TrValue> rname = args[1]->Run(constraints,pm,ctx,trace_log);
     const UCString &val_name = rname->GetString();
  
     for( lem::Container::size_type k=2; k<args.size(); ++k )
      {
       lem::Ptr<TrValue> rv = args[k]->Run(constraints,pm,ctx, trace_log);
 
       if( rv->GetType().IsTree() )
        {
         TrValue *nrv = new TrValue( new Tree_Node( rv->GetTree() ), true );
         rv = nrv;
        }
       else if( rv->GetType().IsTrees() )
        {
         TrValue *nrv = new TrValue( new Variator( rv->GetTrees() ), true );
         rv = nrv;
        }

       if( a0->GetType().IsTree() )
        {
         Tree_Node &tn = a0->GetTree();

         TreeMarks &marks = tn.TouchMarks( val_name );
         marks.Add( new TrValue( *rv ) );
        }
       else if( a0->GetType().IsTrees() )
        {
         Variator &var = a0->GetTrees();

         TreeMarks &marks = var.TouchMarks( val_name );
         marks.Add( new TrValue( *rv ) );
        }
      }

     ret = a0;
    }
   else if( name.eqi( L"mark_copy") )
    {
     // Копирование маркировок
     // mark_copy( приемник, источник [, имя_блока] )
     Tree_Node &dst_tn = a0->GetTree();
     Tree_Node &src_tn = args[1]->Run(constraints,pm,ctx,trace_log)->GetTree();

     if( args.size()==2 )
      {
       for( lem::Container::size_type i=0; i<src_tn.GetMarks().size(); ++i )
        {
         const TreeMarks &src_marks = *src_tn.GetMarks()[i];
         TreeMarks & dst_marks = dst_tn.TouchMarks( src_marks.GetName() );
         dst_marks.Add( src_marks );
        }
      }
     else
      {
       const UCString &mark_name = args[2]->Run( constraints,pm, ctx, trace_log )->GetString();
       const TreeMarks *src_marks = src_tn.FindMarks(mark_name);
       if( src_marks!=NULL )
        {
         TreeMarks & dst_marks = dst_tn.TouchMarks( src_marks->GetName() );
         dst_marks.Add( *src_marks );
        }
      }

     ret = a0;
    } 
   else
    {
     LEM_STOPIT;
    }
  }
 else if( name.eq_begi( L"syntax_analysis" ) )
  {
   // Выполняем синтаксический анализ для аргумента-вариатора.
   // syntax_analysis( контекст, id_language [, method] )

   lem::Ptr<TrValue> a_ctx  = args[0]->Run(constraints,pm,ctx,trace_log);
   Solarix::Variator &var = a_ctx->GetTrees();

   Solarix::Dictionary &dict = pm.GetDict();

   lem::Ptr<TrValue> a_lang = args[1]->Run(constraints,pm,ctx,trace_log);
   int id_language=a_lang->GetInt();
   if( id_language==UNKNOWN )
    id_language = dict.GetLexAuto().GuessLanguage( var );   

   int method=0; // по умолчанию - нисходящий парсер.
   if( args.size()==3 )
    {
     lem::Ptr<TrValue> a_method = args[3]->Run(constraints,pm,ctx,trace_log);
     method = a_method->GetInt();
    }


   TextRecognitionParameters params;
   params.SetLanguageID(id_language);
   params.CompleteAnalysisOnly = true;
   params.AllowPrimaryFuzzyWordRecog = false;
   params.UseTokenReconstruction = false;
   params.UseSparsePatterns = false;
   params.UseTopDownThenSparse = false;

   if( method==2 )
    params.UseSparsePatterns = true;
   else if( method==3 )
    params.UseTopDownThenSparse = true;

   params.ApplyModel = false;
   params.timeout.max_elapsed_millisecs = constraints.GetTimeout();
   params.timeout.max_alt = 0;

   VariatorLexerTokens toks( var, &dict );
   VariatorLexer var_lexer( toks, 0, &dict, params, trace_log );

   WrittenTextAnalysisSession current_analysis( &dict, trace_log );
   current_analysis.SyntacticAnalysis(var_lexer,constraints);
   Res_Pack * pack = current_analysis.PickPack();
   Variator * var_result = pack->vars().front();
   pack->ForgetPtr(0);
   delete pack;

   ret = new TrValue( var_result, true );

/*
#if LEM_DEBUGGING==1
var.PrintV( *lem::mout, dict.GetSynGram(), true );

for( int i=0; i<var.size(); ++i )
 {
  const Tree_Node &n = var.get(i);
  const Word_Form &wf = n.GetNode();
  int ipos = wf.GetOriginPos();
  mout->printf( "%d %d\n", i, ipos );
 }
#endif
*/
  }
 else if( name.eq_begi( L"subst_cplx" ) )
  {
   // Подстановка фразовых переводов/синонимов
   lem::Ptr<TrValue> a_ctx  = args[0]->Run(constraints,pm,ctx,trace_log);
   lem::Ptr<TrValue> a_link  = args[1]->Run(constraints,pm,ctx,trace_log);
   lem::Ptr<TrValue> atags = args[2]->Run(constraints,pm,ctx,trace_log);

   lem::Ptr<TrValue> atracing;
   if( args.size()==4 )
    {
     atracing = args[3]->Run(constraints,pm,ctx,trace_log);
    }
 
   Solarix::Variator &var = a_ctx->GetTrees();

   const int link_type = a_link->GetInt();

   Solarix::Dictionary &dict = pm.GetDict();
   SynGram &sg = dict.GetSynGram();
   LexicalAutomat &la = dict.GetLexAuto();

   Solarix::SG_Net &th = dict.GetSynGram().Get_Net();

#if LEM_DEBUGGING==1
//var.Print( *mout, sg, false );
#endif
   
   TrTuple *ret_tuple = new TrTuple;
   ret = new TrValue( ret_tuple, true );
 
   lem::Ptr<Solarix::SG_TagFilter> tags_ptr0;   
   lem::Ptr<Solarix::SG_TagFilter> tags_ptr1;

   const int ieu = la.GetUnknownEntryKey();
   const int uekey = ieu==UNKNOWN ? UNKNOWN : sg.GetEntry(ieu).GetKey();

   // сканируем корни вариатора, начиная с левой границы
   int iroot=0;
   while( iroot<var.size() )
    {
     const Tree_Node &root = var.get(iroot);

     // Данное слово является началом фразы, присутствующей в тезаурусе?
     bool is_headword=false;
     int minlen=lem::int_max, maxlen=0;
 
     UCString headword;
     const int ekey0 = root.GetNode().GetEntryKey();
     if( ekey0==sg.I_BEGIN || ekey0==sg.I_END )
      {
       iroot++;
       continue;
      }

     if( ekey0!=UNKNOWN && ekey0!=uekey )
      {
       const int n = 1 + CastSizeToInt(root.GetNode().GetAlts().size());
       for( int q=0; q<n; ++q )
        {
         const int ekey = q==0 ? root.GetNode().GetEntryKey() : root.GetNode().GetAlts()[q-1]->GetEntryKey();
         headword = q==0 ? *root.GetNode().GetName() : *root.GetNode().GetAlts()[q-1]->GetName();
         headword.to_upper();

         int mi=lem::int_max, ma=0;
         if( dict.GetSynGram().IsComplexHeadword( headword, mi, ma ) )
          {
           is_headword = true;
           minlen = std::min( minlen, mi );
           maxlen = std::max( maxlen, ma );
           break;     
          }

         if( ekey!=UNKNOWN )
          { 
           const SG_Entry &e = sg.GetEntry(ekey);
           headword = e.GetName();
           Lexem::CorrectFormSpaces(headword);

           if( dict.GetSynGram().IsComplexHeadword( headword, mi, ma ) )
            {
             is_headword = true;
             minlen = std::min( minlen, mi );
             maxlen = std::max( maxlen, ma );
             break;     
            }
          }
 
         // Для случаев, когда левая часть (английская) - одно слово, просто смотрим,
         // что в тезаурусе есть такая фразовая статья и к ней есть перевод.
         const int te_id = sg.FindComplexEntry( headword.c_str() );
         if( te_id!=UNKNOWN )
          {
           lem::MCollect<int> linked_te_id;

           th.Find_Linked_DbEntries( te_id, link_type, linked_te_id, tags_ptr0.IsNull() ? NULL : tags_ptr0.get() );
           if( linked_te_id.empty() && tags_ptr1.NotNull() )
            th.Find_Linked_DbEntries( te_id, link_type, linked_te_id, tags_ptr1.get() );

           is_headword = !linked_te_id.empty(); 
           if( is_headword )
            { 
             minlen=maxlen=1;
             break;
            }
          }
        }
      } 
     else
      {
       headword = *root.GetNode().GetName();
       headword.to_upper();
       is_headword = sg.IsComplexHeadword( headword, minlen, maxlen );
     
       if( !is_headword )
        {
         // Для случаев, когда левая часть (английская) - одно слово, просто смотрим,
         // что в тезаурусе есть такая фразовая статья и к ней есть перевод.
         const int te_id = sg.FindComplexEntry( headword.c_str() );
         if( te_id!=UNKNOWN )
          {
           lem::MCollect<int> linked_te_id;

           th.Find_Linked_DbEntries( te_id, link_type, linked_te_id, tags_ptr0.IsNull() ? NULL : tags_ptr1.get() );

           if( linked_te_id.empty() && tags_ptr1.NotNull() )
            th.Find_Linked_DbEntries( te_id, link_type, linked_te_id, tags_ptr1.get() );

           is_headword = !linked_te_id.empty(); 
           if( is_headword )
            { 
             minlen=maxlen=1;
            }
          }
        } 
      }  

     if( is_headword )
      {
       // Нам нужен будет язык исходного текста.
       int id_lang = pm.GetDict().GetLexAuto().GuessLanguage(var);
     
       const wchar_t * spacer=L" ";
       if( id_lang!=UNKNOWN )
        {
         const SG_Language & lang = sg.languages()[id_lang];
         int iparam = lang.FindParam( L"Segmentation" );
         if( iparam!=UNKNOWN )
          {
           const UFString &pvalue = lang.params[iparam]->values.front();
           if( pvalue.eqi(L"dictionary_lookup") )
            spacer = L""; 
          }
        }  

       int nroots = var.size();
       if( var.roots_list().back()->GetNode().GetEntryKey()==sg.I_END )
        nroots--;

       // Это начало фразы.
       // Будем собирать фразы разной длины от maxlen до minlen и искать их.
       maxlen = std::min( maxlen, nroots-iroot ); 

       // подготовка - заполняем списки вариантов лемматизаций для каждого корня от iroot до iroot+maxlen
       lem::PtrCollect< lem::MCollect<lem::UCString> > cols;
       for( int q=0; q<maxlen; ++q )
        {
         const int iroot1 = iroot+q;
         const Word_Form &wf = var.get(iroot1).GetNode();

         lem::MCollect<lem::UCString> *col = new lem::MCollect<lem::UCString>();
         
         // исходное представление слова
         lem::UCString w( *wf.GetName() );
         w.to_upper();
         Lexem::CorrectFormSpaces(w);
         col->push_back(w);

         const int n = 1+CastSizeToInt(wf.GetAlts().size());
         for( int j=0; j<n; ++j )
          {
           const int ekey = j==0 ? wf.GetEntryKey() : wf.GetAlts()[j-1]->GetEntryKey();

           if( ekey!=UNKNOWN && ekey!=uekey )
            { 
             const SG_Entry &e = dict.GetSynGram().GetEntry(ekey);
             w = e.GetName();
             Lexem::CorrectFormSpaces(w);
             if( col->find(w)==UNKNOWN )
              col->push_back(w);
            }
          }

         cols.push_back(col);
        } 

       bool found_subst=false;

       // сначала пытаемся подобрать самые длинные перестановки   
       for( int l=maxlen; l>=minlen && !found_subst; --l )
        {
         // Собираем фразы длиной l.
         lem::MCollect<int> INDEX, TOP;
         INDEX.resize(l); INDEX.Nullify();
         TOP.resize(l);  

         int NTOT=1;
         for( int j=0; j<l; ++j )
          {
           const int rl = CastSizeToInt(cols[j]->size()); 
           TOP[j] = rl; 
           NTOT *= rl;
          }
                 
         // Максимум будет NTOT сочетаний.
         for( int iperm=0; iperm<NTOT; ++iperm )
          {
           // Собираем фразу
           lem::UFString te_text, tn_text;
           for( int j=0; j<l; ++j )
            {
             const UCString &w = cols[j]->get( INDEX[j] );
             if( !te_text.empty() ) 
              {
               te_text.Add_Dirty(spacer);
              }

             if( !tn_text.empty() )
              tn_text.Add_Dirty(Solarix::SG_Net::DefaultSegmentationDelimiter);

             te_text.Add_Dirty( w.c_str() );
             tn_text.Add_Dirty( w.c_str() );
            }

           te_text.calc_hash();
           tn_text.calc_hash();

           // Ищем фразу среди фразовых статей
           int te_id=UNKNOWN;
           const int tn_id = sg.GetStorage().FindPhraseNote( tn_text, Solarix::SynGram::SegmentationNote, te_id );

           if( te_id==UNKNOWN )
            {
//             te_id = sg.FindComplexEntry( tn_text );
             te_id = sg.FindComplexEntry( te_text );
            } 

           if( te_id!=UNKNOWN )
            {
             // Нашли!

             // Если возможно, определим ведущее слово в паттерне - индекс его должен быть уже
             // записан в тезаурус в TNOTES.
             int pivot_iword = UNKNOWN;              

             if( l==1 )
              {
               // Если левая часть имеет длину 1 слово, то определять особо нечего.
               pivot_iword=0; 
              }  
             else
              { 
               SG_PhraseNote str_pivot_iword;
               const int tn_id_pivot = sg.GetStorage().GetPhraseNote( te_id, Solarix::SynGram::PivotNote, str_pivot_iword );
               if( !str_pivot_iword.GetData().empty() )
                pivot_iword = lem::to_int(str_pivot_iword.GetData());
              }
             
             // Если ведущее слово известно, то мы передадим копию соответствующей словоформы в
             // возвращаемом кортеже.
             std::auto_ptr<Solarix::Tree_Node> pivot_wordform;
             if( pivot_iword!=UNKNOWN )
              pivot_wordform = std::auto_ptr<Solarix::Tree_Node>( new Solarix::Tree_Node( var.get(iroot+pivot_iword) ) );

             // Теперь надо получить связанные правые части и отобрать те, которые соответствуют
             // по фильтру тегов.

             lem::MCollect<int> linked_te_id, tl_ids;

             th.FindComplexLinks( te_id, link_type, tl_ids, linked_te_id, tags_ptr0.IsNull() ? NULL : tags_ptr0.get() );
             if( linked_te_id.empty() && tags_ptr1.NotNull() )
              th.FindComplexLinks( te_id, link_type, tl_ids, linked_te_id, tags_ptr0.IsNull() ? NULL : tags_ptr1.get() );

             if( !linked_te_id.empty() )
              {
               // Получили множество вариантов перевода. Выберем подходящий, обычно это самый первый,
               // но иногда могут быть дополнительные требования на разрешенную позицию, например - менять
               // только в начале предложения.
               bool found_acceptable_link=false;  
               for( lem::Container::size_type p=0; p<tl_ids.size() && !found_acceptable_link; ++p )
                {
                 const int tl_id = tl_ids[p];
                 const int te_id_right = linked_te_id[p];

                 lem::PtrCollect< SG_LinkFlag > flags;
                 th.GetLinkFlags( tl_id, flags );

                 bool acceptable_link=true;

                 bool verbatim_subst=false;
                 bool as_adverb=false;

                 for( lem::Container::size_type j=0; j<flags.size(); ++j )
                  {
                   if(
                      flags[j]->GetFlag().eqi(Solarix::ThesaurusLinkFlags::SubstitutionTechnique) &&
                      flags[j]->GetValue().eqi(Solarix::ThesaurusLinkFlags::SubstituteLiterally)
                     )
                    {
                     verbatim_subst=true;
                    }
                   else
                    if(
                       flags[j]->GetFlag().eqi(Solarix::ThesaurusLinkFlags::SubstituteAsPartOfSpeech) &&
                       flags[j]->GetValue().eqi(Solarix::ThesaurusLinkFlags::AsAdverb)
                      )
                     {
                      as_adverb=true;
                     }
                  }

                 // буквальная подстановка принимается только в том случае, если
                 // фраза составлена из текущих слов, а не из лемм.
                 if( verbatim_subst && iperm!=0 )
                  continue;               

                 // Если буквальная подстановка для начала предложения - проверяем начальную позицию.
                 for( lem::Container::size_type j=0; j<flags.size(); ++j )
                  {
                   if(
                     flags[j]->GetFlag().eqi(Solarix::ThesaurusLinkFlags::SubstitutionPosition) &&
                     flags[j]->GetValue().eqi(Solarix::ThesaurusLinkFlags::OnlyAtBeginning)
                    )
                   {
                    if( iroot!=1 )
                     acceptable_link=false;

                    break;  
                   }

                   if(
                      flags[j]->GetFlag().eqi(Solarix::ThesaurusLinkFlags::SubstitutionPosition) &&
                      flags[j]->GetValue().eqi(Solarix::ThesaurusLinkFlags::WholePhrase) 
                     )
                    {
                     if( iroot!=1 )
                      acceptable_link=false;

                     if( l!=nroots-1 )
                      acceptable_link=false;

                     break;  
                    }
                  }

                 if( !acceptable_link )
                  continue; 

                 bool substitute_as_graf=false;

                 // Есть ли синтаксический граф для найденной правой фразы?
                 SG_PhraseNote hexdata;
                 const int tn_id = sg.GetStorage().GetPhraseNote( te_id_right, Solarix::SynGram::SyntaxNote, hexdata );

                 if( tn_id!=UNKNOWN )
                  {
                   substitute_as_graf=true; 

                   if( verbatim_subst )
                    {
                     substitute_as_graf=false;
                    }
                  }

                 if( as_adverb )
                  {
                   // вся цепочка слов должна быть подставлена как одно слово.

                   // и вставляем одну заглушку
                   const int unknown_entry = la.GetUnknownEntryKey();
                   Tree_Node *node_as_adverb = new Tree_Node( new Solarix::Word_Form( sg.GetEntry(unknown_entry).GetName(), unknown_entry ), true );
                   TreeDimension & node_words_dim = node_as_adverb->TouchDimension(L"self");

                   SG_PhraseNote hexdata;
                   const int tn_id = sg.GetStorage().GetPhraseNote( te_id_right, Solarix::SynGram::SegmentationNote, hexdata );

                   if( tn_id!=UNKNOWN )
                    {
                     const lem::UFString & tokens_str = hexdata.GetData();
                     const wchar_t delimiter[2] = { Solarix::SG_Net::DefaultSegmentationDelimiter, 0 };
                     lem::Collect<lem::UFString> words2;
                     lem::parse( tokens_str, words2, delimiter );

                     for( lem::Container::size_type p=0; p<words2.size(); ++p )
                      {
                       Tree_Node *word_node = new Tree_Node( new Solarix::Word_Form( Solarix::Lexem(words2[p].c_str()) ), true );
                       node_words_dim.Add( word_node );
                      }


                     // в трассировку запишем сведения о выполненной замене
                     if( atracing.NotNull() )
                      {
                       TrTuple *org_phrase = new TrTuple();


                       for( int j=0; j<l; ++j )
                        {
                         //Solarix::Tree_Node * org_node = new Solarix::Tree_Node( * var.roots_list()[iroot+j]->front() );
                         //TrValue *v = new TrValue( org_node, true );

                         const UCString &w = cols[j]->get( INDEX[j] );
                         TrValue *v = new TrValue(w);

                         org_phrase->Add(v); 
                        }


                       TrTuple *new_phrase = new TrTuple();
                       for( lem::Container::size_type p=0; p<words2.size(); ++p )
                        {
                         TrValue *v = new TrValue( lem::UCString(words2[p].c_str()) );
                         new_phrase->Add(v);
                        } 
                   
                       TrTuple * trace_point = new TrTuple();
                       trace_point->Add( new TrValue(org_phrase,true) );
                       trace_point->Add( new TrValue(new_phrase,true) );
                       trace_point->Add( new TrIntValue(iroot) );
                   
                       TrTuple & tr = atracing->GetTuple();
                       tr.Add( new TrValue(trace_point,true) );
                      }

                    }
                   else
                    {
                     SG_Phrase rtext;
                     sg.GetStorage().GetPhrase( te_id_right, rtext );
                     const int id_rlang = rtext.GetLanguage();
 
                     Sentence rsent;
                     rsent.Parse( rtext.GetText(), false, const_cast<Dictionary*>(&dict), id_rlang, trace_log );

                     for( lem::Container::size_type j=0; j<rsent.size(); ++j )
                      {
                       Tree_Node *word_node = new Tree_Node( new Solarix::Word_Form( rsent.GetWord(j) ), true );
                       node_words_dim.Add( word_node );
                      }

                     // в трассировку запишем сведения о выполненной замене
                     if( atracing.NotNull() )
                      {
                       TrTuple *org_phrase = new TrTuple();


                       for( int j=0; j<l; ++j )
                        {
//                         Solarix::Tree_Node * org_node = new Solarix::Tree_Node( * var.roots_list()[iroot+j]->front() );
//                         TrValue *v = new TrValue( org_node, true );
                         const UCString &w = cols[j]->get( INDEX[j] );
                         TrValue *v = new TrValue(w);
                         org_phrase->Add(v); 
                        }

                   
                       TrTuple *new_phrase = new TrTuple();
                   
                       for( lem::Container::size_type j=0; j<rsent.size(); ++j )
                        {
                         TrValue *v = new TrValue( rsent.GetWord(j) );
                         new_phrase->Add(v);
                        } 
                   
                       TrTuple * trace_point = new TrTuple();
                       trace_point->Add( new TrValue(org_phrase,true) );
                       trace_point->Add( new TrValue(new_phrase,true) );
                       trace_point->Add( new TrIntValue(iroot) );

                       TrTuple & tr = atracing->GetTuple();
                       tr.Add( new TrValue(trace_point,true) );
                      }
                    }

                   TrTuple *rect = new TrTuple;
                   rect->Add( TrIntValue( iroot ) );
                   rect->Add( TrValue( L"as_adverb" ) );

                   TrValue *rec = new TrValue( rect, true );
                   ret_tuple->Add(rec);

                   // в обрабатываемом вариаторе удаляем старые узлы
                   for( int j=0; j<l; ++j )
                    {
                     var.RemoveRoot(iroot);
                    }

                   // и вставляем узел с подставленными словами
                   var.Insert( iroot, node_as_adverb );

//                   var.InitHash();

                   #if LEM_DEBUGGING==1
//                   var.Print( *mout, sg, false );
                   #endif 

                   found_subst = true;
                   found_acceptable_link = true;
                  }
                 else if( substitute_as_graf )
                  {
                   int hexlen = hexdata.GetData().length()/2;
                   lem::uint8_t *data = new lem::uint8_t[hexlen];
                   for( int j=0; j<hexlen; ++j )
                    {
                     wchar_t chi4 = hexdata.GetData()[j*2];
                     wchar_t clo4 = hexdata.GetData()[j*2+1];

                     const int hi4 = uchar_to_digit(chi4);
                     const int lo4 = uchar_to_digit(clo4);

                     lem::uint8_t byte = ((hi4<<4) & 0xf0) | (0x0f & lo4 );
                     data[j] = byte;
                    } 

                   lem::MemReadStream rdr( data, hexlen );

                   // Граф сохранен как вариатор.
                   Solarix::Variator right_var;
                   right_var.LoadBin(rdr);
                   LEM_CHECKIT_Z( right_var.size()!=-1 );

                   #if LEM_DEBUGGING==1
                   //right_var.Print( *mout, sg, false );
                   #endif


                   if( atracing.NotNull() )
                    {
                     TrTuple *org_phrase = new TrTuple();

                     for( int j=0; j<l; ++j )
                      {
//                       Solarix::Tree_Node * org_node = new Solarix::Tree_Node( * var.roots_list()[iroot+j]->front() );
//                       TrValue *v = new TrValue( org_node, true );
                       const UCString &w = cols[j]->get( INDEX[j] );
                       TrValue *v = new TrValue(w);
                       org_phrase->Add(v); 
                      }


                     SG_Phrase rtext;
                     sg.GetStorage().GetPhrase( te_id_right, rtext );
                     const int id_rlang = rtext.GetLanguage();
 
                     Sentence rsent;
                     rsent.Parse( rtext.GetText(), false, &dict, id_rlang, trace_log );

                     TrTuple *new_phrase = new TrTuple();

                     for( lem::Container::size_type j=0; j<rsent.size(); ++j )
                      {
                       TrValue *v = new TrValue( rsent.GetWord(j) );
                       new_phrase->Add(v);
                      } 

                     TrTuple * trace_point = new TrTuple();
                     trace_point->Add( new TrValue(org_phrase,true) );
                     trace_point->Add( new TrValue(new_phrase,true) );
                     trace_point->Add( new TrIntValue(iroot) );

                     TrTuple & tr = atracing->GetTuple();
                     tr.Add( new TrValue(trace_point,true) );
                    }

                   delete[] data; data=NULL;
 
                   // В рабочем вариаторе удаляем узлы от iroot до iroot+l-1 включительно,
                   // и вставляем с позиции iroot узлы из right_var. 
                   // Первый и последний узлы left_var не нужны.

                   for( int j=0; j<l; ++j )
                    {
                     var.RemoveRoot(iroot);
                    }

                   int ir=iroot;
                   #if LEM_DEBUGGING==1
                   int nrv = right_var.size();
                   #endif    
                   for( int j=1; j<right_var.size()-1; ++j, iroot++ )
                    {
                     Tree_Node *n = new Tree_Node( right_var.get(j) );
                     var.Insert( iroot, n );

                     // в возвращаемый процедурой результат надо добавить информацию
                     // о положении сделанной замены
                     if( pivot_wordform.get()==NULL )
                      {
                       ret_tuple->Add( TrIntValue( iroot ) );
                      }
                     else
                      {
                       // Кроме индекса вставки также добавим копию ведущего слова замененного паттерна.
                       TrTuple *rect = new TrTuple;
                       rect->Add( TrIntValue( iroot ) );
                       rect->Add( TrValue( L"as_graf" ) );
                       rect->Add( TrValue( pivot_wordform.release(), true ) );
                       TrValue *rec = new TrValue( rect, true );
                       ret_tuple->Add(rec); 
                      }
                    }
   
//                   var.InitHash();

                   #if LEM_DEBUGGING==1
                   //var.Print( *mout, sg, false );
                   #endif 

                   found_subst = true;
                   found_acceptable_link = true;
                  }
                 else
                  {
/*
                   // правую часть надо разобрать на лексемы и подставить их в вариатор
                   // Сначала определим язык фразы.
                   SG_Phrase frz;
                   sg.GetStorage().GetPhrase( te_id_right, frz );
                   const lem::UFString & te_text = frz.GetText();
                   const int id_lang = dict.GetLexAuto().GuessLanguage(te_text);
                   Sentence sent;
                   sent.Parse(te_text,false,&dict,id_lang, trace_log==NULL ? NULL : trace_log->PreprocessorTrace());

                   lem::Ptr<Solarix::Text_Processor> tpu;
                   tpu = new Solarix::Text_Processor( &dict );
                   tpu->PerformSyntacticAnalysis(true);

                   SyntaxAnalyzerTimeout timeout;
                   lem::Ptr<Solarix::PhrasoBlock> fblo = tpu->process_morphology(sent,false,false,timeout);

                   if( fblo.NotNull() )
                    {
                     const Res_Pack &pack = fblo->GetPack();
                     fblo->GetPackPtr()->Save_Shortest_Vars();

                     const int ivar = pack.GetShortestVar();
                     if( ivar!=UNKNOWN )
                      {
                       const Variator &right_var = *pack.vars()[ivar];
      
                       if( atracing.NotNull() )
                        {
                         TrTuple *org_phrase = new TrTuple();


                         for( int j=0; j<l; ++j )
                          {
//                           Tree_Node * org_node = new Tree_Node( * var.roots_list()[iroot+j]->front() );
//                           TrValue *v = new TrValue( org_node, true );
                           const UCString &w = cols[j]->get( INDEX[j] );
                           TrValue *v = new TrValue(w);
                           org_phrase->Add(v); 
                          }

                         TrTuple *new_phrase = new TrTuple();

                         for( int j=0; j<right_var.size(); ++j )
                          {
                           Tree_Node * new_node = new Tree_Node( * right_var.roots_list()[j] );
                           TrValue *v = new TrValue( new_node, true );
                           new_phrase->Add(v); 
                          } 

                         TrTuple * trace_point = new TrTuple();
                         trace_point->Add( new TrValue(org_phrase,true) );
                         trace_point->Add( new TrValue(new_phrase,true) );
                         trace_point->Add( new TrIntValue(iroot) );

                         TrTuple & tr = atracing->GetTuple();
                         tr.Add( new TrValue(trace_point,true) );
                        }

                       for( int j=0; j<l; ++j )
                        var.RemoveRoot(iroot);

                       for( int j=1; j<right_var.size()-1; ++j, ++iroot )
                        {
                         // Сбросим морфологическую информацию из подставляемой словоформы.
                         Solarix::Word_Form *wf = new Solarix::Word_Form( * right_var.get(j).GetNode().GetName() );

                         Tree_Node *n = new Tree_Node( wf, true );
                         var.Insert( iroot, n );

                         // в возвращаемый процедурой результат надо добавить информацию
                         // о положении сделанной замены
                         ret_tuple->Add( TrIntValue( iroot ) );
                        }
   
                       #if LEM_DEBUGGING==1
                       //var.Print( *mout, sg, false );
                       #endif 
  
//                       var.InitHash();
                       found_subst = true;
                       found_acceptable_link = true;
                      }
                    }
*/
                  }
                }

               break;

              }
            }


           // готовим следующую перестановку
           for( int j=l-1; j>=0; --j )
            {
             int x = INDEX[j]+1;
             if( x==TOP[j] )
              {
               INDEX[j]=0;
               continue;  
              }
             else
              {
               INDEX[j] = x;
               break;
              }
            }
          } // for( int iperm=0; iperm<NTOT; ++iperm )
        } // for( int l=maxlen; l>=minlen && !found_subst; --l )

       if( !found_subst )
        iroot++;
      }
     else
      {
       // Слово не является началом фразы - продвигаемся на 1 корень вправо
       iroot++;
      }
    }  
  }
 #if !defined SOL_NO_NGRAMS
 else if( name.eq_begi( L"ngrams_" ) )
  {
   lem::Ptr<Ngrams> ngrams = pm.GetDict().GetNgrams();

   if( name.eqi( L"ngrams_status" ) )
    {
     lem::int64_t res=0;

     if( ngrams.NotNull() )
      {
       // Нужно вернуть признак наличия записей в базе N-грамм заданного порядка.
       // ngrams_status( порядок, нормализовать )
       const int order = args[0]->Run(constraints,pm,ctx,trace_log)->GetInt();
       const bool lemmatize = args[1]->Run(constraints,pm,ctx,trace_log)->GetBool();
       switch( order )
       {
        case 2: res = lemmatize ? ngrams->CountRaw2() : ngrams->CountLiteral2(); break;
        case 3: res = lemmatize ? ngrams->CountRaw3() : ngrams->CountLiteral3(); break;
        case 4: res = lemmatize ? ngrams->CountRaw4() : ngrams->CountLiteral4(); break;
        case 5: res = lemmatize ? ngrams->CountRaw5() : ngrams->CountLiteral5(); break;
       }
      }
     
     ret = new TrBoolValue(res>0);
    }
   else if( name.eqi( L"ngrams_find" ) )
    {
     // Поиск N-граммы
     // ngrams_find( слово1, слово2, ..., нормализовать )
     const int order = CastSizeToInt(args.size())-1;
     int ifreq=0;
     float wfreq=0;
     const bool lemmatize = args.back()->Run(constraints,pm,ctx,trace_log)->GetBool();

     UCString wi[5];

     for( int i=0; i<order; ++i )
      {
       lem::Ptr<TrValue> v = args[i]->Run(constraints,pm,ctx,trace_log);
       if( v->GetType().IsString() )
        wi[i] = v->GetString();
       else if( v->GetType().IsTree() )
        wi[i] = *v->GetTree().GetNode().GetName();
       else
        {
         lem::UFString msg = lem::format_str( L"Incorrect argument #%d - string or tree is required, %us found", i, v->GetType().GetName().c_str() );
         throw E_BaseException(msg);
        }
      }

     switch( order )
     {
      case 2:
       ngrams->FindNGrams( lemmatize, wi[0], wi[1], wfreq, ifreq );
       break; 

      case 3:
       ngrams->FindNGrams( lemmatize, wi[0], wi[1], wi[2], wfreq, ifreq );
       break; 

      case 4:
       ngrams->FindNGrams( lemmatize, wi[0], wi[1], wi[2], wi[3], wfreq, ifreq );
       break; 

      case 5:
       ngrams->FindNGrams( lemmatize, wi[0], wi[1], wi[2], wi[3], wi[4], wfreq, ifreq );
       break; 
     }

     ret = new TrIntValue(ifreq);
    }
   else if( name.eqi( L"ngrams_filter" ) )
    {
     // Фильтрация альтернативных переводов по базе N-грамм
     // ngrams_filter( вариатор, нач_порядок, кон_порядок, нормализовать )
     Variator &var = args[0]->Run(constraints,pm,ctx,trace_log)->GetTrees();
     const int order0 = args[1]->Run(constraints,pm,ctx,trace_log)->GetInt();
     const int order1 = args[2]->Run(constraints,pm,ctx,trace_log)->GetInt();
     const bool lemmatize = args[3]->Run(constraints,pm,ctx,trace_log)->GetBool();
     
     LEM_CHECKIT_Z( order0>=1 );
     LEM_CHECKIT_Z( order1>=order0 );

     MCollect<int> TOP;
     MCollect<int> INDEX;

     const int nroot = CastSizeToInt(var.roots_list().size());

     int total_hits=0;

     // Для каждой альтернативы в словоформах будем накапливать хиты N-грамм.
     lem::PtrCollect< lem::MCollect<int> > alt_hits;
     alt_hits.resize( nroot );

     lem::MCollect<int> NALT;
     NALT.resize(nroot);

     for( int q=0; q<nroot; ++q )
      {
       alt_hits[q] = new lem::MCollect<int>();

       const Tree_Node & tn = var.get(q);
       const Word_Form & wf = tn.GetNode();
       const int nalt = CastSizeToInt(wf.GetAlts().size())+1;

       NALT[q] = nalt;
       alt_hits[q]->resize( nalt );
       alt_hits[q]->Nullify();
      }

     for( int order=order0; order<=order1; ++order )
      {
       TOP.resize(order);
       INDEX.resize(order);

       for( int iroot=1; iroot<nroot-order; ++iroot )
        {
         INDEX.Nullify();

         for( int j=0; j<order; ++j )
          {
           const Tree_Node & tn = var.get(iroot+j);
           const Word_Form & wf = tn.GetNode();
           const int nalt = CastSizeToInt(wf.GetAlts().size())+1;
           TOP[j] = nalt-1;
          }

         // Перебираем все сочетания альтернатив и проверяем их по базе N-грамм.
         int pass=0;
         while(true)
         { 
          pass++;

          if( order==2 )
           {
            const Word_Form & wf0 = var.get(iroot).GetNode();
            const Word_Form & wf1 = var.get(iroot+1).GetNode();

            const UCString &w0 = INDEX[0]==0 ? *wf0.GetName() : *wf0.GetAlts()[INDEX[0]-1]->GetName();
            const UCString &w1 = INDEX[1]==0 ? *wf1.GetName() : *wf1.GetAlts()[INDEX[1]-1]->GetName();
 
            int ifreq=0;
            float afreq=0;
            
            ngrams->FindNGrams( lemmatize, w0, w1, afreq, ifreq );

            if( ifreq>0 )
             {
              // 2-грамма подходит.
              (*alt_hits[iroot] ) [ INDEX[0] ] ++;
              (*alt_hits[iroot+1] ) [ INDEX[1] ] ++;
             }
            else
             {
              // 2-грамма не подходит
              (*alt_hits[iroot] ) [ INDEX[0] ] --;
              (*alt_hits[iroot+1] ) [ INDEX[1] ] --;
              total_hits++;
             }
           }
          else if( order==3 )
           {
            const Word_Form & wf0 = var.get(iroot).GetNode();
            const Word_Form & wf1 = var.get(iroot+1).GetNode();
            const Word_Form & wf2 = var.get(iroot+2).GetNode();

            const UCString &w0 = INDEX[0]==0 ? *wf0.GetName() : *wf0.GetAlts()[INDEX[0]-1]->GetName();
            const UCString &w1 = INDEX[1]==0 ? *wf1.GetName() : *wf1.GetAlts()[INDEX[1]-1]->GetName();
            const UCString &w2 = INDEX[2]==0 ? *wf2.GetName() : *wf2.GetAlts()[INDEX[2]-1]->GetName();
 
            int ifreq=0;
            float afreq=0;
            
            ngrams->FindNGrams( lemmatize, w0, w1, w2, afreq, ifreq );

            if( ifreq>0 )
             {
              // 3-грамма подходит.
              (*alt_hits[iroot] )   [ INDEX[0] ] ++;
              (*alt_hits[iroot+1] ) [ INDEX[1] ] ++;
              (*alt_hits[iroot+2] ) [ INDEX[2] ] ++;
             }
            else
             {
              // 3-грамма не подходит
              (*alt_hits[iroot] )   [ INDEX[0] ] --;
              (*alt_hits[iroot+1] ) [ INDEX[1] ] --;
              (*alt_hits[iroot+2] ) [ INDEX[2] ] --;
              total_hits++;
             }
           }
          else if( order==4 )
           {
            const Word_Form & wf0 = var.get(iroot).GetNode();
            const Word_Form & wf1 = var.get(iroot+1).GetNode();
            const Word_Form & wf2 = var.get(iroot+2).GetNode();
            const Word_Form & wf3 = var.get(iroot+3).GetNode();

            const UCString &w0 = INDEX[0]==0 ? *wf0.GetName() : *wf0.GetAlts()[INDEX[0]-1]->GetName();
            const UCString &w1 = INDEX[1]==0 ? *wf1.GetName() : *wf1.GetAlts()[INDEX[1]-1]->GetName();
            const UCString &w2 = INDEX[2]==0 ? *wf2.GetName() : *wf2.GetAlts()[INDEX[2]-1]->GetName();
            const UCString &w3 = INDEX[3]==0 ? *wf3.GetName() : *wf3.GetAlts()[INDEX[3]-1]->GetName();
 
            int ifreq=0;
            float afreq=0;
            
            ngrams->FindNGrams( lemmatize, w0, w1, w2, w3, afreq, ifreq );

            if( ifreq>0 )
             {
              // 4-грамма подходит.
              (*alt_hits[iroot] )   [ INDEX[0] ] ++;
              (*alt_hits[iroot+1] ) [ INDEX[1] ] ++;
              (*alt_hits[iroot+2] ) [ INDEX[2] ] ++;
              (*alt_hits[iroot+3] ) [ INDEX[3] ] ++;
             }
            else
             {
              // 4-грамма не подходит
              (*alt_hits[iroot] )   [ INDEX[0] ] --;
              (*alt_hits[iroot+1] ) [ INDEX[1] ] --;
              (*alt_hits[iroot+2] ) [ INDEX[2] ] --;
              (*alt_hits[iroot+3] ) [ INDEX[3] ] --;
              total_hits++;
             }
           }
          else if( order==5 )
           {
            const Word_Form & wf0 = var.get(iroot).GetNode();
            const Word_Form & wf1 = var.get(iroot+1).GetNode();
            const Word_Form & wf2 = var.get(iroot+2).GetNode();
            const Word_Form & wf3 = var.get(iroot+3).GetNode();
            const Word_Form & wf4 = var.get(iroot+4).GetNode();

            const UCString &w0 = INDEX[0]==0 ? *wf0.GetName() : *wf0.GetAlts()[INDEX[0]-1]->GetName();
            const UCString &w1 = INDEX[1]==0 ? *wf1.GetName() : *wf1.GetAlts()[INDEX[1]-1]->GetName();
            const UCString &w2 = INDEX[2]==0 ? *wf2.GetName() : *wf2.GetAlts()[INDEX[2]-1]->GetName();
            const UCString &w3 = INDEX[3]==0 ? *wf3.GetName() : *wf3.GetAlts()[INDEX[3]-1]->GetName();
            const UCString &w4 = INDEX[4]==0 ? *wf4.GetName() : *wf4.GetAlts()[INDEX[4]-1]->GetName();
 
            int ifreq=0;
            float afreq=0;
            
            ngrams->FindNGrams( lemmatize, w0, w1, w2, w3, w4, afreq, ifreq );

            if( ifreq>0 )
             {
              // 5-грамма подходит.
              (*alt_hits[iroot] )   [ INDEX[0] ] ++;
              (*alt_hits[iroot+1] ) [ INDEX[1] ] ++;
              (*alt_hits[iroot+2] ) [ INDEX[2] ] ++;
              (*alt_hits[iroot+3] ) [ INDEX[3] ] ++;
              (*alt_hits[iroot+4] ) [ INDEX[4] ] ++;
             }
            else
             {
              // 5-грамма не подходит
              (*alt_hits[iroot] )   [ INDEX[0] ] --;
              (*alt_hits[iroot+1] ) [ INDEX[1] ] --;
              (*alt_hits[iroot+2] ) [ INDEX[2] ] --;
              (*alt_hits[iroot+3] ) [ INDEX[3] ] --;
              (*alt_hits[iroot+4] ) [ INDEX[4] ] --;
              total_hits++;
             }
           }


          int carry=1;
          for( int k=order-1; carry==1 && k>=0; --k )
           {
            INDEX[k] = INDEX[k]+1;
            if( INDEX[k]>TOP[k] )
             {
              INDEX[k]=0;  
              carry=1;
             }
            else
             {
              carry=0;
             }
           }   

          if( carry==1 )
           break;
         }
        } 
      }

     // Теперь в матрице - alt_hits число хитов для каждой альтернативы.

     for( int inode=1; inode<nroot-1; ++inode )
      {
       if( NALT[inode]>1 )
        {
         // Для узла есть альтернативные словоформы, переформируем их список так, чтобы
         // первой оказалась самая достоверная по кол-ву хитов. Самых достоверных может
         // оказаться несколько - это нормально.

         const Tree_Node & tn = var.get(inode);
         const Word_Form & wf = tn.GetNode();

#if LEM_DEBUGGING==1
//wf.Print( *lem::mout, &pm.GetDict().GetSynGram(), true );
#endif

         lem::MCollect< std::pair< const Word_Form *, int > > sorting;

         for( int j=0; j<NALT[inode]; ++j )
          {
           const Word_Form *wfa = j==0 ? &wf : wf.GetAlts()[j-1];
           const int nhit = (*alt_hits[inode])[j];
           sorting.push_back( std::make_pair( wfa, nhit ) );
          }

         std::sort( sorting.begin(), sorting.end(), wfa_sorter );

         #if LEM_DEBUGGING==1
         int h0 = sorting.front().second; 
         int h1 = sorting.back().second; 
         #endif    

         // В списке sorting сейчас отсортированные в порядке убывания альтернативы.
         // Создадим из них версионную словоформу.
         lem::MCollect< const Word_Form* > wfs;
         for( lem::Container::size_type k=0; k<sorting.size(); ++k )
          wfs.push_back( sorting[k].first );
 
         Word_Form recreated( wfs );

/*
#if LEM_DEBUGGING==1
int N1 = wf.GetAlts().size();
int N2 = wfs.size();
int N3 = recreated.GetAlts().size();
recreated.Print( *lem::mout, &pm.GetDict().GetSynGram(), true );
#endif
*/
         // Заменим корень в дереве
         var[inode]->GetNode() = recreated;
        }
      }

//     var.InitHash();
     ret = new TrIntValue(total_hits);
    }
   else
    {
     LEM_STOPIT;
    }
  }
 #endif
 else if( name.eq_begi( L"is_null" ) )
  {
   lem::Ptr<TrValue> v = args[0]->Run(constraints,pm,ctx,trace_log);
   
   if( v->IsNull() )
    ret = new TrBoolValue(true);
   else
    ret = new TrBoolValue(false);
  }
 else if( name.eq_begi( L"type_" ) )
  {
   if( name.eq_begi( L"type_is_" ) )
    {
     lem::Ptr<TrValue> v = args[0]->Run(constraints,pm,ctx,trace_log);

     int required=UNKNOWN;
     if( name.eqi(L"type_is_void") )
      required = TrType::Void;
     else if( name.eqi(L"type_is_int") )
      required = TrType::Int;
     else if( name.eqi(L"type_is_string") )
      required = TrType::String;
     else if( name.eqi(L"type_is_tree") )
      required = TrType::Tree;
     else if( name.eqi(L"type_is_trees") )
      required = TrType::Trees;
     else if( name.eqi(L"type_is_fun") )
      required = TrType::Trees;
     else if( name.eqi(L"type_is_tuple") )
      required = TrType::Tuple;
     else
      LEM_STOPIT;

     if( v->GetType().GetType()==required )
      ret = new TrBoolValue(true);
     else
      ret = new TrBoolValue(false);
    }
   else
    {
     LEM_STOPIT;
    }
  }
 else if( name.eqi( L"is_int" ) )
  {
   lem::Ptr<TrValue> v = args[0]->Run(constraints,pm,ctx,trace_log);
   if( v->GetType().IsString() )
    ret = new TrBoolValue( lem::is_int( v->GetString() ) );
   else if( v->GetType().IsTree() )
    ret = new TrBoolValue( lem::is_int( *v->GetTree().GetNode().GetName() ) );
   else if( v->GetType().IsInt() )
    ret = new TrBoolValue(true);
   else
    ret = new TrBoolValue(false);
  }
 else if( name.eq_begi( L"to_" ) )
  {
   if( name.eqi(L"to_void") )
    {
     // Вычисляет последовательно все аргумент(ы) и возвращает void.
     for( lem::Container::size_type i=0; i<args.size(); ++i )
      args[i]->Run(constraints,pm,ctx, trace_log);

     ret = new TrValue();
    }
   else if( name.eqi(L"to_int") )
    {
     lem::Ptr<TrValue> x = args[0]->Run( constraints,pm, ctx, trace_log);
     if( x->GetType().IsInt() )
      ret = x;
     else if( x->GetType().IsString() )
      ret = new TrIntValue( to_int( x->GetString() ) );
     else if( x->GetType().IsTree() )
      ret = new TrIntValue( lem::to_int( *x->GetTree().GetNode().GetName() ) ); 
     else
      {
       UFString msg = format_str(L"Invalid argument type for 'to_int' function: %s", x->GetType().GetName().c_str() );
       throw E_BaseException( msg );
      }
    }
   else if( name.eqi(L"to_string") )
    {
     lem::Ptr<TrValue> x = args[0]->Run( constraints,pm, ctx, trace_log);
     if( x->GetType().IsInt() )
      {
       ret = new TrValue( to_ustr(x->GetInt()) );
      }
     else if( x->GetType().IsString() )
      {
       ret = x;
      }
     else if( x->GetType().IsTree() )
      {
       ret = new TrValue( *x->GetTree().GetNode().GetName() ); 
      }
     else
      {
       UFString msg = format_str( L"Invalid argument type for 'to_string' function: '%s'", x->GetType().GetName().c_str() );
       throw E_BaseException( msg );
      }
    }
   else if( name.eqi( L"to_wordform" ) )
    {
     lem::Ptr<TrValue> s = args[0]->Run(constraints,pm,ctx,trace_log);
     if( s->GetType().IsString() )
      {
       const UCString &str = s->GetString();
       Word_Form *new_wf = new Word_Form( str );
       Tree_Node *tn = new Tree_Node(new_wf,true);
       ret = new TrValue( tn, true );
      }
     else if( s->GetType().IsTree() )
      {
       ret = s;
      }
     else
      {
       lem::UFString msg = format_str( L"Invalid argument for 'to_wordform' function: '%s'", s->GetType().GetName().c_str() );
       throw E_BaseException( msg );
      } 
    }
  }
 else if( name.eq_begi(L"ctx_") )
  {
   if( name.eqi( L"ctx_var" ) )
    {
     // Текущий вариатор для трансформанты
     ret = new TrValue( ctx.GetCurrentVariator(), false ); 
    }
   else if( name.eqi( L"ctx_root" ) )
    {
     // Корень в текущем вариаторе по относительному индексу.
     ret = new TrValue( ctx.GetCurrentVariator()->get( args[0]->Run(constraints,pm,ctx,trace_log)->GetInt()+ctx.GetCurrentPosition() ) ); 
    }
   else if( name.eqi( L"ctx_cursor" ) )
    {
     // Корень в текущем вариаторе по относительному индексу 0.
     ret = new TrIntValue( ctx.GetCurrentPosition() ); 
    }
  }
 else if( name.eq_begi(L"arith_") )
  {
   lem::Ptr<TrValue> x = args[0]->Run(constraints,pm,ctx,trace_log);
   lem::Ptr<TrValue> y = args[1]->Run(constraints,pm,ctx,trace_log);

   if( name.eqi( L"arith_minus" ) )
    {
     ret = new TrIntValue( x->GetInt()-y->GetInt() );
    }
   else if( name.eqi( L"arith_plus" ) )
    { 
     ret = new TrIntValue( x->GetInt()+y->GetInt() );
    }
   else if( name.eqi( L"arith_mul" ) )
    { 
     ret = new TrIntValue( x->GetInt()*y->GetInt() );
    }
   else if( name.eqi( L"arith_div" ) )
    { 
     ret = new TrIntValue( x->GetInt()/y->GetInt() );
    }
   else if( name.eqi( L"arith_mod" ) )
    { 
     ret = new TrIntValue( x->GetInt()%y->GetInt() );
    }
   else
    {
     LEM_STOPIT;
    }
  }
 else if( name.eq_begi(L"str_") )
  {
   if( name.eqi(L"str_icmp") )
    {
     lem::Ptr<TrValue> sa = args[0]->Run(constraints,pm,ctx,trace_log);
     lem::Ptr<TrValue> sb = args[1]->Run(constraints,pm,ctx,trace_log);

     const UCString &s1 = sa->GetType().IsString() ? sa->GetString() : *sa->GetTree().GetNode().GetName();
     const UCString &s2 = sb->GetType().IsString() ? sb->GetString() : *sb->GetTree().GetNode().GetName();

     ret = new TrBoolValue( s1.eqi( s1 ) );
    }
   else if( name.eqi( L"str_eq_beg" ) )
    {
     lem::Ptr<TrValue> sa = args[0]->Run(constraints,pm,ctx,trace_log);
     lem::Ptr<TrValue> sb = args[1]->Run(constraints,pm,ctx,trace_log);

     const UCString &s1 = sa->GetType().IsString() ? sa->GetString() : *sa->GetTree().GetNode().GetName();
     const UCString &s2 = sb->GetType().IsString() ? sb->GetString() : *sb->GetTree().GetNode().GetName();

     ret = new TrBoolValue( s1.eq_beg( s2 ) );
    }
   else if( name.eqi( L"str_eq_end" ) )
    {
     lem::Ptr<TrValue> sa = args[0]->Run(constraints,pm,ctx,trace_log);
     lem::Ptr<TrValue> sb = args[1]->Run(constraints,pm,ctx,trace_log);

     const UCString &s1 = sa->GetType().IsString() ? sa->GetString() : *sa->GetTree().GetNode().GetName();
     const UCString &s2 = sb->GetType().IsString() ? sb->GetString() : *sb->GetTree().GetNode().GetName();

     ret = new TrBoolValue( s1.eq_end( s2 ) );
    }
   else if( name.eqi( L"str_eq_begi" ) )
    {
     lem::Ptr<TrValue> sa = args[0]->Run(constraints,pm,ctx,trace_log);
     lem::Ptr<TrValue> sb = args[1]->Run(constraints,pm,ctx,trace_log);

     const UCString &s1 = sa->GetType().IsString() ? sa->GetString() : *sa->GetTree().GetNode().GetName();
     const UCString &s2 = sb->GetType().IsString() ? sb->GetString() : *sb->GetTree().GetNode().GetName();

     ret = new TrBoolValue( s1.eq_begi( s2 ) );
    }
   else if( name.eqi( L"str_eq_endi" ) )
    {
     lem::Ptr<TrValue> sa = args[0]->Run(constraints,pm,ctx,trace_log);
     lem::Ptr<TrValue> sb = args[1]->Run(constraints,pm,ctx,trace_log);

     const UCString &s1 = sa->GetType().IsString() ? sa->GetString() : *sa->GetTree().GetNode().GetName();
     const UCString &s2 = sb->GetType().IsString() ? sb->GetString() : *sb->GetTree().GetNode().GetName();

     ret = new TrBoolValue( s1.eq_endi( s2 ) );
    }
   else if( name.eqi( L"str_len" ) )
    {
     lem::Ptr<TrValue> sa = args[0]->Run(constraints,pm,ctx,trace_log);
     if( sa->GetType().IsString() )
      ret = new TrIntValue( sa->GetString().length() );
     else if( sa->GetType().IsTree() )
      ret = new TrIntValue( sa->GetTree().GetNode().GetName()->length() );
     else
      {
       UFString msg = format_str( L"Function 'str_len' expects tree or string argument, got '%s'", sa->GetType().GetName().c_str() );
       throw E_BaseException(msg);
      }
    }
   else if( name.eqi( L"str_left" ) )
    {
     lem::Ptr<TrValue> sa = args[0]->Run(constraints,pm,ctx,trace_log);
     lem::Ptr<TrValue> n = args[1]->Run(constraints,pm,ctx,trace_log);
     const UCString &s1 = sa->GetType().IsString() ? sa->GetString() : *sa->GetTree().GetNode().GetName();
     ret = new TrValue( lem::left( s1, n->GetInt() ) );
    }
   else if( name.eqi( L"str_right" ) )
    {
     lem::Ptr<TrValue> sa = args[0]->Run(constraints,pm,ctx,trace_log);
     lem::Ptr<TrValue> n = args[1]->Run(constraints,pm,ctx,trace_log);
     const UCString &s1 = sa->GetType().IsString() ? sa->GetString() : *sa->GetTree().GetNode().GetName();
     ret = new TrValue( lem::right( s1, n->GetInt() ) );
    }
   else if( name.eqi( L"str_mid" ) )
    {
     lem::Ptr<TrValue> sa = args[0]->Run(constraints,pm,ctx,trace_log);
     lem::Ptr<TrValue> from = args[1]->Run(constraints,pm,ctx,trace_log);
     lem::Ptr<TrValue> n = args[2]->Run(constraints,pm,ctx,trace_log);
     const UCString &s1 = sa->GetType().IsString() ? sa->GetString() : *sa->GetTree().GetNode().GetName();
     ret = new TrValue( lem::mid( s1, from->GetInt(), n->GetInt() ) );
    }
   else if( name.eqi( L"str_index_of" ) )
    {
     lem::Ptr<TrValue> sa = args[0]->Run(constraints,pm,ctx,trace_log);
     lem::Ptr<TrValue> sb = args[1]->Run(constraints,pm,ctx,trace_log);
     const UCString &s1 = sa->GetType().IsString() ? sa->GetString() : *sa->GetTree().GetNode().GetName();
     const int pos = s1.search( sb->GetString() );
     ret = new TrIntValue(pos);
    }
   else if( name.eqi( L"str_rindex_of" ) )
    {
     // todo
     LEM_STOPIT;
    }
   else if( name.eqi( L"str_regex" ) )
    {
     lem::Ptr<TrValue> sa = args[0]->Run(constraints,pm,ctx,trace_log);
     lem::Ptr<TrValue> sb = args[1]->Run(constraints,pm,ctx,trace_log);

     const UCString &s1 = sa->GetType().IsString() ? sa->GetString() : *sa->GetTree().GetNode().GetName();

     boost::wregex mask_rx( sb->GetString().c_str(), boost::regex_constants::icase );
     const bool r = boost::regex_match( s1.c_str(), mask_rx );
    
     ret = new TrBoolValue(r);
    }
   else if( name.eqi( L"str_charset" ) )
    {
     lem::Ptr<TrValue> str = args[0]->Run(constraints,pm,ctx,trace_log);
     lem::Ptr<TrValue> range_begin = args[1]->Run(constraints,pm,ctx,trace_log);
     lem::Ptr<TrValue> range_end = args[2]->Run(constraints,pm,ctx,trace_log);

     const UCString &s1 = str->GetType().IsString() ? str->GetString() : *str->GetTree().GetNode().GetName();

     const int irange_begin = range_begin->GetInt();
     const int irange_end = range_end->GetInt();
    
     bool r=true;
     for( int k=0; k<s1.length(); ++k )
      {
       const wchar_t c = s1[k];
       if( c<irange_begin || c>irange_end )
        {
         r = false;
         break;
        }
      }

     ret = new TrBoolValue(r);
    }
   else if( name.eqi( L"str_cat" ) )
    {
     UCString res_str;

     for( lem::Container::size_type i=0; i<args.size(); ++i )
      {
       lem::Ptr<TrValue> sa = args[i]->Run(constraints,pm,ctx,trace_log);
       const UCString &s1 = sa->GetType().IsString() ? sa->GetString() : *sa->GetTree().GetNode().GetName();
       res_str += s1;
      }

     ret = new TrValue( res_str );
    }
  }
 else if( name.eq_begi( L"tuple_" ) )
  {
   if( name.eqi( L"tuple_create" ) )
    {
     // Создание кортежа из элементов:
     // tuple_create( элемент1, элемент2, ... )

     TrTuple *tu = new TrTuple;

     for( lem::Container::size_type i=0; i<args.size(); ++i )
      {
       lem::Ptr<TrValue> v = args[i]->Run( constraints,pm, ctx, trace_log );
       tu->values.push_back( new TrValue(*v) );
      }

     ret = new TrValue( tu, true );
    }
   else if( name.eqi( L"tuple_clear" ) )
    {
     // очищаем кортеж.
     lem::Ptr<TrValue> a0 = args[0]->Run( constraints,pm, ctx, trace_log );
     TrTuple &tu = a0->GetTuple();
     tu.Clear();
     ret = a0;
    }
   else if( name.eqi( L"tuple_get" ) )
    {
     // Получение значения элемента кортежа
     // tuple_get( кортеж, индекс )

     lem::Ptr<TrValue> a0 = args[0]->Run( constraints,pm, ctx, trace_log );
     const TrTuple &tu = a0->GetTuple();

     lem::Ptr<TrValue> a1 = args[1]->Run( constraints,pm, ctx, trace_log );
     const int index = a1->GetInt();

     const TrValue &v = *tu.values[index];
     ret = new TrValue(v);
    }
   else if( name.eqi( L"tuple_set" ) )
    {
     // Изменение элемента
     // tuple_set( кортеж, индекс, элемент )

     lem::Ptr<TrValue> a0 = args[0]->Run(constraints, pm, ctx, trace_log );
     TrTuple &tu = a0->GetTuple();

     lem::Ptr<TrValue> a1 = args[1]->Run( constraints,pm, ctx, trace_log );
     const int index = a1->GetInt();

     lem::Ptr<TrValue> a2 = args[2]->Run( constraints,pm, ctx, trace_log );

     tu.Set( index, *a2 ); 

     ret = a0;
    }
   else if( name.eqi( L"tuple_count" ) )
    {
     // Количество элементов кортежа
     // tuple_count( кортеж )

     lem::Ptr<TrValue> a0 = args[0]->Run( constraints,pm, ctx, trace_log );
     TrTuple &tu = a0->GetTuple();

     ret = new TrIntValue( CastSizeToInt(tu.values.size()) );
    }
   else if( name.eqi( L"tuple_add" ) )
    {
     // Добавление элементов в хвост кортежа
     // tuple_add( кортеж, элемент [, элемент ... ] )

     lem::Ptr<TrValue> a0 = args[0]->Run( constraints,pm, ctx, trace_log );
     TrTuple &tu = a0->GetTuple();

     for( lem::Container::size_type i=1; i<args.size(); ++i )
      {
       lem::Ptr<TrValue> v = args[i]->Run( constraints,pm, ctx, trace_log );
       tu.Add( *v );
      }

     ret = a0;
    }
   else if( name.eqi( L"tuple_concat" ) )
    {
     // Добавление элементов второго (и далее) кортежа в хвост первого
     // tuple_concat( кортеж1, кортеж2, ... )

     lem::Ptr<TrValue> a0 = args[0]->Run( constraints,pm, ctx, trace_log );
     TrTuple &tu = a0->GetTuple();

     for( lem::Container::size_type i=1; i<args.size(); ++i )
      {
       lem::Ptr<TrValue> v = args[i]->Run( constraints,pm, ctx, trace_log );
       if( v->GetType().IsTuple() )
        {
         TrTuple &tu2 = v->GetTuple();
         for( int q=0; q<tu2.Count(); ++q )
          tu.Add( tu2[q] ); 
        }
       else if( v->GetType().IsVoid() )
        {
        }
       else
        {
         tu.Add( *v );
        }
      }

     ret = a0;
    }
   else if( name.eqi( L"tuple_remove" ) )
    {
     // Удаление элемента из кортежа
     // tuple_remove( кортеж, индекс )

     lem::Ptr<TrValue> a0 = args[0]->Run( constraints,pm, ctx, trace_log );
     TrTuple &tu = a0->GetTuple();

     lem::Ptr<TrValue> a1 = args[1]->Run( constraints,pm, ctx, trace_log );
     const int index = a1->GetInt();

     tu.Remove(index);

     ret = a0;
    }
   else if( name.eqi( L"tuple_insert" ) )
    {
     // Вставка элемента в кортеж
     // tuple_insert( кортеж, индекс, элемент )

     lem::Ptr<TrValue> a0 = args[0]->Run( constraints,pm, ctx, trace_log );
     TrTuple &tu = a0->GetTuple();

     lem::Ptr<TrValue> a1 = args[1]->Run( constraints,pm, ctx, trace_log );
     const int index = a1->GetInt();

     lem::Ptr<TrValue> a2 = args[2]->Run( constraints,pm, ctx, trace_log );

     tu.Insert(index,*a2);

     ret = a0;
    }
   else if( name.eqi( L"tuple_find" ) )
    {
     // поиск элемента в кортеже
     // int tuple_find( кортеж, элемент )

     lem::Ptr<TrValue> a0 = args[0]->Run( constraints,pm, ctx, trace_log );
     const TrTuple &tu = a0->GetTuple();

     lem::Ptr<TrValue> a1 = args[1]->Run( constraints,pm, ctx, trace_log );

     int idx = -1;
     for( lem::Container::size_type k=0; k<tu.values.size(); ++k )
      if( tu.values[k]->eq( a1 ) )
       {
        idx = CastSizeToInt(k);
        break;
       }

     ret = new TrIntValue(idx);
    }
   else if( name.eqi( L"tuple_foreach" ) )
    {
     // Выполнение действия для каждого элемента кортежа
     // tuple_foreach( кортеж, функция )

     lem::Ptr<TrValue> a0 = args[0]->Run( constraints,pm, ctx, trace_log );
     TrTuple &tu = a0->GetTuple();

     if( !tu.values.empty() )
      {
       if( dynamic_cast<const TrFun_Lambda*>(args[1])!=NULL )
        {
         lem::Ptr<TrValue> visitor = args[1]->Run( constraints,pm, ctx, trace_log );

         // ... todo     
        }
       else
        {   
         for( lem::Container::size_type j=0; j<tu.values.size(); ++j )
          {
           lem::Ptr<TrValue> v( tu.values[j], null_deleter() );

           TrContextInvokation ctx2( &ctx );
           ctx2.AddVar( L"_", v );
           
           lem::Ptr<TrValue> dummy = args[1]->Run( constraints,pm, ctx2, trace_log );
          }
        }
      }

     ret = a0;
    }
   else
    {
     LEM_STOPIT;
    }
  }
 else if( name.eqi( L"copy" ) )
  {
   lem::Ptr<TrValue> a0 = args[0]->Run( constraints,pm, ctx, trace_log );

   TrValue *v = new TrTypeValue( a0->GetType() );
   v->Copy( *a0 );

   ret = v;
  }
 else if( name.eqi(L"raise") )
  {
   lem::Ptr<TrValue> a0 = args[0]->Run( constraints,pm, ctx, trace_log );
   const lem::UCString &str = a0->GetString();
   throw lem::E_BaseException( str.c_str() );
  }
 else
  {
   LEM_STOPIT;
  }

 if( trace_log!=NULL )
  trace_log->Leave( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 return ret;
}
#endif



#if defined SOL_SAVEBIN
void TrFun_BuiltIn::SaveBin( lem::Stream& bin ) const
{
 TrFunCall::SaveBin(bin);

 bin.write( &name, sizeof(name) );
 args.SaveBin(bin);
  
 return;
}
#endif


#if defined SOL_LOADBIN 
void TrFun_BuiltIn::LoadBin( lem::Stream& bin )
{
 TrFunCall::LoadBin(bin);
 bin.read( &name, sizeof(name) );
 args.LoadBin(bin);
 return;
}

void TrFun_BuiltIn::Link( const TrFunctions &funs )
{
 for( lem::Container::size_type i=0; i<args.size(); ++i )
  args[i]->Link(funs);

 return;
}
#endif


TrFunCall* TrFun_BuiltIn::clone(void) const
{
 return new TrFun_BuiltIn(*this);
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
void TrFun_BuiltIn::CompileDeclaration(
                                       PM_Automat &pm,
                                       lem::Iridium::Macro_Parser &txtfile,
                                       TrFunctions &functions,
                                       TrKnownVars &known_vars,
                                       const TrBuiltInFunSignature *signature  
                                      )
{
 lem::Iridium::BSourceState beg = txtfile.tellp();
 src_location = pm.GetDict().GetDebugSymbols().RegisterLocation( txtfile, beg );

 LEM_CHECKIT_Z( signature!=NULL );

 name = txtfile.read();

 txtfile.read_it( B_OROUNDPAREN );

 while( !txtfile.eof() )
  {
   if( txtfile.pick().GetToken()==B_CROUNDPAREN )
    break;

   if( !args.empty() )
    txtfile.read_it( B_COMMA );

   TrFunCall *expr = functions.CompileCall( pm, txtfile, known_vars );
   args.push_back(expr);
  }

 if( !signature->Check( CastSizeToInt(args.size()) ) )
  {
   lem::Iridium::Print_Error( beg, txtfile );
   pm.GetIO().merr().printf( "Invalid number of arguments in function call [%vfA%us%vn]", name.c_str() );
   throw E_ParserError(); 
  }

 txtfile.read_it( B_CROUNDPAREN );

 return;
}
#endif
