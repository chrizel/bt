events: events.c event
	gcc -g -o events events.c event.o alloc.o error.o

event: ../src/event.c ../src/event.h ../src/alloc.c ../src/alloc.h ../src/error.h ../src/error.h
	gcc -g -c ../src/event.c
	gcc -g -c ../src/alloc.c
	gcc -g -c ../src/error.c
