// -----------------------------------------------------------------------------
// File SENTENCE.CPP
//
// (c) Koziev Elijah
//
// Content:
// ����� Sentence - ����������� ��� ������ ����.
// -----------------------------------------------------------------------------
//
// CD->24.10.1997
// LC->08.07.2012
// --------------

#if defined SOL_CAA && !defined SOL_NO_AA

#include <lem/oformatter.h>
#include <lem/conversions.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/sentencebroker.h>
//#include <lem/solarix/WordEntry.h>
//#include <lem/solarix/LA_PreprocessorTrace.h>
//#include <lem/solarix/GG_CharOperations.h>
//#include <lem/solarix/GG_CharOperation.h>
//#include <lem/WideStringUcs4.h>
//#include <lem/solarix/casing_coder.h>
#include <lem/solarix/TF_ClassFilter.h>
#include <lem/solarix/WrittenTextLexer.h>
#include <lem/solarix/TextRecognitionParameters.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/phrasema.h>

using namespace lem;
using namespace Solarix;


Sentence::Sentence(void): id_language(UNKNOWN)
{
 return;
}

Sentence::Sentence( const Sentence &x )
 : words(x.words), org_phrase(x.org_phrase), id_language(x.id_language)
{}

void Sentence::operator=( const Sentence &x )
{
 org_phrase = x.org_phrase;
 id_language = x.id_language;
 words = x.words;
 return;
}




void Sentence::AddWord( const lem::UCString & word )
{
 LEM_CHECKIT_Z( !word.empty() );
 SentenceWord * x = new SentenceWord();
 x->word = word;
 words.push_back( x );
 return;
}


