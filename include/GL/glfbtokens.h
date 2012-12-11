#ifndef __GLFB_glxtokens_h__
#define __GLFB_glxtokens_h__

/* $XFree86: xc/include/GL/glxtokens.h,v 1.5 2001/03/21 15:51:38 dawes Exp $ */
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
*/

#ifdef __cplusplus
extern "C" {
#endif

#define GLFB_VERSION_1_1 1
#define GLFB_VERSION_1_2 1
#define GLFB_VERSION_1_3 1

/*
** Visual Config Attributes (glXGetConfig, glXGetFBConfigAttrib)
*/
#define GLFB_USE_GL		1	/* support GLFB rendering */
#define GLFB_BUFFER_SIZE		2	/* depth of the color buffer */
#define GLFB_LEVEL		3	/* level in plane stacking */
#define GLFB_RGBA		4	/* true if RGBA mode */
#define GLFB_DOUBLEBUFFER	5	/* double buffering supported */
#define GLFB_STEREO		6	/* stereo buffering supported */
#define GLFB_AUX_BUFFERS		7	/* number of aux buffers */
#define GLFB_RED_SIZE		8	/* number of red component bits */
#define GLFB_GREEN_SIZE		9	/* number of green component bits */
#define GLFB_BLUE_SIZE		10	/* number of blue component bits */
#define GLFB_ALPHA_SIZE		11	/* number of alpha component bits */
#define GLFB_DEPTH_SIZE		12	/* number of depth bits */
#define GLFB_STENCIL_SIZE	13	/* number of stencil bits */
#define GLFB_ACCUM_RED_SIZE	14	/* number of red accum bits */
#define GLFB_ACCUM_GREEN_SIZE	15	/* number of green accum bits */
#define GLFB_ACCUM_BLUE_SIZE	16	/* number of blue accum bits */
#define GLFB_ACCUM_ALPHA_SIZE	17	/* number of alpha accum bits */
/*
** FBConfig-specific attributes
*/
#define GLFB_X_VISUAL_TYPE		0x22
#define GLFB_CONFIG_CAVEAT		0x20	/* Like visual_info VISUAL_CAVEAT_EXT */
#define GLFB_TRANSPARENT_TYPE		0x23
#define GLFB_TRANSPARENT_INDEX_VALUE	0x24
#define GLFB_TRANSPARENT_RED_VALUE	0x25
#define GLFB_TRANSPARENT_GREEN_VALUE	0x26
#define GLFB_TRANSPARENT_BLUE_VALUE	0x27
#define GLFB_TRANSPARENT_ALPHA_VALUE	0x28
#define GLFB_DRAWABLE_TYPE		0x8010
#define GLFB_RENDER_TYPE			0x8011
#define GLFB_X_RENDERABLE		0x8012
#define GLFB_FBCONFIG_ID			0x8013
#define GLFB_MAX_PBUFFER_WIDTH		0x8016
#define GLFB_MAX_PBUFFER_HEIGHT		0x8017
#define GLFB_MAX_PBUFFER_PIXELS		0x8018
#define GLFB_VISUAL_ID			0x800B

/*
** Error return values from glXGetConfig.  Success is indicated by
** a value of 0.
*/
#define GLFB_BAD_SCREEN		1	/* screen # is bad */
#define GLFB_BAD_ATTRIBUTE	2	/* attribute to get is bad */
#define GLFB_NO_EXTENSION	3	/* no glx extension on server */
#define GLFB_BAD_VISUAL		4	/* visual # not known by GLFB */
#define GLFB_BAD_CONTEXT		5	/* returned only by import_context EXT? */
#define GLFB_BAD_VALUE		6	/* returned only by glXSwapIntervalSGI? */
#define GLFB_BAD_ENUM		7	/* unused? */

/* FBConfig attribute values */

/*
** Generic "don't care" value for glX ChooseFBConfig attributes (except
** GLFB_LEVEL)
*/
#define GLFB_DONT_CARE			0xFFFFFFFF

/* GLFB_RENDER_TYPE bits */
#define GLFB_RGBA_BIT			0x00000001
#define GLFB_COLOR_INDEX_BIT		0x00000002

/* GLFB_DRAWABLE_TYPE bits */
#define GLFB_WINDOW_BIT			0x00000001
#define GLFB_PIXMAP_BIT			0x00000002
#define GLFB_PBUFFER_BIT			0x00000004

/* GLFB_CONFIG_CAVEAT attribute values */
#define GLFB_NONE			0x8000
#define GLFB_SLOW_CONFIG			0x8001
#define GLFB_NON_CONFORMANT_CONFIG	0x800D

/* GLFB_X_VISUAL_TYPE attribute values */
#define GLFB_TRUE_COLOR			0x8002
#define GLFB_DIRECT_COLOR		0x8003
#define GLFB_PSEUDO_COLOR		0x8004
#define GLFB_STATIC_COLOR		0x8005
#define GLFB_GRAY_SCALE			0x8006
#define GLFB_STATIC_GRAY			0x8007

/* GLFB_TRANSPARENT_TYPE attribute values */
/* #define GLFB_NONE			   0x8000 */
#define GLFB_TRANSPARENT_RGB		0x8008
#define GLFB_TRANSPARENT_INDEX		0x8009

/* glXCreateGLFBPbuffer attributes */
#define GLFB_PRESERVED_CONTENTS		0x801B
#define GLFB_LARGEST_PBUFFER		0x801C
#define GLFB_PBUFFER_HEIGHT		0x8040	/* New for GLFB 1.3 */
#define GLFB_PBUFFER_WIDTH		0x8041	/* New for GLFB 1.3 */

/* glXQueryGLFBPBuffer attributes */
#define GLFB_WIDTH			0x801D
#define GLFB_HEIGHT			0x801E
#define GLFB_EVENT_MASK			0x801F

/* glXCreateNewContext render_type attribute values */
#define GLFB_RGBA_TYPE			0x8014
#define GLFB_COLOR_INDEX_TYPE		0x8015

/* glXQueryContext attributes */
/* #define GLFB_FBCONFIG_ID		  0x8013 */
/* #define GLFB_RENDER_TYPE		  0x8011 */
#define GLFB_SCREEN			0x800C

/* glXSelectEvent event mask bits */
#define GLFB_PBUFFER_CLOBBER_MASK	0x08000000

/* GLFBPbufferClobberEvent event_type values */
#define GLFB_DAMAGED			0x8020
#define GLFB_SAVED			0x8021

/* GLFBPbufferClobberEvent draw_type values */
#define GLFB_WINDOW			0x8022
#define GLFB_PBUFFER			0x8023

/* GLFBPbufferClobberEvent buffer_mask bits */
#define GLFB_FRONT_LEFT_BUFFER_BIT	0x00000001
#define GLFB_FRONT_RIGHT_BUFFER_BIT	0x00000002
#define GLFB_BACK_LEFT_BUFFER_BIT	0x00000004
#define GLFB_BACK_RIGHT_BUFFER_BIT	0x00000008
#define GLFB_AUX_BUFFERS_BIT		0x00000010
#define GLFB_DEPTH_BUFFER_BIT		0x00000020
#define GLFB_STENCIL_BUFFER_BIT		0x00000040
#define GLFB_ACCUM_BUFFER_BIT		0x00000080

/*
** Extension return values from glXGetConfig.  These are also
** accepted as parameter values for glXChooseVisual.
*/

#define GLFB_X_VISUAL_TYPE_EXT	0x22	/* visual_info extension type */
#define GLFB_TRANSPARENT_TYPE_EXT 0x23	/* visual_info extension */
#define GLFB_TRANSPARENT_INDEX_VALUE_EXT 0x24	/* visual_info extension */
#define GLFB_TRANSPARENT_RED_VALUE_EXT	0x25	/* visual_info extension */
#define GLFB_TRANSPARENT_GREEN_VALUE_EXT 0x26	/* visual_info extension */
#define GLFB_TRANSPARENT_BLUE_VALUE_EXT	0x27	/* visual_info extension */
#define GLFB_TRANSPARENT_ALPHA_VALUE_EXT 0x28	/* visual_info extension */

/* Property values for visual_type */
#define GLFB_TRUE_COLOR_EXT	0x8002
#define GLFB_DIRECT_COLOR_EXT	0x8003
#define GLFB_PSEUDO_COLOR_EXT	0x8004
#define GLFB_STATIC_COLOR_EXT	0x8005
#define GLFB_GRAY_SCALE_EXT	0x8006
#define GLFB_STATIC_GRAY_EXT	0x8007

/* Property values for transparent pixel */
#define GLFB_NONE_EXT		0x8000
#define GLFB_TRANSPARENT_RGB_EXT		0x8008
#define GLFB_TRANSPARENT_INDEX_EXT	0x8009

/* Property values for visual_rating */
#define GLFB_VISUAL_CAVEAT_EXT		0x20  /* visual_rating extension type */
#define GLFB_SLOW_VISUAL_EXT		0x8001
#define GLFB_NON_CONFORMANT_VISUAL_EXT	0x800D

/*
** Names for attributes to glXGetClientString.
*/
#define GLFB_VENDOR		0x1
#define GLFB_VERSION		0x2
#define GLFB_EXTENSIONS		0x3

/*
** Names for attributes to glXQueryContextInfoEXT.
*/
#define GLFB_SHARE_CONTEXT_EXT	0x800A	/* id of share context */
#define GLFB_VISUAL_ID_EXT	0x800B	/* id of context's visual */
#define GLFB_SCREEN_EXT		0x800C	/* screen number */

/* GLFB Extension Strings */
#define GLFB_EXT_import_context	1
#define GLFB_EXT_visual_info	1
#define GLFB_EXT_visual_rating	1
#define GLFB_ARB_get_proc_address 1

#ifdef __cplusplus
}
#endif

#endif /* !__GLFB_glxtokens_h__ */
