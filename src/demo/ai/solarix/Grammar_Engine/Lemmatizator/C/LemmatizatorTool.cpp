// Lemmatization API sample code.
// The program is also used as a test tool for lemmatizer.
//
// (c) by Elijah Koziev MentalComputing@gmail.com
//
// More information at: http://www.solarix.ru/for_developers/api/lemmatizator-api.shtml

#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <string>
#include <stdlib.h>



#include "../../../../../../include/lem/solarix/lemmatizator_engine.h"


#if defined CHECK_MODEL
#include "../../../../../../include/lem/solarix/solarix_grammar_engine.h"
#include "../../../../../../include/lem/solarix/_sg_api.h"
#endif


#if defined(__DARWIN_X11__)
#define _DARWIN
#elif defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__))
#define _DARWIN
#elif defined(__MACOSX__)
#define _DARWIN
#endif



#if defined _WIN32

#include <string>
#include <vector>
#include <windows.h>

static void fprint8( FILE *f, const char *utf8 )
{
 const int l8 = strlen(utf8);
 char * a = new char[ l8+1 ];

 wchar_t *w = new wchar_t[ l8+1 ];

 MultiByteToWideChar( CP_UTF8, 0, utf8, l8+1, w, l8+1 );

 int w8 = wcslen(w);
 
 memset( a, 0, l8 );
 WideCharToMultiByte( CP_OEMCP, 0, w, w8+1, a, l8+1, NULL, NULL );
 
 fprintf( f, "%s", a );

 delete[] w;
 delete[] a;
 return;
}
 
#else

static void fprint8( FILE *f, const char *utf8 )
{
 fprintf( f, "%s", utf8 ); 
 return;
}

#endif


static void print8( const char *utf8 )
{
 fprint8( stdout, utf8 );
}


#if defined CHECK_MODEL
static int stricmp8( const char * s1, const char * s2 )
{
 #if defined WIN32

 const int l1 = strlen(s1);
 wchar_t *w1 = new wchar_t[ l1+1 ];
 MultiByteToWideChar( CP_UTF8, 0, s1, l1+1, w1, l1+1 );

 const int l2 = strlen(s2);
 wchar_t *w2 = new wchar_t[ l2+1 ];
 MultiByteToWideChar( CP_UTF8, 0, s2, l2+1, w2, l2+1 );

 CharLowerBuffW( w1, l1 );
 CharLowerBuffW( w2, l2 );

 for( int i=0; i<l1; ++i )
  if( w1[i]==0x0401 )
   w1[i] = 0x0415;
  else if( w1[i]==0x0451 )
   w1[i] = 0x0435;

 for( int i=0; i<l2; ++i )
  if( w2[i]==0x0401 )
   w2[i] = 0x0415;
  else if( w2[i]==0x0451 )
   w2[i] = 0x0435;

 int rc = wcscmp( w1, w2 );
 
 delete[] w1;
 delete[] w2;

 return rc;

 #else

  #error not yet implemented

 #endif 
}
#endif


static void reads( char *buffer, int len, FILE *file )
{
 *buffer=0;
 fgets( buffer, len, file );
 int l = strlen(buffer);
 if( l>0 )
  {
   if( l>=2 )
    {
     if( buffer[l-2]=='\r' && buffer[l-1]=='\n' )
      {
       buffer[l-2]=0;
      }
     else if( buffer[l-1]=='\n' )
      {
       buffer[l-1]=0;
      }
    }
   else if( l==1 )
    {
     if( buffer[l-1]=='\n' )
      {
       buffer[l-1]=0;
      }
    } 
  }

 return;
}


static bool xisspace( char c )
{
 return c==' ' || c=='\t' || c=='\r' || c=='\n';
}


static void trim( char * str )
{
 int ileft=0;
 while( str[ileft]!=0 && xisspace(str[ileft]) )
  ileft++;

 char *line2 = str+ileft;
 int iright = strlen(line2)-1;
 
 while( iright>0 )
  {
   if( !xisspace( line2[iright] ) )
    {
     line2[iright+1]=0;
     break;
    }

   iright--;
  }

 memmove( str, line2, strlen(line2)+1 );

 return;
}



