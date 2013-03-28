#ifndef _KONANE_H_
#define _KONANE_H_

#define SIZE 8
#include "state.h"

void * actions( const struct State * state );
struct State * result( const struct State * state, const void * action );
int validateAction( const char ** board, char player, const struct Move * move );
int terminalTest( const struct State * state );
int utility( const void * state, const void * player );

#endif /* _KONANE_H_ */
