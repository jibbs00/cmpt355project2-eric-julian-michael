#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree.h"

/**
 * Copy pointer
 *
 * @param p
 * @return p
 */
void * copy( void * p )
{
    return p;
}

/**
 * Compare nodes
 *
 * @param a a node
 * @param b a node
 * @return -1, 0, 1
 */
int compare_nodes( const void  * a, const void * b )
{
}

/**
 * Print a node
 *
 * @param node a node
 */
void print_node( const void * node )
{
    TNode * n = (TNode * )node;

    printf( "state  @ %p\n", (void *)n->state );
    printf( "parent @ %p\n", (void *)n->parent );
    printf( "list   @ %p\n", (void *)n->list );
}

/**
 * Create a new tree node
 *
 * @param state the current state
 * @param parent the parent node
 * @return a new tree node with the state, and parent node set
 */
TNode * create_node( char ** state, TNode * parent )
{
    TNode * node = (TNode *)malloc( sizeof( TNode ) );
    assert( node != NULL );

    node->state = state;
    node->parent = parent;
    node->list = new_llist();

    init_llist( &(node->list), LL_KEEP_DATA, compare_nodes, copy, print_node );

    return node;
}

/**
 * Delete a node and all child nodes
 *
 * @param root the root node to delete
 */
void delete_node( TNode ** root )
{
    LLNode * current;

    /* base case */
    if( root == NULL )
        return;
    
    /* process children */
    current = (*root)->list->head;
    while( current != NULL )
    {
        delete_node( current->data );
        current = current->next;
    }
    
    /* delete node */
    free( current );
}

/**
 * Insert a child node
 *
 * @param root the node to insert child
 * @param node the child node
 */
void insert_node( TNode ** root, TNode * node )
{
    LinkedList * list = (*root)->list;

    insert_back_llist( &list, node );
}

/**
 * Check if a node is a leaf node
 *
 * @param node to check
 * @return 1 if node is a leaf, else 0
 */
int isLeaf( TNode * node )
{
    /* no children */
    if( is_empty_llist( node->list ) == 1 ) 
        return 1;

    return 0;
}

/**
 * Traverse a tree
 *
 * @param root the starting/root node
 * @param pre a function to process pre traversal
 * @param inorder a function to process nodes in order
 * @param post a function to proces nodes after traversal
 */
void traverse_tree( TNode ** root, void (*pre)( TNode * n ), void (*inorder)( TNode * n ), void (*post)( TNode * n ) )
{
    LLNode * current;

    if( root == NULL )
        return;

    pre( *root );

    /* visit children */
    current = ((*root)->list)->head;
    while( current != NULL )
    {
        inorder( (TNode *)current->data );
        traverse_tree( (TNode *)current->data, pre, inorder, post );
        current = current->next;
    }


    post( *root );
}

/**
 * Get the current state from a node
 *
 * @param node a node
 * @return the current state
 */
char ** getState( TNode * node )
{
    return node->state;
}

/**
 * Set the state of a node
 * 
 * @param node a node
 * @param state the state to set
 */
void setState( TNode ** node, char ** state )
{
    (*node)->state = state;
}
