# API Грамматического Словаря Русского Языка

Набор инструментов и API для работы с русской словарной базой и морфологической моделью для
решения NLP задач на русскоязычных текстах доступен в виде консольных программ и
библиотек для встраивания в код на C/C++, C#, Python, Delphi.

# Установка и компиляция зависимостей

Скачиваем, компилируем и устанавливаем liblbfgs:
```
cd ~
wget https://github.com/downloads/chokkan/liblbfgs/liblbfgs-1.10.tar.gz
tar -xvzf liblbfgs-1.10.tar.gz
cd liblbfgs-1.10
./configure
make
sudo make install
```

Скачиваем, компилируем и устанавливаем crfsuite:
```
cd ~
wget https://github.com/downloads/chokkan/crfsuite/crfsuite-0.12.tar.gz
tar -xvzf crfsuite-0.12.tar.gz
cd crfsuite-0.12
./configure
make
sudo make install
```

Может потребоваться установить sqlite3 библиотеку (если возникнет ошибка "Unable to locate the sqlite3 library"):
```
sudo apt-get install sqlite3 libsqlite3-dev
```

Также может потребоваться установить библиотеки Boost C++:
```
sudo apt-get install libboost-all-dev
```

Установка ncurses, которая необходима для консольных утилит:
```
sudo apt-get install libncurses-dev
```

# Сборка грамматического словаря с помощью CMake

Для сборки необходим компилятор C++, поддерживающий стандарт 11. Я использую VisualStudio 2015 под Windows
и gcc 5.4.0 в Ubuntu 16.04. Все части проекта собираются и используются на 64-битных
платформах. 32-битный вариант давно не проверялся и может не работать.

Далее инструкция по сборке проекта в Ubuntu.

1. Создайте папку build в корне исходников, перейдите туда:
```
mkdir build & cd build
```

2. Запустите генерацию makefile'ов:
```
cmake ..
```

3. Запустите компиляцию:
```
make
```

Примерно через 20 минут все утилиты и so'шки будут собраны и скопированы в каталоги
exe64 и lib64. После этого можно приступать к сборке словаря (см. далее).

