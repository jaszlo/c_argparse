#include "argparse.h"
#include "helpers.h"

// Globals
Arg *args;
unsigned int token_count = 0;
unsigned int arg_count = 0;

Arg *_arg_of(char *key) {
    for (unsigned int i = 0; i < arg_count; i++) {
        if (_streq(args[i].key, key)) {
            return &args[i];
        }
    }
    return NULL;
}

#define is_arg(s) ((s != NULL) && (s[0] == '-') && !is_number(s))

#define CHECK_ARG(arg) \
    if (arg == NULL) { \
        return PARSE_FAILURE; \
    } else if (arg->value_count < 1) { \
        return PARSE_NO_VALUES; \
    }

// Creates arg and value_count. Also returns on failure or no values
#define INIT_PARSE() Arg *arg = _arg_of(key); CHECK_ARG(arg) \

void parse_destroy() {
    for (unsigned int i = 0; i < arg_count; i++) {
        if (args[i].values != NULL) {
            free(args[i].values);
            args[i].values = NULL;
        }
    }

    if (args != NULL) {
        free(args);
        args = NULL;
    }

    token_count = 0;
    arg_count = 0;
}

void parse_lookup_args(Arg **args_ref, unsigned int *arg_count_ref) {
    *args_ref = args;
    *arg_count_ref = arg_count;
}

void parse_create(int argc, char *argv[]) {
    token_count = argc;
    arg_count = 0;
    // Count number of total arguments
    for (int i = 0; i < argc; i++) {
        if (is_arg(argv[i])) {
            // Only increase if argv[i] can't be parsed as a number
            arg_count++;
        }
    }

    args = malloc(sizeof(Arg) * arg_count);
    for (unsigned int i = 0; i < arg_count; i++) { args[i].value_count = 0; }

    // Count number of values for each argument
    unsigned int arg_index = 0;
    for (unsigned int i = 0; i < token_count; i++) {
        if (is_arg(argv[i])) {
            for (unsigned int j = i + 1; j < token_count; j++) {
                if (is_arg(argv[j])) {
                    break;
                }
                args[arg_index].value_count++;
            }
            arg_index++;
        }
    }

    // Populate args
    arg_index = 0;
    for (unsigned int i = 0; i < token_count; i++) {
        if (is_arg(argv[i])) {
            args[arg_index].key = argv[i];
            args[arg_index].values = malloc(sizeof(char *) * args[arg_index].value_count);
            for (unsigned int j = 0; j < args[arg_index].value_count; j++) {
                args[arg_index].values[j] = argv[i + j + 1];
            }
            arg_index++;
        }
    }
}

ParseResult parse(char *key, char **result) {
    INIT_PARSE();
    *result = arg->values[0];
    return PARSE_SUCCESS;
}

ParseResult parse_multiple(char *key, char ***result) {
    INIT_PARSE(); 
    *result = arg->values;
    return PARSE_SUCCESS;
}

ParseResult parse_long(char *key, long *result) {
    INIT_PARSE();
    int base = is_hexadecimal(arg->values[0]) ? 16 : (is_binary(arg->values[0]) ? 2 : 10);
    int sign = 1;
    int sign_offset = 0;
    if (arg->values[0][0] == '-') {
        sign = -1;
        sign_offset = 1;
    }
    // Apply offset if base is 2 or 16 (0b, 0x) and 1 for sign if exists
    char *to_parse = arg->values[0] + sign_offset + (2 * (base == 2 || base == 16));
    *result = sign * strtol(to_parse, NULL, base);
    return PARSE_SUCCESS;
}


ParseResult parse_multiple_long(char *key, long **result) {
    INIT_PARSE();
    *result = malloc(sizeof(long) * arg->value_count);
    for (unsigned int i = 0; i < arg->value_count; i++) {
        int base = is_hexadecimal(arg->values[0]) ? 16 : (is_binary(arg->values[0]) ? 2 : 10);
        int sign = 1;
        int sign_offset = 0;
        if (arg->values[i][0] == '-') {
            sign = -1;
            sign_offset = 1;
        }
        // Apply offset if base is 2 or 16 (0b, 0x) and 1 for sign if exists
        char *to_parse = arg->values[i] + sign_offset + (2 * (base == 2 || base == 16));
        (*result)[i] = sign * strtol(to_parse, NULL, base);
    }
    return PARSE_SUCCESS;
}


ParseResult parse_double(char *key, double *result) {
    INIT_PARSE();
    *result = atof(arg->values[0]);
    return PARSE_SUCCESS;
}


ParseResult parse_multiple_double(char *key, double **result) {
    INIT_PARSE();
    *result = malloc(sizeof(double) * arg->value_count);
    for (unsigned int i = 0; i < arg->value_count; i++) {
        (*result)[i] = atof(arg->values[i]);
    }
    return PARSE_SUCCESS;
}

ParseResult parse_path(char *key, char **result) {
    INIT_PARSE();
    if (path_exists(arg->values[0])) {
        *result = arg->values[0];
        return PARSE_SUCCESS;
    } else {
        return PARSE_FAILURE;
    }
}

ParseResult parse_multiple_path(char *key, char ***result) {
    INIT_PARSE();
    *result = malloc(sizeof(long) * arg->value_count);
    for (unsigned int i = 0; i < arg->value_count; i++) {
        if (!path_exists(arg->values[i])) {
            free(*result);
            return PARSE_FAILURE;
        }
        (*result)[i] = arg->values[i];
    }
    return PARSE_SUCCESS;
}



