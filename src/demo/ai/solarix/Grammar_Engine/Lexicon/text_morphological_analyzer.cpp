#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#if !defined(WIN32)
#include <errno.h>
#endif
#include "../../../../../include/lem/solarix/solarix_grammar_engine.h"
#include "../../../../../include/lem/solarix/_sg_api.h"


extern void print8( const char *utf8 );
extern void failed( HGREN hEngine );
extern void failed( HGREN hEngine, const char * SentenceUTF8 );
extern void PrintGraph( HGREN_RESPACK hPack, int igraf );
extern void PrintGraphs( HGREN_RESPACK hPack );
extern int strcmp_sp( const char *s1, const char *s2 );



// При выполнении анализа предложения sentence_utf8 случилась ошибка, возможно
// несовпадение с эталонными результатами. Выведем предложение и контекст.
static void PrintAnalysisContext( const char *sentence_utf8, HGREN_RESPACK hs )
{
 printf( "\n----------- CONTEXT: ----------------\n\n" );
 printf( "Sentence: " );
 print8( sentence_utf8 );
 printf( "\nAnalysis results:\n" );
 PrintGraphs( hs );
 printf( "\n" ); 
 return;
}



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

// Remove the spaces at the beginning and enging of string.
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


static void read_it( FILE *file, const char *expected_line )
{
 char line[1000];
 reads( line, sizeof(line), file );
 trim(line);
 if( strcmp(line,expected_line)!=0 )
  {
   printf( "Error: " );
   print8( expected_line );
   printf( " is expected, but " );
   print8( line );
   printf( " is read from file\n" );
   exit(1);
  }

 return;
}



// Строку типа AAA | BBB | CCC разбираем на подстроки AAA, BBB и CCC, возвращая
// их в виде списка. Символ-разделитель всегда вертикальная черта.
static void SplitChecker( const char *str, std::vector<std::string> &parts )
{
 int i=0;
 std::string accum;
 while( str[i]!=0 )
  {
   accum.clear();

   while( str[i]!=0 )
    {
     char c = str[i++];
     if( c=='|' )
      {
       parts.push_back(accum);
       accum.clear();
      }
     else
      {
       accum += c;
      }
    }
  }

 if( !accum.empty() )
  {
   parts.push_back(accum);
  }

 return;
}



static FILE * OperErrorFile(void)
{
 FILE *ofile = fopen( "morphological-errors.txt", "wt" );

 if( ofile==NULL )
  {
   printf( "Can not open file morphological-errors.txt\n" );
   exit(1);
  }

 return ofile;
}

#define OPEN_ERRORS_FILE if(ofile==NULL) ofile=OperErrorFile()

static FILE *ofile=NULL;

