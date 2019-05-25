#include <xo-alloc.h>
#include <xo-types.h>

///////////////////////////////////////////////////////////////////////////////////////// Block (internal)

AllocBlock_t* xo_alloc_get_next_block(AllocBlock_t* block) {
  return (AllocBlock_t*)((char*)(block) + block->size + sizeof(AllocBlock_t));
}

AllocBlock_t* xo_alloc_get_prev_block(AllocBlock_t* head, AllocBlock_t* block) {
  while(((char*)head) + head->size + sizeof(AllocBlock_t) < (char*)block) {
    head = xo_alloc_get_next_block(head);
  }
  return head;
}

void xo_alloc_join_blocks(AllocBlock_t* head, AllocBlock_t* end, AllocBlock_t* mem) {
    if(mem->free) {
      AllocBlock_t* n = xo_alloc_get_next_block(mem);
      AllocBlock_t* p = xo_alloc_get_prev_block(head, mem);
      // consume the next block, if it's free.
      if(n < end && n->free) {
        mem->size += n->size + sizeof(AllocBlock_t);
        // n is now invalid.
      }

      // consume the previous block.
      if(p != mem && p->free) {
        p->size += mem->size + sizeof(AllocBlock_t);
        // m is now invalid.
      }
    }
}

///////////////////////////////////////////////////////////////////////////////////////// Allocator (api)

void xo_alloc_init_allocator(BlockAllocator_t* allocator, void* mem, u32 size) {
  allocator->head = (AllocBlock_t*)mem;
  allocator->head->free = TRUE;
  allocator->head->size = size - sizeof(AllocBlock_t);
  allocator->size = size;
}

void* xo_alloc_malloc(BlockAllocator_t* allocator, u32 size) {
  s32 oldSize, nextSize;
  AllocBlock_t* n;
  AllocBlock_t* i = allocator->head;
  AllocBlock_t* e = (AllocBlock_t*)((char*)allocator->head + allocator->size);

  for(;i < e; i = xo_alloc_get_next_block(i)) {
    if(i->free && i->size >= size) {
      i->free = FALSE;
      oldSize = i->size;
      i->size = size;
      n = xo_alloc_get_next_block(i);
      nextSize = (oldSize-(s32)size-sizeof(AllocBlock_t));
      // if there's not enough space for the next block (meaning n is invalid)
      if(nextSize <= sizeof(AllocBlock_t)) {
        i->size += nextSize + sizeof(AllocBlock_t);
        // n = i; // true, but the assignment is not needed
      }
      // otherwise, break our block in half, creating a new next block.
      else {
        n->free = TRUE;
        n->size = nextSize;
      }
      return (char*)(i)+sizeof(AllocBlock_t);
    }
  }
  return NULL;
}

void xo_alloc_free(BlockAllocator_t* allocator, void* mem) {
  AllocBlock_t* m = (AllocBlock_t*)(((char*)mem)-sizeof(AllocBlock_t));
  AllocBlock_t* i = allocator->head;
  AllocBlock_t* e = (AllocBlock_t*)((char*)allocator->head + allocator->size);

  if(m < i || m > e) {
    return;
  }
  m->free = TRUE;
  xo_alloc_join_blocks(i, e, m);
}

void* xo_alloc_malloc8        (BlockAllocator_t* allocator, u32 size) {
  union {
    char* m;
    u32 s;
  } x;
  x.m = xo_alloc_malloc(allocator, size+8);
  return x.m + 8-(s32)(x.s%8);
}

void  xo_alloc_free8          (BlockAllocator_t* allocator, void* mem){
  AllocBlock_t* m = (AllocBlock_t*)(((char*)mem)-sizeof(AllocBlock_t));
  AllocBlock_t* i = allocator->head;
  AllocBlock_t* e = (AllocBlock_t*)((char*)allocator->head + allocator->size);

  if(m < i || m > e) {
    return;
  }

  while(((char*)i) + i->size + sizeof(AllocBlock_t) < (char*)m) {
    i = xo_alloc_get_next_block(i);
  }

  if(i < e) {
    xo_alloc_free(allocator, ((char*)i)+sizeof(AllocBlock_t));
  }
}