#if defined CHECK_MODEL
void CheckModel( const char * dictionary_path, const char * corpus_path, const char * log_path, const char * language )
{
 const int LanguageID = RUSSIAN_LANGUAGE; // TODO: recognize the language by 'language' argument

 HGREN hEngine = sol_CreateGrammarEngine(NULL);

 int load_status = sol_LoadDictionaryExA( hEngine, (std::string(dictionary_path)+"\\dictionary.xml").c_str(), 0 );
 if( load_status!=1 )
  {
   printf( "Could not load the dictionary\n" );
   exit(1);
  }

 HLEM hLemm = sol_LoadLemmatizatorA( (std::string(dictionary_path)+"\\lemmatizer.db").c_str(), LEME_DEFAULT );

 if( hLemm==NULL )
  {
   printf( "Could not load the lemmatizator\n" );
   exit(1);
  }
 

 FILE *file = fopen( corpus_path, "rt" );
 if( file==NULL )
  {
   printf( "Can not open file %s\n", corpus_path );
   exit(1);
  }

 FILE *log_file = fopen( log_path, "wt" );
 if( log_file==NULL )
  {
   printf( "Can not open file %s\n", log_path );
   exit(1);
  }

 char line[1000], sentence[1000];

 // Optionally skip the BOM
 fread( line, 3, 1, file );
 if( line[0]!=(char)0xef || line[1]!=(char)0xbb || line[2]!=(char)0xbf )
  fseek( file, 0, SEEK_SET ); 

 bool AllowFuzzy=false;
 bool TopDown=true;
 bool CompleteOnly=true;
 bool EnableFilters=true; // по умолчанию фильтры включены
 bool EnableTokenReconstruction=false;
 bool EnableSparse=false;
 bool BottomUp=false;

 int total_word_count=0;
 int n_err=0;
 int sentence_count=0;

 while( !feof(file) )
  {
   *line=0;
   reads( line, 1000, file );

   trim(line);

   if( strlen(line)==0 )
    continue;

   if( line[0]=='#' )
    {
     if( memcmp( line, "#exit", 5 )==0 )
      break;

     if( memcmp( line, "#fuzzyon", 8 )==0 )
      {
       AllowFuzzy=true;
      }
     else if( memcmp( line, "#fuzzyoff", 9 )==0 )
      {
       AllowFuzzy=false;
      }     
     else if( memcmp( line, "#allow_incomplete", 17 )==0 )
      {
       TopDown=true;
       CompleteOnly=false;
       EnableSparse=false;
       BottomUp=false;
      }     
     else if( memcmp( line, "#disallow_incomplete", 20 )==0 )
      {
       CompleteOnly=true;
       TopDown=true;
       EnableSparse=false;
       BottomUp=false;
      }
     else if( memcmp( line, "#disable_filters", 16 )==0 )
      {
       EnableFilters=false;
      }
     else if( memcmp( line, "#enable_filters", 15 )==0 )
      {
       EnableFilters=true;
      }
     else if( memcmp( line, "#allow_reco", 11 )==0 )
      {
       EnableTokenReconstruction=true;
      }
     else if( memcmp( line, "#disallow_reco", 14 )==0 )
      {
       EnableTokenReconstruction=false;
      }
     else if( memcmp( line, "#sparse", 7 )==0 )
      {
       EnableSparse=true;
       BottomUp=false;
       TopDown=false;
       CompleteOnly=true;
      }
     else if( memcmp( line, "#bottomup", 10 )==0 )
      {
       BottomUp=true;
       EnableSparse=false;
       TopDown=false;
       CompleteOnly=true;
      }
     else if( memcmp( line, "#topdown", 14 )==0 )
      {
       TopDown=true;
       CompleteOnly=true;
       EnableSparse=false;
       BottomUp=false;
      }

     continue;
    }

   if( strncmp( line, "$begin", 6 )!=0 )
    {
     printf( "$begin token is expected, got " );
     print8(line);
     printf( "\n" );
     exit(1);
    }

   reads( line, 1000, file );
   trim(line);
   strcpy( sentence, line );

   if( !AllowFuzzy && CompleteOnly && TopDown && !EnableTokenReconstruction )
    {
     int Flags = 0;
     if( CompleteOnly ) Flags |= SOL_GREN_COMPLETE_ONLY;
     //Flags |= SOL_GREN_TOPDOWN;

     HGREN_RESPACK hs = sol_MorphologyAnalysis8( hEngine, line, Flags, 0, 300000, LanguageID );
   
     if( hs==NULL )
      {
       printf( "Error has occured for sentence " );
       print8(sentence);
       printf( "\n" );
       exit(1);
      }

    sentence[0] = 0;
    const int nroot = sol_CountRoots(hs,0);

    for( int i=1; i<nroot-1; ++i )
     {
      if( i==0 )
       strcat( sentence, "~~BEGIN~~" );
      else if( i==nroot-1 )
       strcat( sentence, "|~~END~~" );
      else
       {
        if( sentence[0]!=0 )
         strcat( sentence, "|" );

        HGREN_TREENODE hNode = sol_GetRoot( hs, 0, i );
        char Buffer8[100];
        sol_GetNodeContents8( hNode, Buffer8 );
        strcat( sentence, Buffer8 );
       }
     }

     HLEMMAS hList = sol_LemmatizePhrase8( hLemm, sentence, 0, L'|' );
     if( hList!=NULL )
      {
       const int nlemma = sol_CountLemmas(hList);

       const int nroot = sol_CountRoots(hs,0);

       if( nroot-2 == nlemma )
        {
         printf( "[%d] ", sentence_count++ );
         print8(line);
         printf( "\n" );

         for( int i=1; i<nroot-1; ++i )
          {
           HGREN_TREENODE hNode = sol_GetRoot( hs, 0, i );
           const int EntryID = sol_GetNodeIEntry( hEngine, hNode );
           char required_lemma[100];
           sol_GetEntryName8( hEngine, EntryID, required_lemma );
           if( strcmp( required_lemma, "???" )==0 || strcmp( required_lemma, "unknownentry" )==0 || strcmp( required_lemma, "number_" )==0 )
            continue;

           char got_lemma[100];
           sol_GetLemmaString8( hList, i-1, got_lemma, sizeof(got_lemma) );

           total_word_count++;

           if( stricmp8(got_lemma,required_lemma)!=0 )
            {
             printf( "Mismatch: got=" );
             print8(got_lemma);
             printf( ", required=" );
             print8(required_lemma);
             printf( "\n" );

             fprintf( log_file, "\n%s\n", sentence );
             fprintf( log_file, "Mismatch: got=%s, required=%s\n", got_lemma, required_lemma );
             fflush(log_file);             

             n_err++;
            }
          }
        }
  
       sol_DeleteLemmas(hList);
      }

     sol_DeleteResPack(hs);
    }

   // пропускаем строки до токена $end
   while( !feof(file) )
   {
    reads( line, 1000, file );
    if( strncmp( line, "$end", 4 )==0 )
     break;
   }
  }

 fclose(file);
 fclose(log_file);
 
 printf( "Total number of words=%d\n", total_word_count );
 printf( "Number of mismatching lemmas=%d\n", n_err );
 printf( "Error ratio=%5.2f%%\n", float(n_err)*100.0F/float(total_word_count) );

 return;
}
#endif



