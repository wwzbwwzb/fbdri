/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997, 1998, 1999, 2000, 2001  Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Sam Lantinga
    slouken@devolution.com
*/

#ifdef SAVE_RCSID
static char rcsid =
 "@(#) $Id: SDL_x11modes.c,v 1.1 2001/08/01 23:52:47 awilliam Exp $";
#endif

/* Utilities for getting and setting the X display mode */

#include <stdlib.h>
#include <string.h>

#include "SDL_timer.h"
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_events_c.h"
#include "SDL_x11video.h"
#include "SDL_x11wm_c.h"
#include "SDL_x11modes_c.h"


#ifdef XFREE86_VM
Bool XVidMode(GetModeInfo, (Display *dpy, int scr, XF86VidModeModeInfo *info))
{
    XF86VidModeModeLine *l = (XF86VidModeModeLine*)((char*)info + sizeof info->dotclock);
    return XVidMode(GetModeLine, (dpy, scr, &info->dotclock, l));
}
#endif /* XFREE86_VM */

#ifdef XFREE86_VM
static void save_mode(_THIS)
{
    memset(&saved_mode, 0, sizeof(saved_mode));
    XVidMode(GetModeInfo, (SDL_Display,SDL_Screen,&saved_mode));
    XVidMode(GetViewPort, (SDL_Display,SDL_Screen,&saved_view.x,&saved_view.y));
}
#endif

#ifdef XFREE86_VM
static void restore_mode(_THIS)
{
    XF86VidModeModeLine mode;
    int unused;

    if ( XVidMode(GetModeLine, (SDL_Display, SDL_Screen, &unused, &mode)) ) {
        if ( (saved_mode.hdisplay != mode.hdisplay) ||
             (saved_mode.vdisplay != mode.vdisplay) ) {
            XVidMode(SwitchToMode, (SDL_Display, SDL_Screen, &saved_mode));
        }
    }
    if ( (saved_view.x != 0) || (saved_view.y != 0) ) {
        XVidMode(SetViewPort, (SDL_Display, SDL_Screen, saved_view.x, saved_view.y));
    }
}
#endif

#ifdef XFREE86_VM
static int cmpmodes(const void *va, const void *vb)
{
    XF86VidModeModeInfo *a = *(XF86VidModeModeInfo**)va;
    XF86VidModeModeInfo *b = *(XF86VidModeModeInfo**)vb;
    if(a->hdisplay > b->hdisplay)
        return -1;
    return b->vdisplay - a->vdisplay;
}
#endif

static void set_best_resolution(_THIS, int width, int height)
{
#ifdef XFREE86_VM
    if ( use_vidmode ) {
        XF86VidModeModeLine mode;
        XF86VidModeModeInfo **modes;
        int i;
        int nmodes;

        if ( XVidMode(GetModeLine, (SDL_Display, SDL_Screen, &i, &mode)) &&
             XVidMode(GetAllModeLines, (SDL_Display,SDL_Screen,&nmodes,&modes))){
            qsort(modes, nmodes, sizeof *modes, cmpmodes);
#ifdef XFREE86_DEBUG
  printf("Available modes:\n");
  for ( i = 0; i < nmodes; ++i ) {
    printf("Mode %d: %dx%d\n", i, modes[i]->hdisplay, modes[i]->vdisplay);
  }
#endif
            for ( i = nmodes-1; i > 0 ; --i ) {
                if ( (modes[i]->hdisplay >= width) &&
                     (modes[i]->vdisplay >= height) )
                    break;
            }
            if ( (modes[i]->hdisplay != mode.hdisplay) ||
                 (modes[i]->vdisplay != mode.vdisplay) ) {
                XVidMode(SwitchToMode, (SDL_Display, SDL_Screen, modes[i]));
            }
            XFree(modes);
        }
    }
#endif /* XFREE86_VM */
}

static void get_real_resolution(_THIS, int* w, int* h)
{
#ifdef XFREE86_VM
    if ( use_vidmode ) {
        XF86VidModeModeLine mode;
        int unused;

        if ( XVidMode(GetModeLine, (SDL_Display, SDL_Screen, &unused, &mode)) ) {
            *w = mode.hdisplay;
            *h = mode.vdisplay;
            return;
        }
    }
#endif
    *w = DisplayWidth(SDL_Display, SDL_Screen);
    *h = DisplayHeight(SDL_Display, SDL_Screen);
}

/* Called after mapping a window - waits until the window is mapped */
void X11_WaitMapped(_THIS, Window win)
{
    XEvent event;
    do {
        XMaskEvent(SDL_Display, StructureNotifyMask, &event);
    } while ( (event.type != MapNotify) || (event.xmap.event != win) );
}

