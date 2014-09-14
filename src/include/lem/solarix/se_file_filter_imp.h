#ifndef SE_FILE_FILTER_IMP__H
#define SE_FILE_FILTER_IMP__H
#pragma once


 #if !defined FAIND_NO_BOOST_REGEX
 #include <boost/regex.hpp>
 #endif

 #include <lem/ptr_container.h>

 #include <lem/solarix/se_file_filter.h>
  
 namespace Solarix
 {
  namespace Search_Engine
  { 

  class And_File_Filter : public Base_File_Filter
  {
   public:
    lem::PtrCollect<Base_File_Filter> child;

   public:
    And_File_Filter(void);
    virtual ~And_File_Filter(void);

    inline bool Empty(void) const { return child.empty(); }

    virtual bool Check( lem::Stream& file ) const; 
    virtual bool Check( const lem::Path &name ) const;
    virtual bool Check(
                       lem::Stream::pos64_type Size,
                       const boost::posix_time::ptime &Creat,
                       const boost::posix_time::ptime &Modif
                      ) const;

    virtual bool Needs_File(void) const;
  }; 

  class Or_File_Filter : public Base_File_Filter
  {
   public:
    lem::PtrCollect<Base_File_Filter> child;

   public:
    Or_File_Filter(void);
    virtual ~Or_File_Filter(void);

    inline bool Empty(void) const { return child.empty(); }

    virtual bool Check( lem::Stream& file ) const; 
    virtual bool Check( const lem::Path &name ) const;
    virtual bool Check(
                       lem::Stream::pos64_type Size,
                       const boost::posix_time::ptime &Creat,
                       const boost::posix_time::ptime &Modif
                      ) const;

    virtual bool Needs_File(void) const;
  }; 


   #if !defined FAIND_NO_BOOST_REGEX
  // **********************************************************
  // ‘ильтр файлов по имени - на основе регул€рных выражений.
  // File name filter using regular expressions.
  // **********************************************************
  class Regex_Name_File_Filter : public Base_File_Filter
  {
   private:
    lem::UFString mask; // регул€рное выражение - маска файла
    lem::zeroed<bool> case_sensitive;

    boost::wregex mask_rx; // внутреннее представление регэкспа
  
   public:
    Regex_Name_File_Filter( const lem::UFString &Mask, CondType Cond, bool Case );
    Regex_Name_File_Filter(void);

    virtual bool Needs_File(void) const;

    virtual bool Check( lem::Stream& file ) const; 
    virtual bool Check( const lem::Path &name ) const;
    virtual bool Check(
                       lem::Stream::pos64_type Size,
                       const boost::posix_time::ptime &Creat,
                       const boost::posix_time::ptime &Modif
                      ) const;

    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );
  }; 
  #endif

  // ******************************************
  // File filter - by name (with wildcards).
  // ******************************************
  class Wildcards_Name_File_Filter : public Base_File_Filter
  {
   private:
    lem::UFString mask; // регул€рное выражение - маска файла
    lem::zeroed<bool> case_sensitive;

   public:
    Wildcards_Name_File_Filter( const lem::UFString &Mask, CondType Cond, bool Case );
    Wildcards_Name_File_Filter(void);

    virtual bool Needs_File(void) const;

    virtual bool Check( lem::Stream& file ) const; 
    virtual bool Check( const lem::Path &name ) const;
    virtual bool Check(
                       lem::Stream::pos64_type Size,
                       const boost::posix_time::ptime &Creat,
                       const boost::posix_time::ptime &Modif
                      ) const;

    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );
  }; 

  // **************************
  // ‘ильтр файлов по размеру
  // **************************
  class Size_File_Filter : public Base_File_Filter
  {
   private:
    lem::Stream::pos64_type size;
  
   public:
    Size_File_Filter( lem::Stream::pos64_type Size, CondType Cond );
    Size_File_Filter(void);

    virtual bool Check( lem::Stream& file ) const; 
    virtual bool Check( const lem::Path& ) const;
    virtual bool Check(
                       lem::Stream::pos64_type Size,
                       const boost::posix_time::ptime &Creat,
                       const boost::posix_time::ptime &Modif
                      ) const;

    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );
  }; 


  // *******************************
  // ‘ильтр файлов по дате создани€
  // *******************************
  class Creat_Date_File_Filter : public Base_File_Filter
  {
   private:
    boost::posix_time::ptime date;
    boost::gregorian::date ddate;
    lem::zbool probe_time; // провер€ть также врем€
  
   public:
    Creat_Date_File_Filter(
                           boost::posix_time::ptime &Date,
                           bool hastime,
                           CondType Cond
                          );

    Creat_Date_File_Filter(void);

    virtual bool Check( lem::Stream& file ) const; 
    virtual bool Check( const lem::Path &name ) const;
    virtual bool Check(
                       lem::Stream::pos64_type Size,
                       const boost::posix_time::ptime &Creat,
                       const boost::posix_time::ptime &Modif
                      ) const;

    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );
  }; 

  // **********************************
  // ‘ильтр файлов по дате модификации
  // **********************************
  class Modif_Date_File_Filter : public Base_File_Filter
  {
   private:
    boost::posix_time::ptime date;
    boost::gregorian::date ddate;
    lem::zbool probe_time; // провер€ть также врем€
  
   public:
    Modif_Date_File_Filter(
                           boost::posix_time::ptime &Date,
                           bool hastime,
                           Base_File_Filter::CondType Cond
                          );
    Modif_Date_File_Filter(void);

    virtual bool Check( lem::Stream& file ) const; 
    virtual bool Check( const lem::Path &name ) const;
    virtual bool Check(
                       lem::Stream::pos64_type Size,
                       const boost::posix_time::ptime &Creat,
                       const boost::posix_time::ptime &Modif
                      ) const;

    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );
  }; 

 }
}
#endif
