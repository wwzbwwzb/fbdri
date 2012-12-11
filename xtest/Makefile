HAVE_GLOBAL := $(shell if [ -f ../../utils/global_config ]; then echo yes; fi )
HAVE_QUICKTIME := $(shell if [ -f /usr/include/quicktime.h ]; then echo yes; fi )




ifeq ($(HAVE_GLOBAL), yes)
include ../../utils/global_config
else
include ../global_config
endif


CFLAGS += \
	-g \
	-I. \
	-Isdl/include
LIBS += -L/usr/X11R6/lib -Lsdl/src/.libs/ -lGL -lSDL -lpng




ifeq ($(HAVE_QUICKTIME), yes)
CFLAGS += -DHAVE_MOVIE
LIBS += -lglib -lquicktime
endif





OBJS = \
	$(OBJDIR)/animation.o

OUTPUT = $(OBJDIR)/animation



$(shell echo $(CFLAGS) > $(OBJDIR)/c_flags)


$(OUTPUT): $(OBJS)
	$(GCC) -o $(OUTPUT) $(OBJS) $(LIBS)


$(OBJS):
	$(GCC) -c `cat $(OBJDIR)/c_flags` $(subst $(OBJDIR)/,, $*.c) -o $*.o


clean:
	rm -rf $(OBJDIR)
	find \( -name core \
		-o -name '*.o' \
		-o -name '*.lo' \
		-o -name '*.a' \
		-o -name '*.la' \
		-o -name '*.so*' \) -exec rm -rf {} \;




$(OBJDIR)/animation.o:                animation.c
