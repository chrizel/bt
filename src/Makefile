BIN=bt
SRC=bt.cpp error.cpp event.cpp map.cpp console/DT_drawtext.cpp console/SDL_console.c console/internal.cpp textshow.cpp console.cpp bmpl.cpp colors.cpp input.cpp joystick.cpp alloc.cpp sdl_events.cpp filter.cpp game.cpp
OBJ=bt.o error.o event.o map.o console/DT_drawtext.o console/SDL_console.o console/internal.o textshow.o console.o bmpl.o colors.o input.o joystick.o alloc.o sdl_events.o filter.o game.o
HDR=error.h event.h bt.h map.h testmap.h console/DT_drawtext.h console/SDL_console.h console/internal.h textshow.h console.h bmpl.h bitmaps.h colors.h input.h joystick.h alloc.h sdl_events.h filter.h game.h eventhandler.h
CPPFLAGS=-g `sdl-config --cflags` -D DO_FRAMETEST
LIBS=`sdl-config --libs` -lm -lSDL_ttf -lSDL_image 
CC=g++

all: $(BIN)

$(BIN): $(OBJ)
	g++ -o $(BIN) $(LIBS) $(OBJ)

$(OBJ): $(HDR)


clean:
	@rm $(BIN) $(OBJ)

# vim: sw=4 noet ts=4:
