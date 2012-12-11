#include <bfd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include "drm.h"
#include "fbdrm.h"

/* Not all systems have MAP_FAILED defined */
#ifndef MAP_FAILED
#define MAP_FAILED ((void *)-1)
#endif

#ifndef DRM_MAJOR
#define DRM_MAJOR 226		/* Linux */
#endif

#ifndef __linux__
#undef  DRM_MAJOR
#define DRM_MAJOR 145		/* Should set in drm.h for *BSD */
#endif

#ifndef DRM_MAX_MINOR
#define DRM_MAX_MINOR 16
#endif

#ifdef __linux__
#include <sys/sysmacros.h>	/* for makedev() */
#endif

#ifndef makedev
				/* This definition needs to be changed on
                                   some systems if dev_t is a structure.
                                   If there is a header file we can get it
                                   from, there would be best. */
#define makedev(x,y)    ((dev_t)(((x) << 8) | (y)))
#endif

// Want to open the device only once to reduce debugging.
// Copy this after the first drm instance is opened.
static int fd_global = -1;


static void *drmHashTable = NULL; /* Context switch callbacks */

typedef struct drmHashEntry {
    int      fd;
    void     (*f)(int, void *, void *);
    void     *tagTable;
} drmHashEntry;


#define _DRM_MALLOC 	  malloc
#define _DRM_FREE   	  free

void *drmMalloc(int size)
{
    void *pt;
    if ((pt = _DRM_MALLOC(size))) memset(pt, 0, size);
    return pt;
}

void drmFree(void *pt)
{
    if (pt) _DRM_FREE(pt);
}

static unsigned long drmGetKeyFromFd(int fd)
{
    struct stat     st;

    st.st_rdev = 0;
    fstat(fd, &st);
    return st.st_rdev;
}

static drmHashEntry *drmGetEntry(int fd)
{
    unsigned long key = drmGetKeyFromFd(fd);
    void          *value;
    drmHashEntry  *entry;

    if (!drmHashTable) drmHashTable = drmHashCreate();

    if (drmHashLookup(drmHashTable, key, &value)) {
	entry           = drmMalloc(sizeof(*entry));
	entry->fd       = fd;
	entry->f        = NULL;
	entry->tagTable = drmHashCreate();
	drmHashInsert(drmHashTable, key, entry);
    } else {
	entry = value;
    }
    return entry;
}


int drmAddMap(int fd,
	      drmHandle offset,
	      drmSize size,
	      drmMapType type,
	      drmMapFlags flags,
	      drmHandlePtr handle)
{
    drm_map_t map;
	int result;

    map.offset  = offset;
    map.size    = size;
    map.handle  = 0;
    map.type    = type;
    map.flags   = flags;




// Something in here causes segmentation fault and kernel crash on exit


    if (result = ioctl(fd, DRM_IOCTL_ADD_MAP, &map)) return -errno;




//printf("drmAddMap %d\n", result);



    if (handle) *handle = (drmHandle)map.handle;
    return 0;
}

int drmAddBufs(int fd, int count, int size, drmBufDescFlags flags,
	       int agp_offset)
{
    drm_buf_desc_t request;

    request.count     = count;
    request.size      = size;
    request.low_mark  = 0;
    request.high_mark = 0;
    request.flags     = flags;
    request.agp_start = agp_offset;

    if (ioctl(fd, DRM_IOCTL_ADD_BUFS, &request)) return -errno;
    return request.count;
}

int drmMap(int fd,
	   drmHandle handle,
	   drmSize size,
	   drmAddressPtr address)
{
    static unsigned long pagesize_mask = 0;

    if (fd < 0) return -EINVAL;

    if (!pagesize_mask)
	pagesize_mask = getpagesize() - 1;

    size = (size + pagesize_mask) & ~pagesize_mask;





    *address = mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, handle);



//printf("drmMap 1 %d %d %d %p %s\n", size, fd, handle, *address, strerror(errno));

    if (*address == MAP_FAILED) return -errno;






    return 0;
}

