#ifndef _STATE_H_
#define _STATE_H_

#include "konane.h"

struct State {
    char player;
    char board[SIZE][SIZE];
};

struct State * new_state( char board[][SIZE], char player );
int compare_state( const struct State * a, const struct State * b );

#endif /* _STATE_H_ */
