if [ "$OSTYPE" == "darwin10.0" ]
then

 make clean -f makefile.darwin64

else

 if [ "$HOSTTYPE" == "x86_64" ]
 then
  make clean -f makefile.linux64
 else
  make clean -f makefile.linux
 fi

fi
