#include "GL/gl.h"
#include "GL/glfb.h"





__DRIdrawable *driMesaGetDrawable(FBDRI_Main *dpy, 
	GLFBDrawable draw,
	void *screenPrivate);




void glFBSwapBuffers(FBDRI_Main *dpy)
{
    GLFBContext gc = __glFBGetCurrentContext();
    GLFBContextTag tag;
    unsigned char opcode;
    __GLFBdisplayPrivate *priv;
    __DRIdrawable *pdraw;

//printf("glFBSwapBuffers 1\n");

    priv = dpy->private_display;
    if (priv->driDisplay.private) 
	{
		__GLFBscreenConfigs *psc = &priv->screenConfigs[0];

//printf("glFBSwapBuffers 2\n");

		if (psc && psc->driScreen.private) 
		{
/*
** getDrawable returning NULL implies that the drawable is
** not bound to a direct rendering context.
*/

// (*psc->driScreen.getDrawable)
			pdraw = driMesaGetDrawable(dpy, 0, psc->driScreen.private);
		
//printf("glFBSwapBuffers 3\n");



	    	if (pdraw) 
			{
// (*pdraw->swapBuffers)


				driMesaSwapBuffers(dpy, pdraw->private);
//printf("glFBSwapBuffers 4\n");
			}
		}
	}
}



/*
** Create a new context.
*/
GLFBContext glFBCreateContext(FBDRI_Main *dpy)
{
    GLFBContext gc;
    __GLFBdisplayPrivate *priv;

    /* Allocate our context record */
    gc = (GLFBContext)calloc(1, sizeof(struct __GLFBcontextRec));

    if (!gc) 
	{
		return NULL;
    }

    /* Fill in the new context */
    gc->renderMode = GL_RENDER;

    gc->state.storePack.alignment = 4;
    gc->state.storeUnpack.alignment = 4;

    __glFBInitVertexArrayState(gc);

    gc->attributes.stackPointer = &gc->attributes.stack[0];

    /*
    ** PERFORMANCE NOTE: A mode dependent fill image can speed things up.
    ** Other code uses the fastImageUnpack bit, but it is never set
    ** to GL_TRUE.
    */
    gc->fastImageUnpack = GL_FALSE;
    gc->fillImage = __glFillImage;
    gc->createDpy = dpy;

	/*
	** Create the direct rendering context, if requested and
	** available.
	*/
	dpy->private_display = __glFBInitialize(dpy);

//printf("glFBCreateContext 1 %p\n", gc);
	gc->driContext.private = driMesaCreateContext(dpy, &gc->driContext);
//printf("glFBCreateContext 2 %p\n", gc->driContext.private);

    return gc;
}
