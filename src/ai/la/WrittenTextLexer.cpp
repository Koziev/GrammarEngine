#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/TextTokenizationRules.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/WordSplitResults.h>
#include <lem/solarix/GG_CharOperations.h>
#include <lem/solarix/GG_CharOperation.h>
#include <lem/WideStringUcs4.h>
#include <lem/solarix/casing_coder.h>
#include <lem/solarix/MorphFiltersInfo.h>
#include <lem/solarix/TF_ClassFilter.h>
#include <lem/solarix/MorphologyModels.h>

#if defined SOL_DEBUGGING
#include <lem/solarix/LA_PreprocessorTrace.h>
#endif

#include <lem/solarix/WrittenTextLexer.h>

using namespace Solarix;


WrittenTextLexer::WrittenTextLexer(
                                   const lem::UFString & _text,
                                   const TextRecognitionParameters & _params,
                                   Solarix::Dictionary * _dict,
                                   TrTrace * _trace
                                  ) : BasicLexer(_dict,_params,_trace), text(_text)
{
 rules = dict->GetTokenizationRules( params.language_ids );

 UNKNOWN_ENTRY_KEY = dict->GetLexAuto().GetUnknownEntryKey();

 // Подготовим информацию для фильтрации по регистру.

 use_charcase_filter = false;
 upper_xlat=NULL;
 casing_coder = & dict->GetLexAuto().GetCasingCoder();

 // Посмотрим, какие параметры учета регистра выставлены для языка
 if( params.GetLanguageID()!=UNKNOWN )
  {
   const SG_Language & lang = dict->GetSynGram().languages()[params.GetLanguageID()];
   const int icase_opt = lang.FindParam( L"UseCaseFilter" );
   if( icase_opt!=UNKNOWN )
    {
     const SG_LanguageParam & case_opt = lang.GetParam(icase_opt);
     if( case_opt.GetValue().eqi(L"true") )
      {
       // если вся строка в верхнем регистре, то применять фильтр нельзя.
       const int iupper_opt = lang.FindParam( L"UpperCase" );
       if( iupper_opt!=UNKNOWN )
        {
         const lem::UFString &xlat_name = lang.params[iupper_opt]->GetValue();
         upper_xlat = dict->GetGraphGram().GetCharOperations()[xlat_name.c_str()];

         lem::WideStringUcs4 org_phrase_scanner( text.c_str() );
         for(;;)
          {
           const lem::uint32_t src_ucs4 = org_phrase_scanner.Fetch();
           if(!src_ucs4)
            break;
 
           // смотрим только символы, которые включены в набор главного алфавита
           if( upper_xlat->IsSourceSymbol(src_ucs4) )
            {
             // это символ в нижнем регистре.
             use_charcase_filter=true;
             break;
            }
          }
        }
      }
    }
  }

 if( rules->IsExternalSegmentation() )
  {
   CallExternalTokenizer();
  }

 return;
}


void WrittenTextLexer::CallExternalTokenizer()
{
 // Вызываем внешний сегментатор, и на основе его результатов формируем цепочку токенов.

 lem::PtrCollect<UFString> classes;
 lem::MCollect<lem::UCString> tokens;
 std::map<int,lem::UFString> tokenizer_flags;
 rules->GetTokenizer().Tokenize( *dict, text, tokens, classes, tokenizer_flags, trace==NULL ? NULL : trace->PreprocessorTrace() );

 LEM_CHECKIT_Z( classes.size()==tokens.size() );

 const LexerTextPos * prev_token = GetBeginToken();

 for( lem::Container::size_type i=0; i<classes.size(); ++i )
  {
   const lem::UCString & word = tokens[i];

   TokenizationTags * tags = NULL;
   const UFString *s = classes[i];

   if( s==NULL || s->empty() )
    {
     tags = new TF_NoFilter();
    }
   else
    {  
     TF_ClassFilter * f = new TF_ClassFilter();

     lem::Collect<UFString> classes;
     lem::parse( *s, classes, L" " );

     for( lem::Container::size_type k=0; k<classes.size(); ++k )
      {
       UCString cname = classes[k].c_str();
       const int ic = dict->GetSynGram().FindClass(cname);
       LEM_CHECKIT_Z( ic!=UNKNOWN );
       if( ic!=UNKNOWN )
        f->AddClass(ic);
      }
   
     tags = f;
    }

   // Выполняем дораспознавание токена.
   Word_Form * wordform = dict->GetLexAuto().ProjectWord( word, CastSizeToInt(i), 1, tags, params, trace==NULL ? NULL : trace->RecognizerTrace() );
   lem_rub_off(tags);

   if( tokenizer_flags.find(CastSizeToInt(i))!=tokenizer_flags.end()  )
    {
     wordform->SetTokenizerFlag( tokenizer_flags[i] );
    }
 
   // для сборщика мусора.
   wordforms.push_back(wordform);

   LexerTextPos * new_token = new LexerTextPos( prev_token, wordform, 0, -1, word.length(), CastSizeToInt(i) );
   positions.push_back(new_token);
   edges.insert( std::make_pair(prev_token,new_token) );

   prev_token = new_token;
  }

 const LexerTextPos * end = GetEndToken( prev_token );

 return;
}




// Распознаёт слово, возвращается версионная словоформа. Может вернуть
// ссылку на занесенные в кэш результаты.
const Word_Form * WrittenTextLexer::Recognize( const lem::UCString & word, int WordIndex, int WordParts, const wchar_t * TokenizationFlags )
{
 LEM_CHECKIT_Z( !word.empty() );
 LEM_CHECKIT_Z( WordIndex>=0 );
 LEM_CHECKIT_Z( WordParts>0 );

 if( params.RecognizeWordforms )
  {
   if( use_recognition_cache && TokenizationFlags==NULL )
    {
     std::map<lem::UCString,const Word_Form*>::iterator it = recognitions.find(word);
     if( it!=recognitions.end() )
      {
       // используем кэшированный результат, полученный в другой ветке графа.
       // Так как нам необходимо, чтобы каждый токен имел свою копию словоформы с уникальным адресом,
       // то выполним глубокое копирование.
       Word_Form * copy = new Word_Form( *it->second, true );
       copy->SetOriginPos(WordIndex);
 
       const int nver = copy->VersionCount()-1;
       for( int i=0; i<nver; ++i )
        copy->GetAlts()[i]->SetOriginPos(WordIndex);
 
       wordforms.push_back(copy);
       return copy;
      }
    }
 
 
   // Определимся с фильтрацией на основании позиции слова и регистра его букв.
 
   int case_flags=UNKNOWN;
 
   int ichar=0;
   bool all_upper=false, first_upper=false, all_lower=true;
   lem::WideStringUcs4 src_enum( word.c_str() );
   for(;;)
    {
     const lem::uint32_t src_ucs4 = src_enum.Fetch();
     if(!src_ucs4)
      break;
 
     if( upper_xlat->IsSourceSymbol(src_ucs4) )
      {
       // встретился символ в нижнем регистре, значит отбрасываем вариант "все в верхнем".
       all_upper = false;
        
      }
     else if( upper_xlat->IsResultSymbol(src_ucs4) )
      {
       all_lower = false;
 
       if( ichar==0 )
        {
         // первый символ - в верхнем регистре.
         first_upper = true;
        }
       else
        {
         first_upper = false;
        }
      }
 
     ichar++;
    }
 
   // теперь надо закодировать регистр в виде id состояния для специальной координаты.
   // Класс CasingCoder знает про эту координату, поэтому берем его
 
   if( WordIndex==0 )
    {
     // Для первого слова особый подход - если оно начинается с заглавной, то
     // это ничего не означает. Только если оно в верхнем регистре, то будем применять фильтр.
     if( all_upper )
      case_flags = casing_coder->Upper;
     else if( all_lower )
      case_flags = casing_coder->Lower;
    }
   else
    {
     if( first_upper )
      case_flags = casing_coder->FirstCapitalized;
     else if( all_upper )
      case_flags = casing_coder->Upper;
     else if( all_lower )
      case_flags = casing_coder->Lower;
    }
 
   // остался вариант EachLexemCapitalized, его мы не определяем.
 
   TokenizationTags * tags=NULL;
   if( case_flags!=UNKNOWN )
    {
     tags = new TF_CaseFilter( casing_coder->icoord_casing, case_flags, casing_coder->Lower );
    }
 
   // Слово еще не разбиралось, выполняем морфологический анализ.
   // todo: params.AllowPrimaryFuzzyWordRecog --> нечеткое распознавание для несловарных токенов.
   Word_Form * new_recognition = dict->GetLexAuto().ProjectWord( word, WordIndex, WordParts, tags, params, trace==NULL ? NULL : trace->RecognizerTrace() );
 
   lem_rub_off(tags);
 
   if( TokenizationFlags!=NULL )
    new_recognition->SetTokenizerFlag(TokenizationFlags);
   
   // для сборщика мусора.
   wordforms.push_back(new_recognition);
 
   // сохраняем в кэше.
   // recognitions.insert( std::make_pair( word, new_recognition ) );

   return new_recognition;
  }
 else
  {
   RC_Lexem rc_word( new Solarix::Lexem(word) );
   RC_Lexem rc_normalized( new Solarix::Lexem( lem::to_upper(word) ) );
   Word_Form * new_recognition = new Word_Form( rc_word, rc_normalized, UNKNOWN, 0.0f );
   new_recognition->SetOriginPos( WordIndex );
   wordforms.push_back(new_recognition); // для сборщика мусора
   return new_recognition;
  }
}



