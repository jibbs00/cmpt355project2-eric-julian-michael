/**
 * @author Julian Martinez del Campo
 * @file linked_list.c
 *
 * Provides an implementation of a linked list
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"

/**
 * Check if options are valid
 *
 * @param options the options to check
 * @return return 1 i options are valid; else return 0
 */
static int is_options_valid( int options )
{
    switch( options )
    {
        /* valid options, fall through */
        case LL_REMOVE_DATA:
        case LL_KEEP_DATA:
            return 1;
        /* invalid options */
        default:
            return 0;
    }
}

/**
 * Create a new linked list
 *
 * This creates a new linked list.
 *
 * @warning the programmer must set the following functions
 *  after initialization
 *      - comparator
 *      - copy
 *      - print
 *
 * @post an empty linked list is returned. The function pointers
 *  are initialized to null.
 */
LinkedList * new_llist( void )
{
    LinkedList * new_list;
    
    /* create new list */
    new_list = (LinkedList *) malloc( sizeof( LinkedList ) );

    /* initialize */
    new_list->options       = 0;
    new_list->head          = NULL;
    new_list->tail          = NULL;
    new_list->size          = 0;
    new_list->comparator    = NULL;
    new_list->copy          = NULL;
    new_list->print         = NULL;

    return new_list;
}

/**
 * Initializes a linked list
 *
 * This function clears any exisiting data in the list, and sets the functions used by the 
 * linked list
 *
 * @warning this function does not check the comparator or print function
 *  because they are not necessary for basic functionality. Functions that
 *  do require a comparator or print function will return error codes.
 *
 * @param list a linked list
 * @param options deletion options, see LLDeleteOptions for more details
 * @param comparator a function that compares items in a list
 * @param copy a function that copies items in the list
 * @param print a function that prints the items in the list
 * @return returns LL_OK on success, else return LL_COPY_ERROR if
 *  copy function was invalid, LL_INVLD_OPTIONS if options are invalid
 */
LLStatus init_llist( LinkedList ** list, 
                 int options,
                 int (*comparator)( const void *, const void * ), 
                 void * (*copy)( void * ), 
                 void (*print)( const void * ) )
{
    /* check */
    if( is_options_valid( options ) == 0 )
        return LL_INVLD_OPTIONS;
    if( copy == NULL )
        return LL_COPY_ERROR;
    
    /* set options */
    (*list)->options = options;

    /* assign functions */
    (*list)->comparator = comparator;
    (*list)->copy = copy;
    (*list)->print = print;

    return LL_OK;
}
/**
 * Destroy a linked list
 *
 * This function destroys the linked list. 
 *
 * @post the linked list is destroyed and is set to null
 *
 * @param list a pointer to a linked list
 * @return return LL_OK on success, else return LL_INVLD_OPTIONS
 *  if the deletion options are invalid
 */
LLStatus delete_llist( LinkedList ** list )
{
    LLNode * current;
    LLNode * temp;

    /* check */
    if( is_options_valid( (*list)->options ) == 0 )
        return LL_INVLD_OPTIONS;

    /* iterate through list and deallocate nodes */
    current = (*list)->head;
    temp = NULL;

    while( current != NULL )
    {
        temp = current;
        current = current->next;

        /* deallocate node */
        if( (*list)->options == LL_REMOVE_DATA )
        {
            free( temp->data );
            temp->data = NULL;
        }
        free( temp );
        temp = NULL;
    }

    /* deallocate linked list */
    free( *list );

    /* clean up */
    *list = NULL;

    return LL_OK;
}

/**
 * Set a comparator
 *
 * This function sets the comparator used by the linked
 *  list
 *
 * @param list a linked list
 * @param comparator a comparator function
 */
void set_comparator_llist( LinkedList ** list, int (*comparator)( const void *, const void * ) )
{
    (*list)->comparator = comparator;
}

/**
 * Set a print function
 *
 * This function sets the print function to be used by the linked list
 *
 * @param list a linked list
 * @param print a print functions
 */
