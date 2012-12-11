#include "GL/gl.h"
#include "SDL.h"

#include <math.h>
#include <png.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>






#define UNFINISHED 0
	
	
#define CUBE_WIDTH (float)16
#define CUBE_HEIGHT (float)9
#define CUBE_DEPTH (float)3

#define IMAGE_WIDTH 1920
#define IMAGE_HEIGHT 1080

//#define TEXTURE_FILE "test_2048.png"
#define TEXTURE_FILE "test_1024.png"
//#define TEXTURE_FILE "test_512.png"





typedef struct
{
	struct timeval start_time;
	struct timeval last_time;
	int64_t frames, blits;
} status_t;




typedef struct
{
	struct timeval start_time;
	struct timeval last_time;
	int64_t frames;
} synchronizer_t;



void init_status(status_t *status)
{
	gettimeofday(&status->start_time, 0);
	gettimeofday(&status->last_time, 0);
	status->frames = 0;
	status->blits = 0;
}

void update_status(status_t *status)
{
	struct timeval new_time;
	gettimeofday(&new_time, 0);
	if(new_time.tv_sec - status->last_time.tv_sec > 1)
	{
		fprintf(stderr, "%lld frames.  %lld blits   %lld frames/sec  %lld blits/sec           \r", 
			status->frames,
			status->blits,
			(int64_t)status->frames / 
			(int64_t)(new_time.tv_sec - status->start_time.tv_sec),
			(int64_t)status->blits / 
			(int64_t)(new_time.tv_sec - status->start_time.tv_sec));
		fflush(stdout);
		status->last_time = new_time;
	};
}

void stop_status()
{
	fprintf(stderr, "\n\n");
}






typedef struct
{
	SDL_Surface *screen;
	int w, h;
	int done;
	unsigned char value;
	float xrot, yrot, xrot_start, yrot_start, zoom, zoom_start;
	SDLKey key_pressed;
	GLuint texName;
	status_t status;
	int cursor_x, cursor_y;
	int which_button;
	int last_x, last_y;
	int button_down;
} viewport_t;



static int resolutions[][2] =
{
	1920, 1080,
	1280, 1024,
	640, 480
};



viewport_t* new_viewport(int w, int h)
{
	viewport_t *result = (viewport_t *)calloc(sizeof(viewport_t), 1);
	int i;


	if(SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "new_viewport: SDL_Init: %s.\n", SDL_GetError());
		exit(1);
	}

	for(i = 0; i < sizeof(resolutions) / sizeof(int*); i++)
	{
		result->w = resolutions[i][0];
		result->h = resolutions[i][1];
		
		fprintf(stderr, "new_viewport: trying %dx%d.\n", result->w, result->h);

		if((result->screen = SDL_SetVideoMode(result->w, 
			result->h, 
			32,
			(SDL_OPENGL|SDL_ANYFORMAT|SDL_DOUBLEBUF))))
		{
			break;
		}
		else
		{
			fprintf(stderr, "new_viewport: SDL_SetVideoMode: %s.\n", SDL_GetError());
		}
	}
		

	if(!result->screen)
	{
		fprintf(stderr, "new_viewport: SDL_SetVideoMode: %s.\n", SDL_GetError());
		exit(1);
	}
	
	return result;
}

void viewport_set_done(viewport_t *viewport)
{
	SDL_Event event;
	viewport->done = 1;

	event.type = SDL_QUIT;
	SDL_PushEvent(&event);
}

