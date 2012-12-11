# Generated automatically from Makefile.in by configure.
# Makefile.in generated automatically by automake 1.4 from Makefile.am

# Copyright (C) 1994, 1995-8, 1999 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

#
# This is necessary because some platforms have special program
# entry points, which require special application initialization.


SHELL = /bin/sh

srcdir = .
top_srcdir = ../..
prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include

DESTDIR =

pkgdatadir = $(datadir)/SDL
pkglibdir = $(libdir)/SDL
pkgincludedir = $(includedir)/SDL

top_builddir = ../..

ACLOCAL = aclocal
AUTOCONF = autoconf
AUTOMAKE = automake
AUTOHEADER = autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL} $(AM_INSTALL_PROGRAM_FLAGS)
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL_PROGRAM}
transform = s,x,x,

NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
host_alias = i686-pc-linux-gnu
host_triplet = i686-pc-linux-gnu
ARCH = linux
ARTSCCONFIG = /usr/bin/artsc-config
AS = 
AUDIO_DRIVERS =  dsp/libaudio_dsp.la dma/libaudio_dma.la
AUDIO_SUBDIRS =  dsp dma
CC = gcc
CXX = c++
DLLTOOL = 
ESD_CFLAGS = 
ESD_CONFIG = /usr/bin/esd-config
ESD_LIBS = 
JOYSTICK_DRIVERS =  linux/libjoystick_linux.la
JOYSTICK_SUBDIRS =  linux
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LN_S = ln -s
LT_AGE = 0
LT_CURRENT = 0
LT_RELEASE = 1.2
LT_REVISION = 1
MAKEINFO = makeinfo
NASM = /usr/bin/nasm
NASMFLAGS = -f elf
OBJC = 
OBJDUMP = 
PACKAGE = SDL
RANLIB = ranlib
SDL_BINARY_AGE = 1
SDL_CFLAGS =  -D_REENTRANT
SDL_EXTRADIRS =  audio video events joystick cdrom thread timer endian file hermes
SDL_EXTRALIBS =  audio/libaudio.la video/libvideo.la events/libevents.la joystick/libjoystick.la cdrom/libcdrom.la thread/libthread.la timer/libtimer.la endian/libendian.la file/libfile.la hermes/libhermes.la
SDL_INTERFACE_AGE = 1
SDL_LIBS = -lSDL -lpthread
SDL_MAJOR_VERSION = 1
SDL_MICRO_VERSION = 1
SDL_MINOR_VERSION = 2
SDL_RLD_FLAGS = -Wl,-rpath,${exec_prefix}/lib
SDL_VERSION = 1.2.1
SYSTEM_LIBS =  -lm  -L/usr/X11R6/lib -lX11 -lXext -lXxf86vm -lXxf86dga -lXv -ldl
VERSION = 1.2.1
VIDEO_DRIVERS =  x11/libvideo_x11.la dga/libvideo_dga.la
VIDEO_SUBDIRS =  x11 dga

ARCH_SUBDIRS = beos linux macos win32

# Build a separate library containing the main() entry point.
lib_LIBRARIES = libSDLmain.a

MAINLIB_ARCH_SRCS = SDL_main.c

libSDLmain_a_SOURCES = $(MAINLIB_ARCH_SRCS)

# Build an internal library of any special app setup functions
noinst_LTLIBRARIES = libarch.la
#ARCH_SRCS = SDL_BeApp.cc SDL_BeApp.h
ARCH_SRCS = 

# Include the architecture-independent sources
COMMON_SRCS = dummy.c

libarch_la_SOURCES = $(COMMON_SRCS) $(ARCH_SRCS)

BUILT_SOURCES = $(MAINLIB_ARCH_SRCS) $(ARCH_SRCS)

DISTCLEANFILES = $(MAINLIB_ARCH_SRCS) $(ARCH_SRCS)
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_CLEAN_FILES = 
LIBRARIES =  $(lib_LIBRARIES)


DEFS =  -DPACKAGE=\"SDL\" -DVERSION=\"1.2.1\" -DHAVE_ALLOCA_H=1 -DHAVE_ALLOCA=1  -I. -I$(srcdir) 
CPPFLAGS = 
LDFLAGS = 
LIBS = 
X_CFLAGS =  -I/usr/X11R6/include
X_LIBS =  -L/usr/X11R6/lib
X_EXTRA_LIBS = 
X_PRE_LIBS =  -lSM -lICE
libSDLmain_a_LIBADD = 
libSDLmain_a_OBJECTS =  SDL_main.o
AR = ar
LTLIBRARIES =  $(noinst_LTLIBRARIES)

libarch_la_LDFLAGS = 
libarch_la_LIBADD = 
libarch_la_OBJECTS =  dummy.lo
#libarch_la_OBJECTS =  dummy.lo SDL_BeApp.lo
CXXFLAGS = -O3 -march=i686 -fmessage-length=0 -funroll-all-loops -fomit-frame-pointer -malign-loops=2 -malign-jumps=2 -malign-functions=2 -I/usr/local/include -Wall -DUSE_ASMBLIT -I./hermes -I$(top_srcdir)/src/hermes -DOSS_SUPPORT  -I/usr/X11R6/include -DENABLE_X11 -DXFREE86_VM -DXFREE86_VMGAMMA -DXFREE86_DGAMOUSE -DDEFAULT_DGAMOUSE -DXFREE86_XV -DENABLE_DGA -DHAVE_OPENGL -D_REENTRANT -DSDL_USE_PTHREADS -I$(top_srcdir)/include -I$(top_srcdir)/include/SDL -I$(top_srcdir)/src -I$(top_srcdir)/src/linux -I$(top_srcdir)/src/main -I$(top_srcdir)/src/audio -I$(top_srcdir)/src/video -I$(top_srcdir)/src/events -I$(top_srcdir)/src/joystick -I$(top_srcdir)/src/cdrom -I$(top_srcdir)/src/thread -I$(top_srcdir)/src/timer -I$(top_srcdir)/src/endian -I$(top_srcdir)/src/file -I$(top_srcdir)/../dri/include -I$(top_srcdir)/../dri/lib/GL/mesa/src -I$(top_srcdir)/../dri/lib/GL/dri -I$(top_srcdir)/../dri/lib/GL/glfb -I$(top_srcdir)/../dri/os-support -g
CXXCOMPILE = $(CXX) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)
LTCXXCOMPILE = $(LIBTOOL) --mode=compile $(CXX) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)
CXXLD = $(CXX)
CXXLINK = $(LIBTOOL) --mode=link $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@
CFLAGS = -O3 -march=i686 -fmessage-length=0 -funroll-all-loops -fomit-frame-pointer -malign-loops=2 -malign-jumps=2 -malign-functions=2 -I/usr/local/include -Wall -DUSE_ASMBLIT -I./hermes -I$(top_srcdir)/src/hermes -DOSS_SUPPORT  -I/usr/X11R6/include -DENABLE_X11 -DXFREE86_VM -DXFREE86_VMGAMMA -DXFREE86_DGAMOUSE -DDEFAULT_DGAMOUSE -DXFREE86_XV -DENABLE_DGA -DHAVE_OPENGL -D_REENTRANT -DSDL_USE_PTHREADS -I$(top_srcdir)/include -I$(top_srcdir)/include/SDL -I$(top_srcdir)/src -I$(top_srcdir)/src/linux -I$(top_srcdir)/src/main -I$(top_srcdir)/src/audio -I$(top_srcdir)/src/video -I$(top_srcdir)/src/events -I$(top_srcdir)/src/joystick -I$(top_srcdir)/src/cdrom -I$(top_srcdir)/src/thread -I$(top_srcdir)/src/timer -I$(top_srcdir)/src/endian -I$(top_srcdir)/src/file -I$(top_srcdir)/../dri/include -I$(top_srcdir)/../dri/lib/GL/mesa/src -I$(top_srcdir)/../dri/lib/GL/dri -I$(top_srcdir)/../dri/lib/GL/glfb -I$(top_srcdir)/../dri/os-support -g
COMPILE = $(CC) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
LTCOMPILE = $(LIBTOOL) --mode=compile $(CC) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(LIBTOOL) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(LDFLAGS) -o $@
DIST_COMMON =  Makefile.am Makefile.in


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = gtar
GZIP_ENV = --best
SOURCES = $(libSDLmain_a_SOURCES) $(libarch_la_SOURCES)
OBJECTS = $(libSDLmain_a_OBJECTS) $(libarch_la_OBJECTS)