void set_print_llist( LinkedList ** list, void (*print)( const void * ) )
{
    (*list)->print = print;
}

/**
 * Set deletion options
 *
 * This function sets the delete options used by the linked list
 *
 * @warning The deletion options should not be changed unless
 *  the list is empty. There is a high risk data may be lost otherwise
 *
 * @param list a linked list
 * @param options the new deletion options
 */
void set_options_llist( LinkedList ** list, int options )
{
    (*list)->options = options;
}

/**
 * Set a copy function
 *
 * This function sets the copy function used by the linked list to copy
 *  data into the list
 *
 * @warning this function should not be changed unless the list is empty.
 *  There is a high risk data may be lost, or data may be improperly managed.
 *
 * @param list a linked list
 * @param copy a copy function
 */
void set_copy_llist( LinkedList ** list, void * (*copy)( void * ) )
{
    (*list)->copy = copy;
}

/**
 * clear a linked list
 *
 * This function removes all items the linked list. 
 *
 * @post the linked list is empty
 *
 * @param list a pointer to a linked list
 * @return return LL_OK on success, else return
 *  LL_INVLD_OPTIONS if options are invalid.
 */
LLStatus clear_llist( LinkedList ** list )
{
    LLNode * current;
    LLNode * temp;

    /* check */
    if( is_options_valid( (*list)->options ) == 0 )
        return LL_INVLD_OPTIONS;

    /* iterate through list and deallocate nodes */
    current = (*list)->head;
    temp = NULL;

    while( current != NULL )
    {
        temp = current;
        current = current->next;

        /* deallocate node */
        if( (*list)->options == LL_REMOVE_DATA )
        {
            free( temp->data );
            temp->data = NULL;
        }

        free( temp );
        temp = NULL;
    }

    /* reinit */
    (*list)->head = NULL;
    (*list)->tail = NULL;
    (*list)->size = 0;

    return LL_OK;
}

/**
 * Check if a list is empty.
 *
 * @pre list is not null
 *
 * @param list a linked list
 * @return return 1 if list is empty, else return 0
 */
int is_empty_llist( LinkedList * list )
{
    if( list->size == 0 )
        return 1;
    else
        return 0;
}

/**
 * Get the size of a list.
 *
 * @pre list is not null
 *
 * @param list a linked list
 * @return return the size of the list
 */
int size_llist( LinkedList * list )
{
    return list->size;
}

/**
 * Insert an item at the front  a list.
 *
 * @pre list is not null, copy function is set
 * @post an item is inserted at the front of the list.
 *
 * @param list a pointer to a linked list
 * @param data an item to add to the list
 * @return return LL_OK on success, else return LL_COPY_ERROR
 *  if copy function was not set, LL_INVLD_DATA if data is null,
 *  LL_MEMORY_ERROR if an error occured allocating memory
 */
LLStatus insert_front_llist( LinkedList ** list, void * data )
{
    LLNode * new_node;

    /* make sure we have everything */
    if( (*list)->copy == NULL )
        return LL_COPY_ERROR;
    if( data == NULL )
        return LL_INVLD_DATA;

    assert( (*list)->copy != NULL );

    /* create a new node */
    new_node = (LLNode *) malloc( sizeof( LLNode ) );
    if( new_node == NULL )
        return LL_MEMORY_ERROR;
    assert( new_node != NULL ); 

    /* init node */
    new_node->data = NULL;
    new_node->next = NULL;

    /* create new data and copy data over to new node */
    new_node->data = (*list)->copy( data );

    /* set links */
    if( (*list)->size == 0 )
    {
        (*list)->head = new_node;
        (*list)->tail = new_node;
    }
    else
    {
        new_node->next = (*list)->head;
        (*list)->head = new_node;
    }
    (*list)->size++;

    return LL_OK;
}

/**
 * Remove an item from the front of the list
 *
 * @pre list is not null
 * @post an item is removed from the list, if empty do nothing.
 *
 * @param list a pointer to a list
 * @return return 0 if item was successfully removed from front of list
 *         return 1 if the list is empty
 */
