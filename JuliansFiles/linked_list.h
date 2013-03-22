/**
 * @author Julian Martinez del Campo
 * @file linked_list.h
 *
 * This file provides a generic linked list
 */
#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

/** return codes */
typedef enum _ll_status {
    LL_OK = 0,                  /**< everything is ok */
    LL_COPY_ERROR,              /**< missing copy function */
    LL_MEMORY_ERROR,            /**< error allocating memory */
    LL_COMPR_ERROR,             /**< missing compare function */
    LL_PRINT_ERROR,             /**< mising print function */
    LL_EMPTY,                   /**< list is empty */
    LL_OUT_OF_BOUNDS,           /**< index out of bounds */
    LL_NOT_FOUND,               /**< item not found */
    LL_INVLD_DATA,              /**< data is null */
    LL_INVLD_INSERT_OPTION,     /**< invalid insert options */
    LL_INVLD_OPTIONS,           /**< invalid delete options */
} LLStatus;

/** delete options */
typedef enum _ll_delete_options {
    LL_REMOVE_DATA,             /**< deallocate data stored in list */
    LL_KEEP_DATA                /**< dont free data */
} LLDeleteOptions;

/** insertion options */
typedef enum _ll_insert_options {
    LL_ASCENDING = 1,           /**< insert items in ascending order, that is lowest to highest */
    LL_DESCENDING = -1,         /**< insert items in descending order */
} LLInsertOptions;
 
/**
 * A node for a singly linked list
 */
typedef struct _llnode {
    void * data;                /**< data */
    struct _llnode * next;      /**< link */
} LLNode;

/**
 * A singly linked list
 *
 * This contains information about a linked list
 * including its head, and tail pointers. The size
 * of the list, as well as additional helper functions
 * required to use the list, such as:
 *  - comparator used to compare data stored in the list
 *  - copy a function used to copy data into the list
 *  - print a funciton that prints the data stored in the list
 * Additionally, options must be set, these are the deletion
 * options used when deallocating memory, see LLDeleteOptions for
 * more more details.
 */
typedef struct _llist {
    LLNode * head;                                  /**< head of list */
    LLNode * tail;                                  /**< tail of list */
    int options;                                    /**< deletion options */
    int size;                                       /**< size of list */
    int (*comparator)( const void *, const void * );/**< item comparator */
    void * (*copy)( void * );                       /**< copy data from item */
    void (*print)( const void * );                  /**< print a node */
} LinkedList;

/** creation and deletion */
LinkedList * new_llist( void );
LLStatus init_llist( LinkedList ** list, 
                 int options,
                 int (*comparator)( const void *, const void * ),
                 void * (*copy)( void * ), 
                 void (*print)( const void * ) );
LLStatus delete_llist( LinkedList ** list );

/** init operations */
void set_comparator_llist( LinkedList ** list, int (*comparator)( const void *, const void * ) );
void set_print_llist( LinkedList ** list, void (*print)( const void * ) );
void set_options_llist( LinkedList ** list, int options );
void set_copy_llist( LinkedList ** list, void * (*copy)( void * ) );

/** insertion operations */
LLStatus insert_front_llist( LinkedList ** list, void * data );
LLStatus insert_back_llist( LinkedList ** list, void * data );
LLStatus insert_llist( LinkedList ** list, void * data, int index );
LLStatus insert_inorder_llist( LinkedList ** list, void * data );

/** deletion */
LLStatus remove_front_llist( LinkedList ** list );
LLStatus remove_back_llist( LinkedList ** list );
LLStatus remove_llist( LinkedList ** list, int index );
LLStatus remove_one_llist( LinkedList ** list, void * data );
int remove_all_llist( LinkedList ** list, void * data );
LLStatus clear_llist( LinkedList ** list );

/** retrieval */
void * get_front_llist( LinkedList * list );
void * get_back_llist( LinkedList * list );
void * get_llist( LinkedList * list, int index );
int locate_llist( LinkedList * list, void * data );

/** other functions */
LLStatus print_llist( LinkedList * list );
int is_empty_llist( LinkedList * list );
int size_llist( LinkedList * list );
int contains_llist( LinkedList * list, void * data );

LLStatus sort_llist( LinkedList ** list );

/* node functions */
LLNode * get_frontn_llist( LinkedList * list );
LLNode * get_backn_llist( LinkedList * list );
LLNode * getn_llist( LinkedList * list, int index );

#endif /* _LINKED_LIST_H_ */
