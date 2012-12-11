
/*
 * Mesa 3-D graphics library
 * Version:  3.4
 *
 * Copyright (C) 1999-2000  Brian Paul   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef __gl_h_
#define __gl_h_

#ifdef __cplusplus
extern "C" {
#endif



#define GL_VERSION_1_1   1
#define GL_VERSION_1_2   1



/*
 *
 * Datatypes
 *
 */
#ifdef CENTERLINE_CLPP
#define signed
#endif
typedef unsigned int	GLenum;
typedef unsigned char	GLboolean;
typedef unsigned int	GLbitfield;
typedef void		GLvoid;
typedef signed char	GLbyte;		/* 1-byte signed */
typedef short		GLshort;	/* 2-byte signed */
typedef int		GLint;		/* 4-byte signed */
typedef unsigned char	GLubyte;	/* 1-byte unsigned */
typedef unsigned short	GLushort;	/* 2-byte unsigned */
typedef unsigned int	GLuint;		/* 4-byte unsigned */
typedef int		GLsizei;	/* 4-byte signed */
typedef float		GLfloat;	/* single precision float */
typedef float		GLclampf;	/* single precision float in [0,1] */
typedef double		GLdouble;	/* double precision float */
typedef double		GLclampd;	/* double precision float in [0,1] */



/*
 *
 * Constants
 *
 */

/* Boolean values */
#define GL_FALSE				0x0
#define GL_TRUE					0x1

/* Data types */
#define GL_BYTE					0x1400
#define GL_UNSIGNED_BYTE			0x1401
#define GL_SHORT				0x1402
#define GL_UNSIGNED_SHORT			0x1403
#define GL_INT					0x1404
#define GL_UNSIGNED_INT				0x1405
#define GL_FLOAT				0x1406
#define GL_DOUBLE				0x140A
#define GL_2_BYTES				0x1407
#define GL_3_BYTES				0x1408
#define GL_4_BYTES				0x1409

/* Primitives */
#define GL_POINTS				0x0000
#define GL_LINES				0x0001
#define GL_LINE_LOOP				0x0002
#define GL_LINE_STRIP				0x0003
#define GL_TRIANGLES				0x0004
#define GL_TRIANGLE_STRIP			0x0005
#define GL_TRIANGLE_FAN				0x0006
#define GL_QUADS				0x0007
#define GL_QUAD_STRIP				0x0008
#define GL_POLYGON				0x0009

/* Vertex Arrays */
#define GL_VERTEX_ARRAY				0x8074
#define GL_NORMAL_ARRAY				0x8075
#define GL_COLOR_ARRAY				0x8076
#define GL_INDEX_ARRAY				0x8077
#define GL_TEXTURE_COORD_ARRAY			0x8078
#define GL_EDGE_FLAG_ARRAY			0x8079
#define GL_VERTEX_ARRAY_SIZE			0x807A
#define GL_VERTEX_ARRAY_TYPE			0x807B
#define GL_VERTEX_ARRAY_STRIDE			0x807C
#define GL_NORMAL_ARRAY_TYPE			0x807E
#define GL_NORMAL_ARRAY_STRIDE			0x807F
#define GL_COLOR_ARRAY_SIZE			0x8081
#define GL_COLOR_ARRAY_TYPE			0x8082
#define GL_COLOR_ARRAY_STRIDE			0x8083
#define GL_INDEX_ARRAY_TYPE			0x8085
#define GL_INDEX_ARRAY_STRIDE			0x8086
#define GL_TEXTURE_COORD_ARRAY_SIZE		0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE		0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE		0x808A
#define GL_EDGE_FLAG_ARRAY_STRIDE		0x808C
#define GL_VERTEX_ARRAY_POINTER			0x808E
#define GL_NORMAL_ARRAY_POINTER			0x808F
#define GL_COLOR_ARRAY_POINTER			0x8090
#define GL_INDEX_ARRAY_POINTER			0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER		0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER		0x8093
#define GL_V2F					0x2A20
#define GL_V3F					0x2A21
#define GL_C4UB_V2F				0x2A22
#define GL_C4UB_V3F				0x2A23
#define GL_C3F_V3F				0x2A24
#define GL_N3F_V3F				0x2A25
#define GL_C4F_N3F_V3F				0x2A26
#define GL_T2F_V3F				0x2A27
#define GL_T4F_V4F				0x2A28
#define GL_T2F_C4UB_V3F				0x2A29
#define GL_T2F_C3F_V3F				0x2A2A
#define GL_T2F_N3F_V3F				0x2A2B
#define GL_T2F_C4F_N3F_V3F			0x2A2C
#define GL_T4F_C4F_N3F_V4F			0x2A2D

/* Matrix Mode */
#define GL_MATRIX_MODE				0x0BA0
#define GL_MODELVIEW				0x1700
#define GL_PROJECTION				0x1701
#define GL_TEXTURE				0x1702

/* Points */
#define GL_POINT_SMOOTH				0x0B10
#define GL_POINT_SIZE				0x0B11
#define GL_POINT_SIZE_GRANULARITY 		0x0B13
#define GL_POINT_SIZE_RANGE			0x0B12

/* Lines */
#define GL_LINE_SMOOTH				0x0B20
#define GL_LINE_STIPPLE				0x0B24
#define GL_LINE_STIPPLE_PATTERN			0x0B25
#define GL_LINE_STIPPLE_REPEAT			0x0B26
#define GL_LINE_WIDTH				0x0B21
#define GL_LINE_WIDTH_GRANULARITY		0x0B23
#define GL_LINE_WIDTH_RANGE			0x0B22

/* Polygons */
#define GL_POINT				0x1B00
#define GL_LINE					0x1B01
#define GL_FILL					0x1B02
#define GL_CW					0x0900
#define GL_CCW					0x0901
#define GL_FRONT				0x0404
#define GL_BACK					0x0405
#define GL_POLYGON_MODE				0x0B40
#define GL_POLYGON_SMOOTH			0x0B41
#define GL_POLYGON_STIPPLE			0x0B42
#define GL_EDGE_FLAG				0x0B43
#define GL_CULL_FACE				0x0B44
#define GL_CULL_FACE_MODE			0x0B45
#define GL_FRONT_FACE				0x0B46
#define GL_POLYGON_OFFSET_FACTOR		0x8038
#define GL_POLYGON_OFFSET_UNITS			0x2A00
#define GL_POLYGON_OFFSET_POINT			0x2A01
#define GL_POLYGON_OFFSET_LINE			0x2A02
#define GL_POLYGON_OFFSET_FILL			0x8037

/* Display Lists */
#define GL_COMPILE				0x1300
#define GL_COMPILE_AND_EXECUTE			0x1301
#define GL_LIST_BASE				0x0B32
#define GL_LIST_INDEX				0x0B33
#define GL_LIST_MODE				0x0B30

/* Depth buffer */
#define GL_NEVER				0x0200
#define GL_LESS					0x0201
#define GL_EQUAL				0x0202
#define GL_LEQUAL				0x0203
#define GL_GREATER				0x0204
#define GL_NOTEQUAL				0x0205
#define GL_GEQUAL				0x0206
#define GL_ALWAYS				0x0207
#define GL_DEPTH_TEST				0x0B71
#define GL_DEPTH_BITS				0x0D56
#define GL_DEPTH_CLEAR_VALUE			0x0B73
#define GL_DEPTH_FUNC				0x0B74
#define GL_DEPTH_RANGE				0x0B70
#define GL_DEPTH_WRITEMASK			0x0B72
#define GL_DEPTH_COMPONENT			0x1902

/* Lighting */
#define GL_LIGHTING				0x0B50
#define GL_LIGHT0				0x4000
#define GL_LIGHT1				0x4001
#define GL_LIGHT2				0x4002
#define GL_LIGHT3				0x4003
#define GL_LIGHT4				0x4004
#define GL_LIGHT5				0x4005
#define GL_LIGHT6				0x4006
#define GL_LIGHT7				0x4007
#define GL_SPOT_EXPONENT			0x1205
#define GL_SPOT_CUTOFF				0x1206
#define GL_CONSTANT_ATTENUATION			0x1207
#define GL_LINEAR_ATTENUATION			0x1208
#define GL_QUADRATIC_ATTENUATION		0x1209
#define GL_AMBIENT				0x1200
#define GL_DIFFUSE				0x1201
#define GL_SPECULAR				0x1202
#define GL_SHININESS				0x1601
#define GL_EMISSION				0x1600
#define GL_POSITION				0x1203
#define GL_SPOT_DIRECTION			0x1204
#define GL_AMBIENT_AND_DIFFUSE			0x1602
#define GL_COLOR_INDEXES			0x1603
#define GL_LIGHT_MODEL_TWO_SIDE			0x0B52
#define GL_LIGHT_MODEL_LOCAL_VIEWER		0x0B51
#define GL_LIGHT_MODEL_AMBIENT			0x0B53
#define GL_FRONT_AND_BACK			0x0408
#define GL_SHADE_MODEL				0x0B54
#define GL_FLAT					0x1D00
#define GL_SMOOTH				0x1D01
#define GL_COLOR_MATERIAL			0x0B57
#define GL_COLOR_MATERIAL_FACE			0x0B55
#define GL_COLOR_MATERIAL_PARAMETER		0x0B56
#define GL_NORMALIZE				0x0BA1

/* User clipping planes */
#define GL_CLIP_PLANE0				0x3000
#define GL_CLIP_PLANE1				0x3001
#define GL_CLIP_PLANE2				0x3002
#define GL_CLIP_PLANE3				0x3003
#define GL_CLIP_PLANE4				0x3004
#define GL_CLIP_PLANE5				0x3005

/* Accumulation buffer */
#define GL_ACCUM_RED_BITS			0x0D58
#define GL_ACCUM_GREEN_BITS			0x0D59
#define GL_ACCUM_BLUE_BITS			0x0D5A
#define GL_ACCUM_ALPHA_BITS			0x0D5B
#define GL_ACCUM_CLEAR_VALUE			0x0B80
#define GL_ACCUM				0x0100
#define GL_ADD					0x0104
#define GL_LOAD					0x0101
#define GL_MULT					0x0103
#define GL_RETURN				0x0102

/* Alpha testing */
#define GL_ALPHA_TEST				0x0BC0
#define GL_ALPHA_TEST_REF			0x0BC2
#define GL_ALPHA_TEST_FUNC			0x0BC1

/* Blending */
#define GL_BLEND				0x0BE2
#define GL_BLEND_SRC				0x0BE1
#define GL_BLEND_DST				0x0BE0
#define GL_ZERO					0x0
#define GL_ONE					0x1
#define GL_SRC_COLOR				0x0300
#define GL_ONE_MINUS_SRC_COLOR			0x0301
#define GL_DST_COLOR				0x0306
#define GL_ONE_MINUS_DST_COLOR			0x0307
#define GL_SRC_ALPHA				0x0302
#define GL_ONE_MINUS_SRC_ALPHA			0x0303
#define GL_DST_ALPHA				0x0304
#define GL_ONE_MINUS_DST_ALPHA			0x0305
#define GL_SRC_ALPHA_SATURATE			0x0308
#define GL_CONSTANT_COLOR			0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR		0x8002
#define GL_CONSTANT_ALPHA			0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA		0x8004

/* Render Mode */
#define GL_FEEDBACK				0x1C01
#define GL_RENDER				0x1C00
#define GL_SELECT				0x1C02

/* Feedback */
#define GL_2D					0x0600
#define GL_3D					0x0601
#define GL_3D_COLOR				0x0602
#define GL_3D_COLOR_TEXTURE			0x0603
#define GL_4D_COLOR_TEXTURE			0x0604
#define GL_POINT_TOKEN				0x0701
#define GL_LINE_TOKEN				0x0702
#define GL_LINE_RESET_TOKEN			0x0707
#define GL_POLYGON_TOKEN			0x0703
#define GL_BITMAP_TOKEN				0x0704
#define GL_DRAW_PIXEL_TOKEN			0x0705
#define GL_COPY_PIXEL_TOKEN			0x0706
#define GL_PASS_THROUGH_TOKEN			0x0700
#define GL_FEEDBACK_BUFFER_POINTER		0x0DF0
#define GL_FEEDBACK_BUFFER_SIZE			0x0DF1
#define GL_FEEDBACK_BUFFER_TYPE			0x0DF2

/* Selection */
#define GL_SELECTION_BUFFER_POINTER		0x0DF3
#define GL_SELECTION_BUFFER_SIZE		0x0DF4

/* Fog */
#define GL_FOG					0x0B60
#define GL_FOG_MODE				0x0B65
#define GL_FOG_DENSITY				0x0B62
#define GL_FOG_COLOR				0x0B66
#define GL_FOG_INDEX				0x0B61
#define GL_FOG_START				0x0B63
#define GL_FOG_END				0x0B64
#define GL_LINEAR				0x2601
#define GL_EXP					0x0800
#define GL_EXP2					0x0801

/* Logic Ops */
#define GL_LOGIC_OP				0x0BF1
#define GL_INDEX_LOGIC_OP			0x0BF1
#define GL_COLOR_LOGIC_OP			0x0BF2
#define GL_LOGIC_OP_MODE			0x0BF0
#define GL_CLEAR				0x1500
#define GL_SET					0x150F
#define GL_COPY					0x1503
#define GL_COPY_INVERTED			0x150C
#define GL_NOOP					0x1505
#define GL_INVERT				0x150A
#define GL_AND					0x1501
#define GL_NAND					0x150E
#define GL_OR					0x1507
#define GL_NOR					0x1508
#define GL_XOR					0x1506
#define GL_EQUIV				0x1509
#define GL_AND_REVERSE				0x1502
#define GL_AND_INVERTED				0x1504
#define GL_OR_REVERSE				0x150B
#define GL_OR_INVERTED				0x150D

/* Stencil */
#define GL_STENCIL_TEST				0x0B90
#define GL_STENCIL_WRITEMASK			0x0B98
#define GL_STENCIL_BITS				0x0D57
#define GL_STENCIL_FUNC				0x0B92
#define GL_STENCIL_VALUE_MASK			0x0B93
#define GL_STENCIL_REF				0x0B97
#define GL_STENCIL_FAIL				0x0B94
#define GL_STENCIL_PASS_DEPTH_PASS		0x0B96
#define GL_STENCIL_PASS_DEPTH_FAIL		0x0B95
#define GL_STENCIL_CLEAR_VALUE			0x0B91
#define GL_STENCIL_INDEX			0x1901
#define GL_KEEP					0x1E00
#define GL_REPLACE				0x1E01
#define GL_INCR					0x1E02
#define GL_DECR					0x1E03

/* Buffers, Pixel Drawing/Reading */
#define GL_NONE					0x0
#define GL_LEFT					0x0406
#define GL_RIGHT				0x0407
/*GL_FRONT					0x0404 */
/*GL_BACK					0x0405 */
/*GL_FRONT_AND_BACK				0x0408 */
#define GL_FRONT_LEFT				0x0400
#define GL_FRONT_RIGHT				0x0401
#define GL_BACK_LEFT				0x0402
#define GL_BACK_RIGHT				0x0403
#define GL_AUX0					0x0409
#define GL_AUX1					0x040A
#define GL_AUX2					0x040B
#define GL_AUX3					0x040C
#define GL_COLOR_INDEX				0x1900
#define GL_RED					0x1903
#define GL_GREEN				0x1904
#define GL_BLUE					0x1905
#define GL_ALPHA				0x1906
#define GL_LUMINANCE				0x1909
#define GL_LUMINANCE_ALPHA			0x190A
#define GL_ALPHA_BITS				0x0D55
#define GL_RED_BITS				0x0D52
#define GL_GREEN_BITS				0x0D53
#define GL_BLUE_BITS				0x0D54
#define GL_INDEX_BITS				0x0D51
#define GL_SUBPIXEL_BITS			0x0D50
#define GL_AUX_BUFFERS				0x0C00
#define GL_READ_BUFFER				0x0C02
#define GL_DRAW_BUFFER				0x0C01
#define GL_DOUBLEBUFFER				0x0C32
#define GL_STEREO				0x0C33
#define GL_BITMAP				0x1A00
#define GL_COLOR				0x1800
#define GL_DEPTH				0x1801
#define GL_STENCIL				0x1802
#define GL_DITHER				0x0BD0
#define GL_RGB					0x1907
#define GL_RGBA					0x1908

/* Implementation limits */
#define GL_MAX_LIST_NESTING			0x0B31
#define GL_MAX_ATTRIB_STACK_DEPTH		0x0D35
#define GL_MAX_MODELVIEW_STACK_DEPTH		0x0D36
#define GL_MAX_NAME_STACK_DEPTH			0x0D37
#define GL_MAX_PROJECTION_STACK_DEPTH		0x0D38
#define GL_MAX_TEXTURE_STACK_DEPTH		0x0D39
#define GL_MAX_EVAL_ORDER			0x0D30
#define GL_MAX_LIGHTS				0x0D31
#define GL_MAX_CLIP_PLANES			0x0D32
#define GL_MAX_TEXTURE_SIZE			0x0D33
#define GL_MAX_PIXEL_MAP_TABLE			0x0D34
#define GL_MAX_VIEWPORT_DIMS			0x0D3A
#define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH	0x0D3B

/* Gets */
#define GL_ATTRIB_STACK_DEPTH			0x0BB0
#define GL_CLIENT_ATTRIB_STACK_DEPTH		0x0BB1
#define GL_COLOR_CLEAR_VALUE			0x0C22
#define GL_COLOR_WRITEMASK			0x0C23
#define GL_CURRENT_INDEX			0x0B01
#define GL_CURRENT_COLOR			0x0B00
#define GL_CURRENT_NORMAL			0x0B02
#define GL_CURRENT_RASTER_COLOR			0x0B04
#define GL_CURRENT_RASTER_DISTANCE		0x0B09
#define GL_CURRENT_RASTER_INDEX			0x0B05
#define GL_CURRENT_RASTER_POSITION		0x0B07
#define GL_CURRENT_RASTER_TEXTURE_COORDS	0x0B06
#define GL_CURRENT_RASTER_POSITION_VALID	0x0B08
#define GL_CURRENT_TEXTURE_COORDS		0x0B03
#define GL_INDEX_CLEAR_VALUE			0x0C20
#define GL_INDEX_MODE				0x0C30
#define GL_INDEX_WRITEMASK			0x0C21
#define GL_MODELVIEW_MATRIX			0x0BA6
#define GL_MODELVIEW_STACK_DEPTH		0x0BA3
#define GL_NAME_STACK_DEPTH			0x0D70
#define GL_PROJECTION_MATRIX			0x0BA7
#define GL_PROJECTION_STACK_DEPTH		0x0BA4
#define GL_RENDER_MODE				0x0C40
#define GL_RGBA_MODE				0x0C31
#define GL_TEXTURE_MATRIX			0x0BA8
#define GL_TEXTURE_STACK_DEPTH			0x0BA5
#define GL_VIEWPORT				0x0BA2

/* Evaluators */
#define GL_AUTO_NORMAL				0x0D80
#define GL_MAP1_COLOR_4				0x0D90
#define GL_MAP1_GRID_DOMAIN			0x0DD0
#define GL_MAP1_GRID_SEGMENTS			0x0DD1
#define GL_MAP1_INDEX				0x0D91
#define GL_MAP1_NORMAL				0x0D92
#define GL_MAP1_TEXTURE_COORD_1			0x0D93
#define GL_MAP1_TEXTURE_COORD_2			0x0D94
#define GL_MAP1_TEXTURE_COORD_3			0x0D95
#define GL_MAP1_TEXTURE_COORD_4			0x0D96
#define GL_MAP1_VERTEX_3			0x0D97
#define GL_MAP1_VERTEX_4			0x0D98
#define GL_MAP2_COLOR_4				0x0DB0
#define GL_MAP2_GRID_DOMAIN			0x0DD2
#define GL_MAP2_GRID_SEGMENTS			0x0DD3
#define GL_MAP2_INDEX				0x0DB1
#define GL_MAP2_NORMAL				0x0DB2
#define GL_MAP2_TEXTURE_COORD_1			0x0DB3
#define GL_MAP2_TEXTURE_COORD_2			0x0DB4
#define GL_MAP2_TEXTURE_COORD_3			0x0DB5
#define GL_MAP2_TEXTURE_COORD_4			0x0DB6
#define GL_MAP2_VERTEX_3			0x0DB7
#define GL_MAP2_VERTEX_4			0x0DB8
#define GL_COEFF				0x0A00
#define GL_DOMAIN				0x0A02
#define GL_ORDER				0x0A01

/* Hints */
#define GL_FOG_HINT				0x0C54
#define GL_LINE_SMOOTH_HINT			0x0C52
#define GL_PERSPECTIVE_CORRECTION_HINT		0x0C50
#define GL_POINT_SMOOTH_HINT			0x0C51
#define GL_POLYGON_SMOOTH_HINT			0x0C53
#define GL_DONT_CARE				0x1100
#define GL_FASTEST				0x1101
#define GL_NICEST				0x1102