/* Called after unmapping a window - waits until the window is unmapped */
void X11_WaitUnmapped(_THIS, Window win)
{
    XEvent event;
    do {
        XMaskEvent(SDL_Display, StructureNotifyMask, &event);
    } while ( (event.type != UnmapNotify) || (event.xunmap.event != win) );
}

static void move_cursor_to(_THIS, int x, int y)
{
    XWarpPointer(SDL_Display, None, SDL_Root, 0, 0, 0, 0, x, y);
}

static int add_visual(_THIS, int depth, int class)
{
    XVisualInfo vi;
    if(XMatchVisualInfo(SDL_Display, SDL_Screen, depth, class, &vi)) {
	int n = this->hidden->nvisuals;
	this->hidden->visuals[n].depth = vi.depth;
	this->hidden->visuals[n].visual = vi.visual;
	this->hidden->nvisuals++;
    }
    return(this->hidden->nvisuals);
}
static int add_visual_byid(_THIS, const char *visual_id)
{
    XVisualInfo *vi, template;
    int nvis;

    if ( visual_id ) {
        memset(&template, 0, (sizeof template));
        template.visualid = strtol(visual_id, NULL, 0);
        vi = XGetVisualInfo(SDL_Display, VisualIDMask, &template, &nvis);
        if ( vi ) {
	    int n = this->hidden->nvisuals;
	    this->hidden->visuals[n].depth = vi->depth;
	    this->hidden->visuals[n].visual = vi->visual;
	    this->hidden->nvisuals++;
            XFree(vi);
        }
    }
    return(this->hidden->nvisuals);
}

/* Global for the error handler */
int vm_event, vm_error = -1;

int X11_GetVideoModes(_THIS)
{
#ifdef XFREE86_VM
    int buggy_X11;
    int vm_major, vm_minor;
    int nmodes;
    XF86VidModeModeInfo **modes;
#endif
    int i;

    vm_error = -1;
    use_vidmode = 0;
#ifdef XFREE86_VM
    /* Metro-X 4.3.0 and earlier has a broken implementation of
       XF86VidModeGetAllModeLines() - it hangs the client.
     */
    buggy_X11 = 0;
    if ( strcmp(ServerVendor(SDL_Display), "Metro Link Incorporated") == 0 ) {
        FILE *metro_fp;

        metro_fp = fopen("/usr/X11R6/lib/X11/Metro/.version", "r");
        if ( metro_fp != NULL ) {
            int major, minor, patch, version;
            major = 0; minor = 0; patch = 0;
            fscanf(metro_fp, "%d.%d.%d", &major, &minor, &patch);
            version = major*100+minor*10+patch;
            if ( version < 431 ) {
                buggy_X11 = 1;
            }
            fclose(metro_fp);
        }
    }
#if defined(__alpha__) || defined(__powerpc__)
    /* The alpha and PPC XFree86 servers are also buggy */
    buggy_X11 = 1;
#endif
    /* Enumerate the available fullscreen modes */
    if ( ! buggy_X11 ) {
        if ( XVidMode(QueryExtension, (SDL_Display, &vm_event, &vm_error)) &&
              XVidMode(QueryVersion, (SDL_Display, &vm_major, &vm_minor)) ) {
#ifdef BROKEN_XFREE86_4001
#ifdef X_XF86VidModeGetDotClocks  /* Compiled under XFree86 4.0 */
                /* Earlier X servers hang when doing vidmode */
		if ( vm_major < 2 ) {
#ifdef DEBUG_XF86
  printf("Compiled under XFree86 4.0, server is XFree86 3.X\n");
#endif
                    buggy_X11 = 1;
                }
#else
		/* XFree86 3.X code works with XFree86 4.0 servers */;
#endif /* XFree86 4.0 */
#endif /* XFree86 4.02 and newer are fixed wrt backwards compatibility */
        } else {
            buggy_X11 = 1;
        }
    }
    if ( ! buggy_X11 &&
         XVidMode(GetAllModeLines, (SDL_Display, SDL_Screen,&nmodes,&modes)) ) {

        qsort(modes, nmodes, sizeof *modes, cmpmodes);
        SDL_modelist = (SDL_Rect **)malloc((nmodes+1)*sizeof(SDL_Rect *));
        if ( SDL_modelist ) {
            for ( i=0; i<nmodes; ++i ) {
                SDL_modelist[i] = (SDL_Rect *)malloc(sizeof(SDL_Rect));
                if ( SDL_modelist[i] == NULL ) {
                    break;
                }
                SDL_modelist[i]->x = 0;
                SDL_modelist[i]->y = 0;
                SDL_modelist[i]->w = modes[i]->hdisplay;
                SDL_modelist[i]->h = modes[i]->vdisplay;
            }
            SDL_modelist[i] = NULL;
        }
        XFree(modes);

        use_vidmode = 1;
        save_mode(this);
    }
#endif /* XFREE86_VM */

    {
	static int depth_list[] = { 32, 24, 16, 15, 8 };
	int j, np;
	int use_directcolor = 1;
	XPixmapFormatValues *pf;

	/* Search for the visuals in deepest-first order, so that the first
	   will be the richest one */
	if ( getenv("SDL_VIDEO_X11_NODIRECTCOLOR") ) {
		use_directcolor = 0;
	}
	this->hidden->nvisuals = 0;
	if ( ! add_visual_byid(this, getenv("SDL_VIDEO_X11_VISUALID")) ) {
		for ( i=0; i<SDL_TABLESIZE(depth_list); ++i ) {
			if ( depth_list[i] > 8 ) {
				if ( use_directcolor ) {
					add_visual(this, depth_list[i], DirectColor);
				}
				add_visual(this, depth_list[i], TrueColor);
			} else {
				add_visual(this, depth_list[i], PseudoColor);
				add_visual(this, depth_list[i], StaticColor);
			}
		}
	}
	if ( this->hidden->nvisuals == 0 ) {
	    SDL_SetError("Found no sufficiently capable X11 visuals");
	    return -1;
	}
	    
	/* look up the pixel quantum for each depth */
	pf = XListPixmapFormats(SDL_Display, &np);
	for(i = 0; i < this->hidden->nvisuals; i++) {
	    int d = this->hidden->visuals[i].depth;
	    for(j = 0; j < np; j++)
		if(pf[j].depth == d)
		    break;
	    this->hidden->visuals[i].bpp = j < np ? pf[j].bits_per_pixel : d;
	}

	XFree(pf);
    }

    if ( SDL_modelist == NULL ) {
        SDL_modelist = (SDL_Rect **)malloc((1+1)*sizeof(SDL_Rect *));
        i = 0;
        if ( SDL_modelist ) {
            SDL_modelist[i] = (SDL_Rect *)malloc(sizeof(SDL_Rect));
            if ( SDL_modelist[i] ) {
                SDL_modelist[i]->x = 0;
                SDL_modelist[i]->y = 0;
                SDL_modelist[i]->w = DisplayWidth(SDL_Display, SDL_Screen);
                SDL_modelist[i]->h = DisplayHeight(SDL_Display, SDL_Screen);
                ++i;
            }
            SDL_modelist[i] = NULL;
        }
    }

#ifdef DEBUG_XF86
    if ( use_vidmode ) {
        fprintf(stderr, "XFree86 VidMode is enabled\n");
    }
    if ( SDL_modelist ) {
        fprintf(stderr, "X11 video mode list:\n");
        for ( i=0; SDL_modelist[i]; ++i ) {
            fprintf(stderr, "\t%dx%d\n",
                SDL_modelist[i]->w, SDL_modelist[i]->h);
        }
    }
#endif /* DEBUG_XF86 */
    return 0;
}

