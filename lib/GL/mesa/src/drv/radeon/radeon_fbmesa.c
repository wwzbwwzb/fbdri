#include "GL/gl.h"
#include "GL/glfb.h"
#include "context.h"
#include "radeon_context.h"
#include "radeon_lock.h"

static radeonContextPtr radeonCtx = NULL;


/* Copy the back color buffer to the front color buffer.
 */
void FBMesaSwapBuffers( __DRIdrawablePrivate *driDrawPriv )
{
/* FIXME: This assumes buffer is currently bound to a context.  This
 * needs to be able to swap buffers when not currently bound.  Also,
 * this needs to swap according to buffer, and NOT according to
 * context!
 */

//printf("FBMesaSwapBuffers 1\n");

	if ( radeonCtx == NULL ) return;


//printf("FBMesaSwapBuffers 2\n");


/* Only swap buffers when a back buffer exists.
 */
	if ( radeonCtx->glCtx->Visual->DBflag ) 
	{
    	FLUSH_VB( radeonCtx->glCtx, "swap buffers" );

//radeonCtx->doPageFlip = 1;


    	if ( !radeonCtx->doPageFlip ) 
		{
	   		radeonSwapBuffers( radeonCtx );
    	}
		else 
		{
	  		radeonPageFlip( radeonCtx );
    	}
	}
}



/* Create and initialize the Mesa and driver specific visual data.
 */
GLvisual *FBMesaCreateVisual(FBDRI_Main *dpy, 
	__DRIscreenPrivate *driScrnPriv,
	__GLFBvisualConfig *config)
{
   /* Drivers may change the args to _mesa_create_visual() in order to
    * setup special visuals.
     */
// Eventually may want to make dependant on values in *dpy
   return _mesa_create_visual( config->rgba,	// rgbFlag
			    			   config->doubleBuffer,	// dbFlag
			    			   config->stereo,	// stereoFlag
			    			   8,	// redBits
			    			   8,	// greenBits
			    			   8,	// blueBits
			    			   config->alphaSize,	// alphaBits
			    			   0, 	// indexBits
			    			   config->depthSize,	// depthBits
			    			   config->stencilSize,	// stencilBits
			    			   config->accumRedSize,	// accumRedBits
			    			   config->accumGreenSize,	// accumGreenBits
			    			   config->accumBlueSize,	// accumBlueBits
			    			   config->accumAlphaSize,	// accumAlphaBits
			    			   0 ); // numSamples
}



GLboolean FBMesaCreateContext(FBDRI_Main *dpy, 
	GLvisual *mesaVis,
	__DRIcontextPrivate *driContextPriv)
{
//printf("FBMesaCreateContext 1 %p\n", driContextPriv);
   return radeonCreateContext( dpy, mesaVis, driContextPriv );
}




GLframebuffer* FBMesaCreateWindowBuffer(FBDRI_Main *dpy, GLvisual *mesaVis)
{
   return gl_create_framebuffer( mesaVis,		   // GLvisual *visual
				 GL_FALSE,  					   // GLboolean softwareDepth
				 mesaVis->StencilBits > 0,  	   // GLboolean softwareStencil
				 mesaVis->AccumRedBits > 0, 	   // GLboolean softwareAccum
				 GL_FALSE); 					   // GLboolean softwareAlpha
}




GLboolean FBMesaMakeCurrent( __DRIcontextPrivate *driContextPriv,
			    __DRIdrawablePrivate *driDrawPriv,
			    __DRIdrawablePrivate *driReadPriv )
{
//printf("FBMesaMakeCurrent 1\n");
   if ( driContextPriv ) {
//printf("FBMesaMakeCurrent 2\n");
      radeonContextPtr rmesa = (radeonContextPtr)driContextPriv->driverPrivate;

      radeonCtx = radeonMakeCurrent( radeonCtx, rmesa, driDrawPriv );

      gl_make_current2( radeonCtx->glCtx,
			driDrawPriv->mesaBuffer,
			driReadPriv->mesaBuffer );

      if ( radeonCtx->driDrawable != driDrawPriv ) {
	 radeonCtx->driDrawable = driDrawPriv;
	 radeonCtx->dirty = RADEON_UPLOAD_ALL;
      }

      /* GH: We need this to correctly calculate the window offset
       * and aux scissor rects.
       */
      radeonCtx->new_state = RADEON_NEW_WINDOW | RADEON_NEW_CLIP;

      if ( !radeonCtx->glCtx->Viewport.Width ) {
	 gl_Viewport( radeonCtx->glCtx, 0, 0, driDrawPriv->w, driDrawPriv->h );
      }
   } else {
//printf("FBMesaMakeCurrent 3\n");
      gl_make_current( 0, 0 );
      radeonCtx = NULL;
   }

   return GL_TRUE;
}





/* Initialize the driver specific screen private data.
 */
GLboolean FBMesaInitDriver( __DRIscreenPrivate *sPriv )
{
   sPriv->private = (void *) radeonCreateScreen( sPriv );

// Need some version checking in here

   if ( !sPriv->private ) {
      radeonDestroyScreen( sPriv );
      return GL_FALSE;
   }

   return GL_TRUE;
}




/* Initialize the fullscreen mode.
 */
GLboolean
FBMesaOpenFullScreen( __DRIcontextPrivate *driContextPriv )
{
   radeonContextPtr rmesa = (radeonContextPtr)driContextPriv->driverPrivate;
   GLint ret;
//printf("FBMesaOpenFullScreen 1\n");

   /* FIXME: Do we need to check this?
    */
   if ( !radeonCtx->glCtx->Visual->DBflag )
      return GL_TRUE;
//printf("FBMesaOpenFullScreen 2\n");

   LOCK_HARDWARE( rmesa );
   radeonWaitForIdleLocked( rmesa );

   /* Ignore errors.  If this fails, we simply don't do page flipping.
    */
   ret = drmRadeonFullScreen( rmesa->driFd, GL_TRUE );

   UNLOCK_HARDWARE( rmesa );

//printf("FBMesaOpenFullScreen %d\n", ret);
   rmesa->doPageFlip = ( ret == 0 );

   return GL_TRUE;
}





