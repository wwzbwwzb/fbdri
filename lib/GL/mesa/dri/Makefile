include ../../../../../utils/global_config




OBJS = \
	$(OBJDIR)/dri_mesa.o


OUTPUT = \
	$(OBJDIR)/dri_mesa.so


CFLAGS += -I. \
	-I../../../../include \
	-I../../glfb \
	-I../../../../../sdl/src/video \
	-I../../../../../sdl/include \
	-I../../../../dri \
	-I../../../../os-support \
	-I../src

$(shell echo $(CFLAGS) > $(OBJDIR)/c_flags)



$(OUTPUT): $(OBJS)
	gcc -shared -o $(OUTPUT) $(OBJS)

$(OBJS):
	$(GCC) -c `cat $(OBJDIR)/c_flags` $(subst $(OBJDIR)/,, $*.c) -o $*.o





$(OBJDIR)/dri_mesa.o: 	     dri_mesa.c
