#ifndef _3S_CORE_HEADER
#define _3S_CORE_HEADER

#include <string.h>
#include <stdlib.h>

/* Returned if a value was not found in a search. */
#define VALUE_NOT_FOUND -1


/* General type of the values on the
 * trees and linked lists.
 * */
typedef int value_t;

/* This is the default formatter of the
 * type above. It will be used in situations
 * that the code must be printed through this library.
 * Please remember to change the format accordingly to
 * the type of value defined above.
 * */
#define __VALUE_T_DEFAULT_PRINTF_FORMAT "%d"

/* Maximum size of the string representation of the value_t. */
#define __VALUE_T_REPR_BUFFER_MAX_SIZE 30

/* Converts the value to its repr, returning the value stored into the given buffer. */
extern char* value_t_repr(const char* default_format,
                          const unsigned max_buf_size,
                          value_t value);

#define VALUE_T_REPR(value) value_t_repr(__VALUE_T_DEFAULT_PRINTF_FORMAT, __VALUE_T_REPR_BUFFER_MAX_SIZE, value)

#endif /* _3S_CORE_HEADER */
