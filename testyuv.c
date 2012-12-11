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
#include <quicktime.h>

#include "colormodels.h"



#define UNFINISHED 0
	
	
#define CUBE_WIDTH (float)16
#define CUBE_HEIGHT (float)9
#define CUBE_DEPTH (float)3
#define TEXTURE_SIDE 2048
#define VIEWPORT_CMODEL BC_YUV420P
#define MOVIE_CMODEL BC_YUV420P
#define MOVIE_W 1280
#define MOVIE_H 720
#define TOTAL_FRAMES 64

#define MOVIE_FILE "/home/movie.mov"
#define TEXTURE_FILE "test_2048.png"
//#define TEXTURE_FILE "test_1024.png"
//#define TEXTURE_FILE "test_512.png"



#define TEXTURE_COUNT 1


typedef struct
{
	struct timeval start_time;
	struct timeval last_time;
	int64_t frames, blits;
} status_t;

typedef struct
{
	SDL_Surface *screen;
	int w, h;
	int done;
	unsigned char value;
	float xrot, yrot, xrot_start, yrot_start, zoom, zoom_start;
	SDL_keysym key_pressed;
	GLuint texture[TEXTURE_COUNT];
	status_t status;
	int cursor_x, cursor_y;
	int which_button;
	int last_x, last_y;
	int button_down;
	unsigned char *movie_data;
	int frame_size;
	int current_frame;
	int frame_step;
	int total_frames;
	int current_texture;
	unsigned char y, u, v;
	int x1, y1, x2, y2;
	float tex_x1, tex_y1, tex_x2, tex_y2;
} viewport_t;


static unsigned long texture_offsets[] = 
{
	0x2000000,
	0x3000000
};


static int resolutions[][2] =
{
	1920, 1080,
	1280, 1024,
	640, 480
};








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


static void update_status(status_t *status)
{
	struct timeval new_time;
	double new_seconds;
	double old_seconds;
	gettimeofday(&new_time, 0);

return;
	new_seconds = (double)new_time.tv_sec + (double)new_time.tv_usec / 1000000;
	old_seconds = (double)status->start_time.tv_sec + (double)status->start_time.tv_usec / 1000000;

	if(new_seconds - old_seconds > 5)
	{
		fprintf(stderr, "      %lld frames/sec      \r", 
			(int64_t)((double)status->frames / 
				(new_seconds - old_seconds)));
		status->start_time = new_time;
		status->frames = 0;
		fflush(stdout);
		status->last_time = new_time;
	};
}

void stop_status()
{
	fprintf(stderr, "\n\n");
}



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