/* Scissor box */
#define GL_SCISSOR_TEST				0x0C11
#define GL_SCISSOR_BOX				0x0C10

/* Pixel Mode / Transfer */
#define GL_MAP_COLOR				0x0D10
#define GL_MAP_STENCIL				0x0D11
#define GL_INDEX_SHIFT				0x0D12
#define GL_INDEX_OFFSET				0x0D13
#define GL_RED_SCALE				0x0D14
#define GL_RED_BIAS				0x0D15
#define GL_GREEN_SCALE				0x0D18
#define GL_GREEN_BIAS				0x0D19
#define GL_BLUE_SCALE				0x0D1A
#define GL_BLUE_BIAS				0x0D1B
#define GL_ALPHA_SCALE				0x0D1C
#define GL_ALPHA_BIAS				0x0D1D
#define GL_DEPTH_SCALE				0x0D1E
#define GL_DEPTH_BIAS				0x0D1F
#define GL_PIXEL_MAP_S_TO_S_SIZE		0x0CB1
#define GL_PIXEL_MAP_I_TO_I_SIZE		0x0CB0
#define GL_PIXEL_MAP_I_TO_R_SIZE		0x0CB2
#define GL_PIXEL_MAP_I_TO_G_SIZE		0x0CB3
#define GL_PIXEL_MAP_I_TO_B_SIZE		0x0CB4
#define GL_PIXEL_MAP_I_TO_A_SIZE		0x0CB5
#define GL_PIXEL_MAP_R_TO_R_SIZE		0x0CB6
#define GL_PIXEL_MAP_G_TO_G_SIZE		0x0CB7
#define GL_PIXEL_MAP_B_TO_B_SIZE		0x0CB8
#define GL_PIXEL_MAP_A_TO_A_SIZE		0x0CB9
#define GL_PIXEL_MAP_S_TO_S			0x0C71
#define GL_PIXEL_MAP_I_TO_I			0x0C70
#define GL_PIXEL_MAP_I_TO_R			0x0C72
#define GL_PIXEL_MAP_I_TO_G			0x0C73
#define GL_PIXEL_MAP_I_TO_B			0x0C74
#define GL_PIXEL_MAP_I_TO_A			0x0C75
#define GL_PIXEL_MAP_R_TO_R			0x0C76
#define GL_PIXEL_MAP_G_TO_G			0x0C77
#define GL_PIXEL_MAP_B_TO_B			0x0C78
#define GL_PIXEL_MAP_A_TO_A			0x0C79
#define GL_PACK_ALIGNMENT			0x0D05
#define GL_PACK_LSB_FIRST			0x0D01
#define GL_PACK_ROW_LENGTH			0x0D02
#define GL_PACK_SKIP_PIXELS			0x0D04
#define GL_PACK_SKIP_ROWS			0x0D03
#define GL_PACK_SWAP_BYTES			0x0D00
#define GL_UNPACK_ALIGNMENT			0x0CF5
#define GL_UNPACK_LSB_FIRST			0x0CF1
#define GL_UNPACK_ROW_LENGTH			0x0CF2
#define GL_UNPACK_SKIP_PIXELS			0x0CF4
#define GL_UNPACK_SKIP_ROWS			0x0CF3
#define GL_UNPACK_SWAP_BYTES			0x0CF0
#define GL_ZOOM_X				0x0D16
#define GL_ZOOM_Y				0x0D17

/* Texture mapping */
#define GL_TEXTURE_ENV				0x2300
#define GL_TEXTURE_ENV_MODE			0x2200
#define GL_TEXTURE_1D				0x0DE0
#define GL_TEXTURE_2D				0x0DE1
#define GL_TEXTURE_WRAP_S			0x2802
#define GL_TEXTURE_WRAP_T			0x2803
#define GL_TEXTURE_MAG_FILTER			0x2800
#define GL_TEXTURE_MIN_FILTER			0x2801
#define GL_TEXTURE_ENV_COLOR			0x2201
#define GL_TEXTURE_GEN_S			0x0C60
#define GL_TEXTURE_GEN_T			0x0C61
#define GL_TEXTURE_GEN_MODE			0x2500
#define GL_TEXTURE_BORDER_COLOR			0x1004
#define GL_TEXTURE_WIDTH			0x1000
#define GL_TEXTURE_HEIGHT			0x1001
#define GL_TEXTURE_BORDER			0x1005
#define GL_TEXTURE_COMPONENTS			0x1003
#define GL_TEXTURE_RED_SIZE			0x805C
#define GL_TEXTURE_GREEN_SIZE			0x805D
#define GL_TEXTURE_BLUE_SIZE			0x805E
#define GL_TEXTURE_ALPHA_SIZE			0x805F
#define GL_TEXTURE_LUMINANCE_SIZE		0x8060
#define GL_TEXTURE_INTENSITY_SIZE		0x8061
#define GL_NEAREST_MIPMAP_NEAREST		0x2700
#define GL_NEAREST_MIPMAP_LINEAR		0x2702
#define GL_LINEAR_MIPMAP_NEAREST		0x2701
#define GL_LINEAR_MIPMAP_LINEAR			0x2703
#define GL_OBJECT_LINEAR			0x2401
#define GL_OBJECT_PLANE				0x2501
#define GL_EYE_LINEAR				0x2400
#define GL_EYE_PLANE				0x2502
#define GL_SPHERE_MAP				0x2402
#define GL_DECAL				0x2101
#define GL_MODULATE				0x2100
#define GL_NEAREST				0x2600
#define GL_REPEAT				0x2901
#define GL_CLAMP				0x2900
#define GL_S					0x2000
#define GL_T					0x2001
#define GL_R					0x2002
#define GL_Q					0x2003
#define GL_TEXTURE_GEN_R			0x0C62
#define GL_TEXTURE_GEN_Q			0x0C63

/* GL 1.1 texturing */
#define GL_PROXY_TEXTURE_1D			0x8063
#define GL_PROXY_TEXTURE_2D			0x8064
#define GL_TEXTURE_PRIORITY			0x8066
#define GL_TEXTURE_RESIDENT			0x8067
#define GL_TEXTURE_BINDING_1D			0x8068
#define GL_TEXTURE_BINDING_2D			0x8069
#define GL_TEXTURE_INTERNAL_FORMAT		0x1003

/* GL 1.2 texturing */
#define GL_PACK_SKIP_IMAGES			0x806B
#define GL_PACK_IMAGE_HEIGHT			0x806C
#define GL_UNPACK_SKIP_IMAGES			0x806D
#define GL_UNPACK_IMAGE_HEIGHT			0x806E
#define GL_TEXTURE_3D				0x806F
#define GL_PROXY_TEXTURE_3D			0x8070
#define GL_TEXTURE_DEPTH			0x8071
#define GL_TEXTURE_WRAP_R			0x8072
#define GL_MAX_3D_TEXTURE_SIZE			0x8073
#define GL_TEXTURE_BINDING_3D			0x806A

