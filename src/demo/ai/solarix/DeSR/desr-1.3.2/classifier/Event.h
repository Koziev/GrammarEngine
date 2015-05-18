/*
**  Tanl
**  classifier/Event.h
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

#ifndef Tanl_Classifier_Event_H
#define Tanl_Classifier_Event_H

// standard
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Tanl
#include "include/Iterator.h"
#include "text/WordIndex.h"

#define MIN	(std::min)
#define MAX	(std::max)

// from Common/util.h

#define FOR_EACH(T, C, I) \
	for (T::const_iterator I = (C).begin(); I != (C).end(); ++I)

#define TO_EACH(T, C, I) \
	for (T::iterator I = (C).begin(); I != (C).end(); ++I)

namespace Tanl {
namespace Classifier {

typedef unsigned	ClassID; ///< class IDs
typedef std::string	ClassName; ///< class label
typedef unsigned	PID;	///< predicate IDs
typedef double		Weight;	///< feature weight

/**
 *	Representation of features during training.
 */
class Features : public std::vector<std::string>
{
public:
  void		add(char const* predicate) {
    push_back(predicate);
  }

  void		add(std::string const& predicate) {
    push_back(predicate);
  }
};

/**
 *	Representation of a set of features by means of their internal IDs.
 *	Used during classification.
 *
 * @author      Giuseppe Attardi
 *
 */
class Context : public std::vector<PID> {
public:
  Context() { }

  /**
   *	Create a context from the set of features @a feats, using the IDs
   *	present in @a featIndex.
   */
  Context(Features& feats, Text::WordIndex& featIndex) {
    FOR_EACH (Features, feats, fit) {
      Text::WordIndex::const_iterator found = featIndex.find(fit->c_str());
      if (found != featIndex.end())
	add(found->second);
    }
  }

  void		add(PID pid) { push_back(pid); }
};

/**
 *	Used to fill @c Context from unencoded features.
 *	Pass this instead of a Features to a @c FeatureExtractor in order to
 *	obtain encoded features directly.
 */
class FeatureEncoder : public Features
{
public:
  FeatureEncoder(Context& context, Text::WordIndex& featIndex) :
    context(context), featIndex(featIndex)
  {
    context.clear();
  }

  void		add(char const* feature) {
    Text::WordIndex::const_iterator found = featIndex.find(feature);
    if (found != featIndex.end())
      context.add(found->second);
  }

  void		add(std::string const& feature) {
    Text::WordIndex::const_iterator found = featIndex.find(feature.c_str());
    if (found != featIndex.end())
      context.add(found->second);
  }

private:
  Context&		context;
  Text::WordIndex&	featIndex; ///< mapping from unencoded to encoded features
};

// ======================================================================
/**
 *	Generic class for events.
 *	An event is a pair (class, features), that corresponds to a
 *	training sample, where class is the outcome associated to the context
 *	represented by features.
 *
 * @author      Giuseppe Attardi
 *
 */
template <class FeatureType = Features>
class GenericEvent
{
public:

  GenericEvent(ClassName className = "") : className(className) { }

  GenericEvent(ClassName className, FeatureType features) :
    className(className),
    features(features)
  { }

  ClassName	className;
  FeatureType	features;
};

typedef GenericEvent<> Event;

inline std::ostream& operator <<(std::ostream& s, const Event& e)
{
  s << e.className;
  FOR_EACH (std::vector<std::string>, e.features, vit)
    s << " " << *vit;
  return s;
}

// ======================================================================
/**
 * Interface for objects that deliver a stream of training events
 * for computing a Maxent model, through GIS, LMBFG or other procedures.
 *
 * @author      Giuseppe Attardi
 *
 */
class EventStream : public Iterator<Event*> {

public:
  EventStream() { }

  /**
   * @return the string representation of event outcomes
   */
  char const**	outcomes() { return outcomeLabels; }

private:
  char const**	outcomeLabels; // outcomeID -> original string of outcome
};

/**
 *	Stream of classification cases.
 */
typedef Iterator<Context*> ContextStream;

// ======================================================================

class FileError : public std::runtime_error {
public:
  FileError(char const* what): std::runtime_error(what) { }
};

class EventStreamError : public std::runtime_error {
public:
  EventStreamError(char const* what): std::runtime_error(what) { }
};

} // namespce Classifier
} // namespce Tanl

#endif // Tanl_Classifier_Event_H
