#ifndef FAIND_CLUCENE_CONFIG__H
#define FAIND_CLUCENE_CONFIG__H
#pragma once

 const int CLUCENE_MERGE_FACTOR = 64;

 // максимальное кол-во док-ов в сегменте, участвующем в слиянии.  
 const int CLUCENE_MAX_MERGE_DOCS_WRITER  = 8192; // при создании индекса
 const int CLUCENE_MAX_MERGE_DOCS_UPDATER = 1024; // при обновлении

 #define USE_SOLARIX_READER
#endif


