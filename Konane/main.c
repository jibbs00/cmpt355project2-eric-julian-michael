#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main( int argc, char * argv[] )
{

    if( argc != 3 )
    {
        printf("Invalid or no File given\n");
        printf( "%s usage: <input file> <player color>\n", argv[ 0 ] );
        printf( "\t input file - a text file consisting of a konane board\n" );
        printf( "\t player color - a single character B, W which indicates the role the agent assumes.\n" );
        printf( "\t                If player color is not equal to b or w, then game enters interactive mode\n" );
        return EXIT_FAILURE;
    }

    char * str = argv[ 2 ];
    game( argv[ 1 ], str[ 0 ] );
    
/*
  if( argv[1] != NULL ){
    game(argv[1]);
  }
  else{
    printf("Invalid or no File given\n");
    return EXIT_FAILURE;
  }
  */

  return EXIT_SUCCESS;
}
