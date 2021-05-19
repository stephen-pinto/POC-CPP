#include "vx_page_table_types.h"

#ifndef VX_MM_BASE_TYPES_H
#define VX_MM_BASE_TYPES_H

namespace vx_mm {

    enum mem_req_stratergy
    {
       ms_greedy,
       ms_normal,
       ms_lite
    };

}

namespace vx_mem_mngr_types {

    using namespace vx_types;

    typedef class vx_mem_mngr
    {

    public:

        virtual void* alloc(size_t s) = 0;
        virtual void* calloc(size_t s, size_t n) = 0;
        virtual void* realloc(void *p, size_t s) = 0;
        virtual void  free(void *s) = 0;

    }*pvx_mem_mngr;

    class vx_mem_mngr_t1 : public vx_mem_mngr
    {

    public:

        vx_mem_mngr_t1();
        virtual ~vx_mem_mngr_t1();

        virtual void* alloc(size_t s);
        virtual void* calloc(size_t s, size_t n);
        virtual void* realloc(void *p, size_t s);
        virtual void  free(void* p);

    private:

        pvx_page_table page_table;

        pvx_page_table get_page_tbl(vx_mm::mem_req_stratergy m_req_s);
    };
}

#endif // VX_MM_BASE_TYPES_H
