/* $XFree86: xc/lib/GL/mesa/src/drv/radeon/radeon_lock.c,v 1.3 2001/04/10 16:07:53 dawes Exp $ */
/**************************************************************************

Copyright 2000, 2001 ATI Technologies Inc., Ontario, Canada, and
                     VA Linux Systems Inc., Fremont, California.

All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
on the rights to use, copy, modify, merge, publish, distribute, sub
license, and/or sell copies of the Software, and to permit persons to whom
the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice (including the next
paragraph) shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
ATI, VA LINUX SYSTEMS AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
USE OR OTHER DEALINGS IN THE SOFTWARE.

**************************************************************************/

/*
 * Authors:
 *   Kevin E. Martin <martin@valinux.com>
 *   Gareth Hughes <gareth@valinux.com>
 *
 */

#include "radeon_context.h"
#include "radeon_lock.h"
#include "radeon_tex.h"

#if DEBUG_LOCKING
char *prevLockFile = NULL;
int prevLockLine = 0;
#endif


/* Update the hardware state.  This is called if another context has
 * grabbed the hardware lock, which includes the X server.  This
 * function also updates the driver's window state after the X server
 * moves, resizes or restacks a window -- the change will be reflected
 * in the drawable position and clip rects.  Since the X server grabs
 * the hardware lock when it changes the window state, this routine will
 * automatically be called after such a change.
 */
void radeonGetLock( radeonContextPtr rmesa, GLuint flags )
{
   __DRIdrawablePrivate *dPriv = rmesa->driDrawable;
   __DRIscreenPrivate *sPriv = rmesa->driScreen;
   RADEONSAREAPrivPtr sarea = rmesa->sarea;
   int i;

// Hang
   drmGetLock( rmesa->driFd, rmesa->hHWContext, flags );

   /* The window might have moved, so we might need to get new clip
    * rects.
    *
    * NOTE: This releases and regrabs the hw lock to allow the X server
    * to respond to the DRI protocol request for new drawable info.
    * Since the hardware state depends on having the latest drawable
    * clip rects, all state checking must be done _after_ this call.
    */
// Only updates clipping which we don't care about.
//   XMESA_VALIDATE_DRAWABLE_INFO( rmesa->display, sPriv, dPriv );

   if ( rmesa->lastStamp != *(dPriv->pStamp) ) \
   {
      rmesa->lastStamp = *(dPriv->pStamp);
      rmesa->new_state |= RADEON_NEW_WINDOW | RADEON_NEW_CLIP;
      rmesa->SetupDone = 0;
   }

   rmesa->dirty |= RADEON_UPLOAD_CONTEXT | RADEON_UPLOAD_CLIPRECTS;

   rmesa->numClipRects = dPriv->numClipRects;
   rmesa->pClipRects = dPriv->pClipRects;

   if ( sarea->ctxOwner != rmesa->hHWContext ) 
   {
      sarea->ctxOwner = rmesa->hHWContext;
      rmesa->dirty = RADEON_UPLOAD_ALL;
   }

	for ( i = 0 ; i < rmesa->lastTexHeap ; i++ ) 
	{
   	if ( sarea->texAge[i] != rmesa->lastTexAge[i] ) 
		{
	 		radeonAgeTextures( rmesa, i );
    	}
	}
}
