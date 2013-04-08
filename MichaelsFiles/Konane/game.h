#ifndef _GAME_H_
#define _GAME_H_

#include "game_node.h"
#include "move.h"
#include "state.h"

int game( void );

int human_vs_computer( void );
int computer_vs_computer( void );

struct State * human_player_first( struct State * game_state );
struct State * computer_player_first( struct State * game_state );
struct State * human_player_second( struct State * game_state );
struct State * computer_player_second( struct State * game_state );

struct State * human_player( struct State * game_state );
struct State * computer_player( struct State * game_state );

#endif /* _GAME_H_ */
