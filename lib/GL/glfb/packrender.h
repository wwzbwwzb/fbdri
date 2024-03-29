/* $XFree86: xc/lib/GL/glx/packrender.h,v 1.6 2001/03/21 16:04:39 dawes Exp $ */
#ifndef __GLFB_packrender_h__
#define __GLFB_packrender_h__

/*
** License Applicability. Except to the extent portions of this file are
** made subject to an alternative license as permitted in the SGI Free
** Software License B, Version 1.1 (the "License"), the contents of this
** file are subject only to the provisions of the License. You may not use
** this file except in compliance with the License. You may obtain a copy
** of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
** Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
** 
** http://oss.sgi.com/projects/FreeB
** 
** Note that, as provided in the License, the Software is distributed on an
** "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
** DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
** CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
** PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
** 
** Original Code. The Original Code is: OpenGL Sample Implementation,
** Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
** Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
** Copyright in any portions created by third parties is as indicated
** elsewhere herein. All Rights Reserved.
** 
** Additional Notice Provisions: The application programming interfaces
** established by SGI in conjunction with the Original Code are The
** OpenGL(R) Graphics System: A Specification (Version 1.2.1), released
** April 1, 1999; The OpenGL(R) Graphics System Utility Library (Version
** 1.3), released November 4, 1998; and OpenGL(R) Graphics with the X
** Window System(R) (Version 1.3), released October 19, 1998. This software
** was created using the OpenGL(R) version 1.2.1 Sample Implementation
** published by SGI, but has not been independently verified as being
** compliant with the OpenGL(R) version 1.2.1 Specification.
**
*/

#define NEED_GL_FUNCS_WRAPPED
#include "glfbclient.h"

/*
** The macros in this header convert the client machine's native data types to
** wire protocol data types.  The header is part of the porting layer of the
** client library, and it is intended that hardware vendors will rewrite this
** header to suit their own machines.
*/

/*
** Pad a count of bytes to the nearest multiple of 4.  The X protocol
** transfers data in 4 byte quantities, so this macro is used to
** insure the right amount of data being sent.
*/
#define __GLFB_PAD(a) (((a)+3) & ~3)

/*
 ** Network size parameters
 */
#define sz_double 8

/* Setup for all commands */
#define __GLFB_DECLARE_VARIABLES() \
    __GLFBcontext *gc;		  \
    GLubyte *pc, *pixelHeaderPC;  \
    GLuint compsize, cmdlen

#define __GLFB_LOAD_VARIABLES()	   \
    gc = __glXGetCurrentContext(); \
    pc = gc->pc;                   \
    (void) cmdlen;                 \
    (void) compsize;               \
    (void) pixelHeaderPC

/*
** Variable sized command support macro.  This macro is used by calls
** that are potentially larger than __GLFB_SMALL_RENDER_CMD_SIZE.
** Because of their size, they may not automatically fit in the buffer.
** If the buffer can't hold the command then it is flushed so that
** the command will fit in the next buffer.
*/
#define __GLFB_BEGIN_VARIABLE(opcode,size)	\
    if (pc + (size) > gc->bufEnd) {		\
	pc = __glXFlushRenderBuffer(gc, pc);	\
    }						\
    __GLFB_PUT_SHORT(0,size);			\
    __GLFB_PUT_SHORT(2,opcode)

#define __GLFB_BEGIN_VARIABLE_LARGE(opcode,size)	\
    pc = __glXFlushRenderBuffer(gc, pc);	\
    __GLFB_PUT_LONG(0,size);			\
    __GLFB_PUT_LONG(4,opcode)

#define __GLFB_BEGIN_VARIABLE_WITH_PIXEL(opcode,size) \
    if (pc + (size) > gc->bufEnd) {		     \
	pc = __glXFlushRenderBuffer(gc, pc);	     \
    }						     \
    __GLFB_PUT_SHORT(0,size);			     \
    __GLFB_PUT_SHORT(2,opcode);			     \
    pc += __GLFB_RENDER_HDR_SIZE;		     \
    pixelHeaderPC = pc;				     \
    pc += __GLFB_PIXEL_HDR_SIZE

#define __GLFB_BEGIN_VARIABLE_LARGE_WITH_PIXEL(opcode,size) \
    pc = __glXFlushRenderBuffer(gc, pc);		   \
    __GLFB_PUT_LONG(0,size);				   \
    __GLFB_PUT_LONG(4,opcode);				   \
    pc += __GLFB_RENDER_LARGE_HDR_SIZE;			   \
    pixelHeaderPC = pc;					   \
    pc += __GLFB_PIXEL_HDR_SIZE

#define __GLFB_BEGIN_VARIABLE_WITH_PIXEL_3D(opcode,size) \
    if (pc + (size) > gc->bufEnd) {		        \
	pc = __glXFlushRenderBuffer(gc, pc); 	        \
    }						        \
    __GLFB_PUT_SHORT(0,size);			        \
    __GLFB_PUT_SHORT(2,opcode);			        \
    pc += __GLFB_RENDER_HDR_SIZE;		        \
    pixelHeaderPC = pc;				        \
    pc += __GLFB_PIXEL_3D_HDR_SIZE

#define __GLFB_BEGIN_VARIABLE_LARGE_WITH_PIXEL_3D(opcode,size) \
    pc = __glXFlushRenderBuffer(gc, pc);	   	      \
    __GLFB_PUT_LONG(0,size);				      \
    __GLFB_PUT_LONG(4,opcode);				      \
    pc += __GLFB_RENDER_LARGE_HDR_SIZE;			      \
    pixelHeaderPC = pc;					      \
    pc += __GLFB_PIXEL_3D_HDR_SIZE

