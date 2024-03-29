/* drm_scatter.h -- IOCTLs to manage scatter/gather memory -*- linux-c -*-
 * Created: Mon Dec 18 23:20:54 2000 by gareth@valinux.com
 *
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
 *   Gareth Hughes <gareth@valinux.com>
 */

#define __NO_VERSION__
#include <linux/config.h>
#include <linux/vmalloc.h>
#include "drmP.h"

#define DEBUG_SCATTER 0

void DRM(sg_cleanup)( drm_sg_mem_t *entry )
{
	struct page *page;
	int i;

	for ( i = 0 ; i < entry->pages ; i++ ) {
		page = entry->pagelist[i];
		if ( page )
			ClearPageReserved( page );
	}

	vfree( entry->virtual );

	DRM(free)( entry->pagelist,
		  entry->pages * sizeof(*entry->pagelist),
		  DRM_MEM_PAGES );
	DRM(free)( entry,
		  sizeof(*entry),
		  DRM_MEM_SGLISTS );
}

int DRM(sg_alloc)( struct inode *inode, struct file *filp,
		   unsigned int cmd, unsigned long arg )
{
	drm_file_t *priv = filp->private_data;
	drm_device_t *dev = priv->dev;
	drm_scatter_gather_t request;
	drm_sg_mem_t *entry;
	unsigned long pages, i, j;
	pgd_t *pgd;
	pmd_t *pmd;
	pte_t *pte;

	DRM_DEBUG( "%s\n", __FUNCTION__ );

	if ( dev->sg )
		return -EINVAL;

	if ( copy_from_user( &request,
			     (drm_scatter_gather_t *)arg,
			     sizeof(request) ) )
		return -EFAULT;

	entry = DRM(alloc)( sizeof(*entry), DRM_MEM_SGLISTS );
	if ( !entry )
		return -ENOMEM;

   	memset( entry, 0, sizeof(*entry) );

	pages = (request.size + PAGE_SIZE - 1) / PAGE_SIZE;
	DRM_DEBUG( "sg size=%ld pages=%ld\n", request.size, pages );

	entry->pages = pages;
	entry->pagelist = DRM(alloc)( pages * sizeof(*entry->pagelist),
				     DRM_MEM_PAGES );
	if ( !entry->pagelist ) {
		DRM(free)( entry, sizeof(*entry), DRM_MEM_SGLISTS );
		return -ENOMEM;
	}

	entry->virtual = vmalloc_32( pages << PAGE_SHIFT );
	if ( !entry->virtual ) {
		DRM(free)( entry->pagelist,
			  entry->pages * sizeof(*entry->pagelist),
			  DRM_MEM_PAGES );
		DRM(free)( entry,
			  sizeof(*entry),
			  DRM_MEM_SGLISTS );
		return -ENOMEM;
	}

	/* This also forces the mapping of COW pages, so our page list
	 * will be valid.  Please don't remove it...
	 */
	memset( entry->virtual, 0, pages << PAGE_SHIFT );

	entry->handle = (unsigned long)entry->virtual;

	DRM_DEBUG( "sg alloc handle  = %08lx\n", entry->handle );
	DRM_DEBUG( "sg alloc virtual = %p\n", entry->virtual );

	for ( i = entry->handle, j = 0 ; j < pages ; i += PAGE_SIZE, j++ ) {
		pgd = pgd_offset_k( i );
		if ( !pgd_present( *pgd ) )
			goto failed;

		pmd = pmd_offset( pgd, i );
		if ( !pmd_present( *pmd ) )
			goto failed;

		pte = pte_offset( pmd, i );
		if ( !pte_present( *pte ) )
			goto failed;

		entry->pagelist[j] = pte_page( *pte );

		SetPageReserved( entry->pagelist[j] );
	}

	request.handle = entry->handle;

	if ( copy_to_user( (drm_scatter_gather_t *)arg,
			   &request,
			   sizeof(request) ) ) {
		DRM(sg_cleanup)( entry );
		return -EFAULT;
	}

	dev->sg = entry;

#if DEBUG_SCATTER
	/* Verify that each page points to its virtual address, and vice
	 * versa.
	 */
	{
	int error = 0;

	for ( i = 0 ; i < pages ; i++ ) {
		unsigned long *tmp;

		tmp = (unsigned long *)entry->pagelist[i]->virtual;
		for ( j = 0 ;
		      j < PAGE_SIZE / sizeof(unsigned long) ;
		      j++, tmp++ ) {
			*tmp = 0xcafebabe;
		}
		tmp = (unsigned long *)((u8 *)entry->virtual +
					(PAGE_SIZE * i));
		for( j = 0 ;
		     j < PAGE_SIZE / sizeof(unsigned long) ;
		     j++, tmp++ ) {
			if ( *tmp != 0xcafebabe && error == 0 ) {
				error = 1;
				DRM_ERROR( "Scatter allocation error, "
					   "pagelist does not match "
					   "virtual mapping\n" );
			}
		}
		tmp = (unsigned long *)entry->pagelist[i]->virtual;
		for(j = 0 ;
		    j < PAGE_SIZE / sizeof(unsigned long) ;
		    j++, tmp++) {
			*tmp = 0;
		}
	}
	if (error == 0)
		DRM_ERROR( "Scatter allocation matches pagelist\n" );
	}
#endif

	return 0;

 failed:
	DRM(sg_cleanup)( entry );
	return -ENOMEM;
}

int DRM(sg_free)( struct inode *inode, struct file *filp,
		 unsigned int cmd, unsigned long arg )
{
	drm_file_t *priv = filp->private_data;
	drm_device_t *dev = priv->dev;
	drm_scatter_gather_t request;
	drm_sg_mem_t *entry;

	if ( copy_from_user( &request,
			     (drm_scatter_gather_t *)arg,
			     sizeof(request) ) )
		return -EFAULT;

	entry = dev->sg;
	dev->sg = NULL;

	if ( !entry || entry->handle != request.handle )
		return -EINVAL;

	DRM_DEBUG( "sg free virtual  = %p\n", entry->virtual );

	DRM(sg_cleanup)( entry );

	return 0;
}
