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
  cp libdesr.so ../../../../../lib64
 else
  make -f makefile.linux
  cp libdesr.so ../../../../../lib
 fi

fi


