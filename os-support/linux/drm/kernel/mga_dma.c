/* mga_dma.c -- DMA support for mga g200/g400 -*- linux-c -*-
 * Created: Mon Dec 13 01:50:01 1999 by jhartmann@precisioninsight.com
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Rickard E. (Rik) Faith <faith@valinux.com>
 *    Jeff Hartmann <jhartmann@valinux.com>
 *    Keith Whitwell <keithw@valinux.com>
 *
 * Rewritten by:
 *    Gareth Hughes <gareth@valinux.com>
 */

#define __NO_VERSION__
#include "mga.h"
#include "drmP.h"
#include "mga_drv.h"

#include <linux/interrupt.h>	/* For task queue support */
#include <linux/delay.h>

#define MGA_DEFAULT_USEC_TIMEOUT	10000
#define MGA_FREELIST_DEBUG		0


/* ================================================================
 * Engine control
 */

int mga_do_wait_for_idle( drm_mga_private_t *dev_priv )
{
	u32 status = 0;
	int i;
	DRM_DEBUG( "%s\n", __FUNCTION__ );

	for ( i = 0 ; i < dev_priv->usec_timeout ; i++ ) {
		status = MGA_READ( MGA_STATUS ) & MGA_ENGINE_IDLE_MASK;
		if ( status == MGA_ENDPRDMASTS ) {
			MGA_WRITE8( MGA_CRTC_INDEX, 0 );
			return 0;
		}
		udelay( 1 );
	}

#if MGA_DMA_DEBUG
	DRM_ERROR( "failed!\n" );
	DRM_INFO( "   status=0x%08x\n", status );
#endif
	return -EBUSY;
}

int mga_do_dma_idle( drm_mga_private_t *dev_priv )
{
	u32 status = 0;
	int i;
	DRM_DEBUG( "%s\n", __FUNCTION__ );

	for ( i = 0 ; i < dev_priv->usec_timeout ; i++ ) {
		status = MGA_READ( MGA_STATUS ) & MGA_DMA_IDLE_MASK;
		if ( status == MGA_ENDPRDMASTS ) return 0;
		udelay( 1 );
	}

#if MGA_DMA_DEBUG
	DRM_ERROR( "failed! status=0x%08x\n", status );
#endif
	return -EBUSY;
}

int mga_do_dma_reset( drm_mga_private_t *dev_priv )
{
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_primary_buffer_t *primary = &dev_priv->prim;

	DRM_DEBUG( "%s\n", __FUNCTION__ );

	/* The primary DMA stream should look like new right about now.
	 */
	primary->tail = 0;
	primary->space = primary->size;
	primary->last_flush = 0;

	sarea_priv->last_wrap = 0;

	/* FIXME: Reset counters, buffer ages etc...
	 */

	/* FIXME: What else do we need to reinitialize?  WARP stuff?
	 */

	return 0;
}

int mga_do_engine_reset( drm_mga_private_t *dev_priv )
{
	DRM_DEBUG( "%s\n", __FUNCTION__ );

	/* Okay, so we've completely screwed up and locked the engine.
	 * How about we clean up after ourselves?
	 */
	MGA_WRITE( MGA_RST, MGA_SOFTRESET );
	udelay( 15 );				/* Wait at least 10 usecs */
	MGA_WRITE( MGA_RST, 0 );

	/* Initialize the registers that get clobbered by the soft
	 * reset.  Many of the core register values survive a reset,
	 * but the drawing registers are basically all gone.
	 *
	 * 3D clients should probably die after calling this.  The X
	 * server should reset the engine state to known values.
	 */
#if 0
	MGA_WRITE( MGA_PRIMPTR,
		   virt_to_bus((void *)dev_priv->prim.status_page) |
		   MGA_PRIMPTREN0 |
		   MGA_PRIMPTREN1 );
#endif

	MGA_WRITE( MGA_ICLEAR, MGA_SOFTRAPICLR );
	MGA_WRITE( MGA_IEN,    MGA_SOFTRAPIEN );

	/* The primary DMA stream should look like new right about now.
	 */
	mga_do_dma_reset( dev_priv );

	/* This bad boy will never fail.
	 */
	return 0;
}


