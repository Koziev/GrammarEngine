if [ "$OSTYPE" == "darwin10.0" ]
then

 make install -f makefile.darwin64

else

 if [ "$HOSTTYPE" == "x86_64" ]
 then
  make install -f makefile.linux64
 else
  make install -f makefile.linux
 fi

fi
