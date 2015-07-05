/* __header_here__ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined WIN32
// ...
#else
#include <dlfcn.h>
#endif


#include "php.h"

#include "php_ini.h"
#include "ext/standard/info.h"
#include "gren.h"
#include <lem/solarix/solarix_grammar_engine.h>

/* If you declare any globals in php_extname.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(extname)
*/

/* True global resources - no need for thread safety here */
static int le_gren;



ZEND_BEGIN_ARG_INFO( arginfo_sol_CreateGrammarEngineEx8, 0 )
	ZEND_ARG_INFO( 0, dictionary_xml )
	ZEND_ARG_INFO( 0, InstanceFlags )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO( arginfo_sol_LoadDictionaryEx8, 0 )
	ZEND_ARG_INFO( 0, hEngine )
	ZEND_ARG_INFO( 0, dictionary_xml )
	ZEND_ARG_INFO( 0, InstanceFlags )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO( arginfo_sol_UnloadDictionary, 0 )
	ZEND_ARG_INFO( 0, hEngine )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO( arginfo_sol_DeleteGrammarEngine, 0 )
	ZEND_ARG_INFO( 0, hEngine )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO( arginfo_sol_CountEntries, 0 )
	ZEND_ARG_INFO( 0, hEngine )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO( arginfo_sol_GetVersion, 0 )
	ZEND_ARG_INFO( 0, hEngine )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO( arginfo_sol_DictionaryVersion, 0 )
	ZEND_ARG_INFO( 0, hEngine )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO( arginfo_sol_MaxLexemLen8, 0 )
	ZEND_ARG_INFO( 0, hEngine )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO( arginfo_sol_Tokenize8, 0 )
	ZEND_ARG_INFO( 0, hEngine )
	ZEND_ARG_INFO( 0, Sentence )
	ZEND_ARG_INFO( 0, LanguageID )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO( arginfo_sol_CountStrings, 0 )
	ZEND_ARG_INFO( 0, hStr )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO( arginfo_sol_GetString8, 0 )
	ZEND_ARG_INFO( 0, hStr )
	ZEND_ARG_INFO( 0, i )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO( arginfo_sol_DeleteStrings, 0 )
	ZEND_ARG_INFO( 0, hStr )
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO( arginfo_sol_GetClassName8, 0 )
	ZEND_ARG_INFO( 0, hEngine )
	ZEND_ARG_INFO( 0, PartOfSpeechID )
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO( arginfo_sol_GetEntryName8, 0 )
	ZEND_ARG_INFO( 0, hEngine )
	ZEND_ARG_INFO( 0, EntryID )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO( arginfo_sol_GetEntryClass, 0 )
	ZEND_ARG_INFO( 0, hEngine )
	ZEND_ARG_INFO( 0, EntryID )
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO( arginfo_sol_FindEntry8, 0 )
	ZEND_ARG_INFO( 0, hEngine )
	ZEND_ARG_INFO( 0, Word )
	ZEND_ARG_INFO( 0, PartOfSpeechID )
	ZEND_ARG_INFO( 0, LanguageID )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO( arginfo_sol_CreateSentenceBrokerMem8, 0 )
	ZEND_ARG_INFO( 0, hEngine )
	ZEND_ARG_INFO( 0, Text )
	ZEND_ARG_INFO( 0, LanguageID )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO( arginfo_sol_FetchSentence, 0 )
	ZEND_ARG_INFO( 0, hSegmenter )
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO( arginfo_sol_GetFetchedSentenceLen, 0 )
	ZEND_ARG_INFO( 0, hSegmenter )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO( arginfo_sol_DeleteSentenceBroker, 0 )
	ZEND_ARG_INFO( 0, hSegmenter )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO( arginfo_sol_GetFetchedSentence8, 0 )
	ZEND_ARG_INFO( 0, hSegmenter )
ZEND_END_ARG_INFO()

const zend_function_entry gren_functions[] = {
    PHP_FE( sol_CreateGrammarEngineEx8, arginfo_sol_CreateGrammarEngineEx8 )
    PHP_FE( sol_DeleteGrammarEngine, arginfo_sol_DeleteGrammarEngine )
    PHP_FE( sol_UnloadDictionary, arginfo_sol_UnloadDictionary )
    PHP_FE( sol_CountEntries, arginfo_sol_CountEntries )
    PHP_FE( sol_GetVersion, arginfo_sol_GetVersion )
    PHP_FE( sol_DictionaryVersion, arginfo_sol_DictionaryVersion )
    PHP_FE( sol_MaxLexemLen8, arginfo_sol_MaxLexemLen8 )

    PHP_FE( sol_Tokenize8, arginfo_sol_Tokenize8 )
    PHP_FE( sol_CountStrings, arginfo_sol_CountStrings )
    PHP_FE( sol_GetString8, arginfo_sol_GetString8 )
    PHP_FE( sol_DeleteStrings, arginfo_sol_DeleteStrings )

    PHP_FE( sol_CreateSentenceBrokerMem8, arginfo_sol_CreateSentenceBrokerMem8 )
    PHP_FE( sol_FetchSentence, arginfo_sol_FetchSentence )
    PHP_FE( sol_GetFetchedSentenceLen, arginfo_sol_GetFetchedSentenceLen )
    PHP_FE( sol_GetFetchedSentence8, arginfo_sol_GetFetchedSentence8 )
    PHP_FE( sol_DeleteSentenceBroker, arginfo_sol_DeleteSentenceBroker )

    PHP_FE( sol_GetClassName8, arginfo_sol_GetClassName8 )
    PHP_FE( sol_GetEntryName8, arginfo_sol_GetEntryName8 )
    PHP_FE( sol_GetEntryClass, arginfo_sol_GetEntryClass )
    PHP_FE( sol_FindEntry8, arginfo_sol_FindEntry8 )

    PHP_FE( sol_ProjectWord8, NULL )
    PHP_FE( sol_CountProjections, NULL )
    PHP_FE( sol_GetIEntry, NULL )
    PHP_FE( sol_GetProjCoordState, NULL )
    PHP_FE( sol_DeleteProjections, NULL )

    PHP_FE( sol_MorphologyAnalysis8, NULL )
    PHP_FE( sol_DeleteResPack, NULL )

    PHP_FE( sol_CountGrafs, NULL )
    PHP_FE( sol_CountRoots, NULL )
    PHP_FE( sol_GetRoot, NULL )
    PHP_FE( sol_CountLeafs, NULL )
    PHP_FE( sol_GetLeafLinkType, NULL )
    PHP_FE( sol_GetLeaf, NULL )
    PHP_FE( sol_GetNodeIEntry, NULL )
    PHP_FE( sol_GetNodeVerIEntry, NULL )
    PHP_FE( sol_GetNodePosition, NULL )
    PHP_FE( sol_GetNodeContents8, NULL )
#else
    PHP_FE( sol_GetNodeCoordState, NULL )
    PHP_FE( sol_GetNodeVerCoordState, NULL )
    PHP_FE( sol_GetNodeVersionCount, NULL )
    PHP_FE( sol_GetNodeCoordPair, NULL )
    PHP_FE( sol_GetNodeVerCoordPair, NULL )
    PHP_FE( sol_GetNodePairsCount, NULL )
    PHP_FE( sol_GetNodeVerPairsCount, NULL )
    PHP_FE( sol_GetNodePairCoord, NULL )
    PHP_FE( sol_GetNodeVerPairCoord, NULL )
    PHP_FE( sol_GetNodePairState, NULL )
    PHP_FE( sol_GetNodeVerPairState, NULL )
    PHP_FE( sol_GetNodeContentsLen, NULL )

	/* __function_entries_here__ */
	PHP_FE_END	/* Must be the last line in extname_functions[] */
};






