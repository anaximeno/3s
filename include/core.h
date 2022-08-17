/* MIT License
 *
 * Copyright (c) 2022 Anaxímeno Brito
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * */


#ifndef _3S_CORE_HEADER
#define _3S_CORE_HEADER

#include <stdint.h>

/* Returned when searching for
 * values on lists or arrays.
 * This is defined on the
 * core module.
 * */
#define VALUE_NOT_FOUND -1

/* When defined the program will
 * run the assertions stated in some
 * parts of the code. This is defined
 * on the core module.
 * */
#define _MAKE_ROBUST_CHECK

/* The types of values allowed inside the s3_value_t wrapper. */
typedef enum s3_value_t_types {
    INTEGER, UNSIGNED, FLOAT32, FLOAT64,
    STRING, CHARACTER, POINTER, NONE
} s3_value_t_types;


/* Wrapper used to store the actual data inside.
 * It was made so it could allow different types
 * to be stored in a shared space.
 * */
typedef struct s3_value_t {
    /* This union stores the actual data
     * inside one of its fields.
     * */
    union s3_value_data_type {
        int32_t integer;
        uint32_t uinteger;
        float float32;
        double float64;
        char* string;
        char character;
        void* pointer;
    } data;

    /* This represents the type of the
     * data being stored on the specific instance
     * of this structure.
     * */
    s3_value_t_types type;

    /* Returns a pointer to an array of characters containing
     * the string representation of the value depending on its type.
     * */
    char* (*repr) (struct s3_value_t*);

    /* Shows the string representation of the value. It doesn't appends
     * a new line at the end of the value being printed.
     * */
    void (*display) (struct s3_value_t*);
}* s3_value_t;

/* Returns a newly allocated s3_value_t of type INTEGER */
extern s3_value_t s3_new_int(int32_t);
/* Returns a newly allocated s3_value_t of type UNSIGNED */
extern s3_value_t s3_new_uint(uint32_t);
/* Returns a newly allocated s3_value_t of type FLOAT32 */
extern s3_value_t s3_new_float32(float);
/* Returns a newly allocated s3_value_t of type FLOAT64 */
extern s3_value_t s3_new_float64(double);
/* Returns a newly allocated s3_value_t of type STRING */
extern s3_value_t s3_new_string(char*);
/* Returns a newly allocated s3_value_t of type CHARACTER */
extern s3_value_t s3_new_char(char);
/* Returns a newly allocated s3_value_t of type POINTER */
extern s3_value_t s3_new_pointer(void*);
/* Returns a newly allocated s3_value_t of type POINTER */
extern s3_value_t s3_new_none(void);

/* When in use, a global struct named value_factory will be available. */
#define CREATE_VALUE_T_FACTORY_AS(NAME)\
    static const struct s3_value_t_factory {\
        s3_value_t (*from_int) (int32_t);\
        s3_value_t (*from_uint) (uint32_t);\
        s3_value_t (*from_float32) (float);\
        s3_value_t (*from_float64) (double);\
        s3_value_t (*from_string) (char*);\
        s3_value_t (*from_char) (char);\
        s3_value_t (*from_pointer) (void*);\
        s3_value_t (*from_none) (void);\
    } NAME = {\
        .from_int=&s3_new_int,\
        .from_uint=&s3_new_uint,\
        .from_float32=&s3_new_float32,\
        .from_float64=&s3_new_float64,\
        .from_string=&s3_new_string,\
        .from_char=&s3_new_char,\
        .from_pointer=&s3_new_pointer,\
        .from_none=&s3_new_none,\
    };

/* Maximum size of the string representation of the s3_value_t. */
#define __VALUE_T_REPR_BUFFER_MAX_SIZE 30

/* Converts the value to its repr, returning the value stored into the given buffer. */
extern char* s3_value_repr(s3_value_t value);

/* Prints the value to the stdout. */
extern void s3_value_display(s3_value_t value);

#endif /* _3S_CORE_HEADER */
