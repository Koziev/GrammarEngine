// LC->17.01.2013

#include <lem/solarix/la_autom.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/Alphabets.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/sentencebroker.h>

using namespace lem;
using namespace Solarix;

static const int MAX_SENTENCE_LENGTH=1024;
#define EOS_CODE L'\x1D'

SentenceBroker::SentenceBroker(void) : eof(true), LanguageID(UNKNOWN)
{
 Prepare( NULL, UNKNOWN );
 return;
}

SentenceBroker::SentenceBroker( Dictionary &dict, int language ): eof(true)
{
 Prepare( &dict, language );
 return;
}


SentenceBroker::SentenceBroker( lem::Char_Stream::WideStream &_stream /*non-deleteable*/, Dictionary * dict, int language )
{
 Open(_stream);
 Prepare( dict, language );
 return;
}

SentenceBroker::SentenceBroker( const wchar_t *text, Dictionary * dict, int language )
 : max_sentence_length(MAX_SENTENCE_LENGTH)
{
 Open( lem::Ptr<lem::Char_Stream::WideStream>( new lem::Char_Stream::UTF16_MemReader(text) ) );
 Prepare( dict, language );
 return;
}

SentenceBroker::SentenceBroker( const lem::UFString &text, Dictionary * dict, int language )
 : max_sentence_length(MAX_SENTENCE_LENGTH)
{
 Open( lem::Ptr<lem::Char_Stream::WideStream>( new lem::Char_Stream::UTF16_MemReader(text) ) );
 Prepare( dict, language );
 return;
}

SentenceBroker::SentenceBroker( lem::Ptr<lem::Char_Stream::WideStream> _stream, Dictionary * dict, int language )
 :  max_sentence_length(MAX_SENTENCE_LENGTH), stream(_stream)
{
 Open(_stream);
 Prepare( dict, language );
 return;
}


void SentenceBroker::Prepare( Dictionary * dict, int language )
{
 LanguageID = language;

 max_sentence_length = MAX_SENTENCE_LENGTH;

 const wchar_t *sent_delims_raw[] = { L".", L"?", L"!", L";", L"...", L"?!", L"\x1D", NULL };
 int i=0;
 while( sent_delims_raw[i]!=NULL )
  {
   if( sent_delims_raw[i][1]==0 )
    sent_delims1.push_back( sent_delims_raw[i][0] );

   sent_delims.push_back( sent_delims_raw[i] ); 
   i++;
  }

 la = NULL;
 sg = NULL;

 #if defined SOL_CAA && !defined SOL_NO_AA
 if( dict!=NULL )
  {
   tokenizer = dict->GetSentenceTokenizer(language);
   seeker = dict->seeker;
   la = & dict->GetLexAuto(); 
   sg = & dict->GetSynGram();

   if( language!=UNKNOWN )
    {
     const SG_Language & lang = dict->GetSynGram().languages()[language];

     const int ip1 = lang.FindParam(L"SentenceBrokerFlags");
     if( ip1!=UNKNOWN )
      {
       for( lem::Container::size_type i=0; i<lang.params[ip1]->values.size(); ++i )
        {
         const UFString &v = lang.params[ip1]->values[i];
         if( v.eqi(L"UseLexicon") )
          use_lexicon = true;
         else if( v.eq_begi(L"MinFormLen=") )
          {
           const int k = v.search(L'=');
           if( k!=UNKNOWN )
            min_wordform_len = lem::to_int( v.c_str()+k+1 );
          }
        }
      }

     const int ip11 = lang.FindParam(L"CasingSentBroker");
     if( ip11!=UNKNOWN )
      {
       casing_sent_delim.clear();
       for( lem::Container::size_type q=0; q<lang.params[ip11]->values.size(); ++q )
        casing_sent_delim.push_back( lem::UCString(lang.params[ip11]->values[q].c_str()) );

       CharCasingCoord = dict->GetSynGram().FindCoord(L"CharCasing").GetIndex();
       if( CharCasingCoord!=UNKNOWN )
        {
         LowerCasingState = dict->GetSynGram().coords()[CharCasingCoord].FindState(L"lower");
        }
      }

     const int ip2 = lang.FindParam( L"SentenceDelimiters" );
     if( ip2!=UNKNOWN )
      {
       sent_delims.clear();
       sent_delims.push_back( lem::UCString(EOS_CODE) );
       sent_delims1.push_back( EOS_CODE );

       for( lem::Container::size_type q=0; q<lang.params[ip2]->values.size(); ++q )
        {
         const lem::UFString &s = lang.params[ip2]->values[q];
         sent_delims.push_back( lem::UCString(s.c_str()) );

         if( s.length()==1 )
          sent_delims1.push_back( s.front() );
        }
      }

     const int ip3 = lang.FindParam( L"MaxSentenceLen" );
     if( ip3!=UNKNOWN )
      {
       max_sentence_length = lem::to_int(lang.params[ip3]->values.front());
      }
    }
  }
 #endif

 return;
}


