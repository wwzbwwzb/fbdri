#define MESALIB
/* 
We are supplying these functions, so we have to pretend that we are part of the MESA library,
so these symbols are not redefined by the mapgl header file.
*/
#include <GL/gl.h>
#include <stdlib.h>

#define STUB(function, string) \
	void function() \
	{ \
		printf("called " string "\n"); \
	}                                       
	

