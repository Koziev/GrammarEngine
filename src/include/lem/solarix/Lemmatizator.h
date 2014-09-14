#pragma once
#if !defined SOL_LEMMATIZATOR__H
 #define SOL_LEMMATIZATOR__H

 #include <map>
 #include <lem/smart_pointers.h>
 #include <lem/ptr_container.h>
 #include <lem/path.h>
 #include <lem/ucstring.h>
 #include <lem/streams.h>
 #include <lem/containers.h>
 #include <lem/process.h>
 #include <lem/solarix/LemmatizatorStorage.h>
 #include <lem/solarix/LEMM_NGrams.h>

 namespace Solarix
 {
  class Lemmatizator : public LemmatizatorStorage
  {
   private:
    #if defined LEM_THREADS
    lem::Process::CriticalSection cs;
    #endif

    lem::Ptr<lem::Stream> bin;
    lem::Stream::pos_type norm_ref;
    lem::Stream::pos_type model_pos;
   
    bool model_loaded;
    bool model_available;
    int model_suffix_len;
    std::map<lem::UCString,int> suffix2id;
    std::map<int,lem::UCString> id2suffix;

    lem::MCollect<LEMM_Ngram2> model_ngram2;
    lem::PtrCollect< lem::MCollect<const LEMM_Ngram2*> > gc_2;
    std::map<int, lem::MCollect<const LEMM_Ngram2*>* > tag0_2_ngram2;

    lem::MCollect<LEMM_Ngram2> model_ngram2_1;
    std::map<int, lem::MCollect<const LEMM_Ngram2*>* > tag1_2_ngram2;

    lem::PtrCollect< lem::MCollect<const LEMM_Ngram3*> > gc_3;
    lem::MCollect<LEMM_Ngram3> model_ngram3;
    std::map< std::pair<int,int>, lem::MCollect<const LEMM_Ngram3*>* > tag0_2_ngram3;

    lem::MCollect<LEMM_Ngram3> model_ngram3_1;
    std::map< std::pair<int,int>, lem::MCollect<const LEMM_Ngram3*>* > tag1_2_ngram3;

    lem::MCollect<LEMM_Ngram3> model_ngram3_2;
    std::map< std::pair<int,int>, lem::MCollect<const LEMM_Ngram3*>* > tag2_2_ngram3;

    lem::PtrCollect< lem::MCollect<const LEMM_Ngram4*> > gc_4;
    lem::MCollect<LEMM_Ngram4> model_ngram4;
    std::map< lem::triple<int,int,int>, lem::MCollect<const LEMM_Ngram4*>* > tag0_2_ngram4;

    void BuildIndex();

    lem::UCString GetSuffix( const lem::UCString & word ) const;
    lem::UCString GetSuffixById( int id ) const;
    int MatchSuffix( const lem::UCString & suffix ) const;
    int GetTag( const lem::UCString & word ) const;
    void LemmatizeViaModel( const lem::MCollect<lem::UCString> & words, lem::MCollect<lem::UCString> &lemmas );


    int L_NHASHGROUP;
    lem::Stream::pos_type *group_pos;
    int n_lemma;

    int char_size;   
    lem::MCollect<wchar_t> i2wchar;

    int min_sfx_len, max_sfx_len;
    lem::MCollect< std::pair<lem::UCString /*suffix*/, lem::UCString /*lemma_suffix*/> > suffices;

    lem::UCString GetLemma( int idx );
    void LoadEncodedString( lem::UCString *str, lem::Stream &bin, int compression );
    void LoadString1( lem::CString *str, lem::Stream &bin, int compression );
    void DecodeWord1( const lem::CString & a, lem::UCString & u ) const;
    void EncodeWord1( const lem::UCString & u, lem::CString & a ) const;

    bool fast_search1;
    std::map<wchar_t,int> wchar2i;
    lem::MCollect<lem::CString> lemmas_1;

    lem::MCollect<lem::CString> *lexemes_1;
    lem::MCollect<int> *lexeme2lemma_1;

    void LoadModel();


   public:
    Lemmatizator(void);
    ~Lemmatizator(void);
    void Load( const lem::Path &DbPath, int Flags );

    virtual void Lemmatize( const lem::UCString &word, lem::MCollect<lem::UCString> &lemmas );
    virtual int Lemmatize( const lem::UCString &word, lem::UCString &lemma );
    virtual void Lemmatize( const lem::MCollect<lem::UCString> & words, lem::MCollect<lem::UCString> &lemmas );
  };
 
 }

#endif
