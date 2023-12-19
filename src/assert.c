#include "assert.h"
#ifdef GDB
// If in Debug GDB mode we don't want to print anyhting therefore
void _printf(char *format, ...) {
    (void)format;
    return;
}
#else
#include <stdarg.h>
// This acts just like printf but does nothing if in GDB mode
void _printf(char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
#endif // GDB

int assert_count = 0;
int assert_fail_count = 0;

char *current_test_category = NULL;

void _assert_require(bool condition, char *message, char *file, int line_number) {
    if (!condition) {
        _printf("Assertion in %s:%d failed: %s\n", file, line_number, message);
        exit(EXIT_FAILURE);
    }
}

void assert_reset(char *test_category) {
    assert_count = 0;
    assert_fail_count = 0;
    current_test_category = test_category;
}

void assert_report() {
    _printf("\n");
    if (assert_fail_count > 0) {
        _printf("Total Assertions: %d\n", assert_count);
        _printf("Assertions failed: %d\n", assert_fail_count);
    } else {
        _printf("Test Category %s was succfesully completed\n", current_test_category);
        _printf("All %d assertions passed\n", assert_count);
        _printf("=========================================================\n\n\n\n");
    }
}

void _assert(bool condition, char *message, char *file, int line_number) {
    assert_count++;
    if (!condition) {
        _printf("\nAssertion %d failed\n\t%s:%d\n\t%s\n", assert_count, file, line_number, message);
        assert_fail_count++;
        return;
    }
    _printf("Assertion %d passed ✓\n", assert_count);
}

void _assert_true(bool condition, char *message, char *file, int line_number) {
    _assert(condition, message, file, line_number);
    if (!condition) {
        _printf("\tExpected: true , Actual false\n");
    }
}

void _assert_false(bool condition, char *message, char *file, int line_number) {
    _assert(!condition, message, file, line_number);
}

void _assert_int(int expected, int actual, char *message, char *file, int line_number) {
    _assert(expected == actual, message, file, line_number);
    if (expected != actual) {
        _printf("\tExpected: %d , Actual %d\n\n", expected, actual);
    }
}

void _assert_double(double expected, double actual, double delta, char *message, char *file, int line_number) {
    _assert(expected - delta <= actual && expected + delta >= actual, message, file, line_number);
    if (expected - delta > actual || expected + delta < actual) {
        _printf("Expected: %f , Actual %f\n", expected, actual);
    }
}

void _assert_char(char expected, char actual, char *message, char *file, int line_number) {
    _assert(expected == actual, message, file, line_number);
    if (expected != actual) {
        _printf("Expected: %c , Actual %c\n", expected, actual);
    }
}

void _assert_pointer(void *expected, void *actual, char *message, char *file, int line_number) {
    _assert(expected == actual, message, file, line_number);
    if (expected != actual) {
        _printf("Expected: %p , Actual %p\n", expected, actual);
    }
}

void _assert_string(char *expected, char *actual, unsigned int length, char *message, char *file, int line_number) {
    if ((expected == NULL) != (actual == NULL)) {
        _printf("Either Exepcetd or Actual Value was NULL\n");
        _assert(false, message, file, line_number);
        return;
    }
    for (unsigned int i = 0; i < length; i++) {
        if (expected[i] != actual[i]) {
            _printf("Expected: %s , Actual %s\n", expected, actual);
            _assert(false, message, file, line_number);
            return;
        }
    }
    _assert(true, message, file, line_number);
}

void _assert_array(void *expected[], void *actual[], unsigned int length, char *message, char *file, int line_number) {
    if ((expected == NULL) != (actual == NULL)) {
        _assert(false, message, file, line_number);
        return;
    }
    for (unsigned int i = 0; i < length; i++) {
        if (expected[i] != actual[i]) {
            _assert(false, message, file, line_number);
            return;
        }
    }
}

void _assert_not_null(void *pointer, char *message, char *file, int line_number) {
    _assert(pointer != NULL, message, file, line_number);
}

void _assert_null(void *pointer, char *message, char *file, int line_number) {
    _assert(pointer == NULL, message, file, line_number);
}

unsigned int assertion_failures() {
    return assert_fail_count;
}

unsigned int assertion_count() {
    return assert_count;
}

