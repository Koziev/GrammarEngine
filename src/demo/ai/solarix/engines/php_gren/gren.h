/* __header_here__ */

#ifndef PHP_GREN_H
#define PHP_GREN_H

extern zend_module_entry gren_module_entry;
#define phpext_gren_ptr &gren_module_entry

#ifdef PHP_WIN32
#	define PHP_GREN_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_GREN_API __attribute__ ((visibility("default")))
#else
#	define PHP_GREN_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(gren);
PHP_MSHUTDOWN_FUNCTION(gren);
PHP_RINIT_FUNCTION(gren);
PHP_RSHUTDOWN_FUNCTION(gren);
PHP_MINFO_FUNCTION(gren);

PHP_FUNCTION(sol_CreateGrammarEngineEx8);
PHP_FUNCTION(sol_LoadDictionaryEx8);
PHP_FUNCTION(sol_UnloadDictionary);
PHP_FUNCTION(sol_DeleteGrammarEngine);
PHP_FUNCTION(sol_CountEntries);
PHP_FUNCTION(sol_GetVersion);
PHP_FUNCTION(sol_DictionaryVersion);

PHP_FUNCTION(sol_Tokenize8);
PHP_FUNCTION(sol_CountStrings);
PHP_FUNCTION(sol_GetString8);
PHP_FUNCTION(sol_DeleteStrings);

PHP_FUNCTION(sol_CreateSentenceBrokerMem8);
PHP_FUNCTION(sol_FetchSentence);
PHP_FUNCTION(sol_GetFetchedSentenceLen);
PHP_FUNCTION(sol_GetFetchedSentence8);
PHP_FUNCTION(sol_DeleteSentenceBroker);

PHP_FUNCTION(sol_GetClassName8);
PHP_FUNCTION(sol_GetEntryName8);
PHP_FUNCTION(sol_GetEntryClass);
PHP_FUNCTION(sol_MaxLexemLen8);
PHP_FUNCTION(sol_FindEntry8);

PHP_FUNCTION(sol_ProjectWord8);
PHP_FUNCTION(sol_CountProjections);
PHP_FUNCTION(sol_GetIEntry);
PHP_FUNCTION(sol_GetProjCoordState);
PHP_FUNCTION(sol_DeleteProjections);

PHP_FUNCTION(sol_MorphologyAnalysis8);
PHP_FUNCTION(sol_SyntaxAnalysis8);
PHP_FUNCTION(sol_DeleteResPack);

PHP_FUNCTION(sol_CountGrafs);
PHP_FUNCTION(sol_CountRoots);
PHP_FUNCTION(sol_GetRoot);
PHP_FUNCTION(sol_CountLeafs);
PHP_FUNCTION(sol_GetLeafLinkType);
PHP_FUNCTION(sol_GetLeaf);
PHP_FUNCTION(sol_GetNodeIEntry);
PHP_FUNCTION(sol_GetNodeVerIEntry);
PHP_FUNCTION(sol_GetNodePosition);
PHP_FUNCTION(sol_GetNodeContents8);
PHP_FUNCTION(sol_GetNodeCoordState);
PHP_FUNCTION(sol_GetNodeVerCoordState);
PHP_FUNCTION(sol_GetNodeVersionCount);
PHP_FUNCTION(sol_GetNodeCoordPair);
PHP_FUNCTION(sol_GetNodeVerCoordPair);
PHP_FUNCTION(sol_GetNodePairsCount);
PHP_FUNCTION(sol_GetNodeVerPairsCount);
PHP_FUNCTION(sol_GetNodePairCoord);
PHP_FUNCTION(sol_GetNodeVerPairCoord);
PHP_FUNCTION(sol_GetNodePairState);
PHP_FUNCTION(sol_GetNodeVerPairState);
PHP_FUNCTION(sol_GetNodeContentsLen);




/* __function_declarations_here__ */

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(extname)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(extname)
*/

/* In every utility function you add that needs to use variables 
   in php_extname_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as EXTNAME_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define EXTNAME_G(v) TSRMG(gren_globals_id, zend_gren_globals *, v)
#else
#define EXTNAME_G(v) (gren_globals.v)
#endif

#endif	/* PHP_GREN_H */

/* __footer_here__ */
