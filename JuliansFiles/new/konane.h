#ifndef _KONANE_H_
#define _KONANE_H_

#include "state.h"

void * actions( const struct State * state );
struct State * result( const struct State * state, const void * action );
int validateAction( const char ** board, char player, const struct Move * move );
int terminalTest( const struct State * state );
int utility( const void * state, const void * player );
static void * actionsUp( const char ** board, int col, char player );
static void * actionsDown( const char ** board, int col, char player );
static void * actionsLeft( const char ** board, int row, char player );
static void * actionsRight( const char ** board, int row, char player );

#endif /* _KONANE_H_ */
