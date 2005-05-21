BIN=bt
SRC=main.cc error.cc map.cc bmpl.cc alloc.cc sdl_events.cc game.cc audio.cc player.cc console.cc console/DT_drawtext.cc console/SDL_console.cc console/internal.cc editor.cc sprite.cc character.cc
OBJ=main.o error.o map.o bmpl.o alloc.o sdl_events.o game.o audio.o player.o console.o console/DT_drawtext.o console/SDL_console.o console/internal.o editor.o sprite.o character.o 
HDR=error.h map.h bmpl.h bitmaps.h alloc.h sdl_events.h game.h audio.h player.h console.h console/DT_drawtext.h console/SDL_console.h console/internal.h editor.h sprite.h character.h
CFLAGS=-g `sdl-config --cflags`
LIBS=`sdl-config --libs` -lm -lSDL_ttf -lSDL_image -lSDL_mixer
CC=g++
EOBJ=.o
ESRC=.cc

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $(BIN) $(LIBS) $(OBJ)

%.o: %.cc $(HDR) 
	$(CC) $(CFLAGS) -c $(subst $(EOBJ),$(ESRC),$@) -o $@

clean:
	rm -rf $(BIN) $(OBJ) 2> /dev/null

.PHONY: all clean


# vim: sw=4 noet ts=4:
