#if !defined BackTraceItem__H
#define BackTraceItem__H
#pragma once

 #include <map>
 #include <lem/zeroed.h>
 #include <lem/solarix/coord_pair.h>

 namespace lem
 {
  class OFormatter;
 }

 namespace Solarix
 {
  class Word_Form;
  class CP_Array;
  struct BackRefCorrel;
  class SynGram;
//  class Variator;
  class LexerTextPos;


  class BackTraceItem
  {
   private:
    const Solarix::Word_Form *wf;
    lem::zbool use_export;
    CP_Array export_coords;
    lem::MCollect< std::pair<const lem::UCString*,const Word_Form*> > export_nodes;

    const LexerTextPos * beg_token, * end_token; // начало и конец цепочки токенов, входящих в маркировку

    BackTraceItem();

   public:
    BackTraceItem( const BackTraceItem &x );

    BackTraceItem( const Solarix::Word_Form * _wordform );
    BackTraceItem( const CP_Array & _export );
    BackTraceItem( const Solarix::Word_Form * _wordform, const CP_Array & _export );

    void operator=( const BackTraceItem &x );

    void SetExportedNodes( const lem::MCollect< std::pair<const lem::UCString*,const Word_Form*> > & nodes );
    void SetRange( const LexerTextPos * _begin, const LexerTextPos * _end );
    void SetHeadWord( const Word_Form *head ) { wf=head; }
    
    bool Check( SynGram &sg, const BackRefCorrel & condition, const Solarix::Word_Form & wf ) const;
    bool Check( SynGram &sg, const BackRefCorrel & condition, const std::multimap<int,int> & coords ) const;

    void Print( lem::OFormatter &to, SynGram &sg, bool detailed ) const;

    int GetCoordState( int id_coord ) const;
    void GetCoorPairs( CP_Array &dst ) const;
    void GetCoordStates( int id_coord, lem::MCollect<int> & states ) const;

    const Solarix::Word_Form* GetWordform(void) const { return wf; }
    const Solarix::Word_Form* GetSingleRootNode() const;

    const Solarix::Word_Form* FindNode( const lem::UCString & name ) const;

    const LexerTextPos * GetBeginToken(void) const { return beg_token; }
    const LexerTextPos * GetEndToken(void) const { return end_token; }
    bool IsSingleWord(void) const { return end_token==beg_token; }
  };

 }
#endif