namespace {
static bool token_sorter( const LexerTextPos * x, const LexerTextPos * y )
{
 return x->GetWordLength() > y->GetWordLength();
}
}


void WrittenTextLexer::TryToSplitToken(
                                       const LexerTextPos * previous_token,
                                       const LexerTextPos * token,
                                       lem::MCollect<const LexerTextPos*> & tokens
                                      )
{
 token_is_split.insert( token ); // чтобы избежать повторной попытки разбиения.

 // Упрощенный алгоритм - разбиваем только на 2 словарные лексемы.

 const lem::UCString & word0 = * token->GetWordform()->GetNormalized();

 const int max_prefix_len = word0.length()-1;

 for( int prefix_len=1; prefix_len<=max_prefix_len; ++prefix_len )
  {
   lem::UCString prefix = lem::left( word0, prefix_len );
   if( dict->GetSynGram().IsWordForm( prefix ) )
    {
     lem::UCString suffix( word0.c_str()+prefix_len );
     if( dict->GetSynGram().IsWordForm(suffix) )
      {
       // Создаем 2 новых токена из префикса и суффикса

       // расчет штрафа. если разбиваемая лексема - словарная, то увеличиваем штраф.
       int score=-1;
       if( dict->GetSynGram().IsWordForm( *token->GetWordform()->GetNormalized() ) )
        score--;

       // префикс
       lem::UCString prefix_str = lem::left( *token->GetWordform()->GetName(), prefix_len );
       const Word_Form * prefix_wordform = Recognize( prefix_str, token->GetWordIndex(), 1, NULL );
       LexerTextPos * prefix_token = new LexerTextPos( previous_token, prefix_wordform, score, token->GetStartPosition(), prefix_str.length(), token->GetWordIndex() );
       prefix_token->Reconstructed();

       positions.push_back( prefix_token );
       edges.insert( std::make_pair(previous_token,prefix_token) );
       tokens.push_back( prefix_token );

       // суффикс
       lem::UCString suffix_str( token->GetWordform()->GetName()->c_str() + prefix_len );
       const Word_Form * suffix_wordform = Recognize( suffix_str, token->GetWordIndex()+1, 1, NULL );
       LexerTextPos * suffix_token = new LexerTextPos( prefix_token, suffix_wordform, -1, token->GetStartPosition()+prefix_len, suffix_str.length(), token->GetWordIndex()+1 );
       suffix_token->Reconstructed();

       positions.push_back( suffix_token );
       edges.insert( std::make_pair(prefix_token,suffix_token) );

       prefix_token->SetNextChained( suffix_token );

/*
       #if defined SOL_DEBUGGING
       if( trace!=NULL )
        {
         lem::MCollect<lem::UCString> split;
         split.push_back( prefix_str );
         split.push_back( suffix_str );
         trace->PreprocessorTrace()->TokenIsSplit( *token->GetWordform()->GetName(), split );
        }
       #endif*/
      }
    }
  }


 return;
}