void SentenceBroker::Open( lem::Char_Stream::WideStream &_stream /*non-deleteable*/ )
{
 stream = lem::Ptr<lem::Char_Stream::WideStream>( &_stream, lem::null_deleter() );
 return;
}


void SentenceBroker::Open( lem::Ptr<lem::Char_Stream::WideStream> _stream )
{
 stream = _stream;
 return;
}


wchar_t SentenceBroker::GetChar(void)
{
 if( !chars.empty() )
  return chars.pop();

 wchar_t c = stream->wget();

 if( c==WEOF )
  {
   eof=true;
   return WEOF;
  }

 if( c=='\n' )
  {
   // Если следом идет еще один перевод строки, значит перед нами двойной перевод строки, который
   // мы считаем разделителем предложений.
   lem::Stream::pos_type backpos = stream->tellp();

   wchar_t c2 = stream->wget();
   if( c2==L'\r' || c2==L'\n' )
    c=EOS_CODE;
   else if( lem::is_uspace(c2) )
    {
     // может идти цепочка пробельных символов, а после них - символ перевода строки.
     while( !stream->eof() )
     {
      wchar_t c3 = stream->wget();
      if( c3==L'\r' || c3==L'\n' )
       {
        c=EOS_CODE;
        break;
       }
      else if( lem::is_uspace(c3) )
       continue;
      else
       break;
     }
    }

   // В любом случае возвращаем курсор чтения.
   stream->seekp(backpos);
  }
 else if( lem::is_uspace(c) || c==L'\r' || c==L'\t' )
  c = L' ';

 return c;
}


wchar_t SentenceBroker::PeekChar(void)
{
 if( !chars.empty() )
  return chars.top();

 return stream->wpeek();
} 


void SentenceBroker::UngetChar( wchar_t c )
{
 chars.push_back(c);
 return;
}

bool SentenceBroker::Fetch(void)
{
 return Fetch(last_sentence);
}

bool SentenceBroker::IsTokenDelimiter( wchar_t c ) const
{
 return tokenizer.NotNull() ?
         tokenizer->IsTokenDelimiter(c) :
         (lem::is_uspace(c) || lem::is_udelim(c) || c==L'\r' || c==L'\n' || c==EOS_CODE);
}



