
#ifndef _KONANE_H_
#define _KOHANE_H_

#define BOARD_SIZE 8

/* min-max node structure */
typedef struct mm_node{
  short int utility_val;
  short int child_count;
  //char player; 
  //char[2] move;
  struct mm_node *parent;
  struct mm_node *next;
  struct mm_node *child_head;
  char state[BOARD_SIZE][BOARD_SIZE];
} node;

/*** global head pointer used to build min-max tree,
     and tot point to the current state node ***/
extern node *tree_head;
extern node *current_state;

extern node *test_tree_head;

/* 2D char array used to represent current board state */
extern char board[BOARD_SIZE][BOARD_SIZE];

/* function to initialize the board by reading in values from a file */
void _setupboard(char *filename);

int evaluation (char fcolor, char ecolor, char board[][BOARD_SIZE]);

void _playerMove(int x1, int y1, int x2, int y2, char state[][BOARD_SIZE]);


void _MIN_MAX(char state[][BOARD_SIZE]);


/* function builds a test tree using the global tree head node 
   (NOTE: tree has 3 lvls (max, min, terminal) */
void _testTree();
void _createNode(int next, char state[][BOARD_SIZE]);
void _createState(int x, int y1, char new[][BOARD_SIZE], char state[][BOARD_SIZE]);
void _copyBoard(node *n,char state[][BOARD_SIZE]);
void _printTesttree(node *head);
void _cleanTesttree(node *head);


#endif
