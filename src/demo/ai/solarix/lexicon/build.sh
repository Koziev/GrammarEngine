if [ "$OSTYPE" == "darwin10.0" ]
then

 make -f makefile.darwin64

else

 if [ -d "tmp/lexicon" ];
 then 
  echo "."
 else
  mkdir "/tmp/lexicon"
 fi  

 if [ "$HOSTTYPE" == "x86_64" ]
 then
  make -f makefile.linux64
  cp lexicon ../../../../exe64
 else
  make -f makefile.linux
  cp lexicon ../../../../exe
 fi

fi


