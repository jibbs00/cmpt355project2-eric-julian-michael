CC= gcc
CFLAGS= -Wall -g -pedantic -std=c99
LDFLAGS=

all: test_move test_list test_game_node test_state test_konane 

konane.o: konane.h state.h move.h list.h
list.o: list.h utility.h
move.o: move.h utility.h
state.o: state.h konane.h utility.h move.h
game_node.o: game_node.h list.h state.h utility.h
utility.o: utility.h

test_state.o: test_state.c state.h utility.h move.h
test_state: test_state.o state.o utility.o move.o

test_move.o: test_move.c move.h utility.h
test_move: test_move.o move.o utility.o

test_list.o: test_list.c list.h utility.h
test_list: test_list.o list.o utility.o

test_game_node.o: test_game_node.c game_node.h state.h list.h utility.h
test_game_node: test_game_node.o game_node.o state.o list.o utility.o move.o

test_konane.o: test_konane.c konane.h state.h game_node.h move.h list.h utility.h
test_konane: test_konane.o konane.o state.o game_node.o move.o list.o utility.o

clean:
	$(RM) *.o
	$(RM) test_move test_list test_game_node test_state test_konane
