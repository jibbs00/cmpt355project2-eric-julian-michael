#include <stdlib.h>
#include <assert.h>

#include "game_node.h"
#include "state.h"
#include "list.h"

struct GameNode * new_game_node( struct State * state, struct GameNode * parent )
{
    struct GameNode * node = calloc( 1, sizeof( struct GameNode ) );
    assert( node );

    node->state = state;
    node->parent = parent;
    node->children = new_list();

    return node;
}

void add_children_game_node( struct GameNode * parent, struct GameNode * child )
{
    child->parent = parent;
    add_front( &parent->children, child );
}
