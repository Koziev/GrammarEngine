#ifndef SE_ACTION_OPTIONS__H
#define SE_ACTION_OPTIONS__H
#pragma once

 #include <lem/ufstring.h>
 #include <lem/containers.h>
 #include <lem/ptr_container.h>
 #include <lem/tuple.h>
 #include <lem/solarix/se_data_miner.h>
 #include <lem/solarix/se_hit_statistics.h>

 namespace Solarix
 {
  namespace Search_Engine
  { 
   class File_Location;
   class Fix_Context;
   struct Query;
   struct Pattern;

   class Base_DataSet_Printer;
   class Base_Report;

  // Опции для формирования результатов.
  struct Action_Options : boost::noncopyable
  {
   lem::UFString command; // исполняемая команда - символы {} заменяются на имя файла
   bool confirm;          // требовать ли подтверждения перед каждым выполнением

   Base_DataSet_Printer *res_dataset; // формирователь файла результатов (Result DataSet)
                                      // через этот объект идет запись результатов поиска
                                      // в файлы разных форматов или передача результатов
                                      // другими способами. 


   #if defined FAIND_AWK  
   Base_DataSet_Printer *awk; // Обработчик AWK-программ
   #endif

//   int hit_count; // счетчик найденных контекстов

   Hit_Statistics hit_count;
   
   lem::UCString sort_field; // по какому полю сортировка результатов
   lem::zeroed<bool> sort_desc; // сортировать в порядке убывания
   lem::MCollect< lem::triple< lem::UFString* /*ZoneName*/, File_Location*, Fix_Context* > > to_sort;

   lem::zbool subst_shares; // в путях найденныъх файлов заменять локальные части на сетевые пути
   lem::zbool got_shares;
   lem::Collect<lem::UFString> shares;
   lem::Collect<lem::UFString> sh_folders;
   void GetLocalShares(void);
   File_Location SubstShares( const File_Location &file );


   #if defined FAIND_REPORTS
   lem::MCollect< Base_Report* > reports; // список создаваемых отчетов
   #endif

   #if defined FAIND_DATAMINE
   lem::PtrCollect< Base_DataMiner > miners; // допобработчики документов
   #endif

   Action_Options(void);
   
   ~Action_Options(void);

   void clear(void);

   // Начало поиска - сведения о запросе
   void Print_DataSet( const Query &q );
   void Print_DataSet( const lem::MCollect<Pattern*> &qlist );

   // В ходе поиска - найден очередной контекст
   void Print_DataSet(
                      const wchar_t *ZoneName,
                      const File_Location &file,
                      const Fix_Context *ctx
                     );

   // Поиск завершен - вызывается данный метод с некоторой итоговой статистикой
   void Print_DataSet( const Hit_Statistics &hits, const Query &q );

   bool CanShowRawFileList(void) const;
   void PrintRaw( const wchar_t *ZoneName, const File_Location &where );

   void PrintSimple( const UFString &str, const UFString &format );
  };
 }
}
#endif

