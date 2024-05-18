#include "../include/tinytest/tinytest.h"
#include "../include/3s/3s.h"

#include <stdint.h>

// -- Testing value creation

void test_value_int_creation(void)
{
    ts_generic_t value = ts_new_int(9);
    ASSERT_EQ(value->data.integer, (int32_t)9);
    ASSERT_EQ(value->type, TS_TYPE_INTEGER);
}

void test_value_unsigned_creation(void)
{
    ts_generic_t value = ts_new_uint(9);
    ASSERT_EQ(value->data.uinteger, (uint32_t)9);
    ASSERT_EQ(value->type, TS_TYPE_UNSIGNED);
}

void test_value_float32_creation(void)
{
    ts_generic_t value = ts_new_float32(9);
    ASSERT_EQ(value->data.float32, (float)9);
    ASSERT_EQ(value->type, TS_TYPE_FLOAT32);
}

void test_value_float64_creation(void)
{
    ts_generic_t value = ts_new_float64(9);
    ASSERT_EQ(value->data.float64, (double)9);
    ASSERT_EQ(value->type, TS_TYPE_FLOAT64);
}

void test_value_string_creation(void)
{
    ts_generic_t value = ts_new_string("Test");
    ASSERT_STR_EQ(value->data.string, "Test");
    ASSERT_EQ(value->type, TS_TYPE_STRING);
}

void test_value_pointer_creation(void)
{
    ts_generic_t value = ts_new_pointer((void *)3);
    ASSERT_EQ(value->data.pointer, (void *)3);
    ASSERT_EQ(value->type, TS_TYPE_POINTER);
}

void test_value_char_creation(void)
{
    ts_generic_t value = ts_new_char('X');
    ASSERT_EQ(value->data.character, 'X');
    ASSERT_EQ(value->type, TS_TYPE_CHARACTER);
}

void test_value_none_creation(void)
{
    ts_generic_t value = ts_new_none();
    ASSERT_EQ(value->type, TS_TYPE_NONE);
}

// -- Testing representation

void test_value_int_repr(void)
{
    ts_generic_t value = ts_new_int(3);
    ASSERT_STR_EQ(value->repr(value), "3");
}

// -- Testing comparation

void test_value_int_comparation(void)
{
    ts_generic_t value1 = ts_new_int(3);

    ASSERT_EQ(TS_GREATER, value1->compare(value1, ts_new_uint(1)));
    ASSERT_EQ(TS_LESS, value1->compare(value1, ts_new_float32(3.4)));
    ASSERT_EQ(TS_EQUAL, value1->compare(value1, ts_new_float64(3.0)));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_new_string("test")));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_new_char('x')));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_new_pointer(0)));
}

void test_value_uint_comparation(void)
{
    ts_generic_t value1 = ts_new_uint(3);

    ASSERT_EQ(TS_GREATER, value1->compare(value1, ts_new_float32(1)));
    ASSERT_EQ(TS_LESS, value1->compare(value1, ts_new_float64(4)));
    ASSERT_EQ(TS_EQUAL, value1->compare(value1, ts_new_int(3)));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_new_string("test")));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_new_char('x')));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_new_pointer(0)));
}

void test_value_float32_comparation(void)
{
    ts_generic_t value1 = ts_new_float32(3.0);

    ASSERT_EQ(TS_GREATER, value1->compare(value1, ts_new_float64(1)));
    ASSERT_EQ(TS_LESS, value1->compare(value1, ts_new_uint(4)));
    ASSERT_EQ(TS_EQUAL, value1->compare(value1, ts_new_int(3)));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_new_string("test")));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_new_char('x')));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_new_pointer(0)));
}

void test_value_float64_comparation(void)
{
    ts_generic_t value1 = ts_new_float64(3.0);

    ASSERT_EQ(TS_GREATER, value1->compare(value1, ts_new_float32(1)));
    ASSERT_EQ(TS_LESS, value1->compare(value1, ts_new_uint(4)));
    ASSERT_EQ(TS_EQUAL, value1->compare(value1, ts_new_int(3)));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_new_string("test")));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_new_char('x')));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_new_pointer(0)));
}

void test_value_string_comparation(void)
{
    ts_generic_t value1 = ts_new_string("test string");

    ASSERT_EQ(TS_GREATER, value1->compare(value1, ts_new_char('a')));
    ASSERT_EQ(TS_EQUAL, value1->compare(value1, ts_new_string("test string")));
    ASSERT_EQ(TS_LESS, value1->compare(value1, ts_new_char('z')));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_new_pointer(0)));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_new_float32(1)));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_new_uint(4)));
    ASSERT_EQ(TS_DIFFERENT, value1->compare(value1, ts_new_int(3)));
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

    RUN(test_value_int_comparation);
    RUN(test_value_uint_comparation);
    RUN(test_value_float32_comparation);
    RUN(test_value_float64_comparation);
    RUN(test_value_string_comparation);

    return TEST_REPORT();
}
