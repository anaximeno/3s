/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * MIT License                                                                       *
 *                                                                                   *
 * Copyright (c) 2022-2024 Anaxímeno Brito                                           *
 *                                                                                   *
 * Permission is hereby granted, free of charge, to any person obtaining a copy      *
 * of this software and associated documentation files (the "Software"), to deal     *
 * in the Software without restriction, including without limitation the rights      *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell         *
 * copies of the Software, and to permit persons to whom the Software is             *
 * furnished to do so, subject to the following conditions:                          *
 *                                                                                   *
 * The above copyright notice and this permission notice shall be included in all    *
 * copies or substantial portions of the Software.                                   *
 *                                                                                   *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR        *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,          *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE       *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER            *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,     *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE     *
 * SOFTWARE.                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "../include/3s/core.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

/* Compares two basic values. And returns the result
 * being one of the three constants: TS_LESS, TS_EQUAL, and
 * TS_GREATER
 * * */
#define CMP(a, b)            \
    ((TS_LESS * (a < b)) +   \
     (TS_EQUAL * (a == b)) + \
     (TS_GREATER * (a > b)))

/* Wraps the common processes for initializing and assigning value into a new
 * ts generic value.
 * */
#define WRAP(WRAPPINGS)                                                           \
    {                                                                             \
        ts_generic_t wrapped = (ts_generic_t)malloc(sizeof(struct ts_generic_t)); \
                                                                                  \
        if (wrapped != NULL)                                                      \
        {                                                                         \
            wrapped->repr = &ts_generic_t_repr;                                   \
            wrapped->display = &ts_generic_t_display;                             \
            wrapped->compare = &ts_generic_t_cmp;                                 \
            WRAPPINGS;                                                            \
        }                                                                         \
                                                                                  \
        return wrapped;                                                           \
    }

extern ts_generic_t ts_new_int(int32_t value) WRAP({
    wrapped->data.integer = value;
    wrapped->type = TS_TYPE_INTEGER;
});

extern ts_generic_t ts_new_uint(uint32_t value) WRAP({
    wrapped->data.uinteger = value;
    wrapped->type = TS_TYPE_UNSIGNED;
});

extern ts_generic_t ts_new_float32(float value) WRAP({
    wrapped->data.float32 = value;
    wrapped->type = TS_TYPE_FLOAT32;
});

extern ts_generic_t ts_new_float64(double value) WRAP({
    wrapped->data.float64 = value;
    wrapped->type = TS_TYPE_FLOAT64;
});

extern ts_generic_t ts_new_string(char *value) WRAP({
    wrapped->data.string = value;
    wrapped->type = TS_TYPE_STRING;
});

extern ts_generic_t ts_new_char(char value) WRAP({
    wrapped->data.character = value;
    wrapped->type = TS_TYPE_CHARACTER;
});

extern ts_generic_t ts_new_pointer(void *value) WRAP({
    wrapped->data.pointer = value;
    wrapped->type = TS_TYPE_POINTER;
});

extern ts_generic_t ts_new_none(void) WRAP({
    wrapped->type = TS_TYPE_NONE;
});

extern char *ts_generic_t_repr(ts_generic_t value)
{
    char *buffer = (char *)calloc(TS_MAX_REPR_STR_BUF_SIZE, sizeof(char));

    if (buffer != NULL)
    {
        switch (value->type)
        {
        case TS_TYPE_INTEGER:
            sprintf(buffer, "%d", value->data.integer);
            break;
        case TS_TYPE_UNSIGNED:
            sprintf(buffer, "%u", value->data.uinteger);
            break;
        case TS_TYPE_FLOAT32:
            sprintf(buffer, "%f", value->data.float32);
            break;
        case TS_TYPE_FLOAT64:
            sprintf(buffer, "%lf", value->data.float64);
            break;
        case TS_TYPE_STRING:
            sprintf(buffer, "'%s'", value->data.string);
            break;
        case TS_TYPE_CHARACTER:
            sprintf(buffer, "'%c'", value->data.character);
            break;
        case TS_TYPE_POINTER:
            sprintf(buffer, "&{%p}", value->data.pointer);
            break;
        case TS_TYPE_NONE:
            sprintf(buffer, "%s", "NONE");
            break;
        default:
            sprintf(buffer, "%s", "UNKNOWN");
            break;
        }

        // Reallocates the size of the buffer to only use the space needed.
        buffer = realloc(buffer, strlen(buffer) + 1);
    }

    return buffer;
}

extern void ts_generic_t_display(ts_generic_t value)
{
    char *repr = ts_generic_t_repr(value);
    printf("%s", repr);
    free(repr);
}

