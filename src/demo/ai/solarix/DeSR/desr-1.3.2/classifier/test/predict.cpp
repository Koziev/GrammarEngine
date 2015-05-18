/*
**	IXE
**	MaxEntropy/samples/predict.cpp
** ----------------------------------------------------------------------
**	Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
*/

#include <sys/stat.h>
#include <fstream>
#include "BasicContextStream.h"
#include "BasicEventStream.h"
#include "classifier/MaxEnt.h"

using namespace std;
using namespace Tanl::Classifier;
using namespace Tanl::Text;

int main(int argc, char const* argv[])
{
  bool verbose = false;
  int i = 1;
  if (argc > 1 && strcmp(argv[i], "-v") == 0) {
    verbose = true;
    i++;
    argc--;
  }
  if (argc < 3) {
    cerr << "usage: " << argv[0] << " [-v] modelFile data\n";
    exit(1);
    }
  char const* modelFile = argv[i];
  struct stat stat_buf;
  if (::stat(modelFile, &stat_buf) == -1) {
    cerr << "No model file\n";
    exit(-1);
  }
  char const* dataFile = argv[i+1];
  if (::stat(dataFile, &stat_buf) == -1) {
    cerr << "No data file\n";
    exit(-1);
  }

  MaxEnt model(modelFile);
  model.verbose = verbose;
  int numOutcomes = model.NumOutcomes();
  double params[numOutcomes];
  ifstream in(dataFile);
# ifdef USE_CONTEXT
  BasicContextStream contextStream(in, model.PredIndex());
  while (contextStream.hasNext()) {
    Context* context = contextStream.next(); 
    model.estimate(*context, params);
    char const* outcome = model.OutcomeName(model.BestOutcome(params));
    if (verbose)
      cout << outcome << endl;
    delete context;
  }
# else
  int correct = 0;
  int wrong = 0;
  BasicEventStream eventStream(in);
  while (eventStream.hasNext()) {
    Event* event = eventStream.next(); 
    model.estimate(event->features, params);
    char const* outcome = model.OutcomeName(model.BestOutcome(params));
    if (::strcmp(outcome, event->className.c_str())) {
      wrong++;
    } else
      correct++;
    if (verbose)
      cerr << event->className << endl;
    delete event;
  }
  if (correct + wrong)
    cout << "Accuracy: " << float(correct)/(correct+wrong)
	 << " (" << correct << '/' << correct+wrong << ')' << endl;
  else
    cout << "No data" << endl;
# endif
}
