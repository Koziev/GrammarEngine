#include <stdio.h>
#include <string.h>

#if defined WIN32
#include <windows.h>
#endif

#include "../../../../../include/lem/solarix/solarix_grammar_engine.h"
#include "../../../../../include/lem/solarix/_sg_api.h"

#if defined WIN32
void wide( FILE *f, const wchar_t *ustr )
{
 const int l = wcslen(ustr);
 char *abuffer = new char[l*6+1];
 memset( abuffer, 0, l*6+1 );
 WideCharToMultiByte( CP_OEMCP, 0, ustr, l+1, abuffer, l*6+1, NULL, NULL );
 fprintf( f, "%s", abuffer );
 fflush(f);
 delete[] abuffer;
 return;
}
#endif


void PrintNode( FILE * out, HGREN hEngine, HGREN_RESPACK hPack, HGREN_TREENODE hNode )
{
 #if defined WIN32
 wchar_t word[32];
 memset( word, 0, sizeof(word) );
 sol_GetNodeContents( hNode, word );

 if( wcschr( word, L' ' )!=NULL )
  {
   wide(out,L"[");
   wide(out,word);
   wide(out,L"]");
  }
 else
  {
   wide(out,word);
  }
 #else
 char word[100];
 memset( word, 0, sizeof(word) );
 sol_GetNodeContents8( hNode, word );

 if( strchr( word, ' ' )!=NULL )
  {
   fprintf(out,"[");
   fprintf(out,"%s",word);
   fprintf(out,"]");
  }
 else
  {
   fprintf(out,"%s",word);
  }
 #endif
 
 int nleaf = sol_CountLeafs( hNode );
 if( nleaf>0 )
  {
   fprintf( out, "(" );

   for( int i=0; i<nleaf; i++ )
    {
     fprintf( out, " " );
     PrintNode( out, hEngine, hPack, sol_GetLeaf( hNode, i ) );
    }

   fprintf( out, " )" );
  }

 return;
}



void PrintGraph( FILE * out, HGREN hEngine, HGREN_RESPACK hPack, int igraf )
{
 int nroot = sol_CountRoots( hPack, igraf );
 
 for( int i=1; i<nroot-1; i++ )
  {
   PrintNode( out, hEngine, hPack, sol_GetRoot(hPack,igraf,i) ); 
   fprintf( out, " " );
  }

 return;
}


void PrintSyntaxTrees( FILE * out, HGREN hEngine, HGREN_RESPACK hPack )
{
 if( hPack!=NULL )
  {
   const int ngrafs = sol_CountGrafs(hPack);

   if( ngrafs>0 )
    PrintGraph( out, hEngine, hPack, 0 );
  }
 
 return;
}


