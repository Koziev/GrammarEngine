if [ "$OSTYPE" == "darwin10.0" ]
then

 make -f makefile.darwin64

else

 if [ -d "/tmp/lemmatizator" ];
 then echo "."
 else mkdir "/tmp/lemmatizator"
 fi

 if [ "$HOSTTYPE" == "x86_64" ]
 then
  make -f makefile.linux64
  cp lemmatizator.so ../../../../../lib64
 else
  make -f makefile.linux
  cp lemmatizator.so ../../../../../lib
 fi

fi


