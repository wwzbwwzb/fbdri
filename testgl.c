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
#define CUBE_DEPTH (float)5
#define TEXTURE_SIDE 2048
#define VIEWPORT_CMODEL BC_ABGR8888
#define BYTES_PER_PIXEL 4
#define MOVIE_W 1280
#define MOVIE_H 720
#define TOTAL_FRAMES 1000
#define RESOLUTION 20


#define MOVIE_FILE "movie.mov"
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
	GLfloat x, y, z;
} vector_t;

typedef struct
{
	vector_t vertices[RESOLUTION][RESOLUTION];
	vector_t normals[RESOLUTION][RESOLUTION];
} animation_frame_t;

typedef struct
{
	SDL_Surface *screen;
	int w, h;
	int done;
	unsigned char value;
	float xrot, yrot, xrot_start, yrot_start, zoom, zoom_start;
	SDLKey key_pressed;
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
	
	animation_frame_t *animation;
// Texture coords for every vertex
	vector_t tex_coords[RESOLUTION][RESOLUTION];
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

void update_status(status_t *status)
{
	struct timeval new_time;
	gettimeofday(&new_time, 0);
	if(new_time.tv_sec - status->last_time.tv_sec > 1)
	{
		fprintf(stderr, "%lld frames.  %lld frames/sec      \r", 
			status->frames,
			(int64_t)status->frames / 
			(int64_t)(new_time.tv_sec - status->start_time.tv_sec));
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

void viewport_set_done(viewport_t *viewport)
{
	SDL_Event event;
	viewport->done = 1;

	event.type = SDL_QUIT;
	SDL_PushEvent(&event);
}



void draw_thing(viewport_t *viewport)
{
	animation_frame_t *animation = &viewport->animation[viewport->current_frame];
	int i, j, k;

    glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





 	glPushMatrix();




	glTranslatef(0.0, 0.0, viewport->zoom);
	glRotatef(viewport->xrot, 0, 1, 0);
	glRotatef(viewport->yrot, 1, 0, 0);

	glColor4f(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, viewport->texture[viewport->current_texture]);
	glBegin(GL_QUADS);

	for(i = 0; i < RESOLUTION - 1; i++)
	{
		for(j = 0; j < RESOLUTION - 1; j++)
		{
			vector_t *vertex1 = &animation->vertices[i + 1][j + 1];
			vector_t *vertex2 = &animation->vertices[i][j + 1];
			vector_t *vertex3 = &animation->vertices[i][j];
			vector_t *vertex4 = &animation->vertices[i + 1][j];
			vector_t *normal = &animation->normals[i][j];
			vector_t *texcoord1 = &viewport->tex_coords[i + 1][j + 1];
			vector_t *texcoord2 = &viewport->tex_coords[i][j + 1];
			vector_t *texcoord3 = &viewport->tex_coords[i][j];
			vector_t *texcoord4 = &viewport->tex_coords[i + 1][j];
			
			glNormal3f(normal->x, normal->y, normal->z);

//printf(__FUNCTION__ " %.0fx%.0f %.0fx%.0f %.0fx%.0f %.0fx%.0f\n", 
//	texcoord1->x, texcoord1->y, texcoord2->x, texcoord2->y, texcoord3->x, texcoord3->y, texcoord4->x, texcoord4->y);
			glTexCoord2f(texcoord1->x, texcoord1->y);
			glVertex3f(vertex1->x, vertex1->y, vertex1->z);

			glTexCoord2f(texcoord2->x, texcoord2->y);
			glVertex3f(vertex2->x, vertex2->y, vertex2->z);

			glTexCoord2f(texcoord3->x, texcoord3->y);
			glVertex3f(vertex3->x, vertex3->y, vertex3->z);

			glTexCoord2f(texcoord4->x, texcoord4->y);
			glVertex3f(vertex4->x, vertex4->y, vertex4->z);
		}
	}


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
	unsigned char **in_rows, **out_rows;
	int i;
	int next_texture = get_next_texture(viewport);
	
	in_rows = calloc(1, sizeof(unsigned char*) * MOVIE_H);
	out_rows = calloc(1, sizeof(unsigned char*) * MOVIE_H);
	for(i = 0; i < MOVIE_H; i++)
	{
		in_rows[i] = viewport->movie_data + 
			viewport->frame_size * viewport->current_frame + 
			MOVIE_W * BYTES_PER_PIXEL * i;
		out_rows[i] = (unsigned char*)viewport->screen->pixels + 
			texture_offsets[next_texture] +
			TEXTURE_SIDE * BYTES_PER_PIXEL * i;
	}

//printf("texture_iterate 1 %d %dx%d\n", viewport->current_frame, viewport->movie_w, viewport->movie_h);
	cmodel_transfer(out_rows, /* Leave NULL if non existent */
		in_rows,
		0, /* Leave NULL if non existent */
		0,
		0,
		0, /* Leave NULL if non existent */
		0,
		0,
		0,        /* Dimensions to capture from input frame */
		0, 
		MOVIE_W, 
		MOVIE_H,
		0,       /* Dimensions to project on output frame */
		0, 
		MOVIE_W, 
		MOVIE_H,
		VIEWPORT_CMODEL, 
		VIEWPORT_CMODEL,
		0,         /* When transferring BC_RGBA8888 to non-alpha this is the background color in 0xRRGGBB hex */
		0,       /* For planar use the luma rowspan */
		0);     /* For planar use the luma rowspan */


	free(in_rows);
	free(out_rows);

	viewport->current_frame += viewport->frame_step;
	if(viewport->frame_step > 0)
	{
		if(viewport->current_frame >= viewport->total_frames - 1)
		{
			viewport->frame_step = -1;
		}
	}
	else
	{
		if(viewport->current_frame <= 0)
		{
			viewport->frame_step = 1;
		}
	}

	viewport->status.blits++;
}


void viewport_draw(viewport_t *viewport)
{
	texture_iterate(viewport);
//	usleep(4000);


	draw_thing(viewport);




	viewport->current_texture = get_next_texture(viewport);
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

static void normalize(vector_t *out)
{
	float length = sqrt(out->x * out->x +
		out->y * out->y +
		out->z * out->z);

	if(fabs(length) < 0.001) length = 1.0;
	
	out->x /= length;
	out->y /= length;
	out->z /= length;
}


static void calc_normal(vector_t *out, 
	vector_t *in1, 
	vector_t *in2, 
	vector_t *in3)
{
	vector_t v1, v2;

	v1.x = in1->x - in2->x;
	v1.y = in1->y - in2->y;
	v1.z = in1->z - in2->z;

	v2.x = in2->x - in3->x;
	v2.y = in2->y - in3->y;
	v2.z = in2->z - in3->z;

	out->x = v1.y * v2.z - v1.z * v2.y;
	out->y = v1.z * v2.x - v1.x * v2.z;
	out->z = v1.x * v2.y - v1.y * v2.x;

	normalize(out);
}

static GLfloat sinc(float x)
{
	if(fabs(x) < 0.001) return 1;
	return sin(x) / x;
}

static float sinc3(float x, float y)
{
	return sinc(x) * sinc(y);
}

static void init_animation(viewport_t *viewport)
{
	int i, j, k;
	viewport->animation = calloc(1, 
		sizeof(animation_frame_t) * viewport->total_frames);


// Get vertices
	for(i = 0; i < viewport->total_frames; i++)
	{
		animation_frame_t *animation = &viewport->animation[i];
		
		for(j = 0; j < RESOLUTION; j++)
		{
			for(k = 0; k < RESOLUTION; k++)
			{
				vector_t *vertex = &animation->vertices[j][k];
				vertex->z = 
					CUBE_DEPTH * 
					sinc3(((float)j - RESOLUTION / 2) * 1, 
						((float)k - RESOLUTION / 2) * 1) * 
					((float)i / viewport->total_frames * 2 - 1);
				vertex->x = (float)j / RESOLUTION * CUBE_WIDTH - CUBE_WIDTH / 2;
				vertex->y = (float)k / RESOLUTION * CUBE_HEIGHT - CUBE_HEIGHT / 2;
			}
		}
	}


// Get normals
	for(i = 0; i < viewport->total_frames; i++)
	{
		animation_frame_t *animation = &viewport->animation[i];
		
		for(j = 0; j < RESOLUTION - 1; j++)
		{
			for(k = 0; k < RESOLUTION - 1; k++)
			{
				vector_t *vertex1 = &animation->vertices[j][k];
				vector_t *vertex2 = &animation->vertices[j + 1][k];
				vector_t *vertex3 = &animation->vertices[j][k + 1];
				vector_t *out = &animation->normals[j][k];
				
				calc_normal(out, 
					vertex1, 
					vertex2, 
					vertex3);
			}
		}
	}
	
// Get texture coords
	for(j = 0; j < RESOLUTION; j++)
	{
		for(k = 0; k < RESOLUTION; k++)
		{
			vector_t *out = &viewport->tex_coords[j][k];
			
			out->x = (float)j / RESOLUTION * MOVIE_W / TEXTURE_SIDE;
			out->y = (float)(RESOLUTION - k) / RESOLUTION * MOVIE_H / TEXTURE_SIDE;
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
	quicktime_t *movie;
	unsigned char **row_pointers;
	int j, w, h;
	

	if(!(movie = quicktime_open(MOVIE_FILE, 1, 0)))
	{
		printf("Couldn't open movie file %s.\n", MOVIE_FILE);
		exit(1);
	}

	w = quicktime_video_width(movie, 0);
	h = quicktime_video_height(movie, 0);
	viewport->frame_size = MOVIE_W * MOVIE_H * BYTES_PER_PIXEL;
	viewport->total_frames = quicktime_video_length(movie, 0);
	if(viewport->total_frames > TOTAL_FRAMES) viewport->total_frames = TOTAL_FRAMES;
	viewport->movie_data = calloc(1, viewport->frame_size * viewport->total_frames);


	row_pointers = (unsigned char**)calloc(1, sizeof(unsigned char*) * TEXTURE_SIDE);

	for(i = 0; i < viewport->total_frames; i++)
	{
printf("Loading frame %d\r", i);
fflush(stdout);
		for(j = 0; j < MOVIE_H; j++) row_pointers[j] = 
			viewport->movie_data + 
			viewport->frame_size * i + 
			MOVIE_W * BYTES_PER_PIXEL * j;

		quicktime_decode_scaled(movie, 
			0,                    /* Location of input frame to take picture */
			0,
			w,
			h,
			MOVIE_W,                   /* Dimensions of output frame */
			MOVIE_H,
			VIEWPORT_CMODEL,             /* One of the color models defined above */
			row_pointers, 
			0);
	}

	quicktime_close(movie);

	free(row_pointers);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	for(i = 0; i < TEXTURE_COUNT; i++)
	{
		glGenTextures(1, viewport->texture[i]);
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
	viewport->frame_step = 0;

//printf("main 4\n");


//#endif // 0




// Initialize status
	init_status(&viewport->status);

	init_animation(viewport);





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











