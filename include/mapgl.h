/************************************************************************/
/*                                                                      */
/*                              mapgl.h									*/                             
/*                                                                      */
/* Created  by  alt.software inc. for Pioneer Research Center, USA      */
/* Author:	Bill McLean, Adam Williams									*/
/* Created: 2001/07/19 1:29:19 PM										*/  
/*																		*/
/* $LOG$
 ************************************************************************/


/*
This files maps the glfunctions to the appropiate mesa functions. Rather
than creating a stub function that calls the corresponding mesa function,
the same mapping is accomplished by using the C preprocessor. When the
Mesa library is compiled this remapping MUST be disabled.

When new versions of the Mesa libray is released, the current GL/gl.h must
be differenced with the new GL/gl.h. This will provide a list of functions
that must be added/deleted from this file.
*/
#ifndef mapgl_h
#define mapgl_h

#ifdef __cplusplus
extern "C" {
#endif

#define TheFoobar "this"

#ifndef MESALIB
//#include <vbfill.h>         // Breaks vector.h in C++
#endif









/*
 * Miscellaneous
 */

GLAPI void GLAPIENTRY _mesa_ClearIndex( GLfloat c );

GLAPI void GLAPIENTRY _mesa_ClearColor( GLclampf red,
			  GLclampf green,
			  GLclampf blue,
			  GLclampf alpha );

GLAPI void GLAPIENTRY _mesa_Clear( GLbitfield mask );

GLAPI void GLAPIENTRY _mesa_IndexMask( GLuint mask );

GLAPI void GLAPIENTRY _mesa_ColorMask( GLboolean red, GLboolean green,
			 GLboolean blue, GLboolean alpha );

GLAPI void GLAPIENTRY _mesa_AlphaFunc( GLenum func, GLclampf ref );

GLAPI void GLAPIENTRY _mesa_BlendFunc( GLenum sfactor, GLenum dfactor );

GLAPI void GLAPIENTRY _mesa_LogicOp( GLenum opcode );

GLAPI void GLAPIENTRY _mesa_CullFace( GLenum mode );

GLAPI void GLAPIENTRY _mesa_FrontFace( GLenum mode );

GLAPI void GLAPIENTRY _mesa_PointSize( GLfloat size );

GLAPI void GLAPIENTRY _mesa_LineWidth( GLfloat width );

GLAPI void GLAPIENTRY _mesa_LineStipple( GLint factor, GLushort pattern );

GLAPI void GLAPIENTRY _mesa_PolygonMode( GLenum face, GLenum mode );

GLAPI void GLAPIENTRY _mesa_PolygonOffset( GLfloat factor, GLfloat units );

GLAPI void GLAPIENTRY _mesa_PolygonStipple( const GLubyte *mask );

GLAPI void GLAPIENTRY _mesa_GetPolygonStipple( GLubyte *mask );

GLAPI void GLAPIENTRY _mesa_EdgeFlag( GLboolean flag );

GLAPI void GLAPIENTRY _mesa_EdgeFlagv( const GLboolean *flag );

GLAPI void GLAPIENTRY _mesa_Scissor( GLint x, GLint y,
                                   GLsizei width, GLsizei height);

GLAPI void GLAPIENTRY _mesa_ClipPlane( GLenum plane, const GLdouble *equation );

GLAPI void GLAPIENTRY _mesa_GetClipPlane( GLenum plane, GLdouble *equation );

GLAPI void GLAPIENTRY _mesa_DrawBuffer( GLenum mode );

GLAPI void GLAPIENTRY _mesa_ReadBuffer( GLenum mode );

GLAPI void GLAPIENTRY _mesa_Enable( GLenum cap );

GLAPI void GLAPIENTRY _mesa_Disable( GLenum cap );

GLAPI GLboolean GLAPIENTRY _mesa_IsEnabled( GLenum cap );


GLAPI void GLAPIENTRY _mesa_EnableClientState( GLenum cap );  /* 1.1 */

GLAPI void GLAPIENTRY _mesa_DisableClientState( GLenum cap );  /* 1.1 */


GLAPI void GLAPIENTRY _mesa_GetBooleanv( GLenum pname, GLboolean *params );

GLAPI void GLAPIENTRY _mesa_GetDoublev( GLenum pname, GLdouble *params );

GLAPI void GLAPIENTRY _mesa_GetFloatv( GLenum pname, GLfloat *params );

GLAPI void GLAPIENTRY _mesa_GetIntegerv( GLenum pname, GLint *params );


GLAPI void GLAPIENTRY _mesa_PushAttrib( GLbitfield mask );

GLAPI void GLAPIENTRY _mesa_PopAttrib( void );


GLAPI void GLAPIENTRY _mesa_PushClientAttrib( GLbitfield mask );  /* 1.1 */

GLAPI void GLAPIENTRY _mesa_PopClientAttrib( void );  /* 1.1 */


GLAPI GLint GLAPIENTRY _mesa_RenderMode( GLenum mode );

GLAPI GLenum GLAPIENTRY _mesa_GetError( void );

GLAPI const GLubyte* GLAPIENTRY _mesa_GetString( GLenum name );

GLAPI void GLAPIENTRY _mesa_Finish( void );

GLAPI void GLAPIENTRY _mesa_Flush( void );

GLAPI void GLAPIENTRY _mesa_Hint( GLenum target, GLenum mode );



/*
 * Depth Buffer
 */

GLAPI void GLAPIENTRY _mesa_ClearDepth( GLclampd depth );

GLAPI void GLAPIENTRY _mesa_DepthFunc( GLenum func );

GLAPI void GLAPIENTRY _mesa_DepthMask( GLboolean flag );

GLAPI void GLAPIENTRY _mesa_DepthRange( GLclampd near_val, GLclampd far_val );


/*
 * Accumulation Buffer
 */

GLAPI void GLAPIENTRY _mesa_ClearAccum( GLfloat red, GLfloat green,
                                      GLfloat blue, GLfloat alpha );

GLAPI void GLAPIENTRY _mesa_Accum( GLenum op, GLfloat value );



/*
 * Transformation
 */

GLAPI void GLAPIENTRY _mesa_MatrixMode( GLenum mode );

GLAPI void GLAPIENTRY _mesa_Ortho( GLdouble left, GLdouble right,
                                 GLdouble bottom, GLdouble top,
                                 GLdouble near_val, GLdouble far_val );

GLAPI void GLAPIENTRY _mesa_Frustum( GLdouble left, GLdouble right,
                                   GLdouble bottom, GLdouble top,
                                   GLdouble near_val, GLdouble far_val );

GLAPI void GLAPIENTRY _mesa_Viewport( GLint x, GLint y,
                                    GLsizei width, GLsizei height );

GLAPI void GLAPIENTRY _mesa_PushMatrix( void );

GLAPI void GLAPIENTRY _mesa_PopMatrix( void );

GLAPI void GLAPIENTRY _mesa_LoadIdentity( void );

GLAPI void GLAPIENTRY _mesa_LoadMatrixd( const GLdouble *m );
GLAPI void GLAPIENTRY _mesa_LoadMatrixf( const GLfloat *m );

GLAPI void GLAPIENTRY _mesa_MultMatrixd( const GLdouble *m );
GLAPI void GLAPIENTRY _mesa_MultMatrixf( const GLfloat *m );

GLAPI void GLAPIENTRY _mesa_Rotated( GLdouble an_mesa_e,
                                   GLdouble x, GLdouble y, GLdouble z );
GLAPI void GLAPIENTRY _mesa_Rotatef( GLfloat an_mesa_e,
                                   GLfloat x, GLfloat y, GLfloat z );

GLAPI void GLAPIENTRY _mesa_Scaled( GLdouble x, GLdouble y, GLdouble z );
GLAPI void GLAPIENTRY _mesa_Scalef( GLfloat x, GLfloat y, GLfloat z );

GLAPI void GLAPIENTRY _mesa_Translated( GLdouble x, GLdouble y, GLdouble z );
GLAPI void GLAPIENTRY _mesa_Translatef( GLfloat x, GLfloat y, GLfloat z );



/*
 * Display Lists
 */

GLAPI GLboolean GLAPIENTRY _mesa_IsList( GLuint list );

GLAPI void GLAPIENTRY _mesa_DeleteLists( GLuint list, GLsizei range );

GLAPI GLuint GLAPIENTRY _mesa_GenLists( GLsizei range );

GLAPI void GLAPIENTRY _mesa_NewList( GLuint list, GLenum mode );

GLAPI void GLAPIENTRY _mesa_EndList( void );

GLAPI void GLAPIENTRY _mesa_CallList( GLuint list );

GLAPI void GLAPIENTRY _mesa_CallLists( GLsizei n, GLenum type,
                                     const GLvoid *lists );

GLAPI void GLAPIENTRY _mesa_ListBase( GLuint base );



/*
 * Drawing Functions
 */

GLAPI void GLAPIENTRY _mesa_Begin( GLenum mode );

GLAPI void GLAPIENTRY _mesa_End( void );


GLAPI void GLAPIENTRY _mesa_Vertex2d( GLdouble x, GLdouble y );
GLAPI void GLAPIENTRY _mesa_Vertex2f( GLfloat x, GLfloat y );
GLAPI void GLAPIENTRY _mesa_Vertex2i( GLint x, GLint y );
GLAPI void GLAPIENTRY _mesa_Vertex2s( GLshort x, GLshort y );

GLAPI void GLAPIENTRY _mesa_Vertex3d( GLdouble x, GLdouble y, GLdouble z );
GLAPI void GLAPIENTRY _mesa_Vertex3f( GLfloat x, GLfloat y, GLfloat z );
GLAPI void GLAPIENTRY _mesa_Vertex3i( GLint x, GLint y, GLint z );
GLAPI void GLAPIENTRY _mesa_Vertex3s( GLshort x, GLshort y, GLshort z );

GLAPI void GLAPIENTRY _mesa_Vertex4d( GLdouble x, GLdouble y, GLdouble z, GLdouble w );
GLAPI void GLAPIENTRY _mesa_Vertex4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w );
GLAPI void GLAPIENTRY _mesa_Vertex4i( GLint x, GLint y, GLint z, GLint w );
GLAPI void GLAPIENTRY _mesa_Vertex4s( GLshort x, GLshort y, GLshort z, GLshort w );

GLAPI void GLAPIENTRY _mesa_Vertex2dv( const GLdouble *v );
GLAPI void GLAPIENTRY _mesa_Vertex2fv( const GLfloat *v );
GLAPI void GLAPIENTRY _mesa_Vertex2iv( const GLint *v );
GLAPI void GLAPIENTRY _mesa_Vertex2sv( const GLshort *v );

GLAPI void GLAPIENTRY _mesa_Vertex3dv( const GLdouble *v );
GLAPI void GLAPIENTRY _mesa_Vertex3fv( const GLfloat *v );
GLAPI void GLAPIENTRY _mesa_Vertex3iv( const GLint *v );
GLAPI void GLAPIENTRY _mesa_Vertex3sv( const GLshort *v );

GLAPI void GLAPIENTRY _mesa_Vertex4dv( const GLdouble *v );
GLAPI void GLAPIENTRY _mesa_Vertex4fv( const GLfloat *v );
GLAPI void GLAPIENTRY _mesa_Vertex4iv( const GLint *v );
GLAPI void GLAPIENTRY _mesa_Vertex4sv( const GLshort *v );


GLAPI void GLAPIENTRY _mesa_Normal3b( GLbyte nx, GLbyte ny, GLbyte nz );
GLAPI void GLAPIENTRY _mesa_Normal3d( GLdouble nx, GLdouble ny, GLdouble nz );
GLAPI void GLAPIENTRY _mesa_Normal3f( GLfloat nx, GLfloat ny, GLfloat nz );
GLAPI void GLAPIENTRY _mesa_Normal3i( GLint nx, GLint ny, GLint nz );
GLAPI void GLAPIENTRY _mesa_Normal3s( GLshort nx, GLshort ny, GLshort nz );

GLAPI void GLAPIENTRY _mesa_Normal3bv( const GLbyte *v );
GLAPI void GLAPIENTRY _mesa_Normal3dv( const GLdouble *v );
GLAPI void GLAPIENTRY _mesa_Normal3fv( const GLfloat *v );
GLAPI void GLAPIENTRY _mesa_Normal3iv( const GLint *v );
GLAPI void GLAPIENTRY _mesa_Normal3sv( const GLshort *v );


GLAPI void GLAPIENTRY _mesa_Indexd( GLdouble c );
GLAPI void GLAPIENTRY _mesa_Indexf( GLfloat c );
GLAPI void GLAPIENTRY _mesa_Indexi( GLint c );
GLAPI void GLAPIENTRY _mesa_Indexs( GLshort c );
GLAPI void GLAPIENTRY _mesa_Indexub( GLubyte c );  /* 1.1 */

GLAPI void GLAPIENTRY _mesa_Indexdv( const GLdouble *c );
GLAPI void GLAPIENTRY _mesa_Indexfv( const GLfloat *c );
GLAPI void GLAPIENTRY _mesa_Indexiv( const GLint *c );
GLAPI void GLAPIENTRY _mesa_Indexsv( const GLshort *c );
GLAPI void GLAPIENTRY _mesa_Indexubv( const GLubyte *c );  /* 1.1 */

GLAPI void GLAPIENTRY _mesa_Color3b( GLbyte red, GLbyte green, GLbyte blue );
GLAPI void GLAPIENTRY _mesa_Color3d( GLdouble red, GLdouble green, GLdouble blue );
GLAPI void GLAPIENTRY _mesa_Color3f( GLfloat red, GLfloat green, GLfloat blue );
GLAPI void GLAPIENTRY _mesa_Color3i( GLint red, GLint green, GLint blue );
GLAPI void GLAPIENTRY _mesa_Color3s( GLshort red, GLshort green, GLshort blue );
GLAPI void GLAPIENTRY _mesa_Color3ub( GLubyte red, GLubyte green, GLubyte blue );
GLAPI void GLAPIENTRY _mesa_Color3ui( GLuint red, GLuint green, GLuint blue );
GLAPI void GLAPIENTRY _mesa_Color3us( GLushort red, GLushort green, GLushort blue );

GLAPI void GLAPIENTRY _mesa_Color4b( GLbyte red, GLbyte green,
                                   GLbyte blue, GLbyte alpha );
GLAPI void GLAPIENTRY _mesa_Color4d( GLdouble red, GLdouble green,
                                   GLdouble blue, GLdouble alpha );
