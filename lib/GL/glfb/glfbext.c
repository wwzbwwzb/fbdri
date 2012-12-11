#include "GL/gl.h"
#include "GL/glfb.h"
#include "drivers/ati/radeon.h"
#include "dri_glfb.h"
#include "fbdrimain.h"
#include "glfbclient.h"


#include <pthread.h>
#include <stdint.h>

void *__driCreateScreen(FBDRI_Main *dpy, 
	int scrn, 
	__DRIscreen *psc,
    int numConfigs, 
	__GLFBvisualConfig *config);


pthread_mutex_t __glFBmutex;

static GLubyte dummyBuffer[__GLFB_BUFFER_LIMIT_SIZE];

/*
** Dummy context used by small commands when there is no current context.
** All the
** gl and glx entry points are designed to operate as nop's when using
** the dummy context structure.
*/
static __GLFBcontext dummyContext = {
    (GLFBContextTag)&dummyBuffer[0],
    (GLenum)&dummyBuffer[0],
    (GLfloat *)&dummyBuffer[0],
    (GLuint *)&dummyBuffer[__GLFB_BUFFER_LIMIT_SIZE],
    sizeof(dummyBuffer),
};

/* not thread safe */
__GLFBcontext *__glFBcurrentContext = &dummyContext;

static GLboolean TSDinitialized = GL_FALSE;
static pthread_key_t ContextTSD;



/* Return the DRI per screen structure */
__DRIscreen *__glFBFindDRIScreen(FBDRI_Main *dpy, int scrn)
{
    __DRIscreen *pDRIScreen = NULL;

	pDRIScreen = &dpy->private_display->screenConfigs[scrn].driScreen;

    return pDRIScreen;
}


/*
** Make a particular context current.
** NOTE: this is in this file so that it can access dummyContext.
*/
Bool glFBMakeCurrent(FBDRI_Main *dpy, GLFBContext gc)
{
    GLFBContext oldGC;
    Bool sentRequestToOldDpy = False;
    Bool bindReturnValue = True;

//printf("glFBMakeCurrent 1\n");

    /*
    ** Make sure that the new context has a nonzero ID.  In the request,
    ** a zero context ID is used only to mean that we bind to no current
    ** context.
    */
    if ((gc == NULL)) 
	{
		return GL_FALSE;
    }

//printf("glFBMakeCurrent 2 %p %p\n", gc, gc->driContext.private);

    /* Bind the direct rendering context to the drawable */
	if(gc->driContext.private) 
	{
	    bindReturnValue = driMesaBindContext(dpy, 0, 0, gc);
	}
//printf("glFBMakeCurrent 3\n");


    /* Update our notion of what is current */
    __glFBLock();
//printf("glFBMakeCurrent 4\n");

	if (gc) 
	{
	    __glFBSetCurrentContext(gc);
	    gc->currentDpy = dpy;
	    gc->currentDrawable = 0;
	} else {
//	    __glFBSetCurrentContext(&dummyContext);
//            _glapi_set_dispatch(NULL);  /* no-op functions */
	}
    __glFBUnlock();
//printf("glFBMakeCurrent 5\n");


    return GL_TRUE;
}





/*
** Free the per screen configs data as well as the array of
** __glXScreenConfigs.
*/
static void FreeScreenConfigs(__GLFBdisplayPrivate *priv)
{
#if 0  // TODO
    __GLXscreenConfigs *psc;
    GLint i, screens;

    /* Free screen configuration information */
    psc = priv->screenConfigs;
    screens = ScreenCount(priv->dpy);
    for (i = 0; i < screens; i++, psc++) {
	if (psc->configs) {
	    Xfree((char*) psc->configs);
	    if(psc->effectiveGLXexts)
		Xfree(psc->effectiveGLXexts);
	    psc->configs = 0;	/* NOTE: just for paranoia */
	}

#ifdef GLX_DIRECT_RENDERING
	/* Free the direct rendering per screen data */
	if (psc->driScreen.private)
	    (*psc->driScreen.destroyScreen)(priv->dpy, i,
					    psc->driScreen.private);
	psc->driScreen.private = NULL;
#endif
    }
    free((char*) priv->screenConfigs);
#endif

}



