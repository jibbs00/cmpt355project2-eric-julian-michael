/**
 * @file utility.c
 * @author Julian Martinez del Campo
 * @brief this file implements utility.h
 */
#include <stdlib.h>
#include "utility.h"

static unsigned long _memory_usage = 0;

/**
 * Calloc
 *
 * This funciton is a wrapper to calloc. It checks that memory was
 *  properly allocated, and tracks memory usage
 *
 * @param the number of elements in the array
 * @param size the size of the element
 * @return a pointer to the allocated memory
 */
void * Calloc( size_t nmemb, size_t size )
{
  _memory_usage += (nmemb * size);

  return calloc( nmemb, size );
}

/**
 * Free memory
 *
 * Frees memory, and decreases the memory usage tracked accordingly
 *
 * @param ptr to memory to free
 * @param size the size of the memory to free
 */
void Free( void * ptr, size_t size )
{
  _memory_usage -= size;

  free( ptr );
}

/**
 * Get the memory used by the program
 *
 * @return the memory used, in bytes
 */
unsigned long memory_usage( void )
{
  return _memory_usage;
}
