#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"func.h"

node *test_tree_head = NULL;
node *tree_head = NULL;
node *current_state = NULL;

char board[BOARD_SIZE][BOARD_SIZE];

void _setupboard(char *filename)
{
  FILE *fh = fopen(filename,"r");
  if(fh == NULL){
    printf("could not open file %s\n",filename);
    exit(EXIT_FAILURE);
  }

  char c;
  int x = 0, y = 0;
  while((c = fgetc(fh)) != EOF){
    if(c == '\n'){
      x++;
      y = 0;
      continue;
    }
    board[x][y] = c;
    y++;
  }
  
  /*print initial board */
  printf(" ---------- INITIAL STATE ---------- \n");
  for(int x = 0; x < 8; x++){
    for(int y = 0; y < 8; y++){
      printf("%c",board[x][y]);
    }
    printf("\n");
  }
  
  fclose(fh);
}


void _testTree()
{
  /* create 3 lvls for the initial tree */
  /*first lvl, max's turn, initial state of board */
  _createNode(board); //create initial node for test_tree_head, current state = head at this point

  /*second lvl, min's turn, 4 states */
  /*(top left corner, (4,4), (5,5), bottom right corner) */
  char new_state[BOARD_SIZE][BOARD_SIZE];
  
  /*NOTE: x - 1, and y - 1 as array range from 0 -7, not 1 - 8 */

  /* top left corner */
  _createState(0,0,new_state,current_state->state);
  _createNode(new_state);
  /* (4,4) */
  _createState(3,3,new_state,current_state->state);
  _createNode(new_state);
  /* (5,5) */
  _createState(4,4,new_state,current_state->state);
  _createNode(new_state);
  /* bottom right corner */
  _createState(7,7,new_state,current_state->state);
  _createNode(new_state);
  
  /*thrid lvl, middle states have 4 children each, corners have 2 */
  /*NOTE: current state should not point to child_head of top left corner node */
  current_state = current_state->child_head; //reset current state
  
  /*NOTE: x - 1, and y - 1 as array range from 0 -7, not 1 - 8 */

  /* top left corner children = (1,3), (3,1) */
  _createState(0,2,new_state,current_state->state);
  _createNode(new_state);
  _createState(2,0,new_state,current_state->state);
  _createNode(new_state);
  /* (4,4) = (2,4), (4,2), (6,4), (4,6)*/
  _createState(1,3,new_state,current_state->next->state);
  _createNode(new_state);
  _createState(3,1,new_state,current_state->next->state);
  _createNode(new_state);
  _createState(5,3,new_state,current_state->next->state);
  _createNode(new_state);
  _createState(3,5,new_state,current_state->next->state);
  _createNode(new_state);
  /* (5,5) = (3,5), (5,3), (5,7), (7,5) */
  _createState(2,4,new_state,current_state->next->next->state);
  _createNode(new_state);
  _createState(4,2,new_state,current_state->next->next->state);
  _createNode(new_state);
  _createState(4,6,new_state,current_state->next->next->state);
  _createNode(new_state);
  _createState(6,4,new_state,current_state->next->next->state);
  _createNode(new_state);
  /* bottom right corner = (8,6), (6,8) */
  _createState(7,5,new_state,current_state->next->next->next->state);
  _createNode(new_state);
  _createState(5,7,new_state,current_state->next->next->next->state);
  _createNode(new_state);
  

  /* print tree and clean up memory */
  _printTesttree(test_tree_head);
  _cleanTesttree(test_tree_head);

}

void _createNode(char state[][BOARD_SIZE])
{
  /* function creates a new board and sets the fields */
  node *new_node = malloc(sizeof(node));
  if(new_node == NULL){
    printf("malloc fail: _createNode\n");
    exit(EXIT_FAILURE);
  }
   memset(new_node,0,sizeof(node));
  /* copy state over to head node */
  _copyBoard(new_node,state);

  if(test_tree_head == NULL){
    new_node->parent = NULL;
    new_node->next = NULL;
    new_node->child_head = NULL;
    test_tree_head = new_node;
    current_state = test_tree_head;
  }
  else{
    new_node->parent = current_state;
    /*add as child to parent node */
    node *prev = current_state->child_head;
    if(prev != NULL){
      node *cur = prev->next;
      for(;(prev != NULL && cur != NULL);prev = prev->next, cur = cur->next);
      prev->next = new_node;
      printf("fuck\n");
    }
    else{
      current_state->child_head = new_node;
    }
    new_node->next = NULL;
    
  }
  
 
}

void _createState(int x, int y, char new[][BOARD_SIZE], char state[][BOARD_SIZE])
{
  for(int i = 0; i < BOARD_SIZE; i++){
    for(int j = 0; j < BOARD_SIZE; j++){
      new[i][j] = state[i][j];
    }
  }
  
  new[x][y] = '0';
}

void _copyBoard(node *n, char state[][BOARD_SIZE])
{
  /* function copies one board state to another */
  for(int x = 0; x < BOARD_SIZE; x++){
    for(int y = 0; y < BOARD_SIZE; y++){
      n->state[x][y] = state[x][y];
    }
  }

}


void _printTesttree(node *head)
{
  node *itr = head;
  int lvl = 0;

  /*iterate through tree, from level to level, printing out
    states and depth levels, and utility values */
  while(itr != NULL){
      printf(" ---------- LEVEL %d ---------- \n",lvl);
      printf(" UTILITY VAL: %d\n",head->utility_val);
      printf(" STATE:\n");
      for(int x = 0; x < BOARD_SIZE; x++){
	for(int y = 0; y < BOARD_SIZE; y++){
	  printf("%c",itr->state[x][y]);
	}
	printf("\n");
      }

      /* iterate through siblings in same level if not next */
      if(itr->next != NULL){
	itr = itr->next;
      }
      /* else, go to nodes child head and iterate, change depth level */
      else{
	/* if end of sibling linked list, go to parent, go to the parents first
	   child, and then set itr as that childs child list (goes to start of
	   netx level) */
	if(itr->parent != NULL){
	  itr = itr->parent->child_head->child_head;
	}
	else{
	  itr = itr->child_head;
	}
	/*increment level value */
	lvl++;
      }
  }
}

void _cleanTesttree(node *head)
{
  node *del = head;

  /*iterate through tree, from level to level, deleting nodes */
  while(del != NULL){
      node *temp = del;
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

      free(temp);

  }

}
