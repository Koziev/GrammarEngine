# Process this file with autoconf to produce a configure script.
# Use:
#   aclocal -I autoconf
# to produce aclocal.m4 from autoconf/*.m4

AC_INIT(desr, 0.9)
AC_PREREQ(2.50)			# You must have autoconf version 2.50
AC_CONFIG_AUX_DIR(autoconf)
AC_CONFIG_HEADERS([src/config.h ixe/platform.h])
AC_CONFIG_SUBDIRS([text/pcre])
AC_CONFIG_FILES([Makefile.common \
	Makefile \
	classifier/Makefile classifier/test/Makefile \
	ixe/Makefile \
	text/Makefile text/pcre/Makefile \
	src/Makefile \
	doc/Makefile \
	doc/doxygen.conf \
])
# Package.
PACKAGE=desr
AC_SUBST(PACKAGE)

# ======================================================================
# Version numbers.
VERSION=[`grep 'version\[\]' src/version.h | sed 's/.*"\(.*\)".*/\1/'`]
AC_SUBST(VERSION)
MAJOR_VERSION=[`expr $VERSION : '\([0-9][0-9]*\)'`]
AC_SUBST(MAJOR_VERSION)
MINOR_VERSION=[`expr $VERSION : '[0-9][0-9]*\.\([0-9][0-9]*\)'`]
AC_SUBST(MINOR_VERSION)
REVISION_LEVEL=[`expr $VERSION : '[0-9][0-9]*\.[0-9][0-9]*\.\([0-9a-z][0-9a-z]*\)'`]
AC_SUBST(REVISION_LEVEL)

# ======================================================================
# Configure setup

AC_PROG_INSTALL
AC_CANONICAL_HOST       # set host_os, host_cpu
AC_PROG_MAKE_SET        # set MAKE for recursive invocations

# Substitution variables
AC_SUBST(CC)
AC_SUBST(CFLAGS)
AC_SUBST(CPPFLAGS)
AC_SUBST(CPPMMD)        # let cpp produce dependency file
AC_SUBST(CXX)
AC_SUBST(CXXFLAGS)
AC_SUBST(LDFLAGS)
AC_SUBST(LIBS)
AC_SUBST(LD_SHARED)
AC_SUBST(LTCFLAGS)

# ======================================================================
# Process options

AC_MSG_CHECKING(if --enable-32bit option specified)
AC_ARG_ENABLE(32bit,
  [  --enable-32bit          Generate 32 bit binaries.],
  [cv_32bit="$enable_32bit"], [cv_32bit="no"])
AC_MSG_RESULT($cv_32bit)

AC_MSG_CHECKING(if --enable-debug option specified)
AC_ARG_ENABLE(debug,
  [  --enable-debug          Build a debugging version.],
  [cv_debug="$enable_debug"], [cv_debug="no"])
AC_MSG_RESULT($cv_debug)

AC_MSG_CHECKING(if --enable-profile option specified)
AC_ARG_ENABLE(profile,
  [  --enable-profile        Turn on profiling.],
  [cv_profile="$enable_profile"], [cv_profile="no"])
AC_MSG_RESULT($cv_profile)

AC_MSG_CHECKING(if --enable-wall option specified)
AC_ARG_ENABLE(wall,
  [  --enable-wall           Print all compiler warnings.],
  [cv_wall="$enable_wall"], [cv_wall="no"])
AC_MSG_RESULT($cv_wall)

AC_MSG_CHECKING(if --disable-python option specified)
AC_ARG_ENABLE(python,
  [  --disable-python           Do not create python wrapper.],
  [cv_python=`expr "$enable_python" != no`], [cv_python=1])
AC_MSG_RESULT($cv_python)

# ======================================================================
# Checks for programs

AC_PROG_LIBTOOL
AC_SUBST(lt_prog_compiler_pic)
AC_SUBST(lt_prog_compiler_pic_CXX)

