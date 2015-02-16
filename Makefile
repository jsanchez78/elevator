#
# Makefile for compiling and executing code
#
CFLAGS=-DUNIX -lreadline -lcurses 
DEBUG=-lrt
DEBUG1=-g
#DEBUG=

all: shell


shell: main.c 
	gcc $(CFLAGS) linkedList.c findT.c elevator_t.c init_global.c person_t.c main.c -o elevator $(DEBUG) $(DEBUG1) 

clean:
	rm -f shell *~
