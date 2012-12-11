#ifndef GLFBCLIENT_H
#define GLFBCLIENT_H


// Kludges from glxclient to get the dummy context to work

#define __GLFB_MAX_SMALL_RENDER_CMD_SIZE	156

#define __GLFB_BUFFER_LIMIT_SIZE	(__GLFB_MAX_SMALL_RENDER_CMD_SIZE + 32)


typedef struct __GLFBcontextRec __GLFBcontext;
typedef struct __GLFBdisplayPrivateRec __GLFBdisplayPrivate;



/*
** The following structures define the interface between the GLFB client
** side library and the DRI (direct rendering infrastructure).
*/

typedef struct __DRIdisplayRec  __DRIdisplay;
typedef struct __DRIscreenRec   __DRIscreen;
typedef struct __DRIcontextRec  __DRIcontext;
typedef struct __DRIdrawableRec __DRIdrawable;




#include "fbdrimain.h"
#include "GL/gl.h"
#include "GL/glfb.h"
#include "GL/glfbint.h"
#include "GL/glfbproto.h"
#include "GL/xreplacements.h"

#include <pthread.h>

#define __GLFB_MAX_TEXTURE_UNITS 32
#define __GL_BOOLEAN_ARRAY     (GL_BYTE - 1)

extern __GLFBcontext *__glFBcurrentContext;
#define __glFBGetCurrentContext()	__glFBcurrentContext
#define __glFBSetCurrentContext(gc)	__glFBcurrentContext = gc




extern __DRIscreen *__glFBFindDRIScreen(FBDRI_Main *dpy, int scrn);


/*
** Display dependent methods.  This structure is initialized during the
** driCreateDisplay() call.
*/
struct __DRIdisplayRec 
{
// Function pointers removed
    /*
    ** Opaque pointer to private per display direct rendering data.
    ** NULL if direct rendering is not supported on this display.  Never
    ** dereference by this code.
    */
    void *private;
};


extern pthread_mutex_t __glFBmutex;

#define fbmutex_init(x) \
{ \
	pthread_mutexattr_t attr; \
	pthread_mutexattr_init(&attr); \
	pthread_mutex_init((pthread_mutex_t*)x, &attr); \
}

#define fbmutex_lock(x) \
	pthread_mutex_lock((pthread_mutex_t*)x);


#define fbmutex_unlock(x); \
	pthread_mutex_unlock((pthread_mutex_t*)x);


#define __glFBLock()    fbmutex_lock(&__glFBmutex)
#define __glFBUnlock()  fbmutex_unlock(&__glFBmutex)





#define __GL_CLIENT_ATTRIB_STACK_DEPTH 16

typedef struct __GLFBpixelStoreModeRec {
    GLboolean swapEndian;
    GLboolean lsbFirst;
    GLuint rowLength;
    GLuint imageHeight;
    GLuint imageDepth;
    GLuint skipRows;
    GLuint skipPixels;
    GLuint skipImages;
    GLuint alignment;
} __GLFBpixelStoreMode;

typedef struct __GLFBvertexArrayPointerStateRec {
    GLboolean enable;
    void (*proc)(const void *);
    const GLubyte *ptr;
    GLsizei skip;
    GLint size;
    GLenum type;
    GLsizei stride;
} __GLFBvertexArrayPointerState;

typedef struct __GLFBvertArrayStateRec {
    __GLFBvertexArrayPointerState vertex;
    __GLFBvertexArrayPointerState normal;
    __GLFBvertexArrayPointerState color;
    __GLFBvertexArrayPointerState index;
    __GLFBvertexArrayPointerState texCoord[__GLFB_MAX_TEXTURE_UNITS];
    __GLFBvertexArrayPointerState edgeFlag;
    GLint maxElementsVertices;
    GLint maxElementsIndices;
    GLint activeTexture;
} __GLFBvertArrayState;

typedef struct __GLFBattributeRec {
	GLuint mask;

	/*
	** Pixel storage state.  Most of the pixel store mode state is kept
	** here and used by the client code to manage the packing and
	** unpacking of data sent to/received from the server.
	*/
	__GLFBpixelStoreMode storePack, storeUnpack;

	/*
	** Vertex Array storage state.  The vertex array component
	** state is stored here and is used to manage the packing of
	** DrawArrays data sent to the server.
	*/
	__GLFBvertArrayState vertArray;
} __GLFBattribute;

typedef struct __GLFBattributeMachineRec {
	__GLFBattribute *stack[__GL_CLIENT_ATTRIB_STACK_DEPTH];
	__GLFBattribute **stackPointer;
} __GLFBattributeMachine;



/*
** Screen dependent methods.  This structure is initialized during the
** (*createScreen)() call.
*/
struct __DRIscreenRec {
    /*
    ** Method to destroy the private DRI screen data.
    */
    void (*destroyScreen)(FBDRI_Main *dpy, int scrn, void *private);

    /*
    ** Method to create the private DRI context data and initialize the
    ** context dependent methods.
    */
    void *(*createContext)(FBDRI_Main *dpy, void *shared,
			   __DRIcontext *pctx);

    /*
    ** Method to create the private DRI drawable data and initialize the
    ** drawable dependent methods.
    */
    void *(*createDrawable)(FBDRI_Main *dpy, int scrn, GLFBDrawable draw,
			    __DRIdrawable *pdraw);

    /*
    ** Method to return a pointer to the DRI drawable data.
    */
    __DRIdrawable *(*getDrawable)(FBDRI_Main *dpy, GLFBDrawable draw,
				  void *private);

    /*
    ** Opaque pointer to private per screen direct rendering data.  NULL
    ** if direct rendering is not supported on dpy screen.  Never
    ** dereference by this code.
    */
    void *private;
};

/*
** Context dependent methods.  This structure is initialized during the
** (*createContext)() call.
*/
struct __DRIcontextRec {
    /*
    ** Method to destroy the private DRI context data.
    */
    void (*destroyContext)(FBDRI_Main *dpy, int scrn, void *private);









    /*
    ** Method to bind a DRI drawable to a DRI graphics context.
    */
    Bool (*bindContext)(FBDRI_Main *dpy, 
		int scrn, 
		GLFBDrawable draw,
		GLFBContext gc);

    /*
    ** Method to unbind a DRI drawable to a DRI graphics context.
    */
    Bool (*unbindContext)(FBDRI_Main *dpy, 
		int scrn, 
		GLFBDrawable draw,
		GLFBContext gc, int will_rebind);









    /*
    ** Opaque pointer to private per context direct rendering data.
    ** NULL if direct rendering is not supported on the display or
    ** screen used to create this context.  Never dereference by this
    ** code.
    */
    void *private;
};

/*
** GLFB state that needs to be kept on the client.  One of these records
** exist for each context that has been made current by this client.
*/
struct __GLFBcontextRec {
   /*
    ** The context tag returned by MakeCurrent when this context is made
    ** current. This tag is used to identify the context that a thread has
    ** current so that proper server context management can be done.  It is
    ** used for all context specific commands (i.e., Render, RenderLarge,
    ** WaitX, WaitGL, UseXFont, and MakeCurrent (for the old context)).
    */
    GLFBContextTag currentContextTag;

    /*
    ** The rendering mode is kept on the client as well as the server.
    ** When glRenderMode() is called, the buffer associated with the
    ** previous rendering mode (feedback or select) is filled.
    */
    GLenum renderMode;
    GLfloat *feedbackBuf;
    GLuint *selectBuf;

    /*
    ** This is GL_TRUE if the pixel unpack modes are such that an image
    ** can be unpacked from the clients memory by just copying.  It may
    ** still be true that the server will have to do some work.  This
    ** just promises that a straight copy will fetch the correct bytes.
    */
    GLboolean fastImageUnpack;

    /*
    ** Fill newImage with the unpacked form of oldImage getting it
    ** ready for transport to the server.
    */
    void (*fillImage)(__GLFBcontext*, GLint, GLint, GLint, GLint, GLenum,
		      GLenum, const GLvoid*, GLubyte*, GLubyte*);

    /*
    ** Client side attribs.
    */
    __GLFBattribute state;
    __GLFBattributeMachine attributes;

    /*
    ** Client side error code.  This is set when client side gl API
    ** routines need to set an error because of a bad enumerant or
    ** running out of memory, etc.
    */
    GLenum error;








