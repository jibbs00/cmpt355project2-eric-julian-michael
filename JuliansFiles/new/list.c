#include <stdlib.h>
#include <assert.h>

#include "list.h"

struct List * new_list( void )
{
    struct List * list = calloc( 1, sizeof( struct List ) );

    list->head = NULL;
    list->tail = NULL;
    list->count = 0;

    return list;
}

void delete_list( struct List ** list )
{
    struct ListNode * current, * temp;

    current = (*list)->head;
    while( current != NULL )
    {
        temp = current;
        current = current->next;

        free( temp );
    }
}

void add_front( struct List ** list, void * data )
{
    struct ListNode * node = calloc( 1, sizeof( struct List * ) );
    assert( node );

    node->data = data;
    node->next = (*list)->head;

    (*list)->head = node;
    (*list)->count++;
}
