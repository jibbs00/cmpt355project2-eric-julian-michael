/**
 * @author Julian Martinez del Campo
 * @file tree.h
 *
 * This file provides a generic tree
 */
#ifndef _TREE_H_
#define _TREE_H_

#include "linked_list.h"

/* A tree node */
typedef struct _tnode {
    char ** state;          /**< current state */
    struct _tnode * parent; /**< parent node */
    LinkedList * children;  /**< list of children */
} TNode;


TNode * create_node( char ** state, TNode * parent );
void delete_node( TNode ** root );
void insert_node( TNode ** root, TNode * node );
int isLeaf( TNode * node );
void traverse_tree( TNode ** root, void (*pre)( TNode * n ), void (*inorder)( TNode * n ), void (*post)( TNode * n ) );
void print_tree( TNode * root );

char ** getState( TNode * node );
void setState( TNode ** node, char ** state );

#endif /* _TREE_H_ */
