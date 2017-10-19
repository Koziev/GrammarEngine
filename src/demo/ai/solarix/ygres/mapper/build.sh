if [ -d "/tmp/ymap" ];
then echo ""
else mkdir /tmp/ymap
fi
 
make -f makefile.linux64
cp decompiler ../../../../../exe64
