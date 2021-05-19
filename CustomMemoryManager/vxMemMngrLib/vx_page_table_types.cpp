#include "vx_page_table_types.h"

using namespace std;

vx_types::vx_page_table::vx_page_table(uint pt_id, size_t incr_alloc_size, size_t page_size)
{
    this->id = pt_id;
    this->page_id_gen = 0;
    this->page_count = VX_PAGE_COUNT(VX_DFLT_INIT_ALLOC_SIZE, page_size);
    this->page_size = page_size;    
    this->incr_alloc_size = incr_alloc_size;
    initialize(VX_DFLT_INIT_ALLOC_SIZE);
}

vx_types::vx_page_table::~vx_page_table()
{
    //Release objects held by used list
    if(used_list.size() > 0)
    {
        for(list<pvx_page>::iterator itr = used_list.begin();
            itr != used_list.end(); itr++)
        {
            //pvx_page tmp_page = (*itr);
            //delete(tmp_page);
            delete((pvx_page_mngd)(*itr));
        }
    }

    //Release objects held by free list
    if(free_list.size() > 0)
    {
        for(list<pvx_page>::iterator itr = free_list.begin();
            itr != free_list.end(); itr++)
        {
            //pvx_page tmp_page = (*itr);
            //delete(tmp_page);
            delete((pvx_page_mngd)(*itr));
        }
    }

    //Release objects held by full list
    if(full_list.size() > 0)
    {
        for(size_t i = 0; i < full_list.size(); i++)
        {
            delete((pvx_page_mngd)full_list[0]);
        }
    }
}

void* vx_types::vx_page_table::allocate(size_t s)
{
    void* new_mem = NULL;
    pvx_page page = get_page_by_size(s);

    if(page == NULL)
        return NULL;

    //If everything is ok then finally allocate mem
    new_mem = page->allocate(s);

    return new_mem;
}

void* vx_types::vx_page_table::callocate(size_t s, size_t n)
{
    void* new_mem = NULL;
    pvx_page page = get_page_by_size(s * n);

    if(page == NULL)
        return NULL;

    new_mem = page->callocate(s * n);
    return new_mem;
}

void *vx_types::vx_page_table::reallocate(void *p, size_t s)
{
    void* new_mem = NULL;

    if(p == NULL)
        return NULL;
    else
        allocate(s);

    if(new_mem == NULL)
        return NULL;

    pvx_block old_block_h = vx_block::extract_header(p);
    pvx_block new_block_h = vx_block::extract_header(new_mem);

    char* str1 = old_block_h->data();
    char* str2 = new_block_h->data();

    while(str1 <= (old_block_h->data() + old_block_h->length()))
    {
        *str2++ = *str1++;
    }

    release(p);
    return str2;
}

void  vx_types::vx_page_table::release(void *p)
{
    //TODO: This part must be done on a separate thread
    //to not delay the caller when not necessary
    pvx_block block_h = vx_block::extract_header(p);

    //Verify to see if the block is valid for this table
    if(block_h->pt_id == id)
    {
        pvx_page_mngd page = static_cast<pvx_page_mngd>(get_page(block_h->p_id));

        if(page != NULL)
            page->release(p);
    }

    //size_t released_bytes = abs(p->d_end - p->d_start) + sizeof(vx_block);
}

void  vx_types::vx_page_table::initialize(size_t init_alloc_size)
{
    //Initialize initial stage of page table
    enlarge_free_list(init_alloc_size);
}

vx_types::pvx_page vx_types::vx_page_table::new_page()
{
    page_id_gen++;
    pvx_page_mngd page = new vx_page_mngd(page_size, id);
    page->id = page_id_gen;
    return page;
}

vx_types::pvx_page vx_types::vx_page_table::get_page_by_size(size_t s)
{
    bool full_pages_present = false;

    //Try to find something accomodating in existing list
    //If found return immidiately else get new page
    for(list<pvx_page>::iterator itr = used_list.begin();
        used_list.size() > 0 && itr != used_list.end(); itr++)
    {
        pvx_page tmp_page = (*itr);

        if(tmp_page->free_size() > s)
        {
            return tmp_page;
        }
        else if(tmp_page->free_size() < 4)
        {
            full_list.push_back(tmp_page);
            full_pages_present = true;
        }
    }

    //Remove any full pages if marked
    if(full_pages_present)
    {
        for(size_t i = 0; i < full_list.size(); i++)
            used_list.remove(full_list[i]);
    }

    //If free list is empty enlarge it first
    if(free_list.size() == 0)
        enlarge_free_list();

    //Take an empty page and try to fulfill request
    pvx_page free_page = free_list.front();
    free_list.pop_front();
    used_list.push_back(free_page);

    return free_page;
}

vx_types::pvx_page vx_types::vx_page_table::get_page(size_t page_id)
{
    //If id is bigger than the allocated ids return
    if(page_id > page_id_gen)
        return NULL;

    //Find the page in used list
    for (pvx_page pg : used_list)
       if(pg->id == page_id)
           return pg;

    //Nothing found so return
    return NULL;
}

vx_types::pvx_page vx_types::vx_page_table::recover_rel_mem()
{

    return NULL;
}

size_t vx_types::vx_page_table::enlarge_free_list(size_t incr_size)
{
    size_t i = 0;

    size_t size = VX_PAGE_COUNT(incr_size, page_size);

    for(i = 0; i < size; i++)
    {
        pvx_page pg = new_page();

        if(pg == NULL)
            break;

        free_list.push_back(pg);
    }

    page_count += i;

    return ((i == 0) ? 0 : --i);
}
