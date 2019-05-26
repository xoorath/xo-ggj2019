include $(ROOT)/usr/include/make/PRdefs

N64KITDIR    = c:\nintendo\n64kit
NUSYSINCDIR  = $(N64KITDIR)/nusys/include
NUSYSLIBDIR  = $(N64KITDIR)/nusys/lib
NSTDINCDIR = $(N64KITDIR)/nustd/include
NSTDLIBDIR = $(N64KITDIR)/nustd/lib

LIB = $(ROOT)/usr/lib
LPR = $(LIB)/PR
INC = $(ROOT)/usr/include
CC  = @gcc
LD  = @ld
MAKEROM = @mild

NUAUDIOLIB = -lnualstl_n_d -ln_gmus_d -ln_gaudio_sc

LCDEFS =	-DNU_DEBUG -DF3DEX_GBI_2
LCINCS =	-I. -I$(NUSYSINCDIR) -I$(NSTDINCDIR) -I$(ROOT)/usr/include/PR -Isource -Isprites -Isource/xo-64
LCOPTS =	-G 0
LDFLAGS =	$(MKDEPOPT) -L$(LIB) -L$(NUSYSLIBDIR) -L$(NSTDLIBDIR) $(NUAUDIOLIB) -lnustd_d -lnusys_d -lgultra_d -L$(GCCDIR)/mipse/lib -lkmc

OPTIMIZER =	-g

APP =		build/project.out

TARGETS =	build/project.n64

HFILES = $(wildcard source/*.h) $(wildcard source/xo-64/*.h)

CODEFILES = $(wildcard source/*.c) $(wildcard source/xo-64/*.c)
CODEOBJECTS =	$(CODEFILES:.c=.o)  $(NUSYSLIBDIR)/nusys.o

DATAFILES   = $(wildcard sprites/*.c)
DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

default: clean $(TARGETS)

code: $(TARGETS)

clean:
		rm -f **/*.o
		rm -f build/*.*
		touch **/*.c
		touch **/*.h


$(CODESEGMENT):	$(CODEOBJECTS) Makefile
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

$(TARGETS):	$(OBJECTS)
		$(MAKEROM) spec -I$(NUSYSINCDIR) -r $(TARGETS) -e $(APP)
		@makemask $(TARGETS)