AC_PATH_PROG(AUTOCONF, autoconf, autoconf)
AC_PATH_PROG(AR, ar, /usr/bin/ar)
AC_PATH_PROG(CHMOD, chmod, /bin/chmod)
AC_PATH_PROG(CP, cp, /bin/cp)
AC_PATH_PROG(FIND, find, /bin/find)
AC_PATH_PROG(GUNZIP, gunzip, /bin/gunzip)
AC_PATH_PROG(LN, ln, /bin/ln)
AC_PATH_PROG(MKDIR, mkdir, /bin/mkdir)
AC_PATH_PROG(PERL, perl, /usr/bin/perl)
AC_PATH_PROG(RM, rm, /bin/rm)
RM="$RM -f" # patch for conflict with libtool
AC_PATH_PROG(SHELL, shell, /bin/sh)
AC_PATH_PROG(STRIP, strip, /usr/bin/strip)
AC_PATH_PROG(TAR, tar, /bin/tar)

AM_PROG_MKDIR_P
AM_PROG_INSTALL_SH
AM_PROG_INSTALL_STRIP

# ======================================================================
# Other languages

# Python includes
if test $cv_python = 1 ; then
  AC_PATH_PROG(PYTHON, python, /usr/bin/python)
  PYTHON_INCLUDE=`$PYTHON -c "from distutils.sysconfig import *; print get_python_inc()"`
  PYTHON_LIB=`$PYTHON -c "from distutils.sysconfig import * ; print get_config_var('LIBRARY')[[3:-2]]"`
  if test -n "$PYTHON_INCLUDE"; then
    AC_DEFINE(HAVE_PYTHON,, [Define if python includes are present. ])
    PYTHON_INCLUDE=-I$PYTHON_INCLUDE
    LIBS="-l$PYTHON_LIB $LIBS"
  fi
fi
AC_SUBST(PYTHON_INCLUDE)

# Java includes
AC_MSG_CHECKING(for java include file jni.h)
AC_ARG_WITH(java-include-dir, [ --with-java-include-dir=path    Set location of Java include directory], [JAVAINCDIR="$withval"], [JAVAINCDIR=""])
if test "$GCC" = yes -a "x`gcc -v 2>&1 | grep with-java-home=`" != 'x'; then
 JAVA_INCLUDE=" " # use space, Makefile tests for emptyness
else
 JAVA_INCLUDE=""
 for d in include "$JAVA_HOME/include" $JAVAINCDIR ; do
   if test -r "$d/jni.h" ; then
     AC_MSG_RESULT($d)
     JAVA_INCLUDE=-I$d
     break
   fi
 done
fi
AC_SUBST(JAVA_INCLUDE)

AC_CHECK_PROGS([JAVA], [java])
AM_CONDITIONAL(HAVE_JAVA, test $JAVA)
AC_SUBST(HAVE_JAVA)

# Programs for building the documentation.

# Acrobat distiller
AC_PATH_PROG(DISTILL, distill, distill)
# DoxyGen document generator
AC_PATH_PROG(DOXYGEN, doxygen, /usr/local/bin/doxygen)

# dot graphic generator
AC_CHECK_PROG(dot, , )
AC_SUBST(HAVE_DOT)
if test -n "$dot"; then
  HAVE_DOT="YES"
fi

# ======================================================================
# This is where we handle stuff that autoconf can't handle.
#
# There are additional libraries we need for some compiler/architecture
# combinations.
#
# Some architectures require special flags and/or libraries for
# threaded applications
#
# Don't override anything if it's already set from the environment.

optimize="-O"
CDEBUG="-g"
LD_SHARED="-shared"
LTCFLAGS=""

case "$host_os" in
aix4.*)    optimize="-O2"
	   CC=${CC-"xlc_r"}
	   CPPFLAGS="-D_THREAD_SAFE $CPPFLAGS"
	   LIBTSO_LIBS="\$(LIBS)";;
bsdi3*)	   CC=${CC-"shlicc2"}
	   optimize="-O2"
	   LIBS="-lipc $LIBS";;
