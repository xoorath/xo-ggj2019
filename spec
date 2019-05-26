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
  name "cardback"
  after code
  flags object
  include "sprites/cardback.o"
endseg

beginseg
  name "cardclubs10_l"
  flags object
  after cardback
  include "sprites/cardclubs10_l.o"
endseg

beginseg
  name "cardclubs10"
  flags object
  after cardclubs10_l
  include "sprites/cardclubs10.o"
endseg

beginseg
  name "cardclubs2_l"
  flags object
  after cardclubs10
  include "sprites/cardclubs2_l.o"
endseg

beginseg
  name "cardclubs2"
  flags object
  after cardclubs2_l
  include "sprites/cardclubs2.o"
endseg

beginseg
  name "cardclubs3_l"
  flags object
  after cardclubs2
  include "sprites/cardclubs3_l.o"
endseg

beginseg
  name "cardclubs3"
  flags object
  after cardclubs3_l
  include "sprites/cardclubs3.o"
endseg

beginseg
  name "cardclubs4_l"
  flags object
  after cardclubs3
  include "sprites/cardclubs4_l.o"
endseg

beginseg
  name "cardclubs4"
  flags object
  after cardclubs4_l
  include "sprites/cardclubs4.o"
endseg

beginseg
  name "cardclubs5_l"
  flags object
  after cardclubs4
  include "sprites/cardclubs5_l.o"
endseg

beginseg
  name "cardclubs5"
  flags object
  after cardclubs5_l
  include "sprites/cardclubs5.o"
endseg

beginseg
  name "cardclubs6_l"
  flags object
  after cardclubs5
  include "sprites/cardclubs6_l.o"
endseg

beginseg
  name "cardclubs6"
  flags object
  after cardclubs6_l
  include "sprites/cardclubs6.o"
endseg

beginseg
  name "cardclubs7_l"
  flags object
  after cardclubs6
  include "sprites/cardclubs7_l.o"
endseg

beginseg
  name "cardclubs7"
  flags object
  after cardclubs7_l
  include "sprites/cardclubs7.o"
endseg

beginseg
  name "cardclubs8_l"
  flags object
  after cardclubs7
  include "sprites/cardclubs8_l.o"
endseg

beginseg
  name "cardclubs8"
  flags object
  after cardclubs8_l
  include "sprites/cardclubs8.o"
endseg

beginseg
  name "cardclubs9_l"
  flags object
  after cardclubs8
  include "sprites/cardclubs9_l.o"
endseg

beginseg
  name "cardclubs9"
  flags object
  after cardclubs9_l
  include "sprites/cardclubs9.o"
endseg

beginseg
  name "cardclubsa_l"
  flags object
  after cardclubs9
  include "sprites/cardclubsa_l.o"
endseg

beginseg
  name "cardclubsa"
  flags object
  after cardclubsa_l
  include "sprites/cardclubsa.o"
endseg

beginseg
  name "cardclubsj_l"
  flags object
  after cardclubsa
  include "sprites/cardclubsj_l.o"
endseg

beginseg
  name "cardclubsj"
  flags object
  after cardclubsj_l
  include "sprites/cardclubsj.o"
endseg

beginseg
  name "cardclubsk_l"
  flags object
  after cardclubsj
  include "sprites/cardclubsk_l.o"
endseg

beginseg
  name "cardclubsk"
  flags object
  after cardclubsk_l
  include "sprites/cardclubsk.o"
endseg

beginseg
  name "cardclubsq_l"
  flags object
  after cardclubsk
  include "sprites/cardclubsq_l.o"
endseg

beginseg
  name "cardclubsq"
  flags object
  after cardclubsq_l
  include "sprites/cardclubsq.o"
endseg

beginseg
  name "carddiamonds10_l"
  flags object
  after cardclubsq
  include "sprites/carddiamonds10_l.o"
endseg

beginseg
  name "carddiamonds10"
  flags object
  after carddiamonds10_l
  include "sprites/carddiamonds10.o"
endseg

beginseg
  name "carddiamonds2_l"
  flags object
  after carddiamonds10
  include "sprites/carddiamonds2_l.o"
endseg

beginseg
  name "carddiamonds2"
  flags object
  after carddiamonds2_l
  include "sprites/carddiamonds2.o"
endseg

beginseg
  name "carddiamonds3_l"
  flags object
  after carddiamonds2
  include "sprites/carddiamonds3_l.o"
endseg

beginseg
  name "carddiamonds3"
  flags object
  after carddiamonds3_l
  include "sprites/carddiamonds3.o"
endseg

beginseg
  name "carddiamonds4_l"
  flags object
  after carddiamonds3
  include "sprites/carddiamonds4_l.o"
endseg

beginseg
  name "carddiamonds4"
  flags object
  after carddiamonds4_l
  include "sprites/carddiamonds4.o"
