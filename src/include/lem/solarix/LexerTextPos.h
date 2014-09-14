#if !defined LexerTextPos__H
 #define LexerTextPos__H

#include <lem/containers.h>

namespace Solarix {

class Word_Form;

// Извлечённый из текста токен.
class LexerTextPos
{
 private:
  int start_position; // индекс первого символа.
  int token_length; // длина токена в широких символах. Из-за действий препроцессора может отличаться от длины слова в wordform.

  const Word_Form * wordform;

  int score; // начисленные штрафы (-) или поощрения (+) за данную токенизацию.
  const LexerTextPos * previous;
  int WordIndex; // условный порядковый индекс слова - фактически это глубина в графе. начинается с 0.
  
  const LexerTextPos * next_chained; // если на шаге выделен не 1 токен, а сразу цепочка
                                     // последовательных, то эта цепочка записана через поля
                                     // next_chained.

 protected:
  lem::int16_t token_flags; // 0=обычный токен
                   // 1=финальный токен - правая граница предложения.
                   // 2=аварийное прерывание сегментации из-за невозможности выделить очередной токен
                   // 3=токен за правой границей
                   // 4=стартовый токен - левая граница
                   // 5=спецтокен левее начального

  lem::int16_t creat_flags; // доп. флагы для лексера - история создания токена

 public:
  LexerTextPos(
               const LexerTextPos * _previous,
               const Word_Form * _wordform,
               int _score,
               int _start,
               int _length,
               int _wordindex
              );

  void SetNextChained( const LexerTextPos * next ) { next_chained=next; }

  int GetWordIndex() const { return WordIndex; }

  const LexerTextPos * GetNextChained() const { return next_chained; }
  
  int GetNextCharPos() const
  {
   if( next_chained!=NULL )
    return next_chained->start_position;
   else
    return start_position+token_length;
  }
  
  const LexerTextPos* GetPrev() const { return previous; }

  int GetWordLength() const;

  const Word_Form * GetWordform() const { return wordform; }
  void ReplaceWordform( const Word_Form * new_wordform );

  void CollectPathToLeft( int count, lem::MCollect<const Word_Form*> & org ) const;

  // Токен - обычное слово.
  bool IsRealWord() const { return token_flags==0; }

  // Токен - правая граница
  bool IsEnd() const { return token_flags==1; }

  // Токен - левая граница
  bool IsBegin() const { return token_flags==4; }

  // Токен для ситуации аварийного прекращения дальнейшей сегментации для беспробельных языков
  bool IsTerminator() const { return token_flags==2; }

  // Токен для обозначения попадания за правую границу.
  bool IsBeyondRight() const { return token_flags==3; }

  void Reconstructed() { creat_flags |= 0x0001; }
  bool IsReconstructed() const { return (creat_flags&1)==1; }

  // От текущего токена двигаемся влево вплоть до токена left_boundary и собираем пройденные токены, включая текущий в inverted_path.
  void Collect_Right2Left( const LexerTextPos *left_boundary, lem::MCollect<const LexerTextPos*> & inverted_path ) const;

  // От текущего токена сдвигаемся влево максимум на count токенов и собираем токены, встречающиеся на этом пути, в inverted_path.
  void Collect_Right2Left( int count, lem::MCollect<const LexerTextPos*> & inverted_path ) const;

  int GetStartPosition() const { return start_position; }

  int GetScore() const { return score; }
};


class LexerTextPos_BeyondLeft : public LexerTextPos
{
 public:
  LexerTextPos_BeyondLeft( const Word_Form * wf );
};


class LexerTextPos_Begin : public LexerTextPos
{
 public:
  LexerTextPos_Begin( const LexerTextPos_BeyondLeft * left_margin, const Word_Form * wf );
};


class LexerTextPos_End : public LexerTextPos
{
 public:
  LexerTextPos_End( const LexerTextPos * previous, const Word_Form * wf );
};


class LexerTextPos_Terminator : public LexerTextPos
{
 public:
  LexerTextPos_Terminator();
};


class LexerTextPos_BeyondRight : public LexerTextPos
{
 public:
  LexerTextPos_BeyondRight( const LexerTextPos * previous, const Word_Form * wf );
};


}
#endif
