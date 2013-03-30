/**
 * @file state.c
 * @author Julian Martinez del Campo
 *
 * This file provides an implementation of state.h
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "konane.h"
#include "state.h"

/**
 * Create a new state
 *
 * @param board a board copy into state
 * @param player the current player
 * @return a new state with board and player
 */
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

/**
 * Compare state
 * 
 * @param a a state
 * @param b a state
 * @return 1 if states are the same, else return 0
 */
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

/**
 * Print a state
 *
 * @param state the state to print
 */
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
