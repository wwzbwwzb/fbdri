/* $XFree86: xc/lib/GL/dri/xf86dri.h,v 1.7 2000/12/07 20:26:02 dawes Exp $ */
/**************************************************************************

Copyright 1998-1999 Precision Insight, Inc., Cedar Park, Texas.
Copyright 2000 VA Linux Systems, Inc.
All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sub license, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice (including the
next paragraph) shall be included in all copies or substantial portions
of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
IN NO EVENT SHALL PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR
ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

**************************************************************************/

/*
 * Authors:
 *   Kevin E. Martin <martin@valinux.com>
 *   Jens Owen <jens@valinux.com>
 *   Rickard E. (Rik) Faith <faith@valinux.com>
 *
 */

#ifndef _FBDRI_H_
#define _FBDRI_H_




#if 0


//#include <X11/Xfuncproto.h>
#include "fbdrm.h"
#include "GL/glfb.h"
#include "GL/xreplacements.h"

#define X_FBDRIQueryVersion			0
#define X_FBDRIQueryDirectRenderingCapable	1
#define X_FBDRIOpenConnection			2
#define X_FBDRICloseConnection		3
#define X_FBDRIGetClientDriverName		4
#define X_FBDRICreateContext			5
#define X_FBDRIDestroyContext			6
#define X_FBDRICreateDrawable			7
#define X_FBDRIDestroyDrawable		8
#define X_FBDRIGetDrawableInfo		9
#define X_FBDRIGetDeviceInfo			10
#define X_FBDRIAuthConnection                 11
#define X_FBDRIOpenFullScreen                 12
#define X_FBDRICloseFullScreen                13

#endif // 0






#define FBDRINumberEvents		0

#define FBDRIClientNotLocal		0
#define FBDRIOperationNotSupported	1
#define FBDRINumberErrors		(FBDRIOperationNotSupported + 1)

/* Warning : Do not change FBDRIClipRect without changing the kernel 
 * structure! */
typedef struct _FBDRIClipRect {
    unsigned short	x1; /* Upper left: inclusive */
    unsigned short	y1;
    unsigned short	x2; /* Lower right: exclusive */
    unsigned short	y2;
} FBDRIClipRectRec, *FBDRIClipRectPtr;





#endif /* _FBDRI_H_ */