bsdi*)     optimize="-O2";;
freebsd*)  optimize="-O4"
	   CPPFLAGS="-D_THREAD_SAFE $CPPFLAGS"
	   LDFLAGS="-pthread $LDFLAGS";;
hpux*)	   AC_DEFINE(_REENTRANT);;
irix*)	   optimize="-O2"
	   CPPFLAGS="-D_SGI_MP_SOURCE $CPPFLAGS";;
gnu*|k*bsd*-gnu|*linux*)	   optimize="-O3"
	   AC_DEFINE(_REENTRANT)
	   AC_DEFINE(_GNU_SOURCE) # enable GNU extensions
	   LIBDLL="-ldl";;
mpeix*)	   CPPFLAGS="-D_POSIX_SOURCE -D_SOCKET_SOURCE $CPPFLAGS"
	   LIBS="-lsocket -lsvipc $LIBS";;
osf*)	   optimize="-O4"
	   CPPFLAGS="$CPPFLAGS -pthread"
	   CPPMMD="-MD"
	   AR="/usr/bin/ar"
	   CXX=${CXX-"cxx -ptr $(top_builddir)/cxx_repository"};;
sco3.2v4*) CC=${CC-"cc -belf"}
	   LIBS="-lsocket -lnsl_s $LIBS";;
sco*)	   CC=${CC-"cc -belf"}
	   LIBS="-lsocket -lnsl $LIBS";;
solaris*)  AC_DEFINE(_REENTRANT)
	   LIBDLL="-ldl"
	   LD_SHARED_="-G";;
*cygwin)   AC_DEFINE(_WIN32);;
*darwin*)  LD_SHARED="-bundle"
	   optimize="-O3"
	   CFLAGS=`echo $CFLAGS | sed "s/(^-g)|[[:space:]]-g//"`
	   CDEBUG="-gdwarf-2"
	   LTCFLAGS="-flat_namespace -undefined suppress"
	   LIBS="-liconv $LIBS";;
esac

CFLAGS=${CFLAGS-$optimize}
CXXFLAGS=$CFLAGS
# Setting for compiler to produce dependency information
CPPMMD=${CPPMMD-"-Wp,-MMD,\$@.d"}

AC_SUBST(SWIG_FLAGS)
if test "$GCC" = yes; then
   SWIG_FLAGS="-fno-strict-aliasing"
fi

# ======================================================================
# Compiler

AC_PROG_CC
AC_PROG_CXX
AC_PROG_CPP

# ======================================================================
# Compiler options

# Generate code that runs on any i386 system
case "$host_cpu" in
x86_64*)
  if test "$GCC" = yes -a "$cv_32bit" = 1 ; then
    CC="$CC -m32"
    CXX="$CXX -m32"
  fi
esac

# ======================================================================
# Configure options

# If the user wants a debugging environment, add suitable flag to the CFLAGS value.
if test "$cv_debug" != "no"; then
  AC_DEFINE(DEBUG)
  CFLAGS="$CFLAGS $CDEBUG"
  CXXFLAGS="$CXXFLAGS $CDEBUG"
else
# enable assert()
  AC_DEFINE(NDEBUG)
# strip binaries
  LDFLAGS="$LDFLAGS -s"
fi

# Turn on profiling
if test "$cv_profile" = yes; then
  CFLAGS="$CFLAGS -pg"
  CXXFLAGS="$CXXFLAGS -pg"
fi

# ======================================================================
# Checks for libraries

# Include -lpthread if the library exists
AC_CHECK_LIB(pthread, pthread_create)

# Include -lxnet if the library exists
AC_CHECK_LIB(xnet, bind)

# Checks for header files
AC_HEADER_STDC

# This is C++ package!
AC_LANG_CPLUSPLUS

# Check for STL headers
AC_CHECK_HEADERS(algorithm vector string map,, \
  AC_MSG_ERROR([** ERROR: Your system lacks some needed STL header files.]))

