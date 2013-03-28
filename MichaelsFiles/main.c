#include<stdio.h>
#include<stdlib.h>
#include"func.h"
#include"tree.h"

char board[BOARD_SIZE][BOARD_SIZE];

int main(int argc, char *argv[])
{
  if(argv[1] != NULL){
    _setupboard(argv[1]);
  }
  else{
    printf("forgot the input file name!\n");
  }

  //_testTree();
  Build_Tree(0,board);


  return 0;
}
