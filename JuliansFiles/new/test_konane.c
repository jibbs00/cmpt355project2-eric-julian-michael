#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "konane.h"
#include "list.h"

int main( void )
{

    /* create board */
    char board[8][8];
    char player1 = 'B';
    char player2 = 'W';
    
    int player = 0;
    /* populate board */
    for( int i = 0; i < 8 ; i++ )
    {
        for( int j = 0; j < 8; j++ )
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

    /* remove piece from board */
    board[ 3 ][ 3 ] = 'O';

    /* create a new state */
    struct State * state = new_state( board, player2 );
    
    printf( "Current player: %c\n", state->player );
    for( int i = 0; i < SIZE; i++ )
    {
        for( int j = 0; j < SIZE; j++ )
        {
            printf( "%c", state->board[i][j] );
        }
        printf( "\n" );
    }

    /* list moves */
    struct List * moves = actions( state );
    struct ListNode * current = moves->head;

    while( current != NULL )
    {
        print_move( current->data );
        current = current->next;
    }

    return EXIT_SUCCESS;
}
