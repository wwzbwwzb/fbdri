include ../../../../../utils/global_config




OBJS = \
	$(OBJDIR)/aatriangle.o \
	$(OBJDIR)/accum.o \
	$(OBJDIR)/alpha.o \
	$(OBJDIR)/alphabuf.o \
	$(OBJDIR)/attrib.o \
	$(OBJDIR)/bbox.o \
	$(OBJDIR)/bitmap.o \
	$(OBJDIR)/blend.o \
	$(OBJDIR)/buffers.o \
	$(OBJDIR)/clip.o \
	$(OBJDIR)/colortab.o \
	$(OBJDIR)/config.o \
	$(OBJDIR)/context.o \
	$(OBJDIR)/copypix.o \
	$(OBJDIR)/cva.o \
	$(OBJDIR)/debug_xform.o \
	$(OBJDIR)/depth.o \
	$(OBJDIR)/dlist.o \
	$(OBJDIR)/drawpix.o \
	$(OBJDIR)/enable.o \
	$(OBJDIR)/enums.o \
	$(OBJDIR)/eval.o \
	$(OBJDIR)/extensions.o \
	$(OBJDIR)/feedback.o \
	$(OBJDIR)/fog.o \
	$(OBJDIR)/get.o \
	$(OBJDIR)/hash.o \
	$(OBJDIR)/hint.o \
	$(OBJDIR)/image.o \
	$(OBJDIR)/imaging.o \
	$(OBJDIR)/light.o \
	$(OBJDIR)/lines.o \
	$(OBJDIR)/logic.o \
	$(OBJDIR)/masking.o \
	$(OBJDIR)/matrix.o \
	$(OBJDIR)/mem.o \
	$(OBJDIR)/mmath.o \
	$(OBJDIR)/pb.o \
	$(OBJDIR)/pipeline.o \
	$(OBJDIR)/pixel.o \
	$(OBJDIR)/pixeltex.o \
	$(OBJDIR)/points.o \
	$(OBJDIR)/polygon.o \
	$(OBJDIR)/quads.o \
	$(OBJDIR)/rastpos.o \
	$(OBJDIR)/readpix.o \
	$(OBJDIR)/rect.o \
	$(OBJDIR)/scissor.o \
	$(OBJDIR)/shade.o \
	$(OBJDIR)/span.o \
	$(OBJDIR)/stages.o \
	$(OBJDIR)/state.o \
	$(OBJDIR)/stencil.o \
	$(OBJDIR)/texformat.o \
	$(OBJDIR)/teximage.o \
	$(OBJDIR)/texobj.o \
	$(OBJDIR)/texstate.o \
	$(OBJDIR)/texture.o \
	$(OBJDIR)/texutil.o \
	$(OBJDIR)/translate.o \
	$(OBJDIR)/triangle.o \
	$(OBJDIR)/varray.o \
	$(OBJDIR)/vb.o \
	$(OBJDIR)/vbcull.o \
	$(OBJDIR)/vbfill.o \
	$(OBJDIR)/vbindirect.o \
	$(OBJDIR)/vbrender.o \
	$(OBJDIR)/vbxform.o \
	$(OBJDIR)/vector.o \
	$(OBJDIR)/vertices.o \
	$(OBJDIR)/winpos.o \
	$(OBJDIR)/xform.o \
	$(OBJDIR)/zoom.o




CFLAGS += -I. \
	-I../../../../include

OUTPUT = $(OBJDIR)/libmesa.so


$(shell echo $(CFLAGS) > i686/c_flags)


$(OUTPUT): $(OBJS) drv
	make -C drv
	gcc -shared -o $(OUTPUT) $(OBJS)

drv:
	make -C drv

clean:
	rm -rf $(OBJDIR)


$(OBJS):
	$(GCC) -c `cat $(OBJDIR)/c_flags` $(subst $(OBJDIR)/,, $*.c) -o $*.o



