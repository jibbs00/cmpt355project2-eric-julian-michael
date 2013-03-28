#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"tree.h"

char board[BOARD_SIZE][BOARD_SIZE];
char player, opponent;


int main(int argc, char *argv[])
{
  if(argv[1] != NULL){
    _setupboard(argv[1]);
  }
  else{
    printf("forgot the input file name!\n");
  }
  
  /* prompt user to pick player color */
  printf("Choose a color: (B)  (W)\n:");
  player = getc(stdin);
  player = toupper(player);
  while(player != 'B' && player != 'W'){
    printf("Choose a color: (B)  (W)\n:");
    player = getc(stdin);
    player = toupper(player);
  }
  if(player == 'B')
    opponent = 'W';
  else
    opponent = 'B';
    

  //Build_Tree(0,board);


  return 0;
}
