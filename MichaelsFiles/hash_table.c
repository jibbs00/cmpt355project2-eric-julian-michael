/**
 * @author Julian Martinez del Campo
 * @file hash_table.c
 *
 * This file provieds an implementation of a generic hash table
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hash_table.h"
/*#include "memwatch.h" */

#ifdef TRACK_MEMORY_USE
    extern unsigned int memory_usage;
    #define INCREASE_MEM_USE( x ) memory_usage += (x) 
    #define DECREASE_MEM_USE( x ) memory_usage -= (x) 
#else
    #define INCREASE_MEM_USE( x ) do{} while( 0 )
    #define DECREASE_MEM_USE( x ) do{} while( 0 )
#endif

/**
 * Create a new hash table
 *
 * @pre capacity can be any positive integer
 * @post a new hash table is created with capacity of init_capacity and
 *  usage = 0
 * @warning prime numbers are recommended for the capacity of the table
 *
 * @param init_capacity the initial capacity for the hash table, prime numbers
 *  are recommended!
 * @return return a pointer to a new hash table
 */
HashTable * new_htable( int init_capacity )
{
    HashTable * new_table;

    /* create a new table */
    new_table = (HashTable *) malloc( sizeof( HashTable ) );
    assert( new_table != NULL );
    INCREASE_MEM_USE( sizeof( HashTable ) );
    
    /* init table */
    new_table->usage        = 0;
    new_table->capacity     = init_capacity;
    new_table->options      = 0;
    new_table->copy_key     = NULL;
    new_table->copy_val     = NULL;
    new_table->comparator   = NULL;
    new_table->hash         = NULL;
    new_table->print        = NULL;
    new_table->table        = NULL;
    
    return new_table;
}

/**
 * Initialize hash table functions
 *
 * This sets the functions used by the hash table
 *
 * @param table a hash table
 * @param options deletion options, one or more separated with bitwise OR,
 *  see HTDeleteOptions for more details
 * @param copy_key a function that copies the key
 * @param copy_val a function that copies the value
 * @param comparator a function that compares values
 * @param hash a function that hashes a key
 * @param print a function that prints a key value
 * @return return HT_OK on success, return HT_INVLD_CAPACITY if 
 *  capacity is invalid
 */
HTStatus init_htable( HashTable ** table, 
                  int options,
                  void * (*copy_key)( void * ), 
                  void * (*copy_val)( void * ), 
                  int (*comparator)( const void *, const void * ), 
                  unsigned long (*hash)( void *, int ), 
                  void (*print)( const HTEntry * ) )
{
    /* assign functions */
    (*table)->options = options;
    (*table)->copy_key = copy_key;
    (*table)->copy_val = copy_val;
    (*table)->comparator = comparator;
    (*table)->hash = hash;
    (*table)->print = print;
    
    /* check capacity */
    if( (*table)->capacity < 1 )
        return HT_INVLD_CAPACITY;
    assert( (*table)->capacity > 0 );

    /* allocate space in table */
    (*table)->table = ( HTEntry ** )calloc( (*table)->capacity,  sizeof( HTEntry * ) );
    assert( (*table)->table != NULL );
    INCREASE_MEM_USE( (*table)->capacity * sizeof( HTEntry * ) );

    return HT_OK;
}

/**
 * Destroy a hash table
 *
 * @param table a hash table
 */
void destroy_htable( HashTable ** table )
{
    HTEntry * current;
    HTEntry * temp;
    int i;

    /* go through table */
    for( i = 0; i < (*table)->capacity; i++ )
    {
        /* destroy each item in table */
        current = (*table)->table[ i ];
        while( current != NULL )
        {
            temp = current;
            current = current->next;
            
            /* deallocate memory */
            if( IS_KEEP_KEY( (*table)->options ) != 0 )
                free( temp->key );
            if( IS_KEEP_DATA( (*table)->options ) != 0 )
                free( temp->value );
            free( temp );
            DECREASE_MEM_USE( sizeof( HTEntry ) );
        }
    }

    /* deallocate table */
    free( (*table)->table );
    (*table)->table = NULL;
    DECREASE_MEM_USE( (*table)->capacity * sizeof( HTEntry * ) );

    /* deallocate hash table */
    free( *table );
    *table = NULL;
    DECREASE_MEM_USE( sizeof( HashTable ) );
}

