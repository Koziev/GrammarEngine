#ifndef SE_FILE_FILTER__H
#define SE_FILE_FILTER__H
#pragma once

 #include <lem/noncopyable.h>
 #include <lem/streams.h>
  
 namespace Solarix
 {
  namespace Search_Engine
  { 

   class Base_File_Reader;

  // *************************************
  // Базовый класс для фильтров файлов.
  // Base class for file filters.
  // *************************************
  class Base_File_Filter : lem::NonCopyable
  {
   public:
    typedef enum { LT, LE, EQ, NE, GE, GT } CondType;

   protected:
    CondType cond; // условие на фильтр

    typedef enum {
                  REGEX_NAME_FILTER,
                  WILDCARDS_NAME_FILTER,
                  SIZE_FILTER,
                  DATE_FILTER,
                  MODIF_FILTER,
                  AND_FILTER,
                  OR_FILTER
                 } Type;

    Type type;

    void Write_Type( lem::Stream &bin ) const;

   public:
    Base_File_Filter( Type t, CondType Cond );
    virtual ~Base_File_Filter(void);

    virtual bool Check( lem::Stream& file ) const=0; 
    virtual bool Check( const lem::Path &name ) const=0;

    virtual bool Check(
                       lem::Stream::pos64_type Size,
                       const boost::posix_time::ptime &Creat,
                       const boost::posix_time::ptime &Modif
                      ) const=0;

    virtual bool Needs_File(void) const;

    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );

    static Base_File_Filter* Load( lem::Stream &bin );
    void Save( lem::Stream &bin ) const;
  }; 
 }
}
#endif
