#ifndef FBDRIMAIN_H
#define FBDRIMAIN_H




/*
 * Authors:
 * Adam Williams <broadcast@earthling.net>
 */

#include <stdint.h>


// From xc/programs/Xserver/render/picturestr.h
typedef union _DevUnion {
    void*		ptr;
    long		val;
    unsigned long	uval;
    void*		(*fptr)(
#if NeedFunctionPrototypes
                        void
#endif
                        );
} DevUnion;



typedef struct _FBDRI_Main FBDRI_Main;


#define MMIO_IN8(base, offset) *(uint8_t*)(base + offset)
#define MMIO_IN16(base, offset) *(uint16_t*)(base + offset)
#define MMIO_IN32(base, offset) *(uint32_t*)(base + offset)

#define MMIO_OUT8(base, offset, val) *(uint8_t*)(base + offset) = val;
#define MMIO_OUT16(base, offset, val) *(uint16_t*)(base + offset) = val;
#define MMIO_OUT32(base, offset, val) *(uint32_t*)(base + offset) = val;



#include "fbdri.h"
#include "glfbclient.h"
#include "GL/glfb.h"
#include "GL/xreplacements.h"

// The following structure should replace Display, Drawables, Screens with
// a single surface and container for all the structures.

// Also the 2D driver needs to copy to certain FBDRI centric structures the
// information that the 2D driver already has.  This alleviates the pain of
// working around SDL's #define work arounds and overall rely on SDL.

struct _FBDRI_Main
{
	void *driverPrivate;
    GLFBContext glfb_context;	/* Current GL context */

// Initialized in programs/Xserver/dix/main.c.
// Now initialized in fbdrimain.c followed by DRIScreenInit
	DevUnion *devPrivates;

	__GLFBdisplayPrivate *private_display;

// One clipping rectangle for the full screen
	FBDRIClipRectRec clipList;

// Base addresses
// Need to prefix stuff to work around the SDL workarounds
	uint32_t dri_physical_mem;
	char *dri_mapped_mem;
	int dri_mapped_memlen;
	uint32_t dri_physical_io;
	char *dri_mapped_io;
	long dri_mapped_iolen;
// Where textures and pixmaps are stored
	char *pixmap_mem;
	long pixmap_memtotal;
	long pixmap_memleft;
	int bus;
	int device;
	int function;
	int pitch;
	int w;
	int h;
	int bpp;    // Bits per pixel
};

FBDRI_Main* FBDRIScreenInit(uint32_t dri_physical_mem, 
	char *dri_mapped_mem,
	int dri_mapped_memlen,
	uint32_t dri_physical_io, 
	char *dri_mapped_io,
	long dri_mapped_iolen,
	char *pixmap_mem,
	long pixmap_memtotal,
	int bus,
	int device,
	int function,
	int pitch,
	int w,
	int h,
	int bpp);


void *driMesaCreateContext(FBDRI_Main *dpy,
	__DRIcontext *pctx);

Bool glFBMakeCurrent(FBDRI_Main *dpy, GLFBContext gc);
void driMesaSwapBuffers(FBDRI_Main *dpy, void *drawPrivate);


#endif
