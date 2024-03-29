/* drm_vm.h -- Memory mapping for DRM -*- linux-c -*-
 * Created: Mon Jan  4 08:58:31 1999 by faith@valinux.com
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
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Rickard E. (Rik) Faith <faith@valinux.com>
 *    Gareth Hughes <gareth@valinux.com>
 */

#define __NO_VERSION__
#include "drmP.h"

struct vm_operations_struct   drm_vm_ops = {
	nopage:	 DRM(vm_nopage),
	open:	 DRM(vm_open),
	close:	 DRM(vm_close),
};

struct vm_operations_struct   drm_vm_shm_ops = {
	nopage:	 DRM(vm_shm_nopage),
	open:	 DRM(vm_open),
	close:	 DRM(vm_shm_close),
};

struct vm_operations_struct   drm_vm_dma_ops = {
	nopage:	 DRM(vm_dma_nopage),
	open:	 DRM(vm_open),
	close:	 DRM(vm_close),
};

struct vm_operations_struct   drm_vm_sg_ops = {
	nopage:  DRM(vm_sg_nopage),
	open:    DRM(vm_open),
	close:   DRM(vm_close),
};

#if LINUX_VERSION_CODE < 0x020317
unsigned long DRM(vm_nopage)(struct vm_area_struct *vma,
			     unsigned long address,
			     int write_access)
#else
				/* Return type changed in 2.3.23 */
struct page *DRM(vm_nopage)(struct vm_area_struct *vma,
			    unsigned long address,
			    int write_access)
#endif
{
	return NOPAGE_SIGBUS;		/* Disallow mremap */
}

#if LINUX_VERSION_CODE < 0x020317
unsigned long DRM(vm_shm_nopage)(struct vm_area_struct *vma,
				 unsigned long address,
				 int write_access)
#else
				/* Return type changed in 2.3.23 */
struct page *DRM(vm_shm_nopage)(struct vm_area_struct *vma,
				unsigned long address,
				int write_access)
#endif
{
#if LINUX_VERSION_CODE >= 0x020300
	drm_map_t	 *map	 = (drm_map_t *)vma->vm_private_data;
#else
	drm_map_t	 *map	 = (drm_map_t *)vma->vm_pte;
#endif
	unsigned long	 physical;
	unsigned long	 offset;
	unsigned long	 i;
	pgd_t		 *pgd;
	pmd_t		 *pmd;
	pte_t		 *pte;

	if (address > vma->vm_end) return NOPAGE_SIGBUS; /* Disallow mremap */
	if (!map)    		   return NOPAGE_OOM;  /* Nothing allocated */

	offset	 = address - vma->vm_start;
	i = (unsigned long)map->handle + offset;
	/* We have to walk page tables here because we need large SAREA's, and
	 * they need to be virtually contiguous in kernel space.
	 */
	pgd = pgd_offset_k( i );
	if( !pgd_present( *pgd ) ) return NOPAGE_OOM;
	pmd = pmd_offset( pgd, i );
	if( !pmd_present( *pmd ) ) return NOPAGE_OOM;
	pte = pte_offset( pmd, i );
	if( !pte_present( *pte ) ) return NOPAGE_OOM;
	physical = (unsigned long)pte_page( *pte )->virtual;
	atomic_inc(&virt_to_page(physical)->count); /* Dec. by kernel */

	DRM_DEBUG("0x%08lx => 0x%08lx\n", address, physical);
#if LINUX_VERSION_CODE < 0x020317
	return physical;
#else
	return virt_to_page(physical);
#endif
}

/* Special close routine which deletes map information if we are the last
 * person to close a mapping and its not in the global maplist.
 */

