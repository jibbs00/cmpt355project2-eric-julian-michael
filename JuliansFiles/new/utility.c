#include <stdlib.h>
#include "utility.h"

static unsigned long _memory_usage = 0;

void * Calloc( size_t nmemb, size_t size )
{
    _memory_usage += (nmemb * size);

    return calloc( nmemb, size );
}

void Free( void * ptr, size_t size )
{
    _memory_usage -= size;

    free( ptr );
}

unsigned long memory_usage( void )
{
    return _memory_usage;
}
