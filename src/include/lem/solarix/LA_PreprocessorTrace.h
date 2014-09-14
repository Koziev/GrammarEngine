#if !defined LA_PREPROCESSOR_TRACE__H
 #define LA_PREPROCESSOR_TRACE__H

 #include <lem/noncopyable.h>

 namespace Solarix
 {
  class LA_PreprocessorRule;
  class LA_PreprocessorTokRule;
  class LA_CropRule;
  class LA_PreprocessorRule;

  class LA_PreprocessorTrace : lem::NonCopyable
  {
   private:

   public:
    LA_PreprocessorTrace(void) {}
    virtual ~LA_PreprocessorTrace(void) {}

    virtual void LanguageGuessed( const lem::UFString &phrase, int LanguageID )=0;
  };
 }

#endif
