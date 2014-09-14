#ifndef SE_GENERAL_OPTIONS__H
#define SE_GENERAL_OPTIONS__H
#pragma once

 #include <lem/noncopyable.h>
 #include <lem/path.h>
 #include <lem/containers.h>
 #include <lem/zeroed.h>

 namespace Solarix
 {
  namespace Search_Engine
  {

   struct ResultPageTemplate
   {
    lem::zbool use;

    lem::UFString header;

    lem::UFString query_form; // форма для ввода запросов

    lem::UFString hits_begin; // теги перед началом списка результатов поиска
    lem::UFString row; // оформление одного хита в списке результатов
    lem::UFString hits_end; // теги после списка результатов поиска

    lem::UFString stat; // шаблон для вывода статистики поиска
   };

   // **********************************************************
   // Группа прочих опций, влияющих на работу поисковой машины
   // в целом, например - пути к файлам с внешними компонентами.
   // **********************************************************
   struct General_Options : lem::NonCopyable
   {
    lem::Path prog_path; // каталог (полный абсолютный путь), в котором находится exe
    lem::Path raw_reader_kb; // файл с базой знаний для Raw Reader'а
    lem::zbool needs_dictionary;   // нужно загружать словарь
    lem::zbool needs_thesaurus;    // нужен тезаурус
    lem::zbool lemmatizer_only;    // если из словарных модулей нужен только лемматизатор
    lem::zbool needs_classifier;   // нужно инициализировать рубрикатор
   
    lem::Path work_dir; // основной рабочий каталог (для сохранения индекса,
                        // файлов истории и т.д.)

    // Пути к файлам загружаемых модулей
    lem::Path dictionary_filename;
    lem::Path stopwords_filename;
    lem::Path log_filename;
    lem::Path topic_db_files; // путь к каталогу с файлами СУБД рубрикатора
    lem::Path ini_path; // путь к файлу, из которого считана конфигурация

    lem::UFString dict_langs_str; // список языков, для которых загружаются лексиконы и т.д.
    lem::MCollect<lem::UCString> dict_langs;

    lem::zbool allow_plugins; // разрешать ли загрузку и использование плагинов
    lem::Path plugins_path; // общий путь к плагинам
    bool append_plugin_subfolders; // если плагины в зависимости от типа будем искать в ...\formats, ...\media и так далее

    lem::zbool save_files; // Можно ли сохранять файлы истории, оставлять следы
                                  // в каталогах индексатора и т.д. (для работы на флэшке).

    lem::zbool start_httpd;  // запускать HTTP сервер для обслуживания запросов от гаджетов
    lem::FString httpd_ip; // на каком интерфейсе запускать HTTPD
    lem::zeroed<int> httpd_port; // на каком порту

    ResultPageTemplate result_page; // шаблон для формирования страницы результатов поиска веб-сервером
    lem::UFString hidden_query_fields; // скрытые поля на форме поискового запроса

    bool use_text_cache; // использовать кэш текста для сохранения результатов извлечения текста с помощью OCR

    General_Options(void); 

    inline bool All_Languages(void) const { return dict_langs_str==L'*'; }

    inline bool Accept_Language( const lem::UCString &lang ) const
    {
     return All_Languages() ||
            std::find( dict_langs.begin(), dict_langs.end(), lang )!=dict_langs.end(); 
    } 
   }; 

  }
 }
#endif