int main( int argc, char *argv[] )
{
 // Create the instance of grammatical engine and connect the local database.
 // SOL_GREN_LAZY_LEXICON instructs the engine to load the word entries when they needed
 // http://www.solarix.ru/api/sol_CreateGrammarEngine.shtml
 #if defined WIN32
 const char dict_path[] = "..\\..\\..\\..\\..\\bin-windows\\dictionary.xml";
 #else
  #if defined __i386__
  const char dict_path[] = "../../../../../bin-linux/dictionary.xml";
  #else
  const char dict_path[] = "../../../../../bin-linux64/dictionary.xml";
  #endif
 #endif

 printf( "Loading dictionary %s ...\n", dict_path );

 HGREN hEngine = sol_CreateGrammarEngineEx8( dict_path, SOL_GREN_LAZY_LEXICON );

 if( hEngine==NULL )
  {
   printf( "Error\n" );
   return 1;
  }

 char sentence[] = "Кошки ели мой корм"; // utf-8

 // Buffers for some text information
 char * EntryName = new char[ sol_MaxLexemLen8(hEngine) ];
 char * PartOfSpeechName = new char[ sol_MaxLexemLen8(hEngine) ];
 char * Word = new char[ sol_MaxLexemLen8(hEngine) ];

 // Split the sentence into words.
 // http://www.solarix.ru/api/sol_Tokenize.shtml
 HGREN_STR hWords = sol_Tokenize8( hEngine, sentence, -1 );

 int nword = sol_CountStrings(hWords); // http://www.solarix.ru/api/sol_CountStrings.shtml
 
 for( int i=0; i<nword; ++i )
 {
  sol_GetString8( hWords, i, Word ); // extract next word http://www.solarix.ru/api/sol_GetString.shtml

  HGREN_WCOORD hProjs = sol_ProjectWord8( hEngine, Word, 0 ); // look for the word forms in dictionary http://www.solarix.ru/api/sol_ProjectWord.shtml

  int nprojs = sol_CountProjections(hProjs); // http://www.solarix.ru/api/sol_CountProjections.shtml
  
  for( int i=0; i<nprojs; ++i )
   {
    int id_entry = sol_GetIEntry(hProjs,i); // http://www.solarix.ru/api/sol_GetIEntry.shtml
    int id_partofspeech = sol_GetEntryClass( hEngine, id_entry ); // http://www.solarix.ru/api/sol_GetEntryClass.shtml

    sol_GetEntryName8( hEngine, id_entry, EntryName ); // http://www.solarix.ru/api/sol_GetEntryName.shtml
    sol_GetClassName8( hEngine, id_partofspeech, PartOfSpeechName ); // http://www.solarix.ru/api/sol_GetClassName.shtml

    // ...
   }

  sol_DeleteProjections(hProjs); // http://www.solarix.ru/api/sol_DeleteProjections.shtml
 }

 sol_DeleteStrings(hWords); // http://www.solarix.ru/api/sol_DeleteStrings.shtml


 // -------------------------
 // Syntax analysis
 // -------------------------

 // Это короткое тестовое предложение содержит несколько морфологических неоднозначностей.
 // Например, существительное СУП может быть либо формой именительного падежа, либо формой винительного.
 // Обычно, в силу сложившейся практики формирования и просмотра таблиц сорвоформ лексикона,
 // сначала движок находит вариант с именительным падежом. Поэтому синтаксический анализатор
 // видит СУП/им.п./ как первый вариант. Это может мешать разбору, если сильно ограничивать
 // число просматриваемых альтернатив. Именно этот факт используется далее в коде для проверки,
 // что морфологическая модель работает.
 
 const char long_sentence[]="Мы ели вкусный суп";

 HGREN_RESPACK hPack;

 // --- no model of russian morphology ---

 int MorphologicalFlags = SOL_GREN_COMPLETE_ONLY;
 int SyntacticFlags = 0;
 int Constraints = 20 << 22;

 hPack = sol_SyntaxAnalysis8( hEngine, long_sentence, MorphologicalFlags, SyntacticFlags, Constraints, RUSSIAN_LANGUAGE );
 PrintSyntaxTrees( stdout, hEngine, hPack );
 printf( "\n\n" );
 sol_DeleteResPack( hPack );

 // включаем вероятностную модель русской морфологии...
 MorphologicalFlags = SOL_GREN_MODEL | SOL_GREN_COMPLETE_ONLY;
 SyntacticFlags = 0;

 // и сильно ограничиваем парсер на размер пространства перебора, до 2х альтернатив на каждом шаге...
 int MAX_ALT = 2;
 int TIMEOUT = 0;
 Constraints = (MAX_ALT<<22) | TIMEOUT;
 hPack = sol_SyntaxAnalysis8( hEngine, long_sentence, MorphologicalFlags, SyntacticFlags, Constraints, RUSSIAN_LANGUAGE );
 PrintSyntaxTrees( stdout, hEngine, hPack );
 sol_DeleteResPack( hPack );
 printf( "\n\n" );

 // проверим без модели - парсер не сможет выполнить разбор
 MorphologicalFlags = SOL_GREN_COMPLETE_ONLY;
 SyntacticFlags = 0;
 hPack = sol_SyntaxAnalysis8( hEngine, long_sentence, MorphologicalFlags, SyntacticFlags, Constraints, RUSSIAN_LANGUAGE );
 PrintSyntaxTrees( stdout, hEngine, hPack );
 sol_DeleteResPack( hPack );
 printf( "\n\n" );


 sol_DeleteGrammarEngine(hEngine); // http://www.solarix.ru/api/sol_DeleteGrammarEngine.shtml

 return 0;
}

