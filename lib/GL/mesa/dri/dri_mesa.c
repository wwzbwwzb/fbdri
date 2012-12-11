/* $XFree86: xc/lib/GL/mesa/dri/dri_mesa.c,v 1.16 2001/04/10 16:07:49 dawes Exp $ */
/**************************************************************************

Copyright 1998-1999 Precision Insight, Inc., Cedar Park, Texas.
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
 *   Kevin E. Martin <kevin@precisioninsight.com>
 *   Brian E. Paul <brian@precisioninsight.com>
 */

/*
 * This file gets compiled into each of the DRI 3D drivers.  The
 * functions defined here are called from the GL library via
 * function pointers in the __DRIdisplayRec, __DRIscreenRec,
 * __DRIcontextRec, __DRIdrawableRec structures defined in glxclient.h
 *
 * Those function pointers are initialized by code in this file.
 * The process starts when libGL calls the __driCreateScreen() function
 * at the end of this file.
 *
 * The above-mentioned DRI structures have no dependencies on Mesa.
 * Each structure instead has a generic (void *) private pointer that
 * points to a private structure.  For Mesa drivers, these private
 * structures are the __DRIdrawablePrivateRec, __DRIcontextPrivateRec,
 * __DRIscreenPrivateRec, and __DRIvisualPrivateRec structures defined
 * in dri_mesaint.h.  We allocate and attach those structs here in
 * this file.
 */


/* VisualID and XVisualInfo removed */
/* Replaced all "screen" with 0 */

//#ifdef GLFB_DIRECT_RENDERING

#include <unistd.h>
#include "glfbclient.h"
//#include "fbdri.h"
#include "GL/fbmesa.h"
#include "sarea.h"
#include "dri_mesaint.h"
//#include "dri_fbmesaapi.h"
#include "../src/context.h"
//#include "../src/mmath.h"


/* Context binding */
Bool driMesaBindContext(FBDRI_Main *dpy, int scrn,
 			GLFBDrawable draw, GLFBContext gc);
Bool driMesaUnbindContext(FBDRI_Main *dpy, int scrn,
 		  GLFBDrawable draw, GLFBContext gc,
 		  int will_rebind);

/* Drawable methods */
static void *driMesaCreateDrawable(FBDRI_Main *dpy, 
	int scrn, 
	GLFBDrawable draw,
	__DRIdrawable *pdraw);
static void driMesaDestroyDrawable(FBDRI_Main *dpy, void *drawPrivate);

/* Context methods */
static void driMesaDestroyContext(FBDRI_Main *dpy, int scrn, void *screenPrivate);

/* Screen methods */
static void driMesaDestroyScreen(FBDRI_Main *dpy, int scrn, void *screenPrivate);

static Bool driFeatureOn(const char *name)
{
    char *env = getenv(name);

    if (!env) return GL_FALSE;
    if (!strcasecmp(env, "enable")) return GL_TRUE;
    if (!strcasecmp(env, "1"))      return GL_TRUE;
    if (!strcasecmp(env, "on"))     return GL_TRUE;
    if (!strcasecmp(env, "true"))   return GL_TRUE;
    if (!strcasecmp(env, "t"))      return GL_TRUE;
    if (!strcasecmp(env, "yes"))    return GL_TRUE;
    if (!strcasecmp(env, "y"))      return GL_TRUE;

    return GL_FALSE;
}


/*
** Print message to stderr if LIBGL_DEBUG env var is set.
*/
void
__driMesaMessage(const char *msg)
{
    if (getenv("LIBGL_DEBUG")) {
        fprintf(stderr, "libGL error: %s\n", msg);
    }
}


/*****************************************************************/

/* Maintain a list of drawables */

static Bool __driMesaAddDrawable(void *drawHash, __DRIdrawable *pdraw)
{
    __DRIdrawablePrivate *pdp = (__DRIdrawablePrivate *)pdraw->private;

    if (drmHashInsert(drawHash, pdp->draw, pdraw))
	return GL_FALSE;

    return GL_TRUE;
}

static __DRIdrawable *__driMesaFindDrawable(void *drawHash, GLFBDrawable draw)
{
    int retcode;
    __DRIdrawable *pdraw;

    retcode = drmHashLookup(drawHash, draw, (void **)&pdraw);
    if (retcode)
		return NULL;

    return pdraw;
}

