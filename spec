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

beginseg
  name "cardclubs10"
  after code
  flags  object
  include "sprites/cardclubs10.o"
endseg

beginseg
  name "cardclubsj"
  after cardclubs10
  flags object
  include "sprites/cardclubsj.o"
endseg

beginseg
  name "carddiamonds8"
  after cardclubsj
  flags object
  include "sprites/carddiamonds8.o"
endseg

beginseg
  name "cardhearts5"
  after carddiamonds8
  flags object
  include "sprites/cardhearts5.o"
endseg

beginseg
  name "cardspades10"
  after cardhearts5
  flags object
  include "sprites/cardspades10.o"
endseg

beginseg
  name "cardspadesj"
  after cardspades10
  flags object
  include "sprites/cardspadesj.o"
endseg

beginseg
  name "cardclubs2"
  after cardspadesj
  flags object
  include "sprites/cardclubs2.o"
endseg

beginseg
  name "cardclubsk"
  after cardclubs2
  flags object
  include "sprites/cardclubsk.o"
endseg

beginseg
  name "carddiamonds9"
  after cardclubsk
  flags object
  include "sprites/carddiamonds9.o"
endseg

beginseg
  name "cardhearts6"
  after carddiamonds9
  flags object
  include "sprites/cardhearts6.o"
endseg

beginseg
  name "cardspades2"
  after cardhearts6
  flags object
  include "sprites/cardspades2.o"
endseg

beginseg
  name "cardspadesk"
  after cardspades2
  flags object
  include "sprites/cardspadesk.o"
endseg

beginseg
  name "cardclubs3"
  after cardspadesk
  flags object
  include "sprites/cardclubs3.o"
endseg

beginseg
  name "cardclubsq"
  after cardclubs3
  flags object
  include "sprites/cardclubsq.o"
endseg

beginseg
  name "carddiamondsa"
  after cardclubsq
  flags object
  include "sprites/carddiamondsa.o"
endseg

beginseg
  name "cardhearts7"
  after carddiamondsa
  flags object
  include "sprites/cardhearts7.o"
endseg

beginseg
  name "cardspades3"
  after cardhearts7
  flags object
  include "sprites/cardspades3.o"
endseg

beginseg
  name "cardspadesq"
  after cardspades3
  flags object
  include "sprites/cardspadesq.o"
endseg

beginseg
  name "cardclubs4"
  after cardspadesq
  flags object
  include "sprites/cardclubs4.o"
endseg

beginseg
  name "carddiamonds10"
  after cardclubs4
  flags object
  include "sprites/carddiamonds10.o"
endseg

beginseg
  name "carddiamondsj"
  after carddiamonds10
  flags object
  include "sprites/carddiamondsj.o"
endseg

beginseg
  name "cardhearts8"
  after carddiamondsj
  flags object
  include "sprites/cardhearts8.o"
endseg

beginseg
  name "cardspades4"
  after cardhearts8
  flags object
  include "sprites/cardspades4.o"
endseg

beginseg
  name "cardclubs5"
  after cardspades4
  flags object
  include "sprites/cardclubs5.o"
endseg

beginseg
  name "carddiamonds2"
  after cardclubs5
  flags object
  include "sprites/carddiamonds2.o"
endseg

beginseg
  name "carddiamondsk"
  after carddiamonds2
  flags object
  include "sprites/carddiamondsk.o"
endseg

beginseg
  name "cardhearts9"
  after carddiamondsk
  flags object
  include "sprites/cardhearts9.o"
endseg

beginseg
  name "cardspades5"
  after cardhearts9
  flags object
  include "sprites/cardspades5.o"
endseg

beginseg
  name "cardclubs6"
  after cardspades5
  flags object
  include "sprites/cardclubs6.o"
endseg

beginseg
  name "carddiamonds3"
  after cardclubs6
  flags object
  include "sprites/carddiamonds3.o"
endseg

beginseg
  name "carddiamondsq"
  after carddiamonds3
  flags object
  include "sprites/carddiamondsq.o"
endseg

beginseg
  name "cardheartsa"
  after carddiamondsq
  flags object
  include "sprites/cardheartsa.o"
endseg

beginseg
  name "cardspades6"
  after cardheartsa
  flags object
  include "sprites/cardspades6.o"
endseg

beginseg
  name "cardclubs7"
  after cardspades6
  flags object
  include "sprites/cardclubs7.o"
