#include <lem/solarix/MorphologyModels.h>

using namespace Solarix;

MorphologyModels::MorphologyModels()
{ 
 sequence_labeler = new SequenceLabelerModel();
 classifier = new ClassifierModel(); 
}

MorphologyModels::~MorphologyModels()
{
 delete sequence_labeler;
 delete classifier;
}

