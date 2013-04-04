#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<assert.h>
#include"tree.h"
#include"move.h"

/*** global pointer for the tree head, board, and chars for players ***/
extern TNode *tree_head;
extern char board[BOARD_SIZE][BOARD_SIZE];
extern char player;
extern char opponent;

/*** global variable for designated tree depth that is serached and propagated 
     in the MIN_MAX function ***/
int search_depth = 4;

//function reads board in from files and initializes board[][]
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

//function generates random number between 0 and N
int random_child (unsigned int n)
{
  /* seed with each call */
  srand(time(NULL));
  /* produce random number [0,n] */
  return rand() % n;
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
    
    /* set node state */
    copy_state(new_node,state);

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
void delete_tree( TNode * root)
{
    TNode * current;

    /* base case */
    if( root == NULL )
        return;
    
    /* process children */
    current = root->child_head;
    while( current != NULL )
    {
        delete_tree( current );
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

  /* print board */
  printf( "\n" );
  printf( "  | " );
  for( int i = 0; i < BOARD_SIZE; i++ )
      printf( "%d ", i + 1 );
  printf( "\n" );
  printf( "--+" );
  for( int i = 0; i < BOARD_SIZE; i++ )
      printf( "--" );
  printf( "\n" );

  for( int i = 0; i < BOARD_SIZE; i++ )
  {
    //row2letter found in move.c
    printf( "%c | ", row2letter( i ) );
    for( int j = 0; j < BOARD_SIZE; j++ )
        printf( "%c ", n->state[i][j] );
    printf( "\n" );
  }
  printf( "\n" );

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


void determine_children(char friendly, char enemy, TNode *parent)
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
    /* check if adjacent friendly spot is open,
	 if so move piece */
    for(col = 0; (col < BOARD_SIZE) && ((col + 2) < BOARD_SIZE); col++){
	/* change state */
      if( (parent->state[row][col] == friendly)
	 && (parent->state[row][col + 1] == enemy) 
	 && (parent->state[row][col + 2] == 'O')){
	new_node->state[row][col] = 'O';
	new_node->state[row][col + 1] = 'O';
	new_node->state[row][col + 2] = friendly;
      }
    }
    /* check if board has been modified, if so create node */
    if(compare_nodes(new_node,parent) == 1){
      /* create child node */
      create_node(parent,new_node->state);
      /* reset new_node to parent  */
      copy_state(new_node,parent->state);
    }


    /* ----- BACKWARDS ----- */
      /* check if adjacent friendly spot is open,
	 if so move piece */
    for(col = BOARD_SIZE - 1; (col > 0) && ((col - 2) >= 0); col--){
	/*change state */
      if( (parent->state[row][col] == friendly)
	 && (parent->state[row][col - 1] == enemy) 
	 && (parent->state[row][col - 2] == 'O')){
	new_node->state[row][col] = 'O';
	new_node->state[row][col - 1] = 'O';
	new_node->state[row][col - 2] = friendly;
      }
    }
    /* check if board has been modified, if so create node */
    if(compare_nodes(new_node,parent) == 1){
      /* create child node */
      create_node(parent,new_node->state);
      /* reset new_node to parent  */
      copy_state(new_node,parent->state);
    }

  }



  /* ----- VERTICALLY ----- */
  for(col = 0; col < BOARD_SIZE; col++){

    /* ----- FORWARDS ----- */
      /* check if adjacent friendly spot is open,
	 if so move piece */
    for(row = 0; (row < BOARD_SIZE) && ((row + 2) < BOARD_SIZE); row++){
	/* change state */
      if( (parent->state[row][col] == friendly)
	 && (parent->state[row + 1][col] == enemy) 
	 && (parent->state[row + 2][col] == 'O')){
	new_node->state[row][col] = 'O';
	new_node->state[row + 1][col] = 'O';
	new_node->state[row + 2][col] = friendly;
      }
    }
    /* check if board has been modified, if so create node */
    if(compare_nodes(new_node,parent) == 1){
      /* create child node */
      create_node(parent,new_node->state);
      /* reset new_node to parent  */
      copy_state(new_node,parent->state);
    }
    
    /* ----- BACKWARDS ----- */
      /* check if adjacent friendly spot is open,
	 if so move piece */
    for(row = BOARD_SIZE - 1; (row > 0) && ((row - 2) >= 0); row--){
	/*change state */
      if( (parent->state[row][col] == friendly)
	 && (parent->state[row - 1][col] == enemy) 
	 && (parent->state[row - 2][col] == 'O')){
	new_node->state[row][col] = 'O';
	new_node->state[row - 1][col] = 'O';
	new_node->state[row - 2][col] = friendly;
      }
    }
    /* check if board has bveen modified, if so create node */
    if(compare_nodes(new_node,parent) == 1){
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
       if(counter+2<size){
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
     if(count+2<size){
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

  /*HACK: count how many slots open on board (if 0 or 1 then initial state or after first
    move so return false automatically*/
  int slot_count = 0;
  for(int x = 0; x < BOARD_SIZE; x++){
    for(int y = 0; y < BOARD_SIZE; y++){
      if(state[x][y] == 'O'){
	slot_count++;
      }
    }
  }
  
  if(slot_count == 0 || slot_count == 1){
    return 1;
  }

  //else, evaulate the number of move left for the opponent on the board
  int eval = evaluation(current,opponent,state);
  //if(current == 'B'){
    //multiple by -1 if looking for MAX value as will reurn max value less than
    //zero, so multiple by -1 to get positive integer
    //eval *= -1;
  //}
  //else if looking for MIN value, eval will be the closet value to 0
  
  //if terminal state found, return 0 (indicating current won, else return 1)
  if(eval == 0){
    return 0;
  }

  return 1;
}

/*** MIN-MAX ALGORITHM IMPLEMENTATION ***/
void MIN_MAX(char MAX, char MIN, int depth, TNode *node)
{
  //input: current state of the game
 
  //**** TERMINAL TEST ****//
  int eval;
  if((eval = Terminal_Test(MAX,MIN,node->state)) == 0){
    printf("player color: %c Wins!!!\n",MAX);
    exit(EXIT_SUCCESS);
  }

  //create the children for the current state passed
  determine_children(MAX,MIN,node);
  //printf("determining children!!!\n");

  //increment the depth for the next child iteration
  depth++;
  
  //variable for utility value that will be assigned to the parent from the best child
  int parent_utility = node->utility_val;
  
  //***ITERATE THROUGH SUCCESSORS OF CURRENT STATE, RECURSE AND DOES DEPTH FIRST SEARCH (3 levels)
  TNode *child = node->child_head;
  if(child == NULL || depth == search_depth){
    //get utility value for current child node (HEURISTIC: your moves left - opponents moves left)
    parent_utility = evaluation(MIN,MAX,node->state) - evaluation(MAX,MIN,node->state);
    /*** decrement thr depth to the previous level in the tree ***/
    depth--;
  }
  else{
    while(child != NULL){
      
      MIN_MAX(MAX,MIN,depth,child);
   
      //get utility value for current child node (HEURISTIC: your moves left - opponents moves left)
      child->utility_val = evaluation(MIN,MAX,child->state) - evaluation(MAX,MIN,child->state);
      
      /*** determine where a MIN or MAX node level for the tree
	   (If Max, wont be depth not divisible by 2) ***/
      if((depth % 2) == 0){
	//MIN NODE: reset utility of parent based on lower child values
	if(child->utility_val < parent_utility){
	  parent_utility = child->utility_val;
	}
      }
      else{
	//MAX NODE: reset utility of parent based on higher child values      
	if(child->utility_val > parent_utility){
	  parent_utility = child->utility_val;
	}
      }
      
      child = child->next;
    }
  }

  //set utility value of parent before return
  node->utility_val = parent_utility;
  printf("parent util: %d\n",node->utility_val);
  return;
  
}


void MAKE_DECISION(char player, char opponent, int depth, char current_state[][BOARD_SIZE])
{
  // *** ASSUMES tree_head is already allocated and is a node (done in main.c)

  /* variable  to add possible next states to as children chosen by agent */
  TNode *temp_head = (TNode *)malloc( sizeof( TNode ) );
  assert( temp_head != NULL );
  memset(temp_head,0,sizeof( TNode ) );
  
  //call function to build tree (MIN_MAX) (propagates all values up tree)
  MIN_MAX(player,opponent,depth,tree_head);

  //get utility value propagated up to tree_head
  int head_utility = tree_head->utility_val;
  printf("parent util: %d\n",head_utility);
  //iterate through immediate children of tree_head, finding matching utility values
  TNode *child = tree_head->child_head;
  int child_count = 0;
  while(child != NULL){
    //if child determined to have th same utility value as the parent, create a temporary
    //node for it and attach it to the temporary head and add to the child count
    if(child->utility_val == head_utility){
      create_node(temp_head,child->state);
      child_count++;
    }
    printf("child util %d\n",child->utility_val);
    //print_node(child);
    child = child->next;
  }

  
  //delete tree for current state
  delete_tree(tree_head);
  

  //generate a random number between 0 and child_count
  int decision = random_child(child_count); 

  printf("child count: %d --- random: %d\n",child_count,decision);

  //iterate through the possible children states that may be chosen by the agent, until child position
  //matches the random number produced
  child = temp_head->child_head;
  int index = 0;
  while(child != NULL){
    //***if index of child in linked list matches random number, 
    //***create a tree node for that state that has been decided upon by the agent
    if(index == decision){
      create_node(tree_head,child->state);
      break;
    }
    index++;
    child = child->next;
  }

  //clean up memory
  delete_tree(temp_head);

}



void Build_Tree(int level, char cur_state[][BOARD_SIZE])
{
  //TESTING FOR NOW
  char agent = 'W';
  char player = 'B';

  /*create head node */
  create_node(tree_head,cur_state);
  
  //testing for a given state
  /*tree_head->state[1][1] = 'O';
  tree_head->state[2][1] = 'O';
  tree_head->state[3][0] = 'O';
  tree_head->state[3][1] = 'O';
  */
  
  tree_head->state[3][3] = 'O';

  printf("TEST NODE:\n");
  print_node(tree_head);

  printf("agents moves left: %d\n",evaluation(player,agent,tree_head->state));
  printf("players moves left: %d\n",evaluation(agent,player,tree_head->state));
  
  //determine_children(agent,player,tree_head);

  MIN_MAX(agent,player,1,tree_head);

  //MAKE_DECISION(agent,player,1,tree_head->state);

  traverse_tree(tree_head,print_node,NULL,NULL);
  delete_tree(tree_head);
  
}
