#ifndef VX_MACROS_H
#define VX_MACROS_H

/// Default initial allocation defined

#define VX_DFLT_INIT_ALLOC_SIZE (128 * 1024)

/// Default incremental allocation sizes

#define VX_DFLT_INCR_ALLOC_SIZE VX_DFLT_INIT_ALLOC_SIZE

#define VX_DFLT_INCR_L_ALLOC_SIZE (512 * 1024)

/// Default chunk sizes for different stratergies

#define VX_DFLT_PAGE_SIZE (8 * 1024)

#define VX_DFLT_L_PAGE_SIZE (32 * 1024)

///Macro functions

#define VX_PAGE_COUNT(total_size, size_per_page) \
    (((size_t)(total_size/size_per_page)) + 1)

#define VX_DFLT_PAGE_COUNT VX_PAGE_COUNT(VX_DFLT_INIT_ALLOC_SIZE, VX_DFLT_PAGE_SIZE)

#endif // VX_MACROS_H