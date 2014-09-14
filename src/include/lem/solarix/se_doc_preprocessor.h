#ifndef SE_DOC_PREPROCESSOR__H
#define SE_DOC_PREPROCESSOR__H
#pragma once

 #if !defined FAIND_NO_BOOST_REGEX
 #include <boost/regex.hpp>
 #endif


 namespace Solarix
 {
  namespace Search_Engine
  {

  // *******************************************************************************
  // Базовый класс - препроцессор документов перед их использованием в индексаторе
  // или поисковике.
  // *******************************************************************************
  class Base_File_Reader;
  class Crawler;

  class Doc_Preprocessor
  {
   protected:
    typedef enum { None, Fragment } Type;
    Type type;

   public:
    Doc_Preprocessor(void);

    Doc_Preprocessor( const Doc_Preprocessor &x );

    virtual ~Doc_Preprocessor(void) {}

    virtual void operator=( const Doc_Preprocessor &x );

    static Doc_Preprocessor* create(  const lem::UFString &name, const lem::UFString &arg );
    static Doc_Preprocessor* load_bin( lem::Stream &bin );

    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );
    virtual Solarix::Search_Engine::Base_File_Reader* GetReader( Solarix::Search_Engine::Base_File_Reader* src_reader, Crawler *crawler ) const { LEM_STOPIT; return NULL; }
  };


  #if !defined FAIND_NO_BOOST_REGEX
  class Fragment_Preprocessor : public Doc_Preprocessor
  {
   private: 
    bool between; // режим BETWEEN
    lem::UFString from, to; // границы выделяемого фрагмента
    boost::wregex from_rx, to_rx; // внутреннее представление регэкспов
    bool to_eol; // конец фрагмента - на конце текущей строки

    bool in; // режим IN
    lem::UFString in_pattern;
    boost::wregex in_rx;

   public:
    Fragment_Preprocessor(void);
    Fragment_Preprocessor( const lem::UFString &arg );
    Fragment_Preprocessor( const Fragment_Preprocessor &x );

    virtual void operator=( const Fragment_Preprocessor &x );

    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );
    virtual Solarix::Search_Engine::Base_File_Reader* GetReader( Solarix::Search_Engine::Base_File_Reader* src_reader, Crawler *crawler ) const;
  };
  #endif

 }

}

#endif

