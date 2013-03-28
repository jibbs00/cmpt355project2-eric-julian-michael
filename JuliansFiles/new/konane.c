#include <stdlib.h>

#include "konane.h"
#include "state.h"
#include "move.h"
#include "list.h"
#include "game_node.h"

#define SIZE 8

/**
 * Get a set of actions at a state
 * 
 * @param state
 * @return the set of actions in a state
 */
static void * actions( const struct State * state )
{
    
    char ** board = state->board;
    struct List * acts = new_list();
    struct List * movesRight, * movesLeft, * movesDown, * movesUp;
    char player = state->player ;

    for( int i = 0; i < SIZE; ++i )
    {
        movesRight = actionsRight( board, i, player );
        movesLeft = actionsLeft( board, i, player );
        movesDown = actionsDown( board, i, player );
        movesUp = actionsUp( board, i, player );
    }

    /* combine sets */

    struct ListNode * current;

    /* moves right */
    for( current = movesRight->head;
         current != NULL;
         current = current->next )
        add_front( &acts, current->data );

    /* moves left */
    for( current = movesLeft->head;
         current != NULL;
         current = current->next )
        add_front( &acts, current->data );

    /* moves up */
    for( current = movesUp->head;
         current != NULL;
         current = current->next )
        add_front( &acts, current->data );

    /* moves down */
    for( current = movesDown->head;
         current != NULL;
         current = current->next )
        add_front( &acts, current->data );

    /* clean up */
    delete_list( &movesRight );
    delete_list( &movesLeft );
    delete_list( &movesUp );
    delete_list( &movesDown );


    return acts;
}

/**
 * Get the result of a current state and an action
 *
 * @param _self
 * @param state
 * @param action
 * @return the resulting state of performing action on the state, return 0 if
 *  action is invalid
 */
static struct State * result( const struct State * state, const void * action )
{
    const char * oldBoard = state->board ;

    char * newBoard  = calloc( SIZE * SIZE, sizeof( char ) );
    assert( newBoard != 0 );
    
    /* copy old board */
    for( int i = 0; i < SIZE * SIZE ; i++ )
        newBoard[ i ] = oldBoard[ i ];

    /* validate move */ 
    if( validateAction( currentBoard( state ), *(char *)currentPlayer( state ), action ) )
    {
        /* get resulting board state 
         * by removing all pieces between start and end action 
         */
        if( startRow( state ) == endRow( state ) )
        {
            /* blank column */
            if( startCol( state ) < endCol( state ) )
                for( int i = startCol( state ); i < endCol( state ); i++ )
                    newBoard[ startRow( state ) * SIZE + i ] = 'O';
            else
                for( int i = endCol( state ); i < startCol( state ); i++ )
                    newBoard[ startRow( state ) * SIZE + i ] = '0';
        }
        else
        {
            /* blank row */
            if( startRow( state ) < endRow( state ) )
                for( int i = startRow( state ); i < endRow( state ); i++ )
                    newBoard[ ( startRow( state ) + i ) * SIZE + startCol( state ) ] = 'O';
            else
                for( int i = endRow( state ); i < startRow( state ); i++ )
                    newBoard[ ( endRow( state ) + i ) * SIZE + startCol( state ) ] = '0';
        }

        /* return changed board */
        return newBoard;
    }

    return 0;
}

/**
 * Validate a move
 *
 * @param board a board state
 * @param move the move to make
 * @return 1 if move is valid, else return 0
 */
static int validateAction( const char ** board, char player, const struct Move * move )
{
    void * moves;

    /* screen move */
    if( move->start_row == move->end_row && move->start_col != move->end_col )
    {
        /* potentially valid move */
        /* check if there is a move in the row */
        if( move->start_col < move->end_col )
            moves = actionsLeft( board, move->start_row, player );
        else
            moves = actionsRight( board, move->start_row, player );

        if( contains( moves, self ) )
        {
            delete( moves );
            return 1;
        }
    
    }
    else if( move->start_col == move->end_col && move->start_row != move->end_row )
    {
        /* potentially valid move */
        /* check if there is move in the column */
        if( move->start_row < move->end_row )
            moves = actionsDown( board, move->start_col, player );
        else
            moves = actionsUp( board, move->start_col, player );

        if( contains( moves, self ) )
        {
            delete( moves );
            return 1;
        }
    }

    return 0;
}

/**
 * Check if the game is won
 *
 * @param state the current game state
 * @return 1 if the game is in a terminal state, i.e. a player is
 *  unable to capture an enemy piece, else return 0
 */
static int terminalTest( const struct State * state )
{
    /* if there are no more moves for other player, game is done */
    char ** board = state->board;
    struct List * acts = new_list();
    struct List * movesRight, * movesLeft, * movesDown, * movesUp;
    char player = opposingPlayer( state );

    for( int i = 0; i < SIZE; ++i )
    {
        movesRight = actionsRight( board, i, player );
        movesLeft = actionsLeft( board, i, player );
        movesDown = actionsDown( board, i, player );
        movesUp = actionsUp( board, i, player );
    }

    /* combine sets */
    struct ListNode * current;

    /* moves right */
    for( current = movesRight->head;
         current != NULL;
         current = current->next )
        add_front( &acts, current->data );

    /* moves left */
    for( current = movesLeft->head;
         current != NULL;
         current = current->next )
        add_front( &acts, current->data );

    /* moves up */
    for( current = movesUp->head;
         current != NULL;
         current = current->next )
        add_front( &acts, current->data );

    /* moves down */
    for( current = movesDown->head;
         current != NULL;
         current = current->next )
        add_front( &acts, current->data );

    /* clean up */
    delete_list( &movesRight );
    delete_list( &movesLeft );
    delete_list( &movesUp );
    delete_list( &movesDown );


    /* check if state is terminal */
    int noMoves = ( acts->count == 0 );
    delete_list( &acts );

    return noMoves;

}