GLAPI void GLAPIENTRY _mesa_Color4f( GLfloat red, GLfloat green,
                                   GLfloat blue, GLfloat alpha );
GLAPI void GLAPIENTRY _mesa_Color4i( GLint red, GLint green,
                                   GLint blue, GLint alpha );
GLAPI void GLAPIENTRY _mesa_Color4s( GLshort red, GLshort green,
                                   GLshort blue, GLshort alpha );
GLAPI void GLAPIENTRY _mesa_Color4ub( GLubyte red, GLubyte green,
                                    GLubyte blue, GLubyte alpha );
GLAPI void GLAPIENTRY _mesa_Color4ui( GLuint red, GLuint green,
                                    GLuint blue, GLuint alpha );
GLAPI void GLAPIENTRY _mesa_Color4us( GLushort red, GLushort green,
                                    GLushort blue, GLushort alpha );


GLAPI void GLAPIENTRY _mesa_Color3bv( const GLbyte *v );
GLAPI void GLAPIENTRY _mesa_Color3dv( const GLdouble *v );
GLAPI void GLAPIENTRY _mesa_Color3fv( const GLfloat *v );
GLAPI void GLAPIENTRY _mesa_Color3iv( const GLint *v );
GLAPI void GLAPIENTRY _mesa_Color3sv( const GLshort *v );
GLAPI void GLAPIENTRY _mesa_Color3ubv( const GLubyte *v );
GLAPI void GLAPIENTRY _mesa_Color3uiv( const GLuint *v );
GLAPI void GLAPIENTRY _mesa_Color3usv( const GLushort *v );

GLAPI void GLAPIENTRY _mesa_Color4bv( const GLbyte *v );
GLAPI void GLAPIENTRY _mesa_Color4dv( const GLdouble *v );
GLAPI void GLAPIENTRY _mesa_Color4fv( const GLfloat *v );
GLAPI void GLAPIENTRY _mesa_Color4iv( const GLint *v );
GLAPI void GLAPIENTRY _mesa_Color4sv( const GLshort *v );
GLAPI void GLAPIENTRY _mesa_Color4ubv( const GLubyte *v );
GLAPI void GLAPIENTRY _mesa_Color4uiv( const GLuint *v );
GLAPI void GLAPIENTRY _mesa_Color4usv( const GLushort *v );


GLAPI void GLAPIENTRY _mesa_TexCoord1d( GLdouble s );
GLAPI void GLAPIENTRY _mesa_TexCoord1f( GLfloat s );
GLAPI void GLAPIENTRY _mesa_TexCoord1i( GLint s );
GLAPI void GLAPIENTRY _mesa_TexCoord1s( GLshort s );

GLAPI void GLAPIENTRY _mesa_TexCoord2d( GLdouble s, GLdouble t );
GLAPI void GLAPIENTRY _mesa_TexCoord2f( GLfloat s, GLfloat t );
GLAPI void GLAPIENTRY _mesa_TexCoord2i( GLint s, GLint t );
GLAPI void GLAPIENTRY _mesa_TexCoord2s( GLshort s, GLshort t );

GLAPI void GLAPIENTRY _mesa_TexCoord3d( GLdouble s, GLdouble t, GLdouble r );
GLAPI void GLAPIENTRY _mesa_TexCoord3f( GLfloat s, GLfloat t, GLfloat r );
GLAPI void GLAPIENTRY _mesa_TexCoord3i( GLint s, GLint t, GLint r );
GLAPI void GLAPIENTRY _mesa_TexCoord3s( GLshort s, GLshort t, GLshort r );

GLAPI void GLAPIENTRY _mesa_TexCoord4d( GLdouble s, GLdouble t, GLdouble r, GLdouble q );
GLAPI void GLAPIENTRY _mesa_TexCoord4f( GLfloat s, GLfloat t, GLfloat r, GLfloat q );
GLAPI void GLAPIENTRY _mesa_TexCoord4i( GLint s, GLint t, GLint r, GLint q );
GLAPI void GLAPIENTRY _mesa_TexCoord4s( GLshort s, GLshort t, GLshort r, GLshort q );

GLAPI void GLAPIENTRY _mesa_TexCoord1dv( const GLdouble *v );
GLAPI void GLAPIENTRY _mesa_TexCoord1fv( const GLfloat *v );
GLAPI void GLAPIENTRY _mesa_TexCoord1iv( const GLint *v );
GLAPI void GLAPIENTRY _mesa_TexCoord1sv( const GLshort *v );

GLAPI void GLAPIENTRY _mesa_TexCoord2dv( const GLdouble *v );
GLAPI void GLAPIENTRY _mesa_TexCoord2fv( const GLfloat *v );
GLAPI void GLAPIENTRY _mesa_TexCoord2iv( const GLint *v );
GLAPI void GLAPIENTRY _mesa_TexCoord2sv( const GLshort *v );

GLAPI void GLAPIENTRY _mesa_TexCoord3dv( const GLdouble *v );
GLAPI void GLAPIENTRY _mesa_TexCoord3fv( const GLfloat *v );
GLAPI void GLAPIENTRY _mesa_TexCoord3iv( const GLint *v );
GLAPI void GLAPIENTRY _mesa_TexCoord3sv( const GLshort *v );

GLAPI void GLAPIENTRY _mesa_TexCoord4dv( const GLdouble *v );
GLAPI void GLAPIENTRY _mesa_TexCoord4fv( const GLfloat *v );
GLAPI void GLAPIENTRY _mesa_TexCoord4iv( const GLint *v );
GLAPI void GLAPIENTRY _mesa_TexCoord4sv( const GLshort *v );


GLAPI void GLAPIENTRY _mesa_RasterPos2d( GLdouble x, GLdouble y );
GLAPI void GLAPIENTRY _mesa_RasterPos2f( GLfloat x, GLfloat y );
GLAPI void GLAPIENTRY _mesa_RasterPos2i( GLint x, GLint y );
GLAPI void GLAPIENTRY _mesa_RasterPos2s( GLshort x, GLshort y );

GLAPI void GLAPIENTRY _mesa_RasterPos3d( GLdouble x, GLdouble y, GLdouble z );
GLAPI void GLAPIENTRY _mesa_RasterPos3f( GLfloat x, GLfloat y, GLfloat z );
GLAPI void GLAPIENTRY _mesa_RasterPos3i( GLint x, GLint y, GLint z );
GLAPI void GLAPIENTRY _mesa_RasterPos3s( GLshort x, GLshort y, GLshort z );

GLAPI void GLAPIENTRY _mesa_RasterPos4d( GLdouble x, GLdouble y, GLdouble z, GLdouble w );
GLAPI void GLAPIENTRY _mesa_RasterPos4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w );
GLAPI void GLAPIENTRY _mesa_RasterPos4i( GLint x, GLint y, GLint z, GLint w );
GLAPI void GLAPIENTRY _mesa_RasterPos4s( GLshort x, GLshort y, GLshort z, GLshort w );

GLAPI void GLAPIENTRY _mesa_RasterPos2dv( const GLdouble *v );
GLAPI void GLAPIENTRY _mesa_RasterPos2fv( const GLfloat *v );
GLAPI void GLAPIENTRY _mesa_RasterPos2iv( const GLint *v );
GLAPI void GLAPIENTRY _mesa_RasterPos2sv( const GLshort *v );

GLAPI void GLAPIENTRY _mesa_RasterPos3dv( const GLdouble *v );
GLAPI void GLAPIENTRY _mesa_RasterPos3fv( const GLfloat *v );
GLAPI void GLAPIENTRY _mesa_RasterPos3iv( const GLint *v );
GLAPI void GLAPIENTRY _mesa_RasterPos3sv( const GLshort *v );

GLAPI void GLAPIENTRY _mesa_RasterPos4dv( const GLdouble *v );
GLAPI void GLAPIENTRY _mesa_RasterPos4fv( const GLfloat *v );
GLAPI void GLAPIENTRY _mesa_RasterPos4iv( const GLint *v );
GLAPI void GLAPIENTRY _mesa_RasterPos4sv( const GLshort *v );


GLAPI void GLAPIENTRY _mesa_Rectd( GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2 );
GLAPI void GLAPIENTRY _mesa_Rectf( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 );
GLAPI void GLAPIENTRY _mesa_Recti( GLint x1, GLint y1, GLint x2, GLint y2 );
GLAPI void GLAPIENTRY _mesa_Rects( GLshort x1, GLshort y1, GLshort x2, GLshort y2 );


GLAPI void GLAPIENTRY _mesa_Rectdv( const GLdouble *v1, const GLdouble *v2 );
GLAPI void GLAPIENTRY _mesa_Rectfv( const GLfloat *v1, const GLfloat *v2 );
GLAPI void GLAPIENTRY _mesa_Rectiv( const GLint *v1, const GLint *v2 );
GLAPI void GLAPIENTRY _mesa_Rectsv( const GLshort *v1, const GLshort *v2 );



/*
 * Vertex Arrays  (1.1)
 */

GLAPI void GLAPIENTRY _mesa_VertexPointer( GLint size, GLenum type,
                                       GLsizei stride, const GLvoid *ptr );

GLAPI void GLAPIENTRY _mesa_NormalPointer( GLenum type, GLsizei stride,
                                       const GLvoid *ptr );

GLAPI void GLAPIENTRY _mesa_ColorPointer( GLint size, GLenum type,
                                      GLsizei stride, const GLvoid *ptr );

GLAPI void GLAPIENTRY _mesa_IndexPointer( GLenum type, GLsizei stride,
                                      const GLvoid *ptr );

GLAPI void GLAPIENTRY _mesa_TexCoordPointer( GLint size, GLenum type,
                                         GLsizei stride, const GLvoid *ptr );

GLAPI void GLAPIENTRY _mesa_EdgeFlagPointer( GLsizei stride, const GLvoid *ptr );

GLAPI void GLAPIENTRY _mesa_GetPointerv( GLenum pname, void **params );

GLAPI void GLAPIENTRY _mesa_ArrayElement( GLint i );

GLAPI void GLAPIENTRY _mesa_DrawArrays( GLenum mode, GLint first, GLsizei count );

GLAPI void GLAPIENTRY _mesa_DrawElements( GLenum mode, GLsizei count,
                                      GLenum type, const GLvoid *indices );

GLAPI void GLAPIENTRY _mesa_InterleavedArrays( GLenum format, GLsizei stride,
                                           const GLvoid *pointer );


/*
 * Lighting
 */

GLAPI void GLAPIENTRY _mesa_ShadeModel( GLenum mode );

GLAPI void GLAPIENTRY _mesa_Lightf( GLenum light, GLenum pname, GLfloat param );
GLAPI void GLAPIENTRY _mesa_Lighti( GLenum light, GLenum pname, GLint param );
GLAPI void GLAPIENTRY _mesa_Lightfv( GLenum light, GLenum pname,
                                 const GLfloat *params );
GLAPI void GLAPIENTRY _mesa_Lightiv( GLenum light, GLenum pname,
                                 const GLint *params );

GLAPI void GLAPIENTRY _mesa_GetLightfv( GLenum light, GLenum pname,
                                    GLfloat *params );
GLAPI void GLAPIENTRY _mesa_GetLightiv( GLenum light, GLenum pname,
                                    GLint *params );

GLAPI void GLAPIENTRY _mesa_LightModelf( GLenum pname, GLfloat param );
GLAPI void GLAPIENTRY _mesa_LightModeli( GLenum pname, GLint param );
GLAPI void GLAPIENTRY _mesa_LightModelfv( GLenum pname, const GLfloat *params );
GLAPI void GLAPIENTRY _mesa_LightModeliv( GLenum pname, const GLint *params );

GLAPI void GLAPIENTRY _mesa_Materialf( GLenum face, GLenum pname, GLfloat param );
GLAPI void GLAPIENTRY _mesa_Materiali( GLenum face, GLenum pname, GLint param );
GLAPI void GLAPIENTRY _mesa_Materialfv( GLenum face, GLenum pname, const GLfloat *params );
GLAPI void GLAPIENTRY _mesa_Materialiv( GLenum face, GLenum pname, const GLint *params );

GLAPI void GLAPIENTRY _mesa_GetMaterialfv( GLenum face, GLenum pname, GLfloat *params );
GLAPI void GLAPIENTRY _mesa_GetMaterialiv( GLenum face, GLenum pname, GLint *params );

GLAPI void GLAPIENTRY _mesa_ColorMaterial( GLenum face, GLenum mode );




/*
 * Raster functions
 */

GLAPI void GLAPIENTRY _mesa_PixelZoom( GLfloat xfactor, GLfloat yfactor );

GLAPI void GLAPIENTRY _mesa_PixelStoref( GLenum pname, GLfloat param );
GLAPI void GLAPIENTRY _mesa_PixelStorei( GLenum pname, GLint param );

GLAPI void GLAPIENTRY _mesa_PixelTransferf( GLenum pname, GLfloat param );
GLAPI void GLAPIENTRY _mesa_PixelTransferi( GLenum pname, GLint param );

GLAPI void GLAPIENTRY _mesa_PixelMapfv( GLenum map, GLint mapsize,
                                    const GLfloat *values );
GLAPI void GLAPIENTRY _mesa_PixelMapuiv( GLenum map, GLint mapsize,
                                     const GLuint *values );
GLAPI void GLAPIENTRY _mesa_PixelMapusv( GLenum map, GLint mapsize,
                                     const GLushort *values );

GLAPI void GLAPIENTRY _mesa_GetPixelMapfv( GLenum map, GLfloat *values );
GLAPI void GLAPIENTRY _mesa_GetPixelMapuiv( GLenum map, GLuint *values );
GLAPI void GLAPIENTRY _mesa_GetPixelMapusv( GLenum map, GLushort *values );

GLAPI void GLAPIENTRY _mesa_Bitmap( GLsizei width, GLsizei height,
                                GLfloat xorig, GLfloat yorig,
                                GLfloat xmove, GLfloat ymove,
                                const GLubyte *bitmap );

GLAPI void GLAPIENTRY _mesa_ReadPixels( GLint x, GLint y,
                                    GLsizei width, GLsizei height,
                                    GLenum format, GLenum type,
                                    GLvoid *pixels );

GLAPI void GLAPIENTRY _mesa_DrawPixels( GLsizei width, GLsizei height,
                                    GLenum format, GLenum type,
                                    const GLvoid *pixels );

GLAPI void GLAPIENTRY _mesa_CopyPixels( GLint x, GLint y,
                                    GLsizei width, GLsizei height,
                                    GLenum type );