zend_module_entry gren_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"gren",
	gren_functions,
	PHP_MINIT(gren),
	PHP_MSHUTDOWN(gren),
	PHP_RINIT(gren),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(gren),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(gren),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

//#ifdef COMPILE_DL_EXTNAME
ZEND_GET_MODULE(gren)
//#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("extname.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_extname_globals, extname_globals)
    STD_PHP_INI_ENTRY("extname.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_extname_globals, extname_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_extname_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_extname_init_globals(zend_extname_globals *extname_globals)
{
	extname_globals->global_value = 0;
	extname_globals->global_string = NULL;
}
*/
/* }}} */

#if defined WIN32
static HMODULE hDLL_SQLite=NULL;
static HMODULE hDLL=NULL;
#else
static void* hDLL=NULL;
#endif

static sol_CreateGrammarEngineEx8_Fun sol_CreateGrammarEngineEx8_Ptr=NULL;
static sol_CountEntries_Fun sol_CountEntries_Ptr=NULL;
static sol_GetVersion_Fun sol_GetVersion_Ptr=NULL;
static sol_DictionaryVersion_Fun sol_DictionaryVersion_Ptr=NULL;
static sol_DeleteGrammarEngine_Fun sol_DeleteGrammarEngine_Ptr=NULL;
static sol_LoadDictionaryEx8_Fun sol_LoadDictionaryEx8_Ptr=NULL;
static sol_UnloadDictionary_Fun sol_UnloadDictionary_Ptr=NULL;
static sol_Tokenize8_Fun sol_Tokenize8_Ptr=NULL;
static sol_CountStrings_Fun sol_CountStrings_Ptr=NULL;
static sol_GetStringLen_Fun sol_GetStringLen_Ptr=NULL;
static sol_GetString8_Fun sol_GetString8_Ptr=NULL;
static sol_DeleteStrings_Fun sol_DeleteStrings_Ptr=NULL;

static sol_CreateSentenceBrokerMem8_Fun sol_CreateSentenceBrokerMem8_Ptr=NULL;
static sol_FetchSentence_Fun sol_FetchSentence_Ptr=NULL;
static sol_GetFetchedSentenceLen_Fun sol_GetFetchedSentenceLen_Ptr=NULL;
static sol_GetFetchedSentence8_Fun sol_GetFetchedSentence8_Ptr=NULL;
static sol_DeleteSentenceBroker_Fun sol_DeleteSentenceBroker_Ptr=NULL;

static sol_GetEntryName8_Fun sol_GetEntryName8_Ptr=NULL;
static sol_GetClassName8_Fun sol_GetClassName8_Ptr=NULL;
static sol_GetEntryClass_Fun sol_GetEntryClass_Ptr=NULL;
static sol_MaxLexemLen8_Fun sol_MaxLexemLen8_Ptr=NULL;
static sol_FindEntry8_Fun sol_FindEntry8_Ptr=NULL;

static sol_ProjectWord8_Fun sol_ProjectWord8_Ptr=NULL;
static sol_CountProjections_Fun sol_CountProjections_Ptr=NULL;
static sol_GetIEntry_Fun sol_GetIEntry_Ptr=NULL;
static sol_GetProjCoordState_Fun sol_GetProjCoordState_Ptr=NULL;
static sol_DeleteProjections_Fun sol_DeleteProjections_Ptr=NULL;
static sol_MorphologyAnalysis8_Fun sol_MorphologyAnalysis8_Ptr=NULL;
static sol_SyntaxAnalysis8_Fun sol_SyntaxAnalysis8_Ptr=NULL;
static sol_DeleteResPack_Fun sol_DeleteResPack_Ptr=NULL;

static sol_CountGrafs_Fun sol_CountGrafs_Ptr=NULL;
static sol_CountRoots_Fun sol_CountRoots_Ptr=NULL;
static sol_GetRoot_Fun sol_GetRoot_Ptr=NULL;
static sol_CountLeafs_Fun sol_CountLeafs_Ptr=NULL;
static sol_GetLeafLinkType_Fun sol_GetLeafLinkType_Ptr=NULL;
static sol_GetLeaf_Fun sol_GetLeaf_Ptr=NULL;
static sol_GetNodeIEntry_Fun sol_GetNodeIEntry_Ptr=NULL;
static sol_GetNodeVerIEntry_Fun sol_GetNodeVerIEntry_Ptr=NULL;
static sol_GetNodePosition_Fun sol_GetNodePosition_Ptr=NULL;
static sol_GetNodeContents8_Fun sol_GetNodeContents8_Ptr=NULL;
static sol_GetNodeCoordState_Fun sol_GetNodeCoordState_Ptr=NULL;
static sol_GetNodeVerCoordState_Fun sol_GetNodeVerCoordState_Ptr=NULL;
static sol_GetNodeVersionCount_Fun sol_GetNodeVersionCount_Ptr=NULL;
static sol_GetNodeCoordPair_Fun sol_GetNodeCoordPair_Ptr=NULL;
static sol_GetNodeVerCoordPair_Fun sol_GetNodeVerCoordPair_Ptr=NULL;
static sol_GetNodePairsCount_Fun sol_GetNodePairsCount_Ptr=NULL;
static sol_GetNodeVerPairsCount_Fun sol_GetNodeVerPairsCount_Ptr=NULL;
static sol_GetNodePairCoord_Fun sol_GetNodePairCoord_Ptr=NULL;
static sol_GetNodeVerPairCoord_Fun sol_GetNodeVerPairCoord_Ptr=NULL;
static sol_GetNodePairState_Fun sol_GetNodePairState_Ptr=NULL;
static sol_GetNodeVerPairState_Fun sol_GetNodeVerPairState_Ptr=NULL;
static sol_GetNodeContentsLen_Fun sol_GetNodeContentsLen_Ptr=NULL;

#define CHECK_PTR(x) if( (x)==NULL ) return FAILURE

#if defined WIN32
#define GET_ADDR(func_name) GetProcAddress( hDLL, func_name )
#else
#define GET_ADDR(func_name) dlsym(hDLL,func_name)
#endif


PHP_MINIT_FUNCTION(gren)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/

 #if defined WIN32
 HMODULE hModule = GetModuleHandle(NULL);
 char filename[MAX_PATH+1]="";
 char sqlite_filename[MAX_PATH+1]="";
 char * last_dir_pos;

 GetModuleFileNameA( hModule, filename, sizeof(filename) );
 last_dir_pos = strrchr( filename, '\\' );
 if( last_dir_pos==NULL )
  filename[0]=0;
 else
  *last_dir_pos = 0;

 strcpy( sqlite_filename, filename );
 strcat( sqlite_filename, "\\ext\\sqlite.dll" );
 hDLL_SQLite = LoadLibraryA( sqlite_filename );

 strcat( filename, "\\ext\\solarix_grammar_engine.dll" );
 hDLL = LoadLibrary( filename );
 if( hDLL==NULL )
  return FAILURE;
 #elif

 char filename[4096]="";

 strcat( filename, "/usr/lib/solarix_grammar_engine.so" );
 hDLL = dlopen( filename, RTLD_NOW | RTLD_GLOBAL );
 if( hDLL==NULL )
  return FAILURE;

 #endif


 sol_CreateGrammarEngineEx8_Ptr = (sol_CreateGrammarEngineEx8_Fun)GET_ADDR( "sol_CreateGrammarEngineEx8" );
 if( sol_CreateGrammarEngineEx8_Ptr==NULL )
  return FAILURE;

 sol_CountEntries_Ptr = (sol_CountEntries_Fun)GET_ADDR( "sol_CountEntries" );
 sol_GetVersion_Ptr = (sol_GetVersion_Fun)GET_ADDR( "sol_GetVersion" );
 sol_DictionaryVersion_Ptr = (sol_DictionaryVersion_Fun)GET_ADDR( "sol_DictionaryVersion" );
 sol_DeleteGrammarEngine_Ptr = (sol_DeleteGrammarEngine_Fun)GET_ADDR( "sol_DeleteGrammarEngine" );
 sol_LoadDictionaryEx8_Ptr = (sol_LoadDictionaryEx8_Fun)GET_ADDR( "sol_LoadDictionaryEx8" );
 sol_UnloadDictionary_Ptr = (sol_UnloadDictionary_Fun)GET_ADDR( "sol_UnloadDictionary" );

 sol_Tokenize8_Ptr = (sol_Tokenize8_Fun)GET_ADDR( "sol_Tokenize8" );
 sol_CountStrings_Ptr = (sol_CountStrings_Fun)GET_ADDR( "sol_CountStrings" );
 sol_GetStringLen_Ptr = (sol_GetStringLen_Fun)GET_ADDR( "sol_GetStringLen" );
 sol_GetString8_Ptr = (sol_GetString8_Fun)GET_ADDR( "sol_GetString8" );
 sol_DeleteStrings_Ptr = (sol_DeleteStrings_Fun)GET_ADDR( "sol_DeleteStrings" );
 sol_CreateSentenceBrokerMem8_Ptr=(sol_CreateSentenceBrokerMem8_Fun)GET_ADDR( "sol_CreateSentenceBrokerMem8" );

 CHECK_PTR( sol_CreateSentenceBrokerMem8_Ptr );

 sol_FetchSentence_Ptr=(sol_FetchSentence_Fun)GET_ADDR( "sol_FetchSentence" );
 sol_GetFetchedSentenceLen_Ptr=(sol_GetFetchedSentenceLen_Fun)GET_ADDR( "sol_GetFetchedSentenceLen" );
 sol_GetFetchedSentence8_Ptr=(sol_GetFetchedSentence8_Fun)GET_ADDR( "sol_GetFetchedSentence8" );
 sol_DeleteSentenceBroker_Ptr=(sol_DeleteSentenceBroker_Fun)GET_ADDR( "sol_DeleteSentenceBroker" );

 sol_GetEntryName8_Ptr =(sol_GetEntryName8_Fun)GET_ADDR( "sol_GetEntryName8" );
 sol_GetClassName8_Ptr =(sol_GetClassName8_Fun)GET_ADDR( "sol_GetClassName8" );
 sol_GetEntryClass_Ptr =(sol_GetEntryClass_Fun)GET_ADDR( "sol_GetEntryClass" );
 sol_MaxLexemLen8_Ptr = (sol_MaxLexemLen8_Fun)GET_ADDR( "sol_MaxLexemLen8" );
 sol_FindEntry8_Ptr = (sol_FindEntry8_Fun)GET_ADDR( "sol_FindEntry8" );

 sol_ProjectWord8_Ptr = (sol_ProjectWord8_Fun)GET_ADDR( "sol_ProjectWord8" );
 sol_CountProjections_Ptr = (sol_CountProjections_Fun)GET_ADDR( "sol_CountProjections" );
 sol_GetIEntry_Ptr = (sol_GetIEntry_Fun)GET_ADDR( "sol_GetIEntry" );
 sol_GetProjCoordState_Ptr = (sol_GetProjCoordState_Fun)GET_ADDR( "sol_GetProjCoordState" );
 sol_DeleteProjections_Ptr = (sol_DeleteProjections_Fun)GET_ADDR( "sol_DeleteProjections" );

 sol_MorphologyAnalysis8_Ptr = (sol_MorphologyAnalysis8_Fun)GET_ADDR( "sol_MorphologyAnalysis8" );
 sol_SyntaxAnalysis8_Ptr = (sol_SyntaxAnalysis8_Fun)GET_ADDR( "sol_SyntaxAnalysis8" );
 sol_DeleteResPack_Ptr = (sol_DeleteResPack_Fun)GET_ADDR( "sol_DeleteResPack" );

 sol_CountGrafs_Ptr = (sol_CountGrafs_Fun)GET_ADDR( "sol_CountGrafs" );
 sol_CountRoots_Ptr = (sol_CountRoots_Fun)GET_ADDR( "sol_CountRoots" );
 sol_GetRoot_Ptr = (sol_GetRoot_Fun)GET_ADDR( "sol_GetRoot" );
 sol_CountLeafs_Ptr = (sol_CountLeafs_Fun)GET_ADDR( "sol_CountLeafs" );
 sol_GetLeafLinkType_Ptr = (sol_GetLeafLinkType_Fun)GET_ADDR( "sol_GetLeafLinkType" );
 sol_GetLeaf_Ptr = (sol_GetLeaf_Fun)GET_ADDR( "sol_GetLeaf" );
 sol_GetNodeIEntry_Ptr = (sol_GetNodeIEntry_Fun)GET_ADDR( "sol_GetNodeIEntry" );
 sol_GetNodeVerIEntry_Ptr = (sol_GetNodeVerIEntry_Fun)GET_ADDR( "sol_GetNodeVerIEntry" );
 sol_GetNodePosition_Ptr = (sol_GetNodePosition_Fun)GET_ADDR( "sol_GetNodePosition" );
 sol_GetNodeContents8_Ptr = (sol_GetNodeContents8_Fun)GET_ADDR( "sol_GetNodeContents8" );
 sol_GetNodeCoordState_Ptr = (sol_GetNodeCoordState_Fun)GET_ADDR( "sol_GetNodeCoordState" );
 sol_GetNodeVerCoordState_Ptr = (sol_GetNodeVerCoordState_Fun)GET_ADDR( "sol_GetNodeVerCoordState" );
 sol_GetNodeVersionCount_Ptr = (sol_GetNodeVersionCount_Fun)GET_ADDR( "sol_GetNodeVersionCount" );
 sol_GetNodeCoordPair_Ptr = (sol_GetNodeCoordPair_Fun)GET_ADDR( "sol_GetNodeCoordPair" );
 sol_GetNodeVerCoordPair_Ptr = (sol_GetNodeVerCoordPair_Fun)GET_ADDR( "sol_GetNodeVerCoordPair" );
 sol_GetNodePairsCount_Ptr = (sol_GetNodePairsCount_Fun)GET_ADDR( "sol_GetNodePairsCount" );
 sol_GetNodeVerPairsCount_Ptr = (sol_GetNodeVerPairsCount_Fun)GET_ADDR( "sol_GetNodeVerPairsCount" );
 sol_GetNodePairCoord_Ptr = (sol_GetNodePairCoord_Fun)GET_ADDR( "sol_GetNodePairCoord" );
 sol_GetNodeVerPairCoord_Ptr = (sol_GetNodeVerPairCoord_Fun)GET_ADDR( "sol_GetNodeVerPairCoord" );
 sol_GetNodePairState_Ptr = (sol_GetNodePairState_Fun)GET_ADDR( "sol_GetNodePairState" );
 sol_GetNodeVerPairState_Ptr = (sol_GetNodeVerPairState_Fun)GET_ADDR( "sol_GetNodeVerPairState" );
 sol_GetNodeContentsLen_Ptr = (sol_GetNodeContentsLen_Fun)GET_ADDR( "sol_GetNodeContentsLen" );

 return SUCCESS;
}


