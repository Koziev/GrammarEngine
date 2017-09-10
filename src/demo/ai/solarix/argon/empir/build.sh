if [ "$OSTYPE" == "darwin10.0" ]
then

 make -f makefile.darwin64

else

 if [ -d "/tmp/empirika" ];
 then echo "."
 else mkdir "/tmp/empirika"
 fi
  

 if [ "$HOSTTYPE" == "x86_64" ]
 then
  make -f makefile.linux64
  cp empirika ../../../../../exe64
 else
  make -f makefile.linux
  cp empirika ../../../../../exe
 fi

fi


