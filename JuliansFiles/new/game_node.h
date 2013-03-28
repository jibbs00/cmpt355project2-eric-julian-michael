#ifndef _GAME_NODE_
#define _GAME_NODE_

#include "state.h"

struct GameNode {
    struct State * state;
    struct GameNode * parent;
    struct List * children;
};

struct GameNode * new_game_node( struct State * state, struct GameNode * parent );
void add_children_game_node( struct GameNode * parent, struct GameNode * child );
void delete_children_game_node( struct GameNode * parent );

#endif /* _GAME_NODE_ */
