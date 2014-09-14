#if !defined SG_CASING_CODER__H
 #define SG_CASING_CODER__H

 #include <lem/noncopyable.h>
 #include <lem/RWULock.h>
 #include <lem/process.h>
 #include <lem/containers.h>

 namespace Solarix
 {
  class SynGram;
  class GG_CharOperation;

  class CasingCoder : lem::NonCopyable
  {
   private:
    SynGram &SG;

    int x( int i ) const;

    struct XLAT : lem::NonCopyable
    {
     lem::MCollect<int> id_langs;
     bool use_unicode;
     lem::MCollect<const GG_CharOperation*> lower_xlat, upper_xlat;
    };

    #if defined LEM_THREADS
    lem::Process::RWU_Lock cs, cs_class_default_casing;
    #endif    

    XLAT *default_xlat;
    lem::MCollect<XLAT*> xlats;
    std::map<int,XLAT*> lang2xlat;

    std::map< int /*id_class*/, int /*default_casing*/ > class2casing;

    const XLAT * GetXLAT( int ekey );

    void AddLower( const XLAT *xlat, lem::uint32_t src_ch, lem::UFString &res ) const;
    void AddUpper( const XLAT *xlat, lem::uint32_t src_ch, lem::UFString &res ) const;

   public:
    int icoord_casing;
    int Lower, FirstCapitalized, Upper, EachLexemCapitalized;
    int UnknownEntries_ekey;

    CasingCoder( SynGram &sg );
    ~CasingCoder(void);

    void RestoreCasing( int external_casing_state, lem::UFString &res, int ekey=UNKNOWN );
    void RestoreCasing( lem::UFString &res, int ekey );
  };

 }

#endif

