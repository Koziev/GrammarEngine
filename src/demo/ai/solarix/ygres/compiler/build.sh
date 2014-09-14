if [ "$OSTYPE" == "darwin10.0" ]
then

 echo "Building COMPILER for Darwin..."
 make -f makefile.darwin64

else

 if [ -d "/tmp/ygres" ];
 then
  echo "."
 else
  mkdir /tmp/ygres
 fi

 if [ "$HOSTTYPE" == "x86_64" ]
 then
  make -f makefile.linux64
  cp compiler ../../../../../exe64
 else
  make -f makefile.linux
  cp compiler ../../../../../exe
 fi

fi


