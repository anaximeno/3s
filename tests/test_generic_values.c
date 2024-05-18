#include "../include/tinytest/tinytest.h"
#include "../include/3s/3s.h"

#include <stdint.h>

// -- Testing value creation

void test_value_int_creation(void)
{
    ts_generic_t value = ts_int(9);
    ASSERT_EQ(value->data.integer, (int32_t)9);
    ASSERT_EQ(value->type, INTEGER);
}

void test_value_unsigned_creation(void)
{
    ts_generic_t value = ts_uint(9);
    ASSERT_EQ(value->data.uinteger, (uint32_t)9);
    ASSERT_EQ(value->type, UNSIGNED);
}

void test_value_float32_creation(void)
{
    ts_generic_t value = ts_float32(9);
    ASSERT_EQ(value->data.float32, (float)9);
    ASSERT_EQ(value->type, FLOAT32);
}

void test_value_float64_creation(void)
{
    ts_generic_t value = ts_float64(9);
    ASSERT_EQ(value->data.float64, (double)9);
    ASSERT_EQ(value->type, FLOAT64);
}

void test_value_string_creation(void)
{
    ts_generic_t value = ts_string("Test");
    ASSERT_STR_EQ(value->data.string, "Test");
    ASSERT_EQ(value->type, STRING);
}

void test_value_pointer_creation(void)
{
    ts_generic_t value = ts_pointer((void *)3);
    ASSERT_EQ(value->data.pointer, (void *)3);
    ASSERT_EQ(value->type, POINTER);
}

void test_value_char_creation(void)
{
    ts_generic_t value = ts_char('X');
    ASSERT_EQ(value->data.character, 'X');
    ASSERT_EQ(value->type, CHARACTER);
}

void test_value_none_creation(void)
{
    ts_generic_t value = ts_none();
    ASSERT_EQ(value->type, NONE);
}

// -- Testing representation

void test_value_int_repr(void)
{
    ts_generic_t value = ts_int(3);
    ASSERT_STR_EQ(value->repr(value), "3");
}

// -- Testing comparation

void test_value_int_comparation(void)
{
    ts_generic_t value1 = ts_int(3);

    ASSERT_EQ(TS_GREATER, value1->compare(value1, ts_uint(1)));
    ASSERT_EQ(TS_LESS, value1->compare(value1, ts_float32(3.4)));
    ASSERT_EQ(TS_EQUAL, value1->compare(value1, ts_float64(3.0)));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_string("test")));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_char('x')));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_pointer(0)));
}

void test_value_uint_comparation(void)
{
    ts_generic_t value1 = ts_uint(3);

    ASSERT_EQ(TS_GREATER, value1->compare(value1, ts_float32(1)));
    ASSERT_EQ(TS_LESS, value1->compare(value1, ts_float64(4)));
    ASSERT_EQ(TS_EQUAL, value1->compare(value1, ts_int(3)));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_string("test")));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_char('x')));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_pointer(0)));
}

void test_value_float32_comparation(void)
{
    ts_generic_t value1 = ts_float32(3.0);

    ASSERT_EQ(TS_GREATER, value1->compare(value1, ts_float64(1)));
    ASSERT_EQ(TS_LESS, value1->compare(value1, ts_uint(4)));
    ASSERT_EQ(TS_EQUAL, value1->compare(value1, ts_int(3)));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_string("test")));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_char('x')));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_pointer(0)));
}

void test_value_float64_comparation(void)
{
    ts_generic_t value1 = ts_float64(3.0);

    ASSERT_EQ(TS_GREATER, value1->compare(value1, ts_float32(1)));
    ASSERT_EQ(TS_LESS, value1->compare(value1, ts_uint(4)));
    ASSERT_EQ(TS_EQUAL, value1->compare(value1, ts_int(3)));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_string("test")));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_char('x')));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_pointer(0)));
}

void test_value_string_comparation(void)
{
    ts_generic_t value1 = ts_string("test string");

    ASSERT_EQ(TS_GREATER, value1->compare(value1, ts_char('a')));
    ASSERT_EQ(TS_EQUAL, value1->compare(value1, ts_string("test string")));
    ASSERT_EQ(TS_LESS, value1->compare(value1, ts_char('z')));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_pointer(0)));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_float32(1)));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_uint(4)));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_int(3)));
}

// ts_generic_t value2 = ts_uint(1);
// ts_generic_t value3 = ts_float32(3.4);
// ts_generic_t value4 = ts_float64(0.55233);
// ts_generic_t value5 = ts_string("test");
// ts_generic_t value6 = ts_char('x');

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
