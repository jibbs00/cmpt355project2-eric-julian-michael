#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "game.h"
#include "game_node.h"
#include "move.h"
#include "state.h"
#include "konane.h"
#include "utility.h"

#define INPUT_SIZE  20 

time_t timer;

int game( char *file )
{

    /* human or computer player */
    printf( "Play konane:\n" );
    printf( " a) play computer\n" );
    printf( " b) computer vs computer\n" );
    char option[ INPUT_SIZE ];
    do
    {
        printf( "Please choose an option: " );
        fgets( option, INPUT_SIZE, stdin );
    }
    while( option[ 0 ] != 'a' && option[ 0 ] != 'b' );

    if( option[0] == 'a' )
    {
        human_vs_computer(file);
    }
    else
    {
        computer_vs_computer(file);
    }

    return 1;
}

int human_vs_computer( char *file )
{
    char input[ INPUT_SIZE ];
    char board[ SIZE ][ SIZE ];
    char player;

    /* set up board */
    /*int _player = 0;
    for( int i = 0; i < 8 ; i++ )
    {
        for( int j = 0; j < 8; j++ )
        {
            if( _player == 0 )
            {
                board[i][j] = 'B';
                _player = 1;
            }
            else
            {
                board[i][j] = 'W';
                _player = 0;
            }
        }
        if( _player == 0 )
            _player = 1;
        else
            _player = 0;
	    }*/
    setup_board(file,board);
    
  
    /* choose player */
    do 
    {
        printf( "Please choose a player ('B' or 'W' ): " );
        fgets( input, INPUT_SIZE, stdin );
    }
    while( input[ 0 ] != 'W' && input[ 0 ] != 'B' );
    player = input[0];

    /* create a new state */
    struct State * state = new_state( board, 'B' );

    print_state( state );

    /* START GAME */

    /* start game ( B first ) */
    struct State * temp_state;
    if( player == 'B' )
    {
        temp_state = human_player_first( state );
        Free( state, sizeof( struct State ) );
        state = temp_state;
    }
    else
    {
        temp_state = computer_player_first( state );
        Free( state, sizeof( struct State ) );
        state = temp_state;
    }

    /* second move */
    printf( "\n" );
    print_state( state );
    if( player == 'W' )
    {
        temp_state = human_player_second( state );
        Free( state, sizeof( struct State ) );
        state = temp_state;
    }
    else
    {
        temp_state = computer_player_second( state );
        Free( state, sizeof( struct State ) );
        state = temp_state;
    }

    /* regular game */
    for( ;; )
    {
        printf( "\n" );
        print_state( state );

        if( state->player == player )
        {
            temp_state = human_player( state );
            Free( state, sizeof( struct State ) );
            state = temp_state;
        }
        else
        {
            temp_state = computer_player( state );
            Free( state, sizeof( struct State ) );
            state = temp_state;
        }

        if( terminal_test( state ) == 1 )
        {
            printf( "%c wins!!!\n", opposite_player( state->player ) );
            break;
        }
    }

    return 1;
}

int computer_vs_computer( char *file )
{
    char board[ SIZE ][ SIZE ];

    /* set up board */
    /*int _player = 0;
    for( int i = 0; i < 8 ; i++ )
    {
        for( int j = 0; j < 8; j++ )
        {
            if( _player == 0 )
            {
                board[i][j] = 'B';
                _player = 1;
            }
            else
            {
                board[i][j] = 'W';
                _player = 0;
            }
        }
        if( _player == 0 )
            _player = 1;
        else
            _player = 0;
	    }*/
    setup_board(file,board);
    

    /* create a new state */
    struct State * state = new_state( board, 'B' );
    struct State * temp_state;

    /* start game */
    print_state( state );
    temp_state = computer_player_first( state );
    Free( state, sizeof( struct State ) );
    state = temp_state;

    /* second move */
    printf( "\n" );
    print_state( state );
    temp_state = computer_player_second( state );
    Free( state, sizeof( struct State ) );
    state = temp_state;

    /* regular game */
    for( ;; )
    {
        printf( "\n" );
        print_state( state );

        printf( "\n>> Mem usage before: %ld\n", memory_usage() );
        temp_state = computer_player( state );
        Free( state, sizeof( struct State ) );
        state = temp_state;
        printf( ">> Mem usage after: %ld\n", memory_usage() );

        if( terminal_test( state ) == 1 )
        {
            printf( "\n" );
            print_state( state );
            printf( "\nNo moves left!... \n" );
            printf( "\n%c wins!!!\n", opposite_player( state->player ) );
            Free( state, sizeof( struct State ) );
            break;
        }
    }
    return 1;
}

struct State * human_player_first( struct State * game_state )
{
    char input[ INPUT_SIZE ];
    struct State * state;
    struct Move * move;

    printf( "To begin game, please remove one piece from the board.\n" );
    printf( "Valid moves are from the 4 center squares, or one of the corners.\n" );
    printf( "Piece removed must be a piece of your color!\n" );

    /* get input */
    do 
    {
        printf( "Please enter a move: " );
        fgets( input, INPUT_SIZE, stdin );

        move = translate_first_in_move( input );

        /* make sure piece is of players color */
        if( game_state->board[ move->start_row ][ move->start_col ] != 'B' )
        {
            /* invalid move */
            Free( move, sizeof( struct Move ) );
        }
    }
    while( move == NULL );

    /* create a new state */
    state = new_state( game_state->board, opposite_player( game_state->player ) );

    /* apply move */
    state->board[ move->start_row ][ move->start_col ] = 'O';
    print_move( move );

    return state;
}

struct State * human_player_second( struct State * game_state )
{
    char input[ INPUT_SIZE ];
    struct State * state;
    struct Move * move;

    /* must remove piece orthoganally adjacent */

    printf( "Please remove a piece of your color adjacent to the piece removed\n" );

    /* get input */
    do 
    {
        printf( "Please enter a move: " );
        fgets( input, INPUT_SIZE, stdin );

        move = translate_first_in_move( input );

        /* make sure piece is valid */
        if( move != NULL )
        {
            if( validate_second_in_move( game_state, move ) == 0 )
            {
                /* invalid move */
                Free( move, sizeof( struct Move ) );
            }
            else
                break;
        }
    }
    while( 1 );

    printf( "Move chosen: " );
    print_move( move );

    /* create a new state */
    state = new_state( game_state->board, opposite_player( game_state->player ) );

    /* apply move */
    state->board[ move->start_row ][ move->start_col ] = 'O';

    return state;
    
}

struct State * computer_player_first( struct State * game_state )
{
    struct State * state;
    struct Move * move;

    srand( time( NULL ) );

    do
    {
        /* determine a move randomly */
        int random_move = rand() % 8;

        switch( random_move )
        {
        case 0:
            /* center top left */
            move = new_move( 3, 3, 0, 0 );
            break;
        case 1:
            /* center top right */
            move = new_move( 3, 4, 0, 0 );
            break;
        case 2:
            /* center botom left */
            move = new_move( 4, 3, 0, 0 );
            break;
        case 3:
            /* center bottom right */
            move = new_move( 4, 4, 0, 0 );
            break;
        case 4:
            /* corner top left */
            move = new_move( 0, 0, 0, 0 );
            break;
        case 5:
            /* corner top right */
            move = new_move( 0, 7, 0, 0 );
            break;
        case 6:
            /* corner bottom left */
            move = new_move( 7, 0, 0, 0 );
            break;
        case 7:
            /* corner bottom right */
            move = new_move( 7, 7, 0, 0 );
            break;
        }

        /* check if move is valid */
        if( game_state->board[ move->start_row ][ move->start_col ] == 'B' )
        {
            break;
        }
        else
        {
            Free( move, sizeof( struct Move ) );
        }
    }
    while( 1 );

    /* print move */
    printf( "Move chosen: " );
    print_move( move );

    /* create new state */
    state = new_state( game_state->board, opposite_player( game_state->player ) );

    /* apply move */
    state->board[ move->start_row ][ move->start_col ] = 'O';

    Free( move, sizeof( struct Move ) );

    return state;

}

struct State * computer_player_second( struct State * game_state )
{
    struct State * state;
    struct Move * move;
    int random_move = 0;
    int row, col, i, j;

    /* find blank spot */
    for( row = 0; row < SIZE; row++ )
        for( col = 0; col < SIZE; col++ )
            if( game_state->board[row][col] == 'O' )
            {
                i = row;
                j = col;
                break;
            }

    srand( time( NULL ) );

    /* select piece */
    /* valid moves are on either side of empty space */
    if( i == 0 && j == 0 )
    {
        if( ( game_state->board[ i ][ j + 1 ] == 'W' ) ||
            ( game_state->board[ i + 1][ j ] == 'W' ) )
        {
            random_move = rand() % 2;

            switch( random_move )
            {
            case 0:
                move = new_move( i, j+1, 0, 0 );
                break;
            case 1:
                move = new_move( i+1, j, 0, 0 );
                break;
            }
        }

    }
    else if( i == 0 && j == 7 )
    {
        if( (game_state->board[ i ][ j - 1 ] == 'W' ) ||
            (game_state->board[ i + 1 ][ j ] == 'W' ) )
        {
            random_move = rand() % 2;

            switch( random_move )
            {
            case 0:
                move = new_move( i, j-1, 0, 0 );
                break;
            case 1:
                move = new_move( i+1, j, 0, 0 );
                break;
            }
        }
    }
    else if( i == 7 && j == 0 )
    {
        if( (game_state->board[ i ][ j + 1 ] == 'W' ) ||
            (game_state->board[ i - 1 ][ j ] == 'W' ) )
        {
            random_move = rand() % 2;

            switch( random_move )
            {
            case 0:
                move = new_move( i, j+1, 0, 0 );
                break;
            case 1:
                move = new_move( i-1, j, 0, 0 );
                break;
            }
        }
    }
    else if( i == 7 && j == 7 )
    {
        if( (game_state->board[ i ][ j - 1 ] == 'W' ) ||
            (game_state->board[ i - 1 ][ j ] == 'W' ) )
        {
            random_move = rand() % 2;

            switch( random_move )
            {
            case 0:
                move = new_move( i, j-1, 0, 0 );
                break;
            case 1:
                move = new_move( i-1, j, 0, 0 );
                break;
            }
        }
    }
    else
    {
        if( (game_state->board[ i + 1 ][ j ] == 'W' ) ||
            (game_state->board[ i - 1 ][ j ] == 'W' ) ||
            (game_state->board[ i ][ j + 1 ] == 'W' ) ||
            (game_state->board[ i ][ j - 1 ] == 'W' ) )
        {
            random_move = rand() % 4;

            switch( random_move )
            {
            case 0:
                move = new_move( i+1, j, 0, 0 );
                break;
            case 1:
                move = new_move( i-1, j, 0, 0 );
                break;
            case 2:
                move = new_move( i, j+1, 0, 0 );
                break;
            case 3:
                move = new_move( i, j-1, 0, 0 );
                break;
            }
        }
    }

    /* print move */
    printf( "Move chosen: " );
    print_move( move );

    /* create new state */
    state = new_state( game_state->board, opposite_player( game_state->player ) );

    /* apply move */
    state->board[ move->start_row ][ move->start_col ] = 'O';
    Free( move, sizeof( struct Move ) );

    return state;
}


struct State * human_player( struct State * game_state )
{
    char input[ INPUT_SIZE ];
    struct State * state;
    struct Move * move;
    //struct GameNode * root;

    /* get input */
    do 
    {
        printf( "Please enter a move: " );
        fgets( input, INPUT_SIZE, stdin );

        move = translate_in_move( input );

        if( move != NULL )
        {
            if( validate_action( game_state, move ) == 1 )
                break;
            else
            {
                Free( move, sizeof( struct Move ) );
                move = NULL;
            }
        }
    }
    while( move == NULL );

    /* print move */
    printf( "Move chosen: " );
    print_move( move );

    /* create a new state & apply move */
    state = result( game_state, move );
    Free( move, sizeof( struct Move ) );
    state->player = opposite_player( game_state->player );

    return state;

}

struct State * computer_player( struct State * game_state )
{
    struct State * state;
    struct Move * move;
    struct GameNode * root;
    time_t stop;

    /* create a new game node */
    root = new_game_node( game_state, NULL );

    /* computer player */
    time( &timer );
    move = alpha_beta_search( root );
    time( &stop );

    /* print time */
    printf( "Time taken: %d\n", stop - timer );

    /* print move */
    printf( "Move chosen: " );
    print_move( move );

    /* create a new state and apply move */
    state = result( game_state, move );
    Free( move, sizeof( struct Move ) );
    state->player = opposite_player( game_state->player );

    delete_game_node( &root );

    return state;
}
