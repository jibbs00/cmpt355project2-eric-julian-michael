#include <stdlib.h>
#include <assert.h>
#include "move.h"

struct Move * new_move( int start_row, int start_col, int end_row, int end_col )
{
    struct Move * move = calloc( 1, sizeof( struct Move ) );
    assert( move );

    move->start_row = start_row;
    move->start_col = start_col;
    move->end_row = end_row;
    move->end_col = end_col;

    return move;
}
