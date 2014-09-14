// -----------------------------------------------------------------------------
// File PM_ACTOR_LIST.H
//
// (c) Koziev Elijah
//
// Content:
// Класс PM_Actor_List - список акторов.
// -----------------------------------------------------------------------------
//
// CD->31.01.1999
// LC->23.06.2011
// --------------

#if !defined SOL_ACTORLIST__H
#define SOL_ACTORLIST__H
#pragma once

 //#include <vector>
 //#include <set>

 namespace Solarix
 {
  class PM_Actor;

  class PM_Actor_List : public lem::MCollect<PM_Actor*>
  {
   private:
    void Delete(void);
    void Init( const PM_Actor_List &x );

   public:
    PM_Actor_List(void);
    PM_Actor_List( const PM_Actor_List &x );
    
    virtual ~PM_Actor_List(void);

    void operator=( const PM_Actor_List &x );

    void LoadBin( lem::Stream &bin );

    #if defined SOL_LOADBIN
    void Link( const TrFunctions &funs );
    #endif

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream &bin ) const;
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void FindContextLens( int *min_context_len, int *max_context_len ) const;
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void Optimize( SynGram &sg );
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void Assemble_Entries_List( lem::BaseSet<int> &entries ) const;
    #endif
  };

 } // namespace 'Solarix'

#endif
