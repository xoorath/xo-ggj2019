// File takes inspiration from my c++11 allocator: https://github.com/xoorath/xo-alloc/blob/master/xo-alloc.h
#ifndef __XO_ALLOC_H_
#define __XO_ALLOC_H_

#include <PR/ultratypes.h>

typedef char              byte_t;
typedef u32               xo_alloc_size_t;
typedef xo_alloc_size_t   xo_alloc_block_t;

///////////////////////////////////////////////////////////////////////////////////////// Api

typedef struct {
  xo_alloc_size_t size;
  union {
    byte_t *data;
    xo_alloc_block_t* head;
  };
} xo_alloc_buffer;

// Initialize your xo_alloc_buffer before using it, provide it with a buffer of data and a size to manage.
void    xo_alloc_init(xo_alloc_buffer* buff, byte_t* data, xo_alloc_size_t size);

// allocate from the xo_alloc_buffer. No error checking is done.
// ensure you're not asking for too much memory or causing needless fragmentation.
byte_t* xo_alloc_malloc(xo_alloc_buffer* buff, xo_alloc_size_t size);

// free the allocation alloc created with xo_alloc_malloc.
// This will join adjacent memory blocks when possible.
void    xo_alloc_free(xo_alloc_buffer* buff, byte_t* alloc);

#endif