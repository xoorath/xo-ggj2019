#ifndef __XO_BUFFERS_H_
#define __XO_BUFFERS_H_

#define xo_buffer_mb(x) x*1024*1024
#define xo_buffer_kb(x) x*1024

// How much memory is reserved for textures?
#define XO_BUFFER_TEX_MEM                         xo_buffer_kb(4*32)


#endif