/*
 * Stenciling
 */

GLAPI void GLAPIENTRY _mesa_StencilFunc( GLenum func, GLint ref, GLuint mask );

GLAPI void GLAPIENTRY _mesa_StencilMask( GLuint mask );

GLAPI void GLAPIENTRY _mesa_StencilOp( GLenum fail, GLenum zfail, GLenum zpass );

GLAPI void GLAPIENTRY _mesa_ClearStencil( GLint s );



/*
 * Texture mapping
 */

GLAPI void GLAPIENTRY _mesa_TexGend( GLenum coord, GLenum pname, GLdouble param );
GLAPI void GLAPIENTRY _mesa_TexGenf( GLenum coord, GLenum pname, GLfloat param );
GLAPI void GLAPIENTRY _mesa_TexGeni( GLenum coord, GLenum pname, GLint param );

GLAPI void GLAPIENTRY _mesa_TexGendv( GLenum coord, GLenum pname, const GLdouble *params );
GLAPI void GLAPIENTRY _mesa_TexGenfv( GLenum coord, GLenum pname, const GLfloat *params );
GLAPI void GLAPIENTRY _mesa_TexGeniv( GLenum coord, GLenum pname, const GLint *params );

GLAPI void GLAPIENTRY _mesa_GetTexGendv( GLenum coord, GLenum pname, GLdouble *params );
GLAPI void GLAPIENTRY _mesa_GetTexGenfv( GLenum coord, GLenum pname, GLfloat *params );
GLAPI void GLAPIENTRY _mesa_GetTexGeniv( GLenum coord, GLenum pname, GLint *params );


GLAPI void GLAPIENTRY _mesa_TexEnvf( GLenum target, GLenum pname, GLfloat param );
GLAPI void GLAPIENTRY _mesa_TexEnvi( GLenum target, GLenum pname, GLint param );

GLAPI void GLAPIENTRY _mesa_TexEnvfv( GLenum target, GLenum pname, const GLfloat *params );
GLAPI void GLAPIENTRY _mesa_TexEnviv( GLenum target, GLenum pname, const GLint *params );

GLAPI void GLAPIENTRY _mesa_GetTexEnvfv( GLenum target, GLenum pname, GLfloat *params );
GLAPI void GLAPIENTRY _mesa_GetTexEnviv( GLenum target, GLenum pname, GLint *params );


GLAPI void GLAPIENTRY _mesa_TexParameterf( GLenum target, GLenum pname, GLfloat param );
GLAPI void GLAPIENTRY _mesa_TexParameteri( GLenum target, GLenum pname, GLint param );

GLAPI void GLAPIENTRY _mesa_TexParameterfv( GLenum target, GLenum pname,
                                          const GLfloat *params );
GLAPI void GLAPIENTRY _mesa_TexParameteriv( GLenum target, GLenum pname,
                                          const GLint *params );

GLAPI void GLAPIENTRY _mesa_GetTexParameterfv( GLenum target,
                                           GLenum pname, GLfloat *params);
GLAPI void GLAPIENTRY _mesa_GetTexParameteriv( GLenum target,
                                           GLenum pname, GLint *params );

GLAPI void GLAPIENTRY _mesa_GetTexLevelParameterfv( GLenum target, GLint level,
                                                GLenum pname, GLfloat *params );
GLAPI void GLAPIENTRY _mesa_GetTexLevelParameteriv( GLenum target, GLint level,
                                                GLenum pname, GLint *params );


GLAPI void GLAPIENTRY _mesa_TexImage1D( GLenum target, GLint level,
                                    GLint internalFormat,
                                    GLsizei width, GLint border,
                                    GLenum format, GLenum type,
                                    const GLvoid *pixels );

GLAPI void GLAPIENTRY _mesa_TexImage2D( GLenum target, GLint level,
                                    GLint internalFormat,
                                    GLsizei width, GLsizei height,
                                    GLint border, GLenum format, GLenum type,
                                    const GLvoid *pixels );

GLAPI void GLAPIENTRY _mesa_GetTexImage( GLenum target, GLint level,
                                     GLenum format, GLenum type,
                                     GLvoid *pixels );



/* 1.1 functions */

GLAPI void GLAPIENTRY _mesa_GenTextures( GLsizei n, GLuint *textures );

GLAPI void GLAPIENTRY _mesa_DeleteTextures( GLsizei n, const GLuint *textures);

GLAPI void GLAPIENTRY _mesa_BindTexture( GLenum target, GLuint texture );

GLAPI void GLAPIENTRY _mesa_PrioritizeTextures( GLsizei n,
                                            const GLuint *textures,
                                            const GLclampf *priorities );

GLAPI GLboolean GLAPIENTRY _mesa_AreTexturesResident( GLsizei n,
                                                  const GLuint *textures,
                                                  GLboolean *residences );

GLAPI GLboolean GLAPIENTRY _mesa_IsTexture( GLuint texture );


GLAPI void GLAPIENTRY _mesa_TexSubImage1D( GLenum target, GLint level,
                                       GLint xoffset,
                                       GLsizei width, GLenum format,
                                       GLenum type, const GLvoid *pixels );


GLAPI void GLAPIENTRY _mesa_TexSubImage2D( GLenum target, GLint level,
                                       GLint xoffset, GLint yoffset,
                                       GLsizei width, GLsizei height,
                                       GLenum format, GLenum type,
                                       const GLvoid *pixels );


GLAPI void GLAPIENTRY _mesa_CopyTexImage1D( GLenum target, GLint level,
                                        GLenum internalformat,
                                        GLint x, GLint y,
                                        GLsizei width, GLint border );


GLAPI void GLAPIENTRY _mesa_CopyTexImage2D( GLenum target, GLint level,
                                        GLenum internalformat,
                                        GLint x, GLint y,
                                        GLsizei width, GLsizei height,
                                        GLint border );


GLAPI void GLAPIENTRY _mesa_CopyTexSubImage1D( GLenum target, GLint level,
                                           GLint xoffset, GLint x, GLint y,
                                           GLsizei width );


GLAPI void GLAPIENTRY _mesa_CopyTexSubImage2D( GLenum target, GLint level,
                                           GLint xoffset, GLint yoffset,
                                           GLint x, GLint y,
                                           GLsizei width, GLsizei height );




/*
 * Evaluators
 */

GLAPI void GLAPIENTRY _mesa_Map1d( GLenum target, GLdouble u1, GLdouble u2,
                               GLint stride,
                               GLint order, const GLdouble *points );
GLAPI void GLAPIENTRY _mesa_Map1f( GLenum target, GLfloat u1, GLfloat u2,
                               GLint stride,
                               GLint order, const GLfloat *points );

GLAPI void GLAPIENTRY _mesa_Map2d( GLenum target,
		     GLdouble u1, GLdouble u2, GLint ustride, GLint uorder,
		     GLdouble v1, GLdouble v2, GLint vstride, GLint vorder,
		     const GLdouble *points );
GLAPI void GLAPIENTRY _mesa_Map2f( GLenum target,
		     GLfloat u1, GLfloat u2, GLint ustride, GLint uorder,
		     GLfloat v1, GLfloat v2, GLint vstride, GLint vorder,
		     const GLfloat *points );

GLAPI void GLAPIENTRY _mesa_GetMapdv( GLenum target, GLenum query, GLdouble *v );
GLAPI void GLAPIENTRY _mesa_GetMapfv( GLenum target, GLenum query, GLfloat *v );
GLAPI void GLAPIENTRY _mesa_GetMapiv( GLenum target, GLenum query, GLint *v );

GLAPI void GLAPIENTRY _mesa_EvalCoord1d( GLdouble u );
GLAPI void GLAPIENTRY _mesa_EvalCoord1f( GLfloat u );

GLAPI void GLAPIENTRY _mesa_EvalCoord1dv( const GLdouble *u );
GLAPI void GLAPIENTRY _mesa_EvalCoord1fv( const GLfloat *u );

GLAPI void GLAPIENTRY _mesa_EvalCoord2d( GLdouble u, GLdouble v );
GLAPI void GLAPIENTRY _mesa_EvalCoord2f( GLfloat u, GLfloat v );

GLAPI void GLAPIENTRY _mesa_EvalCoord2dv( const GLdouble *u );
GLAPI void GLAPIENTRY _mesa_EvalCoord2fv( const GLfloat *u );

GLAPI void GLAPIENTRY _mesa_MapGrid1d( GLint un, GLdouble u1, GLdouble u2 );
GLAPI void GLAPIENTRY _mesa_MapGrid1f( GLint un, GLfloat u1, GLfloat u2 );

GLAPI void GLAPIENTRY _mesa_MapGrid2d( GLint un, GLdouble u1, GLdouble u2,
                                   GLint vn, GLdouble v1, GLdouble v2 );
GLAPI void GLAPIENTRY _mesa_MapGrid2f( GLint un, GLfloat u1, GLfloat u2,
                                   GLint vn, GLfloat v1, GLfloat v2 );

GLAPI void GLAPIENTRY _mesa_EvalPoint1( GLint i );

GLAPI void GLAPIENTRY _mesa_EvalPoint2( GLint i, GLint j );

GLAPI void GLAPIENTRY _mesa_EvalMesh1( GLenum mode, GLint i1, GLint i2 );

GLAPI void GLAPIENTRY _mesa_EvalMesh2( GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2 );



/*
 * Fog
 */

GLAPI void GLAPIENTRY _mesa_Fogf( GLenum pname, GLfloat param );

GLAPI void GLAPIENTRY _mesa_Fogi( GLenum pname, GLint param );

GLAPI void GLAPIENTRY _mesa_Fogfv( GLenum pname, const GLfloat *params );

GLAPI void GLAPIENTRY _mesa_Fogiv( GLenum pname, const GLint *params );



/*
 * Selection and Feedback
 */

GLAPI void GLAPIENTRY _mesa_FeedbackBuffer( GLsizei size, GLenum type, GLfloat *buffer );

GLAPI void GLAPIENTRY _mesa_PassThrough( GLfloat token );

GLAPI void GLAPIENTRY _mesa_SelectBuffer( GLsizei size, GLuint *buffer );

GLAPI void GLAPIENTRY _mesa_InitNames( void );

GLAPI void GLAPIENTRY _mesa_LoadName( GLuint name );

GLAPI void GLAPIENTRY _mesa_PushName( GLuint name );

GLAPI void GLAPIENTRY _mesa_PopName( void );



/* 1.2 functions */
GLAPI void GLAPIENTRY _mesa_DrawRangeElements( GLenum mode, GLuint start,
	GLuint end, GLsizei count, GLenum type, const GLvoid *indices );

GLAPI void GLAPIENTRY _mesa_TexImage3D( GLenum target, GLint level,
                                      GLint internalFormat,
                                      GLsizei width, GLsizei height,
                                      GLsizei depth, GLint border,
                                      GLenum format, GLenum type,
                                      const GLvoid *pixels );

GLAPI void GLAPIENTRY _mesa_TexSubImage3D( GLenum target, GLint level,
                                         GLint xoffset, GLint yoffset,
                                         GLint zoffset, GLsizei width,
                                         GLsizei height, GLsizei depth,
                                         GLenum format,
                                         GLenum type, const GLvoid *pixels);

GLAPI void GLAPIENTRY _mesa_CopyTexSubImage3D( GLenum target, GLint level,
                                             GLint xoffset, GLint yoffset,
                                             GLint zoffset, GLint x,
                                             GLint y, GLsizei width,
                                             GLsizei height );


/* 1.2 imaging extension functions */

GLAPI void GLAPIENTRY _mesa_ColorTable( GLenum target, GLenum internalformat,
                                    GLsizei width, GLenum format,
                                    GLenum type, const GLvoid *table );

GLAPI void GLAPIENTRY _mesa_ColorSubTable( GLenum target,
                                       GLsizei start, GLsizei count,
                                       GLenum format, GLenum type,
                                       const GLvoid *data );

GLAPI void GLAPIENTRY _mesa_ColorTableParameteriv(GLenum target, GLenum pname,
                                              const GLint *params);

GLAPI void GLAPIENTRY _mesa_ColorTableParameterfv(GLenum target, GLenum pname,
                                              const GLfloat *params);

GLAPI void GLAPIENTRY _mesa_CopyColorSubTable( GLenum target, GLsizei start,
                                           GLint x, GLint y, GLsizei width );

GLAPI void GLAPIENTRY _mesa_CopyColorTable( GLenum target, GLenum internalformat,
                                        GLint x, GLint y, GLsizei width );

GLAPI void GLAPIENTRY _mesa_GetColorTable( GLenum target, GLenum format,
                                       GLenum type, GLvoid *table );

GLAPI void GLAPIENTRY _mesa_GetColorTableParameterfv( GLenum target, GLenum pname,
                                                  GLfloat *params );

GLAPI void GLAPIENTRY _mesa_GetColorTableParameteriv( GLenum target, GLenum pname,
                                                  GLint *params );

GLAPI void GLAPIENTRY _mesa_BlendEquation( GLenum mode );

GLAPI void GLAPIENTRY _mesa_BlendColor( GLclampf red, GLclampf green,
                                    GLclampf blue, GLclampf alpha );

GLAPI void GLAPIENTRY _mesa_Histogram( GLenum target, GLsizei width,
				   GLenum internalformat, GLboolean sink );

GLAPI void GLAPIENTRY _mesa_ResetHistogram( GLenum target );

GLAPI void GLAPIENTRY _mesa_GetHistogram( GLenum target, GLboolean reset,
				      GLenum format, GLenum type,
				      GLvoid *values );

GLAPI void GLAPIENTRY _mesa_GetHistogramParameterfv( GLenum target, GLenum pname,
						 GLfloat *params );

GLAPI void GLAPIENTRY _mesa_GetHistogramParameteriv( GLenum target, GLenum pname,
						 GLint *params );

GLAPI void GLAPIENTRY _mesa_Minmax( GLenum target, GLenum internalformat,
				GLboolean sink );

GLAPI void GLAPIENTRY _mesa_ResetMinmax( GLenum target );

GLAPI void GLAPIENTRY _mesa_GetMinmax( GLenum target, GLboolean reset,
                                   GLenum format, GLenum types,
                                   GLvoid *values );

GLAPI void GLAPIENTRY _mesa_GetMinmaxParameterfv( GLenum target, GLenum pname,
					      GLfloat *params );

GLAPI void GLAPIENTRY _mesa_GetMinmaxParameteriv( GLenum target, GLenum pname,
					      GLint *params );

