#include <xo-alloc.h>

#include <xo-types.h>
#include <xo-render.h>

void xo_alloc_dbg_draw(BlockAllocator_t* allocator, u32 x, u32 y) {
  u32
    size_bytes,
    used_bytes,
    unused_bytes,
    sys_bytes,
    blocks_free,
    blocks_used;

  AllocBlock_t *current, *end;

  if(allocator != NULL) {

    size_bytes = allocator->size;
    used_bytes = 0;
    unused_bytes = 0;
    sys_bytes = 0;
    blocks_free = 0;
    blocks_used = 0;

    current = allocator->head;
    end = (AllocBlock_t*)(((char*)allocator->head) + allocator->size);

    while(current < end) {
      sys_bytes += sizeof(AllocBlock_t);

      if(current->free) {
        unused_bytes += current->size;
        blocks_free++;
      } else {
        used_bytes += current->size;
        blocks_used++;
      }

      current = xo_alloc_get_next_block(current);
    }

    nuDebConTextColor(0, NU_DEB_CON_TEXT_BLUE);

    nuDebConTextPos(0, x, y+0);
    nuDebConPrintf(NU_DEB_CON_WINDOW0, "bytes n:%u sys:%u", size_bytes, sys_bytes);
    nuDebConTextPos(0, x, y+1);
    nuDebConPrintf(NU_DEB_CON_WINDOW0, "bytes free:%u used:%u", unused_bytes, used_bytes);
    nuDebConTextPos(0, x, y+2);
    nuDebConPrintf(NU_DEB_CON_WINDOW0, "blocks n:%u free:%u used:%u", blocks_free+blocks_used, blocks_free, blocks_used);

    nuDebConTextColor(0, NU_DEB_CON_TEXT_WHITE);
  }
}