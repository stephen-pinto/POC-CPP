#include "vx_mm_base_types.h"

using namespace vx_mm;

vx_mem_mngr_types::vx_mem_mngr_t1::vx_mem_mngr_t1()
{
    page_table = get_page_tbl(mem_req_stratergy::ms_normal);
}

vx_mem_mngr_types::vx_mem_mngr_t1::~vx_mem_mngr_t1()
{
    delete(page_table);
}

void *vx_mem_mngr_types::vx_mem_mngr_t1::alloc(size_t s)
{
    return page_table->allocate(s);
}

void *vx_mem_mngr_types::vx_mem_mngr_t1::calloc(size_t s, size_t n)
{
    return page_table->callocate(s, n);
}

void *vx_mem_mngr_types::vx_mem_mngr_t1::realloc(void *p, size_t s)
{
    return page_table->reallocate(p, s);
}

void vx_mem_mngr_types::vx_mem_mngr_t1::free(void *p)
{    
    page_table->release(p);
}

vx_types::pvx_page_table vx_mem_mngr_types::vx_mem_mngr_t1::get_page_tbl(mem_req_stratergy m_req_s)
{
    pvx_page_table ptable = new vx_page_table(1);
    return ptable;
}
