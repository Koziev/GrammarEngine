/*
**  Tanl
**  classifier/MaxEnt.h
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

#ifndef Tanl_Classifier_MaxEnt_H
#define Tanl_Classifier_MaxEnt_H

#include "Classifier.h"
#include "include/unordered_map.h"
#include "text/strings.h"	// hash<string>

// standard
#include <list>

// use correction
#define SLACK

/**
 *	Use compact encoding for representing sparse matrix lambda[f, c]
 */
BEGIN_NAMESPACE_HASH
  template<> struct hash<std::pair<unsigned, unsigned> > {
    size_t operator()(const std::pair<unsigned, unsigned>& x) const {
      unsigned a = x.first + ~(x.first << 13);
      unsigned b = x.second + ~(x.second << 9);
      a += (b >> 13);
      return a ^ b;
      //return (x.first << 8) ^ x.second;
    }
  };

  template<> struct hash<std::pair<unsigned, std::vector<unsigned> > > {
    size_t operator()(const std::pair<unsigned, std::vector<unsigned> >& x) const {
      const std::vector<unsigned>& v = x.second;
      int n = x.first;
      for (unsigned i = 0; i < v.size(); ++i)
	n += v[i] * (i+1);
      return n + v.size() * 47;
    }
  };
END_NAMESPACE_HASH

namespace Tanl {
namespace Classifier {

typedef std::pair<PID, ClassID>	Feature;
  /** Estimates for p[c|f]  */
typedef unordered_map<Feature, double>	FeatureMap;
typedef unordered_map<std::string, int>	WordCounts;

/**
 * A Maximum Entropy classifier.
 * See Adwait Ratnaparkhi's tech report at the University of Pennsylvania,
 * available at <a href ="ftp://ftp.cis.upenn.edu/pub/ircs/tr/97-08.ps.Z">
 * <code>ftp://ftp.cis.upenn.edu/pub/ircs/tr/97-08.ps.Z</code></a>. 
 *
 */
class MaxEnt : public Classifier
{

public:

  MaxEnt() { }

  MaxEnt(int iterations, int cutoff) :
    iterations(iterations), cutoff(cutoff), pID(0),
    correctionConstant(0),
    correctionParam(0.0)
  { }

  MaxEnt(char const* file);

  MaxEnt(std::istream& ifs);

  virtual ~MaxEnt();

  /**
   * Evaluate a context and return an array of the
   * likelihood of each outcome in that context.
   *
   * @param context Represents the set of features which have been
   *                observed at the present decision point.
   * @return        The normalized probabilities for the outcomes given the
   *                context. The indexes of the double[] are the outcome
   *                ids, and the actual string representation of the
   *                outcomes can be obtained from the method getOutcome(int i).
   */
  void		estimate(Context& context, double prob[]) {
    estimate((std::vector<PID>&)context, prob);
  }

  /**
   * Evaluate a set of features and return an array of the
   * likelihood of each outcome in that context.
   *
   * @param features The set of features which have been
   *                observed at the present decision point.
   * @return        The normalized probabilities for the outcomes given the
   *                context. The indexes of the double[] are the outcome
   *                ids, and the actual string representation of the
   *                outcomes can be obtained from the method getOutcome(int i).
   */
  void		estimate(Features& features, double prob[]) {
    Context context(features, predIndex);
    estimate((std::vector<PID>&)context, prob);
  }

  /**
   * Return the ID of the outcome corresponding to the highest likelihood
   * in @param ocs.
   *
   * @param ocs A double[] as returned by the estimate() method.
   * @return    The classID of the most likely outcome.
   */
  ClassID	BestOutcome(double* ocs) const;

  /**
   * Load the model from file.
   * Loader recognizes also text model files produced by Zhang Maxent Toolkit:
   * (http://homepages.inf.ed.ac.uk/s0450736/maxent_toolkit.html).
   */
  void		load(std::istream& is);

  /**
   * Save the model to file
   */
  void		save(char const* file);

  /**
   *	Reads events from @c eventStream into a linked list.
   *	Consider all events = (cID, [pred1, ..., predk])
   *	Assign pID to each predicate that occurrs > cutoff times.
   *	The predicates associated with each event are counted and any which
   *	occurs at least @c cutoff times is added to @c predLabels.
   *	Classes which are outcome of a retained event will be added to
   *	@c outcomeLabels.
   */
  void		read(EventStream& eventStream);

protected:

  /**
   *	 Consume a trainig event.
   */
  void		readEvent(Event* ev);

  /**
   * Estimates the conditional probabilities p(oid|cxt) for a given context.
   *
   * @param predicates from a context.
   * @param alpha the estimated probabilities p(oid|cxt) for each outcome oid.
   */
  ClassID		estimate(const std::vector<PID>& predicates, double alpha[]);

  FeatureMap		lambda;	///< the model parameters
  PID			numPreds; ///< = predLabels.size()
  int			numTokens; ///< # of unique events
  typedef unordered_map<std::pair<ClassID, std::vector<PID> >, int> EventMap;

  EventMap		eventMap; ///< occurrences of unique events

  unsigned		cutoff; ///< discard predicates below this frequency
  int			iterations; ///< steps of the algorithm

  size_t		correctionConstant;
  double		correctionParam;

  // temporaries used by read() before train() gets called
  std::list<Event*>	events;
  WordCounts		counter;
  int			pID;

  /** Load model saved in the format of Zhang maxent implementation. */
  void			loadZhang(std::istream& is);

  friend std::ostream& operator <<(std::ostream& s, MaxEnt const& m);

  // Build the EventMap of unique event occurrences,
  // assigning ids to predicates and labels.
  // It consumes and deletes events.
  static int buildIndex(std::list<Event*>& events,
			Text::WordIndex& predIndex,
			EventMap& eventMap,
			std::vector<char const*>& outcomeLabels,
			int evCutoff, bool verbose);
};

std::ostream& operator <<(std::ostream& s, MaxEnt const& m);

} // namespace Classifier
} // namespace Tanl

#endif // Tanl_Classifier_MaxEnt_H