$(OBJDIR)/aatriangle.o: 	     aatriangle.c
$(OBJDIR)/accum.o:   		     accum.c
$(OBJDIR)/alpha.o:   		     alpha.c
$(OBJDIR)/alphabuf.o: 	 	     alphabuf.c
$(OBJDIR)/attrib.o: 	 	     attrib.c
$(OBJDIR)/bbox.o:    		     bbox.c
$(OBJDIR)/bitmap.o: 	 	     bitmap.c
$(OBJDIR)/blend.o:   		     blend.c
$(OBJDIR)/buffers.o: 	 	     buffers.c
$(OBJDIR)/clip.o:    		     clip.c
$(OBJDIR)/colortab.o: 	 	     colortab.c
$(OBJDIR)/config.o: 	 	     config.c
$(OBJDIR)/context.o: 	 	     context.c
$(OBJDIR)/copypix.o: 	 	     copypix.c
$(OBJDIR)/cva.o: 	 	     cva.c
$(OBJDIR)/debug_xform.o: 	     debug_xform.c
$(OBJDIR)/depth.o:   		     depth.c
$(OBJDIR)/dlist.o:  		     dlist.c
$(OBJDIR)/drawpix.o: 	 	     drawpix.c
$(OBJDIR)/enable.o: 	 	     enable.c
$(OBJDIR)/enums.o:   		     enums.c
$(OBJDIR)/eval.o:    		     eval.c
$(OBJDIR)/extensions.o: 	     extensions.c
$(OBJDIR)/feedback.o: 	 	     feedback.c
$(OBJDIR)/fog.o: 	 	     fog.c
$(OBJDIR)/get.o: 		     get.c
$(OBJDIR)/hash.o:    		     hash.c
$(OBJDIR)/hint.o:    		     hint.c
$(OBJDIR)/image.o:   		     image.c
$(OBJDIR)/imaging.o: 	 	     imaging.c
$(OBJDIR)/light.o:   		     light.c
$(OBJDIR)/lines.o:   		     lines.c
$(OBJDIR)/logic.o:   		     logic.c
$(OBJDIR)/masking.o: 	 	     masking.c
$(OBJDIR)/matrix.o: 	 	     matrix.c
$(OBJDIR)/mem.o: 	 	     mem.c
$(OBJDIR)/mmath.o:   		     mmath.c
$(OBJDIR)/pb.o: 	 	     pb.c
$(OBJDIR)/pipeline.o: 	 	     pipeline.c
$(OBJDIR)/pixel.o:   		     pixel.c
$(OBJDIR)/pixeltex.o: 	 	     pixeltex.c
$(OBJDIR)/points.o: 	 	     points.c
$(OBJDIR)/polygon.o: 	 	     polygon.c
$(OBJDIR)/quads.o:   		     quads.c
$(OBJDIR)/rastpos.o: 	 	     rastpos.c
$(OBJDIR)/readpix.o: 	 	     readpix.c
$(OBJDIR)/rect.o:    		     rect.c
$(OBJDIR)/scissor.o: 	 	     scissor.c
$(OBJDIR)/shade.o:   		     shade.c
$(OBJDIR)/span.o:    		     span.c
$(OBJDIR)/stages.o: 	 	     stages.c
$(OBJDIR)/state.o:   		     state.c
$(OBJDIR)/stencil.o: 	 	     stencil.c
$(OBJDIR)/texformat.o: 	 	     texformat.c
$(OBJDIR)/teximage.o: 	 	     teximage.c
$(OBJDIR)/texobj.o: 	 	     texobj.c
$(OBJDIR)/texstate.o: 	 	     texstate.c
$(OBJDIR)/texture.o: 	 	     texture.c
$(OBJDIR)/texutil.o: 	 	     texutil.c
$(OBJDIR)/translate.o: 	 	     translate.c
$(OBJDIR)/triangle.o: 	 	     triangle.c
$(OBJDIR)/varray.o: 	 	     varray.c
$(OBJDIR)/vb.o: 	 	     vb.c
$(OBJDIR)/vbcull.o: 	 	     vbcull.c
$(OBJDIR)/vbfill.o: 	 	     vbfill.c
$(OBJDIR)/vbindirect.o: 	     vbindirect.c
$(OBJDIR)/vbrender.o: 	 	     vbrender.c
$(OBJDIR)/vbxform.o: 	 	     vbxform.c
$(OBJDIR)/vector.o: 	 	     vector.c
$(OBJDIR)/vertices.o: 	 	     vertices.c
$(OBJDIR)/winpos.o: 	 	     winpos.c
$(OBJDIR)/xform.o:   		     xform.c
$(OBJDIR)/zoom.o: 		     zoom.c
