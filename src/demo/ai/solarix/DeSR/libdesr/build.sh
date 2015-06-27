if [ "$OSTYPE" == "darwin10.0" ]
then

 make -f makefile.darwin64

else

 if [ -d "/tmp/libdesr" ];
 then echo "."
 else mkdir "/tmp/libdesr"
 fi

 if [ "$HOSTTYPE" == "x86_64" ]
 then
  make -f makefile.linux64
  cp libdesr.a ../../../../../lib64
 else
  make -f makefile.linux
  cp libdesr.a ../../../../../lib
 fi

fi


