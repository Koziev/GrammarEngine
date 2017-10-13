#include <lem/config.h>
#include <lem/startup.h>
#include <lem/unicode.h>
#include <lem/solarix/Lemmatizator.h>
#include <lem/solarix/lemmatizator_engine.h>


#if defined LEM_WINDOWS

#include <windows.h>
BOOL APIENTRY DllMain(
                      HANDLE /*hModule*/, 
                      DWORD  /*ul_reason_for_call*/, 
                      LPVOID /*lpReserved*/
					 )
{
 // Library DLL is loaded. 
 return TRUE;
}

#endif // defined LEM_WINDOWS


// http://www.solarix.ru/api/en/sol_LoadLemmatizator.shtml
LEMMA_API(HLEM) sol_LoadLemmatizatorW( const wchar_t *Filepath, int Flags )
{
 lem::Init();

 try
  {
   Solarix::Lemmatizator *p = new Solarix::Lemmatizator;
   p->Load( lem::Path(Filepath), Flags );
   return p;
  }
 catch(...)
  {
  }

 return NULL;
}

// http://www.solarix.ru/api/en/sol_LoadLemmatizator.shtml
LEMMA_API(HLEM) sol_LoadLemmatizatorA( const char *Filepath, int Flags )
{
 lem::Init();
 return sol_LoadLemmatizatorW( lem::to_unicode(Filepath).c_str(), Flags );
}


// http://www.solarix.ru/api/en/sol_LoadLemmatizator.shtml
LEMMA_API(HLEM) sol_LoadLemmatizator8( const char *Filepath, int Flags )
{
 lem::Init();
 return sol_LoadLemmatizatorW( lem::from_utf8(Filepath).c_str(), Flags );
}


// http://www.solarix.ru/api/en/sol_DeleteLemmatizator.shtml
LEMMA_API(int) sol_DeleteLemmatizator( HLEM hEngine )
{
 try
  {
   delete (Solarix::Lemmatizator*)hEngine;
  }
 catch(...)
  {
   return -1;
  }

 return 0;
}


// http://www.solarix.ru/api/en/sol_GetLemma.shtml
LEMMA_API(int) sol_GetLemmaW( HLEM hEngine, const wchar_t *word, wchar_t *result, int bufsize )
{
 try
  {
   if( hEngine!=NULL )
    {
     Solarix::Lemmatizator *e = (Solarix::Lemmatizator*)hEngine;

     lem::UCString lemma;
     const int n = e->Lemmatize( lem::UCString(word), lemma );
     if( lemma.empty() )
      {
       *result=0;
       return 0;
      }
     else
      {
       lem::lem_strncpy( result, lemma.c_str(), bufsize );
       return n;
      }
    }
   else
    {
     *result=0;
     return 0;
    }
  }
 catch(...)
  {
   return 0;
  }
}


// http://www.solarix.ru/api/en/sol_GetLemma.shtml
LEMMA_API(int) sol_GetLemmaA( HLEM hEngine, const char *word, char *result, int bufsize )
{
 if( hEngine!=NULL )
  {
   Solarix::Lemmatizator *e = (Solarix::Lemmatizator*)hEngine;

   lem::UCString lemma;
   lem::UCString ascii( lem::to_unicode(word).c_str() );

   const int n = e->Lemmatize( ascii, lemma );

   if( lemma.empty() )
    {
     *result=0;
     return 0;
    }
   else
    {
     lem::FString a( lem::to_ascii( lemma.c_str() ) ); 
     lem::lem_strncpy( result, a.c_str(), bufsize );
     return n;
    }
  }
 else
  {
   *result=0;
   return 0;
  }
}


// http://www.solarix.ru/api/en/sol_GetLemma.shtml
LEMMA_API(int) sol_GetLemma8( HLEM hEngine, const char *word, char *result, int bufsize )
{
 if( hEngine!=NULL )
  {
   Solarix::Lemmatizator *e = (Solarix::Lemmatizator*)hEngine;

   lem::UCString lemma;
   const int n = e->Lemmatize( lem::UCString( lem::from_utf8(word).c_str() ), lemma );
   if( lemma.empty() )
    {
     *result=0;
     return 0;
    }
   else
    {
     lem::FString utf8 = lem::to_utf8( lemma.c_str() ); 
     lem::lem_strncpy( result, utf8.c_str(), bufsize );
     return n;
    }
  }
 else
  {
   *result=0;
   return 0;
  }
}


// http://www.solarix.ru/api/en/sol_GetLemmas.shtml
LEMMA_API(HLEMMAS) sol_GetLemmasW( HLEM hEngine, const wchar_t *word )
{
 try
  {
   if( hEngine!=NULL )
    {
     Solarix::Lemmatizator *e = (Solarix::Lemmatizator*)hEngine;
     lem::MCollect<lem::UCString> * lemmas = new lem::MCollect<lem::UCString>();
     e->Lemmatize( lem::UCString(word), *lemmas );
     return lemmas;
    }
   else
    {
     return NULL;
    }
  }
 catch(...)
  {
   return NULL;
  }
}


