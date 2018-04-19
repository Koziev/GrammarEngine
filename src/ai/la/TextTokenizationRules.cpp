#include <lem/solarix/sentencebroker.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/TextTokenizationRules.h>

using namespace Solarix;


wchar_t TextTokenizationRules::DefaultSpaceChars[] =
L" "
L"\u00a0" // NO-BREAK SPACE
L"\u200b" // ZERO-WIDTH SPACE 
L"\u2002" // 	EN SPACE
L"\u2003" // 	EM SPACE
L"\u2004" // 	THREE-PER-EM SPACE
L"\u2005" // 	FOUR-PER-EM SPACE
L"\u2006" // 	SIX-PER-EM SPACE
L"\u2007" // 	FIGURE SPACE
L"\u2008" // 	PUNCTUATION SPACE
L"\u2009" // 	THIN SPACE
L"\u200A" // 	HAIR SPACE
L"\u202F" // 	NARROW NO-BREAK SPACE
L"\u205F" // 	MEDIUM MATHEMATICAL SPACE
L"\u3000" // 	IDEOGRAPHIC SPACE
L"\u1680" // 	OGHAM SPACE MARK
L"\u2000" // 	EN QUAD
L"\u2001" // 	EM QUAD
L"\t\r\n";




TextTokenizationRules::TextTokenizationRules(const lem::MCollect<int> & langs, SentenceTokenizer * _tokenizer)
    : id_language(langs), tokenizer(_tokenizer)
{
    LEM_CHECKIT_Z(_tokenizer != nullptr);
    segmentation_flag = Whitespace;
    return;
}



void TextTokenizationRules::AddSpaceCharacters(const wchar_t * whitespace)
{
    int i = 0;
    while (0 != whitespace[i])
    {
        if (spaces.find(whitespace[i]) == UNKNOWN)
            spaces.push_back(whitespace[i]);

        i++;
    }

    AddDelimiterCharacters(whitespace);

    return;
}


void TextTokenizationRules::AddDelimiterCharacters(const wchar_t * delimiter_chars)
{
    int i = 0;
    while (0 != delimiter_chars[i])
    {
        if (delimiters.find(delimiter_chars[i]) == UNKNOWN)
            delimiters.push_back(delimiter_chars[i]);

        i++;
    }

    return;
}




// Пропускаем все пробельные символы с текущей позиции.
// Возвращает позицию первого не-пробельного символа.
int TextTokenizationRules::SkipSpace(const lem::UFString & Text, int pos) const
{
    while (pos < Text.length())
    {
        // Если текущий символ - пробел, то сдвигаемся вправо.
        if (spaces.find(Text[pos]) == UNKNOWN)
            break;

        pos++;
    }

    return pos;
}