Сборка вариантов Парсера вынесена на [отдельную страницу](https://github.com/Koziev/GrammarEngine/tree/master/src/demo/ai/solarix/argon/ParseText/Parser).


# Утилита Compiler для сборки бинарного словаря

Эта утилита нужна, чтобы самостоятельно (пере)собрать словарную базу из исходных текстов
с описанием морфологии и синтаксиса и получить набор бинарных файлов, которые используются
другими утилитами проекта. Подробное описание можно прочитать [тут](http://solarix.ru/solarix.ru/for_developers/bootstrap/compile_dictionary.shtml).

## Компиляция под Windows с помощью MS VisualStudio 2015

В папке [exe64](https://github.com/Koziev/GrammarEngine/tree/master/src/exe64) выложен готовый бинарник compiler.exe, собранный для MS Windows, но Вы
можете самостоятельно собрать его с помощью MS VisualStudio 2015. Проект для сборки
лежит в папке [...\src\demo\ai\solarix\ygres\compiler\ygres_msvc2005](https://github.com/Koziev/GrammarEngine/tree/master/src/demo/ai/solarix/ygres/compiler/ygres_msvc2005)

Так как в проекте стоят ссылки на исходные тексты некоторых библиотек [Boost](http://www.boost.org/), то надо
либо скачать исходники Boost и поправить пути в проекте, либо переделать проект на
линковку со [скомпилированными библиотеками](http://www.boost.org/doc/libs/1_60_0/more/getting_started/windows.html).

В результате компиляции получится исполнимый файл compiler.exe в папке ...\src\exe64

## Компиляция под Ubuntu

Если по каким-то причинам сборка утилиты с помощью CMake вам не подходит, то
можно использовать созданный вручную makefile.

Сборочные файлы находятся в папке [...\src\demo\ai\solarix\ygres\compiler](https://github.com/Koziev/GrammarEngine/tree/master/src/demo/ai/solarix/ygres/compiler).

Перед сборкой создайте временный каталог
```
mkdir /tmp/ygres
```
или другой, изменив соответствующую настройку в файле makefile.linux64

Затем запустите сборку:
```
./build.sh
```

Через некоторое время в папке exe64 появится исполнимый файл *compiler*.

## Тестовая сборка пустого словаря

Для быстрой проверки работоспособности компилятора запустите сборку пустого словаря с помощью
скрипта empty.sh в папке [.../src/scripts/dictionary](https://github.com/Koziev/GrammarEngine/tree/master/src/scripts/dictionary).

В папке .../src/bin-linux64 появятся новые файлы данных diction.bin, lexicon.db и другие.

Сборка пустого словаря под Windows выполняется с помощью скрипта empty.cmd, а результаты
будут записаны в bin-windows64.

## Сборка русской словарной базы

Исходные тексты с описанием морфологии, лексики и синтаксиса [русского языка](http://solarix.ru/for_developers/docs/russian_language.shtml)
находятся в папке [.../src/dictionary.src](https://github.com/Koziev/GrammarEngine/tree/master/src/dictionary.src).

Для сборки русской словарной базы достаточно запустить скрипт russian.sh или russian.cmd
в подкаталоге .../src/scripts/dictionary. Примерно через 30 минут в папке bin-windows64
или bin-linux64 появятся файлы словаря.

## Сборка английской словарной базы и других языковых баз

В репозитории находятся также исходные тексты для сборки английской, французской,
японской и китайской словарных баз. Для получения бинарного словаря необходимо запустить 
соответствующий скрипт в папке [.../src/scripts/dictionary](https://github.com/Koziev/GrammarEngine/tree/master/src/scripts/dictionary):

english.cmd или english.sh  
french.cmd  
japanese.cmd  
chinese.cmd  

Морфологическая модель японского языка сделана в расчете на использование с парсерами
типа [Cabocha](https://taku910.github.io/cabocha/) или [KNP](http://nlp.ist.i.kyoto-u.ac.jp/EN/?KNP).

# Утилита Lexicon

Эта консольная программа позволяет быстро проверить результат сборки словарной базы, описанной в предыдущем
разделе. Запустив ее, Вы можете вводить слова и получать результаты поиска в лексиконе
словарной базы.

Если вы запускаете утилиту lexicon из папки exe64, то она самостоятельно попытается загрузить
словарную базу в папке bin-windows64 или bin-linux64, указывать путь к файлу dictionary.xml
в командной строке в этом случае не нужно.

## Компиляция утилиты Lexicon под Windows с помощью MS VisualStudio 2015

Проект для сборки лежит в папке src\demo\ai\solarix\lexicon

По поводу использования библиотек Boost - см. пояснения для утилиты Compile выше.

В папке [exe64](https://github.com/Koziev/GrammarEngine/tree/master/src/exe64) лежит готовый исполнимый файл [Lexicon.exe](https://github.com/Koziev/GrammarEngine/blob/master/src/exe64/Lexicon.exe), который я собрал по текущей версии исходников
под Win64.

## Компиляция утилиты Lexicon в Ubuntu

Нужно создать временный каталог /tmp/lexicon.

После этого надо перейти в каталог src/demo/ai/solarix/lexicon/ и запустить ./build.sh

После окончания сборки появится исполнимый файл lexicon

# Утилита Syntax

Эта консольная программа является отладчиком синтаксического парсера. Она позволяет
вводить с клавиатуры предложения, запускать парсинг, задавать точки остановки в правилах
разбора, просматривать текущий контекст выполнения синтаксического правила.

## Компиляция утилиты Syntax в Ubuntu

Переходим в каталог с исходниками утилиты Syntax src/demo/ai/solarix/syntax и
запускаем компиляцию:
```
./build.sh
```
После компиляции появится бинарник syntax.

Если при запуске ./syntax появится сообщение, что невозможно найти crfsuite***.so, то
скорее всего поможет такая команда:
```
export LD_LIBRARY_PATH=/usr/local/lib
```
После запуска утилиты можно ввести предложение, которое будет разобрано:
```
eek@ubuntu:~/Solarix/GrammarEngine/src/demo/ai/solarix/syntax$ ./syntax  
Solarix SYNTAX parser debugger ver. 14.15.11192 Standard Linux 4.10.0-32-generic x86_64  (build date Sep  6 2017)  
Loading dictionary from ../../../../bin-linux64/dictionary.xml... ok  
Enter #help to read online help.  

: кошка ловит мышей  
BEGIN  ловит ( кошка, мышей )   END  
```

Команда #tree выведет синтаксическое дерево:
```
: \#tree  
ловит ( ГЛАГОЛ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 ЧИСЛО:ЕД ~МОДАЛЬНЫЙ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ ВИД:НЕСОВЕРШ ~ВОЗВРАТНОСТЬ )  
││                                                                                                                                                              
│└─мышей ( СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:МН РОД:ЖЕН ОДУШ:ОДУШ ПЕРЕЧИСЛИМОСТЬ:ДА ПАДЕЖВАЛ:РОД )                                                                
│                                                                                                                                                               
└──кошка ( СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:ЖЕН ОДУШ:ОДУШ ПЕРЕЧИСЛИМОСТЬ:ДА ПАДЕЖВАЛ:РОД )                                                                 
:   
```

# C API грамматического словаря

Полный перечень процедур в API с описаниями можно найти на [странице](http://www.solarix.ru/for_developers/api/grammar-engine-api.shtml). 

## Компиляция динамической библиотеки

API словаря реализован как динамическая библиотека solarix_grammar_engine.dll на платформе Windows
или solarix_grammar_engine.so для Linux. 

Для сборки с помощью MS VisualStudio 2015 откройте проект [Grammar_Engine_Pro2005.sln](https://github.com/Koziev/GrammarEngine/blob/master/src/demo/ai/solarix/engines/Grammar_Engine_Pro2005.sln)
в папке [.../src/demo/ai/solarix/engines](https://github.com/Koziev/GrammarEngine/tree/master/src/demo/ai/solarix/engines) и
запустите компиляция. По окончании в папке .../src/lib64 появится файл solarix_grammar_engine.dll.

Для компиляции под Ubuntu запустите скрипт build.sh в той же папке.

## Пример использования C API грамматического словаря

Пример на C++ находится в папке [.../src/demo/ai/solarix/Grammar_Engine/SimpleGREN](https://github.com/Koziev/GrammarEngine/tree/master/src/demo/ai/solarix/Grammar_Engine/SimpleGREN).

## Консольный парсер

Парсер - консольная утилита, которая умеет выполнять токенизацию, лемматизацию, частеречную
разметку (part-of-speech tagging), синтаксический разбор с построением дерева (dependency parsing)
и выделение составляющих (chunking). Сборочная инфструкция и подробное описание
порядка запуска вынесено на [отдельную страницу](https://github.com/Koziev/GrammarEngine/tree/master/src/demo/ai/solarix/argon/ParseText/Parser).
Также доступно [описание на сайте проекта](http://solarix.ru/parser.shtml).


