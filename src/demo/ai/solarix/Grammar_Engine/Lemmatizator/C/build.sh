if [ "$OSTYPE" == "darwin10.0" ]
then

echo "Darwin..."
export DYLD_LIBRARY_PATH=/Users/Shared/MVoice/lem/libmac
g++ LemmatizatorTool.cpp -L/Users/Shared/MVoice/lem/libmac -R/Users/Shared/MVoice/lem/libmac -arch i386 -l lemma -l dl -o LemmatizatorTool

elif [ "$HOSTTYPE" == "x86_64" ]
then
g++ LemmatizatorTool.cpp -l lemma -march=nocona -l dl -o LemmatizatorTool
else
gcc LemmatizatorTool.cpp -l lemma -l dl -o LemmatizatorTool
fi
