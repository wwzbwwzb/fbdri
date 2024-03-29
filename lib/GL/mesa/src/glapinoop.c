
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


/*
 * This is part of the reusable GL dispather, see glapi.c for details.
 */


#include "glheader.h"
#include "glapi.h"
#include "glapinoop.h"
#include "glapitable.h"


static GLboolean WarnFlag = GL_FALSE;


void
_glapi_noop_enable_warnings(GLboolean enable)
{
   WarnFlag = enable;
}


static GLboolean
warn(void)
{
   if (WarnFlag || getenv("MESA_DEBUG") || getenv("LIBGL_DEBUG"))
      return GL_TRUE;
   else
      return GL_FALSE;
}


#define KEYWORD1 static
#define KEYWORD2
#define NAME(func)  NoOp##func

#define F stderr

#define DISPATCH(func, args, msg)			\
   if (warn()) {					\
      fprintf(stderr, "GL User Error: calling ");	\
      fprintf msg;					\
      fprintf(stderr, " without a current context\n");	\
   }

#define RETURN_DISPATCH(func, args, msg)		\
   if (warn()) {					\
      fprintf(stderr, "GL User Error: calling ");	\
      fprintf msg;					\
      fprintf(stderr, " without a current context\n");	\
   }							\
   return 0

#include "glapitemp.h"



static int
NoOpGeneric(void)
{
   if (warn()) {
      fprintf(stderr, "GL User Error: calling extension function without a current context\n");
   }
   return 0;
}


