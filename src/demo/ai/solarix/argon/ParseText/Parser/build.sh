if [ "$OSTYPE" == "darwin10.0" ]
then

 make -f makefile.darwin64

else

 if [ -d "/tmp/parser" ]
 then echo "."
 else mkdir "/tmp/parser"
 fi

 if [ "$HOSTTYPE" == "x86_64" ]
 then
  make -f makefile.linux64
  cp parser ../../../../exe64
 else
  make -f makefile.linux
  cp parser ../../../../exe
 fi

fi


