#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "konane.h"
#include "state.h"
#include "utility.h"

int main( void )
{
    char board[SIZE][SIZE];
    char player1 = 'B';
    char player2 = 'W';
    
    int player = 0;
    /* populate board */
    for( int i = 0; i < SIZE ; i++ )
    {
        for( int j = 0; j < SIZE; j++ )
        {
            if( player == 0 )
            {
                board[i][j] = player1;
                player = 1;
            }
            else
            {
                board[i][j] = player2;
                player = 0;
            }
        }
        if( player == 0 )
            player = 1;
        else
            player = 0;
    }

    /* create a new state */
    struct State * state = new_state( board, player1 );

    printf( "Player : %c\n", state->player );
    
    /* print board */
    for( int i = 0; i < SIZE ; i++ )
    {
        for( int j = 0; j < SIZE; j++ )
        {
            printf( "%c", state->board[i][j] );
        }
        printf( "\n" );
    }

    printf( "\n" );

    struct State * state2 = new_state( board, player2 );
    printf( "Player : %c\n", state2->player );
    
    /* print board */
    for( int i = 0; i < SIZE ; i++ )
    {
        for( int j = 0; j < SIZE; j++ )
        {
            printf( "%c", state2->board[i][j] );
        }
        printf( "\n" );
    }


    /* compare states */
    printf( "same = %d\n", compare_state( state, state ) );
    printf( "different = %d\n", compare_state( state, state2 ) );


    /* remove piece from board */
    board[ 3 ][ 3 ] = 'O';

    struct State * state3 = new_state( board, player2 );
    printf( "Player : %c\n", state3->player );
    
    /* print board */
    for( int i = 0; i < SIZE ; i++ )
    {
        for( int j = 0; j < SIZE; j++ )
        {
            printf( "%c", state3->board[i][j] );
        }
        printf( "\n" );
    }

    /* print state */
    print_state( state );
    print_state( state2 );
    print_state( state3 );

    Free( state, sizeof( struct State ) );
    Free( state2, sizeof( struct State ) );
    Free( state3, sizeof( struct State ) );

    return EXIT_SUCCESS;
}
