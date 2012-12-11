HAVE_GLOBAL := $(shell if [ -f ../utils/global_config ]; then echo yes; fi )
HAVE_QUICKTIME := $(shell if [ -f /usr/include/quicktime.h ]; then echo yes; fi )



ifeq ($(HAVE_GLOBAL), yes)
include ../utils/global_config
else
include global_config
endif




ifeq ($(HAVE_QUICKTIME), yes)
QUICKTIMECFLAGS = -DHAVE_MOVIE
QUICKTIMELIBS = -lglib -lquicktime
endif




#CFLAGS += -g




TEST1OBJS = $(OBJDIR)/testcube.o
TEST2OBJS = $(OBJDIR)/testpng.o
TEST3OBJS = $(OBJDIR)/testyuv.o
TEST5OBJS = $(OBJDIR)/animation.o

TEST1 = $(OBJDIR)/testcube
TEST2 = $(OBJDIR)/testpng
TEST3 = $(OBJDIR)/testyuv
TEST5 = $(OBJDIR)/animation

TESTCFLAGS = $(CFLAGS) \
	-I. \
	-Idri \
	-Idrivers/ati \
	-Iinclude \
	-Ikernel \
	-Ilib/GL/dri \
	-Ilib/GL/glfb \
	-Ilib/GL/mesa/dri/ \
	-Ilib/GL/mesa/src/ \
	-Ilib/GL/mesa/src/drv/common/ \
	-Ilib/GL/mesa/src/drv/radeon/ \
	-Ios-support \
	-Ios-support/linux/drm/kernel \
	-I../sdl/src/video \
	-I../sdl/src/video/fbcon \
	-I../sdl/include \
	$(QUICKTIMECFLAGS)













OBJDIRS = \
	$(OBJDIR)/dri \
	$(OBJDIR)/drivers/ati \
	$(OBJDIR)/kernel \
	$(OBJDIR)/os-support/linux/drm \
	$(OBJDIR)/lib/GL/dri \
	$(OBJDIR)/lib/GL/glfb/ \
	$(OBJDIR)/lib/GL/mesa/dri/ \
	$(OBJDIR)/lib/GL/mesa/src-glu/ \
	$(OBJDIR)/lib/GL/mesa/src/drv/common/ \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/


OUTPUTOBJS = \
	$(OBJDIR)/dri/dri.o \
	$(OBJDIR)/drivers/ati/radeon_accel.o \
	$(OBJDIR)/drivers/ati/radeon_dri.o \
	$(OBJDIR)/drivers/ati/radeon_driver.o \
	$(OBJDIR)/lib/GL/dri/dri_glfb.o \
	$(OBJDIR)/lib/GL/dri/fbdri.o \
	$(OBJDIR)/lib/GL/dri/fbdrimain.o \
	$(OBJDIR)/lib/GL/glfb/g_single.o \
	$(OBJDIR)/lib/GL/glfb/glfbcmds.o \
	$(OBJDIR)/lib/GL/glfb/glfbext.o \
	$(OBJDIR)/lib/GL/glfb/pixel.o \
	$(OBJDIR)/lib/GL/glfb/pixelstore.o \
	$(OBJDIR)/lib/GL/glfb/render2.o \
	$(OBJDIR)/lib/GL/glfb/vertarr.o

TAILOBJS = \
	$(OBJDIR)/os-support/linux/drm/fbdrm.o \
	$(OBJDIR)/os-support/linux/drm/fbdrmHash.o \
	$(OBJDIR)/os-support/linux/drm/fbdrmRadeon.o