# Check for TR1 unordered_map
AC_CACHE_CHECK([for tr1/unordered_map],
  ac_cv_cxx_tr1_unordered_map,
  [AC_COMPILE_IFELSE([#include <tr1/unordered_map>
  using std::tr1::unordered_map;],
  ac_cv_cxx_tr1_unordered_map=yes, ac_cv_cxx_tr1_unordered_map=no)
])
if test "$ac_cv_cxx_tr1_unordered_map" = yes; then
  AC_DEFINE(HAVE_TR1_UNORDERED_MAP,,[Define if tr1/unordered_map is present. ])
fi

# Check for TR1 unordered_set
AC_CACHE_CHECK([for tr1/unordered_set],
  ac_cv_cxx_tr1_unordered_set,
  [AC_COMPILE_IFELSE([#include <tr1/unordered_set>
  using std::tr1::unordered_set;],
  ac_cv_cxx_tr1_unordered_set=yes, ac_cv_cxx_tr1_unordered_set=no)
])
if test "$ac_cv_cxx_tr1_unordered_set" = yes; then
  AC_DEFINE(HAVE_TR1_UNORDERED_SET,,[Define if tr1/unordered_set is present. ])
fi

# gcc-3.0 have hash_map and hash_set in ext dir
hash_in_ext=no
AC_CHECK_HEADERS(hash_map hash_set,, [
  AC_CHECK_HEADERS(ext/hash_map ext/hash_set, hash_in_ext=yes,
    AC_MSG_ERROR([** ERROR: Your system lacks some needed STL header files.])
)
]
break
)
if test "$hash_in_ext" = "yes"; then
  AC_DEFINE(HAVE_EXT_HASH_MAP_SET, 1, \
    [Define if you have hash_map and hash_set includes in ext/ directory.])
fi

# Tools defined in aclocal.m4
AC_SUBST(AR)
AC_SUBST(RANLIB)

# Checks for library functions
AC_FUNC_ALLOCA
AC_SUBST(HAVE_ALLOCA)
AC_FUNC_FNMATCH
AC_FUNC_MEMCMP
AC_FUNC_MMAP
AC_CHECK_FUNCS(getcwd gettimeofday strdup strerror strspn strstr)
AC_CHECK_FUNCS(bcopy memmove)     # Required by pcre

# Checks for typedefs, structures, and system/compiler characteristics
AC_C_BIGENDIAN			# defines WORDS_BIGENDIAN
AC_STRUCT_TM
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_CHECK_TYPE(off64_t, , AC_DEFINE(off64_t, off_t), [
#include <sys/types.h>
#include <stdio.h>])
AC_TYPE_PID_T
AC_TYPE_SIZE_T

# ======================================================================
# Check for byte aligned memory access

AC_CACHE_CHECK([alignement memory restriction], ac_cv_bytealign, [dnl
AC_RUN_IFELSE([
#include <stdlib.h>
#include <stdio.h>
int block@<:@2@:>@;
main()
{
  FILE* f=fopen("conftestval", "w");
  if (!f) exit(1);
  fprintf(f, "%d\n", *(int*)((char*)block+1));
  exit(0);
}],
ac_cv_bytealign=yes,
ac_cv_bytealign=no
)])
if test $ac_cv_bytealign = yes; then
  AC_DEFINE([BYTE_ALIGN], 1,
  [Define if there are no memory alignement restrictions])
fi

# Compute PAGE_SIZE
AC_CACHE_CHECK([suitable value for PAGE_SIZE], ac_cv_page_size, [dnl
AC_TRY_RUN([
#include <stdio.h>
#include <unistd.h>
int main() {
  FILE* fd = fopen("confpage.set", "w");
  exit(fprintf(fd, "%d\n", getpagesize()) < 0);
}],[
 if test -s confpage.set; then
  ac_cv_page_size=`cat confpage.set`
  rm -f confpage.set
 fi
],
 ac_cv_page_size=4096)])
AC_DEFINE_UNQUOTED(PAGE_SIZE, $ac_cv_page_size)

# ======================================================================
# Generated files

AC_OUTPUT
