#include <list>
#include <mutex>
#include "vx_page_types.h"
#include "vx_macros.h"

#ifndef VX_PAGE_TABLE_TYPES_H
#define VX_PAGE_TABLE_TYPES_H

namespace  vx_types {

    typedef class vx_page_table
    {

    public:

        uint id;

        vx_page_table(uint id, size_t incr_alloc_size = VX_DFLT_INCR_ALLOC_SIZE, size_t page_size = VX_DFLT_PAGE_SIZE);
        virtual ~vx_page_table();

        virtual void* allocate(size_t s);
        virtual void* callocate(size_t s, size_t n);
        virtual void* reallocate(void* p, size_t s);
        virtual void  release(void* p);

    private:

        std::mutex            lock;
        std::list<pvx_page>   free_list;
        std::list<pvx_page>   used_list;
        std::vector<pvx_page> full_list;

        size_t page_id_gen;
        size_t page_count;
        size_t page_size;
        size_t incr_alloc_size;

        ///Initializer functions
        void    initialize(size_t init_alloc_size);

        ///Helper functions
        pvx_page new_page();
        pvx_page get_page(size_t page_id);
        pvx_page get_page_by_size(size_t s);
        pvx_page recover_rel_mem();

        size_t enlarge_free_list(size_t incr_size = VX_DFLT_INCR_ALLOC_SIZE);

    }*pvx_page_table;

}//vx_types

#endif // VX_PAGE_TABLE_TYPES_H
