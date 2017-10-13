
PACKAGE =	DeSR
VERSION =	1.3.2

top_builddir =	..
subdir =	src
srcdir =	.
top_srcdir =	..
bindir =	${exec_prefix}/bin
libdir =        ${exec_prefix}/bin

DESTDIR =	$(top_builddir)

##################################################
# FILES
##################################################

# PtbTokenizer.cpp must be added explicitly, since it is generated
SOURCES = $(filter-out PtbTokenizer.cpp PyPipe.cpp, $(wildcard *.cpp)) PtbTokenizer.cpp

POS_SOURCES:= $(filter-out PosTaggerStub.cpp, $(SOURCES))
NOPOS_SOURCES:= $(filter-out PosTagger.cpp, $(SOURCES))

OBJECTS:= $(NOPOS_SOURCES:.cpp=.lo)
#OBJECTS:= $(POS_SOURCES:.cpp=.lo)

LIB_OBJECTS = $(filter-out desr.lo, $(OBJECTS))

SWIG_SOURCES = desr.i
PY_WRAPPERS:=   $(SWIG_SOURCES:.i=_py.cxx)
PY_OBJECTS:=    $(SWIG_SOURCES:.i=_py.lo) PyPipe.lo
#SWIGPYTHON_OPTIONS= -builtin

JAVA_WRAPPERS:= $(SWIG_SOURCES:.i=_java.cxx)
JAVA_OBJECTS:=  $(SWIG_SOURCES:.i=_java.lo)
SWIGJAVA_OPTIONS= -package jni -outdir jni

##################################################
# External Packages
##################################################

DESRDIR = $(top_builddir)
IXEDIR = $(DESRDIR)/ixe
TEXTDIR = $(DESRDIR)/text
MEDIR = $(DESRDIR)/classifier

INCLUDES= -I$(DESRDIR) -I$(IXEDIR) -I$(MEDIR) \
	  -I/usr/include/python2.7  

LIBS	= $(MEDIR)/libClassifier.a \
	  $(IXEDIR)/libixe.a $(TEXTDIR)/libText.so

LDLIBS = -lpthread -lpython2.7 

STATIC_LIBS = -lstdc++ -lm

######################################################################
# Programs
######################################################################

PROGRAMS = desr

######################################################################
# LIBRARIES
######################################################################

LIBRARIES= libdesr.so

ifneq ("-I/usr/include/python2.7", "")
LIBRARIES:= $(LIBRARIES) _desr.so desr.py
endif
ifneq (" ", "")
LIBRARIES:= $(LIBRARIES) libjdesr.so
endif

##################################################
# Targets
##################################################

all: $(LIBRARIES) $(PROGRAMS)

desr: $(OBJECTS) $(LIBS)
	$(CXX) -o $@ $(CXXFLAGS) $(OBJECTS) $(LIBS) $(LDLIBS)

desr.static: $(OBJECTS) $(LIBS)
	$(CC) -o $@ -static $(CXXFLAGS) $(OBJECTS) $(LIBS) $(STATIC_LIBS)

libdesr.so: $(LIB_OBJECTS)
	$(SOLINK) -o $@ $(LIB_OBJECTS) $(LIBS) $(LDLIBS)

$(PY_WRAPPERS): $(wildcard *.i)
_desr.so: $(LIB_OBJECTS) $(PY_OBJECTS) $(PY_WRAPPERS)
	$(SOLINK) -o $@ $(LIB_OBJECTS) $(PY_OBJECTS) $(LIBS) $(LDLIBS)

$(JAVA_WRAPPERS): $(wildcard *.i)
libjdesr.so: $(LIB_OBJECTS) $(JAVA_OBJECTS) $(JAVA_WRAPPERS)
	$(SOLINK) -o $@ $(LIB_OBJECTS) $(JAVA_OBJECTS) $(LIBS)

##################################################
# Test cases
##################################################

Test.class: Test.java libjdesr.so
	javac -cp . Test.java

##################################################
# Specialized cases
##################################################

PtbTokenizer.cpp: PtbTokenizer.lex
	flex++ -o$@ -Pptb $<
	sed -i 's/<FlexLexer.h>/"FlexLexer.h"/' $@

##################################################
# PATHS FOR STANDARD USER-LEVEL COMMANDS
##################################################
SHELL=	/bin/bash
AR=	/usr/bin/ar cr
CHMOD=	/bin/chmod
CP=	/bin/cp
LN=	/bin/ln
MKDIR=	/bin/mkdir
RANLIB= ranlib
RM=	/bin/rm -f
STRIP=	/usr/bin/strip

##################################################
# C, C++
##################################################
CPPFLAGS=	
CFLAGS=	 	-g -O2
CXXFLAGS =	-g -O2
LDFLAGS=	 -s

######################################################################
# Dynamic Library
######################################################################

LTCXXCOMPILE= $(CXXCOMPILE) -fPIC

######################################################################
# Common rules and targets
######################################################################

-include $(top_builddir)/Makefile.common
