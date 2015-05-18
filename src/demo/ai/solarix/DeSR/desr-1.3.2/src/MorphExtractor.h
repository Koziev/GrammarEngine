/*
**  DeSR
**  src/MorphExtractor.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2005  Giuseppe Attardi (attardi@di.unipi.it).
**  ----------------------------------------------------------------------
**
**  This file is part of DeSR.
**
**  DeSR is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License, version 3,
**  as published by the Free Software Foundation.
**
**  DeSR is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**  ----------------------------------------------------------------------
*/

#ifndef DeSR_MorphExtractor_H
#define DeSR_MorphExtractor_H

#include "text/RegExp.h"

namespace Tanl {

/**
 *	@ingroup parser
 *
 *	Functional interface for extractors of morphological features.
 */
struct MorphExtractor
{
  MorphExtractor() { }

  struct Features {
    Features() {
      Case[0] = '\0';
      extra[0] = '\0';
      gender[0] = '\0';
      mode[0] = '\0';
      subcat[0] = '\0';
      negative[0] = '\0';
      number[0] = '\0';
      person[0] = '\0';
      tense[0] = '\0';
      trans[0] = '\0';
      full[0] = '\0';
    }

    char Case[20];		///< case
    char extra[20];		///< extra values
    char gender[20];		///< gender
    char mode[20];		///< mode (active/passive)
    char subcat[20];		///< subcat (see below)
    char negative[20];		///< negative
    char number[20];		///< number
    char person[20];		///< person
    char tense[20];		///< verb tense
    char trans[20];		///< transitive verb (or root verb)
    char full[256];		///< combined morpho features
  };

  virtual void operator() (char const* start, char const* end,
			   Features& mf) const;
};

/**
 *	@ingroup parser
 */
struct ArabicMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reCase;
  static Tanl::Text::RegExp::Pattern reGender;
  static Tanl::Text::RegExp::Pattern reNumber;
  static Tanl::Text::RegExp::Pattern rePerson;

  void operator() (char const* start, char const* end, Features& mf) const;
};

/**
 *	@ingroup parser
 */
struct BasqueMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reNumber;

  BasqueMorphExtractor() {}

  void operator() (char const* start, char const* end, Features& mf) const;
};

/**
 *	@ingroup parser
 */
struct BulgarianMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reGender;
  static Tanl::Text::RegExp::Pattern reNumber;
  static Tanl::Text::RegExp::Pattern rePerson;

  void operator() (char const* start, char const* end, Features& mf) const;
};

/**
 *	@ingroup parser
 */
struct CzechMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reCase;
  static Tanl::Text::RegExp::Pattern reGender;
  static Tanl::Text::RegExp::Pattern reNumber;
  static Tanl::Text::RegExp::Pattern rePerson;
  static Tanl::Text::RegExp::Pattern reNegative;
  static Tanl::Text::RegExp::Pattern reGra;

  void operator() (char const* start, char const* end, Features& mf) const;
};

/**
 *	@ingroup parser
 */
struct DanishMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reGender;
  static Tanl::Text::RegExp::Pattern reNumber;
  static Tanl::Text::RegExp::Pattern rePerson;
  static Tanl::Text::RegExp::Pattern reCase;

  void operator() (char const* start, char const* end, Features& mf) const;
};

/**
 *	@ingroup parser
 */
struct DutchMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reGender;
  static Tanl::Text::RegExp::Pattern reNumber;
  static Tanl::Text::RegExp::Pattern rePerson;
  static Tanl::Text::RegExp::Pattern reCase;

  void operator() (char const* start, char const* end, Features& mf) const;
};

/**
 *	@ingroup parser
 */
struct FrenchMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reGender;
  static Tanl::Text::RegExp::Pattern reNumber;
  static Tanl::Text::RegExp::Pattern rePerson;
  /**
     Subcategories.
     Adjective:
     <ul>
       <li>qual</li>
       <li>poss</li>
       <li>card</li>
       <li>ord</li>
       <li>ind</li>
       <li>int</li>
     </ul>
     Adverb:
     <ul>
       <li>int</li>
       <li>neg</li>
       <li>excl</li>
     </ul>
     Conjunct:
     <ul>
       <li>C</li>
       <li>S</li>
      </ul>
     Weak clitic:
     <ul>
       <li>suj</li>
       <li>obj</li>
       <li>refl</li>
     </ul>
     Determiner:
     <ul>
       <li>dem</li>
       <li>def</li>
       <li>ind</li>
       <li>part</li>
       <li>card</li>
       <li>neg</li>
       <li>poss</li>
       <li>excl</li>
       <li>int</li>
     </ul>
     Pronoun:
     <ul>
       <li>rel</li>
       <li>int</li>
       <li>card</li>
       <li>pers</li>
       <li>neg</li>
       <li>ind</li>
       <li>poss</li>
       <li>dem</li>
       <li>refl</li>
     </ul>
     Punctuation:
     <ul>
       <li>W</li>
       <li>S</li>
     </ul>
   */
  static Tanl::Text::RegExp::Pattern reSubcat;

  void operator() (char const* start, char const* end, Features& mf) const;
};

