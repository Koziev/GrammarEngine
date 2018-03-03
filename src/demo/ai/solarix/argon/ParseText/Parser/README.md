# Parser - частеречная разметка, лемматизация и синтаксический разбор

Парсер выполняет базовые задачи для текста на русском (или другом, поддерживаемом словарной базой
и моделями) языке:

* Частеречная разметка (part-of-speech tagging)  
* Построение синтаксического дерева зависимостей (dependency parsing)  
* Разбивка на глагольные/именные составляющие первого уровня (chunking)  
* Лемматизация  
* Токенизация с учетом неоднозначностей для составных слов  

## Словарная база и языковые модели

Для работы Парсера необходима словарная база и файлы данных моделей, полученных
применением алгоритмов машинного обучения для больших размеченных корпусов. Готовые
файлы моделей для русского языка можно взять из [каталога в репозитории](https://github.com/Koziev/GrammarEngine/tree/master/src/bin-windows64).
Сборка русской словарной базы из [исходников](https://github.com/Koziev/GrammarEngine/tree/master/src/dictionary.src) описана
на [главной странице](https://github.com/Koziev/GrammarEngine).

Кроме того, архив с полностью готовыми файлами парсера можно взять на [сайте проекта](http://www.solarix.ru/parser.shtml).

Путь к файлу dictionary.xml словарной базы задается опцией "-d path". По умолчанию файлы
языковых моделей лежат в том же каталоге, что и сама словарная база, хотя это можно
изменить, задавая относительные пути для элементов под тегом <models> в dictionary.xml.

## Сборка из исходников

Под MS Windows для компиляции парсера можно использовать готовое решение для VisualStudio 2015 - файл Parser64.sln в [каталоге](https://github.com/Koziev/GrammarEngine/blob/master/src/demo/ai/solarix/argon/ParseText/Parser/Parser64.sln).
В этом решении собраны проекты для сборки консольной версии парсера (Parser) и модуля для Питона (PyParser).

Предварительно надо скачать и собрать [библиотеки Boost](http://www.boost.org). На момент
написания инструкции текущей версией Boost была 1.66, для нее процесс выглядит примерно так ([здесь](http://www.boost.org/doc/libs/1_52_0/more/getting_started/windows.html) есть
официальная дока).  

1) Скачиваем и распаковываем архив с исходниками отсюда http://www.boost.org/users/history/version_1_66_0.html.

2) Открываем консоль.

3) Возможно, потребуется инициализировать переменные среды для VisualStudio, для этого
при установленной версии 2015 запускаем
```
"c:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64
```

4) Собираем инструменты для сборки буста, для этого переходим в кореневой каталог, куда
был распакован архив буста и выполняем:
```
bootstrap.bat
```

5) Запускаем сборку библиотек буста:
```
bjam -j4 --build-type=complete architecture=x86 address-model=64 link=static stage
```

6) Далее можно скопировать собранные файлы библиотек в новый отдельный каталог, либо
линковаться с подкаталогом ...\stage\lib. В проекте сборки парсера не забудьте указать путь
к этому каталогу в свойствах линкера вместо моего значения e:\boost.1.66\stage\lib\.

## Установка собранного модуля pyparser

Все pyd и dll файлы, необходимые для работы с парсером в питоне, собраны в подкаталоге pyparser.
Для удобства использования в птоновском коде модуль pyparser необходимо установить
с помощью pip. Для этого перейдите внутрь каталога src репозитория (там можно увидеть файл setup.py)
и выполните 
```
pip install .
```

Далее можно запустить интерпретатор питона python и выполнить в нем следующий код:

```
from __future__ import print_function

from pyparser import PyParser

p = PyParser()
p.load(u'e:/mvoice/lem/bin-windows64/dictionary.xml', 0, -1)

tokens = p.tag1(u'кошки спят на веранде', True, False)
for token in tokens:
    print(u'{}\t{}\t{}'.format(token[0], token[1], token[2]))

```

Метод PyParser.load загружает словарную базу по указанному файлу конфигурации, поэтому
потребуется скорректировать путь. Метод PyParser.tag1 разбирает одно предложение,
переданное как юникодная строка, и возвращает список кортежей. Каждый кортеж
имеет 4 элемента: исходное слово, лемма, часть речи и список пар тег+значение для
морфологических признаков слова.

## Результаты разбора

Консольный вариант парсера сохраняет результаты разбора в указанном XML файле (если указана опция -o имя_файла) или выводит
их прямо в консоль (по умолчанию).

Например, предложение "Совещание происходило на квартире генерала Науменко." в результате
работы чанкера (опция -parser 2) даст такой результат:

```
<chunks>
 <token word_index='0' is_chunk_starter='1'/>
 <token word_index='1' is_chunk_starter='1'/>
 <token word_index='2' is_chunk_starter='1'/>
 <token word_index='3' is_chunk_starter='0'/>
 <token word_index='4' is_chunk_starter='0'/>
 <token word_index='5' is_chunk_starter='0'/>
 <token word_index='6' is_chunk_starter='1'/>
</chunks>
```

Атрибут is_chunk_starter для каждого входного слова определяет, является
ли слово первым в отдельной группе, прикрепляемой к корню:

![chunking](chunking.png)

В данном случае видно, как отдельная группа слов для предложного обстоятельства
"на квартире генерала Науменко" образует отдельную группу, в которой первое слово,
предлог "на", помечен атрибутом is_chunk_starter='1', а остальные помечены
атрибутом is_chunk_starter='0'.


## Примеры запуска

Парсер реализован как консольная программа. Режим обработки текста задается
аргументами командной строки.

Только частеречная разметка текста (-tagger 0) в файле (-i ...), где каждая строка соответствует одному
предложению (опция -eol):

```
parser -verbose -tagger 0 -eol -d ../ru/dictionary.xml -i input.txt -o output.xml
```

Частеречная разметка, синтаксический разбор и лемматизация:

```
parser -verbose -tagger 0 -parser 0 -lemmatizer 0 -eol -d ../ru/dictionary.xml -i input.txt -o output.xml
```

Разбивка на составляющие для текста, который надо по ходу разбора разбивать на предложения:

```
parser -verbose -tagger 0 -parser 2 -d ../ru/dictionary.xml -i input.txt -o output.xml
```

## Тренеры моделей

Парсер использует статистические модели для лемматизации, частеречной разметки и парсинга,
обучая их на большом корпусе размеченных в ручную текстов. Исходный текст программ, выполняющих
обучение, также доступен в репозитории:

[part-of-speech tagger model trainer](https://github.com/Koziev/GrammarEngine/tree/master/src/demo/ai/solarix/argon/DisambigRuleBuilder/POSTaggerDatasetBuilder)  
[chunker model trainer](https://github.com/Koziev/GrammarEngine/tree/master/src/demo/ai/solarix/argon/DisambigRuleBuilder/ShallowParserDatasetBuilder)  
[lemmatizer model trainer](https://github.com/Koziev/GrammarEngine/tree/master/src/demo/ai/solarix/argon/DisambigRuleBuilder/LemmatizerDatasetBuilder)
[dependency parsing model trainer](https://github.com/Koziev/GrammarEngine/tree/master/src/demo/ai/solarix/argon/DisambigRuleBuilder/DisambigRuleBuilder)  