/* Internal texture formats (GL 1.1) */
#define GL_ALPHA4				0x803B
#define GL_ALPHA8				0x803C
#define GL_ALPHA12				0x803D
#define GL_ALPHA16				0x803E
#define GL_LUMINANCE4				0x803F
#define GL_LUMINANCE8				0x8040
#define GL_LUMINANCE12				0x8041
#define GL_LUMINANCE16				0x8042
#define GL_LUMINANCE4_ALPHA4			0x8043
#define GL_LUMINANCE6_ALPHA2			0x8044
#define GL_LUMINANCE8_ALPHA8			0x8045
#define GL_LUMINANCE12_ALPHA4			0x8046
#define GL_LUMINANCE12_ALPHA12			0x8047
#define GL_LUMINANCE16_ALPHA16			0x8048
#define GL_INTENSITY				0x8049
#define GL_INTENSITY4				0x804A
#define GL_INTENSITY8				0x804B
#define GL_INTENSITY12				0x804C
#define GL_INTENSITY16				0x804D
#define GL_R3_G3_B2				0x2A10
#define GL_RGB4					0x804F
#define GL_RGB5					0x8050
#define GL_RGB8					0x8051
#define GL_RGB10				0x8052
#define GL_RGB12				0x8053
#define GL_RGB16				0x8054
#define GL_RGBA2				0x8055
#define GL_RGBA4				0x8056
#define GL_RGB5_A1				0x8057
#define GL_RGBA8				0x8058
#define GL_RGB10_A2				0x8059
#define GL_RGBA12				0x805A
#define GL_RGBA16				0x805B

/* Utility */
#define GL_VENDOR				0x1F00
#define GL_RENDERER				0x1F01
#define GL_VERSION				0x1F02
#define GL_EXTENSIONS				0x1F03

/* Errors */
#define GL_NO_ERROR 				0x0
#define GL_INVALID_VALUE			0x0501
#define GL_INVALID_ENUM				0x0500
#define GL_INVALID_OPERATION			0x0502
#define GL_STACK_OVERFLOW			0x0503
#define GL_STACK_UNDERFLOW			0x0504
#define GL_OUT_OF_MEMORY			0x0505


/* OpenGL 1.2 */
#define GL_RESCALE_NORMAL			0x803A
#define GL_CLAMP_TO_EDGE			0x812F
#define GL_MAX_ELEMENTS_VERTICES		0x80E8
#define GL_MAX_ELEMENTS_INDICES			0x80E9
#define GL_BGR					0x80E0
#define GL_BGRA					0x80E1
#define GL_UNSIGNED_BYTE_3_3_2			0x8032
#define GL_UNSIGNED_BYTE_2_3_3_REV		0x8362
#define GL_UNSIGNED_SHORT_5_6_5			0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV		0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4		0x8033
#define GL_UNSIGNED_SHORT_4_4_4_4_REV		0x8365
#define GL_UNSIGNED_SHORT_5_5_5_1		0x8034
#define GL_UNSIGNED_SHORT_1_5_5_5_REV		0x8366
#define GL_UNSIGNED_INT_8_8_8_8			0x8035
#define GL_UNSIGNED_INT_8_8_8_8_REV		0x8367
#define GL_UNSIGNED_INT_10_10_10_2		0x8036
#define GL_UNSIGNED_INT_2_10_10_10_REV		0x8368
#define GL_LIGHT_MODEL_COLOR_CONTROL		0x81F8
#define GL_SINGLE_COLOR				0x81F9
#define GL_SEPARATE_SPECULAR_COLOR		0x81FA
#define GL_TEXTURE_MIN_LOD			0x813A
#define GL_TEXTURE_MAX_LOD			0x813B
#define GL_TEXTURE_BASE_LEVEL			0x813C
#define GL_TEXTURE_MAX_LEVEL			0x813D
#define GL_SMOOTH_POINT_SIZE_RANGE		0x0B12
#define GL_SMOOTH_POINT_SIZE_GRANULARITY	0x0B13
#define GL_SMOOTH_LINE_WIDTH_RANGE		0x0B22
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY	0x0B23
#define GL_ALIASED_POINT_SIZE_RANGE		0x846D
#define GL_ALIASED_LINE_WIDTH_RANGE		0x846E



/*
 * OpenGL 1.2 imaging subset (NOT IMPLEMENTED BY MESA)
 */
/* GL_EXT_color_table */
#define GL_COLOR_TABLE				0x80D0
#define GL_POST_CONVOLUTION_COLOR_TABLE		0x80D1
#define GL_POST_COLOR_MATRIX_COLOR_TABLE	0x80D2
#define GL_PROXY_COLOR_TABLE			0x80D3
#define GL_PROXY_POST_CONVOLUTION_COLOR_TABLE	0x80D4
#define GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE	0x80D5
#define GL_COLOR_TABLE_SCALE			0x80D6
#define GL_COLOR_TABLE_BIAS			0x80D7
#define GL_COLOR_TABLE_FORMAT			0x80D8
#define GL_COLOR_TABLE_WIDTH			0x80D9
#define GL_COLOR_TABLE_RED_SIZE			0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE		0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE		0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE		0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE		0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE		0x80DF
/* GL_EXT_convolution and GL_HP_convolution_border_modes */
#define GL_CONVOLUTION_1D			0x8010
#define GL_CONVOLUTION_2D			0x8011
#define GL_SEPARABLE_2D				0x8012
#define GL_CONVOLUTION_BORDER_MODE		0x8013
#define GL_CONVOLUTION_FILTER_SCALE		0x8014
#define GL_CONVOLUTION_FILTER_BIAS		0x8015
#define GL_REDUCE				0x8016
#define GL_CONVOLUTION_FORMAT			0x8017
#define GL_CONVOLUTION_WIDTH			0x8018
#define GL_CONVOLUTION_HEIGHT			0x8019
#define GL_MAX_CONVOLUTION_WIDTH		0x801A
#define GL_MAX_CONVOLUTION_HEIGHT		0x801B
#define GL_POST_CONVOLUTION_RED_SCALE		0x801C
#define GL_POST_CONVOLUTION_GREEN_SCALE		0x801D
#define GL_POST_CONVOLUTION_BLUE_SCALE		0x801E
#define GL_POST_CONVOLUTION_ALPHA_SCALE		0x801F
#define GL_POST_CONVOLUTION_RED_BIAS		0x8020
#define GL_POST_CONVOLUTION_GREEN_BIAS		0x8021
#define GL_POST_CONVOLUTION_BLUE_BIAS		0x8022
#define GL_POST_CONVOLUTION_ALPHA_BIAS		0x8023
#define GL_CONSTANT_BORDER			0x8151
#define GL_REPLICATE_BORDER			0x8153
#define GL_CONVOLUTION_BORDER_COLOR		0x8154
/* GL_SGI_color_matrix */
#define GL_COLOR_MATRIX				0x80B1
#define GL_COLOR_MATRIX_STACK_DEPTH		0x80B2
#define GL_MAX_COLOR_MATRIX_STACK_DEPTH		0x80B3
#define GL_POST_COLOR_MATRIX_RED_SCALE		0x80B4
#define GL_POST_COLOR_MATRIX_GREEN_SCALE	0x80B5
#define GL_POST_COLOR_MATRIX_BLUE_SCALE		0x80B6
#define GL_POST_COLOR_MATRIX_ALPHA_SCALE	0x80B7
#define GL_POST_COLOR_MATRIX_RED_BIAS		0x80B8
#define GL_POST_COLOR_MATRIX_GREEN_BIAS		0x80B9
#define GL_POST_COLOR_MATRIX_BLUE_BIAS		0x80BA
#define GL_POST_COLOR_MATRIX_ALPHA_BIAS		0x80BB
/* GL_EXT_histogram */
#define GL_HISTOGRAM				0x8024
#define GL_PROXY_HISTOGRAM			0x8025
#define GL_HISTOGRAM_WIDTH			0x8026
#define GL_HISTOGRAM_FORMAT			0x8027
#define GL_HISTOGRAM_RED_SIZE			0x8028
#define GL_HISTOGRAM_GREEN_SIZE			0x8029
#define GL_HISTOGRAM_BLUE_SIZE			0x802A
#define GL_HISTOGRAM_ALPHA_SIZE			0x802B
#define GL_HISTOGRAM_LUMINANCE_SIZE		0x802C
#define GL_HISTOGRAM_SINK			0x802D
#define GL_MINMAX				0x802E
#define GL_MINMAX_FORMAT			0x802F
#define GL_MINMAX_SINK				0x8030
#define GL_TABLE_TOO_LARGE			0x8031
/* GL_EXT_blend_color, GL_EXT_blend_minmax */
#define GL_BLEND_EQUATION			0x8009
#define GL_MIN					0x8007
#define GL_MAX					0x8008
#define GL_FUNC_ADD				0x8006
#define GL_FUNC_SUBTRACT			0x800A
#define GL_FUNC_REVERSE_SUBTRACT		0x800B
#define	GL_BLEND_COLOR				0x8005