static void __driMesaRemoveDrawable(void *drawHash, __DRIdrawable *pdraw)
{
    int retcode;
    __DRIdrawablePrivate *pdp = (__DRIdrawablePrivate *)pdraw->private;

    retcode = drmHashLookup(drawHash, pdp->draw, (void **)&pdraw);
    if (!retcode) { /* Found */
	drmHashDelete(drawHash, pdp->draw);
    }
}

static Bool __driMesaWindowExistsFlag;

static int __driMesaWindowExistsErrorHandler(FBDRI_Main *dpy)
{
    return 0;
}

static Bool __driMesaWindowExists(FBDRI_Main *dpy, GLFBDrawable draw)
{
    __driMesaWindowExistsFlag = GL_TRUE;
    return __driMesaWindowExistsFlag;
}

static void __driMesaGarbageCollectDrawables(void *drawHash)
{
    GLFBDrawable draw;
    __DRIdrawable *pdraw;
    FBDRI_Main *dpy;

    if (drmHashFirst(drawHash, (unsigned long*)&draw, (void **)&pdraw)) {
	do {
	    __DRIdrawablePrivate *pdp = (__DRIdrawablePrivate *)pdraw->private;
	    dpy = pdp->driScreenPriv->display;
	    if (!__driMesaWindowExists(dpy, draw)) {
		/* Destroy the local drawable data in the hash table, if the
		   drawable no longer exists in the Xserver */
		__driMesaRemoveDrawable(drawHash, pdraw);
		(*pdraw->destroyDrawable)(dpy, pdraw->private);
		free(pdraw);
	    }
	} while (drmHashNext(drawHash, (unsigned long*)&draw, (void **)&pdraw));
    }
}


/*****************************************************************/

Bool driMesaUnbindContext(FBDRI_Main *dpy, int scrn,
				 GLFBDrawable draw, GLFBContext gc,
				 int will_rebind)
{
    __DRIscreen *pDRIScreen;
    __DRIdrawable *pdraw;
    __DRIcontextPrivate *pcp;
    __DRIscreenPrivate *psp;
    __DRIdrawablePrivate *pdp;

    /*
    ** Assume error checking is done properly in glFBMakeCurrent before
    ** calling driMesaUnbindContext.
    */

    if (gc == NULL || draw == None) {
	/* ERROR!!! */
	return GL_FALSE;
    }

    if (!(pDRIScreen = __glFBFindDRIScreen(dpy, scrn))) {
	/* ERROR!!! */
	return GL_FALSE;
    } else if (!(psp = (__DRIscreenPrivate *)pDRIScreen->private)) {
	/* ERROR!!! */
	return GL_FALSE;
    }

    pcp = (__DRIcontextPrivate *)gc->driContext.private;

    pdraw = __driMesaFindDrawable(psp->drawHash, draw);
    if (!pdraw) {
	/* ERROR!!! */
	return GL_FALSE;
    }
    pdp = (__DRIdrawablePrivate *)pdraw->private;

				/* Don't leave fullscreen mode if the
                                   drawable will be rebound in the next
                                   step -- this avoids a protocol
                                   request. */
    if (!will_rebind && psp->fullscreen) {
//	psp->MesaAPI.CloseFullScreen(pcp);
	DRICloseFullScreen(dpy, scrn, draw);
	psp->fullscreen = NULL;
    }

    /* Unbind Mesa's drawable from Mesa's context */
//    (*psp->MesaAPI.UnbindContext)(pcp);

    if (pdp->refcount == 0) {
	/* ERROR!!! */
	return GL_FALSE;
    } else if (--pdp->refcount == 0) {
#if 0
	/*
	** NOT_DONE: When a drawable is unbound from one direct
	** rendering context and then bound to another, we do not want
	** to destroy the drawable data structure each time only to
	** recreate it immediatly afterwards when binding to the next
	** context.  This also causes conflicts with caching of the
	** drawable stamp.
	**
	** In addition, we don't destroy the drawable here since Mesa
	** keeps private data internally (e.g., software accumulation
	** buffers) that should not be destroyed unless the client
	** explicitly requests that the window be destroyed.
	**
	** When GLFB 1.3 is integrated, the create and destroy drawable
	** functions will have user level counterparts and the memory
	** will be able to be recovered.
	** 
	** Below is an example of what needs to go into the destroy
	** drawable routine to support GLFB 1.3.
	*/
	__driMesaRemoveDrawable(psp->drawHash, pdraw);
	(*pdraw->destroyDrawable)(dpy, pdraw->private);
	free(pdraw);
#endif
    }

    /* XXX this is disabled so that if we call SwapBuffers on an unbound
     * window we can determine the last context bound to the window and
     * use that context's lock. (BrianP, 2-Dec-2000)
     */
#if 0
    /* Unbind the drawable */
    pcp->driDrawablePriv = NULL;
    pdp->driContextPriv = &psp->dummyContextPriv;
#endif

    return GL_TRUE;
}

