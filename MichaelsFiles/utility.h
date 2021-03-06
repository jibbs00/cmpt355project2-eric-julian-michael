#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdlib.h>

void * Calloc( size_t nmemb, size_t size );
void Free( void * ptr, size_t size );
unsigned long memory_usage( void );

#endif /* _UTILITY_H_ */
