#include <stdlib.h>
#include <assert.h>

#include "konane.h"
#include "state.h"

struct State * new_state( char board[][SIZE], char player )
{
    struct State * state = calloc( 1, sizeof( struct State ) );
    assert( state );

    for( int i = 0 ; i < SIZE; i++ )
        for( int j = 0; j < SIZE; j++ )
            state->board[i][j] = board[i][j];

    state->player = player;

    return state;
}