void draw_thing(viewport_t *viewport)
{
    glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





 	glPushMatrix();




	glTranslatef(0.0, 0.0, viewport->zoom);
	glRotatef(viewport->xrot, 0, 1, 0);
	glRotatef(viewport->yrot, 1, 0, 0);


// Back
	glColor4f(1.0, 0.0, 0.0, 0.7);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glVertex3f(-CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glVertex3f(-CUBE_WIDTH / 2, CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glVertex3f(CUBE_WIDTH / 2, CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);

// Right
	glColor4f(0.0, 1.0, 0.0, 0.7);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(CUBE_WIDTH / 2, CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glVertex3f(CUBE_WIDTH / 2, CUBE_HEIGHT / 2, CUBE_DEPTH / 2);
	glVertex3f(CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, CUBE_DEPTH / 2);
	glVertex3f(CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);

// Left
	glColor4f(0.0, 0.0, 1.0, 0.7);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glVertex3f(-CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, CUBE_DEPTH / 2);
	glVertex3f(-CUBE_WIDTH / 2, CUBE_HEIGHT / 2, CUBE_DEPTH / 2);
	glVertex3f(-CUBE_WIDTH / 2, CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);

// Top
	glColor4f(0.0, 1.0, 1.0, 0.7);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-CUBE_WIDTH / 2, CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glVertex3f(-CUBE_WIDTH / 2, CUBE_HEIGHT / 2, CUBE_DEPTH / 2);
	glVertex3f(CUBE_WIDTH / 2, CUBE_HEIGHT / 2, CUBE_DEPTH / 2);
	glVertex3f(CUBE_WIDTH / 2, CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);

// Bottom
	glColor4f(1.0, 1.0, 0.0, 0.7);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glVertex3f(CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, -CUBE_DEPTH / 2);
	glVertex3f(CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, CUBE_DEPTH / 2);
	glVertex3f(-CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, CUBE_DEPTH / 2);
	glEnd();



	glColor4f(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, viewport->texture[viewport->current_texture]);

	glBegin(GL_QUADS);

	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(viewport->tex_x2, viewport->tex_y1);   
	glVertex3f(CUBE_WIDTH / 2, CUBE_HEIGHT / 2, CUBE_DEPTH / 2);

	glTexCoord2f(viewport->tex_x1, viewport->tex_y1);   
	glVertex3f(-CUBE_WIDTH / 2, CUBE_HEIGHT / 2, CUBE_DEPTH / 2);

	glTexCoord2f(viewport->tex_x1, viewport->tex_y2);   
	glVertex3f(-CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, CUBE_DEPTH / 2);

	glTexCoord2f(viewport->tex_x2, viewport->tex_y2);   
	glVertex3f(CUBE_WIDTH / 2, -CUBE_HEIGHT / 2, CUBE_DEPTH / 2);

	glEnd();

    glDisable(GL_TEXTURE_2D);


	glFlush();






    glPopMatrix();


  	SDL_GL_SwapBuffers();
}








int get_next_texture(viewport_t *viewport)
{
	int next_texture = viewport->current_texture + 1;
	if(next_texture >= TEXTURE_COUNT) next_texture = 0;
	return next_texture;
}


void texture_iterate(viewport_t *viewport)
{
	unsigned char *data;
	int i, j;
	int next_texture = get_next_texture(viewport);
#define BYTES_PER_PIXEL 2
	
	data = (unsigned char*)viewport->screen->pixels + 
		texture_offsets[next_texture];

	memset(data, 0x80, TEXTURE_SIDE * TEXTURE_SIDE * 2);

	for(i = viewport->y1; i < viewport->y2; i++)
	{
		unsigned char *row = data + 
			i * TEXTURE_SIDE * BYTES_PER_PIXEL +
			((viewport->x1 * BYTES_PER_PIXEL) & 0xfffffffc);

		for(j = viewport->x1; j < viewport->x2; j += 2)
		{
			row[1] = row[3] = viewport->y;
			row[0] = viewport->u;
			row[2] = viewport->v;
			row += 4;
		}
	}

return;

	memset(data, 0x00, TEXTURE_SIDE * TEXTURE_SIDE * 4);
	memset(data, 
		viewport->y, 
		TEXTURE_SIDE * TEXTURE_SIDE);

	memset(data + 
		TEXTURE_SIDE * TEXTURE_SIDE, 
		viewport->u,
		TEXTURE_SIDE * TEXTURE_SIDE / 4);

	memset(data + 
		TEXTURE_SIDE * TEXTURE_SIDE +
		TEXTURE_SIDE * TEXTURE_SIDE / 4, 
		viewport->u,
		TEXTURE_SIDE * TEXTURE_SIDE / 4);

	viewport->current_frame += viewport->frame_step;

	if(viewport->current_frame >= viewport->total_frames )
	{
		viewport->current_frame = 0;
	}
}


void viewport_draw(viewport_t *viewport)
{
	texture_iterate(viewport);
//	usleep(4000);


	draw_thing(viewport);




	viewport->current_texture = get_next_texture(viewport);
	viewport->status.frames++;
	update_status(&viewport->status);
//	if(!viewport->button_down) viewport->xrot += 0.1;
};

void viewport_set_done(viewport_t *viewport)
{
	SDL_Event event;
	viewport->done = 1;

	event.type = SDL_QUIT;
	SDL_PushEvent(&event);
}



int keypress_event(viewport_t *viewport)
{
	int mod = viewport->key_pressed.mod;
//	printf("Key pressed: sym=%x mod=%x\n", viewport->key_pressed.sym, viewport->key_pressed.mod);


	switch(viewport->key_pressed.sym)
	{
		case 'y':
			if(mod & KMOD_SHIFT)
				viewport->y -= 8;
			else
				viewport->y += 8;
			break;

		case 'u':
			if(mod & KMOD_SHIFT)
				viewport->u -= 8;
			else
				viewport->u += 8;
			break;

		case 'v':
			if(mod & KMOD_SHIFT)
				viewport->v -= 8;
			else
				viewport->v += 8;
			break;

		case SDLK_LEFT:
			if(mod & KMOD_SHIFT)
				viewport->x2 -= 8;
			else
			if(mod & KMOD_CTRL)
				viewport->tex_x1 -= 0.1;
			else
			if(mod & KMOD_ALT)
				viewport->tex_x2 -= 0.1;
			else
				viewport->x1 -= 8;
			break;

		case SDLK_RIGHT:
			if(mod & KMOD_SHIFT)
				viewport->x2 += 8;
			else
			if(mod & KMOD_CTRL)
				viewport->tex_x1 += 0.1;
			else
			if(mod & KMOD_ALT)
				viewport->tex_x2 += 0.1;
			else
				viewport->x1 += 8;
			break;

		case SDLK_UP:
			if(mod & KMOD_SHIFT)
				viewport->y2 -= 8;
			else
			if(mod & KMOD_CTRL)
				viewport->tex_y1 -= 0.1;
			else
			if(mod & KMOD_ALT)
				viewport->tex_y2 -= 0.1;
			else
				viewport->y1 -= 8;
			break;

		case SDLK_DOWN:
			if(mod & KMOD_SHIFT)
				viewport->y2 += 8;
			else
			if(mod & KMOD_CTRL)
				viewport->tex_y1 += 0.1;
			else
			if(mod & KMOD_ALT)
				viewport->tex_y2 += 0.1;
			else
				viewport->y1 += 8;
			break;

		case 0x1b:
			stop_status();
			viewport_set_done(viewport);
			break;
	}
	
	printf("x1=%x y1=%x x2=%x y2=%x y=%x u=%x v=%x                  \n", 
		viewport->x1, viewport->y1, viewport->x2, viewport->y2, viewport->y, viewport->u, viewport->v);
	viewport_draw(viewport);
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

		viewport_draw(viewport);
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
				viewport->key_pressed = event.key.keysym;
				keypress_event(viewport);
				break;
			}

       		case SDL_MOUSEMOTION:
			{
				SDL_Event compress_event;
				while(SDL_PollEvent(&compress_event))
				{
					if(compress_event.type != SDL_MOUSEMOTION)
					{
						SDL_PushEvent(&compress_event);
						break;
					}
					event = compress_event;
				}

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
	viewport->x1 = 0;
	viewport->y1 = 0;
	viewport->y2 = TEXTURE_SIDE;
	viewport->x2 = TEXTURE_SIDE;

	viewport->tex_x1 = 0;
	viewport->tex_y1 = 0;
	viewport->tex_x2 = 1;
	viewport->tex_y2 = 1;


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


    glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
//	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//	glDepthMask(GL_FALSE);
//printf("main 2\n");











// Initialize movie
{
	unsigned char **row_pointers;
	int j, w, h;
	

	viewport->frame_size = TEXTURE_SIDE * TEXTURE_SIDE * 4;
	viewport->total_frames = TOTAL_FRAMES;
	viewport->movie_data = calloc(1, 
		TEXTURE_SIDE * TEXTURE_SIDE * 4);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	for(i = 0; i < TEXTURE_COUNT; i++)
	{
		glGenTextures(1, &viewport->texture[i]);
		glBindTexture(GL_TEXTURE_2D, viewport->texture[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glTexImage2D(GL_TEXTURE_2D, 
			0, 
			GL_RGB, 
			TEXTURE_SIDE,
        	TEXTURE_SIDE, 
			0, 
			GL_RGB, 
			GL_UNSIGNED_BYTE,
        	viewport->movie_data);
	}
//printf("main 3\n");
}
	viewport->current_frame = 0;
	viewport->frame_step = 1;

//printf("main 4\n");


//#endif // 0




// Initialize status
	init_status(&viewport->status);

	



	viewport_draw(viewport);


	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, viewport_loop, viewport);

	pthread_join(tid, 0);

//#endif // UNFINISHED

//printf("main 8\n");

	return 0;
}