static int CheckNode( HGREN hEngine, HGREN_TREENODE hNode, const char *line, bool write_errors, bool stop_on_error, const char *sentence_utf8, HGREN_RESPACK hs )
{
 int nerr=0;

 char Buffer8[100], Class8[100]; 

 sol_GetNodeContents8( hNode, Buffer8 );

 // Ищем символ-разделитель лексемы и граммемы. Чтобы корректно обрабатывать случай, когда в предложении есть !, проверяем
 // со второго символа.
 bool must_be_only_1 = false;
 const char *ptr_coords = strchr( line+1, '@' );
 if( ptr_coords==NULL )
  {
   ptr_coords = strchr( line+1, '!' );
   must_be_only_1 = true;
  }

 if( ptr_coords==NULL )
  {
   failed(hEngine,sentence_utf8);
   if( write_errors )
    {
     printf( "Can not extract first token from line " );
     print8(line);
     printf( "\n" );

     if( stop_on_error )
      exit(1);
    }
   else
    {
     if( stop_on_error )
      exit(1);
    }

   return 1;
  } 

// std::string tok0( line, ptr_coords );
 std::string tok0;
 for( const char* tok0_str=line; tok0_str!=ptr_coords; ++tok0_str )
  tok0 += *tok0_str;
  

 if( strncmp(Buffer8,"' ",2)==0 )
  {
   strcpy( Buffer8, Buffer8+1 );
   Buffer8[0]='\'';
  } 
 
 if( strcmp_sp( Buffer8, tok0.c_str() )!=0 )
  {
   failed(hEngine);
   if( write_errors )
    {
     printf( "Incorrect token: got [" );
     print8(Buffer8);
     printf( "], expected [" );
     print8(tok0.c_str());
     printf( "]\n" );

     PrintAnalysisContext( sentence_utf8, hs );
     nerr++;

     if( stop_on_error )
      exit(1);
    }
   else
    {
     exit(1);
    }
  }

 ptr_coords++;

 // Если для разделения токена и координат использован символ '!', то словоформа должна иметь только 1 версию.
 if( must_be_only_1 )
  {
   int n_ver = sol_GetNodeVersionCount( hEngine, hNode );
   if( n_ver!=1 )
    {
     nerr++;
     failed(hEngine);
     if( write_errors )
      {
       printf( "Word [" );
       print8(Buffer8);
       printf( "] has %d versions, whereas only 1 is expected.\n", n_ver );
       PrintAnalysisContext( sentence_utf8, hs );

       if( stop_on_error )
        exit(1);
      }
     else
      {
       if( stop_on_error )
        exit(1);
      }
    }
  }
 

 // от ptr_coords до терминатора идет список эталонных координат и название части речи. Кроме того,
 // может быть задано множество альтернативных наборов, разделенных символом |
 std::vector<std::string> coords_parts;
 SplitChecker( ptr_coords, coords_parts );

 bool any_matched=false;
 int n_parts = coords_parts.size();

 for( int ipart=0; ipart<n_parts; ++ipart )
  {
   std::vector<std::string> toks;
   bool part_matched=true;

   const char *ptr1 = coords_parts[ipart].c_str();

   while( ptr1!=NULL )
    {
     const char *ptr2 = strchr(ptr1,' ');
     if( ptr2==NULL )
      {
       if( *ptr1!=0 )
        {
         std::string tok(ptr1);
         if( !tok.empty() ) 
          toks.push_back(tok);
        }
 
       break;
      }
     else
      {
       std::string tok(ptr1,ptr2);
 
       if( !tok.empty() ) 
        toks.push_back(tok);
 
       ptr1 = ptr2+1;
      }
    }
 
   if( toks.empty() )
    {
     failed(hEngine);
     if( write_errors )
      {
       printf( "Could not split the line [%s] to tokens\n", line );
       exit(1);
      }
     else
      {
       exit(1);
      }
    }
 
   if( toks.size()>0 )
    {     
     const int EntryID = sol_GetNodeIEntry( hEngine, hNode );
     const int PartOfSpeechID = sol_GetEntryClass( hEngine, EntryID );
 
     if( toks[0]!="*" )
      {
       const int ExpectedPartOfSpeechID = sol_FindClass8( hEngine, toks[0].c_str() );
       if( ExpectedPartOfSpeechID==-1 )
        {
         failed(hEngine);
         if( write_errors )
          {
           printf( "Unknown part of speech name: " ); print8(toks[0].c_str()); printf( "\n" );
           exit(1);
          }
         else
          {
           exit(1);
          }
        }
 
       if( PartOfSpeechID!=ExpectedPartOfSpeechID )
        {
         if( n_parts==1 || ipart==n_parts-1 )
          {
           failed(hEngine);
           printf( "Error - part of speech mismatch for word [" );
           print8( tok0.c_str() );
           printf( "]," );
           print8( toks[0].c_str()); printf( " is expected, whereas " );
           sol_GetClassName8(hEngine,PartOfSpeechID,Class8);
           print8(Class8);
           printf(" is extracted\n");

           PrintAnalysisContext( sentence_utf8, hs );

           if( stop_on_error )
            exit(1);

           nerr++;
          }
         else
          {
           part_matched = false;
           continue;
          }
        }
      }
 
     for( int idim=1; idim<toks.size(); ++idim )
      {
       const std::string &dim = toks[idim];

       std::string coord_name;
       std::string state_name;
       int bistable_state=-1;

       if( dim[0]=='~' )
        {
         coord_name = std::string( dim.c_str()+1 );
         bistable_state=0;
        }
       else
        {
         const char * pos3 = strchr( dim.c_str(), ':' );
         if( pos3==NULL )
          {
           // учтем вариант, когда указано имя бистабильной координаты - это имплицитно подразумевает состояние 1.
           const int id_coord = sol_FindEnum8(hEngine,dim.c_str());
           if( id_coord!=-1 )
            {
             coord_name = dim;
             int nstates = sol_CountCoordStates( hEngine, id_coord );
             if( nstates==0 )
              {
               bistable_state = 1;
              }
            }

           if( bistable_state!=1 )
            {
             failed(hEngine);
             if( write_errors )
              {
               printf( "Can not parse " );
               print8(dim.c_str());
               printf( "\n" );
               printf( "Line: " );
               print8(line);
               exit(1);
              }
             else
              {
               exit(1);
              }
            }
          }
         else
          {
           coord_name = std::string( dim.c_str(), pos3 );
           state_name = std::string( pos3+1 );
          }
        }
 
 
       const int CategoryID = sol_FindEnum8(hEngine,coord_name.c_str());
       if( CategoryID==-1 )
        {
         failed(hEngine);
 
         if( write_errors )
          {
           printf( "Could not find grammatical category " );
           print8( coord_name.c_str() );
           printf( "\n" );
           exit(1);
          }
         else
          {
           exit(1);
          }
        }
 
       const int StateID = bistable_state==-1 ? sol_FindEnumState8(hEngine,CategoryID,state_name.c_str()) : bistable_state;
       if( StateID==-1 )
        {
         failed(hEngine);
         if( write_errors )
          {
           printf( "Could not find grammatical attribute " );
           print8( state_name.c_str() );
           printf( "\n" );
           exit(1);
          }
         else
          {
           exit(1);
          }
        }          
 
       bool state_matched=false;

       if( bistable_state==0 )
        {
         // для бистабильных координат проверка происходит иначе, чем для обычных.
         // если требуется состояние 1, то ищем такое состояние.
         // если требуется состояние 0, то координатная пара должна либо вообще отсутствовать, либо иметь состояние 0.
         int found_state = sol_GetNodeCoordState( hNode, CategoryID );
         if( found_state==1 )
          {
           state_matched = false;
          }
         else
          {
           state_matched = true;
          }
        }
       else
        {
         int ip = sol_GetNodeCoordPair( hNode, CategoryID, StateID );
         state_matched = ip==1;
        }

       if( !state_matched )
        {
         if( n_parts==1 || ipart==n_parts-1 )
          {
           if( write_errors )
            {
             printf( "Error in sentence:\n" );
             print8(sentence_utf8);
             printf( "\nNode [ " );
             print8(Buffer8);
             printf( " ] does not contain the grammatical attribute " );
             print8( coord_name.c_str() );
             printf( ":" );
             print8( state_name.c_str() );
             printf( "\n" );
          
             OPEN_ERRORS_FILE;
             fprintf( ofile, "%s\n", sentence_utf8 );
             nerr++;

             if( stop_on_error )
              exit(1);
            }
          }
         else
          {
           part_matched = false;
           break;
          }
        }
      }
    }

   if( part_matched )
    {
     any_matched = true;
     break;
    }
  }

 if( n_parts>1 && !any_matched )
  {
   if( write_errors )
    {
     printf( "Error in sentence:\n" );
     print8(sentence_utf8);
     printf( "\nNode " );
     print8(Buffer8);
     printf( " does not match alternatives in " );
     print8( ptr_coords );
     printf( "\n" );
   
     OPEN_ERRORS_FILE;
     fprintf( ofile, "%s\n", sentence_utf8 );

     if( stop_on_error )
      exit(1);
    }

   nerr++;
  }

 return nerr;
}


