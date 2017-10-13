######################################################################
# Directories
######################################################################

subdir=       text
srcdir=       .
top_builddir= ..
top_srcdir=   ..

######################################################################
# Libraries
######################################################################

LIBRARIES=  libText.a libText.so

# These are the version numbers for the shared libraries.
LIBVERSION= 0:1:0

######################################################################
# Packages
######################################################################

SUBDIRS= pcre .

######################################################################
# Includes
######################################################################

INCLUDES= -I$(top_srcdir) -I$(top_srcdir)/ixe

######################################################################
# Files
######################################################################

SOURCES=  charmap.cpp \
          HtmlTokenizer.cpp \
          RegExp.cpp \
          StreamTokenizer.cpp \
          strings.cpp \
          StringTokenizer.cpp \
          Suffixes.cpp \
          WordSet.cpp \
          Encoding.cpp \
          Char.cpp \
          String.cpp \
          Unicode.cpp \
          Utf8Utils.cpp \
          xml.cpp \
          XmlReader.cpp

OBJECTS=  $(SOURCES:.cpp=.o) $(wildcard pcre/*.o)
SOBJECTS= $(SOURCES:.cpp=.lo) $(wildcard pcre/*.lo)

######################################################################
# C, C++
######################################################################

CPPFLAGS= 
CFLAGS=   -g -O2
CXXFLAGS= -g -O2
LDFLAGS=   -s

######################################################################
# Targets
######################################################################

all: all-recursive
	@if test -z "$(SUBDIRS)"; then $(MAKE) $(LIBRARIES); fi

libText.a: $(OBJECTS)
	@echo ' '
	@echo '--- Building static library:' $@
	@echo ' '
	$(AR) $@ $^
	$(RANLIB) $@

libText.so: $(SOBJECTS)
	@echo ' '
	@echo '--- Building dynamic library:' $@
	@echo ' '
	$(AR) $@ $^
	$(RANLIB) $@

##################################################
# Specialized cases
##################################################

xml.cpp: xml.lex
	flex++ -o$@ -Pxml $<
	sed -i 's/<FlexLexer.h>/"FlexLexer.h"/' $@

######################################################################
# Common rules and targets
######################################################################

-include $(top_builddir)/Makefile.common
