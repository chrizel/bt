SOURCES = main.cc error.cc map.cc bmpl.cc alloc.cc sdl_events.cc game.cc audio.cc player.cc editor.cc sprite.cc character.cc
HEADERS = error.h map.h bmpl.h bitmaps.h alloc.h sdl_events.h game.h audio.h player.h editor.h sprite.h character.h
OBJECTS = $(SOURCES:.cc=.o)

BINARY=bt
CC=g++
CFLAGS=-g `sdl-config --cflags`
LDFLAGS = `sdl-config --libs` -lm -lSDL_ttf -lSDL_image -lSDL_mixer
MKDEP = g++ -MM ${CFLAGS}

all: $(BINARY)

${BINARY}: ${OBJECTS}
	${CC} ${LDFLAGS} -o $@ ${OBJECTS}

.cc.o:
	${CC} -c ${CFLAGS} $<

.PHONY: clean dep all

clean:
	rm -rf ${OBJECTS} ${BINARY}

dep:
	${MKDEP} ${SOURCES} > make.dep

include make.dep

# vim: sw=4 noet ts=4:
