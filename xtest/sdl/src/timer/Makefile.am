
## Makefile.am for the SDL timer library

noinst_LTLIBRARIES = libtimer.la

ARCH_SUBDIRS = amigaos beos linux macos win32

# Include the architecture-independent sources
COMMON_SRCS = SDL_timer.c SDL_timer_c.h SDL_systimer.h

# Include the architecture-specific sources
ARCH_SRCS = SDL_systimer.c

libtimer_la_SOURCES = $(COMMON_SRCS) $(ARCH_SRCS)

## Let automake know that it shouldn't distribute linked sources
BUILT_SOURCES = $(ARCH_SRCS)

## Let automake know that it should remove these for distribution
DISTCLEANFILES = $(ARCH_SRCS)

# The architecture specific directories need to be copied into place
# when building a distribution.
dist-hook:
	(cd $(distdir) && rm -f $(BUILT_SOURCES))
	cp -rp $(ARCH_SUBDIRS) $(distdir)
	(cd $(distdir) && rm -rf `find . -name CVS`)