MESAOBJS = \
	$(OBJDIR)/lib/GL/mesa/dri/dri_mesa.o \
	$(OBJDIR)/lib/GL/mesa/src/aatriangle.o \
	$(OBJDIR)/lib/GL/mesa/src/accum.o \
	$(OBJDIR)/lib/GL/mesa/src/alpha.o \
	$(OBJDIR)/lib/GL/mesa/src/alphabuf.o \
	$(OBJDIR)/lib/GL/mesa/src/attrib.o \
	$(OBJDIR)/lib/GL/mesa/src/bbox.o \
	$(OBJDIR)/lib/GL/mesa/src/bitmap.o \
	$(OBJDIR)/lib/GL/mesa/src/blend.o \
	$(OBJDIR)/lib/GL/mesa/src/buffers.o \
	$(OBJDIR)/lib/GL/mesa/src/clip.o \
	$(OBJDIR)/lib/GL/mesa/src/colortab.o \
	$(OBJDIR)/lib/GL/mesa/src/config.o \
	$(OBJDIR)/lib/GL/mesa/src/context.o \
	$(OBJDIR)/lib/GL/mesa/src/copypix.o \
	$(OBJDIR)/lib/GL/mesa/src/cva.o \
	$(OBJDIR)/lib/GL/mesa/src/debug_xform.o \
	$(OBJDIR)/lib/GL/mesa/src/depth.o \
	$(OBJDIR)/lib/GL/mesa/src/dlist.o \
	$(OBJDIR)/lib/GL/mesa/src/drawpix.o \
	$(OBJDIR)/lib/GL/mesa/src/enable.o \
	$(OBJDIR)/lib/GL/mesa/src/enums.o \
	$(OBJDIR)/lib/GL/mesa/src/eval.o \
	$(OBJDIR)/lib/GL/mesa/src/extensions.o \
	$(OBJDIR)/lib/GL/mesa/src/feedback.o \
	$(OBJDIR)/lib/GL/mesa/src/fog.o \
	$(OBJDIR)/lib/GL/mesa/src/get.o \
	$(OBJDIR)/lib/GL/mesa/src/hash.o \
	$(OBJDIR)/lib/GL/mesa/src/hint.o \
	$(OBJDIR)/lib/GL/mesa/src/image.o \
	$(OBJDIR)/lib/GL/mesa/src/imaging.o \
	$(OBJDIR)/lib/GL/mesa/src/light.o \
	$(OBJDIR)/lib/GL/mesa/src/lines.o \
	$(OBJDIR)/lib/GL/mesa/src/logic.o \
	$(OBJDIR)/lib/GL/mesa/src/masking.o \
	$(OBJDIR)/lib/GL/mesa/src/matrix.o \
	$(OBJDIR)/lib/GL/mesa/src/mem.o \
	$(OBJDIR)/lib/GL/mesa/src/mmath.o \
	$(OBJDIR)/lib/GL/mesa/src/pb.o \
	$(OBJDIR)/lib/GL/mesa/src/pipeline.o \
	$(OBJDIR)/lib/GL/mesa/src/pixel.o \
	$(OBJDIR)/lib/GL/mesa/src/pixeltex.o \
	$(OBJDIR)/lib/GL/mesa/src/points.o \
	$(OBJDIR)/lib/GL/mesa/src/polygon.o \
	$(OBJDIR)/lib/GL/mesa/src/quads.o \
	$(OBJDIR)/lib/GL/mesa/src/rastpos.o \
	$(OBJDIR)/lib/GL/mesa/src/readpix.o \
	$(OBJDIR)/lib/GL/mesa/src/rect.o \
	$(OBJDIR)/lib/GL/mesa/src/scissor.o \
	$(OBJDIR)/lib/GL/mesa/src/shade.o \
	$(OBJDIR)/lib/GL/mesa/src/span.o \
	$(OBJDIR)/lib/GL/mesa/src/stages.o \
	$(OBJDIR)/lib/GL/mesa/src/state.o \
	$(OBJDIR)/lib/GL/mesa/src/stencil.o \
	$(OBJDIR)/lib/GL/mesa/src/texformat.o \
	$(OBJDIR)/lib/GL/mesa/src/teximage.o \
	$(OBJDIR)/lib/GL/mesa/src/texobj.o \
	$(OBJDIR)/lib/GL/mesa/src/texstate.o \
	$(OBJDIR)/lib/GL/mesa/src/texture.o \
	$(OBJDIR)/lib/GL/mesa/src/texutil.o \
	$(OBJDIR)/lib/GL/mesa/src/translate.o \
	$(OBJDIR)/lib/GL/mesa/src/triangle.o \
	$(OBJDIR)/lib/GL/mesa/src/varray.o \
	$(OBJDIR)/lib/GL/mesa/src/vb.o \
	$(OBJDIR)/lib/GL/mesa/src/vbcull.o \
	$(OBJDIR)/lib/GL/mesa/src/vbfill.o \
	$(OBJDIR)/lib/GL/mesa/src/vbindirect.o \
	$(OBJDIR)/lib/GL/mesa/src/vbrender.o \
	$(OBJDIR)/lib/GL/mesa/src/vbxform.o \
	$(OBJDIR)/lib/GL/mesa/src/vector.o \
	$(OBJDIR)/lib/GL/mesa/src/vertices.o \
	$(OBJDIR)/lib/GL/mesa/src/winpos.o \
	$(OBJDIR)/lib/GL/mesa/src/xform.o \
	$(OBJDIR)/lib/GL/mesa/src/zoom.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/common/hwlog.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/common/mm.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_context.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_dd.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_delay.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_eltpath.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_fastpath.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_fbmesa.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_ioctl.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_lock.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_pipeline.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_screen.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_span.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_state.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_tex.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_texmem.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_texstate.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_tris.o \
	$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_vb.o











