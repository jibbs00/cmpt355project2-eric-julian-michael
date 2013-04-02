# *** MACRO VARIABLES ***
SHELL=/bin/bash
CC=gcc
CFLAGS=-std=c99 -Wall -g

konane: main.c tree.o move.o utility.o
	$(CC) $(CFLAGS) -o $@ $^

test: testmain.c tree.o move.o utility.o timer.o
	$(CC) -pthread $(CFLAGS) -o $@ $^

# use of wildcards to compile all object files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

# command to remove all unwanted files, object, and executables as well
clean:
	$(RM) -f *~ *# *.o konane test