LLStatus remove_front_llist( LinkedList ** list )
{
    LLNode * temp;

    /* list is empty */
    if( (*list)->size == 0 )
    {
        return LL_EMPTY;
    }

    /* set links */
    temp = (*list)->head;
    if( (*list)->size == 1 )
    {
        /* head of list */
        (*list)->head = NULL;
        (*list)->tail = NULL;
    }
    else
    {
        /* remove from list */
        (*list)->head = temp->next;
    }

    /* deallocate */
    if( (*list)->options == LL_REMOVE_DATA )
        free( temp->data );
    free( temp );

    (*list)->size--;

    return LL_OK;
}

/**
 * Insert an item at the back of the list
 *
 * @pre list is not null, copy function is set
 * @post an item is added to the back of the list
 *
 * @param list a pointer to a list
 * @param data an item to add
 * @return return LL_OK on success, else return LL_COPY_ERROR
 *  if copy function was not set, LL_INVLD_DATA if data is null,
 *  LL_MEMORY_ERROR if an error occured allocating memory
 */
LLStatus insert_back_llist( LinkedList ** list, void * data )
{
    LLNode * new_node;

    /* make sure we have everything */
    if( (*list)->copy == NULL )
        return LL_COPY_ERROR;
    if( data == NULL )
        return LL_INVLD_DATA;

    assert( (*list)->copy != NULL );

    /* create a new node */
    new_node = (LLNode *) malloc( sizeof( LLNode ) );
    if( new_node == NULL )
        return LL_MEMORY_ERROR;
    assert( new_node != NULL ); 

    /* init node */
    new_node->data = NULL;
    new_node->next = NULL;

    /* create new data and copy data over to new node */
    new_node->data = (*list)->copy( data );
    
    /* set links */
    if( (*list)->size == 0 )
    {
        (*list)->head = new_node;
        (*list)->tail = new_node;
    }
    else
    {
        (*list)->tail->next = new_node;
        (*list)->tail = new_node;
    }
    (*list)->size++;

    return LL_OK;
}

/**
 * This item removes an item from the back of a list
 *
 * @pre list is not null
 * @post an item is removed from the back, if list is empty then the
 *  list is unchanged
 *
 * @param list a pointer to a list
 * @return return 0 if item is successfully removed, if list is
 *  empty return 1
 */
LLStatus remove_back_llist( LinkedList ** list )
{
    LLNode * last;
    LLNode * before;
    LLNode * current;

    /* list is empty */
    if( is_empty_llist( *list ) == 1 )
    {
        return LL_EMPTY;
    }

    /* set links */
    last = (*list)->tail;

    /* one item left in list */
    if( (*list)->size == 1 )
    {
        /* remove from list */
        (*list)->head = NULL;
        (*list)->tail = NULL;
    }
    else
    {
        /* get second to last node */
        // before = get_node_llist( *list, (*list)->size - 2 ); 

        before = NULL;
        current = (*list)->head;
        while( current->next != NULL )
        {
            before = current;
            current = current->next;
        }


        before->next = NULL;
        (*list)->tail = before;
    }

    /* deallocate */
    if( (*list)->options == LL_REMOVE_DATA )
    {
        free( last->data );
        last->data = NULL;
    }

    free( last );
    last = NULL;

    (*list)->size--;

    return LL_OK;
}

/**
 * Insert an item at index
 *
 * This will insert an item into the list at the given index.
 *
 * @param list a pointer to a list
 * @param data an item to add to the list
 * @param index the index to insert the item at.
 * @return return LL_OK on success, return LL_COMPR_ERROR
 *  if comparator is not set, LL_OUT_OF_BOUNDS if the index
 *  is out of bounds, LL_MEMORY_ERROR if there was an error 
 *  allocating memory. LL_INVLD_DATA if data is null
 */
