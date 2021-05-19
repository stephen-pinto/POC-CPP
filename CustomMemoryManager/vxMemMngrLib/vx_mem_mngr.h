#include "vx_mm_base_types.h"

#ifndef VX_MEM_MNGR_H
#define VX_MEM_MNGR_H

namespace  vx_mm {

using namespace vx_mem_mngr_types;

    class vx_managed_memory{

    public:

        vx_managed_memory(mem_req_stratergy m_req_s);
        ~vx_managed_memory();

        void* operator new(size_t s);
        void* operator new[](size_t s);

        void  operator delete(void* p);
        void  operator delete[](void *p);

        void  __stdcall release_all();
        void  __stdcall initialize();

        template<typename T> static T* __stdcall vx_new(mem_req_stratergy m_req_s);
        template<typename T> static T* __stdcall vx_new_arr(size_t n, mem_req_stratergy m_req_s);
        static void  __stdcall vx_delete(void *p, mem_req_stratergy m_req_s);

        static void* __stdcall vx_malloc(size_t s, mem_req_stratergy m_req_s);
        static void* __stdcall vx_calloc(size_t s, size_t n, mem_req_stratergy m_req_s);
        static void* __stdcall vx_realloc(void* p, size_t s, mem_req_stratergy m_req_s);
        static void  __stdcall vx_free(void* p, mem_req_stratergy m_req_s);

        static void  __stdcall release_all(mem_req_stratergy m_req_s);
        static void  __stdcall initialize(mem_req_stratergy m_req_s);

    private:

        static pvx_mem_mngr greedy_mngr;
        static pvx_mem_mngr normal_mngr;
        static pvx_mem_mngr lite_mngr;

        pvx_mem_mngr base_mngr;
    };

    template<typename T>
    T *vx_managed_memory::vx_new(mem_req_stratergy m_req_s)
    {
        return new(greedy_mngr->alloc(sizeof(T))) T;
    }

    template<typename T>
    T *vx_managed_memory::vx_new_arr(size_t n, mem_req_stratergy m_req_s)
    {
        (void)m_req_s;
        return new(greedy_mngr->alloc(sizeof(T) * n)) T[n];
    }
}


#define VX_NEW(T, type) vx_managed_memory::vx_new<T>((vx_mm::mem_req_stratergy)type)
#define VX_DEL(p, type) vx_managed_memory::vx_delete(p, (vx_mm::mem_req_stratergy)type)

#endif // VX_MEM_MNGR_H