void *__glapi_noop_table[] = {
   (void *) NoOpNewList,
   (void *) NoOpEndList,
   (void *) NoOpCallList,
   (void *) NoOpCallLists,
   (void *) NoOpDeleteLists,
   (void *) NoOpGenLists,
   (void *) NoOpListBase,
   (void *) NoOpBegin,
   (void *) NoOpBitmap,
   (void *) NoOpColor3b,
   (void *) NoOpColor3bv,
   (void *) NoOpColor3d,
   (void *) NoOpColor3dv,
   (void *) NoOpColor3f,
   (void *) NoOpColor3fv,
   (void *) NoOpColor3i,
   (void *) NoOpColor3iv,
   (void *) NoOpColor3s,
   (void *) NoOpColor3sv,
   (void *) NoOpColor3ub,
   (void *) NoOpColor3ubv,
   (void *) NoOpColor3ui,
   (void *) NoOpColor3uiv,
   (void *) NoOpColor3us,
   (void *) NoOpColor3usv,
   (void *) NoOpColor4b,
   (void *) NoOpColor4bv,
   (void *) NoOpColor4d,
   (void *) NoOpColor4dv,
   (void *) NoOpColor4f,
   (void *) NoOpColor4fv,
   (void *) NoOpColor4i,
   (void *) NoOpColor4iv,
   (void *) NoOpColor4s,
   (void *) NoOpColor4sv,
   (void *) NoOpColor4ub,
   (void *) NoOpColor4ubv,
   (void *) NoOpColor4ui,
   (void *) NoOpColor4uiv,
   (void *) NoOpColor4us,
   (void *) NoOpColor4usv,
   (void *) NoOpEdgeFlag,
   (void *) NoOpEdgeFlagv,
   (void *) NoOpEnd,
   (void *) NoOpIndexd,
   (void *) NoOpIndexdv,
   (void *) NoOpIndexf,
   (void *) NoOpIndexfv,
   (void *) NoOpIndexi,
   (void *) NoOpIndexiv,
   (void *) NoOpIndexs,
   (void *) NoOpIndexsv,
   (void *) NoOpNormal3b,
   (void *) NoOpNormal3bv,
   (void *) NoOpNormal3d,
   (void *) NoOpNormal3dv,
   (void *) NoOpNormal3f,
   (void *) NoOpNormal3fv,
   (void *) NoOpNormal3i,
   (void *) NoOpNormal3iv,
   (void *) NoOpNormal3s,
   (void *) NoOpNormal3sv,
   (void *) NoOpRasterPos2d,
   (void *) NoOpRasterPos2dv,
   (void *) NoOpRasterPos2f,
   (void *) NoOpRasterPos2fv,
   (void *) NoOpRasterPos2i,
   (void *) NoOpRasterPos2iv,
   (void *) NoOpRasterPos2s,
   (void *) NoOpRasterPos2sv,
   (void *) NoOpRasterPos3d,
   (void *) NoOpRasterPos3dv,
   (void *) NoOpRasterPos3f,
   (void *) NoOpRasterPos3fv,
   (void *) NoOpRasterPos3i,
   (void *) NoOpRasterPos3iv,
   (void *) NoOpRasterPos3s,
   (void *) NoOpRasterPos3sv,
   (void *) NoOpRasterPos4d,
   (void *) NoOpRasterPos4dv,
   (void *) NoOpRasterPos4f,
   (void *) NoOpRasterPos4fv,
   (void *) NoOpRasterPos4i,
   (void *) NoOpRasterPos4iv,
   (void *) NoOpRasterPos4s,
   (void *) NoOpRasterPos4sv,
   (void *) NoOpRectd,
   (void *) NoOpRectdv,
   (void *) NoOpRectf,
   (void *) NoOpRectfv,
   (void *) NoOpRecti,
   (void *) NoOpRectiv,
   (void *) NoOpRects,
   (void *) NoOpRectsv,
   (void *) NoOpTexCoord1d,
   (void *) NoOpTexCoord1dv,
   (void *) NoOpTexCoord1f,
   (void *) NoOpTexCoord1fv,
   (void *) NoOpTexCoord1i,
   (void *) NoOpTexCoord1iv,
   (void *) NoOpTexCoord1s,
   (void *) NoOpTexCoord1sv,
   (void *) NoOpTexCoord2d,
   (void *) NoOpTexCoord2dv,
   (void *) NoOpTexCoord2f,
   (void *) NoOpTexCoord2fv,
   (void *) NoOpTexCoord2i,
   (void *) NoOpTexCoord2iv,
   (void *) NoOpTexCoord2s,
   (void *) NoOpTexCoord2sv,
   (void *) NoOpTexCoord3d,
   (void *) NoOpTexCoord3dv,
   (void *) NoOpTexCoord3f,
   (void *) NoOpTexCoord3fv,
   (void *) NoOpTexCoord3i,
   (void *) NoOpTexCoord3iv,
   (void *) NoOpTexCoord3s,
   (void *) NoOpTexCoord3sv,
   (void *) NoOpTexCoord4d,
   (void *) NoOpTexCoord4dv,
   (void *) NoOpTexCoord4f,
   (void *) NoOpTexCoord4fv,
   (void *) NoOpTexCoord4i,
   (void *) NoOpTexCoord4iv,
   (void *) NoOpTexCoord4s,
   (void *) NoOpTexCoord4sv,
   (void *) NoOpVertex2d,
   (void *) NoOpVertex2dv,
   (void *) NoOpVertex2f,
   (void *) NoOpVertex2fv,
   (void *) NoOpVertex2i,
   (void *) NoOpVertex2iv,
   (void *) NoOpVertex2s,
   (void *) NoOpVertex2sv,
   (void *) NoOpVertex3d,
   (void *) NoOpVertex3dv,
   (void *) NoOpVertex3f,
   (void *) NoOpVertex3fv,
   (void *) NoOpVertex3i,
   (void *) NoOpVertex3iv,
   (void *) NoOpVertex3s,
   (void *) NoOpVertex3sv,
   (void *) NoOpVertex4d,
   (void *) NoOpVertex4dv,
   (void *) NoOpVertex4f,
   (void *) NoOpVertex4fv,
   (void *) NoOpVertex4i,
   (void *) NoOpVertex4iv,
   (void *) NoOpVertex4s,
   (void *) NoOpVertex4sv,
   (void *) NoOpClipPlane,
   (void *) NoOpColorMaterial,
   (void *) NoOpCullFace,
   (void *) NoOpFogf,
   (void *) NoOpFogfv,
   (void *) NoOpFogi,
   (void *) NoOpFogiv,
   (void *) NoOpFrontFace,
   (void *) NoOpHint,
   (void *) NoOpLightf,
   (void *) NoOpLightfv,
   (void *) NoOpLighti,
   (void *) NoOpLightiv,
   (void *) NoOpLightModelf,
   (void *) NoOpLightModelfv,
   (void *) NoOpLightModeli,
   (void *) NoOpLightModeliv,
   (void *) NoOpLineStipple,
   (void *) NoOpLineWidth,
   (void *) NoOpMaterialf,
   (void *) NoOpMaterialfv,
   (void *) NoOpMateriali,
   (void *) NoOpMaterialiv,
   (void *) NoOpPointSize,
   (void *) NoOpPolygonMode,
   (void *) NoOpPolygonStipple,
   (void *) NoOpScissor,
   (void *) NoOpShadeModel,
   (void *) NoOpTexParameterf,
   (void *) NoOpTexParameterfv,
   (void *) NoOpTexParameteri,
   (void *) NoOpTexParameteriv,
   (void *) NoOpTexImage1D,
   (void *) NoOpTexImage2D,
   (void *) NoOpTexEnvf,
   (void *) NoOpTexEnvfv,
   (void *) NoOpTexEnvi,
   (void *) NoOpTexEnviv,
   (void *) NoOpTexGend,
   (void *) NoOpTexGendv,
   (void *) NoOpTexGenf,
   (void *) NoOpTexGenfv,
   (void *) NoOpTexGeni,
   (void *) NoOpTexGeniv,
   (void *) NoOpFeedbackBuffer,
   (void *) NoOpSelectBuffer,
   (void *) NoOpRenderMode,
   (void *) NoOpInitNames,
   (void *) NoOpLoadName,
   (void *) NoOpPassThrough,
   (void *) NoOpPopName,
   (void *) NoOpPushName,
   (void *) NoOpDrawBuffer,
   (void *) NoOpClear,
   (void *) NoOpClearAccum,
   (void *) NoOpClearIndex,
   (void *) NoOpClearColor,
   (void *) NoOpClearStencil,
   (void *) NoOpClearDepth,
   (void *) NoOpStencilMask,
   (void *) NoOpColorMask,
   (void *) NoOpDepthMask,
   (void *) NoOpIndexMask,
   (void *) NoOpAccum,
   (void *) NoOpDisable,
   (void *) NoOpEnable,
   (void *) NoOpFinish,
   (void *) NoOpFlush,
   (void *) NoOpPopAttrib,
   (void *) NoOpPushAttrib,
   (void *) NoOpMap1d,
   (void *) NoOpMap1f,
   (void *) NoOpMap2d,
   (void *) NoOpMap2f,
   (void *) NoOpMapGrid1d,
   (void *) NoOpMapGrid1f,
   (void *) NoOpMapGrid2d,
   (void *) NoOpMapGrid2f,
   (void *) NoOpEvalCoord1d,
   (void *) NoOpEvalCoord1dv,
   (void *) NoOpEvalCoord1f,
   (void *) NoOpEvalCoord1fv,
   (void *) NoOpEvalCoord2d,
   (void *) NoOpEvalCoord2dv,
   (void *) NoOpEvalCoord2f,
   (void *) NoOpEvalCoord2fv,
   (void *) NoOpEvalMesh1,
   (void *) NoOpEvalPoint1,
   (void *) NoOpEvalMesh2,
   (void *) NoOpEvalPoint2,
   (void *) NoOpAlphaFunc,
   (void *) NoOpBlendFunc,
   (void *) NoOpLogicOp,
   (void *) NoOpStencilFunc,
   (void *) NoOpStencilOp,
   (void *) NoOpDepthFunc,
   (void *) NoOpPixelZoom,
   (void *) NoOpPixelTransferf,
   (void *) NoOpPixelTransferi,
   (void *) NoOpPixelStoref,
   (void *) NoOpPixelStorei,
   (void *) NoOpPixelMapfv,
   (void *) NoOpPixelMapuiv,
   (void *) NoOpPixelMapusv,
   (void *) NoOpReadBuffer,
   (void *) NoOpCopyPixels,
   (void *) NoOpReadPixels,
   (void *) NoOpDrawPixels,
   (void *) NoOpGetBooleanv,
   (void *) NoOpGetClipPlane,
   (void *) NoOpGetDoublev,
   (void *) NoOpGetError,
   (void *) NoOpGetFloatv,
   (void *) NoOpGetIntegerv,
   (void *) NoOpGetLightfv,
   (void *) NoOpGetLightiv,
   (void *) NoOpGetMapdv,
   (void *) NoOpGetMapfv,
   (void *) NoOpGetMapiv,
   (void *) NoOpGetMaterialfv,
   (void *) NoOpGetMaterialiv,
   (void *) NoOpGetPixelMapfv,
   (void *) NoOpGetPixelMapuiv,
   (void *) NoOpGetPixelMapusv,
   (void *) NoOpGetPolygonStipple,
   (void *) NoOpGetString,
   (void *) NoOpGetTexEnvfv,
   (void *) NoOpGetTexEnviv,
   (void *) NoOpGetTexGendv,
   (void *) NoOpGetTexGenfv,
   (void *) NoOpGetTexGeniv,
   (void *) NoOpGetTexImage,
   (void *) NoOpGetTexParameterfv,
   (void *) NoOpGetTexParameteriv,
   (void *) NoOpGetTexLevelParameterfv,
   (void *) NoOpGetTexLevelParameteriv,
   (void *) NoOpIsEnabled,
   (void *) NoOpIsList,
   (void *) NoOpDepthRange,
   (void *) NoOpFrustum,
   (void *) NoOpLoadIdentity,
   (void *) NoOpLoadMatrixf,
   (void *) NoOpLoadMatrixd,
   (void *) NoOpMatrixMode,
   (void *) NoOpMultMatrixf,
   (void *) NoOpMultMatrixd,
   (void *) NoOpOrtho,
   (void *) NoOpPopMatrix,
   (void *) NoOpPushMatrix,
   (void *) NoOpRotated,
   (void *) NoOpRotatef,
   (void *) NoOpScaled,
   (void *) NoOpScalef,
   (void *) NoOpTranslated,
   (void *) NoOpTranslatef,
   (void *) NoOpViewport,
   /* 1.1 */
   (void *) NoOpArrayElement,
   (void *) NoOpBindTexture,
   (void *) NoOpColorPointer,
   (void *) NoOpDisableClientState,
   (void *) NoOpDrawArrays,
   (void *) NoOpDrawElements,
   (void *) NoOpEdgeFlagPointer,
   (void *) NoOpEnableClientState,
   (void *) NoOpIndexPointer,
   (void *) NoOpIndexub,
   (void *) NoOpIndexubv,
   (void *) NoOpInterleavedArrays,
   (void *) NoOpNormalPointer,
   (void *) NoOpPolygonOffset,
   (void *) NoOpTexCoordPointer,
   (void *) NoOpVertexPointer,
   (void *) NoOpAreTexturesResident,
   (void *) NoOpCopyTexImage1D,
   (void *) NoOpCopyTexImage2D,
   (void *) NoOpCopyTexSubImage1D,
   (void *) NoOpCopyTexSubImage2D,
   (void *) NoOpDeleteTextures,
   (void *) NoOpGenTextures,
   (void *) NoOpGetPointerv,
   (void *) NoOpIsTexture,
   (void *) NoOpPrioritizeTextures,
   (void *) NoOpTexSubImage1D,
   (void *) NoOpTexSubImage2D,
   (void *) NoOpPopClientAttrib,
   (void *) NoOpPushClientAttrib,
   /* 1.2 */
   (void *) NoOpBlendColor,
   (void *) NoOpBlendEquation,
   (void *) NoOpDrawRangeElements,
   (void *) NoOpColorTable,
   (void *) NoOpColorTableParameterfv,
   (void *) NoOpColorTableParameteriv,
   (void *) NoOpCopyColorTable,
   (void *) NoOpGetColorTable,
   (void *) NoOpGetColorTableParameterfv,
   (void *) NoOpGetColorTableParameteriv,
   (void *) NoOpColorSubTable,
   (void *) NoOpCopyColorSubTable,
   (void *) NoOpConvolutionFilter1D,
   (void *) NoOpConvolutionFilter2D,
   (void *) NoOpConvolutionParameterf,
   (void *) NoOpConvolutionParameterfv,
   (void *) NoOpConvolutionParameteri,
   (void *) NoOpConvolutionParameteriv,
   (void *) NoOpCopyConvolutionFilter1D,
   (void *) NoOpCopyConvolutionFilter2D,
   (void *) NoOpGetConvolutionFilter,
   (void *) NoOpGetConvolutionParameterfv,
   (void *) NoOpGetConvolutionParameteriv,
   (void *) NoOpGetSeparableFilter,
   (void *) NoOpSeparableFilter2D,
   (void *) NoOpGetHistogram,
   (void *) NoOpGetHistogramParameterfv,
   (void *) NoOpGetHistogramParameteriv,
   (void *) NoOpGetMinmax,
   (void *) NoOpGetMinmaxParameterfv,
   (void *) NoOpGetMinmaxParameteriv,
   (void *) NoOpHistogram,
   (void *) NoOpMinmax,
   (void *) NoOpResetHistogram,
   (void *) NoOpResetMinmax,
   (void *) NoOpTexImage3D,
   (void *) NoOpTexSubImage3D,
   (void *) NoOpCopyTexSubImage3D,
   /* GL_ARB_multitexture */
   (void *) NoOpActiveTextureARB,
   (void *) NoOpClientActiveTextureARB,
   (void *) NoOpMultiTexCoord1dARB,
   (void *) NoOpMultiTexCoord1dvARB,
   (void *) NoOpMultiTexCoord1fARB,
   (void *) NoOpMultiTexCoord1fvARB,
   (void *) NoOpMultiTexCoord1iARB,
   (void *) NoOpMultiTexCoord1ivARB,
   (void *) NoOpMultiTexCoord1sARB,
   (void *) NoOpMultiTexCoord1svARB,
   (void *) NoOpMultiTexCoord2dARB,
   (void *) NoOpMultiTexCoord2dvARB,
   (void *) NoOpMultiTexCoord2fARB,
   (void *) NoOpMultiTexCoord2fvARB,
   (void *) NoOpMultiTexCoord2iARB,
   (void *) NoOpMultiTexCoord2ivARB,
   (void *) NoOpMultiTexCoord2sARB,
   (void *) NoOpMultiTexCoord2svARB,
   (void *) NoOpMultiTexCoord3dARB,
   (void *) NoOpMultiTexCoord3dvARB,
   (void *) NoOpMultiTexCoord3fARB,
   (void *) NoOpMultiTexCoord3fvARB,
   (void *) NoOpMultiTexCoord3iARB,
   (void *) NoOpMultiTexCoord3ivARB,
   (void *) NoOpMultiTexCoord3sARB,
   (void *) NoOpMultiTexCoord3svARB,
   (void *) NoOpMultiTexCoord4dARB,
   (void *) NoOpMultiTexCoord4dvARB,
   (void *) NoOpMultiTexCoord4fARB,
   (void *) NoOpMultiTexCoord4fvARB,
   (void *) NoOpMultiTexCoord4iARB,
   (void *) NoOpMultiTexCoord4ivARB,
   (void *) NoOpMultiTexCoord4sARB,
   (void *) NoOpMultiTexCoord4svARB,
   /* GL_ARB_transpose_matrix */
   (void *) NoOpLoadTransposeMatrixfARB,
   (void *) NoOpLoadTransposeMatrixdARB,
   (void *) NoOpMultTransposeMatrixfARB,
   (void *) NoOpMultTransposeMatrixdARB,
   /* GL_ARB_multisample */
   (void *) NoOpSampleCoverageARB,
   (void *) NoOpSamplePassARB,
   /* GL_EXT_blend_color */
   /* GL_EXT_polygon_offset */
   (void *) NoOpPolygonOffsetEXT,
   /* GL_EXT_texture3D */
   /* GL_EXT_subtexture */
   /* GL_SGIS_texture_filter4 */
   (void *) NoOpGetTexFilterFuncSGIS,
   (void *) NoOpTexFilterFuncSGIS,
   /* GL_EXT_subtexture */
   /* GL_EXT_copy_texture */
   /* GL_EXT_histogram */
   (void *) NoOpGetHistogramEXT,
   (void *) NoOpGetHistogramParameterfvEXT,
   (void *) NoOpGetHistogramParameterivEXT,
   (void *) NoOpGetMinmaxEXT,
   (void *) NoOpGetMinmaxParameterfvEXT,
   (void *) NoOpGetMinmaxParameterivEXT,
   /* GL_EXT_convolution */
   (void *) NoOpGetConvolutionFilterEXT,
   (void *) NoOpGetConvolutionParameterfvEXT,
   (void *) NoOpGetConvolutionParameterivEXT,
   (void *) NoOpGetSeparableFilterEXT,
   /* GL_SGI_color_table */
   (void *) NoOpGetColorTableSGI,
   (void *) NoOpGetColorTableParameterfvSGI,
   (void *) NoOpGetColorTableParameterivSGI,
   /* GL_SGIX_pixel_texture */
   (void *) NoOpPixelTexGenSGIX,
   /* GL_SGIS_pixel_texture */
   (void *) NoOpPixelTexGenParameteriSGIS,
   (void *) NoOpPixelTexGenParameterivSGIS,
   (void *) NoOpPixelTexGenParameterfSGIS,
   (void *) NoOpPixelTexGenParameterfvSGIS,
   (void *) NoOpGetPixelTexGenParameterivSGIS,
   (void *) NoOpGetPixelTexGenParameterfvSGIS,
   /* GL_SGIS_texture4D */
   (void *) NoOpTexImage4DSGIS,
   (void *) NoOpTexSubImage4DSGIS,
   /* GL_EXT_texture_object */
   (void *) NoOpAreTexturesResidentEXT,
   (void *) NoOpGenTexturesEXT,
   (void *) NoOpIsTextureEXT,
   /* GL_SGIS_detail_texture */
   (void *) NoOpDetailTexFuncSGIS,
   (void *) NoOpGetDetailTexFuncSGIS,
   /* GL_SGIS_sharpen_texture */
   (void *) NoOpSharpenTexFuncSGIS,
   (void *) NoOpGetSharpenTexFuncSGIS,
   /* GL_SGIS_multisample */
   (void *) NoOpSampleMaskSGIS,
   (void *) NoOpSamplePatternSGIS,
   /* GL_EXT_vertex_array */
   (void *) NoOpColorPointerEXT,
   (void *) NoOpEdgeFlagPointerEXT,
   (void *) NoOpIndexPointerEXT,
   (void *) NoOpNormalPointerEXT,
   (void *) NoOpTexCoordPointerEXT,
   (void *) NoOpVertexPointerEXT,
   /* GL_EXT_blend_minmax */
   /* GL_SGIX_sprite */
   (void *) NoOpSpriteParameterfSGIX,
   (void *) NoOpSpriteParameterfvSGIX,
   (void *) NoOpSpriteParameteriSGIX,
   (void *) NoOpSpriteParameterivSGIX,
   /* GL_EXT_point_parameters */
   (void *) NoOpPointParameterfEXT,
   (void *) NoOpPointParameterfvEXT,
   /* GL_SGIX_instruments */
   (void *) NoOpGetInstrumentsSGIX,
   (void *) NoOpInstrumentsBufferSGIX,
   (void *) NoOpPollInstrumentsSGIX,
   (void *) NoOpReadInstrumentsSGIX,
   (void *) NoOpStartInstrumentsSGIX,
   (void *) NoOpStopInstrumentsSGIX,
   /* GL_SGIX_framezoom */
   (void *) NoOpFrameZoomSGIX,
   /* GL_SGIX_tag_sample_buffer */
   (void *) NoOpTagSampleBufferSGIX,
   /* GL_SGIX_reference_plane */
   (void *) NoOpReferencePlaneSGIX,
   /* GL_SGIX_flush_raster */
   (void *) NoOpFlushRasterSGIX,
   /* GL_SGIX_list_priority */
   (void *) NoOpGetListParameterfvSGIX,
   (void *) NoOpGetListParameterivSGIX,
   (void *) NoOpListParameterfSGIX,
   (void *) NoOpListParameterfvSGIX,
   (void *) NoOpListParameteriSGIX,
   (void *) NoOpListParameterivSGIX,
   /* GL_SGIX_fragment_lighting */
   (void *) NoOpFragmentColorMaterialSGIX,
   (void *) NoOpFragmentLightfSGIX,
   (void *) NoOpFragmentLightfvSGIX,
   (void *) NoOpFragmentLightiSGIX,
   (void *) NoOpFragmentLightivSGIX,
   (void *) NoOpFragmentLightModelfSGIX,
   (void *) NoOpFragmentLightModelfvSGIX,
   (void *) NoOpFragmentLightModeliSGIX,
   (void *) NoOpFragmentLightModelivSGIX,
   (void *) NoOpFragmentMaterialfSGIX,
   (void *) NoOpFragmentMaterialfvSGIX,
   (void *) NoOpFragmentMaterialiSGIX,
   (void *) NoOpFragmentMaterialivSGIX,
   (void *) NoOpGetFragmentLightfvSGIX,
   (void *) NoOpGetFragmentLightivSGIX,
   (void *) NoOpGetFragmentMaterialfvSGIX,
   (void *) NoOpGetFragmentMaterialivSGIX,
   (void *) NoOpLightEnviSGIX,
   /* GL_EXT_vertex_weighting */
   (void *) NoOpVertexWeightfEXT,
   (void *) NoOpVertexWeightfvEXT,
   (void *) NoOpVertexWeightPointerEXT,
   /* GL_NV_vertex_array_range */
   (void *) NoOpFlushVertexArrayRangeNV,
   (void *) NoOpVertexArrayRangeNV,
   /* GL_NV_register_combiners */
   (void *) NoOpCombinerParameterfvNV,
   (void *) NoOpCombinerParameterfNV,
   (void *) NoOpCombinerParameterivNV,
   (void *) NoOpCombinerParameteriNV,
   (void *) NoOpCombinerInputNV,
   (void *) NoOpCombinerOutputNV,
   (void *) NoOpFinalCombinerInputNV,
   (void *) NoOpGetCombinerInputParameterfvNV,
   (void *) NoOpGetCombinerInputParameterivNV,
   (void *) NoOpGetCombinerOutputParameterfvNV,
   (void *) NoOpGetCombinerOutputParameterivNV,
   (void *) NoOpGetFinalCombinerInputParameterfvNV,
   (void *) NoOpGetFinalCombinerInputParameterivNV,
   /* GL_MESA_resize_buffers */
   (void *) NoOpResizeBuffersMESA,
   /* GL_MESA_window_pos */
   (void *) NoOpWindowPos2dMESA,
   (void *) NoOpWindowPos2dvMESA,
   (void *) NoOpWindowPos2fMESA,
   (void *) NoOpWindowPos2fvMESA,
   (void *) NoOpWindowPos2iMESA,
   (void *) NoOpWindowPos2ivMESA,
   (void *) NoOpWindowPos2sMESA,
   (void *) NoOpWindowPos2svMESA,
   (void *) NoOpWindowPos3dMESA,
   (void *) NoOpWindowPos3dvMESA,
   (void *) NoOpWindowPos3fMESA,
   (void *) NoOpWindowPos3fvMESA,
   (void *) NoOpWindowPos3iMESA,
   (void *) NoOpWindowPos3ivMESA,
   (void *) NoOpWindowPos3sMESA,
   (void *) NoOpWindowPos3svMESA,
   (void *) NoOpWindowPos4dMESA,
   (void *) NoOpWindowPos4dvMESA,
   (void *) NoOpWindowPos4fMESA,
   (void *) NoOpWindowPos4fvMESA,
   (void *) NoOpWindowPos4iMESA,
   (void *) NoOpWindowPos4ivMESA,
   (void *) NoOpWindowPos4sMESA,
   (void *) NoOpWindowPos4svMESA,
   /* GL_EXT_draw_range_elements */
   (void *) NoOpBlendFuncSeparateEXT,
   /* GL_EXT_index_material */
   (void *) NoOpIndexMaterialEXT,
   /* GL_EXT_index_func */
   (void *) NoOpIndexFuncEXT,
   /* GL_EXT_compiled_vertex_array */
   (void *) NoOpLockArraysEXT,
   (void *) NoOpUnlockArraysEXT,
   /* GL_EXT_cull_vertex */
   (void *) NoOpCullParameterdvEXT,
   (void *) NoOpCullParameterfvEXT,
   /* GL_PGI_misc_hints */
   (void *) NoOpHintPGI,
   /* GL_EXT_fog_coord */
   (void *) NoOpFogCoordfEXT,
   (void *) NoOpFogCoordfvEXT,
   (void *) NoOpFogCoorddEXT,
   (void *) NoOpFogCoorddvEXT,
   (void *) NoOpFogCoordPointerEXT,
   /* GL_EXT_color_table */
   (void *) NoOpGetColorTableEXT,
   (void *) NoOpGetColorTableParameterivEXT,
   (void *) NoOpGetColorTableParameterfvEXT,
   /* GL_3DFX_tbuffer */
   (void *) NoOpTbufferMask3DFX,
   /* GL_ARB_texture_compression */
   (void *) NoOpCompressedTexImage3DARB,
   (void *) NoOpCompressedTexImage2DARB,
   (void *) NoOpCompressedTexImage1DARB,
   (void *) NoOpCompressedTexSubImage3DARB,
   (void *) NoOpCompressedTexSubImage2DARB,
   (void *) NoOpCompressedTexSubImage1DARB,
   (void *) NoOpGetCompressedTexImageARB,
   /* A whole bunch of no-op functions.  These might be called
    * when someone tries to call a dynamically-registered extension
    * function without a current rendering context.
    */
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric,
   (void *) NoOpGeneric
};