/**
 * Clear a hash table
 *
 * @param table a table to clear
 */
void clear_htable( HashTable ** table )
{
    HTEntry * current;
    HTEntry * temp;
    int i;

    /* go through table */
    for( i = 0; i < (*table)->capacity; i++ )
    {
        /* destroy each item in table */
        current = (*table)->table[ i ];
        while( current != NULL )
        {
            temp = current;
            current = current->next;
            
            /* deallocate memory */
            if( IS_KEEP_KEY( (*table)->options ) != 0 )
                free( temp->key );
            if( IS_KEEP_DATA( (*table)->options ) != 0 )
                free( temp->value );
            free( temp );
            DECREASE_MEM_USE( sizeof( HTEntry ) );
        }
    }
}

/**
 * Resize a hash table
 *
 * @pre new_capacity is greater than the current capacity
 * @post a hash table is resized iff new_capacity > current usage
 *
 * @param table a hash table
 * @param new_capacity the new table capacity
 * @return return 0 if successfull, return -1 if capacity is invalid,
 *  return 1 if not all items were copied
 */
HTStatus resize_htable( HashTable ** table, int new_capacity )
{
    HTEntry ** temp;
    HTEntry ** new_table;
    HTEntry * current;
    HTEntry * todelete;
    int temp_capacity;
    int temp_usage;
    int i;

    /* make sure we can continue */
    if( (*table)->hash == NULL )
        return HT_HASH_ERROR;
    assert( (*table)->hash != NULL );

    /* check that we can resize the table */
    if( new_capacity < (*table)->usage )
        return HT_INVLD_CAPACITY;
    assert( (*table)->capacity > 0 );
    
    /* create new table of size */
    new_table = (HTEntry **)calloc( new_capacity, sizeof( HTEntry * ) );
    if( new_table == NULL )
        return HT_MEMORY_ERROR;
    assert( new_table != NULL );
    INCREASE_MEM_USE( new_capacity * sizeof( HTEntry * ) );

    /* copy old table and insert new table */
    temp = (*table)->table;
    temp_capacity = (*table)->capacity;
    temp_usage = (*table)->usage;

    /* update table info */
    (*table)->table = new_table;
    (*table)->capacity = new_capacity;
    (*table)->usage = 0;

    /* copy table */
    for( i = 0; i < temp_capacity ; i++ )
    {
        /* copy each element */
        current = temp[ i ];
        while( current != NULL )
        {
            todelete = current;

            /* re-hash and insert */
            insert_htable( table, current->key, current->value );
            current = current->next;

            /* deallocate memory */
            if( IS_KEEP_KEY( (*table)->options ) != 0 )
                free( todelete->key );
            if( IS_KEEP_DATA( (*table)->options ) != 0 )
                free( todelete->value );
            free( todelete );
            DECREASE_MEM_USE( sizeof( HTEntry ) );
        }
    }

    /* destroy previous table */
    free( temp );
    temp = NULL;
    DECREASE_MEM_USE( temp_capacity * sizeof( HTEntry * ) );



    /* check that all items were copied */
    if( temp_usage != (*table)->usage )
        return HT_COMPARATOR_ERROR;

    return HT_OK;
}

/**
 * Insert an item in the table
 *
 * @param table a hash table
 * @param key a key
 * @param data the value associated with the key
 * @return return HT_OK if insert was successful, 
 *  return HT_MEMORY_ERROR if there was an error allocating
 *  memory, return HT_COPY_ERROR if the copy function was not set
 */
HTStatus insert_htable( HashTable ** table, void * key, void * data )
{
    int key_index;
    HTEntry * new_entry;
    HTEntry * current;

    /* check if everything is in order */
    if( (*table)->hash == NULL )
        return HT_HASH_ERROR;
    if( (*table)->comparator == NULL )
        return HT_COMPARATOR_ERROR;
    if( (*table)->copy_key == NULL )
        return HT_COPY_KEY_ERROR;
    if( (*table)->copy_val == NULL )
        return HT_COPY_VAL_ERROR;
    if( (*table)->usage >= (*table)->capacity )
        return HT_FULL;

    /* make sure we can continue */
    assert( (*table)->hash          != NULL );
    assert( (*table)->comparator    != NULL );
    assert( (*table)->copy_key      != NULL );
    assert( (*table)->copy_val      != NULL );

    /* create a new entry in the table */
    new_entry = (HTEntry *) malloc( sizeof( HTEntry ) );
    if( new_entry == NULL )
        return HT_MEMORY_ERROR;
    assert( new_entry != NULL );
    INCREASE_MEM_USE( sizeof( HTEntry ) );

    /* init entry */
    new_entry->key      = NULL;
    new_entry->value    = NULL;
    new_entry->next     = NULL;
    
    /* copy data over */
    new_entry->key = (*table)->copy_key( key );
    new_entry->value = (*table)->copy_val( data );

    /* hash the key */
    key_index = (*table)->hash( key, (*table)->capacity );

    /* check there is a collision */
    if( (*table)->table[ key_index ] == NULL )
    {
        /* first */
        (*table)->table[ key_index ] = new_entry;
    }
    else
    {
        /* collision */
        for( current = (*table)->table[ key_index ] ; current != NULL ; current = current->next )
        {
            /* make sure keys are not the same */
            if( (*table)->comparator( key, current->key ) == 0 )
            {
                /* deallocate memory */
                if( IS_KEEP_KEY( (*table)->options ) != 0 )
                    free( new_entry->key );
                if( IS_KEEP_DATA( (*table)->options ) != 0 )
                    free( new_entry->value );
                free( new_entry );
                DECREASE_MEM_USE( sizeof( HTEntry ) );

                return HT_KEY_CONFLICTS;
            }
        }
        
        /* link */
        new_entry->next = (*table)->table[ key_index ];
        (*table)->table[ key_index ] = new_entry;
    }
    
    /* increase the number of items in the table */
    (*table)->usage++;

    return HT_OK;
}

/**
 * Change a value associated with the key
 *
 * @param table a hash table
 * @param key a key
 * @param new_data data to associate with the key
 * @return -1 if key is not in table, 0 if succesfully change
 */
HTStatus edit_htable( HashTable ** table, void * key, void * new_data )
{
    HTEntry * current;
    int key_index;

    /* check for errors */
    if( (*table)->hash == NULL )
        return HT_HASH_ERROR;
    if( (*table)->comparator == NULL )
        return HT_COMPARATOR_ERROR;
    if( (*table)->copy_key == NULL )
        return HT_COPY_KEY_ERROR;
    if( (*table)->copy_val == NULL )
        return HT_COPY_VAL_ERROR;

    /* make sure we can continue */
    assert( (*table)->copy_val != NULL );
    assert( (*table)->copy_key != NULL );
    assert( (*table)->comparator != NULL );
    assert( (*table)->hash != NULL );

    /* hash key */
    key_index = (*table)->hash( key, (*table)->capacity );

    /* need to compare keys */
    for( current = (*table)->table[ key_index ] ; current != NULL ; current = current->next )
    {
        if( (*table)->comparator( key, current->key ) == 0 )
        {
            /* key found, change value */
            
            /* free current value */
            if( IS_KEEP_DATA( (*table)->options ) != 0 )
                free( current->value);

            /* allocate new value */
            current->value = (*table)->copy_val( new_data );

            return HT_OK;
        }
    }

    /* reached end of list, item not found */
    return HT_ITEM_NOT_FOUND;

}

/**
 * Lookup an item in the table
 *
 * @param table a hash table
 * @param key a key
 * @return return NULL if there is not data associated with the key in the table,
 *         return the data associated with the key if found.
 */
void * lookup_htable( HashTable ** table, void * key )
{
    HTEntry * current;
    int key_index;

    /* make sure we can use this */
    assert( (*table)->hash != NULL );
    assert( (*table)->comparator != NULL );

    /* hash key */
    key_index = (*table)->hash( key, (*table)->capacity );

    /* check if entry is empty */
    if( (*table)->table[ key_index ] == NULL )
        return NULL;

    /* need to compare keys */
    for( current = (*table)->table[ key_index ] ; current != NULL ; current = current->next )
    {
        if( (*table)->comparator( key, current->key ) == 0 )
        {
            return current->value;
        }
    }

    /* reached end of list, item not found */
    return NULL;
}

/**
 * Remove an item from a hash table
 *
 * @param table a hash table
 * @param key a key
 * @return Return 0 if key was removed; return -1 if key is empty; return 1 
 *  if key was not removed
 */
HTStatus remove_htable( HashTable ** table, void * key )
{
    HTEntry * current;
    HTEntry * before;
    HTEntry * temp;
    int key_index;

    /* check for errors */
    if( (*table)->hash == NULL )
        return HT_HASH_ERROR;
    if( (*table)->comparator == NULL )
        return HT_COMPARATOR_ERROR;

    /* make sure we can continue */
    assert( (*table)->hash != NULL );
    assert( (*table)->comparator != NULL );

    /* hash the key */
    key_index = (*table)->hash( key, (*table)->capacity );

    /* go to entry */
    before = NULL;
    current = (*table)->table[ key_index ];

    /* remove item from list */
    while( current != NULL )
    {
        /* compare items */
        if( (*table)->comparator( current->key, key ) == 0 )
        {
            temp = current;

            /* remove item */
            if( before == NULL )
            {
                (*table)->table[ key_index ] = current->next;
            }
            else
            {
                before->next = current->next;
            }
            (*table)->usage--;

            /* deallocate memory */
            if( IS_KEEP_KEY( (*table)->options ) != 0 )
                free( temp->key );
            if( IS_KEEP_DATA( (*table)->options ) != 0 )
                free( temp->value );
            free( temp );
            DECREASE_MEM_USE( sizeof( HTEntry ) );

            /* clean up */
            temp = NULL;
            
            return HT_OK;
        }

        before = current;
        current = current->next;
    }
    
    return HT_ITEM_NOT_FOUND;
}

/**
 * Print the hash table
 *
 * @pre the print function has been set in the hash table
 * @post the table is printed to stdout
 *
 * @param table a hash table
 * @return return HT_OK on success, else return HT_PRINT_ERROR if
 *  print function is not allocated
 */
HTStatus print_htable( HashTable * table )
{
    HTEntry * current;
    int i;

    /* make sure we can use this */
    if( table->print == NULL )
        return HT_PRINT_ERROR;
    assert( table->print != NULL );

    /* go through entire list */
    for( i = 0; i < table->capacity ; i++ )
    {
        /* print item */
        for( current = table->table[ i ]; current != NULL; current = current->next )
        {
            table->print( current );
        }
    }

    return HT_OK;
}

/**
 * Get the capacity of the table
 *
 * @param table a hash table
 * @return the capacity of the table
 */
int capacity_htable( HashTable * table )
{
    return table->capacity;
}

/**
 * Get the usage of the table
 *
 * @param table a hash table
 * @return the amount of items in the table
 */
int usage_htable( HashTable * table )
{
    return table->usage;
}

/**
 * Get the table load
 *
 * @param table a hash table
 * @return return the current table load
 */
double load_htable( HashTable * table )
{
    return (double)table->usage / (double)table->capacity;
}