/* glPush/PopAttrib bits */
#define GL_CURRENT_BIT				0x00000001
#define GL_POINT_BIT				0x00000002
#define GL_LINE_BIT				0x00000004
#define GL_POLYGON_BIT				0x00000008
#define GL_POLYGON_STIPPLE_BIT			0x00000010
#define GL_PIXEL_MODE_BIT			0x00000020
#define GL_LIGHTING_BIT				0x00000040
#define GL_FOG_BIT				0x00000080
#define GL_DEPTH_BUFFER_BIT			0x00000100
#define GL_ACCUM_BUFFER_BIT			0x00000200
#define GL_STENCIL_BUFFER_BIT			0x00000400
#define GL_VIEWPORT_BIT				0x00000800
#define GL_TRANSFORM_BIT			0x00001000
#define GL_ENABLE_BIT				0x00002000
#define GL_COLOR_BUFFER_BIT			0x00004000
#define GL_HINT_BIT				0x00008000
#define GL_EVAL_BIT				0x00010000
#define GL_LIST_BIT				0x00020000
#define GL_TEXTURE_BIT				0x00040000
#define GL_SCISSOR_BIT				0x00080000
#define GL_ALL_ATTRIB_BITS			0x000FFFFF


#define GL_CLIENT_PIXEL_STORE_BIT		0x00000001
#define GL_CLIENT_VERTEX_ARRAY_BIT		0x00000002
#define GL_ALL_CLIENT_ATTRIB_BITS 		0xFFFFFFFF





#if defined(__BEOS__) || defined(__QUICKDRAW__)
#pragma export on
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



/*
 * GL_ARB_multitexture (ARB extension 1 and OpenGL 1.2.1)
 */
#ifndef GL_ARB_multitexture
#define GL_ARB_multitexture 1

#define GL_TEXTURE0_ARB				0x84C0
#define GL_TEXTURE1_ARB				0x84C1
#define GL_TEXTURE2_ARB				0x84C2
#define GL_TEXTURE3_ARB				0x84C3
#define GL_TEXTURE4_ARB				0x84C4
#define GL_TEXTURE5_ARB				0x84C5
#define GL_TEXTURE6_ARB				0x84C6
#define GL_TEXTURE7_ARB				0x84C7
#define GL_TEXTURE8_ARB				0x84C8
#define GL_TEXTURE9_ARB				0x84C9
#define GL_TEXTURE10_ARB			0x84CA
#define GL_TEXTURE11_ARB			0x84CB
#define GL_TEXTURE12_ARB			0x84CC
#define GL_TEXTURE13_ARB			0x84CD
#define GL_TEXTURE14_ARB			0x84CE
#define GL_TEXTURE15_ARB			0x84CF
#define GL_TEXTURE16_ARB			0x84D0
#define GL_TEXTURE17_ARB			0x84D1
#define GL_TEXTURE18_ARB			0x84D2
#define GL_TEXTURE19_ARB			0x84D3
#define GL_TEXTURE20_ARB			0x84D4
#define GL_TEXTURE21_ARB			0x84D5
#define GL_TEXTURE22_ARB			0x84D6
#define GL_TEXTURE23_ARB			0x84D7
#define GL_TEXTURE24_ARB			0x84D8
#define GL_TEXTURE25_ARB			0x84D9
#define GL_TEXTURE26_ARB			0x84DA
#define GL_TEXTURE27_ARB			0x84DB
#define GL_TEXTURE28_ARB			0x84DC
#define GL_TEXTURE29_ARB			0x84DD
#define GL_TEXTURE30_ARB			0x84DE
#define GL_TEXTURE31_ARB			0x84DF
#define GL_ACTIVE_TEXTURE_ARB			0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE_ARB		0x84E1
#define GL_MAX_TEXTURE_UNITS_ARB		0x84E2

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

#endif /* GL_ARB_multitexture */




#if defined(GL_GLEXT_LEGACY)


/*
 * 1. GL_EXT_abgr
 */
#ifndef GL_EXT_abgr
#define GL_EXT_abgr 1

#define GL_ABGR_EXT				0x8000

#endif /* GL_EXT_abgr */



/*
 * 2. GL_EXT_blend_color
 */
#ifndef GL_EXT_blend_color
#define GL_EXT_blend_color 1

#define GL_CONSTANT_COLOR_EXT			0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR_EXT		0x8002
#define GL_CONSTANT_ALPHA_EXT			0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA_EXT		0x8004
#define GL_BLEND_COLOR_EXT			0x8005

GLAPI void GLAPIENTRY _mesa_BlendColorEXT( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha );

#endif /* GL_EXT_blend_color */



/*
 * 3. GL_EXT_polygon_offset
 */
#ifndef GL_EXT_polygon_offset
#define GL_EXT_polygon_offset 1

#define GL_POLYGON_OFFSET_EXT			0x8037
#define GL_POLYGON_OFFSET_FACTOR_EXT		0x8038
#define GL_POLYGON_OFFSET_BIAS_EXT		0x8039

