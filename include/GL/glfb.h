#ifndef GLFB_H
#define GLFB_H

/*
** GLXContext is a pointer to opaque data.
*/
typedef struct __GLFBcontextRec *GLFBContext;


#include "fbdri.h"
#include "GL/glfbtokens.h"
#include "glfbclient.h"
#include "GL/xreplacements.h"


extern GLFBContext glFBCreateContext (FBDRI_Main *this);


#endif