/* ================================================================
 * Primary DMA stream
 */

void mga_do_dma_flush( drm_mga_private_t *dev_priv )
{
	drm_mga_primary_buffer_t *primary = &dev_priv->prim;
	u32 head, tail;
	DMA_LOCALS;
	DRM_DEBUG( "%s:\n", __FUNCTION__ );

	if ( primary->tail == primary->last_flush ) {
		DRM_DEBUG( "   bailing out...\n" );
		return;
	}

	tail = primary->tail + dev_priv->primary->offset;

	/* We need to pad the stream between flushes, as the card
	 * actually (partially?) reads the first of these commands.
	 * See page 4-16 in the G400 manual, middle of the page or so.
	 */
	BEGIN_DMA( 1 );

	DMA_BLOCK( MGA_DMAPAD,  0x00000000,
		   MGA_DMAPAD,  0x00000000,
		   MGA_DMAPAD,  0x00000000,
		   MGA_DMAPAD,	0x00000000 );

	ADVANCE_DMA();

	primary->last_flush = primary->tail;

	head = MGA_READ( MGA_PRIMADDRESS );

	if ( head <= tail ) {
		primary->space = primary->size - primary->tail;
	} else {
		primary->space = head - tail;
	}

	DRM_DEBUG( "   head = 0x%06lx\n", head - dev_priv->primary->offset );
	DRM_DEBUG( "   tail = 0x%06lx\n", tail - dev_priv->primary->offset );
	DRM_DEBUG( "  space = 0x%06x\n", primary->space );

	mga_flush_write_combine();
	MGA_WRITE( MGA_PRIMEND, tail | MGA_PAGPXFER );

	DRM_DEBUG( "%s: done.\n", __FUNCTION__ );
}

void mga_do_dma_wrap_start( drm_mga_private_t *dev_priv )
{
	drm_mga_primary_buffer_t *primary = &dev_priv->prim;
	u32 head, tail;
	DMA_LOCALS;
	DRM_DEBUG( "%s:\n", __FUNCTION__ );

	BEGIN_DMA_WRAP();

	DMA_BLOCK( MGA_DMAPAD,	0x00000000,
		   MGA_DMAPAD,	0x00000000,
		   MGA_DMAPAD,	0x00000000,
		   MGA_DMAPAD,	0x00000000 );

	ADVANCE_DMA();

	tail = primary->tail + dev_priv->primary->offset;

	primary->tail = 0;
	primary->last_flush = 0;
	primary->last_wrap++;

	head = MGA_READ( MGA_PRIMADDRESS );

	if ( head == dev_priv->primary->offset ) {
		primary->space = primary->size;
	} else {
		primary->space = head - dev_priv->primary->offset;
	}

	DRM_DEBUG( "   head = 0x%06lx\n",
		  head - dev_priv->primary->offset );
	DRM_DEBUG( "   tail = 0x%06x\n", primary->tail );
	DRM_DEBUG( "   wrap = %d\n", primary->last_wrap );
	DRM_DEBUG( "  space = 0x%06x\n", primary->space );

	mga_flush_write_combine();
	MGA_WRITE( MGA_PRIMEND, tail | MGA_PAGPXFER );

	set_bit( 0, &primary->wrapped );
	DRM_DEBUG( "%s: done.\n", __FUNCTION__ );
}

void mga_do_dma_wrap_end( drm_mga_private_t *dev_priv )
{
	drm_mga_primary_buffer_t *primary = &dev_priv->prim;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	u32 head = dev_priv->primary->offset;
	DRM_DEBUG( "%s:\n", __FUNCTION__ );

	sarea_priv->last_wrap++;
	DRM_DEBUG( "   wrap = %d\n", sarea_priv->last_wrap );

	mga_flush_write_combine();
	MGA_WRITE( MGA_PRIMADDRESS, head | MGA_DMA_GENERAL );

	clear_bit( 0, &primary->wrapped );
	DRM_DEBUG( "%s: done.\n", __FUNCTION__ );
}


/* ================================================================
 * Freelist management
 */

#define MGA_BUFFER_USED		~0
#define MGA_BUFFER_FREE		0

