#ifndef _STATE_H_
#define _STATE_H_

#include "move.h"

struct State {
    char ** board;
    char player;
};

struct State * new_state( char ** board, char player );

#endif /* _STATE_H_ */