endseg

beginseg
  name "carddiamonds4"
  after cardclubs7
  flags object
  include "sprites/carddiamonds4.o"
endseg

beginseg
  name "cardhearts10"
  after carddiamonds4
  flags object
  include "sprites/cardhearts10.o"
endseg

beginseg
  name "cardheartsj"
  after cardhearts10
  flags object
  include "sprites/cardheartsj.o"
endseg

beginseg
  name "cardspades7"
  after cardheartsj
  flags object
  include "sprites/cardspades7.o"
endseg

beginseg
  name "test_joker"
  after cardspades7
  flags object
  include "sprites/test_joker.o"
endseg

beginseg
  name "cardclubs8"
  after test_joker
  flags object
  include "sprites/cardclubs8.o"
endseg

beginseg
  name "carddiamonds5"
  after cardclubs8
  flags object
  include "sprites/carddiamonds5.o"
endseg

beginseg
  name "cardhearts2"
  after carddiamonds5
  flags object
  include "sprites/cardhearts2.o"
endseg

beginseg
  name "cardheartsk"
  after cardhearts2
  flags object
  include "sprites/cardheartsk.o"
endseg

beginseg
  name "cardspades8"
  after cardheartsk
  flags object
  include "sprites/cardspades8.o"
endseg

beginseg
  name "cardclubs9"
  after cardspades8
  flags object
  include "sprites/cardclubs9.o"
endseg

beginseg
  name "carddiamonds6"
  after cardclubs9
  flags object
  include "sprites/carddiamonds6.o"
endseg

beginseg
  name "cardhearts3"
  after carddiamonds6
  flags object
  include "sprites/cardhearts3.o"
endseg

beginseg
  name "cardheartsq"
  after cardhearts3
  flags object
  include "sprites/cardheartsq.o"
endseg

beginseg
  name "cardspades9"
  after cardheartsq
  flags object
  include "sprites/cardspades9.o"
endseg

beginseg
  name "cardclubsa"
  after cardspades9
  flags object
  include "sprites/cardclubsa.o"
endseg

beginseg
  name "carddiamonds7"
  after cardclubsa
  flags object
  include "sprites/carddiamonds7.o"
endseg

beginseg
  name "cardhearts4"
  after carddiamonds7
  flags object
  include "sprites/cardhearts4.o"
endseg

beginseg
  name "cardjoker"
  after cardhearts4
  flags object
  include "sprites/cardjoker.o"
endseg

beginseg
  name "cardspadesa"
  after cardjoker
  flags object
  include "sprites/cardspadesa.o"
endseg


beginwave
  name	"nu5"
  include	"code"
  include "cardclubs10"
  include "cardclubsj"
  include "carddiamonds8"
  include "cardhearts5"
  include "cardspades10"
  include "cardspadesj"
  include "cardclubs2"
  include "cardclubsk"
  include "carddiamonds9"
  include "cardhearts6"
  include "cardspades2"
  include "cardspadesk"
  include "cardclubs3"
  include "cardclubsq"
  include "carddiamondsa"
  include "cardhearts7"
  include "cardspades3"
  include "cardspadesq"
  include "cardclubs4"
  include "carddiamonds10"
  include "carddiamondsj"
  include "cardhearts8"
  include "cardspades4"
  include "cardclubs5"
  include "carddiamonds2"
  include "carddiamondsk"
  include "cardhearts9"
  include "cardspades5"
  include "cardclubs6"
  include "carddiamonds3"
  include "carddiamondsq"
  include "cardheartsa"
  include "cardspades6"
  include "cardclubs7"
  include "carddiamonds4"
  include "cardhearts10"
  include "cardheartsj"
  include "cardspades7"
  include "test_joker"
  include "cardclubs8"
  include "carddiamonds5"
  include "cardhearts2"
  include "cardheartsk"
  include "cardspades8"
  include "cardclubs9"
  include "carddiamonds6"
  include "cardhearts3"
  include "cardheartsq"
  include "cardspades9"
  include "cardclubsa"
  include "carddiamonds7"
  include "cardhearts4"
  include "cardjoker"
  include "cardspadesa"
  include "donsolptr"
  include "donsolwbank"
  include "donsolbin"
  include "donsolbfx"
  include "countptr"
  include "countwbank"
  include "countbin"
endwave
