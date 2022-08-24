#include "../include/3s/core.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
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
    default: _("%s", "UNDEFINED");
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

/* Compares an double precision floating point value with a value_t value. */
extern int
s3_value_compare_float64_and_value_t(const double value1, const s3_value_t value2)
{
#define COMPARE(V) COMPARE_V(value1, V)
    switch (value2->type)
    {
        case INTEGER:
            return COMPARE(value2->data.integer);
        case UNSIGNED:
            return COMPARE(value2->data.uinteger);
        case FLOAT32:
            return COMPARE(value2->data.float32);
        case FLOAT64:
            return COMPARE(value2->data.float64);
        case CHARACTER:
        case STRING:
        case POINTER:
        case NONE:
        default:
            return S3_VALUE_DIFFERENT;
    }
}

/* Compares an simple precision value with a value_t value. */
extern int
s3_value_compare_float32_and_value_t(const float value1, const s3_value_t value2)
{
    return s3_value_compare_float64_and_value_t((double) value1, value2);
}

/* Compares an unsigned integer with a value_t value. */
extern int
s3_value_compare_uint_and_value_t(const uint32_t value1, const s3_value_t value2)
{
    return s3_value_compare_float64_and_value_t((double) value1, value2);
}

/* Compares an integer with a value_t value. */
extern int
s3_value_compare_int_and_value_t(const int32_t value1, const s3_value_t value2)
{
    return s3_value_compare_float64_and_value_t((double) value1, value2);
}

/* Compares an char value with a value_t value. */
extern int
s3_value_compare_char_and_value_t(const char value1, const s3_value_t value2)
{
#define COMPARE(V) COMPARE_V(value1, V)
    switch (value2->type) {
        case CHARACTER:
            return COMPARE(value2->data.character);
        case STRING:
            if (strlen(value2->data.string) > 0)
                return COMPARE(*value2->data.string);
            return value1 == '\0' ? S3_VALUE_EQUAL : S3_VALUE_GREATER;
        case INTEGER:
        case UNSIGNED:
        case FLOAT32:
        case FLOAT64:
        case POINTER:
        case NONE:
        default:
            return S3_VALUE_DIFFERENT;
    }
}

/* Compares an string value with a value_t value. */
extern int
s3_value_compare_string_and_value_t(char* value1, const s3_value_t value2)
{
    if (value2->type == CHARACTER) {
        if (strlen(value1) == 0) {
            //empty string
            return value2->data.character == '\0' ? S3_VALUE_EQUAL : S3_VALUE_LESS;
        } else if (strlen(value1) == 1) {
            // the string as just one character, then compare the characters
            return COMPARE_V(*value1, value2->data.character);
        } else { // strlen(value1) > 0
            // in this case, if the first character is equal as the character value
            // of value2, then the character value will be considered the lesser, and
            // the string as the greater.
            const int cmp = COMPARE_V(*value1, value2->data.character);
            return cmp == 0 ? S3_VALUE_GREATER : cmp;
        }
    } else if (value2->type == STRING) {
        const int cmp = strcmp(value1, value2->data.string);

#ifdef _MAKE_ROBUST_CHECK
        assert(
            cmp == S3_VALUE_LESS ||
            cmp == S3_VALUE_EQUAL ||
            cmp == S3_VALUE_GREATER
        );
#endif

        return cmp;
    } else {
        /* Values can't be compared. */
        return S3_VALUE_DIFFERENT;
    }
}

/* Compares an pointer value with a value_t value. */
extern int
s3_value_compare_pointer_and_value_t(void* value1, const s3_value_t value2)
{
    if (value2->type == POINTER)
        return COMPARE_V(value1, value2->data.pointer);
    return S3_VALUE_DIFFERENT;
}

/* Compares two values and returns 0 if they are equal, 1 if value1 > value2,
 * and -1 if value2 > value1.
 * */
extern int s3_value_compare(s3_value_t value1, s3_value_t value2)
{
    switch (value1->type)
    {
    case INTEGER:
        return s3_value_compare_int_and_value_t(value1->data.integer, value2);
    case UNSIGNED:
        return s3_value_compare_uint_and_value_t(value1->data.uinteger, value2);
    case FLOAT32:
        return s3_value_compare_float32_and_value_t(value1->data.float32, value2);
    case FLOAT64:
        return s3_value_compare_float64_and_value_t(value1->data.float64, value2);
    case CHARACTER:
        return s3_value_compare_char_and_value_t(value1->data.character, value2);
    case STRING:
        return s3_value_compare_string_and_value_t(value1->data.string, value2);
    case POINTER:
        return s3_value_compare_pointer_and_value_t(value1->data.pointer, value2);
    case NONE:
        if (value2->type == NONE)
            return S3_VALUE_EQUAL;
        /* Return default value else. */
    default:
        return S3_VALUE_DIFFERENT;
    }
}