drmBufMapPtr drmMapBufs(int fd)
{
    drm_buf_map_t bufs;
    drmBufMapPtr  retval;
    int           i;

    bufs.count = 0;
    bufs.list  = NULL;
    if (ioctl(fd, DRM_IOCTL_MAP_BUFS, &bufs)) return NULL;

    if (bufs.count) {
	if (!(bufs.list = drmMalloc(bufs.count * sizeof(*bufs.list))))
	    return NULL;

	if (ioctl(fd, DRM_IOCTL_MAP_BUFS, &bufs)) {
	    drmFree(bufs.list);
	    return NULL;
	}
				/* Now, copy it all back into the
                                   client-visible data structure... */
	retval = drmMalloc(sizeof(*retval));
	retval->count = bufs.count;
	retval->list  = drmMalloc(bufs.count * sizeof(*retval->list));
	for (i = 0; i < bufs.count; i++) {
	    retval->list[i].idx     = bufs.list[i].idx;
	    retval->list[i].total   = bufs.list[i].total;
	    retval->list[i].used    = 0;
	    retval->list[i].address = bufs.list[i].address;
	}
	return retval;
    }
    return NULL;
}

int drmUnmapBufs(drmBufMapPtr bufs)
{
    int i;

    for (i = 0; i < bufs->count; i++) {
	munmap(bufs->list[i].address, bufs->list[i].total);
    }
    return 0;
}

int drmUnmap(drmAddress address, drmSize size)
{
    return munmap(address, size);
}

#define DRM_DMA_RETRY		16

int drmDMA(int fd, drmDMAReqPtr request)
{
    drm_dma_t dma;
    int ret, i = 0;

				/* Copy to hidden structure */
    dma.context         = request->context;
    dma.send_count      = request->send_count;
    dma.send_indices    = request->send_list;
    dma.send_sizes      = request->send_sizes;
    dma.flags           = request->flags;
    dma.request_count   = request->request_count;
    dma.request_size    = request->request_size;
    dma.request_indices = request->request_list;
    dma.request_sizes   = request->request_sizes;

    do {
	ret = ioctl( fd, DRM_IOCTL_DMA, &dma );
    } while ( ret && errno == EAGAIN && i++ < DRM_DMA_RETRY );

    if ( ret == 0 ) {
	request->granted_count = dma.granted_count;
	return 0;
    } else {
	return -errno;
    }
}

static int drmOpenDevice(long dev, int minor)
{
    struct stat     st;
    char            buf[64];
    int             fd;
    mode_t          dirmode = DRM_DEV_DIRMODE;
    mode_t          devmode = DRM_DEV_MODE;
    int             isroot  = !geteuid();


// Get directory
    if (stat(DRM_DIR_NAME, &st)) 
	{
		if (!isroot) return DRM_ERR_NOT_ROOT;
		remove(DRM_DIR_NAME);
		mkdir(DRM_DIR_NAME, dirmode);
    }

    sprintf(buf, DRM_DEV_NAME, DRM_DIR_NAME, minor);
    if (stat(buf, &st) || st.st_rdev != dev) 
	{
		if (!isroot) 
			return DRM_ERR_NOT_ROOT;

		remove(buf);
		mknod(buf, S_IFCHR | devmode, dev);
    }



//printf("drmOpenDevice 1\n");
	if((fd = fd_global) >= 0) return fd;
	else
    if((fd_global = fd = open(buf, O_RDWR, 0)) >= 0) return fd;




    remove(buf);
    return -errno;



}

static int drmOpenMinor(int minor, int create)
{
    int  fd;
    char buf[64];
//printf("drmOpenMinor 1\n");
    
    if (create) return drmOpenDevice(makedev(DRM_MAJOR, minor), minor);
    
    sprintf(buf, DRM_DEV_NAME, DRM_DIR_NAME, minor);


//printf("drmOpenMinor 2\n");

	if((fd = fd_global) >= 0) 
	{
		return fd;
	}
	else
    if ((fd = fd_global = open(buf, O_RDWR, 0)) >= 0) 
	{
		return fd;
	}
	else
	{
		perror("drmOpenMinor");
    	return -errno;
	}
}

