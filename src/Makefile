BIN=bt
SRC=bt.cpp error.cpp event.cpp map.cpp textshow.cpp bmpl.cpp colors.cpp input.cpp joystick.cpp alloc.cpp sdl_events.cpp filter.cpp game.cpp audio.cpp 
OBJ=bt.o error.o event.o map.o textshow.o bmpl.o colors.o input.o joystick.o alloc.o sdl_events.o filter.o game.o audio.o
HDR=error.h event.h bt.h map.h textshow.h bmpl.h bitmaps.h colors.h input.h joystick.h alloc.h sdl_events.h filter.h game.h eventhandler.h audio.h
CFLAGS=-g `sdl-config --cflags` -D DO_FRAMETEST -lobjc -x objective-c
LIBS=`sdl-config --libs` -lm -lSDL_ttf -lSDL_image -lSDL_mixer
CC=gcc

all: $(BIN)

$(BIN): $(OBJ)
	g++ -o $(BIN) $(LIBS) $(OBJ)

$(OBJ): $(HDR)


clean:
	@rm $(BIN) $(OBJ)

# vim: sw=4 noet ts=4:
