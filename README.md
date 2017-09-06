## Компиляция утилиты Lexicon в Ubuntu

Для успешной компиляции необходимо иметь установленные dev-версии библиотек ncurses и sqlite.
Их можно установить такими командами в консоли:

sudo apt-get install libncurses-dev  
sudo apt-get install sqlite3 libsqlite3-dev  

Также нужно создать временный каталог /tmp/lexicon.

После этого надо перейти в каталог src/demo/ai/solarix/lexicon/ и запустить ./build.sh

После окончания сборки появится исполнимый файл lexicon


## Компиляция утилиты Syntax в Ubuntu

Скачиваем библиотеку liblbfgs либо из гитхаба

git clone https://github.com/chokkan/liblbfgs

Либо берем tar.gz архив и распаковываем:

mkdir lbfgs
tar -xf liblbfgs-1.10.tar.gz -C ./lbfgs
cd lbfgs/liblbfgs-1.10

Далее сборка:

./configure
make
sudo make install

Аналогичные шаги делаем для CRFSuite. Берем ее из репозитория

git clone https://github.com/chokkan/crfsuite

Либо скачиваем и распаковываем tar.gz:

mkdir crfsuite
tar -xf crfsuite-0.12.tar.gz -C ./crfsuite
cd crfsuite/crfsuite-0.12

Далее сборка:

./configure
make
sudo make install

Теперь переходим в каталог с исходниками утилиты Syntax src/demo/ai/solarix/syntax и
запускаем компиляцию:

./build.sh

После компиляции появится бинарник syntax.

Если при запуске ./syntax появится сообщение, что невозможно найти crfsuite***.so, то
скорее всего поможет такая команда:

export LD_LIBRARY_PATH=/usr/local/lib

После запуска утилиты можно ввести предложение, которое будет разобрано:

eek@ubuntu:~/Solarix/GrammarEngine/src/demo/ai/solarix/syntax$ ./syntax
Solarix SYNTAX parser debugger ver. 14.15.11192 Standard Linux 4.10.0-32-generic x86_64  (build date Sep  6 2017)
Loading dictionary from ../../../../bin-linux64/dictionary.xml... ok
Enter #help to read online help.

: кошка ловит мышей
BEGIN  ловит ( кошка, мышей )   END


Команда #tree выведет синтаксическое дерево:

: #tree
ловит ( ГЛАГОЛ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 ЧИСЛО:ЕД ~МОДАЛЬНЫЙ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ ВИД:НЕСОВЕРШ ~ВОЗВРАТНОСТЬ )
││                                                                                                                                                            
│└─мышей ( СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:МН РОД:ЖЕН ОДУШ:ОДУШ ПЕРЕЧИСЛИМОСТЬ:ДА ПАДЕЖВАЛ:РОД )                                                              
│                                                                                                                                                             
└──кошка ( СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:ЖЕН ОДУШ:ОДУШ ПЕРЕЧИСЛИМОСТЬ:ДА ПАДЕЖВАЛ:РОД )                                                               
: 
