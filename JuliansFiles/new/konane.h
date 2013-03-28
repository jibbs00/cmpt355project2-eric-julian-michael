#ifndef _KONANE_H_
#define _KONANE_H_

#include "state.h"

#define SIZE 8

void * actions( const struct State * state );
char ** result( const struct State * state, const struct Move * action );
int validateAction( const struct State * state, const struct Move * move );
int terminalTest( const struct State * state );
int utility( const void * state, const void * player );

#endif /* _KONANE_H_ */
