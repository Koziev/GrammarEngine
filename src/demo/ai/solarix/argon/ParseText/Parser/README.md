# Parser

Выполняет базовые задачи для текста на русском (или другом, поддерживаемом словарной базой
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

Под MS Windows для компиляции парсера можно использовать [проект для VisualStudio 2015](https://github.com/Koziev/GrammarEngine/blob/master/src/demo/ai/solarix/argon/ParseText/Parser/Parser64.sln).

## Результаты разбора

Парсер сохраняет результаты разбора в указанном XML файле (опция -o имя_файла) или выводит
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
[dependency parsing model trainer](https://github.com/Koziev/GrammarEngine/tree/master/src/demo/ai/solarix/argon/DisambigRuleBuilder/DisambigRuleBuilder)  






