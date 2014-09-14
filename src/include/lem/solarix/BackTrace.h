#if !defined BackTrace_H
#define BackTrace_H
#pragma once

 #include <lem/noncopyable.h>
 #include <lem/ptr_container.h>
 #include <lem/solarix/BackTraceItem.h>

 namespace Solarix
 {
 
  typedef int BackTraceTx;

  // “рассировка хода сопоставлени€ точек со словоформами, дл€
  // работы механизма согласовани€.

  class BackTrace : lem::NonCopyable
  {
   private:
    const BackTrace *parent;
    lem::PtrCollect< lem::MCollect<int> > seq_number;
    lem::MCollect<lem::UCString> name;
    lem::PtrCollect<BackTraceItem> trace;

   public:
    BackTrace(void) : parent(NULL) {}
    BackTrace( const BackTrace *_parent );

    void Add( const BackTrace &src );

    void CollectAll( BackTrace *result ) const;

    bool Empty(void) const;

    BackTraceTx BeginTx(void) const { return CastSizeToInt(trace.size()); }
    void CommitTx( const BackTraceTx &tx  ) {}
    void RollbackTx( const BackTraceTx &tx );
    void Clear(void);

    BackTraceItem& Add( const lem::MCollect<int> & PatternSequenceNumber, const lem::UCString &wf_name, const Solarix::Word_Form *wf );
    BackTraceItem& Add( const lem::MCollect<int> & PatternSequenceNumber, const lem::UCString &wf_name, const CP_Array & export_coords );
    BackTraceItem& Add( const lem::MCollect<int> & PatternSequenceNumber, const lem::UCString &wf_name, const Solarix::Word_Form *wf, const CP_Array & export_coords );

    bool Contains( const lem::MCollect<int> & PatternSequenceNumber, const lem::UCString &name ) const;
    const BackTraceItem* Get( const lem::MCollect<int> & PatternSequenceNumber, const lem::UCString &name, bool thow_if_missing=true ) const;

    void Print( lem::OFormatter &to, SynGram &sg, bool detailed ) const;
    void PrintExportedNodes( lem::OFormatter &to, SynGram &sg, bool detailed ) const;
  };

 }
#endif