bool SentenceBroker::Fetch( lem::UFString &line )
{
 line.clear();

 if( eof )
  return false;

 int n_quote=0; // для учета символов "

 // Пропустим начальные пробелы.
 while( !eof )
  {
   wchar_t c = GetChar();

   if( c==WEOF )
    {
     break;
    }

   if( !lem::is_uspace(c) )
    {
     UngetChar(c);
     break;
    }
  }


 while( !eof || !chars.empty() )
  {
   wchar_t c = GetChar();

   if( c==WEOF )
    {
     eof = true;
     return true;
    }
   else if( c==L' ' )
    {
     line.Add_Dirty(c);
     continue;
    }
   else if( c==EOS_CODE )
    {
     // пустая строка - попробуем считать следующую.
     if( !line.empty() )
      break;

     continue;
    }

   bool line_ready=false;

   if(
      ( line.empty() || IsTokenDelimiter(line.back()) || IsTokenDelimiter(c)) &&
      tokenizer.NotNull() && tokenizer->IsUnbreakableFront(c)
     )
    {
     // Возможно далее идет исключительный случай. Выбираем символы из входного потока в 
     // попытке сконструировать максимально длинное исключение.
     lem::UCString substr;
     substr = c;

     while( !eof )
      {
       wchar_t c2 = GetChar();
       if( c2==WEOF )
        {
         // Достигли конца файла. Считали полный исключительный случай?
         if( tokenizer->IsMatched(substr) )
          {
           // Да!
           line.Add_Dirty( substr.c_str() );
           c = c2;

           // Считанный токен является разделителем предложений (типа ...)
           if( sent_delims.find(substr)!=UNKNOWN )
            {
             line.calc_hash();
             line.trim();

             if( !line.empty() && (n_quote%2)==0 )
              {  
               count++;
               return true;
              }
            }
          }
         else
          {
           // нет - вернем накопленные символы в поток чтения
           for( int k=substr.length()-1; k>=0; --k )
            UngetChar( substr[k] );

           c = GetChar();
          }

         break;
        }

       substr += c2; // добавили еще один символ.

       // С символов substr начинается хоть одно исключение?
       if( !tokenizer->IsUnbreakableFront(substr) || substr.length()==lem::UCString::max_len )
        {
         // Возможно, предыдущая подстрока является исключительной ситуацией.
         UCString substr1 = lem::left( substr, substr.length()-1 );
         if( tokenizer->IsMatched(substr1) && IsTokenDelimiter(substr.back()) )
          {
           // Да!
           line.Add_Dirty( substr1.c_str() );

           // Считанный токен является разделителем предложений (типа ...)
           if( sent_delims.find(substr1)!=UNKNOWN )
            {
             if( (n_quote%2)==0 )
              {
               line.calc_hash();
               line.trim();

               if( !line.empty() )
                {   
                 UngetChar(c2);
                 count++;
                 return true;
                }
              }
             else
              {
               if( c2==L'"' )
                {
                 // Ситуация типа Кошка говорит "Мяу!" Собака говорит "Гав!"
                 bool continuation_found=true;
                 lem::MCollect<wchar_t> tmp_chars;
                 while( !eof || !chars.empty() )
                  {
                   const wchar_t c4 = GetChar();
                   tmp_chars.push_back(c4);
                   if( !lem::is_uspace(c4) )
                    {
                     if( IsUpperChar(c4) )
                      {
                       continuation_found=false;
                      }
 
                     break;
                    }
                  }

                 for( int k=CastSizeToInt(tmp_chars.size())-1; k>=0; --k )
                  UngetChar( tmp_chars[k] );

                 if( !continuation_found )
                  {
                   line.Add_Dirty( c2 );
                   return true;
                  }
                }
              }
            }

           #if defined SOL_CAA
           // Если считанный токен делит предложения в случае, когда за ним
           // идет слово с первой заглавной буквой.
           if( use_lexicon && casing_sent_delim.find( to_lower(substr1) )!=UNKNOWN && CharCasingCoord!=UNKNOWN && LowerCasingState!=UNKNOWN )
            {
             Lexem next_token = PickNextToken();
             if( IsUpperChar(next_token.front()) )
              {
               la->TranslateLexem( next_token );

               int ie=UNKNOWN;
               if( seeker!=NULL )
                {
                 ie = seeker->Find(next_token,false);
                }
               else
                {
                 MCollect<Word_Coord> found_list;
                 la->ProjectWord( next_token, found_list, LanguageID );
                 if( !found_list.empty() )
                  ie = found_list.front().GetEntry();
                }

               if( ie!=UNKNOWN )
                {
                 const Solarix::SG_Entry &e = sg->GetEntry(ie);

                 const int casing = e.attrs().FindOnce( Solarix::GramCoordAdr(CharCasingCoord) );
                 if( casing==LowerCasingState || casing==UNKNOWN )
                  {
                   UngetChar(c2);
                   count++;
                   return true;
                  }
                }
              }
            }
           #endif

           c = c2;           
          }
         else
          {
           // Возвращаем все загруженные символы обратно в поток.
           for( int k=substr.length()-1; k>=0; --k )
            UngetChar( substr[k] );

           c = GetChar();
          } 

         break;
        }
      }
    }

   if( c==WEOF )
    {
     // закончился исходный текст, принудительно прерываем текущее предложение.
     eof = true;
     return true;
    }

   const bool ItIsSentDelim = sent_delims1.find(c)!=UNKNOWN;
   if( ItIsSentDelim )
    {
     if( c==EOS_CODE )
      break;

     // Обычный конец предложения. Для точки надо проверять, если сразу после точки идет цифра
     // или символ в нижнем регистре, то это НЕ конец предложения.
     bool breaker=false; 
     bool add_char=true;

     // Если у нас есть незакрытая пара ", то проверим следующий непустой символ.
     if( (n_quote%2)!=0 )
      {
       const wchar_t c2 = GetChar();
       // Если это закрывающая "
       if( c2==L'"' )
        {
         n_quote++;
         line.Add_Dirty( c );
         line.Add_Dirty( c2 );

         const wchar_t c4 = GetChar();
         if( sent_delims1.find(c4)!=UNKNOWN )
          {
           line.Add_Dirty( c4 );
           count++;
           return true;
          }
         else
          {
           UngetChar(c4);
          }

         // если дальше - пробел, и после него идет символ в нижнем регистре, то это не конец предложения.
         bool continuation_found=true;
         UFString tmp_chars;
         while( !eof )
          {
           const wchar_t c5 = GetChar();
           if( c5==WEOF )
            {
             break;
            }

           tmp_chars.Add_Dirty(c5);
           if( !lem::is_uspace(c5) )
            {
             // найден не-пробельный символ.
             if( IsUpperChar(c5) )
              {
               continuation_found=false;
              }

              break;
            }
          }

         // возвращаем все символы обратно
         for( int i=CastSizeToInt(tmp_chars.size())-1; i>=0; --i )
          UngetChar( tmp_chars[i] );

         if( !continuation_found )
          {
           // обрываем предложение.
           line.trim();
           count++;
           return true;
          }
        }
       else
        {
         // нет - продолжим считывание символов предложения.
         line.Add_Dirty( c );
         line.Add_Dirty( c2 );
        }
      }
     else
      {
       #if defined SOL_CAA
       if( tokenizer.NotNull() && seeker.NotNull() && use_lexicon && c==L'.' )
        {
         // надо выделить слово, предшествующее точке. идем влево до разделителя токенов.
         int icur = line.length()-1;
         while( icur>=0 )
          {
           if( tokenizer->IsTokenDelimiter(line[icur]) )
            break; // нашли начало последнего слова
           else
            icur--; // сдвигаемся влево
          }
    
         Solarix::Lexem last_word;
         for( int j=icur+1; j<line.length(); ++j )
          last_word.Add_Dirty( line[j] );
    
         last_word.calc_hash();

         la->TranslateLexem( last_word );
    
         if( seeker->Find(last_word,false)!=UNKNOWN )
          {
           breaker=true;
          }
        }
       #endif 
    
       if( !breaker )
        {
         breaker = true; 
         wchar_t c2 = PeekChar();
         if( c==L'.' )
          {
           if( lem::is_udigit(c2) )
            {
             breaker=false;
            }
           else if( IsLowerChar(c2) ) 
            {
             breaker=false;
            }
           else if( c2==L',' )
            {
             breaker=false;
            }
           else if( lem::is_uspace(c2) )
            {
             // Дойдем до первого не-пробельного символа.
             line.Add_Dirty( c );
    
             add_char=false;
             while( c!=WEOF )
              {
               c = GetChar();
               if( c==EOS_CODE )
                break;

               line.Add_Dirty( c );
               c = PeekChar();
    
               if( !lem::is_uspace(c) )
                {
                 if( IsLowerChar(c) )
                  {
                   breaker = false;
                  }
    
                 break; 
                }
              }
    
             c=L'.';
            }
    
           wchar_t c0 = c;
           c2 = PeekChar();
           if( c2==c0 )
            {
             line.Add_Dirty( c );
             add_char=false;
             while( c!=WEOF && c==c0 )
              {
               c = GetChar();
               line.Add_Dirty( c );
               c = PeekChar();
              } 
            }    
          }
         else if( c=='!' || c=='?' )
          {
           wchar_t c0 = c;
           c2 = PeekChar();
           if( c2==L'?' || c2==L'!' ) // То есть токены типа !!! и !?
            {
             line.Add_Dirty( c );
             add_char=false;
             while( c!=WEOF && (c==L'!' || c==L'?') )
              {
               c = GetChar();
               line.Add_Dirty( c );
               c = PeekChar();
              } 
            }
          }
        }
    
       if( c==WEOF )  
        {
         eof = true;
         add_char=false;
        } 
    
       if( breaker )
        {
         line_ready=true;
        }
    
       if( add_char )
        line.Add_Dirty( c );
      }
    }
   else if( line.length()>max_sentence_length && (lem::is_uspace(c) || c==L',' || c==L'-' || c==L';' || c==L':' ) )
    {
     // Слишком длинные предложения обрываем на безопасных символах.
     line_ready=true;
     line.Add_Dirty( c );
    }
   else if( c==L'\r' || c==L'\n' || c==L'\t' || c==L'\b' )
    {
     // некоторые управляющие символы заменяем пробелами
     line.Add_Dirty( L' ' );
    }
   else
    {
     line.Add_Dirty( c );
   
     if( c==L'"' )
      n_quote++;
     else if( c==L'(' )
      {
       // если предложение начинается с (, то надо смотреть, какой токен будет перед ), и если это терминатор - обрывать предложение.
       if( line.size()==1 )
        {
         if( ReadCharsUntilClosingParen( line ) )
          {
           line.trim();
           return true;
          }
        }
       else
        {
         ReadCharsUntilClosingParen( line );
        }
      }
    }
     
   if( line_ready ) 
    {
     line.calc_hash();
     line.trim();

     if( !line.empty() )
      count++;

     return true;
    }
  }

 line.calc_hash();
 line.trim();

 if( !line.empty() )
  count++;

 return true;
}


// Считываем символы до закрывающей )
// Возвращает true, если последний токен перед ) был терминатором предложения.
bool SentenceBroker::ReadCharsUntilClosingParen( lem::UFString & line )
{
 int n_paren=1;

 lem::UCString unbreakable;
 bool last_is_sentence_terminator=false; 

 while( !Eof() || !chars.empty() )
  {
   wchar_t c = GetChar();
   if( c==WEOF )
    {
     eof=true;
     break;
    }

   if( lem::is_uspace(c) )
    {
     line.Add_Dirty(L' ');

     if( line.length()>=max_sentence_length )
      break;
    }
   else
    {
     // считаем символ или группу неразрывных символов.
     ReadCharOrUnbreakable(c,unbreakable);

     if( unbreakable==L')' )
      {
       line += unbreakable.front();
       n_paren--;
       if( !n_paren )
        break;
      }
     else if( unbreakable==L'(' )
      {
       line.Add_Dirty( unbreakable.front() );
       n_paren++;
       last_is_sentence_terminator=false;
      }
     else
      {
       line.Add_Dirty( unbreakable.c_str() );
       last_is_sentence_terminator = sent_delims.find(unbreakable)!=UNKNOWN;
      }

     if( line.length()>=max_sentence_length*2 )
      break;
    }
  }

 line.calc_hash();

 return last_is_sentence_terminator;
}



bool SentenceBroker::Eof(void) const
{ return eof; }

int SentenceBroker::Count(void) const
{ return count; }


// *********************************************************************
// Возвращает следующий полный токен из входного потока, не перемещая
// курсор чтения.
// *********************************************************************
lem::UCString SentenceBroker::PickNextToken(void)
{
 UFString buffer;
 UCString res;

 // Сначала пропустим пробелы
 while(true)
  {
   const wchar_t c = GetChar();
   if( c==WEOF )
    break;

   buffer.Add_Dirty(c);
   if( !lem::is_uspace(c) )
    {
     res = c;
     break;  
    }
  }

 // Теперь считываем символы до любого разделителя
 while(true)
  {
   const wchar_t c = GetChar();
   if( c==WEOF )
    break;
   
   buffer.Add_Dirty(c);

   if( tokenizer->IsTokenDelimiter(c) )
    break;

   res += c;  
  }

 // Возвращаем обратно все считанные символы.
 for( int i=buffer.length()-1; i>=0; --i )
  UngetChar( buffer[i] );

 return res;
}


void SentenceBroker::ReadCharOrUnbreakable( wchar_t first_char, lem::UCString &buffer )
{
 if( tokenizer.IsNull() )
  {
   buffer = first_char;
  }
 else
  {
   wchar_t c = first_char;
   if( tokenizer->IsUnbreakableFront(c) )
    {
     // загрузим неразрывную группу символов
     lem::UCString substr;
     substr = c;

     while( !eof || !chars.empty() )
      {
       wchar_t c2 = GetChar();
       if( c2==WEOF )
        {
         // Достигли конца файла. Считали полный исключительный случай?
         if( tokenizer->IsMatched(substr) )
          {
           // Да!
           buffer = substr.c_str();
          }
         else
          {
           // нет - вернем накопленные символы в поток чтения
           for( int k=substr.length()-1; k>=0; --k )
            UngetChar( substr[k] );

           c = GetChar();
          }

         break;
        }

       substr += c2; // добавили еще один символ.

       // С символов substr начинается хоть одно исключение?
       if( !tokenizer->IsUnbreakableFront(substr) )
        {
         // Возможно, предыдущая подстрока является исключительной ситуацией.
         UCString substr1 = lem::left( substr, substr.length()-1 );
         if( tokenizer->IsMatched(substr1) )
          {
           // да.
           buffer = substr1;
           UngetChar(c2);
           return;
          }
         else
          {
           // возвращаем все символы обратно, первый символ будет единственным в группе.
           for( int k=substr.length()-1; k>=1; --k )
            UngetChar( substr[k] );

           buffer=first_char;
           return;           
          }
        }
       else if( tokenizer->IsMatched(substr) )
        {
         buffer = substr;
         return;
        }
      }

     buffer = substr;
    }
   else
    {
     buffer=c;
    }    
  }

 return;
}


