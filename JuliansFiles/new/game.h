#ifndef _GAME_H_
#define _GAME_H_

#include "game_node.h"
#include "move.h"
#include "state.h"

int game( void );

int human_vs_computer( void );
int computer_vs_computer( void );

struct GameNode * human_player_first( struct GameNode * game_state );
struct GameNode * computer_player_first( struct GameNode * game_state );
struct GameNode * human_player_second( struct GameNode * game_state );
struct GameNode * computer_player_second( struct GameNode * game_state );

struct GameNode * human_player( struct GameNode * game_state );
struct GameNode * computer_player( struct GameNode * game_state );


#endif /* _GAME_H_ */
