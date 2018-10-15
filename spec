/*
	ROM spec file

	Main memory map

  	0x80000000  exception vectors, ...
  	0x80000400  zbuffer (size 320*240*2)
  	0x80025c00  codesegment
	      :
  	0x8030F800  Audio Heap
  	0x8038F800  cfb 16b 3buffer (size 320*240*2*3)

   	Copyright (C) 1997-1999, NINTENDO Co,Ltd.
*/

#include <nusys.h>

/* Use all graphic an N_audio Micro codes */
beginseg
	name	"code"
	flags	BOOT OBJECT
	entry 	nuBoot
	address NU_SPEC_BOOT_ADDR
        stack   NU_SPEC_BOOT_STACK
	include "codesegment.o"
	include "$(ROOT)/usr/lib/PR/n_aspMain.o"
	include "$(ROOT)/usr/lib/PR/rspboot.o"
	include "$(ROOT)/usr/lib/PR/gspF3DEX2.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspL3DEX2.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspF3DEX2.Rej.fifo.o"
        include "$(ROOT)/usr/lib/PR/gspF3DEX2.NoN.fifo.o"
        include "$(ROOT)/usr/lib/PR/gspF3DLX2.Rej.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspS2DEX2.fifo.o"
endseg

beginseg
  name "donsolptr"
  flags RAW
  include "gamesnd.ptr"
endseg

beginseg
  name "donsolwbank"
  flags RAW
  include "gamesnd.wbk"
endseg

beginseg
  name "donsolbin"
  flags RAW
  include "ambient.bin"
endseg

beginseg
  name "donsolbfx"
  flags RAW
  include "gamesnd.bfx"
endseg

beginseg
  name "countptr"
  flags RAW
  include "count.ptr"
endseg

beginseg
  name "countwbank"
  flags RAW
  include "count.wbk"
endseg

beginseg
  name "countbin"
  flags RAW
  include "count.bin"
endseg

beginwave
  name	"nu5"
  include	"code"
  include "donsolptr"
  include "donsolwbank"
  include "donsolbin"
  include "donsolbfx"
  include "countptr"
  include "countwbank"
  include "countbin"
endwave
