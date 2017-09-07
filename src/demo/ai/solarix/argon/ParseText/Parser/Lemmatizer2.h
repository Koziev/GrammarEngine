#if !defined Lemmatizer2__H
#define Lemmatizer2__H

#include <lem/path.h>
#include <lem/ucstring.h>
#include <lem/solarix/morphologymodels.h>

class Lemmatizer2
{
 private:
  bool loaded;

  struct EndingMinMaxLen
  {
   lem::int8_t min_len;
   lem::int8_t max_len;
  };

  std::map< int, EndingMinMaxLen > Xtag2ending_len;

  typedef std::map< lem::UCString/*wordform_ending*/, lem::MCollect< lem::triple<lem::UCString/*wordform_prefix*/,lem::UCString/*lemma_prefix*/,lem::UCString/*lemma_ending*/> > > LEMMA_BUILDERS;
  typedef std::map< int/*tag_id*/, LEMMA_BUILDERS* > XTAG2LEMMA_BUILDER;
  XTAG2LEMMA_BUILDER Xtag2lemma_builder;

  Solarix::ModelCodeBook codebook;

  lem::UCString LoadStr( lem::BinaryReader & rdr );

 public:
 Lemmatizer2();
 ~Lemmatizer2();

 void Load( const lem::Path & model_folder );

 void Lemmatize( const Solarix::Word_Form & wordform, lem::UFString & lemma, Solarix::Dictionary & dict ) const;
};

#endif
