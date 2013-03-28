#ifndef _STATE_H_
#define _STATE_H_

#include "konane.h"
#include "move.h"

struct State {
    char player;
    char board[SIZE][SIZE];
};

struct State * new_state( char board[][SIZE], char player );

#endif /* _STATE_H_ */
