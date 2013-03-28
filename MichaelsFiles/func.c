#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"func.h"
#include"tree.h"

extern TNode *tree_head;
node *current_state;
node *test_tree_head = NULL;

extern char board[BOARD_SIZE][BOARD_SIZE];

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
  
  fclose(fh);
}


void _testTree()
{
  // create 3 lvls for the initial tree
  //first lvl, max's turn, initial state of board
  _createNode(0,board); //create initial node for test_tree_head, current state = head at this point
  
  //second lvl, min's turn, 4 states
  //(top left corner, (4,4), (5,5), bottom right corner)
  char new_state[BOARD_SIZE][BOARD_SIZE];
  
  /*NOTE: x - 1, and y - 1 as array range from 0 -7, not 1 - 8 */

  /* top left corner */
  _createState(0,0,new_state,current_state->state);
  _createNode(0,new_state);
  /* (4,4) */
  _createState(3,3,new_state,current_state->state);
  _createNode(0,new_state);
  /* (5,5) */
  _createState(4,4,new_state,current_state->state);
  _createNode(0,new_state);
  /* bottom right corner */
  _createState(7,7,new_state,current_state->state);
  _createNode(0,new_state);
  
  /*third lvl, middle states have 4 children each, corners have 2 */
  /*NOTE: current state should point to child_head of top left corner node */
  current_state = current_state->child_head; //reset current state to firsts lvl's child_head
  
  /*NOTE: x - 1, and y - 1 as array range from 0 -7, not 1 - 8 */

  /* top left corner children = (1,2), (2,1) */
  _createState(0,1,new_state,current_state->state);
  _playerMove(0,0,0,1,new_state); //zero all slots between moves
  _createNode(0,new_state);
  _createState(1,0,new_state,current_state->state);
  _playerMove(0,0,1,0,new_state); //zero all slots between moves
  _createNode(0,new_state);

  /* (4,4) = (3,4), (4,3), (5,4), (4,5)*/
  _createState(2,3,new_state,current_state->next->state); //skip to next as current_state not reset
  _playerMove(3,3,2,3,new_state); //zero all slots between moves
  _createNode(1, new_state);  //reset current_state to next parent
  _createState(3,2,new_state,current_state->state);
  _playerMove(3,3,3,2,new_state); //zero all slots between moves
  _createNode(0,new_state);
  _createState(4,3,new_state,current_state->state);
  _playerMove(3,3,4,3,new_state); //zero all slots between moves
  _createNode(0,new_state);
  _createState(3,4,new_state,current_state->state);
  _playerMove(3,3,3,4,new_state); //zero all slots between moves
  _createNode(0,new_state);

  /* (5,5) = (4,5), (5,4), (5,6), (6,5) */
  _createState(3,4,new_state,current_state->next->state); //skip to next as current_state not reset
  _playerMove(4,4,3,4,new_state); //zero all slots between moves
  _createNode(1, new_state); //reset current-state to next parent
  _createState(4,3,new_state,current_state->state);
  _playerMove(4,4,4,3,new_state); //zero all slots between moves
  _createNode(0,new_state);
  _createState(4,5,new_state,current_state->state);
  _playerMove(4,4,4,5,new_state); //zero all slots between moves
  _createNode(0,new_state);
  _createState(5,4,new_state,current_state->state);
  _playerMove(4,4,5,4,new_state); //zero all slots between moves
  _createNode(0,new_state);

  /* bottom right corner = (8,7), (7,8) */
  _createState(7,6,new_state,current_state->next->state); //skip to next as current_state not reset
  _playerMove(7,7,7,6,new_state); //zero all slots between moves
  _createNode(1, new_state); //reset current-state to next parent
  _createState(6,7,new_state,current_state->state);
  _playerMove(7,7,6,7,new_state); //zero all slots between moves
  _createNode(0,new_state);

  // print tree and clean up memory
  _printTesttree(test_tree_head);
  _cleanTesttree(test_tree_head);

}

void _createNode(int next, char state[][BOARD_SIZE])
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
    
    /*add as child to parent node */
    node *prev = current_state->child_head;
    if(prev != NULL){
      node *cur = prev->next;
      for(;(cur != NULL);prev = prev->next, cur = cur->next);
      prev->next = new_node;
    }
    else{
      current_state->child_head = new_node;
    }

    /* stupid hack to connect child nodes to the proper parent, and 
       set the parents child_list */
    if(next == 1){
      //reset current_state to next node in parent list
      current_state = current_state->next;
      //set current_state child head to previous (to connect all children among parent list
      current_state->child_head = new_node;
    }

    new_node->parent = current_state;  
    new_node->next = NULL;
    new_node->child_head = NULL;
  }
   
}

void _createState(int x1, int y1, char new[][BOARD_SIZE], char state[][BOARD_SIZE])
{
  for(int i = 0; i < BOARD_SIZE; i++){
    for(int j = 0; j < BOARD_SIZE; j++){
      new[i][j] = state[i][j];
    }
  }
  
  new[x1][y1] = 'O';
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


void _printState(node *n)
{
  for(int x = 0; x < BOARD_SIZE; x++){
    for(int y = 0; y < BOARD_SIZE; y++){
      printf("%c",n->state[x][y]);
    }
    printf("\n");
  }
  printf("\n");
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

/* ---------------------------------------------------------------------------------------- */

void _playerMove(int x1, int y1, int x2, int y2, char state[][BOARD_SIZE]){
  /*function finds an empty point, and determines if there
    is another mepty point on the same horizontal or vertical line,
    and then empties all the slots between theose two ponts (gets correct state)*/

  if(x1 == x2 && y1 < y2){
    /* loop from (x1,y1) right on the same row */
    for(; y1 <= y2; y1++)
      state[x1][y1] = 'O';
  }
  else if(x1 == x2 && y1 > y2){
    for(; y1 >= y2; y1--)
      state[x1][y1] = 'O';
  }
  else if(y1 == y1 && x1 < x2){
    for(; x1 <= x2; x1++)
      state[x1][y1] = 'O';
  }
  else if( y1 == y2 && x1 > x2){
    for(; x1 >= x2; x1--)
      state[x1][y1] = 'O';
  }

}