namespace {
 bool IsDashChar( wchar_t c )
 {
  return c==L'-' || c==0x2014 || c==2013 || c==2012;
 }
}


// для реконструкции слиянием - убираем у слова начальный или финальный '-', чтобы
// восстановить слово после деления на слоги для переноса.
lem::UCString WrittenTextLexer::RemoveDash( const lem::UCString & word ) const
{
 if( word.length()>1 )
  {
   if( IsDashChar(word.front()) )
    return lem::UCString( word.c_str()+1 ); // убираем лидирующий '-'
   else if( IsDashChar(word.back()) )
    return lem::left(word,word.length()-1); // убираем финальный '-'
  }

 return word;
}


void WrittenTextLexer::Extract(
                               const lem::UFString & Text,
                               int CurrentPosition,
                               const LexerTextPos *PreviousToken,
                               lem::MCollect<const LexerTextPos*> & tokens
                              )
{
 ExtractUnfiltered( Text, CurrentPosition, PreviousToken, (lem::MCollect<LexerTextPos*>&)tokens );



 if( params.UseTokenReconstruction )
  {
   // Попробуем расщепить полученные токены на словарные лексемы. Например НЕЗНАЮ --> НЕ ЗНАЮ
   const int n0 = CastSizeToInt(tokens.size());
   for( int i=0; i<n0; ++i )
    {
     const LexerTextPos * tok = tokens[i];
     if( !tok->IsReconstructed() && token_is_split.find(tok)==token_is_split.end() )
      TryToSplitToken( PreviousToken, tok, tokens );
    }
  }


 filtered_next_after.insert(PreviousToken);

 return;
}



void WrittenTextLexer::ExtractAhead(
                                    int n_tokens,
                                    const lem::UFString & Text,
                                    int CurrentPosition,
                                    const LexerTextPos *PreviousToken,
                                    lem::MCollect<LexerTextPos*> & tokens
                                   )
{
 if( n_tokens>1 )
  {
   lem::MCollect<LexerTextPos*> ahead_tokens;
   ExtractUnfiltered( Text, CurrentPosition, PreviousToken, ahead_tokens );

   for( lem::Container::size_type i=0; i<ahead_tokens.size(); ++i )
    {
     LexerTextPos * ahead_token = ahead_tokens[i];
     ExtractAhead( n_tokens-1, Text, ahead_token->GetNextCharPos(), ahead_token, tokens );
    }
  }
 else
  {
   ExtractUnfiltered( Text, CurrentPosition, PreviousToken, tokens );
  }

 return;
}


namespace {
inline bool IsTiret( wchar_t c ) { return c=='-' || c==0x2014 /*—*/ || c==0x2013 /*–*/; }
}