#if MGA_FREELIST_DEBUG
static void mga_freelist_print( drm_device_t *dev )
{
	drm_mga_private_t *dev_priv = dev->dev_private;
	drm_mga_freelist_t *entry;

	DRM_INFO( "\n" );
	DRM_INFO( "current dispatch: last=0x%x done=0x%x\n",
		  dev_priv->sarea_priv->last_dispatch,
		  (unsigned int)(MGA_READ( MGA_PRIMADDRESS ) -
				 dev_priv->primary->offset) );
	DRM_INFO( "current freelist:\n" );

	for ( entry = dev_priv->head->next ; entry ; entry = entry->next ) {
		DRM_INFO( "   %p   idx=%2d  age=0x%x 0x%06lx\n",
			  entry, entry->buf->idx, entry->age.head,
			  entry->age.head - dev_priv->primary->offset );
	}
	DRM_INFO( "\n" );
}
#endif

static int mga_freelist_init( drm_device_t *dev )
{
	drm_device_dma_t *dma = dev->dma;
	drm_mga_private_t *dev_priv = dev->dev_private;
	drm_buf_t *buf;
	drm_mga_buf_priv_t *buf_priv;
	drm_mga_freelist_t *entry;
	int i;
	DRM_DEBUG( "%s: count=%d\n",
		   __FUNCTION__, dma->buf_count );

	dev_priv->head = DRM(alloc)( sizeof(drm_mga_freelist_t),
				     DRM_MEM_DRIVER );
	if ( dev_priv->head == NULL )
		return -ENOMEM;

	memset( dev_priv->head, 0, sizeof(drm_mga_freelist_t) );
	SET_AGE( &dev_priv->head->age, MGA_BUFFER_USED, 0 );

	for ( i = 0 ; i < dma->buf_count ; i++ ) {
		buf = dma->buflist[i];
	        buf_priv = buf->dev_private;

		entry = DRM(alloc)( sizeof(drm_mga_freelist_t),
				    DRM_MEM_DRIVER );
		if ( entry == NULL )
			return -ENOMEM;

		memset( entry, 0, sizeof(drm_mga_freelist_t) );

		entry->next = dev_priv->head->next;
		entry->prev = dev_priv->head;
		SET_AGE( &entry->age, MGA_BUFFER_FREE, 0 );
		entry->buf = buf;

		if ( dev_priv->head->next != NULL )
			dev_priv->head->next->prev = entry;
		if ( entry->next == NULL )
			dev_priv->tail = entry;

		buf_priv->list_entry = entry;
		buf_priv->discard = 0;
		buf_priv->dispatched = 0;

		dev_priv->head->next = entry;
	}

	return 0;
}

static void mga_freelist_cleanup( drm_device_t *dev )
{
	drm_mga_private_t *dev_priv = dev->dev_private;
	drm_mga_freelist_t *entry;
	drm_mga_freelist_t *next;
	DRM_DEBUG( "%s\n", __FUNCTION__ );

	entry = dev_priv->head;
	while ( entry ) {
		next = entry->next;
		DRM(free)( entry, sizeof(drm_mga_freelist_t), DRM_MEM_DRIVER );
		entry = next;
	}

	dev_priv->head = dev_priv->tail = NULL;
}

#if 0
/* FIXME: Still needed?
 */
static void mga_freelist_reset( drm_device_t *dev )
{
	drm_device_dma_t *dma = dev->dma;
	drm_buf_t *buf;
	drm_mga_buf_priv_t *buf_priv;
	int i;

	for ( i = 0 ; i < dma->buf_count ; i++ ) {
		buf = dma->buflist[i];
	        buf_priv = buf->dev_private;
		SET_AGE( &buf_priv->list_entry->age,
			 MGA_BUFFER_FREE, 0 );
	}
}
#endif

