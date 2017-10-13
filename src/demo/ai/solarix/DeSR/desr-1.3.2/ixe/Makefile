
PACKAGE =	desr
VERSION =	1.3.2

top_builddir =	..
subdir =	ixe
srcdir =	.
top_srcdir =	..

##################################################
# Installation directories
##################################################
prefix =	/usr/local
exec_prefix =	${prefix}
bindir =	${exec_prefix}/bin
includedir =	${prefix}/include
libdir =	${exec_prefix}/lib
mandir =	${datarootdir}/man
datarootdir=    ${prefix}/share

pkgdatadir =	$(datarootdir)/desr
pkglibdir =	$(libdir)/desr
pkgincludedir =	$(includedir)/desr

transform =	s,x,x,

######################################################################
# Programs
######################################################################

PROGRAMS =

######################################################################
# LIBRARIES
######################################################################

LIBRARIES =	$(LIBIXE)

LIBIXE =	libixe.a

######################################################################
# Files
######################################################################

ixe_COMMON = \
		conf/conf.cpp \
		conf/conf_bool.cpp \
		conf/conf_float.cpp \
		conf/conf_int.cpp \
		conf/conf_set.cpp \
		conf/conf_string.cpp \
		Common/OptionStream.cpp

ixe_LIB = \
	io/File.cpp \
	io/FileHandle.cpp \
	io/Format.cpp \
	io/mappedFile.cpp

ixe_HEADERS = \
	Common/OptionStream.h \
	Common/util.h \
	conf/conf_bool.h \
	conf/conf.h \
	conf/conf_int.h \
	conf/conf_set.h \
	conf/conf_string.h \
	conf/conf_vector.h \
	conf/Conversion.h \
	conf/ExcludeFile.h \
	conf/FileType.h \
	conf/IncludeFile.h \
	conf/PatternMap.h \
	conf/PatternList.h \
	conf/PatternSet.h \
	include/config.h \
	include/error.h \
	include/exit_codes.h \
	include/ixe.h \
	include/version.h \
	io/File.h \
	io/FileHandle.h \
	io/mappedFile.h \

######################################################################

libixe_SOURCES =  $(ixe_COMMON) $(ixe_INDEX) $(ixe_SEARCH) $(ixe_LIB)
libixe_CSOURCES=  $(ixe_CLIB)

EXTRA_DIST =	ixe.conf ChangeLog \
	lib option_spec.cpp README autoconf aclocal.m4 win32

CONFIG_HEADER =	platform.h

##################################################
# C, C++
##################################################
CPPFLAGS=	
CFLAGS=	 	-g -O2
CXXFLAGS =	-g -O2
LDFLAGS=	 -s
LIBS =		-lpthread -lpython2.7 
INCLUDES=	-I. -I$(top_builddir)

######################################################################
# Package
######################################################################

libixe_OBJECTS:= $(libixe_SOURCES:.cpp=.lo) $(libixe_CSOURCES:.c=.lo)

DIST_COMMON =	README COPYING ChangeLog INSTALL THANKS \
		Makefile.in Makefile.common.in $(CONFIG_HEADER).in

SOURCES =	$(libixe_SOURCES) $(libixe_CSOURCES)
OBJECTS =	$(libixe_OBJECTS)

#######################################################################
# Targets
#######################################################################

all: $(LIBRARIES) $(PROGRAMS)

$(LIBIXE): $(libixe_OBJECTS)
	$(AR) $@ $(libixe_OBJECTS)
	test ! -f $(RANLIB) || $(RANLIB) $@

######################################################################
# Common rules and targets
######################################################################

-include $(top_builddir)/Makefile.common
