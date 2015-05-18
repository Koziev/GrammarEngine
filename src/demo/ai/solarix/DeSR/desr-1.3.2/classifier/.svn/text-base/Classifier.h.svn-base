/*
**  Tanl
**  classifier/Classifier.h
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

#ifndef Tanl_Classifier_Classifier_H
#define Tanl_Classifier_Classifier_H

#include "platform.h"
#include "Event.h"

namespace Tanl {
namespace Classifier {

  /**
   *	Abstract class for ML classifiers.
   */
class Classifier {

public:

  Classifier(bool verbose = false) :
    verbose(verbose)
    { }

  /**
   * Create classifier from model @a file.
   */
  Classifier(char const* file);

  /**
   * Create classifier reading model from stream @a ifs.
   */
  Classifier(std::istream& ifs);

  virtual ~Classifier() { }

  /**
   * Return the ID of the outcome corresponding to the highest likelihood
   * in @param ocs.
   *
   * @param ocs A double[] as returned by the estimate() method.
   * @return    The classID of the most likely outcome.
   */
  ClassID	BestOutcome(double* ocs) const;

  /**
   * Estimates the conditional probabilities p(oid|cxt) for a given context.
   *
   * @param predicates from a context.
   * @param alpha the estimated probabilities p(oid|cxt) for each outcome oid.
   */
  virtual ClassID	estimate(const std::vector<PID>& predicates, double alpha[]) {
    return 0;
  }

  /**
   * Return the name of an outcome corresponding to an int id.
   *
   * @param i An outcome id.
   * @return  The name of the outcome associated with that id.
   */
  char const*	OutcomeName(int i) const { return outcomeLabels[i]; }

  /**
   *	Return the ID of an outcome.
   *
   *	@param c an outcome label.
   *	@return the ID of @a c.
   */
  ClassID	OutcomeID(char const* c) const {
    for (unsigned i = 0; i < outcomeLabels.size(); i++)
      if (!strcmp(outcomeLabels[i], c))
	return i;
    return (ClassID)-1;
  }

  /** Returns the number of outcomes for this model.
   *  @return The number of outcomes.
   **/
  int		NumOutcomes() const { return numOutcomes; }
  
  /**
   * Return the name of an predicate corresponding to an int id.
   *
   * @param i An predicate id.
   * @return  The name of the predicate associated with that id.
   */
  std::string	PredicateName(int i) const { return predLabels[i]; }

  /**
   * Return the index of an predicate gives its name
   *
   * @param name The name of a predicate.
   * @return  The id associated to the predicate.
   */
  int		PredicateIndex(char const* name) { return predIndex[name]; }

  /**
   * Load the model from file.
   */
  void		load(std::istream& is);

  /**
   * Save the model to file
   */
  void		save(char const* file);

  Text::WordIndex&	PredIndex() { return predIndex; }

  /** Control whether to print progress indication */
  bool		verbose;

protected:

  std::vector<std::string>	predLabels;
  // associates pred labels to index
  // used by ContextStream when creating contexts
  Text::WordIndex		predIndex;
  // names of event outcomes
  std::vector<char const*>	outcomeLabels;
  // number of outcomes
  ClassID			numOutcomes;

};

} // namespace Classifier
} // namespace Tanl

#endif // Tanl_Classifier_Classifier_H