PHP_MSHUTDOWN_FUNCTION(gren)
{
 #if defined WIN32
 FreeLibrary( hDLL );
 FreeLibrary( hDLL_SQLite );
 hDLL=NULL;
 hDLL_SQLite=NULL;
 #else
 dlclose(hDLL);
 hDLL=NULL;
 #endif

	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
 return SUCCESS;
}




/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(gren)
{
	return SUCCESS;
}
/* }}} */

PHP_RSHUTDOWN_FUNCTION(gren)
{
	return SUCCESS;
}


PHP_MINFO_FUNCTION(gren)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "gren support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}





PHP_FUNCTION(sol_CreateGrammarEngineEx8)
{
 char *dictionary_xml = "e:\\mvoice\\lem\\bin-windows\\dictionary.xml";
 int argc = ZEND_NUM_ARGS();
 int dictionary_xml_len;
 long InstanceFlags=0;
 HGREN hEngine=NULL;

 if( argc != 2 ) WRONG_PARAM_COUNT;


 if( zend_parse_parameters( argc TSRMLS_CC, "sl", &dictionary_xml, &dictionary_xml_len, &InstanceFlags ) == FAILURE )
  {
   RETURN_LONG((long)0);
  }


 hEngine = sol_CreateGrammarEngineEx8_Ptr( dictionary_xml, InstanceFlags );

 if( hEngine==NULL )
  {
   RETURN_LONG(0L);
  }
 else
  {
   RETURN_LONG((long)hEngine);
  }
}