void clear_viewport()
{
    glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void draw_thing(viewport_t *viewport)
{
 	glPushMatrix();


//printf("draw_thing 1\n");


	glTranslatef(0.0, 0.0, viewport->zoom);
//printf("draw_thing 2\n");
	glRotatef(viewport->xrot, 0, 1, 0);
//printf("draw_thing 3\n");
	glRotatef(viewport->yrot, 1, 0, 0);
//printf("draw_thing 4\n");









//#if 0

// Back
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(CUBE_WIDTH / 2, CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glVertex3f(-CUBE_WIDTH / 2, CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glVertex3f(-CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glVertex3f(CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glEnd();

// Right
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(CUBE_WIDTH / 2, CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glVertex3f(CUBE_WIDTH / 2, CUBE_HEIGHT / 2, CUBE_DEPTH / 2);
	glVertex3f(CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, CUBE_DEPTH / 2);
	glVertex3f(CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glEnd();

// Left
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-CUBE_WIDTH / 2, CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glVertex3f(-CUBE_WIDTH / 2, CUBE_HEIGHT / 2, CUBE_DEPTH / 2);
	glVertex3f(-CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, CUBE_DEPTH / 2);
	glVertex3f(-CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glEnd();

// Top
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-CUBE_WIDTH / 2, CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glVertex3f(-CUBE_WIDTH / 2, CUBE_HEIGHT / 2, CUBE_DEPTH / 2);
	glVertex3f(CUBE_WIDTH / 2, CUBE_HEIGHT / 2, CUBE_DEPTH / 2);
	glVertex3f(CUBE_WIDTH / 2, CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glEnd();

// Bottom
	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glVertex3f(-CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, CUBE_DEPTH / 2);
	glVertex3f(CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, CUBE_DEPTH / 2);
	glVertex3f(CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glEnd();


//#endif



    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, viewport->texName);

	glBegin(GL_QUADS);

	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f((float)IMAGE_WIDTH / 2048, 0.0);   
	glVertex3f(CUBE_WIDTH / 2, CUBE_HEIGHT / 2, CUBE_DEPTH / 2);

	glTexCoord2f(0.0, 0.0);   
	glVertex3f(-CUBE_WIDTH / 2, CUBE_HEIGHT / 2, CUBE_DEPTH / 2);

	glTexCoord2f(0.0, (float)IMAGE_HEIGHT / 2048);   
	glVertex3f(-CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, CUBE_DEPTH / 2);

	glTexCoord2f((float)IMAGE_WIDTH / 2048, (float)IMAGE_HEIGHT / 2048);   
	glVertex3f(CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, CUBE_DEPTH / 2);

	glEnd();


    glDisable(GL_TEXTURE_2D);


	glFlush();






    glPopMatrix();
}


// Draw stuff on top of objects and flash
void draw_overlays()
{
  	SDL_GL_SwapBuffers();
}


void texture_iterate(viewport_t *viewport)
{
	memset((unsigned char*)viewport->screen->pixels + 0x1800000, 
		viewport->value, 
		1920*1080*2);
	viewport->value += 10;
	if(viewport->value >= 255) viewport->value = 0;
	viewport->status.blits++;
}


void viewport_draw(viewport_t *viewport)
{
//	usleep(14000);

	clear_viewport();

//printf("viewport_draw 2\n");
	draw_thing(viewport);

//printf("viewport_draw 3\n");
	draw_overlays();
//printf("viewport_draw 4\n");

	texture_iterate(viewport);
	viewport->status.frames++;
	update_status(&viewport->status);
	if(!viewport->button_down) viewport->xrot += 0.1;
};


int keypress_event(viewport_t *viewport)
{
	printf("Key pressed: %c\n", viewport->key_pressed);
	stop_status();
	viewport_set_done(viewport);
	return 1;
};









int button_press(viewport_t *viewport)
{
	viewport->zoom_start = viewport->zoom;
	viewport->xrot_start = viewport->xrot;
	viewport->yrot_start = viewport->yrot;
	viewport->last_x = viewport->cursor_x;
	viewport->last_y = viewport->cursor_y;
	return 1;
};




int cursor_motion(viewport_t *viewport)
{
	if(viewport->button_down)
	{
		if(viewport->which_button == 1)
		{
			viewport->zoom = viewport->zoom_start + (float)(viewport->cursor_y - viewport->last_y) / 8;
		}
		else
		{
			viewport->xrot = viewport->xrot_start + (float)(viewport->cursor_x - viewport->last_x);
			viewport->yrot = viewport->yrot_start + (float)(viewport->cursor_y - viewport->last_y);
		}
		return 1;
	}
};










void* viewport_loop(void *ptr)
{
	viewport_t *viewport = (viewport_t *)ptr;
	SDL_Event event;

//printf("viewport_loop 1\n");
	while(!viewport->done)
	{
		int result = !SDL_WaitEvent(&event);
//printf("viewport_loop 2\n");

		if(result) viewport->done = 1;

		switch(event.type)
		{
			case SDL_KEYDOWN:
			{
				stop_status();
				viewport_set_done(viewport);
				break;
			}

       		case SDL_MOUSEMOTION:
			{
				SDL_MouseMotionEvent *mouse_event = (SDL_MouseMotionEvent*)&event;
				viewport->cursor_x = mouse_event->x;
				viewport->cursor_y = mouse_event->y;
				cursor_motion(viewport);
				break;
			}

       		case SDL_MOUSEBUTTONDOWN:
			{
				SDL_MouseButtonEvent *mouse_event = (SDL_MouseButtonEvent*)&event;
				viewport->which_button = mouse_event->button - 1;
				viewport->button_down = 1;
				button_press(viewport);
				break;
			}

       		case SDL_MOUSEBUTTONUP:
				viewport->button_down = 0;
				break;

			case SDL_QUIT:
				viewport->done = 1;
				break;
		}
	}
}









// Constantly writes garbage into the texture memory
void* texture_loop(void *ptr)
{
	viewport_t *viewport = (viewport_t *)ptr;
	int value = 0;
	int i;
	
	while(1)
	{
		memset((unsigned char*)viewport->screen->pixels + 0x1800000, value, 1920*1080*2);
		value++;
		if(value >= 255) value = 0;
		viewport->status.blits++;
		update_status(&viewport->status);
	}
}








int main()
{
	viewport_t *viewport;
	int last_x, last_y;
	pthread_attr_t  attr;
	pthread_t tid;
	int i;
	GLfloat ratio;
    static GLfloat light_position[] = { 5.0, 5.0, 10.0, 0.0 };
    static GLfloat diffuse_light[] = { 1.0, 1.0, 1.0, 1.0 };
	



//printf("main 1\n");

	viewport = new_viewport(1280, 1024);


//printf("main 2\n");
	viewport->xrot = 20.0;
	viewport->yrot = 30.0;
	viewport->zoom = -40.0;





//#if UNFINISHED


// Initialize OpenGL
// From the reshape event handler
  	glViewport(0, 0, viewport->w, viewport->h);
//printf("main 2\n");
	glMatrixMode(GL_PROJECTION);
//printf("main 2\n");
	glLoadIdentity();
//printf("main 2\n");

  	ratio = (GLfloat)viewport->h / (GLfloat)viewport->w;
//printf("main 2\n");
 	glFrustum(-1.0, 
		1.0, 
		-ratio, 
		ratio, 
		5.0, 
		600.0);
//printf("main 2\n");
	glMatrixMode(GL_MODELVIEW);
//printf("main 2\n");
	glLoadIdentity();
//printf("main 2\n");


    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glDepthMask(GL_FALSE);
//printf("main 2\n");











// Initialize texture
//#if 0
{
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	png_infop info_ptr = png_create_info_struct(png_ptr);
	FILE *fd = fopen(TEXTURE_FILE, "rb");
	int w;
	int h;
	int color_model;
	unsigned char **row_pointers;
	unsigned char *data;

	if(!fd)
	{
		printf("Couldn't open %s.\n", TEXTURE_FILE);
		exit(1);
	}

	png_init_io(png_ptr, fd);
	png_read_info(png_ptr, info_ptr);
	w = png_get_image_width(png_ptr, info_ptr);
	h = png_get_image_height(png_ptr, info_ptr);
	color_model = png_get_color_type(png_ptr, info_ptr);
	row_pointers = (unsigned char**)calloc(1, sizeof(png_bytep) * h);
	data = (unsigned char*)calloc(1, w * h * 3);
	for(i = 0; i < h; i++) row_pointers[i] = data + w * 3 * i;
	png_read_image(png_ptr, row_pointers);


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &viewport->texName);
	glBindTexture(GL_TEXTURE_2D, viewport->texName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexImage2D(GL_TEXTURE_2D, 
		0, 
		GL_RGB, 
		w,
        h, 
		0, 
		GL_RGB, 
		GL_UNSIGNED_BYTE,
        row_pointers[0]);
//printf("main 3\n");

	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	free(row_pointers);
	free(data);
	fclose(fd);
}


//printf("main 4\n");


//#endif // 0




// Initialize status
	init_status(&viewport->status);

	





	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, viewport_loop, viewport);
//	pthread_create(&tid, &attr, texture_loop, viewport);

	
	while(!viewport->done)
	{
//printf("main 5\n");
		viewport_draw(viewport);

//		SDL_ScanFrameBuffer(viewport->screen);
		
//printf("main 6 press a key\n");
//getc(stdin);
//exit(0);
	}


//#endif // UNFINISHED

//printf("main 8\n");

	return 0;
}











