# Generated automatically from Makefile.in by configure.
# Makefile.in generated automatically by automake 1.4a from Makefile.am

# Copyright (C) 1994, 1995-8, 1999 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.


SHELL = /bin/sh

srcdir = .
top_srcdir = ../../..
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

top_builddir = ../../..

ACLOCAL = aclocal
AUTOCONF = autoconf
AUTOMAKE = automake
AUTOHEADER = autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL_PROGRAM}
INSTALL_STRIP_FLAG =
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

noinst_LTLIBRARIES = libaudio_alsa.la
libaudio_alsa_la_SOURCES = $(SRCS)

# The SDL audio driver sources
SRCS = SDL_alsa_audio.c		SDL_alsa_audio.h

mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_CLEAN_FILES = 
LTLIBRARIES =  $(noinst_LTLIBRARIES)


DEFS =  -DPACKAGE=\"SDL\" -DVERSION=\"1.2.1\" -DHAVE_ALLOCA_H=1 -DHAVE_ALLOCA=1  -I. -I$(srcdir) 
CPPFLAGS = 
LDFLAGS = 
LIBS = 
X_CFLAGS =  -I/usr/X11R6/include
X_LIBS =  -L/usr/X11R6/lib
X_EXTRA_LIBS = 
X_PRE_LIBS =  -lSM -lICE
libaudio_alsa_la_LDFLAGS = 
libaudio_alsa_la_LIBADD = 
libaudio_alsa_la_OBJECTS =  SDL_alsa_audio.lo
CFLAGS = -O3 -march=i686 -fmessage-length=0 -funroll-all-loops -fomit-frame-pointer -malign-loops=2 -malign-jumps=2 -malign-functions=2 -I/usr/local/include -Wall -DUSE_ASMBLIT -I./hermes -I$(top_srcdir)/src/hermes -DOSS_SUPPORT  -I/usr/X11R6/include -DENABLE_X11 -DXFREE86_VM -DXFREE86_VMGAMMA -DXFREE86_DGAMOUSE -DDEFAULT_DGAMOUSE -DXFREE86_XV -DENABLE_DGA -DHAVE_OPENGL -D_REENTRANT -DSDL_USE_PTHREADS -I$(top_srcdir)/include -I$(top_srcdir)/include/SDL -I$(top_srcdir)/src -I$(top_srcdir)/src/linux -I$(top_srcdir)/src/main -I$(top_srcdir)/src/audio -I$(top_srcdir)/src/video -I$(top_srcdir)/src/events -I$(top_srcdir)/src/joystick -I$(top_srcdir)/src/cdrom -I$(top_srcdir)/src/thread -I$(top_srcdir)/src/timer -I$(top_srcdir)/src/endian -I$(top_srcdir)/src/file -I$(top_srcdir)/../dri/include -I$(top_srcdir)/../dri/lib/GL/mesa/src -I$(top_srcdir)/../dri/lib/GL/dri -I$(top_srcdir)/../dri/lib/GL/glfb -I$(top_srcdir)/../dri/os-support -g
COMPILE = $(CC) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
LTCOMPILE = $(LIBTOOL) --mode=compile $(CC) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(LIBTOOL) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(LDFLAGS) -o $@
DIST_COMMON =  Makefile.am Makefile.in


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = gtar
GZIP_ENV = --best
SOURCES = $(libaudio_alsa_la_SOURCES)
OBJECTS = $(libaudio_alsa_la_OBJECTS)

all: all-redirect
.SUFFIXES:
.SUFFIXES: .S .c .lo .o .s
$(srcdir)/Makefile.in: Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --foreign --include-deps src/audio/alsa/Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status


mostlyclean-noinstLTLIBRARIES:

clean-noinstLTLIBRARIES:
	-test -z "$(noinst_LTLIBRARIES)" || rm -f $(noinst_LTLIBRARIES)

distclean-noinstLTLIBRARIES:

maintainer-clean-noinstLTLIBRARIES:

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

libaudio_alsa.la: $(libaudio_alsa_la_OBJECTS) $(libaudio_alsa_la_DEPENDENCIES)
	$(LINK)  $(libaudio_alsa_la_LDFLAGS) $(libaudio_alsa_la_OBJECTS) $(libaudio_alsa_la_LIBADD) $(LIBS)

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

subdir = src/audio/alsa

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
info-am:
info: info-am
dvi-am:
dvi: dvi-am
check-am: all-am
check: check-am
installcheck-am:
installcheck: installcheck-am
install-exec-am:
install-exec: install-exec-am

install-data-am:
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am:
uninstall: uninstall-am
all-am: Makefile $(LTLIBRARIES)
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_STRIP_FLAG=-s install
installdirs:


mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)
	-rm -f config.cache config.log stamp-h stamp-h[0-9]*

maintainer-clean-generic:
mostlyclean-am:  mostlyclean-noinstLTLIBRARIES mostlyclean-compile \
		mostlyclean-libtool mostlyclean-tags \
		mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-noinstLTLIBRARIES clean-compile clean-libtool \
		clean-tags clean-generic mostlyclean-am

clean: clean-am

distclean-am:  distclean-noinstLTLIBRARIES distclean-compile \
		distclean-libtool distclean-tags distclean-generic \
		clean-am
	-rm -f libtool

distclean: distclean-am

maintainer-clean-am:  maintainer-clean-noinstLTLIBRARIES \
		maintainer-clean-compile maintainer-clean-libtool \
		maintainer-clean-tags maintainer-clean-generic \
		distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am

.PHONY: mostlyclean-noinstLTLIBRARIES distclean-noinstLTLIBRARIES \
clean-noinstLTLIBRARIES maintainer-clean-noinstLTLIBRARIES \
mostlyclean-compile distclean-compile clean-compile \
maintainer-clean-compile mostlyclean-libtool distclean-libtool \
clean-libtool maintainer-clean-libtool tags mostlyclean-tags \
distclean-tags clean-tags maintainer-clean-tags distdir info-am info \
dvi-am dvi check check-am installcheck-am installcheck install-exec-am \
install-exec install-data-am install-data install-am install \
uninstall-am uninstall all-redirect all-am all installdirs \
mostlyclean-generic distclean-generic clean-generic \
maintainer-clean-generic clean mostlyclean distclean maintainer-clean


# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
