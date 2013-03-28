#ifndef _MOVE_H_
#define _MOVE_H_

struct Move {
    int start_row;
    int start_col;
    int end_row;
    int end_col;
};

struct Move * new_move( int start_row, int start_col, int end_row, int end_col );
char * translate_move( const struct Move * move );
int translate_in_move( const char * move );

#endif /* _MOVE_H_ */
