#include "xo-alloc.h"

u32 xo_alloc_block_get_size(xo_alloc_block_t* block) {
  return (*block)&0x7fffffff;
}

u8 xo_alloc_block_get_free(xo_alloc_block_t* block) {
  return (!!((*block)&0x80000000));
}

void xo_alloc_block_set_size(xo_alloc_block_t*block, u32 sz) {
  *block = (sz&0x7fffffff) | (xo_alloc_block_get_free(block)<<31);
}

void xo_alloc_block_set_free(xo_alloc_block_t* block, u8 fr) {
  *block |= ((!!fr)<<31);
}

static xo_alloc_block_t* xo_alloc_begin(xo_alloc_buffer* buff) {
  buff->head;
}

static xo_alloc_block_t* xo_alloc_end(xo_alloc_buffer* buff) {
  return (xo_alloc_block_t*)(buff->data + buff->size);
}

static xo_alloc_block_t* xo_alloc_next_block(xo_alloc_block_t* block) {
  return ((byte_t*)block) + xo_alloc_block_get_size(block) + sizeof(xo_alloc_block_t);
}

static xo_alloc_block_t* xo_alloc_prev_block(xo_alloc_block_t* begin, xo_alloc_block_t* block) {
  while((byte_t*)begin + xo_alloc_block_get_size(begin) + sizeof(xo_alloc_block_t) < (byte_t*)block) {
      begin = xo_alloc_next_block(begin);
  }
  return begin;
}

static void xo_alloc_join_blocks(xo_alloc_buffer* buff, xo_alloc_block_t* b, xo_alloc_block_t* e, xo_alloc_block_t* m) {
  if(xo_alloc_block_get_free(m)) {
    xo_alloc_block_t* n = xo_alloc_next_block(m);
    xo_alloc_block_t* p = xo_alloc_prev_block(b, m);
    // consume the next block, if it's free.
    if(n < e && xo_alloc_block_get_free(n)) {
      xo_alloc_block_set_size(m, (xo_alloc_block_get_size(m) + xo_alloc_block_get_size(n) + sizeof(xo_alloc_block_t)));
      // n is now invalid.
    }

    // consume the previous block.
    if(p != m && xo_alloc_block_get_free(p)) {
      xo_alloc_block_set_size(p, (xo_alloc_block_get_size(m) + sizeof(xo_alloc_block_t)));
      // m is now invalid.
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////

void xo_alloc_init(xo_alloc_buffer* buff, byte_t* data, xo_alloc_size_t size) {
  buff->size = size;
  buff->data = data;
  xo_alloc_block_set_free(buff->head, TRUE);
  xo_alloc_block_set_size(buff->head, size - sizeof(xo_alloc_block_t));
}

byte_t* xo_alloc_malloc(xo_alloc_buffer* buff, xo_alloc_size_t size) {
  xo_alloc_block_t* n;
  xo_alloc_block_t* i = xo_alloc_begin(buff);
  xo_alloc_block_t* e = xo_alloc_end(buff);
  for(;i < e; i = xo_alloc_next_block(i)) {
    if(xo_alloc_block_get_free(i) && xo_alloc_block_get_size(i) >= size) {
      s32 nextSize;
      s32 oldSize = xo_alloc_block_get_size(i);
      xo_alloc_block_set_free(i, FALSE);
      xo_alloc_block_set_size(i, size);
      n = xo_alloc_next_block(i);
      nextSize = (oldSize-size-sizeof(xo_alloc_block_t));
      // if there's not enough space for the next block (meaning n is invalid)
      if(nextSize <= sizeof(xo_alloc_block_t)) {
        xo_alloc_block_set_size(i, xo_alloc_block_get_size(i) + nextSize + sizeof(xo_alloc_block_t));
        n = i;
      }
      // otherwise, break our block in half, creating a new next block.
      else {
        xo_alloc_block_set_free(n, TRUE);
        xo_alloc_block_set_size(n, nextSize);
      }
      return (byte_t*)(i+1);
    }
  }
  return NULL;
}

void xo_alloc_free(xo_alloc_buffer* buff, byte_t* alloc) {
  xo_alloc_block_t* m = ((xo_alloc_block_t*)alloc)-1;
  xo_alloc_block_t* i = xo_alloc_begin(buff);
  xo_alloc_block_t* e = xo_alloc_end(buff);

  if(m < i || m > e) {
    return;
  }
  xo_alloc_block_set_free(m, TRUE);

  xo_alloc_join_blocks(buff, i, e, m);
}