endseg

beginseg
  name "carddiamonds5_l"
  flags object
  after carddiamonds4
  include "sprites/carddiamonds5_l.o"
endseg

beginseg
  name "carddiamonds5"
  flags object
  after carddiamonds5_l
  include "sprites/carddiamonds5.o"
endseg

beginseg
  name "carddiamonds6_l"
  flags object
  after carddiamonds5
  include "sprites/carddiamonds6_l.o"
endseg

beginseg
  name "carddiamonds6"
  flags object
  after carddiamonds6_l
  include "sprites/carddiamonds6.o"
endseg

beginseg
  name "carddiamonds7_l"
  flags object
  after carddiamonds6
  include "sprites/carddiamonds7_l.o"
endseg

beginseg
  name "carddiamonds7"
  flags object
  after carddiamonds7_l
  include "sprites/carddiamonds7.o"
endseg

beginseg
  name "carddiamonds8_l"
  flags object
  after carddiamonds7
  include "sprites/carddiamonds8_l.o"
endseg

beginseg
  name "carddiamonds8"
  flags object
  after carddiamonds8_l
  include "sprites/carddiamonds8.o"
endseg

beginseg
  name "carddiamonds9_l"
  flags object
  after carddiamonds8
  include "sprites/carddiamonds9_l.o"
endseg

beginseg
  name "carddiamonds9"
  flags object
  after carddiamonds9_l
  include "sprites/carddiamonds9.o"
endseg

beginseg
  name "carddiamondsa_l"
  flags object
  after carddiamonds9
  include "sprites/carddiamondsa_l.o"
endseg

beginseg
  name "carddiamondsa"
  flags object
  after carddiamondsa_l
  include "sprites/carddiamondsa.o"
endseg

beginseg
  name "carddiamondsj_l"
  flags object
  after carddiamondsa
  include "sprites/carddiamondsj_l.o"
endseg

beginseg
  name "carddiamondsj"
  flags object
  after carddiamondsj_l
  include "sprites/carddiamondsj.o"
endseg

beginseg
  name "carddiamondsk_l"
  flags object
  after carddiamondsj
  include "sprites/carddiamondsk_l.o"
endseg

beginseg
  name "carddiamondsk"
  flags object
  after carddiamondsk_l
  include "sprites/carddiamondsk.o"
endseg

beginseg
  name "carddiamondsq_l"
  flags object
  after carddiamondsk
  include "sprites/carddiamondsq_l.o"
endseg

beginseg
  name "carddiamondsq"
  flags object
  after carddiamondsq_l
  include "sprites/carddiamondsq.o"
endseg

beginseg
  name "cardhearts10_l"
  flags object
  after carddiamondsq
  include "sprites/cardhearts10_l.o"
endseg

beginseg
  name "cardhearts10"
  flags object
  after cardhearts10_l
  include "sprites/cardhearts10.o"
endseg

beginseg
  name "cardhearts2_l"
  flags object
  after cardhearts10
  include "sprites/cardhearts2_l.o"
endseg

beginseg
  name "cardhearts2"
  flags object
  after cardhearts2_l
  include "sprites/cardhearts2.o"
endseg

beginseg
  name "cardhearts3_l"
  flags object
  after cardhearts2
  include "sprites/cardhearts3_l.o"
endseg

beginseg
  name "cardhearts3"
  flags object
  after cardhearts3_l
  include "sprites/cardhearts3.o"
endseg

beginseg
  name "cardhearts4_l"
  flags object
  after cardhearts3
  include "sprites/cardhearts4_l.o"
endseg

beginseg
  name "cardhearts4"
  flags object
  after cardhearts4_l
  include "sprites/cardhearts4.o"
endseg

beginseg
  name "cardhearts5_l"
  flags object
  after cardhearts4
  include "sprites/cardhearts5_l.o"
endseg

beginseg
  name "cardhearts5"
  flags object
  after cardhearts5_l
  include "sprites/cardhearts5.o"
endseg

beginseg
  name "cardhearts6_l"
  flags object
  after cardhearts5
  include "sprites/cardhearts6_l.o"
endseg

beginseg
  name "cardhearts6"
  flags object
  after cardhearts6_l
  include "sprites/cardhearts6.o"
endseg

beginseg
  name "cardhearts7_l"
  flags object
  after cardhearts6
  include "sprites/cardhearts7_l.o"
endseg

beginseg
  name "cardhearts7"
  flags object
  after cardhearts7_l
  include "sprites/cardhearts7.o"
endseg

beginseg
  name "cardhearts8_l"
  flags object
  after cardhearts7
  include "sprites/cardhearts8_l.o"
endseg

beginseg
  name "cardhearts8"
  flags object
  after cardhearts8_l
  include "sprites/cardhearts8.o"
endseg

