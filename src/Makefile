BIN=bt
SRC=bt.m error.m event.m map.m textshow.m bmpl.m colors.m input.m joystick.m alloc.m sdl_events.m filter.m game.m audio.m player.m console.m console/DT_drawtext.m console/SDL_console.m console/internal.m python.m
OBJ=bt.o error.o event.o map.o textshow.o bmpl.o colors.o input.o joystick.o alloc.o sdl_events.o filter.o game.o audio.o player.o console.o console/DT_drawtext.o console/SDL_console.o console/internal.o python.o
HDR=error.h event.h bt.h map.h textshow.h bmpl.h bitmaps.h colors.h input.h joystick.h alloc.h sdl_events.h filter.h game.h eventhandler.h audio.h player.h console.h console/DT_drawtext.h console/SDL_console.h console/internal.h python.h
CFLAGS=-g `sdl-config --cflags` -I/usr/include/python2.3
LIBS=`sdl-config --libs` -lm -lSDL_ttf -lSDL_image -lSDL_mixer -lobjc -lpython2.3
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