PHP_FUNCTION(sol_LoadDictionaryEx8)
{
 long hEngine=0;
 long rc=0;
 char *dictionary_xml = "e:\\mvoice\\lem\\bin-windows\\dictionary.xml";
 int argc = ZEND_NUM_ARGS();
 int dictionary_xml_len;
 long InstanceFlags=0;

 if( argc != 2 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "lsl", &hEngine, &dictionary_xml, &dictionary_xml_len, &InstanceFlags ) == FAILURE )
  {
   RETURN_LONG((long)-1);
  }

 rc = sol_LoadDictionaryEx8_Ptr( (HGREN)hEngine, dictionary_xml, InstanceFlags );
 RETURN_LONG(rc);
}



PHP_FUNCTION(sol_CountEntries)
{
 long nentry=0;
 int argc = ZEND_NUM_ARGS();
 HGREN hEngine=NULL;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hEngine ) == FAILURE )
  {
   RETURN_LONG(-1L);
  }

 nentry = sol_CountEntries_Ptr( hEngine );
 RETURN_LONG(nentry);
}


PHP_FUNCTION(sol_GetVersion)
{
 long major=0, minor=0, build=0;
 int argc = ZEND_NUM_ARGS();
 char buf[32]="";
 HGREN hEngine=NULL;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hEngine ) == FAILURE )
  {
   RETURN_STRING("",1);
  }

 sol_GetVersion_Ptr( hEngine, &major, &minor, &build );

 sprintf( buf, "%d.%d.%d", major, minor, build );

 RETURN_STRING(buf,1);
}



PHP_FUNCTION(sol_MaxLexemLen8)
{
 long max_len=0;
 int argc = ZEND_NUM_ARGS();
 HGREN hEngine=NULL;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hEngine ) == FAILURE )
  {
   RETURN_STRING("",1);
  }

 max_len = sol_MaxLexemLen8_Ptr( hEngine );

 RETURN_LONG(max_len);
}




PHP_FUNCTION(sol_DictionaryVersion)
{
 long ver_no=0;
 int argc = ZEND_NUM_ARGS();
 HGREN hEngine=NULL;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hEngine ) == FAILURE )
  {
   RETURN_LONG(-1L);
  }

 ver_no = sol_DictionaryVersion_Ptr( hEngine );
 RETURN_LONG(ver_no);
}


PHP_FUNCTION(sol_DeleteGrammarEngine)
{
 long rc=0;
 int argc = ZEND_NUM_ARGS();
 char buf[32]="";
 HGREN hEngine=NULL;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hEngine ) == FAILURE )
  {
   RETURN_LONG(-1L);
  }

 rc = sol_DeleteGrammarEngine_Ptr( hEngine );
 RETURN_LONG(rc);
}


PHP_FUNCTION(sol_UnloadDictionary)
{
 long rc=0;
 int argc = ZEND_NUM_ARGS();
 HGREN hEngine=NULL;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hEngine ) == FAILURE )
  {
   RETURN_LONG(-1L);
  }

 rc = sol_UnloadDictionary_Ptr( hEngine );
 RETURN_LONG(rc);
}




PHP_FUNCTION(sol_Tokenize8)
{
 HGREN_STR hStr=NULL;
 char *Sentence=NULL;
 int SentenceLen=0;
 int argc = ZEND_NUM_ARGS();
 HGREN hEngine=NULL;
 long LanguageID=-1;

 if( ZEND_NUM_ARGS() != 3 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "lsl", &hEngine, &Sentence, &SentenceLen, &LanguageID ) == FAILURE )
  {
   RETURN_LONG(-1L);
  }

 hStr = sol_Tokenize8_Ptr( hEngine, Sentence, LanguageID );

 RETURN_LONG((long)hStr);
}


PHP_FUNCTION(sol_CountStrings)
{
 HGREN_STR hStr=NULL;
 int argc = ZEND_NUM_ARGS();
 long count=0;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hStr ) == FAILURE )
  {
   RETURN_LONG(-1L);
  }

 count = sol_CountStrings_Ptr(hStr);

 RETURN_LONG((long)count);
}



PHP_FUNCTION(sol_DeleteStrings)
{
 HGREN_STR hStr=NULL;
 int argc = ZEND_NUM_ARGS();
 long rc=0;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hStr ) == FAILURE )
  {
   RETURN_LONG(-1L);
  }

 rc = sol_DeleteStrings_Ptr(hStr);

 RETURN_LONG((long)rc);
}



PHP_FUNCTION(sol_GetString8)
{
 int argc = ZEND_NUM_ARGS();
 long i=0;
 long str_len=0;
 char *buf=NULL;
 HGREN_STR hStr=NULL;

 if( ZEND_NUM_ARGS() != 2 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "ll", &hStr, &i ) == FAILURE )
  {
   RETURN_NULL();
  }
 else
  {
   str_len = sol_GetStringLen_Ptr( hStr, i );
   buf = emalloc( str_len*6 + 1 );
   sol_GetString8_Ptr( hStr, i, buf );
   RETURN_STRING(buf,0);
  }
}


PHP_FUNCTION(sol_CreateSentenceBrokerMem8)
{
 HGREN hEngine=NULL;
 HGREN_SBROKER hSegmenter=NULL;
 char *Text=NULL;
 int TextLen=0;
 int argc = ZEND_NUM_ARGS();
 long LanguageID=-1;

 if( ZEND_NUM_ARGS() != 3 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "lsl", &hEngine, &Text, &TextLen, &LanguageID ) == FAILURE )
  {
   RETURN_NULL();
  }

 hSegmenter = sol_CreateSentenceBrokerMem8_Ptr( hEngine, Text, LanguageID );

 RETURN_LONG((long)hSegmenter);
}


PHP_FUNCTION(sol_FetchSentence)
{
 HGREN_SBROKER hSegmenter=NULL;
 int argc = ZEND_NUM_ARGS();
 long rc=0;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hSegmenter ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 rc = sol_FetchSentence_Ptr(hSegmenter);

 RETURN_LONG((long)rc);
}


PHP_FUNCTION(sol_GetFetchedSentenceLen)
{
 HGREN_SBROKER hSegmenter=NULL;
 int argc = ZEND_NUM_ARGS();
 long len=0;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hSegmenter ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 len = sol_GetFetchedSentenceLen_Ptr(hSegmenter);

 RETURN_LONG((long)len);
}


PHP_FUNCTION(sol_GetFetchedSentence8)
{
 int argc = ZEND_NUM_ARGS();
 long i=0;
 int str_len=0;
 char *buf=NULL;
 HGREN_SBROKER hSegmenter=NULL;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hSegmenter ) == FAILURE )
  {
   RETURN_NULL();
  }
 else
  {
   str_len = sol_GetFetchedSentenceLen_Ptr( hSegmenter );
   buf = emalloc( str_len*6 + 1 );
   sol_GetFetchedSentence8_Ptr( hSegmenter, buf );
   RETURN_STRING(buf,0);
  }
}


PHP_FUNCTION(sol_DeleteSentenceBroker)
{
 HGREN_SBROKER hSegmenter=NULL;
 int argc = ZEND_NUM_ARGS();
 long rc=0;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hSegmenter ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 rc = sol_DeleteSentenceBroker_Ptr(hSegmenter);

 RETURN_LONG((long)rc);
}




PHP_FUNCTION(sol_GetClassName8)
{
 HGREN hEngine=NULL;
 long PartOfSpeechID=-1;
 int argc = ZEND_NUM_ARGS();
 char * buf=NULL;
 int max_len=0;

 if( ZEND_NUM_ARGS() != 2 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "ll", &hEngine, &PartOfSpeechID ) == FAILURE )
  {
   RETURN_NULL();
  }

 max_len = sol_MaxLexemLen8_Ptr(hEngine);
 buf = emalloc( max_len+1 );
 sol_GetClassName8_Ptr( hEngine, PartOfSpeechID, buf );

 RETURN_STRING(buf,0);
}


PHP_FUNCTION(sol_GetEntryName8)
{
 HGREN hEngine=NULL;
 long EntryID=-1;
 int argc = ZEND_NUM_ARGS();
 char * buf=NULL;
 int max_len=0;

 if( ZEND_NUM_ARGS() != 2 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "ll", &hEngine, &EntryID ) == FAILURE )
  {
   RETURN_NULL();
  }

 max_len = sol_MaxLexemLen8_Ptr(hEngine);
 buf = emalloc( max_len+1 );
 sol_GetEntryName8_Ptr( hEngine, EntryID, buf );

 RETURN_STRING(buf,0);
}


PHP_FUNCTION(sol_GetEntryClass)
{
 HGREN hEngine=NULL;
 long EntryID=-1;
 int argc = ZEND_NUM_ARGS();
 char * buf=NULL;
 int max_len=0;
 long PartOfSpeechID=-1;

 if( ZEND_NUM_ARGS() != 2 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "ll", &hEngine, &EntryID ) == FAILURE )
  {
   RETURN_NULL();
  }

 max_len = sol_MaxLexemLen8_Ptr(hEngine);
 buf = malloc( max_len+1 );
 PartOfSpeechID = sol_GetEntryClass_Ptr( hEngine, EntryID );

 RETURN_LONG(PartOfSpeechID);
}


PHP_FUNCTION(sol_FindEntry8)
{
 HGREN hEngine=NULL;
 long EntryID=-1;
 long PartOfSpeechID=-1;
 long LanguageID=-1;
 int argc = ZEND_NUM_ARGS();
 char *Word=NULL;
 int WordLen=0;

 if( ZEND_NUM_ARGS() != 4 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "lsll", &hEngine, &Word, &WordLen, &PartOfSpeechID, &LanguageID ) == FAILURE )
  {
   RETURN_NULL();
  }

 EntryID = sol_FindEntry8_Ptr( hEngine, Word, PartOfSpeechID, LanguageID );

 RETURN_LONG(EntryID);
}



PHP_FUNCTION(sol_ProjectWord8)
{
 HGREN hEngine=NULL;
 int argc = ZEND_NUM_ARGS();
 char *Word=NULL;
 int WordLen=0;
 HGREN_WCOORD hList=NULL;
 long Flags=0;

 if( ZEND_NUM_ARGS() != 3 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "lsl", &hEngine, &Word, &WordLen, &Flags ) == FAILURE )
  {
   RETURN_NULL();
  }

 hList = sol_ProjectWord8_Ptr( hEngine, Word, Flags );

 RETURN_LONG((long)hList);
}


PHP_FUNCTION(sol_CountProjections)
{
 HGREN_WCOORD hList=NULL;
 int argc = ZEND_NUM_ARGS();
 long count=0;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hList ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 count = sol_CountProjections_Ptr( hList );

 RETURN_LONG(count);
}


PHP_FUNCTION(sol_GetIEntry)
{
 HGREN_WCOORD hList=NULL;
 int argc = ZEND_NUM_ARGS();
 long ItemIndex=-1;
 long EntryID=-1;

 if( ZEND_NUM_ARGS() != 2 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "ll", &hList, &ItemIndex ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 EntryID = sol_GetIEntry_Ptr( hList, ItemIndex );

 RETURN_LONG(EntryID);
}



PHP_FUNCTION(sol_GetProjCoordState)
{
 HGREN hEngine=NULL;
 HGREN_WCOORD hList=NULL;
 int argc = ZEND_NUM_ARGS();
 long ItemIndex=-1;
 long CoordID=-1;
 long StateID=-1;

 if( ZEND_NUM_ARGS() != 4 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "llll", &hEngine, &hList, &ItemIndex, &CoordID ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 StateID = sol_GetProjCoordState_Ptr( hEngine, hList, ItemIndex, CoordID );

 RETURN_LONG(StateID);
}



PHP_FUNCTION(sol_DeleteProjections)
{
 HGREN_WCOORD hList=NULL;
 int argc = ZEND_NUM_ARGS();
 long rc=0;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hList ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 rc = sol_DeleteProjections_Ptr( hList );

 RETURN_LONG(rc);
}



PHP_FUNCTION(sol_MorphologyAnalysis8)
{
 HGREN hEngine=NULL;
 int argc = ZEND_NUM_ARGS();
 char *Sentence=NULL;
 int SentenceLen=0;
 long Flags=0;
 long UnusedFlags=0;
 long MaxMSec=0;
 long LanguageID=-1;
 HGREN_RESPACK hRes=NULL;

 if( ZEND_NUM_ARGS() != 6 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "lsllll", &hEngine, &Sentence, &SentenceLen, &Flags, &UnusedFlags, &MaxMSec, &LanguageID ) == FAILURE )
  {
   RETURN_NULL();
  }

 hRes = sol_MorphologyAnalysis8_Ptr( hEngine, Sentence, Flags, UnusedFlags, MaxMSec, LanguageID );

 RETURN_LONG((long)hRes);
}


PHP_FUNCTION(sol_SyntaxAnalysis8)
{
 HGREN hEngine=NULL;
 int argc = ZEND_NUM_ARGS();
 char *Sentence=NULL;
 int SentenceLen=0;
 long MorphologicalFlags=0;
 long SyntacticFlags=0;
 long Constraints=0;
 long LanguageID=-1;
 HGREN_RESPACK hRes=NULL;

 if( ZEND_NUM_ARGS() != 6 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "lsllll", &hEngine, &Sentence, &SentenceLen, &MorphologicalFlags, &SyntacticFlags, &Constraints, &LanguageID ) == FAILURE )
  {
   RETURN_NULL();
  }

 hRes = sol_SyntaxAnalysis8_Ptr( hEngine, Sentence, MorphologicalFlags, SyntacticFlags, Constraints, LanguageID );

 RETURN_LONG((long)hRes);
}


PHP_FUNCTION(sol_DeleteResPack)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_RESPACK hPack=NULL;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hPack ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 sol_DeleteResPack_Ptr( hPack );

 RETURN_NULL();
}





PHP_FUNCTION(sol_CountGrafs)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_RESPACK hPack=NULL;
 long rc=0;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hPack ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 rc = sol_CountGrafs_Ptr( hPack );

 RETURN_LONG(rc);
}


PHP_FUNCTION(sol_CountRoots)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_RESPACK hPack=NULL;
 long igraf=0;
 long rc=0;

 if( ZEND_NUM_ARGS() != 2 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "ll", &hPack, &igraf ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 rc = sol_CountRoots_Ptr( hPack, igraf );

 RETURN_LONG(rc);
}


PHP_FUNCTION(sol_GetRoot)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_RESPACK hPack=NULL;
 long igraf=0;
 long iroot=0;
 HGREN_TREENODE hNode=NULL;

 if( ZEND_NUM_ARGS() != 3 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "lll", &hPack, &igraf, &iroot ) == FAILURE )
  {
   RETURN_NULL();
  }

 hNode = sol_GetRoot_Ptr( hPack, igraf, iroot );

 RETURN_LONG((long)hNode);
}


PHP_FUNCTION(sol_CountLeafs)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_TREENODE hNode=NULL;
 long count=0;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hNode ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 count = sol_CountLeafs_Ptr( hNode );

 RETURN_LONG(count);
}


PHP_FUNCTION(sol_GetLeafLinkType)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_TREENODE hNode=NULL;
 long iLeaf=0;
 long rc=0;

 if( ZEND_NUM_ARGS() != 2 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "ll", &hNode, &iLeaf ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 rc = sol_GetLeafLinkType_Ptr( hNode, iLeaf );

 RETURN_LONG(rc);
}


PHP_FUNCTION(sol_GetLeaf)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_TREENODE hNode=NULL;
 HGREN_TREENODE hLeaf=NULL;
 long iLeaf=0;

 if( ZEND_NUM_ARGS() != 2 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "ll", &hNode, &iLeaf ) == FAILURE )
  {
   RETURN_NULL();
  }

 hLeaf = sol_GetLeaf_Ptr( hNode, iLeaf );

 RETURN_LONG((long)hLeaf);
}


