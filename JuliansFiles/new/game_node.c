#include <stdlib.h>
#include <assert.h>

#include "game_node.h"
#include "state.h"
#include "list.h"
#include "utility.h"

struct GameNode * new_game_node( struct State * state, struct GameNode * parent )
{
    struct GameNode * node = Calloc( 1, sizeof( struct GameNode ) );
    assert( node );

    node->state = state;
    node->parent = parent;
    node->children = new_list();

    return node;
}

void add_child_game_node( struct GameNode * parent, struct GameNode * child )
{
    child->parent = parent;
    add_front( &parent->children, child );
}

void delete_children_game_node( struct GameNode * parent )
{
    struct List * children = parent->children;
    struct ListNode * current;

    if( parent == NULL )
        return;
    
    for( current = children->head;
         current != NULL;
         current = current->next )
    {
        delete_children_game_node( current->data );
    }

    delete_list( &children );
    
    Free( parent, sizeof( struct GameNode ) );
}

void print_game_node( struct GameNode * node )
{
}