beginseg
  name "cardhearts9_l"
  flags object
  after cardhearts8
  include "sprites/cardhearts9_l.o"
endseg

beginseg
  name "cardhearts9"
  flags object
  after cardhearts9_l
  include "sprites/cardhearts9.o"
endseg

beginseg
  name "cardheartsa_l"
  flags object
  after cardhearts9
  include "sprites/cardheartsa_l.o"
endseg

beginseg
  name "cardheartsa"
  flags object
  after cardheartsa_l
  include "sprites/cardheartsa.o"
endseg

beginseg
  name "cardheartsj_l"
  flags object
  after cardheartsa
  include "sprites/cardheartsj_l.o"
endseg

beginseg
  name "cardheartsj"
  flags object
  after cardheartsj_l
  include "sprites/cardheartsj.o"
endseg

beginseg
  name "cardheartsk_l"
  flags object
  after cardheartsj
  include "sprites/cardheartsk_l.o"
endseg

beginseg
  name "cardheartsk"
  flags object
  after cardheartsk_l
  include "sprites/cardheartsk.o"
endseg

beginseg
  name "cardheartsq_l"
  flags object
  after cardheartsk
  include "sprites/cardheartsq_l.o"
endseg

beginseg
  name "cardheartsq"
  flags object
  after cardheartsq_l
  include "sprites/cardheartsq.o"
endseg

beginseg
  name "cardjoker_l"
  flags object
  after cardheartsq
  include "sprites/cardjoker_l.o"
endseg

beginseg
  name "cardjoker"
  flags object
  after cardjoker_l
  include "sprites/cardjoker.o"
endseg

beginseg
  name "cardspades10_l"
  flags object
  after cardjoker
  include "sprites/cardspades10_l.o"
endseg

beginseg
  name "cardspades10"
  flags object
  after cardspades10_l
  include "sprites/cardspades10.o"
endseg

beginseg
  name "cardspades2_l"
  flags object
  after cardspades10
  include "sprites/cardspades2_l.o"
endseg

beginseg
  name "cardspades2"
  flags object
  after cardspades2_l
  include "sprites/cardspades2.o"
endseg

beginseg
  name "cardspades3_l"
  flags object
  after cardspades2
  include "sprites/cardspades3_l.o"
endseg

beginseg
  name "cardspades3"
  flags object
  after cardspades3_l
  include "sprites/cardspades3.o"
endseg

beginseg
  name "cardspades4_l"
  flags object
  after cardspades3
  include "sprites/cardspades4_l.o"
endseg

beginseg
  name "cardspades4"
  flags object
  after cardspades4_l
  include "sprites/cardspades4.o"
endseg

beginseg
  name "cardspades5_l"
  flags object
  after cardspades4
  include "sprites/cardspades5_l.o"
endseg

beginseg
  name "cardspades5"
  flags object
  after cardspades5_l
  include "sprites/cardspades5.o"
endseg

beginseg
  name "cardspades6_l"
  flags object
  after cardspades5
  include "sprites/cardspades6_l.o"
endseg

beginseg
  name "cardspades6"
  flags object
  after cardspades6_l
  include "sprites/cardspades6.o"
endseg

beginseg
  name "cardspades7_l"
  flags object
  after cardspades6
  include "sprites/cardspades7_l.o"
endseg

beginseg
  name "cardspades7"
  flags object
  after cardspades7_l
  include "sprites/cardspades7.o"
endseg

beginseg
  name "cardspades8_l"
  flags object
  after cardspades7
  include "sprites/cardspades8_l.o"
endseg

beginseg
  name "cardspades8"
  flags object
  after cardspades8_l
  include "sprites/cardspades8.o"
endseg

beginseg
  name "cardspades9_l"
  flags object
  after cardspades8
  include "sprites/cardspades9_l.o"
endseg

beginseg
  name "cardspades9"
  flags object
  after cardspades9_l
  include "sprites/cardspades9.o"
endseg

beginseg
  name "cardspadesa_l"
  flags object
  after cardspades9
  include "sprites/cardspadesa_l.o"
endseg

beginseg
  name "cardspadesa"
  flags object
  after cardspadesa_l
  include "sprites/cardspadesa.o"
endseg

beginseg
  name "cardspadesj_l"
  flags object
  after cardspadesa
  include "sprites/cardspadesj_l.o"
endseg

beginseg
  name "cardspadesj"
  flags object
  after cardspadesj_l
  include "sprites/cardspadesj.o"
endseg

beginseg
  name "cardspadesk_l"
  flags object
  after cardspadesj
  include "sprites/cardspadesk_l.o"
endseg

beginseg
  name "cardspadesk"
  flags object
  after cardspadesk_l
  include "sprites/cardspadesk.o"
endseg

beginseg
  name "cardspadesq_l"
  flags object
  after cardspadesk
  include "sprites/cardspadesq_l.o"