struct TreeTopologyCheckResult
{
 bool matched;
 int n_error;

 TreeTopologyCheckResult() : matched(false), n_error(0) {}
};


static int CheckTree( HGREN hEngine, HGREN_TREENODE hNode, FILE *file, bool write_errors, bool stop_on_error, const char *sentence_utf8, HGREN_RESPACK hs )
{
 int nerr=0;
 char line[1000];
 reads( line, 1000, file );
 trim(line);

 nerr = CheckNode( hEngine, hNode, line, write_errors, stop_on_error, sentence_utf8, hs );

 if( nerr==0 )
  {
   int nleaf = sol_CountLeafs( hNode );
   if( nleaf>0 )
    {
     read_it( file, "(" );

     for( int i=0; i<nleaf; i++ )
      {
       nerr += CheckTree( hEngine, sol_GetLeaf( hNode, i ), file, write_errors, stop_on_error, sentence_utf8, hs );
      }

     read_it( file, ")" );
    }
  }

 return nerr;
}




void TestMorphologicalAnalyzer( HGREN hEngine, int id_language, int default_beam_size, const char *filename, bool write_errors, bool use_model, int thread_no )
{
 FILE *file = fopen( filename, "rt" );

 if( file==NULL )
  {
   printf( "Can not open file %s\n", filename );
   exit(1);
  }

 if( write_errors )
  ofile = NULL;

 char line[1000], sentence[1000];

 int nerr=0, sentence_count=0, word_count=0;
 time_t start_time;
 time(&start_time);

 bool stop_on_error = !use_model;

 // Optionally skip the BOM
 fread( line, 3, 1, file );
 if( line[0]!=(char)0xef || line[1]!=(char)0xbb || line[2]!=(char)0xbf )
  fseek( file, 0, SEEK_SET ); 

 bool AllowFuzzy=false;
 bool CompleteOnly=true;
 bool EnableFilters=true; // по умолчанию фильтры включены
 bool EnableTokenReconstruction=false;
 bool EnableSparse=false;
 int max_alt=default_beam_size;

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
       CompleteOnly=false;
       EnableSparse=false;
      }     
     else if( memcmp( line, "#disallow_incomplete", 20 )==0 )
      {
       CompleteOnly=true;
       EnableSparse=false;
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

     continue;
    }

   if( strncmp( line, "$begin", 6 )!=0 )
    {
     failed(hEngine);

     if( write_errors )
      {
       printf( "$begin token is expected, got " );
       print8(line);
       printf( "\n" );

       if( stop_on_error )
        exit(1);
       else
        {
         while( !feof(file) )
         {
          reads( line, 1000, file );
          if( strncmp( line, "$begin", 6 )==0 )
           {
            break;
           }
         }
        }
      }
     else
      {
       break;
      }
    }

   reads( line, 1000, file );
   trim(line);
   strcpy( sentence, line );

   sentence_count++;

   if( write_errors || use_model )
    {
     printf( "[%d] ", sentence_count );
     print8(line); printf( "\n" );
    }
   else
    {
     printf( "(%d:%d)", thread_no, sentence_count );
     fflush(stdout);
    }
   
   int Flags = 0;
   if( AllowFuzzy ) Flags |= SOL_GREN_ALLOW_FUZZY;
   if( CompleteOnly ) Flags |= SOL_GREN_COMPLETE_ONLY;

  
   if( !EnableFilters ) Flags |= SOL_GREN_DISABLE_FILTERS;

   if( use_model )
    Flags |= SOL_GREN_MODEL;


   int Constraints=0;
   if( max_alt!=0 )
    {
     Constraints = max_alt<<22;
    }

   HGREN_RESPACK hs = sol_MorphologyAnalysis8( hEngine, line, Flags, 0, Constraints, id_language );
   
   if( hs==NULL )
    {
     failed(hEngine);

     if( write_errors )
      {
       printf( "Error has occured for sentence " );
       print8(sentence);
       printf( "\n" );
       exit(1);
      }
     else
      {
       continue;
      }
    }

   const int nroot = sol_CountRoots(hs,0);

   for( int i=1; i<nroot-1; ++i )
    {
     HGREN_TREENODE hNode = sol_GetRoot( hs, 0, i );
     reads( line, 1000, file );
     nerr += CheckNode( hEngine, hNode, line, write_errors, !use_model, sentence, hs );
     word_count++;
    }

   sol_DeleteResPack(hs);

   reads( line, 1000, file );
   if( strncmp( line, "$end", 4 )!=0 )
    {
     failed(hEngine);
     if( write_errors )
      {
       printf( "$end token is expected, got " );
       print8(line);
       printf( "\n" );

       if( stop_on_error )
        exit(1);
       else
        {
         while( !feof(file) )
         {
          reads( line, 1000, file );
          if( strncmp( line, "$end", 4 )==0 )
           {
            break;
           }
         }
        }
      }
     else
      {
       exit(1);
      }
    }
  }

 fclose(file);

 if( write_errors && ofile!=NULL )
  fclose(ofile);

 if( (nerr>0 && write_errors) || use_model )
  {
   printf( "There are %d error(s) in morphological analysis\n", nerr );

   if( use_model )
    printf( "Word count=%d\n", word_count );

   if( nerr>0 )
    exit(1);
  }

 if( write_errors )
  {
   printf( "\n-------------------------------------------------\nNumber of sentences: %d\n", sentence_count );
   time_t finish_time;
   time(&finish_time);
   double elapsed = difftime( finish_time, start_time );
   printf( "Elapsed time: %f sec\n", elapsed );
  }

 return;
}



