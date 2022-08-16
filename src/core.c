#include "../include/core.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define WRAP_AROUND(STTMT) ({\
    value_t* value_wrapper = (value_t*) malloc(sizeof(value_t));\
    if (value_wrapper != NULL) { STTMT }\
    return value_wrapper;\
})


extern value_t* new_int_value_t(int32_t value)
{
    WRAP_AROUND(value_wrapper->data.integer = value;);
}

extern value_t* new_uint_value_t(uint32_t value)
{
    WRAP_AROUND(value_wrapper->data.uinteger = value;);
}

extern value_t* new_float32_value_t(float value)
{
    WRAP_AROUND(value_wrapper->data.float32 = value;);
}

extern value_t* new_float64_value_t(double value)
{
    WRAP_AROUND(value_wrapper->data.float64 = value;);
}

extern value_t* new_string_value_t(char* value)
{
    WRAP_AROUND(value_wrapper->data.string = value;);
}

extern value_t* new_char_value_t(char value)
{
    WRAP_AROUND(value_wrapper->data.character = value;);
}

extern value_t* new_pointer_value_t(void* value)
{
    WRAP_AROUND(value_wrapper->data.pointer = value;);
}

extern char* value_t_repr(value_t value)
{
    char* buffer = (char*) malloc(__VALUE_T_REPR_BUFFER_MAX_SIZE * sizeof(char));

    switch (value.type)
    {
    case INTEGER:
        sprintf(buffer, "%d", value.data.integer);
        break;

    case UNSIGNED:
        sprintf(buffer, "%u", value.data.uinteger);
        break;

    case FLOAT32:
        sprintf(buffer, "%f", value.data.float32);
        break;

    case FLOAT64:
        sprintf(buffer, "%lf", value.data.float64);
        break;

    case STRING:
        sprintf(buffer, "%s", value.data.string);
        break;

    case CHARACTER:
        sprintf(buffer, "%c", value.data.character);
        break;

    case POINTER:
        sprintf(buffer, "&[%p]", value.data.pointer);
        break;

    default:
        // TODO: handle here, exit gracefully?
        break;
    }

    return buffer;
}