void WrittenTextLexer::ExtractUnfiltered(
                                         const lem::UFString & Text,
                                         int CurrentPosition,
                                         const LexerTextPos *PreviousToken,
                                         lem::MCollect<LexerTextPos*> & tokens
                                        )
{
 tokens.clear();

 std::pair<CACHED_EDGES::const_iterator,CACHED_EDGES::const_iterator> p_edges = edges.equal_range(PreviousToken);
 if( p_edges.first!=p_edges.second )
  {
   for( CACHED_EDGES::const_iterator it=p_edges.first; it!=p_edges.second; ++it )
    {
     tokens.push_back( it->second );
    }

   return;
  }


 if( CurrentPosition<Text.length() )
  {
   // справа есть текст, попробуем извлечь из него токены.

   const int WordIndex = PreviousToken==NULL ? 0 : PreviousToken->GetWordIndex()+1;

   // ищем все варианты токенизации, для которых в словаре есть лексемы, то есть
   // включая многолексемные слова с внутренними пробелами и др. разделителями.
   // Учитываем правила токенизации.
   lem::MCollect<int> headword_lens;

   bool is_unbreakable_token=false; // если извлеченный токен нельзя расщеплять, то флаг станет true;

   const int StartPos = rules->Extract( *dict, Text, CurrentPosition, headword_lens, &is_unbreakable_token );

   if( headword_lens.empty() && rules->IsStreamingSegmentation() )
    {
     // Аварийная ситуация сегментация текста далее невозможна, хотя остались символы.
     // Возвращаем один особый токен-терминатор.

     LexerTextPos_Terminator * new_token = new LexerTextPos_Terminator();
     tokens.push_back(new_token);
     positions.push_back( new_token );
     edges.insert( std::make_pair( PreviousToken, new_token ) );

     return;
    }

   // Некоторые из этих слов могут оказаться вариантами мультилексем, их проверим отдельно.
   // Некоторые слова будут разбиты на несколько правилами препроцессора.
   // Некоторые слова могут начинать группу слов, которые будут заменены на
   // другие слова правилами препроцессора.

   // Сначала сделаем токены из всех простых слов.
   for( lem::Container::size_type i=0; i<headword_lens.size(); ++i )
    {
     const int WordLen = headword_lens[i];
     const int WordParts=1;
     const int Score=0;
     lem::UCString word( lem::mid( Text, StartPos, WordLen ).c_str() );

     const wchar_t * tokenization_flags=NULL;

     if( WordLen==1 && IsTiret(Text[StartPos]) )
      {
       if( StartPos>0 && StartPos<Text.length()-1 )
        {
         if( rules->IsWhitespace(Text[StartPos-1]) && rules->IsWhitespace(Text[StartPos+1]) )
          tokenization_flags = L"word_separation";
         else
          tokenization_flags = L"word_conjunction";
        }
      }     

     bool insert_word=true;

     // Если есть жадные правила препроцессинга, которые заменяют это слово на одно или несколько других,
     // то применяем эти правила, а слово не попадет в выходной список токенов.
     if( false /*...*/ )
      {
      }

     if( insert_word )
      {
       const Word_Form * new_wordform = Recognize( word, WordIndex, WordParts, tokenization_flags );

       // Если слово является начальной частью мультилексемы, то анализируем результаты распознавания.
       // Если слово распознано, то оно может быть само по себе. В этом случае дробим дальнейший путь распознавания.
       // В противном случае надо найти всю мультилексему, а одно первое слово не добавлять.

       int n_accepted_mlex=0; // счетчик найденных и распознанных мультилексем.
 
       const int ml_len = dict->GetSynGram().IsMultiLexemBegin( * new_wordform->GetNormalized() );
       if( ml_len>1 )
        {
         lem::MCollect<TextTokenizationItem> extracted;
         rules->ExtractNextWords( *dict, Text, StartPos + WordLen, ml_len-1, extracted );

         lem::MCollect<Solarix::Lexem> normalized_words;
         for( lem::Container::size_type k=0; k<extracted.size(); ++k )
          {
           Solarix::Lexem l( extracted[k].word );
           dict->GetLexAuto().TranslateLexem( l, true, params.language_ids.front() );
           normalized_words.push_back( l );
          }
         
         // Фактическая максимальная длина возможной мультилексемы.
         const int max_count = CastSizeToInt(extracted.size())+1;

         // теперь перебираем все длины, начиная с 2.
         for( int xlen=1; xlen<max_count; ++xlen )
          {
           RC_Lexem ml( new Lexem() );
           ml->Add( * new_wordform->GetNormalized() );
           for( int k=0; k<xlen; ++k )
            {
             ml->Add( normalized_words[k] );
            }

           // такая мультилексема известна?
           if( dict->GetSynGram().IsMultiLexem(*ml) )
            {
             // да.
             n_accepted_mlex++;
             
             // Фактическая длина участка строки, с которого взята мультилексема.
             const int MLexlength = extracted[xlen-1].start_pos+extracted[xlen-1].len - StartPos;

             Solarix::Lexem ml( lem::mid( Text, StartPos, MLexlength ).c_str() );

             // распознаём это мультислово
             const Word_Form * new_wordform = Recognize( ml, WordIndex, xlen+1, NULL );

             LexerTextPos * new_token = new LexerTextPos(
                                                         PreviousToken,
                                                         new_wordform,
                                                         Score,
                                                         StartPos,
                                                         MLexlength,
                                                         WordIndex
                                                        );

             // Токен для мультилексемы распознан
             if( new_token!=NULL )
              {
               positions.push_back( new_token );      
               tokens.push_back(new_token);
               edges.insert( std::make_pair( PreviousToken, new_token ) );
              }
            }
          }
        }


       // если распознали мультилексемы, кооторые начинаются с этого слова, а одиночное слово
       // не удалось распознать, то не будем добавлять слово в токены. Хотя можно в будущем
       // добавлять его с начислением штрафа, как менее достоверный вариант.
       if( n_accepted_mlex>0 && new_wordform->GetEntryKey()==UNKNOWN_ENTRY_KEY )
        {
         // ... ??? todo
        }
       else
        {
         // добавляем одиночное слово.
         LexerTextPos * new_token = new LexerTextPos(
                                                     PreviousToken,
                                                     new_wordform,
                                                     Score,
                                                     StartPos,
                                                     WordLen,
                                                     WordIndex
                                                    );
    
         if( new_token!=NULL )
          {
           positions.push_back( new_token );      
           tokens.push_back(new_token);
           edges.insert( std::make_pair( PreviousToken, new_token ) );
          }
        }
      }
    }

  
   // Тут можно отсортировать варианты в порядке убывания длины. Таким образом,
   // сначала будут идти самые длинные токены, как наиболее вероятные.
   if( tokens.size()>1 )
    std::sort( tokens.begin(), tokens.end(), token_sorter );

   LimitBranching( (lem::MCollect<const LexerTextPos*>&)tokens);

   AddBranching( CastSizeToInt(tokens.size()) );
  }

 return;
}



