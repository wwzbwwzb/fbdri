#ifndef FBMESA_H
#define FBMESA_H


#ifdef __cplusplus
extern "C" {
#endif

#include "dri_mesaint.h"
#include "dri_mesa.h"
#include "types.h"


// Defined in lib/GL/mesa/src/drv/brand_name.
// These 4 functions must be called at startup.

extern GLvisual* FBMesaCreateVisual(FBDRI_Main *dpy__,
	__DRIscreenPrivate *driScrnPriv,
	__GLFBvisualConfig *config);

extern GLboolean FBMesaCreateContext(FBDRI_Main *dpy, 
	GLvisual *mesaVis,
	__DRIcontextPrivate *driContextPriv);

extern GLframebuffer* FBMesaCreateWindowBuffer(FBDRI_Main *dpy, 
	GLvisual *mesaVis);

extern GLboolean FBMesaMakeCurrent(__DRIcontextPrivate *driContextPriv,
			    __DRIdrawablePrivate *driDrawPriv,
			    __DRIdrawablePrivate *driReadPriv);





#ifdef __cplusplus
}
#endif


#endif
