#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<ctype.h>
#include"tree.h"
#include"move.h"

#define BUF_SIZE 20

//function applies a users move to a node states
/*NOTE: didnt know where to put function */
void apply_move(struct Move *move, char player, TNode *node);

/*** global variables used to build tree, represent board, and players ***/
TNode * tree_head = NULL;
char board[BOARD_SIZE][BOARD_SIZE];
char player, opponent; //opponent state is agent

/***** MAIN *****
*****************/
int main(int argc, char *argv[])
{
  //read in filename, set up board
  if(argv[1] != NULL){
    _setupboard(argv[1]);
  }
  else{
    printf("forgot the input file name!\n");
    return 1;
  }
  
  /* prompt user to pick player color and set up opponent color */
  printf("Choose a color (B or W): ");
  scanf(" %c",&player); //space to ignore whitepsace or newline in stdin
  player = toupper(player);
  while(player != 'B' && player != 'W'){
    printf("Choose a color: (B)  (W)\n:");
    scanf(" %c",&player); //space to ignore whitepsace or newline in stdin
    player = toupper(player);
  }
  
  if(player == 'B')
    opponent = 'W';
  else
    opponent = 'B';
  
  //*** flush input buffer stdin
  char ch;
  while ((ch = getchar()) != '\n' && ch != EOF);

  /*** create initial board node for first tree using board ***/
  create_node(tree_head,board);
  
  /*** print intial board - for testing ***/
  printf(" ----- INITIAL BOARD -----\n");
  print_node(tree_head);

  /*** Move struct used to translater players moves read in ***/
  struct Move *players_move;

  /* loop, prompting the user to make a move, and have a the agent
     responding with a move (plays the game) */
  char input_buffer[BUF_SIZE] = {0};
  while(1){
    /* read in user move and translate */
    printf("enter a valid move: ");
    fgets(input_buffer,BUF_SIZE,stdin);
    while(input_buffer[0] == '\n'){
      printf("enter a valid move: ");
      fgets(input_buffer,BUF_SIZE,stdin);
    }
    //remove newline from end of buffer
    if (input_buffer[strlen(input_buffer) - 1] == '\n')
      input_buffer[strlen(input_buffer) - 1] = '\0';

    /* translate move into a structure of 4 points (string to move struct)*/
    players_move = translate_in_move(input_buffer);

    /*call function to apply players move */
    apply_move(players_move,player,tree_head);

    /* print players move */
    printf(" ----- YOUR MOVE -----\n");
    print_node(tree_head);

    /*** call agent decision function to make a move ***/
    //NOTE: switched player and opponent in function parameters
    //as in the agents eyes the user is the opponent
    MAKE_DECISION(opponent,player,1,tree_head->state);

    //print agents move
    printf(" ----- AGENTS MOVE -----\n");
    print_node(tree_head);

    //free players move before next iteration
    free(players_move);
    //break;
  }

  //memory clean up
  delete_tree(tree_head);

  return 0;
}



//function applies a users move to a node states
void apply_move(struct Move *move, char player, TNode *node)
{
  //ASSUMES USER MAKES VALID MOVE
  //NOTE: ACCOUNT FOR ARRAY - 1 FROM ACTUAL MOVE (IE IF WANT A1 - A3, TYPE IN A0 - A2)
  /* apply move */

  /* first move state */
  if(move->start_row == move->end_row
     && move->start_col == move->end_col){
    node->state[move->start_row][move->start_col] = 'O';
    node->state[move->end_row][move->end_col] = 'O';
    return;
  }
  /* forwards horzontally */
  if(move->start_row == move->end_row
     && move->start_col < move->end_col){
    for(int x = move->start_col; x <= move->end_col; x++){
      node->state[move->start_row][x] = 'O';
    }    
  }
  /* backwards horizontally */
  if(move->start_row == move->end_row
     && move->start_col > move->end_col){
    for(int x = move->start_col; x >= move->end_col; x--){
      node->state[move->start_row][x] = 'O';
    }    
  }
  /* forwards vertically */
  if(move->start_col == move->end_col
     && move->start_row < move->end_row){
    for(int x = move->start_row; x <= move->end_row; x++){
      node->state[x][move->start_col] = 'O';
    }    
  }
  /* backwards vertically */
  if(move->start_col == move->end_col
     && move->start_row > move->end_row){
    for(int x = move->start_row; x >= move->end_row; x--){
      node->state[x][move->start_col] = 'O';
    }    
  }
  
  /* after apply non zero changes  if not first move state */
  node->state[move->start_row][move->start_col] = 'O';
  node->state[move->end_row][move->end_col] = player;

}