// ======================================================================
// German

/**
 *	@ingroup parser
 */
struct GreekMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reGender;
  static Tanl::Text::RegExp::Pattern reNumber;
  static Tanl::Text::RegExp::Pattern rePerson;
  static Tanl::Text::RegExp::Pattern reCase;

  void operator() (char const* start, char const* end, Features& mf) const;
};

/**
 *	@ingroup parser
 */
struct HungarianMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reNumber;
  static Tanl::Text::RegExp::Pattern rePerson;
  static Tanl::Text::RegExp::Pattern reCase;

  void operator() (char const* start, char const* end, Features& mf) const;
};

/**
 *	@ingroup parser
 */
struct IndianMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reCase;
  static Tanl::Text::RegExp::Pattern reGender;
  static Tanl::Text::RegExp::Pattern reNumber;
  static Tanl::Text::RegExp::Pattern rePerson;
  static Tanl::Text::RegExp::Pattern reVibhakti;
  static Tanl::Text::RegExp::Pattern reTam;

  void operator() (char const* start, char const* end, Features& mf) const;
};

/**
 *	@ingroup parser
 */
struct ItalianMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reGender;
  static Tanl::Text::RegExp::Pattern reMode;
  static Tanl::Text::RegExp::Pattern reNumber;
  static Tanl::Text::RegExp::Pattern rePerson;
  static Tanl::Text::RegExp::Pattern reTense;

  void operator() (char const* start, char const* end, Features& mf) const;
};

/**
 *	@ingroup parser
 */
struct ItalianTutMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reCase;
  static Tanl::Text::RegExp::Pattern reGender;
  static Tanl::Text::RegExp::Pattern reMode;
  static Tanl::Text::RegExp::Pattern reNumber;
  static Tanl::Text::RegExp::Pattern rePerson;
  static Tanl::Text::RegExp::Pattern reSem;
  static Tanl::Text::RegExp::Pattern reTense;
  static Tanl::Text::RegExp::Pattern reTrans;
  static Tanl::Text::RegExp::Pattern reVTrans;

  void operator() (char const* start, char const* end, Features& mf) const;
};

/**
 *	@ingroup parser
 */
struct PortugueseMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reGender;
  static Tanl::Text::RegExp::Pattern reNumber;
  static Tanl::Text::RegExp::Pattern rePerson;

  PortugueseMorphExtractor() {}

  void operator() (char const* start, char const* end, Features& mf) const;
};

/**
 *	@ingroup parser
 */
struct SloveneMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reCase;
  static Tanl::Text::RegExp::Pattern reGender;
  static Tanl::Text::RegExp::Pattern reNegative;
  static Tanl::Text::RegExp::Pattern reNumber;
  static Tanl::Text::RegExp::Pattern rePerson;

  void operator() (char const* start, char const* end, Features& mf) const;
};

/**
 *	@ingroup parser
 */
struct SpanishMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reGender;
  static Tanl::Text::RegExp::Pattern reNumber;
  static Tanl::Text::RegExp::Pattern rePerson;

  void operator() (char const* start, char const* end, Features& mf) const;
};

/**
 *	@ingroup parser
 */
struct TurkishMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reAFeats;
  static Tanl::Text::RegExp::Pattern rePFeats;

  void operator() (char const* start, char const* end, Features& mf) const;
};





struct RussianMorphExtractor : public MorphExtractor
{
  static Tanl::Text::RegExp::Pattern reAnimate;
  static Tanl::Text::RegExp::Pattern reCase;
  static Tanl::Text::RegExp::Pattern reGender;
  static Tanl::Text::RegExp::Pattern reNumber;
  static Tanl::Text::RegExp::Pattern reDegree;
  static Tanl::Text::RegExp::Pattern reParticiple;
  static Tanl::Text::RegExp::Pattern rePerson;
  static Tanl::Text::RegExp::Pattern reMood;
  static Tanl::Text::RegExp::Pattern reTense;
  static Tanl::Text::RegExp::Pattern reModal;
  static Tanl::Text::RegExp::Pattern reAspect;
  static Tanl::Text::RegExp::Pattern reTransCase;
  static Tanl::Text::RegExp::Pattern rePassive;

  void operator() (char const* start, char const* end, Features& mf) const;
};

} // namespace Tanl

#endif // DeSR_MorphExtractor_H