Bool driMesaBindContext(FBDRI_Main *dpy, int scrn,
			       GLFBDrawable draw, GLFBContext gc)
{
    __DRIscreen *pDRIScreen;
    __DRIdrawable *pdraw;
    __DRIdrawablePrivate *pdp;
    __DRIscreenPrivate *psp;
    __DRIcontextPrivate *pcp;
    static Bool envchecked      = False;
    static Bool checkfullscreen = False;

//printf("driMesaBindContext 1 %p %p\n", gc, draw);
    /*
    ** Assume error checking is done properly in glFBMakeCurrent before
    ** calling driMesaBindContext.
    */

    if (gc == NULL /* || draw == None */) 
	{
		/* ERROR!!! */
		return GL_FALSE;
    }

//printf("driMesaBindContext 2\n");
    if (!(pDRIScreen = __glFBFindDRIScreen(dpy, scrn))) 
	{
		/* ERROR!!! */
		return GL_FALSE;
    }
	
	
	
	if(!(psp = (__DRIscreenPrivate *)pDRIScreen->private)) 
	{
		/* ERROR!!! */
		return GL_FALSE;
    }
//printf("driMesaBindContext 3\n");

    pdraw = __driMesaFindDrawable(psp->drawHash, draw);
    if (!pdraw) 
	{
/* Allocate a new drawable */
		pdraw = (__DRIdrawable *)calloc(1, sizeof(__DRIdrawable));
		if (!pdraw) {
	    	/* ERROR!!! */
	    	return GL_FALSE;
		}
//printf("driMesaBindContext 4\n");

/* Create a new drawable */
		pdraw->private = driMesaCreateDrawable(dpy, 
			scrn, 
			draw, 
			pdraw);




		if (!pdraw->private) 
		{
	    	/* ERROR!!! */
	    	free(pdraw);
	    	return GL_FALSE;
		}
//printf("driMesaBindContext 5\n");

/* Add pdraw to drawable list */
		if (!__driMesaAddDrawable(psp->drawHash, pdraw)) 
		{
	    	/* ERROR!!! */
	    	(*pdraw->destroyDrawable)(dpy, pdraw->private);
	    	free(pdraw);
	    	return GL_FALSE;
		}
    }
//printf("driMesaBindContext 6\n");








    pdp = (__DRIdrawablePrivate *)pdraw->private;

    /* Bind the drawable to the context */
    pcp = (__DRIcontextPrivate *)gc->driContext.private;
    pcp->driDrawablePriv = pdp;
    pdp->driContextPriv = pcp;
    pdp->refcount++;
//printf("driMesaBindContext 7\n");

    /*
    ** Now that we have a context associated with this drawable, we can
    ** initialize the drawable information if has not been done before.
    ** Also, since we need it when LIBGL_DRI_FULLSCREEN, pick up any changes
    ** that are outstanding.
    */
    if (!pdp->pStamp || *pdp->pStamp != pdp->lastStamp) 
	{
//printf("driMesaBindContext 7.1\n");
		DRM_SPINLOCK(&psp->pSAREA->drawable_lock, psp->drawLockID);
//printf("driMesaBindContext 7.2\n");
		driMesaUpdateDrawableInfo(dpy, scrn, pdp);
//printf("driMesaBindContext 7.3\n");
		DRM_SPINUNLOCK(&psp->pSAREA->drawable_lock, psp->drawLockID);
//printf("driMesaBindContext 7.4\n");
    }




//printf("driMesaBindContext 8\n");






    /* Call device-specific MakeCurrent */
	FBMesaMakeCurrent(pcp, pdp, pdp);



//printf("driMesaBindContext 9\n");




    /* Check for the potential to enter an automatic full-screen mode.
       This may need to be moved up. */
    if (!envchecked) {
		checkfullscreen = driFeatureOn("LIBGL_DRI_AUTOFULLSCREEN");
		envchecked = GL_TRUE;
    }
	
	checkfullscreen = 1;
	
	
    if (checkfullscreen && pdp->numClipRects == 1) 
	{
		/* If there is valid information in the SAREA, we can use it to
		avoid a protocol request.  The only time when the SAREA
		information won't be valid will be initially, so in the worst
		case, we'll make one protocol request that we could have
		avoided. */
	
		int try = 1;

		int clw = pdp->pClipRects[0].x2 - pdp->pClipRects[0].x1;
		int clh = pdp->pClipRects[0].y2 - pdp->pClipRects[0].y1;



#if 0
				/* Useful client-side debugging message */
	fprintf(stderr,
		"********************************************\n"
		"********************************************\n"
		"********************************************\n"
		"%d @ %d,%d,%d,%d\n"
		"frame %d,%d,%d,%d\n"
		"win   %d,%d,%d,%d\n"
		"fs = %p pdp = %p sarea = %d\n"
		"********************************************\n"
		"********************************************\n"
		"********************************************\n",
		pdp->numClipRects,
		pdp->pClipRects[0].x1,
		pdp->pClipRects[0].y1,
		pdp->pClipRects[0].x2,
		pdp->pClipRects[0].y2,
		psp->pSAREA->frame.x,
		psp->pSAREA->frame.y,
		psp->pSAREA->frame.width,
		psp->pSAREA->frame.height,
		pdp->x, pdp->y, pdp->w, pdp->h,
		psp->fullscreen, pdp, psp->pSAREA->frame.fullscreen);
#endif

//printf("driMesaBindContext 10 %d\n", try);

		if (pdp->x != pdp->pClipRects[0].x1
	    	|| pdp->y != pdp->pClipRects[0].y1
	    	|| pdp->w != clw
	    	|| pdp->h != clh) try = 0;
//printf("driMesaBindContext 11 %d\n", try);

		if (try && psp->pSAREA->frame.width && psp->pSAREA->frame.height) {
	    	if (pdp->x != psp->pSAREA->frame.x
			|| pdp->y != psp->pSAREA->frame.y
			|| pdp->w != psp->pSAREA->frame.width
			|| pdp->h != psp->pSAREA->frame.height) try = 0;
		}



//printf("driMesaBindContext 1 %d\n", try);
		if (try) 
		{
	    	if (psp->fullscreen && !psp->pSAREA->frame.fullscreen) 
			{
/* Server has closed fullscreen mode */
				__driMesaMessage("server closed fullscreen mode");
				psp->fullscreen = NULL;
	    	}

//printf("driMesaBindContext 12\n", try);
	    	if (DRIOpenFullScreen(dpy)) 
			{
				psp->fullscreen = pdp;
//printf("driMesaBindContext 13\n", try);
				FBMesaOpenFullScreen(pcp);
	    	}
		}
    }

    return GL_TRUE;
}