int X11_SupportedVisual(_THIS, SDL_PixelFormat *format)
{
    int i;
    for(i = 0; i < this->hidden->nvisuals; i++)
	if(this->hidden->visuals[i].bpp == format->BitsPerPixel)
	    return 1;
    return 0;
}

SDL_Rect **X11_ListModes(_THIS, SDL_PixelFormat *format, Uint32 flags)
{
    if ( X11_SupportedVisual(this, format) ) {
        if ( flags & SDL_FULLSCREEN ) {
            return(SDL_modelist);
        } else {
            return((SDL_Rect **)-1);
        }
    } else {
        return((SDL_Rect **)0);
    }
}

void X11_FreeVideoModes(_THIS)
{
    int i;

    if ( SDL_modelist ) {
        for ( i=0; SDL_modelist[i]; ++i ) {
            free(SDL_modelist[i]);
        }
        free(SDL_modelist);
        SDL_modelist = NULL;
    }
}

int X11_ResizeFullScreen(_THIS)
{
    int x, y;
    int real_w, real_h;

    if ( currently_fullscreen ) {
        /* Switch resolution and cover it with the FSwindow */
        move_cursor_to(this, 0, 0);
        set_best_resolution(this, current_w, current_h);
        move_cursor_to(this, 0, 0);
        get_real_resolution(this, &real_w, &real_h);
        XResizeWindow(SDL_Display, FSwindow, real_w, real_h);
        move_cursor_to(this, real_w/2, real_h/2);

        /* Center and reparent the drawing window */
        x = (real_w - current_w)/2;
        y = (real_h - current_h)/2;
        XReparentWindow(SDL_Display, SDL_Window, FSwindow, x, y);
        /* FIXME: move the mouse to the old relative location */
        XSync(SDL_Display, True);   /* Flush spurious mode change events */
    }
    return(1);
}

