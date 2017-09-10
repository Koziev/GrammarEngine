# The script builds an empty dictionary, version 'PRO'
# More info about dictionary compilation:
# http://solarix.ru/for_developers/bootstrap/compile_dictionary.shtml


./cleanup.sh

set -e

if [ "$OSTYPE" == "darwin10.0" ]
then

 echo "Starting compilation under DARWIN..."
 ../../exemac/compiler -j=2 -dir=../../dictionary.src -outdir=../../bin-mac -ldsize=1000000 -save_paradigmas -save_seeker -save_affixes -save_lemmatizer -save_prefix_entry_searcher ../../dictionary.src/version-pro ../../dictionary.src/dictionary -file=../../dictionary.src/english-language-only.sol ../../dictionary.src/shared-resources ../../dictionary.src/english-lexicon ../../dictionary.src/english-stat ../../dictionary.src/english-thesaurus  ../../dictionary.src/common-syntax  ../../dictionary.src/english-syntax ../../dictionary.src/dictionary-english ../../dictionary.src/common_dictionary_xml
 
else

 if [ "$HOSTTYPE" == "x86_64" ]
 then
 
 ../../exe64/compiler -j=2 -dir=../../dictionary.src -outdir=../../bin-linux64 -ldsize=1000000 -save_paradigmas -save_seeker -save_affixes -save_lemmatizer -save_prefix_entry_searcher ../../dictionary.src/version-pro ../../dictionary.src/dictionary -file=../../dictionary.src/english-language-only.sol ../../dictionary.src/shared-resources ../../dictionary.src/english-lexicon ../../dictionary.src/english-stat ../../dictionary.src/english-thesaurus ../../dictionary.src/common-syntax ../../dictionary.src/english-syntax ../../dictionary.src/dictionary-english ../../dictionary.src/common_dictionary_xml
 
 else
 
 ../../exe/compiler -j=2 -dir=../../dictionary.src -outdir=../../bin-linux -ldsize=1000000 -save_paradigmas -save_seeker -save_affixes -save_lemmatizer -save_prefix_entry_searcher ../../dictionary.src/version-pro ../../dictionary.src/dictionary -file=../../dictionary.src/english-language-only.sol ../../dictionary.src/shared-resources ../../dictionary.src/english-lexicon ../../dictionary.src/english-stat ../../dictionary.src/english-thesaurus ../../dictionary.src/common-syntax ../../dictionary.src/english-syntax ../../dictionary.src/dictionary-english ../../dictionary.src/common_dictionary_xml

 fi

fi
