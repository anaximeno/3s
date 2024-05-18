#include "../include/tinytest/tinytest.h"
#include "../include/3s/3s.h"

#include <stdint.h>

// -- Testing value creation

void test_value_int_creation(void)
{
    s3_value_t value = s3_value_int(9);
    ASSERT_EQ(value->data.integer, (int32_t) 9);
    ASSERT_EQ(value->type, INTEGER);
}

void test_value_unsigned_creation(void)
{
    s3_value_t value = s3_value_uint(9);
    ASSERT_EQ(value->data.uinteger, (uint32_t) 9);
    ASSERT_EQ(value->type, UNSIGNED);
}

void test_value_float32_creation(void)
{
    s3_value_t value = s3_value_float32(9);
    ASSERT_EQ(value->data.float32, (float) 9);
    ASSERT_EQ(value->type, FLOAT32);
}

void test_value_float64_creation(void)
{
    s3_value_t value = s3_value_float64(9);
    ASSERT_EQ(value->data.float64, (double) 9);
    ASSERT_EQ(value->type, FLOAT64);
}

void test_value_string_creation(void)
{
    s3_value_t value = s3_value_string("Test");
    ASSERT_STR_EQ(value->data.string, "Test");
    ASSERT_EQ(value->type, STRING);
}

void test_value_pointer_creation(void)
{
    s3_value_t value = s3_value_pointer((void*) 3);
    ASSERT_EQ(value->data.pointer, (void*) 3);
    ASSERT_EQ(value->type, POINTER);
}

void test_value_char_creation(void)
{
    s3_value_t value = s3_value_char('X');
    ASSERT_EQ(value->data.character, 'X');
    ASSERT_EQ(value->type, CHARACTER);
}

void test_value_none_creation(void)
{
    s3_value_t value = s3_value_none();
    ASSERT_EQ(value->type, NONE);
}

// -- Testing representation

void test_value_int_repr(void)
{
    s3_value_t value = s3_value_int(3);
    ASSERT_STR_EQ(value->repr(value), "3");
}

// -- Testing comparation

void test_value_int_comparation(void)
{
    s3_value_t value1 = s3_value_int(3);

    ASSERT_EQ(S3_VALUE_GREATER, value1->compare(value1, s3_value_uint(1)));
    ASSERT_EQ(S3_VALUE_LESS, value1->compare(value1, s3_value_float32(3.4)));
    ASSERT_EQ(S3_VALUE_EQUAL, value1->compare(value1, s3_value_float64(3.0)));
    ASSERT_EQ(S3_VALUE_DIFFERENT, value1->compare(value1, s3_value_string("test")));
    ASSERT_EQ(S3_VALUE_DIFFERENT, value1->compare(value1, s3_value_char('x')));
    ASSERT_EQ(S3_VALUE_DIFFERENT, value1->compare(value1, s3_value_pointer(0)));
}

void test_value_uint_comparation(void)
{
    s3_value_t value1 = s3_value_uint(3);

    ASSERT_EQ(S3_VALUE_GREATER, value1->compare(value1, s3_value_float32(1)));
    ASSERT_EQ(S3_VALUE_LESS, value1->compare(value1, s3_value_float64(4)));
    ASSERT_EQ(S3_VALUE_EQUAL, value1->compare(value1, s3_value_int(3)));
    ASSERT_EQ(S3_VALUE_DIFFERENT, value1->compare(value1, s3_value_string("test")));
    ASSERT_EQ(S3_VALUE_DIFFERENT, value1->compare(value1, s3_value_char('x')));
    ASSERT_EQ(S3_VALUE_DIFFERENT, value1->compare(value1, s3_value_pointer(0)));
}

void test_value_float32_comparation(void)
{
    s3_value_t value1 = s3_value_float32(3.0);

    ASSERT_EQ(S3_VALUE_GREATER, value1->compare(value1, s3_value_float64(1)));
    ASSERT_EQ(S3_VALUE_LESS, value1->compare(value1, s3_value_uint(4)));
    ASSERT_EQ(S3_VALUE_EQUAL, value1->compare(value1, s3_value_int(3)));
    ASSERT_EQ(S3_VALUE_DIFFERENT, value1->compare(value1, s3_value_string("test")));
    ASSERT_EQ(S3_VALUE_DIFFERENT, value1->compare(value1, s3_value_char('x')));
    ASSERT_EQ(S3_VALUE_DIFFERENT, value1->compare(value1, s3_value_pointer(0)));
}

void test_value_float64_comparation(void)
{
    s3_value_t value1 = s3_value_float64(3.0);

    ASSERT_EQ(S3_VALUE_GREATER, value1->compare(value1, s3_value_float32(1)));
    ASSERT_EQ(S3_VALUE_LESS, value1->compare(value1, s3_value_uint(4)));
    ASSERT_EQ(S3_VALUE_EQUAL, value1->compare(value1, s3_value_int(3)));
    ASSERT_EQ(S3_VALUE_DIFFERENT, value1->compare(value1, s3_value_string("test")));
    ASSERT_EQ(S3_VALUE_DIFFERENT, value1->compare(value1, s3_value_char('x')));
    ASSERT_EQ(S3_VALUE_DIFFERENT, value1->compare(value1, s3_value_pointer(0)));
}

void test_value_string_comparation(void)
{
    s3_value_t value1 = s3_value_string("test string");

    ASSERT_EQ(S3_VALUE_GREATER, value1->compare(value1, s3_value_char('a')));
    ASSERT_EQ(S3_VALUE_EQUAL, value1->compare(value1, s3_value_string("test string")));
    ASSERT_EQ(S3_VALUE_LESS, value1->compare(value1, s3_value_char('z')));
    ASSERT_EQ(S3_VALUE_DIFFERENT, value1->compare(value1, s3_value_pointer(0)));
    ASSERT_EQ(S3_VALUE_DIFFERENT, value1->compare(value1, s3_value_float32(1)));
    ASSERT_EQ(S3_VALUE_DIFFERENT, value1->compare(value1, s3_value_uint(4)));
    ASSERT_EQ(S3_VALUE_DIFFERENT, value1->compare(value1, s3_value_int(3)));
}



// s3_value_t value2 = s3_value_uint(1);
// s3_value_t value3 = s3_value_float32(3.4);
// s3_value_t value4 = s3_value_float64(0.55233);
// s3_value_t value5 = s3_value_string("test");
// s3_value_t value6 = s3_value_char('x');

int main()
{
    RUN(test_value_int_creation);
    RUN(test_value_unsigned_creation);
    RUN(test_value_float32_creation);
    RUN(test_value_float64_creation);
    RUN(test_value_string_creation);
    RUN(test_value_pointer_creation);
    RUN(test_value_char_creation);
    RUN(test_value_none_creation);

    RUN(test_value_int_repr);

    RUN(test_value_int_comparation);
    RUN(test_value_uint_comparation);
    RUN(test_value_float32_comparation);
    RUN(test_value_float64_comparation);
    RUN(test_value_string_comparation);
    return TEST_REPORT();
}