all: all-redirect
.SUFFIXES:
.SUFFIXES: .S .c .cc .lo .o .s
$(srcdir)/Makefile.in: Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --foreign --include-deps src/main/Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status


mostlyclean-libLIBRARIES:

clean-libLIBRARIES:
	-test -z "$(lib_LIBRARIES)" || rm -f $(lib_LIBRARIES)

distclean-libLIBRARIES:

maintainer-clean-libLIBRARIES:

install-libLIBRARIES: $(lib_LIBRARIES)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(libdir)
	@list='$(lib_LIBRARIES)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo " $(INSTALL_DATA) $$p $(DESTDIR)$(libdir)/$$p"; \
	    $(INSTALL_DATA) $$p $(DESTDIR)$(libdir)/$$p; \
	  else :; fi; \
	done
	@$(POST_INSTALL)
	@list='$(lib_LIBRARIES)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo " $(RANLIB) $(DESTDIR)$(libdir)/$$p"; \
	    $(RANLIB) $(DESTDIR)$(libdir)/$$p; \
	  else :; fi; \
	done

uninstall-libLIBRARIES:
	@$(NORMAL_UNINSTALL)
	list='$(lib_LIBRARIES)'; for p in $$list; do \
	  rm -f $(DESTDIR)$(libdir)/$$p; \
	done

.c.o:
	$(COMPILE) -c $<

.s.o:
	$(COMPILE) -c $<

.S.o:
	$(COMPILE) -c $<

mostlyclean-compile:
	-rm -f *.o core *.core

clean-compile:

distclean-compile:
	-rm -f *.tab.c

maintainer-clean-compile:

.c.lo:
	$(LIBTOOL) --mode=compile $(COMPILE) -c $<

.s.lo:
	$(LIBTOOL) --mode=compile $(COMPILE) -c $<

.S.lo:
	$(LIBTOOL) --mode=compile $(COMPILE) -c $<

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

distclean-libtool:

maintainer-clean-libtool:

libSDLmain.a: $(libSDLmain_a_OBJECTS) $(libSDLmain_a_DEPENDENCIES)
	-rm -f libSDLmain.a
	$(AR) cru libSDLmain.a $(libSDLmain_a_OBJECTS) $(libSDLmain_a_LIBADD)
	$(RANLIB) libSDLmain.a

mostlyclean-noinstLTLIBRARIES:

clean-noinstLTLIBRARIES:
	-test -z "$(noinst_LTLIBRARIES)" || rm -f $(noinst_LTLIBRARIES)

distclean-noinstLTLIBRARIES:

maintainer-clean-noinstLTLIBRARIES:

libarch.la: $(libarch_la_OBJECTS) $(libarch_la_DEPENDENCIES)
	$(LINK)  $(libarch_la_LDFLAGS) $(libarch_la_OBJECTS) $(libarch_la_LIBADD) $(LIBS)
.cc.o:
	$(CXXCOMPILE) -c $<
.cc.lo:
	$(LTCXXCOMPILE) -c $<

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP)
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	here=`pwd` && cd $(srcdir) \
	  && mkid -f$$here/ID $$unique $(LISP)

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$unique$(LISP)$$tags" \
	  || (cd $(srcdir) && etags $(ETAGS_ARGS) $$tags  $$unique $(LISP) -o $$here/TAGS)