OUTPUTCFLAGS := $(CFLAGS)\
	-I. \
	-Idri \
	-Idrivers/ati \
	-Iinclude \
	-Ikernel \
	-Ilib/GL/dri \
	-Ilib/GL/glfb \
	-Ilib/GL/mesa/dri/ \
	-Ilib/GL/mesa/src/ \
	-Ilib/GL/mesa/src/drv/common/ \
	-Ios-support \
	-Ios-support/linux/drm/kernel \
	-I../sdl/src/video \
	-I../sdl/src/video/fbcon \
	-I../sdl/include

















MESACFLAGS := $(OUTPUTCFLAGS) -DMESALIB -DNDEBUG


OUTPUTLIBS = \
	lib/GL/mesa/src/$(OBJDIR)/libmesa.so \

OUTPUT = $(OBJDIR)/libfbdri.a


KERNEL = $(OBJDIR)/kernel/radeonfb.o

DRM = os-support/linux/drm/kernel/radeon.o

TESTLIBS = \
	-lpthread \
	-lm \
	-lpng \
	-ldl \
	-lSDL \
	-L../sdl/src/.libs \
	$(OUTPUT) \
	$(QUICKTIMELIBS)


$(shell echo $(OUTPUTCFLAGS) > $(OBJDIR)/outputc_flags)
$(shell echo $(TESTCFLAGS) > $(OBJDIR)/testc_flags)
$(shell echo $(MESACFLAGS) > $(OBJDIR)/mesac_flags)

$(shell echo $(OUTPUTOBJS) > $(OBJDIR)/objs)
$(shell echo $(MESAOBJS) > $(OBJDIR)/mesaobjs)
$(shell echo $(TAILOBJS) > $(OBJDIR)/tailobjs)


all: $(OUTPUT) $(KERNEL) $(DRM)


$(OUTPUT): $(OBJDIRS) $(OUTPUTOBJS) $(MESAOBJS) $(TAILOBJS) 
	ar rcs $(OUTPUT) `cat $(OBJDIR)/objs` `cat $(OBJDIR)/mesaobjs` `cat $(OBJDIR)/tailobjs`

$(TEST1): $(TEST1OBJS)
	$(GCC) -o $(TEST1) $(TEST1OBJS) $(TESTLIBS)

$(TEST2): $(TEST2OBJS)
	$(GCC) -o $(TEST2) $(TEST2OBJS) $(TESTLIBS)

$(TEST3): $(TEST3OBJS)
	$(GCC) -o $(TEST3) $(TEST3OBJS) $(TESTLIBS)

mpeg2qt: mpeg2qt.c
	$(GCC) -o mpeg2qt mpeg2qt.c -I/amazon/root/libmpeg3 /amazon/root/libmpeg3/$(OBJDIR)/libmpeg3.a -lm -lquicktime -lpthread -lpng -ldl -lglib

$(TEST5): $(TEST5OBJS)
	$(GCC) -o $(TEST5) $(TEST5OBJS) $(TESTLIBS)

