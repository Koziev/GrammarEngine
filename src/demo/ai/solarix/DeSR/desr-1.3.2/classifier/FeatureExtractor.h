/*
**  Tanl
**  classifier/FeatureExtractor.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
**  ----------------------------------------------------------------------
**
**  This file is part of Tanl.
**
**  Tanl is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License, version 3,
**  as published by the Free Software Foundation.
**
**  Tanl is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**  ----------------------------------------------------------------------
*/

#ifndef Tanl_Classifier_FeatureExtractor_H
#define Tanl_Classifier_FeatureExtractor_H

namespace Tanl {
namespace Classifier {

/**
 *	Interface for feature extractors.
 */
template<class Features, typename Item>
class FeatureExtractor
{
public:

  virtual ~FeatureExtractor() { }

  /**
   *	Extract features from a given @a object and add them to @a features.
   */
  virtual void	extract(Features& features, Item& item) = 0;

  /**
   *	Reset to initial state.
   *	Useful when analyzing several items belonging to different groups
   *	with a single extractor: for instance sentences from documents.
   *	Some global state maintained by the extractor may need to be cleared.
   */
  virtual void		reset() { };
};

} // namespace Classifier
} // namespace Tanl

#endif // Tanl_Classifier_FeatureExtractor_H