void DRM(vm_shm_close)(struct vm_area_struct *vma)
{
	drm_file_t	*priv	= vma->vm_file->private_data;
	drm_device_t	*dev	= priv->dev;
	drm_vma_entry_t *pt, *prev;
	drm_map_t *map;
	drm_map_list_t *r_list;
	struct list_head *list;
	int found_maps = 0;


return;


printk("vm_shm_close 1\n");
	DRM_DEBUG("0x%08lx,0x%08lx\n",
		  vma->vm_start, vma->vm_end - vma->vm_start);
#if LINUX_VERSION_CODE < 0x020333
	MOD_DEC_USE_COUNT; /* Needed before Linux 2.3.51 */
#endif
	atomic_dec(&dev->vma_count);
printk("vm_shm_close 2\n");

#if LINUX_VERSION_CODE >= 0x020300
	map = vma->vm_private_data;
#else
	map = vma->vm_pte;
#endif

	down(&dev->struct_sem);




printk("vm_shm_close 3\n");
	for (pt = dev->vmalist, prev = NULL; 
		pt;             // Not NULL terminated
		prev = pt, pt = pt->next) {




printk("vm_shm_close 4 %p\n", pt);
printk("vm_shm_close 4.1 %p\n", pt->vma);
printk("vm_shm_close 4.2 %p\n", pt->vma->vm_private_data);
#if LINUX_VERSION_CODE >= 0x020300
		if (pt->vma->vm_private_data == map) found_maps++;
#else
		if (pt->vma->vm_pte == map) found_maps++;
#endif





printk("vm_shm_close 5\n");




		if (pt->vma == vma) {



printk("vm_shm_close 6\n");
			if (prev) {
				prev->next = pt->next;
			} else {
				dev->vmalist = pt->next;
			}
printk("vm_shm_close 7\n");


			DRM(free)(pt, sizeof(*pt), DRM_MEM_VMAS);


printk("vm_shm_close 8\n");


		}
	}



printk("vm_shm_close 9\n");
	/* We were the only map that was found */
	if(found_maps == 1 &&
	   map->flags & _DRM_REMOVABLE) 
	   {
printk("vm_shm_close 10\n");
		/* Check to see if we are in the maplist, if we are not, then
		 * we delete this mappings information.
		 */



		found_maps = 0;
printk("vm_shm_close 11\n");
		list = &dev->maplist->head;
printk("vm_shm_close 12\n");
		list_for_each(list, &dev->maplist->head) {
			r_list = (drm_map_list_t *) list;
			if (r_list->map == map) found_maps++;
		}

printk("vm_shm_close 13\n");
		if(!found_maps) {
printk("vm_shm_close 14\n");
			switch (map->type) {
			case _DRM_REGISTERS:
			case _DRM_FRAME_BUFFER:
#if __REALLY_HAVE_MTRR
				if (map->mtrr >= 0) {
					int retcode;
					retcode = mtrr_del(map->mtrr,
							   map->offset,
							   map->size);
					DRM_DEBUG("mtrr_del = %d\n", retcode);
				}
#endif
				DRM(ioremapfree)(map->handle, map->size);
				break;
			case _DRM_SHM:
				vfree(map->handle);
				break;
			case _DRM_AGP:
			case _DRM_SCATTER_GATHER:
				break;
			}
printk("vm_shm_close 15\n");
			DRM(free)(map, sizeof(*map), DRM_MEM_MAPS);
printk("vm_shm_close 16\n");
		}
	}
printk("vm_shm_close 17\n");
	up(&dev->struct_sem);
printk("vm_shm_close 18\n");
}

#if LINUX_VERSION_CODE < 0x020317
unsigned long DRM(vm_dma_nopage)(struct vm_area_struct *vma,
				 unsigned long address,
				 int write_access)
#else
				/* Return type changed in 2.3.23 */
struct page *DRM(vm_dma_nopage)(struct vm_area_struct *vma,
				unsigned long address,
				int write_access)
#endif
{
	drm_file_t	 *priv	 = vma->vm_file->private_data;
	drm_device_t	 *dev	 = priv->dev;
	drm_device_dma_t *dma	 = dev->dma;
	unsigned long	 physical;
	unsigned long	 offset;
	unsigned long	 page;

	if (!dma)		   return NOPAGE_SIGBUS; /* Error */
	if (address > vma->vm_end) return NOPAGE_SIGBUS; /* Disallow mremap */
	if (!dma->pagelist)	   return NOPAGE_OOM ; /* Nothing allocated */

	offset	 = address - vma->vm_start; /* vm_[pg]off[set] should be 0 */
	page	 = offset >> PAGE_SHIFT;
	physical = dma->pagelist[page] + (offset & (~PAGE_MASK));
	atomic_inc(&virt_to_page(physical)->count); /* Dec. by kernel */

	DRM_DEBUG("0x%08lx (page %lu) => 0x%08lx\n", address, page, physical);
#if LINUX_VERSION_CODE < 0x020317
	return physical;
#else
	return virt_to_page(physical);
#endif
}

#if LINUX_VERSION_CODE < 0x020317
unsigned long DRM(vm_sg_nopage)(struct vm_area_struct *vma,
				unsigned long address,
				int write_access)
#else
				/* Return type changed in 2.3.23 */
struct page *DRM(vm_sg_nopage)(struct vm_area_struct *vma,
			       unsigned long address,
			       int write_access)
#endif
{
#if LINUX_VERSION_CODE >= 0x020300
	drm_map_t        *map    = (drm_map_t *)vma->vm_private_data;
#else
	drm_map_t        *map    = (drm_map_t *)vma->vm_pte;
#endif
	drm_file_t *priv = vma->vm_file->private_data;
	drm_device_t *dev = priv->dev;
	drm_sg_mem_t *entry = dev->sg;
	unsigned long offset;
	unsigned long map_offset;
	unsigned long page_offset;
	struct page *page;

	if (!entry)                return NOPAGE_SIGBUS; /* Error */
	if (address > vma->vm_end) return NOPAGE_SIGBUS; /* Disallow mremap */
	if (!entry->pagelist)      return NOPAGE_OOM ;  /* Nothing allocated */


	offset = address - vma->vm_start;
	map_offset = map->offset - dev->sg->handle;
	page_offset = (offset >> PAGE_SHIFT) + (map_offset >> PAGE_SHIFT);
	page = entry->pagelist[page_offset];
	atomic_inc(&page->count);                       /* Dec. by kernel */

#if LINUX_VERSION_CODE < 0x020317
	return (unsigned long)virt_to_phys(page->virtual);
#else
	return page;
#endif
}

void DRM(vm_open)(struct vm_area_struct *vma)
{
	drm_file_t	*priv	= vma->vm_file->private_data;
	drm_device_t	*dev	= priv->dev;
	drm_vma_entry_t *vma_entry;

	DRM_DEBUG("0x%08lx,0x%08lx\n",
		  vma->vm_start, vma->vm_end - vma->vm_start);
	atomic_inc(&dev->vma_count);
#if LINUX_VERSION_CODE < 0x020333
				/* The map can exist after the fd is closed. */
	MOD_INC_USE_COUNT; /* Needed before Linux 2.3.51 */
#endif

	vma_entry = DRM(alloc)(sizeof(*vma_entry), DRM_MEM_VMAS);
	if (vma_entry) {
		down(&dev->struct_sem);
		vma_entry->vma	= vma;
		vma_entry->next = dev->vmalist;
		vma_entry->pid	= current->pid;
		dev->vmalist	= vma_entry;
		up(&dev->struct_sem);
	}
}

void DRM(vm_close)(struct vm_area_struct *vma)
{
	drm_file_t	*priv	= vma->vm_file->private_data;
	drm_device_t	*dev	= priv->dev;
	drm_vma_entry_t *pt, *prev;

	DRM_DEBUG("0x%08lx,0x%08lx\n",
		  vma->vm_start, vma->vm_end - vma->vm_start);
#if LINUX_VERSION_CODE < 0x020333
	MOD_DEC_USE_COUNT; /* Needed before Linux 2.3.51 */
#endif
	atomic_dec(&dev->vma_count);

	down(&dev->struct_sem);
	for (pt = dev->vmalist, prev = NULL; pt; prev = pt, pt = pt->next) {
		if (pt->vma == vma) {
			if (prev) {
				prev->next = pt->next;
			} else {
				dev->vmalist = pt->next;
			}
			DRM(free)(pt, sizeof(*pt), DRM_MEM_VMAS);
			break;
		}
	}
	up(&dev->struct_sem);
}

int DRM(mmap_dma)(struct file *filp, struct vm_area_struct *vma)
{
	drm_file_t	 *priv	 = filp->private_data;
	drm_device_t	 *dev;
	drm_device_dma_t *dma;
	unsigned long	 length	 = vma->vm_end - vma->vm_start;

	lock_kernel();
	dev	 = priv->dev;
	dma	 = dev->dma;
	DRM_DEBUG("start = 0x%lx, end = 0x%lx, offset = 0x%lx\n",
		  vma->vm_start, vma->vm_end, VM_OFFSET(vma));

				/* Length must match exact page count */
	if (!dma || (length >> PAGE_SHIFT) != dma->page_count) {
		unlock_kernel();
		return -EINVAL;
	}
	unlock_kernel();

	vma->vm_ops   = &drm_vm_dma_ops;
	vma->vm_flags |= VM_LOCKED | VM_SHM; /* Don't swap */

#if LINUX_VERSION_CODE < 0x020203 /* KERNEL_VERSION(2,2,3) */
				/* In Linux 2.2.3 and above, this is
				   handled in do_mmap() in mm/mmap.c. */
	++filp->f_count;
#endif
	vma->vm_file  =	 filp;	/* Needed for drm_vm_open() */
	DRM(vm_open)(vma);
	return 0;
}