mostlyclean-tags:

clean-tags:

distclean-tags:
	-rm -f TAGS ID

maintainer-clean-tags:

distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)

subdir = src/main

distdir: $(DISTFILES)
	@for file in $(DISTFILES); do \
	  d=$(srcdir); \
	  if test -d $$d/$$file; then \
	    cp -pr $$d/$$file $(distdir)/$$file; \
	  else \
	    test -f $(distdir)/$$file \
	    || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	    || cp -p $$d/$$file $(distdir)/$$file || :; \
	  fi; \
	done
	$(MAKE) $(AM_MAKEFLAGS) top_distdir="$(top_distdir)" distdir="$(distdir)" dist-hook
info-am:
info: info-am
dvi-am:
dvi: dvi-am
check-am: all-am
check: check-am
installcheck-am:
installcheck: installcheck-am
install-exec-am: install-libLIBRARIES
install-exec: install-exec-am

install-data-am:
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am: uninstall-libLIBRARIES
uninstall: uninstall-am
all-am: Makefile $(LIBRARIES) $(LTLIBRARIES)
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) AM_INSTALL_PROGRAM_FLAGS=-s install
installdirs:
	$(mkinstalldirs)  $(DESTDIR)$(libdir)


mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)
	-rm -f config.cache config.log stamp-h stamp-h[0-9]*
	-test -z "$(DISTCLEANFILES)" || rm -f $(DISTCLEANFILES)

maintainer-clean-generic:
	-test -z "$(BUILT_SOURCES)" || rm -f $(BUILT_SOURCES)
mostlyclean-am:  mostlyclean-libLIBRARIES mostlyclean-compile \
		mostlyclean-libtool mostlyclean-noinstLTLIBRARIES \
		mostlyclean-tags mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-libLIBRARIES clean-compile clean-libtool \
		clean-noinstLTLIBRARIES clean-tags clean-generic \
		mostlyclean-am

clean: clean-am

distclean-am:  distclean-libLIBRARIES distclean-compile \
		distclean-libtool distclean-noinstLTLIBRARIES \
		distclean-tags distclean-generic clean-am
	-rm -f libtool

distclean: distclean-am

maintainer-clean-am:  maintainer-clean-libLIBRARIES \
		maintainer-clean-compile maintainer-clean-libtool \
		maintainer-clean-noinstLTLIBRARIES \
		maintainer-clean-tags maintainer-clean-generic \
		distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am

.PHONY: mostlyclean-libLIBRARIES distclean-libLIBRARIES \
clean-libLIBRARIES maintainer-clean-libLIBRARIES uninstall-libLIBRARIES \
install-libLIBRARIES mostlyclean-compile distclean-compile \
clean-compile maintainer-clean-compile mostlyclean-libtool \
distclean-libtool clean-libtool maintainer-clean-libtool \
mostlyclean-noinstLTLIBRARIES distclean-noinstLTLIBRARIES \
clean-noinstLTLIBRARIES maintainer-clean-noinstLTLIBRARIES tags \
mostlyclean-tags distclean-tags clean-tags maintainer-clean-tags \
distdir info-am info dvi-am dvi check check-am installcheck-am \
installcheck install-exec-am install-exec install-data-am install-data \
install-am install uninstall-am uninstall all-redirect all-am all \
installdirs mostlyclean-generic distclean-generic clean-generic \
maintainer-clean-generic clean mostlyclean distclean maintainer-clean


# The architecture specific directories need to be copied into place
# when building a distribution.
dist-hook:
	(cd $(distdir) && rm -f $(BUILT_SOURCES))
	cp -rp $(ARCH_SUBDIRS) $(distdir)
	(cd $(distdir) && rm -rf `find . -name CVS`)

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