    /*
    ** Whether this context does direct rendering.
    */
    Bool isDirect;

    /* Record the dpy this context was created on for later freeing */
    FBDRI_Main *createDpy;     // createDpy

    /*
    ** dpy of current display for this context. Will be NULL if not
    ** current to any display, or if this is the "dummy context".
    */
    FBDRI_Main *currentDpy;


    /*
    ** The current drawable for this context.  Will be None if this
    ** context is not current to any drawable.
    */
    FBDRI_Main *currentDrawable;     // createDpy

#if 0       // TODO

    /*
    ** Constant strings that describe the server implementation
    ** These pertain to GL attributes, not to be confused with
    ** GLFB versioning attributes.
    */
    GLubyte *vendor;
    GLubyte *renderer;
    GLubyte *version;
    GLubyte *extensions;


    /*
    ** Maximum small render command size.  This is the smaller of 64k and
    ** the size of the above buffer.
    */
    GLint maxSmallRenderCommandSize;

    /*
    ** Major opcode for the extension.  Copied here so a lookup isn't
    ** needed.
    */
    GLint majorOpcode;

#endif

    /*
    ** Per context direct rendering interface functions and data.
    */
    __DRIcontext driContext;
};


#define __glFBSetError(gc,code) \
    if (!(gc)->error) {	       \
	(gc)->error = code;    \
    }

/*
** Drawable dependent methods.  This structure is initialized during the
** (*createDrawable)() call.  These methods are not currently called
** from GLFB 1.2, but could be used in GLFB 1.3.
*/
struct __DRIdrawableRec {
    /*
    ** Method to destroy the private DRI drawable data.
    */
    void (*destroyDrawable)(FBDRI_Main *dpy, void *private);

    /*
    ** Method to swap the front and back buffers.
    */
    void (*swapBuffers)(FBDRI_Main *dpy, void *private);

    /*
    ** Opaque pointer to private per drawable direct rendering data.
    ** NULL if direct rendering is not supported on the display or
    ** screen used to create this drawable.  Never dereference by this
    ** code.
    */
    void *private;
};

/*
** One of these records exists per screen of the display.  It contains
** a pointer to the config data for that screen (if the screen supports GL).
*/
typedef struct __GLFBscreenConfigsRec {
    __GLFBvisualConfig *configs;
    int numConfigs;
    const char *serverGLFBexts;
    char *effectiveGLFBexts;

    /*
    ** Per screen direct rendering interface functions and data.
    */
    __DRIscreen driScreen;
} __GLFBscreenConfigs;


/*
** Per display private data.  One of these records exists for each display
** that is using the OpenGL (GLFB) extension.
*/
struct __GLFBdisplayPrivateRec {
    /*
    ** Back pointer to the display
    */
    FBDRI_Main *dpy;      // Display *dpy

    /*
    ** The majorOpcode is common to all connections to the same server.
    ** It is also copied into the context structure.
    */
    int majorOpcode;

    /*
    ** Major and minor version returned by the server during initialization.
    */
    int majorVersion, minorVersion;

    /* Storage for the servers GLFB vendor and versions strings.  These
    ** are the same for all screens on this display. These fields will
    ** be filled in on demand.
    */
    char *serverGLFBvendor;
    char *serverGLFBversion;

    /*
    ** Configurations of visuals for all screens on this display.
    ** Also, per screen data which now includes the server GLFB_EXTENSION
    ** string.
    */
    __GLFBscreenConfigs *screenConfigs;

    /*
    ** Per display direct rendering interface functions and data.
    */
    __DRIdisplay driDisplay;
};


/*
** Fill the transport buffer with the data from the users buffer,
** applying some of the pixel store modes (unpack modes) to the data
** first.  As a side effect of this call, the "modes" field is
** updated to contain the modes needed by the server to decode the
** sent data.
*/
extern void __glFillImage(__GLFBcontext*, GLint, GLint, GLint, GLint, GLenum,
			  GLenum, const GLvoid*, GLubyte*, GLubyte*);



extern __GLFBdisplayPrivate *__glFBInitialize(FBDRI_Main *this);



#endif
