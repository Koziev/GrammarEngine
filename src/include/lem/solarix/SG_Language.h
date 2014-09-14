#if !defined SG_Language__H
 #define SG_Language__H
 
 #include <lem/ucstring.h>
 #include <lem/containers.h>
 #include <lem/ptr_container.h>
 #include <lem/solarix/tree_link.h>
 #include <algorithm>

 namespace lem
 {
  namespace Iridium
  {
   class Macro_Parser;
  }
 }

 namespace Solarix
 {
  class GraphGram;

  struct SG_LanguageParam
  {
   lem::UCString name; // им€ параметра (не-уникальное)
   lem::Collect<lem::UFString> values; // вектор значений (или компонентов значени€)

   SG_LanguageParam(void) {}
   SG_LanguageParam( const SG_LanguageParam &x );
   void operator=( const SG_LanguageParam &x );

   #if defined SOL_SAVEBIN
   void SaveBin( lem::Stream &bin ) const;
   #endif

   #if defined SOL_LOADBIN
   void LoadBin( lem::Stream &bin );
   #endif

   const lem::UFString & GetValue(void) const { return values.front(); }
  };


  // **********************************
  // Natural language descriptor.
  // **********************************
  class SG_Language
  { 
   public:
    int id;        // Unique language id
    lem::UCString name; // language name (Russian, English, etc)
    lem::MCollect<int> alphabet; // List of alphabets id's for this language
    lem::MCollect< std::pair<Tree_Link,int/*id_language*/> > lang_links; // List of links to other languages
    lem::PtrCollect<SG_LanguageParam> params;

   private:
    #if defined SOL_LOADTXT && defined SOL_COMPILER
    lem::UCString c_name; // им€ константы дл€ объ€влени€ id €зыка в C++ файле
    #endif

   public:
    SG_Language(void);
    SG_Language( const SG_Language &x );
    
    void operator=( const SG_Language &x );

    void Copy_Definition( const SG_Language &x );

    int GetId(void) const { return id; }

    inline const lem::UCString& GetName(void) const { return name; }

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt( int Id, lem::Iridium::Macro_Parser& txt, Solarix::GraphGram& gram );
    inline const lem::UCString& get_C_Name(void) const { return c_name; }
    #endif

    inline int get_Id(void) const { return id; }

    const lem::MCollect<int>& GetAlphabets(void) const { return alphabet; }

    // Is this alphabet OK for the language?
    inline bool Find_Alphabet( int id ) const
    { return std::find( alphabet.begin(), alphabet.end(), id )!=alphabet.end(); }

    bool IsMainAlphabet( int id_alphabet ) const;

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream &bin ) const;
    #endif

    #if defined SOL_LOADBIN
    void LoadBin( lem::Stream &bin );
    #endif

    inline const lem::MCollect< std::pair<Tree_Link,int/*id_language*/> >& links(void) const
    { return lang_links; }

    inline bool empty(void) const { return alphabet.empty() && lang_links.empty(); }

    int FindParam( const lem::UCString & name, int ifrom=0 ) const;
    int FindLastParam( const lem::UCString & name ) const;
    const SG_LanguageParam& GetParam( int i ) const { return *params[i]; }

    #if defined SOL_COMPILER
    void SubstParadigmPattern( lem::UFString &pattern ) const;
    #endif
  };

 }
#endif
