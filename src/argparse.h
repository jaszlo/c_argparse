#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char *key;
    unsigned int value_count;
    char **values;
} Arg;


typedef enum ParseResult {
    PARSE_FAILURE = 0,
    PARSE_SUCCESS = 1,
    PARSE_NO_VALUES = 2,
} ParseResult;

void parse_create(int argc, char *argv[]);

void parse_lookup_args(Arg **args_ref, unsigned int *arg_count_ref);

void parse_destroy();


ParseResult parse(char *key, char **result);
ParseResult parse_multiple(char *key, char ***result);


ParseResult parse_long(char *key, long *result);
ParseResult parse_multiple_long(char *key, long **result);


ParseResult parse_double(char *key, double *result);
ParseResult parse_multiple_double(char *key, double **result);


ParseResult parse_path(char *key, char **result);
ParseResult parse_multiple_path(char *key, char ***result);

#endif // ARGPARSE_H