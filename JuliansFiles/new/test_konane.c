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
    struct State * state = new_state( board, player1 );
    
    print_state( state );

    /* list moves */
    struct List * moves = actions( state );
    struct ListNode * current = moves->head;
    char * human_move;

    printf( "List of valid moves:\n" );
    while( current != NULL )
    {
        print_move( current->data );

        human_move = translate_move( current->data );
        printf( "%s\n", human_move );
        free( human_move );

        current = current->next;
    }

    /* get the result of a move */


    return EXIT_SUCCESS;
}
