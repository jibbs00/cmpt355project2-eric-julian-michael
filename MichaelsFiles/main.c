#include<stdio.h>
#include<stdlib.h>
#include"func.h"

int main(int argc, char *argv[])
{
  if(argv[1] != NULL){
    _setupboard(argv[1]);
  }
  else{
    printf("forgot the input file name!\n");
  }

  _testTree();

  return 0;
}
