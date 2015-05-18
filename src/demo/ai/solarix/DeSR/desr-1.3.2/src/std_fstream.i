%{
#include <fstream>
%}

#ifdef SWIGPYTHON
%include <std_iostream.i>
#endif
#ifdef SWIGJAVA
//%include <std/std_iostream.i> // raises errors
#endif

namespace std {

class ifstream: public istream
{
public:
  ifstream(const char *fn);
};

class ofstream: public istream
{
public:
  ofstream(const char *fn);
};

}