GLAPI void GLAPIENTRY _mesa_ConvolutionFilter1D( GLenum target,
	GLenum internalformat, GLsizei width, GLenum format, GLenum type,
	const GLvoid *image );

GLAPI void GLAPIENTRY _mesa_ConvolutionFilter2D( GLenum target,
	GLenum internalformat, GLsizei width, GLsizei height, GLenum format,
	GLenum type, const GLvoid *image );

GLAPI void GLAPIENTRY _mesa_ConvolutionParameterf( GLenum target, GLenum pname,
	GLfloat params );

GLAPI void GLAPIENTRY _mesa_ConvolutionParameterfv( GLenum target, GLenum pname,
	const GLfloat *params );

GLAPI void GLAPIENTRY _mesa_ConvolutionParameteri( GLenum target, GLenum pname,
	GLint params );

GLAPI void GLAPIENTRY _mesa_ConvolutionParameteriv( GLenum target, GLenum pname,
	const GLint *params );

GLAPI void GLAPIENTRY _mesa_CopyConvolutionFilter1D( GLenum target,
	GLenum internalformat, GLint x, GLint y, GLsizei width );

GLAPI void GLAPIENTRY _mesa_CopyConvolutionFilter2D( GLenum target,
	GLenum internalformat, GLint x, GLint y, GLsizei width,
	GLsizei height);

GLAPI void GLAPIENTRY _mesa_GetConvolutionFilter( GLenum target, GLenum format,
	GLenum type, GLvoid *image );

GLAPI void GLAPIENTRY _mesa_GetConvolutionParameterfv( GLenum target, GLenum pname,
	GLfloat *params );

GLAPI void GLAPIENTRY _mesa_GetConvolutionParameteriv( GLenum target, GLenum pname,
	GLint *params );

GLAPI void GLAPIENTRY _mesa_SeparableFilter2D( GLenum target,
	GLenum internalformat, GLsizei width, GLsizei height, GLenum format,
	GLenum type, const GLvoid *row, const GLvoid *column );

GLAPI void GLAPIENTRY _mesa_GetSeparableFilter( GLenum target, GLenum format,
	GLenum type, GLvoid *row, GLvoid *column, GLvoid *span );


