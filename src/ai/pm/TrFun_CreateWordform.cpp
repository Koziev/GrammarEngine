// LC->02.02.2013

#include <lem/solarix/tokens.h>
#include <lem/solarix/pm_autom.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tr_funs.h>
#include <lem/solarix/tr_trace_actors.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/WordEntry.h>

using namespace lem;
using namespace Solarix;

TrFun_CreateWordform::TrFun_CreateWordform(void)
 : TrFunCall( TrFunCall::CreateWordform )
{
}


TrFun_CreateWordform::TrFun_CreateWordform( const TrFun_CreateWordform & x )
 : TrFunCall(x)
{
 ientry    = x.ientry;
 coords    = x.coords;
 states    = x.states;
 form_name = x.form_name;
 return;
}



void TrFun_CreateWordform::operator=( const TrFunCall & x )
{
 TrFunCall::operator =(x);

 ientry    = ((const TrFun_CreateWordform&)x).ientry;
 coords    = ((const TrFun_CreateWordform&)x).coords;
 states    = ((const TrFun_CreateWordform&)x).states;
 form_name = ((const TrFun_CreateWordform&)x).form_name;

 return;
}
   

#if defined SOL_CAA
lem::Ptr<TrValue> TrFun_CreateWordform::Run(
                                            const ElapsedTimeConstraint & constraints,
                                            PM_Automat &pm,
                                            TrFunContext &ctx,
                                            TrTrace *trace_log
                                           ) const
{
 const int mark = TrTraceActor::seq++;
 if( trace_log!=NULL )
  trace_log->Enter( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 SynGram &sg = pm.GetDict().GetSynGram();
 const int ekey = ientry->Run(constraints,pm,ctx,trace_log)->GetInt();
 const SG_Entry &e = sg.GetEntry( ekey );

 Word_Form *wf = new Word_Form( form_name.empty() ? e.GetName() : form_name, e.GetKey() );

 // Скопируем в словоформу атрибуты статьи
 for( lem::Container::size_type i=0; i<e.attrs().size(); ++i )
  {
   wf->SetState( e.attrs()[i] ); 
  }

 {
 // Теперь зададим измерения, которые определены внутри {...}
 for( lem::Container::size_type i=0; i<coords.size(); ++i )
  {
   const int icoord = coords[i]->Run(constraints,pm,ctx,trace_log)->GetInt();
   const int istate = states[i]->Run(constraints,pm,ctx,trace_log)->GetInt();

   wf->SetState( GramCoordPair( icoord, istate ) ); 
  }
 }

 if( form_name.empty() )
  {
   wf->Rename_By_States(sg);
  }

 Tree_Node *tn = new Tree_Node(wf,true);
 lem::Ptr<TrValue> ret( new TrValue(tn,true) ); 

 if( trace_log!=NULL )
  trace_log->Leave( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 return ret;
}
#endif


#if defined SOL_SAVEBIN
void TrFun_CreateWordform::SaveBin( lem::Stream& bin ) const
{
 TrFunCall::SaveBin(bin);

 ientry.SaveBin(bin);
 coords.SaveBin(bin);
 states.SaveBin(bin);
 bin.write( &form_name, sizeof(form_name) );

 return;
}
#endif


#if defined SOL_LOADBIN 
void TrFun_CreateWordform::LoadBin( lem::Stream& bin )
{
 TrFunCall::LoadBin(bin);
 ientry.LoadBin(bin);
 coords.LoadBin(bin);
 states.LoadBin(bin);
 bin.read( &form_name, sizeof(form_name) );

 return;
}

void TrFun_CreateWordform::Link( const TrFunctions &funs )
{
 ientry->Link(funs);

 for( lem::Container::size_type i=0; i<coords.size(); ++i )
  coords[i]->Link(funs);

 {
 for( lem::Container::size_type i=0; i<states.size(); ++i )
  states[i]->Link(funs);
 }

 return;
}
#endif

#if defined SOL_COMPILER
void TrFun_CreateWordform::RefreshArgumentNames( const TrFunctions &funs )
{
 ientry->RefreshArgumentNames(funs);

 for( lem::Container::size_type i=0; i<coords.size(); ++i )
  coords[i]->RefreshArgumentNames(funs);

 {
 for( lem::Container::size_type i=0; i<states.size(); ++i )
  states[i]->RefreshArgumentNames(funs);
 }
 return;
}
#endif



TrFunCall* TrFun_CreateWordform::clone(void) const
{
 return new TrFun_CreateWordform(*this);
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void TrFun_CreateWordform::CompileDeclaration(
                                              PM_Automat &pm,
                                              lem::Iridium::Macro_Parser &txtfile,
                                              TrFunctions &functions,
                                              const TrProcedureDeclaration &procs,
                                              TrKnownVars &known_vars,
                                              const TrBuiltInFunSignature *signature  
                                             )
{
 lem::Iridium::BSourceState ebeg = txtfile.tellp();

 SynGram &sg = pm.GetDict().GetSynGram();

 const lem::Iridium::BethToken &class_name = txtfile.read();
 const int iclass = sg.FindClass(class_name);

 txtfile.read_it( B_COLON );
 lem::Iridium::BSourceState ename = txtfile.tellp();

 UCString entry_name = sol_read_multyname( pm.GetIO(), txtfile, B_OFIGPAREN );
     
 const int v_ientry = sg.FindEntry( entry_name, iclass, false );
 if( v_ientry==UNKNOWN )
  {
   lem::Iridium::Print_Error( ename, txtfile );
   pm.GetIO().merr().printf( "Unknown entry [%vfE%us:%us%vn]\n", class_name.c_str(), entry_name.c_str() );
   throw E_ParserError();
  } 

 ientry = new TrFun_Constant( TrIntValue(sg.GetEntry(v_ientry).GetKey()) );

 while( !txtfile.eof() )
  {
   if( txtfile.pick().GetToken()==B_CFIGPAREN )
    {
     break;
    }

   // Координатная пара или имя формы слова в апострофах

   lem::Iridium::BethToken cn = txtfile.read();
   if( lem::in_quotes(cn.string()) )
    {
     form_name = strip_quotes(cn.string());
    }
   else
    {
     bool AFFIRM=true;

     if( cn.GetToken()==B_NEGATIVE )
      {
       // Оператор отрицания перед определением координаты!
       AFFIRM=false;
       cn = txtfile.read();
      }

     // Для бистабильных - просто имя координаты.
     int icoord=UNKNOWN, istate=UNKNOWN;

     icoord = sg.FindCoord(cn).GetIndex();
     if( icoord==UNKNOWN )
      {
       lem::Iridium::Print_Error( cn, txtfile );
       pm.GetIO().merr().printf( "Unknown coordinate [%vfE%us%vn]\n", cn.c_str() );
       throw E_ParserError();
      }

     if( sg.coords()[icoord].IsBistable() )
      {
       istate=AFFIRM ? 1 : 0;
      }
     else
      {
       txtfile.read_it( B_COLON );
       const lem::Iridium::BethToken & sn = txtfile.read();
       istate = sg.coords()[icoord].FindState(sn);

       if( istate==UNKNOWN )
        {
         // Нет такого состояния для этого измерения.
         lem::Iridium::Print_Error(sn,txtfile);
          sg.GetIO().merr().printf(
                                    "State [%vfE%us%vn] is not declared for coordinate [%vfE%us%vn]\n"
                                    , sn.c_str(), cn.c_str()
                                   );
         throw E_ParserError();
        }
      }

     TrIntValue v2( icoord );
     coords.push_back( new TrFun_Constant(v2) );
  
     TrIntValue v3( istate );
     states.push_back( new TrFun_Constant(v3) );
    }
  }

 txtfile.read_it( B_CFIGPAREN );

 return;
}
#endif

