#include <stdio.h>
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

int compare_state( const struct State * a, const struct State * b )
{
    if( a->player != b->player )
        return 0;

    for( int i = 0; i < SIZE; i++ )
        for( int j = 0; j < SIZE; j++ )
            if( a->board[i][j] != b->board[i][j] )
                return 0;

    return 1;
}

void print_state( const struct State * state )
{
    printf( "Current Player: %c\n", state->player );
    
    /* print board */
    printf( "  " );
    for( int i = 0; i < SIZE; i++ )
        printf( "%d ", i );
    printf( "\n" );

    for( int i = 0; i < SIZE; i++ )
    {
        printf( "%d ", i );
        for( int j = 0; j < SIZE; j++ )
            printf( "%c ", state->board[i][j] );
        printf( "\n" );
    }
    printf( "\n" );
}