PHP_FUNCTION(sol_GetNodeIEntry)
{
 int argc = ZEND_NUM_ARGS();
 HGREN hEngine=NULL;
 HGREN_TREENODE hNode=NULL;
 long id_entry=-1;

 if( ZEND_NUM_ARGS() != 2 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "ll", &hEngine, &hNode ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 id_entry = sol_GetNodeIEntry_Ptr( hEngine, hNode );

 RETURN_LONG(id_entry);
}


PHP_FUNCTION(sol_GetNodeVerIEntry)
{
 int argc = ZEND_NUM_ARGS();
 HGREN hEngine=NULL;
 HGREN_TREENODE hNode=NULL;
 long iver=0;
 long id_entry=-1;

 if( ZEND_NUM_ARGS() != 3 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "lll", &hEngine, &hNode, &iver ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 id_entry = sol_GetNodeVerIEntry_Ptr( hEngine, hNode, iver );

 RETURN_LONG(id_entry);
}


PHP_FUNCTION(sol_GetNodePosition)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_TREENODE hNode=NULL;
 long pos=0;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hNode ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 pos = sol_GetNodePosition_Ptr( hNode );

 RETURN_LONG(pos);
}


PHP_FUNCTION(sol_GetNodeContentsLen)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_TREENODE hNode=NULL;
 long len=0;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hNode ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 len = sol_GetNodeContentsLen_Ptr( hNode );

 RETURN_LONG(len);
}




PHP_FUNCTION(sol_GetNodeCoordState)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_TREENODE hNode=NULL;
 long id_state=0;
 long CoordID=0;

 if( ZEND_NUM_ARGS() != 2 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "ll", &hNode, &CoordID ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 id_state = sol_GetNodeCoordState_Ptr( hNode, CoordID );

 RETURN_LONG(id_state);
}


PHP_FUNCTION(sol_GetNodeVerCoordState)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_TREENODE hNode=NULL;
 long iver=0;
 long id_state=0;
 long CoordID=0;

 if( ZEND_NUM_ARGS() != 3 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "ll", &hNode, &iver, &CoordID ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 id_state = sol_GetNodeVerCoordState_Ptr( hNode, iver, CoordID );

 RETURN_LONG(id_state);
}


PHP_FUNCTION(sol_GetNodeVersionCount)
{
 int argc = ZEND_NUM_ARGS();
 HGREN hEngine=NULL;
 HGREN_TREENODE hNode=NULL;
 long count=0;

 if( ZEND_NUM_ARGS() != 2 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "ll", &hEngine, &hNode ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 count = sol_GetNodeVersionCount_Ptr( hEngine, hNode );

 RETURN_LONG(count);
}


PHP_FUNCTION(sol_GetNodeCoordPair)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_TREENODE hNode=NULL;
 long CoordID=-1;
 long StateID=-1;
 long rc=0;
 
 if( ZEND_NUM_ARGS() != 3 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "lll", &hNode, &CoordID, &StateID ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 rc = sol_GetNodeCoordPair_Ptr( hNode, CoordID, StateID );

 RETURN_LONG(rc);
}


PHP_FUNCTION(sol_GetNodeVerCoordPair)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_TREENODE hNode=NULL;
 long iver=-1;
 long CoordID=-1;
 long StateID=-1;
 long rc=0;
 
 if( ZEND_NUM_ARGS() != 4 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "llll", &hNode, &iver, &CoordID, &StateID ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 rc = sol_GetNodeVerCoordPair_Ptr( hNode, iver, CoordID, StateID );

 RETURN_LONG(rc);
}


PHP_FUNCTION(sol_GetNodePairsCount)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_TREENODE hNode=NULL;
 long count=0;
 
 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hNode ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 count = sol_GetNodePairsCount_Ptr( hNode );

 RETURN_LONG(count);
}


PHP_FUNCTION(sol_GetNodeVerPairsCount)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_TREENODE hNode=NULL;
 long iver=0;
 long count=0;
 
 if( ZEND_NUM_ARGS() != 2 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "ll", &hNode, &iver ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 count = sol_GetNodeVerPairsCount_Ptr( hNode, iver );

 RETURN_LONG(count);
}



PHP_FUNCTION(sol_GetNodePairCoord)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_TREENODE hNode=NULL;
 long ipair=-1;
 long id_coord=0;
 
 if( ZEND_NUM_ARGS() != 2 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "ll", &hNode, &ipair ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 id_coord = sol_GetNodePairCoord_Ptr( hNode, ipair );

 RETURN_LONG(id_coord);
}



PHP_FUNCTION(sol_GetNodeVerPairCoord)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_TREENODE hNode=NULL;
 long iver=-1;
 long ipair=-1;
 long id_coord=0;
 
 if( ZEND_NUM_ARGS() != 3 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "lll", &hNode, &iver, &ipair ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 id_coord = sol_GetNodeVerPairCoord_Ptr( hNode, iver, ipair );

 RETURN_LONG(id_coord);
}


PHP_FUNCTION(sol_GetNodePairState)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_TREENODE hNode=NULL;
 long ipair=-1;
 long id_state=0;
 
 if( ZEND_NUM_ARGS() != 2 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "ll", &hNode, &ipair ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 id_state = sol_GetNodePairState_Ptr( hNode, ipair );

 RETURN_LONG(id_state);
}


PHP_FUNCTION(sol_GetNodeVerPairState)
{
 int argc = ZEND_NUM_ARGS();
 HGREN_TREENODE hNode=NULL;
 long iver=-1;
 long ipair=-1;
 long id_state=0;
 
 if( ZEND_NUM_ARGS() != 3 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "lll", &hNode, &iver, &ipair ) == FAILURE )
  {
   RETURN_LONG(-100L);
  }

 id_state = sol_GetNodeVerPairState_Ptr( hNode, iver, ipair );

 RETURN_LONG(id_state);
}



PHP_FUNCTION(sol_GetNodeContents8)
{
 int argc = ZEND_NUM_ARGS();
 int str_len=0;
 char *buf=NULL;
 HGREN_TREENODE hNode=NULL;

 if( ZEND_NUM_ARGS() != 1 ) WRONG_PARAM_COUNT;

 if( zend_parse_parameters( argc TSRMLS_CC, "l", &hNode ) == FAILURE )
  {
   RETURN_NULL();
  }
 else
  {
   str_len = sol_GetNodeContentsLen_Ptr( hNode );
   buf = emalloc( str_len*6 + 1 );
   sol_GetNodeContents8_Ptr( hNode, buf );
   RETURN_STRING(buf,0);
  }
}

