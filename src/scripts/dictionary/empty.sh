# The script builds an empty dictionary, version 'PRO'
# More info about dictionary compilation:
# http://solarix.ru/for_developers/bootstrap/compile_dictionary.shtml

./cleanup.sh

set -e

if [ "$OSTYPE" == "darwin10.0" ]
then

 echo "Starting compilation under DARWIN..."
 ../../exemac/compiler -j=2 -optimize -nolinks -dir=../../dictionary.src -outdir=../../bin-mac -ldsize=1000000 -save_seeker -save_affixes -save_prefix_entry_searcher -save_lemmatizer ../../dictionary.src/version-pro ../../dictionary.src/dictionary ../../dictionary.src/common_dictionary_xml ../../dictionary.src/empty_dictionary_xml
 
else

 if [ "$HOSTTYPE" == "x86_64" ]
  then
  
  ../../exe64/compiler -j=2 -optimize -nolinks -dir=../../dictionary.src -outdir=../../bin-linux64 -ldsize=1000000 -save_seeker -save_affixes -save_prefix_entry_searcher -save_lemmatizer ../../dictionary.src/version-pro ../../dictionary.src/dictionary ../../dictionary.src/common_dictionary_xml ../../dictionary.src/empty_dictionary_xml
  
  if [ -d "../../distributives/Dictionary/pro/linux64/empty" ];
   then

    cp ../../bin-linux64/alphabet.bin    ../../distributives/Dictionary/pro/linux64/empty
    cp ../../bin-linux64/diction.bin    ../../distributives/Dictionary/pro/linux64/empty
#    cp ../../bin-linux64/affixes.bin    ../../distributives/Dictionary/pro/linux64/empty
    cp ../../bin-linux64/seeker.bin     ../../distributives/Dictionary/pro/linux64/empty
    cp ../../bin-linux64/lexicon.db  ../../distributives/Dictionary/pro/linux64/empty
    cp ../../bin-linux64/thesaurus.db  ../../distributives/Dictionary/pro/linux64/empty
    cp ../../bin-linux64/dictionary.xml ../../distributives/Dictionary/pro/linux64/empty

   fi 
  
  else
  
  ../../exe/compiler -j=2 -optimize -nolinks -dir=../../dictionary.src -outdir=../../bin-linux -ldsize=1000000 -save_seeker -save_affixes -save_prefix_entry_searcher -save_lemmatizer ../../dictionary.src/version-pro ../../dictionary.src/dictionary ../../dictionary.src/common_dictionary_xml ../../dictionary.src/empty_dictionary_xml
  
  if [ -d "../../distributives/Dictionary/pro/linux/empty" ];
   then

    cp ../../bin-linux/alphabet.bin    ../../distributives/Dictionary/pro/linux/empty
    cp ../../bin-linux/diction.bin    ../../distributives/Dictionary/pro/linux/empty
#    cp ../../bin-linux/affixes.bin    ../../distributives/Dictionary/pro/linux/empty
    cp ../../bin-linux/seeker.bin     ../../distributives/Dictionary/pro/linux/empty
    cp ../../bin-linux/lexicon.db  ../../distributives/Dictionary/pro/linux/empty
    cp ../../bin-linux/thesaurus.db  ../../distributives/Dictionary/pro/linux/empty
    cp ../../bin-linux/dictionary.xml ../../distributives/Dictionary/pro/linux/empty
    
   fi 
  
 fi

fi
