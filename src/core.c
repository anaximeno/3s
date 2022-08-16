#include "../include/core.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* This was implemented to reduce duplication and improve reuse. */
#define WRAP_AROUND(STATEMENTS) ({\
    s3_value_t value_wrapper = (s3_value_t) malloc(sizeof(struct s3_value_t));\
    if (value_wrapper != NULL) {\
        value_wrapper->repr = &s3_value_t_repr;\
        value_wrapper->display = &s3_value_t_display;\
        STATEMENTS\
    }\
    return value_wrapper;\
})


extern s3_value_t s3_new_int_value_t(int32_t value)
{
    WRAP_AROUND(value_wrapper->data.integer = value; value_wrapper->type = INTEGER;);
}

extern s3_value_t s3_new_uint_value_t(uint32_t value)
{
    WRAP_AROUND(value_wrapper->data.uinteger = value; value_wrapper->type = UNSIGNED;);
}

extern s3_value_t s3_new_float32_value_t(float value)
{
    WRAP_AROUND(value_wrapper->data.float32 = value; value_wrapper->type = FLOAT32;);
}

extern s3_value_t s3_new_float64_value_t(double value)
{
    WRAP_AROUND(value_wrapper->data.float64 = value; value_wrapper->type = FLOAT64;);
}

extern s3_value_t s3_new_string_value_t(char* value)
{
    WRAP_AROUND(value_wrapper->data.string = value; value_wrapper->type = STRING;);
}

extern s3_value_t s3_new_char_value_t(char value)
{
    WRAP_AROUND(value_wrapper->data.character = value; value_wrapper->type = CHARACTER;);
}

extern s3_value_t s3_new_pointer_value_t(void* value)
{
    WRAP_AROUND(value_wrapper->data.pointer = value; value_wrapper->type = POINTER;);
}

extern char* s3_value_t_repr(s3_value_t value)
{
    char* buffer = (char*) malloc(__VALUE_T_REPR_BUFFER_MAX_SIZE * sizeof(char));

    if (buffer == NULL)
        return NULL;

#define _(FORMAT, VAL) sprintf(buffer, FORMAT, VAL); break;

    switch (value->type)
    {
    case INTEGER: _("%d", value->data.integer);

    case UNSIGNED: _("%u", value->data.uinteger);

    case FLOAT32: _("%f", value->data.float32);

    case FLOAT64: _("%lf", value->data.float64);

    case STRING: _("%s", value->data.string);

    case CHARACTER: _("%c", value->data.character);

    case POINTER: _("&{%p}", value->data.pointer);

    default:
        // TODO: handle here. Exit gracefully?
        break;
    }

    return buffer;
}

extern void s3_value_t_display(s3_value_t value)
{
    char* repr = s3_value_t_repr(value);
    printf("%s", repr);
    free(repr);
}