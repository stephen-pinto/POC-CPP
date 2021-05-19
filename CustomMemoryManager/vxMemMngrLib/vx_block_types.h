#include <iostream>
#include <math.h>

#include "vx_typedefs.h"

#ifndef VX_BLOCK_TYPES_H
#define VX_BLOCK_TYPES_H

#define VALID_BLOCK_MARK 1001001

/// Note we could use virtual functions to allow inherit but if we
/// we do that then we will require more memory for header and we
/// must use new converter for existing memory

namespace  vx_types {

    typedef struct vx_block *pvx_block;

    struct vx_block
    {
        uint pt_id;
        uint p_id;

        inline size_t length()
        {
            return len;
        }

        inline size_t total_size()
        {
            return header_size() + length();
        }

        void set_header(const size_t data_len, const uint page_id, const uint page_table_id)
        {
            len = data_len;
            pt_id = page_table_id;
            p_id = page_id;
        }

        void set_header(const uint page_id, const uint page_table_id)
        {
            pt_id = page_table_id;
            p_id = page_id;
        }

        inline void zero_data()
        {
            char* data_ptr = data(this);
            size_t i = 0;

            while(i++ < len)
                data_ptr[i] = 0;
        }

        inline char* data()
        {
            return data(this);
        }

        static inline pvx_block extract_header(void* ptr)
        {
            char* temp_ptr = static_cast<char*>(ptr) - header_size();
            return reinterpret_cast<pvx_block>(temp_ptr);
        }

        static inline char* data(pvx_block blk_strt)
        {
            return reinterpret_cast<char*>(blk_strt) + header_size();
        }

    private:

        static inline size_t header_size()
        {
            return sizeof(vx_block);
        }

        size_t len;    
    };
}

#endif // VX_BLOCK_TYPES_H
