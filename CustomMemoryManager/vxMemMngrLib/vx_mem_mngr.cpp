#include "vx_mem_mngr.h"

vx_mm::pvx_mem_mngr vx_mm::vx_managed_memory::greedy_mngr = NULL;
vx_mm::pvx_mem_mngr vx_mm::vx_managed_memory::normal_mngr = NULL;
vx_mm::pvx_mem_mngr vx_mm::vx_managed_memory::lite_mngr = NULL;

void *vx_mm::vx_managed_memory::operator new(size_t s)
{
    return greedy_mngr->alloc(s);
}

void *vx_mm::vx_managed_memory::operator new[](size_t s)
{
    return greedy_mngr->alloc(s);
}

void vx_mm::vx_managed_memory::operator delete(void *p)
{
   greedy_mngr->free(p);
}

void vx_mm::vx_managed_memory::operator delete[](void *p)
{
    greedy_mngr->free(p);
}

void vx_mm::vx_managed_memory::release_all()
{
    //delete pointer here
}

void vx_mm::vx_managed_memory::initialize()
{
    //create new object here
}

void vx_mm::vx_managed_memory::vx_delete(void *p, vx_mm::mem_req_stratergy m_req_s)
{
    (void)m_req_s;
    greedy_mngr->free(p);
}

void *vx_mm::vx_managed_memory::vx_malloc(size_t s, vx_mm::mem_req_stratergy m_req_s)
{
    (void)m_req_s;
    return greedy_mngr->alloc(s);
}

void *vx_mm::vx_managed_memory::vx_calloc(size_t s, size_t n, vx_mm::mem_req_stratergy m_req_s)
{
    (void)m_req_s;
    return greedy_mngr->calloc(s, n);
}

void *vx_mm::vx_managed_memory::vx_realloc(void *p, size_t s, vx_mm::mem_req_stratergy m_req_s)
{
    (void)m_req_s;
    return greedy_mngr->realloc(p, s);
}

void vx_mm::vx_managed_memory::vx_free(void *p, vx_mm::mem_req_stratergy m_req_s)
{
    (void)m_req_s;
    greedy_mngr->free(p);
}

void vx_mm::vx_managed_memory::release_all(vx_mm::mem_req_stratergy m_req_s)
{
    (void)m_req_s;
    //delete pointer here
}

void vx_mm::vx_managed_memory::initialize(vx_mm::mem_req_stratergy m_req_s)
{
    (void)m_req_s;
    //create new object here
    greedy_mngr = new vx_mem_mngr_t1();
}