GLAPI void GLAPIENTRY _mesa_ActiveTextureARB(GLenum texture);
GLAPI void GLAPIENTRY _mesa_ClientActiveTextureARB(GLenum texture);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord1dARB(GLenum target, GLdouble s);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord1dvARB(GLenum target, const GLdouble *v);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord1fARB(GLenum target, GLfloat s);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord1fvARB(GLenum target, const GLfloat *v);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord1iARB(GLenum target, GLint s);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord1ivARB(GLenum target, const GLint *v);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord1sARB(GLenum target, GLshort s);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord1svARB(GLenum target, const GLshort *v);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord2dARB(GLenum target, GLdouble s, GLdouble t);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord2dvARB(GLenum target, const GLdouble *v);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord2fARB(GLenum target, GLfloat s, GLfloat t);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord2fvARB(GLenum target, const GLfloat *v);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord2iARB(GLenum target, GLint s, GLint t);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord2ivARB(GLenum target, const GLint *v);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord2sARB(GLenum target, GLshort s, GLshort t);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord2svARB(GLenum target, const GLshort *v);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord3dARB(GLenum target, GLdouble s, GLdouble t, GLdouble r);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord3dvARB(GLenum target, const GLdouble *v);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord3fARB(GLenum target, GLfloat s, GLfloat t, GLfloat r);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord3fvARB(GLenum target, const GLfloat *v);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord3iARB(GLenum target, GLint s, GLint t, GLint r);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord3ivARB(GLenum target, const GLint *v);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord3sARB(GLenum target, GLshort s, GLshort t, GLshort r);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord3svARB(GLenum target, const GLshort *v);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord4dARB(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord4dvARB(GLenum target, const GLdouble *v);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord4fARB(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord4fvARB(GLenum target, const GLfloat *v);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord4iARB(GLenum target, GLint s, GLint t, GLint r, GLint q);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord4ivARB(GLenum target, const GLint *v);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord4sARB(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
GLAPI void GLAPIENTRY _mesa_MultiTexCoord4svARB(GLenum target, const GLshort *v);

GLAPI void GLAPIENTRY _mesa_BlendColorEXT( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha );

GLAPI void GLAPIENTRY _mesa_PolygonOffsetEXT( GLfloat factor, GLfloat bias );

GLAPI void GLAPIENTRY _mesa_TexImage3DEXT( GLenum target, GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels );

GLAPI void GLAPIENTRY _mesa_TexSubImage3DEXT( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);

GLAPI void GLAPIENTRY _mesa_CopyTexSubImage3DEXT( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height );

GLAPI void GLAPIENTRY _mesa_GenTexturesEXT( GLsizei n, GLuint *textures );

GLAPI void GLAPIENTRY _mesa_DeleteTexturesEXT( GLsizei n, const GLuint *textures);

GLAPI void GLAPIENTRY _mesa_BindTextureEXT( GLenum target, GLuint texture );

GLAPI void GLAPIENTRY _mesa_PrioritizeTexturesEXT( GLsizei n, const GLuint *textures, const GLclampf *priorities );

GLAPI GLboolean GLAPIENTRY _mesa_AreTexturesResidentEXT( GLsizei n, const GLuint *textures, GLboolean *residences );

GLAPI GLboolean GLAPIENTRY _mesa_IsTextureEXT( GLuint texture );

GLAPI void GLAPIENTRY _mesa_VertexPointerEXT( GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *ptr );

GLAPI void GLAPIENTRY _mesa_NormalPointerEXT( GLenum type, GLsizei stride, GLsizei count, const GLvoid *ptr );

GLAPI void GLAPIENTRY _mesa_ColorPointerEXT( GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *ptr );

GLAPI void GLAPIENTRY _mesa_IndexPointerEXT( GLenum type, GLsizei stride, GLsizei count, const GLvoid *ptr );

GLAPI void GLAPIENTRY _mesa_TexCoordPointerEXT( GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *ptr );

GLAPI void GLAPIENTRY _mesa_EdgeFlagPointerEXT( GLsizei stride, GLsizei count, const GLboolean *ptr );

GLAPI void GLAPIENTRY _mesa_GetPointervEXT( GLenum pname, void **params );

GLAPI void GLAPIENTRY _mesa_ArrayElementEXT( GLint i );

GLAPI void GLAPIENTRY _mesa_DrawArraysEXT( GLenum mode, GLint first, GLsizei count );

GLAPI void GLAPIENTRY _mesa_BlendEquationEXT( GLenum mode );

GLAPI void GLAPIENTRY _mesa_PointParameterfEXT( GLenum pname, GLfloat param );
GLAPI void GLAPIENTRY _mesa_PointParameterfvEXT( GLenum pname, const GLfloat *params );
GLAPI void GLAPIENTRY _mesa_PointParameterfSGIS(GLenum pname, GLfloat param);
GLAPI void GLAPIENTRY _mesa_PointParameterfvSGIS(GLenum pname, const GLfloat *params);

GLAPI void GLAPIENTRY _mesa_ColorTableEXT( GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table );

GLAPI void GLAPIENTRY _mesa_ColorSubTableEXT( GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data );

GLAPI void GLAPIENTRY _mesa_GetColorTableEXT( GLenum target, GLenum format, GLenum type, GLvoid *table );

GLAPI void GLAPIENTRY _mesa_GetColorTableParameterfvEXT( GLenum target, GLenum pname, GLfloat *params );

GLAPI void GLAPIENTRY _mesa_GetColorTableParameterivEXT( GLenum target, GLenum pname, GLint *params );

GLAPI void GLAPIENTRY _mesa_LockArraysEXT( GLint first, GLsizei count );
GLAPI void GLAPIENTRY _mesa_UnlockArraysEXT( void );

GLAPI void GLAPIENTRY _mesa_WindowPos2iMESA( GLint x, GLint y );
GLAPI void GLAPIENTRY _mesa_WindowPos2sMESA( GLshort x, GLshort y );
GLAPI void GLAPIENTRY _mesa_WindowPos2fMESA( GLfloat x, GLfloat y );
GLAPI void GLAPIENTRY _mesa_WindowPos2dMESA( GLdouble x, GLdouble y );
GLAPI void GLAPIENTRY _mesa_WindowPos2ivMESA( const GLint *p );
GLAPI void GLAPIENTRY _mesa_WindowPos2svMESA( const GLshort *p );
GLAPI void GLAPIENTRY _mesa_WindowPos2fvMESA( const GLfloat *p );
GLAPI void GLAPIENTRY _mesa_WindowPos2dvMESA( const GLdouble *p );
GLAPI void GLAPIENTRY _mesa_WindowPos3iMESA( GLint x, GLint y, GLint z );
GLAPI void GLAPIENTRY _mesa_WindowPos3sMESA( GLshort x, GLshort y, GLshort z );
GLAPI void GLAPIENTRY _mesa_WindowPos3fMESA( GLfloat x, GLfloat y, GLfloat z );
GLAPI void GLAPIENTRY _mesa_WindowPos3dMESA( GLdouble x, GLdouble y, GLdouble z );
GLAPI void GLAPIENTRY _mesa_WindowPos3ivMESA( const GLint *p );
GLAPI void GLAPIENTRY _mesa_WindowPos3svMESA( const GLshort *p );
GLAPI void GLAPIENTRY _mesa_WindowPos3fvMESA( const GLfloat *p );
GLAPI void GLAPIENTRY _mesa_WindowPos3dvMESA( const GLdouble *p );
GLAPI void GLAPIENTRY _mesa_WindowPos4iMESA( GLint x, GLint y, GLint z, GLint w );
GLAPI void GLAPIENTRY _mesa_WindowPos4sMESA( GLshort x, GLshort y, GLshort z, GLshort w );
GLAPI void GLAPIENTRY _mesa_WindowPos4fMESA( GLfloat x, GLfloat y, GLfloat z, GLfloat w );
GLAPI void GLAPIENTRY _mesa_WindowPos4dMESA( GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLAPI void GLAPIENTRY _mesa_WindowPos4ivMESA( const GLint *p );
GLAPI void GLAPIENTRY _mesa_WindowPos4svMESA( const GLshort *p );
GLAPI void GLAPIENTRY _mesa_WindowPos4fvMESA( const GLfloat *p );
GLAPI void GLAPIENTRY _mesa_WindowPos4dvMESA( const GLdouble *p );

GLAPI void GLAPIENTRY _mesa_ResizeBuffersMESA( void );



























//* all declarations go here

/*
 * Miscellaneous
 */

#define glClearIndex _mesa_ClearIndex
#define glClearColor _mesa_ClearColor
#define glClear _mesa_Clear
#define glIndexMask _mesa_IndexMask
#define glColorMask _mesa_ColorMask
#define glAlphaFunc _mesa_AlphaFunc
#define glBlendFunc _mesa_BlendFunc
#define glLogicOp _mesa_LogicOp
#define glCullFace _mesa_CullFace
#define glFrontFace _mesa_FrontFace
#define glPointSize _mesa_PointSize
#define glLineWidth _mesa_LineWidth
#define glLineStipple _mesa_LineStipple
#define glPolygonMode _mesa_PolygonMode
#define glPolygonOffset _mesa_PolygonOffset
#define glPolygonStipple _mesa_PolygonStipple
#define glGetPolygonStipple _mesa_GetPolygonStipple
#define glEdgeFlag _mesa_EdgeFlag
#define glEdgeFlagv _mesa_EdgeFlagv
#define glScissor _mesa_Scissor
#define glClipPlane _mesa_ClipPlane
#define glGetClipPlane _mesa_GetClipPlane
#define glDrawBuffer _mesa_DrawBuffer
#define glReadBuffer _mesa_ReadBuffer
#define glEnable _mesa_Enable
#define glDisable _mesa_Disable
#define glIsEnabled _mesa_IsEnabled
#define glEnableClientState _mesa_EnableClientState
#define glDisableClientState _mesa_DisableClientState
#define glGetBooleanv _mesa_GetBooleanv
#define glGetDoublev _mesa_GetDoublev
#define glGetFloatv _mesa_GetFloatv
#define glGetIntegerv _mesa_GetIntegerv
#define glPushAttrib _mesa_PushAttrib
#define glPopAttrib _mesa_PopAttrib
#define glPushClientAttrib _mesa_PushClientAttrib
#define glPopClientAttrib _mesa_PopClientAttrib
#define glRenderMode _mesa_RenderMode
#define glGetError _mesa_GetError
#define glGetString _mesa_GetString
#define glFinish _mesa_Finish
#define glFlush _mesa_Flush
#define glHint _mesa_Hint

/*
 * Depth Buffer
 */

#define glClearDepth _mesa_ClearDepth
#define glDepthFunc _mesa_DepthFunc
#define glDepthMask _mesa_DepthMask
#define glDepthRange _mesa_DepthRange

/*
 * Accumulation Buffer
 */

#define glClearAccum _mesa_ClearAccum
#define glAccum _mesa_Accum

/*
 * Transformation
 */

#define glMatrixMode _mesa_MatrixMode
#define glOrtho _mesa_Ortho
#define glFrustum _mesa_Frustum
#define glViewport _mesa_Viewport
#define glPushMatrix _mesa_PushMatrix
#define glPopMatrix _mesa_PopMatrix
#define glLoadIdentity _mesa_LoadIdentity
#define glLoadMatrixd _mesa_LoadMatrixd
#define glLoadMatrixf _mesa_LoadMatrixf
#define glMultMatrixd _mesa_MultMatrixd
#define glMultMatrixf _mesa_MultMatrixf
#define glRotated _mesa_Rotated
#define glRotatef _mesa_Rotatef
#define glScaled _mesa_Scaled
#define glScalef _mesa_Scalef
#define glTranslated _mesa_Translated
#define glTranslatef _mesa_Translatef

/*
 * Display Lists
 */

#define glIsList _mesa_IsList
#define glDeleteLists _mesa_DeleteLists
#define glGenLists _mesa_GenLists
#define glNewList _mesa_NewList
#define glEndList _mesa_EndList
#define glCallList _mesa_CallList
#define glCallLists _mesa_CallLists
#define glListBase _mesa_ListBase

/*
 * Drawing Functions
 */

#define glBegin _mesa_Begin
#define glEnd _mesa_End

#define glVertex2d _mesa_Vertex2d
#define glVertex2f _mesa_Vertex2f
#define glVertex2i _mesa_Vertex2i
#define glVertex2s _mesa_Vertex2s
#define glVertex3d _mesa_Vertex3d
#define glVertex3f _mesa_Vertex3f
#define glVertex3i _mesa_Vertex3i
#define glVertex3s _mesa_Vertex3s
#define glVertex4d _mesa_Vertex4d
#define glVertex4f _mesa_Vertex4f
#define glVertex4i _mesa_Vertex4i
#define glVertex4s _mesa_Vertex4s
#define glVertex2dv _mesa_Vertex2dv
#define glVertex2fv _mesa_Vertex2fv
#define glVertex2iv _mesa_Vertex2iv
#define glVertex2sv _mesa_Vertex2sv

#define glVertex3dv _mesa_Vertex3dv
#define glVertex3fv _mesa_Vertex3fv
#define glVertex3iv _mesa_Vertex3iv
#define glVertex3sv _mesa_Vertex3sv

#define glVertex4dv _mesa_Vertex4dv
#define glVertex4fv _mesa_Vertex4fv
#define glVertex4iv _mesa_Vertex4iv
#define glVertex4sv _mesa_Vertex4sv

#define glNormal3b _mesa_Normal3b
#define glNormal3d _mesa_Normal3d
#define glNormal3f _mesa_Normal3f
#define glNormal3i _mesa_Normal3i
#define glNormal3s _mesa_Normal3s

#define glNormal3bv _mesa_Normal3bv
#define glNormal3dv _mesa_Normal3dv
#define glNormal3fv _mesa_Normal3fv
#define glNormal3iv _mesa_Normal3iv
#define glNormal3sv _mesa_Normal3sv

#define glIndexd _mesa_Indexd
#define glIndexf _mesa_Indexf
#define glIndexi _mesa_Indexi
#define glIndexs _mesa_Indexs
#define glIndexub _mesa_Indexub

#define glIndexdv _mesa_Indexdv
#define glIndexfv _mesa_Indexfv
#define glIndexiv _mesa_Indexiv
#define glIndexsv _mesa_Indexsv
#define glIndexubv _mesa_Indexubv

#define glColor3b _mesa_Color3b
#define glColor3d _mesa_Color3d
#define glColor3f _mesa_Color3f
#define glColor3i _mesa_Color3i
#define glColor3s _mesa_Color3s
#define glColor3ub _mesa_Color3ub
#define glColor3ui _mesa_Color3ui
#define glColor3us _mesa_Color3us

#define glColor4b _mesa_Color4b
#define glColor4f _mesa_Color4f
#define glColor4i _mesa_Color4i
#define glColor4s _mesa_Color4s
#define glColor4ub _mesa_Color4ub
#define glColor4ui _mesa_Color4ui
#define glColor4us _mesa_Color4us

#define glColor3bv _mesa_Color3bv
#define glColor3dv _mesa_Color3dv
#define glColor3fv _mesa_Color3fv
#define glColor3iv _mesa_Color3iv
#define glColor3sv _mesa_Color3sv
#define glColor3ubv _mesa_Color3ubv
#define glColor3uiv _mesa_Color3uiv
#define glColor3usv _mesa_Color3usv

#define glColor4bv _mesa_Color4bv
#define glColor4dv _mesa_Color4dv
#define glColor4fv _mesa_Color4fv
#define glColor4iv _mesa_Color4iv
#define glColor4sv _mesa_Color4sv
#define glColor4ubv _mesa_Color4ubv
#define glColor4uiv _mesa_Color4uiv
#define glColor4usv _mesa_Color4usv

#define glTexCoord1d _mesa_TexCoord1d
#define glTexCoord1f _mesa_TexCoord1f
#define glTexCoord1i _mesa_TexCoord1i
#define glTexCoord1s _mesa_TexCoord1s

#define glTexCoord2d _mesa_TexCoord2d
#define glTexCoord2f _mesa_TexCoord2f
#define glTexCoord2i _mesa_TexCoord2i
#define glTexCoord2s _mesa_TexCoord2s

#define glTexCoord3d _mesa_TexCoord3d
#define glTexCoord3f _mesa_TexCoord3f
#define glTexCoord3i _mesa_TexCoord3i
#define glTexCoord3s _mesa_TexCoord3s

#define glTexCoord4d _mesa_TexCoord4d
#define glTexCoord4f _mesa_TexCoord4f
#define glTexCoord4i _mesa_TexCoord4i
#define glTexCoord4s _mesa_TexCoord4s

#define glTexCoord1dv _mesa_TexCoord1dv
#define glTexCoord1fv _mesa_TexCoord1fv
#define glTexCoord1iv _mesa_TexCoord1iv
#define glTexCoord1sv _mesa_TexCoord1sv

#define glTexCoord2dv _mesa_TexCoord2dv
#define glTexCoord2fv _mesa_TexCoord2fv
#define glTexCoord2iv _mesa_TexCoord2iv
#define glTexCoord2sv _mesa_TexCoord2sv

#define glTexCoord3dv _mesa_TexCoord3dv
#define glTexCoord3fv _mesa_TexCoord3fv
#define glTexCoord3iv _mesa_TexCoord3iv
#define glTexCoord3sv _mesa_TexCoord3sv

#define glTexCoord4dv _mesa_TexCoord4dv
#define glTexCoord4fv _mesa_TexCoord4fv
#define glTexCoord4iv _mesa_TexCoord4iv
#define glTexCoord4sv _mesa_TexCoord4sv

#define glRasterPos2d _mesa_RasterPos2d
#define glRasterPos2f _mesa_RasterPos2f
#define glRasterPos2i _mesa_RasterPos2i
#define glRasterPos2s _mesa_RasterPos2s

#define glRasterPos3d _mesa_RasterPos3d
#define glRasterPos3f _mesa_RasterPos3f
#define glRasterPos3i _mesa_RasterPos3i
#define glRasterPos3s _mesa_RasterPos3s

#define glRasterPos4d _mesa_RasterPos4d
#define glRasterPos4f _mesa_RasterPos4f
#define glRasterPos4i _mesa_RasterPos4i
#define glRasterPos4s _mesa_RasterPos4s

#define glRasterPos2dv _mesa_RasterPos2dv
#define glRasterPos2fv _mesa_RasterPos2fv
#define glRasterPos2iv _mesa_RasterPos2iv
#define glRasterPos2sv _mesa_RasterPos2sv

#define glRasterPos3dv _mesa_RasterPos3dv
#define glRasterPos3fv _mesa_RasterPos3fv
#define glRasterPos3iv _mesa_RasterPos3iv
#define glRasterPos3sv _mesa_RasterPos3sv

#define glRasterPos4dv _mesa_RasterPos4dv
#define glRasterPos4fv _mesa_RasterPos4fv
#define glRasterPos4iv _mesa_RasterPos4iv
#define glRasterPos4sv _mesa_RasterPos4sv

#define glRectd _mesa_Rectd
#define glRectf _mesa_Rectf
#define glRecti _mesa_Recti
#define glRects _mesa_Rects

#define glRectdv _mesa_Rectdv
#define glRectfv _mesa_Rectfv
#define glRectiv _mesa_Rectiv
#define glRectsv _mesa_Rectsv

/*
 * Vertex Arrays  (1.1)
 */

#define glVertexPointer _mesa_VertexPointer
#define glNormalPointer _mesa_NormalPointer
#define glColorPointer _mesa_ColorPointer
#define glIndexPointer _mesa_IndexPointer
#define glTexCoordPointer _mesa_TexCoordPointer
#define glEdgeFlagPointer _mesa_EdgeFlagPointer

#define glGetPointerv _mesa_GetPointerv
#define glArrayElement _mesa_ArrayElement
#define glDrawArrays _mesa_DrawArrays

#define glDrawElements _mesa_DrawElements
#define glInterleavedArrays _mesa_InterleavedArrays

/*
 * Lighting
 */

#define glShadeModel _mesa_ShadeModel
#define glLightf _mesa_Lightf
#define glLighti _mesa_Lighti
#define glLightfv _mesa_Lightfv
#define glLightiv _mesa_Lightiv
#define glGetLightfv _mesa_GetLightfv
#define glGetLightiv _mesa_GetLightiv

#define glLightModelf _mesa_LightModelf
#define glLightModeli _mesa_LightModeli
#define glLightModelfv _mesa_LightModelfv
#define glLightModeliv _mesa_LightModeliv

#define glMaterialf _mesa_Materialf
#define glMateriali _mesa_Materiali
#define glMaterialfv _mesa_Materialfv
#define glMaterialiv _mesa_Materialiv

#define glGetMaterialfv _mesa_GetMaterialfv
#define glGetMaterialiv _mesa_GetMaterialiv

#define glColorMaterial _mesa_ColorMaterial

/*
 * Raster functions
 */

#define glPixelZoom _mesa_PixelZoom
#define glPixelStoref _mesa_PixelStoref
#define glPixelStorei _mesa_PixelStorei
#define glPixelTransferf _mesa_PixelTransferf
#define glPixelTransferi _mesa_PixelTransferi

#define glPixelMapfv _mesa_PixelMapfv
#define glPixelMapuiv _mesa_PixelMapuiv
#define glPixelMapusv _mesa_PixelMapusv
#define glGetPixelMapfv _mesa_GetPixelMapfv
#define glGetPixelMapuiv _mesa_GetPixelMapuiv
#define glGetPixelMapusv _mesa_GetPixelMapusv
#define glBitmap _mesa_Bitmap
#define glReadPixels _mesa_ReadPixels
#define glDrawPixels _mesa_DrawPixels
#define glCopyPixels _mesa_CopyPixels

/*
 * Stenciling
 */

#define glStencilFunc _mesa_StencilFunc
#define glStencilMask _mesa_StencilMask
#define glStencilOp _mesa_StencilOp
#define glClearStencil _mesa_ClearStencil

/*
 * Texture mapping
 */

#define glTexGend _mesa_TexGend
#define glTexGenf _mesa_TexGenf
#define glTexGeni _mesa_TexGeni

#define glTexGendv _mesa_TexGendv
#define glTexGenfv _mesa_TexGenfv
#define glTexGeniv _mesa_TexGeniv

#define glGetTexGendv _mesa_GetTexGendv
#define glGetTexGenfv _mesa_GetTexGenfv
#define glGetTexGeniv _mesa_GetTexGeniv

#define glTexEnvf _mesa_TexEnvf
#define glTexEnvi _mesa_TexEnvi

#define glTexEnvfv _mesa_TexEnvfv
#define glTexEnviv _mesa_TexEnviv

#define glGetTexEnvfv _mesa_GetTexEnvfv
#define glGetTexEnviv _mesa_GetTexEnviv

#define glTexParameterf _mesa_TexParameterf
#define glTexParameteri _mesa_TexParameteri

#define glTexParameterfv _mesa_TexParameterfv
#define glTexParameteriv _mesa_TexParameteriv

#define glGetTexParameterfv _mesa_GetTexParameterfv
#define glGetTexParameteriv _mesa_GetTexParameteriv
#define glGetTexLevelParameterfv _mesa_GetTexLevelParameterfv
#define glGetTexLevelParameteriv _mesa_GetTexLevelParameteriv

#define glTexImage1D _mesa_TexImage1D
#define glTexImage2D _mesa_TexImage2D
#define glGetTexImage _mesa_GetTexImage

/* 1.1 functions */

#define glGenTextures _mesa_GenTextures
#define glDeleteTextures _mesa_DeleteTextures
#define glBindTexture _mesa_BindTexture
#define glPrioritizeTextures _mesa_PrioritizeTextures
#define glAreTexturesResident _mesa_AreTexturesResident
#define glIsTexture _mesa_IsTexture
#define glTexSubImage1D _mesa_TexSubImage1D
#define glTexSubImage2D _mesa_TexSubImage2D
#define glCopyTexImage1D _mesa_CopyTexImage1D
#define glCopyTexImage2D _mesa_CopyTexImage2D
#define glCopyTexSubImage1D _mesa_CopyTexSubImage1D
#define glCopyTexSubImage2D _mesa_CopyTexSubImage2D

/*
 * Evaluators
 */

#define glMap1d _mesa_Map1d
#define glMap1f _mesa_Map1f
#define glMap2d _mesa_Map2d
#define glMap2f _mesa_Map2f
#define glGetMapdv _mesa_GetMapdv
#define glGetMapfv _mesa_GetMapfv
#define glGetMapiv _mesa_GetMapiv
#define glEvalCoord1d _mesa_EvalCoord1d
#define glEvalCoord1f _mesa_EvalCoord1f
#define glEvalCoord1dv _mesa_EvalCoord1dv
#define glEvalCoord1fv _mesa_EvalCoord1fv
#define glEvalCoord2d _mesa_EvalCoord2d
#define glEvalCoord2f _mesa_EvalCoord2f
#define glEvalCoord2dv _mesa_EvalCoord2dv
#define glEvalCoord2fv _mesa_EvalCoord2fv
#define glMapGrid1d _mesa_MapGrid1d
#define glMapGrid1f _mesa_MapGrid1f
#define glMapGrid2d _mesa_MapGrid2d
#define glMapGrid2f _mesa_MapGrid2f
#define glEvalPoint1 _mesa_EvalPoint1
#define glEvalPoint2 _mesa_EvalPoint2
#define glEvalMesh1 _mesa_EvalMesh1
#define glEvalMesh2 _mesa_EvalMesh2

/*
 * Fog
 */

#define glFogf _mesa_Fogf
#define glFogi _mesa_Fogi
#define glFogfv _mesa_Fogfv
#define glFogiv _mesa_Fogiv

/*
 * Selection and Feedback
 */

#define glFeedbackBuffer _mesa_FeedbackBuffer
#define glPassThrough _mesa_PassThrough
#define glSelectBuffer _mesa_SelectBuffer
#define glInitNames _mesa_InitNames
#define glLoadName _mesa_LoadName
#define glPushName _mesa_PushName
#define glPopName _mesa_PopName

/* 1.2 functions */

#define glDrawRangeElements _mesa_DrawRangeElements
#define glTexImage3D _mesa_TexImage3D
#define glTexSubImage3D _mesa_TexSubImage3D
#define glCopyTexSubImage3D _mesa_CopyTexSubImage3D

/* 1.2 imaging extension functions */

#define glColorTable _mesa_ColorTable
#define glColorSubTable _mesa_ColorSubTable
#define glColorTableParameteri _mesa_ColorTableParameteri
#define glColorTableParameterf _mesa_ColorTableParameterf
#define glCopyColorSubTable _mesa_CopyColorSubTable
#define glCopyColorTable _mesa_CopyColorTable
#define glGetColorTable _mesa_GetColorTable
#define glGetColorTableParameterfv _mesa_GetColorTableParameterfv
#define glGetColorTableParameteriv _mesa_GetColorTableParameteriv
#define glBlendEquation _mesa_BlendEquation
#define glBlendColor _mesa_BlendColor
#define glHistogram _mesa_Histogram
#define glResetHistogram _mesa_ResetHistogram
#define glGetHistogram _mesa_GetHistogram
#define glGetHistogramParameterfv _mesa_GetHistogramParameterfv
#define glGetHistogramParameteriv _mesa_GetHistogramParameteriv
#define glMinmax _mesa_Minmax
#define glResetMinmax _mesa_ResetMinmax
#define glGetMinmax _mesa_GetMinmax
#define glGetMinmaxParameterfv _mesa_GetMinmaxParameterfv
#define glGetMinmaxParameteriv _mesa_GetMinmaxParameteriv
#define glConvolutionFilter1D _mesa_ConvolutionFilter1D
#define glConvolutionFilter2D _mesa_ConvolutionFilter2D
#define glConvolutionParameterf _mesa_ConvolutionParameterf
#define glConvolutionParameterfv _mesa_ConvolutionParameterfv
#define glConvolutionParameteri _mesa_ConvolutionParameteri
#define glConvolutionParameteriv _mesa_ConvolutionParameteriv
#define glCopyConvolutionFilter1D _mesa_CopyConvolutionFilter1D
#define glCopyConvolutionFilter2D _mesa_CopyConvolutionFilter2D
#define glGetConvolutionFilter _mesa_GetConvolutionFilter
#define glGetConvolutionParameterfv _mesa_GetConvolutionParameterfv
#define glGetConvolutionParameteriv _mesa_GetConvolutionParameteriv
#define glSeparableFilter2D _mesa_SeparableFilter2D
#define glGetSeparableFilter _mesa_GetSeparableFilter

/*
 * GL_ARB_multitexture (ARB extension 1 and OpenGL 1.2.1)
 */

#define glActiveTextureAR _mesa_ActiveTextureAR
#define glClientActiveTextureAR _mesa_ClientActiveTextureAR
#define glMultiTexCoord1dAR _mesa_MultiTexCoord1dAR
#define glMultiTexCoord1dvAR _mesa_MultiTexCoord1dvAR
#define glMultiTexCoord1fAR _mesa_MultiTexCoord1fAR
#define glMultiTexCoord1fvAR _mesa_MultiTexCoord1fvAR
#define glMultiTexCoord1iAR _mesa_MultiTexCoord1iAR
#define glMultiTexCoord1ivAR _mesa_MultiTexCoord1ivAR
#define glMultiTexCoord1sAR _mesa_MultiTexCoord1sAR
#define glMultiTexCoord1svAR _mesa_MultiTexCoord1svAR
#define glMultiTexCoord2dAR _mesa_MultiTexCoord2dAR
#define glMultiTexCoord2dvAR _mesa_MultiTexCoord2dvAR
#define glMultiTexCoord2fAR _mesa_MultiTexCoord2fAR
#define glMultiTexCoord2fvAR _mesa_MultiTexCoord2fvAR
#define glMultiTexCoord2iAR _mesa_MultiTexCoord2iAR
#define glMultiTexCoord2ivAR _mesa_MultiTexCoord2ivAR
#define glMultiTexCoord2sAR _mesa_MultiTexCoord2sAR
#define glMultiTexCoord2svAR _mesa_MultiTexCoord2svAR
#define glMultiTexCoord3dAR _mesa_MultiTexCoord3dAR
#define glMultiTexCoord3dvAR _mesa_MultiTexCoord3dvAR
#define glMultiTexCoord3fAR _mesa_MultiTexCoord3fAR
#define glMultiTexCoord3fvAR _mesa_MultiTexCoord3fvAR
#define glMultiTexCoord3iAR _mesa_MultiTexCoord3iAR
#define glMultiTexCoord3ivAR _mesa_MultiTexCoord3ivAR
#define glMultiTexCoord3sAR _mesa_MultiTexCoord3sAR
#define glMultiTexCoord3svAR _mesa_MultiTexCoord3svAR
#define glMultiTexCoord4dAR _mesa_MultiTexCoord4dAR
#define glMultiTexCoord4dvAR _mesa_MultiTexCoord4dvAR
#define glMultiTexCoord4fAR _mesa_MultiTexCoord4fAR
#define glMultiTexCoord4fvAR _mesa_MultiTexCoord4fvAR
#define glMultiTexCoord4iAR _mesa_MultiTexCoord4iAR
#define glMultiTexCoord4ivAR _mesa_MultiTexCoord4ivAR
#define glMultiTexCoord4sAR _mesa_MultiTexCoord4sAR
#define glMultiTexCoord4svAR _mesa_MultiTexCoord4svAR

#if defined(GL_GLEXT_LEGACY)


/*
 * 1. GL_EXT_abgr
 */



/*
 * 2. GL_EXT_blend_color
 */
#define glBlendColorEXT _mesa_BlendColorEXT

/*
 * 3. GL_EXT_polygon_offset
 */
#define glPolygonOffsetEXT _mesa_PolygonOffsetEXT


/*
 * 6. GL_EXT_texture3D
 */

#define glTexImage3DEXT _mesa_TexImage3DEXT
#define glTexSubImage3DEXT _mesa_TexSubImage3DEXT
#define glCopyTexSubImage3DEXT _mesa_CopyTexSubImage3DEXT

/*
 * 20. GL_EXT_texture_object
 */

#define glGenTexturesEXT _mesa_GenTextures
#define glDeleteTexturesEXT _mesa_DeleteTextures
#define glBindTextureEXT _mesa_BindTexture
#define glPrioritizeTexturesEXT _mesa_PrioritizeTextures
#define glAreTexturesResidentEXT _mesa_AreTexturesResident
#define glIsTextureEXT _mesa_IsTexture

/*
 * 27. GL_EXT_rescale_normal
 */


/*
 * 30. GL_EXT_vertex_array
 */

#define glVertexPointerEXT _mesa_VertexPointerEXT
#define glNormalPointerEXT _mesa_NormalPointerEXT
#define glColorPointerEXT _mesa_ColorPointerEXT
#define glIndexPointerEXT _mesa_IndexPointerEXT
#define glTexCoordPointerEXT _mesa_TexCoordPointerEXT
#define glEdgeFlagPointerEXT _mesa_EdgeFlagPointerEXT
#define glGetPointervEXT _mesa_GetPointervEXT
#define glArrayElementEXT _mesa_ArrayElementEXT
#define glDrawArraysEXT _mesa_DrawArraysEXT

/*
 * 35. GL_SGIS_texture_edge_clamp
 */


/*
 * 37. GL_EXT_blend_minmax
 */
#define glBlendEquationEXT _mesa_BlendEquationEXT

/*
 * 38. GL_EXT_blend_subtract (requires GL_EXT_blend_max )
 */


/*
 * 39. GL_EXT_blend_logic_op
 */


/*
 * 54. GL_EXT_point_parameters
 */

#define glPointParameterfEXT _mesa_PointParameterfEXT
#define glPointParameterfvEXT _mesa_PointParameterfvEXT
#define glPointParameterfSGI _mesa_PointParameterfSGI
#define glPointParameterfvSGI _mesa_PointParameterfvSGI

/*
 * 78. GL_EXT_paletted_texture
 */

#define glColorTableEXT _mesa_ColorTableEXT
#define glColorSubTableEXT _mesa_ColorSubTableEXT
#define glGetColorTableEXT _mesa_GetColorTableEXT
#define glGetColorTableParameterfvEXT _mesa_GetColorTableParameterfvEXT
#define glGetColorTableParameterivEXT _mesa_GetColorTableParameterivEXT

/*
 * 79. GL_EXT_clip_volume_hint
 */

/*
 * 97. GL_EXT_compiled_vertex_array
 */

#define glLockArraysEXT _mesa_LockArraysEXT
#define glUnlockArraysEXT _mesa_UnlockArraysEXT

/*
 * 137. GL_HP_occlusion_test
 */

/*
 * 141. GL_EXT_shared_texture_palette (req's GL_EXT_paletted_texture)
 */

/*
 * 176. GL_EXT_stencil_wrap
 */

/*
 * 179. GL_NV_texgen_reflection
 */

/*
 * 185. GL_EXT_texture_env_add
 */

/*
 * 197. GL_MESA_window_pos
 */

#define glWindowPos2iMESA _mesa_WindowPos2iMESA
#define glWindowPos2sMESA _mesa_WindowPos2sMESA
#define glWindowPos2fMESA _mesa_WindowPos2fMESA
#define glWindowPos2dMESA _mesa_WindowPos2dMESA
#define glWindowPos2ivMESA _mesa_WindowPos2ivMESA
#define glWindowPos2svMESA _mesa_WindowPos2svMESA
#define glWindowPos2fvMESA _mesa_WindowPos2fvMESA
#define glWindowPos2dvMESA _mesa_WindowPos2dvMESA
#define glWindowPos3iMESA _mesa_WindowPos3iMESA
#define glWindowPos3sMESA _mesa_WindowPos3sMESA
#define glWindowPos3fMESA _mesa_WindowPos3fMESA
#define glWindowPos3dMESA _mesa_WindowPos3dMESA
#define glWindowPos3ivMESA _mesa_WindowPos3ivMESA
#define glWindowPos3svMESA _mesa_WindowPos3svMESA
#define glWindowPos3fvMESA _mesa_WindowPos3fvMESA
#define glWindowPos3dvMESA _mesa_WindowPos3dvMESA
#define glWindowPos4iMESA _mesa_WindowPos4iMESA
#define glWindowPos4sMESA _mesa_WindowPos4sMESA
#define glWindowPos4fMESA _mesa_WindowPos4fMESA
#define glWindowPos4dMESA _mesa_WindowPos4dMESA
#define glWindowPos4ivMESA _mesa_WindowPos4ivMESA
#define glWindowPos4svMESA _mesa_WindowPos4svMESA
#define glWindowPos4fvMESA _mesa_WindowPos4fvMESA
#define glWindowPos4dvMESA _mesa_WindowPos4dvMESA

/* The following are glext.h mappings */

/*************************************************************/

#define glBlendColor _mesa_BlendColor
#define glBlendEquation _mesa_BlendEquation
#define glDrawRangeElements _mesa_DrawRangeElements
#define glColorTable _mesa_ColorTable
#define glColorTableParameterfv _mesa_ColorTableParameterfv
#define glColorTableParameteriv _mesa_ColorTableParameteriv
#define glCopyColorTable _mesa_CopyColorTable
#define glGetColorTable _mesa_GetColorTable
#define glGetColorTableParameterfv _mesa_GetColorTableParameterfv
#define glGetColorTableParameteriv _mesa_GetColorTableParameteriv
#define glColorSubTable _mesa_ColorSubTable
#define glCopyColorSubTable _mesa_CopyColorSubTable
#define glConvolutionFilter1D _mesa_ConvolutionFilter1D
#define glConvolutionFilter2D _mesa_ConvolutionFilter2D
#define glConvolutionParameterf _mesa_ConvolutionParameterf
#define glConvolutionParameterfv _mesa_ConvolutionParameterfv
#define glConvolutionParameteri _mesa_ConvolutionParameteri
#define glConvolutionParameteriv _mesa_ConvolutionParameteriv
#define glCopyConvolutionFilter1D _mesa_CopyConvolutionFilter1D
#define glCopyConvolutionFilter2D _mesa_CopyConvolutionFilter2D
#define glGetConvolutionFilter _mesa_GetConvolutionFilter
#define glGetConvolutionParameterfv _mesa_GetConvolutionParameterfv
#define glGetConvolutionParameteriv _mesa_GetConvolutionParameteriv
#define glGetSeparableFilter _mesa_GetSeparableFilter
#define glSeparableFilter2D _mesa_SeparableFilter2D
#define glGetHistogram _mesa_GetHistogram
#define glGetHistogramParameterfv _mesa_GetHistogramParameterfv
#define glGetHistogramParameteriv _mesa_GetHistogramParameteriv
#define glGetMinmax _mesa_GetMinmax
#define glGetMinmaxParameterfv _mesa_GetMinmaxParameterfv
#define glGetMinmaxParameteriv _mesa_GetMinmaxParameteriv
#define glHistogram _mesa_Histogram
#define glMinmax _mesa_Minmax
#define glResetHistogram _mesa_ResetHistogram
#define glResetMinmax _mesa_ResetMinmax
#define glTexImage3D _mesa_TexImage3D
#define glTexSubImage3D _mesa_TexSubImage3D
#define glCopyTexSubImage3D _mesa_CopyTexSubImage3D


#define glActiveTextureARB _mesa_ActiveTextureARB
#define glClientActiveTextureARB _mesa_ClientActiveTextureARB
#define glMultiTexCoord1dARB _mesa_MultiTexCoord1dARB
#define glMultiTexCoord1dvARB _mesa_MultiTexCoord1dvARB
#define glMultiTexCoord1fARB _mesa_MultiTexCoord1fARB
#define glMultiTexCoord1fvARB _mesa_MultiTexCoord1fvARB
#define glMultiTexCoord1iARB _mesa_MultiTexCoord1iARB
#define glMultiTexCoord1ivARB _mesa_MultiTexCoord1ivARB
#define glMultiTexCoord1sARB _mesa_MultiTexCoord1sARB
#define glMultiTexCoord1svARB _mesa_MultiTexCoord1svARB
#define glMultiTexCoord2dARB _mesa_MultiTexCoord2dARB
#define glMultiTexCoord2dvARB _mesa_MultiTexCoord2dvARB
#define glMultiTexCoord2fARB _mesa_MultiTexCoord2fARB
#define glMultiTexCoord2fvARB _mesa_MultiTexCoord2fvARB
#define glMultiTexCoord2iARB _mesa_MultiTexCoord2iARB
#define glMultiTexCoord2ivARB _mesa_MultiTexCoord2ivARB
#define glMultiTexCoord2sARB _mesa_MultiTexCoord2sARB
#define glMultiTexCoord2svARB _mesa_MultiTexCoord2svARB
#define glMultiTexCoord3dARB _mesa_MultiTexCoord3dARB
#define glMultiTexCoord3dvARB _mesa_MultiTexCoord3dvARB
#define glMultiTexCoord3fARB _mesa_MultiTexCoord3fARB
#define glMultiTexCoord3fvARB _mesa_MultiTexCoord3fvARB
#define glMultiTexCoord3iARB _mesa_MultiTexCoord3iARB
#define glMultiTexCoord3ivARB _mesa_MultiTexCoord3ivARB
#define glMultiTexCoord3sARB _mesa_MultiTexCoord3sARB
#define glMultiTexCoord3svARB _mesa_MultiTexCoord3svARB
#define glMultiTexCoord4dARB _mesa_MultiTexCoord4dARB
#define glMultiTexCoord4dvARB _mesa_MultiTexCoord4dvARB
#define glMultiTexCoord4fARB _mesa_MultiTexCoord4fARB
#define glMultiTexCoord4fvARB _mesa_MultiTexCoord4fvARB
#define glMultiTexCoord4iARB _mesa_MultiTexCoord4iARB
#define glMultiTexCoord4ivARB _mesa_MultiTexCoord4ivARB
#define glMultiTexCoord4sARB _mesa_MultiTexCoord4sARB
#define glMultiTexCoord4svARB _mesa_MultiTexCoord4svARB

#define glLoadTransposeMatrixfARB _mesa_LoadTransposeMatrixfARB
#define glLoadTransposeMatrixdARB _mesa_LoadTransposeMatrixdARB
#define glMultTransposeMatrixfARB _mesa_MultTransposeMatrixfARB
#define glMultTransposeMatrixdARB _mesa_MultTransposeMatrixdARB

#define glSampleCoverageARB _mesa_SampleCoverageARB
#define glSamplePassARB _mesa_SamplePassARB

#define glCompressedTexImage3DARB _mesa_CompressedTexImage3DARB
#define glCompressedTexImage2DARB _mesa_CompressedTexImage2DARB
#define glCompressedTexImage1DARB _mesa_CompressedTexImage1DARB
#define glCompressedTexSubImage3DARB _mesa_CompressedTexSubImage3DARB
#define glCompressedTexSubImage2DARB _mesa_CompressedTexSubImage2DARB
#define glCompressedTexSubImage1DARB _mesa_CompressedTexSubImage1DARB
#define glGetCompressedTexImageARB _mesa_GetCompressedTexImageARB

#define glBlendColorEXT _mesa_BlendColorEXT

#define glPolygonOffsetEXT _mesa_PolygonOffsetEXT

#define glTexImage3DEXT _mesa_TexImage3DEXT
#define glTexSubImage3DEXT _mesa_TexSubImage3DEXT
#define glGetTexFilterFuncSGIS _mesa_GetTexFilterFuncSGIS
#define glTexFilterFuncSGIS _mesa_TexFilterFuncSGIS
#define glTexSubImage1DEXT _mesa_TexSubImage1DEXT
#define glTexSubImage2DEXT _mesa_TexSubImage2DEXT
#define glCopyTexImage1DEXT _mesa_CopyTexImage1DEXT
#define glCopyTexImage2DEXT _mesa_CopyTexImage2DEXT
#define glCopyTexSubImage1DEXT _mesa_CopyTexSubImage1DEXT
#define glCopyTexSubImage2DEXT _mesa_CopyTexSubImage2DEXT
#define glCopyTexSubImage3DEXT _mesa_CopyTexSubImage3DEXT

#define glGetHistogramEXT _mesa_GetHistogramEXT
#define glGetHistogramParameterfvEXT _mesa_GetHistogramParameterfvEXT
#define glGetHistogramParameterivEXT _mesa_GetHistogramParameterivEXT
#define glGetMinmaxEXT _mesa_GetMinmaxEXT
#define glGetMinmaxParameterfvEXT _mesa_GetMinmaxParameterfvEXT
#define glGetMinmaxParameterivEXT _mesa_GetMinmaxParameterivEXT
#define glHistogramEXT _mesa_HistogramEXT
#define glMinmaxEXT _mesa_MinmaxEXT
#define glResetHistogramEXT _mesa_ResetHistogramEXT
#define glResetMinmaxEXT _mesa_ResetMinmaxEXT

#define glConvolutionFilter1DEXT _mesa_ConvolutionFilter1DEXT
#define glConvolutionFilter2DEXT _mesa_ConvolutionFilter2DEXT
#define glConvolutionParameterfEXT _mesa_ConvolutionParameterfEXT
#define glConvolutionParameterfvEXT _mesa_ConvolutionParameterfvEXT
#define glConvolutionParameteriEXT _mesa_ConvolutionParameteriEXT
#define glConvolutionParameterivEXT _mesa_ConvolutionParameterivEXT
#define glCopyConvolutionFilter1DEXT _mesa_CopyConvolutionFilter1DEXT
#define glCopyConvolutionFilter2DEXT _mesa_CopyConvolutionFilter2DEXT
#define glGetConvolutionFilterEXT _mesa_GetConvolutionFilterEXT
#define glGetConvolutionParameterfvEXT _mesa_GetConvolutionParameterfvEXT
#define glGetConvolutionParameterivEXT _mesa_GetConvolutionParameterivEXT
#define glGetSeparableFilterEXT _mesa_GetSeparableFilterEXT
#define glSeparableFilter2DEXT _mesa_SeparableFilter2DEXT

#define glColorTableSGI _mesa_ColorTableSGI
#define glColorTableParameterfvSGI _mesa_ColorTableParameterfvSGI
#define glColorTableParameterivSGI _mesa_ColorTableParameterivSGI
#define glCopyColorTableSGI _mesa_CopyColorTableSGI
#define glGetColorTableSGI _mesa_GetColorTableSGI
#define glGetColorTableParameterfvSGI _mesa_GetColorTableParameterfvSGI
#define glGetColorTableParameterivSGI _mesa_GetColorTableParameterivSGI

#define glPixelTexGenSGIX _mesa_PixelTexGenSGIX

#define glPixelTexGenParameteriSGIS _mesa_PixelTexGenParameteriSGIS
#define glPixelTexGenParameterivSGIS _mesa_PixelTexGenParameterivSGIS
#define glPixelTexGenParameterfSGIS _mesa_PixelTexGenParameterfSGIS
#define glPixelTexGenParameterfvSGIS _mesa_PixelTexGenParameterfvSGIS
#define glGetPixelTexGenParameterivSGIS _mesa_GetPixelTexGenParameterivSGIS
#define glGetPixelTexGenParameterfvSGIS _mesa_GetPixelTexGenParameterfvSGIS

#define glTexImage4DSGIS _mesa_TexImage4DSGIS
#define glTexSubImage4DSGIS _mesa_TexSubImage4DSGIS

#if 0
#define glAreTexturesResidentEXT _mesa_AreTexturesResident
#define glBindTextureEXT _mesa_BindTexture
#define glDeleteTexturesEXT _mesa_DeleteTextures
#define glGenTexturesEXT _mesa_GenTextures
#define glIsTextureEXT _mesa_IsTexture
#define glPrioritizeTexturesEXT _mesa_PrioritizeTextures
#endif

#define glDetailTexFuncSGIS _mesa_DetailTexFuncSGIS
#define glGetDetailTexFuncSGIS _mesa_GetDetailTexFuncSGIS

#define glSharpenTexFuncSGIS _mesa_SharpenTexFuncSGIS
#define glGetSharpenTexFuncSGIS _mesa_GetSharpenTexFuncSGIS

#define glSampleMaskSGIS _mesa_SampleMaskSGIS
#define glSamplePatternSGIS _mesa_SamplePatternSGIS

#define glArrayElementEXT _mesa_ArrayElementEXT
#define glColorPointerEXT _mesa_ColorPointerEXT
#define glDrawArraysEXT _mesa_DrawArraysEXT
#define glEdgeFlagPointerEXT _mesa_EdgeFlagPointerEXT
#define glGetPointervEXT _mesa_GetPointervEXT
#define glIndexPointerEXT _mesa_IndexPointerEXT
#define glNormalPointerEXT _mesa_NormalPointerEXT
#define glTexCoordPointerEXT _mesa_TexCoordPointerEXT
#define glVertexPointerEXT _mesa_VertexPointerEXT

#define glBlendEquationEXT _mesa_BlendEquationEXT

#define glSpriteParameterfSGIX _mesa_SpriteParameterfSGIX
#define glSpriteParameterfvSGIX _mesa_SpriteParameterfvSGIX
#define glSpriteParameteriSGIX _mesa_SpriteParameteriSGIX
#define glSpriteParameterivSGIX _mesa_SpriteParameterivSGIX

#define glPointParameterfEXT _mesa_PointParameterfEXT
#define glPointParameterfvEXT _mesa_PointParameterfvEXT
#define glPointParameterfSGIS _mesa_PointParameterfSGIS
#define glPointParameterfvSGIS _mesa_PointParameterfvSGIS

#define glGetInstrumentsSGIX _mesa_GetInstrumentsSGIX
#define glInstrumentsBufferSGIX _mesa_InstrumentsBufferSGIX
#define glPollInstrumentsSGIX _mesa_PollInstrumentsSGIX
#define glReadInstrumentsSGIX _mesa_ReadInstrumentsSGIX
#define glStartInstrumentsSGIX _mesa_StartInstrumentsSGIX
#define glStopInstrumentsSGIX _mesa_StopInstrumentsSGIX

#define glFrameZoomSGIX _mesa_FrameZoomSGIX

#define glTagSampleBufferSGIX _mesa_TagSampleBufferSGIX

#define glDeformationMap3dSGIX _mesa_DeformationMap3dSGIX
#define glDeformationMap3fSGIX _mesa_DeformationMap3fSGIX
#define glDeformSGIX _mesa_DeformSGIX
#define glLoadIdentityDeformationMapSGIX _mesa_LoadIdentityDeformationMapSGIX

#define glReferencePlaneSGIX _mesa_ReferencePlaneSGIX
#endif /* GL_GLEXT_PROTOTYPES */

#define glFlushRasterSGIX _mesa_FlushRasterSGIX

#define glFogFuncSGIS _mesa_FogFuncSGIS
#define glGetFogFuncSGIS _mesa_GetFogFuncSGIS

#define glImageTransformParameteriHP _mesa_ImageTransformParameteriHP
#define glImageTransformParameterfHP _mesa_ImageTransformParameterfHP
#define glImageTransformParameterivHP _mesa_ImageTransformParameterivHP
#define glImageTransformParameterfvHP _mesa_ImageTransformParameterfvHP
#define glGetImageTransformParameterivHP _mesa_GetImageTransformParameterivHP
#define glGetImageTransformParameterfvHP _mesa_GetImageTransformParameterfvHP

#define glColorSubTableEXT _mesa_ColorSubTableEXT
#define glCopyColorSubTableEXT _mesa_CopyColorSubTableEXT

#define glHintPGI _mesa_HintPGI

#define glColorTableEXT _mesa_ColorTableEXT
#define glGetColorTableEXT _mesa_GetColorTableEXT
#define glGetColorTableParameterivEXT _mesa_GetColorTableParameterivEXT
#define glGetColorTableParameterfvEXT _mesa_GetColorTableParameterfvEXT

#define glGetListParameterfvSGIX _mesa_GetListParameterfvSGIX
#define glGetListParameterivSGIX _mesa_GetListParameterivSGIX
#define glListParameterfSGIX _mesa_ListParameterfSGIX
#define glListParameterfvSGIX _mesa_ListParameterfvSGIX
#define glListParameteriSGIX _mesa_ListParameteriSGIX
#define glListParameterivSGIX _mesa_ListParameterivSGIX

#define glIndexMaterialEXT _mesa_IndexMaterialEXT

#define glIndexFuncEXT _mesa_IndexFuncEXT

#define glLockArraysEXT _mesa_LockArraysEXT
#define glUnlockArraysEXT _mesa_UnlockArraysEXT

#define glCullParameterdvEXT _mesa_CullParameterdvEXT
#define glCullParameterfvEXT _mesa_CullParameterfvEXT

#define glFragmentColorMaterialSGIX _mesa_FragmentColorMaterialSGIX
#define glFragmentLightfSGIX _mesa_FragmentLightfSGIX
#define glFragmentLightfvSGIX _mesa_FragmentLightfvSGIX
#define glFragmentLightiSGIX _mesa_FragmentLightiSGIX
#define glFragmentLightivSGIX _mesa_FragmentLightivSGIX
#define glFragmentLightModelfSGIX _mesa_FragmentLightModelfSGIX
#define glFragmentLightModelfvSGIX _mesa_FragmentLightModelfvSGIX
#define glFragmentLightModeliSGIX _mesa_FragmentLightModeliSGIX
#define glFragmentLightModelivSGIX _mesa_FragmentLightModelivSGIX
#define glFragmentMaterialfSGIX _mesa_FragmentMaterialfSGIX
#define glFragmentMaterialfvSGIX _mesa_FragmentMaterialfvSGIX
#define glFragmentMaterialiSGIX _mesa_FragmentMaterialiSGIX
#define glFragmentMaterialivSGIX _mesa_FragmentMaterialivSGIX
#define glGetFragmentLightfvSGIX _mesa_GetFragmentLightfvSGIX
#define glGetFragmentLightivSGIX _mesa_GetFragmentLightivSGIX
#define glGetFragmentMaterialfvSGIX _mesa_GetFragmentMaterialfvSGIX
#define glGetFragmentMaterialivSGIX _mesa_GetFragmentMaterialivSGIX
#define glLightEnviSGIX _mesa_LightEnviSGIX

#define glDrawRangeElementsEXT _mesa_DrawRangeElementsEXT

#define glApplyTextureEXT _mesa_ApplyTextureEXT
#define glTextureLightEXT _mesa_TextureLightEXT
#define glTextureMaterialEXT _mesa_TextureMaterialEXT

#define glAsyncMarkerSGIX _mesa_AsyncMarkerSGIX
#define glFinishAsyncSGIX _mesa_FinishAsyncSGIX
#define glPollAsyncSGIX _mesa_PollAsyncSGIX
#define glGenAsyncMarkersSGIX _mesa_GenAsyncMarkersSGIX
#define glDeleteAsyncMarkersSGIX _mesa_DeleteAsyncMarkersSGIX
#define glIsAsyncMarkerSGIX _mesa_IsAsyncMarkerSGIX

#define glVertexPointervINTEL _mesa_VertexPointervINTEL
#define glNormalPointervINTEL _mesa_NormalPointervINTEL
#define glColorPointervINTEL _mesa_ColorPointervINTEL
#define glTexCoordPointervINTEL _mesa_TexCoordPointervINTEL

#define glPixelTransformParameteriEXT _mesa_PixelTransformParameteriEXT
#define glPixelTransformParameterfEXT _mesa_PixelTransformParameterfEXT
#define glPixelTransformParameterivEXT _mesa_PixelTransformParameterivEXT
#define glPixelTransformParameterfvEXT _mesa_PixelTransformParameterfvEXT

#define glSecondaryColor3bEXT _mesa_SecondaryColor3bEXT
#define glSecondaryColor3bvEXT _mesa_SecondaryColor3bvEXT
#define glSecondaryColor3dEXT _mesa_SecondaryColor3dEXT
#define glSecondaryColor3dvEXT _mesa_SecondaryColor3dvEXT
#define glSecondaryColor3fEXT _mesa_SecondaryColor3fEXT
#define glSecondaryColor3fvEXT _mesa_SecondaryColor3fvEXT
#define glSecondaryColor3iEXT _mesa_SecondaryColor3iEXT
#define glSecondaryColor3ivEXT _mesa_SecondaryColor3ivEXT
#define glSecondaryColor3sEXT _mesa_SecondaryColor3sEXT
#define glSecondaryColor3svEXT _mesa_SecondaryColor3svEXT
#define glSecondaryColor3ubEXT _mesa_SecondaryColor3ubEXT
#define glSecondaryColor3ubvEXT _mesa_SecondaryColor3ubvEXT
#define glSecondaryColor3uiEXT _mesa_SecondaryColor3uiEXT
#define glSecondaryColor3uivEXT _mesa_SecondaryColor3uivEXT
#define glSecondaryColor3usEXT _mesa_SecondaryColor3usEXT
#define glSecondaryColor3usvEXT _mesa_SecondaryColor3usvEXT
#define glSecondaryColorPointerEXT _mesa_SecondaryColorPointerEXT

#define glTextureNormalEXT _mesa_TextureNormalEXT

#define glMultiDrawArraysEXT _mesa_MultiDrawArraysEXT
#define glMultiDrawElementsEXT _mesa_MultiDrawElementsEXT

#define glFogCoordfEXT _mesa_FogCoordfEXT
#define glFogCoordfvEXT _mesa_FogCoordfvEXT
#define glFogCoorddEXT _mesa_FogCoorddEXT
#define glFogCoorddvEXT _mesa_FogCoorddvEXT
#define glFogCoordPointerEXT _mesa_FogCoordPointerEXT

#define glTangent3bEXT _mesa_Tangent3bEXT
#define glTangent3bvEXT _mesa_Tangent3bvEXT
#define glTangent3dEXT _mesa_Tangent3dEXT
#define glTangent3dvEXT _mesa_Tangent3dvEXT
#define glTangent3fEXT _mesa_Tangent3fEXT
#define glTangent3fvEXT _mesa_Tangent3fvEXT
#define glTangent3iEXT _mesa_Tangent3iEXT
#define glTangent3ivEXT _mesa_Tangent3ivEXT
#define glTangent3sEXT _mesa_Tangent3sEXT
#define glTangent3svEXT _mesa_Tangent3svEXT
#define glBinormal3bEXT _mesa_Binormal3bEXT
#define glBinormal3bvEXT _mesa_Binormal3bvEXT
#define glBinormal3dEXT _mesa_Binormal3dEXT
#define glBinormal3dvEXT _mesa_Binormal3dvEXT
#define glBinormal3fEXT _mesa_Binormal3fEXT
#define glBinormal3fvEXT _mesa_Binormal3fvEXT
#define glBinormal3iEXT _mesa_Binormal3iEXT
#define glBinormal3ivEXT _mesa_Binormal3ivEXT
#define glBinormal3sEXT _mesa_Binormal3sEXT
#define glBinormal3svEXT _mesa_Binormal3svEXT
#define glTangentPointerEXT _mesa_TangentPointerEXT
#define glBinormalPointerEXT _mesa_BinormalPointerEXT
#define glFinishTextureSUNX _mesa_FinishTextureSUNX

#define glGlobalAlphaFactorbSUN _mesa_GlobalAlphaFactorbSUN
#define glGlobalAlphaFactorsSUN _mesa_GlobalAlphaFactorsSUN
#define glGlobalAlphaFactoriSUN _mesa_GlobalAlphaFactoriSUN
#define glGlobalAlphaFactorfSUN _mesa_GlobalAlphaFactorfSUN
#define glGlobalAlphaFactordSUN _mesa_GlobalAlphaFactordSUN
#define glGlobalAlphaFactorubSUN _mesa_GlobalAlphaFactorubSUN
#define glGlobalAlphaFactorusSUN _mesa_GlobalAlphaFactorusSUN
#define glGlobalAlphaFactoruiSUN _mesa_GlobalAlphaFactoruiSUN

#define glReplacementCodeuiSUN _mesa_ReplacementCodeuiSUN
#define glReplacementCodeusSUN _mesa_ReplacementCodeusSUN
#define glReplacementCodeubSUN _mesa_ReplacementCodeubSUN
#define glReplacementCodeuivSUN _mesa_ReplacementCodeuivSUN
#define glReplacementCodeusvSUN _mesa_ReplacementCodeusvSUN
#define glReplacementCodeubvSUN _mesa_ReplacementCodeubvSUN
#define glReplacementCodePointerSUN _mesa_ReplacementCodePointerSUN

#define glColor4ubVertex2fSUN _mesa_Color4ubVertex2fSUN
#define glColor4ubVertex2fvSUN _mesa_Color4ubVertex2fvSUN
#define glColor4ubVertex3fSUN _mesa_Color4ubVertex3fSUN
#define glColor4ubVertex3fvSUN _mesa_Color4ubVertex3fvSUN
#define glColor3fVertex3fSUN _mesa_Color3fVertex3fSUN
#define glColor3fVertex3fvSUN _mesa_Color3fVertex3fvSUN
#define glNormal3fVertex3fSUN _mesa_Normal3fVertex3fSUN
#define glNormal3fVertex3fvSUN _mesa_Normal3fVertex3fvSUN
#define glColor4fNormal3fVertex3fSUN _mesa_Color4fNormal3fVertex3fSUN
#define glColor4fNormal3fVertex3fvSUN _mesa_Color4fNormal3fVertex3fvSUN
#define glTexCoord2fVertex3fSUN _mesa_TexCoord2fVertex3fSUN
#define glTexCoord2fVertex3fvSUN _mesa_TexCoord2fVertex3fvSUN
#define glTexCoord4fVertex4fSUN _mesa_TexCoord4fVertex4fSUN
#define glTexCoord4fVertex4fvSUN _mesa_TexCoord4fVertex4fvSUN
#define glTexCoord2fColor4ubVertex3fSUN _mesa_TexCoord2fColor4ubVertex3fSUN
#define glTexCoord2fColor4ubVertex3fvSUN _mesa_TexCoord2fColor4ubVertex3fvSUN
#define glTexCoord2fColor3fVertex3fSUN _mesa_TexCoord2fColor3fVertex3fSUN
#define glTexCoord2fColor3fVertex3fvSUN _mesa_TexCoord2fColor3fVertex3fvSUN
#define glTexCoord2fNormal3fVertex3fSUN _mesa_TexCoord2fNormal3fVertex3fSUN
#define glTexCoord2fNormal3fVertex3fvSUN _mesa_TexCoord2fNormal3fVertex3fvSUN
#define glTexCoord2fColor4fNormal3fVertex3fSUN _mesa_TexCoord2fColor4fNormal3fVertex3fSUN
#define glTexCoord2fColor4fNormal3fVertex3fvSUN _mesa_TexCoord2fColor4fNormal3fVertex3fvSUN
#define glTexCoord4fColor4fNormal3fVertex4fSUN _mesa_TexCoord4fColor4fNormal3fVertex4fSUN
#define glTexCoord4fColor4fNormal3fVertex4fvSUN _mesa_TexCoord4fColor4fNormal3fVertex4fvSUN
#define glReplacementCodeuiVertex3fSUN _mesa_ReplacementCodeuiVertex3fSUN
#define glReplacementCodeuiVertex3fvSUN _mesa_ReplacementCodeuiVertex3fvSUN
#define glReplacementCodeuiColor4ubVertex3fSUN _mesa_ReplacementCodeuiColor4ubVertex3fSUN
#define glReplacementCodeuiColor4ubVertex3fvSUN _mesa_ReplacementCodeuiColor4ubVertex3fvSUN
#define glReplacementCodeuiColor3fVertex3fSUN _mesa_ReplacementCodeuiColor3fVertex3fSUN
#define glReplacementCodeuiColor3fVertex3fvSUN _mesa_ReplacementCodeuiColor3fVertex3fvSUN
#define glReplacementCodeuiNormal3fVertex3fSUN _mesa_ReplacementCodeuiNormal3fVertex3fSUN
#define glReplacementCodeuiNormal3fVertex3fvSUN _mesa_ReplacementCodeuiNormal3fVertex3fvSUN
#define glReplacementCodeuiColor4fNormal3fVertex3fSUN _mesa_ReplacementCodeuiColor4fNormal3fVertex3fSUN
#define glReplacementCodeuiColor4fNormal3fVertex3fvSUN _mesa_ReplacementCodeuiColor4fNormal3fVertex3fvSUN
#define glReplacementCodeuiTexCoord2fVertex3fSUN _mesa_ReplacementCodeuiTexCoord2fVertex3fSUN
#define glReplacementCodeuiTexCoord2fVertex3fvSUN _mesa_ReplacementCodeuiTexCoord2fVertex3fvSUN
#define glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN _mesa_ReplacementCodeuiTexCoord2fNormal3fVertex3fSUN
#define glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN _mesa_ReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN
#define glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN _mesa_ReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN
#define glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN _mesa_ReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN

#define glBlendFuncSeparateEXT _mesa_BlendFuncSeparateEXT

#define glVertexWeightfEXT _mesa_VertexWeightfEXT
#define glVertexWeightfvEXT _mesa_VertexWeightfvEXT
#define glVertexWeightPointerEXT _mesa_VertexWeightPointerEXT

#define glFlushVertexArrayRangeNV _mesa_FlushVertexArrayRangeNV
#define glVertexArrayRangeNV _mesa_VertexArrayRangeNV

#define glCombinerParameterfvNV _mesa_CombinerParameterfvNV
#define glCombinerParameterfNV _mesa_CombinerParameterfNV
#define glCombinerParameterivNV _mesa_CombinerParameterivNV
#define glCombinerParameteriNV _mesa_CombinerParameteriNV
#define glCombinerInputNV _mesa_CombinerInputNV
#define glCombinerOutputNV _mesa_CombinerOutputNV
#define glFinalCombinerInputNV _mesa_FinalCombinerInputNV
#define glGetCombinerInputParameterfvNV _mesa_GetCombinerInputParameterfvNV
#define glGetCombinerInputParameterivNV _mesa_GetCombinerInputParameterivNV
#define glGetCombinerOutputParameterfvNV _mesa_GetCombinerOutputParameterfvNV
#define glGetCombinerOutputParameterivNV _mesa_GetCombinerOutputParameterivNV
#define glGetFinalCombinerInputParameterfvNV _mesa_GetFinalCombinerInputParameterfvNV
#define glGetFinalCombinerInputParameterivNV _mesa_GetFinalCombinerInputParameterivNV

#define glResizeBuffersMESA _mesa_ResizeBuffersMESA

#define glWindowPos2dMESA _mesa_WindowPos2dMESA
#define glWindowPos2dvMESA _mesa_WindowPos2dvMESA
#define glWindowPos2fMESA _mesa_WindowPos2fMESA
#define glWindowPos2fvMESA _mesa_WindowPos2fvMESA
#define glWindowPos2iMESA _mesa_WindowPos2iMESA
#define glWindowPos2ivMESA _mesa_WindowPos2ivMESA
#define glWindowPos2sMESA _mesa_WindowPos2sMESA
#define glWindowPos2svMESA _mesa_WindowPos2svMESA
#define glWindowPos3dMESA _mesa_WindowPos3dMESA
#define glWindowPos3dvMESA _mesa_WindowPos3dvMESA
#define glWindowPos3fMESA _mesa_WindowPos3fMESA
#define glWindowPos3fvMESA _mesa_WindowPos3fvMESA
#define glWindowPos3iMESA _mesa_WindowPos3iMESA
#define glWindowPos3ivMESA _mesa_WindowPos3ivMESA
#define glWindowPos3sMESA _mesa_WindowPos3sMESA
#define glWindowPos3svMESA _mesa_WindowPos3svMESA
#define glWindowPos4dMESA _mesa_WindowPos4dMESA
#define glWindowPos4dvMESA _mesa_WindowPos4dvMESA
#define glWindowPos4fMESA _mesa_WindowPos4fMESA
#define glWindowPos4fvMESA _mesa_WindowPos4fvMESA
#define glWindowPos4iMESA _mesa_WindowPos4iMESA
#define glWindowPos4ivMESA _mesa_WindowPos4ivMESA
#define glWindowPos4sMESA _mesa_WindowPos4sMESA
#define glWindowPos4svMESA _mesa_WindowPos4svMESA

#define glMultiModeDrawArraysIBM _mesa_MultiModeDrawArraysIBM
#define glMultiModeDrawElementsIBM _mesa_MultiModeDrawElementsIBM

#define glColorPointerListIBM _mesa_ColorPointerListIBM
#define glSecondaryColorPointerListIBM _mesa_SecondaryColorPointerListIBM
#define glEdgeFlagPointerListIBM _mesa_EdgeFlagPointerListIBM
#define glFogCoordPointerListIBM _mesa_FogCoordPointerListIBM
#define glIndexPointerListIBM _mesa_IndexPointerListIBM
#define glNormalPointerListIBM _mesa_NormalPointerListIBM
#define glTexCoordPointerListIBM _mesa_TexCoordPointerListIBM
#define glVertexPointerListIBM _mesa_VertexPointerListIBM

#define glTbufferMask3DFX _mesa_TbufferMask3DFX

#define glSampleMaskEXT _mesa_SampleMaskEXT
#define glSamplePatternEXT _mesa_SamplePatternEXT

#define glTextureColorMaskSGIS _mesa_TextureColorMaskSGIS

#define glIglooInterfaceSGIX _mesa_IglooInterfaceSGIX

#ifdef __cplusplus
}
#endif
#endif
