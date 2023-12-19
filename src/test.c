#include <stdio.h>
#include "argparse.h"
#include "assert.h"

int main() {
    const int argc = 17;
    char *argv[] = { 
        "test", 
        "-a", "1", "-2", 
        "-b", "1.2", "-3.2",
        "--c", 
        "-path", "test", "src", 
        "-hex", "0xFF", "-0XF0", // 255, -240
        "-binary", "0b101010", "-0b010101" // 42, -21
};

    parse_create(argc, argv);   
    assert_reset("ArgParse");

    // Block for test cases
    {
        // Strings
        char *s_result;
        assert_int(PARSE_SUCCESS, parse("-a", &s_result), "Parse single value as string returns PARSE_SUCCESS");
        assert_string(s_result, "1", 1, "Parse single value as string parses correctly");
        assert_int(PARSE_NO_VALUES, parse("--c", &s_result), "Parse single value as string returns PARSE_NO_VALUES");

        char **ms_result;
        assert_int(PARSE_SUCCESS, parse_multiple("-a", &ms_result), "Parse multiple values as string returns PARSE_SUCCESS");
        assert_int(PARSE_NO_VALUES, parse_multiple("--c", &ms_result), "Parse multiple values as string returns PARSE_NO_VALUES");
        assert_string("1", ms_result[0], 1, "Parse multiple values as string parses first value correctly");
        assert_string("-2", ms_result[1], 2, "Parse multiple values as string parses second value correctly");

        // Integers
        long i_result;
        assert_int(PARSE_SUCCESS, parse_long("-a", &i_result), "Parse single value as int returns PARSE_SUCCESS");
        assert_int(PARSE_NO_VALUES, parse_long("--c", &i_result), "Parse single value as int returns PARSE_NO_VALUES");
        assert_int(1, i_result, "Parse single value as int parses correctly");

        long *mi_result;
        assert_int(PARSE_SUCCESS, parse_multiple_long("-a", &mi_result), "Parse multiple values as int returns PARSE_SUCCESS");
        assert_int(PARSE_NO_VALUES, parse_multiple_long("--c", &mi_result), "Parse multiple values as int returns PARSE_NO_VALUES");
        assert_int(1, mi_result[0], "Parse multiple values as int parses first value correctly");
        assert_int(-2, mi_result[1], "Parse multiple values as int parses second value correctly");
        free(mi_result);


        // Hex Integers
        long h_result;
        assert_int(PARSE_SUCCESS, parse_long("-hex", &h_result), "Parse single value as hex int returns PARSE_SUCCESS");
        assert_int(PARSE_NO_VALUES, parse_long("--c", &h_result), "Parse single value as hex int returns PARSE_NO_VALUES");
        assert_int(255, h_result, "Parse single value as hex int parses correctly");

        long *mh_result;
        assert_int(PARSE_SUCCESS, parse_multiple_long("-hex", &mh_result), "Parse multiple values as hex int returns PARSE_SUCCESS");
        assert_int(PARSE_NO_VALUES, parse_multiple_long("--c", &mh_result), "Parse multiple values as hex int returns PARSE_NO_VALUES");
        assert_int(255, mh_result[0], "Parse multiple values as hex int parses first value correctly");
        assert_int(-240, mh_result[1], "Parse multiple values as hex int parses second value correctly");
        free(mh_result);


        // Binary Integers
        long b_result;
        assert_int(PARSE_SUCCESS, parse_long("-binary", &b_result), "Parse single value as binary int returns PARSE_SUCCESS");
        assert_int(PARSE_NO_VALUES, parse_long("--c", &b_result), "Parse single value as binary int returns PARSE_NO_VALUES");
        assert_int(42, b_result, "Parse single value as binary int parses correctly");
        
        long *mb_result;
        assert_int(PARSE_SUCCESS, parse_multiple_long("-binary", &mb_result), "Parse multiple values as binary int returns PARSE_SUCCESS");
        assert_int(PARSE_NO_VALUES, parse_multiple_long("--c", &mb_result), "Parse multiple values as binary int returns PARSE_NO_VALUES");
        assert_int(42, mb_result[0], "Parse multiple values as binary int parses first value correctly");
        assert_int(-21, mb_result[1], "Parse multiple values as binary int parses second value correctly");
        free(mb_result);


        // Doubles
        double d_result;
        assert_int(PARSE_SUCCESS, parse_double("-b", &d_result), "Parse single value as double returns PARSE_SUCCESS");
        assert_int(PARSE_NO_VALUES, parse_double("--c", &d_result), "Parse single value as double returns PARSE_NO_VALUES");
        assert_double(1.2, d_result,  0.0001, "Parse single value as double parses correctly");
        
        double *md_result;
        assert_int(PARSE_SUCCESS, parse_multiple_double("-b", &md_result), "Parse multiple values as double returns PARSE_SUCCESS");
        assert_int(PARSE_NO_VALUES, parse_multiple_double("--c", &md_result), "Parse multiple values as double returns PARSE_NO_VALUES");
        assert_double(1.2, md_result[0], 0.0001, "Parse multiple values as double parses first value correctly");
        assert_double(-3.2, md_result[1], 0.0001, "Parse multiple values as double parses second value correctly");
        free(md_result);


        // Paths
        char *p_result;
        assert_int(PARSE_SUCCESS, parse_path("-path", &p_result), "Parse single value as valid path returns PARSE_SUCCESS");
        assert_int(PARSE_NO_VALUES, parse_path("--c", &p_result), "Parse single value as valid path returns PARSE_NO_VALUES");
        assert_string(p_result, "test", 4, "Parse single value as valid path parses correctly");

        char **mp_result;
        assert_int(PARSE_SUCCESS, parse_multiple_path("-path", &mp_result), "Parse multiple values as valid path returns PARSE_SUCCESS");
        assert_int(PARSE_NO_VALUES, parse_multiple_path("--c", &mp_result), "Parse multiple values as valid path returns PARSE_NO_VALUES");
        assert_string(mp_result[0], "test", 4, "Parse multiple values as valid path parses first value correctly");
        assert_string(mp_result[1], "src", 3, "Parse multiple values as valid path parses second value correctly");
        free(mp_result);
    }

    parse_destroy();
    assert_report();

    return 0;
}