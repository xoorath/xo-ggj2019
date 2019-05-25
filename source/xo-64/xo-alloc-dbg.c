#include <PR/ultratypes.h>
#include <xo-alloc.h>
#include <xo-render.h>

void xo_alloc_dbg_draw(BlockAllocator_t* allocator) {
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

    nuDebConTextPos(0, 1, 10);
    nuDebConPrintf(NU_DEB_CON_WINDOW0, "bytes n:%d sys:%d", (int)size_bytes, (int)sys_bytes);
    nuDebConTextPos(0, 1, 11);
    nuDebConPrintf(NU_DEB_CON_WINDOW0, "bytes free:%d used:%d", (int)unused_bytes, (int)used_bytes);
    nuDebConTextPos(0, 1, 12);
    nuDebConPrintf(NU_DEB_CON_WINDOW0, "blocks n:%d free:%d used:%d", (int)blocks_free+(int)blocks_used, (int)blocks_free, (int)blocks_used);

    nuDebConTextColor(0, NU_DEB_CON_TEXT_WHITE);
  }
}