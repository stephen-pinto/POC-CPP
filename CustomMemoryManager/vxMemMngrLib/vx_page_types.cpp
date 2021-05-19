#include "vx_page_types.h"

/*
* Base abstract class definition
*/

vx_types::vx_page::vx_page(size_t page_size, size_t id, size_t parent_id)
{
    //Allocate altogether to page size
    this->p_memory_chunk = (char*) malloc (page_size * 1);
    this->p_freem_strt = p_memory_chunk;
    this->parent_id = parent_id;
    this->id = id;
}

vx_types::vx_page::~vx_page()
{
    //Release the memory chunk
    free(p_memory_chunk);
}

/*
*  -------------------------------------------------------------------------
*   Managed memory model implementation
*  -------------------------------------------------------------------------
*/

/// DEBUG functions
/// Temporary and must not be used in live version

void print_array(std::vector<vx_types::pvx_block> list)
{
    for(size_t i = 0; i < list.size(); i++)
    {
        if(list[i] == 0)
            continue;

        std::cout << "\nPT : " << list[i]->p_id << " P : %d" << list[i]->pt_id;
    }
}

/// Actual code

vx_types::vx_page_mngd::vx_page_mngd(size_t page_size, size_t id, size_t parent_id) : vx_page(page_size, id, parent_id)
{
    free_bytes = page_size;
    used_bytes = 0;        
}

vx_types::vx_page_mngd::~vx_page_mngd()
{

}

void* vx_types::vx_page_mngd::allocate(const size_t s)
{
    pvx_block blk = NULL;

    if(free_size() < s)
        return NULL;

    //If free blocks list contains any appropriate
    //free block then return this block
    if(free_blocks_size() >= s)
    {
        blk = allocate_from_free_list(s);

        if(blk != NULL)
        {
            blk->set_header(id, parent_id);
            return blk->data();
        }
    }

    //Prepare block header first
    blk = (pvx_block) p_freem_strt;
    blk->set_header(s, id, parent_id);

    //Shift pointers to book changes
    p_freem_strt = p_freem_strt + blk->total_size();
    free_bytes -= blk->total_size();
    used_bytes += blk->total_size();

    return blk->data();
}

void* vx_types::vx_page_mngd::callocate(const size_t s)
{
    void* ptr = allocate(s);

    if(ptr != NULL)
        zero(ptr);

    return ptr;
}

void vx_types::vx_page_mngd::release(void* p)
{
    //Simply add to the free block list since this memory is segmented
    //so cannot be added back to the pool.
    pvx_block blk = vx_block::extract_header(p);
    add_to_free_list(blk);
}

void vx_types::vx_page_mngd::zero(void *p)
{
    pvx_block blk = vx_block::extract_header(p);

    //Make sure the block belongs in this family
    if(blk->pt_id != parent_id || blk->p_id != id)
       return;

    //Zero out all the memory from start to end
    blk->zero_data();
}

void vx_types::vx_page_mngd::reset()
{
    char* temp_ptr = p_memory_chunk;
    p_memory_chunk = NULL;
    p_freem_strt = NULL;
    free_bytes = 0;
    used_bytes = 0;
    delete(temp_ptr);
}

size_t vx_types::vx_page_mngd::size()
{
    return free_size() + used_size();
}

size_t vx_types::vx_page_mngd::free_size()
{
    //Considering atleast one header is needed
    return free_blocks_size() + (free_bytes - sizeof(vx_block));
}

size_t vx_types::vx_page_mngd::used_size()
{
    return used_bytes - free_blocks_size();
}

size_t vx_types::vx_page_mngd::free_blocks_size()
{
    size_t total = 0;

    for(size_t i = 0; i < free_block_size_list.size(); i++)
    {
        if(free_block_list[i] != 0)
        {
            total += free_block_size_list[i];
        }
    }

    return total;
}

size_t vx_types::vx_page_mngd::add_to_free_list(vx_types::pvx_block p)
{
    //See if there already exist an empty slot
    for(size_t i = 0; i < free_block_size_list.size(); i++)
    {
        //If so then add to it
        if(free_block_size_list[i] == 0)
        {
            free_block_list[i] = p;
            free_block_size_list[i] = p->length();
            return i;
        }
    }

    //If not increase the vector size
    free_block_list.push_back(p);
    free_block_size_list.push_back(p->length());

    return free_block_list.size() - 1;
}

vx_types::pvx_block vx_types::vx_page_mngd::remove_from_free_list(size_t i)
{
    if(free_block_list.size() < i)
        return NULL;

    pvx_block blk = free_block_list[i];
    free_block_list[i] = NULL;
    free_block_size_list[i] = 0;

    return blk;
}

vx_types::pvx_block vx_types::vx_page_mngd::allocate_from_free_list(size_t s)
{
    for(size_t i = 0; i < free_block_size_list.size(); i++)
    {
        //If a sufficient free block is found mark vector
        //index as emtpy and return to the caller new block
        if(free_block_size_list[i] >= s)
        {
            return remove_from_free_list(i);
        }
    }

    return NULL;
}

/*
*  -------------------------------------------------------------------------
*   Linear segmented memory model implementation
*  -------------------------------------------------------------------------
*/

vx_types::vx_page_ls::vx_page_ls(size_t page_size, size_t id, size_t parent_id) : vx_page(page_size, id, parent_id)
{
    free_bytes = page_size;
    used_bytes = 0;
}

vx_types::vx_page_ls::~vx_page_ls()
{

}

void* vx_types::vx_page_ls::allocate(const size_t s)
{
    if(free_size() < s)
        return NULL;

    void* ptr_m = p_freem_strt;

    //Shift pointers to book changes
    p_freem_strt = p_freem_strt + s;
    free_bytes  -= s;
    used_bytes  += s;

    return ptr_m;
}

void* vx_types::vx_page_ls::callocate(const size_t s)
{
    char* ptr = static_cast<char*>(allocate(s));

    if(ptr != NULL)
    {
        for(size_t i = 0; i < s; i++)
        {
            ptr[i] = 0;
        }
    }

    return ptr;
}

void vx_types::vx_page_ls::release(void* p)
{
    //Do nothing here. Page table will manage
    //this page when needed
    p = p;
}

void vx_types::vx_page_ls::reset()
{
    char* temp_ptr = p_memory_chunk;
    p_memory_chunk = NULL;
    p_freem_strt = NULL;
    free_bytes = 0;
    used_bytes = 0;
    delete(temp_ptr);
}

size_t vx_types::vx_page_ls::size()
{
    return free_bytes + used_bytes;
}

size_t vx_types::vx_page_ls::free_size()
{
    return free_bytes;
}

size_t vx_types::vx_page_ls::used_size()
{
    return used_bytes;
}
