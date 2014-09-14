#ifndef SE_HIT_STATISTICS__H
#define SE_HIT_STATISTICS__H
#pragma once
 
 namespace Solarix
 {
  namespace Search_Engine
  { 

  // *****************************************************************************
  // Статистика по обработке запроса - в ней накапливаются сведения о количестве
  // обработанных файлов и т.д.
  // *****************************************************************************
  struct Hit_Statistics
  {
   lem::zeroed<int> hits;    // сколько контекстов зафиксировано
   lem::zeroed<int> files;   // сколько файлов обработано
   lem::zeroed<int> folders; // сколько каталогов обработано (не считая стартовый)
   lem::zeroed<int> packs;   // сколько архивов обработано
   lem::zeroed<int> sites;   // сколько сайтов просканировано
   lem::zeroed<int> uris;    // сколько документов получено из Интернета
   lem::zeroed<int> pipes;   // сколько именованных каналов прослушано.

   boost::posix_time::ptime started;  // когда начат поиск
   boost::posix_time::ptime stopped; // когда поиск закончен

   Hit_Statistics(void) {}

   void clear(void);

   const lem::UFString Get_XML(void) const;
   const lem::UFString Get_HTML(void) const;

   void Started(void);
   void Stopped(void);
   int Elapsed(void) const;

   inline void Success(void) { hits++; }
  };

 }
}

#endif
