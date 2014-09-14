// CD->29.06.2008
// LC->29.06.2008

#if !defined SOL_DOCUMENT_TAGS_CACHE__H && defined SOLARIX_PRO
 #define SOL_DOCUMENT_TAGS_CACHE__H
#pragma once

 #include <lem/config.h>
 #include <lem/sqlite/sqlite3.h> 
 #include <lem/path.h>
 #include <lem/ptr_container.h>

 namespace Solarix
 {
  class DocumentTagsCache
  {
   private:
    lem::Path dbfolder;

    struct sqlite3* hdb; // дескриптор открытой БД

    void OpenAndCreateDatabase(void);
    void Begin(void);
    void Commit(void);
    void Rollback(void);

   public:
    DocumentTagsCache( const lem::Path &DbFolder );
    ~DocumentTagsCache(void);

    int FindDocId( const lem::UFString &filename );
    int FindDocId( const lem::UFString &filename, const lem::UFString &location );

    void GetDocAttr( int id_doc, boost::posix_time::ptime &creat, boost::posix_time::ptime &modif, lem::Stream::pos64_type size );

    int /*id_doc*/ AddDoc(
                          const lem::UFString &filename,
                          const lem::UFString &location
                         );

    int /*id_doc*/ AddDoc( const lem::UFString &filename );

    void SetDocAttr(
                    int id_doc,
                    const boost::posix_time::ptime &creat,
                    const boost::posix_time::ptime &modif,
                    lem::Stream::pos64_type size
                   );

    lem::UFString GetTagForFile( int id_doc, const lem::UFString &tag );
    void GetTagsForFile( int id_doc, lem::PtrCollect<lem::UFString> &tag_names, lem::PtrCollect<lem::UFString> &tag_values );
    void GetTagValuesForFile( int id_doc, const lem::UFString &tag, lem::PtrCollect<lem::UFString> &tag_values );

    // Все имеющиеся значения для указанного тега без повторов
    void GetTagValues( const lem::UFString &tag, lem::PtrCollect<lem::UFString> &tag_values );

    void SetTagForFile( int id_doc, const lem::UFString &tag, const lem::UFString &value );
    void AddTagForFile( int id_doc, const lem::UFString &tag, const lem::UFString &value );
    void RemoveTagForFile( int id_doc, const lem::UFString &tag );
    void RemoveTagsForFile( int id_doc );

    bool GetFile( int id_doc, lem::UFString &filename, lem::UFString &location );

    void SearchFiles( const lem::UFString &tag, const lem::UFString &value, lem::MCollect<int> &id_docs );
  };
 } // namespace Solarix

#endif
