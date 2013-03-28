#include <stdlib.h>
#include <assert.h>
#include "state.h"

struct State * new_state( char ** board, char player )
{
    struct State * state = calloc( 1, sizeof( struct State ) );
    assert( state );

    state->board = board;
    state->player = player;

    return state;
}
