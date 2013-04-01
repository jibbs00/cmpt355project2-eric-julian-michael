
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

/* function to get random number to pick children that have the same utility
   value when an agent makes a decision */
int random_child (unsigned int n);

/* functions to create, delete, and manipulate tree structure */
void copy_state(TNode *node, char state[][BOARD_SIZE]);
void create_node(TNode * parent, char state[][BOARD_SIZE]);
void delete_tree( TNode * root);
void print_node(TNode * n);
void traverse_tree( TNode * root, void (*pre)( TNode * n ), void (*inorder)( TNode * n ), void (*post)( TNode * n ) );

/* evaluation/heuristic and terminal test */
int evaluation (char fcolor, char ecolor, char board[][BOARD_SIZE]);
int Terminal_Test(char current, char opponent, char state[][BOARD_SIZE]);

/* function creates all children states for a possible current one */
void determine_children(char friendly, char enemy, TNode *parent);

/*** in max implementation recurses a tree, propagating values up the tree, to get
     the next move with the best utility value ***/
void MIN_MAX(char MAX, char MIN, TNode *node);

/*** function applies a move calculated from MAX_VALUE ***/
void MAKE_DECISION(char player, char opponent, char current_state[][BOARD_SIZE]);


//function for testing
void Build_Tree(int level, char cur_state[][BOARD_SIZE]);

#endif /* _TREE_H_ */
