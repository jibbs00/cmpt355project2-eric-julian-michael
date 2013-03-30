/**
 * @file move.c
 * @author Julian Martinez del Campo
 *
 * Provides an implementation of moves
 */
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "move.h"


/**
 * Create a new move
 *
 * @param start_row the starting row
 * @param start_col the starting column
 * @param end_row the ending row
 * @param end_col the ending column
 * @return a new move containing the start row, start col, end row, and end col
 */
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

/**
 * Convert a row number to a string
 *
 * @param i the row number
 * @return the row as a letter, if row is invalid return null
 */
static char * row2letter( int i )
{
    static char * letters[ 8 ] = { "A", "B", "C", "D", "E", "F", "G", "H" };

    if( i < 0 || i > 8 )
        return NULL;

    return letters[i];
}

/**
 * Translate a move into a string
 *
 * @param move a move to convert to string
 * @return a string in human readable form
 */
char * translate_move( const struct Move * move )
{
    char * human_readable = calloc( 11, sizeof( char ) );
    assert( human_readable );
    
    snprintf( human_readable, 11, "%s%d - %s%d",
                row2letter( move->start_row ),
                move->start_col,
                row2letter( move->end_row ),
                move->end_col );

    return human_readable;
}

/**
 * Convert a letter to a row
 *
 * @param letter a letter to convert a row number
 * @return the row number
 */
static int letter2row( char * letter )
{
    char l = letter[0];
    return (int) l - 65;
}

/**
 * Translate an input move
 *
 * @param move a move input by the user
 * @return a move
 */
struct Move * translate_in_move( const char * move )
{
    int length = strnlen( move, 20 );
    int i;
    int valid = 0;
    char start_row[2];
    char start_col[2];
    char end_row[2];
    char end_col[2];

    /* find first letter */
    for( i = 0; i < length; i++ )
        if( isalpha( move[ i ] ) )
        {
            start_row[0] = move[ i ];
            start_row[1] = '\0';
            valid++;
            break;
        }

    /* find next number */
    for( ; i< length; i++ )
        if( isdigit( move[i] ) )
        {
            start_col[0] = move[ i ];
            start_col[1] = '\0';
            valid++;
            break;
        }

    /* find next letter */
    for( ; i < length; i++ )
        if( isalpha( move[ i ] ) )
        {
            end_row[0] = move[ i ];
            end_row[1] = '\0';
            valid++;
            break;
        }

    /* find next number */
    for( ; i < length; i++ )
        if( isdigit( move[ i ] ) )
        {
            end_col[0] = move[ i ];
            end_col[1] = '\0';
            valid++;
            break;
        }

    if( valid != 4 )
        return NULL;

    struct Move * translated_move = new_move( letter2row( start_row ), 
            atoi( start_col ),
            letter2row( end_row ),
            atoi( end_col ) );

    return translated_move;
}

/**
 * Compare a move
 *
 * @param a a move
 * @param b a move
 * @return 1 if moves are the same, else return 0
 */
int compare_move( const struct Move * a, const struct Move * b )
{
    return ( a->start_row == b->start_row &&
             a->start_col == b->start_col &&
             a->end_row == b->end_row &&
             a->end_col == b->end_col );
}

/**
 * Print a move
 *
 * @param move a move to print
 */
void print_move( const struct Move * move )
{
    printf( "(%d,%d),(%d,%d)\n", 
                move->start_row,
                move->start_col,
                move->end_row,
                move->end_col );
}