// От токена current продолжаем токенизацию вправо. Возможно, появятся альтернативные пути,
// каждый из которых будет представлен своим объектом в списке next.
// Возвращает true, если токенизация продолжена; false если дальше вправо нет слов.
//
// даже если возвращает false, то в next помещается минимум один специальный токен, обозначающий
// текст за правой границей.
bool WrittenTextLexer::Fetch(
                             const LexerTextPos * current,
                             const TokenExpectation * expectations,
                             lem::MCollect<const LexerTextPos*> & next
                            )
{
 LEM_CHECKIT_Z( current!=NULL );

 if( current->GetNextChained()!=NULL )
  {
   next.push_back( current->GetNextChained() );
   return true;
  }
 else if( current->IsEnd() || current->IsTerminator() )
  {
   // Достигли правую границу.

   Word_Form *wf = new Word_Form( Solarix::Lexem(L"") );
   wordforms.push_back(wf);

   LexerTextPos_BeyondRight * t = new LexerTextPos_BeyondRight( current, wf );
   positions.push_back(t);

   next.push_back(t);
   return false;
  }
 else
  {
   const int NextCharPosition = current->GetNextCharPos();
  
   if( NextCharPosition>=text.length() )
    {
     next.push_back( GetEndToken( current ) );
     return true;
    }
   else
    {
     Extract( text, NextCharPosition, current, next );
  
     if( next.empty() )
      {
       // Если в конце предложения много пробелов или символ перевода строки, то оказываемся здесь.
       next.push_back( GetEndToken( current ) );
      }
  
     return true;
    }
  }
}