/* Compares an double precision floating point value with a generic_t value. */
extern int
ts_cmp_float64_and_generic_t(const double value1, const ts_generic_t value2)
{
    switch (value2->type)
    {
    case TS_TYPE_INTEGER:
        return CMP(value1, value2->data.integer);
    case TS_TYPE_UNSIGNED:
        return CMP(value1, value2->data.uinteger);
    case TS_TYPE_FLOAT32:
        return CMP(value1, value2->data.float32);
    case TS_TYPE_FLOAT64:
        return CMP(value1, value2->data.float64);
    case TS_TYPE_CHARACTER:
    case TS_TYPE_STRING:
    case TS_TYPE_POINTER:
    case TS_TYPE_NONE:
    default:
        return TS_DIFFERENT;
    }
}

/* Compares an simple precision value with a generic_t value. */
extern int
ts_cmp_float32_and_generic_t(const float value1, const ts_generic_t value2)
{
    return ts_cmp_float64_and_generic_t((double)value1, value2);
}

/* Compares an unsigned integer with a generic_t value. */
extern int
ts_cmp_uint_and_generic_t(const uint32_t value1, const ts_generic_t value2)
{
    return ts_cmp_float64_and_generic_t((double)value1, value2);
}

/* Compares an integer with a generic_t value. */
extern int
ts_cmp_int_and_generic_t(const int32_t value1, const ts_generic_t value2)
{
    return ts_cmp_float64_and_generic_t((double)value1, value2);
}

/* Compares an char value with a generic_t value. */
extern int
ts_cmp_char_and_generic_t(const char value1, const ts_generic_t value2)
{
    if (value2->type == TS_TYPE_CHARACTER)
    {
        return CMP(value1, value2->data.character);
    }
    else if (value2->type == TS_TYPE_STRING)
    {
        const char *_value2 = value2->data.string;

        if (strlen(_value2) == 0)
        {
            return value1 == '\0' ? TS_EQUAL : TS_GREATER;
        }
        else if (strlen(_value2) == 1)
        {
            // the string as just one character, then compare the characters
            return CMP(value1, *_value2);
        }
        else
        { // strlen(_value2) > 0
            // in this case, if the first character is equal as the character value
            // of value2, then the character value will be considered the lesser, and
            // the string as the greater.
            const int cmp = CMP(value1, *_value2);
            return cmp == 0 ? TS_LESS : cmp;
        }
    }
    else
    {
        return TS_DIFFERENT;
    }
}

/* Compares an string value with a generic_t value. */
extern int
ts_cmp_string_and_generic_t(char *value1, const ts_generic_t value2)
{
    if (value2->type == TS_TYPE_CHARACTER)
    {
        if (strlen(value1) == 0)
        {
            // empty string
            return value2->data.character == '\0' ? TS_EQUAL : TS_LESS;
        }
        else if (strlen(value1) == 1)
        {
            // the string as just one character, then compare the characters
            return CMP(*value1, value2->data.character);
        }
        else
        { // strlen(value1) > 0
            // in this case, if the first character is equal as the character value
            // of value2, then the character value will be considered the lesser, and
            // the string as the greater.
            const int cmp = CMP(*value1, value2->data.character);
            return cmp == 0 ? TS_GREATER : cmp;
        }
    }
    else if (value2->type == TS_TYPE_STRING)
    {
        const int cmp = strcmp(value1, value2->data.string);

#ifdef _MAKE_ROBUST_CHECK
        assert(
            cmp == TS_LESS ||
            cmp == TS_EQUAL ||
            cmp == TS_GREATER);
#endif

        return cmp;
    }
    else
    {
        /* Values can't be compared. */
        return TS_DIFFERENT;
    }
}

/* Compares an pointer value with a generic_t value. */
extern int
ts_cmp_pointer_and_generic_t(void *value1, const ts_generic_t value2)
{
    if (value2->type == TS_TYPE_POINTER)
        return CMP(value1, value2->data.pointer);
    return TS_DIFFERENT;
}

/* Compares two values and returns 0 if they are equal, 1 if value1 > value2,
 * and -1 if value2 > value1.
 * */
extern int ts_generic_t_cmp(ts_generic_t value1, ts_generic_t value2)
{
    switch (value1->type)
    {
    case TS_TYPE_INTEGER:
        return ts_cmp_int_and_generic_t(value1->data.integer, value2);
    case TS_TYPE_UNSIGNED:
        return ts_cmp_uint_and_generic_t(value1->data.uinteger, value2);
    case TS_TYPE_FLOAT32:
        return ts_cmp_float32_and_generic_t(value1->data.float32, value2);
    case TS_TYPE_FLOAT64:
        return ts_cmp_float64_and_generic_t(value1->data.float64, value2);
    case TS_TYPE_CHARACTER:
        return ts_cmp_char_and_generic_t(value1->data.character, value2);
    case TS_TYPE_STRING:
        return ts_cmp_string_and_generic_t(value1->data.string, value2);
    case TS_TYPE_POINTER:
        return ts_cmp_pointer_and_generic_t(value1->data.pointer, value2);
    case TS_TYPE_NONE:
        if (value2->type == TS_TYPE_NONE)
            return TS_EQUAL;
        /* Else return default value below. */
    default:
        return TS_DIFFERENT;
    }
}