static drm_buf_t *mga_freelist_get( drm_device_t *dev )
{
	drm_mga_private_t *dev_priv = dev->dev_private;
	drm_mga_freelist_t *next;
	drm_mga_freelist_t *prev;
	drm_mga_freelist_t *tail = dev_priv->tail;
	u32 head, wrap;
	DRM_DEBUG( "%s:\n", __FUNCTION__ );

	head = MGA_READ( MGA_PRIMADDRESS );
	wrap = dev_priv->sarea_priv->last_wrap;

	DRM_DEBUG( "   tail=0x%06lx %d\n",
		   tail->age.head ?
		   tail->age.head - dev_priv->primary->offset : 0,
		   tail->age.wrap );
	DRM_DEBUG( "   head=0x%06lx %d\n",
		   head - dev_priv->primary->offset, wrap );

	if ( TEST_AGE( &tail->age, head, wrap ) ) {
		prev = dev_priv->tail->prev;
		next = dev_priv->tail;
		prev->next = NULL;
		next->prev = next->next = NULL;
		dev_priv->tail = prev;
		SET_AGE( &next->age, MGA_BUFFER_USED, 0 );
		return next->buf;
	}

	DRM_DEBUG( "returning NULL!\n" );
	return NULL;
}

int mga_freelist_put( drm_device_t *dev, drm_buf_t *buf )
{
	drm_mga_private_t *dev_priv = dev->dev_private;
	drm_mga_buf_priv_t *buf_priv = buf->dev_private;
	drm_mga_freelist_t *head, *entry, *prev;

	DRM_DEBUG( "%s: age=0x%06lx wrap=%d\n",
		   __FUNCTION__,
		   buf_priv->list_entry->age.head -
		   dev_priv->primary->offset,
		   buf_priv->list_entry->age.wrap );

	entry = buf_priv->list_entry;
	head = dev_priv->head;

	if ( buf_priv->list_entry->age.head == MGA_BUFFER_USED ) {
		SET_AGE( &entry->age, MGA_BUFFER_FREE, 0 );
		prev = dev_priv->tail;
		prev->next = entry;
		entry->prev = prev;
		entry->next = NULL;
	} else {
		prev = head->next;
		head->next = entry;
		prev->prev = entry;
		entry->prev = head;
		entry->next = prev;
	}

	return 0;
}


/* ================================================================
 * DMA initialization, cleanup
 */