/*****************************************************************/

/*
 * This function basically updates the __DRIdrawablePrivate struct's
 * cliprect information by calling FBDRIGetDrawableInfo().  This is
 * usually called by the DRI_MESA_VALIDATE_DRAWABLE_INFO macro which
 * compares the __DRIdrwablePrivate pStamp and lastStamp values.  If
 * the values are different that means we have to update the clipping
 * info.
 */
void driMesaUpdateDrawableInfo(FBDRI_Main *dpy, int scrn,
			       __DRIdrawablePrivate *pdp)
{
    __DRIscreenPrivate *psp;
    __DRIcontextPrivate *pcp = pdp->driContextPriv;

//printf("driMesaUpdateDrawableInfo 1\n");
    if (!pcp || (pdp != pcp->driDrawablePriv)) {
	/* ERROR!!! */
	return;
    }

//printf("driMesaUpdateDrawableInfo 2\n");
    psp = pdp->driScreenPriv;
    if (!psp) {
	/* ERROR!!! */
	return;
    }

//printf("driMesaUpdateDrawableInfo 3\n");


    if (pdp->pClipRects) 
	{
		free(pdp->pClipRects); 
    }

//printf("driMesaUpdateDrawableInfo 4\n");
    if (pdp->pBackClipRects) 
	{
		free(pdp->pBackClipRects); 
    }

//printf("driMesaUpdateDrawableInfo 5\n");

    DRM_SPINUNLOCK(&psp->pSAREA->drawable_lock, psp->drawLockID);

//printf("driMesaUpdateDrawableInfo 6\n");
    if (!DRIGetDrawableInfo(dpy, 
		&pdp->index, 
		&pdp->lastStamp,
		&pdp->x, 
		&pdp->y, 
		&pdp->w, 
		&pdp->h,
		&pdp->numClipRects, 
		&pdp->pClipRects, 
		&pdp->backX,
		&pdp->backY,
		&pdp->numBackClipRects,
		&pdp->pBackClipRects)) 
	{

//printf("driMesaUpdateDrawableInfo 7\n");
		pdp->numClipRects = 0;
		pdp->pClipRects = NULL;
		pdp->numBackClipRects = 0;
		pdp->pBackClipRects = 0;


	/* ERROR!!! */
    }

//printf("driMesaUpdateDrawableInfo 8\n");
    DRM_SPINLOCK(&psp->pSAREA->drawable_lock, psp->drawLockID);

//printf("driMesaUpdateDrawableInfo 9\n");
    pdp->pStamp = &(psp->pSAREA->drawableTable[pdp->index].stamp);
//printf("driMesaUpdateDrawableInfo 10\n");
}

