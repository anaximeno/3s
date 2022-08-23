#include "../include/3s/core.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


/* Compares two basic values. And returns the result
 * being one of the three constants: S3_VALUE_LESS, S3_VALUE_EQUAL, and
 * S3_VALUE_GREATER
 * * */
#define COMPARE_V(a, b)\
    ((S3_VALUE_LESS * (a < b)) +\
    (S3_VALUE_EQUAL * (a == b)) +\
    (S3_VALUE_GREATER * (a > b)))


/* This was implemented to reduce duplication and improve reuse. */
#define WRAP_AROUND(STATEMENTS) {\
    s3_value_t wrapper = (s3_value_t) malloc(sizeof(struct s3_value_t));\
    if (wrapper != NULL) {\
        wrapper->repr = &s3_value_repr;\
        wrapper->display = &s3_value_display;\
        STATEMENTS\
    }\
    return wrapper;\
}

extern s3_value_t s3_value_int(int32_t value)
WRAP_AROUND(wrapper->data.integer = value; wrapper->type = INTEGER;);

extern s3_value_t s3_value_uint(uint32_t value)
WRAP_AROUND(wrapper->data.uinteger = value; wrapper->type = UNSIGNED;);

extern s3_value_t s3_value_float32(float value)
WRAP_AROUND(wrapper->data.float32 = value; wrapper->type = FLOAT32;);

extern s3_value_t s3_value_float64(double value)
WRAP_AROUND(wrapper->data.float64 = value; wrapper->type = FLOAT64;);

extern s3_value_t s3_value_string(char* value)
WRAP_AROUND(wrapper->data.string = value; wrapper->type = STRING;);

extern s3_value_t s3_value_char(char value)
WRAP_AROUND(wrapper->data.character = value; wrapper->type = CHARACTER;);

extern s3_value_t s3_value_pointer(void* value)
WRAP_AROUND(wrapper->data.pointer = value; wrapper->type = POINTER;);

extern s3_value_t s3_value_none(void) WRAP_AROUND(wrapper->type = NONE;);

extern char* s3_value_repr(s3_value_t value)
{
    char* buffer = (char*) calloc(__VALUE_T_REPR_BUFFER_MAX_SIZE, sizeof(char));

    if (buffer == NULL)
        return NULL;

#define _(FORMAT, VAL) sprintf(buffer, FORMAT, VAL); break;

    switch (value->type)
    {
    case INTEGER: _("%d", value->data.integer);
    case UNSIGNED: _("%u", value->data.uinteger);
    case FLOAT32: _("%f", value->data.float32);
    case FLOAT64: _("%lf", value->data.float64);
    case STRING: _("'%s'", value->data.string);
    case CHARACTER: _("'%c'", value->data.character);
    case POINTER: _("&{%p}", value->data.pointer);
    case NONE: _("%s", "NONE");

    default:
        // TODO: handle here. Exit gracefully?
        exit(EXIT_FAILURE);
        break;
    }

    /* Reallocates the size of the buffer to only use the space needed. */
    buffer = realloc(buffer, strlen(buffer) + 1);

    return buffer;
}

extern void s3_value_display(s3_value_t value)
{
    char* repr = s3_value_repr(value);
    printf("%s", repr);
    free(repr);
}

/* Compares two values and returns 0 if they are equal, 1 if value1 > value2,
 * and -1 if value2 > value1.
 * */
extern int s3_value_compare(s3_value_t value1, s3_value_t value2)
{
    if (value1->type == value2->type) {
        switch (value1->type)
        {
        case INTEGER:
            return COMPARE_V(value1->data.integer, value2->data.integer);
        case UNSIGNED:
            return COMPARE_V(value1->data.uinteger, value2->data.uinteger);
        case FLOAT32:
            return COMPARE_V(value1->data.float32, value2->data.float32);
        case FLOAT64:
            return COMPARE_V(value1->data.float64, value2->data.float64);
        case CHARACTER:
            return COMPARE_V(value1->data.character, value2->data.character);
        case POINTER:
            return COMPARE_V(value1->data.pointer, value2->data.pointer);
        case STRING:
            int comp = strcmp(value1->data.string, value2->data.string);
            #ifdef _MAKE_ROBUST_CHECK
            assert(comp == S3_VALUE_LESS || comp == S3_VALUE_GREATER || comp == S3_VALUE_EQUAL);
            #endif
            return comp;
        case NONE:
            return S3_VALUE_EQUAL;

        default:
            // TODO: handle here. Exit gracefully?
            exit(EXIT_FAILURE);
            break;
        }
    } else
        return S3_VALUE_DIFFERENT;
}
