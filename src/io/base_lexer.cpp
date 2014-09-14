// -----------------------------------------------------------------------------
// File BASE_LEXER.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// Немного статических объектов для лексера (класса-шаблона BaseParser<...>).
// -----------------------------------------------------------------------------
//
// CD->13.08.2004
// LC->04.01.2009
// --------------

#include <lem/lexers.h>

using namespace lem;

int     Special_Char<char>::eof(void)    { return EOF; }

wchar_t Special_Char<wchar_t>::eof(void) { return WEOF; }



  /************************************************************************
   Процедура подготавливает акселератор поиска лексемы в списке токенов.
   Применяется такой алгоритм. Все пространство значений хэшей (мне самому
   нравится это начало) разбивается на 256 подклассов. Каждому подклассу
   соответствует подсписок токенов. Чтобы токенизировать лексему (поясняю:
   найти для неё соответствующий токен), достаточно взять хэш-код строки,
   а он уже вычислен!, и определить, к какому подпространству относитс
   лексема. Далее будем искать в списке, относящемся к данному подклассу.
  *************************************************************************/
  void ASrcLookUpTable::Prepare( const std::vector< lem::CString > &Tokens )
  {
   int it=0;
   for( std::vector< lem::CString >::const_iterator i=Tokens.begin(); i!=Tokens.end(); i++, it++ )
    push_back( ASrcTok( *i, it ) );

   const int N=CastSizeToInt(size());
   ASrcTok dummy;

   for( int gap=N/2; gap>0; gap/=2 )
    for( int i=gap; i<N; i++ )
     for( int j=i-gap; j>=0; j-=gap )
      {
       if( get(j+gap).GetHash() > get(j).GetHash() )
        break;

       dummy          = get(j);
       (*this)[j]     = get(j+gap);
       (*this)[j+gap] = dummy;
      }

   return;
  }

  void USrcLookUpTable::Prepare( const std::vector< UCString > &Tokens )
  {
   int it=0;
   for( std::vector< UCString >::const_iterator i=Tokens.begin(); i!=Tokens.end(); i++, it++ )
    push_back( USrcTok( *i, it ) );

   const int N=CastSizeToInt(size());
   USrcTok dummy;

   for( int gap=N/2; gap>0; gap/=2 )
    for( int i=gap; i<N; i++ )
     for( int j=i-gap; j>=0; j-=gap )
      {
       if( get(j+gap).GetHash() > get(j).GetHash() )
        break;

       dummy          = get(j);
       (*this)[j]     = get(j+gap);
       (*this)[j+gap] = dummy;
      }

   return;
  }

  int ASrcLookUpTable::Find( const lem::CString &s ) const
  {
   const lem::uint8_t hash = s.GetHash();

   int ileft=0, iright=CastSizeToInt(size())-1;

   while( (iright-ileft)>1 )
    {
     const int imid = (iright+ileft)/2;
     if( get(imid).GetHash() > hash )
      iright = imid;
     else if( get(imid).GetHash() == hash )
      {
       // The item with equal hash is found. It can be
       // more than one item with the same hash, so we must
       // scan the whole range of items with equal hashes.

       if( get(imid) == s )
        return get(imid).index;

       // Scan backward to the origin of equal hashes
       for( int i1=imid-1; i1>=ileft; i1-- )
        if( get(i1).GetHash() != hash )
         break;
        else if( get(i1) == s )
         return get(i1).index;

       // and scan forward for the same reason
       for( int i2=imid+1; i2<=iright; i2++ )
        if( get(i2).GetHash() != hash )
         break;
        else if( get(i2) == s )
         return get(i2).index;

       return UNKNOWN;
      }
     else
      ileft = imid;
    }

   if( get(ileft) == s )
    return get(ileft).index;

   if( get(iright) == s )
    return get(iright).index;

   return UNKNOWN;
  }

  int USrcLookUpTable::Find( const UCString &s ) const
  {
   const lem::uint8_t hash = s.GetHash();

   int ileft=0, iright=CastSizeToInt(size())-1;

   while( (iright-ileft)>1 )
    {
     const int imid = (iright+ileft)/2;
     if( get(imid).GetHash() > hash )
      iright = imid;
     else if( get(imid).GetHash() == hash )
      {
       // The item with equal hash is found. It can be
       // more than one item with the same hash, so we must
       // scan the whole range of items with equal hashes.

       if( get(imid) == s )
        return get(imid).index;

       // Scan backward to the origin of equal hashes
       for( int i1=imid-1; i1>=ileft; i1-- )
        if( get(i1).GetHash() != hash )
         break;
        else if( get(i1) == s )
         return get(i1).index;

       // and scan forward for the same reason
       for( int i2=imid+1; i2<=iright; i2++ )
        if( get(i2).GetHash() != hash )
         break;
        else if( get(i2) == s )
         return get(i2).index;

       return UNKNOWN;
      }
     else
      ileft = imid;
    }

   if( get(ileft) == s )
    return get(ileft).index;

   if( get(iright) == s )
    return get(iright).index;

   return UNKNOWN;
  }



ASrcToken::ASrcToken(
             const str_type &Str,
             const SourceState &pos,
             bool ignore_case,
             const std::vector< lem::CString > &Tokens
            ) : lem::CString(Str), begin(pos)
    {
     token=UNKNOWN;

     // Ищем лексему в таблице ключевых слов.
     if( ignore_case )
      {
       str_type ls = lem::to_lower( static_cast<str_type>(*this) );

       int i=0;
       for( std::vector< lem::CString >::const_iterator j=Tokens.begin(); j!=Tokens.end(); j++, i++ )
         if( lem::to_lower( *j ) == ls )
          {
           token=i;
           break;
          }
      }
     else
      {
       int i=0;
       for( std::vector< lem::CString >::const_iterator j=Tokens.begin(); j!=Tokens.end(); j++, i++ )
        if( *j == str )
         {
          token=i;
          break;
         }
      }

     return;
    }

USrcToken::USrcToken(
             const str_type &Str,
             const SourceState &pos,
             bool ignore_case,
             const std::vector< UCString > &Tokens
            ) : UCString(Str), begin(pos)
    {
     token=UNKNOWN;

     // Ищем лексему в таблице ключевых слов.
     if( ignore_case )
      {
       str_type ls = lem::to_lower( static_cast<str_type>(*this) );

       int i=0;
       for( std::vector< UCString >::const_iterator j=Tokens.begin(); j!=Tokens.end(); j++, i++ )
         if( lem::to_lower( *j ) == ls )
          {
           token=i;
           break;
          }
      }
     else
      {
       int i=0;
       for( std::vector< UCString >::const_iterator j=Tokens.begin(); j!=Tokens.end(); j++, i++ )
        if( *j == str )
         {
          token=i;
          break;
         }
      }

     return;
    }



UCString ASrcToken::GetUnicode(void) const
{
 return to_unicode(*this);
}

