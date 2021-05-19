#include "vx_block_types.h"
#include <vector>

#ifndef VX_PAGE_TYPES_H
#define VX_PAGE_TYPES_H

namespace  vx_types {

    ///Abstract base class for pages
    typedef class vx_page
    {

    public:

        uint id;
        uint parent_id;

        vx_page(size_t page_size, size_t id = 0, size_t parent_id = 0);
        virtual ~vx_page();

        virtual void* allocate(const size_t s) = 0;
        virtual void* callocate(const size_t s) = 0;
        virtual void  release(void* p) = 0;

        virtual size_t size() = 0;
        virtual size_t free_size() = 0;
        virtual size_t used_size() = 0;
        virtual void   reset() = 0;

    protected:

        char* p_memory_chunk;
        char* p_freem_strt;

    }*pvx_page;

    ///Managed page model
    typedef class vx_page_mngd : public vx_page
    {

      public:

        vx_page_mngd(size_t page_size, size_t id = 0, size_t parent_id = 0);
        virtual ~vx_page_mngd();

        virtual void* allocate(const size_t s);
        virtual void* callocate(const size_t s);
        virtual void  release(void* p);
        virtual void  zero(void* p);
        virtual void  reset();

        virtual size_t size();
        virtual size_t free_size();     //Considering we need atleast one block header
        virtual size_t used_size();

      protected:

        size_t free_bytes;
        size_t used_bytes;

        std::vector<pvx_block> free_block_list;
        std::vector<size_t> free_block_size_list;

        virtual size_t    free_blocks_size();
        virtual size_t    add_to_free_list(pvx_block p);
        virtual pvx_block remove_from_free_list(size_t i);
        virtual pvx_block allocate_from_free_list(size_t s);

    }*pvx_page_mngd;

    ///Linear segmented page model
    typedef class vx_page_ls : public vx_page
    {

    public:

        vx_page_ls(size_t page_size, size_t id = 0, size_t parent_id = 0);
        virtual ~vx_page_ls();

        virtual void* allocate(const size_t s);
        virtual void* callocate(const size_t s);
        virtual void  release(void* p);
        virtual void  reset();

        virtual size_t size();
        virtual size_t free_size();     //Considering we need atleast one block header
        virtual size_t used_size();

    protected:

      size_t free_bytes;
      size_t used_bytes;

    }*pvx_page_ls;

}

#endif // VX_PAGE_TYPES_H
