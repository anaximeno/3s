#include "../include/core.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern char* value_t_repr(const char* default_format,
                          const unsigned max_buf_size,
                          value_t value)
{
    char* buffer = (char*) malloc(max_buf_size * sizeof(char));
    sprintf(buffer, default_format, value);
    return buffer;
}