int main( int argc, char* argv[] )
{
 int error_count=0;
 bool stop_on_first_error=false;
 
 FILE *out = fopen( "errors.txt", "wt" );
 if( out==NULL )
  {
   printf( "Can not open 'errors.txt' file for writing\n" );
   exit(1);     
  }

 const char *dict_path=NULL;

 bool check_model=false;
 const char *lemmas2_filename = "lemmas2.txt";
 const char *lemmas1_filename = "lemmas1.txt";
 const char *language = "russian";

 for( int i=1; i<argc; ++i )
  {
   if( strcmp( argv[i]+1, "dict" )==0 )
    dict_path = argv[++i];
   else if( strcmp( argv[i]+1, "file1" )==0 )
    lemmas1_filename = argv[++i];
   else if( strcmp( argv[i]+1, "file2" )==0 )
    lemmas2_filename = argv[++i];
   else if( strcmp( argv[i]+1, "stop_on_first_error" )==0 )
    stop_on_first_error=true;
   else if( strcmp( argv[i]+1, "language" )==0 )
    language = argv[++i];
   else if( strcmp( argv[i], "check_model" )==0 )
    check_model = true;
   else
    {
     printf( "Invalid option: %s\n", argv[i] );
     exit(1);
    }
  }
 
 if( dict_path==NULL )
  {
   #if defined _WIN32
    #if defined _M_X64
    dict_path = "..\\..\\..\\..\\..\\..\\bin-windows64\\lemmatizer.db";
    #else
    dict_path = "..\\..\\..\\..\\..\\..\\bin-windows\\lemmatizer.db";
    #endif
   #elif defined _DARWIN
    #if __WORDSIZE==64 || __SIZEOF_POINTER__==8 || __amd64__==1
    dict_path = "../../../../../../bin-mac64/lemmatizer.db";
    #else
    dict_path = "../../../../../../bin-mac/lemmatizer.db";
    #endif
   #else
    #if __WORDSIZE==64 || __SIZEOF_POINTER__==8 || __amd64__==1
    dict_path = "../../../../../../bin-linux64/lemmatizer.db";
    #else
    dict_path = "../../../../../../bin-linux/lemmatizer.db";
    #endif
   #endif
  }

 #if defined CHECK_MODEL
 if( check_model )
  {
   CheckModel(dict_path,lemmas1_filename,"e:\\MVoice\\lem\\tmp\\lemmatizer.log",language);
   return 0;
  }
 #endif


 for( int pass=0; pass<2 && error_count==0; pass++ )
  {
   int flags=0;
   switch(pass)
   {
    case 0: flags=LEME_DEFAULT; break;
    case 1: flags=LEME_FASTEST; break;
   }
   
   printf( "Loading the lemmatizator from %s\n", dict_path );

   HLEM hEngine = sol_LoadLemmatizatorA( dict_path, flags );

   if( hEngine==NULL )
    {
     printf( "Could not load the lemmatizator from %s\n", dict_path );
     exit(1);
    }

   char utf8[256];

   if( strcmp(language,"russian")==0 )
    {
     #if defined _WIN32 || defined _WINDOWS || defined __WIN32__ || defined WIN32
     // Проверим ASCII-версию функций лемматизации
     const char ascii0[]="\xEA\xEE\xF8\xEA\xEE\xFE";
     char ascii[32];
     int nlemA = sol_GetLemmaA( hEngine, ascii0, ascii, sizeof(ascii) );
     if( strcmp( ascii, "\xCA\xCE\xD8\xCA\xC0" )!=0 )
      {
       fprintf( stdout, "Lemmatization error: word=%s result=%s\n", ascii0, ascii );
       fflush(stdout);
       error_count++;
       if( stop_on_first_error ) exit(1);
      }
     #endif    
  
  
     // Проверим utf8-версию функций лемматизации
     const char *words[]={
     "ДНК-тестирование",
     "ДНК-тестированием",
     "языковыкручивающее",
     "абы кого",
     "абрикосовича",
     "аарона",
     "АББАТСТВА",
     "Горрилой",
     "кошками",
     "галактическою",
     "ужасен",
     "верифицировали",
     "воспроизведи",
     NULL
     };
  
 
     int i=0;
     while( words[i] )
      {
       const char *word = words[i];
       int nlem = sol_GetLemma8( hEngine, word, utf8, sizeof(utf8) );
  
       print8(word);
       printf( " -> " );
       print8(utf8);
       printf( "\n" );
  
       i++;
      }
  
     const char *words2[]={
     "ярко",
     "абы кого",
     "абстрактно",
     "роем",
     "простынь",
     NULL
     };
  
     i=0;
     while( words2[i] )
      {
       const char *word = words2[i];
       print8(word);
       printf( " --> " );
  
       HLEMMAS hList = sol_GetLemmas8( hEngine, word );
       if( hList!=NULL )
        {
         int nlemma = sol_CountLemmas(hList);
     
         for( int i=0; i<nlemma; ++i )
          {
           sol_GetLemmaString8( hList, i, utf8, sizeof(utf8) );
           print8(utf8);
           printf( " " );
          }
  
         sol_DeleteLemmas(hList);
         printf( "\n" );
        }
  
       i++;
      }
    }

   // Test the cases when a given word can be lemmatized producing 2 alternative lemmas.
   // These cases are few in comparison to 1-to-1 mapping cases.
   FILE *f2 = fopen( lemmas2_filename, "rt" );
   if( f2!=NULL )
    {
     char str[512];

     // Optionally skip the BOM
     fread( str, 3, 1, f2 );
     if( str[0]!=(char)0xef || str[1]!=(char)0xbb || str[2]!=(char)0xbf )
      fseek( f2, 0, SEEK_SET ); 
  

     int count=0;

     while( !feof(f2) )
      {
       memset( str, 0, sizeof(str) );
       if( fgets( str, 511, f2 )==NULL )
        break;

       int l = strlen(str);
       if( str[l-1]=='\n' ) str[l-1]=0;
       if( str[l-2]=='\r' ) str[l-2]=0;

       char * p1 = strchr( str, ';' );
       char * p2 = strrchr( str, ';' );

       std::string word( str, p1 );

       std::string lemma1( p1+1, p2 );
       std::string lemma2( p2+1 );

       HLEMMAS hList = sol_GetLemmas8( hEngine, word.c_str() );
       if( hList!=NULL )
        {
         int nlemma = sol_CountLemmas(hList);
   
         if( nlemma!=2 )
          {
           for( int q=0; q<2; ++q )
            {
             FILE *f = q==0 ? stdout : out;  
             fprintf( f, "Lemmatization error: word=" );
             fprint8( f, word.c_str() );
             fprintf( f, " results in %d lemmas, 2 are expected\n", nlemma );
             fflush(f);
            } 

           error_count++;
           if( stop_on_first_error ) exit(1);
           
           continue; 
          }


         bool match0=false, match1=false;

         for( int i=0; i<nlemma; ++i )
          {
           sol_GetLemmaString8( hList, i, utf8, sizeof(utf8) );

           if( lemma1==utf8 )
            {
             match0=true; 
            }
           else if( lemma2==utf8 )
            {
             match1=true;
            }
          }

         if( !match0 || !match1 )
          {
           for( int q=0; q<2; ++q )
            {
             FILE *f = q==0 ? stdout : out;  
             fprintf( f,"Incorrect lemmatization: word=" );
             fprint8(f,word.c_str());
             fprintf( f, " lemma=" );
             fprint8(f,utf8);

             fprintf( f, " must be[0]=" );
             fprint8( f, lemma1.c_str());

             fprintf( f, " must be[1]=" );
             fprint8( f, lemma2.c_str());

             fprintf( f, "\n" );
             fflush(f);
            }  

           error_count++;
           if( stop_on_first_error ) exit(1);
           continue; 
          }

         sol_DeleteLemmas(hList);
        }

       if( count && !(count%100) )
        printf( "%d words processed\n", count ); 

       count++;
      }

     fclose(f2); f2=NULL;
    }
   else
    {
     printf( "Can not open file %s\n", lemmas2_filename );
     exit(1);
    }


   // Test the lemmatization of words with with 1-to-1 mapping from lexeme to lemma.
   FILE *f = fopen( lemmas1_filename, "rt" );
   if( f!=NULL )
    {
     char str[512];
     int count=0;

     // Skip optionally BOM
     fread( str, 3, 1, f );
     if( str[0]!=(char)0xef || str[1]!=(char)0xbb || str[2]!=(char)0xbf )
      fseek( f, 0, SEEK_SET ); 

     while( !feof(f) )
      {
       memset( str, 0, sizeof(str) );
       if( fgets( str, 511, f )==NULL )
       break;

       int l = strlen(str);
       if( str[l-1]=='\n' ) str[l-1]=0;
       if( str[l-2]=='\r' ) str[l-2]=0;

       char * p1 = strchr( str, ';' );
       std::string word( str, p1 );
       std::string lemma( p1+1 );

       int nlem = sol_GetLemma8( hEngine, word.c_str(), utf8, sizeof(utf8) );

/*
     print8(word.c_str());
     printf( " -> " );
     print8(utf8);
     printf( "\n" );
*/
       if( count && !(count%1000) )
        printf( "%d words processed\n", count ); 

       count++;

       if( nlem!=1 )
        {
         for( int q=0; q<2; ++q )
          {
           FILE *f = q==0 ? stdout : out;  
           fprintf( f, "Lemmatization error: word=" );
           fprint8(f,word.c_str());
           fprintf( f, " results in %d lemmas, %d is expected\n", nlem, 1 );
           fflush(f);
          }
          
         error_count++;
         if( stop_on_first_error ) exit(1);
         continue; 
        }

       if( strcmp( utf8, lemma.c_str() )!=0 )
        {
         for( int q=0; q<2; ++q )
          {
           FILE *f = q==0 ? stdout : out;  
           fprintf( f,"Incorrect lemmatization: word=" );
           fprint8(f,word.c_str());
           fprintf( f," lemma=" );
           fprint8(f,utf8);
           fprintf( f," mustbe=" );
           fprint8(f,lemma.c_str()); 
           fprintf( f, "\n" );
           fflush(f);
          }
           
         error_count++;
         if( stop_on_first_error ) exit(1);
         continue; 
        }
      }

     fclose(f); f=NULL;
    }
   else
    {
     printf( "Can not open file %s\n", lemmas1_filename );
     exit(1);
    }

   sol_DeleteLemmatizator(hEngine);
  }

 if( error_count==0 )
  {
   printf( "No errors detected\n" );
  }
 else
  {
   if( error_count==1 )
    printf( "There is 1 error\n" );
   else
    printf( "There are %d errors\n", error_count );
  } 

 fclose( out );

 return 0;
}