LLStatus insert_llist( LinkedList ** list, void * data, int index )
{
    LLNode * new_node;
    LLNode * current;
    LLNode * before;
    int i;

    /* make sure we can run */
    if( (*list)->copy == NULL )
        return LL_COMPR_ERROR;
    if( ( index < 0 ) || ( index > (*list)->size ) )
        return LL_OUT_OF_BOUNDS;
    if( data == NULL )
        return LL_INVLD_DATA;

    /* get node before and at index */
    for( i = 0, before = NULL, current = (*list)->head; 
         i < index; 
         i++, before = current, current = current->next )
    {}

    /* insert node */
    if( i == 0 )
    {
        return insert_front_llist( list, data );
    }
    else if( i == (*list)->size - 1 )
    {
        return insert_back_llist( list, data );
    }
    else
    {
        /* create a new node */
        new_node = (LLNode *) malloc( sizeof( LLNode ) );
        if( new_node == NULL )
            return LL_MEMORY_ERROR;
        assert( new_node != NULL ); 

        /* init node */
        new_node->data = NULL;
        new_node->next = NULL;

        /* create new data and copy data over to new node */
        new_node->data = (*list)->copy( data );
        
        /* set links */
        new_node->next = before->next;
        before->next = new_node;

        (*list)->size++;
    }

    return LL_OK;
}

/**
 * Insert an item in order
 *
 * @pre the list must be sorted already
 *  the comparator function must be set, and the copy function must be set
 * @post the item is inserted into the list in order
 *
 * @param list a pointer to a list
 * @param data an item to add to the list
 * @return return LL_OK on success, else return LL_COPY_ERROR
 *  if copy function was not set, LL_INVLD_DATA if data is null,
 *  LL_MEMORY_ERROR if an error occured allocating memory
 */
LLStatus insert_inorder_llist( LinkedList ** list, void * data )
{
    LLNode * new_node;
    LLNode * current;
    LLNode * before;

    /* make sure we can run */
    if( (*list)->comparator == NULL )
        return LL_COMPR_ERROR;
    if( (*list)->copy == NULL )
        return LL_COPY_ERROR;
    if( data == NULL )
        return LL_INVLD_DATA;

    assert( (*list)->comparator != NULL );
    assert( (*list)->copy != NULL );

    /* create new node */
    new_node = (LLNode *) malloc( sizeof( LLNode ) );
    if( new_node == NULL )
        return LL_MEMORY_ERROR;

    assert( new_node != NULL ); 

    /* initialize new node */
    new_node->data = NULL;
    new_node->next = NULL;

    /* create new data and copy data over to new node */
    new_node->data = (*list)->copy( data );

    /* find out where to insert item */
    for( current = (*list)->head, before = NULL; 
         current != NULL; 
         before = current, current = current->next )
    {
        /* insert here */
        if( (*list)->comparator( current->data, data ) == 1 )
        {
            /* check if first */
            if( before == NULL )
            {
                new_node->next = (*list)->head;
                (*list)->head = new_node; 
            }
            /* other */
            else
            {
                new_node->next = before->next;
                before->next = new_node;
            }

            /* increment size of list */
            (*list)->size++;

            break;
        }
    }

    /* check if last */
    if( current == NULL )
    {
        /* insert at end of list */
        if( (*list)->size == 0 )
        {
            (*list)->head = new_node;
            (*list)->tail = new_node;
        }
        else
        {
            (*list)->tail->next = new_node;
            (*list)->tail = new_node;
        }

        /* increment size of list */
        (*list)->size++;
    }


    return LL_OK;
}

/**
 * Get the item at the front of the list
 *
 * @pre list is not null
 * @post an item from the front of the list is returned
 *
 * @param list a linked list
 * @return an item at the front of the list is returned, if list is
 *  empty then return null.
 */
void * get_front_llist( LinkedList * list )
{
    if( list->size == 0 )
        return NULL;

    return list->head->data;
}

/**
 * Get the item at the back of the list
 *
 * @pre list is not null
 * @post item from the front of the list is returned, if the list is
 *  empty then return null.
 *
 * @param list a linked list
 * @return item at the back of the list is returned, if list is empty
 *  then return null.
 */
