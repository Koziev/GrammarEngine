if [ "$OSTYPE" == "darwin10.0" ]
then

 make -f makefile.darwin64

else

 if [ -d "/tmp/syntax" ]
 then echo "."
 else mkdir "/tmp/syntax"
 fi

 if [ "$HOSTTYPE" == "x86_64" ]
 then
  make -f makefile.linux64
  cp syntax ../../../../exe64
 else
  make -f makefile.linux
  cp syntax ../../../../exe
 fi

fi


