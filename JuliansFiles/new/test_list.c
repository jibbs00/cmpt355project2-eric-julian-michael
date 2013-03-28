#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

int main( void )
{
    char * test[ 10 ] = { "hello world", "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog", };
    struct List * list = new_list();

    printf( "Count = %d\n", list->count );

    /* add to list */
    for( int i = 0; i < 10; i++ )
        add_front( &list, test[ i ] );

    /* print list */
    struct ListNode * current = list->head;
    while( current != NULL )
    {
        printf( "%s\n", (char *)current->data );
        current = current->next;
    }

    printf( "Count = %d\n", list->count );

    delete_list( &list );

    return EXIT_SUCCESS;
}
