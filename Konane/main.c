#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main( int argc, char * argv[] )
{
  if(argv[1] != NULL){
    game(argv[1]);
  }
  else{
    printf("Invalid or no File given\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
