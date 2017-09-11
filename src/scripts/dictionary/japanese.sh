# More info about dictionary compilation:
# http://solarix.ru/for_developers/bootstrap/compile_dictionary.shtml

./cleanup.sh

set -e

if [ "$OSTYPE" == "darwin10.0" ]
then

 echo "Starting compilation under DARWIN..."
 ../../exe/compiler /j=2 /ldsize=2000000 -optimize -dir=../../dictionary.src -outdir=../../bin-windows -save_seeker -save_affixes -save_prefix_entry_searcher ../../dictionary.src/version-pro ../../dictionary.src/dictionary -file=../../dictionary.src/japanese-language-only.sol ../../dictionary.src/japanese-lexicon ../../dictionary.src/japanese-syntax ../../dictionary.src/dictionary-japanese ../../dictionary.src/common_dictionary_xml
 
else

 if [ "$HOSTTYPE" == "x86_64" ]
 then
 ../../exe64/compiler /j=2 /ldsize=2000000 -optimize -dir=../../dictionary.src -outdir=../../bin-windows64 -save_seeker -save_affixes -save_prefix_entry_searcher ../../dictionary.src/version-pro ../../dictionary.src/dictionary -file=../../dictionary.src/japanese-language-only.sol ../../dictionary.src/japanese-lexicon ../../dictionary.src/japanese-syntax ../../dictionary.src/dictionary-japanese ../../dictionary.src/common_dictionary_xml
 else
 ../../exe/compiler /j=2 /ldsize=2000000 -optimize -dir=../../dictionary.src -outdir=../../bin-windows -save_seeker -save_affixes -save_prefix_entry_searcher ../../dictionary.src/version-pro ../../dictionary.src/dictionary -file=../../dictionary.src/japanese-language-only.sol ../../dictionary.src/japanese-lexicon ../../dictionary.src/japanese-syntax ../../dictionary.src/dictionary-japanese ../../dictionary.src/common_dictionary_xml
 fi

fi

