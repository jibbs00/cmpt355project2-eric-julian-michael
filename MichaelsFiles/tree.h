
#ifndef _TREE_H_
#define _TREE_H_

#define TREE_DEPTH 3
#define BOARD_SIZE 8

typedef struct _tnode {
  short int utility_val;
  short int child_count;
  struct _tnode * parent; /**< parent node */
  struct _tnode * next;
  struct _tnode * child_head;  /**< list of children */
  //char ** state;          /**< current state */
  char state[BOARD_SIZE][BOARD_SIZE];
} TNode;

/*** global head pointer used to build min-max tree,
     and tot point to the current state node ***/
extern TNode *tree_head;

/* 2D char array used to represent current board state */
extern char board[BOARD_SIZE][BOARD_SIZE];

/* global char values for the player, and subsequent opponent colors */
extern char player;
extern char opponent;


/* function to initialize the board by reading in values from a file */
void _setupboard(char *filename);

void copy_state(TNode *node, char state[][BOARD_SIZE]);
void create_node(TNode * parent, char state[][BOARD_SIZE]);
void delete_node( TNode * root);
void print_node(TNode * n);
void traverse_tree( TNode * root, void (*pre)( TNode * n ), void (*inorder)( TNode * n ), void (*post)( TNode * n ) );

int evaluation (char fcolor, char ecolor, char board[][BOARD_SIZE]);
int Terminal_Test(char current, char opponent, char state[][BOARD_SIZE]);

void determine_children(TNode *parent, char friendly, char enemy);

void MAX_VALUE(TNode *node);

//function for testing
void Build_Tree(int level, char cur_state[][BOARD_SIZE]);

void MAKE_DECISION(char player, char opponent, char current_state[][BOARD_SIZE]);


#endif /* _TREE_H_ */
