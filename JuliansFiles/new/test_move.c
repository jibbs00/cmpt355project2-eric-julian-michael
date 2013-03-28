#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "move.h"

int main( void )
{
    /* new move */
    struct Move * move = new_move( 1, 1, 1, 3 );

    /* print move */
    printf( "(%d,%d),(%d,%d)\n", 
                move->start_row,
                move->start_col,
                move->end_row,
                move->end_col );

    /* translate move */
    char * human_readable = translate_move( move );
    printf( "Move: %s\n", human_readable );

    /* translate input move */
    char * human_input = "H2 - A2";

    struct Move * human_move = translate_in_move( human_input );
    /* print move */
    printf( "Input move: %s\n", human_input );
    printf( "(%d,%d),(%d,%d)\n", 
                human_move->start_row,
                human_move->start_col,
                human_move->end_row,
                human_move->end_col );

    free( human_readable );
    free( move );

    return EXIT_SUCCESS;
}
