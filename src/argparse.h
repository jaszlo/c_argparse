#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Data structure for storing arguments and their values.
 * 
 */
typedef struct {
    char *key;
    unsigned int value_count;
    char **values;
} Arg;


/**
 * @brief Describes the result of a parse operation.
 * The parse operation can fail, succeed, or succeed with no values.
 */
typedef enum ParseResult {
    PARSE_FAILURE = 0,
    PARSE_SUCCESS = 1,
    PARSE_NO_VALUES = 2,
} ParseResult;

/**
 * @brief Initializes the parser with the given arguments.
 * 
 * @param argc argument count given to main
 * @param argv argument vector given to main
 */
void parse_create(int argc, char *argv[]);

/**
 * @brief Moves references to the internal args and arg_count variables to the given pointers.
 * 
 * @param args_ref reference to the args variables created by parse_create
 * @param arg_count_ref reference to the arg_count variable created by parse_create
 */
void parse_lookup_args(Arg **args_ref, unsigned int *arg_count_ref);

/**
 * @brief Frees all memory allocated by the parser. Does not include values creates by parse_multiple.
 */
void parse_destroy();

/**
 * @brief Parse the first value for the given key as a string
 * 
 * @param key Key of the argument to parse
 * @param result Reference where the first value of the argument
 * @return ParseResult PARSE_SUCCESS, PARSE_FAILURE, or PARSE_NO_VALUES 
 */
ParseResult parse(char *key, char **result);
/**
 * @brief Parse all values for the given key as a string
 * 
 * @param key Key of the argument to parse
 * @param result Reference where all values of the argument
 * @return ParseResult PARSE_SUCCESS, PARSE_FAILURE, or PARSE_NO_VALUES 
 */
ParseResult parse_multiple(char *key, char ***result);


/**
 * @brief Parse the first value for the given key as a long
 * 
 * @param key Key of the argument to parse
 * @param result Reference where the first value of the argument
 * @return ParseResult PARSE_SUCCESS, PARSE_FAILURE, or PARSE_NO_VALUES 
 */
ParseResult parse_long(char *key, long *result);
/**
 * @brief Parse all values for the given key as a long
 * 
 * @param key Key of the argument to parse
 * @param result Reference where all values of the argument as a long
 * @return ParseResult PARSE_SUCCESS, PARSE_FAILURE, or PARSE_NO_VALUES 
 */
ParseResult parse_multiple_long(char *key, long **result);


/**
 * @brief Parse the first value for the given key as a double
 * 
 * @param key Key of the argument to parse
 * @param result Reference where the first value of the argument as a double
 * @return ParseResult PARSE_SUCCESS, PARSE_FAILURE, or PARSE_NO_VALUES 
 */
ParseResult parse_double(char *key, double *result);
/**
 * @brief Parse all values for the given key as a double
 * 
 * @param key Key of the argument to parse
 * @param result Reference where all values of the argument as a double
 * @return ParseResult PARSE_SUCCESS, PARSE_FAILURE, or PARSE_NO_VALUES 
 */
ParseResult parse_multiple_double(char *key, double **result);


/**
 * @brief Parse the first value for the given key as a path if it exists
 * 
 * @param key Key of the argument to parse
 * @param result Reference where the first value of the argument as a path if it exists
 * @return ParseResult PARSE_SUCCESS, PARSE_FAILURE, or PARSE_NO_VALUES 
 */
ParseResult parse_path(char *key, char **result);
/**
 * @brief Parse all values for the given key as a path if it exists
 * 
 * @param key Key of the argument to parse
 * @param result Reference where all values of the argument as a path if it exists
 * @return ParseResult PARSE_SUCCESS, PARSE_FAILURE, or PARSE_NO_VALUES 
 */
ParseResult parse_multiple_path(char *key, char ***result);

#endif // ARGPARSE_H