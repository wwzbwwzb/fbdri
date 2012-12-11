#include "GL/gl.h"
#include "GL/glfb.h"
#include "dri_glfb.h"

static void driDestroyDisplay(FBDRI_Main *dpy, void *private)
{
    __DRIdisplayPrivate *pdpyp = (__DRIdisplayPrivate *)private;

    if (pdpyp) 
	{
        const int numScreens = 1;
        int i;
        for (i = 0; i < numScreens; i++) 
		{
            if (pdpyp->libraryHandles[i])
                dlclose(pdpyp->libraryHandles[i]);
        }
        free(pdpyp->libraryHandles);
		free(pdpyp);
    }
}


void *driCreateDisplay(FBDRI_Main *dpy, __DRIdisplay *pdisp)
{
    const int numScreens = 0;
    __DRIdisplayPrivate *pdpyp;
    int eventBase, errorBase;
    int major, minor, patch;

    /* Initialize these fields to NULL in case we fail.
     * If we don't do this we may later get segfaults trying to free random
     * addresses when the display is closed.
     */
    pdisp->private = NULL;

    pdpyp = (__DRIdisplayPrivate *)calloc(1, sizeof(__DRIdisplayPrivate));
    if (!pdpyp) 
	{
		return NULL;
    }

    pdpyp->driMajor = 0;
    pdpyp->driMinor = 0;
    pdpyp->driPatch = 0;




    return (void *)pdpyp;
}