static int mga_do_init_dma( drm_device_t *dev, drm_mga_init_t *init )
{
	drm_mga_private_t *dev_priv;
	struct list_head *list;
	int ret;
	DRM_DEBUG( "%s\n", __FUNCTION__ );

	dev_priv = DRM(alloc)( sizeof(drm_mga_private_t), DRM_MEM_DRIVER );
	if ( !dev_priv )
		return -ENOMEM;
	dev->dev_private = (void *)dev_priv;

	memset( dev_priv, 0, sizeof(drm_mga_private_t) );

	dev_priv->chipset = init->chipset;

	dev_priv->usec_timeout = MGA_DEFAULT_USEC_TIMEOUT;

	if ( init->sgram ) {
		dev_priv->clear_cmd = MGA_DWGCTL_CLEAR | MGA_ATYPE_BLK;
	} else {
		dev_priv->clear_cmd = MGA_DWGCTL_CLEAR | MGA_ATYPE_RSTR;
	}
	dev_priv->maccess	= init->maccess;

	dev_priv->fb_cpp	= init->fb_cpp;
	dev_priv->front_offset	= init->front_offset;
	dev_priv->front_pitch	= init->front_pitch;
	dev_priv->back_offset	= init->back_offset;
	dev_priv->back_pitch	= init->back_pitch;

	dev_priv->depth_cpp	= init->depth_cpp;
	dev_priv->depth_offset	= init->depth_offset;
	dev_priv->depth_pitch	= init->depth_pitch;

	/* FIXME: Need to support AGP textures...
	 */
	dev_priv->texture_offset = init->texture_offset[0];
	dev_priv->texture_size = init->texture_size[0];

	list_for_each( list, &dev->maplist->head ) {
		drm_map_list_t *entry = (drm_map_list_t *)list;
		if ( entry->map &&
		     entry->map->type == _DRM_SHM &&
		     (entry->map->flags & _DRM_CONTAINS_LOCK) ) {
			dev_priv->sarea = entry->map;
 			break;
 		}
 	}

	DRM_FIND_MAP( dev_priv->fb, init->fb_offset );
	DRM_FIND_MAP( dev_priv->mmio, init->mmio_offset );
	DRM_FIND_MAP( dev_priv->status, init->status_offset );

	DRM_FIND_MAP( dev_priv->warp, init->warp_offset );
	DRM_FIND_MAP( dev_priv->primary, init->primary_offset );
	DRM_FIND_MAP( dev_priv->buffers, init->buffers_offset );

	dev_priv->sarea_priv =
		(drm_mga_sarea_t *)((u8 *)dev_priv->sarea->handle +
				    init->sarea_priv_offset);

	DRM_IOREMAP( dev_priv->warp );
	DRM_IOREMAP( dev_priv->primary );
	DRM_IOREMAP( dev_priv->buffers );

	ret = mga_warp_install_microcode( dev );
	if ( ret < 0 ) {
		DRM_ERROR( "failed to install WARP ucode!\n" );
		mga_do_cleanup_dma( dev );
		return ret;
	}

	ret = mga_warp_init( dev );
	if ( ret < 0 ) {
		DRM_ERROR( "failed to init WARP engine!\n" );
		mga_do_cleanup_dma( dev );
		return ret;
	}

	dev_priv->prim.status = (u32 *)dev_priv->status->handle;

	mga_do_wait_for_idle( dev_priv );

	/* Init the primary DMA registers.
	 */
	MGA_WRITE( MGA_PRIMADDRESS,
		   dev_priv->primary->offset | MGA_DMA_GENERAL );
#if 0
	MGA_WRITE( MGA_PRIMPTR,
		   virt_to_bus((void *)dev_priv->prim.status) |
		   MGA_PRIMPTREN0 |	/* Soft trap, SECEND, SETUPEND */
		   MGA_PRIMPTREN1 );	/* DWGSYNC */
#endif

	dev_priv->prim.start = (u8 *)dev_priv->primary->handle;
	dev_priv->prim.end = ((u8 *)dev_priv->primary->handle
			      + dev_priv->primary->size);
	dev_priv->prim.size = dev_priv->primary->size;

	dev_priv->prim.tail = 0;
	dev_priv->prim.space = dev_priv->prim.size;
	dev_priv->prim.wrapped = 0;

	dev_priv->prim.last_flush = 0;
	dev_priv->prim.last_wrap = 0;

	dev_priv->prim.high_mark = 256 * DMA_BLOCK_SIZE;

	spin_lock_init( &dev_priv->prim.list_lock );

	dev_priv->prim.status[0] = dev_priv->primary->offset;
	dev_priv->prim.status[1] = 0;

	dev_priv->sarea_priv->last_wrap = 0;
	dev_priv->sarea_priv->last_frame.head = 0;
	dev_priv->sarea_priv->last_frame.wrap = 0;

	if ( mga_freelist_init( dev ) < 0 ) {
		DRM_ERROR( "could not initialize freelist\n" );
		mga_do_cleanup_dma( dev );
		return -ENOMEM;
	}

	return 0;
}

int mga_do_cleanup_dma( drm_device_t *dev )
{
	DRM_DEBUG( "%s\n", __FUNCTION__ );

	if ( dev->dev_private ) {
		drm_mga_private_t *dev_priv = dev->dev_private;

		DRM_IOREMAPFREE( dev_priv->warp );
		DRM_IOREMAPFREE( dev_priv->primary );
		DRM_IOREMAPFREE( dev_priv->buffers );

		if ( dev_priv->head != NULL ) {
			mga_freelist_cleanup( dev );
		}

		DRM(free)( dev->dev_private, sizeof(drm_mga_private_t),
			   DRM_MEM_DRIVER );
		dev->dev_private = NULL;
	}

	return 0;
}

int mga_dma_init( struct inode *inode, struct file *filp,
		  unsigned int cmd, unsigned long arg )
{
	drm_file_t *priv = filp->private_data;
	drm_device_t *dev = priv->dev;
	drm_mga_init_t init;

	if ( copy_from_user( &init, (drm_mga_init_t *)arg, sizeof(init) ) )
		return -EFAULT;

	switch ( init.func ) {
	case MGA_INIT_DMA:
		return mga_do_init_dma( dev, &init );
	case MGA_CLEANUP_DMA:
		return mga_do_cleanup_dma( dev );
	}

	return -EINVAL;
}


/* ================================================================
 * Primary DMA stream management
 */

