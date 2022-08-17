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
    STRING, CHARACTER, POINTER
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
extern s3_value_t s3_new_int_value_t(int32_t);
/* Returns a newly allocated s3_value_t of type UNSIGNED */
extern s3_value_t s3_new_uint_value_t(uint32_t);
/* Returns a newly allocated s3_value_t of type FLOAT32 */
extern s3_value_t s3_new_float32_value_t(float);
/* Returns a newly allocated s3_value_t of type FLOAT64 */
extern s3_value_t s3_new_float64_value_t(double);
/* Returns a newly allocated s3_value_t of type STRING */
extern s3_value_t s3_new_string_value_t(char*);
/* Returns a newly allocated s3_value_t of type CHARACTER */
extern s3_value_t s3_new_char_value_t(char);
/* Returns a newly allocated s3_value_t of type POINTER */
extern s3_value_t s3_new_pointer_value_t(void*);

/* When in use, a global struct named value_factory will be available. */
#define CREATE_VALUE_T_FACTORY_AS(NAME)\
    static const struct s3_value_t_factory {\
        s3_value_t (*new_int) (int32_t);\
        s3_value_t (*new_uint) (uint32_t);\
        s3_value_t (*new_float32) (float);\
        s3_value_t (*new_float64) (double);\
        s3_value_t (*new_string) (char*);\
        s3_value_t (*new_char) (char);\
        s3_value_t (*new_pointer) (void*);\
    } NAME = {\
        .new_int=&s3_new_int_value_t,\
        .new_uint=&s3_new_uint_value_t,\
        .new_float32=&s3_new_float32_value_t,\
        .new_float64=&s3_new_float64_value_t,\
        .new_string=&s3_new_string_value_t,\
        .new_char=&s3_new_char_value_t,\
        .new_pointer=&s3_new_pointer_value_t,\
    };

/* Maximum size of the string representation of the s3_value_t. */
#define __VALUE_T_REPR_BUFFER_MAX_SIZE 30

/* Converts the value to its repr, returning the value stored into the given buffer. */
extern char* s3_value_t_repr(s3_value_t value);

/* Prints the value to the stdout. */
extern void s3_value_t_display(s3_value_t value);

#endif /* _3S_CORE_HEADER */
