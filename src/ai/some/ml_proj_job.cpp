// -----------------------------------------------------------------------------
// File ML_PROJ_JOB.CPP
//
// (c) Koziev Elijah
//
// Content:
// Класс MLProjJob - хранение ссылки на задание на проекцию мультилексемы.
// Используется Фразоблоком для реализации постепенного анализа. Каждое задание
// на проекцию обрабатывается Лексическим Автоматом.
// -----------------------------------------------------------------------------
//
// CD->28.08.1997
// LC->19.08.2009
// --------------

#if defined SOL_CAA

#include <lem/oformatter.h>
#include <lem/solarix/tree_node.h>
#include <lem/solarix/ml_projections.h>

using namespace lem;
using namespace Solarix;

MLProjJob::MLProjJob(void)
{ ijob=pos=UNKNOWN; }

MLProjJob::MLProjJob( const MLProjJob &x )
 : val(x.val), ijob(x.ijob),  pos(x.pos), ml(x.ml), org_word(x.org_word)
{}

MLProjJob::MLProjJob(
                     int Pos,
                     const RC_Lexem &Ml,
                     Real1 Val,
                     int Ijob
                    ) : val(Val), ijob(Ijob), pos(Pos), ml(Ml)
{}

MLProjJob::MLProjJob(
                     int Pos,
                     const RC_Lexem &Ml,
                     const UCString &Org, 
                     Real1 Val,
                     int Ijob
                    ) : val(Val), ijob(Ijob), pos(Pos), ml(Ml), org_word(Org)
{}

// Этот конструктор вызывается, когда формируется задание на проекцию
// слова, описываемого через грамматические категории.
MLProjJob::MLProjJob( int Pos, int Ijob ) : val( Real1(100) )
{
 ijob = Ijob;
 pos  = Pos;
}

void MLProjJob::operator=( const MLProjJob &x )
{
 val   = x.val;
 ijob  = x.ijob;
 ml    = x.ml;
 org_word = x.org_word;
 pos   = x.pos;
 return;
}


void MLProjJob::Print( lem::OFormatter &to ) const
{
 to.printf( "Multylexem: [%us] ijob=%d\n", ml->c_str(), ijob );
 return;
}

void MLProjJob::PrintLexem( lem::OFormatter &to ) const
{
 to.printf( "%us", ml->c_str() );
 return;
}

#endif // defined SOL_CAA