int DRM(mmap)(struct file *filp, struct vm_area_struct *vma)
{
	drm_file_t	*priv	= filp->private_data;
	drm_device_t	*dev	= priv->dev;
	drm_map_t	*map	= NULL;
	drm_map_list_t  *r_list;
	unsigned long   offset  = 0;
	struct list_head *list;

	DRM_DEBUG("start = 0x%lx, end = 0x%lx, offset = 0x%lx\n",
		  vma->vm_start, vma->vm_end, VM_OFFSET(vma));

	if ( !priv->authenticated ) return -EACCES;

	if (!VM_OFFSET(vma)) return DRM(mmap_dma)(filp, vma);

				/* A sequential search of a linked list is
				   fine here because: 1) there will only be
				   about 5-10 entries in the list and, 2) a
				   DRI client only has to do this mapping
				   once, so it doesn't have to be optimized
				   for performance, even if the list was a
				   bit longer. */
	list_for_each(list, &dev->maplist->head) {
		r_list = (drm_map_list_t *)list;
		map = r_list->map;
		if (!map) continue;
		if (map->offset == VM_OFFSET(vma)) break;
	}

	if (!map || ((map->flags&_DRM_RESTRICTED) && !capable(CAP_SYS_ADMIN)))
		return -EPERM;

				/* Check for valid size. */
	if (map->size != vma->vm_end - vma->vm_start) return -EINVAL;

	if (!capable(CAP_SYS_ADMIN) && (map->flags & _DRM_READ_ONLY)) {
		vma->vm_flags &= VM_MAYWRITE;
#if defined(__i386__)
		pgprot_val(vma->vm_page_prot) &= ~_PAGE_RW;
#else
				/* Ye gads this is ugly.  With more thought
                                   we could move this up higher and use
                                   `protection_map' instead.  */
		vma->vm_page_prot = __pgprot(pte_val(pte_wrprotect(
			__pte(pgprot_val(vma->vm_page_prot)))));
#endif
	}

	switch (map->type) {
	case _DRM_FRAME_BUFFER:
	case _DRM_REGISTERS:
	case _DRM_AGP:
		if (VM_OFFSET(vma) >= __pa(high_memory)) {
#if defined(__i386__)
			if (boot_cpu_data.x86 > 3 && map->type != _DRM_AGP) {
				pgprot_val(vma->vm_page_prot) |= _PAGE_PCD;
				pgprot_val(vma->vm_page_prot) &= ~_PAGE_PWT;
			}
#elif defined(__ia64__)
			if (map->type != _DRM_AGP)
				vma->vm_page_prot =
					pgprot_writecombine(vma->vm_page_prot);
#elif defined(__powerpc__)
			pgprot_val(vma->vm_page_prot) |= _PAGE_NO_CACHE | _PAGE_GUARDED;
#endif
			vma->vm_flags |= VM_IO;	/* not in core dump */
		}
#ifdef __alpha__
                offset = dev->hose->dense_mem_base -
		         dev->hose->mem_space->start;
#endif
		if (remap_page_range(vma->vm_start,
				     VM_OFFSET(vma) + offset,
				     vma->vm_end - vma->vm_start,
				     vma->vm_page_prot))
				return -EAGAIN;
		DRM_DEBUG("   Type = %d; start = 0x%lx, end = 0x%lx,"
			  " offset = 0x%lx\n",
			  map->type,
			  vma->vm_start, vma->vm_end, VM_OFFSET(vma) + offset);
		vma->vm_ops = &drm_vm_ops;
		break;
	case _DRM_SHM:
		vma->vm_ops = &drm_vm_shm_ops;
#if LINUX_VERSION_CODE >= 0x020300
		vma->vm_private_data = (void *)map;
#else
		vma->vm_pte = (unsigned long)map;
#endif
				/* Don't let this area swap.  Change when
				   DRM_KERNEL advisory is supported. */
		vma->vm_flags |= VM_LOCKED;
		break;
	case _DRM_SCATTER_GATHER:
		vma->vm_ops = &drm_vm_sg_ops;
#if LINUX_VERSION_CODE >= 0x020300
		vma->vm_private_data = (void *)map;
#else
		vma->vm_pte = (unsigned long)map;
#endif
                vma->vm_flags |= VM_LOCKED;
                break;
	default:
		return -EINVAL;	/* This should never happen. */
	}
	vma->vm_flags |= VM_LOCKED | VM_SHM; /* Don't swap */

#if LINUX_VERSION_CODE < 0x020203 /* KERNEL_VERSION(2,2,3) */
				/* In Linux 2.2.3 and above, this is
				   handled in do_mmap() in mm/mmap.c. */
	++filp->f_count;
#endif
	vma->vm_file  =	 filp;	/* Needed for drm_vm_open() */
	DRM(vm_open)(vma);
	return 0;
}