GLAPI void GLAPIENTRY _mesa_PolygonOffsetEXT( GLfloat factor, GLfloat bias );

#endif /* GL_EXT_polygon_offset */



/*
 * 6. GL_EXT_texture3D
 */
#ifndef GL_EXT_texture3D
#define GL_EXT_texture3D 1

#define GL_PACK_SKIP_IMAGES_EXT			0x806B
#define GL_PACK_IMAGE_HEIGHT_EXT		0x806C
#define GL_UNPACK_SKIP_IMAGES_EXT		0x806D
#define GL_UNPACK_IMAGE_HEIGHT_EXT		0x806E
#define GL_TEXTURE_3D_EXT			0x806F
#define GL_PROXY_TEXTURE_3D_EXT			0x8070
#define GL_TEXTURE_DEPTH_EXT			0x8071
#define GL_TEXTURE_WRAP_R_EXT			0x8072
#define GL_MAX_3D_TEXTURE_SIZE_EXT		0x8073
#define GL_TEXTURE_3D_BINDING_EXT		0x806A

GLAPI void GLAPIENTRY _mesa_TexImage3DEXT( GLenum target, GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels );

GLAPI void GLAPIENTRY _mesa_TexSubImage3DEXT( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);

GLAPI void GLAPIENTRY _mesa_CopyTexSubImage3DEXT( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height );

#endif /* GL_EXT_texture3D */



/*
 * 20. GL_EXT_texture_object
 */
#ifndef GL_EXT_texture_object
#define GL_EXT_texture_object 1

#define GL_TEXTURE_PRIORITY_EXT			0x8066
#define GL_TEXTURE_RESIDENT_EXT			0x8067
#define GL_TEXTURE_1D_BINDING_EXT		0x8068
#define GL_TEXTURE_2D_BINDING_EXT		0x8069

GLAPI void GLAPIENTRY _mesa_GenTexturesEXT( GLsizei n, GLuint *textures );

GLAPI void GLAPIENTRY _mesa_DeleteTexturesEXT( GLsizei n, const GLuint *textures);

GLAPI void GLAPIENTRY _mesa_BindTextureEXT( GLenum target, GLuint texture );

GLAPI void GLAPIENTRY _mesa_PrioritizeTexturesEXT( GLsizei n, const GLuint *textures, const GLclampf *priorities );

GLAPI GLboolean GLAPIENTRY _mesa_AreTexturesResidentEXT( GLsizei n, const GLuint *textures, GLboolean *residences );

GLAPI GLboolean GLAPIENTRY _mesa_IsTextureEXT( GLuint texture );

#endif /* GL_EXT_texture_object */



/*
 * 27. GL_EXT_rescale_normal
 */
#ifndef GL_EXT_rescale_normal
#define GL_EXT_rescale_normal 1

#define GL_RESCALE_NORMAL_EXT			0x803A

#endif /* GL_EXT_rescale_normal */



/*
 * 30. GL_EXT_vertex_array
 */
#ifndef GL_EXT_vertex_array
#define GL_EXT_vertex_array 1

#define GL_VERTEX_ARRAY_EXT			0x8074
#define GL_NORMAL_ARRAY_EXT			0x8075
#define GL_COLOR_ARRAY_EXT			0x8076
#define GL_INDEX_ARRAY_EXT			0x8077
#define GL_TEXTURE_COORD_ARRAY_EXT		0x8078
#define GL_EDGE_FLAG_ARRAY_EXT			0x8079
#define GL_VERTEX_ARRAY_SIZE_EXT		0x807A
#define GL_VERTEX_ARRAY_TYPE_EXT		0x807B
#define GL_VERTEX_ARRAY_STRIDE_EXT		0x807C
#define GL_VERTEX_ARRAY_COUNT_EXT		0x807D
#define GL_NORMAL_ARRAY_TYPE_EXT		0x807E
#define GL_NORMAL_ARRAY_STRIDE_EXT		0x807F
#define GL_NORMAL_ARRAY_COUNT_EXT		0x8080
#define GL_COLOR_ARRAY_SIZE_EXT			0x8081
#define GL_COLOR_ARRAY_TYPE_EXT			0x8082
#define GL_COLOR_ARRAY_STRIDE_EXT		0x8083
#define GL_COLOR_ARRAY_COUNT_EXT		0x8084
#define GL_INDEX_ARRAY_TYPE_EXT			0x8085
#define GL_INDEX_ARRAY_STRIDE_EXT		0x8086
#define GL_INDEX_ARRAY_COUNT_EXT		0x8087
#define GL_TEXTURE_COORD_ARRAY_SIZE_EXT		0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE_EXT		0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE_EXT	0x808A
#define GL_TEXTURE_COORD_ARRAY_COUNT_EXT	0x808B
#define GL_EDGE_FLAG_ARRAY_STRIDE_EXT		0x808C
#define GL_EDGE_FLAG_ARRAY_COUNT_EXT		0x808D
#define GL_VERTEX_ARRAY_POINTER_EXT		0x808E
#define GL_NORMAL_ARRAY_POINTER_EXT		0x808F
#define GL_COLOR_ARRAY_POINTER_EXT		0x8090
#define GL_INDEX_ARRAY_POINTER_EXT		0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER_EXT	0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER_EXT		0x8093

GLAPI void GLAPIENTRY _mesa_VertexPointerEXT( GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *ptr );

GLAPI void GLAPIENTRY _mesa_NormalPointerEXT( GLenum type, GLsizei stride, GLsizei count, const GLvoid *ptr );

GLAPI void GLAPIENTRY _mesa_ColorPointerEXT( GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *ptr );

GLAPI void GLAPIENTRY _mesa_IndexPointerEXT( GLenum type, GLsizei stride, GLsizei count, const GLvoid *ptr );

GLAPI void GLAPIENTRY _mesa_TexCoordPointerEXT( GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *ptr );

GLAPI void GLAPIENTRY _mesa_EdgeFlagPointerEXT( GLsizei stride, GLsizei count, const GLboolean *ptr );

GLAPI void GLAPIENTRY _mesa_GetPointervEXT( GLenum pname, void **params );

GLAPI void GLAPIENTRY _mesa_ArrayElementEXT( GLint i );

GLAPI void GLAPIENTRY _mesa_DrawArraysEXT( GLenum mode, GLint first, GLsizei count );

#endif /* GL_EXT_vertex_array */



/*
 * 35. GL_SGIS_texture_edge_clamp
 */
#ifndef GL_SGIS_texture_edge_clamp
#define GL_SGIS_texture_edge_clamp 1

#define GL_CLAMP_TO_EDGE_SGIS			0x812F

#endif /* GL_SGIS_texture_edge_clamp */



/*
 * 37. GL_EXT_blend_minmax
 */
#ifndef GL_EXT_blend_minmax
#define GL_EXT_blend_minmax 1

#define GL_FUNC_ADD_EXT				0x8006
#define GL_MIN_EXT				0x8007
#define GL_MAX_EXT				0x8008
#define GL_BLEND_EQUATION_EXT			0x8009

GLAPI void GLAPIENTRY _mesa_BlendEquationEXT( GLenum mode );

