#include "GL/gl.h"



// Transferred from the glx backend in XFree86




#if 0
void glBegin(GLenum mode)
{
}

void glBindTexture(GLenum target, GLuint texture)
{
}

void glClear(GLbitfield mask)
{
}

void glDepthMask(GLboolean flag)
{
}

void glEnd(void)
{
}

void glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
}

void glLightfv(GLenum light, GLenum pname, const GLfloat *params)
{
}

void glLoadIdentity(void)
{
}

void glMatrixMode(GLenum mode)
{
}

void glPopMatrix(void)
{
}

void glPushMatrix(void)
{
}

void glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
}

void glTexCoord2f(GLfloat s, GLfloat t)
{
}

void glTexImage2D(GLenum target, GLint level, GLint components,
		  GLsizei width, GLsizei height, GLint border, GLenum format,
		  GLenum type, const GLvoid *image)
{
}

void glTexParameteri(GLenum target, GLenum pname, GLint param)
{
}

void glTexEnvf(GLenum target, GLenum pname, GLfloat param)
{
}

void glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
}

void glVertex3f(GLfloat x, GLfloat y, GLfloat z)
{
}

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	_mesa_Viewport( x, y, width, height );
}

#endif