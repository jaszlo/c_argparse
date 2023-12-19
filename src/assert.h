#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef ASSERT_H
#define ASSERT_H 
void _printf(char *format, ...);

void assert_reset(char *test_category);
void assert_report();


#define assert(condition, message) _assert(condition, message, __FILE__, __LINE__)
void _assert(bool condition, char *message, char *file, int line_number);

#define assert_require(condition, message) _assert_require(condition, message, __FILE__, __LINE__)
void _assert_require(bool condition, char *message, char *file, int line_number);

#define assert_true(condition, message) _assert_true(condition, message, __FILE__, __LINE__)
void _assert_true(bool condition, char *message, char *file, int line_number);

#define assert_false(condition, message) _assert_false(condition, message, __FILE__, __LINE__)
void _assert_false(bool condition, char *message, char *file, int line_number);

#define assert_int(expected, actual, message) _assert_int(expected, actual, message, __FILE__, __LINE__)
void _assert_int(int expected, int actual, char *message, char *file, int line_number);

#define assert_double(expected, actual, delta, message) _assert_double(expected, actual, delta, message, __FILE__, __LINE__)
void _assert_double(double expected, double actual, double delta, char *message, char *file, int line_number);

#define assert_char(expected, actual, message) _assert_char(expected, actual, message, __FILE__, __LINE__)
void _assert_char(char expected, char actual, char *message, char *file, int line_number);

#define assert_pointer(expected, actual, message) _assert_pointer(expected, actual, message, __FILE__, __LINE__)
void _assert_pointer(void *expected, void *actual, char *message, char *file, int line_number);

#define assert_string(expected, actual, length, message) _assert_string(expected, actual, length, message, __FILE__, __LINE__)
void _assert_string(char *expected, char *actual, unsigned int length, char *message, char *file, int line_number);

#define assert_array(arr1, arr2, length, message) _assert_array(arr1, arr2, length, message, __FILE__, __LINE__)
void _assert_array(void *arr1[], void *arr2[], unsigned int length, char *message, char *file, int line_number);

#define assert_not_null(pointer, message) _assert_not_null(pointer, message, __FILE__, __LINE__)
void _assert_not_null(void *pointer, char *message, char *file, int line_number);

#define assert_null(pointer, message) _assert_null(pointer, message, __FILE__, __LINE__)
void _assert_null(void *pointer, char *message, char *file, int line_number);

unsigned int assertion_failures();

unsigned int assertion_count();


#endif // ASSERT_H