$(KERNEL): kernel/radeonfb.c
	$(GCC) -c -o $*.o $(subst $(OBJDIR)/,, $*.c) \
		 -D__KERNEL__ -I/usr/src/linux/include \
		 -Ikernel \
		 -Wall -Wstrict-prototypes -Wno-trigraphs -O2 \
		 -fomit-frame-pointer -fno-strict-aliasing -fno-common \
		 -pipe -DMODULE \
		 -DMODVERSIONS -include \
		 /usr/src/linux/include/linux/modversions.h

$(DRM):
	make -C os-support/linux/drm/kernel/


install: $(OUTPUT)
	cp $(OUTPUT) $(TARGET)/lib/libglfb.so


$(OBJDIRS):
	if ! test -d $@ ; then mkdir -p $@ ; fi

$(TEST1OBJS) $(TEST2OBJS) $(TEST3OBJS) $(TEST5OBJS):
	$(GCC) -c `cat $(OBJDIR)/testc_flags` $(subst $(OBJDIR)/,, $*.c) -o $*.o

$(OUTPUTOBJS):
	$(GCC) -c `cat $(OBJDIR)/outputc_flags` $(subst $(OBJDIR)/,, $*.c) -o $*.o

$(MESAOBJS):
	$(GCC) -c `cat $(OBJDIR)/mesac_flags` $(subst $(OBJDIR)/,, $*.c) -o $*.o

$(TAILOBJS):
	$(GCC) -c `cat $(OBJDIR)/outputc_flags` $(subst $(OBJDIR)/,, $*.c) -o $*.o


clean:
	rm -f $(OUTPUT);
	find -name c_flags -exec rm {} \;
	rm -rf $(OBJDIR)
	find \( -name core \
		-o -name '*.o' \
		-o -name '*.a' \
		-o -name '.libs' \
		-o -name '*.so' \) -exec rm -rf {} \;

$(OBJDIR)/dri/dri.o: 					    				dri/dri.c
$(OBJDIR)/drivers/ati/radeon_accel.o:						drivers/ati/radeon_accel.c
$(OBJDIR)/drivers/ati/radeon_dri.o: 						drivers/ati/radeon_dri.c
$(OBJDIR)/drivers/ati/radeon_driver.o: 						drivers/ati/radeon_driver.c
$(OBJDIR)/lib/GL/dri/dri_glfb.o: 			    			lib/GL/dri/dri_glfb.c
$(OBJDIR)/lib/GL/dri/fbdri.o: 			    				lib/GL/dri/fbdri.c
$(OBJDIR)/lib/GL/dri/fbdrimain.o: 			    			lib/GL/dri/fbdrimain.c
$(OBJDIR)/lib/GL/glfb/g_render.o: 			    			lib/GL/glfb/g_render.c
$(OBJDIR)/lib/GL/glfb/g_single.o: 			    			lib/GL/glfb/g_single.c
$(OBJDIR)/lib/GL/glfb/glfbcmds.o: 			    			lib/GL/glfb/glfbcmds.c
$(OBJDIR)/lib/GL/glfb/glfbext.o: 			    			lib/GL/glfb/glfbext.c
$(OBJDIR)/lib/GL/glfb/pixel.o: 			        			lib/GL/glfb/pixel.c
$(OBJDIR)/lib/GL/glfb/pixelstore.o: 						lib/GL/glfb/pixelstore.c
$(OBJDIR)/lib/GL/glfb/render2.o: 			    			lib/GL/glfb/render2.c
$(OBJDIR)/lib/GL/glfb/vertarr.o: 			    			lib/GL/glfb/vertarr.c
$(OBJDIR)/lib/GL/mesa/dri/dri_mesa.o: 						lib/GL/mesa/dri/dri_mesa.c
$(OBJDIR)/lib/GL/mesa/src/aatriangle.o: 					lib/GL/mesa/src/aatriangle.c
$(OBJDIR)/lib/GL/mesa/src/accum.o: 			    			lib/GL/mesa/src/accum.c
$(OBJDIR)/lib/GL/mesa/src/alpha.o: 			    			lib/GL/mesa/src/alpha.c
$(OBJDIR)/lib/GL/mesa/src/alphabuf.o: 						lib/GL/mesa/src/alphabuf.c
$(OBJDIR)/lib/GL/mesa/src/attrib.o: 						lib/GL/mesa/src/attrib.c
$(OBJDIR)/lib/GL/mesa/src/bbox.o: 			    			lib/GL/mesa/src/bbox.c
$(OBJDIR)/lib/GL/mesa/src/bitmap.o: 						lib/GL/mesa/src/bitmap.c
$(OBJDIR)/lib/GL/mesa/src/blend.o: 			    			lib/GL/mesa/src/blend.c
$(OBJDIR)/lib/GL/mesa/src/buffers.o: 						lib/GL/mesa/src/buffers.c
$(OBJDIR)/lib/GL/mesa/src/clip.o: 			    			lib/GL/mesa/src/clip.c
$(OBJDIR)/lib/GL/mesa/src/colortab.o: 						lib/GL/mesa/src/colortab.c
$(OBJDIR)/lib/GL/mesa/src/config.o: 						lib/GL/mesa/src/config.c
$(OBJDIR)/lib/GL/mesa/src/context.o: 						lib/GL/mesa/src/context.c
$(OBJDIR)/lib/GL/mesa/src/copypix.o: 						lib/GL/mesa/src/copypix.c
$(OBJDIR)/lib/GL/mesa/src/cva.o: 			    			lib/GL/mesa/src/cva.c
$(OBJDIR)/lib/GL/mesa/src/debug_xform.o: 					lib/GL/mesa/src/debug_xform.c
$(OBJDIR)/lib/GL/mesa/src/depth.o: 			    			lib/GL/mesa/src/depth.c
$(OBJDIR)/lib/GL/mesa/src/dlist.o: 			    			lib/GL/mesa/src/dlist.c
$(OBJDIR)/lib/GL/mesa/src/drawpix.o: 						lib/GL/mesa/src/drawpix.c
$(OBJDIR)/lib/GL/mesa/src/enable.o: 						lib/GL/mesa/src/enable.c
$(OBJDIR)/lib/GL/mesa/src/enums.o: 			    			lib/GL/mesa/src/enums.c
$(OBJDIR)/lib/GL/mesa/src/eval.o: 			    			lib/GL/mesa/src/eval.c
$(OBJDIR)/lib/GL/mesa/src/extensions.o: 					lib/GL/mesa/src/extensions.c
$(OBJDIR)/lib/GL/mesa/src/feedback.o: 						lib/GL/mesa/src/feedback.c
$(OBJDIR)/lib/GL/mesa/src/fog.o: 			    			lib/GL/mesa/src/fog.c
$(OBJDIR)/lib/GL/mesa/src/get.o: 			    			lib/GL/mesa/src/get.c
$(OBJDIR)/lib/GL/mesa/src/glapi.o: 			    			lib/GL/mesa/src/glapi.c
$(OBJDIR)/lib/GL/mesa/src/hash.o: 			    			lib/GL/mesa/src/hash.c
$(OBJDIR)/lib/GL/mesa/src/hint.o: 			    			lib/GL/mesa/src/hint.c
$(OBJDIR)/lib/GL/mesa/src/image.o: 			    			lib/GL/mesa/src/image.c
$(OBJDIR)/lib/GL/mesa/src/imaging.o: 						lib/GL/mesa/src/imaging.c
$(OBJDIR)/lib/GL/mesa/src/light.o: 			    			lib/GL/mesa/src/light.c
$(OBJDIR)/lib/GL/mesa/src/lines.o: 			    			lib/GL/mesa/src/lines.c
$(OBJDIR)/lib/GL/mesa/src/logic.o: 			    			lib/GL/mesa/src/logic.c
$(OBJDIR)/lib/GL/mesa/src/masking.o: 						lib/GL/mesa/src/masking.c
$(OBJDIR)/lib/GL/mesa/src/matrix.o: 						lib/GL/mesa/src/matrix.c
$(OBJDIR)/lib/GL/mesa/src/mem.o: 			    			lib/GL/mesa/src/mem.c
$(OBJDIR)/lib/GL/mesa/src/mmath.o: 			    			lib/GL/mesa/src/mmath.c
$(OBJDIR)/lib/GL/mesa/src/pb.o: 			    			lib/GL/mesa/src/pb.c
$(OBJDIR)/lib/GL/mesa/src/pipeline.o: 						lib/GL/mesa/src/pipeline.c
$(OBJDIR)/lib/GL/mesa/src/pixel.o: 			    			lib/GL/mesa/src/pixel.c
$(OBJDIR)/lib/GL/mesa/src/pixeltex.o: 						lib/GL/mesa/src/pixeltex.c
$(OBJDIR)/lib/GL/mesa/src/points.o: 						lib/GL/mesa/src/points.c
$(OBJDIR)/lib/GL/mesa/src/polygon.o: 						lib/GL/mesa/src/polygon.c
$(OBJDIR)/lib/GL/mesa/src/quads.o: 			    			lib/GL/mesa/src/quads.c
$(OBJDIR)/lib/GL/mesa/src/rastpos.o: 						lib/GL/mesa/src/rastpos.c
$(OBJDIR)/lib/GL/mesa/src/readpix.o: 						lib/GL/mesa/src/readpix.c
$(OBJDIR)/lib/GL/mesa/src/rect.o: 			    			lib/GL/mesa/src/rect.c
$(OBJDIR)/lib/GL/mesa/src/scissor.o: 						lib/GL/mesa/src/scissor.c
$(OBJDIR)/lib/GL/mesa/src/shade.o: 			    			lib/GL/mesa/src/shade.c
$(OBJDIR)/lib/GL/mesa/src/span.o: 			    			lib/GL/mesa/src/span.c
$(OBJDIR)/lib/GL/mesa/src/stages.o: 						lib/GL/mesa/src/stages.c
$(OBJDIR)/lib/GL/mesa/src/state.o: 			    			lib/GL/mesa/src/state.c
$(OBJDIR)/lib/GL/mesa/src/stencil.o: 						lib/GL/mesa/src/stencil.c
$(OBJDIR)/lib/GL/mesa/src/texformat.o:  					lib/GL/mesa/src/texformat.c
$(OBJDIR)/lib/GL/mesa/src/teximage.o: 						lib/GL/mesa/src/teximage.c
$(OBJDIR)/lib/GL/mesa/src/texobj.o: 						lib/GL/mesa/src/texobj.c
$(OBJDIR)/lib/GL/mesa/src/texstate.o: 						lib/GL/mesa/src/texstate.c
$(OBJDIR)/lib/GL/mesa/src/texture.o: 						lib/GL/mesa/src/texture.c
$(OBJDIR)/lib/GL/mesa/src/texutil.o: 						lib/GL/mesa/src/texutil.c
$(OBJDIR)/lib/GL/mesa/src/translate.o:  					lib/GL/mesa/src/translate.c
$(OBJDIR)/lib/GL/mesa/src/triangle.o: 						lib/GL/mesa/src/triangle.c
$(OBJDIR)/lib/GL/mesa/src/varray.o: 						lib/GL/mesa/src/varray.c
$(OBJDIR)/lib/GL/mesa/src/vb.o: 			    			lib/GL/mesa/src/vb.c
$(OBJDIR)/lib/GL/mesa/src/vbcull.o: 						lib/GL/mesa/src/vbcull.c
$(OBJDIR)/lib/GL/mesa/src/vbfill.o: 						lib/GL/mesa/src/vbfill.c
$(OBJDIR)/lib/GL/mesa/src/vbindirect.o: 					lib/GL/mesa/src/vbindirect.c
$(OBJDIR)/lib/GL/mesa/src/vbrender.o: 						lib/GL/mesa/src/vbrender.c
$(OBJDIR)/lib/GL/mesa/src/vbxform.o: 						lib/GL/mesa/src/vbxform.c
$(OBJDIR)/lib/GL/mesa/src/vector.o: 						lib/GL/mesa/src/vector.c
$(OBJDIR)/lib/GL/mesa/src/vertices.o: 						lib/GL/mesa/src/vertices.c
$(OBJDIR)/lib/GL/mesa/src/winpos.o: 						lib/GL/mesa/src/winpos.c
$(OBJDIR)/lib/GL/mesa/src/xform.o: 			    			lib/GL/mesa/src/xform.c
$(OBJDIR)/lib/GL/mesa/src/zoom.o: 			    			lib/GL/mesa/src/zoom.c
$(OBJDIR)/lib/GL/mesa/src/drv/common/hwlog.o: 				lib/GL/mesa/src/drv/common/hwlog.c
$(OBJDIR)/lib/GL/mesa/src/drv/common/mm.o: 					lib/GL/mesa/src/drv/common/mm.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_context.o:      lib/GL/mesa/src/drv/radeon/radeon_context.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_dd.o:           lib/GL/mesa/src/drv/radeon/radeon_dd.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_delay.o:        lib/GL/mesa/src/drv/radeon/radeon_delay.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_eltpath.o:      lib/GL/mesa/src/drv/radeon/radeon_eltpath.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_fastpath.o:     lib/GL/mesa/src/drv/radeon/radeon_fastpath.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_fbmesa.o: 	    lib/GL/mesa/src/drv/radeon/radeon_fbmesa.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_ioctl.o:        lib/GL/mesa/src/drv/radeon/radeon_ioctl.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_lock.o:         lib/GL/mesa/src/drv/radeon/radeon_lock.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_pipeline.o:     lib/GL/mesa/src/drv/radeon/radeon_pipeline.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_screen.o: 	    lib/GL/mesa/src/drv/radeon/radeon_screen.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_span.o: 	    lib/GL/mesa/src/drv/radeon/radeon_span.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_state.o: 	    lib/GL/mesa/src/drv/radeon/radeon_state.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_tex.o:          lib/GL/mesa/src/drv/radeon/radeon_tex.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_texmem.o:       lib/GL/mesa/src/drv/radeon/radeon_texmem.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_texstate.o:     lib/GL/mesa/src/drv/radeon/radeon_texstate.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_tris.o:         lib/GL/mesa/src/drv/radeon/radeon_tris.c
$(OBJDIR)/lib/GL/mesa/src/drv/radeon/radeon_vb.o:           lib/GL/mesa/src/drv/radeon/radeon_vb.c
$(OBJDIR)/os-support/linux/drm/fbdrm.o: 		    		os-support/linux/drm/fbdrm.c
$(OBJDIR)/os-support/linux/drm/fbdrmHash.o:                 os-support/linux/drm/fbdrmHash.c
$(OBJDIR)/os-support/linux/drm/fbdrmRadeon.o:               os-support/linux/drm/fbdrmRadeon.c
$(OBJDIR)/stubs.o: 					    					stubs.c
$(OBJDIR)/testcube.o: 					testcube.c
$(OBJDIR)/testpng.o: 					testpng.c
$(OBJDIR)/testyuv.o: 					testyuv.c
$(OBJDIR)/testsinc.o: 					testsinc.c
$(OBJDIR)/animation.o: 					animation.c

#
# glu library
#

$(OBJDIR)/lib/GL/mesa/src-glu/glu.o: lib/GL/mesa/src-glu/glu.c
$(OBJDIR)/lib/GL/mesa/src-glu/mipmap.o: lib/GL/mesa/src-glu/mipmap.c
$(OBJDIR)/lib/GL/mesa/src-glu/nurbs.o: lib/GL/mesa/src-glu/nurbs.c
$(OBJDIR)/lib/GL/mesa/src-glu/nurbscrv.o: lib/GL/mesa/src-glu/nurbscrv.c
$(OBJDIR)/lib/GL/mesa/src-glu/nurbssrf.o: lib/GL/mesa/src-glu/nurbssrf.c
$(OBJDIR)/lib/GL/mesa/src-glu/nurbsutl.o: lib/GL/mesa/src-glu/nurbsutl.c
$(OBJDIR)/lib/GL/mesa/src-glu/polytest.o: lib/GL/mesa/src-glu/polytest.c
$(OBJDIR)/lib/GL/mesa/src-glu/project.o: lib/GL/mesa/src-glu/project.c
$(OBJDIR)/lib/GL/mesa/src-glu/quadric.o: lib/GL/mesa/src-glu/quadric.c
$(OBJDIR)/lib/GL/mesa/src-glu/tess.o: lib/GL/mesa/src-glu/tess.c
$(OBJDIR)/lib/GL/mesa/src-glu/tesselat.o: lib/GL/mesa/src-glu/tesselat.c
