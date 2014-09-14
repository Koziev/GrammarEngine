
// Извлечённый из текста токен.
class LexerTextPos
{
 private:
  int32_t start_position; // индекс первого символа.
  int32_t token_length; // длина токена в широких символах.
  const Word_Form * wordform;
  int32_t negative_score; // начисленные штрафы за данную токенизацию.
  const LexerTextPos * previous;
  
  const LexerTextPos * next_chained; // если на шаге выделен не 1 токен, а сразу цепочка
                                     // последовательных, то эта цепочка записана через поля
                                     // next_chained.
 
 public:
  LexerTextPos(
               const LexerTextPos * _previous,
               const LexerTextPos * _next_chained,
               const Word_Form * _wordform,
               int _negative_score,
               lem::int32_t _start,
               lem::int32_t _length
              )
   : start_position(_start), token_length(_length), wordform(_wordform),
     negative_score(_negative_score), previous(_previous), next_chained(_next_chained)
  {
   LEM_CHECKIT_Z( wordform!=NULL );
   LEM_CHECKIT_Z( start_position>=0 );
   LEM_CHECKIT_Z( token_length>0 );
   LEM_CHECKIT_Z( negative_score<=0 );
  }

  const LexerTextPos * GetNextChained() const { return next_chained; }
  
  // Возвращает указатель на текст справа от токена.
  const wchar_t* NextText( const wchar_t *text ) const
  {
   if( next_chained!=NULL )
    return text + next_chained->start_position;
   else
    return text + start_position + token_length;
  }
  
  lem::int32_t GetNextCharPos() const
  {
   if( next_chained!=NULL )
    return next_chained->start_position;
   else
    return start_position+token_length;
  }
  
  const LexerTextPos& GetPrev() const { return *previous; }
  
  lem::int32_t CalcTotalScore() const
  { return negative_score + previous==NULL ? 0 : previous->CalcTotalScore(); }
}



struct TextTokenizationRules : lem::NonCopyable
{
 lem::MCollect<wchar_t> spaces; // пробельные символы.
 lem::MCollect<wchar_t> delimeters; // символы-разделители.
 
 
};



class WrittenTextLexer : public BasicLexer
{
 private:
  Solarix::Dictionary * dict;
  lem::MCollect<int> language_ids; // языки, из которых используются правила токенизации.
  const TextTokenizationRules * rules; // все необходимые правила токенизации для заданного набора языков.
  
  const wchar_t * text; // разбираемый текст.
  lem::PtrCollect<Word_Form> wordforms; // все сгенерированные словоформы для всех путей.
  lem::PtrCollect<LexerTextPos> positions; // все позиции, по которым прошел поток распознавания
  
  // чтобы не повторять распознавание слов, будем хранить результаты распознавания.
  // Слова в исходном регистре.
  std::map< lem::UCString, const Word_Form* > recognitions;

  // Распознаёт слово, возвращается версионная словоформа. Может вернуть
  // ссылку на занесенные в кэш результаты.
  private const Word_Form * Recognize( const lem::UCString & word )
  {
   std::map<lem::UCString,Word_Form*>::iterator it = recognitions.find(word);
   if( it==recognitions.end() )
    {
     // Слово еще не разбиралось, выполняем морфологический анализ.
     const Word_Form * new_recognition = ...
     recognitions.insert( std::make_pair( word, new_recognition ) );
     return new_recognition;
    }
   else
    return it->second;
  }
  
  private void Extract(
                       const wchar_t * current_text,
                       lem::int32_t current_idx,
                       LexerTextPos *previous_pos,
                       lem::MCollect<LexerTextPos*> & tokens
                      )
  {
   next.clear();

   if( 0 != *current_text )
    {
     // справа есть текст, попробуем извлечь из него токены.

     // Пропускаем пробелы. Считаем, что тут все детерминировано - альтернативных
     // вариантов нет, то есть во всех языках символы являются или не являются
     // пробельными согласованно.
     current_text = rules->SkipSpace( current_text );
     
     // ... ищем все варианты токенизации, для которых в словаре есть лексемы, то есть
     // включая многолексемные слова с внутренними пробелами и др. разделителями.
     // Учитываем правила токенизации.
     while( ... )
     {
      lem::int32_t token_len = ...
      
      lem::UCString token = ...      
      
      const Word_Form * new_wordform = Recognize( token );
     
      LexerTextPos * new_token = new LexerTextPos(
                                                  previous_pos,
                                                  new_wordform,
                                                  current_idx,
                                                  token_len
                                                 );
                                                 
      // Если есть предыдущие токены, то проверим возможность
      // сочетания токенов.
      if( previous_pos!=NULL )
       {
        // ...
        
        // если путь невозможен, то удаляем new_token и ставим переменную в NULL.
       }

      if( new_token!=NULL )
       {
        positions.push_back( new_token );      
        tokens.push_back(new_token);
       }
     }
     
     // Тут можно отсортировать варианты в порядке убывания длины. Таким образом,
     // сначала будут идти самые длинные токены, как наиболее вероятные.
    }

   return;
  }
 
 public:
  WrittenTextLexer(
                   const wchar_t *Text,
                   const lem::MCollect<int> & _language_ids,
                   Solarix::Dictionary * _dict
                  )
   : dict(_dict), language_ids(_language_ids), text(Text)
  {
   LEM_CHECKIT_Z( text!=NULL );

   rules = dict->GetTokenizationRules( language_id );
  }
  
  // Начинаем токенизацию текста - извлекаем первые токены, с которых начинаются
  // альтернативные пути.
  virtual void Start( lem::MCollect<const LexerTextPos*> & tokens )
  {
   Extract( text, 0, NULL, tokens );
   return;
  }
  
  // От токена current продолжаем токенизацию. Возможно, появятся альтернативные пути,
  // каждый из которых будет представлен своим объектом в списке next.
  // Возвращает true, если токенизация продолжена; false если дальше вправо нет слов.
  virtual bool Next( const LexerTextPos * current, lem::MCollect<const LexerTextPos*> & next )
  {
   if( current->GetNextChained()!=NULL )
    {
     next.push_back( current->GetNextChained() );
     return true;
    }
   else
    {
     const wchar_t * text2 = current->NextText( text );
     lem::int32_t pos = current->GetNextCharPos();
     ExtractTokens( text2, pos, current, next );
     return !next.empty();
    }
  }
};
