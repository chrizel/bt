BIN=bt
SRC=bt.c error.c event.c map.c console/DT_drawtext.c console/SDL_console.c console/internal.c textshow.c console.c bmpl.c colors.c input.c joystick.c alloc.c sdl_events.c filter.c
OBJ=bt.o error.o event.o map.o console/DT_drawtext.o console/SDL_console.o console/internal.o textshow.o console.o bmpl.o colors.o input.o joystick.o alloc.o sdl_events.o filter.o
HDR=error.h event.h bt.h map.h testmap.h console/DT_drawtext.h console/SDL_console.h console/internal.h textshow.h console.h bmpl.h bitmaps.h colors.h input.h joystick.h alloc.h sdl_events.h filter.h
CFLAGS=-g `sdl-config --cflags` 
LIBS=`sdl-config --libs` -lm -lSDL_ttf -lSDL_image 
CC=g++

all: $(BIN)

$(BIN): $(OBJ)
	g++ -o $(BIN) $(LIBS) $(OBJ)

$(OBJ): $(HDR)


clean:
	@rm $(BIN) $(OBJ)

# vim: sw=4 noet ts=4:
