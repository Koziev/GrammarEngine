# The script builds the Russian dictionary (lexicon)
# More info about dictionary compilation:
# http://solarix.ru/for_developers/bootstrap/compile_dictionary.shtml

./cleanup.sh

set -e

if [ "$OSTYPE" == "darwin10.0" ]
then

echo "Starting compilation under DARWIN..."
../../exemac/compiler -j=2 -optimize -dir=../../dictionary.src -outdir=../../bin-mac -ldsize=3000000 -save_paradigmas -save_seeker -save_affixes -save_lemmatizer -save_prefix_entry_searcher ../../dictionary.src/version-pro ../../dictionary.src/dictionary -file=../../dictionary.src/russian-language-only.sol ../../dictionary.src/shared-resources ../../dictionary.src/russian-lexicon ../../dictionary.src/russian-stat ../../dictionary.src/russian-thesaurus ../../dictionary.src/lemm_model.files ../../dictionary.src/common-syntax ../../dictionary.src/russian-syntax ../../dictionary.src/dictionary-russian ../../dictionary.src/common_dictionary_xml
 
else

 if [ "$HOSTTYPE" == "x86_64" ]
 then
 
 ../../exe64/compiler -j=2 -optimize -dir=../../dictionary.src -outdir=../../bin-linux64 -ldsize=3000000 -save_paradigmas -save_seeker -save_affixes -save_lemmatizer -save_prefix_entry_searcher ../../dictionary.src/version-pro ../../dictionary.src/dictionary -file=../../dictionary.src/russian-language-only.sol ../../dictionary.src/shared-resources ../../dictionary.src/russian-lexicon ../../dictionary.src/russian-stat ../../dictionary.src/russian-thesaurus ../../dictionary.src/lemm_model.files ../../dictionary.src/common-syntax ../../dictionary.src/russian-syntax ../../dictionary.src/dictionary-russian ../../dictionary.src/common_dictionary_xml
 
 else
 
 ../../exe/compiler -j=2 -optimize -dir=../../dictionary.src -outdir=../../bin-linux -ldsize=3000000 -save_paradigmas -save_seeker -save_affixes -save_lemmatizer -save_prefix_entry_searcher ../../dictionary.src/version-pro ../../dictionary.src/dictionary -file=../../dictionary.src/russian-language-only.sol ../../dictionary.src/shared-resources ../../dictionary.src/russian-lexicon ../../dictionary.src/russian-stat ../../dictionary.src/russian-thesaurus ../../dictionary.src/lemm_model.files ../../dictionary.src/common-syntax ../../dictionary.src/russian-syntax ../../dictionary.src/dictionary-russian ../../dictionary.src/common_dictionary_xml
 
 fi

fi