/**
 * A utility function
 *
 * @param state
 * @param player
 */
static int utility( const void * state, const void * player )
{
}

/**
 * Get a set of possible actions across right
 *
 * @param board a konane board
 * @param row the row to check
 * @param player the current player
 * @return a set of actions
 */
static void * actionsRight( const char ** board, int row, char player )
{
    int col = 0;                        /* current pos */
    struct List * actions = new_list();

    /* find all possible actions across right in row */
    while( col < SIZE )
    {
        /* andvance to next piece in row */
        for( ; 
             ( board[ row ][ ( col ) ] != player ) && 
             ( col < SIZE - 1);             /* stop at end one before end of board */
             ++col );

        /* check for moves */
        for( int i = col + 1; i < SIZE; i++ )
        {
            if( board[ row ][ (col + i) ] != player &&
                board[ row ][ (col + i) ] != 'O' ) 
            {
                if( board[ row ][ ( col + i + 1 ) ]== 'O' )
                {
                    /* has move */
                    add_front( &actions, new_move( row, col, row, col + i + 1 ) );

                    /* check for more moves */
                    i += 1;
                    continue;    /* not really necessary */
                }
            }
        }
        col += 1;   /* advance piece */
    }

    return actions;
}

/**
 * Get a set of possible actions across left
 *
 * @param board a konane board
 * @param row the row to check
 * @param player the current player
 * @return a set of actions
 */
static void * actionsLeft( const char ** board, int row, char player )
{
    int col = SIZE;                     /* current pos */
    struct List * actions = new_list();

    /* find all possible actions across right in row */
    while( col >= 0 )
    {
        /* andvance to next piece in row */
        for( ; 
             ( board[ row ][ col ] != player ) && 
             ( col > 1);             /* stop at end one before end of board */
             col-- );

        /* check for moves */
        for( int i = col + 1; i < SIZE; i++ )
        {
            if( board[ row ][ ( col - i ) ] != player &&
                board[ row ][ ( col - i ) ] != 'O' )
            {
                if( board[ row ][ ( col - (i + 1 )) ]== 'O' )
                {
                    /* has move */
                    add_front( &actions, new_move( row, col, row, col - (i + 1) ) );

                    /* check for more moves */
                    i += 1;
                    continue;    /* not really necessary */
                }
            }
        }
        col -= 1;   /* advance piece */
    }

    return actions;
}

/**
 * Get a set of possible actions down from the top
 *
 * @param board a konane board
 * @param col the column to check
 * @param player the current player
 * @return a set of actions
 */
static void * actionsDown( const char ** board, int col, char player )
{
    int row = 0;                        /* current pos */
    struct List * actions = new_list();

    /* find all possible actions across right in row */
    while( row < SIZE )
    {
        /* andvance to next piece in row */
        for( ; 
             ( board[ row ][ col ] != player ) && 
             ( row < SIZE - 1);             /* stop at end one before end of board */
             ++row );

        /* check for moves */
        for( int i = row + 1; i < SIZE; i++ )
        {
            if( board[ (row + i) ][ col ] != player &&
                board[ (row + i) ][ col ] != 'O' )
            {
                if( board[ (row + i + 1) ][ col ]== 'O' )
                {
                    /* has move */
                    add_front( &actions, new_move( row, col, row + i + 1, col ) );

                    /* check for more moves */
                    i += 1;
                    continue;    /* not really necessary */
                }
            }
        }
        row += 1;   /* advance piece */
    }

    return actions;
}

/**
 * Get a set of possible actions down from the bottom up
 *
 * @param board a konane board
 * @param col the column to check
 * @param player the current player
 * @return a set of actions
 */
static void * actionsUp( const char ** board, int col, char player )
{
    int row = SIZE;                        /* current pos */
    struct List * actions = new_list();

    /* find all possible actions across right in row */
    while( row >= 0 )
    {
        /* andvance to next piece in row */
        for( ; 
             ( board[ row ][ col ] != player ) && 
             ( row < SIZE - 1);             /* stop at end one before end of board */
             ++row );

        /* check for moves */
        for( int i = row + 1; i < SIZE; i++ )
        {
            if( board[ ( row - i ) ][ col ] != player &&
                board[ ( row - i ) ][ col ] != 'O' )
            {
                if( board[ (row - (i + 1)) ][ col ]== 'O' )
                {
                    /* has move */
                    add_front( &actions, new_move( row, col, row + (i-1), col ) );

                    /* check for more moves */
                    i += 1;
                    continue;    /* not really necessary */
                }
            }
        }
        row -= 1;   /* advance piece */
    }

    return actions;
}
