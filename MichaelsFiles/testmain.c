#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<pthread.h>
#include<sys/time.h>
#include<unistd.h>
#include"tree.h"
#include"timer.h"

#define BUF_SIZE 20

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

  /*pthread_t thread;

  int req;
  req = pthread_create(&thread,NULL,timer,NULL);
  if(req != 0){
    printf("fuck\n");
    exit(EXIT_FAILURE);
    }*/
  
  Build_Tree(0,board);

  return 0;
  //pthread_exit(0);
}