static FILE* OpenSyntaxErrors()
{
 FILE *failed_syntax = fopen( "failed_syntax.txt", "wt" );

 if( failed_syntax==NULL )
  {
   fprintf( stderr, "Can not open file 'failed_syntax.txt' for writing\n" );
   exit(1);
  }
 
 return failed_syntax;
}



#define OPEN_SYNTAX_ERRORS if(failed_syntax==NULL) failed_syntax=OpenSyntaxErrors()

void TestSyntacticAnalyzer( HGREN hEngine, int id_language, int default_beam_size, const char *filename, bool write_errors, int thread_no )
{
 FILE *file = fopen( filename, "rb" );

 if( file==NULL )
  {
   printf( "Can not open file %s\n", filename );
   exit(1);
  }

 FILE *failed_syntax = NULL;

 char sentence[1000];
 char line[1000];

 time_t start_time;
 time(&start_time);

 int sentence_count=0, nfailed_syntax=0, nsucceeded_syntax=0;

 const int lexlen = sol_MaxLexemLen(hEngine);
 wchar_t *Buffer = new wchar_t[lexlen+1];

 char Buffer8[100], mustbe_root[100];

 // Optionally skip the BOM
 fread( line, 3, 1, file );
 if( line[0]!=(char)0xef || line[1]!=(char)0xbb || line[2]!=(char)0xbf )
  fseek( file, 0, SEEK_SET ); 

 bool AllowFuzzy = false;
 bool CompleteOnly=true;
 bool EnableFilters=true;
 int line_count=0;
 bool EnableTokenReconstruction=false;
 bool EnableSparse=false;
 int max_alt=default_beam_size;

 while( !feof(file) )
  {
   *line=0;
   reads( line, 1000, file );
   line_count++;

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
       CompleteOnly=false;
      }
     else if( memcmp( line, "#disallow_incomplete", 20 )==0 )
      {
       CompleteOnly=true;
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
     else if( memcmp( line, "#maxalt", 7 )==0 )
      {
       errno=0;
       max_alt = atoi(line+8);
       printf( "MAXALT=%d\n", max_alt );
      }

     continue;
    }

   if( strncmp( line, "$begin", 6 )!=0 )
    {
     failed(hEngine);

     if( write_errors )
      {
       printf( "$begin token is expected, got " );
       print8(line);
       printf( "\n" );
       exit(1);
      }
     else
      {
       break;
      }
    }

   reads( line, 1000, file );
   trim(line);
   strcpy( sentence, line );

   sentence_count++;

   bool reorder_tree=false;

   if( write_errors )
    {
     printf( "\n[%d] ", sentence_count );
     print8(sentence);
     printf( "\n" );
    }
   else
    {
     printf( "[%d:%d]", thread_no, sentence_count );
     fflush(stdout);
    }


   // опционально может быть указан требуемый корневой узел, точнее его текстовое содержимое
   int required_number_of_roots=3; // по умолчанию требует 3 корвенвых узла, то есть завершенный анализ
   long beg0 = ftell(file);
   reads( line, 1000, file );
   if( memcmp( line, "@root=", 6 )==0 )
    {
     strcpy( mustbe_root, line+6 );
    }
   else
    {
     *mustbe_root=0;

     if( memcmp(line, "@nroot=", 7)==0 )
      {
       required_number_of_roots = atoi( line+7 );
      }
     else if( memcmp(line, "@reorder_tree", 13)==0 )
      {
       reorder_tree=true;
      }
     else
      {
       fseek( file, beg0, SEEK_SET );
      }
    }

   int MorphologicalFlags = 0;
   int SyntacticFlags = 0;

   if( AllowFuzzy ) MorphologicalFlags |= SOL_GREN_ALLOW_FUZZY;
   if( !EnableFilters ) MorphologicalFlags |= SOL_GREN_DISABLE_FILTERS;
   if( CompleteOnly ) MorphologicalFlags |= SOL_GREN_COMPLETE_ONLY;

   if( reorder_tree )
    SyntacticFlags |= SOL_GREN_REORDER_TREE;

   int Constraints=0;
   if( max_alt!=0 )
    {
     Constraints = max_alt<<22;
    }

   HGREN_RESPACK hPack = sol_SyntaxAnalysis8( hEngine, sentence, MorphologicalFlags, SyntacticFlags, Constraints, id_language );

   // сбрасываем ограничение max_alt, чтобы следующее предложение по умолчанию работало без ограничений
   max_alt=default_beam_size;

   if( hPack==NULL )
    {
     nfailed_syntax++;

     OPEN_SYNTAX_ERRORS;
     fprintf( failed_syntax, "%s", line );

     if( write_errors )
      printf( "ERROR: syntax analysis has failed\n" );

     failed(hEngine);
    }
   else
    {
     const int ngrafs = sol_CountGrafs(hPack);

     if( ngrafs==0 )
      {
       nfailed_syntax++;

       OPEN_SYNTAX_ERRORS;
       fprintf( failed_syntax, "%s", line );

       if( write_errors )
        printf( "ERROR: syntax analysis has failed\n" );

       failed(hEngine);
      }
     else
      {
       // Выберем среди результатов альтернативу с минимальным количеством корневых
       // узлов. Два узла присутствуют в каждой альтернативе - это метки начала $BEGIN$
       // и конца $END$. В случае полностью успешного анализа альтернатива имеет 3
       // корневых узла - средний узел представляет из себя искомое синтаксическое дерево.

       int imin_graf=-1, minv=1000000;
       for( int i=0; i<ngrafs; i++ )
        {
         const int nroots = sol_CountRoots(hPack,i);
         if( nroots<minv ) 
          {
           minv = nroots;
           imin_graf = i; 
          }  
        }

       if( write_errors )
        {
         if( imin_graf!=-1 )
          {
           // Наиболее компактный граф содержит minv узлов верхнего уровня.
           // Распечатаем содержимое этого графа.
           PrintGraph( hPack, imin_graf );
          }
        }

       if( minv!=required_number_of_roots )
        {
         // Для тестирования обработки очень больших предложений можно вообще задавать только предложение в скобках $begin/$end. Тогда
         // мы проверим, что есть хотя бы одно ребро, и все.

         long back_pos = ftell(file);
         *line=0;
         reads( line, 1000, file );
         trim(line);
         fseek(file,back_pos,SEEK_SET);

         if( strcmp(line,"$end")==0 )
          {
           int edge_count=0;

           const int nroot = sol_CountRoots(hPack, imin_graf);
           for( int i=1; i<nroot-1; ++i )
            {
             HGREN_TREENODE hNode = sol_GetRoot( hPack, imin_graf, i );
             edge_count += sol_CountLeafs( hNode );
            }

           if( edge_count==0 )
            {
             nfailed_syntax++;

             OPEN_SYNTAX_ERRORS;
             fprintf( failed_syntax, "%s", line );
        
             if( write_errors )
              {
               printf( "ERROR: syntax analysis has failed. At least one edge is expected.\n" );
               failed(hEngine);
              }
            }
          }
         else
          {
           nfailed_syntax++;
        
           OPEN_SYNTAX_ERRORS;
           fprintf( failed_syntax, "%s", line );
        
           if( write_errors )
            {
             printf( "ERROR: syntax analysis has failed\n" );
             failed(hEngine);
            }
          }
        }
       else
        {
         // Если тестовое предложение содержало указание на правильный корень графа,
         // то проверим это.
         bool ok=true;
         if( strlen(mustbe_root)>0 )
          {
           HGREN_TREENODE hNode = sol_GetRoot( hPack, imin_graf, 1 );
           sol_GetNodeContents8( hNode, Buffer8 );

           if( strcmp_sp( mustbe_root, Buffer8 )!=0 )
            {
             nfailed_syntax++;
             ok = false;
        
             OPEN_SYNTAX_ERRORS;
             fprintf( failed_syntax, "%s", line );
        
             if( write_errors )
              {
               printf( "ERROR: mismatching root node, expecting " );
               print8(mustbe_root);
               printf( ", got " );
               print8( Buffer8 );
               printf( "\n" );

               failed(hEngine);
              }
            }
          }

         // Может быть задано описание всей структуры синтаксического дерева - каждого узла
         if(ok)
          {
           long back_pos = ftell(file);
           *line=0;
           reads( line, 1000, file );
           trim(line);
           if( strcmp(line,"@tree=")==0 )
            {
             fseek( file, back_pos, SEEK_SET );
             const int nroot = sol_CountRoots(hPack, imin_graf);
  
             for( int i=1; i<nroot-1; ++i )
              {
               read_it( file, "@tree=" );

               HGREN_TREENODE hNode = sol_GetRoot( hPack, imin_graf, i );
               int err = CheckTree( hEngine, hNode, file, write_errors, true, sentence, hPack );
               if( err!=0 )
                {
                 ok=false;
                 break;
                }
              }
            }
           else
            {
             int rc = fseek( file, back_pos, SEEK_SET );
             if( rc!=0 )
              {
               printf( "Internal error on line %d: fseek has failed\n", __LINE__-3 );
               exit(-1);
              }
            }
          }        

         if( ok )
          nsucceeded_syntax++;
        }
      }
   
     sol_DeleteResPack( hPack );
    }

   reads( line, 1000, file );
   if( strncmp( line, "$end", 4 )!=0 )
    {
     failed(hEngine);
     if( write_errors )
      {
       printf( "$end token is expected, got " );
       print8(line);
       printf( "\n" );
       exit(1);
      }
     else
      break;
    }

   if( write_errors && nfailed_syntax>0 )
    printf( "%d succeeded, %d failed so far.\n", nsucceeded_syntax, nfailed_syntax );
  }

 fclose(file);

 if( failed_syntax!=NULL )
  fclose(failed_syntax);

 delete[] Buffer;

 if( nfailed_syntax>0 && write_errors )
  {
   printf( "There are %d error(s) in syntax analysis\n", nfailed_syntax );
   exit(1);
  }

 if( write_errors )
  {
   printf( "\n-------------------------------------------------\nNumber of sentences: %d\n", sentence_count );

   time_t finish_time;
   time(&finish_time);
   double elapsed = difftime( finish_time, start_time );
   printf( "Elapsed time: %f sec\n", elapsed );
  }

 return;
}