void SentenceBroker::LoadUpperAndLowerChars(void)
{
 chars_loaded = true;

 const SG_Language &lang = sg->languages()[LanguageID];
 const lem::MCollect<int> &ids = lang.GetAlphabets();
 for( lem::Container::size_type i=0; i<ids.size(); ++i )
  {
   const int id_alphabet = ids[i];

   // для этого алфавита надо получить список букв в верхнем регистре
   // ... TODO
  }

 return;
}


bool SentenceBroker::IsUpperChar( wchar_t c )
{
 if( LanguageID!=UNKNOWN && sg!=NULL )
  {
   if( !chars_loaded )
    {
     LoadUpperAndLowerChars();
    }

   if( !upper_chars.empty() )
    {
     return upper_chars.find(c)!=upper_chars.end();
    }
  }

 // упрощенная проверка.
 return lem::is_ualpha(c) && lem::is_uupper(c);
}


bool SentenceBroker::IsLowerChar( wchar_t c )
{
 if( LanguageID!=UNKNOWN && sg!=NULL )
  {
   if( !chars_loaded )
    {
     LoadUpperAndLowerChars();
    }

   if( !lower_chars.empty() )
    {
     return lower_chars.find(c)!=lower_chars.end();
    }
  }

 // упрощенная проверка.
 return lem::is_ualpha(c) && lem::is_ulower(c);
}
