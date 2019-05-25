// C port of https://github.com/xoorath/xo-alloc/blob/master/xo-alloc.h

#ifndef __XO_ALLOC_H_
#define __XO_ALLOC_H_

#include <xo-types.h>

///////////////////////////////////////////////////////////////////////////////////////// Block (internal)

typedef struct {
  u32 free : 1;
  u32 size : 31;
} AllocBlock_t;

AllocBlock_t* xo_alloc_get_next_block(AllocBlock_t* block);
AllocBlock_t* xo_alloc_get_prev_block(AllocBlock_t* head, AllocBlock_t* block);
void          xo_alloc_join_blocks   (AllocBlock_t* head, AllocBlock_t* end, AllocBlock_t* mem);

///////////////////////////////////////////////////////////////////////////////////////// Allocator (api)

typedef struct {
  AllocBlock_t* head;
  u32 size;
} BlockAllocator_t;

void  xo_alloc_init_allocator(BlockAllocator_t* allocator, void* mem, u32 size);
void* xo_alloc_malloc        (BlockAllocator_t* allocator, u32 size);
void  xo_alloc_free          (BlockAllocator_t* allocator, void* mem);

// alligned malloc/free, always use together.
void* xo_alloc_malloc8        (BlockAllocator_t* allocator, u32 size);
void  xo_alloc_free8          (BlockAllocator_t* allocator, void* mem);

// dbg
void xo_alloc_dbg_draw(BlockAllocator_t* allocator);

#endif