/*
** Allocate the memory for the per screen configs for each screen.
** If that works then fetch the per screen configs data.
*/
static Bool AllocAndFetchScreenConfigs(FBDRI_Main *dpy, 
	__GLFBdisplayPrivate *priv) 
{
    __GLFBscreenConfigs *psc;
    __GLFBvisualConfig *config;
    GLint i, j, k, nprops, screens;

    /*
    ** First allocate memory for the array of per screen configs.
    */
    screens = 1;
    psc = (__GLFBscreenConfigs*) calloc(1, screens * sizeof(__GLFBscreenConfigs));
    if (!psc) 
	{
		return GL_FALSE;
    }
    priv->screenConfigs = psc;
    
    /*
    ** Now fetch each screens configs structures.  If a screen supports
    ** GL (by returning a numVisuals > 0) then allocate memory for our
    ** config structure and then fill it in.
    */
    for (i = 0; i < screens; i++, psc++) 
	{

		/* Allocate memory for our config structure */
		psc->configs = (__GLFBvisualConfig*)calloc(1, 1 * sizeof(__GLFBvisualConfig));
		psc->numConfigs = 1;

		if (!psc->configs) 
		{
	    	FreeScreenConfigs(priv);
	    	return GL_FALSE;
		}



		/* Read each config structure and convert it into our format */
		config = psc->configs;
		for (j = 0; j < 1; j++, config++) 
		{
			__GLFBvisualConfig *src = &((RADEONInfoPtr)dpy->driverPrivate)->pVisualConfigs[0];




// Taken from xc/programs/Xserver/hw/xfree86/drivers/ati/radeon_dri.c
// and FBDRI_Main
// TODO: This should be defined in a device initialization stage.
	    	/* Copy in the first set of properties */
//	    	config->vid = 							 src->vid;
	    	config->class = 						 src->class;
	    	config->rgba =  						 src->rgba;

	    	config->redSize = 						 src->redSize;
	    	config->greenSize = 					 src->greenSize;
	    	config->blueSize =  					 src->blueSize;
	    	config->alphaSize = 					 src->alphaSize;
	    	config->accumRedSize =  				 src->accumRedSize;
	    	config->accumGreenSize = 				 src->accumGreenSize;
	    	config->accumBlueSize = 				 src->accumBlueSize;
	    	config->accumAlphaSize = 				 src->accumAlphaSize;

	    	config->doubleBuffer =  				 src->doubleBuffer;
	    	config->stereo = 						 src->stereo;

	    	config->bufferSize = 					 src->bufferSize;
	    	config->depthSize = 					 src->depthSize;
	    	config->stencilSize = 					 src->stencilSize;
	    	config->auxBuffers = 					 src->auxBuffers;
	    	config->level = 						 src->level;

/*													 
** Additional properties may be in a list at the end 
** of the reply.  They are in pairs of property type 
** and property value.								 
*/													 
	    	config->visualRating =  				 src->visualRating;
	    	config->transparentPixel =  			 src->transparentPixel;

			config->visualRating =  				 src->visualRating;
			config->transparentPixel =  			 src->transparentPixel;
			config->transparentIndex =   			 src->transparentIndex;
			config->transparentRed =  				 src->transparentRed;
			config->transparentGreen =  			 src->transparentGreen;
			config->transparentBlue = 				 src->transparentBlue;
			config->transparentAlpha =  			 src->transparentAlpha;
		}


//printf("AllocAndFetchScreenConfigs 1 %p %p\n", psc, &psc->driScreen);
	/* Initialize the direct rendering per screen data and functions */
		psc->driScreen.private = __driCreateScreen(dpy, 
			i, 
			&psc->driScreen,
			psc->numConfigs,
			psc->configs);
    }
    return GL_TRUE;
}


/*
** Initialize the client side extension code.
*/
__GLFBdisplayPrivate *__glFBInitialize(FBDRI_Main *dpy)
{
    __GLFBdisplayPrivate *dpyPriv;
    int major, minor;

    /* The one and only long long lock */
    __glFBLock();

    dpyPriv = (__GLFBdisplayPrivate *) calloc(1, sizeof(__GLFBdisplayPrivate));
    if (!dpyPriv) 
	{
		__glFBUnlock();
		return 0;
    }

    /*
    ** Init the display private and then read in the screen config
    ** structures from the server.
    */
    dpyPriv->majorOpcode = 0;
    dpyPriv->majorVersion = 0;
    dpyPriv->minorVersion = 0;
    dpyPriv->dpy = dpy;

    dpyPriv->serverGLFBvendor = 0x0; 
    dpyPriv->serverGLFBversion = 0x0;

    /*
    ** Initialize the direct rendering per display data and functions.
    ** Note: This _must_ be done before calling any other DRI routines
    ** (e.g., those called in AllocAndFetchScreenConfigs).
    */
    dpyPriv->driDisplay.private = driCreateDisplay(dpy, &dpyPriv->driDisplay);

    if (!AllocAndFetchScreenConfigs(dpy, dpyPriv)) 
	{
		__glFBUnlock();
		free((char*) dpyPriv);
		return 0;
    }

    __glFBUnlock();

    return dpyPriv;
}