void TestSegmenter( HGREN hEngine, int id_language, const char *filename, bool write_errors, int thread_no )
{
 FILE *file = fopen( filename, "rb" );

 if( file==NULL )
  {
   printf( "Can not open file %s\n", filename );
   exit(1);
  }

 FILE *failed_syntax = NULL;

 char line[1000];

 time_t start_time;
 time(&start_time);

 int nfailed=0, nsucceeded=0;

 // Optionally skip the BOM
 fread( line, 3, 1, file );
 if( line[0]!=(char)0xef || line[1]!=(char)0xbb || line[2]!=(char)0xbf )
  fseek( file, 0, SEEK_SET ); 

 int sentence_count=0;
 int text_count=0;

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

     continue;
    }

   if( strncmp( line, "$begin", 6 )!=0 )
    {
     failed(hEngine);

     if( write_errors )
      {
       printf( "$begin token is expected, got " );
       print8(line);
       printf( "\n" );
       exit(1);
      }
     else
      {
       break;
      }
    }

   // Читаем текст построчно, пока не встретится строка с $sentences
   std::string text;
   while( !feof(file) )
    {
     reads( line, 1000, file );
     if( strcmp( line, "$sentences" )==0 )
      break;

     if( !text.empty() )
      text += "\n";

     text += line;
    }

   text_count++;

   // Для текста в std::string инициализируем сегментатор.
   HGREN_SBROKER hBroker = sol_CreateSentenceBrokerMem8( hEngine, text.c_str(), id_language );

   if( !hBroker )
    failed(hEngine);

   while(true)
    {
     int rc = sol_FetchSentence( hBroker );
     if( rc==-1 )
      {
       // больше предложений нет.
       reads( line, 1000, file );
       trim(line);
       if( strcmp( line, "$end" )!=0 )
        {
         if( write_errors )
          {
           printf( "Incorrect segmentation for text:\n" );
           print8(text.c_str());
           exit(1);
          }

         failed(hEngine);
         nfailed++;
        }
       
       break;
      }
     else if( rc==-2 )
      {
       failed(hEngine);
       exit(1);
      }
   
     sentence_count++;

     int sentence_len = sol_GetFetchedSentenceLen(hBroker)*6+1;
     char *sentence_buf = new char[ sentence_len ];
     sol_GetFetchedSentence8( hBroker, sentence_buf );

     if( write_errors )
      {
       print8(sentence_buf);
       printf( "\n" );
      }

     reads( line, 1000, file );
     trim(line);

     if( strcmp( sentence_buf, line )!=0 )
      {
       if( write_errors )
        {
         printf( "\nInvalid segmentation, expected:\n\n" );
         print8(line);
         printf( "\n\nextracted:\n\n" );
         print8(sentence_buf);
         printf( "\n\n" );
        }

       failed(hEngine);
       break;
      }

     delete[] sentence_buf;
    }

   sol_DeleteSentenceBroker(hBroker);
  }

 fclose(file);


 if( nfailed>0 && write_errors )
  {
   printf( "There are %d segmentation error(s)\n", nfailed );
   exit(1);
  }

 if( write_errors )
  {
   printf( "%d text chunks, %d sentence have been processed\n", text_count, sentence_count );
  }

 return;
}



