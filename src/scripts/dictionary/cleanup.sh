
if [ "$OSTYPE" == "darwin10.0" ]
then

 rm ../../bin-mac/*.db
 rm ../../bin-mac/*.bin
 rm ../../bin-mac/NGRAMS
 
else

 if [ "$HOSTTYPE" == "x86_64" ]
  then
 
   rm ../../bin-linux64/*.db
   rm ../../bin-linux64/*.bin
   rm ../../bin-linux64/NGRAMS
  
  else

   rm ../../bin-linux/*.db
   rm ../../bin-linux/*.bin
   rm ../../bin-linux/NGRAMS
  
  fi 

fi
