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

void delete_game_node( struct GameNode ** root )
{
    if( *root == NULL )
        return;
    
    /* for each child */
    if( (*root)->children != NULL )
    {
        struct ListNode * current = (*root)->children->head;
        struct ListNode * temp;
        while( current != NULL )
        {
            struct GameNode * temp_node = current->data;
            Free( temp_node->state, sizeof( struct State ) );
            Free( temp_node->best_move, sizeof( struct Move ) );

            delete_game_node( &temp_node );

            //temp = current;
            current = current->next;

            //Free( temp, sizeof( struct ListNode ) );
        }
        delete_list( &(*root)->children );
    }
    
    Free( *root, sizeof( struct GameNode ) );
    *root = NULL;
}
