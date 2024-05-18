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

/* Maximum size of the string representation of the ts_generic_t. */
#define TS_MAX_REPR_STR_BUF_SIZE 30

/* The types of values allowed inside the ts_generic_t wrapper. */
typedef enum ts_types
{
    TS_TYPE_INTEGER,
    TS_TYPE_UNSIGNED,
    TS_TYPE_FLOAT32,
    TS_TYPE_FLOAT64,
    TS_TYPE_STRING,
    TS_TYPE_CHARACTER,
    TS_TYPE_POINTER,
    TS_TYPE_NONE
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
extern ts_generic_t ts_new_int(int32_t);
/* Returns a newly allocated ts_generic_t of type UNSIGNED */
extern ts_generic_t ts_new_uint(uint32_t);
/* Returns a newly allocated ts_generic_t of type FLOAT32 */
extern ts_generic_t ts_new_float32(float);
/* Returns a newly allocated ts_generic_t of type FLOAT64 */
extern ts_generic_t ts_new_float64(double);
/* Returns a newly allocated ts_generic_t of type STRING */
extern ts_generic_t ts_new_string(char *);
/* Returns a newly allocated ts_generic_t of type CHARACTER */
extern ts_generic_t ts_new_char(char);
/* Returns a newly allocated ts_generic_t of type POINTER */
extern ts_generic_t ts_new_pointer(void *);
/* Returns a newly allocated ts_generic_t of type POINTER */
extern ts_generic_t ts_new_none(void);

/* 3s Generic type value factory. */
typedef struct ts_generic_t_factory
{
    const ts_generic_t (*new_int)(int32_t);
    const ts_generic_t (*new_uint)(uint32_t);
    const ts_generic_t (*new_float32)(float);
    const ts_generic_t (*new_float64)(double);
    const ts_generic_t (*new_string)(char *);
    const ts_generic_t (*new_char)(char);
    const ts_generic_t (*new_pointer)(void *);
    const ts_generic_t (*new_none)(void);
} ts_generic_t_factory;

/* When in use, a global struct named value_factory will be available. */
#define TS_NEW_GENERIC_T_FACTORY()      \
    {                                   \
        .new_int = &ts_new_int,         \
        .new_uint = &ts_new_uint,       \
        .new_float32 = &ts_new_float32, \
        .new_float64 = &ts_new_float64, \
        .new_string = &ts_new_string,   \
        .new_char = &ts_new_char,       \
        .new_pointer = &ts_new_pointer, \
        .new_none = &ts_new_none,       \
    };

/* Converts the value to its repr, returning the value stored into the given buffer. */
extern char *ts_repr(ts_generic_t value);

/* Prints the value to the stdout. */
extern void ts_display(ts_generic_t value);

/* Compares two values and returns 0 if they are equal, 1 if value1 > value2,
 * and -1 if value2 > value1.
 * */
extern int ts_compare(ts_generic_t value1, ts_generic_t value2);

#endif /* _3S_CORE_HEADER */
