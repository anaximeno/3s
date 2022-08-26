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
    return TEST_REPORT();
}