int mga_dma_flush( struct inode *inode, struct file *filp,
		   unsigned int cmd, unsigned long arg )
{
	drm_file_t *priv = filp->private_data;
	drm_device_t *dev = priv->dev;
	drm_mga_private_t *dev_priv = (drm_mga_private_t *)dev->dev_private;
	drm_lock_t lock;

	LOCK_TEST_WITH_RETURN( dev );

	if ( copy_from_user( &lock, (drm_lock_t *)arg, sizeof(lock) ) )
		return -EFAULT;

	DRM_DEBUG( "%s: %s%s%s\n",
		   __FUNCTION__,
		   (lock.flags & _DRM_LOCK_FLUSH) ?	"flush, " : "",
		   (lock.flags & _DRM_LOCK_FLUSH_ALL) ?	"flush all, " : "",
		   (lock.flags & _DRM_LOCK_QUIESCENT) ?	"idle, " : "" );

	WRAP_WAIT_WITH_RETURN( dev_priv );

	if ( lock.flags & (_DRM_LOCK_FLUSH | _DRM_LOCK_FLUSH_ALL) ) {
		mga_do_dma_flush( dev_priv );
	}

	if ( lock.flags & _DRM_LOCK_QUIESCENT ) {
#if MGA_DMA_DEBUG
		int ret = mga_do_wait_for_idle( dev_priv );
		if ( ret < 0 )
			DRM_INFO( __FUNCTION__": -EBUSY\n" );
		return ret;
#else
		return mga_do_wait_for_idle( dev_priv );
#endif
	} else {
		return 0;
	}
}

int mga_dma_reset( struct inode *inode, struct file *filp,
		   unsigned int cmd, unsigned long arg )
{
	drm_file_t *priv = filp->private_data;
	drm_device_t *dev = priv->dev;
	drm_mga_private_t *dev_priv = (drm_mga_private_t *)dev->dev_private;

	LOCK_TEST_WITH_RETURN( dev );

	return mga_do_dma_reset( dev_priv );
}


/* ================================================================
 * DMA buffer management
 */

static int mga_dma_get_buffers( drm_device_t *dev, drm_dma_t *d )
{
	drm_buf_t *buf;
	int i;

	for ( i = d->granted_count ; i < d->request_count ; i++ ) {
		buf = mga_freelist_get( dev );
		if ( !buf ) return -EAGAIN;

		buf->pid = current->pid;

		if ( copy_to_user( &d->request_indices[i],
				   &buf->idx, sizeof(buf->idx) ) )
			return -EFAULT;
		if ( copy_to_user( &d->request_sizes[i],
				   &buf->total, sizeof(buf->total) ) )
			return -EFAULT;

		d->granted_count++;
	}
	return 0;
}

int mga_dma_buffers( struct inode *inode, struct file *filp,
		     unsigned int cmd, unsigned long arg )
{
	drm_file_t *priv = filp->private_data;
	drm_device_t *dev = priv->dev;
	drm_device_dma_t *dma = dev->dma;
	drm_mga_private_t *dev_priv = (drm_mga_private_t *)dev->dev_private;
	drm_dma_t d;
	int ret = 0;

	LOCK_TEST_WITH_RETURN( dev );

	if ( copy_from_user( &d, (drm_dma_t *)arg, sizeof(d) ) )
		return -EFAULT;

	/* Please don't send us buffers.
	 */
	if ( d.send_count != 0 ) {
		DRM_ERROR( "Process %d trying to send %d buffers via drmDMA\n",
			   current->pid, d.send_count );
		return -EINVAL;
	}

	/* We'll send you buffers.
	 */
	if ( d.request_count < 0 || d.request_count > dma->buf_count ) {
		DRM_ERROR( "Process %d trying to get %d buffers (of %d max)\n",
			   current->pid, d.request_count, dma->buf_count );
		return -EINVAL;
	}

	WRAP_TEST_WITH_RETURN( dev_priv );

	d.granted_count = 0;

	if ( d.request_count ) {
		ret = mga_dma_get_buffers( dev, &d );
	}

	if ( copy_to_user( (drm_dma_t *)arg, &d, sizeof(d) ) )
		return -EFAULT;

	return ret;
}
