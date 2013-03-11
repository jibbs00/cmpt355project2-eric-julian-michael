#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"func.h"

char board[8][8];

void _setupboard(char *filename)
{
  FILE *fh = fopen(filename,"r");
  if(fh == NULL){
    printf("could not open file %s\n",filename);
    exit(EXIT_FAILURE);
  }

  //char buf[9] = {0};
  char c;
  int x = 0, y = 0;
  while((c = fgetc(fh)) != EOF){
    if(c == '\n'){
      x++;
      y = 0;
    }
    board[x][y] = c;
    y++;
    //strcpy(board[index][],str);
  }
  

  for(int x = 0; x < 8; x++){
    for(int y = 0; y < 8; y++){
      printf("%c",board[x][y]);
    }
    printf("\n");
  }

  fclose(fh);
}


