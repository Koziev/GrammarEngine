#if !defined BasicLexer__H
 #define BasicLexer__H

#include <set>
#include <lem/containers.h>
#include <lem/ptr_container.h>
#include <lem/solarix/TextRecognitionParameters.h>

namespace Solarix {

class Dictionary;
class TrTrace;
class LexerTextPos;
class Word_Form;


class TokenExpectation
{
 public:
  TokenExpectation() {}
  virtual ~TokenExpectation() {}
};


// ATT: ����� �����������������, ��������� �� ������ ������ � 1 �������!!!
class BasicLexer
{
 protected:
  const LexerTextPos *begin_token;

 protected:
  Solarix::Dictionary * dict;
  TrTrace * trace;
  TextRecognitionParameters params; // ����������� ���������

  int path_count; // ��� �������� �� ���������� ����� - ������� ����� ��������� ����� �����������
  void AddBranching( int new_branching );
  bool IsTooManyTokens( int new_branching ) const;
  void LimitBranching( lem::MCollect<const LexerTextPos*> & tokens ) const;

  lem::MCollect<Word_Form*> wordforms; // ��� ��������������� ���������� ��� ���� �����.
  lem::MCollect<LexerTextPos*> positions; // ��� �������, �� ������� ������ ����� �������������

  typedef std::multimap<const LexerTextPos*,LexerTextPos*> CACHED_EDGES;
  CACHED_EDGES edges; // ����������� ���� �����������.

  // �������� �������������� ������ � ���������� �����������. ��� �� ���, � ������ ������
  // ������������� �������� ��������� ������������ ��� ������ � ���� �� ���������� ������.
  typedef std::map<const LexerTextPos*,LexerTextPos*> CACHED_ENDS;
  CACHED_ENDS end_tokens;

  // ����� �� ��������� ������������� ����, ����� ������� ���������� �������������.
  // ����� � �������� ��������.
  bool use_recognition_cache; // ������������ ��� ������������� ����
  std::map< lem::UCString, const Word_Form* > recognitions;

  Word_Form *wf_end; // ����������� �������������� ���������� ��� ��������� ������.

  void SortTokensByScoreDesc( lem::MCollect<const LexerTextPos*> & tokens ) const;

  const LexerTextPos * GetEndToken( const LexerTextPos * last_token );
  const LexerTextPos * GetBeyondRigthToken( const LexerTextPos * previous );

 public:
  BasicLexer( Solarix::Dictionary * _dict, const TextRecognitionParameters & _params, TrTrace * _trace );

  virtual ~BasicLexer();

  virtual void ResetParams( const TextRecognitionParameters & _params );

  const TextRecognitionParameters& GetParams() const { return params; }
  TextRecognitionParameters& ChangeParams() { return params; }
  
  virtual const LexerTextPos * GetBeginToken();

  virtual bool Fetch(
                     const LexerTextPos * current,
                     const TokenExpectation * expectations,
                     lem::MCollect<const LexerTextPos*> & next
                    )=0;

  virtual bool Fetch( const LexerTextPos * current, lem::MCollect<const LexerTextPos*> & next );

  void FetchN( const LexerTextPos *current_token, int n, lem::MCollect<const LexerTextPos*> & final_tokens );

  void FetchEnds( const LexerTextPos * current, lem::MCollect<const LexerTextPos*> & right_ends, int max_right_leaves );

  #if defined SOL_DEBUGGING
  void PrintRecognitions( lem::OFormatter & to ) const;
  #endif

  TrTrace* GetTrace() { return trace; }

  void FilterRecognitions( const LexerTextPos * token, const std::set<int> & selected_recognitions, bool remove_incorrect_alts );
  void ReplaceTokenWordform( LexerTextPos * token, Word_Form * new_wordform );
};

}
#endif
