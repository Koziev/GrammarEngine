#ifndef IDX_INDEXER_ACTIVE_READER__H
#define IDX_INDEXER_ACTIVE_READER__H
#pragma once

 #if defined FAIND_INDEXER_CLUCENE || FAIND_INDEXER_WDS

 #include <lem/solarix/se_indexer.h>
 #include <lem/solarix/se_text.h>
 #include <lem/solarix/se_crawler_operation.h>


 namespace Solarix
 {
  namespace Search_Engine
  {
  
   class IndexActiveReader : public Indexer
   {
    protected:
     Crawler_Operation engine_command;
     int phrase_distance;

     virtual Assoc_Files* GetAssocFilesForPhrase( const lem::UFString &phrase, int distance, int maxhitcount, const Pattern &pattern )=0;
     virtual Assoc_Files* GetAssocFiles( const UCString &word, bool Prefix, int maxhitcount, const Pattern &pattern )=0; // поиск по одному слову
     virtual Assoc_Files* GetAssocFiles( const MCollect<UCString> &words, int maxhitcount, const Pattern &pattern )=0; // поиск по альтернативным словам (OR)

     virtual bool CanPerformActiveFilesearch( const Pattern &pattern ) const;
     virtual Assoc_Files* PerformActiveFilesearch( const Pattern &pattern );
     
     Assoc_Files* GetAssocFilesForQueryWord( const Word *word, int maxhitcount, const Pattern &pattern );

    public:
     IndexActiveReader(
                       IndexManager *Manager,
                       const Domain_Info &Domain_info,
                       Solarix::Dictionary *ptrDict,
                       const LD_Seeker *seeker,
                       const Echo_Options *Echo,
                       const General_Options *Generals
                      );

     virtual Assoc_Files* GetAssocFiles( int super_index );
     virtual Assoc_Files* GetAssocFiles(
                                        int super_index1,
                                        int super_index2
                                       );

     virtual bool LoadDocumentIndex( File_Entry *file_entry );

     virtual void PreparePrefetchingKeywords(void);
     virtual void FinishPrefetchingKeywords(void);
     virtual void PrefetchKeyword( const UCString &Word );

     virtual Document_Index* CreateDocIndex(void) const;

     #if defined FAIND_DATAMINE
     virtual boost::shared_ptr<Doc_Topic> LoadDocumentTopic( int i_file );
     #endif

     virtual bool FindIndex(
                            const File_Location &loc,
                            File_Entry **entry,
                            bool &broken,
                            bool do_load=true
                           );

     virtual bool DoesSupportMorphology(void) const;
     virtual bool SupportSolarixKeywordsDictionary(void) const;
     virtual bool IsActiveSearcher( const Pattern &pattern ) const;

     virtual Assoc_Files* GetAssocFiles( const Pattern &pattern );

     virtual int FindKeywordSlow( const UCString &Word, Morphology morph ) const;
     virtual void FindKeywordsSlow(
                                   const UCString &Word,
                                   Fuzzy_Comparator *equator,
                                   std::set<int> &result
                                  ) const;
   };

  }
 }


#endif

#endif