// ***********************************
// ��������� ����������� �� �����.
// ***********************************
void Sentence::Parse(
                     const lem::UFString & str_buffer,
                     bool Pretokenized,
                     Dictionary * dict,
                     int _id_language,
                     TrTrace * trace
                    )
{
 org_phrase = str_buffer;

 if( Pretokenized )
  {
   const int l = org_phrase.length();

   UCString word;
   int i=0;
   while( i<l )
    {
     wchar_t c = org_phrase[i];

     if( c==L'\x1F' )
      {
       if( !word.empty() )
        {
         AddWord( word );
         word.clear();
        }
      }
     else
      {
       word+=c;
       i++;
      }
    }

   // ��������� ����� ������������� ������ ������
   if( !word.empty() )
    {
     AddWord( word );
    }

   return;
  }

 if( dict!=NULL )
  {
   Solarix::TextRecognitionParameters params;
   params.SetLanguageID(_id_language);

   if( params.LanguageUnknown() )
    {
     // ���� ����������� �� ����� ����, ��������� ��� �� ������ �������������� ���������.
     const int id_language = dict->GetLexAuto().GuessLanguage( str_buffer );

     if( id_language==UNKNOWN )
      {
       lem::MemFormatter msg;
       msg.printf( "Can not guess the language of the phrase [%us]", str_buffer.c_str() );
       throw E_BaseException(msg.string());
      }

     params.SetLanguageID( id_language );

     if( trace!=NULL )
      {
       trace->LanguageGuessed( str_buffer, id_language );
      }
    }

   params.RecognizeWordforms = false;

   WrittenTextLexer lexer( str_buffer, params, dict, trace );
   lem::MCollect<const LexerTextPos*> ends;
   lexer.FetchEnds( lexer.GetBeginToken(), ends, lexer.GetParams().GetMaxRightLeaves() );

   if( !ends.empty() )
    {
     lem::MCollect<const LexerTextPos*> inverted_path;
     ends.front()->Collect_Right2Left( lexer.GetBeginToken(), inverted_path );

     for( int i=CastSizeToInt(inverted_path.size())-2; i>=1; --i )
      {
       SentenceWord * word = new SentenceWord();
       word->word = * inverted_path[i]->GetWordform()->GetName();
       word->normalized_word = * inverted_path[i]->GetWordform()->GetNormalized();
       words.push_back(word);
      }
    }

   id_language = lexer.GetParams().GetLanguageID();

   return;
  }

 if( _id_language!=UNKNOWN )
  id_language = _id_language;

 if( dict!=NULL && id_language==UNKNOWN )
  {
   if( id_language==UNKNOWN )
    {
     // ��������� ���������� ���� �� �������������� ���������.
     id_language = dict->GetLexAuto().GuessLanguage(org_phrase);

     if( trace!=NULL )
      trace->LanguageGuessed( org_phrase, id_language );
    }
  }


 // ������� � ��������� ����� �������� ������������� �������������.
 const int l = org_phrase.length();

 UCString word;
 int i=0;
 while( i<l )
  {
   wchar_t c = org_phrase[i];

   if( lem::is_uspace(c) ) // ����� ���� ������ ������ UNICODE-������� ���������� ����� � �.�.
    c = L' ';

   const bool delimiter = lem::is_udelim(c) || c==L' ';

   if( delimiter )
    {
     switch(c)
     {
      case L' ':
      case L'\r': 
      case L'\n':
      case L'\t':
       {
        if( !word.empty() )
         {
          AddWord( word );
          word.clear();
         }

        i++;
        while( i<l )
        {
         c = org_phrase[i];
         // ������� ����������
         if( c==L' ' || c==L'\r' || c==L'\n' )
          i++;
         else
          break;  
        }

        break;
       }

      case L'.':
      case L'!':
      case L'?':
       {
        // ����� - ������ ������
        if( c==L'.' )
         {
          // � ����� �����������?
          bool eol=true;
          UCString dot; dot=c;

          i++;
          while( i<l )
           {
            wchar_t c2 = org_phrase[i];
            if( lem::is_uspace(c2) )
             c2 = L' ';   
  
            if( c2==L'\r' || c2==L'\n' || c2==L' ' || c2=='\t' )
             break;

            if( c2!=L'.' )
             {
              eol=false;
              break; 
             }
 
            dot += c2;
            i++;
           }
      
          if( eol )
           {
            // ��, ����� � ����� �����������
            if( word.empty() )
             {
              AddWord( dot );
              break;
             } 
            else
             {
              AddWord( word );
              AddWord( dot );
              word.clear();
              break;
             }  
           }  
          else
           {
            if( dot==L"..." )
             {
              if( word.empty() )
               {
                AddWord( dot );
               } 
              else
               {
                AddWord( word );
                AddWord( dot );
                word.clear();
               }  

              break;
             }
           }
 
          // ���, ��� ����� ���� �������� ������ ����� "3.141", ���� ������ ���������� "��.",
          // ���� ������ ���������� "..."
          word += c;
          break;
         }

        if( word.empty() )
         {
          i++;
          word = c;

          // ����� ���� ��������� ???, !!!, ... ��� ���� ����� ?!
          while( i<l )
           {
            wchar_t c2 = org_phrase[i];
            if( c2==L'.' || c2==L'!' || c2=='?' )
             {
              word+=c2;
              i++;              
             }
            else
             {
              break;
             }  
           }

          AddWord( word );
          word.clear();
         }
        else
         {
          AddWord( word );
          word.clear();
         }
 
        break;
       }

      default:
       {
        if( word.empty() )
         {
          i++;
          word = c;
          AddWord( word );
          word.clear();
         }
        else
         {
          AddWord( word );

          i++;
          word = c;
          AddWord( word );
          word.clear();
         }

        break;
       }
     }
    }
   else
    {
     word+=c;
     i++;
    }
  }

 // ��������� ����� ������������� ������ ������
 if( !word.empty() )
  {
   AddWord( word );
  }
 
 return;
}



void Sentence::clear(void)
{
 words.clear();
 return;
}

void Sentence::PrintOrg( OFormatter &s ) const
{
 for( Container::size_type i=0; i<size(); i++ )
  {
   const SentenceWord * word = words[i];
   s.printf( "%us ", word->word.c_str() );
  }

 return;
}

// ***************************************************************
// ������������ ������ �� ����� ��������� ��������� �����������.
// ***************************************************************
const lem::UFString Sentence::string( wchar_t delimiter ) const
{
 UFString res;
 for( Container::size_type i=0; i<size(); i++ )
  {
   if( i ) res += delimiter;
   res += GetWord(i).c_str();
  }

 return res;  
}


void Sentence::SaveBin( lem::Stream &bin ) const
{
 // ... todo
 return;
}

void Sentence::LoadBin( lem::Stream &bin )
{
 // ... todo
 return;
}


#endif // defined SOL_CAA
