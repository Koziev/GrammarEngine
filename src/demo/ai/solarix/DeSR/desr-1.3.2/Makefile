
PACKAGE =	desr
VERSION =	1.3.2

top_builddir =	.
subdir =	.
srcdir =	.
top_srcdir =	.

##################################################
# Installation directories
##################################################
prefix =	/usr/local
exec_prefix =	${prefix}
bindir =	${exec_prefix}/bin
includedir =	${prefix}/include
libdir =	${exec_prefix}/lib
mandir =	${prefix}/share/man

pkgdatadir =	$(datadir)/desr
pkglibdir =	$(libdir)/desr
pkgincludedir =	$(includedir)/desr

INSTALL =	/usr/bin/install -c
INSTALL_PROGRAM=${INSTALL} $(INSTALL_PROGRAM_FLAGS)
INSTALL_DATA =	${INSTALL} -m 644
INSTALL_SCRIPT= ${INSTALL}
transform =	s,x,x,

######################################################################
# Programs
######################################################################

PROGRAMS =

######################################################################
# LIBRARIES
######################################################################

LIBRARIES =

######################################################################
# Package
######################################################################

SUBDIRS =	ixe text classifier src doc

#######################################################################
# Targets
#######################################################################

all: all-recursive
	@if test -z "$(SUBDIRS)" ; then $(MAKE) $(LIBRARIES) $(PROGRAMS); fi

######################################################################
# Common rules and targets
######################################################################

-include $(top_builddir)/Makefile.common
