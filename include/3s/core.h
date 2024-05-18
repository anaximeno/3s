/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * MIT License                                                                       *
 *                                                                                   *
 * Copyright (c) 2022-2024 Anaxímeno Brito                                                *
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

#ifndef _3S_CORE_HEADER
#define _3S_CORE_HEADER

#include <stdint.h>

/* Returned if the first value is less than the second one. */
#define TS_LESS -1
/* Returned if the first value is equal to the second one. */
#define TS_EQUAL 0
/* Returned if the first value is greater than the second one. */
#define TS_GREATER 1
/* Returned if the first value is of different type of the second one. */
#define TS_DIFFERENT -2022

/* When defined the program will
 * run the assertions stated in some
 * parts of the code. This is defined
 * on the core module.
 * */
#define _MAKE_ROBUST_CHECK 1

/* The types of values allowed inside the ts_generic_t wrapper. */
typedef enum ts_types
{
    INTEGER,
    UNSIGNED,
    FLOAT32,
    FLOAT64,
    STRING,
    CHARACTER,
    POINTER,
    NONE
} ts_types;

/* Wrapper used to store the actual data inside.
 * It was made so it could allow different types
 * to be stored in a shared space.
 * */
typedef struct ts_generic_t
{
    /* This union stores the actual data
     * inside one of its fields.
     * */
    union ts_data_type
    {
        int32_t integer;
        uint32_t uinteger;
        float float32;
        double float64;
        char *string;
        char character;
        void *pointer;
    } data;

    /* This represents the type of the
     * data being stored on the specific instance
     * of this structure.
     * */
    ts_types type;

    /* Returns a pointer to an array of characters containing
     * the string representation of the value depending on its type.
     * */
    char *(*repr)(struct ts_generic_t *);

    /* Shows the string representation of the value. It doesn't appends
     * a new line at the end of the value being printed.
     * */
    void (*display)(struct ts_generic_t *);

    /* Compare the self value with a the other given. */
    int (*compare)(struct ts_generic_t *, struct ts_generic_t *);
} *ts_generic_t;

/* Returns a newly allocated ts_generic_t of type INTEGER */
extern ts_generic_t ts_int(int32_t);
/* Returns a newly allocated ts_generic_t of type UNSIGNED */
extern ts_generic_t ts_uint(uint32_t);
/* Returns a newly allocated ts_generic_t of type FLOAT32 */
extern ts_generic_t ts_float32(float);
/* Returns a newly allocated ts_generic_t of type FLOAT64 */
extern ts_generic_t ts_float64(double);
/* Returns a newly allocated ts_generic_t of type STRING */
extern ts_generic_t ts_string(char *);
/* Returns a newly allocated ts_generic_t of type CHARACTER */
extern ts_generic_t ts_char(char);
/* Returns a newly allocated ts_generic_t of type POINTER */
extern ts_generic_t ts_pointer(void *);
/* Returns a newly allocated ts_generic_t of type POINTER */
extern ts_generic_t ts_none(void);

/* When in use, a global struct named value_factory will be available. */
#define CREATE_VALUE_T_FACTORY_AS(NAME)       \
    static const struct ts_factory            \
    {                                         \
        ts_generic_t (*from_int)(int32_t);    \
        ts_generic_t (*from_uint)(uint32_t);  \
        ts_generic_t (*from_float32)(float);  \
        ts_generic_t (*from_float64)(double); \
        ts_generic_t (*from_string)(char *);  \
        ts_generic_t (*from_char)(char);      \
        ts_generic_t (*from_pointer)(void *); \
        ts_generic_t (*from_none)(void);      \
    } NAME = {                                \
        .from_int = &ts_int,                  \
        .from_uint = &ts_uint,                \
        .from_float32 = &ts_float32,          \
        .from_float64 = &ts_float64,          \
        .from_string = &ts_string,            \
        .from_char = &ts_char,                \
        .from_pointer = &ts_pointer,          \
        .from_none = &ts_none,                \
    };

/* Maximum size of the string representation of the ts_generic_t. */
#define __VALUE_T_REPR_BUFFER_MAX_SIZE 30

/* Converts the value to its repr, returning the value stored into the given buffer. */
extern char *ts_repr(ts_generic_t value);

/* Prints the value to the stdout. */
extern void ts_display(ts_generic_t value);

/* Compares two values and returns 0 if they are equal, 1 if value1 > value2,
 * and -1 if value2 > value1.
 * */
extern int ts_compare(ts_generic_t value1, ts_generic_t value2);

#endif /* _3S_CORE_HEADER */
