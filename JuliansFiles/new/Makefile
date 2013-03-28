CC= gcc
CFLAGS= -Wall -g -pedantic -std=c99
LDFLAGS=

all: test_move test_list test_game_node test_state test_konane 

konane.o: konane.h state.h move.h
list.o: list.h
move.o: move.h
state.o: state.h
game_node.o: game_node.h list.h state.h

test_state.o: test_state.c state.h
test_state: test_state.o state.o

test_move.o: test_move.c move.h
test_move: test_move.o move.o

test_list.o: test_list.c list.h
test_list: test_list.o list.o

test_game_node.o: test_game_node.c game_node.h state.h list.h
test_game_node: test_game_node.o game_node.o state.o list.o

test_konane.o: test_konane.c konane.h state.h game_node.h move.h
test_konane: test_konane.o konane.o state.o game_node.o move.o