/*****************************************************************/

static void *driMesaCreateDrawable(FBDRI_Main *dpy, 
	int scrn, 
	GLFBDrawable draw,
	__DRIdrawable *pdraw)
{
    __DRIscreen *pDRIScreen;
    __DRIscreenPrivate *psp;
    __DRIdrawablePrivate *pdp;
    int i;
    GLvisual *mesaVis = NULL;


//printf("driMesaCreateDrawable 1\n");
    pdp = (__DRIdrawablePrivate *)calloc(1, sizeof(__DRIdrawablePrivate));

    if (!pdp) 
	{
		return NULL;
    }

//printf("driMesaCreateDrawable 2\n");
    if (!DRICreateDrawable(dpy, &pdp->hHWDrawable)) 
	{
		free(pdp);
		return NULL;
    }

//printf("driMesaCreateDrawable 3\n");
    pdp->draw = draw;
    pdp->refcount = 0;
    pdp->pStamp = NULL;
    pdp->lastStamp = 0;
    pdp->index = 0;
    pdp->x = 0;
    pdp->y = 0;
    pdp->w = 0;
    pdp->h = 0;
    pdp->numClipRects = 0;
    pdp->numBackClipRects = 0;
//    pdp->pClipRects = NULL;
//    pdp->pBackClipRects = NULL;

    if (!(pDRIScreen = __glFBFindDRIScreen(dpy, scrn))) 
	{
		(void)DRIDestroyDrawable(dpy, scrn, pdp->draw);
		free(pdp);
		return NULL;
    } 
	else 
	if (!(psp = (__DRIscreenPrivate *)pDRIScreen->private)) 
	{
		(void)DRIDestroyDrawable(dpy, scrn, pdp->draw);
		free(pdp);
		return NULL;
    }
//printf("driMesaCreateDrawable 4 %p\n", psp->visuals);

    pdp->driScreenPriv = psp;
    pdp->driContextPriv = &psp->dummyContextPriv;
	mesaVis = psp->visuals[0].mesaVisual;


/* XXX pixmap rendering not implemented yet */
    if (1) 
	{
		pdp->mesaBuffer = FBMesaCreateWindowBuffer(dpy, mesaVis);
//       pdp->mesaBuffer = (*psp->MesaAPI.CreateWindowBuffer)(dpy, psp, pdp, mesaVis);
    }
    else {
//       pdp->mesaBuffer = (*psp->MesaAPI.CreatePixmapBuffer)(dpy, psp, pdp);
    }

//printf("driMesaCreateDrawable 5\n");
    if (!pdp->mesaBuffer) 
	{
		(void)DRIDestroyDrawable(dpy, scrn, pdp->draw);
		free(pdp);
		return NULL;
    }

//printf("driMesaCreateDrawable 6\n");
    pdraw->destroyDrawable = driMesaDestroyDrawable;
    pdraw->swapBuffers = driMesaSwapBuffers;

//printf("driMesaCreateDrawable 7\n");
    return (void *)pdp;
}











