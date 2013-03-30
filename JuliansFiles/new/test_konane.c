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
    printf( "Result of move: \n" );
    struct State * new_state1;
    current = moves->head;
    while( current != NULL )
    {
        print_move( current->data );

        new_state1 = result( state, current->data );
        print_state( new_state1 );
        free( new_state1 );

        current = current->next;
    }

    board[ 2 ][ 1 ] = 'O';
    board[ 3 ][ 4 ] = 'O';

    struct State * state4;
    current = moves->head;
    while( current != NULL )
    {
        print_move( current->data );

        state4 = new_state( board, player2 );
        print_state( state4 );

        /* list moves */
        struct List * moves2 = actions( state4 );
        struct ListNode * current2 = moves2->head;

        printf( "List of valid moves:\n" );
        while( current2 != NULL )
        {
            print_move( current2->data );

            human_move = translate_move( current2->data );
            printf( "%s\n", human_move );
            free( human_move );

            current2 = current2->next;
        }

        free( moves2 );

        free( state4 );

        current = current->next;
    }

    return EXIT_SUCCESS;
}