void X11_QueueEnterFullScreen(_THIS)
{
    switch_waiting = 0x01 | SDL_FULLSCREEN;
    switch_time = SDL_GetTicks() + 1500;
#if 0 /* This causes a BadMatch error if the window is iconified (not needed) */
    XSetInputFocus(SDL_Display, WMwindow, RevertToNone, CurrentTime);
#endif
}

int X11_EnterFullScreen(_THIS)
{
    int okay;
#if 0
    Window tmpwin, *windows;
    int i, nwindows;
#endif

    okay = 1;
    if ( ! currently_fullscreen ) {
        int real_w, real_h;

        /* Map the fullscreen window to blank the screen */
        get_real_resolution(this, &real_w, &real_h);
        XResizeWindow(SDL_Display, FSwindow, real_w, real_h);
        XMapRaised(SDL_Display, FSwindow);
        X11_WaitMapped(this, FSwindow);

#if 0 /* This seems to break WindowMaker in focus-follows-mouse mode */
        /* Make sure we got to the top of the window stack */
        if ( XQueryTree(SDL_Display, SDL_Root, &tmpwin, &tmpwin,
                                &windows, &nwindows) && windows ) {
            /* If not, try to put us there - if fail... oh well */
            if ( windows[nwindows-1] != FSwindow ) {
                tmpwin = windows[nwindows-1];
                for ( i=0; i<nwindows; ++i ) {
                    if ( windows[i] == FSwindow ) {
                        memcpy(&windows[i], &windows[i+1],
                               (nwindows-i-1)*sizeof(windows[i]));
                        break;
                    }
                }
                windows[nwindows-1] = FSwindow;
                XRestackWindows(SDL_Display, windows, nwindows);
                XSync(SDL_Display, False);
            }
            XFree(windows);
        }
#else
	XRaiseWindow(SDL_Display, FSwindow);
#endif

        /* Grab the mouse on the fullscreen window
           The event handling will know when we become active, and then
           enter fullscreen mode if we can't grab the mouse this time.
         */
#ifdef GRAB_FULLSCREEN
        if ( (XGrabPointer(SDL_Display, FSwindow, True, 0,
                          GrabModeAsync, GrabModeAsync,
                          FSwindow, None, CurrentTime) != GrabSuccess) ||
             (XGrabKeyboard(SDL_Display, WMwindow, True,
                          GrabModeAsync, GrabModeAsync, CurrentTime) != 0) ) {
#else
        if ( XGrabPointer(SDL_Display, FSwindow, True, 0,
                          GrabModeAsync, GrabModeAsync,
                          FSwindow, None, CurrentTime) != GrabSuccess ) {
#endif
            /* We lost the grab, so try again later */
            XUnmapWindow(SDL_Display, FSwindow);
            X11_WaitUnmapped(this, FSwindow);
            X11_QueueEnterFullScreen(this);
            return(0);
        }
#ifdef GRAB_FULLSCREEN
	SDL_PrivateAppActive(1, SDL_APPINPUTFOCUS);
#endif

#ifdef XFREE86_VM
        /* Save the current video mode */
        if ( use_vidmode ) {
            XVidMode(LockModeSwitch, (SDL_Display, SDL_Screen, True));
        }
#endif
        currently_fullscreen = 1;

        /* Set the new resolution */
        okay = X11_ResizeFullScreen(this);
        if ( ! okay ) {
            X11_LeaveFullScreen(this);
        }
	/* Set the colormap */
	if ( SDL_XColorMap ) {
		XInstallColormap(SDL_Display, SDL_XColorMap);
	}
    }
    X11_GrabInputNoLock(this, this->input_grab | SDL_GRAB_FULLSCREEN);
    return(okay);
}

int X11_LeaveFullScreen(_THIS)
{
    if ( currently_fullscreen ) {
        XReparentWindow(SDL_Display, SDL_Window, WMwindow, 0, 0);
#ifdef XFREE86_VM
        if ( use_vidmode ) {
            restore_mode(this);
            XVidMode(LockModeSwitch, (SDL_Display, SDL_Screen, False));
        }
#endif
        XUnmapWindow(SDL_Display, FSwindow);
        X11_WaitUnmapped(this, FSwindow);
#ifdef GRAB_FULLSCREEN
        XUngrabKeyboard(SDL_Display, CurrentTime);
#endif
        XSync(SDL_Display, True);   /* Flush spurious mode change events */
        currently_fullscreen = 0;
    }
    /* If we get popped out of fullscreen mode for some reason, input_grab
       will still have the SDL_GRAB_FULLSCREEN flag set, since this is only
       temporary.  In this case, release the grab unless the input has been
       explicitly grabbed.
     */
    X11_GrabInputNoLock(this, this->input_grab & ~SDL_GRAB_FULLSCREEN);
    return(0);
}
