#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include"func.h"
#include"tree.h"

/*** global pointers for the tree head ***/
TNode *tree_head = NULL;


void copy_state(TNode *node, char state[][BOARD_SIZE])
{
  /* function copies one board state to another */
  for(int x = 0; x < BOARD_SIZE; x++){
    for(int y = 0; y < BOARD_SIZE; y++){
      node->state[x][y] = state[x][y];
    }
  }
}


/**
 * Create a new tree node
 *
 * @param state the current state
 * @param parent the parent node
 * @return a new tree node with the state, and parent node set
 */
void create_node(TNode * parent, char state[][BOARD_SIZE])
{
    TNode * new_node = (TNode *)malloc( sizeof( TNode ) );
    assert( new_node != NULL );
    memset(new_node,0,sizeof( TNode ) );
    
    /*(alocate memory for state of new node */
    /*new_node->state = malloc( BOARD_SIZE * BOARD_SIZE * sizeof(char));
    assert( new_node->state != NULL );
    memset(new_node->state,0,( BOARD_SIZE * BOARD_SIZE * sizeof(char)));*/
    /*iterate through and initialize new_node->state */
    
    /* set node state */
    copy_state(new_node,state);
    //new_node->state = state;

    /* set initial tree head */
    if(tree_head == NULL){
      new_node->parent = NULL;
      new_node->next = NULL;
      new_node->child_head = NULL;
      tree_head = new_node;
    }
    else{
    
      /*add as child to parent node */
      TNode *prev = parent->child_head;
      if(prev != NULL){
	TNode *cur = prev->next;
	for(;(cur != NULL);prev = prev->next, cur = cur->next);
	prev->next = new_node;
      }
      else{
	parent->child_head = new_node;
      }

      /* set node attributes */
      new_node->parent = parent;  
      new_node->next = NULL;
      new_node->child_head = NULL;
    }
}

/**
 * Delete a node and all child nodes
 *
 * @param root the root node to delete
 */
void delete_node( TNode * root)
{
    TNode * current;

    /* base case */
    if( root == NULL )
        return;
    
    /* process children */
    current = root->child_head;
    while( current != NULL )
    {
        delete_node( current );
        current = current->next;
    }
    
    /* delete node */
    free( current );
    free( root);
}



/*void _cleanTesttree(TNode *head)
{
  TNode *del = head;

  //iterate through tree, from level to level, deleting nodes
  while(del != NULL){
      TNode *temp = del;
      if(del->next != NULL){
	del = del->next;
      }
      else{
	if(del->parent != NULL){
	  del = del->parent->child_head->child_head;
	}
	else{
	  del = del->child_head;
	}
      }

      delete_node(temp);
  }

}*/


void print_node(TNode * n)
{
  printf(" UTILITY VAL: %d\n",n->utility_val);
  printf(" STATE:\n");

  for(int x = 0; x < BOARD_SIZE; x++){
     for(int y = 0; y < BOARD_SIZE; y++){
       printf("%c",n->state[x][y]);
     }
     printf("\n");
  }
      
}

/**
 * Traverse a tree
 *
 * @param root the starting/root node
 * @param pre a function to process pre traversal
 * @param inorder a function to process nodes in order
 * @param post a function to proces nodes after traversal
 */
void traverse_tree(TNode * root, void (*pre)( TNode * n ), void (*inorder)( TNode * n ), void (*post)( TNode * n ) )
{
    TNode * current;

    if( root == NULL )
        return;

    if(pre != NULL)
      pre( root );

    // visit children
    current =  root->child_head;
    while( current != NULL )
    {
      if(inorder != NULL)
	inorder( current );

      traverse_tree( current, pre, inorder, post );
      current = current->next;
    }

    if(post != NULL)
      post( root );
}


/**
 * Get the current state from a node
 *
 * @param node a node
 * @return the current state
 */
 /*char ** getState( TNode * node )
{
    return node->state;
    }*/

/**
 * Set the state of a node
 * 
 * @param node a node
 * @param state the state to set
 */
  /*void setState( TNode ** node, char ** state )
{
    (*node)->state = state;
    }*/


void Build_Tree(int level, char cur_state[][BOARD_SIZE])
{
  //TESTING FOR NOW

  /* create 3 lvls for the initial tree */
  /*first lvl, max's turn, initial state of board */
  create_node(tree_head,cur_state);
  //print_Tree(tree_head);
  traverse_tree(tree_head,print_node,print_node,NULL);
  delete_node(tree_head);
  


}
