BIN=bt
SRC=bt.m error.m event.m map.m textshow.m bmpl.m colors.m input.m joystick.m alloc.m sdl_events.m filter.m game.m audio.m 
OBJ=bt.o error.o event.o map.o textshow.o bmpl.o colors.o input.o joystick.o alloc.o sdl_events.o filter.o game.o audio.o
HDR=error.h event.h bt.h map.h textshow.h bmpl.h bitmaps.h colors.h input.h joystick.h alloc.h sdl_events.h filter.h game.h eventhandler.h audio.h
CFLAGS=-g `sdl-config --cflags` -D DO_FRAMETEST
LIBS=`sdl-config --libs` -lm -lSDL_ttf -lSDL_image -lSDL_mixer -lobjc
CC=gcc
EOBJ=.o
ESRC=.m

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $(BIN) $(LIBS) $(OBJ)

%.o: %.m $(HDR) 
	$(CC) $(CFLAGS) -c $(subst $(EOBJ),$(ESRC),$@) -o $@

clean:
	@rm $(BIN) $(OBJ)

# vim: sw=4 noet ts=4:
