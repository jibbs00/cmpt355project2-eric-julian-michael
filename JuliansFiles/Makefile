CC = gcc
CFLAGS = -Wall -g -pedantic -std=c99

# for gprof
#CFLAGS+=-pg

# for gcov
#CFLAGS+= -fprofile-arcs -ftest-coverage

all: 

linked_list.o: linked_list.c linked_list.h 
	$(CC) $(CFLAGS) -c $<

hash_table.o: hash_table.c hash_table.h
	$(CC) $(CFLAGS) -c $<

tree.o: tree.c tree.h linked_list.h
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o
