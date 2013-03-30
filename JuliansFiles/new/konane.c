#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "konane.h"
#include "state.h"
#include "move.h"
#include "list.h"

static struct List * actions_right( const struct State * state, int row )
{
    int idx = 0;
    struct List * actions = new_list();

    for( idx = 0; idx < SIZE; idx++ )
    {
        /* find next piece on board */
        for( ; state->board[ row ][ idx ] != state->player && 
             idx < SIZE - 1; ++idx );

        /* check for moves */
        for( int i = 1; i + idx < SIZE; i++ )
        {
            if( state->board[ row ][ idx + i ] != state->player &&
                state->board[ row ][ idx + i ] != 'O' )
            {
                if( state->board[ row ][ idx + i + 1 ] == 'O' )
                {
                    /* has move */
                    //printf( "(%d,%d), (%d, %d)\n", row, idx, row, idx + i + 1 );
                    add_front( &actions, new_move( row, idx, row, idx + i + 1 ) );

                    /* check for more moves */
                    continue;
                }
                break;
            }
        }
    }

    return actions;
}

static struct List * actions_left( const struct State * state, int row )
{
    int idx = SIZE-1;
    struct List * actions = new_list();

    for( idx = SIZE - 1; idx >= 0; idx-- )
    {
        /* find next piece on board */
        for( ; state->board[ row ][ idx ] != state->player && idx > 0; idx-- );
        
        /* check for moves */
        for( int i = idx - 1; i >= 0; i-- )
        {
            if( state->board[ row ][ i ] != state->player &&
                state->board[ row ][ i ] != 'O' )
            {
                if( state->board[ row ][ i - 1 ] == 'O' )
                {
                    /* has move */
                    //printf( "(%d,%d), (%d, %d)\n", row, idx, row, i - 1 );
                    add_front( &actions, new_move( row, idx, row, i - 1 ) );

                    /* check for more moves */
                    continue;
                }
                break;
            }
        }
    }

    return actions;
}

static struct List * actions_down( const struct State * state, int col )
{
    int idx = 0;
    struct List * actions = new_list();

    for( idx = 0; idx < SIZE; idx++ )
    {
        /* find next piece on board */
        for( ; state->board[ idx ][ col ] != state->player && 
             idx < SIZE - 1; ++idx );

        /* check for moves */
        for( int i = 1; i + idx < SIZE; i++ )
        {
            if( state->board[ idx + i ][ col ] != state->player &&
                state->board[ idx + i ][ col ] != 'O' )
            {
                if( state->board[ idx + i + 1 ][ col ] == 'O' )
                {
                    /* has move */
                    //printf( "(%d,%d), (%d, %d)\n", row, idx, row, idx + i + 1 );
                    add_front( &actions, new_move( idx, col, idx + i + 1, col  ));

                    /* check for more moves */
                    continue;
                }
                break;
            }
        }
    }

    return actions;
}

static struct List * actions_up( const struct State * state, int col )
{
    int idx = SIZE;
    struct List * actions = new_list();

    for( idx = SIZE; idx >= 0; idx-- )
    {
        /* find next piece on board */
        for( ; state->board[ idx ][ col ] != state->player && 
             idx > 0; --idx );

        /* check for moves */
        for( int i = 1; idx - i >= 0; i++ )
        {
            if( state->board[ idx - i ][ col ] != state->player &&
                state->board[ idx - i ][ col ] != 'O' )
            {
                if( state->board[ idx - (i+1) ][ col ] == 'O' )
                {
                    /* has move */
                    add_front( &actions, new_move( idx, col, idx - (i+1), col ) );

                    /* check for more moves */
                    continue;
                }
                break;
            }
        }
    }

    return actions;
}

struct List * actions( const struct State * state )
{

    struct List * moves = new_list();
    struct List * temp_moves;
    struct ListNode * current;

    /* combine all actions */
    for( int i = 0; i < SIZE; i++ )
    {
        /* actions right */
        temp_moves = actions_right( state, i );

        current = temp_moves->head; 
        while( current != NULL )
        {
            add_front( &moves, current->data );
            current = current->next;
        }

        delete_list( &temp_moves );

        /* actions left */
        temp_moves = actions_left( state, i );

        current = temp_moves->head; 
        while( current != NULL )
        {
            add_front( &moves, current->data );
            current = current->next;
        }

        delete_list( &temp_moves );

        /* actions up */
        temp_moves = actions_up( state, i );

        current = temp_moves->head; 
        while( current != NULL )
        {
            add_front( &moves, current->data );
            current = current->next;
        }

        delete_list( &temp_moves );

        /* actions down */
        temp_moves = actions_down( state, i );

        current = temp_moves->head; 
        while( current != NULL )
        {
            add_front( &moves, current->data );
            current = current->next;
        }

        delete_list( &temp_moves );
    }

    return moves;
}

struct State * result( const struct State * state, const struct Move * action )
{
    char newBoard[SIZE][SIZE];
    
    /* copy old board */
    for( int i = 0; i < SIZE; i++ )
        for( int j = 0; j < SIZE; j++ )
            newBoard[ i ][ j ] = state->board[ i ][ j ];

    /* validate move */ 
    if( validate_action( state, action ) )
    {
        /* get resulting board state 
         * by removing all pieces between start and end action 
         */
        if( action->start_row == action->end_row )
        {
            /* blank column */
            if( action->start_col < action->end_col )
                for( int i = action->start_col; i < action->end_col; i++ )
                    newBoard[ action->start_row ][ i ] = 'O';
            else
                for( int i = action->end_col; i < action->start_col; i++ )
                    newBoard[ action->start_row ][ i ] = '0';
        }
        else
        {
            /* blank row */
            if( action->start_row < action->end_row )
                for( int i = action->start_row; i < action->end_row; i++ )
                    newBoard[ action->start_row + i ][ action->start_col ] = 'O';
            else
                for( int i = action->end_row; i < action->start_row; i++ )
                    newBoard[ action->end_row + i ][ action->start_col ] = '0';
        }

        /* return changed board */
        return new_state( newBoard, opposite_player( state->player ) );
    }

    return NULL;
}

int validate_action( const struct State * state, const struct Move * action )
{
    struct List * moves;

    /* screen move */
    if( action->start_row == action->end_row && action->start_col != action->end_col )
    {
        /* potentially valid move */
        /* check if there is a move in the row */
        if( action->start_col < action->end_col )
            moves = actions_left( state, action->start_row );
        else
            moves = actions_right( state, action->start_row );

        struct ListNode * current = moves->head;
        while( current != NULL )
        {
            if( compare_move( current->data, action ) == 1 )
            {
                delete_list( &moves );
                return 1;
            }
            current = current->next;
        }
    
    }
    else if( action->start_col == action->end_col && action->start_row != action->end_row )
    {
        /* potentially valid move */
        /* check if there is move in the column */
        if( action->start_row < action->end_row )
            moves = actions_down( state, action->start_col );
        else
            moves = actions_up( state, action->start_col );

        struct ListNode * current = moves->head;
        while( current != NULL )
        {
            if( compare_move( current->data, action ) )
            {
                delete_list( &moves );
                return 1;
            }
            current = current->next;
        }
    }

    return 0;
}

int terminal_test( const struct State * state )
{
    /* if there are no more moves for other player, game is done */
    struct List * moves = new_list();

    moves = actions( state );

    /* check if state is terminal */
    int has_move = ( moves->count != 0 );
    delete_list( &moves );

    return has_move;
}

int utility( const struct State * state )
{
}

char opposite_player( char player )
{
    if( player == 'B' )
        return 'W';
    else
        return 'B';
}
