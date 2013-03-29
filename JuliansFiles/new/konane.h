#ifndef _KONANE_H_
#define _KONANE_H_

#include "state.h"
#include "move.h"
#include "list.h"

struct List * actions( const struct State * state );
struct State * result( const struct State * state, const struct Move * action );
int validate_action( const struct State * state, const struct Move * action );
int terminal_test( const struct State * state );
int utility( const struct State * state );
char opposite_player( char player );

#endif /* _KONANE_H_ */
