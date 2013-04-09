/**
 * @file utility.h
 * @author Julian Martinez del Campo
 * @brief this file provides memory allocation routines, and memory tracking functions
 */
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdlib.h>

u#define SIZE 8

void setup_board(char *filename,char board[][SIZE]);

void * Calloc( size_t nmemb, size_t size );
void Free( void * ptr, size_t size );
unsigned long memory_usage( void );

#endif /* _UTILITY_H_ */
