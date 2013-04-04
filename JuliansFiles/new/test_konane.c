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

    char board2[8][8] = { { 'B', 'O', 'O', 'W', '0', '0', 'B', 'W' },
                          { '0', '0', '0', 'B', '0', '0', 'W', 'B' },
                          { '0', 'O', '0', '0', '0', '0', '0', 'W' },
                          { '0', 'O', '0', '0', '0', '0', '0', 'B' },
                          { '0', '0', 'B', 'W', '0', '0', 'B', 'W' },
                          { 'W', '0', 'W', 'B', 'W', 'B', 'W', 'B' },
                          { 'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W' },
                          { 'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B' } };

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
            printf( "\n" );
            current2 = current2->next;
        }

        free( moves2 );

        free( state4 );

        current = current->next;
    }

    /* list moves on board 2 */
    printf( "\n\nBoard 2: %c\n", player1 );
    struct State * test_state = new_state( board2, player1 );
    moves = actions( test_state );

    print_state( test_state );

    printf( "List of valid moves:\n" );
    current = moves->head;
    while( current != NULL )
    {
        print_move( current->data );
        printf( "\n" );
        current = current->next;
    }

    free( test_state );

    printf( "Board 2: %c\n", player2 );
    test_state = new_state( board2, player2 );
    print_state( test_state );
    moves = actions( test_state );
    printf( "List of valid moves:\n" );
    current = moves->head;
    while( current != NULL )
    {
        print_move( current->data );
        printf( "\n" );
        current = current->next;
    }

    free( test_state );

    return EXIT_SUCCESS;
}
