# *** MACRO VARIABLES ***
SHELL=/bin/bash
CC=gcc
CFLAGS=-std=c99 -Wall -g

sample: main.c func.o
	$(CC) $(CFLAGS) -o $@ $^

# use of wildcards to compile all object files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

# command to remove all unwanted files, object, and executables as well
clean:
	$(RM) -f *~ *# *.o sample

