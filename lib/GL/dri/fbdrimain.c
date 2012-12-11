#include "drivers/ati/radeon.h"
#include "fbdrimain.h"
#include <glapitable.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>





#if 1



/* This is used when thread safety is disabled */
struct _glapi_table *_glapi_Dispatch = (struct _glapi_table *) NULL;

void *_glapi_Context = NULL;



static GLboolean WarnFlag = GL_FALSE;


void
_glapi_noop_enable_warnings(GLboolean enable)
{
   WarnFlag = enable;
}

/*
 * Set the current context pointer for this thread.
 * The context pointer is an opaque type which should be cast to
 * void from the real context pointer type.
 */
void
_glapi_set_context(void *context)
{
   _glapi_Context = context;
}

void
_glapi_check_multithread()
{
}

// Stubs 
void _glapi_add_entrypoint(char *text, int opcode)
{
}


/*
 * Set the global or per-thread dispatch table pointer.
 */
void
_glapi_set_dispatch(struct _glapi_table *dispatch)
{
}


/*
 * Get the current context pointer for this thread.
 * The context pointer is an opaque type which should be cast from
 * void to the real context pointer type.
 */
void *
_glapi_get_context(void)
{
   return _glapi_Context;
}


/*
 * Return size of dispatch table struct as number of functions (or
 * slots).
 */
GLuint
_glapi_get_dispatch_table_size(void)
{
   return 1;
}

#endif




















// Variables normally provided by the X Server and not replacable by
// pure FB variables.

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
	int bpp)
{
	FBDRI_Main *result = calloc(1, sizeof(FBDRI_Main));

/*
 * fprintf(stderr, "FBDRIScreenInit 1\n"
 * 	"dri_physical_mem %p\n"
 * 	"dri_mapped_mem %p\n"
 * 	"dri_mapped_memlen %p\n"
 * 	"dri_physical_io, %p\n"
 * 	"dri_mapped_io, %p\n"
 * 	"dri_mapped_iolen, %p\n"
 * 	"pixmap_mem, %p\n"
 * 	"pixmap_memtotal %p\n"
 * 	"bus %p\n"
 * 	"device %p\n"
 * 	"function, %p\n"
 * 	"pitch %p\n"
 * 	"w %p\n"
 * 	"h %p\n"
 * 	"bpp %p\n",
 * 	
 * 	dri_physical_mem,
 * 	dri_mapped_mem,
 * 	dri_mapped_memlen,
 * 	dri_physical_io,
 * 	dri_mapped_io,
 * 	dri_mapped_iolen,
 * 	pixmap_mem,
 * 	pixmap_memtotal,
 * 	bus,
 * 	device,
 * 	function,
 * 	pitch,
 * 	w,
 * 	h,
 * 	bpp);fflush(stderr);
 * 
 */
	result->dri_physical_mem = dri_physical_mem;
	result->dri_mapped_mem = dri_mapped_mem;
	result->dri_mapped_memlen = dri_mapped_memlen;
	result->pixmap_mem = pixmap_mem;
	result->pixmap_memtotal = pixmap_memtotal;
	result->pixmap_memleft = pixmap_memtotal;
	result->pitch = pitch;
	result->bus = bus;
	result->device = device;
	result->function = function;
	result->dri_physical_io = dri_physical_io;
	result->dri_mapped_io = dri_mapped_io;
	result->dri_mapped_iolen = dri_mapped_iolen;
	result->w = w;
	result->h = h;
	result->bpp = bpp;

	result->clipList.x1 = 0;
	result->clipList.y1 = 0;
	result->clipList.x2 = w;
	result->clipList.y2 = h;


	result->driverPrivate = calloc(sizeof(RADEONInfoRec), 1);

// For the DRIScreenPrivIndex and DRIWindowPrivIndex
// Previously done in programs/Xserver/dix/privates.c
	result->devPrivates = calloc(sizeof(DevUnion), 2);

//fprintf(stderr, "FBDRIScreenInit 1\n");fflush(stderr);

	RADEONPreInitDRI(result);
//fprintf(stderr, "FBDRIScreenInit 2\n");fflush(stderr);


// Kernel crash 1
	RADEONDRIScreenInit(result);
//fprintf(stderr, "FBDRIScreenInit 3\n");fflush(stderr);


	RADEONDRITexturesInit(result);
//fprintf(stderr, "FBDRIScreenInit 4\n");fflush(stderr);

	RADEONDRIFinishScreenInit(result);
//fprintf(stderr, "FBDRIScreenInit 5\n");fflush(stderr);

	return result;
}

void FBDRICloseScreen(FBDRI_Main *fbdri)
{
//printf("FBDRICloseScreen 1\n");
	RADEONCloseScreen(fbdri, 0);
}


void ErrorF(char *f, ...)
{
}

