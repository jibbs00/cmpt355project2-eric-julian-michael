#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include"tree.h"

/*** global pointers for the tree head ***/
TNode *tree_head = NULL;

extern char board[BOARD_SIZE][BOARD_SIZE];
extern char player;
extern char opponent;


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


void copy_state(TNode *node, char state[][BOARD_SIZE])
{
  /* function copies one board state to another */
  for(int x = 0; x < BOARD_SIZE; x++){
    for(int y = 0; y < BOARD_SIZE; y++){
      node->state[x][y] = state[x][y];
    }
  }
}

int compare_nodes(TNode *a, TNode *b)
{
  /* return 1 if different, 0 if the same */
  for(int x = 0; x < BOARD_SIZE; x++){
    for(int y = 0; y < BOARD_SIZE; y++){
      if(a->state[x][y] != b->state[x][y]){
	return 1;
      }
    }
  }
  return 0;
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
  printf("\n");

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


void determine_children(TNode *parent, char friendly, char enemy)
{
  int row, col;
  
  //***testing
  TNode *new_node = malloc(sizeof(TNode));
  assert( new_node != NULL );
  memset(new_node,0,sizeof(TNode));
  
  //TESTING TO SEE IF AFTER FIRST MOVE STATE (only one spot free on baord)
  int slot_count = 0;
  int pos_x, pos_y;
  for(row = 0; row < BOARD_SIZE; row++){
    for(col = 0; col < BOARD_SIZE; col++){
      if(parent->state[row][col] == 'O'){
	slot_count++;
	pos_x = row;
	pos_y = col;
      }
    }
  }
  
  //if only one open slot, must be first move for agent so choose all
  //adjacent slots to the open one as possible states
  if(slot_count == 1){
    /* above slot */
    if( (pos_x - 1) >= 0){
        /* copy state over to head node */
	copy_state(new_node,parent->state);
	/* change state */
	new_node->state[pos_x - 1][pos_y] = 'O';
	/* create child node */
	create_node(parent,new_node->state);
    }
    /* below slot */
    if( (pos_x + 1) < BOARD_SIZE){
        /* copy state over to head node */
        copy_state(new_node,parent->state);
	/* change state */
	new_node->state[pos_x + 1][pos_y] = 'O';
	/* create child node */
	create_node(parent,new_node->state);
    }
    /* left of slot */
    if( (pos_y - 1) >= 0){
          /* copy state over to head node */
	copy_state(new_node,parent->state);
	/* change state */
	new_node->state[pos_x][pos_y - 1] = 'O';
	/* create child node */
	create_node(parent,new_node->state);
    }
    /* right of slot */
    if( (pos_y + 1) < BOARD_SIZE){
        /* copy state over to head node */
	copy_state(new_node,parent->state);
	/* change state */
	new_node->state[pos_x][pos_y + 1] = 'O';
	/* create child node */
	create_node(parent,new_node->state);
    }
    //return, dont evaluate further
    return;
  }


  //else, evaluate for typical board state

  /*** copy state from parent node to new_node ***/
  copy_state(new_node,parent->state);

  /* ----- HORIZONTAL ----- */
  for(row = 0; row < BOARD_SIZE; row++){

    /* ----- FORWARDS ----- */
    /* based on friendly, decide what col index to start from */
    if(parent->state[row][0] == friendly)
      col = 0;
    else
      col = 1;

    /* check if adjacent friendly spot is open,
	 if so move piece */
    for(; (col < BOARD_SIZE) 
	  && ((col + 2) < BOARD_SIZE)
	  && (parent->state[row][col + 1] == enemy)
	  && (parent->state[row][col + 2] == 'O'); col += 2){
	/* change state */
	new_node->state[row][col] = 'O';
	new_node->state[row][col + 1] = 'O';
	new_node->state[row][col + 2] = friendly;
    }
    /* check if board has been modified, if so create node */
    if(compare_nodes(new_node,parent)){
      /* create child node */
      create_node(parent,new_node->state);
      /* reset new_node to parent  */
      copy_state(new_node,parent->state);
    }


    /* ----- BACKWARDS ----- */
    /* based on friendly, decide what col index to start from */
    if(parent->state[row][BOARD_SIZE - 1] == friendly)
      col = BOARD_SIZE - 1;
    else
      col = BOARD_SIZE - 2;

      /* check if adjacent friendly spot is open,
	 if so move piece */
    for(; (col > 0)
	  && ((col - 2) >= 0)
	  && (parent->state[row][col - 1] == enemy)
	  && (parent->state[row][col - 2] == 'O') ; col -= 2){
	/*change state */
	new_node->state[row][col] = 'O';
	new_node->state[row][col - 1] = 'O';
	new_node->state[row][col - 2] = friendly;
    }
    /* check if board has been modified, if so create node */
    if(compare_nodes(new_node,parent)){
      /* create child node */
      create_node(parent,new_node->state);
      /* reset new_node to parent  */
      copy_state(new_node,parent->state);
    }

  }



  /* ----- VERTICALLY ----- */
  for(col = 0; col < BOARD_SIZE; col++){

    /* ----- FORWARDS ----- */
    /* based on friendly, decide what col index to start from */
    if(parent->state[0][col] == friendly)
      row = 0;
    else
      row = 1;

      /* check if adjacent friendly spot is open,
	 if so move piece */
    for(; (row < BOARD_SIZE)
	  && ((row + 2) < BOARD_SIZE)
	  && (parent->state[row + 1][col] == enemy)
	  && (parent->state[row + 2][col] == 'O'); row += 2){
	/* change state */
	new_node->state[row][col] = 'O';
	new_node->state[row + 1][col] = 'O';
	new_node->state[row + 2][col] = friendly;
    }
    /* check if board has been modified, if so create node */
    if(compare_nodes(new_node,parent)){
      /* create child node */
      create_node(parent,new_node->state);
      /* reset new_node to parent  */
      copy_state(new_node,parent->state);
    }

    /* ----- BACKWARDS ----- */
    /* based on friendly, decide what col index to start from */
    if(parent->state[BOARD_SIZE - 1][col] == friendly)
      row = BOARD_SIZE - 1;
    else
      row = BOARD_SIZE - 2;

      /* check if adjacent friendly spot is open,
	 if so move piece */
    for(; (row > 0) 
	  && ((row - 2) >= 0)
	  && (parent->state[row - 1][col] == enemy)
	  && (parent->state[row - 2][col] == 'O'); row -= 2){
	/*change state */
	new_node->state[row][col] = 'O';
	new_node->state[row - 1][col] = 'O';
	new_node->state[row - 2][col] = friendly;
    }
    /* check if board has been modified, if so create node */
    if(compare_nodes(new_node,parent)){
      /* create child node */
      create_node(parent,new_node->state);
      /* reset new_node to parent  */
      copy_state(new_node,parent->state);
    }

    
  }

  free(new_node);
}


//will evaluate the board and return a number based on the
//number of moves an enemy has
int evaluation (char fcolor, char ecolor, char board[][BOARD_SIZE]) {
  int count = 0, counter = 0;
  int size=BOARD_SIZE;
  int tc=0;
   
 //goes through the board horizontally
 while(count<size){
     while(counter<size){
       if(counter+2<=size){
	 if((ecolor==board[count][counter])
	    && (fcolor==board[count][counter+1])
	    && (board[count][counter+2]=='O'))
	   { 
	     tc=tc+1; 
	   }
       }
       if(counter-2>=0){
	 if((ecolor==board[count][counter])
	    && (fcolor==board[count][counter-1])
	    && (board[count][counter-2]=='O')) 
	   {
	     tc=tc+1;
	   }
       }
       //printf("count: %d counter: %d\n",count,counter);
       counter++;
     }
     counter=0;
    count++;
 }

 count=0;
 counter=0;
 //goes through the board vertically
 while(counter<size){
   while(count<size){
     if(count+2<=size){
       if((ecolor==board[count][counter])
	  && (fcolor==board[count+1][counter])
	  && (board[count+2][counter]=='O'))
	 {
	   tc=tc+1;
	 }
     }
     if(count-2>=0){
       if((ecolor==board[count][counter])
	  && (fcolor==board[count-1][counter])
	  && (board[count-2][counter]=='O'))
	 {
	   tc=tc+1;
	 }
     }

     //printf("count: %d counter: %d\n",count,counter);
     count++;
   }
   count=0;
   counter++;
 }
 
 return tc;
}


int Terminal_Test(char current, char opponent, char state[][BOARD_SIZE])
{
  //function determines the number of moves left, if 0, calculate the 
  //the number of moves left and test whether its a terminal state

  int eval = evaluation(current,opponent,state);
  if(current == 'B'){
    //multiple by -1 if looking for MAX value as will reurn max value less than
    //zero, so multiple by -1 to get positive integer
    eval *= -1;
  }
  //else if looking for MIN value, eval will be the closet value to 0
  
  //if terminal state found, return 0 (indicating current won, else return 1)
  if(eval == 0){
    return 0;
  }

  return 1;
}

/*** MIN-MAX ALGORITHM IMPLEMENTATION ***/
void MAX_VALUE(TNode *node)
{
  //input: current state of the game
  
  char MAX = 'B';
  char MIN = 'W';
 
  //**** TERMINAL TEST ****//
  int eval;
  if((eval = Terminal_Test(MAX,MIN,node->state)) == 0){
    printf("you've won Black!!!\n");
    //return;
  }
  /******************************************************************/

  //create the children for the current state passed
  determine_children(node,MAX,MIN);
    
  //variable for utility value that will be assigned to the parent from the best child
  int parent_utility = node->utility_val;
  
  //***ITERATE THROUGH SUCCESSORS OF CURRENT STATE, RECURSE AND DOES DEPTH FIRST SEARCH (3 levels)
  TNode *child = node->child_head;
  if(child == NULL){
    //get utility value for current child node (HEURISTIC: your moves left - opponents moves left)
    parent_utility = evaluation(MIN,MAX,node->state) - evaluation(MAX,MIN,node->state);
  }
  else{
    while(child != NULL){

      MAX_VALUE(child);
    
      //get utility value for current child node (HEURISTIC: your moves left - opponents moves left)
      child->utility_val = evaluation(MIN,MAX,child->state) - evaluation(MAX,MIN,child->state);
      
      //reset utility of parent based on higher child values
      if(child->utility_val > parent_utility){
	parent_utility = child->utility_val;
      }

      child = child->next;
    }
  }

  //set utility value of parent before return
  node->utility_val = parent_utility;

  return;
  
}


void Build_Tree(int level, char cur_state[][BOARD_SIZE])
{
  //TESTING FOR NOW

  /*create head node */
  create_node(tree_head,cur_state);
  //make first move (user made)
  tree_head->state[3][3] = 'O';
  
  //testing for a given state
  /*tree_head->state[1][3] = 'O';
  tree_head->state[3][3] = 'O';
  tree_head->state[2][3] = 'O';
  tree_head->state[5][3] = 'O';
  tree_head->state[5][5] = 'O';
  tree_head->state[5][7] = 'O';
  //determine_children(tree_head,'B','W');

  tree_head->utility_val = evaluation('B','W',tree_head->state);
  print_node(tree_head);
  */

  MAX_VALUE(tree_head);

  traverse_tree(tree_head,print_node,NULL,NULL);
  delete_node(tree_head);
  
}

void MAKE_DECISION(char player, char opponent, char current_state[][BOARD_SIZE])
{
  //input: player and agent characters, current game state
  //ASSUMES tree_head is already allocated and is a node (done in main.c)

  //call function to build tree (MIN_MAX) (propagates all values up tree)
  MAX_VALUE(tree_head);

  //get utility value propagated up to tree_head
  int utility = tree_head->utility_val;

  //iterate through immediate children of tree_head, finding matching utility values
  TNode *child = tree_head->child_head;
  while(child != NULL){
    //if childs utility values matches tree_head 
    if(child->utility_val == utility){
      
    }
  }

  
  //create a tree node for the state that has been decided by the agent to be carried out
  create_node(tree_head,current_state);


}
