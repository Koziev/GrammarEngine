if [ -d "/tmp/lemmatizator" ];
then echo "."
else mkdir "/tmp/lemmatizator"
fi

make -f makefile.linux64
cp lemmatizator.so ../../../../../lib64
