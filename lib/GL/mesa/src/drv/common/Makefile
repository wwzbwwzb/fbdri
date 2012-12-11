include ../../../../../../../utils/global_config


OBJS = \
	$(OBJDIR)/hwlog.o \
	$(OBJDIR)/mm.o


CFLAGS += -I. \
	-I../common \
	-I../../../../../../dri \
	-I../../../dri \
	-I../../../../../../kernel \
	-I../../../../glfb \
	-I../../../../../../include \
	-I../../ \
	-I../../../../../../os-support \
	-I../../../../../../../sdl/include \
	-I../../../../../../../sdl/src \
	-I../../../../../../../sdl/src/video \
	-I../../../../../../../sdl/src/video/fbcon

CFLAGS += -Dlinux -D__i386__ -D_POSIX_C_SOURCE=199309L -D_POSIX_SOURCE \
	-D_XOPEN_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE  -D_GNU_SOURCE   \
	-DFUNCPROTO=15 -DNARROWPROTO   -DMALLOC_0_RETURNS_NULL -DGLXEXT \
	-DXF86DRI -DGLX_DIRECT_RENDERING -DGLX_USE_DLOPEN -DGLX_USE_MESA

OUTPUT = $(OBJDIR)/dri_common.so

$(shell echo $(CFLAGS) > $(OBJDIR)/c_flags)


$(OUTPUT): $(OBJS)
	gcc -shared -o $(OUTPUT) $(OBJS)

clean:
	rm -rf $(OBJDIR)

$(OBJS):
	$(GCC) -c `cat $(OBJDIR)/c_flags` $(subst $(OBJDIR)/,, $*.c) -o $*.o







$(OBJDIR)/hwlog.o:                  hwlog.c
$(OBJDIR)/mm.o:                     mm.c