void TestSyllabicBreaks( HGREN hEngine, int id_language, const char *filename, bool write_errors, int thread_no )
{
 FILE *file = fopen( filename, "rb" );

 if( file==NULL )
  {
   printf( "Can not open file %s\n", filename );
   exit(1);
  }

 FILE *failed_syntax = NULL;

 char sentence[1000];
 char line[1000];

 time_t start_time;
 time(&start_time);

 int word_count=0, nfailed_syllabs=0;
 char syllabs_buffer[200];

 // Optionally skip the BOM
 fread( line, 3, 1, file );
 if( line[0]!=(char)0xef || line[1]!=(char)0xbb || line[2]!=(char)0xbf )
  fseek( file, 0, SEEK_SET ); 

 int line_count=0;

 while( !feof(file) )
  {
   *line=0;
   reads( line, 1000, file );
   line_count++;

   trim(line);

   if( strlen(line)==0 )
    continue;

   if( line[0]=='#' )
    {
     if( memcmp( line, "#exit", 5 )==0 )
      break;

     continue;
    }

   if( strncmp( line, "$begin", 6 )!=0 )
    {
     failed(hEngine);

     if( write_errors )
      {
       printf( "$begin token is expected, got " );
       print8(line);
       printf( "\n" );
       exit(1);
      }
     else
      {
       break;
      }
    }

   reads( line, 1000, file );
   trim(line);
   strcpy( sentence, line );

   word_count++;

   if( write_errors )
    {
     printf( "\n" );
     print8(sentence);
     printf( "\n" );
    }
   else
    {
     printf( "(%d:%d)", thread_no, word_count );
     fflush(stdout);
    }

   // эталонная разбивка, символ + в качестве разделителя слогов
   reads( line, 1000, file );

   sol_Syllabs8( hEngine, sentence, '+', syllabs_buffer, id_language );

   if( strcmp( syllabs_buffer, line )!=0 )    
    {
     failed(hEngine);
    }

   reads( line, 1000, file );
   if( strncmp( line, "$end", 4 )!=0 )
    {
     failed(hEngine);
     if( write_errors )
      {
       printf( "$end token is expected, got " );
       print8(line);
       printf( "\n" );
       exit(1);
      }
     else
      break;
    }
  }

 fclose(file);

 if( failed_syntax!=NULL )
  fclose(failed_syntax);

 if( nfailed_syllabs>0 && write_errors )
  {
   printf( "There are %d error(s) in syllabic breaks\n", nfailed_syllabs );
   exit(1);
  }

 if( write_errors )
  {
   printf( "\n-------------------------------------------------\nNumber of words: %d\n", word_count );

   time_t finish_time;
   time(&finish_time);
   double elapsed = difftime( finish_time, start_time );
   printf( "Elapsed time: %f sec\n", elapsed );
  }

 return;
}