char *drmGetBusid(int fd)
{
    drm_unique_t u;

    u.unique_len = 0;
    u.unique     = NULL;

    if (ioctl(fd, DRM_IOCTL_GET_UNIQUE, &u))
	{
		perror("drmGetBusid DRM_IOCTL_GET_UNIQUE");
		return NULL;
	}
    u.unique = drmMalloc(u.unique_len + 1);

    if (ioctl(fd, DRM_IOCTL_GET_UNIQUE, &u))
	{
		perror("drmGetBusid DRM_IOCTL_GET_UNIQUE");
		return NULL;
	}
    u.unique[u.unique_len] = '\0';

//printf("drmGetBusid %p\n", u.unique);

    return u.unique;
}

int drmSetBusid(int fd, const char *busid)
{
    drm_unique_t u;

    u.unique     = (char *)busid;
    u.unique_len = strlen(busid);




//printf("drmSetBusid %d %s\n ", fd, busid);
    if (ioctl(fd, DRM_IOCTL_SET_UNIQUE, &u)) return -errno;





    return 0;
}


void drmFreeBusid(const char *busid)
{
    drmFree((void *)busid);
}


static int drmOpenByBusid(const char *busid)
{
    int        i;
    int        fd;
    const char *buf;
    
    for(i = 0; i < DRM_MAX_MINOR; i++)
	{
//printf("drmOpenByBusid 1 %d\n", i);
		if((fd = drmOpenMinor(i, 0)) >= 0)
		{
//printf("drmOpenByBusid 2 %d\n", i);
	    	buf = drmGetBusid(fd);

//printf("drmOpenByBusid 2 %s %s\n", buf, busid);
// Since our device will only have one graphics card we'll skip the busid 
// matching and go on the the next bug.



//	    	if(buf && !strcmp(buf, busid))
			{
//printf("drmOpenByBusid 3\n", i);
				drmFreeBusid(buf);
				return fd;
	    	}



	    	if (buf) drmFreeBusid(buf);
	    	close(fd);
		}
    }
    return -1;
}

/* drmAvailable looks for (DRM_MAJOR, 0) and returns 1 if it returns
   information for DRM_IOCTL_VERSION.  For backward compatibility with
   older Linux implementations, /proc/dri is also checked. */

int drmAvailable(void)
{
    drmVersionPtr version;
    int           retval = 0;
    int           fd;

    if ((fd_global = fd = drmOpenMinor(0, 1)) < 0) 
	{
			return 1;
    }

    return retval;
}

/* drmOpen looks up the specified name and busid, and opens the device
   found.  The entry in /dev/dri is created if necessary (and if root).
   A file descriptor is returned.  On error, the return value is
   negative. */

int drmOpen(const char *name, const char *busid)
{

    if (busid) 
		return drmOpenByBusid(busid);
	else
	{
	 	fprintf(stderr, "drmOpen drmOpenByName undefined\n");
	    //return drmOpenByName(name);
	}
}

int drmClose(int fd)
{
    unsigned long key    = drmGetKeyFromFd(fd);
    drmHashEntry  *entry = drmGetEntry(fd);

    drmHashDestroy(entry->tagTable);
    entry->fd       = 0;
    entry->f        = NULL;
    entry->tagTable = NULL;

    drmHashDelete(drmHashTable, key);
    drmFree(entry);

    return close(fd);
}


int drmGetLock(int fd, drmContext context, drmLockFlags flags)
{
    drm_lock_t lock;
	int i = 0;





    lock.context = context;
    lock.flags   = 0;
    if (flags & DRM_LOCK_READY)      lock.flags |= _DRM_LOCK_READY;
    if (flags & DRM_LOCK_QUIESCENT)  lock.flags |= _DRM_LOCK_QUIESCENT;
    if (flags & DRM_LOCK_FLUSH)      lock.flags |= _DRM_LOCK_FLUSH;
    if (flags & DRM_LOCK_FLUSH_ALL)  lock.flags |= _DRM_LOCK_FLUSH_ALL;
    if (flags & DRM_HALT_ALL_QUEUES) lock.flags |= _DRM_HALT_ALL_QUEUES;
    if (flags & DRM_HALT_CUR_QUEUES) lock.flags |= _DRM_HALT_CUR_QUEUES;

//printf("drmGetLock 1 %x\n", context);

    while (ioctl(fd, DRM_IOCTL_LOCK, &lock))
		;

    return 0;
}

int drmUnlock(int fd, drmContext context)
{
    drm_lock_t lock;

    lock.context = context;
    lock.flags   = 0;


//printf("drmUnlock 1\n");
    return ioctl(fd, DRM_IOCTL_UNLOCK, &lock);
}

drmContextPtr drmGetReservedContextList(int fd, int *count)
{
    drm_ctx_res_t res;
    drm_ctx_t     *list;
    drmContextPtr retval;
    int           i;

    res.count    = 0;
    res.contexts = NULL;
    if (ioctl(fd, DRM_IOCTL_RES_CTX, &res)) return NULL;

    if (!res.count) return NULL;

    if (!(list   = drmMalloc(res.count * sizeof(*list)))) return NULL;
    if (!(retval = drmMalloc(res.count * sizeof(*retval)))) {
	drmFree(list);
	return NULL;
    }

    res.contexts = list;
    if (ioctl(fd, DRM_IOCTL_RES_CTX, &res)) return NULL;

    for (i = 0; i < res.count; i++) retval[i] = list[i].handle;
    drmFree(list);

    *count = res.count;
    return retval;
}

void drmFreeReservedContextList(drmContextPtr pt)
{
    drmFree(pt);
}


int drmCreateContext(int fd, drmContextPtr handle)
{
    drm_ctx_t ctx;

    ctx.flags = 0;	/* Modified with functions below */
    if (ioctl(fd, DRM_IOCTL_ADD_CTX, &ctx)) return -errno;
    *handle = ctx.handle;
    return 0;
}

int drmSwitchToContext(int fd, drmContext context)
{
    drm_ctx_t ctx;

    ctx.handle = context;
    if (ioctl(fd, DRM_IOCTL_SWITCH_CTX, &ctx)) return -errno;
    return 0;
}

int drmSetContextFlags(int fd, drmContext context, drmContextFlags flags)
{
    drm_ctx_t ctx;

				/* Context preserving means that no context
                                   switched are done between DMA buffers
                                   from one context and the next.  This is
                                   suitable for use in the X server (which
                                   promises to maintain hardware context,
                                   or in the client-side library when
                                   buffers are swapped on behalf of two
                                   threads. */
    ctx.handle = context;
    ctx.flags  = 0;
    if (flags & DRM_CONTEXT_PRESERVED) ctx.flags |= _DRM_CONTEXT_PRESERVED;
    if (flags & DRM_CONTEXT_2DONLY)    ctx.flags |= _DRM_CONTEXT_2DONLY;
    if (ioctl(fd, DRM_IOCTL_MOD_CTX, &ctx)) return -errno;
    return 0;
}

int drmGetContextFlags(int fd, drmContext context, drmContextFlagsPtr flags)
{
    drm_ctx_t ctx;

    ctx.handle = context;
    if (ioctl(fd, DRM_IOCTL_GET_CTX, &ctx)) return -errno;
    *flags = 0;
    if (ctx.flags & _DRM_CONTEXT_PRESERVED) *flags |= DRM_CONTEXT_PRESERVED;
    if (ctx.flags & _DRM_CONTEXT_2DONLY)    *flags |= DRM_CONTEXT_2DONLY;
    return 0;
}

int drmDestroyContext(int fd, drmContext handle)
{
    drm_ctx_t ctx;
    ctx.handle = handle;
    if (ioctl(fd, DRM_IOCTL_RM_CTX, &ctx)) return -errno;
    return 0;
}

int drmCreateDrawable(int fd, drmDrawablePtr handle)
{
    drm_draw_t draw;
    if (ioctl(fd, DRM_IOCTL_ADD_DRAW, &draw)) return -errno;
    *handle = draw.handle;
    return 0;
}

int drmDestroyDrawable(int fd, drmDrawable handle)
{
    drm_draw_t draw;
    draw.handle = handle;
    if (ioctl(fd, DRM_IOCTL_RM_DRAW, &draw)) return -errno;
    return 0;
}

int drmAgpAcquire(int fd)
{
    if (ioctl(fd, DRM_IOCTL_AGP_ACQUIRE, NULL)) return -errno;
    return 0;
}

int drmAgpRelease(int fd)
{
    if (ioctl(fd, DRM_IOCTL_AGP_RELEASE, NULL)) return -errno;
    return 0;
}

int drmAgpEnable(int fd, unsigned long mode)
{
    drm_agp_mode_t m;

    m.mode = mode;
    if (ioctl(fd, DRM_IOCTL_AGP_ENABLE, &m)) return -errno;
    return 0;
}

int drmAgpAlloc(int fd, unsigned long size, unsigned long type,
		unsigned long *address, unsigned long *handle)
{
    drm_agp_buffer_t b;
    *handle = 0;
    b.size   = size;
    b.handle = 0;
    b.type   = type;
    if (ioctl(fd, DRM_IOCTL_AGP_ALLOC, &b)) return -errno;
    if (address != 0UL) *address = b.physical;
    *handle = b.handle;
    return 0;
}

int drmAgpFree(int fd, unsigned long handle)
{
    drm_agp_buffer_t b;

    b.size   = 0;
    b.handle = handle;
    if (ioctl(fd, DRM_IOCTL_AGP_FREE, &b)) return -errno;
    return 0;
}

int drmAgpBind(int fd, unsigned long handle, unsigned long offset)
{
    drm_agp_binding_t b;

    b.handle = handle;
    b.offset = offset;
    if (ioctl(fd, DRM_IOCTL_AGP_BIND, &b)) return -errno;
    return 0;
}

int drmAgpUnbind(int fd, unsigned long handle)
{
    drm_agp_binding_t b;

    b.handle = handle;
    b.offset = 0;
    if (ioctl(fd, DRM_IOCTL_AGP_UNBIND, &b)) return -errno;
    return 0;
}

int drmAgpVersionMajor(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return -errno;
    return i.agp_version_major;
}

int drmAgpVersionMinor(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return -errno;
    return i.agp_version_minor;
}

unsigned long drmAgpGetMode(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return 0;
    return i.mode;
}

unsigned long drmAgpBase(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return 0;
    return i.aperture_base;
}

unsigned long drmAgpSize(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return 0;
    return i.aperture_size;
}

unsigned long drmAgpMemoryUsed(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return 0;
    return i.memory_used;
}

unsigned long drmAgpMemoryAvail(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return 0;
    return i.memory_allowed;
}

unsigned int drmAgpVendorId(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return 0;
    return i.id_vendor;
}

unsigned int drmAgpDeviceId(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return 0;
    return i.id_device;
}

int drmScatterGatherAlloc(int fd, unsigned long size, unsigned long *handle)
{
    drm_scatter_gather_t sg;

    *handle = 0;
    sg.size   = size;
    sg.handle = 0;
    if (ioctl(fd, DRM_IOCTL_SG_ALLOC, &sg)) return -errno;
    *handle = sg.handle;
    return 0;
}

int drmScatterGatherFree(int fd, unsigned long handle)
{
    drm_scatter_gather_t sg;

    sg.size   = 0;
    sg.handle = handle;
    if (ioctl(fd, DRM_IOCTL_SG_FREE, &sg)) return -errno;
    return 0;
}

int drmError(int err, const char *label)
{
    switch (err) {
    case DRM_ERR_NO_DEVICE: fprintf(stderr, "%s: no device\n", label);   break;
    case DRM_ERR_NO_ACCESS: fprintf(stderr, "%s: no access\n", label);   break;
    case DRM_ERR_NOT_ROOT:  fprintf(stderr, "%s: not root\n", label);    break;
    case DRM_ERR_INVALID:   fprintf(stderr, "%s: invalid args\n", label);break;
    default:
	if (err < 0) err = -err;
	fprintf( stderr, "%s: error %d (%s)\n", label, err, strerror(err) );
	break;
    }

    return 1;
}

int drmCtlInstHandler(int fd, int irq)
{
    drm_control_t ctl;

    ctl.func  = DRM_INST_HANDLER;
    ctl.irq   = irq;
    if (ioctl(fd, DRM_IOCTL_CONTROL, &ctl)) return -errno;
    return 0;
}

int drmCtlUninstHandler(int fd)
{
    drm_control_t ctl;

    ctl.func  = DRM_UNINST_HANDLER;
    ctl.irq   = 0;
    if (ioctl(fd, DRM_IOCTL_CONTROL, &ctl)) return -errno;
    return 0;
}

int drmFinish(int fd, int context, drmLockFlags flags)
{
    drm_lock_t lock;

    lock.context = context;
    lock.flags   = 0;
    if (flags & DRM_LOCK_READY)      lock.flags |= _DRM_LOCK_READY;
    if (flags & DRM_LOCK_QUIESCENT)  lock.flags |= _DRM_LOCK_QUIESCENT;
    if (flags & DRM_LOCK_FLUSH)      lock.flags |= _DRM_LOCK_FLUSH;
    if (flags & DRM_LOCK_FLUSH_ALL)  lock.flags |= _DRM_LOCK_FLUSH_ALL;
    if (flags & DRM_HALT_ALL_QUEUES) lock.flags |= _DRM_HALT_ALL_QUEUES;
    if (flags & DRM_HALT_CUR_QUEUES) lock.flags |= _DRM_HALT_CUR_QUEUES;
    if (ioctl(fd, DRM_IOCTL_FINISH, &lock)) return -errno;
    return 0;
}

int drmGetInterruptFromBusID(int fd, int busnum, int devnum, int funcnum)
{
    drm_irq_busid_t p;

    p.busnum  = busnum;
    p.devnum  = devnum;
    p.funcnum = funcnum;
    if (ioctl(fd, DRM_IOCTL_IRQ_BUSID, &p)) return -errno;
    return p.irq;
}

int drmAddContextTag(int fd, drmContext context, void *tag)
{
    drmHashEntry  *entry = drmGetEntry(fd);

    if (drmHashInsert(entry->tagTable, context, tag)) {
	drmHashDelete(entry->tagTable, context);
	drmHashInsert(entry->tagTable, context, tag);
    }
    return 0;
}

int drmDelContextTag(int fd, drmContext context)
{
    drmHashEntry  *entry = drmGetEntry(fd);

    return drmHashDelete(entry->tagTable, context);
}

void *drmGetContextTag(int fd, drmContext context)
{
    drmHashEntry  *entry = drmGetEntry(fd);
    void          *value;

    if (drmHashLookup(entry->tagTable, context, &value)) return NULL;

    return value;
}

int drmAddContextPrivateMapping(int fd, drmContext ctx_id, drmHandle handle)
{
    drm_ctx_priv_map_t map;

    map.ctx_id = ctx_id;
    map.handle = (void *)handle;

    if (ioctl(fd, DRM_IOCTL_SET_SAREA_CTX, &map)) return -errno;
    return 0;
}

int drmGetContextPrivateMapping(int fd, drmContext ctx_id, drmHandlePtr handle)
{
    drm_ctx_priv_map_t map;

    map.ctx_id = ctx_id;

    if (ioctl(fd, DRM_IOCTL_GET_SAREA_CTX, &map)) return -errno;
    if (handle) *handle = (drmHandle)map.handle;

    return 0;
}

int drmGetMap(int fd, int idx, drmHandle *offset, drmSize *size,
	      drmMapType *type, drmMapFlags *flags, drmHandle *handle,
	      int *mtrr)
{
    drm_map_t map;

    map.offset = idx;
    if (ioctl(fd, DRM_IOCTL_GET_MAP, &map)) return -errno;
    *offset = map.offset;
    *size   = map.size;
    *type   = map.type;
    *flags  = map.flags;
    *handle = (unsigned long)map.handle;
    *mtrr   = map.mtrr;
    return 0;
}

int drmGetClient(int fd, int idx, int *auth, int *pid, int *uid,
		 unsigned long *magic, unsigned long *iocs)
{
    drm_client_t client;

    client.idx = idx;
    if (ioctl(fd, DRM_IOCTL_GET_CLIENT, &client)) return -errno;
    *auth      = client.auth;
    *pid       = client.pid;
    *uid       = client.uid;
    *magic     = client.magic;
    *iocs      = client.iocs;
    return 0;
}

int drmGetStats(int fd, drmStatsT *stats)
{
    drm_stats_t s;
    int         i;

    if (ioctl(fd, DRM_IOCTL_GET_STATS, &s)) return -errno;

    stats->count = 0;
    memset(stats, 0, sizeof(*stats));
    if (s.count > sizeof(stats->data)/sizeof(stats->data[0]))
	return -1;

#define SET_VALUE                              \
    stats->data[i].long_format = "%-20.20s";   \
    stats->data[i].rate_format = "%8.8s";      \
    stats->data[i].isvalue     = 1;            \
    stats->data[i].verbose     = 0

#define SET_COUNT                              \
    stats->data[i].long_format = "%-20.20s";   \
    stats->data[i].rate_format = "%5.5s";      \
    stats->data[i].isvalue     = 0;            \
    stats->data[i].mult_names  = "kgm";        \
    stats->data[i].mult        = 1000;         \
    stats->data[i].verbose     = 0

#define SET_BYTE                               \
    stats->data[i].long_format = "%-20.20s";   \
    stats->data[i].rate_format = "%5.5s";      \
    stats->data[i].isvalue     = 0;            \
    stats->data[i].mult_names  = "KGM";        \
    stats->data[i].mult        = 1024;         \
    stats->data[i].verbose     = 0


    stats->count = s.count;
    for (i = 0; i < s.count; i++) {
	stats->data[i].value = s.data[i].value;
	switch (s.data[i].type) {
	case _DRM_STAT_LOCK:
	    stats->data[i].long_name = "Lock";
	    stats->data[i].rate_name = "Lock";
	    SET_VALUE;
	    break;
	case _DRM_STAT_OPENS:
	    stats->data[i].long_name = "Opens";
	    stats->data[i].rate_name = "O";
	    SET_COUNT;
	    stats->data[i].verbose   = 1;
	    break;
	case _DRM_STAT_CLOSES:
	    stats->data[i].long_name = "Closes";
	    stats->data[i].rate_name = "Lock";
	    SET_COUNT;
	    stats->data[i].verbose   = 1;
	    break;
	case _DRM_STAT_IOCTLS:
	    stats->data[i].long_name = "Ioctls";
	    stats->data[i].rate_name = "Ioc/s";
	    SET_COUNT;
	    break;
	case _DRM_STAT_LOCKS:
	    stats->data[i].long_name = "Locks";
	    stats->data[i].rate_name = "Lck/s";
	    SET_COUNT;
	    break;
	case _DRM_STAT_UNLOCKS:
	    stats->data[i].long_name = "Unlocks";
	    stats->data[i].rate_name = "Unl/s";
	    SET_COUNT;
	    break;
	case _DRM_STAT_IRQ:
	    stats->data[i].long_name = "IRQs";
	    stats->data[i].rate_name = "IRQ/s";
	    SET_COUNT;
	    break;
	case _DRM_STAT_PRIMARY:
	    stats->data[i].long_name = "Primary Bytes";
	    stats->data[i].rate_name = "PB/s";
	    SET_BYTE;
	    break;
	case _DRM_STAT_SECONDARY:
	    stats->data[i].long_name = "Secondary Bytes";
	    stats->data[i].rate_name = "SB/s";
	    SET_BYTE;
	    break;
	case _DRM_STAT_DMA:
	    stats->data[i].long_name = "DMA";
	    stats->data[i].rate_name = "DMA/s";
	    SET_COUNT;
	    break;
	case _DRM_STAT_SPECIAL:
	    stats->data[i].long_name = "Special DMA";
	    stats->data[i].rate_name = "dma/s";
	    SET_COUNT;
	    break;
	case _DRM_STAT_MISSED:
	    stats->data[i].long_name = "Miss";
	    stats->data[i].rate_name = "Ms/s";
	    SET_COUNT;
	    break;
	case _DRM_STAT_VALUE:
	    stats->data[i].long_name = "Value";
	    stats->data[i].rate_name = "Value";
	    SET_VALUE;
	    break;
	case _DRM_STAT_BYTE:
	    stats->data[i].long_name = "Bytes";
	    stats->data[i].rate_name = "B/s";
	    SET_BYTE;
	    break;
	case _DRM_STAT_COUNT:
	default:
	    stats->data[i].long_name = "Count";
	    stats->data[i].rate_name = "Cnt/s";
	    SET_COUNT;
	    break;
	}
    }
    return 0;
}
