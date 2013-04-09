/**
 * @file move.h
 * @author Julian Martinez del Campo
 *
 * This file provides a move in konane
 */
#ifndef _MOVE_H_
#define _MOVE_H_

/** A move */
struct Move {
    int start_row;
    int start_col;
    int end_row;
    int end_col;
};

struct Move * new_move( int start_row, int start_col, int end_row, int end_col );
char * translate_move( const struct Move * move );
struct Move * clone_move( const struct Move * move );
struct Move * translate_in_move( const char * move );
struct Move * translate_first_in_move( const char * move );
char * translate_first_move( const struct Move * move );
int compare_move( const struct Move * a, const struct Move * b );
void print_move( const struct Move * move );
void print_single_move( const struct Move * move );
char row2letter( int i );

#endif /* _MOVE_H_ */
