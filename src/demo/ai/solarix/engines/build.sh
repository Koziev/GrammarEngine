if [ "$OSTYPE" == "darwin10.0" ]
then

 make -f makefile.darwin64
 cp /Users/Shared/MVoice/lem/libmac/solarix_grammar_engine.dylib /Users/Shared/MVoice/lem/exemac

else

 if [ -d "/tmp/grammar_engine" ];
 then echo "."
 else mkdir "/tmp/grammar_engine"
 fi

 if [ "$HOSTTYPE" == "x86_64" ]
 then
  make -f makefile.linux64
  cp solarix_grammar_engine.so ../../../../lib64
  cp solarix_grammar_engine.so ../../../../exe64
 else
  make -f makefile.linux
  cp solarix_grammar_engine.so ../../../../lib
  cp solarix_grammar_engine.so ../../../../exe
 fi

fi