endseg

beginseg
  name "cardspadesq"
  flags object
  after cardspadesq_l
  include "sprites/cardspadesq.o"
endseg

beginseg
  name "cdown"
  flags object
  after cardspadesq
  include "sprites/cdown.o"
endseg

beginseg
  name "cleft"
  flags objec
  after cdown
  include "sprites/cleft.o"
endseg

beginseg
  name "cright"
  flags objec
  after cleft
  include "sprites/cright.o"
endseg

beginseg
  name "cup"
  flags object
  after cright
  include "sprites/cup.o"
endseg

beginseg
  name "test_joker"
  flags obj
  after cup
  include "sprites/test_joker.o"
endseg

beginseg
  name "enterdonsol"
  flags obj
  after test_joker
  include "sprites/enterdonsol.o"
endseg

beginseg
  name "eye0"
  flags obj
  after enterdonsol
  include "sprites/eye0.o"
endseg

beginseg
  name "eye1"
  flags obj
  after eye0
  include "sprites/eye1.o"
endseg

beginseg
  name "eye2"
  flags obj
  after eye1
  include "sprites/eye2.o"
endseg









beginwave
  name	"nu5"
  include	"code"

  include "cardback"
  include "cardclubs10_l"
  include "cardclubs10"
  include "cardclubs2_l"
  include "cardclubs2"
  include "cardclubs3_l"
  include "cardclubs3"
  include "cardclubs4_l"
  include "cardclubs4"
  include "cardclubs5_l"
  include "cardclubs5"
  include "cardclubs6_l"
  include "cardclubs6"
  include "cardclubs7_l"
  include "cardclubs7"
  include "cardclubs8_l"
  include "cardclubs8"
  include "cardclubs9_l"
  include "cardclubs9"
  include "cardclubsa_l"
  include "cardclubsa"
  include "cardclubsj_l"
  include "cardclubsj"
  include "cardclubsk_l"
  include "cardclubsk"
  include "cardclubsq_l"
  include "cardclubsq"
  include "carddiamonds10_l"
  include "carddiamonds10"
  include "carddiamonds2_l"
  include "carddiamonds2"
  include "carddiamonds3_l"
  include "carddiamonds3"
  include "carddiamonds4_l"
  include "carddiamonds4"
  include "carddiamonds5_l"
  include "carddiamonds5"
  include "carddiamonds6_l"
  include "carddiamonds6"
  include "carddiamonds7_l"
  include "carddiamonds7"
  include "carddiamonds8_l"
  include "carddiamonds8"
  include "carddiamonds9_l"
  include "carddiamonds9"
  include "carddiamondsa_l"
  include "carddiamondsa"
  include "carddiamondsj_l"
  include "carddiamondsj"
  include "carddiamondsk_l"
  include "carddiamondsk"
  include "carddiamondsq_l"
  include "carddiamondsq"
  include "cardhearts10_l"
  include "cardhearts10"
  include "cardhearts2_l"
  include "cardhearts2"
  include "cardhearts3_l"
  include "cardhearts3"
  include "cardhearts4_l"
  include "cardhearts4"
  include "cardhearts5_l"
  include "cardhearts5"
  include "cardhearts6_l"
  include "cardhearts6"
  include "cardhearts7_l"
  include "cardhearts7"
  include "cardhearts8_l"
  include "cardhearts8"
  include "cardhearts9_l"
  include "cardhearts9"
  include "cardheartsa_l"
  include "cardheartsa"
  include "cardheartsj_l"
  include "cardheartsj"
  include "cardheartsk_l"
  include "cardheartsk"
  include "cardheartsq_l"
  include "cardheartsq"
  include "cardjoker_l"
  include "cardjoker"
  include "cardspades10_l"
  include "cardspades10"
  include "cardspades2_l"
  include "cardspades2"
  include "cardspades3_l"
  include "cardspades3"
  include "cardspades4_l"
  include "cardspades4"
  include "cardspades5_l"
  include "cardspades5"
  include "cardspades6_l"
  include "cardspades6"
  include "cardspades7_l"
  include "cardspades7"
  include "cardspades8_l"
  include "cardspades8"
  include "cardspades9_l"
  include "cardspades9"
  include "cardspadesa_l"
  include "cardspadesa"
  include "cardspadesj_l"
  include "cardspadesj"
  include "cardspadesk_l"
  include "cardspadesk"
  include "cardspadesq_l"
  include "cardspadesq"
  include "cdown"
  include "cleft"
  include "cright"
  include "cup"
  include "test_joker"
  include "enterdonsol"
  include "eye0"
  include "eye1"
  include "eye2"

  include "donsolptr"
  include "donsolwbank"
  include "donsolbin"
  include "donsolbfx"
  include "countptr"
  include "countwbank"
  include "countbin"
endwave