// ********************************************************************************************
// В тексте, который начинается в Text, ищем альтернативные варианты выделения слов.
// Все варианты возвращаем через список words.
// Результат работы - указатель на начало слов, то есть первый символ после пропуска пробелов.
// ********************************************************************************************
int TextTokenizationRules::Extract(
    Solarix::Dictionary & dict,
    const lem::UFString &Text,
    int CurrentPosition,
    lem::MCollect<int> & WordLengths,
    bool * is_unbreakable_token
)
{
    WordLengths.clear();

    if (segmentation_flag == Whitespace)
    {
        // пропускаем пробельные символы.
        const int NewStartPos = SkipSpace(Text, CurrentPosition);

        if (NewStartPos < Text.length())
        {

            /*
                 *is_unbreakable_token=false;
                 int WordLen=0, Pos=NewStartPos;
                 if( delimiters.find(Text[Pos])!=UNKNOWN )
                  {
                   WordLen=1;
                  }
                 else
                  {
                   while( Pos<Text.length() )
                   {
                    wchar_t c = Text[Pos];
                    if( delimiters.find(c)!=UNKNOWN )
                     break;

                    WordLen++;
                    Pos++;
                   }
                  }

                 if( NewStartPos+WordLen+1 < Text.length() )
                  {
                   // найденный участок текста, начиная с NewStartPos длиной WordLen+1, является началом специального случая?
                   lem::UCString probe( Text.c_str()+NewStartPos, Text.c_str()+NewStartPos+WordLen+1 );
                   probe.to_upper();

                   #if defined LEM_THREADS
                   lem::Process::RWU_ReaderGuard rlock(cs_unbreakable_begginnings);
                   #endif
                   std::set<lem::UCString>::const_iterator it = not_unbreakable_begginnings.find(probe);
                   if( it==not_unbreakable_begginnings.end() )
                    {
                     #if defined LEM_THREADS
                     lem::Process::RWU_WriterGuard wlock(rlock);
                     #endif

                     // тут теоретически надо сделать вторую проверку на вхождение к кэш, но так как невхождение в кэш просто немного
                     // замедлит работу, то не будем этого делать.

                     if( tokenizer->IsUnbreakableFront( probe ) )
                      {
                       if( tokenizer->MatchAllLens( Text, NewStartPos, WordLengths ) )
                        {
                         *is_unbreakable_token=true;
                        }
                      }
                     else
                      {
                       not_unbreakable_begginnings.insert(probe);
                      }
                    }
                  }
                 else if( NewStartPos+WordLen == Text.length()-1 )
                  {
                   // Извлеченный токен и символ-разделитель после него являются последними в строке.
                   lem::UCString probe( Text.c_str()+NewStartPos, Text.c_str()+NewStartPos+WordLen+1 );

                   #if defined LEM_THREADS
                   lem::Process::RWU_ReaderGuard rlock(cs_not_unbreakable);
                   #endif
                   std::set<lem::UCString>::const_iterator it = not_unbreakable.find(probe);
                   if( it==not_unbreakable.end() )
                    {
                     #if defined LEM_THREADS
                     lem::Process::RWU_WriterGuard wlock(rlock);
                     #endif

                     // тут теоретически надо сделать вторую проверку на вхождение в not_unbreakable, но так как невхождение в кэш просто немного
                     // замедлит работу, то не будем этого делать.
                     if( tokenizer->IsMatched( probe ) )
                      {
                       // извлеченный токен и разделитель после него образуют неразрывный спецтокен!
                       *is_unbreakable_token=true;
                       WordLengths.push_back( WordLen+1 );
                      }
                     else
                      {
                       not_unbreakable.insert( probe );
                      }
                    }
                  }

                 if( !*is_unbreakable_token )
                  WordLengths.push_back(WordLen);
            */

            if (tokenizer->MatchAllLens(Text, NewStartPos, WordLengths))
            {
                *is_unbreakable_token = true;
            }
            else
            {
                // специальных случаев не обнаружено, поэтому выберем из текста цепочку символов до пробела или до разделителя.
                *is_unbreakable_token = false;
                int WordLen = 0, Pos = NewStartPos;
                if (delimiters.find(Text[Pos]) != UNKNOWN)
                {
                    WordLen = 1;
                }
                else
                {
                    while (Pos < Text.length())
                    {
                        wchar_t c = Text[Pos];
                        if (delimiters.find(c) != UNKNOWN)
                            break;

                        WordLen++;
                        Pos++;
                    }
                }

                WordLengths.push_back(WordLen);
            }
        }

        return NewStartPos;
    }
    else if (segmentation_flag == Streaming)
    {
        if (CurrentPosition < Text.length())
        {
            // для языков типа китайского - явных разделителей нет, вместо этого
            // надо использовать информацию о том, какие префиксы валидны (использовать PrefixEntrySearcher::IsValidPrefix)
            // и какие лексемы есть в языке (IsWordForm).
            // Наращиваем длину излекаемых слов до тех пор, пока они являются валидными префиксами, и фиксируем
            // длину тех вариантов, которые являются известными лексемами.


            // Максимальная длина валидного префикса.  
            const int max_prefix_len = prefix_lookup->FindMaxPrefixLen(Text.c_str() + CurrentPosition);

            // теперь будет искать лексемы разной длины вплоть до максимального префикса.

            Solarix::Lexem prefix;

            for (int prefix_len = 1; prefix_len <= max_prefix_len; ++prefix_len)
            {
                prefix += Text[CurrentPosition + prefix_len - 1];

                // Это известная лексема?
                if (dict.GetSynGram().IsWordForm(prefix))
                {
                    // да - добавляем длину в список найденных слов.
                    WordLengths.push_back(prefix_len);
                }
            }
        }

        return CurrentPosition;
    }

    return UNKNOWN;
}



// Используется для поиска мультилексем.
// С указанной позиции выделяет максимум NumberToExtract слов и возвращает их список через extracted.
void TextTokenizationRules::ExtractNextWords(
    Solarix::Dictionary & dict,
    const lem::UFString & Text,
    int CurrentPosition,
    int NumberToExtract,
    lem::MCollect<TextTokenizationItem> & extracted
) const
{
    extracted.clear();

    int Pos = CurrentPosition;
    while (CastSizeToInt(extracted.size()) < NumberToExtract && Pos < Text.length())
    {
        Pos = SkipSpace(Text, Pos);
        int NewStartPos = Pos;

        int WordLen = 0;
        if (delimiters.find(Text[Pos]) != UNKNOWN)
        {
            WordLen = 1;
            Pos++;
        }
        else
        {
            while (Pos < Text.length())
            {
                wchar_t c = Text[Pos];
                if (delimiters.find(c) != UNKNOWN)
                    break;

                WordLen++;
                Pos++;
            }
        }

        if (WordLen > 0)
        {
            TextTokenizationItem w;
            w.len = WordLen;
            w.start_pos = NewStartPos;
            w.word = lem::mid(Text, NewStartPos, WordLen).c_str();
            extracted.push_back(w);
        }
    }

    return;
}

