CC = gcc
CFLAGS = -Wall -g -pedantic -std=c99

# for gprof
CFLAGS+=-pg

# for gcov
CFLAGS+= -fprofile-arcs -ftest-coverage

all: test_linked_list

linked_list.o: linked_list.c linked_list.h 
	$(CC) $(CFLAGS) -c $<

test_linked_list.o: test_linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c $<

test_linked_list: test_linked_list.o linked_list.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

hash_table.o: hash_table.c hash_table.h
	$(CC) $(CFLAGS) -c $<

HashTable.o: HashTable.cpp HashTable.hpp hash_table.h
	$(CC) $(CFLAGS) -c $<

test: test_linked_list
	valgrind -v --leak-check=full --track-origins=yes --show-reachable=yes ./test_linked_list

profile: test_linked_list
	./test_linked_list &> /dev/null
	gcov test_linked_list > coverage
	gprof test_linked_list > profile

clean:
	$(RM) *.o
	$(RM) ./test_linked_list
	$(RM) coverage profile
	$(RM) gmon.out *.gcda *.gcno *.gcov