/*
** Fixed size command support macro.  This macro is used by calls that
** are never larger than __GLFB_SMALL_RENDER_CMD_SIZE.  Because they
** always fit in the buffer, and because the buffer promises to
** maintain enough room for them, we don't need to check for space
** before doing the storage work.
*/
#define __GLFB_BEGIN(opcode,size) \
    __GLFB_PUT_SHORT(0,size);     \
    __GLFB_PUT_SHORT(2,opcode)

/*
** Finish a rendering command by advancing the pc.  If the pc is now past
** the limit pointer then there is no longer room for a
** __GLFB_SMALL_RENDER_CMD_SIZE sized command, which will break the
** assumptions present in the __GLFB_BEGIN macro.  In this case the
** rendering buffer is flushed out into the X protocol stream (which may
** or may not do I/O).
*/
#define __GLFB_END(size)			       \
    pc += size;				       \
    if (pc > gc->limit) {		       \
	(void) __glXFlushRenderBuffer(gc, pc); \
    } else {				       \
	gc->pc = pc;			       \
    }

/* Array copy macros */
#define __GLFB_MEM_COPY(dest,src,bytes) \
    memcpy(dest, src, bytes)

/* Single item copy macros */
#define __GLFB_PUT_CHAR(offset,a) \
    *((int8_t *) (pc + offset)) = a

#ifndef _CRAY
#define __GLFB_PUT_SHORT(offset,a) \
    *((int16_t *) (pc + offset)) = a

#define __GLFB_PUT_LONG(offset,a) \
    *((int32_t *) (pc + offset)) = a

#define __GLFB_PUT_FLOAT(offset,a) \
    *((FLOAT32 *) (pc + offset)) = a

#else
#define __GLFB_PUT_SHORT(offset,a) \
 { GLubyte *cp = (pc+offset); \
   int shift = (64-16) - ((int)(cp) >> (64-6)); \
   *(int *)cp = (*(int *)cp & ~(0xffff << shift)) | ((a & 0xffff) << shift); }

#define __GLFB_PUT_LONG(offset,a) \
 { GLubyte *cp = (pc+offset); \
   int shift = (64-32) - ((int)(cp) >> (64-6)); \
   *(int *)cp = (*(int *)cp & ~(0xffffffff << shift)) | ((a & 0xffffffff) << shift); }

#define __GLFB_PUT_FLOAT(offset,a) \
    gl_put_float((pc + offset),a)

#define __GLFB_PUT_DOUBLE(offset,a) \
    gl_put_double(pc + offset, a)

extern void gl_put_float(/*GLubyte *, struct cray_single*/);
extern void gl_put_double(/*GLubyte *, struct cray_double*/);
#endif

#ifndef _CRAY

#ifdef __GLFB_ALIGN64
/*
** This can certainly be done better for a particular machine
** architecture!
*/
#define __GLFB_PUT_DOUBLE(offset,a) \
    __GLFB_MEM_COPY(pc + offset, &a, 8)
#else
#define __GLFB_PUT_DOUBLE(offset,a) \
    *((FLOAT64 *) (pc + offset)) = a
#endif

#endif

#define __GLFB_PUT_CHAR_ARRAY(offset,a,alen) \
    __GLFB_MEM_COPY(pc + offset, a, alen * __GLFB_SIZE_int8_t)

#ifndef _CRAY
#define __GLFB_PUT_SHORT_ARRAY(offset,a,alen) \
    __GLFB_MEM_COPY(pc + offset, a, alen * __GLFB_SIZE_int16_t)

#define __GLFB_PUT_LONG_ARRAY(offset,a,alen) \
    __GLFB_MEM_COPY(pc + offset, a, alen * __GLFB_SIZE_int32_t)

#define __GLFB_PUT_FLOAT_ARRAY(offset,a,alen) \
    __GLFB_MEM_COPY(pc + offset, a, alen * __GLFB_SIZE_FLOAT32)

#define __GLFB_PUT_DOUBLE_ARRAY(offset,a,alen) \
    __GLFB_MEM_COPY(pc + offset, a, alen * __GLFB_SIZE_FLOAT64)

#else
#define __GLFB_PUT_SHORT_ARRAY(offset,a,alen) \
    gl_put_short_array((GLubyte *)(pc + offset), a, alen * __GLFB_SIZE_int16_t)

#define __GLFB_PUT_LONG_ARRAY(offset,a,alen) \
    gl_put_long_array((GLubyte *)(pc + offset), (long *)a, alen * __GLFB_SIZE_int32_t)

#define __GLFB_PUT_FLOAT_ARRAY(offset,a,alen) \
    gl_put_float_array((GLubyte *)(pc + offset), (float *)a, alen * __GLFB_SIZE_FLOAT32)

#define __GLFB_PUT_DOUBLE_ARRAY(offset,a,alen) \
    gl_put_double_array((GLubyte *)(pc + offset), (double *)a, alen * __GLFB_SIZE_FLOAT64)

extern gl_put_short_array (GLubyte *, short *, int);
extern gl_put_long_array (GLubyte *, long *, int);
extern gl_put_float_array (GLubyte *, float *, int);
extern gl_put_double_array (GLubyte *, double *, int);

#endif /* _CRAY */

#endif /* !__GLFB_packrender_h__ */
