#ifndef _GAME_H_
#define _GAME_H_

#include "game_node.h"
#include "move.h"
#include "state.h"

int game( char *file );

int human_vs_computer( char *file );
int computer_vs_computer( char *file );

struct State * human_player_first( struct State * game_state );
struct State * computer_player_first( struct State * game_state );
struct State * human_player_second( struct State * game_state );
struct State * computer_player_second( struct State * game_state );

struct State * human_player( struct State * game_state );
struct State * computer_player( struct State * game_state );

#endif /* _GAME_H_ */
