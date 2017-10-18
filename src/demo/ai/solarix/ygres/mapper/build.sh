if [ "$OSTYPE" == "darwin10.0" ]
then

 make -f makefile.darwin64

else

 if [ -d "/tmp/ymap" ];
 then echo ""
 else mkdir /tmp/ymap
 fi
 
 if [ "$HOSTTYPE" == "x86_64" ]
 then
  make -f makefile.linux64
  cp decompiler ../../../../../exe64
 else
  make -f makefile.linux
  cp decompiler ../../../../../exe
 fi

fi
