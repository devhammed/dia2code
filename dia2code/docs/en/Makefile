# Makefile.in generated by automake 1.7.2 from Makefile.am.
# dia2code/docs/en/Makefile.  Generated from Makefile.in by configure.

# Copyright 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
# Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.



####### kdevelop will overwrite this part!!! (begin)##########

srcdir = .
top_srcdir = ../../..

pkgdatadir = $(datadir)/dia2code
pkglibdir = $(libdir)/dia2code
pkgincludedir = $(includedir)/dia2code
top_builddir = ../../..

am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
INSTALL = /usr/bin/install -c
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_HEADER = $(INSTALL_DATA)
transform = $(program_transform_name)
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
ACLOCAL = ${SHELL} /home/devhammed/Projects/Personal/dia2code/missing --run aclocal-1.7
AMDEP_FALSE = #
AMDEP_TRUE = 
AMTAR = ${SHELL} /home/devhammed/Projects/Personal/dia2code/missing --run tar
AUTOCONF = ${SHELL} /home/devhammed/Projects/Personal/dia2code/missing --run autoconf
AUTOHEADER = ${SHELL} /home/devhammed/Projects/Personal/dia2code/missing --run autoheader
AUTOMAKE = ${SHELL} /home/devhammed/Projects/Personal/dia2code/missing --run automake-1.7
AWK = gawk
CC = gcc
CCDEPMODE = depmode=gcc3
CFLAGS = -g -O2
CPP = gcc -E
CPPFLAGS =  -DDSO
CYGPATH_W = echo
DEFS = -DHAVE_CONFIG_H
DEPDIR = .deps
ECHO_C = 
ECHO_N = -n
ECHO_T = 
EGREP = /bin/grep -E
EXEEXT = 
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_STRIP_PROGRAM = ${SHELL} $(install_sh) -c -s
LDFLAGS =  -rdynamic
LIBOBJS = 
LIBS =  -lxml2 -ldl
LTLIBOBJS = 
MAKEINFO = ${SHELL} /home/devhammed/Projects/Personal/dia2code/missing --run makeinfo
OBJEXT = o
PACKAGE = dia2code
PACKAGE_BUGREPORT = 
PACKAGE_NAME = 
PACKAGE_STRING = 
PACKAGE_TARNAME = 
PACKAGE_VERSION = 
PATH_SEPARATOR = :
RANLIB = ranlib
SET_MAKE = 
SHELL = /bin/sh
STRIP = 
VERSION = 0.8.4
XML_CONFIG = /usr/bin/xml2-config
XML_INCLUDES = -I/usr/include/libxml2
ac_ct_CC = gcc
ac_ct_RANLIB = @ac_ct_RANLIB@
ac_ct_STRIP = @ac_ct_STRIP@
am__fastdepCC_FALSE = #
am__fastdepCC_TRUE = 
am__include = include
am__quote = 
bindir = ${exec_prefix}/bin
build_alias = 
datadir = ${prefix}/share
exec_prefix = ${prefix}
host_alias = 
includedir = ${prefix}/include
infodir = ${prefix}/share/info
install_sh = /home/devhammed/Projects/Personal/dia2code/install-sh
libdir = ${exec_prefix}/lib
libexecdir = ${exec_prefix}/libexec
localstatedir = ${prefix}/var
mandir = ${prefix}/share/man
oldincludedir = /usr/include
prefix = /home/devhammed/.local
program_transform_name = s,x,x,
sbindir = ${exec_prefix}/sbin
sharedstatedir = ${prefix}/com
sysconfdir = ${prefix}/etc
target_alias = 

EXTRA_DIST = Makefile.in 
subdir = dia2code/docs/en
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = $(top_builddir)/config.h
CONFIG_CLEAN_FILES =
DIST_SOURCES =
DIST_COMMON = Makefile.am Makefile.in
all: all-am

.SUFFIXES:
$(srcdir)/Makefile.in:  Makefile.am  $(top_srcdir)/configure.in $(ACLOCAL_M4)
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --gnu  dia2code/docs/en/Makefile
Makefile:  $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe)
uninstall-info-am:
tags: TAGS
TAGS:

ctags: CTAGS
CTAGS:

DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)

top_distdir = ../../..
distdir = $(top_distdir)/$(PACKAGE)-$(VERSION)

distdir: $(DISTFILES)
	@srcdirstrip=`echo "$(srcdir)" | sed 's|.|.|g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's|.|.|g'`; \
	list='$(DISTFILES)'; for file in $$list; do \
	  case $$file in \
	    $(srcdir)/*) file=`echo "$$file" | sed "s|^$$srcdirstrip/||"`;; \
	    $(top_srcdir)/*) file=`echo "$$file" | sed "s|^$$topsrcdirstrip/|$(top_builddir)/|"`;; \
	  esac; \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  dir=`echo "$$file" | sed -e 's,/[^/]*$$,,'`; \
	  if test "$$dir" != "$$file" && test "$$dir" != "."; then \
	    dir="/$$dir"; \
	    $(mkinstalldirs) "$(distdir)$$dir"; \
	  else \
	    dir=''; \
	  fi; \
	  if test -d $$d/$$file; then \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -pR $(srcdir)/$$file $(distdir)$$dir || exit 1; \
	    fi; \
	    cp -pR $$d/$$file $(distdir)$$dir || exit 1; \
	  else \
	    test -f $(distdir)/$$file \
	    || cp -p $$d/$$file $(distdir)/$$file \
	    || exit 1; \
	  fi; \
	done
check-am: all-am
check: check-am
all-am: Makefile

installdirs:

install: install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  INSTALL_STRIP_FLAG=-s \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-am

clean-am: clean-generic mostlyclean-am

distclean: distclean-am

distclean-am: clean-am distclean-generic

dvi: dvi-am

dvi-am:

info: info-am

info-am:

install-data-am:

install-exec-am:

install-info: install-info-am

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-am

maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-generic

pdf: pdf-am

pdf-am:

ps: ps-am

ps-am:

uninstall-am: uninstall-info-am

.PHONY: all all-am check check-am clean clean-generic distclean \
	distclean-generic distdir dvi dvi-am info info-am install \
	install-am install-data install-data-am install-exec \
	install-exec-am install-info install-info-am install-man \
	install-strip installcheck installcheck-am installdirs \
	maintainer-clean maintainer-clean-generic mostlyclean \
	mostlyclean-generic pdf pdf-am ps ps-am uninstall uninstall-am \
	uninstall-info-am


####### kdevelop will overwrite this part!!! (end)############
# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