__DRIdrawable *driMesaGetDrawable(FBDRI_Main *dpy, 
	GLFBDrawable draw,
	void *screenPrivate)
{
    __DRIscreenPrivate *psp = (__DRIscreenPrivate *) screenPrivate;

    /*
    ** Make sure this routine returns NULL if the drawable is not bound
    ** to a direct rendering context!
    */
    return __driMesaFindDrawable(psp->drawHash, draw);
}









/*
 * XXX if we get rid of the FBMesa function table then we should probably
 * get rid of this function and require each driver to implement a
 * driMesaSwapBuffers function.
 */
void driMesaSwapBuffers(FBDRI_Main *dpy, void *drawPrivate)
{
    __DRIdrawablePrivate *pdp = (__DRIdrawablePrivate *) drawPrivate;
    __DRIscreenPrivate *psp = pdp->driScreenPriv;




	FBMesaSwapBuffers( pdp );


//    (*psp->MesaAPI.SwapBuffers)(pdp);
}

static void driMesaDestroyDrawable(FBDRI_Main *dpy, void *drawPrivate)
{
    __DRIdrawablePrivate *pdp = (__DRIdrawablePrivate *)drawPrivate;
    __DRIscreenPrivate *psp = pdp->driScreenPriv;
    int scrn = psp->myNum;

    if (pdp) {
        gl_destroy_framebuffer(pdp->mesaBuffer);
	if (__driMesaWindowExists(dpy, pdp->draw))
	    (void)DRIDestroyDrawable(dpy, scrn, pdp->draw);
	free(pdp);
    }
}

/*****************************************************************/


void *driMesaCreateContext(FBDRI_Main *dpy,
	__DRIcontext *pctx)
{
    __DRIscreen *pDRIScreen;
    __DRIcontextPrivate *pcp;
//    __DRIcontextPrivate *pshare = (__DRIcontextPrivate *)shared;
    __DRIscreenPrivate *psp;
    int i;



    if (!(pDRIScreen = __glFBFindDRIScreen(dpy, /* vis->screen */ 0))) 
	{
		/* ERROR!!! */
		fprintf(stderr, "driMesaCreateContext: __glFBFindDRIScreen == NULL\n");
		return NULL;
    } 


//printf("driMesaCreateContext 1 %p\n", pDRIScreen);

	if (!(psp = (__DRIscreenPrivate *)pDRIScreen->private)) 
	{
		/* ERROR!!! */
		fprintf(stderr, "driMesaCreateContext: pDRIScreen->private == NULL\n");
		return NULL;
    }

//printf("driMesaCreateContext 1\n");
    /* Create the hash table */
    if (!psp->drawHash) psp->drawHash = drmHashCreate();










    pcp = (__DRIcontextPrivate *)calloc(1, sizeof(__DRIcontextPrivate));
    if (!pcp) 
	{
		return NULL;
    }




    pcp->display = dpy;
    pcp->driScreenPriv = psp;
    pcp->mesaContext = NULL;
    pcp->driDrawablePriv = NULL;
//printf("driMesaCreateContext 1 %p %p\n", pcp, pcp->driScreenPriv);



// Was XF86DRICreateContext

    if (!DRICreateContext(dpy, 
		0, 
		&pcp->contextID, 
		&pcp->hHWContext)) 
	{
		free(pcp);
		return NULL;
    }










    /* This is moved because the Xserver creates a global dummy context
     * the first time FBDRICreateContext is called.
     */

    if (!psp->dummyContextPriv.driScreenPriv) 
	{
        psp->dummyContextPriv.hHWContext = psp->pSAREA->dummy_context;
		psp->dummyContextPriv.driScreenPriv = psp;
		psp->dummyContextPriv.mesaContext = NULL;
		psp->dummyContextPriv.driDrawablePriv = NULL;
        	psp->dummyContextPriv.driverPrivate = NULL;
		/* No other fields should be used! */
    }

//    for (i = 0; i < psp->numVisuals; i++) {
//        if (psp->visuals[i].vid == vis->visualid) {

{
        	GLvisual *mesaVis = psp->visuals[0].mesaVisual;
        	GLcontext *sharedMesaCtx = NULL;


            pcp->mesaContext = gl_create_context(mesaVis,
												sharedMesaCtx,
                                                 (void*)NULL, /* set below */
                                                 GL_TRUE);
            if (pcp->mesaContext) 
			{




//printf("driMesaCreateContext 2 %p\n", pcp);
/* Driver now creates its private context data */
// Was psp->MesaAPI.CreateContext
				if(FBMesaCreateContext(dpy, mesaVis, pcp))
				{
					pcp->mesaContext->DriverCtx = pcp->driverPrivate;
				}



				pcp->mesaContext->DriverCtx = pcp->driverPrivate;
            }
}


//        }
//    }

//printf("driMesaCreateContext 1\n");
    if (!pcp->mesaContext) {
//	(void)DRIDestroyContext(dpy, /* vis->screen */ 0, /* pcp->contextID */ 0);
	free(pcp);
	return NULL;
    }

//printf("driMesaCreateContext 1\n");


/*
 *     pctx->destroyContext = driMesaDestroyContext;
 *     pctx->bindContext    = driMesaBindContext;
 *     pctx->unbindContext  = driMesaUnbindContext;
 */





    __driMesaGarbageCollectDrawables(pcp->driScreenPriv->drawHash);

//printf("driMesaCreateContext 2 %p\n", pcp);
    return pcp;
}

static void driMesaDestroyContext(FBDRI_Main *dpy, 
	int scrn, 
	void *contextPrivate)
{
    __DRIcontextPrivate  *pcp   = (__DRIcontextPrivate *) contextPrivate;
    __DRIscreenPrivate   *psp;
    __DRIdrawablePrivate *pdp;

    if (pcp) {
  	if ((pdp = pcp->driDrawablePriv)) {
 	    /* Shut down fullscreen mode */
 	    if ((psp = pdp->driScreenPriv) && psp->fullscreen) {
// 		psp->MesaAPI.CloseFullScreen(pcp);
 		DRICloseFullScreen(dpy, scrn, pdp->draw);
 		psp->fullscreen = NULL;
 	    }
	}
	__driMesaGarbageCollectDrawables(pcp->driScreenPriv->drawHash);
//	(*pcp->driScreenPriv->MesaAPI.DestroyContext)(pcp);
        gl_destroy_context(pcp->mesaContext);
//	(void)DRIDestroyContext(dpy, scrn, /* pcp->contextID */ 0);
	free(pcp);
    }
}

/*****************************************************************/

static void *driMesaCreateScreen(FBDRI_Main *dpy, 
	int scrn, 
	__DRIscreen *psc,
	int numConfigs, 
	__GLFBvisualConfig *config)
{
    int directCapable = 1, i, n;
    __DRIscreenPrivate *psp;
    drmHandle hFB, hSAREA;
	char *BusID;

    if(!(psp = (__DRIscreenPrivate *)calloc(1, sizeof(__DRIscreenPrivate))))
	{
		return NULL;
    }
//printf("driMesaCreateScreen 1\n");

    psp->display = dpy;
    psp->myNum = scrn;

// Version number
    psp->drmMajor = 0;
    psp->drmMinor = 0;
    psp->drmPatch = 0;



//printf("driMesaCreateScreen 1\n");


// Get hSAREA and BusID from something in here
	if(!DRIOpenConnection(dpy, &hSAREA, &BusID))
	{
		free(psp);
		return NULL;
    }


//printf("driMesaCreateScreen 1\n");



// Open the device handle
    psp->fd = drmOpen(NULL, BusID);


    if(psp->fd < 0) 
	{
        fprintf(stderr, "driMesaCreateScreen: failed to open DRM: %s\n", strerror(-psp->fd));
		free(BusID);
		free(psp);		
		return NULL;
	}
	free(BusID); /* No longer needed */

//printf("driMesaCreateScreen 1\n");



    /*
     * Get device-specific info.  pDevPriv will point to a struct
     * (such as DRIRADEONRec in xfree86/driver/ati/radeon_dri.h)
     * that has information about the screen size, depth, pitch,
     * ancilliary buffers, DRM mmap handles, etc.
     */
    if (!DRIGetDeviceInfo(dpy,
			      &hFB,
			      &psp->fbOrigin,
			      &psp->fbSize,
			      &psp->fbStride,
			      &psp->devPrivSize,
			      &psp->pDevPriv)) 
	{
		(void)drmClose(psp->fd);
		free(psp);
//		(void)FBDRICloseConnection(dpy, scrn);
		return NULL;
    }



    psp->fbWidth = dpy->w;
    psp->fbHeight = dpy->h;
    psp->fbBPP = dpy->bpp;

    /*
     * Map the framebuffer region.
     */
    if(drmMap(psp->fd, hFB, psp->fbSize, (drmAddressPtr)&psp->pFB)) 
	{
		perror("driMesaCreateScreen: drmMap framebuffer handle");
		free(psp->pDevPriv);
		(void)drmClose(psp->fd);
		free(psp);
		return NULL;
    }
//printf("driMesaCreateScreen 1\n");


    /*
     * Map the SAREA region.  Further mmap regions may be setup in
     * each DRI driver's "createScreen" function.
     */
    if(drmMap(psp->fd, hSAREA, SAREA_MAX, (drmAddressPtr)&psp->pSAREA)) 
	{
		perror("driMesaCreateScreen: drmMap SAREA handle");
		(void)drmUnmap((drmAddress)psp->pFB, psp->fbSize);
		free(psp->pDevPriv);
		(void)drmClose(psp->fd);
		free(psp);
		return NULL;
    }



   /*
     * Allocate space for an array of visual records and initialize them.
     */
    psp->numVisuals = numConfigs;
    psp->visuals = (__DRIvisualPrivate *)calloc(numConfigs, sizeof(__DRIvisualPrivate));
 
 
    for (i = 0; i < numConfigs; i++, config++) 
	{
//		psp->visuals[i].vid = scrn;
    	psp->visuals[i].mesaVisual = FBMesaCreateVisual(dpy, psp, config);
	}




    /* Initialize the screen specific GLFB driver */
    if (!FBMesaInitDriver(psp)) {
	    free(psp->pDevPriv);
	    free(psp);
	    return NULL;
    }

    /*
    ** Do not init dummy context here; actual initialization will be
    ** done when the first DRI context is created.  Init screen priv ptr
    ** to NULL to let CreateContext routine that it needs to be inited.
    */
    psp->dummyContextPriv.driScreenPriv = NULL;

    /* Initialize the drawHash when the first context is created */
    psp->drawHash = NULL;
//printf("driMesaCreateScreen 2\n");

    return (void *)psp;
}

static void driMesaDestroyScreen(FBDRI_Main *dpy, int scrn, void *screenPrivate)
{
    __DRIscreenPrivate *psp = (__DRIscreenPrivate *) screenPrivate;

    if (psp) {
#if 0
	/*
	** NOT_DONE: For the same reason as that listed below, we cannot
	** call the X server here to destroy the dummy context.
	*/
	if (psp->dummyContextPriv.driScreenPriv) {
	    (void)DRIDestroyContext(dpy, scrn,
					psp->dummyContextPriv.contextID);
	}
#endif







//	if (psp->MesaAPI.ResetDriver)
//	    (*psp->MesaAPI.ResetDriver)(psp);
	free(psp->visuals);
	(void)drmUnmap((drmAddress)psp->pSAREA, SAREA_MAX);
	(void)drmUnmap((drmAddress)psp->pFB, psp->fbSize);
	free(psp->pDevPriv);
	(void)drmClose(psp->fd);
	free(psp);





#if 0
	/*
	** NOT_DONE: Normally, we would call FBDRICloseConnection()
	** here, but since this routine is called after the
	** XCloseDisplay() function has already shut down the connection
	** to the Display, there is no protocol stream open to the X
	** server anymore.  Luckily, FBDRICloseConnection() does not
	** really do anything (for now).
	*/
	(void)FBDRICloseConnection(dpy, scrn);
#endif
    }
}


/*
 * This is the entrypoint into the DRI 3D driver.
 * The driCreateScreen name is the symbol that libGL.so fetches via
 * dlsym() in order to bootstrap the driver.
 */
void *__driCreateScreen(FBDRI_Main *dpy, 
	int scrn, 
	__DRIscreen *psc,
    int numConfigs, 
	__GLFBvisualConfig *config)
{
    return driMesaCreateScreen(dpy, scrn, psc, numConfigs, config);
}



//#endif