// http://www.solarix.ru/api/en/sol_GetLemmas.shtml
LEMMA_API(HLEMMAS) sol_GetLemmasA( HLEM hEngine, const char *word )
{
 return sol_GetLemmasW( hEngine, lem::to_unicode(word).c_str() );
}


// http://www.solarix.ru/api/en/sol_GetLemmas.shtml
LEMMA_API(HLEMMAS) sol_GetLemmas8( HLEM hEngine, const char *word )
{
 return sol_GetLemmasW( hEngine, lem::from_utf8(word).c_str() );
}


// http://www.solarix.ru/api/en/sol_CountLemmas.shtml
LEMMA_API(int) sol_CountLemmas( HLEMMAS hList )
{
 if( hList!=NULL )
  return CastSizeToInt(((const lem::MCollect<lem::UCString>*)hList)->size());
 else
  return 0;
}


// http://www.solarix.ru/api/en/sol_GetLemmaString.shtml
LEMMA_API(int) sol_GetLemmaStringW( HLEMMAS hList, int Index, wchar_t *result, int bufsize )
{
 try
  {
   if( hList==NULL )
    {
     *result = 0;
     return -1;
    }
   else
    { 
     const lem::UCString & s = ((const lem::MCollect<lem::UCString>*)hList)->get(Index);
     lem::lem_strncpy( result, s.c_str(), bufsize );
     return s.length();
    }
  }
 catch(...)
  {
   return -1;
  }
}


// http://www.solarix.ru/api/en/sol_GetLemmaString.shtml
LEMMA_API(int) sol_GetLemmaStringA( HLEMMAS hList, int Index, char *result, int bufsize )
{
 try
  {
   if( hList==NULL )
    {
     *result = 0;
     return -1;
    }
   else
    { 
     const lem::UCString & s = ((const lem::MCollect<lem::UCString>*)hList)->get(Index);
     lem::FString a( lem::to_ascii( s.c_str() ) ); 
     lem::lem_strncpy( result, a.c_str(), bufsize );
     return a.length();
    }
  }
 catch(...)
  {
   return -1;
  }
}


// http://www.solarix.ru/api/en/sol_GetLemmaString.shtml
LEMMA_API(int) sol_GetLemmaString8( HLEMMAS hList, int Index, char *result, int bufsize )
{
 try
  {
   if( hList==NULL )
    {
     *result = 0;
     return -1;
    }
   else
    { 
     const lem::UCString & s = ((const lem::MCollect<lem::UCString>*)hList)->get(Index);
     lem::FString utf8 = lem::to_utf8( s.c_str() ); 
     lem::lem_strncpy( result, utf8.c_str(), bufsize );
     return utf8.length();
    }
  }
 catch(...)
  {
   return -1;
  }
}


// http://www.solarix.ru/api/en/sol_DeleteLemmas.shtml
LEMMA_API(int) sol_DeleteLemmas( HLEMMAS hList )
{
 try
  {
   if( hList!=NULL )
    {
     delete (const lem::MCollect<lem::UCString>*)hList;
    }
  }
 catch(...)
  {
   return -1;
  }

 return 0;
}








LEMMA_API(HLEMMAS) sol_LemmatizePhraseW( HLEM hEngine, const wchar_t *sentence, int Flags, int WordSeparator )
{
 try
  {
   if( hEngine!=NULL )
    {
     Solarix::Lemmatizator *e = (Solarix::Lemmatizator*)hEngine;

     lem::MCollect<lem::UCString> words;
     int cur=0;
     while( sentence[cur]!=0 )
     {
      lem::UCString word;
      while( sentence[cur]!=0 )
       if( sentence[cur]==(wchar_t)WordSeparator )
        {
         cur++;
         break;
        }
       else
        {
         word.Add_Dirty( sentence[cur] );
         cur++;
        }

      word.calc_hash();
      words.push_back(word);
     }

     lem::MCollect<lem::UCString> * lemmas = new lem::MCollect<lem::UCString>();
     e->Lemmatize( words, *lemmas );
     return lemmas;
    }
   else
    {
     return NULL;
    }
  }
 catch(...)
  {
   return NULL;
  }
}


LEMMA_API(HLEMMAS) sol_LemmatizePhraseA( HLEM hEngine, const char *sentence, int Flags, int WordSeparator )
{
 return sol_LemmatizePhraseW( hEngine, lem::to_unicode(sentence).c_str(), Flags, WordSeparator );
}


LEMMA_API(HLEMMAS) sol_LemmatizePhrase8( HLEM hEngine, const char *sentence, int Flags, int WordSeparator )
{
 return sol_LemmatizePhraseW( hEngine, lem::from_utf8(sentence).c_str(), Flags, WordSeparator );
}