void * get_back_llist( LinkedList * list )
{
    if( list->size == 0 )
        return NULL;

    return list->tail->data;
}

/**
 * Get an item at a specified index in the list
 *
 * @pre list is not null
 * @post an item at index is returned
 *
 * @param list a pointer to a list
 * @param index the index to get
 * @return item at index is returned, if index is out of bounds, return null
 */
void * get_llist( LinkedList * list, int index )
{
    LLNode * current;
    int current_index;

    /* check bounds */
    if( index < 0 || index > list->size )
    {
        return NULL;
    }

    /*traverse list */
    for( current = list->head, current_index = 0; 
         current_index < index && current != NULL;
         current = current->next, current_index++ )
    {}

    if( current == NULL )
        return NULL;

    /* return data */
    return current->data;
}

/**
 * locate an item in the list
 *
 * @pre list is not null, comparator is set
 * 
 * @param list a list
 * @param data an item to locate
 * @return return index of the item, else return -1 if item was not found
 */
int locate_llist( LinkedList * list, void * data )
{
    LLNode * current;
    int data_index;
    int current_index;
    
    /* make sure we have everything */
    if( list->comparator == NULL )
        return -1;
    if( data == NULL )
        return -1;

    assert( list->comparator != NULL );

    /* search for item */
    for( current = list->head, data_index = -1, current_index = 0;
         current != NULL;
         current = current->next, current_index++ )
    {
        if( list->comparator( data, current->data ) == 0 )
        {
            data_index = current_index;
            break;
        }
    }

    return data_index;
}

/**
 * Search a linked list for data item
 *
 * @param list a linked list
 * @param data the data to check for
 * @return return 1 if data is in the list, return 0 if data is not
 *  in the list, return -1 if comparator is not set, returns -2 if data is null
 */
int contains_llist( LinkedList * list, void * data )
{
    LLNode * current;

    /* make sure we have everything */
    if( list->comparator == NULL )
        return -1;
    if( data == NULL )
        return -2;

    assert( list->comparator != NULL );

    /* traverse list */
    for( current = list->head; current != NULL; current = current->next )
    {
        if( list->comparator( data, current->data ) == 0 )
            return 1;
    }

    return 0;
}

/**
 * print the list
 *
 * @pre list is not null, print is set
 * @post the list is printed to screen
 *
 * @param list a linked list
 * @return return LL_OK on success, else return
 *  LL_PRINT_ERROR if print function is not set.
 */
LLStatus print_llist( LinkedList * list )
{
    LLNode * current;
    int i;

    /* make sure we have everything */
    if( list->print == NULL )
        return LL_PRINT_ERROR;

    assert( list->print != NULL );

    /* traverse list and print */
    for( current = list->head, i = 0; current != NULL; current = current->next, i++ )
    {
        printf( "%5d. ", i );           /** print number */
        list->print( current->data );   /** print value */
    }

    return LL_OK;
}

/**
 * Remove an item at index from the list
 *
 * @param list a linked list
 * @param index the index of item to remove
 * @return return LL_OK on success, else return LL_OUT_OF_BOUNDS 
 *  if index is out of bounds, return LL_EMPTY if the list is empty,
 *  return LL_INVLD_OPTIONS if options are invalid.
 */
LLStatus remove_llist( LinkedList ** list, int index )
{
    LLNode * current;
    LLNode * before;
    LLNode * temp;
    int i;

    /* check if list is empty */
    if( is_empty_llist( *list ) == 1 )
        return LL_EMPTY;

    /* check bounds */
    if( ( index < 0 ) || ( index > ( (*list)->size -1 ) ) )
        return LL_OUT_OF_BOUNDS;;

    /* check options */
    if( is_options_valid( (*list)->options ) == 0 )
        return LL_INVLD_OPTIONS;

    /* remove from list */
    if( index == 0 )
    {
        return remove_front_llist( list );
    }
    else if( index == (*list)->size )
    {
        return remove_back_llist( list );
    }
    else
    {
        /* go to index */
        for( current = (*list)->head, before = NULL, i = 0; i < index; current = current->next, i++ )
            before = current;

        if( before == NULL )
        {
            /* item is head */
            temp = (*list)->head;
            (*list)->head = temp->next;
        }
        else
        {
            temp = current;
            before->next = current->next;
        }

        /* deallocate */
        if( (*list)->options == LL_REMOVE_DATA )
        {
            free( temp->data );
            temp->data = NULL;
        }

        free( temp );
        temp = NULL;

        (*list)->size--;
    }

    return LL_OK;
}

/**
 * Remove one item from the list
 *
 * Removes one instance of an item (data) from the list
 *
 * @param list a linked list
 * @param data the item to remove from the list
 * @return return LL_OK on success, else return LL_COMPR_ERROR
 *  if comparator was not set, return LL_INVLD_OPTIONS if options
 *  are invalid, LL_INVLD_DATA if data is null
 */
LLStatus remove_one_llist( LinkedList ** list, void * data )
{
    LLNode * current;
    LLNode * before;
    LLNode * temp;

    /* make sure we can continue */
    if( (*list)->comparator == NULL )
        return LL_COMPR_ERROR;
    if( is_options_valid( (*list)->options ) == 0 )
        return LL_INVLD_OPTIONS;
    if( data == NULL )
        return LL_INVLD_DATA;

    /* iterate through list */
    for( before = NULL, current = (*list)->head;
         current != NULL;
         before = current, current = current->next )
    {
        /* check if data matches item */
        if( (*list)->comparator( data, current->data ) == 0 )
        {
            /* remove item from the list */
            if( current == (*list)->head )
            {
                return remove_front_llist( list );
            }
            else if( current == (*list)->tail )
            {
                return remove_back_llist( list );
            }
            else
            {
                temp = current;
                before->next = current->next;

                /* deallocate memory */
                if( (*list)->options == LL_REMOVE_DATA )
                {
                    free( temp->data );
                    temp->data = NULL;
                }

                free( temp );
                temp = NULL;

                /* decrement list size */
                (*list)->size--;

            }

            return LL_OK;
        }
    }

    return LL_NOT_FOUND;
}

/**
 * Remove all instances of data from a list
 *
 * This function removes all instances of data from the linked
 * list.
 *
 * @param list a linked list
 * @param data the data item to remove
 * @return return the number of items successfully removed, return -1 if comparator is not set,
 *  or -2 if data was null
 */
int remove_all_llist( LinkedList ** list, void * data )
{
    int items_removed;
    int rv;

    /* make sure we can continue */
    if( (*list)->comparator == NULL )
        return -1;
    assert( (*list)->comparator != NULL );
    if( data == NULL )
        return -2;

    /* iterate through list */
    items_removed = 0;
    
    /* delete items from the list */
    for( ;; )
    {
        rv = remove_one_llist( list, data );
        if( rv == LL_OK )
            items_removed++;
        else
            break;
    }

    return items_removed;
}

/**
 * Get the first node in the list
 *
 * @param list a linked list
 * @return returns a linked list node on success, return null if
 *  an error occured
 */
LLNode * get_frontn_llist( LinkedList * list )
{
    if( list->size == 0 )
        return NULL;

    return list->head;
}

/**
 * Get the last node in the list
 *
 * @param list a linked list
 * @return returns a linked list node on success, return null if
 *  an error occured
 */
LLNode * get_backn_llist( LinkedList * list )
{
    if( list->size == 0 )
        return NULL;

    return list->tail;
}

/**
 * Get a node from a list at the specified index
 *
 * @pre list is not null
 * @post node is returned
 *
 * @param list a linked list
 * @param index index of node to return
 * @return a node at index, if index is out of range return null.
 */
LLNode * getn_llist( LinkedList * list, int index )
{
    LLNode * current;
    int current_index;

    /* check bounds */
    if( index < 0 || index > list->size )
    {
        return NULL;
    }

    /*traverse list */
    for( current = list->head, current_index = 0; 
         current_index < index;
         current = current->next, current_index++ )
    {}

    /* return data */
    return current;
}
