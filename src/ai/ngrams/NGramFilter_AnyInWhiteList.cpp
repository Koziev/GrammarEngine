#include <lem/streams.h>
#include <lem/ustreams.h>
#include <lem/solarix/NGramFilter_AnyInWhiteList.h>

using namespace Solarix;

// пропускает N-грамму на регистрацию, если в ее составе есть хоть одно
// слово из белого списка.

NGramFilter_AnyInWhiteList::NGramFilter_AnyInWhiteList( const lem::Path &filename )
{
 lem::Ptr<lem::Stream> file( new lem::BinaryReader(filename) );
 lem::Ptr<lem::Char_Stream::WideStream> reader = lem::Char_Stream::WideStream::GetReader(file);

 lem::UFString line;

 while(true) 
  {
   if( reader->eof() )
    break;

   line.clear();

   reader->read_line(line);
   lem::UCString w = line.trim().to_upper().c_str();
   if( !w.empty() )
    words.insert( w );
  }

 return;
}

void NGramFilter_AnyInWhiteList::AttachCollector( RawNGramsCollector *collector )
{
 for( std::set<lem::UCString>::const_iterator it=words.begin(); it!=words.end(); ++it )
  {
   int id_word = collector->RegisterWord(*it);
   id_words.insert( id_word );
  }

 return;
}


NGramFilter* NGramFilter_AnyInWhiteList::Clone(void) const
{
 NGramFilter_AnyInWhiteList *x = new NGramFilter_AnyInWhiteList();
 x->words = words;
 x->id_words = id_words;
 return x;
}



bool NGramFilter_AnyInWhiteList::Probe( RawNGramsCollector *collector, int ie1 )
{
 return id_words.find(ie1)!=id_words.end();
}

bool NGramFilter_AnyInWhiteList::Probe( RawNGramsCollector *collector, int ie1, int ie2 )
{
 return Probe(collector,ie1) || Probe(collector,ie2);
}

bool NGramFilter_AnyInWhiteList::Probe( RawNGramsCollector *collector, int ie1, int ie2, int ie3 )
{
 return Probe(collector,ie1) || Probe(collector,ie2) || Probe(collector,ie3);
}

bool NGramFilter_AnyInWhiteList::Probe( RawNGramsCollector *collector, int ie1, int ie2, int ie3, int ie4 )
{
 return Probe(collector,ie1) || Probe(collector,ie2) || Probe(collector,ie3) || Probe(collector,ie4);
}

bool NGramFilter_AnyInWhiteList::Probe( RawNGramsCollector *collector, int ie1, int ie2, int ie3, int ie4, int ie5 )
{
 return Probe(collector,ie1) || Probe(collector,ie2) || Probe(collector,ie3) || Probe(collector,ie4) || Probe(collector,ie5);
}