#endif /* GL_EXT_blend_minmax */



/*
 * 38. GL_EXT_blend_subtract (requires GL_EXT_blend_max )
 */
#ifndef GL_EXT_blend_subtract
#define GL_EXT_blend_subtract 1

#define GL_FUNC_SUBTRACT_EXT			0x800A
#define GL_FUNC_REVERSE_SUBTRACT_EXT		0x800B

#endif /* GL_EXT_blend_subtract */



/*
 * 39. GL_EXT_blend_logic_op
 */
#ifndef GL_EXT_blend_logic_op
#define GL_EXT_blend_logic_op 1

/* No new tokens or functions */

#endif /* GL_EXT_blend_logic_op */



/*
 * 54. GL_EXT_point_parameters
 */
#ifndef GL_EXT_point_parameters
#define GL_EXT_point_parameters 1

#define GL_POINT_SIZE_MIN_EXT			0x8126
#define GL_POINT_SIZE_MAX_EXT			0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_EXT	0x8128
#define GL_DISTANCE_ATTENUATION_EXT		0x8129

GLAPI void GLAPIENTRY _mesa_PointParameterfEXT( GLenum pname, GLfloat param );
GLAPI void GLAPIENTRY _mesa_PointParameterfvEXT( GLenum pname, const GLfloat *params );
GLAPI void GLAPIENTRY _mesa_PointParameterfSGIS(GLenum pname, GLfloat param);
GLAPI void GLAPIENTRY _mesa_PointParameterfvSGIS(GLenum pname, const GLfloat *params);

#endif /* GL_EXT_point_parameters */



/*
 * 78. GL_EXT_paletted_texture
 */
#ifndef GL_EXT_paletted_texture
#define GL_EXT_paletted_texture 1

#define GL_TABLE_TOO_LARGE_EXT			0x8031
#define GL_COLOR_TABLE_FORMAT_EXT		0x80D8
#define GL_COLOR_TABLE_WIDTH_EXT		0x80D9
#define GL_COLOR_TABLE_RED_SIZE_EXT		0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE_EXT		0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE_EXT		0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE_EXT	 	0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE_EXT	0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE_EXT	0x80DF
#define GL_TEXTURE_INDEX_SIZE_EXT		0x80ED
#define GL_COLOR_INDEX1_EXT			0x80E2
#define GL_COLOR_INDEX2_EXT			0x80E3
#define GL_COLOR_INDEX4_EXT			0x80E4
#define GL_COLOR_INDEX8_EXT			0x80E5
#define GL_COLOR_INDEX12_EXT			0x80E6
#define GL_COLOR_INDEX16_EXT			0x80E7

GLAPI void GLAPIENTRY _mesa_ColorTableEXT( GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table );

GLAPI void GLAPIENTRY _mesa_ColorSubTableEXT( GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data );

GLAPI void GLAPIENTRY _mesa_GetColorTableEXT( GLenum target, GLenum format, GLenum type, GLvoid *table );

GLAPI void GLAPIENTRY _mesa_GetColorTableParameterfvEXT( GLenum target, GLenum pname, GLfloat *params );

GLAPI void GLAPIENTRY _mesa_GetColorTableParameterivEXT( GLenum target, GLenum pname, GLint *params );

#endif /* GL_EXT_paletted_texture */



/*
 * 79. GL_EXT_clip_volume_hint
 */
#ifndef GL_EXT_clip_volume_hint
#define GL_EXT_clip_volume_hint 1

#define GL_CLIP_VOLUME_CLIPPING_HINT_EXT	0x80F0

#endif /* GL_EXT_clip_volume_hint */



/*
 * 97. GL_EXT_compiled_vertex_array
 */
#ifndef GL_EXT_compiled_vertex_array
#define GL_EXT_compiled_vertex_array 1

#define GL_ARRAY_ELEMENT_LOCK_FIRST_EXT		0x81A8
#define GL_ARRAY_ELEMENT_LOCK_COUNT_EXT		0x81A9

GLAPI void GLAPIENTRY _mesa_LockArraysEXT( GLint first, GLsizei count );
GLAPI void GLAPIENTRY _mesa_UnlockArraysEXT( void );

#endif /* GL_EXT_compiled_vertex_array */

/*
 * 137. GL_HP_occlusion_test
 */
#ifndef GL_HP_occlusion_test
#define GL_HP_occlusion_test 1

#define GL_OCCLUSION_TEST_HP                    0x8165
#define GL_OCCLUSION_TEST_RESULT_HP             0x8166

#endif /* GL_HP_occlusion_test */


/*
 * 141. GL_EXT_shared_texture_palette (req's GL_EXT_paletted_texture)
 */
#ifndef GL_EXT_shared_texture_palette
#define GL_EXT_shared_texture_palette 1

#define GL_SHARED_TEXTURE_PALETTE_EXT		0x81FB

#endif /* GL_EXT_shared_texture_palette */



/*
 * 176. GL_EXT_stencil_wrap
 */
#ifndef GL_EXT_stencil_wrap
#define GL_EXT_stencil_wrap 1

#define GL_INCR_WRAP_EXT			0x8507
#define GL_DECR_WRAP_EXT			0x8508

#endif /* GL_EXT_stencil_wrap */



/*
 * 179. GL_NV_texgen_reflection
 */
#ifndef GL_NV_texgen_reflection
#define GL_NV_texgen_reflection 1

#define GL_NORMAL_MAP_NV			0x8511
#define GL_REFLECTION_MAP_NV			0x8512

#endif /* GL_NV_texgen_reflection */



/*
 * 185. GL_EXT_texture_env_add
 */
#ifndef GL_EXT_texture_env_add
#define GL_EXT_texture_env_add 1

/* No new tokens or functions */

#endif /* GL_EXT_texture_env_add */





/*
 * 197. GL_MESA_window_pos
 */
#ifndef GL_MESA_window_pos
#define GL_MESA_window_pos 1

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

#endif /* GL_MESA_window_pos */



/*
 * 196. GL_MESA_resize_bufffers
 */
#ifndef GL_MESA_resize_bufffers
#define GL_MESA_resize_buffers 1

GLAPI void GLAPIENTRY _mesa_ResizeBuffersMESA( void );

#endif /* GL_MESA_resize_bufffers */



/*
 * 220. GL_EXT_texture_env_dot3
 */
#ifndef GL_EXT_texture_env_dot3
#define GL_EXT_texture_env_dot3 1

#define GL_DOT3_RGB_EXT				0x8740
#define GL_DOT3_RGBA_EXT			0x8741

#endif /* GL_EXT_texture_env_dot3 */


#else  /* GL_GLEXT_LEGACY */

#include <GL/glext.h>

#endif  /* GL_GLEXT_LEGACY */



/**********************************************************************
 * Begin system-specific stuff
 */
#if defined(__BEOS__) || defined(__QUICKDRAW__)
#pragma export off
#endif

#if defined(macintosh) && PRAGMA_IMPORT_SUPPORTED
#pragma import off
#endif

/*
 * End system-specific stuff
 **********************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* __gl_h_ */
