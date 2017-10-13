
PROGRAMS = train predict

SOURCES = $(wildcard *.cpp)

OBJECTS = BasicEventStream.o BasicContextStream.o

TANLDIR = ../..
INCLUDES= -I$(TANLDIR)
LIBS	= $(TANLDIR)/classifier/libClassifier.a

CXX = g++
CXXFLAGS = -g -O2

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $<

all: $(PROGRAMS)

train: $(OBJECTS) $(LIBS) train.cpp
	$(CXX) $(CXXFLAGS) train.cpp -o $@ $(INCLUDES) $(OBJECTS) $(LIBS)

predict: $(OBJECTS) $(LIBS) predict.cpp
	$(CXX) $(CXXFLAGS) predict.cpp -o $@ $(INCLUDES) $(OBJECTS) $(LIBS)

clean:
	rm -f $(OBJECTS) $(SOURCES:%.cpp=%.o) *~ $(PROGRAMS)
