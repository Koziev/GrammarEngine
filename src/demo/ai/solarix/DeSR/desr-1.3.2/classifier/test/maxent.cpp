/*
**	Tanl
**	MaxEntropy/samples/maxent.cpp
** ----------------------------------------------------------------------
**	Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
*/

#include <fstream>
#include "BasicEventStream.h"
#include "classifier/GIS.h"
#include "classifier/LBFGS.h"

using namespace std;
using namespace Tanl::Classifier;

int main(int argc, char const* argv[])
{
  bool gis = false;
  int i = 1;
  if (argc > 1 && strcmp(argv[i], "-gis") == 0) {
    gis = true;
    i++;
  }
  if (argc < 3) {
    cerr << "usage: " << argv[0]
	 << " [-gis] model trainfile [iterations] [cutoff]\n";
	 << " -p model testfile\n";
    exit(1);
  }
  char const* modelFile = argv[i++];
  char const* trainset = argv[i++];
  int iter = 100;
  if (argc > i)
    iter = atoi(argv[i++]);
  int cutoff = 0;
  if (argc > i)
    cutoff = atoi(argv[i++]);
  double alpha = 0.0;
 
  // train the system
  ifstream ifs(trainset);
  BasicEventStream eventStream(ifs);
  if (gis) {
    GIS model(iter, cutoff, alpha);
    model.verbose = true;
    model.train(eventStream);
    // dump the model
    model.save(modelFile);
  } else {
    LBFGS model(iter, cutoff);
    model.verbose = true;
    model.train(eventStream);
    // dump the model
    model.save(modelFile);
  }
  cout << "Generated model: " << modelFile << endl;
}
